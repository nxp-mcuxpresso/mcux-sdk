/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, UART0 - UART5. */
/* User needs to provide the implementation of UARTX_GetFreq/UARTX_InitPins/UARTX_DeinitPins for the enabled UART
 * instance. */
#define RTE_USART0        0
#define RTE_USART0_DMA_EN 0
#define RTE_USART1        0
#define RTE_USART1_DMA_EN 0
#define RTE_USART2        0
#define RTE_USART2_DMA_EN 0
#define RTE_USART3        0
#define RTE_USART3_DMA_EN 0
#define RTE_USART4        0
#define RTE_USART4_DMA_EN 0
#define RTE_USART5        0
#define RTE_USART5_DMA_EN 0

/* UART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 0
#define USART1_RX_BUFFER_ENABLE 0
#define USART2_RX_BUFFER_ENABLE 0
#define USART3_RX_BUFFER_ENABLE 0
#define USART4_RX_BUFFER_ENABLE 0
#define USART5_RX_BUFFER_ENABLE 0

#define RTE_USART0_PIN_INIT           UART0_InitPins
#define RTE_USART0_PIN_DEINIT         UART0_DeinitPins
#define RTE_USART0_DMA_TX_CH          0
#define RTE_USART0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0UART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_TX_DMA_BASE    DMA0
#define RTE_USART0_DMA_RX_CH          1
#define RTE_USART0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0UART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_RX_DMA_BASE    DMA0

#define RTE_USART1_PIN_INIT           UART1_InitPins
#define RTE_USART1_PIN_DEINIT         UART1_DeinitPins
#define RTE_USART1_DMA_TX_CH          0
#define RTE_USART1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0UART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_TX_DMA_BASE    DMA0
#define RTE_USART1_DMA_RX_CH          1
#define RTE_USART1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0UART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_RX_DMA_BASE    DMA0

#define RTE_USART2_PIN_INIT           UART2_InitPins
#define RTE_USART2_PIN_DEINIT         UART2_DeinitPins
#define RTE_USART2_DMA_TX_CH          16
#define RTE_USART2_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART2Tx
#define RTE_USART2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_TX_DMA_BASE    DMA0
#define RTE_USART2_DMA_RX_CH          17
#define RTE_USART2_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART2Rx
#define RTE_USART2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_RX_DMA_BASE    DMA0

#define RTE_USART3_PIN_INIT           UART3_InitPins
#define RTE_USART3_PIN_DEINIT         UART3_DeinitPins
#define RTE_USART3_DMA_TX_CH          16
#define RTE_USART3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART3Tx
#define RTE_USART3_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_TX_DMA_BASE    DMA0
#define RTE_USART3_DMA_RX_CH          17
#define RTE_USART3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART3Rx
#define RTE_USART3_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_RX_DMA_BASE    DMA0

#define RTE_USART4_PIN_INIT           UART4_InitPins
#define RTE_USART4_PIN_DEINIT         UART4_DeinitPins
#define RTE_USART4_DMA_TX_CH          16
#define RTE_USART4_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART4Tx
#define RTE_USART4_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART4_DMA_TX_DMA_BASE    DMA0
#define RTE_USART4_DMA_RX_CH          17
#define RTE_USART4_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART4Rx
#define RTE_USART4_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART4_DMA_RX_DMA_BASE    DMA0

#define RTE_USART5_PIN_INIT           UART5_InitPins
#define RTE_USART5_PIN_DEINIT         UART5_DeinitPins
#define RTE_USART5_DMA_TX_CH          16
#define RTE_USART5_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART5Tx
#define RTE_USART5_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART5_DMA_TX_DMA_BASE    DMA0
#define RTE_USART5_DMA_RX_CH          17
#define RTE_USART5_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1UART5Rx
#define RTE_USART5_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART5_DMA_RX_DMA_BASE    DMA0

/* I2C Select, I2C0 - I2C1. */
/* User needs to provide the implementation of I2CX_GetFreq/I2CX_InitPins/I2CX_DeinitPins for the enabled I2C instance.
 */
