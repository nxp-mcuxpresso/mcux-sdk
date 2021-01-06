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

/* MIPI_DSI0_I2C0_SCL (number AC31), MIPI_DSI0_I2C_SCL */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_PERIPHERAL              MIPI_DSI0__I2C0   /*!< Device name: MIPI_DSI0__I2C0 */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_SIGNAL                          i2c_scl   /*!< MIPI_DSI0__I2C0 signal: i2c_scl */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_PIN_NAME             MIPI_DSI0_I2C0_SCL   /*!< Pin name */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_PIN_FUNCTION_ID SC_P_MIPI_DSI0_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_LABEL               "MIPI_DSI0_I2C_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SCL_NAME                "MIPI_DSI0_I2C_SCL"   /*!< Identifier name */

/* MIPI_DSI0_I2C0_SDA (number AB28), MIPI_DSI0_I2C_SDA */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_PERIPHERAL              MIPI_DSI0__I2C0   /*!< Device name: MIPI_DSI0__I2C0 */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_SIGNAL                          i2c_sda   /*!< MIPI_DSI0__I2C0 signal: i2c_sda */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_PIN_NAME             MIPI_DSI0_I2C0_SDA   /*!< Pin name */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_PIN_FUNCTION_ID SC_P_MIPI_DSI0_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_LABEL               "MIPI_DSI0_I2C_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI0_I2C_SDA_NAME                "MIPI_DSI0_I2C_SDA"   /*!< Identifier name */

/* MIPI_DSI1_I2C0_SCL (number AE33), MIPI_DSI1_I2C_SCL */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_PERIPHERAL              MIPI_DSI1__I2C0   /*!< Device name: MIPI_DSI1__I2C0 */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_SIGNAL                          i2c_scl   /*!< MIPI_DSI1__I2C0 signal: i2c_scl */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_PIN_NAME             MIPI_DSI1_I2C0_SCL   /*!< Pin name */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_PIN_FUNCTION_ID SC_P_MIPI_DSI1_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_LABEL               "MIPI_DSI1_I2C_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SCL_NAME                "MIPI_DSI1_I2C_SCL"   /*!< Identifier name */

/* MIPI_DSI1_I2C0_SDA (number AC29), MIPI_DSI1_I2C_SDA */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_PERIPHERAL              MIPI_DSI1__I2C0   /*!< Device name: MIPI_DSI1__I2C0 */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_SIGNAL                          i2c_sda   /*!< MIPI_DSI1__I2C0 signal: i2c_sda */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_PIN_NAME             MIPI_DSI1_I2C0_SDA   /*!< Pin name */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_PIN_FUNCTION_ID SC_P_MIPI_DSI1_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_LABEL               "MIPI_DSI1_I2C_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI1_I2C_SDA_NAME                "MIPI_DSI1_I2C_SDA"   /*!< Identifier name */

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

/* CSI_D00 (number AK28), BB_CSI_D0(TAMP_OUT0)/J13E[40] */
#define BOARD_INITPINS_BB_CSI_D0_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D0_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D0_CHANNEL                                      02   /*!< CI_PI__CSI csi_d channel: 02 */
#define BOARD_INITPINS_BB_CSI_D0_PIN_NAME                                CSI_D00   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D0_PIN_FUNCTION_ID                    SC_P_CSI_D00   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D0_LABEL           "BB_CSI_D0(TAMP_OUT0)/J13E[40]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D0_NAME                                "BB_CSI_D0"   /*!< Identifier name */

/* CSI_D01 (number AL29), BB_CSI_D1(TAMP_OUT1)/J13E[41] */
#define BOARD_INITPINS_BB_CSI_D1_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D1_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D1_CHANNEL                                      03   /*!< CI_PI__CSI csi_d channel: 03 */
#define BOARD_INITPINS_BB_CSI_D1_PIN_NAME                                CSI_D01   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D1_PIN_FUNCTION_ID                    SC_P_CSI_D01   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D1_LABEL           "BB_CSI_D1(TAMP_OUT1)/J13E[41]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D1_NAME                                "BB_CSI_D1"   /*!< Identifier name */

