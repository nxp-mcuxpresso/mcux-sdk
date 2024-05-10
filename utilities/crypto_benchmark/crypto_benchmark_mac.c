/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "crypto_benchmark.h"
#include "crypto_benchmark_mac.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HMAC_SHA224_BLOCK         64u /* SHA224 block is 64 Bytes (512bit) */
#define HMAC_SHA224_PAYLOAD       55u /* 512 bit - 64 bit (padding size) - 1bit (padding '1') = ~55 Bytes */
#define HMAC_SHA224_PAYLOAD_MULTI (HMAC_SHA224_BLOCK * (MULTIPLE_BLOCK - 1) + HMAC_SHA224_PAYLOAD) /* Multi-block */

#define HMAC_SHA256_BLOCK         64u /* SHA256 block is 64 Bytes (512bit) */
#define HMAC_SHA256_PAYLOAD       55u /* 512 bit - 64 bit (padding size) - 1bit (padding '1') = ~55 Bytes */
#define HMAC_SHA256_PAYLOAD_MULTI (HMAC_SHA256_BLOCK * (MULTIPLE_BLOCK - 1) + HMAC_SHA256_PAYLOAD) /* Multi-block */

#define HMAC_SHA384_BLOCK         128u /* SHA384 block is 128 Bytes (1024bit) */
#define HMAC_SHA384_PAYLOAD       111u /* 1024 bit - 128 bit (padding size) - 1bit (padding '1') = ~111 Bytes */
#define HMAC_SHA384_PAYLOAD_MULTI (HMAC_SHA384_BLOCK * (MULTIPLE_BLOCK - 1) + HMAC_SHA384_PAYLOAD) /* Multi-block */

#define HMAC_SHA512_BLOCK         128u /* SHA512 block is 128 Bytes (1024bit) */
#define HMAC_SHA512_PAYLOAD       111u /* 1024 bit - 128 bit (padding size) - 1bit (padding '1') = ~111 Bytes */
#define HMAC_SHA512_PAYLOAD_MULTI (HMAC_SHA512_BLOCK * (MULTIPLE_BLOCK - 1) + HMAC_SHA512_PAYLOAD) /* Multi-block */

#define HMAC_SHA256_KEY_SIZE    32u
#define HMAC_SHA256_DIGEST_SIZE 64u

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(CRYPTO_BENCHMARK_HMAC_SHA224) && (CRYPTO_BENCHMARK_HMAC_SHA224 == 1u) || \
    defined(CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE == 1u)
status_t hmac_sha224_benchmark(void)
{
    status_t status = kStatus_Fail;

#if defined(CRYPTO_BENCHMARK_HMAC_SHA224) && (CRYPTO_BENCHMARK_HMAC_SHA224 == 1u)
    /* Placeholder */
#endif /* CRYPTO_BENCHMARK_HMAC_SHA224 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE == 1u)
    /* Placeholder */
#endif /* CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE */

    return kStatus_Success;
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA224 || CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256) && (CRYPTO_BENCHMARK_HMAC_SHA256 == 1u) ||               \
    defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE == 1u) || \
    defined(CRYPTO_BENCHMARK_FAST_HMAC) && (CRYPTO_BENCHMARK_FAST_HMAC == 1u)
