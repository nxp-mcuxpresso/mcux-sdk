//*****************************************************************************
// 88MW320 startup code for use with MCUXpresso IDE
//
// Version : 231220
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
// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
//*****************************************************************************
#include <NXP/crp.h>
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

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
WEAK void IntDefaultHandler(void);

//*****************************************************************************
// Forward declaration of the application IRQ handlers. When the application
// defines a handler (with the same name), this will automatically take
// precedence over weak definitions below
//*****************************************************************************
WEAK void Reserved16_IRQHandler(void);
WEAK void Reserved17_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void CRC_IRQHandler(void);
WEAK void AES_IRQHandler(void);
WEAK void I2C0_IRQHandler(void);
WEAK void I2C1_IRQHandler(void);
WEAK void Reserved23_IRQHandler(void);
WEAK void DMAC_IRQHandler(void);
WEAK void GPIO_IRQHandler(void);
WEAK void SSP0_IRQHandler(void);
WEAK void SSP1_IRQHandler(void);
WEAK void SSP2_IRQHandler(void);
WEAK void QSPI_IRQHandler(void);
WEAK void GPT0_IRQHandler(void);
WEAK void GPT1_IRQHandler(void);
WEAK void GPT2_IRQHandler(void);
WEAK void GPT3_IRQHandler(void);
WEAK void UART0_IRQHandler(void);
WEAK void UART1_IRQHandler(void);
WEAK void UART2_IRQHandler(void);
WEAK void Reserved37_IRQHandler(void);
WEAK void WDT_IRQHandler(void);
WEAK void Reserved39_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void DAC_IRQHandler(void);
WEAK void ACOMP_WAKEUP_IRQHandler(void);
WEAK void ACOMP_IRQHandler(void);
WEAK void SDIO_IRQHandler(void);
WEAK void USB_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void Reserved47_IRQHandler(void);
WEAK void Reserved48_IRQHandler(void);
WEAK void RC32M_IRQHandler(void);
WEAK void Reserved50_IRQHandler(void);
WEAK void Reserved51_IRQHandler(void);
WEAK void Reserved52_IRQHandler(void);
WEAK void Reserved53_IRQHandler(void);
WEAK void Reserved54_IRQHandler(void);
WEAK void Reserved55_IRQHandler(void);
WEAK void Reserved56_IRQHandler(void);
WEAK void Reserved57_IRQHandler(void);
WEAK void Reserved58_IRQHandler(void);
WEAK void Reserved59_IRQHandler(void);
WEAK void Reserved60_IRQHandler(void);
WEAK void Reserved61_IRQHandler(void);
WEAK void Reserved62_IRQHandler(void);
WEAK void Reserved63_IRQHandler(void);
WEAK void Reserved64_IRQHandler(void);
WEAK void Reserved65_IRQHandler(void);
WEAK void Reserved66_IRQHandler(void);
WEAK void Reserved67_IRQHandler(void);
WEAK void Reserved68_IRQHandler(void);
WEAK void Reserved69_IRQHandler(void);
WEAK void Reserved70_IRQHandler(void);
WEAK void Reserved71_IRQHandler(void);
WEAK void Reserved72_IRQHandler(void);
WEAK void Reserved73_IRQHandler(void);
WEAK void Reserved74_IRQHandler(void);
WEAK void Reserved75_IRQHandler(void);
WEAK void PMU_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void Reserved16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CRC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void AES_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMAC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SSP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SSP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SSP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void QSPI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACOMP_WAKEUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACOMP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SDIO_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved47_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved48_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RC32M_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved50_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved51_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved52_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved53_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved54_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved55_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved56_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved57_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved58_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved59_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved60_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved61_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved62_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved63_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved64_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved65_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved66_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved67_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved68_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved69_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved70_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved71_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved72_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved73_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved74_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved75_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PMU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved

    // Chip Level - 88MW320
    Reserved16_IRQHandler,    // 16: Reserved interrupt
    Reserved17_IRQHandler,    // 17: Reserved interrupt
    RTC_IRQHandler,           // 18: RTC INT
    CRC_IRQHandler,           // 19: CRC INT
    AES_IRQHandler,           // 20: AES INT
    I2C0_IRQHandler,          // 21: I2C0 INT
    I2C1_IRQHandler,          // 22: I2C1 INT
    Reserved23_IRQHandler,    // 23: Reserved interrupt
    DMAC_IRQHandler,          // 24: DMAC INT
    GPIO_IRQHandler,          // 25: GPIO INT
    SSP0_IRQHandler,          // 26: SSP0 INT
    SSP1_IRQHandler,          // 27: SSP1 INT
    SSP2_IRQHandler,          // 28: SSP2 INT
    QSPI_IRQHandler,          // 29: QSPI INT
    GPT0_IRQHandler,          // 30: GPT0 INT
    GPT1_IRQHandler,          // 31: GPT1 INT
    GPT2_IRQHandler,          // 32: GPT2 INT
    GPT3_IRQHandler,          // 33: GPT3 INT
    UART0_IRQHandler,         // 34: UART0 INT
    UART1_IRQHandler,         // 35: UART1 INT
    UART2_IRQHandler,         // 36: UART2 INT
    Reserved37_IRQHandler,    // 37: Reserved interrupt
    WDT_IRQHandler,           // 38: WDT INT
    Reserved39_IRQHandler,    // 39: Reserved interrupt
    ADC0_IRQHandler,          // 40: ADC0 INT
    DAC_IRQHandler,           // 41: DAC INT
    ACOMP_WAKEUP_IRQHandler,  // 42: ACOMP Wake-up INT
    ACOMP_IRQHandler,         // 43: ACOMP INT
    SDIO_IRQHandler,          // 44: SDIO INT
    USB_IRQHandler,           // 45: USB INT
    Reserved46_IRQHandler,    // 46: Reserved interrupt
    Reserved47_IRQHandler,    // 47: Reserved interrupt
    Reserved48_IRQHandler,    // 48: Reserved interrupt
    RC32M_IRQHandler,         // 49: RC32M INT FUNC
    Reserved50_IRQHandler,    // 50: Reserved interrupt
    Reserved51_IRQHandler,    // 51: Reserved interrupt
    Reserved52_IRQHandler,    // 52: Reserved interrupt
    Reserved53_IRQHandler,    // 53: Reserved interrupt
    Reserved54_IRQHandler,    // 54: Reserved interrupt
    Reserved55_IRQHandler,    // 55: Reserved interrupt
    Reserved56_IRQHandler,    // 56: Reserved interrupt
    Reserved57_IRQHandler,    // 57: Reserved interrupt
    Reserved58_IRQHandler,    // 58: Reserved interrupt
    Reserved59_IRQHandler,    // 59: Reserved interrupt
    Reserved60_IRQHandler,    // 60: Reserved interrupt
    Reserved61_IRQHandler,    // 61: Reserved interrupt
    Reserved62_IRQHandler,    // 62: Reserved interrupt
    Reserved63_IRQHandler,    // 63: Reserved interrupt
    Reserved64_IRQHandler,    // 64: Reserved interrupt
    Reserved65_IRQHandler,    // 65: Reserved interrupt
    Reserved66_IRQHandler,    // 66: Reserved interrupt
    Reserved67_IRQHandler,    // 67: Reserved interrupt
    Reserved68_IRQHandler,    // 68: Reserved interrupt
    Reserved69_IRQHandler,    // 69: Reserved interrupt
    Reserved70_IRQHandler,    // 70: Reserved interrupt
    Reserved71_IRQHandler,    // 71: Reserved interrupt
    Reserved72_IRQHandler,    // 72: Reserved interrupt
    Reserved73_IRQHandler,    // 73: Reserved interrupt
    Reserved74_IRQHandler,    // 74: Reserved interrupt
    Reserved75_IRQHandler,    // 75: Reserved interrupt
    PMU_IRQHandler,           // 76: ULP COMP


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
WEAK void Reserved16_IRQHandler(void)
{   Reserved16_DriverIRQHandler();
}

