//*****************************************************************************
// K32L3A60_cm4 startup code for use with MCUXpresso IDE
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
WEAK void CTI0_MCM0_IRQHandler(void);
WEAK void DMA0_IRQHandler(void);
WEAK void DMA1_IRQHandler(void);
WEAK void DMA2_IRQHandler(void);
WEAK void DMA3_IRQHandler(void);
WEAK void DMA4_IRQHandler(void);
WEAK void DMA5_IRQHandler(void);
WEAK void DMA6_IRQHandler(void);
WEAK void DMA7_IRQHandler(void);
WEAK void DMA8_IRQHandler(void);
WEAK void DMA9_IRQHandler(void);
WEAK void DMA10_IRQHandler(void);
WEAK void DMA11_IRQHandler(void);
WEAK void DMA12_IRQHandler(void);
WEAK void DMA13_IRQHandler(void);
WEAK void DMA14_IRQHandler(void);
WEAK void DMA15_IRQHandler(void);
WEAK void DMA0_Error_IRQHandler(void);
WEAK void MSMC_IRQHandler(void);
WEAK void EWM_IRQHandler(void);
WEAK void FTFE_Command_Complete_IRQHandler(void);
WEAK void FTFE_Read_Collision_IRQHandler(void);
WEAK void LLWU0_IRQHandler(void);
WEAK void MUA_IRQHandler(void);
WEAK void SPM_IRQHandler(void);
WEAK void WDOG0_IRQHandler(void);
WEAK void SCG_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
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
WEAK void CAU3_Task_Complete_IRQHandler(void);
WEAK void CAU3_Security_Violation_IRQHandler(void);
WEAK void TRNG_IRQHandler(void);
WEAK void LPIT1_IRQHandler(void);
WEAK void LPTMR2_IRQHandler(void);
WEAK void TPM3_IRQHandler(void);
WEAK void LPI2C3_IRQHandler(void);
WEAK void LPSPI3_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void LPCMP1_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void CTI0_MCM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA9_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA10_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA12_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA13_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA14_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_Command_Complete_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_Read_Collision_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MUA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
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
void CAU3_Task_Complete_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAU3_Security_Violation_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPCMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
    // Core Level - CM4
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

    // Chip Level - K32L3A60_cm4
    CTI0_MCM0_IRQHandler,                // 16: Cross Trigger Interface 0 / Miscellaneous Control Module
    DMA0_IRQHandler,                     // 17: DMA0 channel 0 transfer complete
    DMA1_IRQHandler,                     // 18: DMA0 channel 1 transfer complete
    DMA2_IRQHandler,                     // 19: DMA0 channel 2 transfer complete
    DMA3_IRQHandler,                     // 20: DMA0 channel 3 transfer complete
    DMA4_IRQHandler,                     // 21: DMA0 channel 4 transfer complete
    DMA5_IRQHandler,                     // 22: DMA0 channel 5 transfer complete
    DMA6_IRQHandler,                     // 23: DMA0 channel 6 transfer complete
    DMA7_IRQHandler,                     // 24: DMA0 channel 7 transfer complete
    DMA8_IRQHandler,                     // 25: DMA0 channel 8 transfer complete
    DMA9_IRQHandler,                     // 26: DMA0 channel 9 transfer complete
    DMA10_IRQHandler,                    // 27: DMA0 channel 10 transfer complete
    DMA11_IRQHandler,                    // 28: DMA0 channel 11 transfer complete
    DMA12_IRQHandler,                    // 29: DMA0 channel 12 transfer complete
    DMA13_IRQHandler,                    // 30: DMA0 channel 13 transfer complete
    DMA14_IRQHandler,                    // 31: DMA0 channel 14 transfer complete
    DMA15_IRQHandler,                    // 32: DMA0 channel 15 transfer complete
    DMA0_Error_IRQHandler,               // 33: DMA0 channel 0-15 error interrupt
    MSMC_IRQHandler,                     // 34: MSMC (SMC0) interrupt
    EWM_IRQHandler,                      // 35: EWM interrupt
    FTFE_Command_Complete_IRQHandler,    // 36: FTFE interrupt
    FTFE_Read_Collision_IRQHandler,      // 37: FTFE interrupt
    LLWU0_IRQHandler,                    // 38: Low leakage wakeup 0
    MUA_IRQHandler,                      // 39: MU Side A interrupt
    SPM_IRQHandler,                      // 40: SPM
    WDOG0_IRQHandler,                    // 41: WDOG0 interrupt
    SCG_IRQHandler,                      // 42: SCG interrupt
    LPIT0_IRQHandler,                    // 43: LPIT0 interrupt
    RTC_IRQHandler,                      // 44: RTC Alarm interrupt
    LPTMR0_IRQHandler,                   // 45: LPTMR0 interrupt
    LPTMR1_IRQHandler,                   // 46: LPTMR1 interrupt
    TPM0_IRQHandler,                     // 47: TPM0 single interrupt vector for all sources
    TPM1_IRQHandler,                     // 48: TPM1 single interrupt vector for all sources
    TPM2_IRQHandler,                     // 49: TPM2 single interrupt vector for all sources
    EMVSIM0_IRQHandler,                  // 50: EMVSIM0 interrupt
    FLEXIO0_IRQHandler,                  // 51: FLEXIO0
    LPI2C0_IRQHandler,                   // 52: LPI2C0 interrupt
    LPI2C1_IRQHandler,                   // 53: LPI2C1 interrupt
    LPI2C2_IRQHandler,                   // 54: LPI2C2 interrupt
    I2S0_IRQHandler,                     // 55: I2S0 interrupt
    USDHC0_IRQHandler,                   // 56: SDHC0 interrupt
    LPSPI0_IRQHandler,                   // 57: LPSPI0 single interrupt vector for all sources
    LPSPI1_IRQHandler,                   // 58: LPSPI1 single interrupt vector for all sources
    LPSPI2_IRQHandler,                   // 59: LPSPI2 single interrupt vector for all sources
    LPUART0_IRQHandler,                  // 60: LPUART0 status and error
    LPUART1_IRQHandler,                  // 61: LPUART1 status and error
    LPUART2_IRQHandler,                  // 62: LPUART2 status and error
    USB0_IRQHandler,                     // 63: USB0 interrupt
    PORTA_IRQHandler,                    // 64: PORTA Pin detect
    PORTB_IRQHandler,                    // 65: PORTB Pin detect
    PORTC_IRQHandler,                    // 66: PORTC Pin detect
    PORTD_IRQHandler,                    // 67: PORTD Pin detect
    LPADC0_IRQHandler,                   // 68: LPADC0 interrupt
    LPCMP0_IRQHandler,                   // 69: LPCMP0 interrupt
    LPDAC0_IRQHandler,                   // 70: LPDAC0 interrupt
    CAU3_Task_Complete_IRQHandler,       // 71: Cryptographic Acceleration Unit version 3 Task Complete
    CAU3_Security_Violation_IRQHandler,  // 72: Cryptographic Acceleration Unit version 3 Security Violation
    TRNG_IRQHandler,                     // 73: TRNG interrupt
    LPIT1_IRQHandler,                    // 74: LPIT1 interrupt
    LPTMR2_IRQHandler,                   // 75: LPTMR2 interrupt
    TPM3_IRQHandler,                     // 76: TPM3 single interrupt vector for all sources
    LPI2C3_IRQHandler,                   // 77: LPI2C3 interrupt
    LPSPI3_IRQHandler,                   // 78: LPSPI3 single interrupt vector for all sources
    LPUART3_IRQHandler,                  // 79: LPUART3 status and error
    PORTE_IRQHandler,                    // 80: PORTE Pin detect
    LPCMP1_IRQHandler,                   // 81: LPCMP1 interrupt


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
// will enable the FPU
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
    //
    // Code to enable the Cortex-M4 FPU only included
    // if appropriate build options have been selected.
    // Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C)
    //
    // Read CPACR (located at address 0xE000ED88)
    // Set bits 20-23 to enable CP10 and CP11 coprocessors
    // Write back the modified value to the CPACR
    asm volatile ("LDR.W R0, =0xE000ED88\n\t"
                  "LDR R1, [R0]\n\t"
                  "ORR R1, R1, #(0xF << 20)\n\t"
                  "STR R1, [R0]");
