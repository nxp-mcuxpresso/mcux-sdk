/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MMA8451Q_H_
#define _FSL_MMA8451Q_H_

#include "fsl_common.h"

#define WHO_AM_I_REG                   kMMA8451_WHO_AM_I
#define MMA8451Q_ACCEL_RESOLUTION_BITS 14

/*!
 * @brief Register definitions for the MMA8451.
 */
enum _mma8451_constants
{
    kMMA8451_STATUS             = 0x00,
    kMMA8451_OUT_X_MSB          = 0x01,
    kMMA8451_OUT_X_LSB          = 0x02,
    kMMA8451_OUT_Y_MSB          = 0x03,
    kMMA8451_OUT_Y_LSB          = 0x04,
    kMMA8451_OUT_Z_MSB          = 0x05,
    kMMA8451_OUT_Z_LSB          = 0x06,
    kMMA8451_F_SETUP            = 0x09,
    kMMA8451_TRIG_CFG           = 0x0a,
    kMMA8451_SYSMOD             = 0x0b,
    kMMA8451_INT_SOURCE         = 0x0c,
    kMMA8451_WHO_AM_I           = 0x0d,
    kMMA8451_WHO_AM_I_Device_ID = 0x1a,
    kMMA8451_XYZ_DATA_CFG       = 0x0e,
    kMMA8451_CTRL_REG1          = 0x2a,
    kMMA8451_CTRL_REG2          = 0x2b,
    kMMA8451_CTRL_REG3          = 0x2c,
    kMMA8451_CTRL_REG4          = 0x2d,
    kMMA8451_CTRL_REG5          = 0x2e
};

typedef struct _mma_data
{
    uint8_t accelXMSB;
    uint8_t accelXLSB;
    uint8_t accelYMSB;
    uint8_t accelYLSB;
    uint8_t accelZMSB;
    uint8_t accelZLSB;
} mma_data_t;

/*! @brief Define I2C access function. */
typedef status_t (*I2C_SendFunc_t)(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
typedef status_t (*I2C_ReceiveFunc_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/*! @brief mma8451q configure definition. This structure should be global.*/
typedef struct _mma_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
} mma_handle_t;

/*! @brief mma8451q configure structure.*/
typedef struct _mma_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
} mma_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the MMA8451 driver instance.
 *
 * @param accel_device Device driver state structure that will be filled in by this function.
 *      It is the responsibility of the caller to provide storage for this structure, and
 *      to free that storage when the driver is no longer needed.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t MMA_Init(mma_handle_t *handle, mma_config_t *config);

/*!
 * @brief Read the current acceleration values.
 *
 * @param handle Pointer to a valid accel_device instance structure.
 * @param accel Pointer to a structure that will be filled in with the current acceleration
 *      values for all three axes.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t MMA_ReadSensorData(mma_handle_t *handle, mma_data_t *accel);

/*!
 * @brief Read the value of register in accelerometer.
 *
 * @param handle Pointer to a valid accel_device instance structure.
 * @param reg variable store address of register
 * @param val pointer store return value.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t MMA_ReadReg(mma_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Write the value to register of accelerometer.
 *
 * @param handle Pointer to a valid accel_device instance structure.
 * @param reg variable store address of register
 * @param val pointer store value which is writen to accelerometer.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t MMA_WriteReg(mma_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Get device accelerator resolution bits.
 *
 * @return accelerator resolution bits.
 */
static inline uint8_t MMA_GetResolutionBits(void)
{
    return MMA8451Q_ACCEL_RESOLUTION_BITS;
}

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_MMA8451Q_H_ */
