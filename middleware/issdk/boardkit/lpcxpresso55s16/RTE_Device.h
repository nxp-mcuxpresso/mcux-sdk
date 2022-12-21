/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void I2C4_InitPins();
extern void I2C4_DeinitPins();
extern void USART0_InitPins();
extern void USART0_DeinitPins();
extern void SPI8_InitPins();
extern void SPI8_DeinitPins();
extern void USART0_InitPins();
extern void USART0_DeinitPins();
extern void SPI7_InitPins();
extern void SPI7_DeinitPins();

/*I2C Driver name mapping*/
/* User needs to provide the implementation of I2CX_GetFreq/I2CX_InitPins/I2CX_DeinitPins for the enabled I2C instance.
 */
#define RTE_I2C4            1
#define RTE_I2C4_PIN_INIT   I2C4_InitPins
#define RTE_I2C4_PIN_DEINIT I2C4_DeinitPins
#define RTE_I2C4_DMA_EN     0

/*USART Driver name mapping. */
/* User needs to provide the implementation of USARTX_GetFreq/USARTX_InitPins/USARTX_DeinitPins for the enabled USART
 * instance. */
#define RTE_USART0            1
#define RTE_USART0_PIN_INIT   USART0_InitPins
#define RTE_USART0_PIN_DEINIT USART0_DeinitPins
#define RTE_USART0_DMA_EN     0

/*SPI Driver name mapping*/
/* User needs to provide the implementation of SPIX_GetFreq/SPIX_InitPins/SPIX_DeinitPins for the enabled SPI instance.
 */
#define RTE_SPI8            1
#define RTE_SPI8_PIN_INIT   SPI8_InitPins
#define RTE_SPI8_PIN_DEINIT SPI8_DeinitPins
#define RTE_SPI8_DMA_EN     0

/*I2C configuration*/
#define RTE_I2C4_Master_DMA_BASE DMA0
#define RTE_I2C4_Master_DMA_CH   21

/* USART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 1
#define USART1_RX_BUFFER_ENABLE 0
#define USART2_RX_BUFFER_ENABLE 0
#define USART3_RX_BUFFER_ENABLE 0
#define USART4_RX_BUFFER_ENABLE 0
#define USART5_RX_BUFFER_ENABLE 0
#define USART6_RX_BUFFER_ENABLE 0
#define USART7_RX_BUFFER_ENABLE 0

#define RTE_USART0_PIN_INIT        USART0_InitPins
#define RTE_USART0_PIN_DEINIT      USART0_DeinitPins
#define RTE_USART0_DMA_TX_CH       5
#define RTE_USART0_DMA_TX_DMA_BASE DMA0
#define RTE_USART0_DMA_RX_CH       4
#define RTE_USART0_DMA_RX_DMA_BASE DMA0

/* SPI configuration. */

#define RTE_SPI8_SSEL_NUM        kSPI_Ssel1
#define RTE_SPI8_PIN_INIT        SPI8_InitPins
#define RTE_SPI8_PIN_DEINIT      SPI8_DeinitPins
#define RTE_SPI8_DMA_TX_CH       19
#define RTE_SPI8_DMA_TX_DMA_BASE DMA0
#define RTE_SPI8_DMA_RX_CH       18
#define RTE_SPI8_DMA_RX_DMA_BASE DMA0
#endif /* _RTE_DEVICE_H */
