/* startup.c */
#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata;
extern uint32_t _sbss, _ebss;

int main(void);

void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for interrupts */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* Vector table */
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))(&_estack),  /* Initial stack pointer */
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,                  /* Reserved */
    SVC_Handler,
    DebugMon_Handler,
    0,                           /* Reserved */
    PendSV_Handler,
    SysTick_Handler,
    /* If you need more IRQs, add them here */
};

void Reset_Handler(void)
{
    /* Copy .data from Flash to RAM */
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Zero .bss */
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* Call main */
    (void)main();

    /* If main returns, trap */
    while (1) { }
}

void Default_Handler(void)
{
    while (1) { }
}
