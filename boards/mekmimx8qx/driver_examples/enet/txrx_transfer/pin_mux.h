/*
 * Copyright 2020 NXP
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

/* ENET0_MDC (coord D30), ENET0_MDC */
#define BOARD_INITPINS_ENET0_MDC_PERIPHERAL                          CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_MDC_SIGNAL                                 enet_mdc   /*!< CONN__ENET0 signal: enet_mdc */
#define BOARD_INITPINS_ENET0_MDC_PIN_NAME                              ENET0_MDC   /*!< Pin name */
#define BOARD_INITPINS_ENET0_MDC_PIN_FUNCTION_ID                  SC_P_ENET0_MDC   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_MDC_LABEL                               "ENET0_MDC"   /*!< Label */
#define BOARD_INITPINS_ENET0_MDC_NAME                                "ENET0_MDC"   /*!< Identifier name */

/* ENET0_MDIO (coord B32), ENET0_MDIO */
#define BOARD_INITPINS_ENET0_MDIO_PERIPHERAL                         CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_MDIO_SIGNAL                               enet_mdio   /*!< CONN__ENET0 signal: enet_mdio */
#define BOARD_INITPINS_ENET0_MDIO_PIN_NAME                            ENET0_MDIO   /*!< Pin name */
#define BOARD_INITPINS_ENET0_MDIO_PIN_FUNCTION_ID                SC_P_ENET0_MDIO   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_MDIO_LABEL                             "ENET0_MDIO"   /*!< Label */
#define BOARD_INITPINS_ENET0_MDIO_NAME                              "ENET0_MDIO"   /*!< Identifier name */

/* ENET0_REFCLK_125M_25M (coord F28), USB_TYPEC_CROSS */
#define BOARD_INITPINS_USB_TYPEC_CROSS_PERIPHERAL                    CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_USB_TYPEC_CROSS_SIGNAL               enet_refclk_125m_25m   /*!< CONN__ENET0 signal: enet_refclk_125m_25m */
#define BOARD_INITPINS_USB_TYPEC_CROSS_PIN_NAME            ENET0_REFCLK_125M_25M   /*!< Pin name */
#define BOARD_INITPINS_USB_TYPEC_CROSS_PIN_FUNCTION_ID SC_P_ENET0_REFCLK_125M_25M  /*!< Pin function id */
#define BOARD_INITPINS_USB_TYPEC_CROSS_LABEL                   "USB_TYPEC_CROSS"   /*!< Label */
#define BOARD_INITPINS_USB_TYPEC_CROSS_NAME                    "USB_TYPEC_CROSS"   /*!< Identifier name */

/* ENET0_RGMII_RXC (coord D28), ENET0_RGMII_RXC */
#define BOARD_INITPINS_ENET0_RGMII_RXC_PERIPHERAL                    CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RXC_SIGNAL                     enet_rgmii_rxc   /*!< CONN__ENET0 signal: enet_rgmii_rxc */
#define BOARD_INITPINS_ENET0_RGMII_RXC_PIN_NAME                  ENET0_RGMII_RXC   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RXC_PIN_FUNCTION_ID      SC_P_ENET0_RGMII_RXC   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RXC_LABEL                   "ENET0_RGMII_RXC"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RXC_NAME                    "ENET0_RGMII_RXC"   /*!< Identifier name */

/* ENET0_RGMII_RXD0 (coord A31), ENET0_RGMII_RXD0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_SIGNAL                    enet_rgmii_rxd   /*!< CONN__ENET0 signal: enet_rgmii_rxd */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_CHANNEL                                0   /*!< CONN__ENET0 enet_rgmii_rxd channel: 0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_PIN_NAME                ENET0_RGMII_RXD0   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_RXD0   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_LABEL                 "ENET0_RGMII_RXD0"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RXD0_NAME                  "ENET0_RGMII_RXD0"   /*!< Identifier name */

/* ENET0_RGMII_RXD1 (coord C29), ENET0_RGMII_RXD1 */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_SIGNAL                    enet_rgmii_rxd   /*!< CONN__ENET0 signal: enet_rgmii_rxd */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_CHANNEL                                1   /*!< CONN__ENET0 enet_rgmii_rxd channel: 1 */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_PIN_NAME                ENET0_RGMII_RXD1   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_RXD1   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_LABEL                 "ENET0_RGMII_RXD1"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RXD1_NAME                  "ENET0_RGMII_RXD1"   /*!< Identifier name */

/* ENET0_RGMII_RXD2 (coord G27), ENET0_RGMII_RXD2 */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_SIGNAL                    enet_rgmii_rxd   /*!< CONN__ENET0 signal: enet_rgmii_rxd */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_CHANNEL                                2   /*!< CONN__ENET0 enet_rgmii_rxd channel: 2 */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_PIN_NAME                ENET0_RGMII_RXD2   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_RXD2   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_LABEL                 "ENET0_RGMII_RXD2"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RXD2_NAME                  "ENET0_RGMII_RXD2"   /*!< Identifier name */

