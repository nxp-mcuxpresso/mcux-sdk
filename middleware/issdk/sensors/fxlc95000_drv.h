/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxlc95000_drv.h
 * @brief The fxlc95000_drv.h file describes the FXLC95000L driver interface and structures.
 */

#ifndef MMA9553_DRV_H_
#define MMA9553_DRV_H_

/* Standard C Includes */
#include <stdint.h>

/* ISSDK Includes */
#include "fxlc95000.h"
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
} fxlc95000_spi_sensorhandle_t;

/*!
 * @brief This defines the sensor specific information for I2C.
 */
typedef struct
{
    registerDeviceInfo_t deviceInfo; /*!< I2C device context. */
    ARM_DRIVER_I2C *pCommDrv;        /*!< Pointer to the i2c driver. */
    bool isInitialized;              /*!< whether sensor is intialized or not.*/
    uint16_t slaveAddress;           /*!< slave address.*/
} fxlc95000_i2c_sensorhandle_t;

/*! @brief This structure defines the fxlc95000 pedometer data buffer. */
typedef struct
{
    uint32_t timestamp; /*! The time, this sample was recorded.  */
    int16_t accel[3];   /*! The raw accel data */
} fxlc95000_acceldata_t;

/*! @def    FXLC95000_COCO_ERROR_MASK
 *  @brief  The Error Bit Mask in COCO Byte. */
#define FXLC95000_COCO_ERROR_MASK (0x7F)

/*! @def    FXLC95000_SPI_MAX_MSG_SIZE
 *  @brief  The MAX size of SPI message. */
#define FXLC95000_SPI_MAX_MSG_SIZE (64)

/*! @def    FXLC95000_SPI_CMD_LEN
 *  @brief  The size of the Sensor specific SPI Header. */
#define FXLC95000_SPI_CMD_LEN (1)

/*! @def    FXLC95000_SS_ACTIVE_VALUE
 *  @brief  Is the Slave Select Pin Active Low or High. */
#define FXLC95000_SS_ACTIVE_VALUE SPI_SS_ACTIVE_LOW

/*! @def    FXLC95000_ROM_CI_WRITE_MIN_LEN
 *  @brief  The MIN Length of ROM CI_WRITE Data. */
#define FXLC95000_ROM_CI_WRITE_MIN_LEN 4

/*! @def    FXLC95000_ROM_CI_WRITE_MAX_LEN
 *  @brief  The MAX Length of ROM CI_WRITE Data. */
#define FXLC95000_ROM_CI_WRITE_MAX_LEN 24

/*! @def    FXLC95000_ROM_CI_READ_WRITE_MAX_LEN
 *  @brief  The MAX Length of ROM CI_READ_WRITE Command. */
#define FXLC95000_ROM_CI_READ_WRITE_MAX_LEN 32

/*! @def    FXLC95000_ROM_CI_READ_WRITE_HDR_LEN
 *  @brief  The Length of ROM CI_READ_WRITE Command Header. */
#define FXLC95000_ROM_CI_READ_WRITE_HDR_LEN 6

/*! @def    FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN
 *  @brief  The Length of Address field in ROM CI_READ_WRITE Command Header. */
#define FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN 2

/*! @def    FXLC95000_FLASH_PAYLOAD_ADDR_LEN
 *  @brief  The Length of Address field in FLASH Payload form Host. */
#define FXLC95000_FLASH_PAYLOAD_ADDR_LEN 4

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*! @brief       The interface function to check if the sensor is in ROM CI Mode.
 *  @details     This function checks the Response of Version Info command to determine if Sensor is in ROM CI Mode.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @constraints This can be called any time.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_I2C_CheckRomMode() returns the status.
 */
int32_t FXLC95000_I2C_CheckRomMode(ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress);

/*! @brief       The interface function to write ROM CI Commands.
 *  @details     This function Writes ROM CI commands over I2C to the Sensor.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @param[in]   pCommandList  pointer to the command read list.
 *  @constraints This can be called only if Sensor is in ROM CI Mode.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_I2C_FlashCommands() returns the status.
 */
int32_t FXLC95000_I2C_FlashCommands(ARM_DRIVER_I2C *pBus,
                                    uint8_t index,
                                    uint16_t sAddress,
                                    const registercommandlist_t *pCommandList);

/*! @brief       The interface function to write ROM CI Data Payload.
 *  @details     This function Writes ROM CI Payload Bytes by creating formatted Commands and writing over I2C to the
 * Sensor.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @param[in]   pFlashBytes    pointer to payload bytes of flash data.
 *  @param[in]   numBytes       the number of bytes of flash data to be written.
 *  @constraints This can be called only if Sensor is in ROM CI Mode.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_I2C_FlashPayload() returns the status.
 */
