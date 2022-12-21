/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
* @file comm_if_uart.c
* @brief The comm_if_uart.c file implements comm interface for the UART.
*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Driver_USART.h"
#include "comm_interface.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
* Prototypes
******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

int32_t COMM_UART_GetCapabilities(comm_handle_t *pHandle)
{
    // @todo the implementation.
    return COMM_INTERFACE_OK;
}

int32_t COMM_UART_Init(comm_handle_t *pHandle, void *pCommInstance, COMM_Event_t event, void *pInitializeData)
{
    // @todo handle the pointers and validation properly.
    pHandle->pComm = pCommInstance;
    //@todo use the rest of argument properly.
    // SDK CMSIS driver adoption; init call will be done by the user application.
    //((ARM_DRIVER_USART *)(pHandle->pComm))->Initialize(event);
    return COMM_INTERFACE_OK;
}
int32_t COMM_UART_Config(comm_handle_t *pHandle, void *pConfigData)
{
    // @todo the implementation.
    comm_control_t *pControl = (comm_control_t *)pConfigData;
    return ((ARM_DRIVER_USART *)(pHandle->pComm))->Control(pControl->control, pControl->arg);
}
int32_t COMM_UART_Send(comm_handle_t *pHandle, void *pData, uint32_t size)
{
    //@todo the validation of the pointer
    return ((ARM_DRIVER_USART *)(pHandle->pComm))->Send(pData, size);
}
int32_t COMM_UART_Receive(comm_handle_t *pHandle, void *pData, uint32_t size)
{
    //@todo the validation of the pointer
    return ((ARM_DRIVER_USART *)(pHandle->pComm))->Receive(pData, size);
}
int32_t COMM_UART_GetStatus(comm_handle_t *pHandle)
{
    //@todo the validation of the pointer
    return pHandle->status;
}
// End USART Interface

comm_interface_t commUART = {
    COMM_UART_GetCapabilities, COMM_UART_Init, COMM_UART_Config, COMM_UART_Send, COMM_UART_Receive, COMM_UART_GetStatus,
};
