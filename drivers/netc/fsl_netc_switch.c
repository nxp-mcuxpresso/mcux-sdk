/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_switch.h"
#include "fsl_netc_timer.h"
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051587) && FSL_FEATURE_NETC_HAS_ERRATA_051587
#include <math.h>
#endif

/*! @name NETC register map. */
/*@{*/
#define NETC_SWT_PORT_GROUP_BASE_OFFSET (0x4000U)  /*!< The Switch port group register base address offset. */
#define NETC_SWT_GLOBAL_BASE_OFFSET     (0x80000U) /*!< The Switch global register base address offset. */
#define NETC_SWT_PCIE_FUNC_OFFSET       (2U)       /*!< The Switch function register base address offset. */

/*! @brief Pointers to netc bases for each instance. */
static ENETC_PCI_TYPE0_Type *const s_netcPciBases[] = ENETC_PCI_TYPE0_BASE_PTRS;

/*! @brief Pointers to netc bases for each instance. */
static NETC_SW_Type *const s_netcSWBases[] = NETC_SW_BASE_PTRS;

/*! @brief Common message data buffer for command ring 0 and ring 1, data buffer address need align with 16 bytes */
AT_NONCACHEABLE_SECTION_ALIGN(static netc_tb_data_buffer_t dataBuffer0, 16);
AT_NONCACHEABLE_SECTION_ALIGN(static netc_tb_data_buffer_t dataBuffer1, 16);
static netc_tb_data_buffer_t *s_cmdDataBuffer[2] = {&dataBuffer0, &dataBuffer1};
/*!< Management ENETC SI 0 Rx ring hardware index, this ring is only used for receive frames with Host Reason filed not
 * zero. */
static uint8_t mgmtRxBdRingIdx;

static void SWT_GetBaseResource(swt_handle_t *handle, netc_hw_switch_idx_t sw)
{
    handle->hw.func   = s_netcPciBases[NETC_SWT_PCIE_FUNC_OFFSET + (uint32_t)sw];
    handle->hw.base   = s_netcSWBases[sw];
    handle->hw.common = (NETC_SW_ENETC_Type *)((uintptr_t)handle->hw.base);
    handle->hw.global = (ENETC_GLOBAL_Type *)((uintptr_t)handle->hw.base + NETC_SWT_GLOBAL_BASE_OFFSET);
    for (uint32_t i = 0U; i < (uint32_t)FSL_FEATURE_NETC_SWITCH_MAX_PORT_NUMBER; i++)
    {
        handle->hw.ports[i].port =
            (NETC_PORT_Type *)((uintptr_t)handle->hw.base + (i + 1U) * NETC_SWT_PORT_GROUP_BASE_OFFSET);
        handle->hw.ports[i].eth = (NETC_ETH_LINK_Type *)((uintptr_t)handle->hw.ports[i].port + 0x1000U);
    }
    handle->hw.msixTable = (netc_msix_entry_t *)((uint32_t)FSL_FEATURE_NETC_MSIX_TABLE_BASE +
                                                 NETC_MSIX_TABLE_OFFSET * (NETC_SWT_PCIE_FUNC_OFFSET + (uint32_t)sw));
}

/*!
 * @brief Set the MSIX entry table
 *
 * This function is to set entry table in specified MSIX Table memory. After entry table setup, set interrupts
 * vector/entry index.
 *
 * @param handle  The SWT handle.
 * @param config  The SWT configuration.
 * @return status_t
 */
static status_t SWT_MSIXSetEntryTable(swt_handle_t *handle, const swt_config_t *config)
{
    uint32_t *msixTable  = (uint32_t *)(uintptr_t)handle->hw.msixTable;
    uint32_t *entryTable = (uint32_t *)(uintptr_t)config->msixEntry;
    uint8_t msixNum;

    msixNum =
        (uint8_t)(((handle->hw.base->SCAPR0 & NETC_SW_SCAPR0_NUM_MSIX_MASK) >> NETC_SW_SCAPR0_NUM_MSIX_SHIFT) + 1U);

    /* Entry > 0, enable MSIX. */
    if (config->entryNum != 0U)
    {
        if (config->entryNum > msixNum)
        {
            return kStatus_InvalidArgument;
        }

        if (MAX(MAX(config->cmdBdrEntryIdx[0], config->cmdBdrEntryIdx[1]), config->timeCaptureEntryIdx) >=
            config->entryNum)
        {
            return kStatus_InvalidArgument;
        }

        /* Use 32-bit access to set MSIX table. */
        for (uint32_t i = 0; i < config->entryNum; i++)
        {
            msixTable[i * 4U]      = entryTable[i * 4U];
            msixTable[i * 4U + 1U] = entryTable[i * 4U + 1U];
            msixTable[i * 4U + 2U] = entryTable[i * 4U + 2U];
            msixTable[i * 4U + 3U] = entryTable[i * 4U + 3U];
        }

        /* Set MSIX entry index. */
        handle->hw.base->NUM_CBDR_INT[0].CBDRMSIVR =
            (uint32_t)config->cmdBdrEntryIdx[0] & NETC_SW_CBDRMSIVR_VECTOR_MASK;
        handle->hw.base->NUM_CBDR_INT[1].CBDRMSIVR =
            (uint32_t)config->cmdBdrEntryIdx[1] & NETC_SW_CBDRMSIVR_VECTOR_MASK;
        handle->hw.common->TCMSIVR = (uint32_t)config->timeCaptureEntryIdx & NETC_SW_ENETC_TCMSIVR_VECTOR_MASK;

        /* Enable MSIX. */
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK;
    }
    else
    {
        /* Disable MSIX. */
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
    }

    return kStatus_Success;
}

status_t SWT_MsixSetGlobalMask(swt_handle_t *handle, bool mask)
{
    if (mask)
    {
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL |= ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
    }
    else
    {
        handle->hw.func->PCI_CFC_MSIX_MSG_CTL &= (uint16_t)(~ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK);
    }

    return kStatus_Success;
}

status_t SWT_MsixSetEntryMask(swt_handle_t *handle, uint8_t entryIdx, bool mask)
{
    status_t result;

    if (entryIdx < handle->cfg.entryNum)
    {
        handle->hw.msixTable[entryIdx].control = (uint32_t)mask;
        result                                 = kStatus_Success;
    }
    else
    {
        result = kStatus_Fail;
    }

    return result;
}

status_t SWT_MsixGetPendingStatus(swt_handle_t *handle, uint8_t pbaIdx, uint64_t *status)
{
    status_t result = kStatus_Success;
    bool funcEnable;

    if (handle->cfg.entryNum == 0U)
    {
        return kStatus_Fail;
    }

    /* Check MSIX enable status. */
    funcEnable = ((handle->hw.func->PCI_CFC_MSIX_MSG_CTL & ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK) != 0U);

    if (funcEnable)
    {
        if (pbaIdx <= ((handle->cfg.entryNum - 1U) / 64U))
        {
            *status = *(uint64_t *)((uintptr_t)handle->hw.msixTable + NETC_MSIX_TABLE_PBA_OFFSET + 8U * pbaIdx);
            result  = kStatus_Success;
        }
        else
        {
            result = kStatus_InvalidArgument;
        }
    }
    else
    {
        *status = 0;
        result  = kStatus_Fail;
    }

    return result;
}

status_t SWT_GetDefaultConfig(swt_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(swt_config_t));
    for (uint32_t i = 0U; i < 5U; i++)
    {
        config->ports[i].bridgeCfg.acceptUntag          = true;
        config->ports[i].bridgeCfg.acceptPriorityTag    = true;
        config->ports[i].bridgeCfg.acceptSingleTag      = true;
        config->ports[i].bridgeCfg.acceptDoubleTag      = true;
        config->ports[i].bridgeCfg.enSrcPortPrun        = true;
        config->ports[i].bridgeCfg.stgMode[0]           = kNETC_ForwardFrame;
        config->ports[i].bridgeCfg.bcastRpEntryID       = 0xFFFU;
        config->ports[i].bridgeCfg.unUcastRpEntryID     = 0xFFFU;
        config->ports[i].bridgeCfg.unMcastRpEntryID     = 0xFFFU;
        config->ports[i].bridgeCfg.mcastEntryID         = 0xFFFU;
        config->ports[i].isiCfg.defaultISEID            = 0xFFFFU;
        config->ports[i].commonCfg.acceptTpid.innerMask = (uint8_t)kNETC_OuterStanCvlan | (uint8_t)kNETC_OuterStanSvlan;
        config->ports[i].commonCfg.acceptTpid.outerMask = (uint8_t)kNETC_InnerStanCvlan | (uint8_t)kNETC_InnerStanSvlan;
        config->ports[i].commonCfg.pSpeed               = 0x63U;
        config->ports[i].commonCfg.rxTsSelect           = kNETC_SyncTime;
#if (defined(FSL_FEATURE_NETC_HAS_PORT_FCSEA) && FSL_FEATURE_NETC_HAS_PORT_FCSEA)
        config->ports[i].commonCfg.stompFcs = true;
#endif
        config->ports[i].commonCfg.rxPpduBco         = 20U;
        config->ports[i].commonCfg.txPpduBco         = 20U;
        config->ports[i].commonCfg.timeGate.holdSkew = 64;
        config->ports[i].commonCfg.parser.l2PloadCount    = 24;
        config->ports[i].commonCfg.parser.l3PayloadCount  = 24;
        config->ports[i].commonCfg.parser.enableL3Parser  = true;
        config->ports[i].commonCfg.parser.l4PayloadCount  = 24;
        config->ports[i].commonCfg.parser.enableL4Parser  = true;
        config->ports[i].ethMac.preemptMode          = kNETC_PreemptDisable;
        config->ports[i].ethMac.enMergeVerify        = false;
        config->ports[i].ethMac.mergeVerifyTime      = 10U;
        config->ports[i].ethMac.enTxPad              = true;
        config->ports[i].ethMac.rxMinFrameSize       = 64U;
        config->ports[i].ethMac.rxMaxFrameSize       = 0x600U;
        config->ports[i].ethMac.maxBackPressOn       = 3036U;
        config->ports[i].ethMac.minBackPressOff      = 20U;
        config->ports[i].enTxRx                      = true;
        for (uint32_t j = 0U; j < 8U; j++)
        {
            config->ports[i].txTcCfg[j].enTcGate           = true;
            config->ports[i].txTcCfg[j].sduCfg.maxSduSized = 0x600U;
            config->ports[i].txTcCfg[j].sduCfg.sduType     = kNETC_MPDU;
            config->ports[i].ipvToTC[j]                    = (uint8_t)j;
        }
    }
    for (uint32_t i = 0U; i < 2U; i++)
    {
        for (uint32_t j = 0U; j < 8U; j++)
        {
            config->rxqosCfg.profiles[i].ipv[j * 2U]      = (uint8_t)j;
            config->rxqosCfg.profiles[i].ipv[j * 2U + 1U] = (uint8_t)j;
            config->rxqosCfg.profiles[i].dr[j * 2U + 1U]  = 2U;
        }
    }
    config->bridgeCfg.dVFCfg.portMembership = 0x1FU;
    config->bridgeCfg.dVFCfg.mfo            = kNETC_FDBLookUpWithFlood;
    config->bridgeCfg.dVFCfg.mlo            = kNETC_HardwareMACLearn;
    config->imrCfg.dr                       = 3;
    config->imrCfg.enMirror                 = false;
    config->imrCfg.efmEntryID               = 0xFFFFU;

    return kStatus_Success;
}

