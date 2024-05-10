//*****************************************************************************
// MIMXRT1187_cm33 startup code for use with MCUXpresso IDE
//
// Version : 131223
//*****************************************************************************
//
// Copyright 2016-2023 NXP
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
WEAK void TMR1_IRQHandler(void);
WEAK void DAP_IRQHandler(void);
WEAK void M7_CTI_TRIGGER_OUTPUT_IRQHandler(void);
WEAK void M33_CTI_TRIGGER_OUTPUT_IRQHandler(void);
WEAK void TMR5_IRQHandler(void);
WEAK void TMR6_IRQHandler(void);
WEAK void TMR7_IRQHandler(void);
WEAK void TMR8_IRQHandler(void);
WEAK void CAN1_IRQHandler(void);
WEAK void CAN1_ERROR_IRQHandler(void);
WEAK void GPIO1_0_IRQHandler(void);
WEAK void GPIO1_1_IRQHandler(void);
WEAK void I3C1_IRQHandler(void);
WEAK void LPI2C1_IRQHandler(void);
WEAK void LPI2C2_IRQHandler(void);
WEAK void LPIT1_IRQHandler(void);
WEAK void LPSPI1_IRQHandler(void);
WEAK void LPSPI2_IRQHandler(void);
WEAK void LPTMR1_IRQHandler(void);
WEAK void LPUART1_IRQHandler(void);
WEAK void LPUART2_IRQHandler(void);
WEAK void MU1_IRQHandler(void);
WEAK void MU2_IRQHandler(void);
WEAK void PWM1_FAULT_IRQHandler(void);
WEAK void PWM1_0_IRQHandler(void);
WEAK void PWM1_1_IRQHandler(void);
WEAK void PWM1_2_IRQHandler(void);
WEAK void PWM1_3_IRQHandler(void);
WEAK void EDGELOCK_TRUST_MUA_RX_FULL_IRQHandler(void);
WEAK void EDGELOCK_TRUST_MUA_TX_EMPTY_IRQHandler(void);
WEAK void EDGELOCK_APPS_CORE_MUA_RX_FULL_IRQHandler(void);
WEAK void EDGELOCK_APPS_CORE_MUA_TX_EMPTY_IRQHandler(void);
WEAK void EDGELOCK_REALTIME_CORE_MUA_RX_FULL_IRQHandler(void);
WEAK void EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_IRQHandler(void);
WEAK void EDGELOCK_SECURE_IRQHandler(void);
WEAK void EDGELOCK_NONSECURE_IRQHandler(void);
WEAK void TPM1_IRQHandler(void);
WEAK void TPM2_IRQHandler(void);
WEAK void RTWDOG1_IRQHandler(void);
WEAK void RTWDOG2_IRQHandler(void);
WEAK void TRDC_MGR_AON_IRQHandler(void);
WEAK void PDM_HWVAD_EVENT_IRQHandler(void);
WEAK void PDM_HWVAD_ERROR_IRQHandler(void);
WEAK void PDM_EVENT_IRQHandler(void);
WEAK void PDM_ERROR_IRQHandler(void);
WEAK void SAI1_IRQHandler(void);
WEAK void CM33_PS_IRQHandler(void);
WEAK void CM33_TCM_ECC_IRQHandler(void);
WEAK void CM33_TCM_ERROR_IRQHandler(void);
WEAK void CM7_TCM_ECC_IRQHandler(void);
WEAK void CM7_TCM_ERROR_IRQHandler(void);
WEAK void CAN2_IRQHandler(void);
WEAK void CAN2_ERROR_IRQHandler(void);
WEAK void FLEXIO1_IRQHandler(void);
WEAK void FLEXIO2_IRQHandler(void);
WEAK void FLEXSPI1_IRQHandler(void);
WEAK void FLEXSPI2_IRQHandler(void);
WEAK void GPIO2_0_IRQHandler(void);
WEAK void GPIO2_1_IRQHandler(void);
WEAK void GPIO3_0_IRQHandler(void);
WEAK void GPIO3_1_IRQHandler(void);
WEAK void I3C2_IRQHandler(void);
WEAK void LPI2C3_IRQHandler(void);
WEAK void LPI2C4_IRQHandler(void);
WEAK void LPIT2_IRQHandler(void);
WEAK void LPSPI3_IRQHandler(void);
WEAK void LPSPI4_IRQHandler(void);
WEAK void LPTMR2_IRQHandler(void);
WEAK void LPUART3_IRQHandler(void);
WEAK void LPUART4_IRQHandler(void);
WEAK void LPUART5_IRQHandler(void);
WEAK void LPUART6_IRQHandler(void);
WEAK void Reserved88_IRQHandler(void);
WEAK void BBNSM_IRQHandler(void);
WEAK void SYS_CTR1_IRQHandler(void);
WEAK void TPM3_IRQHandler(void);
WEAK void TPM4_IRQHandler(void);
WEAK void TPM5_IRQHandler(void);
WEAK void TPM6_IRQHandler(void);
WEAK void RTWDOG3_IRQHandler(void);
WEAK void RTWDOG4_IRQHandler(void);
WEAK void RTWDOG5_IRQHandler(void);
WEAK void TRDC_MGR_WKUP_IRQHandler(void);
WEAK void TMPSNS_INT_IRQHandler(void);
WEAK void BBSM_IRQHandler(void);
WEAK void LDO_AON_ANA_IRQHandler(void);
WEAK void USDHC1_IRQHandler(void);
WEAK void USDHC2_IRQHandler(void);
WEAK void TRDC_MGR_MEGA_IRQHandler(void);
WEAK void SFA_IRQHandler(void);
WEAK void LDO_AON_DIG_IRQHandler(void);
WEAK void MECC1_IRQHandler(void);
WEAK void MECC2_IRQHandler(void);
WEAK void ADC1_IRQHandler(void);
WEAK void DMA_ERROR_IRQHandler(void);
WEAK void DMA3_CH0_IRQHandler(void);
WEAK void DMA3_CH1_IRQHandler(void);
WEAK void DMA3_CH2_IRQHandler(void);
WEAK void DMA3_CH3_IRQHandler(void);
WEAK void DMA3_CH4_IRQHandler(void);
WEAK void DMA3_CH5_IRQHandler(void);
WEAK void DMA3_CH6_IRQHandler(void);
WEAK void DMA3_CH7_IRQHandler(void);
WEAK void DMA3_CH8_IRQHandler(void);
WEAK void DMA3_CH9_IRQHandler(void);
WEAK void DMA3_CH10_IRQHandler(void);
WEAK void DMA3_CH11_IRQHandler(void);
WEAK void DMA3_CH12_IRQHandler(void);
WEAK void DMA3_CH13_IRQHandler(void);
WEAK void DMA3_CH14_IRQHandler(void);
WEAK void DMA3_CH15_IRQHandler(void);
WEAK void DMA3_CH16_IRQHandler(void);
WEAK void DMA3_CH17_IRQHandler(void);
WEAK void DMA3_CH18_IRQHandler(void);
WEAK void DMA3_CH19_IRQHandler(void);
WEAK void DMA3_CH20_IRQHandler(void);
WEAK void DMA3_CH21_IRQHandler(void);
WEAK void DMA3_CH22_IRQHandler(void);
WEAK void DMA3_CH23_IRQHandler(void);
WEAK void DMA3_CH24_IRQHandler(void);
WEAK void DMA3_CH25_IRQHandler(void);
WEAK void DMA3_CH26_IRQHandler(void);
WEAK void DMA3_CH27_IRQHandler(void);
WEAK void DMA3_CH28_IRQHandler(void);
WEAK void DMA3_CH29_IRQHandler(void);
WEAK void DMA3_CH30_IRQHandler(void);
WEAK void DMA3_CH31_IRQHandler(void);
WEAK void DMA4_ERROR_IRQHandler(void);
WEAK void DMA4_CH0_CH1_CH32_CH33_IRQHandler(void);
WEAK void DMA4_CH2_CH3_CH34_CH35_IRQHandler(void);
WEAK void DMA4_CH4_CH5_CH36_CH37_IRQHandler(void);
WEAK void DMA4_CH6_CH7_CH38_CH39_IRQHandler(void);
WEAK void DMA4_CH8_CH9_CH40_CH41_IRQHandler(void);
WEAK void DMA4_CH10_CH11_CH42_CH43_IRQHandler(void);
WEAK void DMA4_CH12_CH13_CH44_CH45_IRQHandler(void);
WEAK void DMA4_CH14_CH15_CH46_CH47_IRQHandler(void);
WEAK void DMA4_CH16_CH17_CH48_CH49_IRQHandler(void);
WEAK void DMA4_CH18_CH19_CH50_CH51_IRQHandler(void);
WEAK void DMA4_CH20_CH21_CH52_CH53_IRQHandler(void);
WEAK void DMA4_CH22_CH23_CH54_CH55_IRQHandler(void);
WEAK void DMA4_CH24_CH25_CH56_CH57_IRQHandler(void);
WEAK void DMA4_CH26_CH27_CH58_CH59_IRQHandler(void);
WEAK void DMA4_CH28_CH29_CH60_CH61_IRQHandler(void);
WEAK void DMA4_CH30_CH31_CH62_CH63_IRQHandler(void);
WEAK void XBAR1_CH0_CH1_IRQHandler(void);
WEAK void XBAR1_CH2_CH3_IRQHandler(void);
WEAK void SINC3_CH0_CH1_CH2_CH3_IRQHandler(void);
WEAK void EWM_IRQHandler(void);
WEAK void SEMC_IRQHandler(void);
WEAK void LPIT3_IRQHandler(void);
WEAK void LPTMR3_IRQHandler(void);
WEAK void TMR4_IRQHandler(void);
WEAK void LPI2C5_IRQHandler(void);
WEAK void LPI2C6_IRQHandler(void);
WEAK void SAI4_IRQHandler(void);
WEAK void SPDIF_IRQHandler(void);
WEAK void LPUART9_IRQHandler(void);
WEAK void LPUART10_IRQHandler(void);
WEAK void LPUART11_IRQHandler(void);
WEAK void LPUART12_IRQHandler(void);
WEAK void INTG_BOOTROM_DEBUG_CTRL_IRQHandler(void);
WEAK void EDGELOCK_REQ1_IRQHandler(void);
WEAK void EDGELOCK_REQ2_IRQHandler(void);
WEAK void EDGELOCK_REQ3_IRQHandler(void);
WEAK void TMR3_IRQHandler(void);
WEAK void JTAGC_IRQHandler(void);
WEAK void M33_SYSRESET_REQ_IRQHandler(void);
WEAK void M33_LOCKUP_IRQHandler(void);
WEAK void M7_SYSRESET_REQ_IRQHandler(void);
WEAK void M7_LOCKUP_IRQHandler(void);
WEAK void PWM2_FAULT_IRQHandler(void);
WEAK void PWM2_0_IRQHandler(void);
WEAK void PWM2_1_IRQHandler(void);
WEAK void PWM2_2_IRQHandler(void);
WEAK void PWM2_3_IRQHandler(void);
WEAK void PWM3_FAULT_IRQHandler(void);
WEAK void PWM3_0_IRQHandler(void);
WEAK void PWM3_1_IRQHandler(void);
WEAK void PWM3_2_IRQHandler(void);
WEAK void PWM3_3_IRQHandler(void);
WEAK void PWM4_FAULT_IRQHandler(void);
WEAK void PWM4_0_IRQHandler(void);
WEAK void PWM4_1_IRQHandler(void);
WEAK void PWM4_2_IRQHandler(void);
WEAK void PWM4_3_IRQHandler(void);
WEAK void EQDC1_IRQHandler(void);
WEAK void EQDC2_IRQHandler(void);
WEAK void EQDC3_IRQHandler(void);
WEAK void EQDC4_IRQHandler(void);
WEAK void ADC2_IRQHandler(void);
WEAK void DCDC_IRQHandler(void);
WEAK void CAN3_IRQHandler(void);
WEAK void CAN3_ERROR_IRQHandler(void);
WEAK void DAC_IRQHandler(void);
WEAK void LPSPI5_IRQHandler(void);
WEAK void LPSPI6_IRQHandler(void);
WEAK void LPUART7_IRQHandler(void);
WEAK void LPUART8_IRQHandler(void);
WEAK void SAI2_IRQHandler(void);
WEAK void SAI3_IRQHandler(void);
WEAK void ACMP1_IRQHandler(void);
WEAK void ACMP2_IRQHandler(void);
WEAK void ACMP3_IRQHandler(void);
WEAK void ACMP4_IRQHandler(void);
WEAK void CM7_PS_IRQHandler(void);
WEAK void CM7_MCM_IRQHandler(void);
WEAK void CM33_MCM_IRQHandler(void);
WEAK void Reserved223_IRQHandler(void);
WEAK void SAFETY_CLK_MON_IRQHandler(void);
WEAK void GPT1_IRQHandler(void);
WEAK void GPT2_IRQHandler(void);
WEAK void KPP_IRQHandler(void);
WEAK void USBPHY1_IRQHandler(void);
WEAK void USBPHY2_IRQHandler(void);
WEAK void USB_OTG2_IRQHandler(void);
WEAK void USB_OTG1_IRQHandler(void);
WEAK void FLEXSPI_SLV_IRQHandler(void);
WEAK void NETC_IRQHandler(void);
WEAK void MSGINTR1_IRQHandler(void);
WEAK void MSGINTR2_IRQHandler(void);
WEAK void MSGINTR3_IRQHandler(void);
WEAK void MSGINTR4_IRQHandler(void);
WEAK void MSGINTR5_IRQHandler(void);
WEAK void MSGINTR6_IRQHandler(void);
WEAK void SINC1_CH0_IRQHandler(void);
WEAK void SINC1_CH1_IRQHandler(void);
WEAK void SINC1_CH2_IRQHandler(void);
WEAK void SINC1_CH3_IRQHandler(void);
WEAK void SINC2_CH0_IRQHandler(void);
WEAK void SINC2_CH1_IRQHandler(void);
WEAK void SINC2_CH2_IRQHandler(void);
WEAK void SINC2_CH3_IRQHandler(void);
WEAK void GPIO4_IRQHandler(void);
WEAK void TMR2_IRQHandler(void);
WEAK void GPIO5_IRQHandler(void);
WEAK void ASRC_IRQHandler(void);
WEAK void GPIO6_IRQHandler(void);
WEAK void DBG_TRACE_IRQHandler(void);

