/*
 * Copyright 2021-2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_SI_H_
#define FSL_NETC_SI_H_

#include "fsl_netc.h"
#include "netc_hw/fsl_netc_hw.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_si
#endif
/*!
 * @addtogroup netc_hw_si
 * @{
 */

/*! @name Control and status bit masks of the transmit buffer descriptor. */
/*@{*/
/*! @brief Defines for read format. */
#define NETC_SI_TXDESCRIP_RD_TXSTART(n) ((uint32_t)(n)&0x1fffffUL)
#define NETC_SI_TXDESCRIP_RD_DR(n)      (((uint32_t)(n)&0x3U) << 10U)
#define NETC_SI_TXDESCRIP_RD_IPV(n)     (((uint32_t)(n)&0x7U) << 12U)
#define NETC_SI_TXDESCRIP_RD_PORT(n)    (((uint32_t)(n)&0x1fU) << 16U)
#define NETC_SI_TXDESCRIP_RD_TSR_MASK   (1UL << 22U)
#define NETC_SI_TXDESCRIP_RD_SMSO_MASK  (1UL << 23U)
#define NETC_SI_TXDESCRIP_RD_FLQ(n)     (((uint32_t)(n)&0x03U) << 24U)
#define NETC_SI_TXDESCRIP_RD_TSE_MASK   (1UL << 25U)
#define NETC_SI_TXDESCRIP_RD_FL(n)      (((uint32_t)(n)&0x03U) << 27U)
/*@}*/

/*!
 * @brief ENETC Station Interface BD Ring priority enumeration
 *
 */
typedef enum _enetc_si_bdr_priority
{
    kNETC_SIBdrPriorityLowest = 0U,
    kNETC_SIBdrPriority0      = 0U,
    kNETC_SIBdrPriority1,
    kNETC_SIBdrPriority2,
    kNETC_SIBdrPriority3,
    kNETC_SIBdrPriority4,
    kNETC_SIBdrPriority5,
    kNETC_SIBdrPriority6,
    kNETC_SIBdrPriority7       = 7U,
    kNETC_SIBdrPriorityHighest = kNETC_SIBdrPriority7,
} enetc_si_bdr_priority_t;

/*! @} */ // end of netc_hw_si
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_si
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_si
#endif
/*!
 * @addtogroup netc_hw_si
 * @{
 */

/*!
 * @brief Enable the Station Interface(SI)
 *
 * @param base
 */
static inline void NETC_SIEnable(ENETC_SI_Type *base, bool enable)
{
    if (enable)
    {
        base->SIMR |= ENETC_SI_SIMR_EN_MASK;
    }
    else
    {
        base->SIMR &= ~ENETC_SI_SIMR_EN_MASK;
    }
}

/*!
 * @brief Enable the specified Rx BD ring
 *
 * @param base
 * @param ring  The ring index.
 * @param base  Enable/Disable the ring.
 */
static inline void NETC_SIRxRingEnable(ENETC_SI_Type *base, uint8_t ring, bool enable)
{
    if (enable)
    {
        base->BDR[ring].RBMR |= ENETC_SI_RBMR_EN_MASK;
    }
    else
    {
        base->BDR[ring].RBMR &= ~ENETC_SI_RBMR_EN_MASK;
    }
}

/*!
 * @brief Enable/Disable unicast/multicast/boardcast promisc mode for specified SI
 *
 * @param base
 * @param type
 * @param enable
 */
static inline void NETC_SIEnablePromisc(ENETC_SI_Type *base, netc_packet_type_t type, bool enable)
{
    if (enable)
    {
        base->SIMR |= ((uint32_t)1U << ((uint32_t)type + 1U));
    }
    else
    {
        base->SIMR &= ~((uint32_t)1U << ((uint32_t)type + 1U));
    }
}

/*!
 * @brief Set producer index of specified Tx BD ring
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @param producer  The producer index of specified ring.
 */
static inline void NETC_SISetTxProducer(ENETC_SI_Type *base, uint8_t ring, uint16_t producer)
{
    base->BDR[ring].TBPIR = producer;
}

/*!
 * @brief Get consumer index of specified Tx BD ring
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @return consumer  The consumer index of specified ring.
 */
static inline uint16_t NETC_SIGetTxConsumer(ENETC_SI_Type *base, uint8_t ring)
{
    return (uint16_t)base->BDR[ring].TBCIR;
}

/*!
 * @brief Set consumer index of specified Rx BD ring
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @param consumer  The consumer index of specified ring.
 */
static inline void NETC_SISetRxConsumer(ENETC_SI_Type *base, uint8_t ring, uint16_t consumer)
{
    base->BDR[ring].RBCIR = consumer;
}

/*!
 * @brief Get producer index of specified Rx BD ring
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @return producer  The producer index of specified ring.
 */
static inline uint16_t NETC_SIGetRxProducer(ENETC_SI_Type *base, uint8_t ring)
{
    return (uint16_t)base->BDR[ring].RBPIR;
}

