#include "platform/input_hal.h"

#include <string.h>

#include "edgeai_config.h"
#include "edgeai_util.h"

#include "accel4_click.h"

#include "platform/touch_hal.h"

#include "fsl_clock.h"
#include "fsl_debug_console.h"
#include "fsl_lpi2c.h"

#ifndef EDGEAI_I2C
#define EDGEAI_I2C LPI2C3
#endif

/* Touch control tuning.
 * Use dedicated side strips so player fingers stay out of the center play view.
 */

static uint32_t input_i2c_get_freq(void)
{
    return CLOCK_GetLPFlexCommClkFreq(3u);
}

static bool input_i2c_write(uint8_t addr7, uint8_t reg, const uint8_t *data, uint32_t len)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.slaveAddress = addr7;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1;
    xfer.data = (uint8_t *)data;
    xfer.dataSize = len;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    return (LPI2C_MasterTransferBlocking(EDGEAI_I2C, &xfer) == kStatus_Success);
}

static bool input_i2c_read(uint8_t addr7, uint8_t reg, uint8_t *data, uint32_t len)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.slaveAddress = addr7;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1;
    xfer.data = data;
    xfer.dataSize = len;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    return (LPI2C_MasterTransferBlocking(EDGEAI_I2C, &xfer) == kStatus_Success);
}

