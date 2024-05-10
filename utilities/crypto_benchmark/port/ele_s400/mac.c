/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "crypto_benchmark.h"
#include "crypto_benchmark_mac.h"
#include "ele_crypto.h"
#include "ele.h"

status_t wrapper_mac_compute(mac_alg_t alg,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *mac,
                             size_t *mac_size,
                             const uint8_t *key,
                             size_t key_length)
{
    status_t status    = kStatus_Fail;
    mac_algo_t ele_alg = (mac_algo_t)alg;

    status = ELE_GenericHmac(S3MU, input, input_length, mac, mac_size, key, key_length, ele_alg);

    return status;
}

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE == 1u)
status_t wrapper_hmac_sha256_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id)
{
    uint16_t mac_size;
    ele_mac_t conf;
    conf.mac_handle_id = g_ele_ctx.mac_handle;
    conf.key_id        = key_id;
    conf.payload       = (uint32_t)input;
    conf.payload_size  = input_length;
    conf.mac           = (uint32_t)mac;
    conf.mac_size      = 32u;
    conf.alg           = kPermitted_HMAC_SHA256;
    conf.mode          = kMAC_Generate;

    return ELE_Mac(S3MU, &conf, NULL, &mac_size);
}

status_t wrapper_hmac_sha256_opaque_setup(void)
{
    status_t status = kStatus_Fail;

    /* Create a keystore */
    ele_keystore_t keystore_param;
    keystore_param.id            = KEYSTORE_ID;
    keystore_param.nonce         = KEYSTORE_NONCE;
    keystore_param.max_updates   = 0xff;
    keystore_param.min_mac_check = false;
    keystore_param.min_mac_len   = 0u;

    status = ELE_CreateKeystore(S3MU, g_ele_ctx.session_handle, &keystore_param, &g_ele_ctx.keystore_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set up key management */
    status = ELE_OpenKeyService(S3MU, g_ele_ctx.keystore_handle, &g_ele_ctx.key_management_handle);
    if (status != kStatus_Success)
    {
        ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
        return status;
    }

    /* Open a MAC service */
    status = ELE_OpenMacService(S3MU, g_ele_ctx.keystore_handle, &g_ele_ctx.mac_handle);
    if (status != kStatus_Success)
    {
        ELE_CloseKeyService(S3MU, g_ele_ctx.key_management_handle);
        ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
        return status;
    }

    return status;
}

status_t wrapper_hmac_sha256_opaque_cleanup(void)
{
    status_t status = kStatus_Fail;

    status = ELE_CloseMacService(S3MU, g_ele_ctx.mac_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = ELE_CloseKeyService(S3MU, g_ele_ctx.key_management_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

status_t wrapper_hmac_sha256_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id)
{
    uint16_t key_size_out = 0u;
    ele_gen_key_t cfg     = {0u};

    /* Generate a key */
    cfg.key_type      = kKeyType_HMAC;
    cfg.key_lifetime  = kKey_Persistent;
    cfg.key_usage     = kKeyUsage_SignMessage | kKeyUsage_VerifyMessage;
    cfg.key_size      = key_size;
    cfg.permitted_alg = kPermitted_HMAC_SHA256;
    cfg.pub_key_addr  = 0u;
    cfg.pub_key_size  = 0u;
    cfg.key_group     = 1u;

    return ELE_GenerateKey(S3MU, g_ele_ctx.key_management_handle, &cfg, hmac_key_id, &key_size_out, false, false);
}

status_t wrapper_hmac_sha256_opaque_key_delete(uint32_t hmac_key_id)
{
    return ELE_DeleteKey(S3MU, g_ele_ctx.key_management_handle, hmac_key_id, false, false);
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE == 1u)
status_t wrapper_hmac_sha384_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id)
{
    uint16_t mac_size;
    ele_mac_t conf;
    conf.mac_handle_id = g_ele_ctx.mac_handle;
    conf.key_id        = key_id;
    conf.payload       = (uint32_t)input;
    conf.payload_size  = input_length;
    conf.mac           = (uint32_t)mac;
    conf.mac_size      = 48u;
    conf.alg           = kPermitted_HMAC_SHA384;
    conf.mode          = kMAC_Generate;

    return ELE_Mac(S3MU, &conf, NULL, &mac_size);
}

status_t wrapper_hmac_sha384_opaque_setup(void)
{
    status_t status = kStatus_Fail;

    /* Create a keystore */
    ele_keystore_t keystore_param;
    keystore_param.id            = KEYSTORE_ID;
    keystore_param.nonce         = KEYSTORE_NONCE;
    keystore_param.max_updates   = 0xff;
    keystore_param.min_mac_check = false;
    keystore_param.min_mac_len   = 0u;

    status = ELE_CreateKeystore(S3MU, g_ele_ctx.session_handle, &keystore_param, &g_ele_ctx.keystore_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set up key management */
    status = ELE_OpenKeyService(S3MU, g_ele_ctx.keystore_handle, &g_ele_ctx.key_management_handle);
    if (status != kStatus_Success)
    {
        ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
        return status;
    }

    /* Open a MAC service */
    status = ELE_OpenMacService(S3MU, g_ele_ctx.keystore_handle, &g_ele_ctx.mac_handle);
    if (status != kStatus_Success)
    {
        ELE_CloseKeyService(S3MU, g_ele_ctx.key_management_handle);
        ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
        return status;
    }

    return status;
}

status_t wrapper_hmac_sha384_opaque_cleanup(void)
{
    status_t status = kStatus_Fail;

    status = ELE_CloseMacService(S3MU, g_ele_ctx.mac_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = ELE_CloseKeyService(S3MU, g_ele_ctx.key_management_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

status_t wrapper_hmac_sha384_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id)
{
    uint16_t key_size_out = 0u;
    ele_gen_key_t cfg     = {0u};

    /* Generate a key */
    cfg.key_type      = kKeyType_HMAC;
    cfg.key_lifetime  = kKey_Persistent;
    cfg.key_usage     = kKeyUsage_SignMessage | kKeyUsage_VerifyMessage;
    cfg.key_size      = key_size;
    cfg.permitted_alg = kPermitted_HMAC_SHA384;
    cfg.pub_key_addr  = 0u;
    cfg.pub_key_size  = 0u;
    cfg.key_group     = 1u;

    return ELE_GenerateKey(S3MU, g_ele_ctx.key_management_handle, &cfg, hmac_key_id, &key_size_out, false, false);
}

status_t wrapper_hmac_sha384_opaque_key_delete(uint32_t hmac_key_id)
{
    return ELE_DeleteKey(S3MU, g_ele_ctx.key_management_handle, hmac_key_id, false, false);
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE */

#if defined(CRYPTO_BENCHMARK_FAST_HMAC) && (CRYPTO_BENCHMARK_FAST_HMAC == 1u)
status_t wrapper_fast_mac_start(const uint8_t *key)
{
    status_t status = kStatus_Fail;

    status = ELE_FastMacStart(S3MU, key);

    return status;
}

status_t wrapper_fast_mac_proceed(const uint8_t *input, size_t input_length, uint8_t *mac)
{
    status_t status = kStatus_Fail;

    status = ELE_FastMacProceed(S3MU, input, mac, input_length);

    return status;
}

status_t wrapper_fast_mac_end(void)
{
    status_t status = kStatus_Fail;

    status = ELE_FastMacEnd(S3MU);

    return status;
}
#endif /* defined(CRYPTO_BENCHMARK_FAST_HMAC) */
