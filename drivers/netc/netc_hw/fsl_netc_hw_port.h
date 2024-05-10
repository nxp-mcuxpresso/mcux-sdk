/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_PORT_H_
#define FSL_NETC_PORT_H_

#include "fsl_netc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port
#endif
/*! @addtogroup netc_hw_port
 * @{
 */

/*! @brief The port supported minimum/maximum frame size. */
#define NETC_PORT_MIN_FRAME_SIZE (18U)
#define NETC_PORT_MAX_FRAME_SIZE (2000U)

typedef enum _netc_port_intr_flags
{
    kNETC_TxEmptyFlag             = NETC_ETH_LINK_PM0_IEVENT_TX_EMPTY_MASK, /*!< Tx FIFO empty flag. */
    kNETC_RxEmptyFlag             = NETC_ETH_LINK_PM0_IEVENT_RX_EMPTY_MASK, /*!< Rx FIFO empty flag. */
    kNETC_TxOverflowFlag          = NETC_ETH_LINK_PM0_IEVENT_TX_OVFL_MASK, /*!< Tx overflow flag. */
    kNETC_TxUnderflowFlag         = NETC_ETH_LINK_PM0_IEVENT_TX_UNFL_MASK, /*!< Tx underflow flag. */
    kNETC_RxOverflowFlag          = NETC_ETH_LINK_PM0_IEVENT_RX_OVFL_MASK, /*!< Rx overflow flag. */
    kNETC_MagicPacketFlag         = NETC_ETH_LINK_PM0_IEVENT_MGI_MASK, /*!< Magic packet detection indication flag. */
    kNETC_TxClkStopFlag           = NETC_ETH_LINK_PM0_IEVENT_TX_CSD_MASK, /*!< Tx clock stop detection flag. */
    kNETC_RxClkStopFlag           = NETC_ETH_LINK_PM0_IEVENT_RX_CSD_MASK, /*!< Rx clock stop detection flag. */
    kNETC_SpeedDuplexChangeFlag   = NETC_ETH_LINK_PM0_IEVENT_SPD_DUP_MASK, /*!< Speed/Duplex Change flag */
    kNETC_MacMergeSMDErrFlag      = NETC_ETH_LINK_PM0_IEVENT_MRG_SERR_MASK, /*!< MAC merge frame SMD error received event flag */
    kNETC_MacMergeAssemblyErrFlag = NETC_ETH_LINK_PM0_IEVENT_MRG_AERR_MASK, /*!< MAC merge frame assembly error event flag */
} netc_port_intr_flags_t;

/*! @brief Defines the port MAC frame loopback mode. */
typedef enum _netc_port_loopback_mode_t
{
    kNETC_PortLpbWithExtTxClk, /*!< Port MAC frame loopback with external Tx clock. */
    kNETC_PortLpbWithIntTxClk = 2U, /*!< Port MAC frame loopback with internal Tx clock. */
} netc_port_loopback_mode_t;

/*! @} */ // end of netc_hw_port
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_tx
#endif
/*! @addtogroup netc_hw_port_tx
 * @{
 */

/*! @} */ // end of netc_hw_port_tx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_tx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_rx
#endif
/*! @addtogroup netc_hw_port_rx
 * @{
 */

/*! @} */ // end of netc_hw_port_rx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_rx
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port
#endif
/*! @addtogroup netc_hw_port
 * @{
 */
/*!
 * @brief Configure specified PORT
 *
 * @param base   NETC port module base address.
 * @param config Port configuration structure.
 * @return status_t
 */
status_t NETC_PortConfig(NETC_PORT_Type *base, const netc_port_common_t *config);

/*!
 * @brief Set the MAC address.
 *
 * @param handle
 * @param macAddr
 */
void NETC_PortSetMacAddr(NETC_PORT_Type *base, const uint8_t *macAddr);

/*!
 * @brief Check whether this port a pseudo MAC port.
 *
 * @param base PORT peripheral base address.
 */
bool NETC_PortIsPseudo(NETC_PORT_Type *base);

/*!
 * @brief Get specified PORT discard counter
 *
 * @param base   NETC port module base address.
 * @param discardType Port discard type.
 * @param statistic pointer to the statistic data
 */
