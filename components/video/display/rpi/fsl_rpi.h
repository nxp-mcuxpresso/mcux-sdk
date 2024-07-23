/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RPI_H_
#define _RPI_H_

#include "fsl_display.h"
#include "fsl_mipi_dsi_cmd.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RPI_ADDR 0x45U

/*!
 * @brief RaspberryPi 7" Display resource.
 */
typedef struct _rpi_resource
{
    mipi_dsi_device_t *dsiDevice;                              /*!< MIPI DSI device. */
    status_t (*readStatus)(uint8_t regAddr, uint8_t *value);   /*!< Function to read and return register status. */
    status_t (*writeRegister)(uint8_t regAddr, uint8_t value); /*!< Function to write register value. */
} rpi_resource_t;

extern const display_operations_t rpi_ops;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t RPI_Init(display_handle_t *handle, const display_config_t *config);

status_t RPI_Deinit(display_handle_t *handle);

status_t RPI_Start(display_handle_t *handle);

status_t RPI_Stop(display_handle_t *handle);

#if defined(__cplusplus)
}
#endif

#endif /* _RPI_H_ */
