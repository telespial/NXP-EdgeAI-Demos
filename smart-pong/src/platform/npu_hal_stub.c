#include "platform/npu_hal.h"
#include "platform/time_hal.h"

#if defined(CONFIG_EDGEAI_USE_NPU) && (CONFIG_EDGEAI_USE_NPU)
bool npu_hal_tflm_neutron_init(npu_hal_t *s);
bool npu_hal_tflm_neutron_predict(npu_hal_t *s, const float features[16], npu_pred_t *out);
#endif

static void npu_hal_reset_stats(npu_hal_t *s)
{
    if (!s) return;
    s->invoke_count = 0u;
    s->invoke_ok_count = 0u;
    s->invoke_fail_count = 0u;
    s->last_infer_us = 0u;
    s->avg_infer_us = 0u;
}

bool npu_hal_init(npu_hal_t *s)
{
    if (!s) return false;
    s->init_ok = false;
    npu_hal_reset_stats(s);

#if defined(CONFIG_EDGEAI_USE_NPU) && (CONFIG_EDGEAI_USE_NPU)
    return npu_hal_tflm_neutron_init(s);
#else
    return true;
#endif
}

bool npu_hal_predict(npu_hal_t *s, const float features[16], npu_pred_t *out)
{
    if (!s || !out) return false;
    if (!s->init_ok) return false;

    uint32_t start_cycles = time_hal_cycles();
    bool ok = false;
#if defined(CONFIG_EDGEAI_USE_NPU) && (CONFIG_EDGEAI_USE_NPU)
    ok = npu_hal_tflm_neutron_predict(s, features, out);
#else
    (void)features;
    ok = false;
#endif

    uint32_t elapsed_us = time_hal_elapsed_us(start_cycles);
    s->invoke_count++;
    s->last_infer_us = elapsed_us;
    if (s->invoke_count == 1u)
    {
        s->avg_infer_us = elapsed_us;
    }
    else
    {
        /* Low-cost moving average for runtime telemetry. */
        s->avg_infer_us = (s->avg_infer_us * 7u + elapsed_us) / 8u;
    }

    if (ok) s->invoke_ok_count++;
    else s->invoke_fail_count++;

    return ok;
}

bool npu_hal_get_telemetry(const npu_hal_t *s, npu_telemetry_t *out)
{
    if (!s || !out) return false;

    out->invoke_count = s->invoke_count;
    out->invoke_ok_count = s->invoke_ok_count;
    out->invoke_fail_count = s->invoke_fail_count;
    out->last_infer_us = s->last_infer_us;
    out->avg_infer_us = s->avg_infer_us;
    return true;
}
