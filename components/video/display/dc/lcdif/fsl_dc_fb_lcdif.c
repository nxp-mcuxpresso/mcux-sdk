/*
 * Copyright (c) 2019-2020,2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_lcdif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsLcdif = {
    .init                  = DC_FB_LCDIF_Init,
    .deinit                = DC_FB_LCDIF_Deinit,
    .enableLayer           = DC_FB_LCDIF_EnableLayer,
    .disableLayer          = DC_FB_LCDIF_DisableLayer,
    .setLayerConfig        = DC_FB_LCDIF_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_LCDIF_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_LCDIF_SetFrameBuffer,
    .getProperty           = DC_FB_LCDIF_GetProperty,
    .setCallback           = DC_FB_LCDIF_SetCallback,
};

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
typedef struct
{
    video_pixel_format_t videoFormat;
    lcdif_fb_format_t lcdifFormat;
    lcdif_layer_input_order_t componentOrder;
} dc_fb_lcdif_pixel_foramt_map_t;
#else
typedef struct
{
    video_pixel_format_t videoFormat;
    lcdif_fb_format_t lcdifFormat;
} dc_fb_lcdif_pixel_foramt_map_t;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
static status_t DC_FB_LCDIF_GetPixelFormat(video_pixel_format_t input, lcdif_fb_format_t *output, lcdif_layer_input_order_t *order);
#else
static status_t DC_FB_LCDIF_GetPixelFormat(video_pixel_format_t input, lcdif_fb_format_t *output);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
static const dc_fb_lcdif_pixel_foramt_map_t s_lcdifPixelFormatMap[] = {
    {kVIDEO_PixelFormatXRGB8888, kLCDIF_PixelFormatARGB8888, kLCDIF_PixelInputOrderARGB},
    {kVIDEO_PixelFormatRGBX8888, kLCDIF_PixelFormatARGB8888, kLCDIF_PixelInputOrderRGBA},
    {kVIDEO_PixelFormatXBGR8888, kLCDIF_PixelFormatARGB8888, kLCDIF_PixelInputOrderABGR},
    {kVIDEO_PixelFormatBGRX8888, kLCDIF_PixelFormatARGB8888, kLCDIF_PixelInputOrderBGRA},
    {kVIDEO_PixelFormatRGB888, kLCDIF_PixelFormatRGB888, kLCDIF_PixelInputOrderARGB},
    {kVIDEO_PixelFormatBGR888, kLCDIF_PixelFormatRGB888, kLCDIF_PixelInputOrderABGR},
    {kVIDEO_PixelFormatRGB565, kLCDIF_PixelFormatRGB565, kLCDIF_PixelInputOrderARGB},
    {kVIDEO_PixelFormatBGR565, kLCDIF_PixelFormatRGB565, kLCDIF_PixelInputOrderABGR},
    {kVIDEO_PixelFormatXRGB1555, kLCDIF_PixelFormatARGB1555, kLCDIF_PixelInputOrderARGB},
    {kVIDEO_PixelFormatRGBX5551, kLCDIF_PixelFormatARGB1555, kLCDIF_PixelInputOrderRGBA},
    {kVIDEO_PixelFormatXBGR1555, kLCDIF_PixelFormatARGB1555, kLCDIF_PixelInputOrderABGR},
    {kVIDEO_PixelFormatBGRX5551, kLCDIF_PixelFormatARGB1555, kLCDIF_PixelInputOrderBGRA},
    {kVIDEO_PixelFormatXRGB4444, kLCDIF_PixelFormatARGB4444, kLCDIF_PixelInputOrderARGB},
    {kVIDEO_PixelFormatRGBX4444, kLCDIF_PixelFormatARGB4444, kLCDIF_PixelInputOrderRGBA},
    {kVIDEO_PixelFormatXBGR4444, kLCDIF_PixelFormatARGB4444, kLCDIF_PixelInputOrderABGR},
    {kVIDEO_PixelFormatBGRX4444, kLCDIF_PixelFormatARGB4444, kLCDIF_PixelInputOrderBGRA},
};
#else
static const dc_fb_lcdif_pixel_foramt_map_t s_lcdifPixelFormatMap[] = {
    {kVIDEO_PixelFormatRGB565, kLCDIF_PixelFormatRGB565},
    {kVIDEO_PixelFormatXRGB8888, kLCDIF_PixelFormatXRGB8888},
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
static status_t DC_FB_LCDIF_GetPixelFormat(video_pixel_format_t input, lcdif_fb_format_t *output, lcdif_layer_input_order_t *order)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_lcdifPixelFormatMap); i++)
    {
        if (s_lcdifPixelFormatMap[i].videoFormat == input)
        {
            *output = s_lcdifPixelFormatMap[i].lcdifFormat;
            *order = s_lcdifPixelFormatMap[i].componentOrder;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}
#else
static status_t DC_FB_LCDIF_GetPixelFormat(video_pixel_format_t input, lcdif_fb_format_t *output)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_lcdifPixelFormatMap); i++)
    {
        if (s_lcdifPixelFormatMap[i].videoFormat == input)
        {
            *output = s_lcdifPixelFormatMap[i].lcdifFormat;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}
#endif

status_t DC_FB_LCDIF_Init(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;
    const dc_fb_lcdif_config_t *dcConfig;

    lcdif_dpi_config_t lcdifConfig = {0};

    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

    if (0U == dcHandle->initTimes++)
    {
        dcConfig = (const dc_fb_lcdif_config_t *)(dc->config);

        LCDIF_DpiModeGetDefaultConfig(&lcdifConfig);

        lcdifConfig.panelWidth    = dcConfig->width;
        lcdifConfig.panelHeight   = dcConfig->height;
        lcdifConfig.hsw           = (uint8_t)dcConfig->hsw;
        lcdifConfig.hfp           = (uint8_t)dcConfig->hfp;
        lcdifConfig.hbp           = (uint8_t)dcConfig->hbp;
        lcdifConfig.vsw           = (uint8_t)dcConfig->vsw;
        lcdifConfig.vfp           = (uint8_t)dcConfig->vfp;
        lcdifConfig.vbp           = (uint8_t)dcConfig->vbp;
        lcdifConfig.format        = dcConfig->outputFormat;
        lcdifConfig.polarityFlags = dcConfig->polarityFlags;

        dcHandle->height = dcConfig->height;
        dcHandle->width  = dcConfig->width;
        dcHandle->lcdif  = dcConfig->lcdif;

        (void)LCDIF_Init(dcHandle->lcdif);

        status = LCDIF_DpiModeSetConfig(dcHandle->lcdif, 0, &lcdifConfig);

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
        LCDIF_SetFrameBufferBackground(dcHandle->lcdif, 0U, 0U);
#endif
    }

    return status;
}

status_t DC_FB_LCDIF_Deinit(const dc_fb_t *dc)
{
    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

    if (dcHandle->initTimes > 0U)
    {
        if (--dcHandle->initTimes == 0U)
        {
            LCDIF_Deinit(dcHandle->lcdif);
        }
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIF_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);

    status_t status                = kStatus_Success;
    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

    /* If the layer is already started. */
    if (!dcHandle->layers[layer].enabled)
    {
        /* Must have valid frame buffer to show. */
        if (dcHandle->layers[layer].activeBuffer == NULL)
        {
            status = kStatus_Fail;
        }
        else
        {
            dcHandle->layers[layer].fbConfig.enable = true;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
            lcdif_panel_config_t config;
            LCDIF_PanelGetDefaultConfig(&config);
            LCDIF_SetPanelConfig(dcHandle->lcdif, 0, &config);

            switch (layer)
            {
                case 0U:
                    LCDIF_SetFrameBufferConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig);
                    break;
                case 1U:
                    LCDIF_SetOverlayLayerConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig, 0U);
                    break;
                case 2:
                    LCDIF_SetOverlayLayerConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig, 1U);
                    break;
            }
            LCDIF_Start(dcHandle->lcdif);
