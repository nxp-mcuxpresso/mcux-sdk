/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_netc_endpoint.h"
#include "fsl_netc_timer.h"
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051587) && FSL_FEATURE_NETC_HAS_ERRATA_051587
#include <math.h>
#endif

/*! @name Defines some Ethernet parameters. */
/*@{*/
#define NETC_ENETC_TXFRAME_LEN_MAX (9600U) /*!< The Maximum length of frame length. */
#define NETC_ENETC_TXFRAME_LEN_MIN (16U)   /*!< The Minimum length of frame length. */
/*@}*/

/*! @brief Mask the cache management code if cache control is disabled. */
#if !defined(FSL_ETH_ENABLE_CACHE_CONTROL)
#define NETC_DcacheInvalidateByRange(address, sizeByte)
#define NETC_DcacheCleanByRange(address, sizeByte)
#else
#define NETC_DcacheInvalidateByRange(address, sizeByte) DCACHE_InvalidateByRange(address, sizeByte)
#define NETC_DcacheCleanByRange(address, sizeByte)      DCACHE_CleanByRange(address, sizeByte)
#endif

/*! @brief Command BD common buffer. */
AT_NONCACHEABLE_SECTION_ALIGN(static netc_tb_data_buffer_t s_cmdData, 16);

/*!
 * @brief Get register map resource for handle
 *
 * @param handle  The EP handle.
 * @param si      The SI object.
 */
static void EP_GetBaseResource(ep_handle_t *handle, netc_hw_si_idx_t si)
{
    NETC_SocGetBaseResource(&handle->hw, si);
}

/*!
 * @brief Store necessary configuration constant in the handle
 *
 * @param handle  The EP handle.
 * @param config  The user configuration.
 */
static void EP_StoreConfig(ep_handle_t *handle, const ep_config_t *config)
{
    handle->cfg.si              = config->si;
    handle->cfg.rxRingUse       = config->siConfig.rxRingUse;
    handle->cfg.txRingUse       = config->siConfig.txRingUse;
    handle->cfg.rxBdrGroupNum   = config->siConfig.rxBdrGroupNum;
    handle->cfg.ringPerBdrGroup = config->siConfig.ringPerBdrGroup;
    handle->cfg.entryNum        = config->entryNum;
    handle->cfg.reclaimCallback = config->reclaimCallback;
    handle->cfg.userData        = config->userData;
    handle->cfg.rxCacheMaintain = config->rxCacheMaintain;
    handle->cfg.txCacheMaintain = config->txCacheMaintain;
    handle->cfg.rxZeroCopy      = config->rxZeroCopy;
    handle->cfg.rxBuffAlloc     = config->rxBuffAlloc;
    handle->cfg.rxBuffFree      = config->rxBuffFree;
}

/*!
 * @brief Free all Rx buffers
 *
 * @param handle  The EP handle.
 */
static void EP_RxBufferFreeAll(ep_handle_t *handle)
{
    netc_rx_bdr_t *rxBdRing;
    uint32_t maxHwBdNum;
    uint32_t index;
    uint8_t ring;

    if (handle->cfg.rxZeroCopy)
    {
        for (ring = 0U; ring < handle->cfg.rxRingUse; ring++)
        {
            rxBdRing = &handle->rxBdRing[ring];
            /* Hardware BD number means actual BD number in hardware view, two standard BDs act as one extended BD. */
            maxHwBdNum = rxBdRing->extendDesc ? (rxBdRing->len / 2U) : rxBdRing->len;

            for (index = 0U; index < maxHwBdNum; index++)
            {
                if (rxBdRing->buffArray[index] != 0U)
                {
                    handle->cfg.rxBuffFree(handle, ring, (void *)(uint8_t *)(uintptr_t)rxBdRing->buffArray[index],
                                           handle->cfg.userData);
                }
            }
        }
    }
}

/*!
 * @brief Allocate Rx buffers for Rx BD rings
 *
 * @param handle     The EP handle.
 * @param config     The EP configuration.
 * @param bdrConfig  The BD ring configuration.
 */
static status_t EP_RxBufferAllocAll(ep_handle_t *handle, const ep_config_t *config, const netc_bdr_config_t *bdrConfig)
{
    status_t result = kStatus_Success;
    const netc_rx_bdr_config_t *rxRingConfig;
    netc_rx_bd_t *rxDesc;
    uint64_t buffAddr;
    uint16_t buffIdx;
    uint16_t index;
    uint8_t ring;

    for (ring = 0U; ring < config->siConfig.rxRingUse; ring++)
    {
        rxRingConfig = &bdrConfig->rxBdrConfig[ring];
        rxDesc       = &rxRingConfig->bdArray[0];

        /* Store address information in the array in case the buffer address is lost due to Rx BD write-back. */
        handle->rxBdRing[ring].buffArray = rxRingConfig->buffAddrArray;

        /* Initialize the buffers in Rx BD ring. */
        for (index = 0U; index < rxRingConfig->len; index++)
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
            if (!config->rxZeroCopy)
            {
                /* Get Rx buffer address from the address array provided by application. */
                buffAddr = handle->rxBdRing[ring].buffArray[buffIdx];
            }
            else
            {
                /* Get Rx buffer address from the allocation function provided by application. */
                buffAddr = (uint64_t)(uintptr_t)(uint8_t *)handle->cfg.rxBuffAlloc(
                    handle, ring, handle->rxBdRing[ring].buffSize, handle->cfg.userData);
                if (buffAddr == 0U)
                {
                    EP_RxBufferFreeAll(handle);
                    result = kStatus_NETC_LackOfResource;
                    break;
                }

                /* Keep Rx buffer address from pool in driver until it's freed. */
                handle->rxBdRing[ring].buffArray[buffIdx] = buffAddr;
            }

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            buffAddr = MEMORY_ConvertMemoryMapAddress((uintptr_t)buffAddr, kMEMORY_Local2DMA);
#endif
            rxDesc->standard.addr = buffAddr;
            rxDesc++;
        }

        if (result != kStatus_Success)
        {
            break;
        }
    }

    return result;
}

/*!
 * @brief Initialize the Tx/Rx BD ring
 *
 * @param handle     The EP handle.
 * @param config     The EP configuration.
 * @param bdrConfig  The BD ring configuration.
 */
