/*
 * Copyright 2021,2023 NXP
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
/*! @brief Driver version. */
#define FSL_SOC_MIPI_DSI_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/* PLL VCO output frequency max value is 1.5GHz, VCO output is (refClk / CN ) * CM. */
#define DSI_DPHY_PLL_VCO_MAX 1500000000U
#define DSI_DPHY_PLL_VCO_MIN 750000000U

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_SOC_MIPI_DSI_H_ */
