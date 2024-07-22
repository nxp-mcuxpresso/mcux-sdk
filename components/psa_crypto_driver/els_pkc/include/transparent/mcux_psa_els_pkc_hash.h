/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_ELS_PKC_HASH_H
#define MCUX_PSA_ELS_PKC_HASH_H

/** \file mcux_psa_els_pkc_hash.h
 *
 * This file contains the declaration of the entry points associated to the
 * hash capability (single-part and multipart) as described by the PSA
 * Cryptoprocessor Driver interface specification
 *
 */

#include "psa/crypto.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Set up an operation object for hashing with an algorithm
 *
 * \param[in] operation Pointer to the operation object to be setup
 * \param[in] alg       Algorithm for hash to be used
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_setup(els_pkc_hash_operation_t *operation,
                                             psa_algorithm_t alg);
/*!
 * \brief Clone an operation object
 *
 * \param[in]  source_operation Pointer to the operation to be cloned
 * \param[out] target_operation Pointer to the target operation
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_clone(const els_pkc_hash_operation_t *source_operation,
                                             els_pkc_hash_operation_t *target_operation);
/*!
 * \brief Updates an hash operation with some new input data
 *
 * \param[in]  operation    Pointer to the operation object
 * \param[in]  input        Buffer containing the input data
 * \param[out] input_length Size in bytes of the input data
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_update(els_pkc_hash_operation_t *operation,
                                              const uint8_t *input, size_t input_length);
/*!
 * \brief Finish an hash operation and produce the hash output
 *
 * \param[in]  operation   Pointer to the operation object
 * \param[out] hash        Buffer containing the output hash
 * \param[in]  hash_size   Size in bytes of the hash buffer
 * \param[out] hash_length Size of the produced hash in bytes
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_finish(els_pkc_hash_operation_t *operation, uint8_t *hash,
                                              size_t hash_size, size_t *hash_length);
/*!
 * \brief Abort an hash operation
 *
 * \param[out] operation Pointer to the operation object
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_abort(els_pkc_hash_operation_t *operation);

/*!
 * \brief Performs hashing of the input in a single call
 *
 * \param[in]  alg          Algorithm to be used
 * \param[in]  input        Buffer containing the input
 * \param[in]  input_length Size in bytes of the input data
 * \param[out] hash         Buffer containing the output hash
 * \param[in]  hash_size    Size in bytes of the hash buffer
 * \param[out] hash_length  Size in bytes
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t els_pkc_transparent_hash_compute(psa_algorithm_t alg, const uint8_t *input,
                                               size_t input_length, uint8_t *hash,
                                               size_t hash_size, size_t *hash_length);
#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_ELS_PKC_HASH_H */
