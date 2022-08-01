/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  fxlc95000_drv.c
 * @brief The fxlc95000_drv.c file implements the FXLC95000 sensor driver interface.
 */

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "gpio_driver.h"
#include "fxlc95000_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
uint8_t fxlc95000_spiRead_CmdBuffer[FXLC95000_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxlc95000_spiRead_DataBuffer[FXLC95000_SPI_MAX_MSG_SIZE] = {0};
uint8_t fxlc95000_spiWrite_CmdDataBuffer[FXLC95000_SPI_MAX_MSG_SIZE] = {0};

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------
void FXLC95000_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxlc95000_spiRead_CmdBuffer;
    uint8_t *pRBuff = fxlc95000_spiRead_DataBuffer;

    /* Formatting for Read command of FXLC95000 SENSOR. */
    *(pWBuff) =
        (offset & 0x7F) << 1; /* offset is the internal register address of the sensor at which write is performed. */

    /* Create the slave read command. */
    pSlaveCmd->size = size + FXLC95000_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void FXLC95000_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = fxlc95000_spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = fxlc95000_spiWrite_CmdDataBuffer + size + FXLC95000_SPI_CMD_LEN;

    /* Formatting for Write command of FXLC95000 SENSOR. */
    *(pWBuff) =
        (offset | 0x40) << 1; /* offset is the internal register address of the sensor at which write is performed. */

    /* Copy the slave write command */
    memcpy(pWBuff + FXLC95000_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + FXLC95000_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

int32_t FXLC95000_SPI_Initialize(fxlc95000_spi_sensorhandle_t *pSensorHandle,
                                 ARM_DRIVER_SPI *pBus,
                                 uint8_t index,
                                 void *pSpiSelect,
                                 void *pSlaveSelect,
                                 void *pReset,
                                 uint16_t buildId)
{
    int32_t status;
    uint16_t readNumber[2];
    GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

    /*! Check the input parameters. */
    if (pSensorHandle == NULL || pBus == NULL || pSpiSelect == NULL || pSlaveSelect == NULL || pReset == NULL)
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /*! Initialize the sensor handle. */
    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveParams.pReadPreprocessFN = FXLC95000_SPI_ReadPreprocess;
    pSensorHandle->slaveParams.pWritePreprocessFN = FXLC95000_SPI_WritePreprocess;
    pSensorHandle->slaveParams.pTargetSlavePinID = pSlaveSelect;
    pSensorHandle->slaveParams.spiCmdLen = FXLC95000_SPI_CMD_LEN;
    pSensorHandle->slaveParams.ssActiveValue = FXLC95000_SS_ACTIVE_VALUE;

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Initialize the Slave Select and reset Pins. */
    pGPIODriver->pin_init(pSlaveSelect, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGPIODriver->pin_init(pSpiSelect, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    pGPIODriver->pin_init(pReset, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /* Pull down SPI Select, Pull up SS and Reset */
    pGPIODriver->set_pin(pSlaveSelect);
    pGPIODriver->clr_pin(pSpiSelect);
    pGPIODriver->set_pin(pReset);
    BOARD_DELAY_ms(30); /* Wait for Part to Complete Reset */

    pGPIODriver->clr_pin(pReset);
    BOARD_DELAY_ms(50); /* Wait for Part to Initialize in SPI Mode */

    pGPIODriver->set_pin(pSpiSelect);
    BOARD_DELAY_ms(10); /* Wait for ROM Initialization before communication */

    /* Verify if the SPI connection by writing command to Boot to flash and fetch Device Info.
     * A matching Build Number confirms Sensor Identity and Firmware. */
    Register_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams, 0,
                            BootToFlash, sizeof(BootToFlash));
    BOARD_DELAY_ms(10); /* Allow time for the device to boot to Flash. */
    Register_SPI_BlockWrite(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams, 0,
                            GetDeviceInfoCmd, sizeof(GetDeviceInfoCmd));
    BOARD_DELAY_ms(1);

    status = Register_SPI_Read(pSensorHandle->pCommDrv, &pSensorHandle->deviceInfo, &pSensorHandle->slaveParams,
                               FXLC95000_BUILD_ID_OFFSET, FXLC95000_BUILD_ID_SIZE + FXLC95000_PART_NUMBER_SIZE,
                               (uint8_t *)&readNumber);
    readNumber[0] = (readNumber[0] >> 8) | (readNumber[0] << 8);
    readNumber[1] = (readNumber[1] >> 8) | (readNumber[1] << 8);
    if (ARM_DRIVER_OK != status || readNumber[0] != buildId || readNumber[1] != FXLC95000_PART_NUMBER)
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    pSensorHandle->isInitialized = true;
    return SENSOR_ERROR_NONE;
}

void FXLC95000_SPI_SetIdleTask(fxlc95000_spi_sensorhandle_t *pSensorHandle,
                               registeridlefunction_t idleTask,
                               void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t FXLC95000_SPI_CommandResponse(fxlc95000_spi_sensorhandle_t *pSensorHandle,
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
                                       pCommandList, FXLC95000_COCO_ERROR_MASK);
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

int32_t FXLC95000_I2C_CheckRomMode(ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress)
{
    int32_t status;
    uint16_t readNumber[2];
    registerDeviceInfo_t deviceInfo = {.deviceInstance = index, .idleFunction = NULL};

    Register_I2C_BlockWrite(pBus, &deviceInfo, sAddress, 0, GetDeviceInfoCmd, sizeof(GetDeviceInfoCmd));
    BOARD_DELAY_ms(1);

    status = Register_I2C_Read(pBus, &deviceInfo, sAddress, FXLC95000_BUILD_ID_OFFSET,
                               FXLC95000_BUILD_ID_SIZE + FXLC95000_PART_NUMBER_SIZE, (uint8_t *)&readNumber);
    readNumber[0] = (readNumber[0] >> 8) | (readNumber[0] << 8);
    readNumber[1] = (readNumber[1] >> 8) | (readNumber[1] << 8);
    if (ARM_DRIVER_OK != status || readNumber[0] != FXLC95000_RESERVED_ID || readNumber[1] != FXLC95000_PART_NUMBER)
    {
        return -1;
    }

    return 0;
}

int32_t FXLC95000_I2C_FlashCommands(ARM_DRIVER_I2C *pBus,
                                    uint8_t index,
                                    uint16_t sAddress,
                                    const registercommandlist_t *pCommandList)
{
    int32_t status;
    registerDeviceInfo_t deviceInfo = {.deviceInstance = index, .idleFunction = NULL};

    /*! Validate for the correct handle and register write list.*/
    if (pBus == NULL || pCommandList == NULL)
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    /* Write command to fetch configuration. */
    status = Sensor_I2C_BlockWrite(pBus, &deviceInfo, sAddress, pCommandList, FXLC95000_COCO_ERROR_MASK);
    if (ARM_DRIVER_OK != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLC95000_I2C_FlashPayload(
    ARM_DRIVER_I2C *pBus, uint8_t index, uint16_t sAddress, uint8_t *pFlashBytes, uint8_t numBytes)
{
    int32_t status;

    /* First 4 bytes is address (which fits into 2 byte separate address field and Bank code)
     * and then remaining bytes is WData. */
    /* Make sure that the Flash payload received has the minimum information bytes
     * required to construct a CI_READ_WRITE ROM Command. */
    if (numBytes >= FXLC95000_FLASH_PAYLOAD_ADDR_LEN + FXLC95000_ROM_CI_WRITE_MIN_LEN)
    {
        uint8_t bytesToPageBoundary = 256 - *(pFlashBytes + 3);
        uint8_t bytesAfterPageBoundary = numBytes - bytesToPageBoundary - FXLC95000_FLASH_PAYLOAD_ADDR_LEN;
        /* Prepare CI_READ_WRITE ROM Command. */
        /* Check if the write command being attempted spans across a page boundary (256 bytes). */
        if (bytesToPageBoundary > 0 && bytesToPageBoundary < numBytes - FXLC95000_FLASH_PAYLOAD_ADDR_LEN)
        { /* Break it into 2 write commands if write spans across 2 pages. Ref. Section 16.5 of FXLC95000CLHWRM. */
            uint8_t writeFlashCommand[FXLC95000_ROM_CI_READ_WRITE_MAX_LEN] = {0x0A, 0x00, 0x12, 0x34, 0x56, 0x78};
            uint8_t writeFlashCommand_2[FXLC95000_ROM_CI_READ_WRITE_MAX_LEN] = {0x0A, 0x00, 0x12, 0x34, 0x56, 0x78};

            writeFlashCommand[1] =
                (*(pFlashBytes + 1) == 0) ? 0x1F & (bytesToPageBoundary) : 0xC0 | (bytesToPageBoundary);
            for (int i = 0; i < bytesToPageBoundary + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN;
                 i++) // 2 LSB Bytes of Address + Data.
            {
                writeFlashCommand[FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + i] =
                    pFlashBytes[FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN + i];
            }

            writeFlashCommand_2[1] =
                (*(pFlashBytes + 1) == 0) ? 0x1F & (bytesAfterPageBoundary) : 0xC0 | (bytesAfterPageBoundary);
            uint8_t address[] = {*(pFlashBytes + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN + 1),
                                 *(pFlashBytes + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN)};
            *((uint16_t *)address) += bytesToPageBoundary;
            writeFlashCommand_2[FXLC95000_ROM_CI_READ_WRITE_HDR_LEN] = address[1];
            writeFlashCommand_2[FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + 1] = address[0];
            for (int i = 0; i < bytesAfterPageBoundary; i++)
            {
                writeFlashCommand_2[FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN + i] =
                    pFlashBytes[FXLC95000_FLASH_PAYLOAD_ADDR_LEN + bytesToPageBoundary + i];
            }

            if (bytesToPageBoundary > FXLC95000_ROM_CI_WRITE_MAX_LEN ||
                bytesAfterPageBoundary > FXLC95000_ROM_CI_WRITE_MAX_LEN)
            {
                return SENSOR_ERROR_INVALID_PARAM;
            }
            else
            { /* Create Command List to Write. */
                const registercommandlist_t cWriteFlashSequence[] = {
                    {writeFlashCommand, 0,
                     FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN + bytesToPageBoundary},
                    {writeFlashCommand_2, 0, FXLC95000_ROM_CI_READ_WRITE_HDR_LEN +
                                                 FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN + bytesAfterPageBoundary},
                    __END_WRITE_CMD__};
                /* Write Flash Bytes as Commands to Sensor. */
                status = FXLC95000_I2C_FlashCommands(pBus, index, sAddress, cWriteFlashSequence);
                if (ARM_DRIVER_OK != status)
                {
                    return SENSOR_ERROR_WRITE;
                }
            }
        }
        else /* If write is enclosed within 1-page, a single CI_READ_WRITE will do the job. */
        {
            uint8_t writeFlashCommand[FXLC95000_ROM_CI_READ_WRITE_MAX_LEN] = {0x0A, 0x00, 0x12, 0x34, 0x56, 0x78};
            writeFlashCommand[1] = /* Ref. Section 16.5 of FXLC95000CLHWRM. */
                (*(pFlashBytes + 1) == 0) ? 0x1F & (numBytes - FXLC95000_FLASH_PAYLOAD_ADDR_LEN) :
                                            0xC0 | (numBytes - FXLC95000_FLASH_PAYLOAD_ADDR_LEN);

            for (int i = FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN; i < numBytes; i++) // Skip 2 MSBs of Address.
            {
                writeFlashCommand[FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + i - FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN] =
                    pFlashBytes[i];
            }
            if (FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + numBytes >
                FXLC95000_ROM_CI_WRITE_MAX_LEN + FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN)
            {
                return SENSOR_ERROR_INVALID_PARAM;
            }
            else
            { /* Create Command List to Write. */
                const registercommandlist_t cWriteFlashSequence[] = {
                    {writeFlashCommand, 0,
                     FXLC95000_ROM_CI_READ_WRITE_HDR_LEN + numBytes - FXLC95000_ROM_CI_READ_WRITE_ADDR_LEN},
                    __END_WRITE_CMD__};
                /* Write Flash Bytes as Commands to Sensor. */
                status = FXLC95000_I2C_FlashCommands(pBus, index, sAddress, cWriteFlashSequence);
                if (ARM_DRIVER_OK != status)
                {
                    return SENSOR_ERROR_WRITE;
                }
            }
        }
    }
    else
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    return SENSOR_ERROR_NONE;
}

int32_t FXLC95000_I2C_Initialize(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
                                 ARM_DRIVER_I2C *pBus,
                                 uint8_t index,
                                 uint16_t sAddress,
                                 uint16_t buildId)
{
    int32_t status;
    uint16_t readNumber[2];

    /*! Check the input parameters. */
    if ((pSensorHandle == NULL) || (pBus == NULL))
    {
        return SENSOR_ERROR_INVALID_PARAM;
    }

    pSensorHandle->deviceInfo.deviceInstance = index;
    pSensorHandle->deviceInfo.functionParam = NULL;
    pSensorHandle->deviceInfo.idleFunction = NULL;

    /* Verify if the I2C connection by writing command to Boot to flash and fetch Device Info.
     * A matching Build Number confirms Sensor Identity and Firmware. */
    Register_I2C_BlockWrite(pBus, &pSensorHandle->deviceInfo, sAddress, 0, BootToFlash, sizeof(BootToFlash));
    BOARD_DELAY_ms(10); /* Allow time for the device to boot to Flash. */
    Register_I2C_BlockWrite(pBus, &pSensorHandle->deviceInfo, sAddress, 0, GetDeviceInfoCmd, sizeof(GetDeviceInfoCmd));
    BOARD_DELAY_ms(1);

    status = Register_I2C_Read(pBus, &pSensorHandle->deviceInfo, sAddress, FXLC95000_BUILD_ID_OFFSET,
                               FXLC95000_BUILD_ID_SIZE + FXLC95000_PART_NUMBER_SIZE, (uint8_t *)&readNumber);
    readNumber[0] = (readNumber[0] >> 8) | (readNumber[0] << 8);
    readNumber[1] = (readNumber[1] >> 8) | (readNumber[1] << 8);
    if (ARM_DRIVER_OK != status || readNumber[0] != buildId || readNumber[1] != FXLC95000_PART_NUMBER)
    {
        pSensorHandle->isInitialized = false;
        return SENSOR_ERROR_INIT;
    }

    pSensorHandle->pCommDrv = pBus;
    pSensorHandle->slaveAddress = sAddress;
    pSensorHandle->isInitialized = true;

    return SENSOR_ERROR_NONE;
}

void FXLC95000_I2C_SetIdleTask(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
                               registeridlefunction_t idleTask,
                               void *userParam)
{
    pSensorHandle->deviceInfo.functionParam = userParam;
    pSensorHandle->deviceInfo.idleFunction = idleTask;
}

int32_t FXLC95000_I2C_CommandResponse(fxlc95000_i2c_sensorhandle_t *pSensorHandle,
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
                                       pCommandList, FXLC95000_COCO_ERROR_MASK);
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
