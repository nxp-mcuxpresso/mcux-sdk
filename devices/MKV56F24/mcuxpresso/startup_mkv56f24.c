//*****************************************************************************
// MKV56F24 startup code for use with MCUXpresso IDE
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
WEAK void PMC_IRQHandler(void);
WEAK void LLWU_IRQHandler(void);
WEAK void WDOG_EWM_IRQHandler(void);
WEAK void TRNG0_IRQHandler(void);
WEAK void I2C0_IRQHandler(void);
WEAK void I2C1_IRQHandler(void);
WEAK void SPI0_IRQHandler(void);
WEAK void SPI1_IRQHandler(void);
WEAK void UART5_RX_TX_IRQHandler(void);
WEAK void UART5_ERR_IRQHandler(void);
WEAK void Reserved46_IRQHandler(void);
WEAK void UART0_RX_TX_IRQHandler(void);
WEAK void UART0_ERR_IRQHandler(void);
WEAK void UART1_RX_TX_IRQHandler(void);
WEAK void UART1_ERR_IRQHandler(void);
WEAK void UART2_RX_TX_IRQHandler(void);
WEAK void UART2_ERR_IRQHandler(void);
WEAK void ADC0_IRQHandler(void);
WEAK void HSADC_ERR_IRQHandler(void);
WEAK void HSADC0_CCA_IRQHandler(void);
WEAK void CMP0_IRQHandler(void);
WEAK void CMP1_IRQHandler(void);
WEAK void FTM0_IRQHandler(void);
WEAK void FTM1_IRQHandler(void);
WEAK void UART3_RX_TX_IRQHandler(void);
WEAK void UART3_ERR_IRQHandler(void);
WEAK void UART4_RX_TX_IRQHandler(void);
WEAK void UART4_ERR_IRQHandler(void);
WEAK void PIT0_IRQHandler(void);
WEAK void PIT1_IRQHandler(void);
WEAK void PIT2_IRQHandler(void);
WEAK void PIT3_IRQHandler(void);
WEAK void PDB0_IRQHandler(void);
WEAK void FTM2_IRQHandler(void);
WEAK void XBARA_IRQHandler(void);
WEAK void PDB1_IRQHandler(void);
WEAK void DAC0_IRQHandler(void);
WEAK void MCG_IRQHandler(void);
WEAK void LPTMR0_IRQHandler(void);
WEAK void PORTA_IRQHandler(void);
WEAK void PORTB_IRQHandler(void);
WEAK void PORTC_IRQHandler(void);
WEAK void PORTD_IRQHandler(void);
WEAK void PORTE_IRQHandler(void);
WEAK void SWI_IRQHandler(void);
WEAK void SPI2_IRQHandler(void);
WEAK void ENC_COMPARE_IRQHandler(void);
WEAK void ENC_HOME_IRQHandler(void);
WEAK void ENC_WDOG_SAB_IRQHandler(void);
WEAK void ENC_INDEX_IRQHandler(void);
WEAK void CMP2_IRQHandler(void);
WEAK void FTM3_IRQHandler(void);
WEAK void Reserved88_IRQHandler(void);
WEAK void HSADC0_CCB_IRQHandler(void);
WEAK void HSADC1_CCA_IRQHandler(void);
WEAK void CAN0_ORed_Message_buffer_IRQHandler(void);
WEAK void CAN0_Bus_Off_IRQHandler(void);
WEAK void CAN0_Error_IRQHandler(void);
WEAK void CAN0_Tx_Warning_IRQHandler(void);
WEAK void CAN0_Rx_Warning_IRQHandler(void);
WEAK void CAN0_Wake_Up_IRQHandler(void);
WEAK void PWM0_CMP0_IRQHandler(void);
WEAK void PWM0_RELOAD0_IRQHandler(void);
WEAK void PWM0_CMP1_IRQHandler(void);
WEAK void PWM0_RELOAD1_IRQHandler(void);
WEAK void PWM0_CMP2_IRQHandler(void);
WEAK void PWM0_RELOAD2_IRQHandler(void);
WEAK void PWM0_CMP3_IRQHandler(void);
WEAK void PWM0_RELOAD3_IRQHandler(void);
WEAK void PWM0_CAP_IRQHandler(void);
WEAK void PWM0_RERR_IRQHandler(void);
WEAK void PWM0_FAULT_IRQHandler(void);
WEAK void CMP3_IRQHandler(void);
WEAK void HSADC1_CCB_IRQHandler(void);
WEAK void CAN1_ORed_Message_buffer_IRQHandler(void);
WEAK void CAN1_Bus_Off_IRQHandler(void);
WEAK void CAN1_Error_IRQHandler(void);
WEAK void CAN1_Tx_Warning_IRQHandler(void);
WEAK void CAN1_Rx_Warning_IRQHandler(void);
WEAK void CAN1_Wake_Up_IRQHandler(void);
WEAK void Reserved116_IRQHandler(void);
WEAK void Reserved117_IRQHandler(void);
WEAK void Reserved118_IRQHandler(void);
WEAK void Reserved119_IRQHandler(void);
WEAK void PWM1_CMP0_IRQHandler(void);
WEAK void PWM1_RELOAD0_IRQHandler(void);
WEAK void PWM1_CMP1_IRQHandler(void);
WEAK void PWM1_RELOAD1_IRQHandler(void);
WEAK void PWM1_CMP2_IRQHandler(void);
WEAK void PWM1_RELOAD2_IRQHandler(void);
WEAK void PWM1_CMP3_IRQHandler(void);
WEAK void PWM1_RELOAD3_IRQHandler(void);
WEAK void PWM1_CAP_IRQHandler(void);
WEAK void PWM1_RERR_IRQHandler(void);
WEAK void PWM1_FAULT_IRQHandler(void);

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
void PMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LLWU_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void WDOG_EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRNG0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART5_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART5_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved46_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSADC_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSADC0_CCA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART3_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART4_RX_TX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void UART4_ERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PIT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XBARA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDB1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MCG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTD_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PORTE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SWI_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC_COMPARE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC_HOME_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC_WDOG_SAB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ENC_INDEX_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FTM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved88_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSADC0_CCB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSADC1_CCA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_RELOAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_RELOAD1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_CMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_RELOAD2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_CMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_RELOAD3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_CAP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_RERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM0_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void HSADC1_CCB_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved116_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved117_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved118_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved119_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_CMP0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_RELOAD0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_CMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_RELOAD1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_CMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_RELOAD2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_CMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_RELOAD3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_CAP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_RERR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
    // Core Level - CM7
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

    // Chip Level - MKV56F24
    DMA0_DMA16_IRQHandler,                // 16 : DMA channel 0/16 transfer complete
    DMA1_DMA17_IRQHandler,                // 17 : DMA channel 1/17 transfer complete
    DMA2_DMA18_IRQHandler,                // 18 : DMA channel 2/18 transfer complete
    DMA3_DMA19_IRQHandler,                // 19 : DMA channel 3/19 transfer complete
    DMA4_DMA20_IRQHandler,                // 20 : DMA channel 4/20 transfer complete
    DMA5_DMA21_IRQHandler,                // 21 : DMA channel 5/21 transfer complete
    DMA6_DMA22_IRQHandler,                // 22 : DMA channel 6/22 transfer complete
    DMA7_DMA23_IRQHandler,                // 23 : DMA channel 7/23 transfer complete
    DMA8_DMA24_IRQHandler,                // 24 : DMA channel 8/24 transfer complete
    DMA9_DMA25_IRQHandler,                // 25 : DMA channel 9/25 transfer complete
    DMA10_DMA26_IRQHandler,               // 26 : DMA channel 10/26 transfer complete
    DMA11_DMA27_IRQHandler,               // 27 : DMA channel 11/27 transfer complete
    DMA12_DMA28_IRQHandler,               // 28 : DMA channel 12/28 transfer complete
    DMA13_DMA29_IRQHandler,               // 29 : DMA channel 13/29 transfer complete
    DMA14_DMA30_IRQHandler,               // 30 : DMA channel 14/30 transfer complete
    DMA15_DMA31_IRQHandler,               // 31 : DMA channel 15/31 transfer complete
    DMA_Error_IRQHandler,                 // 32 : DMA error interrupt channels 0-31
    MCM_IRQHandler,                       // 33 : MCM normal interrupt
    FTFE_IRQHandler,                      // 34 : FTFL command complete
    Read_Collision_IRQHandler,            // 35 : FTFL read collision
    PMC_IRQHandler,                       // 36 : PMC controller low-voltage detect, low-voltage warning
    LLWU_IRQHandler,                      // 37 : Low leakage wakeup
    WDOG_EWM_IRQHandler,                  // 38 : Single interrupt vector for  WDOG and EWM
    TRNG0_IRQHandler,                     // 39 : True randon number generator
    I2C0_IRQHandler,                      // 40 : Inter-integrated circuit 0
    I2C1_IRQHandler,                      // 41 : Inter-integrated circuit 1
    SPI0_IRQHandler,                      // 42 : Serial peripheral Interface 0
    SPI1_IRQHandler,                      // 43 : Serial peripheral Interface 1
    UART5_RX_TX_IRQHandler,               // 44 : UART5 receive/transmit interrupt
    UART5_ERR_IRQHandler,                 // 45 : UART5 error interrupt
    Reserved46_IRQHandler,                // 46 : Reserved interrupt
    UART0_RX_TX_IRQHandler,               // 47 : UART0 receive/transmit interrupt
    UART0_ERR_IRQHandler,                 // 48 : UART0 error interrupt
    UART1_RX_TX_IRQHandler,               // 49 : UART1 receive/transmit interrupt
    UART1_ERR_IRQHandler,                 // 50 : UART1 error interrupt
    UART2_RX_TX_IRQHandler,               // 51 : UART2 receive/transmit interrupt
    UART2_ERR_IRQHandler,                 // 52 : UART2 error interrupt
    ADC0_IRQHandler,                      // 53 : Analog-to-digital converter 0
    HSADC_ERR_IRQHandler,                 // 54 : High speed analog-to-digital converter zero cross
    HSADC0_CCA_IRQHandler,                // 55 : High speed analog-to-digital converter 0 submodule A scan complete
    CMP0_IRQHandler,                      // 56 : Comparator 0
    CMP1_IRQHandler,                      // 57 : Comparator 1
    FTM0_IRQHandler,                      // 58 : FlexTimer module 0 fault, overflow and channels interrupt
    FTM1_IRQHandler,                      // 59 : FlexTimer module 1 fault, overflow and channels interrupt
    UART3_RX_TX_IRQHandler,               // 60 : UART3 receive/transmit interrupt
    UART3_ERR_IRQHandler,                 // 61 : UART3 error interrupt
    UART4_RX_TX_IRQHandler,               // 62 : UART4 receive/transmit interrupt
    UART4_ERR_IRQHandler,                 // 63 : UART4 error interrupt
    PIT0_IRQHandler,                      // 64 : Periodic interrupt timer channel 0
    PIT1_IRQHandler,                      // 65 : Periodic interrupt timer channel 1
    PIT2_IRQHandler,                      // 66 : Periodic interrupt timer channel 2
    PIT3_IRQHandler,                      // 67 : Periodic interrupt timer channel 3
    PDB0_IRQHandler,                      // 68 : Programmable delay block 0
    FTM2_IRQHandler,                      // 69 : FlexTimer module 2 fault, overflow and channels interrupt
    XBARA_IRQHandler,                     // 70 : Inter-peripheral crossbar switch A
    PDB1_IRQHandler,                      // 71 : Programmable delay block 1
    DAC0_IRQHandler,                      // 72 : Digital-to-analog converter 0
    MCG_IRQHandler,                       // 73 : Multipurpose clock generator
    LPTMR0_IRQHandler,                    // 74 : Low power timer interrupt
    PORTA_IRQHandler,                     // 75 : Port A interrupt
    PORTB_IRQHandler,                     // 76 : Port B interrupt
    PORTC_IRQHandler,                     // 77 : Port C interrupt
    PORTD_IRQHandler,                     // 78 : Port D interrupt
    PORTE_IRQHandler,                     // 79 : Port E interrupt
    SWI_IRQHandler,                       // 80 : Software interrupt
    SPI2_IRQHandler,                      // 81 : Serial peripheral Interface 2
    ENC_COMPARE_IRQHandler,               // 82 : ENC Compare
    ENC_HOME_IRQHandler,                  // 83 : ENC Home
    ENC_WDOG_SAB_IRQHandler,              // 84 : ENC Wdog/SAB
    ENC_INDEX_IRQHandler,                 // 85 : ENC Index/Roll over/Roll Under
    CMP2_IRQHandler,                      // 86 : Comparator 2
    FTM3_IRQHandler,                      // 87 : FlexTimer module 3 fault, overflow and channels
    Reserved88_IRQHandler,                // 88 : Reserved interrupt
    HSADC0_CCB_IRQHandler,                // 89 : High speed analog-to-digital converter 0 submodule B scan complete
    HSADC1_CCA_IRQHandler,                // 90 : High speed analog-to-digital converter 1 submodule A scan complete
    CAN0_ORed_Message_buffer_IRQHandler,  // 91 : Flex controller area network 0 message buffer
    CAN0_Bus_Off_IRQHandler,              // 92 : Flex controller area network 0 bus off
    CAN0_Error_IRQHandler,                // 93 : Flex controller area network 0 error
    CAN0_Tx_Warning_IRQHandler,           // 94 : Flex controller area network 0 transmit
    CAN0_Rx_Warning_IRQHandler,           // 95 : Flex controller area network 0 receive
    CAN0_Wake_Up_IRQHandler,              // 96 : Flex controller area network 0 wake up
    PWM0_CMP0_IRQHandler,                 // 97 : Pulse width modulator 0 channel 0 compare
    PWM0_RELOAD0_IRQHandler,              // 98 : Pulse width modulator 0 channel 0 reload
    PWM0_CMP1_IRQHandler,                 // 99 : Pulse width modulator 0 channel 1 compare
    PWM0_RELOAD1_IRQHandler,              // 100: Pulse width modulator 0 channel 1 reload
    PWM0_CMP2_IRQHandler,                 // 101: Pulse width modulator 0 channel 2 compare
    PWM0_RELOAD2_IRQHandler,              // 102: Pulse width modulator 0 channel 2 reload
    PWM0_CMP3_IRQHandler,                 // 103: Pulse width modulator 0 channel 3 compare
    PWM0_RELOAD3_IRQHandler,              // 104: Pulse width modulator 0 channel 3 reload
    PWM0_CAP_IRQHandler,                  // 105: Pulse width modulator 0 capture
    PWM0_RERR_IRQHandler,                 // 106: Pulse width modulator 0 reload error
    PWM0_FAULT_IRQHandler,                // 107: Pulse width modulator 0 fault
    CMP3_IRQHandler,                      // 108: Comparator 3
    HSADC1_CCB_IRQHandler,                // 109: High speed analog-to-digital converter 1 submodule B scan complete
    CAN1_ORed_Message_buffer_IRQHandler,  // 110: Flex controller area network 1 message buffer
    CAN1_Bus_Off_IRQHandler,              // 111: Flex controller area network 1 bus off
    CAN1_Error_IRQHandler,                // 112: Flex controller area network 1 error
    CAN1_Tx_Warning_IRQHandler,           // 113: Flex controller area network 1 transmit
    CAN1_Rx_Warning_IRQHandler,           // 114: Flex controller area network 1 receive
    CAN1_Wake_Up_IRQHandler,              // 115: Flex controller area network 1 wake up
    Reserved116_IRQHandler,               // 116: Reserved interrupt
    Reserved117_IRQHandler,               // 117: Reserved interrupt
    Reserved118_IRQHandler,               // 118: Reserved interrupt
    Reserved119_IRQHandler,               // 119: Reserved interrupt
    PWM1_CMP0_IRQHandler,                 // 120: Pulse width modulator 1 channel 0 compare
    PWM1_RELOAD0_IRQHandler,              // 121: Pulse width modulator 1 channel 0 reload
    PWM1_CMP1_IRQHandler,                 // 122: Pulse width modulator 1 channel 1 compare
    PWM1_RELOAD1_IRQHandler,              // 123: Pulse width modulator 1 channel 1 reload
    PWM1_CMP2_IRQHandler,                 // 124: Pulse width modulator 1 channel 2 compare
    PWM1_RELOAD2_IRQHandler,              // 125: Pulse width modulator 1 channel 2 reload
    PWM1_CMP3_IRQHandler,                 // 126: Pulse width modulator 1 channel 3 compare
    PWM1_RELOAD3_IRQHandler,              // 127: Pulse width modulator 1 channel 3 reload
    PWM1_CAP_IRQHandler,                  // 128: Pulse width modulator 1 capture
    PWM1_RERR_IRQHandler,                 // 129: Pulse width modulator 1 reload error
    PWM1_FAULT_IRQHandler,                // 130: Pulse width modulator 1 fault


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

