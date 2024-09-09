/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s40x_asymmetric_signature.c
 *
 * This file contains the implementation of the entry points associated to the
 * asymmetric signature capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */
#include "ele_crypto.h"

#include "mcux_psa_s4xx_asymmetric_signature.h"
#include "mcux_psa_s4xx_common_key_management.h"
#include "mcux_psa_s4xx_init.h"

#include "psa/crypto.h"
#include "psa_crypto_rsa.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>

#define mbedtls_printf printf
#define mbedtls_calloc calloc
#define mbedtls_free free
#endif

/* FixMe: Currently, some parts of the low-level driver are
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


psa_status_t psa_algo_to_generic_rsa_sign_algo(psa_algorithm_t alg, generic_rsa_algo_t *sig_scheme)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    /* ELE sig schemes are compatible with PSA alg. So just assign for now. */
    *sig_scheme = alg;

    switch (*sig_scheme) {
        case RSA_PKCS1_V1_5_SHA224_SIGN:
        case RSA_PKCS1_V1_5_SHA256_SIGN:
        case RSA_PKCS1_V1_5_SHA384_SIGN:
        case RSA_PKCS1_V1_5_SHA512_SIGN:
        case RSA_PKCS1_PSS_MGF1_SHA224:
        case RSA_PKCS1_PSS_MGF1_SHA256:
        case RSA_PKCS1_PSS_MGF1_SHA384:
        case RSA_PKCS1_PSS_MGF1_SHA512:
            status = PSA_SUCCESS;
            break;
        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

static psa_status_t ele_s4xx_transparent_rsa_sign_common(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_length, psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature, size_t signature_size,
    size_t *signature_length, bool is_msg)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    status_t ele_status = kStatus_Fail;
    ele_generic_rsa_t GenericRsaSign;
    generic_rsa_algo_t sig_scheme;
    struct rsa_keypair rsa_key;
    size_t key_bits = psa_get_key_bits(attributes);
    uint32_t key_bytes = key_bits / 8;
    size_t slen = -1;
    size_t hlen = PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg));
    int lock = 0;

    /* First check if the key size is supported by hardware, then any further checks */
    if (key_bits != 2048 && key_bits != 3072 && key_bits != 4096) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Not checking for input as RSA - PSS can take 0 as input.
     * For rest of teh algorithms, let's leave it up to ELE FW to
     * take care of this error.
     */
