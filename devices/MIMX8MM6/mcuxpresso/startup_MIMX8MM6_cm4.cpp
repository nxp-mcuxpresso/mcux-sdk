/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2018 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

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
// automatically take precedence over these weak definitions
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);
//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void CTI0_IRQHandler(void);
WEAK void DMA0_0_4_IRQHandler(void);
WEAK void DMA0_1_5_IRQHandler(void);
WEAK void DMA0_2_6_IRQHandler(void);
WEAK void DMA0_3_7_IRQHandler(void);
WEAK void DMA0_8_12_IRQHandler(void);
WEAK void DMA0_9_13_IRQHandler(void);
WEAK void DMA0_10_14_IRQHandler(void);
WEAK void DMA0_11_15_IRQHandler(void);
WEAK void DMA0_16_20_IRQHandler(void);
WEAK void DMA0_17_21_IRQHandler(void);
WEAK void DMA0_18_22_IRQHandler(void);
WEAK void DMA0_19_23_IRQHandler(void);
WEAK void DMA0_24_28_IRQHandler(void);
WEAK void DMA0_25_29_IRQHandler(void);
WEAK void DMA0_26_30_IRQHandler(void);
WEAK void DMA0_27_31_IRQHandler(void);
WEAK void DMA0_Error_IRQHandler(void);
WEAK void MCM0_IRQHandler(void);
WEAK void EWM_IRQHandler(void);
WEAK void LLWU0_IRQHandler(void);
WEAK void SIM_IRQHandler(void);
WEAK void MU_A_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void Software1_IRQHandler(void);
WEAK void Software2_IRQHandler(void);
WEAK void WDOG0_IRQHandler(void);
WEAK void SCG0_IRQHandler(void);
WEAK void QSPI_IRQHandler(void);
WEAK void LTC_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void SNVS_IRQHandler(void);
WEAK void TRNG0_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void PMC0_IRQHandler(void);
WEAK void CMC0_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void LPTMR1_IRQHandler(void);
WEAK void TPM0_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void TPM2_IRQHandler(void);
WEAK void TPM3_IRQHandler(void);
WEAK void FLEXIO0_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void LPI2C2_IRQHandler(void);
WEAK void LPI2C3_IRQHandler(void);
WEAK void SAI0_IRQHandler(void);
WEAK void SAI1_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void DPM_IRQHandler(void);
WEAK void PCTLA_IRQHandler(void);
WEAK void PCTLB_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void ADC1_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void CMP1_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void DAC1_IRQHandler(void);
WEAK void WDOG1_IRQHandler(void);
WEAK void USB0_IRQHandler(void);
WEAK void USB1_IRQHandler(void);
WEAK void Reserved83_IRQHandler(void);
WEAK void WDOG2_IRQHandler(void);
WEAK void USBPHY_IRQHandler(void);
WEAK void CMC1_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void CTI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_0_4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_1_5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_2_6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_3_7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_8_12_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_9_13_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_10_14_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_11_15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_16_20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_17_21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_18_22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_19_23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_24_28_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_25_29_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_26_30_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_27_31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SIM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MU_A_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Software1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Software2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void QSPI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SNVS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PMC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DPM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PCTLA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PCTLB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved83_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
      &_vStackTop,                                  // The initial stack pointer
     ResetISR,                                      // The reset handler
     NMI_Handler,                                   //NMI Handler
     HardFault_Handler,                             //Hard Fault Handler
     MemManage_Handler,                             //MPU Fault Handler
     BusFault_Handler,                              //Bus Fault Handler
     UsageFault_Handler,                            //Usage Fault Handler
     0,                                             //Reserved
     0,                                             //Reserved
     0,                                             //Reserved
     0,                                             //Reserved
     SVC_Handler,                                   //SVCall Handler
     DebugMon_Handler,                              //Debug Monitor Handler
     0,                                             //Reserved
     PendSV_Handler,                                //PendSV Handler
     SysTick_Handler,                               //SysTick Handler
     //External Interrupts
     CTI0_IRQHandler,                               //Cross Trigger Interface for CM4
     DMA0_0_4_IRQHandler,                           //DMA Channel 0, 4 Transfer Complete
     DMA0_1_5_IRQHandler,                           //DMA Channel 1, 5 Transfer Complete
     DMA0_2_6_IRQHandler,                           //DMA Channel 2, 6 Transfer Complete
     DMA0_3_7_IRQHandler,                           //DMA Channel 3, 7 Transfer Complete
     DMA0_8_12_IRQHandler,                          //DMA Channel 8, 12 Transfer Complete
     DMA0_9_13_IRQHandler,                          //DMA Channel 9, 13 Transfer Complete
     DMA0_10_14_IRQHandler,                         //DMA Channel 10, 14 Transfer Complete
     DMA0_11_15_IRQHandler,                         //DMA Channel 11, 15 Transfer Complete
     DMA0_16_20_IRQHandler,                         //DMA Channel 16, 20 Transfer Complete
     DMA0_17_21_IRQHandler,                         //DMA Channel 17, 21 Transfer Complete
     DMA0_18_22_IRQHandler,                         //DMA Channel 18, 22 Transfer Complete
     DMA0_19_23_IRQHandler,                         //DMA Channel 19, 23 Transfer Complete
     DMA0_24_28_IRQHandler,                         //DMA Channel 24, 28 Transfer Complete
     DMA0_25_29_IRQHandler,                         //DMA Channel 25, 29 Transfer Complete
     DMA0_26_30_IRQHandler,                         //DMA Channel 26, 30 Transfer Complete
     DMA0_27_31_IRQHandler,                         //DMA Channel 27, 31 Transfer Complete
     DMA0_Error_IRQHandler,                         //DMA Error Interrupt - All Channels
     MCM0_IRQHandler,                               //MCM Interrupt
     EWM_IRQHandler,                                //External Watchdog Monitor Interrupt
     LLWU0_IRQHandler,                              //Low Leakage Wake Up
     SIM_IRQHandler,                                //System Integation Module
     MU_A_IRQHandler,                               //Messaging Unit - Side A
     Reserved39_IRQHandler,                         //Secured JTAG Controller
     Software1_IRQHandler,                          //Software Interrupt
     Software2_IRQHandler,                          //Software Interrupt
     WDOG0_IRQHandler,                              //Watchdog Interrupt
     SCG0_IRQHandler,                               //System Clock Generator for M4 domain
     QSPI_IRQHandler,                               //Quad Serial Peripheral Interface
     LTC_IRQHandler,                                //Low Power Trusted Cryptography
     Reserved46_IRQHandler,                         //Reserved
     SNVS_IRQHandler,                               //Secure Non-Volatile Storage Consolidated Interrupt
     TRNG0_IRQHandler,                              //Random Number Generator
     LPIT0_IRQHandler,                              //Low Power Periodic Interrupt Timer
     PMC0_IRQHandler,                               //Power Management  Control interrupts for M4 domain
     CMC0_IRQHandler,                               //Core Mode Controller interrupts for M4 domain
     LPTMR0_IRQHandler,                             //Low Power Timer
     LPTMR1_IRQHandler,                             //Low Power Timer
     TPM0_IRQHandler,                               //Timer PWM module
     TPM1_IRQHandler,                               //Timer PWM module
     TPM2_IRQHandler,                               //Timer PWM module
     TPM3_IRQHandler,                               //Timer PWM module
     FLEXIO0_IRQHandler,                            //Flexible IO
     LPI2C0_IRQHandler,                             //Inter-integrated circuit 0
     LPI2C1_IRQHandler,                             //Inter-integrated circuit 1
     LPI2C2_IRQHandler,                             //Inter-integrated circuit 2
     LPI2C3_IRQHandler,                             //Inter-integrated circuit 3
     SAI0_IRQHandler,                               //Serial Audio Interface
     SAI1_IRQHandler,                               //Serial Audio Interface 1
     LPSPI0_IRQHandler,                             //Low Power Serial Peripheral Interface
     LPSPI1_IRQHandler,                             //Low Power Serial Peripheral Interface
     LPUART0_IRQHandler,                            //Low Power UART
     LPUART1_IRQHandler,                            //Low Power UART
     LPUART2_IRQHandler,                            //Low Power UART
     LPUART3_IRQHandler,                            //Low Power UART
     DPM_IRQHandler,                                //Dynamic Process Monitor
     PCTLA_IRQHandler,                              //Port A pin interrupt
     PCTLB_IRQHandler,                              //Port B pin interrupt
     ADC0_IRQHandler,                               //Analog to Digital Convertor
     ADC1_IRQHandler,                               //Analog to Digital Convertor
     CMP0_IRQHandler,                               //Comparator
     CMP1_IRQHandler,                               //Comparator
     DAC0_IRQHandler,                               //Digital to Analog Convertor
     DAC1_IRQHandler,                               //Digital to Analog Convertor
     WDOG1_IRQHandler,                              //Watchdog Interrupt from A7 subsystem
     USB0_IRQHandler,                               //USB 0 Interrupt from A7 subsystem
     USB1_IRQHandler,                               //USB 1 Interrupt from A7 subsystem
     Reserved83_IRQHandler,                         //
     WDOG2_IRQHandler,                              //Watchdog Interrupt from A7 subsystem
     USBPHY_IRQHandler,                             //USB PHY (used in conjunction with USBOTG0)
     CMC1_IRQHandler,                               //A7 resets
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
    __main() ;
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
WEAK void NMI_Handler(void)                                   //NMI Handler
{ while(1) {}
}

