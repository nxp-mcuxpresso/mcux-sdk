/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s2xx_aead.c
 *
 * This file contains the implementations of the entry points associated to the
 * aead capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification.
 *
 */

#include "mcux_psa_s2xx_init.h"
#include "mcux_psa_s2xx_aead.h"

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

/* Number of valid tag lengths sizes both for CCM and GCM modes */
#define VALID_TAG_LENGTH_SIZE 7u

static psa_status_t check_generic_aead_alg(psa_algorithm_t alg, psa_key_type_t key_type, sss_algorithm_t *ele_alg)
{
    psa_algorithm_t default_alg = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);
    size_t tag_length           = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);
    size_t valid_tag_lengths[VALID_TAG_LENGTH_SIZE];

    /* Only AES key type is supported, first check for that */
    switch (key_type)
    {
#if defined(PSA_WANT_KEY_TYPE_AES)
        case PSA_KEY_TYPE_AES:
            break;
#endif /* PSA_WANT_KEY_TYPE_AES */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    switch (default_alg)
    {
#if defined(PSA_WANT_ALG_CCM)
        case PSA_ALG_CCM:
            valid_tag_lengths[0] = 4;
            valid_tag_lengths[1] = 6;
            valid_tag_lengths[2] = 8;
            valid_tag_lengths[3] = 10;
            valid_tag_lengths[4] = 12;
            valid_tag_lengths[5] = 14;
            valid_tag_lengths[6] = 16;
            *ele_alg             = kAlgorithm_SSS_AES_CCM;
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
            *ele_alg             = kAlgorithm_SSS_AES_GCM;
            break;
#endif /* PSA_WANT_ALG_GCM */
        default:
            return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Cycle through all valid tag lengths for CCM or GCM */
    uint32_t i;
    for (i = 0; i < VALID_TAG_LENGTH_SIZE; i++)
    {
        if (tag_length == valid_tag_lengths[i])
        {
            break;
        }
    }

    if (i == VALID_TAG_LENGTH_SIZE)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    return PSA_SUCCESS;
}

/**
 *  Set AEAD key which is placed in keybuffer into keyslot inside ELE
 */
static status_t aes_aead_setkey(sss_sscp_object_t *sssKey, const uint8_t *key_buffer, size_t key_bits)
{
    if (key_bits != 128u && key_bits != 192u && key_bits != 256u)
    {
        return kStatus_Fail;
    }
    size_t key_bytes = key_bits >> 3u;
    
    if ((sss_sscp_key_object_init(sssKey, &g_ele_ctx.keyStore)) != kStatus_SSS_Success)
    {
        return kStatus_Fail;
    }

    if ((sss_sscp_key_object_allocate_handle(sssKey, 1u, /* key id */
                                             kSSS_KeyPart_Default, kSSS_CipherType_AES, key_bytes,
                                             kSSS_KeyProp_CryptoAlgo_AEAD)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return kStatus_Fail;
    }

    if ((sss_sscp_key_store_set_key(&g_ele_ctx.keyStore, sssKey, key_buffer, key_bytes, key_bits,
                                    kSSS_KeyPart_Default)) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return kStatus_Fail;
    }

    return kStatus_Success;
}

/** \defgroup psa_aead PSA driver entry points for AEAD
 *
 *  Entry points for AEAD encryption and decryption as described by the PSA
 *  Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t ele_s2xx_transparent_aead_encrypt(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size,
                                               psa_algorithm_t alg,
                                               const uint8_t *nonce,
                                               size_t nonce_length,
                                               const uint8_t *additional_data,
                                               size_t additional_data_length,
                                               const uint8_t *plaintext,
                                               size_t plaintext_length,
                                               uint8_t *ciphertext,
                                               size_t ciphertext_size,
                                               size_t *ciphertext_length)
{
    psa_status_t status      = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type  = psa_get_key_type(attributes);
    size_t key_bits          = psa_get_key_bits(attributes);
    sss_algorithm_t ele_alg  = 0;
    sss_sscp_aead_t ctx      = {0};
    sss_sscp_object_t sssKey = {0};
    size_t tag_length        = 0;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_generic_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    /* S200 doesnt support plaintext_length 0 */
    if (plaintext_length == 0U)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Get the TAG length encoded in the algorithm */
    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

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

    /* Nonce can't be NULL */
    if (!nonce || !nonce_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* No check for input and additional data as 0 value for these is allowed */

    /* Output buffer has to be atleast Input buffer size  -> Check for encrypt */
    if (ciphertext_size < (plaintext_length + tag_length))
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Output buffer can't be NULL */
    if (!ciphertext || !ciphertext_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    *ciphertext_length = 0;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    if ((aes_aead_setkey(&sssKey, key_buffer, key_bits)) != kStatus_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_aead_context_init(&ctx, &g_ele_ctx.sssSession, &sssKey, ele_alg, kMode_SSS_Encrypt)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    size_t tlen = tag_length;

    /* RUN AEAD */
    if ((sss_sscp_aead_one_go(&ctx, plaintext, ciphertext, plaintext_length, (uint8_t *)nonce, nonce_length,
                              additional_data, additional_data_length, (ciphertext + plaintext_length), &tlen)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_aead_context_free(&ctx);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    };

    /* Free contexts */
    if (sss_sscp_aead_context_free(&ctx) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    *ciphertext_length = plaintext_length + tag_length;

    return PSA_SUCCESS;
}

psa_status_t ele_s2xx_transparent_aead_decrypt(const psa_key_attributes_t *attributes,
                                               const uint8_t *key_buffer,
                                               size_t key_buffer_size,
                                               psa_algorithm_t alg,
                                               const uint8_t *nonce,
                                               size_t nonce_length,
                                               const uint8_t *additional_data,
                                               size_t additional_data_length,
                                               const uint8_t *ciphertext,
                                               size_t ciphertext_length,
                                               uint8_t *plaintext,
                                               size_t plaintext_size,
                                               size_t *plaintext_length)
{
    psa_status_t status      = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type  = psa_get_key_type(attributes);
    size_t key_bits          = psa_get_key_bits(attributes);
    sss_algorithm_t ele_alg  = 0;
    sss_sscp_aead_t ctx      = {0};
    sss_sscp_object_t sssKey = {0};
    size_t tag_length        = 0;
    uint8_t *tag             = NULL;
    size_t cipher_length     = 0;

    /* Algorithm needs to be a AEAD algo */
    if (!PSA_ALG_IS_AEAD(alg))
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Validate the algorithm first */
    status = check_generic_aead_alg(alg, key_type, &ele_alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    tag_length = PSA_ALG_AEAD_GET_TAG_LENGTH(alg);

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

    /* Input Buffer or size can't be NULL */
    if (!ciphertext || !ciphertext_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!nonce || !nonce_length)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* ciphertext has cipher + tag */
    cipher_length = ciphertext_length - tag_length;
    /* Output buffer has to be atleast Input buffer size  -> Check for encrypt */

    /* S200 doesnt cipher_length 0 */
    if (cipher_length == 0U)
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (plaintext_size < cipher_length)
    {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Input buffer i.e plaintext or AAD is allowed to be 0 in encrypt
     * Operation. Hence output of a decrypt can be of size 0. Hence no
     * check involving plaintext buffer.
     */

    *plaintext_length = 0;

    /* Tag is at the end of ciphertext */
    tag = (uint8_t *)(ciphertext + cipher_length);

    if ((aes_aead_setkey(&sssKey, key_buffer, key_bits)) != kStatus_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    if ((sss_sscp_aead_context_init(&ctx, &g_ele_ctx.sssSession, &sssKey, ele_alg, kMode_SSS_Decrypt)) !=
        kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* RUN AEAD */
    if ((sss_sscp_aead_one_go(&ctx, ciphertext, plaintext, cipher_length, (uint8_t *)nonce, nonce_length,
                              additional_data, additional_data_length, tag, &tag_length)) != kStatus_SSS_Success)
    {
        /* If AEAD decrypt failed in this case we cannot differentiate between root cause
         * It may be due to some sanity check, but most likely due to tag mismatch between actual and expected value
         * So threat all fails in this case as signature mismatch */
        (void)sss_sscp_aead_context_free(&ctx);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        mcux_mutex_unlock(&ele_hwcrypto_mutex);
        return PSA_ERROR_INVALID_SIGNATURE;
    };

    /* Free used contexts */
    if (sss_sscp_aead_context_free(&ctx) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_BAD_STATE;
    }

    *plaintext_length = cipher_length;

    return PSA_SUCCESS;
}

/** @} */ // end of psa_aead