#if 0
    if (!input || !input_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
#endif

    if (signature_size < key_bytes) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (!signature) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Check if algorithm is supporte dby ELE and return the ele algorithm */
    if ((status = psa_algo_to_generic_rsa_sign_algo(alg, &sig_scheme)) != PSA_SUCCESS) {
        return status;
    }

    /* Check for input buffer size in case it is hash it should match the algorithm size */
    if (!is_msg && input_length != hlen) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* TBD - uncomment if we find this is needed. For both sign and verify if we pass -1
     * to ELE, it should take care of this.The calculation below seems unnecessary for now.
     * Uncomment if we find a usecase for it.
     */
#if 0
    size_t min_slen = 0;
    /* Check for salt length and output buffer size*/
    if (PSA_ALG_IS_RSA_PSS(alg)) {
        /* For PSA API, explicit salt length is not passed by caller */
        /* Calculate the largest possible salt length, up to the hash size.
         * Normally this is the hash length, which is the maximum salt length
         * according to FIPS 185-4 §5.5 (e) and common practice. If there is not
         * enough room, use the maximum salt length that fits. The constraint is
         * that the hash length plus the salt length plus 2 bytes must be at most
         * the key length. This complies with FIPS 186-4 §5.5 (e) and RFC 8017
         * (PKCS#1 v2.2) §9.1.1 step 3. */
        min_slen = hlen - 2;
        if (signature_size < hlen + min_slen + 2) {
            return PSA_ERROR_INVALID_ARGUMENT;
        } else if (signature_size >= hlen + hlen + 2) {
            slen = hlen;
        } else {
            slen = signature_size - hlen - 2;
        }
    }
#endif

    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    memset(&rsa_key, 0, sizeof(rsa_key));

    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    status = mcux_key_buf_to_raw_rsa(key_type, key_buffer, key_length, key_bytes, false, &rsa_key);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Clear the output buffer. Intentially clearing only key_bytes data */
    memset(signature, 0, key_bytes);

    /* Clear the ele structure */
    memset(&GenericRsaSign, 0, sizeof(ele_generic_rsa_t));

    /* Set ELE structure */
    GenericRsaSign.mode     = kSignGen;
    GenericRsaSign.key_size = key_bits;
    /* Private exponent */
    GenericRsaSign.priv_exponent      = (uint32_t) rsa_key.priv_exp;
    GenericRsaSign.priv_exponent_size = rsa_key.priv_exp_len;
    /* Modulus */
    GenericRsaSign.modulus      = (uint32_t) rsa_key.modulus;
    GenericRsaSign.modulus_size = rsa_key.modulus_len;
    /* Digest / Msg */
    GenericRsaSign.digest      = (uint32_t) input;
    GenericRsaSign.digest_size = input_length;
    /* Signature destination */
    GenericRsaSign.signature      = (uint32_t) signature;
    GenericRsaSign.signature_size = signature_size;

    /* Will be considered only in case of PSS sign else ignored */
    GenericRsaSign.salt_size = slen;   /* ELE FWspec says if set to -1, FW sets the salt length as hash length */

    GenericRsaSign.algo  = sig_scheme;

    if (is_msg) {
        GenericRsaSign.flags = kFlagActualMsg; // Actual message as input
    } else {
        GenericRsaSign.flags = kFlagDigest;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        lock = 1;
        status = PSA_ERROR_COMMUNICATION_FAILURE;
        goto cleanup;
    }

    ele_status = ELE_GenericRsa(S3MU, &GenericRsaSign);
    status = ele_to_psa_status(ele_status);

    // Nothing returned from ELE, so assign signature length as key bytes
    *signature_length = key_bytes;

cleanup:
    mcux_free_raw_rsa(rsa_key);

    if (lock) {
        if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
            return PSA_ERROR_BAD_STATE;
        }
    }

    return status;
}

static psa_status_t ele_s4xx_transparent_rsa_verify_common(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_length, psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature, size_t signature_size,
    bool is_msg)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    status_t ele_status = kStatus_Fail;
    ele_generic_rsa_t GenericRsaVerif;
    generic_rsa_algo_t sig_scheme;
    size_t key_bits = psa_get_key_bits(attributes);
    uint32_t key_bytes = key_bits / 8;
    int lock = 0;
    struct rsa_keypair rsa_key;
    size_t hlen = PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg));

    /* If key size is not supported by hardware, return from here */
    if (key_bits != 2048 && key_bits != 3072 && key_bits != 4096) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    /* Signature is input, it can't be NULL */
    if (!signature) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Signature has to be equal to key modulus size */
    if (signature_size != key_bytes) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Not checking for input as RSA - PSS can take 0 as input.
     * For rest of teh algorithms, let's leave it up to ELE FW to
     * take care of this error.
     */
