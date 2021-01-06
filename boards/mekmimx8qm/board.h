/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/* SCFW includes */
#include "main/rpc.h"
#include "svc/pm/pm_api.h"
#include "svc/irq/irq_api.h"
#include "svc/timer/timer_api.h"
#include "svc/misc/misc_api.h"

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "MEK-MIMX8QM"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BAUDRATE 115200u

#if defined(MIMX8QM_CM4_CORE0)
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) CM4_0__LPUART
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_SC_RSRC  SC_R_M4_0_UART
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_M4_0_Lpuart
#define BOARD_UART_IRQ            M4_0_LPUART_IRQn
#define BOARD_UART_IRQ_HANDLER    M4_0_LPUART_IRQHandler
#define BOARD_M4_CPU_RSRC         SC_R_M4_0_PID0
#elif defined(MIMX8QM_CM4_CORE1)
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) DMA__LPUART2
#define BOARD_DEBUG_UART_INSTANCE 4U
#define BOARD_DEBUG_UART_SC_RSRC  SC_R_UART_2
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_DMA_Lpuart2
#define BOARD_UART_IRQ            DMA_UART2_INT_IRQn
#define BOARD_UART_IRQ_HANDLER    DMA_UART2_INT_IRQHandler
#define BOARD_M4_CPU_RSRC         SC_R_M4_1_PID0
#else
#error "No valid BOARD_DEBUG_UART_BASEADDR defined."
#endif

#define BOARD_ENET0_PHY_ADDRESS (0x00)

/* DISPLAY 0: MIPI DSI0. */
#define BOARD_DISPLAY0_I2C_BASEADDR DI_MIPI_0__LPI2C0
#define BOARD_DISPLAY0_I2C_RSRC     SC_R_MIPI_0_I2C_0

/* DISPLAY 1: MIPI DSI1. */
#define BOARD_DISPLAY1_I2C_BASEADDR DI_MIPI_1__LPI2C0
#define BOARD_DISPLAY1_I2C_RSRC     SC_R_MIPI_1_I2C_0

/* DISPLAY 2: LVDS0 CH0. */
#define BOARD_DISPLAY2_I2C_BASEADDR DI_LVDS_0__LPI2C1
#define BOARD_DISPLAY2_I2C_RSRC     SC_R_LVDS_0_I2C_0 /* LPI2C0 & LPI2C1 share one resource. */

/* DISPLAY 3: LVDS0 CH1. */
#define BOARD_DISPLAY3_I2C_BASEADDR DI_LVDS_0__LPI2C1
#define BOARD_DISPLAY3_I2C_RSRC     SC_R_LVDS_0_I2C_0 /* LPI2C0 & LPI2C1 share one resource. */

/* DISPLAY 4: LVDS1 CH0. */
#define BOARD_DISPLAY4_I2C_BASEADDR DI_LVDS_1__LPI2C1
#define BOARD_DISPLAY4_I2C_RSRC     SC_R_LVDS_1_I2C_0 /* LPI2C0 & LPI2C1 share one resource. */

/* DISPLAY 5: LVDS1 CH1. */
#define BOARD_DISPLAY5_I2C_BASEADDR DI_LVDS_1__LPI2C1
#define BOARD_DISPLAY5_I2C_RSRC     SC_R_LVDS_1_I2C_0 /* LPI2C0 & LPI2C1 share one resource. */

/* CAMERA 0: MIPI CSI 0. */
#define BOARD_CAMERA0_I2C_BASEADDR MIPI_CSI_0__LPI2C
#define BOARD_CAMERA0_I2C_RSRC     SC_R_CSI_0_I2C_0

/* CAMERA 1: MIPI CSI 1. */
#define BOARD_CAMERA1_I2C_BASEADDR MIPI_CSI_1__LPI2C
#define BOARD_CAMERA1_I2C_RSRC     SC_R_CSI_1_I2C_0

#define BOARD_CODEC_I2C_BASEADDR   DMA__LPI2C1
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_DMA_Lpi2c1)
#define BOARD_CODEC_I2C_INSTANCE   12U /* Codec I2C on CPU board: DMA__LPI2C1. */
#define BOARD_CS42888_I2C_ADDR     0x48
#define BOARD_CS42888_I2C_INSTANCE 1U /* Codec I2C on AUDIO card: CM4_1__LPI2C1. */

/* VRING used for communicate with Linux */
#if defined(MIMX8QM_CM4_CORE0)
#define VDEV0_VRING_BASE (0x90000000U)
#define VDEV1_VRING_BASE (0x90010000U)
#elif defined(MIMX8QM_CM4_CORE1)
#define VDEV0_VRING_BASE (0x90100000U)
#define VDEV1_VRING_BASE (0x90110000U)
#else
#error "No valid VDEVn_VRING_BASE defined."
#endif
#define RESOURCE_TABLE_OFFSET (0xFF000)

/* VRING used for communicate between M40 and M41 */
#define M40_M41_VRING_BASE (0x90200000U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
sc_ipc_t BOARD_InitRpc(void);
sc_ipc_t BOARD_GetRpcHandle(void);
void BOARD_InitDebugConsole(void);
void BOARD_InitMemory(void);

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
void BOARD_LPI2C_Deinit(LPI2C_Type *base);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_SendWithoutSubAddr(LPI2C_Type *base,
                                        uint32_t baudRate_Hz,
                                        uint8_t deviceAddress,
                                        uint8_t *txBuff,
                                        uint8_t txBuffSize,
                                        uint8_t needStop);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
status_t BOARD_LPI2C_ReceiveWithoutSubAddr(LPI2C_Type *base,
                                           uint32_t baudRate_Hz,
                                           uint8_t deviceAddress,
                                           uint8_t *txBuff,
                                           uint8_t txBuffSize,
                                           uint8_t needStop);
status_t BOARD_LPI2C_SendSCCB(LPI2C_Type *base,
                              uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subaddressSize,
                              uint8_t *txBuff,
                              uint8_t txBuffSize);
status_t BOARD_LPI2C_ReceiveSCCB(LPI2C_Type *base,
                                 uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subaddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize);

void BOARD_Display0_I2C_Init(void);
void BOARD_Display0_I2C_Deinit(void);
status_t BOARD_Display0_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display0_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_Display1_I2C_Init(void);
void BOARD_Display1_I2C_Deinit(void);
status_t BOARD_Display1_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display1_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/* LVDS 0 CH 0 */
void BOARD_Display2_I2C_Init(void);
void BOARD_Display2_I2C_Deinit(void);
status_t BOARD_Display2_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display2_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/* LVDS 0 CH 1 */
void BOARD_Display3_I2C_Init(void);
void BOARD_Display3_I2C_Deinit(void);
status_t BOARD_Display3_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display3_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/* LVDS 1 CH 0 */
void BOARD_Display4_I2C_Init(void);
void BOARD_Display4_I2C_Deinit(void);
status_t BOARD_Display4_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display4_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/* LVDS 1 CH 1 */
void BOARD_Display5_I2C_Init(void);
void BOARD_Display5_I2C_Deinit(void);
status_t BOARD_Display5_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display5_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_Camera0_I2C_Init(void);
void BOARD_Camera0_I2C_Deinit(void);
status_t BOARD_Camera0_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera0_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_Camera1_I2C_Init(void);
void BOARD_Camera1_I2C_Deinit(void);
status_t BOARD_Camera1_I2C_SendSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Camera1_I2C_ReceiveSCCB(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
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