#define RTE_I2C0        1
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C1        1
#define RTE_I2C1_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_Master_DMA_BASE    DMA0
#define RTE_I2C0_Master_DMA_CH      0
#define RTE_I2C0_Master_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_Master_PERI_SEL    kDmaRequestMux0I2C0

#define RTE_I2C1_Master_DMA_BASE    DMA0
#define RTE_I2C1_Master_DMA_CH      16
#define RTE_I2C1_Master_DMAMUX_BASE DMAMUX0
#define RTE_I2C1_Master_PERI_SEL    kDmaRequestMux0Group1I2C1

/* SPI select, DSPI0 - DSPI2. */
/* User needs to provide the implementation of DSPIX_GetFreq/DSPIX_InitPins/DSPIX_DeinitPins for the enabled DSPI
 * instance. */
#define RTE_SPI0        1
#define RTE_SPI0_DMA_EN 0
#define RTE_SPI1        0
#define RTE_SPI1_DMA_EN 0
#define RTE_SPI2        1
#define RTE_SPI2_DMA_EN 0

/* UART configuration. */
#define RTE_SPI0_PIN_INIT           DSPI0_InitPins
#define RTE_SPI0_PIN_DEINIT         DSPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH          0
#define RTE_SPI0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0SPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_TX_DMA_BASE    DMA0
#define RTE_SPI0_DMA_RX_CH          1
#define RTE_SPI0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0SPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI0_DMA_RX_DMA_BASE    DMA0
#define RTE_SPI0_DMA_LINK_DMA_BASE  DMA0
#define RTE_SPI0_DMA_LINK_CH        2

#define RTE_SPI1_PIN_INIT           DSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT         DSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH          16
#define RTE_SPI1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1SPI1Tx
#define RTE_SPI1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI1_DMA_TX_DMA_BASE    DMA0
#define RTE_SPI1_DMA_RX_CH          17
#define RTE_SPI1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1SPI1Rx
#define RTE_SPI1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI1_DMA_RX_DMA_BASE    DMA0
#define RTE_SPI1_DMA_LINK_DMA_BASE  DMA0
#define RTE_SPI1_DMA_LINK_CH        18

#define RTE_SPI2_PIN_INIT           DSPI2_InitPins
#define RTE_SPI2_PIN_DEINIT         DSPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH          19
#define RTE_SPI2_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1SPI2Tx
#define RTE_SPI2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_SPI2_DMA_TX_DMA_BASE    DMA0
#define RTE_SPI2_DMA_RX_CH          20
#define RTE_SPI2_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0Group1SPI2Rx
#define RTE_SPI2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_SPI2_DMA_RX_DMA_BASE    DMA0
#define RTE_SPI2_DMA_LINK_DMA_BASE  DMA0
#define RTE_SPI2_DMA_LINK_CH        21

#define RTE_SPI0_PCS_TO_SCK_DELAY       1000
#define RTE_SPI0_SCK_TO_PSC_DELAY       1000
#define RTE_SPI0_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI0_MASTER_PCS_PIN_SEL     kDSPI_MasterPcs0
#define RTE_SPI1_PCS_TO_SCK_DELAY       1000
#define RTE_SPI1_SCK_TO_PSC_DELAY       1000
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI1_MASTER_PCS_PIN_SEL     kDSPI_MasterPcs0
#define RTE_SPI2_PCS_TO_SCK_DELAY       1000
#define RTE_SPI2_SCK_TO_PSC_DELAY       1000
#define RTE_SPI2_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI2_MASTER_PCS_PIN_SEL     kDSPI_MasterPcs0

/* ENET configuration. */
#define RTE_ENET             1
#define RTE_ENET_PHY_ADDRESS 0
#define RTE_ENET_MII         0
#define RTE_ENET_RMII        1

#endif /* _RTE_DEVICE_H */
