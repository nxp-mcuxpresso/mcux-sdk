/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_NETC_MSG_H_
#define FSL_NETC_MSG_H_

#include "fsl_netc.h"
#include "fsl_netc_endpoint.h"

#define NETC_MSG_RETURN_CODE(class, code, cookie) (((uint16_t)(class) << 8U) | ((uint16_t)(code) << 4U) | (uint16_t)(cookie))

/*!
 * @brief VSI-PSI message class id
 */
typedef enum _netc_msg_class
{
    /* PSI to VSI only */
    kNETC_MsgClassDone         = 0x01U,
    kNETC_MsgClassDenied       = 0x02U,
    kNETC_MsgClassNotSupport   = 0x03U,
    kNETC_MsgClassBusy         = 0x04U,
    kNETC_MsgClassCsumError    = 0x05U,
    kNETC_MsgClassVersionError = 0x06U,
    kNETC_MsgClassLenError     = 0x07U,
    kNETC_MsgClassTimeout      = 0x08U,
    kNETC_MsgClassDefer        = 0x0fU,
    /* Others */
    kNETC_MsgClassMacFilter       = 0x20U,
    kNETC_MsgClassVlanFilter      = 0x21U,
    kNETC_MsgClassLinkStatus      = 0x80U,
    kNETC_MsgClassLinkSpeed       = 0x81U,
    kNETC_MsgClassTimerSyncStatus = 0xe0U,
    kNETC_MsgClassIpVersion       = 0xf0U,
} netc_msg_class_t;

/*!
 * @brief MAC address filtering class cmd id
 */
typedef enum _netc_msg_mac_filter_cmd
{
    kNETC_MsgMacFilterSetMacAddr    = 0x00U,
    kNETC_MsgMacFilterAdd           = 0x01U,
    kNETC_MsgMacFilterDelete        = 0x02U,
    kNETC_MsgMacFilterSet           = 0x03U,
    kNETC_MsgMacFilterFlush         = 0x04U,
    kNETC_MsgMacFilterSetMacPromisc = 0x05U,
} netc_msg_mac_filter_cmd_t;

/*!
 * @brief MAC address filtering class specific code
 */
typedef enum _netc_msg_mac_filter_code
{
    kNETC_MsgMacFilterInvalidAddr   = 0x0U, /* Invalid MAC address                                    */
    kNETC_MsgMacFilterDuplicateAddr = 0x1U, /* Duplicate MAC addr (‘set primary’, ‘add entry’)        */
    kNETC_MsgMacFilterAddrNotFound  = 0x2U, /* MAC addr not found (‘del entry’)                       */
    kNETC_MsgMacFilterNoResource    = 0x3U, /* No resource (not enough exact-match entries available) */
    kNETC_MsgMacFilterNotSupported  = 0x4U, /* Not supported: HT size mismatch                        */
} netc_msg_mac_filter_code_t;

/*!
 * @brief VLAN filtering class cmd id
 */
typedef enum _netc_msg_vlan_filter_cmd
{
    kNETC_MsgVlanFilterAdd            = 0x00U,
    kNETC_MsgVlanFilterDelete         = 0x01U,
    kNETC_MsgVlanFilterSet            = 0x02U,
    kNETC_MsgVlanFilterFlush          = 0x03U,
    kNETC_MsgVlanFilterSetVlanPromisc = 0x04U,
} netc_msg_vlan_filter_cmd_t;

/*!
 * @brief VLAN filtering class specific code
 */
typedef enum _netc_msg_vlan_filter_code
{
    kNETC_MsgVlanFilterInvalidVlan   = 0x0U, /* Invalid VLAN                                    */
    kNETC_MsgVlanFilterDuplicateVlan = 0x1U, /* Duplicate VLAN (‘add entry’)        */
    kNETC_MsgVlanFilterAddrNotFound  = 0x2U, /* VLAN not found (‘del entry’)                       */
    kNETC_MsgVlanFilterNoResource    = 0x3U, /* No resource (not enough exact-match entries available) */
    kNETC_MsgVlanFilterNotSupported  = 0x4U, /* Not supported: HT size mismatch                        */
} netc_msg_vlan_filter_code_t;

/*!
 * @brief Get link status class cmd id
 */
