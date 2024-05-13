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
#include "crypto_benchmark_hash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SHA256_BLOCK         64u /* SHA256 block is 64 Bytes (512bit) */
#define SHA256_PAYLOAD       55u /* 512 bit - 64 bit (padding size) - 1bit (padding '1') = ~55 Bytes */
#define SHA256_PAYLOAD_MULTI (SHA256_BLOCK * (MULTIPLE_BLOCK - 1) + SHA256_PAYLOAD)

#define SHA384_SHA512_BLOCK      128u /* SHA384/512 block is 128 Bytes (1024 bit) */
#define SHA384_SHA512_PAYLOAD    111u /* 1024 bit - 128 bit (padding size) - 1bit (padding '1') = ~111 Bytes */
#define SHA384_512_PAYLOAD_MULTI (SHA384_SHA512_BLOCK * (MULTIPLE_BLOCK - 1) + SHA384_SHA512_PAYLOAD)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t sha224_benchmark(void)
{
    /* One GO */
    PRINTF("One GO SHA:\r\n");
    uint32_t hash_length   = 0u;
    status_t status        = kStatus_Fail;
    status_t status_setup  = kStatus_Fail;
    status_t status_update = kStatus_Fail;
    status_t status_finish = kStatus_Fail;

    uint8_t DigestSha224[28u] = {0u};
    PRINTF("\t SHA2-224 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha224, g_CommonPayload, SHA256_PAYLOAD, DigestSha224,
                                                     sizeof(DigestSha224), &hash_length),
                       SINGLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-224 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha224, g_CommonPayload, SHA256_PAYLOAD_MULTI, DigestSha224,
                                                     sizeof(DigestSha224), &hash_length),
                       MULTIPLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

    /* Multi-part */
    PRINTF("Multi-part (streaming) SHA:\r\n");

    PRINTF("\t SHA2-224 single block: ");
    hash_ctx ctx224;
    double setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx224, kSha224));
    double update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx224, g_CommonPayload, SHA256_PAYLOAD, kSha224));
    double finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx224, DigestSha224, sizeof(DigestSha224), &hash_length, kSha224));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / SHA256_BLOCK);
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-224 multiple blocks: ");
    setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx224, kSha224));
    update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx224, g_CommonPayload, SHA256_PAYLOAD_MULTI, kSha224));
    finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx224, DigestSha224, sizeof(DigestSha224), &hash_length, kSha224));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / (SHA256_BLOCK * MULTIPLE_BLOCK));
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    return kStatus_Success;
}

status_t sha256_benchmark(void)
{
    /* One GO */
    PRINTF("One GO SHA:\r\n");
    uint32_t hash_length   = 0u;
    status_t status        = kStatus_Fail;
    status_t status_setup  = kStatus_Fail;
    status_t status_update = kStatus_Fail;
    status_t status_finish = kStatus_Fail;

    uint8_t DigestSha256[32u] = {0u};
    PRINTF("\t SHA2-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha256, g_CommonPayload, SHA256_PAYLOAD, DigestSha256,
                                                     sizeof(DigestSha256), &hash_length),
                       SINGLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /*  One time call implementation, provides similar numbers compared to multiple calls and it's average above

        double one_go_single_block_count = CYCLES_COUNT(wrapper_hash_compute(kSha256,
                                             g_CommonPayload,
                                             SHA256_PAYLOAD,
                                             DigestSha256,
                                             sizeof(DigestSha256),
                                             &hash_length));
        PRINTF("Cycles/Byte: %f\r\n", one_go_single_block_count / SHA256_BLOCK);
    */
    PRINTF("\t SHA2-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha256, g_CommonPayload, SHA256_PAYLOAD_MULTI, DigestSha256,
                                                     sizeof(DigestSha256), &hash_length),
                       MULTIPLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /*
        double one_go_multi_blocks_count = CYCLES_COUNT(wrapper_hash_compute(kSha256,
                                             g_CommonPayload,
                                             SHA256_PAYLOAD_MULTI,
                                             DigestSha256,
                                             sizeof(DigestSha256),
                                             &hash_length));
        PRINTF("Cycles/Byte: %f\r\n", one_go_multi_blocks_count / (SHA256_BLOCK * MULTIPLE_BLOCK));
    */

    PRINTF("\r\n");

    /* Multi-part */
    PRINTF("Multi-part (streaming) SHA:\r\n");

    PRINTF("\t SHA2-256 single block: ");
    hash_ctx ctx256;
    double setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx256, kSha256));
    double update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx256, g_CommonPayload, SHA256_PAYLOAD, kSha256));
    double finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx256, DigestSha256, sizeof(DigestSha256), &hash_length, kSha256));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / SHA256_BLOCK);
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-256 multiple blocks: ");
    setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx256, kSha256));
    update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx256, g_CommonPayload, SHA256_PAYLOAD_MULTI, kSha256));
    finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx256, DigestSha256, sizeof(DigestSha256), &hash_length, kSha256));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / (SHA256_BLOCK * MULTIPLE_BLOCK));
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    return kStatus_Success;
}

