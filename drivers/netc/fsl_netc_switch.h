/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_SWITCH_H_
#define FSL_NETC_SWITCH_H_

#include "fsl_netc.h"
#include "fsl_netc_endpoint.h"
#include "netc_hw/fsl_netc_hw.h"
#include "netc_hw/fsl_netc_hw_enetc.h"
#include "netc_hw/fsl_netc_hw_port.h"
#include "netc_hw/fsl_netc_hw_si.h"

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region api_swt
#endif
//////////////////////////////////////
// Group for the Switch Driver
//////////////////////////////////////
/*!
 * @defgroup netc_swt NETC SWITCH (SWT) Driver
 * @details This is the group of data structure/functions for the NETC switch
 * drivers.
 * This group handles switch devices covering the features to Initialize/De-Initialize the switch, transfer
 * packets, configure the port/links, and get the status and statistic. Note that it doesn't cover the phy configuration
 * which shall be configured in MDIO module for both external PHY and internal (virtual) PHY.
 *
 * The switch API mainly relates to the SWITCH IP which provides IEEE 802.1Q functionalities.
 *
 * APIs in this group take the swt_handle_t as first parameter to retrieve the current context.
 * User shall not manipulate the members of the handle without invoking the provided APIs or help macros as it may
 * break the driver state.
 *
 * All API in this groups start with `SWT_` and data structure specific to switch start with `swt_`.
 *
 * @ingroup netc_api
 */
/*!
 * @defgroup netc_swt_init Switch (SWT) Generic Configuration
 * @details Generic Ethernet switch configuration
 * MAC, host interface and driver configuration.
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_ntmp Switch (SWT) Table Management Module
 * @details Generic Table Management related functionalities
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_interrupt Switch (SWT) Interrupt Module
 * @details Interrupt related functionalities
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_xfer Switch (SWT) Transmit/Receive
 * @details Data interface for transmit and receive
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_datapath Switch (SWT) data path
 * @details QoS, classification and filtering functionalities
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_stat Switch (SWT) Statistic Module
 * @details Statistics counters
 * @ingroup netc_swt
 */
/*!
 * @defgroup netc_swt_tx Switch (SWT) Egress data path configuration
 * @details API/Data structure for configuration of the endpoint ingress datapath
 * This module includes steps below in sequence and APIs are placed following this sequence for user to identify easily
 * - EPP : Egress Packet Processing
 * - CBS: Credit Based Shaper also referred as IEEE 802.1 Qav
 * - TGS: Time Gate Scheduling referred as IEEE 802.1 Qbv
 * - ETM : Egress Queuing and Traffic Management
 *
 * API in this group starts with `SWT_Tx`.
 *
 * @ingroup netc_swt_datapath
 */
/*!
 * @defgroup netc_swt_rx Switch (SWT) Ingress data path configuration
 * @details API/Data structure for configuration of the switch ingress datapath
 * This module includes steps below in sequence and APIs are placed following this sequence for user to identify easily
 * - Parser
 * - VLAN Classification
 * - Ingress QoS Classification
 * - IPF : Ingress Port Filtering
 * - PSFP : Per-Stream Filtering and Policing
 *   - Stream Identification and Filtering
 *   - Policying: Rate Policing and Stream Gating
 * - L2 Filtering: VLAN/MAC Address
 * - Enqueue (Ingress Congestion Management ICM)
 *
 * API in this group starts with `SWT_Rx`.
 *
 * @ingroup netc_swt_datapath
 */

/*!
 * @defgroup netc_swt_mgt Switch (SWT) management
 * @details Specific switch management and the Rx/Tx sharing features (e.g FDB)
 * - FM : Ingress/Egress Frame modification
 * - FRER : Frame Replication and Elimination for Reliability sequence generation
 * @ingroup netc_swt
 */

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion api_swt
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_init
#endif
/*! @addtogroup netc_swt_init
 * @{
 */
typedef struct _swt_handle swt_handle_t;
typedef struct _swt_transfer_config swt_transfer_config_t;

/*! @brief Callback for reclaimed tx frames */
typedef status_t (*swt_reclaim_cb_t)(swt_handle_t *handle, netc_tx_frame_info_t *frameInfo, void *userData);
/*! @brief Defines the Switch Rx memory buffer alloc function pointer. */
typedef void *(*swt_rx_alloc_cb_t)(swt_handle_t *handle, uint32_t length, void *userData);

/*! @brief Defines the Switch Rx memory buffer free function pointer. */
typedef void (*swt_rx_free_cb_t)(swt_handle_t *handle, void *address, void *userData);

/*! @brief Configuration structure for Switch */
typedef struct _swt_config
{
    netc_hw_switch_idx_t switchIdx; /*!< Switch index */
    struct
    {
        netc_port_ethmac_t ethMac;               /*!< Ethernet MAC configuration, vaild only on port 0 ~ 3 */
        netc_port_common_t commonCfg;            /*!< Port common configuration */
        netc_swt_port_bridge_config_t bridgeCfg; /*!< Port bridge configuration */
        netc_swt_port_fm_config_t fmCfg;         /*!< Port Frame Modification configuration */
        netc_port_tx_tc_config_t
            txTcCfg[8]; /*!< Port Tx traffic class related configuration, vaild only on port 0 ~ 3 */
        uint8_t
            ipvToTC[8]; /*!< Port IPV to Tx traffic class queue index mapping, value means TC index, range in 0 ~ 7 */
        uint8_t ipvToBP[8];               /*!< Port IPV to buffer pool ID mapping, value means BP ID, range in 0 ~
                                             (SWT_GetBPTableEntryNum() - 1) */
        netc_port_psfp_isi_config isiCfg; /*!< Port Ingress stream identification */
        bool enMirror;                    /*!< Enable/Disable Ingress Mirroring on this port */
        uint8_t lanID;                    /*!< The HSR's LANID this port belong to */
        bool inCutThrough;     /*!< Enable/Disable Ingress Cut Through on this port, vaild only on port 0 ~ 3 */
        bool outCutThrough;    /*!< Enable/Disable Egress Cut Through on this port, vaild only on port 0 ~ 3 */
#if defined(NETC_PORT_PCTFCR_BSQS_MASK)
        uint8_t outBufferSize; /*!< Specifies the minimal frame data buffered in words (24B) before the frame can be Cut
                                  Through out an egress port, range in 1 ~ 3, vaild only on port 0 ~ 3 */
#endif
        bool enableTg;         /*!< Enable port time gate scheduling. */
        bool enTxRx; /*!< Enable port transmit/receive path, if disabled, the tx/rx of the mac corresponding to the port
                        will also be closed. */
    } ports[5];      /*!< The common configuration required for all ports */
    uint16_t dynFDBLimit; /*!< Maximum number of entries which can be dynamically learned by FDB table, a value of 0
                             implies no limit. */
    netc_swt_psfp_config_t psfpCfg;          /*!< The switch PSFP configuration, cover the ISI key construction
                                                 profiles configuration */
    netc_ipf_config_t ipfCfg;                /*!< The switch ingress port filter configuration */
    netc_vlan_classify_config_t vlanCfg;     /*!< The switch ingress vlan classify configuration */
    netc_swt_qos_classify_config_t rxqosCfg; /*!< The switch ingress VLAN to QoS mapping configuration */
    netc_swt_qos_to_vlan_config_t txqosCfg;  /*!< The switch egress QoS to VLAN mapping configuration */
    netc_swt_imr_config_t imrCfg;            /*!< The switch Ingress mirror configuration */
    netc_swt_bridge_config_t bridgeCfg;      /*!< The switch bridge configuration */
    uint8_t cmdRingUse;                      /*!< Number of command BD rings to be used */
    netc_cmd_bdr_config_t cmdBdrCfg[2];      /*!< The switch command BD rings configuration */
    netc_msix_entry_t *msixEntry;            /*!< MSIX table entry array. */
    uint8_t entryNum;                        /*!< MSIX entry number. */
    uint8_t cmdBdrEntryIdx[2];               /*!< MSIX entry index of command BD ring interrupt. */
    uint8_t timeCaptureEntryIdx;             /*!< MSIX entry index of time capture interrupt. */
} swt_config_t;

