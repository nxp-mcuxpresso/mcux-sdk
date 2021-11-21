//*****************************************************************************
// MKE18F16 startup code for use with MCUXpresso IDE
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
} Flash_Config = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF7DFE};
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
WEAK void DMA_Error_IRQHandler(void);
WEAK void MCM_IRQHandler(void);
WEAK void FTFE_IRQHandler(void);
WEAK void Read_Collision_IRQHandler(void);
WEAK void LVD_LVW_IRQHandler(void);
WEAK void Doublebit_Fault_IRQHandler(void);
WEAK void WDOG_EWM_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void Reserved44_IRQHandler(void);
WEAK void PWT_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void LPUART0_TX_IRQHandler(void);
WEAK void LPUART0_RX_IRQHandler(void);
WEAK void LPUART1_TX_IRQHandler(void);
WEAK void LPUART1_RX_IRQHandler(void);
WEAK void LPUART2_TX_IRQHandler(void);
WEAK void LPUART2_RX_IRQHandler(void);
WEAK void Reserved53_IRQHandler(void);
WEAK void Reserved54_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void CMP1_IRQHandler(void);
WEAK void FTM0_IRQHandler(void);
WEAK void FTM1_IRQHandler(void);
WEAK void FTM2_IRQHandler(void);
WEAK void Reserved61_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void RTC_Seconds_IRQHandler(void);
WEAK void LPIT0_Ch0_IRQHandler(void);
WEAK void LPIT0_Ch1_IRQHandler(void);
WEAK void LPIT0_Ch2_IRQHandler(void);
WEAK void LPIT0_Ch3_IRQHandler(void);
WEAK void PDB0_IRQHandler(void);
WEAK void Reserved69_IRQHandler(void);
WEAK void Reserved70_IRQHandler(void);
WEAK void Reserved71_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void SCG_RCM_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void PORTA_IRQHandler(void);
WEAK void PORTB_IRQHandler(void);
WEAK void PORTC_IRQHandler(void);
WEAK void PORTD_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void SWI_IRQHandler(void);
WEAK void Reserved81_IRQHandler(void);
WEAK void Reserved82_IRQHandler(void);
WEAK void Reserved83_IRQHandler(void);
WEAK void PDB1_IRQHandler(void);
WEAK void FLEXIO_IRQHandler(void);
WEAK void CMP2_IRQHandler(void);
WEAK void FTM3_IRQHandler(void);
WEAK void Reserved88_IRQHandler(void);
WEAK void ADC1_IRQHandler(void);
WEAK void ADC2_IRQHandler(void);
WEAK void Reserved91_IRQHandler(void);
WEAK void Reserved92_IRQHandler(void);
WEAK void PDB2_IRQHandler(void);
WEAK void CAN0_ORed_IRQHandler(void);
WEAK void CAN0_Error_IRQHandler(void);
WEAK void CAN0_Wake_Up_IRQHandler(void);
WEAK void CAN0_ORed_Message_buffer_IRQHandler(void);
WEAK void Reserved98_IRQHandler(void);
WEAK void Reserved99_IRQHandler(void);
WEAK void Reserved100_IRQHandler(void);
WEAK void CAN1_ORed_IRQHandler(void);
WEAK void CAN1_Error_IRQHandler(void);
WEAK void CAN1_Wake_Up_IRQHandler(void);
WEAK void CAN1_ORed_Message_buffer_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
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
void DMA_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Read_Collision_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LVD_LVW_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Doublebit_Fault_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG_EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved44_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_RX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_RX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_RX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved53_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved54_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved61_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Seconds_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_Ch0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_Ch1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_Ch2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_Ch3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved69_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved70_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved71_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG_RCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SWI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved81_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved82_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved83_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved88_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved91_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved92_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved98_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved99_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved100_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - MKE18F16
    DMA0_IRQHandler,                      // 16 : DMA channel 0 transfer complete
    DMA1_IRQHandler,                      // 17 : DMA channel 1 transfer complete
    DMA2_IRQHandler,                      // 18 : DMA channel 2 transfer complete
    DMA3_IRQHandler,                      // 19 : DMA channel 3 transfer complete
    DMA4_IRQHandler,                      // 20 : DMA channel 4 transfer complete
    DMA5_IRQHandler,                      // 21 : DMA channel 5 transfer complete
    DMA6_IRQHandler,                      // 22 : DMA channel 6 transfer complete
    DMA7_IRQHandler,                      // 23 : DMA channel 7 transfer complete
    DMA8_IRQHandler,                      // 24 : DMA channel 8 transfer complete
    DMA9_IRQHandler,                      // 25 : DMA channel 9 transfer complete
    DMA10_IRQHandler,                     // 26 : DMA channel 10 transfer complete
    DMA11_IRQHandler,                     // 27 : DMA channel 11 transfer complete
    DMA12_IRQHandler,                     // 28 : DMA channel 12 transfer complete
    DMA13_IRQHandler,                     // 29 : DMA channel 13 transfer complete
    DMA14_IRQHandler,                     // 30 : DMA channel 14 transfer complete
    DMA15_IRQHandler,                     // 31 : DMA channel 15 transfer complete
    DMA_Error_IRQHandler,                 // 32 : DMA error interrupt channels 0-15
    MCM_IRQHandler,                       // 33 : FPU sources
    FTFE_IRQHandler,                      // 34 : FTFE command complete
    Read_Collision_IRQHandler,            // 35 : FTFE read collision
    LVD_LVW_IRQHandler,                   // 36 : PMC controller low-voltage detect, low-voltage warning
    Doublebit_Fault_IRQHandler,           // 37 : FTFE double bit fault detect
    WDOG_EWM_IRQHandler,                  // 38 : Single interrupt vector for WDOG and EWM
    Reserved39_IRQHandler,                // 39 : Reserved interrupt
    LPI2C0_IRQHandler,                    // 40 : Inter-integrated circuit 0 interrupt
    LPI2C1_IRQHandler,                    // 41 : Inter-integrated circuit 1 interrupt
    LPSPI0_IRQHandler,                    // 42 : Serial peripheral Interface 0 interrupt
    LPSPI1_IRQHandler,                    // 43 : Serial peripheral Interface 1 interrupt
    Reserved44_IRQHandler,                // 44 : Reserved interrupt
    PWT_IRQHandler,                       // 45 : PWT interrupt
    Reserved46_IRQHandler,                // 46 : Reserved interrupt
    LPUART0_TX_IRQHandler,                // 47 : LPUART0 transmit interrupt
    LPUART0_RX_IRQHandler,                // 48 : LPUART0 receive interrupt
    LPUART1_TX_IRQHandler,                // 49 : LPUART1 transmit interrupt
    LPUART1_RX_IRQHandler,                // 50 : LPUART1 receive interrupt
    LPUART2_TX_IRQHandler,                // 51 : LPUART2 transmit interrupt
    LPUART2_RX_IRQHandler,                // 52 : LPUART2 receive interrupt
    Reserved53_IRQHandler,                // 53 : Reserved interrupt
    Reserved54_IRQHandler,                // 54 : Reserved interrupt
    ADC0_IRQHandler,                      // 55 : ADC conversion complete interrupt
    CMP0_IRQHandler,                      // 56 : CMP0 interrupt
    CMP1_IRQHandler,                      // 57 : CMP1 interrupt
    FTM0_IRQHandler,                      // 58 : FTM0 single interrupt vector for all sources
    FTM1_IRQHandler,                      // 59 : FTM1 single interrupt vector for all sources
    FTM2_IRQHandler,                      // 60 : FTM2 single interrupt vector for all sources
    Reserved61_IRQHandler,                // 61 : Reserved interrupt
    RTC_IRQHandler,                       // 62 : RTC alarm interrupt
    RTC_Seconds_IRQHandler,               // 63 : RTC seconds interrupt
    LPIT0_Ch0_IRQHandler,                 // 64 : LPIT channel 0 overflow interrupt
    LPIT0_Ch1_IRQHandler,                 // 65 : LPIT channel 1 overflow interrupt
    LPIT0_Ch2_IRQHandler,                 // 66 : LPIT channel 2 overflow interrupt
    LPIT0_Ch3_IRQHandler,                 // 67 : LPIT channel 3 overflow interrupt
    PDB0_IRQHandler,                      // 68 : Programmable delay block 0 interrupt
    Reserved69_IRQHandler,                // 69 : Reserved interrupt
    Reserved70_IRQHandler,                // 70 : Reserved interrupt
    Reserved71_IRQHandler,                // 71 : Reserved interrupt
    DAC0_IRQHandler,                      // 72 : Digital-to-analog converter 0 interrupt
    SCG_RCM_IRQHandler,                   // 73 : SCG_RCM interrupt
    LPTMR0_IRQHandler,                    // 74 : Single interrupt vector for  Low Power Timer 0 interrupt
    PORTA_IRQHandler,                     // 75 : Port A pin detect interrupt
    PORTB_IRQHandler,                     // 76 : Port B pin detect interrupt
    PORTC_IRQHandler,                     // 77 : Port C pin detect interrupt
    PORTD_IRQHandler,                     // 78 : Port D pin detect interrupt
    PORTE_IRQHandler,                     // 79 : Port E pin detect interrupt
    SWI_IRQHandler,                       // 80 : Software interrupt
    Reserved81_IRQHandler,                // 81 : Reserved interrupt
    Reserved82_IRQHandler,                // 82 : Reserved interrupt
    Reserved83_IRQHandler,                // 83 : Reserved interrupt
    PDB1_IRQHandler,                      // 84 : Programmable delay block 1 interrupt
    FLEXIO_IRQHandler,                    // 85 : FLEXIO interrupt
    CMP2_IRQHandler,                      // 86 : CMP2 interrupt
    FTM3_IRQHandler,                      // 87 : FlexTimer module 3 fault, overflow and channels interrupt
    Reserved88_IRQHandler,                // 88 : Reserved interrupt
    ADC1_IRQHandler,                      // 89 : ADC conversion complete interrupt
    ADC2_IRQHandler,                      // 90 : ADC conversion complete interrupt
    Reserved91_IRQHandler,                // 91 : Reserved interrupt
    Reserved92_IRQHandler,                // 92 : Reserved interrupt
    PDB2_IRQHandler,                      // 93 : Programmable delay block 2 interrupt
    CAN0_ORed_IRQHandler,                 // 94 : can
    CAN0_Error_IRQHandler,                // 95 : can
    CAN0_Wake_Up_IRQHandler,              // 96 : can
    CAN0_ORed_Message_buffer_IRQHandler,  // 97 : can
    Reserved98_IRQHandler,                // 98 : Reserved interrupt
    Reserved99_IRQHandler,                // 99 : Reserved interrupt
    Reserved100_IRQHandler,               // 100: Reserved interrupt
    CAN1_ORed_IRQHandler,                 // 101: can
    CAN1_Error_IRQHandler,                // 102: can
    CAN1_Wake_Up_IRQHandler,              // 103: can
    CAN1_ORed_Message_buffer_IRQHandler,  // 104: can


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

