#include "device.h"   // should include stm32f4xx.h (+ system header)
#include "uart.h"

#include <stddef.h>
#include <stdint.h>

/* USART2 on PA2 (TX) / PA3 (RX), AF7 */
static void uart2_gpio_init(void)
{
    /* Enable GPIOA clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)RCC->AHB1ENR; /* read-back */

    /* Set PA2, PA3 to Alternate Function mode (MODER = 10b) */
    GPIOA->MODER &= ~(3u << (2u * 2u));
    GPIOA->MODER |=  (2u << (2u * 2u));

    GPIOA->MODER &= ~(3u << (3u * 2u));
    GPIOA->MODER |=  (2u << (3u * 2u));

    /* Optional but good practice: push-pull, high speed, pull-up on RX/TX */
    GPIOA->OTYPER &= ~((1u << 2u) | (1u << 3u));           /* push-pull */
    GPIOA->OSPEEDR |= (3u << (2u * 2u)) | (3u << (3u * 2u)); /* high speed */
    GPIOA->PUPDR &= ~((3u << (2u * 2u)) | (3u << (3u * 2u)));
    GPIOA->PUPDR |=  (1u << (2u * 2u)) | (1u << (3u * 2u));  /* pull-up */

    /* Select AF7 for PA2 and PA3: AFR[0] is pins 0..7, 4 bits per pin */
    GPIOA->AFR[0] &= ~((0xFu << (2u * 4u)) | (0xFu << (3u * 4u)));
    GPIOA->AFR[0] |=  ((7u   << (2u * 4u)) | (7u   << (3u * 4u)));
}

void uart2_init(uint32_t pclk1_hz, uint32_t baud)
{
    uart2_gpio_init();

    /* Enable USART2 clock on APB1 */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    (void)RCC->APB1ENR; /* read-back */

    /* Disable USART before configuration (UE = 0) */
    USART2->CR1 &= ~USART_CR1_UE;

    /* 8 data bits, no parity: M=0, PCE=0 */
    USART2->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);

    /* 1 stop bit: STOP[13:12] in CR2 = 00 */
    USART2->CR2 &= ~USART_CR2_STOP;

    /* Oversampling by 16 (OVER8 = 0) */
    USART2->CR1 &= ~USART_CR1_OVER8;

    /*
      Baud rate:
      For oversampling by 16, BRR = pclk / baud (rounded).
      Note: On STM32F4, BRR packs mantissa+fraction; ST's reference manual
      defines encoding. This simple formula works when pclk/baud is an integer
      or near-integer; for best accuracy you'd compute mantissa/fraction.
    */
    uint32_t usartdiv = (pclk1_hz + (baud / 2u)) / baud;
    USART2->BRR = usartdiv;

    /* Enable transmitter (TE) and receiver (RE) */
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    /* Enable USART (UE) */
    USART2->CR1 |= USART_CR1_UE;
}

void uart2_write_byte(uint8_t b)
{
    /* Wait until TXE (Transmit data register empty) is set */
    while ((USART2->SR & USART_SR_TXE) == 0u) { }

    USART2->DR = (uint16_t)b; /* DR is 9-bit wide on some configs; write as 16-bit */
}

void uart2_write_n(const uint8_t *buf, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        uart2_write_byte(buf[i]);
    }
}

void uart2_write(const char *s)
{
    while (*s) {
        if (*s == '\n') {
            uart2_write_byte('\r');
        }
        uart2_write_byte((uint8_t)*s++);
    }
}
