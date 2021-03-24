/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_CHANNEL_STRUCT_H__
#define __SRTM_CHANNEL_STRUCT_H__

#include "srtm_defs.h"
#include "srtm_list.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM channel struct
 */
struct _srtm_channel
{
    srtm_list_t node;     /*!< SRTM channel list node to link to a list */
    srtm_peercore_t core; /*!< SRTM peer core channel belongs to */

    void (*destroy)(srtm_channel_t channel);
    srtm_status_t (*start)(srtm_channel_t channel);
    srtm_status_t (*stop)(srtm_channel_t channel);
    srtm_status_t (*sendData)(srtm_channel_t channel, void *data, uint32_t len);
};

/*******************************************************************************
 * API
 ******************************************************************************/

/*! @} */

#endif /* __SRTM_CHANNEL_STRUCT_H__ */
