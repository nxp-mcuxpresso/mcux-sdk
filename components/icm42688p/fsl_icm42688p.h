/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ICM42688P_H_
#define _FSL_ICM42688P_H_

#include "fsl_common.h"

#define INVALID_DATA (-32768)

/* Locate in bank 0. */
#define DEVICE_CONFIG      0x11U
#define INT_CONFIG         0x14U
#define TEMP_DATA1         0x1DU
#define TEMP_DATA0         0x1EU
#define PWR_MGMT0          0x4EU
#define GYRO_CONFIG0       0x4FU
#define ACCEL_CONFIG0      0x50U
#define GYRO_CONFIG1       0x51U
#define GYRO_ACCEL_CONFIG0 0x52U
#define ACCEL_CONFIG1      0x53U
#define WHO_AM_I           0x75U
#define WHO_AM_I_VALUE     0x47U
#define BANK_SEL           0x76U

#define ACCEL_DATA_X1 0x1FU
#define ACCEL_DATA_X0 0x20U

#define ACCEL_DATA_Y1 0x21U
#define ACCEL_DATA_Y0 0x22U

#define ACCEL_DATA_Z1 0x23U
#define ACCEL_DATA_Z0 0x24U

#define GYRO_DATA_X1 0x25U
#define GYRO_DATA_X0 0x26U

#define GYRO_DATA_Y1 0x27U
#define GYRO_DATA_Y0 0x28U

#define GYRO_DATA_Z1 0x29U
#define GYRO_DATA_Z0 0x2AU

#define FIFO_CONFIG  0x16U
#define FIFO_CONFIG1 0x5FU
#define FIFO_DATA    0x30U
#define APEX_CONFIG0 0x56U

/* Locate in bank 4. */
#define INT_SOURCE10 0x51U

/*! @brief Define sensor access function. */
typedef status_t (*sensor_write_transfer_func_t)(uint8_t deviceAddress,
                                                 uint32_t regAddress,
                                                 uint8_t *regData,
                                                 size_t dataSize);
typedef status_t (*sensor_read_transfer_func_t)(uint8_t deviceAddress,
                                                uint32_t regAddress,
                                                uint8_t *regData,
                                                size_t dataSize);

typedef struct _icm42688p_sensor_data
{
    int16_t accelDataX;
    int16_t accelDataY;
    int16_t accelDataZ;
    int16_t gyroDataX;
    int16_t gyroDataY;
    int16_t gyroDataZ;
} icm42688p_sensor_data_t;

typedef struct _icm42688p_handle
{
    sensor_write_transfer_func_t Sensor_WriteTransfer;
    sensor_read_transfer_func_t Sensor_ReadTransfer;
    uint8_t sensorAddress;
} icm42688p_handle_t;

typedef struct _icm42688p_config
{
    sensor_write_transfer_func_t Sensor_WriteTransfer;
    sensor_read_transfer_func_t Sensor_ReadTransfer;
    uint8_t sensorAddress;
    bool isReset;
} icm42688p_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Create handle for ICM42688P, reset the sensor per user configuration.
 *
 * @param icm42688p_handle The pointer to #icm42688p_handle_t.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t ICM42688P_Init(icm42688p_handle_t *handle, icm42688p_config_t *config);

/*!
 * @brief Write Register with register data buffer.
 *
 * @param handle The pointer to #icm42688p_handle_t.
 * @param regAddress register address to write.
 * @param regData The pointer to data buffer to be write to the reg.
 * @param dataSize Size of the regData.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t ICM42688P_WriteReg(icm42688p_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize);

/*!
 * @brief Read Register to speficied data buffer.
 *
 * @param handle The pointer to #icm42688p_handle_t.
 * @param regAddress register address to read.
 * @param regData The pointer to data buffer to store the read out data.
 * @param dataSize Size of the regData to be read.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t ICM42688P_ReadReg(icm42688p_handle_t *handle, uint32_t regAddress, uint8_t *regData, size_t dataSize);

/*!
 * @brief Enable ACCEL and GYRO sensors.
 *
 * @param handle The pointer to #icm42688p_handle_t.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t ICM42688P_EnableSensors(icm42688p_handle_t *handle);

/*!
 * @brief Configure ICM42688P sensor to generate TAP detect IBI.
 *
 * @param handle The pointer to #icm42688p_handle_t.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t ICM42688P_ConfigureTapDetectIBI(icm42688p_handle_t *handle);

/*!
 * @brief Read sensor data from fifo.
 *
 * @param handle The pointer to #icm42688p_handle_t.
 * @param icm42688p_sensor_data_t The pointer to #icm42688p_sensor_data_t which stores the read out data.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 * @return kStatus_NoData There's invalid data in sensorData structure.
 */
status_t ICM42688P_ReadSensorData(icm42688p_handle_t *handle, icm42688p_sensor_data_t *sensorData);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _FSL_ICM42688P_H_ */