/*!
 * @brief Free all Rx buffers
 *
 * @param handle  The Switch handle.
 */
static void SWT_RxBufferFreeAll(swt_handle_t *handle)
{
    netc_rx_bdr_t *rxBdRing;
    uint32_t maxHwBdNum;
    uint32_t index;

    if (handle->cfg.rxZeroCopy)
    {
        rxBdRing = &handle->mgmtRxBdRing;
        /* Hardware BD number means actual BD number in hardware view, two standard BDs act as one extended BD. */
        maxHwBdNum = rxBdRing->extendDesc ? (rxBdRing->len / 2U) : rxBdRing->len;

        for (index = 0U; index < maxHwBdNum; index++)
        {
            if (rxBdRing->buffArray[index] != 0U)
            {
                handle->cfg.rxBuffFree(handle, (void *)(uint8_t *)(uintptr_t)rxBdRing->buffArray[index],
                                       handle->cfg.userData);
            }
        }
    }
}

status_t SWT_Init(swt_handle_t *handle, const swt_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    status_t result = kStatus_Success;
    NETC_PORT_Type *port;

    (void)memset(handle, 0, sizeof(swt_handle_t));
    /* Get the register map resource for switch */
    SWT_GetBaseResource(handle, config->switchIdx);
    /* Enable master bus and memory access for PCIe and MSI-X first to do ETH MAC reset*/
    handle->hw.func->PCI_CFH_CMD |=
        (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
    /* Do software reset for all ETH MAC to clear Tx/Rx FIFO*/
    for (uint32_t i = 0U; (i < 5U) && (!NETC_PortIsPseudo(handle->hw.ports[i].port)); i++)
    {
        handle->hw.ports[i].port->POR |= (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
        NETC_PortSoftwareResetEthMac(handle->hw.ports[i].eth);
    }
    /* Reset this function */
    handle->hw.func->PCI_CFC_PCIE_DEV_CTL |= ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK;
    while ((handle->hw.func->PCI_CFC_PCIE_DEV_CTL & ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK) != 0U)
    {
    }
    /* Enable master bus and memory access for PCIe and MSI-X */
    handle->hw.func->PCI_CFH_CMD |=
        (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051260) && FSL_FEATURE_NETC_HAS_ERRATA_051260)
    /* Errata 051260: All NETC functions need to be enabled for switch NTMP operation */
    ENETC0_PCI_HDR_TYPE0->PCI_CFH_CMD |=
        (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
    ENETC1_PCI_HDR_TYPE0->PCI_CFH_CMD |=
        (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
#endif
    /* Store configuration in handle */
    handle->cfg.cmdRingUse = config->cmdRingUse;
    handle->cfg.entryNum   = config->entryNum;
    /* Store configuration in handle */
    result = SWT_MSIXSetEntryTable(handle, config);
    if (result != kStatus_Success)
    {
        return result;
    }
    /* Configure switch ingress mirror destination */
    if (kStatus_Success != SWT_RxMirrorConfig(handle, &config->imrCfg))
    {
        return kStatus_Fail;
    }
    /* Configure switch FDB hash table maximum number of  dynamically entries */
    handle->hw.base->FDBHTMCR = NETC_SW_FDBHTMCR_DYN_LIMIT(config->dynFDBLimit);
    /* Configure switch bridge */
    (void)SWT_BridgeInit(handle, &config->bridgeCfg);
    /* Configure switch command BD rings */
    for (uint32_t i = 0U; i < config->cmdRingUse; i++)
    {
        result = SWT_CmdBDRInit(handle, (netc_hw_swt_cbdr_idx_t)i, &config->cmdBdrCfg[i]);
        if (kStatus_Success != result)
        {
            return result;
        }
        handle->cmdBdRing[i].bdBase        = config->cmdBdrCfg[i].bdBase;
        handle->cmdBdRing[i].bdLength      = config->cmdBdrCfg[i].bdLength;
        handle->cmdBdRing[i].producerIndex = 0U;
        handle->cmdBdRing[i].cleanIndex    = 0U;
        handle->cmdBdRing[i].bdrEnable     = true;
    }
    /* Configure switch Ingress Port Filtering */
    (void)SWT_RxIPFInit(handle, &config->ipfCfg);
    /* Configure switch Ingress VLAN classification */
    (void)SWT_RxVlanCInit(handle, &config->vlanCfg);
    /* Configure switch Ingress QOS classification */
    (void)SWT_RxQosCInit(handle, &config->rxqosCfg);
    /* Configure switch egress QOS to VLAN map classification */
    (void)SWT_TxEPPQosToVlanConfig(handle, &config->txqosCfg);
    /* Configure switch PSFP */
    (void)SWT_RxPSFPInit(handle, &config->psfpCfg);
    /* Configure all ports and macs */
    for (uint32_t i = 0U; i < 5U; i++)
    {
        if (config->ports[i].enTxRx)
        {
            /* Config TGS on PSI side */
            result = SWT_TxPortTGSEnable(handle, (netc_hw_port_idx_t)i, config->ports[i].enableTg, 0xFFU);
            if (result != kStatus_Success)
            {
                return result;
            }
            port = handle->hw.ports[i].port;
            (void)SWT_BridgeConfigPort(handle, (netc_hw_port_idx_t)i, &config->ports[i].bridgeCfg);
            (void)SWT_FMConfigPort(handle, (netc_hw_port_idx_t)i, &config->ports[i].fmCfg);
            (void)NETC_PortSetISI(port, &config->ports[i].isiCfg);
            (void)NETC_PortConfig(port, &config->ports[i].commonCfg);
            port->PMCR      = NETC_PORT_PMCR_IMIRE(config->ports[i].enMirror);
            port->PLANIDCR  = NETC_PORT_PLANIDCR_LANID(config->ports[i].lanID);
            port->PIPV2QMR0 = NETC_PORT_PIPV2QMR0_IPV7_Q(config->ports[i].ipvToTC[7]) |
                              NETC_PORT_PIPV2QMR0_IPV6_Q(config->ports[i].ipvToTC[6]) |
                              NETC_PORT_PIPV2QMR0_IPV5_Q(config->ports[i].ipvToTC[5]) |
                              NETC_PORT_PIPV2QMR0_IPV4_Q(config->ports[i].ipvToTC[4]) |
                              NETC_PORT_PIPV2QMR0_IPV3_Q(config->ports[i].ipvToTC[3]) |
                              NETC_PORT_PIPV2QMR0_IPV2_Q(config->ports[i].ipvToTC[2]) |
                              NETC_PORT_PIPV2QMR0_IPV1_Q(config->ports[i].ipvToTC[1]) |
                              NETC_PORT_PIPV2QMR0_IPV0_Q(config->ports[i].ipvToTC[0]);
            port->PBPMCR0 = NETC_PORT_PBPMCR0_IPV3_INDEX(config->ports[i].ipvToBP[3]) |
                            NETC_PORT_PBPMCR0_IPV2_INDEX(config->ports[i].ipvToBP[2]) |
                            NETC_PORT_PBPMCR0_IPV1_INDEX(config->ports[i].ipvToBP[1]) |
                            NETC_PORT_PBPMCR0_IPV0_INDEX(config->ports[i].ipvToBP[0]);
            port->PBPMCR1 = NETC_PORT_PBPMCR1_IPV7_INDEX(config->ports[i].ipvToBP[7]) |
                            NETC_PORT_PBPMCR1_IPV6_INDEX(config->ports[i].ipvToBP[6]) |
                            NETC_PORT_PBPMCR1_IPV5_INDEX(config->ports[i].ipvToBP[5]) |
                            NETC_PORT_PBPMCR1_IPV4_INDEX(config->ports[i].ipvToBP[4]);
            /* Configure Ethernet MAC */
            if (!NETC_PortIsPseudo(port))
            {
                (void)NETC_PortConfigEthMac(handle->hw.ports[i].eth, &config->ports[i].ethMac);
                port->PCTFCR = NETC_PORT_PCTFCR_ECTS(!config->ports[i].outCutThrough) |
#if defined(NETC_PORT_PCTFCR_BSQS_MASK)
                               NETC_PORT_PCTFCR_BSQS(config->ports[i].outBufferSize) |
#endif
                               NETC_PORT_PCTFCR_ICTS(!config->ports[i].inCutThrough);
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051202) && FSL_FEATURE_NETC_HAS_ERRATA_051202)
                /* RT1180 errata 051202: Configure Tx MAC to wait until 32 bytes of data are built up in the transmit
                 * FIFO before beginning transmission on the link */
                *(volatile uint32_t *)((uintptr_t)handle->hw.ports[i].eth + 0x1020U) = 0x00010104;
                *(volatile uint32_t *)((uintptr_t)handle->hw.ports[i].eth + 0x1420U) = 0x00010104;
#endif
            }
            /* Configure traffic class */
            for (uint32_t j = 8U; j > 0U; j--)
            {
                result = SWT_TxTrafficClassConfig(handle, (netc_hw_port_idx_t)i, (netc_hw_tc_idx_t)(uint32_t)(j - 1U),
                                                  &config->ports[i].txTcCfg[(j - 1U)]);
                if (result != kStatus_Success)
                {
                    return result;
                }
            }
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051246) && FSL_FEATURE_NETC_HAS_ERRATA_051246)
            /* Clear Tx/Rx disable to allow traffic to flow */
            handle->hw.ports[i].port->POR &= ~(NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
#endif
        }
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051246) && FSL_FEATURE_NETC_HAS_ERRATA_051246)
        else
        {
            /* Disable the unused port Tx/Rx */
            handle->hw.ports[i].port->POR |= (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
        }
#endif
    }
    return result;
}

status_t SWT_Deinit(swt_handle_t *handle)
{
    for (uint32_t i = 0U; i < handle->cfg.cmdRingUse; i++)
    {
        (void)SWT_CmdBDRDeinit(handle, (netc_hw_swt_cbdr_idx_t)i);
    }
    for (uint32_t i = 0U; i < 5U; i++)
    {
        if (!NETC_PortIsPseudo(handle->hw.ports[i].port) &&
            (0U == (handle->hw.ports[i].port->POR & (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK))))
        {
            NETC_PortEthMacGracefulStop(handle->hw.ports[i].port);
        }
    }
    SWT_RxBufferFreeAll(handle);

    return kStatus_Success;
}

status_t SWT_SetEthPortMII(swt_handle_t *handle,
                           uint8_t ethPort,
                           netc_hw_mii_speed_t speed,
                           netc_hw_mii_duplex_t duplex)
{
    netc_hw_mii_mode_t miiMode;

    if (ethPort >= (uint8_t)FSL_FEATURE_NETC_SWITCH_ETH_PORT_NUMBER)
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        miiMode = NETC_PortGetMIIMode(handle->hw.ports[ethPort].eth);
        return NETC_PortSetMII(handle->hw.ports[ethPort].eth, miiMode, speed, duplex);
    }
}

