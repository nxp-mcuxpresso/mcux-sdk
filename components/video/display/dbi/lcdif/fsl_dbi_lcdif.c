/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dbi.h"
#include "fsl_dbi_lcdif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MIPI_DSI_MAX_PAYLOAD_SIZE 0xFFFF

typedef struct
{
    video_pixel_format_t videoFormat;
    lcdif_fb_format_t lcdifFormat;
    lcdif_layer_input_order_t componentOrder;
} dbi_lcdif_pixel_foramt_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t DBI_LCDIF_GetPixelFormat(video_pixel_format_t input,
                                         lcdif_fb_format_t *output,
                                         lcdif_layer_input_order_t *order);

static void DBI_LCDIF_WriteMemoryInternal(
    dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t stride_byte, bool isInterleave);

/*******************************************************************************
 * Variables
 ******************************************************************************/
const dbi_iface_xfer_ops_t g_dbiLcdifXferOps = {
    .writeCommandData = DBI_LCDIF_WriteCommandData,
    .writeMemory      = DBI_LCDIF_WriteMemory,
    .writeMemory2D    = DBI_LCDIF_WriteMemory2D,
};

const dbi_config_ops_t g_dbiLcdifConfigOps = {
    .setPixelFormat = DBI_LCDIF_SetPixelFormat,
};

