/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

#include "pin_mux.h"

/* LPUART Select, LPUART0-13(cm33_core0), LPUART17-20(cm33_core1). */
/* User needs to provide the implementation of LPUARTX_GetFreq/LPUARTX_InitPins/LPUARTX_DeinitPins for the enabled
 * LPUART instance. */
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
#define RTE_USART17        0
#define RTE_USART17_DMA_EN 0
#define RTE_USART18        0
#define RTE_USART18_DMA_EN 0
#define RTE_USART19        0
#define RTE_USART19_DMA_EN 0
#define RTE_USART20        0
#define RTE_USART20_DMA_EN 0

/* USART configuration. */
#define RTE_USART0_PIN_INIT        LPUART0_InitPins
#define RTE_USART0_PIN_DEINIT      LPUART0_DeinitPins
#define RTE_USART0_DMA_TX_CH       0
#define RTE_USART0_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Tx
#define RTE_USART0_DMA_TX_DMA_BASE DMA0
#define RTE_USART0_DMA_RX_CH       1
#define RTE_USART0_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Rx
#define RTE_USART0_DMA_RX_DMA_BASE DMA0

#define RTE_USART1_PIN_INIT        LPUART1_InitPins
#define RTE_USART1_PIN_DEINIT      LPUART1_DeinitPins
#define RTE_USART1_DMA_TX_CH       2
#define RTE_USART1_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Tx
#define RTE_USART1_DMA_TX_DMA_BASE DMA0
#define RTE_USART1_DMA_RX_CH       3
#define RTE_USART1_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Rx
#define RTE_USART1_DMA_RX_DMA_BASE DMA0

#define RTE_USART2_PIN_INIT        LPUART2_InitPins
#define RTE_USART2_PIN_DEINIT      LPUART2_DeinitPins
#define RTE_USART2_DMA_TX_CH       4
#define RTE_USART2_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Tx
#define RTE_USART2_DMA_TX_DMA_BASE DMA0
#define RTE_USART2_DMA_RX_CH       5
#define RTE_USART2_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Rx
#define RTE_USART2_DMA_RX_DMA_BASE DMA0

#define RTE_USART3_PIN_INIT        LPUART3_InitPins
#define RTE_USART3_PIN_DEINIT      LPUART3_DeinitPins
#define RTE_USART3_DMA_TX_CH       6
#define RTE_USART3_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Tx
#define RTE_USART3_DMA_TX_DMA_BASE DMA0
#define RTE_USART3_DMA_RX_CH       7
#define RTE_USART3_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Rx
#define RTE_USART3_DMA_RX_DMA_BASE DMA0

#define RTE_USART4_PIN_INIT        LPUART4_InitPins
#define RTE_USART4_PIN_DEINIT      LPUART4_DeinitPins
#define RTE_USART4_DMA_TX_CH       8
#define RTE_USART4_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Tx
#define RTE_USART4_DMA_TX_DMA_BASE DMA0
#define RTE_USART4_DMA_RX_CH       9
#define RTE_USART4_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Rx
#define RTE_USART4_DMA_RX_DMA_BASE DMA0

#define RTE_USART5_PIN_INIT        LPUART5_InitPins
#define RTE_USART5_PIN_DEINIT      LPUART5_DeinitPins
#define RTE_USART5_DMA_TX_CH       10
#define RTE_USART5_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Tx
#define RTE_USART5_DMA_TX_DMA_BASE DMA0
#define RTE_USART5_DMA_RX_CH       11
#define RTE_USART5_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Rx
#define RTE_USART5_DMA_RX_DMA_BASE DMA0

#define RTE_USART6_PIN_INIT        LPUART6_InitPins
#define RTE_USART6_PIN_DEINIT      LPUART6_DeinitPins
#define RTE_USART6_DMA_TX_CH       12
#define RTE_USART6_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Tx
#define RTE_USART6_DMA_TX_DMA_BASE DMA0
#define RTE_USART6_DMA_RX_CH       13
#define RTE_USART6_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Rx
#define RTE_USART6_DMA_RX_DMA_BASE DMA0

#define RTE_USART7_PIN_INIT        LPUART7_InitPins
#define RTE_USART7_PIN_DEINIT      LPUART7_DeinitPins
#define RTE_USART7_DMA_TX_CH       14
#define RTE_USART7_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Tx
#define RTE_USART7_DMA_TX_DMA_BASE DMA0
#define RTE_USART7_DMA_RX_CH       15
#define RTE_USART7_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Rx
#define RTE_USART7_DMA_RX_DMA_BASE DMA0

