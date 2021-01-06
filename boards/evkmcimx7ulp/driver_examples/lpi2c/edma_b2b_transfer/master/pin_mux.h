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

/* PTB12 (number AC8), I2C3_SCL */
/* Routed pin properties */
#define BOARD_I2C3_SCL_PERIPHERAL                                         LPI2C3   /*!< Peripheral name */
#define BOARD_I2C3_SCL_SIGNAL                                          lpi2c_scl   /*!< Signal name */
#define BOARD_I2C3_SCL_PIN_NAME                                            PTB12   /*!< Routed pin name */
#define BOARD_I2C3_SCL_PIN_FUNCTION_ID                   IOMUXC_PTB12_LPI2C3_SCL   /*!< Pin function id */
#define BOARD_I2C3_SCL_LABEL                                          "I2C3_SCL"   /*!< Label */
#define BOARD_I2C3_SCL_NAME                                           "I2C3_SCL"   /*!< Identifier */

/* PTB13 (number AD8), I2C3_SDA */
/* Routed pin properties */
#define BOARD_I2C3_SDA_PERIPHERAL                                         LPI2C3   /*!< Peripheral name */
#define BOARD_I2C3_SDA_SIGNAL                                          lpi2c_sda   /*!< Signal name */
#define BOARD_I2C3_SDA_PIN_NAME                                            PTB13   /*!< Routed pin name */
#define BOARD_I2C3_SDA_PIN_FUNCTION_ID                   IOMUXC_PTB13_LPI2C3_SDA   /*!< Pin function id */
#define BOARD_I2C3_SDA_LABEL                                          "I2C3_SDA"   /*!< Label */
#define BOARD_I2C3_SDA_NAME                                           "I2C3_SDA"   /*!< Identifier */

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
