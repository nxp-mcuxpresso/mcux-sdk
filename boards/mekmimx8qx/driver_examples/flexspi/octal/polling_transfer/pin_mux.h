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

/* QSPI0A_DATA0 (number AK14), QSPI0_DATA0 */
#define BOARD_INITPINS_QSPI0_DATA0_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA0_SIGNAL                            qspi_a_data   /*!< LSIO__QSPI0 signal: qspi_a_data */
#define BOARD_INITPINS_QSPI0_DATA0_CHANNEL                                     0   /*!< LSIO__QSPI0 qspi_a_data channel: 0 */
#define BOARD_INITPINS_QSPI0_DATA0_PIN_NAME                         QSPI0A_DATA0   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA0_PIN_FUNCTION_ID             SC_P_QSPI0A_DATA0   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA0_LABEL                           "QSPI0_DATA0"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA0_NAME                            "QSPI0_DATA0"   /*!< Identifier name */

/* QSPI0A_DATA1 (number AR13), QSPI0_DATA1 */
#define BOARD_INITPINS_QSPI0_DATA1_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA1_SIGNAL                            qspi_a_data   /*!< LSIO__QSPI0 signal: qspi_a_data */
#define BOARD_INITPINS_QSPI0_DATA1_CHANNEL                                     1   /*!< LSIO__QSPI0 qspi_a_data channel: 1 */
#define BOARD_INITPINS_QSPI0_DATA1_PIN_NAME                         QSPI0A_DATA1   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA1_PIN_FUNCTION_ID             SC_P_QSPI0A_DATA1   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA1_LABEL                           "QSPI0_DATA1"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA1_NAME                            "QSPI0_DATA1"   /*!< Identifier name */

/* QSPI0A_DATA2 (number AJ13), QSPI0_DATA2 */
#define BOARD_INITPINS_QSPI0_DATA2_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA2_SIGNAL                            qspi_a_data   /*!< LSIO__QSPI0 signal: qspi_a_data */
#define BOARD_INITPINS_QSPI0_DATA2_CHANNEL                                     2   /*!< LSIO__QSPI0 qspi_a_data channel: 2 */
#define BOARD_INITPINS_QSPI0_DATA2_PIN_NAME                         QSPI0A_DATA2   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA2_PIN_FUNCTION_ID             SC_P_QSPI0A_DATA2   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA2_LABEL                           "QSPI0_DATA2"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA2_NAME                            "QSPI0_DATA2"   /*!< Identifier name */

/* QSPI0A_DATA3 (number AH12), QSPI0_DATA3 */
#define BOARD_INITPINS_QSPI0_DATA3_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA3_SIGNAL                            qspi_a_data   /*!< LSIO__QSPI0 signal: qspi_a_data */
#define BOARD_INITPINS_QSPI0_DATA3_CHANNEL                                     3   /*!< LSIO__QSPI0 qspi_a_data channel: 3 */
#define BOARD_INITPINS_QSPI0_DATA3_PIN_NAME                         QSPI0A_DATA3   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA3_PIN_FUNCTION_ID             SC_P_QSPI0A_DATA3   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA3_LABEL                           "QSPI0_DATA3"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA3_NAME                            "QSPI0_DATA3"   /*!< Identifier name */

/* QSPI0A_DQS (number AL11), QSPI0A_DQS */
#define BOARD_INITPINS_QSPI0A_DQS_PERIPHERAL                         LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0A_DQS_SIGNAL                              qspi_a_dqs   /*!< LSIO__QSPI0 signal: qspi_a_dqs */
#define BOARD_INITPINS_QSPI0A_DQS_PIN_NAME                            QSPI0A_DQS   /*!< Pin name */
#define BOARD_INITPINS_QSPI0A_DQS_PIN_FUNCTION_ID                SC_P_QSPI0A_DQS   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0A_DQS_LABEL                             "QSPI0A_DQS"   /*!< Label */
#define BOARD_INITPINS_QSPI0A_DQS_NAME                              "QSPI0A_DQS"   /*!< Identifier name */

/* QSPI0A_SCLK (number AP12), QSPI0A_SCLK */
#define BOARD_INITPINS_QSPI0A_SCLK_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0A_SCLK_SIGNAL                            qspi_a_sclk   /*!< LSIO__QSPI0 signal: qspi_a_sclk */
#define BOARD_INITPINS_QSPI0A_SCLK_PIN_NAME                          QSPI0A_SCLK   /*!< Pin name */
#define BOARD_INITPINS_QSPI0A_SCLK_PIN_FUNCTION_ID              SC_P_QSPI0A_SCLK   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0A_SCLK_LABEL                           "QSPI0A_SCLK"   /*!< Label */
#define BOARD_INITPINS_QSPI0A_SCLK_NAME                            "QSPI0A_SCLK"   /*!< Identifier name */

