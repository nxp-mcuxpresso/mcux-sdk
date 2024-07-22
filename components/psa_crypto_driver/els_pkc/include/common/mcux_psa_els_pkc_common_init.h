/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_ELS_PKC_COMMON_INIT_H
#define MCUX_PSA_ELS_PKC_COMMON_INIT_H

/** \file els_pkc_transparent_psa_init.h
 *
 * This file contains the declaration of the entry points associated to
 * driver initialisation and de-initialisation procedures.
 *
 */

#include "psa/crypto.h"

/* MUTEX FOR HW Modules*/
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
#include "osal_mutex.h"
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
#include "fsl_common.h"

/* MUTEX FOR HW Modules*/
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
extern mcux_mutex_t els_pkc_hwcrypto_mutex;
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

#ifdef __cplusplus
extern "C" {
#endif

extern bool g_isCryptoHWInitialized;

/*!
 * @brief Application init for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_InitHardware(void);

/*!
 * @brief Application Deinit for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic deinit for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_DeinitHardware(void);

/*!
 * @brief  Convert ELE error to PSA status
 *
 * @return PSA_SUCCESS on success. Error code from psa_status_t on
 *          failure
 */
psa_status_t els_pkc_to_psa_status(status_t els_pkc_status);

/*!
 * @brief  Mutex un/lock APIS
 *
 * @return PSA_SUCCESS on success. PSA_ERROR_GENERIC_ERROR on
 *          failure
 */

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
static inline int mcux_els_mutex_lock(void)
{
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
    return PSA_SUCCESS;
}

static inline int mcux_els_mutex_unlock(void)
{
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
    return PSA_SUCCESS;
}
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

#ifdef __cplusplus
}
#endif

#endif /* MCUX_PSA_ELS_PKC_COMMON_INIT_H */
