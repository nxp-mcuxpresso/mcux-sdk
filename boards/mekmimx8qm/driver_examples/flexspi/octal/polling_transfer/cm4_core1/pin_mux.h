/*
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#include "board.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* QSPI0A_DATA0 (coord G13), QSPI0_DAT0 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT0_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT0_SIGNAL                             qspi_a_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT0_CHANNEL                                      0   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT0_PIN_NAME                          QSPI0A_DATA0   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT0_PIN_FUNCTION_ID              SC_P_QSPI0A_DATA0   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT0_LABEL                             "QSPI0_DAT0"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT0_NAME                              "QSPI0_DAT0"   /*!< Identifier */

/* QSPI0A_DATA1 (coord F14), QSPI0_DAT1 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT1_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT1_SIGNAL                             qspi_a_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT1_CHANNEL                                      1   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT1_PIN_NAME                          QSPI0A_DATA1   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT1_PIN_FUNCTION_ID              SC_P_QSPI0A_DATA1   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT1_LABEL                             "QSPI0_DAT1"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT1_NAME                              "QSPI0_DAT1"   /*!< Identifier */

/* QSPI0A_DATA2 (coord H14), QSPI0_DAT2 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT2_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT2_SIGNAL                             qspi_a_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT2_CHANNEL                                      2   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT2_PIN_NAME                          QSPI0A_DATA2   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT2_PIN_FUNCTION_ID              SC_P_QSPI0A_DATA2   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT2_LABEL                             "QSPI0_DAT2"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT2_NAME                              "QSPI0_DAT2"   /*!< Identifier */

/* QSPI0A_DATA3 (coord H16), QSPI0_DAT3 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT3_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT3_SIGNAL                             qspi_a_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT3_CHANNEL                                      3   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT3_PIN_NAME                          QSPI0A_DATA3   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT3_PIN_FUNCTION_ID              SC_P_QSPI0A_DATA3   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT3_LABEL                             "QSPI0_DAT3"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT3_NAME                              "QSPI0_DAT3"   /*!< Identifier */

/* QSPI0A_DQS (coord G17), QSPI0_DQS */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DQS_PERIPHERAL                          LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DQS_SIGNAL                               qspi_a_dqs   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DQS_PIN_NAME                             QSPI0A_DQS   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DQS_PIN_FUNCTION_ID                 SC_P_QSPI0A_DQS   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DQS_LABEL                               "QSPI0_DQS"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DQS_NAME                                "QSPI0_DQS"   /*!< Identifier */

/* QSPI0A_SCLK (coord E17), QSPI0A_CLK */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0A_CLK_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0A_CLK_SIGNAL                             qspi_a_sclk   /*!< Signal name */
#define BOARD_INITPINS_QSPI0A_CLK_PIN_NAME                           QSPI0A_SCLK   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0A_CLK_PIN_FUNCTION_ID               SC_P_QSPI0A_SCLK   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0A_CLK_LABEL                             "QSPI0A_CLK"   /*!< Label */
#define BOARD_INITPINS_QSPI0A_CLK_NAME                              "QSPI0A_CLK"   /*!< Identifier */

/* QSPI0A_SS0_B (coord E15), QSPI0A_CS_B */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0A_CS_B_PERIPHERAL                        LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0A_CS_B_SIGNAL                           qspi_a_ss0_b   /*!< Signal name */
#define BOARD_INITPINS_QSPI0A_CS_B_PIN_NAME                         QSPI0A_SS0_B   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0A_CS_B_PIN_FUNCTION_ID             SC_P_QSPI0A_SS0_B   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0A_CS_B_LABEL                           "QSPI0A_CS_B"   /*!< Label */
#define BOARD_INITPINS_QSPI0A_CS_B_NAME                            "QSPI0A_CS_B"   /*!< Identifier */

/* QSPI0B_DATA0 (coord H18), QSPI0_DAT4 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT4_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT4_SIGNAL                             qspi_b_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT4_CHANNEL                                      0   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT4_PIN_NAME                          QSPI0B_DATA0   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT4_PIN_FUNCTION_ID              SC_P_QSPI0B_DATA0   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT4_LABEL                             "QSPI0_DAT4"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT4_NAME                              "QSPI0_DAT4"   /*!< Identifier */

/* QSPI0B_DATA1 (coord H20), QSPI0_DAT5 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT5_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT5_SIGNAL                             qspi_b_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT5_CHANNEL                                      1   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT5_PIN_NAME                          QSPI0B_DATA1   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT5_PIN_FUNCTION_ID              SC_P_QSPI0B_DATA1   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT5_LABEL                             "QSPI0_DAT5"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT5_NAME                              "QSPI0_DAT5"   /*!< Identifier */