/*!
 * @brief Configure the Transmit Buffer Descriptor Ring for specified SI
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @param bdrConfig  The BD ring configuration.
 * @return status_t
 */
status_t NETC_SIConfigTxBDR(ENETC_SI_Type *base, uint8_t ring, const netc_tx_bdr_config_t *bdrConfig);

/*!
 * @brief Configure the Rx Buffer Descriptor Ring for specified SI
 *
 * @param base  SI base address.
 * @param ring  BD ring index.
 * @param bdrConfig  The BD ring configuration.
 * @return status_t
 */
status_t NETC_SIConfigRxBDR(ENETC_SI_Type *base, uint8_t ring, const netc_rx_bdr_config_t *bdrConfig);

/*!
 * @brief Enable the mapping of VLAN to IPV
 *
 * @param base  SI base address.
 * @param pcpDei  The VLAN tag pcp dei value (use NETC_VLAN_PCP_DEI_VALUE macro).
 * @param ipv  The IPV value for this VLAN mapping.
 */
static inline void NETC_SIMapVlanToIpv(ENETC_SI_Type *base, uint8_t pcpDei, uint8_t ipv)
{
    if (pcpDei <= 7U)
    {
        base->SIVLANIPVMR0 |= ENETC_SI_SIVLANIPVMR0_PCP_DEI_0(ipv) << (pcpDei * 4U);
    }
    else
    {
        pcpDei -= 8U;
        base->SIVLANIPVMR1 |= ENETC_SI_SIVLANIPVMR1_PCP_DEI_8(ipv) << (pcpDei * 4U);
    }
}
/*!
 * @brief Enable the mapping of VLAN to IPV
 *
 * @param base  SI base address.
 * @param enable  Whether enable mapping.
 * @return status_t
 */
static inline void NETC_SIEnableVlanToIpv(ENETC_SI_Type *base, bool enable)
{
    if (enable)
    {
        base->SIMR |= ENETC_SI_SIMR_V2IPVE_MASK;
    }
    else
    {
        base->SIMR &= ~ENETC_SI_SIMR_V2IPVE_MASK;
    }
}

/*!
 * @brief Set the IPV to ring mapping
 *
 * @param base  SI base address.
 * @param ipv  IPV value to be mapped.
 * @param ring  The Rx BD ring index to be mapped.
 * @return status_t
 */
static inline void NETC_SIMapIpvToRing(ENETC_SI_Type *base, uint8_t ipv, uint8_t ring)
{
    base->SIIPVBDRMR0 |= ENETC_SI_SIIPVBDRMR0_IPV0BDR(ring) << (ipv * 4U);
}

/*!
 * @brief Set the group of Rx BD ring
 *
 * @param base  SI base address.
 * @param groupNum  Total group number.
 * @param ringPerGroup Rings per group.
 * @return status_t
 */
static inline void NETC_SISetRxBDRGroup(ENETC_SI_Type *base, uint8_t groupNum, uint8_t ringPerGroup)
{
    /* Rings per group should be > 0. */
    assert(ringPerGroup != 0U);

    base->SIRBGCR =
        ENETC_SI_SIRBGCR_NUM_GROUPS(groupNum) | ENETC_SI_SIRBGCR_RINGS_PER_GROUP((uint32_t)ringPerGroup - 1U);
}

/*!
 * @brief Set the default used receive Rx BD ring group.
 * @note The IPV mapped ring index is the relative index inside the default used group.
 *
 * @param base  SI base address.
 * @param groupNum  The default Rx group index.
 * @return status_t
 */
static inline void NETC_SISetDefaultRxBDRGroup(ENETC_SI_Type *base, netc_hw_enetc_si_rxr_group groupIdx)
{
    base->SIMR = (base->SIMR & (~ENETC_SI_SIMR_DEFAULT_RX_GROUP_MASK)) | ENETC_SI_SIMR_DEFAULT_RX_GROUP(groupIdx);
}

/*!
 * @brief Clean the SI transmit interrupt flags
 *
 * @param base  SI base address.
 * @param txFrameIntrMask  IPV value to be mapped, bit x represents ring x.
 * @param txThresIntrMask  The Rx BD ring index to be mapped, bit x represents ring x.
 */
static inline void NETC_SICleanTxIntrFlags(ENETC_SI_Type *base, uint16_t txFrameIntrMask, uint16_t txThresIntrMask)
{
    base->SITXIDR0 = ((uint32_t)txFrameIntrMask << 16U) + txThresIntrMask;
}

/*!
 * @brief Clean the SI receive interrupt flags
 *
 * @param base  SI base address.
 * @param rxIntrMask  Rx interrupt bit mask, bit x represents ring x.
 */
static inline void NETC_SICleanRxIntrFlags(ENETC_SI_Type *base, uint32_t rxIntrMask)
{
    base->SIRXIDR0 = rxIntrMask;
}

/*!
 * @brief PSI enables/disables specified interrupt
 *
 * @param base  SI base address.
 * @param mask  The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 * @param enable  Enable/Disable the interrupt.
 */
