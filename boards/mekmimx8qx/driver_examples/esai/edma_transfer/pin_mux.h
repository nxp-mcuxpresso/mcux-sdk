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

/* ADC_IN0 (coord U35), M4_I2C0_1V8_SCL */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_PERIPHERAL                      M40__I2C0   /*!< Device name: M40__I2C0 */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_SIGNAL                            i2c_scl   /*!< M40__I2C0 signal: i2c_scl */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_PIN_NAME                          ADC_IN0   /*!< Pin name */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_PIN_FUNCTION_ID              SC_P_ADC_IN0   /*!< Pin function id */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_LABEL                   "M4_I2C0_1V8_SCL"   /*!< Label */
#define BOARD_INITPINS_M4_I2C0_1V8_SCL_NAME                    "M4_I2C0_1V8_SCL"   /*!< Identifier name */

/* ADC_IN1 (coord U33), M4_I2C0_1V8_SDA */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_PERIPHERAL                      M40__I2C0   /*!< Device name: M40__I2C0 */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_SIGNAL                            i2c_sda   /*!< M40__I2C0 signal: i2c_sda */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_PIN_NAME                          ADC_IN1   /*!< Pin name */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_PIN_FUNCTION_ID              SC_P_ADC_IN1   /*!< Pin function id */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_LABEL                   "M4_I2C0_1V8_SDA"   /*!< Label */
#define BOARD_INITPINS_M4_I2C0_1V8_SDA_NAME                    "M4_I2C0_1V8_SDA"   /*!< Identifier name */

/* ESAI0_FSR (coord F30), ESAI0_FSR/BB_RGMII_TXCJ13F[44] */
#define BOARD_INITPINS_ESAI0_FSR_PERIPHERAL                          ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_FSR_SIGNAL                                 esai_fsr   /*!< ADMA__ESAI0 signal: esai_fsr */
#define BOARD_INITPINS_ESAI0_FSR_PIN_NAME                              ESAI0_FSR   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_FSR_PIN_FUNCTION_ID                  SC_P_ESAI0_FSR   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_FSR_LABEL          "ESAI0_FSR/BB_RGMII_TXCJ13F[44]"   /*!< Label */
#define BOARD_INITPINS_ESAI0_FSR_NAME                                "ESAI0_FSR"   /*!< Identifier name */

/* ESAI0_FST (coord G29), ESAI0_FST/BB_RGMII_TXD2/J13F[27] */
#define BOARD_INITPINS_ESAI0_FST_PERIPHERAL                          ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_FST_SIGNAL                                 esai_fst   /*!< ADMA__ESAI0 signal: esai_fst */
#define BOARD_INITPINS_ESAI0_FST_PIN_NAME                              ESAI0_FST   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_FST_PIN_FUNCTION_ID                  SC_P_ESAI0_FST   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_FST_LABEL        "ESAI0_FST/BB_RGMII_TXD2/J13F[27]"   /*!< Label */
#define BOARD_INITPINS_ESAI0_FST_NAME                                "ESAI0_FST"   /*!< Identifier name */

/* ESAI0_SCKR (coord H28), ESAI0_SCKR/BB_RGMII_TX_CTL/J13F[42] */
#define BOARD_INITPINS_ESAI0_SCKR_PERIPHERAL                         ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_SCKR_SIGNAL                               esai_sckr   /*!< ADMA__ESAI0 signal: esai_sckr */
#define BOARD_INITPINS_ESAI0_SCKR_PIN_NAME                            ESAI0_SCKR   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_SCKR_PIN_FUNCTION_ID                SC_P_ESAI0_SCKR   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_SCKR_LABEL    "ESAI0_SCKR/BB_RGMII_TX_CTL/J13F[42]"   /*!< Label */
#define BOARD_INITPINS_ESAI0_SCKR_NAME                              "ESAI0_SCKR"   /*!< Identifier name */

/* ESAI0_SCKT (coord E31), ESAI0_SCKT/BB_RGMII_TXD3/J13F[36] */
#define BOARD_INITPINS_ESAI0_SCKT_PERIPHERAL                         ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_SCKT_SIGNAL                               esai_sckt   /*!< ADMA__ESAI0 signal: esai_sckt */
#define BOARD_INITPINS_ESAI0_SCKT_PIN_NAME                            ESAI0_SCKT   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_SCKT_PIN_FUNCTION_ID                SC_P_ESAI0_SCKT   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_SCKT_LABEL      "ESAI0_SCKT/BB_RGMII_TXD3/J13F[36]"   /*!< Label */
#define BOARD_INITPINS_ESAI0_SCKT_NAME                              "ESAI0_SCKT"   /*!< Identifier name */