static status_t EP_DescriptorInit(ep_handle_t *handle, const ep_config_t *config, const netc_bdr_config_t *bdrConfig)
{
    assert(bdrConfig != NULL);

    status_t result  = kStatus_Success;
    uint8_t idxStart = 0U;
    uint8_t ring;

    /* Setup Tx/Rx buffer descriptor rings. */
    if (NETC_EnetcHasManagement(handle->hw.base) && (getSiNum(handle->cfg.si) == 0U))
    {
        /* For management ENETC, the SI 0 hardware Tx ring index 0 has been keep for direct switch enqueue feature */
        idxStart = 1;
    }
    for (ring = 0; ring < config->siConfig.txRingUse; ring++)
    {
        if (NETC_SIConfigTxBDR(handle->hw.si, ring + idxStart, &bdrConfig->txBdrConfig[ring]) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        handle->txBdRing[ring].bdBase    = bdrConfig->txBdrConfig[ring].bdArray;
        handle->txBdRing[ring].dirtyBase = bdrConfig->txBdrConfig[ring].dirtyArray;
        handle->txBdRing[ring].len       = bdrConfig->txBdrConfig[ring].len;
    }
    for (ring = 0; ring < config->siConfig.rxRingUse; ring++)
    {
        if (NETC_SIConfigRxBDR(handle->hw.si, ring, &bdrConfig->rxBdrConfig[ring]) != kStatus_Success)
        {
            return kStatus_Fail;
        }
        handle->rxBdRing[ring].extendDesc = bdrConfig->rxBdrConfig[ring].extendDescEn;
        handle->rxBdRing[ring].bdBase     = bdrConfig->rxBdrConfig[ring].bdArray;
        handle->rxBdRing[ring].len        = bdrConfig->rxBdrConfig[ring].len;
        handle->rxBdRing[ring].buffSize   = bdrConfig->rxBdrConfig[ring].buffSize;
    }

    /* Allocate Rx buffers to the BDs. */
    result = EP_RxBufferAllocAll(handle, config, bdrConfig);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Enable the used BD ring. */
    for (ring = 0; ring < config->siConfig.rxRingUse; ring++)
    {
        NETC_SIRxRingEnable(handle->hw.si, ring, true);
    }

    return kStatus_Success;
}

/*!
 * @brief Setup Station Interface
 *
 * @param handle     The EP handle.
 * @param si         The SI number.
 * @param epConfig   The EP configuration.
 * @param bdrConfig  The BD ring configuration.
 */
static status_t EP_SISetup(ep_handle_t *handle,
                           uint8_t si,
                           const ep_config_t *epConfig,
                           const netc_bdr_config_t *bdrConfig)
{
    status_t result;

    if (((epConfig->siConfig.ringPerBdrGroup * epConfig->siConfig.rxBdrGroupNum) > epConfig->siConfig.rxRingUse) ||
        (((uint8_t)epConfig->siConfig.defaultRxBdrGroup >= epConfig->siConfig.rxBdrGroupNum) &&
         (epConfig->siConfig.defaultRxBdrGroup != kNETC_SiBDRGroupOne)) ||
        (epConfig->siConfig.ringPerBdrGroup == 0U))
    {
        /* Not recommended to make groups use more rings than the total number available, and Can't selected non
         * existing group */
        return kStatus_InvalidArgument;
    }

    NETC_SISetRxBDRGroup(handle->hw.si, (uint8_t)epConfig->siConfig.rxBdrGroupNum,
                         (uint8_t)epConfig->siConfig.ringPerBdrGroup);
    NETC_SISetDefaultRxBDRGroup(handle->hw.si, epConfig->siConfig.defaultRxBdrGroup);

    /* Configure station interface. */
    result = NETC_EnetcConfigureSI(handle->hw.base, si, &epConfig->siConfig);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Initialize the Tx/Rx buffer descriptor. */
    result = EP_DescriptorInit(handle, epConfig, bdrConfig);
    if (result != kStatus_Success)
    {
        return result;
    }
    NETC_SIEnableVlanToIpv(handle->hw.si, (bool)epConfig->siConfig.valnToIpvEnable);
    for (uint8_t i = 0U; i < 16U; i++)
    {
        if (epConfig->siConfig.vlanToIpvMap[i] > 7U)
        {
            /* The mapped IPV value range in 0 ~ 7 */
            return kStatus_InvalidArgument;
        }
        else
        {
            NETC_SIMapVlanToIpv(handle->hw.si, i, epConfig->siConfig.vlanToIpvMap[i]);
        }
    }
    for (uint8_t i = 0U; i < 8U; i++)
    {
        if ((epConfig->siConfig.ipvToRingMap[i] != 0U) &&
            (epConfig->siConfig.ipvToRingMap[i] >= epConfig->siConfig.ringPerBdrGroup))
        {
            /* The mapped BD ring should be located in one BD ring group */
            return kStatus_InvalidArgument;
        }
        else
        {
            NETC_SIMapIpvToRing(handle->hw.si, i, epConfig->siConfig.ipvToRingMap[i]);
        }
    }

    /* Enable station interface from both ENETC and SI sides. */
    NETC_EnetcEnableSI(handle->hw.base, si, true);
    NETC_SIEnable(handle->hw.si, true);

    return result;
}

/*!
 * @brief Set the MSIX entry table
 *
 * This function is to set entry table in specified MSIX Table memory. After entry table setup, set interrupts
 * vector/entry index.
 *
 * @param handle  The EP handle.
 * @param config  The EP configuration.
 * @return status_t
 */
static status_t EP_MSIXSetEntryTable(ep_handle_t *handle, const ep_config_t *config)
{
    uint32_t *msixTable  = (uint32_t *)(uintptr_t)handle->hw.msixTable;
    uint32_t *entryTable = (uint32_t *)(uintptr_t)config->msixEntry;
    uint8_t siNum        = getSiNum(handle->cfg.si);
    uint8_t msixNum;
    status_t result;

    result = NETC_EnetcSetMsixEntryNum(handle->hw.base, siNum, config->entryNum);
    if (result != kStatus_Success)
    {
        return result;
    }

    msixNum = (uint8_t)(
        ((handle->hw.si->SIPCAPR1 & ENETC_SI_SIPCAPR1_NUM_MSIX_MASK) >> ENETC_SI_SIPCAPR1_NUM_MSIX_SHIFT) + 1U);

    /* Entry > 0, enable MSIX. */
    if (config->entryNum != 0U)
    {
        if (config->entryNum > msixNum)
        {
            return kStatus_InvalidArgument;
        }

        if (MAX(MAX(config->siComEntryIdx, config->timerSyncEntryIdx), config->cmdBdEntryIdx) >= config->entryNum)
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

        /* Enable MSIX. */
        if (siNum == 0U)
        {
            handle->hw.func.pf->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK;
        }
        else
        {
            handle->hw.func.vf->PCI_CFC_MSIX_MSG_CTL = ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK;
        }

        /* Set the MSIX table entry index for various events */
        if (handle->capability.vsiNum > 0U)
        {
            handle->hw.si->SIMSIVR = (uint32_t)config->siComEntryIdx & ENETC_SI_SIMSIVR_VECTOR_MASK;
        }
        handle->hw.si->SITMRMSIVR = (uint32_t)config->timerSyncEntryIdx & ENETC_SI_SITMRMSIVR_VECTOR_MASK;
        handle->hw.si->SICMSIVR   = (uint32_t)config->cmdBdEntryIdx & ENETC_SI_SICMSIVR_VECTOR_MASK;
    }
    else
    {
        /* Disable MSIX. */
        if (siNum == 0U)
        {
            handle->hw.func.pf->PCI_CFC_MSIX_MSG_CTL = ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
        }
        else
        {
            handle->hw.func.vf->PCI_CFC_MSIX_MSG_CTL = ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
        }
    }

    return kStatus_Success;
}

/*!
 * @brief Get the idle Tx BD number in the ring
 * @note The last BD before producer index should be treated as an used BD according to hardware design.
 *
 * @param txBdRing  The EP handle.
 * @return The idle BD number.
 */
static uint16_t EP_GetIdleTxBDNum(netc_tx_bdr_t *txBdRing)
{
    if (txBdRing->producerIndex >= txBdRing->cleanIndex)
    {
        return (uint16_t)((txBdRing->len - txBdRing->producerIndex) + txBdRing->cleanIndex - 1U);
    }
    else
    {
        return (txBdRing->cleanIndex - txBdRing->producerIndex - 1U);
    }
}

status_t EP_GetDefaultConfig(ep_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(ep_config_t));

    config->port.common.acceptTpid.innerMask = (uint8_t)kNETC_OuterStanCvlan | (uint8_t)kNETC_OuterStanSvlan;
    config->port.common.acceptTpid.outerMask = (uint8_t)kNETC_InnerStanCvlan | (uint8_t)kNETC_InnerStanSvlan;
    config->port.common.pSpeed               = 0x63U;
    config->port.common.rxTsSelect           = kNETC_SyncTime;
#if (defined(FSL_FEATURE_NETC_HAS_PORT_FCSEA) && FSL_FEATURE_NETC_HAS_PORT_FCSEA)
    config->port.common.stompFcs = true;
#endif
    config->port.common.rxPpduBco              = 20U;
    config->port.common.txPpduBco              = 20U;
    config->port.common.timeGate.holdSkew      = 64;
    config->port.common.parser.l2PloadCount    = 24;
    config->port.common.parser.l3PayloadCount  = 24;
    config->port.common.parser.enableL3Parser  = true;
    config->port.common.parser.l4PayloadCount  = 24;
    config->port.common.parser.enableL4Parser  = true;
    config->port.ethMac.enableRevMii           = false;
    config->port.ethMac.preemptMode            = kNETC_PreemptDisable;
    config->port.ethMac.enMergeVerify          = false;
    config->port.ethMac.mergeVerifyTime        = 10U;
    config->port.ethMac.txTsSelect             = kNETC_SyncTime;
    config->port.ethMac.enTxPad                = true;
    config->port.ethMac.rxMinFrameSize         = 64U;
    config->port.ethMac.rxMaxFrameSize         = 0x600U;
    config->port.ethMac.maxBackPressOn         = 3036U;
    config->port.ethMac.minBackPressOff        = 20U;
    config->port.enPseudoMacTxPad              = true;
    config->psfpCfg.isiPortConfig.defaultISEID = 0xFFFFU;
    config->siConfig.ringPerBdrGroup           = 0x1U;
    for (uint8_t i = 0U; i < 8U; i++)
    {
        config->txTcCfg[i].enTcGate           = true;
        config->txTcCfg[i].sduCfg.maxSduSized = 0x600U;
        config->txTcCfg[i].sduCfg.sduType     = kNETC_MPDU;
        config->txPrioToTC[i]                 = i;
        config->siConfig.vsiTcToTC[i]         = i;
    }

    return kStatus_Success;
}

status_t EP_Init(ep_handle_t *handle, uint8_t *macAddr, const ep_config_t *config, const netc_bdr_config_t *bdrConfig)
{
    assert(handle != NULL);
    assert(config != NULL);

    uint8_t siNum = getSiNum(config->si);
    status_t result;
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051246) && FSL_FEATURE_NETC_HAS_ERRATA_051246)
    NETC_PORT_Type *swPseudoPort = (NETC_PORT_Type *)FSL_FEATURE_NETC_SWITCH_PSEUDO_PORT_BASE;
    uint32_t porTemp             = 0U;
#endif

    (void)memset(handle, 0, sizeof(ep_handle_t));

    /* Get the register map resource for ENETC */
    EP_GetBaseResource(handle, config->si);

    /* Store necessary configuration constant in the handle */
    EP_StoreConfig(handle, config);

    if (siNum != 0U)
    {
        /* Reset VF function */
        handle->hw.func.vf->PCI_CFC_PCIE_DEV_CTL |= ENETC_VF_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK;
        while ((handle->hw.func.pf->PCI_CFC_PCIE_DEV_CTL & ENETC_VF_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK) != 0U)
        {
        }
        /* Enable master bus and memory access for PCIe and MSI-X */
        handle->hw.func.vf->PCI_CFH_CMD |= ENETC_VF_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;

        NETC_EnetcGetCapability(handle->hw.base, &handle->capability);
        /* Transmit priority to traffic class mapping */
        handle->hw.base->NUM_SI[siNum].PSICFGR1 = NETC_ENETC_PSICFGR1_TC7_MAP(config->siConfig.vsiTcToTC[7]) |
                                                  NETC_ENETC_PSICFGR1_TC6_MAP(config->siConfig.vsiTcToTC[6]) |
                                                  NETC_ENETC_PSICFGR1_TC5_MAP(config->siConfig.vsiTcToTC[5]) |
                                                  NETC_ENETC_PSICFGR1_TC4_MAP(config->siConfig.vsiTcToTC[4]) |
                                                  NETC_ENETC_PSICFGR1_TC3_MAP(config->siConfig.vsiTcToTC[3]) |
                                                  NETC_ENETC_PSICFGR1_TC2_MAP(config->siConfig.vsiTcToTC[2]) |
                                                  NETC_ENETC_PSICFGR1_TC1_MAP(config->siConfig.vsiTcToTC[1]) |
                                                  NETC_ENETC_PSICFGR1_TC0_MAP(config->siConfig.vsiTcToTC[0]);
    }
    else
    {
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051260) && FSL_FEATURE_NETC_HAS_ERRATA_051260)
        /* Errata 051260: All NETC functions need to be enabled for ENETC NTMP operation */
        SWITCH_PCI_HDR_TYPE0->PCI_CFH_CMD |=
            ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;
        ENETC0_PCI_HDR_TYPE0->PCI_CFH_CMD |=
            ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;
        ENETC1_PCI_HDR_TYPE0->PCI_CFH_CMD |=
            ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK;
