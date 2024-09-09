/*
 * Copyright 2023-2024 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_els_pkc_transparent_mac.c
 *
 * This file contains the implementation of the entry points associated to the
 * mac capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */
#include "mcuxClEls.h"
#include "mcuxClPsaDriver_Functions.h"
#include "mcux_psa_els_pkc_mac.h"
#include <mbedtls/platform.h>
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
#include "mcux_psa_els_pkc_common_init.h"
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
/*
 * Entry points for MAC computation and verification as described by the PSA
 *  Cryptoprocessor Driver interface specification
 */

psa_status_t els_pkc_transparent_mac_compute(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer,
                             size_t key_buffer_size, psa_algorithm_t alg,
                             const uint8_t *input, size_t input_length,
                             uint8_t *mac, size_t mac_size,
                             size_t *mac_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    uint8_t *padded_input = NULL;
    if (PSA_ALG_IS_HMAC(alg)) {
        padded_input = mbedtls_calloc(1, MCUXCLHMAC_ELS_INPUTBUFFER_LENGTH(input_length));
        if (padded_input == NULL) {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        (void)memcpy(padded_input, input, input_length);
    }

    status = mcuxClPsaDriver_psa_driver_wrapper_mac_computeLayer(
                                        attributes,
                                        key_buffer,
                                        key_buffer_size,
                                        alg,
                                        PSA_ALG_IS_HMAC(alg) ? padded_input : input,
                                        input_length,
                                        mac,
                                        mac_size,
                                        mac_length);

    mbedtls_free(padded_input);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}


/** \defgroup psa_mac PSA driver entry points for MAC operations
 *
 *  Entry points for MAC sign setup, update, finish and verification as described by the PSA
 *  Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t els_pkc_transparent_mac_sign_setup(els_pkc_transparent_mac_operation_t *operation,
                                const psa_key_attributes_t *attributes,
                                const uint8_t *key_buffer,
                                size_t key_buffer_size, psa_algorithm_t alg)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer(attributes,
                                                               key_buffer,
                                                               key_buffer_size,
                                                               operation,
                                                               alg);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_mac_verify_setup(els_pkc_transparent_mac_operation_t *operation,
                                  const psa_key_attributes_t *attributes,
                                  const uint8_t *key_buffer,
                                  size_t key_buffer_size, psa_algorithm_t alg)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer(attributes,
                                                               key_buffer,
                                                               key_buffer_size,
                                                               operation,
                                                               alg);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_mac_update(els_pkc_transparent_mac_operation_t *operation,
                            const uint8_t *input, size_t input_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_mac_updateLayer(operation,
                                                                input,
                                                                input_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_mac_sign_finish(els_pkc_transparent_mac_operation_t *operation,
                                 uint8_t *mac, size_t mac_size,
                                 size_t *mac_length)
{
    uint8_t macCalc[MCUXCLMAC_MAX_OUTPUT_SIZE];

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

        psa_status_t status = mcuxClPsaDriver_psa_driver_wrapper_mac_finalizeLayer(operation,
                                                                               macCalc,
                                                                               mac_size,
                                                                               NULL);
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    if (status == PSA_SUCCESS)
    {
        for(unsigned int i = 0u; i < mac_size; i++)
        {
            mac[i] = macCalc[i];
        }
        *mac_length = mac_size;
    }
    return status;
}

psa_status_t els_pkc_transparent_mac_verify_finish(els_pkc_transparent_mac_operation_t *operation,
                                   const uint8_t *mac, size_t mac_length)
{
    uint8_t macCalc[ MCUXCLMAC_MAX_OUTPUT_SIZE];

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    psa_status_t status = mcuxClPsaDriver_psa_driver_wrapper_mac_finalizeLayer(operation,
                                                                               macCalc,
                                                                               mac_length,
                                                                               NULL);
    if (status == PSA_SUCCESS)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(compare_result, token, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, mac, macCalc, mac_length),
                                                              mac,
                                                              macCalc,
                                                              mac_length));
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare) != token)){
            return PSA_ERROR_GENERIC_ERROR;
        }

        if(compare_result != MCUXCSSLMEMORY_STATUS_EQUAL)
        {
            return PSA_ERROR_INVALID_SIGNATURE;
        }
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_transparent_mac_abort(els_pkc_transparent_mac_operation_t *operation)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_mac_abort(operation);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

/** @} */ // end of psa_mac
