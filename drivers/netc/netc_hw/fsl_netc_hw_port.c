/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_hw_port.h"

bool NETC_PortIsPseudo(NETC_PORT_Type *base)
{
    return ((base->PCAPR & NETC_PORT_PCAPR_LINK_TYPE_MASK) != 0U);
}

void NETC_PortSetMacAddr(NETC_PORT_Type *base, const uint8_t *macAddr)
{
    uint32_t address;

    /* Set physical address lower register. */
    address     = ((uint32_t *)(uintptr_t)macAddr)[0];
    base->PMAR0 = address;

    /* Set physical address high register. */
    address     = ((uint32_t)macAddr[5] << 8U) | (uint32_t)macAddr[4];
    base->PMAR1 = NETC_PORT_PMAR1_PRIM_MAC_ADDR(address);
}

status_t NETC_PortConfig(NETC_PORT_Type *base, const netc_port_common_t *config)
{
    status_t result;

    NETC_PortSetParser(base, &config->parser);
    NETC_PortSetVlanClassify(base, &config->acceptTpid);

    result = NETC_PortSetQosClassify(base, &config->qosMode);
    if (result != kStatus_Success)
    {
        return result;
    }

    (void)NETC_PortConfigTGS(base, &config->timeGate);
    NETC_PortSetIPF(base, &config->ipfCfg);
    NETC_PortSetMacAddr(base, &config->macAddr[0]);
    base->PCR = NETC_PORT_PCR_PSPEED(config->pSpeed) |
#if (defined(FSL_FEATURE_NETC_HAS_PORT_FCSEA) && FSL_FEATURE_NETC_HAS_PORT_FCSEA)
                NETC_PORT_PCR_FCSEA(!config->stompFcs) |
#endif
                NETC_PORT_PCR_TIMER_CS(config->rxTsSelect);
    base->PSGCR = NETC_PORT_PSGCR_OGC(config->ogcMode) | NETC_PORT_PSGCR_PDELAY(config->pDelay);

    /* Configure Port SDU overhead */
    base->PRXSDUOR =
        NETC_PORT_PRXSDUOR_MACSEC_BCO(config->rxMacsecBco) | NETC_PORT_PRXSDUOR_PPDU_BCO(config->rxPpduBco);
    base->PTXSDUOR =
        NETC_PORT_PTXSDUOR_MACSEC_BCO(config->txMacsecBco) | NETC_PORT_PTXSDUOR_PPDU_BCO(config->txPpduBco);
    return kStatus_Success;
}

status_t NETC_PortSetMII(NETC_ETH_LINK_Type *base,
                         netc_hw_mii_mode_t miiMode,
                         netc_hw_mii_speed_t speed,
                         netc_hw_mii_duplex_t duplex)
{
    uint32_t reg = base->PM0_IF_MODE;

    /* Set MAC interface mode */
    reg &= ~NETC_ETH_LINK_PM0_IF_MODE_IFMODE_MASK;
    reg |= NETC_ETH_LINK_PM0_IF_MODE_IFMODE(miiMode);

    /* Set MAC speed and duplex */
    if ((miiMode == kNETC_MiiMode) || (miiMode == kNETC_RmiiMode))
    {
        if (speed == kNETC_MiiSpeed10M)
        {
            reg |= NETC_ETH_LINK_PM0_IF_MODE_M10_MASK;
        }
        else if (speed == kNETC_MiiSpeed100M)
        {
            reg &= ~NETC_ETH_LINK_PM0_IF_MODE_M10_MASK;
        }
        else
        {
            return kStatus_Fail;
        }
        reg &= ~NETC_ETH_LINK_PM0_IF_MODE_HD_MASK;
        reg |= NETC_ETH_LINK_PM0_IF_MODE_HD(duplex != kNETC_MiiFullDuplex);
    }
    else if (miiMode == kNETC_RgmiiMode)
    {
        reg &= ~NETC_ETH_LINK_PM0_IF_MODE_SSP_MASK;
        reg &= ~NETC_ETH_LINK_PM0_IF_MODE_HD_MASK;
        if (speed == kNETC_MiiSpeed1000M)
        {
            reg |= NETC_ETH_LINK_PM0_IF_MODE_SSP(speed);
            reg |= NETC_ETH_LINK_PM0_IF_MODE_HD(0);
        }
        else
        {
            reg |= NETC_ETH_LINK_PM0_IF_MODE_SSP(speed != kNETC_MiiSpeed100M);
            reg |= NETC_ETH_LINK_PM0_IF_MODE_HD(duplex != kNETC_MiiFullDuplex);
        }
    }
    else /* kNETC_GmiiMode, force 1Gbps and full speed */
    {
        if ((speed < kNETC_MiiSpeed1000M) || (duplex != kNETC_MiiFullDuplex))
        {
            return kStatus_InvalidArgument;
        }
    }
    base->PM0_IF_MODE = reg;
    base->PM1_IF_MODE = reg;

    return kStatus_Success;
}

