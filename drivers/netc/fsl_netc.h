/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_H_
#define FSL_NETC_H_

#include "fsl_common.h"
#if defined(FSL_ETH_ENABLE_CACHE_CONTROL)
#include "fsl_cache.h"
#endif
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc
#endif
/*! @addtogroup netc
 * @{
 */

/*!
 * @defgroup netc_abbrev Abbreviation in NETC driver
 * @details Abbreviation list in NETC driver
 *   - UC: unicast
 *   - BC: broadcast
 *   - MC: multicast
 *   - IPF: ingress port filter
 *   - VlanC: Vlan classification
 *   - QosC: Qos Classification
 *   - FRER: Frame Replication and Elimination for Reliability
 *   - PSFP: Per-stream Filtering and Policing
 *   - FM: Frame Modification
 *   - SGI: Stream Gate Instance
 *   - SGC: Stream Gate Control List
 *   - ISI: Ingress Stream Identification
 *   - ISC: Ingress stream count
 *   - IS: Ingress Stream Table
 *   - VF: Vlan Filter
 *   - MF: Mac Filter
 *   - EM: Extract Match
 * @ingroup netc
 */

/*! @brief Driver Version */
#define FSL_NETC_DRIVER_VERSION (MAKE_VERSION(2, 6, 1))

/*! @brief Macro to divides an address into a low 32 bits and a possible high 32 bits */
#define NETC_ADDR_LOW_32BIT(x)  ((uint32_t)(x)&0xFFFFFFFFU)
#define NETC_ADDR_HIGH_32BIT(x) ((4U != sizeof(uintptr_t)) ? (((uintptr_t)(x) >> 32U) & 0xFFFFFFFFU) : 0U)

/*! @brief Status code for the NETC module */
enum
{
    kStatus_NETC_RxFrameEmpty   = MAKE_STATUS(kStatusGroup_NETC, 0), /*!< Rx BD ring empty. */
    kStatus_NETC_RxTsrResp      = MAKE_STATUS(kStatusGroup_NETC, 1), /*!< Rx timestamp reference response  */
    kStatus_NETC_RxFrameError   = MAKE_STATUS(kStatusGroup_NETC, 2), /*!< Rx frame error.  */
    kStatus_NETC_TxFrameOverLen = MAKE_STATUS(kStatusGroup_NETC, 3), /*!< Tx frame over length. */
    kStatus_NETC_LackOfResource =
        MAKE_STATUS(kStatusGroup_NETC, 4), /*!< Lack of resources to configure certain features. */
    kStatus_NETC_Unsupported      = MAKE_STATUS(kStatusGroup_NETC, 5), /*!< Unsupported operation/feature. */
    kStatus_NETC_RxHRZeroFrame    = MAKE_STATUS(kStatusGroup_NETC, 6), /*!< Rx frame host reason is zero */
    kStatus_NETC_RxHRNotZeroFrame = MAKE_STATUS(kStatusGroup_NETC, 7),  /*!< Rx frame host reason is not zero */
    kStatus_NETC_NotFound         = MAKE_STATUS(kStatusGroup_NETC, 8),  /*!< No entry found in hardware tables */
    kStatus_NETC_EntryExists      = MAKE_STATUS(kStatusGroup_NETC, 9)  /*!< An entry already exists in hardware tables */
};

/*! @brief Defines the common interrupt event for callback use. */
typedef enum _netc_ep_event
{
    kNETC_EPRxEvent, /*!< EP Rx interrupt event. */
    kNETC_EPTxEvent  /*!< EP Tx interrupt event. */
} netc_ep_event_t;

/*! @brief Status for the transmit buffer descriptor status. */
typedef enum _netc_ep_tx_status
{
    kNETC_EPTxSuccess       = 0x0, /*!< Success transmission. */
    kNETC_EPTxProgramErr    = 0x1, /*!< Error exists in either the Tx BD, the Tx ring registers, or both. */
    kNETC_EPTxTsdDrop       = 0x2, /*!< The time defined in TX_START expired before frame could be transmitted. */
    kNETC_EPTxFrameSizeErr  = 0x8, /*!< Frame size error. */
    kNETC_EPTxNullAddr      = 0x9, /*!< Null address. */
    kNETC_EPTxInvalidLength = 0xA, /*!< Invalid frame/buffer/chain length. */
    kNETC_EPTxSrcMacSpoofingDetect = 0x10, /*!< Source MAC address spoofing detected. */
    kNETC_EPTxPortRestDrop         = 0x20, /*!< Frame dropped due to port reset. */
    kNETC_EPTxPortDisableDrop      = 0x21, /*!< Frame dropped due to port disable. */
    kNETC_EPTxVlanTpidDrop         = 0x40, /*!< VLAN TPID not allowed. */
    kNETC_EPTxSmsoParamErr   = 0x60,  /*!< Programming error in buffer descriptor used for direct switch enqueue. */
    kNETC_EPTxFrameGateErr   = 0x80,  /*!< Frame too large for time gating window. */
    kNETC_EPTxAxiReadErr     = 0x90,  /*!< AXI read error. */
    kNETC_EPTxAxiWriteErr    = 0x91,  /*!< AXI write error. */
    kNETC_EPTxMultiBitECCErr = 0xA0,  /*!< Frame not transmitted(dropped) due to a multi-bit ECC error detected. */
    kNETC_EPTxParityErr      = 0xF0,  /*!< Parity error. */
    kNETC_EPTxSwCongestion   = 0x100, /*!< Frame dropped due to switch congestion. */
} netc_ep_tx_status_t;

/*! @brief VLAN tag struct */
typedef struct _netc_vlan
{
    uint32_t vid : 12;  /*!< Vlan Identifier. */
    uint32_t dei : 1;   /*!< Drop Eligible indicator. */
    uint32_t pcp : 3;   /*!< Priority. */
    uint32_t tpid : 16; /*!< Tag protocol identifier. */
} netc_vlan_t;

/*! @brief Ethernet VLAN Tag protocol identifier */
typedef enum _netc_vlan_tpid_select
{
    kNETC_StanCvlan = 0x0U, /*!< 0x8100. */
    kNETC_StanSvlan,        /*!< 0x88A8. */
    kNETC_CustomVlan1,      /*!< CVLANR1[ETYPE] */
    kNETC_CustomVlan2       /*!< CVLANR2[ETYPE] */
} netc_vlan_tpid_select_t;

/*! @brief Ethernet packet type enumerator */
typedef enum _netc_packet_type
{
    kNETC_PacketUnicast = 0U,
    kNETC_PacketMulticast,
    kNETC_PacketBroadcast,
} netc_packet_type_t;

/*! @brief Host reason*/
typedef enum _netc_host_reason
{
    kNETC_RegularFrame   = 0x0,
    kNETC_IngressMirror  = 0x1,
    kNETC_MACLearning    = 0x2,
    kNETC_TimestampResp  = 0x3,
    kNETC_SoftwareDefHR0 = 0x8,
    kNETC_SoftwareDefHR1 = 0x9,
    kNETC_SoftwareDefHR2 = 0xa,
    kNETC_SoftwareDefHR3 = 0xb,
    kNETC_SoftwareDefHR4 = 0xc,
    kNETC_SoftwareDefHR5 = 0xd,
    kNETC_SoftwareDefHR6 = 0xe,
    kNETC_SoftwareDefHR7 = 0xf
} netc_host_reason_t;

/*! @brief Buffer structure. Driver can send/receive one frame spread across multiple buffers */
typedef struct _ep_buffer_struct
{
    void *buffer;    /*!< Buffer address. */
    uint16_t length; /*!< Buffer data length. */
} netc_buffer_struct_t;

/*! @brief Frame structure for single Tx/Rx frame */
typedef struct _ep_frame_struct
{
    netc_buffer_struct_t *buffArray; /*!< Buffer array. Tx: [in]App sets, Rx: [in/out]App sets prepared array, driver
                                        sets back received buffers array. */
    uint16_t length; /*!< Buffer array length. Tx: [in]App sets, Rx: [in/out]App sets prepared array length, driver sets
                        back received buffers array length. */
} netc_frame_struct_t;

/*! @brief Frame attribute struct */
typedef struct _netc_frame_attr_struct
{
    bool isTsAvail;       /*!< Rx frame timestamp is available or not. */
    bool isVlanExtracted; /*!< Rx frame VLAN header is available or not. */
    bool isRssHashValid;
    uint16_t parserSummary;
    netc_host_reason_t hostReason;
    uint8_t srcPort;
    uint32_t rssHash;
    netc_vlan_t vlan;
    uint32_t timestamp; /*!< The timestamp of this Rx frame. */
} netc_frame_attr_t;

/*! @brief Frame attribute structure */
typedef struct _netc_tx_frame_info_struct
{
    bool isTsAvail;     /*!< Tx frame timestamp is available or not. */
    uint32_t timestamp; /*!< The timestamp of this Tx frame, valid when isTsAvail is true. */
    bool isTxTsIdAvail; /*!< Switch port Tx frame timestamp Identifier is available or not. */
    uint16_t txtsid; /*!< The Transmit Timestamp Identifier, valid when isTsIdAvail is true, use for Switch management
                        ENETC direct frame which has specified a timestamp request. */
    void *context;   /*!< Private context provided by the user. */
    netc_ep_tx_status_t status; /*!< Transmit status. */
} netc_tx_frame_info_t;

/*! @brief MSIX vector control field */
typedef enum _netc_msix_vector_ctrl
{
    kNETC_MsixIntrMaskBit = 1U, /*!< MSIX vector control interrupt mask bit. */
} netc_msix_vector_ctrl_t;

/*!
 * @brief NETC MSIX entry structure
 */
typedef struct _netc_msix_entry
{
    uint64_t msgAddr; /*!< Message address. */
    uint32_t msgData; /*!< Message data. */
    uint32_t control; /*!< Vector control, netc_msix_vector_ctrl_t. */
} netc_msix_entry_t;

/*! @brief METC Extension Transmit Buffer Descriptor Extension flags field */
typedef enum _netc_tx_ext_flags
{
    kNETC_TxExtVlanInsert = 0x1, /*!< Enable VLAN insert. */
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
    kNETC_TxExtOneStepTs = 0x1 << 1U, /*!< Enable one-step timestamp offload. */
#endif
    kNETC_TxExtTwoStepTs = 0x1 << 2U, /*!< Enable two-step timestamp offload. */
} netc_tx_ext_flags_t;

/*! @} */ // end of netc
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw
#endif
/*! @addtogroup netc_hw
 * @{
 */
/*! @brief Get SI information from netc_hw_si_idx_t. */
#define getSiInstance(si) ((uint8_t)((uint16_t)(si) >> 8U))          /*!< The ENETC instance of this SI. */
#define getSiNum(si)      ((uint8_t)(((uint16_t)(si) >> 4U) & 0xFU)) /*!< The SI number in the ENETC. */
#define getSiIdx(si)      ((uint8_t)((uint16_t)(si)&0xFU))           /*!< The actaul index in the netc_hw_si_idx_t. */

/*! @brief ENETC index enumerator */
typedef enum _netc_hw_enetc_idx
{
    kNETC_ENETC0, /*!< ENETC hardware 0 */
    kNETC_ENETC1, /*!< ENETC hardware 0 */
} netc_hw_enetc_idx_t;

/*! @brief SWITCH index enumerator */
typedef enum _netc_hw_switch_idx
{
    kNETC_SWITCH0, /*!< SWITCH hardware 0 */
} netc_hw_switch_idx_t;

/*! @brief Port Resource for the NETC module */
typedef enum _netc_hw_port_idx
{
    kNETC_ENETC0Port   = 0U, /*!< MAC port for ENETC0 */
    kNETC_ENETC1Port   = 0U, /*!< Pseudo MAC port for ENETC1 */
    kNETC_SWITCH0Port0 = 0U, /*!< MAC port0 for SWITCH */
    kNETC_SWITCH0Port1 = 1U, /*!< MAC port1 for SWITCH */
    kNETC_SWITCH0Port2 = 2U, /*!< MAC port2 for SWITCH */
    kNETC_SWITCH0Port3 = 3U, /*!< MAC port3 for SWITCH */
    kNETC_SWITCH0Port4 = 4U, /*!< Pseudo port4 for SWITCH */
} netc_hw_port_idx_t;

/*! @brief Traffic class enumerator */
typedef enum _netc_hw_tc_idx
{
    kNETC_TxTC0 = 0, /*!< Traffic class 0 */
    kNETC_TxTC1,     /*!< Traffic class 1 */
    kNETC_TxTC2,     /*!< Traffic class 2 */
    kNETC_TxTC3,     /*!< Traffic class 3 */
    kNETC_TxTC4,     /*!< Traffic class 4 */
    kNETC_TxTC5,     /*!< Traffic class 5 */
    kNETC_TxTC6,     /*!< Traffic class 6 */
    kNETC_TxTC7      /*!< Traffic class 7 */
} netc_hw_tc_idx_t;

/*! @brief Enumeration for the ENETC SI BDR identifier */
typedef enum _netc_hw_bdr_idx
{
    kNETC_BDR0 = 0,
    kNETC_BDR1,
    kNETC_BDR2,
    kNETC_BDR3,
    kNETC_BDR4,
    kNETC_BDR5,
    kNETC_BDR6,
    kNETC_BDR7,
    kNETC_BDR8,
    kNETC_BDR9,
    kNETC_BDR10,
    kNETC_BDR11,
    kNETC_BDR12,
    kNETC_BDR13
} netc_hw_bdr_idx_t;

/*! @brief Switch command BD ring index enumerator */
typedef enum _netc_hw_swt_cbdr_idx
{
    kNETC_SWTCBDR0 = 0U, /*!< Switch command BD ring 0 */
    kNETC_SWTCBDR1       /*!< Switch command BD ring 1 */
} netc_hw_swt_cbdr_idx_t;

/*! @brief Enumerator for ETM class queue identifier */
typedef enum _netc_hw_classs_queue_idx
{
    kNETC_ClassQueue0 = 0, /*!< ETM Class Queue 0 */
    kNETC_ClassQueue1,     /*!< ETM Class Queue 1 */
    kNETC_ClassQueue2,     /*!< ETM Class Queue 2 */
    kNETC_ClassQueue3,     /*!< ETM Class Queue 3 */
    kNETC_ClassQueue4,     /*!< ETM Class Queue 4 */
    kNETC_ClassQueue5,     /*!< ETM Class Queue 5 */
    kNETC_ClassQueue6,     /*!< ETM Class Queue 6 */
    kNETC_ClassQueue7      /*!< ETM Class Queue 7 */
} netc_hw_etm_class_queue_idx_t;

/*! @brief Enumerator for the ETM congestion group */
typedef enum _netc_hw_congestion_group_idx
{
    kNETC_CongGroup0 = 0,
    kNETC_CongGroup1
} netc_hw_congestion_group_idx_t;

/*! @brief Defines the MII/RGMII mode for data interface between the MAC and the PHY. */
typedef enum _netc_hw_mii_mode
{
    kNETC_XgmiiMode = 0U, /*!< XGMII mode for data interface. */
    kNETC_MiiMode   = 1U, /*!< MII mode for data interface. */
    kNETC_GmiiMode  = 2U, /*!< GMII mode for data interface. */
    kNETC_RmiiMode  = 3U, /*!< RMII mode for data interface. */
    kNETC_RgmiiMode = 4U, /*!< RGMII mode for data interface. */
} netc_hw_mii_mode_t;

/*! @brief Defines the speed for the *MII data interface. */
typedef enum _netc_hw_mii_speed
{
    kNETC_MiiSpeed10M   = 0U, /*!< Speed 10 Mbps. */
    kNETC_MiiSpeed100M  = 1U, /*!< Speed 100 Mbps. */
    kNETC_MiiSpeed1000M = 2U, /*!< Speed 1000 Mbps. */
    kNETC_MiiSpeed2500M = 3U, /*!< Speed 2500 Mbps. */
    kNETC_MiiSpeed5G    = 4U, /*!< Speed 5Gbps. */
    kNETC_MiiSpeed10G   = 5U, /*!< Speed 10Gbps Mbps. */
} netc_hw_mii_speed_t;

/*! @brief Defines the half or full duplex for the MII data interface. */
typedef enum _netc_hw_mii_duplex
{
    kNETC_MiiHalfDuplex = 0U, /*!< Half duplex mode. */
    kNETC_MiiFullDuplex       /*!< Full duplex mode. */
} netc_hw_mii_duplex_t;

/*! @brief NETC PSFP kc profile configuration, the key size (not include the spmp and portp) is up to 16 bytes */
typedef struct _netc_psfp_kc_profile
{
    bool etp : 1;   /*!< 2 Byte Ethertype field present in the key */
    bool sqtp : 1;  /*!< 1 Byte Sequence Tag present in the key */
    bool ipcpp : 1; /*!< inner VLAN header's PCP field present in the key */
    bool ividp : 1; /*!< inner VLAN ID present in the key */
    bool opcpp : 1; /*!< outer VLAN header's PCP field present in the key */
    bool ovidp : 1; /*!< outer VLAN ID present in the key */
    bool smacp : 1; /*!< 6 bytes of source MAC address present in the key */
    bool dmacp : 1; /*!<  6 bytes of destination MAC address present in the key */
    bool spmp : 1;  /*!< switch port masquerading flag present in the key */
    bool portp : 1; /*!< source port present in the key */
    bool valid : 1; /*!< Key Construction is valid */
    struct
    {
        uint8_t lbMask : 3;     /*!< Payload Last Byte Mask */
        uint8_t fbMask : 3;     /*!< Payload First Byte Mask */
        uint8_t byteOffset : 7; /*!< Payload Byte Offset where field extraction begins */
        uint8_t numBytes : 4;   /*!< Specify the size (numBytes + 1) of the payload key field */
        uint8_t pfp : 1;        /*!< Payload field Present */
    } payload[4];
} netc_isi_kc_rule_t;

/*! @brief NETC Vlan classification config */
typedef struct _netc_vlan_classify_config
{
    bool enableCustom1;        /*!< Enable/Disable custom0 ether type */
    uint16_t custom1EtherType; /*!< Ethertype */
    bool enableCustom2;        /*!< Enable/Disable custom0 ether type */
    uint16_t custom2EtherType; /*!< Ethertype */
    uint16_t preStandRTAGType; /*!< 802.1CB draft 2.0 R-TAG Ethertype value. PSRTAGETR. Only applicable for switch */
} netc_vlan_classify_config_t;

/*! @brief NETC Qos Classification profile file (vlan PCP/DEI to IPV/DR map) */
typedef struct _netc_qos_classify_profile
{
    uint8_t ipv[16]; /*!< Index is created from PCP (3 bits) + DEI (1 bit) field. Value is the mapped IPV for Qos. */
    uint8_t dr[16];  /*!< Index is created from PCP (3 bits) + DEI (1 bit) field. Value is the mapped DR for QoS. */
} netc_qos_classify_profile_t;

/*! @brief NETC Ingress Filter config */
typedef struct _netc_ipf_config
{
    bool l2DiscardMCSmac;      /*!< DOSL2CR. Discard received frames with Multicast SMAC address */
    bool l2DiscardSmacEquDmac; /*!< DOSL2CR. Discard received frames with SMAC = DMAC */
    bool l3DiscardSipEquDip;   /*!< DOSL3CR. Discard IPV3/IPV6 source address == destination address */
} netc_ipf_config_t;

/*! @} */ // end of netc_hw
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_enetc
#endif
/*! @addtogroup netc_hw_enetc
 * @{
 */
/*! @brief ENETC Port outer/inner VLAN tag */
typedef struct _netc_enetc_vlan_tag_t
{
    uint16_t pcp : 3;                 /*!< Priority code point */
    uint16_t dei : 1;                 /*!< Drop eligible indicator */
    uint16_t vid : 12;                /*!< VLAN identifier */
    netc_vlan_tpid_select_t tpid : 2; /*!< Tag protocol identifier */
} netc_enetc_vlan_tag_t;

/*! @brief PORT discard count statistic */
typedef struct _netc_enetc_discard_statistic
{
    uint32_t ingressDR[4];      /*!< Discard count for port ingress congestion different DR */
    uint32_t broadcastReject;   /*!< Broadcast frame drops count due to all SI enable broadcast reject */
    uint32_t smacPruning;       /*!< Frames discard count due to port MAC source address pruning */
    uint32_t unicastMacFilt;    /*!< Unicast frame discard count due to port MAC filtering */
    uint32_t multicastMacFilt;  /*!< Multicast frame discard count due to MAC filtering */
    uint32_t unicastVlanFilt;   /*!< Unicast frame discard count due to VLAN filtering */
    uint32_t multicastVlanFilt; /*!< Multicast frame discard count due to VLAN filtering */
    uint32_t boradcastVlanFilt; /*!< Broadcast frame discard count due to VLAN filtering */
} netc_enetc_port_discard_statistic_t;

/*! @brief ENETC Port outer/inner native VLAN config */
typedef struct _netc_enetc_native_vlan_config_t
{
    bool enUnderZeroVid; /*!< Enable use the port default VLAN VID when the VID in the packet's is zero */
    bool enUnderNoVlan;  /*!< Enable use the port default VLAN VID when the VLAN tag is not present */
    netc_enetc_vlan_tag_t
        vlanTag; /*!< Port native outer/inner VLAN tag, valid when enUnderZeroVid or enUnderNoVlan is true */
} netc_enetc_native_vlan_config_t;

/*! @brief ENETC parser configuration */
typedef struct _netc_enetc_parser_config_t
{
    bool disL3Checksum; /*!< Disable Layer 3 IPv4 Header checksum validation. */
    bool disL4Checksum; /*!< Disable Layer 4 TCP and UDP checksum validation. */
    struct
    {
        uint16_t etype; /*!< Custom Ethertype value. Upon detecting this ether type the associated code point will be
                           mapped to the parse summary as a Non IP code point. */
        bool en;        /*!< Enables the detection and mapping. */
        uint8_t cp;     /*!< This value is mapped to the parse summary as a Non IP code point. */
    } custEtype[4];
} netc_enetc_parser_config_t;

/*! @} */ // end of netc_hw_enetc
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_enetc
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port
#endif
/*! @addtogroup netc_hw_port
 * @{
 */

/*! @brief Port time gate scheduling gate list status */
typedef enum _netc_port_tgsl_status
{
    kNETC_OperListActive = 0x1U, /*!< Port operational gate control list is active. */
    kNETC_AdminListPending =
        0x2U /*!< Administrative gate control list is pending (configured but not installed yet). */
} netc_port_tgsl_status_t;

/*! @brief Port Tx/Rx discard counter in the datapath processing pipeline or bridge forwarding processing function*/
typedef enum _netc_port_discard_tpye
{
    kNETC_RxDiscard = 0U, /*!< Discarded frames in the receive port datapath processing pipeline. */
    kNETC_TxDiscard,      /*!< Discarded frames in the egress datapath processing pipeline, only for switch. */
    kNETC_BridgeDiscard   /*!< Discarded frames in the bridge forwarding processing function, only for switch. */
} netc_port_discard_tpye_t;

/*! @brief Defines Port TPID acceptance */
typedef enum _netc_port_tpidlist
{
    kNETC_OuterStanCvlan   = 0x1U, /*!< Accept outer Standard C-VLAN 0x8100. */
    kNETC_OuterStanSvlan   = 0x2U, /*!< Accept outer Standard S-VLAN 0x88A8. */
    kNETC_OuterCustomVlan1 = 0x4U, /*!< Accept outer Custom VLAN as defined by CVLANR1[ETYPE]. */
    kNETC_OuterCustomVlan2 = 0x8U, /*!< Accept outer Custom VLAN as defined by CVLANR2[ETYPE]. */
    kNETC_InnerStanCvlan   = 0x1U, /*!< Accept inner Standard C-VLAN 0x8100. */
    kNETC_InnerStanSvlan   = 0x2U, /*!< Accept inner Standard S-VLAN 0x88A8. */
    kNETC_InnerCustomVlan1 = 0x4U, /*!< Accept inner Custom VLAN as defined by CVLANR1[ETYPE]. */
    kNETC_InnerCustomVlan2 = 0x8U, /*!< Accept inner Custom VLAN as defined by CVLANR2[ETYPE]. */
} netc_port_tpidlist_t;

/*! @brief Defines port timestamp selection. */
typedef enum _netc_port_ts_select
{
    kNETC_SyncTime = 0U,  /*!< Synchronized time. */
    kNETC_FreeRunningTime /*!< Free running time. */
} netc_port_ts_select_t;

/*! @brief Port Qos mode */
typedef struct _netc_port_qos_mode
{
    uint8_t qosVlanMap : 4; /*!< Transmit QoS to VLAN PCP Mapping Profile index, only active on switch port */
    uint8_t vlanQosMap : 4; /*!< Receive VLAN PCP/DE to QoS Mapping Profile index, only active on switch port */
    uint8_t defaultIpv : 3; /*!< Port default IPV */
    uint8_t defaultDr : 2;  /*!< Port default DR */
    bool enVlanInfo : 1;    /*!< Enable use VLAN info to determine IPV and DR (base on VLANIPVMPaR0/1 and VLANDRMPaR) */
    bool vlanTagSelect : 1; /*!< True: Outer VLAN, False: Innner VLAN. Active when enVlanInfo is true */
} netc_port_qos_mode_t;

