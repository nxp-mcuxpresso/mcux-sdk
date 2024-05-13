/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "crypto_benchmark.h"
#include "crypto_benchmark_aes.h"
#include "ele_crypto.h"
#include "ele.h"

/*******************************************************************************
 * Transparent key cipher compute definitions
 ******************************************************************************/
status_t wrapper_aes_ecb_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *key, size_t key_length)
{
    ele_generic_cipher_t conf;
    status_t status = kStatus_Fail;

    conf.algo     = kAES_ECB;
    conf.data     = (uint32_t)input;
    conf.size     = (uint32_t)input_length;
    conf.iv       = (uint32_t)0u;
    conf.iv_size  = (uint32_t)0u;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.mode     = kEncrypt;
    conf.output   = (uint32_t)cipher;

    status = ELE_GenericCipher(S3MU, &conf);

    return status;
}

status_t wrapper_aes_cbc_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_cipher_t conf;
    status_t status = kStatus_Fail;

    conf.algo     = kAES_CBC;
    conf.data     = (uint32_t)input;
    conf.size     = (uint32_t)input_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.mode     = kEncrypt;
    conf.output   = (uint32_t)cipher;

    status = ELE_GenericCipher(S3MU, &conf);

    return status;
}

status_t wrapper_aes_cfb_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_cipher_t conf;
    status_t status = kStatus_Fail;

    conf.algo     = kAES_CFB;
    conf.data     = (uint32_t)input;
    conf.size     = (uint32_t)input_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.mode     = kEncrypt;
    conf.output   = (uint32_t)cipher;

    status = ELE_GenericCipher(S3MU, &conf);

    return status;
}

status_t wrapper_aes_ofb_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_cipher_t conf;
    status_t status = kStatus_Fail;

    conf.algo     = kAES_OFB;
    conf.data     = (uint32_t)input;
    conf.size     = (uint32_t)input_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.mode     = kEncrypt;
    conf.output   = (uint32_t)cipher;

    status = ELE_GenericCipher(S3MU, &conf);

    return status;
}

status_t wrapper_aes_ctr_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_cipher_t conf;
    status_t status = kStatus_Fail;

    conf.algo     = kAES_CTR;
    conf.data     = (uint32_t)input;
    conf.size     = (uint32_t)input_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.mode     = kEncrypt;
    conf.output   = (uint32_t)cipher;

    status = ELE_GenericCipher(S3MU, &conf);

    return status;
}

status_t wrapper_aes_ccm_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *aad,
                                 size_t aad_length,
                                 uint8_t *tag,
                                 size_t tag_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_aead_t conf;
    status_t status = kStatus_Fail;

    conf.data     = (uint32_t)input;
    conf.output   = (uint32_t)cipher;
    conf.size     = (uint32_t)input_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.aad      = (uint32_t)aad;
    conf.aad_size = (uint32_t)aad_length;
    conf.tag      = (uint32_t)tag;
    conf.tag_size = (uint32_t)tag_length;
    conf.mode     = kEncrypt;
    conf.algo     = kAES_CCM;

    status = ELE_GenericAead(S3MU, &conf);

    return status;
}

status_t wrapper_aes_gcm_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *aad,
                                 size_t aad_length,
                                 uint8_t *tag,
                                 size_t tag_length,
                                 const uint8_t *key,
                                 size_t key_length)
{
    ele_generic_aead_t conf;
    status_t status = kStatus_Fail;

    conf.data     = (uint32_t)input;
    conf.output   = (uint32_t)cipher;
    conf.size     = (uint32_t)input_length;
    conf.key      = (uint32_t)key;
    conf.key_size = (uint32_t)key_length;
    conf.iv       = (uint32_t)iv;
    conf.iv_size  = (uint32_t)iv_length;
    conf.aad      = (uint32_t)aad;
    conf.aad_size = (uint32_t)aad_length;
    conf.tag      = (uint32_t)tag;
    conf.tag_size = (uint32_t)tag_length;
    conf.mode     = kEncrypt;
    conf.algo     = kAES_GCM;

    status = ELE_GenericAead(S3MU, &conf);

    return status;
}

/*******************************************************************************
 * Opaque key cipher compute definitions
 ******************************************************************************/
status_t wrapper_aes_ecb_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *cipher, uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;

    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = 0u;
    aes_hsm_param.iv_size     = 0u;
    aes_hsm_param.alg         = kPermitted_ECB;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Cipher(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param);
}

status_t wrapper_aes_cbc_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_CBC;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Cipher(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param);
}

status_t wrapper_aes_cfb_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_CFB;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Cipher(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param);
}

status_t wrapper_aes_ofb_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_OFB;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Cipher(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param);
}

status_t wrapper_aes_ctr_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_CTR;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Cipher(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param);
}

status_t wrapper_aes_ccm_opaque_compute(const uint8_t *input,
                                        size_t input_length,
                                        uint8_t *cipher,
                                        const uint8_t *iv,
                                        size_t iv_length,
                                        const uint8_t *aad,
                                        size_t aad_length,
                                        uint8_t *tag,
                                        size_t tag_length,
                                        uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_CCM;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Aead(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param, (uint32_t)aad, aad_length, kHSM_IV_User);
}

