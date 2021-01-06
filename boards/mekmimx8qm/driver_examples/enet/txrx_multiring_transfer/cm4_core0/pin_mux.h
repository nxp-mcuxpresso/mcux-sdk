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

/* M40_I2C0_SCL (number AM44), FTDI_M40_UART0_RX */
/* Routed pin properties */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PERIPHERAL                   M40__UART0   /*!< Peripheral name */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_SIGNAL                          uart_rx   /*!< Signal name */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PIN_NAME                   M40_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_PIN_FUNCTION_ID       SC_P_M40_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_LABEL               "FTDI_M40_UART0_RX"   /*!< Label */
#define BOARD_INITPINS_FTDI_M40_UART0_RX_NAME                "FTDI_M40_UART0_RX"   /*!< Identifier */

/* M40_I2C0_SDA (number AU51), FTDI_M40_UART0_TX */
/* Routed pin properties */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PERIPHERAL                   M40__UART0   /*!< Peripheral name */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_SIGNAL                          uart_tx   /*!< Signal name */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PIN_NAME                   M40_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_PIN_FUNCTION_ID       SC_P_M40_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_LABEL               "FTDI_M40_UART0_TX"   /*!< Label */
#define BOARD_INITPINS_FTDI_M40_UART0_TX_NAME                "FTDI_M40_UART0_TX"   /*!< Identifier */

/* ENET0_MDC (coord A9), ENET0_MDC */
/* Routed pin properties */
#define BOARD_INITPINS_ENET0_MDC_PERIPHERAL                          CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ENET0_MDC_SIGNAL                                 enet_mdc   /*!< Signal name */
#define BOARD_INITPINS_ENET0_MDC_PIN_NAME                              ENET0_MDC   /*!< Routed pin name */
#define BOARD_INITPINS_ENET0_MDC_PIN_FUNCTION_ID                  SC_P_ENET0_MDC   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_MDC_LABEL                               "ENET0_MDC"   /*!< Label */
#define BOARD_INITPINS_ENET0_MDC_NAME                                "ENET0_MDC"   /*!< Identifier */

/* ENET0_MDIO (coord D10), ENET0_MDIO */
/* Routed pin properties */
#define BOARD_INITPINS_ENET0_MDIO_PERIPHERAL                         CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ENET0_MDIO_SIGNAL                               enet_mdio   /*!< Signal name */
#define BOARD_INITPINS_ENET0_MDIO_PIN_NAME                            ENET0_MDIO   /*!< Routed pin name */
#define BOARD_INITPINS_ENET0_MDIO_PIN_FUNCTION_ID                SC_P_ENET0_MDIO   /*!< Pin function id */
#define BOARD_INITPINS_ENET0_MDIO_LABEL                             "ENET0_MDIO"   /*!< Label */
#define BOARD_INITPINS_ENET0_MDIO_NAME                              "ENET0_MDIO"   /*!< Identifier */

/* ENET0_REFCLK_125M_25M (coord B10), BB_ARD_MIK_RST_B/J20D[41] */
/* Routed pin properties */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_PERIPHERAL                   CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_SIGNAL              enet_refclk_125m_25m   /*!< Signal name */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_PIN_NAME           ENET0_REFCLK_125M_25M   /*!< Routed pin name */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_PIN_FUNCTION_ID SC_P_ENET0_REFCLK_125M_25M /*!< Pin function id */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_LABEL        "BB_ARD_MIK_RST_B/J20D[41]"   /*!< Label */
#define BOARD_INITPINS_BB_ARD_MIK_RST_B_NAME                  "BB_ARD_MIK_RST_B"   /*!< Identifier */

/* ENET0_RGMII_RX_CTL (coord E43), ETH0_RGMII_RX_CTL */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_PERIPHERAL                  CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_SIGNAL                enet_rgmii_rx_ctl   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_PIN_NAME             ENET0_RGMII_RX_CTL   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_PIN_FUNCTION_ID SC_P_ENET0_RGMII_RX_CTL   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_LABEL               "ETH0_RGMII_RX_CTL"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RX_CTL_NAME                "ETH0_RGMII_RX_CTL"   /*!< Identifier */

/* ENET0_RGMII_RXC (coord B44), ETH0_RGMII_RXC */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RXC_PERIPHERAL                     CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RXC_SIGNAL                      enet_rgmii_rxc   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RXC_PIN_NAME                   ENET0_RGMII_RXC   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RXC_PIN_FUNCTION_ID       SC_P_ENET0_RGMII_RXC   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RXC_LABEL                     "ETH0_RGMII_RXC"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RXC_NAME                      "ETH0_RGMII_RXC"   /*!< Identifier */

