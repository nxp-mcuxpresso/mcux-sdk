/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* USART select, LPUART0 - LPUART3. */
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
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 0
#define USART1_RX_BUFFER_ENABLE 0
#define USART2_RX_BUFFER_ENABLE 0
#define USART3_RX_BUFFER_ENABLE 0

#define RTE_USART0_PIN_INIT           LPUART0_InitPins
#define RTE_USART0_PIN_DEINIT         LPUART0_DeinitPins
#define RTE_USART0_DMA_TX_CH          0
#define RTE_USART0_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART0Tx
#define RTE_USART0_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_TX_DMA_BASE    DMA0
#define RTE_USART0_DMA_RX_CH          1
#define RTE_USART0_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART0Rx
#define RTE_USART0_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART0_DMA_RX_DMA_BASE    DMA0

#define RTE_USART1_PIN_INIT           LPUART1_InitPins
#define RTE_USART1_PIN_DEINIT         LPUART1_DeinitPins
#define RTE_USART1_DMA_TX_CH          0
#define RTE_USART1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART1Tx
#define RTE_USART1_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_TX_DMA_BASE    DMA0
#define RTE_USART1_DMA_RX_CH          1
#define RTE_USART1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART1Rx
#define RTE_USART1_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART1_DMA_RX_DMA_BASE    DMA0

#define RTE_USART2_PIN_INIT           LPUART2_InitPins
#define RTE_USART2_PIN_DEINIT         LPUART2_DeinitPins
#define RTE_USART2_DMA_TX_CH          0
#define RTE_USART2_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART2Tx
#define RTE_USART2_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_TX_DMA_BASE    DMA0
#define RTE_USART2_DMA_RX_CH          1
#define RTE_USART2_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART2Rx
#define RTE_USART2_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART2_DMA_RX_DMA_BASE    DMA0

#define RTE_USART3_PIN_INIT           LPUART3_InitPins
#define RTE_USART3_PIN_DEINIT         LPUART3_DeinitPins
#define RTE_USART3_DMA_TX_CH          0
#define RTE_USART3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART3Tx
#define RTE_USART3_DMA_TX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_TX_DMA_BASE    DMA0
#define RTE_USART3_DMA_RX_CH          1
#define RTE_USART3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMux0LPUART3Rx
#define RTE_USART3_DMA_RX_DMAMUX_BASE DMAMUX0
#define RTE_USART3_DMA_RX_DMA_BASE    DMA0

/* I2C Select, LPI2C0 - LPI2C3 */
/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled LPI2C
 * instance. */
#define RTE_I2C0        0
#define RTE_I2C0_DMA_EN 0
#define RTE_I2C1        0
#define RTE_I2C1_DMA_EN 0
#define RTE_I2C2        0
#define RTE_I2C2_DMA_EN 0
#define RTE_I2C3        0
#define RTE_I2C3_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_Master_DMA_BASE    DMA0
#define RTE_I2C0_Master_DMA_CH      0
#define RTE_I2C0_Master_DMAMUX_BASE DMAMUX0
#define RTE_I2C0_Master_PERI_SEL    kDmaRequestMux0LPI2C0

#define RTE_I2C1_Master_DMA_BASE    DMA0
#define RTE_I2C1_Master_DMA_CH      1
#define RTE_I2C1_Master_DMAMUX_BASE DMAMUX0
#define RTE_I2C1_Master_PERI_SEL    kDmaRequestMux0LPI2C1

#define RTE_I2C2_Master_DMA_BASE    DMA0
#define RTE_I2C2_Master_DMA_CH      2
#define RTE_I2C2_Master_DMAMUX_BASE DMAMUX0
#define RTE_I2C2_Master_PERI_SEL    kDmaRequestMux0LPI2C2

#define RTE_I2C3_Master_DMA_BASE    DMA1
#define RTE_I2C3_Master_DMA_CH      3
#define RTE_I2C3_Master_DMAMUX_BASE DMAMUX1
#define RTE_I2C3_Master_PERI_SEL    kDmaRequestMux1LPI2C3

#endif /* _RTE_DEVICE_H */