#else
            LCDIF_SetFrameBufferConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig);
#endif
            LCDIF_EnableInterrupts(dcHandle->lcdif, (uint32_t)kLCDIF_Display0FrameDoneInterrupt);
            dcHandle->layers[layer].enabled = true;
        }
    }

    return status;
}

status_t DC_FB_LCDIF_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);

    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

    if (dcHandle->layers[layer].enabled)
    {
        dcHandle->layers[layer].fbConfig.enable = false;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
        switch (layer)
        {
            case 0U:
                LCDIF_SetFrameBufferConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig);
                break;
            case 1U:
                LCDIF_SetOverlayLayerConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig, 0U);
                break;
            case 2:
                LCDIF_SetOverlayLayerConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig, 1U);
                break;
        }
        LCDIF_SetUpdateReady(dcHandle->lcdif);
#else
        LCDIF_SetFrameBufferConfig(dcHandle->lcdif, 0, &dcHandle->layers[layer].fbConfig);
#endif
        dcHandle->layers[layer].enabled = false;
        LCDIF_DisableInterrupts(dcHandle->lcdif, (uint32_t)kLCDIF_Display0FrameDoneInterrupt);
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIF_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);

    lcdif_fb_format_t pixelFormat;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
    lcdif_layer_input_order_t componentOrder;
#endif
    status_t status;

    dc_fb_lcdif_handle_t *dcHandle = (dc_fb_lcdif_handle_t *)(dc->prvData);

#if !(defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000)
    assert(fbInfo->startX == 0U);
    assert(fbInfo->startY == 0U);
    assert(fbInfo->width == dcHandle->width);
    assert(fbInfo->height == dcHandle->height);
    status = DC_FB_LCDIF_GetPixelFormat(fbInfo->pixelFormat, &pixelFormat);