/*! @brief Port Parser config */
typedef struct _netc_port_parser_config
{
    uint8_t l2PloadCount : 5;   /*!< L2 payload fields size in bytes */
    bool enableL3Parser : 1;    /*!< Enable/Disable parser for L3 */
    uint8_t l3PayloadCount : 5; /*!< L3 payload fields size in bytes */
    bool enableL4Parser : 1;    /*!< Enable/Disable parser for L4 */
    uint8_t l4PayloadCount : 5; /*!< L4 payload fields size in bytes */
} netc_port_parser_config_t;

/*! @brief Port time gate config */
typedef struct _netc_port_tg_config
{
    uint16_t advOffset; /*!< Advance time offset in ns. */
    uint32_t holdSkew;  /*!< Hold-Skew in ns, not effective on ports connected to a pseudo-MAC */
} netc_port_tg_config_t;

/*! @brief Port MAC preemption mode */
typedef enum _netc_hw_preemption_mode
{
    kNETC_PreemptDisable = 0U, /*!< Frame preemption is not enabled */
    kNETC_PreemptOn64B,        /*!< Frame preemption is enabled, but transmit only preempts frames on 64B boundaries */
    kNETC_PreemptOn4B          /*!< Frame preemption is enabled, but transmit only preempts frames on 4B boundaries */
} netc_hw_preemption_mode_t;

/*! @brief Configuration for the Credit Based Shaped for port TC.
 *
 *  @note  The 802.1Qav bandwidth availability parameters is is calculated as follows:
 *          - idleSlope (bits) = portTxRate * bwWeight / 100
 *          - sendSlope (bits) = portTxRate * (100 - bwWeight) / 100
 *          - lowCredit (bits) = tcMaxFrameSize * (100 - bwWeight) / 100
 *          - hiCredit (bits) calculation formula depends on the traffic class, Please refer to the Reference manual.
 *          - hiCredit (credits) = (enetClockFrequency / portTxRate) * 100 * hiCredit (bits)
 */
typedef struct _netc_port_tc_cbs_config
{
    uint8_t bwWeight;  /*!< Percentage units of the port transmit rate and the credit-based shaper (range from 0 ~ 100),
                           the sum of all traffic class credit-based shaper's bandwidth cannot exceed 100 */
    uint32_t hiCredit; /*!< The maximum allowed accumulation of credits when conflicting transfers occur,
                          in credit units ((enetClockFrequency / portTxRate) * 100) */
} netc_port_tc_cbs_config_t;

/*! @brief Type of PDU/SDU (Protocol/Service Data Unit).
 *
 *  @note  Overhead values which adding to the transmitted frame of Length are specified by Port SDU config as follows:
 *          - PPDU = add rxPpduBco/txPpduBco + rxMacsecBco/txMacsecBco bytes
 *          - MPDU = add rxMacsecBco/txMacsecBco bytes
 *          - MSDU = minus 16B (12B MAC Header + 4B FCS)
 */
typedef enum _netc_tc_sdu_type
{
    kNETC_PDU = 0U, /*!< Physical Layer PDU, Preamble, IFG, SFD along with MPDU. Not supported if cut-through frames are
                       expected */
    kNETC_MPDU,     /*!< MAC PDU, MAC Header, MSDU and FCS */
    kNETC_MSDU /*!< MAC SDU, MPDU minus 12B MAC Header and 4B FCS. Not supported if cut-through frames are expected */
} netc_tc_sdu_type_t;

typedef struct _netc_port_tc_sdu_config
{
    bool enTxMaxSduCheck; /*!< Enable Tx Max SDU check for Store and Forward frames, the frame which greater than
                           maxSduSized wiil be discarded, Cut-Through frames will always perform Max SDU check */
    netc_tc_sdu_type_t
        sduType;          /*!< Specifies the type of PDU/SDU whose length is being validated as seen on the link */
    uint16_t maxSduSized; /*!< Transmit Maximum SDU size in bytes, the dequeued frame will be discarded when it SDU size
                             exceeds this value */
} netc_port_tc_sdu_config_t;

/*! @brief Configuration for the port Tx Traffic Class */
typedef struct _netc_port_tx_tc_config
{
    bool enPreemption : 1; /*!< Frames from traffic class are transmitted on the preemptable MAC, not supported on
                          internal port (ENETC 1 port and Switch port 4)*/
    bool enTcGate : 1; /*!< Enable the traffic class gate when no gate control list is operational, or when time gate
                            scheduling is disabled. */
    bool enableTsd : 1;    /*!< Enable Time Specific Departure traffic class, only applicable to ENETC */
    bool enableCbs : 1;    /*!< Enable Credit based shaper for traffic class  */
    netc_port_tc_sdu_config_t sduCfg;
    netc_port_tc_cbs_config_t cbsCfg; /*!< Configure transmit traffic class credit based shaper (PTC0CBSR0/PTC0CBSR1) if
                                  enableCbs set to ture */
} netc_port_tx_tc_config_t;

/*! @brief Switch or ENETC port Tx/Rx/Bridge discard statistic / reason */
typedef struct _netc_port_discard_statistic
{
    uint32_t count;   /*!< Count of discarded frames. PRXDCR, PTXDCR or BPDCR. */
    uint32_t reason0; /*!< Discard Reason. Find bit detail from PT/RXDCRR0 or BPDCRR0. */
    uint32_t reason1; /*!< Discard Reason. Find bit detail from PT/RXDCRR1 or BPDCRR1.*/
} netc_port_discard_statistic_t;

/*! @brief Port accepted Vlan classification config */
typedef struct _netc_port_vlan_classify_config
{
    uint8_t innerMask : 4; /*!< Bitmap identifying which TPIDs are acceptable as Inner VLAN tag. See PTAR */
    uint8_t outerMask : 4; /*!< Bitmap identifying which TPIDs are acceptable as Outter VLAN tag. See PTAR */
} netc_port_vlan_classify_config_t;

/*! @brief Port Qos Classification Config */
typedef struct _netc_port_qos_classify_configs
{
    uint8_t vlanQosMap : 4; /*!< Receive VLAN PCP/DE to QoS Mapping Profile index */
    uint8_t defaultIpv : 3; /*!< Port default IPV */
    uint8_t defaultDr : 2;  /*!< Port default DR */
    bool enVlanInfo : 1; /*!< Enable use VLAN info to determine IPV and DR ,base on VLAN to IPV map (VLANIPVMPaR0/1) and
                            VLAN to DR map (VLANDRMPaR) */
    bool vlanTagSelect : 1; /*!< True: Use received Outer VLAN, False: Use received Innner VLAN. Active when enVlanInfo
                               is true */
} netc_port_qos_classify_config_t;

/*! @brief Port Ingress Filter Config */
typedef struct _netc_port_ipf_config_t
{
    bool enL2Dos : 1;    /*!< Enable port L2 Ethernet DoS Protection */
    bool enL3Dos : 1;    /*!< Enable port L3 IP DoS Protection */
    bool enIPFTable : 1; /*!< Enable port IPF lookup */
} netc_port_ipf_config_t;

/*! @brief PSFP port config */
/*!
 * @brief Port ingress stream identification config
 *
 * @note The first stream identification find IS_EID has higher precedence value than the second, and the priority of
 *       the IS_EID found by the IPF is specified by the IPF entry RRR bit. The possible orderings are as follows
 *          - RRR = 00b : IPF > enKC0 > enKC1 > defaultISEID
 *          - RRR = 01b : enKC0 > IPF > enKC1 > defaultISEID
 *          - RRR = 10b : enKC0 > enKC1 > IPF > defaultISEID
 */
typedef struct _netc_port_psfp_isi_config
{
    uint16_t defaultISEID; /*!< Default Ingress Stream Entry ID, has lower precedence value than ISI entry and IPF entry
                              defined IS_EID. 0xFFFF means NULL */
    bool enKC1 : 1;        /*!< Enable do the second stream identification with key construction rule 1 or rule 3 */
    bool enKC0 : 1;        /*!< Enable do the first stream identification with key construction rule 0 or rule 2 */
    bool kcPair : 1; /*!< Indicates which Key Construction pair to use for this port, false - user pair0. true - use
                        pair1 only applicable for Switch */
} netc_port_psfp_isi_config;

typedef struct _netc_port_ethmac
{
    bool enableRevMii : 1;                /*!< Enable RevMII mode. */
    netc_port_ts_select_t txTsSelect : 1; /*!< Tx timestamp clock source. */
    bool isTsPointPhy : 1; /*!< True: Timestamp is captured based on PHY SFD detect pulse on Rx and Tx for 2-step timestamping.
                                False: Based on SFD detect at boundary of MAC merge layer and pins/protocol gaskets. */
    netc_hw_mii_mode_t miiMode : 3;       /*!< MII mode. */
    netc_hw_mii_speed_t miiSpeed : 3;     /*!< MII Speed. */
    netc_hw_mii_duplex_t miiDuplex : 1;   /*!< MII duplex. */
    bool enTxPad : 1; /*!< Enable ETH MAC Tx Padding, which will pad the frame to a minimum of 60 bytes and append 4
                         octets of FCS. */
    uint8_t rxMinFrameSize : 7; /*!< Receive Minimum Frame Length size in bytes, range in 18 ~ 64, received frames
                                   shorter than 18B are discarded silently. Both for express MAC and preemptable MAC. */
    uint16_t rxMaxFrameSize;    /*!< Receive Maximum Frame Length size in bytes, up to 2000, received frames that exceed
                                   this stated maximum are truncated. Both for express MAC and preemptable MAC. */
    bool enMergeVerify : 1; /*!< Enable verify the merged preemption frame, need to enable when preemptMode is not zero
                             */
    uint8_t mergeVerifyTime : 7; /*!< The nominal wait time between verification attempts in milliseconds, range in 1 ~
                                    128 */
    netc_hw_preemption_mode_t preemptMode : 2; /*!< When set to not zero, PMAC frames may be preempted by EMAC frames */
    bool rgmiiClkStop : 1; /*!< True: RGMII transmit clock is stoppable during low power idle. False: It's not stoppable. */
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
    bool enOneStepTS : 1;        /*!< Enable IEEE-1588 Single-Step timestamp */
    bool enChUpdate : 1;         /*!< Enable correction UDP checksum when enable Single-Step timestamp */
    uint16_t oneStepOffset : 10; /*!< Start offset from the beginning of a frame where the field to update is found
                                    (index to MS byte) */
#endif
    bool enableHalfDuplexFlowCtrl : 1; /*!< Enable/Disable half-duplex flow control. */
    uint16_t maxBackPressOn; /*!< Maximum amount of time backpressure can stay asserted before stopping to prevent excess
                                     defer on link partner, in byte times. */
    uint16_t minBackPressOff; /*!< Minimum amount of time backpressure will stay off after reaching the ON max, before
                                      backpressure can reassert after checking if icm_pause_notification is still or again
                                      asserted, in byte times. */
} netc_port_ethmac_t;

/*! @brief Defines the Port's Stream Gate Open Gate Check mode. */
typedef enum _netc_port_sg_ogc_mode
{
    kNETC_SGCheckSFD = 0U, /*!< Check whether frame SFD is within the open gate interval. */
    kNETC_SGCheckEntire    /*!< Check whether the entire frame is within the open gate interval. */
} netc_port_sg_ogc_mode_t;

/*! @brief Port common configuration */
typedef struct _netc_port_common
{
    netc_port_vlan_classify_config_t acceptTpid; /*!< Port acceptable VLAN tpid configure. */
    netc_port_ts_select_t rxTsSelect;            /*!< Eth MAC Rx or pseudo MAC Tx timestamp clock source */
    uint16_t pSpeed; /*!< Transmit Port Speed = 10Mbps * (pSpeed+1), Used by ETS, Qbu and to determine if cut-through is
                        permissable  */
    uint8_t rxMacsecBco; /*!< Port receive MACSec byte count overhead which due to MACSec encapsulation */
    uint8_t rxPpduBco;   /*!< Port receive PPDU Byte count overhead which includes IPG, SFD and Preamble */
    uint8_t txMacsecBco; /*!< Port transmit MACSec byte count overhead which due to MACSec encapsulation */
    uint8_t txPpduBco;   /*!< Port transmit PPDU Byte count overhead which includes IPG, SFD and Preamble */
#if (defined(FSL_FEATURE_NETC_HAS_PORT_FCSEA) && FSL_FEATURE_NETC_HAS_PORT_FCSEA)
    bool stompFcs : 1; /*!< Enable stomp the FCS error frame, not effective on ports connected to a pseudo-MAC, only
                          applies to device with ASIL-B safety requirements */
#endif
    netc_port_sg_ogc_mode_t ogcMode : 1; /*!< Stream Gate Open Gate Check mode, 0b is check whether SFD is within the
                         open gate interval, 1b is check whether the entire frame is within the open gate interval */
    uint32_t pDelay : 24;                /*!< Link propagation delay in ns */
    uint8_t macAddr[6]; /*!< Port MAC address, used for Switch egress frame modification action or ENETC SI0 primary MAC
                           address  */
    netc_port_qos_classify_config_t qosMode; /*!< Port Rx Qos Classification config */
    netc_port_ipf_config_t ipfCfg;           /*!< Port ingress port filter configuration */
    netc_port_tg_config_t timeGate;          /*!< Port Tx time gate config */
    netc_port_parser_config_t parser;        /*!< Port Rx Parser config */
} netc_port_common_t;

/*! @} */ // end of netc_hw_port
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_port_mac
#endif
/*! @addtogroup netc_hw_port_mac
 * @{
 */

/*! @brief Defines the Ethernet MAC physical port type. */
typedef enum _netc_port_phy_mac_type
{
    kNETC_ExpressMAC = 0U, /*!< The MAC which handles express traffic when frame preemption is enabled or handles all
                                traffic when frame preemption is disabled. */
    kNETC_PreemptableMAC   /*!< The MAC which handles preemptive traffic when frame preemption is enabled. */
} netc_port_phy_mac_type_t;

/*! @brief Definesthe state of the mac merge sublayer with respect to verification as defined in IEEE Std 802.3br-2016.
 */
typedef enum _netc_port_preemption_verify_status
{
    kNETC_VerifyDisable    = 0U, /*!< Verification is disabled */
    kNETC_VerifyInProgress = 2U, /*!< Verification is in progress */
    kNETC_VerifySuccess,         /*!<  Verification was successful */
    kNETC_VerifyFaile,           /*!<  Verification failed */
    kNETC_VerifyUndefined        /*!< Verification is in an undefined state */
} netc_port_preemption_verify_status_t;

/*! @brief Port MAC preemption Status */
typedef struct _netc_port_phy_mac_preemption_status
{
    bool mergeActive;                                  /*!< Transmit preemption is active or not */
    netc_port_preemption_verify_status_t verifyStatus; /*!< Transmit preemption is active or not */
} netc_port_phy_mac_preemption_status_t;

/*! @brief Ethernet MAC physical port traffic (Tx/Rx) statistics counters, when enable frame preemption, one physical
 *         MAC will be divided into a pMAC and a eMAC and statistics counters will also have two groups */
typedef struct _netc_port_phy_mac_traffic_statistic
{
    uint64_t totalOctet;             /*!< Count of MAC received/transmitted good/error Ethernet octets. */
    uint64_t validOctet;             /*!< Count of MAC received/transmitted good Ethernet octets. */
    uint64_t pauseFrame;             /*!< Count of MAC received/transmitted valid PAUSE frames. */
    uint64_t validFrame;             /*!< Count of MAC received/transmitted valid frames. */
    uint64_t vlanFrame;              /*!< Count of MAC received/transmitted valid VLAN tagged frames. */
    uint64_t unicastFrame;           /*!< Count of MAC received/transmitted valid unicast frames. */
    uint64_t multicastFrame;         /*!< Count of MAC received/transmitted valid multicast frames. */
    uint64_t boradcastFrame;         /*!< Count of MAC received/transmitted valid broadcast frames. */
    uint64_t totalPacket;            /*!< Count of MAC received/transmitted good/error packets. */
    uint64_t rxMinPacket;            /*!< Count of MAC received min to 63-octet packets. */
    uint64_t total64BPacket;         /*!< Count of MAC received/transmitted 64 octet packets. */
    uint64_t total65To127BPacket;    /*!< Count of MAC received/transmitted 65 to 127 octet packets. */
    uint64_t total128To255BPacket;   /*!< Count of MAC received/transmitted 128 to 255 octet packets. */
    uint64_t total256To511BPacket;   /*!< Count of MAC received/transmitted 256 to 511 octet packets. */
    uint64_t total511To1023BPacket;  /*!< Count of MAC received/transmitted 512 to 1023 octet packets. */
    uint64_t total1024To1522BPacket; /*!< Count of MAC received/transmitted 1024 to 1522 octet packets. */
    uint64_t total1523ToMaxBPacket;  /*!< Count of MAC received/transmitted 1523 to Max octet packets. */
    uint64_t controlPacket;          /*!< Count of MAC received/transmitted control packets. */
} netc_port_phy_mac_traffic_statistic_t;

/*! @brief Ethernet MAC physical port frame discard/errors status statistics counters, when enable frame preemption, one
 * physical MAC will be divided into a pMAC and a eMAC and statistics counters will also have two groups */
typedef struct _netc_port_phy_mac_discard_statistic
{
    uint64_t rxError;              /*!< Count of MAC received error frames. */
    uint64_t rxUndersized;         /*!< Count of MAC received undersized frames. */
    uint64_t rxOversized;          /*!< Count of MAC received oversized frames. */
    uint64_t rxErrorFCS;           /*!< Count of MAC received check sequence (FCS) error frames. */
    uint64_t rxFragment;           /*!< Count of MAC frames which is shorter than the MIN length and received with a
                                        wrong FCS/CRC. */
    uint64_t rxJabber;             /*!< Count of MAC frames which is larger than the MAX length and received with a
                                        wrong FCS/CRC. */
    uint64_t rxDiscard;            /*!< Count of MAC drops frame. */
    uint64_t rxDiscardNoTruncated; /*!< Count of MAC non-truncated drops frame. */
    uint64_t txErrorFCS;           /*!< Count of MAC transmitted bad FCS frames. */
    uint64_t txUndersized;         /*!< Count of MAC transmitted less than 64B with good FCS frames. */
} netc_port_phy_mac_discard_statistic_t;

/*! @brief Ethernet physical MAC port preemption (Tx/Rx) related statistics counters */
typedef struct _netc_port_phy_mac_preemption_statistic
{
    uint32_t rxReassembledFrame; /*!< Count of MAC frames that were successfully reassembled and delivered to
                                      the MAC. */
    uint32_t rxReassembledError; /*!< Count of MAC frames with reassembly errors. */
    uint32_t rxMPacket;          /*!< Count of the number of additional mPackets received due to preemption. */
    uint32_t rxSMDError;         /*!< Count of received MAC frames / MAC frame fragments rejected due to unknown SMD. */
    uint32_t txPreemptionReq;    /*!< Count of the number of tx preemption HOLD requests. */
    uint32_t txMPacket;          /*!< Count of the number of additional mPackets transmitted due to preemption. */
} netc_port_phy_mac_preemption_statistic_t;

/*! @brief Ethernet pseudo MAC port traffic (Tx/Rx) statistics counters */
typedef struct _netc_port_pseudo_mac_traffic_statistic
{
    uint64_t totalOctet;     /*!< Count of MAC received/transmitted octets. */
    uint64_t unicastFrame;   /*!< Count of MAC received/transmitted unicast frames. */
    uint64_t multicastFrame; /*!< Count of MAC received/transmitted multicast frames. */
    uint64_t boradcastFrame; /*!< Count of MAC received/transmitted broadcast frames . */
} netc_port_pseudo_mac_traffic_statistic_t;

/*! @} */ // end of netc_hw_port_mac
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_port_mac
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_table
#endif
/*! @addtogroup netc_hw_table
 * @{
 */

/*! @brief Table index */
typedef enum _netc_tb_index
{
    kNETC_TGSTable   = 5U,  /*!< Time Gate Scheduling table index */
    kNETC_RPTable    = 10U, /*!< Rate Policer table index */
    kNETC_IPFTable   = 13U, /*!< Ingress Port filter table index */
    kNETC_FDBTable   = 15U, /*!< FDB table index */
    kNETC_L2MCFTable = 16U, /*!< L2 IPV4 Multicast Filter table index */
    kNETC_VFTable    = 18U, /*!< VLAN Filter table index */
    kNETC_ECQTable   = 22U, /*!< ETM Class Queue table index */
    kNETC_ECSTable   = 23U, /*!< ETM Class Scheduler table index */
    kNETC_ISITable   = 30U, /*!< Ingress Stream Identification table index */
    kNETC_ISTable    = 31U, /*!< Ingress Stream table index */
    kNETC_ISFTable   = 32U, /*!< Ingress Stream Filter table index */
    kNETC_ETTable    = 33U, /*!< Egress Treatment table index */
    kNETC_ISGTable   = 34U, /*!< Ingress Sequence Generation table index */
    kNETC_ESRTable   = 35U, /*!< Egress Sequence Recovery table index */
    kNETC_SGITable   = 36U, /*!< Stream Gate Instance table index */
    kNETC_SGCLTable  = 37U, /*!< Stream Gate Control List table index */
    kNETC_ISCTable   = 38U, /*!< Ingress Stream Count table index */
    kNETC_ECTable    = 39U, /*!< Egress Count table index */
    kNETC_FMTable    = 40U, /*!< Frame Modification table index */
    kNETC_BPTable    = 41U, /*!< Buffer Pool table index */
    kNETC_SBPTable   = 42U, /*!< Shared Buffer Pool table index */
    kNETC_ECGTable   = 43U, /*!< ETM Class Group table index */
    kNETC_FMDTable   = 44U  /*!< Frame Modification Data table index */
} netc_tb_index_t;

/*! @brief Table management command operations */
typedef enum _netc_tb_cmd
{
    kNETC_DeleteEntry         = 0x1U, /*!< Delete operation */
    kNETC_UpdateEntry         = 0x2U, /*!< Update operation */
    kNETC_QueryEntry          = 0x4U, /*!< Query operation */
    kNETC_QueryAndDeleteEntry = 0x5U, /*!< Query operation followed by a delete operation */
    kNETC_QueryAndUpdateEntry = 0x6U, /*!< Query operation followed by a update operation */
    kNETC_AddEntry            = 0x8U, /*!< Add operation */
    kNETC_AddOrUpdateEntry = 0xAU, /*!< If the entry exists, is update operation, if not exist, is the Add operation*/
    kNETC_AddAndQueryEntry = 0xCU, /*!< Add operation followed by a query operation */
    kNETC_AddQueryAndUpdateEntry =
        0xEU /*!< Add operation followed by a query operation, Then, if the entry existed
                  prior to the Add operation of this command, the Update operation will be performed. */
} netc_tb_cmd_t;

/*! @brief Table Access Method */
typedef enum _netc_tb_access_mode
{
    kNETC_EntryIDMatch = 0U, /*!< Entry ID Match */
    kNETC_ExactKeyMatch,     /*!< Exact Match Key Element Match */
    kNETC_Search,            /*!< Search with search criteria*/
    kNETC_TernaryKeyMatch    /*!< Ternary Match Key Element Match */
} netc_tb_access_mode_t;

/*! @brief NTMP version */
typedef enum _netc_cbd_version
{
    kNETC_NtmpV1_0 = 0U, /*!< NTMP Version 1.0 */
    kNETC_NtmpV2_0       /*!< NTMP Version 2.0 */
} netc_cbd_version_t;