status_t NETC_PortSetMaxFrameSize(NETC_ETH_LINK_Type *base, uint16_t size)
{
    /* The MAC supports reception of any frame size up to 2000 bytes. */
    if (size > NETC_PORT_MAX_FRAME_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    base->PM0_MAXFRM = NETC_ETH_LINK_PM0_MAXFRM_MAXFRM(size);
    base->PM1_MAXFRM = NETC_ETH_LINK_PM1_MAXFRM_MAXFRM(size);

    return kStatus_Success;
}

status_t NETC_PortConfigEthMac(NETC_ETH_LINK_Type *base, const netc_port_ethmac_t *config)
{
    uint32_t reg = 0;
    status_t result;

    if ((config->rxMinFrameSize < NETC_PORT_MIN_FRAME_SIZE) || (config->rxMaxFrameSize > NETC_PORT_MAX_FRAME_SIZE) ||
        (config->rxMinFrameSize > config->rxMaxFrameSize))
    {
        return kStatus_InvalidArgument;
    }

    /* Set Rx Frame Maximum/Minimum Length */
    result = NETC_PortSetMaxFrameSize(base, config->rxMaxFrameSize);
    if (result != kStatus_Success)
    {
        return result;
    }
#if defined(NETC_ETH_LINK_PM0_MINFRM_NUM_BYTES_MASK)
    base->PM0_MINFRM = NETC_ETH_LINK_PM0_MINFRM_NUM_BYTES(config->rxMinFrameSize);
#endif
#if defined(NETC_ETH_LINK_PM1_MINFRM_NUM_BYTES_MASK)
    base->PM1_MINFRM = NETC_ETH_LINK_PM1_MINFRM_NUM_BYTES(config->rxMinFrameSize);
#endif

    /* Set MAC interface mode, speed and duplex */
    result = NETC_PortSetMII(base, config->miiMode, config->miiSpeed, config->miiDuplex);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Enable reverse mode */
    reg = base->PM0_IF_MODE;
    if (config->enableRevMii)
    {
        reg |= NETC_ETH_LINK_PM0_IF_MODE_REVMII_MASK;
    }
    else
    {
        reg &= ~NETC_ETH_LINK_PM0_IF_MODE_REVMII_MASK;
    }
    /* Enable RGMII Tx clock stop status during low power idle.  */
    if (config->rgmiiClkStop)
    {
        reg |= NETC_ETH_LINK_PM0_IF_MODE_CLK_STOP_MASK;
    }
    else
    {
        reg &= ~NETC_ETH_LINK_PM0_IF_MODE_CLK_STOP_MASK;
    }
    base->PM0_IF_MODE = reg;
    base->PM1_IF_MODE = reg;

    base->MAC_MERGE_MMCSR = NETC_ETH_LINK_MAC_MERGE_MMCSR_VT(config->mergeVerifyTime) |
                            NETC_ETH_LINK_MAC_MERGE_MMCSR_VDIS(!config->enMergeVerify) |
                            NETC_ETH_LINK_MAC_MERGE_MMCSR_ME(config->preemptMode);

#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
    reg = NETC_ETH_LINK_PM0_SINGLE_STEP_CH(config->enChUpdate) |
          NETC_ETH_LINK_PM0_SINGLE_STEP_OFFSET(config->oneStepOffset) |
          NETC_ETH_LINK_PM0_SINGLE_STEP_EN(config->enOneStepTS);
    base->PM0_SINGLE_STEP = reg;
    base->PM1_SINGLE_STEP = reg;
#endif

    /* Enable Tx/Rx */
    reg = NETC_ETH_LINK_PM0_COMMAND_CONFIG_TX_EN_MASK | NETC_ETH_LINK_PM0_COMMAND_CONFIG_RX_EN_MASK |
          NETC_ETH_LINK_PM0_COMMAND_CONFIG_TS_MODE(config->txTsSelect) |
          NETC_ETH_LINK_PM0_COMMAND_CONFIG_TS_PNT(config->isTsPointPhy) |
          NETC_ETH_LINK_PM0_COMMAND_CONFIG_HD_FCEN(config->enableHalfDuplexFlowCtrl) |
          NETC_ETH_LINK_PM0_COMMAND_CONFIG_TXP(config->enTxPad);
    base->PM0_COMMAND_CONFIG = reg;
    base->PM1_COMMAND_CONFIG = reg;

    if (config->enableHalfDuplexFlowCtrl)
    {
        assert((config->maxBackPressOn <= 3036U) && (config->minBackPressOff <= 20U));
        reg = NETC_ETH_LINK_PM0_HD_FLOW_CTRL_HD_BP_ON_MAX(config->maxBackPressOn) |
              NETC_ETH_LINK_PM0_HD_FLOW_CTRL_HD_BP_OFF_MIN(config->minBackPressOff);
        base->PM0_HD_FLOW_CTRL = reg;
        base->PM1_HD_FLOW_CTRL = reg;
    }

    return kStatus_Success;
}

uint32_t NETC_GetPortMacInterruptFlags(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType)
{
    if (macType == kNETC_ExpressMAC)
    {
        return base->PM0_IEVENT;
    }
    else
    {
        return base->PM1_IEVENT;
    }
}

void NETC_ClearPortMacInterruptFlags(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType, uint32_t mask)
{
    if (macType == kNETC_ExpressMAC)
    {
        base->PM0_IEVENT |= mask;
    }
    else
    {
        base->PM1_IEVENT |= mask;
    }
}

void NETC_EnablePortMacInterrupts(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType, uint32_t mask, bool enable)
{
    if (macType == kNETC_ExpressMAC)
    {
        if (enable)
        {
            base->PM0_IMASK |= mask;
        }
        else
        {
            base->PM0_IMASK &= ~mask;
        }
    }
    else
    {
        if (enable)
        {
            base->PM1_IMASK |= mask;
        }
        else
        {
            base->PM1_IMASK &= ~mask;
        }
    }
}

status_t NETC_PortEnableLoopback(NETC_ETH_LINK_Type *base, netc_port_loopback_mode_t loopMode, bool enable)
{
    uint32_t reg = base->PM0_COMMAND_CONFIG;

    if (enable)
    {
        reg &= ~NETC_ETH_LINK_PM0_COMMAND_CONFIG_LPBK_MODE_MASK;
        reg |= NETC_ETH_LINK_PM0_COMMAND_CONFIG_LOOP_ENA_MASK | NETC_ETH_LINK_PM0_COMMAND_CONFIG_LPBK_MODE(loopMode);
    }
    else
    {
        reg &= ~NETC_ETH_LINK_PM0_COMMAND_CONFIG_LOOP_ENA_MASK;
    }

    base->PM0_COMMAND_CONFIG = reg;
    base->PM1_COMMAND_CONFIG = reg;

    return kStatus_Success;
}

void NETC_PortGetDiscardStatistic(NETC_PORT_Type *base,
                                  netc_port_discard_tpye_t discardType,
                                  netc_port_discard_statistic_t *statistic)
{
    switch (discardType)
    {
        case kNETC_RxDiscard:
            statistic->count   = base->PRXDCR;
            statistic->reason0 = base->PRXDCRR0;
            statistic->reason1 = base->PRXDCRR1;
            break;
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        case kNETC_TxDiscard:
            statistic->count   = base->PTXDCR;
            statistic->reason0 = base->PTXDCRR0;
            statistic->reason1 = base->PTXDCRR1;
            break;
        case kNETC_BridgeDiscard:
            statistic->count   = base->BPDCR;
            statistic->reason0 = base->BPDCRR0;
            statistic->reason1 = base->BPDCRR1;
            break;
#endif
        default:
            assert(false);
            break;
    }
}

void NETC_PortClearDiscardReason(NETC_PORT_Type *base,
                                 netc_port_discard_tpye_t discardType,
                                 uint32_t reason0,
                                 uint32_t reason1)
{
    switch (discardType)
    {
        case kNETC_RxDiscard:
            base->PRXDCRR0 = reason0;
            base->PRXDCRR1 = reason1;
            break;
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        case kNETC_TxDiscard:
            base->PTXDCRR0 = reason0;
            base->PTXDCRR1 = reason1;
            break;
        case kNETC_BridgeDiscard:
            base->BPDCRR0 = reason0;
            base->BPDCRR1 = reason1;
            break;
#endif
        default:
            assert(false);
            break;
    }
}

void NETC_PortGetPhyMacTxStatistic(NETC_ETH_LINK_Type *base,
                                   netc_port_phy_mac_type_t macType,
                                   netc_port_phy_mac_traffic_statistic_t *statistic)
{
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    uint32_t primask;

    primask = DisableGlobalIRQ();
#endif
    statistic->rxMinPacket = 0;
    if (macType == kNETC_ExpressMAC)
    {
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051711) && FSL_FEATURE_NETC_HAS_ERRATA_051711
        /* ERRATA051711: MAC statistic counters TEOCT and TOCT are inaccurate after Pause frames are transmitted with
           flexible preamble enabled (PM0_TX_IPG_PREAMBLE[FLEX_PREAMBLE_EN] = 1) and flexible preamble count
           (PM0_TX_IPG_PREAMBLE[FLEX_PREAMBLE_CNT]) set to less than 7. */
        uint32_t flexPreambleCnt = (base->PM0_TX_IPG_PREAMBLE & NETC_ETH_LINK_PM0_TX_IPG_PREAMBLE_FLEX_PREAMBLE_CNT_MASK) >> NETC_ETH_LINK_PM0_TX_IPG_PREAMBLE_FLEX_PREAMBLE_CNT_SHIFT;
        if ((base->PM0_TX_IPG_PREAMBLE & NETC_ETH_LINK_PM0_TX_IPG_PREAMBLE_FLEX_PREAMBLE_EN_MASK) != 0U)
        {
            statistic->totalOctet = base->PM0_TEOCTN - base->PM0_TXPFN * ((uint64_t)7U - flexPreambleCnt);
            statistic->validOctet = base->PM0_TOCTN - base->PM0_TXPFN * ((uint64_t)7U - flexPreambleCnt);
        }
        else
        {
            statistic->totalOctet = base->PM0_TEOCTN;
            statistic->validOctet = base->PM0_TOCTN;
        }
#else
        statistic->totalOctet = base->PM0_TEOCTN;
        statistic->validOctet = base->PM0_TOCTN;
#endif
        statistic->pauseFrame             = base->PM0_TXPFN;
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051710) && FSL_FEATURE_NETC_HAS_ERRATA_051710
        /* ERRATA051710: After one or more late collision or excessive collision events, counters PMa_TOCTn and PMa_TFRMn will be higher than
           expected. The accurate value cannot be recovered for PMa_TOCTn, but PMa_TRFMn can be recovered as follows formula. */
        statistic->validFrame             = base->PM0_TFRMN - base->PM0_TLCOLN - base->PM0_TECOLN;
#else
        statistic->validFrame             = base->PM0_TFRMN;
#endif
        statistic->vlanFrame              = base->PM0_TVLANN;
        statistic->unicastFrame           = base->PM0_TUCAN;
        statistic->multicastFrame         = base->PM0_TMCAN;
        statistic->boradcastFrame         = base->PM0_TBCAN;
        statistic->totalPacket            = base->PM0_TPKTN;
        statistic->total64BPacket         = base->PM0_T64N;
        statistic->total65To127BPacket    = base->PM0_T127N;
        statistic->total128To255BPacket   = base->PM0_T255N;
        statistic->total256To511BPacket   = base->PM0_T511N;
        statistic->total511To1023BPacket  = base->PM0_T1023N;
        statistic->total1024To1522BPacket = base->PM0_T1522N;
        statistic->total1523ToMaxBPacket  = base->PM0_T1523XN;
        statistic->controlPacket          = base->PM0_TCNPN;
    }
    else if (macType == kNETC_PreemptableMAC)
    {
        statistic->totalOctet             = base->PM1_TEOCTN;
        statistic->validOctet             = base->PM1_TOCTN;
        statistic->pauseFrame             = base->PM1_TXPFN;
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051710) && FSL_FEATURE_NETC_HAS_ERRATA_051710
        /* ERRATA051710: After one or more late collision or excessive collision events, counters PMa_TOCTn and PMa_TFRMn will be higher than
           expected. The accurate value cannot be recovered for PMa_TOCTn, but PMa_TRFMn can be recovered as follows formula. */
        statistic->validFrame             = base->PM1_TFRMN - base->PM1_TLCOLN - base->PM1_TECOLN;
