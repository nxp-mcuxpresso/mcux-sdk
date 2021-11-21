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

#define PORT_DFER_DFE_10_MASK 0x0400u   /*!<@brief Digital Filter Enable Mask for item 10. */
#define PORT_DFER_DFE_11_MASK 0x0800u   /*!<@brief Digital Filter Enable Mask for item 11. */
#define PORT_DFER_DFE_12_MASK 0x1000u   /*!<@brief Digital Filter Enable Mask for item 12. */
#define PORT_DFER_DFE_13_MASK 0x2000u   /*!<@brief Digital Filter Enable Mask for item 13. */
#define PORT_DFER_DFE_15_MASK 0x8000u   /*!<@brief Digital Filter Enable Mask for item 15. */
#define PORT_DFER_DFE_16_MASK 0x010000u /*!<@brief Digital Filter Enable Mask for item 16. */
#define PORT_DFER_DFE_5_MASK 0x20u      /*!<@brief Digital Filter Enable Mask for item 5. */

/*! @name PORTC12 (number 50), D8[C]/FTM3_CH6/LEDYL
  @{ */
#define BOARD_LED_YELLOW_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_YELLOW_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_YELLOW_PIN 12U    /*!<@brief PORTC pin index: 12 */
                                    /* @} */

/*! @name PORTC10 (number 52), D6[C]/FTM3_CH4/LEDRD
  @{ */
#define BOARD_LED_RED1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_RED1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_RED1_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                  /* @} */

/*! @name PORTC13 (number 49), D9[C]/FTM3_CH7/LEDOR
  @{ */
#define BOARD_LED_ORANGE_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_ORANGE_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_ORANGE_PIN 13U    /*!<@brief PORTC pin index: 13 */
                                    /* @} */

/*! @name PORTC11 (number 51), D7[C]/FTM3_CH5/LEDGR
  @{ */
#define BOARD_LED_GREEN1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_GREEN1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_GREEN1_PIN 11U    /*!<@brief PORTC pin index: 11 */
                                    /* @} */

/*! @name PORTB5 (number 27), J15[B57]/D5[3]/TRI_BL
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_LED_BLUE_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_LED_BLUE_PIN 5U     /*!<@brief PORTB pin index: 5 */
                                  /* @} */

/*! @name PORTD15 (number 22), J15[B60]/D5[4]/TRI_GR
  @{ */
#define BOARD_LED_GREEN2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_GREEN2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_GREEN2_PIN 15U    /*!<@brief PORTD pin index: 15 */
                                    /* @} */

/*! @name PORTD16 (number 21), J15[B59]/D5[1]/TRI_RED
  @{ */
#define BOARD_LED_RED2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_RED2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_RED2_PIN 16U    /*!<@brief PORTD pin index: 16 */
                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define PORT_DFER_DFE_3_MASK 0x08u /*!<@brief Digital Filter Enable Mask for item 3. */
#define PORT_DFER_DFE_6_MASK 0x40u /*!<@brief Digital Filter Enable Mask for item 6. */

/*! @name PORTD3 (number 70), J15[B9]/SW2/LPSPI1_PCS0
  @{ */
#define BOARD_SW2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SW2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SW2_PIN 3U     /*!<@brief PORTD pin index: 3 */
                             /* @} */

/*! @name PORTD6 (number 32), J15[A11]/SW3
  @{ */
#define BOARD_SW3_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SW3_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SW3_PIN 6U     /*!<@brief PORTD pin index: 6 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONSPins(void);

/*! @name PORTC2 (number 30), Y1[2]/XTAL32
  @{ */
#define BOARD_XTAL32_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_XTAL32_PIN 2U     /*!<@brief PORTC pin index: 2 */
                                /* @} */

/*! @name PORTC3 (number 29), Y1[1]/EXTAL32
  @{ */
#define BOARD_EXTAL32_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_EXTAL32_PIN 3U     /*!<@brief PORTC pin index: 3 */
                                 /* @} */

/*! @name PORTB6 (number 16), X2[1]/XTAL
  @{ */
#define BOARD_XTAL0_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_XTAL0_PIN 6U     /*!<@brief PORTB pin index: 6 */
                               /* @} */

/*! @name PORTB7 (number 15), J24[2]/EXTAL
  @{ */
#define BOARD_EXTAL0_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_EXTAL0_PIN 7U     /*!<@brief PORTB pin index: 7 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCPins(void);

#define PORT_DFER_DFE_15_MASK 0x8000u /*!<@brief Digital Filter Enable Mask for item 15. */
#define PORT_DFER_DFE_2_MASK 0x04u    /*!<@brief Digital Filter Enable Mask for item 2. */
#define PORT_DFER_DFE_3_MASK 0x08u    /*!<@brief Digital Filter Enable Mask for item 3. */

