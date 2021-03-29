/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_SEM_H__
#define __SRTM_SEM_H__

#include <srtm_defs.h>

/*!
 * @addtogroup srtm
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief SRTM semaphore handle
 */
typedef void *srtm_sem_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create a semaphore.
 *
 * @param maxCount maximum count value of the semaphore.
 * @param initCount initial count value of the semaphore.
 * @param stack Stack for semaphore data.
 * @return Created semaphore handle, or NULL on failure.
 */
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
srtm_sem_t SRTM_Sem_Create(uint32_t maxCount, uint32_t initCount, srtm_sem_buf_t *stack);
#else
srtm_sem_t SRTM_Sem_Create(uint32_t maxCount, uint32_t initCount);
#endif

/*!
 * @brief Destroy the semaphore.
 *
 * @param sem The semaphore to destroy.
 */
void SRTM_Sem_Destroy(srtm_sem_t sem);

/*!
 * @brief Posts a semaphore.
 *
 * @param sem Semaphore handle
 * @return SRTM_Status_Success on success and others on failure.
 */
srtm_status_t SRTM_Sem_Post(srtm_sem_t sem);

/*!
 * @brief Waits on a semaphore.
 *
 * @param sem Semaphore handle
 * @param timeout   The maximum milliseconds to wait for the semaphore.
 * @return SRTM_Status_Success on success, SRTM_Status_Timeout on timeout.
 */
srtm_status_t SRTM_Sem_Wait(srtm_sem_t sem, uint32_t timeout);

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_SEM_H__ */
