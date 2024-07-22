//*****************************************************************************
// KW45Z41082 startup code for use with MCUXpresso IDE
//
// Version : 270224
//*****************************************************************************
//
// Copyright 2016-2024 NXP
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
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SecureFault_Handler(void);
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
WEAK void CTI_IRQHandler(void);
WEAK void CMC0_IRQHandler(void);
WEAK void DMA0_CH0_IRQHandler(void);
WEAK void DMA0_CH1_IRQHandler(void);
WEAK void DMA0_CH2_IRQHandler(void);
WEAK void DMA0_CH3_IRQHandler(void);
WEAK void DMA0_CH4_IRQHandler(void);
WEAK void DMA0_CH5_IRQHandler(void);
WEAK void DMA0_CH6_IRQHandler(void);
WEAK void DMA0_CH7_IRQHandler(void);
WEAK void DMA0_CH8_IRQHandler(void);
WEAK void DMA0_CH9_IRQHandler(void);
WEAK void DMA0_CH10_IRQHandler(void);
WEAK void DMA0_CH11_IRQHandler(void);
WEAK void DMA0_CH12_IRQHandler(void);
WEAK void DMA0_CH13_IRQHandler(void);
WEAK void DMA0_CH14_IRQHandler(void);
WEAK void DMA0_CH15_IRQHandler(void);
WEAK void EWM0_IRQHandler(void);
WEAK void MCM0_IRQHandler(void);
WEAK void MSCM0_IRQHandler(void);
WEAK void SPC0_IRQHandler(void);
WEAK void WUU0_IRQHandler(void);
WEAK void WDOG0_IRQHandler(void);
WEAK void WDOG1_IRQHandler(void);
WEAK void SCG0_IRQHandler(void);
WEAK void SFA0_IRQHandler(void);
WEAK void FMU0_IRQHandler(void);
WEAK void ELE_CMD_IRQHandler(void);
WEAK void ELE_SECURE_IRQHandler(void);
WEAK void ELE_NONSECURE_IRQHandler(void);
WEAK void TRDC0_IRQHandler(void);
WEAK void RTC_Alarm_IRQHandler(void);
WEAK void RTC_Seconds_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void LPTMR1_IRQHandler(void);
WEAK void LPIT0_IRQHandler(void);
WEAK void TPM0_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void LPI2C0_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void I3C0_IRQHandler(void);
WEAK void LPSPI0_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPUART0_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void FLEXIO0_IRQHandler(void);
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
WEAK void GPIOA_INT0_IRQHandler(void);
WEAK void GPIOA_INT1_IRQHandler(void);
WEAK void GPIOB_INT0_IRQHandler(void);
WEAK void GPIOB_INT1_IRQHandler(void);
WEAK void GPIOC_INT0_IRQHandler(void);
WEAK void GPIOC_INT1_IRQHandler(void);
WEAK void GPIOD_INT0_IRQHandler(void);
WEAK void GPIOD_INT1_IRQHandler(void);
WEAK void PORTA_EFT_IRQHandler(void);
WEAK void PORTB_EFT_IRQHandler(void);
WEAK void PORTC_EFT_IRQHandler(void);
WEAK void PORTD_EFT_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void LPCMP0_IRQHandler(void);
WEAK void LPCMP1_IRQHandler(void);
WEAK void VBAT_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void CTI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSCM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WUU0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SFA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FMU0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELE_CMD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELE_SECURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELE_NONSECURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRDC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Alarm_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_Seconds_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I3C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
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
void GPIOA_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOA_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOB_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOB_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOC_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOC_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOD_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIOD_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_EFT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_EFT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_EFT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_EFT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPCMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPCMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void VBAT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
extern void _vStackBase(void);
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
    // Core Level - CM33
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    SecureFault_Handler,               // The secure fault handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - KW45Z41082
    CTI_IRQHandler,            // 16: Cross Trigger Interface interrupt
    CMC0_IRQHandler,           // 17: Core Mode Controller interrupt
    DMA0_CH0_IRQHandler,       // 18: eDMA channel 0 error or transfer complete
    DMA0_CH1_IRQHandler,       // 19: eDMA channel 1 error or transfer complete
    DMA0_CH2_IRQHandler,       // 20: eDMA channel 2 error or transfer complete
    DMA0_CH3_IRQHandler,       // 21: eDMA channel 3 error or transfer complete
    DMA0_CH4_IRQHandler,       // 22: eDMA channel 4 error or transfer complete
    DMA0_CH5_IRQHandler,       // 23: eDMA channel 5 error or transfer complete
    DMA0_CH6_IRQHandler,       // 24: eDMA channel 6 error or transfer complete
    DMA0_CH7_IRQHandler,       // 25: eDMA channel 7 error or transfer complete
    DMA0_CH8_IRQHandler,       // 26: eDMA channel 8 error or transfer complete
    DMA0_CH9_IRQHandler,       // 27: eDMA channel 9 error or transfer complete
    DMA0_CH10_IRQHandler,      // 28: eDMA channel 10 error or transfer complete
    DMA0_CH11_IRQHandler,      // 29: eDMA channel 11 error or transfer complete
    DMA0_CH12_IRQHandler,      // 30: eDMA channel 12 error or transfer complete
    DMA0_CH13_IRQHandler,      // 31: eDMA channel 13 error or transfer complete
    DMA0_CH14_IRQHandler,      // 32: eDMA channel 14 error or transfer complete
    DMA0_CH15_IRQHandler,      // 33: eDMA channel 15 error or transfer complete
    EWM0_IRQHandler,           // 34: External Watchdog Monitor 0 interrupt
    MCM0_IRQHandler,           // 35: Miscellaneous Control Module interrupt
    MSCM0_IRQHandler,          // 36: Miscellaneous System Control Module interrupt
    SPC0_IRQHandler,           // 37: System Power Controller 0 interrupt
    WUU0_IRQHandler,           // 38: Wake-Up Unit 0 interrupt
    WDOG0_IRQHandler,          // 39: Watchdog Timer 0 interrupt
    WDOG1_IRQHandler,          // 40: Watchdog Timer 1 interrupt
    SCG0_IRQHandler,           // 41: System Clock Generator 0 interrupt
    SFA0_IRQHandler,           // 42: Singal Frequency Analyzer 0 interrupt
    FMU0_IRQHandler,           // 43: Flash Memory Unit 0 interrupt
    ELE_CMD_IRQHandler,        // 44: EdgeLock enclave command interface interrupt
    ELE_SECURE_IRQHandler,     // 45: EdgeLock enclave interrupt
    ELE_NONSECURE_IRQHandler,  // 46: EdgeLock enclave non-secure interrupt
    TRDC0_IRQHandler,          // 47: Trusted Resource Domain Controller 0 interrupt
    RTC_Alarm_IRQHandler,      // 48: Real Time Clock 0 alarm interrupt
    RTC_Seconds_IRQHandler,    // 49: Real Time Clock 0 seconds interrupt
    LPTMR0_IRQHandler,         // 50: Low-Power Timer0 interrupt
    LPTMR1_IRQHandler,         // 51: Low-Power Timer1 interrupt
    LPIT0_IRQHandler,          // 52: Low-Power Periodic Interrupt Timer 0 interrupt
    TPM0_IRQHandler,           // 53: Timer / PWM Module 0 interrupt
    TPM1_IRQHandler,           // 54: Timer / PWM Module 1 interrupt
    LPI2C0_IRQHandler,         // 55: Low-Power Inter Integrated Circuit 0 interrupt
    LPI2C1_IRQHandler,         // 56: Low-Power Inter Integrated Circuit 1 interrupt
    I3C0_IRQHandler,           // 57: Improved Inter-Integrated Circuit 0 interrupt
    LPSPI0_IRQHandler,         // 58: Low-Power Serial Peripheral Interface 0 interrupt
    LPSPI1_IRQHandler,         // 59: Low-Power Serial Peripheral Interface 1 interrupt
    LPUART0_IRQHandler,        // 60: Low-Power Universal Asynchronous Receiver/Transmitter 0 interrupt
    LPUART1_IRQHandler,        // 61: Low-Power Universal Asynchronous Receiver/Transmitter 1 interrupt
    FLEXIO0_IRQHandler,        // 62: Flexible Input/Output 0 interrupt
    Reserved63_IRQHandler,     // 63: Reserved interrupt
    Reserved64_IRQHandler,     // 64: Reserved interrupt
    Reserved65_IRQHandler,     // 65: Reserved interrupt
    Reserved66_IRQHandler,     // 66: Reserved interrupt
    Reserved67_IRQHandler,     // 67: Reserved interrupt
    Reserved68_IRQHandler,     // 68: Reserved interrupt
    Reserved69_IRQHandler,     // 69: Reserved interrupt
    Reserved70_IRQHandler,     // 70: Reserved interrupt
    Reserved71_IRQHandler,     // 71: Reserved interrupt
    Reserved72_IRQHandler,     // 72: Reserved interrupt
    Reserved73_IRQHandler,     // 73: Reserved interrupt
    Reserved74_IRQHandler,     // 74: Reserved interrupt
    GPIOA_INT0_IRQHandler,     // 75: General Purpose Input/Output A interrupt 0
    GPIOA_INT1_IRQHandler,     // 76: General Purpose Input/Output A interrupt 1
    GPIOB_INT0_IRQHandler,     // 77: General Purpose Input/Output B interrupt 0
    GPIOB_INT1_IRQHandler,     // 78: General Purpose Input/Output B interrupt 1
    GPIOC_INT0_IRQHandler,     // 79: General Purpose Input/Output C interrupt 0
    GPIOC_INT1_IRQHandler,     // 80: General Purpose Input/Output C interrupt 1
    GPIOD_INT0_IRQHandler,     // 81: General Purpose Input/Output D interrupt 0
    GPIOD_INT1_IRQHandler,     // 82: General Purpose Input/Output D interrupt 1
    PORTA_EFT_IRQHandler,      // 83: PortA EFT interrupt
    PORTB_EFT_IRQHandler,      // 84: PortB EFT interrupt
    PORTC_EFT_IRQHandler,      // 85: PortC EFT interrupt
    PORTD_EFT_IRQHandler,      // 86: PortD EFT interrupt
    ADC0_IRQHandler,           // 87: Analog-to-Digital Converter 0 interrupt
    LPCMP0_IRQHandler,         // 88: Low-Power Comparator 0 interrupt
    LPCMP1_IRQHandler,         // 89: Low-Power Comparator 1 interrupt
    VBAT_IRQHandler,           // 90: Smart Power Switch Domain interrupt
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
    __asm volatile (
        "cpsid i\t\n"
#if !defined(BYPASS_ECC_RAM_INIT)
        "ldr     r0, =0x04000000\t\n"
        "ldr     r1, =.ram_init_ctcm01\t\n"
        "bics.w  r1, #0x10000000\t\n"
        "cmp     r0, r1\t\n"
        "bcc.n   .ram_init_done\t\n"    // Bypass ECC RAM initialization on RAM target, debugger will do the initialization
        ".ram_init_ctcm01:\t\n"         // Initialize ctcm01
        "ldr     r0, =0x4000000\t\n"
        "ldr     r1, =0x4004000\t\n"
        "ldr     r2, =0\t\n"
        "ldr     r3, =0\t\n"
        "ldr     r4, =0\t\n"
        "ldr     r5, =0\t\n"
        ".loop01:\t\n"
        "stmia   r0!, {r2 - r5}\t\n"
        "cmp     r0, r1\t\n"
        "bcc.n   .loop01\t\n"
        "\t\n"
        ".ram_init_stcm012:\t\n"        // Initialize stcm012
        "ldr     r0, =0x20000000\t\n"
        "ldr     r1, =0x20010000\t\n"
        ".loop012:\t\n"
        "stmia   r0!, {r2 - r5}\t\n"
        "cmp     r0, r1\t\n"
        "bcc.n   .loop012\t\n"
        "\t\n"
        ".ram_init_stcm5:\t\n"
        "ldr     r0, =0x2001a000\t\n"
        "ldr     r1, =0x2001c000\t\n"
        ".loop5:\t\n"                   // Initialize stcm5
        "stmia   r0!, {r2 - r5}\t\n"
        "cmp     r0, r1\t\n"
        "bcc.n   .loop5\t\n"
        "\t\n"
        ".ram_init_done:\t\n"
#endif
    );
    // Config VTOR & MSPLIM register
    __asm volatile ("LDR R0, =0xE000ED08  \n"
                    "STR %0, [R0]         \n"
                    "LDR R1, [%0]         \n"
                    "MSR MSP, R1          \n"
                    "MSR MSPLIM, %1       \n"
                    :
                    : "r"(g_pfnVectors), "r"(_vStackBase)
                    : "r0", "r1");

