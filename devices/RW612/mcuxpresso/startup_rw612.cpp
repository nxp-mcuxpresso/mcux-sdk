//*****************************************************************************
// RW612 startup code for use with MCUXpresso IDE
//
// Version : 161122
//*****************************************************************************
//
// Copyright 2016-2022 NXP
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
WEAK void WDT0_IRQHandler(void);
WEAK void DMA0_IRQHandler(void);
WEAK void GPIO_INTA_IRQHandler(void);
WEAK void GPIO_INTB_IRQHandler(void);
WEAK void PIN_INT0_IRQHandler(void);
WEAK void PIN_INT1_IRQHandler(void);
WEAK void PIN_INT2_IRQHandler(void);
WEAK void PIN_INT3_IRQHandler(void);
WEAK void UTICK_IRQHandler(void);
WEAK void MRT0_IRQHandler(void);
WEAK void CTIMER0_IRQHandler(void);
WEAK void CTIMER1_IRQHandler(void);
WEAK void SCT0_IRQHandler(void);
WEAK void CTIMER3_IRQHandler(void);
WEAK void FLEXCOMM0_IRQHandler(void);
WEAK void FLEXCOMM1_IRQHandler(void);
WEAK void FLEXCOMM2_IRQHandler(void);
WEAK void FLEXCOMM3_IRQHandler(void);
WEAK void Reserved34_IRQHandler(void);
WEAK void Reserved35_IRQHandler(void);
WEAK void FLEXCOMM14_IRQHandler(void);
WEAK void Reserved37_IRQHandler(void);
WEAK void Reserved38_IRQHandler(void);
WEAK void MRT1_IRQHandler(void);
WEAK void Reserved40_IRQHandler(void);
WEAK void DMIC0_IRQHandler(void);
WEAK void WFD_IRQHandler(void);
WEAK void HYPERVISOR_IRQHandler(void);
WEAK void SECUREVIOLATION_IRQHandler(void);
WEAK void HWVAD0_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void Reserved47_IRQHandler(void);
WEAK void RTC_IRQHandler(void);
WEAK void Reserved49_IRQHandler(void);
WEAK void Reserved50_IRQHandler(void);
WEAK void PIN_INT4_IRQHandler(void);
WEAK void PIN_INT5_IRQHandler(void);
WEAK void PIN_INT6_IRQHandler(void);
WEAK void PIN_INT7_IRQHandler(void);
WEAK void CTIMER2_IRQHandler(void);
WEAK void CTIMER4_IRQHandler(void);
WEAK void OS_EVENT_IRQHandler(void);
WEAK void FLEXSPI_IRQHandler(void);
WEAK void Reserved59_IRQHandler(void);
WEAK void Reserved60_IRQHandler(void);
WEAK void Reserved61_IRQHandler(void);
WEAK void SDU_IRQHandler(void);
WEAK void SGPIO_INTA_IRQHandler(void);
WEAK void SGPIO_INTB_IRQHandler(void);
WEAK void Reserved65_IRQHandler(void);
WEAK void USB_IRQHandler(void);
WEAK void Reserved67_IRQHandler(void);
WEAK void Reserved68_IRQHandler(void);
WEAK void Reserved69_IRQHandler(void);
WEAK void DMA1_IRQHandler(void);
WEAK void PUF_IRQHandler(void);
WEAK void POWERQUAD_IRQHandler(void);
WEAK void Reserved73_IRQHandler(void);
WEAK void Reserved74_IRQHandler(void);
WEAK void Reserved75_IRQHandler(void);
WEAK void Reserved76_IRQHandler(void);
WEAK void LCDIC_IRQHandler(void);
WEAK void CAPT_PULSE_IRQHandler(void);
WEAK void Reserved79_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE0_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE1_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE2_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE3_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE4_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE5_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE6_IRQHandler(void);
WEAK void WL_MCI_WAKEUP_DONE7_IRQHandler(void);
WEAK void WL_MCI_WAKEUP0_IRQHandler(void);
WEAK void WL_MCI_WAKEUP1_IRQHandler(void);
WEAK void WL_MCI_INT0_IRQHandler(void);
WEAK void WL_MCI_INT1_IRQHandler(void);
WEAK void WL_MCI_INT2_IRQHandler(void);
WEAK void WL_MCI_INT3_IRQHandler(void);
WEAK void WL_MCI_INT4_IRQHandler(void);
WEAK void WL_MCI_INT5_IRQHandler(void);
WEAK void WL_MCI_INT6_IRQHandler(void);
WEAK void WL_MCI_INT7_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE0_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE1_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE2_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE3_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE4_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE5_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE6_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP_DONE7_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP0_IRQHandler(void);
WEAK void BLE_MCI_WAKEUP1_IRQHandler(void);
WEAK void BLE_MCI_INT0_IRQHandler(void);
WEAK void BLE_MCI_INT1_IRQHandler(void);
WEAK void BLE_MCI_INT2_IRQHandler(void);
WEAK void BLE_MCI_INT3_IRQHandler(void);
WEAK void BLE_MCI_INT4_IRQHandler(void);
WEAK void BLE_MCI_INT5_IRQHandler(void);
WEAK void BLE_MCI_INT6_IRQHandler(void);
WEAK void BLE_MCI_INT7_IRQHandler(void);
WEAK void PIN0_INT_IRQHandler(void);
WEAK void PIN1_INT_IRQHandler(void);
WEAK void ELS_IRQHandler(void);
WEAK void ELS_GDET_IRQ_IRQHandler(void);
WEAK void ELS_GDET_ERR_IRQHandler(void);
WEAK void PKC_IRQHandler(void);
WEAK void PKC_ERR_IRQHandler(void);
WEAK void CDOG_IRQHandler(void);
WEAK void GAU_GPDAC_INT_FUNC11_IRQHandler(void);
WEAK void GAU_ACOMP_INT_WKUP11_IRQHandler(void);
WEAK void GAU_ACOMP_INT_FUNC11_IRQHandler(void);
WEAK void GAU_GPADC1_INT_FUNC11_IRQHandler(void);
WEAK void GAU_GPADC0_INT_FUNC11_IRQHandler(void);
WEAK void USIM_IRQHandler(void);
WEAK void OCOTP_IRQHandler(void);
WEAK void ENET_IRQHandler(void);
WEAK void ENET_TIMER_IRQHandler(void);
WEAK void BOD_1_85_INT_IRQHandler(void);
WEAK void BOD_1_85_NEG_IRQHandler(void);
WEAK void ITRC_IRQHandler(void);
WEAK void BTU_HOST_TRIGGER0_IRQHandler(void);
WEAK void BTU_HOST_TRIGGER1_IRQHandler(void);
WEAK void BTU_HOST_TRIGGER2_IRQHandler(void);
WEAK void TRNG_IRQHandler(void);
WEAK void AHB_MEM_ACC_CHECKER_VIO_INT_C_OR_IRQHandler(void);
WEAK void AHB_MEM_ACC_CHECKER_VIO_INT_S_OR_IRQHandler(void);
WEAK void WL_ACC_INT_IRQHandler(void);
WEAK void BLE_ACC_INT_IRQHandler(void);
WEAK void GDMA_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void WDT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_INTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO_INTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UTICK_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MRT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved34_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved35_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXCOMM14_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved38_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MRT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved40_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMIC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WFD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HYPERVISOR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SECUREVIOLATION_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HWVAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved47_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved49_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved50_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CTIMER4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OS_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved59_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved60_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved61_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SDU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SGPIO_INTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SGPIO_INTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved65_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved67_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved68_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved69_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PUF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void POWERQUAD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved73_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved74_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved75_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved76_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LCDIC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAPT_PULSE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved79_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP_DONE7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_WAKEUP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_MCI_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP_DONE7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_WAKEUP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_MCI_INT7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN0_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIN1_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELS_GDET_IRQ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ELS_GDET_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PKC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PKC_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CDOG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GAU_GPDAC_INT_FUNC11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GAU_ACOMP_INT_WKUP11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GAU_ACOMP_INT_FUNC11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GAU_GPADC1_INT_FUNC11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GAU_GPADC0_INT_FUNC11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USIM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void OCOTP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENET_TIMER_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_1_85_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_1_85_NEG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ITRC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BTU_HOST_TRIGGER0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BTU_HOST_TRIGGER1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BTU_HOST_TRIGGER2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void AHB_MEM_ACC_CHECKER_VIO_INT_C_OR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void AHB_MEM_ACC_CHECKER_VIO_INT_S_OR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WL_ACC_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BLE_ACC_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GDMA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
extern void _image_size(void);
//*****************************************************************************
// External declaration for the pointer to the stack base from the Linker Script
//*****************************************************************************
extern void _vStackBase(void);
//*****************************************************************************
// External declaration for image type and load address from  Linker Script
//*****************************************************************************
WEAK extern void __imghdr_loadaddress();
WEAK extern void __imghdr_imagetype();

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
    NMI_Handler,                       // NMI Handler
    HardFault_Handler,                 // Hard Fault Handler
    MemManage_Handler,                 // MPU Fault Handler
    BusFault_Handler,                  // Bus Fault Handler
    UsageFault_Handler,                // Usage Fault Handler
    SecureFault_Handler,               // Secure Fault Handler
