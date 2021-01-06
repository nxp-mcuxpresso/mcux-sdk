/*
 * Copyright 2017-2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "board.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* UART0_RX (number AB32), FTDI_UART0_RX */
#define BOARD_INITPINS_FTDI_UART0_RX_PERIPHERAL                      ADMA__UART0   /*!< Device name: ADMA__UART0 */
#define BOARD_INITPINS_FTDI_UART0_RX_SIGNAL                              uart_rx   /*!< ADMA__UART0 signal: uart_rx */
#define BOARD_INITPINS_FTDI_UART0_RX_PIN_NAME                           UART0_RX   /*!< Pin name */
#define BOARD_INITPINS_FTDI_UART0_RX_PIN_FUNCTION_ID               SC_P_UART0_RX   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_UART0_RX_LABEL                       "FTDI_UART0_RX"   /*!< Label */
#define BOARD_INITPINS_FTDI_UART0_RX_NAME                        "FTDI_UART0_RX"   /*!< Identifier name */

/* UART0_TX (number AA29), FTDI_UART0_TX */
#define BOARD_INITPINS_FTDI_UART0_TX_PERIPHERAL                      ADMA__UART0   /*!< Device name: ADMA__UART0 */
#define BOARD_INITPINS_FTDI_UART0_TX_SIGNAL                              uart_tx   /*!< ADMA__UART0 signal: uart_tx */
#define BOARD_INITPINS_FTDI_UART0_TX_PIN_NAME                           UART0_TX   /*!< Pin name */
#define BOARD_INITPINS_FTDI_UART0_TX_PIN_FUNCTION_ID               SC_P_UART0_TX   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_UART0_TX_LABEL                       "FTDI_UART0_TX"   /*!< Label */
#define BOARD_INITPINS_FTDI_UART0_TX_NAME                        "FTDI_UART0_TX"   /*!< Identifier name */

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
 * @param ipc scfw ipchandle.
 *
 */
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[m4] */

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
