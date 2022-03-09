/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_icm42688p.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t ICM42688P_WriteReg(icm42688p_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
    status_t result = kStatus_Success;
    result          = handle->Sensor_WriteTransfer(handle->sensorAddress, regAddress, regData, dataSize);

    return (result == kStatus_Success) ? result : kStatus_Fail;
}

status_t ICM42688P_ReadReg(icm42688p_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
    status_t result = kStatus_Success;
    result          = handle->Sensor_ReadTransfer(handle->sensorAddress, regAddress, regData, dataSize);

    return (result == kStatus_Success) ? result : kStatus_Fail;
}

status_t ICM42688P_Init(icm42688p_handle_t *handle, icm42688p_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);
    assert(config->Sensor_WriteTransfer != NULL);
    assert(config->Sensor_ReadTransfer != NULL);

    handle->Sensor_WriteTransfer = config->Sensor_WriteTransfer;
    handle->Sensor_ReadTransfer  = config->Sensor_ReadTransfer;
    handle->sensorAddress        = config->sensorAddress;

    status_t result = kStatus_Success;

    if (config->isReset)
    {
        uint8_t resetVal = 0x01;
        uint8_t bankSel  = 0;

        result = ICM42688P_WriteReg(handle, BANK_SEL, &bankSel, 1);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = ICM42688P_WriteReg(handle, DEVICE_CONFIG, &resetVal, 1);
        if (result != kStatus_Success)
        {
            return result;
        }
        SDK_DelayAtLeastUs(2000, SystemCoreClock);
    }

    return result;
}

status_t ICM42688P_EnableSensors(icm42688p_handle_t *handle)
{
    uint8_t sensorConfig = 0x1F;
    uint8_t fifoConfData = 0x03;
    uint8_t fifoInitVal  = 0x40;
    uint8_t whoamiVal    = 0;
    uint8_t readVal      = 0;
    status_t result      = kStatus_Success;

    result = ICM42688P_ReadReg(handle, WHO_AM_I, &whoamiVal, 1);
    if (result != kStatus_Success)
    {
        return result;
    }
    assert(whoamiVal == WHO_AM_I_VALUE);

    result = ICM42688P_WriteReg(handle, PWR_MGMT0, &sensorConfig, 1);
    if (result != kStatus_Success)
    {
        return result;
    }
    SDK_DelayAtLeastUs(1000, SystemCoreClock);
    result = ICM42688P_ReadReg(handle, PWR_MGMT0, &readVal, 1);
    assert(readVal == sensorConfig);

    result = ICM42688P_WriteReg(handle, FIFO_CONFIG, &fifoInitVal, 1);
    if (result != kStatus_Success)
    {
        return result;
    }
    SDK_DelayAtLeastUs(1000, SystemCoreClock);
    result = ICM42688P_ReadReg(handle, FIFO_CONFIG, &readVal, 1);
    assert(readVal == fifoInitVal);

    result = ICM42688P_WriteReg(handle, FIFO_CONFIG1, &fifoConfData, 1);

    SDK_DelayAtLeastUs(1000, SystemCoreClock);
    result = ICM42688P_ReadReg(handle, FIFO_CONFIG1, &readVal, 1);
    assert(readVal == fifoConfData);

    return result;
}

status_t ICM42688P_ConfigureTapDetectIBI(icm42688p_handle_t *handle)
{
    uint8_t confData = 0x40U;
    uint8_t bankSel  = 4;
    uint8_t enTapIbi = 0x1U;
    status_t result  = kStatus_Success;

    result = ICM42688P_WriteReg(handle, APEX_CONFIG0, &confData, 1);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = ICM42688P_WriteReg(handle, BANK_SEL, &bankSel, 1);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = ICM42688P_WriteReg(handle, INT_SOURCE10, &enTapIbi, 1);

    return result;
}

status_t ICM42688P_ReadSensorData(icm42688p_handle_t *handle, icm42688p_sensor_data_t *sensorData)
{
    uint8_t fifoData[16];
    status_t result = kStatus_Success;

    result = ICM42688P_ReadReg(handle, FIFO_DATA, fifoData, 16);
    if (result == kStatus_Success)
    {
        sensorData->accelDataX = (fifoData[1] << 8) | fifoData[2];
        sensorData->accelDataY = (fifoData[3] << 8) | fifoData[4];
        sensorData->accelDataZ = (fifoData[5] << 8) | fifoData[6];
        sensorData->gyroDataX  = (fifoData[7] << 8) | fifoData[8];
        sensorData->gyroDataY  = (fifoData[9] << 8) | fifoData[10];
        sensorData->gyroDataZ  = (fifoData[11] << 8) | fifoData[12];
    }

    return result;
}