/* QSPI0A_SS0_B (number AM12), QSPI0A_SS0_B */
#define BOARD_INITPINS_QSPI0A_SS0_B_PERIPHERAL                       LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0A_SS0_B_SIGNAL                          qspi_a_ss0_b   /*!< LSIO__QSPI0 signal: qspi_a_ss0_b */
#define BOARD_INITPINS_QSPI0A_SS0_B_PIN_NAME                        QSPI0A_SS0_B   /*!< Pin name */
#define BOARD_INITPINS_QSPI0A_SS0_B_PIN_FUNCTION_ID            SC_P_QSPI0A_SS0_B   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0A_SS0_B_LABEL                         "QSPI0A_SS0_B"   /*!< Label */
#define BOARD_INITPINS_QSPI0A_SS0_B_NAME                          "QSPI0A_SS0_B"   /*!< Identifier name */

/* QSPI0B_DATA0 (number AM10), QSPI0_DATA4 */
#define BOARD_INITPINS_QSPI0_DATA4_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA4_SIGNAL                            qspi_b_data   /*!< LSIO__QSPI0 signal: qspi_b_data */
#define BOARD_INITPINS_QSPI0_DATA4_CHANNEL                                     0   /*!< LSIO__QSPI0 qspi_b_data channel: 0 */
#define BOARD_INITPINS_QSPI0_DATA4_PIN_NAME                         QSPI0B_DATA0   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA4_PIN_FUNCTION_ID             SC_P_QSPI0B_DATA0   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA4_LABEL                           "QSPI0_DATA4"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA4_NAME                            "QSPI0_DATA4"   /*!< Identifier name */

/* QSPI0B_DATA1 (number AL9), QSPI0_DATA5 */
#define BOARD_INITPINS_QSPI0_DATA5_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA5_SIGNAL                            qspi_b_data   /*!< LSIO__QSPI0 signal: qspi_b_data */
#define BOARD_INITPINS_QSPI0_DATA5_CHANNEL                                     1   /*!< LSIO__QSPI0 qspi_b_data channel: 1 */
#define BOARD_INITPINS_QSPI0_DATA5_PIN_NAME                         QSPI0B_DATA1   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA5_PIN_FUNCTION_ID             SC_P_QSPI0B_DATA1   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA5_LABEL                           "QSPI0_DATA5"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA5_NAME                            "QSPI0_DATA5"   /*!< Identifier name */

/* QSPI0B_DATA2 (number AJ11), QSPI0_DATA6 */
#define BOARD_INITPINS_QSPI0_DATA6_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA6_SIGNAL                            qspi_b_data   /*!< LSIO__QSPI0 signal: qspi_b_data */
#define BOARD_INITPINS_QSPI0_DATA6_CHANNEL                                     2   /*!< LSIO__QSPI0 qspi_b_data channel: 2 */
#define BOARD_INITPINS_QSPI0_DATA6_PIN_NAME                         QSPI0B_DATA2   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA6_PIN_FUNCTION_ID             SC_P_QSPI0B_DATA2   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA6_LABEL                           "QSPI0_DATA6"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA6_NAME                            "QSPI0_DATA6"   /*!< Identifier name */

/* QSPI0B_DATA3 (number AM8), QSPI0_DATA7 */
#define BOARD_INITPINS_QSPI0_DATA7_PERIPHERAL                        LSIO__QSPI0   /*!< Device name: LSIO__QSPI0 */
#define BOARD_INITPINS_QSPI0_DATA7_SIGNAL                            qspi_b_data   /*!< LSIO__QSPI0 signal: qspi_b_data */
#define BOARD_INITPINS_QSPI0_DATA7_CHANNEL                                     3   /*!< LSIO__QSPI0 qspi_b_data channel: 3 */
#define BOARD_INITPINS_QSPI0_DATA7_PIN_NAME                         QSPI0B_DATA3   /*!< Pin name */
#define BOARD_INITPINS_QSPI0_DATA7_PIN_FUNCTION_ID             SC_P_QSPI0B_DATA3   /*!< Pin function id */
#define BOARD_INITPINS_QSPI0_DATA7_LABEL                           "QSPI0_DATA7"   /*!< Label */
#define BOARD_INITPINS_QSPI0_DATA7_NAME                            "QSPI0_DATA7"   /*!< Identifier name */

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
