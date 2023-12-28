/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, UART0-UART3, UART14. */
/* User needs to provide the implementation of USARTX_GetFreq/USARTX_InitPins/USARTX_DeinitPins for the enabled USART
 * instance. */
#define RTE_USART0         0
#define RTE_USART0_DMA_EN  0
#define RTE_USART1         0
#define RTE_USART1_DMA_EN  0
#define RTE_USART2         0
#define RTE_USART2_DMA_EN  0
#define RTE_USART3         0
#define RTE_USART3_DMA_EN  0
#define RTE_USART14        0
#define RTE_USART14_DMA_EN 0

/* USART configuration. */
#define USART_RX_BUFFER_LEN      64
#define USART0_RX_BUFFER_ENABLE  0
#define USART1_RX_BUFFER_ENABLE  0
#define USART2_RX_BUFFER_ENABLE  0
#define USART3_RX_BUFFER_ENABLE  0
#define USART14_RX_BUFFER_ENABLE 0

#define RTE_USART0_PIN_INIT        USART0_InitPins
#define RTE_USART0_PIN_DEINIT      USART0_DeinitPins
#define RTE_USART0_DMA_TX_CH       1
#define RTE_USART0_DMA_TX_DMA_BASE DMA0
#define RTE_USART0_DMA_RX_CH       0
#define RTE_USART0_DMA_RX_DMA_BASE DMA0

#define RTE_USART1_PIN_INIT        USART1_InitPins
#define RTE_USART1_PIN_DEINIT      USART1_DeinitPins
#define RTE_USART1_DMA_TX_CH       3
#define RTE_USART1_DMA_TX_DMA_BASE DMA0
#define RTE_USART1_DMA_RX_CH       2
#define RTE_USART1_DMA_RX_DMA_BASE DMA0

#define RTE_USART2_PIN_INIT        USART2_InitPins
#define RTE_USART2_PIN_DEINIT      USART2_DeinitPins
#define RTE_USART2_DMA_TX_CH       5
#define RTE_USART2_DMA_TX_DMA_BASE DMA0
#define RTE_USART2_DMA_RX_CH       4
#define RTE_USART2_DMA_RX_DMA_BASE DMA0

#define RTE_USART3_PIN_INIT        USART3_InitPins
#define RTE_USART3_PIN_DEINIT      USART3_DeinitPins
#define RTE_USART3_DMA_TX_CH       7
#define RTE_USART3_DMA_TX_DMA_BASE DMA0
#define RTE_USART3_DMA_RX_CH       6
#define RTE_USART3_DMA_RX_DMA_BASE DMA0

#define RTE_USART14_PIN_INIT        USART14_InitPins
#define RTE_USART14_PIN_DEINIT      USART14_DeinitPins
#define RTE_USART14_DMA_TX_CH       27
#define RTE_USART14_DMA_TX_DMA_BASE DMA0
#define RTE_USART14_DMA_RX_CH       26
#define RTE_USART14_DMA_RX_DMA_BASE DMA0

/* I2C Select, I2C0-I2C3, I2C14 */
/* User needs to provide the implementation of I2CX_GetFreq/I2CX_InitPins/I2CX_DeinitPins for the enabled I2C instance.
 */
#define RTE_I2C0         0
#define RTE_I2C0_DMA_EN  0
#define RTE_I2C1         0
#define RTE_I2C1_DMA_EN  0
#define RTE_I2C2         0
#define RTE_I2C2_DMA_EN  0
#define RTE_I2C3         0
#define RTE_I2C3_DMA_EN  0
#define RTE_I2C14        0
#define RTE_I2C14_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_Master_DMA_BASE DMA0
#define RTE_I2C0_Master_DMA_CH   1

#define RTE_I2C1_Master_DMA_BASE DMA0
#define RTE_I2C1_Master_DMA_CH   3

#define RTE_I2C2_Master_DMA_BASE DMA0
#define RTE_I2C2_Master_DMA_CH   5

#define RTE_I2C3_Master_DMA_BASE DMA0
#define RTE_I2C3_Master_DMA_CH   7

#define RTE_I2C14_Master_DMA_BASE DMA0
#define RTE_I2C14_Master_DMA_CH   27

/* SPI select, SPI0-SPI3, SPI14. */
/* User needs to provide the implementation of SPIX_GetFreq/SPIX_InitPins/SPIX_DeinitPins for the enabled SPI instance.
 */
#define RTE_SPI0         0
#define RTE_SPI0_DMA_EN  0
#define RTE_SPI1         0
#define RTE_SPI1_DMA_EN  0
#define RTE_SPI2         0
#define RTE_SPI2_DMA_EN  0
#define RTE_SPI3         0
#define RTE_SPI3_DMA_EN  0
#define RTE_SPI14        0
#define RTE_SPI14_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI0_PIN_INIT        SPI0_InitPins
#define RTE_SPI0_PIN_DEINIT      SPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH       1
#define RTE_SPI0_DMA_TX_DMA_BASE DMA0
#define RTE_SPI0_DMA_RX_CH       0
#define RTE_SPI0_DMA_RX_DMA_BASE DMA0

#define RTE_SPI1_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI1_PIN_INIT        SPI1_InitPins
#define RTE_SPI1_PIN_DEINIT      SPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH       3
#define RTE_SPI1_DMA_TX_DMA_BASE DMA0
#define RTE_SPI1_DMA_RX_CH       2
#define RTE_SPI1_DMA_RX_DMA_BASE DMA0

#define RTE_SPI2_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI2_PIN_INIT        SPI2_InitPins
#define RTE_SPI2_PIN_DEINIT      SPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH       5
#define RTE_SPI2_DMA_TX_DMA_BASE DMA0
#define RTE_SPI2_DMA_RX_CH       4
#define RTE_SPI2_DMA_RX_DMA_BASE DMA0

#define RTE_SPI3_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI3_PIN_INIT        SPI3_InitPins
#define RTE_SPI3_PIN_DEINIT      SPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH       7
#define RTE_SPI3_DMA_TX_DMA_BASE DMA0
#define RTE_SPI3_DMA_RX_CH       6
#define RTE_SPI3_DMA_RX_DMA_BASE DMA0

#define RTE_SPI14_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI14_PIN_INIT        SPI14_InitPins
#define RTE_SPI14_PIN_DEINIT      SPI14_DeinitPins
#define RTE_SPI14_DMA_TX_CH       27
#define RTE_SPI14_DMA_TX_DMA_BASE DMA0
#define RTE_SPI14_DMA_RX_CH       26
#define RTE_SPI14_DMA_RX_DMA_BASE DMA0

/* ENET configuration. */
#define RTE_ENET             0
#define RTE_ENET_PHY_ADDRESS 2
#define RTE_ENET_MII         0
#define RTE_ENET_RMII        1

#endif /* _RTE_DEVICE_H */
