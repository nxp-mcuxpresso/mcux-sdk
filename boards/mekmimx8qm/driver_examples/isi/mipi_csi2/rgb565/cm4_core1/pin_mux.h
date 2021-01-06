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

/* MIPI_DSI0_I2C0_SCL (number BE29), MIPI_DSI0_TS_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_PERIPHERAL               MIPI_DSI0__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_SIGNAL                           i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_PIN_NAME              MIPI_DSI0_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_PIN_FUNCTION_ID  SC_P_MIPI_DSI0_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_LABEL                 "MIPI_DSI0_TS_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI0_TS_SCL_NAME                  "MIPI_DSI0_TS_SCL"   /*!< Identifier */

/* MIPI_DSI0_I2C0_SDA (number BE31), MIPI_DSI0_TS_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_PERIPHERAL               MIPI_DSI0__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_SIGNAL                           i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_PIN_NAME              MIPI_DSI0_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_PIN_FUNCTION_ID  SC_P_MIPI_DSI0_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_LABEL                 "MIPI_DSI0_TS_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI0_TS_SDA_NAME                  "MIPI_DSI0_TS_SDA"   /*!< Identifier */

/* MIPI_DSI1_I2C0_SCL (number BE27), MIPI_DSI1_TS_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_PERIPHERAL               MIPI_DSI1__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_SIGNAL                           i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_PIN_NAME              MIPI_DSI1_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_PIN_FUNCTION_ID  SC_P_MIPI_DSI1_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_LABEL                 "MIPI_DSI1_TS_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI1_TS_SCL_NAME                  "MIPI_DSI1_TS_SCL"   /*!< Identifier */

/* MIPI_DSI1_I2C0_SDA (number BG25), MIPI_DSI1_TS_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_PERIPHERAL               MIPI_DSI1__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_SIGNAL                           i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_PIN_NAME              MIPI_DSI1_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_PIN_FUNCTION_ID  SC_P_MIPI_DSI1_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_LABEL                 "MIPI_DSI1_TS_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI1_TS_SDA_NAME                  "MIPI_DSI1_TS_SDA"   /*!< Identifier */

/* MIPI_CSI0_MCLK_OUT (number BJ23), MIPI_CSI0_MCLK_OUT */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PERIPHERAL              MIPI_CSI0__ACM   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_SIGNAL                        mclk_out   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PIN_NAME            MIPI_CSI0_MCLK_OUT   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_PIN_FUNCTION_ID SC_P_MIPI_CSI0_MCLK_OUT  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_LABEL             "MIPI_CSI0_MCLK_OUT"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_MCLK_OUT_NAME              "MIPI_CSI0_MCLK_OUT"   /*!< Identifier */

/* MIPI_CSI0_GPIO0_00 (number BL23), MIPI_CSI0_RST_B */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_PERIPHERAL               MIPI_CSI0__GPIO0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_SIGNAL                            gpio_io   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_CHANNEL                                00   /*!< Signal channel */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_PIN_NAME               MIPI_CSI0_GPIO0_00   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_PIN_FUNCTION_ID   SC_P_MIPI_CSI0_GPIO0_00   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_LABEL                   "MIPI_CSI0_RST_B"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_NAME                    "MIPI_CSI0_RST_B"   /*!< Identifier */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_DIRECTION             kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_GPIO                     MIPI_CSI0__GPIO0   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_GPIO_PIN                               0U   /*!< GPIO pin number */
#define BOARD_INITPINS_MIPI_CSI0_RST_B_GPIO_PIN_MASK                  (1U << 0U)   /*!< GPIO pin mask */