status_t SWT_PortStop(swt_handle_t *handle, netc_hw_port_idx_t portIdx)
{
    if (!NETC_PortIsPseudo(handle->hw.ports[portIdx].port))
    {
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051398) && FSL_FEATURE_NETC_HAS_ERRATA_051398)
        NETC_PORT_Type *base              = handle->hw.ports[portIdx].port;
        NETC_ETH_LINK_Type *eth           = (NETC_ETH_LINK_Type *)((uintptr_t)base + 0x1000U);
        bool hasPM1                       = 0U != (eth->MAC_MERGE_MMCSR & NETC_ETH_LINK_MAC_MERGE_MMCSR_ME_MASK);
        netc_tb_etmcg_config_t cgEntryCfg = {
            .cfge.tdDr0En = 1U, .cfge.tdDr1En = 1U, .cfge.tdDr2En = 1U, .cfge.tdDr3En = 1U};

        /* Configure congestion group to enable tail drop (with corresponding threshold set to 0) for each DR level
         */
        for (uint32_t i = 0U; i < 8U; i++)
        {
            cgEntryCfg.entryID = NETC_TB_ETM_CG_ENTRY_ID(portIdx, i);
            if (kStatus_Success != SWT_TxETMConfigCongestionGroup(handle, &cgEntryCfg))
            {
                return kStatus_Fail;
            }
        }
        /* Wait for PMa_IEVENT[TX_EMPTY] to be set. */
        while (0U == (eth->PM0_IEVENT & NETC_ETH_LINK_PM0_IEVENT_TX_EMPTY_MASK))
        {
        }
        if (hasPM1)
        {
            while (0U == (eth->PM1_IEVENT & NETC_ETH_LINK_PM1_IEVENT_TX_EMPTY_MASK))
            {
            }
            eth->PM1_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM1_COMMAND_CONFIG_TX_EN_MASK;
        }
        /* Set POR[TXDIS] to 1b. */
        base->POR |= NETC_PORT_POR_TXDIS_MASK;
        /* Disable the congestion group tail drop(s) */
        (void)memset(&cgEntryCfg, 0, sizeof(netc_tb_etmcg_config_t));
        for (uint32_t i = 0U; i < 8U; i++)
        {
            cgEntryCfg.entryID = NETC_TB_ETM_CG_ENTRY_ID(portIdx, i);
            if (kStatus_Success != SWT_TxETMConfigCongestionGroup(handle, &cgEntryCfg))
            {
                return kStatus_Fail;
            }
        }
        /* Wait 64 byte time for Tx packet transmission to complete. */
        SDK_DelayAtLeastUs(512, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        /* Write PMa_COMMAND_CONFIG[TX_EN]=0b.  */
        eth->PM0_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM0_COMMAND_CONFIG_TX_EN_MASK;
        if (hasPM1)
        {
            eth->PM1_COMMAND_CONFIG &= ~NETC_ETH_LINK_PM1_COMMAND_CONFIG_TX_EN_MASK;
        }

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
#else
        NETC_PortEthMacGracefulStop(handle->hw.ports[portIdx].port);
#endif
    }
    else
    {
        /* Disable the port Tx/Rx directly */
        handle->hw.ports[portIdx].port->POR |= (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
    }
    return kStatus_Success;
}

status_t SWT_SetPortMaxFrameSize(swt_handle_t *handle, netc_hw_port_idx_t portIdx, uint16_t size)
{
    assert(handle != NULL);

    NETC_PORT_Type *base = handle->hw.ports[portIdx].port;

    if (NETC_PortIsPseudo(base))
    {
        return kStatus_InvalidArgument;
    }

    return NETC_PortSetMaxFrameSize(handle->hw.ports[portIdx].eth, size);
}

status_t SWT_RxMirrorConfig(swt_handle_t *handle, const netc_swt_imr_config_t *config)
{
    assert((handle != NULL) && (config != NULL));

    handle->hw.base->IMDCR0 =
        NETC_SW_IMDCR0_PORT((kNETC_SWTMPort != config->destPort) ? (uint32_t)config->destPort : 0U) |
        NETC_SW_IMDCR0_DR(config->dr) | NETC_SW_IMDCR0_IPV(config->ipv) |
        NETC_SW_IMDCR0_MIRDEST((kNETC_SWTMPort == config->destPort) ? 1U : 0U) | NETC_SW_IMDCR0_MIREN(config->enMirror);
    if ((kNETC_SWTMPort == config->destPort) && (0xFFFFU != config->efmEntryID))
    {
        return kStatus_Fail;
    }
    else
    {
        handle->hw.base->IMDCR1 =
            NETC_SW_IMDCR1_EFM_LEN_CHANGE(config->efmLengthChange) | NETC_SW_IMDCR1_EFMEID(config->efmEntryID);
        return kStatus_Success;
    }
}

/*!
 * @brief Store necessary configuration constant in the handle
 *
 * @param handle  The SWT handle.
 * @param config  The user configuration.
 */
static void SWT_StoreTransConfig(swt_handle_t *handle, const swt_transfer_config_t *config)
{
    handle->cfg.rxCacheMaintain   = config->rxCacheMaintain;
    handle->cfg.txCacheMaintain   = config->txCacheMaintain;
    handle->cfg.rxZeroCopy        = config->rxZeroCopy;
    handle->cfg.rxBuffAlloc       = config->rxBuffAlloc;
    handle->cfg.rxBuffFree        = config->rxBuffFree;
    handle->cfg.enUseMgmtRxBdRing = config->enUseMgmtRxBdRing;
    handle->cfg.enUseMgmtTxBdRing = config->enUseMgmtTxBdRing;
    handle->cfg.reclaimCallback   = config->reclaimCallback;
    handle->cfg.userData          = config->userData;
}

status_t SWT_ManagementTxRxConfig(swt_handle_t *handle, ep_handle_t *epHandle, const swt_transfer_config_t *txRxConfig)
{
    assert((handle != NULL) && (epHandle != NULL) && (txRxConfig != NULL));

    const netc_rx_bdr_config_t *rxRingConfig;
    netc_rx_bd_t *rxDesc;
    uint64_t buffAddr;
    uint32_t buffIdx;

    handle->epHandle = epHandle;
    SWT_StoreTransConfig(handle, txRxConfig);
    if ((!NETC_EnetcHasManagement(epHandle->hw.base)) || (getSiNum(epHandle->cfg.si) != 0U))
    {
        /* Management frame only can be Tx/Rx on Switch management ENETC SI 0 */
        return kStatus_InvalidArgument;
    }
    if (txRxConfig->enUseMgmtRxBdRing)
    {
        rxRingConfig = &txRxConfig->mgmtRxBdrConfig;
        /* Get Management Rx ring hardware index */
        mgmtRxBdRingIdx = (uint8_t)(((epHandle->hw.base->NUM_SI[0].PSICFGR0 & NETC_ENETC_PSICFGR0_NUM_RX_BDR_MASK) >>
                                     NETC_ENETC_PSICFGR0_NUM_RX_BDR_SHIFT) -
                                    1U);
        if (NETC_SIConfigRxBDR(epHandle->hw.si, mgmtRxBdRingIdx, rxRingConfig) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        handle->mgmtRxBdRing.extendDesc = rxRingConfig->extendDescEn;
        handle->mgmtRxBdRing.bdBase     = rxRingConfig->bdArray;
        handle->mgmtRxBdRing.len        = rxRingConfig->len;
        handle->mgmtRxBdRing.buffSize   = rxRingConfig->buffSize;
        /* Make all frames with the metadata field Host Reason set to non-zero are directed to this Management Rx ring
         */
        for (uint8_t i = 0U; i < NETC_ENETC_SMHRBDRMR_COUNT; i++)
        {
            epHandle->hw.base->SMHRBDRMR[i] = NETC_ENETC_SMHRBDRMR_RXBDR(mgmtRxBdRingIdx);
        }
        rxDesc = &rxRingConfig->bdArray[0];

        /* Store address information in the array in case the buffer address is lost due to Rx BD write-back. */
        handle->mgmtRxBdRing.buffArray = rxRingConfig->buffAddrArray;

        /* Initialize the buffers in Rx BD ring. */
        for (uint32_t index = 0U; index < rxRingConfig->len; index++)
        {
            /* Clear Rx BD before config the receive buffer start address */
            (void)memset(rxDesc, 0, sizeof(netc_rx_bd_t));

            /* When extended BD is enabled, two standard BDs represet one extended BD. Even number BD sets 0. */
            if (rxRingConfig->extendDescEn && (index % 2U != 0U))
            {
                rxDesc++;
                continue;
            }

            buffIdx = rxRingConfig->extendDescEn ? (index / 2U) : index;
            if (!txRxConfig->rxZeroCopy)
            {
                /* Get Rx buffer address from the address array provided by application. */
                buffAddr = handle->mgmtRxBdRing.buffArray[buffIdx];
            }
            else
            {
                /* Get Rx buffer address from the allocation function provided by application. */
                buffAddr =
                    (uintptr_t)(uint8_t *)txRxConfig->rxBuffAlloc(handle, rxRingConfig->buffSize, txRxConfig->userData);
                if (buffAddr == 0U)
                {
                    SWT_RxBufferFreeAll(handle);
                    return kStatus_NETC_LackOfResource;
                }

                /* Store address information in the array in case the buffer address can't find due to Rx BD
                 * write-back. */
                handle->mgmtRxBdRing.buffArray[buffIdx] = buffAddr;
            }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffAddr = MEMORY_ConvertMemoryMapAddress((uintptr_t)buffAddr, kMEMORY_Local2DMA);
#endif
            rxDesc->standard.addr = buffAddr;
            rxDesc++;
        }

        /* Enable the Rx BD ring. */
        NETC_SIRxRingEnable(epHandle->hw.si, mgmtRxBdRingIdx, true);
    }
    if (txRxConfig->enUseMgmtTxBdRing)
    {
        /* Management Tx ring only can be SI 0 ring 0 */
        if (NETC_SIConfigTxBDR(epHandle->hw.si, 0, &txRxConfig->mgmtTxBdrConfig) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        handle->mgmtTxBdRing.bdBase    = txRxConfig->mgmtTxBdrConfig.bdArray;
        handle->mgmtTxBdRing.dirtyBase = txRxConfig->mgmtTxBdrConfig.dirtyArray;
        handle->mgmtTxBdRing.len       = txRxConfig->mgmtTxBdrConfig.len;
    }
    return kStatus_Success;
}

status_t SWT_SendFrame(swt_handle_t *handle,
                       swt_mgmt_tx_arg_t ringOrQueue,
                       netc_hw_port_idx_t swtPort,
                       bool enMasquerade,
                       netc_frame_struct_t *frame,
                       void *context,
                       swt_tx_opt *opt)
{
    netc_tx_bd_t txDesc[2] = {0};
    uint8_t hwRing;
    netc_tx_bdr_t *txBdRing;
    if (enMasquerade)
    {
        if (getSiNum(handle->epHandle->cfg.si) == 0U)
        {
            /* Switch management ENETC Tx BD hardware ring 0 can't be used to send port masqueradeque frame, so the
             * index need increase 1 */
            hwRing = ringOrQueue.ring + 1U;
        }
        else
        {
            hwRing = ringOrQueue.ring;
        }
        txDesc[0].standard.flags = NETC_SI_TXDESCRIP_RD_FLQ(2) | NETC_SI_TXDESCRIP_RD_PORT(swtPort);
        txBdRing                 = &handle->epHandle->txBdRing[ringOrQueue.ring];
    }
    else
    {
        if ((getSiNum(handle->epHandle->cfg.si) != 0U) || (!handle->cfg.enUseMgmtTxBdRing))
        {
            /* Direct switch enqueue frame only can be sent by Switch management ENETC SI 0 */
            return kStatus_InvalidArgument;
        }
        txDesc[0].standard.flags = NETC_SI_TXDESCRIP_RD_FLQ(2) | NETC_SI_TXDESCRIP_RD_SMSO_MASK |
                                   NETC_SI_TXDESCRIP_RD_PORT(swtPort) | NETC_SI_TXDESCRIP_RD_IPV(ringOrQueue.ipv) |
                                   NETC_SI_TXDESCRIP_RD_DR(ringOrQueue.dr);
        hwRing   = 0U;
        txBdRing = &handle->mgmtTxBdRing;
    }
    if (opt != NULL)
    {
        if (((opt->flags & (uint32_t)kSWT_TX_OPT_VLAN_INSERT) != 0U) && enMasquerade)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.pcp             = opt->vlan.pcp;
            txDesc[1].ext.dei             = opt->vlan.dei;
            txDesc[1].ext.vid             = opt->vlan.vid;
            txDesc[1].ext.tpid            = (uint16_t)opt->vlan.tpid;
            txDesc[1].ext.eFlags          = (uint8_t)kNETC_TxExtVlanInsert;
        }
        if (((opt->flags & (uint32_t)kSWT_TX_OPT_REQ_TS) != 0U) && enMasquerade)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.eFlags |= (uint8_t)kNETC_TxExtTwoStepTs;
        }
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
        if (((opt->flags & (uint32_t)kEP_TX_OPT_REQ_ONE_STEP_TS) != 0U) && enMasquerade)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.eFlags |= kNETC_TxExtOneStepTs;
        }
#endif
        if (((opt->flags & (uint32_t)kSWT_TX_OPT_DIRECT_ENQUEUE_REQ_TSR) != 0U) && (!enMasquerade))
        {
            txDesc[0].standard.flags |= NETC_SI_TXDESCRIP_RD_TSR_MASK;
        }
    }
    return EP_SendFrameCommon(handle->epHandle, txBdRing, hwRing, frame, context, &txDesc[0],
                              handle->cfg.txCacheMaintain);
}