#define RTE_USART8_PIN_INIT        LPUART8_InitPins
#define RTE_USART8_PIN_DEINIT      LPUART8_DeinitPins
#define RTE_USART8_DMA_TX_CH       0
#define RTE_USART8_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Tx
#define RTE_USART8_DMA_TX_DMA_BASE DMA1
#define RTE_USART8_DMA_RX_CH       1
#define RTE_USART8_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Rx
#define RTE_USART8_DMA_RX_DMA_BASE DMA1

#define RTE_USART9_PIN_INIT        LPUART9_InitPins
#define RTE_USART9_PIN_DEINIT      LPUART9_DeinitPins
#define RTE_USART9_DMA_TX_CH       2
#define RTE_USART9_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Tx
#define RTE_USART9_DMA_TX_DMA_BASE DMA1
#define RTE_USART9_DMA_RX_CH       3
#define RTE_USART9_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Rx
#define RTE_USART9_DMA_RX_DMA_BASE DMA1

#define RTE_USART10_PIN_INIT        LPUART10_InitPins
#define RTE_USART10_PIN_DEINIT      LPUART10_DeinitPins
#define RTE_USART10_DMA_TX_CH       4
#define RTE_USART10_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Tx
#define RTE_USART10_DMA_TX_DMA_BASE DMA1
#define RTE_USART10_DMA_RX_CH       5
#define RTE_USART10_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Rx
#define RTE_USART10_DMA_RX_DMA_BASE DMA1

#define RTE_USART11_PIN_INIT        LPUART11_InitPins
#define RTE_USART11_PIN_DEINIT      LPUART11_DeinitPins
#define RTE_USART11_DMA_TX_CH       6
#define RTE_USART11_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Tx
#define RTE_USART11_DMA_TX_DMA_BASE DMA1
#define RTE_USART11_DMA_RX_CH       7
#define RTE_USART11_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Rx
#define RTE_USART11_DMA_RX_DMA_BASE DMA1

#define RTE_USART12_PIN_INIT        LPUART12_InitPins
#define RTE_USART12_PIN_DEINIT      LPUART12_DeinitPins
#define RTE_USART12_DMA_TX_CH       8
#define RTE_USART12_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Tx
#define RTE_USART12_DMA_TX_DMA_BASE DMA1
#define RTE_USART12_DMA_RX_CH       9
#define RTE_USART12_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Rx
#define RTE_USART12_DMA_RX_DMA_BASE DMA1

#define RTE_USART13_PIN_INIT        LPUART13_InitPins
#define RTE_USART13_PIN_DEINIT      LPUART13_DeinitPins
#define RTE_USART13_DMA_TX_CH       10
#define RTE_USART13_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Tx
#define RTE_USART13_DMA_TX_DMA_BASE DMA1
#define RTE_USART13_DMA_RX_CH       11
#define RTE_USART13_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Rx
#define RTE_USART13_DMA_RX_DMA_BASE DMA1

#define RTE_USART17_PIN_INIT        LPUART17_InitPins
#define RTE_USART17_PIN_DEINIT      LPUART17_DeinitPins
#define RTE_USART17_DMA_TX_CH       0
#define RTE_USART17_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Tx
#define RTE_USART17_DMA_TX_DMA_BASE DMA2
#define RTE_USART17_DMA_RX_CH       1
#define RTE_USART17_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Rx
#define RTE_USART17_DMA_RX_DMA_BASE DMA2

#define RTE_USART18_PIN_INIT        LPUART18_InitPins
#define RTE_USART18_PIN_DEINIT      LPUART18_DeinitPins
#define RTE_USART18_DMA_TX_CH       2
#define RTE_USART18_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Tx
#define RTE_USART18_DMA_TX_DMA_BASE DMA2
#define RTE_USART18_DMA_RX_CH       3
#define RTE_USART18_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Rx
#define RTE_USART18_DMA_RX_DMA_BASE DMA2

#define RTE_USART19_PIN_INIT        LPUART19_InitPins
#define RTE_USART19_PIN_DEINIT      LPUART19_DeinitPins
#define RTE_USART19_DMA_TX_CH       4
#define RTE_USART19_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Tx
#define RTE_USART19_DMA_TX_DMA_BASE DMA2
#define RTE_USART19_DMA_RX_CH       5
#define RTE_USART19_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Rx
#define RTE_USART19_DMA_RX_DMA_BASE DMA2