/*! @brief Table command response error status */
typedef enum _netc_cmd_error
{
    /* Version 1.0 NTMP Table error status */
    kNETC_FormatError = 0x1U, /*!< Format error : 1. Illegal class or command. 2. Invalid SF bit setting. 3. LENGTH is
                                 zero for long format. 4. LENGTH is too small for buffer size. */
    kNETC_SizeError = 0x2U,   /*!< Size error : 1. Invalid table index, out of range. 2. Table overflow, no additional
                                 entries available. */
    kNETC_AccessError    = 0x4U, /*!< Access violation error, the entity is not allowed to perform the task requested */
    kNETC_ClassError     = 0x8U, /*!< Class specific error */
    kNETC_IntegrityError = 0x10U, /*!< Integrity error, the command did not execute due to a data integrity error (ECC
                                     on internal memory or AXI read/write error) */
    /* Version 2.0 NTMP Table Generic error status */
    kNETC_InvTableID         = 0x80U, /*!< Invalid table ID */
    kNETC_InvAccMethod       = 0x81U, /*!< Invalid Access method */
    kNETC_TableIdxOutRange   = 0x82U, /*!< Table index out of range */
    kNETC_DBNotEnough        = 0x83U, /*!< Request data buffer size or response data buffer size is not sufficient */
    kNETC_InvCmd             = 0x84U, /*!< Invalid command */
    kNETC_ReqDBError         = 0x85U, /*!< Request Data buffer error */
    kNETC_MultiBitError      = 0x86U, /*!< Multi-bit ECC or parity error observed during command processing */
    kNETC_HashEntryLimit     = 0x87U, /*!< Exceeded hash entry limit */
    kNETC_HashChainLimit     = 0x88U, /*!< Exceeded maximum hash collision chain limit and the CAM if present is full */
    kNETC_InvHWGenEntryID    = 0x89U, /*!< Invalid ENTRY_ID for ENTRY_ID generated by hardware */
    kNETC_SrchResDBNotEnough = 0x8AU, /*!< Search command filled the response data buffer before completing the
                                           command */
    kNETC_CmdIdxTableWithITM   = 0x8BU, /*!< Command for index table before OSR[ITM_STATE]=0 */
    kNETC_InvQueryAction       = 0x8CU, /*!< Invalid Query action */
    kNETC_InvTableAccPrivilege = 0x8DU, /*!< Invalid table access privilege */
    kNETC_ReadSysBusErr        = 0x8EU, /*!< System Bus Read Error */
    kNETC_WriteSysBusErr       = 0x8FU, /*!< System Bus Write Error */
    kNETC_ClientErr            = 0x90U, /*!< Client encountered a fault */
    /* Time Gate Scheduling Table error status */
    kNETC_TGSCmdIssue        = 0xD0U,  /*!< Command issued when time gating function is disabled for the port. */
    kNETC_TGSUpdateExistList = 0xD1U,  /*!< Update action attempted on an existing admin gate control list. (should
                                      delete   admin gate control list first before creating a new admin list) */
    kNETC_TGSUpdateOverLength = 0xD2U, /*!< Update action attempted exceeds TGSTCAPR[MAX_GCL_LEN] */
    kNETC_TGSUpdateOverSize   = 0xD3U, /*!< Update action attempted exceeds TGSTCAPR[NUM_WORDS]. */
    kNETC_TGSEntryNotEnough   = 0xD4U, /*!< Insufficient resources to perform the requested operation (not enough free
                                          time gate list entries) */
    kNETC_TGSUpdateNSList = 0xD5U,     /*!< Update action attempted with ADMIN_CYCLE_TIME, ADMIN_TIME_INTERVAL_GE_i or
                        truncated ADMIN_TIME_INTERVAL_GE_n due ADMIN_CYCLE_TIME specified is not sufficient to transmit 64
                        byte of frame data + header overhead. */
    kNETC_TGSUpdateEarlierStartTime = 0xD6U, /*!< Update action attempted with ADMIN_BASE_TIME specified s more than one
                                                second in the past from tcs advance time. */
    kNETC_TGSUpdateOverflowCycle = 0xD7U,   /*!< Update action attempted with ADMIN_CYCLE_TIME + ADMIN_CYCLE_TIME_EXT is
                                           greater than 2^32-1. */
    kNETC_TGSQueryBeforeListActive = 0xD8U, /*!< Query action issued when config change occurred. Retry query.*/
    kNETC_TGSUpdateInvGateValue = 0xD9U, /*!< Update action attempted with ADMIN_HR_CB_GE_i set to an invalid value */
    /* Rate Policer Table error status */
    kNETC_RPSDUTypeOutRange = 0x120U, /*!< SDU_TYPE specified in entry CFGE_DATA is out of range */
    /* Ingress Port Filter Table error status */
    kNETC_IPFInvHR = 0x150U,           /*!< HR value not valid. Only checked if command issued from the Switch
                                          and FLTFA=0x2 or FLTFA=0x3 */
    kNETC_IPFEntryNotFit     = 0x151U, /*!< Entry being added does not fit in table */
    kNETC_IPFWithoutSTSE     = 0x152U, /*!< CFGE_DATA update without STSE_DATA update */
    kNETC_IPFInvRPP          = 0x154U, /*!< RPR set to a reserved value. Only checked if FLTA=0x2. */
    kNETC_IPFFLTATGTOutRange = 0x155U, /*!< FLTA_TGT is outside valid range and not NULL. Only checked if FLTA>0x0 */
    kNETC_IPFInvSwtFLTA      = 0x156U, /*!< FLTA=0x3 when command issued from the Switch. */
    kNETC_IPFInvEnetcFLTA    = 0x157U, /*!< FLTFA>0x1 when command issued from an ENETC PF. */
    /* FDB Table error status */
    kNETC_FDBReachPortLimit = 0x171U, /*!< Failed to add or update and entry because the Port BPCR[DYN_LIMIT] has
                                           been reached */
    kNETC_FDBReachSwtLimit = 0x172U,  /*!< Failed to add entry because the Switch FDBHTMCR[DYN_LIMIT] has been
                                           reached. */
    kNETC_FDBInvEPORT      = 0x173U,  /*!< EPORT value not valid. Only checked if (OETEID=0x1 OR CTD=0x1) */
    kNETC_FDBETEIDOutRange = 0x174U,  /*!< ET_EID is out of range and not NULL. Only checked if OETEID>0x0 */
    kNETC_FDBParityErr     = 0x175U,  /*!< Parity error encountered when adding guaranteed entry */
    /* L2 IPv4 Multicast Filter Table error status */
    kNETC_L2MCFInvEPORT      = 0x181U, /*!< EPORT value not valid. Only checked if (OETEID=0x1 OR CTD=0x1) */
    kNETC_L2MCFETEIDOutRange = 0x182U, /*!< ET_EID is not NULL or within the valid range. Only checked if OETEID>0x0. */
    kNETC_L2MCFInvKEYTYPE    = 0x183U, /*!< KEY_TYPE value not valid */
    /* VLAN Filter Table error status */
    kNETC_VFBASEETEIDOutRange = 0x1A0U, /*!< BASE_ET_EID is out of range or MLO is not valid. */
    /* ETM Class Queue Table error status */
    kNETC_ECQCQ2CGMAPOutRange = 0x1E0U, /*!< CQ2CG_MAP value out-of-range in update command. */
    /* Ingress Stream Identification Table error status */
    kNETC_ISIPortIDOutRange = 0x260U, /*!< Port ID specified in KEYE_DATA is out of range. */
    kNETC_ISIInvISEID       = 0x261U, /*!< IS_EID in invalid. */
    /* Ingress Stream Table error status */
    kNETC_ISInvOpt = 0x270U,   /*!< Option specified in one or more of the following fields is not valid – FA, CTD or
                                       ISQA, SDU_TYPE. */
    kNETC_ISInvID = 0x271U,    /*!< One or more of following : 1. Entry IDs are not in valid range or Entry ID is not
                                  Null. 2. Check valid ranges specified for these Entry IDs in Ingress Stream table entry –
                                  RP_EID, SGI_EID, ISQ_EID, ET_EID or EPORT. 3. ET_EID is checked if (FA =010b .. 101b) &
                                  (OETEID!=0). 4. EPORT is checked if (FA = 010b .. 101b) & (OETEID= 0x1 OR CTD= 0x1). 5.
                                  HR is chked if FA = 001b, 100b, or 101b. HR specified cannot be 0x0*/
    kNETC_ISInvFMEID = 0x272U, /*!< FM_EID format or index is out of range : 1. FM_EID format option type is invalid. 2.
                                  FM_EID format is option 1 and the Index is out of range and not Null, or FM_EID format
                                  is option 2 and VUDA or SQTA is out of range.*/
    /* Ingress Stream Filter Table error status */
    kNETC_ISFInvISEID = 0x280U, /*!< IS_EID in KEYE_DATA is invalid. */
    kNETC_ISFInvCFGE = 0x281U, /*!< Any of the following in CFGE_DATA is invalid : 1. One or more of following Entry IDs
                                are not in valid range or Entry ID specified is not Null. Checks are performed for
                                following Entry IDs CFGE DATA – RP_EID, SGI_EID, ISC_EID. 2. SDU_TYPE is invalid */
    /* Egress Treatment Table error status */
    kNETC_ETInvOpt = 0x290U, /*!< Command option specified is invalid or not supported. ESQA is not 00 or 10 (others are
                                reserved), or ECA > 1 (reserved). */
    kNETC_ETInvFMEID = 0x291U, /*!< FM_EID format or index is out of range. Check performed is as follows : 1. EFM_EID
                                  format option type is invalid, or EFM_EID format is option 1 and the Index is out of
                                  range and not Null, or EFM_EID format is option 2 and VUDA or SQTA is out of range
                                  . 2. the Egress Counter Table index EC_EID is out of range. 3. The Egress Sequence
                                  Actions Target Entry ID ESQA_TGT_EID is out of range*/
    /* Ingress Sequence Generation Table error status */
    kNETC_ISGInvQSTAG = 0x2A0U, /*!< SQ_TAG specified is not valid */
    /* Stream Gate Instance Table error status */
    kNETC_SGISGCLEIDOutRange = 0x2C0U,  /*!< SGCL_EID specified in out of range for Add or Update operation. */
    kNETC_SGIInvSDUTYPE      = 0x2C1U,  /*!< SDU_TYPE is specified is invalid for Add or Update operation. */
    kNETC_SGISGCLEIDNotAlloc = 0x2C2U,  /*!< Either the SGCL_EID specified as admin gate control list in Add or Update
                                      operation has not been allocated or SGCL_EID is not the first entry in gate control
                                      list or the reference count in SGCL entry is not 0. */
    kNETC_SGIInvSGCLEID       = 0x2C3U, /*!< SGCL_EID specified for Update operation is in invalid.  */
    kNETC_SGIInvADMINBASETIME = 0x2C4U, /*!< ADMIN_BASE_TIME specified for Add or Update operation is more than 2^30ns
                                        in the past. */
    kNETC_SGIInvCYCLETIME = 0x2C5U,     /*!< Cumulated time value of CYCLE_TIME in Stream gate Control list plus
                                            CYCLE_TIME_EXT specified in Add or Update operation is >=2^30ns or
                                            CYCLE_TIME specified is 0. */
    /* Stream Gate Control List Table error status */
    kNETC_SGCLOverLength = 0x2D0U,       /*!< Number words required for the LIST_LENGTH specified for the Add operation
                                            exceeds the number of words allocated for SGCL table */
    kNETC_SGCLTimeIntervalZero = 0x2D1U, /*!< TIME_INTERVAL_GE_N specified in Add operation is 0. Note that upper
                            2 bits of TIME_INTERVAL_GE_N are ignored, TIME_INTERVAL_GE_N[29:0] must not be 0. */
    kNETC_SGCLTimeIntervalOverflow = 0x2D2U, /*!< Cumulated time value of TIME_INTERVAL_GE_N[29:0] for the gate list
                                                specified in Add operation is >= 2^30ns. */
    /* Frame Modification Table error status */
    kNETC_FMInvEMEID    = 0x300U, /*!< FM_EID format is invalid */
    kNETC_FMOptOutRange = 0x301U, /*!< Following fields specified are out of range - MAC_HDR_ACT, VLAN_HDR_ACT, SQT_ACT,
                                     OUTER_PCP_DEI_ACT, PLD_ACT. */
    kNETC_FMFMDOutRange = 0x302U, /*!< FMD_EID,FMD_BYTES specified is out of range. When FMD_EID is not set to Null,
                                     valid range is FMD_EID[15:0]*24 + FMD_BYTES <= (FMDITCAPR[NUM_WORDS]*24).*/
    /* Buffer Pool Table error status */
    kNETC_BPSBPEIDOutRange = 0x310U, /*!< SBP_EN is 1 and SBP_EID value is out-of-range in update command */
} netc_cmd_error_t;

/*! @brief The Switch/SI command BD data structure */
typedef union _netc_cmd_bd
{
    struct
    {
        uint64_t addr; /*!< The request and response data buffers address */
        struct
        {
            uint32_t resLength : 20; /*!< The length of the Response Data Buffer */
            uint32_t reqLength : 12; /*!< The length of the Request Data Buffer */
        };
        struct
        {
            netc_tb_cmd_t cmd : 4; /*!< Access table entry command, see @ref netc_tb_cmd_t . */
            uint32_t : 8;
            netc_tb_access_mode_t accessType : 2; /*!< Access table entry method, see @ref netc_tb_access_mode_t. */
            uint32_t : 2;                         /*!< RSS Hash high field value. */
            netc_tb_index_t tableId : 8;
            uint32_t version : 6;   /*!< Protocol Version. */
            uint32_t enCompInt : 1; /*!< Command Completion Interrupt. */
            uint32_t resReady : 1;  /*!< Response Ready. */
        };
        uint32_t reserved[3];
        struct
        {
            uint32_t : 15;
            uint32_t npf : 1; /*!< NTMP Protocol Format. */
            uint32_t : 16;
        };
    } req;
    struct
    {
        uint32_t reserved1[3];
        struct
        {
            uint32_t numMatched : 16; /*!< Number of Entries Matched. */
            uint32_t error : 12;      /*!< Error status. */
            uint32_t : 3;
            uint32_t resReady : 1; /*!< Response Ready. */
        };
        uint32_t reserved2[4];
    } resp;
    struct
    {
        uint64_t addr; /*!< Data. */
        uint32_t : 31;
        uint32_t en : 1; /*!< Enable entry. */
        uint32_t reserved[2];
        uint32_t siBitMap : 16; /*!< Station interfaces 15-0 for which this filter applies. */
        uint32_t : 16;
        uint32_t index : 16;  /*!< The index refers to an entry location within a table. */
        uint32_t length : 16; /*!< NA */
        uint32_t cmd : 8;     /*!< Command. */
        uint32_t class : 8;   /*!< Class of command. */
        uint32_t : 8;
        uint32_t status : 6; /*!< Status. */
        uint32_t ci : 1;     /*!< Completion interrupt. */
        uint32_t sf : 1;     /*!< Short format. */
    } generic;
} netc_cmd_bd_t;

/*! @brief Configuration for the Switch/SI command BD Ring Configuration */
typedef struct _netc_cmd_bdr_config
{
    netc_cmd_bd_t *bdBase; /*!< BDR base address which shall be 128 bytes aligned */
    uint16_t bdLength;     /*!< Size of BD ring which shall be multiple of 8 BD */
    bool enCompInt;        /*!< Enable/Disable command BD completion interrupt */
} netc_cmd_bdr_config_t;

/*! @brief The Switch/SI command BD ring handle data structure */
typedef struct _netc_cmd_bdr
{
    netc_cmd_bd_t *bdBase;  /*!< BDR base address which shall be 128 bytes aligned */
    uint16_t bdLength;      /*!< Size of BD ring */
    uint16_t producerIndex; /*!< Current index for execution. */
    uint16_t cleanIndex;    /*!< Current index for cleaning. */
    bool bdrEnable;         /*!< Current command BD ring is enable or not. */
} netc_cmd_bdr_t;

/*! @brief Table request data buffer common header */
typedef struct _netc_tb_common_header
{
    uint32_t updateActions : 16; /*!< Update Actions */
    uint32_t : 8;
    uint32_t queryActions : 4; /*!< Query Actions */
    uint32_t : 4;
} netc_tb_common_header_t;

/*!
 * @brief Frame Modification VLAN Update/Delete Action
 * @note  Misconfiguration error if replace or delete action is specified and if VLAN tag is not present in frame.
 */
typedef enum _netc_fm_vlan_ud_act
{
    kNETC_NoUDVlanAction = 0U, /*!< No Update/Delete VLAN action */
    kNETC_ReplVlanPcpAndDei, /*!< Replace outer VLAN's PCP/DEI based on the port's PPCPDEIMR. The tag's original VID and
                                TPID are preserved */
    kNETC_DelVlan            /*!< Delete outer VLAN Tag */

} netc_fm_vlan_ud_act_t;

/*!
 * @brief Frame Modification Sequence Tag Action
 * @note Must be set to 000b for Ingress frame modification, otherwise misconfiguration error..
 */
typedef enum _netc_fm_sqt_act
{
    kNETC_NoSqtAction = 0U, /*!< No SQT action */
    kNETC_ReomveRTag /*!< Remove R-TAG/draft 2.0 R-TAG/HSR tag, If R-TAG/HSR tag not present, misconfiguration error. */
} netc_fm_sqt_act_t;

/*!
 * @brief Frame Modification VLAN Add/Replace Action
 * @note  For ingress frame modificaion with 00b or 01b, use the ingress port to select PCP and DEI from the Bridge port
 *        default VLAN register (BPDVR). For egress frame modification with 00b or 01b, use the internal QoS associated
 *        with the frame (IPV, DR) to access the QoS to PCP mapping profile (PQOSMR[QVMP] , QOSVLANMPaR0/1/2/3) to set
 *        the new PCP value. Use internal DR associated with frame to access the DR to DEI mapping profile
 *        (PPCPDEIMR[DRnDEI]) to set the new DEI value.
 */
typedef enum _netc_fm_vlan_ar_act
{
    kNETC_AddCVlanPcpAndDei = 0U, /*!< Add outer VLAN with VID and PCP/DEI updated as described above. TPID=0x8100 */
    kNETC_AddSVlanPcpAndDei,      /*!< Add outer VLAN with VID and PCP/DEI updated as described above. TPID=0x88A8 */
    kNETC_ReplVidOnly,            /*!< Replace VLAN with VID. The tag's original PCP, DEI and TPID are preserved */
    kNETC_ReplVidPcpAndDei        /*!< Replace VLAN with VID and PCP/DEI updated by port's PPCPDEIMR. The tag's original
                                 TPID is preserved */

} netc_fm_vlan_ar_act_t;

/*!
 * @brief Frame Modification Entry ID encode options
 * @note sqta should be netc_fm_sqt_act_t type, vuda should be netc_fm_vlan_ud_act_t type and vara should be
 *       netc_fm_vlan_ar_act_t type.
 */
#define NETC_FD_EID_ENCODE_OPTION_0(entryId)    ((uint32_t)(entryId)&0xFFFU)
#define NETC_FD_EID_ENCODE_OPTION_1(sqta, vuda) ((((uint32_t)(sqta)&0x7U) << 2U) | ((uint32_t)(vuda)&0x3U) | 0x2000U)
#define NETC_FD_EID_ENCODE_OPTION_2(vara, vid)  ((((uint32_t)(vara)&0x3U) << 12U) | ((uint32_t)(vid)&0xFFFU) | 0x4000U)

/*!
 * @brief Define FDB/L2MCF/IS table entry access the primary Egress Treatment table entry group mode
 * @note  The FDB/L2 IPv4 Multicast filter table has precedence over any assignment made via the Ingress Stream table.
 *        For Mulit port mode, the index to access the Egress Treatment table is computed by adding an offset to the
 *        base index of the Egress Treatment group. That offset is derived from the applicability bitmap as follows:
 *        starting from the lowest significant bit of the bitmap, the first encountered bit set to 1, corresponds to
 *        offset 0, and so on. This continues till the destination port location in the bitmap is reached
 */
typedef enum _netc_tb_eteid_access_mode
{
    kNETC_NoETAccess = 0x0U,       /*!< No Egress Treatment table access */
    kNETC_SinglePortETAccess,      /*!< Only frame sent to a special port (define in ePort) can access a single Egress
                                    Treatment table entry, the applicability bitmap specified by FDB/L2MCF/IS ePort field
                                    */
    kNETC_MulitPortPackedETAccess, /*!< Only frames sent to a special set of ports (ports set to 1 in ePortBitmap) can
                                      access the Egress Treatment table, the applicability bitmap = IS ePortBitmap field
                                      or FDB/L2MCF portBitmap field */
    kNETC_MulitPortAbsETAccess     /*!< Frames sent to all of ports can access the Egress Treatment table, means the
                                      applicability bitmap is set with 1 for all ports */
} netc_tb_eteid_access_mode_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Port Filter Table
#endif

/*! @brief Ingress Port Filter Table Update Actions */
typedef enum _netc_tb_ipf_update_action
{
    kNETC_IPFCfgEUpdate = 0x1U, /*!< Configuration Element Update */
    kNETC_IPFStsEUpdate = 0x2U  /*!< Statistics Element Update */
} netc_tb_ipf_update_action_t;

/*! @brief Ingress Port Filter frame attribute mask */
typedef enum _netc_tb_ipf_attr_mask
{
    kNETC_IPFSwtPortMasMask = 0x1U,   /*!<  Switch port masquerading Mask */
    kNETC_IPFEthernetMask   = 0x2U,   /*!< Ethernet type Mask */
    kNETC_IPFOuterVlanMask  = 0x4U,   /*!< Outer VLAN Mask */
    kNETC_IPFInnerVlanMask  = 0x8U,   /*!< Inner VLAN Mask */
    kNETC_IPFSeqTagMask     = 0x70U,  /*!< Sequence Tag Code Mask */
    kNETC_IPFIpHeaderMask   = 0x80U,  /*!< IP Header Mask */
    kNETC_IPFIpVersionMask  = 0x100U, /*!< IP Version Mask */
    kNETC_IPFIpExtMask      = 0x200U, /*!< IPv4 option / IPv6 extension Mask */
    kNETC_IPFL4HeaderMask   = 0x400U, /*!< L4 Code Mask */
    kNETC_IPFWakeOnLanMask  = 0x800U  /*!< Wake-on-LAN Magic Packet Mask */
} netc_tb_ipf_attr_mask_t;

/*! @brief Ingress Port Filter frame attribute Sequence Tag Code */
typedef enum _netc_tb_ipf_seq_tag
{
    kNETC_IPFNoRtag = 0x0U, /*!<  R-TAG/HSR tag is not present */
    kNETC_IPFDraftRtag,     /*!< 802.1CB draft 2.0 R-TAG is present */
    kNETC_IPFRtag,          /*!< 802.1CB R-TAG is present */
    kNETC_IPFHsrTag         /*!< HSR Tag is present */
} netc_tb_ipf_seq_tag_t;

/*! @brief Ingress Port Filter frame attribute L4 Header Code */
typedef enum _netc_tb_ipf_l4_header
{
    kNETC_IPFOtherL4 =
        0x0U,     /*!< The L4 Header is considered as other L4 if it is not one of the following L4 Headers */
    kNETC_IPFTcp, /*!< TCP header is present */
    kNETC_IPFUdp, /*!< UDP header is present */
    kNETC_IPFSctp /*!< SCTP header is present */
} netc_tb_ipf_l4_header_t;

/*! @brief Ingress Port Filter key element */
typedef struct _netc_tb_ipf_keye
{
    uint16_t precedence; /*!< Precedence value of an entry*/
    uint8_t res0[6];
    struct
    {
        uint16_t swtPortMas : 1; /*!< Switch port masquerading, applicable only if the incoming port is designated
                                    as a switch management port */
        uint16_t ethernet : 1;   /*!< Ethernet type Present */
        uint16_t outerVlan : 1;  /*!< Outer VLAN Present */
        uint16_t innerVlan : 1;  /*!< Inner VLAN Present */
        netc_tb_ipf_seq_tag_t seqTag : 3;     /*!<  Sequence Tag Code */
        uint16_t ipHeader : 1;                /*!<  IP Header Present */
        uint16_t ipVersion : 1;               /*!< 0b = IPv4, 1b = IPv6 */
        uint16_t ipExt : 1;                   /*!< IPv4 option / IPv6 extension present */
        netc_tb_ipf_l4_header_t l4Header : 2; /*!< L4 Header code */
        uint16_t wakeOnLan : 1;               /*!< Wake-on-LAN Magic Packet Present */
        uint16_t : 3;
    } frameAttr;            /*!< Frame Attribute flags */
    uint16_t frameAttrMask; /*!< Frame attribute mask, set with OR of @ref netc_tb_ipf_attr_mask_t */
    uint16_t dscp : 6;      /*!< Differentiated Services Code Point */
    uint16_t dscpMask : 6;  /*!< Differentiated Services Code Point Mask */
    uint16_t res1 : 4;
    uint16_t srcPort : 5;     /*!< Source Port ID */
    uint16_t srcPortMask : 5; /*!< Source Port ID Mask */
    uint16_t res2 : 6;
    uint16_t outerVlanTCI;     /*!< Outer VLAN Tag Control Information */
    uint16_t outerVlanTCIMask; /*!< Outer VLAN Tag Control Information Mask */
    uint8_t dmac[6];           /*!< Destination MAC Address */
    uint8_t dmacMask[6];       /*!< Destination MAC Address Mask */
    uint8_t smac[6];           /*!< Source MAC Address */
    uint8_t smacMask[6];       /*!< Source MAC Address Mask */
    uint16_t innerVlanTCI;     /*!< Inner VLAN Tag Control Information */
    uint16_t innerVlanTCIMask; /*!< Inner VLAN Tag Control Information Mask */
    uint16_t etherType;        /*!< 2-byte EtherType */
    uint16_t etherTypeMask;    /*!< EtherType Mask */
    uint8_t IPProtocol;        /*!< IP Protocol */
    uint8_t IPProtocolMask;    /*!< IP Protocol Mask */
    uint8_t res3[14];
    uint8_t srcIPAddr[16]; /*!< IP Source Address, Bits 127-0: IPv6 source address, Bits 127-96: IPv4 source address */
    uint8_t res4[8];
    uint8_t srcIPAddrMask[16]; /*!< IP Source Address Mask */
    uint16_t l4SrcPort;        /*!< L4 Source Port */
    uint16_t l4SrcPortMask;    /*!< L4 Source Port Mask */
    uint8_t res5[4];
    uint8_t destIPAddr[16]; /*!< IP Destination Address, Bits 127-0: IPv6 source address, Bits 127-96: IPv4 source
                               address */
    uint8_t res6[8];
    uint8_t destIPAddrMask[16]; /*!< IP Destination Address Mask*/
    uint16_t l4DestPort;        /*!< L4 Destination Port */
    uint16_t l4DestPortMask;    /*!< L4 Destination Port Mask */
    uint8_t res7[4];
    struct
    {
        uint8_t data; /*!< Payload Byte n */
        uint8_t mask; /*!< Payload Byte n  Mask */
    } payload[24];
} netc_tb_ipf_keye_t;