/*! @brief Configuration constant structure for Switch in handle. */
typedef struct _swt_config_const
{
    uint8_t cmdRingUse;               /*!< Number of command BD rings to be used */
    uint8_t entryNum;                 /*!< MSIX entry number. */
    bool rxCacheMaintain : 1;         /*!< Enable/Disable Rx buffer cache maintain in driver. */
    bool txCacheMaintain : 1;         /*!< Enable/Disable Tx buffer cache maintain in driver. */
    bool enUseMgmtRxBdRing : 1;       /*!< Enable/Disable use Switch management Rx BD ring. */
    bool enUseMgmtTxBdRing : 1;       /*!< Enable/Disable use Switch management Tx BD ring. */
    bool rxZeroCopy : 1;              /*!< Enable zero-copy receive mode. */
    swt_rx_alloc_cb_t rxBuffAlloc;    /*!< Callback function to alloc memory, must be provided for zero-copy Rx. */
    swt_rx_free_cb_t rxBuffFree;      /*!< Callback function to free memory, must be provided for zero-copy Rx. */
    swt_reclaim_cb_t reclaimCallback; /*!< Callback for reclaimed Tx Switch management frames. */
    void *userData;                   /*!< User data, return in callback. */
} swt_config_const_t;

/*! @brief Handle for SWITCH */
struct _swt_handle
{
    netc_switch_hw_t hw;         /*!< Hardware register map resource. */
    swt_config_const_t cfg;      /*!< Switch configuration constant. */
    netc_cmd_bdr_t cmdBdRing[2]; /*!< Command BD ring handle for switch. */
    ep_handle_t *epHandle;       /*!< The EP handle to send/receive management frame. */
    netc_rx_bdr_t mgmtRxBdRing;  /*!< Management Receive BD ring for frames with Host Reason filed not zero. */
    netc_tx_bdr_t mgmtTxBdRing;  /*!< Management Transmit BD ring for Direct Switch Enqueue frames. */
};

/*! @} */ // end of netc_swt_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_interrupt
#endif
/*! @addtogroup netc_swt_interrupt
 * @{
 */

/*! @} */ // end of netc_swt_interrupt
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_interrupt
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_xfer
#endif
/*! @addtogroup netc_swt_xfer
 * @{
 */
/*! @brief Switch management Tx Option flags */
typedef enum _swt_mgmt_tx_opt_flags
{
    kSWT_TX_OPT_REQ_TS =
        0x1, /*!< Request frame transmission timestamp, only active when use Switch Port masquerading Tx option */
    kSWT_TX_OPT_VLAN_INSERT = 0x2U, /*!< Enable VLAN insert, only active when use Switch Port masquerading Tx option */
    kSWT_TX_OPT_DIRECT_ENQUEUE_REQ_TSR =
        0x4U /*!< Timestamp Reference Request, only active when use Direct Switch Enqueue Tx option */
} swt_mgmt_tx_opt_flags;

/*! @brief Switch management Tx parameter */
typedef union _swt_mgmt_tx_arg_t
{
    uint8_t ring; /*!< Tx ring index, use for Switch Port masquerading Tx option */
    struct
    {
        uint8_t ipv : 3; /*!< Internal Priority Value, use for Direct Switch Enqueue Tx option */
        uint8_t dr : 1;  /*!< Discard Resiliance, use for Direct Switch Enqueue Tx option */
        uint8_t : 4;
    };
} swt_mgmt_tx_arg_t;

/*! @brief Switch management Tx Option */
typedef struct _swt_tx_opt
{
    uint32_t flags;             /*!< A bitmask of swt_mgmt_tx_opt_flags */
    netc_enetc_vlan_tag_t vlan; /*!< VLAN tag which will be inserted, used if enVlanInsert is set */
} swt_tx_opt;

/*! @brief Switch management Tx Timestamp Reference Response */
typedef struct _swt_tsr_resp_t
{
    uint32_t timestamp; /*!< Switch response timestamp. */
    uint32_t txtsid;    /*!< Transmit timestamp identifier. */
} swt_tsr_resp_t;

/*!
 * @brief Transfer configuration structure for Switch
 *
 * @note When need use Switch/EP receive APIs, recommended enable mgmtRxBdrConfig to use special MgmtRxBdRing rings to
 *       receive these host reason not-zero frames
 */
struct _swt_transfer_config
{
    bool rxCacheMaintain;          /*!< Enable/Disable Rx buffer cache maintain in driver. */
    bool txCacheMaintain;          /*!< Enable/Disable Tx buffer cache maintain in driver. */
    bool rxZeroCopy;               /*!< Enable zero-copy receive mode. */
    swt_rx_alloc_cb_t rxBuffAlloc; /*!< Callback function to alloc memory, must be provided for zero-copy Rx. */
    swt_rx_free_cb_t rxBuffFree;   /*!< Callback function to free memory, must be provided for zero-copy Rx. */
    bool enUseMgmtRxBdRing; /*!< Enable/Disable use Switch management Rx BD ring, if disabled, the Switch/EP receive
                        APIs (SWT_GetRxFrameSize()/SWT_ReceiveFrameCopy()/SWT_GetTimestampRefResp()/SWT_ReceiveFrame())
                        will use EP Rx BD ring 0 to receive frames. */
    bool enUseMgmtTxBdRing; /*!< Enable/Disable use Switch management Tx BD ring, if disabled, can't use Switch transfer
                               API (SWT_SendFrame()) to send frames. */
    netc_rx_bdr_config_t mgmtRxBdrConfig; /*!< Switch management Rx BD ring configuration. */
    netc_tx_bdr_config_t mgmtTxBdrConfig; /*!< Switch management Rx BD ring configuration. */
    swt_reclaim_cb_t reclaimCallback;     /*!< Callback for reclaimed Tx Switch management frames. */
    void *userData;                       /*!< User data, return in callback. */
};

/*! @} */ // end of netc_swt_xfer
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_xfer
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_datapath
#endif
/*! @addtogroup netc_swt_datapath
 * @{
 */

/*! @} */ // end of netc_swt_datapath
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_datapath
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_stat
#endif
/*! @addtogroup netc_swt_stat
 * @{
 */

