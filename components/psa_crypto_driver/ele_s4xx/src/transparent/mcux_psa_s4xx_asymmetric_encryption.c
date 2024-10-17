/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_asymmetric_encryption.c
 *
 * This file contains the implementation of the entry points associated to the
 * asymmetric encryption capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */

#include "ele_crypto.h"

#include "mcux_psa_s4xx_init.h"
#include "mcux_psa_s4xx_asymmetric_encryption.h"
#include "mcux_psa_s4xx_common_key_management.h"

#include "psa/crypto.h"
#include "psa_crypto_rsa.h"
#include "psa/crypto_sizes.h"

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf printf
#define mbedtls_calloc calloc
#define mbedtls_free free
#endif

/* To be able to include the PSA style configuration */
#include "mbedtls/build_info.h"

psa_status_t psa_algo_to_generic_rsa_encrypt_algo(psa_algorithm_t alg,
                                                  generic_rsa_algo_t *encrypt_algo)
{
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    /* ELE encrypt schemes are compatible with PSA alg. So just assign for now. */
    *encrypt_algo = alg;

    switch (*encrypt_algo) {
        case RSA_PKCS1_V1_5_CRYPT:
        case RSA_PKCS1_OAEP_SHA1:
        case RSA_PKCS1_OAEP_SHA224:
        case RSA_PKCS1_OAEP_SHA256:
        case RSA_PKCS1_OAEP_SHA384:
        case RSA_PKCS1_OAEP_SHA512:
            status = PSA_SUCCESS;
            break;
        default:
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
    }

    return status;
}

