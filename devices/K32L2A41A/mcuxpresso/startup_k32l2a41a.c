//*****************************************************************************
// K32L2A41A startup code for use with MCUXpresso IDE
//
// Version : 160420
//*****************************************************************************
//
// Copyright 2016-2020 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************

#if defined (DEBUG)
#pragma GCC push_options
#pragma GCC optimize ("Og")
#endif // (DEBUG)

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define WEAK_AV __attribute__ ((weak, section(".after_vectors")))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
// Flash Configuration block : 16-byte flash configuration field that stores
// default protection settings (loaded on reset) and security information that
// allows the MCU to restrict access to the Flash Memory module.
// Placed at address 0x400 by the linker script.
//*****************************************************************************
__attribute__ ((used,section(".FlashConfig"))) const struct {
    unsigned int word1;
    unsigned int word2;
    unsigned int word3;
    unsigned int word4;
} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF3DFE};
//*****************************************************************************
// Declaration of external SystemInit function
//*****************************************************************************
#if defined (__USE_CMSIS)
extern void SystemInit(void);
#endif // (__USE_CMSIS)

//*****************************************************************************
// Forward declaration of the core exception handlers.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions.
// If your application is a C++ one, then any interrupt handlers defined
// in C++ files within in your main application will need to have C linkage
// rather than C++ linkage. To do this, make sure that you are using extern "C"
// { .... } around the interrupt handler within your main application code.
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void DMA0_04_IRQHandler(void);
WEAK void DMA0_15_IRQHandler(void);
WEAK void DMA0_26_IRQHandler(void);
WEAK void DMA0_37_IRQHandler(void);
WEAK void CTI0_DMA0_Error_IRQHandler(void);
WEAK void FLEXIO0_IRQHandler(void);
WEAK void TPM0_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void TPM2_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void Reserved32_IRQHandler(void);
WEAK void PORTA_IRQHandler(void);
WEAK void PORTB_IRQHandler(void);
WEAK void PORTC_IRQHandler(void);
WEAK void PORTD_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void LLWU_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void USB0_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void RTC_Seconds_IRQHandler(void);
WEAK void INTMUX0_0_IRQHandler(void);
WEAK void INTMUX0_1_IRQHandler(void);
WEAK void INTMUX0_2_IRQHandler(void);
WEAK void INTMUX0_3_IRQHandler(void);
WEAK void LPTMR1_IRQHandler(void);
WEAK void Reserved49_IRQHandler(void);
WEAK void Reserved50_IRQHandler(void);
WEAK void Reserved51_IRQHandler(void);
WEAK void LPSPI2_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void EMVSIM0_IRQHandler(void);
WEAK void LPI2C2_IRQHandler(void);
WEAK void TSI0_IRQHandler(void);
WEAK void PMC_IRQHandler(void);
WEAK void FTFA_IRQHandler(void);
WEAK void SCG_IRQHandler(void);
WEAK void WDOG0_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void TRNG_IRQHandler(void);
WEAK void RCM_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void CMP1_IRQHandler(void);
WEAK void RTC_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void DMA0_04_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTI0_DMA0_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved32_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Seconds_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX0_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX0_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX0_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX0_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved49_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved50_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved51_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EMVSIM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TSI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

//*****************************************************************************
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);

//*****************************************************************************
// External declaration for the pointer to the stack top from the Linker Script
//*****************************************************************************
extern void _vStackTop(void);
//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
// The vector table.
// This relies on the linker script to place at correct location in memory.
//*****************************************************************************



extern void (* const g_pfnVectors[])(void);
extern void * __Vectors __attribute__ ((alias ("g_pfnVectors")));