void NETC_PortGetDiscardStatistic(NETC_PORT_Type *base,
                                  netc_port_discard_tpye_t discardType,
                                  netc_port_discard_statistic_t *statistic);

/*!
 * @brief Clean the Port Rx discard reason. Set the related bits to 1 to clear the specific reasons
 *
 * @param base   NETC port module base address.
 * @param discardType Port discard type.
 * @param reason0
 * @param reason1
 */
void NETC_PortClearDiscardReason(NETC_PORT_Type *base,
                                 netc_port_discard_tpye_t discardType,
                                 uint32_t reason0,
                                 uint32_t reason1);

/*!
 * @brief Get port time gate scheduling gate list status
 *
 * @param base   NETC port module base address.
 * @return Port status flags which are ORed by the enumerators in the @ref netc_port_tgsl_status_t
 */
static inline uint32_t NETC_PortGetTGSListStatus(NETC_PORT_Type *base)
{
    return base->PTGAGLSR;
}

/*!
 * @brief Do graceful stop for Port Ethernet MAC receive/transmit
 *
 * @param base   NETC port module base address.
 */
void NETC_PortEthMacGracefulStop(NETC_PORT_Type *base);

/*!
 * @brief Set port speed
 *
 * @param base  NETC port module base address.
 * @param pSpeed  Transmit Port Speed = 10Mbps * (pSpeed+1), Used by ETS, Qbu and to determine
 * if cut-through is permissable.
 */
static inline void NETC_PortSetSpeed(NETC_PORT_Type *base, uint16_t pSpeed)
{
    assert(pSpeed <= 15999U);
    base->PCR = (base->PCR & ~NETC_PORT_PCR_PSPEED_MASK) | NETC_PORT_PCR_PSPEED(pSpeed);
}

/*! @} */ // end of netc_hw_port
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_tx
#endif
/*! @addtogroup netc_hw_port_tx
 * @{
 */

/*!
 * @brief Configure the port time gating Scheduling
 *
 * @param base
 * @param config
 * @return status_t
 */
static inline status_t NETC_PortConfigTGS(NETC_PORT_Type *base, const netc_port_tg_config_t *config)
{
    base->PTGSATOR = NETC_PORT_PTGSATOR_ADV_TIME_OFFSET(config->advOffset);
    if ((base->PCAPR & NETC_PORT_PCAPR_LINK_TYPE_MASK) == 0U)
    {
        base->PTGSHCR = NETC_PORT_PTGSHCR_HOLD_SKEW(config->holdSkew);
    }
    return kStatus_Success;
}

/*!
 * @brief Config the Credit-Based Shaper (CBS) for specified Port Traffic Class
 *
 * @param base
 * @param tcIdx
 * @param config
 * @return status_t
 */
status_t NETC_PortConfigTcCBS(NETC_PORT_Type *base, netc_hw_tc_idx_t tcIdx, const netc_port_tc_cbs_config_t *config);

/*!
 * @brief Config the max Transmit max SDU for specified Port Traffic Class
 *
 * @param base
 * @param tcIdx
 * @param config
 * @return status_t
 */
static inline status_t NETC_PortConfigTcMaxSDU(NETC_PORT_Type *base,
                                               netc_hw_tc_idx_t tcIdx,
                                               const netc_port_tc_sdu_config_t *config)
{
    status_t result = kStatus_Success;

    if (config->maxSduSized > 0x07D0U)
    {
        /* This limit must not exceed 0x07D0 (2000 bytes) */
        result = kStatus_OutOfRange;
    }
    else
    {
        base->TCT_NUM[tcIdx].PTCTMSDUR = NETC_PORT_PTCTMSDUR_SF_MAXSDU_DIS(!config->enTxMaxSduCheck) |
                                         NETC_PORT_PTCTMSDUR_SDU_TYPE(config->sduType) |
                                         NETC_PORT_PTCTMSDUR_MAXSDU(config->maxSduSized);
    }

    return result;
}

/*!
 * @brief Read the max Transmit max SDU for specified Port Traffic Class
 *
 * @param base
 * @param tcIdx
 * @param config
 * @return status_t
 */
