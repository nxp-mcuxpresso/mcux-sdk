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

/* SPI0_CS0 (coord R33), BB_SPI0_CS0/J13E[15] */
#define BOARD_INITPINS_BB_SPI0_CS0_PERIPHERAL                          M40__TPM0   /*!< Device name: M40__TPM0 */
#define BOARD_INITPINS_BB_SPI0_CS0_SIGNAL                                 tpm_ch   /*!< M40__TPM0 signal: tpm_ch */
#define BOARD_INITPINS_BB_SPI0_CS0_CHANNEL                                     1   /*!< M40__TPM0 tpm_ch channel: 1 */
#define BOARD_INITPINS_BB_SPI0_CS0_PIN_NAME                             SPI0_CS0   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_CS0_PIN_FUNCTION_ID                 SC_P_SPI0_CS0   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_CS0_LABEL                  "BB_SPI0_CS0/J13E[15]"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_CS0_NAME                            "BB_SPI0_CS0"   /*!< Identifier name */

/* SPI0_SDI (coord P34), BB_SPI0_MISO/J13E[28] */
#define BOARD_INITPINS_BB_SPI0_MISO_PERIPHERAL                         M40__TPM0   /*!< Device name: M40__TPM0 */
#define BOARD_INITPINS_BB_SPI0_MISO_SIGNAL                                tpm_ch   /*!< M40__TPM0 signal: tpm_ch */
#define BOARD_INITPINS_BB_SPI0_MISO_CHANNEL                                    0   /*!< M40__TPM0 tpm_ch channel: 0 */
#define BOARD_INITPINS_BB_SPI0_MISO_PIN_NAME                            SPI0_SDI   /*!< Pin name */
#define BOARD_INITPINS_BB_SPI0_MISO_PIN_FUNCTION_ID                SC_P_SPI0_SDI   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI0_MISO_LABEL                "BB_SPI0_MISO/J13E[28]"   /*!< Label */
#define BOARD_INITPINS_BB_SPI0_MISO_NAME                          "BB_SPI0_MISO"   /*!< Identifier name */

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
