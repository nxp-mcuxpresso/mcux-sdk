/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_IT6263_H_
#define _FSL_IT6263_H_

#include "fsl_common.h"
#include "fsl_video_i2c.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fix MISRA-C 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief IT6263 resource.
 *
 * The I2C instance should be initialized before calling @ref IT6263_Init.
 */
typedef struct _it6263_resource
{
    video_i2c_send_func_t i2cSendFunc;       /* I2C send function. */
    video_i2c_receive_func_t i2cReceiveFunc; /* I2C receive function. */
    void (*pullResetPin)(bool pullUp);       /* Function to pull reset pin high or low. */
    uint8_t i2cAddr;                         /* I2C address, 0x98 or 0x9A. */
} it6263_resource_t;

extern const display_operations_t it6263_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t IT6263_Init(display_handle_t *handle, const display_config_t *config);

status_t IT6263_Deinit(display_handle_t *handle);

status_t IT6263_Start(display_handle_t *handle);

status_t IT6263_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_IT6263_H_ */