/*! @name PORTA3 (number 72), J15[A7]/U4[4]/LPI2C0_SCL
  @{ */
#define BOARD_ACCEL_I2C_SCL_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_ACCEL_I2C_SCL_PIN 3U     /*!<@brief PORTA pin index: 3 */
                                       /* @} */

/*! @name PORTA2 (number 73), J15[A8]/U4[6]/LPI2C0_SDA
  @{ */
#define BOARD_ACCEL_I2C_SDA_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_ACCEL_I2C_SDA_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                       /* @} */

/*! @name PORTC15 (number 45), U4[16]/FTM1_CH3/RST_FXOS8700CQ
  @{ */
#define BOARD_ACCEL_I2C_RST_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_I2C_RST_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_I2C_RST_PIN 15U    /*!<@brief PORTC pin index: 15 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void);

#define PORT_DFER_DFE_0_MASK 0x01u /*!<@brief Digital Filter Enable Mask for item 0. */
#define PORT_DFER_DFE_1_MASK 0x02u /*!<@brief Digital Filter Enable Mask for item 1. */

/*! @name PORTA0 (number 79), THER_A/ADC0_SE0
  @{ */
#define BOARD_THER_A_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_THER_A_PIN 0U     /*!<@brief PORTA pin index: 0 */
                                /* @} */

/*! @name PORTA1 (number 78), THER_B/ADC0_SE1
  @{ */
#define BOARD_THER_B_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_THER_B_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitTHERMISTORPins(void);

#define PORT_DFER_DFE_14_MASK 0x4000u /*!<@brief Digital Filter Enable Mask for item 14. */

/*! @name PORTC14 (number 46), J9[1]/ADC0_SE12/POT_5K
  @{ */
#define BOARD_POT_5K_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_POT_5K_PIN 14U    /*!<@brief PORTC pin index: 14 */
                                /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPOTPins(void);

#define PORT_DFER_DFE_14_MASK 0x4000u /*!<@brief Digital Filter Enable Mask for item 14. */
#define PORT_DFER_DFE_3_MASK 0x08u    /*!<@brief Digital Filter Enable Mask for item 3. */
#define PORT_DFER_DFE_6_MASK 0x40u    /*!<@brief Digital Filter Enable Mask for item 6. */
#define PORT_DFER_DFE_7_MASK 0x80u    /*!<@brief Digital Filter Enable Mask for item 7. */

/*! @name PORTC7 (number 80), J15[A42]/TP5/LPUART1_TX/IRTX
  @{ */
#define BOARD_IRTX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_IRTX_PIN 7U     /*!<@brief PORTC pin index: 7 */
                              /* @} */

/*! @name PORTE14 (number 17), TP4/IRRX
  @{ */
#define BOARD_IRRX_CMP_IN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_IRRX_CMP_IN_PIN 14U    /*!<@brief PORTE pin index: 14 */
                                     /* @} */

/*! @name PORTE3 (number 18), J15[A41]/PTC6/LPUART1_RX
  @{ */
#define BOARD_IRRX_CMP_OUT_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_IRRX_CMP_OUT_PIN 3U     /*!<@brief PORTE pin index: 3 */
                                      /* @} */

/*! @name PORTC6 (number 81), J15[A41]/PTE3/LPUART1_RX
  @{ */
#define BOARD_IRRX_UART_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_IRRX_UART_PIN 6U     /*!<@brief PORTC pin index: 6 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitIRPins(void);

#define PORT_DFER_DFE_4_MASK 0x10u /*!<@brief Digital Filter Enable Mask for item 4. */
#define PORT_DFER_DFE_5_MASK 0x20u /*!<@brief Digital Filter Enable Mask for item 5. */

/*! @name PORTE5 (number 8), J6[2]/CAN0_TX
  @{ */
#define BOARD_CAN0_TX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_CAN0_TX_PIN 5U     /*!<@brief PORTE pin index: 5 */
                                 /* @} */

/*! @name PORTE4 (number 9), J7[2]/CAN0_RX
  @{ */
#define BOARD_CAN0_RX_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_CAN0_RX_PIN 4U     /*!<@brief PORTE pin index: 4 */
                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitCANPins(void);

#define PORT_DFER_DFE_0_MASK 0x01u /*!<@brief Digital Filter Enable Mask for item 0. */
#define PORT_DFER_DFE_1_MASK 0x02u /*!<@brief Digital Filter Enable Mask for item 1. */

/*! @name PORTB1 (number 53), J3[2]/LPUART0_TX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                       /* @} */

/*! @name PORTB0 (number 54), J5[2]/LPUART0_RX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

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