#else
    status = DC_FB_LCDIF_GetPixelFormat(fbInfo->pixelFormat, &pixelFormat, &componentOrder);
#endif

    if (kStatus_Success != status)
    {
        return status;
    }

    dcHandle->layers[layer].fbConfig.format = pixelFormat;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000
    dcHandle->layers[layer].fbConfig.enableClear     = false;
    dcHandle->layers[layer].fbConfig.inOrder         = componentOrder;
    dcHandle->layers[layer].fbConfig.colorkey.enable = false;
    dcHandle->layers[layer].fbConfig.rotateFlipMode  = kLCDIF_Rotate0;
    dcHandle->layers[layer].fbConfig.alpha.enable    = 0;
    dcHandle->layers[layer].fbConfig.topLeftX        = fbInfo->startX;
    dcHandle->layers[layer].fbConfig.topLeftY        = fbInfo->startY;
    dcHandle->layers[layer].fbConfig.width           = fbInfo->width;
    dcHandle->layers[layer].fbConfig.height          = fbInfo->height;
    /* gamma is disabled by default, no need to configure. */

    switch (layer)
    {
        case 0U:
            LCDIF_SetFrameBufferStride(dcHandle->lcdif, 0, fbInfo->strideBytes);
            break;
        case 1U:
            LCDIF_SetOverlayLayerStride(dcHandle->lcdif, 0, fbInfo->strideBytes, 0U);
            break;
        case 2:
            LCDIF_SetOverlayLayerStride(dcHandle->lcdif, 0, fbInfo->strideBytes, 1U);
            break;
    }
    LCDIF_SetUpdateReady(dcHandle->lcdif);
#else
    dcHandle->layers[layer].fbConfig.enableGamma = false;
    LCDIF_SetFrameBufferStride(dcHandle->lcdif, 0, fbInfo->strideBytes);
#endif

    return kStatus_Success;
}

status_t DC_FB_LCDIF_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);

    dc_fb_lcdif_handle_t *dcHandle = (dc_fb_lcdif_handle_t *)(dc->prvData);

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = dcHandle->width;
    fbInfo->height      = dcHandle->height;
    fbInfo->strideBytes = DC_FB_LCDIF_DEFAULT_BYTE_PER_PIXEL * dcHandle->width;
    fbInfo->pixelFormat = DC_FB_LCDIF_DEFAULT_PIXEL_FORMAT;

    return kStatus_Success;
}

status_t DC_FB_LCDIF_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);
    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) && FSL_FEATURE_LCDIF_VERSION_DC8000

    switch (layer)
    {
        case 0U:
            LCDIF_SetFrameBufferAddr(dcHandle->lcdif, 0, (uint32_t)(uint8_t *)frameBuffer);
            break;
        case 1U:
            LCDIF_SetOverlayLayerAddr(dcHandle->lcdif, 0, (uint32_t)(uint8_t *)frameBuffer, 0U);
            break;
        case 2:
            LCDIF_SetOverlayLayerAddr(dcHandle->lcdif, 0, (uint32_t)(uint8_t *)frameBuffer, 1U);
            break;
    }
    
    LCDIF_SetUpdateReady(dcHandle->lcdif);
#else
    LCDIF_SetFrameBufferAddr(dcHandle->lcdif, 0, (uint32_t)(uint8_t *)frameBuffer);
#endif
    dcHandle->layers[layer].inactiveBuffer = frameBuffer;

    if (!dcHandle->layers[layer].enabled)
    {
        dcHandle->layers[layer].activeBuffer = frameBuffer;
    }
    else
    {
        dcHandle->layers[layer].framePending = true;
    }

    return kStatus_Success;
}

void DC_FB_LCDIF_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    assert(layer < DC_FB_LCDIF_MAX_LAYER);
    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;

    dcHandle->layers[layer].callback = callback;
    dcHandle->layers[layer].cbParam  = param;
}

uint32_t DC_FB_LCDIF_GetProperty(const dc_fb_t *dc)
{
    return (uint32_t)kDC_FB_ReserveFrameBuffer;
}

void DC_FB_LCDIF_IRQHandler(const dc_fb_t *dc)
{
    uint32_t intStatus;
    dc_fb_lcdif_handle_t *dcHandle = dc->prvData;
    dc_fb_lcdif_layer_t *layer;
    void *oldActiveBuffer;

    intStatus = LCDIF_GetAndClearInterruptPendingFlags(dcHandle->lcdif);

    if (0U == (intStatus & (uint32_t)kLCDIF_Display0FrameDoneInterrupt))
    {
        return;
    }

    for (uint8_t i = 0; i < DC_FB_LCDIF_MAX_LAYER; i++)
    {
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
