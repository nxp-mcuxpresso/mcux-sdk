//*****************************************************************************
// MK28FA15 startup code for use with MCUXpresso IDE
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
WEAK void DMA0_DMA16_IRQHandler(void);
WEAK void DMA1_DMA17_IRQHandler(void);
WEAK void DMA2_DMA18_IRQHandler(void);
WEAK void DMA3_DMA19_IRQHandler(void);
WEAK void DMA4_DMA20_IRQHandler(void);
WEAK void DMA5_DMA21_IRQHandler(void);
WEAK void DMA6_DMA22_IRQHandler(void);
WEAK void DMA7_DMA23_IRQHandler(void);
WEAK void DMA8_DMA24_IRQHandler(void);
WEAK void DMA9_DMA25_IRQHandler(void);
WEAK void DMA10_DMA26_IRQHandler(void);
WEAK void DMA11_DMA27_IRQHandler(void);
WEAK void DMA12_DMA28_IRQHandler(void);
WEAK void DMA13_DMA29_IRQHandler(void);
WEAK void DMA14_DMA30_IRQHandler(void);
WEAK void DMA15_DMA31_IRQHandler(void);
WEAK void DMA_Error_IRQHandler(void);
WEAK void MCM_IRQHandler(void);
WEAK void FTFE_IRQHandler(void);
WEAK void Read_Collision_IRQHandler(void);
WEAK void LVD_LVW_IRQHandler(void);
WEAK void LLWU_IRQHandler(void);
WEAK void WDOG_EWM_IRQHandler(void);
WEAK void TRNG0_IRQHandler(void);
WEAK void I2C0_IRQHandler(void);
WEAK void I2C1_IRQHandler(void);
WEAK void SPI0_IRQHandler(void);
WEAK void SPI1_IRQHandler(void);
WEAK void I2S0_Tx_IRQHandler(void);
WEAK void I2S0_Rx_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void LPUART4_IRQHandler(void);
WEAK void Reserved51_IRQHandler(void);
WEAK void Reserved52_IRQHandler(void);
WEAK void Reserved53_IRQHandler(void);
WEAK void Reserved54_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void CMP1_IRQHandler(void);
WEAK void FTM0_IRQHandler(void);
WEAK void FTM1_IRQHandler(void);
WEAK void FTM2_IRQHandler(void);
WEAK void CMT_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void RTC_Seconds_IRQHandler(void);
WEAK void PIT0CH0_IRQHandler(void);
WEAK void PIT0CH1_IRQHandler(void);
WEAK void PIT0CH2_IRQHandler(void);
WEAK void PIT0CH3_IRQHandler(void);
WEAK void PDB0_IRQHandler(void);
WEAK void USB0_IRQHandler(void);
WEAK void USBDCD_IRQHandler(void);
WEAK void Reserved71_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void MCG_IRQHandler(void);
WEAK void LPTMR0_LPTMR1_IRQHandler(void);
WEAK void PORTA_IRQHandler(void);
WEAK void PORTB_IRQHandler(void);
WEAK void PORTC_IRQHandler(void);
WEAK void PORTD_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void SWI_IRQHandler(void);
WEAK void SPI2_IRQHandler(void);
WEAK void SPI3_IRQHandler(void);
WEAK void Reserved83_IRQHandler(void);
WEAK void I2S1_Tx_IRQHandler(void);
WEAK void I2S1_Rx_IRQHandler(void);
WEAK void FLEXIO0_IRQHandler(void);
WEAK void FTM3_IRQHandler(void);
WEAK void Reserved88_IRQHandler(void);
WEAK void Reserved89_IRQHandler(void);
WEAK void I2C2_IRQHandler(void);
WEAK void Reserved91_IRQHandler(void);
WEAK void Reserved92_IRQHandler(void);
WEAK void Reserved93_IRQHandler(void);
WEAK void Reserved94_IRQHandler(void);
WEAK void Reserved95_IRQHandler(void);
WEAK void Reserved96_IRQHandler(void);
WEAK void SDHC_IRQHandler(void);
WEAK void Reserved98_IRQHandler(void);
WEAK void Reserved99_IRQHandler(void);
WEAK void Reserved100_IRQHandler(void);
WEAK void Reserved101_IRQHandler(void);
WEAK void Reserved102_IRQHandler(void);
WEAK void Reserved103_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void TPM2_IRQHandler(void);
WEAK void USBHSDCD_IRQHandler(void);
WEAK void I2C3_IRQHandler(void);
WEAK void Reserved108_IRQHandler(void);
WEAK void USBHS_IRQHandler(void);
WEAK void Reserved110_IRQHandler(void);
WEAK void Reserved111_IRQHandler(void);
WEAK void Reserved112_IRQHandler(void);
WEAK void Reserved113_IRQHandler(void);
WEAK void Reserved114_IRQHandler(void);
WEAK void Reserved115_IRQHandler(void);
WEAK void QuadSPI0_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void DMA0_DMA16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DMA17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA2_DMA18_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_DMA19_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_DMA20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA5_DMA21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA6_DMA22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA7_DMA23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA8_DMA24_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA9_DMA25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA10_DMA26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA11_DMA27_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA12_DMA28_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA13_DMA29_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA14_DMA30_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA15_DMA31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_Error_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTFE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Read_Collision_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LVD_LVW_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG_EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_Tx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S0_Rx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved51_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved52_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved53_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved54_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Seconds_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0CH0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0CH1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0CH2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBDCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved71_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SWI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved83_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S1_Tx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2S1_Rx_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved88_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved89_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved91_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved92_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved93_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved94_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved95_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved96_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SDHC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved98_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved99_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved100_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved101_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved102_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved103_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBHSDCD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved108_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBHS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved110_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved111_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved112_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved113_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved114_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved115_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void QuadSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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

    // Chip Level - MK28FA15
    DMA0_DMA16_IRQHandler,      // 16 : DMA channel 0,16 transfer complete
    DMA1_DMA17_IRQHandler,      // 17 : DMA channel 1,17 transfer complete
    DMA2_DMA18_IRQHandler,      // 18 : DMA channel 2,18 transfer complete
    DMA3_DMA19_IRQHandler,      // 19 : DMA channel 3,19 transfer complete
    DMA4_DMA20_IRQHandler,      // 20 : DMA channel 4,20 transfer complete
    DMA5_DMA21_IRQHandler,      // 21 : DMA channel 5,21 transfer complete
    DMA6_DMA22_IRQHandler,      // 22 : DMA channel 6,22 transfer complete
    DMA7_DMA23_IRQHandler,      // 23 : DMA channel 7,23 transfer complete
    DMA8_DMA24_IRQHandler,      // 24 : DMA channel 8,24 transfer complete
    DMA9_DMA25_IRQHandler,      // 25 : DMA channel 9,25 transfer complete
    DMA10_DMA26_IRQHandler,     // 26 : DMA channel 10,26 transfer complete
    DMA11_DMA27_IRQHandler,     // 27 : DMA channel 11,27 transfer complete
    DMA12_DMA28_IRQHandler,     // 28 : DMA channel 12,28 transfer complete
    DMA13_DMA29_IRQHandler,     // 29 : DMA channel 13,29 transfer complete
    DMA14_DMA30_IRQHandler,     // 30 : DMA channel 14,30 transfer complete
    DMA15_DMA31_IRQHandler,     // 31 : DMA channel 15,31 transfer complete
    DMA_Error_IRQHandler,       // 32 : DMA channel 0 - 31 error
    MCM_IRQHandler,             // 33 : MCM normal interrupt
    FTFE_IRQHandler,            // 34 : FTFE command complete
    Read_Collision_IRQHandler,  // 35 : FTFE read collision
    LVD_LVW_IRQHandler,         // 36 : PMC controller low-voltage detect, low-voltage warning
    LLWU_IRQHandler,            // 37 : Low leakage wakeup unit
    WDOG_EWM_IRQHandler,        // 38 : Single interrupt vector for  WDOG and EWM
    TRNG0_IRQHandler,           // 39 : True randon number generator
    I2C0_IRQHandler,            // 40 : Inter-integrated circuit 0
    I2C1_IRQHandler,            // 41 : Inter-integrated circuit 1
    SPI0_IRQHandler,            // 42 : Serial peripheral Interface 0
    SPI1_IRQHandler,            // 43 : Serial peripheral Interface 1
    I2S0_Tx_IRQHandler,         // 44 : Integrated interchip sound 0 transmit interrupt
    I2S0_Rx_IRQHandler,         // 45 : Integrated interchip sound 0 receive interrupt
    LPUART0_IRQHandler,         // 46 : LPUART0 receive/transmit/error interrupt
    LPUART1_IRQHandler,         // 47 : LPUART1 receive/transmit/error interrupt
    LPUART2_IRQHandler,         // 48 : LPUART2 receive/transmit/error interrupt
    LPUART3_IRQHandler,         // 49 : LPUART3 receive/transmit/error interrupt
    LPUART4_IRQHandler,         // 50 : LPUART4 receive/transmit/error interrupt
    Reserved51_IRQHandler,      // 51 : Reserved interrupt
    Reserved52_IRQHandler,      // 52 : Reserved interrupt
    Reserved53_IRQHandler,      // 53 : Reserved interrupt
    Reserved54_IRQHandler,      // 54 : Reserved interrupt
    ADC0_IRQHandler,            // 55 : Analog-to-digital converter 0
    CMP0_IRQHandler,            // 56 : Comparator 0
    CMP1_IRQHandler,            // 57 : Comparator 1
    FTM0_IRQHandler,            // 58 : FlexTimer module 0 fault, overflow and channels interrupt
    FTM1_IRQHandler,            // 59 : FlexTimer module 1 fault, overflow and channels interrupt
    FTM2_IRQHandler,            // 60 : FlexTimer module 2 fault, overflow and channels interrupt
    CMT_IRQHandler,             // 61 : Carrier modulator transmitter
    RTC_IRQHandler,             // 62 : Real time clock
    RTC_Seconds_IRQHandler,     // 63 : Real time clock seconds
    PIT0CH0_IRQHandler,         // 64 : Periodic interrupt timer 0 channel 0
    PIT0CH1_IRQHandler,         // 65 : Periodic interrupt timer 0 channel 1
    PIT0CH2_IRQHandler,         // 66 : Periodic interrupt timer 0 channel 2
    PIT0CH3_IRQHandler,         // 67 : Periodic interrupt timer 0 channel 3
    PDB0_IRQHandler,            // 68 : Programmable delay block
    USB0_IRQHandler,            // 69 : USB OTG interrupt
    USBDCD_IRQHandler,          // 70 : USB charger detect
    Reserved71_IRQHandler,      // 71 : Reserved interrupt
    DAC0_IRQHandler,            // 72 : Digital-to-analog converter 0
    MCG_IRQHandler,             // 73 : Multipurpose clock generator
    LPTMR0_LPTMR1_IRQHandler,   // 74 : Single interrupt vector for  Low Power Timer 0 and 1
    PORTA_IRQHandler,           // 75 : Port A pin detect interrupt
    PORTB_IRQHandler,           // 76 : Port B pin detect interrupt
    PORTC_IRQHandler,           // 77 : Port C pin detect interrupt
    PORTD_IRQHandler,           // 78 : Port D pin detect interrupt
    PORTE_IRQHandler,           // 79 : Port E pin detect interrupt
    SWI_IRQHandler,             // 80 : Software interrupt
    SPI2_IRQHandler,            // 81 : Serial peripheral Interface 2
    SPI3_IRQHandler,            // 82 : Serial peripheral Interface 3
    Reserved83_IRQHandler,      // 83 : Reserved interrupt
    I2S1_Tx_IRQHandler,         // 84 : Integrated interchip sound 1 transmit interrupt
    I2S1_Rx_IRQHandler,         // 85 : Integrated interchip sound 1 receive interrupt
    FLEXIO0_IRQHandler,         // 86 : FLEXIO0
    FTM3_IRQHandler,            // 87 : FlexTimer module 3 fault, overflow and channels interrupt
    Reserved88_IRQHandler,      // 88 : Reserved interrupt
    Reserved89_IRQHandler,      // 89 : Reserved interrupt
    I2C2_IRQHandler,            // 90 : Inter-integrated circuit 2
    Reserved91_IRQHandler,      // 91 : Reserved interrupt
    Reserved92_IRQHandler,      // 92 : Reserved interrupt
    Reserved93_IRQHandler,      // 93 : Reserved interrupt
    Reserved94_IRQHandler,      // 94 : Reserved interrupt
    Reserved95_IRQHandler,      // 95 : Reserved interrupt
    Reserved96_IRQHandler,      // 96 : Reserved interrupt
    SDHC_IRQHandler,            // 97 : Secured digital host controller
    Reserved98_IRQHandler,      // 98 : Reserved interrupt
    Reserved99_IRQHandler,      // 99 : Reserved interrupt
    Reserved100_IRQHandler,     // 100: Reserved interrupt
    Reserved101_IRQHandler,     // 101: Reserved interrupt
    Reserved102_IRQHandler,     // 102: Reserved interrupt
    Reserved103_IRQHandler,     // 103: Reserved interrupt
    TPM1_IRQHandler,            // 104: TPM1 single interrupt vector for all sources
    TPM2_IRQHandler,            // 105: TPM2 single interrupt vector for all sources
    USBHSDCD_IRQHandler,        // 106: HS USB charger detect
    I2C3_IRQHandler,            // 107: Inter-integrated circuit 3
    Reserved108_IRQHandler,     // 108: Reserved interrupt
    USBHS_IRQHandler,           // 109: USB HS interrupt
    Reserved110_IRQHandler,     // 110: Reserved interrupt
    Reserved111_IRQHandler,     // 111: Reserved interrupt
    Reserved112_IRQHandler,     // 112: Reserved interrupt
    Reserved113_IRQHandler,     // 113: Reserved interrupt
    Reserved114_IRQHandler,     // 114: Reserved interrupt
    Reserved115_IRQHandler,     // 115: Reserved interrupt
    QuadSPI0_IRQHandler,        // 116: qspi


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
    //  Write 0xC520 to watchdog unlock register
    *((volatile unsigned short *)0x4005200E) = 0xC520;
    //  Followed by 0xD928 to complete the unlock
    *((volatile unsigned short *)0x4005200E) = 0xD928;
    // Now disable watchdog via STCTRLH register
    *((volatile unsigned short *)0x40052000) = 0x01D2u;
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
WEAK void DMA0_DMA16_IRQHandler(void)
{   DMA0_DMA16_DriverIRQHandler();
}

