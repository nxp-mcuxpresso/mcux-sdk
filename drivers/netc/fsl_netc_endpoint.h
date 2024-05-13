/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_ENDPOINT_H_
#define FSL_NETC_ENDPOINT_H_

#include "fsl_netc.h"
#include "fsl_netc_soc.h"
#include "netc_hw/fsl_netc_hw.h"
#include "netc_hw/fsl_netc_hw_enetc.h"
#include "netc_hw/fsl_netc_hw_port.h"
#include "netc_hw/fsl_netc_hw_si.h"

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region api_ep
#endif
//////////////////////////////////////
// Group for the End Point Driver
//////////////////////////////////////
/*!
 * @defgroup netc_ep NETC Endpoint (EP) Driver
 * @details API / Data structure for using NETC driver and endpoint.
 * This group handles endpoint devices covering the features to Initialize/De-Initialize the endpoint, transfer
 * packets, configure the port/links, and get the status and statistic. Note that it doesn't cover the phy configuration
 * which shall be configured in MDIO module for both external real PHY and internal virtual PHY.
 *
 * The endpoint API mainly relates to the ENETC IP which interfaces the host to the MAC or Pseudo-MAC (Switch).
 *
 * APIs in this group take the ep_handle_t as first parameter to retrieve the current context.
 * User shall not manipulate the members of the handle without invoking the provided APIs or help macros as it may
 * break the driver state.
 *
 * All API in this groups start with `EP_` and data structure specific to endpoint start with `ep_`.
 *
 * @ingroup netc_api
 */

/*!
 * @defgroup netc_ep_config Endpoint (EP) Generic Configuration
 * @details Generic Ethernet endpoint configuration
 * MAC, host interface and driver configuration.
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_ntmp Endpoint (EP) Table Management Module
 * @details Generic Table Management related functionalities
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_stat Endpoint (EP) Statistic Module
 * @details Statistics counters
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_interrupt Endpoint (EP) Interrupt Module
 * @details Interrupt related functionalities
 *
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_xfer Endpoint (EP) Transmit/Receive
 * @details Data interface for transmit and receive
 *
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_psi_vsi_msg Endpoint (EP) PSI/VSI
 * @details PSI/VSI related functionalities
 *
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_datapath Endpoint (EP) data path
 * @details QoS, classification and filtering functionalities
 * @ingroup netc_ep
 */
/*!
 * @defgroup netc_ep_tx Endpoint (EP) Egress data path configuration
 * @details API/Data structure for configuration of the endpoint ingress datapath
 * This module includes steps below in sequence and APIs are placed following this sequence for user to identify easily
 * - Schedule: Credit Based Shaper also referred as IEEE 802.1 Qav
 * - Schedule: Time Specific Departure
 * - Schedule: Time Gate Scheduling referred as IEEE 802.1 Qbv
 * - VLAN Insert
 *
 * API in this group starts with `EP_Tx`.
 *
 * @ingroup netc_ep_datapath
 */
/*!
 * @defgroup netc_ep_rx Endpoint (EP) Ingress data path configuration
 * @details API/Data structure for configuration of the endpoint ingress datapath.
 * This module includes steps below in sequence and APIs are placed following this sequence for user to identify easily
 * - Parser
 * - VLAN Classification
 * - Ingress QoS Classification
 * - Ingress Port Filtering
 * - Stream Identification and Filtering
 * - L2 Filtering: VLAN/MAC Address
 * - Policying: Rate Policing and Stream Gating
 * - Enqueue (Ingress Congestion Management ICM)
 * - HTA (Host Transfer Agent Rx)
 *
 * API in this group starts with `EP_Rx`.
 *
 * @ingroup netc_ep_datapath
 */

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion api_ep
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_stat
#endif
/*! @addtogroup netc_ep_stat
 * @{
 */

/*! @brief Status/interrupt detect flags merged to same set of enum. TODO SITMRIDR */
typedef enum _ep_flags
{
    kNETC_EPTimerSyncedFlag     = 0x1,
    kNETC_EPICMBlockedFlag      = 0x1 << 1,
    kNETC_EPWakeOnLANActiveFlag = 0x1 << 2,

} ep_flags_t;

/*! @} */ // end of netc_ep_stat
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_stat
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_interrupt
#endif
/*! @addtogroup netc_ep_interrupt
 * @{
 */

/*!
 * @brief Interrupt enable/disable flags.
 *
 * The value of the enumerator is not necessary match the bit in register. All interrupts in Endpoint are
 * merged into this enum except the BDR specific interrupt.
 * TODO SITMRIER
 */
typedef enum _ep_interrupt_flag
{
    kNETC_EPPSIResetInterruptEnable = 0x1,
    kNETC_EPPSIMsgRxInterruptEnable = 0x1 << 1U,
} ep_interrupt_flag_t;

/*! @} */ // end of netc_ep_interrupt
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_interrupt
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_xfer
#endif
/*! @addtogroup netc_ep_xfer
 * @{
 */

typedef enum _ep_rx_flags
{
    kEP_RX_RSS_VALID       = 0x1,       /*!< Request timestamp. */
    kEP_RX_VLAN_VALID      = 0x1 << 1U, /*!< Specifiy frame departure time. */
    kEP_RX_TIMESTAMP_VALID = 0x1 << 2U, /*!< Enable port masquerading. */
} ep_rx_flags_t;

typedef enum _ep_tx_opt_flags
{
    kEP_TX_OPT_REQ_TS      = 0x1U, /*!< Request timestamp (IEEE 1588 PTP two-step timestamp). */
    kEP_TX_OPT_VLAN_INSERT = 0x2U, /*!< Enable VLAN insert. */
    kEP_TX_OPT_START_TIME  = 0x4U, /*!< Specifiy frame departure time. */
#if !(defined(FSL_FEATURE_NETC_HAS_ERRATA_051255) && FSL_FEATURE_NETC_HAS_ERRATA_051255)
    kEP_TX_OPT_REQ_ONE_STEP_TS = 0x8U, /*!< Request IEEE 1588 PTP one-step timestamp offload. */
#endif
} ep_tx_opt_flags;

