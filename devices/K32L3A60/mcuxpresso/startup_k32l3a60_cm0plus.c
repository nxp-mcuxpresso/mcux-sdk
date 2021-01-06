//*****************************************************************************
// K32L3A60_cm0plus startup code for use with MCUXpresso IDE
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
WEAK void CTI1_IRQHandler(void);
WEAK void DMA1_04_IRQHandler(void);
WEAK void DMA1_15_IRQHandler(void);
WEAK void DMA1_26_IRQHandler(void);
WEAK void DMA1_37_IRQHandler(void);
WEAK void DMA1_Error_IRQHandler(void);
WEAK void MSMC_IRQHandler(void);
WEAK void LLWU1_IRQHandler(void);
WEAK void MUB_IRQHandler(void);
WEAK void WDOG1_IRQHandler(void);
WEAK void CAU3_Task_Complete_IRQHandler(void);
WEAK void CAU3_Security_Violation_IRQHandler(void);
WEAK void TRNG_IRQHandler(void);
WEAK void LPIT1_IRQHandler(void);
WEAK void LPTMR2_IRQHandler(void);
WEAK void TPM3_IRQHandler(void);
WEAK void LPI2C3_IRQHandler(void);
WEAK void Reserved33_IRQHandler(void);
WEAK void Reserved34_IRQHandler(void);
WEAK void LPSPI3_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void LPCMP1_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void INTMUX1_0_IRQHandler(void);
WEAK void INTMUX1_1_IRQHandler(void);
WEAK void INTMUX1_2_IRQHandler(void);
WEAK void INTMUX1_3_IRQHandler(void);
WEAK void INTMUX1_4_IRQHandler(void);
WEAK void INTMUX1_5_IRQHandler(void);
WEAK void INTMUX1_6_IRQHandler(void);
WEAK void INTMUX1_7_IRQHandler(void);
WEAK void EWM_IRQHandler(void);
WEAK void FTFE_Command_Complete_IRQHandler(void);
WEAK void FTFE_Read_Collision_IRQHandler(void);
WEAK void SPM_IRQHandler(void);
WEAK void SCG_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void LPTMR1_IRQHandler(void);
WEAK void TPM0_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void TPM2_IRQHandler(void);
WEAK void EMVSIM0_IRQHandler(void);
WEAK void FLEXIO0_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void LPI2C2_IRQHandler(void);
WEAK void I2S0_IRQHandler(void);
WEAK void USDHC0_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPSPI2_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void USB0_IRQHandler(void);
WEAK void PORTA_IRQHandler(void);
WEAK void PORTB_IRQHandler(void);
WEAK void PORTC_IRQHandler(void);
WEAK void PORTD_IRQHandler(void);
WEAK void LPADC0_IRQHandler(void);
WEAK void LPCMP0_IRQHandler(void);
WEAK void LPDAC0_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void CTI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_04_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MUB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAU3_Task_Complete_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAU3_Security_Violation_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved33_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved34_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPCMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTMUX1_7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_Command_Complete_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_Read_Collision_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EMVSIM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPCMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPDAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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

    // Chip Level - K32L3A60_cm0plus
    CTI1_IRQHandler,                     // 16: Cross Trigger Interface 1
    DMA1_04_IRQHandler,                  // 17: DMA1 channel 0/4 transfer complete
    DMA1_15_IRQHandler,                  // 18: DMA1 channel 1/5 transfer complete
    DMA1_26_IRQHandler,                  // 19: DMA1 channel 2/6 transfer complete
    DMA1_37_IRQHandler,                  // 20: DMA1 channel 3/7 transfer complete
    DMA1_Error_IRQHandler,               // 21: DMA1 channel 0-7 error interrupt
    MSMC_IRQHandler,                     // 22: MSMC (SMC1) interrupt
    LLWU1_IRQHandler,                    // 23: Low leakage wakeup 1
    MUB_IRQHandler,                      // 24: MU Side B interrupt
    WDOG1_IRQHandler,                    // 25: WDOG1 interrupt
    CAU3_Task_Complete_IRQHandler,       // 26: Cryptographic Acceleration Unit version 3 Task Complete
    CAU3_Security_Violation_IRQHandler,  // 27: Cryptographic Acceleration Unit version 3 Security Violation
    TRNG_IRQHandler,                     // 28: TRNG interrupt
    LPIT1_IRQHandler,                    // 29: LPIT1 interrupt
    LPTMR2_IRQHandler,                   // 30: LPTMR2 interrupt
    TPM3_IRQHandler,                     // 31: TPM3 single interrupt vector for all sources
    LPI2C3_IRQHandler,                   // 32: LPI2C3 interrupt
    Reserved33_IRQHandler,               // 33: Reserved interrupt
    Reserved34_IRQHandler,               // 34: Reserved interrupt
    LPSPI3_IRQHandler,                   // 35: LPSPI3 single interrupt vector for all sources
    LPUART3_IRQHandler,                  // 36: LPUART3 status and error
    PORTE_IRQHandler,                    // 37: PORTE Pin detect
    LPCMP1_IRQHandler,                   // 38: LPCMP1 interrupt
    RTC_IRQHandler,                      // 39: RTC
    INTMUX1_0_IRQHandler,                // 40: INTMUX1 channel0 interrupt
    INTMUX1_1_IRQHandler,                // 41: INTMUX1 channel1 interrupt
    INTMUX1_2_IRQHandler,                // 42: INTMUX1 channel2 interrupt
    INTMUX1_3_IRQHandler,                // 43: INTMUX1 channel3 interrupt
    INTMUX1_4_IRQHandler,                // 44: INTMUX1 channel4 interrupt
    INTMUX1_5_IRQHandler,                // 45: INTMUX1 channel5 interrupt
    INTMUX1_6_IRQHandler,                // 46: INTMUX1 channel6 interrupt
    INTMUX1_7_IRQHandler,                // 47: INTMUX1 channel7 interrupt
    EWM_IRQHandler,                      // 48: EWM interrupt  (INTMUX1 source IRQ0)
    FTFE_Command_Complete_IRQHandler,    // 49: FTFE interrupt  (INTMUX1 source IRQ1)
    FTFE_Read_Collision_IRQHandler,      // 50: FTFE interrupt  (INTMUX1 source IRQ2)
    SPM_IRQHandler,                      // 51: SPM (INTMUX1 source IRQ3)
    SCG_IRQHandler,                      // 52: SCG interrupt (INTMUX1 source IRQ4)
    LPIT0_IRQHandler,                    // 53: LPIT0 interrupt (INTMUX1 source IRQ5)
    LPTMR0_IRQHandler,                   // 54: LPTMR0 interrupt (INTMUX1 source IRQ6)
    LPTMR1_IRQHandler,                   // 55: LPTMR1 interrupt (INTMUX1 source IRQ7)
    TPM0_IRQHandler,                     // 56: TPM0 single interrupt vector for all sources (INTMUX1 source IRQ8)
    TPM1_IRQHandler,                     // 57: TPM1 single interrupt vector for all sources (INTMUX1 source IRQ9)
    TPM2_IRQHandler,                     // 58: TPM2 single interrupt vector for all sources (INTMUX1 source IRQ10)
    EMVSIM0_IRQHandler,                  // 59: EMVSIM0 interrupt (INTMUX1 source IRQ11)
    FLEXIO0_IRQHandler,                  // 60: FLEXIO0 (INTMUX1 source IRQ12)
    LPI2C0_IRQHandler,                   // 61: LPI2C0 interrupt (INTMUX1 source IRQ13)
    LPI2C1_IRQHandler,                   // 62: LPI2C1 interrupt (INTMUX1 source IRQ14)
    LPI2C2_IRQHandler,                   // 63: LPI2C2 interrupt (INTMUX1 source IRQ15)
    I2S0_IRQHandler,                     // 64: I2S0 interrupt (INTMUX1 source IRQ16)
    USDHC0_IRQHandler,                   // 65: SDHC0 interrupt (INTMUX1 source IRQ17)
    LPSPI0_IRQHandler,                   // 66: LPSPI0 single interrupt vector for all sources (INTMUX1 source IRQ18)
    LPSPI1_IRQHandler,                   // 67: LPSPI1 single interrupt vector for all sources (INTMUX1 source IRQ19)
    LPSPI2_IRQHandler,                   // 68: LPSPI2 single interrupt vector for all sources (INTMUX1 source IRQ20)
    LPUART0_IRQHandler,                  // 69: LPUART0 status and error (INTMUX1 source IRQ21)
    LPUART1_IRQHandler,                  // 70: LPUART1 status and error (INTMUX1 source IRQ22)
    LPUART2_IRQHandler,                  // 71: LPUART2 status and error (INTMUX1 source IRQ23)
    USB0_IRQHandler,                     // 72: USB0 interrupt (INTMUX1 source IRQ24)
    PORTA_IRQHandler,                    // 73: PORTA Pin detect (INTMUX1 source IRQ25)
    PORTB_IRQHandler,                    // 74: PORTB Pin detect (INTMUX1 source IRQ26)
    PORTC_IRQHandler,                    // 75: PORTC Pin detect (INTMUX1 source IRQ27)
    PORTD_IRQHandler,                    // 76: PORTD Pin detect (INTMUX1 source IRQ28)
    LPADC0_IRQHandler,                   // 77: LPADC0 interrupt (INTMUX1 source IRQ29)
    LPCMP0_IRQHandler,                   // 78: LPCMP0 interrupt (INTMUX1 source IRQ30)
    LPDAC0_IRQHandler,                   // 79: LPDAC0 interrupt (INTMUX1 source IRQ31)


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
    *((volatile unsigned int *)0x41026004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x41026008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *WDOG_CS = (unsigned int *) 0x41026000;
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
WEAK_AV void CTI1_IRQHandler(void)
{   CTI1_DriverIRQHandler();
}

WEAK_AV void DMA1_04_IRQHandler(void)
{   DMA1_04_DriverIRQHandler();
}

WEAK_AV void DMA1_15_IRQHandler(void)
{   DMA1_15_DriverIRQHandler();
}

WEAK_AV void DMA1_26_IRQHandler(void)
{   DMA1_26_DriverIRQHandler();
}

WEAK_AV void DMA1_37_IRQHandler(void)
{   DMA1_37_DriverIRQHandler();
}

WEAK_AV void DMA1_Error_IRQHandler(void)
{   DMA1_Error_DriverIRQHandler();
}

WEAK_AV void MSMC_IRQHandler(void)
{   MSMC_DriverIRQHandler();
}

WEAK_AV void LLWU1_IRQHandler(void)
{   LLWU1_DriverIRQHandler();
}

WEAK_AV void MUB_IRQHandler(void)
{   MUB_DriverIRQHandler();
}

WEAK_AV void WDOG1_IRQHandler(void)
{   WDOG1_DriverIRQHandler();
}

WEAK_AV void CAU3_Task_Complete_IRQHandler(void)
{   CAU3_Task_Complete_DriverIRQHandler();
}

WEAK_AV void CAU3_Security_Violation_IRQHandler(void)
{   CAU3_Security_Violation_DriverIRQHandler();
}

WEAK_AV void TRNG_IRQHandler(void)
{   TRNG_DriverIRQHandler();
}

WEAK_AV void LPIT1_IRQHandler(void)
{   LPIT1_DriverIRQHandler();
}

WEAK_AV void LPTMR2_IRQHandler(void)
{   LPTMR2_DriverIRQHandler();
}

WEAK_AV void TPM3_IRQHandler(void)
{   TPM3_DriverIRQHandler();
}

WEAK_AV void LPI2C3_IRQHandler(void)
{   LPI2C3_DriverIRQHandler();
}

WEAK_AV void Reserved33_IRQHandler(void)
{   Reserved33_DriverIRQHandler();
}

WEAK_AV void Reserved34_IRQHandler(void)
{   Reserved34_DriverIRQHandler();
}

WEAK_AV void LPSPI3_IRQHandler(void)
{   LPSPI3_DriverIRQHandler();
}

WEAK_AV void LPUART3_IRQHandler(void)
{   LPUART3_DriverIRQHandler();
}

WEAK_AV void PORTE_IRQHandler(void)
{   PORTE_DriverIRQHandler();
}

WEAK_AV void LPCMP1_IRQHandler(void)
{   LPCMP1_DriverIRQHandler();
}

WEAK_AV void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK_AV void INTMUX1_0_IRQHandler(void)
{   INTMUX1_0_DriverIRQHandler();
}

WEAK_AV void INTMUX1_1_IRQHandler(void)
{   INTMUX1_1_DriverIRQHandler();
}

WEAK_AV void INTMUX1_2_IRQHandler(void)
{   INTMUX1_2_DriverIRQHandler();
}

WEAK_AV void INTMUX1_3_IRQHandler(void)
{   INTMUX1_3_DriverIRQHandler();
}

WEAK_AV void INTMUX1_4_IRQHandler(void)
{   INTMUX1_4_DriverIRQHandler();
}

WEAK_AV void INTMUX1_5_IRQHandler(void)
{   INTMUX1_5_DriverIRQHandler();
}

WEAK_AV void INTMUX1_6_IRQHandler(void)
{   INTMUX1_6_DriverIRQHandler();
}

WEAK_AV void INTMUX1_7_IRQHandler(void)
{   INTMUX1_7_DriverIRQHandler();
}

WEAK_AV void EWM_IRQHandler(void)
{   EWM_DriverIRQHandler();
}

WEAK_AV void FTFE_Command_Complete_IRQHandler(void)
{   FTFE_Command_Complete_DriverIRQHandler();
}

WEAK_AV void FTFE_Read_Collision_IRQHandler(void)
{   FTFE_Read_Collision_DriverIRQHandler();
}

WEAK_AV void SPM_IRQHandler(void)
{   SPM_DriverIRQHandler();
}

WEAK_AV void SCG_IRQHandler(void)
{   SCG_DriverIRQHandler();
}

WEAK_AV void LPIT0_IRQHandler(void)
{   LPIT0_DriverIRQHandler();
}

WEAK_AV void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
}

