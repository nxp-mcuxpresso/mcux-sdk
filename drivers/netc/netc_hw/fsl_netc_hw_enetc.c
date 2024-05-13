/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_hw_enetc.h"

void NETC_EnetcGetCapability(NETC_ENETC_Type *base, netc_enetc_cap_t *capability)
{
    uint32_t cap;

    cap                    = base->ECAPR0;
    capability->funcSafety = ((cap & NETC_ENETC_ECAPR0_FS_MASK) != 0U);
    capability->wol        = ((cap & NETC_ENETC_ECAPR0_WO_MASK) != 0U);
    capability->rss        = ((cap & NETC_ENETC_ECAPR0_RSS_MASK) != 0U);
    capability->tsd        = ((cap & NETC_ENETC_ECAPR0_TSD_MASK) != 0U);
    capability->rfs        = ((cap & NETC_ENETC_ECAPR0_RFS_MASK) != 0U);

    cap                 = base->ECAPR1;
    capability->ipvNum  = ((cap & NETC_ENETC_ECAPR1_NUM_IPV_MASK) != 0U) ? 16U : 8U;
    capability->vsiNum  = (cap & NETC_ENETC_ECAPR1_NUM_VSI_MASK) >> NETC_ENETC_ECAPR1_NUM_VSI_SHIFT;
    capability->msixNum = (cap & NETC_ENETC_ECAPR1_NUM_MSIX_MASK) >> NETC_ENETC_ECAPR1_NUM_MSIX_SHIFT;
    capability->tcsNum  = 1U + ((cap & NETC_ENETC_ECAPR1_NUM_TCS_MASK) >> NETC_ENETC_ECAPR1_NUM_TCS_SHIFT);
    capability->uchNum =
        64U * ((uint16_t)1U << ((cap & NETC_ENETC_ECAPR1_NUM_UCH_MASK) >> NETC_ENETC_ECAPR1_NUM_UCH_SHIFT));
    capability->mchNum =
        64U * ((uint16_t)1U << ((cap & NETC_ENETC_ECAPR1_NUM_MCH_MASK) >> NETC_ENETC_ECAPR1_NUM_MCH_SHIFT));

    cap                  = base->ECAPR2;
    capability->rxBdrNum = (uint16_t)((cap & NETC_ENETC_ECAPR2_NUM_RX_BDR_MASK) >> NETC_ENETC_ECAPR2_NUM_RX_BDR_SHIFT);
    capability->txBdrNum = (uint16_t)(cap & NETC_ENETC_ECAPR2_NUM_TX_BDR_MASK);
}

void NETC_EnetcSetSIMacAddr(NETC_ENETC_Type *base, uint8_t si, uint8_t *macAddr)
{
    /* This API is for VSI. */
    assert(si != 0U);

    uint32_t address;

    /* Set physical address lower register. */
    address                   = ((uint32_t *)(uintptr_t)macAddr)[0];
    base->NUM_SI[si].PSIPMAR0 = address;

    /* Set physical address high register. */
    address                   = (((uint32_t)macAddr[5] << 8U) | (uint32_t)macAddr[4]);
    base->NUM_SI[si].PSIPMAR1 = address;
}