/*! @brief Ingress port filter forwarding Action */
typedef enum _netc_tb_ipf_forward_action
{
    kNETC_IPFForwardDiscard = 0U, /*!< Frame be discard */
    kNETC_IPFForwardPermit,       /*!< Frame be permit */
    kNETC_IPFRedirectToMgmtPort,  /*!< Redirect frame to switch management port without any frame modification, Switch
                                    only */
    kNETC_IPFCopyToMgmtPort /*!< Copy frame to switch management port without any frame modification, Switch only */
} netc_tb_ipf_forward_action_t;

/*! @brief Ingress port filter Filter Action */
typedef enum _netc_tb_ipf_filter_action
{
    kNETC_IPFNoAction = 0U,     /*!< No action */
    kNETC_IPFWithRatePolicer,   /*!< Rate action with the Rate Policer Entry ID (RP_EID) set to the value configured in
                                   the fltaTgt field */
    kNETC_IPFWithIngressStream, /*!< Ingress stream identification action where the Ingress Stream Entry ID (IS_EID) is
                                   set to the value configured in the fltaTgt field */
    kNETC_IPFWithL2Filtering    /*!< Setting a pre L2 filtering SI bitmap (set to the value configured in the fltaTgt)
                                   that will be used by the L2 filtering function to determine the final SI bitmap, ENETC
                                   only */
} netc_tb_ipf_filter_action_t;

/*! @brief Ingress port filter config element */
typedef struct _netc_tb_ipf_cfge
{
    uint32_t ipv : 4;                       /*!< Internal Priority Value */
    uint32_t oipv : 1;                      /*!< Overwrite IPV */
    uint32_t dr : 2;                        /*!< Drop Resilience */
    uint32_t odr : 1;                       /*!< Overwrite DR */
    netc_tb_ipf_forward_action_t fltfa : 2; /*!< Filter Forwarding action. */
    uint32_t : 1;
    uint32_t imire : 1;                   /*!< Ingress Mirroring Enable */
    uint32_t wolte : 1;                   /*!< Wake-onLAN trigger enable */
    netc_tb_ipf_filter_action_t flta : 2; /*!< FIlter Action. */
    uint32_t rpr : 2;                     /*!< Relative Precedent Resolution */
    uint32_t ctd : 1;                     /*!< Cut through disable. */
    netc_host_reason_t hr : 4;            /*!< Host Reason metadata when frame is redirected/copied to
                                            the switch management port */
    uint32_t timecape : 1;                /*!< Timestam capture enable */
    uint32_t : 9;
    uint32_t fltaTgt; /*!< Target for selected switch forwarding action or filter action*/
} netc_tb_ipf_cfge_t;

/*! @brief Ingress port filter statistic element */
typedef struct _netc_tb_ipf_stse
{
    uint32_t matchCount[2]; /*!< A count of how many times this entry has been matched. */
} netc_tb_ipf_stse_t;

/*! @brief Ingress port filter table entry config */
typedef struct _netc_tb_ipf_req_data
{
    netc_tb_common_header_t commonHeader;
    union
    {
        netc_tb_ipf_keye_t keye;
        uint32_t entryID;
        uint32_t sCriteria;
    };
    netc_tb_ipf_cfge_t cfge;
} netc_tb_ipf_req_data_t;

/*! @brief Ingress port filter table response data */
typedef struct _netc_tb_ipf_rsp_data
{
    uint32_t status;
    uint32_t entryID;        /*!< Present only for commands which perform a query */
    netc_tb_ipf_keye_t keye; /*!< Present only for commands which perform a query */
    netc_tb_ipf_stse_t stse; /*!< Present only for commands which perform a query */
    netc_tb_ipf_cfge_t cfge; /*!< Present only for commands which perform a query */
} netc_tb_ipf_rsp_data_t;

/*! @brief Ingress Port filter table data buffer */
typedef struct _netc_tb_ipf_data
{
    union
    {
        netc_tb_ipf_req_data_t request;
        netc_tb_ipf_rsp_data_t response;
    };
} netc_tb_ipf_data_t;

/*! @brief Ingress Port filter entry config */
typedef struct _netc_tb_ipf_config
{
    netc_tb_ipf_keye_t keye;
    netc_tb_ipf_cfge_t cfge;
} netc_tb_ipf_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Port Filter Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Stream Identification Table
#endif

/*! @brief 2 Bytes VLAN field which may added to the frame Key */
#define NETC_ISI_VLAN_FRAME_KEY(valid, pcp, vid) \
    (((uint16_t)((valid)&0x1) << 15U) | ((uint16_t)((pcp)&0x3) << 12U) | ((uint16_t)(vid)&0xFFFU))

/*! @brief Stream identification table key type */
typedef enum _netc_tb_isi_key_type
{
    kNETC_KCRule0 = 0U, /*!< Use key construction rule 0 (ISIDKC0CR0) */
    kNETC_KCRule1,      /*!< Use key construction rule 1 (ISIDKC1CR0) */
    kNETC_KCRule2,      /*!< Use key construction rule 2 (ISIDKC2CR0). Only for SWITCH */
    kNETC_KCRule3       /*!< Use key construction rule 3 (ISIDKC3CR0). Only for SWITCH */
} netc_tb_isi_key_type;

/*! @brief Stream identification table key element */
typedef struct _netc_tb_isi_keye
{
    netc_tb_isi_key_type keyType : 2; /*!< Define the key type used for the current isi entry */
    uint8_t srcPortID : 5;            /*!< Source Port ID, used when kc portp filed is 1. Only for SWITCH */
    uint8_t spm : 1;                  /*!< Source Port Masquerading, used when kc spm filed is 1. Only for SWITCH */
    uint8_t res0[3];
    uint8_t framekey[16]; /*!< Frame portion of the key. */
} netc_tb_isi_keye_t;

/*! @brief Stream identification table config element */
typedef struct _netc_tb_isi_cfge
{
    uint32_t iSEID; /*!< Ingress stream entry ID, 0xFFFFFFFF means NULL */
} netc_tb_isi_cfge_t;

/*! @brief Stream identification table request data buffer */
typedef struct _netc_tb_isi_req_data
{
    netc_tb_common_header_t commonHeader;
    union
    {
        uint32_t entryID;
        uint32_t sCriteria;
        netc_tb_isi_keye_t keye;
    };
    netc_tb_isi_cfge_t cfge;
} netc_tb_isi_req_data_t;

/*! @brief Stream identification table request response data buffer */
typedef struct _netc_tb_isi_rsp_data
{
    uint32_t status;
    uint32_t entryID;        /*!< Only present for query command */
    netc_tb_isi_keye_t keye; /*!< Only present for query command */
    netc_tb_isi_cfge_t cfge; /*!< Only present for query command */
} netc_tb_isi_rsp_data_t;

/*! @brief Stream identification table data buffer */
typedef struct _netc_tb_isi_data
{
    union
    {
        netc_tb_isi_req_data_t request;
        netc_tb_isi_rsp_data_t response;
    };
} netc_tb_isi_data_t;

/*! @brief Stream identification table entry config */
typedef struct _netc_tb_isi_config
{
    netc_tb_isi_keye_t keye;
    netc_tb_isi_cfge_t cfge;
} netc_tb_isi_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Stream Identification Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Stream Table
#endif

/*! @brief Ingress Stream table Ingress Sequence Action */
typedef enum _netc_tb_is_isq_action
{
    kNETC_ISNotPerformFRER = 0, /*!< Not perform Frame FRER sequence generation function */
    kNETC_ISPerformFRER         /*!< Perform Frame FRER sequence generation function */
} netc_tb_is_isq_action_t;

/*! @brief Ingress Stream table forwarding Action */
typedef enum _netc_tb_is_forward_action
{
    kNETC_ISDiscard            = 0U, /*!< Frame be discard */
    kNETC_ISRedirectToMgmtPort = 1U, /*!< Frame be Re-direct frame to switch management port, Switch only */
    kNETC_ISAllow              = 1U, /*!< Frame is allow without setting the pre L2 filtering SI bitmap, ENETC only */
    kNETC_ISAllowWithSIMap = 2U, /*!< Frame is allow with setting the pre L2 filtering SI bitmap to the value configured
                                    in the SI_MAP field, ENETC only */
    kNETC_ISStreamForward = 2U,  /*!< Frame is forwarded to the port(s) specified in the EGRESS_PORT_BITMAP field,
                                         Switch only */
    kNETC_ISBridgeForward, /*!< Frame is do 802.1Q Bridge forwarding (VLAN processing and L2 forwarding), Switch only */
    kNETC_ISCopyToMgmtPortAndStream, /*!< Copy frame to switch management port with specified HR and stream forwarding,
                                        Switch only */
    kNETC_ISCopyToMgmtPortAndBridge  /*!< Copy frame to switch management port with specified HR and Bridge forwarding,
                                        Switch only */
} netc_tb_is_forward_action_t;

/*! @brief Ingress Stream table Cut-Through Disable mode */
typedef enum _netc_tb_is_ctd_mode
{
    kNETC_ISNoCTD = 0x0U,  /*!< Do not override cut-through state */
    kNETC_ISSinglePortCTD, /*!< Disable cut-through for the outgoing port specified in the cfge ePort field */
    kNETC_ISAllPortCTD     /*!< Disable cut-through for all ports specified in cfge portBitmap field */
} netc_tb_is_ctd_mode_t;

/*! @brief Ingress Stream table Override ET_EID mode */
typedef netc_tb_eteid_access_mode_t netc_tb_is_oeteid_mode_t;

/*! @brief Ingress Stream table config element */
typedef struct _netc_tb_is_cfge
{
    uint32_t sfe : 1; /*!< Stream Filtering Enable */
    uint32_t : 3;
    uint32_t ipv : 4;      /*!< Internal Priority Value, active when opiv is set to 1 */
    uint32_t oipv : 1;     /*!< Override internal priority value */
    uint32_t dr : 2;       /*!< Drop Resilience, active when odr is set to 1 */
    uint32_t odr : 1;      /*!< Overwrite DR */
    uint32_t imire : 1;    /*!< Ingress Mirroring Enable, not applicable to ENETC */
    uint32_t timecape : 1; /*!< Timestamp Capture Enable, not applicable to ENETC */
    uint32_t : 1;
    uint32_t sppd : 1;                /*!< Source Port Pruning Disable, not applicable to ENETC */
    netc_tb_is_isq_action_t isqa : 2; /*!< Ingress Sequence Action, not applicable to ENETC */
    uint32_t orp : 1;                 /*!< Override Rate Policer ID */
    uint32_t osgi : 1;                /*!< Override stream gate instance entry id (default is NULL) */
    netc_host_reason_t hr : 4; /*!< Host Reason when frame is redirected (fa = 01b) to the switch management port or
                        copied to the switch management port (fa = 100b or 101b), value specified has to be a software
                        defined Host Reason (8-15). */
    netc_tb_is_forward_action_t fa : 3; /*!< Forwad Option */
    netc_tc_sdu_type_t sduType : 2;     /*!< Service Data Unit Type to user for MSDU */
    uint32_t : 3;
    uint32_t msdu : 16;         /*!< Maximum Service Data Unit */
    uint32_t ifmeLenChange : 7; /*!< Ingress Frame Modification Entry Frame Length Change, specified in unit of bytes
                                   using a 2's complement notation */
    uint32_t eport : 5; /*!< Egress Port which need do egress packet processing, active when oeteid is set to 1, not
                           applicable to ENETC */
    netc_tb_is_oeteid_mode_t oETEID : 2; /*!< Override ET_EID (Egress Treatment table entry, which specified egress
                            packet processing actions) */
    netc_tb_is_ctd_mode_t ctd : 2;       /*!< Cut-Through Disable mode, valid if fa = 010b ~ 101b */
    uint32_t isqEID; /*!< Ingress Sequence Generation Entry ID, Valid when isqa is set to 1. 0xFFFF_FFFF is NULL. Not
                        applicable to ENETC */
    uint32_t rpEID;  /*!< Rate Policer Entry ID, Valid when orp =1. 0xFFFF_FFFF is NULL */
    uint32_t sgiEID; /*!< Stream Gate Instance Entry ID, Valid when osgi =1. 0xFFFF_FFFF is NULL */
    uint32_t ifmEID; /*!< Ingress Frame Modification Entry ID. 0xFFFF_FFFF is NULL */
    uint32_t etEID;  /*!< Base Egress Treatment Entry ID for primary Egress Treatment group, Valid alid if fa = 010b ~
                        101b.  0xFFFF_FFFF is NULL. Not applicable  to ENETC */
    uint32_t iscEID; /*!< Ingress Stream counter Index. 0xFFFF_FFFF is NULL. */
    uint32_t ePortBitmap; /*!< Egress Port bitmap, identifies the ports to which the frame is to be forwarding or
                                  ET applicability port bitmap when oETEID = 10b. Not applicable to ENETC */
    uint32_t : 8;
    uint32_t siMap : 16; /*!< Station Interface Map, only valid for ENETC function when fa field is set to 10b */
    uint32_t : 16;
} netc_tb_is_cfge_t;

/*! @brief Ingress Stream table request data buffer */
typedef struct _netc_tb_is_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_is_cfge_t cfge; /*!< Only perform for update or add command */
} netc_tb_is_req_data_t;

/*! @brief Ingress Stream table request response data buffer */
typedef struct _netc_tb_is_rsp_data
{
    uint32_t entryID;       /*!< Only perform for query command */
    netc_tb_is_cfge_t cfge; /*!< Only perform for query command */
} netc_tb_is_rsp_data_t;

/*! @brief Ingress Stream table data buffer */
typedef struct _netc_tb_is_data
{
    union
    {
        netc_tb_is_req_data_t request;
        netc_tb_is_rsp_data_t response;
    };
} netc_tb_is_data_t;

/*! @brief Ingress Stream table entry config */
typedef struct _netc_tb_is_config
{
    uint32_t entryID;
    netc_tb_is_cfge_t cfge;
} netc_tb_is_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Stream Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Stream Filter Table
#endif

/*! @brief Ingress Stream Filter table key element */
typedef struct _netc_tb_isf_keye
{
    uint32_t isEID;  /*!< Ingress Stream Entry ID */
    uint8_t pcp : 3; /*!< Priority Code Point, Outer VLAN TAG PCP of the received frame */
    uint8_t : 5;
} netc_tb_isf_keye_t;

/*! @brief Ingress Stream Filter table config element */
typedef struct _netc_tb_isf_cfge
{
    uint32_t ipv : 4;      /*!< Internal Priority Value, active when opiv is set to 1 */
    uint32_t oipv : 1;     /*!< Override internal priority value */
    uint32_t dr : 2;       /*!< Drop Resilience, active when odr is set to 1 */
    uint32_t odr : 1;      /*!< Overwrite DR */
    uint32_t imire : 1;    /*!< Ingress Mirroring Enable, not applicable to ENETC */
    uint32_t timecape : 1; /*!< Timestamp Capture Enable, not applicable to ENETC */
    uint32_t osgi : 1;     /*!< Override stream gate instance entry id */
    uint32_t ctd : 1;      /*!< Cut-Through Disable, will disable cut-through for all destined ports when set 1, not
                              applicable to ENETC */
    uint32_t orp : 1;      /*!< Override Rate Policer (instance) ID */
    netc_tc_sdu_type_t sduType : 2; /*!< Service Data Unit Type to user for MSDU */
    uint32_t : 1;
    uint32_t msdu : 16; /*!< Maximum Service Data Unit */
    uint32_t rpEID;     /*!< Rate Policer Entry ID, Valid when orp =1. 0xFFFF_FFFF is NULL */
    uint32_t sgiEID;    /*!< Stream Gate Instance Entry ID, Valid when osgi =1. 0xFFFF_FFFF is NULL */
    uint32_t iscEID;    /*!< Ingress Stream counter Index. 0xFFFF_FFFF is NULL. */
} netc_tb_isf_cfge_t;

/*! @brief Ingress Stream Filter table request data buffer */
typedef struct _netc_tb_isf_req_data
{
    netc_tb_common_header_t commonHeader;
    union
    {
        uint32_t entryID;
        uint32_t sCriteria;
        netc_tb_isf_keye_t keye;
    };
    netc_tb_isf_cfge_t cfge; /*!< Only perform for update or add command */
} netc_tb_isf_req_data_t;

/*! @brief Ingress Stream Filter table request response data buffer */
typedef struct _netc_tb_isf_rsp_data
{
    uint32_t status;
    uint32_t entryID;        /*!< Only perform for query command */
    netc_tb_isf_keye_t keye; /*!< Only perform for query command */
    netc_tb_isf_cfge_t cfge; /*!< Only perform for query command */
} netc_tb_isf_rsp_data_t;

/*! @brief Ingress Stream Filter table data buffer */
typedef struct _netc_tb_isf_data
{
    union
    {
        netc_tb_isf_req_data_t request;
        netc_tb_isf_rsp_data_t response;
    };
} netc_tb_isf_data_t;

/*! @brief Ingress Stream Filter table entry config */
typedef struct _netc_tb_isf_config
{
    netc_tb_isf_keye_t keye;
    netc_tb_isf_cfge_t cfge;
} netc_tb_isf_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Stream Filter Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Rate Policer Table
#endif

/*! @brief Rate Policer Table Update Actions */
typedef enum _netc_tb_rp_update_action
{
    kNETC_RPCfgEUpdate = 0x1U, /*!< Configuration Element Update */
    kNETC_RPFeEUpdate  = 0x2U, /*!< Functional Enable Element Update */
    kNETC_RPPsEUpdate  = 0x4U, /*!< Policer State Element Update Element Update */
    kNETC_RPStsEUpdate = 0x8U  /*!< Statistics Element Update */
} netc_tb_rp_update_action_t;

/*! @brief Rate Policer Table Protocol/Service Data Unit Type */
typedef netc_tc_sdu_type_t netc_tb_rp_sdu_type_t;

/*! @brief Rate Policer table config element */
typedef struct _netc_tb_rp_cfge
{
    uint32_t cir;      /*!< Committed information Rate */
    uint32_t cbs;      /*!< Commited Burst Size */
    uint32_t eir;      /*!< Excess information Rate */
    uint32_t ebs;      /*!< Excess Burst Size */
    uint32_t mren : 1; /*!< Mark All Frames Red Enable, Not valid when ndor=1 */
    uint32_t doy : 1;  /*!< Drop on Yellow enable */
    uint32_t cm : 1;   /*!< Color mode, 0b = Color blind, 1b = Color aware */
    uint32_t cf : 1;   /*!< Coupling flag, enables coupling the Committed (C) bucket and Excess (E) bucket */
    uint32_t ndor : 1; /*!< No drop on red */
    netc_tb_rp_sdu_type_t sduType : 2; /*!< Service Data Unit Type */
    uint32_t : 25;                     /*!< Reserved */
} netc_tb_rp_cfge_t;

/*! @brief Rate Policer table Function Enable element */
typedef struct _netc_tb_rp_fee
{
    uint8_t fen : 1; /*!< Function Enable */
    uint8_t : 7;     /*!< Reserved */
} netc_tb_rp_fee_t;

/*! @brief Rate Policer table Policer State element */
typedef struct _netc_tb_rp_pse
{
    uint8_t mr : 1;   /*!< Mark Red Flag */
    uint8_t res0 : 7; /*!< Reserved */
} netc_tb_rp_pse_t;

/*! @brief Rate Policer table statistic element */
typedef struct _netc_tb_rp_stse
{
    uint32_t byteCount[2];       /*!< Number of bytes received by the rate policer instance */
    uint32_t dropFrames[2];      /*!< Number of frames dropped by the rate policer instance */
    uint32_t dr0GrnFrames[2];    /*!< Number of frames marked green with DR=0 by the rate policer instance */
    uint32_t dr1GrnFrames[2];    /*!< Number of frames marked green with DR=1 by the rate policer instance */
    uint32_t dr2GrnFrames[2];    /*!< Number of frames marked yellow with DR=2 by the rate policer instance */
    uint32_t remarkYlwFrames[2]; /*!< Number of frames re-marked from green to yellow by the rate policer instance */
    uint32_t dr3RedFrames[2];    /*!< Number of frames marked red with DR=3 by the rate policer instance */
    uint32_t
        remarkRedFrames[2]; /*!< Number of frames re-marked from green or yellow to red by the rate policer instance */
    uint32_t lts;           /*!< Last timestamp */
    uint32_t bci : 31;      /*!< Committed token bucket contents, integer portion (31 bits) */
    uint32_t bcs : 1;       /*!< Committed token bucket sign bit (1 bit) */
    uint32_t bcf;           /*!< Committed token bucket contents, fractional portion (31 bits) */
    uint32_t bei;           /*!< Excess token bucket contents, integer portion (32 bits) */
    uint32_t bef : 31;      /*!< Excess token bucket contents, fractional portion (31 bits) */
    uint32_t bes : 1;       /*!< Committed token bucket sign bit */
} netc_tb_rp_stse_t;

/*! @brief Rate Policer table request data buffer */
typedef struct _netc_tb_rp_req_data
{
    netc_tb_common_header_t commonHeader; /* Common header, contains Update Actions and Query Actions */
    uint32_t entryID;                     /* Access Key, activer when use Entry ID Match */
    union
    {
        netc_tb_rp_cfge_t cfge; /*!< Present only for commands which perform an update or add */
        struct
        {
            uint8_t reserved[18];
            netc_tb_rp_fee_t fee; /*!< Present only for commands which perform an update or add */
        };
    };
} netc_tb_rp_req_data_t;

/*! @brief Rate Policer table request response data buffer */
typedef struct _netc_tb_rp_rsp_data
{
    uint32_t entryID;       /*!< Present only for commands which perform a query */
    netc_tb_rp_stse_t stse; /*!< Present only for commands which perform a query */
    union
    {
        netc_tb_rp_cfge_t cfge; /*!< Present only for commands which perform a query */
        struct
        {
            uint8_t reserved1[18];
            netc_tb_rp_fee_t fee; /*!< Present only for commands which perform a query */
            uint8_t reserved2;
        };
        struct
        {
            uint8_t reserved3[19];
            netc_tb_rp_pse_t pse; /*!< Present only for commands which perform a query */
        };
    };
} netc_tb_rp_rsp_data_t;

/*! @brief Rate Policer table data buffer */
typedef struct _netc_tb_rp_data
{
    union
    {
        netc_tb_rp_req_data_t request;
        netc_tb_rp_rsp_data_t response;
    };
} netc_tb_rp_data_t;

/*! @brief Rate Policer table entry config */
typedef struct _netc_tb_rp_config
{
    uint32_t entryID;
    netc_tb_rp_cfge_t cfge;
    netc_tb_rp_fee_t fee;
} netc_tb_rp_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Rate Policer Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Stream Count Table
#endif

/*! @brief Ingress Stream Count table statistic element */
typedef struct _netc_tb_isc_stse
{
    uint32_t rxCount; /*!< Receive Count */
    uint32_t res0;
    uint32_t msduDropCount; /*!< MSDU Drop Count */
    uint32_t res1;
    uint32_t policerDropCount; /*!< Policer Drop Count */
    uint32_t res2;
    uint32_t sgDropCount; /*!< Stream Gating Drop Count */
    uint32_t res3;
} netc_tb_isc_stse_t;

/*! @brief Ingress Stream Count table request data buffer */
typedef struct _netc_tb_isc_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
} netc_tb_isc_req_data_t;

/*! @brief Ingress Stream Count table request response data buffer */
typedef struct _netc_tb_isc_rsp_data
{
    uint32_t entryID;
    netc_tb_isc_stse_t stse;
} netc_tb_isc_rsp_data_t;

/*! @brief Ingress Stream Count table data buffer */
typedef struct _netc_tb_isc_data
{
    union
    {
        netc_tb_isc_req_data_t request;
        netc_tb_isc_rsp_data_t response;
    };
} netc_tb_isc_data_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Stream Count Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Stream Gate Instance Table
#endif

/*! @brief Stream Gate Instance table Update Actions */
typedef enum _netc_tb_sgi_update_action
{
    kNETC_SGIAcfEUpdate  = 0x1U, /*!< Admin Configuration Element  */
    kNETC_SGICfgEUpdate  = 0x2U, /*!< Configuration Element Update */
    kNETC_SGISgisEUpdate = 0x4U  /*!< Stream Gate Instance State Element Update */
} netc_tb_sgi_update_action_t;

