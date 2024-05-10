/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_ENETC_H_
#define FSL_NETC_ENETC_H_

#include "fsl_netc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_enetc
#endif
/*! @addtogroup netc_hw_enetc
 * @{
 */

/*!
 * @brief ENETC capability.
 *
 */
typedef struct _netc_enetc_cap
{
    bool funcSafety : 1;   /*!< Support for safety capability. */
    bool wol : 1;          /*!< Support for Wake-on-LAN in low-power mode. */
    bool rss : 1;          /*!< Support for RSS. */
    bool tsd : 1;          /*!< Support for time specific departure. */
    bool rfs : 1;          /*!< Support for RFS. */
    uint32_t ipvNum : 5;   /*!< IPV number. */
    uint32_t vsiNum : 4;   /*!< VSI number. */
    uint32_t msixNum : 11; /*!< MSIX table vector/entry number. */
    uint32_t tcsNum : 4;   /*!< Traffic class number. */
    uint16_t uchNum;       /*!< Unicast hash entry number. */
    uint16_t mchNum;       /*!< Multicast hash entry number. */
    uint16_t rxBdrNum;     /*!< Rx BD ring number. */
    uint16_t txBdrNum;     /*!< Tx BD ring number. */
} netc_enetc_cap_t;

/*!
 * @brief Check whether ENETC has switch management capability
 *
 * @param base   NETC peripheral base address.
 * @return true or false
 */
static inline bool NETC_EnetcHasManagement(NETC_ENETC_Type *base)
{
    return ((base->SMCAPR & NETC_ENETC_SMCAPR_SM_MASK) != 0U);
}

/*!
 * @brief Get ENETC capability
 *
 * @param base   NETC peripheral base address.
 * @param capability Pointer to capability structure.
 */
void NETC_EnetcGetCapability(NETC_ENETC_Type *base, netc_enetc_cap_t *capability);

/*!
 * @brief Set MAC address for specified VSI of ENETC
 *
 * @param base
 * @param macAddr
 */
void NETC_EnetcSetSIMacAddr(NETC_ENETC_Type *base, uint8_t si, uint8_t *macAddr);

/*!
 * @brief Configure SI
 *
 * @param base  ENETC peripheral base address.
 * @param si  The SI number
 * @param psConfig  The SI configuration
 * @return status_t
 */
status_t NETC_EnetcConfigureSI(NETC_ENETC_Type *base, uint8_t si, const netc_hw_enetc_si_config_t *psConfig);

/*!
 * @brief Set SI MSIX table entry number
 *
 * @param base  ENETC peripheral base address.
 * @param si  The SI number.
 * @param msixNum  The MSIX table entry number.
 * @return status_t
 */
status_t NETC_EnetcSetMsixEntryNum(NETC_ENETC_Type *base, uint8_t si, uint32_t msixNum);

/*!
 * @brief Enable/Disable specified SI
 *
 * @param base  ENETC peripheral base address.
 * @param si  SI index.
 * @param enable  Enable/Disable SI from ENETC layer.
 */
static inline void NETC_EnetcEnableSI(NETC_ENETC_Type *base, uint8_t si, bool enable)
{
    /* Enable SI from ENETC block, need to set SI block together to enable SI completely. */
    if (enable)
    {
        base->PMR |= (NETC_ENETC_PMR_SI0EN_MASK << si);
    }
    else
    {
        base->PMR &= ~(NETC_ENETC_PMR_SI0EN_MASK << si);
    }
}

/*!
 * @brief Get ENETC discard statistic data
 *
 * @param base  ENETC peripheral base address.
 * @param statistic  Statistic data.
 */
void NETC_EnetcGetPortDiscardStatistic(NETC_ENETC_Type *base, netc_enetc_port_discard_statistic_t *statistic);

/*!
 * @brief Enable MAC promiscuous mode
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param enableUCPromis  Enable unicast frame promiscuous.
 * @param enableMCPromis  Enable multicast frame promiscuous.
 */
void NETC_EnetcEnablePromiscuous(NETC_ENETC_Type *base, uint8_t si, bool enableUCPromis, bool enableMCPromis);

/*!
 * @brief Configure VLAN filter
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param config  Enable untagged VLAN frame promiscuous.
 */
void NETC_EnetcConfigureVlanFilter(NETC_ENETC_Type *base, uint8_t si, netc_si_l2vf_config_t *config);

/*!
 * @brief Add the hash filter for the MAC address
 *
 * Hardware layer will not maitain the counter of the hash filter. API layer shall cover this requirement.
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param type  Unicast or multicast frame type.
 * @param hashIndex  The calculated hash index of MAC address.
 */