status_t NETC_EnetcConfigureSI(NETC_ENETC_Type *base, uint8_t si, const netc_hw_enetc_si_config_t *psConfig)
{
    uint16_t txBdrMax =
        (uint16_t)((base->ECAPR2 & NETC_ENETC_ECAPR2_NUM_TX_BDR_MASK) >> NETC_ENETC_ECAPR2_NUM_TX_BDR_SHIFT);
    uint16_t rxBdrMax =
        (uint16_t)((base->ECAPR2 & NETC_ENETC_ECAPR2_NUM_RX_BDR_MASK) >> NETC_ENETC_ECAPR2_NUM_RX_BDR_SHIFT);
    uint16_t siMax =
        (uint16_t)(1U + ((base->ECAPR1 & NETC_ENETC_ECAPR1_NUM_VSI_MASK) >> NETC_ENETC_ECAPR1_NUM_VSI_SHIFT));
    uint16_t txLeftBdr = txBdrMax;
    uint16_t rxLeftBdr = rxBdrMax;

    /* SI index ranges from 0 ~ max-1. */
    if (si >= siMax)
    {
        return kStatus_InvalidArgument;
    }

    /* Minus the ring number used by SIs in front. */
    for (uint8_t i = 0; i < si; i++)
    {
        txLeftBdr -= (uint16_t)((base->NUM_SI[i].PSICFGR0 & NETC_ENETC_PSICFGR0_NUM_TX_BDR_MASK) >>
                                NETC_ENETC_PSICFGR0_NUM_TX_BDR_SHIFT);
        rxLeftBdr -= (uint16_t)((base->NUM_SI[i].PSICFGR0 & NETC_ENETC_PSICFGR0_NUM_RX_BDR_MASK) >>
                                NETC_ENETC_PSICFGR0_NUM_RX_BDR_SHIFT);
    }

    if ((psConfig->txRingUse > txLeftBdr) || (psConfig->rxRingUse > rxLeftBdr))
    {
        return kStatus_NETC_LackOfResource;
    }

    /* Configure the station interface. */
    if ((NETC_EnetcHasManagement(base)) && (si == 0U))
    {
        /* Management ENETC SI 0 need allocated one more Tx/Rx ring to do the Switch management frames send and receive.
         */
        base->NUM_SI[si].PSICFGR0 =
            NETC_ENETC_PSICFGR0_SIBW(psConfig->bandWeight) | NETC_ENETC_PSICFGR0_SIVC(psConfig->vlanCtrl) |
            NETC_ENETC_PSICFGR0_ASE(psConfig->antiSpoofEnable) | NETC_ENETC_PSICFGR0_SIVIE(psConfig->vlanInsertEnable) |
            NETC_ENETC_PSICFGR0_VTE(psConfig->vlanExtractEnable) |
            NETC_ENETC_PSICFGR0_SPE(psConfig->sourcePruneEnable) |
            NETC_ENETC_PSICFGR0_NUM_TX_BDR(psConfig->txRingUse + 1U) |
            NETC_ENETC_PSICFGR0_NUM_RX_BDR(psConfig->rxRingUse + 1U);
    }
    else
    {
        base->NUM_SI[si].PSICFGR0 =
            NETC_ENETC_PSICFGR0_SIBW(psConfig->bandWeight) | NETC_ENETC_PSICFGR0_SIVC(psConfig->vlanCtrl) |
            NETC_ENETC_PSICFGR0_ASE(psConfig->antiSpoofEnable) | NETC_ENETC_PSICFGR0_SIVIE(psConfig->vlanInsertEnable) |
            NETC_ENETC_PSICFGR0_VTE(psConfig->vlanExtractEnable) |
            NETC_ENETC_PSICFGR0_SPE(psConfig->sourcePruneEnable) | NETC_ENETC_PSICFGR0_NUM_TX_BDR(psConfig->txRingUse) |
            NETC_ENETC_PSICFGR0_NUM_RX_BDR(psConfig->rxRingUse);
    }

    base->NUM_SI[si].PSIVLANR =
        NETC_ENETC_PSIVLANR_E(psConfig->enSIBaseVlan) | NETC_ENETC_PSIVLANR_TPID(psConfig->siBaseVlan.tpid) |
        NETC_ENETC_PSIVLANR_PCP(psConfig->siBaseVlan.pcp) | NETC_ENETC_PSIVLANR_DEI(psConfig->siBaseVlan.dei) |
        NETC_ENETC_PSIVLANR_VID(psConfig->siBaseVlan.vid);

    return kStatus_Success;
}

status_t NETC_EnetcSetMsixEntryNum(NETC_ENETC_Type *base, uint8_t si, uint32_t msixNum)
{
    status_t result = kStatus_Success;
    uint16_t msixEntryMax =
        (uint16_t)(((base->ECAPR1 & NETC_ENETC_ECAPR1_NUM_MSIX_MASK) >> NETC_ENETC_ECAPR1_NUM_MSIX_SHIFT) + 1U);
    uint16_t leftEntry = msixEntryMax;
    uint32_t entryNum;

    /* Minus the MSIX entry used by SIs in front. */
    for (uint8_t i = 0; i < si; i++)
    {
        leftEntry -= (uint16_t)(1U + ((base->NUM_SI[i].PSICFGR2 & NETC_ENETC_PSICFGR2_NUM_MSIX_MASK) >>
                                      NETC_ENETC_PSICFGR2_NUM_MSIX_SHIFT));
    }

    if (msixNum > leftEntry)
    {
        result = kStatus_NETC_LackOfResource;
    }
    else
    {
        entryNum                  = (msixNum != 0U) ? msixNum : 1U;
        base->NUM_SI[si].PSICFGR2 = NETC_ENETC_PSICFGR2_NUM_MSIX(entryNum - 1U);
    }

    return result;
}

