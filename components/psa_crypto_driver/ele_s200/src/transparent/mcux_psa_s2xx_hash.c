/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s2xx_hash.c
 *
 * This file contains the implementation of the entry points associated to the
 * hash capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s2xx_init.h"
#include "mcux_psa_s2xx_hash.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

#define SHA224_DIGEST_SIZE_IN_BYTES (224u / 8u)
#define SHA256_DIGEST_SIZE_IN_BYTES (256u / 8u)
#define SHA384_DIGEST_SIZE_IN_BYTES (384u / 8u)
#define SHA512_DIGEST_SIZE_IN_BYTES (512u / 8u)

static psa_status_t ele_psa_hash_alg_to_ele_hash_alg(psa_algorithm_t alg, sss_algorithm_t *mode)
{
    switch (alg)
    {
#if defined(PSA_WANT_ALG_SHA_224)
        case PSA_ALG_SHA_224:
            *mode = kAlgorithm_SSS_SHA224;
            break;
#endif /* PSA_WANT_ALG_SHA_224 */
#if defined(PSA_WANT_ALG_SHA_256)
        case PSA_ALG_SHA_256:
            *mode = kAlgorithm_SSS_SHA256;
            break;
#endif /* PSA_WANT_ALG_SHA_256 */
#if defined(PSA_WANT_ALG_SHA_384)
        case PSA_ALG_SHA_384:
            *mode = kAlgorithm_SSS_SHA384;
            break;
#endif /* PSA_WANT_ALG_SHA_384 */
#if defined(PSA_WANT_ALG_SHA_512)
        case PSA_ALG_SHA_512:
            *mode = kAlgorithm_SSS_SHA512;
            break;
#endif /* PSA_WANT_ALG_SHA_512 */
#if defined(PSA_WANT_ALG_SHA_1)
        case PSA_ALG_SHA_1:
#endif /* PSA_WANT_ALG_SHA_1 */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_SUCCESS;
}

/** \defgroup psa_hash PSA driver entry points for hashing
 *
 *  Entry points for hashing operations as described by the PSA Cryptoprocessor
 *  Driver interface specification
 *
 *  @{
 */
psa_status_t ele_s2xx_transparent_hash_setup(ele_s2xx_hash_operation_t *operation, psa_algorithm_t alg)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    if (NULL == operation)
    {
        // ELE_OSAL_LOG_ERR("hash operation is NULL");
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    memset(operation, 0, sizeof(ele_s2xx_hash_operation_t));

    if ((status = ele_psa_hash_alg_to_ele_hash_alg(alg, &operation->ctx.algorithm)) != PSA_SUCCESS)
    {
        return status;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if (sss_sscp_digest_context_init(&operation->ctx, &g_ele_ctx.sssSession, operation->ctx.algorithm,
                                     kMode_SSS_Digest) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if (sss_sscp_digest_init(&operation->ctx) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s2xx_transparent_hash_clone(const ele_s2xx_hash_operation_t *source_operation,
                                             ele_s2xx_hash_operation_t *target_operation)
{
        if (source_operation == NULL || target_operation == NULL) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
        memcpy(target_operation, source_operation, sizeof(ele_s2xx_hash_operation_t));
    //    return PSA_SUCCESS;

    /* HASH Context cloning is not supported on ELE200*/
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s2xx_transparent_hash_update(ele_s2xx_hash_operation_t *operation,
                                              const uint8_t *input,
                                              size_t input_length)
{
    if (NULL == operation)
    {
        // ELE_OSAL_LOG_ERR("operation is NULL");
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (0u == input_length)
    {
        /* This is a valid situation, no need to call ele_hash_update.
         * ele_hash_finish will produce the result.
         */
        return PSA_SUCCESS;
    }

    /* if len not zero, but pointer is NULL */
    if (NULL == input)
    {
        // ELE_OSAL_LOG_ERR("input is NULL");
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if (sss_sscp_digest_update(&operation->ctx, (uint8_t *)(uintptr_t)input, input_length) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    return PSA_SUCCESS;
}

psa_status_t ele_s2xx_transparent_hash_finish(ele_s2xx_hash_operation_t *operation,
                                              uint8_t *hash,
                                              size_t hash_size,
                                              size_t *hash_length)
{
    if (operation == NULL)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if hash_size is sufficient or not */
    if (!hash || hash_size < operation->ctx.digestFullLen)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if (sss_sscp_digest_finish(&operation->ctx, hash, &hash_size) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    *hash_length = operation->ctx.digestFullLen;

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    return PSA_SUCCESS;
}

psa_status_t ele_s2xx_transparent_hash_abort(ele_s2xx_hash_operation_t *operation)
{
    (void)sss_sscp_digest_context_free(&operation->ctx);

    /* Zeroize the context */
    memset(operation, 0, sizeof(ele_s2xx_hash_operation_t));
    return PSA_SUCCESS;
}

psa_status_t ele_s2xx_transparent_hash_compute(psa_algorithm_t alg,
                                               const uint8_t *input,
                                               size_t input_length,
                                               uint8_t *hash,
                                               size_t hash_size,
                                               size_t *hash_length)
{
    psa_status_t status       = PSA_ERROR_CORRUPTION_DETECTED;
    size_t actual_hash_length = PSA_HASH_LENGTH(alg);
    sss_sscp_digest_t ctx;
    sss_algorithm_t mode = 0;

    if ((status = ele_psa_hash_alg_to_ele_hash_alg(alg, &mode)) != PSA_SUCCESS)
    {
        return status;
    }

    if (!hash || !hash_size)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Fill the output buffer with something that isn't a valid hash
     * (barring an attack on the hash and deliberately-crafted input),
     * in case the caller doesn't check the return status properly. */

    /* If hash_size is 0 then hash may be NULL and then the
     * call to memset would have undefined behavior. */
    if (hash_size != 0u)
    {
        memset(hash, '!', hash_size);
    }

    if (hash_size < actual_hash_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if (sss_sscp_digest_context_init(&ctx, &g_ele_ctx.sssSession, mode, kMode_SSS_Digest) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    *hash_length = ctx.digestFullLen;

    if (sss_sscp_digest_one_go(&ctx, input, input_length, hash, hash_length) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if (sss_sscp_digest_context_free(&ctx) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}
/** @} */ // end of psa_hash