void SWT_ReclaimTxDescriptor(swt_handle_t *handle, bool enMasquerade, uint8_t ring)
{
    netc_tx_frame_info_t *frameInfo;

    do
    {
        if (enMasquerade)
        {
            /* Port masquerade still use ep transfer handle */
            frameInfo = EP_ReclaimTxDescCommon(handle->epHandle, &handle->epHandle->txBdRing[ring], ring + 1U,
                                               (handle->epHandle->cfg.reclaimCallback != NULL));
        }
        else
        {
            frameInfo = EP_ReclaimTxDescCommon(handle->epHandle, &handle->mgmtTxBdRing, 0,
                                               (handle->cfg.reclaimCallback != NULL));
        }
        if (frameInfo != NULL)
        {
            /* If reclaim callback is enabled, it must be called for each full frame. */
            if (enMasquerade)
            {
                /* Port masquerade still use ep transfer handle */
                (void)handle->epHandle->cfg.reclaimCallback(handle->epHandle, ring, frameInfo,
                                                            handle->epHandle->cfg.userData);
            }
            else
            {
                (void)handle->cfg.reclaimCallback(handle, frameInfo, handle->cfg.userData);
            }
            (void)memset(frameInfo, 0, sizeof(netc_tx_frame_info_t));
        }
    } while (frameInfo != NULL);
}

status_t SWT_GetRxFrameSize(swt_handle_t *handle, uint32_t *length)
{
    assert((handle != NULL) && (length != NULL));
    netc_rx_bdr_t *rxBdRing = NULL;
    status_t result;

    if (handle->cfg.enUseMgmtRxBdRing)
    {
        rxBdRing = &handle->mgmtRxBdRing;
    }
    else if (handle->epHandle->cfg.rxRingUse != 0U)
    {
        /* If no management Rx ring is specified, the host reason not zero frames will be received by Rx ring 0 */
        rxBdRing = &handle->epHandle->rxBdRing[0];
    }
    else
    {
        /* If both the switch and its associated EP not config the Rx BD ring, no frame can be received */
        return kStatus_InvalidArgument;
    }

    result = EP_GetRxFrameSizeCommon(handle->epHandle, rxBdRing, length);
    if (kStatus_NETC_RxHRNotZeroFrame == result)
    {
        /* Only return success when currently frame is host reason not zero frame */
        result = kStatus_Success;
    }
    return result;
}

status_t SWT_GetTimestampRefResp(swt_handle_t *handle, swt_tsr_resp_t *tsr)
{
    status_t result         = kStatus_Fail;
    netc_rx_bdr_t *rxBdRing = NULL;
    netc_rx_bd_t *rxDesc    = NULL;
    uint64_t rxDmaBuff;
    uint16_t index;
    uint8_t rxBdRingIdx;

    if (handle->cfg.enUseMgmtRxBdRing)
    {
        rxBdRing    = &handle->mgmtRxBdRing;
        rxBdRingIdx = mgmtRxBdRingIdx;
    }
    else if (handle->epHandle->cfg.rxRingUse != 0U)
    {
        /* If no management Rx ring is specified, the host reason not zero frames will be received by Rx ring 0 */
        rxBdRing    = &handle->epHandle->rxBdRing[0];
        rxBdRingIdx = 0;
    }
    else
    {
        /* If both the switch and its associated EP not config the Rx BD ring, no frame can be received */
        return kStatus_InvalidArgument;
    }

    rxDesc = &rxBdRing->bdBase[rxBdRing->index];
    /* Check the current buffer descriptor's ready flag. The flag in first BD indicates entire frame ready status. */
    if ((rxDesc->resp.isReady != 0U) && ((netc_host_reason_t)rxDesc->resp.hr == kNETC_TimestampResp) &&
        (rxDesc->resp.error == 0U))
    {
        tsr->timestamp = rxDesc->resp.timestamp;
        tsr->txtsid    = rxDesc->resp.txtsid;
        /* Set the Rx buffer address in BD which is overwritten by BD writeback. */
        index     = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
        rxDmaBuff = rxBdRing->buffArray[index];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        rxDmaBuff = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)rxDmaBuff, kMEMORY_Local2DMA);
#endif
        rxDesc->standard.addr = rxDmaBuff;
        /* Updates the receive buffer descriptors flags, only clear necessary field. */
        rxDesc->writeback.isFinal = 0;
        rxDesc->writeback.isReady = 0;
        if (rxBdRing->extendDesc)
        {
            /* Extended BD occupies one more 16 bytes space. */
            rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
        }
        rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
        /* Update the Rx consumer index to free BD. */
        index = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
        NETC_SISetRxConsumer(handle->epHandle->hw.si, rxBdRingIdx, index);
        result = kStatus_Success;
    }

    return result;
}

status_t SWT_ReceiveFrameCopy(swt_handle_t *handle, void *buffer, uint32_t length, netc_frame_attr_t *attr)
{
    assert((handle != NULL) && (((buffer != NULL) && (length != 0U)) || (buffer == NULL)));
    netc_rx_bdr_t *rxBdRing = NULL;
    uint8_t rxBdRingIdx;

    if (handle->cfg.enUseMgmtRxBdRing)
    {
        rxBdRing    = &handle->mgmtRxBdRing;
        rxBdRingIdx = mgmtRxBdRingIdx;
    }
    else if (handle->epHandle->cfg.rxRingUse != 0U)
    {
        /* If no management Rx ring is specified, the host reason not zero frames will be received by Rx ring 0 */
        rxBdRing    = &handle->epHandle->rxBdRing[0];
        rxBdRingIdx = 0;
    }
    else
    {
        /* If both the switch and its associated EP not config the Rx BD ring, no frame can be received */
        return kStatus_InvalidArgument;
    }

    return EP_ReceiveFrameCopyCommon(handle->epHandle, rxBdRing, rxBdRingIdx, buffer, length, attr,
                                     handle->cfg.rxCacheMaintain);
}

status_t SWT_ReceiveFrame(swt_handle_t *handle, netc_frame_struct_t *frame, netc_frame_attr_t *attr)
{
    assert((handle != NULL) && (frame != NULL) && (handle->cfg.rxZeroCopy));

    status_t result         = kStatus_Success;
    netc_rx_bdr_t *rxBdRing = NULL;
    netc_rx_bd_t *rxDesc    = NULL;
    uint16_t index;
    uint16_t buffNum = 0;
    void *newBuff;
    uint8_t rxBdRingIdx;

    if (handle->cfg.enUseMgmtRxBdRing)
    {
        rxBdRing    = &handle->mgmtRxBdRing;
        rxBdRingIdx = mgmtRxBdRingIdx;
    }
    else if (handle->epHandle->cfg.rxRingUse != 0U)
    {
        /* If no management Rx ring is specified, the host reason not zero frames will be received by Rx ring 0 */
        rxBdRing    = &handle->epHandle->rxBdRing[0];
        rxBdRingIdx = 0;
    }
    else
    {
        /* If both the switch and its associated EP not config the Rx BD ring, no frame can be received */
        return kStatus_InvalidArgument;
    }

    rxDesc = &rxBdRing->bdBase[rxBdRing->index];
    /* Check the current buffer descriptor's ready flag. The flag in first BD indicates entire frame ready status. */
    if (rxDesc->writeback.isReady == 0U)
    {
        /* Reset the buffer array length. */
        frame->length = 0;
        return kStatus_NETC_RxFrameEmpty;
    }
    else
    {
        /* Check the status of the received frame. */
        if (rxDesc->writeback.error != 0U)
        {
            result = kStatus_NETC_RxFrameError;
        }
        else if ((netc_host_reason_t)rxDesc->writeback.hr != kNETC_TimestampResp)
        {
            if ((netc_host_reason_t)rxDesc->writeback.hr == kNETC_RegularFrame)
            {
                /* Return without receive when currently frame is regular frame */
                return kStatus_NETC_RxHRZeroFrame;
            }
            /* Check how many buffers will be taken away to receive one frame. */
            index = rxBdRing->index;
            do
            {
                buffNum++;

                /* Find the last BD of this frame. */
                if (rxDesc->writeback.isFinal != 0U)
                {
                    break;
                }

                if (rxBdRing->extendDesc)
                {
                    /* Extended BD needs additional offset. */
                    index = EP_IncreaseIndex(index, rxBdRing->len);
                }
                index  = EP_IncreaseIndex(index, rxBdRing->len);
                rxDesc = &rxBdRing->bdBase[index];
            } while (index != rxBdRing->index);

            /* The buffer array length provided by application is not enough to receive frame. */
            if (buffNum > frame->length)
            {
                return kStatus_NETC_LackOfResource;
            }

            /* Prepare the buffer from appliction to exchange with the buffer in the BD. */
            index = 0;
            do
            {
                newBuff = handle->cfg.rxBuffAlloc(handle, rxBdRing->buffSize, handle->cfg.userData);
                if (newBuff == NULL)
                {
                    while (index-- > 0U)
                    {
                        handle->cfg.rxBuffFree(handle, frame->buffArray[index].buffer, handle->cfg.userData);
                    }
                    /* When appliction buffer pool is not enough, drop frame in the BD to keep frame latest. */
                    result = kStatus_NETC_LackOfResource;
                    break;
                }

                /* Store in this strcuture, and exchange the buffer in the BD in below code. */
                frame->buffArray[index].buffer = newBuff;
                index++;
            } while (--buffNum != 0U);
        }
        else
        {
            /* Get Transmit Timestamp Reference Response messages, no need prepare new Rx buffer */
            return kStatus_NETC_RxTsrResp;
        }
    }

    result = EP_ReceiveFrameCommon(handle->epHandle, rxBdRing, rxBdRingIdx, frame, attr, (result != kStatus_Success),
                                   handle->cfg.rxCacheMaintain);

    return result;
}

