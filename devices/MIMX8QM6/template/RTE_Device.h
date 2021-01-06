/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2020 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* UART Select, LPUART0 - LPUART6. */
/* USART instance mapping */
#define LPUART0 CM4_0__LPUART
#define LPUART1 CM4_1__LPUART
#define LPUART2 DMA__LPUART0
#define LPUART3 DMA__LPUART1
#define LPUART4 DMA__LPUART2
#define LPUART5 DMA__LPUART3
#define LPUART6 DMA__LPUART4

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
#define RTE_USART4        0
#define RTE_USART4_DMA_EN 0
#define RTE_USART5        0
#define RTE_USART5_DMA_EN 0
#define RTE_USART6        0
#define RTE_USART6_DMA_EN 0

/* UART configuration. */
#define USART_RX_BUFFER_LEN     64
#define USART0_RX_BUFFER_ENABLE 0
#define USART1_RX_BUFFER_ENABLE 0
#define USART2_RX_BUFFER_ENABLE 0
#define USART3_RX_BUFFER_ENABLE 0
#define USART4_RX_BUFFER_ENABLE 0
#define USART5_RX_BUFFER_ENABLE 0
#define USART6_RX_BUFFER_ENABLE 0

/* Note: LPUART0, LPUART1 not support DMA mode */
#define RTE_USART2_PIN_INIT        LPUART2_InitPins
#define RTE_USART2_PIN_DEINIT      LPUART2_DeinitPins
#define RTE_USART2_DMA_TX_CH       13
#define RTE_USART2_DMA_TX_PERI_SEL 13
#define RTE_USART2_DMA_TX_DMA_BASE DMA__DMA0
#define RTE_USART2_DMA_RX_CH       12
#define RTE_USART2_DMA_RX_PERI_SEL 12
#define RTE_USART2_DMA_RX_DMA_BASE DMA__DMA0

#define RTE_USART3_PIN_INIT        LPUART3_InitPins
#define RTE_USART3_PIN_DEINIT      LPUART3_DeinitPins
#define RTE_USART3_DMA_TX_CH       15
#define RTE_USART3_DMA_TX_PERI_SEL 15
#define RTE_USART3_DMA_TX_DMA_BASE DMA__DMA0
#define RTE_USART3_DMA_RX_CH       14
#define RTE_USART3_DMA_RX_PERI_SEL 14
#define RTE_USART3_DMA_RX_DMA_BASE DMA__DMA0

#define RTE_USART4_PIN_INIT        LPUART4_InitPins
#define RTE_USART4_PIN_DEINIT      LPUART4_DeinitPins
#define RTE_USART4_DMA_TX_CH       17
#define RTE_USART4_DMA_TX_PERI_SEL 17
#define RTE_USART4_DMA_TX_DMA_BASE DMA__DMA0
#define RTE_USART4_DMA_RX_CH       16
#define RTE_USART4_DMA_RX_PERI_SEL 16
#define RTE_USART4_DMA_RX_DMA_BASE DMA__DMA0

#define RTE_USART5_PIN_INIT        LPUART5_InitPins
#define RTE_USART5_PIN_DEINIT      LPUART5_DeinitPins
#define RTE_USART5_DMA_TX_CH       19
#define RTE_USART5_DMA_TX_PERI_SEL 19
#define RTE_USART5_DMA_TX_DMA_BASE DMA__DMA0
#define RTE_USART5_DMA_RX_CH       18
#define RTE_USART5_DMA_RX_PERI_SEL 18
#define RTE_USART5_DMA_RX_DMA_BASE DMA__DMA0

#define RTE_USART6_PIN_INIT        LPUART6_InitPins
#define RTE_USART6_PIN_DEINIT      LPUART6_DeinitPins
#define RTE_USART6_DMA_TX_CH       21
#define RTE_USART6_DMA_TX_PERI_SEL 21
#define RTE_USART6_DMA_TX_DMA_BASE DMA__DMA0
#define RTE_USART6_DMA_RX_CH       20
#define RTE_USART6_DMA_RX_PERI_SEL 20
#define RTE_USART6_DMA_RX_DMA_BASE DMA__DMA0

