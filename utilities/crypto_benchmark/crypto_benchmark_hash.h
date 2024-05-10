/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CRYPTO_BENCHMARK_HASH_H
#define CRYPTO_BENCHMARK_HASH_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"
#include "crypto_benchmark.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HASH_CTX_MAX_SIZE 256u /* Choose sufficient size of CTX structure */

typedef enum _hash_mode_t
{
    kSha224 = 0x02000008, /*!< SHA_224  */
    kSha256 = 0x02000009, /*!< SHA_256  */
    kSha384 = 0x0200000A, /*!< SHA_384  */
    kSha512 = 0x0200000B, /*!< SHA_512  */
    kSM3256 = 0x02000014, /*!< SM3_256  */
} hash_mode_t;

typedef struct hash_ctx
{
    uint8_t X[HASH_CTX_MAX_SIZE];
} hash_ctx;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t sha224_benchmark(void);
status_t sha256_benchmark(void);
status_t sha384_benchmark(void);
status_t sha512_benchmark(void);

status_t wrapper_hash_compute(hash_mode_t alg,
                              const uint8_t *input,
                              size_t input_length,
                              uint8_t *hash,
                              size_t hash_size,
                              size_t *hash_length);

status_t wrapper_hash_setup(void *ctx,
                            hash_mode_t alg);

status_t wrapper_hash_update(void *ctx,
                             const uint8_t *input,
                             size_t input_length,
                             hash_mode_t alg); /* Alg mode may be unused */

status_t wrapper_hash_finish(void *ctx,
                             uint8_t *hash,
                             size_t hash_size,
                             size_t *hash_length,
                             hash_mode_t alg); /* Alg mode may be unused */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#endif /* CRYPTO_BENCHMARK_HASH_H */
