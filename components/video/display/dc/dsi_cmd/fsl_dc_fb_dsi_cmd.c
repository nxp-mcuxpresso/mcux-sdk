/*
 * Copyright (c) 2019-2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_dsi_cmd.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsDsiCmd = {
    .init                  = DC_FB_DSI_CMD_Init,
    .deinit                = DC_FB_DSI_CMD_Deinit,
    .enableLayer           = DC_FB_DSI_CMD_EnableLayer,
    .disableLayer          = DC_FB_DSI_CMD_DisableLayer,
    .setLayerConfig        = DC_FB_DSI_CMD_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_DSI_CMD_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_DSI_CMD_SetFrameBuffer,
    .getProperty           = DC_FB_DSI_CMD_GetProperty,
    .setCallback           = DC_FB_DSI_CMD_SetCallback,
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DC_FB_DSI_CMD_FrameDoneCallback(status_t status, void *userData)
{
    dc_fb_dsi_cmd_handle_t *dcHandle;
    dc_fb_dsi_cmd_layer_t *layer;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)userData;

    /* Currently only support one layer, so the layer index is always 0. */
    layer = &(dcHandle->layers[0]);

    /* Frame buffer data has been sent to the panel, the frame buffer is free
     * to be used for set new data, call the callback to notify upper layer.
     * The callback is set in application or fbdev.
     */
    layer->callback(layer->cbParam, layer->frameBuffer);
}

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t DC_FB_DSI_CMD_Init(const dc_fb_t *dc)
{
    status_t status;

    const dc_fb_dsi_cmd_config_t *dcConfig;
    dc_fb_dsi_cmd_handle_t *dcHandle;
    display_handle_t *panelHandle;
    mipi_dsi_device_t *dsiDevice;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)dc->prvData;

    if (0U == dcHandle->initTimes++)
    {
        panelHandle = (display_handle_t *)(dcHandle->panelHandle);
        dcConfig    = (const dc_fb_dsi_cmd_config_t *)(dc->config);
        dsiDevice   = dcHandle->dsiDevice;

        dcHandle->useTEPin = dcConfig->useTEPin;

        status = DISPLAY_Init(panelHandle, &dcConfig->commonConfig);

        if (kStatus_Success != status)
        {
            return status;
        }

        MIPI_DSI_SetMemoryDoneCallback(dsiDevice, DC_FB_DSI_CMD_FrameDoneCallback, dcHandle);
    }

    return kStatus_Success;
}

status_t DC_FB_DSI_CMD_Deinit(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;

    dc_fb_dsi_cmd_handle_t *dcHandle;
    display_handle_t *panelHandle;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)dc->prvData;

    if (dcHandle->initTimes > 0U)
    {
        if (--dcHandle->initTimes == 0U)
        {
            panelHandle = (display_handle_t *)(dcHandle->panelHandle);
            status      = DISPLAY_Deinit(panelHandle);
        }
    }

    return status;
}

status_t DC_FB_DSI_CMD_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    dc_fb_dsi_cmd_handle_t *dcHandle;
    display_handle_t *panelHandle;

    status_t status = kStatus_Success;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)dc->prvData;

    if (0U == dcHandle->enabledLayerCount++)
    {
        panelHandle = (display_handle_t *)(dcHandle->panelHandle);

        status = DISPLAY_Start(panelHandle);
    }

    return status;
}

status_t DC_FB_DSI_CMD_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    dc_fb_dsi_cmd_handle_t *dcHandle;
    display_handle_t *panelHandle;

    status_t status = kStatus_Success;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)dc->prvData;

    if (dcHandle->enabledLayerCount > 0U)
    {
        if (--dcHandle->enabledLayerCount == 0U)
        {
            panelHandle = (display_handle_t *)(dcHandle->panelHandle);

            status = DISPLAY_Stop(panelHandle);
        }
    }

    return status;
}

status_t DC_FB_DSI_CMD_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_DSI_CMD_MAX_LAYER);

    dc_fb_dsi_cmd_handle_t *dcHandle = (dc_fb_dsi_cmd_handle_t *)(dc->prvData);

    /* The pixel format is already set by DSI_CMD_Init and could not be changed,
       so here don't need to set the format.
       */

    dcHandle->layers[layer].fbInfo = *fbInfo;

    return kStatus_Success;
}

status_t DC_FB_DSI_CMD_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_DSI_CMD_MAX_LAYER);

    dc_fb_dsi_cmd_handle_t *dcHandle = (dc_fb_dsi_cmd_handle_t *)(dc->prvData);
    display_handle_t *panelHandle    = (display_handle_t *)(dcHandle->panelHandle);

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = panelHandle->width;
    fbInfo->height      = panelHandle->height;
    fbInfo->strideBytes = panelHandle->width * VIDEO_GetPixelSizeBits(panelHandle->pixelFormat) / 8U;
    fbInfo->pixelFormat = panelHandle->pixelFormat;

    return kStatus_Success;
}

