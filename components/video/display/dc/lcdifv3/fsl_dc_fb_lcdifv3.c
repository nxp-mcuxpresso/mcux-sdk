/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_lcdifv3.h"
#if defined(SDK_OS_FREE_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsLcdifv3 = {
    .init                  = DC_FB_LCDIFV3_Init,
    .deinit                = DC_FB_LCDIFV3_Deinit,
    .enableLayer           = DC_FB_LCDIFV3_EnableLayer,
    .disableLayer          = DC_FB_LCDIFV3_DisableLayer,
    .setLayerConfig        = DC_FB_LCDIFV3_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_LCDIFV3_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_LCDIFV3_SetFrameBuffer,
    .getProperty           = DC_FB_LCDIFV3_GetProperty,
    .setCallback           = DC_FB_LCDIFV3_SetCallback,
};

typedef struct
{
    video_pixel_format_t videoFormat;
    lcdifv3_pixel_format_t lcdifv3Format;
} dc_fb_lcdifv3_pixel_foramt_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t DC_FB_LCDIFV3_GetPixelFormat(video_pixel_format_t input, lcdifv3_pixel_format_t *output);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const dc_fb_lcdifv3_pixel_foramt_map_t s_lcdifv3PixelFormatMap[] = {
    {kVIDEO_PixelFormatRGB565, kLCDIFV3_PixelFormatRGB565},
    {kVIDEO_PixelFormatRGB888, kLCDIFV3_PixelFormatRGB888},
    {kVIDEO_PixelFormatXRGB8888, kLCDIFV3_PixelFormatARGB8888},
    {kVIDEO_PixelFormatXBGR8888, kLCDIFV3_PixelFormatABGR8888},
    {kVIDEO_PixelFormatXRGB4444, kLCDIFV3_PixelFormatARGB4444},
    {kVIDEO_PixelFormatXRGB1555, kLCDIFV3_PixelFormatARGB1555}};
{
    kVIDEO_PixelFormatYVYU, kLCDIFV3_PixelFormatYVYU
}
}
;
{
    kVIDEO_PixelFormatYUYV, kLCDIFV3_PixelFormatYUYV
}
}
;
{
    kVIDEO_PixelFormatVYUY, kLCDIFV3_PixelFormatVYUY
}
}
;
{
    kVIDEO_PixelFormatUYVY, kLCDIFV3_PixelFormatUYVY
}
}
;

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t DC_FB_LCDIFV3_GetPixelFormat(video_pixel_format_t input, lcdifv3_pixel_format_t *output)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_lcdifv3PixelFormatMap); i++)
    {
        if (s_lcdifv3PixelFormatMap[i].videoFormat == input)
        {
            *output = s_lcdifv3PixelFormatMap[i].lcdifv3Format;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}

status_t DC_FB_LCDIFV3_Init(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;
    const dc_fb_lcdifv3_config_t *dcConfig;

    lcdifv3_display_config_t lcdifv3Config = {0};

    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    if (0U == dcHandle->initTimes++)
    {
        dcConfig = (const dc_fb_lcdifv3_config_t *)(dc->config);

        LCDIFV3_DisplayGetDefaultConfig(&lcdifv3Config);

        lcdifv3Config.panelWidth    = dcConfig->width;
        lcdifv3Config.panelHeight   = dcConfig->height;
        lcdifv3Config.hsw           = (uint8_t)dcConfig->hsw;
        lcdifv3Config.hfp           = (uint8_t)dcConfig->hfp;
        lcdifv3Config.hbp           = (uint8_t)dcConfig->hbp;
        lcdifv3Config.vsw           = (uint8_t)dcConfig->vsw;
        lcdifv3Config.vfp           = (uint8_t)dcConfig->vfp;
        lcdifv3Config.vbp           = (uint8_t)dcConfig->vbp;
        lcdifv3Config.polarityFlags = dcConfig->polarityFlags;
        lcdifv3Config.lineOrder     = dcConfig->lineOrder;

        dcHandle->height  = dcConfig->height;
        dcHandle->width   = dcConfig->width;
        dcHandle->lcdifv3 = dcConfig->lcdifv3;
        dcHandle->domain  = dcConfig->domain;

        LCDIFV3_Init(dcHandle->lcdifv3);

        LCDIFV3_SetDisplayConfig(dcHandle->lcdifv3, &lcdifv3Config);

        LCDIFV3_EnableInterrupts(dcHandle->lcdifv3, dcHandle->domain, (uint32_t)kLCDIFV3_VerticalBlankingInterrupt);

        LCDIFV3_EnableDisplay(dcHandle->lcdifv3, true);
    }

    return status;
}

status_t DC_FB_LCDIFV3_Deinit(const dc_fb_t *dc)
{
    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    if (dcHandle->initTimes > 0U)
    {
        if (--dcHandle->initTimes == 0U)
        {
            LCDIFV3_DisableInterrupts(dcHandle->lcdifv3, dcHandle->domain,
                                      (uint32_t)kLCDIFV3_VerticalBlankingInterrupt);
            LCDIFV3_Deinit(dcHandle->lcdifv3);
        }
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIFV3_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);

    status_t status                  = kStatus_Success;
    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    /* If the layer is not started. */
    if (!dcHandle->layers[0].enabled)
    {
        LCDIFV3_SetLayerBackGroundColor(dcHandle->lcdifv3, 0U);
        LCDIFV3_EnableLayer(dcHandle->lcdifv3, true);
        LCDIFV3_TriggerLayerShadowLoad(dcHandle->lcdifv3);
        dcHandle->layers[0].shadowLoadPending = true;

        while (true == dcHandle->layers[0].shadowLoadPending)
        {
#if defined(SDK_OS_FREE_RTOS)
            vTaskDelay(1);
#endif
        }

        dcHandle->layers[0].activeBuffer = dcHandle->layers[0].inactiveBuffer;
        dcHandle->layers[0].enabled      = true;
    }

    return status;
}

status_t DC_FB_LCDIFV3_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);

    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    if (dcHandle->layers[0].enabled)
    {
        LCDIFV3_EnableLayer(dcHandle->lcdifv3, false);
        LCDIFV3_TriggerLayerShadowLoad(dcHandle->lcdifv3);
        dcHandle->layers[0].enabled = false;
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIFV3_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);

    lcdifv3_buffer_config_t bufferConfig = {0};
    lcdifv3_pixel_format_t pixelFormat;
    LCDIF_Type *lcdifv3;
    status_t status;

    dc_fb_lcdifv3_handle_t *dcHandle = (dc_fb_lcdifv3_handle_t *)(dc->prvData);

    lcdifv3 = dcHandle->lcdifv3;

    status = DC_FB_LCDIFV3_GetPixelFormat(fbInfo->pixelFormat, &pixelFormat);
    if (kStatus_Success != status)
    {
        return status;
    }

    LCDIFV3_SetLayerSize(lcdifv3, fbInfo->width, fbInfo->height);
    LCDIFV3_SetLayerOffset(lcdifv3, fbInfo->startX, fbInfo->startY);

    bufferConfig.strideBytes = fbInfo->strideBytes;
    bufferConfig.pixelFormat = pixelFormat;
    LCDIFV3_SetLayerBufferConfig(lcdifv3, &bufferConfig);

    return kStatus_Success;
}