status_t hmac_sha256_benchmark(void)
{
    size_t DigestSize;
    uint8_t DigestHmac[HMAC_SHA256_DIGEST_SIZE] = {0u};
    uint8_t HmacSha256Key[HMAC_SHA256_KEY_SIZE] = {0u};
    status_t status                             = kStatus_Fail;

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256) && (CRYPTO_BENCHMARK_HMAC_SHA256 == 1u)
    PRINTF("One GO HMAC-SHA256:\r\n");

    PRINTF("\t HMAC-SHA2-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_mac_compute(kHmac_Sha256, g_CommonPayload, HMAC_SHA256_PAYLOAD, DigestHmac,
                                                    &DigestSize, HmacSha256Key, HMAC_SHA256_KEY_SIZE),
                       SINGLE_BLOCK, HMAC_SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t HMAC-SHA2-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_mac_compute(kHmac_Sha256, g_CommonPayload, HMAC_SHA256_PAYLOAD_MULTI,
                                                    DigestHmac, &DigestSize, HmacSha256Key, HMAC_SHA256_KEY_SIZE),
                       MULTIPLE_BLOCK, HMAC_SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE == 1u)
    PRINTF("One GO HMAC-SHA256 Opaque:\r\n");

    size_t key_sizes[]   = CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE_KEY_SIZES;
    uint32_t n_key_sizes = sizeof(key_sizes) / sizeof(key_sizes[0]);
    uint32_t key_id      = 0u;

    /* Opaque setup */
    status = wrapper_hmac_sha256_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure("HMAC SHA256 opaque setup");
    }

    for (int i = 0; i < n_key_sizes; i++)
    {
        PRINTF("Key Size: %lu\r\n", key_sizes[i]);

        /* Key generate */
        status = wrapper_hmac_sha256_opaque_key_generate(key_sizes[i], &key_id);
        if (status != kStatus_Success)
        {
            print_failure("HMAC SHA256 key generate");
        }

        PRINTF("\t HMAC-SHA2-256 Opaque single block: ");
        PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_hmac_sha256_opaque_compute(
                                                     g_CommonPayload, HMAC_SHA256_PAYLOAD, g_CommonOutput, key_id),
                                                 SINGLE_BLOCK, HMAC_SHA256_BLOCK));
        if (status != kStatus_Success)
        {
            print_failure(NULL);
        }

        PRINTF("\t HMAC-SHA2-256 Opaque multiple blocks: ");
        PRINTF("%f Cycles/Byte\r\n",
               CYCLES_BYTE(status = wrapper_hmac_sha256_opaque_compute(g_CommonPayload, HMAC_SHA256_PAYLOAD_MULTI,
                                                                       g_CommonOutput, key_id),
                           MULTIPLE_BLOCK, HMAC_SHA256_BLOCK));
        if (status != kStatus_Success)
        {
            print_failure(NULL);
        }

        /* Key delete */
        status = wrapper_hmac_sha256_opaque_key_delete(key_id);
        if (status != kStatus_Success)
        {
            print_failure("HMAC SHA256 key delete");
        }
    }

    /* Opaque cleanup */
    status = wrapper_hmac_sha256_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("HMAC SHA256 opaque cleanup");
    }

    PRINTF("\r\n");
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE */

#if defined(CRYPTO_BENCHMARK_FAST_HMAC) && (CRYPTO_BENCHMARK_FAST_HMAC == 1u)
    /* FastMAC can only do SHA256 HMAC */
    PRINTF("One GO FastHMAC (SHA256):\r\n");

    /* Fast HMAC Start */
    double setup_cycles = CYCLES_COUNT(status = wrapper_fast_mac_start(HmacSha256Key));
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Start");
    }

    /* Benchmark including Start and Finish (= same as Generic + 1 call for finish) */
    // double update_cycles = CYCLES_COUNT(wrapper_fast_mac_proceed(g_CommonPayload, HMAC_SHA256_PAYLOAD, DigestHmac));
    // double finish_cycles = CYCLES_COUNT(wrapper_fast_mac_end());
    // PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / HMAC_SHA256_BLOCK);

    PRINTF("\t FastHMAC-SHA2-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_fast_mac_proceed(g_CommonPayload, HMAC_SHA256_PAYLOAD, DigestHmac),
                       SINGLE_BLOCK, HMAC_SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Proceed");
    }

    PRINTF("\t FastHMAC-SHA2-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_fast_mac_proceed(g_CommonPayload, HMAC_SHA256_PAYLOAD_MULTI, DigestHmac),
                       MULTIPLE_BLOCK, HMAC_SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Proceed");
    }

    /* Fast HMAC 1500B*/
    double time_spent = TIME_TOTAL_USEC(status = wrapper_fast_mac_proceed(g_CommonPayload, 1500u, DigestHmac));
    PRINTF("\t FastHMAC-SHA2-256 1500 B: %lf u sec\r\n", time_spent);
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Proceed");
    }

    /* Fast HMAC 80*/
    time_spent = TIME_TOTAL_USEC(status = wrapper_fast_mac_proceed(g_CommonPayload, 80u, DigestHmac));
    PRINTF("\t FastHMAC-SHA2-256 80 B: %lf u sec\r\n", time_spent);
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Proceed");
    }

    /* Fast HMAC 32*/
    time_spent = TIME_TOTAL_USEC(status = wrapper_fast_mac_proceed(g_CommonPayload, 32u, DigestHmac));
    PRINTF("\t FastHMAC-SHA2-256 32 B: %lf u sec\r\n", time_spent);
    if (status != kStatus_Success)
    {
        print_failure("FastMAC Proceed");
    }

    /* Fast HMAC Finish */
    double finish_cycles = CYCLES_COUNT(status = wrapper_fast_mac_end());
    if (status != kStatus_Success)
    {
        print_failure("FastMAC End");
    }

    PRINTF("\r\n");
