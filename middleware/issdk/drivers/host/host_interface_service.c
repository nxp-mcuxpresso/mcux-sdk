/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
* @file host_interface_service.c
* @brief The dhost_interface_servicec file implements host interface functions
*/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "host_interface_service.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern comm_interface_t commUART;

/*******************************************************************************
 * Functions
 *****************************************************************************/
int32_t HOST_Initialize(host_interface_handle_t *pHandle,
                        comm_type_t type,
                        void *pCommInstance,
                        comm_instance_type_t inType,
                        Host_Event_t event,
                        void *pInData)
{
    int32_t status;

    if (type == COMM_UART)
    {
        pHandle->pCommInterface = &commUART;
    }
    comm_interface_t *pCommInt = pHandle->pCommInterface;
    pHandle->event = event;
    pHandle->pInData = pInData;
    pHandle->instanceType = inType;
    // call interface function with appropriate comm instance.
    status = pCommInt->Init(&pHandle->commHandle, (void *)pCommInstance, pHandle->event, pHandle->pInData);

    return status;
}

int32_t HOST_Configure(host_interface_handle_t *pHandle, void *pConfigData)
{
    int32_t status;

    comm_interface_t *pCommInt = pHandle->pCommInterface;
    status = pCommInt->Configure(&pHandle->commHandle, pConfigData);
    return status;
}

int32_t HOST_Send(host_interface_handle_t *pHandle, uint8_t *pData, uint32_t size)
{
    int32_t status;

    comm_interface_t *pCommInt = pHandle->pCommInterface;
    status = pCommInt->Send(&pHandle->commHandle, pData, size);
    return status;
}

int32_t HOST_Receive(
    host_interface_handle_t *pHandle, uint8_t *pData, uint32_t *pRecvSize, uint32_t size, BlockRead_t process)
{
    int32_t status;

    comm_interface_t *pCommInt = pHandle->pCommInterface;
    // Call Host Data format specified callback for block read data
    if ((process != NULL) && (pHandle->instanceType == COMM_BLOCKING))
    {
        process(pHandle, pData);
        status = HOST_INTERFACE_OK;
    }
    else
    {
        status = pCommInt->Receive(&pHandle->commHandle, pData, size);
    }
    return status;
}
