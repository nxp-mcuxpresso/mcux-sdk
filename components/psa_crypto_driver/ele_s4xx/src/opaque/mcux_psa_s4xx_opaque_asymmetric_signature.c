/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_opaque_asymmetric_signature.c
 *
 * This file contains the implementation of the entry points associated to the
 * asymmetric signature capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */

#include "mcux_psa_s4xx_opaque_asymmetric_signature.h"
#include "mcux_psa_s4xx_common_key_management.h"
#include "ele_crypto.h"

#include "mcux_psa_s4xx_common_init.h"

#include "psa/crypto.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf printf
#define mbedtls_calloc calloc
#define mbedtls_free free
#endif

/* It is essential to have NVM Manager defined with opaque driver. Return PSA_ERROR_NOT_SUPPORTED
 * if the NVM manager is not present. Since psa_crypto_wrapper will be auto-generated, we can't add
 * the check there. hence implementing it in opaque drivers for ELE.
 */
#if !defined(PSA_ELE_S4XX_SD_NVM_MANAGER)

psa_status_t ele_s4xx_opaque_sign_message(const psa_key_attributes_t *attributes,
                                          const uint8_t *key, size_t key_length,
                                          psa_algorithm_t alg, const uint8_t *input,
                                          size_t input_length, uint8_t *signature,
                                          size_t signature_size,
                                          size_t *signature_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_verify_message(const psa_key_attributes_t *attributes,
                                            const uint8_t *key, size_t key_length,
                                            psa_algorithm_t alg, const uint8_t *input,
                                            size_t input_length, const uint8_t *signature,
                                            size_t signature_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_sign_hash(const psa_key_attributes_t *attributes,
                                       const uint8_t *key, size_t key_length,
                                       psa_algorithm_t alg, const uint8_t *input,
                                       size_t input_length, uint8_t *signature,
                                       size_t signature_size, size_t *signature_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t ele_s4xx_opaque_verify_hash(const psa_key_attributes_t *attributes,
                                         const uint8_t *key, size_t key_length,
                                         psa_algorithm_t alg, const uint8_t *hash,
                                         size_t hash_length, const uint8_t *signature,
                                         size_t signature_length)
{
    return PSA_ERROR_NOT_SUPPORTED;
}

#else

/* FixMe: Currently, some parts of the low-level driver
 *        are not built at all based on the mbed TLS configuration,
 *        hence they can't be called from the interface code.
 *        Eventually, the low level driver should be made
 *        independent of the mbed TLS configuration and the
 *        interface layer should be the only part that should
 *        be configured through defines
 */
#include "mbedtls/build_info.h"

extern ele_s4xx_ctx_t g_ele_ctx;

/** \defgroup psa_asym_sign PSA driver entry points for asymmetric sign/verify
 *
 *  Entry points for asymmetric message signing and signature verification as
 *  described by the PSA Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t psa_algo_to_ele_sig_algo(psa_algorithm_t alg, key_sig_scheme_t *sig_scheme)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    /* ELE sig schemes are compatible with PSA alg. So just assign for now. */
    *sig_scheme = alg;

    switch (*sig_scheme) {
        case kSig_RSA_PKCS1_V1_5_SHA1:
        case kSig_RSA_PKCS1_V1_5_SHA224:          
        case kSig_RSA_PKCS1_V1_5_SHA256:
        case kSig_RSA_PKCS1_V1_5_SHA384:
        case kSig_RSA_PKCS1_V1_5_SHA512:
        case kSig_RSA_PKCS1_PSS_MGF1_SHA1:
        case kSig_RSA_PKCS1_PSS_MGF1_SHA224:
        case kSig_RSA_PKCS1_PSS_MGF1_SHA256:
        case kSig_RSA_PKCS1_PSS_MGF1_SHA384:
        case kSig_RSA_PKCS1_PSS_MGF1_SHA512:
        case kSig_ECDSA_SHA224:
        case kSig_ECDSA_SHA256:
        case kSig_ECDSA_SHA384:
        case kSig_ECDSA_SHA512:
            status = PSA_SUCCESS;
            break;
        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

static psa_status_t ele_s4xx_opaque_sign_common(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_length, psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature, size_t signature_size,
    size_t *signature_length, bool is_msg)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    uint32_t key_id = 0u;
    uint32_t signHandleID;
    key_sig_scheme_t sig_scheme;
    uint32_t sig_size = 0u;
    ele_sign_t signGenParam = { 0u };
    size_t hlen = PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg));

    /* Add check on signature and signature_size */
    if ((status = psa_algo_to_ele_sig_algo(alg, &sig_scheme)) != PSA_SUCCESS) {
        return status;
    }

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_length, &key_id)) != PSA_SUCCESS) {
        return status;
    }
    
    /* Check for input buffer size in case it is hash it should match the algorithm size */
    if (!is_msg && input_length != hlen) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    
    if (!signature) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* TBD - should we add a check that this key id corresponds to a key pair ?? */

    signGenParam.key_id     = key_id;
    signGenParam.msg        = input;
    signGenParam.msg_size   = input_length;
    signGenParam.signature  = signature;
    signGenParam.sig_size   = signature_size;
    signGenParam.scheme     = sig_scheme;
    signGenParam.input_flag = is_msg; // Actual message as input

    /* PSA_ALG_RSA_PSS salt length should be equal to hash length */
    if(PSA_ALG_IS_RSA_PSS_STANDARD_SALT(alg)) {
        signGenParam.salt_size = hlen;
    } else {
        signGenParam.salt_size = 0u;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_OpenSignService(S3MU, g_ele_ctx.key_store_handle, &signHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Sign(S3MU, signHandleID, &signGenParam, &sig_size);
    status = ele_to_psa_status(ele_status);
    /* Avoid over-writing status */
    if (status != PSA_SUCCESS) {
        ELE_CloseSignService(S3MU, signHandleID);
        goto out;
    }
        
    ele_status = ELE_CloseSignService(S3MU, signHandleID);
    status = ele_to_psa_status(ele_status);

out:
    *signature_length = sig_size;
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

static psa_status_t ele_s4xx_opaque_verify_common(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_length, psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature, size_t signature_size,
    bool is_msg)
{
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    uint32_t key_id = 0u;
    uint32_t verifyHandleID;
    key_sig_scheme_t sig_scheme;
    ele_verify_t verifyParam = { 0u };
    bool result = false;
    size_t hlen = PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg));

    if ((status = psa_algo_to_ele_sig_algo(alg, &sig_scheme)) != PSA_SUCCESS) {
        return status;
    }

    if ((status =
             ele_get_key_id_from_buf(attributes, key_buffer, key_length, &key_id)) != PSA_SUCCESS) {
        return status;
    }

    /* TBD - should we add a check that this key id corresponds to a key pair ?? as we can retreive public key only if the key id corresponds to a key pair */

    /* Retreive the public key corresponding to the key ID passed */
    size_t buffer_size = PSA_EXPORT_PUBLIC_KEY_OUTPUT_SIZE(key_type, key_bits);
    uint8_t *tmp = malloc(buffer_size);
    uint16_t out_size;
    if (!tmp) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        free(tmp);
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GeneratePubKey(S3MU, g_ele_ctx.key_store_handle, key_id,
                                    (uint32_t *) tmp, buffer_size, &out_size);
    status = ele_to_psa_status(ele_status);

    /* Free mutex and return back if error in retreiving public key */
    if (status != PSA_SUCCESS) {
        goto out;
    }

    verifyParam.msg               = input;
    verifyParam.msg_size          = input_length;
    verifyParam.signature         = (uint8_t *) signature;
    verifyParam.sig_size          = signature_size;
    verifyParam.scheme            = sig_scheme;
    verifyParam.input_flag        = is_msg; // Actual message as input

    /* Directly using PSA key type as ELE supports the PSA defines */
    verifyParam.keypair_type      = PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(key_type);
    verifyParam.pub_key           = tmp;
    verifyParam.key_size          = out_size;
    verifyParam.key_security_size = key_bits;
    verifyParam.internal          = false;                      /* TBD - Check with Vit, Benjamin what this flag is. Can't find it in document */

    /* PSA_ALG_RSA_PSS salt length should be equal to hash length */
    if(PSA_ALG_IS_RSA_PSS_STANDARD_SALT(alg)) {
        verifyParam.salt_size = hlen;
    } else {
        verifyParam.salt_size = 0u;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        free(tmp);
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_OpenVerifyService(S3MU, g_ele_ctx.session_handle, &verifyHandleID);
    status = ele_to_psa_status(ele_status);
    if (status != PSA_SUCCESS) {
        goto out;
    }

    ele_status = ELE_Verify(S3MU, verifyHandleID, &verifyParam, &result);
    status = ele_to_psa_status(ele_status);
    /* If status returned is success but result is failure, signature verification has failed */
    if (status == PSA_SUCCESS && result == false) {
        status = PSA_ERROR_INVALID_SIGNATURE;
    }

    ele_status = ELE_CloseVerifyService(S3MU, verifyHandleID);
    status = ele_to_psa_status(ele_status);

out:
    free(tmp);
    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    return status;
}

psa_status_t ele_s4xx_opaque_sign_hash(const psa_key_attributes_t *attributes,
                                       const uint8_t *key, size_t key_length,
                                       psa_algorithm_t alg, const uint8_t *input,
                                       size_t input_length, uint8_t *signature,
                                       size_t signature_size, size_t *signature_length)
{
    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (PSA_ALG_IS_ECDSA(alg) || (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_opaque_sign_common(
            attributes, key, key_length, alg, input, input_length, signature,
            signature_size, signature_length, false);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

}

psa_status_t ele_s4xx_opaque_verify_hash(const psa_key_attributes_t *attributes,
                                         const uint8_t *key, size_t key_length,
                                         psa_algorithm_t alg, const uint8_t *hash,
                                         size_t hash_length, const uint8_t *signature,
                                         size_t signature_length)
{
    if (alg != PSA_ALG_RSA_PKCS1V15_SIGN_RAW &&
        hash_length != PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg))) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (PSA_ALG_IS_ECDSA(alg) || (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_opaque_verify_common(attributes, key, key_length, alg,
                                             hash, hash_length, signature,
                                             signature_length, false);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_ERROR_NOT_SUPPORTED;

}

psa_status_t ele_s4xx_opaque_sign_message(const psa_key_attributes_t *attributes,
                                          const uint8_t *key, size_t key_length,
                                          psa_algorithm_t alg, const uint8_t *input,
                                          size_t input_length, uint8_t *signature,
                                          size_t signature_size, size_t *signature_length)
{
    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (PSA_ALG_IS_ECDSA(alg) || (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_opaque_sign_common(
            attributes, key, key_length, alg, input, input_length, signature,
            signature_size, signature_length, true);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

}

psa_status_t ele_s4xx_opaque_verify_message(const psa_key_attributes_t *attributes,
                                            const uint8_t *key, size_t key_length,
                                            psa_algorithm_t alg, const uint8_t *input,
                                            size_t input_length, const uint8_t *signature,
                                            size_t signature_length)
{

    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (PSA_ALG_IS_ECDSA(alg) || (PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_opaque_verify_common(attributes, key, key_length, alg,
                                             input, input_length, signature,
                                             signature_length, true);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_ERROR_NOT_SUPPORTED;
}

#endif
/** @} */ // end of psa_asym_sign
