/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include "srtm_channel.h"
#include "srtm_channel_struct.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_Channel_Destroy(srtm_channel_t channel)
{
    assert(channel);
    assert(channel->destroy);

    channel->destroy(channel);
}

srtm_status_t SRTM_Channel_Start(srtm_channel_t channel)
{
    assert(channel);
    assert(channel->start);

    return channel->start(channel);
}

srtm_status_t SRTM_Channel_Stop(srtm_channel_t channel)
{
    assert(channel);
    assert(channel->stop);

    return channel->stop(channel);
}

srtm_status_t SRTM_Channel_SendData(srtm_channel_t channel, void *data, uint32_t len)
{
    assert(channel);
    assert(channel->sendData);

    return channel->sendData(channel, data, len);
}
