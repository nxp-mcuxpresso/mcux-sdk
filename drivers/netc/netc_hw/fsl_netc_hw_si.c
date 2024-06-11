/*
 * Copyright 2021-2022, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_hw_si.h"

status_t NETC_SIConfigTxBDR(ENETC_SI_Type *base, uint8_t ring, const netc_tx_bdr_config_t *bdrConfig)
{
    uint64_t address;

    /* Set the MSIX entry index triggered when interrupt occurs. */
    base->SIMSITRVR[ring] = bdrConfig->msixEntryIdx;

    /* Map function only supports 32-bit now, so here limit 32-bit first */
    address = (uintptr_t)bdrConfig->bdArray;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_Local2DMA);
#endif

    /* Set the tx descriptor start/tail pointer, shall be word aligned. */
    base->BDR[ring].TBBAR0 = NETC_ADDR_LOW_32BIT(address);
    base->BDR[ring].TBBAR1 = NETC_ADDR_HIGH_32BIT(address);
    base->BDR[ring].TBPIR  = 0;
    base->BDR[ring].TBCIR  = 0;
    base->BDR[ring].TBLENR = ENETC_SI_TBLENR_LENGTH((uint32_t)bdrConfig->len / 8U);
    base->BDR[ring].TBIER  = ENETC_SI_TBIER_TXFIE(bdrConfig->enIntr) | ENETC_SI_TBIER_TXTIE(bdrConfig->enThresIntr);
    base->BDR[ring].TBMR   = ENETC_SI_TBMR_EN_MASK | ENETC_SI_TBMR_WRR(bdrConfig->wrrWeight) |
                           ENETC_SI_TBMR_PRIO(bdrConfig->priority) | ENETC_SI_TBMR_VIH(bdrConfig->isVlanInsert);

    return kStatus_Success;
}

status_t NETC_SIConfigRxBDR(ENETC_SI_Type *base, uint8_t ring, const netc_rx_bdr_config_t *bdrConfig)
{
    uint64_t address;

    /* The BD ring length should be multiple of 8/16 according to whether extended descriptor is enabled. */
    /* Maximun BD number is 64K. */
    if ((bdrConfig->extendDescEn && (((bdrConfig->len & 0xFU) != 0U) || ((bdrConfig->len / 2U) > 65536U))) ||
        ((!bdrConfig->extendDescEn) && (((bdrConfig->len & 0x7U) != 0U) || (bdrConfig->len > 65536U))))
    {
        return kStatus_InvalidArgument;
    }

    /* Minimum buffer size is 128 bytes. */
    if (bdrConfig->buffSize < 128U)
    {
        return kStatus_InvalidArgument;
    }

    /* Set the MSIX entry index triggered when interrupt occurs. */
    base->SIMSIRRVR[ring] = bdrConfig->msixEntryIdx;

    /* Map function only supports 32-bit now, so here limit 32-bit first */
    address = (uintptr_t)bdrConfig->bdArray;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_Local2DMA);
#endif

    /* Set the Rx descriptor address, shall be word aligned. */
    base->BDR[ring].RBBAR0 = NETC_ADDR_LOW_32BIT(address);
    base->BDR[ring].RBBAR1 = NETC_ADDR_HIGH_32BIT(address);
    base->BDR[ring].RBBSR  = bdrConfig->buffSize;
    base->BDR[ring].RBPIR  = 0;
    base->BDR[ring].RBCIR  = 0;
    base->BDR[ring].RBLENR = bdrConfig->extendDescEn ? (bdrConfig->len / 2U) : bdrConfig->len;
    base->BDR[ring].RBIER  = ENETC_SI_RBIER_RXTIE(bdrConfig->enThresIntr);
    base->BDR[ring].RBICR0 =
        ENETC_SI_RBICR0_ICEN(bdrConfig->enCoalIntr) | ENETC_SI_RBICR0_ICPT(bdrConfig->intrThreshold);
    base->BDR[ring].RBICR1 = ENETC_SI_RBICR1_ICTT(bdrConfig->intrTimerThres);
    base->BDR[ring].RBMR   = ENETC_SI_RBMR_CRC(bdrConfig->isKeepCRC) | ENETC_SI_RBMR_BDS(bdrConfig->extendDescEn) |
                           ENETC_SI_RBMR_CM(bdrConfig->congestionMode) | ENETC_SI_RBMR_AL(bdrConfig->enHeaderAlign) |
                           ENETC_SI_RBMR_VTPD(bdrConfig->disVlanPresent) | ENETC_SI_RBMR_VTE(bdrConfig->enVlanExtract);

    return kStatus_Success;
}

