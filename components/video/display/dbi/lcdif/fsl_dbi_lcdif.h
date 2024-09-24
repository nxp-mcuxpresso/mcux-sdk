/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DBI_LCDIF_H_
#define FSL_DBI_LCDIF_H_

#ifndef DBI_USE_MIPI_PANEL
#define DBI_USE_MIPI_PANEL 0
#endif

#include "fsl_dbi.h"
#include "fsl_lcdif.h"
#if DBI_USE_MIPI_PANEL
#include "fsl_mipi_dsi.h"
#endif

/*
 * Change log:
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dbi_lcdif
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief LCDIF DBI interface transfer operation. */
extern const dbi_iface_xfer_ops_t g_dbiIfaceXferOps;
extern const dbi_config_ops_t g_dbiConfigOps;

typedef struct _dbi_lcdif_prv_data
{
    LCDIF_Type *lcdif;       /*!< Pointer to LCDIF peripheral. */
    uint16_t height;         /*!< Left height of the area to send. */
    uint16_t width;          /*!< Width of the area to send. */
    uint8_t bytePerPixel;    /*!< Used to calculate stride when not using 2-D memory write. */
#if DBI_USE_MIPI_PANEL
    MIPI_DSI_HOST_Type *dsi; /*!< Pointer to MIPI DSI peripheral. */
    const uint8_t *data;     /*!< Pointer to the pixel data to send. Used only for MIPI command panel, since the MIPI
                                payload size is limited. */
    uint16_t heightSent; /*!< Height of the area already sent. Used only for MIPI command panel, since the MIPI payload
                            size is limited. */
    uint16_t heightEachWrite; /*!< Height of the area for each memory write. Used only for MIPI command panel, since the
                                 MIPI payload size is limited. */
    uint16_t
        stride; /*!< Stride of the area. Used only for MIPI command panel, since the MIPI payload size is limited. */
#endif
} dbi_lcdif_prv_data_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Init LCDIF DBI controller.
 *
 * @param[out] dbiIface Pointer to the DBI interface.
 * @param[in] prvData Private data for DBI controller, maintains the info LCDIF needs for the memory write,
    uppwer layer only need to pass in it, DBI_LCDIF driver will initialize it.
 * @param[in] lcdif Pointer to LCDIF base.
 * @param[in] dsi Pointer to MIPI DSI base. Set to NULL if the panel uses a parallel interface.
 *
 */
void DBI_LCDIF_InitController(dbi_iface_t *dbiIface, dbi_lcdif_prv_data_t *prvData, void *lcdif, void *dsi);

status_t DBI_LCDIF_WriteCommandData(dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte);

status_t DBI_LCDIF_WriteMemory(dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte);

status_t DBI_LCDIF_WriteMemory2D(
    dbi_iface_t *dbiIface, uint32_t command, const void *data, uint32_t len_byte, uint32_t stride_byte);

status_t DBI_LCDIF_SetPixelFormat(dbi_iface_t *dbiIface, video_pixel_format_t format);

void DBI_LCDIF_IRQHandler(dbi_iface_t *dbiIface);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_DBI_LCDIF_H_ */
