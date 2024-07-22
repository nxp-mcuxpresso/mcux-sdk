/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FT6X06_H_
#define _FSL_FT6X06_H_

#include "fsl_common.h"

/*!
 * @addtogroup ft6x06
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef FT6X06_USE_CMSIS_DRIVER
#define FT6X06_USE_CMSIS_DRIVER 1
#endif

#if (FT6X06_USE_CMSIS_DRIVER)
#include "Driver_I2C.h"
#endif

/*! @brief FT6X06 I2C address. */
#define FT6X06_I2C_ADDRESS (0x38)

/*! @brief FT6X06 maximum number of simultaneously detected touches. */
#define FT6X06_MAX_TOUCHES (2U)

/*! @brief FT6X06 register address where touch data begin. */
#define F6X06_TOUCH_DATA_SUBADDR (1)

/*! @brief FT6X06 raw touch data length. */
#define FT6X06_TOUCH_DATA_LEN (2 + (FT6X06_MAX_TOUCHES) * 6)

#if (!FT6X06_USE_CMSIS_DRIVER)
typedef status_t (*ft6x06_i2c_send_func_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
typedef status_t (*ft6x06_i2c_receive_func_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

typedef struct _ft6x06_config
{
    ft6x06_i2c_send_func_t I2C_SendFunc;
    ft6x06_i2c_receive_func_t I2C_ReceiveFunc;
} ft6x06_config_t;
#endif

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
    uint8_t TOUCH_ID; /*!< Id of the touch point. This numeric value stays constant between down and up event. */
    uint16_t TOUCH_X; /*!< X coordinate of the touch point */
    uint16_t TOUCH_Y; /*!< Y coordinate of the touch point */
} touch_point_t;

/*! @brief FT6X06 driver handle. */
typedef struct _ft6x06_handle
{
#if FT6X06_USE_CMSIS_DRIVER
    ARM_DRIVER_I2C *i2c_driver;
    volatile uint32_t i2c_event;
    volatile bool i2c_event_received;
#else
    ft6x06_i2c_send_func_t I2C_SendFunc;
    ft6x06_i2c_receive_func_t I2C_ReceiveFunc;
#endif
    uint8_t touch_buf[FT6X06_TOUCH_DATA_LEN];
} ft6x06_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#if FT6X06_USE_CMSIS_DRIVER
/*!
 * @brief Initialize the driver.
 *
 * This function power on the touch controller, releases the touch controller
 * reset. After calling this function, the touch controller is ready to work.
 *
 * @param [in] handle Pointer to the driver.
 * @param [in] i2c_driver Pointer to the CMSIS I2C driver used by FT6X06.
 * @return Returns @ref kStatus_Success if initialize success, otherwise return error code.
 */
status_t FT6X06_Init(ft6x06_handle_t *handle, ARM_DRIVER_I2C *i2c_driver);
#else
status_t FT6X06_Init(ft6x06_handle_t *handle, const ft6x06_config_t *config);
#endif /* FT6X06_USE_CMSIS_DRIVER */

/*!
 * @brief De-initialize the driver.
 *
 * After this function, the touch controller is powered off.
 *
 * @param [in] handle Pointer to the driver.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT6X06_Denit(ft6x06_handle_t *handle);

#if FT6X06_USE_CMSIS_DRIVER
/*!
 * @brief Event Handler
 *
 * Called in CMSIS I2C event handler to notify the event.
 *
 * @param [in] handle Pointer to the driver.
 * @param [in] i2c_event The event passed by CMSIS I2C signal function ARM_I2C_SignalEvent_t
 */
void FT6X06_EventHandler(ft6x06_handle_t *handle, uint32_t i2c_event);
#endif /* FT6X06_USE_CMSIS_DRIVER */

/*!
 * @brief Get single touch point coordinate.
 *
 * Get one touch point coordinate.
 *
 * @param [in] handle Pointer to the driver.
 * @param [out] touch_event Touch Event.
 * @param [out] touch_x X coordinate of the touch point.
 * @param [out] touch_y Y coordinate of the touch point.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT6X06_GetSingleTouch(ft6x06_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y);

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
status_t FT6X06_GetMultiTouch(ft6x06_handle_t *handle, int *touch_count, touch_point_t touch_array[FT6X06_MAX_TOUCHES]);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
