/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_heap.h"
#include "srtm_peercore.h"
#include "srtm_peercore_struct.h"
#include "srtm_channel.h"
#include "srtm_channel_struct.h"
#include "srtm_dispatcher.h"
#include "srtm_dispatcher_struct.h"

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
srtm_peercore_t SRTM_PeerCore_Create(uint32_t id)
{
    srtm_peercore_t core = (srtm_peercore_t)SRTM_Heap_Malloc(sizeof(struct _srtm_peercore));
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
    srtm_mutex_t mutex   = SRTM_Mutex_Create(&core->mutexStatic);
#else
    srtm_mutex_t mutex   = SRTM_Mutex_Create();
#endif

    assert((core != NULL) && (mutex != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);
    SRTM_List_Init(&core->node);
    SRTM_List_Init(&core->channels);
    SRTM_List_Init(&core->pendingQ);

    core->id          = id;
    core->dispatcher  = NULL;
    core->mutex       = mutex;
    core->started     = false;
    core->state       = SRTM_PeerCore_State_Inactive;
    core->wakeupFunc  = NULL;
    core->wakeupParam = NULL;

    return core;
}

void SRTM_PeerCore_Destroy(srtm_peercore_t core)
{
    srtm_channel_t channel;
    srtm_list_t *list;

    assert(core);
    assert(!core->started);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    while (!SRTM_List_IsEmpty(&core->channels))
    {
        list = core->channels.next;
        SRTM_List_Remove(list);
        channel       = SRTM_LIST_OBJ(srtm_channel_t, node, list);
        channel->core = NULL;
        SRTM_Channel_Destroy(channel);
    }

    /* Pending Q must be cleaned by SRTM before removing peer core from it */
    assert(SRTM_List_IsEmpty(&core->pendingQ));

    SRTM_Mutex_Destroy(core->mutex);
    SRTM_Heap_Free(core);
}

uint32_t SRTM_PeerCore_GetID(srtm_peercore_t core)
{
    assert(core);

    return core->id;
}

srtm_status_t SRTM_PeerCore_Start(srtm_peercore_t core)
{
    srtm_status_t status = SRTM_Status_Success;
    srtm_channel_t channel;
    srtm_list_t *list;

    assert(core);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (core->started)
    {
        return SRTM_Status_InvalidState;
    }

    core->started = true;

    for (list = core->channels.next; list != &core->channels; list = list->next)
    {
        channel = SRTM_LIST_OBJ(srtm_channel_t, node, list);
        status  = SRTM_Channel_Start(channel);
    }

    return status;
}

srtm_status_t SRTM_PeerCore_Stop(srtm_peercore_t core)
{
    srtm_status_t status = SRTM_Status_Success;
    srtm_channel_t channel;
    srtm_list_t *list;

    assert(core);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (!core->started)
    {
        return SRTM_Status_InvalidState;
    }

    core->started = false;

    for (list = core->channels.next; list != &core->channels; list = list->next)
    {
        channel = SRTM_LIST_OBJ(srtm_channel_t, node, list);
        status  = SRTM_Channel_Stop(channel);
    }

    return status;
}

srtm_status_t SRTM_PeerCore_Activate(srtm_peercore_t core)
{
    srtm_status_t status = SRTM_Status_Success;

    assert(core);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (core->wakeupFunc != NULL)
    {
        status = core->wakeupFunc(core, core->wakeupParam);
    }

    if (status == SRTM_Status_Success)
    {
        core->state = SRTM_PeerCore_State_Activating;
    }

    /* Only Life Cycle Service knows about the real state of peer core when processing
       peer core request, so it will take responsibility to change the state to ACTIVATED */

    return status;
}

srtm_status_t SRTM_PeerCore_Deactivate(srtm_peercore_t core, srtm_peercore_wakeup_cb_t wakeup, void *param)
{
    assert(core);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    core->wakeupFunc  = wakeup;
    core->wakeupParam = param;

    core->state = SRTM_PeerCore_State_Deactivating;

    /* Only application knows about the real state of peer core when querying the peer
       core status, so it will take responsibility to change the state to DEACTIVATED */

    return SRTM_Status_Success;
}

srtm_status_t SRTM_PeerCore_AddChannel(srtm_peercore_t core, srtm_channel_t channel)
{
    assert(core);
    assert(channel);
    assert(!core->started); /* Add channel when SRTM dispatcher running is forbidden */

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: 0x%x\r\n", __func__, channel);

    if (!SRTM_List_IsEmpty(&channel->node))
    {
        return SRTM_Status_ListAddFailed;
    }

    (void)SRTM_Mutex_Lock(core->mutex);
    SRTM_List_AddTail(&core->channels, &channel->node);
    (void)SRTM_Mutex_Unlock(core->mutex);
    channel->core = core;

    return SRTM_Status_Success;
}

srtm_status_t SRTM_PeerCore_RemoveChannel(srtm_peercore_t core, srtm_channel_t channel)
{
    assert(core);
    assert(channel);
    assert(!core->started); /* Remove channel when SRTM dispatcher running is forbidden */

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: 0x%x\r\n", __func__, channel);

    if (SRTM_List_IsEmpty(&channel->node))
    {
        return SRTM_Status_ListRemoveFailed;
    }

    (void)SRTM_Mutex_Lock(core->mutex);
    SRTM_List_Remove(&channel->node);
    (void)SRTM_Mutex_Unlock(core->mutex);
    channel->core = NULL;

    return SRTM_Status_Success;
}

srtm_peercore_state_t SRTM_PeerCore_GetState(srtm_peercore_t core)
{
    assert(core);

    return core->state;
}

srtm_status_t SRTM_PeerCore_SetState(srtm_peercore_t core, srtm_peercore_state_t state)
{
    assert(core);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d\r\n", __func__, state);

    core->state = state;

    return SRTM_Status_Success;
}
