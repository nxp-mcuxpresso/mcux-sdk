/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_fxls.h"

/******************************************************************************
 * Code
 ******************************************************************************/
status_t FXLS_Init(fxls_handle_t *fxls_handle, fxls_config_t *config)
{
    assert(fxls_handle != NULL);
    assert(config != NULL);
    assert(config->I2C_SendFunc != NULL);
    assert(config->I2C_ReceiveFunc != NULL);

    uint8_t tmp[1] = {0};

    /* Initialize the I2C access function. */
    fxls_handle->I2C_SendFunc    = config->I2C_SendFunc;
    fxls_handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    fxls_handle->slaveAddress = config->slaveAddress;

    if (FXLS_ReadReg(fxls_handle, WHO_AM_I_REG, tmp, 1) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (tmp[0] != kFXLS_WHO_AM_I_Device_ID)
    {
        return kStatus_Fail;
    }

    /* Setup SENS_CONFIG1 register to enter standby mode. */
    if (FXLS_ReadReg(fxls_handle, SENS_CONFIG1_REG, tmp, 1) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (FXLS_WriteReg(fxls_handle, SENS_CONFIG1_REG, tmp[0] & (uint8_t)~ACTIVE_MASK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Read again to make sure we are in standby mode. */
    if (FXLS_ReadReg(fxls_handle, SENS_CONFIG1_REG, tmp, 1) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if ((tmp[0] & ACTIVE_MASK) == ACTIVE_MASK)
    {
        return kStatus_Fail;
    }

    if (FXLS_WriteReg(fxls_handle, SENS_CONFIG2_REG, 0) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (FXLS_WriteReg(fxls_handle, SENS_CONFIG4_REG, 0x1) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (FXLS_WriteReg(fxls_handle, SENS_CONFIG1_REG, ACTIVE_MASK) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    /* Read SENS_CONFIG1 register again to ensure we are in active mode */
    if (FXLS_ReadReg(fxls_handle, SENS_CONFIG1_REG, tmp, 1) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if ((tmp[0] & ACTIVE_MASK) != ACTIVE_MASK)
    {
        return kStatus_Fail;
    }

    if (FXLS_WriteReg(fxls_handle, SENS_CONFIG4_REG, 0x5) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

status_t FXLS_ReadAccelRawData(fxls_handle_t *fxls_handle, fxls_accel_raw_data_t *accelRawData)
{
    status_t status = kStatus_Success;

    if ((FXLS_ReadReg(fxls_handle, OUT_X_LSB_REG, (uint8_t *)accelRawData, 6)) != kStatus_Success)
    {
        status = kStatus_Fail;
    }

    return status;
}

status_t FXLS_ReadAccelData(fxls_handle_t *fxls_handle, fxls_accel_data_t *accelData)
{
    status_t status     = kStatus_Success;
    uint8_t tmp_buff[6] = {0};

    if ((FXLS_ReadReg(fxls_handle, OUT_X_LSB_REG, tmp_buff, 6)) != kStatus_Success)
    {
        status = kStatus_Fail;
    }
    else
    {
        /* Get the X and Y data from the sensor data structure in 12 bit left format data*/
        accelData->accelX = (int16_t)(uint16_t)(((uint16_t)tmp_buff[1] << 8) | (uint16_t)tmp_buff[0]);
        accelData->accelY = (int16_t)(uint16_t)(((uint16_t)tmp_buff[3] << 8) | (uint16_t)tmp_buff[2]);
        accelData->accelZ = (int16_t)(uint16_t)(((uint16_t)tmp_buff[5] << 8) | (uint16_t)tmp_buff[4]);
    }

    return status;
}

status_t FXLS_ReadReg(fxls_handle_t *handle, uint8_t reg, uint8_t *val, uint8_t bytesNumber)
{
    assert(handle != NULL);
    assert(val != NULL);

    if ((handle->I2C_ReceiveFunc) == NULL)
    {
        return kStatus_Fail;
    }
    else
    {
        return handle->I2C_ReceiveFunc(handle->slaveAddress, reg, 1, val, bytesNumber);
    }
}

status_t FXLS_WriteReg(fxls_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle != NULL);

    if ((handle->I2C_SendFunc) == NULL)
    {
        return kStatus_Fail;
    }
    else
    {
        return handle->I2C_SendFunc(handle->slaveAddress, reg, 1, val);
    }
}
