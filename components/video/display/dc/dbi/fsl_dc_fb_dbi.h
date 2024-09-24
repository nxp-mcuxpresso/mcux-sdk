/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DC_FB_DBI_H_
#define _FSL_DC_FB_DBI_H_

#include "fsl_dc_fb.h"
#include "fsl_dbi.h"

/*!
 * @addtogroup dc_fb_dbi
 * @{
 */

/*
 * Change log:
 *
 * - 1.0.0
 *   - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Data for DBI display controller driver handle. */
typedef struct _dc_fb_dbi_handle
{
    /* These items are initialized in driver */
    uint8_t initTimes;          /*!< How many times the displa controller is initialized. */
    dc_fb_info_t fbInfo;        /*!< Frame buffer info. */
    dc_fb_callback_t callback;  /*!< Callback for frame data sent done. */
    void *cbParam;              /*!< Callback parameter. */
    const uint8_t *frameBuffer; /*!< The frame buffer currently used. */
    volatile bool fbWaitTE;     /*!< There is frame buffer wait to send at next TE. */

    /* These items are initialized by application. */
    dbi_iface_t dbiIface;             /*!< DBI interface. */
    uint16_t width;                   /*!< Panel width. */
    uint16_t height;                  /*!< Panel height. */
    video_pixel_format_t pixelFormat; /*!< Panel pixel format. */
    bool useTEPin;                    /*!< Whether to use the panel TE pin to handle tearing effect. */
} dc_fb_dbi_handle_t;

extern const dc_fb_ops_t g_dcFbOpsDbi;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t DC_FB_DBI_Init(const dc_fb_t *dc);
status_t DC_FB_DBI_Deinit(const dc_fb_t *dc);
status_t DC_FB_DBI_EnableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_DBI_DisableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_DBI_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_DBI_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_DBI_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer);
uint32_t DC_FB_DBI_GetProperty(const dc_fb_t *dc);
void DC_FB_DBI_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param);

/*
 * If useTEPin is true, the driver will use TE pin to handle tearing effect.
 * Then call this function should be called in panel TE pin ISR.
 */
void DC_FB_DBI_TE_IRQHandler(const dc_fb_t *dc);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DC_FB_DBI_H_ */
