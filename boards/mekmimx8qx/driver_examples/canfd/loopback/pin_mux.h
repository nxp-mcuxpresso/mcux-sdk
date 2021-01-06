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

/* ADC_IN2 (coord V32), FTDI_M40_UART0_RX */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PERIPHERAL                   M40__UART0   /*!< Device name: M40__UART0 */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_SIGNAL                          uart_rx   /*!< M40__UART0 signal: uart_rx */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PIN_NAME                        ADC_IN2   /*!< Pin name */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PIN_FUNCTION_ID            SC_P_ADC_IN2   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_LABEL               "FTDI_M40_UART0_RX"   /*!< Label */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_NAME                "FTDI_M40_UART0_RX"   /*!< Identifier name */

/* ADC_IN3 (coord V30), FTDI_M40_UART0_TX */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PERIPHERAL                   M40__UART0   /*!< Device name: M40__UART0 */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_SIGNAL                          uart_tx   /*!< M40__UART0 signal: uart_tx */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PIN_NAME                        ADC_IN3   /*!< Pin name */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PIN_FUNCTION_ID            SC_P_ADC_IN3   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_LABEL               "FTDI_M40_UART0_TX"   /*!< Label */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_NAME                "FTDI_M40_UART0_TX"   /*!< Identifier name */

/* FLEXCAN0_RX (coord Y34), BB_CAN0_RX/J13C[25] */
#define BOARD_INITPINS_BB_CAN0_RX_PERIPHERAL                      ADMA__FLEXCAN0   /*!< Device name: ADMA__FLEXCAN0 */
#define BOARD_INITPINS_BB_CAN0_RX_SIGNAL                              flexcan_rx   /*!< ADMA__FLEXCAN0 signal: flexcan_rx */
#define BOARD_INITPINS_BB_CAN0_RX_PIN_NAME                           FLEXCAN0_RX   /*!< Pin name */
#define BOARD_INITPINS_BB_CAN0_RX_PIN_FUNCTION_ID               SC_P_FLEXCAN0_RX   /*!< Pin function id */
#define BOARD_INITPINS_BB_CAN0_RX_LABEL                    "BB_CAN0_RX/J13C[25]"   /*!< Label */
#define BOARD_INITPINS_BB_CAN0_RX_NAME                              "BB_CAN0_RX"   /*!< Identifier name */

/* FLEXCAN0_TX (coord Y32), BB_CAN0_TX/J13C[26] */
#define BOARD_INITPINS_BB_CAN0_TX_PERIPHERAL                      ADMA__FLEXCAN0   /*!< Device name: ADMA__FLEXCAN0 */
#define BOARD_INITPINS_BB_CAN0_TX_SIGNAL                              flexcan_tx   /*!< ADMA__FLEXCAN0 signal: flexcan_tx */
#define BOARD_INITPINS_BB_CAN0_TX_PIN_NAME                           FLEXCAN0_TX   /*!< Pin name */
#define BOARD_INITPINS_BB_CAN0_TX_PIN_FUNCTION_ID               SC_P_FLEXCAN0_TX   /*!< Pin function id */
#define BOARD_INITPINS_BB_CAN0_TX_LABEL                    "BB_CAN0_TX/J13C[26]"   /*!< Label */
#define BOARD_INITPINS_BB_CAN0_TX_NAME                              "BB_CAN0_TX"   /*!< Identifier name */

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