static inline status_t NETC_PortGetTcMaxSDU(NETC_PORT_Type *base,
                                            netc_hw_tc_idx_t tcIdx,
                                            netc_port_tc_sdu_config_t *config)
{
    config->maxSduSized = (uint16_t)(base->TCT_NUM[tcIdx].PTCTMSDUR & NETC_PORT_PTCTMSDUR_MAXSDU_MASK) >> NETC_PORT_PTCTMSDUR_MAXSDU_SHIFT; 
    config->enTxMaxSduCheck = (bool)((base->TCT_NUM[tcIdx].PTCTMSDUR & NETC_PORT_PTCTMSDUR_SF_MAXSDU_DIS_MASK) >> NETC_PORT_PTCTMSDUR_SF_MAXSDU_DIS_SHIFT);
    config->sduType = (netc_tc_sdu_type_t)(uint32_t)((base->TCT_NUM[tcIdx].PTCTMSDUR & NETC_PORT_PTCTMSDUR_SDU_TYPE_MASK) >> NETC_PORT_PTCTMSDUR_SDU_TYPE_SHIFT);

    return kStatus_Success;
}

/*! @} */ // end of netc_hw_port_tx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_tx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_rx
#endif
/*! @addtogroup netc_hw_port_rx
 * @{
 */

/*!
 * @brief Set port Parser.
 *
 * @param base  PORT peripheral base address.
 * @param config  The port Parser configuration.
 */
static inline void NETC_PortSetParser(NETC_PORT_Type *base, const netc_port_parser_config_t *config)
{
    base->PPCR = NETC_PORT_PPCR_L4PFS(config->l4PayloadCount) | NETC_PORT_PPCR_L4HFP(config->enableL4Parser) |
                 NETC_PORT_PPCR_L3PFS(config->l3PayloadCount) | NETC_PORT_PPCR_L3HFP(config->enableL3Parser) |
                 NETC_PORT_PPCR_L2PFS(config->l2PloadCount);
}

/*!
 * @brief Set port acceptable VLAN.
 *
 * @param base  PORT peripheral base address.
 * @param config  The port acceptable vlan classification configuration.
 */
static inline void NETC_PortSetVlanClassify(NETC_PORT_Type *base, const netc_port_vlan_classify_config_t *config)
{
    base->PTAR = NETC_PORT_PTAR_OVTPIDL(config->outerMask) | NETC_PORT_PTAR_IVTPIDL(config->innerMask);
}

/*!
 * @brief Set port Qos Classification.
 *
 * @param base  PORT peripheral base address.
 * @param config  The port QoS classification configuration.
 * @return status_t
 */
static inline status_t NETC_PortSetQosClassify(NETC_PORT_Type *base, const netc_port_qos_classify_config_t *config)
{
#if defined(FSL_FEATURE_NETC_HAS_ERRATA_051649) && FSL_FEATURE_NETC_HAS_ERRATA_051649
    /* ERRATA051649: Only mapping profile instance 0 can be used. Mapping profile instance 1 cannot be used due the decoding of the selected
       profile is not correct. Therefore, if any switch port is configured to use the second mapping profile (1), all switch ports will not
       assign the default QoS correctly. */
    if (config->vlanQosMap != 0U)
    {
        return kStatus_InvalidArgument;
    }
#endif

    base->PQOSMR = NETC_PORT_PQOSMR_VQMP(config->vlanQosMap) | NETC_PORT_PQOSMR_DIPV(config->defaultIpv) |
                   NETC_PORT_PQOSMR_DDR(config->defaultDr) | NETC_PORT_PQOSMR_VE(config->enVlanInfo) |
                   NETC_PORT_PQOSMR_VS(config->vlanTagSelect);

    return kStatus_Success;
}

/*!
 * @brief Set port ingress filter.
 *
 * @param base  PORT peripheral base address.
 * @param config  The port ingress filter configuration.
 */
static inline void NETC_PortSetIPF(NETC_PORT_Type *base, const netc_port_ipf_config_t *config)
{
    base->PCR    = NETC_PORT_PCR_L2DOSE(config->enL2Dos);
    base->PIPFCR = NETC_PORT_PIPFCR_EN(config->enIPFTable);
}