/*! @} */ // end of netc_swt_stat
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_stat
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_init
#endif
/*! @addtogroup netc_swt_init
 * @{
 */

/*!
 * @brief Init SWITCH
 *
 * @param handle
 * @param config The user configuration
 * @return status_t
 */
status_t SWT_Init(swt_handle_t *handle, const swt_config_t *config);

/*!
 * @brief Deinit switch
 *
 * @param handle
 * @return status_t
 */
status_t SWT_Deinit(swt_handle_t *handle);

/*!
 * @brief Get deafult configuration for switch
 *
 * @param config
 * @return status_t
 */
status_t SWT_GetDefaultConfig(swt_config_t *config);

/*!
 * @brief Set MII speed and duplex for switch ethernet port
 *
 * @param handle
 * @param ethPort
 * @param speed
 * @param duplex
 * @return status_t
 */
status_t SWT_SetEthPortMII(swt_handle_t *handle,
                           uint8_t ethPort,
                           netc_hw_mii_speed_t speed,
                           netc_hw_mii_duplex_t duplex);

/*!
 * @brief Set switch port speed
 *
 * @param handle
 * @param portIdx
 * @param pSpeed
 */
static inline void SWT_SetPortSpeed(swt_handle_t *handle, netc_hw_port_idx_t portIdx, uint16_t pSpeed)
{
    NETC_PortSetSpeed(handle->hw.ports[portIdx].port, pSpeed);
}

/*!
 * @brief Stop Switch Port receive/transmit (disable both ETH and port)
 *
 * @param handle
 * @param portIdx
 * @return status_t
 */
status_t SWT_PortStop(swt_handle_t *handle, netc_hw_port_idx_t portIdx);

/*!
 * @brief Set switch port maximum supported received frame size
 *
 * @param handle
 * @param portIdx
 * @param size
 * @return status_t
 */
status_t SWT_SetPortMaxFrameSize(swt_handle_t *handle, netc_hw_port_idx_t portIdx, uint16_t size);

/*! @} */ // end of netc_swt_init
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_init
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_ntmp
#endif
/*! @addtogroup netc_swt_ntmp
 * @{
 */

/*!
 * @brief Init SWITCH command BD ring.
 *
 * @param handle
 * @param ring Command BD ring index
 * @param config The user configuration
 * @return status_t
 */
status_t SWT_CmdBDRInit(swt_handle_t *handle, netc_hw_swt_cbdr_idx_t ring, const netc_cmd_bdr_config_t *config);

/*!
 * @brief Deinit switch command BD ring.
 *
 * @param handle
 * @param ring Command BD ring index
 * @return status_t
 */
status_t SWT_CmdBDRDeinit(swt_handle_t *handle, netc_hw_swt_cbdr_idx_t ring);

/*! @} */ // end of netc_swt_ntmp
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_ntmp
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_interrupt
#endif
/*! @addtogroup netc_swt_interrupt
 * @{
 */

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
status_t SWT_MsixSetGlobalMask(swt_handle_t *handle, bool mask);

/*!
 * @brief Set the MSIX entry mask status for specified entry
 *
 * This function masks/unmasks MSIX message for specified entry.
 *
 * @param handle    SWT handle.
 * @param entryIdx  The entry index in the table.
 * @param mask      The mask state. True: Mask, False: Unmask.
 * @return status_t
 */
status_t SWT_MsixSetEntryMask(swt_handle_t *handle, uint8_t entryIdx, bool mask);

/*!
 * @brief Get the MSIX pending status in MSIX PBA table
 *
 * This function is to get the entry pending status from MSIX PBA table. If interrupt occurs but masked by vector
 * control of entry, pending bit in PBA will be set.
 *
 * @param handle  SWT handle.
 * @param pbaIdx  The index of PBA array with 64-bit unit.
 * @param status  Pending status bit mask, bit n for entry n.
 * @return status_t
 */
status_t SWT_MsixGetPendingStatus(swt_handle_t *handle, uint8_t pbaIdx, uint64_t *status);

/*! @} */ // end of netc_swt_interrupt
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_interrupt
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_rx
#endif
/*! @addtogroup netc_swt_rx
 * @{
 */
/*!
 * @brief Configure switch ingress mirror
 *
 * @param handle
 * @param config
 * @return status_t
 */
status_t SWT_RxMirrorConfig(swt_handle_t *handle, const netc_swt_imr_config_t *config);
/*!
 * @brief Configure Parser in Receive Data Path
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxParserConfig(swt_handle_t *handle,
                                          netc_hw_port_idx_t portIdx,
                                          const netc_port_parser_config_t *config)
{
    NETC_PortSetParser(handle->hw.ports[portIdx].port, config);
    return kStatus_Success;
}

/*!
 * @brief Configure the customer vlan type
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxVlanCInit(swt_handle_t *handle, const netc_vlan_classify_config_t *config)
{
    NETC_RxVlanCInit(handle->hw.common, config, true);
    return kStatus_Success;
}

/*!
 * @brief Configure the Accepted Vlan for PORT.
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxVlanCConfigPort(swt_handle_t *handle,
                                             netc_hw_port_idx_t portIdx,
                                             netc_port_vlan_classify_config_t *config)
{
    NETC_PortSetVlanClassify(handle->hw.ports[portIdx].port, config);
    return kStatus_Success;
}

/*!
 * @brief Init the ingress QoS classification for Switch
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxQosCInit(swt_handle_t *handle, const netc_swt_qos_classify_config_t *config)
{
    NETC_RxQosCInit(handle->hw.common, &config->profiles[0], false);
    NETC_RxQosCInit(handle->hw.common, &config->profiles[1], true);
    return kStatus_Success;
}

/*!
 * @brief Configure the QoS Classification for Switch Port
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxQosCConfigPort(swt_handle_t *handle,
                                            netc_hw_port_idx_t portIdx,
                                            netc_port_qos_classify_config_t *config)
{
    return NETC_PortSetQosClassify(handle->hw.ports[portIdx].port, config);
}

/*!
 * @brief Enable/Disable Ingress Port Filtering
 *
 * Applied for both Switch and ENETC
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxIPFInit(swt_handle_t *handle, const netc_ipf_config_t *config)
{
    NETC_IPFInit(handle->hw.common, config);
    return kStatus_Success;
}
/*!
 * @brief Config the IPF for specified Port
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxIPFConfigPort(swt_handle_t *handle,
                                           netc_hw_port_idx_t portIdx,
                                           const netc_port_ipf_config_t *config)
{
    NETC_PortSetIPF(handle->hw.ports[portIdx].port, config);
    return kStatus_Success;
}

/*!
 * @brief Get remaining available word number (words size is 6 bytes) of the ingress Port Filter Table.
 * @note  This is a ternary match table, and the entries can vary in size, from 2 to 14 words.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxIPFGetTableRemainWordNum(swt_handle_t *handle)
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
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFAddTableEntry(swt_handle_t *handle, netc_tb_ipf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFUpdateTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_ipf_cfge_t *cfg);

/*!
 * @brief Query an entry for the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFQueryTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_ipf_config_t *config);

/*!
 * @brief Delete an entry for the ingress Port Filter Table.
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFDelTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Reset the counter of an ingress port filter entry
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFResetMatchCounter(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the matched count for entry in IPF
 *
 * @param handle
 * @param entryID
 * @param count
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxIPFGetMatchedCount(swt_handle_t *handle, uint32_t entryID, uint64_t *count);

// PSPF
/*!
 * @brief Init the Switch PSFP
 * Cover configuration below
 * - ISI  key construction profiles (ISIDKC0CR0 - ISIDKC3CR0)
 *
 * Not Cover
 * - Port specific isi config
 *
 * @param handle
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxPSFPInit(swt_handle_t *handle, const netc_swt_psfp_config_t *config)
{
    NETC_PSFPKcProfileInit(handle->hw.common, &config->kcRule[0], false);
    NETC_PSFPKcProfileInit(handle->hw.common, &config->kcRule[2], true);
    return kStatus_Success;
}

/*!
 * @brief Configure Ingress stream identification for specified port
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_RxPSFPConfigPortISI(swt_handle_t *handle,
                                               netc_hw_port_idx_t portIdx,
                                               const netc_port_psfp_isi_config *config)
{
    NETC_PortSetISI(handle->hw.ports[portIdx].port, config);
    return kStatus_Success;
}

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of stream identification table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream Filter,
 *       VLAN Filter, FDB, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetISITableRemainEntryNum(swt_handle_t *handle)
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
status_t SWT_RxPSFPAddISITableEntry(swt_handle_t *handle, netc_tb_isi_config_t *config, uint32_t *entryID);

/*!
 * @brief Query an entry in ingress stream identification table
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 */
status_t SWT_RxPSFPQueryISITableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_isi_config_t *config);

