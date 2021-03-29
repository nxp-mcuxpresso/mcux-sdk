/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_MUTEX_H__
#define __SRTM_MUTEX_H__

#include <srtm_defs.h>

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM mutex handle
 */
typedef void *srtm_mutex_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create a mutex.
 *
 * @param stack Stack for mutex data.
 *
 * @return Created mutex handle, or NULL on failure.
 */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
srtm_mutex_t SRTM_Mutex_Create(srtm_mutex_buf_t *stack);
#else
srtm_mutex_t SRTM_Mutex_Create(void);
#endif

/*!
 * @brief Destroy the mutex.
 *
 * @param mutex The mutex to destroy.
 */
void SRTM_Mutex_Destroy(srtm_mutex_t mutex);

/*!
 * @brief Lock a mutex.
 *
 * @param mutex Mutex handle
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Mutex_Lock(srtm_mutex_t mutex);

/*!
 * @brief Unlock on a mutex.
 *
 * @param mutex Mutex handle
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Mutex_Unlock(srtm_mutex_t mutex);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_MUTEX_H__ */