#if 0
    if (!input || !input_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
#endif

    /* Check for input buffer size in case it is hash it should match the algorithm size */
    if (!is_msg && input_length != hlen) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ((status = psa_algo_to_generic_rsa_sign_algo(alg, &sig_scheme)) != PSA_SUCCESS) {
        return status;
    }

    memset(&rsa_key, 0, sizeof(rsa_key));

    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    status = mcux_key_buf_to_raw_rsa(key_type, key_buffer, key_length, key_bytes, true, &rsa_key);
    if (status != PSA_SUCCESS) {
        return status;
    }

    memset(&GenericRsaVerif, 0, sizeof(ele_generic_rsa_t));

    /* Set ELE structure */
    GenericRsaVerif.mode     = kVerification;
    GenericRsaVerif.key_size = key_bits;
    /* Public exponent */
    GenericRsaVerif.pub_exponent      = (uint32_t) rsa_key.pub_exp;
    GenericRsaVerif.pub_exponent_size = rsa_key.pub_exp_len;
    /* Modulus */
    GenericRsaVerif.modulus      = (uint32_t) rsa_key.modulus;
    GenericRsaVerif.modulus_size = rsa_key.modulus_len;
    /* Digest/ Msg */
    GenericRsaVerif.digest      = (uint32_t) input;
    GenericRsaVerif.digest_size = input_length;

    /* Signature */
    GenericRsaVerif.signature      = (uint32_t) signature;
    GenericRsaVerif.signature_size = signature_size;

    GenericRsaVerif.salt_size = -1;   /* ELE FWspec says if set to -1, FW sets the salt length as hash length */

    GenericRsaVerif.algo  = sig_scheme;

    if (is_msg) {
        GenericRsaVerif.flags = kFlagActualMsg; // Actual message as input
    } else {
        GenericRsaVerif.flags = kFlagDigest;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        lock = 1;
        status = PSA_ERROR_COMMUNICATION_FAILURE;
        goto cleanup;
    }

    ele_status = ELE_GenericRsa(S3MU, &GenericRsaVerif);
    status = ele_to_psa_status(ele_status);
    /* If status returned is success but result is failure, signature verification has failed */
    if (status == PSA_SUCCESS && GenericRsaVerif.verify_status == kVerifyFailure) {
        status = PSA_ERROR_INVALID_SIGNATURE;
    }

cleanup:
    mcux_free_raw_rsa(rsa_key);

    if (lock) {
        if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
            return PSA_ERROR_BAD_STATE;
        }
    }

    return status;
}


psa_status_t ele_s4xx_transparent_sign_hash(const psa_key_attributes_t *attributes,
                                            const uint8_t *key, size_t key_length,
                                            psa_algorithm_t alg, const uint8_t *input,
                                            size_t input_length, uint8_t *signature,
                                            size_t signature_size, size_t *signature_length)
{
    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_transparent_rsa_sign_common(
            attributes, key, key_length, alg, input, input_length, signature,
            signature_size, signature_length, false);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

}

psa_status_t ele_s4xx_transparent_verify_hash(const psa_key_attributes_t *attributes,
                                              const uint8_t *key, size_t key_length,
                                              psa_algorithm_t alg, const uint8_t *hash,
                                              size_t hash_length, const uint8_t *signature,
                                              size_t signature_length)
{

#if 0
    if (alg != PSA_ALG_RSA_PKCS1V15_SIGN_RAW &&
        hash_length != PSA_HASH_LENGTH(PSA_ALG_SIGN_GET_HASH(alg))) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
#endif

    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_transparent_rsa_verify_common(attributes, key, key_length, alg,
                                                      hash, hash_length, signature,
                                                      signature_length, false);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_ERROR_NOT_SUPPORTED;

}

psa_status_t ele_s4xx_transparent_sign_message(const psa_key_attributes_t *attributes,
                                               const uint8_t *key, size_t key_length,
                                               psa_algorithm_t alg, const uint8_t *input,
                                               size_t input_length, uint8_t *signature,
                                               size_t signature_size, size_t *signature_length)
{
    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_transparent_rsa_sign_common(
            attributes, key, key_length, alg, input, input_length, signature,
            signature_size, signature_length, true);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

}

psa_status_t ele_s4xx_transparent_verify_message(const psa_key_attributes_t *attributes,
                                                 const uint8_t *key, size_t key_length,
                                                 psa_algorithm_t alg, const uint8_t *input,
                                                 size_t input_length, const uint8_t *signature,
                                                 size_t signature_length)
{

    if (!PSA_KEY_TYPE_IS_ASYMMETRIC(psa_get_key_type(attributes))) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((PSA_ALG_IS_RSA_PKCS1V15_SIGN(alg) || PSA_ALG_IS_RSA_PSS(alg))) {
        return ele_s4xx_transparent_rsa_verify_common(attributes, key, key_length, alg,
                                                      input, input_length, signature,
                                                      signature_length, true);
    } else {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    return PSA_ERROR_NOT_SUPPORTED;
}
/** @} */ // end of psa_asym_sign
