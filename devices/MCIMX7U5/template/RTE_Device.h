/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, LPUART0 - LPUART3. */
/* User needs to provide the implementation of LPUARTX_GetFreq/LPUARTX_InitPins/LPUARTX_DeinitPins for the enabled
 * LPUART instance. */
#define RTE_USART0        0
#define RTE_USART0_DMA_EN 0
#define RTE_USART1        0
#define RTE_USART1_DMA_EN 0
#define RTE_USART2        0
#define RTE_USART2_DMA_EN 0
#define RTE_USART3        0
#define RTE_USART3_DMA_EN 0

/* UART configuration. */
#define RTE_USART0_PIN_INIT           LPUART0_InitPins
#define RTE_USART0_PIN_DEINIT         LPUART0_DeinitPins
#define RTE_USART0_DMA_TX_CH          0
#define RTE_USART0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux1LPUART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_USART0_DMA_TX_DMA_BASE    DMA1
#define RTE_USART0_DMA_RX_CH          1
#define RTE_USART0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux1LPUART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_USART0_DMA_RX_DMA_BASE    DMA1

#define RTE_USART1_PIN_INIT           LPUART1_InitPins
#define RTE_USART1_PIN_DEINIT         LPUART1_DeinitPins
#define RTE_USART1_DMA_TX_CH          2
#define RTE_USART1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux1LPUART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_USART1_DMA_TX_DMA_BASE    DMA1
#define RTE_USART1_DMA_RX_CH          3
#define RTE_USART1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux1LPUART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_USART1_DMA_RX_DMA_BASE    DMA1

#define RTE_USART2_PIN_INIT           LPUART2_InitPins
#define RTE_USART2_PIN_DEINIT         LPUART2_DeinitPins
#define RTE_USART2_DMA_TX_CH          4
#define RTE_USART2_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART2Tx
#define RTE_USART2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_TX_DMA_BASE    DMA0
#define RTE_USART2_DMA_RX_CH          5
#define RTE_USART2_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART2Rx
#define RTE_USART2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_RX_DMA_BASE    DMA0

#define RTE_USART3_PIN_INIT           LPUART3_InitPins
#define RTE_USART3_PIN_DEINIT         LPUART3_DeinitPins
#define RTE_USART3_DMA_TX_CH          6
#define RTE_USART3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART2Tx
#define RTE_USART3_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_TX_DMA_BASE    DMA0
#define RTE_USART3_DMA_RX_CH          7
#define RTE_USART3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART3Rx
#define RTE_USART3_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_RX_DMA_BASE    DMA0

/* I2C Select, LPI2C0 - LPI2C3. */
/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled LPI2C
 * instance. */
#define RTE_I2C0        1
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C1        0
#define RTE_I2C1_DMA_EN 0
#define RTE_I2C2        0
#define RTE_I2C2_DMA_EN 0
#define RTE_I2C3        1
#define RTE_I2C3_DMA_EN 0

/* LPI2C configuration. */
#define RTE_I2C0_PIN_INIT           LPI2C0_InitPins
#define RTE_I2C0_PIN_DEINIT         LPI2C0_DeinitPins
#define RTE_I2C0_DMA_TX_CH          0
#define RTE_I2C0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C0Tx
#define RTE_I2C0_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_I2C0_DMA_TX_DMA_BASE    DMA1
#define RTE_I2C0_DMA_RX_CH          1
#define RTE_I2C0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C0Rx
#define RTE_I2C0_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_I2C0_DMA_RX_DMA_BASE    DMA1

#define RTE_I2C1_PIN_INIT           LPI2C1_InitPins
#define RTE_I2C1_PIN_DEINIT         LPI2C1_DeinitPins
#define RTE_I2C1_DMA_TX_CH          2
#define RTE_I2C1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C1Tx
#define RTE_I2C1_DMA_TX_DMAMUX_BASE DMAMUX1
#define RTE_I2C1_DMA_TX_DMA_BASE    DMA1
#define RTE_I2C1_DMA_RX_CH          3
#define RTE_I2C1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux1LPI2C1Rx
#define RTE_I2C1_DMA_RX_DMAMUX_BASE DMAMUX1
#define RTE_I2C1_DMA_RX_DMA_BASE    DMA1

