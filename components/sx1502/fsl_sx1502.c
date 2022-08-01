/*
 * Copyright  2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sx1502.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t SX1502_I2C_Send(void *handle,
                                uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subaddressSize,
                                uint8_t *txBuff,
                                uint8_t txBuffSize);

static status_t SX1502_I2C_Receive(void *handle,
                                   uint8_t deviceAddress,
                                   uint32_t subAddress,
                                   uint8_t subaddressSize,
                                   uint8_t *rxBuff,
                                   uint8_t rxBuffSize);

static status_t SX1502_I2C_Deinit(void *handle);

static status_t SX1502_I2C_Init(void *handle, uint32_t i2cInstance, uint32_t i2cBaudrate, uint32_t i2cSourceClockHz);
/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t SX1502_I2C_Receive(void *handle,
                                   uint8_t deviceAddress,
                                   uint32_t subAddress,
                                   uint8_t subaddressSize,
                                   uint8_t *rxBuff,
                                   uint8_t rxBuffSize)
{
    hal_i2c_master_transfer_t masterXfer;

    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kHAL_I2cRead;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.flags          = (uint32_t)kHAL_I2cTransferDefaultFlag;

    return (status_t)HAL_I2cMasterTransferBlocking((hal_i2c_master_handle_t *)handle, &masterXfer);
}

static status_t SX1502_I2C_Send(void *handle,
                                uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subaddressSize,
                                uint8_t *txBuff,
                                uint8_t txBuffSize)
{
    hal_i2c_master_transfer_t masterXfer;

    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kHAL_I2cWrite;
    masterXfer.subaddress     = (uint32_t)subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data           = txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = (uint32_t)kHAL_I2cTransferDefaultFlag;

    return (status_t)HAL_I2cMasterTransferBlocking((hal_i2c_master_handle_t *)handle, &masterXfer);
}

static status_t SX1502_I2C_Deinit(void *handle)
{
    return (status_t)HAL_I2cMasterDeinit((hal_i2c_master_handle_t *)handle);
}

static status_t SX1502_I2C_Init(void *handle, uint32_t i2cInstance, uint32_t i2cBaudrate, uint32_t i2cSourceClockHz)
{
    hal_i2c_master_config_t masterConfig;

    masterConfig.enableMaster = true;
    masterConfig.baudRate_Bps = i2cBaudrate;
    masterConfig.srcClock_Hz  = i2cSourceClockHz;
    masterConfig.instance     = (uint8_t)i2cInstance;

    return (status_t)HAL_I2cMasterInit((hal_i2c_master_handle_t *)handle, &masterConfig);
}

/*!
 * brief SX1502 write register.
 *
 * param handle SX1502 handle structure.
 * param reg register address.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t SX1502_WriteRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t value)
{
    assert(handle != NULL);
    assert(handle->slaveAddress != 0U);

    return SX1502_I2C_Send(handle->i2cHandle, handle->slaveAddress, reg, 1U, (uint8_t *)&value, 1U);
}

/*!
 * brief SX1502 read register.
 *
 * param handle SX1502 handle structure.
 * param reg register address.
 * param value value to read.
 * return kStatus_Success, else failed.
 */
status_t SX1502_ReadRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t *value)
{
    assert(handle != NULL);
    assert(handle->slaveAddress != 0U);

    status_t retval   = 0;
    uint8_t readValue = 0U;

    retval = SX1502_I2C_Receive(handle->i2cHandle, handle->slaveAddress, (uint32_t)reg, 1U, (uint8_t *)&readValue, 1U);

    *value = readValue;

    return retval;
}

/*!
 * brief SX1502 modify register.
 *
 * param handle SX1502 handle structure.
 * param reg register address.
 * oaram mask register bits mask.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t SX1502_ModifyRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t value)
{
    status_t result;
    uint8_t regValue;

    result = SX1502_ReadRegister(handle, reg, &regValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    regValue &= (uint8_t)~mask;
    regValue |= value;

    return SX1502_WriteRegister(handle, reg, regValue);
}

/*!
 * brief Initializes SX1502.
 *
 * param handle SX1502 handle structure.
 * param sx1502_config SX1502 configuration structure.
 */