#endif
        /* Enable master bus and memory access for PCIe and MSI-X */
        handle->hw.func.pf->PCI_CFH_CMD |=
            (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);

        if (!NETC_PortIsPseudo(handle->hw.portGroup.port))
        {
            handle->hw.portGroup.port->POR |= (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
            /* Do software reset first */
            NETC_PortSoftwareResetEthMac(handle->hw.portGroup.eth);
        }
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051246) && FSL_FEATURE_NETC_HAS_ERRATA_051246)
        else
        {
            if (0U != (SWITCH_PCI_HDR_TYPE0->PCI_CFH_CMD & ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK))
            {
                porTemp = swPseudoPort->POR;
                /* Disable the internal switch port's Tx/Rx to prevent frames from flowing into the internal ENETC
                 * during its FLR and bring up */
                swPseudoPort->POR |= (NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
            }
        }
#endif
        /* Reset PF function */
        handle->hw.func.pf->PCI_CFC_PCIE_DEV_CTL |= ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK;
        while ((handle->hw.func.pf->PCI_CFC_PCIE_DEV_CTL & ENETC_PCI_TYPE0_PCI_CFC_PCIE_DEV_CTL_INIT_FLR_MASK) != 0U)
        {
        }

        /* Enable master bus and memory access for PCIe and MSI-X */
        handle->hw.func.pf->PCI_CFH_CMD |=
            (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);

        /* TODO: Here enable virtaul fucntion as default, may need flexible way. */
        /* Enable virtual function */
        handle->hw.func.pf->PCIE_CFC_SRIOV_CTL |=
            (ENETC_PCI_TYPE0_PCIE_CFC_SRIOV_CTL_VF_MSE_MASK | ENETC_PCI_TYPE0_PCIE_CFC_SRIOV_CTL_VF_ENABLE_MASK);

        NETC_EnetcGetCapability(handle->hw.base, &handle->capability);

        /* Only PSI needs to configure port */
        result = NETC_PortConfig(handle->hw.portGroup.port, &config->port.common);
        if (result != kStatus_Success)
        {
            return result;
        }

        if (!NETC_PortIsPseudo(handle->hw.portGroup.port))
        {
            result = NETC_PortConfigEthMac(handle->hw.portGroup.eth, &config->port.ethMac);
            if (result != kStatus_Success)
            {
                return result;
            }
        }
#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
        else
        {
            handle->hw.portGroup.pseudo->PPMCR = NETC_PSEUDO_LINK_PPMCR_TXPAD(config->port.enPseudoMacTxPad);
        }
#endif
        /* Configure Port VLAN classification control, only do PSI */
        handle->hw.base->PVCLCTR = NETC_ENETC_PVCLCTR_OAI(config->enOuterAsInner);
        /* Configure ENETC pasue on/off threshold, only do PSI */
        handle->hw.base->PPAUONTR  = NETC_ENETC_PPAUONTR_THRESH(config->pauseOnThr);
        handle->hw.base->PPAUOFFTR = NETC_ENETC_PPAUOFFTR_THRESH(config->pauseOffThr);
        /* Transmit priority to traffic class mapping, only do PSI */
        handle->hw.base->PRIO2TCMR0 = NETC_ENETC_PRIO2TCMR0_PRIO7TC(config->txPrioToTC[7]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO6TC(config->txPrioToTC[6]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO5TC(config->txPrioToTC[5]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO4TC(config->txPrioToTC[4]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO3TC(config->txPrioToTC[3]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO2TC(config->txPrioToTC[2]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO1TC(config->txPrioToTC[1]) |
                                      NETC_ENETC_PRIO2TCMR0_PRIO0TC(config->txPrioToTC[0]);
        /* Configure ENETC L3/L4 parser, only do on PSI */
        NETC_EnetcSetParser(handle->hw.base, &config->parserCfg);
        /* Configure ENETC PORT native VLAN, only do on PSI */
        NETC_EnetcPortSetNativeVLAN(handle->hw.base, &config->rxOuterVLANCfg, true);
        NETC_EnetcPortSetNativeVLAN(handle->hw.base, &config->rxInnerVLANCfg, false);

#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051524) && FSL_FEATURE_NETC_HAS_ERRATA_051524
        /* ERRATA051524: The Ingress Stream Identification key construction check of payload may evaluate incorrectly
           (indicating an invalid key construction) when the frame is received from a pseudo port (internal port) bound
           to ENETC or the switch, and maximum frame size is 1024 bytes or larger. */
        if ((config->port.ethMac.rxMaxFrameSize >= 1024U) && NETC_PortIsPseudo(handle->hw.portGroup.port))
        {
            /* Check the first payload is enough. */
            if (config->psfpCfg.kcRule[0].payload[0].pfp == 1U)
            {
                return kStatus_InvalidArgument;
            }
        }
#endif
        /* Configure ENETC PSFP, only do PSI */
        (void)EP_RxPSFPInit(handle, &config->psfpCfg);
        /* Configure ENETC traffic class, only do PSI */
        for (uint32_t i = 8U; i > 0U; i--)
        {
            result = EP_TxTrafficClassConfig(handle, (netc_hw_tc_idx_t)(uint32_t)(i - 1U), &config->txTcCfg[(i - 1U)]);
            if (result != kStatus_Success)
            {
                return result;
            }
        }
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051246) && FSL_FEATURE_NETC_HAS_ERRATA_051246)
        /* Clear Tx/Rx disable to allow traffic to flow */
        handle->hw.portGroup.port->POR &= ~(NETC_PORT_POR_TXDIS_MASK | NETC_PORT_POR_RXDIS_MASK);
#else
        if (NETC_PortIsPseudo(handle->hw.portGroup.port))
        {
            if (0U != (SWITCH_PCI_HDR_TYPE0->PCI_CFH_CMD & ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK))
            {
                swPseudoPort->POR = porTemp;
            }
        }
#endif
    }

    /* Set primary MAC address */
    result = EP_SetPrimaryMacAddr(handle, macAddr);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Set the MSIX table to handle interrupts */
    result = EP_MSIXSetEntryTable(handle, config);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Initialize station interface */
    result = EP_SISetup(handle, siNum, config, bdrConfig);
    if (result != kStatus_Success)
    {
        return result;
    }

    /* Initialize command BD ring for NTMP access */
    result = EP_CmdBDRInit(handle, &config->cmdBdrConfig);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (siNum == 0U)
    {
        /* Config TGS on PSI side */
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
        result = EP_TxPortTGSEnable(handle, config->port.enableTg, 0xFFU);
#else
        result = EP_TxPortTGSEnable(handle, config->port.enableTg);
#endif
    }
    return result;
}

status_t EP_Deinit(ep_handle_t *handle)
{
    uint8_t siNum = getSiNum(handle->cfg.si);

    (void)EP_CmdBDRDeinit(handle);
    NETC_EnetcEnableSI(handle->hw.base, siNum, false);
    NETC_SIEnable(handle->hw.si, false);
    if (!NETC_PortIsPseudo(handle->hw.portGroup.port))
    {
        NETC_PortEthMacGracefulStop(handle->hw.portGroup.port);
    }

    EP_RxBufferFreeAll(handle);

    return kStatus_Success;
}

status_t EP_Up(ep_handle_t *handle, netc_hw_mii_speed_t speed, netc_hw_mii_duplex_t duplex)
{
    status_t result = kStatus_Success;
    uint8_t siNum   = getSiNum(handle->cfg.si);
    netc_hw_mii_mode_t miiMode;

    if ((siNum == 0U) && (!NETC_PortIsPseudo(handle->hw.portGroup.port)))
    {
        miiMode = NETC_PortGetMIIMode(handle->hw.portGroup.eth);
        result  = NETC_PortSetMII(handle->hw.portGroup.eth, miiMode, speed, duplex);
        if (result != kStatus_Success)
        {
            return result;
        }
    }

    NETC_EnetcEnableSI(handle->hw.base, siNum, true);
    NETC_SIEnable(handle->hw.si, true);

    return result;
}

status_t EP_Down(ep_handle_t *handle)
{
    NETC_EnetcEnableSI(handle->hw.base, getSiNum(handle->cfg.si), false);
    NETC_SIEnable(handle->hw.si, false);

    return kStatus_Success;
}

status_t EP_SetPrimaryMacAddr(ep_handle_t *handle, uint8_t *macAddr)
{
    assert(macAddr != NULL);

    uint8_t siNum = getSiNum(handle->cfg.si);

    if (siNum == 0U)
    {
        NETC_PortSetMacAddr(handle->hw.portGroup.port, macAddr);
    }
    else
    {
        NETC_EnetcSetSIMacAddr(handle->hw.base, siNum, macAddr);
    }

    return kStatus_Success;
}

status_t EP_SendFrameCommon(ep_handle_t *handle,
                            netc_tx_bdr_t *txBdRing,
                            uint8_t hwRing,
                            netc_frame_struct_t *frame,
                            void *context,
                            netc_tx_bd_t *txDesc,
                            bool txCacheMaintain)
{
    assert((frame != NULL) && (frame->buffArray != NULL));

    status_t result              = kStatus_Success;
    netc_buffer_struct_t *txBuff = frame->buffArray;
    uint32_t totBdNum            = frame->length;
    uint16_t frameLen            = 0;
    bool isExtEnable             = (bool)txDesc[0].standard.isExtended;
    uint32_t address;
    netc_tx_bd_t *txDesTemp = NULL;

    /* Check the frame length. */
    if ((frame->buffArray[0].length < NETC_ENETC_TXFRAME_LEN_MIN) || (frame->length == 0U))
    {
        result = kStatus_NETC_TxFrameOverLen;
    }

    /* Calculate frame length and Tx data buffer number. */
    do
    {
        frameLen += txBuff->length;
        txBuff++;
    } while (--totBdNum != 0U);

    if (isExtEnable)
    {
        totBdNum = (uint32_t)frame->length + 1U;
    }
    else
    {
        totBdNum = frame->length;
    }

    /* Check the frame total length. */
    if ((frameLen > NETC_ENETC_TXFRAME_LEN_MAX) || (frameLen < NETC_ENETC_TXFRAME_LEN_MIN))
    {
        result = kStatus_NETC_TxFrameOverLen;
    }
    /* Check whether the available BD number is enough for Tx data buffer. */
    else if (totBdNum > EP_GetIdleTxBDNum(txBdRing))
    {
        result = kStatus_Busy;
    }
    else
    {
        txBuff = frame->buffArray;
        for (uint32_t bdIndex = 0; bdIndex < totBdNum; bdIndex++)
        {
            /* Check the buffer address */
            if (txBuff->buffer == NULL)
            {
                return kStatus_InvalidArgument;
            }

            if (txCacheMaintain)
            {
                /* Swith API share same cache */
                NETC_DcacheCleanByRange((uintptr_t)(uint8_t *)txBuff->buffer, txBuff->length);
            }
            /* Get latest Tx BD address and clean it content. */
            txDesTemp = &txBdRing->bdBase[txBdRing->producerIndex];
            (void)memset(txDesTemp, 0, sizeof(netc_tx_bd_t));
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            address =
                (uintptr_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)(uint8_t *)txBuff->buffer, kMEMORY_Local2DMA);
#else
            address = (uintptr_t)(uint32_t *)txBuff->buffer;
#endif
            if (bdIndex == 0U)
            {
                /* Update latest Tx dirty frame info. */
                txBdRing->dirtyBase[txBdRing->producerIndex].context = context;
                if (0U != (txDesc[0].standard.flags & NETC_SI_TXDESCRIP_RD_TSR_MASK))
                {
                    txBdRing->dirtyBase[txBdRing->producerIndex].isTxTsIdAvail = true;
                }
                else
                {
                    txBdRing->dirtyBase[txBdRing->producerIndex].isTxTsIdAvail = false;
                }

                if (isExtEnable && (0U != (txDesc[1].ext.eFlags & (uint32_t)kNETC_TxExtTwoStepTs)))
                {
                    txBdRing->dirtyBase[txBdRing->producerIndex].isTsAvail = true;
                }
                else
                {
                    txBdRing->dirtyBase[txBdRing->producerIndex].isTsAvail = false;
                }
                /* Copy user Tx descriptors to hardware Tx BD. */
                txDesTemp->standard.flags      = txDesc[0].standard.flags;
                txDesTemp->standard.addr       = address;
                txDesTemp->standard.bufLen     = txBuff->length;
                txDesTemp->standard.frameLen   = frameLen;
                txDesTemp->standard.isExtended = (uint32_t)isExtEnable;
                txDesTemp->standard.enableInterrupt =
                    (uint32_t)((handle->hw.si->BDR[hwRing].TBIER & ENETC_SI_TBIER_TXFIE_MASK) != 0U);
                if (isExtEnable)
                {
                    /* Increase producer index when first BD is extension BD. */
                    txBdRing->producerIndex = EP_IncreaseIndex(txBdRing->producerIndex, txBdRing->len);
                    txDesTemp               = &txBdRing->bdBase[txBdRing->producerIndex];
                    txDesTemp->ext          = txDesc[1].ext;
                    bdIndex++;
                }
            }
            else
            {
                txDesTemp->standard.addr   = address;
                txDesTemp->standard.bufLen = txBuff->length;
            }

            /* Increase tx buffer address index and producer index. */
            txBuff++;
            txBdRing->producerIndex = EP_IncreaseIndex(txBdRing->producerIndex, txBdRing->len);
        }

        /* Set final flag in last BD, same bit for stand or extension BD */
        if (txDesTemp != NULL)
        {
            txDesTemp->standard.isFinal = 1;
        }

        /* Make sure all data in the Tx BD is ready. */
        __DSB();

        /* Active Tx. */
        NETC_SISetTxProducer(handle->hw.si, hwRing, txBdRing->producerIndex);
    }

    return result;
}

status_t EP_SendFrame(ep_handle_t *handle, uint8_t ring, netc_frame_struct_t *frame, void *context, ep_tx_opt *opt)
{
    assert(handle != NULL);
    netc_tx_bd_t txDesc[2] = {0};
    uint8_t hwRing         = ring;

    if (ring >= handle->cfg.txRingUse)
    {
        /* Tx BD ring index is out of range */
        return kStatus_InvalidArgument;
    }
    if (NETC_EnetcHasManagement(handle->hw.base) && (getSiNum(handle->cfg.si) == 0U))
    {
        /* Switch management ENETC Tx BD hardware ring 0 can't be used to send regular frame, so the index need increase
         * 1 */
        hwRing = ring + 1U;
    }

    if (opt != NULL)
    {
        if ((opt->flags & (uint32_t)kEP_TX_OPT_START_TIME) != 0U)
        {
            txDesc[0].standard.flags = NETC_SI_TXDESCRIP_RD_FLQ(0x2U) | NETC_SI_TXDESCRIP_RD_TSE_MASK |
                                       NETC_SI_TXDESCRIP_RD_TXSTART(opt->timestamp);
        }
        if ((opt->flags & (uint32_t)kEP_TX_OPT_VLAN_INSERT) != 0U)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.pcp             = opt->vlan.pcp;
            txDesc[1].ext.dei             = opt->vlan.dei;
            txDesc[1].ext.vid             = opt->vlan.vid;
            txDesc[1].ext.tpid            = (uint16_t)opt->vlan.tpid;
            txDesc[1].ext.eFlags          = (uint8_t)kNETC_TxExtVlanInsert;
        }
        if ((opt->flags & (uint32_t)kEP_TX_OPT_REQ_TS) != 0U)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.eFlags |= (uint8_t)kNETC_TxExtTwoStepTs;
        }
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
        if ((opt->flags & (uint32_t)kEP_TX_OPT_REQ_ONE_STEP_TS) != 0U)
        {
            txDesc[0].standard.isExtended = 1U;
            txDesc[1].ext.eFlags |= (uint8_t)kNETC_TxExtOneStepTs;
        }
#endif
    }
    return EP_SendFrameCommon(handle, &handle->txBdRing[ring], hwRing, frame, context, &txDesc[0],
                              handle->cfg.txCacheMaintain);
}

