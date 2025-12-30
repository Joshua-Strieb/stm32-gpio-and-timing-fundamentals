#include "clock.h"
#include "stm32f4xx.h"

void systick_init_1ms(uint32_t core_clock_hz)
{
    // 24-bit LOAD register: make sure core_clock_hz/1000 fits (< 2^24)
    SysTick->LOAD = (core_clock_hz / 1000U) - 1U;  // e.g., 16 MHz -> 15999
    SysTick->VAL  = 0U;                            // clear current count + COUNTFLAG
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |   // use core clock
                    SysTick_CTRL_TICKINT_Msk   |   // enable SysTick interrupt
                    SysTick_CTRL_ENABLE_Msk;       // start counting
}

void clock_init(void)
{
    // Default after reset: HSI @ 16 MHz
    SystemCoreClockUpdate();            // sets SystemCoreClock (should become 16000000)
    systick_init_1ms(SystemCoreClock);  // start 1 ms tick immediately
}