/*! @brief Stream Gate Instance table Protocol/Service Data Unit Type */
typedef netc_tc_sdu_type_t netc_tb_sgi_sdu_type_t;

/*! @brief Stream Gate Instance State */
typedef enum _netc_tb_sgi_state
{
    kNETC_GSNotOper = 0x0U,  /*!< Gate instance is not operational or Gate instance and lists are not valid */
    kNETC_GSUseDefaultParam, /*!< Gate instance is operational but no stream gate control list specified, use default
                                Gate Instance parameters */
    kNETC_GSUseDefUntilAdminAct,  /*!<  Use default Gate Instance parameters until administrative stream gate control
                                     list takes effect */
    kNETC_GSUseOperUntilAdminAct, /*!< Use Operational stream gate control list until new administrative stream gate
                                     control list takes effect */
    kNETC_GSUseOperList           /*!< Operational stream gate control list is in effect */
} netc_tb_sgi_state_t;

/*! @brief Stream Gate Instance table config element */
typedef struct _netc_tb_sgi_cfge
{
    uint8_t oexen : 1;                  /*!< Octets Exceeded (Gate Closed Due To Octets Exceeded function) Enable */
    uint8_t irxen : 1;                  /*!< Invalid Receive (Gate Closed Due To Invalid Rx) Enable */
    netc_tb_sgi_sdu_type_t sduType : 2; /*!< The type of PDU/SDU for Interval Octets Maximum check for Gate Entry */
    uint8_t : 4;
} netc_tb_sgi_cfge_t;

/*! @brief Stream Gate Instance table Admin Configuration element */
typedef struct _netc_tb_sgi_acfge
{
    uint32_t adminSgclEID;      /*!< Administrative Stream Gate Control List Entry ID, 0xFFFFFFFF is NULL */
    uint32_t adminBaseTime[2];  /*!< Admin Base Time */
    uint32_t adminCycleTimeExt; /*!< Admin Cycle Time Extension */
} netc_tb_sgi_acfge_t;

/*! @brief Stream Gate Instance table Initial Configuration element */
typedef struct _netc_tb_sgi_icfge
{
    uint8_t ipv : 4;  /*!< Internal Priority Value (IPV), Valid if oipv is 1 */
    uint8_t oipv : 1; /*!< Override frame IPV, otherwise the IPV value is determined by the stream gate control list
                          entry */
    uint8_t gst : 1;  /*!< Specifies Gate State before the administrative stream gate control list takes affect, 0b =
                         Closed; 1b = Open */
    uint8_t ctd : 1;  /*!< Specifies Cut Through disable status before the administrative stream gate control list takes
                          affect , Not applicable to ENETC function*/
    uint8_t : 1;
} netc_tb_sgi_icfge_t;

/*! @brief Stream Gate Instance table stream gate instance state element */
typedef struct _netc_tb_sgi_sgise
{
    uint32_t operSgclEID;          /*!< Operational Stream Gate Control List Entry ID */
    uint32_t configChangeTime[2];  /*!< Configuration Change Time */
    uint32_t operBaseTime[2];      /*!< Operational Base Time */
    uint32_t operCycleTimeExt;     /*!< Oper Cycle Time Extension */
    uint32_t oex : 1;              /*!< Octets Exceeded Flag */
    uint32_t irx : 1;              /*!< Invalid Receive Flag */
    netc_tb_sgi_state_t state : 3; /*!< Current Gate Instance State */
    uint32_t : 27;
} netc_tb_sgi_sgise_t;

/*! @brief Stream Gate Instance table request data buffer */
typedef struct _netc_tb_sgi_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_sgi_acfge_t acfge;
    netc_tb_sgi_cfge_t cfge;
    netc_tb_sgi_icfge_t icfge;
} netc_tb_sgi_req_data_t;

/*! @brief Stream Gate Instance table request response data buffer */
typedef struct _netc_tb_sgi_rsp_data
{
    uint32_t entryID;
    union
    {
        netc_tb_sgi_sgise_t sgise;
        struct
        {
            uint8_t res0[24];
            netc_tb_sgi_cfge_t cfge;
            netc_tb_sgi_icfge_t icfge;
            uint8_t res1;
        };
    };
    netc_tb_sgi_acfge_t acfge;
} netc_tb_sgi_rsp_data_t;

/*! @brief Stream Gate Instance table data buffer */
typedef struct _netc_tb_sgi_data
{
    union
    {
        netc_tb_sgi_req_data_t request;
        netc_tb_sgi_rsp_data_t response;
    };
} netc_tb_sgi_data_t;

/*! @brief Stream Gate Instance table entry config */
typedef struct _netc_tb_sgi_config
{
    uint32_t entryID;
    netc_tb_sgi_acfge_t acfge;
    netc_tb_sgi_cfge_t cfge;
    netc_tb_sgi_icfge_t icfge;
} netc_tb_sgi_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Stream Gate Instance Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Stream Gate Control List Table
#endif
/*! @brief Stream Gate Control List Table maximum gate control list length */
#define NETC_TB_SGCL_MAX_ENTRY (0x100U)

/*! @brief Defines the Stream Gate Control entry structure. */
typedef struct _netc_sgcl_gate_entry
{
    uint32_t timeInterval; /*!< Time Interval for Gate Entry */
    uint32_t iom : 24;     /*!< Interval Octets Maximum for Gate Entry, specifies the maximum bytes (octets) allowed to
                              pass (open), valid if iomen = 1 */
    uint32_t ipv : 4;      /*!< Internal Priority Value for Gate Entry */
    uint32_t oipv : 1;     /*!< Override Internal Priority Value for Gate Entry */
    uint32_t ctd : 1;      /*!< Cut Through Disable for Gate Entry */
    uint32_t iomen : 1;    /*!< Interval Octet Maximum Enabled for Gate Entry, 0b = Don'track count, 1b = Track count */
    uint32_t gtst : 1;     /*!< Gate State for Gate Entry, 0b = Closed; 1b = Open  */
} netc_sgcl_gate_entry_t;

/*! @brief Stream Gate Control List table config element */
typedef struct _netc_tb_sgcl_cfge
{
    uint32_t cycleTime; /*!< Cycle Time */
    uint8_t listLength; /*!< List Length */
    uint8_t res0;
    uint16_t extOipv : 1; /*!< Extension (means the stream gate control list ends and before cycleTime restarts)
                             Override Internal Priority Value */
    uint16_t extIpv : 4;  /*!< List Extension Internal Priority Value, valid if extOipv = 1 */
    uint16_t extCtd : 1;  /*!< Extension Cut Through Disabled, 0b = No action, 1b = Disabled */
    uint16_t extGtst : 1; /*!< Extension Gate State, 0b = closed, 1b = Open */
    uint16_t res1 : 9;
    netc_sgcl_gate_entry_t ges[];
} netc_tb_sgcl_cfge_t;

/*! @brief Stream Gate Control List table Stream Gate Control List State element */
typedef struct _netc_tb_sgcl_sgclse
{
    uint8_t refCount; /*!< Reference Count, 1 indicates that the gate control list is an administrative or an
                         operational gate control list in a stream gate instance  */
} netc_tb_sgcl_sgclse_t;

/*! @brief Stream Gate Control List table request data buffer */
typedef struct _netc_tb_sgcl_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_sgcl_cfge_t cfge;
} netc_tb_sgcl_req_data_t;

/*! @brief Stream Gate Control List table request response data buffer */
typedef struct _netc_tb_sgcl_rsp_data
{
    uint32_t entryID;
    netc_tb_sgcl_sgclse_t sgclse;
    uint8_t res[3];
    netc_tb_sgcl_cfge_t cfge;
} netc_tb_sgcl_rsp_data_t;

/*! @brief Stream Gate Control List table data buffer */
typedef struct _netc_tb_sgcl_data
{
    union
    {
        netc_tb_sgcl_req_data_t request;
        netc_tb_sgcl_rsp_data_t response;
        struct
        {
            uint32_t rel0[4];
            netc_sgcl_gate_entry_t res1[NETC_TB_SGCL_MAX_ENTRY];
        };
    };
} netc_tb_sgcl_data_t;

/*! @brief Stream Gate Control List table entry gate control list structure */
typedef struct _netc_tb_sgcl_gcl
{
    uint16_t entryID;
    uint16_t extOipv : 1; /*!< Extension (means the stream gate control list ends and before cycleTime restarts)
                             Override Internal Priority Value */
    uint16_t extIpv : 4;  /*!< List Extension Internal Priority Value, valid if extOipv = 1 */
    uint16_t extCtd : 1;  /*!< Extension Cut Through Disabled, 0b = No action, 1b = Disabled */
    uint16_t extGtst : 1; /*!< Extension Gate State, 0b = closed, 1b = Open */
    uint32_t cycleTime;   /*!< Cycle Time */
    uint32_t numEntries;  /*!< Control List entry numbers */
    netc_sgcl_gate_entry_t *gcList; /*!< Pointer to stream gate control list array */
} netc_tb_sgcl_gcl_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Stream Gate Control List Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Frame Modification Table
#endif

/*!
 * @brief Frame Modification table Layer 2 Actions
 * @note  This field must be set to 0 for traffic destined to a pseudo link.
 *        This field must be set to 0 for any device with ASIL-B safety requirements.
 */
typedef enum _netc_tb_fm_layer2_act
{
    kNETC_UseL2HeaderAct = 0U, /*!< L2 actions are specified in L2 header action fields macHdrAct,
                                    vlanHdrAct and sqtAct */
    kNETC_UseSpecPlayload /*!< The entire L2 PDU is replaced with fmdBytes of data specified in fmdEID, not applicable
                             for ingress frame modifications */
} netc_tb_fm_layer2_act_t;

/*!
 * @brief Frame Modification table Layer 2 Header MAC Actions
 * @note Ingress frame modifications only support kNETC_NoAction or kNETC_ReplDmac.
 */
typedef enum _netc_tb_fm_mac_header_act
{
    kNETC_NoMacAction = 0U, /*!< No Mac header action */
    kNETC_ReplSmac    = 2U, /*!< Replace SMAC with the contents of the port's PMAR0/1 register, The port is specified by
                                       smacPort field */
    kNETC_ReplSmacAndDmacAct1, /*!< Replace SMAC and DMAC, The content of SMAC is the same as kNETC_ReplaceSMAC, the
                                      DMAC is specified by dmac[6] field */
    kNETC_ReplSmacAndDmacAct2, /*!< Replace SMAC and DMAC, The content of SMAC is the same as kNETC_ReplaceSMAC, the
                                      DMAC is specified by frame's SMAC */
    kNETC_ReplDmac,            /*!< Replace DMAC with specified dmac[6] field value */
    kNETC_SwapDmacAndSmac      /*!< Swap DMAC and SMAC */
} netc_tb_fm_mac_header_act_t;

/*!
 * @brief Frame Modification table Layer 2 VLAN Actions
 * @note For use Delete or Replace action, if no outer VLAN header is present, then a misconfiguration event will be
 *       generated and handled according to the port's PFMCR register.
 */
typedef enum _netc_tb_fm_vlan_header_act
{
    kNETC_NoVlanAction = 0U, /*!< No VLAN header action */
    kNETC_DelOuterVlan,      /*!< Delete outer VLAN header */
    kNETC_AddOuterVlan, /*!< Add outer VLAN header (new VLAN data will be inserted in the outer position), the VID, PCP,
                          DEI and TPID values are specified by outerVidAct, outerPcpAct, outerDeiAct and outerTpidAct
                          field */
    kNETC_ReplOuterVlan /*!< Replace outer VLAN header, the VID, PCP, DEI and TPID values are specified by outerVidAct,
                          outerPcpAct, outerDeiAct and outerTpidAct field */
} netc_tb_fm_vlan_header_act_t;

/*!
 * @brief Frame Modification table Layer 2 outer VLAN VID Actions
 * @note For use kNETC_UseFrameVID action, if no outer VLAN header is present, then a misconfiguration event will be
 *       generated and handled according to the port's PFMCR register.
 */
typedef enum _netc_tb_fm_outer_vid_act
{
    kNETC_UseFrameVid = 0U, /*!< Use the VID from the valid outer VLAN header of the received frame */
    kNETC_UseSpecVid        /*!< Use the VID specified in the outerVlanID field */
} netc_tb_fm_outer_vid_act_t;

/*!
 * @brief Frame Modification table Sequence Tag Action
 * @note For use kNETC_ReomveTag action, If R-TAG/draft 2.0 R-TAG/HSR tag not present, then a misconfiguration event
 * will be generated and handled according to the port's PFMCR register.
 */
typedef netc_fm_sqt_act_t netc_tb_fm_sqt_act_t;

/*!
 * @brief Frame Modification table Outer TPID action
 * @note For use kNETC_UseFrameTpid action, If outer VLAN header not present, then a misconfiguration event will be
 *       generated and handled according to the port's PFMCR register.
 */
typedef enum _netc_tb_fm_outer_tpid_act
{
    kNETC_UseFrameTpid = 0U, /*!< Use TPID from outer VLAN header */
    kNETC_UseStdCVlan,       /*!< Set TPID to Standard C-VLAN 0x8100 */
    kNETC_UseStdSVlan,       /*!< Set TPID to Standard S-VLAN 0x88A8 */
    kNETC_UseCustomCVlan,    /*!< Set TPID to Custom C-VLAN as defined by CVLANR1[ETYPE] */
    kNETC_UseCustomSVlan     /*!< Set TPID to Custom S-VLAN as defined by CVLANR2[ETYPE] */
} netc_tb_fm_outer_tpid_act_t;

/*!
 * @brief Frame Modification table Outer PCP action
 * @note For use kNETC_UseFramePcp/kNETC_UseFramePcpMap action, If outer VLAN header not present, then a
 * misconfiguration event will be generated and handled according to the port's PFMCR register.
 */
typedef enum _netc_tb_fm_outer_pcp_act
{
    kNETC_UseFramePcp = 0U, /*!< Use PCP from frame outer VLAN header */
    kNETC_UseSpecPcp,       /*!< Use the PCP specified in the outerVlanPcp field */
    kNETC_UseFramePcpMap,   /*!< The PCP is mapping from frame outer VLAN PCP (do mapping according to the PCP to PCP
                               mapping profile which specified in PPCPDEIMR[IPCPMP/EPCPMP]) */
    kNETC_UseQosMap /*!< The PCP is mapping from internal QoS (IPV, DR) (do mapping according to the QOS to PCP mapping
                    profile which specified in QOSVLANMPaR0/1/2/3), not applicable for ingress frame modifications */
} netc_tb_fm_outer_pcp_act_t;

/*!
 * @brief Frame Modification table Outer DEI action
 * @note For use kNETC_UseFrameDei action, If outer VLAN header not present, then a misconfiguration event will be
 *       generated and handled according to the port's PFMCR register.
 */
typedef enum _netc_tb_fm_outer_dei_act
{
    kNETC_UseFrameDei = 0U, /*!< Use DEI from frame outer VLAN header */
    kNETC_UseSpecDei,       /*!< Use the DEI specified in the outerVlanDei field */
    kNETC_UseDrMap          /*!< The DEI is mapping from internal DR (do mapping according to the DR to DEI mapping
                             profile which specified in PPCPDEIMR[DRnDEI], not applicable for ingress frame modifications */
} netc_tb_fm_outer_dei_act_t;

/*!
 * @brief Frame Modification table Payload Actions
 * @note  This field must be set to 0 for traffic destined to a pseudo link.
 *        This field must be set to 0 for any device with ASIL-B safety requirements.
 */
typedef enum _netc_tb_fm_payload_act
{
    kNETC_NoAction = 0U,    /*!< No Action */
    kNETC_ReplAllEthPld,    /*!< Remove entire Ethernet payload and insert with fmdBytes of data specified in fmdEID */
    kNETC_ReplPldWithOffset /*!< Replace fmdBytes of raw data in the Ethernet payload starting at pldOffset, data
                               specified in fmdEID */
} netc_tb_fm_payload_act_t;

/*! @brief Frame Modification table config element */
typedef struct _netc_tb_fm_cfge
{
    netc_tb_fm_layer2_act_t l2Act : 1;           /*!< Layer 2 Actions */
    netc_tb_fm_mac_header_act_t macHdrAct : 3;   /*!< Layer 2 Header MAC Actions */
    netc_tb_fm_vlan_header_act_t vlanHdrAct : 2; /*!< Layer 2 VLAN Actions */
    netc_tb_fm_outer_vid_act_t outerVidAct : 2;  /*!< Outer VID Actions */
    netc_tb_fm_sqt_act_t sqtAct : 3; /*!< Sequence Tag Action, Not applicable for ingress frame modifications */
    uint16_t smacPort : 5;           /*!< Source MAC Address Register Port, valid if macHdrAct=010b,011b,100b */
    uint8_t dmac[6];                 /*!< Destination MAC Address, valid if macHdrAct = 011b,101b */
    uint32_t outerVlanID : 12;       /*!< Outer VLAN VID, valid if outerVidAct = 01b */
    uint32_t outerVlanPcp : 3;       /*!< Outer VLAN PCP, valid if outerPcpAct = 01b */
    uint32_t outerVlanDei : 1;       /*!< Outer VLAN DEI, valid if outerDeiAct = 01b */
    netc_tb_fm_outer_tpid_act_t outerTpidAct : 3; /*!< Outer TPID action */
    netc_tb_fm_outer_pcp_act_t outerPcpAct : 3;   /*!< Outer PCP action */
    netc_tb_fm_outer_dei_act_t outerDeiAct : 2;   /*!< Outer DEI action */
    netc_tb_fm_payload_act_t pldAct : 3; /*!< Payload Actions, Not applicable for ingress frame modifications */
    uint32_t : 5;
    uint8_t pldOffset; /*!< Payload Offset, valid if outerPldAct = 010b */
    uint8_t res1[3];
    uint16_t fmdBytes; /*!< Frame Modification Bytes, valid if outerPldAct = 001b,010b or l2Act = 1b */
    uint16_t res2;
    uint32_t fmdEID; /*!< Frame Modification Data Entry ID, valid if outerPldAct = 001b,010b or l2Act = 1b. 0xFFFF is
                        null pointer */
} netc_tb_fm_cfge_t;

/*! @brief Frame Modification table request data buffer */
typedef struct _netc_tb_fm_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_fm_cfge_t cfge;
} netc_tb_fm_req_data_t;

/*! @brief Frame Modification table request response data buffer */
typedef struct _netc_tb_fm_rsp_data
{
    uint32_t entryID;
    netc_tb_fm_cfge_t cfge;
} netc_tb_fm_rsp_data_t;

/*! @brief Frame Modification table data buffer */
typedef struct _netc_tb_fm_data
{
    union
    {
        netc_tb_fm_req_data_t request;
        netc_tb_fm_rsp_data_t response;
    };
} netc_tb_fm_data_t;

/*! @brief Frame Modification table entry config */
typedef struct _netc_tb_fm_config
{
    uint32_t entryID;
    netc_tb_fm_cfge_t cfge;
} netc_tb_fm_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Frame Modification DataTable
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Frame Modification Data Table
#endif
/*! @brief TFrame Modification Data table update config Data Buffer length, x is the number of update data bytes */
#define NETC_TB_FMD_UPDATE_CONFIG_LENGTH(x) (8U + (x))

/*! @brief Frame Modification Data table request data buffer */
typedef struct _netc_tb_fmd_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    uint8_t cfge[]; /*!< Configuration Element Data size is variable */
} netc_tb_fmd_req_data_t;

/*! @brief Frame Modification Data table request response data buffer */
typedef struct _netc_tb_fmd_rsp_data
{
    uint32_t entryID;
    uint8_t cfge[]; /*!< Configuration Element Data size is variable */
} netc_tb_fmd_rsp_data_t;

/*! @brief Frame Modification Data table data buffer */
typedef struct _netc_tb_fmd_data
{
    union
    {
        netc_tb_fmd_req_data_t request;
        netc_tb_fmd_rsp_data_t response;
    };
} netc_tb_fmd_data_t;

/*! @brief Frame Modification data table entry update config */
typedef struct _netc_tb_fmd_update_config
{
    uint32_t res; /*!< Hold for request->commonHeader */
    uint32_t entryID;
    uint8_t cfge[]; /*!< Configuration Element Data size is variable */
} netc_tb_fmd_update_config_t;

/*! @brief Frame Modification data table entry query data buffer */
typedef struct _netc_tb_fmd_query_buffer
{
    uint32_t entryID; /*!< EntryID of the queried entry */
    uint8_t cfge[];   /*!< Configuration Element Data size is variable */
} netc_tb_fmd_query_buffer_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Frame Modification Data Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Vlan Filter Table
#endif

/*! @brief Vlan Filter table key element */
typedef struct _netc_tb_vf_keye
{
    uint32_t vid : 12;
    uint32_t : 20;
} netc_tb_vf_keye_t;

/*! @brief Vlan Filter table config element */
typedef struct _netc_tb_vf_cfge
{
    uint32_t portMembership : 24; /*!< Port Membership Bitmap */
    uint32_t stgID : 4;           /*!< Spanning Tree Group Member ID */
    uint32_t : 4;
    uint32_t fid : 12; /*!< Filtering ID */
    uint32_t : 4;
    uint32_t mlo : 3; /*!< MAC Learning Options */
    uint32_t mfo : 2; /*!< MAC Forwarding Options */
    uint32_t : 1;
    uint32_t ipmfe : 1;  /*!< IP Multicast Filtering Enable */
    uint32_t ipmfle : 1; /*!< IP Multicast Flooding Enable */
    uint32_t : 8;
    uint32_t etaPortBitmap : 24; /*!< Egress Treatment Applicability Port Bitmap for the secondary
                                    Egress Treatment group */
    uint32_t : 8;
    uint32_t baseETEID; /*!< Base Egress Treatment Entry ID for the secondary Egress Treatment group */
} netc_tb_vf_cfge_t;

/*! @brief Vlan Filter table search criteria format */
typedef struct _netc_tb_vf_search_criteria
{
    uint32_t resumeEntryId; /*!< Resume Entry ID, when starting a search, pass the NULL Entry ID. */
} netc_tb_vf_search_criteria_t;

/*! @brief Vlan Filter table request data buffer */
typedef struct _netc_tb_vf_req_data
{
    netc_tb_common_header_t commonHeader;
    union
    {
        uint32_t entryID;
        netc_tb_vf_search_criteria_t sCriteria; /*!< Active when access method is kNETC_Search */
        netc_tb_vf_keye_t keye;
    };
    netc_tb_vf_cfge_t cfge; /*!< Present only for update or add commands */
} netc_tb_vf_req_data_t;

/*! @brief Vlan Filter table request response data buffer */
typedef struct _netc_tb_vf_rsp_data
{
    uint32_t status;        /*!< Present only for query command with search access method */
    uint32_t entryID;       /*!< Present only for query command */
    netc_tb_vf_keye_t keye; /*!< Present only for query command */
    netc_tb_vf_cfge_t cfge; /*!< Present only for query command */
} netc_tb_vf_rsp_data_t;

/*! @brief Vlan Filter table data buffer */
typedef struct _netc_tb_vf_data
{
    union
    {
        netc_tb_vf_req_data_t request;
        netc_tb_vf_rsp_data_t response;
    };
} netc_tb_vf_data_t;

/*! @brief Vlan Filter table entry config */
typedef struct _netc_tb_vf_config
{
    netc_tb_vf_keye_t keye;
    netc_tb_vf_cfge_t cfge;
} netc_tb_vf_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Vlan Filter Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region FDB Table
#endif

/*! @brief FDB table Update Actions */
typedef enum _netc_tb_fdb_update_action
{
    kNETC_FDBCfgEUpdate = 0x1U, /*!< Configuration Element Update */
    kNETC_FDBActEUpdate = 0x2U  /*!< Activity Element Update */
} netc_tb_fdb_update_action_t;

/*! @brief FDB table entry defined the egress packet processing actions (will cover the actions which specified in the
 * Egress Treatment table )*/
typedef netc_tb_eteid_access_mode_t netc_tb_fdb_oeteid_mode_t;

/*! @brief FDB table Cut-Through Disable mode */
typedef enum _netc_tb_fdb_ctd_mode
{
    kNETC_FDBNoCTD         = 0x0U, /*!< Do not override cut-through state */
    kNETC_FDBSinglePortCTD = 0x1U, /*!< Disable cut-through for the outgoing port specified in the cfge ePort field */
    kNETC_FDBAllPortCTD    = 0x2U  /*!< Disable cut-through for all ports specified in cfge portBitmap field */
} netc_tb_fdb_ctd_mode_t;

typedef struct _netc_tb_fdb_keye
{
    uint8_t macAddr[6]; /*!< Destination MAC address of the frame for MAC forwarding lookups and the source MAC address
                           of the frame for MAC learning lookups */
    uint8_t res0[2];
    uint32_t fid : 12; /*!< Filtering ID, is obtained from an ingress lookup into the VLAN Filter table */
    uint32_t : 20;
} netc_tb_fdb_keye_t;