void NETC_SIPsiEnableInterrupt(ENETC_SI_Type *base, uint32_t mask, bool enable);

/*!
 * @brief PSI gets interrupt event flag status
 *
 * @param base  SI base address.
 * @return The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 */
static inline uint32_t NETC_SIPsiGetStatus(ENETC_SI_Type *base)
{
    return (base->PSI.PSIIDR & 0xFFFEFFFEU);
}

/*!
 * @brief PSI clears interrupt event flag
 *
 * @param base  SI base address.
 * @param mask  The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 */
static inline void NETC_SIPsiClearStatus(ENETC_SI_Type *base, uint32_t mask)
{
    base->PSI.PSIIDR = mask;
}

/*!
 * @brief PSI sends message to specified VSI(s)
 *
 * @param base  SI base address.
 * @param msg  The message to be sent.
 * @param vsi  The VSI number.
 * @return status_t
 */
status_t NETC_SIPsiSendMsg(ENETC_SI_Type *base, uint16_t msg, netc_vsi_number_t vsi);

/*!
 * @brief PSI checks Tx busy flag which should be cleaned when VSI receive the message data
 *
 * @param base  SI base address.
 * @param vsi  The VSI number.
 * @return The busy status of specified VSI.
 */
static inline bool NETC_SIPsiCheckTxBusy(ENETC_SI_Type *base, netc_vsi_number_t vsi)
{
    return ((base->PSI_A.PSIMSGSR & (uint32_t)vsi) != 0U);
}

/*!
 * @brief PSI sets Rx buffer to receive message from specified VSI
 * @note The buffer memory size should be big enough for the message data from VSI
 *
 * @param base  SI base address.
 * @param vsi  The VSI number.
 * @param buffAddr  The buffer address to store message data from VSI, must be 64 bytes aligned.
 * @return status_t
 */
status_t NETC_SIPsiSetRxBuffer(ENETC_SI_Type *base, netc_vsi_number_t vsi, uint64_t buffAddr);

/*!
 * @brief PSI gets Rx message from specified VSI
 *
 * @param base  SI base address.
 * @param vsi  The VSI number.
 * @param msgInfo  The Rx message information.
 */
status_t NETC_SIPsiGetRxMsg(ENETC_SI_Type *base, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo);

/*!
 * @brief Enable VSI interrupt
 *
 * @param base  SI base address.
 * @param mask  The interrupt mask, see #netc_vsi_msg_flags_t which should be OR'd together.
 * @param enable  Enable/Disable interrupt.
 */
void NETC_SIVsiEnableInterrupt(ENETC_SI_Type *base, uint32_t mask, bool enable);

/*!
 * @brief Get VSI interrupt status
 *
 * @param base  SI base address.
 * @return A bitmask composed of #netc_vsi_msg_flags_t enumerators OR'd together.
 */
static inline uint32_t NETC_SIVsiGetStatus(ENETC_SI_Type *base)
{
    return ((base->VSI.VSIIDR & (ENETC_SI_VSIIDR_MS_MASK | ENETC_SI_VSIIDR_MR_MASK)) >> 8U);
}

/*!
 * @brief Clear VSI interrupt status
 *
 * @param base  SI base address.
 * @param mask  The interrupt mask, see #netc_vsi_msg_flags_t which should be OR'd together.
 */
static inline void NETC_SIVsiClearStatus(ENETC_SI_Type *base, uint32_t mask)
{
    base->VSI.VSIIDR = mask << 8U;
}

/*!
 * @brief VSI sends message to PSI
 *
 * @param base  SI base address.
 * @param msgAddr  Address to store message ready to be sent, must be 64 bytes aligned.
 * @param msgLen  The message length, must be 32 bytes aligned.
 * @return status_t
 */
status_t NETC_SIVsiSendMsg(ENETC_SI_Type *base, uint64_t msgAddr, uint32_t msgLen);

/*!
 * @brief Check VSI Tx status
 *
 * @param base  SI base address.
 * @param status  The VSI Tx status structure.
 */
void NETC_SIVsiCheckTxStatus(ENETC_SI_Type *base, netc_vsi_msg_tx_status_t *status);

/*!
 * @brief VSI receives message from PSI
 *
 * @param base  SI base address.
 * @param msg  The message from PSI.
 * @return status_t
 */
status_t NETC_SIVsiReceiveMsg(ENETC_SI_Type *base, uint16_t *msg);

/*!
 * @brief Get the discard statistic from SI layer
 *
 * @param base  SI base address.
 * @param statistic  The statistic data.
 */
void NETC_SIGetDiscardStatistic(ENETC_SI_Type *base, netc_si_discard_statistic_t *statistic);

/*!
 * @brief Get the traffic statistic from SI layer
 *
 * @param base  SI base address.
 * @param statistic  The statistic data.
 */
void NETC_SIGetTrafficStatistic(ENETC_SI_Type *base, netc_si_traffic_statistic_t *statistic);

/*! @} */ // end of netc_hw_si
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_si
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_SI_H_ */