//*****************************************************************************
// Forward declaration of the driver IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the driver
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//*****************************************************************************
void TMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M7_CTI_TRIGGER_OUTPUT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M33_CTI_TRIGGER_OUTPUT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN1_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO1_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO1_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I3C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MU1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MU2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM1_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_TRUST_MUA_RX_FULL_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_TRUST_MUA_TX_EMPTY_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_APPS_CORE_MUA_RX_FULL_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_APPS_CORE_MUA_TX_EMPTY_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_REALTIME_CORE_MUA_RX_FULL_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_SECURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_NONSECURE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRDC_MGR_AON_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_HWVAD_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_HWVAD_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_EVENT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PDM_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM33_PS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM33_TCM_ECC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM33_TCM_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM7_TCM_ECC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM7_TCM_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN2_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXIO2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO2_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO2_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO3_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO3_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void I3C2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved88_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BBNSM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SYS_CTR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TPM6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void RTWDOG5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRDC_MGR_WKUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMPSNS_INT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void BBSM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LDO_AON_ANA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USDHC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TRDC_MGR_MEGA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SFA_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LDO_AON_DIG_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MECC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH9_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH10_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH12_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH13_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH14_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH15_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH16_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH17_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH18_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH19_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH20_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH21_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH22_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH23_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH24_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH25_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH26_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH27_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH28_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH29_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH30_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA3_CH31_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XBAR1_CH0_CH1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void XBAR1_CH2_CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC3_CH0_CH1_CH2_CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EWM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SEMC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPIT3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPTMR3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPI2C6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SPDIF_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART9_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART10_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART11_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART12_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void INTG_BOOTROM_DEBUG_CTRL_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_REQ1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_REQ2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EDGELOCK_REQ3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void JTAGC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M33_SYSRESET_REQ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M33_LOCKUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M7_SYSRESET_REQ_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void M7_LOCKUP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM2_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM3_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_FAULT_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void PWM4_3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EQDC1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EQDC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EQDC3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void EQDC4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ADC2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DCDC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CAN3_ERROR_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPSPI6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART7_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void LPUART8_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAI3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM7_PS_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM7_MCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void CM33_MCM_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void Reserved223_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SAFETY_CLK_MON_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPT2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void KPP_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USBPHY2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_OTG2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void USB_OTG1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void FLEXSPI_SLV_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void NETC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void MSGINTR6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC1_CH0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC1_CH1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC1_CH2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC1_CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC2_CH0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC2_CH1_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC2_CH2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void SINC2_CH3_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO4_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void TMR2_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO5_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void ASRC_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void GPIO6_DriverIRQHandler(void) ALIAS(IntDefaultHandler);
void DBG_TRACE_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

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
    NMI_Handler,                       // NMI Handler
    HardFault_Handler,                 // Hard Fault Handler
    MemManage_Handler,                 // MPU Fault Handler
    BusFault_Handler,                  // Bus Fault Handler
    UsageFault_Handler,                // Usage Fault Handler
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall Handler
    DebugMon_Handler,                  // Debug Monitor Handler
    0,                                 // Reserved
    PendSV_Handler,                    // PendSV Handler
    SysTick_Handler,                   // SysTick Handler

    // Chip Level - MIMXRT1187_cm33
    TMR1_IRQHandler,                          // 16 : TMR1 interrupt
    DAP_IRQHandler,                          // 17 : DAP interrupt
    M7_CTI_TRIGGER_OUTPUT_IRQHandler,                // 18 : CTI trigger outputs from CM7
    M33_CTI_TRIGGER_OUTPUT_IRQHandler,               // 19 : CTI trigger outputs from CM33
    TMR5_IRQHandler,                          // 20 : TMR5 interrupt
    TMR6_IRQHandler,                          // 21 : TMR6 interrupt
    TMR7_IRQHandler,                          // 22 : TMR7 interrupt
    TMR8_IRQHandler,                          // 23 : TMR8 interrupt
    CAN1_IRQHandler,                          // 24 : CAN1 interrupt
    CAN1_ERROR_IRQHandler,                          // 25 : CAN1 error interrupt
    GPIO1_0_IRQHandler,                          // 26 : GPIO1 interrupt 0
    GPIO1_1_IRQHandler,                          // 27 : GPIO1 interrupt 1
    I3C1_IRQHandler,                          // 28 : I3C1 interrupt
    LPI2C1_IRQHandler,                          // 29 : LPI2C1 interrupt
    LPI2C2_IRQHandler,                          // 30 : LPI2C2 interrupt
    LPIT1_IRQHandler,                          // 31 : LPIT1 interrupt
    LPSPI1_IRQHandler,                          // 32 : LPSPI1 interrupt
    LPSPI2_IRQHandler,                          // 33 : LPSPI2 interrupt
    LPTMR1_IRQHandler,                          // 34 : LPTMR1 interrupt
    LPUART1_IRQHandler,                          // 35 : LPUART1 interrupt
    LPUART2_IRQHandler,                          // 36 : LPUART2 interrupt
    MU1_IRQHandler,                          // 37 : MU1 interrupt
    MU2_IRQHandler,                          // 38 : MU2 interrupt
    PWM1_FAULT_IRQHandler,                          // 39 : PWM1 fault or reload error interrupt
    PWM1_0_IRQHandler,                          // 40 : PWM1 capture 0, compare 0, or reload 0 interrupt
    PWM1_1_IRQHandler,                          // 41 : PWM1 capture 1, compare 1, or reload 1 interrupt
    PWM1_2_IRQHandler,                          // 42 : PWM1 capture 2, compare 2, or reload 2 interrupt
    PWM1_3_IRQHandler,                          // 43 : PWM1 capture 3, compare 3, or reload 3 interrupt
    EDGELOCK_TRUST_MUA_RX_FULL_IRQHandler,           // 44 : Edgelock Trust MUA RX full interrupt
    EDGELOCK_TRUST_MUA_TX_EMPTY_IRQHandler,          // 45 : Edgelock Trust MUA TX empty interrupt
    EDGELOCK_APPS_CORE_MUA_RX_FULL_IRQHandler,       // 46 : Edgelock Apps Core MUA RX full interrupt
    EDGELOCK_APPS_CORE_MUA_TX_EMPTY_IRQHandler,      // 47 : Edgelock Apps Core MUA TX empty interrupt
    EDGELOCK_REALTIME_CORE_MUA_RX_FULL_IRQHandler,   // 48 : Edgelock Realtime Core MUA RX full interrupt
    EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_IRQHandler,  // 49 : Edgelock Realtime Core MUA TX empty interrupt
    EDGELOCK_SECURE_IRQHandler,                      // 50 : Edgelock secure interrupt
    EDGELOCK_NONSECURE_IRQHandler,                   // 51 : Edgelock non-secure interrupt
    TPM1_IRQHandler,                          // 52 : TPM1 interrupt
    TPM2_IRQHandler,                          // 53 : TPM2 interrupt
    RTWDOG1_IRQHandler,                          // 54 : RTWDOG1 interrupt
    RTWDOG2_IRQHandler,                          // 55 : RTWDOG2 interrupt
    TRDC_MGR_AON_IRQHandler,                         // 56 : AONMIX TRDC transfer error interrupt
    PDM_HWVAD_EVENT_IRQHandler,                      // 57 : HWVAD event interrupt
    PDM_HWVAD_ERROR_IRQHandler,                      // 58 : HWVAD error interrupt
    PDM_EVENT_IRQHandler,                          // 59 : PDM event interrupt
    PDM_ERROR_IRQHandler,                          // 60 : PDM error interrupt
    SAI1_IRQHandler,                          // 61 : SAI interrupt
    CM33_PS_IRQHandler,                          // 62 : M33 PS Tag/Data Parity Error
    CM33_TCM_ECC_IRQHandler,                         // 63 : M33 TCM ECC interrupt
    CM33_TCM_ERROR_IRQHandler,                       // 64 : M33 TCM Error interrupt
    CM7_TCM_ECC_IRQHandler,                          // 65 : M7 TCM ECC interrupt
    CM7_TCM_ERROR_IRQHandler,                        // 66 : M7 TCM Error interrupt
    CAN2_IRQHandler,                          // 67 : CAN2 interrupt
    CAN2_ERROR_IRQHandler,                          // 68 : CAN2 error interrupt
    FLEXIO1_IRQHandler,                          // 69 : FLEXIO1 interrupt
    FLEXIO2_IRQHandler,                          // 70 : FLEXIO2 interrupt
    FLEXSPI1_IRQHandler,                          // 71 : FLEXSPI1 interrupt
    FLEXSPI2_IRQHandler,                          // 72 : FLEXSPI2 interrupt
    GPIO2_0_IRQHandler,                          // 73 : GPIO2 interrupt 0
    GPIO2_1_IRQHandler,                          // 74 : GPIO2 interrupt 1
    GPIO3_0_IRQHandler,                          // 75 : GPIO3 interrupt 0
    GPIO3_1_IRQHandler,                          // 76 : GPIO3 interrupt 1
    I3C2_IRQHandler,                          // 77 : I3C2 interrupt
    LPI2C3_IRQHandler,                          // 78 : LPI2C3 interrupt
    LPI2C4_IRQHandler,                          // 79 : LPI2C4 interrput
    LPIT2_IRQHandler,                          // 80 : LPIT2 interrupt
    LPSPI3_IRQHandler,                          // 81 : LPSPI3 interrupt
    LPSPI4_IRQHandler,                          // 82 : LPSPI4 interrupt
    LPTMR2_IRQHandler,                          // 83 : LPTMR2 interrupt
    LPUART3_IRQHandler,                          // 84 : LPUART3 interrupt
    LPUART4_IRQHandler,                          // 85 : LPUART4 interrupt
    LPUART5_IRQHandler,                          // 86 : LPUART5 interrupt
    LPUART6_IRQHandler,                          // 87 : LPUART6 interrupt
    Reserved88_IRQHandler,                          // 88 : Reserved interrupt
    BBNSM_IRQHandler,                          // 89 : BBNSM iterrupt
    SYS_CTR1_IRQHandler,                          // 90 : System Counter compare interrupt 0 and 1
    TPM3_IRQHandler,                          // 91 : TPM3 interrupt
    TPM4_IRQHandler,                          // 92 : TPM4 interrupt
    TPM5_IRQHandler,                          // 93 : TPM5 interrupt
    TPM6_IRQHandler,                          // 94 : TPM6 interrupt
    RTWDOG3_IRQHandler,                          // 95 : RTWDOG3 interrupt
    RTWDOG4_IRQHandler,                          // 96 : RTWDOG4 interrupt
    RTWDOG5_IRQHandler,                          // 97 : RTWDOG5 interrupt
    TRDC_MGR_WKUP_IRQHandler,                        // 98 : WAKEUPMIX TRDC transfer error interrupt
    TMPSNS_INT_IRQHandler,                          // 99 : Temperature alarm interrupt
    BBSM_IRQHandler,                          // 100: BBSM wakeup alarm interrupt
    LDO_AON_ANA_IRQHandler,                          // 101: Brown out interrupt
    USDHC1_IRQHandler,                          // 102: USDHC1
    USDHC2_IRQHandler,                          // 103: USDHC2
    TRDC_MGR_MEGA_IRQHandler,                        // 104: MEGAMIX TRDC transfer error interrupt
    SFA_IRQHandler,                          // 105: Signal Frequency Analyzer interrupt
    LDO_AON_DIG_IRQHandler,                          // 106: Brown out interrupt
    MECC1_IRQHandler,                          // 107: MECC1 interrupt
    MECC2_IRQHandler,                          // 108: MECC2 interrupt
    ADC1_IRQHandler,                          // 109: ADC1 interrupt
    DMA_ERROR_IRQHandler,                          // 110: AON Domain eDMA error interrupt
    DMA3_CH0_IRQHandler,                          // 111: AON Domain eDMA channel 0 interrupt
    DMA3_CH1_IRQHandler,                          // 112: AON Domain eDMA channel 1 interrupt
    DMA3_CH2_IRQHandler,                          // 113: AON Domain eDMA channel 2 interrupt
    DMA3_CH3_IRQHandler,                          // 114: AON Domain eDMA channel 3 interrupt
    DMA3_CH4_IRQHandler,                          // 115: AON Domain eDMA channel 4 interrupt
    DMA3_CH5_IRQHandler,                          // 116: AON Domain eDMA channel 5 interrupt
    DMA3_CH6_IRQHandler,                          // 117: AON Domain eDMA channel 6 interrupt
    DMA3_CH7_IRQHandler,                          // 118: AON Domain eDMA channel 7 interrupt
    DMA3_CH8_IRQHandler,                          // 119: AON Domain eDMA channel 8 interrupt
    DMA3_CH9_IRQHandler,                          // 120: AON Domain eDMA channel 9 interrupt
    DMA3_CH10_IRQHandler,                          // 121: AON Domain eDMA channel 10 interrupt
    DMA3_CH11_IRQHandler,                          // 122: AON Domain eDMA channel 11 interrupt
    DMA3_CH12_IRQHandler,                          // 123: AON Domain eDMA channel 12 interrupt
    DMA3_CH13_IRQHandler,                          // 124: AON Domain eDMA channel 13 interrupt
    DMA3_CH14_IRQHandler,                          // 125: AON Domain eDMA channel 14 interrupt
    DMA3_CH15_IRQHandler,                          // 126: AON Domain eDMA channel 15 interrupt
    DMA3_CH16_IRQHandler,                          // 127: AON Domain eDMA channel 16 interrupt
    DMA3_CH17_IRQHandler,                          // 128: AON Domain eDMA channel 17 interrupt
    DMA3_CH18_IRQHandler,                          // 129: AON Domain eDMA channel 18 interrupt
    DMA3_CH19_IRQHandler,                          // 130: AON Domain eDMA channel 19 interrupt
    DMA3_CH20_IRQHandler,                          // 131: AON Domain eDMA channel 20 interrupt
    DMA3_CH21_IRQHandler,                          // 132: AON Domain eDMA channel 21 interrupt
    DMA3_CH22_IRQHandler,                          // 133: AON Domain eDMA channel 22 interrupt
    DMA3_CH23_IRQHandler,                          // 134: AON Domain eDMA channel 23 interrupt
    DMA3_CH24_IRQHandler,                          // 135: AON Domain eDMA channel 24 interrupt
    DMA3_CH25_IRQHandler,                          // 136: AON Domain eDMA channel 25 interrupt
    DMA3_CH26_IRQHandler,                          // 137: AON Domain eDMA channel 26 interrupt
    DMA3_CH27_IRQHandler,                          // 138: AON Domain eDMA channel 27 interrupt
    DMA3_CH28_IRQHandler,                          // 139: AON Domain eDMA channel 28 interrupt
    DMA3_CH29_IRQHandler,                          // 140: AON Domain eDMA channel 29 interrupt
    DMA3_CH30_IRQHandler,                          // 141: AON Domain eDMA channel 30 interrupt
    DMA3_CH31_IRQHandler,                          // 142: AON Domain eDMA channel 31 interrupt
    DMA4_ERROR_IRQHandler,                          // 143: WAKEUP Domain eDMA error interrupt
    DMA4_CH0_CH1_CH32_CH33_IRQHandler,               // 144: WAKEUP Domain eDMA channel 0/1/32/33 interrupt
    DMA4_CH2_CH3_CH34_CH35_IRQHandler,               // 145: WAKEUP Domain eDMA channel 2/3/34/35 interrupt
    DMA4_CH4_CH5_CH36_CH37_IRQHandler,               // 146: WAKEUP Domain eDMA channel 4/5/36/37 interrupt
    DMA4_CH6_CH7_CH38_CH39_IRQHandler,               // 147: WAKEUP Domain eDMA channel 6/7/38/39 interrupt
    DMA4_CH8_CH9_CH40_CH41_IRQHandler,               // 148: WAKEUP Domain eDMA channel 8/9/40/41 interrupt
    DMA4_CH10_CH11_CH42_CH43_IRQHandler,             // 149: WAKEUP Domain eDMA channel 10/11/42/43 interrupt
    DMA4_CH12_CH13_CH44_CH45_IRQHandler,             // 150: WAKEUP Domain eDMA channel 12/13/44/45 interrupt
    DMA4_CH14_CH15_CH46_CH47_IRQHandler,             // 151: WAKEUP Domain eDMA channel 14/15/46/47 interrupt
    DMA4_CH16_CH17_CH48_CH49_IRQHandler,             // 152: WAKEUP Domain eDMA channel 16/17/48/49 interrupt
    DMA4_CH18_CH19_CH50_CH51_IRQHandler,             // 153: WAKEUP Domain eDMA channel 18/19/50/51 interrupt
    DMA4_CH20_CH21_CH52_CH53_IRQHandler,             // 154: WAKEUP Domain eDMA channel 20/21/52/53 interrupt
    DMA4_CH22_CH23_CH54_CH55_IRQHandler,             // 155: WAKEUP Domain eDMA channel 22/23/54/55 interrupt
    DMA4_CH24_CH25_CH56_CH57_IRQHandler,             // 156: WAKEUP Domain eDMA channel 24/25/56/57 interrupt
    DMA4_CH26_CH27_CH58_CH59_IRQHandler,             // 157: WAKEUP Domain eDMA channel 26/27/58/59 interrupt
    DMA4_CH28_CH29_CH60_CH61_IRQHandler,             // 158: WAKEUP Domain eDMA channel 28/29/60/61 interrupt
    DMA4_CH30_CH31_CH62_CH63_IRQHandler,             // 159: WAKEUP Domain eDMA channel 30/31/62/63 interrupt
    XBAR1_CH0_CH1_IRQHandler,                        // 160: XBAR1 channel 0/1 interrupt
    XBAR1_CH2_CH3_IRQHandler,                        // 161: XBAR1 channel 2/3 interrupt
    SINC3_CH0_CH1_CH2_CH3_IRQHandler,                // 162: SINC Filter Glue 3 channel 0/1/2/3
    EWM_IRQHandler,                          // 163: EWM reset out interrupt
    SEMC_IRQHandler,                          // 164: SEMC interrupt
    LPIT3_IRQHandler,                          // 165: LPIT3 interrupt
    LPTMR3_IRQHandler,                          // 166: LPTMR3 interrupt
    TMR4_IRQHandler,                          // 167: TMR4 interrupt
    LPI2C5_IRQHandler,                          // 168: LPI2C5 interrupt
    LPI2C6_IRQHandler,                          // 169: LPI2C6 interrupt
    SAI4_IRQHandler,                          // 170: SAI4 interrupt
    SPDIF_IRQHandler,                          // 171: SPDIF interrupt
    LPUART9_IRQHandler,                          // 172: LPUART9 interrupt
    LPUART10_IRQHandler,                          // 173: LPUART10 interrupt
    LPUART11_IRQHandler,                          // 174: LPUART11 interrupt
    LPUART12_IRQHandler,                          // 175: LPUART12 interrupt
    INTG_BOOTROM_DEBUG_CTRL_IRQHandler,              // 176: CM33, CM7, DAP access IRQ
    EDGELOCK_REQ1_IRQHandler,                        // 177: Edgelock reuqest 1 interrupt
    EDGELOCK_REQ2_IRQHandler,                        // 178: Edgelock reuqest 2 interrupt
    EDGELOCK_REQ3_IRQHandler,                        // 179: Edgelock reuqest 3 interrupt
    TMR3_IRQHandler,                          // 180: TMR3 interrupt
    JTAGC_IRQHandler,                          // 181: JTAGC SRC reset source
    M33_SYSRESET_REQ_IRQHandler,                     // 182: CM33 SYSREQRST SRC reset source
    M33_LOCKUP_IRQHandler,                          // 183: CM33 LOCKUP SRC reset source
    M7_SYSRESET_REQ_IRQHandler,                      // 184: CM33 SYSREQRST SRC reset source
    M7_LOCKUP_IRQHandler,                          // 185: CM33 LOCKUP SRC reset source
    PWM2_FAULT_IRQHandler,                          // 186: PWM2 fault or reload error interrupt
    PWM2_0_IRQHandler,                          // 187: PWM2 capture 0, compare 0, or reload 0 interrupt
    PWM2_1_IRQHandler,                          // 188: PWM2 capture 1, compare 1, or reload 1 interrupt
    PWM2_2_IRQHandler,                          // 189: PWM2 capture 2, compare 2, or reload 2 interrupt
    PWM2_3_IRQHandler,                          // 190: PWM2 capture 3, compare 3, or reload 3 interrupt
    PWM3_FAULT_IRQHandler,                          // 191: PWM3 fault or reload error interrupt
    PWM3_0_IRQHandler,                          // 192: PWM3 capture 0, compare 0, or reload 0 interrupt
    PWM3_1_IRQHandler,                          // 193: PWM3 capture 1, compare 1, or reload 1 interrupt
    PWM3_2_IRQHandler,                          // 194: PWM3 capture 2, compare 2, or reload 2 interrupt
    PWM3_3_IRQHandler,                          // 195: PWM3 capture 3, compare 3, or reload 3 interrupt
    PWM4_FAULT_IRQHandler,                          // 196: PWM4 fault or reload error interrupt
    PWM4_0_IRQHandler,                          // 197: PWM4 capture 0, compare 0, or reload 0 interrupt
    PWM4_1_IRQHandler,                          // 198: PWM4 capture 1, compare 1, or reload 1 interrupt
    PWM4_2_IRQHandler,                          // 199: PWM4 capture 2, compare 2, or reload 2 interrupt
    PWM4_3_IRQHandler,                          // 200: PWM4 capture 3, compare 3, or reload 3 interrupt
    EQDC1_IRQHandler,                          // 201: EQDC1 interrupt
    EQDC2_IRQHandler,                          // 202: EQDC2 interrupt
    EQDC3_IRQHandler,                          // 203: EQDC3 interrupt
    EQDC4_IRQHandler,                          // 204: EQDC4 interrupt
    ADC2_IRQHandler,                          // 205: ADC2 interrupt
    DCDC_IRQHandler,                          // 206: DCDC brown out interrupt
    CAN3_IRQHandler,                          // 207: CAN3 interrupt
    CAN3_ERROR_IRQHandler,                          // 208: CAN3 error interrupt
    DAC_IRQHandler,                          // 209: DAC interrupt
    LPSPI5_IRQHandler,                          // 210: LPSPI5 interrupt
    LPSPI6_IRQHandler,                          // 211: LPSPI6 interrupt
    LPUART7_IRQHandler,                          // 212: LPUART7 interrupt
    LPUART8_IRQHandler,                          // 213: LPUART8 interrupt
    SAI2_IRQHandler,                          // 214: SAI2 interrupt
    SAI3_IRQHandler,                          // 215: SAI3 interrupt
    ACMP1_IRQHandler,                          // 216: CMP1 interrupt
    ACMP2_IRQHandler,                          // 217: CMP2 interrupt
    ACMP3_IRQHandler,                          // 218: CMP3 interrupt
    ACMP4_IRQHandler,                          // 219: CMP4 interrupt
    CM7_PS_IRQHandler,                          // 220: M7 PS Tag/Data Parity Error
    CM7_MCM_IRQHandler,                          // 221: M7 MCM interrupt
    CM33_MCM_IRQHandler,                          // 222: M33 MCM interrupt
    Reserved223_IRQHandler,                          // 223: Reserved interrupt
    SAFETY_CLK_MON_IRQHandler,                       // 224: Safety clock monitor interrupt
    GPT1_IRQHandler,                          // 225: GPT1 interrupt
    GPT2_IRQHandler,                          // 226: GPT2 interrupt
    KPP_IRQHandler,                          // 227: KPP interrupt
    USBPHY1_IRQHandler,                          // 228: USBPHY1 interrupt
    USBPHY2_IRQHandler,                          // 229: USBPHY2 interrupt
    USB_OTG2_IRQHandler,                          // 230: USBOTG2 interrupt
    USB_OTG1_IRQHandler,                          // 231: USBOTG1 interrupt
    FLEXSPI_SLV_IRQHandler,                          // 232: FLEXSPI follower interrupt
    NETC_IRQHandler,                          // 233: NETC interrupt
    MSGINTR1_IRQHandler,                          // 234: MSGINTR1 interrupt
    MSGINTR2_IRQHandler,                          // 235: MSGINTR2 interrupt
    MSGINTR3_IRQHandler,                          // 236: MSGINTR3 interrupt
    MSGINTR4_IRQHandler,                          // 237: MSGINTR4 interrupt
    MSGINTR5_IRQHandler,                          // 238: MSGINTR5 interrupt
    MSGINTR6_IRQHandler,                          // 239: MSGINTR6 interrupt
    SINC1_CH0_IRQHandler,                          // 240: SINC Filter Glue 1 channel 0
    SINC1_CH1_IRQHandler,                          // 241: SINC Filter Glue 1 channel 1
    SINC1_CH2_IRQHandler,                          // 242: SINC Filter Glue 1 channel 2
    SINC1_CH3_IRQHandler,                          // 243: SINC Filter Glue 1 channel 3
    SINC2_CH0_IRQHandler,                          // 244: SINC Filter Glue 2 channel 0
    SINC2_CH1_IRQHandler,                          // 245: SINC Filter Glue 2 channel 1
    SINC2_CH2_IRQHandler,                          // 246: SINC Filter Glue 2 channel 2
    SINC2_CH3_IRQHandler,                          // 247: SINC Filter Glue 2 channel 3
    GPIO4_IRQHandler,                          // 248: GPIO4 interrupt
    TMR2_IRQHandler,                          // 249: TMR2 interrupt
    GPIO5_IRQHandler,                          // 250: GPIO5 interrupt
    ASRC_IRQHandler,                          // 251: ASRC interrupt
    GPIO6_IRQHandler,                          // 252: GPIO6 interrupt
    DBG_TRACE_IRQHandler,                          // 253: JTAGSW DAP MDM-AP SRC reset source
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