/*!
 * @brief Set port Ingress stream identification.
 *
 * @param base  PORT peripheral base address.
 * @param config  The port Ingress stream identification configuration.
 */
static inline void NETC_PortSetISI(NETC_PORT_Type *base, const netc_port_psfp_isi_config *config)
{
    /* Configure ingress stream identification */
    base->PISIDCR = NETC_PORT_PISIDCR_ISEID(config->defaultISEID) | NETC_PORT_PISIDCR_KC1EN(config->enKC1) |
                    NETC_PORT_PISIDCR_KC0EN(config->enKC0) | NETC_PORT_PISIDCR_KCPAIR(config->kcPair);
}

/*! @} */ // end of netc_hw_port_rx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_rx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_mac
#endif
/*! @addtogroup netc_hw_port_mac
 * @{
 */

/*!
 * @brief Get port MAC interrupt flags
 *
 * @param base  NETC ETH link base register.
 * @param mac  MAC type.
 */
uint32_t NETC_GetPortMacInterruptFlags(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType);

/*!
 * @brief Clear port MAC interrupt flags
 *
 * @param base  NETC ETH link base register.
 * @param mac  MAC type.
 * @param mask  Bit mask of interrupts to enable. See #netc_port_intr_flags_t for the set
 *              of constants that should be OR'd together to form the bit mask.
 */
void NETC_ClearPortMacInterruptFlags(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType, uint32_t mask);

/*!
 * @brief Enable/Disable port MAC interrupts
 *
 * @param base  NETC ETH link base register.
 * @param mac  MAC type.
 * @param mask  Bit mask of interrupts to enable. See #netc_port_intr_flags_t for the set
 *              of constants that should be OR'd together to form the bit mask.
 * @param enable  Enable/Disable interrupts.
 */
void NETC_EnablePortMacInterrupts(NETC_ETH_LINK_Type *base, netc_port_phy_mac_type_t macType, uint32_t mask, bool enable);

/*!
 * @brief Enable/Disable Loopback for specified MAC
 *
 * @param base
 * @param loopMode
 * @param enable
 * @return status_t
 */
status_t NETC_PortEnableLoopback(NETC_ETH_LINK_Type *base, netc_port_loopback_mode_t loopMode, bool enable);

/*!
 * @brief Get ethernet MAC port MII mode.
 *
 * @param base Ethernet MAC port peripheral base address.
 * @return netc_hw_mii_mode_t
 */
static inline netc_hw_mii_mode_t NETC_PortGetMIIMode(NETC_ETH_LINK_Type *base)
{
    return (netc_hw_mii_mode_t)(uint32_t)(base->PM0_IF_MODE & NETC_ETH_LINK_PM0_IF_MODE_IFMODE_MASK);
}

/*!
 * @brief Configure ethernet MAC interface mode, speed and duplex for specified PORT.
 *
 * @param base Ethernet MAC port peripheral base address.
 * @param miiMode The Ethernet MAC MII mode.
 * @param speed The Ethernet MAC speed.
 * @param duplex The Ethernet MAC duplex.
 * @return status_t
 */
status_t NETC_PortSetMII(NETC_ETH_LINK_Type *base,
                         netc_hw_mii_mode_t miiMode,
                         netc_hw_mii_speed_t speed,
                         netc_hw_mii_duplex_t duplex);

/*!
 * @brief Set the maximum supported received frame size.
 *
 * @param base Ethernet MAC port peripheral base address.
 * @param size Maximum frame size to set.
 * @return status_t
 */
status_t NETC_PortSetMaxFrameSize(NETC_ETH_LINK_Type *base, uint16_t size);

/*!
 * @brief Configure ethernet MAC for specified PORT.
 * Set the MII mode, speed/duplex, reverse mode, etc.
 *
 * @param base Ethernet MAC port peripheral base address.
 * @param config The Ethernet MAC configuration.
 * @return status_t
 */
status_t NETC_PortConfigEthMac(NETC_ETH_LINK_Type *base, const netc_port_ethmac_t *config);

/*!
 * @brief Do software reset for Ethernet MAC.
 *
 * @note This can reset all statistic counters.
 *
 * @param base  PORT MAC peripheral base address.
 */