typedef struct _ep_tx_opt
{
    uint32_t flags;             /*!< A bitmask of ep_tx_opt_flags */
    uint32_t timestamp;         /*!< Departure timestamp, used if kEP_TX_OPT_START_TIME is set */
    netc_enetc_vlan_tag_t vlan; /*!< VLAN tag which will be inserted, used if kEP_TX_OPT_VLAN_INSERT is set */
} ep_tx_opt;

/*! @} */ // end of netc_ep_xfer
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_xfer
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_datapath
#endif
/*! @addtogroup netc_ep_datapath
 * @{
 */
/*! @brief Port Ingress Filter config */
typedef struct _netc_ep_ipf_config
{
    netc_ipf_config_t dosCfg;          /*!< Configuration for L2/3 DOS. */
    netc_port_ipf_config_t portConfig; /*!< Configuration for port connected to enetc peripheral. */
} netc_ep_ipf_config_t;

/*! @brief PSFP config */
typedef struct _netc_ep_psfp_config
{
    netc_isi_kc_rule_t kcRule[2];
    netc_port_psfp_isi_config isiPortConfig;
} netc_ep_psfp_config_t;

/*! @} */ // end of netc_ep_datapath
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_datapath
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_config
#endif
/*! @addtogroup netc_ep_config
 * @{
 */

/*! @brief Endpoint handle. */
typedef struct _ep_handle ep_handle_t;

/*! @brief Callback for reclaimed tx frames. */
typedef status_t (*ep_reclaim_cb_t)(ep_handle_t *handle, uint8_t ring, netc_tx_frame_info_t *frameInfo, void *userData);

/*! @brief Defines the EP Rx memory buffer alloc function pointer. */
typedef void *(*ep_rx_alloc_cb_t)(ep_handle_t *handle, uint8_t ring, uint32_t length, void *userData);

/*! @brief Defines the EP Rx memory buffer free function pointer. */
typedef void (*ep_rx_free_cb_t)(ep_handle_t *handle, uint8_t ring, void *address, void *userData);

/*! @brief Configuration for the endpoint handle. */
typedef struct _ep_config
{
    netc_hw_si_idx_t si;                /*!< Station interface index. */
    netc_hw_enetc_si_config_t siConfig; /*!< Station interface configuration. */
    uint8_t txPrioToTC[8]; /*!< Tx BD ring priority to Tx traffic class queue index mapping, range in TC0 ~ TC7. */
    netc_port_tx_tc_config_t txTcCfg[8]; /*!< Tx traffic class related configuration, vaild only on ENETC 0. */
    netc_ep_psfp_config_t psfpCfg;       /*!< PSFP configuration,cover the ISI key construction profile and port ingress
                                            stream identification configuration. */
    bool enOuterAsInner;                 /*!< Enable use outer VLAN tag as the inner tag if only one tag is found. */
    netc_enetc_native_vlan_config_t rxOuterVLANCfg; /*!< Port outer native VLAN config. */
    netc_enetc_native_vlan_config_t rxInnerVLANCfg; /*!< Port inner native VLAN config. */
    netc_enetc_parser_config_t parserCfg;           /*!< ENETC parser configuration. */
    uint32_t pauseOnThr;  /*!< ENETC Port pause ON threshold value, value 0 means disables pause generation. */
    uint32_t pauseOffThr; /*!< ENETC Port pause OFF threshold value, value 0 means disables pause generation. */
    struct
    {
        netc_port_ethmac_t ethMac; /*!< Ethernet MAC configuration. */
        netc_port_common_t common; /*!< Port common configuration. */
        bool enableTg;             /*!< Enable port time gate scheduling. */
        bool enPseudoMacTxPad; /*!< Enable pseudo MAC Port Transmit Padding, will pad the frame to a minimum of 60 bytes
                                  and append 4 octets of FCS. */
    } port;
    netc_msix_entry_t *msixEntry;       /*!< MSIX table entry array. */
    uint8_t entryNum;                   /*!< MSIX entry number. */
    uint8_t cmdBdEntryIdx;              /*!< MSIX entry index of command BD ring interrupt. */
    uint8_t siComEntryIdx;              /*!< MSIX entry index of PSI-VSI communication interrupt. */
    uint8_t timerSyncEntryIdx;          /*!< MSIX entry index of timer synchronous state change interrupt. */
    ep_reclaim_cb_t reclaimCallback;    /*!< Callback for reclaimed Tx frames. */
    void *userData;                     /*!< User data, return in callback. */
    bool rxCacheMaintain;               /*!< Enable/Disable Rx buffer cache maintain in driver. */
    bool txCacheMaintain;               /*!< Enable/Disable Tx buffer cache maintain in driver. */
    bool rxZeroCopy;                    /*!< Enable/Disable zero-copy receive mode. */
    ep_rx_alloc_cb_t rxBuffAlloc;       /*!< Callback function to alloc memory, must be provided for zero-copy Rx. */
    ep_rx_free_cb_t rxBuffFree;         /*!< Callback function to free memory, must be provided for zero-copy Rx. */
    netc_cmd_bdr_config_t cmdBdrConfig; /*!< Command BD ring configuration. */
} ep_config_t;

/*! @brief Configuration constant in handle. */
typedef struct _ep_config_const
{
    netc_hw_si_idx_t si;    /*!< Station interface index. */
    uint32_t rxRingUse : 7; /*!< Number of Rx Rings to be used, when enable Rx ring group, this equal to the sum of all
                          Rx group rings. */
    uint32_t txRingUse : 7; /*!< Number of Tx Rings to be used, note that when SI is Switch management ENETC SI, the
                          number not include Tx ring 0. */
    uint32_t rxBdrGroupNum : 2;      /*!< Rx BD ring group number, range in 0 ~ 2. */
    uint32_t ringPerBdrGroup : 3;    /*!< The ring number in every Rx BD ring group, range in 1 ~ 8, active when
                                       rxBdrGroupNum not equal zero. */
    bool rxCacheMaintain : 1;        /*!< Enable/Disable Rx buffer cache maintain in driver. */
    bool txCacheMaintain : 1;        /*!< Enable/Disable Tx buffer cache maintain in driver. */
    bool rxZeroCopy : 1;             /*!< Enable/Disable zero-copy receive mode. */
    uint8_t entryNum;                /*!< MSIX entry number. */
    ep_reclaim_cb_t reclaimCallback; /*!< Callback for reclaimed Tx frames. */
    void *userData;                  /*!< User data, return in callback. */
    ep_rx_alloc_cb_t rxBuffAlloc;    /*!< Callback function to alloc memory, must be provided for zero-copy Rx. */
    ep_rx_free_cb_t rxBuffFree;      /*!< Callback function to free memory, must be provided for zero-copy Rx. */
} ep_config_const_t;