#if defined (__USE_CMSIS)
// If __USE_CMSIS defined, then call CMSIS SystemInit code
    SystemInit();

#else
    // Disable Watchdog
    // Write watchdog update key to unlock
    *((volatile unsigned int *)0x4001B004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x4001B008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *WDOG_CS = (unsigned int *) 0x4001B000;
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

WEAK_AV void MemManage_Handler(void)
{ while(1) {}
}

WEAK_AV void BusFault_Handler(void)
{ while(1) {}
}

WEAK_AV void UsageFault_Handler(void)
{ while(1) {}
}

WEAK_AV void SecureFault_Handler(void)
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
WEAK void CTI_IRQHandler(void)
{   CTI_DriverIRQHandler();
}

WEAK void CMC0_IRQHandler(void)
{   CMC0_DriverIRQHandler();
}

WEAK void DMA0_CH0_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH1_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH2_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH3_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH4_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH5_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH6_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH7_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH8_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH9_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH10_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH11_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH12_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH13_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH14_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void DMA0_CH15_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void EWM0_IRQHandler(void)
{   EWM0_DriverIRQHandler();
}

WEAK void MCM0_IRQHandler(void)
{   MCM0_DriverIRQHandler();
}

WEAK void MSCM0_IRQHandler(void)
{   MSCM0_DriverIRQHandler();
}

WEAK void SPC0_IRQHandler(void)
{   SPC0_DriverIRQHandler();
}

WEAK void WUU0_IRQHandler(void)
{   WUU0_DriverIRQHandler();
}

WEAK void WDOG0_IRQHandler(void)
{   WDOG0_DriverIRQHandler();
}

WEAK void WDOG1_IRQHandler(void)
{   WDOG1_DriverIRQHandler();
}

WEAK void SCG0_IRQHandler(void)
{   SCG0_DriverIRQHandler();
}

WEAK void SFA0_IRQHandler(void)
{   SFA0_DriverIRQHandler();
}

WEAK void FMU0_IRQHandler(void)
{   FMU0_DriverIRQHandler();
}

WEAK void ELE_CMD_IRQHandler(void)
{   ELE_CMD_DriverIRQHandler();
}

WEAK void ELE_SECURE_IRQHandler(void)
{   ELE_SECURE_DriverIRQHandler();
}

WEAK void ELE_NONSECURE_IRQHandler(void)
{   ELE_NONSECURE_DriverIRQHandler();
}

WEAK void TRDC0_IRQHandler(void)
{   TRDC0_DriverIRQHandler();
}

WEAK void RTC_Alarm_IRQHandler(void)
{   RTC_Alarm_DriverIRQHandler();
}

WEAK void RTC_Seconds_IRQHandler(void)
{   RTC_Seconds_DriverIRQHandler();
}

WEAK void LPTMR0_IRQHandler(void)
{   LPTMR0_DriverIRQHandler();
}

WEAK void LPTMR1_IRQHandler(void)
{   LPTMR1_DriverIRQHandler();
}

WEAK void LPIT0_IRQHandler(void)
{   LPIT0_DriverIRQHandler();
}

WEAK void TPM0_IRQHandler(void)
{   TPM0_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK void LPI2C0_IRQHandler(void)
{   LPI2C0_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK void I3C0_IRQHandler(void)
{   I3C0_DriverIRQHandler();
}

WEAK void LPSPI0_IRQHandler(void)
{   LPSPI0_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK void LPUART0_IRQHandler(void)
{   LPUART0_DriverIRQHandler();
}

WEAK void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK void FLEXIO0_IRQHandler(void)
{   FLEXIO0_DriverIRQHandler();
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

WEAK void GPIOA_INT0_IRQHandler(void)
{   GPIOA_INT0_DriverIRQHandler();
}

WEAK void GPIOA_INT1_IRQHandler(void)
{   GPIOA_INT1_DriverIRQHandler();
}

WEAK void GPIOB_INT0_IRQHandler(void)
{   GPIOB_INT0_DriverIRQHandler();
}

WEAK void GPIOB_INT1_IRQHandler(void)
{   GPIOB_INT1_DriverIRQHandler();
}

WEAK void GPIOC_INT0_IRQHandler(void)
{   GPIOC_INT0_DriverIRQHandler();
}

WEAK void GPIOC_INT1_IRQHandler(void)
{   GPIOC_INT1_DriverIRQHandler();
}

WEAK void GPIOD_INT0_IRQHandler(void)
{   GPIOD_INT0_DriverIRQHandler();
}

WEAK void GPIOD_INT1_IRQHandler(void)
{   GPIOD_INT1_DriverIRQHandler();
}

WEAK void PORTA_EFT_IRQHandler(void)
{   PORTA_EFT_DriverIRQHandler();
}

WEAK void PORTB_EFT_IRQHandler(void)
{   PORTB_EFT_DriverIRQHandler();
}

WEAK void PORTC_EFT_IRQHandler(void)
{   PORTC_EFT_DriverIRQHandler();
}

WEAK void PORTD_EFT_IRQHandler(void)
{   PORTD_EFT_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void LPCMP0_IRQHandler(void)
{   LPCMP0_DriverIRQHandler();
}

WEAK void LPCMP1_IRQHandler(void)
{   LPCMP1_DriverIRQHandler();
}

WEAK void VBAT_IRQHandler(void)
{   VBAT_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
