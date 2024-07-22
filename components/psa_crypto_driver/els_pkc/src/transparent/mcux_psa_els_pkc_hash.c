/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_els_pkc_hash.c
 *
 * This file contains the implementation of the entry points associated to the
 * hash capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */
#include "mcuxClEls.h"
#include "mcuxClPsaDriver_Functions.h"
#include "mcux_psa_els_pkc_hash.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
#include "mcux_psa_els_pkc_common_init.h"
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

/** \defgroup psa_hash PSA driver entry points for hashing
 *
 *  Entry points for hashing operations as described by the PSA Cryptoprocessor
 *  Driver interface specification
 *
 *  @{
 */
psa_status_t els_pkc_transparent_hash_setup(els_pkc_hash_operation_t *operation,
                                             psa_algorithm_t alg)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_setup(operation, alg);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_hash_compute(psa_algorithm_t alg, const uint8_t *input,
                                               size_t input_length, uint8_t *hash,
                                               size_t hash_size, size_t *hash_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_compute(alg,
                                                             input,
                                                             input_length,
                                                             hash,
                                                             hash_size,
                                                             hash_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_hash_clone(const els_pkc_hash_operation_t *source_operation,
                                             els_pkc_hash_operation_t *target_operation)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_clone(source_operation,
                                                           target_operation);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_hash_update(els_pkc_hash_operation_t *operation,
                                              const uint8_t *input, size_t input_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_update(operation,
                                                            input,
                                                            input_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_hash_finish(els_pkc_hash_operation_t *operation,
                                              uint8_t *hash,
                                              size_t hash_size, size_t *hash_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_finish(operation,
                                                            hash,
                                                            hash_size,
                                                            hash_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_hash_abort(els_pkc_hash_operation_t *operation)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_hash_abort(operation);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}
/** @} */ // end of psa_hash
