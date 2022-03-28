//*****************************************************************************
// LPC55S36 startup code for use with MCUXpresso IDE
//
// Version : 170921
//*****************************************************************************
//
// Copyright 2016-2021 NXP
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
WEAK void WDT_BOD_IRQHandler(void);
WEAK void DMA0_IRQHandler(void);
WEAK void GINT0_IRQHandler(void);
WEAK void GINT1_IRQHandler(void);
WEAK void PIN_INT0_IRQHandler(void);
WEAK void PIN_INT1_IRQHandler(void);
WEAK void PIN_INT2_IRQHandler(void);
WEAK void PIN_INT3_IRQHandler(void);
WEAK void UTICK0_IRQHandler(void);
WEAK void MRT0_IRQHandler(void);
WEAK void CTIMER0_IRQHandler(void);
WEAK void CTIMER1_IRQHandler(void);
WEAK void SCT0_IRQHandler(void);
WEAK void CTIMER3_IRQHandler(void);
WEAK void FLEXCOMM0_IRQHandler(void);
WEAK void FLEXCOMM1_IRQHandler(void);
WEAK void FLEXCOMM2_IRQHandler(void);
WEAK void FLEXCOMM3_IRQHandler(void);
WEAK void FLEXCOMM4_IRQHandler(void);
WEAK void FLEXCOMM5_IRQHandler(void);
WEAK void FLEXCOMM6_IRQHandler(void);
WEAK void FLEXCOMM7_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void ADC1_IRQHandler(void);
WEAK void ACMP_IRQHandler(void);
WEAK void DMIC_IRQHandler(void);
WEAK void HWVAD0_IRQHandler(void);
WEAK void USB0_NEEDCLK_IRQHandler(void);
WEAK void USB0_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void EZH_ARCH_B0_IRQHandler(void);
WEAK void WAKEUP_IRQHandler(void);
WEAK void PIN_INT4_IRQHandler(void);
WEAK void PIN_INT5_IRQHandler(void);
WEAK void PIN_INT6_IRQHandler(void);
WEAK void PIN_INT7_IRQHandler(void);
WEAK void CTIMER2_IRQHandler(void);
WEAK void CTIMER4_IRQHandler(void);
WEAK void OS_EVENT_IRQHandler(void);
WEAK void FlexSPI0_IRQHandler(void);
WEAK void Reserved56_IRQHandler(void);
WEAK void Reserved57_IRQHandler(void);
WEAK void Reserved58_IRQHandler(void);
WEAK void CAN0_IRQ0_IRQHandler(void);
WEAK void CAN0_IRQ1_IRQHandler(void);
WEAK void SPI_FILTER_IRQHandler(void);
WEAK void Reserved62_IRQHandler(void);
WEAK void Reserved63_IRQHandler(void);
WEAK void Reserved64_IRQHandler(void);
WEAK void SEC_HYPERVISOR_CALL_IRQHandler(void);
WEAK void SEC_GPIO_INT0_IRQ0_IRQHandler(void);
WEAK void SEC_GPIO_INT0_IRQ1_IRQHandler(void);
WEAK void Freqme_IRQHandler(void);
WEAK void SEC_VIO_IRQHandler(void);
WEAK void SHA_IRQHandler(void);
WEAK void PKC_IRQHandler(void);
WEAK void PUF_IRQHandler(void);
WEAK void POWERQUAD_IRQHandler(void);
WEAK void DMA1_IRQHandler(void);
WEAK void FLEXCOMM8_IRQHandler(void);
WEAK void CDOG_IRQHandler(void);
WEAK void Reserved77_IRQHandler(void);
WEAK void I3C0_IRQHandler(void);
WEAK void Reserved79_IRQHandler(void);
WEAK void Reserved80_IRQHandler(void);
WEAK void CSS_IRQ1_IRQHandler(void);
WEAK void Tamper_IRQHandler(void);
WEAK void Analog_Glitch_IRQHandler(void);
WEAK void Reserved84_IRQHandler(void);
WEAK void Reserved85_IRQHandler(void);
WEAK void Reserved86_IRQHandler(void);
WEAK void Reserved87_IRQHandler(void);
WEAK void Reserved88_IRQHandler(void);
WEAK void Reserved89_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void DAC1_IRQHandler(void);
WEAK void DAC2_IRQHandler(void);
WEAK void HSCMP0_IRQHandler(void);
WEAK void HSCMP1_IRQHandler(void);
WEAK void HSCMP2_IRQHandler(void);
WEAK void FLEXPWM0_CAPTURE_IRQHandler(void);
WEAK void FLEXPWM0_FAULT_IRQHandler(void);
WEAK void FLEXPWM0_RELOAD_ERROR_IRQHandler(void);
WEAK void FLEXPWM0_COMPARE0_IRQHandler(void);
WEAK void FLEXPWM0_RELOAD0_IRQHandler(void);
WEAK void FLEXPWM0_COMPARE1_IRQHandler(void);
WEAK void FLEXPWM0_RELOAD1_IRQHandler(void);
WEAK void FLEXPWM0_COMPARE2_IRQHandler(void);
WEAK void FLEXPWM0_RELOAD2_IRQHandler(void);
WEAK void FLEXPWM0_COMPARE3_IRQHandler(void);
WEAK void FLEXPWM0_RELOAD3_IRQHandler(void);
WEAK void FLEXPWM1_CAPTURE_IRQHandler(void);
WEAK void FLEXPWM1_FAULT_IRQHandler(void);
WEAK void FLEXPWM1_RELOAD_ERROR_IRQHandler(void);
WEAK void FLEXPWM1_COMPARE0_IRQHandler(void);
WEAK void FLEXPWM1_RELOAD0_IRQHandler(void);
WEAK void FLEXPWM1_COMPARE1_IRQHandler(void);
WEAK void FLEXPWM1_RELOAD1_IRQHandler(void);
WEAK void FLEXPWM1_COMPARE2_IRQHandler(void);
WEAK void FLEXPWM1_RELOAD2_IRQHandler(void);
WEAK void FLEXPWM1_COMPARE3_IRQHandler(void);
WEAK void FLEXPWM1_RELOAD3_IRQHandler(void);
WEAK void ENC0_COMPARE_IRQHandler(void);
WEAK void ENC0_HOME_IRQHandler(void);
WEAK void ENC0_WDG_IRQHandler(void);
WEAK void ENC0_IDX_IRQHandler(void);
WEAK void ENC1_COMPARE_IRQHandler(void);
WEAK void ENC1_HOME_IRQHandler(void);
WEAK void ENC1_WDG_IRQHandler(void);
WEAK void ENC1_IDX_IRQHandler(void);
WEAK void ITRC0_IRQHandler(void);
WEAK void Reserved127_IRQHandler(void);
WEAK void CSSV2_ERR_IRQHandler(void);
WEAK void PKC_ERR_IRQHandler(void);
WEAK void Reserved130_IRQHandler(void);
WEAK void Reserved131_IRQHandler(void);
WEAK void Reserved132_IRQHandler(void);
WEAK void Reserved133_IRQHandler(void);
WEAK void FLASH_IRQHandler(void);
WEAK void RAM_PARITY_ECC_ERR_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void WDT_BOD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UTICK0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MRT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMIC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HWVAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_NEEDCLK_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EZH_ARCH_B0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WAKEUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OS_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FlexSPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved56_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved57_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved58_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_IRQ0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_IRQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI_FILTER_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved62_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved63_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved64_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEC_HYPERVISOR_CALL_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEC_GPIO_INT0_IRQ0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEC_GPIO_INT0_IRQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Freqme_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEC_VIO_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SHA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PKC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PUF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void POWERQUAD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CDOG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved77_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I3C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved79_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved80_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CSS_IRQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Tamper_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Analog_Glitch_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved84_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved85_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved86_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved87_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved88_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved89_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSCMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSCMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSCMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_CAPTURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_RELOAD_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_COMPARE0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_RELOAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_COMPARE1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_RELOAD1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_COMPARE2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_RELOAD2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_COMPARE3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM0_RELOAD3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_CAPTURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_RELOAD_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_COMPARE0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_RELOAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_COMPARE1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_RELOAD1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_COMPARE2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_RELOAD2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_COMPARE3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXPWM1_RELOAD3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC0_COMPARE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC0_HOME_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC0_WDG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC0_IDX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC1_COMPARE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC1_HOME_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC1_WDG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC1_IDX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ITRC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved127_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CSSV2_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PKC_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved130_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved131_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved132_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved133_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RAM_PARITY_ECC_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
// External declaration for LPC MCU vector table checksum from  Linker Script
//*****************************************************************************
WEAK extern void __valid_user_code_checksum();

