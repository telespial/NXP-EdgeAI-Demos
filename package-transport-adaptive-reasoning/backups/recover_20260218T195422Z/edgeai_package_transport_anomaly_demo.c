#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "app.h"
#include "board.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_gt911.h"
#include "fsl_i3c.h"
#include "fsl_lpi2c.h"
#include "fsl_ostimer.h"
#include "fsl_port.h"
#include "gauge_render.h"
#include "power_data_source.h"
#include "anomaly_engine.h"
#include "accel4_click.h"
#include "fxls8974cf.h"
#include "ext_flash_recorder.h"

#define TOUCH_I2C LPI2C2
#define TOUCH_I2C_FLEXCOMM_INDEX 2u
#define TOUCH_POINTS 5u
#define TOUCH_INT_PORT PORT4
#define TOUCH_INT_PIN 6u
#define ACCEL_I2C LPI2C3
#define ACCEL_I2C_FLEXCOMM_INDEX 3u
#define TEMP_I3C I3C1
#define TEMP_I3C_INDEX 1u
#define BOARD_TEMP_REG 0x00u
#define TEMP_SENSOR_STATIC_ADDR 0x48u
#define TEMP_SENSOR_DYNAMIC_ADDR 0x08u
#define I3C_BROADCAST_ADDR 0x7Eu
#define I3C_CCC_RSTDAA 0x06u
#define I3C_CCC_SETDASA 0x87u
#define SHIELD_GYRO_ADDR0 0x6Au
#define SHIELD_GYRO_ADDR1 0x6Bu
#define SHIELD_GYRO_REG_WHO_AM_I 0x0Fu
#define SHIELD_GYRO_REG_CTRL1_XL 0x10u
#define SHIELD_GYRO_REG_CTRL2_G 0x11u
#define SHIELD_GYRO_REG_CTRL3_C 0x12u
#define SHIELD_GYRO_REG_OUTX_L_G 0x22u
#define SHIELD_GYRO_REG_OUTX_L_A 0x28u
#define SHIELD_GYRO_REG_FUNC_CFG_ACCESS 0x01u
#define SHIELD_IMU_WHOAMI_LSM6DSO16IS 0x22u
#define SHIELD_IMU_WHOAMI_LSM6DSV16X 0x70u
#define SHIELD_SHUB_FUNC_CFG_ACCESS 0x40u
#define SHIELD_SHUB_REG_SENSOR_HUB_1 0x02u
#define SHIELD_SHUB_REG_MASTER_CONFIG 0x14u
#define SHIELD_SHUB_REG_SLV0_ADD 0x15u
#define SHIELD_SHUB_REG_SLV0_SUBADD 0x16u
#define SHIELD_SHUB_REG_SLV0_CONFIG 0x17u
#define SHIELD_SHUB_REG_DATAWRITE_SLV0 0x21u
#define SHIELD_SHUB_REG_STATUS_MASTER 0x22u
#define SHIELD_SHUB_STATUS_ENDOP 0x01u
#define SHIELD_SHUB_STATUS_NACK_MASK 0x78u
#define SHIELD_SHUB_MASTER_SHUB_PU_EN 0x08u
#define SHIELD_SHUB_MASTER_ON 0x04u
#define SHIELD_SHUB_MASTER_WRITE_ONCE 0x40u
#define SHIELD_SHUB_MASTER_RST_REGS 0x80u
#define SHIELD_LIS2DUXS12_ADDR0 0x18u
#define SHIELD_LIS2DUXS12_ADDR1 0x19u
#define SHIELD_LIS2DUXS12_WHOAMI 0x47u
#define SHIELD_LIS2MDL_ADDR 0x1Eu
#define SHIELD_LIS2MDL_ADDR_ALT 0x1Cu
#define SHIELD_LIS2MDL_REG_WHO_AM_I 0x4Fu
#define SHIELD_LIS2MDL_WHOAMI 0x40u
#define SHIELD_LIS2MDL_REG_CFG_A 0x60u
#define SHIELD_LIS2MDL_REG_CFG_C 0x62u
#define SHIELD_LIS2MDL_REG_OUTX_L 0x68u
#define SHIELD_LPS22DF_ADDR0 0x5Cu
#define SHIELD_LPS22DF_ADDR1 0x5Du
#define SHIELD_LPS22DF_WHOAMI 0xB4u
#define SHIELD_LPS22DF_REG_CTRL1 0x10u
#define SHIELD_LPS22DF_REG_OUT_P_XL 0x28u
#define SHIELD_LPS22DF_PRESS_LSB_PER_HPA 4096
#define SHIELD_SHT40_ADDR0 0x44u
#define SHIELD_SHT40_ADDR1 0x45u
#define SHIELD_SHT40_CMD_MEASURE_LP 0xE0u
#define SHIELD_STTS22H_WHOAMI 0xA0u
#define SHIELD_STTS22H_REG_WHO_AM_I 0x01u
#define SHIELD_STTS22H_REG_CTRL 0x04u
#define SHIELD_STTS22H_REG_TEMP_L 0x06u
#define SHIELD_AUX_POLL_PERIOD_US 150000u

#define TOUCH_POLL_DELAY_US 5000u
#define POWER_TICK_PERIOD_US 1000000u
#define DISPLAY_REFRESH_PERIOD_US 100000u
#define RECPLAY_TICK_PERIOD_US 100000u
#define GYRO_REFRESH_PERIOD_US 100000u
#define ACCEL_LIVE_PERIOD_US 100000u
#define RUNTIME_CLOCK_PERIOD_US 100000u
#define TEMP_REFRESH_PERIOD_US 100000u
#define ACCEL_TEST_LOG_PERIOD_US 1000000u
#define EDGEAI_TIMEBASE_CRYSTAL_HZ 32768u
#define EDGEAI_TIMEBASE_CAL_WINDOW_US 250000u
#ifndef EDGEAI_ENABLE_ACCEL_TEST_LOG
#define EDGEAI_ENABLE_ACCEL_TEST_LOG 0
#endif
#ifndef EDGEAI_ENABLE_SHIELD_SCAN_DIAG
#define EDGEAI_ENABLE_SHIELD_SCAN_DIAG 0
#endif
#ifndef EDGEAI_ENABLE_SHIELD_SENSOR_SCAN_LOG
#define EDGEAI_ENABLE_SHIELD_SENSOR_SCAN_LOG 0
#endif
#ifndef EDGEAI_I2C_RETRY_COUNT
#define EDGEAI_I2C_RETRY_COUNT 3u
#endif
#ifndef EDGEAI_SENSOR_SCAN_MODE
#define EDGEAI_SENSOR_SCAN_MODE 0
#endif

static gt911_handle_t s_touch_handle;
static bool s_touch_ready = false;
static bool s_touch_was_down = false;
static uint32_t s_touch_recover_backoff = 0u;
static bool s_timebase_ready = false;
static uint32_t s_timebase_hz = EDGEAI_TIMEBASE_CRYSTAL_HZ;
static bool s_timebase_use_raw = false;
static bool s_timebase_use_core_cycle = false;
static uint32_t s_core_cycle_prev = 0u;
static uint64_t s_core_cycle_accum = 0u;
static bool s_touch_i2c_inited = false;
static bool s_accel_i2c_inited = false;
static bool s_accel_ready = false;
static fxls8974_dev_t s_accel_dev;
static int16_t s_accel_x_mg = 0;
static int16_t s_accel_y_mg = 0;
static int16_t s_accel_z_mg = 1000;
static bool s_shield_gyro_ready = false;
static uint8_t s_shield_gyro_addr = 0u;
static uint8_t s_shield_gyro_who = 0u;
static bool s_shield_use_touch_bus = true;
static bool s_shield_gyro_missing_logged = false;
static bool s_shield_gyro_read_fail_logged = false;
static uint8_t s_shield_gyro_read_fail_streak = 0u;
static int16_t s_ui_gyro_x = 0;
static int16_t s_ui_gyro_y = 0;
static int16_t s_ui_gyro_z = 0;
static bool s_shield_mag_ready = false;
static bool s_shield_baro_ready = false;
static bool s_shield_sht_ready = false;
static bool s_shield_stts_ready = false;
static bool s_shield_aux_init_done = false;
static bool s_shield_mag_use_shub = false;
static bool s_shield_baro_use_shub = false;
static bool s_shield_stts_use_shub = false;
static bool s_shield_mag_use_touch_bus = true;
static uint8_t s_shield_mag_addr = SHIELD_LIS2MDL_ADDR;
static bool s_shield_baro_use_touch_bus = true;
static bool s_shield_sht_use_touch_bus = true;
static bool s_shield_stts_use_touch_bus = true;
static uint8_t s_shield_baro_addr = 0u;
static uint8_t s_shield_sht_addr = 0u;
static uint8_t s_shield_stts_addr = 0u;
static int16_t s_mag_x_mgauss = 0;
static int16_t s_mag_y_mgauss = 0;
static int16_t s_mag_z_mgauss = 0;
static uint8_t s_shield_mag_reprobe_ticks = 0u;
static int16_t s_baro_dhpa = 10132;
static int16_t s_sht_temp_c10 = 250;
static int16_t s_sht_rh_dpct = 500;
static int16_t s_stts_temp_c10 = 250;
static bool s_temp_ready = false;
static bool s_temp_i3c_inited = false;
static uint8_t s_temp_addr = 0u;
static uint8_t s_temp_c = 25u;
static int16_t s_temp_c10 = 250;
static i3c_bus_type_t s_temp_bus_type = kI3C_TypeI2C;
static power_sample_t s_frame_sample;
static anomaly_output_t s_anom_out;
static bool BoardTempI3CInit(void);
static bool TouchI2CInit(void);
static bool AccelI2CInit(void);
static void ShieldGyroInit(void);
static uint32_t CoreClockHz(void);
static bool ShieldImuSupportsShub(uint8_t who);

typedef struct
{
    uint8_t addr;
    uint8_t reg;
    const char *name;
} diag_probe_t;

static const diag_probe_t kDiagProbes[] = {
    {0x6Au, 0x0Fu, "IMU_A"},
    {0x6Bu, 0x0Fu, "IMU_B"},
    {0x18u, 0x0Fu, "LIS2DUXS12_A"},
    {0x19u, 0x0Fu, "LIS2DUXS12_B"},
    {0x1Eu, 0x4Fu, "LIS2MDL"},
    {0x5Cu, 0x0Fu, "LPS22DF_A"},
    {0x5Du, 0x0Fu, "LPS22DF_B"},
    {0x44u, 0x89u, "SHT4x_CMD"},
    {0x45u, 0x89u, "SHT4x_CMD_ALT"},
    {0x5Du, 0x0Fu, "STTS22H?"},
    {0x3Cu, 0x4Fu, "LIS2MDL_ALT8"},
};

static void ClockFromDeciseconds(uint32_t ds_total, uint8_t *hh, uint8_t *mm, uint8_t *ss, uint8_t *ds)
{
    uint32_t sec_total = ds_total / 10u;
    uint32_t rem_ds = ds_total % 10u;
    uint32_t hh_v = (sec_total / 3600u) % 24u;
    uint32_t mm_v = (sec_total % 3600u) / 60u;
    uint32_t ss_v = sec_total % 60u;

    if (hh != NULL)
    {
        *hh = (uint8_t)hh_v;
    }
    if (mm != NULL)
    {
        *mm = (uint8_t)mm_v;
    }
    if (ss != NULL)
    {
        *ss = (uint8_t)ss_v;
    }
    if (ds != NULL)
    {
        *ds = (uint8_t)rem_ds;
    }
}

static uint8_t ChannelLevelPct(anomaly_level_t lvl)
{
    if (lvl >= ANOMALY_LEVEL_MAJOR)
    {
        return 100u;
    }
    if (lvl >= ANOMALY_LEVEL_MINOR)
    {
        return 80u;
    }
    if (lvl >= ANOMALY_LEVEL_WATCH)
    {
        return 40u;
    }
    return 5u;
}

static void ApplyAnomalyToFrame(power_sample_t *dst)
{
    uint8_t overall = (uint8_t)s_anom_out.overall_level;
    uint8_t ax = ChannelLevelPct(s_anom_out.channel_level[ANOMALY_CH_AX]);
    uint8_t ay = ChannelLevelPct(s_anom_out.channel_level[ANOMALY_CH_AY]);
    uint8_t az = ChannelLevelPct(s_anom_out.channel_level[ANOMALY_CH_AZ]);
    uint8_t tp = ChannelLevelPct(s_anom_out.channel_level[ANOMALY_CH_TEMP]);
    uint8_t maxch = ax;

    if (dst == NULL)
    {
        return;
    }

    if (ay > maxch)
    {
        maxch = ay;
    }
    if (az > maxch)
    {
        maxch = az;
    }
    if (tp > maxch)
    {
        maxch = tp;
    }

    dst->anomaly_score_pct = maxch;
    dst->connector_risk_pct = ax;
    dst->wire_risk_pct = ay;
    dst->thermal_damage_risk_pct = tp;
    dst->degradation_drift_pct = az;
    dst->thermal_risk_s = 0u;

    if (overall >= (uint8_t)ANOMALY_LEVEL_MAJOR)
    {
        dst->ai_status = AI_STATUS_FAULT;
    }
    else if (overall >= (uint8_t)ANOMALY_LEVEL_WATCH)
    {
        dst->ai_status = AI_STATUS_WARNING;
    }
    else
    {
        dst->ai_status = AI_STATUS_NORMAL;
    }

    dst->ai_fault_flags = 0u;
}

