/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef OSAL_MUTEX_H
#define OSAL_MUTEX_H

/** \file osal_mutex.h
 *
 * This file contains the generic mutex definitions
 *
 */

#include "osal_mutex_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief  Creates and initializes the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mcux_mutex_init(mcux_mutex_t *mutex);

/*!
 * @brief  Free the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mcux_mutex_free(mcux_mutex_t *mutex);

/*!
 * @brief  Lock the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mcux_mutex_lock(mcux_mutex_t *mutex);

/*!
 * @brief  Unlock the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mcux_mutex_unlock(mcux_mutex_t *mutex);

#ifdef __cplusplus
}
#endif

#endif /* OSAL_MUTEX_H */
