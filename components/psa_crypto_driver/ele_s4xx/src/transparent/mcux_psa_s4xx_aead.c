/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/** \file mcux_psa_s4xx_aead.c
 *
 * This file contains the implementations of the entry points associated to the
 * aead capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification.
 *
 */

#include "ele_crypto.h"

#include "mcux_psa_s4xx_init.h"
#include "mcux_psa_s4xx_aead.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

/* Number of valid tag lengths sizes both for CCM and GCM modes */
#define VALID_TAG_LENGTH_SIZE 7

static psa_status_t check_generic_aead_alg(psa_algorithm_t alg,
                                           psa_key_type_t key_type,
                                           generic_aead_algo_t *ele_alg)
{
    psa_algorithm_t default_alg = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);
    size_t tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);
    size_t valid_tag_lengths[VALID_TAG_LENGTH_SIZE];

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
            valid_tag_lengths[0] = 4;
            valid_tag_lengths[1] = 6;
            valid_tag_lengths[2] = 8;
            valid_tag_lengths[3] = 10;
            valid_tag_lengths[4] = 12;
            valid_tag_lengths[5] = 14;
            valid_tag_lengths[6] = 16;
            *ele_alg = kAES_CCM;
            break;
#endif /* PSA_WANT_ALG_CCM */
#if defined(PSA_WANT_ALG_GCM)
        case PSA_ALG_GCM:
            valid_tag_lengths[0] = 4;
            valid_tag_lengths[1] = 8;
            valid_tag_lengths[2] = 12;
            valid_tag_lengths[3] = 13;
            valid_tag_lengths[4] = 14;
            valid_tag_lengths[5] = 15;
            valid_tag_lengths[6] = 16;
            *ele_alg = kAES_GCM;
            break;
#endif /* PSA_WANT_ALG_GCM */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Cycle through all valid tag lengths for CCM or GCM */
    uint32_t i;
    for (i = 0; i < VALID_TAG_LENGTH_SIZE; i++) {
        if (tag_length == valid_tag_lengths[i]) {
            break;
        }
    }

    if (i == VALID_TAG_LENGTH_SIZE) {
        return PSA_ERROR_INVALID_ARGUMENT;
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
ele_s4xx_transparent_aead_encrypt(const psa_key_attributes_t *attributes,
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
    size_t key_bits = psa_get_key_bits(attributes);
    generic_aead_algo_t ele_alg = 0;
    ele_generic_aead_t ctx = { 0 };
    size_t tag_length = 0;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_generic_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Get the TAG length encoded in the algorithm */
    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    /* Key buffer or size can't be NULL */
    if (!key_buffer || !key_buffer_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Key size should match the key_bits in attribute */
    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits) {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Nonce can't be NULL */
    if (!nonce || !nonce_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
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

    *ciphertext_length = 0;

    /* additional data */
    ctx.aad = (uint32_t) additional_data;
    ctx.aad_size = additional_data_length;
    /* Algo and mode */
    ctx.algo = ele_alg;
    ctx.mode = kEncrypt;
    /* Plain text input data */
    ctx.data = (uint32_t) plaintext;
    ctx.size  = plaintext_length;
    /* Nonce */
    ctx.iv = (uint32_t) nonce;
    ctx.iv_size = nonce_length;
    /* Key */
    ctx.key = (uint32_t) key_buffer;
    ctx.key_size = key_bits / 8;
    /* Cipher text */
    ctx.output = (uint32_t) ciphertext;
    /* tag */
    ctx.tag = (uint32_t) (ciphertext + plaintext_length);
    ctx.tag_size = tag_length;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenericAead(S3MU, &ctx);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    if (status == PSA_SUCCESS) {
        *ciphertext_length = plaintext_length + tag_length;
    }

    return status;
}

psa_status_t ele_s4xx_transparent_aead_decrypt(
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
    size_t key_bits = psa_get_key_bits(attributes);
    generic_aead_algo_t ele_alg = 0;
    ele_generic_aead_t ctx = { 0 };
    size_t tag_length = 0;
    uint8_t *tag = NULL;
    size_t cipher_length = 0;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_generic_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS) {
        return status;
    }

    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

    /* Key buffer or size can't be NULL */
    if (!key_buffer || !key_buffer_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Key size should match the key_bits in attribute */
    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits) {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Input Buffer or size can't be NULL */
    if (!ciphertext || !ciphertext_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!nonce || !nonce_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

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

    /* Tag is at the end of ciphertext */
    tag = (uint8_t *) (ciphertext + cipher_length);

    /* additional data */
    ctx.aad = (uint32_t) additional_data;
    ctx.aad_size = additional_data_length;
    /* Algo and mode */
    ctx.algo = ele_alg;
    ctx.mode = kDecrypt;
    /* Nonce */
    ctx.iv = (uint32_t) nonce;
    ctx.iv_size = nonce_length;
    /* Key */
    ctx.key = (uint32_t) key_buffer;
    ctx.key_size = key_bits / 8;
    /* Cipher text Input data */
    ctx.data = (uint32_t) ciphertext;
    ctx.size  = cipher_length;
    /* tag */
    ctx.tag = (uint32_t) tag;
    ctx.tag_size = tag_length;
    /* Plain text output data */
    ctx.output = (uint32_t) plaintext;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenericAead(S3MU, &ctx);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    if (status == PSA_SUCCESS) {
        *plaintext_length = cipher_length;
    } else {
	/* 
	 * ELE doesn't return a specific error in case the signature is invalid,
	 * which is required by PSA specification. As a workaround parameter checks
	 * have ben done before calling the ELE_GenericAEAD function. Expectation
	 * is that the only case where ELE would return error would be when there
	 * is invalid signature. This may not always hold good. This is a 
	 * workaround for now.
	 */
	status = PSA_ERROR_INVALID_SIGNATURE;
    }

    return status;
}

/** @} */ // end of psa_aead