static void AccelAxisSelfTestLog(void)
{
#if EDGEAI_ENABLE_ACCEL_TEST_LOG
    int32_t ax = s_accel_x_mg;
    int32_t ay = s_accel_y_mg;
    int32_t az = s_accel_z_mg;
    int32_t abx = (ax < 0) ? -ax : ax;
    int32_t aby = (ay < 0) ? -ay : ay;
    int32_t abz = (az < 0) ? -az : az;
    char axis = 'X';
    int32_t val = ax;

    if (aby > abx)
    {
        axis = 'Y';
        val = ay;
        abx = aby;
    }
    if (abz > abx)
    {
        axis = 'Z';
        val = az;
    }

    PRINTF("ACCEL_TEST,DOM=%c%s,X=%d,Y=%d,Z=%d\r\n",
           axis, (val >= 0) ? "+" : "-", (int)ax, (int)ay, (int)az);
#else
    /* Disabled by default to avoid periodic UART blocking in the render loop. */
#endif
}

static void TouchDelayMs(uint32_t delay_ms)
{
    SDK_DelayAtLeastUs(delay_ms * 1000u, CoreClockHz());
}

static bool TimebaseInit(void)
{
    status_t st = CLOCK_SetupOsc32KClocking(kCLOCK_Osc32kToWake);
    uint32_t cfg_hz;
    uint32_t measured_hz = 0u;
    uint64_t t0;
    uint64_t t1;

    CLOCK_AttachClk(kXTAL32K2_to_OSTIMER);
    OSTIMER_Init(OSTIMER0);
    cfg_hz = CLOCK_GetOstimerClkFreq();

    s_timebase_use_core_cycle = false;
    s_timebase_use_raw = false;
    s_timebase_hz = (cfg_hz != 0u) ? cfg_hz : EDGEAI_TIMEBASE_CRYSTAL_HZ;

    /* Calibrate effective OSTIMER tick rate against CPU delay, then quantize to expected divisors. */
    t0 = OSTIMER_GetCurrentTimerValue(OSTIMER0);
    SDK_DelayAtLeastUs(EDGEAI_TIMEBASE_CAL_WINDOW_US, CoreClockHz());
    t1 = OSTIMER_GetCurrentTimerValue(OSTIMER0);
    if (t1 > t0)
    {
        measured_hz = (uint32_t)(((t1 - t0) * 1000000ull) / EDGEAI_TIMEBASE_CAL_WINDOW_US);
    }
    if (measured_hz != 0u)
    {
        /* Accept measured tick rate when plausible; avoid forcing a wrong nominal divisor. */
        if ((measured_hz >= (s_timebase_hz / 2u)) && (measured_hz <= (s_timebase_hz * 2u)))
        {
            s_timebase_hz = measured_hz;
        }
    }

    PRINTF("TIMEBASE: src=ostimer32k setup=%d cfg=%u meas=%u use=%u raw=%u\r\n",
           (int)st,
           (unsigned int)cfg_hz,
           (unsigned int)measured_hz,
           (unsigned int)s_timebase_hz,
           (unsigned int)s_timebase_use_raw);
    s_timebase_ready = true;
    return true;
}

static uint64_t TimebaseNowTicks(void)
{
    if (s_timebase_use_core_cycle)
    {
        uint32_t now = DWT->CYCCNT;
        uint32_t delta = now - s_core_cycle_prev;
        s_core_cycle_prev = now;
        s_core_cycle_accum += (uint64_t)delta;
        return s_core_cycle_accum;
    }
    if (!s_timebase_ready)
    {
        return 0u;
    }
    return s_timebase_use_raw ? OSTIMER_GetCurrentTimerRawValue(OSTIMER0) : OSTIMER_GetCurrentTimerValue(OSTIMER0);
}

static void DelayUsByTimebase(uint32_t delay_us)
{
    uint64_t start_ticks;
    uint64_t wait_ticks;

    if (!s_timebase_ready)
    {
        SDK_DelayAtLeastUs(delay_us, CoreClockHz());
        return;
    }

    start_ticks = TimebaseNowTicks();
    wait_ticks = ((uint64_t)delay_us * s_timebase_hz) / 1000000ull;
    if (wait_ticks == 0u)
    {
        wait_ticks = 1u;
    }
    while ((TimebaseNowTicks() - start_ticks) < wait_ticks)
    {
    }
}

static uint32_t CoreClockHz(void)
{
    uint32_t hz = CLOCK_GetCoreSysClkFreq();
    if (hz == 0u)
    {
        hz = SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY;
    }
    return hz;
}

static bool TouchI2CRecover(void)
{
    s_touch_i2c_inited = false;
    LPI2C_MasterDeinit(TOUCH_I2C);
    return TouchI2CInit();
}

static bool TouchI2CInit(void)
{
    uint32_t src_hz;
    lpi2c_master_config_t cfg;

    if (s_touch_i2c_inited)
    {
        return true;
    }

    CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

    src_hz = CLOCK_GetLPFlexCommClkFreq(TOUCH_I2C_FLEXCOMM_INDEX);
    if (src_hz == 0u)
    {
        PRINTF("TOUCH i2c init failed: FC2 clock=0\r\n");
        return false;
    }

    LPI2C_MasterGetDefaultConfig(&cfg);
    /* Shared bus (GT911 + ST sensor shield): keep conservative speed for stability. */
    cfg.baudRate_Hz = 100000u;
    LPI2C_MasterInit(TOUCH_I2C, &cfg, src_hz);
    s_touch_i2c_inited = true;
    return true;
}

static bool AccelI2CRecover(void)
{
    s_accel_i2c_inited = false;
    LPI2C_MasterDeinit(ACCEL_I2C);
    return AccelI2CInit();
}

static bool AccelI2CInit(void)
{
    uint32_t src_hz;
    lpi2c_master_config_t cfg;

    if (s_accel_i2c_inited)
    {
        return true;
    }

    CLOCK_SetClkDiv(kCLOCK_DivFlexcom3Clk, 1u);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);

    src_hz = CLOCK_GetLPFlexCommClkFreq(ACCEL_I2C_FLEXCOMM_INDEX);
    if (src_hz == 0u)
    {
        PRINTF("ACCEL i2c init failed: FC3 clock=0\r\n");
        return false;
    }

    LPI2C_MasterGetDefaultConfig(&cfg);
    cfg.baudRate_Hz = 100000u;
    LPI2C_MasterInit(ACCEL_I2C, &cfg, src_hz);
    s_accel_i2c_inited = true;
    return true;
}

static bool ShieldBusTransferWithRetry(bool use_touch_bus, lpi2c_master_transfer_t *xfer)
{
    LPI2C_Type *base = use_touch_bus ? TOUCH_I2C : ACCEL_I2C;
    bool inited = use_touch_bus ? TouchI2CInit() : AccelI2CInit();
    uint32_t attempt;

    if (!inited || (xfer == NULL))
    {
        return false;
    }

    for (attempt = 0u; attempt < EDGEAI_I2C_RETRY_COUNT; attempt++)
    {
        if (LPI2C_MasterTransferBlocking(base, xfer) == kStatus_Success)
        {
            return true;
        }
        if (use_touch_bus)
        {
            (void)TouchI2CRecover();
        }
        else
        {
            (void)AccelI2CRecover();
        }
        SDK_DelayAtLeastUs(300u, CoreClockHz());
    }

    return false;
}

static status_t TouchI2CSend(uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             const uint8_t *txBuff,
                             uint8_t txBuffSize)
{
    lpi2c_master_transfer_t xfer;
    status_t st;
    uint32_t attempt;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = (uint8_t *)(uintptr_t)txBuff;
    xfer.dataSize = txBuffSize;
    st = kStatus_Fail;
    for (attempt = 0u; attempt < EDGEAI_I2C_RETRY_COUNT; attempt++)
    {
        st = LPI2C_MasterTransferBlocking(TOUCH_I2C, &xfer);
        if (st == kStatus_Success)
        {
            break;
        }
        (void)TouchI2CRecover();
        SDK_DelayAtLeastUs(250u, CoreClockHz());
    }
    return st;
}

static status_t TouchI2CReceive(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subaddressSize,
                                uint8_t *rxBuff,
                                uint8_t rxBuffSize)
{
    lpi2c_master_transfer_t xfer;
    status_t st;
    uint32_t attempt;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = subAddress;
    xfer.subaddressSize = subaddressSize;
    xfer.data = rxBuff;
    xfer.dataSize = rxBuffSize;
    st = kStatus_Fail;
    for (attempt = 0u; attempt < EDGEAI_I2C_RETRY_COUNT; attempt++)
    {
        st = LPI2C_MasterTransferBlocking(TOUCH_I2C, &xfer);
        if (st == kStatus_Success)
        {
            break;
        }
        (void)TouchI2CRecover();
        SDK_DelayAtLeastUs(250u, CoreClockHz());
    }
    return st;
}

static bool AccelI2CWrite(uint8_t deviceAddress, uint8_t reg, const uint8_t *txBuff, uint32_t txLen)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1u;
    xfer.data = (uint8_t *)(uintptr_t)txBuff;
    xfer.dataSize = txLen;
    return (LPI2C_MasterTransferBlocking(ACCEL_I2C, &xfer) == kStatus_Success);
}

static bool AccelI2CRead(uint8_t deviceAddress, uint8_t reg, uint8_t *rxBuff, uint32_t rxLen)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1u;
    xfer.data = rxBuff;
    xfer.dataSize = rxLen;
    return (LPI2C_MasterTransferBlocking(ACCEL_I2C, &xfer) == kStatus_Success);
}

static bool ShieldBusRead(bool use_touch_bus, uint8_t deviceAddress, uint8_t reg, uint8_t *rxBuff, uint32_t rxLen)
{
    lpi2c_master_transfer_t xfer;

    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1u;
    xfer.data = rxBuff;
    xfer.dataSize = rxLen;
    return ShieldBusTransferWithRetry(use_touch_bus, &xfer);
}

static bool ShieldBusWriteReg(bool use_touch_bus, uint8_t deviceAddress, uint8_t reg, uint8_t value)
{
    lpi2c_master_transfer_t xfer;

    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1u;
    xfer.data = &value;
    xfer.dataSize = 1u;
    return ShieldBusTransferWithRetry(use_touch_bus, &xfer);
}

static bool ShieldBusProbeAddress(bool use_touch_bus, uint8_t deviceAddress)
{
    lpi2c_master_transfer_t xfer;

    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = 0u;
    xfer.subaddressSize = 0u;
    xfer.data = NULL;
    xfer.dataSize = 0u;
    return ShieldBusTransferWithRetry(use_touch_bus, &xfer);
}

static bool ShieldBusWriteRaw(bool use_touch_bus, uint8_t deviceAddress, const uint8_t *txBuff, uint32_t txLen)
{
    lpi2c_master_transfer_t xfer;

    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = 0u;
    xfer.subaddressSize = 0u;
    xfer.data = (uint8_t *)(uintptr_t)txBuff;
    xfer.dataSize = txLen;
    return ShieldBusTransferWithRetry(use_touch_bus, &xfer);
}

static bool ShieldBusReadRaw(bool use_touch_bus, uint8_t deviceAddress, uint8_t *rxBuff, uint32_t rxLen)
{
    lpi2c_master_transfer_t xfer;

    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = deviceAddress;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = 0u;
    xfer.subaddressSize = 0u;
    xfer.data = rxBuff;
    xfer.dataSize = rxLen;
    return ShieldBusTransferWithRetry(use_touch_bus, &xfer);
}

static bool ShieldShubSetAccess(bool enable)
{
    uint8_t value = enable ? SHIELD_SHUB_FUNC_CFG_ACCESS : 0u;
    return ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_FUNC_CFG_ACCESS, value);
}

static bool ShieldShubResetMaster(uint8_t master_cfg)
{
    if (!ShieldBusWriteReg(s_shield_use_touch_bus,
                           s_shield_gyro_addr,
                           SHIELD_SHUB_REG_MASTER_CONFIG,
                           (uint8_t)(master_cfg | SHIELD_SHUB_MASTER_RST_REGS)))
    {
        return false;
    }
    return ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_MASTER_CONFIG, master_cfg);
}

static bool ShieldShubReadRegs(uint8_t ext_addr7, uint8_t reg, uint8_t *rx, uint8_t len)
{
    uint8_t master_cfg = 0u;
    uint8_t status = 0u;
    bool ok = false;

    if ((rx == NULL) || (len == 0u) || (len > 6u) || !s_shield_gyro_ready || (s_shield_gyro_addr == 0u))
    {
        return false;
    }

    if (!ShieldShubSetAccess(true))
    {
        return false;
    }

    do
    {
        if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_MASTER_CONFIG, &master_cfg, 1u))
        {
            break;
        }
        if (!ShieldShubResetMaster(master_cfg))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_ADD, (uint8_t)((ext_addr7 << 1) | 0x01u)))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_SUBADD, reg))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_CONFIG, (uint8_t)(len & 0x07u)))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus,
                               s_shield_gyro_addr,
                               SHIELD_SHUB_REG_MASTER_CONFIG,
                               (uint8_t)((master_cfg & 0xF0u) | SHIELD_SHUB_MASTER_SHUB_PU_EN | SHIELD_SHUB_MASTER_ON)))
        {
            break;
        }

        for (uint32_t attempt = 0u; attempt < 16u; attempt++)
        {
            if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_STATUS_MASTER, &status, 1u))
            {
                break;
            }
            if ((status & SHIELD_SHUB_STATUS_ENDOP) != 0u)
            {
                break;
            }
            SDK_DelayAtLeastUs(1200u, CoreClockHz());
        }

        if (((status & SHIELD_SHUB_STATUS_ENDOP) == 0u) || ((status & SHIELD_SHUB_STATUS_NACK_MASK) != 0u))
        {
            break;
        }
        if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SENSOR_HUB_1, rx, len))
        {
            break;
        }
        ok = true;
    } while (false);

    (void)ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_MASTER_CONFIG, master_cfg);
    (void)ShieldShubSetAccess(false);
    return ok;
}