/* MIPI_CSI0_GPIO0_01 (number BM22), MIPI_CSI0_EN */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI0_EN_PERIPHERAL                  MIPI_CSI0__GPIO0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI0_EN_SIGNAL                               gpio_io   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI0_EN_CHANNEL                                   01   /*!< Signal channel */
#define BOARD_INITPINS_MIPI_CSI0_EN_PIN_NAME                  MIPI_CSI0_GPIO0_01   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI0_EN_PIN_FUNCTION_ID      SC_P_MIPI_CSI0_GPIO0_01   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_EN_LABEL                         "MIPI_CSI0_EN"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_EN_NAME                          "MIPI_CSI0_EN"   /*!< Identifier */
#define BOARD_INITPINS_MIPI_CSI0_EN_DIRECTION                kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_MIPI_CSI0_EN_GPIO                        MIPI_CSI0__GPIO0   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_MIPI_CSI0_EN_GPIO_PIN                                  1U   /*!< GPIO pin number */
#define BOARD_INITPINS_MIPI_CSI0_EN_GPIO_PIN_MASK                     (1U << 1U)   /*!< GPIO pin mask */

/* MIPI_CSI0_I2C0_SCL (number BH24), MIPI_CSI0_I2C0_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PERIPHERAL             MIPI_CSI0__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_SIGNAL                         i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PIN_NAME            MIPI_CSI0_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_PIN_FUNCTION_ID SC_P_MIPI_CSI0_I2C0_SCL  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_LABEL             "MIPI_CSI0_I2C0_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SCL_NAME              "MIPI_CSI0_I2C0_SCL"   /*!< Identifier */

/* MIPI_CSI0_I2C0_SDA (number BN19), MIPI_CSI0_I2C0_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PERIPHERAL             MIPI_CSI0__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_SIGNAL                         i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PIN_NAME            MIPI_CSI0_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_PIN_FUNCTION_ID SC_P_MIPI_CSI0_I2C0_SDA  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_LABEL             "MIPI_CSI0_I2C0_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI0_I2C0_SDA_NAME              "MIPI_CSI0_I2C0_SDA"   /*!< Identifier */

/* MIPI_CSI1_MCLK_OUT (number BN23), MIPI_CSI1_MCLK_OUT */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_PERIPHERAL              MIPI_CSI1__ACM   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_SIGNAL                        mclk_out   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_PIN_NAME            MIPI_CSI1_MCLK_OUT   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_PIN_FUNCTION_ID SC_P_MIPI_CSI1_MCLK_OUT  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_LABEL             "MIPI_CSI1_MCLK_OUT"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI1_MCLK_OUT_NAME              "MIPI_CSI1_MCLK_OUT"   /*!< Identifier */

/* MIPI_CSI1_GPIO0_00 (number BN15), MIPI_CSI1_RST_B */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_PERIPHERAL               MIPI_CSI1__GPIO0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_SIGNAL                            gpio_io   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_CHANNEL                                00   /*!< Signal channel */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_PIN_NAME               MIPI_CSI1_GPIO0_00   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_PIN_FUNCTION_ID   SC_P_MIPI_CSI1_GPIO0_00   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_LABEL                   "MIPI_CSI1_RST_B"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_NAME                    "MIPI_CSI1_RST_B"   /*!< Identifier */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_DIRECTION             kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_GPIO                     MIPI_CSI1__GPIO0   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_GPIO_PIN                               0U   /*!< GPIO pin number */
#define BOARD_INITPINS_MIPI_CSI1_RST_B_GPIO_PIN_MASK                  (1U << 0U)   /*!< GPIO pin mask */

/* MIPI_CSI1_GPIO0_01 (number BN13), MIPI_CSI1_EN */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI1_EN_PERIPHERAL                  MIPI_CSI1__GPIO0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI1_EN_SIGNAL                               gpio_io   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI1_EN_CHANNEL                                   01   /*!< Signal channel */
#define BOARD_INITPINS_MIPI_CSI1_EN_PIN_NAME                  MIPI_CSI1_GPIO0_01   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI1_EN_PIN_FUNCTION_ID      SC_P_MIPI_CSI1_GPIO0_01   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI1_EN_LABEL                         "MIPI_CSI1_EN"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI1_EN_NAME                          "MIPI_CSI1_EN"   /*!< Identifier */
#define BOARD_INITPINS_MIPI_CSI1_EN_DIRECTION                kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_MIPI_CSI1_EN_GPIO                        MIPI_CSI1__GPIO0   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_MIPI_CSI1_EN_GPIO_PIN                                  1U   /*!< GPIO pin number */
#define BOARD_INITPINS_MIPI_CSI1_EN_GPIO_PIN_MASK                     (1U << 1U)   /*!< GPIO pin mask */