/* CSI_D02 (number AP30), BB_CSI_D2(TAMP_OUT2)/J13C[50] */
#define BOARD_INITPINS_BB_CSI_D2_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D2_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D2_CHANNEL                                      04   /*!< CI_PI__CSI csi_d channel: 04 */
#define BOARD_INITPINS_BB_CSI_D2_PIN_NAME                                CSI_D02   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D2_PIN_FUNCTION_ID                    SC_P_CSI_D02   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D2_LABEL           "BB_CSI_D2(TAMP_OUT2)/J13C[50]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D2_NAME                                "BB_CSI_D2"   /*!< Identifier name */

/* CSI_D03 (number AJ27), BB_CSI_D3(TAMP_OUT3)/J13E[43] */
#define BOARD_INITPINS_BB_CSI_D3_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D3_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D3_CHANNEL                                      05   /*!< CI_PI__CSI csi_d channel: 05 */
#define BOARD_INITPINS_BB_CSI_D3_PIN_NAME                                CSI_D03   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D3_PIN_FUNCTION_ID                    SC_P_CSI_D03   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D3_LABEL           "BB_CSI_D3(TAMP_OUT3)/J13E[43]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D3_NAME                                "BB_CSI_D3"   /*!< Identifier name */

/* CSI_D04 (number AN29), BB_CSI_D4(TAMP_OUT4)/J13E[44] */
#define BOARD_INITPINS_BB_CSI_D4_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D4_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D4_CHANNEL                                      06   /*!< CI_PI__CSI csi_d channel: 06 */
#define BOARD_INITPINS_BB_CSI_D4_PIN_NAME                                CSI_D04   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D4_PIN_FUNCTION_ID                    SC_P_CSI_D04   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D4_LABEL           "BB_CSI_D4(TAMP_OUT4)/J13E[44]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D4_NAME                                "BB_CSI_D4"   /*!< Identifier name */

/* CSI_D05 (number AM30), BB_CSI_D5(TAMP_IN0)/J13E[46] */
#define BOARD_INITPINS_BB_CSI_D5_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D5_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D5_CHANNEL                                      07   /*!< CI_PI__CSI csi_d channel: 07 */
#define BOARD_INITPINS_BB_CSI_D5_PIN_NAME                                CSI_D05   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D5_PIN_FUNCTION_ID                    SC_P_CSI_D05   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D5_LABEL            "BB_CSI_D5(TAMP_IN0)/J13E[46]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D5_NAME                                "BB_CSI_D5"   /*!< Identifier name */

/* CSI_D06 (number AJ25), BB_CSI_D6(TAMP_IN1)/J13E[47] */
#define BOARD_INITPINS_BB_CSI_D6_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D6_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D6_CHANNEL                                      08   /*!< CI_PI__CSI csi_d channel: 08 */
#define BOARD_INITPINS_BB_CSI_D6_PIN_NAME                                CSI_D06   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D6_PIN_FUNCTION_ID                    SC_P_CSI_D06   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D6_LABEL            "BB_CSI_D6(TAMP_IN1)/J13E[47]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D6_NAME                                "BB_CSI_D6"   /*!< Identifier name */

/* CSI_D07 (number AM28), BB_CSI_D7(TAMP_IN2)/J13B[32] */
#define BOARD_INITPINS_BB_CSI_D7_PERIPHERAL                           CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_D7_SIGNAL                                    csi_d   /*!< CI_PI__CSI signal: csi_d */
#define BOARD_INITPINS_BB_CSI_D7_CHANNEL                                      09   /*!< CI_PI__CSI csi_d channel: 09 */
#define BOARD_INITPINS_BB_CSI_D7_PIN_NAME                                CSI_D07   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_D7_PIN_FUNCTION_ID                    SC_P_CSI_D07   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_D7_LABEL            "BB_CSI_D7(TAMP_IN2)/J13B[32]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_D7_NAME                                "BB_CSI_D7"   /*!< Identifier name */

