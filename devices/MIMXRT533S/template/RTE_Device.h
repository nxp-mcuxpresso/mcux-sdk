/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, UART0-UART13. */
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
#define RTE_USART4         0
#define RTE_USART4_DMA_EN  0
#define RTE_USART5         0
#define RTE_USART5_DMA_EN  0
#define RTE_USART6         0
#define RTE_USART6_DMA_EN  0
#define RTE_USART7         0
#define RTE_USART7_DMA_EN  0
#define RTE_USART8         0
#define RTE_USART8_DMA_EN  0
#define RTE_USART9         0
#define RTE_USART9_DMA_EN  0
#define RTE_USART10        0
#define RTE_USART10_DMA_EN 0
#define RTE_USART11        0
#define RTE_USART11_DMA_EN 0
#define RTE_USART12        0
#define RTE_USART12_DMA_EN 0
#define RTE_USART13        0
#define RTE_USART13_DMA_EN 0

/* USART configuration. */
#define USART_RX_BUFFER_LEN      64
#define USART0_RX_BUFFER_ENABLE  0
#define USART1_RX_BUFFER_ENABLE  0
#define USART2_RX_BUFFER_ENABLE  0
#define USART3_RX_BUFFER_ENABLE  0
#define USART4_RX_BUFFER_ENABLE  0
#define USART5_RX_BUFFER_ENABLE  0
#define USART6_RX_BUFFER_ENABLE  0
#define USART7_RX_BUFFER_ENABLE  0
#define USART8_RX_BUFFER_ENABLE  0
#define USART9_RX_BUFFER_ENABLE  0
#define USART10_RX_BUFFER_ENABLE 0
#define USART11_RX_BUFFER_ENABLE 0
#define USART12_RX_BUFFER_ENABLE 0
#define USART13_RX_BUFFER_ENABLE 0

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

#define RTE_USART4_PIN_INIT        USART4_InitPins
#define RTE_USART4_PIN_DEINIT      USART4_DeinitPins
#define RTE_USART4_DMA_TX_CH       9
#define RTE_USART4_DMA_TX_DMA_BASE DMA0
#define RTE_USART4_DMA_RX_CH       8
#define RTE_USART4_DMA_RX_DMA_BASE DMA0

#define RTE_USART5_PIN_INIT        USART5_InitPins
#define RTE_USART5_PIN_DEINIT      USART5_DeinitPins
#define RTE_USART5_DMA_TX_CH       11
#define RTE_USART5_DMA_TX_DMA_BASE DMA0
#define RTE_USART5_DMA_RX_CH       10
#define RTE_USART5_DMA_RX_DMA_BASE DMA0

#define RTE_USART6_PIN_INIT        USART6_InitPins
#define RTE_USART6_PIN_DEINIT      USART6_DeinitPins
#define RTE_USART6_DMA_TX_CH       13
#define RTE_USART6_DMA_TX_DMA_BASE DMA0
#define RTE_USART6_DMA_RX_CH       12
#define RTE_USART6_DMA_RX_DMA_BASE DMA0

#define RTE_USART7_PIN_INIT        USART7_InitPins
#define RTE_USART7_PIN_DEINIT      USART7_DeinitPins
#define RTE_USART7_DMA_TX_CH       15
#define RTE_USART7_DMA_TX_DMA_BASE DMA0
#define RTE_USART7_DMA_RX_CH       14
#define RTE_USART7_DMA_RX_DMA_BASE DMA0

#define RTE_USART8_PIN_INIT        USART8_InitPins
#define RTE_USART8_PIN_DEINIT      USART8_DeinitPins
#define RTE_USART8_DMA_TX_CH       17
#define RTE_USART8_DMA_TX_DMA_BASE DMA0
#define RTE_USART8_DMA_RX_CH       16
#define RTE_USART8_DMA_RX_DMA_BASE DMA0

#define RTE_USART9_PIN_INIT        USART9_InitPins
#define RTE_USART9_PIN_DEINIT      USART9_DeinitPins
#define RTE_USART9_DMA_TX_CH       19
#define RTE_USART9_DMA_TX_DMA_BASE DMA0
#define RTE_USART9_DMA_RX_CH       18
#define RTE_USART9_DMA_RX_DMA_BASE DMA0

#define RTE_USART10_PIN_INIT        USART10_InitPins
#define RTE_USART10_PIN_DEINIT      USART10_DeinitPins
#define RTE_USART10_DMA_TX_CH       21
#define RTE_USART10_DMA_TX_DMA_BASE DMA0
#define RTE_USART10_DMA_RX_CH       20
#define RTE_USART10_DMA_RX_DMA_BASE DMA0

#define RTE_USART11_PIN_INIT        USART11_InitPins
#define RTE_USART11_PIN_DEINIT      USART11_DeinitPins
#define RTE_USART11_DMA_TX_CH       33
#define RTE_USART11_DMA_TX_DMA_BASE DMA0
#define RTE_USART11_DMA_RX_CH       32
#define RTE_USART11_DMA_RX_DMA_BASE DMA0

