/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  mma9553_drv.c
 * @brief The mma9553_drv.c file implements the MMA9553L sensor driver interface.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "gpio_driver.h"
#include "mma9553_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
uint8_t mma9553_spiRead_CmdBuffer[MMA9553_SPI_MAX_MSG_SIZE] = {0};
uint8_t mma9553_spiRead_DataBuffer[MMA9553_SPI_MAX_MSG_SIZE] = {0};
uint8_t mma9553_spiWrite_CmdDataBuffer[MMA9553_SPI_MAX_MSG_SIZE] = {0};

/*! @brief Suspend the Pedometer Application. */
static uint8_t SuspendPedometer[] = {0x17, 0x20, 0x05, 0x01, 0x20};

/*! @brief Suspend the AFE Application. */
static uint8_t SuspendAFE[] = {0x17, 0x20, 0x07, 0x01, 0x40};

/*! @brief Read Suspend Registers. */
static const uint8_t ReadSuspendRegisters[] = {0x17, 0x10, 0x04, 0x04};

/*! @brief Write Suspend Registers (The actual value has to be updated as required). */
static uint8_t WriteSuspendRegisters[] = {0x17, 0x20, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00};

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief The Read Version Info Command. */
const uint8_t ReadVersionInfo[4] = {0x00, 0x00, 0x00, 0x0C};

/*! @brief Configure MBOX for QR Data and XYZ Axes Command. */
const uint8_t MBoxQRDataXYZ[16] = {0x04, 0x20, 0x2C, 0x0C, 0x06, 0x13, 0x06, 0x12,
                                   0x06, 0x15, 0x06, 0x14, 0x06, 0x17, 0x06, 0x16};

/*! @brief Set Sensor to Legacy (free running) Mode Command. */
const uint8_t SetLegacyMode[5] = {0x18, 0x20, 0x00, 0x01, 0x10};

/*! @brief Set Sensor to Legacy Mode with INT_O interrupt on completion of the AFE sampling. */
const uint8_t SetLegacyIntMode[5] = {0x18, 0x20, 0x00, 0x01, 0xB0};

/*! @brief Set sensor to Wake Mode Command. */
const uint8_t WakeApplication[5] = {0x12, 0x20, 0x06, 0x01, 0x00};

/*! @brief Command to reset all applications of the sensor. */
const uint8_t ResetApplication[5] = {0x17, 0x20, 0x03, 0x01, 0x01};

/*! @brief Full-Scale Range Selections. */
const uint8_t SetFSRange_2g[5] = {0x06, 0x20, 0x00, 0x01, 0x40};
const uint8_t SetFSRange_4g[5] = {0x06, 0x20, 0x00, 0x01, 0x80};
const uint8_t SetFSRange_8g[5] = {0x06, 0x20, 0x00, 0x01, 0x00};

/*! @brief Sample Rate Commands. */
const uint8_t SetSampleRate_488Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x07};
const uint8_t SetSampleRate_244Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x08};
const uint8_t SetSampleRate_122Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x09};
const uint8_t SetSampleRate_61Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x0A};
const uint8_t SetSampleRate_30Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x0B};
const uint8_t SetSampleRate_15Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x0C};
const uint8_t SetSampleRate_7Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x0D};
const uint8_t SetSampleRate_3Hz[5] = {0x06, 0x20, 0x0C, 0x01, 0x0E};

/*! @brief AFE Priority Commands. */
const uint8_t SetAFEPriority_for488Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD7};
const uint8_t SetAFEPriority_for224Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD6};
const uint8_t SetAFEPriority_for122Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD5};
const uint8_t SetAFEPriority_for61Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD4};
const uint8_t SetAFEPriority_for30Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD3};
const uint8_t SetAFEPriority_for15Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD2};
const uint8_t SetAFEPriority_for7Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD1};
const uint8_t SetAFEPriority_for3Hz[5] = {0x01, 0x20, 0x32, 0x01, 0xD0};