/*! @brief Handle for the endpoint
 * Private internal data.
 */
struct _ep_handle
{
    netc_enetc_hw_t hw;                                       /*!< Hardware register map resource. */
    netc_enetc_cap_t capability;                              /*!< ENETC capability. */
    ep_config_const_t cfg;                                    /*!< Endpoint configuration constant. */
    netc_rx_bdr_t rxBdRing[FSL_FEATURE_NETC_SI_RING_NUM_MAX]; /*!< Receive buffer descriptor ring. */
    netc_tx_bdr_t txBdRing[FSL_FEATURE_NETC_SI_RING_NUM_MAX]; /*!< Transmit buffer descriptor ring. */
    netc_cmd_bdr_t cmdBdRing;                                 /*!< Command BD ring handle for endpoint. */
    uint8_t unicastHashCount[64];                             /*!< Unicast hash index collisions counter. */
    uint8_t multicastHashCount[64];                           /*!< Multicast hash index collisions counter. */
    uint8_t vlanHashCount[64];                                /*!< VLAN hash index collisions counter. */
};

/*! @} */ // end of netc_ep_config
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_config
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_config
#endif
/*! @addtogroup netc_ep_config
 * @{
 */

/*!
 * @brief Initialize the endpoint with specified station interface
 *
 * Each station interface needs to call this API. In the case of a virtual station interface
 * it's necessary that the physical station interface has been initialized beforehand.
 *
 * @param handle
 * @param macAddr Primary MAC address
 * @param config The user configuration
 * @param bdrConfig Array of buffer configurations (for each queue/ring)
 * @return status_t
 */
status_t EP_Init(ep_handle_t *handle, uint8_t *macAddr, const ep_config_t *config, const netc_bdr_config_t *bdrConfig);

/*!
 * @brief De-initialize the endpoint.
 *
 * @param handle
 * @return status_t
 */
status_t EP_Deinit(ep_handle_t *handle);

/*!
 * @brief Get the default configuration.
 *
 * @param config
 * @return status_t
 */
status_t EP_GetDefaultConfig(ep_config_t *config);

/*!
 * @brief Enable MAC transmission/reception
 * To be called when the PHY link is up.
 *
 * @param handle
 * @param speed
 * @param duplex
 * @return status_t
 */
status_t EP_Up(ep_handle_t *handle, netc_hw_mii_speed_t speed, netc_hw_mii_duplex_t duplex);

/*!
 * @brief Disable MAC transmission/reception
 * To be called when the PHY link is down.
 * @note Must ensure all active Tx rings finish current transmission before call this API.
 *
 * @param handle
 * @return status_t
 */
status_t EP_Down(ep_handle_t *handle);

/*!
 * @brief Set the Primary MAC address.
 *
 * @param handle
 * @param macAddr
 * @return status_t
 */
status_t EP_SetPrimaryMacAddr(ep_handle_t *handle, uint8_t *macAddr);

/*!
 * @brief Set EP port speed
 *
 * @param handle
 * @param pSpeed
 */
static inline void EP_SetPortSpeed(ep_handle_t *handle, uint16_t pSpeed)
{
    NETC_PortSetSpeed(handle->hw.portGroup.port, pSpeed);
}

/*! @} */ // end of netc_ep_config
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_config
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_ntmp
#endif
/*! @addtogroup netc_ep_ntmp
 * @{
 */

/*!
 * @brief Initialize endpoint command BD ring
 *
 * @param handle
 * @param config The command BD ring configuration
 * @return status_t
 */
status_t EP_CmdBDRInit(ep_handle_t *handle, const netc_cmd_bdr_config_t *config);

/*!
 * @brief Deinit endpoint command BD ring
 *
 * @param handle
 * @return status_t
 */
status_t EP_CmdBDRDeinit(ep_handle_t *handle);

/*! @} */ // end of netc_ep_ntmp
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_ntmp
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_rx
#endif
/*! @addtogroup netc_ep_rx
 * @{
 */

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Rx Parser
#endif
/*!
 * @brief Configure Parser in Receive Data Path
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t EP_RxParserConfig(ep_handle_t *handle, netc_port_parser_config_t *config)
{
    NETC_PortSetParser(handle->hw.portGroup.port, config);
    return kStatus_Success;
}
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Rx Parser
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region Vlan classification
#endif
/*!
 * @brief Configure the customer vlan type
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t EP_RxVlanCInit(ep_handle_t *handle, const netc_vlan_classify_config_t *config)
{
    NETC_RxVlanCInit(handle->hw.common, config, false);
    return kStatus_Success;
}

/*!
 * @brief Configure the Accepted Vlan.
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t EP_RxVlanCConfigPort(ep_handle_t *handle, netc_port_vlan_classify_config_t *config)
{
    NETC_PortSetVlanClassify(handle->hw.portGroup.port, config);
    return kStatus_Success;
}

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion Vlan classification
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region PSFP
#endif
/*!
 * @brief Enable / Disable Ingress Port Filtering
 *
 * Applied for both Switch and ENETC
 *
 * @param handle
 * @param config IPF general features
 * @return status_t
 */
status_t EP_RxIPFInit(ep_handle_t *handle, netc_ep_ipf_config_t *config);