netc_tx_frame_info_t *EP_ReclaimTxDescCommon(ep_handle_t *handle,
                                             netc_tx_bdr_t *txBdRing,
                                             uint8_t hwRing,
                                             bool enCallback)
{
    netc_tx_frame_info_t *frameInfo = NULL;
    netc_tx_bd_t *txDesc;
    uint16_t cleanNum;
    uint16_t consumer = NETC_SIGetTxConsumer(handle->hw.si, hwRing);

    /* Get the dirty Tx BD number ready for reclaiming in the ring */
    if (consumer >= txBdRing->cleanIndex)
    {
        cleanNum = (consumer - txBdRing->cleanIndex);
    }
    else
    {
        cleanNum = (uint16_t)(txBdRing->len - txBdRing->cleanIndex + consumer);
    }

    while (cleanNum-- != 0U)
    {
        /* When callback enable, get the reclaim information. */
        if (enCallback)
        {
            txDesc = &txBdRing->bdBase[txBdRing->cleanIndex];

            /* Valid Tx frame information is in the first BD of one BD chain. */
            if (txDesc->writeback.written != 0U)
            {
                /* When reclaim callback is enabled, never process more than one full frame */
                if (NULL != frameInfo)
                {
                    break;
                }

                frameInfo = &txBdRing->dirtyBase[txBdRing->cleanIndex];
                if (frameInfo->isTsAvail)
                {
                    frameInfo->timestamp = txDesc->writeback.timestamp;
                }
                if (frameInfo->isTxTsIdAvail)
                {
                    frameInfo->txtsid = (uint16_t)txDesc->writeback.txtsid;
                }
                frameInfo->status = (netc_ep_tx_status_t)txDesc->writeback.status;
            }
            else if (txDesc->standard.frameLen != 0U)
            {
                /* When reclaim callback is enabled, never process more than one full frame */
                if (NULL != frameInfo)
                {
                    break;
                }

                frameInfo         = &txBdRing->dirtyBase[txBdRing->cleanIndex];
                frameInfo->status = kNETC_EPTxSuccess;
            }
            else
            {
                /* Intentional empty */
            }
        }

        /* Update the clean index to free BD resource. */
        txBdRing->cleanIndex = EP_IncreaseIndex(txBdRing->cleanIndex, txBdRing->len);

        if (cleanNum == 0U)
        {
            consumer = NETC_SIGetTxConsumer(handle->hw.si, hwRing);
            /* Get the dirty Tx BD number again */
            if (consumer >= txBdRing->cleanIndex)
            {
                cleanNum = (consumer - txBdRing->cleanIndex);
            }
            else
            {
                cleanNum = (uint16_t)(txBdRing->len - txBdRing->cleanIndex + consumer);
            }
        }
    }
    return frameInfo;
}