static status_t SWT_GetIdleCmdBDRing(swt_handle_t *handle, netc_cbdr_handle_t *cdbrHandle)
{
    for (uint32_t i = 0U; i < handle->cfg.cmdRingUse; i++)
    {
        if (0U == (handle->hw.base->NUM_CBDR[i].CBDRSR & NETC_SW_CBDRSR_BUSY_MASK))
        {
            cdbrHandle->base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.base->NUM_CBDR[i].CBDRMR;
            cdbrHandle->cmdr   = &handle->cmdBdRing[i];
            cdbrHandle->buffer = s_cmdDataBuffer[i];
            return kStatus_Success;
        }
    }
    return kStatus_NETC_LackOfResource;
}

status_t SWT_CmdBDRInit(swt_handle_t *handle, netc_hw_swt_cbdr_idx_t ring, const netc_cmd_bdr_config_t *config)
{
    assert(handle != NULL);
    return NETC_CmdBDRInit((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.base->NUM_CBDR[ring].CBDRMR, config);
}

status_t SWT_CmdBDRDeinit(swt_handle_t *handle, netc_hw_swt_cbdr_idx_t ring)
{
    assert(handle != NULL);
    return NETC_CmdBDRDeinit((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.base->NUM_CBDR[ring].CBDRMR);
}

status_t SWT_RxIPFAddTableEntry(swt_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddIPFTableEntry(&cdbrHandle, config, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxIPFUpdateTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_UpdateIPFTableEntry(&cdbrHandle, entryID, cfg);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxIPFQueryTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_ipf_config_t *config)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryIPFTableEntry(&cdbrHandle, entryID, config);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxIPFDelTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelIPFTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxIPFResetMatchCounter(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_ResetIPFMatchCounter(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxIPFGetMatchedCount(swt_handle_t *handle, uint32_t entryID, uint64_t *count)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetIPFMatchedCount(&cdbrHandle, entryID, count);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeInit(swt_handle_t *handle, const netc_swt_bridge_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);

    /* Configure switch default VLAN filter entry */
    handle->hw.base->VFHTDECR0 =
        NETC_SW_VFHTDECR0_IPMFLE(config->dVFCfg.enIPMFlood) | NETC_SW_VFHTDECR0_IPMFE(config->dVFCfg.enIPMFilter) |
        NETC_SW_VFHTDECR0_STG_ID(config->dVFCfg.stgID) |
        ((config->dVFCfg.portMembership << NETC_SW_VFHTDECR0_PORT0_SHIFT) &
         (NETC_SW_VFHTDECR0_PORT4_MASK | NETC_SW_VFHTDECR0_PORT3_MASK | NETC_SW_VFHTDECR0_PORT2_MASK |
          NETC_SW_VFHTDECR0_PORT1_MASK | NETC_SW_VFHTDECR0_PORT0_MASK));
    handle->hw.base->VFHTDECR1 = NETC_SW_VFHTDECR1_BASE_ETEID(config->dVFCfg.baseETEID) |
                                 NETC_SW_VFHTDECR1_VL_MODE(config->dVFCfg.enUseFilterID) |
                                 NETC_SW_VFHTDECR1_FID(config->dVFCfg.filterID);
    handle->hw.base->VFHTDECR2 =
        NETC_SW_VFHTDECR2_MFO(config->dVFCfg.mfo) | NETC_SW_VFHTDECR2_MLO(config->dVFCfg.mlo) |
        ((config->dVFCfg.etaPortBitmap << NETC_SW_VFHTDECR2_ET_PORT0_SHIFT) &
         (NETC_SW_VFHTDECR2_ET_PORT4_MASK | NETC_SW_VFHTDECR2_ET_PORT3_MASK | NETC_SW_VFHTDECR2_ET_PORT2_MASK |
          NETC_SW_VFHTDECR2_ET_PORT1_MASK | NETC_SW_VFHTDECR2_ET_PORT0_MASK));
    return kStatus_Success;
}

status_t SWT_BridgeConfigPort(swt_handle_t *handle,
                              netc_hw_port_idx_t portIdx,
                              const netc_swt_port_bridge_config_t *config)
{
    assert((handle != NULL) && (config != NULL));

    NETC_PORT_Type *base  = handle->hw.ports[portIdx].port;
    uint32_t stgMode      = 0U;
    uint8_t tagAccepyMode = (uint8_t)config->acceptUntag | ((uint8_t)config->acceptPriorityTag << 1U) |
                            ((uint8_t)config->acceptSingleTag << 2U) | ((uint8_t)config->acceptDoubleTag << 3U);

    for (uint32_t i = 0U; i < 16U; i++)
    {
        stgMode |= ((uint32_t)config->stgMode[i] & NETC_PORT_BPSTGSR_STG_STATE0_MASK) << (i * 2U);
    }
    base->BPSTGSR = stgMode;
    base->BPDVR   = NETC_PORT_BPDVR_TXTAGA(config->txVlanAction) | NETC_PORT_BPDVR_RXVAM(!config->isRxVlanAware) |
                  NETC_PORT_BPDVR_RXTAGA(tagAccepyMode) | NETC_PORT_BPDVR_TPID(config->defaultVlan.tpid) |
                  NETC_PORT_BPDVR_PCP(config->defaultVlan.pcp) | NETC_PORT_BPDVR_DEI(config->defaultVlan.dei) |
                  NETC_PORT_BPDVR_VID(config->defaultVlan.vid);
    base->BPCR = NETC_PORT_BPCR_SRCPRND(!config->enSrcPortPrun) | NETC_PORT_BPCR_STAMVD(!config->enMacStationMove) |
                 NETC_PORT_BPCR_BCASTE(config->enBcastStormCtrl) | NETC_PORT_BPCR_MCASTE(config->enMcastStormCtrl) |
                 NETC_PORT_BPCR_UMCASTE(config->enUnMcastStormCtrl) |
                 NETC_PORT_BPCR_UUCASTE(config->enUnUcastStormCtrl) | NETC_PORT_BPCR_DYN_LIMIT(config->maxDynaFDBEntry);
    base->BPSCR0 =
        NETC_PORT_BPSCR0_BCASTRPEID(config->bcastRpEntryID) | NETC_PORT_BPSCR0_UUCASTRPEID(config->unUcastRpEntryID);
    base->BPSCR1 =
        NETC_PORT_BPSCR1_UMCASTRPEID(config->unMcastRpEntryID) | NETC_PORT_BPSCR1_MCASTRPEID(config->mcastEntryID);
    return kStatus_Success;
}

status_t SWT_BridgeConfigPortDefaultVid(swt_handle_t *handle,
                              netc_hw_port_idx_t portIdx, uint16_t vid)
{
    assert(handle != NULL);
    NETC_PORT_Type *base  = handle->hw.ports[portIdx].port;

    base->BPDVR = (base->BPDVR & ~NETC_PORT_BPDVR_VID_MASK) | NETC_PORT_BPDVR_VID(vid);

    return kStatus_Success;
}

status_t SWT_BridgeAddVFTableEntry(swt_handle_t *handle, netc_tb_vf_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL));
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_vf_req_data_t));
        /* Add entry to VLAN Filter Table and query the ENTRY_ID  */
        cdbrHandle.buffer->vf.request.cfge                       = config->cfge;
        cdbrHandle.buffer->vf.request.keye                       = config->keye;
        cdbrHandle.buffer->vf.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->vf.request.commonHeader.queryActions  = 1U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_vf_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_vf_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_VFTable;
        cmdBd.req.cmd                                            = kNETC_AddAndQueryEntry;
        /* Add operation only support Exact Key Element Match */
        cmdBd.req.accessType = kNETC_ExactKeyMatch;
        status               = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *entryID = cdbrHandle.buffer->vf.response.entryID;
        }
    }

    return status;
}

status_t SWT_BridgeUpdateVFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_vf_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_vf_req_data_t));
        /* Update entry in VLAN Filter Table based on the ENTRY_ID  */
        cdbrHandle.buffer->vf.request.cfge                       = *cfg;
        cdbrHandle.buffer->vf.request.entryID                    = entryID;
        cdbrHandle.buffer->vf.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->vf.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_vf_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_vf_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_VFTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeSearchVFTableEntry(swt_handle_t *handle,
                                       netc_tb_vf_search_criteria_t *sCriteria,
                                       netc_tb_vf_rsp_data_t *rsp)
{
    assert((handle != NULL) && (sCriteria != NULL) && (rsp != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Query entry in VF Table based on the search criteria */
        cdbrHandle.buffer->vf.request.sCriteria                 = *sCriteria;
        cdbrHandle.buffer->vf.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_vf_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_vf_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_VFTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_Search;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                *rsp = cdbrHandle.buffer->vf.response;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }

    return status;
}

status_t SWT_BridgeQueryVFTableEntry(swt_handle_t *handle,
                                       netc_tb_vf_keye_t *keye,
                                       netc_tb_vf_rsp_data_t *rsp)
{
    assert((handle != NULL) && (keye != NULL) && (rsp != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Query entry in VF Table based on the exact match criteria */
        cdbrHandle.buffer->vf.request.keye                       = *keye;
        cdbrHandle.buffer->vf.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_vf_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_vf_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_VFTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_ExactKeyMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                *rsp = cdbrHandle.buffer->vf.response;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }

    return status;
}


status_t SWT_BridgeDelVFTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_vf_req_data_t));
        cdbrHandle.buffer->vf.request.entryID                    = entryID;
        cdbrHandle.buffer->vf.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->vf.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = 8U;
        cmdBd.req.resLength                                      = 4U;
        cmdBd.req.tableId                                        = kNETC_VFTable;
        cmdBd.req.cmd                                            = kNETC_DeleteEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeAddFDBTableEntry(swt_handle_t *handle, netc_tb_fdb_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL));
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Add entry to FDB Table and query the ENTRY_ID  */
        cdbrHandle.buffer->fdb.request.cfge                       = config->cfge;
        cdbrHandle.buffer->fdb.request.keye                       = config->keye;
        cdbrHandle.buffer->fdb.request.commonHeader.updateActions = (uint16_t)kNETC_FDBCfgEUpdate;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions  = 1U;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = sizeof(netc_tb_fdb_req_data_t);
        cmdBd.req.resLength                                       = sizeof(netc_tb_fdb_rsp_data_t);
        cmdBd.req.tableId                                         = kNETC_FDBTable;
        cmdBd.req.cmd                                             = kNETC_AddAndQueryEntry;
        /* Add operation only support Exact Key Element Match */
        cmdBd.req.accessType = kNETC_ExactKeyMatch;
        status               = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *entryID = cdbrHandle.buffer->fdb.response.entryID;
        }
    }

    return status;
}