/*! @brief FDB table configuration element */
typedef struct _netc_tb_fdb_cfge
{
    uint32_t
        portBitmap : 24; /*!< Forwarding destination Port Bitmap and ET applicability port bitmap when oETEID = 10b */
    uint32_t : 8;
    netc_tb_fdb_oeteid_mode_t oETEID : 2; /*!< Override ET_EID option */
    uint32_t ePort : 5;                   /*!< Egress Ports, active when oETEid = 01b or ctd = 01b */
    uint32_t iMirE : 1;                   /*!< Ingress Mirroring Enable */
    uint32_t : 1;
    netc_tb_fdb_ctd_mode_t ctd : 2; /*!< Cut-Through Disable */
    uint32_t dynamic : 1;           /*!< Static or Dynamic Entry, 0b = Static entry, 1b = Dynamic entry */
    uint32_t timeCapE : 1;          /*!< Timestamp Capture Enable when set */
    uint32_t : 19;
    uint32_t etEID; /*!< Base egress treatment table entry id for primary Egress Treatment group, is valid if the oETEID
                       field is set to value other than kNETC_FDBNoEPP. 0xFFFFFFFF is NULL. */
} netc_tb_fdb_cfge_t;

/*! @brief FDB table Activity element */
typedef struct _netc_tb_fdb_acte
{
    uint8_t actCnt : 7;  /*!< Activity Counter */
    uint8_t actFlag : 1; /*!< Activity Flag */
} netc_tb_fdb_acte_t;

/*! @brief FDB table search criteria Key Element Match Criteria */
typedef enum _netc_tb_fdb_sc_keye_mc
{
    kNETC_FDBKeyeMacthAny          = 0x0, /*!< Match any Key Element Criteria */
    kNETC_FDBKeyeMacthFID          = 0x1, /*!< Match Key Element FID */
    kNETC_FDBKeyeMacthMacMulticast = 0x2, /*!< Match Key Element MAC Multicast bit (MAC_ADDR most
                                                significant byte's least significant bit) */
    kNETC_FDBKeyeMacthBoth = 0x3          /*!< Match both FID field and MAC Multicast bit */
} netc_tb_fdb_sc_keye_mc_t;

/*! @brief FDB table search criteria Configuration Element Match Criteria */
typedef enum _netc_tb_fdb_sc_cfge_mc
{
    kNETC_FDBCfgeMacthAny        = 0x0, /*!< Match any Configuration Element Criteria */
    kNETC_FDBCfgeMacthDynamic    = 0x1, /*!< Match Configuration Element dynamic field */
    kNETC_FDBCfgeMacthPortBitmap = 0x2, /*!< Match Configuration Element portBitmap field */
    kNETC_FDBCfgeMacthBoth       = 0x3  /*!< Match both dynamic field and portBitmap */
} netc_tb_fdb_sc_cfge_mc_t;

/*! @brief FDB table search criteria Activity Element Match Criteria */
typedef enum _netc_tb_fdb_sc_acte_mc
{
    kNETC_FDBActeMacthAny   = 0x0, /*!< Match any Activity Element Criteria */
    kNETC_FDBActeMatchExact = 0x1  /*!<  Exact match with Activity Element */
} netc_tb_fdb_sc_acte_mc_t;

/*! @brief FDB table search criteria format */
typedef struct _netc_tb_fdb_search_criteria
{
    uint32_t resumeEntryId;  /*!< Resume Entry ID, pass the NULL Entry ID when starting a search */
    netc_tb_fdb_keye_t keye; /*!< Key Element data which used to match against the table entries */
    netc_tb_fdb_cfge_t cfge; /*!< Configuration Element data which used to match against the table entries */
    struct
    {
        netc_tb_fdb_acte_t acte;            /*!< Activity Element data which used to match against the table entries */
        netc_tb_fdb_sc_keye_mc_t keyeMc : 2; /*!< Key Element data match criteria */
        uint8_t : 6;
        netc_tb_fdb_sc_cfge_mc_t cfgeMc : 3; /*!< Configuration Element data match criteria */
        uint8_t : 5;
        netc_tb_fdb_sc_acte_mc_t acteMc : 1; /*!< Activity Element data match criteria */
        uint8_t : 7;
    };
} netc_tb_fdb_search_criteria_t;

/*! @brief FDB table request data buffer */
typedef struct _netc_tb_fdb_req_data
{
    netc_tb_common_header_t commonHeader; /*!< Define update actions (use netc_tb_fdb_update_action_t)
                                                and query actions */
    union
    {
        uint32_t entryID;                        /*!< Active when access method is kNETC_EntryIDMatch */
        netc_tb_fdb_keye_t keye;                 /*!< Active when access method is kNETC_ExactKeyMatch */
        netc_tb_fdb_search_criteria_t sCriteria; /*!< Active when access method is kNETC_Search */
    };
    netc_tb_fdb_cfge_t cfge; /*!< Present only for commands which perform an update or add */
} netc_tb_fdb_req_data_t;

/*! @brief FDB table request response data buffer */
typedef struct _netc_tb_fdb_rsp_data
{
    uint32_t status;  /*!<  RESUME_ENTRY_ID, valid only in responses for commands which use the Search Access Method */
    uint32_t entryID; /*!< Present only for query command */
    netc_tb_fdb_keye_t keye; /*!< Present only for query command */
    netc_tb_fdb_cfge_t cfge; /*!< Present only for query command */
    netc_tb_fdb_acte_t acte; /*!< Present only for query command */
} netc_tb_fdb_rsp_data_t;

/*! @brief FDB table data buffer */
typedef struct _netc_tb_fdb_data
{
    union
    {
        netc_tb_fdb_req_data_t request;
        netc_tb_fdb_rsp_data_t response;
    };
} netc_tb_fdb_data_t;

/*! @brief FDB table entry config */
typedef struct _netc_tb_fdb_config
{
    netc_tb_fdb_keye_t keye;
    netc_tb_fdb_cfge_t cfge;
} netc_tb_fdb_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion FDB Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region L2 IPV4 Multicast Filter Table
#endif

/*! @brief L2 IPV4 Multicast Filter table key type */
typedef enum _netc_tb_l2mcf_key_type
{
    kNETC_IPv4ASMKey = 0U, /*!< Key consists of a filtering ID (FID) and destination multicast IPv4 address */
    kNETC_IPv4SSMKey       /*!< Key consists of a filtering ID (FID), IPv4 source address and multicast IPv4 destination
                              address */
} netc_tb_l2mcf_key_type_t;

/*! @brief L2 IPV4 Multicast Filter table key element */
typedef struct _netc_tb_l2mcf_keye
{
    netc_tb_l2mcf_key_type_t keyType : 4; /*!< Key Type */
    uint32_t : 12;
    uint32_t fid : 12; /*!< Filtering ID */
    uint32_t : 4;
    uint32_t ipv4DestAddr; /*!< IPv4 Destination Address */
    uint32_t ipv4SrcAddr;  /*!< IPv4 Source Address */
} netc_tb_l2mcf_keye_t;

/*! @brief L2 IPV4 Multicast Filter table search criteria Key Element Match Criteria */
typedef enum _etc_tb_l2mcf_sc_keye_mc
{
    kNETC_L2MCFKeyeMacthAny = 0x0, /*!< Match any Key Element Criteria */
    kNETC_L2MCFKeyeMacthFID = 0x1  /*!< Match Key Element FID */
} etc_tb_l2mcf_sc_keye_mc_t;

/*! @brief L2 IPV4 Multicast Filter table search criteria Configuration Element Match Criteria */
typedef enum _etc_tb_l2mcf_sc_cfge_mc
{
    kNETC_L2MCFCfgeMacthAny        = 0x0, /*!< Match any Configuration Element Criteria */
    kNETC_L2MCFCfgeMacthDynamic    = 0x1, /*!< Match Configuration Element dynamic field */
    kNETC_L2MCFCfgeMacthPortBitmap = 0x2, /*!< Match Configuration Element portBitmap field */
    kNETC_L2MCFCfgeMacthBoth       = 0x3  /*!< Match both dynamic field and portBitmap */
} etc_tb_l2mcf_sc_cfge_mc_t;

/*! @brief FDB table search criteria Activity Element Match Criteria */
typedef enum _etc_tb_l2mcf_sc_acte_mc
{
    kNETC_L2MCFActeMacthAny   = 0x0, /*!< Match any Activity Element Criteria */
    kNETC_L2MCFActeMatchExact = 0x1  /*!<  Exact match with Activity Element */
} etc_tb_l2mcf_sc_acte_mc_t;

/*! @brief L2 IPV4 Multicast Filter table config element */
typedef netc_tb_fdb_cfge_t netc_tb_l2mcf_cfge_t;

/*! @brief L2 IPV4 Multicast Filter table activity lement */
typedef netc_tb_fdb_acte_t netc_tb_l2mcf_acte_t;

/*! @brief L2 IPV4 Multicast Filter table search criteria format */
typedef struct _etc_tb_l2mcf_search_criteria
{
    uint32_t resumeEntryId;    /*!< Resume Entry ID, pass the NULL Entry ID when starting a search */
    netc_tb_l2mcf_keye_t keye; /*!< Key Element data which used to match against the table entries */
    netc_tb_l2mcf_cfge_t cfge; /*!< Configuration Element data which used to match against the table entries */
    struct
    {
        netc_tb_l2mcf_acte_t acte; /*!< Activity Element data which used to match against the table entries */
        etc_tb_l2mcf_sc_keye_mc_t keyeMc : 1; /*!< Key Element data match criteria */
        uint8_t : 7;
        etc_tb_l2mcf_sc_cfge_mc_t cfgeMc : 3; /*!< Configuration Element data match criteria */
        uint8_t : 5;
        etc_tb_l2mcf_sc_acte_mc_t acteMc : 1; /*!< Activity Element data match criteria */
        uint8_t : 7;
    };
} netc_tb_l2mcf_search_criteria_t;

/*! @brief L2 IPV4 Multicast Filter table request data buffer */
typedef struct _netc_tb_l2mcf_req_data
{
    netc_tb_common_header_t commonHeader;
    union
    {
        uint32_t entryID;
        netc_tb_l2mcf_search_criteria_t sCriteria;
        netc_tb_l2mcf_keye_t keye;
    };
    netc_tb_l2mcf_cfge_t cfge;
} netc_tb_l2mcf_req_data_t;

/*! @brief L2 IPV4 Multicast Filter table request response data buffer */
typedef struct _netc_tb_l2mcf_rsp_data
{
    uint32_t status;
    uint32_t entryID;
    netc_tb_l2mcf_keye_t keye;
    netc_tb_l2mcf_cfge_t cfge;
    netc_tb_l2mcf_acte_t acte;
} netc_tb_l2mcf_rsp_data_t;

/*! @brief L2 IPV4 Multicast Filter table data buffer */
typedef struct _netc_tb_l2mcf_data
{
    union
    {
        netc_tb_l2mcf_req_data_t request;
        netc_tb_l2mcf_rsp_data_t response;
    };
} netc_tb_l2mcf_data_t;

/*! @brief L2 IPV4 Multicast Filter table entry config */
typedef struct _netc_tb_l2mcf_config
{
    netc_tb_l2mcf_keye_t keye;
    netc_tb_l2mcf_cfge_t cfge;
} netc_tb_l2mcf_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion L2 IPV4 Multicast Filter Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Ingress Sequence Generation Table
#endif

/*! @brief Sequence Tag Type */
typedef enum _netc_tb_iseqg_sqtag
{
    kNETC_SqDraftRTag = 1U, /*!< 802.1CB draft 2.0 R-TAG. */
    kNETC_SqRTag,           /*!< 802.1CB R-TAG. */
    kNETC_SqHsrTag,         /*!< HSR Tag. */
} netc_tb_iseqg_sqtag_t;

/*! @brief Ingress Sequence Generation table config element */
typedef struct _netc_tb_iseqg_cfge
{
    netc_tb_iseqg_sqtag_t sqTag : 3; /*!< Sequence Tag Type. */
    uint8_t : 5;                     /*!< Reserved. */
} netc_tb_iseqg_cfge_t;

/*! @brief Ingress Sequence Generation table Sequence generation state element */
typedef struct _netc_tb_iseqg_sgse
{
    uint16_t sqgNum; /*!< Sequence Generation Number */
} netc_tb_iseqg_sgse_t;

/*! @brief Ingress Sequence Generation table request data buffer */
typedef struct _netc_tb_iseqg_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_iseqg_cfge_t cfge;
} netc_tb_iseqg_req_data_t;

/*! @brief Ingress Sequence Generation table request response data buffer */
typedef struct _netc_tb_iseqg_rsp_data
{
    uint32_t entryID;
    netc_tb_iseqg_cfge_t cfge;
    uint8_t : 8;
    netc_tb_iseqg_sgse_t sgse;
} netc_tb_iseqg_rsp_data_t;

/*! @brief Ingress Sequence Generation table data buffer */
typedef struct _netc_tb_iseqg_data
{
    union
    {
        netc_tb_iseqg_req_data_t request;
        netc_tb_iseqg_rsp_data_t response;
    };
} netc_tb_iseqg_data_t;

/*! @brief Ingress Sequence Generation table entry config */
typedef struct _netc_tb_iseqg_config
{
    uint32_t entryID;
    netc_tb_iseqg_cfge_t cfge;
} netc_tb_iseqg_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Ingress Sequence Generation Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Egress Sequence Recovery Table
#endif
/*! @brief Egress Sequence Recovery table Sequence Tag Type */
typedef enum _netc_tb_eseqr_sqtag
{
    kNETC_AcceptAnyTag    = 0U, /*!< Accept any incoming tag type (802.1CB draft 2.0 R-TAG, 802.1CB R-TAG or HSR Tag) */
    kNETC_AcceptDraftRTag = 1U, /*!< 802.1CB draft 2.0 R-TAG. */
    kNETC_AcceptRTag,           /*!< 802.1CB R-TAG. */
    kNETC_AcceptHsrTag,         /*!< HSR Tag. */
} netc_tb_eseqr_sqtag_t;

/*! @brief Egress Sequence Recovery table config element */
typedef struct _netc_tb_eseqr_cfge
{
    netc_tb_eseqr_sqtag_t sqTag : 3; /*!< Sequence Tag, specify the expected sequence tag type in the frame */
    uint32_t sqrTnsq : 1;            /*!< Sequence Recovery Take No Sequence */
    uint32_t sqrAlg : 1;             /*!< Sequence Recovery Algorithm, 0b = Vector algorithm, 1b = Match algorithm */
    uint32_t sqrType : 1; /*!< Sequence Recovery Function type, 0b = Sequence recovery function, 1b = Individual
                             recovery function */
    uint32_t : 2;
    uint32_t sqrHl : 7; /*!< Sequence Recovery History Length, valid if sqrAlg = 0b */
    uint32_t : 1;
    uint32_t sqrFwl : 12; /*!< Sequence Recovery Future Window Length, valid if sqrAlg = 0b */
    uint32_t : 4;
    uint32_t sqrTp : 12; /*!< Sequence Timeout Period, the unit is 1.048576 milliseconds */
    uint32_t : 20;
} netc_tb_eseqr_cfge_t;

/*! @brief Egress Sequence Recovery table statistic element */
typedef struct _netc_tb_eseqr_stse
{
    uint32_t inOrderPackets[2];    /*!< In Order Packets */
    uint32_t outOfOrderPackets[2]; /*!< Out of Order Packets */
    uint32_t roguePackets[2];      /*!< Rogue Packets */
    uint32_t duplicatePackets[2];  /*!< Duplicate Packets */
    uint32_t lostPackets[2];       /*!< Lost Packets */
    uint32_t taglessPackets[2];    /*!< Tag-Less Packets */
    uint32_t esqrResetCounts;      /*!< Sequence Recovery Resets */
} netc_tb_eseqr_stse_t;

/*! @brief Egress Sequence Recovery table sequence recovery state element */
typedef struct _netc_tb_eseqr_srse
{
    uint32_t sqrNum : 16; /*!< Sequence Recovery Number */
    uint32_t takeAny : 1; /*!< Take Any */
    uint32_t lce : 1;     /*!< Lost Count Enable */
    uint32_t sqrTs : 12;  /*!< Sequence Recovery Timestamp */
    uint32_t : 2;
    uint32_t sqrHistory[4]; /*!< Recovery History bit vector, each bit corresponding to sequence numbers, bit 1 means a
                               packet with that sequence number has been previously received */
} netc_tb_eseqr_srse_t;

/*! @brief Egress Sequence Recovery table request data buffer */
typedef struct _netc_tb_eseqr_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_eseqr_cfge_t cfge;
} netc_tb_eseqr_req_data_t;

/*! @brief Egress Sequence Recovery table request response data buffer */
typedef struct _netc_tb_eseqr_rsp_data
{
    uint32_t entryID;
    netc_tb_eseqr_stse_t stse;
    netc_tb_eseqr_cfge_t cfge;
    netc_tb_eseqr_srse_t srse;
} netc_tb_eseqr_rsp_data_t;

/*! @brief Egress Sequence Recovery table data buffer */
typedef struct _netc_tb_eseqr_data
{
    union
    {
        netc_tb_eseqr_req_data_t request;
        netc_tb_eseqr_rsp_data_t response;
    };
} netc_tb_eseqr_data_t;

/*! @brief Egress Sequence Recovery table entry config */
typedef struct _netc_tb_eseqr_config
{
    uint32_t entryID;
    netc_tb_eseqr_cfge_t cfge;
} netc_tb_eseqr_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Egress Sequence Recovery Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Time Gate Scheduling Table
#endif

/*! @brief Time Gate Scheduling Table maximum gate control list length (TGSTCAPR[MAX_GCL_LEN]) */
#define NETC_TB_TGS_MAX_ENTRY (0x100U)

/*! @brief Time Gate Scheduling table entry ID for switch and ENETC */
typedef enum _netc_tb_tgs_entry_id
{
    kNETC_TGSSwtPort0 = 0U, /*!< Switch PORT 0 entry ID */
    kNETC_TGSSwtPort1,      /*!< Switch PORT 1 entry ID */
    kNETC_TGSSwtPort2,      /*!< Switch PORT 2 entry ID */
    kNETC_TGSSwtPort3,      /*!< Switch PORT 3 entry ID */
    kNETC_TGSSwtPort4,      /*!< Switch PORT 4 entry ID */
    kNETC_TGSEnetc0Port,    /*!< ENETC 0 port entry ID */
    kNETC_TGSEnetc1Port     /*!< ENETC 1 port entry ID */
} netc_tb_tgs_entry_id_t;

/*! @brief Administrative gate operation type */
typedef enum _netc_tb_tgs_gate_type
{
    kNETC_SetGateStates = 0U, /*!< HoldRequest is unchanged */
    kNETC_SetAndHoldMac,      /*!< HoldRequest is set to value hold, only active when enable preemption */
    kNETC_SetAndReleaseMac    /*!< HoldRequest is set to value release, only active when enable preemption */
} netc_tb_tgs_gate_type_t;

/*! @brief Defines the Time Gate Scheduling gate control entry structure. */
typedef struct _netc_tgs_gate_entry
{
    uint32_t interval; /*!< Entry Time Interval */
    union
    {
        struct
        {
            uint32_t tcGateState : 8; /*!< Traffic Class Gate States for Gate Entry, 8 bits for 8 Traffic
                                           Class , 0b means Gate closed, 1b means Gate open */
            uint32_t : 8;
            netc_tb_tgs_gate_type_t operType : 4; /*!< Gate operation type ( IEEE 802.1Q-2018) field for gate
                                                    control list entry i */
            uint32_t : 12;
        };
        uint32_t gate; /*!< Entry Gate Mask*/
    };
} netc_tgs_gate_entry_t;

/*! @brief Time Gate Scheduling table config element */
typedef struct _netc_tb_tgs_cfge
{
    uint64_t adminBaseTime;           /*!< Administrative Base Time */
    uint32_t adminCycleTime;          /*!< Administrative Cycle Time */
    uint32_t adminCycleTimeExt;       /*!< Administrative Cycle Time Extension */
    uint32_t adminControlListLength;  /*!< Administrative Control List Length */
    netc_tgs_gate_entry_t adminGcl[]; /*!< Administrative Gate control list */
} netc_tb_tgs_cfge_t;

/*! @brief Time Gate Scheduling table statistic element */
typedef struct _netc_tb_tgs_olse
{
    uint64_t configChangeTime;       /*!< The time at which this operational gate control list became active */
    uint64_t configChangeError;      /*!< Count of error configuration changes */
    uint64_t operBaseTime;           /*!< Operational Base Time */
    uint32_t operCycleTime;          /*!< Operational Cycle Time */
    uint32_t operCycleTimeExt;       /*!< Operational Cycle Time Extension */
    uint32_t operControlListLength;  /*!< Operational Control List Length */
    netc_tgs_gate_entry_t operGcl[]; /*!< Operational Gate control list */
} netc_tb_tgs_olse_t;

/*! @brief Time Gate Scheduling table request data buffer */
typedef struct _netc_tb_tgs_req_data
{
    netc_tb_common_header_t commonHeader;
    netc_tb_tgs_entry_id_t entryID;
    netc_tb_tgs_cfge_t cfge; /*!< Present only for commands which perform a update */
} netc_tb_tgs_req_data_t;

#if (defined(__CC_ARM) || defined(__ARMCC_VERSION))
/* Ignore the "field with variable sized type not at the end of a struct or class" warning. */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-variable-sized-type-not-at-end"
#endif
/*! @brief Time Gate Scheduling table request response data buffer */
typedef struct _netc_tb_tgs_rsp_data
{
    uint64_t configChangeTime;
    uint32_t res0;
    uint32_t entryID;        /*!< Present only for commands which perform a query */
    netc_tb_tgs_cfge_t cfge; /*!< Present only for commands which perform a query */
    netc_tb_tgs_olse_t olse; /*!< Present only for commands which perform a query */
} netc_tb_tgs_rsp_data_t;
#if (defined(__CC_ARM) || defined(__ARMCC_VERSION))
#pragma clang diagnostic pop
#endif

/*! @brief Time Gate Scheduling table data buffer, set with max size */
typedef struct _netc_tb_tgs_data
{
    union
    {
        netc_tb_tgs_req_data_t request;
        netc_tb_tgs_rsp_data_t response;
        struct
        {
            uint32_t rel0[18];
            netc_tgs_gate_entry_t res1[NETC_TB_TGS_MAX_ENTRY];
        };
    };
} netc_tb_tgs_data_t;

/*! @brief Time Gate Scheduling table entry gate control list structure */
typedef struct _netc_tb_tgs_gcl
{
    netc_tb_tgs_entry_id_t entryID;
    uint64_t baseTime;             /*!< Base Time */
    uint32_t cycleTime;            /*!< Cycle Time */
    uint32_t extTime;              /*!< Cycle Time Extension */
    uint32_t numEntries;           /*!< Control List entry numbers */
    netc_tgs_gate_entry_t *gcList; /*!< Pointer to time gate control list array */
} netc_tb_tgs_gcl_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Time Gate Scheduling Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Egress Treatment Table
#endif
/*! @brief Egress Frame Modification entry mode */
typedef enum _netc_tb_et_efm_mode
{
    kNETC_NormalMode = 0U, /*!< Egress Frame Modification entry use normal/Default mode */
    kNETC_L2Act1,          /*!< Egress Frame Modification entry l2Act = kNETC_UseSpecPlayload */
    kNETC_PldAct1          /*!< Egress Frame Modification entry pldAct = kNETC_ReplAllEthPld */
} netc_tb_et_efm_mode_t;

/*! @brief Egress Sequence Actions */
typedef enum _netc_tb_et_esq_act
{
    kNETC_NoEsqAction  = 0U, /*!< No Egress Sequence Action required */
    kNETC_HasEsqAction = 2U, /*!< Has Egress Sequence Recovery action */
} netc_tb_et_esq_act_t;

/*! @brief Egress Counter Action */
typedef enum _netc_tb_et_ec_act
{
    kNETC_NoEcCounter = 0U, /*!< Do not increment egress frame counter */
    kNETC_HasEcCounter      /*!< Increment egress frame counter */
} netc_tb_et_ec_act_t;

/*! @brief Egress Treatment table config element */
typedef struct _netc_tb_et_cfge
{
    netc_tb_et_efm_mode_t efmMode : 2; /*!< Egress Frame Modification mode */
    uint8_t : 2;
    netc_tb_et_esq_act_t esqa : 2; /*!< Egress Sequence Actions */
    netc_tb_et_ec_act_t eca : 2;   /*!< Egress Counter Action */
    uint8_t : 1;                   /*!< Reserve for data align */
    uint8_t efmLenChange : 7;      /*!< Egress Frame Modification Length Change, specified in units of bytes using a 2's
                                       complement notation */
    uint16_t efmDataLen : 11;      /*!< Egress Frame Modification Data Length */
    uint16_t : 5;
    uint32_t efmEID;     /*!< Egress Frame Modification Entry Id */
    uint32_t ecEID;      /*!< Egress Count Table Entry ID */
    uint32_t esqaTgtEID; /*!< Egress Sequence Actions Target Entry ID, active when esqa = 10b */
} netc_tb_et_cfge_t;

