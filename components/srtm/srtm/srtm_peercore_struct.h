/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_PEERCORE_STRUCT_H__
#define __SRTM_PEERCORE_STRUCT_H__

#include "srtm_defs.h"
#include "srtm_list.h"
#include "srtm_mutex.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM peer core struct
 */
struct _srtm_peercore
{
    uint32_t id;          /*!< SRTM peer core ID */
    srtm_list_t node;     /*!< SRTM peer core list node to link to a list */
    srtm_list_t channels; /*!< SRTM channel list to maintain channels added to the peer core */
    srtm_list_t pendingQ; /*!< Pending messages queue */

    srtm_dispatcher_t dispatcher;
    srtm_mutex_t mutex;
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_mutex_buf_t mutexStatic;
#endif

    bool started;
    srtm_peercore_state_t state;
    srtm_peercore_wakeup_cb_t wakeupFunc;
    void *wakeupParam;
};

/*******************************************************************************
 * API
 ******************************************************************************/

/*! @} */

#endif /* __SRTM_PEERCORE_STRUCT_H__ */
