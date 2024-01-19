/*
 * Copyright  2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SX1502_H_
#define _FSL_SX1502_H_

#include "fsl_common.h"
#include "fsl_adapter_i2c.h"

/*!
 * @addtogroup SX1502
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*! @{ */
/*! @brief SX1502 driver version 2.0.0. */
#define FSL_SX1502_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

/*! @brief SX1502 handle size */
#ifndef SX1502_I2C_HANDLER_SIZE
#define SX1502_I2C_HANDLER_SIZE HAL_I2C_MASTER_HANDLE_SIZE
#endif

/*! @brief SX1502 register map*/
#define SX1502_REGDATA            (0x00U)
#define SX1502_REGDIR             (0x01U)
#define SX1502_REGPULLUP          (0x02U)
#define SX1502_REGPULLDOWN        (0x03U)
#define SX1502_REGINTERRUPTMASK   (0x05U)
#define SX1502_REGSENSEHIGH       (0x06U)
#define SX1502_REGSENSELOW        (0x07U)
#define SX1502_REGINTERRUPTSOURCE (0x08U)
#define SX1502_REGEVENTSTATUS     (0x09U)
#define SX1502_REGPLDMODE         (0x10U)
#define SX1502_REGPLDTABLE0       (0x11U)
#define SX1502_REGPLDTABLE1       (0x12U)
#define SX1502_REGPLDTABLE2       (0x13U)
#define SX1502_REGPLDTABLE3       (0x14U)
#define SX1502_REGPLDTABLE4       (0x15U)
#define SX1502_REGADVANCED        (0xABU)

/*! @brief SX1502 I2C address. */
#define SX1502_I2C_ADDRESS (0x20U)

/*! @brief SX1502 I2C bit rate. */
#define SX1502_I2C_BITRATE (400000U)

/*! @brief SX1502 IO output status.*/
typedef enum _sx1502_io_status
{
    kSX1502_IO_Low  = 0x0, /*!< Output low */
    kSX1502_IO_High = 0x1, /*!< Output high */
} sx1502_io_status_t;

/*! @brief SX1502 IO direction.*/
typedef enum _sx1502_io_dir
{
    kSX1502_IO_Output = 0, /*!< Output */
    kSX1502_IO_Input  = 1, /*!< Input */
} sx1502_io_dir_t;

/*! @brief SX1502 IO index.*/
typedef enum _sx1502_io_index
{
    kSX1502_IO0    = 0x01U, /*!< IO_0 */
    kSX1502_IO1    = 0x02U, /*!< IO_1 */
    kSX1502_IO2    = 0x04U, /*!< IO_2 */
    kSX1502_IO3    = 0x08U, /*!< IO_3 */
    kSX1502_IO4    = 0x10U, /*!< IO_4 */
    kSX1502_IO5    = 0x20U, /*!< IO_5 */
    kSX1502_IO6    = 0x40U, /*!< IO_6 */
    kSX1502_IO7    = 0x80U, /*!< IO_7 */
    kSX1502_IO_All = 0xFFU, /*!< IO_All */
} sx1502_io_index_t;

/*! @brief Configuration structure of SX1502.*/
typedef struct _sx1502_config
{
    uint8_t initRegDataValue;      /*!< RegData register init value */
    uint8_t initRegDirValue;       /*!< RegDir register init value */
    uint32_t sx1502I2CInstance;    /*!< i2c bus instance */
    uint32_t sx1502I2CSourceClock; /*!< i2c bus source clock frequency */
} sx1502_config_t;

/*! @brief SX1502 handler
 */
typedef struct _sx1502_handle
{
    uint8_t slaveAddress;                       /*!< code device slave address */
    uint8_t i2cHandle[SX1502_I2C_HANDLER_SIZE]; /*!< i2c handle */
} sx1502_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief SX1502 write register.
 *
 * @param handle SX1502 handle structure.
 * @param reg register address.
 * @param value value to write.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_WriteRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t value);

/*!
 * @brief SX1502 read register.
 *
 * @param handle SX1502 handle structure.
 * @param reg register address.
 * @param value value to read.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_ReadRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t *value);

/*!
 * @brief SX1502 modify register.
 *
 * @param handle SX1502 handle structure.
 * @param reg register address.
 * @param mask register bits mask.
 * @param value value to write.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_ModifyRegister(sx1502_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t value);

/*!
 * @brief Initializes SX1502.
 *
 * @param handle SX1502 handle structure.
 * @param sx1502Config SX1502 configuration structure.
 */
status_t SX1502_Init(sx1502_handle_t *handle, const sx1502_config_t *sx1502Config);

/*!
 * @brief Deinitializes the SX1502 codec.
 *
 * This function resets SX1502.
 *
 * @param handle SX1502 handle structure.
 *
 * @return kStatus_Success if successful, different code otherwise.
 */
status_t SX1502_Deinit(sx1502_handle_t *handle);

/*!
 * @brief SX1502 IO Set.
 *
 * @param handle SX1502 handle structure.
 * @param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * eg.Set IO1~IO3,ioMask is kSX1502_IO1|kSX1502_IO2|kSX1502_IO3.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_IO_Set(sx1502_handle_t *handle, uint8_t ioMask);

/*!
 * @brief SX1502 IO Clear.
 *
 * @param handle SX1502 handle structure.
 * @param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or-operation.
 * eg.Clear IO1~IO3,ioMask is kSX1502_IO1|kSX1502_IO2|kSX1502_IO3.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_IO_Clear(sx1502_handle_t *handle, uint8_t ioMask);

/*!
 * @brief SX1502 IO Direction to input or output.
 *
 * This API is used to set the direction of any IO combination.For example,set the direction of IO0~IO3 as output.
 * SX1502_IO_SetDirection(handle, kSX1502_IO0|kSX1502_IO1|kSX1502_IO2|kSX1502_IO3, kSX1502_IO_Output);
 *
 * @param handle SX1502 handle structure.
 * @param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or-operation.
 * @param ioDirection set IO direction to input or output.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_IO_SetDirection(sx1502_handle_t *handle, uint8_t ioMask, sx1502_io_dir_t ioDirection);

/*!
 * @brief SX1502 IO output status in a pattern.
 *
 * This API is used to set any IO combination and output in any pattern.
 * For example,set IO0~IO3 as output and iopattern as 0101,iopattern is 0x05U.
 * SX1502_IO_OutputControl(handle, kSX1502_IO0|kSX1502_IO1|kSX1502_IO2|kSX1502_IO3, 0x05U);
 *
 * @param handle SX1502 handle structure.
 * @param ioMask bits to be set,it can be a single IO or multiple IO,control multiple IO with or operation.
 * @param ioPattern ioPattern is the pattern of IO status to set.0-output low,1-output high.
 * @return kStatus_Success, else failed.
 */
status_t SX1502_IO_OutputControl(sx1502_handle_t *handle, uint8_t ioMask, uint8_t ioPattern);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_SX1502_H_ */