__attribute__((section(".after_vectors.init_stack_heap"))) void misc_init(unsigned int start, unsigned int len)
{
    unsigned int *pulDest = (unsigned int *)start;
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
extern unsigned int _StackSize;
extern unsigned int _HeapSize;
extern unsigned int _pvHeapStart;

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
#else
    // Disable Watchdog
    volatile unsigned int *WDOG1_WCR = (unsigned int *) 0x400B8000;
    *WDOG1_WCR = *WDOG1_WCR & ~(1 << 2);
    volatile unsigned int *WDOG2_WCR = (unsigned int *) 0x400D0000;
    *WDOG2_WCR = *WDOG2_WCR & ~(1 << 2);
    // Write watchdog update key to unlock
    *((volatile unsigned int *)0x424B0004) = 0xD928C520;
    // Set timeout value
    *((volatile unsigned int *)0x424B0008) = 0xFFFF;
    // Now disable watchdog via control register
    volatile unsigned int *RTWDOG_CS = (unsigned int *) 0x424B0000;
    *RTWDOG_CS = (*RTWDOG_CS & ~(1 << 7)) | (1 << 5);

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

    // Heap and stack initialization
    ExeAddr    = (unsigned int)_vStackBase;
    SectionLen = (unsigned int)&_StackSize;
    misc_init(ExeAddr, SectionLen);

    ExeAddr    = (unsigned int)&_pvHeapStart;
    SectionLen = (unsigned int)&_HeapSize;
    misc_init(ExeAddr, SectionLen);

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
WEAK void TMR1_IRQHandler(void)
{   TMR1_DriverIRQHandler();
}

WEAK void DAP_IRQHandler(void)
{   DAP_DriverIRQHandler();
}

WEAK void M7_CTI_TRIGGER_OUTPUT_IRQHandler(void)
{   M7_CTI_TRIGGER_OUTPUT_DriverIRQHandler();
}

WEAK void M33_CTI_TRIGGER_OUTPUT_IRQHandler(void)
{   M33_CTI_TRIGGER_OUTPUT_DriverIRQHandler();
}

WEAK void TMR5_IRQHandler(void)
{   TMR5_DriverIRQHandler();
}

WEAK void TMR6_IRQHandler(void)
{   TMR6_DriverIRQHandler();
}

WEAK void TMR7_IRQHandler(void)
{   TMR7_DriverIRQHandler();
}

WEAK void TMR8_IRQHandler(void)
{   TMR8_DriverIRQHandler();
}

WEAK void CAN1_IRQHandler(void)
{   CAN1_DriverIRQHandler();
}

WEAK void CAN1_ERROR_IRQHandler(void)
{   CAN1_ERROR_DriverIRQHandler();
}

WEAK void GPIO1_0_IRQHandler(void)
{   GPIO1_0_DriverIRQHandler();
}

WEAK void GPIO1_1_IRQHandler(void)
{   GPIO1_1_DriverIRQHandler();
}

WEAK void I3C1_IRQHandler(void)
{   I3C1_DriverIRQHandler();
}

WEAK void LPI2C1_IRQHandler(void)
{   LPI2C1_DriverIRQHandler();
}

WEAK void LPI2C2_IRQHandler(void)
{   LPI2C2_DriverIRQHandler();
}

WEAK void LPIT1_IRQHandler(void)
{   LPIT1_DriverIRQHandler();
}

WEAK void LPSPI1_IRQHandler(void)
{   LPSPI1_DriverIRQHandler();
}

WEAK void LPSPI2_IRQHandler(void)
{   LPSPI2_DriverIRQHandler();
}

WEAK void LPTMR1_IRQHandler(void)
{   LPTMR1_DriverIRQHandler();
}

WEAK void LPUART1_IRQHandler(void)
{   LPUART1_DriverIRQHandler();
}

WEAK void LPUART2_IRQHandler(void)
{   LPUART2_DriverIRQHandler();
}

WEAK void MU1_IRQHandler(void)
{   MU1_DriverIRQHandler();
}

WEAK void MU2_IRQHandler(void)
{   MU2_DriverIRQHandler();
}

WEAK void PWM1_FAULT_IRQHandler(void)
{   PWM1_FAULT_DriverIRQHandler();
}

WEAK void PWM1_0_IRQHandler(void)
{   PWM1_0_DriverIRQHandler();
}

WEAK void PWM1_1_IRQHandler(void)
{   PWM1_1_DriverIRQHandler();
}

WEAK void PWM1_2_IRQHandler(void)
{   PWM1_2_DriverIRQHandler();
}

WEAK void PWM1_3_IRQHandler(void)
{   PWM1_3_DriverIRQHandler();
}

WEAK void EDGELOCK_TRUST_MUA_RX_FULL_IRQHandler(void)
{   EDGELOCK_TRUST_MUA_RX_FULL_DriverIRQHandler();
}

WEAK void EDGELOCK_TRUST_MUA_TX_EMPTY_IRQHandler(void)
{   EDGELOCK_TRUST_MUA_TX_EMPTY_DriverIRQHandler();
}

WEAK void EDGELOCK_APPS_CORE_MUA_RX_FULL_IRQHandler(void)
{   EDGELOCK_APPS_CORE_MUA_RX_FULL_DriverIRQHandler();
}

WEAK void EDGELOCK_APPS_CORE_MUA_TX_EMPTY_IRQHandler(void)
{   EDGELOCK_APPS_CORE_MUA_TX_EMPTY_DriverIRQHandler();
}

WEAK void EDGELOCK_REALTIME_CORE_MUA_RX_FULL_IRQHandler(void)
{   EDGELOCK_REALTIME_CORE_MUA_RX_FULL_DriverIRQHandler();
}

WEAK void EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_IRQHandler(void)
{   EDGELOCK_REALTIME_CORE_MUA_TX_EMPTY_DriverIRQHandler();
}

WEAK void EDGELOCK_SECURE_IRQHandler(void)
{   EDGELOCK_SECURE_DriverIRQHandler();
}

WEAK void EDGELOCK_NONSECURE_IRQHandler(void)
{   EDGELOCK_NONSECURE_DriverIRQHandler();
}

WEAK void TPM1_IRQHandler(void)
{   TPM1_DriverIRQHandler();
}

WEAK void TPM2_IRQHandler(void)
{   TPM2_DriverIRQHandler();
}

WEAK void RTWDOG1_IRQHandler(void)
{   RTWDOG1_DriverIRQHandler();
}

WEAK void RTWDOG2_IRQHandler(void)
{   RTWDOG2_DriverIRQHandler();
}

WEAK void TRDC_MGR_AON_IRQHandler(void)
{   TRDC_MGR_AON_DriverIRQHandler();
}

WEAK void PDM_HWVAD_EVENT_IRQHandler(void)
{   PDM_HWVAD_EVENT_DriverIRQHandler();
}

WEAK void PDM_HWVAD_ERROR_IRQHandler(void)
{   PDM_HWVAD_ERROR_DriverIRQHandler();
}

WEAK void PDM_EVENT_IRQHandler(void)
{   PDM_EVENT_DriverIRQHandler();
}

WEAK void PDM_ERROR_IRQHandler(void)
{   PDM_ERROR_DriverIRQHandler();
}

WEAK void SAI1_IRQHandler(void)
{   SAI1_DriverIRQHandler();
}

WEAK void CM33_PS_IRQHandler(void)
{   CM33_PS_DriverIRQHandler();
}

WEAK void CM33_TCM_ECC_IRQHandler(void)
{   CM33_TCM_ECC_DriverIRQHandler();
}

WEAK void CM33_TCM_ERROR_IRQHandler(void)
{   CM33_TCM_ERROR_DriverIRQHandler();
}

WEAK void CM7_TCM_ECC_IRQHandler(void)
{   CM7_TCM_ECC_DriverIRQHandler();
}

WEAK void CM7_TCM_ERROR_IRQHandler(void)
{   CM7_TCM_ERROR_DriverIRQHandler();
}

WEAK void CAN2_IRQHandler(void)
{   CAN2_DriverIRQHandler();
}

WEAK void CAN2_ERROR_IRQHandler(void)
{   CAN2_ERROR_DriverIRQHandler();
}

WEAK void FLEXIO1_IRQHandler(void)
{   FLEXIO1_DriverIRQHandler();
}

WEAK void FLEXIO2_IRQHandler(void)
{   FLEXIO2_DriverIRQHandler();
}

WEAK void FLEXSPI1_IRQHandler(void)
{   FLEXSPI1_DriverIRQHandler();
}

WEAK void FLEXSPI2_IRQHandler(void)
{   FLEXSPI2_DriverIRQHandler();
}

WEAK void GPIO2_0_IRQHandler(void)
{   GPIO2_0_DriverIRQHandler();
}

WEAK void GPIO2_1_IRQHandler(void)
{   GPIO2_1_DriverIRQHandler();
}

WEAK void GPIO3_0_IRQHandler(void)
{   GPIO3_0_DriverIRQHandler();
}

WEAK void GPIO3_1_IRQHandler(void)
{   GPIO3_1_DriverIRQHandler();
}

WEAK void I3C2_IRQHandler(void)
{   I3C2_DriverIRQHandler();
}

WEAK void LPI2C3_IRQHandler(void)
{   LPI2C3_DriverIRQHandler();
}

WEAK void LPI2C4_IRQHandler(void)
{   LPI2C4_DriverIRQHandler();
}

WEAK void LPIT2_IRQHandler(void)
{   LPIT2_DriverIRQHandler();
}

WEAK void LPSPI3_IRQHandler(void)
{   LPSPI3_DriverIRQHandler();
}

WEAK void LPSPI4_IRQHandler(void)
{   LPSPI4_DriverIRQHandler();
}

WEAK void LPTMR2_IRQHandler(void)
{   LPTMR2_DriverIRQHandler();
}

WEAK void LPUART3_IRQHandler(void)
{   LPUART3_DriverIRQHandler();
}

WEAK void LPUART4_IRQHandler(void)
{   LPUART4_DriverIRQHandler();
}

WEAK void LPUART5_IRQHandler(void)
{   LPUART5_DriverIRQHandler();
}

WEAK void LPUART6_IRQHandler(void)
{   LPUART6_DriverIRQHandler();
}

WEAK void Reserved88_IRQHandler(void)
{   Reserved88_DriverIRQHandler();
}

WEAK void BBNSM_IRQHandler(void)
{   BBNSM_DriverIRQHandler();
}

WEAK void SYS_CTR1_IRQHandler(void)
{   SYS_CTR1_DriverIRQHandler();
}

WEAK void TPM3_IRQHandler(void)
{   TPM3_DriverIRQHandler();
}

WEAK void TPM4_IRQHandler(void)
{   TPM4_DriverIRQHandler();
}

WEAK void TPM5_IRQHandler(void)
{   TPM5_DriverIRQHandler();
}

WEAK void TPM6_IRQHandler(void)
{   TPM6_DriverIRQHandler();
}

WEAK void RTWDOG3_IRQHandler(void)
{   RTWDOG3_DriverIRQHandler();
}

WEAK void RTWDOG4_IRQHandler(void)
{   RTWDOG4_DriverIRQHandler();
}

WEAK void RTWDOG5_IRQHandler(void)
{   RTWDOG5_DriverIRQHandler();
}

WEAK void TRDC_MGR_WKUP_IRQHandler(void)
{   TRDC_MGR_WKUP_DriverIRQHandler();
}

WEAK void TMPSNS_INT_IRQHandler(void)
{   TMPSNS_INT_DriverIRQHandler();
}

WEAK void BBSM_IRQHandler(void)
{   BBSM_DriverIRQHandler();
}

WEAK void LDO_AON_ANA_IRQHandler(void)
{   LDO_AON_ANA_DriverIRQHandler();
}

WEAK void USDHC1_IRQHandler(void)
{   USDHC1_DriverIRQHandler();
}

WEAK void USDHC2_IRQHandler(void)
{   USDHC2_DriverIRQHandler();
}

WEAK void TRDC_MGR_MEGA_IRQHandler(void)
{   TRDC_MGR_MEGA_DriverIRQHandler();
}

WEAK void SFA_IRQHandler(void)
{   SFA_DriverIRQHandler();
}

WEAK void LDO_AON_DIG_IRQHandler(void)
{   LDO_AON_DIG_DriverIRQHandler();
}

WEAK void MECC1_IRQHandler(void)
{   MECC1_DriverIRQHandler();
}

WEAK void MECC2_IRQHandler(void)
{   MECC2_DriverIRQHandler();
}

WEAK void ADC1_IRQHandler(void)
{   ADC1_DriverIRQHandler();
}

WEAK void DMA_ERROR_IRQHandler(void)
{   DMA_ERROR_DriverIRQHandler();
}

WEAK void DMA3_CH0_IRQHandler(void)
{   DMA3_CH0_DriverIRQHandler();
}

WEAK void DMA3_CH1_IRQHandler(void)
{   DMA3_CH1_DriverIRQHandler();
}

WEAK void DMA3_CH2_IRQHandler(void)
{   DMA3_CH2_DriverIRQHandler();
}

WEAK void DMA3_CH3_IRQHandler(void)
{   DMA3_CH3_DriverIRQHandler();
}

WEAK void DMA3_CH4_IRQHandler(void)
{   DMA3_CH4_DriverIRQHandler();
}

WEAK void DMA3_CH5_IRQHandler(void)
{   DMA3_CH5_DriverIRQHandler();
}

WEAK void DMA3_CH6_IRQHandler(void)
{   DMA3_CH6_DriverIRQHandler();
}

WEAK void DMA3_CH7_IRQHandler(void)
{   DMA3_CH7_DriverIRQHandler();
}

WEAK void DMA3_CH8_IRQHandler(void)
{   DMA3_CH8_DriverIRQHandler();
}

WEAK void DMA3_CH9_IRQHandler(void)
{   DMA3_CH9_DriverIRQHandler();
}

WEAK void DMA3_CH10_IRQHandler(void)
{   DMA3_CH10_DriverIRQHandler();
}

WEAK void DMA3_CH11_IRQHandler(void)
{   DMA3_CH11_DriverIRQHandler();
}

WEAK void DMA3_CH12_IRQHandler(void)
{   DMA3_CH12_DriverIRQHandler();
}

WEAK void DMA3_CH13_IRQHandler(void)
{   DMA3_CH13_DriverIRQHandler();
}

WEAK void DMA3_CH14_IRQHandler(void)
{   DMA3_CH14_DriverIRQHandler();
}

WEAK void DMA3_CH15_IRQHandler(void)
{   DMA3_CH15_DriverIRQHandler();
}

WEAK void DMA3_CH16_IRQHandler(void)
{   DMA3_CH16_DriverIRQHandler();
}

WEAK void DMA3_CH17_IRQHandler(void)
{   DMA3_CH17_DriverIRQHandler();
}

WEAK void DMA3_CH18_IRQHandler(void)
{   DMA3_CH18_DriverIRQHandler();
}

WEAK void DMA3_CH19_IRQHandler(void)
{   DMA3_CH19_DriverIRQHandler();
}

WEAK void DMA3_CH20_IRQHandler(void)
{   DMA3_CH20_DriverIRQHandler();
}

WEAK void DMA3_CH21_IRQHandler(void)
{   DMA3_CH21_DriverIRQHandler();
}

WEAK void DMA3_CH22_IRQHandler(void)
{   DMA3_CH22_DriverIRQHandler();
}

WEAK void DMA3_CH23_IRQHandler(void)
{   DMA3_CH23_DriverIRQHandler();
}

WEAK void DMA3_CH24_IRQHandler(void)
{   DMA3_CH24_DriverIRQHandler();
}

WEAK void DMA3_CH25_IRQHandler(void)
{   DMA3_CH25_DriverIRQHandler();
}

WEAK void DMA3_CH26_IRQHandler(void)
{   DMA3_CH26_DriverIRQHandler();
}

WEAK void DMA3_CH27_IRQHandler(void)
{   DMA3_CH27_DriverIRQHandler();
}

WEAK void DMA3_CH28_IRQHandler(void)
{   DMA3_CH28_DriverIRQHandler();
}

WEAK void DMA3_CH29_IRQHandler(void)
{   DMA3_CH29_DriverIRQHandler();
}

WEAK void DMA3_CH30_IRQHandler(void)
{   DMA3_CH30_DriverIRQHandler();
}

WEAK void DMA3_CH31_IRQHandler(void)
{   DMA3_CH31_DriverIRQHandler();
}

WEAK void DMA4_ERROR_IRQHandler(void)
{   DMA4_ERROR_DriverIRQHandler();
}

WEAK void DMA4_CH0_CH1_CH32_CH33_IRQHandler(void)
{   DMA4_CH0_CH1_CH32_CH33_DriverIRQHandler();
}

WEAK void DMA4_CH2_CH3_CH34_CH35_IRQHandler(void)
{   DMA4_CH2_CH3_CH34_CH35_DriverIRQHandler();
}

WEAK void DMA4_CH4_CH5_CH36_CH37_IRQHandler(void)
{   DMA4_CH4_CH5_CH36_CH37_DriverIRQHandler();
}

WEAK void DMA4_CH6_CH7_CH38_CH39_IRQHandler(void)
{   DMA4_CH6_CH7_CH38_CH39_DriverIRQHandler();
}

WEAK void DMA4_CH8_CH9_CH40_CH41_IRQHandler(void)
{   DMA4_CH8_CH9_CH40_CH41_DriverIRQHandler();
}

WEAK void DMA4_CH10_CH11_CH42_CH43_IRQHandler(void)
{   DMA4_CH10_CH11_CH42_CH43_DriverIRQHandler();
}

WEAK void DMA4_CH12_CH13_CH44_CH45_IRQHandler(void)
{   DMA4_CH12_CH13_CH44_CH45_DriverIRQHandler();
}

WEAK void DMA4_CH14_CH15_CH46_CH47_IRQHandler(void)
{   DMA4_CH14_CH15_CH46_CH47_DriverIRQHandler();
}

WEAK void DMA4_CH16_CH17_CH48_CH49_IRQHandler(void)
{   DMA4_CH16_CH17_CH48_CH49_DriverIRQHandler();
}

WEAK void DMA4_CH18_CH19_CH50_CH51_IRQHandler(void)
{   DMA4_CH18_CH19_CH50_CH51_DriverIRQHandler();
}

WEAK void DMA4_CH20_CH21_CH52_CH53_IRQHandler(void)
{   DMA4_CH20_CH21_CH52_CH53_DriverIRQHandler();
}

WEAK void DMA4_CH22_CH23_CH54_CH55_IRQHandler(void)
{   DMA4_CH22_CH23_CH54_CH55_DriverIRQHandler();
}

WEAK void DMA4_CH24_CH25_CH56_CH57_IRQHandler(void)
{   DMA4_CH24_CH25_CH56_CH57_DriverIRQHandler();
}

WEAK void DMA4_CH26_CH27_CH58_CH59_IRQHandler(void)
{   DMA4_CH26_CH27_CH58_CH59_DriverIRQHandler();
}

WEAK void DMA4_CH28_CH29_CH60_CH61_IRQHandler(void)
{   DMA4_CH28_CH29_CH60_CH61_DriverIRQHandler();
}

WEAK void DMA4_CH30_CH31_CH62_CH63_IRQHandler(void)
{   DMA4_CH30_CH31_CH62_CH63_DriverIRQHandler();
}

WEAK void XBAR1_CH0_CH1_IRQHandler(void)
{   XBAR1_CH0_CH1_DriverIRQHandler();
}

WEAK void XBAR1_CH2_CH3_IRQHandler(void)
{   XBAR1_CH2_CH3_DriverIRQHandler();
}

WEAK void SINC3_CH0_CH1_CH2_CH3_IRQHandler(void)
{   SINC3_CH0_CH1_CH2_CH3_DriverIRQHandler();
}

WEAK void EWM_IRQHandler(void)
{   EWM_DriverIRQHandler();
}

WEAK void SEMC_IRQHandler(void)
{   SEMC_DriverIRQHandler();
}

WEAK void LPIT3_IRQHandler(void)
{   LPIT3_DriverIRQHandler();
}

WEAK void LPTMR3_IRQHandler(void)
{   LPTMR3_DriverIRQHandler();
}

WEAK void TMR4_IRQHandler(void)
{   TMR4_DriverIRQHandler();
}

WEAK void LPI2C5_IRQHandler(void)
{   LPI2C5_DriverIRQHandler();
}

WEAK void LPI2C6_IRQHandler(void)
{   LPI2C6_DriverIRQHandler();
}

WEAK void SAI4_IRQHandler(void)
{   SAI4_DriverIRQHandler();
}

WEAK void SPDIF_IRQHandler(void)
{   SPDIF_DriverIRQHandler();
}

WEAK void LPUART9_IRQHandler(void)
{   LPUART9_DriverIRQHandler();
}

WEAK void LPUART10_IRQHandler(void)
{   LPUART10_DriverIRQHandler();
}

WEAK void LPUART11_IRQHandler(void)
{   LPUART11_DriverIRQHandler();
}

WEAK void LPUART12_IRQHandler(void)
{   LPUART12_DriverIRQHandler();
}

WEAK void INTG_BOOTROM_DEBUG_CTRL_IRQHandler(void)
{   INTG_BOOTROM_DEBUG_CTRL_DriverIRQHandler();
}

WEAK void EDGELOCK_REQ1_IRQHandler(void)
{   EDGELOCK_REQ1_DriverIRQHandler();
}

WEAK void EDGELOCK_REQ2_IRQHandler(void)
{   EDGELOCK_REQ2_DriverIRQHandler();
}

WEAK void EDGELOCK_REQ3_IRQHandler(void)
{   EDGELOCK_REQ3_DriverIRQHandler();
}

WEAK void TMR3_IRQHandler(void)
{   TMR3_DriverIRQHandler();
}

WEAK void JTAGC_IRQHandler(void)
{   JTAGC_DriverIRQHandler();
}

WEAK void M33_SYSRESET_REQ_IRQHandler(void)
{   M33_SYSRESET_REQ_DriverIRQHandler();
}

WEAK void M33_LOCKUP_IRQHandler(void)
{   M33_LOCKUP_DriverIRQHandler();
}

WEAK void M7_SYSRESET_REQ_IRQHandler(void)
{   M7_SYSRESET_REQ_DriverIRQHandler();
}

WEAK void M7_LOCKUP_IRQHandler(void)
{   M7_LOCKUP_DriverIRQHandler();
}

WEAK void PWM2_FAULT_IRQHandler(void)
{   PWM2_FAULT_DriverIRQHandler();
}

WEAK void PWM2_0_IRQHandler(void)
{   PWM2_0_DriverIRQHandler();
}

WEAK void PWM2_1_IRQHandler(void)
{   PWM2_1_DriverIRQHandler();
}

WEAK void PWM2_2_IRQHandler(void)
{   PWM2_2_DriverIRQHandler();
}

WEAK void PWM2_3_IRQHandler(void)
{   PWM2_3_DriverIRQHandler();
}

WEAK void PWM3_FAULT_IRQHandler(void)
{   PWM3_FAULT_DriverIRQHandler();
}

WEAK void PWM3_0_IRQHandler(void)
{   PWM3_0_DriverIRQHandler();
}

WEAK void PWM3_1_IRQHandler(void)
{   PWM3_1_DriverIRQHandler();
}

WEAK void PWM3_2_IRQHandler(void)
{   PWM3_2_DriverIRQHandler();
}

WEAK void PWM3_3_IRQHandler(void)
{   PWM3_3_DriverIRQHandler();
}

WEAK void PWM4_FAULT_IRQHandler(void)
{   PWM4_FAULT_DriverIRQHandler();
}

WEAK void PWM4_0_IRQHandler(void)
{   PWM4_0_DriverIRQHandler();
}

WEAK void PWM4_1_IRQHandler(void)
{   PWM4_1_DriverIRQHandler();
}

WEAK void PWM4_2_IRQHandler(void)
{   PWM4_2_DriverIRQHandler();
}

WEAK void PWM4_3_IRQHandler(void)
{   PWM4_3_DriverIRQHandler();
}

WEAK void EQDC1_IRQHandler(void)
{   EQDC1_DriverIRQHandler();
}

WEAK void EQDC2_IRQHandler(void)
{   EQDC2_DriverIRQHandler();
}

WEAK void EQDC3_IRQHandler(void)
{   EQDC3_DriverIRQHandler();
}

WEAK void EQDC4_IRQHandler(void)
{   EQDC4_DriverIRQHandler();
}

WEAK void ADC2_IRQHandler(void)
{   ADC2_DriverIRQHandler();
}

WEAK void DCDC_IRQHandler(void)
{   DCDC_DriverIRQHandler();
}

WEAK void CAN3_IRQHandler(void)
{   CAN3_DriverIRQHandler();
}

WEAK void CAN3_ERROR_IRQHandler(void)
{   CAN3_ERROR_DriverIRQHandler();
}

WEAK void DAC_IRQHandler(void)
{   DAC_DriverIRQHandler();
}

WEAK void LPSPI5_IRQHandler(void)
{   LPSPI5_DriverIRQHandler();
}

WEAK void LPSPI6_IRQHandler(void)
{   LPSPI6_DriverIRQHandler();
}

WEAK void LPUART7_IRQHandler(void)
{   LPUART7_DriverIRQHandler();
}

WEAK void LPUART8_IRQHandler(void)
{   LPUART8_DriverIRQHandler();
}

WEAK void SAI2_IRQHandler(void)
{   SAI2_DriverIRQHandler();
}

WEAK void SAI3_IRQHandler(void)
{   SAI3_DriverIRQHandler();
}

WEAK void ACMP1_IRQHandler(void)
{   ACMP1_DriverIRQHandler();
}

WEAK void ACMP2_IRQHandler(void)
{   ACMP2_DriverIRQHandler();
}

WEAK void ACMP3_IRQHandler(void)
{   ACMP3_DriverIRQHandler();
}

WEAK void ACMP4_IRQHandler(void)
{   ACMP4_DriverIRQHandler();
}

WEAK void CM7_PS_IRQHandler(void)
{   CM7_PS_DriverIRQHandler();
}

WEAK void CM7_MCM_IRQHandler(void)
{   CM7_MCM_DriverIRQHandler();
}

WEAK void CM33_MCM_IRQHandler(void)
{   CM33_MCM_DriverIRQHandler();
}

WEAK void Reserved223_IRQHandler(void)
{   Reserved223_DriverIRQHandler();
}

WEAK void SAFETY_CLK_MON_IRQHandler(void)
{   SAFETY_CLK_MON_DriverIRQHandler();
}

WEAK void GPT1_IRQHandler(void)
{   GPT1_DriverIRQHandler();
}

WEAK void GPT2_IRQHandler(void)
{   GPT2_DriverIRQHandler();
}

WEAK void KPP_IRQHandler(void)
{   KPP_DriverIRQHandler();
}

WEAK void USBPHY1_IRQHandler(void)
{   USBPHY1_DriverIRQHandler();
}

WEAK void USBPHY2_IRQHandler(void)
{   USBPHY2_DriverIRQHandler();
}

WEAK void USB_OTG2_IRQHandler(void)
{   USB_OTG2_DriverIRQHandler();
}

WEAK void USB_OTG1_IRQHandler(void)
{   USB_OTG1_DriverIRQHandler();
}

WEAK void FLEXSPI_SLV_IRQHandler(void)
{   FLEXSPI_SLV_DriverIRQHandler();
}

WEAK void NETC_IRQHandler(void)
{   NETC_DriverIRQHandler();
}

WEAK void MSGINTR1_IRQHandler(void)
{   MSGINTR1_DriverIRQHandler();
}

WEAK void MSGINTR2_IRQHandler(void)
{   MSGINTR2_DriverIRQHandler();
}

WEAK void MSGINTR3_IRQHandler(void)
{   MSGINTR3_DriverIRQHandler();
}

WEAK void MSGINTR4_IRQHandler(void)
{   MSGINTR4_DriverIRQHandler();
}

WEAK void MSGINTR5_IRQHandler(void)
{   MSGINTR5_DriverIRQHandler();
}

WEAK void MSGINTR6_IRQHandler(void)
{   MSGINTR6_DriverIRQHandler();
}

WEAK void SINC1_CH0_IRQHandler(void)
{   SINC1_CH0_DriverIRQHandler();
}

WEAK void SINC1_CH1_IRQHandler(void)
{   SINC1_CH1_DriverIRQHandler();
}

WEAK void SINC1_CH2_IRQHandler(void)
{   SINC1_CH2_DriverIRQHandler();
}

WEAK void SINC1_CH3_IRQHandler(void)
{   SINC1_CH3_DriverIRQHandler();
}

WEAK void SINC2_CH0_IRQHandler(void)
{   SINC2_CH0_DriverIRQHandler();
}

WEAK void SINC2_CH1_IRQHandler(void)
{   SINC2_CH1_DriverIRQHandler();
}

WEAK void SINC2_CH2_IRQHandler(void)
{   SINC2_CH2_DriverIRQHandler();
}

WEAK void SINC2_CH3_IRQHandler(void)
{   SINC2_CH3_DriverIRQHandler();
}

WEAK void GPIO4_IRQHandler(void)
{   GPIO4_DriverIRQHandler();
}

WEAK void TMR2_IRQHandler(void)
{   TMR2_DriverIRQHandler();
}

WEAK void GPIO5_IRQHandler(void)
{   GPIO5_DriverIRQHandler();
}

WEAK void ASRC_IRQHandler(void)
{   ASRC_DriverIRQHandler();
}

WEAK void GPIO6_IRQHandler(void)
{   GPIO6_DriverIRQHandler();
}

WEAK void DBG_TRACE_IRQHandler(void)
{   DBG_TRACE_DriverIRQHandler();
}

//*****************************************************************************

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
