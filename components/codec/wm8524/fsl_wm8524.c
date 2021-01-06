/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wm8524.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Initializes WM8524.
 *
 * param handle WM8524 handle structure.
 * param config WM8524 configure structure.
 * return kStatus_Success.
 */
status_t WM8524_Init(wm8524_handle_t *handle, wm8524_config_t *config)
{
    assert(config != NULL);
    wm8524_config_t *wm8524Config = (wm8524_config_t *)config;

    handle->config = config;

    if ((wm8524Config->setProtocol) != NULL)
    {
        /* set format */
        WM8524_ConfigFormat(handle, wm8524Config->protocol);
    }

    /* Unmute codec */
    wm8524Config->setMute(kWM8524_Unmute);

    return kStatus_Success;
}

/*!
 * brief Configure WM8524 audio protocol.
 *
 * param handle WM8524 handle structure.
 * param protocol WM8524 configuration structure.
 */
void WM8524_ConfigFormat(wm8524_handle_t *handle, wm8524_protocol_t protocol)
{
    assert(handle->config != NULL);
    assert(handle->config->setProtocol != NULL);

    wm8524_config_t *wm8524Config = (wm8524_config_t *)handle->config;

    if (protocol != kWM8524_ProtocolRightJustified)
    {
        wm8524Config->setProtocol((uint32_t)protocol);
    }
}

/*!
 * brief Sets the codec mute state.
 *
 * param handle WM8524 handle structure.
 * param isMute true means mute, false means normal.
 */
void WM8524_SetMute(wm8524_handle_t *handle, bool isMute)
{
    assert(handle->config != NULL);
    assert(handle->config->setMute != NULL);

    wm8524_config_t *wm8524Config = (wm8524_config_t *)handle->config;

    wm8524Config->setMute(!isMute);
}
