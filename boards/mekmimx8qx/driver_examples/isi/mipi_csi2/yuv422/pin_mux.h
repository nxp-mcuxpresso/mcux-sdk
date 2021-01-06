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

/* MIPI_CSI0_GPIO0_00 (number AR25), MIPI_CSI0_RST# */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_GPIO                     MIPI_CSI0__GPIO0   /*!< GPIO device name: MIPI_CSI0__GPIO0 */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_GPIO_PIN                               0U   /*!< MIPI_CSI0__GPIO0 pin index: 0 */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_PIN_NAME               MIPI_CSI0_GPIO0_00   /*!< Pin name */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_PIN_FUNCTION_ID   SC_P_MIPI_CSI0_GPIO0_00   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_LABEL                    "MIPI_CSI0_RST#"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_NAME                    "MIPI_CSI0_RST_B"   /*!< Identifier name */

/* MIPI_CSI0_GPIO0_01 (number AP24), MIPI_CSI0_EN */
#define BOARD_INITPINS_MIPI_CSI0_EN_GPIO                        MIPI_CSI0__GPIO0   /*!< GPIO device name: MIPI_CSI0__GPIO0 */
#define BOARD_INITPINS_MIPI_CSI0_EN_GPIO_PIN                                  1U   /*!< MIPI_CSI0__GPIO0 pin index: 1 */
#define BOARD_INITPINS_MIPI_CSI0_EN_PIN_NAME                  MIPI_CSI0_GPIO0_01   /*!< Pin name */
#define BOARD_INITPINS_MIPI_CSI0_EN_PIN_FUNCTION_ID      SC_P_MIPI_CSI0_GPIO0_01   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_EN_LABEL                         "MIPI_CSI0_EN"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_EN_NAME                          "MIPI_CSI0_EN"   /*!< Identifier name */

/* MIPI_CSI0_I2C0_SCL (number AP26), MIPI_CSI0_I2C0_SCL */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PERIPHERAL             MIPI_CSI0__I2C0   /*!< Device name: MIPI_CSI0__I2C0 */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_SIGNAL                         i2c_scl   /*!< MIPI_CSI0__I2C0 signal: i2c_scl */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PIN_NAME            MIPI_CSI0_I2C0_SCL   /*!< Pin name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PIN_FUNCTION_ID SC_P_MIPI_CSI0_I2C0_SCL  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_LABEL             "MIPI_CSI0_I2C0_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_NAME              "MIPI_CSI0_I2C0_SCL"   /*!< Identifier name */

/* MIPI_CSI0_I2C0_SDA (number AM24), MIPI_CSI0_I2C0_SDA */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PERIPHERAL             MIPI_CSI0__I2C0   /*!< Device name: MIPI_CSI0__I2C0 */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_SIGNAL                         i2c_sda   /*!< MIPI_CSI0__I2C0 signal: i2c_sda */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PIN_NAME            MIPI_CSI0_I2C0_SDA   /*!< Pin name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PIN_FUNCTION_ID SC_P_MIPI_CSI0_I2C0_SDA  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_LABEL             "MIPI_CSI0_I2C0_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_NAME              "MIPI_CSI0_I2C0_SDA"   /*!< Identifier name */

/* MIPI_CSI0_MCLK_OUT (number AN25), MIPI_CSI0_MCLK_OUT */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PERIPHERAL              MIPI_CSI0__ACM   /*!< Device name: MIPI_CSI0__ACM */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_SIGNAL                        mclk_out   /*!< MIPI_CSI0__ACM signal: mclk_out */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PIN_NAME            MIPI_CSI0_MCLK_OUT   /*!< Pin name */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PIN_FUNCTION_ID SC_P_MIPI_CSI0_MCLK_OUT  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_LABEL             "MIPI_CSI0_MCLK_OUT"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_NAME              "MIPI_CSI0_MCLK_OUT"   /*!< Identifier name */

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