#endif // (__VFP_FP__) && !(__SOFTFP__)
#endif // (__USE_CMSIS)


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
WEAK void CTI0_MCM0_IRQHandler(void)
{   CTI0_MCM0_DriverIRQHandler();
}

WEAK void DMA0_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA1_IRQHandler(void)
{   DMA1_DriverIRQHandler();
}

WEAK void DMA2_IRQHandler(void)
{   DMA2_DriverIRQHandler();
}

WEAK void DMA3_IRQHandler(void)
{   DMA3_DriverIRQHandler();
}

WEAK void DMA4_IRQHandler(void)
{   DMA4_DriverIRQHandler();
}

WEAK void DMA5_IRQHandler(void)
{   DMA5_DriverIRQHandler();
}

WEAK void DMA6_IRQHandler(void)
{   DMA6_DriverIRQHandler();
}

WEAK void DMA7_IRQHandler(void)
{   DMA7_DriverIRQHandler();
}

WEAK void DMA8_IRQHandler(void)
{   DMA8_DriverIRQHandler();
}

WEAK void DMA9_IRQHandler(void)
{   DMA9_DriverIRQHandler();
}

WEAK void DMA10_IRQHandler(void)
{   DMA10_DriverIRQHandler();
}

WEAK void DMA11_IRQHandler(void)
{   DMA11_DriverIRQHandler();
}