#define RTE_USART20_PIN_INIT        LPUART20_InitPins
#define RTE_USART20_PIN_DEINIT      LPUART20_DeinitPins
#define RTE_USART20_DMA_TX_CH       6
#define RTE_USART20_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Tx
#define RTE_USART20_DMA_TX_DMA_BASE DMA2
#define RTE_USART20_DMA_RX_CH       7
#define RTE_USART20_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Rx
#define RTE_USART20_DMA_RX_DMA_BASE DMA2

/* I2C Select, I2C0-I2C13,I2C15, I2C17-I2C20 */
/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled I2C
 * instance.
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
#define RTE_I2C17        0
#define RTE_I2C17_DMA_EN 0
#define RTE_I2C18        0
#define RTE_I2C18_DMA_EN 0
#define RTE_I2C19        0
#define RTE_I2C19_DMA_EN 0
#define RTE_I2C20        0
#define RTE_I2C20_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C0_PIN_INIT        LPI2C0_InitPins
#define RTE_I2C0_PIN_DEINIT      LPI2C0_DeinitPins
#define RTE_I2C0_DMA_TX_CH       0
#define RTE_I2C0_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Tx
#define RTE_I2C0_DMA_TX_DMA_BASE DMA0
#define RTE_I2C0_DMA_RX_CH       1
#define RTE_I2C0_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Rx
#define RTE_I2C0_DMA_RX_DMA_BASE DMA0

#define RTE_I2C1_PIN_INIT        LPI2C1_InitPins
#define RTE_I2C1_PIN_DEINIT      LPI2C1_DeinitPins
#define RTE_I2C1_DMA_TX_CH       2
#define RTE_I2C1_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Tx
#define RTE_I2C1_DMA_TX_DMA_BASE DMA0
#define RTE_I2C1_DMA_RX_CH       3
#define RTE_I2C1_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Rx
#define RTE_I2C1_DMA_RX_DMA_BASE DMA0

#define RTE_I2C2_PIN_INIT        LPI2C2_InitPins
#define RTE_I2C2_PIN_DEINIT      LPI2C2_DeinitPins
#define RTE_I2C2_DMA_TX_CH       4
#define RTE_I2C2_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Tx
#define RTE_I2C2_DMA_TX_DMA_BASE DMA0
#define RTE_I2C2_DMA_RX_CH       5
#define RTE_I2C2_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Rx
#define RTE_I2C2_DMA_RX_DMA_BASE DMA0

#define RTE_I2C3_PIN_INIT        LPI2C3_InitPins
#define RTE_I2C3_PIN_DEINIT      LPI2C3_DeinitPins
#define RTE_I2C3_DMA_TX_CH       6
#define RTE_I2C3_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Tx
#define RTE_I2C3_DMA_TX_DMA_BASE DMA0
#define RTE_I2C3_DMA_RX_CH       7
#define RTE_I2C3_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Rx
#define RTE_I2C3_DMA_RX_DMA_BASE DMA0

#define RTE_I2C4_PIN_INIT        LPI2C4_InitPins
#define RTE_I2C4_PIN_DEINIT      LPI2C4_DeinitPins
#define RTE_I2C4_DMA_TX_CH       8
#define RTE_I2C4_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Tx
#define RTE_I2C4_DMA_TX_DMA_BASE DMA0
#define RTE_I2C4_DMA_RX_CH       9
#define RTE_I2C4_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Rx
#define RTE_I2C4_DMA_RX_DMA_BASE DMA0

#define RTE_I2C5_PIN_INIT        LPI2C5_InitPins
#define RTE_I2C5_PIN_DEINIT      LPI2C5_DeinitPins
#define RTE_I2C5_DMA_TX_CH       10
#define RTE_I2C5_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Tx
#define RTE_I2C5_DMA_TX_DMA_BASE DMA0
#define RTE_I2C5_DMA_RX_CH       11
#define RTE_I2C5_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Rx
#define RTE_I2C5_DMA_RX_DMA_BASE DMA0

#define RTE_I2C6_PIN_INIT        LPI2C6_InitPins
#define RTE_I2C6_PIN_DEINIT      LPI2C6_DeinitPins
#define RTE_I2C6_DMA_TX_CH       12
#define RTE_I2C6_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Tx
#define RTE_I2C6_DMA_TX_DMA_BASE DMA0
#define RTE_I2C6_DMA_RX_CH       13
#define RTE_I2C6_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Rx
#define RTE_I2C6_DMA_RX_DMA_BASE DMA0

#define RTE_I2C7_PIN_INIT        LPI2C7_InitPins
#define RTE_I2C7_PIN_DEINIT      LPI2C7_DeinitPins
#define RTE_I2C7_DMA_TX_CH       14
#define RTE_I2C7_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Tx
#define RTE_I2C7_DMA_TX_DMA_BASE DMA0
#define RTE_I2C7_DMA_RX_CH       15
#define RTE_I2C7_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Rx
#define RTE_I2C7_DMA_RX_DMA_BASE DMA0

#define RTE_I2C8_PIN_INIT        LPI2C8_InitPins
#define RTE_I2C8_PIN_DEINIT      LPI2C8_DeinitPins
#define RTE_I2C8_DMA_TX_CH       0
#define RTE_I2C8_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Tx
#define RTE_I2C8_DMA_TX_DMA_BASE DMA1
#define RTE_I2C8_DMA_RX_CH       1
#define RTE_I2C8_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Rx
#define RTE_I2C8_DMA_RX_DMA_BASE DMA1

#define RTE_I2C9_PIN_INIT        LPI2C9_InitPins
#define RTE_I2C9_PIN_DEINIT      LPI2C9_DeinitPins
#define RTE_I2C9_DMA_TX_CH       2
#define RTE_I2C9_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Tx
#define RTE_I2C9_DMA_TX_DMA_BASE DMA1
#define RTE_I2C9_DMA_RX_CH       3
#define RTE_I2C9_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Rx
#define RTE_I2C9_DMA_RX_DMA_BASE DMA1

#define RTE_I2C10_PIN_INIT        LPI2C10_InitPins
#define RTE_I2C10_PIN_DEINIT      LPI2C10_DeinitPins
#define RTE_I2C10_DMA_TX_CH       4
#define RTE_I2C10_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Tx
#define RTE_I2C10_DMA_TX_DMA_BASE DMA1
#define RTE_I2C10_DMA_RX_CH       5
#define RTE_I2C10_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Rx
#define RTE_I2C10_DMA_RX_DMA_BASE DMA1

#define RTE_I2C11_PIN_INIT        LPI2C11_InitPins
#define RTE_I2C11_PIN_DEINIT      LPI2C11_DeinitPins
#define RTE_I2C11_DMA_TX_CH       6
#define RTE_I2C11_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Tx
#define RTE_I2C11_DMA_TX_DMA_BASE DMA1
#define RTE_I2C11_DMA_RX_CH       7
#define RTE_I2C11_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Rx
#define RTE_I2C11_DMA_RX_DMA_BASE DMA1

#define RTE_I2C12_PIN_INIT        LPI2C12_InitPins
#define RTE_I2C12_PIN_DEINIT      LPI2C12_DeinitPins
#define RTE_I2C12_DMA_TX_CH       8
#define RTE_I2C12_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Tx
#define RTE_I2C12_DMA_TX_DMA_BASE DMA1
#define RTE_I2C12_DMA_RX_CH       9
#define RTE_I2C12_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Rx
#define RTE_I2C12_DMA_RX_DMA_BASE DMA1

#define RTE_I2C13_PIN_INIT        LPI2C13_InitPins
#define RTE_I2C13_PIN_DEINIT      LPI2C13_DeinitPins
#define RTE_I2C13_DMA_TX_CH       10
#define RTE_I2C13_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Tx
#define RTE_I2C13_DMA_TX_DMA_BASE DMA1
#define RTE_I2C13_DMA_RX_CH       11
#define RTE_I2C13_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Rx
#define RTE_I2C13_DMA_RX_DMA_BASE DMA1

#define RTE_I2C15_PIN_INIT        LPI2C15_InitPins
#define RTE_I2C15_PIN_DEINIT      LPI2C15_DeinitPins
#define RTE_I2C15_DMA_TX_CH       12
#define RTE_I2C15_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpi2c15Tx
#define RTE_I2C15_DMA_TX_DMA_BASE DMA1
#define RTE_I2C15_DMA_RX_CH       13
#define RTE_I2C15_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpi2c15Rx
#define RTE_I2C15_DMA_RX_DMA_BASE DMA1

#define RTE_I2C17_PIN_INIT        LPI2C17_InitPins
#define RTE_I2C17_PIN_DEINIT      LPI2C17_DeinitPins
#define RTE_I2C17_DMA_TX_CH       0
#define RTE_I2C17_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Tx
#define RTE_I2C17_DMA_TX_DMA_BASE DMA2
#define RTE_I2C17_DMA_RX_CH       1
#define RTE_I2C17_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Rx
#define RTE_I2C17_DMA_RX_DMA_BASE DMA2

#define RTE_I2C18_PIN_INIT        LPI2C18_InitPins
#define RTE_I2C18_PIN_DEINIT      LPI2C18_DeinitPins
#define RTE_I2C18_DMA_TX_CH       2
#define RTE_I2C18_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Tx
#define RTE_I2C18_DMA_TX_DMA_BASE DMA2
#define RTE_I2C18_DMA_RX_CH       3
#define RTE_I2C18_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Rx
#define RTE_I2C18_DMA_RX_DMA_BASE DMA2

#define RTE_I2C19_PIN_INIT        LPI2C19_InitPins
#define RTE_I2C19_PIN_DEINIT      LPI2C19_DeinitPins
#define RTE_I2C19_DMA_TX_CH       4
#define RTE_I2C19_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Tx
#define RTE_I2C19_DMA_TX_DMA_BASE DMA2
#define RTE_I2C19_DMA_RX_CH       5
#define RTE_I2C19_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Rx
#define RTE_I2C19_DMA_RX_DMA_BASE DMA2

#define RTE_I2C20_PIN_INIT        LPI2C20_InitPins
#define RTE_I2C20_PIN_DEINIT      LPI2C20_DeinitPins
#define RTE_I2C20_DMA_TX_CH       6
#define RTE_I2C20_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Tx
#define RTE_I2C20_DMA_TX_DMA_BASE DMA2
#define RTE_I2C20_DMA_RX_CH       7
#define RTE_I2C20_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Rx
#define RTE_I2C20_DMA_RX_DMA_BASE DMA2

/* SPI select, SPI0-SPI14, SPI16, SPI17-SPI20.*/
/* User needs to provide the implementation of LPSPIX_GetFreq/LPSPIX_InitPins/LPSPIX_DeinitPins for the enabled SPI
 * instance.
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
#define RTE_SPI17        0
#define RTE_SPI17_DMA_EN 0
#define RTE_SPI18        0
#define RTE_SPI18_DMA_EN 0
#define RTE_SPI19        0
#define RTE_SPI19_DMA_EN 0
#define RTE_SPI20        0
#define RTE_SPI20_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI0_PIN_INIT        LPSPI0_InitPins
#define RTE_SPI0_PIN_DEINIT      LPSPI0_DeinitPins
#define RTE_SPI0_DMA_TX_CH       0
#define RTE_SPI0_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Tx
#define RTE_SPI0_DMA_TX_DMA_BASE DMA0
#define RTE_SPI0_DMA_RX_CH       1
#define RTE_SPI0_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm0Rx
#define RTE_SPI0_DMA_RX_DMA_BASE DMA0

#define RTE_SPI1_PIN_INIT        LPSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT      LPSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH       2
#define RTE_SPI1_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Tx
#define RTE_SPI1_DMA_TX_DMA_BASE DMA0
#define RTE_SPI1_DMA_RX_CH       3
#define RTE_SPI1_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm1Rx
#define RTE_SPI1_DMA_RX_DMA_BASE DMA0

#define RTE_SPI2_PIN_INIT        LPSPI2_InitPins
#define RTE_SPI2_PIN_DEINIT      LPSPI2_DeinitPins
#define RTE_SPI2_DMA_TX_CH       4
#define RTE_SPI2_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Tx
#define RTE_SPI2_DMA_TX_DMA_BASE DMA0
#define RTE_SPI2_DMA_RX_CH       5
#define RTE_SPI2_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm2Rx
#define RTE_SPI2_DMA_RX_DMA_BASE DMA0

#define RTE_SPI3_PIN_INIT        LPSPI3_InitPins
#define RTE_SPI3_PIN_DEINIT      LPSPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH       6
#define RTE_SPI3_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Tx
#define RTE_SPI3_DMA_TX_DMA_BASE DMA0
#define RTE_SPI3_DMA_RX_CH       7
#define RTE_SPI3_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm3Rx
#define RTE_SPI3_DMA_RX_DMA_BASE DMA0

#define RTE_SPI4_PIN_INIT        LPSPI4_InitPins
#define RTE_SPI4_PIN_DEINIT      LPSPI4_DeinitPins
#define RTE_SPI4_DMA_TX_CH       8
#define RTE_SPI4_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Tx
#define RTE_SPI4_DMA_TX_DMA_BASE DMA0
#define RTE_SPI4_DMA_RX_CH       9
#define RTE_SPI4_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm4Rx
#define RTE_SPI4_DMA_RX_DMA_BASE DMA0

#define RTE_SPI5_PIN_INIT        LPSPI5_InitPins
#define RTE_SPI5_PIN_DEINIT      LPSPI5_DeinitPins
#define RTE_SPI5_DMA_TX_CH       10
#define RTE_SPI5_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Tx
#define RTE_SPI5_DMA_TX_DMA_BASE DMA0
#define RTE_SPI5_DMA_RX_CH       11
#define RTE_SPI5_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm5Rx
#define RTE_SPI5_DMA_RX_DMA_BASE DMA0

#define RTE_SPI6_PIN_INIT        LPSPI6_InitPins
#define RTE_SPI6_PIN_DEINIT      LPSPI6_DeinitPins
#define RTE_SPI6_DMA_TX_CH       12
#define RTE_SPI6_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Tx
#define RTE_SPI6_DMA_TX_DMA_BASE DMA0
#define RTE_SPI6_DMA_RX_CH       13
#define RTE_SPI6_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm6Rx
#define RTE_SPI6_DMA_RX_DMA_BASE DMA0

#define RTE_SPI7_PIN_INIT        LPSPI7_InitPins
#define RTE_SPI7_PIN_DEINIT      LPSPI7_DeinitPins
#define RTE_SPI7_DMA_TX_CH       14
#define RTE_SPI7_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Tx
#define RTE_SPI7_DMA_TX_DMA_BASE DMA0
#define RTE_SPI7_DMA_RX_CH       15
#define RTE_SPI7_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm7Rx
#define RTE_SPI7_DMA_RX_DMA_BASE DMA0

#define RTE_SPI8_PIN_INIT        LPSPI8_InitPins
#define RTE_SPI8_PIN_DEINIT      LPSPI8_DeinitPins
#define RTE_SPI8_DMA_TX_CH       0
#define RTE_SPI8_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Tx
#define RTE_SPI8_DMA_TX_DMA_BASE DMA1
#define RTE_SPI8_DMA_RX_CH       1
#define RTE_SPI8_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm8Rx
#define RTE_SPI8_DMA_RX_DMA_BASE DMA1

#define RTE_SPI9_PIN_INIT        LPSPI9_InitPins
#define RTE_SPI9_PIN_DEINIT      LPSPI9_DeinitPins
#define RTE_SPI9_DMA_TX_CH       2
#define RTE_SPI9_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Tx
#define RTE_SPI9_DMA_TX_DMA_BASE DMA1
#define RTE_SPI9_DMA_RX_CH       3
#define RTE_SPI9_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm9Rx
#define RTE_SPI9_DMA_RX_DMA_BASE DMA1

#define RTE_SPI10_PIN_INIT        LPSPI10_InitPins
#define RTE_SPI10_PIN_DEINIT      LPSPI10_DeinitPins
#define RTE_SPI10_DMA_TX_CH       4
#define RTE_SPI10_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Tx
#define RTE_SPI10_DMA_TX_DMA_BASE DMA1
#define RTE_SPI10_DMA_RX_CH       5
#define RTE_SPI10_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm10Rx
#define RTE_SPI10_DMA_RX_DMA_BASE DMA1

#define RTE_SPI11_PIN_INIT        LPSPI11_InitPins
#define RTE_SPI11_PIN_DEINIT      LPSPI11_DeinitPins
#define RTE_SPI11_DMA_TX_CH       6
#define RTE_SPI11_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Tx
#define RTE_SPI11_DMA_TX_DMA_BASE DMA1
#define RTE_SPI11_DMA_RX_CH       7
#define RTE_SPI11_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm11Rx
#define RTE_SPI11_DMA_RX_DMA_BASE DMA1

#define RTE_SPI12_PIN_INIT        LPSPI12_InitPins
#define RTE_SPI12_PIN_DEINIT      LPSPI12_DeinitPins
#define RTE_SPI12_DMA_TX_CH       8
#define RTE_SPI12_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Tx
#define RTE_SPI12_DMA_TX_DMA_BASE DMA1
#define RTE_SPI12_DMA_RX_CH       9
#define RTE_SPI12_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm12Rx
#define RTE_SPI12_DMA_RX_DMA_BASE DMA1

#define RTE_SPI13_PIN_INIT        LPSPI13_InitPins
#define RTE_SPI13_PIN_DEINIT      LPSPI13_DeinitPins
#define RTE_SPI13_DMA_TX_CH       10
#define RTE_SPI13_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Tx
#define RTE_SPI13_DMA_TX_DMA_BASE DMA1
#define RTE_SPI13_DMA_RX_CH       11
#define RTE_SPI13_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm13Rx
#define RTE_SPI13_DMA_RX_DMA_BASE DMA1

#define RTE_SPI14_PIN_INIT        LPSPI14_InitPins
#define RTE_SPI14_PIN_DEINIT      LPSPI14_DeinitPins
#define RTE_SPI14_DMA_TX_CH       12
#define RTE_SPI14_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpspi14Tx
#define RTE_SPI14_DMA_TX_DMA_BASE DMA1
#define RTE_SPI14_DMA_RX_CH       13
#define RTE_SPI14_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpspi14Rx
#define RTE_SPI14_DMA_RX_DMA_BASE DMA1

#define RTE_SPI16_PIN_INIT        LPSPI16_InitPins
#define RTE_SPI16_PIN_DEINIT      LPSPI16_DeinitPins
#define RTE_SPI16_DMA_TX_CH       14
#define RTE_SPI16_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpspi16Tx
#define RTE_SPI16_DMA_TX_DMA_BASE DMA1
#define RTE_SPI16_DMA_RX_CH       15
#define RTE_SPI16_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpspi16Rx
#define RTE_SPI16_DMA_RX_DMA_BASE DMA1

#define RTE_SPI17_PIN_INIT        LPSPI17_InitPins
#define RTE_SPI17_PIN_DEINIT      LPSPI17_DeinitPins
#define RTE_SPI17_DMA_TX_CH       0
#define RTE_SPI17_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Tx
#define RTE_SPI17_DMA_TX_DMA_BASE DMA2
#define RTE_SPI17_DMA_RX_CH       1
#define RTE_SPI17_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm17Rx
#define RTE_SPI17_DMA_RX_DMA_BASE DMA2

#define RTE_SPI18_PIN_INIT        LPSPI18_InitPins
#define RTE_SPI18_PIN_DEINIT      LPSPI18_DeinitPins
#define RTE_SPI18_DMA_TX_CH       2
#define RTE_SPI18_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Tx
#define RTE_SPI18_DMA_TX_DMA_BASE DMA2
#define RTE_SPI18_DMA_RX_CH       3
#define RTE_SPI18_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm18Rx
#define RTE_SPI18_DMA_RX_DMA_BASE DMA2

#define RTE_SPI19_PIN_INIT        LPSPI19_InitPins
#define RTE_SPI19_PIN_DEINIT      LPSPI19_DeinitPins
#define RTE_SPI19_DMA_TX_CH       4
#define RTE_SPI19_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Tx
#define RTE_SPI19_DMA_TX_DMA_BASE DMA2
#define RTE_SPI19_DMA_RX_CH       5
#define RTE_SPI19_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm19Rx
#define RTE_SPI19_DMA_RX_DMA_BASE DMA2

#define RTE_SPI20_PIN_INIT        LPSPI20_InitPins
#define RTE_SPI20_PIN_DEINIT      LPSPI20_DeinitPins
#define RTE_SPI20_DMA_TX_CH       6
#define RTE_SPI20_DMA_TX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Tx
#define RTE_SPI20_DMA_TX_DMA_BASE DMA2
#define RTE_SPI20_DMA_RX_CH       7
#define RTE_SPI20_DMA_RX_PERI_SEL (uint16_t) kDmaRequestMuxLpFlexcomm20Rx
#define RTE_SPI20_DMA_RX_DMA_BASE DMA2

#endif /* _RTE_DEVICE_H */
