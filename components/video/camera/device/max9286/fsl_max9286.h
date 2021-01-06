/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MAX9286_H_
#define _FSL_MAX9286_H_

#include "fsl_common.h"
#include "fsl_camera_device.h"
#include "fsl_video_i2c.h"

/*
 * Change Log:
 *
 * 1.0.2:
 *   - Bug Fixes:
 *     - Fix MISRA 2012 issues.
 *
 * 1.0.1:
 *   - Bug Fixes:
 *     - Fixed the bug that camera does not work after warm reset.
 *
 * 1.0.0:
 *   - Initial version.
 *
 */

/*
 * The MAX9286 supports 4 camera output. Currently the driver only support
 * one camera output. User could select which camera to enable by the extended
 * configuration max9286_ext_config_t. If not specified, the first valid camera
 * is used.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief MAX9286 resource.
 *
 * Before initialize the MAX9286, the resource must be initialized that the
 * Two-Wire-Serial-Interface I2C could start to work.
 *
 * The input clock must be 27MHz.
 */
typedef struct _max9286_resource
{
    video_i2c_send_func_t i2cSendFunc;       /*!< I2C send function. */
    video_i2c_receive_func_t i2cReceiveFunc; /*!< I2C receive function. */
    void (*pullPowerDownPin)(bool pullUp);   /*!< Function to pull power down pin high or low. */
} max9286_resource_t;

/*!
 * @brief MAX9286 extended configuration.
 */
typedef struct _max9286_ext_config
{
    uint8_t enableCameraMask; /*!< Select which camera to enable, there are 4 cameras. For example,
                                   use 0x01 to use camera 0, use 0x08 to use camera 3.
                                   Currently only support one camera. If multiple cameras are
                                   selected, the first available selected camera is used.
                                   */
} max9286_ext_config_t;

/*! @brief MAX9286 operation functions. */
extern const camera_device_operations_t max9286_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_MAX9286_H_ */