/*! @brief MBox Priority Commands. */
const uint8_t SetMBoxPriority_for488Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD7};
const uint8_t SetMBoxPriority_for244Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD6};
const uint8_t SetMBoxPriority_for122Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD5};
const uint8_t SetMBoxPriority_for61Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD4};
const uint8_t SetMBoxPriority_for30Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD3};
const uint8_t SetMBoxPriority_for15Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD2};
const uint8_t SetMBoxPriority_for7Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD1};
const uint8_t SetMBoxPriority_for3Hz[5] = {0x01, 0x20, 0x30, 0x01, 0xD0};

/*! @brief Command to Read Pedometer Data. */
const uint8_t ReadPedometerData[4] = {0x15, 0x30, 0x00, 0x0C};

const registercommandlist_t MMA9553_InitializeCommand[] = {{MBoxQRDataXYZ, 0, sizeof(MBoxQRDataXYZ)},
                                                           __END_WRITE_CMD__};

const registercommandlist_t MMA9553_ReadSuspendRegistersCommand[] = {
    {ReadSuspendRegisters, 0, sizeof(ReadSuspendRegisters)}, __END_WRITE_CMD__};

const registercommandlist_t MMA9553_ActivateCommands[] = {{WriteSuspendRegisters, 0, sizeof(WriteSuspendRegisters)},
                                                          {WakeApplication, 0, sizeof(WakeApplication)},
                                                          {SetLegacyMode, 0, sizeof(SetLegacyMode)},
                                                          __END_WRITE_CMD__};

const registercommandlist_t MMA9553_StandbyCommands[] = {
    {SuspendAFE, 0, sizeof(SuspendAFE)}, {SuspendPedometer, 0, sizeof(SuspendPedometer)}, __END_WRITE_CMD__};