/* QSPI0B_DATA2 (coord G19), QSPI0_DAT6 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT6_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT6_SIGNAL                             qspi_b_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT6_CHANNEL                                      2   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT6_PIN_NAME                          QSPI0B_DATA2   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT6_PIN_FUNCTION_ID              SC_P_QSPI0B_DATA2   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT6_LABEL                             "QSPI0_DAT6"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT6_NAME                              "QSPI0_DAT6"   /*!< Identifier */

/* QSPI0B_DATA3 (coord F20), QSPI0_DAT7 */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0_DAT7_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0_DAT7_SIGNAL                             qspi_b_data   /*!< Signal name */
#define BOARD_INITPINS_QSPI0_DAT7_CHANNEL                                      3   /*!< Signal channel */
#define BOARD_INITPINS_QSPI0_DAT7_PIN_NAME                          QSPI0B_DATA3   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0_DAT7_PIN_FUNCTION_ID              SC_P_QSPI0B_DATA3   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DAT7_LABEL                             "QSPI0_DAT7"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DAT7_NAME                              "QSPI0_DAT7"   /*!< Identifier */

/* QSPI0B_SCLK (coord F18), QSPI0B_CLK */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0B_CLK_PERIPHERAL                         LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0B_CLK_SIGNAL                             qspi_b_sclk   /*!< Signal name */
#define BOARD_INITPINS_QSPI0B_CLK_PIN_NAME                           QSPI0B_SCLK   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0B_CLK_PIN_FUNCTION_ID               SC_P_QSPI0B_SCLK   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0B_CLK_LABEL                             "QSPI0B_CLK"   /*!< Label */
#define BOARD_INITPINS_QSPI0B_CLK_NAME                              "QSPI0B_CLK"   /*!< Identifier */

/* QSPI0B_SS0_B (coord F22), QSPI0B_CS_B */
/* Routed pin properties */
#define BOARD_INITPINS_QSPI0B_CS_B_PERIPHERAL                        LSIO__QSPI0   /*!< Peripheral name */
#define BOARD_INITPINS_QSPI0B_CS_B_SIGNAL                           qspi_b_ss0_b   /*!< Signal name */
#define BOARD_INITPINS_QSPI0B_CS_B_PIN_NAME                         QSPI0B_SS0_B   /*!< Routed pin name */
#define BOARD_INITPINS_QSPI0B_CS_B_PIN_FUNCTION_ID             SC_P_QSPI0B_SS0_B   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0B_CS_B_LABEL                           "QSPI0B_CS_B"   /*!< Label */
#define BOARD_INITPINS_QSPI0B_CS_B_NAME                            "QSPI0B_CS_B"   /*!< Identifier */

/* UART0_RTS_B (number AU45), BB_UART2_RX/J20A[28] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_UART2_RX_PERIPHERAL                         DMA__UART2   /*!< Peripheral name */
#define BOARD_INITPINS_BB_UART2_RX_SIGNAL                                uart_rx   /*!< Signal name */
#define BOARD_INITPINS_BB_UART2_RX_PIN_NAME                          UART0_RTS_B   /*!< Routed pin name */
#define BOARD_INITPINS_BB_UART2_RX_PIN_FUNCTION_ID              SC_P_UART0_RTS_B   /*!< Pin function id */
#define BOARD_INITPINS_BB_UART2_RX_LABEL                  "BB_UART2_RX/J20A[28]"   /*!< Label */
#define BOARD_INITPINS_BB_UART2_RX_NAME                            "BB_UART2_RX"   /*!< Identifier */

/* UART0_CTS_B (number AW49), BB_UART2_TX/J20A[29] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_UART2_TX_PERIPHERAL                         DMA__UART2   /*!< Peripheral name */
#define BOARD_INITPINS_BB_UART2_TX_SIGNAL                                uart_tx   /*!< Signal name */
#define BOARD_INITPINS_BB_UART2_TX_PIN_NAME                          UART0_CTS_B   /*!< Routed pin name */
#define BOARD_INITPINS_BB_UART2_TX_PIN_FUNCTION_ID              SC_P_UART0_CTS_B   /*!< Pin function id */
#define BOARD_INITPINS_BB_UART2_TX_LABEL                  "BB_UART2_TX/J20A[29]"   /*!< Label */
#define BOARD_INITPINS_BB_UART2_TX_NAME                            "BB_UART2_TX"   /*!< Identifier */

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
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[cm4_core1] */

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
