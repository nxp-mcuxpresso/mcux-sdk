/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#define PORT_DFER_DFE_0_MASK 0x01u /*!<@brief Digital Filter Enable Mask for item 0. */

/*! @name PORTA4 (coord L9), SW2
  @{ */
#define BOARD_SW2_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SW2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SW2_PIN 4U     /*!<@brief PORTA pin index: 4 */
                             /* @} */

/*! @name PORTD0 (coord A6), SW3
  @{ */
#define BOARD_SW3_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SW3_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SW3_PIN 0U     /*!<@brief PORTD pin index: 0 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitButtonsPins(void);

/*! @name PORTA18 (coord N13), Y2[1]/EXTAL
  @{ */
#define BOARD_EXTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_EXTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                /* @} */

/*! @name PORTA19 (coord M13), Y2[3]/XTAL
  @{ */
#define BOARD_XTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_XTAL0_PIN 19U    /*!<@brief PORTA pin index: 19 */
                               /* @} */

/*! @name XTAL32 (coord N5), Y1[1]/XTAL32_RTC
  @{ */
/* @} */

/*! @name EXTAL32 (coord N6), Y1[2]/EXTAL32_RTC
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCPins(void);

/*! @name PORTE6 (coord E2), J1[7]/D1[1]/LEDRGB_RED
  @{ */
#define BOARD_LED_RED_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_RED_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_RED_PIN 6U     /*!<@brief PORTE pin index: 6 */
                                 /* @} */

/*! @name PORTE7 (coord E3), J1[15]/D1[4]/LEDRGB_GREEN
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_GREEN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_GREEN_PIN 7U     /*!<@brief PORTE pin index: 7 */
                                   /* @} */

/*! @name PORTE8 (coord E4), J1[13]/D1[3]/LEDRGB_BLUE
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_BLUE_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_BLUE_PIN 8U     /*!<@brief PORTE pin index: 8 */
                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART0 receive data source select: LPUART0_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 transmit data source select: LPUART0_TX pin */

/*! @name PORTC24 (coord B7), LPUART0_TX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_DEBUG_UART_TX_PIN 24U    /*!<@brief PORTC pin index: 24 */
                                       /* @} */

/*! @name PORTC25 (coord A7), LPUART0_RX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_DEBUG_UART_RX_PIN 25U    /*!<@brief PORTC pin index: 25 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name PORTC29 (coord B6), U6[4]/I2C_SCL
  @{ */
#define BOARD_I2C_SCL_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_I2C_SCL_PIN 29U    /*!<@brief PORTC pin index: 29 */
                                 /* @} */

/*! @name PORTC28 (coord C6), U6[6]/I2C SDA
  @{ */
#define BOARD_I2C_SDA_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_I2C_SDA_PIN 28U    /*!<@brief PORTC pin index: 28 */
                                 /* @} */

/*! @name PORTC26 (coord E6), U6[11]/INT1_FXOS8700CQ_R
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT1_PIN 26U    /*!<@brief PORTC pin index: 26 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void);

/*! @name PORTE2 (coord C1), U11[5]/QSPIA_DATA0
  @{ */
#define BOARD_QSPIA_DATA0_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_DATA0_PIN 2U     /*!<@brief PORTE pin index: 2 */
                                     /* @} */

/*! @name PORTE4 (coord E1), U11[2]/QSPIA_DATA1
  @{ */
#define BOARD_QSPIA_DATA1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_DATA1_PIN 4U     /*!<@brief PORTE pin index: 4 */
                                     /* @} */

/*! @name PORTE3 (coord D1), U11[3]/QSPIA_DATA2
  @{ */
#define BOARD_QSPIA_DATA2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_DATA2_PIN 3U     /*!<@brief PORTE pin index: 3 */
                                     /* @} */

/*! @name PORTE0 (coord A1), U11[7]/QSPIA_DATA3
  @{ */
#define BOARD_QSPIA_DATA3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_DATA3_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                     /* @} */

/*! @name PORTE1 (coord B1), U11[6]/QSPIA_SCLK
  @{ */
#define BOARD_QSPIA_SCLK_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_SCLK_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                    /* @} */

/*! @name PORTE5 (coord D2), U11[1]/QSPIA_SS
  @{ */