#else
        statistic->validFrame             = base->PM1_TFRMN;
#endif
        statistic->vlanFrame              = base->PM1_TVLANN;
        statistic->unicastFrame           = base->PM1_TUCAN;
        statistic->multicastFrame         = base->PM1_TMCAN;
        statistic->boradcastFrame         = base->PM1_TBCAN;
        statistic->totalPacket            = base->PM1_TPKTN;
        statistic->total64BPacket         = base->PM1_T64N;
        statistic->total65To127BPacket    = base->PM1_T127N;
        statistic->total128To255BPacket   = base->PM1_T255N;
        statistic->total256To511BPacket   = base->PM1_T511N;
        statistic->total511To1023BPacket  = base->PM1_T1023N;
        statistic->total1024To1522BPacket = base->PM1_T1522N;
        statistic->total1523ToMaxBPacket  = base->PM1_T1523XN;
        statistic->controlPacket          = base->PM1_TCNPN;
    }
    else
    {
        ; /* Intentional empty */
    }

#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    EnableGlobalIRQ(primask);
#endif
}

void NETC_PortGetPhyMacRxStatistic(NETC_ETH_LINK_Type *base,
                                   netc_port_phy_mac_type_t macType,
                                   netc_port_phy_mac_traffic_statistic_t *statistic)
{
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    uint32_t primask;

    primask = DisableGlobalIRQ();
#endif

    if (macType == kNETC_ExpressMAC)
    {
        statistic->totalOctet             = base->PM0_REOCTN;
        statistic->validOctet             = base->PM0_ROCTN;
        statistic->pauseFrame             = base->PM0_RXPFN;
        statistic->validFrame             = base->PM0_RFRMN;
        statistic->vlanFrame              = base->PM0_RVLANN;
        statistic->unicastFrame           = base->PM0_RUCAN;
        statistic->multicastFrame         = base->PM0_RMCAN;
        statistic->boradcastFrame         = base->PM0_RBCAN;
        statistic->totalPacket            = base->PM0_RPKTN;
        statistic->total64BPacket         = base->PM0_R64N;
        statistic->total65To127BPacket    = base->PM0_R127N;
        statistic->total128To255BPacket   = base->PM0_R255N;
        statistic->total256To511BPacket   = base->PM0_R511N;
        statistic->total511To1023BPacket  = base->PM0_R1023N;
        statistic->total1024To1522BPacket = base->PM0_R1522N;
        statistic->total1523ToMaxBPacket  = base->PM0_R1523XN;
        statistic->controlPacket          = base->PM0_RCNPN;
#if defined(NETC_ETH_LINK_PM0_RMIN63N_RMIN63n_MASK)
        statistic->rxMinPacket            = base->PM0_RMIN63N;
#endif
    }
    else if (macType == kNETC_PreemptableMAC)
    {
        statistic->totalOctet             = base->PM1_REOCTN;
        statistic->validOctet             = base->PM1_ROCTN;
        statistic->pauseFrame             = base->PM1_RXPFN;
        statistic->validFrame             = base->PM1_RFRMN;
        statistic->vlanFrame              = base->PM1_RVLANN;
        statistic->unicastFrame           = base->PM1_RUCAN;
        statistic->multicastFrame         = base->PM1_RMCAN;
        statistic->boradcastFrame         = base->PM1_RBCAN;
        statistic->totalPacket            = base->PM1_RPKTN;
        statistic->total64BPacket         = base->PM1_R64N;
        statistic->total65To127BPacket    = base->PM1_R127N;
        statistic->total128To255BPacket   = base->PM1_R255N;
        statistic->total256To511BPacket   = base->PM1_R511N;
        statistic->total511To1023BPacket  = base->PM1_R1023N;
        statistic->total1024To1522BPacket = base->PM1_R1522N;
        statistic->total1523ToMaxBPacket  = base->PM1_R1523XN;
        statistic->controlPacket          = base->PM1_RCNPN;
#if defined(NETC_ETH_LINK_PM1_RMIN63N_RMIN63n_MASK)
        statistic->rxMinPacket            = base->PM1_RMIN63N;
#endif
    }
    else
    {
        ; /* Intentional empty */
    }

#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    EnableGlobalIRQ(primask);
#endif
}

