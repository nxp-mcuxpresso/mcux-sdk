/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mma8491q_drv.c
 * @brief The mma8491q_drv.c file implements the MMA8491 sensor driver interfaces.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "mma8491q_drv.h"

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
int32_t MMA8491Q_I2C_Initialize(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                                ARM_DRIVER_I2C *pBus,
                                uint8_t index,
                                uint16_t sAddress)
{
    int32_t status;
    MMA8491Q_STATUS_t reg = {.w = MMA8491Q_STATUS_RESERVED_MASK}; /* Set the reserved bits to 1. */

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Since this sensor does not have who am i register, we verify Status Register Reserved bits to validate
     * communication. */
    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, MMA8491Q_STATUS, 1, (uint8_t *)&reg);
    if ((ARM_DRIVER_OK != status) || (MMA8491Q_STATUS_RESERVED_ZERO != reg.b.reserved))
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveAddress = sAddress;
    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void MMA8491Q_I2C_SetIdleTask(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                              registeridlefunction_t idleTask,
                              void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t MMA8491Q_I2C_ReadData(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                              const registerreadlist_t *pReadList,
                              uint8_t *pBuffer)
{
    int32_t status;

    /*! Validate for the correct handle and register read list.*/
    if ((pSensorHandle == NULL) || (pReadList == NULL) || (pBuffer == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before reading sensor data.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /*! Parse through the read list and read the data one by one. */
    status = Sensor_I2C_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                             pReadList, pBuffer);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_READ;
    }

    return SENSOR_ERROR_NONE;
}