WEAK void DMA1_DMA17_IRQHandler(void)
{   DMA1_DMA17_DriverIRQHandler();
}

WEAK void DMA2_DMA18_IRQHandler(void)
{   DMA2_DMA18_DriverIRQHandler();
}

WEAK void DMA3_DMA19_IRQHandler(void)
{   DMA3_DMA19_DriverIRQHandler();
}

WEAK void DMA4_DMA20_IRQHandler(void)
{   DMA4_DMA20_DriverIRQHandler();
}

WEAK void DMA5_DMA21_IRQHandler(void)
{   DMA5_DMA21_DriverIRQHandler();
}

WEAK void DMA6_DMA22_IRQHandler(void)
{   DMA6_DMA22_DriverIRQHandler();
}

WEAK void DMA7_DMA23_IRQHandler(void)
{   DMA7_DMA23_DriverIRQHandler();
}

WEAK void DMA8_DMA24_IRQHandler(void)
{   DMA8_DMA24_DriverIRQHandler();
}

WEAK void DMA9_DMA25_IRQHandler(void)
{   DMA9_DMA25_DriverIRQHandler();
}

WEAK void DMA10_DMA26_IRQHandler(void)
{   DMA10_DMA26_DriverIRQHandler();
}

WEAK void DMA11_DMA27_IRQHandler(void)
{   DMA11_DMA27_DriverIRQHandler();
}