void EP_ReclaimTxDescriptor(ep_handle_t *handle, uint8_t ring)
{
    assert(ring < handle->cfg.txRingUse);
    netc_tx_frame_info_t *frameInfo;
    uint8_t hwRing = ring;

    if (NETC_EnetcHasManagement(handle->hw.base) && (getSiNum(handle->cfg.si) == 0U))
    {
        /* Switch management ENETC Tx BD hardware ring 0 can't be used to send regular frame, so the index need increase
         * 1 */
        hwRing = ring + 1U;
    }

    do
    {
        frameInfo =
            EP_ReclaimTxDescCommon(handle, &handle->txBdRing[ring], hwRing, (handle->cfg.reclaimCallback != NULL));
        /* If reclaim callback is enabled, it must be called for each full frame. */
        if (frameInfo != NULL)
        {
            (void)handle->cfg.reclaimCallback(handle, ring, frameInfo, handle->cfg.userData);
            (void)memset(frameInfo, 0, sizeof(netc_tx_frame_info_t));
        }
    } while (frameInfo != NULL);
}

status_t EP_GetRxFrameSizeCommon(ep_handle_t *handle, netc_rx_bdr_t *rxBdRing, uint32_t *length)
{
    status_t result      = kStatus_NETC_RxHRZeroFrame;
    netc_rx_bd_t *rxDesc = &rxBdRing->bdBase[rxBdRing->index];
    uint16_t index       = rxBdRing->index;
    uint32_t totlen      = 0;

    /* Reset the length to zero. */
    *length = 0;

    /* Check the current buffer descriptor's ready flag. The flag in first BD indicates entire frame ready status. */
    if (rxDesc->writeback.isReady == 0U)
    {
        result = kStatus_NETC_RxFrameEmpty;
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
            if ((netc_host_reason_t)rxDesc->writeback.hr != kNETC_RegularFrame)
            {
                result = kStatus_NETC_RxHRNotZeroFrame;
            }
            else
            {
                result = kStatus_NETC_RxHRZeroFrame;
            }
            do
            {
                /* Check abnormal case. */
                if (rxDesc->writeback.bufLen == 0U)
                {
                    result = kStatus_NETC_RxFrameError;
                    break;
                }
                totlen += rxDesc->writeback.bufLen;

                /* Find the last buffer descriptor. */
                if (rxDesc->writeback.isFinal != 0U)
                {
                    *length = totlen;
                    break;
                }

                /* Extended BD needs additional offset. */
                if (rxBdRing->extendDesc)
                {
                    index = EP_IncreaseIndex(index, rxBdRing->len);
                }

                /* Increase to next buffer descriptor. */
                index  = EP_IncreaseIndex(index, rxBdRing->len);
                rxDesc = &rxBdRing->bdBase[index];
            } while (index != rxBdRing->index);
        }
        else
        {
            /* Get Transmit Timestamp Reference Response messages */
            result = kStatus_NETC_RxTsrResp;
        }
    }
    return result;
}

status_t EP_GetRxFrameSize(ep_handle_t *handle, uint8_t ring, uint32_t *length)
{
    assert((handle != NULL) && (length != NULL));
    status_t result;
    if (ring >= handle->cfg.rxRingUse)
    {
        /* Rx BD ring index is out of range */
        return kStatus_InvalidArgument;
    }
    else
    {
        result = EP_GetRxFrameSizeCommon(handle, &handle->rxBdRing[ring], length);
        if (kStatus_NETC_RxHRZeroFrame == result)
        {
            /* Only return success when currently frame is regular frame */
            result = kStatus_Success;
        }
        return result;
    }
}

static void EP_GetRxFrameAttribute(ep_handle_t *handle, netc_rx_bd_t *rxDesc, netc_frame_attr_t *attr)
{
    bool isPseudoPort = NETC_PortIsPseudo(handle->hw.portGroup.port);

    (void)memset(attr, 0, sizeof(netc_frame_attr_t));

    attr->parserSummary = rxDesc->writeback.parserSummary;
    attr->hostReason    = (netc_host_reason_t)rxDesc->writeback.hr;

    if (isPseudoPort)
    {
        attr->srcPort = (uint8_t)rxDesc->writeback.srcPort;
    }
    if ((rxDesc->writeback.flags & (uint8_t)kEP_RX_RSS_VALID) != 0U)
    {
        attr->isRssHashValid = true;
        attr->rssHash        = isPseudoPort ? rxDesc->writeback.rssHash : rxDesc->writeback.rssHashSwt;
    }
    if ((rxDesc->writeback.flags & (uint8_t)kEP_RX_VLAN_VALID) != 0U)
    {
        attr->isVlanExtracted = true;
        attr->vlan.vid        = rxDesc->writeback.vid;
        attr->vlan.dei        = rxDesc->writeback.dei;
        attr->vlan.pcp        = rxDesc->writeback.pcp;
        attr->vlan.tpid       = rxDesc->writeback.tpid;
    }
    if ((rxDesc->writeback.flags & (uint8_t)kEP_RX_TIMESTAMP_VALID) != 0U)
    {
        attr->isTsAvail = true;
    }
}

static void EP_DropFrame(ep_handle_t *handle, netc_rx_bdr_t *rxBdRing, uint8_t ring)
{
    netc_rx_bd_t *rxDesc;
    uint64_t rxDmaBuff;
    uint16_t index;
    bool isLastBd;

    /* Drop frame through updating BD status. */
    do
    {
        rxDesc    = &rxBdRing->bdBase[rxBdRing->index];
        index     = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
        rxDmaBuff = rxBdRing->buffArray[index];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        rxDmaBuff = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)rxDmaBuff, kMEMORY_Local2DMA);
#endif
        rxDesc->standard.addr = rxDmaBuff;

        /* Store last BD flag before it's cleared. */
        isLastBd = (rxDesc->writeback.isFinal != 0U) ? true : false;

        /* Update the receive buffer descriptors. */
        rxDesc->writeback.isFinal = 0;
        rxDesc->writeback.isReady = 0;

        if (rxBdRing->extendDesc)
        {
            /* Skip 16-bytes extended BD space. */
            rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
        }
        rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
    } while (!isLastBd);

    /* Update the Rx consumer index to free idle BD. */
    index = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
    NETC_SISetRxConsumer(handle->hw.si, ring, index);
}

status_t EP_ReceiveFrameCopyCommon(ep_handle_t *handle,
                                   netc_rx_bdr_t *rxBdRing,
                                   uint8_t ring,
                                   void *buffer,
                                   uint32_t length,
                                   netc_frame_attr_t *attr,
                                   bool rxCacheMaintain)
{
    uint32_t leftLen = length;
    bool isTsBd      = true;
    uintptr_t offset = 0;
    netc_rx_bd_t *rxDesc;
    uint64_t rxDmaBuff;
    uint16_t copyLen;
    uintptr_t data;
    uint16_t index;
    bool isLastBd;

    /* For data-NULL input, drop the frame. */
    if (buffer == NULL)
    {
        EP_DropFrame(handle, rxBdRing, ring);
    }
    else
    {
        rxDesc = &rxBdRing->bdBase[rxBdRing->index];

        /* Get the Rx frame information from first BD. */
        if (attr != NULL)
        {
            EP_GetRxFrameAttribute(handle, rxDesc, attr);
        }

        do
        {
            /* Copy scattered buffers to contiguous application memory. */
            if (leftLen != 0U)
            {
                /* Get the destination buffer address which NETC DMA copy frames to. */
                rxDmaBuff = rxBdRing->extendDesc ? rxBdRing->buffArray[rxBdRing->index / 2U] :
                                                   rxBdRing->buffArray[rxBdRing->index];
                if (rxCacheMaintain)
                {
                    /* Invalidate cache before copy. */
                    NETC_DcacheInvalidateByRange((uintptr_t)rxDmaBuff, rxBdRing->buffSize);
                }

                data    = (uintptr_t)(uint8_t *)buffer + offset;
                copyLen = (leftLen > rxDesc->writeback.bufLen) ? rxDesc->writeback.bufLen : (uint16_t)leftLen;
                (void)memcpy((void *)(uint8_t *)data, (void *)(uint8_t *)(uintptr_t)rxDmaBuff, copyLen);
                offset += copyLen;
                leftLen -= copyLen;
            }

            /* Set the Rx buffer address in BD which is overwritten by BD writeback. */
            index     = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
            rxDmaBuff = rxBdRing->buffArray[index];
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            rxDmaBuff = (uintptr_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)rxDmaBuff, kMEMORY_Local2DMA);
#endif
            rxDesc->standard.addr = rxDmaBuff;

            /* The last buffer descriptor flag of one frame. */
            isLastBd = (rxDesc->writeback.isFinal != 0U) ? true : false;

            /* Updates the receive buffer descriptors. */
            rxDesc->writeback.isFinal = 0;
            rxDesc->writeback.isReady = 0;

            if (rxBdRing->extendDesc)
            {
                /* Extended BD occupies one more 16 bytes space. */
                rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);

                /* Get the timestamp from extended BD if it's valid. */
                if ((attr != NULL) && isTsBd && attr->isTsAvail)
                {
                    /* Only first extended BD takes timestamp. */
                    rxDesc          = &rxBdRing->bdBase[rxBdRing->index];
                    attr->timestamp = rxDesc->ext.timestamp;
                    isTsBd          = false;
                }
            }

            /* Get the latest buffer descriptor. */
            rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
            rxDesc          = &rxBdRing->bdBase[rxBdRing->index];
        } while (!isLastBd);

        /* Update the Rx consumer index to free BD whose data is taken away. */
        index = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
        NETC_SISetRxConsumer(handle->hw.si, ring, index);
    }

    return kStatus_Success;
}