WEAK void Reserved17_IRQHandler(void)
{   Reserved17_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void CRC_IRQHandler(void)
{   CRC_DriverIRQHandler();
}

WEAK void AES_IRQHandler(void)
{   AES_DriverIRQHandler();
}

WEAK void I2C0_IRQHandler(void)
{   I2C0_DriverIRQHandler();
}

WEAK void I2C1_IRQHandler(void)
{   I2C1_DriverIRQHandler();
}

WEAK void Reserved23_IRQHandler(void)
{   Reserved23_DriverIRQHandler();
}

WEAK void DMAC_IRQHandler(void)
{   DMAC_DriverIRQHandler();
}

WEAK void GPIO_IRQHandler(void)
{   GPIO_DriverIRQHandler();
}

WEAK void SSP0_IRQHandler(void)
{   SSP0_DriverIRQHandler();
}

WEAK void SSP1_IRQHandler(void)
{   SSP1_DriverIRQHandler();
}

WEAK void SSP2_IRQHandler(void)
{   SSP2_DriverIRQHandler();
}

WEAK void QSPI_IRQHandler(void)
{   QSPI_DriverIRQHandler();
}

WEAK void GPT0_IRQHandler(void)
{   GPT0_DriverIRQHandler();
}

WEAK void GPT1_IRQHandler(void)
{   GPT1_DriverIRQHandler();
}

WEAK void GPT2_IRQHandler(void)
{   GPT2_DriverIRQHandler();
}

WEAK void GPT3_IRQHandler(void)
{   GPT3_DriverIRQHandler();
}

WEAK void UART0_IRQHandler(void)
{   UART0_DriverIRQHandler();
}

WEAK void UART1_IRQHandler(void)
{   UART1_DriverIRQHandler();
}

WEAK void UART2_IRQHandler(void)
{   UART2_DriverIRQHandler();
}

WEAK void Reserved37_IRQHandler(void)
{   Reserved37_DriverIRQHandler();
}

WEAK void WDT_IRQHandler(void)
{   WDT_DriverIRQHandler();
}

WEAK void Reserved39_IRQHandler(void)
{   Reserved39_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void DAC_IRQHandler(void)
{   DAC_DriverIRQHandler();
}

WEAK void ACOMP_WAKEUP_IRQHandler(void)
{   ACOMP_WAKEUP_DriverIRQHandler();
}

WEAK void ACOMP_IRQHandler(void)
{   ACOMP_DriverIRQHandler();
}

WEAK void SDIO_IRQHandler(void)
{   SDIO_DriverIRQHandler();
}

WEAK void USB_IRQHandler(void)
{   USB_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void Reserved47_IRQHandler(void)
{   Reserved47_DriverIRQHandler();
}

WEAK void Reserved48_IRQHandler(void)
{   Reserved48_DriverIRQHandler();
}

WEAK void RC32M_IRQHandler(void)
{   RC32M_DriverIRQHandler();
}

WEAK void Reserved50_IRQHandler(void)
{   Reserved50_DriverIRQHandler();
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

WEAK void Reserved55_IRQHandler(void)
{   Reserved55_DriverIRQHandler();
}

WEAK void Reserved56_IRQHandler(void)
{   Reserved56_DriverIRQHandler();
}

WEAK void Reserved57_IRQHandler(void)
{   Reserved57_DriverIRQHandler();
}

WEAK void Reserved58_IRQHandler(void)
{   Reserved58_DriverIRQHandler();
}

WEAK void Reserved59_IRQHandler(void)
{   Reserved59_DriverIRQHandler();
}

WEAK void Reserved60_IRQHandler(void)
{   Reserved60_DriverIRQHandler();
}

WEAK void Reserved61_IRQHandler(void)
{   Reserved61_DriverIRQHandler();
}

WEAK void Reserved62_IRQHandler(void)
{   Reserved62_DriverIRQHandler();
}

WEAK void Reserved63_IRQHandler(void)
{   Reserved63_DriverIRQHandler();
}

WEAK void Reserved64_IRQHandler(void)
{   Reserved64_DriverIRQHandler();
}

WEAK void Reserved65_IRQHandler(void)
{   Reserved65_DriverIRQHandler();
}

WEAK void Reserved66_IRQHandler(void)
{   Reserved66_DriverIRQHandler();
}

WEAK void Reserved67_IRQHandler(void)
{   Reserved67_DriverIRQHandler();
}

WEAK void Reserved68_IRQHandler(void)
{   Reserved68_DriverIRQHandler();
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

WEAK void Reserved72_IRQHandler(void)
{   Reserved72_DriverIRQHandler();
}

WEAK void Reserved73_IRQHandler(void)
{   Reserved73_DriverIRQHandler();
}

WEAK void Reserved74_IRQHandler(void)
{   Reserved74_DriverIRQHandler();
}

WEAK void Reserved75_IRQHandler(void)
{   Reserved75_DriverIRQHandler();
}

WEAK void PMU_IRQHandler(void)
{   PMU_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