status_t DC_FB_DSI_CMD_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    assert(layer < DC_FB_DSI_CMD_MAX_LAYER);

    status_t status;

    dc_fb_dsi_cmd_handle_t *dcHandle = dc->prvData;
    dc_fb_dsi_cmd_layer_t *pLayer    = &(dcHandle->layers[layer]);
    dc_fb_info_t *fbInfo             = &(pLayer->fbInfo);
    mipi_dsi_device_t *dsiDevice     = dcHandle->dsiDevice;
    uint8_t byteperpixel             = VIDEO_GetPixelSizeBits(fbInfo->pixelFormat) / 8U;
    uint32_t minorLoopBytes          = (uint32_t)fbInfo->width * (uint32_t)byteperpixel;

    /* The selected area is non-constant in memory and the display device does not support 2-D memory write,
       return kStatus_Fail directly. */
    if ((dsiDevice->memWriteFunc2D == NULL) && (minorLoopBytes < (uint32_t)fbInfo->strideBytes))
    {
        return kStatus_Fail;
    }

    status = MIPI_DSI_SelectArea(dsiDevice, fbInfo->startX, fbInfo->startY, fbInfo->startX + fbInfo->width - 1U,
                                 fbInfo->startY + fbInfo->height - 1U);

    if (kStatus_Success != status)
    {
        return status;
    }

    /*
     * If TE pin is not used, send the new FB directly.
     *
     * If TE pin is used, then set the new FB as pending, and send it at next TE
     * interrupt.
     */
    if (!dcHandle->useTEPin)
    {
        pLayer->frameBuffer = frameBuffer;
        /* If the update width in byte is smaller than the stride, it means the pixel data is interleaved, use 2-D
         * transfer. */
        if (minorLoopBytes < (uint32_t)fbInfo->strideBytes)
        {
            status = MIPI_DSI_WriteMemory2D(dsiDevice, frameBuffer, minorLoopBytes,
                                            (uint32_t)fbInfo->strideBytes - minorLoopBytes, (uint32_t)fbInfo->height);
        }
        else
        {
            status =
                MIPI_DSI_WriteMemory(dsiDevice, frameBuffer, (uint32_t)fbInfo->height * (uint32_t)fbInfo->strideBytes);
        }
    }
    else
    {
        if (pLayer->fbWaitTE == NULL)
        {
            /* Save the new FB, and send it at next TE. */
            pLayer->fbWaitTE = frameBuffer;
        }
        else
        {
            /*
             * Generally should never be here, because this function should only
             * be called when no pending frames.
             */
            status = kStatus_Fail;
        }
    }

    return status;
}

void DC_FB_DSI_CMD_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    assert(layer < DC_FB_DSI_CMD_MAX_LAYER);
    dc_fb_dsi_cmd_handle_t *dcHandle = dc->prvData;

    dcHandle->layers[layer].callback = callback;
    dcHandle->layers[layer].cbParam  = param;
}

uint32_t DC_FB_DSI_CMD_GetProperty(const dc_fb_t *dc)
{
    dc_fb_dsi_cmd_handle_t *dcHandle = dc->prvData;
    mipi_dsi_device_t *dsiDevice     = dcHandle->dsiDevice;
    if (dsiDevice->memWriteFunc2D != NULL)
    {
        return (uint32_t)kDC_FB_TwoDimensionMemoryWrite;
    }
    else
    {
        return 0;
    }
}

void DC_FB_DSI_CMD_TE_IRQHandler(const dc_fb_t *dc)
{
    dc_fb_dsi_cmd_handle_t *dcHandle;
    dc_fb_dsi_cmd_layer_t *layer;
    dc_fb_info_t *fbInfo;
    uint8_t *newFB;
    uint8_t byteperpixel;
    uint32_t minorLoopBytes;

    dcHandle = (dc_fb_dsi_cmd_handle_t *)dc->prvData;

    /* Currently only support one layer, so the layer index is always 0. */
    layer = &(dcHandle->layers[0]);

    newFB = layer->fbWaitTE;

    if (NULL != newFB)
    {
        fbInfo             = &(layer->fbInfo);
        layer->fbWaitTE    = NULL;
        layer->frameBuffer = newFB;
        byteperpixel       = VIDEO_GetPixelSizeBits(fbInfo->pixelFormat) / 8U;
        minorLoopBytes     = (uint32_t)fbInfo->width * (uint32_t)byteperpixel;
        /* If the updaett width is smaller than the stride, it means the pixel data is interleaved, use 2-D transfer. */
        if (minorLoopBytes < (uint32_t)fbInfo->strideBytes)
        {
            (void)MIPI_DSI_WriteMemory2D(dcHandle->dsiDevice, newFB, minorLoopBytes,
                                         (uint32_t)fbInfo->strideBytes - minorLoopBytes, (uint32_t)fbInfo->height);
        }
        else
        {
            (void)MIPI_DSI_WriteMemory(dcHandle->dsiDevice, newFB,
                                       (uint32_t)fbInfo->height * (uint32_t)fbInfo->strideBytes);
        }
    }
}
