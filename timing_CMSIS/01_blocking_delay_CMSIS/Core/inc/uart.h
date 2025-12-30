#pragma once

#include <stddef.h>
#include <stdint.h>

void uart2_init(uint32_t pclk1_hz, uint32_t baud);
void uart2_write_byte(uint8_t b);
void uart2_write_n(const uint8_t *buf, size_t len);
void uart2_write(const char *s);
