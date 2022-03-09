/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mma.h"

/******************************************************************************
 * Code
 ******************************************************************************/
status_t MMA_Init(mma_handle_t *handle, mma_config_t *config)
{
    assert(handle);
    assert(config);

    uint8_t val = 0;

    /* Initialize the callback function. */
    handle->I2C_SendFunc    = config->I2C_SendFunc;
    handle->I2C_ReceiveFunc = config->I2C_ReceiveFunc;
    /* Set Slave Address. */
    handle->slaveAddress = config->slaveAddress;

    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_WHO_AM_I, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    if (val != (uint8_t)kMMA8652_WHO_AM_I_Device_ID)
    {
        return kStatus_Fail;
    }

    /* Put the mma8652 into standby mode */
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_CTRL_REG1, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val &= (uint8_t)~0x01U;
    if (MMA_WriteReg(handle, (uint8_t)kMMA8652_CTRL_REG1, val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Set the range, -4g to 4g */
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_XYZ_DATA_CFG, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val &= (uint8_t)~0x03U;
    val |= 0x01U;
    if (MMA_WriteReg(handle, (uint8_t)kMMA8652_XYZ_DATA_CFG, val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Set the F_MODE, disable FIFO */
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_F_SETUP, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    val &= 0x3FU;
    if (MMA_WriteReg(handle, (uint8_t)kMMA8652_F_SETUP, val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Put the mma8652 into active mode */
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_CTRL_REG1, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    val |= 0x01U;
    val &= (uint8_t)~0x02U; /* set F_READ to 0 */
    if (MMA_WriteReg(handle, (uint8_t)kMMA8652_CTRL_REG1, val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}

status_t MMA_ReadSensorData(mma_handle_t *handle, mma_data_t *accel)
{
    uint8_t val      = 0U;
    uint8_t ucStatus = 0;

    do
    {
        if (MMA_ReadReg(handle, (uint8_t)kMMA8652_STATUS, &ucStatus) != kStatus_Success)
        {
            return kStatus_Fail;
        }
    } while ((ucStatus & 0x08U) == 0U);

    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_X_MSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelXMSB = val;
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_X_LSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelXLSB = val;

    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_Y_MSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelYMSB = val;
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_Y_LSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelYLSB = val;

    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_Z_MSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelZMSB = val;
    if (MMA_ReadReg(handle, (uint8_t)kMMA8652_OUT_Z_LSB, &val) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    accel->accelZLSB = val;

    return kStatus_Success;
}

status_t MMA_ReadReg(mma_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle);
    assert(val);

    if (NULL == handle->I2C_ReceiveFunc)
    {
        return kStatus_Fail;
    }

    return handle->I2C_ReceiveFunc(handle->slaveAddress, reg, 1, val, 1);
}

status_t MMA_WriteReg(mma_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle);

    if (NULL == handle->I2C_SendFunc)
    {
        return kStatus_Fail;
    }

    return handle->I2C_SendFunc(handle->slaveAddress, reg, 1, val);
}
