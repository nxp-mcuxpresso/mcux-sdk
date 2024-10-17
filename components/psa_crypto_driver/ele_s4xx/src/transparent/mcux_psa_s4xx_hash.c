/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_hash.c
 *
 * This file contains the implementation of the entry points associated to the
 * hash capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "ele_crypto.h"

#include "mcux_psa_s4xx_init.h"
#include "mcux_psa_s4xx_hash.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

#define SHA224_DIGEST_SIZE_IN_BYTES  (224u / 8u)
#define SHA256_DIGEST_SIZE_IN_BYTES  (256u / 8u)
#define SHA384_DIGEST_SIZE_IN_BYTES  (384u / 8u)
#define SHA512_DIGEST_SIZE_IN_BYTES  (512u / 8u)

psa_status_t ele_psa_hash_alg_to_ele_hash_alg(psa_algorithm_t alg, hash_algo_t *mode)
{
    switch (alg) {
#if defined(PSA_WANT_ALG_SHA_224)
        case PSA_ALG_SHA_224:
            *mode = kELE_Sha224;
            break;
#endif /* PSA_WANT_ALG_SHA_224 */
#if defined(PSA_WANT_ALG_SHA_256)
        case PSA_ALG_SHA_256:
            *mode = kELE_Sha256;
            break;
#endif /* PSA_WANT_ALG_SHA_256 */
#if defined(PSA_WANT_ALG_SHA_384)
        case PSA_ALG_SHA_384:
            *mode = kELE_Sha384;
            break;
#endif /* PSA_WANT_ALG_SHA_384 */
#if defined(PSA_WANT_ALG_SHA_512)
        case PSA_ALG_SHA_512:
            *mode = kELE_Sha512;
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
psa_status_t ele_s4xx_transparent_hash_setup(ele_s4xx_hash_operation_t *operation,
                                             psa_algorithm_t alg)
{
    psa_status_t status = PSA_SUCCESS;
    status_t ele_status = kStatus_Fail;

    if (NULL == operation) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    memset(operation, 0, sizeof(ele_s4xx_hash_operation_t));

    if ((status = ele_psa_hash_alg_to_ele_hash_alg(alg, &operation->mode)) != PSA_SUCCESS) {
        return status;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_Hash_Init(S3MU, &operation->ctx, operation->mode);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_transparent_hash_clone(const ele_s4xx_hash_operation_t *source_operation,
                                             ele_s4xx_hash_operation_t *target_operation)
{
    if (source_operation == NULL || target_operation == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    memcpy(target_operation, source_operation,
           sizeof(ele_s4xx_hash_operation_t));
    return PSA_SUCCESS;
}

psa_status_t ele_s4xx_transparent_hash_update(ele_s4xx_hash_operation_t *operation,
                                              const uint8_t *input, size_t input_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;

    if (NULL == operation) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (0 == input_length) {
        /* This is a valid situation, no need to call ele_hash_update.
         * ele_hash_finish will produce the result.
         */
        return PSA_SUCCESS;
    }

    /* if len not zero, but pointer is NULL */
    if (NULL == input) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_Hash_Update(S3MU, &operation->ctx, operation->mode, input, input_length);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_transparent_hash_finish(ele_s4xx_hash_operation_t *operation,
                                              uint8_t *hash,
                                              size_t hash_size, size_t *hash_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    size_t out_length = 0;

    if (operation == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if hash_size is sufficient or not */
    switch (operation->mode) {
#if defined(PSA_WANT_ALG_SHA_224)
        case kELE_Sha224:
            if (SHA224_DIGEST_SIZE_IN_BYTES > hash_size) {
                return PSA_ERROR_BUFFER_TOO_SMALL;
            }
            out_length = SHA224_DIGEST_SIZE_IN_BYTES;
            break;
#endif /* PSA_WANT_ALG_SHA_224 */
#if defined(PSA_WANT_ALG_SHA_256)
        case kELE_Sha256:
            if (SHA256_DIGEST_SIZE_IN_BYTES > hash_size) {
                return PSA_ERROR_BUFFER_TOO_SMALL;
            }
            out_length = SHA256_DIGEST_SIZE_IN_BYTES;
            break;
#endif /* PSA_WANT_ALG_SHA_256 */
#if defined(PSA_WANT_ALG_SHA_384)
        case kELE_Sha384:
            if (SHA384_DIGEST_SIZE_IN_BYTES > hash_size) {
                return PSA_ERROR_BUFFER_TOO_SMALL;
            }
            out_length = SHA384_DIGEST_SIZE_IN_BYTES;
            break;
#endif /* PSA_WANT_ALG_SHA_256 */
#if defined(PSA_WANT_ALG_SHA_512)
        case kELE_Sha512:
            if (SHA512_DIGEST_SIZE_IN_BYTES > hash_size) {
                return PSA_ERROR_BUFFER_TOO_SMALL;
            }
            out_length = SHA512_DIGEST_SIZE_IN_BYTES;
            break;
#endif /* PSA_WANT_ALG_SHA_1 */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    if (!hash || hash_size < out_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Assign the output buffer size to 0. This will be updated by ELE */
    *hash_length = 0;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_Hash_Finish(S3MU, &operation->ctx, operation->mode,
                                 hash, hash_size, (uint32_t *) hash_length, NULL, 0U);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_transparent_hash_abort(ele_s4xx_hash_operation_t *operation)
{

    /* Zeroize the context */
    memset(operation, 0, sizeof(ele_s4xx_hash_operation_t));
    return PSA_SUCCESS;
}

psa_status_t ele_s4xx_transparent_hash_compute(psa_algorithm_t alg, const uint8_t *input,
                                               size_t input_length, uint8_t *hash,
                                               size_t hash_size, size_t *hash_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    size_t actual_hash_length = PSA_HASH_LENGTH(alg);
    hash_algo_t mode = 0;

    if ((status = ele_psa_hash_alg_to_ele_hash_alg(alg, &mode)) != PSA_SUCCESS) {
        return status;
    }

    if (!hash || !hash_size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Fill the output buffer with something that isn't a valid hash
     * (barring an attack on the hash and deliberately-crafted input),
     * in case the caller doesn't check the return status properly. */

    /* If hash_size is 0 then hash may be NULL and then the
     * call to memset would have undefined behavior. */
    if (hash_size != 0) {
        memset(hash, '!', hash_size);
    }

    if (hash_size < actual_hash_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Assign the output buffer size to 0. This will be updated by ELE */
    *hash_length = 0;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status =
        ELE_Hash(S3MU, input, input_length, hash, hash_size, (uint32_t *) hash_length, mode);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}
/** @} */ // end of psa_hash