/* I2C Select, LPI2C0 - LPI2C6. */
/* LPI2C instance mapping */
#define LPI2C0 CM4_0__LPI2C
#define LPI2C1 CM4_1__LPI2C
#define LPI2C2 DMA__LPI2C0
#define LPI2C3 DMA__LPI2C1
#define LPI2C4 DMA__LPI2C2
#define LPI2C5 DMA__LPI2C3
#define LPI2C6 DMA__LPI2C4

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
#define RTE_I2C4        0
#define RTE_I2C4_DMA_EN 0
#define RTE_I2C5        0
#define RTE_I2C5_DMA_EN 0
#define RTE_I2C6        0
#define RTE_I2C6_DMA_EN 0

/* LPI2C configuration. */
/*Note: LPI2C0 and LPI2C1 not support DMA */
#define RTE_I2C2_PIN_INIT        LPI2C2_InitPins
#define RTE_I2C2_PIN_DEINIT      LPI2C2_DeinitPins
#define RTE_I2C2_DMA_TX_CH       1
#define RTE_I2C2_DMA_TX_PERI_SEL 1
#define RTE_I2C2_DMA_TX_DMA_BASE DMA__DMA1
#define RTE_I2C2_DMA_RX_CH       0
#define RTE_I2C2_DMA_RX_PERI_SEL 0
#define RTE_I2C2_DMA_RX_DMA_BASE DMA__DMA1

#define RTE_I2C3_PIN_INIT        LPI2C3_InitPins
#define RTE_I2C3_PIN_DEINIT      LPI2C3_DeinitPins
#define RTE_I2C3_DMA_TX_CH       3
#define RTE_I2C3_DMA_TX_PERI_SEL 3
#define RTE_I2C3_DMA_TX_DMA_BASE DMA__DMA1
#define RTE_I2C3_DMA_RX_CH       2
#define RTE_I2C3_DMA_RX_PERI_SEL 2
#define RTE_I2C3_DMA_RX_DMA_BASE DMA__DMA1

#define RTE_I2C4_PIN_INIT        LPI2C4_InitPins
#define RTE_I2C4_PIN_DEINIT      LPI2C4_DeinitPins
#define RTE_I2C4_DMA_TX_CH       5
#define RTE_I2C4_DMA_TX_PERI_SEL 5
#define RTE_I2C4_DMA_TX_DMA_BASE DMA__DMA1
#define RTE_I2C4_DMA_RX_CH       4
#define RTE_I2C4_DMA_RX_PERI_SEL 4
#define RTE_I2C4_DMA_RX_DMA_BASE DMA__DMA1

#define RTE_I2C5_PIN_INIT        LPI2C5_InitPins
#define RTE_I2C5_PIN_DEINIT      LPI2C5_DeinitPins
#define RTE_I2C5_DMA_TX_CH       7
#define RTE_I2C5_DMA_TX_PERI_SEL 7
#define RTE_I2C5_DMA_TX_DMA_BASE DMA__DMA1
#define RTE_I2C5_DMA_RX_CH       6
#define RTE_I2C5_DMA_RX_PERI_SEL 6
#define RTE_I2C5_DMA_RX_DMA_BASE DMA__DMA1

#define RTE_I2C6_PIN_INIT        LPI2C6_InitPins
#define RTE_I2C6_PIN_DEINIT      LPI2C6_DeinitPins
#define RTE_I2C6_DMA_TX_CH       9
#define RTE_I2C6_DMA_TX_PERI_SEL 9
#define RTE_I2C6_DMA_TX_DMA_BASE DMA__DMA1
#define RTE_I2C6_DMA_RX_CH       8
#define RTE_I2C6_DMA_RX_PERI_SEL 8
#define RTE_I2C6_DMA_RX_DMA_BASE DMA__DMA1