WEAK void PMC_IRQHandler(void)
{   PMC_DriverIRQHandler();
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

WEAK void UART5_RX_TX_IRQHandler(void)
{   UART5_RX_TX_DriverIRQHandler();
}

WEAK void UART5_ERR_IRQHandler(void)
{   UART5_ERR_DriverIRQHandler();
}

WEAK void Reserved46_IRQHandler(void)
{   Reserved46_DriverIRQHandler();
}

WEAK void UART0_RX_TX_IRQHandler(void)
{   UART0_RX_TX_DriverIRQHandler();
}

WEAK void UART0_ERR_IRQHandler(void)
{   UART0_ERR_DriverIRQHandler();
}

WEAK void UART1_RX_TX_IRQHandler(void)
{   UART1_RX_TX_DriverIRQHandler();
}

WEAK void UART1_ERR_IRQHandler(void)
{   UART1_ERR_DriverIRQHandler();
}

WEAK void UART2_RX_TX_IRQHandler(void)
{   UART2_RX_TX_DriverIRQHandler();
}

WEAK void UART2_ERR_IRQHandler(void)
{   UART2_ERR_DriverIRQHandler();
}

WEAK void ADC0_IRQHandler(void)
{   ADC0_DriverIRQHandler();
}

WEAK void HSADC_ERR_IRQHandler(void)
{   HSADC_ERR_DriverIRQHandler();
}

WEAK void HSADC0_CCA_IRQHandler(void)
{   HSADC0_CCA_DriverIRQHandler();
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

WEAK void UART3_RX_TX_IRQHandler(void)
{   UART3_RX_TX_DriverIRQHandler();
}

WEAK void UART3_ERR_IRQHandler(void)
{   UART3_ERR_DriverIRQHandler();
}

WEAK void UART4_RX_TX_IRQHandler(void)
{   UART4_RX_TX_DriverIRQHandler();
}

WEAK void UART4_ERR_IRQHandler(void)
{   UART4_ERR_DriverIRQHandler();
}

WEAK void PIT0_IRQHandler(void)
{   PIT0_DriverIRQHandler();
}

WEAK void PIT1_IRQHandler(void)
{   PIT1_DriverIRQHandler();
}

WEAK void PIT2_IRQHandler(void)
{   PIT2_DriverIRQHandler();
}

WEAK void PIT3_IRQHandler(void)
{   PIT3_DriverIRQHandler();
}

WEAK void PDB0_IRQHandler(void)
{   PDB0_DriverIRQHandler();
}

WEAK void FTM2_IRQHandler(void)
{   FTM2_DriverIRQHandler();
}

WEAK void XBARA_IRQHandler(void)
{   XBARA_DriverIRQHandler();
}

WEAK void PDB1_IRQHandler(void)
{   PDB1_DriverIRQHandler();
}

WEAK void DAC0_IRQHandler(void)
{   DAC0_DriverIRQHandler();
}

WEAK void MCG_IRQHandler(void)
{   MCG_DriverIRQHandler();
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

WEAK void SPI2_IRQHandler(void)
{   SPI2_DriverIRQHandler();
}

WEAK void ENC_COMPARE_IRQHandler(void)
{   ENC_COMPARE_DriverIRQHandler();
}

WEAK void ENC_HOME_IRQHandler(void)
{   ENC_HOME_DriverIRQHandler();
}

WEAK void ENC_WDOG_SAB_IRQHandler(void)
{   ENC_WDOG_SAB_DriverIRQHandler();
}

WEAK void ENC_INDEX_IRQHandler(void)
{   ENC_INDEX_DriverIRQHandler();
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

WEAK void HSADC0_CCB_IRQHandler(void)
{   HSADC0_CCB_DriverIRQHandler();
}

WEAK void HSADC1_CCA_IRQHandler(void)
{   HSADC1_CCA_DriverIRQHandler();
}

WEAK void CAN0_ORed_Message_buffer_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Bus_Off_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Error_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Tx_Warning_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Rx_Warning_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void CAN0_Wake_Up_IRQHandler(void)
{   CAN0_DriverIRQHandler();
}

WEAK void PWM0_CMP0_IRQHandler(void)
{   PWM0_CMP0_DriverIRQHandler();
}

WEAK void PWM0_RELOAD0_IRQHandler(void)
{   PWM0_RELOAD0_DriverIRQHandler();
}

WEAK void PWM0_CMP1_IRQHandler(void)
{   PWM0_CMP1_DriverIRQHandler();
}

WEAK void PWM0_RELOAD1_IRQHandler(void)
{   PWM0_RELOAD1_DriverIRQHandler();
}

WEAK void PWM0_CMP2_IRQHandler(void)
{   PWM0_CMP2_DriverIRQHandler();
}

WEAK void PWM0_RELOAD2_IRQHandler(void)
{   PWM0_RELOAD2_DriverIRQHandler();
}

WEAK void PWM0_CMP3_IRQHandler(void)
{   PWM0_CMP3_DriverIRQHandler();
}

WEAK void PWM0_RELOAD3_IRQHandler(void)
{   PWM0_RELOAD3_DriverIRQHandler();
}

WEAK void PWM0_CAP_IRQHandler(void)
{   PWM0_CAP_DriverIRQHandler();
}

WEAK void PWM0_RERR_IRQHandler(void)
{   PWM0_RERR_DriverIRQHandler();
}

WEAK void PWM0_FAULT_IRQHandler(void)
{   PWM0_FAULT_DriverIRQHandler();
}

WEAK void CMP3_IRQHandler(void)
{   CMP3_DriverIRQHandler();
}

WEAK void HSADC1_CCB_IRQHandler(void)
{   HSADC1_CCB_DriverIRQHandler();
}

WEAK void CAN1_ORed_Message_buffer_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Bus_Off_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Error_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Tx_Warning_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Rx_Warning_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_Wake_Up_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void Reserved116_IRQHandler(void)
{   Reserved116_DriverIRQHandler();
}

WEAK void Reserved117_IRQHandler(void)
{   Reserved117_DriverIRQHandler();
}

WEAK void Reserved118_IRQHandler(void)
{   Reserved118_DriverIRQHandler();
}

WEAK void Reserved119_IRQHandler(void)
{   Reserved119_DriverIRQHandler();
}

WEAK void PWM1_CMP0_IRQHandler(void)
{   PWM1_CMP0_DriverIRQHandler();
}

WEAK void PWM1_RELOAD0_IRQHandler(void)
{   PWM1_RELOAD0_DriverIRQHandler();
}

WEAK void PWM1_CMP1_IRQHandler(void)
{   PWM1_CMP1_DriverIRQHandler();
}

WEAK void PWM1_RELOAD1_IRQHandler(void)
{   PWM1_RELOAD1_DriverIRQHandler();
}

WEAK void PWM1_CMP2_IRQHandler(void)
{   PWM1_CMP2_DriverIRQHandler();
}

WEAK void PWM1_RELOAD2_IRQHandler(void)
{   PWM1_RELOAD2_DriverIRQHandler();
}

WEAK void PWM1_CMP3_IRQHandler(void)
{   PWM1_CMP3_DriverIRQHandler();
}

WEAK void PWM1_RELOAD3_IRQHandler(void)
{   PWM1_RELOAD3_DriverIRQHandler();
}

WEAK void PWM1_CAP_IRQHandler(void)
{   PWM1_CAP_DriverIRQHandler();
}

WEAK void PWM1_RERR_IRQHandler(void)
{   PWM1_RERR_DriverIRQHandler();
}

WEAK void PWM1_FAULT_IRQHandler(void)
{   PWM1_FAULT_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