static inline float clamp01f(float v)
{
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

static inline float remap_touch_y(float ty, float ui_y_max)
{
    if (ty <= ui_y_max) return 0.0f;
    return clamp01f((ty - ui_y_max) / (1.0f - ui_y_max));
}

static inline float remap_touch_z_from_left_edge(float tx)
{
    return clamp01f(tx * (1.0f / EDGEAI_TOUCH_STRIP_W_NORM));
}

static inline float remap_touch_z_from_right_edge(float tx)
{
    float start = 1.0f - EDGEAI_TOUCH_STRIP_W_NORM;
    return clamp01f((tx - start) * (1.0f / EDGEAI_TOUCH_STRIP_W_NORM));
}

static void input_hal_update_accel(input_hal_t *s, platform_input_t *out)
{
    if (!out) return;
    if (!s || !s->accel_ok) return;

    fxls8974_sample_t raw = {0};
    if (!fxls8974_read_sample_12b(&s->accel, &raw))
    {
        s->accel_fail++;
        if (s->accel_has_data)
        {
            out->accel_active = true;
            out->accel_ax = s->accel_last_ax;
            out->accel_ay = s->accel_last_ay;
        }
        return;
    }

    accel_proc_out_t aout;
    accel_proc_update(&s->accel_proc, raw.x, raw.y, raw.z, &aout);

    /* Use a mostly-linear mapping for tilt:
     * - The "soft" response used for paddle control can make small tilts too weak.
     * - Axis mapping must match accel_proc so game/render see the same directions.
     */
    int32_t ax_i = raw.x;
    int32_t ay_i = raw.y;
    accel_proc_apply_axis_map(&ax_i, &ay_i);

    float ax = (float)ax_i / (float)EDGEAI_ACCEL_MAP_DENOM;
    float ay = (float)ay_i / (float)EDGEAI_ACCEL_MAP_DENOM;
    if (ax < -1.0f) ax = -1.0f;
    if (ax > 1.0f) ax = 1.0f;
    if (ay < -1.0f) ay = -1.0f;
    if (ay > 1.0f) ay = 1.0f;

    s->accel_has_data = true;
    s->accel_last_ax = ax;
    s->accel_last_ay = ay;

    out->accel_active = true;
    out->accel_ax = ax;
    out->accel_ay = ay;
    out->accel_bang = aout.bang_pulse;
}

bool input_hal_init(input_hal_t *s)
{
    if (!s) return false;
    memset(s, 0, sizeof(*s));

    touch_hal_init();

    accel_proc_init(&s->accel_proc);
    s->accel_ok = false;
    s->accel_fail = 0;

    lpi2c_master_config_t masterCfg;
    LPI2C_MasterGetDefaultConfig(&masterCfg);
    masterCfg.baudRate_Hz = 100000u;
    LPI2C_MasterInit(EDGEAI_I2C, &masterCfg, input_i2c_get_freq());

    s->accel.addr7 = 0;
    s->accel.write = input_i2c_write;
    s->accel.read = input_i2c_read;

    const uint8_t addrs[] = {ACCEL4_CLICK_I2C_ADDR0, ACCEL4_CLICK_I2C_ADDR1};
    uint8_t who = 0;
    for (size_t i = 0; i < (sizeof(addrs) / sizeof(addrs[0])); i++)
    {
        s->accel.addr7 = addrs[i];
        if (fxls8974_read_whoami(&s->accel, &who) && (who == FXLS8974_WHO_AM_I_VALUE))
        {
            s->accel_ok = true;
            break;
        }
    }

    if (!s->accel_ok)
    {
        PRINTF("SMART PONG: accel not found (WHO_AM_I=0x%02x)\r\n", (unsigned)who);
        return true;
    }

    (void)fxls8974_set_active(&s->accel, false);
    (void)fxls8974_set_fsr(&s->accel, FXLS8974_FSR_4G);
    (void)fxls8974_set_active(&s->accel, true);
    PRINTF("SMART PONG: accel ok addr=0x%02x\r\n", (unsigned)s->accel.addr7);

    return true;
}

void input_hal_poll(input_hal_t *s, platform_input_t *out)
{
    if (!out) return;
    memset(out, 0, sizeof(*out));

    out->p1_active = false;
    out->p1_y = 0.5f;
    out->p1_z = 0.5f;
    out->p2_active = false;
    out->p2_y = 0.5f;
    out->p2_z = 0.5f;
    out->mode_toggle = false;
    out->accel_active = false;
    out->accel_ax = 0.0f;
    out->accel_ay = 0.0f;
    out->accel_bang = false;
    out->touch_active = false;
    out->touch_pressed = false;
    out->touch_x = 0.0f;
    out->touch_y = 0.0f;

    /* Always sample accelerometer when present so game logic can use tilt even
     * when touch is available. Touch still takes precedence for paddle control.
     */
    input_hal_update_accel(s, out);

    edgeai_touch_state_t ts;
    touch_hal_poll(&ts);
    if (ts.count > 0)
    {
        out->touch_active = true;
        out->touch_x = ts.points[0].x;
        out->touch_y = ts.points[0].y;
        out->touch_pressed = s ? (out->touch_active && !s->prev_touch_active) : true;

        /* Do not drive paddles from touches inside the UI bar region. */
        const float ui_y_max = (float)EDGEAI_UI_BAR_H / (float)(EDGEAI_LCD_H - 1);

        /* Touch mapping (strip-only): y -> paddle y, strip x -> paddle z. */
        if (ts.count == 1)
        {
            if (ts.points[0].y >= ui_y_max)
            {
                float tx = clamp01f(ts.points[0].x);
                float ty = clamp01f(ts.points[0].y);
                if (tx <= EDGEAI_TOUCH_STRIP_W_NORM)
                {
                    out->p1_active = true;
                    out->p1_y = remap_touch_y(ty, ui_y_max);
                    out->p1_z = remap_touch_z_from_left_edge(tx);
                }
                else if (tx >= (1.0f - EDGEAI_TOUCH_STRIP_W_NORM))
                {
                    out->p2_active = true;
                    out->p2_y = remap_touch_y(ty, ui_y_max);
                    out->p2_z = 1.0f - remap_touch_z_from_right_edge(tx);
                }
            }
            if (s) s->prev_touch_active = out->touch_active;
            return;
        }

        for (uint32_t i = 0; i < ts.count && i < 2; i++)
        {
            float tx = clamp01f(ts.points[i].x);
            float ty = clamp01f(ts.points[i].y);
            if (ty < ui_y_max) continue;
            if (tx <= EDGEAI_TOUCH_STRIP_W_NORM)
            {
                out->p1_active = true;
                out->p1_y = remap_touch_y(ty, ui_y_max);
                out->p1_z = remap_touch_z_from_left_edge(tx);
            }
            else if (tx >= (1.0f - EDGEAI_TOUCH_STRIP_W_NORM))
            {
                out->p2_active = true;
                out->p2_y = remap_touch_y(ty, ui_y_max);
                out->p2_z = 1.0f - remap_touch_z_from_right_edge(tx);
            }
        }
        if (s) s->prev_touch_active = out->touch_active;
        return;
    }

    if (s) s->prev_touch_active = false;

    /* Touch controller present: do not fall back to accelerometer paddle driving.
     * This avoids unintentional recenters when touch is released.
     */
    if (touch_hal_is_ok())
    {
        return;
    }

    if (!s || !s->accel_ok) return;
    if (!out->accel_active) return;
    float ax = out->accel_ax;
    float ay = out->accel_ay;

    /* Tilt mapping: ay -> y, ax -> z. */
    out->p1_active = true;
    out->p1_y = clamp01f(0.5f - (ay * 0.45f));
    out->p1_z = clamp01f(0.5f + (ax * 0.45f));
    out->mode_toggle = out->accel_bang;
}