//*****************************************************************************
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
    0,                                 // ECRP
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - LPC55S36
    WDT_BOD_IRQHandler,                // 16 : Windowed watchdog timer, Brownout detect, Flash interrupt
    DMA0_IRQHandler,                   // 17 : DMA0 controller
    GINT0_IRQHandler,                  // 18 : GPIO group 0
    GINT1_IRQHandler,                  // 19 : GPIO group 1
    PIN_INT0_IRQHandler,               // 20 : Pin interrupt 0 or pattern match engine slice 0
    PIN_INT1_IRQHandler,               // 21 : Pin interrupt 1or pattern match engine slice 1
    PIN_INT2_IRQHandler,               // 22 : Pin interrupt 2 or pattern match engine slice 2
    PIN_INT3_IRQHandler,               // 23 : Pin interrupt 3 or pattern match engine slice 3
    UTICK0_IRQHandler,                 // 24 : Micro-tick Timer
    MRT0_IRQHandler,                   // 25 : Multi-rate timer
    CTIMER0_IRQHandler,                // 26 : Standard counter/timer CTIMER0
    CTIMER1_IRQHandler,                // 27 : Standard counter/timer CTIMER1
    SCT0_IRQHandler,                   // 28 : SCTimer/PWM
    CTIMER3_IRQHandler,                // 29 : Standard counter/timer CTIMER3
    FLEXCOMM0_IRQHandler,              // 30 : Flexcomm Interface 0 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM1_IRQHandler,              // 31 : Flexcomm Interface 1 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM2_IRQHandler,              // 32 : Flexcomm Interface 2 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM3_IRQHandler,              // 33 : Flexcomm Interface 3 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM4_IRQHandler,              // 34 : Flexcomm Interface 4 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM5_IRQHandler,              // 35 : Flexcomm Interface 5 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM6_IRQHandler,              // 36 : Flexcomm Interface 6 (USART, SPI, I2C, I2S, FLEXCOMM)
    FLEXCOMM7_IRQHandler,              // 37 : Flexcomm Interface 7 (USART, SPI, I2C, I2S, FLEXCOMM)
    ADC0_IRQHandler,                   // 38 : ADC0
    ADC1_IRQHandler,                   // 39 : ADC1
    ACMP_IRQHandler,                   // 40 : ACMP interrupts
    DMIC_IRQHandler,                   // 41 : Digital microphone and DMIC subsystem
    HWVAD0_IRQHandler,                 // 42 : Hardware Voice Activity Detector
    USB0_NEEDCLK_IRQHandler,           // 43 : USB Activity Wake-up Interrupt
    USB0_IRQHandler,                   // 44 : USB device
    RTC_IRQHandler,                    // 45 : RTC alarm and wake-up interrupts
    EZH_ARCH_B0_IRQHandler,            // 46 : EZH interrupt
    WAKEUP_IRQHandler,                 // 47 : Wakeup interrupt
    PIN_INT4_IRQHandler,               // 48 : Pin interrupt 4 or pattern match engine slice 4 int
    PIN_INT5_IRQHandler,               // 49 : Pin interrupt 5 or pattern match engine slice 5 int
    PIN_INT6_IRQHandler,               // 50 : Pin interrupt 6 or pattern match engine slice 6 int
    PIN_INT7_IRQHandler,               // 51 : Pin interrupt 7 or pattern match engine slice 7 int
    CTIMER2_IRQHandler,                // 52 : Standard counter/timer CTIMER2
    CTIMER4_IRQHandler,                // 53 : Standard counter/timer CTIMER4
    OS_EVENT_IRQHandler,               // 54 : OS_EVENT_TIMER and OS_EVENT_WAKEUP interrupts
    FlexSPI0_IRQHandler,               // 55 : FlexSPI interrupt
    Reserved56_IRQHandler,             // 56 : Reserved interrupt
    Reserved57_IRQHandler,             // 57 : Reserved interrupt
    Reserved58_IRQHandler,             // 58 : Reserved interrupt
    CAN0_IRQ0_IRQHandler,              // 59 : CAN0 interrupt0
    CAN0_IRQ1_IRQHandler,              // 60 : CAN0 interrupt1
    SPI_FILTER_IRQHandler,             // 61 : SPI Filter interrupt
    Reserved62_IRQHandler,             // 62 : Reserved interrupt
    Reserved63_IRQHandler,             // 63 : Reserved interrupt
    Reserved64_IRQHandler,             // 64 : Reserved interrupt
    SEC_HYPERVISOR_CALL_IRQHandler,    // 65 : SEC_HYPERVISOR_CALL interrupt
    SEC_GPIO_INT0_IRQ0_IRQHandler,     // 66 : SEC_GPIO_INT00 interrupt
    SEC_GPIO_INT0_IRQ1_IRQHandler,     // 67 : SEC_GPIO_INT01 interrupt
    Freqme_IRQHandler,                 // 68 : frequency measure interrupt
    SEC_VIO_IRQHandler,                // 69 : SEC_VIO interrupt
    SHA_IRQHandler,                    // 70 : SHA interrupt
    PKC_IRQHandler,                    // 71 : CASPER interrupt
    PUF_IRQHandler,                    // 72 : PUF interrupt
    POWERQUAD_IRQHandler,              // 73 : PowerQuad interrupt
    DMA1_IRQHandler,                   // 74 : DMA1 interrupt
    FLEXCOMM8_IRQHandler,              // 75 : LSPI_HS interrupt
    CDOG_IRQHandler,                   // 76 : CodeWDG interrupt
    Reserved77_IRQHandler,             // 77 : Reserved interrupt
    I3C0_IRQHandler,                   // 78 : I3C interrupt
    Reserved79_IRQHandler,             // 79 : Reserved interrupt
    Reserved80_IRQHandler,             // 80 : Reserved interrupt
    CSS_IRQ1_IRQHandler,               // 81 : CSS_IRQ1
    Tamper_IRQHandler,                 // 82 : Tamper
    Analog_Glitch_IRQHandler,          // 83 : Analog_Glitch
    Reserved84_IRQHandler,             // 84 : Reserved interrupt
    Reserved85_IRQHandler,             // 85 : Reserved interrupt
    Reserved86_IRQHandler,             // 86 : Reserved interrupt
    Reserved87_IRQHandler,             // 87 : Reserved interrupt
    Reserved88_IRQHandler,             // 88 : Reserved interrupt
    Reserved89_IRQHandler,             // 89 : Reserved interrupt
    DAC0_IRQHandler,                   // 90 : dac0 interrupt
    DAC1_IRQHandler,                   // 91 : dac1 interrupt
    DAC2_IRQHandler,                   // 92 : dac2 interrupt
    HSCMP0_IRQHandler,                 // 93 : hscmp0 interrupt
    HSCMP1_IRQHandler,                 // 94 : hscmp1 interrupt
    HSCMP2_IRQHandler,                 // 95 : hscmp2 interrupt
    FLEXPWM0_CAPTURE_IRQHandler,       // 96 : flexpwm0_capture interrupt
    FLEXPWM0_FAULT_IRQHandler,         // 97 : flexpwm0_fault interrupt
    FLEXPWM0_RELOAD_ERROR_IRQHandler,  // 98 : flexpwm0_reload_error interrupt
    FLEXPWM0_COMPARE0_IRQHandler,      // 99 : flexpwm0_compare0 interrupt
    FLEXPWM0_RELOAD0_IRQHandler,       // 100: flexpwm0_reload0 interrupt
    FLEXPWM0_COMPARE1_IRQHandler,      // 101: flexpwm0_compare1 interrupt
    FLEXPWM0_RELOAD1_IRQHandler,       // 102: flexpwm0_reload1 interrupt
    FLEXPWM0_COMPARE2_IRQHandler,      // 103: flexpwm0_compare2 interrupt
    FLEXPWM0_RELOAD2_IRQHandler,       // 104: flexpwm0_reload2 interrupt
    FLEXPWM0_COMPARE3_IRQHandler,      // 105: flexpwm0_compare3 interrupt
    FLEXPWM0_RELOAD3_IRQHandler,       // 106: flexpwm0_reload3 interrupt
    FLEXPWM1_CAPTURE_IRQHandler,       // 107: flexpwm1_capture interrupt
    FLEXPWM1_FAULT_IRQHandler,         // 108: flexpwm1_fault interrupt
    FLEXPWM1_RELOAD_ERROR_IRQHandler,  // 109: flexpwm1_reload_error interrupt
    FLEXPWM1_COMPARE0_IRQHandler,      // 110: flexpwm1_compare0 interrupt
    FLEXPWM1_RELOAD0_IRQHandler,       // 111: flexpwm1_reload0 interrupt
    FLEXPWM1_COMPARE1_IRQHandler,      // 112: flexpwm1_compare1 interrupt
    FLEXPWM1_RELOAD1_IRQHandler,       // 113: flexpwm1_reload1 interrupt
    FLEXPWM1_COMPARE2_IRQHandler,      // 114: flexpwm1_compare2 interrupt
    FLEXPWM1_RELOAD2_IRQHandler,       // 115: flexpwm1_reload2 interrupt
    FLEXPWM1_COMPARE3_IRQHandler,      // 116: flexpwm1_compare3 interrupt
    FLEXPWM1_RELOAD3_IRQHandler,       // 117: flexpwm1_reload3 interrupt
    ENC0_COMPARE_IRQHandler,           // 118: enc0_compare interrupt
    ENC0_HOME_IRQHandler,              // 119: enc0_home interrupt
    ENC0_WDG_IRQHandler,               // 120: enc0_wdg interrupt
    ENC0_IDX_IRQHandler,               // 121: enc0_idx interrupt
    ENC1_COMPARE_IRQHandler,           // 122: enc1_compare interrupt
    ENC1_HOME_IRQHandler,              // 123: enc1_home interrupt
    ENC1_WDG_IRQHandler,               // 124: enc1_wdg interrupt
    ENC1_IDX_IRQHandler,               // 125: enc1_idx interrupt
    ITRC0_IRQHandler,                  // 126: itrc0 interrupt
    Reserved127_IRQHandler,            // 127: Reserved interrupt
    CSSV2_ERR_IRQHandler,              // 128: cssv2_err interrupt
    PKC_ERR_IRQHandler,                // 129: pkc_err interrupt
    Reserved130_IRQHandler,            // 130: Reserved interrupt
    Reserved131_IRQHandler,            // 131: Reserved interrupt
    Reserved132_IRQHandler,            // 132: Reserved interrupt
    Reserved133_IRQHandler,            // 133: Reserved interrupt
    FLASH_IRQHandler,                  // 134: flash interrupt
    RAM_PARITY_ECC_ERR_IRQHandler,     // 135: ram_parity_ecc_err interrupt
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
WEAK void WDT_BOD_IRQHandler(void)
{   WDT_BOD_DriverIRQHandler();
}

