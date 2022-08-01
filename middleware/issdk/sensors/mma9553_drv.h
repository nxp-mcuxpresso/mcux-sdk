/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma9553_drv.h
 * @brief The mma9553_drv.h file describes the MMA9553L driver interface and structures.
 */

#ifndef MMA9553_DRV_H_
#define MMA9553_DRV_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "mma9553.h"
#include "sensor_io_i2c.h"
#include "sensor_io_spi.h"
#include "register_io_i2c.h"
#include "register_io_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief This defines the sensor specific information for SPI.
 */
typedef struct
{
    registerDeviceInfo_t deviceInfo;      /*!< SPI device context. */
    ARM_DRIVER_SPI *pCommDrv;             /*!< Pointer to the spi driver. */
    bool isInitialized;                   /*!< Whether sensor is intialized or not.*/
    spiSlaveSpecificParams_t slaveParams; /*!< Slave Specific Params.*/
} mma9553_spi_sensorhandle_t;

/*!
 * @brief This defines the sensor specific information for I2C.
 */
typedef struct
{
    registerDeviceInfo_t deviceInfo; /*!< I2C device context. */
    ARM_DRIVER_I2C *pCommDrv;        /*!< Pointer to the i2c driver. */
    bool isInitialized;              /*!< whether sensor is intialized or not.*/
    uint16_t slaveAddress;           /*!< slave address.*/
} mma9553_i2c_sensorhandle_t;

/*! @brief This structure defines the mma9553 pedometer data buffer. */
typedef struct
{
    uint32_t timestamp; /*! The time, this sample was recorded.  */
    int16_t accel[3];   /*! The raw accel data */
} mma9553_acceldata_t;

/*! @brief This structure defines the Size of response for pedometer data read command. */
typedef struct
{
    uint8_t responseHeader[MMA9553_HDR_SIZE]; /*! The response header for the read command. */
    uint16_t statusRegister;                  /*! Status register. */
    uint16_t stepCount;                       /*! Step Counter. */
    uint16_t distance;                        /*! Distance covered. */
    uint16_t speed;                           /*! Walking Speed. */
    uint16_t calories;                        /*! Calories burnt. */
    uint16_t sleepCount;                      /*! Sleep Counter. */
} mma9553_pedometerdata_t;

/*! @def    MMA9553_COCO_ERROR_MASK
 *  @brief  The Error Bit Mask in COCO Byte. */
#define MMA9553_COCO_ERROR_MASK (0x7F)

/*! @def    MMA9553_SPI_MAX_MSG_SIZE
 *  @brief  The MAX size of SPI message. */
#define MMA9553_SPI_MAX_MSG_SIZE (64)

/*! @def    MMA9553_SPI_CMD_LEN
 *  @brief  The size of the Sensor specific SPI Header. */
#define MMA9553_SPI_CMD_LEN (1)

/*! @def    MMA9553_SS_ACTIVE_VALUE
 *  @brief  Is the Slave Select Pin Active Low or High. */
#define MMA9553_SS_ACTIVE_VALUE SPI_SS_ACTIVE_LOW

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*! @brief       The interface function to initialize the sensor.
 *  @details     This function initialize the sensor and sensor handle.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @constraints This should be the first API to be called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_I2C_Initialize() returns the status .
 */
int32_t MMA9553_I2C_Initialize(mma9553_i2c_sensorhandle_t *pSensorHandle,
                               ARM_DRIVER_I2C *pBus,
                               uint8_t index,
                               uint16_t sAddress);

/*! @brief      :  The interface function to set the I2C Idle Task.
 *  @param[in]  :  mma9553_i2c_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on I2C Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after MMA9553_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void MMA9553_I2C_SetIdleTask(mma9553_i2c_sensorhandle_t *pSensorHandle,
                             registeridlefunction_t idleTask,
                             void *userParam);

/*! @brief       The interface function to configure he sensor.
 *  @details     This function configure the sensor with requested ODR, Range and registers in the regsiter pair array.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @param[in]   pCommandList      pointer to the command write list.
 *  @constraints This can be called any number of times only after MMA9553_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_I2C_Configure() returns the status.
 */
int32_t MMA9553_I2C_Configure(mma9553_i2c_sensorhandle_t *pSensorHandle, const registercommandlist_t *pCommandList);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pCommandList  pointer to the command read list.
 *  @param[in]   pReadList      pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer        buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *                              command read in the list.
 *  @constraints This can be called any number of times only after MMA9553_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_I2C_CommandResponse() returns the status .
 */