/* ESAI0_TX0 (coord D32), BB_ESAI0_TX0/J13F[38] */
#define BOARD_INITPINS_BB_ESAI0_TX0_PERIPHERAL                       ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_BB_ESAI0_TX0_SIGNAL                               esai_tx   /*!< ADMA__ESAI0 signal: esai_tx */
#define BOARD_INITPINS_BB_ESAI0_TX0_CHANNEL                                    0   /*!< ADMA__ESAI0 esai_tx channel: 0 */
#define BOARD_INITPINS_BB_ESAI0_TX0_PIN_NAME                           ESAI0_TX0   /*!< Pin name */
#define BOARD_INITPINS_BB_ESAI0_TX0_PIN_FUNCTION_ID               SC_P_ESAI0_TX0   /*!< Pin function id */
#define BOARD_INITPINS_BB_ESAI0_TX0_LABEL                "BB_ESAI0_TX0/J13F[38]"   /*!< Label */
#define BOARD_INITPINS_BB_ESAI0_TX0_NAME                          "BB_ESAI0_TX0"   /*!< Identifier name */

/* ESAI0_TX1 (coord B34), BB_ESAI0_TX1/J13F[29] */
#define BOARD_INITPINS_BB_ESAI0_TX1_PERIPHERAL                       ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_BB_ESAI0_TX1_SIGNAL                               esai_tx   /*!< ADMA__ESAI0 signal: esai_tx */
#define BOARD_INITPINS_BB_ESAI0_TX1_CHANNEL                                    1   /*!< ADMA__ESAI0 esai_tx channel: 1 */
#define BOARD_INITPINS_BB_ESAI0_TX1_PIN_NAME                           ESAI0_TX1   /*!< Pin name */
#define BOARD_INITPINS_BB_ESAI0_TX1_PIN_FUNCTION_ID               SC_P_ESAI0_TX1   /*!< Pin function id */
#define BOARD_INITPINS_BB_ESAI0_TX1_LABEL                "BB_ESAI0_TX1/J13F[29]"   /*!< Label */
#define BOARD_INITPINS_BB_ESAI0_TX1_NAME                          "BB_ESAI0_TX1"   /*!< Identifier name */

/* ESAI0_TX2_RX3 (coord K28), BB_ESAI0_TX2_RX3/J13F[32] */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_PERIPHERAL                   ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_SIGNAL                       esai_tx2_rx   /*!< ADMA__ESAI0 signal: esai_tx2_rx */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_CHANNEL                                3   /*!< ADMA__ESAI0 esai_tx2_rx channel: 3 */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_PIN_NAME                   ESAI0_TX2_RX3   /*!< Pin name */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_PIN_FUNCTION_ID       SC_P_ESAI0_TX2_RX3   /*!< Pin function id */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_LABEL        "BB_ESAI0_TX2_RX3/J13F[32]"   /*!< Label */
#define BOARD_INITPINS_BB_ESAI0_TX2_RX3_NAME                  "BB_ESAI0_TX2_RX3"   /*!< Identifier name */

/* ESAI0_TX3_RX2 (coord C33), BB_ESAI0_TX3_RX2/J13F[35] */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_PERIPHERAL                   ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_SIGNAL                       esai_tx3_rx   /*!< ADMA__ESAI0 signal: esai_tx3_rx */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_CHANNEL                                2   /*!< ADMA__ESAI0 esai_tx3_rx channel: 2 */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_PIN_NAME                   ESAI0_TX3_RX2   /*!< Pin name */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_PIN_FUNCTION_ID       SC_P_ESAI0_TX3_RX2   /*!< Pin function id */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_LABEL        "BB_ESAI0_TX3_RX2/J13F[35]"   /*!< Label */
#define BOARD_INITPINS_BB_ESAI0_TX3_RX2_NAME                  "BB_ESAI0_TX3_RX2"   /*!< Identifier name */

/* ESAI0_TX4_RX1 (coord F32), ESAI0_TX4_RX1/BB_RGMII_TXD0/J13F[41] */
#define BOARD_INITPINS_ESAI0_TX4_RX1_PERIPHERAL                      ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_TX4_RX1_SIGNAL                          esai_tx4_rx   /*!< ADMA__ESAI0 signal: esai_tx4_rx */
#define BOARD_INITPINS_ESAI0_TX4_RX1_CHANNEL                                   1   /*!< ADMA__ESAI0 esai_tx4_rx channel: 1 */
#define BOARD_INITPINS_ESAI0_TX4_RX1_PIN_NAME                      ESAI0_TX4_RX1   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_TX4_RX1_PIN_FUNCTION_ID          SC_P_ESAI0_TX4_RX1   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_TX4_RX1_LABEL "ESAI0_TX4_RX1/BB_RGMII_TXD0/J13F[41]"  /*!< Label */
#define BOARD_INITPINS_ESAI0_TX4_RX1_NAME                        "ESAI0_TX4_RX1"   /*!< Identifier name */