void NETC_SIPsiEnableInterrupt(ENETC_SI_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->PSI.PSIIER |= mask;
    }
    else
    {
        base->PSI.PSIIER &= ~mask;
    }
}

status_t NETC_SIPsiSendMsg(ENETC_SI_Type *base, uint16_t msg, netc_vsi_number_t vsi)
{
    status_t result;

    if (NETC_SIPsiCheckTxBusy(base, vsi))
    {
        result = kStatus_Busy;
    }
    else
    {
        base->PSI_A.PSIMSGSR = ENETC_SI_PSIMSGSR_MC(msg) | (uint32_t)vsi;
        result               = kStatus_Success;
    }
    return result;
}

status_t NETC_SIPsiSetRxBuffer(ENETC_SI_Type *base, netc_vsi_number_t vsi, uint64_t buffAddr)
{
    status_t result  = kStatus_InvalidArgument;
    uint16_t vsiIdx  = NETC_SIGetVsiIndex(vsi);
    uint64_t address = buffAddr;
    bool addrAlign;

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_Local2DMA);
#endif
    addrAlign = (address & 0x3FU) == 0U;
    if (addrAlign)
    {
        base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR0 = (uint32_t)address & ENETC_SI_PSIVMSGRCVAR0_ADDRL_MASK;
        base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR1 = (uint32_t)(address >> 32U);
        result                                    = kStatus_Success;
    }
    return result;
}

status_t NETC_SIPsiGetRxMsg(ENETC_SI_Type *base, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    assert(msgInfo != NULL);

    status_t result   = kStatus_Fail;
    uint16_t siBitMap = (uint16_t)base->PSI_A.PSIMSGRR;
    uint16_t vsiIdx   = NETC_SIGetVsiIndex(vsi);
    uint64_t address;
    uint8_t msgSize;
    uint32_t addrH;
    uint32_t addrL;

    if ((siBitMap & (uint16_t)vsi) != 0U)
    {
        addrH   = base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR1;
        addrL   = base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR0 & ENETC_SI_PSIVMSGRCVAR0_ADDRL_MASK;
        address = ((uint64_t)addrH << 32U) + addrL;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_DMA2Local);
#endif
        msgInfo->msgBuff = (uint8_t *)(uintptr_t)address;
        msgSize          = (uint8_t)(base->PSI_A.VSI_NUM[vsiIdx].PSIVMSGRCVAR0 & ENETC_SI_PSIVMSGRCVAR0_MSIZE_MASK);
        msgInfo->msgLen  = (msgSize == 0U) ? 1024U : (32U * (uint32_t)msgSize);

        /* Clear specified VSI status, VSI-side Tx busy status will be cleared together. */
        base->PSI_A.PSIMSGRR = (uint16_t)vsi;

        result = kStatus_Success;
    }
    return result;
}

void NETC_SIVsiEnableInterrupt(ENETC_SI_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->VSI.VSIIER |= (mask << 8U);
    }
    else
    {
        base->VSI.VSIIER &= ~(mask << 8U);
    }
}

