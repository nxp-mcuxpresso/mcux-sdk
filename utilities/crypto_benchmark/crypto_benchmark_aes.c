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
#include "crypto_benchmark_aes.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AES_BLOCK   16u /* AES block is 16 Bytes (128bit) */
#define AES_PAYLOAD 16u /* To be generic and support any kind of padding (including no padding),
                         * the payload is set to the block size. With various padding schemes
                         * this may cause cipher calculation to be done on one block more
                         * than SINGLE_BLOCK or MULTIPLE_BLOCK, but this will only cause small
                         * differences in the benchmarking. */
#define AES_PAYLOAD_MULTI (AES_PAYLOAD * MULTIPLE_BLOCK) /* Multi-block */

#define AES_128_KEY_SIZE 16u
#define AES_192_KEY_SIZE 24u
#define AES_256_KEY_SIZE 32u

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t aes_ecb_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-ECB:\r\n");
    uint8_t key[AES_256_KEY_SIZE] = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-ECB-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD,
                                                                              g_CommonOutput, key, AES_128_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD_MULTI,
                                                                              g_CommonOutput, key, AES_128_KEY_SIZE),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-ECB-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD,
                                                                              g_CommonOutput, key, AES_192_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD_MULTI,
                                                                              g_CommonOutput, key, AES_192_KEY_SIZE),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-ECB-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD,
                                                                              g_CommonOutput, key, AES_256_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_compute(g_CommonPayload, AES_PAYLOAD_MULTI,
                                                                              g_CommonOutput, key, AES_256_KEY_SIZE),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

#if defined(CRYPTO_BENCHMARK_AES_ECB_OPAQUE) && (CRYPTO_BENCHMARK_AES_ECB_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-ECB Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_ecb_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_ecb_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 128 key generate");
    }

    PRINTF("\t AES-ECB-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ecb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_ecb_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 192 key generate");
    }

    PRINTF("\t AES-ECB-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ecb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_ecb_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 256 key generate");
    }

    PRINTF("\t AES-ECB-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-ECB-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ecb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ecb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES ECB 256 key delete");
    }

    status = wrapper_aes_ecb_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES ECB opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_ECB_OPAQUE */
    return kStatus_Success;
}

status_t aes_cbc_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-CBC:\r\n");
    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t iv[AES_BLOCK]         = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-CBC-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_128_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-CBC-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_192_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-CBC-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_256_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cbc_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

#if defined(CRYPTO_BENCHMARK_AES_CBC_OPAQUE) && (CRYPTO_BENCHMARK_AES_CBC_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-CBC Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_cbc_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_cbc_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 128 key generate");
    }

    PRINTF("\t AES-CBC-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cbc_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_cbc_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 192 key generate");
    }

    PRINTF("\t AES-CBC-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cbc_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_cbc_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 256 key generate");
    }

    PRINTF("\t AES-CBC-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CBC-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cbc_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cbc_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CBC 256 key delete");
    }

    status = wrapper_aes_cbc_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES CBC opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_CBC_OPAQUE */
    return kStatus_Success;
}

status_t aes_cfb_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-CFB:\r\n");
    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t iv[AES_BLOCK]         = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-CFB-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_128_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-CFB-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_192_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-CFB-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_256_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_cfb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

#if defined(CRYPTO_BENCHMARK_AES_CFB_OPAQUE) && (CRYPTO_BENCHMARK_AES_CFB_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-CFB Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_cfb_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_cfb_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 128 key generate");
    }

    PRINTF("\t AES-CFB-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cfb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_cfb_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 192 key generate");
    }

    PRINTF("\t AES-CFB-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cfb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_cfb_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 256 key generate");
    }

    PRINTF("\t AES-CFB-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CFB-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_cfb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_cfb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CFB 256 key delete");
    }

    status = wrapper_aes_cfb_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES CFB opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_CFB_OPAQUE */
    return kStatus_Success;
}

status_t aes_ofb_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-OFB:\r\n");
    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t iv[AES_BLOCK]         = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-OFB-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_128_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-OFB-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_192_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-OFB-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_256_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ofb_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

#if defined(CRYPTO_BENCHMARK_AES_OFB_OPAQUE) && (CRYPTO_BENCHMARK_AES_OFB_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-OFB Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_ofb_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_ofb_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 128 key generate");
    }

    PRINTF("\t AES-OFB-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ofb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_ofb_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 192 key generate");
    }

    PRINTF("\t AES-OFB-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ofb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_ofb_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 256 key generate");
    }

    PRINTF("\t AES-OFB-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-OFB-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ofb_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ofb_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES OFB 256 key delete");
    }

    status = wrapper_aes_ofb_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES OFB opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_OFB_OPAQUE */
    return kStatus_Success;
}

status_t aes_ctr_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-CTR:\r\n");
    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t iv[AES_BLOCK]         = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-CTR-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_128_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-CTR-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_192_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-CTR-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD, g_CommonOutput, iv, sizeof(iv),
                                                        key, AES_256_KEY_SIZE),
                       SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ctr_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, iv,
                                                        sizeof(iv), key, AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\r\n");

