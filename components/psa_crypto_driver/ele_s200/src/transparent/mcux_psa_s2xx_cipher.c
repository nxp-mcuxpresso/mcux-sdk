/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s2xx_cipher.c
 *
 * This file contains the implementation of the entry points associated to the
 * cipher capability (single-part only, multi-part (not supported in ele) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s2xx_init.h"
#include "mcux_psa_s2xx_cipher.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

psa_status_t ele_s2xx_transparent_cipher_encrypt(const psa_key_attributes_t *attributes,
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
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits         = psa_get_key_bits(attributes);

    sss_algorithm_t ele_algo = 0;
    sss_sscp_symmetric_t ctx = {0};
    sss_sscp_object_t sssKey = {0};

    /* Key buffer or size can't be NULL */
    if (!key_buffer || !key_buffer_size)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Key size should match the key_bits in attribute */
    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits)
    {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Algorithm needs to be a CIPHER algo */
    if (!PSA_ALG_IS_CIPHER(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    switch (key_type)
    {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            switch (alg)
            {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                case PSA_ALG_CBC_NO_PADDING:
                    ele_algo = kAlgorithm_SSS_AES_CBC;
                    /* IV buffer can't be NULL or size 0 */
                    if (!iv || !iv_length)
                    {
                        return PSA_ERROR_INVALID_ARGUMENT;
                    }
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kAlgorithm_SSS_AES_ECB;
                    /* PSA specification is not very clear on 0 input for ECB.
                     * However software implementation and the tests return SUCCESS
                     * for 0 input. So adding this check here.
                     */
                    if (input_length == 0)
                    {
                        *output_length = 0;
                        return PSA_SUCCESS;
                    }
                    break;
#endif /* PSA_WANT_ALG_ECB_NO_PADDING */
#if defined(PSA_WANT_ALG_CTR)
                case PSA_ALG_CTR:
                    ele_algo = kAlgorithm_SSS_AES_CTR;
                    /* IV buffer can't be NULL or size 0 */
                    if (!iv || !iv_length)
                    {
                        return PSA_ERROR_INVALID_ARGUMENT;
                    }
                    break;
#endif /* PSA_WANT_ALG_CTR */
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            } /* operation->alg */
            break;
#endif        /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* If input length or input buffer NULL, it;s an error.
     * Special case for ECB where input = 0 may be allowed.
     * Taken care of in above code.
     */
    if (!input_length || !input)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Output buffer has to be atleast Input buffer size */
    if (output_size < input_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Output buffer can't be NULL */
    if (!output || !output_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* For CBC and ECB No padding, input length has to be multiple of cipher block length */
    if ((alg == PSA_ALG_CBC_NO_PADDING || alg == PSA_ALG_ECB_NO_PADDING) &&
        input_length % PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if ((sss_sscp_key_object_init(&sssKey, &g_ele_ctx.keyStore)) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_key_object_allocate_handle(&sssKey, 1u, /* key id */
                                             kSSS_KeyPart_Default, kSSS_CipherType_AES, key_buffer_size,
                                             kSSS_KeyProp_CryptoAlgo_AES)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_key_store_set_key(&g_ele_ctx.keyStore, &sssKey, key_buffer, key_buffer_size,
                                    PSA_BYTES_TO_BITS(key_buffer_size), kSSS_KeyPart_Default)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_symmetric_context_init(&ctx, &g_ele_ctx.sssSession, &sssKey, ele_algo, kMode_SSS_Encrypt)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* RUN AES */
    if ((sss_sscp_cipher_one_go(&ctx, (uint8_t *)iv, iv_length, input, output, input_length)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_symmetric_context_free(&ctx);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    };

    /* Free AES context whether AES operation succeeded or not */
    if (sss_sscp_symmetric_context_free(&ctx) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    *output_length = input_length;

    return PSA_SUCCESS;
}

psa_status_t ele_s2xx_transparent_cipher_decrypt(const psa_key_attributes_t *attributes,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 psa_algorithm_t alg,
                                                 const uint8_t *input,
                                                 size_t input_length,
                                                 uint8_t *output,
                                                 size_t output_size,
                                                 size_t *output_length)
{
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits         = psa_get_key_bits(attributes);

    sss_algorithm_t ele_algo = 0;
    sss_sscp_symmetric_t ctx = {0};
    sss_sscp_object_t sssKey = {0};

    uint32_t iv_length          = 0;
    uint32_t expected_op_length = 0;

    if (PSA_BYTES_TO_BITS(key_buffer_size) != key_bits)
    {
        /* The attributes don't match the buffer given as input */
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!PSA_ALG_IS_CIPHER(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    switch (key_type)
    {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            switch (alg)
            {
#if defined(PSA_WANT_ALG_CBC_NO_PADDING)
                case PSA_ALG_CBC_NO_PADDING:
                    ele_algo = kAlgorithm_SSS_AES_CBC;
                    break;
#endif /* PSA_WANT_ALG_CBC_NO_PADDING */
#if defined(PSA_WANT_ALG_ECB_NO_PADDING)
                case PSA_ALG_ECB_NO_PADDING:
                    ele_algo = kAlgorithm_SSS_AES_ECB;
                    /* PSA specification is not very clear on 0 input for ECB.
                     * However software implementation and the tests return SUCCESS
                     * for 0 input. So adding this check here.
                     */
                    if (input_length == 0u)
                    {
                        *output_length = 0;
                        return PSA_SUCCESS;
                    }
                    break;
#endif /* PSA_WANT_ALG_ECB_NO_PADDING */
#if defined(PSA_WANT_ALG_CTR)
                case PSA_ALG_CTR:
                    ele_algo = kAlgorithm_SSS_AES_CTR;
#endif /* PSA_WANT_ALG_CTR */
                default:
                    return PSA_ERROR_NOT_SUPPORTED;
            } /* operation->alg */
            break;
#endif        /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* If input length or input buffer NULL, it;s an error.
     * Special case for ECB where input = 0 may be allowed.
     * Taken care of in above code.
     */
    if (!input_length || !input)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Output buffer can't be NULL */
    if (!output || !output_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Input length has to be multiple of block size for decrypt operation */
    if ((alg == PSA_ALG_CBC_NO_PADDING || alg == PSA_ALG_ECB_NO_PADDING) &&
        input_length % PSA_BLOCK_CIPHER_BLOCK_LENGTH(key_type))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Find the IV length for key type and algorithm */
    iv_length = PSA_CIPHER_IV_LENGTH(key_type, alg);

    /* Input buffer -> IV + INPUT.
     * So output length would be (input - iv_length)
     */
    expected_op_length = input_length - iv_length;

    if (output_size < expected_op_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if ((sss_sscp_key_object_init(&sssKey, &g_ele_ctx.keyStore)) != kStatus_SSS_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_key_object_allocate_handle(&sssKey, 1u, /* key id */
                                             kSSS_KeyPart_Default, kSSS_CipherType_AES, key_buffer_size,
                                             kSSS_KeyProp_CryptoAlgo_AES)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_key_store_set_key(&g_ele_ctx.keyStore, &sssKey, key_buffer, key_buffer_size,
                                    PSA_BYTES_TO_BITS(key_buffer_size), kSSS_KeyPart_Default)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_symmetric_context_init(&ctx, &g_ele_ctx.sssSession, &sssKey, ele_algo, kMode_SSS_Decrypt)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* RUN AES */
    if ((sss_sscp_cipher_one_go(&ctx, (uint8_t *)input, iv_length, (input + iv_length), output, input_length)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_symmetric_context_free(&ctx);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    };

    /* Free AES context whether AES operation succeeded or not */
    if (sss_sscp_symmetric_context_free(&ctx) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    *output_length = expected_op_length;

    return PSA_SUCCESS;
}
