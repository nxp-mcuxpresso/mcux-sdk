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

/* SPI2_SCK (number AW5), BB_SPI2_SCLK/J20B[18] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_SPI2_SCLK_PERIPHERAL                       LSIO__GPIO3   /*!< Peripheral name */
#define BOARD_INITPINS_BB_SPI2_SCLK_SIGNAL                               gpio_io   /*!< Signal name */
#define BOARD_INITPINS_BB_SPI2_SCLK_CHANNEL                                   07   /*!< Signal channel */
#define BOARD_INITPINS_BB_SPI2_SCLK_PIN_NAME                            SPI2_SCK   /*!< Routed pin name */
#define BOARD_INITPINS_BB_SPI2_SCLK_PIN_FUNCTION_ID                SC_P_SPI2_SCK   /*!< Pin function id */
#define BOARD_INITPINS_BB_SPI2_SCLK_LABEL                "BB_SPI2_SCLK/J20B[18]"   /*!< Label */
#define BOARD_INITPINS_BB_SPI2_SCLK_NAME                          "BB_SPI2_SCLK"   /*!< Identifier */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_BB_SPI2_SCLK_GPIO                             LSIO__GPIO3   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_BB_SPI2_SCLK_GPIO_PIN                                  7U   /*!< GPIO pin number */
#define BOARD_INITPINS_BB_SPI2_SCLK_GPIO_PIN_MASK                     (1U << 7U)   /*!< GPIO pin mask */

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