WEAK_AV void MemManage_Handler(void)
{ while(1) {}
}

WEAK_AV void BusFault_Handler(void)
{ while(1) {}
}

WEAK_AV void UsageFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SVC_Handler(void)
{ while(1) {}
}

WEAK_AV void DebugMon_Handler(void)
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

WEAK void DMA_Error_IRQHandler(void)
{   DMA_Error_DriverIRQHandler();
}

WEAK void MCM_IRQHandler(void)
{   MCM_DriverIRQHandler();
}

WEAK void FTFE_IRQHandler(void)
{   FTFE_DriverIRQHandler();
}

WEAK void Read_Collision_IRQHandler(void)
{   Read_Collision_DriverIRQHandler();
}

WEAK void LVD_LVW_IRQHandler(void)
{   LVD_LVW_DriverIRQHandler();
}

WEAK void Doublebit_Fault_IRQHandler(void)
{   Doublebit_Fault_DriverIRQHandler();
}

WEAK void WDOG_EWM_IRQHandler(void)
{   WDOG_EWM_DriverIRQHandler();
}

WEAK void Reserved39_IRQHandler(void)
{   Reserved39_DriverIRQHandler();
}

WEAK void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK void Reserved44_IRQHandler(void)
{   Reserved44_DriverIRQHandler();
}

