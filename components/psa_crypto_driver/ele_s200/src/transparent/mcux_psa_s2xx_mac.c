/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s2xx_mac.c
 *
 * This file contains the implementation of the entry points associated to the
 * mac capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s2xx_mac.h"

/*
 * Entry points for MAC computation and verification as described by the PSA
 *  Cryptoprocessor Driver interface specification
 */

/* Convert PSA Algorithm to ELE Algorithm, CMAC or HMAC with SHA256 */
static psa_status_t ele_psa_mac_alg_to_ele_mac_alg(psa_algorithm_t alg, sss_algorithm_t *ele_alg)
{
#if defined(PSA_WANT_ALG_CMAC)
    if (PSA_ALG_FULL_LENGTH_MAC(alg) == PSA_ALG_CMAC)
    {
        *ele_alg = kAlgorithm_SSS_CMAC_AES;
        return PSA_SUCCESS;
    }
    else
#endif /* PSA_WANT_ALG_CMAC */
#if defined(PSA_WANT_ALG_HMAC)
        if (PSA_ALG_IS_HMAC(alg))
    {
        if (PSA_ALG_HMAC_GET_HASH(alg) == PSA_ALG_SHA_256)
        {
            *ele_alg = kAlgorithm_SSS_HMAC_SHA256;
            return PSA_SUCCESS;
        }
        else
        {
            return PSA_ERROR_NOT_SUPPORTED;
        }
    }
    else
#endif /* PSA_WANT_ALG_HMAC */
    {
        return PSA_ERROR_NOT_SUPPORTED;
    }
}

/**
 *  Set MAC key which is placed in keybuffer into keyslot inside ELE
 */
static status_t set_mac_key(sss_sscp_object_t *sssKey, const uint8_t *key_buffer, size_t key_bits, sss_algorithm_t mode)
{
    sss_cipher_type_t type = 0u;

    if (mode == kAlgorithm_SSS_HMAC_SHA256)
    {
        type = kSSS_CipherType_HMAC;
    }
    else if (mode == kAlgorithm_SSS_CMAC_AES)
    {
        type = kSSS_CipherType_CMAC;
    }
    else
    {
        return kStatus_InvalidArgument;
    }
    size_t key_bytes = key_bits >> 3u;
    
    if ((sss_sscp_key_object_init(sssKey, &g_ele_ctx.keyStore)) != kStatus_SSS_Success)
    {
        return kStatus_Fail;
    }

    if ((sss_sscp_key_object_allocate_handle(sssKey, 1u, /* key id */
                                             kSSS_KeyPart_Default, type, key_bytes, kSSS_KeyProp_CryptoAlgo_MAC)) !=
        kStatus_SSS_Success)
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

psa_status_t ele_s2xx_transparent_mac_compute(const psa_key_attributes_t *attributes,
                                              const uint8_t *key_buffer,
                                              size_t key_buffer_size,
                                              psa_algorithm_t alg,
                                              const uint8_t *input,
                                              size_t input_length,
                                              uint8_t *mac,
                                              size_t mac_size,
                                              size_t *mac_length)
{
    psa_status_t status      = PSA_ERROR_CORRUPTION_DETECTED;
    sss_sscp_mac_t ctx       = {0};
    sss_algorithm_t ele_alg  = 0;
    sss_sscp_object_t sssKey = {0};
    size_t key_bits          = psa_get_key_bits(attributes);
    psa_key_type_t key_type  = psa_get_key_type(attributes);

    /* Get Algo fo ELE */
    status = ele_psa_mac_alg_to_ele_mac_alg(alg, &ele_alg);
    if (status != PSA_SUCCESS)
    {
        return status;
    }

    mac_size = PSA_MAC_LENGTH(key_type, key_bits, alg);

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* Set Key for MAC*/
    if ((set_mac_key(&sssKey, key_buffer, key_bits, ele_alg)) != kStatus_Success)
    {
        (void)mcux_mutex_unlock(&ele_hwcrypto_mutex);
        return PSA_ERROR_GENERIC_ERROR;
    }
    /* Init context for MAC*/
    if ((sss_sscp_mac_context_init(&ctx, &g_ele_ctx.sssSession, &sssKey, ele_alg, kMode_SSS_Mac)) !=
        kStatus_SSS_Success)
    {
        (void)mcux_mutex_unlock(&ele_hwcrypto_mutex);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }
    /* Call MAC one go*/
    if ((sss_sscp_mac_one_go(&ctx, (const uint8_t *)input, input_length, (uint8_t *)mac, &mac_size)) !=
        kStatus_SSS_Success)
    {
        (void)mcux_mutex_unlock(&ele_hwcrypto_mutex);
        (void)sss_sscp_mac_context_free(&ctx);
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    *mac_length = mac_size;

    /* Free context */
    if (sss_sscp_mac_context_free(&ctx) != kStatus_SSS_Success)
    {
        (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);
        return PSA_ERROR_GENERIC_ERROR;
    }

    (void)sss_sscp_key_object_free(&sssKey, kSSS_keyObjFree_KeysStoreDefragment);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    return PSA_SUCCESS;
}
/** @} */ // end of psa_mac
