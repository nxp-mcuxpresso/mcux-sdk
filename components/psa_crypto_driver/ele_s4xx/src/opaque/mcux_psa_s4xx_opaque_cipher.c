/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_opaque_cipher.c
 *
 * This file contains the implementation of the entry points associated to the
 * cipher capability (single-part only, multi-part (not supported in ele) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s4xx_opaque_cipher.h"
#include "ele_crypto.h"
#include "mcux_psa_s4xx_common_key_management.h"

#include "mcux_psa_s4xx_common_init.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

extern ele_s4xx_ctx_t g_ele_ctx;

/* It is essential to have NVM Manager defined with opaque driver. Return PSA_ERROR_NOT_SUPPORTED
 * if the NVM manager is not present. Since psa_crypto_wrapper will be auto-generated, we can't add
 * the check there. hence implementing it in opaque drivers for ELE.
 */
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)

psa_status_t ele_s4xx_opaque_cipher_encrypt(
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
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_cipher_decrypt(
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
    return PSA_ERROR_NOT_SUPPORTED;
}

#else
psa_status_t ele_s4xx_opaque_cipher_encrypt(
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
    key_permitted_alg_t ele_algo = 0;
    ele_hsm_cipher_t ctx = { 0 };
    uint32_t iv_addr = (uint32_t) iv;
    uint32_t cipherHandleID = 0;
    uint32_t key_id = 0;

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size,
                                     &key_id)) != PSA_SUCCESS) {
        return status;
    }

    if (!PSA_ALG_IS_CIPHER(alg)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* PSA Algorithm and ele alg matches. This check can be skipped if needed */
    switch (key_type) {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            switch (alg) {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                case PSA_ALG_CBC_NO_PADDING:
                    ele_algo = kPermitted_CBC;
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kPermitted_ECB;
                    iv_addr = 0;
                    break;
#endif /* PSA_WANT_ALG_ECB_NO_PADDING */
#if defined(PSA_WANT_ALG_CTR)
                case PSA_ALG_CTR:
                    ele_algo = kPermitted_CTR;
                    break;
#endif /* PSA_WANT_ALG_CTR */
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            } /* operation->alg */
            break;
#endif /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* If input length or input buffer NULL, its an error.
     * Special case for ECB where input = 0 may be allowed.
     * Taken care of in above code.
     */
    if (!input_length || !input) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* ele_crupto by default passes input length as output size so buffer can't be smaller than that */
    if (output_size < input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Output buffer can't be NULL */
    if (!output || !output_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ((alg == PSA_ALG_CBC_NO_PADDING || alg == PSA_ALG_ECB_NO_PADDING) &&
        input_length % PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    ctx.keyID       = key_id;
    ctx.alg         = ele_algo;
    ctx.input       = (uint32_t) input;
    ctx.input_size  = input_length;
    ctx.iv          = iv_addr;
    ctx.iv_size     = iv_length;
    ctx.mode        = kHSM_Encrypt;
    ctx.output      = (uint32_t) output;
    ctx.output_size = output_length;    /* OUT parameter filled by ELE */

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_OpenCipherService(S3MU, g_ele_ctx.key_store_handle, &cipherHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Cipher(S3MU, cipherHandleID, &ctx);
    status = ele_to_psa_status(ele_status);

    ele_status = ELE_CloseCipherService(S3MU, cipherHandleID);
    status = ele_to_psa_status(ele_status);

out:
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_opaque_cipher_decrypt(
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
    key_permitted_alg_t ele_algo = 0;
    ele_hsm_cipher_t ctx = { 0 };
    uint32_t iv_length = 0;
    uint32_t input_cipher_length = 0;
    uint32_t cipherHandleID = 0;
    uint32_t key_id = 0;

    /* TBD - do we need NULL check for input, output and key */

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_buffer_size,
                                     &key_id)) != PSA_SUCCESS) {
        return status;
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
                    ele_algo = kPermitted_CBC;
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kPermitted_ECB;
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
                    ele_algo = kPermitted_CTR;
                    break;
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

    /* Input size */
    input_cipher_length = input_length - iv_length;

    if (output_size < input_cipher_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    ctx.alg = ele_algo;
    /* Cipher data follows the IV. So pointer to input would need to be advanced */
    ctx.input = (uint32_t) (input + iv_length);
    ctx.input_size = input_cipher_length;
    ctx.iv_size = iv_length;
    /* if algorithm doesn't support IV length, IV pointre should be NULL */
    if (iv_length) {
        /* iv is at start of input buffer */
        ctx.iv = (uint32_t) input;
    } else {
        ctx.iv = 0;
    }
    ctx.keyID = key_id;
    /* Size of this buffer is assumed to be of ctx.input_size */
    ctx.mode = kHSM_Decrypt;
    ctx.output = (uint32_t) output;
    /* ELE will return the output_length */
    ctx.output_size = output_length;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_OpenCipherService(S3MU, g_ele_ctx.key_store_handle, &cipherHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Cipher(S3MU, cipherHandleID, &ctx);
    status = ele_to_psa_status(ele_status);

    ele_status = ELE_CloseCipherService(S3MU, cipherHandleID);
    status = ele_to_psa_status(ele_status);

out:
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}
#endif