/* CSI_PCLK (number AK26), BB_CSI_PCLK/J13C[47] */
#define BOARD_INITPINS_BB_CSI_PCLK_PERIPHERAL                         CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_PCLK_SIGNAL                               csi_pclk   /*!< CI_PI__CSI signal: csi_pclk */
#define BOARD_INITPINS_BB_CSI_PCLK_PIN_NAME                             CSI_PCLK   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_PCLK_PIN_FUNCTION_ID                 SC_P_CSI_PCLK   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_PCLK_LABEL                  "BB_CSI_PCLK/J13C[47]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_PCLK_NAME                            "BB_CSI_PCLK"   /*!< Identifier name */

/* CSI_MCLK (number AM26), BB_CSI_MCLK/J13E[38] */
#define BOARD_INITPINS_BB_CSI_MCLK_PERIPHERAL                         CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_MCLK_SIGNAL                               csi_mclk   /*!< CI_PI__CSI signal: csi_mclk */
#define BOARD_INITPINS_BB_CSI_MCLK_PIN_NAME                             CSI_MCLK   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_MCLK_PIN_FUNCTION_ID                 SC_P_CSI_MCLK   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_MCLK_LABEL                  "BB_CSI_MCLK/J13E[38]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_MCLK_NAME                            "BB_CSI_MCLK"   /*!< Identifier name */

/* CSI_HSYNC (number AR29), BB_CSI_HSYNC(TAMP_IN3)/J13B[33] */
#define BOARD_INITPINS_BB_CSI_HSYNC_PERIPHERAL                        CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_HSYNC_SIGNAL                             csi_hsync   /*!< CI_PI__CSI signal: csi_hsync */
#define BOARD_INITPINS_BB_CSI_HSYNC_PIN_NAME                           CSI_HSYNC   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_HSYNC_PIN_FUNCTION_ID               SC_P_CSI_HSYNC   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_HSYNC_LABEL      "BB_CSI_HSYNC(TAMP_IN3)/J13B[33]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_HSYNC_NAME                          "BB_CSI_HSYNC"   /*!< Identifier name */

/* CSI_VSYNC (number AL27), BB_CSI_VSYNC(TAMP_IN4)/J13E[49] */
#define BOARD_INITPINS_BB_CSI_VSYNC_PERIPHERAL                        CI_PI__CSI   /*!< Device name: CI_PI__CSI */
#define BOARD_INITPINS_BB_CSI_VSYNC_SIGNAL                             csi_vsync   /*!< CI_PI__CSI signal: csi_vsync */
#define BOARD_INITPINS_BB_CSI_VSYNC_PIN_NAME                           CSI_VSYNC   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_VSYNC_PIN_FUNCTION_ID               SC_P_CSI_VSYNC   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_VSYNC_LABEL      "BB_CSI_VSYNC(TAMP_IN4)/J13E[49]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_VSYNC_NAME                          "BB_CSI_VSYNC"   /*!< Identifier name */

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

/* CSI_RESET (number AR27), BB_CSI_RST_B/J13E[37] */
#define BOARD_INITPINS_BB_CSI_RST_B_GPIO                             LSIO__GPIO3   /*!< GPIO device name: LSIO__GPIO3 */
#define BOARD_INITPINS_BB_CSI_RST_B_GPIO_PIN                                  3U   /*!< LSIO__GPIO3 pin index: 3 */
#define BOARD_INITPINS_BB_CSI_RST_B_PIN_NAME                           CSI_RESET   /*!< Pin name */
#define BOARD_INITPINS_BB_CSI_RST_B_PIN_FUNCTION_ID               SC_P_CSI_RESET   /*!< Pin function id */
#define BOARD_INITPINS_BB_CSI_RST_B_LABEL                "BB_CSI_RST_B/J13E[37]"   /*!< Label */
#define BOARD_INITPINS_BB_CSI_RST_B_NAME                          "BB_CSI_RST_B"   /*!< Identifier name */

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
