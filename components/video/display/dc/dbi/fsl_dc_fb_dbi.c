/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_dbi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsDbi = {
    .init                  = DC_FB_DBI_Init,
    .deinit                = DC_FB_DBI_Deinit,
    .enableLayer           = DC_FB_DBI_EnableLayer,
    .disableLayer          = DC_FB_DBI_DisableLayer,
    .setLayerConfig        = DC_FB_DBI_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_DBI_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_DBI_SetFrameBuffer,
    .getProperty           = DC_FB_DBI_GetProperty,
    .setCallback           = DC_FB_DBI_SetCallback,
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DC_FB_DBI_FrameDoneCallback(status_t status, void *userData)
{
    dc_fb_dbi_handle_t *dcDbiHandle;

    dcDbiHandle = (dc_fb_dbi_handle_t *)userData;

    /* Frame buffer data has been sent to the panel, the frame buffer is free
     * to be used for set new data, call the callback to notify upper layer.
     * The callback is set in application or fbdev.
     */
    dcDbiHandle->callback(dcDbiHandle->cbParam, (void *)dcDbiHandle->frameBuffer);
}

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t DC_FB_DBI_Init(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;

    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;

    if (0U == dcDbiHandle->initTimes++)
    {
        /* Initialize the panel. */
        DBI_IFACE_SetMemoryDoneCallback(dcDbiHandle->dbiIface, DC_FB_DBI_FrameDoneCallback, dcDbiHandle);
    }

    return status;
}

status_t DC_FB_DBI_Deinit(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;

    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;

    if (dcDbiHandle->initTimes > 0U)
    {
        if (--dcDbiHandle->initTimes == 0U)
        {
            status = DBI_IFACE_SetDiplayOn(dcDbiHandle->dbiIface, false);
        }
    }

    return status;
}

status_t DC_FB_DBI_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;
    return DBI_IFACE_SetDiplayOn(dcDbiHandle->dbiIface, true);
}

status_t DC_FB_DBI_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;
    return DBI_IFACE_SetDiplayOn(dcDbiHandle->dbiIface, false);
}

status_t DC_FB_DBI_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;

    dcDbiHandle->fbInfo = *fbInfo;

    return DBI_IFACE_SelectArea(dcDbiHandle->dbiIface, fbInfo->startX, fbInfo->startY,
                                fbInfo->startX + fbInfo->width - 1U, fbInfo->startY + fbInfo->height - 1U);
}

status_t DC_FB_DBI_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = dcDbiHandle->width;
    fbInfo->height      = dcDbiHandle->height;
    fbInfo->strideBytes = dcDbiHandle->width * VIDEO_GetPixelSizeBits(dcDbiHandle->pixelFormat) / 8U;
    fbInfo->pixelFormat = dcDbiHandle->pixelFormat;

    return kStatus_Success;
}

status_t DC_FB_DBI_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    status_t status;

    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;
    dc_fb_info_t *fbInfo;
    dcDbiHandle->frameBuffer = frameBuffer;

    if (dcDbiHandle->useTEPin)
    {
        /* Save to send at TE. */
        dcDbiHandle->fbWaitTE = true;
        status                = kStatus_Success;
    }
    else
    {
        fbInfo = &dcDbiHandle->fbInfo;
        status = DBI_IFACE_WriteMemory(dcDbiHandle->dbiIface, (const uint8_t *)frameBuffer,
                                       (uint32_t)fbInfo->strideBytes * (uint32_t)fbInfo->height);
    }

    return status;
}

uint32_t DC_FB_DBI_GetProperty(const dc_fb_t *dc)
{
    return 0U;
}

void DC_FB_DBI_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;

    dcDbiHandle->callback = callback;
    dcDbiHandle->cbParam  = param;
}

void DC_FB_DBI_TE_IRQHandler(const dc_fb_t *dc)
{
    dc_fb_dbi_handle_t *dcDbiHandle = (dc_fb_dbi_handle_t *)dc->prvData;
    dc_fb_info_t *fbInfo            = &dcDbiHandle->fbInfo;

    if (dcDbiHandle->fbWaitTE)
    {
        dcDbiHandle->fbWaitTE = false;
        (void)DBI_IFACE_WriteMemory(dcDbiHandle->dbiIface, (const uint8_t *)dcDbiHandle->frameBuffer,
                              (uint32_t)fbInfo->strideBytes * (uint32_t)fbInfo->height);
    }
}