void NETC_PortGetPhyMacDiscardStatistic(NETC_ETH_LINK_Type *base,
                                        netc_port_phy_mac_type_t macType,
                                        netc_port_phy_mac_discard_statistic_t *statistic)
{
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    uint32_t primask;

    primask = DisableGlobalIRQ();
#endif
    if (macType == kNETC_ExpressMAC)
    {
        statistic->rxError              = base->PM0_RERRN;
        statistic->rxUndersized         = base->PM0_RUNDN;
        statistic->rxOversized          = base->PM0_ROVRN;
        statistic->rxErrorFCS           = base->PM0_RFCSN;
        statistic->rxFragment           = base->PM0_RFRGN;
        statistic->rxJabber             = base->PM0_RJBRN;
        statistic->rxDiscard            = base->PM0_RDRPN;
        statistic->rxDiscardNoTruncated = base->PM0_RDRNTPN;
        statistic->txErrorFCS           = base->PM0_TERRN;
        statistic->txUndersized         = base->PM0_TUNDN;
    }
    else if (macType == kNETC_PreemptableMAC)
    {
        statistic->rxError              = base->PM1_RERRN;
        statistic->rxUndersized         = base->PM1_RUNDN;
        statistic->rxOversized          = base->PM1_ROVRN;
        statistic->rxErrorFCS           = base->PM1_RFCSN;
        statistic->rxFragment           = base->PM1_RFRGN;
        statistic->rxJabber             = base->PM1_RJBRN;
        statistic->rxDiscard            = base->PM1_RDRPN;
        statistic->rxDiscardNoTruncated = base->PM1_RDRNTPN;
        statistic->txErrorFCS           = base->PM1_TERRN;
        statistic->txUndersized         = base->PM1_TUNDN;
    }
    else
    {
        ; /* Intentional empty */
    }
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    EnableGlobalIRQ(primask);
#endif
}

