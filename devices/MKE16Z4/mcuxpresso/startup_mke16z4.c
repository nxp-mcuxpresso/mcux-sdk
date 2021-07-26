//*****************************************************************************
// MKE16Z4 startup code for use with MCUXpresso IDE
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
} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE};
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
WEAK void Reserved16_IRQHandler(void);
WEAK void Reserved17_IRQHandler(void);
WEAK void Reserved18_IRQHandler(void);
WEAK void Reserved19_IRQHandler(void);
WEAK void Reserved20_IRQHandler(void);
WEAK void FTFA_IRQHandler(void);
WEAK void LVD_LVW_IRQHandler(void);
WEAK void PORTAE_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void Reserved25_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void Reserved27_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void FTM0_IRQHandler(void);
WEAK void FTM1_IRQHandler(void);
WEAK void Reserved35_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void Reserved37_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void TSI_IRQHandler(void);
WEAK void PDB0_IRQHandler(void);
WEAK void PORTBCD_IRQHandler(void);
WEAK void SCG_RCM_IRQHandler(void);
WEAK void WDOG_EWM_IRQHandler(void);
WEAK void PWT_LPTMR0_IRQHandler(void);
WEAK void MSCAN_Rx_IRQHandler(void);
WEAK void MSCAN_ORed_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void Reserved16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved18_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved19_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LVD_LVW_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTAE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved27_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved35_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TSI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTBCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG_RCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG_EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWT_LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSCAN_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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

    // Chip Level - MKE16Z4
    Reserved16_IRQHandler,   // 16: Reserved interrupt
    Reserved17_IRQHandler,   // 17: Reserved interrupt
    Reserved18_IRQHandler,   // 18: Reserved interrupt
    Reserved19_IRQHandler,   // 19: Reserved interrupt
    Reserved20_IRQHandler,   // 20: Reserved interrupt
    FTFA_IRQHandler,         // 21: Flash memory single interrupt vector for all sources
    LVD_LVW_IRQHandler,      // 22: Low-voltage detect, low-voltage warning
    PORTAE_IRQHandler,       // 23: Pin detect (Port A, E)
    LPI2C0_IRQHandler,       // 24: Inter-integrated circuit 0 interrupt
    Reserved25_IRQHandler,   // 25: Reserved interrupt
    LPSPI0_IRQHandler,       // 26: Serial peripheral Interface 0 interrupt
    Reserved27_IRQHandler,   // 27: Reserved interrupt
    LPUART0_IRQHandler,      // 28: Single interrupt vector for all sources
    LPUART1_IRQHandler,      // 29: Single interrupt vector for all sources
    LPUART2_IRQHandler,      // 30: Single interrupt vector for all sources
    ADC0_IRQHandler,         // 31: ADC0 conversion complete interrupt
    CMP0_IRQHandler,         // 32: CMP0 interrupt
    FTM0_IRQHandler,         // 33: FTM0 single interrupt vector for all sources
    FTM1_IRQHandler,         // 34: FTM1 single interrupt vector for all sources
    Reserved35_IRQHandler,   // 35: Reserved interrupt
    RTC_IRQHandler,          // 36: Single interrupt vector for all sources
    Reserved37_IRQHandler,   // 37: Reserved interrupt
    LPIT0_IRQHandler,        // 38: LPIT channel 0-1
    Reserved39_IRQHandler,   // 39: Reserved interrupt
    TSI_IRQHandler,          // 40: TSI interrupt
    PDB0_IRQHandler,         // 41: Programmable delay block interrupt
    PORTBCD_IRQHandler,      // 42: Pin detect (Port B, C, D)
    SCG_RCM_IRQHandler,      // 43: Single interrupt vector for SCG and RCM
    WDOG_EWM_IRQHandler,     // 44: Single interrupt vector for WDOG and EWM
    PWT_LPTMR0_IRQHandler,   // 45: Single interrupt vector for PWT and LPTMR0
    MSCAN_Rx_IRQHandler,     // 46: MSCAN Rx Interrupt
    MSCAN_ORed_IRQHandler,   // 47: MSCAN Tx, Err and Wake-up interrupt


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
__attribute__ ((naked, section(".after_vectors.reset")))
void ResetISR(void) {

    // Disable interrupts
    __asm volatile ("cpsid i");


#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();

#else
    // Disable Watchdog
    // Write watchdog update key to unlock
    *((volatile unsigned int *)0x40052004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x40052008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *WDOG_CS = (unsigned int *) 0x40052000;
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
WEAK_AV void Reserved16_IRQHandler(void)
{   Reserved16_DriverIRQHandler();
}

WEAK_AV void Reserved17_IRQHandler(void)
{   Reserved17_DriverIRQHandler();
}

WEAK_AV void Reserved18_IRQHandler(void)
{   Reserved18_DriverIRQHandler();
}

WEAK_AV void Reserved19_IRQHandler(void)
{   Reserved19_DriverIRQHandler();
}

WEAK_AV void Reserved20_IRQHandler(void)
{   Reserved20_DriverIRQHandler();
}

WEAK_AV void FTFA_IRQHandler(void)
{   FTFA_DriverIRQHandler();
}

WEAK_AV void LVD_LVW_IRQHandler(void)
{   LVD_LVW_DriverIRQHandler();
}

WEAK_AV void PORTAE_IRQHandler(void)
{   PORTAE_DriverIRQHandler();
}

WEAK_AV void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK_AV void Reserved25_IRQHandler(void)
{   Reserved25_DriverIRQHandler();
}

WEAK_AV void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK_AV void Reserved27_IRQHandler(void)
{   Reserved27_DriverIRQHandler();
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

WEAK_AV void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK_AV void CMP0_IRQHandler(void)
{   CMP0_DriverIRQHandler();
}

WEAK_AV void FTM0_IRQHandler(void)
{   FTM0_DriverIRQHandler();
}

WEAK_AV void FTM1_IRQHandler(void)
{   FTM1_DriverIRQHandler();
}

WEAK_AV void Reserved35_IRQHandler(void)
{   Reserved35_DriverIRQHandler();
}

WEAK_AV void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK_AV void Reserved37_IRQHandler(void)
{   Reserved37_DriverIRQHandler();
}

WEAK_AV void LPIT0_IRQHandler(void)
{   LPIT0_DriverIRQHandler();
}

WEAK_AV void Reserved39_IRQHandler(void)
{   Reserved39_DriverIRQHandler();
}

WEAK_AV void TSI_IRQHandler(void)
{   TSI_DriverIRQHandler();
}

WEAK_AV void PDB0_IRQHandler(void)
{   PDB0_DriverIRQHandler();
}

WEAK_AV void PORTBCD_IRQHandler(void)
{   PORTBCD_DriverIRQHandler();
}

WEAK_AV void SCG_RCM_IRQHandler(void)
{   SCG_RCM_DriverIRQHandler();
}

WEAK_AV void WDOG_EWM_IRQHandler(void)
{   WDOG_EWM_DriverIRQHandler();
}

WEAK_AV void PWT_LPTMR0_IRQHandler(void)
{   PWT_LPTMR0_DriverIRQHandler();
}

WEAK_AV void MSCAN_Rx_IRQHandler(void)
{   MSCAN_DriverIRQHandler();
}

WEAK_AV void MSCAN_ORed_IRQHandler(void)
{   MSCAN_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