status_t NETC_SIVsiSendMsg(ENETC_SI_Type *base, uint64_t msgAddr, uint32_t msgLen)
{
    status_t result  = kStatus_InvalidArgument;
    uint64_t address = msgAddr;
    uint8_t msgSize;
    bool addrAlign;
    bool lenAlign;

    if ((base->VSI_A.VSIMSGSR & ENETC_SI_VSIMSGSR_MB_MASK) != 0U)
    {
        result = kStatus_Busy;
    }
    else
    {
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        address = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)address, kMEMORY_Local2DMA);
#endif
        addrAlign = (address & 0x3FU) == 0U;
        lenAlign  = (msgLen & 0x1FU) == 0U;
        if ((msgLen <= 1024U) && addrAlign && lenAlign)
        {
            msgSize                  = (uint8_t)((msgLen == 1024U) ? 0U : (msgLen / 32U));
            base->VSI_A.VSIMSGSNDAR1 = (uint32_t)(address >> 32U);
            base->VSI_A.VSIMSGSNDAR0 =
                ((uint32_t)address & ENETC_SI_VSIMSGSNDAR0_ADDRL_MASK) | ENETC_SI_VSIMSGSNDAR0_MSIZE(msgSize);
            result = kStatus_Success;
        }
    }
    return result;
}

void NETC_SIVsiCheckTxStatus(ENETC_SI_Type *base, netc_vsi_msg_tx_status_t *status)
{
    assert(status != NULL);

    uint32_t txStatus = base->VSI_A.VSIMSGSR;

    status->txBusy  = ((txStatus & ENETC_SI_VSIMSGSR_MB_MASK) != 0U);
    status->isTxErr = ((txStatus & ENETC_SI_VSIMSGSR_MS_MASK) != 0U);
    status->msgCode = (uint16_t)((txStatus & ENETC_SI_VSIMSGSR_MC_MASK) >> ENETC_SI_VSIMSGSR_MC_SHIFT);
}

status_t NETC_SIVsiReceiveMsg(ENETC_SI_Type *base, uint16_t *msg)
{
    status_t result = kStatus_NoData;
    uint32_t msgData;

    msgData = base->VSI_A.VSIMSGRR;
    if ((msgData & ENETC_SI_VSIMSGRR_MR_MASK) != 0U)
    {
        *msg   = (uint16_t)((msgData & ENETC_SI_VSIMSGRR_MC_MASK) >> ENETC_SI_VSIMSGRR_MC_SHIFT);
        result = kStatus_Success;
    }
    return result;
}

void NETC_SIGetDiscardStatistic(ENETC_SI_Type *base, netc_si_discard_statistic_t *statistic)
{
    uint8_t rxRingNum =
        (uint8_t)((base->SICAPR0 & ENETC_SI_SICAPR0_NUM_RX_BDR_MASK) >> ENETC_SI_SICAPR0_NUM_RX_BDR_SHIFT);
    assert(rxRingNum <= ARRAY_SIZE(base->BDR));

    statistic->programError = base->SIUPECTR;
    statistic->busError     = base->SIUNSBECTR;
    for (uint32_t i = 0; i < ARRAY_SIZE(statistic->lackBD); i++)
    {
        if (i < rxRingNum)
        {
            statistic->lackBD[i] = base->BDR[i].RBDCR;
        }
        else
        {
            statistic->lackBD[i] = 0U;
        }
    }
}

void NETC_SIGetTrafficStatistic(ENETC_SI_Type *base, netc_si_traffic_statistic_t *statistic)
{
    statistic->rxOctet          = ((uint64_t)base->SIROCT1 << 32U) | base->SIROCT0;
    statistic->rxFrame          = ((uint64_t)base->SIRFRM1 << 32U) | base->SIRFRM0;
    statistic->rxFrameUnicast   = ((uint64_t)base->SIRUCA1 << 32U) | base->SIRUCA0;
    statistic->rxFrameMulticast = ((uint64_t)base->SIRMCA1 << 32U) | base->SIRMCA0;
    statistic->txOctet          = ((uint64_t)base->SITOCT1 << 32U) | base->SITOCT0;
    statistic->txFrame          = ((uint64_t)base->SITFRM1 << 32U) | base->SITFRM0;
    statistic->txFrameUnicast   = ((uint64_t)base->SITUCA1 << 32U) | base->SITUCA0;
    statistic->txFrameMulticast = ((uint64_t)base->SITMCA1 << 32U) | base->SITMCA0;
}
