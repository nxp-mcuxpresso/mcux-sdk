/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, LPUART0 - LPUART1. */
/* User needs to provide the implementation of LPUARTX_GetFreq/LPUARTX_InitPins/LPUARTX_DeinitPins for the enabled
 * LPUART instance. */
#define RTE_USART0        0
#define RTE_USART0_DMA_EN 0
#define RTE_USART1        0
#define RTE_USART1_DMA_EN 0

/* UART configuration. */
#define RTE_USART0_PIN_INIT           LPUART0_InitPins
#define RTE_USART0_PIN_DEINIT         LPUART0_DeinitPins
#define RTE_USART0_DMA_TX_CH          0
#define RTE_USART0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestLPUART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_TX_DMA_BASE    DMA0
#define RTE_USART0_DMA_RX_CH          1
#define RTE_USART0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestLPUART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_USART0_DMA_RX_DMA_BASE    DMA0

#define RTE_USART1_PIN_INIT           LPUART1_InitPins
#define RTE_USART1_PIN_DEINIT         LPUART1_DeinitPins
#define RTE_USART1_DMA_TX_CH          2
#define RTE_USART1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestLPUART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_TX_DMA_BASE    DMA0
#define RTE_USART1_DMA_RX_CH          3
#define RTE_USART1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestLPUART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_USART1_DMA_RX_DMA_BASE    DMA0

/* LPSPI Select, LPSPI0 - LPSPI1. */
/* User needs to provide the implementation of LPSPIX_GetFreq/LPSPIX_InitPins/LPSPIX_DeinitPins for the enabled LPSPI
 * instance. */
#define RTE_SPI0        0
#define RTE_SPI0_DMA_EN 0
#define RTE_SPI1        0
#define RTE_SPI1_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_PCS_TO_SCK_DELAY       1000
#define RTE_SPI0_SCK_TO_PSC_DELAY       1000
#define RTE_SPI0_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI0_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI0_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI0_PIN_INIT               LPSPI0_InitPins
#define RTE_SPI0_PIN_DEINIT             LPSPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH              0
#define RTE_SPI0_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestLPSPI0Tx
#define RTE_SPI0_DMA_TX_DMAMUX_BASE     DMAMUX
#define RTE_SPI0_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI0_DMA_RX_CH              1
#define RTE_SPI0_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestLPSPI0Rx
#define RTE_SPI0_DMA_RX_DMAMUX_BASE     DMAMUX
#define RTE_SPI0_DMA_RX_DMA_BASE        DMA0

#define RTE_SPI1_PCS_TO_SCK_DELAY       1000
#define RTE_SPI1_SCK_TO_PSC_DELAY       1000
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI1_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs0)
#define RTE_SPI1_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs0)
#define RTE_SPI1_PIN_INIT               LPSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT             LPSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH              0
#define RTE_SPI1_DMA_TX_PERI_SEL        (uint8_t) kDmaRequestLPSPI1Tx
#define RTE_SPI1_DMA_TX_DMAMUX_BASE     DMAMUX
#define RTE_SPI1_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI1_DMA_RX_CH              1
#define RTE_SPI1_DMA_RX_PERI_SEL        (uint8_t) kDmaRequestLPSPI1Rx
#define RTE_SPI1_DMA_RX_DMAMUX_BASE     DMAMUX
#define RTE_SPI1_DMA_RX_DMA_BASE        DMA0

/* LPI2C Select, LPI2C0 - LPI2C1. */
/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled LPI2C
 * instance. */
#define RTE_I2C0        0
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C1        0
#define RTE_I2C1_DMA_EN 0

/* LPI2C configuration. */
#define RTE_I2C0_PIN_INIT           LPI2C0_InitPins
#define RTE_I2C0_PIN_DEINIT         LPI2C0_DeinitPins
#define RTE_I2C0_DMA_TX_CH          0
#define RTE_I2C0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestLPI2C0Tx
#define RTE_I2C0_DMA_TX_DMAMUX_BASE DMAMUX
#define RTE_I2C0_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C0_DMA_RX_CH          1
#define RTE_I2C0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestLPI2C0Rx
#define RTE_I2C0_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_I2C0_DMA_RX_DMA_BASE    DMA0

#define RTE_I2C1_PIN_INIT           LPI2C1_InitPins
#define RTE_I2C1_PIN_DEINIT         LPI2C1_DeinitPins
#define RTE_I2C1_DMA_TX_CH          2
#define RTE_I2C1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestLPI2C1Tx
#define RTE_I2C1_DMA_TX_DMAMUX_BASE DMAMUX
#define RTE_I2C1_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C1_DMA_RX_CH          3
#define RTE_I2C1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestLPI2C1Rx
#define RTE_I2C1_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_I2C1_DMA_RX_DMA_BASE    DMA0

#endif /* _RTE_DEVICE_H */
