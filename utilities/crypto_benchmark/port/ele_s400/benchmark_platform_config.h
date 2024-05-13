/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BENCHMARK_PLATFORM_CONFIG_H
#define BENCHMARK_PLATFORM_CONFIG_H

#define CRYPTO_BENCHMARK_SHA224  (1u)
#define CRYPTO_BENCHMARK_SHA256  (1u)
#define CRYPTO_BENCHMARK_SHA384  (1u)
#define CRYPTO_BENCHMARK_SHA512  (1u)
#define CRYPTO_BENCHMARK_AES_ECB (1u)
#define CRYPTO_BENCHMARK_AES_CTR (1u)
#define CRYPTO_BENCHMARK_AES_CBC (1u)
#define CRYPTO_BENCHMARK_AES_OFB (1u)
#define CRYPTO_BENCHMARK_AES_CFB (1u)
#define CRYPTO_BENCHMARK_AES_CCM (1u)
#define CRYPTO_BENCHMARK_AES_GCM (1u)
// #define CRYPTO_BENCHMARK_AEAD_MULTIPART (1u) /* Disabled until new ELE FW */

#define CRYPTO_BENCHMARK_HMAC_SHA256 (1u)
#define CRYPTO_BENCHMARK_FAST_HMAC   (1u) /* ELE-specific */

// #define CRYPTO_BENCHMARK_CMAC (1u)
// #define CRYPTO_BENCHMARK_RSA (1u)
// #define CRYPTO_BENCHMARK_CTR_DRBG (1u)
// #define CRYPTO_BENCHMARK_HMAC_DRBG (1u)
// #define CRYPTO_BENCHMARK_ECC (1u)
// #define CRYPTO_BENCHMARK_ENTROPY (1u)
// #define CRYPTO_BENCHMARK_ECDH (1u)

/*******************************************************************************
 * Enablers for opaque benchmarking
 ******************************************************************************/
#define CRYPTO_BENCHMARK_AES_ECB_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_CTR_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_CBC_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_OFB_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_CFB_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_CCM_OPAQUE (1u)
#define CRYPTO_BENCHMARK_AES_GCM_OPAQUE (1u)

#define CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE (1u)
#define CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE (1u)

/*******************************************************************************
 * Benchmark setup defines
 ******************************************************************************/
#if defined(CRYPTO_BENCHMARK_HMAC_SHA256) && (CRYPTO_BENCHMARK_HMAC_SHA256 == 1u)
#define CRYPTO_BENCHMARK_HMAC_SHA256_KEY_SIZES {256u}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE == 1u)
#define CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE_KEY_SIZES {224u, 256u, 384u, 512u}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE == 1u)
#define CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE_KEY_SIZES {224u, 256u, 384u, 512u}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE */

/*******************************************************************************
 * Encapsulating defines
 ******************************************************************************/
#if defined(CRYPTO_BENCHMARK_HMAC_SHA224) || defined(CRYPTO_BENCHMARK_HMAC_SHA256) ||               \
    defined(CRYPTO_BENCHMARK_HMAC_SHA384) || defined(CRYPTO_BENCHMARK_HMAC_SHA512) ||               \
    defined(CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE) || defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) || \
    defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) || defined(CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE) || \
    defined(CRYPTO_BENCHMARK_FAST_HMAC)
#define CRYPTO_BENCHMARK_HMAC
#endif

#endif /* BENCHMARK_PLATFORM_CONFIG_H */