#define RTE_I2C2_PIN_INIT           LPI2C2_InitPins
#define RTE_I2C2_PIN_DEINIT         LPI2C2_DeinitPins
#define RTE_I2C2_DMA_TX_CH          4
#define RTE_I2C2_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C2Tx
#define RTE_I2C2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_I2C2_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C2_DMA_RX_CH          5
#define RTE_I2C2_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C2Rx
#define RTE_I2C2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_I2C2_DMA_RX_DMA_BASE    DMA0

#define RTE_I2C3_PIN_INIT           LPI2C3_InitPins
#define RTE_I2C3_PIN_DEINIT         LPI2C3_DeinitPins
#define RTE_I2C3_DMA_TX_CH          6
#define RTE_I2C3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C3Tx
#define RTE_I2C3_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_I2C3_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C3_DMA_RX_CH          7
#define RTE_I2C3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPI2C3Rx
#define RTE_I2C3_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_I2C3_DMA_RX_DMA_BASE    DMA0

/* UART Select, LPSPI0 - LPSPI3. */
/* User needs to provide the implementation of LPSPIX_GetFreq/LPSPIX_InitPins/LPSPIX_DeinitPins for the enabled LPSPI
 * instance. */
#define RTE_SPI0        0
#define RTE_SPI0_DMA_EN 0
#define RTE_SPI1        0
#define RTE_SPI1_DMA_EN 0
#define RTE_SPI2        0
#define RTE_SPI2_DMA_EN 0
#define RTE_SPI3        0
#define RTE_SPI3_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_PCS_TO_SCK_DELAY       1000
#define RTE_SPI0_SCK_TO_PSC_DELAY       1000
#define RTE_SPI0_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI0_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI0_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI0_PIN_INIT               LPSPI0_InitPins
#define RTE_SPI0_PIN_DEINIT             LPSPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH              0
#define RTE_SPI0_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMux1LPSPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE     DMAMUX1
#define RTE_SPI0_DMA_TX_DMA_BASE        DMA1
#define RTE_SPI0_DMA_RX_CH              1
#define RTE_SPI0_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestMux1LPSPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE     DMAMUX1
#define RTE_SPI0_DMA_RX_DMA_BASE        DMA1

#define RTE_SPI1_PCS_TO_SCK_DELAY       1000
#define RTE_SPI1_SCK_TO_PSC_DELAY       1000
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI1_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI1_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI1_PIN_INIT               LPSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT             LPSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH              2
#define RTE_SPI1_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMux1LPSPI1Tx
#define RTE_SPI1_DMA_TX_DMAMUX_BASE     DMAMUX1
#define RTE_SPI1_DMA_TX_DMA_BASE        DMA1
#define RTE_SPI1_DMA_RX_CH              3
#define RTE_SPI1_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestMux1LPSPI1Rx
#define RTE_SPI1_DMA_RX_DMAMUX_BASE     DMAMUX1
#define RTE_SPI1_DMA_RX_DMA_BASE        DMA1

#define RTE_SPI2_PCS_TO_SCK_DELAY       1000
#define RTE_SPI2_SCK_TO_PSC_DELAY       1000
#define RTE_SPI2_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI2_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI2_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI2_PIN_INIT               LPSPI2_InitPins
#define RTE_SPI2_PIN_DEINIT             LPSPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH              4
#define RTE_SPI2_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI2Tx
#define RTE_SPI2_DMA_TX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI2_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI2_DMA_RX_CH              5
#define RTE_SPI2_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI2Rx
#define RTE_SPI2_DMA_RX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI2_DMA_RX_DMA_BASE        DMA0

#define RTE_SPI3_PCS_TO_SCK_DELAY       1000
#define RTE_SPI3_SCK_TO_PSC_DELAY       1000
#define RTE_SPI3_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI3_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI3_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI3_PIN_INIT               LPSPI3_InitPins
#define RTE_SPI3_PIN_DEINIT             LPSPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH              6
#define RTE_SPI3_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI3Tx
#define RTE_SPI3_DMA_TX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI3_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI3_DMA_RX_CH              7
#define RTE_SPI3_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestMux0LPSPI3Rx
#define RTE_SPI3_DMA_RX_DMAMUX_BASE     DMAMUX0
#define RTE_SPI3_DMA_RX_DMA_BASE        DMA0

#endif /* _RTE_DEVICE_H */
