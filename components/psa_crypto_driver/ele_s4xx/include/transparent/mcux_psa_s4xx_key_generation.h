/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUX_PSA_S4XX_KEY_GENERATION_H
#define MCUX_PSA_S4XX_KEY_GENERATION_H

/** \file ele_psa_key_generation.h
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

/*!
 * \brief Generate a random key
 *
 * \param[in]  attributes        Attributes of the key to use
 * \param[out] key_buffer        Buffer to hold the generated key
 * \param[in]  key_buffer_size   Size in bytes of the key_buffer buffer
 * \param[out] key_buffer_length Size in bytes of the generated key
 *
 * \retval  PSA_SUCCESS on success. Error code from \ref psa_status_t on
 *          failure
 */
psa_status_t ele_s4xx_transparent_generate_key(const psa_key_attributes_t *attributes,
                                               uint8_t *key_buffer, size_t key_buffer_size,
                                               size_t *key_buffer_length);

#ifdef __cplusplus
}
#endif
#endif /* MCUX_PSA_S4XX_KEY_GENERATION_H */
