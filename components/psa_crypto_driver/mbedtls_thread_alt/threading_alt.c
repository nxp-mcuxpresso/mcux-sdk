/*
 * Copyright 2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "common.h"

#if defined(MBEDTLS_THREADING_C) && defined(MBEDTLS_THREADING_ALT)
#include "mbedtls/threading.h"
#include "threading_alt.h"
/**
 * @brief Implementation of mutex_init for thread-safety.
 *
 */
void mbedtls_alt_mutex_init(mbedtls_threading_mutex_t *mutex)
{
#ifdef __ZEPHYR__
    k_mutex_init(&mutex->mutex);

    mutex->is_valid = 1;

#else
    mutex->mutex = xSemaphoreCreateMutex();

    if (mutex->mutex != NULL)
    {
        mutex->is_valid = 1;
    }
    else
    {
        mutex->is_valid = 0;
    }
#endif
}

/**
 * @brief Implementation of mutex_free for thread-safety.
 *
 */
void mbedtls_alt_mutex_free(mbedtls_threading_mutex_t *mutex)
{
    if (mutex->is_valid == 1)
    {
#ifdef __ZEPHYR__
#else
        vSemaphoreDelete(mutex->mutex);
#endif
        mutex->is_valid = 0;
    }
}

/**
 * @brief Implementation of mutex_lock for thread-safety.
 *
 * @return 0 if successful, -1 if not
 */
int mbedtls_alt_mutex_lock(mbedtls_threading_mutex_t *mutex)
{
    int ret = MBEDTLS_ERR_THREADING_BAD_INPUT_DATA;

    if (mutex->is_valid == 1)
    {
#ifdef __ZEPHYR__
        k_mutex_lock(&mutex->mutex, K_FOREVER);
        ret = 0;
#else
        if (xSemaphoreTake(mutex->mutex, portMAX_DELAY))
        {
            ret = 0;
        }
        else
        {
            ret = MBEDTLS_ERR_THREADING_MUTEX_ERROR;
        }
#endif
    }
    return ret;
}

/**
 * @brief Implementation of mutex_unlock for thread-safety.
 *
 * @return 0 if successful, -1 if not
 */
int mbedtls_alt_mutex_unlock(mbedtls_threading_mutex_t *mutex)
{
    int ret = MBEDTLS_ERR_THREADING_BAD_INPUT_DATA;

    if (mutex->is_valid == 1)
    {
#ifdef __ZEPHYR__
        k_mutex_unlock(&mutex->mutex);
        ret = 0;
#else
        if (xSemaphoreGive(mutex->mutex))
        {
            ret = 0;
        }
        else
        {
            ret = MBEDTLS_ERR_THREADING_MUTEX_ERROR;
        }
#endif
    }

    return ret;
}

void config_mbedtls_threading_alt(void)
{
    /* Configure mbedtls to use threading alt mutexes. */
    mbedtls_threading_set_alt(mbedtls_alt_mutex_init, mbedtls_alt_mutex_free, mbedtls_alt_mutex_lock,
                              mbedtls_alt_mutex_unlock);
}

#endif /* MBEDTLS_THREADING_C && MBEDTLS_THREADING_ALT */