#if (defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE & 0x2))
    (void (*)())0x100000,                // Image length
#else
    (void (*)())((unsigned)_image_size), // Image length
#endif
    __imghdr_imagetype,                // Image type
    0,                                 // Reserved
    SVC_Handler,                       // SVCall Handler
    DebugMon_Handler,                  // Debug Monitor Handler
    (void (*)())g_pfnVectors,          // Image load address
    PendSV_Handler,                    // PendSV Handler
    SysTick_Handler,                   // SysTick Handler

    // Chip Level - RW612
    WDT0_IRQHandler,                          // 16 : Windowed watchdog timer 0 (CM33 watchdog)
    DMA0_IRQHandler,                          // 17 : DMA controller 0 (secure or CM33 DMA)
    GPIO_INTA_IRQHandler,                         // 18 : GPIO interrupt A
    GPIO_INTB_IRQHandler,                         // 19 : GPIO interrupt B
    PIN_INT0_IRQHandler,                          // 20 : Pin interrupt 0 or pattern match engine slice 0 int
    PIN_INT1_IRQHandler,                          // 21 : Pin interrupt 1 or pattern match engine slice 1 int
    PIN_INT2_IRQHandler,                          // 22 : Pin interrupt 2 or pattern match engine slice 2 int
    PIN_INT3_IRQHandler,                          // 23 : Pin interrupt 3 or pattern match engine slice 3 int
    UTICK_IRQHandler,                          // 24 : Micro-tick Timer
    MRT0_IRQHandler,                          // 25 : Multi-Rate Timer. Global MRT interrupts
    CTIMER0_IRQHandler,                          // 26 : Standard counter/timer CTIMER0
    CTIMER1_IRQHandler,                          // 27 : Standard counter/timer CTIMER1
    SCT0_IRQHandler,                          // 28 : SCTimer/PWM
    CTIMER3_IRQHandler,                          // 29 : Standard counter/timer CTIMER3
    FLEXCOMM0_IRQHandler,                         // 30 : Flexcomm Interface 0 (USART, SPI, I2C, I2S)
    FLEXCOMM1_IRQHandler,                         // 31 : Flexcomm Interface 1 (USART, SPI, I2C, I2S)
    FLEXCOMM2_IRQHandler,                         // 32 : Flexcomm Interface 2 (USART, SPI, I2C, I2S)
    FLEXCOMM3_IRQHandler,                         // 33 : Flexcomm Interface 3 (USART, SPI, I2C, I2S)
    Reserved34_IRQHandler,                        // 34 : Reserved interrupt
    Reserved35_IRQHandler,                        // 35 : Reserved interrupt
    FLEXCOMM14_IRQHandler,                        // 36 : Flexcomm Interface 14 (USART, SPI, I2C, I2S)
    Reserved37_IRQHandler,                        // 37 : Reserved interrupt
    Reserved38_IRQHandler,                        // 38 : Reserved interrupt
    MRT1_IRQHandler,                          // 39 : Free Multi-rate timer. Global MRT interrupts
    Reserved40_IRQHandler,                        // 40 : Reserved interrupt
    DMIC0_IRQHandler,                          // 41 : Digital microphone and DMIC subsystem
    WFD_IRQHandler,                          // 42 : Wakeup From Deepsleep
    HYPERVISOR_IRQHandler,                        // 43 : Hypervisor service software interrupt
    SECUREVIOLATION_IRQHandler,                   // 44 : Secure violation
    HWVAD0_IRQHandler,                          // 45 : Hardware Voice Activity Detector
    Reserved46_IRQHandler,                        // 46 : Reserved interrupt
    Reserved47_IRQHandler,                        // 47 : Reserved interrupt
    RTC_IRQHandler,                          // 48 : RTC alarm and wake-up
    Reserved49_IRQHandler,                        // 49 : Reserved interrupt
    Reserved50_IRQHandler,                        // 50 : Reserved interrupt
    PIN_INT4_IRQHandler,                          // 51 : Pin interrupt 4 or pattern match engine slice 4 int
    PIN_INT5_IRQHandler,                          // 52 : Pin interrupt 5 or pattern match engine slice 5 int
    PIN_INT6_IRQHandler,                          // 53 : Pin interrupt 6 or pattern match engine slice 6 int
    PIN_INT7_IRQHandler,                          // 54 : Pin interrupt 7 or pattern match engine slice 7 int
    CTIMER2_IRQHandler,                          // 55 : Standard counter/timer CTIMER2
    CTIMER4_IRQHandler,                          // 56 : Standard counter/timer CTIMER4
    OS_EVENT_IRQHandler,                          // 57 : OS event timer
    FLEXSPI_IRQHandler,                          // 58 : FLEXSPI interface
    Reserved59_IRQHandler,                        // 59 : Reserved interrupt
    Reserved60_IRQHandler,                        // 60 : Reserved interrupt
    Reserved61_IRQHandler,                        // 61 : Reserved interrupt
    SDU_IRQHandler,                          // 62 : SDIO
    SGPIO_INTA_IRQHandler,                        // 63 : Secure GPIO interrupt A
    SGPIO_INTB_IRQHandler,                        // 64 : Secure GPIO interrupt B
    Reserved65_IRQHandler,                        // 65 : Reserved interrupt
    USB_IRQHandler,                          // 66 : High-speed USB device/host
    Reserved67_IRQHandler,                        // 67 : Reserved interrupt
    Reserved68_IRQHandler,                        // 68 : Reserved interrupt
    Reserved69_IRQHandler,                        // 69 : Reserved interrupt
    DMA1_IRQHandler,                          // 70 : DMA controller 1 (non-secure or HiFi 4 DMA)
    PUF_IRQHandler,                          // 71 : Physical Unclonable Function
    POWERQUAD_IRQHandler,                         // 72 : PowerQuad math coprocessor
    Reserved73_IRQHandler,                        // 73 : Reserved interrupt
    Reserved74_IRQHandler,                        // 74 : Reserved interrupt
    Reserved75_IRQHandler,                        // 75 : Reserved interrupt
    Reserved76_IRQHandler,                        // 76 : Reserved interrupt
    LCDIC_IRQHandler,                          // 77 : LCDIC
    CAPT_PULSE_IRQHandler,                        // 78 : Capture timer
    Reserved79_IRQHandler,                        // 79 : Reserved interrupt
    WL_MCI_WAKEUP_DONE0_IRQHandler,               // 80 : WL to MCI, Wakeup done 0
    WL_MCI_WAKEUP_DONE1_IRQHandler,               // 81 : WL to MCI, Wakeup done 1
    WL_MCI_WAKEUP_DONE2_IRQHandler,               // 82 : WL to MCI, Wakeup done 2
    WL_MCI_WAKEUP_DONE3_IRQHandler,               // 83 : WL to MCI, Wakeup done 3
    WL_MCI_WAKEUP_DONE4_IRQHandler,               // 84 : WL to MCI, Wakeup done 4
    WL_MCI_WAKEUP_DONE5_IRQHandler,               // 85 : WL to MCI, Wakeup done 5
    WL_MCI_WAKEUP_DONE6_IRQHandler,               // 86 : WL to MCI, Wakeup done 6
    WL_MCI_WAKEUP_DONE7_IRQHandler,               // 87 : WL to MCI, Wakeup done 7
    WL_MCI_WAKEUP0_IRQHandler,                    // 88 : IMU_INT0: Cpu1_to_cpu3_msg_rdy_imu wl_mci_wakeup[0]
    WL_MCI_WAKEUP1_IRQHandler,                    // 89 : GP_INT from WL
    WL_MCI_INT0_IRQHandler,                       // 90 : IMU_INT: Imu13_cpu3_msg_space_avail
    WL_MCI_INT1_IRQHandler,                       // 91 : reserved
    WL_MCI_INT2_IRQHandler,                       // 92 : reserved
    WL_MCI_INT3_IRQHandler,                       // 93 : reserved
    WL_MCI_INT4_IRQHandler,                       // 94 : reserved
    WL_MCI_INT5_IRQHandler,                       // 95 : reserved
    WL_MCI_INT6_IRQHandler,                       // 96 : reserved
    WL_MCI_INT7_IRQHandler,                       // 97 : reserved
    BLE_MCI_WAKEUP_DONE0_IRQHandler,              // 98 : BLE to MCI, Wakeup done 0
    BLE_MCI_WAKEUP_DONE1_IRQHandler,              // 99 : BLE to MCI, Wakeup done 1
    BLE_MCI_WAKEUP_DONE2_IRQHandler,              // 100: BLE to MCI, Wakeup done 2
    BLE_MCI_WAKEUP_DONE3_IRQHandler,              // 101: BLE to MCI, Wakeup done 3
    BLE_MCI_WAKEUP_DONE4_IRQHandler,              // 102: BLE to MCI, Wakeup done 4
    BLE_MCI_WAKEUP_DONE5_IRQHandler,              // 103: BLE to MCI, Wakeup done 5
    BLE_MCI_WAKEUP_DONE6_IRQHandler,              // 104: BLE to MCI, Wakeup done 6
    BLE_MCI_WAKEUP_DONE7_IRQHandler,              // 105: BLE to MCI, Wakeup done 7
    BLE_MCI_WAKEUP0_IRQHandler,                   // 106: IMU_INT0: Cpu2_to_cpu3_msg_rdy_imu wl_mci_wakeup[0]
    BLE_MCI_WAKEUP1_IRQHandler,                   // 107: GP_INT from BLE
    BLE_MCI_INT0_IRQHandler,                      // 108: IMU_INT: Imu13_cpu3_msg_space_avail
    BLE_MCI_INT1_IRQHandler,                      // 109: reserved
    BLE_MCI_INT2_IRQHandler,                      // 110: reserved
    BLE_MCI_INT3_IRQHandler,                      // 111: reserved
    BLE_MCI_INT4_IRQHandler,                      // 112: reserved
    BLE_MCI_INT5_IRQHandler,                      // 113: reserved
    BLE_MCI_INT6_IRQHandler,                      // 114: reserved
    BLE_MCI_INT7_IRQHandler,                      // 115: reserved
    PIN0_INT_IRQHandler,                          // 116: From AON GPIO
    PIN1_INT_IRQHandler,                          // 117: From AON GPIO
    ELS_IRQHandler,                          // 118: ELS
    ELS_GDET_IRQ_IRQHandler,                      // 119: ELS IRQ line for GDET error
    ELS_GDET_ERR_IRQHandler,                      // 120: ELS Ungated latched error
    PKC_IRQHandler,                          // 121: PKC interrupt
    PKC_ERR_IRQHandler,                          // 122: PKC error
    CDOG_IRQHandler,                          // 123: Code watch dog timmer
    GAU_GPDAC_INT_FUNC11_IRQHandler,              // 124: GAU
    GAU_ACOMP_INT_WKUP11_IRQHandler,              // 125: GAU
    GAU_ACOMP_INT_FUNC11_IRQHandler,              // 126: GAU
    GAU_GPADC1_INT_FUNC11_IRQHandler,             // 127: GAU
    GAU_GPADC0_INT_FUNC11_IRQHandler,             // 128: GAU
    USIM_IRQHandler,                          // 129: USIM
    OCOTP_IRQHandler,                          // 130: OTP
    ENET_IRQHandler,                          // 131: ENET
    ENET_TIMER_IRQHandler,                        // 132: ENET
    BOD_1_85_INT_IRQHandler,                      // 133: PMIP
    BOD_1_85_NEG_IRQHandler,                      // 134: Bod_1_85_int negedge
    ITRC_IRQHandler,                          // 135: ITRC
    BTU_HOST_TRIGGER0_IRQHandler,                 // 136: Btu host trigger0
    BTU_HOST_TRIGGER1_IRQHandler,                 // 137: Btu host trigger1
    BTU_HOST_TRIGGER2_IRQHandler,                 // 138: Btu host trigger2
    TRNG_IRQHandler,                          // 139: TRNG
    AHB_MEM_ACC_CHECKER_VIO_INT_C_OR_IRQHandler,  // 140: ahb memory access checker - CM33 code bus
    AHB_MEM_ACC_CHECKER_VIO_INT_S_OR_IRQHandler,  // 141: ahb memory access checker - CM33 sys bus
    WL_ACC_INT_IRQHandler,                        // 142: Cpu access wlan when wlan is powered off
    BLE_ACC_INT_IRQHandler,                       // 143: Cpu access wlan when ble is powered off
    GDMA_IRQHandler,                          // 144: GDMA
}; /* End of g_pfnVectors */