/*!
 * @brief Query an entry in ingress stream identification table using key match
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 */
status_t SWT_RxPSFPQueryISITableEntryWithKey(swt_handle_t *handle, netc_tb_isi_keye_t *keye, netc_tb_isi_rsp_data_t *rsp);

/*!
 * @brief Delete an entry in the stream identification table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelISITableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of ingress stream table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetISTableRemainEntryNum(swt_handle_t *handle)
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
status_t SWT_RxPSFPAddISTableEntry(swt_handle_t *handle, netc_tb_is_config_t *config);

/*!
 * @brief Updtae an entry in the ingress stream table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPUpdateISTableEntry(swt_handle_t *handle, netc_tb_is_config_t *config);

/*!
 * @brief Query an entry in ingress stream table
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPQueryISTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_is_config_t *config);

/*!
 * @brief Delete an entry in the stream identification table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelISTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of ingress stream filter table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, VLAN Filter, FDB, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetISFTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Get maximum available entry number (entry size is 24 bytes) of ingress stream filter table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, VLAN Filter, FDB, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetISFTableMaxEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK);
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
status_t SWT_RxPSFPAddISFTableEntry(swt_handle_t *handle, netc_tb_isf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update an entry in the ingress stream filter table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPUpdateISFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_isf_cfge_t *cfg);

/*!
 * @brief Delete an entry in the ingress stream filter table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelISFTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of Rate Policer table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetRPTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->RPITCAPR & NETC_SW_ENETC_RPITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->RPITOR & NETC_SW_ENETC_RPITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Get maximum available entry number (entry size is 24 bytes) of Rate Policer table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, VLAN Filter, FDB, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetRPTableMaxEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->RPITCAPR & NETC_SW_ENETC_RPITCAPR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry to Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPAddRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Update entry in Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPUpdateRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Add or update entry in Rate Policer table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPAddOrUpdateRPTableEntry(swt_handle_t *handle, netc_tb_rp_config_t *config);

/*!
 * @brief Delete entry in the Rate Policer table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelRPTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Query entry in the stream Rate Policer table
 *
 * @param handle
 * @param entryID
 * @param rsp
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPQueryRPTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_rp_rsp_data_t *rsp);

/*!
 * @brief Get statistic of specified Rate Policer entry
 *
 * @param handle
 * @param entryID
 * @param statis
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPGetRPStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_rp_stse_t *statis);

/*!
 * @brief Get remaining available entry number of ingress stream count table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetISCTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->ISCITCAPR & NETC_SW_ENETC_ISCITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->ISCITOR & NETC_SW_ENETC_ISCITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Query entry from the Ingress Stream Filter table
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 */
status_t SWT_RxPSFPQueryISFTableEntry(swt_handle_t *handle, netc_tb_isf_keye_t *keye, netc_tb_isf_rsp_data_t *rsp);

/*!
 * @brief Add entry in ingress stream count table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPAddISCTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get ingress stream count statistic
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPGetISCStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_isc_stse_t *statistic);

/*!
 * @brief Reset the count of the ingress stream count
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPResetISCStatistic(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get remaining available entry number of stream gate instance table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetSGITableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->SGIITCAPR & NETC_SW_ENETC_SGIITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->SGIITOR & NETC_SW_ENETC_SGIITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Get maximum entry number of stream gate instance table
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetSGITableMaxEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->SGIITCAPR & NETC_SW_ENETC_SGIITCAPR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry in stream gate instance table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPAddSGITableEntry(swt_handle_t *handle, netc_tb_sgi_config_t *config);

/*!
 * @brief Update entry in stream gate instance table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPUpdateSGITableEntry(swt_handle_t *handle, netc_tb_sgi_config_t *config);

/*!
 * @brief Delete entry in stream gate instance table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelSGITableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get state of the stream gate instance for specified entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPGetSGIState(swt_handle_t *handle, uint32_t entryID, netc_tb_sgi_sgise_t *state);

/*!
 * @brief Query entry in the stream gate instance table
 *
 * @param handle
 * @param entryID
 * @param rsp
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPQuerySGITableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_sgi_rsp_data_t *rsp);

/*!
 * @brief Get remaining available words number of Stream Gate Control List table
 * @note This is a dynamic bounded index table, and number of words required for a stream gate
 *       control list is 1+N/2 where N is number of gate time slots in the stream gate control list.
 *       The remaining word should be greater than the want added entry size
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetSGCLTableRemainWordNum(swt_handle_t *handle)
{
    return (handle->hw.common->SGCLITCAPR & NETC_SW_ENETC_SGCLITCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->SGCLTMOR & NETC_SW_ENETC_SGCLTMOR_NUM_WORDS_MASK);
}

/*!
 * @brief Get maximum words number of Stream Gate Control List table
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_RxPSFPGetSGCLTableMaxWordNum(swt_handle_t *handle)
{
    return (handle->hw.common->SGCLITCAPR & NETC_SW_ENETC_SGCLITCAPR_NUM_WORDS_MASK);
}

/*!
 * @brief Add entry into Stream Gate Control List Table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPAddSGCLTableEntry(swt_handle_t *handle, netc_tb_sgcl_gcl_t *config);

/*!
 * @brief Delete entry of Stream Gate Control List Table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPDelSGCLTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get Stream Gate Control List Table entry gate control list
 *
 * @param handle
 * @param gcl
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPGetSGCLGateList(swt_handle_t *handle, netc_tb_sgcl_gcl_t *gcl, uint32_t length);

/*!
 * @brief Get state (ref count) for Stream Gate Control List table entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_RxPSFPGetSGCLState(swt_handle_t *handle, uint32_t entryID, netc_tb_sgcl_sgclse_t *state);

/*! @} */ // end of netc_swt_rx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_rx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_mgt
#endif
/*! @addtogroup netc_swt_mgt
 * @{
 */

