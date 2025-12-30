#pragma once

#include <stdint.h>
#include "system_stm32f4xx.h"

void clock_init(void);
void systick_init_1ms(uint32_t core_clock_hz);