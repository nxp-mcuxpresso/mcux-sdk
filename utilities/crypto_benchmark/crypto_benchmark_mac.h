/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CRYPTO_BENCHMARK_MAC_H
#define CRYPTO_BENCHMARK_MAC_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"
#include "crypto_benchmark.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum _mac_alg_t
{
    kHmac_Sha256 = 0x03800009 /*!< HMAC SHA_256 */
} mac_alg_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t hmac_sha224_benchmark(void);
status_t hmac_sha256_benchmark(void);
status_t hmac_sha384_benchmark(void);
status_t hmac_sha512_benchmark(void);

status_t wrapper_mac_compute(mac_alg_t alg,
                             const uint8_t *input,
                             size_t input_length,
                             uint8_t *mac,
                             size_t *mac_size,
                             const uint8_t *key,
                             size_t key_length);

/*******************************************************************************
 * Generic
 ******************************************************************************/
#if defined(CRYPTO_BENCHMARK_HMAC_SHA224) && (CRYPTO_BENCHMARK_HMAC_SHA224 == 1u)
status_t wrapper_hmac_sha224_compute(
    const uint8_t *input, size_t input_length, uint8_t *mac, size_t *mac_size, const uint8_t *key, size_t key_length);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA224 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256) && (CRYPTO_BENCHMARK_HMAC_SHA256 == 1u)
status_t wrapper_hmac_sha256_compute(
    const uint8_t *input, size_t input_length, uint8_t *mac, size_t *mac_size, const uint8_t *key, size_t key_length);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384) && (CRYPTO_BENCHMARK_HMAC_SHA384 == 1u)
status_t wrapper_hmac_sha384_compute(
    const uint8_t *input, size_t input_length, uint8_t *mac, size_t *mac_size, const uint8_t *key, size_t key_length);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA512) && (CRYPTO_BENCHMARK_HMAC_SHA512 == 1u)
status_t wrapper_hmac_sha512_compute(
    const uint8_t *input, size_t input_length, uint8_t *mac, size_t *mac_size, const uint8_t *key, size_t key_length);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA512 */

/*******************************************************************************
 * Opaque
 ******************************************************************************/
#if defined(CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE == 1u)
status_t wrapper_hmac_sha224_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id);
status_t wrapper_hmac_sha224_opaque_setup(void);
status_t wrapper_hmac_sha224_opaque_cleanup(void);
status_t wrapper_hmac_sha224_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id);
status_t wrapper_hmac_sha224_opaque_key_delete(uint32_t hmac_key_id);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE == 1u)
status_t wrapper_hmac_sha256_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id);
status_t wrapper_hmac_sha256_opaque_setup(void);
status_t wrapper_hmac_sha256_opaque_cleanup(void);
status_t wrapper_hmac_sha256_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id);
status_t wrapper_hmac_sha256_opaque_key_delete(uint32_t hmac_key_id);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE == 1u)
status_t wrapper_hmac_sha384_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id);
status_t wrapper_hmac_sha384_opaque_setup(void);
status_t wrapper_hmac_sha384_opaque_cleanup(void);
status_t wrapper_hmac_sha384_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id);
status_t wrapper_hmac_sha384_opaque_key_delete(uint32_t hmac_key_id);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE == 1u)
status_t wrapper_hmac_sha512_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *mac, uint32_t key_id);
status_t wrapper_hmac_sha512_opaque_setup(void);
status_t wrapper_hmac_sha512_opaque_cleanup(void);
status_t wrapper_hmac_sha512_opaque_key_generate(uint16_t key_size, uint32_t *hmac_key_id);
status_t wrapper_hmac_sha512_opaque_key_delete(uint32_t hmac_key_id);
#endif /* CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE */

#if defined(CRYPTO_BENCHMARK_FAST_HMAC) && (CRYPTO_BENCHMARK_FAST_HMAC == 1u)
status_t wrapper_fast_mac_start(const uint8_t *key);
status_t wrapper_fast_mac_proceed(const uint8_t *input, size_t input_length, uint8_t *mac);
status_t wrapper_fast_mac_end(void);
#endif /* defined(CRYPTO_BENCHMARK_FAST_HMAC) */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#endif /* CRYPTO_BENCHMARK_MAC_H */