/*! @brief Egress Treatment table request data buffer */
typedef struct _netc_tb_et_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_et_cfge_t cfge;
} netc_tb_et_req_data_t;

/*! @brief Egress Treatment table request response data buffer */
typedef struct _netc_tb_et_rsp_data
{
    uint32_t entryID;
    netc_tb_et_cfge_t cfge;
} netc_tb_et_rsp_data_t;

/*! @brief Egress Treatment table data buffer */
typedef struct _netc_tb_et_data
{
    union
    {
        netc_tb_et_req_data_t request;
        netc_tb_et_rsp_data_t response;
    };
} netc_tb_et_data_t;

/*! @brief Egress Treatment table entry config */
typedef struct _netc_tb_et_config
{
    uint32_t entryID;
    netc_tb_et_cfge_t cfge;
} netc_tb_et_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Egress Treatment Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region ETM Class Queue Table
#endif
/*! @brief ETM Class Queue table entry ID macro, cqID is represents the Class Queue ID ,rang in 0 ~ 7, portID is Switch
 * ID, rang in 0 ~ 4 */
#define NETC_TB_ETM_CQ_ENTRY_ID(portID, cqID) (((uint32_t)(portID) << 4U) | ((cqID)&0x7U))

/*! @brief ETM Class Queue table Update Actions */
typedef enum _netc_tb_etmcq_update_action
{
    kNETC_CQCfgEUpdate = 0x1U, /*!< Configuration Element Update */
    kNETC_CQStsEUpdate =
        0x2U /*!< Statistics Element Update, all counters (except FRM_CNT) within the Statistics Element are reset */
} netc_tb_etmcq_update_action_t;

/*! @brief ETM Class Queue table config element */
typedef struct _netc_tb_etmcq_cfge
{
    netc_hw_etm_class_queue_idx_t cq2cgMap : 4; /*!< Class Queue to Congestion Group Mapping */
    uint8_t res0 : 4;
} netc_tb_etmcq_cfge_t;

/*! @brief ETM Class Queue table statistic element */
typedef struct _netc_tb_etmcq_stse
{
    uint32_t rejByteCnt[2];   /*!< Reject Byte Count */
    uint32_t rejFrameCnt[2];  /*!< Reject Frame Count */
    uint32_t deqByteCnt[2];   /*!< Dequeue Byte Count */
    uint32_t deqFrameCnt[2];  /*!< Dequeue Frame Count */
    uint32_t dropByteCnt[2];  /*!< Dropped Frames, Memory Lost */
    uint32_t dropFrameCnt[2]; /*!< Dropped Frames, Memory Recovered */
    uint32_t frmCnt;          /*!< Frame Count */
} netc_tb_etmcq_stse_t;

/*! @brief ETM Class Queue table request data buffer */
typedef struct _netc_tb_etmcq_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_etmcq_cfge_t cfge;
} netc_tb_etmcq_req_data_t;

/*! @brief ETM Class Queue table request response data buffer */
typedef struct _netc_tb_etmcq_rsp_data
{
    uint32_t entryID;
    netc_tb_etmcq_stse_t stse;
    netc_tb_etmcq_cfge_t cfge;
} netc_tb_etmcq_rsp_data_t;

/*! @brief ETM Class Queue table data buffer */
typedef struct _netc_tb_etmcq_data
{
    union
    {
        netc_tb_etmcq_req_data_t request;
        netc_tb_etmcq_rsp_data_t response;
    };
} netc_tb_etmcq_data_t;

/*! @brief ETM Class Queue table entry config */
typedef struct _netc_tb_etmcq_config
{
    uint32_t entryID; /*!< Need use NETC_TB_ETM_CQ_ENTRY_ID macro to create entry ID */
    netc_tb_etmcq_cfge_t cfge;
} netc_tb_etmcq_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion ETM Class Queue Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region ETM Class Scheduler Table
#endif

/*! @brief ETM Class Scheduler table entry ID */
typedef enum _netc_tb_etmcs_entry_id
{
    kNETC_CSSwtPort0 = 0U, /*!< CS Switch PORT 0 entry ID */
    kNETC_CSSwtPort1,      /*!< CS Switch PORT 1 entry ID */
    kNETC_CSSwtPort2,      /*!< CS Switch PORT 2 entry ID */
    kNETC_CSSwtPort3,      /*!< CS Switch PORT 3 entry ID */
    kNETC_CSSwtPort4       /*!< CS Switch PORT 4 entry ID */
} netc_tb_etmcs_entry_id_t;

/*! @brief ETM Class Scheduler table Class queue assignment to scheduler inputs mode */
typedef enum _netc_tb_etmcs_ca_assg
{
    kNETC_CQ7AssignToSchedIn15 = 0U, /*!< CQ 7 assignment to scheduler input 15, means all CQ use strict priority */
    kNETC_CQ7AssignToSchedIn14,      /*!< CQ 7 assignment to scheduler input 14 */
    kNETC_CQ7AssignToSchedIn13,      /*!< CQ 7 assignment to scheduler input 13 */
    kNETC_CQ7AssignToSchedIn12,      /*!< CQ 7 assignment to scheduler input 12 */
    kNETC_CQ7AssignToSchedIn11,      /*!< CQ 7 assignment to scheduler input 11 */
    kNETC_CQ7AssignToSchedIn10,      /*!< CQ 7 assignment to scheduler input 10 */
    kNETC_CQ7AssignToSchedIn9,       /*!< CQ 7 assignment to scheduler input 9 */
    kNETC_CQ7AssignToSchedIn8,       /*!< CQ 7 assignment to scheduler input 8 */
    kNETC_CQ7AssignToSchedIn7        /*!< CQ 7 assignment to scheduler input 7, means all CQ use weighted fair */
} netc_tb_etmcs_ca_assg_t;

/*! @brief ETM Class Scheduler table config element */
typedef struct _netc_tb_etmcs_cfge
{
    netc_tb_etmcs_ca_assg_t cqAssg : 4; /*!< Class Queue Assignment, input 0 to 7 are weighted fair whereby input 8 to
                                           15 are strict priority */
    uint32_t : 12;
    uint32_t oal : 11; /*!< Overead accounting length */
    uint32_t : 5;
    struct
    {
        uint8_t xCode : 3; /*!< Weight code x value */
        uint8_t yCode : 5; /*!< Weight code y value */
    } wbfsWeight[8];       /*!< Weight for scheduler input 0 ~ 7, effective weight is: (2^x)/(1-(y/64)) */
} netc_tb_etmcs_cfge_t;

/*! @brief ETM Class Scheduler table request data buffer */
typedef struct _netc_tb_etmcs_req_data
{
    netc_tb_common_header_t commonHeader;
    netc_tb_etmcs_entry_id_t entryID; /*!< One class scheduler entry per port  */
    netc_tb_etmcs_cfge_t cfge;
} netc_tb_etmcs_req_data_t;

/*! @brief ETM Class Scheduler table request response data buffer */
typedef struct _netc_tb_etmcs_rsp_data
{
    netc_tb_etmcs_entry_id_t entryID;
    netc_tb_etmcs_cfge_t cfge;
} netc_tb_etmcs_rsp_data_t;

/*! @brief ETM Class Scheduler table data buffer */
typedef struct _netc_tb_etmcs_data
{
    union
    {
        netc_tb_etmcs_req_data_t request;
        netc_tb_etmcs_rsp_data_t response;
    };
} netc_tb_etmcs_data_t;

/*! @brief ETM Class Scheduler table entry config */
typedef struct _netc_tb_etmcs_config
{
    netc_tb_etmcs_entry_id_t entryID; /*!< One class scheduler entry per port  */
    netc_tb_etmcs_cfge_t cfge;
} netc_tb_etmcs_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion ETM Class Scheduler Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region ETM Congestion Group Table
#endif
/*! @brief ETM Congestion Group table entry ID macro, cgID is represents the Congestion Group ID ,rang in 0 ~ 7, portID
 * is Switch ID, rang in 0 ~ 4 */
#define NETC_TB_ETM_CG_ENTRY_ID(portID, cgID) (((uint32_t)(portID) << 4U) | ((cgID)&0x7U))

/*! @brief ETM Congestion Group table config element */
typedef struct _netc_tb_etmcg_cfge
{
    uint16_t tdDr0En : 1; /*!< Tail drop enable for DR0 Frame */
    uint16_t tdDr1En : 1; /*!< Tail drop enable for DR1 Frame */
    uint16_t tdDr2En : 1; /*!< Tail drop enable for DR2 Frame */
    uint16_t tdDr3En : 1; /*!< Tail drop enable for DR3 Frame */
    uint16_t oal : 12;    /*!< Overhead accounting length, 2's complement value (range -2048 to +2047)  */
    struct
    {
        uint16_t tn : 5; /*!< TA */
        uint16_t ta : 8; /*!< Tn */
        uint16_t : 3;
    } tdDRThresh[4]; /*!< Tail Drop Threshold (TA * 2^Tn) for DR0 ~ DR3 Frames, valid if tdDrnEn = 1b */
} netc_tb_etmcg_cfge_t;

/*! @brief ETM Congestion Group table statistic element */
typedef struct _netc_tb_etmcg_stse
{
    uint32_t byteCount[2]; /*!< Number of bytes currently in use in all class queues that are members of this group. */
} netc_tb_etmcg_stse_t;

/*! @brief ETM Congestion Group table request data buffer */
typedef struct _netc_tb_etmcg_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_etmcg_cfge_t cfge;
} netc_tb_etmcg_req_data_t;

/*! @brief ETM Congestion Group table request response data buffer */
typedef struct _netc_tb_etmcg_rsp_data
{
    uint32_t entryID;
    netc_tb_etmcg_stse_t stse;
    netc_tb_etmcg_cfge_t cfge;
} netc_tb_etmcg_rsp_data_t;

/*! @brief ETM Congestion Group table data buffer */
typedef struct _netc_tb_etmcg_data
{
    union
    {
        netc_tb_etmcg_req_data_t request;
        netc_tb_etmcg_rsp_data_t response;
    };
} netc_tb_etmcg_data_t;

/*! @brief ETM Congestion Group table entry config */
typedef struct _netc_tb_etmcg_config
{
    uint32_t entryID; /*!< Need use NETC_TB_ETM_CG_ENTRY_ID macro to create entry ID */
    netc_tb_etmcg_cfge_t cfge;
} netc_tb_etmcg_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion ETM Congestion Group Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Egress Count Table
#endif

/*! @brief Egress Count table statistic element */
typedef struct _netc_tb_ec_stse
{
    uint32_t enqFrmCnt[2]; /*!< Enqueued Frame Count */
    uint32_t rejFrmCnt[2]; /*!< Rejected Frame Count */
} netc_tb_ec_stse_t;

/*! @brief Egress Count table request data buffer */
typedef struct _netc_tb_ec_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
} netc_tb_ec_req_data_t;

/*! @brief Egress Count table request response data buffer */
typedef struct _netc_tb_ec_rsp_data
{
    uint32_t entryID;
    netc_tb_ec_stse_t stse;
} netc_tb_ec_rsp_data_t;

/*! @brief Egress Count table data buffer */
typedef struct _netc_tb_ec_data
{
    union
    {
        netc_tb_ec_req_data_t request;
        netc_tb_ec_rsp_data_t response;
    };
} netc_tb_ec_data_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Egress Count Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Buffer Pool Table
#endif

/*! @brief Buffer pool and shared buffer pool threshold macro, the threshold = MANT*2^EXP, uint is internal memory words
 * (avergae of 20 bytes each) */
#define NETC_TB_BP_THRESH(mant, exp) (((uint32_t)((mant)&0xFF) << 4U) | ((exp)&0xF))

/*! @brief Buffer Pool Flow Control (FC) Configuration */
typedef enum _netc_tb_bp_fc_cfg
{
    kNETC_FlowCtrlDisable = 0U, /*!< Flow Control disabled */
    kNETC_FlowCtrlWithBP,       /*!< Flow Control enabled using only buffer pool FC state. */
    kNETC_FlowCtrlWithSBP,      /*!< Flow Control enabled using only shared buffer pool FC state. */
    kNETC_FlowCtrlWithBPAndSBP  /*!<  Flow Control enabled using both buffer pool and shared buffer pool FC state, only
                                   both 1 trigger the Flow Control ON */
} netc_tb_bp_fc_cfg_t;

/*! @brief Buffer Pool table config element */
typedef struct _netc_tb_bp_cfge
{
    bool sbpEn : 1; /*!< Shared Buffer Pool Enable, set true measn a shared buffer pool is associated with this buffer
                       pool */
    netc_tb_bp_fc_cfg_t gcCfg : 2; /*!< Flow Control (FC) Configuration */
    uint8_t : 5;
    uint8_t pfcVector;       /*!< Priority Flow Control (PFC) Vector, not support in NETC 3.0 and 3.1 version */
    uint16_t maxThresh : 12; /*!< Maximum Threshold, value 0 means disable maximum threshold checking, use
                                NETC_TB_BP_THRESH macro to set this value */
    uint16_t : 4;
    uint16_t fcOnThresh : 12; /*!< Flow Control On Threshold, If the buffer pool usage crosses this threshold, and if
                                fcOnThresh is greater than fcOffThresh, the flow control state of the buffer pool
                                is set to 1, use NETC_TB_BP_THRESH macro to set this value. */
    uint16_t : 4;
    uint16_t fcOffThresh : 12; /*!< Flow Control Off Threshold, If buffer pool usage drops to this threshold or below,
                                      the flow control state of the buffer pool is set to 0, , use NETC_TB_BP_THRESH
                                  macro to set this value */
    uint16_t : 4;
    uint32_t sbpThresh : 12; /*!< Shared Buffer Pool Threshold, use NETC_TB_BP_THRESH macro to set this value */
    uint32_t : 20;
    uint32_t sbpEid;  /*!< Shared Buffer Pool Entry ID, valid if sbpEn is true */
    uint32_t fcPorts; /*!< Flow Control Port bitmap, indicates which ports are to be flow controlled for this
                            buffer pool */
} netc_tb_bp_cfge_t;

/*! @brief Buffer Pool table State Element Data*/
typedef struct _netc_tb_bp_bpse
{
    uint32_t amountUsed; /*!< Amount Used, number of internal memory words (average of 20 bytes each) currently in use
                              in this buffer pool. */
    uint32_t amountUsedHWM; /*!< Amount Used High Watermark, value sticks at the highest AMOUNT_USED seen since the last
                               watermark reset */
    uint32_t fcState : 1;   /*!< Flow Control (FC) State, ON (1) or OFF (0)  */
    uint32_t bpd : 1; /*!< Buffer Pool Disabled, 1 means the  buffer pool has been disabled due to an uncorrectable ECC
                         error */
    uint32_t : 30;
} netc_tb_bp_bpse_t;

/*! @brief Buffer Pool table request data buffer */
typedef struct _netc_tb_bp_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_bp_cfge_t cfge;
} netc_tb_bp_req_data_t;

/*! @brief Buffer Pool table request response data buffer */
typedef struct _netc_tb_bp_rsp_data
{
    uint32_t entryID;
    netc_tb_bp_bpse_t bpse;
    netc_tb_bp_cfge_t cfge;
} netc_tb_bp_rsp_data_t;

/*! @brief Buffer Pool table data buffer */
typedef struct _netc_tb_bp_data
{
    union
    {
        netc_tb_bp_req_data_t request;
        netc_tb_bp_rsp_data_t response;
    };
} netc_tb_bp_data_t;

/*! @brief Buffer Pool table entry config */
typedef struct _netc_tb_bp_config
{
    uint32_t entryID;       /*!< Buffer pool ID, range in 0 ~ (SWT_GetBPTableEntryNum() - 1) */
    netc_tb_bp_cfge_t cfge; /*!< Buffer Pool table config element */
} netc_tb_bp_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Buffer Pool Table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Shared Buffer Pool Table
#endif
/*! @brief Shared Buffer Pool table config element */
typedef struct _netc_tb_sbp_cfge
{
    uint32_t : 16;
    uint32_t maxThresh : 12; /*!< Maximum Threshold, If shared buffer pool usage is greater than or equal to this
                                threshold, use NETC_TB_BP_THRESH macro to set this value */
    uint32_t : 4;
    uint16_t fcOnThresh : 12; /*!< Flow Control On Threshold, If the shared buffer pool usage crosses this threshold,
                                and if fcOnThresh is greater than fcOffThresh, the flow control state of the buffer pool
                                is set to 1, use NETC_TB_BP_THRESH macro to set this value.  */
    uint16_t : 4;
    uint16_t fcOffThresh : 12; /*!< Flow Control Off Threshold, If shared buffer pool usage drops to this threshold or
                                  below, the flow control state of the buffer pool is set to 0, use NETC_TB_BP_THRESH
                                  macro to set this value */
    uint16_t : 4;
} netc_tb_sbp_cfge_t;

/*! @brief Shared Buffer Pool table State Element Data*/
typedef struct _netc_tb_sbp_sbpse
{
    uint32_t amountUsed; /*!< Amount Used, number of internal memory words (average of 20 bytes each) currently in use
                              in this buffer pool. */
    uint32_t amountUsedHWM; /*!< Amount Used High Watermark, value sticks at the highest AMOUNT_USED seen since the last
                               watermark reset */
    uint32_t fcState : 1;   /*!< Flow Control (FC) State, ON (1) or OFF (0)  */
    uint32_t : 31;
} netc_tb_sbp_sbpse_t;

/*! @brief Shared Buffer Pool table request data buffer */
typedef struct _netc_tb_sbp_req_data
{
    netc_tb_common_header_t commonHeader;
    uint32_t entryID;
    netc_tb_sbp_cfge_t cfge;
} netc_tb_sbp_req_data_t;

/*! @brief Shared Buffer Pool table request response data buffer */
typedef struct _netc_tb_sbp_rsp_data
{
    uint32_t entryID;
    netc_tb_sbp_sbpse_t sbpse;
    netc_tb_sbp_cfge_t cfge;
} netc_tb_sbp_rsp_data_t;

/*! @brief Shared Buffer Pool table data buffer */
typedef struct _netc_tb_sbp_data
{
    union
    {
        netc_tb_sbp_req_data_t request;
        netc_tb_sbp_rsp_data_t response;
    };
} netc_tb_sbp_data_t;

/*! @brief Shared Buffer Pool table entry config */
typedef struct _netc_tb_sbp_config
{
    uint32_t entryID;        /*!< Shared Buffer pool ID, range in 0 ~ (SWT_GetSBPTableEntryNum() - 1) */
    netc_tb_sbp_cfge_t cfge; /*!< Shared Buffer Pool table config element */
} netc_tb_sbp_config_t;

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Shared Buffer Pool Table
#endif

/*! @brief Table common data buffer */
typedef union _netc_tb_data_buffer
{
    netc_tb_tgs_data_t tgs;     /*!< Time Gate Scheduling table data buffer */
    netc_tb_rp_data_t rp;       /*!< Rate Policer table data buffer */
    netc_tb_ipf_data_t ipf;     /*!< Ingress Port filter table data buffer */
    netc_tb_fdb_data_t fdb;     /*!< FDB table data buffer */
    netc_tb_l2mcf_data_t l2mcf; /*!< L2 IPV4 Multicast Filter table data buffer */
    netc_tb_vf_data_t vf;       /*!<  VLAN Filter table data buffer */
    netc_tb_isi_data_t isi;     /*!< Ingress Stream Identification table data buffer */
    netc_tb_is_data_t is;       /*!< Ingress Stream table data buffer */
    netc_tb_isf_data_t isf;     /*!< Ingress Stream Filter table data buffer */
    netc_tb_isc_data_t isc;     /*!< Ingress Stream Count table data buffer */
    netc_tb_sgi_data_t sgi;     /*!< Stream Gate Instance table data buffer */
    netc_tb_sgcl_data_t sgcl;   /*!< Stream Gate Control List table data buffer */
    netc_tb_fm_data_t fm;       /*!< Frame Modification table data buffer */
    netc_tb_fmd_data_t fmd;     /*!< Frame Modification Data table data buffer */
    netc_tb_et_data_t et;       /*!< Egress Treatment table data buffer */
    netc_tb_ec_data_t ec;       /*!< Egress Count table data buffer */
    netc_tb_etmcq_data_t cq;    /*!< ETM Class Queue table data buffer */
    netc_tb_etmcs_data_t cs;    /*!< ETM Class Scheduler table data buffer */
    netc_tb_etmcg_data_t cg;    /*!< ETM Class Group table data buffer */
    netc_tb_iseqg_data_t iseqg; /*!< Ingress Sequence Generation table data buffer */
    netc_tb_eseqr_data_t eseqr; /*!< Egress Sequence Recovery table data buffer */
    netc_tb_bp_data_t bp;       /*!< Buffer Pool table data buffer */
    netc_tb_sbp_data_t sbp;     /*!< Shared Buffer Pool table data buffer */
} netc_tb_data_buffer_t;

/*! @} */ // end of netc_hw_table
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_table
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_si
#endif
/*! @addtogroup netc_hw_si
 * @{
 */
/*! @brief Macro to cover VLAN PCP, DEI value to internal used pcpDei value. */
#define NETC_VLAN_PCP_DEI_VALUE(pcp, dei) (((uint8_t)((pcp)&0x7U) << 1U) | ((dei)&0x1U))

/*! @brief VLAN Ethertypes. */
typedef enum _netc_hw_enetc_si_vlan_type
{
    kNETC_ENETC_StanCVlan   = 0x1U, /*!< Standard C-VLAN 0x8100. */
    kNETC_ENETC_StanSVlan   = 0x2U, /*!< Standard S-VLAN 0x88A8. */
    kNETC_ENETC_CustomVlan1 = 0x4U, /*!< Custom VLAN as defined by CVLANR1[ETYPE]. */
    kNETC_ENETC_CustomVlan2 = 0x8U  /*!< Custom VLAN as defined by CVLANR2[ETYPE]. */
} netc_hw_enetc_si_vlan_type;

/*! @brief SI receive BD ring group index. */
typedef enum _netc_hw_enetc_si_rxr_group
{
    kNETC_SiBDRGroupOne = 0U, /*!< SI Rx BD ring group index one. */
    kNETC_SiBDRGroupTwo       /*!< SI Rx BD ring group index two. */
} netc_hw_enetc_si_rxr_group;

/*!
 * @brief Station Interface configuration.
 *
 */
typedef struct _netc_hw_enetc_si_config
{
    uint32_t bandWeight : 4;        /*!< Station interface traffic class bandwidth weight */
    uint32_t vlanCtrl : 4;          /*!< VLAN Ethertypes can be inserted by the SI driver, set with OR of @ref
                                       netc_hw_enetc_si_vlan_type. */
    uint32_t antiSpoofEnable : 1;   /*!< Anti-spoofing enable */
    uint32_t vlanInsertEnable : 1;  /*!< Software SI-based VLAN Insertion enable, avtive when enSIBaseVlan is true */
    uint32_t vlanExtractEnable : 1; /*!< SI-based VLAN removed from frame enable, avtive when enSIBaseVlan is true */
    uint32_t sourcePruneEnable : 1; /*!< Source pruning enable */
    uint32_t rxRingUse : 7; /*!< Number of Rx Rings to be used, when enable Rx ring group, this equal to the sum of all
                          Rx group rings. */
    uint32_t txRingUse : 7; /*!< Number of Tx Rings to be used, note that when SI is Switch management ENETC SI, the
                          number not include Tx ring 0. */
    uint32_t valnToIpvEnable : 1; /*!< Enable the VLAN PCP/DEI value (use NETC_VLAN_PCP_DEI_VALUE marco) to internal
                                     priority value mapping. */
    uint32_t rxBdrGroupNum : 2;   /*!< Rx BD ring group number, range in 0 ~ 2. */
    uint32_t ringPerBdrGroup : 3; /*!< The ring number in every Rx BD ring group, range in 1 ~ 8, active when
                                    rxBdrGroupNum not equal zero. */
    netc_hw_enetc_si_rxr_group
        defaultRxBdrGroup; /*!< The selected Rx BD ring group, active when rxBdrGroupNum not equal zero. */

    uint8_t vlanToIpvMap[16]; /*!< Frame VLAN pcp|dei to IPV mapping, active when valnToIpvEnable is true. */
    uint8_t ipvToRingMap[8];  /*!< BD ring used within the default Rx BD ring group for IPV n, active when rxBdrGroupNum
                                 not equal zero. */
    uint8_t vsiTcToTC[8]; /*!< Maps the VSI traffic class to transmit traffic class, done after the ENETC txPrio to TC
                             mapping, only available for VSI. */
    bool enSIBaseVlan;    /*!< Enable use SI-based VLAN information. */
    netc_enetc_vlan_tag_t siBaseVlan; /*!< SI-based VLAN information, active when enSIBaseVlan is true. */
} netc_hw_enetc_si_config_t;

/*! @brief L2 Mac Filter Configuration for SI. */
typedef struct _netc_si_l2mf_config
{
    bool macUCPromis; /*!< Enable/Disable MAC unicast promiscuous. */
    bool macMCPromis; /*!< Enable/Disable MAC multicast promiscuous. */
    bool rejectUC;    /*!< Reject Unicast. */
    bool rejectMC;    /*!< Reject Multicast. */
    bool rejectBC;    /*!< Reject Broadcast. */
} netc_si_l2mf_config_t;

