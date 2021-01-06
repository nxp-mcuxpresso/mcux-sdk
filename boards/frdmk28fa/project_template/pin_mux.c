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
processor: MK28FN2M0Axxx15
package_id: MK28FN2M0AVMI15
mcu_data: ksdk2_0
processor_version: 0.0.8
board: FRDM-K28FA
pin_labels:
- {pin_num: L9, pin_signal: PTA4/LLWU_P3/FTM0_CH1/FXIO0_D14/NMI_b, label: SW2, identifier: SW2}
- {pin_num: A6, pin_signal: PTD0/LLWU_P12/SPI0_PCS0/LPUART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/FXIO0_D22, label: SW3, identifier: SW3}
- {pin_num: N13, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0/TPM_CLKIN0, label: 'Y2[1]/EXTAL', identifier: EXTAL0}
- {pin_num: M13, pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1/LPTMR1_ALT1/TPM_CLKIN1, label: 'Y2[3]/XTAL', identifier: XTAL0}
- {pin_num: N5, pin_signal: XTAL32, label: 'Y1[1]/XTAL32_RTC', identifier: XTAL32K}
- {pin_num: N6, pin_signal: EXTAL32, label: 'Y1[2]/EXTAL32_RTC', identifier: EXTAL32K}
- {pin_num: E2, pin_signal: PTE6/LLWU_P16/FXIO0_D12/LPUART3_CTS_b/I2S0_MCLK/QSPI0B_DATA3/FTM3_CH1/SDHC0_D4, label: 'J1[7]/D1[1]/LEDRGB_RED', identifier: LED_RED}
- {pin_num: E3, pin_signal: PTE7/FXIO0_D13/LPUART3_RTS_b/I2S0_RXD0/QSPI0B_SCLK/FTM3_CH2/QSPI0A_SS1_B, label: 'J1[15]/D1[4]/LEDRGB_GREEN', identifier: LED_GREEN}
- {pin_num: E4, pin_signal: PTE8/I2S0_RXD1/FXIO0_D14/I2S0_RX_FS/QSPI0B_DATA0/FTM3_CH3/SDHC0_D5, label: 'J1[13]/D1[3]/LEDRGB_BLUE', identifier: LED_BLUE}
- {pin_num: A7, pin_signal: PTC25/LPUART0_RX/FB_A4/SDRAM_D4/QSPI0A_SCLK, label: LPUART0_RX_TGTMCU, identifier: DEBUG_UART_RX}
- {pin_num: J9, pin_signal: PTA31/I2C3_SCL/LPUART3_RTS_b/FB_A10/SDRAM_D10/I2S1_RX_BCLK, label: 'J1[3]/I2S0_TX_FS'}
- {pin_num: H10, pin_signal: PTA30/I2C3_SDA/LPUART3_CTS_b/FB_A11/SDRAM_D11/I2S1_RX_FS, label: 'J1[1]/I2S0_TX_BCLK'}
- {pin_num: C6, pin_signal: PTC28/I2C3_SDA/FB_A1/SDRAM_D1/QSPI0A_DATA1, label: 'U6[6]/I2C SDA', identifier: I2C_SDA}
- {pin_num: B6, pin_signal: PTC29/I2C3_SCL/FB_A0/SDRAM_D0/QSPI0A_SS0_B, label: 'U6[4]/I2C_SCL', identifier: I2C_SCL}
- {pin_num: E6, pin_signal: PTC26/LPUART0_CTS_b/FB_A3/SDRAM_D3/QSPI0A_DATA0, label: 'U6[11]/INT1_FXOS8700CQ_R', identifier: ACCEL_INT1}
- {pin_num: C1, pin_signal: PTE2/LLWU_P1/SPI1_SOUT/LPUART1_CTS_b/SDHC0_DCLK/QSPI0A_DATA0/FXIO0_D0/SPI1_SCK, label: 'U11[5]/QSPIA_DATA0', identifier: QSPIA_DATA0}
- {pin_num: E1, pin_signal: PTE4/LLWU_P2/SPI1_SIN/LPUART3_TX/SDHC0_D3/QSPI0A_DATA1, label: 'U11[2]/QSPIA_DATA1', identifier: QSPIA_DATA1}
- {pin_num: D1, pin_signal: PTE3/SPI1_PCS2/LPUART1_RTS_b/SDHC0_CMD/QSPI0A_DATA2/FXIO0_D1/SPI1_SOUT, label: 'U11[3]/QSPIA_DATA2', identifier: QSPIA_DATA2}
- {pin_num: A1, pin_signal: PTE0/SPI1_PCS1/LPUART1_TX/SDHC0_D1/QSPI0A_DATA3/I2C1_SDA/RTC_CLKOUT, label: 'U11[7]/QSPIA_DATA3', identifier: QSPIA_DATA3}
- {pin_num: B1, pin_signal: PTE1/LLWU_P0/SPI1_SCK/LPUART1_RX/SDHC0_D0/QSPI0A_SCLK/I2C1_SCL/SPI1_SIN, label: 'U11[6]/QSPIA_SCLK', identifier: QSPIA_SCLK}
- {pin_num: D2, pin_signal: PTE5/SPI1_PCS0/LPUART3_RX/SDHC0_D2/QSPI0A_SS0_B/FTM3_CH0/USB0_SOF_OUT, label: 'U11[1]/QSPIA_SS', identifier: QSPIA_SS}
- {pin_num: H1, pin_signal: USB1_DM, label: 'J24[2]USB_CONN_DN', identifier: K28_MICRO_USB_DM_DCD;K28_MICRO_USB_DM_PHY;K28_MICRO_USB_DM_HS}
- {pin_num: J1, pin_signal: USB1_DP, label: 'J24[3]USB_CONN_DP', identifier: K28_MICRO_USB_DP_DCD;K28_MICRO_USB_DP_PHY;K28_MICRO_USB_DP_HS}
- {pin_num: H12, pin_signal: PTA28/LPUART3_TX/SDHC0_D3/FB_A25/I2S1_RXD1, label: 'J19[P2]/SDHC0_D3', identifier: SDHC0_D3}
- {pin_num: J11, pin_signal: PTA25/LPUART2_RX/SDHC0_D0/FB_A14/SDRAM_D14/FB_A28/I2S1_TX_FS, label: 'J19[P7]/SDHC0_D0', identifier: SDHC0_D0}
- {pin_num: H11, pin_signal: PTA29/LPUART3_RX/SDHC0_D2/FB_A24/I2S1_RXD0, label: 'J19[P1]/SDHC0_D2', identifier: SDHC0_D2}
- {pin_num: K11, pin_signal: PTA24/LPUART2_TX/SDHC0_D1/FB_A15/SDRAM_D15/FB_A29/I2S1_TX_BCLK, label: 'J19[P8]/SDHC0_D1', identifier: SDHC0_D1}
- {pin_num: J10, pin_signal: PTA26/LPUART2_CTS_b/SDHC0_DCLK/FB_A13/SDRAM_D13/FB_A27/I2S1_TXD0, label: 'J19[P5]/SDHC0_DCLK', identifier: SDHC0_DCLK}
- {pin_num: H13, pin_signal: PTA27/LPUART2_RTS_b/SDHC0_CMD/FB_A12/SDRAM_D12/FB_A26/I2S1_TXD1, label: 'J19[P3]/SDHC0_CMD', identifier: SDHC0_CMD}
- {pin_num: F13, pin_signal: PTB5/FTM2_FLT0, label: 'J19[G1]/SD_CARD_DETECT', identifier: SDCARD_CARD_DETECTION}
- {pin_num: N4, pin_signal: ADC0_SE16, label: 'Q5[2]/LIGHT_SENSOR', identifier: LIGHT_SENSOR}
- {pin_num: C9, pin_signal: CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0/FXIO0_D17, label: 'U13[J8]/SDRAM_A14', identifier: SDRAM_A14}
- {pin_num: A8, pin_signal: PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13/FXIO0_D18, label: 'U13[J7]/SDRAM_A13', identifier: SDRAM_A13}
- {pin_num: A4, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/LPUART2_RX/FTM3_CH2/FB_AD4/SDRAM_A12/I2C0_SCL, label: 'U13[J3]/SDRAM_A12', identifier: SDRAM_A12}
- {pin_num: B4, pin_signal: PTD3/SPI0_SIN/LPUART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA, label: 'U13[J2]/SDRAM_A11', identifier: SDRAM_A11}
- {pin_num: B5, pin_signal: PTD4/LLWU_P14/SPI0_PCS1/LPUART0_RTS_b/FTM0_CH4/FB_AD2/SDRAM_A10/EWM_IN/SPI1_PCS0, label: 'U13[H3]/SDRAM_A10', identifier: SDRAM_A10}
- {pin_num: C4, pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/LPUART0_CTS_b/FTM0_CH5/FB_AD1/SDRAM_A9/EWM_OUT_b/SPI1_SCK, label: 'U13[H2]/SDRAM_A9', identifier: SDRAM_A9}
- {pin_num: A11, pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/LPTMR1_ALT2/I2S0_RXD0/FB_AD10/SDRAM_A18/CMP0_OUT/FTM0_CH2, label: 'U13[H1]/SDRAM_A18', identifier: SDRAM_A18}
- {pin_num: B11, pin_signal: PTC4/LLWU_P8/SPI0_PCS0/LPUART1_TX/FTM0_CH3/FB_AD11/SDRAM_A19/CMP1_OUT, label: 'U13[G3]/SDRAM_A19', identifier: SDRAM_A19}
- {pin_num: E5, pin_signal: PTD7/CMT_IRO/LPUART0_TX/FTM0_CH7/SDRAM_CKE/FTM0_FLT1/SPI1_SIN, label: 'U13[F3]/SDRAM_CKE', identifier: SDRAM_CKE}
- {pin_num: E7, pin_signal: PTC17/LPUART3_TX/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b/SDRAM_DQM3, label: 'U13[F1]/SDRAM_DQM3', identifier: SDRAM_DQM3}
- {pin_num: B8, pin_signal: PTC13/LPUART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, label: 'U13[D1]/SDRAM_D26', identifier: SDRAM_D26}
- {pin_num: C8, pin_signal: PTC14/LPUART4_RX/FB_AD25/SDRAM_D25/FXIO0_D20, label: 'U13[D2]/SDRAM_D25', identifier: SDRAM_D25}
- {pin_num: D8, pin_signal: PTC15/LPUART4_TX/FB_AD24/SDRAM_D24/FXIO0_D21, label: 'U13[E1]/SDRAM_D24', identifier: SDRAM_D24}
- {pin_num: E8, pin_signal: PTC16/LPUART3_RX/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b/SDRAM_DQM2, label: 'U13[E8]/SDRAM_DQM2', identifier: SDRAM_DQM2}
- {pin_num: F8, pin_signal: PTB16/SPI1_SOUT/LPUART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0, label: 'U13[B9]/SDRAM_D17', identifier: SDRAM_D17}
- {pin_num: B9, pin_signal: PTC12/LPUART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, label: 'U13[C2]/SDRAM_D27', identifier: SDRAM_D27}
- {pin_num: D9, pin_signal: PTB21/SPI2_SCK/FB_AD30/SDRAM_D30/CMP1_OUT/FXIO0_D9, label: 'U13[B1]/SDRAM_D30', identifier: SDRAM_D30}
- {pin_num: F9, pin_signal: PTB9/SPI1_PCS1/LPUART3_CTS_b/FB_AD20/SDRAM_D20, label: 'U13[C8]/SDRAM_D20', identifier: SDRAM_D20}
- {pin_num: G9, pin_signal: PTB10/SPI1_PCS0/LPUART3_RX/I2C2_SCL/FB_AD19/SDRAM_D19/FTM0_FLT1/FXIO0_D4, label: 'U13[C9]/SDRAM_D19', identifier: SDRAM_D19}
- {pin_num: B10, pin_signal: CMP0_IN1/PTC7/SPI0_SIN/USB0_SOF_OUT/I2S0_RX_FS/FB_AD8/SDRAM_A16/FXIO0_D15, label: 'U13[H7]/SDRAM_A16', identifier: SDRAM_A16}
- {pin_num: C10, pin_signal: CMP0_IN2/PTC8/FTM3_CH4/I2S0_MCLK/FB_AD7/SDRAM_A15/FXIO0_D16, label: 'U13[H8]/SDRAM_A15', identifier: SDRAM_A15}
- {pin_num: D10, pin_signal: PTB20/SPI2_PCS0/FB_AD31/SDRAM_D31/CMP0_OUT/FXIO0_D8, label: 'U13[A2]/SDRAM_D31', identifier: SDRAM_D31}
- {pin_num: F10, pin_signal: PTB8/LPUART3_RTS_b/FB_AD21/SDRAM_D21, label: 'U13[D9]/SDRAM_D21', identifier: SDRAM_D21}
- {pin_num: G10, pin_signal: ADC0_SE13/PTB3/I2C0_SDA/LPUART0_CTS_b/SDRAM_CS0_b/FTM0_FLT0/FXIO0_D3, label: 'U13[G9]/SDRAM_CS0_b', identifier: SDRAM_CS0_b}
- {pin_num: F11, pin_signal: PTB7/FB_AD22/SDRAM_D22, label: 'U13[D8]/SDRAM_D22', identifier: SDRAM_D22}
- {pin_num: G11, pin_signal: ADC0_SE12/PTB2/I2C0_SCL/LPUART0_RTS_b/SDRAM_WE_b/FTM0_FLT3/FXIO0_D2, label: 'U13[F9]/SDRAM_WE_b', identifier: SDRAM_WE_b}
- {pin_num: B12, pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/LPUART1_RTS_b/FTM0_CH0/FB_AD13/SDRAM_A21/I2S0_TXD0/FXIO0_D13, label: 'U13[G2]/SDRAM_A21', identifier: SDRAM_A21}
- {pin_num: C12, pin_signal: PTB23/SPI2_SIN/SPI0_PCS5/FB_AD28/SDRAM_D28/FXIO0_D11, label: 'U13[C1]/SDRAM_D28', identifier: SDRAM_D28}
- {pin_num: D12, pin_signal: PTB18/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/SDRAM_A23/FTM2_QD_PHA/TPM2_CH0/FXIO0_D6, label: 'U13[G8]/SDRAM_A23', identifier: SDRAM_A23}
- {pin_num: F12, pin_signal: PTB6/FB_AD23/SDRAM_D23, label: 'U13[E9]/SDRAM_D23', identifier: SDRAM_D23}
- {pin_num: G12, pin_signal: ADC0_SE9/PTB1/I2C0_SDA/FTM1_CH1/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1/FXIO0_D1, label: 'U13[F8]/SDRAM_RAS_b', identifier: SDRAM_RAS_b}
- {pin_num: A12, pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/LPUART1_RX/FTM0_CH2/CLKOUT/I2S0_TX_BCLK, label: 'U13[F2]/CLKOUT', identifier: CLKOUT}
- {pin_num: A13, pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/LPUART1_CTS_b/FTM0_CH1/FB_AD12/SDRAM_A20/I2S0_TX_FS, label: 'U13[H9]/SDRAM_A20', identifier: SDRAM_A20}
- {pin_num: B13, pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/USB0_SOF_OUT/FB_AD14/SDRAM_A22/I2S0_TXD1/FXIO0_D12, label: 'U13[G7]/SDRAM_A22', identifier: SDRAM_A22}
- {pin_num: C13, pin_signal: PTB22/SPI2_SOUT/FB_AD29/SDRAM_D29/FXIO0_D10, label: 'U13[B2]/SDRAM_D29', identifier: SDRAM_D29}
- {pin_num: D13, pin_signal: PTB17/SPI1_SIN/LPUART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, label: 'U13[A8]/SDRAM_D16', identifier: SDRAM_D16}
- {pin_num: E13, pin_signal: PTB11/SPI1_SCK/LPUART3_TX/I2C2_SDA/FB_AD18/SDRAM_D18/FTM0_FLT2/FXIO0_D5, label: 'U13[B8]/SDRAM_D18', identifier: SDRAM_D18}
- {pin_num: G13, pin_signal: ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0/FXIO0_D0, label: 'U13[F7]/SDRAM_CAS_b', identifier: SDRAM_CAS_b}
- {pin_num: J2, pin_signal: USB1_VBUS, label: 'J24[1]P5V0_USB_CONN_VBUS', identifier: P5V_K28_USB}
- {pin_num: M11, pin_signal: PTA11/LLWU_P23/I2C2_SCL/FTM2_CH1/FXIO0_D17/FTM2_QD_PHB/TPM2_CH1/USB1_ID, label: 'J24[4]TC_USB_ID', identifier: USB_ID}
- {pin_num: F2, pin_signal: VREG_IN0, label: VREG_IN0, identifier: VREG_IN0}
- {pin_num: B7, pin_signal: PTC24/LPUART0_TX/FB_A5/SDRAM_D5/QSPI0A_DATA3, label: LPUART0_TX_TGTMCU, identifier: DEBUG_UART_TX}
- {pin_num: K1, pin_signal: USB1_VSS, label: GND}
- {pin_num: L1, pin_signal: ADC0_DM1, label: 'J3[1]/ADC0_DM1'}
- {pin_num: M1, pin_signal: ADC0_DP1, label: 'J3[3]/ADC0_DP1'}
- {pin_num: A2, pin_signal: PTD14/SPI2_SIN/FB_A22/FXIO0_D30, label: 'J27[25]/FXIO0_D30/J2[10]/Arduino_D12_SPI2_SIN'}
- {pin_num: B2, pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/FB_A20/FXIO0_D28, label: 'J27[23]/FXIO0_D28/J2[12]/Arduino_D13_SPI2_SCK'}
- {pin_num: C2, pin_signal: PTD11/LLWU_P25/SPI2_PCS0/LPUART1_CTS_b/FB_A19/FXIO0_D27, label: 'J27[22]/FXIO0_D27'}
- {pin_num: G2, pin_signal: VREG_OUT, label: GND}
- {pin_num: H2, pin_signal: VREG_IN1, label: VREG_IN0}
- {pin_num: A3, pin_signal: PTD15/SPI2_PCS1/FB_A23/FXIO0_D31, label: 'J27[26]/FXIO0_D31/J2[6]/Arduino_D10_SPI2_PCS1'}
- {pin_num: B3, pin_signal: PTD13/SPI2_SOUT/FB_A21/FXIO0_D29, label: 'J27[24]/FXIO0_D29/J2[8]/ Arduino_D11_SPI2_SOUT '}
- {pin_num: C3, pin_signal: VSS5, label: GND}
- {pin_num: D3, pin_signal: PTD10/LPUART1_RTS_b/FB_A18/FXIO0_D26, label: 'J27[21]/FXIO0_D26'}
- {pin_num: F3, pin_signal: PTE9/LLWU_P17/I2S0_TXD1/FXIO0_D15/I2S0_RX_BCLK/QSPI0B_DATA2/FTM3_CH4/SDHC0_D6, label: 'J1[9]/I2S0_RX_BCLK'}
- {pin_num: G3, pin_signal: VSS28, label: GND}
- {pin_num: J3, pin_signal: VDDA, label: VDD_K28F}
- {pin_num: K3, pin_signal: VREFH, label: VREFH}
- {pin_num: L3, pin_signal: VSSA46, label: GND}
- {pin_num: N3, pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC0_SE22, label: 'J3[5]/VREF_OUT'}
- {pin_num: D4, pin_signal: PTD9/I2C0_SDA/LPUART1_TX/FB_A17/FXIO0_D25, label: 'J27[20]/FXIO0_D25'}
- {pin_num: F4, pin_signal: PTE10/LLWU_P18/I2C3_SDA/FXIO0_D16/I2S0_TXD0/QSPI0B_DATA1/FTM3_CH5/SDHC0_D7, label: 'J1[5]/I2S0_TXD0'}
- {pin_num: G4, pin_signal: PTE11/I2C3_SCL/FXIO0_D17/I2S0_TX_FS/QSPI0B_SS0_B/FTM3_CH6/QSPI0A_DQS, label: 'J1[3]/I2S0_TX_FS'}
- {pin_num: H4, pin_signal: PTE12/LPUART2_TX/I2S0_TX_BCLK/QSPI0B_DQS/FTM3_CH7/FXIO0_D2, label: 'J1[1]/I2S0_TX_BCLK'}
- {pin_num: J4, pin_signal: VSSA45, label: GND}
- {pin_num: K4, pin_signal: VREFL, label: GND}
- {pin_num: L4, pin_signal: VSS184, label: GND}
- {pin_num: M4, pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'J3[13]/DAC0OUT'}
- {pin_num: A5, pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/LPUART2_CTS_b/FTM3_CH1/FB_CS0_b/FXIO0_D23, label: 'J4[6]/Arduino_D16_ADC0_SE5b'}
- {pin_num: C5, pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/LPUART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'J4[8]/Arduino_D17_ADC0_SE7b'}
- {pin_num: D5, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART1_RX/FB_A16/FXIO0_D24, label: 'J27[19]/FXIO0_D24'}
- {pin_num: G5, pin_signal: VDDIO_E6, label: VDDIO_E_1V8}
- {pin_num: H5, pin_signal: VDDIO_E17, label: VDDIO_E_1V8}
- {pin_num: J5, pin_signal: VSS185, label: GND}
- {pin_num: K5, pin_signal: VDD_CORE135, label: VDDCORE_1V2}
- {pin_num: L5, pin_signal: VDD_CORE159, label: VDDCORE_1V2}
- {pin_num: M5, pin_signal: RTC_WAKEUP_B, label: 'J3[7]/RTC_WAKEUP_B'}
- {pin_num: D6, pin_signal: PTC27/LPUART0_RTS_b/FB_A2/SDRAM_D2/QSPI0A_DATA2, label: 'U6[16]/RST_FXOS8700CQ'}
- {pin_num: G6, pin_signal: VDD72, label: VDD_K28F}
- {pin_num: H6, pin_signal: VDD136, label: VDD_K28F}
- {pin_num: M6, pin_signal: VBAT, label: VBAT}
- {pin_num: C7, pin_signal: PTC19/LPUART3_CTS_b/FB_CS3_b/FB_BE7_0_BLS31_24_b/SDRAM_DQM0/FB_TA_b/QSPI0A_SS1_B, label: 'J2[2]/Arduino_D8'}
- {pin_num: D7, pin_signal: PTC18/LPUART3_RTS_b/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b/SDRAM_DQM1, label: 'J1[16]/Arduino_D7'}
- {pin_num: G7, pin_signal: VDD58, label: VDD_K28F}
- {pin_num: H7, pin_signal: VDD105, label: VDD_K28F}
- {pin_num: K7, pin_signal: PTA21/LLWU_P21/I2C0_SDA/LPUART4_RX/FXIO0_D9/EWM_IN, label: 'J27[18]/PDWN/TE'}
- {pin_num: L7, pin_signal: PTA20/I2C0_SCL/LPUART4_TX/FTM_CLKIN1/FXIO0_D8/EWM_OUT_b/TPM_CLKIN1, label: 'J27[5]/FXIO_D8/VSync'}
- {pin_num: N7, pin_signal: VSS/CORE_BYPASS, label: GND}
- {pin_num: G8, pin_signal: VSS18, label: GND}
- {pin_num: H8, pin_signal: VSS73, label: GND}
- {pin_num: J8, pin_signal: VSS104, label: GND}
- {pin_num: K8, pin_signal: PTA22/LPUART4_CTS_b/FXIO0_D6/RTC_CLKOUT/USB0_CLKIN, label: 'J27[7]/FXIO0_D6/PCLK', identifier: USB0_CLKIN}
- {pin_num: L8, pin_signal: PTA23/LPUART4_RTS_b/FXIO0_D7, label: 'J27[6]/FXIO_D7/HREF'}
- {pin_num: M8, pin_signal: PTA3/LPUART0_RTS_b/FTM0_CH0/FXIO0_D13/JTAG_TMS/SWD_DIO, label: 'J23[2]/SWD_DIO_TGTMCU'}
- {pin_num: N8, pin_signal: PTA0/LPUART0_CTS_b/FTM0_CH5/FXIO0_D10/JTAG_TCLK/SWD_CLK, label: 'J17[1]/K28F_SWD_CLK'}
- {pin_num: A9, pin_signal: PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b/FXIO0_D19, label: 'J1[8]/Arduino_D3_FTM3_CH7'}
- {pin_num: H9, pin_signal: PTB4/SDRAM_CS1_b/FTM1_FLT0, label: 'J1[6]/Arduino_D2'}
- {pin_num: K9, pin_signal: ADC0_SE11/PTA8/I2C1_SCL/FTM1_CH0/FTM1_QD_PHA/TPM1_CH0/TRACE_D2, label: 'J4[4]/Arduino_D15_ADC0_SE11/J27[3]/I2C1_SCL'}
- {pin_num: M9, pin_signal: PTA2/LPUART0_TX/FTM0_CH7/I2C3_SCL/FXIO0_D12/JTAG_TDO/TRACE_SWO, label: 'J23[6]/TRACE_SWO /J27[28]/INT'}
- {pin_num: N9, pin_signal: PTA1/LPUART0_RX/FTM0_CH6/I2C3_SDA/FXIO0_D11/JTAG_TDI, label: 'J27[27]/GPIO0'}
- {pin_num: A10, pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/SDRAM_A17/I2S0_MCLK/FXIO0_D14, label: 'J1[10]/Arduino_D4'}
- {pin_num: E10, pin_signal: PTB14/LPUART0_RX/FB_A7/SDRAM_D7, label: 'U12[3]'}
- {pin_num: K10, pin_signal: PTA9/I2C1_SDA/FTM1_CH1/FTM1_QD_PHB/TPM1_CH1/TRACE_D1, label: 'J27[4]/I2C1_SDA'}
- {pin_num: L10, pin_signal: ADC0_SE10/PTA7/I2C2_SDA/FTM0_CH4/TRACE_D3, label: 'J4[2]/Arduino_D14_ADC0_SE10'}
- {pin_num: M10, pin_signal: PTA6/I2C2_SCL/FTM0_CH3/CLKOUT/TRACE_CLKOUT, label: 'J27[8]/CLKOUT/XCLK'}
- {pin_num: N10, pin_signal: PTA5/USB0_CLKIN/FTM0_CH2/FXIO0_D15/I2S0_TX_BCLK/JTAG_TRST_b, label: 'J27[17]/Camera_Reset'}
- {pin_num: C11, pin_signal: VSS133, label: GND}
- {pin_num: D11, pin_signal: PTB19/SDRAM_CKE/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1/FXIO0_D7, label: 'J2[4]/Arduino_D9_FTM2_CH1'}
- {pin_num: E11, pin_signal: PTB13/LPUART0_CTS_b/FTM1_CH1/FTM0_CH5/FB_A8/SDRAM_D8/FTM1_QD_PHB/TPM1_CH1, label: 'J1[14]/Arduino_D6_FTM1_CH1/FTM0_CH5'}
- {pin_num: L11, pin_signal: PTA13/LLWU_P4/FTM1_CH1/TRACE_D3/FXIO0_D19/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1, label: 'J27[13]/FXIO0_D19/CAM_D3'}
- {pin_num: N11, pin_signal: PTA10/LLWU_P22/I2C2_SDA/FTM2_CH0/FXIO0_D16/FTM2_QD_PHA/TPM2_CH0/TRACE_D0, label: 'J27[16]/FXIO0_D16/CAM_D0'}
- {pin_num: E12, pin_signal: PTB12/LPUART0_RTS_b/FTM1_CH0/FTM0_CH4/FB_A9/SDRAM_D9/FTM1_QD_PHA/TPM1_CH0, label: 'J1[12]/Arduino_D5_FTM1_CH0/FTM0_CH4'}
- {pin_num: J12, pin_signal: PTA17/SPI0_SIN/LPUART0_RTS_b/FXIO0_D23/I2S0_MCLK/I2S1_MCLK, label: 'J27[9]/FXIO0_D23/CAM_D7'}
- {pin_num: K12, pin_signal: PTA15/SPI0_SCK/LPUART0_RX/TRACE_D1/FXIO0_D21/I2S0_RXD0, label: 'J27[11]/FXIO0_D21/CAM_D5'}
- {pin_num: L12, pin_signal: PTA12/FTM1_CH0/TRACE_CLKOUT/FXIO0_D18/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0, label: 'J27[14]/FXIO0_D18/CAM_D2'}
- {pin_num: M12, pin_signal: VSS88, label: GND}
- {pin_num: N12, pin_signal: VDD86, label: VDD_K28F}
- {pin_num: J13, pin_signal: PTA16/SPI0_SOUT/LPUART0_CTS_b/TRACE_D0/FXIO0_D22/I2S0_RX_FS/I2S0_RXD1, label: 'J27[10]/FXIO0_D22/CAM_D6'}
- {pin_num: K13, pin_signal: PTA14/SPI0_PCS0/LPUART0_TX/TRACE_D2/FXIO0_D20/I2S0_RX_BCLK/I2S0_TXD1, label: 'J27[12]/FXIO0_D20/CAM_D4'}
- {pin_num: L13, pin_signal: RESET_b, label: 'J23[10]/J3[6]/RST_TGTMCU_b'}
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
  - {pin_num: M9, peripheral: TPIU, signal: SWO, pin_signal: PTA2/LPUART0_TX/FTM0_CH7/I2C3_SCL/FXIO0_D12/JTAG_TDO/TRACE_SWO, pull_select: down, pull_enable: disable}
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

    /* PORTA2 (pin M9) is configured as TRACE_SWO */
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
BOARD_InitButtonsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L9, peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/FXIO0_D14/NMI_b, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: A6, peripheral: GPIOD, signal: 'GPIO, 0', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/LPUART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/FXIO0_D22, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitButtonsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitButtonsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA4 (pin L9)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD0 (pin A6)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    const port_pin_config_t SW2 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
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
    /* PORTA4 (pin L9) is configured as PTA4 */
    PORT_SetPinConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
        PORT_DFER_DFE_0_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t SW3 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTD0 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTD0 (pin A6) is configured as PTD0 */
    PORT_SetPinConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: N13, peripheral: OSC, signal: EXTAL0, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0/TPM_CLKIN0, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: M13, peripheral: OSC, signal: XTAL0, pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1/LPTMR1_ALT1/TPM_CLKIN1, slew_rate: no_init, open_drain: no_init,
    pull_select: no_init, pull_enable: no_init}
  - {pin_num: N5, peripheral: RTC, signal: XTAL32, pin_signal: XTAL32}
  - {pin_num: N6, peripheral: RTC, signal: EXTAL32, pin_signal: EXTAL32}
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

    /* PORTA18 (pin N13) is configured as EXTAL0 */
    PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTA19 (pin M13) is configured as XTAL0 */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E2, peripheral: GPIOE, signal: 'GPIO, 6', pin_signal: PTE6/LLWU_P16/FXIO0_D12/LPUART3_CTS_b/I2S0_MCLK/QSPI0B_DATA3/FTM3_CH1/SDHC0_D4, direction: OUTPUT,
    gpio_init_state: 'true', slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: E3, peripheral: GPIOE, signal: 'GPIO, 7', pin_signal: PTE7/FXIO0_D13/LPUART3_RTS_b/I2S0_RXD0/QSPI0B_SCLK/FTM3_CH2/QSPI0A_SS1_B, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: E4, peripheral: GPIOE, signal: 'GPIO, 8', pin_signal: PTE8/I2S0_RXD1/FXIO0_D14/I2S0_RX_FS/QSPI0B_DATA0/FTM3_CH3/SDHC0_D5, direction: OUTPUT, gpio_init_state: 'true',
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
    /* Initialize GPIO functionality on pin PTE6 (pin E2)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE7 (pin E3)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE8 (pin E4)  */
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

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
                                       /* Pin is configured as PTE6 */
                                       kPORT_MuxAsGpio,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTE6 (pin E2) is configured as PTE6 */
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
                                         /* Pin is configured as PTE7 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTE7 (pin E3) is configured as PTE7 */
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
                                        /* Pin is configured as PTE8 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE8 (pin E4) is configured as PTE8 */
    PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B7, peripheral: LPUART0, signal: TX, pin_signal: PTC24/LPUART0_TX/FB_A5/SDRAM_D5/QSPI0A_DATA3, direction: OUTPUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: A7, peripheral: LPUART0, signal: RX, pin_signal: PTC25/LPUART0_RX/FB_A4/SDRAM_D4/QSPI0A_SCLK, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
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
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

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
                                             /* Pin is configured as LPUART0_TX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTC24 (pin B7) is configured as LPUART0_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);

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
                                             /* Pin is configured as LPUART0_RX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTC25 (pin A7) is configured as LPUART0_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 transmit data source select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 receive data source select: LPUART0_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCELPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B6, peripheral: I2C3, signal: SCL, pin_signal: PTC29/I2C3_SCL/FB_A0/SDRAM_D0/QSPI0A_SS0_B, slew_rate: fast, open_drain: enable, pull_select: down, pull_enable: disable}
  - {pin_num: C6, peripheral: I2C3, signal: SDA, pin_signal: PTC28/I2C3_SDA/FB_A1/SDRAM_D1/QSPI0A_DATA1, slew_rate: fast, open_drain: enable, pull_select: down, pull_enable: disable}
  - {pin_num: E6, peripheral: GPIOC, signal: 'GPIO, 26', pin_signal: PTC26/LPUART0_CTS_b/FB_A3/SDRAM_D3/QSPI0A_DATA0, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
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

    gpio_pin_config_t ACCEL_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC26 (pin E6)  */
    GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1_config);

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
                                          /* Pin is configured as PTC26 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC26 (pin E6) is configured as PTC26 */
    PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);

    const port_pin_config_t I2C_SDA = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is enabled */
                                       kPORT_OpenDrainEnable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as I2C3_SDA */
                                       kPORT_MuxAlt2,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTC28 (pin C6) is configured as I2C3_SDA */
    PORT_SetPinConfig(BOARD_I2C_SDA_PORT, BOARD_I2C_SDA_PIN, &I2C_SDA);

    const port_pin_config_t I2C_SCL = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is enabled */
                                       kPORT_OpenDrainEnable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as I2C3_SCL */
                                       kPORT_MuxAlt2,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTC29 (pin B6) is configured as I2C3_SCL */
    PORT_SetPinConfig(BOARD_I2C_SCL_PORT, BOARD_I2C_SCL_PIN, &I2C_SCL);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitQSPI_FLASHPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C1, peripheral: QuadSPI0, signal: 'DATA0, A', pin_signal: PTE2/LLWU_P1/SPI1_SOUT/LPUART1_CTS_b/SDHC0_DCLK/QSPI0A_DATA0/FXIO0_D0/SPI1_SCK, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: E1, peripheral: QuadSPI0, signal: 'DATA1, A', pin_signal: PTE4/LLWU_P2/SPI1_SIN/LPUART3_TX/SDHC0_D3/QSPI0A_DATA1, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: D1, peripheral: QuadSPI0, signal: 'DATA2, A', pin_signal: PTE3/SPI1_PCS2/LPUART1_RTS_b/SDHC0_CMD/QSPI0A_DATA2/FXIO0_D1/SPI1_SOUT, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: A1, peripheral: QuadSPI0, signal: 'DATA3, A', pin_signal: PTE0/SPI1_PCS1/LPUART1_TX/SDHC0_D1/QSPI0A_DATA3/I2C1_SDA/RTC_CLKOUT, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: B1, peripheral: QuadSPI0, signal: 'SCLK, A', pin_signal: PTE1/LLWU_P0/SPI1_SCK/LPUART1_RX/SDHC0_D0/QSPI0A_SCLK/I2C1_SCL/SPI1_SIN, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: D2, peripheral: QuadSPI0, signal: 'SS0, A', pin_signal: PTE5/SPI1_PCS0/LPUART3_RX/SDHC0_D2/QSPI0A_SS0_B/FTM3_CH0/USB0_SOF_OUT, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitQSPI_FLASHPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitQSPI_FLASHPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    const port_pin_config_t QSPIA_DATA3 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as QSPI0A_DATA3 */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTE0 (pin A1) is configured as QSPI0A_DATA3 */
    PORT_SetPinConfig(BOARD_QSPIA_DATA3_PORT, BOARD_QSPIA_DATA3_PIN, &QSPIA_DATA3);

    const port_pin_config_t QSPIA_SCLK = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as QSPI0A_SCLK */
                                          kPORT_MuxAlt5,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTE1 (pin B1) is configured as QSPI0A_SCLK */
    PORT_SetPinConfig(BOARD_QSPIA_SCLK_PORT, BOARD_QSPIA_SCLK_PIN, &QSPIA_SCLK);

    const port_pin_config_t QSPIA_DATA0 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as QSPI0A_DATA0 */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTE2 (pin C1) is configured as QSPI0A_DATA0 */
    PORT_SetPinConfig(BOARD_QSPIA_DATA0_PORT, BOARD_QSPIA_DATA0_PIN, &QSPIA_DATA0);

    const port_pin_config_t QSPIA_DATA2 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as QSPI0A_DATA2 */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTE3 (pin D1) is configured as QSPI0A_DATA2 */
    PORT_SetPinConfig(BOARD_QSPIA_DATA2_PORT, BOARD_QSPIA_DATA2_PIN, &QSPIA_DATA2);

    const port_pin_config_t QSPIA_DATA1 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as QSPI0A_DATA1 */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTE4 (pin E1) is configured as QSPI0A_DATA1 */
    PORT_SetPinConfig(BOARD_QSPIA_DATA1_PORT, BOARD_QSPIA_DATA1_PIN, &QSPIA_DATA1);

    const port_pin_config_t QSPIA_SS = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as QSPI0A_SS0_B */
                                        kPORT_MuxAlt5,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE5 (pin D2) is configured as QSPI0A_SS0_B */
    PORT_SetPinConfig(BOARD_QSPIA_SS_PORT, BOARD_QSPIA_SS_PIN, &QSPIA_SS);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSBPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: H1, peripheral: USBPHY, signal: DM, pin_signal: USB1_DM, identifier: K28_MICRO_USB_DM_PHY}
  - {pin_num: J1, peripheral: USBPHY, signal: DP, pin_signal: USB1_DP, identifier: K28_MICRO_USB_DP_PHY}
  - {pin_num: J2, peripheral: USBPHY, signal: VBUS, pin_signal: USB1_VBUS}
  - {pin_num: M11, peripheral: USBPHY, signal: ID, pin_signal: PTA11/LLWU_P23/I2C2_SCL/FTM2_CH1/FXIO0_D17/FTM2_QD_PHB/TPM2_CH1/USB1_ID, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: K8, peripheral: USB0, signal: CLKIN, pin_signal: PTA22/LPUART4_CTS_b/FXIO0_D6/RTC_CLKOUT/USB0_CLKIN, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitUSBPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitUSBPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    const port_pin_config_t USB_ID = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Fast slew rate is configured */
                                      kPORT_FastSlewRate,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Open drain is disabled */
                                      kPORT_OpenDrainDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as USB1_ID */
                                      kPORT_MuxAlt7,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTA11 (pin M11) is configured as USB1_ID */
    PORT_SetPinConfig(BOARD_USB_ID_PORT, BOARD_USB_ID_PIN, &USB_ID);

    const port_pin_config_t USB0_CLKIN = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as USB0_CLKIN */
                                          kPORT_MuxAlt7,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA22 (pin K8) is configured as USB0_CLKIN */
    PORT_SetPinConfig(BOARD_USB0_CLKIN_PORT, BOARD_USB0_CLKIN_PIN, &USB0_CLKIN);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDHC0Pins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: H11, peripheral: SDHC, signal: 'D, 2', pin_signal: PTA29/LPUART3_RX/SDHC0_D2/FB_A24/I2S1_RXD0, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: H12, peripheral: SDHC, signal: 'D, 3', pin_signal: PTA28/LPUART3_TX/SDHC0_D3/FB_A25/I2S1_RXD1, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: J11, peripheral: SDHC, signal: 'D, 0', pin_signal: PTA25/LPUART2_RX/SDHC0_D0/FB_A14/SDRAM_D14/FB_A28/I2S1_TX_FS, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: K11, peripheral: SDHC, signal: 'D, 1', pin_signal: PTA24/LPUART2_TX/SDHC0_D1/FB_A15/SDRAM_D15/FB_A29/I2S1_TX_BCLK, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: J10, peripheral: SDHC, signal: DCLK, pin_signal: PTA26/LPUART2_CTS_b/SDHC0_DCLK/FB_A13/SDRAM_D13/FB_A27/I2S1_TXD0, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: H13, peripheral: SDHC, signal: CMD, pin_signal: PTA27/LPUART2_RTS_b/SDHC0_CMD/FB_A12/SDRAM_D12/FB_A26/I2S1_TXD1, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: F13, peripheral: GPIOB, signal: 'GPIO, 5', pin_signal: PTB5/FTM2_FLT0, direction: INPUT, slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDHC0Pins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSDHC0Pins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    gpio_pin_config_t SDCARD_CARD_DETECTION_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB5 (pin F13)  */
    GPIO_PinInit(BOARD_SDCARD_CARD_DETECTION_GPIO, BOARD_SDCARD_CARD_DETECTION_PIN, &SDCARD_CARD_DETECTION_config);

    const port_pin_config_t SDHC0_D1 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D1 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA24 (pin K11) is configured as SDHC0_D1 */
    PORT_SetPinConfig(BOARD_SDHC0_D1_PORT, BOARD_SDHC0_D1_PIN, &SDHC0_D1);

    const port_pin_config_t SDHC0_D0 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D0 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA25 (pin J11) is configured as SDHC0_D0 */
    PORT_SetPinConfig(BOARD_SDHC0_D0_PORT, BOARD_SDHC0_D0_PIN, &SDHC0_D0);

    const port_pin_config_t SDHC0_DCLK = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as SDHC0_DCLK */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA26 (pin J10) is configured as SDHC0_DCLK */
    PORT_SetPinConfig(BOARD_SDHC0_DCLK_PORT, BOARD_SDHC0_DCLK_PIN, &SDHC0_DCLK);

    const port_pin_config_t SDHC0_CMD = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDHC0_CMD */
                                         kPORT_MuxAlt4,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTA27 (pin H13) is configured as SDHC0_CMD */
    PORT_SetPinConfig(BOARD_SDHC0_CMD_PORT, BOARD_SDHC0_CMD_PIN, &SDHC0_CMD);

    const port_pin_config_t SDHC0_D3 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D3 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA28 (pin H12) is configured as SDHC0_D3 */
    PORT_SetPinConfig(BOARD_SDHC0_D3_PORT, BOARD_SDHC0_D3_PIN, &SDHC0_D3);

    const port_pin_config_t SDHC0_D2 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D2 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA29 (pin H11) is configured as SDHC0_D2 */
    PORT_SetPinConfig(BOARD_SDHC0_D2_PORT, BOARD_SDHC0_D2_PIN, &SDHC0_D2);

    const port_pin_config_t SDCARD_CARD_DETECTION = {/* Internal pull-up resistor is enabled */
                                                     kPORT_PullUp,
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
    /* PORTB5 (pin F13) is configured as PTB5 */
    PORT_SetPinConfig(BOARD_SDCARD_CARD_DETECTION_PORT, BOARD_SDCARD_CARD_DETECTION_PIN, &SDCARD_CARD_DETECTION);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_Init_visible_lightPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: N4, peripheral: ADC0, signal: 'SE, 16', pin_signal: ADC0_SE16}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_Init_visible_lightPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_Init_visible_lightPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDRAMPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B10, peripheral: SDRAM, signal: A16, pin_signal: CMP0_IN1/PTC7/SPI0_SIN/USB0_SOF_OUT/I2S0_RX_FS/FB_AD8/SDRAM_A16/FXIO0_D15, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: C10, peripheral: SDRAM, signal: A15, pin_signal: CMP0_IN2/PTC8/FTM3_CH4/I2S0_MCLK/FB_AD7/SDRAM_A15/FXIO0_D16, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: C9, peripheral: SDRAM, signal: A14, pin_signal: CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0/FXIO0_D17, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: A8, peripheral: SDRAM, signal: A13, pin_signal: PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13/FXIO0_D18, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: A4, peripheral: SDRAM, signal: A12, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/LPUART2_RX/FTM3_CH2/FB_AD4/SDRAM_A12/I2C0_SCL, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: B4, peripheral: SDRAM, signal: A11, pin_signal: PTD3/SPI0_SIN/LPUART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: B5, peripheral: SDRAM, signal: A10, pin_signal: PTD4/LLWU_P14/SPI0_PCS1/LPUART0_RTS_b/FTM0_CH4/FB_AD2/SDRAM_A10/EWM_IN/SPI1_PCS0, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: C4, peripheral: SDRAM, signal: A9, pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/LPUART0_CTS_b/FTM0_CH5/FB_AD1/SDRAM_A9/EWM_OUT_b/SPI1_SCK, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: A11, peripheral: SDRAM, signal: A18, pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/LPTMR1_ALT2/I2S0_RXD0/FB_AD10/SDRAM_A18/CMP0_OUT/FTM0_CH2, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: B11, peripheral: SDRAM, signal: A19, pin_signal: PTC4/LLWU_P8/SPI0_PCS0/LPUART1_TX/FTM0_CH3/FB_AD11/SDRAM_A19/CMP1_OUT, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: A13, peripheral: SDRAM, signal: A20, pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/LPUART1_CTS_b/FTM0_CH1/FB_AD12/SDRAM_A20/I2S0_TX_FS, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: B12, peripheral: SDRAM, signal: A21, pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/LPUART1_RTS_b/FTM0_CH0/FB_AD13/SDRAM_A21/I2S0_TXD0/FXIO0_D13, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: B13, peripheral: SDRAM, signal: A22, pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/USB0_SOF_OUT/FB_AD14/SDRAM_A22/I2S0_TXD1/FXIO0_D12, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D12, peripheral: SDRAM, signal: A23, pin_signal: PTB18/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/SDRAM_A23/FTM2_QD_PHA/TPM2_CH0/FXIO0_D6, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: G12, peripheral: SDRAM, signal: RAS, pin_signal: ADC0_SE9/PTB1/I2C0_SDA/FTM1_CH1/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1/FXIO0_D1, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: G13, peripheral: SDRAM, signal: CAS, pin_signal: ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0/FXIO0_D0, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: G11, peripheral: SDRAM, signal: WE, pin_signal: ADC0_SE12/PTB2/I2C0_SCL/LPUART0_RTS_b/SDRAM_WE_b/FTM0_FLT3/FXIO0_D2, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: G10, peripheral: SDRAM, signal: CS0, pin_signal: ADC0_SE13/PTB3/I2C0_SDA/LPUART0_CTS_b/SDRAM_CS0_b/FTM0_FLT0/FXIO0_D3, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E7, peripheral: SDRAM, signal: DQM3, pin_signal: PTC17/LPUART3_TX/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b/SDRAM_DQM3, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E8, peripheral: SDRAM, signal: DQM2, pin_signal: PTC16/LPUART3_RX/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b/SDRAM_DQM2, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: A12, peripheral: SDRAM, signal: CLKOUT, pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/LPUART1_RX/FTM0_CH2/CLKOUT/I2S0_TX_BCLK, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: E5, peripheral: SDRAM, signal: CKE, pin_signal: PTD7/CMT_IRO/LPUART0_TX/FTM0_CH7/SDRAM_CKE/FTM0_FLT1/SPI1_SIN, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: D10, peripheral: SDRAM, signal: D31, pin_signal: PTB20/SPI2_PCS0/FB_AD31/SDRAM_D31/CMP0_OUT/FXIO0_D8, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: D9, peripheral: SDRAM, signal: D30, pin_signal: PTB21/SPI2_SCK/FB_AD30/SDRAM_D30/CMP1_OUT/FXIO0_D9, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: D13, peripheral: SDRAM, signal: D16, pin_signal: PTB17/SPI1_SIN/LPUART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: F8, peripheral: SDRAM, signal: D17, pin_signal: PTB16/SPI1_SOUT/LPUART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E13, peripheral: SDRAM, signal: D18, pin_signal: PTB11/SPI1_SCK/LPUART3_TX/I2C2_SDA/FB_AD18/SDRAM_D18/FTM0_FLT2/FXIO0_D5, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: G9, peripheral: SDRAM, signal: D19, pin_signal: PTB10/SPI1_PCS0/LPUART3_RX/I2C2_SCL/FB_AD19/SDRAM_D19/FTM0_FLT1/FXIO0_D4, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: F9, peripheral: SDRAM, signal: D20, pin_signal: PTB9/SPI1_PCS1/LPUART3_CTS_b/FB_AD20/SDRAM_D20, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: F10, peripheral: SDRAM, signal: D21, pin_signal: PTB8/LPUART3_RTS_b/FB_AD21/SDRAM_D21, slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: F11, peripheral: SDRAM, signal: D22, pin_signal: PTB7/FB_AD22/SDRAM_D22, slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: F12, peripheral: SDRAM, signal: D23, pin_signal: PTB6/FB_AD23/SDRAM_D23, slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D8, peripheral: SDRAM, signal: D24, pin_signal: PTC15/LPUART4_TX/FB_AD24/SDRAM_D24/FXIO0_D21, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: C8, peripheral: SDRAM, signal: D25, pin_signal: PTC14/LPUART4_RX/FB_AD25/SDRAM_D25/FXIO0_D20, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: B8, peripheral: SDRAM, signal: D26, pin_signal: PTC13/LPUART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: B9, peripheral: SDRAM, signal: D27, pin_signal: PTC12/LPUART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: C12, peripheral: SDRAM, signal: D28, pin_signal: PTB23/SPI2_SIN/SPI0_PCS5/FB_AD28/SDRAM_D28/FXIO0_D11, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: C13, peripheral: SDRAM, signal: D29, pin_signal: PTB22/SPI2_SOUT/FB_AD29/SDRAM_D29/FXIO0_D10, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDRAMPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSDRAMPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    const port_pin_config_t SDRAM_CAS_b = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as SDRAM_CAS_b */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTB0 (pin G13) is configured as SDRAM_CAS_b */
    PORT_SetPinConfig(BOARD_SDRAM_CAS_b_PORT, BOARD_SDRAM_CAS_b_PIN, &SDRAM_CAS_b);

    const port_pin_config_t SDRAM_RAS_b = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as SDRAM_RAS_b */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTB1 (pin G12) is configured as SDRAM_RAS_b */
    PORT_SetPinConfig(BOARD_SDRAM_RAS_b_PORT, BOARD_SDRAM_RAS_b_PIN, &SDRAM_RAS_b);

    const port_pin_config_t SDRAM_D19 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D19 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB10 (pin G9) is configured as SDRAM_D19 */
    PORT_SetPinConfig(BOARD_SDRAM_D19_PORT, BOARD_SDRAM_D19_PIN, &SDRAM_D19);

    const port_pin_config_t SDRAM_D18 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D18 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB11 (pin E13) is configured as SDRAM_D18 */
    PORT_SetPinConfig(BOARD_SDRAM_D18_PORT, BOARD_SDRAM_D18_PIN, &SDRAM_D18);

    const port_pin_config_t SDRAM_D17 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D17 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB16 (pin F8) is configured as SDRAM_D17 */
    PORT_SetPinConfig(BOARD_SDRAM_D17_PORT, BOARD_SDRAM_D17_PIN, &SDRAM_D17);

    const port_pin_config_t SDRAM_D16 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D16 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB17 (pin D13) is configured as SDRAM_D16 */
    PORT_SetPinConfig(BOARD_SDRAM_D16_PORT, BOARD_SDRAM_D16_PIN, &SDRAM_D16);

    const port_pin_config_t SDRAM_A23 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A23 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB18 (pin D12) is configured as SDRAM_A23 */
    PORT_SetPinConfig(BOARD_SDRAM_A23_PORT, BOARD_SDRAM_A23_PIN, &SDRAM_A23);

    const port_pin_config_t SDRAM_WE_b = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as SDRAM_WE_b */
                                          kPORT_MuxAlt5,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTB2 (pin G11) is configured as SDRAM_WE_b */
    PORT_SetPinConfig(BOARD_SDRAM_WE_b_PORT, BOARD_SDRAM_WE_b_PIN, &SDRAM_WE_b);

    const port_pin_config_t SDRAM_D31 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D31 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB20 (pin D10) is configured as SDRAM_D31 */
    PORT_SetPinConfig(BOARD_SDRAM_D31_PORT, BOARD_SDRAM_D31_PIN, &SDRAM_D31);

    const port_pin_config_t SDRAM_D30 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D30 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB21 (pin D9) is configured as SDRAM_D30 */
    PORT_SetPinConfig(BOARD_SDRAM_D30_PORT, BOARD_SDRAM_D30_PIN, &SDRAM_D30);

    const port_pin_config_t SDRAM_D29 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D29 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB22 (pin C13) is configured as SDRAM_D29 */
    PORT_SetPinConfig(BOARD_SDRAM_D29_PORT, BOARD_SDRAM_D29_PIN, &SDRAM_D29);

    const port_pin_config_t SDRAM_D28 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D28 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB23 (pin C12) is configured as SDRAM_D28 */
    PORT_SetPinConfig(BOARD_SDRAM_D28_PORT, BOARD_SDRAM_D28_PIN, &SDRAM_D28);

    const port_pin_config_t SDRAM_CS0_b = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as SDRAM_CS0_b */
                                           kPORT_MuxAlt5,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTB3 (pin G10) is configured as SDRAM_CS0_b */
    PORT_SetPinConfig(BOARD_SDRAM_CS0_b_PORT, BOARD_SDRAM_CS0_b_PIN, &SDRAM_CS0_b);

    const port_pin_config_t SDRAM_D23 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D23 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB6 (pin F12) is configured as SDRAM_D23 */
    PORT_SetPinConfig(BOARD_SDRAM_D23_PORT, BOARD_SDRAM_D23_PIN, &SDRAM_D23);

    const port_pin_config_t SDRAM_D22 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D22 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB7 (pin F11) is configured as SDRAM_D22 */
    PORT_SetPinConfig(BOARD_SDRAM_D22_PORT, BOARD_SDRAM_D22_PIN, &SDRAM_D22);

    const port_pin_config_t SDRAM_D21 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D21 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB8 (pin F10) is configured as SDRAM_D21 */
    PORT_SetPinConfig(BOARD_SDRAM_D21_PORT, BOARD_SDRAM_D21_PIN, &SDRAM_D21);

    const port_pin_config_t SDRAM_D20 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D20 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB9 (pin F9) is configured as SDRAM_D20 */
    PORT_SetPinConfig(BOARD_SDRAM_D20_PORT, BOARD_SDRAM_D20_PIN, &SDRAM_D20);

    const port_pin_config_t SDRAM_A22 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A22 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC0 (pin B13) is configured as SDRAM_A22 */
    PORT_SetPinConfig(BOARD_SDRAM_A22_PORT, BOARD_SDRAM_A22_PIN, &SDRAM_A22);

    const port_pin_config_t SDRAM_A21 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A21 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC1 (pin B12) is configured as SDRAM_A21 */
    PORT_SetPinConfig(BOARD_SDRAM_A21_PORT, BOARD_SDRAM_A21_PIN, &SDRAM_A21);

    const port_pin_config_t SDRAM_A13 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A13 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC10 (pin A8) is configured as SDRAM_A13 */
    PORT_SetPinConfig(BOARD_SDRAM_A13_PORT, BOARD_SDRAM_A13_PIN, &SDRAM_A13);

    const port_pin_config_t SDRAM_D27 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D27 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC12 (pin B9) is configured as SDRAM_D27 */
    PORT_SetPinConfig(BOARD_SDRAM_D27_PORT, BOARD_SDRAM_D27_PIN, &SDRAM_D27);

    const port_pin_config_t SDRAM_D26 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D26 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC13 (pin B8) is configured as SDRAM_D26 */
    PORT_SetPinConfig(BOARD_SDRAM_D26_PORT, BOARD_SDRAM_D26_PIN, &SDRAM_D26);

    const port_pin_config_t SDRAM_D25 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D25 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC14 (pin C8) is configured as SDRAM_D25 */
    PORT_SetPinConfig(BOARD_SDRAM_D25_PORT, BOARD_SDRAM_D25_PIN, &SDRAM_D25);

    const port_pin_config_t SDRAM_D24 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_D24 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC15 (pin D8) is configured as SDRAM_D24 */
    PORT_SetPinConfig(BOARD_SDRAM_D24_PORT, BOARD_SDRAM_D24_PIN, &SDRAM_D24);

    const port_pin_config_t SDRAM_DQM2 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as SDRAM_DQM2 */
                                          kPORT_MuxAlt5,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC16 (pin E8) is configured as SDRAM_DQM2 */
    PORT_SetPinConfig(BOARD_SDRAM_DQM2_PORT, BOARD_SDRAM_DQM2_PIN, &SDRAM_DQM2);

    const port_pin_config_t SDRAM_DQM3 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as SDRAM_DQM3 */
                                          kPORT_MuxAlt5,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC17 (pin E7) is configured as SDRAM_DQM3 */
    PORT_SetPinConfig(BOARD_SDRAM_DQM3_PORT, BOARD_SDRAM_DQM3_PIN, &SDRAM_DQM3);

    const port_pin_config_t SDRAM_A20 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A20 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC2 (pin A13) is configured as SDRAM_A20 */
    PORT_SetPinConfig(BOARD_SDRAM_A20_PORT, BOARD_SDRAM_A20_PIN, &SDRAM_A20);

    const port_pin_config_t CLKOUT = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Fast slew rate is configured */
                                      kPORT_FastSlewRate,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Open drain is disabled */
                                      kPORT_OpenDrainDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as CLKOUT */
                                      kPORT_MuxAlt5,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTC3 (pin A12) is configured as CLKOUT */
    PORT_SetPinConfig(BOARD_CLKOUT_PORT, BOARD_CLKOUT_PIN, &CLKOUT);

    const port_pin_config_t SDRAM_A19 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A19 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC4 (pin B11) is configured as SDRAM_A19 */
    PORT_SetPinConfig(BOARD_SDRAM_A19_PORT, BOARD_SDRAM_A19_PIN, &SDRAM_A19);

    const port_pin_config_t SDRAM_A18 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A18 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC5 (pin A11) is configured as SDRAM_A18 */
    PORT_SetPinConfig(BOARD_SDRAM_A18_PORT, BOARD_SDRAM_A18_PIN, &SDRAM_A18);

    const port_pin_config_t SDRAM_A16 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A16 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC7 (pin B10) is configured as SDRAM_A16 */
    PORT_SetPinConfig(BOARD_SDRAM_A16_PORT, BOARD_SDRAM_A16_PIN, &SDRAM_A16);

    const port_pin_config_t SDRAM_A15 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A15 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC8 (pin C10) is configured as SDRAM_A15 */
    PORT_SetPinConfig(BOARD_SDRAM_A15_PORT, BOARD_SDRAM_A15_PIN, &SDRAM_A15);

    const port_pin_config_t SDRAM_A14 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A14 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTC9 (pin C9) is configured as SDRAM_A14 */
    PORT_SetPinConfig(BOARD_SDRAM_A14_PORT, BOARD_SDRAM_A14_PIN, &SDRAM_A14);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_2_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_3_MASK
            /* Digital filter is configured for PORTD2 */
            | PORT_DFER_DFE_4_MASK
            /* Digital filter is configured for PORTD3 */
            | PORT_DFER_DFE_5_MASK
            /* Digital filter is configured for PORTD4 */
            | PORT_DFER_DFE_7_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t SDRAM_A12 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A12 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD2 (pin A4) is configured as SDRAM_A12 */
    PORT_SetPinConfig(BOARD_SDRAM_A12_PORT, BOARD_SDRAM_A12_PIN, &SDRAM_A12);

    const port_pin_config_t SDRAM_A11 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A11 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD3 (pin B4) is configured as SDRAM_A11 */
    PORT_SetPinConfig(BOARD_SDRAM_A11_PORT, BOARD_SDRAM_A11_PIN, &SDRAM_A11);

    const port_pin_config_t SDRAM_A10 = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_A10 */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD4 (pin B5) is configured as SDRAM_A10 */
    PORT_SetPinConfig(BOARD_SDRAM_A10_PORT, BOARD_SDRAM_A10_PIN, &SDRAM_A10);

    const port_pin_config_t SDRAM_A9 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDRAM_A9 */
                                        kPORT_MuxAlt5,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTD5 (pin C4) is configured as SDRAM_A9 */
    PORT_SetPinConfig(BOARD_SDRAM_A9_PORT, BOARD_SDRAM_A9_PIN, &SDRAM_A9);

    const port_pin_config_t SDRAM_CKE = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDRAM_CKE */
                                         kPORT_MuxAlt5,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTD7 (pin E5) is configured as SDRAM_CKE */
    PORT_SetPinConfig(BOARD_SDRAM_CKE_PORT, BOARD_SDRAM_CKE_PIN, &SDRAM_CKE);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
