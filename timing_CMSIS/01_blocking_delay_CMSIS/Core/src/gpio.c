#include "gpio.h"
#include "device.h"
#include "stm32f4xx.h"   // Brings in GPIOA, RCC, and bit definitions

// Defensive: ensure pin is in 0..15.
// In bare metal you may not want asserts; this clamps silently.
static inline uint32_t clamp_pin(uint32_t pin)
{
    return (pin > 15u) ? 15u : pin;
}

void gpio_enable_port_a(void)
{
    // Enable GPIOA clock on AHB1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    (void)RCC->AHB1ENR;
}

void gpio_set_output_a(uint32_t pin)
{
    pin = clamp_pin(pin);

    // Mode: 01 = General purpose output
    // MODER has 2 bits per pin
    GPIOA->MODER &= ~(3u << (pin * 2u));
    GPIOA->MODER |=  (1u << (pin * 2u));

    // Output type: 0 = Push-pull
    GPIOA->OTYPER &= ~(1u << pin);

    // Speed: 00 = Low speed (fine for LED/blink)
    GPIOA->OSPEEDR &= ~(3u << (pin * 2u));

    // Pull-up/pull-down: 00 = No pull
    GPIOA->PUPDR &= ~(3u << (pin * 2u));
}

void gpio_toggle_a(uint32_t pin)
{
    pin = clamp_pin(pin);

    // Toggling via ODR XOR is simplest.
    // For high integrity code you might prefer using BSRR and tracking state,
    // but for blink this is perfectly acceptable.
    GPIOA->ODR ^= (1u << pin);
}

void gpio_set_a(uint32_t pin)
{
    pin = clamp_pin(pin);

    // BSRR lower 16 bits set pin
    GPIOA->BSRR = (1u << pin);
}

void gpio_clear_a(uint32_t pin)
{
    pin = clamp_pin(pin);

    // BSRR upper 16 bits reset pin
    GPIOA->BSRR = (1u << (pin + 16u));
}

uint32_t gpio_read_a(uint32_t pin)
{
    pin = clamp_pin(pin);
    return (GPIOA->IDR >> pin) & 1u;
}