int32_t FXLC95000_I2C_FlashPayload(
    ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t *pFlashBytes, uint8_t numBytes);

/*! @brief       The interface function to initialize the sensor.
 *  @details     This function initialize the sensor and sensor handle.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pBus           pointer to the CMSIS API compatible I2C bus object.
 *  @param[in]   index          the I2C device number.
 *  @param[in]   sAddress       slave address of the device on the bus.
 *  @param[in]   buildId        FXLC95000 firmware buid number.
 *  @constraints This should be the first API to be called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_I2C_Initialize() returns the status .
 */
int32_t FXLC95000_I2C_Initialize(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
                                 ARM_DRIVER_I2C *pBus,
                                 uint8_t index,
                                 uint16_t sAddress,
                                 uint16_t buildId);

/*! @brief      :  The interface function to set the I2C Idle Task.
 *  @param[in]  :  fxlc95000_i2c_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on I2C Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after FXLC95000_I2C_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void FXLC95000_I2C_SetIdleTask(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
                               registeridlefunction_t idleTask,
                               void *userParam);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle  handle to the sensor.
 *  @param[in]   pCommandList  pointer to the command read list.
 *  @param[in]   pReadList      pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer        buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *                              command read in the list.
 *  @constraints This can be called any number of times only after FXLC95000_I2C_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_I2C_CommandResponse() returns the status .
 */
int32_t FXLC95000_I2C_CommandResponse(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
                                      const registercommandlist_t *pCommandList,
                                      const registerreadlist_t *pReadList,
                                      uint8_t *pBuffer);

/*! @brief       The interface function to initialize the sensor.
 *  @details     This function initializes the sensor and sensor handle.
 *  @param[in]   pSensorHandle handle to the sensor.
 *  @param[in]   pBus          pointer to the CMSIS API compatible SPI bus object.
 *  @param[in]   index         the I2C device number.
 *  @param[in]   pSlaveSelect  slave select hndle of the device on the bus.
 *  @param[in]   pReset        reset handle of the device on the bus.
 *  @param[in]   buildId       FXLC95000 firmware buid number.
 *  @constraints This should be the first API to be called.
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_SPI_Initialize() returns the status .
 */
int32_t FXLC95000_SPI_Initialize(fxlc95000_spi_sensorhandle_t *pSensorHandle,
                                 ARM_DRIVER_SPI *pBus,
                                 uint8_t index,
                                 void *pSpiSelect,
                                 void *pSlaveSelect,
                                 void *pReset,
                                 uint16_t buildId);

/*! @brief      :  The interface function to set the SPI Idle Task.
 *  @param[in]  :  fxlc95000_spi_sensorhandle_t *pSensorHandle, handle to the sensor handle.
 *  @param[in]  :  registeridlefunction_t idleTask, function pointer to the function to execute on SPI Idle Time.
 *  @param[in]  :  void *userParam, the pointer to the user idle ftask parameters.
 *  @return        void.
 *  @constraints   This can be called any number of times only after FXLC95000_SPI_Initialize().
 *                 Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant    No
 */
void FXLC95000_SPI_SetIdleTask(fxlc95000_spi_sensorhandle_t *pSensorHandle,
                               registeridlefunction_t idleTask,
                               void *userParam);

/*! @brief       The interface function to read the sensor data.
 *  @details     This function read the sensor data out from the device and returns raw data in a byte stream.
 *  @param[in]   pSensorHandle handle to the sensor.
 *  @param[in]   pCommandList  pointer to the command read list.
 *  @param[in]   pReadList     pointer to the list of device registers and values to read.
 *  @param[out]  pBuffer       buffer which holds raw sensor data.This buffer may be back to back databuffer based
 *               command read in the list.
 *  @constraints This can be called any number of times only after FXLC95000_SPI_Initialize().
 *               Application has to ensure that previous instances of these APIs have exited before invocation.
 *  @reeentrant  No
 *  @return      ::FXLC95000_SPI_CommandResponse() returns the status .
 */
int32_t FXLC95000_SPI_CommandResponse(fxlc95000_spi_sensorhandle_t *pSensorHandle,
                                      const registercommandlist_t *pCommandList,
                                      const registerreadlist_t *pReadList,
                                      uint8_t *pBuffer);

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
void FXLC95000_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size);

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
void FXLC95000_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer);

#endif // FXLC95000_DRV_H_