void NETC_PortGetPhyMacPreemptionStatistic(NETC_ETH_LINK_Type *base,
                                           netc_port_phy_mac_preemption_statistic_t *statistic)
{
    statistic->rxReassembledFrame = base->MAC_MERGE_MMFAOCR;
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051707) && FSL_FEATURE_NETC_HAS_ERRATA_051707
    /* ERRATA051707: The host that is reading MAC_MERGE_MMFAECR register should check status of PM1_RFCS. If the PM1_RFCS indicates no
       error then MAC_MERGE_MMFAECR is valid and can be used if on other hand there is an error reported in PM1_RFCS register
       then MAC_MERGE_MMFAECR might be incorrect and should be treated accordingly. */
    statistic->rxReassembledError = (base->PM1_RFCSN == 0U) ? base->MAC_MERGE_MMFAECR : 0U;
#else
    statistic->rxReassembledError = base->MAC_MERGE_MMFAECR;
#endif
    statistic->rxMPacket          = base->MAC_MERGE_MMFCRXR;
    statistic->rxSMDError         = base->MAC_MERGE_MMFSECR;
    statistic->txPreemptionReq    = base->MAC_MERGE_MMHCR;
    statistic->txMPacket          = base->MAC_MERGE_MMFCTXR;
}

#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
void NETC_PortGetPseudoMacTrafficStatistic(NETC_PSEUDO_LINK_Type *base,
                                           bool getTx,
                                           netc_port_pseudo_mac_traffic_statistic_t *statistic)
{
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    uint32_t primask;

    primask = DisableGlobalIRQ();
#endif
    if (getTx)
    {
        statistic->totalOctet     = ((uint64_t)base->PPMTOCR[1] << 32U) | base->PPMTOCR[0];
        statistic->unicastFrame   = ((uint64_t)base->PPMTUFCR[1] << 32U) | base->PPMTUFCR[0];
        statistic->multicastFrame = ((uint64_t)base->PPMTMFCR[1] << 32U) | base->PPMTMFCR[0];
        statistic->boradcastFrame = ((uint64_t)base->PPMTBFCR[1] << 32U) | base->PPMTBFCR[0];
    }
    else
    {
        statistic->totalOctet     = ((uint64_t)base->PPMROCR[1] << 32U) | base->PPMROCR[0];
        statistic->unicastFrame   = ((uint64_t)base->PPMRUFCR[1] << 32U) | base->PPMRUFCR[0];
        statistic->multicastFrame = ((uint64_t)base->PPMRMFCR[1] << 32U) | base->PPMRMFCR[0];
        statistic->boradcastFrame = ((uint64_t)base->PPMRBFCR[1] << 32U) | base->PPMRBFCR[0];
    }
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_050679) && FSL_FEATURE_NETC_HAS_ERRATA_050679)
    EnableGlobalIRQ(primask);