/* SPI Select, LPSPI0 - LPSPI3. */
#define LPSPI0 DMA__LPSPI0
#define LPSPI1 DMA__LPSPI1
#define LPSPI2 DMA__LPSPI2
#define LPSPI3 DMA__LPSPI3

/* User needs to provide the implementation of SPIX_GetFreq/SPIX_InitPins/SPIX_DeinitPins for the enabled SPI instance.
 */
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
#define RTE_SPI0_MASTER_PCS_PIN_SEL     kLPSPI_MasterPcs0
#define RTE_SPI0_PIN_INIT               SPI0_InitPins
#define RTE_SPI0_PIN_DEINIT             SPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH              1
#define RTE_SPI0_DMA_TX_PERI_SEL        1
#define RTE_SPI0_DMA_TX_DMA_BASE        DMA__DMA0
#define RTE_SPI0_DMA_RX_CH              0
#define RTE_SPI0_DMA_RX_PERI_SEL        0
#define RTE_SPI0_DMA_RX_DMA_BASE        DMA__DMA0

#define RTE_SPI1_PCS_TO_SCK_DELAY       1000
#define RTE_SPI1_SCK_TO_PSC_DELAY       1000
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI1_MASTER_PCS_PIN_SEL     kLPSPI_MasterPcs0
#define RTE_SPI1_PIN_INIT               SPI1_InitPins
#define RTE_SPI1_PIN_DEINIT             SPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH              3
#define RTE_SPI1_DMA_TX_PERI_SEL        3
#define RTE_SPI1_DMA_TX_DMA_BASE        DMA__DMA0
#define RTE_SPI1_DMA_RX_CH              2
#define RTE_SPI1_DMA_RX_PERI_SEL        2
#define RTE_SPI1_DMA_RX_DMA_BASE        DMA__DMA0

#define RTE_SPI2_PCS_TO_SCK_DELAY       1000
#define RTE_SPI2_SCK_TO_PSC_DELAY       1000
#define RTE_SPI2_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI2_MASTER_PCS_PIN_SEL     kLPSPI_MasterPcs0
#define RTE_SPI2_PIN_INIT               SPI2_InitPins
#define RTE_SPI2_PIN_DEINIT             SPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH              5
#define RTE_SPI2_DMA_TX_PERI_SEL        5
#define RTE_SPI2_DMA_TX_DMA_BASE        DMA__DMA0
#define RTE_SPI2_DMA_RX_CH              4
#define RTE_SPI2_DMA_RX_PERI_SEL        4
#define RTE_SPI2_DMA_RX_DMA_BASE        DMA__DMA0

#define RTE_SPI3_PCS_TO_SCK_DELAY       1000
#define RTE_SPI3_SCK_TO_PSC_DELAY       1000
#define RTE_SPI3_BETWEEN_TRANSFER_DELAY 1000
#define RTE_SPI3_MASTER_PCS_PIN_SEL     kLPSPI_MasterPcs0
#define RTE_SPI3_PIN_INIT               SPI3_InitPins
#define RTE_SPI3_PIN_DEINIT             SPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH              7
#define RTE_SPI3_DMA_TX_PERI_SEL        7
#define RTE_SPI3_DMA_TX_DMA_BASE        DMA__DMA0
#define RTE_SPI3_DMA_RX_CH              6
#define RTE_SPI3_DMA_RX_PERI_SEL        6
#define RTE_SPI3_DMA_RX_DMA_BASE        DMA__DMA0

/* ENET configuration. */
#define RTE_ENET             1
#define RTE_ENET_PHY_ADDRESS 0
#define RTE_ENET_MII         0
#define RTE_ENET_RMII        1
#define RTE_ENET_RGMII       1

#endif /* _RTE_DEVICE_H */