static bool ShieldShubWriteReg(uint8_t ext_addr7, uint8_t reg, uint8_t value)
{
    uint8_t master_cfg = 0u;
    uint8_t status = 0u;
    bool ok = false;

    if (!s_shield_gyro_ready || (s_shield_gyro_addr == 0u))
    {
        return false;
    }

    if (!ShieldShubSetAccess(true))
    {
        return false;
    }

    do
    {
        if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_MASTER_CONFIG, &master_cfg, 1u))
        {
            break;
        }
        if (!ShieldShubResetMaster(master_cfg))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_ADD, (uint8_t)(ext_addr7 << 1)))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_SUBADD, reg))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_DATAWRITE_SLV0, value))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_SLV0_CONFIG, 0x00u))
        {
            break;
        }
        if (!ShieldBusWriteReg(s_shield_use_touch_bus,
                               s_shield_gyro_addr,
                               SHIELD_SHUB_REG_MASTER_CONFIG,
                               (uint8_t)((master_cfg & 0xB0u) | SHIELD_SHUB_MASTER_WRITE_ONCE |
                                         SHIELD_SHUB_MASTER_SHUB_PU_EN | SHIELD_SHUB_MASTER_ON)))
        {
            break;
        }

        for (uint32_t attempt = 0u; attempt < 16u; attempt++)
        {
            if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_STATUS_MASTER, &status, 1u))
            {
                break;
            }
            if ((status & SHIELD_SHUB_STATUS_ENDOP) != 0u)
            {
                break;
            }
            SDK_DelayAtLeastUs(1200u, CoreClockHz());
        }

        if (((status & SHIELD_SHUB_STATUS_ENDOP) == 0u) || ((status & SHIELD_SHUB_STATUS_NACK_MASK) != 0u))
        {
            break;
        }
        ok = true;
    } while (false);

    (void)ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_SHUB_REG_MASTER_CONFIG, master_cfg);
    (void)ShieldShubSetAccess(false);
    return ok;
}

static bool ShieldSht40CrcOk(const uint8_t *buf2, uint8_t crc)
{
    uint8_t c = 0xFFu;
    for (uint32_t i = 0u; i < 2u; i++)
    {
        c ^= buf2[i];
        for (uint32_t b = 0u; b < 8u; b++)
        {
            c = (c & 0x80u) ? (uint8_t)((c << 1) ^ 0x31u) : (uint8_t)(c << 1);
        }
    }
    return (c == crc);
}

static void ShieldAuxSetRenderState(void)
{
    GaugeRender_SetMag(s_mag_x_mgauss,
                       s_mag_y_mgauss,
                       s_mag_z_mgauss,
                       s_shield_mag_ready);
    GaugeRender_SetBaro(s_baro_dhpa, s_shield_baro_ready);
    GaugeRender_SetSht(s_sht_temp_c10, s_sht_rh_dpct, s_shield_sht_ready);
    GaugeRender_SetStts(s_stts_temp_c10, s_shield_stts_ready);
}

static void ShieldAuxInit(void)
{
    static const bool buses[2] = {true, false};
    static const char *bus_name[2] = {"FC2", "FC3"};
    static const uint8_t stts_addrs[] = {0x3Cu, 0x3Du, 0x3Eu, 0x3Fu, 0x38u};
    uint8_t who = 0u;

    s_shield_mag_ready = false;
    s_shield_baro_ready = false;
    s_shield_sht_ready = false;
    s_shield_stts_ready = false;
    s_shield_mag_use_shub = false;
    s_shield_baro_use_shub = false;
    s_shield_stts_use_shub = false;
    s_shield_mag_use_touch_bus = true;
    s_shield_mag_addr = SHIELD_LIS2MDL_ADDR;
    s_shield_baro_use_touch_bus = true;
    s_shield_sht_use_touch_bus = true;
    s_shield_stts_use_touch_bus = true;
    s_shield_baro_addr = 0u;
    s_shield_sht_addr = 0u;
    s_shield_stts_addr = 0u;

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        if (ShieldBusRead(buses[bi], SHIELD_LIS2MDL_ADDR, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LIS2MDL_WHOAMI))
        {
            s_shield_mag_use_touch_bus = buses[bi];
            s_shield_mag_addr = SHIELD_LIS2MDL_ADDR;
            s_shield_mag_ready = true;
            break;
        }
        if (ShieldBusRead(buses[bi], SHIELD_LIS2MDL_ADDR_ALT, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LIS2MDL_WHOAMI))
        {
            s_shield_mag_use_touch_bus = buses[bi];
            s_shield_mag_addr = SHIELD_LIS2MDL_ADDR_ALT;
            s_shield_mag_ready = true;
            break;
        }
    }
    if (!s_shield_mag_ready && s_shield_gyro_ready && ShieldImuSupportsShub(s_shield_gyro_who))
    {
        if (ShieldShubReadRegs(SHIELD_LIS2MDL_ADDR, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LIS2MDL_WHOAMI))
        {
            s_shield_mag_addr = SHIELD_LIS2MDL_ADDR;
            s_shield_mag_ready = true;
            s_shield_mag_use_shub = true;
        }
        else if (ShieldShubReadRegs(SHIELD_LIS2MDL_ADDR_ALT, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u) &&
                 (who == SHIELD_LIS2MDL_WHOAMI))
        {
            s_shield_mag_addr = SHIELD_LIS2MDL_ADDR_ALT;
            s_shield_mag_ready = true;
            s_shield_mag_use_shub = true;
        }
    }

    if (s_shield_mag_ready)
    {
        if (s_shield_mag_use_shub)
        {
            (void)ShieldShubWriteReg(s_shield_mag_addr, SHIELD_LIS2MDL_REG_CFG_A, 0x00u);
            (void)ShieldShubWriteReg(s_shield_mag_addr, SHIELD_LIS2MDL_REG_CFG_C, 0x10u);
            PRINTF("SHIELD_MAG ready bus=SHUB addr=0x%02x\r\n", (unsigned int)s_shield_mag_addr);
        }
        else
        {
            (void)ShieldBusWriteReg(s_shield_mag_use_touch_bus, s_shield_mag_addr, SHIELD_LIS2MDL_REG_CFG_A, 0x00u);
            (void)ShieldBusWriteReg(s_shield_mag_use_touch_bus, s_shield_mag_addr, SHIELD_LIS2MDL_REG_CFG_C, 0x10u);
            PRINTF("SHIELD_MAG ready bus=%s addr=0x%02x\r\n",
                   s_shield_mag_use_touch_bus ? bus_name[0] : bus_name[1],
                   (unsigned int)s_shield_mag_addr);
        }
    }
    else
    {
        PRINTF("SHIELD_MAG not_found\r\n");
    }

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        if (ShieldBusRead(buses[bi], SHIELD_LPS22DF_ADDR0, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LPS22DF_WHOAMI))
        {
            s_shield_baro_addr = SHIELD_LPS22DF_ADDR0;
            s_shield_baro_use_touch_bus = buses[bi];
            break;
        }
        if (ShieldBusRead(buses[bi], SHIELD_LPS22DF_ADDR1, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LPS22DF_WHOAMI))
        {
            s_shield_baro_addr = SHIELD_LPS22DF_ADDR1;
            s_shield_baro_use_touch_bus = buses[bi];
            break;
        }
    }
    if ((s_shield_baro_addr == 0u) && s_shield_gyro_ready && ShieldImuSupportsShub(s_shield_gyro_who))
    {
        if (ShieldShubReadRegs(SHIELD_LPS22DF_ADDR0, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) &&
            (who == SHIELD_LPS22DF_WHOAMI))
        {
            s_shield_baro_addr = SHIELD_LPS22DF_ADDR0;
            s_shield_baro_use_shub = true;
        }
        else if (ShieldShubReadRegs(SHIELD_LPS22DF_ADDR1, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) &&
                 (who == SHIELD_LPS22DF_WHOAMI))
        {
            s_shield_baro_addr = SHIELD_LPS22DF_ADDR1;
            s_shield_baro_use_shub = true;
        }
    }

    if (s_shield_baro_addr != 0u)
    {
        if (s_shield_baro_use_shub)
        {
            (void)ShieldShubWriteReg(s_shield_baro_addr, SHIELD_LPS22DF_REG_CTRL1, 0x22u);
        }
        else
        {
            (void)ShieldBusWriteReg(s_shield_baro_use_touch_bus, s_shield_baro_addr, SHIELD_LPS22DF_REG_CTRL1, 0x22u);
        }
        s_shield_baro_ready = true;
        if (s_shield_baro_use_shub)
        {
            PRINTF("SHIELD_BARO ready bus=SHUB addr=0x%02x\r\n", (unsigned int)s_shield_baro_addr);
        }
        else
        {
            PRINTF("SHIELD_BARO ready bus=%s addr=0x%02x\r\n",
                   s_shield_baro_use_touch_bus ? bus_name[0] : bus_name[1],
                   (unsigned int)s_shield_baro_addr);
        }
    }

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        if (ShieldBusProbeAddress(buses[bi], SHIELD_SHT40_ADDR0))
        {
            s_shield_sht_addr = SHIELD_SHT40_ADDR0;
            s_shield_sht_use_touch_bus = buses[bi];
            break;
        }
        if (ShieldBusProbeAddress(buses[bi], SHIELD_SHT40_ADDR1))
        {
            s_shield_sht_addr = SHIELD_SHT40_ADDR1;
            s_shield_sht_use_touch_bus = buses[bi];
            break;
        }
    }
    if (s_shield_sht_addr != 0u)
    {
        s_shield_sht_ready = true;
        PRINTF("SHIELD_SHT ready bus=%s addr=0x%02x\r\n",
               s_shield_sht_use_touch_bus ? bus_name[0] : bus_name[1],
               (unsigned int)s_shield_sht_addr);
    }

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        for (uint32_t i = 0u; i < (sizeof(stts_addrs) / sizeof(stts_addrs[0])); i++)
        {
            if (!ShieldBusRead(buses[bi], stts_addrs[i], SHIELD_STTS22H_REG_WHO_AM_I, &who, 1u))
            {
                continue;
            }
            if ((who == SHIELD_STTS22H_WHOAMI) || ((who != 0x00u) && (who != 0xFFu)))
            {
                s_shield_stts_addr = stts_addrs[i];
                s_shield_stts_use_touch_bus = buses[bi];
                break;
            }
        }
        if (s_shield_stts_addr != 0u)
        {
            break;
        }
    }
    if ((s_shield_stts_addr == 0u) && s_shield_gyro_ready && ShieldImuSupportsShub(s_shield_gyro_who))
    {
        for (uint32_t i = 0u; i < (sizeof(stts_addrs) / sizeof(stts_addrs[0])); i++)
        {
            if (!ShieldShubReadRegs(stts_addrs[i], SHIELD_STTS22H_REG_WHO_AM_I, &who, 1u))
            {
                continue;
            }
            if ((who == SHIELD_STTS22H_WHOAMI) || ((who != 0x00u) && (who != 0xFFu)))
            {
                s_shield_stts_addr = stts_addrs[i];
                s_shield_stts_use_shub = true;
                break;
            }
        }
    }

    if (s_shield_stts_addr != 0u)
    {
        if (s_shield_stts_use_shub)
        {
            (void)ShieldShubWriteReg(s_shield_stts_addr, SHIELD_STTS22H_REG_CTRL, 0x0Cu);
        }
        else
        {
            (void)ShieldBusWriteReg(s_shield_stts_use_touch_bus, s_shield_stts_addr, SHIELD_STTS22H_REG_CTRL, 0x0Cu);
        }
        s_shield_stts_ready = true;
        if (s_shield_stts_use_shub)
        {
            PRINTF("SHIELD_STTS ready bus=SHUB addr=0x%02x\r\n", (unsigned int)s_shield_stts_addr);
        }
        else
        {
            PRINTF("SHIELD_STTS ready bus=%s addr=0x%02x\r\n",
                   s_shield_stts_use_touch_bus ? bus_name[0] : bus_name[1],
                   (unsigned int)s_shield_stts_addr);
        }
    }

    s_shield_aux_init_done = true;
    ShieldAuxSetRenderState();
}