status_t SWT_BridgeUpdateFDBTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_fdb_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Update entry in FDB Table based on the ENTRY_ID  */
        cdbrHandle.buffer->fdb.request.cfge                       = *cfg;
        cdbrHandle.buffer->fdb.request.entryID                    = entryID;
        cdbrHandle.buffer->fdb.request.commonHeader.updateActions = (uint16_t)kNETC_FDBCfgEUpdate;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = sizeof(netc_tb_fdb_req_data_t);
        cmdBd.req.resLength                                       = sizeof(netc_tb_fdb_rsp_data_t);
        cmdBd.req.tableId                                         = kNETC_FDBTable;
        cmdBd.req.cmd                                             = kNETC_UpdateEntry;
        cmdBd.req.accessType                                      = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeSearchFDBTableEntry(swt_handle_t *handle,
                                       netc_tb_fdb_search_criteria_t *sCriteria,
                                       netc_tb_fdb_rsp_data_t *rsp)
{
    assert((handle != NULL) && (sCriteria != NULL) && (rsp != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Query entry in FDB Table based on the search criteria */
        cdbrHandle.buffer->fdb.request.sCriteria                 = *sCriteria;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_fdb_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_fdb_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_FDBTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_Search;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                *rsp = cdbrHandle.buffer->fdb.response;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }

    return status;
}

status_t SWT_BridgeQueryFDBTableEntry(swt_handle_t *handle,
                                       netc_tb_fdb_keye_t *keye,
                                       netc_tb_fdb_rsp_data_t *rsp)
{
    assert((handle != NULL) && (keye != NULL) && (rsp != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        /* Query entry in FDB Table based on the exact match criteria */
        cdbrHandle.buffer->fdb.request.keye                       = *keye;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_fdb_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_fdb_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_FDBTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_ExactKeyMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                *rsp = cdbrHandle.buffer->fdb.response;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }

    return status;
}

status_t SWT_BridgeDelFDBTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        cdbrHandle.buffer->fdb.request.entryID                    = entryID;
        cdbrHandle.buffer->fdb.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = 36U;
        cmdBd.req.resLength                                       = 4U;
        cmdBd.req.tableId                                         = kNETC_FDBTable;
        cmdBd.req.cmd                                             = kNETC_DeleteEntry;
        cmdBd.req.accessType                                      = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeGetFDBActivityState(swt_handle_t *handle, uint32_t entryID, netc_tb_fdb_acte_t *state)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fdb_req_data_t));
        cdbrHandle.buffer->fdb.request.entryID                    = entryID;
        cdbrHandle.buffer->fdb.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->fdb.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = 36U;
        cmdBd.req.resLength                                       = sizeof(netc_tb_fdb_rsp_data_t);
        cmdBd.req.tableId                                         = kNETC_FDBTable;
        cmdBd.req.cmd                                             = kNETC_QueryEntry;
        cmdBd.req.accessType                                      = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *state = cdbrHandle.buffer->fdb.response.acte;
        }
    }

    return status;
}

status_t SWT_BridgeAddL2MCFTableEntry(swt_handle_t *handle, netc_tb_l2mcf_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL));
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_l2mcf_req_data_t));
        /* Add entry to L2MCF Table and query the ENTRY_ID  */
        cdbrHandle.buffer->l2mcf.request.cfge                       = config->cfge;
        cdbrHandle.buffer->l2mcf.request.keye                       = config->keye;
        cdbrHandle.buffer->l2mcf.request.commonHeader.updateActions = (uint16_t)kNETC_FDBCfgEUpdate;
        cdbrHandle.buffer->l2mcf.request.commonHeader.queryActions  = 1U;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = sizeof(netc_tb_l2mcf_req_data_t);
        cmdBd.req.resLength                                         = sizeof(netc_tb_l2mcf_rsp_data_t);
        cmdBd.req.tableId                                           = kNETC_L2MCFTable;
        cmdBd.req.cmd                                               = kNETC_AddAndQueryEntry;
        /* Add operation only support Exact Key Element Match */
        cmdBd.req.accessType = kNETC_ExactKeyMatch;
        status               = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *entryID = cdbrHandle.buffer->l2mcf.response.entryID;
        }
    }
    return status;
}

status_t SWT_BridgeUpdateL2MCFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_l2mcf_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_l2mcf_req_data_t));
        /* Add entry to L2MCF Table base on the ENTRY_ID  */
        cdbrHandle.buffer->l2mcf.request.cfge                       = *cfg;
        cdbrHandle.buffer->l2mcf.request.entryID                    = entryID;
        cdbrHandle.buffer->l2mcf.request.commonHeader.updateActions = (uint16_t)kNETC_FDBCfgEUpdate;
        cdbrHandle.buffer->l2mcf.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = sizeof(netc_tb_l2mcf_req_data_t);
        cmdBd.req.resLength                                         = sizeof(netc_tb_l2mcf_rsp_data_t);
        cmdBd.req.tableId                                           = kNETC_L2MCFTable;
        cmdBd.req.cmd                                               = kNETC_UpdateEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeSearchL2MCFTableEntry(swt_handle_t *handle,
                                         netc_tb_l2mcf_search_criteria_t *sCriteria,
                                         netc_tb_l2mcf_rsp_data_t *rsp)
{
    assert((handle != NULL) && (sCriteria != NULL) && (rsp != NULL));
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_l2mcf_req_data_t));
        /* Query entry in L2MCF Table base on the search criteria */
        cdbrHandle.buffer->l2mcf.request.sCriteria                 = *sCriteria;
        cdbrHandle.buffer->l2mcf.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                             = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                        = sizeof(netc_tb_l2mcf_req_data_t);
        cmdBd.req.resLength                                        = sizeof(netc_tb_l2mcf_rsp_data_t);
        cmdBd.req.tableId                                          = kNETC_L2MCFTable;
        cmdBd.req.cmd                                              = kNETC_QueryEntry;
        cmdBd.req.accessType                                       = kNETC_Search;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                *rsp = cdbrHandle.buffer->l2mcf.response;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }
    return status;
}

status_t SWT_BridgeDelL2MCFTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_l2mcf_req_data_t));
        cdbrHandle.buffer->l2mcf.request.entryID                    = entryID;
        cdbrHandle.buffer->l2mcf.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->l2mcf.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 36U;
        /* Add command response data buffer only contains 4 bytes status filed */
        cmdBd.req.resLength  = 4U;
        cmdBd.req.tableId    = kNETC_L2MCFTable;
        cmdBd.req.cmd        = kNETC_DeleteEntry;
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_BridgeGetL2MCFActivityState(swt_handle_t *handle, uint32_t entryID, netc_tb_l2mcf_acte_t *state)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_l2mcf_req_data_t));
        cdbrHandle.buffer->l2mcf.request.entryID                    = entryID;
        cdbrHandle.buffer->l2mcf.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->l2mcf.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 36U;
        cmdBd.req.resLength                                         = sizeof(netc_tb_l2mcf_rsp_data_t);
        cmdBd.req.tableId                                           = kNETC_L2MCFTable;
        cmdBd.req.cmd                                               = kNETC_QueryEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *state = cdbrHandle.buffer->l2mcf.response.acte;
        }
    }
    return status;
}