WEAK void DMA0_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void GINT0_IRQHandler(void)
{   GINT0_DriverIRQHandler();
}

WEAK void GINT1_IRQHandler(void)
{   GINT1_DriverIRQHandler();
}

WEAK void PIN_INT0_IRQHandler(void)
{   PIN_INT0_DriverIRQHandler();
}

WEAK void PIN_INT1_IRQHandler(void)
{   PIN_INT1_DriverIRQHandler();
}

WEAK void PIN_INT2_IRQHandler(void)
{   PIN_INT2_DriverIRQHandler();
}

WEAK void PIN_INT3_IRQHandler(void)
{   PIN_INT3_DriverIRQHandler();
}

WEAK void UTICK0_IRQHandler(void)
{   UTICK0_DriverIRQHandler();
}

WEAK void MRT0_IRQHandler(void)
{   MRT0_DriverIRQHandler();
}

WEAK void CTIMER0_IRQHandler(void)
{   CTIMER0_DriverIRQHandler();
}

WEAK void CTIMER1_IRQHandler(void)
{   CTIMER1_DriverIRQHandler();
}

WEAK void SCT0_IRQHandler(void)
{   SCT0_DriverIRQHandler();
}

WEAK void CTIMER3_IRQHandler(void)
{   CTIMER3_DriverIRQHandler();
}

