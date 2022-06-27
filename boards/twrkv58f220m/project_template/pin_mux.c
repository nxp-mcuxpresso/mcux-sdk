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
processor: MKV58F1M0xxx24
package_id: MKV58F1M0VLQ24
mcu_data: ksdk2_0
processor_version: 0.0.16
board: TWR-KV58F220M
pin_labels:
- {pin_num: '1', pin_signal: HSADC0B_CH16/HSADC1A_CH0/PTE0/SPI1_PCS1/UART1_TX/XB_OUT10/XB_IN11/I2C1_SDA/TRACE_CLKOUT, label: 'J15[D30]/ADCB_CH6F/ADCC_CH0_RC'}
- {pin_num: '10', pin_signal: PTE7/UART3_RTS_b/FLEXPWM1_A1/FTM3_CH2, label: 'J31[30]/FLEXPWMB_A1'}
- {pin_num: '100', pin_signal: PTB21/SPI2_SCK/FLEXPWM0_X1/CMP1_OUT/FB_AD30, label: 'J15[B7]/J15[B74]/J31[21]/SPI2_SCK'}
- {pin_num: '101', pin_signal: PTB22/SPI2_SOUT/FLEXPWM0_X2/CMP2_OUT/FB_AD29, label: 'J15[B10]/J15[B75]/SPI2_SOUT/FB_AD29'}
- {pin_num: '102', pin_signal: PTB23/SPI2_SIN/SPI0_PCS5/FLEXPWM0_X3/CMP3_OUT/FB_AD28, label: 'J15[B11]/J15[B76]/SPI2_SIN/FB_AD28'}
- {pin_num: '103', pin_signal: HSADC0B_CH8/PTC0/SPI0_PCS4/PDB0_EXTRG/FTM0_FLT1/SPI0_PCS0/FB_AD14, label: 'J15[A66]/FB_AD14'}
- {pin_num: '104', pin_signal: HSADC0B_CH9/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FLEXPWM0_A3/XB_IN11/FB_AD13, label: 'J15[A67]/FB_AD13'}
- {pin_num: '105', pin_signal: HSADC1B_CH10/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FLEXPWM0_B3/XB_IN6/FB_AD12, label: 'J15[A68]/FB_AD12'}
- {pin_num: '106', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/FTM3_FLT0, label: 'J15[A64]/CLKOUT'}
- {pin_num: '107', pin_signal: VSS107, label: GND}
- {pin_num: '108', pin_signal: VDD108, label: VDD_MCU}
- {pin_num: '109', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/CMP1_OUT/FB_AD11, label: 'J15[A69]/FB_AD11'}
- {pin_num: '117', pin_signal: PTC12/CAN2_TX/FTM_CLKIN0/FLEXPWM1_A1/FTM3_FLT0/SPI2_PCS1/FB_AD27/UART4_RTS_b, label: 'J15[B8]/J15[B77]/SPI2_PCS1/FB_AD27'}
- {pin_num: '11', pin_signal: PTE8/UART5_TX/FLEXPWM1_B1/FTM3_CH3, label: 'J15[C37]/J31[32]/FLEXPWMB_B1'}
- {pin_num: '110', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/XB_IN2/CMP0_OUT/FTM0_CH2/FB_AD10, label: 'J15[A70]/FB_AD10'}
- {pin_num: '111', pin_signal: CMP2_IN4/CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/XB_IN3/UART0_RX/XB_OUT6/I2C0_SCL/FB_AD9, label: 'J15[A71]/FB_AD9'}
- {pin_num: '112', pin_signal: CMP3_IN4/CMP0_IN1/PTC7/SPI0_SIN/XB_IN4/UART0_TX/XB_OUT7/I2C0_SDA/FB_AD8, label: 'J15[A72]/FB_AD8'}
- {pin_num: '113', pin_signal: HSADC1B_CH11/CMP0_IN2/PTC8/FTM3_CH4/FLEXPWM1_A2/FB_AD7, label: 'J15[A73]/FB_AD7'}
- {pin_num: '114', pin_signal: HSADC1B_CH12/CMP0_IN3/PTC9/FTM3_CH5/FLEXPWM1_B2/FB_AD6, label: 'J15[A74]/FB_AD6'}
- {pin_num: '115', pin_signal: HSADC1B_CH13/PTC10/I2C1_SCL/FTM3_CH6/FLEXPWM1_A3/FB_AD5, label: 'J15[A75]/FB_AD5'}
- {pin_num: '116', pin_signal: HSADC1B_CH14/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FLEXPWM1_B3/FB_RW_b, label: 'J15[B72]'}
- {pin_num: '118', pin_signal: PTC13/CAN2_RX/FTM_CLKIN1/FLEXPWM1_B1/FB_AD26/UART4_CTS_b, label: 'J15[B78]/FB_AD26'}
- {pin_num: '119', pin_signal: PTC14/I2C1_SCL/I2C0_SCL/FLEXPWM1_A0/FB_AD25/UART4_RX, label: 'J15[B79]/FB_AD25'}
- {pin_num: '12', pin_signal: PTE9/LLWU_P17/UART5_RX/FLEXPWM1_A2/FTM3_CH4, label: 'J15[D40]/J31[34]/FLEXPWMB_A2'}
- {pin_num: '120', pin_signal: PTC15/I2C1_SDA/I2C0_SDA/FLEXPWM1_B0/FB_AD24/UART4_TX, label: 'J15[B80]/FB_AD24'}
- {pin_num: '121', pin_signal: VSS121, label: GND}
- {pin_num: '122', pin_signal: VDD122, label: VDD_MCU}
- {pin_num: '123', pin_signal: PTC16/CAN1_RX/UART3_RX/ENET0_1588_TMR0/FLEXPWM1_A2/FB_CS5_b/FB_TSIZ1/FB_BE23_16_b, label: 'J15[B41]/CAN1_RX'}
- {pin_num: '124', pin_signal: PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FLEXPWM1_B2/FB_CS4_b/FB_TSIZ0/FB_BE31_24_b, label: 'J15[B42]/CAN1_TX'}
- {pin_num: '125', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FLEXPWM1_A3/FB_TBST_b/FB_CS2_b/FB_BE15_8_b, label: 'J15[D52]/U1[11]/INT1', identifier: ACCEL_INT1}
- {pin_num: '126', pin_signal: PTC19/UART3_CTS_b/ENET0_1588_TMR3/FLEXPWM1_B3/FB_CS3_b/FB_BE7_0_b/FB_TA_b, label: 'U1[9]/INT2', identifier: ACCEL_INT2}
- {pin_num: '127', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FTM0_CH0/FLEXPWM0_A0/FB_ALE/FB_CS1_b/FB_TS_b/FLEXPWM1_A0, label: 'J15[B63]/FB_ALE'}
- {pin_num: '128', pin_signal: HSADC1A_CH11/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FTM0_CH1/FLEXPWM0_B0/FB_CS0_b/FLEXPWM1_B0, label: 'J15[B64]/FB_CS0'}
- {pin_num: '129', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FTM0_CH2/FLEXPWM0_A1/I2C0_SCL/FB_AD4/FLEXPWM1_A1, label: 'J15[A76]/FB_AD4'}
- {pin_num: '13', pin_signal: PTE10/LLWU_P18/UART5_CTS_b/FLEXPWM1_B2/FTM3_CH5, label: 'J15[D39]/J31[36]/FLEXPWMB_B2'}
- {pin_num: '130', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FTM0_CH3/FLEXPWM0_B1/I2C0_SDA/FB_AD3/FLEXPWM1_B1, label: 'J15[A77]/FB_AD3'}
- {pin_num: '131', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FLEXPWM0_A2/EWM_IN/SPI1_PCS0/FB_AD2, label: 'J15[A78]/FB_AD2'}
- {pin_num: '132', pin_signal: HSADC1A_CH8/PTD5/SPI0_PCS2/UART0_CTS_b/UART0_COL_b/FTM0_CH5/FLEXPWM0_B2/EWM_OUT_b/SPI1_SCK/FB_AD1, label: 'J15[A79]/FB_AD1'}
- {pin_num: '133', pin_signal: HSADC1A_CH9/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FTM1_CH0/FTM0_FLT0/SPI1_SOUT/FB_AD0, label: 'J15[A80]/FB_AD0'}
- {pin_num: '134', pin_signal: VSS134, label: GND}
- {pin_num: '135', pin_signal: VDD135, label: VDD_MCU}
- {pin_num: '136', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM1_CH1/FTM0_FLT1/SPI1_SIN, label: 'J15[D60]/J31[14]'}
- {pin_num: '137', pin_signal: PTD8/LLWU_P24/I2C1_SCL/UART5_RX/FLEXPWM0_A3/FB_A16, label: 'J15[A7]/U1[4]/I2C1_SCL', identifier: I2C_SCL}
- {pin_num: '138', pin_signal: PTD9/I2C1_SDA/UART5_TX/FLEXPWM0_B3/FB_A17, label: 'J15[A8]/U1[6]/I2C1_SDA', identifier: I2C_SDA}
- {pin_num: '139', pin_signal: PTD10/UART5_RTS_b/FLEXPWM0_A2/FB_A18, label: 'J15[B40]/FLEXPWMA_A2'}
- {pin_num: '14', pin_signal: HSADC1A_CH6/ADC0_SE3/ADC0_DP3/PTE11/UART5_RTS_b/FLEXPWM1_A3/FTM3_CH6, label: 'J30[1]/LED_J_PTE11', identifier: LED_RED}
- {pin_num: '140', pin_signal: PTD11/LLWU_P25/SPI2_PCS0/UART5_CTS_b/FLEXPWM0_B2/FB_A19, label: 'J15[B39]/FLEXPWMA_B2'}
- {pin_num: '141', pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/XB_IN5/XB_OUT5/FLEXPWM0_A1/FB_A20, label: 'J15[A38]/FLEXPWMA_A1'}
- {pin_num: '142', pin_signal: PTD13/SPI2_SOUT/XB_IN7/XB_OUT7/FLEXPWM0_B1/FB_A21, label: 'J15[A37]/FLEXPWMA_B1'}
- {pin_num: '143', pin_signal: PTD14/SPI2_SIN/XB_IN11/XB_OUT11/FLEXPWM0_A0/FB_A22, label: 'J15[A40]/FLEXPWMA_A0'}
- {pin_num: '144', pin_signal: PTD15/SPI2_PCS1/FLEXPWM0_B0/FB_A23, label: 'J15[A39]/FLEXPWMA_B0'}
- {pin_num: '15', pin_signal: HSADC1B_CH6/ADC0_SE11/ADC0_DM3/PTE12/FLEXPWM1_B3/FTM3_CH7, label: 'J30[3]/LED_J_PTE12', identifier: LED_GREEN}
- {pin_num: '16', pin_signal: VDD16, label: VDD_MCU}
- {pin_num: '17', pin_signal: VSS17, label: GND}
- {pin_num: '18', pin_signal: HSADC0A_CH0/ADC0_SE1/ADC0_DP1/PTE16/SPI0_PCS0/UART2_TX/FTM_CLKIN0/FTM0_FLT3, label: 'J15[B46]/SPI0_PCS0'}
- {pin_num: '19', pin_signal: HSADC0A_CH1/ADC0_SE9/ADC0_DM1/PTE17/LLWU_P19/SPI0_SCK/UART2_RX/FTM_CLKIN1/LPTMR0_ALT3, label: 'J15[B48]/SPI0_SCK'}
- {pin_num: '2', pin_signal: HSADC0B_CH17/HSADC1A_CH1/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/XB_OUT11/XB_IN7/I2C1_SCL/TRACE_D3, label: 'J15[C28]/ADCB_CH7F/ADCC_CH1_RC'}
- {pin_num: '20', pin_signal: HSADC0B_CH0/ADC0_SE5a/PTE18/LLWU_P20/SPI0_SOUT/UART2_CTS_b/I2C0_SDA, label: 'J15[B45]/SPI0_SOUT'}
- {pin_num: '21', pin_signal: HSADC0B_CH1/ADC0_SE6a/PTE19/SPI0_SIN/UART2_RTS_b/I2C0_SCL/CMP3_OUT, label: 'J15[B44]/SPI0_SIN'}
- {pin_num: '22', pin_signal: VSS22, label: GND}
- {pin_num: '23', pin_signal: HSADC0A_CH6/ADC0_SE7a, label: 'J15[B30]/ADCA_CH6A/ADC0_SE7A_RC'}
- {pin_num: '24', pin_signal: HSADC0A_CH7/ADC0_SE4b, label: 'J15[B28]/ADCA_CH7A/ADC0_SE4B_RC'}
- {pin_num: '25', pin_signal: HSADC0A_CH8/ADC0_SE5b/PTE20/FTM1_CH0/UART0_TX/FTM1_QD_PHA, label: 'J31[13]/FTM1_QD_PHA'}
- {pin_num: '26', pin_signal: HSADC0A_CH9/HSADC1A_CH7/PTE21/XB_IN9/FTM1_CH1/UART0_RX/FTM1_QD_PHB, label: 'J15[B33]/J15[C33]/J3[1]/J31[15]/FTM1_QD_PHB'}
- {pin_num: '3', pin_signal: HSADC0B_CH10/HSADC1B_CH0/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/TRACE_D2, label: 'J15[C29]/ADCB_CH6C/ADCD_CH0_RC'}
- {pin_num: '30', pin_signal: HSADC0A_CH11/HSADC1B_CH3, label: 'J15[C27]/ADCA_CH7C/ADCD_CH3_RC'}
- {pin_num: '31', pin_signal: VDDA, label: VDD_MCU}
- {pin_num: '32', pin_signal: VREFH, label: VDD_MCU, identifier: VREFH}
- {pin_num: '33', pin_signal: VREFL, label: GND, identifier: VREFL}
- {pin_num: '34', pin_signal: VSSA, label: GND}
- {pin_num: '37', pin_signal: HSADC0A_CH4/CMP1_IN5/CMP0_IN5/PTE29/FTM0_CH2/FTM_CLKIN0, label: 'J30[5]/LED_J_PTE29', identifier: LED_BLUE}
- {pin_num: '38', pin_signal: DAC0_OUT/CMP1_IN3/HSADC0A_CH5/PTE30/FTM0_CH3/FTM_CLKIN1, label: 'J30[7]/LED_J_PTE30', identifier: LED_ORANGE}
- {pin_num: '39', pin_signal: HSADC0A_CH12/CMP0_IN4/CMP2_IN3, label: 'J4[1]/POT_5K', identifier: ADC_POT}
- {pin_num: '4', pin_signal: HSADC0B_CH11/HSADC1B_CH1/PTE3/SPI1_SIN/UART1_RTS_b/TRACE_D1, label: 'J15[C30]/ADCB_CH7C/ADCD_CH1_RC'}
- {pin_num: '40', pin_signal: PTE13, label: 'J15[D50]/J31[26]'}
- {pin_num: '41', pin_signal: PTE22/FTM2_CH0/XB_IN2/FTM2_QD_PHA, label: 'J15[C34]/J31[17]/FTM2_QD_PHA'}
- {pin_num: '42', pin_signal: PTE23/FTM2_CH1/XB_IN3/FTM2_QD_PHB, label: 'J15[A33]/J31[19]/FTM2_QD_PHB'}
- {pin_num: '43', pin_signal: VDD43, label: VDD_MCU}
- {pin_num: '44', pin_signal: VSS44, label: GND}
- {pin_num: '45', pin_signal: HSADC0B_CH4/HSADC1B_CH4/PTE24/CAN1_TX/FTM0_CH0/XB_IN2/I2C0_SCL/EWM_OUT_b/XB_OUT4/UART4_TX, label: 'J15[A33]/J15[B62]/XBAR_IN2/FTM2_QD_PHB'}
- {pin_num: '46', pin_signal: HSADC0B_CH5/HSADC1B_CH5/PTE25/LLWU_P21/CAN1_RX/FTM0_CH1/XB_IN3/I2C0_SDA/EWM_IN/XB_OUT5/UART4_RX, label: 'J15[D61]/J31[33]/XBAR0_IN3'}
- {pin_num: '47', pin_signal: PTE26/ENET_1588_CLKIN/FTM0_CH4/UART4_CTS_b, label: 'J15[B47]/SPI0_PCS1', identifier: ENET_1588_CLKIN}
- {pin_num: '48', pin_signal: PTE27/CAN2_TX/UART4_RTS_b, label: 'J15[B55]'}
- {pin_num: '49', pin_signal: PTE28/CAN2_RX, label: 'J15[B52]'}
- {pin_num: '5', pin_signal: VDD5, label: VDD_MCU}
- {pin_num: '50', pin_signal: PTA0/UART0_CTS_b/UART0_COL_b/FTM0_CH5/XB_IN4/EWM_IN/JTAG_TCLK/SWD_CLK, label: 'J13[4]/J31[29]/JTAG_TCLK'}
- {pin_num: '51', pin_signal: PTA1/UART0_RX/FTM0_CH6/CMP0_OUT/FTM2_QD_PHA/FTM1_CH1/JTAG_TDI, label: 'J13[8]/J31[25]/JTAG_TDI'}
- {pin_num: '52', pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO, label: 'J13[6]/J31[27]/JTAG_TDO'}
- {pin_num: '53', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/XB_IN9/EWM_OUT_b/FLEXPWM0_A0/JTAG_TMS/SWD_DIO, label: 'J13[2]/J31[31]/JTAG_TMS'}
- {pin_num: '54', pin_signal: PTA4/LLWU_P3/FTM0_CH1/XB_IN10/FTM0_FLT3/FLEXPWM0_B0/NMI_b, label: SW2, identifier: SW2}
- {pin_num: '55', pin_signal: PTA5/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/JTAG_TRST_b, label: 'J15[B13]/MII0_RXER'}
- {pin_num: '56', pin_signal: VDD56, label: VDD_MCU}
- {pin_num: '57', pin_signal: VSS57, label: GND}
- {pin_num: '58', pin_signal: PTA6/FTM0_CH3/CLKOUT/TRACE_CLKOUT, label: 'J15[B25]/J13[12]/TRACE_CLKOUT'}
- {pin_num: '59', pin_signal: HSADC1B_CH8/PTA7/FTM0_CH4/RMII0_MDIO/MII0_MDIO/TRACE_D3, label: 'J15[A14]/J13[20]/MII0_MDIO/TRACE_D3'}
- {pin_num: '6', pin_signal: VSS6, label: GND}
- {pin_num: '60', pin_signal: HSADC1B_CH9/PTA8/FTM1_CH0/RMII0_MDC/MII0_MDC/TRACE_D2, label: 'J15[A13]/J13[18]/MII0_MDC/TRACE_D2'}
- {pin_num: '61', pin_signal: PTA9/FTM1_CH1/MII0_RXD3/TRACE_D1, label: 'J15[A17]/J13[16]/MII0_RXD3/TRACE_D1'}
- {pin_num: '62', pin_signal: PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TRACE_D0, label: 'J15[A18]/J13[14]/MII0_RXD2/TRACE_D0'}
- {pin_num: '63', pin_signal: PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/FTM2_QD_PHB/I2C0_SDA, label: 'J15[A15]/MII0_RXCLK'}
- {pin_num: '64', pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/FTM1_QD_PHA/I2C0_SCL, label: 'J15[A19]/MII0_RXD1'}
- {pin_num: '65', pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/FTM1_QD_PHB/I2C1_SDA, label: 'J15[A20]/MII0_RXD0'}
- {pin_num: '66', pin_signal: CMP3_IN0/PTA14/SPI0_PCS0/UART0_TX/CAN2_TX/RMII0_CRS_DV/MII0_RXDV/I2C1_SCL, label: 'J15[A16]/MII0_RXDV'}
- {pin_num: '67', pin_signal: CMP3_IN1/PTA15/SPI0_SCK/UART0_RX/CAN2_RX/RMII0_TXEN/MII0_TXEN, label: 'J15[B15]/MII0_TXEN'}
- {pin_num: '68', pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0, label: 'J15[B20]/MII0_TXD0'}
- {pin_num: '69', pin_signal: HSADC0A_CH15/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1, label: 'J15[B19]/MII0_TXD1'}
- {pin_num: '7', pin_signal: HSADC1A_CH4/ADC0_SE2/ADC0_DP2/PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/TRACE_D0, label: SW3, identifier: SW3}
- {pin_num: '70', pin_signal: VDD70, label: VDD_MCU}
- {pin_num: '71', pin_signal: VSS71, label: GND}
- {pin_num: '72', pin_signal: EXTAL0/PTA18/XB_IN7/FTM0_FLT2/FTM_CLKIN0/XB_OUT8/FTM3_CH2, label: 'Y1[3]/50MHz_OSC', identifier: XTAL0}
- {pin_num: '74', pin_signal: RESET_b, label: 'J15[A62]/J15[A63]/J13[10]/J31[4]/RESET'}
- {pin_num: '75', pin_signal: PTA24/XB_IN4/MII0_TXD2/FB_A29, label: 'J15[B18]/MII0_TXD2'}
- {pin_num: '76', pin_signal: PTA25/XB_IN5/MII0_TXCLK/FB_A28, label: 'J15[B14]/MII0_TXCLK'}
- {pin_num: '77', pin_signal: PTA26/MII0_TXD3/FB_A27, label: 'J15[B17]/MII0_TXD3'}
- {pin_num: '78', pin_signal: PTA27/MII0_CRS/FB_A26, label: 'J15[A12]/MII0_CRS'}
- {pin_num: '8', pin_signal: HSADC1A_CH5/ADC0_SE10/ADC0_DM2/PTE5/SPI1_PCS2/UART3_RX/FLEXPWM1_A0/FTM3_CH0, label: 'J15[C40]/J31[9]/FLEXPWMB_A0'}
- {pin_num: '80', pin_signal: PTA29/MII0_COL/FB_A24, label: 'J15[B12]/MII0_COL'}
- {pin_num: '81', pin_signal: HSADC0B_CH2/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX/RMII0_MDIO/MII0_MDIO, label: 'J15[A43]/J31[7]/UART0_RX', identifier: DEBUG_UART_RX}
- {pin_num: '82', pin_signal: HSADC0B_CH3/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX/RMII0_MDC/MII0_MDC, label: 'J15[A44]/J31[5]/UART0_TX', identifier: DEBUG_UART_TX}
- {pin_num: '83', pin_signal: HSADC0A_CH14/CMP2_IN2/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT1/ENET0_1588_TMR0/FTM0_FLT3, label: 'J14[7]/ENET0_1588_TMR0'}
- {pin_num: '84', pin_signal: HSADC0B_CH15/CMP3_IN5/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/FTM0_FLT0, label: 'J14[5]/ENET0_1588_TMR1'}
- {pin_num: '85', pin_signal: ADC0_SE6b/PTB4/FLEXPWM1_X0/ENET0_1588_TMR2/FTM1_FLT0, label: 'J15[A63]/J14[3]/SW5/ENET0_1588_TMR2', identifier: SW5}
- {pin_num: '86', pin_signal: ADC0_SE7b/PTB5/FLEXPWM1_X1/ENET0_1588_TMR3/FTM2_FLT0, label: 'J15[D34]/J14[1]/SW4/ENET0_1588_TMR3', identifier: SW4}
- {pin_num: '87', pin_signal: HSADC1A_CH12/PTB6/CAN2_TX/FLEXPWM1_X2/FB_AD23, label: 'J15[B21]'}
- {pin_num: '88', pin_signal: HSADC1A_CH13/PTB7/CAN2_RX/FLEXPWM1_X3/FB_AD22, label: 'J15[B22]'}
- {pin_num: '89', pin_signal: PTB8/UART3_RTS_b/FB_AD21, label: 'J15[B61]'}
- {pin_num: '9', pin_signal: HSADC1B_CH7/ADC0_SE4a/PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/FLEXPWM1_B0/FTM3_CH1, label: 'J15[C39]/J31[11]/FLEXPWMB_B0'}
- {pin_num: '90', pin_signal: PTB9/SPI1_PCS1/UART3_CTS_b/ENET0_1588_TMR2/FB_AD20, label: 'J15[D51]/J31[28]/'}
- {pin_num: '91', pin_signal: HSADC0B_CH6/PTB10/SPI1_PCS0/UART3_RX/ENET0_1588_TMR3/FTM0_FLT1/FB_AD19, label: 'J15[B70]/FB_AD19'}
- {pin_num: '92', pin_signal: HSADC0B_CH7/PTB11/SPI1_SCK/UART3_TX/FTM0_FLT2/FB_AD18, label: 'J15[B69]/FB_AD18'}
- {pin_num: '93', pin_signal: VSS93, label: GND}
- {pin_num: '94', pin_signal: VDD94, label: VDD_MCU}
- {pin_num: '95', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN2/CAN0_TX/EWM_IN/XB_IN5/FB_AD17, label: 'J15[B68]/FB_AD17'}
- {pin_num: '96', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/CAN0_RX/EWM_OUT_b/FB_AD16, label: 'J15[B67]/FB_AD16'}
- {pin_num: '97', pin_signal: PTB18/CAN0_TX/FTM2_CH0/FTM3_CH2/FLEXPWM1_A1/FTM2_QD_PHA/FB_AD15, label: 'J15[B66]/FB_AD15'}
- {pin_num: '98', pin_signal: PTB19/CAN0_RX/FTM2_CH1/FTM3_CH3/FLEXPWM1_B1/FTM2_QD_PHB/FB_OE_b, label: 'J15[B71]/FB_OE'}
- {pin_num: '99', pin_signal: PTB20/SPI2_PCS0/FLEXPWM0_X0/CMP0_OUT/FB_AD31, label: 'J15[B9]/J15[B73]/J31[23]/SPI2_PCS0/FB_AD31'}
- {pin_num: '27', pin_signal: HSADC0A_CH2/HSADC1A_CH2, label: 'J15[A30]/ADCA_CH2/ADCC_CH2_RC'}
- {pin_num: '35', pin_signal: ADC0_SE0/ADC0_DP0/CMP2_IN5, label: NC}
- {pin_num: '36', pin_signal: ADC0_SE8/ADC0_DM0/CMP1_IN2, label: NC}
- {pin_num: '28', pin_signal: HSADC0A_CH3/HSADC1A_CH3, label: 'J15[A29]/ADCA_CH3/ADCC_CH3_RC'}
- {pin_num: '29', pin_signal: HSADC0A_CH10/HSADC1B_CH2, label: 'J15[A28]/ADCA_CH6C/ADCD_CH2_RC'}
- {pin_num: '79', pin_signal: PTA28/MII0_TXER/FB_A25, label: NC}
- {pin_num: '73', pin_signal: XTAL0/PTA19/XB_IN8/FTM1_FLT0/FTM_CLKIN1/XB_OUT9/LPTMR0_ALT1, label: NC}
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
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '52', peripheral: JTAG, signal: TRACE_SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/CMP1_OUT/FTM2_QD_PHB/FTM1_CH0/JTAG_TDO/TRACE_SWO, pull_select: down, pull_enable: disable}
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

    /* PORTA2 (pin 52) is configured as TRACE_SWO */
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
BOARD_InitBUTTONsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '54', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/XB_IN10/FTM0_FLT3/FLEXPWM0_B0/NMI_b, direction: INPUT, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable, passive_filter: disable}
  - {pin_num: '7', peripheral: GPIOE, signal: 'GPIO, 4', pin_signal: HSADC1A_CH4/ADC0_SE2/ADC0_DP2/PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/TRACE_D0, direction: INPUT, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '86', peripheral: GPIOB, signal: 'GPIO, 5', pin_signal: ADC0_SE7b/PTB5/FLEXPWM1_X1/ENET0_1588_TMR3/FTM2_FLT0, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: '85', peripheral: GPIOB, signal: 'GPIO, 4', pin_signal: ADC0_SE6b/PTB4/FLEXPWM1_X0/ENET0_1588_TMR2/FTM1_FLT0, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBUTTONsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA4 (pin 54)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW5_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB4 (pin 85)  */
    GPIO_PinInit(BOARD_SW5_GPIO, BOARD_SW5_PIN, &SW5_config);

    gpio_pin_config_t SW4_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB5 (pin 86)  */
    GPIO_PinInit(BOARD_SW4_GPIO, BOARD_SW4_PIN, &SW4_config);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE4 (pin 7)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    const port_pin_config_t SW2 = {/* Internal pull-up/down resistor is disabled */
                                   kPORT_PullDisable,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTA4 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTA4 (pin 54) is configured as PTA4 */
    PORT_SetPinConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2);

    const port_pin_config_t SW5 = {/* Internal pull-up/down resistor is disabled */
                                   kPORT_PullDisable,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTB4 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTB4 (pin 85) is configured as PTB4 */
    PORT_SetPinConfig(BOARD_SW5_PORT, BOARD_SW5_PIN, &SW5);

    const port_pin_config_t SW4 = {/* Internal pull-up/down resistor is disabled */
                                   kPORT_PullDisable,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTB5 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTB5 (pin 86) is configured as PTB5 */
    PORT_SetPinConfig(BOARD_SW4_PORT, BOARD_SW4_PIN, &SW4);

    const port_pin_config_t SW3 = {/* Internal pull-up/down resistor is disabled */
                                   kPORT_PullDisable,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTE4 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTE4 (pin 7) is configured as PTE4 */
    PORT_SetPinConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '14', peripheral: GPIOE, signal: 'GPIO, 11', pin_signal: HSADC1A_CH6/ADC0_SE3/ADC0_DP3/PTE11/UART5_RTS_b/FLEXPWM1_A3/FTM3_CH6, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '15', peripheral: GPIOE, signal: 'GPIO, 12', pin_signal: HSADC1B_CH6/ADC0_SE11/ADC0_DM3/PTE12/FLEXPWM1_B3/FTM3_CH7, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '37', peripheral: GPIOE, signal: 'GPIO, 29', pin_signal: HSADC0A_CH4/CMP1_IN5/CMP0_IN5/PTE29/FTM0_CH2/FTM_CLKIN0, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '38', peripheral: GPIOE, signal: 'GPIO, 30', pin_signal: DAC0_OUT/CMP1_IN3/HSADC0A_CH5/PTE30/FTM0_CH3/FTM_CLKIN1, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDsPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE11 (pin 14)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE12 (pin 15)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE29 (pin 37)  */
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_ORANGE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE30 (pin 38)  */
    GPIO_PinInit(BOARD_LED_ORANGE_GPIO, BOARD_LED_ORANGE_PIN, &LED_ORANGE_config);

    const port_pin_config_t LED_RED = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as PTE11 */
                                       kPORT_MuxAsGpio,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTE11 (pin 14) is configured as PTE11 */
    PORT_SetPinConfig(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, &LED_RED);

    const port_pin_config_t LED_GREEN = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTE12 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTE12 (pin 15) is configured as PTE12 */
    PORT_SetPinConfig(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, &LED_GREEN);

    const port_pin_config_t LED_BLUE = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTE29 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE29 (pin 37) is configured as PTE29 */
    PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);

    const port_pin_config_t LED_ORANGE = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTE30 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTE30 (pin 38) is configured as PTE30 */
    PORT_SetPinConfig(BOARD_LED_ORANGE_PORT, BOARD_LED_ORANGE_PIN, &LED_ORANGE);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCELPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '138', peripheral: I2C1, signal: SDA, pin_signal: PTD9/I2C1_SDA/UART5_TX/FLEXPWM0_B3/FB_A17, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: '137', peripheral: I2C1, signal: SCL, pin_signal: PTD8/LLWU_P24/I2C1_SCL/UART5_RX/FLEXPWM0_A3/FB_A16, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: '125', peripheral: GPIOC, signal: 'GPIO, 18', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FLEXPWM1_A3/FB_TBST_b/FB_CS2_b/FB_BE15_8_b, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: '126', peripheral: GPIOC, signal: 'GPIO, 19', pin_signal: PTC19/UART3_CTS_b/ENET0_1588_TMR3/FLEXPWM1_B3/FB_CS3_b/FB_BE7_0_b/FB_TA_b, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCELPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCELPins(void)
{
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t ACCEL_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC18 (pin 125)  */
    GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1_config);

    gpio_pin_config_t ACCEL_INT2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC19 (pin 126)  */
    GPIO_PinInit(BOARD_ACCEL_INT2_GPIO, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2_config);

    const port_pin_config_t ACCEL_INT1 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC18 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC18 (pin 125) is configured as PTC18 */
    PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);

    const port_pin_config_t ACCEL_INT2 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC19 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC19 (pin 126) is configured as PTC19 */
    PORT_SetPinConfig(BOARD_ACCEL_INT2_PORT, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
        PORT_DFER_DFE_8_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_9_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t I2C_SCL = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as I2C1_SCL */
                                       kPORT_MuxAlt2,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTD8 (pin 137) is configured as I2C1_SCL */
    PORT_SetPinConfig(BOARD_I2C_SCL_PORT, BOARD_I2C_SCL_PIN, &I2C_SCL);

    const port_pin_config_t I2C_SDA = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as I2C1_SDA */
                                       kPORT_MuxAlt2,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTD9 (pin 138) is configured as I2C1_SDA */
    PORT_SetPinConfig(BOARD_I2C_SDA_PORT, BOARD_I2C_SDA_PIN, &I2C_SDA);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '82', peripheral: UART0, signal: TX, pin_signal: HSADC0B_CH3/PTB1/I2C0_SDA/FTM1_CH1/FTM0_FLT2/EWM_IN/FTM1_QD_PHB/UART0_TX/RMII0_MDC/MII0_MDC, direction: OUTPUT,
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '81', peripheral: UART0, signal: RX, pin_signal: HSADC0B_CH2/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA/UART0_RX/RMII0_MDIO/MII0_MDIO, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
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

    const port_pin_config_t DEBUG_UART_RX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART0_RX */
                                             kPORT_MuxAlt7,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB0 (pin 81) is configured as UART0_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

    const port_pin_config_t DEBUG_UART_TX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART0_TX */
                                             kPORT_MuxAlt7,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB1 (pin 82) is configured as UART0_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)

                  /* UART 0 receive data source select: UART0_RX pin. */
                  | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPOTPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '39', peripheral: HSADC0, signal: 'ADCA, CH12', pin_signal: HSADC0A_CH12/CMP0_IN4/CMP2_IN3}
  - {pin_num: '32', peripheral: ADC0, signal: VREFH, pin_signal: VREFH}
  - {pin_num: '33', peripheral: ADC0, signal: VREFL, pin_signal: VREFL}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPOTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPOTPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '72', peripheral: OSC0, signal: EXTAL0, pin_signal: EXTAL0/PTA18/XB_IN7/FTM0_FLT2/FTM_CLKIN0/XB_OUT8/FTM3_CH2, slew_rate: no_init, open_drain: no_init,
    pull_select: no_init, pull_enable: no_init}
  - {pin_num: '47', peripheral: ENET, signal: CLKIN_1588, pin_signal: PTE26/ENET_1588_CLKIN/FTM0_CH4/UART4_CTS_b, slew_rate: no_init, open_drain: no_init, drive_strength: low,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTA18 (pin 72) is configured as EXTAL0 */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTE26 (pin 47) is configured as ENET_1588_CLKIN */
    PORT_SetPinMux(BOARD_ENET_1588_CLKIN_PORT, BOARD_ENET_1588_CLKIN_PIN, kPORT_MuxAlt2);

    PORTE->PCR[26] = ((PORTE->PCR[26] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | PORT_PCR_PS(kPORT_PullDown)

                      /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding
                       * pin. */
                      | PORT_PCR_PE(kPORT_PullDisable)

                      /* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin
                       * is configured as a digital output. */
                      | PORT_PCR_DSE(kPORT_LowDriveStrength));

    SIM->SOPT2 = ((SIM->SOPT2 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT2_TIMESRC_MASK)))

                  /* IEEE 1588 timestamp clock source select: External bypass clock (ENET_1588_CLKIN). */
                  | SIM_SOPT2_TIMESRC(SOPT2_TIMESRC_ENET));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