#define RTE_USART12_PIN_INIT        USART12_InitPins
#define RTE_USART12_PIN_DEINIT      USART12_DeinitPins
#define RTE_USART12_DMA_TX_CH       35
#define RTE_USART12_DMA_TX_DMA_BASE DMA0
#define RTE_USART12_DMA_RX_CH       34
#define RTE_USART12_DMA_RX_DMA_BASE DMA0

#define RTE_USART13_PIN_INIT        USART13_InitPins
#define RTE_USART13_PIN_DEINIT      USART13_DeinitPins
#define RTE_USART13_DMA_TX_CH       23
#define RTE_USART13_DMA_TX_DMA_BASE DMA0
#define RTE_USART13_DMA_RX_CH       22
#define RTE_USART13_DMA_RX_DMA_BASE DMA0

/* I2C Select, I2C0-I2C13,I2C15*/
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
#define RTE_I2C4         0
#define RTE_I2C4_DMA_EN  0
#define RTE_I2C5         0
#define RTE_I2C5_DMA_EN  0
#define RTE_I2C6         0
#define RTE_I2C6_DMA_EN  0
#define RTE_I2C7         0
#define RTE_I2C7_DMA_EN  0
#define RTE_I2C8         0
#define RTE_I2C8_DMA_EN  0
#define RTE_I2C9         0
#define RTE_I2C9_DMA_EN  0
#define RTE_I2C10        0
#define RTE_I2C10_DMA_EN 0
#define RTE_I2C11        0
#define RTE_I2C11_DMA_EN 0
#define RTE_I2C12        0
#define RTE_I2C12_DMA_EN 0
#define RTE_I2C13        0
#define RTE_I2C13_DMA_EN 0
#define RTE_I2C15        0
#define RTE_I2C15_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_Master_DMA_BASE DMA0
#define RTE_I2C0_Master_DMA_CH   1

#define RTE_I2C1_Master_DMA_BASE DMA0
#define RTE_I2C1_Master_DMA_CH   3

#define RTE_I2C2_Master_DMA_BASE DMA0
#define RTE_I2C2_Master_DMA_CH   5

#define RTE_I2C3_Master_DMA_BASE DMA0
#define RTE_I2C3_Master_DMA_CH   7

#define RTE_I2C4_Master_DMA_BASE DMA0
#define RTE_I2C4_Master_DMA_CH   9

#define RTE_I2C5_Master_DMA_BASE DMA0
#define RTE_I2C5_Master_DMA_CH   11

#define RTE_I2C6_Master_DMA_BASE DMA0
#define RTE_I2C6_Master_DMA_CH   13

#define RTE_I2C7_Master_DMA_BASE DMA0
#define RTE_I2C7_Master_DMA_CH   15

#define RTE_I2C8_Master_DMA_BASE DMA0
#define RTE_I2C8_Master_DMA_CH   17

#define RTE_I2C9_Master_DMA_BASE DMA0
#define RTE_I2C9_Master_DMA_CH   19

#define RTE_I2C10_Master_DMA_BASE DMA0
#define RTE_I2C10_Master_DMA_CH   21

#define RTE_I2C11_Master_DMA_BASE DMA0
#define RTE_I2C11_Master_DMA_CH   33

#define RTE_I2C12_Master_DMA_BASE DMA0
#define RTE_I2C12_Master_DMA_CH   35

#define RTE_I2C13_Master_DMA_BASE DMA0
#define RTE_I2C13_Master_DMA_CH   23

/* SPI select, SPI0-SPI14, SPI16.*/
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
#define RTE_SPI4         0
#define RTE_SPI4_DMA_EN  0
#define RTE_SPI5         0
#define RTE_SPI5_DMA_EN  0
#define RTE_SPI6         0
#define RTE_SPI6_DMA_EN  0
#define RTE_SPI7         0
#define RTE_SPI7_DMA_EN  0
#define RTE_SPI8         0
#define RTE_SPI8_DMA_EN  0
#define RTE_SPI9         0
#define RTE_SPI9_DMA_EN  0
#define RTE_SPI10        0
#define RTE_SPI10_DMA_EN 0
#define RTE_SPI11        0
#define RTE_SPI11_DMA_EN 0
#define RTE_SPI12        0
#define RTE_SPI12_DMA_EN 0
#define RTE_SPI13        0
#define RTE_SPI13_DMA_EN 0
#define RTE_SPI14        0
#define RTE_SPI14_DMA_EN 0
#define RTE_SPI16        0
#define RTE_SPI16_DMA_EN 0

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

#define RTE_SPI4_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI4_PIN_INIT        SPI4_InitPins
#define RTE_SPI4_PIN_DEINIT      SPI4_DeinitPins
#define RTE_SPI4_DMA_TX_CH       9
#define RTE_SPI4_DMA_TX_DMA_BASE DMA0
#define RTE_SPI4_DMA_RX_CH       8
#define RTE_SPI4_DMA_RX_DMA_BASE DMA0

