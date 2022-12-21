/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file register_io_i2c.c
 * @brief The register_io_i2c.c file contains definitions for low-level interface functions
 *  for reading and writing sensor registers.
 */

/* Standard C Includes */
#include <string.h>

/* ISSDK Includes */
#include "issdk_hal.h"
#include "register_io_i2c.h"

/*******************************************************************************
 * Types
 ******************************************************************************/
#define I2C_COUNT (sizeof(i2cBases) / sizeof(void *))

/*******************************************************************************
 * Variables
 ******************************************************************************/
I2C_Type *const i2cBases[] = I2C_BASE_PTRS;
volatile bool b_I2C_CompletionFlag[I2C_COUNT] = {false};
volatile uint32_t g_I2C_ErrorEvent[I2C_COUNT] = {ARM_I2C_EVENT_TRANSFER_DONE};

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined(I2C0)
/* The I2C0 Signal Event Handler function. */
void I2C0_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[0] = event;
    }
    b_I2C_CompletionFlag[0] = true;
}
#endif

#if defined(I2C1)
/* The I2C1 Signal Event Handler function. */
void I2C1_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[1] = event;
    }
    b_I2C_CompletionFlag[1] = true;
}
#endif

#if defined(I2C2)
/* The I2C2 Signal Event Handler function. */
void I2C2_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[2] = event;
    }
    b_I2C_CompletionFlag[2] = true;
}
#endif

#if defined(I2C3)
/* The I2C3 Signal Event Handler function. */
void I2C3_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[3] = event;
    }
    b_I2C_CompletionFlag[3] = true;
}
#endif

#if defined(I2C4)
/* The I2C4 Signal Event Handler function. */
void I2C4_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[4] = event;
    }
    b_I2C_CompletionFlag[4] = true;
}
#endif

#if defined(I2C5)
/* The I2C5 Signal Event Handler function. */
void I2C5_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[5] = event;
    }
    b_I2C_CompletionFlag[5] = true;
}
#endif

#if defined(I2C6)
/* The I2C6 Signal Event Handler function. */
void I2C6_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[6] = event;
    }
    b_I2C_CompletionFlag[6] = true;
}
#endif

#if defined(I2C7)
/* The I2C7 Signal Event Handler function. */
void I2C7_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[7] = event;
    }
    b_I2C_CompletionFlag[7] = true;
}
#endif

#ifdef MIMXRT500_AGM01
#if defined(I2C11)
/* The I2C11 Signal Event Handler function. */
void I2C11_SignalEvent_t(uint32_t event)
{
    if (event != ARM_I2C_EVENT_TRANSFER_DONE)
    {
        g_I2C_ErrorEvent[11] = event;
    }
    b_I2C_CompletionFlag[11] = true;
}
#endif
#endif

/*! The interface function to block write sensor registers. */
int32_t Register_I2C_BlockWrite(ARM_DRIVER_I2C *pCommDrv,
                                registerDeviceInfo_t *devInfo,
                                uint16_t slaveAddress,
                                uint8_t offset,
                                const uint8_t *pBuffer,
                                uint8_t bytesToWrite)
{
    int32_t status;
    uint8_t buffer[SENSOR_MAX_REGISTER_COUNT];

    buffer[0] = offset;
    memcpy(buffer + 1, pBuffer, bytesToWrite);

    b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
    g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
    status = pCommDrv->MasterTransmit(slaveAddress, buffer, bytesToWrite + 1, false);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
        {
            pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
        {
            status = ARM_DRIVER_ERROR;
        }
    }

    return status;
}

/*! The interface function to write a sensor register. */
int32_t Register_I2C_Write(ARM_DRIVER_I2C *pCommDrv,
                           registerDeviceInfo_t *devInfo,
                           uint16_t slaveAddress,
                           uint8_t offset,
                           uint8_t value,
                           uint8_t mask,
                           bool repeatedStart)
{
    int32_t status;
    uint8_t config[] = {offset, 0x00};

    /*! Set the register based on the values in the register value pair configuration.*/
    if (mask)
    {
        b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
        g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
        /*! Send the register address to read from.*/
        status = pCommDrv->MasterTransmit(slaveAddress, &config[0], 1, true);
        if (ARM_DRIVER_OK == status)
        {
            /* Wait for completion without calling idle function */
            while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
            {
                if (devInfo->idleFunction)
                {
                    devInfo->idleFunction(devInfo->functionParam);
                }
                else
                {
                    __NOP();
                }
            };
            if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
            {
                pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
            }
            if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
            {
                return ARM_DRIVER_ERROR;
            }
        }
        else
        {
            return status;
        }
        b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
        g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
        /*! Read the value.*/
        status = pCommDrv->MasterReceive(slaveAddress, &config[1], 1, false);
        if (ARM_DRIVER_OK == status)
        {
            /* Wait for completion */
            while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
            {
                if (devInfo->idleFunction)
                {
                    devInfo->idleFunction(devInfo->functionParam);
                }
                else
                {
                    __NOP();
                }
            }
            if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
            {
                pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
            }
            if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
            {
                return ARM_DRIVER_ERROR;
            }
        }
        else
        {
            return status;
        }
        /*! 'OR' in the requested values to the current contents of the register */
        config[1] = (config[1] & ~mask) | value;
    }
    else
    {
        /*! Overwrite the register with specified value.*/
        config[1] = value;
    }

    b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
    g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
    /*!  Write the updated value. */
    status = pCommDrv->MasterTransmit(slaveAddress, config, sizeof(config), repeatedStart);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
        {
            pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
        {
            status = ARM_DRIVER_ERROR;
        }
    }

    return status;
}

/*! The interface function to read a sensor register. */
int32_t Register_I2C_Read(ARM_DRIVER_I2C *pCommDrv,
                          registerDeviceInfo_t *devInfo,
                          uint16_t slaveAddress,
                          uint8_t offset,
                          uint8_t length,
                          uint8_t *pOutBuffer)
{
    int32_t status;

    b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
    g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
    status = pCommDrv->MasterTransmit(slaveAddress, &offset, 1, true);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion without calling idle function. */
        while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        };
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
        {
            pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
        {
            return ARM_DRIVER_ERROR;
        }
    }
    else
    {
        return status;
    }

    b_I2C_CompletionFlag[devInfo->deviceInstance] = false;
    g_I2C_ErrorEvent[devInfo->deviceInstance] = ARM_I2C_EVENT_TRANSFER_DONE;
    /*! Read and update the value.*/
    status = pCommDrv->MasterReceive(slaveAddress, pOutBuffer, length, false);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_I2C_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] == ARM_I2C_EVENT_TRANSFER_INCOMPLETE)
        {
            pCommDrv->Control(ARM_I2C_ABORT_TRANSFER, 0);
        }
        if (g_I2C_ErrorEvent[devInfo->deviceInstance] != ARM_I2C_EVENT_TRANSFER_DONE)
        {
            status = ARM_DRIVER_ERROR;
        }
    }

    return status;
}
