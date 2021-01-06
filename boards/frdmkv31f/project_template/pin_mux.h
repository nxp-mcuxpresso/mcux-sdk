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

/*! @name PORTA2 (number 36), J9[6]/TRACE_SWO
  @{ */
#define BOARD_TRACE_SWO_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_TRACE_SWO_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTE4 (number 5), SW3
  @{ */
#define BOARD_SW3_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_SW3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SW3_PIN 4U     /*!<@brief PORTE pin index: 4 */
                             /* @} */

/*! @name PORTA4 (number 38), SW2/NMI_b
  @{ */
#define BOARD_SW2_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SW2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SW2_PIN 4U     /*!<@brief PORTA pin index: 4 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void);

#define PORT_DFER_DFE_1_MASK 0x02u /*!<@brief Digital Filter Enable Mask for item 1. */
#define PORT_DFER_DFE_7_MASK 0x80u /*!<@brief Digital Filter Enable Mask for item 7. */

/*! @name PORTE25 (number 32), D4[3]/LEDRGB_BLUE
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_BLUE_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_BLUE_PIN 25U    /*!<@brief PORTE pin index: 25 */
                                  /* @} */

/*! @name PORTD1 (number 94), D4[1]/LEDRGB_RED
  @{ */
#define BOARD_LED_RED_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_RED_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_RED_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                 /* @} */

/*! @name PORTD7 (number 100), D4[4]/LEDRGB_GREEN
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_LED_GREEN_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_LED_GREEN_PIN 7U     /*!<@brief PORTD pin index: 7 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (number 62), U7[4]/UART0_RX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                       /* @} */

/*! @name PORTB17 (number 63), U10[1]/UART0_TX_TGTMCU
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name ADC1_DP1 (number 16), RT1/THER_A
  @{ */
/* @} */

/*! @name ADC1_DM1 (number 17), RT1/THER_B
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitTHERPins(void);

#define PORT_DFER_DFE_0_MASK 0x01u /*!<@brief Digital Filter Enable Mask for item 0. */
#define PORT_DFER_DFE_2_MASK 0x04u /*!<@brief Digital Filter Enable Mask for item 2. */
#define PORT_DFER_DFE_3_MASK 0x08u /*!<@brief Digital Filter Enable Mask for item 3. */

/*! @name PORTD2 (number 95), U8[4]/I2C0_SCL
  @{ */
#define BOARD_ACCEL_SCL_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_ACCEL_SCL_PIN 2U     /*!<@brief PORTD pin index: 2 */
                                   /* @} */

/*! @name PORTD3 (number 96), U8[6]/I2C0_SDA
  @{ */
#define BOARD_ACCEL_SDA_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_ACCEL_SDA_PIN 3U     /*!<@brief PORTD pin index: 3 */
                                   /* @} */

/*! @name PORTC18 (number 92), U8[9]/Sensor_INT2
  @{ */
#define BOARD_ACCEL_INT2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT2_PIN 18U    /*!<@brief PORTC pin index: 18 */
                                    /* @} */

/*! @name PORTD0 (number 93), U8[11]/INT1
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_ACCEL_INT1_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_ACCEL_INT1_PIN 0U     /*!<@brief PORTD pin index: 0 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void);

/*! @name PORTA18 (number 50), X501[1]/EXTAL0
  @{ */
#define BOARD_EXTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_EXTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                /* @} */

/*! @name PORTA19 (number 51), X501[3]/XTAL0
  @{ */
#define BOARD_XTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_XTAL0_PIN 19U    /*!<@brief PORTA pin index: 19 */
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