void NETC_EnetcAddMacAddrHash(NETC_ENETC_Type *base, uint8_t si, netc_packet_type_t type, uint8_t hashIndex);

/*!
 * @brief Remove the hash filter for the MAC address
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param type  Unicast or multicast frame type.
 * @param hashIndex  The calculated hash index of MAC address.
 */
void NETC_EnetcDelMacAddrHash(NETC_ENETC_Type *base, uint8_t si, netc_packet_type_t type, uint8_t hashIndex);

/*!
 * @brief Add the hash filter for the VLAN
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param hashIndex  The calculated hash index of MAC address.
 */
void NETC_EnetcAddVlanHash(NETC_ENETC_Type *base, uint8_t si, uint8_t hashIndex);

/*!
 * @brief Remove the hash filter for the VLAN
 *
 * @param base  ENETC peripheral base address.
 * @param si    SI index.
 * @param hashIndex  The calculated hash index of MAC address.
 */
void NETC_EnetcDelVlanHash(NETC_ENETC_Type *base, uint8_t si, uint8_t hashIndex);

/*!
 * @brief Enable / Disable ENETC Port Time Specific Departure (TSD) feature
 *
 * It can't work with QBV CBS
 *
 * @param base
 * @param tcIdx
 * @param isEnable
 * @return status_t
 */
static inline status_t NETC_EnetcPortEnableTSD(NETC_ENETC_Type *base, netc_hw_tc_idx_t tcIdx, bool isEnable)
{
    base->PTCTSDR[tcIdx] = NETC_ENETC_PTCTSDR_TSDE(isEnable);
    return kStatus_Success;
}

/*!
 * @brief Set ENETC Rx native outer/inner VLAN
 *
 *  It is used for classification when untagged frames are received by the port.
 *
 * @param base
 * @param config
 * @param isOunter
 */
static inline void NETC_EnetcPortSetNativeVLAN(NETC_ENETC_Type *base,
                                               const netc_enetc_native_vlan_config_t *config,
                                               bool isOuter)
{
    if (isOuter)
    {
        base->PONVLANR = NETC_ENETC_PONVLANR_VZE(config->enUnderZeroVid) |
                         NETC_ENETC_PONVLANR_PNE(config->enUnderNoVlan) |
                         NETC_ENETC_PONVLANR_TPID(config->vlanTag.tpid) | NETC_ENETC_PONVLANR_PCP(config->vlanTag.pcp) |
                         NETC_ENETC_PONVLANR_DEI(config->vlanTag.dei) | NETC_ENETC_PONVLANR_VID(config->vlanTag.vid);
    }
    else
    {
        base->PINVLANR = NETC_ENETC_PINVLANR_VZE(config->enUnderZeroVid) |
                         NETC_ENETC_PINVLANR_PNE(config->enUnderNoVlan) |
                         NETC_ENETC_PINVLANR_TPID(config->vlanTag.tpid) | NETC_ENETC_PINVLANR_PCP(config->vlanTag.pcp) |
                         NETC_ENETC_PINVLANR_DEI(config->vlanTag.dei) | NETC_ENETC_PINVLANR_VID(config->vlanTag.vid);
    }
}

/*!
 * @brief Set ENETC Parser configuration
 *
 *  PARCSCR and PARCE0CR - PARCE3CR.
 *
 * @param base
 * @param config
 */
static inline void NETC_EnetcSetParser(NETC_ENETC_Type *base, const netc_enetc_parser_config_t *config)
{
    base->PARCSCR = NETC_ENETC_PARCSCR_L3CD(config->disL3Checksum) | NETC_ENETC_PARCSCR_L4CD(config->disL4Checksum);
    for (uint8_t i = 0u; i < 4U; i++)
    {
        base->PARCECR[i] = NETC_ENETC_PARCECR_ETYPE(config->custEtype[i].etype) |
                           NETC_ENETC_PARCECR_EN(config->custEtype[i].en) |
                           NETC_ENETC_PARCECR_CP(config->custEtype[i].cp);
    }
}

/*!
 * @brief Enable / Disable ENETC Wake-on-LAN mode
 *
 * Only available on ENETC 0
 *
 * @param base
 * @param isEnable
 * @return status_t
 */
static inline void NETC_EnetcEnableWakeOnLan(NETC_ENETC_Type *base, bool isEnable)
{
    if (0U != (base->ECAPR0 & NETC_ENETC_ECAPR0_WO_MASK))
    {
        base->PLPMR = NETC_ENETC_PLPMR_WME(isEnable);
    }
}
/*! @} */ // end of netc_hw_enetc
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_enetc
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_ENETC_H_ */
