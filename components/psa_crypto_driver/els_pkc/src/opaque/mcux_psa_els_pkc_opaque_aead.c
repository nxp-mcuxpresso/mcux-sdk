/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/** \file mcux_psa_els_pkc_opaque_aead.c
 *
 * This file contains the implementations of the entry points associated to the
 * aead capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification.
 *
 */
#include "mcuxClEls.h"
#include "mcuxClPsaDriver_Functions.h"
#include "mcux_psa_els_pkc_opaque_aead.h"

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
#include "mcux_psa_els_pkc_common_init.h"
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

/** \defgroup psa_aead PSA driver entry points for AEAD
 *
 *  Entry points for AEAD encryption and decryption as described by the PSA
 *  Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t
els_pkc_opaque_aead_encrypt(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer, size_t key_buffer_size,
                             psa_algorithm_t alg, const uint8_t *nonce,
                             size_t nonce_length, const uint8_t *additional_data,
                             size_t additional_data_length, const uint8_t *plaintext,
                             size_t plaintext_length, uint8_t *ciphertext,
                             size_t ciphertext_size, size_t *ciphertext_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt(
                         attributes,
                         key_buffer,
                         key_buffer_size,
                         alg,
                         nonce, nonce_length,
                         additional_data,additional_data_length,
                         plaintext, plaintext_length,
                         ciphertext, ciphertext_size, ciphertext_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt(
                         attributes,
                         key_buffer,
                         key_buffer_size,
                         alg,
                         nonce, nonce_length,
                         additional_data, additional_data_length,
                         ciphertext, ciphertext_length,
                         plaintext, plaintext_size, plaintext_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_encrypt_setup(
   els_pkc_opaque_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer, size_t key_buffer_size,
   psa_algorithm_t alg)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt_setup(
                         operation, attributes, key_buffer,
                         key_buffer_size, alg);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_decrypt_setup(
    els_pkc_opaque_aead_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt_setup(
                         operation, attributes,
                         key_buffer, key_buffer_size, alg);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_set_nonce(
    els_pkc_opaque_aead_operation_t *operation,
    const uint8_t *nonce,
    size_t nonce_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_set_nonce(
                operation,
                nonce,
                nonce_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_set_lengths(
    els_pkc_opaque_aead_operation_t *operation,
    size_t ad_length,
    size_t plaintext_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status =  mcuxClPsaDriver_psa_driver_wrapper_aead_set_lengths(
                operation,
                ad_length,
                plaintext_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_update_ad(
    els_pkc_opaque_aead_operation_t *operation,
    const uint8_t *input,
    size_t input_length)
{
    psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_update_ad(
                operation,
                input,
                input_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_update(
    els_pkc_opaque_aead_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
   psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_update(
                operation,
                input, input_length,
                output, output_size,
                output_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_finish(
    els_pkc_opaque_aead_operation_t *operation,
    uint8_t *ciphertext,
    size_t ciphertext_size,
    size_t *ciphertext_length,
    uint8_t *tag,
    size_t tag_size,
    size_t *tag_length)
{
   psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_finish(
                operation,
                ciphertext, ciphertext_size, ciphertext_length,
                tag, tag_size, tag_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}


psa_status_t els_pkc_opaque_aead_verify(
    els_pkc_opaque_aead_operation_t *operation,
    uint8_t *plaintext,
    size_t plaintext_size,
    size_t *plaintext_length,
    const uint8_t *tag,
    size_t tag_length)
{
   psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_verify(
                operation,
                plaintext, plaintext_size, plaintext_length,
                tag, tag_length);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}

psa_status_t els_pkc_opaque_aead_abort(els_pkc_opaque_aead_operation_t *operation)
{
   psa_status_t status;

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    status = mcuxClPsaDriver_psa_driver_wrapper_aead_abort(operation);

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex)) {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return status;
}


/** @} */ // end of psa_aead