#endif /* defined(CRYPTO_BENCHMARK_FAST_HMAC) */

    return kStatus_Success;
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA256 || CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE || CRYPTO_BENCHMARK_FAST_HMAC */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384) && (CRYPTO_BENCHMARK_HMAC_SHA384 == 1u) || \
    defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE == 1u)
status_t hmac_sha384_benchmark(void)
{
    status_t status = kStatus_Fail;

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384) && (CRYPTO_BENCHMARK_HMAC_SHA384 == 1u)
    /* Placeholder */
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE == 1u)
    PRINTF("One GO HMAC-SHA384 Opaque:\r\n");

    size_t key_sizes[]   = CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE_KEY_SIZES;
    uint32_t n_key_sizes = sizeof(key_sizes) / sizeof(key_sizes[0]);
    uint32_t key_id      = 0u;

    /* Opaque setup */
    status = wrapper_hmac_sha384_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure("HMAC SHA384 opaque setup");
    }

    for (int i = 0; i < n_key_sizes; i++)
    {
        PRINTF("Key Size: %lu\r\n", key_sizes[i]);

        /* Key generate */
        status = wrapper_hmac_sha384_opaque_key_generate(key_sizes[i], &key_id);
        if (status != kStatus_Success)
        {
            print_failure("HMAC SHA384 key generate");
        }

        PRINTF("\t HMAC-SHA2-384 Opaque single block: ");
        PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_hmac_sha384_opaque_compute(
                                                     g_CommonPayload, HMAC_SHA384_PAYLOAD, g_CommonOutput, key_id),
                                                 SINGLE_BLOCK, HMAC_SHA384_BLOCK));
        if (status != kStatus_Success)
        {
            print_failure(NULL);
        }

        PRINTF("\t HMAC-SHA2-384 Opaque multiple blocks: ");
        PRINTF("%f Cycles/Byte\r\n",
               CYCLES_BYTE(status = wrapper_hmac_sha384_opaque_compute(g_CommonPayload, HMAC_SHA384_PAYLOAD_MULTI,
                                                                       g_CommonOutput, key_id),
                           MULTIPLE_BLOCK, HMAC_SHA384_BLOCK));
        if (status != kStatus_Success)
        {
            print_failure(NULL);
        }

        /* Key delete */
        status = wrapper_hmac_sha384_opaque_key_delete(key_id);
        if (status != kStatus_Success)
        {
            print_failure("HMAC SHA384 key delete");
        }
    }

    /* Opaque cleanup */
    status = wrapper_hmac_sha384_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("HMAC SHA384 opaque cleanup");
    }

    PRINTF("\r\n");
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE */

    return kStatus_Success;
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA384 || CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA512) && (CRYPTO_BENCHMARK_HMAC_SHA512 == 1u) || \
    defined(CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE == 1u)
status_t hmac_sha512_benchmark(void)
{
    status_t status = kStatus_Fail;

#if defined(CRYPTO_BENCHMARK_HMAC_SHA512) && (CRYPTO_BENCHMARK_HMAC_SHA512 == 1u)
    /* Placeholder */
#endif /* CRYPTO_BENCHMARK_HMAC_SHA512 */

#if defined(CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE) && (CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE == 1u)
    /* Placeholder */
#endif /* CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE */

    return kStatus_Success;
}
#endif /* CRYPTO_BENCHMARK_HMAC_SHA512 || CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE */
