/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_clock.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME        "MCIMX7ULP-EVK"
#define MANUFACTURER_NAME "NXP"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE        kSerialPort_Uart
#define BOARD_DEBUG_UART_BAUDRATE    115200u
#define BOARD_DEBUG_UART_BASEADDR    LPUART0_BASE
#define BOARD_DEBUG_UART_INSTANCE    0U
#define BOARD_DEBUG_UART_CLK_FREQ    CLOCK_GetIpFreq(kCLOCK_Lpuart0)
#define BOARD_DEBUG_UART_PCC_ADDRESS kCLOCK_Lpuart0
#define BOARD_DEBUG_UART_CLKSRC      kCLOCK_IpSrcSystem
#define BOARD_UART_IRQ               LPUART0_IRQn
#define BOARD_UART_IRQ_HANDLER       LPUART0_IRQHandler

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR   LPI2C3
#define BOARD_ACCEL_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c3)

#define BOARD_CODEC_I2C_BASEADDR   LPI2C0
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)
#define BOARD_CODEC_I2C_INSTANCE   0U

#define BOARD_VOLP_GPIO        GPIOA
#define BOARD_VOLP_PORT        PORTA
#define BOARD_VOLP_GPIO_PIN    3U
#define BOARD_VOLP_IRQ         PCTLA_IRQn
#define BOARD_VOLP_IRQ_HANDLER PCTLA_IRQHandler
#define BOARD_VOLP_NAME        "VOL+"

#define BOARD_VOLM_GPIO        GPIOA
#define BOARD_VOLM_PORT        PORTA
#define BOARD_VOLM_GPIO_PIN    13U
#define BOARD_VOLM_IRQ         PCTLA_IRQn
#define BOARD_VOLM_IRQ_HANDLER PCTLA_IRQHandler
#define BOARD_VOLM_NAME        "VOL-"

#define VDEV0_VRING_BASE (0x9FF00000U)
#define VDEV1_VRING_BASE (0x9FF10000U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