status_t SWT_RxPSFPAddISITableEntry(swt_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL) && (entryID != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddISITableEntry(&cdbrHandle, config, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQueryISITableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_isi_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryISITableEntry(&cdbrHandle, entryID, config);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQueryISITableEntryWithKey(swt_handle_t *handle, netc_tb_isi_keye_t *keye, netc_tb_isi_rsp_data_t *rsp)
{
    assert((handle != NULL) && (keye != NULL) && (rsp != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryISITableEntryWithKey(&cdbrHandle, keye, rsp);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelISITableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelISITableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddISTableEntry(swt_handle_t *handle, netc_tb_is_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateISTableEntry(&cdbrHandle, config, true);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPUpdateISTableEntry(swt_handle_t *handle, netc_tb_is_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateISTableEntry(&cdbrHandle, config, false);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQueryISTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_is_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryISTableEntry(&cdbrHandle, entryID, config);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelISTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelISTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddISFTableEntry(swt_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL) && (entryID != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddISFTableEntry(&cdbrHandle, config, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPUpdateISFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_UpdateISFTableEntry(&cdbrHandle, entryID, cfg);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelISFTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelISFTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQueryISFTableEntry(swt_handle_t *handle, netc_tb_isf_keye_t *keye, netc_tb_isf_rsp_data_t *rsp)
{
    assert((handle != NULL) && (keye != NULL) && (rsp != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryISFTableEntry(&cdbrHandle, keye, rsp);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddISCTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddISCTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPGetISCStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetISCStatistic(&cdbrHandle, entryID, statistic);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPResetISCStatistic(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_ResetISCStatistic(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddSGITableEntry(swt_handle_t *handle, netc_tb_sgi_config_t *config)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateSGITableEntry(&cdbrHandle, config, true);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPUpdateSGITableEntry(swt_handle_t *handle, netc_tb_sgi_config_t *config)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateSGITableEntry(&cdbrHandle, config, false);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelSGITableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelSGITableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPGetSGIState(swt_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *state)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetSGIState(&cdbrHandle, entryID, state);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQuerySGITableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_sgi_rsp_data_t *rsp)
{
    assert((handle != NULL) && (rsp != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QuerySGITableEntry(&cdbrHandle, entryID, rsp);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddSGCLTableEntry(swt_handle_t *handle, netc_tb_sgcl_gcl_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddSGCLTableEntry(&cdbrHandle, config);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelSGCLTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelSGCLTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPGetSGCLGateList(swt_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length)
{
    assert((handle != NULL) && (gcl != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetSGCLGateList(&cdbrHandle, gcl, length);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPGetSGCLState(swt_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state)
{
    assert((handle != NULL) && (state != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetSGCLState(&cdbrHandle, entryID, state);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_AddEntry);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPUpdateRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_UpdateEntry);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPAddOrUpdateRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_AddOrUpdateEntry);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPDelRPTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_DelRPTableEntry(&cdbrHandle, entryID);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPQueryRPTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_rp_rsp_data_t *rsp)
{
    assert((handle != NULL) && (rsp != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_QueryRPTableEntry(&cdbrHandle, entryID, rsp);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_RxPSFPGetRPStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetRPStatistic(&cdbrHandle, entryID, statis);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxTrafficClassConfig(swt_handle_t *handle,
                                  netc_hw_port_idx_t portIdx,
                                  netc_hw_tc_idx_t tcIdx,
                                  const netc_port_tx_tc_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    NETC_PORT_Type *base = handle->hw.ports[portIdx].port;
    status_t result;
    uint32_t temp;

    if (!NETC_PortIsPseudo(base))
    {
        temp = base->PFPCR & (~((uint32_t)1U << (uint8_t)tcIdx));
        base->PFPCR   = temp | ((uint32_t)config->enPreemption << (uint8_t)tcIdx);
    }
    temp        = base->PDGSR & (~((uint32_t)1U << (uint32_t)tcIdx));
    base->PDGSR = temp | ((uint32_t)config->enTcGate << (uint32_t)tcIdx);

    result = NETC_PortConfigTcMaxSDU(base, tcIdx, &config->sduCfg);
    if ((kStatus_Success == result) && (config->enableCbs))
    {
        result = NETC_PortConfigTcCBS(base, tcIdx, &config->cbsCfg);
    }
    return result;
}

#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
status_t SWT_TxPortTGSEnable(swt_handle_t *handle, netc_hw_port_idx_t portIdx, bool enable, uint8_t gateState)
#else
status_t SWT_TxPortTGSEnable(swt_handle_t *handle, netc_hw_port_idx_t portIdx, bool enable)
#endif
{
    assert(handle != NULL);
    status_t result = kStatus_Success;

    if (enable)
    {
        handle->hw.ports[portIdx].port->PTGSCR |= NETC_PORT_PTGSCR_TGE_MASK;
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
        netc_tgs_gate_entry_t gate[2] = {{.interval = 50000U, .tcGateState = gateState},
                                         {.interval = 50000U, .tcGateState = gateState}};
        netc_tb_tgs_gcl_t wTgsList    = {
            .entryID = (netc_tb_tgs_entry_id_t)portIdx, .cycleTime = 1000000U, .numEntries = 2U, .gcList = &gate[0]};
        uint64_t time;
        /* Enable master bus and memory access for default ns timer*/
        TMR_PCI_HDR_TYPE0->PCI_CFH_CMD |=
            (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);
        NETC_TimerGetTime(TMR0_BASE, &time);
        wTgsList.baseTime = time;
        result            = SWT_TxTGSConfigAdminGcl(handle, &wTgsList);
#endif
    }
    else
    {
        handle->hw.ports[portIdx].port->PTGSCR &= ~NETC_PORT_PTGSCR_TGE_MASK;
    }

    return result;
}

status_t SWT_TxTGSConfigAdminGcl(swt_handle_t *handle, netc_tb_tgs_gcl_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_Success;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        if (0U != (handle->hw.ports[config->entryID].port->PTGAGLSR & NETC_PORT_PTGAGLSR_CFG_PEND_MASK))
        {
            /* Removed the previous pending administrative gate control list */
            netc_tb_tgs_gcl_t emptyList = {.entryID = config->entryID, .numEntries = 0U};
            status                      = NETC_ConfigTGSAdminList(&cdbrHandle, &emptyList);

            if (kStatus_Success != status)
            {
                return status;
            }
        }
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051587) && FSL_FEATURE_NETC_HAS_ERRATA_051587
        if (0U != (handle->hw.ports[config->entryID].port->PTGAGLSR & NETC_PORT_PTGAGLSR_TG_MASK))
        {
            netc_cmd_bd_t cmdBd = {0};
            uint32_t cycleTime;
            uint64_t time, minBaseTime;

            /* Read the previous active Operationa gate control list cycle time*/
            (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_tgs_data_t));
            cdbrHandle.buffer->tgs.request.entryID                    = config->entryID;
            cdbrHandle.buffer->tgs.request.commonHeader.updateActions = 0U;
            cdbrHandle.buffer->tgs.request.commonHeader.queryActions  = 0U;
            cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
            cmdBd.req.reqLength                                       = 8U;
            /* Set Response Data Buffer length to MAX */
            cmdBd.req.resLength  = sizeof(netc_tb_tgs_data_t);
            cmdBd.req.tableId    = kNETC_TGSTable;
            cmdBd.req.cmd        = kNETC_QueryEntry;
            cmdBd.req.accessType = kNETC_EntryIDMatch;
            status               = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
            if (kStatus_Success == status)
            {
                cycleTime = ((netc_tb_tgs_olse_t *)(uintptr_t)(&((uint8_t *)cdbrHandle.buffer)[36U]))->operCycleTime;
            }
            else
            {
                return status;
            }
            /* Get Current Time */
            NETC_TimerGetTime(TMR0_BASE, &time);
            /* The minimum base time = current time + advance time (0.1us) + command processing time (~90us) + (2 *
             * operational cycle times) */
            minBaseTime = time + 100100U + (2U * cycleTime);
            /* Check, if there is operating GCL and if admin base time is in range described in ERR051587*/
            if ((config->numEntries > 0U) && (config->baseTime < minBaseTime))
            {
                config->baseTime +=
                    (((uint64_t)ceil(((double)minBaseTime - (double)config->baseTime) / (double)config->cycleTime))) *
                    config->cycleTime;
            }
        }
#endif
        /* Install the new administrative gate control list */
        return NETC_ConfigTGSAdminList(&cdbrHandle, config);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxtTGSGetOperGcl(swt_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length)
{
    assert((handle != NULL) && (gcl != NULL));
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        return NETC_GetTGSOperationList(&cdbrHandle, gcl, length);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_FMAddTableEntry(swt_handle_t *handle, netc_tb_fm_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fm_req_data_t));
        /* Add entry to FM Table */
        cdbrHandle.buffer->fm.request.cfge                       = config->cfge;
        cdbrHandle.buffer->fm.request.entryID                    = config->entryID;
        cdbrHandle.buffer->fm.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->fm.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_fm_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_fm_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_FMTable;
        cmdBd.req.cmd                                            = kNETC_AddEntry;
        /* Add operation only support Entry ID Match */
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_FMUpdateTableEntry(swt_handle_t *handle, netc_tb_fm_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fm_req_data_t));
        /* Add entry to FM Table */
        cdbrHandle.buffer->fm.request.cfge                       = config->cfge;
        cdbrHandle.buffer->fm.request.entryID                    = config->entryID;
        cdbrHandle.buffer->fm.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->fm.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_fm_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_fm_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_FMTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_FMDelTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fm_req_data_t));
        cdbrHandle.buffer->fm.request.entryID                    = entryID;
        cdbrHandle.buffer->fm.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->fm.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_fm_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_fm_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_FMTable;
        cmdBd.req.cmd                                            = kNETC_DeleteEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_FMDUpdateTableEntry(swt_handle_t *handle, netc_tb_fmd_update_config_t *config, uint32_t length)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_fmd_req_data_t));
        cdbrHandle.buffer->fmd.request.entryID                    = config->entryID;
        cdbrHandle.buffer->fmd.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->fmd.request.commonHeader.queryActions  = 0U;
        (void)memcpy((void *)&cdbrHandle.buffer->fmd.request.cfge, (void *)&config->cfge, length);
        cmdBd.req.addr      = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength = length + 8U;
        cmdBd.req.resLength = length + 8U;
        cmdBd.req.tableId   = kNETC_FMDTable;
        cmdBd.req.cmd       = kNETC_UpdateEntry;
        /* Only support Entry ID Match */
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_FMDQueryTableEntry(swt_handle_t *handle, netc_tb_fmd_query_buffer_t *query, uint32_t length)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, length + 4U);
        cdbrHandle.buffer->fmd.request.entryID                    = query->entryID;
        cdbrHandle.buffer->fmd.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->fmd.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = 8U;
        cmdBd.req.resLength                                       = length + 4U;
        cmdBd.req.tableId                                         = kNETC_FMDTable;
        cmdBd.req.cmd                                             = kNETC_QueryEntry;
        /* Only support Entry ID Match */
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        status               = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            (void)memcpy(&query->cfge, &cdbrHandle.buffer->fmd.response.cfge, length);
        }
    }

    return status;
}

status_t SWT_TxEPPAddETTableEntry(swt_handle_t *handle, netc_tb_et_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_et_req_data_t));
        /* Add entry to ET Table */
        cdbrHandle.buffer->et.request.cfge                       = config->cfge;
        cdbrHandle.buffer->et.request.entryID                    = config->entryID;
        cdbrHandle.buffer->et.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->et.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_et_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_et_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ETTable;
        cmdBd.req.cmd                                            = kNETC_AddEntry;
        /* Add operation only support Entry ID Match */
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxEPPUpdateETTableEntry(swt_handle_t *handle, netc_tb_et_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_et_req_data_t));
        /* Update entry to ET Table */
        cdbrHandle.buffer->et.request.cfge                       = config->cfge;
        cdbrHandle.buffer->et.request.entryID                    = config->entryID;
        cdbrHandle.buffer->et.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->et.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_et_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_et_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ETTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        /* Add operation only support Entry ID Match */
        cmdBd.req.accessType = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxEPPQueryETTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_et_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_NETC_LackOfResource;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_et_req_data_t));
        cdbrHandle.buffer->et.request.entryID                    = entryID;
        cdbrHandle.buffer->et.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->et.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_et_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_et_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ETTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            if (0U != cmdBd.resp.numMatched)
            {
                config->entryID = cdbrHandle.buffer->et.response.entryID;
                config->cfge = cdbrHandle.buffer->et.response.cfge;
            }
            else
            {
                status = kStatus_NETC_NotFound;
            }
        }
    }

    return status;
}

status_t SWT_TxEPPDelETTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_et_req_data_t));
        cdbrHandle.buffer->et.request.entryID                    = entryID;
        cdbrHandle.buffer->et.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->et.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_et_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_et_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ETTable;
        cmdBd.req.cmd                                            = kNETC_DeleteEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxEPPQosToVlanConfig(swt_handle_t *handle, const netc_swt_qos_to_vlan_config_t *config)
{
    for (uint32_t i = 0U; i < 2U; i++)
    {
        for (uint32_t j = 0U; j < 4U; j++)
        {
            handle->hw.base->MAP_PCP[i].QOSVLANMPR[j] =
                NETC_SW_QOSVLANMPR_IPV0_DR0(config->profiles[i].qos[j * 8U]) |
                NETC_SW_QOSVLANMPR_IPV0_DR1(config->profiles[i].qos[j * 8U + 1U]) |
                NETC_SW_QOSVLANMPR_IPV0_DR2(config->profiles[i].qos[j * 8U + 2U]) |
                NETC_SW_QOSVLANMPR_IPV0_DR1(config->profiles[i].qos[j * 8U + 3U]) |
                NETC_SW_QOSVLANMPR_IPV1_DR0(config->profiles[i].qos[j * 8U + 4U]) |
                NETC_SW_QOSVLANMPR_IPV1_DR1(config->profiles[i].qos[j * 8U + 5U]) |
                NETC_SW_QOSVLANMPR_IPV1_DR2(config->profiles[i].qos[j * 8U + 6U]) |
                NETC_SW_QOSVLANMPR_IPV1_DR3(config->profiles[i].qos[j * 8U + 7U]);
        }
        handle->hw.base->PCP2PCPMPR[i] =
            NETC_SW_PCP2PCPMPR_PCP0(config->profiles[i].pcp[0]) | NETC_SW_PCP2PCPMPR_PCP1(config->profiles[i].pcp[1]) |
            NETC_SW_PCP2PCPMPR_PCP2(config->profiles[i].pcp[2]) | NETC_SW_PCP2PCPMPR_PCP3(config->profiles[i].pcp[3]) |
            NETC_SW_PCP2PCPMPR_PCP4(config->profiles[i].pcp[4]) | NETC_SW_PCP2PCPMPR_PCP5(config->profiles[i].pcp[5]) |
            NETC_SW_PCP2PCPMPR_PCP6(config->profiles[i].pcp[6]) | NETC_SW_PCP2PCPMPR_PCP7(config->profiles[i].pcp[7]);
    }
    return kStatus_Success;
}

status_t SWT_GetECStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_ec_stse_t *statistic)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_ec_req_data_t));
        cdbrHandle.buffer->ec.request.entryID                    = entryID;
        cdbrHandle.buffer->ec.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->ec.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_ec_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_ec_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *statistic = cdbrHandle.buffer->ec.response.stse;
        }
    }
    return status;
}

