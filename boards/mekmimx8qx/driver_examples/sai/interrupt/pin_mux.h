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

/* MCLK_OUT0 (coord L29), AUDIO_MCLK/BB_AUD_CON_IN_MCLK/J13A[17] */
#define BOARD_INITPINS_AUDIO_MCLK_PERIPHERAL                           ADMA__ACM   /*!< Device name: ADMA__ACM */
#define BOARD_INITPINS_AUDIO_MCLK_SIGNAL                            acm_mclk_out   /*!< ADMA__ACM signal: acm_mclk_out */
#define BOARD_INITPINS_AUDIO_MCLK_CHANNEL                                      0   /*!< ADMA__ACM acm_mclk_out channel: 0 */
#define BOARD_INITPINS_AUDIO_MCLK_PIN_NAME                             MCLK_OUT0   /*!< Pin name */
#define BOARD_INITPINS_AUDIO_MCLK_PIN_FUNCTION_ID                 SC_P_MCLK_OUT0   /*!< Pin function id */
#define BOARD_INITPINS_AUDIO_MCLK_LABEL "AUDIO_MCLK/BB_AUD_CON_IN_MCLK/J13A[17]"   /*!< Label */
#define BOARD_INITPINS_AUDIO_MCLK_NAME                              "AUDIO_MCLK"   /*!< Identifier name */

/* SAI1_RXC (coord L35), SAI1_TXC(SAI1_RXC) */
#define BOARD_INITPINS_SAI1_TXC_PERIPHERAL                            ADMA__SAI1   /*!< Device name: ADMA__SAI1 */
#define BOARD_INITPINS_SAI1_TXC_SIGNAL                                   sai_txc   /*!< ADMA__SAI1 signal: sai_txc */
#define BOARD_INITPINS_SAI1_TXC_PIN_NAME                                SAI1_RXC   /*!< Pin name */
#define BOARD_INITPINS_SAI1_TXC_PIN_FUNCTION_ID                    SC_P_SAI1_RXC   /*!< Pin function id */
#define BOARD_INITPINS_SAI1_TXC_LABEL                       "SAI1_TXC(SAI1_RXC)"   /*!< Label */
#define BOARD_INITPINS_SAI1_TXC_NAME                                  "SAI1_TXC"   /*!< Identifier name */

/* SAI1_RXFS (coord N35), SAI1_TXFS(SAI1_RXFS) */
#define BOARD_INITPINS_SAI1_TXFS_PERIPHERAL                           ADMA__SAI1   /*!< Device name: ADMA__SAI1 */
#define BOARD_INITPINS_SAI1_TXFS_SIGNAL                                 sai_txfs   /*!< ADMA__SAI1 signal: sai_txfs */
#define BOARD_INITPINS_SAI1_TXFS_PIN_NAME                              SAI1_RXFS   /*!< Pin name */
#define BOARD_INITPINS_SAI1_TXFS_PIN_FUNCTION_ID                  SC_P_SAI1_RXFS   /*!< Pin function id */
#define BOARD_INITPINS_SAI1_TXFS_LABEL                    "SAI1_TXFS(SAI1_RXFS)"   /*!< Label */
#define BOARD_INITPINS_SAI1_TXFS_NAME                                "SAI1_TXFS"   /*!< Identifier name */

/* SPI0_CS1 (coord R35), SAI1_TXD(SPI0_CS1) */
#define BOARD_INITPINS_SAI1_TXD_PERIPHERAL                            ADMA__SAI1   /*!< Device name: ADMA__SAI1 */
#define BOARD_INITPINS_SAI1_TXD_SIGNAL                                   sai_txd   /*!< ADMA__SAI1 signal: sai_txd */
#define BOARD_INITPINS_SAI1_TXD_PIN_NAME                                SPI0_CS1   /*!< Pin name */
#define BOARD_INITPINS_SAI1_TXD_PIN_FUNCTION_ID                    SC_P_SPI0_CS1   /*!< Pin function id */
#define BOARD_INITPINS_SAI1_TXD_LABEL                       "SAI1_TXD(SPI0_CS1)"   /*!< Label */
#define BOARD_INITPINS_SAI1_TXD_NAME                                  "SAI1_TXD"   /*!< Identifier name */

/* SAI1_RXD (coord M32), SAI1_RXD */
#define BOARD_INITPINS_SAI1_RXD_PERIPHERAL                            ADMA__SAI1   /*!< Device name: ADMA__SAI1 */
#define BOARD_INITPINS_SAI1_RXD_SIGNAL                                   sai_rxd   /*!< ADMA__SAI1 signal: sai_rxd */
#define BOARD_INITPINS_SAI1_RXD_PIN_NAME                                SAI1_RXD   /*!< Pin name */
#define BOARD_INITPINS_SAI1_RXD_PIN_FUNCTION_ID                    SC_P_SAI1_RXD   /*!< Pin function id */
#define BOARD_INITPINS_SAI1_RXD_LABEL                                 "SAI1_RXD"   /*!< Label */
#define BOARD_INITPINS_SAI1_RXD_NAME                                  "SAI1_RXD"   /*!< Identifier name */

/* ADC_IN0 (coord U35), M4_I2C0_1V8_SCL */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_PERIPHERAL             M40__I2C0   /*!< Device name: M40__I2C0 */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_SIGNAL                   i2c_scl   /*!< M40__I2C0 signal: i2c_scl */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_PIN_NAME                 ADC_IN0   /*!< Pin name */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_PIN_FUNCTION_ID     SC_P_ADC_IN0   /*!< Pin function id */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_LABEL          "M4_I2C0_1V8_SCL"   /*!< Label */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SCL_NAME           "M4_I2C0_1V8_SCL"   /*!< Identifier name */

/* ADC_IN1 (coord U33), M4_I2C0_1V8_SDA */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_PERIPHERAL             M40__I2C0   /*!< Device name: M40__I2C0 */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_SIGNAL                   i2c_sda   /*!< M40__I2C0 signal: i2c_sda */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_PIN_NAME                 ADC_IN1   /*!< Pin name */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_PIN_FUNCTION_ID     SC_P_ADC_IN1   /*!< Pin function id */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_LABEL          "M4_I2C0_1V8_SDA"   /*!< Label */
#define BOARD_I2C_CONFIGUREPINS_M4_I2C0_1V8_SDA_NAME           "M4_I2C0_1V8_SDA"   /*!< Identifier name */

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

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 * @param ipc scfw ipchandle.
 *
 */
void BOARD_I2C_ConfigurePins(sc_ipc_t ipc);                /*!< Function assigned for the core: Cortex-M4F[m4] */

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
