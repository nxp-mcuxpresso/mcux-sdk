/*
 * Copyright 2021-2022 NXP
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
        uint8_t resetVal = 0x01U;
        uint8_t bankSel  = 0;

        result = ICM42688P_WriteReg(handle, BANK_SEL, &bankSel, 1U);
        if (result != kStatus_Success)
        {
            return result;
        }
        result = ICM42688P_WriteReg(handle, DEVICE_CONFIG, &resetVal, 1U);
        if (result != kStatus_Success)
        {
            return result;
        }
        SDK_DelayAtLeastUs(1000, SystemCoreClock);
    }

    return result;
}

status_t ICM42688P_EnableSensors(icm42688p_handle_t *handle)
{
    uint8_t sensorConfig = 0x1FU;
    uint8_t fifoConfData = 0x03U;
    uint8_t fifoInitVal  = 0x40U;
    uint8_t whoamiVal    = 0;
    status_t result      = kStatus_Success;

    result = ICM42688P_ReadReg(handle, WHO_AM_I, &whoamiVal, 1U);
    if (result != kStatus_Success)
    {
        return result;
    }
    assert(whoamiVal == WHO_AM_I_VALUE);

    result = ICM42688P_WriteReg(handle, PWR_MGMT0, &sensorConfig, 1U);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = ICM42688P_WriteReg(handle, FIFO_CONFIG, &fifoInitVal, 1U);
    if (result != kStatus_Success)
    {
        return result;
    }

    return ICM42688P_WriteReg(handle, FIFO_CONFIG1, &fifoConfData, 1U);
}

status_t ICM42688P_ConfigureTapDetectIBI(icm42688p_handle_t *handle)
{
    uint8_t confData = 0x40U;
    uint8_t bankSel  = 4;
    uint8_t enTapIbi = 0x1U;
    status_t result  = kStatus_Success;

    result = ICM42688P_WriteReg(handle, APEX_CONFIG0, &confData, 1U);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = ICM42688P_WriteReg(handle, BANK_SEL, &bankSel, 1U);
    if (result != kStatus_Success)
    {
        return result;
    }

    return ICM42688P_WriteReg(handle, INT_SOURCE10, &enTapIbi, 1U);
}

status_t ICM42688P_ReadSensorData(icm42688p_handle_t *handle, icm42688p_sensor_data_t *sensorData)
{
    status_t result = kStatus_Success;
    uint8_t fifoData[16];

    result = ICM42688P_ReadReg(handle, FIFO_DATA, fifoData, 16U);
    if (result == kStatus_Success)
    {
        sensorData->accelDataX = (int16_t)(uint16_t)(((uint16_t)fifoData[1] << 8U) | (uint16_t)fifoData[2]);
        sensorData->accelDataY = (int16_t)(uint16_t)(((uint16_t)fifoData[3] << 8U) | (uint16_t)fifoData[4]);
        sensorData->accelDataZ = (int16_t)(uint16_t)(((uint16_t)fifoData[5] << 8U) | (uint16_t)fifoData[6]);
        sensorData->gyroDataX  = (int16_t)(uint16_t)(((uint16_t)fifoData[7] << 8U) | (uint16_t)fifoData[8]);
        sensorData->gyroDataY  = (int16_t)(uint16_t)(((uint16_t)fifoData[9] << 8U) | (uint16_t)fifoData[10]);
        sensorData->gyroDataZ  = (int16_t)(uint16_t)(((uint16_t)fifoData[11] << 8U) | (uint16_t)fifoData[12]);
    }

    if ((sensorData->accelDataX == INVALID_DATA) || (sensorData->gyroDataX == INVALID_DATA))
    {
        result = kStatus_NoData;
    }

    return result;
}
