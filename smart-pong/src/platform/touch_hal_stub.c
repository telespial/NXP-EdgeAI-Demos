#include "platform/touch_hal.h"

#include <string.h>

#include "edgeai_config.h"

#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_gt911.h"
#include "fsl_lpi2c.h"
#include "fsl_port.h"

#ifndef EDGEAI_TOUCH_I2C
#define EDGEAI_TOUCH_I2C LPI2C2
#endif

#define EDGEAI_TOUCH_INT_PORT PORT4
#define EDGEAI_TOUCH_INT_GPIO GPIO4
#define EDGEAI_TOUCH_INT_PIN  6u

static gt911_handle_t s_touchHandle;
static bool s_touchOk = false;

static volatile bool s_touchPending = false;
static bool s_lastDown = false;

static uint32_t touch_i2c_get_freq(void)
{
    return CLOCK_GetLPFlexCommClkFreq(2u);
}

static status_t touch_i2c_send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = (uint8_t *)txBuff;
    xfer.dataSize = txBuffSize;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    return LPI2C_MasterTransferBlocking(EDGEAI_TOUCH_I2C, &xfer);
}

static status_t touch_i2c_receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = rxBuff;
    xfer.dataSize = rxBuffSize;
    xfer.flags = kLPI2C_TransferDefaultFlag;
    return LPI2C_MasterTransferBlocking(EDGEAI_TOUCH_I2C, &xfer);
}