WEAK_AV void LPTMR1_IRQHandler(void)
{   LPTMR1_DriverIRQHandler();
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

WEAK_AV void EMVSIM0_IRQHandler(void)
{   EMVSIM0_DriverIRQHandler();
}

WEAK_AV void FLEXIO0_IRQHandler(void)
{   FLEXIO0_DriverIRQHandler();
}

WEAK_AV void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK_AV void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK_AV void LPI2C2_IRQHandler(void)
{   LPI2C2_DriverIRQHandler();
}

WEAK_AV void I2S0_IRQHandler(void)
{   I2S0_DriverIRQHandler();
}

WEAK_AV void USDHC0_IRQHandler(void)
{   USDHC0_DriverIRQHandler();
}

WEAK_AV void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK_AV void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK_AV void LPSPI2_IRQHandler(void)
{   LPSPI2_DriverIRQHandler();
}

WEAK_AV void LPUART0_IRQHandler(void)
{   LPUART0_DriverIRQHandler();
}

WEAK_AV void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK_AV void LPUART2_IRQHandler(void)
{   LPUART2_DriverIRQHandler();
}

WEAK_AV void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
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

WEAK_AV void LPADC0_IRQHandler(void)
{   LPADC0_DriverIRQHandler();
}

WEAK_AV void LPCMP0_IRQHandler(void)
{   LPCMP0_DriverIRQHandler();
}

WEAK_AV void LPDAC0_IRQHandler(void)
{   LPDAC0_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