const registercommandlist_t MMA9553_ResetCommand[] = {{ResetApplication, 0, sizeof(ResetApplication)},
                                                      __END_WRITE_CMD__};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void MMA9553_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = mma9553_spiRead_CmdBuffer;
    uint8_t *pRBuff = mma9553_spiRead_DataBuffer;

    /* Formatting for Read command of MMA9553 SENSOR. */
    *(pWBuff) =
        (offset & 0x7F) << 1; /* offset is the internal register address of the sensor at which write is performed. */

    /* Create the slave read command. */
    pSlaveCmd->size = size + MMA9553_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void MMA9553_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = mma9553_spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = mma9553_spiWrite_CmdDataBuffer + size + MMA9553_SPI_CMD_LEN;

    /* Formatting for Write command of MMA9553 SENSOR. */
    *(pWBuff) =
        (offset | 0x40) << 1; /* offset is the internal register address of the sensor at which write is performed. */

    /* Copy the slave write command */
    memcpy(pWBuff + MMA9553_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + MMA9553_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

int32_t MMA9553_SPI_Initialize(
    mma9553_spi_sensorhandle_t *pSensorHandle, ARM_DRIVER_SPI *pBus, uint8_t index, void *pSlaveSelect, void *pReset)
{
    int32_t status;
    uint8_t cmdRespHdr[MMA9553_HDR_SIZE] = {0};
    GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

    /*! Check the input parameters. */
    if (pSensorHandle == NULL || pBus == NULL || pSlaveSelect == NULL || pReset == NULL)
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveParams.pReadPreprocessFN = MMA9553_SPI_ReadPreprocess;
    pSensorHandle->slaveParams.pWritePreprocessFN = MMA9553_SPI_WritePreprocess;
    pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
    pSensorHandle->slaveParams.spiCmdLen = MMA9553_SPI_CMD_LEN;
    pSensorHandle->slaveParams.ssActiveValue = MMA9553_SS_ACTIVE_VALUE;

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Initialize the Slave Select and reset Pins. */
    pGPIODriver->pin_init(pSlaveSelect, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGPIODriver->pin_init(pReset, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /* Pull down SS and Reset */
    pGPIODriver->clr_pin(pSlaveSelect);
    pGPIODriver->set_pin(pReset);

    BOARD_DELAY_ms(1); /* Wait for Part to Complete Reset */
    pGPIODriver->clr_pin(pReset);

    BOARD_DELAY_ms(2); /* Wait for Part to Initialize in SPI Mode */
    pGPIODriver->set_pin(pSlaveSelect);

    /* Verify if the SPI connection by writing command to fetch Version Info and waiting for a sufficient duration.
     * A valid response COCO and length fields indicate command acceptance and by nature Sensor Identity. */
    Register_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams, 0,
                            ReadVersionInfo, sizeof(ReadVersionInfo));
    BOARD_DELAY_ms(1);
    status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams, 0,
                               sizeof(cmdRespHdr), cmdRespHdr);
    if (ARM_DRIVER_OK != status || (cmdRespHdr[1] & 0x80) != 0x80 || cmdRespHdr[2] != ReadVersionInfo[3] ||
        cmdRespHdr[3] != ReadVersionInfo[3])
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    /* Send the Initialize commands to the Sensor. */
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   MMA9553_InitializeCommand, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void MMA9553_SPI_SetIdleTask(mma9553_spi_sensorhandle_t *pSensorHandle,
                             registeridlefunction_t idleTask,
                             void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t MMA9553_SPI_Configure(mma9553_spi_sensorhandle_t *pSensorHandle, const registercommandlist_t *pCommandList)
{
    int32_t status;
    uint8_t standbyRegister[MMA9553_HDR_SIZE + STANDBY_REG_SIZE];

    /*! Validate for the correct handle and register write list.*/
    if ((pSensorHandle == NULL) || (pCommandList == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before applying configuration.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /* Write command to fetch Standby register. */
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   MMA9553_ReadSuspendRegistersCommand, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Read the standby register values. */
    status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams, 0,
                               sizeof(standbyRegister), standbyRegister);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_READ;
    }

    /* Set Bits for AFE and Pedometer Standby. */
    SuspendAFE[MMA9553_HDR_SIZE] |= standbyRegister[MMA9553_HDR_SIZE + 3];
    SuspendPedometer[MMA9553_HDR_SIZE] |= standbyRegister[MMA9553_HDR_SIZE + 1];

    /* Put the sensor to Standby Mode. */
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   MMA9553_StandbyCommands, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Send the requested commands to the Sensor. */
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   pCommandList, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Put the sensor to out of standby Mode. */
    memcpy(WriteSuspendRegisters + MMA9553_HDR_SIZE, standbyRegister + MMA9553_HDR_SIZE, STANDBY_REG_SIZE);
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   MMA9553_ActivateCommands, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t MMA9553_SPI_CommandResponse(mma9553_spi_sensorhandle_t *pSensorHandle,
                                    const registercommandlist_t *pCommandList,
                                    const registerreadlist_t *pResponseList,
                                    uint8_t *pBuffer)
{
    int32_t status;

    /*! Validate for the correct handle and command list.*/
    if (pSensorHandle == NULL || (pCommandList == NULL && pResponseList == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before reading sensor data.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    if (pCommandList != NULL)
    { /* Write command to fetch configuration. */
        status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                       pCommandList, MMA9553_COCO_ERROR_MASK);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_WRITE;
        }
    }

    /*! Parse through the read list and read the data one by one. */
    if (pResponseList != NULL)
    {
        status = Sensor_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                 pResponseList, pBuffer);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_READ;
        }
    }

    return SENSOR_ERROR_NONE;
}

int32_t MMA9553_SPI_DeInit(mma9553_spi_sensorhandle_t *pSensorHandle)
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
    status = Sensor_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                                   MMA9553_ResetCommand, MMA9553_COCO_ERROR_MASK);
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

int32_t MMA9553_I2C_Initialize(mma9553_i2c_sensorhandle_t *pSensorHandle,
                               ARM_DRIVER_I2C *pBus,
                               uint8_t index,
                               uint16_t sAddress)
{
    int32_t status;
    uint8_t cmdRespHdr[MMA9553_HDR_SIZE] = {0};

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Verify if the I2C connection by writing command to fetch Version Info and waiting for a sufficient duration.
     * A valid response COCO and length fields indicate command acceptance and by nature Sensor Identity. */
    Register_I2C_BlockWrite(pBus, &pSensorHandle->deviceInfo, sAddress, 0, ReadVersionInfo, sizeof(ReadVersionInfo));
    BOARD_DELAY_ms(1);
    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, 0, sizeof(cmdRespHdr), cmdRespHdr);
    if (ARM_DRIVER_OK != status || (cmdRespHdr[1] & 0x80) != 0x80 || cmdRespHdr[2] != ReadVersionInfo[3] ||
        cmdRespHdr[3] != ReadVersionInfo[3])
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    /* Send the Initialize commands to the Sensor. */
    status = Sensor_I2C_BlockWrite(pBus, &pSensorHandle->deviceInfo, sAddress, MMA9553_InitializeCommand,
                                   MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_WRITE;
    }

    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveAddress = sAddress;
    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void MMA9553_I2C_SetIdleTask(mma9553_i2c_sensorhandle_t *pSensorHandle,
                             registeridlefunction_t idleTask,
                             void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t MMA9553_I2C_Configure(mma9553_i2c_sensorhandle_t *pSensorHandle, const registercommandlist_t *pCommandList)
{
    int32_t status;
    uint8_t standbyRegister[MMA9553_HDR_SIZE + STANDBY_REG_SIZE];

    /* Validate for the correct handle.*/
    if ((pSensorHandle == NULL) || (pCommandList == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before applying configuration.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    /* Write command to fetch Standby register. */
    status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   MMA9553_ReadSuspendRegistersCommand, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Read the standby register values. */
    status = Register_I2C_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress, 0,
                               sizeof(standbyRegister), standbyRegister);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_READ;
    }

    /* Set Bits for AFE and Pedometer Standby. */
    SuspendAFE[MMA9553_HDR_SIZE] |= standbyRegister[MMA9553_HDR_SIZE + 3];
    SuspendPedometer[MMA9553_HDR_SIZE] |= standbyRegister[MMA9553_HDR_SIZE + 1];

    /* Put the sensor to Standby Mode. */
    status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   MMA9553_StandbyCommands, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Send the requested commands to the Sensor. */
    status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   pCommandList, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    /* Put the sensor to out of standby Mode. */
    memcpy(WriteSuspendRegisters + MMA9553_HDR_SIZE, standbyRegister + MMA9553_HDR_SIZE, STANDBY_REG_SIZE);
    status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   MMA9553_ActivateCommands, MMA9553_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t MMA9553_I2C_CommandResponse(mma9553_i2c_sensorhandle_t *pSensorHandle,
                                    const registercommandlist_t *pCommandList,
                                    const registerreadlist_t *pResponseList,
                                    uint8_t *pBuffer)
{
    int32_t status;

    /*! Validate for the correct handle and register read list.*/
    if (pSensorHandle == NULL || (pCommandList == NULL && pResponseList == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Check whether sensor handle is initialized before reading sensor data.*/
    if (pSensorHandle->isInitialized != true)
    {
        return SENSOR_ERROR_INIT;
    }

    if (pCommandList != NULL)
    { /* Write command to fetch configuration. */
        status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                       pCommandList, MMA9553_COCO_ERROR_MASK);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_WRITE;
        }
    }

    if (pResponseList != NULL)
    { /* Parse through the read list and read the data one by one */
        status = Sensor_I2C_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                 pResponseList, pBuffer);
        if (ARM_DRIVER_OK != status)
        {
            return SENSOR_ERROR_READ;
        }
    }

    return SENSOR_ERROR_NONE;
}

int32_t MMA9553_I2C_DeInit(mma9553_i2c_sensorhandle_t *pSensorHandle)
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

    /* Reset the device to put it into default state. */
    status = Sensor_I2C_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, pSensorHandle->slaveAddress,
                                   MMA9553_ResetCommand, MMA9553_COCO_ERROR_MASK);
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
