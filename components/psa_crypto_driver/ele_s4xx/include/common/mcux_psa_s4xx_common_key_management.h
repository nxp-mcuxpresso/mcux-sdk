/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_S4XX_COMMON_KEY_MANAGEMENT_H
#define MCUX_PSA_S4XX_COMMON_KEY_MANAGEMENT_H

/** \file mcux_psa_s4xx_common_key_management.h
 *
 * This file contains the declaration of the entry points associated to the
 * key generation (i.e. random generation and extraction of public keys) as
 * described by the PSA Cryptoprocessor Driver interface specification
 *
 */

#include "psa/crypto.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ELE_KEY_USAGE_MASK      (kKeyUsage_Encrypt | kKeyUsage_Decrypt | \
                                 kKeyUsage_SignMessage | kKeyUsage_VerifyMessage | \
                                 kKeyUsage_SignHash | kKeyUsage_VerifyHash | kKeyUsage_Derive)

#define MAX_RSA_KEYSIZE          (4096/8)
#define MAX_RSA_EXP_SIZE          4

#define USE_MALLOC

#if defined(USE_MALLOC)
struct rsa_keypair {
    size_t modulus_len;
    size_t pub_exp_len;
    size_t priv_exp_len;
    uint32_t *modulus;
    uint32_t *pub_exp;
    uint32_t *priv_exp;
};
#else
struct rsa_keypair {
    size_t modulus_len;
    size_t pub_exp_len;
    size_t priv_exp_len;
    uint32_t modulus[MAX_RSA_KEYSIZE];
    uint32_t pub_exp[MAX_RSA_EXP_SIZE];
    uint32_t priv_exp[MAX_RSA_KEYSIZE];
};
#endif

psa_status_t ele_get_key_id_from_buf(const psa_key_attributes_t *attributes,
                                     const uint8_t *key_buffer,
                                     size_t key_buffer_size,
                                     uint32_t *key_id);

psa_status_t get_ele_key_group(psa_key_lifetime_t lifetime, uint16_t *keyGroupID);

int mcux_write_rsa_pubkey_in_asn(unsigned char **p, unsigned char *start,
                                 uint8_t *modulus, size_t mod_len,
                                 int exponent);

/* Convert the content of key buffer to struct rsa_priv -> RAW binary format */
psa_status_t mcux_key_buf_to_raw_rsa(psa_key_type_t key_type,
                                     const uint8_t *key_buffer,
                                     size_t key_buffer_size,
                                     uint32_t key_bytes,
                                     bool is_public,
                                     struct rsa_keypair *rsa_key);


/* Convert struct RSA raw binary format to key buffer content
 *  For now to keep things simple, we are assuming key buffer is in ASN1 format.
 */
psa_status_t mcux_raw_rsa_to_key_buf(psa_key_type_t key_type, struct rsa_keypair rsa_key,
                                     const uint8_t *key_buffer, size_t key_buffer_size,
                                     size_t *key_buffer_length);

psa_status_t mcux_alloc_raw_rsa(struct rsa_keypair *rsa_key, size_t key_bytes);
psa_status_t mcux_free_raw_rsa(struct rsa_keypair rsa_key);

#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_S4XX_COMMON_KEY_MANAGEMENT_H */
