/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "psa/crypto.h"
#include "psa_crypto_rsa.h"
#include "mbedtls/asn1write.h"

#include "mcux_psa_s4xx_common_key_management.h"
#include "mcux_psa_s4xx_common_init.h"

extern ele_s4xx_ctx_t g_ele_ctx;

/* These shouldbe initalized by some saved data on what group to start with */
uint32_t g_volatile_grp_id = ELE_KEYGROUP_ID_VOLATILE;
uint32_t g_persistent_grp_id = ELE_KEYGROUP_ID_PERSISTENT;

psa_status_t get_ele_key_group(psa_key_lifetime_t lifetime, uint16_t *keyGroupID)
{
    uint16_t grp_id = 0u;

    if (PSA_KEY_LIFETIME_IS_VOLATILE(lifetime)) {
        if (g_volatile_grp_id >= ELE_KEYGROUP_ID_VOLATILE_LIMIT) {
            return PSA_ERROR_INSUFFICIENT_STORAGE;
        }
        grp_id = g_volatile_grp_id++;
    } else {
        if (g_persistent_grp_id >= ELE_KEYGROUP_ID_PERSISTENT_LIMIT) {
            return PSA_ERROR_INSUFFICIENT_STORAGE;
        }
        grp_id = g_persistent_grp_id++;
    }

    *keyGroupID = grp_id;

    return PSA_SUCCESS;
}

psa_status_t ele_get_key_id_from_buf(const psa_key_attributes_t *attributes,
                                     const uint8_t *key_buffer,
                                     size_t key_buffer_size,
                                     uint32_t *key_id)
{

    if (!key_buffer || !key_buffer_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    // We are currently using the key id stored in key buffer. This is the one returned by ELE FW
    // When Key DB management comes into picture, we can directly pass the key id from attributes
    if (key_buffer_size < sizeof(key_id)) {
        return PSA_ERROR_INVALID_ARGUMENT;
    }

    memcpy(key_id, key_buffer, key_buffer_size);

    return PSA_SUCCESS;
}

// Functions

/*
 *  RSAPublicKey ::= SEQUENCE {
 *      modulus           INTEGER,  -- n
 *      publicExponent    INTEGER   -- e
 *  }
 * Inspired from function - pk_write_rsa_pubkey()
 * Write passed N and E to the buffer p in ASN format
 */
int mcux_write_rsa_pubkey_in_asn(unsigned char **p, unsigned char *start,
                                 uint8_t *modulus, size_t mod_len,
                                 int exponent)
{
    size_t len = 0;
    int ret = 0;
    mbedtls_mpi N, E;

    mbedtls_mpi_init(&N);
    mbedtls_mpi_init(&E);

    /*  Read from buf to mpi variable N */
    if (modulus != NULL) {
        MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&N, modulus, mod_len));
    } else {
        goto cleanup;
    }

    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&E, exponent));

    /* Export E */
    if ((ret = mbedtls_asn1_write_mpi(p, start, &E)) < 0) {
        goto cleanup;
    }
    len += ret;

    /* Export N */
    if ((ret = mbedtls_asn1_write_mpi(p, start, &N)) < 0) {
        len = 0;
        goto cleanup;
    }
    len += ret;

    MBEDTLS_ASN1_CHK_ADD(len, mbedtls_asn1_write_len(p, start, len));
    MBEDTLS_ASN1_CHK_ADD(len, mbedtls_asn1_write_tag(p, start, MBEDTLS_ASN1_CONSTRUCTED |
                                                     MBEDTLS_ASN1_SEQUENCE));

cleanup:
    mbedtls_mpi_free(&N);
    mbedtls_mpi_free(&E);

    return (int) len;
}

static int mcux_write_rsa_keypair_in_asn(psa_key_type_t key_type,
                                         struct rsa_keypair rsa_key,
                                         const uint8_t *key_buffer, size_t key_buffer_size,
                                         size_t *key_buffer_length)
{
    mbedtls_rsa_context rsa;
    uint32_t exponent;
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

    mbedtls_rsa_init(&rsa);

    mbedtls_mpi_init(&rsa.private_N);
    mbedtls_mpi_init(&rsa.private_D);

    if (sizeof(exponent) < rsa_key.pub_exp_len) {
        return PSA_ERROR_BAD_STATE;
    }

    memcpy(&exponent, rsa_key.pub_exp, rsa_key.pub_exp_len);
    mbedtls_mpi_lset(&rsa.private_E, exponent);

    /* Read modulo in MPI */
    mbedtls_mpi_read_binary(&rsa.private_N,
                            (const unsigned char *) rsa_key.modulus,
                            rsa_key.modulus_len);

    /* Read private exponent in MPI */
    mbedtls_mpi_read_binary(&rsa.private_D,
                            (const unsigned char *) rsa_key.priv_exp,
                            rsa_key.priv_exp_len);

    /* Set Ctx length */
    rsa.private_len = mbedtls_mpi_size(&rsa.private_N);

    /* Compute P and Q in CTX. */
    /* Needed as key buffer needs to be in PKCS1 format*/
    mbedtls_rsa_complete(&rsa);

    status = mbedtls_psa_rsa_export_key(key_type,
                                        &rsa, (uint8_t *) key_buffer, key_buffer_size,
                                        key_buffer_length);
    mbedtls_rsa_free(&rsa);

    return status;
}

