/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma8491q_drv.h
 * @brief The mma8491q_drv.h file describes the MMA8491Q driver interface and structures.
 */

#ifndef MMA8491Q_FI_H_
#define MMA8491Q_FI_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "mma8491q.h"
#include "sensor_io_i2c.h"
#include "register_io_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief This defines the function pointers and sensor specific information. */
typedef struct
{
    registerDeviceInfo_t deviceInfo; /*!< I2C device context. */
    ARM_DRIVER_I2C *pCommDrv;        /*!< Pointer to the i2c driver. */
    bool isInitialized;              /*!< Init status.*/
    uint16_t slaveAddress;           /*!< slave address.*/
} mma8491q_i2c_sensorhandle_t;

/*! @brief This structure defines the mma8491q data buffer.*/
typedef struct
{
    uint32_t timestamp; /*!< Time stamp value in micro-seconds. */
    int16_t accel[3];   /*! Sensor Acceleration output: signed 14-bits. */
    uint8_t tilt[3];    /*! 3-Axis Tilt output. */
} mma8491q_acceldata_t;

/*! @brief This structure stores the Sensor's context parameters. */
typedef struct
{
    uint64_t adjustedODR;       /*! The actual ODR calculated considering T_On and T_Rst. */
    void *pGpioEN;              /*! The GPIO handle for the EN Pin. */
    uint8_t sensorMode;         /*! The current operating Mode of the Sensor. */
    volatile bool inTransition; /*! The Flag indicating Sensor is undergoing Transition to another mode as a result of
                                   EN pin toggling. */
} mma8491q_context_t;

/*! @brief This enum lists the MMA8491Q operating Modes. */
enum
{
    SENSOR_MODE_SHUTDOWN,
    SENSOR_MODE_ACTIVE,
    SENSOR_MODE_STANDBY,
};

#define MMA8491Q_DATA_SIZE (6) /* 2 byte X,Y,Z Axis Data each. */

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
 *  @return      ::MMA8491Q_I2C_Initialize() returns the status.
 */
int32_t MMA8491Q_I2C_Initialize(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                                ARM_DRIVER_I2C *pBus,
                                uint8_t index,
                                uint16_t sAddress);

/*! @brief      :  The interface function to set the I2C Idle Task.
 *  @param[in]  :  mma8491q_i2c_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on I2C Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after MMA8491Q_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void MMA8491Q_I2C_SetIdleTask(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                              registeridlefunction_t idleTask,
                              void *userParam);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pReadList      pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer        buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *                              command read in the list.
 *  @constraints This can be called any number of times only after MMA8491Q_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA8491Q_I2C_ReadData() returns the status .
 */

int32_t MMA8491Q_I2C_ReadData(mma8491q_i2c_sensorhandle_t *pSensorHandle,
                              const registerreadlist_t *pReadList,
                              uint8_t *pBuffer);

#endif // MMA8491Q_FI_H_
