/*
 * Copyright (c) 2019-2020, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RM67162_H_
#define _FSL_RM67162_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*
 * Change Log:
 *
 * 1.0.2:
 *   - Bug Fixes
 *     - Fix MISRA 2012 issues.
 *
 * 1.0.1:
 *   - Improvements
 *     - Support resolution 400x392.
 *
 * 1.0.0:
 *   - Initial version.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief RM67162 resource.
 */
typedef struct _rm67162_resource
{
    mipi_dsi_device_t *dsiDevice;      /*!< MIPI DSI device. */
    void (*pullResetPin)(bool pullUp); /*!< Function to pull reset pin high or low. */
    void (*pullPowerPin)(bool pullUp); /*!< Function to pull power pin high or low. */
} rm67162_resource_t;

extern const display_operations_t rm67162_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t RM67162_Init(display_handle_t *handle, const display_config_t *config);

status_t RM67162_Deinit(display_handle_t *handle);

status_t RM67162_Start(display_handle_t *handle);

status_t RM67162_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_RM67162_H_ */