/* Currently we are using mbedtls API's for translation. We can have our own asn implementation and replace this */
static psa_status_t mcux_write_rsa_keypair_from_asn(psa_key_type_t key_type,
                                                    const uint8_t *key_buffer, size_t key_length,
                                                    uint32_t key_bytes,
                                                    bool is_public,
                                                    struct rsa_keypair *rsa_key)
{
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    mbedtls_rsa_context *rsa = NULL;

    /* Parse input - We will use mbedtls_rsa_context to parse the context into*/
    status = mbedtls_psa_rsa_load_representation(key_type,
                                                 key_buffer,
                                                 key_length,
                                                 &rsa);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Alocate MPI structure for Public modulus */

#if defined(USE_MALLOC)
    rsa_key->modulus = malloc(key_bytes);
    if (rsa_key->modulus == NULL) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#else
    if (key_bytes > sizeof(rsa_key->modulus)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#endif
    rsa_key->modulus_len = key_bytes;

    if (is_public) {
#if defined(USE_MALLOC)
        /* Alocate MPI structure for Public exponent */
        rsa_key->pub_exp = malloc(sizeof(uint32_t));
        if (rsa_key->pub_exp == NULL) {
            free(rsa_key->modulus);
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
#else
        if (sizeof(uint32_t) > sizeof(rsa_key->pub_exp)) {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
#endif

        rsa_key->pub_exp_len = sizeof(uint32_t);
        mbedtls_mpi_write_binary(&rsa->MBEDTLS_PRIVATE(E),
                                 (unsigned char *) rsa_key->pub_exp,
                                 rsa_key->pub_exp_len);
    } else {
#if defined(USE_MALLOC)
        /* Alocate MPI structure for Private exponent */
        rsa_key->priv_exp = malloc(key_bytes);
        if (rsa_key->priv_exp == NULL) {
            free(rsa_key->modulus);
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
#else
        if (key_bytes > sizeof(rsa_key->priv_exp)) {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
#endif
        rsa_key->priv_exp_len = key_bytes;
        /* Read private exponent data from MPI ctx structure */
        mbedtls_mpi_write_binary(&rsa->MBEDTLS_PRIVATE(D),
                                 (unsigned char *) rsa_key->priv_exp,
                                 rsa_key->priv_exp_len);
    }

    /* Read motulus data from MPI ctx structure */
    mbedtls_mpi_write_binary(&rsa->MBEDTLS_PRIVATE(N), (unsigned char *) rsa_key->modulus,
                             key_bytes);

    return PSA_SUCCESS;

}

psa_status_t mcux_key_buf_to_raw_rsa(
    psa_key_type_t key_type, const uint8_t *key_buffer, size_t key_buffer_size,
    uint32_t key_bytes, bool is_public, struct rsa_keypair *rsa_key)
{
    return mcux_write_rsa_keypair_from_asn(key_type, key_buffer,
                                           key_buffer_size, key_bytes,
                                           is_public, rsa_key);
}

psa_status_t mcux_raw_rsa_to_key_buf(psa_key_type_t key_type, struct rsa_keypair rsa_key,
                                     const uint8_t *key_buffer, size_t key_buffer_size,
                                     size_t *key_buffer_length)
{
    return mcux_write_rsa_keypair_in_asn(key_type, rsa_key, key_buffer,
                                         key_buffer_size, key_buffer_length);
}

psa_status_t mcux_alloc_raw_rsa(struct rsa_keypair *rsa_key, size_t key_bytes)
{
#if defined(USE_MALLOC)
    rsa_key->modulus = malloc(key_bytes);
    if (rsa_key->modulus == NULL) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#else
    if (key_bytes > sizeof(rsa_key->modulus)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#endif
    rsa_key->modulus_len = key_bytes;


#if defined(USE_MALLOC)
    /* Alocate MPI structure for Public exponent */
    rsa_key->pub_exp = malloc(sizeof(uint32_t));
    if (rsa_key->pub_exp == NULL) {
        free(rsa_key->modulus);
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#else
    if (sizeof(uint32_t) > sizeof(rsa_key->pub_exp)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#endif

    rsa_key->pub_exp_len = sizeof(uint32_t);

#if defined(USE_MALLOC)
    /* Alocate MPI structure for Private exponent */
    rsa_key->priv_exp = malloc(key_bytes);
    if (rsa_key->priv_exp == NULL) {
        free(rsa_key->pub_exp);
        free(rsa_key->modulus);
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#else
    if (key_bytes > sizeof(rsa_key->priv_exp)) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    }
#endif
    rsa_key->priv_exp_len = key_bytes;

    return PSA_SUCCESS;
}

psa_status_t mcux_free_raw_rsa(struct rsa_keypair rsa_key)
{
#if defined(USE_MALLOC)
    if (rsa_key.modulus_len && rsa_key.modulus) {
        free(rsa_key.modulus);
    }

    if (rsa_key.pub_exp_len && rsa_key.pub_exp) {
        free(rsa_key.pub_exp);
    }

    if (rsa_key.priv_exp_len && rsa_key.priv_exp) {
        memset(rsa_key.priv_exp, 0, rsa_key.priv_exp_len);
        free(rsa_key.priv_exp);
    }
#else
    memset(&rsa_key, 0, sizeof(rsa_key));
#endif

    return PSA_SUCCESS;
}
/** @} */ // end of psa_key_generation