WEAK void DMA12_DMA28_IRQHandler(void)
{   DMA12_DMA28_DriverIRQHandler();
}

WEAK void DMA13_DMA29_IRQHandler(void)
{   DMA13_DMA29_DriverIRQHandler();
}

WEAK void DMA14_DMA30_IRQHandler(void)
{   DMA14_DMA30_DriverIRQHandler();
}

WEAK void DMA15_DMA31_IRQHandler(void)
{   DMA15_DMA31_DriverIRQHandler();
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

WEAK void LLWU_IRQHandler(void)
{   LLWU_DriverIRQHandler();
}

WEAK void WDOG_EWM_IRQHandler(void)
{   WDOG_EWM_DriverIRQHandler();
}

WEAK void TRNG0_IRQHandler(void)
{   TRNG0_DriverIRQHandler();
}

WEAK void I2C0_IRQHandler(void)
{   I2C0_DriverIRQHandler();
}

WEAK void I2C1_IRQHandler(void)
{   I2C1_DriverIRQHandler();
}

WEAK void SPI0_IRQHandler(void)
{   SPI0_DriverIRQHandler();
}

WEAK void SPI1_IRQHandler(void)
{   SPI1_DriverIRQHandler();
}

WEAK void I2S0_Tx_IRQHandler(void)
{   I2S0_Tx_DriverIRQHandler();
}

WEAK void I2S0_Rx_IRQHandler(void)
{   I2S0_Rx_DriverIRQHandler();
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

WEAK void LPUART3_IRQHandler(void)
{   LPUART3_DriverIRQHandler();
}

WEAK void LPUART4_IRQHandler(void)
{   LPUART4_DriverIRQHandler();
}

WEAK void Reserved51_IRQHandler(void)
{   Reserved51_DriverIRQHandler();
}

WEAK void Reserved52_IRQHandler(void)
{   Reserved52_DriverIRQHandler();
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

WEAK void CMT_IRQHandler(void)
{   CMT_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void RTC_Seconds_IRQHandler(void)
{   RTC_Seconds_DriverIRQHandler();
}

WEAK void PIT0CH0_IRQHandler(void)
{   PIT0CH0_DriverIRQHandler();
}

WEAK void PIT0CH1_IRQHandler(void)
{   PIT0CH1_DriverIRQHandler();
}

WEAK void PIT0CH2_IRQHandler(void)
{   PIT0CH2_DriverIRQHandler();
}

WEAK void PIT0CH3_IRQHandler(void)
{   PIT0CH3_DriverIRQHandler();
}

WEAK void PDB0_IRQHandler(void)
{   PDB0_DriverIRQHandler();
}

WEAK void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
}

WEAK void USBDCD_IRQHandler(void)
{   USBDCD_DriverIRQHandler();
}

WEAK void Reserved71_IRQHandler(void)
{   Reserved71_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK void MCG_IRQHandler(void)
{   MCG_DriverIRQHandler();
}

WEAK void LPTMR0_LPTMR1_IRQHandler(void)
{   LPTMR0_LPTMR1_DriverIRQHandler();
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

WEAK void SPI2_IRQHandler(void)
{   SPI2_DriverIRQHandler();
}

WEAK void SPI3_IRQHandler(void)
{   SPI3_DriverIRQHandler();
}

WEAK void Reserved83_IRQHandler(void)
{   Reserved83_DriverIRQHandler();
}

WEAK void I2S1_Tx_IRQHandler(void)
{   I2S1_Tx_DriverIRQHandler();
}

WEAK void I2S1_Rx_IRQHandler(void)
{   I2S1_Rx_DriverIRQHandler();
}

WEAK void FLEXIO0_IRQHandler(void)
{   FLEXIO0_DriverIRQHandler();
}

WEAK void FTM3_IRQHandler(void)
{   FTM3_DriverIRQHandler();
}

WEAK void Reserved88_IRQHandler(void)
{   Reserved88_DriverIRQHandler();
}

WEAK void Reserved89_IRQHandler(void)
{   Reserved89_DriverIRQHandler();
}

WEAK void I2C2_IRQHandler(void)
{   I2C2_DriverIRQHandler();
}

WEAK void Reserved91_IRQHandler(void)
{   Reserved91_DriverIRQHandler();
}

WEAK void Reserved92_IRQHandler(void)
{   Reserved92_DriverIRQHandler();
}

WEAK void Reserved93_IRQHandler(void)
{   Reserved93_DriverIRQHandler();
}

WEAK void Reserved94_IRQHandler(void)
{   Reserved94_DriverIRQHandler();
}

WEAK void Reserved95_IRQHandler(void)
{   Reserved95_DriverIRQHandler();
}

WEAK void Reserved96_IRQHandler(void)
{   Reserved96_DriverIRQHandler();
}

WEAK void SDHC_IRQHandler(void)
{   SDHC_DriverIRQHandler();
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

WEAK void Reserved101_IRQHandler(void)
{   Reserved101_DriverIRQHandler();
}

WEAK void Reserved102_IRQHandler(void)
{   Reserved102_DriverIRQHandler();
}

WEAK void Reserved103_IRQHandler(void)
{   Reserved103_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK void TPM2_IRQHandler(void)
{   TPM2_DriverIRQHandler();
}

WEAK void USBHSDCD_IRQHandler(void)
{   USBHSDCD_DriverIRQHandler();
}

WEAK void I2C3_IRQHandler(void)
{   I2C3_DriverIRQHandler();
}

WEAK void Reserved108_IRQHandler(void)
{   Reserved108_DriverIRQHandler();
}

WEAK void USBHS_IRQHandler(void)
{   USBHS_DriverIRQHandler();
}

WEAK void Reserved110_IRQHandler(void)
{   Reserved110_DriverIRQHandler();
}

WEAK void Reserved111_IRQHandler(void)
{   Reserved111_DriverIRQHandler();
}

WEAK void Reserved112_IRQHandler(void)
{   Reserved112_DriverIRQHandler();
}

WEAK void Reserved113_IRQHandler(void)
{   Reserved113_DriverIRQHandler();
}

WEAK void Reserved114_IRQHandler(void)
{   Reserved114_DriverIRQHandler();
}

WEAK void Reserved115_IRQHandler(void)
{   Reserved115_DriverIRQHandler();
}

WEAK void QuadSPI0_IRQHandler(void)
{   QuadSPI0_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
