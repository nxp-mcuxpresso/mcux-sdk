/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SOC_MIPI_DSI_H_
#define _FSL_SOC_MIPI_DSI_H_

#include "fsl_common.h"

/*!
 * @addtogroup soc_mipi_dsi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.soc_mipi_dsi"
#endif

/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.0. */
#define FSL_SOC_MIPI_DSI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
typedef MIPI_DSI_LVDS_COMBO_CSR_Type MIPI_DSI_CSR_Type;
#define MIPI_DSI_CSR_ULPS_CTRL(csr)      ((csr)->ULPS_CTRL)
#define MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK MIPI_DSI_LVDS_COMBO_CSR_ULPS_CTRL_TX_ULPS_MASK
#define MIPI_DSI_CSR_PXL2DPI(csr)        ((csr)->PXL2DPI_CTRL)
#else
#define MIPI_DSI_CSR_ULPS_CTRL(csr)      ((csr)->TX_ULPS_ENABLE)
#define MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK MIPI_DSI_TX_ULPS_ENABLE_TX_ULPS_ENABLE_MASK
#define MIPI_DSI_CSR_PXL2DPI(csr)        ((csr)->PXL2DPI_CONFIG)
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Get MIPI_DSI_CSR to control related MIPI DSI.
 *
 * @param base MIPI DSI host peripheral base address.
 * @return The MIPI_DSI_CSR to control MIPI DSI.
 */
static inline MIPI_DSI_CSR_Type* SOC_MIPI_DSI_GetCsr(MIPI_DSI_HOST_Type *base)
{
    return (MIPI_DSI_CSR_Type *)((uint32_t)(base) - (uint32_t)FSL_FEATURE_DSI_CSR_OFFSET);
}

/*!
 * @brief Enable or disable the TX ULPS.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param enable Use true to enable, false to disable.
 */
static inline void SOC_MIPI_DSI_EnableUlps(MIPI_DSI_HOST_Type *base, bool enable)
{
    MIPI_DSI_CSR_Type *csr = SOC_MIPI_DSI_GetCsr(base);

    if (enable)
    {
        MIPI_DSI_CSR_ULPS_CTRL(csr) = MIPI_DSI_CSR_ULPS_CTRL_ULPS_MASK;
    }
    else
    {
        MIPI_DSI_CSR_ULPS_CTRL(csr) = 0U;
    }
}

/*!
 * @brief Set pixel-link to DPI format mapping.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param pxl2dpi The map relationship.
 */
static inline void SOC_MIPI_DSI_SetPixelDpiMap(MIPI_DSI_HOST_Type *base, uint32_t pxl2dpi)
{
    MIPI_DSI_CSR_Type *csr = SOC_MIPI_DSI_GetCsr(base);

    MIPI_DSI_CSR_PXL2DPI(csr) = pxl2dpi;
}

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_SOC_MIPI_DSI_H_ */