#if defined(ENABLE_RAM_VECTOR_TABLE)
extern void * __VECTOR_TABLE __attribute__ ((alias ("g_pfnVectors")));
void (* __VECTOR_RAM[sizeof(g_pfnVectors) / 4])(void) __attribute__((aligned(128)));
unsigned int __RAM_VECTOR_TABLE_SIZE_BYTES = sizeof(g_pfnVectors);
#endif

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
WEAK void WDT0_IRQHandler(void)
{   WDT0_DriverIRQHandler();
}

WEAK void DMA0_IRQHandler(void)
{   DMA0_DriverIRQHandler();
}

WEAK void GPIO_INTA_IRQHandler(void)
{   GPIO_INTA_DriverIRQHandler();
}

WEAK void GPIO_INTB_IRQHandler(void)
{   GPIO_INTB_DriverIRQHandler();
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

WEAK void UTICK_IRQHandler(void)
{   UTICK_DriverIRQHandler();
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

WEAK void Reserved34_IRQHandler(void)
{   Reserved34_DriverIRQHandler();
}

WEAK void Reserved35_IRQHandler(void)
{   Reserved35_DriverIRQHandler();
}

WEAK void FLEXCOMM14_IRQHandler(void)
{   FLEXCOMM14_DriverIRQHandler();
}

WEAK void Reserved37_IRQHandler(void)
{   Reserved37_DriverIRQHandler();
}

WEAK void Reserved38_IRQHandler(void)
{   Reserved38_DriverIRQHandler();
}

WEAK void MRT1_IRQHandler(void)
{   MRT1_DriverIRQHandler();
}

WEAK void Reserved40_IRQHandler(void)
{   Reserved40_DriverIRQHandler();
}

WEAK void DMIC0_IRQHandler(void)
{   DMIC0_DriverIRQHandler();
}

WEAK void WFD_IRQHandler(void)
{   WFD_DriverIRQHandler();
}

WEAK void HYPERVISOR_IRQHandler(void)
{   HYPERVISOR_DriverIRQHandler();
}

WEAK void SECUREVIOLATION_IRQHandler(void)
{   SECUREVIOLATION_DriverIRQHandler();
}

WEAK void HWVAD0_IRQHandler(void)
{   HWVAD0_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void Reserved47_IRQHandler(void)
{   Reserved47_DriverIRQHandler();
}

WEAK void RTC_IRQHandler(void)
{   RTC_DriverIRQHandler();
}

WEAK void Reserved49_IRQHandler(void)
{   Reserved49_DriverIRQHandler();
}

WEAK void Reserved50_IRQHandler(void)
{   Reserved50_DriverIRQHandler();
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

WEAK void FLEXSPI_IRQHandler(void)
{   FLEXSPI_DriverIRQHandler();
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

WEAK void SDU_IRQHandler(void)
{   SDU_DriverIRQHandler();
}

WEAK void SGPIO_INTA_IRQHandler(void)
{   SGPIO_INTA_DriverIRQHandler();
}

WEAK void SGPIO_INTB_IRQHandler(void)
{   SGPIO_INTB_DriverIRQHandler();
}

WEAK void Reserved65_IRQHandler(void)
{   Reserved65_DriverIRQHandler();
}

WEAK void USB_IRQHandler(void)
{   USB_DriverIRQHandler();
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

WEAK void DMA1_IRQHandler(void)
{   DMA1_DriverIRQHandler();
}

WEAK void PUF_IRQHandler(void)
{   PUF_DriverIRQHandler();
}

WEAK void POWERQUAD_IRQHandler(void)
{   POWERQUAD_DriverIRQHandler();
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

WEAK void Reserved76_IRQHandler(void)
{   Reserved76_DriverIRQHandler();
}

WEAK void LCDIC_IRQHandler(void)
{   LCDIC_DriverIRQHandler();
}

WEAK void CAPT_PULSE_IRQHandler(void)
{   CAPT_PULSE_DriverIRQHandler();
}

WEAK void Reserved79_IRQHandler(void)
{   Reserved79_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE0_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE0_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE1_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE1_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE2_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE2_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE3_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE3_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE4_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE4_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE5_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE5_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE6_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE6_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP_DONE7_IRQHandler(void)
{   WL_MCI_WAKEUP_DONE7_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP0_IRQHandler(void)
{   WL_MCI_WAKEUP0_DriverIRQHandler();
}

WEAK void WL_MCI_WAKEUP1_IRQHandler(void)
{   WL_MCI_WAKEUP1_DriverIRQHandler();
}

WEAK void WL_MCI_INT0_IRQHandler(void)
{   WL_MCI_INT0_DriverIRQHandler();
}

WEAK void WL_MCI_INT1_IRQHandler(void)
{   WL_MCI_INT1_DriverIRQHandler();
}

WEAK void WL_MCI_INT2_IRQHandler(void)
{   WL_MCI_INT2_DriverIRQHandler();
}

WEAK void WL_MCI_INT3_IRQHandler(void)
{   WL_MCI_INT3_DriverIRQHandler();
}

WEAK void WL_MCI_INT4_IRQHandler(void)
{   WL_MCI_INT4_DriverIRQHandler();
}

WEAK void WL_MCI_INT5_IRQHandler(void)
{   WL_MCI_INT5_DriverIRQHandler();
}

WEAK void WL_MCI_INT6_IRQHandler(void)
{   WL_MCI_INT6_DriverIRQHandler();
}

WEAK void WL_MCI_INT7_IRQHandler(void)
{   WL_MCI_INT7_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE0_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE0_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE1_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE1_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE2_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE2_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE3_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE3_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE4_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE4_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE5_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE5_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE6_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE6_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP_DONE7_IRQHandler(void)
{   BLE_MCI_WAKEUP_DONE7_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP0_IRQHandler(void)
{   BLE_MCI_WAKEUP0_DriverIRQHandler();
}

WEAK void BLE_MCI_WAKEUP1_IRQHandler(void)
{   BLE_MCI_WAKEUP1_DriverIRQHandler();
}

WEAK void BLE_MCI_INT0_IRQHandler(void)
{   BLE_MCI_INT0_DriverIRQHandler();
}

WEAK void BLE_MCI_INT1_IRQHandler(void)
{   BLE_MCI_INT1_DriverIRQHandler();
}

WEAK void BLE_MCI_INT2_IRQHandler(void)
{   BLE_MCI_INT2_DriverIRQHandler();
}

WEAK void BLE_MCI_INT3_IRQHandler(void)
{   BLE_MCI_INT3_DriverIRQHandler();
}

WEAK void BLE_MCI_INT4_IRQHandler(void)
{   BLE_MCI_INT4_DriverIRQHandler();
}

WEAK void BLE_MCI_INT5_IRQHandler(void)
{   BLE_MCI_INT5_DriverIRQHandler();
}

WEAK void BLE_MCI_INT6_IRQHandler(void)
{   BLE_MCI_INT6_DriverIRQHandler();
}

WEAK void BLE_MCI_INT7_IRQHandler(void)
{   BLE_MCI_INT7_DriverIRQHandler();
}

WEAK void PIN0_INT_IRQHandler(void)
{   PIN0_INT_DriverIRQHandler();
}

WEAK void PIN1_INT_IRQHandler(void)
{   PIN1_INT_DriverIRQHandler();
}

WEAK void ELS_IRQHandler(void)
{   ELS_DriverIRQHandler();
}

WEAK void ELS_GDET_IRQ_IRQHandler(void)
{   ELS_GDET_IRQ_DriverIRQHandler();
}

WEAK void ELS_GDET_ERR_IRQHandler(void)
{   ELS_GDET_ERR_DriverIRQHandler();
}

WEAK void PKC_IRQHandler(void)
{   PKC_DriverIRQHandler();
}

WEAK void PKC_ERR_IRQHandler(void)
{   PKC_ERR_DriverIRQHandler();
}

WEAK void CDOG_IRQHandler(void)
{   CDOG_DriverIRQHandler();
}

WEAK void GAU_GPDAC_INT_FUNC11_IRQHandler(void)
{   GAU_GPDAC_INT_FUNC11_DriverIRQHandler();
}

WEAK void GAU_ACOMP_INT_WKUP11_IRQHandler(void)
{   GAU_ACOMP_INT_WKUP11_DriverIRQHandler();
}

WEAK void GAU_ACOMP_INT_FUNC11_IRQHandler(void)
{   GAU_ACOMP_INT_FUNC11_DriverIRQHandler();
}

WEAK void GAU_GPADC1_INT_FUNC11_IRQHandler(void)
{   GAU_GPADC1_INT_FUNC11_DriverIRQHandler();
}

WEAK void GAU_GPADC0_INT_FUNC11_IRQHandler(void)
{   GAU_GPADC0_INT_FUNC11_DriverIRQHandler();
}

WEAK void USIM_IRQHandler(void)
{   USIM_DriverIRQHandler();
}

WEAK void OCOTP_IRQHandler(void)
{   OCOTP_DriverIRQHandler();
}

WEAK void ENET_IRQHandler(void)
{   ENET_DriverIRQHandler();
}

WEAK void ENET_TIMER_IRQHandler(void)
{   ENET_TIMER_DriverIRQHandler();
}

WEAK void BOD_1_85_INT_IRQHandler(void)
{   BOD_1_85_INT_DriverIRQHandler();
}

WEAK void BOD_1_85_NEG_IRQHandler(void)
{   BOD_1_85_NEG_DriverIRQHandler();
}

WEAK void ITRC_IRQHandler(void)
{   ITRC_DriverIRQHandler();
}

WEAK void BTU_HOST_TRIGGER0_IRQHandler(void)
{   BTU_HOST_TRIGGER0_DriverIRQHandler();
}

WEAK void BTU_HOST_TRIGGER1_IRQHandler(void)
{   BTU_HOST_TRIGGER1_DriverIRQHandler();
}

WEAK void BTU_HOST_TRIGGER2_IRQHandler(void)
{   BTU_HOST_TRIGGER2_DriverIRQHandler();
}

WEAK void TRNG_IRQHandler(void)
{   TRNG_DriverIRQHandler();
}

WEAK void AHB_MEM_ACC_CHECKER_VIO_INT_C_OR_IRQHandler(void)
{   AHB_MEM_ACC_CHECKER_VIO_INT_C_OR_DriverIRQHandler();
}

WEAK void AHB_MEM_ACC_CHECKER_VIO_INT_S_OR_IRQHandler(void)
{   AHB_MEM_ACC_CHECKER_VIO_INT_S_OR_DriverIRQHandler();
}

WEAK void WL_ACC_INT_IRQHandler(void)
{   WL_ACC_INT_DriverIRQHandler();
}

WEAK void BLE_ACC_INT_IRQHandler(void)
{   BLE_ACC_INT_DriverIRQHandler();
}

WEAK void GDMA_IRQHandler(void)
{   GDMA_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