WEAK void HardFault_Handler(void)                             //Hard Fault Handler
{ while(1) {}
}

WEAK void MemManage_Handler(void)                             //MPU Fault Handler
{ while(1) {}
}

WEAK void BusFault_Handler(void)                              //Bus Fault Handler
{ while(1) {}
}

WEAK void UsageFault_Handler(void)                            //Usage Fault Handler
{ while(1) {}
}

WEAK void SVC_Handler(void)                                   //SVCall Handler
{ while(1) {}
}

WEAK void DebugMon_Handler(void)                              //Debug Monitor Handler
{ while(1) {}
}

WEAK void PendSV_Handler(void)                                //PendSV Handler
{ while(1) {}
}

WEAK void SysTick_Handler(void)                               //SysTick Handler
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
WEAK void CTI0_IRQHandler(void)                               //Cross Trigger Interface for CM4
{   CTI0_DriverIRQHandler();
}

WEAK void DMA0_0_4_IRQHandler(void)                           //DMA Channel 0, 4 Transfer Complete
{   DMA0_0_4_DriverIRQHandler();
}

WEAK void DMA0_1_5_IRQHandler(void)                           //DMA Channel 1, 5 Transfer Complete
{   DMA0_1_5_DriverIRQHandler();
}

WEAK void DMA0_2_6_IRQHandler(void)                           //DMA Channel 2, 6 Transfer Complete
{   DMA0_2_6_DriverIRQHandler();
}