static void ShieldAuxUpdate(void)
{
    uint8_t raw[6];

    if (!s_shield_aux_init_done)
    {
        ShieldAuxInit();
    }
    if (s_shield_mag_ready)
    {
        bool ok = true;
        for (uint32_t i = 0u; i < 6u; i++)
        {
            if (s_shield_mag_use_shub)
            {
                if (!ShieldShubReadRegs(s_shield_mag_addr, (uint8_t)(SHIELD_LIS2MDL_REG_OUTX_L + i), &raw[i], 1u))
                {
                    ok = false;
                    break;
                }
            }
            else if (!ShieldBusRead(s_shield_mag_use_touch_bus, s_shield_mag_addr, (uint8_t)(SHIELD_LIS2MDL_REG_OUTX_L + i), &raw[i], 1u))
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            int16_t mx = (int16_t)(((uint16_t)raw[1] << 8) | raw[0]);
            int16_t my = (int16_t)(((uint16_t)raw[3] << 8) | raw[2]);
            int16_t mz = (int16_t)(((uint16_t)raw[5] << 8) | raw[4]);
            s_mag_x_mgauss = (int16_t)((mx * 15) / 10);
            s_mag_y_mgauss = (int16_t)((my * 15) / 10);
            s_mag_z_mgauss = (int16_t)((mz * 15) / 10);
        }
        else
        {
            s_shield_mag_ready = false;
            s_shield_mag_reprobe_ticks = 4u;
        }
    }
    else
    {
        if (s_shield_mag_reprobe_ticks > 0u)
        {
            s_shield_mag_reprobe_ticks--;
        }
        else
        {
            /* Re-scan magnetometer path periodically when unavailable. */
            s_shield_aux_init_done = false;
            ShieldAuxInit();
            s_shield_mag_reprobe_ticks = 4u;
        }
    }

    if (s_shield_baro_ready)
    {
        if ((s_shield_baro_use_shub && ShieldShubReadRegs(s_shield_baro_addr, SHIELD_LPS22DF_REG_OUT_P_XL, raw, 5u)) ||
            (!s_shield_baro_use_shub &&
             ShieldBusRead(s_shield_baro_use_touch_bus, s_shield_baro_addr, SHIELD_LPS22DF_REG_OUT_P_XL, raw, 5u)))
        {
            int32_t p_raw = (int32_t)((((uint32_t)raw[2]) << 16) | (((uint32_t)raw[1]) << 8) | raw[0]);
            if ((p_raw & 0x00800000) != 0)
            {
                p_raw |= (int32_t)0xFF000000;
            }
            s_baro_dhpa = (int16_t)((p_raw * 10) / SHIELD_LPS22DF_PRESS_LSB_PER_HPA);
        }
        else
        {
            s_shield_baro_ready = false;
        }
    }

    if (s_shield_sht_ready)
    {
        uint8_t cmd = SHIELD_SHT40_CMD_MEASURE_LP;
        if (ShieldBusWriteRaw(s_shield_sht_use_touch_bus, s_shield_sht_addr, &cmd, 1u))
        {
            uint16_t raw_t;
            uint16_t raw_rh;
            SDK_DelayAtLeastUs(2500u, CoreClockHz());
            if (ShieldBusReadRaw(s_shield_sht_use_touch_bus, s_shield_sht_addr, raw, 6u) &&
                ShieldSht40CrcOk(&raw[0], raw[2]) &&
                ShieldSht40CrcOk(&raw[3], raw[5]))
            {
                raw_t = (uint16_t)(((uint16_t)raw[0] << 8) | raw[1]);
                raw_rh = (uint16_t)(((uint16_t)raw[3] << 8) | raw[4]);
                s_sht_temp_c10 = (int16_t)(((1750 * (int32_t)raw_t) / 65535) - 450);
                s_sht_rh_dpct = (int16_t)(((1250 * (int32_t)raw_rh) / 65535) - 60);
                if (s_sht_rh_dpct < 0)
                {
                    s_sht_rh_dpct = 0;
                }
                if (s_sht_rh_dpct > 1000)
                {
                    s_sht_rh_dpct = 1000;
                }
            }
            else
            {
                s_shield_sht_ready = false;
            }
        }
        else
        {
            s_shield_sht_ready = false;
        }
    }

    if (s_shield_stts_ready)
    {
        if ((s_shield_stts_use_shub && ShieldShubReadRegs(s_shield_stts_addr, SHIELD_STTS22H_REG_TEMP_L, raw, 2u)) ||
            (!s_shield_stts_use_shub &&
             ShieldBusRead(s_shield_stts_use_touch_bus, s_shield_stts_addr, SHIELD_STTS22H_REG_TEMP_L, raw, 2u)))
        {
            int16_t t_raw = (int16_t)(((uint16_t)raw[1] << 8) | raw[0]);
            s_stts_temp_c10 = (int16_t)(t_raw / 10);
        }
        else
        {
            s_shield_stts_ready = false;
        }
    }

    ShieldAuxSetRenderState();
}

static void __attribute__((unused)) ShieldScanI2CAddresses(bool use_touch_bus, const char *bus_name)
{
    bool found = false;
    PRINTF("SHIELD scan %s addr:", bus_name);
    for (uint8_t addr = 0x08u; addr <= 0x77u; addr++)
    {
        if (ShieldBusProbeAddress(use_touch_bus, addr))
        {
            PRINTF(" 0x%02x", (unsigned int)addr);
            found = true;
        }
    }
    if (!found)
    {
        PRINTF(" none");
    }
    PRINTF("\r\n");
}

static bool __attribute__((unused)) DiagLpi2cInit(LPI2C_Type *base, uint32_t fc_idx, uint32_t baud_hz)
{
    lpi2c_master_config_t cfg;
    uint32_t src_hz;

    if ((base == TOUCH_I2C) && !s_touch_i2c_inited)
    {
        CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u);
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    }
    if ((base == ACCEL_I2C) && !s_accel_i2c_inited)
    {
        CLOCK_SetClkDiv(kCLOCK_DivFlexcom3Clk, 1u);
        CLOCK_AttachClk(kFRO12M_to_FLEXCOMM3);
    }

    src_hz = CLOCK_GetLPFlexCommClkFreq(fc_idx);
    if (src_hz == 0u)
    {
        return false;
    }
    LPI2C_MasterGetDefaultConfig(&cfg);
    cfg.baudRate_Hz = baud_hz;
    LPI2C_MasterDeinit(base);
    LPI2C_MasterInit(base, &cfg, src_hz);
    return true;
}

static bool __attribute__((unused)) DiagLpi2cProbeAddr(LPI2C_Type *base, uint8_t addr7)
{
    lpi2c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = addr7;
    xfer.direction = kLPI2C_Write;
    xfer.subaddress = 0u;
    xfer.subaddressSize = 0u;
    xfer.data = NULL;
    xfer.dataSize = 0u;
    return (LPI2C_MasterTransferBlocking(base, &xfer) == kStatus_Success);
}

static bool __attribute__((unused)) DiagLpi2cReadReg(LPI2C_Type *base, uint8_t addr7, uint8_t reg, uint8_t *val)
{
    lpi2c_master_transfer_t xfer;
    if (val == NULL)
    {
        return false;
    }
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kLPI2C_TransferDefaultFlag;
    xfer.slaveAddress = addr7;
    xfer.direction = kLPI2C_Read;
    xfer.subaddress = reg;
    xfer.subaddressSize = 1u;
    xfer.data = val;
    xfer.dataSize = 1u;
    return (LPI2C_MasterTransferBlocking(base, &xfer) == kStatus_Success);
}

static void __attribute__((unused)) DiagScanLpi2cBus(const char *name, LPI2C_Type *base, uint32_t fc_idx)
{
    static const uint32_t bauds[] = {100000u, 400000u};
    for (uint32_t bi = 0u; bi < (sizeof(bauds) / sizeof(bauds[0])); bi++)
    {
        bool any = false;
        if (!DiagLpi2cInit(base, fc_idx, bauds[bi]))
        {
            PRINTF("DIAG %s %luHz: init_failed\r\n", name, (unsigned long)bauds[bi]);
            continue;
        }
        PRINTF("DIAG %s %luHz addr:", name, (unsigned long)bauds[bi]);
        for (uint8_t addr = 0x08u; addr <= 0x77u; addr++)
        {
            if (DiagLpi2cProbeAddr(base, addr))
            {
                PRINTF(" 0x%02x", (unsigned int)addr);
                any = true;
            }
        }
        if (!any)
        {
            PRINTF(" none");
        }
        PRINTF("\r\n");

        for (uint32_t pi = 0u; pi < (sizeof(kDiagProbes) / sizeof(kDiagProbes[0])); pi++)
        {
            uint8_t who = 0u;
            if (DiagLpi2cReadReg(base, kDiagProbes[pi].addr, kDiagProbes[pi].reg, &who))
            {
                PRINTF("DIAG %s %luHz %s addr=0x%02x reg=0x%02x val=0x%02x\r\n",
                       name,
                       (unsigned long)bauds[bi],
                       kDiagProbes[pi].name,
                       (unsigned int)kDiagProbes[pi].addr,
                       (unsigned int)kDiagProbes[pi].reg,
                       (unsigned int)who);
            }
        }
    }
}

static bool __attribute__((unused)) DiagI3CProbeAddrI2C(uint8_t addr7)
{
    i3c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kI3C_TransferDefaultFlag;
    xfer.slaveAddress = addr7;
    xfer.direction = kI3C_Write;
    xfer.subaddress = 0u;
    xfer.subaddressSize = 0u;
    xfer.data = NULL;
    xfer.dataSize = 0u;
    xfer.busType = kI3C_TypeI2C;
    xfer.ibiResponse = kI3C_IbiRespAck;
    return (I3C_MasterTransferBlocking(TEMP_I3C, &xfer) == kStatus_Success);
}

static void ShieldRunDatastreamDiagnostics(void)
{
#if EDGEAI_ENABLE_SHIELD_SCAN_DIAG
    bool any_i3c = false;
    PRINTF("DIAG start shield datastream scan\r\n");
    DiagScanLpi2cBus("FC2", TOUCH_I2C, TOUCH_I2C_FLEXCOMM_INDEX);
    DiagScanLpi2cBus("FC3", ACCEL_I2C, ACCEL_I2C_FLEXCOMM_INDEX);

    if (BoardTempI3CInit())
    {
        PRINTF("DIAG I3C1(I2C-mode) addr:");
        for (uint8_t addr = 0x08u; addr <= 0x77u; addr++)
        {
            if (DiagI3CProbeAddrI2C(addr))
            {
                PRINTF(" 0x%02x", (unsigned int)addr);
                any_i3c = true;
            }
        }
        if (!any_i3c)
        {
            PRINTF(" none");
        }
        PRINTF("\r\n");
    }
    else
    {
        PRINTF("DIAG I3C1 init_failed\r\n");
    }
    PRINTF("DIAG done shield datastream scan\r\n");
#endif
}

static const char *ShieldImuName(uint8_t who)
{
    if (who == SHIELD_IMU_WHOAMI_LSM6DSO16IS)
    {
        return "LSM6DSO16IS";
    }
    if (who == SHIELD_IMU_WHOAMI_LSM6DSV16X)
    {
        return "LSM6DSV16X";
    }
    return "UNKNOWN";
}

static bool ShieldImuSupportsShub(uint8_t who)
{
    return (who == SHIELD_IMU_WHOAMI_LSM6DSO16IS) || (who == SHIELD_IMU_WHOAMI_LSM6DSV16X);
}