void NETC_EnetcGetPortDiscardStatistic(NETC_ENETC_Type *base, netc_enetc_port_discard_statistic_t *statistic)
{
    for (uint32_t i = 0U; i < 4U; i++)
    {
        statistic->ingressDR[i] = base->PICDRADCR[i].PICDRDCR;
    }
    statistic->broadcastReject   = base->PBFDSIR;
    statistic->smacPruning       = base->PFDMSAPR;
    statistic->unicastMacFilt    = base->PUFDMFR;
    statistic->multicastMacFilt  = base->PMFDMFR;
    statistic->unicastVlanFilt   = base->PUFDVFR;
    statistic->multicastVlanFilt = base->PMFDVFR;
    statistic->boradcastVlanFilt = base->PBFDVFR;
}

void NETC_EnetcEnablePromiscuous(NETC_ENETC_Type *base, uint8_t si, bool enableUCPromis, bool enableMCPromis)
{
    if (enableUCPromis)
    {
        base->PSIPMMR |= ((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_UP_MASK << si);
    }
    else
    {
        base->PSIPMMR &= ~((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_UP_MASK << si);
    }

    if (enableMCPromis)
    {
        base->PSIPMMR |= ((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_MP_MASK << si);
    }
    else
    {
        base->PSIPMMR &= ~((uint32_t)NETC_ENETC_PSIPMMR_SI0_MAC_MP_MASK << si);
    }
}

void NETC_EnetcConfigureVlanFilter(NETC_ENETC_Type *base, uint8_t si, netc_si_l2vf_config_t *config)
{
    if (config->acceptUntagged)
    {
        base->PSIPVMR |= ((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_UTA_MASK << si);
    }
    else
    {
        base->PSIPVMR &= ~((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_UTA_MASK << si);
    }

    if (config->enPromis)
    {
        base->PSIPVMR |= ((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_P_MASK << si);
    }
    else
    {
        base->PSIPVMR &= ~((uint32_t)NETC_ENETC_PSIPVMR_SI0_VLAN_P_MASK << si);
    }

    base->PSIVLANFMR = NETC_ENETC_PSIVLANFMR_VS(config->useOuterVlanTag);
}

void NETC_EnetcAddMacAddrHash(NETC_ENETC_Type *base, uint8_t si, netc_packet_type_t type, uint8_t hashIndex)
{
    assert(type != kNETC_PacketBroadcast);

    if (type == kNETC_PacketUnicast)
    {
        if (hashIndex < 32U)
        {
            base->NUM_SI[si].PSIUMHFR0 |= ((uint32_t)1U << hashIndex);
        }
        else
        {
            base->NUM_SI[si].PSIUMHFR1 |= ((uint32_t)1U << (hashIndex - 32U));
        }
    }
    else
    {
        if (hashIndex < 32U)
        {
            base->NUM_SI[si].PSIMMHFR0 |= ((uint32_t)1U << hashIndex);
        }
        else
        {
            base->NUM_SI[si].PSIMMHFR1 |= ((uint32_t)1U << (hashIndex - 32U));
        }
    }
}

void NETC_EnetcDelMacAddrHash(NETC_ENETC_Type *base, uint8_t si, netc_packet_type_t type, uint8_t hashIndex)
{
    assert(type != kNETC_PacketBroadcast);

    if (type == kNETC_PacketUnicast)
    {
        if (hashIndex < 32U)
        {
            base->NUM_SI[si].PSIUMHFR0 &= ~((uint32_t)1U << hashIndex);
        }
        else
        {
            base->NUM_SI[si].PSIUMHFR1 &= ~((uint32_t)1U << (hashIndex - 32U));
        }
    }
    else
    {
        if (hashIndex < 32U)
        {
            base->NUM_SI[si].PSIMMHFR0 &= ~((uint32_t)1U << hashIndex);
        }
        else
        {
            base->NUM_SI[si].PSIMMHFR1 &= ~((uint32_t)1U << (hashIndex - 32U));
        }
    }
}

void NETC_EnetcAddVlanHash(NETC_ENETC_Type *base, uint8_t si, uint8_t hashIndex)
{
    if (hashIndex < 32U)
    {
        base->NUM_SI[si].PSIVHFR0 |= ((uint32_t)1U << hashIndex);
    }
    else
    {
        base->NUM_SI[si].PSIVHFR1 |= ((uint32_t)1U << (hashIndex - 32U));
    }
}

void NETC_EnetcDelVlanHash(NETC_ENETC_Type *base, uint8_t si, uint8_t hashIndex)
{
    if (hashIndex < 32U)
    {
        base->NUM_SI[si].PSIVHFR0 &= ~((uint32_t)1U << hashIndex);
    }
    else
    {
        base->NUM_SI[si].PSIVHFR1 &= ~((uint32_t)1U << (hashIndex - 32U));
    }
}
