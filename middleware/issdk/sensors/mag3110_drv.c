/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mag3110_drv.c
 * @brief The mag3110_drv.c file implements the MAG3110 sensor driver interfaces.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "mag3110_drv.h"

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
int32_t MAG3110_I2C_Initialize(
    mag3110_i2c_sensorhandle_t *pSensorHandle, ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg;

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, MAG3110_WHO_AM_I, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
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

void MAG3110_I2C_SetIdleTask(mag3110_i2c_sensorhandle_t *pSensorHandle,
                             registeridlefunction_t idleTask,
                             void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t MAG3110_I2C_Configure(mag3110_i2c_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
{
    int32_t status;

    /*! Validate for the correct handle and register write list.*/
    if ((pSensorHandle == NULL) || (pRegWriteList == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before applying configuration.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /*! Put the device into standby mode so that configuration can be applied.*/
    status = Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                MAG3110_CTRL_REG1, MAG3110_CTRL_REG1_AC_STANDBY, MAG3110_CTRL_REG1_AC_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /*! Apply the Sensor Configuration based on the Register Write List */
    status = Sensor_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                              pRegWriteList);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /*! Put the device into active mode and ready for reading data.*/
    status = Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                MAG3110_CTRL_REG1, MAG3110_CTRL_REG1_AC_ACTIVE, MAG3110_CTRL_REG1_AC_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t MAG3110_I2C_ReadData(mag3110_i2c_sensorhandle_t *pSensorHandle,
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

int32_t MAG3110_I2C_DeInit(mag3110_i2c_sensorhandle_t *pSensorHandle)
{
    int32_t status;

    if (pSensorHandle == NULL)
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before triggering sensor reset.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /*! Trigger sensor device reset.*/
    status = Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                MAG3110_CTRL_REG2, MAG3110_CTRL_REG2_MAG_RST_EN, MAG3110_CTRL_REG2_MAG_RST_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }
    else
    {
        /*! De-initialize sensor handle. */
        pSensorHandle->isInitialized = false;
    }

    return SENSOR_ERROR_NONE;
}

void MAG3110_CalibrateHardIronOffset(int16_t* xValue, int16_t* yValue, int16_t* zValue)
{
    static int16_t xOffsetMax = 0x8000, yOffsetMax = 0x8000, zOffsetMax = 0x8000,
                   xOffsetMin = 0x7FFF, yOffsetMin = 0x7FFF, zOffsetMin = 0x7FFF;

    xOffsetMax = (*xValue > xOffsetMax)?(*xValue):(xOffsetMax);
    xOffsetMin = (*xValue < xOffsetMin)?(*xValue):(xOffsetMin);

    yOffsetMax = (*yValue > yOffsetMax)?(*yValue):(yOffsetMax);
    yOffsetMin = (*yValue < yOffsetMin)?(*yValue):(yOffsetMin);

    zOffsetMax = (*zValue > zOffsetMax)?(*zValue):(zOffsetMax);
    zOffsetMin = (*zValue < zOffsetMin)?(*zValue):(zOffsetMin);

    *xValue -= (xOffsetMax+xOffsetMin)/2;
    *yValue -= (yOffsetMax+yOffsetMin)/2;
    *zValue -= (zOffsetMax+zOffsetMin)/2;
}
