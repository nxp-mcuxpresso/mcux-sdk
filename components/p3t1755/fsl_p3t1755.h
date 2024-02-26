/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_P3T1755_H_
#define _FSL_P3T1755_H_

#include "fsl_common.h"

/* Registers. */
#define P3T1755_TEMPERATURE_REG (0x00U)
#define P3T1755_CONFIG_REG      (0x01U)

/*! @brief Define sensor access function. */
typedef status_t (*sensor_write_transfer_func_t)(uint8_t deviceAddress,
                                                 uint32_t regAddress,
                                                 uint8_t *regData,
                                                 size_t dataSize);
typedef status_t (*sensor_read_transfer_func_t)(uint8_t deviceAddress,
                                                uint32_t regAddress,
                                                uint8_t *regData,
                                                size_t dataSize);

typedef struct _p3t1755_handle
{
    sensor_write_transfer_func_t writeTransfer;
    sensor_read_transfer_func_t readTransfer;
    uint8_t sensorAddress;
} p3t1755_handle_t;

typedef struct _p3t1755_config
{
    sensor_write_transfer_func_t writeTransfer;
    sensor_read_transfer_func_t readTransfer;
    uint8_t sensorAddress;
} p3t1755_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Create handle for P3T1755, reset the sensor per user configuration.
 *
 * @param p3t1755_handle The pointer to #p3t1755_handle_t.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t P3T1755_Init(p3t1755_handle_t *handle, p3t1755_config_t *config);

/*!
 * @brief Write Register with register data buffer.
 *
 * @param handle The pointer to #p3t1755_handle_t.
 * @param regAddress register address to write.
 * @param regData The pointer to data buffer to be write to the reg.
 * @param dataSize Size of the regData.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t P3T1755_WriteReg(p3t1755_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize);

/*!
 * @brief Read Register to speficied data buffer.
 *
 * @param handle The pointer to #p3t1755_handle_t.
 * @param regAddress register address to read.
 * @param regData The pointer to data buffer to store the read out data.
 * @param dataSize Size of the regData to be read.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t P3T1755_ReadReg(p3t1755_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize);

/*!
 * @brief Read temperature data.
 *
 * @param handle The pointer to #p3t1755_handle_t.
 * @param temperature The pointer to temperature data.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t P3T1755_ReadTemperature(p3t1755_handle_t *handle, double *temperature);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _FSL_P3T1755_H_ */