/* ENET0_RGMII_RXD3 (coord H26), ENET0_RGMII_RXD3 */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_SIGNAL                    enet_rgmii_rxd   /*!< CONN__ENET0 signal: enet_rgmii_rxd */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_CHANNEL                                3   /*!< CONN__ENET0 enet_rgmii_rxd channel: 3 */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_PIN_NAME                ENET0_RGMII_RXD3   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_RXD3   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_LABEL                 "ENET0_RGMII_RXD3"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RXD3_NAME                  "ENET0_RGMII_RXD3"   /*!< Identifier name */

/* ENET0_RGMII_RX_CTL (coord B30), ENET0_RGMII_RX_CTL */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_PERIPHERAL                 CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_SIGNAL               enet_rgmii_rx_ctl   /*!< CONN__ENET0 signal: enet_rgmii_rx_ctl */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_PIN_NAME            ENET0_RGMII_RX_CTL   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_PIN_FUNCTION_ID SC_P_ENET0_RGMII_RX_CTL  /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_LABEL             "ENET0_RGMII_RX_CTL"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_RX_CTL_NAME              "ENET0_RGMII_RX_CTL"   /*!< Identifier name */

/* ENET0_RGMII_TXC (coord H24), ENET0_RGMII_TXC */
#define BOARD_INITPINS_ENET0_RGMII_TXC_PERIPHERAL                    CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TXC_SIGNAL                     enet_rgmii_txc   /*!< CONN__ENET0 signal: enet_rgmii_txc */
#define BOARD_INITPINS_ENET0_RGMII_TXC_PIN_NAME                  ENET0_RGMII_TXC   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TXC_PIN_FUNCTION_ID      SC_P_ENET0_RGMII_TXC   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TXC_LABEL                   "ENET0_RGMII_TXC"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TXC_NAME                    "ENET0_RGMII_TXC"   /*!< Identifier name */

/* ENET0_RGMII_TXD0 (coord G25), ENET0_RGMII_TXD0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_SIGNAL                    enet_rgmii_txd   /*!< CONN__ENET0 signal: enet_rgmii_txd */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_CHANNEL                                0   /*!< CONN__ENET0 enet_rgmii_txd channel: 0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_PIN_NAME                ENET0_RGMII_TXD0   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_TXD0   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_LABEL                 "ENET0_RGMII_TXD0"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TXD0_NAME                  "ENET0_RGMII_TXD0"   /*!< Identifier name */

/* ENET0_RGMII_TXD1 (coord B28), ENET0_RGMII_TXD1 */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_SIGNAL                    enet_rgmii_txd   /*!< CONN__ENET0 signal: enet_rgmii_txd */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_CHANNEL                                1   /*!< CONN__ENET0 enet_rgmii_txd channel: 1 */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_PIN_NAME                ENET0_RGMII_TXD1   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_TXD1   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_LABEL                 "ENET0_RGMII_TXD1"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TXD1_NAME                  "ENET0_RGMII_TXD1"   /*!< Identifier name */

/* ENET0_RGMII_TXD2 (coord E27), ENET0_RGMII_TXD2 */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_SIGNAL                    enet_rgmii_txd   /*!< CONN__ENET0 signal: enet_rgmii_txd */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_CHANNEL                                2   /*!< CONN__ENET0 enet_rgmii_txd channel: 2 */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_PIN_NAME                ENET0_RGMII_TXD2   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_TXD2   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_LABEL                 "ENET0_RGMII_TXD2"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TXD2_NAME                  "ENET0_RGMII_TXD2"   /*!< Identifier name */

/* ENET0_RGMII_TXD3 (coord F26), ENET0_RGMII_TXD3 */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_PERIPHERAL                   CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_SIGNAL                    enet_rgmii_txd   /*!< CONN__ENET0 signal: enet_rgmii_txd */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_CHANNEL                                3   /*!< CONN__ENET0 enet_rgmii_txd channel: 3 */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_PIN_NAME                ENET0_RGMII_TXD3   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_PIN_FUNCTION_ID    SC_P_ENET0_RGMII_TXD3   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_LABEL                 "ENET0_RGMII_TXD3"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TXD3_NAME                  "ENET0_RGMII_TXD3"   /*!< Identifier name */

/* ENET0_RGMII_TX_CTL (coord A29), ENET0_RGMII_TX_CTL */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_PERIPHERAL                 CONN__ENET0   /*!< Device name: CONN__ENET0 */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_SIGNAL               enet_rgmii_tx_ctl   /*!< CONN__ENET0 signal: enet_rgmii_tx_ctl */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_PIN_NAME            ENET0_RGMII_TX_CTL   /*!< Pin name */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_PIN_FUNCTION_ID SC_P_ENET0_RGMII_TX_CTL  /*!< Pin function id */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_LABEL             "ENET0_RGMII_TX_CTL"   /*!< Label */
#define BOARD_INITPINS_ENET0_RGMII_TX_CTL_NAME              "ENET0_RGMII_TX_CTL"   /*!< Identifier name */

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