#define RTE_SPI5_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI5_PIN_INIT        SPI5_InitPins
#define RTE_SPI5_PIN_DEINIT      SPI5_DeinitPins
#define RTE_SPI5_DMA_TX_CH       11
#define RTE_SPI5_DMA_TX_DMA_BASE DMA0
#define RTE_SPI5_DMA_RX_CH       10
#define RTE_SPI5_DMA_RX_DMA_BASE DMA0

#define RTE_SPI6_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI6_PIN_INIT        SPI6_InitPins
#define RTE_SPI6_PIN_DEINIT      SPI6_DeinitPins
#define RTE_SPI6_DMA_TX_CH       13
#define RTE_SPI6_DMA_TX_DMA_BASE DMA0
#define RTE_SPI6_DMA_RX_CH       12
#define RTE_SPI6_DMA_RX_DMA_BASE DMA0

#define RTE_SPI7_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI7_PIN_INIT        SPI7_InitPins
#define RTE_SPI7_PIN_DEINIT      SPI7_DeinitPins
#define RTE_SPI7_DMA_TX_CH       15
#define RTE_SPI7_DMA_TX_DMA_BASE DMA0
#define RTE_SPI7_DMA_RX_CH       14
#define RTE_SPI7_DMA_RX_DMA_BASE DMA0

#define RTE_SPI8_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI8_PIN_INIT        SPI8_InitPins
#define RTE_SPI8_PIN_DEINIT      SPI8_DeinitPins
#define RTE_SPI8_DMA_TX_CH       17
#define RTE_SPI8_DMA_TX_DMA_BASE DMA0
#define RTE_SPI8_DMA_RX_CH       16
#define RTE_SPI8_DMA_RX_DMA_BASE DMA0

#define RTE_SPI9_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI9_PIN_INIT        SPI9_InitPins
#define RTE_SPI9_PIN_DEINIT      SPI9_DeinitPins
#define RTE_SPI9_DMA_TX_CH       19
#define RTE_SPI9_DMA_TX_DMA_BASE DMA0
#define RTE_SPI9_DMA_RX_CH       18
#define RTE_SPI9_DMA_RX_DMA_BASE DMA0

#define RTE_SPI10_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI10_PIN_INIT        SPI10_InitPins
#define RTE_SPI10_PIN_DEINIT      SPI10_DeinitPins
#define RTE_SPI10_DMA_TX_CH       21
#define RTE_SPI10_DMA_TX_DMA_BASE DMA0
#define RTE_SPI10_DMA_RX_CH       20
#define RTE_SPI10_DMA_RX_DMA_BASE DMA0

#define RTE_SPI11_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI11_PIN_INIT        SPI11_InitPins
#define RTE_SPI11_PIN_DEINIT      SPI11_DeinitPins
#define RTE_SPI11_DMA_TX_CH       33
#define RTE_SPI11_DMA_TX_DMA_BASE DMA0
#define RTE_SPI11_DMA_RX_CH       32
#define RTE_SPI11_DMA_RX_DMA_BASE DMA0

#define RTE_SPI12_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI12_PIN_INIT        SPI12_InitPins
#define RTE_SPI12_PIN_DEINIT      SPI12_DeinitPins
#define RTE_SPI12_DMA_TX_CH       35
#define RTE_SPI12_DMA_TX_DMA_BASE DMA0
#define RTE_SPI12_DMA_RX_CH       34
#define RTE_SPI12_DMA_RX_DMA_BASE DMA0

#define RTE_SPI13_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI13_PIN_INIT        SPI13_InitPins
#define RTE_SPI13_PIN_DEINIT      SPI13_DeinitPins
#define RTE_SPI13_DMA_TX_CH       23
#define RTE_SPI13_DMA_TX_DMA_BASE DMA0
#define RTE_SPI13_DMA_RX_CH       22
#define RTE_SPI13_DMA_RX_DMA_BASE DMA0

#define RTE_SPI14_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI14_PIN_INIT        SPI14_InitPins
#define RTE_SPI14_PIN_DEINIT      SPI14_DeinitPins
#define RTE_SPI14_DMA_TX_CH       27
#define RTE_SPI14_DMA_TX_DMA_BASE DMA0
#define RTE_SPI14_DMA_RX_CH       26
#define RTE_SPI14_DMA_RX_DMA_BASE DMA0

#define RTE_SPI16_SSEL_NUM        kSPI_Ssel0
#define RTE_SPI16_PIN_INIT        SPI16_InitPins
#define RTE_SPI16_PIN_DEINIT      SPI16_DeinitPins
#define RTE_SPI16_DMA_TX_CH       29
#define RTE_SPI16_DMA_TX_DMA_BASE DMA0
#define RTE_SPI16_DMA_RX_CH       28
#define RTE_SPI16_DMA_RX_DMA_BASE DMA0
#endif /* _RTE_DEVICE_H */
