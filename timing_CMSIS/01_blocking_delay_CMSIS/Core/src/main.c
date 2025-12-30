#include <stdint.h>
#include "clock.h"
#include "gpio.h"
#include "stm32f4xx.h"

static volatile uint32_t g_ms = 0;

void SysTick_Handler(void) // SysTick interrupt handler is defined in startup file
{
    g_ms++; // Increment millisecond counter, inaccurate
}

void delay(volatile uint32_t ms)
{
    uint32_t start = g_ms;

    while ((g_ms - start) < ms)
    {
        
    }
}

int main(void)
{
    clock_init();

    gpio_enable_port_a(); //GPIOA clock on AHB1 from gpio.c
    gpio_set_output_a(5); //sets pin 5 as an output from gpio.c
    //gpio_set_output_a(6); //sets pin 6 as an output from gpio.c

    while (1)
    {
        gpio_toggle_a(5);
        delay(500);
        //gpio_toggle_a(6);
        //delay(500);
    }
}