WEAK void FLEXCOMM0_IRQHandler(void)
{   FLEXCOMM0_DriverIRQHandler();
}

WEAK void FLEXCOMM1_IRQHandler(void)
{   FLEXCOMM1_DriverIRQHandler();
}

WEAK void FLEXCOMM2_IRQHandler(void)
{   FLEXCOMM2_DriverIRQHandler();
}

WEAK void FLEXCOMM3_IRQHandler(void)
{   FLEXCOMM3_DriverIRQHandler();
}

WEAK void FLEXCOMM4_IRQHandler(void)
{   FLEXCOMM4_DriverIRQHandler();
}

WEAK void FLEXCOMM5_IRQHandler(void)
{   FLEXCOMM5_DriverIRQHandler();
}

WEAK void FLEXCOMM6_IRQHandler(void)
{   FLEXCOMM6_DriverIRQHandler();
}

WEAK void FLEXCOMM7_IRQHandler(void)
{   FLEXCOMM7_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)
{   ADC1_DriverIRQHandler();
}

WEAK void ACMP_IRQHandler(void)
{   ACMP_DriverIRQHandler();
}

WEAK void DMIC_IRQHandler(void)
{   DMIC_DriverIRQHandler();
}

WEAK void HWVAD0_IRQHandler(void)
{   HWVAD0_DriverIRQHandler();
}