static psa_status_t ele_s4xx_transparent_internal_rsa_encrypt(
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg, const uint8_t *input,
    size_t input_length, const uint8_t *label, size_t label_len,
    uint8_t *output, size_t output_size, size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    status_t ele_status = kStatus_Fail;
    generic_rsa_algo_t rsa_algo;
    ele_generic_rsa_t GenericRsaEncrypt = { 0 };
    struct rsa_keypair rsa_key = { 0 };
    size_t key_bits = psa_get_key_bits(attributes);
    uint32_t key_bytes = key_bits / 8;
    int lock = 0;

    // No check on input as input can be NULL
    if (!output) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if (output_size < key_bytes) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    /* Zero output length by default */
    *output_length = 0;

    if (key_bits != 2048 && key_bits != 3072 && key_bits != 4096) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((status = psa_algo_to_generic_rsa_encrypt_algo(alg, &rsa_algo)) != PSA_SUCCESS) {
        return status;
    }

    /* If label_len != 0, label can't be NULL */
    if ((PSA_ALG_IS_RSA_OAEP(alg)) && (label_len && !label)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ((PSA_ALG_IS_RSA_OAEP(alg))) {
        uint32_t hlen = PSA_HASH_LENGTH(PSA_ALG_RSA_OAEP_GET_HASH(alg));
        /* Chek for overflows */
        if (input_length + 2 * hlen + 2 < input_length ||
            output_size < input_length + 2 * hlen + 2) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }

        /* Check for  input message length . RFC defines mLen > k – 2hLen – 2 as error */
        if (input_length > (key_bytes - 2 * hlen - 2)) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    } else {
        /* Check for  input message length . For PKCS#1.5 padding is 11 bytes */
        if (input_length > key_bytes - 11) {
            return PSA_ERROR_INVALID_ARGUMENT;
        }
    }


    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    status = mcux_key_buf_to_raw_rsa(key_type,
                                     key_buffer,
                                     key_buffer_size,
                                     key_bytes,
                                     true,
                                     &rsa_key);
    if (status != PSA_SUCCESS) {
        return status;
    }

    GenericRsaEncrypt.algo = rsa_algo;
    GenericRsaEncrypt.mode = kEncryption;
    GenericRsaEncrypt.key_size = key_bits;
    /* Public Exponent */
    GenericRsaEncrypt.pub_exponent = (uint32_t) rsa_key.pub_exp;
    GenericRsaEncrypt.pub_exponent_size = rsa_key.pub_exp_len;
    /* Modulus */
    GenericRsaEncrypt.modulus = (uint32_t) rsa_key.modulus;
    GenericRsaEncrypt.modulus_size = rsa_key.modulus_len;
    /* Input plain text if provided, can be NULL*/
    if (input && input_length) {
        GenericRsaEncrypt.plaintext = (uint32_t) input;
        GenericRsaEncrypt.plaintext_size = input_length;
    }
    /* Ouput Cipher Text */
    GenericRsaEncrypt.ciphertext = (uint32_t) output;
    GenericRsaEncrypt.ciphertext_size = (uint16_t) output_size;
    /* Label */
    if (PSA_ALG_IS_RSA_OAEP(alg) && label_len) {
        GenericRsaEncrypt.label = (uint32_t) label;
        GenericRsaEncrypt.label_size = label_len;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        lock = 1;
        status = PSA_ERROR_COMMUNICATION_FAILURE;
        goto cleanup;
    }

    ele_status = ELE_GenericRsa(S3MU, &GenericRsaEncrypt);
    status = ele_to_psa_status(ele_status);

    /* ELE FW doesn't return the output size, we are assuming if things have gone right it will be equal to modulus size. */
    if (status == PSA_SUCCESS) {
        *output_length = key_bytes;
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

static psa_status_t ele_s4xx_transparent_internal_rsa_decrypt(
    const psa_key_attributes_t *attributes, const uint8_t *key_buffer,
    size_t key_buffer_size, psa_algorithm_t alg, const uint8_t *input,
    size_t input_length, const uint8_t *label, size_t label_len,
    uint8_t *output, size_t output_size, size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    psa_key_type_t key_type = psa_get_key_type(attributes);
    status_t ele_status = kStatus_Fail;
    generic_rsa_algo_t rsa_algo;
    ele_generic_rsa_t GenericRsaDecrypt = { 0 };
    struct rsa_keypair rsa_key = { 0 };
    size_t key_bits = psa_get_key_bits(attributes);
    uint32_t key_bytes = key_bits / 8;
    int lock = 0;

    /* If user sends a buffer with 0 size, return error */
    if (!output || !output_size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    if (!input || input_length != key_bytes) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Zero output length by default */
    *output_length = 0;

    if (key_bits != 2048 && key_bits != 3072 && key_bits != 4096) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if ((status = psa_algo_to_generic_rsa_encrypt_algo(alg, &rsa_algo)) != PSA_SUCCESS) {
        return status;
    }


    /* If label_len != 0, label can't be NULL */
    if ((PSA_ALG_IS_RSA_OAEP(alg)) && (label_len && !label)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    status = mcux_key_buf_to_raw_rsa(key_type,
                                     key_buffer,
                                     key_buffer_size,
                                     key_bytes,
                                     false,
                                     &rsa_key);
    if (status != PSA_SUCCESS) {
        return status;
    }

    GenericRsaDecrypt.algo = rsa_algo;
    GenericRsaDecrypt.mode = kDecryption;
    GenericRsaDecrypt.key_size = key_bits;
    /* Private Exponent */
    GenericRsaDecrypt.priv_exponent = (uint32_t) rsa_key.priv_exp;
    GenericRsaDecrypt.priv_exponent_size = rsa_key.priv_exp_len;
    /* Modulus */
    GenericRsaDecrypt.modulus = (uint32_t) rsa_key.modulus;
    GenericRsaDecrypt.modulus_size = rsa_key.modulus_len;
    /* Cipher Text */
    GenericRsaDecrypt.ciphertext = (uint32_t) input;
    GenericRsaDecrypt.ciphertext_size = input_length;
    /* Output plain text */
    GenericRsaDecrypt.plaintext = (uint32_t) output;
    GenericRsaDecrypt.plaintext_size = output_size;
    /* Label */
    if (PSA_ALG_IS_RSA_OAEP(alg) && label && label_len) {
        GenericRsaDecrypt.label = (uint32_t) label;
        GenericRsaDecrypt.label_size = label_len;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        lock = 1;
        status = PSA_ERROR_COMMUNICATION_FAILURE;
        goto cleanup;
    }

    ele_status = ELE_GenericRsa(S3MU, &GenericRsaDecrypt);
    status = ele_to_psa_status(ele_status);

    // Output length returned in out_plaintext_len
    if (status == PSA_SUCCESS) {
        *output_length = GenericRsaDecrypt.out_plaintext_len;
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

/** \defgroup psa_asym_encrypt PSA driver entry points for asymmetric cipher
 *
 *  Entry points for asymmetric cipher encryption and decryption as described
 *  by the PSA Cryptoprocessor Driver interface specification
 *
 *  @{
 */
psa_status_t ele_s4xx_transparent_asymmetric_encrypt(const psa_key_attributes_t *attributes,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *input,
                                                     size_t input_length,
                                                     const uint8_t *salt, size_t salt_length,
                                                     uint8_t *output, size_t output_size,
                                                     size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    size_t key_bits = psa_get_key_bits(attributes);
    psa_key_type_t type = psa_get_key_type(attributes);

    *output_length = 0;

#if defined(PSA_WANT_ALG_RSA_OAEP) || defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT)
    if ((alg == PSA_ALG_RSA_PKCS1V15_CRYPT) || PSA_ALG_IS_RSA_OAEP(alg)) {
        /* Check that the output buffer is large enough */
        if (output_size <
            PSA_ASYMMETRIC_ENCRYPT_OUTPUT_SIZE(type, key_bits, alg)) {
            return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        status = ele_s4xx_transparent_internal_rsa_encrypt(
            attributes, key_buffer, key_buffer_size, alg, input, input_length,
            salt, salt_length, output, output_size, output_length);
    } else
#endif /* PSA_WANT_ALG_RSA_OAEP || PSA_WANT_ALG_RSA_PKCS1V15_CRYPT */
#if defined(PSA_WANT_ALG_ECDSA_ANY)
    if (PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg) || alg == PSA_ALG_ECDSA_ANY) {
        status = PSA_ERROR_NOT_SUPPORTED;
    } else
#endif /* PSA_WANT_ALG_ECDSA_ANY */
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

    return status;
}

psa_status_t ele_s4xx_transparent_asymmetric_decrypt(const psa_key_attributes_t *attributes,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *input,
                                                     size_t input_length,
                                                     const uint8_t *salt, size_t salt_length,
                                                     uint8_t *output, size_t output_size,
                                                     size_t *output_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    *output_length = 0;

#if defined(PSA_WANT_ALG_RSA_OAEP) || defined(PSA_WANT_ALG_RSA_PKCS1V15_CRYPT)
    if ((alg == PSA_ALG_RSA_PKCS1V15_CRYPT) || PSA_ALG_IS_RSA_OAEP(alg)) {
        /* We don't perform a check on the output buffer size in the decrypt
         * case because the PSA_ASYMMETRIC_DECRYPT_OUTPUT_SIZE would return
         * only a sufficient value, while the necessary value could be smaller
         * hence too restrictive on the implementation.
         */
        status = ele_s4xx_transparent_internal_rsa_decrypt(
            attributes, key_buffer, key_buffer_size, alg, input, input_length,
            salt, salt_length, output, output_size, output_length);
    } else
#endif /* PSA_WANT_ALG_RSA_OAEP || PSA_WANT_ALG_RSA_PKCS1V15_CRYPT */
#if defined(PSA_WANT_ALG_ECDSA_ANY)
    if (PSA_ALG_IS_ASYMMETRIC_ENCRYPTION(alg) || alg == PSA_ALG_ECDSA_ANY) {
        status = PSA_ERROR_NOT_SUPPORTED;
    } else
#endif /* PSA_WANT_ALG_ECDSA_ANY */
    {
        status = PSA_ERROR_INVALID_ARGUMENT;
    }

    return status;
}
/** @} */ // end of psa_asym_encrypt
