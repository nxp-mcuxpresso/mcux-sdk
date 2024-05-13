/*
 *  Benchmark demonstration program
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *  Copyright 2017, 2021-2023 NXP. Not a Contribution
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "crypto_benchmark.h"
#include "app.h"

#if defined(CRYPTO_BENCHMARK_SHA1) || defined(CRYPTO_BENCHMARK_SHA224) || defined(CRYPTO_BENCHMARK_SHA256) || \
    defined(CRYPTO_BENCHMARK_SHA384) || defined(CRYPTO_BENCHMARK_SHA512)
#include "crypto_benchmark_hash.h"
#endif
#if defined(CRYPTO_BENCHMARK_HMAC) || defined(CRYPTO_BENCHMARK_CMAC)
#include "crypto_benchmark_mac.h"
#endif
#if defined(CRYPTO_BENCHMARK_AES_ECB) || defined(CRYPTO_BENCHMARK_AES_CTR) || defined(CRYPTO_BENCHMARK_AES_CBC) || \
    defined(CRYPTO_BENCHMARK_AES_CFB) || defined(CRYPTO_BENCHMARK_AES_OFB) || defined(CRYPTO_BENCHMARK_AES_CCM) || \
    defined(CRYPTO_BENCHMARK_AES_GCM)
#include "crypto_benchmark_aes.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern status_t CRYPTO_InitHardware(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
DATA_AT_SECTION(uint8_t g_CommonPayload[COMMON_PAYLOAD_SIZE], DATA_LOCATION);
DATA_AT_SECTION(uint8_t g_CommonOutput[COMMON_OUTPUT_SIZE], DATA_LOCATION);

const testcases_t testcases[] = {
#if defined(CRYPTO_BENCHMARK_SHA1)
    {"sha1", sha1_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_SHA224)
    {"sha224", sha224_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_SHA256)
    {"sha256", sha256_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_SHA384)
    {"sha384", sha384_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_SHA512)
    {"sha512", sha512_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_ECB)
    {"aes_ecb", aes_ecb_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_GCM)
    {"aes_gcm", aes_gcm_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_CCM)
    {"aes_ccm", aes_ccm_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_CTR)
    {"aes_ctr", aes_ctr_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_CBC)
    {"aes_cbc", aes_cbc_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_CFB)
    {"aes_cfb", aes_cfb_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_AES_OFB)
    {"aes_ofb", aes_ofb_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_HMAC_SHA224) || defined(CRYPTO_BENCHMARK_HMAC_SHA224_OPAQUE)
    {"hmac_sha224", hmac_sha224_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_HMAC_SHA256) || defined(CRYPTO_BENCHMARK_HMAC_SHA256_OPAQUE)
    {"hmac_sha256", hmac_sha256_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_HMAC_SHA384) || defined(CRYPTO_BENCHMARK_HMAC_SHA384_OPAQUE)
    {"hmac_sha384", hmac_sha384_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_HMAC_SHA512) || defined(CRYPTO_BENCHMARK_HMAC_SHA512_OPAQUE)
    {"hmac_sha512", hmac_sha512_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_CMAC)
    {"cmac", cmac_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_RSA)
    {"rsa", rsa_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_CTR_DRBG)
    {"ctr_drbg", ctr_drbg_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_HMAC_DRBG)
    {"hmac_drbg", hmac_drbg_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_ECC)
    {"ecc", ecp_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_ENTROPY)
    {"entropy", entropy_benchmark},
#endif
#if defined(CRYPTO_BENCHMARK_ECDH)
    {"ecdh", ecdh_benchmark},
#endif
    {NULL, NULL}};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Milliseconds counter since last POR/reset.
 */
void SysTick_Handler(void)
{
    s_MsCount++;
}

uint64_t benchmark_timing_hardclock(void)
{
    uint32_t currMsCount;
    uint32_t currTick;
    uint32_t loadTick;

    do
    {
        currMsCount = s_MsCount;
        currTick    = SysTick->VAL;
    } while (currMsCount != s_MsCount);

    loadTick = CLOCK_GetCoreSysClkFreq() / 1000U;
    return (((uint64_t)currMsCount) * loadTick) + loadTick - currTick;
}

void benchmark_mbedtls_set_alarm(int seconds)
{
    benchmark_mbedtls_timing_alarmed = 0;
    s_Timeout                        = benchmark_timing_hardclock() + (seconds * CLOCK_GetCoreSysClkFreq());
}

void benchmark_mbedtls_poll_alarm(void)
{
    if (benchmark_timing_hardclock() > s_Timeout)
    {
        benchmark_mbedtls_timing_alarmed = 1;
    }
}

void print_failure(const char *additional_message)
{
    PRINTF("BENCHMARK FAILURE %s\r\n", additional_message != NULL ? additional_message : "");
}

int main(int argc, char *argv[])
{
    const testcases_t *test;
    /* HW init */
    BOARD_InitHardware();

    CRYPTO_InitHardware();

    /* Init SysTick module */
    /* call CMSIS SysTick function. It enables the SysTick interrupt at low priority */
    SysTick_Config(CLOCK_GetCoreSysClkFreq() / 1000U); /* 1 ms period */

    /* Run all the tests */
    for (test = testcases; test->name != NULL; test++)
    {
        PRINTF("Test case: %s\r\n", test->name);
        test->function();
        PRINTF("\n");
    }

    PRINTF("\n");

    while (1)
    {
        char ch = GETCHAR();
        PUTCHAR(ch);
    }
}