/* MIPI_CSI1_I2C0_SCL (number BN17), MIPI_CSI1_I2C0_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_PERIPHERAL             MIPI_CSI1__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_SIGNAL                         i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_PIN_NAME            MIPI_CSI1_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_PIN_FUNCTION_ID SC_P_MIPI_CSI1_I2C0_SCL  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_LABEL             "MIPI_CSI1_I2C0_SCL"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SCL_NAME              "MIPI_CSI1_I2C0_SCL"   /*!< Identifier */

/* MIPI_CSI1_I2C0_SDA (number BE15), MIPI_CSI1_I2C0_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_PERIPHERAL             MIPI_CSI1__I2C0   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_SIGNAL                         i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_PIN_NAME            MIPI_CSI1_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_PIN_FUNCTION_ID SC_P_MIPI_CSI1_I2C0_SDA  /*!< Pin function id */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_LABEL             "MIPI_CSI1_I2C0_SDA"   /*!< Label */
#define BOARD_INITPINS_MIPI_CSI1_I2C0_SDA_NAME              "MIPI_CSI1_I2C0_SDA"   /*!< Identifier */

/* LVDS0_I2C0_SDA (number BD36), MIPI_DSI0_1_EN */
/* Routed pin properties */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_PERIPHERAL                     LSIO__GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_SIGNAL                             gpio_io   /*!< Signal name */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_CHANNEL                                 07   /*!< Signal channel */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_PIN_NAME                    LVDS0_I2C0_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_PIN_FUNCTION_ID        SC_P_LVDS0_I2C0_SDA   /*!< Pin function id */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_LABEL                     "MIPI_DSI0_1_EN"   /*!< Label */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_NAME                      "MIPI_DSI0_1_EN"   /*!< Identifier */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_DIRECTION              kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_GPIO                           LSIO__GPIO1   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_GPIO_PIN                                7U   /*!< GPIO pin number */
#define BOARD_INITPINS_MIPI_DSI0_1_EN_GPIO_PIN_MASK                   (1U << 7U)   /*!< GPIO pin mask */

/* LVDS0_I2C0_SCL (number BD38), LVDS_EN */
/* Routed pin properties */
#define BOARD_INITPINS_LVDS_EN_PERIPHERAL                            LSIO__GPIO1   /*!< Peripheral name */
#define BOARD_INITPINS_LVDS_EN_SIGNAL                                    gpio_io   /*!< Signal name */
#define BOARD_INITPINS_LVDS_EN_CHANNEL                                        06   /*!< Signal channel */
#define BOARD_INITPINS_LVDS_EN_PIN_NAME                           LVDS0_I2C0_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_LVDS_EN_PIN_FUNCTION_ID               SC_P_LVDS0_I2C0_SCL   /*!< Pin function id */
#define BOARD_INITPINS_LVDS_EN_LABEL                                   "LVDS_EN"   /*!< Label */
#define BOARD_INITPINS_LVDS_EN_NAME                                    "LVDS_EN"   /*!< Identifier */
#define BOARD_INITPINS_LVDS_EN_DIRECTION                     kGPIO_DigitalOutput   /*!< Direction */