status_t wrapper_aes_gcm_opaque_compute(const uint8_t *input,
                                        size_t input_length,
                                        uint8_t *cipher,
                                        const uint8_t *iv,
                                        size_t iv_length,
                                        const uint8_t *aad,
                                        size_t aad_length,
                                        uint8_t *tag,
                                        size_t tag_length,
                                        uint32_t key_id)
{
    ele_hsm_cipher_t aes_hsm_param;
    aes_hsm_param.keyID       = key_id;
    aes_hsm_param.input       = (uint32_t)input;
    aes_hsm_param.input_size  = input_length;
    aes_hsm_param.output      = (uint32_t)cipher;
    aes_hsm_param.output_size = NULL;
    aes_hsm_param.iv          = (uint32_t)iv;
    aes_hsm_param.iv_size     = iv_length;
    aes_hsm_param.alg         = kPermitted_GCM;
    aes_hsm_param.mode        = kHSM_Encrypt;

    return ELE_Aead(S3MU, g_ele_ctx.cipher_handle, &aes_hsm_param, (uint32_t)aad, aad_length, kHSM_IV_User);
}

/*******************************************************************************
 * Opaque key setup definitions
 ******************************************************************************/
/* All cipher modes have the same setup */
static status_t aes_common_opaque_setup(void)
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

    /* Open a cipher service */
    status = ELE_OpenCipherService(S3MU, g_ele_ctx.keystore_handle, &g_ele_ctx.cipher_handle);
    if (status != kStatus_Success)
    {
        ELE_CloseKeyService(S3MU, g_ele_ctx.key_management_handle);
        ELE_CloseKeystore(S3MU, g_ele_ctx.keystore_handle);
        return status;
    }

    return status;
}

status_t wrapper_aes_ecb_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_cbc_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_cfb_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_ofb_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_ctr_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_ccm_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

status_t wrapper_aes_gcm_opaque_setup(void)
{
    return aes_common_opaque_setup();
}

/*******************************************************************************
 * Opaque key cleanup definitions
 ******************************************************************************/
/* All cipher modes have the same cleanup */
static status_t aes_common_opaque_cleanup(void)
{
    status_t status = kStatus_Fail;

    status = ELE_CloseCipherService(S3MU, g_ele_ctx.cipher_handle);
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

status_t wrapper_aes_ecb_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_cbc_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_cfb_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_ofb_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_ctr_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_ccm_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

status_t wrapper_aes_gcm_opaque_cleanup(void)
{
    return aes_common_opaque_cleanup();
}

/*******************************************************************************
 * Opaque key generation definitions
 ******************************************************************************/
/* By using permitted_alg, keygen can be mostly common */
static status_t aes_common_opaque_key_generate(uint16_t key_size,
                                               uint32_t *aes_key_id,
                                               key_permitted_alg_t permitted_alg)
{
    uint16_t key_size_out     = 0u;
    ele_gen_key_t aes_key_cfg = {0u};

    /* Generate a key */
    aes_key_cfg.key_type      = kKeyType_AES;
    aes_key_cfg.key_lifetime  = kKey_Persistent;
    aes_key_cfg.key_usage     = kKeyUsage_Encrypt | kKeyUsage_Decrypt;
    aes_key_cfg.key_size      = key_size;
    aes_key_cfg.permitted_alg = permitted_alg;
    aes_key_cfg.pub_key_addr  = 0u;
    aes_key_cfg.pub_key_size  = 0u;
    aes_key_cfg.key_group     = 1u;

    return ELE_GenerateKey(S3MU, g_ele_ctx.key_management_handle, &aes_key_cfg, aes_key_id, &key_size_out, false,
                           false);
}

status_t wrapper_aes_ecb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_Cipher);
}

status_t wrapper_aes_cbc_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_Cipher);
}

status_t wrapper_aes_cfb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_Cipher);
}

status_t wrapper_aes_ofb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_Cipher);
}

status_t wrapper_aes_ctr_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_Cipher);
}

status_t wrapper_aes_ccm_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_AEAD);
}

status_t wrapper_aes_gcm_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id)
{
    return aes_common_opaque_key_generate(key_size, aes_key_id, kPermitted_All_AEAD);
}

/*******************************************************************************
 * Opaque key deletion definitions
 ******************************************************************************/
/* All cipher modes have the same key delete */
static status_t aes_common_opaque_key_delete(uint32_t aes_key_id)
{
    return ELE_DeleteKey(S3MU, g_ele_ctx.key_management_handle, aes_key_id, false, false);
}

status_t wrapper_aes_ecb_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_cbc_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_cfb_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_ofb_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_ctr_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_ccm_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}

status_t wrapper_aes_gcm_opaque_key_delete(uint32_t aes_key_id)
{
    return aes_common_opaque_key_delete(aes_key_id);
}
