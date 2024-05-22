/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_p3t1755.h"

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
status_t P3T1755_WriteReg(p3t1755_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
    status_t result;
    result = handle->writeTransfer(handle->sensorAddress, regAddress, regData, dataSize);

    return (result == kStatus_Success) ? result : kStatus_Fail;
}

status_t P3T1755_ReadReg(p3t1755_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize)
{
    status_t result;
    result = handle->readTransfer(handle->sensorAddress, regAddress, regData, dataSize);

    return (result == kStatus_Success) ? result : kStatus_Fail;
}

status_t P3T1755_Init(p3t1755_handle_t *handle, p3t1755_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);
    assert(config->writeTransfer != NULL);
    assert(config->readTransfer != NULL);

    handle->writeTransfer = config->writeTransfer;
    handle->readTransfer  = config->readTransfer;
    handle->sensorAddress = config->sensorAddress;

    return kStatus_Success;
}

status_t P3T1755_ReadTemperature(p3t1755_handle_t *handle, double *temperature)
{
    status_t result = kStatus_Success;
    uint8_t data[2];

    result = P3T1755_ReadReg(handle, P3T1755_TEMPERATURE_REG, &data[0], 2);
    if (result == kStatus_Success)
    {
        *temperature = (double)((((uint16_t)data[0] << 8U) | (uint16_t)data[1]) >> 4U);
        *temperature = *temperature * 0.0625;
    }

    return result;
}
