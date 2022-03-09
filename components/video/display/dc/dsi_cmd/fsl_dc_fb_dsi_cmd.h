/*
 * Copyright (c) 2019-2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DC_FB_DSI_CMD_H_
#define _FSL_DC_FB_DSI_CMD_H_

#include "fsl_dc_fb.h"
#include "fsl_mipi_dsi_cmd.h"
#include "fsl_display.h"

/*!
 * @addtogroup dc_fb_dsi_cmd
 * @{
 */

/*
 * Change log:
 *
 * - 1.1.1
 *   - Bug Fixes
 *     - Fixed MISRA 2012 issues.
 *
 * - 1.1.0
 *   - Improvements
 *     - Supported using TE pin to handle smart panel tearing effect.
 *
 * - 1.0.0
 *   - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Only support one layer. To support multiple layers, the DSI transfer should
 * be protected. If writing to a layer is in progress, the writing to another layer
 * should be blocked until previous layer operation finished.
 */
#define DC_FB_DSI_CMD_MAX_LAYER 1U
#if (DC_FB_DSI_CMD_MAX_LAYER != 1U)
#error Current driver only supports one layer
#endif

/*! @brief DSI_CMD display configuration. */
typedef struct _dc_fb_dsi_cmd_config
{
    display_config_t commonConfig; /*!< Common display configuration. */
    bool useTEPin;                 /*!< Use TE pin to handle tearing effect or not. */
} dc_fb_dsi_cmd_config_t;

/*! @brief Data for DSI_CMD display controller layer. */
typedef struct _dc_fb_dsi_cmd_layer
{
    bool enabled;              /*!< The layer is enabled. */
    dc_fb_info_t fbInfo;       /*!< Frame buffer info. */
    void *frameBuffer;         /*!< Frame buffer sent currently. */
    dc_fb_callback_t callback; /*!< Callback for buffer switch off. */
    void *cbParam;             /*!< Callback parameter. */
    void *volatile fbWaitTE;   /*!< New frame buffer wait to send at next TE. */
} dc_fb_dsi_cmd_layer_t;

/*! @brief Data for DSI_CMD display controller driver handle. */
typedef struct _dc_fb_dsi_cmd_handle
{
    mipi_dsi_device_t *dsiDevice;                          /*!< The MIPI DSI device that controls the panel. */
    display_handle_t *panelHandle;                         /*!< Handle of the panel. */
    uint8_t initTimes;                                     /*!< How many times the DC is initialized. */
    uint8_t enabledLayerCount;                             /*!< How many times layers are enabled. */
    dc_fb_dsi_cmd_layer_t layers[DC_FB_DSI_CMD_MAX_LAYER]; /*!< Information of the layer. */
    bool useTEPin;                                         /*!< Use TE pin to handle tearing effect or not. */
} dc_fb_dsi_cmd_handle_t;

extern const dc_fb_ops_t g_dcFbOpsDsiCmd;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t DC_FB_DSI_CMD_Init(const dc_fb_t *dc);
status_t DC_FB_DSI_CMD_Deinit(const dc_fb_t *dc);
status_t DC_FB_DSI_CMD_EnableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_DSI_CMD_DisableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_DSI_CMD_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_DSI_CMD_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_DSI_CMD_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer);
uint32_t DC_FB_DSI_CMD_GetProperty(const dc_fb_t *dc);
void DC_FB_DSI_CMD_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param);

/* This function should be called in panel TE pin ISR. */
void DC_FB_DSI_CMD_TE_IRQHandler(const dc_fb_t *dc);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DC_FB_DSI_CMD_H_ */
