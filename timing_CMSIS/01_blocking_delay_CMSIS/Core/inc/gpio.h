#pragma once

#include <stdint.h>

/**
 * @brief Enable the AHB1 clock for GPIOA.
 */
void gpio_enable_port_a(void);

/**
 * @brief Configure a GPIOA pin as a push-pull output (no pull-up/down, low speed by default).
 * @param pin GPIO pin number 0..15
 */
void gpio_set_output_a(uint32_t pin);

/**
 * @brief Toggle a GPIOA pin output state.
 * @param pin GPIO pin number 0..15
 */
void gpio_toggle_a(uint32_t pin);

/**
 * @brief Set a GPIOA pin output state to 1.
 * @param pin GPIO pin number 0..15
 */
void gpio_set_a(uint32_t pin);

/**
 * @brief Clear a GPIOA pin output state to 0.
 * @param pin GPIO pin number 0..15
 */
void gpio_clear_a(uint32_t pin);

/**
 * @brief Read current input state of a GPIOA pin.
 * @param pin GPIO pin number 0..15
 * @return 0 or 1
 */
uint32_t gpio_read_a(uint32_t pin);
