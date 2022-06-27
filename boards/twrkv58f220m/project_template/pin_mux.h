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

/*! @name PORTA4 (number 54), SW2
  @{ */
#define BOARD_SW2_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SW2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SW2_PIN 4U     /*!<@brief PORTA pin index: 4 */
                             /* @} */

/*! @name PORTE4 (number 7), SW3
  @{ */
#define BOARD_SW3_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_SW3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SW3_PIN 4U     /*!<@brief PORTE pin index: 4 */
                             /* @} */

/*! @name PORTB5 (number 86), J15[D34]/J14[1]/SW4/ENET0_1588_TMR3
  @{ */
#define BOARD_SW4_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_SW4_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SW4_PIN 5U     /*!<@brief PORTB pin index: 5 */
                             /* @} */

/*! @name PORTB4 (number 85), J15[A63]/J14[3]/SW5/ENET0_1588_TMR2
  @{ */
#define BOARD_SW5_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_SW5_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_SW5_PIN 4U     /*!<@brief PORTB pin index: 4 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void);

/*! @name PORTE11 (number 14), J30[1]/LED_J_PTE11
  @{ */
#define BOARD_LED_RED_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_RED_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_RED_PIN 11U    /*!<@brief PORTE pin index: 11 */
                                 /* @} */

/*! @name PORTE12 (number 15), J30[3]/LED_J_PTE12
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_GREEN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_GREEN_PIN 12U    /*!<@brief PORTE pin index: 12 */
                                   /* @} */

/*! @name PORTE29 (number 37), J30[5]/LED_J_PTE29
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_BLUE_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_BLUE_PIN 29U    /*!<@brief PORTE pin index: 29 */
                                  /* @} */

/*! @name PORTE30 (number 38), J30[7]/LED_J_PTE30
  @{ */
#define BOARD_LED_ORANGE_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_ORANGE_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_ORANGE_PIN 30U    /*!<@brief PORTE pin index: 30 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define PORT_DFER_DFE_8_MASK 0x0100u /*!<@brief Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!<@brief Digital Filter Enable Mask for item 9. */

/*! @name PORTD9 (number 138), J15[A8]/U1[6]/I2C1_SDA
  @{ */
#define BOARD_I2C_SDA_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_I2C_SDA_PIN 9U     /*!<@brief PORTD pin index: 9 */
                                 /* @} */

/*! @name PORTD8 (number 137), J15[A7]/U1[4]/I2C1_SCL
  @{ */
#define BOARD_I2C_SCL_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_I2C_SCL_PIN 8U     /*!<@brief PORTD pin index: 8 */
                                 /* @} */

/*! @name PORTC18 (number 125), J15[D52]/U1[11]/INT1
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT1_PIN 18U    /*!<@brief PORTC pin index: 18 */
                                    /* @} */

/*! @name PORTC19 (number 126), U1[9]/INT2
  @{ */
#define BOARD_ACCEL_INT2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT2_PIN 19U    /*!<@brief PORTC pin index: 19 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void);

#define SOPT5_UART0RXSRC_UART_RX 0x00u /*!<@brief UART 0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB1 (number 82), J15[A44]/J31[5]/UART0_TX
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                       /* @} */

/*! @name PORTB0 (number 81), J15[A43]/J31[7]/UART0_RX
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name HSADC0A_CH12 (number 39), J4[1]/POT_5K
  @{ */
/* @} */

/*! @name VREFH (number 32), VDD_MCU
  @{ */
/* @} */

/*! @name VREFL (number 33), GND
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPOTPins(void);

/*!
 * @brief IEEE 1588 timestamp clock source select: External bypass clock (ENET_1588_CLKIN) */
#define SOPT2_TIMESRC_ENET 0x03u

/*! @name PORTA18 (number 72), Y1[3]/50MHz_OSC
  @{ */
#define BOARD_XTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_XTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                               /* @} */

/*! @name PORTE26 (number 47), J15[B47]/SPI0_PCS1
  @{ */
#define BOARD_ENET_1588_CLKIN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_ENET_1588_CLKIN_PIN 26U    /*!<@brief PORTE pin index: 26 */
                                         /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCPins(void);

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