/*!
 * @brief Config the Bridge
 *
 * Cover configuration below
 * - Vlan filter table default VFHTDRCR0-2
 *
 * Not Cover
 * - Port specific Vlan config
 * - Port Storm Control BPSCR0/R1
 * - FDB entry
 * - Vlan Filter Table entry
 * - Multicast filter entry
 *
 * @param handle
 * @param config
 * @return status_t
 */
status_t SWT_BridgeInit(swt_handle_t *handle, const netc_swt_bridge_config_t *config);

/*!
 * @brief Config bridge port vlan Tx/Rx
 *
 * Cover configuration below
 * - Port specific Vlan config
 * - Port Storm Control BPSCR0/R1
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
status_t SWT_BridgeConfigPort(swt_handle_t *handle,
                              netc_hw_port_idx_t portIdx,
                              const netc_swt_port_bridge_config_t *config);

/*!
 * @brief Config bridge port default VID
 *
 * @param handle
 * @param portIdx
 * @param vid
 * @return status_t
 */
status_t SWT_BridgeConfigPortDefaultVid(swt_handle_t *handle,
                              netc_hw_port_idx_t portIdx, uint16_t vid);

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of bridge vlan filter table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, Ingress Stream Filter, FDB, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_BridgeGetVFTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Add entry into bridge vlan filter table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeAddVFTableEntry(swt_handle_t *handle, netc_tb_vf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in bridge vlan filter table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeUpdateVFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_vf_cfge_t *cfg);

/*!
 * @brief Query an entry in bridge VF Table
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeQueryVFTableEntry(swt_handle_t *handle, netc_tb_vf_keye_t *keye, netc_tb_vf_rsp_data_t *rsp);

/*!
 * @brief Delete entry in bridge vlan filter table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeDelVFTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Search entry in bridge vlan filter table
 *
 * @note Only support search and return one entry at a time.
 *
 * @param handle
 * @param sCriteria
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeSearchVFTableEntry(swt_handle_t *handle, netc_tb_vf_search_criteria_t *sCriteria, netc_tb_vf_rsp_data_t *rsp);

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of bridge FDB table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, Ingress Stream Filter, VLAN Filter, L2 IPV4 Multicast Filter table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_BridgeGetFDBTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Add entry into bridge FDB table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeAddFDBTableEntry(swt_handle_t *handle, netc_tb_fdb_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in bridge FDB table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeUpdateFDBTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_fdb_cfge_t *cfg);

/*!
 * @brief Query an entry in bridge FDB Table
 *
 * @param handle
 * @param keye
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeQueryFDBTableEntry(swt_handle_t *handle, netc_tb_fdb_keye_t *keye, netc_tb_fdb_rsp_data_t *rsp);

/*!
 * @brief Search entry in bridge FDB table
 *
 * @note Only support search and return one entry at a time.
 *
 * @param handle
 * @param sCriteria
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeSearchFDBTableEntry(swt_handle_t *handle,
                                       netc_tb_fdb_search_criteria_t *sCriteria,
                                       netc_tb_fdb_rsp_data_t *rsp);

/*!
 * @brief Delete an entry in bridge FDB Table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeDelFDBTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the activity data for FDB table entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeGetFDBActivityState(swt_handle_t *handle, uint32_t entryID, netc_tb_fdb_acte_t *state);

/*!
 * @brief Get remaining available entry number (entry size is 24 bytes) of bridge L2 IPV4 multicast filter table
 * @note This is a Exact Match hash table, and it shares the remaining available entries with Ingress Stream
 *       Identification, Ingress Stream Filter, VLAN Filter, FDB table.
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_BridgeGetL2MCFTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->HTMCAPR & NETC_SW_ENETC_HTMCAPR_NUM_WORDS_MASK) -
           (handle->hw.common->HTMOR & NETC_SW_ENETC_HTMOR_AMOUNT_MASK);
}

/*!
 * @brief Add entry into Bridge L2 IPV4 multicast filter table
 *
 * @param handle
 * @param config
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeAddL2MCFTableEntry(swt_handle_t *handle, netc_tb_l2mcf_config_t *config, uint32_t *entryID);

/*!
 * @brief Update entry in bridge L2 IPV4 multicast filter table
 *
 * @param handle
 * @param entryID
 * @param cfg
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeUpdateL2MCFTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_l2mcf_cfge_t *cfg);

/*!
 * @brief Search entry in bridge L2 IPV4 multicast filter table
 *
 * @note Only support search and return one entry at a time.
 *
 * @param handle
 * @param sCriteria
 * @param rsp
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeSearchL2MCFTableEntry(swt_handle_t *handle,
                                         netc_tb_l2mcf_search_criteria_t *sCriteria,
                                         netc_tb_l2mcf_rsp_data_t *rsp);

/*!
 * @brief Get the activity data for bridge L2 IPV4 multicast filter table entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeGetL2MCFActivityState(swt_handle_t *handle, uint32_t entryID, netc_tb_l2mcf_acte_t *state);

/*!
 * @brief Delete entry in bridge L2 IPV4 multicast filter table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_BridgeDelL2MCFTableEntry(swt_handle_t *handle, uint32_t entryID);

// Frame Modification
/*!
 * @brief Config Port level Frame Modification
 *
 * @param handle
 * @param portIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_FMConfigPort(swt_handle_t *handle,
                                        netc_hw_port_idx_t portIdx,
                                        const netc_swt_port_fm_config_t *config)
{
    NETC_PORT_Type *base = handle->hw.ports[portIdx].port;
    base->PFMCR          = NETC_PORT_PFMCR_FMMA(config->ignoreFMMiscfg);
    base->PPCPDEIMR =
        NETC_PORT_PPCPDEIMR_DRME(config->enUpdateVlanDei) | NETC_PORT_PPCPDEIMR_EPCPMPV(config->enEgressPcpMap) |
        NETC_PORT_PPCPDEIMR_EPCPMP(config->egressPcpMap) | NETC_PORT_PPCPDEIMR_IPCPMPV(config->enIngressPcpMap) |
        NETC_PORT_PPCPDEIMR_IPCPMP(config->ingressPcpMap) |
        (((uint32_t)config->drToDeiMap & 0xFU) << NETC_PORT_PPCPDEIMR_DR0DEI_SHIFT);
    base->PQOSMR = (base->PQOSMR & ~NETC_PORT_PQOSMR_QVMP_MASK) | NETC_PORT_PQOSMR_QVMP(config->qosVlanMap);
    return kStatus_Success;
}

/*!
 * @brief Get remaining available entry number of Frame Modification table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_FMGetTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->FMITCAPR & NETC_SW_ENETC_FMITCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->FMITOR & NETC_SW_ENETC_FMITOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry into the Frame Modification table
 *
 * Add entry of the frame modification table. Frame modification can be encoded into the table id directly or provided
 * as index of the table entry. refer to the frame modification entry definition.
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FMAddTableEntry(swt_handle_t *handle, netc_tb_fm_config_t *config);

/*!
 * @brief Update entry in the Frame Modification table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FMUpdateTableEntry(swt_handle_t *handle, netc_tb_fm_config_t *config);

/*!
 * @brief Delete table entry in Frame Modification Table
 *
 * The provided ID must be table index. Error return if the id is action encoded id.
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FMDelTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get word number (word size is 24  bytes) of Frame Modification data table
 * @note This is a static bounded index table, when update or query table, should satisifed:
 *       numBytes + ENTRY_ID <= 24 * wordNumber .
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_FMDGetTableWordsNum(swt_handle_t *handle)
{
    return handle->hw.common->FMDITCAPR & NETC_SW_ENETC_FMDITCAPR_NUM_WORDS_MASK;
}

/*!
 * @brief Update Frame Modification data table contents
 *
 * @param handle
 * @param config
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FMDUpdateTableEntry(swt_handle_t *handle, netc_tb_fmd_update_config_t *config, uint32_t length);
/*!
 * @brief Query Frame Modification data table contents
 *
 * @param handle
 * @param query
 * @param length
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FMDQueryTableEntry(swt_handle_t *handle, netc_tb_fmd_query_buffer_t *query, uint32_t length);

/*!
 * @brief Get remaining available entry number of ingress Sequence Generation table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_FRERGetISEQGTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->ISQGITCAPR & NETC_SW_ENETC_ETTCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->ISQGITOR & NETC_SW_ENETC_ETTOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry into FRER sequence number generation table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERAddISEQGTableEntry(swt_handle_t *handle, netc_tb_iseqg_config_t *config);

/*!
 * @brief Update entry in FRER sequence number generation table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERUpdateISEQGTableEntry(swt_handle_t *handle, netc_tb_iseqg_config_t *config);

/*!
 * @brief Delete entry in FRER sequence number generation table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERDelISEQGTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the Sequence generation number form sequence generation table for specified entry
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERGetISEQGState(swt_handle_t *handle, uint32_t entryID, netc_tb_iseqg_sgse_t *state);

/*!
 * @brief Get the number of entries assigned to FRER sequence number recovery table
 * @note This is a static bounded index table, so all entries in the table are available for
 *       SWT_FRERConfigESEQRTableEntry() API
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_FRERGetESEQRTableEntryNum(swt_handle_t *handle)
{
    return handle->hw.common->ESQRTCAPR & NETC_SW_ENETC_ESQRTCAPR_NUM_ENTRIES_MASK;
}

/*!
 * @brief Config FRER sequence number recovery table entry
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERConfigESEQRTableEntry(swt_handle_t *handle, netc_tb_eseqr_config_t *config);

/*!
 * @brief Query FRER sequence recovery table entry
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @param config
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERQueryESEQRTableEntry(swt_handle_t *handle,
                                   uint32_t entryID,
                                   netc_tb_eseqr_stse_t *statistic,
                                   netc_tb_eseqr_cfge_t *config,
                                   netc_tb_eseqr_srse_t *state);

/*!
 * @brief Get FRER sequence recorvery table state and statistic
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_FRERGetESEQRStatistic(swt_handle_t *handle,
                                   uint32_t entryID,
                                   netc_tb_eseqr_stse_t *statistic,
                                   netc_tb_eseqr_srse_t *state);

/*!
 * @brief Get Buffer Pool table entry number
 * @note This is a static bounded index table, so all entries in the table are available for
 *       SWT_UpdateBPTableEntry() API
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_GetBPTableEntryNum(swt_handle_t *handle)
{
    return handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_BP_MASK;
}

/*!
 * @brief Update Buffer Pool table entry
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_UpdateBPTableEntry(swt_handle_t *handle, netc_tb_bp_config_t *config);

/*!
 * @brief Get Buffer Pool table entry State
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_GetBPEntryState(swt_handle_t *handle, uint32_t entryID, netc_tb_bp_bpse_t *state);

/*!
 * @brief Get Shared Buffer Pool table entry number
 * @note This is a static bounded index table, so all entries in the table are available for
 *       SWT_UpdateSBPTableEntry() API
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_GetSBPTableEntryNum(swt_handle_t *handle)
{
    return (handle->hw.base->BPCAPR & NETC_SW_BPCAPR_NUM_SPB_MASK) >> NETC_SW_BPCAPR_NUM_SPB_SHIFT;
}

/*!
 * @brief Update Shared Buffer Pool table entry
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_UpdateSBPTableEntry(swt_handle_t *handle, netc_tb_sbp_config_t *config);

/*!
 * @brief Get Shared Buffer Pool table entry State
 *
 * @param handle
 * @param entryID
 * @param state
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_GetSBPEntryState(swt_handle_t *handle, uint32_t entryID, netc_tb_sbp_sbpse_t *state);

/*! @} */ // end of netc_swt_mgt
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_mgt
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_tx
#endif
/*! @addtogroup netc_swt_tx
 * @{
 */

