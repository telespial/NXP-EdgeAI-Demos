#include "platform/npu_hal.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>

/*
 * NPU HAL implementation for MCX N (FRDM-MCXN947) using:
 * - TensorFlow Lite Micro (TFLM)
 * - eIQ Neutron backend via the NeutronGraph custom op
 *
 * A small, pre-converted NeutronGraph model is embedded as a placeholder.
 * The model output is used as a deterministic perturbation on top of an
 * analytic intercept predictor derived from the feature vector.
 *
 * A Pong-specific NeutronGraph model can replace the placeholder by swapping
 * the included model header and adjusting the op resolver to match.
 */

#if defined(CONFIG_EDGEAI_USE_NPU) && (CONFIG_EDGEAI_USE_NPU)

#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/kernels/neutron/neutron.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "npu/model_ds_cnn_s_npu_data.h"

namespace {

static inline float clampf(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static inline float sigmoidf(float x)
{
    if (x >= 0.0f)
    {
        float e = expf(-x);
        return 1.0f / (1.0f + e);
    }
    float e = expf(x);
    return e / (1.0f + e);
}

static float reflect_range(float p, float lo, float hi)
{
    if (!(hi > lo)) return lo;
    float w = hi - lo;
    float x = (p - lo) / w; /* normalize */

    /* Reflect in [0,1] with period 2. */
    float m = fmodf(x, 2.0f);
    if (m < 0.0f) m += 2.0f;
    if (m > 1.0f) m = 2.0f - m;

    return lo + m * w;
}

static int tensor_num_elems(const TfLiteTensor *t)
{
    if (!t || !t->dims || t->dims->size <= 0) return 0;
    int n = 1;
    for (int i = 0; i < t->dims->size; i++)
    {
        int d = t->dims->data[i];
        if (d <= 0) return 0;
        n *= d;
    }
    return n;
}

static bool feature_is_pos_idx(int idx)
{
    /* ball x/y/z + paddle y/z terms */
    return (idx == 0) || (idx == 1) || (idx == 2) || (idx == 6) || (idx == 7) || (idx == 10) || (idx == 11);
}

static bool fill_input_from_features(TfLiteTensor *in, const float features[16])
{
    if (!in || !features) return false;
    int n = tensor_num_elems(in);
    if (n <= 0) return false;

    if (in->type == kTfLiteFloat32)
    {
        for (int i = 0; i < n; i++)
        {
            in->data.f[i] = features[i & 15];
        }
        return true;
    }

    const float scale = in->params.scale;
    const int32_t zp = (int32_t)in->params.zero_point;
    if (scale <= 0.0f) return false;

    for (int i = 0; i < n; i++)
    {
        int fi = (i & 15);
        float f = features[fi];
        if (feature_is_pos_idx(fi))
        {
            /* Map 0..1 positions into -1..1. */
            f = (f * 2.0f) - 1.0f;
        }
        f = clampf(f, -1.0f, 1.0f);

        int32_t q = (int32_t)lrintf((f / scale) + (float)zp);
        if (in->type == kTfLiteInt8)
        {
            if (q < -128) q = -128;
            if (q > 127) q = 127;
            in->data.int8[i] = (int8_t)q;
        }
        else if (in->type == kTfLiteUInt8)
        {
            if (q < 0) q = 0;
            if (q > 255) q = 255;
            in->data.uint8[i] = (uint8_t)q;
        }
        else
        {
            return false;
        }
    }

    return true;
}

static bool output_to_noise2(const TfLiteTensor *out, float *ny, float *nz)
{
    if (!ny || !nz) return false;
    *ny = 0.0f;
    *nz = 0.0f;
    if (!out) return false;

    int n = tensor_num_elems(out);
    if (n <= 0) return false;

    auto at_f = [&](int i) -> float {
        if (out->type == kTfLiteFloat32) return out->data.f[i];

        const float scale = out->params.scale;
        const int32_t zp = (int32_t)out->params.zero_point;
        if (scale <= 0.0f) return 0.0f;

        int32_t q = 0;
        if (out->type == kTfLiteInt8) q = (int32_t)out->data.int8[i];
        else if (out->type == kTfLiteUInt8) q = (int32_t)out->data.uint8[i];
        else return 0.0f;

        return ((float)q - (float)zp) * scale;
    };

    float s1 = 0.0f;
    float s2 = 0.0f;

    /* Two deterministic projections from output vector -> [-1,1] signals. */
    for (int i = 0; i < n; i++)
    {
        float v = at_f(i);
        float w1 = (n == 1) ? 0.0f : ((2.0f * (float)i) / (float)(n - 1)) - 1.0f;
        int j = (i * 7) % n;
        float w2 = (n == 1) ? 0.0f : ((2.0f * (float)j) / (float)(n - 1)) - 1.0f;
        s1 += v * w1;
        s2 += v * w2;
    }

    *ny = clampf(s1, -1.0f, 1.0f);
    *nz = clampf(s2, -1.0f, 1.0f);
    return true;
}

static bool output_to_direct_pred(const TfLiteTensor *out, float *y01, float *z01, float *t01)
{
    if (!out || !y01 || !z01 || !t01) return false;
    int n = tensor_num_elems(out);
    if (n < 3) return false;

    auto at_f = [&](int i) -> float {
        if (out->type == kTfLiteFloat32) return out->data.f[i];

        const float scale = out->params.scale;
        const int32_t zp = (int32_t)out->params.zero_point;
        if (scale <= 0.0f) return 0.0f;

        int32_t q = 0;
        if (out->type == kTfLiteInt8) q = (int32_t)out->data.int8[i];
        else if (out->type == kTfLiteUInt8) q = (int32_t)out->data.uint8[i];
        else return 0.0f;

        return ((float)q - (float)zp) * scale;
    };

    *y01 = clampf(sigmoidf(at_f(0)), 0.0f, 1.0f);
    *z01 = clampf(sigmoidf(at_f(1)), 0.0f, 1.0f);
    *t01 = clampf(sigmoidf(at_f(2)), 0.0f, 1.0f);
    return true;
}

static const tflite::Model *s_model = nullptr;
static tflite::MicroInterpreter *s_interpreter = nullptr;
static bool s_interpreter_ok = false;

static tflite::MicroMutableOpResolver<8> s_resolver;
static bool s_resolver_ready = false;

static uint8_t s_tensor_arena[kTensorArenaSize] __attribute__((aligned(16)));

static void ensure_resolver_ready(void)
{
    if (s_resolver_ready) return;

    s_resolver.AddDepthwiseConv2D();
    s_resolver.AddDequantize();
    s_resolver.AddPad();
    s_resolver.AddQuantize();
    s_resolver.AddReshape();
    s_resolver.AddSlice();
    s_resolver.AddSoftmax();
    s_resolver.AddCustom(tflite::GetString_NEUTRON_GRAPH(), tflite::Register_NEUTRON_GRAPH());

    s_resolver_ready = true;
}

} /* namespace */

extern "C" bool npu_hal_tflm_neutron_init(npu_hal_t *s)
{
    if (!s) return false;

    ensure_resolver_ready();

    s_model = tflite::GetModel(model_data);
    if (!s_model || (s_model->version() != TFLITE_SCHEMA_VERSION))
    {
        s->init_ok = false;
        s_interpreter_ok = false;
        return false;
    }

    static tflite::MicroInterpreter static_interpreter(s_model, s_resolver, s_tensor_arena, kTensorArenaSize);
    s_interpreter = &static_interpreter;
    if (s_interpreter->AllocateTensors() != kTfLiteOk)
    {
        s->init_ok = false;
        s_interpreter_ok = false;
        return false;
    }

    s_interpreter_ok = true;
    s->init_ok = true;
    return true;
}

extern "C" bool npu_hal_tflm_neutron_predict(npu_hal_t *s, const float features[16], npu_pred_t *out)
{
    if (!s || !out || !features) return false;
    if (!s->init_ok) return false;
    if (!s_interpreter_ok || !s_interpreter) return false;

    TfLiteTensor *in0 = s_interpreter->input(0);
    if (!fill_input_from_features(in0, features)) return false;

    if (s_interpreter->Invoke() != kTfLiteOk) return false;

    const TfLiteTensor *out0 = s_interpreter->output(0);
    float ny = 0.0f;
    float nz = 0.0f;
    (void)output_to_noise2(out0, &ny, &nz);

    /* Analytic intercept predictor for right paddle plane (x ~= 0.94 - r). */
    const float x = features[0];
    const float y0 = features[1];
    const float z0 = features[2];
    const float vx = features[3];
    const float vy = features[4];
    const float vz = features[5];

    const float r = 0.040f;
    const float x_hit = 0.94f - r;
    const float y_lo = r;
    const float y_hi = 1.0f - r;
    const float z_lo = r;
    const float z_hi = 1.0f - r;

    if (vx <= 0.00001f)
    {
        out->y_hit = 0.5f;
        out->z_hit = 0.5f;
        out->t_hit = 0.0f;
        return true;
    }

    float t = (x_hit - x) / vx;
    if (t < 0.0f) t = 0.0f;
    if (t > 6.0f) t = 6.0f;

    float y_analytic = reflect_range(y0 + (vy * t), y_lo, y_hi);
    float z_analytic = reflect_range(z0 + (vz * t), z_lo, z_hi);

    float y = y_analytic;
    float z = z_analytic;

    /* Direct NPU path:
     * decode first 3 output channels as (y,z,t) signals, map into physical ranges,
     * then blend strongly toward direct output while retaining analytic stability.
     */
    float y01 = 0.5f;
    float z01 = 0.5f;
    float t01 = 0.5f;
    if (output_to_direct_pred(out0, &y01, &z01, &t01))
    {
        float y_direct = y_lo + y01 * (y_hi - y_lo);
        float z_direct = z_lo + z01 * (z_hi - z_lo);
        float t_direct = t01 * 6.0f;

        /* Confidence gate:
         * if direct output diverges strongly from analytic physics, reduce direct weight.
         */
        float dy = fabsf(y_direct - y_analytic);
        float dz = fabsf(z_direct - z_analytic);
        float err = clampf((dy + dz) * 0.5f, 0.0f, 1.0f);
        float trust = 1.0f - err;
        float direct_w = 0.25f + 0.45f * trust; /* [0.25, 0.70] */

        y = clampf(y_analytic * (1.0f - direct_w) + y_direct * direct_w, y_lo, y_hi);
        z = clampf(z_analytic * (1.0f - direct_w) + z_direct * direct_w, z_lo, z_hi);
        t = clampf(t * (1.0f - direct_w) + t_direct * direct_w, 0.0f, 6.0f);
    }
    else
    {
        /* Fallback if output layout is not suitable for direct decoding. */
        const float amp = 0.028f;
        y = clampf(y + ny * amp, y_lo, y_hi);
        z = clampf(z + nz * amp, z_lo, z_hi);
    }

    out->y_hit = y;
    out->z_hit = z;
    out->t_hit = t;
    return true;
}

#endif /* CONFIG_EDGEAI_USE_NPU */
