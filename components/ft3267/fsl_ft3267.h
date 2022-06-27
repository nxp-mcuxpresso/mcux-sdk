/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FT3267_H_
#define _FSL_FT3267_H_

#include "fsl_common.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fix MISRA 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup ft3267
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief FT3267 I2C address. */
#define FT3267_I2C_ADDRESS (0x38U)

/*! @brief FT3267 maximum number of simultaneously detected touches. */
#define FT3267_MAX_TOUCHES (5U)

/*! @brief FT3267 register address where touch data begin. */
#define FT3267_TOUCH_DATA_SUBADDR (1)

/*! @brief FT3267 raw touch data length. */
#define FT3267_TOUCH_DATA_LEN (0x20)

/*! @brief FT3267 I2C receive function. */
typedef status_t (*ft3267_i2c_receive_func_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/*! @brief Function to pull reset pin up or down. */
typedef void (*ft3267_reset_pin_func_t)(bool pullUp);

/*! @brief Function to pull power pin up or down. */
typedef void (*ft3267_power_pin_func_t)(bool pullUp);

/*! @brief Touch event. */
typedef enum _touch_event
{
    kTouch_Down     = 0, /*!< The state changed to touched. */
    kTouch_Up       = 1, /*!< The state changed to not touched. */
    kTouch_Contact  = 2, /*!< There is a continuous touch being detected. */
    kTouch_Reserved = 3  /*!< No touch information available. */
} touch_event_t;

/*! @brief Touch point information. */
typedef struct _touch_point
{
    touch_event_t TOUCH_EVENT; /*!< Indicates the state or event of the touch point. */
    uint8_t TOUCH_ID; /*!< ID of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X; /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y; /*!< Y coordinate of the touch point */
} touch_point_t;

/*! @brief FT3267 configure structure.*/
typedef struct _ft3267_config
{
    ft3267_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
    ft3267_reset_pin_func_t pullResetPinFunc;  /*!< Function to pull reset pin high or low. */
    ft3267_power_pin_func_t pullPowerPinFunc;  /*!< Function to pull power pin high or low. */
    void (*timeDelayMsFunc)(uint32_t delayMs); /*!< Function to delay some MS. */
} ft3267_config_t;

/*! @brief FT3267 driver handle. */
typedef struct _ft3267_handle
{
    ft3267_i2c_receive_func_t I2C_ReceiveFunc; /*!< Function to receive I2C data. */
    ft3267_reset_pin_func_t pullResetPinFunc;  /*!< Function to pull reset pin high or low. */
    ft3267_power_pin_func_t pullPowerPinFunc;  /*!< Function to pull power pin high or low. */
    uint8_t touchBuf[FT3267_TOUCH_DATA_LEN];   /*!< Buffer to receive touch point raw data. */
} ft3267_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the driver.
 *
 * This function power on the touch controller, releases the touch controller
 * reset. After calling this function, the touch controller is ready to work.
 *
 * @param [in] handle Pointer to the driver.
 * @param [in] config Pointer to the configuration.
 * @return Returns @ref kStatus_Success if initialize success, otherwise return error code.
 */
status_t FT3267_Init(ft3267_handle_t *handle, const ft3267_config_t *config);

/*!
 * @brief De-initialize the driver.
 *
 * After this function, the touch controller is powered off.
 *
 * @param [in] handle Pointer to the driver.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT3267_Deinit(ft3267_handle_t *handle);

/*!
 * @brief Get single touch point coordinate.
 *
 * Get one touch point coordinate.
 *
 * @param [in] handle Pointer to the driver.
 * @param [out] touch_x X coordinate of the touch point.
 * @param [out] touch_y Y coordinate of the touch point.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT3267_GetSingleTouch(ft3267_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y);

/*!
 * @brief Get multiple touch points coordinate.
 *
 * When this function returns successfully, the @p touch_count shows how
 * many valid touch points there are in the @p touch_array.
 *
 * @param [in] handle Pointer to the driver.
 * @param [out] touch_count The actual touch point number.
 * @param [out] touch_array Array of touch points coordinate.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT3267_GetMultiTouch(ft3267_handle_t *handle, int *touch_count, touch_point_t touch_array[FT3267_MAX_TOUCHES]);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