/* Symbols to be used with GPIO driver */
#define BOARD_INITPINS_LVDS_EN_GPIO                                  LSIO__GPIO1   /*!< GPIO peripheral base pointer */
#define BOARD_INITPINS_LVDS_EN_GPIO_PIN                                       6U   /*!< GPIO pin number */
#define BOARD_INITPINS_LVDS_EN_GPIO_PIN_MASK                          (1U << 6U)   /*!< GPIO pin mask */

/* LVDS0_I2C1_SCL (number BE37), LVDS0_TS_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_LVDS0_TS_SCL_PERIPHERAL                       LVDS0__I2C1   /*!< Peripheral name */
#define BOARD_INITPINS_LVDS0_TS_SCL_SIGNAL                               i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_LVDS0_TS_SCL_PIN_NAME                      LVDS0_I2C1_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_LVDS0_TS_SCL_PIN_FUNCTION_ID          SC_P_LVDS0_I2C1_SCL   /*!< Pin function id */
#define BOARD_INITPINS_LVDS0_TS_SCL_LABEL                         "LVDS0_TS_SCL"   /*!< Label */
#define BOARD_INITPINS_LVDS0_TS_SCL_NAME                          "LVDS0_TS_SCL"   /*!< Identifier */

/* LVDS0_I2C1_SDA (number BE35), LVDS0_TS_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_LVDS0_TS_SDA_PERIPHERAL                       LVDS0__I2C1   /*!< Peripheral name */
#define BOARD_INITPINS_LVDS0_TS_SDA_SIGNAL                               i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_LVDS0_TS_SDA_PIN_NAME                      LVDS0_I2C1_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_LVDS0_TS_SDA_PIN_FUNCTION_ID          SC_P_LVDS0_I2C1_SDA   /*!< Pin function id */
#define BOARD_INITPINS_LVDS0_TS_SDA_LABEL                         "LVDS0_TS_SDA"   /*!< Label */
#define BOARD_INITPINS_LVDS0_TS_SDA_NAME                          "LVDS0_TS_SDA"   /*!< Identifier */

/* LVDS1_I2C1_SCL (number BD32), LVDS1_TS_SCL */
/* Routed pin properties */
#define BOARD_INITPINS_LVDS1_TS_SCL_PERIPHERAL                       LVDS1__I2C1   /*!< Peripheral name */
#define BOARD_INITPINS_LVDS1_TS_SCL_SIGNAL                               i2c_scl   /*!< Signal name */
#define BOARD_INITPINS_LVDS1_TS_SCL_PIN_NAME                      LVDS1_I2C1_SCL   /*!< Routed pin name */
#define BOARD_INITPINS_LVDS1_TS_SCL_PIN_FUNCTION_ID          SC_P_LVDS1_I2C1_SCL   /*!< Pin function id */
#define BOARD_INITPINS_LVDS1_TS_SCL_LABEL                         "LVDS1_TS_SCL"   /*!< Label */
#define BOARD_INITPINS_LVDS1_TS_SCL_NAME                          "LVDS1_TS_SCL"   /*!< Identifier */

/* LVDS1_I2C1_SDA (number BN35), LVDS1_TS_SDA */
/* Routed pin properties */
#define BOARD_INITPINS_LVDS1_TS_SDA_PERIPHERAL                       LVDS1__I2C1   /*!< Peripheral name */
#define BOARD_INITPINS_LVDS1_TS_SDA_SIGNAL                               i2c_sda   /*!< Signal name */
#define BOARD_INITPINS_LVDS1_TS_SDA_PIN_NAME                      LVDS1_I2C1_SDA   /*!< Routed pin name */
#define BOARD_INITPINS_LVDS1_TS_SDA_PIN_FUNCTION_ID          SC_P_LVDS1_I2C1_SDA   /*!< Pin function id */
#define BOARD_INITPINS_LVDS1_TS_SDA_LABEL                         "LVDS1_TS_SDA"   /*!< Label */
#define BOARD_INITPINS_LVDS1_TS_SDA_NAME                          "LVDS1_TS_SDA"   /*!< Identifier */

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