WEAK void DMA0_3_7_IRQHandler(void)                           //DMA Channel 3, 7 Transfer Complete
{   DMA0_3_7_DriverIRQHandler();
}

WEAK void DMA0_8_12_IRQHandler(void)                          //DMA Channel 8, 12 Transfer Complete
{   DMA0_8_12_DriverIRQHandler();
}

WEAK void DMA0_9_13_IRQHandler(void)                          //DMA Channel 9, 13 Transfer Complete
{   DMA0_9_13_DriverIRQHandler();
}

WEAK void DMA0_10_14_IRQHandler(void)                         //DMA Channel 10, 14 Transfer Complete
{   DMA0_10_14_DriverIRQHandler();
}

WEAK void DMA0_11_15_IRQHandler(void)                         //DMA Channel 11, 15 Transfer Complete
{   DMA0_11_15_DriverIRQHandler();
}

WEAK void DMA0_16_20_IRQHandler(void)                         //DMA Channel 16, 20 Transfer Complete
{   DMA0_16_20_DriverIRQHandler();
}

WEAK void DMA0_17_21_IRQHandler(void)                         //DMA Channel 17, 21 Transfer Complete
{   DMA0_17_21_DriverIRQHandler();
}

WEAK void DMA0_18_22_IRQHandler(void)                         //DMA Channel 18, 22 Transfer Complete
{   DMA0_18_22_DriverIRQHandler();
}