status_t sha384_benchmark(void)
{
    /* One GO */
    PRINTF("One GO SHA:\r\n");
    uint32_t hash_length   = 0u;
    status_t status        = kStatus_Fail;
    status_t status_setup  = kStatus_Fail;
    status_t status_update = kStatus_Fail;
    status_t status_finish = kStatus_Fail;

    uint8_t DigestSha384[48u] = {0u};
    PRINTF("\t SHA2-384 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha384, g_CommonPayload, SHA384_SHA512_PAYLOAD, DigestSha384,
                                                     sizeof(DigestSha384), &hash_length),
                       SINGLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-384 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha384, g_CommonPayload, SHA384_512_PAYLOAD_MULTI, DigestSha384,
                                                     sizeof(DigestSha384), &hash_length),
                       MULTIPLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

    /* Multi-part */
    PRINTF("Multi-part (streaming) SHA:\r\n");

    PRINTF("\t SHA2-384 single block: ");
    hash_ctx ctx384;
    double setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx384, kSha384));
    double update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx384, g_CommonPayload, SHA384_SHA512_PAYLOAD, kSha384));
    double finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx384, DigestSha384, sizeof(DigestSha384), &hash_length, kSha384));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / SHA256_BLOCK);
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-384 multiple blocks: ");
    setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx384, kSha384));
    update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx384, g_CommonPayload, SHA384_512_PAYLOAD_MULTI, kSha384));
    finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx384, DigestSha384, sizeof(DigestSha384), &hash_length, kSha384));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / (SHA256_BLOCK * MULTIPLE_BLOCK));
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    return kStatus_Success;
}

status_t sha512_benchmark(void)
{
    /* One GO */
    PRINTF("One GO SHA:\r\n");
    uint32_t hash_length   = 0u;
    status_t status        = kStatus_Fail;
    status_t status_setup  = kStatus_Fail;
    status_t status_update = kStatus_Fail;
    status_t status_finish = kStatus_Fail;

    uint8_t DigestSha512[64u] = {0u};
    PRINTF("\t SHA2-512 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha512, g_CommonPayload, SHA384_SHA512_PAYLOAD, DigestSha512,
                                                     sizeof(DigestSha512), &hash_length),
                       SINGLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-512 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_hash_compute(kSha512, g_CommonPayload, SHA384_512_PAYLOAD_MULTI, DigestSha512,
                                                     sizeof(DigestSha512), &hash_length),
                       MULTIPLE_BLOCK, SHA256_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

    /* Multi-part */
    PRINTF("Multi-part (streaming) SHA:\r\n");

    PRINTF("\t SHA2-512 single block: ");
    hash_ctx ctx512;
    double setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx512, kSha512));
    double update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx512, g_CommonPayload, SHA384_SHA512_PAYLOAD, kSha512));
    double finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx512, DigestSha512, sizeof(DigestSha512), &hash_length, kSha512));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / SHA256_BLOCK);
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t SHA2-512 multiple blocks: ");
    setup_cycles = CYCLES_COUNT(status_setup = wrapper_hash_setup(&ctx512, kSha512));
    update_cycles =
        CYCLES_COUNT(status_update = wrapper_hash_update(&ctx512, g_CommonPayload, SHA384_512_PAYLOAD_MULTI, kSha512));
    finish_cycles = CYCLES_COUNT(
        status_finish = wrapper_hash_finish(&ctx512, DigestSha512, sizeof(DigestSha512), &hash_length, kSha512));
    PRINTF("%f Cycles/Byte\r\n", (setup_cycles + update_cycles + finish_cycles) / (SHA256_BLOCK * MULTIPLE_BLOCK));
    if (status_setup != kStatus_Success || status_update != kStatus_Success || status_finish != kStatus_Success)
    {
        print_failure(NULL);
    }

    return kStatus_Success;
}
