/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_display.h"
#include "fsl_rpi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RPI_DelayMs    VIDEO_DelayMs
#define RPI_PWRON_ADDR 0x85U
#define RPI_PORTB_ADDR 0x82U
#define RPI_PWM_ADDR   0x86U
/*******************************************************************************
 * Variables
 ******************************************************************************/
const display_operations_t rpi_ops = {
    .init   = RPI_Init,
    .deinit = RPI_Deinit,
    .start  = RPI_Start,
    .stop   = RPI_Stop,
};

static const uint8_t s_rpiCmds[11][6] = {
    {0x10U, 0x02U, 0x03U, 0x00U, 0x00U, 0x00U}, {0x64U, 0x01U, 0x05U, 0x00U, 0x00U, 0x00U},
    {0x68U, 0x01U, 0x05U, 0x00U, 0x00U, 0x00U}, {0x44U, 0x01U, 0x00U, 0x00U, 0x00U, 0x00U},
    {0x48U, 0x01U, 0x00U, 0x00U, 0x00U, 0x00U}, {0x14U, 0x01U, 0x03U, 0x00U, 0x00U, 0x00U},
    {0x50U, 0x04U, 0x00U, 0x00U, 0x00U, 0x00U}, {0x20U, 0x04U, 0x50U, 0x01U, 0x10U, 0x00U},
    {0x64U, 0x04U, 0x0fU, 0x04U, 0x00U, 0x00U}, {0x04U, 0x01U, 0x01U, 0x00U, 0x00U, 0x00U},
    {0x04U, 0x02U, 0x01U, 0x00U, 0x00U, 0x00U}};
/*******************************************************************************
 * Code
 ******************************************************************************/

status_t RPI_Init(display_handle_t *handle, const display_config_t *config)
{
    status_t status                = kStatus_Success;
    const rpi_resource_t *resource = (const rpi_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice   = resource->dsiDevice;
    uint8_t regVal                 = 0U;

    /* Only support one set of resolution. */
    if (config->resolution != FSL_VIDEO_RESOLUTION(800, 480))
    {
        return kStatus_InvalidArgument;
    }

    /* Reset panel. */
    if (resource->writeRegister(RPI_PWRON_ADDR, 0x0U) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    VIDEO_DelayMs(400);
    if (resource->writeRegister(RPI_PWRON_ADDR, 0x1U) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    VIDEO_DelayMs(400);

    /* Wait for power on done. */
    while ((regVal & 0x1U) == 0U)
    {
        if (resource->readStatus(RPI_PORTB_ADDR, &regVal) != kStatus_Success)
        {
            return kStatus_Fail;
        }
    }

    /* Set backlight. */
    if (resource->writeRegister(RPI_PWM_ADDR, 0x80U) != kStatus_Success)
    {
        return kStatus_Fail;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(s_rpiCmds); i++)
    {
        status = MIPI_DSI_GenericWrite(dsiDevice, s_rpiCmds[i], 6);

        if (kStatus_Success != status)
        {
            break;
        }

        if ((i == 8U) || (i == 10U))
        {
            RPI_DelayMs(100);
        }
    }

    return status;
}

status_t RPI_Deinit(display_handle_t *handle)
{
    const rpi_resource_t *resource = (const rpi_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice   = resource->dsiDevice;

    (void)MIPI_DSI_DCS_EnterSleepMode(dsiDevice, true);

    return kStatus_Success;
}

status_t RPI_Start(display_handle_t *handle)
{
    const rpi_resource_t *resource = (const rpi_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice   = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, true);
}

status_t RPI_Stop(display_handle_t *handle)
{
    const rpi_resource_t *resource = (const rpi_resource_t *)(handle->resource);
    mipi_dsi_device_t *dsiDevice   = resource->dsiDevice;

    return MIPI_DSI_DCS_SetDisplayOn(dsiDevice, false);
}