WEAK void DMA0_19_23_IRQHandler(void)                         //DMA Channel 19, 23 Transfer Complete
{   DMA0_19_23_DriverIRQHandler();
}

WEAK void DMA0_24_28_IRQHandler(void)                         //DMA Channel 24, 28 Transfer Complete
{   DMA0_24_28_DriverIRQHandler();
}

WEAK void DMA0_25_29_IRQHandler(void)                         //DMA Channel 25, 29 Transfer Complete
{   DMA0_25_29_DriverIRQHandler();
}

WEAK void DMA0_26_30_IRQHandler(void)                         //DMA Channel 26, 30 Transfer Complete
{   DMA0_26_30_DriverIRQHandler();
}

WEAK void DMA0_27_31_IRQHandler(void)                         //DMA Channel 27, 31 Transfer Complete
{   DMA0_27_31_DriverIRQHandler();
}

WEAK void DMA0_Error_IRQHandler(void)                         //DMA Error Interrupt - All Channels
{   DMA0_Error_DriverIRQHandler();
}

WEAK void MCM0_IRQHandler(void)                               //MCM Interrupt
{   MCM0_DriverIRQHandler();
}

WEAK void EWM_IRQHandler(void)                                //External Watchdog Monitor Interrupt
{   EWM_DriverIRQHandler();
}

WEAK void LLWU0_IRQHandler(void)                              //Low Leakage Wake Up
{   LLWU0_DriverIRQHandler();
}

WEAK void SIM_IRQHandler(void)                                //System Integation Module
{   SIM_DriverIRQHandler();
}

WEAK void MU_A_IRQHandler(void)                               //Messaging Unit - Side A
{   MU_A_DriverIRQHandler();
}

WEAK void Software1_IRQHandler(void)                          //Software Interrupt
{   Software1_DriverIRQHandler();
}

WEAK void Software2_IRQHandler(void)                          //Software Interrupt
{   Software2_DriverIRQHandler();
}

WEAK void WDOG0_IRQHandler(void)                              //Watchdog Interrupt
{   WDOG0_DriverIRQHandler();
}

WEAK void SCG0_IRQHandler(void)                               //System Clock Generator for M4 domain
{   SCG0_DriverIRQHandler();
}

WEAK void QSPI_IRQHandler(void)                               //Quad Serial Peripheral Interface
{   QSPI_DriverIRQHandler();
}

WEAK void LTC_IRQHandler(void)                                //Low Power Trusted Cryptography
{   LTC_DriverIRQHandler();
}

WEAK void SNVS_IRQHandler(void)                               //Secure Non-Volatile Storage Consolidated Interrupt
{   SNVS_DriverIRQHandler();
}

WEAK void TRNG0_IRQHandler(void)                              //Random Number Generator
{   TRNG0_DriverIRQHandler();
}

WEAK void LPIT0_IRQHandler(void)                              //Low Power Periodic Interrupt Timer
{   LPIT0_DriverIRQHandler();
}

WEAK void PMC0_IRQHandler(void)                               //Power Management  Control interrupts for M4 domain
{   PMC0_DriverIRQHandler();
}

WEAK void CMC0_IRQHandler(void)                               //Core Mode Controller interrupts for M4 domain
{   CMC0_DriverIRQHandler();
}

WEAK void LPTMR0_IRQHandler(void)                             //Low Power Timer
{   LPTMR0_DriverIRQHandler();
}

WEAK void LPTMR1_IRQHandler(void)                             //Low Power Timer
{   LPTMR1_DriverIRQHandler();
}

