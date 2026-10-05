#include "platform/time_hal.h"

#include "fsl_clock.h"
#include "fsl_common.h"

void time_hal_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t time_hal_cycles(void)
{
    return DWT->CYCCNT;
}

uint32_t time_hal_cycles_to_us(uint32_t cycles)
{
    uint32_t hz = CLOCK_GetCoreSysClkFreq();
    if (hz == 0) return 0;
    return (uint32_t)(((uint64_t)cycles * 1000000ull) / (uint64_t)hz);
}

uint32_t time_hal_elapsed_us(uint32_t start_cycles)
{
    uint32_t now = DWT->CYCCNT;
    uint32_t delta = now - start_cycles;
    return time_hal_cycles_to_us(delta);
}

void time_hal_delay_us(uint32_t us)
{
    if (us == 0) return;
    SDK_DelayAtLeastUs(us, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