/*!
 * @brief Get remaining available word number (words size is 6 bytes) of the ingress Port Filter Table.
 * @note  This is a ternary match table, and the entries can vary in size, from 2 to 14 words.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxIPFGetTableRemainWordNum(ep_handle_t *handle)
{
    return (handle->hw.common->IPFTCAPR & NETC_SW_ENETC_IPFTCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->IPFTMOR & NETC_SW_ENETC_IPFTMOR_NUM_WORDS_MASK);
}

/*!
 * @brief Add an entry for the ingress Port Filter Table.
 *
 * This function do an add & query with return hardware id which can be used as future query / delete / update.
 *
 * @param handle
 * @param config  IPF instance configuaration
 * @param entryID  The table entry ID read out
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxIPFAddTableEntry(ep_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxIPFUpdateTableEntry(ep_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg);

/*!
 * @brief Delete an entry for the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID  The table entry ID
 * @return status_t
 */
status_t EP_RxIPFDelTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Reset the counter of an ingress port filter entry
 *
 * @param handle
 * @param entryID  The table entry ID
 * @return status_t
 */
status_t EP_RxIPFResetMatchCounter(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the matched count for entry in IPF
 *
 * @param handle
 * @param entryID  The table entry ID
 * @param count  A count of how many times this entry has been matched.
 * @return status_t
 */
status_t EP_RxIPFGetMatchedCount(ep_handle_t *handle, uint32_t entryID, uint64_t *count);

/*!
 * @brief Init the ENETC PSFP, inlcude
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t EP_RxPSFPInit(ep_handle_t *handle, const netc_ep_psfp_config_t *config)
{
    NETC_PSFPKcProfileInit(handle->hw.common, &config->kcRule[0], false);
    NETC_PortSetISI(handle->hw.portGroup.port, &config->isiPortConfig);
    return kStatus_Success;
}

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of stream identification table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream Filter,
 *       table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetISITableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Add an entry into the stream identification table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddISITableEntry(ep_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID);

/*!
 * @brief Delete an entry in the stream identification table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPDelISITableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of ingress stream table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetISTableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->ISITCAPR & NETC_SW_ENETC_ISITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->ISITOR & NETC_SW_ENETC_ISITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add an entry into the ingress stream table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddISTableEntry(ep_handle_t *handle, netc_tb_is_config_t *config);

/*!
 * @brief Update an entry in the ingress stream table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPUpdateISTableEntry(ep_handle_t *handle, netc_tb_is_config_t *config);

/*!
 * @brief Delete an entry in the stream identification table
 *
 * @param handle
 * @param entryID
 * @return status_t
 */
status_t EP_RxPSFPDelISTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of ingress stream filter table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetISFTableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Add an entry into the ingress stream filter table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddISFTableEntry(ep_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update an entry into the ingress stream filter table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPUpdateISFTableEntry(ep_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg);

/*!
 * @brief Del an entry into the stream filter table
 *
 * @param handle
 * @param entryID
 * @return status_t
 */
status_t EP_RxPSFPDelISFTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of Rate Policer table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetRPTableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->RPITCAPR & NETC_SW_ENETC_RPITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->RPITOR & NETC_SW_ENETC_RPITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry to Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Update entry in Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPUpdateRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Add or update entry in Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddOrUpdateRPTableEntry(ep_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Delete entry in the Rate Policer table
 *
 * @param handle
 * @param entryID
 * @return status_t
 */
status_t EP_RxPSFPDelRPTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get statistic of specified Rate Policer entry
 *
 * @param handle
 * @param entryID
 * @param statis
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPGetRPStatistic(ep_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis);

/*!
 * @brief Get remaining available entry number of ingress stream count table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetISCTableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->ISCITCAPR & NETC_SW_ENETC_ISCITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->ISCITOR & NETC_SW_ENETC_ISCITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry in ingress stream count table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddISCTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get ingress stream count statistic
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPGetISCStatistic(ep_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic);

/*!
 * @brief Reset the count of the ingress stream count
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPResetISCStatistic(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of stream gate instance table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetSGITableRemainEntryNum(ep_handle_t *handle)
{
    return (handle->hw.common->SGIITCAPR & NETC_SW_ENETC_SGIITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->SGIITOR & NETC_SW_ENETC_SGIITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry in stream gate instance table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddSGITableEntry(ep_handle_t *handle, netc_tb_sgi_config_t *config);

/*!
 * @brief Update entry in stream gate instance table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPUpdateSGITableEntry(ep_handle_t *handle, netc_tb_sgi_config_t *config);

/*!
 * @brief Delete entry in stream gate instance table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPDelSGITableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get state of the stream gate instance for specified entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPGetSGIState(ep_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *state);

/*!
 * @brief Get remaining available words number of Stream Gate Control List table
 * @note This is a dynamic bounded index table, and number of words required for a stream gate
 *       control list is 1+N/2 where N is number of gate time slots in the stream gate control list.
 *       The remaining word should be greater than the want added entry size
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t EP_RxPSFPGetSGCLTableRemainWordNum(ep_handle_t *handle)
{
    return (handle->hw.common->SGCLITCAPR & NETC_SW_ENETC_SGCLITCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->SGCLTMOR & NETC_SW_ENETC_SGCLTMOR_NUM_WORDS_MASK);
}

/*!
 * @brief Add entry into Stream Gate Control List Table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPAddSGCLTableEntry(ep_handle_t *handle, netc_tb_sgcl_gcl_t *config);

/*!
 * @brief Delete entry of Stream Gate Control List Table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPDelSGCLTableEntry(ep_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get Stream Gate Control List Table entry gate control list
 *
 * @param handle
 * @param gcl
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPGetSGCLGateList(ep_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length);

/*!
 * @brief Get state (ref count) for Stream Gate Control List table entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxPSFPGetSGCLState(ep_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state);

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion PSFP
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region L2 Filtering
#endif

/*!
 * @brief Init the L2 MAC Filter for a specified SI
 *
 * @param handle  EP handle
 * @param config  The L2 MAC Filter configuration
 * @return status_t
 */
status_t EP_RxL2MFInit(ep_handle_t *handle, netc_si_l2mf_config_t *config);

/*!
 * @brief Add entry into the MAC address hash filter with given MAC address
 * Hardware layer will not maitain the counter of the hash filter. API layer shall cover this requirement.
 *
 * @param handle  EP handle
 * @param type  Unicast or multicast MAC address
 * @param macAddr  MAC address to be added in filter table
 * @return status_t
 */
status_t EP_RxL2MFAddHashEntry(ep_handle_t *handle, netc_packet_type_t type, uint8_t *macAddr);

/*!
 * @brief Delete entry into the MAC address hash filter with given MAC address
 * Hardware layer will not maitain the counter of the hash filter. API layer shall cover this requirement.
 *
 * @param handle  EP handle
 * @param type  Unicast or multicast MAC address
 * @param macAddr  MAC address to be deleted from filter table
 * @return status_t
 */
status_t EP_RxL2MFDelHashEntry(ep_handle_t *handle, netc_packet_type_t type, uint8_t *macAddr);

/*!
 * @brief Add entry into the MAC filter exact match table
 *
 * The entry is associated to the current Station Interface
 *
 * @param handle
 * @param idx      Index in the entry table
 * @param macAddr  MAC address for filter
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxL2MFAddEMTableEntry(ep_handle_t *handle, uint32_t idx, uint8_t *macAddr);

/*!
 * @brief Delete entry into the MAC filter exact match table
 *
 * @param handle  EP handle
 * @param idx  Index in the entry table
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxL2MFDelEMTableEntry(ep_handle_t *handle, uint32_t idx);

// L2 Vlan Filter Table
/*!
 * @brief For VLAN filter, use inner vlan tag or outer vlan tag
 *
 * @param handle
 * @param config
 * @return status_t
 */
status_t EP_RxL2VFInit(ep_handle_t *handle, netc_si_l2vf_config_t *config);

/*!
 * @brief Add entry into the VLAN hash filter with given MAC address
 * Hardware layer will not maitain the counter of the hash filter. API layer shall cover this requirement.
 *
 * @param handle
 * @param vlanId  VLAN identifier for filter
 * @return status_t
 */
status_t EP_RxL2VFAddHashEntry(ep_handle_t *handle, uint16_t vlanId);

/*!
 * @brief Delete entry into the VLAN hash filter with given MAC address
 * Hardware layer will not maitain the counter of the hash filter. API layer shall cover this requirement.
 *
 * @param handle
 * @param vlanId  VLAN identifier for filter
 * @return status_t
 */
status_t EP_RxL2VFDelHashEntry(ep_handle_t *handle, uint16_t vlanId);

/*!
 * @brief Add entry into the MAC filter exact match table
 *
 * The entry is associated to the current Station Interface
 *
 * @param handle
 * @param idx     Index in the entry table
 * @param vlanId  VLAN identifier
 * @param tpid    VLAN TPID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxL2VFAddEMTableEntry(ep_handle_t *handle, uint32_t idx, uint16_t vlanId, netc_vlan_tpid_select_t tpid);

/*!
 * @brief Delete entry into the VLAN filter exact match table
 *
 * @param handle
 * @param idx  Index in the entry table
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_RxL2VFDelEMTableEntry(ep_handle_t *handle, uint32_t idx);

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion L2 Filtering
#endif

/*!
 * @brief Set the received Frame vlan to IPV mapping
 *
 * @param handle
 * @param vlan  Frame VLAN tag.
 * @param ipv  The IPV value to be mapped.
 * @return status_t
 */
static inline status_t EP_RxMapVlanToIpv(ep_handle_t *handle, netc_vlan_t vlan, uint8_t ipv)
{
    status_t result = kStatus_Success;

    if (ipv > 7U)
    {
        result = kStatus_InvalidArgument;
    }
    else
    {
        NETC_SIMapVlanToIpv(handle->hw.si, (uint8_t)(vlan.pcp << 1U | vlan.dei), ipv);
    }

    return result;
}

/*!
 * @brief Set the IPV to Rx ring mapping
 *
 * @param handle
 * @param ipv  IPV value to be mapped.
 * @param ring  The Rx BD ring index to be mapped.
 * @return status_t
 */
static inline status_t EP_RxMapIpvToRing(ep_handle_t *handle, uint8_t ipv, uint8_t ring)
{
    if ((ipv > 7U) || (ring >= handle->cfg.ringPerBdrGroup))
    {
        return kStatus_InvalidArgument;
    }
    else
    {
        NETC_SIMapIpvToRing(handle->hw.si, ipv, ring);
        return kStatus_Success;
    }
}

/*!
 * @brief Set the default used receive Rx BD ring group.
 * @note The IPV mapped ring index is the relative index inside the default used group.
 *
 * @param handle
 * @param groupIdx  The default Rx group index.
 * @return status_t
 */
static inline status_t EP_RxSetDefaultBDRGroup(ep_handle_t *handle, netc_hw_enetc_si_rxr_group groupIdx)
{
    if (((uint8_t)groupIdx >= handle->cfg.rxBdrGroupNum) && (groupIdx != kNETC_SiBDRGroupOne))
    {
        /* Can't selected non existing group */
        return kStatus_InvalidArgument;
    }
    else
    {
        NETC_SISetDefaultRxBDRGroup(handle->hw.si, groupIdx);
        return kStatus_Success;
    }
}

/*! @} */ // end of netc_ep_rx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_rx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_tx
#endif
/*! @addtogroup netc_ep_tx
 * @{
 */

/*!
 * @brief Config the Time Gate Scheduling entry admin gate control list
 *
 * This function is used to program the Enhanced Scheduled Transmisson. (IEEE802.1Qbv)
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_TxTGSConfigAdminGcl(ep_handle_t *handle, netc_tb_tgs_gcl_t *config);

/*!
 * @brief Enable the EP port time gate scheduling
 *
 * @param handle
 * @param enable
 * @param gateState
 * @return status_t
 */
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
status_t EP_TxPortTGSEnable(ep_handle_t *handle, bool enable, uint8_t gateState);
#else
status_t EP_TxPortTGSEnable(ep_handle_t *handle, bool enable);
#endif

/*!
 * @brief Get Time Gate Scheduling entry operation gate control list
 *
 * This function is used to read the Enhanced Scheduled Transmisson. (IEEE802.1Qbv)
 *
 * @param handle
 * @param gcl
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t EP_TxtTGSGetOperGcl(ep_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length);

/*!
 * @brief Config the TC (traffic class) property
 *
 * @param handle
 * @param tcIdx
 * @param config
 * @return status_t
 */
status_t EP_TxTrafficClassConfig(ep_handle_t *handle, netc_hw_tc_idx_t tcIdx, const netc_port_tx_tc_config_t *config);

/*! @} */ // end of netc_ep_tx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_tx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_stat
#endif
/*! @addtogroup netc_ep_stat
 * @{
 */

/*!
 * @brief Get the ENETC port discard statistic and reason
 *
 * Get the discarded count of frames and its reasons.
 *
 * @param handle
 * @param useTx true - Tx port.  false - Rx port.
 * @param statistic pointer to the statistic data
 * @return status_t
 */
static inline status_t EP_GetPortDiscardStatistic(ep_handle_t *handle,
                                                  bool useTx,
                                                  netc_port_discard_statistic_t *statistic)
{
    NETC_PortGetDiscardStatistic(handle->hw.portGroup.port, (useTx) ? kNETC_TxDiscard : kNETC_RxDiscard, statistic);
    return kStatus_Success;
}

/*!
 * @brief Clean the EP Port Rx discard reason. Set the related bits to 1 to clear the specific reasons
 *
 * @param handle
 * @param useTx true - Tx port.  false - Rx port.
 * @param reason0
 * @param reason1
 * @return status_t
 */
static inline status_t EP_ClearPortDiscardReason(ep_handle_t *handle, bool useTx, uint32_t reason0, uint32_t reason1)
{
    NETC_PortClearDiscardReason(handle->hw.portGroup.port, (useTx) ? kNETC_TxDiscard : kNETC_RxDiscard, reason0,
                                reason1);
    return kStatus_Success;
}

/*!
 * @brief Get EP port time gate scheduling gate list status
 *
 * @param handle
 * @return Port status flags which are ORed by the enumerators in the @ref netc_port_tgsl_status_t
 */
static inline uint32_t EP_GetPortTGSListStatus(ep_handle_t *handle)
{
    return NETC_PortGetTGSListStatus(handle->hw.portGroup.port);
}

/*! @} */ // end of netc_ep_stat
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_stat
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_interrupt
#endif
/*! @addtogroup netc_ep_interrupt
 * @{
 */

/*!
 * @brief Clean the SI transmit interrupt flags
 *
 * @param handle    The EP handle.
 * @param txFrameIntrMask  IPV value to be mapped, bit x represents ring x.
 * @param txThresIntrMask  The Rx BD ring index to be mapped, bit x represents ring x.
 */
static inline void EP_CleanTxIntrFlags(ep_handle_t *handle, uint16_t txFrameIntrMask, uint16_t txThresIntrMask)
{
    NETC_SICleanTxIntrFlags(handle->hw.si, txFrameIntrMask, txThresIntrMask);
}

/*!
 * @brief Clean the SI receive interrupt flags
 *
 * @param handle    The EP handle.
 * @param rxIntrMask  Rx interrupt bit mask, bit x represents ring x.
 */
static inline void EP_CleanRxIntrFlags(ep_handle_t *handle, uint32_t rxIntrMask)
{
    NETC_SICleanRxIntrFlags(handle->hw.si, rxIntrMask);
}

/*!
 * @brief Set the global MSIX mask status
 *
 * This function masks/unmasks global MSIX message.
 * Mask - All of the vectors are masked, regardless of their per-entry mask bit states.
 * Unmask - Each entry's mask status determines whether the vector is masked or not.
 *
 * @param handle    The EP handle
 * @param mask      The mask state. True: Mask, False: Unmask.
 * @return status_t
 */
status_t EP_MsixSetGlobalMask(ep_handle_t *handle, bool mask);

/*!
 * @brief Set the MSIX entry mask status for specified entry
 *
 * This function masks/unmasks MSIX message for specified entry.
 *
 * @param handle    The EP handle
 * @param entryIdx  The entry index in the table.
 * @param mask      The mask state. True: Mask, False: Unmask.
 * @return status_t
 */
status_t EP_MsixSetEntryMask(ep_handle_t *handle, uint8_t entryIdx, bool mask);

/*!
 * @brief Get the MSIX pending status in MSIX PBA table
 *
 * This function is to get the entry pending status from MSIX PBA table. If interrupt occurs but masked by vector
 * control of entry, pending bit in PBA will be set.
 *
 * @param handle  The EP handle
 * @param pbaIdx  The index of PBA array with 64-bit unit.
 * @param status  Pending status bit mask, bit n for entry n.
 * @return status_t
 */
status_t EP_MsixGetPendingStatus(ep_handle_t *handle, uint8_t pbaIdx, uint64_t *status);

/*! @} */ // end of netc_ep_interrupt
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_interrupt
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_xfer
#endif
/*! @addtogroup netc_ep_xfer
 * @{
 */
/*!
 * @brief Common part for transfer regular frame or Switch management frame.
 * @note This function is internal used. Please use EP_SendFrame() or SWT_SendFrame() API to send frames.
 *
 * @param handle
 * @param txBdRing The Transmit buffer descriptor ring handle
 * @param hwRing The hardware Tx ring index
 * @param frame The frame descriptor pointer
 * @param context Private context provided back by ep_reclaim_cb_t
 * @param txDesc Point to the Transmits BD Description array.
 * @param txCacheMaintain Enable/Disable Tx buffer Cache Maintain.
 * @retval status_t
 */
status_t EP_SendFrameCommon(ep_handle_t *handle,
                            netc_tx_bdr_t *txBdRing,
                            uint8_t hwRing,
                            netc_frame_struct_t *frame,
                            void *context,
                            netc_tx_bd_t *txDesc,
                            bool txCacheMaintain);

/*!
 * @brief Transmits a frame for specified ring.
 * This API is zero-copy and requires the ep_reclaim_cb_t to be called to free the transmitted frame.
 *
 * @param handle
 * @param ring The ring index
 * @param frame The frame descriptor pointer
 * @param context Private context provided back by ep_reclaim_cb_t
 * @param opt Additional tx options. If NULL, default is tx timestamping enabled, no start time and no masquerading.
 * @retval status_t
 */
status_t EP_SendFrame(ep_handle_t *handle, uint8_t ring, netc_frame_struct_t *frame, void *context, ep_tx_opt *opt);

/*!
 * @brief Wait until the EP Tx ring has completed the transfer.
 *
 * @note Only call after EP_SendFrame() to do a no-interrupt transfer
 *
 * @param handle
 * @param ring The ring index
 */
static inline void EP_WaitUnitilTxComplete(ep_handle_t *handle, uint8_t ring)
{
    uint8_t hwRing = ring;
    if (NETC_EnetcHasManagement(handle->hw.base) && (getSiNum(handle->cfg.si) == 0U))
    {
        /* Switch management ENETC Tx BD hardware ring 0 can't be used to send regular frame, so the index need increase
         * 1 */
        hwRing++;
    }
    while (handle->hw.si->BDR[hwRing].TBCIR != handle->txBdRing[ring].producerIndex)
    {
    }
}
/*!
 * @brief Common part of Reclaim tx descriptors for regular frame or Switch management frame.
 * @note This function is internal used. Please use EP_ReclaimTxDescriptor() or SWT_ReclaimTxDescriptor() API to Reclaim
 * tx descriptors.
 *
 * @param handle
 * @param txBdRing The Transmit buffer descriptor ring handle
 * @param hwRing The hardware Tx ring index
 * @param enCallback Enable/Disable call the Tx Reclaim callback functions.
 */
netc_tx_frame_info_t *EP_ReclaimTxDescCommon(ep_handle_t *handle,
                                             netc_tx_bdr_t *txBdRing,
                                             uint8_t hwRing,
                                             bool enCallback);

/*!
 * @brief Reclaim tx descriptors.
 * This function is used to update the tx descriptor status and
 * get the tx timestamp. For each reclaimed transmit frame the
 * ep_reclaim_cb_t is called.
 *
 * This is called after being notified of a transmit completion from ISR.
 * It runs until there are no more frames to be reclaimed in the BD ring.
 *
 * @param handle
 * @param ring The ring index
 */
void EP_ReclaimTxDescriptor(ep_handle_t *handle, uint8_t ring);

/*!
 * @brief Common part of receives one frame with zero copy from specified ring
 *
 * @note This function is internal used. Please use EP_ReceiveFrame() or SWT_ReceiveFrame() API.
 *
 * @param handle
 * @param rxBdRing Rx BD ring handle
 * @param ring Ring index
 * @param frame Frame buffer point
 * @param attr Frame attribute pointer
 * @param isDrop Whether Frame need be drop
 * @param rxCacheMaintain Enable/Disable Rx buffer Cache maintain
 * @return status_t
 */
status_t EP_ReceiveFrameCommon(ep_handle_t *handle,
                               netc_rx_bdr_t *rxBdRing,
                               uint8_t ring,
                               netc_frame_struct_t *frame,
                               netc_frame_attr_t *attr,
                               bool isDrop,
                               bool rxCacheMaintain);

/*!
 * @brief Receives one frame with zero copy from specified ring
 *
 * @note The sufficient rx frame data structure MUST be provided by appliction.
 *
 * @param handle
 * @param ring The ring index
 * @param frame The frame descriptor pointer
 * @param attr Frame attribute pointer
 * @return kStatus_Success                Successfully receive a regular frame
 * @return kStatus_NETC_RxHRNotZeroFrame  Frame in Rx BD ring is management frame, need call SWT_ReceiveFrame()
 * @return kStatus_NETC_RxTsrResp         Frame in Rx BD ring is Transmit Timestamp Reference Response messages, need
 *                                        call SWT_GetTimestampRefResp() to get Transmit Timestamp Reference Response
 * @return kStatus_NETC_RxFrameEmpty      Rx BD ring is empty
 * @return kStatus_NETC_RxFrameError      Frame in Rx BD ring has error, need be dropped
 * @return kStatus_InvalidArgument        Rx BD ring index is out of range
 * @return kStatus_NETC_LackOfResource    Appliction provided buffer is not enough
 */
status_t EP_ReceiveFrame(ep_handle_t *handle, uint8_t ring, netc_frame_struct_t *frame, netc_frame_attr_t *attr);

/*!
 * @brief Common part of receive regular frame or Switch management frame which will be copied in the provided buffer
 *
 * @note This function is internal used. Please use EP_ReceiveFrameCopy() or SWT_ReceiveFrameCopy() API.
 *
 * @param handle
 * @param rxBdRing Rx BD ring handle
 * @param ring Ring index
 * @param buffer Buffer address
 * @param length Buffer length
 * @param attr Frame attribute pointer
 * @param rxCacheMaintain Enable/Disable Rx buffer Cache maintain
 * @return status_t
 */
status_t EP_ReceiveFrameCopyCommon(ep_handle_t *handle,
                                   netc_rx_bdr_t *rxBdRing,
                                   uint8_t ring,
                                   void *buffer,
                                   uint32_t length,
                                   netc_frame_attr_t *attr,
                                   bool rxCacheMaintain);

/*!
 * @brief Receives one frame which will be copied in the provided buffer from specified ring
 *
 * @note The buffer size MUST be queried using EP_GetRxFrameSize() beforehand.
 *
 * @param handle
 * @param ring Ring index
 * @param buffer Buffer address
 * @param length Buffer length
 * @param attr Frame attribute pointer
 * @return kStatus_Success                Successfully receive a regular frame
 * @return kStatus_InvalidArgument        Rx BD ring index is out of range
 */
status_t EP_ReceiveFrameCopy(ep_handle_t *handle, uint8_t ring, void *buffer, uint32_t length, netc_frame_attr_t *attr);

/*!
 * @brief Common part of get pending frame size API for regular frame or Switch management frame.
 * @note This function is internal used. Please use EP_GetRxFrameSize() or SWT_GetRxFrameSize() API.
 *
 * @param handle
 * @param rxBdRing Rx BD ring handle
 * @param length The length of the valid frame received.
 * @return status_t
 */
status_t EP_GetRxFrameSizeCommon(ep_handle_t *handle, netc_rx_bdr_t *rxBdRing, uint32_t *length);

/*!
 * @brief Gets the size of the pending frame in the specified receive ring buffer.
 *
 * @note Frame size without FCS
 *
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * @param ring The ring index
 * @param length The length of the valid frame received.
 * @return kStatus_Success                Successfully get the length of a regular frame
 * @return kStatus_NETC_RxHRNotZeroFrame  Frame in Rx BD ring is management frame, need call SWT_GetRxFrameSize() to get
 *                                        frame size
 * @return kStatus_NETC_RxTsrResp         Frame in Rx BD ring is Transmit Timestamp Reference Response messages, need
 *                                        call SWT_GetTimestampRefResp() to get Transmit Timestamp Reference Response
 * @return kStatus_NETC_RxFrameEmpty      Rx BD ring is empty
 * @return kStatus_NETC_RxFrameError      Frame in Rx BD ring has error, need be dropped
 * @return kStatus_InvalidArgument        Rx BD ring index is out of range
 */
status_t EP_GetRxFrameSize(ep_handle_t *handle, uint8_t ring, uint32_t *length);

/*! @} */ // end of netc_ep_xfer
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_xfer
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_ep_psi_vsi_msg
#endif
/*! @addtogroup netc_ep_psi_vsi_msg
 * @{
 */

/*!
 * @brief PSI enables/disables specified interrupt
 *
 * @param handle  The EP handle.
 * @param mask  The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 * @param enable  Enable/Disable the interrupt.
 */
void EP_PsiEnableInterrupt(ep_handle_t *handle, uint32_t mask, bool enable);

/*!
 * @brief PSI gets interrupt event flag status
 *
 * @param handle  The EP handle.
 * @return The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 */
uint32_t EP_PsiGetStatus(ep_handle_t *handle);

/*!
 * @brief PSI clears interrupt event flag
 *
 * @param handle  The EP handle.
 * @param mask  The interrupt mask, refer to #netc_psi_msg_flags_t which should be OR'd together.
 */
void EP_PsiClearStatus(ep_handle_t *handle, uint32_t mask);

/*!
 * @brief PSI sends message to specified VSI(s)
 *
 * @param handle  The EP handle.
 * @param msg  The message to be sent.
 * @param vsi  The VSI number.
 * @return status_t
 */
status_t EP_PsiSendMsg(ep_handle_t *handle, uint16_t msg, netc_vsi_number_t vsi);

/*!
 * @brief PSI checks Tx busy flag which should be cleaned when VSI receive the message data
 *
 * @param handle  The EP handle.
 * @param vsi  The VSI number.
 * @return The busy status of specified VSI.
 */
bool EP_PsiCheckTxBusy(ep_handle_t *handle, netc_vsi_number_t vsi);

/*!
 * @brief PSI sets Rx buffer to receive message from specified VSI
 * @note The buffer memory size should be big enough for the message data from VSI
 *
 * @param handle  The EP handle.
 * @param vsi  The VSI number.
 * @param buffAddr  The buffer address to store message data from VSI.
 */
status_t EP_PsiSetRxBuffer(ep_handle_t *handle, netc_vsi_number_t vsi, uint64_t buffAddr);

/*!
 * @brief PSI gets Rx message from specified VSI
 *
 * @param handle  The EP handle.
 * @param vsi  The VSI number.
 * @param msgInfo  The Rx message information.
 */
status_t EP_PsiGetRxMsg(ep_handle_t *handle, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo);

/*!
 * @brief Enable VSI interrupt
 *
 * @param handle  The EP handle.
 * @param mask  The interrupt mask, see #netc_vsi_msg_flags_t which should be OR'd together.
 * @param enable  Enable/Disable interrupt.
 */
void EP_VsiEnableInterrupt(ep_handle_t *handle, uint32_t mask, bool enable);

/*!
 * @brief Get VSI interrupt status
 *
 * @param handle  The EP handle.
 * @return A bitmask composed of #netc_vsi_msg_flags_t enumerators OR'd together.
 */
uint32_t EP_VsiGetStatus(ep_handle_t *handle);

/*!
 * @brief Clear VSI interrupt status
 *
 * @param handle  The EP handle.
 * @param mask  The interrupt mask, see #netc_vsi_msg_flags_t which should be OR'd together.
 */
void EP_VsiClearStatus(ep_handle_t *handle, uint32_t mask);

/*!
 * @brief VSI sends message to PSI
 *
 * @param handle  The EP handle.
 * @param msgAddr  Address to store message ready to be sent, must be 64 bytes aligned.
 * @param msgLen  The message length, must be 32 bytes aligned.
 * @return status_t
 */
status_t EP_VsiSendMsg(ep_handle_t *handle, uint64_t msgAddr, uint32_t msgLen);

/*!
 * @brief Check VSI Tx status
 *
 * @param handle  The EP handle.
 * @param status  The VSI Tx status structure.
 */
void EP_VsiCheckTxStatus(ep_handle_t *handle, netc_vsi_msg_tx_status_t *status);

/*!
 * @brief VSI receives message from PSI
 *
 * @param handle  The EP handle.
 * @param msg  The message from PSI.
 * @return status_t
 */
status_t EP_VsiReceiveMsg(ep_handle_t *handle, uint16_t *msg);

/*! @} */ // end of netc_ep_psi_vsi_msg
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_ep_psi_vsi_msg
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_ENDPOINT_H_ */