#endif
}
#endif

status_t NETC_PortConfigTcCBS(NETC_PORT_Type *base, netc_hw_tc_idx_t tcIdx, const netc_port_tc_cbs_config_t *config)
{
    status_t result = kStatus_Success;
    uint8_t usedBw  = 0U;
    uint8_t index;

    for (index = (uint8_t)kNETC_TxTC0; index <= (uint8_t)kNETC_TxTC7; index++)
    {
        if (index == (uint8_t)tcIdx)
        {
            continue;
        }

        if (0U != (base->TCT_NUM[index].PTCCBSR0 & NETC_PORT_PTCCBSR0_CBSE_MASK))
        {
            usedBw += (uint8_t)(base->TCT_NUM[index].PTCCBSR0 & NETC_PORT_PTCCBSR0_BW_MASK);
        }
    }

    if ((usedBw + config->bwWeight) <= 100U)
    {
        base->TCT_NUM[tcIdx].PTCCBSR0 = NETC_PORT_PTCCBSR0_BW(config->bwWeight) | NETC_PORT_PTCCBSR0_CBSE_MASK;
        base->TCT_NUM[tcIdx].PTCCBSR1 = NETC_PORT_PTCCBSR1_HI_CREDIT(config->hiCredit);
    }
    else
    {
        /* The sum of all traffic class credit-based shaper's bandwidth cannot execeed 100 */
        result = kStatus_Fail;
    }

    return result;
}