static const dbi_lcdif_pixel_foramt_map_t s_lcdifPixelFormatMap[] = {
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

/*******************************************************************************
 * Code
 ******************************************************************************/
void DBI_LCDIF_IRQHandler(dbi_iface_t *dbiIface)
{
    dbi_lcdif_prv_data_t *prvData = (dbi_lcdif_prv_data_t *)dbiIface->prvData;
    LCDIF_Type *lcdif             = prvData->lcdif;

    LCDIF_GetAndClearInterruptPendingFlags(lcdif);

#if DBI_USE_MIPI_PANEL
    uint16_t height         = prvData->heightEachWrite;
    MIPI_DSI_HOST_Type *dsi = prvData->dsi;

    /* There is left data to send */
    if (prvData->height > 0)
    {
        if (prvData->heightEachWrite > prvData->height)
        {
            /* Change height, payload size and buffer for the last piece. */
            height = prvData->height;
            DSI_SetDbiPixelPayloadSize(dsi, height * prvData->width);
            LCDIF_SetFrameBufferPosition(lcdif, 0U, 0U, 0U, prvData->width, height);
        }

        LCDIF_DbiSelectArea(lcdif, 0, 0, prvData->heightSent, prvData->width - 1U, prvData->heightSent + height - 1U,
                            false);
        LCDIF_SetFrameBufferAddr(lcdif, 0, (uint32_t)prvData->data);

        /* Update data and height for next piece. */
        prvData->data += (height * prvData->stride);
        prvData->heightSent += height;
        prvData->height -= height;

        /* Write memory continue. */
        LCDIF_DbiSendCommand(lcdif, 0, kMIPI_DBI_WriteMemoryContinue);

        /* Start memory transfer. */
        LCDIF_DbiWriteMem(lcdif, 0);
    }
    else

    {
        /* Send complete, reset area height value. */
        prvData->height     = prvData->heightSent;
        prvData->heightSent = 0U;
#endif
        /* Completion callback. */
        dbiIface->memDoneCallback(kStatus_Success, dbiIface->memDoneCallbackParam);
#if DBI_USE_MIPI_PANEL
    }
#endif
}

void DBI_LCDIF_InitController(dbi_iface_t *dbiIface, dbi_lcdif_prv_data_t *prvData, void *lcdif, void *dsi)
{
    memset(dbiIface, 0, sizeof(dbi_iface_t));

    dbiIface->xferOps   = &g_dbiLcdifXferOps;
    dbiIface->configOps = &g_dbiLcdifConfigOps;
    dbiIface->prvData   = (void *)prvData;

    prvData->lcdif = (LCDIF_Type *)lcdif;

#if DBI_USE_MIPI_PANEL
    prvData->dsi = (MIPI_DSI_HOST_Type *)dsi;

    if (dsi != NULL)
    {
        /* Every time buffer 64 pixels first then begin the send. */
        DSI_SetDbiPixelFifoSendLevel(prvData->dsi, 64U);
    }
#endif

    LCDIF_EnableInterrupts(prvData->lcdif, kLCDIF_Display0FrameDoneInterrupt | kLCDIF_PanelUnderflowInterrupt);
}

status_t DBI_LCDIF_WriteCommandData(dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte)
{
    uint8_t cmd                   = command;
    uint8_t *pData                = (uint8_t *)data;
    dbi_lcdif_prv_data_t *prvData = (dbi_lcdif_prv_data_t *)dbiIface->prvData;
    LCDIF_Type *lcdif             = prvData->lcdif;

    /* If the command is set address, calculate the selected area size, since LCDIF needs these info for configuration.
     */
    if (cmd == kMIPI_DBI_SetColumnAddress)
    {
        prvData->width = (((uint16_t)pData[2] << 8U) | (uint16_t)pData[3]) - (((uint16_t)pData[0] << 8U) | (uint16_t)pData[1]) + 1U;
    }
    else if (cmd == kMIPI_DBI_SetPageAddress)
    {
        prvData->height = (((uint16_t)pData[2] << 8U) | (uint16_t)pData[3]) - (((uint16_t)pData[0] << 8U) | (uint16_t)pData[1]) + 1U;
    }

    LCDIF_DbiSendCommand(lcdif, 0U, cmd);

    if (len_byte != 0U)
    {
        LCDIF_DbiSendData(lcdif, 0U, pData, len_byte);
    }

    return kStatus_Success;
}

status_t DBI_LCDIF_WriteMemory(dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte)
{
    DBI_LCDIF_WriteMemoryInternal(dbiIface, command, data, 0U, false);

    return kStatus_Success;
}

status_t DBI_LCDIF_WriteMemory2D(
    dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte, uint32_t stride_byte)
{
    DBI_LCDIF_WriteMemoryInternal(dbiIface, command, data, stride_byte, true);

    return kStatus_Success;
}

status_t DBI_LCDIF_SetPixelFormat(dbi_iface_t *dbiIface, video_pixel_format_t format)
{
    status_t status = kStatus_Success;
    lcdif_fb_config_t fbConfig;
    dbi_lcdif_prv_data_t *prvData = (dbi_lcdif_prv_data_t *)dbiIface->prvData;
    LCDIF_Type *lcdif             = prvData->lcdif;
    lcdif_layer_input_order_t componentOrder;
    lcdif_fb_format_t pixelFormat;

    status = DBI_LCDIF_GetPixelFormat(format, &pixelFormat, &componentOrder);

    if (kStatus_Success != status)
    {
        return status;
    }

    LCDIF_FrameBufferGetDefaultConfig(&fbConfig);
    fbConfig.format  = pixelFormat;
    fbConfig.inOrder = componentOrder;
    LCDIF_SetFrameBufferConfig(lcdif, 0, &fbConfig);

    /* Set byte per pixel for stride calculation later. */
    prvData->bytePerPixel = VIDEO_GetPixelSizeBits(format) / 8U;

    return status;
}

static status_t DBI_LCDIF_GetPixelFormat(video_pixel_format_t input,
                                         lcdif_fb_format_t *output,
                                         lcdif_layer_input_order_t *order)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_lcdifPixelFormatMap); i++)
    {
        if (s_lcdifPixelFormatMap[i].videoFormat == input)
        {
            *output = s_lcdifPixelFormatMap[i].lcdifFormat;
            *order  = s_lcdifPixelFormatMap[i].componentOrder;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}

static void DBI_LCDIF_WriteMemoryInternal(
    dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t stride_byte, bool isInterleave)
{
    uint8_t cmd                   = command;
    dbi_lcdif_prv_data_t *prvData = (dbi_lcdif_prv_data_t *)dbiIface->prvData;
    LCDIF_Type *lcdif             = prvData->lcdif;
    uint16_t height               = prvData->height;
    uint32_t stride;

    if (isInterleave)
    {
        stride = stride_byte;
    }
    else
    {
        stride = prvData->width * prvData->bytePerPixel;
    }

    /* For RGB888 the stride shall be calculated as 4 bytes per pixel. */
    if (prvData->bytePerPixel == 3U)
    {
        LCDIF_SetFrameBufferStride(lcdif, 0, stride / 3U * 4U);
    }
    else
    {
        LCDIF_SetFrameBufferStride(lcdif, 0, stride);
    }

#if DBI_USE_MIPI_PANEL
    MIPI_DSI_HOST_Type *dsi = prvData->dsi;
    if (dsi != NULL)
    {
        prvData->stride = stride;

        /* If the whole update payload exceeds the DSI max payload size, send the payload in multiple times. */
        if ((prvData->width * prvData->height * prvData->bytePerPixel) > MIPI_DSI_MAX_PAYLOAD_SIZE)
        {
            /* Calculate how may lines to send each time. Make sure each time the buffer address meets the align
             * requirement. */
            height = MIPI_DSI_MAX_PAYLOAD_SIZE / prvData->width / prvData->bytePerPixel;
            while (((height * prvData->stride) & (LCDIF_FB_ALIGN - 1U)) != 0U)
            {
                height--;
            }
            prvData->heightEachWrite = height;

            /* Point the data to the next piece. */
            prvData->data = (uint8_t *)((uint32_t)data + (height * prvData->stride));
        }

        /* Set payload size. */
        DSI_SetDbiPixelPayloadSize(dsi, height * prvData->width);
    }

    /* Update height info. */
    prvData->heightSent = height;
#endif
    prvData->height -= height;

    /* Configure buffer position, address and area. */
    LCDIF_SetFrameBufferPosition(lcdif, 0U, 0U, 0U, prvData->width, height);
    LCDIF_DbiSelectArea(lcdif, 0, 0, 0, prvData->width - 1U, height - 1U, false);
    LCDIF_SetFrameBufferAddr(lcdif, 0, (uint32_t)data);

    /* Send command. */
    LCDIF_DbiSendCommand(lcdif, 0, cmd);

    /* Start memory transfer. */
    LCDIF_DbiWriteMem(lcdif, 0);
}
