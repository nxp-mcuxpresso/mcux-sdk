/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxpq3115_drv.h
 * @brief The fxpq3115_drv.h file describes the fxpq3115 driver interface and structures.
 */

#ifndef FXPQ3115_FI_H_
#define FXPQ3115_FI_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "fxpq3115.h"
#include "sensor_io_i2c.h"
#include "register_io_i2c.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define FXPQ3115_PRESSURE_CONV_FACTOR (64)     /* Will give Pascals */
#define FXPQ3115_ALTITUDE_CONV_FACTOR (65536)  /* Will give meters above MSL */
#define FXPQ3115_TEMPERATURE_CONV_FACTOR (256) /* Will give °C */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief This defines the sensor specific information. */
typedef struct
{
    registerDeviceInfo_t deviceInfo; /*!< I2C device context. */
    ARM_DRIVER_I2C *pCommDrv;        /*!< Pointer to the i2c driver. */
    bool isInitialized;              /*!< Init status.*/
    uint16_t slaveAddress;           /*!< slave address.*/
} fxpq3115_i2c_sensorhandle_t;

/*! @brief This structure defines the fxpq3115 data buffer in Pressure Mode.*/
typedef struct
{
    uint32_t timestamp;  /*!< Time stamp value in micro-seconds. */
    uint32_t pressure;   /*!< Sensor pressure output: unsigned 20-bits justified to MSBs. */
    int16_t temperature; /*!< Sensor temperature output; 2's complement 12-bits justified to MSBs.
                              MS 8-bits are integer degrees Celsius; LS 4-bits are fractional degrees Celsius. */
} fxpq3115_pressuredata_t;

/*! @brief This structure defines the fxpq3115 data buffer in Altitude Mode.*/
typedef struct
{
    uint32_t timestamp;  /*!< Time stamp value in micro-seconds. */
    int32_t altitude;    /*!< Sensor pressure/altitude output: MS 16-bits are integer meters; LS 4-bits are fractional
                              meters. */
    int16_t temperature; /*!< Sensor temperature output; 2's complement 12-bits justified to MSBs.
                              MS 8-bits are integer degrees Celsius; LS 4-bits are fractional degrees Celsius. */
} fxpq3115_altitudedata_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*! @brief       The interface function to initialize the sensor.
 *  @details     This function initialize the sensor and sensor handle.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @param[in]   whoami         WHO_AM_I value of the device.
 *  @constraints This should be the first API to be called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXPQ3115_I2C_Initialize() returns the status.
 */
int32_t FXPQ3115_I2C_Initialize(
    fxpq3115_i2c_sensorhandle_t *pSensorHandle, ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t whoAmi);

/*! @brief      :  The interface function to set the I2C Idle Task.
 *  @param[in]  :  fxpq3115_i2c_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on I2C Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after FXPQ3115_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void FXPQ3115_I2C_SetIdleTask(fxpq3115_i2c_sensorhandle_t *pSensorHandle,
                              registeridlefunction_t idleTask,
                              void *userParam);

/*! @brief       The interface function to configure he sensor.
 *  @details     This function configure the sensor with requested ODR, Range and registers in the regsiter pair array.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @param[in]   pRegWriteList      pointer to the register list.
 *  @constraints This can be called any number of times only after FXPQ3115_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXPQ3115_I2C_Configure() returns the status.
 */
int32_t FXPQ3115_I2C_Configure(fxpq3115_i2c_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pReadList      pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer        buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *                              command read in the list.
 *  @constraints This can be called only after FXPQ3115_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXPQ3115_I2C_ReadData() returns the status .
 */
int32_t FXPQ3115_I2C_ReadData(fxpq3115_i2c_sensorhandle_t *pSensorHandle,
                              const registerreadlist_t *pReadList,
                              uint8_t *pBuffer);

/*! @brief       The interface function to De Initialize sensor..
 *  @details     This function made sensor in a power safe state and de initialize its handle.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @constraints This can be called only after FXPQ3115_I2C_Initialize() has been called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXPQ3115_I2C_DeInit() returns the status.
 */
int32_t FXPQ3115_I2C_DeInit(fxpq3115_i2c_sensorhandle_t *pSensorHandle);

#endif // FXPQ3115_FI_H_