/*! @brief L2 VLAN Filter Configuration for SI. */
typedef struct _netc_si_l2vf_config
{
    bool acceptUntagged;  /*!< Accept/Reject untagged frame. */
    bool enPromis;        /*!< Enable/Disable VLAN promiscuous. */
    bool useOuterVlanTag; /*!< Use outer/inner VLAN tag for filtering. */
} netc_si_l2vf_config_t;

/*! @brief SI frame drop statistic struct. */
typedef struct _netc_si_discard_statistic
{
    uint32_t programError; /*!< Due to programming error ( non-existing BD ring or non-existing group, or SI disabled or
                              BD ring disabled). */
    uint32_t busError;     /*!< Due to system bus error. */
    uint32_t lackBD[14];   /*!< Due to lack of Rx BDs available. */
} netc_si_discard_statistic_t;

/*! @brief SI traffic statistic struct. */
typedef struct _netc_si_traffic_statistic
{
    uint64_t rxOctet;
    uint64_t rxFrame;
    uint64_t rxFrameUnicast;
    uint64_t rxFrameMulticast;
    uint64_t txOctet;
    uint64_t txFrame;
    uint64_t txFrameUnicast;
    uint64_t txFrameMulticast;
} netc_si_traffic_statistic_t;

/*! @brief SI Configuration. */
typedef struct _netc_si_config
{
    uint32_t tcBWWeight; /*!< SI traffic class bandwidth weight. */
} netc_si_config_t;

/*!
 * @brief Transmit Buffer Descriptor format.
 *
 * A union type cover the BD used as Standard/Extended/WriteBack format.
 */

typedef union _netc_tx_bd
{
    struct
    {
        uint64_t addr;                /*!< Address of the buffer. Little Endian. */
        uint16_t bufLen;              /*!< Length of buffer specifying effective number of bytes. */
        uint16_t frameLen;            /*!< Length of Frame. */
        uint32_t flags : 29;          /*!< Flags qualified setting. */
        uint32_t enableInterrupt : 1; /*!< Whether enable interrupt on complete of BD. */
        uint32_t isExtended : 1;      /*!< Extended BD format flag. */
        uint32_t isFinal : 1;         /*!< Final BD flag. */
    } standard;
    struct
    {
        uint32_t timestamp : 30; /*!< IEEE1588 PTP one-step timestamp. */
        uint32_t : 2;            /*!< Ignore 2-bit MSB. */
        uint16_t : 14;
        uint16_t tpid : 2; /*!< VLAN TPID type, see @ref netc_vlan_tpid_select_t. */
        uint16_t vid : 12; /*!< VLAN ID. */
        uint16_t dei : 1;  /*!< VLAN DEI. */
        uint16_t pcp : 3;  /*!< VLAN PCP. */
        uint32_t : 32;
        uint16_t : 16;
        uint8_t eFlags; /*!< Tx extension flags. */
        uint8_t : 7;
        uint8_t isFinal : 1; /*!< Final BD flag. */
    } ext;
    struct
    {
        uint32_t timestamp;   /*!< Timestamp write back. */
        uint32_t txtsid : 16; /*!/ Transmit timestamp identifier, only active on Switch management ENETC. */
        uint32_t : 16;
        uint32_t : 32;
        uint32_t : 16;
        uint32_t status : 9; /*!< Status. */
        uint32_t : 1;
        uint32_t written : 1; /*!< Write-back flag. */
        uint32_t : 5;
    } writeback;
} netc_tx_bd_t;

/*!
 * @brief Receive Buffer Descriptor format.
 *
 */
typedef union _netc_rx_bd
{
    struct
    {
        uint64_t addr; /*!< Software write address. */
        uint64_t : 64;
    } standard;
    struct
    {
        uint16_t internetChecksum; /*!< Internet Checksum. */
        uint16_t parserSummary;    /*!< Parser Summary. */
        union
        {
            struct
            {
                uint32_t srcPort : 5; /*!< Source port received from switch management port. */
                uint32_t : 3;
                uint32_t rssHash : 24; /*!< RSS Hash high field value. */
            };
            uint32_t rssHashSwt; /*!< RSS hash while not used as switch management port. */
        };
        uint16_t bufLen;   /*!< Length of received buffer. */
        uint16_t vid : 12; /*!< VLAN ID. */
        uint16_t dei : 1;  /*!< VLAN DEI. */
        uint16_t pcp : 3;  /*!< VLAN PCP. */
        uint8_t tpid : 2;  /*!< VLAN TPID. */
        uint8_t hr : 4;    /*!< Host Reason. */
        uint8_t : 2;
        uint8_t flags; /*!< Rx information flags. */
        uint8_t error; /*!< Rx error code. */
        uint8_t : 6;
        uint8_t isReady : 1; /*!< Received data ready flag. */
        uint8_t isFinal : 1; /*!< Final BD flag. */
    } writeback;
    struct
    {
        uint32_t timestamp; /*!< Rx Timestamp. */
        uint32_t : 32;
        uint64_t : 64;
    } ext;
    struct
    {
        uint32_t timestamp; /*!< Switch response timestamp. */
        uint32_t : 32;
        uint16_t txtsid; /*!< Transmit timestamp identifier. */
        uint16_t : 16;
        uint32_t : 2;
        uint32_t hr : 4; /*!< Host Reason. */
        uint32_t : 10;
        uint32_t error : 8;
        uint32_t : 6;
        uint32_t isReady : 1; /*!< Received data ready flag. */
        uint32_t isFinal : 1; /*!< Final BD flag. */
    } resp;
} netc_rx_bd_t;

/*! @brief Configuration for the SI Tx Buffer Descriptor Ring Configuration. */
typedef struct _netc_tx_bdr_config
{
    uint32_t len;                     /*!< Size of BD ring which shall be multiple of 8 BD. */
    netc_tx_bd_t *bdArray;            /*!< BDR base address which shall be 128 bytes aligned. */
    netc_tx_frame_info_t *dirtyArray; /*!< Tx cleanup ring. */
    // Interrupt
    bool enIntr;             /*!< Enable/Disable completion interrupt. */
    bool enThresIntr;        /*!< Enable/Disable threshold interrupt. */
    bool enCoalIntr;         /*!< Enable/Disable interrupt coalescing. */
    uint32_t intrThreshold;  /*!< Interrupt coalescing packet threshold. */
    uint32_t intrTimerThres; /*!< Interrupt coalescing timer threshold, specified in NETC clock cycles. */
    uint8_t msixEntryIdx;    /*!< MSIX entry index of Tx ring interrupt. */
    // Configure
    bool isVlanInsert; /*!< Enable/Disable VLAN insert offload. */
    bool isUserCRC;    /*!< Enable/Disable user provided the CRC32 - FCS at end of frame. */
    uint8_t wrrWeight; /*!< Weight used for arbitration when rings have same priority. */
    uint8_t priority;  /*!< Priority of the Tx BDR. */
} netc_tx_bdr_config_t;

/*! @brief Transmit BD ring handler data structure. */
typedef struct _netc_tx_bdr
{
    netc_tx_bd_t *bdBase;            /*!< Tx BDR base address. */
    netc_tx_frame_info_t *dirtyBase; /*!< Tx cleanup ring base address. */
    uint16_t producerIndex;          /*!< Current index for transmit. */
    uint16_t cleanIndex;             /*!< Current index for tx cleaning. */
    uint32_t len;                    /*!< Length of this BD ring. */
} netc_tx_bdr_t;

/*! @brief Status/Interrupts flags for the TX BDR. Each flag get its own bit thus it support bit AND/OR operation. */
typedef enum _netc_tx_bdr_flags
{
    kNETC_TxBDRSystemBusErrorFlag = 0x1,
    kNETC_TxBDRBusyFlag           = 0x1 << 1U,
    kNETC_TxBDRStatusFlagsMask    = kNETC_TxBDRBusyFlag | kNETC_TxBDRBusyFlag,
    // TODO, Append the interrupt flags
} netc_tx_bdr_flags_t;

/*! @brief Configuration for the SI Rx Buffer Descriptor Ring Configuration. */
typedef struct _netc_rx_bdr_config
{
    // Descriptor data structure
    bool extendDescEn;       /*!< False - Use 16Bytes standard BD. True - Use 32Bytes extended BD. */
    netc_rx_bd_t *bdArray;   /*!< BD ring base address which shall be 128 bytes aligned. */
    uint32_t len;            /*!< BD ring length in the unit of 16Bytes standard BD. Shall be multiple of 8/16 for
                                standard/exteneded BD. */
    uint64_t *buffAddrArray; /*!< Rx buffers array with BD length(half of BD length if use exteneded BD). */
    uint16_t buffSize;       /*!< Size of all Rx buffers in this BD ring. */
    // Interrupt
    bool enThresIntr;        /*!< Enable/Disable threshold interrupt. */
    bool enCoalIntr;         /*!< Enable/Disable interrupt coalescing. */
    uint32_t intrThreshold;  /*!< Interrupt coalescing packet threshold. */
    uint32_t intrTimerThres; /*!< Interrupt coalescing timer threshold, specified in NETC clock cycles. */
    uint8_t msixEntryIdx;    /*!< MSIX entry index of Rx ring interrupt. */
    // Ring configuration
    bool disVlanPresent; /*!< Disable/Enable VLAN in BD. */
    bool enVlanExtract;  /*!< Enable/Disable VLAN extract. */
    bool isKeepCRC;      /*!< Whether user provided the CRC32 - FCS at end of frame. */
    bool congestionMode; /*!< False - lossy. True - lossless. */
    bool enHeaderAlign;  /*!< Enable/disable +2B alignment to frame. */
} netc_rx_bdr_config_t;

/*! @brief Receive BD ring handler data structure. */
typedef struct _netc_rx_bdr
{
    netc_rx_bd_t *bdBase; /*!< Rx BDR base address. */
    bool extendDesc;      /*!< Use extended buffer descriptor. */
    uint16_t index;       /*!< Current index for read. */
    uint32_t len;         /*!< Length of this BD ring, unit of 16Bytes standard BD. */
    uint64_t *buffArray;  /*!< Rx buffers array of this ring. */
    uint32_t buffSize;    /*!< Rx buffers size for all BDs in this ring. */
} netc_rx_bdr_t;

/*! @brief Status/Interrupts flags for the RX BDR. Each flag get its own bit thus it support bit AND/OR operation. */
typedef enum _netc_rx_bdr_flags
{
    kNETC_RxBDRSystemBusErrorFlag = 0x1,
    kNETC_RxBDREmptyFlag          = 0x1 << 1U,
    // TODO, Append the interrupts flags
} netc_rx_bdr_flags_t;

/*! @brief Configuration for the buffer descriptors ring */
typedef struct _netc_bdr_config
{
    netc_rx_bdr_config_t *rxBdrConfig; /*!< Receive buffer ring configuration array. */
    netc_tx_bdr_config_t *txBdrConfig; /*!< Transmit buffer ring configuration array. */
} netc_bdr_config_t;

/*!
 * @brief PSI message interrupt type.
 */
typedef enum _netc_psi_msg_flags_t
{
    kNETC_PsiRxMsgFromVsi1Flag = 0x2,     /*!< Message receive interrupt enable, initiated by VSI1. */
    kNETC_PsiFLRFromVsi1Flag   = 0x20000, /*!< Function level reset interrupt enable, initiated by VSI1. */
} netc_psi_msg_flags_t;

/*!
 * @brief VSI message interrupt flags.
 */
typedef enum _netc_vsi_msg_flags
{
    kNETC_VsiMsgTxFlag = 0x1,       /*!< Message sent to PSI has completed and response received. */
    kNETC_VsiMsgRxFlag = 0x1 << 1U, /*!< Message received from PSI. */
} netc_vsi_msg_flags_t;

/*!
 * @brief VSI number bit map, VSI1 starts from bit1.
 */
typedef enum _netc_vsi_number
{
    kNETC_Vsi1 = 0x1 << 1U,
    /* Reserved for multiple VSIs. */
} netc_vsi_number_t;

/*!
 * @brief PSI receive message information
 */
typedef struct _netc_psi_rx_msg
{
    uint8_t *msgBuff; /*!< The buffer address application set before receiving message. */
    uint32_t msgLen;  /*!< Received message length. */
} netc_psi_rx_msg_t;

/*!
 * @brief VSI message transmit status
 */
typedef struct _netc_vsi_msg_tx_status
{
    bool txBusy;      /*!< The VSI Tx busy flag, become idle when the PSI receive and clear the related status. */
    bool isTxErr;     /*!< Tx error flag. */
    uint16_t msgCode; /*!< The error code or user-defined content. */
} netc_vsi_msg_tx_status_t;

/*! @} */ // end of netc_hw_si
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_si
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_hw_switch
#endif
/*! @addtogroup netc_hw_switch
 * @{
 */
/*! @brief The switch port bitmap */
typedef enum _netc_swt_port_bitmap
{
    kNETC_SWTPort0Bit = 0x1U,  /*!< Switch port0 bitmap */
    kNETC_SWTPort1Bit = 0x2U,  /*!< Switch port1 bitmap */
    kNETC_SWTPort2Bit = 0x4U,  /*!< Switch port2 bitmap */
    kNETC_SWTPort3Bit = 0x8U,  /*!< Switch port3 bitmap */
    kNETC_SWTPort4Bit = 0x10U, /*!< Switch port4 (internal port) bitmap */
} netc_swt_port_bitmap_t;
/*! @brief The switch ingress mirror destination port */
typedef enum _netc_swt_imr_dest_port
{
    kNETC_SWTPort0 = 0U, /*!< Switch port0 */
    kNETC_SWTPort1 = 1U, /*!< Switch port1 */
    kNETC_SWTPort2 = 2U, /*!< Switch port2 */
    kNETC_SWTPort3 = 3U, /*!< Switch port3 */
    kNETC_SWTPort4 = 4U, /*!< Switch port4 */
    kNETC_SWTMPort = 5U  /*!< Switch management port */
} netc_swt_imr_dest_port_t;

/*! @brief The switch MAC forwarding options */
typedef enum _netc_swt_mac_forward_mode
{
    kNETC_NoFDBLookUp        = 1U,   /*!< No FDB lookup is performed, the frame is flooded. */
    kNETC_FDBLookUpWithFlood = 2U,   /*!< FDB lookup is performed, and if there is no match, the frame is flooded to the
                                        port bitmap in VLAN filter entry. */
    kNETC_FDBLookUpWithDiscard = 3U, /*!< FDB lookup is performed, and if there is no match, the frame is discarded. */
} netc_swt_mac_forward_mode_t;

/*! @brief The switch MAC learning options */
typedef enum _netc_swt_mac_learn_mode
{
    kNETC_DisableMACLearn = 1U, /*!< Disable MAC learning. SMAC FDB lookup is by-passed. */
    kNETC_HardwareMACLearn,     /*!< Hardware MAC learning is enabled. */
    kNETC_SeSoftwareMACLearn, /*!< Software MAC learning secure. FDB lookup based on FID and SMAC is performed and if an
                                 entry is not found, the frame is redirected to the switch management port. */
    kNETC_UnseSoftwareMACLearn, /*!<  Software MAC learning unsecure. FDB lookup based on FID and SMAC is performed and
                                   if an entry is not found, the frame is copied to the switch management port. */
    kNETC_DisableMACLearnWithSMAC /*!< Disable MAC learning with SMAC validation. FDB lookup based on FID and SMAC is
                                     performed and if an entry is not found, the frame is discarded. */
} netc_swt_mac_learn_mode_t;

/*! @brief Switch transmit Bridge Port VLAN Tag Action */
typedef enum _netc_swt_port_tx_vlan_act
{
    kNETC_NoTxVlanModify = 0U, /*!< No egress VLAN modification performed */
    kNETC_TxDelOuterVlan,      /*!< Delete outer VLAN tag */
    kNETC_TxReplOuterVlanVid   /*!< Replace outer VLAN tag's VID with 0; frame to be transmitted as a priority tag frame
                                */
} netc_swt_port_tx_vlan_act_t;

/*! @brief Switch port spanning tree group work mode */
typedef enum _netc_swt_port_stg_mode
{
    kNETC_DiscardFrame = 0U,  /*!< Tx or RX Frames on this port with current spanning tree group ID will be discarded */
    kNETC_LearnWithoutFowrad, /*!< RX Frames on this port with current spanning tree group ID will do Learn SMAC, but do
                                 not forward, Tx Frame will be discarded */
    kNETC_ForwardFrame /*!< RX Frames on this port with current spanning tree group ID will do both MAC learning and
                          forwarding, , Tx Frame will be forwarded. */
} netc_swt_port_stg_mode_t;

/*! @brief Switch Ingress mirror destination config */
typedef struct _etc_swt_imr_config
{
    bool enMirror;                     /*!< Enable ingress mirroring */
    netc_swt_imr_dest_port_t destPort; /*!< Port where ingress mirrored frames are sent */
    uint8_t dr;                        /*!< Mirrored packet's DR (drop resilience) */
    uint8_t ipv;                       /*!< Mirrored packet's IPV (internal priority value) */
    uint8_t efmLengthChange; /*!< Egress Frame Modification Frame Length change in 2s complement notation, Vaild if
                                efmEntryID is noy null */
    uint16_t efmEntryID; /*!< Egress Frame Modification Entry Id, note 0xFFFF is a Null Frame Modification Entry, Only
                            applicable if destPort != kNETC_SWTMPort */
} netc_swt_imr_config_t;

/*! @brief Switch port bridge configuration */
typedef struct _netc_swt_port_config
{
    netc_swt_port_tx_vlan_act_t
        txVlanAction : 2;       /*!< Only applies for the frame outer VLAN tag's VID is equal to the port default VID */
    bool isRxVlanAware : 1;     /*!< Receive VLAN Aware Mode */
    bool acceptUntag : 1;       /*!< Accept untagged frame */
    bool acceptPriorityTag : 1; /*!< Accept priority tagged frame (VID = 0) */
    bool acceptSingleTag : 1;   /*!< Accept single tagged frame */
    bool acceptDoubleTag : 1;   /*!< Accept double tagged frame (ounter and inner) */
    struct
    {
        uint32_t : 15;
        uint32_t vid : 12; /*!< Vlan Identifier. */
        uint32_t dei : 1;  /*!< Drop eligible indicator */
        uint32_t pcp : 3;  /*!< Priority code point. */
        uint32_t tpid : 1; /*!< Tag protocol identifier, 0 = Standard C-VLAN 0x8100, 1 = Standard S-VLAN 0x88A8. */
    } defaultVlan;
    netc_swt_port_stg_mode_t
        stgMode[16];           /* Port spanning tree protocol state for spanning tree protocol group 0 ~ 15 */
    bool enSrcPortPrun : 1;    /*!< Enable/Disable received frame be transmitted to same port it was received */
    bool enMacStationMove : 1; /*!< Enable/Disable received frame which ingress port not match the FDB entry Destination
                              Port Bitmap */
    bool enBcastStormCtrl : 1; /*!< Enable/Disable Storm control for broadcast frames */
    bool enMcastStormCtrl : 1; /*!< Enable/Disable Storm control for multicast frames */
    bool enUnMcastStormCtrl : 1; /*!< Enable/Disable Storm control for unknown multicast frames */
    bool enUnUcastStormCtrl : 1; /*!< Enable/Disable Storm control for unknown unicast frames */
    uint32_t bcastRpEntryID;     /*!< Broadcast rate policer entry ID. Valid if enBroadStormCtrl = true */
    uint32_t mcastEntryID;       /*!< Known multicast rate policer entry ID. Valid if enBroadStormCtrl = true */
    uint32_t unMcastRpEntryID;   /*!< Unknown multicast policer entry ID. Valid if enUnMultiStormCtrl = true */
    uint32_t unUcastRpEntryID;   /*!< Unknown unicast rate policer entry ID. Valid if enUnUniStormCtrl = true */
    uint16_t maxDynaFDBEntry;    /*!< The maximium number of dynamic entries in the FDB table, 0 means no limit */
} netc_swt_port_bridge_config_t;

/*! @brief Switch Port level Frame Modification configuration (PPCPDEIMR and PQOSMR[QVMP])*/
typedef struct _netc_swt_port_fm_config
{
    bool ignoreFMMiscfg : 1;   /*!< Enable/Disable ignore the Frame Modification Misconfiguration Action */
    bool enEgressPcpMap : 1;   /*!< Enable egress frame modification of outer VLAN tag's PCP value is mapped to a new
                                  value based on egressPcpMap, used for Frame Modification VLAN Outer PCP action */
    bool enIngressPcpMap : 1;  /*!< Enable ingress frame modification of outer VLAN tag's PCP value is mapped to a
                                  new value based on egressPcpMap, used for Frame Modification VLAN Outer PCP action */
    bool enUpdateVlanDei : 1;  /*!< Enable update DR value in the  outer VLAN based on DEnDEI field, used for egress
                                Frame  Modification Outer DEI action */
    uint8_t drToDeiMap : 4;    /*!< Mapping of internal QoS's DR value n to VLAN DEI, The 4 bits correspond to the DR3 ~
                                  DR0, and 1 means DRn mapping to DEI 1, 0 means DRn mapping to DEI 0 */
    uint8_t egressPcpMap : 4;  /*!< Egress PCP to PCP Mapping Profile instance, active when enEgressPcpMap is true */
    uint8_t ingressPcpMap : 4; /*!< Ingress PCP to PCP Mapping Profile instance, active when enIngressPcpMap is true */
    uint8_t qosVlanMap : 4; /*!< Transmit QoS to VLAN PCP Mapping Profile index, used for egress Frame Modification VLAN
                               Add/Replace Action */
} netc_swt_port_fm_config_t;

/*! @brief  Switch VLAN filter hash table default entry configuration, which determines the default entry when not found
 * in VLAN filter lookup */
typedef struct _netc_swt_default_vlan_filter
{
    bool enIPMFlood;        /*!< Enable IP Multicast Flooding */
    bool enIPMFilter;       /*!< Enable IP Multicast Filtering */
    uint8_t stgID;          /*!< Spanning Tree Group Member ID, range in 0 ~ 15 */
    uint8_t portMembership; /*!< The bit 0 ~ 4 correspond to the 5 ports, When bit set (0b1), means the port is a member
                               of this VLAN. Port membership is used for source/destination pruning */
    bool enUseFilterID;     /*!< Enable use the specified filterID as FID, otherwise will use the frame VID */
    uint16_t filterID; /*!< Used as a key value to do FDB table and the L2 IPV4 Multicast Filter table lookup. Valid if
                          enUseFilterID is true */
    netc_swt_mac_forward_mode_t mfo; /*!< MAC forwarding options */
    netc_swt_mac_learn_mode_t mlo;   /*!< MAC learning options */
    uint16_t baseETEID;              /*!< Base Egress Treatment Entry ID */
    uint8_t etaPortBitmap;           /*!< Egress Treatment Applicability Port. Valid if baseETEID is not null. */
} netc_swt_default_vlan_filter_t;

/*! @brief Bridge config */
typedef struct _netc_swt_bridge_config
{
    netc_swt_default_vlan_filter_t
        dVFCfg; /*!< Default VLAN filter entry configuration when not found in VLAN filter lookup */
} netc_swt_bridge_config_t;

/*! @brief Switch PSFP configuration */
typedef struct _netc_swt_psfp_config
{
    netc_isi_kc_rule_t kcRule[4]; /*!< Key construction rules */
} netc_swt_psfp_config_t;

/*! @brief Switch Qos Classification configuration (include two profiles) */
typedef struct _netc_qos_classify_config
{
    netc_qos_classify_profile_t profiles[2];
} netc_swt_qos_classify_config_t;

/*! @brief Switch QoS to PCP mapping and PCP to PCP mapping configuration when egress packet modification the VLAN tag
 */
typedef struct _netc_swt_qos_to_vlan_config
{
    struct fsl_netc
    {
        uint8_t qos[32]; /*!< Index is created from IPV (3 bits) + DR (2 bits) field. Value is the mapped PCP for VLAN
                            tag. */
        uint8_t pcp[8];  /*!< Index is created from outer PCP (3 bits) field. Value is the mapped PCP for VLAN tag. */
    } profiles[2];
} netc_swt_qos_to_vlan_config_t;

/*! @brief Switch static/dynamic FDB entries in-use statistic */
typedef struct _netc_switch_inuse_fdb_statistic
{
    uint16_t camEntries;        /*!<  Number of FDB entries in-use in the CAM. */
    uint16_t staticEntries;     /*!< Number of static FDB entries in-use (both hash-based and CAM-based entries). */
    uint16_t dynamicEntries;    /*!< Number of dynamic FDB entries in-use (hash-based and CAM-based entries). */
    uint16_t dynamicEntriesHWM; /*!< High water mark of dynamic entries in-use in the FDB table. */
} netc_switch_inuse_fdb_statistic_t;

/*! @} */ // end of netc_hw_switch
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_hw_switch
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_H_ */
