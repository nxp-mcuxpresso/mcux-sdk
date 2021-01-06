/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"

/* SCFW includes */
#include "main/rpc.h"
#include "svc/pm/pm_api.h"

#include "main/imx8qx_pads.h"
#include "svc/pad/pad_api.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "VALMIMX8QX6"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE DEBUG_CONSOLE_DEVICE_TYPE_LPUART
#define BOARD_DEBUG_UART_BAUDRATE 115200u
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) CM4__LPUART
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_CLK_FREQ 6000000u
#define BOARD_UART_IRQ LPUART_CM_0_IRQn
#define BOARD_UART_IRQ_HANDLER LPUART0_IRQHandler
#define BOARD_DEBUG_UART_CLKSRC kCLOCK_IpSrcDummy
#define BOARD_BASEBOARD_PWR_GPIO LSIO__GPIO5
#define BOARD_BASEBOARD_PWR_GPIO_PIN 9U

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/
sc_ipc_t BOARD_InitRpc(void);
sc_ipc_t BOARD_GetRpcHandle(void);
void BOARD_InitDebugConsole(void);
void BOARD_InitPinsPre(void);
void BOARD_PowerOnBaseBoard(void);
void BOARD_InitMemory(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