__attribute__ ((used, section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM0P
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    0,                                 // Reserved
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - K32L2A41A
    DMA0_04_IRQHandler,          // 16: DMA0 channel 0/4 transfer complete
    DMA0_15_IRQHandler,          // 17: DMA0 channel 1/5 transfer complete
    DMA0_26_IRQHandler,          // 18: DMA0 channel 2/6 transfer complete
    DMA0_37_IRQHandler,          // 19: DMA0 channel 3/7 transfer complete
    CTI0_DMA0_Error_IRQHandler,  // 20: CTI0 or DMA0 error
    FLEXIO0_IRQHandler,          // 21: FLEXIO0
    TPM0_IRQHandler,             // 22: TPM0 single interrupt vector for all sources
    TPM1_IRQHandler,             // 23: TPM1 single interrupt vector for all sources
    TPM2_IRQHandler,             // 24: TPM2 single interrupt vector for all sources
    LPIT0_IRQHandler,            // 25: LPIT0 interrupt
    LPSPI0_IRQHandler,           // 26: LPSPI0 single interrupt vector for all sources
    LPSPI1_IRQHandler,           // 27: LPSPI1 single interrupt vector for all sources
    LPUART0_IRQHandler,          // 28: LPUART0 status and error
    LPUART1_IRQHandler,          // 29: LPUART1 status and error
    LPI2C0_IRQHandler,           // 30: LPI2C0 interrupt
    LPI2C1_IRQHandler,           // 31: LPI2C1 interrupt
    Reserved32_IRQHandler,       // 32: Reserved interrupt
    PORTA_IRQHandler,            // 33: PORTA Pin detect
    PORTB_IRQHandler,            // 34: PORTB Pin detect
    PORTC_IRQHandler,            // 35: PORTC Pin detect
    PORTD_IRQHandler,            // 36: PORTD Pin detect
    PORTE_IRQHandler,            // 37: PORTE Pin detect
    LLWU_IRQHandler,             // 38: Low leakage wakeup
    Reserved39_IRQHandler,       // 39: Reserved interrupt
    USB0_IRQHandler,             // 40: USB0 interrupt
    ADC0_IRQHandler,             // 41: ADC0 interrupt
    LPTMR0_IRQHandler,           // 42: LPTMR0 interrupt
    RTC_Seconds_IRQHandler,      // 43: RTC seconds
    INTMUX0_0_IRQHandler,        // 44: INTMUX0 channel 0 interrupt
    INTMUX0_1_IRQHandler,        // 45: INTMUX0 channel 1 interrupt
    INTMUX0_2_IRQHandler,        // 46: INTMUX0 channel 2 interrupt
    INTMUX0_3_IRQHandler,        // 47: INTMUX0 channel 3 interrupt
    LPTMR1_IRQHandler,           // 48: LPTMR1 interrupt  (INTMUX source IRQ0)
    Reserved49_IRQHandler,       // 49: Reserved interrupt
    Reserved50_IRQHandler,       // 50: Reserved interrupt
    Reserved51_IRQHandler,       // 51: Reserved interrupt
    LPSPI2_IRQHandler,           // 52: LPSPI2 single interrupt vector for all sources (INTMUX source IRQ4)
    LPUART2_IRQHandler,          // 53: LPUART2 status and error (INTMUX source IRQ5)
    EMVSIM0_IRQHandler,          // 54: EMVSIM0 interrupt (INTMUX source IRQ6)
    LPI2C2_IRQHandler,           // 55: LPI2C2 interrupt (INTMUX source IRQ7)
    TSI0_IRQHandler,             // 56: TSI0 interrupt (INTMUX source IRQ8)
    PMC_IRQHandler,              // 57: PMC interrupt (INTMUX source IRQ9)
    FTFA_IRQHandler,             // 58: FTFA interrupt (INTMUX source IRQ10)
    SCG_IRQHandler,              // 59: SCG interrupt (INTMUX source IRQ11)
    WDOG0_IRQHandler,            // 60: WDOG0 interrupt (INTMUX source IRQ12)
    DAC0_IRQHandler,             // 61: DAC0 interrupt (INTMUX source IRQ13)
    TRNG_IRQHandler,             // 62: TRNG interrupt (INTMUX source IRQ14)
    RCM_IRQHandler,              // 63: RCM interrupt (INTMUX source IRQ15)
    CMP0_IRQHandler,             // 64: CMP0 interrupt (INTMUX source IRQ16)
    CMP1_IRQHandler,             // 65: CMP1 interrupt (INTMUX source IRQ17)
    RTC_IRQHandler,              // 66: RTC Alarm interrupt (INTMUX source IRQ18)


}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors.init_data")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors.init_bss")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;

//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors.reset")))
void ResetISR(void) {

    // Disable interrupts
    __asm volatile ("cpsid i");


#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();

#else
    // Disable Watchdog
    // Write watchdog update key to unlock
    *((volatile unsigned int *)0x40076004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x40076008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *WDOG_CS = (unsigned int *) 0x40076000;
    *WDOG_CS = (*WDOG_CS & ~(1 << 7)) | (1 << 5);
#endif // (__USE_CMSIS)

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }

    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }


#if !defined (__USE_CMSIS)
// Assume that if __USE_CMSIS defined, then CMSIS SystemInit code
// will setup the VTOR register

    // Check to see if we are running the code from a non-zero
    // address (eg RAM, external flash), in which case we need
    // to modify the VTOR register to tell the CPU that the
    // vector table is located at a non-0x0 address.
    unsigned int * pSCB_VTOR = (unsigned int *) 0xE000ED08;
    if ((unsigned int *)g_pfnVectors!=(unsigned int *) 0x00000000) {
        *pSCB_VTOR = (unsigned int)g_pfnVectors;
    }
#endif // (__USE_CMSIS)
#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

    // Reenable interrupts
    __asm volatile ("cpsie i");

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main();
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default core exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
WEAK_AV void NMI_Handler(void)
{ while(1) {}
}

WEAK_AV void HardFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SVC_Handler(void)
{ while(1) {}
}

WEAK_AV void PendSV_Handler(void)
{ while(1) {}
}

WEAK_AV void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//*****************************************************************************
WEAK_AV void IntDefaultHandler(void)
{ while(1) {}
}