static void touch_delay_ms(uint32_t delayMs)
{
    SDK_DelayAtLeastUs(delayMs * 1000u, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

static void touch_config_int_pin(gt911_int_pin_mode_t mode)
{
    CLOCK_EnableClock(kCLOCK_Port4);

    port_pin_config_t int_config = {
        .pullSelect = kPORT_PullDown,
        .pullValueSelect = kPORT_LowPullResistor,
        .slewRate = kPORT_FastSlewRate,
        .passiveFilterEnable = kPORT_PassiveFilterDisable,
        .openDrainEnable = kPORT_OpenDrainDisable,
        .driveStrength = kPORT_LowDriveStrength,
#if defined(FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH1) && FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH1
        .driveStrength1 = kPORT_NormalDriveStrength,
#endif
        .mux = kPORT_MuxAlt0,
        .inputBuffer = kPORT_InputBufferEnable,
        .invertInput = kPORT_InputNormal,
        .lockRegister = kPORT_UnlockRegister,
    };

    switch (mode)
    {
        case kGT911_IntPinPullUp:
            int_config.pullSelect = kPORT_PullUp;
            break;
        case kGT911_IntPinPullDown:
            int_config.pullSelect = kPORT_PullDown;
            break;
        case kGT911_IntPinInput:
            int_config.pullSelect = kPORT_PullDisable;
            break;
        default:
            break;
    }

    PORT_SetPinConfig(EDGEAI_TOUCH_INT_PORT, EDGEAI_TOUCH_INT_PIN, &int_config);
}

static void touch_config_reset_pin(bool pullUp)
{
    /* Touch reset is shared with the LCD reset pin on this shield. */
    (void)pullUp;
}

void GPIO40_IRQHandler(void)
{
    uint32_t flags = GPIO_GpioGetInterruptFlags(EDGEAI_TOUCH_INT_GPIO);
    GPIO_GpioClearInterruptFlags(EDGEAI_TOUCH_INT_GPIO, flags);

    if ((flags & (1UL << EDGEAI_TOUCH_INT_PIN)) != 0UL)
    {
        s_touchPending = true;
    }

    SDK_ISR_EXIT_BARRIER;
}

void touch_hal_init(void)
{
    lpi2c_master_config_t masterCfg;
    LPI2C_MasterGetDefaultConfig(&masterCfg);
    masterCfg.baudRate_Hz = 100000u;
    LPI2C_MasterInit(EDGEAI_TOUCH_I2C, &masterCfg, touch_i2c_get_freq());

    s_touchOk = false;
    s_touchPending = false;
    s_lastDown = false;

    gt911_config_t cfg = {
        .I2C_SendFunc = touch_i2c_send,
        .I2C_ReceiveFunc = touch_i2c_receive,
        .timeDelayMsFunc = touch_delay_ms,
        .intPinFunc = touch_config_int_pin,
        .pullResetPinFunc = touch_config_reset_pin,
        .touchPointNum = 2,
        .i2cAddrMode = kGT911_I2cAddrAny,
        .intTrigMode = kGT911_IntFallingEdge,
    };

    status_t st = GT911_Init(&s_touchHandle, &cfg);
    if (st != kStatus_Success)
    {
        PRINTF("SMART PONG: touch init failed: %d\r\n", (int)st);
        return;
    }

    const gpio_pin_config_t intPinConfig = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0u,
    };
    GPIO_PinInit(EDGEAI_TOUCH_INT_GPIO, EDGEAI_TOUCH_INT_PIN, &intPinConfig);
    GPIO_SetPinInterruptConfig(EDGEAI_TOUCH_INT_GPIO, EDGEAI_TOUCH_INT_PIN, kGPIO_InterruptFallingEdge);
    GPIO_PinClearInterruptFlag(EDGEAI_TOUCH_INT_GPIO, EDGEAI_TOUCH_INT_PIN);
    NVIC_ClearPendingIRQ(GPIO40_IRQn);
    EnableIRQ(GPIO40_IRQn);

    s_touchOk = true;
    PRINTF("SMART PONG: touch ok res=%ux%u\r\n", (unsigned)s_touchHandle.resolutionX, (unsigned)s_touchHandle.resolutionY);
}

static inline float clamp01f(float v)
{
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

static inline int32_t clampi(int32_t v, int32_t lo, int32_t hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void touch_hal_poll(edgeai_touch_state_t *out)
{
    if (!out) return;
    memset(out, 0, sizeof(*out));
    for (uint32_t i = 0; i < (sizeof(out->points) / sizeof(out->points[0])); i++)
    {
        out->points[i].active = false;
        out->points[i].x = 0.0f;
        out->points[i].y = 0.0f;
        out->points[i].id = (uint8_t)i;
    }

    if (!s_touchOk)
    {
        out->count = 0;
        return;
    }

    /* Read on an interrupt edge, and keep polling while touch is held to detect release. */
    if (!s_touchPending && !s_lastDown)
    {
        out->count = 0;
        return;
    }

    touch_point_t tp[5];
    uint8_t tp_count = (uint8_t)(sizeof(tp) / sizeof(tp[0]));
    status_t st = GT911_GetMultiTouch(&s_touchHandle, &tp_count, tp);
    s_touchPending = false;

    if (st == kStatus_TOUCHPANEL_NotTouched || tp_count == 0u)
    {
        s_lastDown = false;
        out->count = 0;
        return;
    }

    if (st != kStatus_Success)
    {
        out->count = 0;
        return;
    }

    /* Collect up to two valid points, preferring lower touch IDs for stability. */
    uint8_t keep[2] = {0xFFu, 0xFFu};
    for (uint8_t pass = 0; pass < 2; pass++)
    {
        uint8_t best_i = 0xFFu;
        uint8_t best_id = 0xFFu;
        for (uint8_t i = 0; i < tp_count; i++)
        {
            if (!tp[i].valid) continue;
            uint8_t id = tp[i].touchID;
            if (id >= best_id) continue;
            bool used = false;
            for (uint8_t k = 0; k < pass; k++)
            {
                if (keep[k] == i) used = true;
            }
            if (used) continue;
            best_i = i;
            best_id = id;
        }
        if (best_i == 0xFFu) break;
        keep[pass] = best_i;
    }

    uint32_t out_n = 0;
    for (uint32_t k = 0; k < 2; k++)
    {
        if (keep[k] == 0xFFu) continue;
        touch_point_t *p = &tp[keep[k]];

        /* Orientation mapping to match ST7796S_Orientation270. */
        int32_t x_px = (int32_t)p->y;
        int32_t y_px = (int32_t)((int32_t)s_touchHandle.resolutionX - (int32_t)p->x);

        x_px = clampi(x_px, 0, (int32_t)EDGEAI_LCD_W - 1);
        y_px = clampi(y_px, 0, (int32_t)EDGEAI_LCD_H - 1);

        out->points[out_n].active = true;
        out->points[out_n].x = clamp01f((float)x_px * (1.0f / (float)(EDGEAI_LCD_W - 1)));
        out->points[out_n].y = clamp01f((float)y_px * (1.0f / (float)(EDGEAI_LCD_H - 1)));
        out->points[out_n].id = p->touchID;
        out_n++;
        if (out_n >= 2) break;
    }

    out->count = out_n;
    s_lastDown = (out_n > 0);
}

bool touch_hal_is_ok(void)
{
    return s_touchOk;
}
