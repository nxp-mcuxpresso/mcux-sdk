/*
 * Copyright 2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __THREADING_ALT_H__
#define __THREADING_ALT_H__

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread.h>
#else
#include "FreeRTOS.h"
#include "semphr.h"
#endif

/**
 * @brief Mutex struct used to synchronize mbed TLS operations.
 *
 */
typedef struct
{
#ifdef __ZEPHYR__
    struct k_mutex mutex;
#else
    SemaphoreHandle_t mutex; /**< @brief FreeRTOS semaphore. */
#endif
    char is_valid; /**< @brief Flag used by mbedTLS to track wether a mutex is valid. */
} mbedtls_threading_mutex_t;

/**
 * @brief Implementation of mbedtls_alt_mutex_init for thread-safety.
 *
 */
void mbedtls_alt_mutex_init(mbedtls_threading_mutex_t *mutex);

/**
 * @brief Implementation of mbedtls_alt_mutex_free for thread-safety.
 *
 */
void mbedtls_alt_mutex_free(mbedtls_threading_mutex_t *mutex);

/*!
 * @brief  Lock the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mbedtls_alt_mutex_lock(mbedtls_threading_mutex_t *mutex);

/*!
 * @brief  Unlock the mutex
 *
 * @return 0 on success.
 *         -1 on failure
 */
int mbedtls_alt_mutex_unlock(mbedtls_threading_mutex_t *mutex);

extern void mbedtls_threading_set_alt(void (*mutex_init)(mbedtls_threading_mutex_t *),
                                      void (*mutex_free)(mbedtls_threading_mutex_t *),
                                      int (*mutex_lock)(mbedtls_threading_mutex_t *),
                                      int (*mutex_unlock)(mbedtls_threading_mutex_t *));

/*!
 * @brief  provides a function to call mbedtls_threading_set_alt() with
 * thread_alt based mutex functions required by mbedtls3x threading support
 *
 * @return void
 */
void config_mbedtls_threading_alt(void);
#endif /* ifndef __THREADING_ALT_H__ */
