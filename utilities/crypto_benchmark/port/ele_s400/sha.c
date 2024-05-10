/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "crypto_benchmark.h"
#include "crypto_benchmark_hash.h"
#include "ele_crypto.h"
#include "ele.h"

status_t wrapper_hash_compute(
    hash_mode_t alg, const uint8_t *input, size_t input_length, uint8_t *hash, size_t hash_size, size_t *hash_length)
{
    status_t status  = kStatus_Fail;
    hash_algo_t mode = (hash_algo_t)alg;

    /* Assign the output buffer size to 0. This will be updated by ELE */
    *hash_length = 0;

    status = ELE_Hash(S3MU, input, input_length, hash, hash_size, hash_length, mode);

    return status;
}

status_t wrapper_hash_setup(void *ctx, hash_mode_t alg)
{
    status_t status              = kStatus_Fail;
    hash_algo_t mode             = (hash_algo_t)alg;
    ele_hash_ctx_t *ctx_internal = (ele_hash_ctx_t *)ctx;

    status = ELE_Hash_Init(S3MU, ctx_internal, mode);

    return status;
}

status_t wrapper_hash_update(void *ctx, const uint8_t *input, size_t input_length, hash_mode_t alg)
{
    status_t status              = kStatus_Fail;
    ele_hash_ctx_t *ctx_internal = (ele_hash_ctx_t *)ctx;
    hash_algo_t mode             = (hash_algo_t)alg;

    status = ELE_Hash_Update(S3MU, ctx_internal, mode, input, input_length);

    return status;
}

status_t wrapper_hash_finish(void *ctx, uint8_t *hash, size_t hash_size, size_t *hash_length, hash_mode_t alg)
{
    status_t status              = kStatus_Fail;
    ele_hash_ctx_t *ctx_internal = (ele_hash_ctx_t *)ctx;
    hash_algo_t mode             = (hash_algo_t)alg;

    status = ELE_Hash_Finish(S3MU, ctx_internal, mode, hash, hash_size, hash_length, NULL, 0u);

    return status;
}
