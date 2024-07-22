/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "clock_config.h"
#if defined(BOARD_USE_ADP5585) && BOARD_USE_ADP5585
#include "fsl_adp5585.h"
#endif
#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
#include "fsl_pcal6524.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_INSTANCE   2U
#define BOARD_DEBUG_UART_BAUDRATE   115200U
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_UART_CLOCK_ROOT kCLOCK_Root_Lpuart2
#define BOARD_DEBUG_UART_CLK_FREQ   CLOCK_GetIpFreq(BOARD_DEBUG_UART_CLOCK_ROOT)

#define VDEV0_VRING_BASE (0xA4000000U)
#define VDEV1_VRING_BASE (0xA4010000U)

#define LED_INIT()
#define LED_TOGGLE()

#define BOARD_CODEC_I2C_BASEADDR LPI2C1
#define BOARD_CODEC_I2C_INSTANCE 1U

/* ADP5585 */
#define BOARD_ADP5585_I2C            LPI2C2
#define BOARD_ADP5585_I2C_ADDR       (0x34U)
#define BOARD_ADP5585_I2C_CLOCK_ROOT kCLOCK_Root_Lpi2c2
#define BOARD_ADP5585_I2C_CLOCK_FREQ CLOCK_GetIpFreq(BOARD_ADP5585_I2C_CLOCK_ROOT)

#define BOARD_ADP5585_PDM_MQS_SEL (2U)
#define BOARD_ADP5585_EXP_SEL     (4U)
#define BOARD_ADP5585_CAN_STBY    (8U)

/* PCAL6524 */
#define BOARD_PCAL6524_I2C            LPI2C2
#define BOARD_PCAL6524_I2C_ADDR       (0x22U)
#define BOARD_PCAL6524_I2C_CLOCK_ROOT kCLOCK_Root_Lpi2c2
#define BOARD_PCAL6524_I2C_CLOCK_FREQ CLOCK_GetIpFreq(BOARD_PCAL6524_I2C_CLOCK_ROOT)

#define BOARD_PCAL6524_ENET1_NRST (8U + 7U)
#define BOARD_PCAL6524_ENET2_NRST (16U + 0U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize,
                          uint32_t flags);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize,
                             uint32_t flags);
#if defined(BOARD_USE_ADP5585) && BOARD_USE_ADP5585
void BOARD_ADP5585_I2C_Init(void);
status_t BOARD_ADP5585_I2C_Send(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subAddressSize,
                                const uint8_t *txBuff,
                                uint8_t txBuffSize,
                                uint32_t flags);
status_t BOARD_ADP5585_I2C_Receive(uint8_t deviceAddress,
                                   uint32_t subAddress,
                                   uint8_t subAddressSize,
                                   uint8_t *rxBuff,
                                   uint8_t rxBuffSize,
                                   uint32_t flags);

void BOARD_InitADP5585(adp5585_handle_t *handle);
#endif /* BOARD_USE_ADP5585 */

#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
void BOARD_PCAL6524_I2C_Init(void);
status_t BOARD_PCAL6524_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags);
status_t BOARD_PCAL6524_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags);

void BOARD_InitPCAL6524(pcal6524_handle_t *handle);
#endif /* BOARD_USE_PCAL6524 */

#endif

void BOARD_ConfigMPU(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _BOARD_H_ */