/*!
 * @brief Configure the transmit maximum SDU for port Traffic Class
 *
 * @param handle
 * @param portIdx
 * @param tcIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_TxSDUConfigPort(swt_handle_t *handle,
                                           netc_hw_port_idx_t portIdx,
                                           netc_hw_tc_idx_t tcIdx,
                                           const netc_port_tc_sdu_config_t *config)
{
    assert((handle != NULL) && (config != NULL));

    return NETC_PortConfigTcMaxSDU(handle->hw.ports[portIdx].port, tcIdx, config);
}

/*!
 * @brief Configure the Credit Based Shaper for port Traffic Class
 *
 * @param handle
 * @param portIdx
 * @param tcIdx
 * @param config
 * @return status_t
 */
static inline status_t SWT_TxCBSConfigPort(swt_handle_t *handle,
                                           netc_hw_port_idx_t portIdx,
                                           netc_hw_tc_idx_t tcIdx,
                                           const netc_port_tc_cbs_config_t *config)
{
    assert((handle != NULL) && (config != NULL));

    return NETC_PortConfigTcCBS(handle->hw.ports[portIdx].port, tcIdx, config);
}

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
status_t SWT_TxTGSConfigAdminGcl(swt_handle_t *handle, netc_tb_tgs_gcl_t *config);

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
status_t SWT_TxtTGSGetOperGcl(swt_handle_t *handle, netc_tb_tgs_gcl_t *gcl, uint32_t length);

/*!
 * @brief Config the TC (traffic class) property
 *
 * @param handle
 * @param portIdx
 * @param tcIdx
 * @param config
 * @return status_t
 */
status_t SWT_TxTrafficClassConfig(swt_handle_t *handle,
                                  netc_hw_port_idx_t portIdx,
                                  netc_hw_tc_idx_t tcIdx,
                                  const netc_port_tx_tc_config_t *config);

/*!
 * @brief Enable the switch port time gate scheduling
 *
 * @param handle
 * @param portIdx
 * @param enable
 * @param gateState
 * @return status_t
 */
