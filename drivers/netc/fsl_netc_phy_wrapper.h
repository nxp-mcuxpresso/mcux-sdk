/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_NETC_PHY_WRAPPER_H_
#define _FSL_NETC_PHY_WRAPPER_H_

#include "fsl_common.h"
#include "fsl_netc_mdio.h"

#define getPhyReg(reg) ((uint16_t)(((uint32_t)(reg) >> 1U) & 0xFFFFU))
#define getPhyDev(reg) ((uint8_t)(((uint32_t)(reg) >> 17U) & 0x1FU))

/*!
 * @brief ENET_PHY modes supported
 */
typedef enum _phy_mode
{
    kNETC_SGMII1G = 0U,
    kNETC_SGMII2G5,
#if !(defined(FSL_FEATURE_NETC_HAS_NO_XGMII) && FSL_FEATURE_NETC_HAS_NO_XGMII)
    kNETC_XGMII10GAuto,
    kNETC_XGMII10G,
#endif
    kNETC_XFI,
} phy_mode_t;

/*!
 * @brief ENET_PHY mode init
 *
 * @param handle  mdio handle.
 * @param mode  phy mode.
 * @return status_t
 */
status_t NETC_PHYInit(netc_mdio_handle_t *handle, phy_mode_t mode);

#endif /* _FSL_NETC_PHY_WRAPPER_H_ */
