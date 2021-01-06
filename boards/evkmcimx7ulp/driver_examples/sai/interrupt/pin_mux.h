/*
 * Copyright 2020 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* PTA19 (number AB19), UART0_RX */
/* Routed pin properties */
#define BOARD_UART0_RX_PERIPHERAL                                        LPUART0   /*!< Peripheral name */
#define BOARD_UART0_RX_SIGNAL                                          lpuart_rx   /*!< Signal name */
#define BOARD_UART0_RX_PIN_NAME                                            PTA19   /*!< Routed pin name */
#define BOARD_UART0_RX_PIN_FUNCTION_ID                   IOMUXC_PTA19_LPUART0_RX   /*!< Pin function id */
#define BOARD_UART0_RX_LABEL                                          "UART0_RX"   /*!< Label */
#define BOARD_UART0_RX_NAME                                           "UART0_RX"   /*!< Identifier */

/* PTA18 (number AC19), UART0_TX */
/* Routed pin properties */
#define BOARD_UART0_TX_PERIPHERAL                                        LPUART0   /*!< Peripheral name */
#define BOARD_UART0_TX_SIGNAL                                          lpuart_tx   /*!< Signal name */
#define BOARD_UART0_TX_PIN_NAME                                            PTA18   /*!< Routed pin name */
#define BOARD_UART0_TX_PIN_FUNCTION_ID                   IOMUXC_PTA18_LPUART0_TX   /*!< Pin function id */
#define BOARD_UART0_TX_LABEL                                          "UART0_TX"   /*!< Label */
#define BOARD_UART0_TX_NAME                                           "UART0_TX"   /*!< Identifier */

/* PTA4 (number AD15), I2S0_MCLK */
/* Routed pin properties */
#define BOARD_I2S0_MCLK_PERIPHERAL                                          I2S0   /*!< Peripheral name */
#define BOARD_I2S0_MCLK_SIGNAL                                          i2s_mclk   /*!< Signal name */
#define BOARD_I2S0_MCLK_PIN_NAME                                            PTA4   /*!< Routed pin name */
#define BOARD_I2S0_MCLK_PIN_FUNCTION_ID                    IOMUXC_PTA4_I2S0_MCLK   /*!< Pin function id */
#define BOARD_I2S0_MCLK_LABEL                                        "I2S0_MCLK"   /*!< Label */
#define BOARD_I2S0_MCLK_NAME                                         "I2S0_MCLK"   /*!< Identifier */

/* PTA5 (number AC15), I2S0_TX_BCLK */
/* Routed pin properties */
#define BOARD_I2S0_TX_BCLK_PERIPHERAL                                       I2S0   /*!< Peripheral name */
#define BOARD_I2S0_TX_BCLK_SIGNAL                                    i2s_tx_bclk   /*!< Signal name */
#define BOARD_I2S0_TX_BCLK_PIN_NAME                                         PTA5   /*!< Routed pin name */
#define BOARD_I2S0_TX_BCLK_PIN_FUNCTION_ID              IOMUXC_PTA5_I2S0_TX_BCLK   /*!< Pin function id */
#define BOARD_I2S0_TX_BCLK_LABEL                                  "I2S0_TX_BCLK"   /*!< Label */
#define BOARD_I2S0_TX_BCLK_NAME                                   "I2S0_TX_BCLK"   /*!< Identifier */

/* PTA6 (number AB15), I2S0_TX_FS */
/* Routed pin properties */
#define BOARD_I2S0_TX_FS_PERIPHERAL                                         I2S0   /*!< Peripheral name */
#define BOARD_I2S0_TX_FS_SIGNAL                                        i2s_tx_fs   /*!< Signal name */
#define BOARD_I2S0_TX_FS_PIN_NAME                                           PTA6   /*!< Routed pin name */
#define BOARD_I2S0_TX_FS_PIN_FUNCTION_ID                  IOMUXC_PTA6_I2S0_TX_FS   /*!< Pin function id */
#define BOARD_I2S0_TX_FS_LABEL                                      "I2S0_TX_FS"   /*!< Label */
#define BOARD_I2S0_TX_FS_NAME                                       "I2S0_TX_FS"   /*!< Identifier */

