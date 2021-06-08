/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>

#include "srtm_heap.h"
#include "srtm_dispatcher.h"
#include "srtm_dispatcher_struct.h"
#include "srtm_peercore.h"
#include "srtm_peercore_struct.h"
#include "srtm_channel.h"
#include "srtm_channel_struct.h"
#include "srtm_rpmsg_endpoint.h"
#include "rpmsg_ns.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef SRTM_DEBUG_COMMUNICATION
#define SRTM_DEBUG_COMMUNICATION (0)
#endif

typedef struct _srtm_rpmsg_endpoint
{
    struct _srtm_channel channel;
    srtm_rpmsg_endpoint_config_t config;
    struct rpmsg_lite_endpoint *rpmsgEndpoint;
    srtm_rpmsg_endpoint_rx_cb_t rxCallback;
    void *rxCallbackParam;
    bool started;
} * srtm_rpmsg_endpoint_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static int32_t SRTM_RPMsgEndpoint_RxHandler(void *payload, uint32_t payload_len, uint32_t src, void *priv)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)priv;

    assert(handle != NULL);

#if SRTM_DEBUG_COMMUNICATION
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: RPMsg recv: \r\n\t", __func__);
    for (uint32_t i = 0U; i < payload_len; i++)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%x ", ((uint8_t *)payload)[i]);
    }
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "\r\n");
#endif

    if (handle->config.peerAddr == RL_ADDR_ANY)
    {
        handle->config.peerAddr = src;
    }

    if (handle->started)
    {
        if (handle->rxCallback != NULL)
        {
            return handle->rxCallback(&handle->channel, payload, payload_len, src, handle->rxCallbackParam);
        }

        assert(handle->channel.core);
        assert(handle->channel.core->dispatcher);

        (void)SRTM_Dispatcher_PostRecvData(handle->channel.core->dispatcher, &handle->channel, payload, payload_len);
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: Get data before channel start\r\n", __func__);
    }

    return RL_RELEASE;
}

static srtm_status_t SRTM_RPMsgEndpoint_Start(srtm_channel_t channel)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)channel;
    srtm_status_t status         = SRTM_Status_Success;

    assert(handle != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->started = true;

    return status;
}

static srtm_status_t SRTM_RPMsgEndpoint_Stop(srtm_channel_t channel)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)channel;
    srtm_status_t status         = SRTM_Status_Success;

    assert(handle != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->started = false;

    return status;
}

static srtm_status_t SRTM_RPMsgEndpoint_SendData(srtm_channel_t channel, void *data, uint32_t len)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)channel;
    srtm_status_t status         = SRTM_Status_InvalidState;

    assert(handle != NULL);
    assert(handle->config.rpmsgHandle != NULL);
    assert(handle->rpmsgEndpoint != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_DEBUG, "%s: len %d\r\n", __func__, len);

    if (handle->started)
    {
#if SRTM_DEBUG_COMMUNICATION
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: RPMsg send: \r\n\t", __func__);
        for (uint32_t i = 0U; i < len; i++)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%x ", ((uint8_t *)data)[i]);
        }
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "\r\n");
#endif
        if (rpmsg_lite_send(handle->config.rpmsgHandle, handle->rpmsgEndpoint, handle->config.peerAddr, (char *)data,
                            len, RL_BLOCK) == RL_SUCCESS)
        {
            status = SRTM_Status_Success;
        }
        else
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: RPMsg send failed\r\n", __func__);
            status = SRTM_Status_TransferFailed;
        }
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: channel not started\r\n", __func__);
    }

    return status;
}

srtm_channel_t SRTM_RPMsgEndpoint_Create(srtm_rpmsg_endpoint_config_t *config)
{
    srtm_rpmsg_endpoint_t handle;

    assert(config != NULL);
    assert(config->rpmsgHandle != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_rpmsg_endpoint_t)SRTM_Heap_Malloc(sizeof(struct _srtm_rpmsg_endpoint));
    assert(handle);

    handle->started         = false;
    handle->rxCallback      = NULL;
    handle->rxCallbackParam = NULL;
    handle->rpmsgEndpoint =
        rpmsg_lite_create_ept(config->rpmsgHandle, config->localAddr, SRTM_RPMsgEndpoint_RxHandler, handle);
    assert(handle->rpmsgEndpoint);

    memcpy(&handle->config, config, sizeof(struct _srtm_rpmsg_endpoint_config));
    if (config->localAddr == RL_ADDR_ANY)
    {
        handle->config.localAddr = handle->rpmsgEndpoint->addr;
    }

    SRTM_List_Init(&handle->channel.node);
    handle->channel.core     = NULL;
    handle->channel.destroy  = SRTM_RPMsgEndpoint_Destroy;
    handle->channel.start    = SRTM_RPMsgEndpoint_Start;
    handle->channel.stop     = SRTM_RPMsgEndpoint_Stop;
    handle->channel.sendData = SRTM_RPMsgEndpoint_SendData;

    if (config->epName != NULL)
    {
        if (rpmsg_ns_announce(config->rpmsgHandle, handle->rpmsgEndpoint, config->epName, (uint32_t)RL_NS_CREATE) !=
            RL_SUCCESS)
        {
            assert(false);
        }
    }

    return &handle->channel;
}

void SRTM_RPMsgEndpoint_Destroy(srtm_channel_t channel)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)channel;

    assert(channel != NULL);
    assert(channel->core == NULL);             /* Channel must be removed from core before destroy */
    assert(SRTM_List_IsEmpty(&channel->node)); /* Channel must not on any list */

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    rpmsg_lite_destroy_ept(handle->config.rpmsgHandle, handle->rpmsgEndpoint);

    SRTM_Heap_Free(handle);
}

srtm_status_t SRTM_RPMsgEndpoint_OverrideRxHandler(srtm_channel_t channel,
                                                   srtm_rpmsg_endpoint_rx_cb_t callback,
                                                   void *param)
{
    srtm_rpmsg_endpoint_t handle = (srtm_rpmsg_endpoint_t)(void *)channel;

    assert(handle != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->rxCallback      = callback;
    handle->rxCallbackParam = param;

    return SRTM_Status_Success;
}