status_t DC_FB_LCDIFV3_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);

    dc_fb_lcdifv3_handle_t *dcHandle = (dc_fb_lcdifv3_handle_t *)(dc->prvData);

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = dcHandle->width;
    fbInfo->height      = dcHandle->height;
    fbInfo->strideBytes = DC_FB_LCDIFV3_DEFAULT_BYTE_PER_PIXEL * dcHandle->width;
    fbInfo->pixelFormat = DC_FB_LCDIFV3_DEFAULT_PIXEL_FORMAT;

    return kStatus_Success;
}

status_t DC_FB_LCDIFV3_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);
    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    LCDIFV3_SetLayerBufferAddr(dcHandle->lcdifv3, (uint32_t)(uint8_t *)frameBuffer);
    dcHandle->layers[layer].inactiveBuffer = frameBuffer;

    if (dcHandle->layers[0].enabled)
    {
        LCDIFV3_TriggerLayerShadowLoad(dcHandle->lcdifv3);
        dcHandle->layers[0].shadowLoadPending = true;
        dcHandle->layers[0].framePending      = true;
    }
    else
    {
    }

    return kStatus_Success;
}

void DC_FB_LCDIFV3_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    assert(layer < DC_FB_LCDIFV3_MAX_LAYER);
    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;

    dcHandle->layers[0].callback = callback;
    dcHandle->layers[0].cbParam  = param;
}

uint32_t DC_FB_LCDIFV3_GetProperty(const dc_fb_t *dc)
{
    return (uint32_t)kDC_FB_ReserveFrameBuffer;
}

void DC_FB_LCDIFV3_IRQHandler(const dc_fb_t *dc)
{
    uint32_t intStatus;
    dc_fb_lcdifv3_handle_t *dcHandle = dc->prvData;
    dc_fb_lcdifv3_layer_t *layer;
    void *oldActiveBuffer;

    intStatus = LCDIFV3_GetInterruptStatus(dcHandle->lcdifv3, dcHandle->domain);
    LCDIFV3_ClearInterruptStatus(dcHandle->lcdifv3, dcHandle->domain, intStatus);

    if (0U == (intStatus & (uint32_t)kLCDIFV3_VerticalBlankingInterrupt))
    {
        return;
    }

    for (uint8_t i = 0; i < DC_FB_LCDIFV3_MAX_LAYER; i++)
    {
        if (dcHandle->layers[i].shadowLoadPending)
        {
            dcHandle->layers[i].shadowLoadPending = false;
        }

        if (dcHandle->layers[i].framePending)
        {
            layer = &dcHandle->layers[i];

            oldActiveBuffer                  = layer->activeBuffer;
            layer->activeBuffer              = layer->inactiveBuffer;
            dcHandle->layers[i].framePending = false;

            layer->callback(layer->cbParam, oldActiveBuffer);
        }
    }
}