/* ESAI0_TX5_RX0 (coord J29), ESAI0_TX5_RX0/BB_RGMII_TXD1/J13F[39] */
#define BOARD_INITPINS_ESAI0_TX5_RX0_PERIPHERAL                      ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_ESAI0_TX5_RX0_SIGNAL                          esai_tx5_rx   /*!< ADMA__ESAI0 signal: esai_tx5_rx */
#define BOARD_INITPINS_ESAI0_TX5_RX0_CHANNEL                                   0   /*!< ADMA__ESAI0 esai_tx5_rx channel: 0 */
#define BOARD_INITPINS_ESAI0_TX5_RX0_PIN_NAME                      ESAI0_TX5_RX0   /*!< Pin name */
#define BOARD_INITPINS_ESAI0_TX5_RX0_PIN_FUNCTION_ID          SC_P_ESAI0_TX5_RX0   /*!< Pin function id */
#define BOARD_INITPINS_ESAI0_TX5_RX0_LABEL "ESAI0_TX5_RX0/BB_RGMII_TXD1/J13F[39]"  /*!< Label */
#define BOARD_INITPINS_ESAI0_TX5_RX0_NAME                        "ESAI0_TX5_RX0"   /*!< Identifier name */

/* MCLK_OUT0 (coord L29), AUDIO_MCLK/BB_AUD_CON_IN_MCLK/J13A[17] */
#define BOARD_INITPINS_AUDIO_MCLK_PERIPHERAL                         ADMA__ESAI0   /*!< Device name: ADMA__ESAI0 */
#define BOARD_INITPINS_AUDIO_MCLK_SIGNAL                          esai_tx_hf_clk   /*!< ADMA__ESAI0 signal: esai_tx_hf_clk */
#define BOARD_INITPINS_AUDIO_MCLK_PIN_NAME                             MCLK_OUT0   /*!< Pin name */
#define BOARD_INITPINS_AUDIO_MCLK_PIN_FUNCTION_ID                 SC_P_MCLK_OUT0   /*!< Pin function id */
#define BOARD_INITPINS_AUDIO_MCLK_LABEL "AUDIO_MCLK/BB_AUD_CON_IN_MCLK/J13A[17]"   /*!< Label */
#define BOARD_INITPINS_AUDIO_MCLK_NAME                              "AUDIO_MCLK"   /*!< Identifier name */

/* USB_SS3_TC1 (coord H14), I2C1_SCL(SS3_SCL) */
#define BOARD_INITPINS_I2C1_SCL_PERIPHERAL                            ADMA__I2C1   /*!< Device name: ADMA__I2C1 */
#define BOARD_INITPINS_I2C1_SCL_SIGNAL                                   i2c_scl   /*!< ADMA__I2C1 signal: i2c_scl */
#define BOARD_INITPINS_I2C1_SCL_PIN_NAME                             USB_SS3_TC1   /*!< Pin name */
#define BOARD_INITPINS_I2C1_SCL_PIN_FUNCTION_ID                 SC_P_USB_SS3_TC1   /*!< Pin function id */
#define BOARD_INITPINS_I2C1_SCL_LABEL                        "I2C1_SCL(SS3_SCL)"   /*!< Label */
#define BOARD_INITPINS_I2C1_SCL_NAME                                  "I2C1_SCL"   /*!< Identifier name */

/* USB_SS3_TC3 (coord C15), I2C1_SDA(SS3_SDA) */
#define BOARD_INITPINS_I2C1_SDA_PERIPHERAL                            ADMA__I2C1   /*!< Device name: ADMA__I2C1 */
#define BOARD_INITPINS_I2C1_SDA_SIGNAL                                   i2c_sda   /*!< ADMA__I2C1 signal: i2c_sda */
#define BOARD_INITPINS_I2C1_SDA_PIN_NAME                             USB_SS3_TC3   /*!< Pin name */
#define BOARD_INITPINS_I2C1_SDA_PIN_FUNCTION_ID                 SC_P_USB_SS3_TC3   /*!< Pin function id */
#define BOARD_INITPINS_I2C1_SDA_LABEL                        "I2C1_SDA(SS3_SDA)"   /*!< Label */
#define BOARD_INITPINS_I2C1_SDA_NAME                                  "I2C1_SDA"   /*!< Identifier name */

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
