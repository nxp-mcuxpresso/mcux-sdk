/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/** \file mcux_psa_s4xx_opaque_aead.c
 *
 * This file contains the implementations of the entry points associated to the
 * aead capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification.
 *
 */

#include "mcux_psa_s4xx_opaque_aead.h"
#include "mcux_psa_s4xx_common_key_management.h"
#include "ele_crypto.h"

#include "mcux_psa_s4xx_init.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

extern ele_s4xx_ctx_t g_ele_ctx;


/* It is essential to have NVM Manager defined with opaque driver. Return PSA_ERROR_NOT_SUPPORTED
 * if the NVM manager is not present. Since psa_crypto_wrapper will be auto-generated, we can't add
 * the check there. hence implementing it in opaque drivers for ELE.
 */
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)

psa_status_t
ele_s4xx_opaque_aead_encrypt(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer, size_t key_buffer_size,
                             psa_algorithm_t alg, const uint8_t *nonce,
                             size_t nonce_length, const uint8_t *additional_data,
                             size_t additional_data_length, const uint8_t *plaintext,
                             size_t plaintext_length, uint8_t *ciphertext,
                             size_t ciphertext_size, size_t *ciphertext_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t
ele_s4xx_opaque_aead_decrypt(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer, size_t key_buffer_size,
                             psa_algorithm_t alg, const uint8_t *nonce,
                             size_t nonce_length, const uint8_t *additional_data,
                             size_t additional_data_length, const uint8_t *ciphertext,
                             size_t ciphertext_length, uint8_t *plaintext,
                             size_t plaintext_size, size_t *plaintext_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else
/* TBD - key_permitted_alg_t - is it the right one to use ??? Remove after testing on B0*/
static psa_status_t check_hsm_aead_alg(psa_algorithm_t alg,
                                       psa_key_type_t key_type,
                                       key_permitted_alg_t *ele_alg)
{
    psa_algorithm_t default_alg = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);
    size_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    /* Only AES key type is supported, first check for that */
    switch (key_type) {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            break;
#endif /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    switch (default_alg) {
#if defined(PSA_WANT_ALG_CCM)
        case PSA_ALG_CCM:
            *ele_alg = kPermitted_CCM;
            break;
#endif /* PSA_WANT_ALG_CCM */
#if defined(PSA_WANT_ALG_GCM)
        case PSA_ALG_GCM:
            *ele_alg = kPermitted_GCM;
            break;
#endif /* PSA_WANT_ALG_GCM */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* For HSM we suport onlt tag length of 16 */
    if (tag_length != 16) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_SUCCESS;
}

/** \defgroup psa_aead PSA driver entry points for AEAD
 *
 *  Entry points for AEAD encryption and decryption as described by the PSA
 *  Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t
ele_s4xx_opaque_aead_encrypt(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer, size_t key_buffer_size,
                             psa_algorithm_t alg, const uint8_t *nonce,
                             size_t nonce_length, const uint8_t *additional_data,
                             size_t additional_data_length, const uint8_t *plaintext,
                             size_t plaintext_length, uint8_t *ciphertext,
                             size_t ciphertext_size, size_t *ciphertext_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    key_permitted_alg_t ele_alg = 0;
    ele_hsm_cipher_t ctx = { 0 };
    size_t tag_length = 0;
    uint32_t cipherHandleID = 0;
    uint32_t key_id = 0;
    /* For single part, IV is supplied by user */
    iv_generation_t flag = kHSM_IV_User;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_hsm_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS) {
        return status;
    }

    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size,
                                     &key_id)) != PSA_SUCCESS) {
        return status;
    }

    /* Nonce can't be NULL */
    if (!nonce || !nonce_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* For CCM, HSM support iv_length of only 12 */
    if (ele_alg == kPermitted_CCM) {
        if (nonce_length < 12) {
            return PSA_ERROR_NOT_SUPPORTED;
        } else {
            /* Hardcoding nonce_length to 12 if provided nonce_length > 12 */
            nonce_length = 12;
        }
    }

    /* No check for input and additional data as 0 value for these is allowed */

    /* Output buffer has to be atleast Input buffer size  -> Check for encrypt */
    if (ciphertext_size < (plaintext_length + tag_length)) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Output buffer can't be NULL */
    if (!ciphertext || !ciphertext_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Initialize the output length to the current buffer length */
    *ciphertext_length = ciphertext_size;

    /* Algo and mode */
    ctx.alg = ele_alg;
    ctx.mode = kHSM_Encrypt;
    /* Plain text input data */
    ctx.input = (uint32_t) plaintext;
    ctx.input_size  = plaintext_length;
    /* Nonce */
    ctx.iv = (uint32_t) nonce;
    ctx.iv_size = nonce_length;
    /* Key */
    ctx.keyID = key_id;
    /* Cipher text */
    ctx.output = (uint32_t) ciphertext;
    ctx.output_size = ciphertext_length;

    ele_status = ELE_OpenCipherService(S3MU, g_ele_ctx.key_store_handle, &cipherHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Aead(S3MU,
                          cipherHandleID,
                          &ctx,
                          (uint32_t) additional_data,
                          additional_data_length,
                          flag);
    status = ele_to_psa_status(ele_status);

    ele_status = ELE_CloseCipherService(S3MU, cipherHandleID);
    if (status == PSA_SUCCESS) {
        status = ele_to_psa_status(ele_status);
    }

out:
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_opaque_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, size_t nonce_length,
    const uint8_t *additional_data, size_t additional_data_length,
    const uint8_t *ciphertext, size_t ciphertext_length,
    uint8_t *plaintext, size_t plaintext_size, size_t *plaintext_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    key_permitted_alg_t ele_alg = 0;
    ele_hsm_cipher_t ctx = { 0 };
    size_t tag_length = 0;
    uint32_t cipherHandleID = 0;
    uint32_t key_id = 0;
    size_t output_length = 0;
    size_t cipher_length = 0;
    /* For single part, IV is supplied by user */
    iv_generation_t flag = kHSM_IV_User;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_hsm_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS) {
        return status;
    }

    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size,
                                     &key_id)) != PSA_SUCCESS) {
        return status;
    }

    /* Input Buffer or size can't be NULL */
    if (!ciphertext || !ciphertext_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!nonce || !nonce_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* For CCM, HSM supports iv_length of only 12 */
    if (ele_alg == kPermitted_CCM) {
        if (nonce_length != 12u) {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }

    /* No check for input and additional data as 0 value for these is allowed */

    /* ciphertext has cipher + tag */
    cipher_length = ciphertext_length - tag_length;
    /* Output buffer has to be atleast Input buffer size  -> Check for encrypt */
    if (plaintext_size < cipher_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Input buffer i.e plaintext or AAD is allowed to be 0 in encrypt
     * Operation. Hence output of a decrypt can be of size 0. Hence no
     * check involving plaintext buffer.
     */

    *plaintext_length = 0;

    /* Initialize the output length to the current buffer length */
    output_length = plaintext_size;

    /* Algo and mode */
    ctx.alg = ele_alg;
    ctx.mode = kHSM_Decrypt;
    /* Plain text input data */
    ctx.input = (uint32_t) ciphertext;
    ctx.input_size  = ciphertext_length;
    /* Nonce */
    ctx.iv = (uint32_t) nonce;
    ctx.iv_size = nonce_length;
    /* Key */
    ctx.keyID = key_id;
    /* Cipher text */
    ctx.output = (uint32_t) plaintext;
    ctx.output_size = &output_length;

    ele_status = ELE_OpenCipherService(S3MU, g_ele_ctx.key_store_handle, &cipherHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Aead(S3MU,
                          cipherHandleID,
                          &ctx,
                          (uint32_t) additional_data,
                          additional_data_length,
                          flag);
    status = ele_to_psa_status(ele_status);

    if (status == PSA_SUCCESS) {
        *plaintext_length = output_length;
    }

    ele_status = ELE_CloseCipherService(S3MU, cipherHandleID);
    status = ele_to_psa_status(ele_status);

out:
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

#endif

/** @} */ // end of psa_aead
