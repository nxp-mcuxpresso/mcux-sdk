/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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


#define SOPT5_UART0RXSRC_UART_RX 0x00u /*!<@brief UART 0 Receive Data Source Select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 Transmit Data Source Select: UART0_TX pin */

/*! @name PORTA4 (number 26), SW3
  @{ */
#define BOARD_INITPINS_SW3_PERIPHERAL GPIOA                   /*!<@brief Device name: GPIOA */
#define BOARD_INITPINS_SW3_SIGNAL GPIO                        /*!<@brief GPIOA signal: GPIO */
#define BOARD_INITPINS_SW3_GPIO GPIOA                         /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_SW3_GPIO_PIN 4U                        /*!<@brief PORTA pin index: 4 */
#define BOARD_INITPINS_SW3_PORT PORTA                         /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_SW3_PIN 4U                             /*!<@brief PORTA pin index: 4 */
#define BOARD_INITPINS_SW3_CHANNEL 4                          /*!<@brief GPIOA GPIO channel: 4 */
#define BOARD_INITPINS_SW3_PIN_NAME PTA4                      /*!<@brief Pin name */
#define BOARD_INITPINS_SW3_LABEL "SW3"                        /*!<@brief Label */
#define BOARD_INITPINS_SW3_NAME "SW3"                         /*!<@brief Identifier name */
#define BOARD_INITPINS_SW3_DIRECTION kPIN_MUX_DirectionOutput /*!<@brief Direction */
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