WEAK void USB0_NEEDCLK_IRQHandler(void)
{   USB0_NEEDCLK_DriverIRQHandler();
}

WEAK void USB0_IRQHandler(void)
{   USB0_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void EZH_ARCH_B0_IRQHandler(void)
{   EZH_ARCH_B0_DriverIRQHandler();
}

WEAK void WAKEUP_IRQHandler(void)
{   WAKEUP_DriverIRQHandler();
}

WEAK void PIN_INT4_IRQHandler(void)
{   PIN_INT4_DriverIRQHandler();
}

WEAK void PIN_INT5_IRQHandler(void)
{   PIN_INT5_DriverIRQHandler();
}

WEAK void PIN_INT6_IRQHandler(void)
{   PIN_INT6_DriverIRQHandler();
}

WEAK void PIN_INT7_IRQHandler(void)
{   PIN_INT7_DriverIRQHandler();
}

WEAK void CTIMER2_IRQHandler(void)
{   CTIMER2_DriverIRQHandler();
}

WEAK void CTIMER4_IRQHandler(void)
{   CTIMER4_DriverIRQHandler();
}

WEAK void OS_EVENT_IRQHandler(void)
{   OS_EVENT_DriverIRQHandler();
}

WEAK void FlexSPI0_IRQHandler(void)
{   FlexSPI0_DriverIRQHandler();
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

WEAK void CAN0_IRQ0_IRQHandler(void)
{   CAN0_IRQ0_DriverIRQHandler();
}

WEAK void CAN0_IRQ1_IRQHandler(void)
{   CAN0_IRQ1_DriverIRQHandler();
}

WEAK void SPI_FILTER_IRQHandler(void)
{   SPI_FILTER_DriverIRQHandler();
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

WEAK void SEC_HYPERVISOR_CALL_IRQHandler(void)
{   SEC_HYPERVISOR_CALL_DriverIRQHandler();
}

WEAK void SEC_GPIO_INT0_IRQ0_IRQHandler(void)
{   SEC_GPIO_INT0_IRQ0_DriverIRQHandler();
}

WEAK void SEC_GPIO_INT0_IRQ1_IRQHandler(void)
{   SEC_GPIO_INT0_IRQ1_DriverIRQHandler();
}

WEAK void Freqme_IRQHandler(void)
{   Freqme_DriverIRQHandler();
}

WEAK void SEC_VIO_IRQHandler(void)
{   SEC_VIO_DriverIRQHandler();
}

WEAK void SHA_IRQHandler(void)
{   SHA_DriverIRQHandler();
}

WEAK void PKC_IRQHandler(void)
{   PKC_DriverIRQHandler();
}

WEAK void PUF_IRQHandler(void)
{   PUF_DriverIRQHandler();
}

WEAK void POWERQUAD_IRQHandler(void)
{   POWERQUAD_DriverIRQHandler();
}

WEAK void DMA1_IRQHandler(void)
{   DMA1_DriverIRQHandler();
}

WEAK void FLEXCOMM8_IRQHandler(void)
{   FLEXCOMM8_DriverIRQHandler();
}

WEAK void CDOG_IRQHandler(void)
{   CDOG_DriverIRQHandler();
}

WEAK void Reserved77_IRQHandler(void)
{   Reserved77_DriverIRQHandler();
}

WEAK void I3C0_IRQHandler(void)
{   I3C0_DriverIRQHandler();
}

WEAK void Reserved79_IRQHandler(void)
{   Reserved79_DriverIRQHandler();
}

WEAK void Reserved80_IRQHandler(void)
{   Reserved80_DriverIRQHandler();
}

WEAK void CSS_IRQ1_IRQHandler(void)
{   CSS_IRQ1_DriverIRQHandler();
}

WEAK void Tamper_IRQHandler(void)
{   Tamper_DriverIRQHandler();
}

WEAK void Analog_Glitch_IRQHandler(void)
{   Analog_Glitch_DriverIRQHandler();
}

WEAK void Reserved84_IRQHandler(void)
{   Reserved84_DriverIRQHandler();
}

WEAK void Reserved85_IRQHandler(void)
{   Reserved85_DriverIRQHandler();
}

WEAK void Reserved86_IRQHandler(void)
{   Reserved86_DriverIRQHandler();
}

WEAK void Reserved87_IRQHandler(void)
{   Reserved87_DriverIRQHandler();
}

WEAK void Reserved88_IRQHandler(void)
{   Reserved88_DriverIRQHandler();
}

WEAK void Reserved89_IRQHandler(void)
{   Reserved89_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK void DAC1_IRQHandler(void)
{   DAC1_DriverIRQHandler();
}

WEAK void DAC2_IRQHandler(void)
{   DAC2_DriverIRQHandler();
}

WEAK void HSCMP0_IRQHandler(void)
{   HSCMP0_DriverIRQHandler();
}

WEAK void HSCMP1_IRQHandler(void)
{   HSCMP1_DriverIRQHandler();
}

WEAK void HSCMP2_IRQHandler(void)
{   HSCMP2_DriverIRQHandler();
}

WEAK void FLEXPWM0_CAPTURE_IRQHandler(void)
{   FLEXPWM0_CAPTURE_DriverIRQHandler();
}

WEAK void FLEXPWM0_FAULT_IRQHandler(void)
{   FLEXPWM0_FAULT_DriverIRQHandler();
}

WEAK void FLEXPWM0_RELOAD_ERROR_IRQHandler(void)
{   FLEXPWM0_RELOAD_ERROR_DriverIRQHandler();
}

WEAK void FLEXPWM0_COMPARE0_IRQHandler(void)
{   FLEXPWM0_COMPARE0_DriverIRQHandler();
}

WEAK void FLEXPWM0_RELOAD0_IRQHandler(void)
{   FLEXPWM0_RELOAD0_DriverIRQHandler();
}

WEAK void FLEXPWM0_COMPARE1_IRQHandler(void)
{   FLEXPWM0_COMPARE1_DriverIRQHandler();
}

WEAK void FLEXPWM0_RELOAD1_IRQHandler(void)
{   FLEXPWM0_RELOAD1_DriverIRQHandler();
}

WEAK void FLEXPWM0_COMPARE2_IRQHandler(void)
{   FLEXPWM0_COMPARE2_DriverIRQHandler();
}

WEAK void FLEXPWM0_RELOAD2_IRQHandler(void)
{   FLEXPWM0_RELOAD2_DriverIRQHandler();
}

WEAK void FLEXPWM0_COMPARE3_IRQHandler(void)
{   FLEXPWM0_COMPARE3_DriverIRQHandler();
}

WEAK void FLEXPWM0_RELOAD3_IRQHandler(void)
{   FLEXPWM0_RELOAD3_DriverIRQHandler();
}

WEAK void FLEXPWM1_CAPTURE_IRQHandler(void)
{   FLEXPWM1_CAPTURE_DriverIRQHandler();
}

WEAK void FLEXPWM1_FAULT_IRQHandler(void)
{   FLEXPWM1_FAULT_DriverIRQHandler();
}

WEAK void FLEXPWM1_RELOAD_ERROR_IRQHandler(void)
{   FLEXPWM1_RELOAD_ERROR_DriverIRQHandler();
}

WEAK void FLEXPWM1_COMPARE0_IRQHandler(void)
{   FLEXPWM1_COMPARE0_DriverIRQHandler();
}

WEAK void FLEXPWM1_RELOAD0_IRQHandler(void)
{   FLEXPWM1_RELOAD0_DriverIRQHandler();
}

WEAK void FLEXPWM1_COMPARE1_IRQHandler(void)
{   FLEXPWM1_COMPARE1_DriverIRQHandler();
}

WEAK void FLEXPWM1_RELOAD1_IRQHandler(void)
{   FLEXPWM1_RELOAD1_DriverIRQHandler();
}

WEAK void FLEXPWM1_COMPARE2_IRQHandler(void)
{   FLEXPWM1_COMPARE2_DriverIRQHandler();
}

WEAK void FLEXPWM1_RELOAD2_IRQHandler(void)
{   FLEXPWM1_RELOAD2_DriverIRQHandler();
}

WEAK void FLEXPWM1_COMPARE3_IRQHandler(void)
{   FLEXPWM1_COMPARE3_DriverIRQHandler();
}

WEAK void FLEXPWM1_RELOAD3_IRQHandler(void)
{   FLEXPWM1_RELOAD3_DriverIRQHandler();
}

WEAK void ENC0_COMPARE_IRQHandler(void)
{   ENC0_COMPARE_DriverIRQHandler();
}

WEAK void ENC0_HOME_IRQHandler(void)
{   ENC0_HOME_DriverIRQHandler();
}

WEAK void ENC0_WDG_IRQHandler(void)
{   ENC0_WDG_DriverIRQHandler();
}

WEAK void ENC0_IDX_IRQHandler(void)
{   ENC0_IDX_DriverIRQHandler();
}

WEAK void ENC1_COMPARE_IRQHandler(void)
{   ENC1_COMPARE_DriverIRQHandler();
}

WEAK void ENC1_HOME_IRQHandler(void)
{   ENC1_HOME_DriverIRQHandler();
}

WEAK void ENC1_WDG_IRQHandler(void)
{   ENC1_WDG_DriverIRQHandler();
}

WEAK void ENC1_IDX_IRQHandler(void)
{   ENC1_IDX_DriverIRQHandler();
}

WEAK void ITRC0_IRQHandler(void)
{   ITRC0_DriverIRQHandler();
}

WEAK void Reserved127_IRQHandler(void)
{   Reserved127_DriverIRQHandler();
}

WEAK void CSSV2_ERR_IRQHandler(void)
{   CSSV2_ERR_DriverIRQHandler();
}

WEAK void PKC_ERR_IRQHandler(void)
{   PKC_ERR_DriverIRQHandler();
}

WEAK void Reserved130_IRQHandler(void)
{   Reserved130_DriverIRQHandler();
}

WEAK void Reserved131_IRQHandler(void)
{   Reserved131_DriverIRQHandler();
}

WEAK void Reserved132_IRQHandler(void)
{   Reserved132_DriverIRQHandler();
}

WEAK void Reserved133_IRQHandler(void)
{   Reserved133_DriverIRQHandler();
}

WEAK void FLASH_IRQHandler(void)
{   FLASH_DriverIRQHandler();
}

WEAK void RAM_PARITY_ECC_ERR_IRQHandler(void)
{   RAM_PARITY_ECC_ERR_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
