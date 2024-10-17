/*
 * Copyright 2022-2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file mcux_psa_s4xx_key_generation.c
 *
 * This file contains the implementation of the entry points associated to the
 * key generation (i.e. random generation and extraction of public keys) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

#include "mcux_psa_s4xx_key_generation.h"
#include "mcux_psa_s4xx_common_key_management.h"
#include "mcux_psa_s4xx_init.h"

#include "psa/crypto.h"
#include "mbedtls/asn1write.h"

#if 0
static psa_status_t psa_rsa_read_exponent(const uint8_t *domain_parameters,
                                          size_t domain_parameters_size,
                                          int *exponent)
{
    size_t i;
    uint32_t acc = 0;

    if (domain_parameters_size == 0) {
        *exponent = 65537;
        return PSA_SUCCESS;
    }

    /* Mbed TLS encodes the public exponent as an int. For simplicity, only
     * support values that fit in a 32-bit integer, which is larger than
     * int on just about every platform anyway. */
    if (domain_parameters_size > sizeof(acc)) {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    for (i = 0; i < domain_parameters_size; i++) {
        acc = (acc << 8u) | domain_parameters[i];
    }
    if (acc > INT_MAX) {
        return PSA_ERROR_NOT_SUPPORTED;
    }
    *exponent = acc;
    return PSA_SUCCESS;
}
#endif

psa_status_t ele_internal_gen_rsa_keypair(const psa_key_attributes_t *attributes,
                                          uint8_t *key_buffer, size_t key_buffer_size,
                                          size_t *key_buffer_length)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    status_t ele_status = kStatus_Fail;
    ele_generic_rsa_t GenericRsaKeygen = { 0 };
    psa_key_type_t key_type = psa_get_key_type(attributes);
    size_t key_bits = psa_get_key_bits(attributes);
    size_t key_bytes = key_bits / 8u;
    int exponent = 65537;

    struct rsa_keypair rsa_key;

    if (key_bits != 2048u && key_bits != 3072u && key_bits != 4096u) {
        return PSA_ERROR_NOT_SUPPORTED;
    }

    status = mcux_alloc_raw_rsa(&rsa_key, key_bytes);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* In mbedTLS 3.6 they have removed the domain parameter concept so hardcode exponent to 65537 */
#if 0
    status = psa_rsa_read_exponent(attributes->MBEDTLS_PRIVATE(domain_parameters),
                                   attributes->MBEDTLS_PRIVATE(domain_parameters_size),
                                   &exponent);
    if (status != PSA_SUCCESS) {
        return status;
    }

#endif
   memcpy(rsa_key.pub_exp, &exponent, sizeof(int));
   int exp_be = __REV(exponent);

    GenericRsaKeygen.modulus            = (uint32_t) rsa_key.modulus;
    GenericRsaKeygen.priv_exponent      = (uint32_t) rsa_key.priv_exp;
    GenericRsaKeygen.priv_exponent_size = rsa_key.priv_exp_len;
    GenericRsaKeygen.modulus_size       = rsa_key.modulus_len;
    GenericRsaKeygen.pub_exponent       = (uint32_t) &exp_be;
    GenericRsaKeygen.pub_exponent_size  = rsa_key.pub_exp_len;
    GenericRsaKeygen.key_size           = key_bits;

    if (mcux_mutex_lock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_COMMUNICATION_FAILURE;
    }

    ele_status = ELE_GenericRsaKeygen(S3MU, &GenericRsaKeygen);
    status = ele_to_psa_status(ele_status);

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex)) {
        return PSA_ERROR_BAD_STATE;
    }

    if (status == PSA_SUCCESS) {
        /* The Key needs to be now converted to ASN1 structure */
        status = mcux_raw_rsa_to_key_buf(key_type, rsa_key,
                                         key_buffer, key_buffer_size,
                                         key_buffer_length);
    }

    return status;
}


psa_status_t ele_s4xx_transparent_generate_key(const psa_key_attributes_t *attributes,
                                               uint8_t *key_buffer, size_t key_buffer_size,
                                               size_t *key_buffer_length)
{

    psa_key_type_t key_type = psa_get_key_type(attributes);
    psa_status_t err = PSA_ERROR_NOT_SUPPORTED;


    /* Initialise the return value to 0 */
    *key_buffer_length = 0;

    /* These checks are mainly to check WANT_KEY_TYPE */
    if (PSA_KEY_TYPE_IS_KEY_PAIR(key_type)) {
#if defined(PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE)
        if (PSA_KEY_TYPE_IS_RSA(key_type)) {
            err = ele_internal_gen_rsa_keypair(attributes,
                                               key_buffer,
                                               key_buffer_size,
                                               key_buffer_length);
        }
#endif /* PSA_WANT_KEY_TYPE_RSA_KEY_PAIR_GENERATE */
    }

    return err;
}

/** @} */ // end of psa_key_generation
