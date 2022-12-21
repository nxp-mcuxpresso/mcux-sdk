/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FXLS_H_
#define _FSL_FXLS_H_

#include "fsl_common.h"

#define FXLS8974CF_ACCEL_RESOLUTION_BITS 12

/*
 *  STATUS Register
 */
#define INT_STATUS_REG 0x00

/*
 *  TEMPERATURE Value Register
 */
#define TEMP_OUT_REG 0x01

/*
 *  VECTOR Magnitude Result Registers
 */
#define VECM_LSB_REG 0x02
#define VECM_MSB_REG 0x03

/*
 *  XYZ Data Registers
 */
#define OUT_X_LSB_REG 0x04
#define OUT_X_MSB_REG 0x05
#define OUT_Y_LSB_REG 0x06
#define OUT_Y_MSB_REG 0x07
#define OUT_Z_LSB_REG 0x08
#define OUT_Z_MSB_REG 0x09

/*
 *  XYZ Data Buffer Status Register
 */
#define BUF_STATUS_REG 0x0B

/*
 *  XYZ Sample Data Registers
 */
#define BUF_X_LSB_REG 0x0C
#define BUF_X_MSB_REG 0x0D
#define BUF_Y_LSB_REG 0x0E
#define BUF_Y_MSB_REG 0x0F
#define BUF_Z_LSB_REG 0x10
#define BUF_Z_MSB_REG 0x11

/*
 *  PRODUCT Revision Number Register
 */
#define PROD_REV_REG 0x12

/*
 *  WHO_AM_I Device ID Register
 */
#define WHO_AM_I_REG 0x13
/* Content */
#define kFXLS_WHO_AM_I_Device_ID 0x86U

/*
 *  CURRENT Device Operating Mode Register
 */
#define SYS_MODE_REG 0x14

/*
 *  CONFIG Registers
 */
#define SENS_CONFIG1_REG 0x15U
/* Content */
#define ACTIVE_MASK 0x01U

#define SENS_CONFIG2_REG 0x16

#define SENS_CONFIG3_REG 0x17

#define SENS_CONFIG4_REG 0x18

#define SENS_CONFIG5_REG 0x19

/*
 *  MODE Registers
 */
#define WAKE_IDLE_LSB_REG  0x1A
#define WAKE_IDLE_MSB_REG  0x1B
#define SLEEP_IDLE_LSB_REG 0x1C
#define SLEEP_IDLE_MSB_REG 0x1D
#define ASLP_COUNT_LSB_REG 0x1E
#define ASLP_COUNT_MSB_REG 0x1F

/*
 *  INTERRUPT Registers
 */
#define INT_EN_REG      0x20
#define INT_PIN_SEL_REG 0x21

/* XYZ Offset Correction Registers */
#define OFF_X_REG 0x22
#define OFF_Y_REG 0x23
#define OFF_Z_REG 0x24

/* BUFFER Config Registers */
#define BUF_CONFIG1_REG 0x26
#define BUF_CONFIG2_REG 0x27

/*! @brief Define I2C access function. */
typedef status_t (*I2C_SendFunc_t)(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
typedef status_t (*I2C_ReceiveFunc_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/*! @brief fxls8974cf configure definition. This structure should be global.*/
typedef struct _fxls_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
} fxls_handle_t;

/*! @brief fxls8974cf sensor data structure. */
typedef struct _fxls_accel_raw_data
{
    uint8_t accelXLSB; /* 8-bit X-axis LSB output acceleration data. */
    uint8_t accelXMSB; /* 4-bit X-axis MSB output acceleration data. */
    uint8_t accelYLSB; /* 8-bit Y-axis LSB output acceleration data. */
    uint8_t accelYMSB; /* 4-bit Y-axis MSB output acceleration data. */
    uint8_t accelZLSB; /* 8-bit Z-axis LSB output acceleration data. */
    uint8_t accelZMSB; /* 4-bit Z-axis MSB output acceleration data. */
} fxls_accel_raw_data_t;

/*! @brief fxls8974cf synthesized accel data structure. */
typedef struct _fxls_accel_data
{
    int16_t accelX; /* Synthesized 12-bit X-axis output acceleration data. */
    int16_t accelY; /* Synthesized 12-bit Y-axis output acceleration data. */
    int16_t accelZ; /* Synthesized 12-bit Z-axis output acceleration data. */
} fxls_accel_data_t;

/*! @brief fxls8974cf configure structure.*/
typedef struct _fxls_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address. */
    uint8_t slaveAddress;
} fxls_config_t;

/*!
 * @addtogroup fxls_common
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Verify and initialize fxls_handleice
 *
 * @param fxls_handle The pointer to accel driver handle.
 * @param config The configuration structure pointer to accel.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t FXLS_Init(fxls_handle_t *fxls_handle, fxls_config_t *config);

/*!
 * @brief Read data from sensors
 *
 * @param fxls_handle The pointer to accel driver handle.
 * @param accelRawData The pointer to the buffer to hold sensor data.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t FXLS_ReadAccelRawData(fxls_handle_t *fxls_handle, fxls_accel_raw_data_t *accelRawData);

/*!
 * @brief Read data from sensors and synthesize the final accel data
 *
 * @param fxls_handle The pointer to accel driver handle.
 * @param accelData The pointer to the buffer to hold accel data.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t FXLS_ReadAccelData(fxls_handle_t *fxls_handle, fxls_accel_data_t *accelData);

/*!
 * @brief Write value to register of sensor.
 *
 * @param handle The pointer to fxls8974cf driver handle.
 * @param reg Register address.
 * @param val Data want to write.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t FXLS_WriteReg(fxls_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read n bytes start at register from sensor.
 *
 * @param handle The pointer to fxls8974cf driver handle.
 * @param reg Register address.
 * @param val The pointer to address which store data.
 * @param bytesNumber Number of bytes receiver.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t FXLS_ReadReg(fxls_handle_t *handle, uint8_t reg, uint8_t *val, uint8_t bytesNumber);

/*!
 * @brief Get device accelerator resolution bits.
 *
 * @return accelerator resolution bits.
 */
static inline uint8_t FXLS_GetResolutionBits(void)
{
    return FXLS8974CF_ACCEL_RESOLUTION_BITS;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _FSL_FXLS_H_ */