static void ShieldSensorScanLog(void)
{
#if EDGEAI_ENABLE_SHIELD_SENSOR_SCAN_LOG
    static const bool buses[2] = {true, false};
    static const char *bus_name[2] = {"FC2", "FC3"};
    static const uint8_t stts_addrs[] = {0x3Cu, 0x3Du, 0x3Eu, 0x3Fu, 0x38u};
    uint8_t who = 0u;

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        bool use_touch_bus = buses[bi];
        ShieldScanI2CAddresses(use_touch_bus, bus_name[bi]);
        if (ShieldBusRead(use_touch_bus, SHIELD_LIS2DUXS12_ADDR0, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) ||
            ShieldBusRead(use_touch_bus, SHIELD_LIS2DUXS12_ADDR1, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD probe %s LIS2DUXS12 who=0x%02x %s\r\n",
                   bus_name[bi],
                   (unsigned int)who,
                   (who == SHIELD_LIS2DUXS12_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD probe %s LIS2DUXS12 not_found\r\n", bus_name[bi]);
        }

        if (ShieldBusRead(use_touch_bus, SHIELD_LPS22DF_ADDR0, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) ||
            ShieldBusRead(use_touch_bus, SHIELD_LPS22DF_ADDR1, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD probe %s LPS22DF who=0x%02x %s\r\n",
                   bus_name[bi],
                   (unsigned int)who,
                   (who == SHIELD_LPS22DF_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD probe %s LPS22DF not_found\r\n", bus_name[bi]);
        }

        if (ShieldBusRead(use_touch_bus, SHIELD_LIS2MDL_ADDR, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD probe %s LIS2MDL who=0x%02x %s\r\n",
                   bus_name[bi],
                   (unsigned int)who,
                   (who == SHIELD_LIS2MDL_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD probe %s LIS2MDL not_found\r\n", bus_name[bi]);
        }

        if (ShieldBusRead(use_touch_bus, SHIELD_LIS2MDL_ADDR_ALT, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD probe %s LIS2MDL_ALT who=0x%02x %s\r\n",
                   bus_name[bi],
                   (unsigned int)who,
                   (who == SHIELD_LIS2MDL_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD probe %s LIS2MDL_ALT not_found\r\n", bus_name[bi]);
        }

        if (ShieldBusProbeAddress(use_touch_bus, SHIELD_SHT40_ADDR0) || ShieldBusProbeAddress(use_touch_bus, SHIELD_SHT40_ADDR1))
        {
            PRINTF("SHIELD probe %s SHT4x present\r\n", bus_name[bi]);
        }
        else
        {
            PRINTF("SHIELD probe %s SHT4x not_found\r\n", bus_name[bi]);
        }

        {
            bool stts_found = false;
            for (uint32_t i = 0u; i < (sizeof(stts_addrs) / sizeof(stts_addrs[0])); i++)
            {
                if (ShieldBusRead(use_touch_bus, stts_addrs[i], SHIELD_STTS22H_REG_WHO_AM_I, &who, 1u))
                {
                    PRINTF("SHIELD probe %s STTS22H addr=0x%02x who=0x%02x %s\r\n",
                           bus_name[bi],
                           (unsigned int)stts_addrs[i],
                           (unsigned int)who,
                           (who == SHIELD_STTS22H_WHOAMI) ? "ok" : "candidate");
                    stts_found = true;
                    break;
                }
            }
            if (!stts_found)
            {
                PRINTF("SHIELD probe %s STTS22H not_found\r\n", bus_name[bi]);
            }
        }
    }

    if (!s_shield_gyro_ready)
    {
        ShieldGyroInit();
    }
    if (s_shield_gyro_ready && ShieldImuSupportsShub(s_shield_gyro_who))
    {
        static const uint8_t stts_addrs[] = {0x3Cu, 0x3Du, 0x3Eu, 0x3Fu, 0x38u};
        uint8_t who = 0u;
        bool stts_found = false;

        if (ShieldShubReadRegs(SHIELD_LIS2MDL_ADDR, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u) ||
            ShieldShubReadRegs(SHIELD_LIS2MDL_ADDR_ALT, SHIELD_LIS2MDL_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD_SHUB probe LIS2MDL who=0x%02x %s\r\n",
                   (unsigned int)who,
                   (who == SHIELD_LIS2MDL_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD_SHUB probe LIS2MDL not_found\r\n");
        }

        if (ShieldShubReadRegs(SHIELD_LPS22DF_ADDR0, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u) ||
            ShieldShubReadRegs(SHIELD_LPS22DF_ADDR1, SHIELD_GYRO_REG_WHO_AM_I, &who, 1u))
        {
            PRINTF("SHIELD_SHUB probe LPS22DF who=0x%02x %s\r\n",
                   (unsigned int)who,
                   (who == SHIELD_LPS22DF_WHOAMI) ? "ok" : "unexpected");
        }
        else
        {
            PRINTF("SHIELD_SHUB probe LPS22DF not_found\r\n");
        }

        for (uint32_t i = 0u; i < (sizeof(stts_addrs) / sizeof(stts_addrs[0])); i++)
        {
            if (ShieldShubReadRegs(stts_addrs[i], SHIELD_STTS22H_REG_WHO_AM_I, &who, 1u))
            {
                PRINTF("SHIELD_SHUB probe STTS22H addr=0x%02x who=0x%02x %s\r\n",
                       (unsigned int)stts_addrs[i],
                       (unsigned int)who,
                       (who == SHIELD_STTS22H_WHOAMI) ? "ok" : "candidate");
                stts_found = true;
                break;
            }
        }
        if (!stts_found)
        {
            PRINTF("SHIELD_SHUB probe STTS22H not_found\r\n");
        }
    }
    else if (s_shield_gyro_ready)
    {
        PRINTF("SHIELD_SHUB probe skipped: unsupported imu who=0x%02x\r\n", (unsigned int)s_shield_gyro_who);
    }
    else
    {
        PRINTF("SHIELD_SHUB probe skipped: gyro_not_ready\r\n");
    }
#endif
}

#if EDGEAI_SENSOR_SCAN_MODE
static int SensorScanModeMain(void)
{
    uint32_t core_hz;

    BOARD_InitHardware();
    core_hz = CLOCK_GetCoreSysClkFreq();
    if (core_hz == 0u)
    {
        core_hz = CoreClockHz();
    }

    PRINTF("SENSOR_SCAN_MODE active\r\n");
    PRINTF("Tip: remove LCD, keep shield attached, then reboot this scan image.\r\n");

    for (;;)
    {
        ShieldRunDatastreamDiagnostics();
        ShieldSensorScanLog();
        SDK_DelayAtLeastUs(2000000u, core_hz);
    }

    return 0;
}
#endif

static void TouchConfigIntPin(gt911_int_pin_mode_t mode)
{
    CLOCK_EnableClock(kCLOCK_Port4);

    port_pin_config_t cfg = {
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
            cfg.pullSelect = kPORT_PullUp;
            break;
        case kGT911_IntPinPullDown:
            cfg.pullSelect = kPORT_PullDown;
            break;
        case kGT911_IntPinInput:
            cfg.pullSelect = kPORT_PullDisable;
            break;
        default:
            break;
    }

    PORT_SetPinConfig(TOUCH_INT_PORT, TOUCH_INT_PIN, &cfg);
}

static void TouchConfigResetPin(bool pullUp)
{
    (void)pullUp;
}

static void TouchInit(void)
{
    gt911_config_t touch_cfg = {
        .I2C_SendFunc = TouchI2CSend,
        .I2C_ReceiveFunc = TouchI2CReceive,
        .timeDelayMsFunc = TouchDelayMs,
        .intPinFunc = TouchConfigIntPin,
        .pullResetPinFunc = TouchConfigResetPin,
        .touchPointNum = TOUCH_POINTS,
        .i2cAddrMode = kGT911_I2cAddrMode1,
        .intTrigMode = kGT911_IntFallingEdge,
    };
    status_t st;

    s_touch_ready = false;
    s_touch_was_down = false;
    s_touch_recover_backoff = 0u;

    if (!TouchI2CInit())
    {
        return;
    }

    st = GT911_Init(&s_touch_handle, &touch_cfg);
    if (st != kStatus_Success)
    {
        /* Fallback: some panels come up strapped to 0x5D. */
        touch_cfg.i2cAddrMode = kGT911_I2cAddrMode0;
        st = GT911_Init(&s_touch_handle, &touch_cfg);
    }
    if (st == kStatus_Success)
    {
        s_touch_ready = true;
        PRINTF("TOUCH ready: GT911 (%u x %u)\r\n",
               (unsigned int)s_touch_handle.resolutionX,
               (unsigned int)s_touch_handle.resolutionY);
    }
    else
    {
        PRINTF("TOUCH init failed: GT911 status=%d\r\n", (int)st);
    }
}

static void __attribute__((unused)) AccelInit(void)
{
    static const uint8_t addrs[2] = {ACCEL4_CLICK_I2C_ADDR0, ACCEL4_CLICK_I2C_ADDR1};
    uint8_t who = 0u;

    s_accel_ready = false;
    s_accel_dev.addr7 = 0u;
    s_accel_dev.write = AccelI2CWrite;
    s_accel_dev.read = AccelI2CRead;

    if (!AccelI2CInit())
    {
        GaugeRender_SetAccel(0, 0, 1000, false);
        return;
    }

    for (uint32_t i = 0u; i < 2u; i++)
    {
        s_accel_dev.addr7 = addrs[i];
        if (fxls8974_read_whoami(&s_accel_dev, &who) && (who == FXLS8974_WHO_AM_I_VALUE))
        {
            s_accel_ready = true;
            break;
        }
    }

    if (!s_accel_ready)
    {
        PRINTF("ACCEL not found (WHO_AM_I=0x%02x)\r\n", (unsigned int)who);
        GaugeRender_SetAccel(0, 0, 1000, false);
        return;
    }

    (void)fxls8974_set_active(&s_accel_dev, false);
    (void)fxls8974_set_fsr(&s_accel_dev, FXLS8974_FSR_4G);
    (void)fxls8974_set_active(&s_accel_dev, true);
    PRINTF("ACCEL ready addr=0x%02x\r\n", (unsigned int)s_accel_dev.addr7);
}

static void __attribute__((unused)) AccelUpdate(void)
{
    fxls8974_sample_t raw;
    int32_t x_mg;
    int32_t y_mg;
    int32_t z_mg;
    int16_t filt_x;
    int16_t filt_y;
    int16_t filt_z;

    if (!s_accel_ready)
    {
        return;
    }

    if (!fxls8974_read_sample_12b(&s_accel_dev, &raw))
    {
        return;
    }

    /* FXLS8974 raw is 12-bit signed. For +/-4g, 1 LSB ~= 1.953 mg. */
    x_mg = ((int32_t)raw.x * 125) / 64;
    y_mg = ((int32_t)raw.y * 125) / 64;
    z_mg = ((int32_t)raw.z * 125) / 64;

    /* Simple low-pass to keep the gyro view stable. */
    filt_x = (int16_t)((s_accel_x_mg * 3 + x_mg) / 4);
    filt_y = (int16_t)((s_accel_y_mg * 3 + y_mg) / 4);
    filt_z = (int16_t)((s_accel_z_mg * 3 + z_mg) / 4);

    /* Requested mapping change: swap X and Y axes globally. */
    s_accel_x_mg = filt_y;
    s_accel_y_mg = filt_x;
    s_accel_z_mg = filt_z;
}

static void ShieldGyroInit(void)
{
    static const bool buses[2] = {true, false};
    static const char *bus_name[2] = {"FC2", "FC3"};
    static const uint8_t addrs[2] = {SHIELD_GYRO_ADDR0, SHIELD_GYRO_ADDR1};
    uint8_t who = 0u;

    s_shield_gyro_ready = false;
    s_shield_gyro_addr = 0u;
    s_shield_gyro_who = 0u;
    s_shield_use_touch_bus = true;
    s_ui_gyro_x = 0;
    s_ui_gyro_y = 0;
    s_ui_gyro_z = 0;

    for (uint32_t bi = 0u; bi < 2u; bi++)
    {
        bool use_touch_bus = buses[bi];
        for (uint32_t i = 0u; i < 2u; i++)
        {
            if (!ShieldBusRead(use_touch_bus, addrs[i], SHIELD_GYRO_REG_WHO_AM_I, &who, 1u))
            {
                continue;
            }
            if ((who == SHIELD_IMU_WHOAMI_LSM6DSO16IS) || (who == SHIELD_IMU_WHOAMI_LSM6DSV16X))
            {
                s_shield_gyro_ready = true;
                s_shield_gyro_addr = addrs[i];
                s_shield_gyro_who = who;
                s_shield_use_touch_bus = use_touch_bus;
                PRINTF("SHIELD_GYRO bus=%s\r\n", bus_name[bi]);
                break;
            }
        }
        if (s_shield_gyro_ready)
        {
            break;
        }
    }
    if (!s_shield_gyro_ready)
    {
        if (!s_shield_gyro_missing_logged)
        {
            PRINTF("SHIELD_GYRO not found (last WHO_AM_I=0x%02x)\r\n", (unsigned int)who);
            s_shield_gyro_missing_logged = true;
        }
        return;
    }
    s_shield_gyro_missing_logged = false;
    s_shield_gyro_read_fail_logged = false;
    s_shield_gyro_read_fail_streak = 0u;

    /* LSM6-family setup: BDU + auto-increment, accel ODR=104Hz FS=4g, gyro ODR=104Hz FS=2000 dps. */
    if (!ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_CTRL3_C, 0x44u) ||
        !ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_CTRL1_XL, 0x48u) ||
        !ShieldBusWriteReg(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_CTRL2_G, 0x4Cu))
    {
        s_shield_gyro_ready = false;
        PRINTF("SHIELD_GYRO cfg failed addr=0x%02x\r\n", (unsigned int)s_shield_gyro_addr);
        return;
    }
    PRINTF("SHIELD_GYRO ready addr=0x%02x who=0x%02x (%s)\r\n",
           (unsigned int)s_shield_gyro_addr,
           (unsigned int)s_shield_gyro_who,
           ShieldImuName(s_shield_gyro_who));
}

static void ShieldGyroUpdate(void)
{
    uint8_t raw_g[6];
    uint8_t raw_a[6];
    int16_t ax_raw;
    int16_t ay_raw;
    int16_t az_raw;
    int32_t accel_mg_per_lsb_x1000;
    int32_t ax_mg;
    int32_t ay_mg;
    int32_t az_mg;
    int16_t filt_ax;
    int16_t filt_ay;
    int16_t filt_az;

    if (!s_shield_gyro_ready)
    {
        ShieldGyroInit();
        if (!s_shield_gyro_ready)
        {
            GaugeRender_SetAccel(0, 0, 1000, false);
            GaugeRender_SetLinearAccel(0, 0, 1000, false);
            return;
        }
    }

    if (!s_shield_gyro_ready)
    {
        GaugeRender_SetAccel(0, 0, 1000, false);
        GaugeRender_SetLinearAccel(0, 0, 1000, false);
        return;
    }

    /* Keep gyro read in path, but do not fail accel update if it errors. */
    if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_OUTX_L_G, raw_g, sizeof(raw_g)))
    {
        if (!s_shield_gyro_read_fail_logged)
        {
            PRINTF("SHIELD_GYRO read fail (gyro) addr=0x%02x\r\n", (unsigned int)s_shield_gyro_addr);
            s_shield_gyro_read_fail_logged = true;
        }
    }

    if (!ShieldBusRead(s_shield_use_touch_bus, s_shield_gyro_addr, SHIELD_GYRO_REG_OUTX_L_A, raw_a, sizeof(raw_a)))
    {
        if (s_shield_gyro_read_fail_streak < 255u)
        {
            s_shield_gyro_read_fail_streak++;
        }
        if (s_shield_gyro_read_fail_streak >= 5u)
        {
            s_shield_gyro_ready = false;
        }
        if (!s_shield_gyro_read_fail_logged)
        {
            PRINTF("SHIELD_GYRO read fail (accel) addr=0x%02x\r\n", (unsigned int)s_shield_gyro_addr);
            s_shield_gyro_read_fail_logged = true;
        }
        return;
    }
    s_shield_gyro_read_fail_streak = 0u;
    s_shield_gyro_read_fail_logged = false;

    ax_raw = (int16_t)(((uint16_t)raw_a[1] << 8) | raw_a[0]);
    ay_raw = (int16_t)(((uint16_t)raw_a[3] << 8) | raw_a[2]);
    az_raw = (int16_t)(((uint16_t)raw_a[5] << 8) | raw_a[4]);

    /* LSM6DSV16X reads ~2x high with 0.122 mg/LSB on this setup; use 0.061 mg/LSB. */
    accel_mg_per_lsb_x1000 = (s_shield_gyro_who == SHIELD_IMU_WHOAMI_LSM6DSV16X) ? 61 : 122;
    ax_mg = ((int32_t)ax_raw * accel_mg_per_lsb_x1000) / 1000;
    ay_mg = ((int32_t)ay_raw * accel_mg_per_lsb_x1000) / 1000;
    az_mg = ((int32_t)az_raw * accel_mg_per_lsb_x1000) / 1000;

    /* Stable absolute tilt mapping from accel only (no gyro boost, no axis swap). */
    filt_ax = (int16_t)((s_accel_x_mg * 3 + ax_mg) / 4);
    filt_ay = (int16_t)((s_accel_y_mg * 3 + ay_mg) / 4);
    filt_az = (int16_t)((s_accel_z_mg * 3 + az_mg) / 4);
    s_accel_x_mg = filt_ax;
    s_accel_y_mg = filt_ay;
    s_accel_z_mg = filt_az;

    /* UI orientation mapping: display horizon/sphere use board-rotated axes. */
    s_ui_gyro_x = filt_ay;
    s_ui_gyro_y = filt_ax;
    s_ui_gyro_z = filt_az;
    GaugeRender_SetLinearAccel(s_accel_x_mg, s_accel_y_mg, s_accel_z_mg, true);
    GaugeRender_SetAccel(s_ui_gyro_x, s_ui_gyro_y, s_ui_gyro_z, true);
}

static bool BoardTempReadRaw(uint8_t addr, i3c_bus_type_t bus_type, uint8_t *raw2)
{
    i3c_master_transfer_t xfer;
    memset(&xfer, 0, sizeof(xfer));
    xfer.flags = kI3C_TransferDefaultFlag;
    xfer.slaveAddress = addr;
    xfer.direction = kI3C_Read;
    xfer.subaddress = BOARD_TEMP_REG;
    xfer.subaddressSize = 1u;
    xfer.data = raw2;
    xfer.dataSize = 2u;
    xfer.busType = bus_type;
    xfer.ibiResponse = kI3C_IbiRespAck;
    return (I3C_MasterTransferBlocking(TEMP_I3C, &xfer) == kStatus_Success);
}

static status_t BoardTempAssignDynamicAddress(void)
{
    i3c_master_transfer_t xfer;
    uint8_t ccc;
    uint8_t payload;

    /* RSTDAA to clear stale dynamic addresses. */
    memset(&xfer, 0, sizeof(xfer));
    ccc = I3C_CCC_RSTDAA;
    xfer.slaveAddress = I3C_BROADCAST_ADDR;
    xfer.direction = kI3C_Write;
    xfer.busType = kI3C_TypeI3CSdr;
    xfer.data = &ccc;
    xfer.dataSize = 1u;
    xfer.flags = kI3C_TransferDefaultFlag;
    if (I3C_MasterTransferBlocking(TEMP_I3C, &xfer) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* SETDASA command phase. */
    memset(&xfer, 0, sizeof(xfer));
    ccc = I3C_CCC_SETDASA;
    xfer.slaveAddress = I3C_BROADCAST_ADDR;
    xfer.direction = kI3C_Write;
    xfer.busType = kI3C_TypeI3CSdr;
    xfer.data = &ccc;
    xfer.dataSize = 1u;
    xfer.flags = kI3C_TransferNoStopFlag;
    if (I3C_MasterTransferBlocking(TEMP_I3C, &xfer) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* SETDASA payload phase: assign dynamic address to static 0x48 target. */
    memset(&xfer, 0, sizeof(xfer));
    payload = (uint8_t)(TEMP_SENSOR_DYNAMIC_ADDR << 1);
    xfer.slaveAddress = TEMP_SENSOR_STATIC_ADDR;
    xfer.direction = kI3C_Write;
    xfer.busType = kI3C_TypeI3CSdr;
    xfer.data = &payload;
    xfer.dataSize = 1u;
    xfer.flags = kI3C_TransferDefaultFlag;
    return I3C_MasterTransferBlocking(TEMP_I3C, &xfer);
}

static bool BoardTempDecodeC10(const uint8_t *raw, int32_t *temp_c10_out)
{
    int16_t raw12;
    int32_t temp_c10;

    if ((raw == NULL) || (temp_c10_out == NULL))
    {
        return false;
    }

    raw12 = (int16_t)((((uint16_t)raw[0] << 8) | raw[1]) >> 4);
    if ((raw12 & 0x0800) != 0)
    {
        raw12 |= (int16_t)0xF000;
    }
    /* P3T1755 is 12-bit, 0.0625C/LSB (1/16 C) => 0.625 tenth-C/LSB. */
    temp_c10 = ((int32_t)raw12 * 5) / 8;

    /* Reject clearly invalid values to avoid latching wrong targets. */
    if ((temp_c10 < -400) || (temp_c10 > 1250))
    {
        return false;
    }

    *temp_c10_out = temp_c10;
    return true;
}

static bool BoardTempDecodeC(const uint8_t *raw, int32_t *temp_c_out)
{
    int32_t temp_c10;
    if ((raw == NULL) || (temp_c_out == NULL))
    {
        return false;
    }
    if (!BoardTempDecodeC10(raw, &temp_c10))
    {
        return false;
    }
    *temp_c_out = temp_c10 / 10;
    return true;
}

static bool BoardTempProbeAddr(uint8_t addr, i3c_bus_type_t bus_type, int32_t *temp_c_out)
{
    uint8_t raw_a[2];
    uint8_t raw_b[2];
    int32_t ta;
    int32_t tb;
    int32_t dt;

    if ((temp_c_out == NULL) || !BoardTempReadRaw(addr, bus_type, raw_a) || !BoardTempReadRaw(addr, bus_type, raw_b))
    {
        return false;
    }
    if (!BoardTempDecodeC(raw_a, &ta) || !BoardTempDecodeC(raw_b, &tb))
    {
        return false;
    }

    dt = ta - tb;
    if (dt < 0)
    {
        dt = -dt;
    }
    if (dt > 3)
    {
        return false;
    }

    *temp_c_out = tb;
    return true;
}

static bool BoardTempI3CInit(void)
{
    i3c_master_config_t cfg;
    uint32_t src_hz;

    if (s_temp_i3c_inited)
    {
        return true;
    }

    src_hz = CLOCK_GetI3cClkFreq(TEMP_I3C_INDEX);
    if (src_hz == 0u)
    {
        PRINTF("TEMP i3c init failed: I3C1 clock=0\r\n");
        return false;
    }

    I3C_MasterGetDefaultConfig(&cfg);
    cfg.baudRate_Hz.i2cBaud = 100000u;
    cfg.baudRate_Hz.i3cPushPullBaud = 1000000u;
    cfg.baudRate_Hz.i3cOpenDrainBaud = 125000u;
    cfg.enableOpenDrainStop = false;
    cfg.disableTimeout = true;
    I3C_MasterInit(TEMP_I3C, &cfg, src_hz);
    s_temp_i3c_inited = true;
    return true;
}

static void BoardTempInit(void)
{
    int32_t temp_c;
    int32_t temp_c10;
    uint8_t addr;
    status_t dyn_status;

    s_temp_ready = false;
    if (!BoardTempI3CInit())
    {
        GaugeRender_SetBoardTempC10(s_temp_c10, false);
        return;
    }

    dyn_status = BoardTempAssignDynamicAddress();
    if ((dyn_status == kStatus_Success) &&
        BoardTempProbeAddr(TEMP_SENSOR_DYNAMIC_ADDR, kI3C_TypeI3CSdr, &temp_c))
    {
        uint8_t raw[2] = {0u, 0u};
        uint16_t temp_f = (uint16_t)(((uint16_t)temp_c * 9u) / 5u + 32u);
        s_temp_addr = TEMP_SENSOR_DYNAMIC_ADDR;
        s_temp_bus_type = kI3C_TypeI3CSdr;
        s_temp_c = (uint8_t)temp_c;
        if (BoardTempReadRaw(TEMP_SENSOR_DYNAMIC_ADDR, kI3C_TypeI3CSdr, raw) &&
            BoardTempDecodeC10(raw, &temp_c10))
        {
            s_temp_c10 = (int16_t)temp_c10;
        }
        else
        {
            s_temp_c10 = (int16_t)s_temp_c * 10;
        }
        s_temp_ready = true;
        if (BoardTempReadRaw(TEMP_SENSOR_DYNAMIC_ADDR, kI3C_TypeI3CSdr, raw))
        {
            PRINTF("TEMP init raw=0x%02x 0x%02x -> %dC/%uF\r\n",
                   (unsigned int)raw[0],
                   (unsigned int)raw[1],
                   (int)s_temp_c,
                   (unsigned int)temp_f);
        }
        PRINTF("TEMP ready dyn=0x%02x bus=i3c T=%dC\r\n", (unsigned int)s_temp_addr, (int)s_temp_c);
    }

    /* Fallback to legacy I2C mode if dynamic mapping fails. */
    if (!s_temp_ready)
    {
        s_temp_bus_type = kI3C_TypeI2C;
        for (addr = 0x48u; addr <= 0x4Bu; addr++)
        {
            PRINTF("TEMP legacy probe addr=0x%02x\r\n", (unsigned int)addr);
            if (BoardTempProbeAddr(addr, kI3C_TypeI2C, &temp_c))
            {
                s_temp_addr = addr;
                s_temp_c = (uint8_t)temp_c;
                s_temp_c10 = (int16_t)s_temp_c * 10;
                s_temp_ready = true;
                break;
            }
        }
    }

    if (!s_temp_ready)
    {
        PRINTF("TEMP sensor not found on I3C1 legacy targets\r\n");
    }
    else
    {
        PRINTF("TEMP ready addr=0x%02x bus=%s T=%dC\r\n",
               (unsigned int)s_temp_addr,
               (s_temp_bus_type == kI3C_TypeI3CSdr) ? "i3c" : "i2c",
               (int)s_temp_c);
    }
    GaugeRender_SetBoardTempC10(s_temp_c10, s_temp_ready);
}

static void BoardTempUpdate(void)
{
    uint8_t raw[2];
    int32_t temp_c;
    int32_t temp_c10;

    if (!s_temp_ready)
    {
        GaugeRender_SetBoardTempC10(s_temp_c10, false);
        return;
    }
    if (!BoardTempReadRaw(s_temp_addr, s_temp_bus_type, raw))
    {
        GaugeRender_SetBoardTempC10(s_temp_c10, false);
        return;
    }
    if (!BoardTempDecodeC(raw, &temp_c) || !BoardTempDecodeC10(raw, &temp_c10))
    {
        GaugeRender_SetBoardTempC10(s_temp_c10, false);
        return;
    }
    if (temp_c < 0)
    {
        temp_c = 0;
    }
    if (temp_c > 99)
    {
        temp_c = 99;
    }
    s_temp_c = (uint8_t)temp_c;
    s_temp_c10 = (int16_t)temp_c10;
    GaugeRender_SetBoardTempC10(s_temp_c10, true);
}

static const power_sample_t *GetFrameSample(void)
{
    const power_sample_t *src = PowerData_Get();
    if (src == NULL)
    {
        return NULL;
    }
    s_frame_sample = *src;
    s_frame_sample.temp_c = s_temp_c;
    ApplyAnomalyToFrame(&s_frame_sample);
    return &s_frame_sample;
}

static bool TouchGetPoint(int32_t *x_out, int32_t *y_out)
{
    touch_point_t points[TOUCH_POINTS];
    uint8_t point_count = TOUCH_POINTS;
    const touch_point_t *selected = NULL;
    int32_t x;
    int32_t y;
    int32_t res_x;
    status_t st = kStatus_Fail;

    if ((x_out == NULL) || (y_out == NULL))
    {
        return false;
    }

    if (!s_touch_ready)
    {
        if (++s_touch_recover_backoff >= 200u)
        {
            s_touch_recover_backoff = 0u;
            TouchInit();
        }
        return false;
    }

    for (uint32_t attempt = 0u; attempt < 6u; attempt++)
    {
        point_count = TOUCH_POINTS;
        st = GT911_GetMultiTouch(&s_touch_handle, &point_count, points);
        if (st == kStatus_Success)
        {
            break;
        }
        if (st != kStatus_TOUCHPANEL_NotReady)
        {
            break;
        }
        SDK_DelayAtLeastUs(800u, CoreClockHz());
    }
    if (st != kStatus_Success)
    {
        if (++s_touch_recover_backoff >= 20u)
        {
            s_touch_recover_backoff = 0u;
            (void)TouchI2CRecover();
            TouchInit();
        }
        return false;
    }
    s_touch_recover_backoff = 0u;

    for (uint8_t i = 0u; i < point_count; i++)
    {
        if (points[i].valid && (points[i].touchID == 0u))
        {
            selected = &points[i];
            break;
        }
    }

    if (selected == NULL)
    {
        for (uint8_t i = 0u; i < point_count; i++)
        {
            if (points[i].valid)
            {
                selected = &points[i];
                break;
            }
        }
    }

    if (selected == NULL)
    {
        return false;
    }

    res_x = (s_touch_handle.resolutionX > 0u) ? (int32_t)s_touch_handle.resolutionX : 480;
    x = (int32_t)selected->y;
    y = res_x - (int32_t)selected->x;

    if (x < 0) x = 0;
    if (x > 479) x = 479;
    if (y < 0) y = 0;
    if (y > 319) y = 319;

    *x_out = x;
    *y_out = y;
    return true;
}

static bool TouchInAiPill(int32_t x, int32_t y)
{
    return (x >= GAUGE_RENDER_AI_PILL_X0) && (x <= GAUGE_RENDER_AI_PILL_X1) &&
           (y >= GAUGE_RENDER_AI_PILL_Y0) && (y <= GAUGE_RENDER_AI_PILL_Y1);
}

static bool TouchInAiSet(int32_t x, int32_t y)
{
    return (x >= GAUGE_RENDER_AI_SET_X0) && (x <= GAUGE_RENDER_AI_SET_X1) &&
           (y >= GAUGE_RENDER_AI_SET_Y0) && (y <= GAUGE_RENDER_AI_SET_Y1);
}

static bool TouchInAiHelp(int32_t x, int32_t y)
{
    return (x >= GAUGE_RENDER_AI_HELP_X0) && (x <= GAUGE_RENDER_AI_HELP_X1) &&
           (y >= GAUGE_RENDER_AI_HELP_Y0) && (y <= GAUGE_RENDER_AI_HELP_Y1);
}

static bool TouchInSettingsPanel(int32_t x, int32_t y)
{
    return (x >= GAUGE_RENDER_SET_PANEL_X0) && (x <= GAUGE_RENDER_SET_PANEL_X1) &&
           (y >= GAUGE_RENDER_SET_PANEL_Y0) && (y <= GAUGE_RENDER_SET_PANEL_Y1);
}

static bool TouchInHelpPanel(int32_t x, int32_t y)
{
    return (x >= GAUGE_RENDER_HELP_PANEL_X0) && (x <= GAUGE_RENDER_HELP_PANEL_X1) &&
           (y >= GAUGE_RENDER_HELP_PANEL_Y0) && (y <= GAUGE_RENDER_HELP_PANEL_Y1);
}

static bool TouchInSettingsClose(int32_t x, int32_t y)
{
    int32_t bx1 = GAUGE_RENDER_SET_PANEL_X1 - 8;
    int32_t bx0 = bx1 - 22;
    int32_t by0 = GAUGE_RENDER_SET_PANEL_Y0 + 8;
    int32_t by1 = by0 + 22;
    return (x >= bx0) && (x <= bx1) && (y >= by0) && (y <= by1);
}

static bool TouchInHelpClose(int32_t x, int32_t y)
{
    int32_t bx1 = GAUGE_RENDER_HELP_PANEL_X1 - 8;
    int32_t bx0 = bx1 - 22;
    int32_t by0 = GAUGE_RENDER_HELP_PANEL_Y0 + 8;
    int32_t by1 = by0 + 22;
    return (x >= bx0) && (x <= bx1) && (y >= by0) && (y <= by1);
}

static bool TouchInSettingsModeIndex(int32_t x, int32_t y, uint8_t idx)
{
    int32_t x0 = GAUGE_RENDER_SET_MODE_X0 + (int32_t)idx * (GAUGE_RENDER_SET_MODE_W + GAUGE_RENDER_SET_MODE_GAP);
    int32_t x1 = x0 + GAUGE_RENDER_SET_MODE_W - 1;
    int32_t y0 = GAUGE_RENDER_SET_MODE_Y0;
    int32_t y1 = y0 + GAUGE_RENDER_SET_MODE_H - 1;
    return (x >= x0) && (x <= x1) && (y >= y0) && (y <= y1);
}

static bool TouchInSettingsTuneIndex(int32_t x, int32_t y, uint8_t idx)
{
    int32_t x0 = GAUGE_RENDER_SET_TUNE_X0 + (int32_t)idx * (GAUGE_RENDER_SET_TUNE_W + GAUGE_RENDER_SET_TUNE_GAP);
    int32_t x1 = x0 + GAUGE_RENDER_SET_TUNE_W - 1;
    int32_t y0 = GAUGE_RENDER_SET_TUNE_Y0;
    int32_t y1 = y0 + GAUGE_RENDER_SET_TUNE_H - 1;
    return (x >= x0) && (x <= x1) && (y >= y0) && (y <= y1);
}

static bool TouchInSettingsAiIndex(int32_t x, int32_t y, uint8_t idx)
{
    int32_t x0 = GAUGE_RENDER_SET_AI_X0 + (int32_t)idx * (GAUGE_RENDER_SET_AI_W + GAUGE_RENDER_SET_AI_GAP);
    int32_t x1 = x0 + GAUGE_RENDER_SET_AI_W - 1;
    int32_t y0 = GAUGE_RENDER_SET_AI_Y0;
    int32_t y1 = y0 + GAUGE_RENDER_SET_AI_H - 1;
    return (x >= x0) && (x <= x1) && (y >= y0) && (y <= y1);
}

int main(void)
{
#if EDGEAI_SENSOR_SCAN_MODE
    return SensorScanModeMain();
#else
    bool ai_enabled = true;
    bool lcd_ok;
    bool ext_flash_ok;
    bool help_visible = false;
    bool settings_visible = false;
    bool ui_block_touch = false;
    bool record_mode;
    bool prev_record_mode;
    bool playback_active = false;
    ext_flash_sample_t playback_sample;
    uint32_t data_tick_accum_us = 0u;
    uint32_t recplay_tick_accum_us = 0u;
    uint32_t render_tick_accum_us = 0u;
    uint32_t gyro_tick_accum_us = 0u;
    uint32_t accel_live_tick_accum_us = 0u;
    uint32_t runtime_clock_tick_accum_us = 0u;
    uint32_t temp_tick_accum_us = 0u;
    uint32_t shield_aux_tick_accum_us = 0u;
    uint32_t accel_test_tick_accum_us = 0u;
    uint32_t runtime_elapsed_ds = 0u;
    uint32_t runtime_displayed_sec = UINT32_MAX;
    uint32_t rec_elapsed_ds = 0u;
    uint32_t play_off = 0u;
    uint32_t play_cnt = 0u;
    uint32_t rec_cnt = 0u;
    const power_sample_t *sample;
    anomaly_mode_t anom_mode;
    uint64_t time_prev_ticks = 0u;
    uint64_t time_us_rem = 0u;
    uint64_t runtime_clock_start_ticks = 0u;

    BOARD_InitHardware();
    ext_flash_ok = ExtFlashRecorder_Init();
    PRINTF("EXT_FLASH_REC: %s\r\n", ext_flash_ok ? "ready" : "init_failed");

    lcd_ok = GaugeRender_Init();
    PRINTF("EV dash LCD: %s\r\n", lcd_ok ? "ready" : "init_failed");

    PowerData_Init();
    PowerData_SetAiAssistEnabled(ai_enabled);
    AnomalyEngine_Init();
    anom_mode = AnomalyEngine_GetMode();
    ShieldGyroInit();
    ShieldRunDatastreamDiagnostics();
    ShieldSensorScanLog();
    TouchInit();
    BoardTempInit();
    BoardTempUpdate();
    ShieldGyroUpdate();
    ShieldAuxInit();
    (void)TimebaseInit();
    time_prev_ticks = TimebaseNowTicks();
    runtime_clock_start_ticks = time_prev_ticks;
    GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
    GaugeRender_SetHelpVisible(false);
    GaugeRender_SetSettingsVisible(false);
    GaugeRender_SetLiveBannerMode(true);
    GaugeRender_SetRecordMode(false);
    memset(&s_anom_out, 0, sizeof(s_anom_out));
    AnomalyEngine_GetOutput(&s_anom_out);
    GaugeRender_SetAnomalyInfo((uint8_t)s_anom_out.mode,
                               (uint8_t)s_anom_out.tune,
                               s_anom_out.training_active,
                               s_anom_out.trained_ready,
                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AX],
                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AY],
                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AZ],
                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_TEMP],
                               (uint8_t)s_anom_out.overall_level);
    sample = GetFrameSample();
    if (lcd_ok && (sample != NULL))
    {
        GaugeRender_DrawFrame(sample, ai_enabled, PowerData_GetReplayProfile());
    }
    prev_record_mode = GaugeRender_IsRecordMode();
    if (!prev_record_mode && !GaugeRender_IsLiveBannerMode())
    {
        playback_active = ext_flash_ok && ExtFlashRecorder_StartPlayback();
        runtime_elapsed_ds = 0u;
        runtime_displayed_sec = UINT32_MAX;
        runtime_clock_start_ticks = TimebaseNowTicks();
        GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
        PRINTF("EXT_FLASH_PLAY: %s\r\n", playback_active ? "ready" : "no_data");
        if (playback_active && ExtFlashRecorder_GetPlaybackInfo(&play_off, &play_cnt))
        {
            PRINTF("EXT_FLASH_PLAY_INFO: offset=%u count=%u\r\n", (unsigned int)play_off, (unsigned int)play_cnt);
        }
    }

    PRINTF("EV dash app ready\r\n");

    for (;;)
    {
        int32_t tx = 0;
        int32_t ty = 0;
        bool modal_active;
        bool modal_active_now;
        bool pressed = TouchGetPoint(&tx, &ty);
        bool in_pill;
        bool in_set;
        bool in_help;
        bool timeline_changed = GaugeRender_HandleTouch(tx, ty, pressed);
        bool record_start_request;

        modal_active = GaugeRender_IsRecordConfirmActive();
        in_set = pressed && !modal_active && TouchInAiSet(tx, ty);
        in_help = pressed && !modal_active && TouchInAiHelp(tx, ty);
        in_pill = pressed && !modal_active && TouchInAiPill(tx, ty) && !in_set && !in_help;

        if (ui_block_touch)
        {
            if (!pressed)
            {
                ui_block_touch = false;
            }
            in_set = false;
            in_help = false;
            in_pill = false;
        }

        if (pressed && !s_touch_was_down && !modal_active && !ui_block_touch)
        {
            bool redraw_ui = false;

            if (help_visible)
            {
                if (TouchInHelpClose(tx, ty) || in_help)
                {
                    help_visible = false;
                    GaugeRender_SetHelpVisible(false);
                    redraw_ui = true;
                }
                else if (!TouchInHelpPanel(tx, ty))
                {
                    help_visible = false;
                    GaugeRender_SetHelpVisible(false);
                    redraw_ui = true;
                }
            }
            else if (settings_visible)
            {
                bool handled_setting = false;

                if (TouchInSettingsClose(tx, ty))
                {
                    settings_visible = false;
                    GaugeRender_SetSettingsVisible(false);
                    redraw_ui = true;
                    handled_setting = true;
                }

                for (uint8_t i = 0u; i < 3u; i++)
                {
                    if (!handled_setting && TouchInSettingsModeIndex(tx, ty, i))
                    {
                        anom_mode = (anomaly_mode_t)i;
                        AnomalyEngine_SetMode(anom_mode);
                        GaugeRender_SetLiveBannerMode(false);
                        if (anom_mode == ANOMALY_MODE_TRAINED_MONITOR)
                        {
                            AnomalyEngine_StartTraining();
                        }
                        handled_setting = true;
                        redraw_ui = true;
                        PRINTF("ANOM_MODE,%u\r\n", (unsigned int)anom_mode);
                        break;
                    }
                }

                if (!handled_setting)
                {
                    for (uint8_t i = 0u; i < 3u; i++)
                    {
                        if (TouchInSettingsTuneIndex(tx, ty, i))
                        {
                            AnomalyEngine_SetTune((anomaly_tune_t)i);
                            handled_setting = true;
                            redraw_ui = true;
                            PRINTF("ANOM_TUNE,%u\r\n", (unsigned int)i);
                            break;
                        }
                    }
                }

                if (!handled_setting)
                {
                    if (TouchInSettingsAiIndex(tx, ty, 0u))
                    {
                        anom_mode = ANOMALY_MODE_TRAINED_MONITOR;
                        AnomalyEngine_SetMode(anom_mode);
                        GaugeRender_SetLiveBannerMode(false);
                        GaugeRender_SetRecordMode(true);
                        playback_active = false;
                        AnomalyEngine_StartTraining();
                        settings_visible = false;
                        GaugeRender_SetSettingsVisible(false);
                        handled_setting = true;
                        redraw_ui = true;
                        PRINTF("AI_MODE,TRAIN\r\n");
                    }
                    else if (TouchInSettingsAiIndex(tx, ty, 1u))
                    {
                        anom_mode = ANOMALY_MODE_TRAINED_MONITOR;
                        AnomalyEngine_SetMode(anom_mode);
                        GaugeRender_SetLiveBannerMode(true);
                        GaugeRender_SetRecordMode(false);
                        playback_active = false;
                        AnomalyEngine_StopTraining();
                        settings_visible = false;
                        GaugeRender_SetSettingsVisible(false);
                        handled_setting = true;
                        redraw_ui = true;
                        PRINTF("AI_MODE,LIVE\r\n");
                    }
                }

                if (!handled_setting)
                {
                    if (in_set || !TouchInSettingsPanel(tx, ty))
                    {
                        settings_visible = false;
                        GaugeRender_SetSettingsVisible(false);
                        redraw_ui = true;
                    }
                }

                if (redraw_ui)
                {
                    AnomalyEngine_GetOutput(&s_anom_out);
                    GaugeRender_SetAnomalyInfo((uint8_t)s_anom_out.mode,
                                               (uint8_t)s_anom_out.tune,
                                               s_anom_out.training_active,
                                               s_anom_out.trained_ready,
                                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AX],
                                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AY],
                                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AZ],
                                               (uint8_t)s_anom_out.channel_level[ANOMALY_CH_TEMP],
                                               (uint8_t)s_anom_out.overall_level);
                    if (lcd_ok)
                    {
                        GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
                    }
                }
            }
            else if (in_set)
            {
                settings_visible = true;
                help_visible = false;
                GaugeRender_SetHelpVisible(false);
                GaugeRender_SetSettingsVisible(true);
                redraw_ui = true;
            }
            else if (in_help)
            {
                help_visible = true;
                settings_visible = false;
                GaugeRender_SetSettingsVisible(false);
                GaugeRender_SetHelpVisible(true);
                redraw_ui = true;
                PRINTF("UI_HELP,ON\r\n");
            }

            if (redraw_ui && lcd_ok)
            {
                GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
            }
        }

        if (in_pill && !s_touch_was_down)
        {
            ai_enabled = !ai_enabled;
            PowerData_SetAiAssistEnabled(ai_enabled);
            PRINTF("AI_TOGGLE,%s\r\n", ai_enabled ? "ON" : "OFF");
            if (lcd_ok)
            {
                GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
            }
        }
        if (timeline_changed && lcd_ok)
        {
            GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
        }
        if (timeline_changed && !GaugeRender_IsRecordMode() && !GaugeRender_IsRecordConfirmActive() &&
            !GaugeRender_IsLiveBannerMode())
        {
            playback_active = ext_flash_ok && ExtFlashRecorder_StartPlayback();
            runtime_elapsed_ds = 0u;
            runtime_displayed_sec = UINT32_MAX;
            runtime_clock_start_ticks = TimebaseNowTicks();
            GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
            PRINTF("EXT_FLASH_PLAY: %s\r\n", playback_active ? "restart" : "no_data");
            if (playback_active && ExtFlashRecorder_GetPlaybackInfo(&play_off, &play_cnt))
            {
                PRINTF("EXT_FLASH_PLAY_INFO: offset=%u count=%u\r\n", (unsigned int)play_off, (unsigned int)play_cnt);
            }
        }
        record_start_request = GaugeRender_ConsumeRecordStartRequest();
        if (record_start_request)
        {
            bool cleared = ext_flash_ok && ExtFlashRecorder_ClearAll();
            if (cleared)
            {
                GaugeRender_SetRecordMode(true);
                playback_active = false;
                runtime_elapsed_ds = 0u;
                rec_elapsed_ds = 0u;
                runtime_displayed_sec = UINT32_MAX;
                runtime_clock_start_ticks = TimebaseNowTicks();
                GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
                if (anom_mode == ANOMALY_MODE_TRAINED_MONITOR)
                {
                    AnomalyEngine_StartTraining();
                }
                PRINTF("EXT_FLASH_REC: cleared_start\r\n");
                GaugeRender_SetPlayhead(99u, true);
            }
            else
            {
                GaugeRender_SetRecordMode(false);
                playback_active = (!GaugeRender_IsLiveBannerMode()) && ext_flash_ok && ExtFlashRecorder_StartPlayback();
                runtime_elapsed_ds = 0u;
                runtime_displayed_sec = UINT32_MAX;
                runtime_clock_start_ticks = TimebaseNowTicks();
                GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
                PRINTF("EXT_FLASH_REC: clear_failed\r\n");
            }
            if (lcd_ok)
            {
                GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
            }
        }
        s_touch_was_down = pressed;
        modal_active_now = GaugeRender_IsRecordConfirmActive() || help_visible || settings_visible;
        record_mode = GaugeRender_IsRecordMode();
        if (GaugeRender_IsLiveBannerMode())
        {
            playback_active = false;
        }
        if (record_mode != prev_record_mode)
        {
            if (!record_mode)
            {
                if (anom_mode == ANOMALY_MODE_TRAINED_MONITOR)
                {
                    AnomalyEngine_StopTraining();
                }
                playback_active = (!GaugeRender_IsLiveBannerMode()) && ext_flash_ok && ExtFlashRecorder_StartPlayback();
                runtime_elapsed_ds = 0u;
                runtime_displayed_sec = UINT32_MAX;
                runtime_clock_start_ticks = TimebaseNowTicks();
                GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
                PRINTF("EXT_FLASH_PLAY: %s\r\n", playback_active ? "ready" : "no_data");
                if (playback_active && ExtFlashRecorder_GetPlaybackInfo(&play_off, &play_cnt))
                {
                    PRINTF("EXT_FLASH_PLAY_INFO: offset=%u count=%u\r\n", (unsigned int)play_off, (unsigned int)play_cnt);
                }
            }
            else
            {
                if (anom_mode == ANOMALY_MODE_TRAINED_MONITOR)
                {
                    AnomalyEngine_StartTraining();
                }
                playback_active = false;
                runtime_elapsed_ds = 0u;
                rec_elapsed_ds = 0u;
                runtime_displayed_sec = UINT32_MAX;
                runtime_clock_start_ticks = TimebaseNowTicks();
                GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true);
                PRINTF("EXT_FLASH_REC: active\r\n");
                if (ext_flash_ok && ExtFlashRecorder_GetRecordInfo(&rec_cnt))
                {
                    PRINTF("EXT_FLASH_REC_INFO: count=%u\r\n", (unsigned int)rec_cnt);
                }
                GaugeRender_SetPlayhead(99u, true);
            }
            prev_record_mode = record_mode;
        }

        {
            uint32_t elapsed_loop_us;
            if (s_timebase_ready)
            {
                uint64_t now_ticks = TimebaseNowTicks();
                uint64_t dt_ticks = now_ticks - time_prev_ticks;
                uint64_t us_num = (dt_ticks * 1000000ull) + time_us_rem;
                time_prev_ticks = now_ticks;
                elapsed_loop_us = (uint32_t)(us_num / s_timebase_hz);
                time_us_rem = us_num % s_timebase_hz;
            }
            else
            {
                elapsed_loop_us = TOUCH_POLL_DELAY_US;
            }

            if (elapsed_loop_us == 0u)
            {
                elapsed_loop_us = TOUCH_POLL_DELAY_US;
            }
            if (elapsed_loop_us > 250000u)
            {
                elapsed_loop_us = 250000u;
            }

            runtime_clock_tick_accum_us += elapsed_loop_us;
            data_tick_accum_us += elapsed_loop_us;
            recplay_tick_accum_us += elapsed_loop_us;
            render_tick_accum_us += elapsed_loop_us;
            gyro_tick_accum_us += elapsed_loop_us;
            accel_live_tick_accum_us += elapsed_loop_us;
            temp_tick_accum_us += elapsed_loop_us;
            shield_aux_tick_accum_us += elapsed_loop_us;
            accel_test_tick_accum_us += elapsed_loop_us;

            if (data_tick_accum_us > (POWER_TICK_PERIOD_US * 2u))
            {
                data_tick_accum_us = POWER_TICK_PERIOD_US * 2u;
            }
            if (recplay_tick_accum_us > (RECPLAY_TICK_PERIOD_US * 2u))
            {
                recplay_tick_accum_us = RECPLAY_TICK_PERIOD_US * 2u;
            }
            if (render_tick_accum_us > (DISPLAY_REFRESH_PERIOD_US * 2u))
            {
                render_tick_accum_us = DISPLAY_REFRESH_PERIOD_US * 2u;
            }
            if (temp_tick_accum_us > (TEMP_REFRESH_PERIOD_US * 2u))
            {
                temp_tick_accum_us = TEMP_REFRESH_PERIOD_US * 2u;
            }
            if (shield_aux_tick_accum_us > (SHIELD_AUX_POLL_PERIOD_US * 2u))
            {
                shield_aux_tick_accum_us = SHIELD_AUX_POLL_PERIOD_US * 2u;
            }
            if (accel_test_tick_accum_us > (ACCEL_TEST_LOG_PERIOD_US * 2u))
            {
                accel_test_tick_accum_us = ACCEL_TEST_LOG_PERIOD_US * 2u;
            }
        }

        while (gyro_tick_accum_us >= GYRO_REFRESH_PERIOD_US)
        {
            gyro_tick_accum_us -= GYRO_REFRESH_PERIOD_US;
            if (lcd_ok)
            {
                ShieldGyroUpdate();
                if (!modal_active_now)
                {
                    GaugeRender_DrawGyroFast();
                }
            }
        }

        while (accel_live_tick_accum_us >= ACCEL_LIVE_PERIOD_US)
        {
            accel_live_tick_accum_us -= ACCEL_LIVE_PERIOD_US;
            /* Gyro/accel live update now runs in the gyro refresh loop above. */
        }

        while (shield_aux_tick_accum_us >= SHIELD_AUX_POLL_PERIOD_US)
        {
            shield_aux_tick_accum_us -= SHIELD_AUX_POLL_PERIOD_US;
            ShieldAuxUpdate();
        }

        while (runtime_clock_tick_accum_us >= RUNTIME_CLOCK_PERIOD_US)
        {
            runtime_clock_tick_accum_us -= RUNTIME_CLOCK_PERIOD_US;
            if (!record_mode && !playback_active)
            {
                uint32_t elapsed_sec;
                if (s_timebase_ready && (s_timebase_hz != 0u))
                {
                    uint64_t now_ticks = TimebaseNowTicks();
                    uint64_t dt_ticks = (now_ticks >= runtime_clock_start_ticks) ? (now_ticks - runtime_clock_start_ticks) : 0u;
                    elapsed_sec = (uint32_t)(dt_ticks / s_timebase_hz);
                    runtime_elapsed_ds = elapsed_sec * 10u;
                }
                else
                {
                    runtime_elapsed_ds++;
                    elapsed_sec = runtime_elapsed_ds / 10u;
                }

                if (elapsed_sec != runtime_displayed_sec)
                {
                    uint8_t ch, cm, cs, cds;
                    ClockFromDeciseconds(elapsed_sec * 10u, &ch, &cm, &cs, &cds);
                    GaugeRender_SetRuntimeClock(ch, cm, cs, 0u, true);
                    runtime_displayed_sec = elapsed_sec;
                }
            }
        }

        if (data_tick_accum_us >= POWER_TICK_PERIOD_US)
        {
            data_tick_accum_us -= POWER_TICK_PERIOD_US;
            PowerData_Tick();
        }

        if (recplay_tick_accum_us >= RECPLAY_TICK_PERIOD_US)
        {
            recplay_tick_accum_us -= RECPLAY_TICK_PERIOD_US;
            if (ext_flash_ok && record_mode && !GaugeRender_IsLiveBannerMode())
            {
                uint32_t rec_sec;
                if (s_timebase_ready && (s_timebase_hz != 0u))
                {
                    uint64_t now_ticks = TimebaseNowTicks();
                    uint64_t dt_ticks = (now_ticks >= runtime_clock_start_ticks) ? (now_ticks - runtime_clock_start_ticks) : 0u;
                    rec_elapsed_ds = (uint32_t)((dt_ticks * 10ull) / s_timebase_hz);
                }
                else
                {
                    rec_elapsed_ds++;
                }
                rec_sec = rec_elapsed_ds / 10u;

                if (!ExtFlashRecorder_AppendSampleEx(s_accel_x_mg,
                                                     s_accel_y_mg,
                                                     s_accel_z_mg,
                                                     s_ui_gyro_x,
                                                     s_ui_gyro_y,
                                                     s_ui_gyro_z,
                                                     s_temp_c10,
                                                     s_mag_x_mgauss,
                                                     s_mag_y_mgauss,
                                                     s_mag_z_mgauss,
                                                     s_baro_dhpa,
                                                     s_sht_temp_c10,
                                                     s_sht_rh_dpct,
                                                     s_stts_temp_c10,
                                                     rec_elapsed_ds))
                {
                    PRINTF("EXT_FLASH_REC: write_failed\r\n");
                }
                else
                {
                    uint8_t ch, cm, cs, cds;
                    ClockFromDeciseconds(rec_sec * 10u, &ch, &cm, &cs, &cds);
                    GaugeRender_SetRuntimeClock(ch, cm, cs, 0u, true);
                    runtime_displayed_sec = rec_sec;
                    GaugeRender_SetPlayhead(99u, true);
                }
            }
            else if (playback_active)
            {
                if (ExtFlashRecorder_ReadNextSample(&playback_sample))
                {
                    s_accel_x_mg = playback_sample.ax_mg;
                    s_accel_y_mg = playback_sample.ay_mg;
                    s_accel_z_mg = playback_sample.az_mg;
                    GaugeRender_SetLinearAccel(s_accel_x_mg, s_accel_y_mg, s_accel_z_mg, true);
                    GaugeRender_SetAccel(playback_sample.gx_mdps, playback_sample.gy_mdps, playback_sample.gz_mdps, true);
                    s_mag_x_mgauss = playback_sample.mag_x_mgauss;
                    s_mag_y_mgauss = playback_sample.mag_y_mgauss;
                    s_mag_z_mgauss = playback_sample.mag_z_mgauss;
                    s_baro_dhpa = playback_sample.baro_dhpa;
                    s_sht_temp_c10 = playback_sample.sht_temp_c10;
                    s_sht_rh_dpct = playback_sample.sht_rh_dpct;
                    s_stts_temp_c10 = playback_sample.stts_temp_c10;
                    GaugeRender_SetMag(s_mag_x_mgauss, s_mag_y_mgauss, s_mag_z_mgauss, true);
                    GaugeRender_SetBaro(s_baro_dhpa, true);
                    GaugeRender_SetSht(s_sht_temp_c10, s_sht_rh_dpct, true);
                    GaugeRender_SetStts(s_stts_temp_c10, true);
                    s_temp_c10 = playback_sample.temp_c10;
                    s_temp_c = playback_sample.temp_c;
                    s_temp_ready = true;
                    GaugeRender_SetBoardTempC10(s_temp_c10, true);
                    {
                        uint8_t ch, cm, cs, cds;
                        uint32_t play_sec = playback_sample.ts_ds / 10u;
                        ClockFromDeciseconds(play_sec * 10u, &ch, &cm, &cs, &cds);
                        GaugeRender_SetRuntimeClock(ch, cm, cs, 0u, true);
                        runtime_displayed_sec = play_sec;
                    }
                    if (ExtFlashRecorder_GetPlaybackInfo(&play_off, &play_cnt) && (play_cnt > 0u))
                    {
                        uint32_t pos = (play_off * 100u) / play_cnt;
                        if (pos > 99u)
                        {
                            pos = 99u;
                        }
                        GaugeRender_SetPlayhead((uint8_t)pos, true);
                    }
                }
                else
                {
                    playback_active = false;
                    PRINTF("EXT_FLASH_PLAY: read_failed\r\n");
                }
            }

            AnomalyEngine_Update(s_accel_x_mg, s_accel_y_mg, s_accel_z_mg, s_temp_c10);
            AnomalyEngine_GetOutput(&s_anom_out);
            GaugeRender_SetAnomalyInfo((uint8_t)s_anom_out.mode,
                                       (uint8_t)s_anom_out.tune,
                                       s_anom_out.training_active,
                                       s_anom_out.trained_ready,
                                       (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AX],
                                       (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AY],
                                       (uint8_t)s_anom_out.channel_level[ANOMALY_CH_AZ],
                                       (uint8_t)s_anom_out.channel_level[ANOMALY_CH_TEMP],
                                       (uint8_t)s_anom_out.overall_level);
        }

        if (temp_tick_accum_us >= TEMP_REFRESH_PERIOD_US)
        {
            temp_tick_accum_us -= TEMP_REFRESH_PERIOD_US;
            BoardTempUpdate();
        }

        if (accel_test_tick_accum_us >= ACCEL_TEST_LOG_PERIOD_US)
        {
            accel_test_tick_accum_us -= ACCEL_TEST_LOG_PERIOD_US;
            if (s_accel_ready)
            {
                AccelAxisSelfTestLog();
            }
        }

        if (lcd_ok && (render_tick_accum_us >= DISPLAY_REFRESH_PERIOD_US))
        {
            render_tick_accum_us -= DISPLAY_REFRESH_PERIOD_US;
            if (!modal_active_now)
            {
                GaugeRender_DrawFrame(GetFrameSample(), ai_enabled, PowerData_GetReplayProfile());
            }
        }

        DelayUsByTimebase(TOUCH_POLL_DELAY_US);
    }
#endif
}