#define BOARD_QSPIA_SS_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_QSPIA_SS_PIN 5U     /*!<@brief PORTE pin index: 5 */
                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitQSPI_FLASHPins(void);

/*! @name USB1_DM (coord H1), J24[2]USB_CONN_DN
  @{ */
/* @} */

/*! @name USB1_DP (coord J1), J24[3]USB_CONN_DP
  @{ */
/* @} */

/*! @name USB1_VBUS (coord J2), J24[1]P5V0_USB_CONN_VBUS
  @{ */
/* @} */

/*! @name PORTA11 (coord M11), J24[4]TC_USB_ID
  @{ */
#define BOARD_USB_ID_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_USB_ID_PIN 11U    /*!<@brief PORTA pin index: 11 */
                                /* @} */

/*! @name PORTA22 (coord K8), J27[7]/FXIO0_D6/PCLK
  @{ */
#define BOARD_USB0_CLKIN_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_USB0_CLKIN_PIN 22U    /*!<@brief PORTA pin index: 22 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBPins(void);

/*! @name PORTA29 (coord H11), J19[P1]/SDHC0_D2
  @{ */
#define BOARD_SDHC0_D2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_D2_PIN 29U    /*!<@brief PORTA pin index: 29 */
                                  /* @} */

/*! @name PORTA28 (coord H12), J19[P2]/SDHC0_D3
  @{ */
#define BOARD_SDHC0_D3_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_D3_PIN 28U    /*!<@brief PORTA pin index: 28 */
                                  /* @} */

/*! @name PORTA25 (coord J11), J19[P7]/SDHC0_D0
  @{ */
#define BOARD_SDHC0_D0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_D0_PIN 25U    /*!<@brief PORTA pin index: 25 */
                                  /* @} */

/*! @name PORTA24 (coord K11), J19[P8]/SDHC0_D1
  @{ */
#define BOARD_SDHC0_D1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_D1_PIN 24U    /*!<@brief PORTA pin index: 24 */
                                  /* @} */

/*! @name PORTA26 (coord J10), J19[P5]/SDHC0_DCLK
  @{ */
#define BOARD_SDHC0_DCLK_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_DCLK_PIN 26U    /*!<@brief PORTA pin index: 26 */
                                    /* @} */

/*! @name PORTA27 (coord H13), J19[P3]/SDHC0_CMD
  @{ */
#define BOARD_SDHC0_CMD_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SDHC0_CMD_PIN 27U    /*!<@brief PORTA pin index: 27 */
                                   /* @} */

/*! @name PORTB5 (coord F13), J19[G1]/SD_CARD_DETECT
  @{ */
#define BOARD_SDCARD_CARD_DETECTION_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_SDCARD_CARD_DETECTION_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDCARD_CARD_DETECTION_PIN 5U     /*!<@brief PORTB pin index: 5 */
                                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHC0Pins(void);

/*! @name ADC0_SE16 (coord N4), Q5[2]/LIGHT_SENSOR
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_Init_visible_lightPins(void);

#define PORT_DFER_DFE_2_MASK 0x04u /*!<@brief Digital Filter Enable Mask for item 2. */
#define PORT_DFER_DFE_3_MASK 0x08u /*!<@brief Digital Filter Enable Mask for item 3. */
#define PORT_DFER_DFE_4_MASK 0x10u /*!<@brief Digital Filter Enable Mask for item 4. */
#define PORT_DFER_DFE_5_MASK 0x20u /*!<@brief Digital Filter Enable Mask for item 5. */
#define PORT_DFER_DFE_7_MASK 0x80u /*!<@brief Digital Filter Enable Mask for item 7. */

/*! @name PORTC7 (coord B10), U13[H7]/SDRAM_A16
  @{ */
#define BOARD_SDRAM_A16_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A16_PIN 7U     /*!<@brief PORTC pin index: 7 */
                                   /* @} */

/*! @name PORTC8 (coord C10), U13[H8]/SDRAM_A15
  @{ */
#define BOARD_SDRAM_A15_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A15_PIN 8U     /*!<@brief PORTC pin index: 8 */
                                   /* @} */

/*! @name PORTC9 (coord C9), U13[J8]/SDRAM_A14
  @{ */
