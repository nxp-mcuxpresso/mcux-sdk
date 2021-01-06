/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif



/* PORTC25 (coord A7), LPUART0_RX_TGTMCU */
#define BOARD_DEBUG_UART_RX_PERIPHERAL                                   LPUART0   /*!< Device name: LPUART0 */
#define BOARD_DEBUG_UART_RX_SIGNAL                                            RX   /*!< LPUART0 signal: RX */
#define BOARD_DEBUG_UART_RX_PIN_NAME                                  LPUART0_RX   /*!< Pin name */
#define BOARD_DEBUG_UART_RX_LABEL                            "LPUART0_RX_TGTMCU"   /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME                                 "DEBUG_UART_RX"   /*!< Identifier name */

/* PORTC24 (coord B7), LPUART0_TX_TGTMCU */
#define BOARD_DEBUG_UART_TX_PERIPHERAL                                   LPUART0   /*!< Device name: LPUART0 */
#define BOARD_DEBUG_UART_TX_SIGNAL                                            TX   /*!< LPUART0 signal: TX */
#define BOARD_DEBUG_UART_TX_PIN_NAME                                  LPUART0_TX   /*!< Pin name */
#define BOARD_DEBUG_UART_TX_LABEL                            "LPUART0_TX_TGTMCU"   /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME                                 "DEBUG_UART_TX"   /*!< Identifier name */

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

/*******************************************************************************
 * EOF
 ******************************************************************************/
