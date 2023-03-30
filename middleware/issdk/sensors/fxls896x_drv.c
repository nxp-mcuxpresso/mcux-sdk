/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls896x_drv.c
 * @brief The fxls896x_drv.c file implements the FXLS8964/67 sensor driver interfaces.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "gpio_driver.h"
#include "fxls896x_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
uint8_t fxls896x_spiRead_CmdBuffer[FXLS896x_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxls896x_spiRead_DataBuffer[FXLS896x_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxls896x_spiWrite_CmdDataBuffer[FXLS896x_SPI_MAX_MSG_SIZE] = {0};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void FXLS896x_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxls896x_spiRead_CmdBuffer;
    uint8_t *pRBuff = fxls896x_spiRead_DataBuffer;

    /* Formatting for Read command of FXLS896x SENSOR. */
    *(pWBuff) = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = 0x00;

    /* Create the slave read command. */
    pSlaveCmd->size = size + FXLS896x_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void FXLS896x_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxls896x_spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = fxls896x_spiWrite_CmdDataBuffer + size + FXLS896x_SPI_CMD_LEN;

    /* Formatting for Write command of FXLS896x SENSOR. */
    *(pWBuff) = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = 0x00;

    /* Copy the slave write command */
    memcpy(pWBuff + FXLS896x_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + FXLS896x_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

int32_t FXLS896x_SPI_Initialize(
    fxls896x_spi_sensorhandle_t *pSensorHandle, ARM_DRIVER_SPI *pBus, uint8_t index, void *pSlaveSelect, uint8_t *whoami)
{
    int32_t status;
    uint8_t reg;
    GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL) || (pSlaveSelect == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveParams.pReadPreprocessFN = FXLS896x_SPI_ReadPreprocess;
    pSensorHandle->slaveParams.pWritePreprocessFN = FXLS896x_SPI_WritePreprocess;
    pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
    pSensorHandle->slaveParams.spiCmdLen = FXLS896x_SPI_CMD_LEN;
    pSensorHandle->slaveParams.ssActiveValue = FXLS896x_SS_ACTIVE_VALUE;

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Initialize the Slave Select Pin. */
    pGPIODriver->pin_init(pSlaveSelect, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    if (pSensorHandle->slaveParams.ssActiveValue == SPI_SS_ACTIVE_LOW)
    {
        pGPIODriver->set_pin(pSlaveSelect);
    }
    else
    {
        pGPIODriver->clr_pin(pSlaveSelect);
    }

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                               FXLS896x_WHO_AM_I, 1, &reg);
    //if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
	(*whoami) = reg;
    if (ARM_DRIVER_OK != status)
    {
    	if ((FXLS8962_WHOAMI_VALUE != reg) || (FXLS8964_WHOAMI_VALUE != reg) || (FXLS8967_WHOAMI_VALUE != reg) || (FXLS8968_WHOAMI_VALUE != reg) || (FXLS8974_WHOAMI_VALUE != reg) || (FXLS8971_WHOAMI_VALUE != reg) || (FXLS8961_WHOAMI_VALUE != reg))
    	{
            pSensorHandle->isInitialized = false;
    		return SENSOR_ERROR_BAD_ADDRESS;
    	}
		pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }
    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void FXLS896x_SPI_SetIdleTask(fxls896x_spi_sensorhandle_t *pSensorHandle,
                              registeridlefunction_t idleTask,
                              void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t FXLS896x_SPI_Configure(fxls896x_spi_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
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
    status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_ACTIVE_STANDBY,
                                FXLS896x_SENS_CONFIG1_ACTIVE_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /*! Apply the Sensor Configuration based on the Register Write List */
    status = Sensor_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                              pRegWriteList);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /*! Put the device into active mode and ready for reading data.*/
    status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_ACTIVE_ACTIVE,
                                FXLS896x_SENS_CONFIG1_ACTIVE_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLS896x_SPI_ReadData(fxls896x_spi_sensorhandle_t *pSensorHandle,
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
    status = Sensor_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                             pReadList, pBuffer);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_READ;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLS896x_SPI_Deinit(fxls896x_spi_sensorhandle_t *pSensorHandle)
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
    status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_RST_RST, FXLS896x_SENS_CONFIG1_RST_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }
    else
    {
        /*! De-initialize sensor handle. */
        pSensorHandle->isInitialized = false;
    }

    /* Wait for MAX of TBOOT ms after soft reset command,
     * to allow enough time for FXLS896xAF to complete its internal boot sequence and be ready for communication. */
    BOARD_DELAY_ms(FXLS896x_TBOOT_MAX);

    return SENSOR_ERROR_NONE;
}

int32_t FXLS896x_I2C_Initialize(
    fxls896x_i2c_sensorhandle_t *pSensorHandle, ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t *whoami)
{
    int32_t status;
    uint8_t reg = 0;

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, FXLS896x_WHO_AM_I, 1, &reg);
    //if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
	(*whoami) = reg;
    if (ARM_DRIVER_OK != status)
    {
    	if ((FXLS8962_WHOAMI_VALUE != reg) || (FXLS8964_WHOAMI_VALUE != reg) || (FXLS8967_WHOAMI_VALUE != reg) || (FXLS8968_WHOAMI_VALUE != reg) || (FXLS8974_WHOAMI_VALUE != reg) || (FXLS8971_WHOAMI_VALUE != reg) || (FXLS8961_WHOAMI_VALUE != reg))
    	{
    		pSensorHandle->isInitialized = false;
    		return SENSOR_ERROR_BAD_ADDRESS;
    	}
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveAddress = sAddress;
    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void FXLS896x_I2C_SetIdleTask(fxls896x_i2c_sensorhandle_t *pSensorHandle,
                              registeridlefunction_t idleTask,
                              void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t FXLS896x_I2C_Configure(fxls896x_i2c_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
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
                                FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_ACTIVE_STANDBY,
                                FXLS896x_SENS_CONFIG1_ACTIVE_MASK, false);
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
                                FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_ACTIVE_ACTIVE,
                                FXLS896x_SENS_CONFIG1_ACTIVE_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLS896x_I2C_ReadData(fxls896x_i2c_sensorhandle_t *pSensorHandle,
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

int32_t FXLS896x_I2C_DeInit(fxls896x_i2c_sensorhandle_t *pSensorHandle)
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
    status =
        Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                           FXLS896x_SENS_CONFIG1, FXLS896x_SENS_CONFIG1_RST_RST, FXLS896x_SENS_CONFIG1_RST_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }
    else
    {
        /*! De-initialize sensor handle. */
        pSensorHandle->isInitialized = false;
    }

    /* Wait for MAX of TBOOT ms after soft reset command,
     * to allow enough time for FXLS896xAF to complete its internal boot sequence and be ready for communication. */
    BOARD_DELAY_ms(FXLS896x_TBOOT_MAX);

    return SENSOR_ERROR_NONE;
}
