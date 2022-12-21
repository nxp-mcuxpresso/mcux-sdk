/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file sensor_io_i2c.c
 * @brief The sensor_io_i2c.c file contains definitions for low-level interface functions
 *  for reading and writing data from/to sensor.
 */

#include "Driver_I2C.h"
#include "sensor_drv.h"
#include "systick_utils.h"
#include "sensor_io_i2c.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*! The interface function to block write commands to a sensor. */
int32_t Sensor_I2C_BlockWrite(ARM_DRIVER_I2C *pCommDrv,
                              registerDeviceInfo_t *devInfo,
                              uint16_t slaveAddress,
                              const registercommandlist_t *pCommandList,
                              uint8_t error_mask)
{
    int32_t status;
    bool commandComplete;
    uint8_t cocoBuffer[2] = {0};

    /*! Validate for the correct handle.*/
    if ((pCommDrv == NULL) || (pCommandList == NULL))
    {
        return SENSOR_ERROR_BAD_ADDRESS;
    }

    const registercommandlist_t *pCmd = pCommandList;
    /*! Update register values based on register write list unless the next Cmd is the list terminator */
    do
    { /*! Write the command based on the values in the command and value pair.*/
        status =
            Register_I2C_BlockWrite(pCommDrv, devInfo, slaveAddress, pCmd->writeTo, pCmd->pWriteBuffer, pCmd->numBytes);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_WRITE;
        }

        do
        { /*! Wait for Command Completion. */
            BOARD_DELAY_ms(1);
            status = Register_I2C_Read(pCommDrv, devInfo, slaveAddress, 0, sizeof(cocoBuffer), cocoBuffer);
            if (ARM_DRIVER_OK != status)
            {
                return SENSOR_ERROR_READ;
            }
            commandComplete = cocoBuffer[1] & 0x80;
            if (commandComplete && cocoBuffer[1] & error_mask)
            {
                return SENSOR_ERROR_WRITE;
            }
        } while (!commandComplete);
    } while ((++pCmd)->writeTo != 0xFFFF);

    return SENSOR_ERROR_NONE;
}

/*! The interface function to write register data to a sensor. */
int32_t Sensor_I2C_Write(ARM_DRIVER_I2C *pCommDrv,
                         registerDeviceInfo_t *devInfo,
                         uint16_t slaveAddress,
                         const registerwritelist_t *pRegWriteList)
{
    int32_t status;
    bool repeatedStart;

    /*! Validate for the correct handle.*/
    if ((pCommDrv == NULL) || (pRegWriteList == NULL))
    {
        return SENSOR_ERROR_BAD_ADDRESS;
    }

    const registerwritelist_t *pCmd = pRegWriteList;

    /*! Update register values based on register write list unless the next Cmd is the list terminator */
    do
    {
        repeatedStart = (pCmd + 1)->writeTo != 0xFFFF;
        /*! Set the register based on the values in the register value pair.*/
        status =
            Register_I2C_Write(pCommDrv, devInfo, slaveAddress, pCmd->writeTo, pCmd->value, pCmd->mask, repeatedStart);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_WRITE;
        }
        ++pCmd;
    } while (repeatedStart);

    return SENSOR_ERROR_NONE;
}

/*! The interface function to read register data from a sensor. */
int32_t Sensor_I2C_Read(ARM_DRIVER_I2C *pCommDrv,
                        registerDeviceInfo_t *devInfo,
                        uint16_t slaveAddress,
                        const registerreadlist_t *pReadList,
                        uint8_t *pOutBuffer)
{
    int32_t status;
    uint8_t *pBuf;

    /*! Validate for the correct handle.*/
    if (pCommDrv == NULL || pReadList == NULL || pOutBuffer == NULL)
    {
        return SENSOR_ERROR_BAD_ADDRESS;
    }
    const registerreadlist_t *pCmd = pReadList;

    /*! Traverse the read list and read the registers one by one unless the register read list numBytes is zero*/
    for (pBuf = pOutBuffer; pCmd->numBytes != 0; pCmd++)
    {
        status = Register_I2C_Read(pCommDrv, devInfo, slaveAddress, pCmd->readFrom, pCmd->numBytes, pBuf);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_READ;
        }
        pBuf += pCmd->numBytes;
    }
    return SENSOR_ERROR_NONE;
}
