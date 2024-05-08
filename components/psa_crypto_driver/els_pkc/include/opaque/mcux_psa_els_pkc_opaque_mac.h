/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_ELS_PKC_OPAQUE_MAC_H
#define MCUX_PSA_ELS_PKC_OPAQUE_MAC_H

/** \file mcux_psa_els_pkc_mac.h
 *
 * This file contains the declaration of the entry points associated to the
 * mac capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "psa/crypto.h"
#include "els_pkc_crypto_primitives.h"
#include <mcuxCsslMemory.h>
#include <internal/mcuxClMac_Internal_Constants.h>
   
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Perform a MAC operation in a single step
 *
 * \param[in]  attributes      Attributes for the key to be set
 * \param[in]  key_buffer      Buffer holding key material
 * \param[in]  key_buffer_size Size in bytes of the key
 * \param[in]  alg             Algorithm to be used
 * \param[in]  input           Buffer containing input data to produce the MAC
 * \param[in]  input_length    Size in bytes of the input buffer
 * \param[out] mac             Buffer holding the produced MAC value
 * \param[in]  mac_size        Size in bytes of the mac buffer
 * \param[out] mac_length      Size in bytes of the produced MAC value
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_compute(const psa_key_attributes_t *attributes,
                             const uint8_t *key_buffer,
                             size_t key_buffer_size, psa_algorithm_t alg,
                             const uint8_t *input, size_t input_length,
                             uint8_t *mac, size_t mac_size,
                             size_t *mac_length);

/*!
 * \brief Setup a MAC signing object
 *
 * \param[in] operation       Pointer to the operation object
 * \param[in] attributes      Attributes for the key to be set
 * \param[in] key_buffer      Buffer holding key material
 * \param[in] key_buffer_size Size in bytes of the key
 * \param[in] alg             Algorithm to setup
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_sign_setup(els_pkc_opaque_mac_operation_t *operation,
                                const psa_key_attributes_t *attributes,
                                const uint8_t *key_buffer,
                                size_t key_buffer_size, psa_algorithm_t alg);
/*!
 * \brief Setup a MAC verifying object
 *
 * \param[in] operation       Pointer to the operation object
 * \param[in] attributes      Attributes for the key to be set
 * \param[in] key_buffer      Buffer holding key material
 * \param[in] key_buffer_size Size in bytes of the key
 * \param[in] alg             Algorithm to setup
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_verify_setup(els_pkc_opaque_mac_operation_t *operation,
                                  const psa_key_attributes_t *attributes,
                                  const uint8_t *key_buffer,
                                  size_t key_buffer_size,
                                  psa_algorithm_t alg);
/*!
 * \brief Update a MAC object with new data to authenticate
 *
 * \param[in] operation    Pointer to the operation object
 * \param[in] input        Buffer holding the new input data
 * \param[in] input_length Size in bytes of the input buffer
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_update(els_pkc_opaque_mac_operation_t *operation,
                            const uint8_t *input, size_t input_length);
/*!
 * \brief Finalize a MAC signing operation by producing the MAC value
 *
 * \param[in]  operation  Pointer to the operation object
 * \param[out] mac        Buffer holding the produced MAC
 * \param[in]  mac_size   Size in bytes of the mac buffer
 * \param[out] mac_length Size in bytes of the produced MAC
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_sign_finish(els_pkc_opaque_mac_operation_t *operation,
                                 uint8_t *mac, size_t mac_size,
                                 size_t *mac_length);
/*!
 * \brief Finalize a MAC verifying operation by checking the produced
 *        MAC matches with the reference MAC value
 *
 * \param[in] operation  Pointer to the operation object
 * \param[in] mac        Buffer holding the reference MAC value to verify
 * \param[in] mac_length Size in bytes of the mac buffer
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_verify_finish(els_pkc_opaque_mac_operation_t *operation,
                                   const uint8_t *mac, size_t mac_length);
/*!
 * \brief Abort a MAC operation
 *
 * \param[out] operation Pointer to the operation object
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_opaque_mac_abort(els_pkc_opaque_mac_operation_t *operation);

#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_ELS_PKC_OPAQUE_MAC_H */
