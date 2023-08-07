/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file nmh1000_drv.h
 * @brief The nmh1000_drv.h file describes the NMH1000 driver interface and structures.
 */

#ifndef NMH1000_DRV_H_
#define NMH1000_DRV_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "nmh1000.h"
#include "sensor_io_i2c.h"
#include "register_io_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief This defines the sensor specific information for I2C.
 */
typedef struct
{
    registerDeviceInfo_t deviceInfo; /*!< I2C device context. */
    ARM_DRIVER_I2C *pCommDrv;        /*!< Pointer to the i2c driver. */
    bool isInitialized;              /*!< whether sensor is intialized or not.*/
    uint16_t slaveAddress;           /*!< slave address.*/
} nmh1000_i2c_sensorhandle_t;

/*! @brief This structure defines the nmh1000 data buffer.*/
typedef struct
{
    uint32_t timestamp; /*!< Time stamp value in micro-seconds. */
    uint8_t magData;   /*!< Sensor Mag Raw Data. */
} nmh1000_magData_t;


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
 *  @return      ::NMH1000_I2C_Initialize() returns the status.
 */
int32_t NMH1000_I2C_Initialize(
    nmh1000_i2c_sensorhandle_t *pSensorHandle, ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t whoAmi);

/*! @brief      :  The interface function to set the I2C Idle Task.
 *  @param[in]  :  nmh1000_i2c_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on I2C Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after NMH1000_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void NMH1000_I2C_SetIdleTask(nmh1000_i2c_sensorhandle_t *pSensorHandle, registeridlefunction_t idleTask, void *userParam);

/*! @brief       The interface function to configure he sensor.
 *  @details     This function configure the sensor with requested ODR, Range and registers in the regsiter pair array.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @param[in]   pRegWriteList      pointer to the register list.
 *  @constraints This can be called any number of times only after NMH1000_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::NMH1000_I2C_Configure() returns the status.
 */
int32_t NMH1000_I2C_Configure(nmh1000_i2c_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pReadList      pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer        buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *                              command read in the list.
 *  @constraints This can be called only after NMH1000_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::NMH1000_I2C_ReadData() returns the status .
 */
int32_t NMH1000_I2C_ReadData(nmh1000_i2c_sensorhandle_t *pSensorHandle,
                            const registerreadlist_t *pReadList,
                            uint8_t *pBuffer);

/*! @brief       The interface function to De Initialize sensor..
 *  @details     This function made sensor in a power safe state and de initialize its handle.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @constraints This can be called only after NMH1000_I2C_Initialize() has been called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::NMH1000_I2C_DeInit() returns the status.
 */
int32_t NMH1000_I2C_DeInit(nmh1000_i2c_sensorhandle_t *pSensorHandle);

#endif // NMH1000_DRV_H_
