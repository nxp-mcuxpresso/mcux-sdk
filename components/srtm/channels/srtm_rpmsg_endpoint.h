/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_RPMSG_ENDPOINT_H__
#define __SRTM_RPMSG_ENDPOINT_H__

#include "srtm_channel.h"
#include "rpmsg_lite.h"

/*!
 * @addtogroup srtm_channel
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM RPMsg endpoint channel configuration fields
 */
typedef struct _srtm_rpmsg_endpoint_config
{
    struct rpmsg_lite_instance *rpmsgHandle; /*!< RPMsg handle initialized by app */
    unsigned long localAddr;                 /*!< RPMsg local endpoint address */
    unsigned long peerAddr;                  /*!< RPMsg peer endpoint address */
    const char *epName;                      /*!< RPMsg endpoint name for name service announcement */
} srtm_rpmsg_endpoint_config_t;

/**
 * @brief SRTM RPMsg endpoint channel RX callback function type.
 */
typedef int (*srtm_rpmsg_endpoint_rx_cb_t)(
    srtm_channel_t channel, void *payload, int payloadLen, unsigned long src, void *param);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create RPMsg endpoint channel.
 *
 * @param config SRTM RPMsg endpoint configuration.
 * @return SRTM channel handle on success and NULL on failure.
 */
srtm_channel_t SRTM_RPMsgEndpoint_Create(srtm_rpmsg_endpoint_config_t *config);

/*!
 * @brief Destroy RPMsg endpoint channel.
 *
 * @param channel SRTM channel to destroy.
 */
void SRTM_RPMsgEndpoint_Destroy(srtm_channel_t channel);

/*!
 * @brief Override RPMsg endpoint channel RX handler.
 *
 * By default, the RX messages are posted to dispatcher for SRTM
 * request/response/notification handling. This function is to change the default
 * behavior for functionality extension.
 *
 * @param channel SRTM channel to override RX handler.
 * @param callback User function to handle RX message.
 * @param param User parameter to be used in callback.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_RPMsgEndpoint_OverrideRxHandler(srtm_channel_t channel,
                                                   srtm_rpmsg_endpoint_rx_cb_t callback,
                                                   void *param);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_RPMSG_ENDPOINT_H__ */