WEAK void TPM0_IRQHandler(void)                               //Timer PWM module
{   TPM0_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)                               //Timer PWM module
{   TPM1_DriverIRQHandler();
}

WEAK void TPM2_IRQHandler(void)                               //Timer PWM module
{   TPM2_DriverIRQHandler();
}

WEAK void TPM3_IRQHandler(void)                               //Timer PWM module
{   TPM3_DriverIRQHandler();
}

WEAK void FLEXIO0_IRQHandler(void)                            //Flexible IO
{   FLEXIO0_DriverIRQHandler();
}

WEAK void LPI2C0_IRQHandler(void)                             //Inter-integrated circuit 0
{   LPI2C0_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)                             //Inter-integrated circuit 1
{   LPI2C1_DriverIRQHandler();
}

WEAK void LPI2C2_IRQHandler(void)                             //Inter-integrated circuit 2
{   LPI2C2_DriverIRQHandler();
}

WEAK void LPI2C3_IRQHandler(void)                             //Inter-integrated circuit 3
{   LPI2C3_DriverIRQHandler();
}

WEAK void SAI0_IRQHandler(void)                               //Serial Audio Interface
{   SAI0_DriverIRQHandler();
}

WEAK void SAI1_IRQHandler(void)                               //Serial Audio Interface 1
{   SAI1_DriverIRQHandler();
}

WEAK void LPSPI0_IRQHandler(void)                             //Low Power Serial Peripheral Interface
{   LPSPI0_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)                             //Low Power Serial Peripheral Interface
{   LPSPI1_DriverIRQHandler();
}

WEAK void LPUART0_IRQHandler(void)                            //Low Power UART
{   LPUART0_DriverIRQHandler();
}

WEAK void LPUART1_IRQHandler(void)                            //Low Power UART
{   LPUART1_DriverIRQHandler();
}

WEAK void LPUART2_IRQHandler(void)                            //Low Power UART
{   LPUART2_DriverIRQHandler();
}

WEAK void LPUART3_IRQHandler(void)                            //Low Power UART
{   LPUART3_DriverIRQHandler();
}

WEAK void DPM_IRQHandler(void)                                //Dynamic Process Monitor
{   DPM_DriverIRQHandler();
}

WEAK void PCTLA_IRQHandler(void)                              //Port A pin interrupt
{   PCTLA_DriverIRQHandler();
}

WEAK void PCTLB_IRQHandler(void)                              //Port B pin interrupt
{   PCTLB_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)                               //Analog to Digital Convertor
{   ADC0_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)                               //Analog to Digital Convertor
{   ADC1_DriverIRQHandler();
}

WEAK void CMP0_IRQHandler(void)                               //Comparator
{   CMP0_DriverIRQHandler();
}

WEAK void CMP1_IRQHandler(void)                               //Comparator
{   CMP1_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)                               //Digital to Analog Convertor
{   DAC0_DriverIRQHandler();
}

WEAK void DAC1_IRQHandler(void)                               //Digital to Analog Convertor
{   DAC1_DriverIRQHandler();
}

WEAK void WDOG1_IRQHandler(void)                              //Watchdog Interrupt from A7 subsystem
{   WDOG1_DriverIRQHandler();
}

WEAK void USB0_IRQHandler(void)                               //USB 0 Interrupt from A7 subsystem
{   USB0_DriverIRQHandler();
}

WEAK void USB1_IRQHandler(void)                               //USB 1 Interrupt from A7 subsystem
{   USB1_DriverIRQHandler();
}

WEAK void WDOG2_IRQHandler(void)                              //Watchdog Interrupt from A7 subsystem
{   WDOG2_DriverIRQHandler();
}

WEAK void USBPHY_IRQHandler(void)                             //USB PHY (used in conjunction with USBOTG0)
{   USBPHY_DriverIRQHandler();
}

WEAK void CMC1_IRQHandler(void)                               //A7 resets
{  CMC1_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)