#define BOARD_SDRAM_A14_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A14_PIN 9U     /*!<@brief PORTC pin index: 9 */
                                   /* @} */

/*! @name PORTC10 (coord A8), U13[J7]/SDRAM_A13
  @{ */
#define BOARD_SDRAM_A13_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A13_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                   /* @} */

/*! @name PORTD2 (coord A4), U13[J3]/SDRAM_A12
  @{ */
#define BOARD_SDRAM_A12_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDRAM_A12_PIN 2U     /*!<@brief PORTD pin index: 2 */
                                   /* @} */

/*! @name PORTD3 (coord B4), U13[J2]/SDRAM_A11
  @{ */
#define BOARD_SDRAM_A11_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDRAM_A11_PIN 3U     /*!<@brief PORTD pin index: 3 */
                                   /* @} */

/*! @name PORTD4 (coord B5), U13[H3]/SDRAM_A10
  @{ */
#define BOARD_SDRAM_A10_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDRAM_A10_PIN 4U     /*!<@brief PORTD pin index: 4 */
                                   /* @} */

/*! @name PORTD5 (coord C4), U13[H2]/SDRAM_A9
  @{ */
#define BOARD_SDRAM_A9_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDRAM_A9_PIN 5U     /*!<@brief PORTD pin index: 5 */
                                  /* @} */

/*! @name PORTC5 (coord A11), U13[H1]/SDRAM_A18
  @{ */
#define BOARD_SDRAM_A18_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A18_PIN 5U     /*!<@brief PORTC pin index: 5 */
                                   /* @} */

/*! @name PORTC4 (coord B11), U13[G3]/SDRAM_A19
  @{ */
#define BOARD_SDRAM_A19_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A19_PIN 4U     /*!<@brief PORTC pin index: 4 */
                                   /* @} */

/*! @name PORTC2 (coord A13), U13[H9]/SDRAM_A20
  @{ */
#define BOARD_SDRAM_A20_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A20_PIN 2U     /*!<@brief PORTC pin index: 2 */
                                   /* @} */

/*! @name PORTC1 (coord B12), U13[G2]/SDRAM_A21
  @{ */
#define BOARD_SDRAM_A21_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A21_PIN 1U     /*!<@brief PORTC pin index: 1 */
                                   /* @} */

/*! @name PORTC0 (coord B13), U13[G7]/SDRAM_A22
  @{ */
#define BOARD_SDRAM_A22_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_A22_PIN 0U     /*!<@brief PORTC pin index: 0 */
                                   /* @} */

/*! @name PORTB18 (coord D12), U13[G8]/SDRAM_A23
  @{ */
#define BOARD_SDRAM_A23_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_A23_PIN 18U    /*!<@brief PORTB pin index: 18 */
                                   /* @} */

/*! @name PORTB1 (coord G12), U13[F8]/SDRAM_RAS_b
  @{ */
#define BOARD_SDRAM_RAS_b_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_RAS_b_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                     /* @} */

/*! @name PORTB0 (coord G13), U13[F7]/SDRAM_CAS_b
  @{ */
#define BOARD_SDRAM_CAS_b_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_CAS_b_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                     /* @} */

/*! @name PORTB2 (coord G11), U13[F9]/SDRAM_WE_b
  @{ */
#define BOARD_SDRAM_WE_b_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_WE_b_PIN 2U     /*!<@brief PORTB pin index: 2 */
                                    /* @} */

/*! @name PORTB3 (coord G10), U13[G9]/SDRAM_CS0_b
  @{ */
#define BOARD_SDRAM_CS0_b_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_CS0_b_PIN 3U     /*!<@brief PORTB pin index: 3 */
                                     /* @} */

/*! @name PORTC17 (coord E7), U13[F1]/SDRAM_DQM3
  @{ */
#define BOARD_SDRAM_DQM3_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_DQM3_PIN 17U    /*!<@brief PORTC pin index: 17 */
                                    /* @} */

/*! @name PORTC16 (coord E8), U13[E8]/SDRAM_DQM2
  @{ */
#define BOARD_SDRAM_DQM2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_DQM2_PIN 16U    /*!<@brief PORTC pin index: 16 */
                                    /* @} */