void NETC_PortEthMacGracefulStop(NETC_PORT_Type *base)
{
    NETC_ETH_LINK_Type *eth = (NETC_ETH_LINK_Type *)((uintptr_t)base + 0x1000U);
    bool hasPM1             = 0U != (eth->MAC_MERGE_MMCSR & NETC_ETH_LINK_MAC_MERGE_MMCSR_ME_MASK);

    /* In order to stop receive */
    eth->PM0_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM0_COMMAND_CONFIG_RX_EN_MASK;
    while (0U == (eth->PM0_IEVENT & NETC_ETH_LINK_PM0_IEVENT_RX_EMPTY_MASK))
    {
    }
    if (hasPM1)
    {
        eth->PM1_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM1_COMMAND_CONFIG_RX_EN_MASK;
        while (0U == (eth->PM1_IEVENT & NETC_ETH_LINK_PM1_IEVENT_RX_EMPTY_MASK))
        {
        }
    }
    while (0U != (base->PSR & NETC_PORT_PSR_RX_BUSY_MASK))
    {
    }
    base->POR |= NETC_PORT_POR_RXDIS_MASK;

    /* In order to stop transmit */
    base->POR |= NETC_PORT_POR_TXDIS_MASK;
    while (0U == (eth->PM0_IEVENT & NETC_ETH_LINK_PM0_IEVENT_TX_EMPTY_MASK))
    {
    }
    if (hasPM1)
    {
        while (0U == (eth->PM1_IEVENT & NETC_ETH_LINK_PM1_IEVENT_TX_EMPTY_MASK))
        {
        }
    }
    /* Wait 64 byte time for Tx packet transmission to complete.  */
    SDK_DelayAtLeastUs(512, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    eth->PM0_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM0_COMMAND_CONFIG_TX_EN_MASK;
    if (hasPM1)
    {
        eth->PM1_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM1_COMMAND_CONFIG_TX_EN_MASK;
    }
}
