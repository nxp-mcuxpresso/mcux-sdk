/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_CHANNEL_H__
#define __SRTM_CHANNEL_H__

#include "srtm_defs.h"

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Destroy SRTM channel.
 *
 * @param channel SRTM channel to start.
 */
void SRTM_Channel_Destroy(srtm_channel_t channel);

/*!
 * @brief Let SRTM channel start working.
 *
 * @param channel SRTM channel to start.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Channel_Start(srtm_channel_t channel);

/*!
 * @brief Let SRTM channel stop working.
 *
 * @param channel SRTM channel to stop.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Channel_Stop(srtm_channel_t channel);

/*!
 * @brief Send data via SRTM channel.
 *
 * @param channel SRTM channel to send data.
 * @param data start address of data to send.
 * @param len data length in bytes.
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Channel_SendData(srtm_channel_t channel, void *data, uint32_t len);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_CHANNEL_H__ */