//*****************************************************************************
// Default application exception handlers. Override the ones here by defining
// your own handler routines in your application code. These routines call
// driver exception handlers or IntDefaultHandler() if no driver exception
// handler is included.
//*****************************************************************************
WEAK_AV void DMA0_04_IRQHandler(void)
{   DMA0_04_DriverIRQHandler();
}

WEAK_AV void DMA0_15_IRQHandler(void)
{   DMA0_15_DriverIRQHandler();
}

WEAK_AV void DMA0_26_IRQHandler(void)
{   DMA0_26_DriverIRQHandler();
}

WEAK_AV void DMA0_37_IRQHandler(void)
{   DMA0_37_DriverIRQHandler();
}

WEAK_AV void CTI0_DMA0_Error_IRQHandler(void)
{   CTI0_DMA0_Error_DriverIRQHandler();
}

WEAK_AV void FLEXIO0_IRQHandler(void)
{   FLEXIO0_DriverIRQHandler();
}

WEAK_AV void TPM0_IRQHandler(void)
{   TPM0_DriverIRQHandler();
}

WEAK_AV void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK_AV void TPM2_IRQHandler(void)
{   TPM2_DriverIRQHandler();
}

WEAK_AV void LPIT0_IRQHandler(void)
{   LPIT0_DriverIRQHandler();
}

WEAK_AV void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK_AV void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK_AV void LPUART0_IRQHandler(void)
{   LPUART0_DriverIRQHandler();
}

WEAK_AV void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK_AV void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK_AV void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK_AV void Reserved32_IRQHandler(void)
{   Reserved32_DriverIRQHandler();
}

WEAK_AV void PORTA_IRQHandler(void)
{   PORTA_DriverIRQHandler();
}

WEAK_AV void PORTB_IRQHandler(void)
{   PORTB_DriverIRQHandler();
}

WEAK_AV void PORTC_IRQHandler(void)
{   PORTC_DriverIRQHandler();
}

WEAK_AV void PORTD_IRQHandler(void)
{   PORTD_DriverIRQHandler();
}

WEAK_AV void PORTE_IRQHandler(void)
{   PORTE_DriverIRQHandler();
}

WEAK_AV void LLWU_IRQHandler(void)
{   LLWU_DriverIRQHandler();
}

WEAK_AV void Reserved39_IRQHandler(void)
{   Reserved39_DriverIRQHandler();
}

WEAK_AV void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
}

WEAK_AV void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK_AV void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
}

WEAK_AV void RTC_Seconds_IRQHandler(void)
{   RTC_Seconds_DriverIRQHandler();
}

WEAK_AV void INTMUX0_0_IRQHandler(void)
{   INTMUX0_0_DriverIRQHandler();
}

WEAK_AV void INTMUX0_1_IRQHandler(void)
{   INTMUX0_1_DriverIRQHandler();
}

WEAK_AV void INTMUX0_2_IRQHandler(void)
{   INTMUX0_2_DriverIRQHandler();
}

WEAK_AV void INTMUX0_3_IRQHandler(void)
{   INTMUX0_3_DriverIRQHandler();
}

WEAK_AV void LPTMR1_IRQHandler(void)
{   LPTMR1_DriverIRQHandler();
}

WEAK_AV void Reserved49_IRQHandler(void)
{   Reserved49_DriverIRQHandler();
}

WEAK_AV void Reserved50_IRQHandler(void)
{   Reserved50_DriverIRQHandler();
}

WEAK_AV void Reserved51_IRQHandler(void)
{   Reserved51_DriverIRQHandler();
}

WEAK_AV void LPSPI2_IRQHandler(void)
{   LPSPI2_DriverIRQHandler();
}

WEAK_AV void LPUART2_IRQHandler(void)
{   LPUART2_DriverIRQHandler();
}

WEAK_AV void EMVSIM0_IRQHandler(void)
{   EMVSIM0_DriverIRQHandler();
}

WEAK_AV void LPI2C2_IRQHandler(void)
{   LPI2C2_DriverIRQHandler();
}

WEAK_AV void TSI0_IRQHandler(void)
{   TSI0_DriverIRQHandler();
}

WEAK_AV void PMC_IRQHandler(void)
{   PMC_DriverIRQHandler();
}

WEAK_AV void FTFA_IRQHandler(void)
{   FTFA_DriverIRQHandler();
}

WEAK_AV void SCG_IRQHandler(void)
{   SCG_DriverIRQHandler();
}

WEAK_AV void WDOG0_IRQHandler(void)
{   WDOG0_DriverIRQHandler();
}

WEAK_AV void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK_AV void TRNG_IRQHandler(void)
{   TRNG_DriverIRQHandler();
}

WEAK_AV void RCM_IRQHandler(void)
{   RCM_DriverIRQHandler();
}

WEAK_AV void CMP0_IRQHandler(void)
{   CMP0_DriverIRQHandler();
}

WEAK_AV void CMP1_IRQHandler(void)
{   CMP1_DriverIRQHandler();
}

WEAK_AV void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