WEAK void PWT_IRQHandler(void)
{   PWT_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void LPUART0_TX_IRQHandler(void)
{   LPUART0_TX_DriverIRQHandler();
}

WEAK void LPUART0_RX_IRQHandler(void)
{   LPUART0_RX_DriverIRQHandler();
}

WEAK void LPUART1_TX_IRQHandler(void)
{   LPUART1_TX_DriverIRQHandler();
}

WEAK void LPUART1_RX_IRQHandler(void)
{   LPUART1_RX_DriverIRQHandler();
}

WEAK void LPUART2_TX_IRQHandler(void)
{   LPUART2_TX_DriverIRQHandler();
}

WEAK void LPUART2_RX_IRQHandler(void)
{   LPUART2_RX_DriverIRQHandler();
}

WEAK void Reserved53_IRQHandler(void)
{   Reserved53_DriverIRQHandler();
}

WEAK void Reserved54_IRQHandler(void)
{   Reserved54_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void CMP0_IRQHandler(void)
{   CMP0_DriverIRQHandler();
}

WEAK void CMP1_IRQHandler(void)
{   CMP1_DriverIRQHandler();
}

WEAK void FTM0_IRQHandler(void)
{   FTM0_DriverIRQHandler();
}

WEAK void FTM1_IRQHandler(void)
{   FTM1_DriverIRQHandler();
}

WEAK void FTM2_IRQHandler(void)
{   FTM2_DriverIRQHandler();
}

WEAK void Reserved61_IRQHandler(void)
{   Reserved61_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void RTC_Seconds_IRQHandler(void)
{   RTC_Seconds_DriverIRQHandler();
}

WEAK void LPIT0_Ch0_IRQHandler(void)
{   LPIT0_Ch0_DriverIRQHandler();
}

WEAK void LPIT0_Ch1_IRQHandler(void)
{   LPIT0_Ch1_DriverIRQHandler();
}

WEAK void LPIT0_Ch2_IRQHandler(void)
{   LPIT0_Ch2_DriverIRQHandler();
}

WEAK void LPIT0_Ch3_IRQHandler(void)
{   LPIT0_Ch3_DriverIRQHandler();
}

WEAK void PDB0_IRQHandler(void)
{   PDB0_DriverIRQHandler();
}

WEAK void Reserved69_IRQHandler(void)
{   Reserved69_DriverIRQHandler();
}

WEAK void Reserved70_IRQHandler(void)
{   Reserved70_DriverIRQHandler();
}

WEAK void Reserved71_IRQHandler(void)
{   Reserved71_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK void SCG_RCM_IRQHandler(void)
{   SCG_RCM_DriverIRQHandler();
}

WEAK void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
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

WEAK void PORTE_IRQHandler(void)
{   PORTE_DriverIRQHandler();
}

WEAK void SWI_IRQHandler(void)
{   SWI_DriverIRQHandler();
}

WEAK void Reserved81_IRQHandler(void)
{   Reserved81_DriverIRQHandler();
}

WEAK void Reserved82_IRQHandler(void)
{   Reserved82_DriverIRQHandler();
}

WEAK void Reserved83_IRQHandler(void)
{   Reserved83_DriverIRQHandler();
}

WEAK void PDB1_IRQHandler(void)
{   PDB1_DriverIRQHandler();
}

WEAK void FLEXIO_IRQHandler(void)
{   FLEXIO_DriverIRQHandler();
}

WEAK void CMP2_IRQHandler(void)
{   CMP2_DriverIRQHandler();
}

WEAK void FTM3_IRQHandler(void)
{   FTM3_DriverIRQHandler();
}

WEAK void Reserved88_IRQHandler(void)
{   Reserved88_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)
{   ADC1_DriverIRQHandler();
}

WEAK void ADC2_IRQHandler(void)
{   ADC2_DriverIRQHandler();
}

WEAK void Reserved91_IRQHandler(void)
{   Reserved91_DriverIRQHandler();
}

WEAK void Reserved92_IRQHandler(void)
{   Reserved92_DriverIRQHandler();
}

WEAK void PDB2_IRQHandler(void)
{   PDB2_DriverIRQHandler();
}

WEAK void CAN0_ORed_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Error_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Wake_Up_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_ORed_Message_buffer_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void Reserved98_IRQHandler(void)
{   Reserved98_DriverIRQHandler();
}

WEAK void Reserved99_IRQHandler(void)
{   Reserved99_DriverIRQHandler();
}

WEAK void Reserved100_IRQHandler(void)
{   Reserved100_DriverIRQHandler();
}

WEAK void CAN1_ORed_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Error_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Wake_Up_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_ORed_Message_buffer_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
