/*
 * Copyright 2023, 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_soc.h"

/*! @brief Pointers to enetc si bases for each instance. */
static ENETC_SI_Type *const s_enetcSiBases[] = ENETC_SI_BASE_PTRS;

/*! @brief Pointers to netc bases for each instance. */
static ENETC_PCI_TYPE0_Type *const s_netcBases[] = ENETC_PCI_TYPE0_BASE_PTRS;

/*! @brief Pointers to netc vf bases for each instance. */
static ENETC_VF_PCI_TYPE0_Type *const s_netcVfBases[] = ENETC_VF_PCI_TYPE0_BASE_PTRS;

/*! @brief Pointers to enetc bases for each instance. */
static NETC_ENETC_Type *const s_netcEnetcBases[] = NETC_ENETC_BASE_PTRS;

void NETC_SocGetBaseResource(netc_enetc_hw_t *hw, netc_hw_si_idx_t si)
{
    uint8_t instance = getSiInstance(si);
    uint8_t siNum    = getSiNum(si);
    uint8_t siIdx    = getSiIdx(si);

    hw->si             = s_enetcSiBases[siIdx];
    hw->base           = s_netcEnetcBases[instance];
    hw->common         = (NETC_SW_ENETC_Type *)((uintptr_t)hw->base + 0x1000U);
    hw->portGroup.port = (NETC_PORT_Type *)((uintptr_t)hw->base + 0x4000U);
    hw->portGroup.eth  = (NETC_ETH_LINK_Type *)((uintptr_t)hw->base + 0x5000U);
    hw->global         = (ENETC_GLOBAL_Type *)((uintptr_t)hw->base + 0x10000U);
    if (siNum == 0U)
    {
        hw->func.pf = s_netcBases[1U + siIdx];
        hw->msixTable = (netc_msix_entry_t *)((uintptr_t)hw->si + 0x30000U);
    }
    else
    {
        hw->func.vf = s_netcVfBases[siIdx - 3U];
        hw->msixTable = (netc_msix_entry_t *)((uintptr_t)hw->si + 0x60000U);
    }
}

uint32_t NETC_SocGetFuncInstance(netc_hw_eth_port_idx_t port)
{
    uint32_t instance = (uint32_t)port + 1U;

    return instance;
}