status_t EP_ReceiveFrameCopy(ep_handle_t *handle, uint8_t ring, void *buffer, uint32_t length, netc_frame_attr_t *attr)
{
    assert((handle != NULL) && (((buffer != NULL) && (length != 0U)) || (buffer == NULL)));
    if (ring >= handle->cfg.rxRingUse)
    {
        /* Rx BD ring index is out of range */
        return kStatus_InvalidArgument;
    }
    else
    {
        return EP_ReceiveFrameCopyCommon(handle, &handle->rxBdRing[ring], ring, buffer, length, attr,
                                         handle->cfg.rxCacheMaintain);
    }
}

status_t EP_ReceiveFrameCommon(ep_handle_t *handle,
                               netc_rx_bdr_t *rxBdRing,
                               uint8_t ring,
                               netc_frame_struct_t *frame,
                               netc_frame_attr_t *attr,
                               bool isDrop,
                               bool rxCacheMaintain)
{
    status_t result      = kStatus_Success;
    netc_rx_bd_t *rxDesc = &rxBdRing->bdBase[rxBdRing->index];
    bool isTsBd          = true;
    uint64_t rxDmaBuff;
    uint16_t buffIdx;
    uint16_t index;
    void *newBuff;
    bool isLastBd;

    if (isDrop)
    {
        /* Reset the buffer array length. */
        frame->length = 0;
        EP_DropFrame(handle, rxBdRing, ring);
        return result;
    }

    /* Get the Rx frame information from first BD */
    rxDesc = &rxBdRing->bdBase[rxBdRing->index];
    if (attr != NULL)
    {
        EP_GetRxFrameAttribute(handle, rxDesc, attr);
    }

    index = 0;
    do
    {
        buffIdx = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;

        /* Get the destination buffer address which NETC DMA copy frames to. */
        rxDmaBuff = rxBdRing->buffArray[buffIdx];

        if (rxCacheMaintain)
        {
            NETC_DcacheInvalidateByRange((uintptr_t)rxDmaBuff, rxBdRing->buffSize);
        }

        newBuff                        = frame->buffArray[index].buffer;
        frame->buffArray[index].buffer = (void *)(uint8_t *)(uintptr_t)rxDmaBuff;
        frame->buffArray[index].length = rxDesc->writeback.bufLen;
        index++;

        /* Update the buffer address array. */
        rxBdRing->buffArray[buffIdx] = (uint64_t)(uintptr_t)(uint8_t *)newBuff;

        rxDmaBuff = (uint64_t)(uintptr_t)(uint8_t *)newBuff;
#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        rxDmaBuff = (uint64_t)MEMORY_ConvertMemoryMapAddress((uintptr_t)rxDmaBuff, kMEMORY_Local2DMA);
#endif
        rxDesc->standard.addr = rxDmaBuff;

        /* The last buffer descriptor of one frame. */
        isLastBd = (rxDesc->writeback.isFinal != 0U) ? true : false;

        /* Updates the receive buffer descriptors. */
        rxDesc->writeback.isFinal = 0;
        rxDesc->writeback.isReady = 0;

        if (rxBdRing->extendDesc)
        {
            /* Extended BD occupies one more 16 bytes space. */
            rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);

            /* Get the timestamp from extended BD if it's valid. */
            if ((attr != NULL) && isTsBd && attr->isTsAvail)
            {
                /* Only first extended BD takes timestamp. */
                rxDesc          = &rxBdRing->bdBase[rxBdRing->index];
                attr->timestamp = rxDesc->ext.timestamp;
                isTsBd          = false;
            }
        }

        /* Get the latest buffer descriptor. */
        rxBdRing->index = EP_IncreaseIndex(rxBdRing->index, rxBdRing->len);
        rxDesc          = &rxBdRing->bdBase[rxBdRing->index];
    } while (!isLastBd);

    /* Get the Rx buffer array length. */
    frame->length = index;

    /* Update the Rx consumer index to free idle BD */
    index = rxBdRing->extendDesc ? (rxBdRing->index / 2U) : rxBdRing->index;
    NETC_SISetRxConsumer(handle->hw.si, ring, index);

    return result;
}