typedef enum _netc_msg_link_status_cmd
{
    kNETC_MsgLinkStatusGet          = 0x00U,
    kNETC_MsgLinkStatusEnableNotify = 0x01U,
    kNETC_MsgLinkStatusCancelNotify = 0x02U,
} netc_msg_link_status_cmd_t;

/*!
 * @brief Get link status class specific code
 */
typedef enum _netc_msg_link_status_code
{
    kNETC_MsgLinkStatusUp   = 0x00U,
    kNETC_MsgLinkStatusDown = 0x01U,
} netc_msg_link_status_code_t;

/*!
 * @brief Get link speed class cmd id
 */
typedef enum _netc_msg_link_speed_cmd
{
    kNETC_MsgLinkSpeedGet          = 0x00U,
    kNETC_MsgLinkSpeedEnableNotify = 0x01U,
    kNETC_MsgLinkSpeedCancelNotify = 0x02U,
} netc_msg_link_speed_cmd_t;

/*!
 * @brief Get link speed class specific code
 */
typedef enum _netc_msg_link_speed_code
{
    kNETC_MsgLinkSpeedUnKnown    = 0x00U,
    kNETC_MsgLinkSpeed10HD       = 0x01U,
    kNETC_MsgLinkSpeed10FD       = 0x02U,
    kNETC_MsgLinkSpeed100HD      = 0x03U,
    kNETC_MsgLinkSpeed100FD      = 0x04U,
    kNETC_MsgLinkSpeed1000       = 0x05U,
    kNETC_MsgLinkSpeed2500       = 0x06U,
    kNETC_MsgLinkSpeed5000       = 0x07U,
    kNETC_MsgLinkSpeed10G        = 0x08U,
    kNETC_MsgLinkSpeed25G        = 0x09U,
    kNETC_MsgLinkSpeed50G        = 0x0aU,
    kNETC_MsgLinkSpeed100G       = 0x0bU,
    kNETC_MsgLinkSpeedNotSupport = 0x0fU,
} netc_msg_link_speed_code_t;

/*!
 * @brief Get timer sync status class cmd id
 */
typedef enum _netc_msg_timer_sync_status_cmd
{
    kNETC_MsgTimerSyncStatusGet = 0x00U,
} netc_msg_timer_sync_status_cmd_t;

/*!
 * @brief Get IP version class cmd id
 */
typedef enum _netc_msg_ip_version_cmd
{
    kNETC_MsgIpVersionMJ  = 0x00U,
    kNETC_MsgIpVersionMN  = 0x01U,
    kNETC_MsgIpVersionINT = 0x02U,
    kNETC_MsgIpVersionMNT = 0x03U,
    kNETC_MsgIpVersionCFG = 0x04U,
} netc_msg_ip_version_cmd_t;

/*!
 * @brief VSI-PSI message header format
 */
typedef struct _netc_msg_header
{
    uint16_t crc16;
    uint8_t classId;
    uint8_t cmdId;
    uint8_t protoVer;
    uint8_t len;
    uint8_t reserved1;
    uint8_t cookie;
    uint8_t reserved2[8];
} netc_msg_header_t;

/*!
 * @brief Exact Match table query result
 */
typedef struct _emtable_query_result
{
    uint8_t valid;     /* Valid result or not */
    uint8_t match;     /* If address matches to one entry */
    uint16_t siBitMap; /* The siBitMap of mac matched entry */
    uint16_t index;    /* Index of mac matched entry */
} emtable_query_result_t;

/*!
 * @brief NETC PSI receives message from VSI
 *
 * @param handle
 * @param vsi      vsi number.
 * @param msgInfo  PSI received message from VSI
 * @return status_t
 */
status_t EP_PsiRxMsg(ep_handle_t *handle, netc_vsi_number_t vsi, netc_psi_rx_msg_t *msgInfo);

/*!
 * @brief NETC processes PSI received message from VSI
 *
 * @param handle
 * @param vsi      vsi number.
 * @param msgInfo  PSI received message from VSI
 */
void EP_PsiHandleRxMsg(ep_handle_t *handle, uint8_t vsi, netc_psi_rx_msg_t *msgInfo);

/*!
 * @brief NETC notify VSI for link status and speed
 *
 * @param handle
 */
void EP_PsiNotifyLink(ep_handle_t *handle);
#endif /* FSL_NETC_MSG_H_ */
