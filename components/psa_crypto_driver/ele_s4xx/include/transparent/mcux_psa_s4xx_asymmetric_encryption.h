/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_S4XX_ASYMMETRIC_ENCRYPTION_H
#define MCUX_PSA_S4XX_ASYMMETRIC_ENCRYPTION_H

/** \file mcux_psa_s4xx_asymmetric_encryption.h
 *
 * This file contains the declaration of the entry points associated to the
 * asymmetric encryption capability as described by the PSA Cryptoprocessor
 * Driver interface specification
 *
 */

#include "psa/crypto.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Asymmetric encryption (RSA PKCS#1 v1.5 or RSA-OAEP)
 *
 * \param[in]  attributes      Attributes of the key to use
 * \param[in]  key_buffer      Key material buffer
 * \param[in]  key_buffer_size Size in bytes of the key
 * \param[in]  alg             Algorithm to use
 * \param[in]  input           Data to encrypt buffer
 * \param[in]  input_length    Size in bytes of the data to encrypt
 * \param[in]  salt            Additional salt if supported by the algorithm
 * \param[in]  salt_length     Size in bytes of the salt buffer
 * \param[out] output          Buffer to hold the encrypted data
 * \param[in]  output_size     Size in bytes of the output buffer
 * \param[out] output_length   Size in bytes of the encrypted data
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_transparent_asymmetric_encrypt(const psa_key_attributes_t *attributes,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *input,
                                                     size_t input_length,
                                                     const uint8_t *salt, size_t salt_length,
                                                     uint8_t *output, size_t output_size,
                                                     size_t *output_length);

/*!
 * \brief Asymmetric decryption (RSA PKCS#1 v1.5 or RSA-OAEP)
 *
 * \param[in]  attributes      Attributes of the key to use
 * \param[in]  key_buffer      Key material buffer
 * \param[in]  key_buffer_size Size in bytes of the key
 * \param[in]  alg             Algorithm to use
 * \param[in]  input           Data to decrypt buffer
 * \param[in]  input_length    Size in bytes of the data to decrypt
 * \param[in]  salt            Additional salt if supported by the algorithm
 * \param[in]  salt_length     Size in bytes of the salt buffer
 * \param[out] output          Buffer to hold the decrypted data
 * \param[in]  output_size     Size in bytes of the output buffer
 * \param[out] output_length   Size in bytes of the decrypted data
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_transparent_asymmetric_decrypt(const psa_key_attributes_t *attributes,
                                                     const uint8_t *key_buffer,
                                                     size_t key_buffer_size,
                                                     psa_algorithm_t alg,
                                                     const uint8_t *input,
                                                     size_t input_length,
                                                     const uint8_t *salt, size_t salt_length,
                                                     uint8_t *output, size_t output_size,
                                                     size_t *output_length);
#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_S4XX_ASYMMETRIC_ENCRYPTION_H */