#if defined(CRYPTO_BENCHMARK_AES_CTR_OPAQUE) && (CRYPTO_BENCHMARK_AES_CTR_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-CTR Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_ctr_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_ctr_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 128 key generate");
    }

    PRINTF("\t AES-CTR-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ctr_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_ctr_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 192 key generate");
    }

    PRINTF("\t AES-CTR-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ctr_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_ctr_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 256 key generate");
    }

    PRINTF("\t AES-CTR-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, iv, sizeof(iv), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CTR-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ctr_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, iv, sizeof(iv), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ctr_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CTR 256 key delete");
    }

    status = wrapper_aes_ctr_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES CTR opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_CTR_OPAQUE */
    return kStatus_Success;
}

status_t aes_ccm_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-CCM:\r\n");

    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t aad[AES_PAYLOAD]      = {0u};
    uint8_t nonce[12u]            = {0u};
    uint8_t tag[16u]              = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-CCM-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_128_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ccm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-CCM-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_192_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ccm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-CCM-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_256_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_ccm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

#if defined(CRYPTO_BENCHMARK_AES_CCM_OPAQUE) && (CRYPTO_BENCHMARK_AES_CCM_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-CCM Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_ccm_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_ccm_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 128 key generate");
    }

    PRINTF("\t AES-CCM-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                     aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ccm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_ccm_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 192 key generate");
    }

    PRINTF("\t AES-CCM-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload,
                                                                                    AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                    aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ccm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_ccm_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 256 key generate");
    }

    PRINTF("\t AES-CCM-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-CCM-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_ccm_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                     aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_ccm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES CCM 256 key delete");
    }

    status = wrapper_aes_ccm_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES CCM opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_CCM_OPAQUE */
    return kStatus_Success;
}

status_t aes_gcm_benchmark(void)
{
    /* One GO */
    PRINTF("One GO AES-GCM:\r\n");

    uint8_t key[AES_256_KEY_SIZE] = {0u};
    uint8_t aad[AES_PAYLOAD]      = {0u};
    uint8_t nonce[12u]            = {0u};
    uint8_t tag[16u]              = {0u};
    status_t status               = kStatus_Fail;

    /* 128-bit key */
    PRINTF("\t AES-GCM-128 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_128_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-128 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_gcm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_128_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 192-bit key */
    PRINTF("\t AES-GCM-192 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_192_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-192 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_gcm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_192_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 256-bit key */
    PRINTF("\t AES-GCM-256 single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_compute(
                                                 g_CommonPayload, AES_PAYLOAD, g_CommonOutput, nonce, sizeof(nonce),
                                                 aad, sizeof(aad), tag, sizeof(tag), key, AES_256_KEY_SIZE),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-256 multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n",
           CYCLES_BYTE(status = wrapper_aes_gcm_compute(g_CommonPayload, AES_PAYLOAD_MULTI, g_CommonOutput, nonce,
                                                        sizeof(nonce), aad, sizeof(aad), tag, sizeof(tag), key,
                                                        AES_256_KEY_SIZE),
                       MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

#if defined(CRYPTO_BENCHMARK_AES_GCM_OPAQUE) && (CRYPTO_BENCHMARK_AES_GCM_OPAQUE == 1)
    /* One GO Opaque */
    PRINTF("One GO AES-GCM Opaque:\r\n");
    uint32_t key_id = 0u;

    /* Opaque setup */
    status = wrapper_aes_gcm_opaque_setup();
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    /* 128-bit key */
    status = wrapper_aes_gcm_opaque_key_generate(BYTES_TO_BITS(AES_128_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 128 key generate");
    }

    PRINTF("\t AES-GCM-128 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-128 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload,
                                                                                    AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                    aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_gcm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 128 key delete");
    }

    /* 192-bit key */
    status = wrapper_aes_gcm_opaque_key_generate(BYTES_TO_BITS(AES_192_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 192 key generate");
    }

    PRINTF("\t AES-GCM-192 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-192 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                     aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_gcm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 192 key delete");
    }

    /* 256-bit key */
    status = wrapper_aes_gcm_opaque_key_generate(BYTES_TO_BITS(AES_256_KEY_SIZE), &key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 256 key generate");
    }

    PRINTF("\t AES-GCM-256 Opaque single block: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload, AES_PAYLOAD,
                                                                                     g_CommonOutput, nonce, sizeof(nonce), aad, sizeof(aad),
                                                                                     tag, sizeof(tag), key_id),
                                             SINGLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    PRINTF("\t AES-GCM-256 Opaque multiple blocks: ");
    PRINTF("%f Cycles/Byte\r\n", CYCLES_BYTE(status = wrapper_aes_gcm_opaque_compute(g_CommonPayload,
                                                                                     AES_PAYLOAD_MULTI, g_CommonOutput, nonce, sizeof(nonce),
                                                                                     aad, sizeof(aad), tag, sizeof(tag), key_id),
                                             MULTIPLE_BLOCK, AES_BLOCK));
    if (status != kStatus_Success)
    {
        print_failure(NULL);
    }

    status = wrapper_aes_gcm_opaque_key_delete(key_id);
    if (status != kStatus_Success)
    {
        print_failure("AES GCM 256 key delete");
    }

    status = wrapper_aes_gcm_opaque_cleanup();
    if (status != kStatus_Success)
    {
        print_failure("AES GCM opaque cleanup");
    }
#endif /* CRYPTO_BENCHMARK_AES_GCM_OPAQUE */
    return kStatus_Success;
}