status_t SX1502_Init(sx1502_handle_t *handle, const sx1502_config_t *sx1502Config)
{
    assert(handle != NULL);
    assert(sx1502Config != NULL);

    status_t result;
    handle->slaveAddress = SX1502_I2C_ADDRESS;

    /* i2c bus initialization */
    result = SX1502_I2C_Init(handle->i2cHandle, sx1502Config->sx1502I2CInstance, SX1502_I2C_BITRATE,
                             sx1502Config->sx1502I2CSourceClock);
    if (result != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGPLDMODE, 0U);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGDATA, sx1502Config->initRegDataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGDIR, sx1502Config->initRegDirValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGPULLUP, 0U);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGPULLDOWN, 0U);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = SX1502_WriteRegister(handle, SX1502_REGADVANCED, 0U);
    if (result != kStatus_Success)
    {
        return result;
    }

    return result;
}

/*!
 * brief Deinitializes the SX1502.
 *
 * param handle SX1502 handle structure.
 * return kStatus_Success if successful, different code otherwise.
 */
status_t SX1502_Deinit(sx1502_handle_t *handle)
{
    return SX1502_I2C_Deinit(handle->i2cHandle);
}

/*!
 * brief SX1502 IO Set.
 *
 * param handle SX1502 handle structure.
 * param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * eg.Set IO1~IO3,ioMask is kSX1502_IO1|kSX1502_IO2|kSX1502_IO3.
 * return kStatus_Success, else failed.
 */
status_t SX1502_IO_Set(sx1502_handle_t *handle, uint8_t ioMask)
{
    uint8_t dataValue;
    status_t result;

    result = SX1502_ReadRegister(handle, SX1502_REGDATA, &dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    dataValue |= (ioMask);

    result = SX1502_WriteRegister(handle, SX1502_REGDATA, dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    return SX1502_IO_SetDirection(handle, ioMask, kSX1502_IO_Output);
}

/*!
 * brief SX1502 IO Clear.
 *
 * param handle SX1502 handle structure.
 * param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * eg.Clear IO1~IO3,ioMask is kSX1502_IO1|kSX1502_IO2|kSX1502_IO3.
 * return kStatus_Success, else failed.
 */
status_t SX1502_IO_Clear(sx1502_handle_t *handle, uint8_t ioMask)
{
    uint8_t dataValue;
    status_t result;

    result = SX1502_ReadRegister(handle, SX1502_REGDATA, &dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    dataValue &= ~(ioMask);

    result = SX1502_WriteRegister(handle, SX1502_REGDATA, dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    return SX1502_IO_SetDirection(handle, ioMask, kSX1502_IO_Output);
}

/*!
 * brief SX1502 IO Direction to input or output.
 *
 * This API is used to set the direction of any IO combination.For example,set the direction of IO0~IO3 as output.
 * SX1502_IO_SetDirection(handle, kSX1502_IO0|kSX1502_IO1|kSX1502_IO2|kSX1502_IO3, kSX1502_IO_Output);
 *
 * param handle SX1502 handle structure.
 * param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * param ioDirection set IO direction to input or output.
 * return kStatus_Success, else failed.
 */
status_t SX1502_IO_SetDirection(sx1502_handle_t *handle, uint8_t ioMask, sx1502_io_dir_t ioDirection)
{
    uint8_t dirValue;
    status_t result;

    result = SX1502_ReadRegister(handle, SX1502_REGDIR, &dirValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    switch (ioDirection)
    {
        case kSX1502_IO_Output:
            dirValue &= ~(ioMask);
            break;
        case kSX1502_IO_Input:
            dirValue |= (ioMask);
            break;
        default:
            /* Avoid MISRA 16.4 violation */
            break;
    }

    return SX1502_WriteRegister(handle, SX1502_REGDIR, dirValue);
}

/*!
 * brief SX1502 IO output status in a pattern.
 *
 * This API is used to set any IO combination and output in any pattern.
 * For example,set IO0~IO3 as output and iopattern as 0101,iopattern is 0x05U.
 * SX1502_IO_OutputControl(handle, kSX1502_IO0|kSX1502_IO1|kSX1502_IO2|kSX1502_IO3, 0x05U);
 *
 * param handle SX1502 handle structure.
 * param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * param ioPattern ioPattern is the pattern of IO status to set.0-output low,1-output high.
 * return kStatus_Success, else failed.
 */
status_t SX1502_IO_OutputControl(sx1502_handle_t *handle, uint8_t ioMask, uint8_t ioPattern)
{
    uint8_t dataValue;
    status_t result;

    result = SX1502_ReadRegister(handle, SX1502_REGDATA, &dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    dataValue = (dataValue & ~ioMask) | ioPattern;

    result = SX1502_WriteRegister(handle, SX1502_REGDATA, dataValue);
    if (result != kStatus_Success)
    {
        return result;
    }

    return SX1502_IO_SetDirection(handle, ioMask, kSX1502_IO_Output);
}
