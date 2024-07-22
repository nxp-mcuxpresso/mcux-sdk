/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_cipher.c
 *
 * This file contains the implementation of the entry points associated to the
 * cipher capability (single-part only, multi-part (not supported in ele) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */
#include "ele_crypto.h"

#include "mcux_psa_s4xx_init.h"
#include "mcux_psa_s4xx_cipher.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

psa_status_t ele_s4xx_transparent_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *iv,
    size_t iv_length,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    generic_cipher_algo_t ele_algo = 0;
    ele_generic_cipher_t ctx = { 0 };
    uint32_t iv_addr = (uint32_t) iv;

    /* Key buffer or size can't be NULL */
    if (!key_buffer || !key_buffer_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Key size should match the key_bits in attribute */
    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits) {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Algorithm needs to be a CIPHER algo */
    if (!PSA_ALG_IS_CIPHER(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    switch (key_type) {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            switch (alg) {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                case PSA_ALG_CBC_NO_PADDING:
                    ele_algo = kAES_CBC;
                    /* IV buffer can't be NULL or size 0 */
                    if (!iv_addr || !iv_length) {
                        return PSA_ERROR_INVALID_ARGUMENT;
                    }
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kAES_ECB;
                    iv_addr = 0;
                    /* PSA specification is not very clear on 0 input for ECB.
                     * However software implementation and the tests return SUCCESS
                     * for 0 input. So adding this check here.
                     */
                    if (input_length == 0) {
                        *output_length = 0;
                        return PSA_SUCCESS;
                    }
                    break;
#endif /* PSA_WANT_ALG_ECB_NO_PADDING */
#if defined(PSA_WANT_ALG_CTR)
                case PSA_ALG_CTR:
#endif /* PSA_WANT_ALG_CTR */
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            } /* operation->alg */
            break;
#endif /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* If input length or input buffer NULL, it;s an error.
     * Special case for ECB where input = 0 may be allowed.
     * Taken care of in above code.
     */
    if (!input_length || !input) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Output buffer has to be atleast Input buffer size */
    if (output_size < input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Output buffer can't be NULL */
    if (!output || !output_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* For CBC and ECB No padding, input length has to be multiple of cipher block length */
    if ((alg == PSA_ALG_CBC_NO_PADDING || alg == PSA_ALG_ECB_NO_PADDING) &&
        input_length % PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx.data = (uint32_t) input;
    ctx.algo = ele_algo;
    ctx.iv = iv_addr;
    ctx.iv_size = iv_length;
    ctx.key = (uint32_t) key_buffer;
    ctx.key_size = key_buffer_size;
    ctx.output = (uint32_t) output;
    ctx.size = input_length;
    ctx.mode = kEncrypt;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenericCipher(S3MU, &ctx);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    *output_length = input_length;

    return status;
}

psa_status_t ele_s4xx_transparent_cipher_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    generic_cipher_algo_t ele_algo = 0;
    ele_generic_cipher_t ctx = { 0 };
    uint32_t iv_length = 0;
    uint32_t expected_op_length = 0;

    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits) {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!PSA_ALG_IS_CIPHER(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    switch (key_type) {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            switch (alg) {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                case PSA_ALG_CBC_NO_PADDING:
                    ele_algo = kAES_CBC;
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kAES_ECB;
                    /* PSA specification is not very clear on 0 input for ECB.
                     * However software implementation and the tests return SUCCESS
                     * for 0 input. So adding this check here.
                     */
                    if (input_length == 0) {
                        *output_length = 0;
                        return PSA_SUCCESS;
                    }
                    break;
#endif /* PSA_WANT_ALG_ECB_NO_PADDING */
#if defined(PSA_WANT_ALG_CTR)
                case PSA_ALG_CTR:
#endif /* PSA_WANT_ALG_CTR */
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            } /* operation->alg */
            break;
#endif /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* If input length or input buffer NULL, it;s an error.
     * Special case for ECB where input = 0 may be allowed.
     * Taken care of in above code.
     */
    if (!input_length || !input) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Output buffer can't be NULL */
    if (!output || !output_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Input length has to be multiple of block size for decrypt operation */
    if ((alg == PSA_ALG_CBC_NO_PADDING || alg == PSA_ALG_ECB_NO_PADDING) &&
        input_length % PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Find the IV length for key type and algorithm */
    iv_length =  PSA_CIPHER_IV_LENGTH(key_type, alg);


    /* Input buffer -> IV + INPUT.
     * So output length would be (input - iv_length)
     */
    expected_op_length = input_length - iv_length;

    if (output_size < expected_op_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    ctx.data = (uint32_t) (input + iv_length);
    ctx.algo = ele_algo;
    /* if algorithm doesn't support IV length, IV pointre should be NULL */
    if (iv_length) {
        ctx.iv = (uint32_t) input;
    } else {
        ctx.iv = 0;
    }
    ctx.iv_size = iv_length;
    ctx.key = (uint32_t) key_buffer;
    ctx.key_size = key_buffer_size;
    ctx.output = (uint32_t) output;
    ctx.size = expected_op_length;
    ctx.mode = kDecrypt;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenericCipher(S3MU, &ctx);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    *output_length = expected_op_length;

    return status;
}