#if (defined(FSL_FEATURE_NETC_HAS_ERRATA_051130) && FSL_FEATURE_NETC_HAS_ERRATA_051130)
status_t SWT_TxPortTGSEnable(swt_handle_t *handle, netc_hw_port_idx_t portIdx, bool enable, uint8_t gateState);
#else
status_t SWT_TxPortTGSEnable(swt_handle_t *handle, netc_hw_port_idx_t portIdx, bool enable);
#endif

/*!
 * @brief Get remaining available entry number of egress treatment table
 * @note This is a dynamic bounded index table, the remaining entry can't be zero before add entry into it
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_TxEPPGetETTableRemainEntryNum(swt_handle_t *handle)
{
    return (handle->hw.common->ETTCAPR & NETC_SW_ENETC_ETTCAPR_NUM_ENTRIES_MASK) -
           (handle->hw.common->ETTOR & NETC_SW_ENETC_ETTOR_NUM_ENTRIES_MASK);
}

/*!
 * @brief Add entry in the egress treatment table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxEPPAddETTableEntry(swt_handle_t *handle, netc_tb_et_config_t *config);

/*!
 * @brief Update entry in the egress treatment table
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxEPPUpdateETTableEntry(swt_handle_t *handle, netc_tb_et_config_t *config);

/*!
 * @brief Query an entry in the egress treatment table
 *
 * @param handle
 * @param entryID
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxEPPQueryETTableEntry(swt_handle_t *handle, uint32_t entryID, netc_tb_et_config_t *config);

/*!
 * @brief Delete entry for the egress treatment table
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxEPPDelETTableEntry(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Configure switch egress QOS to VLAN map classification
 *
 * @param handle
 * @param config
 * @return status_t
 */
status_t SWT_TxEPPQosToVlanConfig(swt_handle_t *handle, const netc_swt_qos_to_vlan_config_t *config);

/*!
 * @brief Configure the WBFS and Strict priority for each PORT by using ETM Class Scheduler table
 *
 * @note There is one class queue scheduler per switch port, and there is limitation between TSD and class queue
 *       scheduler configuration
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxETMConfigClassScheduler(swt_handle_t *handle, netc_tb_etmcs_config_t *config);

/*!
 * @brief Configure the class queue to congestion group map by using ETM class queue table
 * @note The number of class queue table entry is equal to the number of class queues in the switch
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxETMConfigClassQueue(swt_handle_t *handle, netc_tb_etmcq_config_t *config);

/*!
 * @brief Config congestion group map by using ETM congestion group table
 * @note The number of congestion groups table entry is equal to the number of class queues in the switch
 *
 * @param handle
 * @param config
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_TxETMConfigCongestionGroup(swt_handle_t *handle, netc_tb_etmcg_config_t *config);

/*! @} */ // end of netc_swt_tx
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_tx
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_xfer
#endif
/*! @addtogroup netc_swt_xfer
 * @{
 */

/*!
 * @brief Set the EP handle used by switch frame management.
 *
 * @param handle
 * @param epHandle The EP handle
 * @param txRxConfig Switch transfer config
 * @retval status_t
 */
status_t SWT_ManagementTxRxConfig(swt_handle_t *handle, ep_handle_t *epHandle, const swt_transfer_config_t *txRxConfig);

/*!
 * @brief Transmits a management frame on a specific port.
 *
 * @param handle
 * @param ringOrQueue The ring index for Port masquerading or egress port priority/dr for direct enqueue
 * @param swtPort The ingress port for Port masquerading or egress for direct enqueue
 * @param enMasquerade Ture - Use Port masquerading Tx option, False - Use direct enqueue Tx Option
 * @param frame The frame descriptor pointer
 * @param context Private context provided back on reclaim
 * @param opt Tx options.
 * @retval status_t
 */
status_t SWT_SendFrame(swt_handle_t *handle,
                       swt_mgmt_tx_arg_t ringOrQueue,
                       netc_hw_port_idx_t swtPort,
                       bool enMasquerade,
                       netc_frame_struct_t *frame,
                       void *context,
                       swt_tx_opt *opt);

/*!
 * @brief Wait until the EP Tx ring has completed the transfer.
 *
 * @note Only call after EP_SendFrame() to do a no-interrupt transfer
 *
 * @param handle
 * @param enMasquerade Ture - Wait Port masquerading Tx ring, False - Wait direct enqueue Tx ring (fixed use
 *                      hardware ring 0)
 * @param ring The Port masquerading Tx ring index, active when enMasquerade is true
 */
static inline void SWT_WaitUnitilTxComplete(swt_handle_t *handle, bool enMasquerade, uint8_t ring)
{
    if (enMasquerade)
    {
        while (handle->epHandle->hw.si->BDR[ring + 1U].TBCIR != handle->epHandle->txBdRing[ring].producerIndex)
        {
        }
    }
    else
    {
        while (handle->epHandle->hw.si->BDR[0].TBCIR != handle->mgmtTxBdRing.producerIndex)
        {
        }
    }
}

/*!
 * @brief Reclaim tx descriptors.
 * This function is used to update the tx descriptor status.
 * For each reclaimed transmit frame the ep_reclaim_cb_t is called.
 *
 * This is called after being notified of a transmit completion from ISR.
 * It runs until there are no more frames to be reclaimed in the BD ring.
 *
 * @param handle
 * @param enMasquerade Ture - Reclaim Port masquerading Tx ring, False - Reclaim direct enqueue Tx ring (fixed use
 *                      hardware ring 0)
 * @param ring The Port masquerading Tx ring index, active when enMasquerade is true
 */
void SWT_ReclaimTxDescriptor(swt_handle_t *handle, bool enMasquerade, uint8_t ring);

/*!
 * @brief Receives management frames (host reason not zero) with zero copy
 *
 * @param handle
 * @param frame The frame descriptor pointer
 * @param attr Frame attribute pointer
 * @return kStatus_Success                Successfully receive a management (host reason not zero) frame frame
 * @return kStatus_NETC_RxHRZeroFrame     Frame in Rx BD ring is regular frame, need call EP_ReceiveFrame()
 * @return kStatus_NETC_RxTsrResp         Frame in Rx BD ring is Transmit Timestamp Reference Response messages, need
 *                                        call SWT_GetTimestampRefResp() to get Transmit Timestamp Reference Response
 * @return kStatus_NETC_RxFrameEmpty      Rx BD ring is empty
 * @return kStatus_NETC_RxFrameError      Frame in Rx BD ring has error, need be dropped
 * @return kStatus_InvalidArgument        No Rx BD ring is available
 * @return kStatus_NETC_LackOfResource    Appliction provided buffer is not enough
 */
status_t SWT_ReceiveFrame(swt_handle_t *handle, netc_frame_struct_t *frame, netc_frame_attr_t *attr);

/*!
 * @brief Receives management frame (host reason not zero) which will be copied in the provided buffer.
 *
 * @note The buffer size MUST be queried using SWT_GetRxFrameSize() beforehand.
 *
 * @param handle
 * @param buffer Buffer address
 * @param length Buffer length
 * @param attr Frame attribute pointer
 * @return kStatus_Success                Successfully receive a management (host reason not zero) frame frame
 * @return kStatus_InvalidArgument        No Rx BD ring is available
 */