static inline void NETC_PortSoftwareResetEthMac(NETC_ETH_LINK_Type *base)
{
    base->PM0_COMMAND_CONFIG |= NETC_ETH_LINK_PM0_COMMAND_CONFIG_SWR_MASK;
    while ((base->PM0_COMMAND_CONFIG & NETC_ETH_LINK_PM0_COMMAND_CONFIG_SWR_MASK) != 0U)
    {
    }
    base->PM1_COMMAND_CONFIG |= NETC_ETH_LINK_PM0_COMMAND_CONFIG_SWR_MASK;
    while ((base->PM1_COMMAND_CONFIG & NETC_ETH_LINK_PM1_COMMAND_CONFIG_SWR_MASK) != 0U)
    {
    }
}

/*!
 * @brief Get Ethernet MAC preemption status.
 *
 * @param base  PORT MAC peripheral base address.
 * @param status Point to the buffer which store status.
 */
static inline void NETC_PortGetPhyMacPreemptionStatus(NETC_ETH_LINK_Type *base,
                                                      netc_port_phy_mac_preemption_status_t *status)
{
    status->verifyStatus = (netc_port_preemption_verify_status_t)(uint32_t)(
        (base->MAC_MERGE_MMCSR & NETC_ETH_LINK_MAC_MERGE_MMCSR_VSTS_MASK) >> NETC_ETH_LINK_MAC_MERGE_MMCSR_VSTS_SHIFT);
    status->mergeActive = ((base->MAC_MERGE_MMCSR & NETC_ETH_LINK_MAC_MERGE_MMCSR_TXSTS_MASK) != 0U) ? true : false;
}

/*!
 * @brief Get Ethernet MAC Tx Traffic Statistics .
 *
 * @param base  PORT MAC peripheral base address.
 * @param macType Express MAC or Preemptable MAC.
 * @param status Point to the buffer which store statistics.
 */
void NETC_PortGetPhyMacTxStatistic(NETC_ETH_LINK_Type *base,
                                   netc_port_phy_mac_type_t macType,
                                   netc_port_phy_mac_traffic_statistic_t *statistic);

/*!
 * @brief Get Ethernet MAC Rx Traffic Statistics .
 *
 * @param base  PORT MAC peripheral base address.
 * @param macType Express MAC or Preemptable MAC.
 * @param status Point to the buffer which store statistics.
 */
void NETC_PortGetPhyMacRxStatistic(NETC_ETH_LINK_Type *base,
                                   netc_port_phy_mac_type_t macType,
                                   netc_port_phy_mac_traffic_statistic_t *statistic);

/*!
 * @brief Get Ethernet MAC Rx/Tx Drops/Errors Statistics .
 *
 * @param base  PORT MAC peripheral base address.
 * @param macType Express MAC or Preemptable MAC.
 * @param status Point to the buffer which store statistics.
 */
void NETC_PortGetPhyMacDiscardStatistic(NETC_ETH_LINK_Type *base,
                                        netc_port_phy_mac_type_t macType,
                                        netc_port_phy_mac_discard_statistic_t *statistic);

/*!
 * @brief Get Ethernet Preemptable MAC preemption Statistics .
 *
 * @param base  PORT MAC peripheral base address.
 * @param status Point to the buffer which store statistics.
 */
void NETC_PortGetPhyMacPreemptionStatistic(NETC_ETH_LINK_Type *base,
                                           netc_port_phy_mac_preemption_statistic_t *statistic);

#if !(defined(FSL_FEATURE_NETC_HAS_NO_SWITCH) && FSL_FEATURE_NETC_HAS_NO_SWITCH)
/*!
 * @brief Get Pseudo MAC Tx/Rx Traffic Statistics .
 *
 * @param base  PORT MAC peripheral base address.
 * @param getTx true is get Tx, false is get Rx.
 * @param status Point to the buffer which store statistics.
 */
void NETC_PortGetPseudoMacTrafficStatistic(NETC_PSEUDO_LINK_Type *base,
                                           bool getTx,
                                           netc_port_pseudo_mac_traffic_statistic_t *statistic);
#endif

/*! @} */ // end of netc_hw_port_mac
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_mac
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_PORT_H_ */