int32_t MMA9553_I2C_CommandResponse(mma9553_i2c_sensorhandle_t *pSensorHandle,
                                    const registercommandlist_t *pCommandList,
                                    const registerreadlist_t *pReadList,
                                    uint8_t *pBuffer);

/*! @brief       The interface function to De Initialize sensor..
 *  @details     This function made sensor in a power safe state and de initialize its handle.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @constraints This can be called only after MMA9553_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_I2C_DeInit() returns the status .
 */
int32_t MMA9553_I2C_DeInit(mma9553_i2c_sensorhandle_t *pSensorHandle);

/*! @brief       The interface function to initialize the sensor.
 *  @details     This function initializes the sensor and sensor handle.
 *  @param[in]   pSensorHandle handle to the sensor.
 *  @param[in]   pBus          pointer to the CMSIS API compatible SPI bus object.
 *  @param[in]   index         the I2C device number.
 *  @param[in]   pSlaveSelect  slave select hndle of the device on the bus.
 *  @param[in]   pReset        reset handle of the device on the bus.
 *  @constraints This should be the first API to be called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_SPI_Initialize() returns the status .
 */
int32_t MMA9553_SPI_Initialize(
    mma9553_spi_sensorhandle_t *pSensorHandle, ARM_DRIVER_SPI *pBus, uint8_t index, void *pSlaveSelect, void *pReset);

/*! @brief      :  The interface function to set the SPI Idle Task.
 *  @param[in]  :  mma9553_spi_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on SPI Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after MMA9553_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void MMA9553_SPI_SetIdleTask(mma9553_spi_sensorhandle_t *pSensorHandle,
                             registeridlefunction_t idleTask,
                             void *userParam);

/*! @brief       The interface function to configure he sensor.
 *  @details     This function configure the sensor with requested ODR, Range and registers in the regsiter pair array.
 *  @param[in]   pSensorHandle handle to the sensor.
 *  @param[in]   pCommandList  pointer to the command list.
 *  @constraints This can be called any number of times only after FXAS21002_SPI_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_SPI_Configure() returns the status .
 */
int32_t MMA9553_SPI_Configure(mma9553_spi_sensorhandle_t *pSensorHandle, const registercommandlist_t *pCommandList);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle handle to the sensor.
 *  @param[in]   pCommandList  pointer to the command read list.
 *  @param[in]   pReadList     pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer       buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *               command read in the list.
 *  @constraints This can be called any number of times only after MMA9553_SPI_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_SPI_CommandResponse() returns the status .
 */
int32_t MMA9553_SPI_CommandResponse(mma9553_spi_sensorhandle_t *pSensorHandle,
                                    const registercommandlist_t *pCommandList,
                                    const registerreadlist_t *pReadList,
                                    uint8_t *pBuffer);

/*! @brief       The interface function to De Initialize sensor..
 *  @details     This function made sensor in a power safe state and de initialize its handle.
 *  @param[in]   pSensorHandle      handle to the sensor.
 *  @constraints This can be called only after after MMA9553_SPI_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::MMA9553_SPI_DeInit() returns the status .
 */
int32_t MMA9553_SPI_DeInit(mma9553_spi_sensorhandle_t *pSensorHandle);

/*! @brief       The SPI Read Pre-Process function to generate Sensor specific SPI Message Header.
 *  @details     This function prepares the SPI Read Command Header with register address and
 *               R/W bit encoded as the Sensor.
 *  @param[out]  pCmdOut  handle to the output buffer.
 *  @param[in]   offset   the address of the register to start reading from.
 *  @param[in]   size     number of bytes to read.
 *  @constraints None
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      :: None.
 */
void MMA9553_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size);

/*! @brief       The SPI Write Pre-Process function to generate Sensor specific SPI Message Header.
 *  @details     This function prepares the SPI Write Command Header with register address and
 *               R/W bit encoded as the Sensor.
 *  @param[out]  pCmdOut  handle to the output buffer.
 *  @param[in]   offset   the address of the register to start writing from.
 *  @param[in]   size     number of bytes to write.
 *  @constraints None
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      :: None.
 */
void MMA9553_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer);

#endif // MMA9553_DRV_H_
