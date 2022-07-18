/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8471q_drv.c
 * @brief The fxls8471q_drv.c file implements the FXLS8471Q sensor driver interfaces.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "gpio_driver.h"
#include "fxls8471q_drv.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
uint8_t fxls8471q_spiRead_CmdBuffer[FXLS8471Q_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxls8471q_spiRead_DataBuffer[FXLS8471Q_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxls8471q_spiWrite_CmdDataBuffer[FXLS8471Q_SPI_MAX_MSG_SIZE] = {0};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void FXLS8471Q_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxls8471q_spiRead_CmdBuffer;
    uint8_t *pRBuff = fxls8471q_spiRead_DataBuffer;

    /* Formatting for Read command of FXLS8471Q SENSOR. */
    *(pWBuff) = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = offset & 0x80;

    // Create the slave read command.
    pSlaveCmd->size = size + FXLS8471Q_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void FXLS8471Q_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxls8471q_spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = fxls8471q_spiWrite_CmdDataBuffer + size + FXLS8471Q_SPI_CMD_LEN;

    /* Formatting for Write command of FXLS8471Q SENSOR. */
    *(pWBuff) = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = offset & 0x80;

    /* Copy the slave write command */
    memcpy(pWBuff + FXLS8471Q_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + FXLS8471Q_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

int32_t FXLS8471Q_SPI_Initialize(fxls8471q_spi_sensorhandle_t *pSensorHandle,
                                 ARM_DRIVER_SPI *pBus,
                                 uint8_t index,
                                 void *pSlaveSelect,
                                 uint8_t whoAmi)
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
    pSensorHandle->slaveParams.pReadPreprocessFN = FXLS8471Q_SPI_ReadPreprocess;
    pSensorHandle->slaveParams.pWritePreprocessFN = FXLS8471Q_SPI_WritePreprocess;
    pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
    pSensorHandle->slaveParams.spiCmdLen = FXLS8471Q_SPI_CMD_LEN;
    pSensorHandle->slaveParams.ssActiveValue = FXLS8471Q_SS_ACTIVE_VALUE;

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
                               FXLS8471Q_WHO_AM_I, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void FXLS8471Q_SPI_SetIdleTask(fxls8471q_spi_sensorhandle_t *pSensorHandle,
                               registeridlefunction_t idleTask,
                               void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t FXLS8471Q_SPI_Configure(fxls8471q_spi_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
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
                                FXLS8471Q_CTRL_REG1, FXLS8471Q_CTRL_REG1_MODE_STANDBY, FXLS8471Q_CTRL_REG1_MODE_MASK);
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
                                FXLS8471Q_CTRL_REG1, FXLS8471Q_CTRL_REG1_MODE_ACTIVE, FXLS8471Q_CTRL_REG1_MODE_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLS8471Q_SPI_ReadData(fxls8471q_spi_sensorhandle_t *pSensorHandle,
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

int32_t FXLS8471Q_SPI_Deinit(fxls8471q_spi_sensorhandle_t *pSensorHandle)
{
    if (pSensorHandle == NULL)
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before triggering sensor reset.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /* Note:
     * There is a Errata described in the data sheet for soft reset with SPI,
     * which says device specific paratameters do not get updated correctly from NVM,
     * causing inaccurate data output once the soft-reset command issued in SPI mode.
     * The work around is hard reset, which cannot be handled in sensor driver software.
     * So software reset command wont be issued until this issue is fixed in the silicon.
     */

    /*! De-initialize sensor handle. */
    pSensorHandle->isInitialized = false;

    return SENSOR_ERROR_NONE;
}
