/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  diff_p_drv.c
 * @brief The diff_p_drv.c file implements the diff_p functional interface.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "gpio_driver.h"
#include "diff_p_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
uint8_t diff_p_spiRead_CmdBuffer[DIFF_P_SPI_MAX_MSG_SIZE] = {0};
uint8_t diff_p_spiRead_DataBuffer[DIFF_P_SPI_MAX_MSG_SIZE] = {0};
uint8_t diff_p_spiWrite_CmdDataBuffer[DIFF_P_SPI_MAX_MSG_SIZE] = {0};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void DIFF_P_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = diff_p_spiRead_CmdBuffer;
    uint8_t *pRBuff = diff_p_spiRead_DataBuffer;

    /* Formatting for Read command of DIFF-P SENSOR. */
    *pWBuff = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */

    // Create the slave read command.
    pSlaveCmd->size = size + DIFF_P_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void DIFF_P_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = diff_p_spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = diff_p_spiWrite_CmdDataBuffer + size + DIFF_P_SPI_CMD_LEN;

    /* Formatting for Write command of DIFF-P SENSOR. */
    *pWBuff = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */

    /* Copy the slave write command */
    memcpy(pWBuff + DIFF_P_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + DIFF_P_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

int32_t DIFF_P_SPI_Initialize(
    diff_p_spi_sensorhandle_t *pSensorHandle, ARM_DRIVER_SPI *pBus, uint8_t index, void *pSlaveSelect, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg, retries = 1;
    GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL) || (pSlaveSelect == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveParams.pReadPreprocessFN = DIFF_P_SPI_ReadPreprocess;
    pSensorHandle->slaveParams.pWritePreprocessFN = DIFF_P_SPI_WritePreprocess;
    pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
    pSensorHandle->slaveParams.spiCmdLen = DIFF_P_SPI_CMD_LEN;
    pSensorHandle->slaveParams.ssActiveValue = DIFF_P_SS_ACTIVE_VALUE;

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
                               DIFF_P_WHO_AM_I, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    pSensorHandle->isInitialized = true;

    do
    { /*! Put the device into standby mode so that we can run calibration can be done. */
        status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                    DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_STANDBY, DIFF_P_CTRL_REG1_SBYB_MASK);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }

        /*! Run Calibration algorithm. */
        status = Register_SPI_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                    DIFF_P_CTRL_REG2, DIFF_P_CTRL_REG2_CTRL_AC_CALRUN, DIFF_P_CTRL_REG2_CTRL_AC_MASK);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }
        BOARD_DELAY_ms(1); /* Wait for calibration to finish... */
        do
        { /*!  Wait for calibration to finish.*/
            status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                       DIFF_P_CTRL_REG2, 1, &reg);
            if (ARM_DRIVER_OK != status)
            {
                return SENSOR_ERROR_INIT;
            }
        } while (reg & DIFF_P_CTRL_REG2_CTRL_AC_MASK);

        /* Check Calibration Result. */
        status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   DIFF_P_STATUS, 1, &reg);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }
        if ((reg & DIFF_P_STATUS_STAT_EP_MASK) == 0)
        {
            break;
        }
        BOARD_DELAY_ms(10); /* Wait and then retry calibration. */
    } while (retries--);

    return SENSOR_ERROR_NONE;
}

void DIFF_P_SPI_SetIdleTask(diff_p_spi_sensorhandle_t *pSensorHandle, registeridlefunction_t idleTask, void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t DIFF_P_SPI_Configure(diff_p_spi_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_STANDBY, DIFF_P_CTRL_REG1_SBYB_MASK);
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_ACTIVE, DIFF_P_CTRL_REG1_SBYB_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t DIFF_P_SPI_ReadData(diff_p_spi_sensorhandle_t *pSensorHandle,
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

int32_t DIFF_P_SPI_DeInit(diff_p_spi_sensorhandle_t *pSensorHandle)
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_RST_RESET, DIFF_P_CTRL_REG1_RST_MASK);
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

int32_t DIFF_P_I2C_Initialize(
    diff_p_i2c_sensorhandle_t *pSensorHandle, ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg, retries = 1;

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, DIFF_P_WHO_AM_I, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveAddress = sAddress;
    pSensorHandle->isInitialized = true;

    do
    { /*! Put the device into standby mode so that we can run calibration can be done. */
        status = Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                    DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_STANDBY, DIFF_P_CTRL_REG1_SBYB_MASK, false);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }

        /*! Run Calibration algorithm. */
        status =
            Register_I2C_Write(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                               DIFF_P_CTRL_REG2, DIFF_P_CTRL_REG2_CTRL_AC_CALRUN, DIFF_P_CTRL_REG2_CTRL_AC_MASK, false);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }
        BOARD_DELAY_ms(1); /* Wait for calibration to finish... */
        do
        { /*!  Wait for calibration to finish.*/
            status = Register_I2C_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                       DIFF_P_CTRL_REG2, 1, &reg);
            if (ARM_DRIVER_OK != status)
            {
                return SENSOR_ERROR_INIT;
            }
        } while (reg & DIFF_P_CTRL_REG2_CTRL_AC_MASK);

        /* Check Calibration Result. */
        status = Register_I2C_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   DIFF_P_STATUS, 1, &reg);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_INIT;
        }
        if ((reg & DIFF_P_STATUS_STAT_EP_MASK) == 0)
        {
            break;
        }
        BOARD_DELAY_ms(10); /* Wait and then retry calibration. */
    } while (retries--);

    return SENSOR_ERROR_NONE;
}

void DIFF_P_I2C_SetIdleTask(diff_p_i2c_sensorhandle_t *pSensorHandle, registeridlefunction_t idleTask, void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t DIFF_P_I2C_Configure(diff_p_i2c_sensorhandle_t *pSensorHandle, const registerwritelist_t *pRegWriteList)
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_STANDBY, DIFF_P_CTRL_REG1_SBYB_MASK, false);
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_SBYB_ACTIVE, DIFF_P_CTRL_REG1_SBYB_MASK, false);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t DIFF_P_I2C_ReadData(diff_p_i2c_sensorhandle_t *pSensorHandle,
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

int32_t DIFF_P_I2C_DeInit(diff_p_i2c_sensorhandle_t *pSensorHandle)
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
                                DIFF_P_CTRL_REG1, DIFF_P_CTRL_REG1_RST_RESET, DIFF_P_CTRL_REG1_RST_MASK, false);
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