status_t EP_ReceiveFrame(ep_handle_t *handle, uint8_t ring, netc_frame_struct_t *frame, netc_frame_attr_t *attr)
{
    assert(handle != NULL);
    assert(handle->cfg.rxZeroCopy);
    assert(frame != NULL);

    status_t result         = kStatus_Success;
    netc_rx_bdr_t *rxBdRing = NULL;
    netc_rx_bd_t *rxDesc    = NULL;
    uint32_t buffNum        = 0U;
    uint16_t index;
    void *newBuff;

    if (ring >= handle->cfg.rxRingUse)
    {
        /* Rx BD ring index is out of range */
        return kStatus_InvalidArgument;
    }
    rxBdRing = &handle->rxBdRing[ring];
    rxDesc   = &rxBdRing->bdBase[rxBdRing->index];

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
            if ((netc_host_reason_t)rxDesc->writeback.hr != kNETC_RegularFrame)
            {
                /* Return without receive when currently frame is not regular frame */
                return kStatus_NETC_RxHRNotZeroFrame;
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
                newBuff = handle->cfg.rxBuffAlloc(handle, ring, rxBdRing->buffSize, handle->cfg.userData);
                if (newBuff == NULL)
                {
                    while (index-- > 0U)
                    {
                        handle->cfg.rxBuffFree(handle, ring, frame->buffArray[index].buffer, handle->cfg.userData);
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
            /* Get Transmit Timestamp Reference Response messages */
            return kStatus_NETC_RxTsrResp;
        }
    }
    result = EP_ReceiveFrameCommon(handle, rxBdRing, ring, frame, attr, (result != kStatus_Success),
                                   handle->cfg.rxCacheMaintain);
    return result;
}

status_t EP_CmdBDRInit(ep_handle_t *handle, const netc_cmd_bdr_config_t *config)
{
    assert(handle != NULL);

    status_t result;

    result = NETC_CmdBDRInit((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, config);
    if (result != kStatus_Success)
    {
        return result;
    }

    handle->cmdBdRing.bdBase        = config->bdBase;
    handle->cmdBdRing.bdLength      = config->bdLength;
    handle->cmdBdRing.producerIndex = 0U;
    handle->cmdBdRing.cleanIndex    = 0U;
    handle->cmdBdRing.bdrEnable     = true;

    return result;
}

status_t EP_CmdBDRDeinit(ep_handle_t *handle)
{
    assert(handle != NULL);
    return NETC_CmdBDRDeinit((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR);
}

status_t EP_RxIPFInit(ep_handle_t *handle, netc_ep_ipf_config_t *config)
{
    NETC_IPFInit(handle->hw.common, &config->dosCfg);
    NETC_PortSetIPF(handle->hw.portGroup.port, &config->portConfig);

    return kStatus_Success;
}

status_t EP_RxIPFAddTableEntry(ep_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddIPFTableEntry(&cdbrHandle, config, entryID);
}

status_t EP_RxIPFUpdateTableEntry(ep_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_UpdateIPFTableEntry(&cdbrHandle, entryID, cfg);
}

status_t EP_RxIPFDelTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelIPFTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxIPFResetMatchCounter(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_ResetIPFMatchCounter(&cdbrHandle, entryID);
}

status_t EP_RxIPFGetMatchedCount(ep_handle_t *handle, uint32_t entryID, uint64_t *count)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetIPFMatchedCount(&cdbrHandle, entryID, count);
}

status_t EP_RxPSFPAddSGITableEntry(ep_handle_t *handle, netc_tb_sgi_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateSGITableEntry(&cdbrHandle, config, true);
}

status_t EP_RxPSFPUpdateSGITableEntry(ep_handle_t *handle, netc_tb_sgi_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateSGITableEntry(&cdbrHandle, config, false);
}

status_t EP_RxPSFPDelSGITableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelSGITableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPGetSGIState(ep_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *state)
{
    assert((handle != NULL) && (state != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetSGIState(&cdbrHandle, entryID, state);
}

status_t EP_RxPSFPAddSGCLTableEntry(ep_handle_t *handle, netc_tb_sgcl_gcl_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddSGCLTableEntry(&cdbrHandle, config);
}

status_t EP_RxPSFPDelSGCLTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelSGCLTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPGetSGCLGateList(ep_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length)
{
    assert((handle != NULL) && (gcl != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetSGCLGateList(&cdbrHandle, gcl, length);
}

status_t EP_RxPSFPGetSGCLState(ep_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state)
{
    assert((handle != NULL) && (state != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetSGCLState(&cdbrHandle, entryID, state);
}

status_t EP_RxPSFPAddRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_AddEntry);
}

status_t EP_RxPSFPUpdateRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_UpdateEntry);
}

status_t EP_RxPSFPAddOrUpdateRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateRPTableEntry(&cdbrHandle, config, kNETC_AddOrUpdateEntry);
}

status_t EP_RxPSFPDelRPTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelRPTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPGetRPStatistic(ep_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetRPStatistic(&cdbrHandle, entryID, statis);
}

status_t EP_MsixSetGlobalMask(ep_handle_t *handle, bool mask)
{
    if (getSiNum(handle->cfg.si) == 0U)
    {
        if (mask)
        {
            handle->hw.func.pf->PCI_CFC_MSIX_MSG_CTL |= (uint16_t)ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
        }
        else
        {
            handle->hw.func.pf->PCI_CFC_MSIX_MSG_CTL &=
                (uint16_t)(~ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK);
        }
    }
    else
    {
        if (mask)
        {
            handle->hw.func.vf->PCI_CFC_MSIX_MSG_CTL |=
                (uint16_t)ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK;
        }
        else
        {
            handle->hw.func.vf->PCI_CFC_MSIX_MSG_CTL &=
                (uint16_t)(~ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_FUNC_MASK_MASK);
        }
    }

    return kStatus_Success;
}

status_t EP_MsixSetEntryMask(ep_handle_t *handle, uint8_t entryIdx, bool mask)
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

status_t EP_MsixGetPendingStatus(ep_handle_t *handle, uint8_t pbaIdx, uint64_t *status)
{
    status_t result = kStatus_Success;
    bool funcEnable;

    if (handle->cfg.entryNum == 0U)
    {
        return kStatus_Fail;
    }

    /* Check MSIX enable status. */
    if (getSiNum(handle->cfg.si) == 0U)
    {
        funcEnable =
            ((handle->hw.func.pf->PCI_CFC_MSIX_MSG_CTL & ENETC_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK) != 0U);
    }
    else
    {
        funcEnable =
            ((handle->hw.func.vf->PCI_CFC_MSIX_MSG_CTL & ENETC_VF_PCI_TYPE0_PCI_CFC_MSIX_MSG_CTL_MSIX_EN_MASK) != 0U);
    }

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

status_t EP_RxL2MFInit(ep_handle_t *handle, netc_si_l2mf_config_t *config)
{
    uint8_t siNum = getSiNum(handle->cfg.si);

    NETC_EnetcEnablePromiscuous(handle->hw.base, siNum, config->macUCPromis, config->macMCPromis);
    NETC_SIEnablePromisc(handle->hw.si, kNETC_PacketUnicast, config->rejectUC);
    NETC_SIEnablePromisc(handle->hw.si, kNETC_PacketMulticast, config->rejectMC);
    NETC_SIEnablePromisc(handle->hw.si, kNETC_PacketBroadcast, config->rejectBC);

    return kStatus_Success;
}

status_t EP_RxL2MFAddHashEntry(ep_handle_t *handle, netc_packet_type_t type, uint8_t *macAddr)
{
    assert(type != kNETC_PacketBroadcast);

    uint8_t siNum     = getSiNum(handle->cfg.si);
    uint8_t hashIndex = 0;
    uint64_t mac      = 0;
    int i             = 0;

    /* Calculate the hash index. */
    for (i = 5; i >= 0; i--)
    {
        mac = (mac << 8U) | macAddr[i];
    }
    for (i = 0; i < 8; i++)
    {
        hashIndex ^= (uint8_t)(mac & 0x3FU);
        mac = mac >> 6U;
    }

    NETC_EnetcAddMacAddrHash(handle->hw.base, siNum, type, hashIndex);

    /* Added the used count of hash index. */
    if (type == kNETC_PacketUnicast)
    {
        handle->unicastHashCount[hashIndex]++;
    }
    else
    {
        handle->multicastHashCount[hashIndex]++;
    }

    return kStatus_Success;
}

status_t EP_RxL2MFDelHashEntry(ep_handle_t *handle, netc_packet_type_t type, uint8_t *macAddr)
{
    assert(type != kNETC_PacketBroadcast);

    uint8_t siNum     = getSiNum(handle->cfg.si);
    uint8_t hashIndex = 0;
    uint64_t mac      = 0;
    int i             = 0;

    /* Calculate the hash index. */
    for (i = 5; i >= 0; i--)
    {
        mac = (mac << 8U) | macAddr[i];
    }
    for (i = 0; i < 8; i++)
    {
        hashIndex ^= (uint8_t)(mac & 0x3FU);
        mac = mac >> 6U;
    }

    if (type == kNETC_PacketUnicast)
    {
        if (handle->unicastHashCount[hashIndex] == 0U)
        {
            return kStatus_Fail;
        }
        else
        {
            /* Delete the hash index when there's no address using this index. */
            if (--handle->unicastHashCount[hashIndex] == 0U)
            {
                NETC_EnetcDelMacAddrHash(handle->hw.base, siNum, type, hashIndex);
            }
        }
    }
    else
    {
        if (handle->multicastHashCount[hashIndex] == 0U)
        {
            return kStatus_Fail;
        }
        else
        {
            /* Delete the hash index when there's no other MAC address using this hash index. */
            if (--handle->multicastHashCount[hashIndex] == 0U)
            {
                NETC_EnetcDelMacAddrHash(handle->hw.base, siNum, type, hashIndex);
            }
        }
    }

    return kStatus_Success;
}

status_t EP_RxL2MFAddEMTableEntry(ep_handle_t *handle, uint32_t idx, uint8_t *macAddr)
{
    assert((handle != NULL) && ((macAddr != NULL)));
    uint64_t address =
        ((uint64_t)macAddr[4] << 32U) + ((uint64_t)macAddr[5] << 40U) + *(uint32_t *)(uintptr_t)&macAddr[0];
    netc_cmd_bd_t cmdBd = {0};

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return kStatus_InvalidArgument;
    }
    cmdBd.generic.addr     = address;
    cmdBd.generic.en       = 1;
    cmdBd.generic.siBitMap = (uint32_t)1U << getSiNum(handle->cfg.si);
    cmdBd.generic.index    = idx;
    cmdBd.generic.cmd      = 0;
    cmdBd.generic.class    = 1;
    cmdBd.generic.ci       = 0;
    cmdBd.generic.sf       = 1;
    return NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                 kNETC_NtmpV1_0);
}

status_t EP_RxL2MFDelEMTableEntry(ep_handle_t *handle, uint32_t idx)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return kStatus_InvalidArgument;
    }
    cmdBd.generic.addr     = 0;
    cmdBd.generic.en       = 1;
    cmdBd.generic.siBitMap = 0;
    cmdBd.generic.index    = idx;
    cmdBd.generic.cmd      = 0;
    cmdBd.generic.class    = 1;
    cmdBd.generic.ci       = 0;
    cmdBd.generic.sf       = 1;
    return NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                 kNETC_NtmpV1_0);
}

status_t EP_RxL2VFInit(ep_handle_t *handle, netc_si_l2vf_config_t *config)
{
    NETC_EnetcConfigureVlanFilter(handle->hw.base, getSiNum(handle->cfg.si), config);
    return kStatus_Success;
}

status_t EP_RxL2VFAddHashEntry(ep_handle_t *handle, uint16_t vlanId)
{
    assert(handle != NULL);
    assert(vlanId <= 0xFFFU);

    uint8_t siNum     = getSiNum(handle->cfg.si);
    uint8_t hash0     = (uint8_t)((vlanId >> 6U) & 0x3FU);
    uint8_t hash1     = (uint8_t)(vlanId & 0x3FU);
    uint8_t hashIndex = hash0 ^ hash1;

    NETC_EnetcAddVlanHash(handle->hw.base, siNum, hashIndex);

    /* Added the used count of hash index. */
    handle->vlanHashCount[hashIndex]++;

    return kStatus_Success;
}

status_t EP_RxL2VFDelHashEntry(ep_handle_t *handle, uint16_t vlanId)
{
    assert(handle != NULL);
    assert(vlanId <= 0xFFFU);

    uint8_t siNum     = getSiNum(handle->cfg.si);
    uint8_t hash0     = (uint8_t)((vlanId >> 6U) & 0x3FU);
    uint8_t hash1     = (uint8_t)(vlanId & 0x3FU);
    uint8_t hashIndex = hash0 ^ hash1;

    if (handle->vlanHashCount[hashIndex] == 0U)
    {
        return kStatus_Fail;
    }
    else
    {
        /* Delete the hash index when there's no other VLAN ID using this hash index. */
        if (--handle->vlanHashCount[hashIndex] == 0U)
        {
            NETC_EnetcDelVlanHash(handle->hw.base, siNum, hashIndex);
        }
    }

    return kStatus_Success;
}

status_t EP_RxL2VFAddEMTableEntry(ep_handle_t *handle, uint32_t idx, uint16_t vlanId, netc_vlan_tpid_select_t tpid)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return kStatus_InvalidArgument;
    }
    cmdBd.generic.addr     = (uint64_t)vlanId | ((uint64_t)tpid << 16U);
    cmdBd.generic.en       = 1;
    cmdBd.generic.siBitMap = (uint32_t)1U << getSiNum(handle->cfg.si);
    cmdBd.generic.index    = idx;
    cmdBd.generic.cmd      = 0;
    cmdBd.generic.class    = 2;
    cmdBd.generic.ci       = 0;
    cmdBd.generic.sf       = 1;
    return NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                 kNETC_NtmpV1_0);
}

