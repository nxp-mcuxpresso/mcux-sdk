/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_PEERCORE_H__
#define __SRTM_PEERCORE_H__

#include "srtm_defs.h"

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM peer core state
 */
typedef enum _srtm_peercore_state
{
    SRTM_PeerCore_State_Inactive = 0x00U, /*!< Peer core is not ready to communicate */
    SRTM_PeerCore_State_Activating,       /*!< Peer core wakeup in progress */
    SRTM_PeerCore_State_Activated,        /*!< Peer core is ready to communicate */
    SRTM_PeerCore_State_Deactivating,     /*!< Peer core is going to suspend */
    SRTM_PeerCore_State_Deactivated,      /*!< Peer core suspended and not ready to communicate */
} srtm_peercore_state_t;

/**
 * @brief SRTM peer core wakeup callback function
 */
typedef srtm_status_t (*srtm_peercore_wakeup_cb_t)(srtm_peercore_t core, void *param);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create SRTM peer core object.
 *
 * @param id SRTM peer core ID allocated by application.
 * @return SRTM peer core handle, or NULL on failure.
 */
srtm_peercore_t SRTM_PeerCore_Create(uint32_t id);

/*!
 * @brief Destroy SRTM peer core object.
 *
 * @param core SRTM peer core handle.
 */
void SRTM_PeerCore_Destroy(srtm_peercore_t core);

/*!
 * @brief Get SRTM peer core ID.
 *
 * @param core SRTM peer core handle.
 * @return SRTM peer core ID.
 */
uint32_t SRTM_PeerCore_GetID(srtm_peercore_t core);

/*!
 * @brief Start SRTM peer core communication.
 *
 * @param core SRTM peer core handle.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_Start(srtm_peercore_t core);

/*!
 * @brief Stop SRTM peer core communication.
 *
 * @param core SRTM peer core handle.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_Stop(srtm_peercore_t core);

/*!
 * @brief Activate the SRTM peer core.
 *
 * @param core SRTM peer core handle.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_Activate(srtm_peercore_t core);

/*!
 * @brief Deactivate the SRTM peer core.
 *
 * @param core SRTM peer core handle.
 * @param wakeup SRTM peer core wakeup function.
 * @param param SRTM peer core wakeup parameter.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_Deactivate(srtm_peercore_t core, srtm_peercore_wakeup_cb_t wakeup, void *param);

/*!
 * @brief Add communication channel to the SRTM peer core.
 *
 * @param core SRTM peer core handle.
 * @param channel SRTM channel to add.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_AddChannel(srtm_peercore_t core, srtm_channel_t channel);

/*!
 * @brief Remove communication channel from the SRTM peer core.
 *
 * @param core SRTM peer core handle.
 * @param channel SRTM channel to remove.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_RemoveChannel(srtm_peercore_t core, srtm_channel_t channel);

/*!
 * @brief Get SRTM peer core state.
 *
 * @param core SRTM peer core handle.
 * @return SRTM peer core state.
 */
srtm_peercore_state_t SRTM_PeerCore_GetState(srtm_peercore_t core);

/*!
 * @brief Set SRTM peer core state.
 *
 * @param core SRTM peer core handle.
 * @param state SRTM peer core state to run into.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_PeerCore_SetState(srtm_peercore_t core, srtm_peercore_state_t state);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_PEERCORE_H__ */
