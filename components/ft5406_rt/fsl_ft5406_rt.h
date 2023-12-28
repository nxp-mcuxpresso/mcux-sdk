/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FT5406_RT_H_
#define _FSL_FT5406_RT_H_

#include "fsl_common.h"

/*!
 * @addtogroup ft5406_rt
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief FT5406_RT I2C address. */
#define FT5406_RT_I2C_ADDRESS (0x38)

/*! @brief FT5406_RT maximum number of simultaneously detected touches. */
#define FT5406_RT_MAX_TOUCHES (5U)

/*! @brief FT5406_RT register address where touch data begin. */
#define FT5406_RT_TOUCH_DATA_SUBADDR (1)

/*! @brief FT5406_RT raw touch data length. */
#define FT5406_RT_TOUCH_DATA_LEN (0x20)

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

/*! @brief Driver handle. */
typedef struct _ft5406_rt_handle
{
    LPI2C_Type *base;
    lpi2c_master_transfer_t xfer;
    uint8_t touch_buf[FT5406_RT_TOUCH_DATA_LEN];
} ft5406_rt_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the driver.
 *
 * @param [in] handle Pointer to the driver.
 * @param [in] base The I2C used by FT5406.
 * @return Returns @ref kStatus_Success if initialize success, otherwise return error code.
 */
status_t FT5406_RT_Init(ft5406_rt_handle_t *handle, LPI2C_Type *base);

/*!
 * @brief De-initialize the driver.
 *
 * @param [in] handle Pointer to the driver.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT5406_RT_Denit(ft5406_rt_handle_t *handle);

/*!
 * @brief Get single touch point coordinate.
 *
 * Get one touch point coordinate.
 *
 * @param [in] handle Pointer to the driver.
 * @param [out] touch_event Touch event.
 * @param [out] touch_x X coordinate of the touch point.
 * @param [out] touch_y Y coordinate of the touch point.
 * @return Returns @ref kStatus_Success if success, otherwise return error code.
 */
status_t FT5406_RT_GetSingleTouch(ft5406_rt_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y);

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
status_t FT5406_RT_GetMultiTouch(ft5406_rt_handle_t *handle,
                                 int *touch_count,
                                 touch_point_t touch_array[FT5406_RT_MAX_TOUCHES]);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