status_t EP_RxL2VFDelEMTableEntry(ep_handle_t *handle, uint32_t idx)
{
    assert(handle != NULL);
    netc_cmd_bd_t cmdBd = {0};

    /* Only PSI can access MAC filter table */
    if (getSiNum(handle->cfg.si) != 0U)
    {
        return kStatus_InvalidArgument;
    }
    cmdBd.generic.addr     = 0;
    cmdBd.generic.en       = 1;
    cmdBd.generic.siBitMap = 0;
    cmdBd.generic.index    = idx;
    cmdBd.generic.cmd      = 0;
    cmdBd.generic.class    = 2;
    cmdBd.generic.ci       = 0;
    cmdBd.generic.sf       = 1;
    return NETC_CmdBDSendCommand((netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR, &handle->cmdBdRing, &cmdBd,
                                 kNETC_NtmpV1_0);
}

#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
status_t EP_TxPortTGSEnable(ep_handle_t *handle, bool enable, uint8_t gateState)
#else
status_t EP_TxPortTGSEnable(ep_handle_t *handle, bool enable)
#endif
{
    assert(handle != NULL);
    status_t result = kStatus_Success;

    if (enable)
    {
        handle->hw.portGroup.port->PTGSCR |= NETC_PORT_PTGSCR_TGE_MASK;
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
        netc_tgs_gate_entry_t gate[2] = {{.interval = 50000U, .tcGateState = gateState},
                                         {.interval = 50000U, .tcGateState = gateState}};
        netc_tb_tgs_gcl_t wTgsList    = {.cycleTime = 1000000U, .numEntries = 2U, .gcList = &gate[0]};
        uint64_t time;
        /* Enable master bus and memory access for default ns timer*/
        TMR_PCI_HDR_TYPE0->PCI_CFH_CMD |=
            (ENETC_PCI_TYPE0_PCI_CFH_CMD_MEM_ACCESS_MASK | ENETC_PCI_TYPE0_PCI_CFH_CMD_BUS_MASTER_EN_MASK);

        NETC_TimerGetTime(TMR0_BASE, &time);

        wTgsList.baseTime = time;
        result            = EP_TxTGSConfigAdminGcl(handle, &wTgsList);
#endif
    }
    else
    {
        handle->hw.portGroup.port->PTGSCR &= ~NETC_PORT_PTGSCR_TGE_MASK;
    }

    return result;
}

status_t EP_TxTGSConfigAdminGcl(ep_handle_t *handle, netc_tb_tgs_gcl_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;
    status_t status = kStatus_Success;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;

    if (0U != (handle->hw.portGroup.port->PTGAGLSR & NETC_PORT_PTGAGLSR_CFG_PEND_MASK))
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
    if (0U != (handle->hw.portGroup.port->PTGAGLSR & NETC_PORT_PTGAGLSR_TG_MASK))
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
    return NETC_ConfigTGSAdminList(&cdbrHandle, config);
}

status_t EP_TxtTGSGetOperGcl(ep_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length)
{
    assert((handle != NULL) && (gcl != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetTGSOperationList(&cdbrHandle, gcl, length);
}

status_t EP_TxTrafficClassConfig(ep_handle_t *handle, netc_hw_tc_idx_t tcIdx, const netc_port_tx_tc_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    status_t reseult;
    uint32_t temp;

    if (!NETC_PortIsPseudo(handle->hw.portGroup.port))
    {
        temp                             = handle->hw.portGroup.port->PFPCR & (~((uint32_t)1U << (uint32_t)tcIdx));
        handle->hw.portGroup.port->PFPCR = temp | ((uint32_t)config->enPreemption << (uint32_t)tcIdx);
    }
    temp                             = handle->hw.portGroup.port->PDGSR & (~((uint32_t)1U << (uint32_t)tcIdx));
    handle->hw.portGroup.port->PDGSR = temp | ((uint32_t)config->enTcGate << (uint32_t)tcIdx);

    (void)NETC_EnetcPortEnableTSD(handle->hw.base, tcIdx, config->enableTsd);

    reseult = NETC_PortConfigTcMaxSDU(handle->hw.portGroup.port, tcIdx, &config->sduCfg);
    if ((kStatus_Success == reseult) && (config->enableCbs))
    {
        reseult = NETC_PortConfigTcCBS(handle->hw.portGroup.port, tcIdx, &config->cbsCfg);
    }
    return reseult;
}

status_t EP_RxPSFPAddISITableEntry(ep_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL) && (entryID != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddISITableEntry(&cdbrHandle, config, entryID);
}

status_t EP_RxPSFPDelISITableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelISITableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPAddISTableEntry(ep_handle_t *handle, netc_tb_is_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateISTableEntry(&cdbrHandle, config, true);
}

status_t EP_RxPSFPUpdateISTableEntry(ep_handle_t *handle, netc_tb_is_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddOrUpdateISTableEntry(&cdbrHandle, config, false);
}

status_t EP_RxPSFPDelISTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelISTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPAddISFTableEntry(ep_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID)
{
    assert((handle != NULL) && (config != NULL) && (entryID != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddISFTableEntry(&cdbrHandle, config, entryID);
}

status_t EP_RxPSFPUpdateISFTableEntry(ep_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg)
{
    assert((handle != NULL) && (cfg != NULL));
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_UpdateISFTableEntry(&cdbrHandle, entryID, cfg);
}

status_t EP_RxPSFPDelISFTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_DelISFTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPAddISCTableEntry(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_AddISCTableEntry(&cdbrHandle, entryID);
}

status_t EP_RxPSFPGetISCStatistic(ep_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_GetISCStatistic(&cdbrHandle, entryID, statistic);
}

status_t EP_RxPSFPResetISCStatistic(ep_handle_t *handle, uint32_t entryID)
{
    assert(handle != NULL);
    netc_cbdr_handle_t cdbrHandle;

    cdbrHandle.base   = (netc_cbdr_hw_t *)(uintptr_t)&handle->hw.si->SICBDRMR;
    cdbrHandle.cmdr   = &handle->cmdBdRing;
    cdbrHandle.buffer = &s_cmdData;
    return NETC_ResetISCStatistic(&cdbrHandle, entryID);
}

void EP_PsiEnableInterrupt(ep_handle_t *handle, uint32_t mask, bool enable)
{
    /* Check whether VSI number is over the capability. */
    assert(((uint16_t)mask >> handle->capability.vsiNum) <= 1U);
    assert(((uint16_t)(mask >> 16U) >> handle->capability.vsiNum) <= 1U);
    assert(getSiNum(handle->cfg.si) == 0U);
    NETC_SIPsiEnableInterrupt(handle->hw.si, mask, enable);
}

uint32_t EP_PsiGetStatus(ep_handle_t *handle)
{
    assert(handle->capability.vsiNum > 0U);
    assert(getSiNum(handle->cfg.si) == 0U);
    return NETC_SIPsiGetStatus(handle->hw.si);
}

void EP_PsiClearStatus(ep_handle_t *handle, uint32_t mask)
{
    /* Check whether VSI number is over the capability. */
    assert(((uint16_t)mask >> handle->capability.vsiNum) <= 1U);
    assert(((uint16_t)(mask >> 16U) >> handle->capability.vsiNum) <= 1U);
    assert(handle->capability.vsiNum > 0U);
    assert(getSiNum(handle->cfg.si) == 0U);
    NETC_SIPsiClearStatus(handle->hw.si, mask);
}

status_t EP_PsiSendMsg(ep_handle_t *handle, uint16_t msg, netc_vsi_number_t vsi)
{
    assert(handle->capability.vsiNum > NETC_SIGetVsiIndex(vsi));
    assert(getSiNum(handle->cfg.si) == 0U);
    return NETC_SIPsiSendMsg(handle->hw.si, msg, vsi);
}

bool EP_PsiCheckTxBusy(ep_handle_t *handle, netc_vsi_number_t vsi)
{
    assert(handle->capability.vsiNum > NETC_SIGetVsiIndex(vsi));
    assert(getSiNum(handle->cfg.si) == 0U);
    return NETC_SIPsiCheckTxBusy(handle->hw.si, vsi);
}

status_t EP_PsiSetRxBuffer(ep_handle_t *handle, netc_vsi_number_t vsi, uint64_t buffAddr)
{
    assert(handle->capability.vsiNum > NETC_SIGetVsiIndex(vsi));
    assert(getSiNum(handle->cfg.si) == 0U);
    return NETC_SIPsiSetRxBuffer(handle->hw.si, vsi, buffAddr);
}

status_t EP_PsiGetRxMsg(ep_handle_t *handle, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo)
{
    assert(handle->capability.vsiNum > NETC_SIGetVsiIndex(vsi));
    assert(getSiNum(handle->cfg.si) == 0U);
    return NETC_SIPsiGetRxMsg(handle->hw.si, vsi, msgInfo);
}

void EP_VsiEnableInterrupt(ep_handle_t *handle, uint32_t mask, bool enable)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    NETC_SIVsiEnableInterrupt(handle->hw.si, mask, enable);
}

uint32_t EP_VsiGetStatus(ep_handle_t *handle)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    return NETC_SIVsiGetStatus(handle->hw.si);
}

void EP_VsiClearStatus(ep_handle_t *handle, uint32_t mask)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    NETC_SIVsiClearStatus(handle->hw.si, mask);
}

status_t EP_VsiSendMsg(ep_handle_t *handle, uint64_t msgAddr, uint32_t msgLen)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    return NETC_SIVsiSendMsg(handle->hw.si, msgAddr, msgLen);
}

void EP_VsiCheckTxStatus(ep_handle_t *handle, netc_vsi_msg_tx_status_t *status)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    NETC_SIVsiCheckTxStatus(handle->hw.si, status);
}

status_t EP_VsiReceiveMsg(ep_handle_t *handle, uint16_t *msg)
{
    assert(getSiNum(handle->cfg.si) <= (uint8_t)handle->capability.vsiNum);
    assert(getSiNum(handle->cfg.si) != 0U);
    return NETC_SIVsiReceiveMsg(handle->hw.si, msg);
}
