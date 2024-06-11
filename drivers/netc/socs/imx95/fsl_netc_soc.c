/*
 * Copyright 2023 NXP
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

status_t NETC_SocPreInitVsi(netc_enetc_hw_t *hw, netc_hw_si_idx_t si)
{
    uint8_t macAddr0[] = { 0x00, 0x00, 0xfa, 0xfa, 0xdd, 0xa0 };
    uint8_t macAddr1[] = { 0x00, 0x00, 0xfa, 0xfa, 0xdd, 0xa1 };
    netc_hw_enetc_si_config_t vsi0Config = { .txRingUse = 3U, .rxRingUse = 3U};
    netc_hw_enetc_si_config_t vsi1Config = { .txRingUse = 4U, .rxRingUse = 4U};
    uint32_t vsi0MsixNum = 4U;
    uint32_t vsi1MsixNum = 5U;
    uint8_t vsi0Num;
    uint8_t vsi1Num;
    status_t result;

    switch (si)
    {
        case kNETC_ENETC0PSI0:
            vsi0Num = getSiNum(kNETC_ENETC0VSI0);
            vsi1Num = getSiNum(kNETC_ENETC0VSI1);
            break;
        case kNETC_ENETC1PSI0:
            vsi0Num = getSiNum(kNETC_ENETC1VSI0);
            vsi1Num = getSiNum(kNETC_ENETC1VSI1);
            break;
        case kNETC_ENETC2PSI0:
            vsi0Num = getSiNum(kNETC_ENETC2VSI0);
            vsi1Num = getSiNum(kNETC_ENETC2VSI1);
            break;
        default:
            assert(false);
            break;
    }

    /* RSS key init with generated random values */
    hw->base->PRSSKR0 = 0x995770eaU;
    hw->base->PRSSKR1 = 0x7e8cbbe3U;
    hw->base->PRSSKR2 = 0x9ac8285bU;
    hw->base->PRSSKR3 = 0xce20c189U;
    hw->base->PRSSKR4 = 0xb7ece3ebU;
    hw->base->PRSSKR5 = 0xf8bc2513U;
    hw->base->PRSSKR6 = 0x62613353U;
    hw->base->PRSSKR7 = 0x4c84ae76U;
    hw->base->PRSSKR8 = 0x72c890f1U;
    hw->base->PRSSKR9 = 0xd7a8144bU;

    /* Preinit vsi0 for mac address, BDR num, and MSIX interrupt num */
    NETC_EnetcSetSIMacAddr(hw->base, vsi0Num, macAddr0);

    result = NETC_EnetcSetMsixEntryNum(hw->base, vsi0Num, vsi0MsixNum);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = NETC_EnetcConfigureSI(hw->base, vsi0Num, &vsi0Config);
    if (result != kStatus_Success)
    {
        return result;
    }

    NETC_EnetcEnableSI(hw->base, vsi0Num, true);

    /* Preinit vsi1 for mac address, BDR num, and MSIX interrupt num */
    NETC_EnetcSetSIMacAddr(hw->base, vsi1Num, macAddr1);

    result = NETC_EnetcSetMsixEntryNum(hw->base, vsi1Num, vsi1MsixNum);
    if (result != kStatus_Success)
    {
        return result;
    }

    result = NETC_EnetcConfigureSI(hw->base, vsi1Num, &vsi1Config);
    if (result != kStatus_Success)
    {
        return result;
    }

    NETC_EnetcEnableSI(hw->base, vsi1Num, true);

    return result;
}