WEAK void DMA12_IRQHandler(void)
{   DMA12_DriverIRQHandler();
}

WEAK void DMA13_IRQHandler(void)
{   DMA13_DriverIRQHandler();
}

WEAK void DMA14_IRQHandler(void)
{   DMA14_DriverIRQHandler();
}

WEAK void DMA15_IRQHandler(void)
{   DMA15_DriverIRQHandler();
}

WEAK void DMA0_Error_IRQHandler(void)
{   DMA0_Error_DriverIRQHandler();
}

WEAK void MSMC_IRQHandler(void)
{   MSMC_DriverIRQHandler();
}

WEAK void EWM_IRQHandler(void)
{   EWM_DriverIRQHandler();
}

WEAK void FTFE_Command_Complete_IRQHandler(void)
{   FTFE_Command_Complete_DriverIRQHandler();
}

WEAK void FTFE_Read_Collision_IRQHandler(void)
{   FTFE_Read_Collision_DriverIRQHandler();
}

WEAK void LLWU0_IRQHandler(void)
{   LLWU0_DriverIRQHandler();
}

WEAK void MUA_IRQHandler(void)
{   MUA_DriverIRQHandler();
}

WEAK void SPM_IRQHandler(void)
{   SPM_DriverIRQHandler();
}

WEAK void WDOG0_IRQHandler(void)
{   WDOG0_DriverIRQHandler();
}

WEAK void SCG_IRQHandler(void)
{   SCG_DriverIRQHandler();
}

WEAK void LPIT0_IRQHandler(void)
{   LPIT0_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
}

WEAK void LPTMR1_IRQHandler(void)
{   LPTMR1_DriverIRQHandler();
}

WEAK void TPM0_IRQHandler(void)
{   TPM0_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK void TPM2_IRQHandler(void)
{   TPM2_DriverIRQHandler();
}

WEAK void EMVSIM0_IRQHandler(void)
{   EMVSIM0_DriverIRQHandler();
}

WEAK void FLEXIO0_IRQHandler(void)
{   FLEXIO0_DriverIRQHandler();
}

WEAK void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK void LPI2C2_IRQHandler(void)
{   LPI2C2_DriverIRQHandler();
}

WEAK void I2S0_IRQHandler(void)
{   I2S0_DriverIRQHandler();
}

WEAK void USDHC0_IRQHandler(void)
{   USDHC0_DriverIRQHandler();
}

WEAK void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK void LPSPI2_IRQHandler(void)
{   LPSPI2_DriverIRQHandler();
}

WEAK void LPUART0_IRQHandler(void)
{   LPUART0_DriverIRQHandler();
}

WEAK void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK void LPUART2_IRQHandler(void)
{   LPUART2_DriverIRQHandler();
}

WEAK void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
}

WEAK void PORTA_IRQHandler(void)
{   PORTA_DriverIRQHandler();
}

WEAK void PORTB_IRQHandler(void)
{   PORTB_DriverIRQHandler();
}

WEAK void PORTC_IRQHandler(void)
{   PORTC_DriverIRQHandler();
}

WEAK void PORTD_IRQHandler(void)
{   PORTD_DriverIRQHandler();
}

WEAK void LPADC0_IRQHandler(void)
{   LPADC0_DriverIRQHandler();
}

WEAK void LPCMP0_IRQHandler(void)
{   LPCMP0_DriverIRQHandler();
}

WEAK void LPDAC0_IRQHandler(void)
{   LPDAC0_DriverIRQHandler();
}

WEAK void CAU3_Task_Complete_IRQHandler(void)
{   CAU3_Task_Complete_DriverIRQHandler();
}

WEAK void CAU3_Security_Violation_IRQHandler(void)
{   CAU3_Security_Violation_DriverIRQHandler();
}

WEAK void TRNG_IRQHandler(void)
{   TRNG_DriverIRQHandler();
}

WEAK void LPIT1_IRQHandler(void)
{   LPIT1_DriverIRQHandler();
}

WEAK void LPTMR2_IRQHandler(void)
{   LPTMR2_DriverIRQHandler();
}

WEAK void TPM3_IRQHandler(void)
{   TPM3_DriverIRQHandler();
}

WEAK void LPI2C3_IRQHandler(void)
{   LPI2C3_DriverIRQHandler();
}

WEAK void LPSPI3_IRQHandler(void)
{   LPSPI3_DriverIRQHandler();
}

WEAK void LPUART3_IRQHandler(void)
{   LPUART3_DriverIRQHandler();
}

WEAK void PORTE_IRQHandler(void)
{   PORTE_DriverIRQHandler();
}

WEAK void LPCMP1_IRQHandler(void)
{   LPCMP1_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