/* PTA7 (number AD14), I2S0_TXD0 */
/* Routed pin properties */
#define BOARD_I2S0_TXD0_PERIPHERAL                                          I2S0   /*!< Peripheral name */
#define BOARD_I2S0_TXD0_SIGNAL                                           i2s_txd   /*!< Signal name */
#define BOARD_I2S0_TXD0_CHANNEL                                                0   /*!< Signal channel */
#define BOARD_I2S0_TXD0_PIN_NAME                                            PTA7   /*!< Routed pin name */
#define BOARD_I2S0_TXD0_PIN_FUNCTION_ID                    IOMUXC_PTA7_I2S0_TXD0   /*!< Pin function id */
#define BOARD_I2S0_TXD0_LABEL                                        "I2S0_TXD0"   /*!< Label */
#define BOARD_I2S0_TXD0_NAME                                         "I2S0_TXD0"   /*!< Identifier */

/* PTA2 (number AG14), I2S0_RXD0 */
/* Routed pin properties */
#define BOARD_I2S0_RXD0_PERIPHERAL                                          I2S0   /*!< Peripheral name */
#define BOARD_I2S0_RXD0_SIGNAL                                           i2s_rxd   /*!< Signal name */
#define BOARD_I2S0_RXD0_CHANNEL                                                0   /*!< Signal channel */
#define BOARD_I2S0_RXD0_PIN_NAME                                            PTA2   /*!< Routed pin name */
#define BOARD_I2S0_RXD0_PIN_FUNCTION_ID                    IOMUXC_PTA2_I2S0_RXD0   /*!< Pin function id */
#define BOARD_I2S0_RXD0_LABEL                                        "I2S0_RXD0"   /*!< Label */
#define BOARD_I2S0_RXD0_NAME                                         "I2S0_RXD0"   /*!< Identifier */

/* PTA16 (number AG18), I2C0_SCL */
/* Routed pin properties */
#define BOARD_I2C0_SCL_PERIPHERAL                                         LPI2C0   /*!< Peripheral name */
#define BOARD_I2C0_SCL_SIGNAL                                          lpi2c_scl   /*!< Signal name */
#define BOARD_I2C0_SCL_PIN_NAME                                            PTA16   /*!< Routed pin name */
#define BOARD_I2C0_SCL_PIN_FUNCTION_ID                   IOMUXC_PTA16_LPI2C0_SCL   /*!< Pin function id */
#define BOARD_I2C0_SCL_LABEL                                          "I2C0_SCL"   /*!< Label */
#define BOARD_I2C0_SCL_NAME                                           "I2C0_SCL"   /*!< Identifier */

/* PTA17 (number AD19), I2C0_SDA */
/* Routed pin properties */
#define BOARD_I2C0_SDA_PERIPHERAL                                         LPI2C0   /*!< Peripheral name */
#define BOARD_I2C0_SDA_SIGNAL                                          lpi2c_sda   /*!< Signal name */
#define BOARD_I2C0_SDA_PIN_NAME                                            PTA17   /*!< Routed pin name */
#define BOARD_I2C0_SDA_PIN_FUNCTION_ID                   IOMUXC_PTA17_LPI2C0_SDA   /*!< Pin function id */
#define BOARD_I2C0_SDA_LABEL                                          "I2C0_SDA"   /*!< Label */
#define BOARD_I2C0_SDA_NAME                                           "I2C0_SDA"   /*!< Identifier */

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
 *
 */
void BOARD_InitPins(void);                                 /*!< Function assigned for the core: Cortex-M4[cm4] */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_I2C_ConfigurePins(void);                        /*!< Function assigned for the core: Cortex-M4[cm4] */

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