status_t SWT_ResetECStatistic(swt_handle_t *handle, uint32_t entryID)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_ec_req_data_t));
        /* Reset EC Table according to the ENTRY_ID (EC_EID) */
        cdbrHandle.buffer->ec.request.entryID                    = entryID;
        cdbrHandle.buffer->ec.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->ec.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_ec_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_ec_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxETMConfigClassQueue(swt_handle_t *handle, netc_tb_etmcq_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_etmcq_data_t));
        cdbrHandle.buffer->cq.request.entryID = config->entryID;
        cdbrHandle.buffer->cq.request.cfge    = config->cfge;
        cdbrHandle.buffer->cq.request.commonHeader.updateActions =
            (uint16_t)kNETC_CQCfgEUpdate | (uint16_t)kNETC_CQStsEUpdate;
        cdbrHandle.buffer->cq.request.commonHeader.queryActions = 0U;
        cmdBd.req.addr                                          = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                     = sizeof(netc_tb_etmcq_req_data_t);
        cmdBd.req.resLength                                     = sizeof(netc_tb_etmcq_rsp_data_t);
        cmdBd.req.tableId                                       = kNETC_ECQTable;
        cmdBd.req.cmd                                           = kNETC_UpdateEntry;
        cmdBd.req.accessType                                    = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_GetETMClassQueueStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_etmcq_stse_t *statistic)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_etmcq_data_t));
        cdbrHandle.buffer->cq.request.entryID                    = entryID;
        cdbrHandle.buffer->cq.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->cq.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_etmcq_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_etmcq_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECQTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *statistic = cdbrHandle.buffer->cq.response.stse;
        }
    }
    return status;
}
status_t SWT_TxETMConfigClassScheduler(swt_handle_t *handle, netc_tb_etmcs_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_etmcs_data_t));
        cdbrHandle.buffer->cs.request.entryID                    = config->entryID;
        cdbrHandle.buffer->cs.request.cfge                       = config->cfge;
        cdbrHandle.buffer->cs.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->cs.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_etmcs_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_etmcs_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECSTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_TxETMConfigCongestionGroup(swt_handle_t *handle, netc_tb_etmcg_config_t *config)
{
    netc_cmd_bd_t cmdBd = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_etmcg_data_t));
        cdbrHandle.buffer->cg.request.entryID                    = config->entryID;
        cdbrHandle.buffer->cg.request.cfge                       = config->cfge;
        cdbrHandle.buffer->cg.request.commonHeader.updateActions = 1U;
        cdbrHandle.buffer->cg.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_etmcg_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_etmcg_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECGTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        return NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }
    else
    {
        return kStatus_NETC_LackOfResource;
    }
}

status_t SWT_GetETMCongestionGroupStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_etmcg_stse_t *statistic)
{
    netc_cmd_bd_t cmdBd = {0};
    status_t status     = kStatus_NETC_LackOfResource;
    netc_cbdr_handle_t cdbrHandle;

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        (void)memset(cdbrHandle.buffer, 0, sizeof(netc_tb_etmcg_data_t));
        cdbrHandle.buffer->cg.request.entryID                    = entryID;
        cdbrHandle.buffer->cg.request.commonHeader.updateActions = 0U;
        cdbrHandle.buffer->cg.request.commonHeader.queryActions  = 0U;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_etmcg_req_data_t);
        cmdBd.req.resLength                                      = sizeof(netc_tb_etmcg_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_ECGTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (kStatus_Success == status)
        {
            *statistic = cdbrHandle.buffer->cg.response.stse;
        }
    }
    return status;
}

status_t SWT_FRERAddISEQGTableEntry(swt_handle_t *handle, netc_tb_iseqg_config_t *config)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ISQGITCAPR & NETC_SW_ENETC_ISQGITCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (config->entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->iseqg.request.entryID                    = config->entryID;
        cdbrHandle.buffer->iseqg.request.commonHeader.updateActions = 1;
        cdbrHandle.buffer->iseqg.request.commonHeader.queryActions  = 0;
        cdbrHandle.buffer->iseqg.request.cfge                       = config->cfge;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 12U;
        cmdBd.req.resLength                                         = 8U;
        cmdBd.req.tableId                                           = kNETC_ISGTable;
        cmdBd.req.cmd                                               = kNETC_AddEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_FRERUpdateISEQGTableEntry(swt_handle_t *handle, netc_tb_iseqg_config_t *config)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ISQGITCAPR & NETC_SW_ENETC_ISQGITCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (config->entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->iseqg.request.entryID                    = config->entryID;
        cdbrHandle.buffer->iseqg.request.commonHeader.updateActions = 1;
        cdbrHandle.buffer->iseqg.request.commonHeader.queryActions  = 0;
        cdbrHandle.buffer->iseqg.request.cfge                       = config->cfge;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 12U;
        cmdBd.req.resLength                                         = 8U;
        cmdBd.req.tableId                                           = kNETC_ISGTable;
        cmdBd.req.cmd                                               = kNETC_UpdateEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_FRERDelISEQGTableEntry(swt_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ISQGITCAPR & NETC_SW_ENETC_ISQGITCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->iseqg.request.entryID                    = entryID;
        cdbrHandle.buffer->iseqg.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->iseqg.request.commonHeader.queryActions  = 0;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 12U;
        cmdBd.req.resLength                                         = 8U;
        cmdBd.req.tableId                                           = kNETC_ISGTable;
        cmdBd.req.cmd                                               = kNETC_DeleteEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_FRERGetISEQGState(swt_handle_t *handle, uint32_t entryID, netc_tb_iseqg_sgse_t *state)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ISQGITCAPR & NETC_SW_ENETC_ISQGITCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->iseqg.request.entryID                    = entryID;
        cdbrHandle.buffer->iseqg.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->iseqg.request.commonHeader.queryActions  = 0;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 12U;
        cmdBd.req.resLength                                         = 8U;
        cmdBd.req.tableId                                           = kNETC_ISGTable;
        cmdBd.req.cmd                                               = kNETC_QueryEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (status == kStatus_Success)
        {
            *state = cdbrHandle.buffer->iseqg.response.sgse;
        }
    }

    return status;
}

status_t SWT_FRERConfigESEQRTableEntry(swt_handle_t *handle, netc_tb_eseqr_config_t *config)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ESQRTCAPR & NETC_SW_ENETC_ESQRTCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (config->entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->eseqr.request.entryID                    = config->entryID;
        cdbrHandle.buffer->eseqr.request.commonHeader.updateActions = 0x7;
        cdbrHandle.buffer->eseqr.request.commonHeader.queryActions  = 0;
        cdbrHandle.buffer->eseqr.request.cfge                       = config->cfge;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 16U;
        cmdBd.req.resLength                                         = 84U;
        cmdBd.req.tableId                                           = kNETC_ESRTable;
        cmdBd.req.cmd                                               = kNETC_UpdateEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_FRERQueryESEQRTableEntry(swt_handle_t *handle,
                                   uint32_t entryID,
                                   netc_tb_eseqr_stse_t *statistic,
                                   netc_tb_eseqr_cfge_t *config,
                                   netc_tb_eseqr_srse_t *state)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.common->ESQRTCAPR & NETC_SW_ENETC_ESQRTCAPR_NUM_ENTRIES_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->eseqr.request.entryID                    = entryID;
        cdbrHandle.buffer->eseqr.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->eseqr.request.commonHeader.queryActions  = 0;
        cmdBd.req.addr                                              = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                         = 16U;
        cmdBd.req.resLength                                         = 84U;
        cmdBd.req.tableId                                           = kNETC_ESRTable;
        cmdBd.req.cmd                                               = kNETC_QueryEntry;
        cmdBd.req.accessType                                        = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (status == kStatus_Success)
        {
            *statistic = cdbrHandle.buffer->eseqr.response.stse;

            if (config != NULL)
            {
                *config    = cdbrHandle.buffer->eseqr.response.cfge;
            }

            *state     = cdbrHandle.buffer->eseqr.response.srse;
        }
    }

    return status;
}

status_t SWT_FRERGetESEQRStatistic(swt_handle_t *handle,
                                   uint32_t entryID,
                                   netc_tb_eseqr_stse_t *statistic,
                                   netc_tb_eseqr_srse_t *state)
{
    return SWT_FRERQueryESEQRTableEntry(handle, entryID, statistic, NULL, state);
}

status_t SWT_UpdateBPTableEntry(swt_handle_t *handle, netc_tb_bp_config_t *config)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_BP_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (config->entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->bp.request.entryID                    = config->entryID;
        cdbrHandle.buffer->bp.request.commonHeader.updateActions = 0x3;
        cdbrHandle.buffer->bp.request.commonHeader.queryActions  = 0;
        cdbrHandle.buffer->bp.request.cfge                       = config->cfge;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = sizeof(netc_tb_bp_req_data_t);
        cmdBd.req.resLength                                      = 0;
        cmdBd.req.tableId                                        = kNETC_BPTable;
        cmdBd.req.cmd                                            = kNETC_UpdateEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_GetBPEntryState(swt_handle_t *handle, uint32_t entryID, netc_tb_bp_bpse_t *state)
{
    assert(handle != NULL);

    uint32_t entryNumMax = handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_BP_MASK;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->bp.request.entryID                    = entryID;
        cdbrHandle.buffer->bp.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->bp.request.commonHeader.queryActions  = 0;
        cmdBd.req.addr                                           = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                      = 8U;
        cmdBd.req.resLength                                      = sizeof(netc_tb_bp_rsp_data_t);
        cmdBd.req.tableId                                        = kNETC_BPTable;
        cmdBd.req.cmd                                            = kNETC_QueryEntry;
        cmdBd.req.accessType                                     = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (status == kStatus_Success)
        {
            *state = cdbrHandle.buffer->bp.response.bpse;
        }
    }

    return status;
}

status_t SWT_UpdateSBPTableEntry(swt_handle_t *handle, netc_tb_sbp_config_t *config)
{
    assert(handle != NULL);

    uint32_t entryNumMax = (handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_SPB_MASK) >> NETC_SW_BPCAPR_NUM_SPB_SHIFT;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (config->entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->sbp.request.entryID                    = config->entryID;
        cdbrHandle.buffer->sbp.request.commonHeader.updateActions = 0x3;
        cdbrHandle.buffer->sbp.request.commonHeader.queryActions  = 0;
        cdbrHandle.buffer->sbp.request.cfge                       = config->cfge;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = sizeof(netc_tb_sbp_req_data_t);
        cmdBd.req.resLength                                       = 0;
        cmdBd.req.tableId                                         = kNETC_SBPTable;
        cmdBd.req.cmd                                             = kNETC_UpdateEntry;
        cmdBd.req.accessType                                      = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
    }

    return status;
}

status_t SWT_GetSBPEntryState(swt_handle_t *handle, uint32_t entryID, netc_tb_sbp_sbpse_t *state)
{
    assert(handle != NULL);

    uint32_t entryNumMax = (handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_SPB_MASK) >> NETC_SW_BPCAPR_NUM_SPB_SHIFT;
    status_t status      = kStatus_NETC_LackOfResource;
    netc_cmd_bd_t cmdBd  = {0};
    netc_cbdr_handle_t cdbrHandle;

    if (entryID >= entryNumMax)
    {
        return kStatus_InvalidArgument;
    }

    if (SWT_GetIdleCmdBDRing(handle, &cdbrHandle) == kStatus_Success)
    {
        cdbrHandle.buffer->sbp.request.entryID                    = entryID;
        cdbrHandle.buffer->sbp.request.commonHeader.updateActions = 0;
        cdbrHandle.buffer->sbp.request.commonHeader.queryActions  = 0;
        cmdBd.req.addr                                            = (uintptr_t)cdbrHandle.buffer;
        cmdBd.req.reqLength                                       = 8U;
        cmdBd.req.resLength                                       = sizeof(netc_tb_sbp_rsp_data_t);
        cmdBd.req.tableId                                         = kNETC_SBPTable;
        cmdBd.req.cmd                                             = kNETC_QueryEntry;
        cmdBd.req.accessType                                      = kNETC_EntryIDMatch;
        status = NETC_CmdBDSendCommand(cdbrHandle.base, cdbrHandle.cmdr, &cmdBd, kNETC_NtmpV2_0);
        if (status == kStatus_Success)
        {
            *state = cdbrHandle.buffer->sbp.response.sbpse;
        }
    }

    return status;
}
