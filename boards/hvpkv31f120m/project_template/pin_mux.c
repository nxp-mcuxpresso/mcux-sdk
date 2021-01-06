/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: MKV31F512xxx12
package_id: MKV31F512VLL12
mcu_data: ksdk2_0
processor_version: 0.0.18
board: HVP-KV31F120M
pin_labels:
- {pin_num: '39', pin_signal: PTA5/FTM0_CH2/JTAG_TRST_b, label: USER_LED_2, identifier: LED_RED}
- {pin_num: '8', pin_signal: VDD8, label: 3.3V}
- {pin_num: '9', pin_signal: VSS9, label: GND}
- {pin_num: '22', pin_signal: VDDA, label: 3.3VA}
- {pin_num: '23', pin_signal: VREFH, label: 3.3VA}
- {pin_num: '24', pin_signal: VREFL, label: GNDA}
- {pin_num: '25', pin_signal: VSSA, label: GNDA}
- {pin_num: '29', pin_signal: VSS29, label: GND}
- {pin_num: '30', pin_signal: VDD30, label: 3.3V}
- {pin_num: '40', pin_signal: VDD40, label: 3.3V}
- {pin_num: '41', pin_signal: VSS41, label: GND}
- {pin_num: '48', pin_signal: VDD48, label: 3.3V}
- {pin_num: '49', pin_signal: VSS49, label: GND}
- {pin_num: '60', pin_signal: VSS60, label: GND}
- {pin_num: '61', pin_signal: VDD61, label: 3.3V}
- {pin_num: '75', pin_signal: VDD75, label: 3.3V}
- {pin_num: '89', pin_signal: VDD89, label: 3.3V}
- {pin_num: '88', pin_signal: VSS88, label: GND}
- {pin_num: '74', pin_signal: VSS74, label: GND}
- {pin_num: '34', pin_signal: PTA0/UART0_CTS_b/FTM0_CH5/EWM_IN/JTAG_TCLK/SWD_CLK/EZP_CLK, label: 'J3[4]/U4[11]/U5[13]/SWCLK/SWDCLK_ISOLATED'}
- {pin_num: '37', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/FTM2_FLT0/EWM_OUT_b/JTAG_TMS/SWD_DIO, label: 'J3[2]/U4[3]/U5[14]/SWDIO/SWDIO_ISOLATED'}
- {pin_num: '36', pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J3[6]/U5[12]/SWO/SWO_ISOLATED'}
- {pin_num: '52', pin_signal: RESET_b, label: 'J3[10]/U5[11]/SW1/''/RESET''/''RESET_ISOLATED'''}
- {pin_num: '62', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, label: 'U2[24]/U6[13]/TxD_sda/UART_TX_TGTMCU', identifier: UART_TX_TGTMCU}
- {pin_num: '63', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, label: 'U2[25]/U6[14]/RxD_sda/UART_RX_TGTMCU', identifier: UART_RX_TGTMCU}
- {pin_num: '12', pin_signal: ADC0_SE6a/PTE18/SPI0_SOUT/UART2_CTS_b/I2C0_SDA, label: MOSI/TP21}
- {pin_num: '11', pin_signal: ADC0_SE5a/PTE17/SPI0_SCK/UART2_RX/FTM_CLKIN1/LPTMR0_ALT3, label: 'MB_J3[2]/MB_J11[B27]/MB_U1[12]/MB_U3[26]/MB_TP2/MB_TP10/MB_RxD/J4[B27]/RxD/MISO/TP19',
  identifier: RXD}
- {pin_num: '93', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/LPUART0_RTS_b, label: '''/SS''/TP18'}
- {pin_num: '94', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, label: SCK/TP20}
- {pin_num: '95', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL, label: SCL0/TP23}
- {pin_num: '96', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA, label: SDA0/TP22}
- {pin_num: '65', pin_signal: PTB19/FTM2_CH1/FB_OE_b/FTM2_QD_PHB, label: 'MB_J11[B20]/MB_U9[4]/MB_USER_LED/J4[B20]/USER_LED', identifier: LED_GREEN}
- {pin_num: '1', pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA, label: 'MB_J1[1]/MB_J2[3]/MB_J11[A31]/MB_TxD_1/MB_TxD_EXT/J4[A31]/TxD1', identifier: TXD_1}
- {pin_num: '2', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN, label: 'MB_J2[4]/MB_J3[4]/MB_J11[A32]/MB_RxD_1/MB_RxD_EXT/J4[A32]/RxD1',
  identifier: RXD_1}
- {pin_num: '3', pin_signal: ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b, label: NC}
- {pin_num: '4', pin_signal: ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SPI1_SOUT, label: NC}
- {pin_num: '5', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/LPUART0_TX, label: NC}
- {pin_num: '6', pin_signal: PTE5/SPI1_PCS2/LPUART0_RX/FTM3_CH0, label: 'MB_J11[A22]/MB_U14[4]/MB_TP15/MB_PWM_PFC2/J4[A22]/PWM8', identifier: PWM_PFC2}
- {pin_num: '7', pin_signal: PTE6/SPI1_PCS3/LPUART0_CTS_b/FTM3_CH1, label: 'MB_J11[A23]/MB_U14[2]/MB_TP12/MB_PWM_PFC1/J4[A23]/PWM9', identifier: PWM_PFC1}
- {pin_num: '10', pin_signal: ADC0_SE4a/PTE16/SPI0_PCS0/UART2_TX/FTM_CLKIN0/FTM0_FLT3, label: 'MB_J1[3]/MB_J11[B26]/MB_U1[13]/MB_U3[25]/MB_TP3/MB_TP7/MB_TxD/J4[B26]/TxD',
  identifier: TXD}
- {pin_num: '13', pin_signal: ADC0_SE7a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL, label: MISO/TP19}
- {pin_num: '14', pin_signal: ADC0_DP1, label: NC}
- {pin_num: '15', pin_signal: ADC0_DM1, label: TP24}
- {pin_num: '16', pin_signal: ADC1_DP1/ADC0_DP2, label: NC}
- {pin_num: '17', pin_signal: ADC1_DM1/ADC0_DM2, label: 'MB_J11[B8]/MB_TP41/MB_BEMF_sense_C/MB_Phase_C/J4[B8]/BEMF_C', identifier: BEMF_C}
- {pin_num: '18', pin_signal: ADC0_DP0/ADC1_DP3, label: 'MB_J11[A5]/MB_U8A[1]/MB_TP37/MB_I_sense_C/J4[A5]/I_phC', identifier: I_PH_C_2}
- {pin_num: '54', pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX, label: 'MB_J11[A5]/MB_U8A[1]/MB_TP37/MB_I_sense_C/J4[A5]/I_phC',
  identifier: I_PH_C}
- {pin_num: '19', pin_signal: ADC0_DM0/ADC1_DM3, label: 'MB_J11[B6]/MB_TP44/MB_BEMF_sense_A/MB_Phase_A/J4[B6]/BEMF_A', identifier: BEMF_A}
- {pin_num: '20', pin_signal: ADC1_DP0/ADC0_DP3, label: 'MB_J11[A4]/MB_U11B[7]/MB_TP40/MB_I_sense_B/J4[A4]/I_phB', identifier: I_PH_B}
- {pin_num: '21', pin_signal: ADC1_DM0/ADC0_DM3, label: 'MB_J11[B7]/MB_TP43/MB_BEMF_sense_B/MB_Phase_B/J4[B7]/BEMF_B', identifier: BEMF_B}
- {pin_num: '26', pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18, label: 'MB_J11[B3]/MB_U8B[7]/MB_TP34/MB_I_sense_DCB/J4[B3]/I_dcb', identifier: I_DCB}
- {pin_num: '27', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'MB_J11[A7]/MB_TP18/MB_Vin/J4[A7]/V_in', identifier: V_IN}
- {pin_num: '28', pin_signal: DAC1_OUT/CMP0_IN4/ADC1_SE23, label: 'MB_J11[A7]/MB_TP18/MB_Vin/J4[A7]/V_in', identifier: V_IN_2}
- {pin_num: '31', pin_signal: ADC0_SE17/PTE24/FTM0_CH0/I2C0_SCL/EWM_OUT_b, label: 'MB_J11[B17]/J4[B17]/MB_TP_29'}
- {pin_num: '32', pin_signal: ADC0_SE18/PTE25/FTM0_CH1/I2C0_SDA/EWM_IN, label: NC}
- {pin_num: '33', pin_signal: PTE26/CLKOUT32K, label: NC}
- {pin_num: '35', pin_signal: PTA1/UART0_RX/FTM0_CH6/CMP0_OUT/FTM2_QD_PHA/FTM1_CH1/JTAG_TDI/EZP_DI, label: NC}
- {pin_num: '38', pin_signal: PTA4/LLWU_P3/FTM0_CH1/FTM0_FLT3/NMI_b/EZP_CS_b, label: nmi, identifier: NMI}
- {pin_num: '42', pin_signal: PTA12/FTM1_CH0/FTM1_QD_PHA, label: 'MB_J9[3]/MB_J11[B14]/MB_TP13/MB_ENC_PhaseA/J4[B14]/TM0', identifier: ENC_PHASE_A}
- {pin_num: '43', pin_signal: PTA13/LLWU_P4/FTM1_CH1/FTM1_QD_PHB, label: 'MB_J9[4]/MB_J11[B15]/MB_TP17/MB_ENC_PhaseB/J4[B15]/TM1', identifier: ENC_PHASE_B}
- {pin_num: '44', pin_signal: PTA14/SPI0_PCS0/UART0_TX, label: NC}
- {pin_num: '45', pin_signal: PTA15/SPI0_SCK/UART0_RX, label: NC}
- {pin_num: '46', pin_signal: PTA16/SPI0_SOUT/UART0_CTS_b, label: NC}
- {pin_num: '47', pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b, label: NC}
- {pin_num: '50', pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, label: NC}
- {pin_num: '51', pin_signal: XTAL0/PTA19/FTM0_FLT0/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, label: 'MB_J11[A25]/MB_U12[11]/MB_TP28/MB_FAULT/MB_FAULT_1/MB_PFC_overcurrent/J4[A25]/FAULT_1',
  identifier: FAULT_1}
- {pin_num: '53', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX, label: 'MB_J11[A3]/MB_U11A[1]/MB_TP45/MB_I_sense_A/J4[A3]/I_phA',
  identifier: I_PH_A}
- {pin_num: '55', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/FTM0_FLT3, label: 'MB_J11[B4]/MB_TP31/MB_V_sense_DCB/MB_DCB_Pos/J4[B4]/U_dcb', identifier: U_DCB}
- {pin_num: '56', pin_signal: ADC0_SE13/PTB3/I2C0_SDA/UART0_CTS_b/FTM0_FLT0, label: NC}
- {pin_num: '57', pin_signal: PTB9/SPI1_PCS1/LPUART0_CTS_b/FB_AD20, label: NC}
- {pin_num: '58', pin_signal: ADC1_SE14/PTB10/SPI1_PCS0/LPUART0_RX/FB_AD19/FTM0_FLT1, label: 'MB_J11[A30]/MB_TP22/J4[A30]/MB_TP_22'}
- {pin_num: '59', pin_signal: ADC1_SE15/PTB11/SPI1_SCK/LPUART0_TX/FB_AD18/FTM0_FLT2, label: 'MB_J11[A29]/MB_TP24/J4[A29]/MB_TP_24'}
- {pin_num: '64', pin_signal: PTB18/FTM2_CH0/FB_AD15/FTM2_QD_PHA, label: NC}
- {pin_num: '66', pin_signal: PTB20/FB_AD31/CMP0_OUT, label: NC}
- {pin_num: '67', pin_signal: PTB21/FB_AD30/CMP1_OUT, label: NC}
- {pin_num: '68', pin_signal: PTB22/FB_AD29, label: NC}
- {pin_num: '69', pin_signal: PTB23/SPI0_PCS5/FB_AD28, label: NC}
- {pin_num: '70', pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/FB_AD14/FTM0_FLT1/SPI0_PCS0, label: 'MB_J11[B25]/MB_U9[2]/MB_TP_35/MB_MCU_BRAKE/J4[B25]/MCU_BRAKE',
  identifier: MCU_BRAKE}
- {pin_num: '71', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/LPUART0_RTS_b, label: 'MB_J11[A14]/MB_U12[18]/MB_PWM_AT/J4[A14]/PWM0',
  identifier: PWM_AT}
- {pin_num: '72', pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/LPUART0_CTS_b, label: 'MB_J11[A15]/MB_U12[12]/MB_PWM_AB/J4[A15]/PWM1',
  identifier: PWM_AB}
- {pin_num: '73', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/LPUART0_RX, label: 'MB_J11[A6]/MB_TP16/MB_TACHO/J4[A6]/TACHO', identifier: TACHO}
- {pin_num: '76', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT/LPUART0_TX, label: 'MB_J11[A17]/MB_U12[13]/MB_PWM_BB/J4[A17]/PWM3', identifier: PWM_BB}
- {pin_num: '77', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/FB_AD10/CMP0_OUT/FTM0_CH2, label: 'MB_J11[A16]/MB_U12[19]/MB_PWM_BT/J4[A16]/PWM2', identifier: PWM_BT}
- {pin_num: '78', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/FB_AD9/I2C0_SCL, label: 'MB_J11[B21]/MB_PFC_zc_2/J4[B21]/MB_TP_27', identifier: PFC_ZC_2}
- {pin_num: '79', pin_signal: CMP0_IN1/PTC7/SPI0_SIN/FB_AD8/I2C0_SDA, label: 'MB_J11[B22]/MB_PFC_zc_1/J4[B22]/MB_TP_26', identifier: PFC_ZC_1}
- {pin_num: '80', pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/FB_AD7, label: 'MB_J11[A8]/MB_U2B[7]/MB_TP14/MB_Ipfc1/J4[A8]/I_pfc1', identifier: I_PFC1}
- {pin_num: '81', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/FB_AD6/FTM2_FLT0, label: 'MB_J11[A9]/MB_U2A[1]/MB_TP5/MB_Ipfc2/J4[A9]/I_pfc2', identifier: I_PFC2}
- {pin_num: '82', pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/FB_AD5, label: 'MB_J11[B5]/MB_TP33/''MB_V_sense_DCB/2''/J4[B5]/''U_dcb/2''', identifier: U_DCB_HALF}
- {pin_num: '83', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FB_RW_b, label: 'MB_J11[B9]/MB_U12[2]/MB_TP38/MB_IPM_temp/J4[B9]/Temp_IPM', identifier: TEMP_IPM}
- {pin_num: '84', pin_signal: PTC12/FB_AD27/FTM3_FLT0, label: 'MB_J11[A26]/MB_U9[2]/MB_TP35/MB_FAULT_2/MB_Over-voltage_FAULT/J4[A26]/FAULT_2', identifier: FAULT_2}
- {pin_num: '85', pin_signal: PTC13/FB_AD26, label: 'MB_J11[B28]/MB_Q3[1]/MB_Relay/J4[B28]/Relay', identifier: RELAY}
- {pin_num: '86', pin_signal: PTC14/FB_AD25, label: NC}
- {pin_num: '87', pin_signal: PTC15/FB_AD24, label: NC}
- {pin_num: '90', pin_signal: PTC16/LPUART0_RX/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b, label: NC}
- {pin_num: '91', pin_signal: PTC17/LPUART0_TX/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b, label: NC}
- {pin_num: '92', pin_signal: PTC18/LPUART0_RTS_b/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b, label: NC}
- {pin_num: '97', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/EWM_IN/SPI1_PCS0, label: 'MB_J11[A18]/MB_U12[20]/MB_PWM_CT/J4[A18]/PWM4', identifier: PWM_CT}
- {pin_num: '98', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, label: 'MB_J11[A19]/MB_U12[14]/MB_PWM_CB/J4[A19]/PWM5', identifier: PWM_CB}
- {pin_num: '99', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'MB_J9[5]/MB_J11[B16]/MB_TP19/MB_ENC_Index/J4[B16]/TM2',
  identifier: ENC_INDEX}
- {pin_num: '100', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, label: NC}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitMC_PWMPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '71', peripheral: FTM0, signal: 'CH, 0', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/LPUART0_RTS_b, direction: OUTPUT}
  - {pin_num: '72', peripheral: FTM0, signal: 'CH, 1', pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/LPUART0_CTS_b, direction: OUTPUT}
  - {pin_num: '76', peripheral: FTM0, signal: 'CH, 3', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT/LPUART0_TX, direction: OUTPUT}
  - {pin_num: '77', peripheral: FTM0, signal: 'CH, 2', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/FB_AD10/CMP0_OUT/FTM0_CH2, direction: OUTPUT}
  - {pin_num: '97', peripheral: FTM0, signal: 'CH, 4', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/EWM_IN/SPI1_PCS0, direction: OUTPUT}
  - {pin_num: '98', peripheral: FTM0, signal: 'CH, 5', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, direction: OUTPUT}
  - {pin_num: '51', peripheral: FTM0, signal: 'FLT, 0', pin_signal: XTAL0/PTA19/FTM0_FLT0/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitMC_PWMPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitMC_PWMPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* PORTA19 (pin 51) is configured as FTM0_FLT0 */
    PORT_SetPinMux(MB_FAULT_1_PORT, MB_FAULT_1_PIN, kPORT_MuxAlt2);

    /* PORTC1 (pin 71) is configured as FTM0_CH0 */
    PORT_SetPinMux(MB_PWM_AT_PORT, MB_PWM_AT_PIN, kPORT_MuxAlt4);

    /* PORTC2 (pin 72) is configured as FTM0_CH1 */
    PORT_SetPinMux(MB_PWM_AB_PORT, MB_PWM_AB_PIN, kPORT_MuxAlt4);

    /* PORTC4 (pin 76) is configured as FTM0_CH3 */
    PORT_SetPinMux(MB_PWM_BB_PORT, MB_PWM_BB_PIN, kPORT_MuxAlt4);

    /* PORTC5 (pin 77) is configured as FTM0_CH2 */
    PORT_SetPinMux(MB_PWM_BT_PORT, MB_PWM_BT_PIN, kPORT_MuxAlt7);

    /* PORTD4 (pin 97) is configured as FTM0_CH4 */
    PORT_SetPinMux(MB_PWM_CT_PORT, MB_PWM_CT_PIN, kPORT_MuxAlt4);

    /* PORTD5 (pin 98) is configured as FTM0_CH5 */
    PORT_SetPinMux(MB_PWM_CB_PORT, MB_PWM_CB_PIN, kPORT_MuxAlt4);

    SIM->SOPT4 = ((SIM->SOPT4 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT4_FTM0FLT0_MASK)))

                  /* FTM0 Fault 0 Select: FTM0_FLT0 pin. */
                  | SIM_SOPT4_FTM0FLT0(SOPT4_FTM0FLT0_FTM));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitPFCPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '78', peripheral: CMP0, signal: 'IN, 0', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/FB_AD9/I2C0_SCL}
  - {pin_num: '79', peripheral: CMP0, signal: 'IN, 1', pin_signal: CMP0_IN1/PTC7/SPI0_SIN/FB_AD8/I2C0_SDA}
  - {pin_num: '85', peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/FB_AD26, direction: OUTPUT}
  - {pin_num: '6', peripheral: FTM3, signal: 'CH, 0', pin_signal: PTE5/SPI1_PCS2/LPUART0_RX/FTM3_CH0, direction: OUTPUT}
  - {pin_num: '7', peripheral: FTM3, signal: 'CH, 1', pin_signal: PTE6/SPI1_PCS3/LPUART0_CTS_b/FTM3_CH1, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitPFCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitPFCPins(void)
{
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t RELAY_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC13 (pin 85)  */
    GPIO_PinInit(MB_RELAY_GPIO, MB_RELAY_PIN, &RELAY_config);

    /* PORTC13 (pin 85) is configured as PTC13 */
    PORT_SetPinMux(MB_RELAY_PORT, MB_RELAY_PIN, kPORT_MuxAsGpio);

    /* PORTC6 (pin 78) is configured as CMP0_IN0 */
    PORT_SetPinMux(MB_PFC_ZC_2_PORT, MB_PFC_ZC_2_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC7 (pin 79) is configured as CMP0_IN1 */
    PORT_SetPinMux(MB_PFC_ZC_1_PORT, MB_PFC_ZC_1_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTE5 (pin 6) is configured as FTM3_CH0 */
    PORT_SetPinMux(MB_PWM_PFC2_PORT, MB_PWM_PFC2_PIN, kPORT_MuxAlt6);

    /* PORTE6 (pin 7) is configured as FTM3_CH1 */
    PORT_SetPinMux(MB_PWM_PFC1_PORT, MB_PWM_PFC1_PIN, kPORT_MuxAlt6);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitANA_SENSPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '26', peripheral: ADC1, signal: 'SE, 18', pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18}
  - {pin_num: '55', peripheral: ADC0, signal: 'SE, 12', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/FTM0_FLT3}
  - {pin_num: '82', peripheral: ADC1, signal: 'SE, 6b', pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/FB_AD5}
  - {pin_num: '83', peripheral: ADC1, signal: 'SE, 7b', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FB_RW_b}
  - {pin_num: '53', peripheral: ADC0, signal: 'SE, 8', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX}
  - {pin_num: '54', peripheral: ADC0, signal: 'SE, 9', pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX}
  - {pin_num: '20', peripheral: ADC1, signal: 'SE, 0', pin_signal: ADC1_DP0/ADC0_DP3}
  - {pin_num: '18', peripheral: ADC1, signal: 'SE, 3', pin_signal: ADC0_DP0/ADC1_DP3}
  - {pin_num: '27', peripheral: ADC0, signal: 'SE, 23', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23}
  - {pin_num: '28', peripheral: ADC1, signal: 'SE, 23', pin_signal: DAC1_OUT/CMP0_IN4/ADC1_SE23}
  - {pin_num: '80', peripheral: ADC1, signal: 'SE, 4b', pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/FB_AD7}
  - {pin_num: '81', peripheral: ADC1, signal: 'SE, 5b', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/FB_AD6/FTM2_FLT0}
  - {pin_num: '73', peripheral: CMP1, signal: 'IN, 1', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/LPUART0_RX}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitANA_SENSPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitANA_SENSPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* PORTB0 (pin 53) is configured as ADC0_SE8 */
    PORT_SetPinMux(MB_I_PH_A_PORT, MB_I_PH_A_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTB1 (pin 54) is configured as ADC0_SE9 */
    PORT_SetPinMux(MB_I_PH_C_PORT, MB_I_PH_C_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTB2 (pin 55) is configured as ADC0_SE12 */
    PORT_SetPinMux(MB_U_DCB_PORT, MB_U_DCB_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC10 (pin 82) is configured as ADC1_SE6b */
    PORT_SetPinMux(MB_U_DCB_HALF_PORT, MB_U_DCB_HALF_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC11 (pin 83) is configured as ADC1_SE7b */
    PORT_SetPinMux(MB_TEMP_IPM_PORT, MB_TEMP_IPM_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC3 (pin 73) is configured as CMP1_IN1 */
    PORT_SetPinMux(MB_TACHO_PORT, MB_TACHO_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC8 (pin 80) is configured as ADC1_SE4b */
    PORT_SetPinMux(MB_I_PFC1_PORT, MB_I_PFC1_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC9 (pin 81) is configured as ADC1_SE5b */
    PORT_SetPinMux(MB_I_PFC2_PORT, MB_I_PFC2_PIN, kPORT_PinDisabledOrAnalog);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitBEMFPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '19', peripheral: ADC0, signal: 'SE, 19', pin_signal: ADC0_DM0/ADC1_DM3}
  - {pin_num: '21', peripheral: ADC1, signal: 'SE, 19', pin_signal: ADC1_DM0/ADC0_DM3}
  - {pin_num: '17', peripheral: ADC1, signal: 'SE, 20', pin_signal: ADC1_DM1/ADC0_DM2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitBEMFPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitBEMFPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitENCPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '42', peripheral: FTM1, signal: 'QD_PH, A', pin_signal: PTA12/FTM1_CH0/FTM1_QD_PHA}
  - {pin_num: '43', peripheral: FTM1, signal: 'QD_PH, B', pin_signal: PTA13/LLWU_P4/FTM1_CH1/FTM1_QD_PHB}
  - {pin_num: '99', peripheral: GPIOD, signal: 'GPIO, 6', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitENCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitENCPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t ENC_INDEX_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD6 (pin 99)  */
    GPIO_PinInit(MB_ENC_INDEX_GPIO, MB_ENC_INDEX_PIN, &ENC_INDEX_config);

    /* PORTA12 (pin 42) is configured as FTM1_QD_PHA */
    PORT_SetPinMux(MB_ENC_PHASE_A_PORT, MB_ENC_PHASE_A_PIN, kPORT_MuxAlt7);

    /* PORTA13 (pin 43) is configured as FTM1_QD_PHB */
    PORT_SetPinMux(MB_ENC_PHASE_B_PORT, MB_ENC_PHASE_B_PIN, kPORT_MuxAlt7);

    /* PORTD6 (pin 99) is configured as PTD6 */
    PORT_SetPinMux(MB_ENC_INDEX_PORT, MB_ENC_INDEX_PIN, kPORT_MuxAsGpio);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitBRAKEPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '70', peripheral: GPIOC, signal: 'GPIO, 0', pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/FB_AD14/FTM0_FLT1/SPI0_PCS0, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitBRAKEPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitBRAKEPins(void)
{
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t MCU_BRAKE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC0 (pin 70)  */
    GPIO_PinInit(MB_MCU_BRAKE_GPIO, MB_MCU_BRAKE_PIN, &MCU_BRAKE_config);

    /* PORTC0 (pin 70) is configured as PTC0 */
    PORT_SetPinMux(MB_MCU_BRAKE_PORT, MB_MCU_BRAKE_PIN, kPORT_MuxAsGpio);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitUSB_UARTPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '10', peripheral: UART2, signal: TX, pin_signal: ADC0_SE4a/PTE16/SPI0_PCS0/UART2_TX/FTM_CLKIN0/FTM0_FLT3, direction: OUTPUT}
  - {pin_num: '11', peripheral: UART2, signal: RX, pin_signal: ADC0_SE5a/PTE17/SPI0_SCK/UART2_RX/FTM_CLKIN1/LPTMR0_ALT3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitUSB_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitUSB_UARTPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTE16 (pin 10) is configured as UART2_TX */
    PORT_SetPinMux(MB_TXD_PORT, MB_TXD_PIN, kPORT_MuxAlt3);

    /* PORTE17 (pin 11) is configured as UART2_RX */
    PORT_SetPinMux(MB_RXD_PORT, MB_RXD_PIN, kPORT_MuxAlt3);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitEXT_UARTPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN}
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitEXT_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitEXT_UARTPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(MB_TXD_1_PORT, MB_TXD_1_PIN, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(MB_RXD_1_PORT, MB_RXD_1_PIN, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
MB_InitMISCPins:
- options: {prefix: MB_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '84', peripheral: GPIOC, signal: 'GPIO, 12', pin_signal: PTC12/FB_AD27/FTM3_FLT0, direction: INPUT}
  - {peripheral: ADC0, signal: 'TRG, A', pin_signal: PDB0_CH0_TriggerA}
  - {peripheral: ADC0, signal: 'TRG, B', pin_signal: PDB0_CH0_TriggerB}
  - {peripheral: ADC1, signal: 'TRG, A', pin_signal: PDB0_CH1_TriggerA}
  - {peripheral: ADC1, signal: 'TRG, B', pin_signal: PDB0_CH1_TriggerB}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : MB_InitMISCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void MB_InitMISCPins(void)
{
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t FAULT_2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC12 (pin 84)  */
    GPIO_PinInit(MB_FAULT_2_GPIO, MB_FAULT_2_PIN, &FAULT_2_config);

    /* PORTC12 (pin 84) is configured as PTC12 */
    PORT_SetPinMux(MB_FAULT_2_PORT, MB_FAULT_2_PIN, kPORT_MuxAsGpio);

    SIM->SOPT7 = ((SIM->SOPT7 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC1ALTTRGEN_MASK)))

                  /* ADC0 alternate trigger enable: PDB trigger selected for ADC0. */
                  | SIM_SOPT7_ADC0ALTTRGEN(SOPT7_ADC0ALTTRGEN_PDB)

                  /* ADC1 alternate trigger enable: PDB trigger selected for ADC1. */
                  | SIM_SOPT7_ADC1ALTTRGEN(SOPT7_ADC1ALTTRGEN_PDB));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '36', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO/EZP_DO, pull_select: down,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA2 (pin 36) is configured as TRACE_SWO */
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);

    PORTA->PCR[2] = ((PORTA->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                      * corresponding PE field is set. */
                     | PORT_PCR_PS(kPORT_PullDown)

                     /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                     | PORT_PCR_PE(kPORT_PullDisable));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN}
  - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* PORTB16 (pin 62) is configured as UART0_RX */
    PORT_SetPinMux(BOARD_UART_TX_TGTMCU_PORT, BOARD_UART_TX_TGTMCU_PIN, kPORT_MuxAlt3);

    /* PORTB17 (pin 63) is configured as UART0_TX */
    PORT_SetPinMux(BOARD_UART_RX_TGTMCU_PORT, BOARD_UART_RX_TGTMCU_PIN, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDSPins:
- options: {callFromInitBoot: 'false', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '65', peripheral: GPIOB, signal: 'GPIO, 19', pin_signal: PTB19/FTM2_CH1/FB_OE_b/FTM2_QD_PHB, direction: OUTPUT}
  - {pin_num: '39', peripheral: GPIOA, signal: 'GPIO, 5', pin_signal: PTA5/FTM0_CH2/JTAG_TRST_b, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDSPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDSPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA5 (pin 39)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB19 (pin 65)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    /* PORTA5 (pin 39) is configured as PTA5 */
    PORT_SetPinMux(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, kPORT_MuxAsGpio);

    /* PORTB19 (pin 65) is configured as PTB19 */
    PORT_SetPinMux(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, kPORT_MuxAsGpio);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
