/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
    kPIN_MUX_DirectionInput = 0U,        /* Input direction */
    kPIN_MUX_DirectionOutput = 1U,       /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U /* Input or output direction */
} pin_mux_direction_t;

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

#define SOPT5_LPUART0RXSRC_LPUART_RX 0x00u /*!<@brief LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX 0x00u /*!<@brief LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*! @name PORTA1 (number 23), J1[2]/J25[1]/D0-UART0_RX
  @{ */
#define BOARD_INITPINS_DEBUG_UART0_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART0_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                                 /* @} */

/*! @name PORTA2 (number 24), J1[4]/J26[1]/D1-UART0_TX
  @{ */
#define BOARD_INITPINS_DEBUG_UART0_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART0_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                                 /* @} */

/*! @name PORTE20 (number 9), J4[6]/A2-ADC0_SE0
  @{ */
#define BOARD_INITPINS_ADC0_SE0_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_ADC0_SE0_PIN 20U    /*!<@brief PORTE pin index: 20 */
                                           /* @} */

/*! @name PORTD4 (number 61), J1[9]/SDA_LED
  @{ */
#define BOARD_INITPINS_SDA_LED_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_SDA_LED_PIN 4U     /*!<@brief PORTD pin index: 4 */
                                          /* @} */

/*! @name PORTE0 (number 1), J3[1]/CLKOUT32K
  @{ */
#define BOARD_INITPINS_CLKOUT32K_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_CLKOUT32K_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

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