/* ENET0_RGMII_RXD0 (coord A47), ETH0_RGMII_RXD0 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_SIGNAL                     enet_rgmii_rxd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_CHANNEL                                 0   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_PIN_NAME                 ENET0_RGMII_RXD0   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_RXD0   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_LABEL                   "ETH0_RGMII_RXD0"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RXD0_NAME                    "ETH0_RGMII_RXD0"   /*!< Identifier */

/* ENET0_RGMII_RXD1 (coord D44), ETH0_RGMII_RXD1 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_SIGNAL                     enet_rgmii_rxd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_CHANNEL                                 1   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_PIN_NAME                 ENET0_RGMII_RXD1   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_RXD1   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_LABEL                   "ETH0_RGMII_RXD1"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RXD1_NAME                    "ETH0_RGMII_RXD1"   /*!< Identifier */

/* ENET0_RGMII_RXD2 (coord C45), ETH0_RGMII_RXD2 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_SIGNAL                     enet_rgmii_rxd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_CHANNEL                                 2   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_PIN_NAME                 ENET0_RGMII_RXD2   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_RXD2   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_LABEL                   "ETH0_RGMII_RXD2"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RXD2_NAME                    "ETH0_RGMII_RXD2"   /*!< Identifier */

/* ENET0_RGMII_RXD3 (coord E45), ETH0_RGMII_RXD3 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_SIGNAL                     enet_rgmii_rxd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_CHANNEL                                 3   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_PIN_NAME                 ENET0_RGMII_RXD3   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_RXD3   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_LABEL                   "ETH0_RGMII_RXD3"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_RXD3_NAME                    "ETH0_RGMII_RXD3"   /*!< Identifier */

/* ENET0_RGMII_TX_CTL (coord E41), ETH0_RGMII_TX_CTL */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_PERIPHERAL                  CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_SIGNAL                enet_rgmii_tx_ctl   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_PIN_NAME             ENET0_RGMII_TX_CTL   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_PIN_FUNCTION_ID SC_P_ENET0_RGMII_TX_CTL   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_LABEL               "ETH0_RGMII_TX_CTL"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TX_CTL_NAME                "ETH0_RGMII_TX_CTL"   /*!< Identifier */

/* ENET0_RGMII_TXC (coord A41), ETH0_RGMII_TXC */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TXC_PERIPHERAL                     CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TXC_SIGNAL                      enet_rgmii_txc   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TXC_PIN_NAME                   ENET0_RGMII_TXC   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TXC_PIN_FUNCTION_ID       SC_P_ENET0_RGMII_TXC   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TXC_LABEL                     "ETH0_RGMII_TXC"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TXC_NAME                      "ETH0_RGMII_TXC"   /*!< Identifier */

/* ENET0_RGMII_TXD0 (coord A43), ETH0_RGMII_TXD0 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_SIGNAL                     enet_rgmii_txd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_CHANNEL                                 0   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_PIN_NAME                 ENET0_RGMII_TXD0   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_TXD0   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_LABEL                   "ETH0_RGMII_TXD0"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TXD0_NAME                    "ETH0_RGMII_TXD0"   /*!< Identifier */

/* ENET0_RGMII_TXD1 (coord B42), ETH0_RGMII_TXD1 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_SIGNAL                     enet_rgmii_txd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_CHANNEL                                 1   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_PIN_NAME                 ENET0_RGMII_TXD1   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_TXD1   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_LABEL                   "ETH0_RGMII_TXD1"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TXD1_NAME                    "ETH0_RGMII_TXD1"   /*!< Identifier */

/* ENET0_RGMII_TXD2 (coord A45), ETH0_RGMII_TXD2 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_SIGNAL                     enet_rgmii_txd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_CHANNEL                                 2   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_PIN_NAME                 ENET0_RGMII_TXD2   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_TXD2   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_LABEL                   "ETH0_RGMII_TXD2"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TXD2_NAME                    "ETH0_RGMII_TXD2"   /*!< Identifier */

/* ENET0_RGMII_TXD3 (coord D42), ETH0_RGMII_TXD3 */
/* Routed pin properties */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_PERIPHERAL                    CONN__ENET0   /*!< Peripheral name */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_SIGNAL                     enet_rgmii_txd   /*!< Signal name */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_CHANNEL                                 3   /*!< Signal channel */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_PIN_NAME                 ENET0_RGMII_TXD3   /*!< Routed pin name */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_PIN_FUNCTION_ID     SC_P_ENET0_RGMII_TXD3   /*!< Pin function id */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_LABEL                   "ETH0_RGMII_TXD3"   /*!< Label */
#define BOARD_INITPINS_ETH0_RGMII_TXD3_NAME                    "ETH0_RGMII_TXD3"   /*!< Identifier */

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
void BOARD_InitPins(sc_ipc_t ipc);                         /*!< Function assigned for the core: Cortex-M4F[cm4_core0] */

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