status_t SWT_ReceiveFrameCopy(swt_handle_t *handle, void *buffer, uint32_t length, netc_frame_attr_t *attr);

/*!
 * @brief Receives Switch Transmit Timestamp Reference Response.
 *
 * @note MUST call SWT_GetRxFrameSize() beforehand to confirm get the kStatus_NETC_RxTsrResp status.
 *
 * @param handle
 * @param tsr Timestamp Reference Response pointer
 * @return kStatus_Success                Successfully receive Switch Transmit Timestamp Reference Response
 * @return kStatus_InvalidArgument        No Rx BD ring is available
 */
status_t SWT_GetTimestampRefResp(swt_handle_t *handle, swt_tsr_resp_t *tsr);

/*!
 * brief Gets the size of the pending frame in the specified receive ring buffer.
 *
 * @note Frame size without FCS, and the size will be zero when Rx BD is Timestamp Reference Response message.
 *
 * @param handle The ENET handler structure. This is the same handler pointer used in the ENET_Init.
 * @param length The length of the valid frame received.
 * @return kStatus_Success                Successfully get the length of a management (host reason not zero) frame
 * @return kStatus_NETC_RxHRZeroFrame     Frame in Rx BD ring is regular frame, need call EP_GetRxFrameSize() to get
 *                                        frame size
 * @return kStatus_NETC_RxTsrResp         Frame in Rx BD ring is Transmit Timestamp Reference Response messages, need
 *                                        call SWT_GetTimestampRefResp() to get Transmit Timestamp Reference Response
 * @return kStatus_NETC_RxFrameEmpty      Rx BD ring is empty
 * @return kStatus_NETC_RxFrameError      Frame in Rx BD ring has error, need be dropped
 * @return kStatus_InvalidArgument        No Rx BD ring is available
 */
status_t SWT_GetRxFrameSize(swt_handle_t *handle, uint32_t *length);

/*! @} */ // end of netc_swt_xfer
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_xfer
#endif

#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma region netc_swt_stat
#endif
/*! @addtogroup netc_swt_stat
 * @{
 */

/*!
 * @brief Get Switch cut through forwarding count
 *
 * Get the Cut-through frames counter of frames forwarded to at least one egress port.
 *
 * @param handle
 * @param statistic pointer to the statistic count data
 * @return kStatus_Success
 */
static inline status_t SWT_GetCutThroughForwardStatistic(swt_handle_t *handle, uint32_t *statistic)
{
    *statistic = handle->hw.base->CTFCR;
    return kStatus_Success;
}

/*!
 * @brief Get statistic of the congestion group
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_GetETMCongestionGroupStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_etmcg_stse_t *statistic);

/*!
 * @brief Get the statistic for the class queue in specified switch port
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_GetETMClassQueueStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_etmcq_stse_t *statistic);

/*!
 * @brief Get egress count table entry number
 * @note This is a static bounded index table, so all entries in the table are available for
 *       SWT_GetECStatistic()/SWT_ResetECStatistic() API
 *
 * @param handle
 * @return uint32_t
 */
static inline uint32_t SWT_GetECEntryNum(swt_handle_t *handle)
{
    return handle->hw.common->ECTCAPR & NETC_SW_ENETC_ECTCAPR_NUM_ENTRIES_MASK;
}

/*!
 * @brief Get statistic for specified egress count table entry
 *
 * @param handle
 * @param entryID
 * @param statistic
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_GetECStatistic(swt_handle_t *handle, uint32_t entryID, netc_tb_ec_stse_t *statistic);

/*!
 * @brief Reset statistic for specified egress count table entry
 *
 * @param handle
 * @param entryID
 * @return status_t
 * @return See @ref netc_cmd_error_t
 */
status_t SWT_ResetECStatistic(swt_handle_t *handle, uint32_t entryID);

/*!
 * @brief Get the port discard statistic and reason
 *
 * Get the discarded count of frames and its reasons.
 *
 * @param handle
 * @param portIdx port index
 * @param discardType Port discard type.
 * @param statistic pointer to the statistic data
 * @return kStatus_Success
 */
static inline status_t SWT_GetPortDiscardStatistic(swt_handle_t *handle,
                                                   netc_hw_port_idx_t portIdx,
                                                   netc_port_discard_tpye_t discardType,
                                                   netc_port_discard_statistic_t *statistic)
{
    NETC_PortGetDiscardStatistic(handle->hw.ports[portIdx].port, discardType, statistic);
    return kStatus_Success;
}

/*!
 * @brief Clean the Port Rx discard reason. Set the related bits to 1 to clear the specific reasons
 *
 * @param handle
 * @param portIdx port index
 * @param discardType Port discard type.
 * @param reason0
 * @param reason1
 * @return kStatus_Success
 */
static inline status_t SWT_ClearPortDiscardReason(swt_handle_t *handle,
                                                  netc_hw_port_idx_t portIdx,
                                                  netc_port_discard_tpye_t discardType,
                                                  uint32_t reason0,
                                                  uint32_t reason1)
{
    NETC_PortClearDiscardReason(handle->hw.ports[portIdx].port, discardType, reason0, reason1);
    return kStatus_Success;
}

/*!
 * @brief Clean the Port Rx discard reason. Set the related bits to 1 to clear the specific reasons
 *
 * @param handle
 * @param statistic
 * @return kStatus_Success
 */
static inline status_t SWT_GetFDBInUseEntriesNumber(swt_handle_t *handle, netc_switch_inuse_fdb_statistic_t *statistic)
{
    statistic->staticEntries     = (uint16_t)(handle->hw.base->FDBHTOR0 & NETC_SW_FDBHTOR0_STATIC_ENTRIES_MASK);
    statistic->camEntries        = (uint16_t)((handle->hw.base->FDBHTOR0 >> NETC_SW_FDBHTOR0_NUM_GENTRIES_SHIFT) &
                                       NETC_SW_FDBHTOR0_NUM_GENTRIES_MASK);
    statistic->dynamicEntries    = (uint16_t)(handle->hw.base->FDBHTOR1 & NETC_SW_FDBHTOR1_DYN_ENTRIES_MASK);
    statistic->dynamicEntriesHWM = (uint16_t)((handle->hw.base->FDBHTOR1 >> NETC_SW_FDBHTOR1_HWM_DYN_ENTRIES_SHIFT) &
                                              NETC_SW_FDBHTOR1_HWM_DYN_ENTRIES_MASK);
    return kStatus_Success;
}

/*!
 * @brief Get Switch port time gate scheduling gate list status
 *
 * @param handle
 * @param portIdx port index
 * @return Port status flags which are ORed by the enumerators in the @ref netc_port_tgsl_status_t
 */
static inline uint32_t SWT_GetPortTGSListStatus(swt_handle_t *handle, netc_hw_port_idx_t portIdx)
{
    return NETC_PortGetTGSListStatus(handle->hw.ports[portIdx].port);
}
/*! @} */ // end of netc_swt_stat
#if !(defined(__GNUC__) || defined(__ICCARM__))
#pragma endregion netc_swt_stat
#endif

#if defined(__cplusplus)
}
#endif
#endif /* FSL_NETC_SWITCH_H_ */