/*! @name PORTC3 (coord A12), U13[F2]/CLKOUT
  @{ */
#define BOARD_CLKOUT_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_CLKOUT_PIN 3U     /*!<@brief PORTC pin index: 3 */
                                /* @} */

/*! @name PORTD7 (coord E5), U13[F3]/SDRAM_CKE
  @{ */
#define BOARD_SDRAM_CKE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDRAM_CKE_PIN 7U     /*!<@brief PORTD pin index: 7 */
                                   /* @} */

/*! @name PORTB20 (coord D10), U13[A2]/SDRAM_D31
  @{ */
#define BOARD_SDRAM_D31_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D31_PIN 20U    /*!<@brief PORTB pin index: 20 */
                                   /* @} */

/*! @name PORTB21 (coord D9), U13[B1]/SDRAM_D30
  @{ */
#define BOARD_SDRAM_D30_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D30_PIN 21U    /*!<@brief PORTB pin index: 21 */
                                   /* @} */

/*! @name PORTB17 (coord D13), U13[A8]/SDRAM_D16
  @{ */
#define BOARD_SDRAM_D16_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D16_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                   /* @} */

/*! @name PORTB16 (coord F8), U13[B9]/SDRAM_D17
  @{ */
#define BOARD_SDRAM_D17_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D17_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                   /* @} */

/*! @name PORTB11 (coord E13), U13[B8]/SDRAM_D18
  @{ */
#define BOARD_SDRAM_D18_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D18_PIN 11U    /*!<@brief PORTB pin index: 11 */
                                   /* @} */

/*! @name PORTB10 (coord G9), U13[C9]/SDRAM_D19
  @{ */
#define BOARD_SDRAM_D19_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D19_PIN 10U    /*!<@brief PORTB pin index: 10 */
                                   /* @} */

/*! @name PORTB9 (coord F9), U13[C8]/SDRAM_D20
  @{ */
#define BOARD_SDRAM_D20_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D20_PIN 9U     /*!<@brief PORTB pin index: 9 */
                                   /* @} */

/*! @name PORTB8 (coord F10), U13[D9]/SDRAM_D21
  @{ */
#define BOARD_SDRAM_D21_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D21_PIN 8U     /*!<@brief PORTB pin index: 8 */
                                   /* @} */

/*! @name PORTB7 (coord F11), U13[D8]/SDRAM_D22
  @{ */
#define BOARD_SDRAM_D22_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D22_PIN 7U     /*!<@brief PORTB pin index: 7 */
                                   /* @} */

/*! @name PORTB6 (coord F12), U13[E9]/SDRAM_D23
  @{ */
#define BOARD_SDRAM_D23_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D23_PIN 6U     /*!<@brief PORTB pin index: 6 */
                                   /* @} */

/*! @name PORTC15 (coord D8), U13[E1]/SDRAM_D24
  @{ */
#define BOARD_SDRAM_D24_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_D24_PIN 15U    /*!<@brief PORTC pin index: 15 */
                                   /* @} */

/*! @name PORTC14 (coord C8), U13[D2]/SDRAM_D25
  @{ */
#define BOARD_SDRAM_D25_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_D25_PIN 14U    /*!<@brief PORTC pin index: 14 */
                                   /* @} */

/*! @name PORTC13 (coord B8), U13[D1]/SDRAM_D26
  @{ */
#define BOARD_SDRAM_D26_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_D26_PIN 13U    /*!<@brief PORTC pin index: 13 */
                                   /* @} */

/*! @name PORTC12 (coord B9), U13[C2]/SDRAM_D27
  @{ */
#define BOARD_SDRAM_D27_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SDRAM_D27_PIN 12U    /*!<@brief PORTC pin index: 12 */
                                   /* @} */

/*! @name PORTB23 (coord C12), U13[C1]/SDRAM_D28
  @{ */
#define BOARD_SDRAM_D28_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D28_PIN 23U    /*!<@brief PORTB pin index: 23 */
                                   /* @} */

/*! @name PORTB22 (coord C13), U13[B2]/SDRAM_D29
  @{ */
#define BOARD_SDRAM_D29_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SDRAM_D29_PIN 22U    /*!<@brief PORTB pin index: 22 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDRAMPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
