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

#ifndef CRYPTO_BENCHMARK_H
#define CRYPTO_BENCHMARK_H

#include "fsl_common.h"

#if defined(BENCHMARK_PLATFORM_CONFIG)
#include "benchmark_platform_config.h"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint64_t benchmark_timing_hardclock(void);
void benchmark_mbedtls_set_alarm(int seconds);
void benchmark_mbedtls_poll_alarm(void);
void print_failure(const char *additional_message);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SINGLE_BLOCK   1u
#define MULTIPLE_BLOCK 512u

#define DATA_AT_SECTION(var, section) var @"section"

#define BYTES_TO_BITS(bytes) (bytes * 8u)

#define LARGEST_INPUT_BLOCK_SIZE  (128u) /* SHA512 */
#define LARGEST_OUTPUT_BLOCK_SIZE (64u)  /* ChaCha20-Poly1305 */
#define COMMON_PAYLOAD_SIZE       (LARGEST_INPUT_BLOCK_SIZE * MULTIPLE_BLOCK) /* A large enough size for the common input buffer */
#define COMMON_OUTPUT_SIZE        (LARGEST_OUTPUT_BLOCK_SIZE * MULTIPLE_BLOCK) /* A large enough size for the common output buffer */

/* Keystore and opaque cipher related defines */
#define KEYSTORE_ID    0x12345678u
#define KEYSTORE_NONCE 0xabcdef12u

/** @brief Common input payload buffer for various algorithms */
DATA_AT_SECTION(extern uint8_t g_CommonPayload[COMMON_PAYLOAD_SIZE], DATA_LOCATION);

/** @brief Common output buffer for various algorithms */
DATA_AT_SECTION(extern uint8_t g_CommonOutput[COMMON_OUTPUT_SIZE], DATA_LOCATION);

/** Macro function adapted from existing mbedtls benchmark */
#define CYCLES_BYTE(CODE, BLOCK_AMOUNT, BLOCK_SIZE)                                                   \
    ({                                                                                                \
        uint32_t jj;                                                                                  \
        uint64_t tsc1;                                                                                \
        tsc1 = benchmark_timing_hardclock();                                                          \
        for (jj = 0U; jj < 1024U; ++jj)                                                               \
        {                                                                                             \
            CODE;                                                                                     \
        }                                                                                             \
        (double)((float)(benchmark_timing_hardclock() - tsc1) / (1024U * BLOCK_SIZE * BLOCK_AMOUNT)); \
    })

/** Macro function adapted from existing mbedtls benchmark */
#define KB_S(CODE, BLOCK_AMOUNT, BLOCK_SIZE)                                                                      \
    ({                                                                                                            \
        uint64_t ii;                                                                                              \
        uint64_t tsc1;                                                                                            \
        uint64_t tsc2;                                                                                            \
        benchmark_set_alarm(0x1U); /* Measure only 1 second  (KB/s) */                                            \
        tsc1 = benchmark_timing_hardclock();                                                                      \
        for (ii = 1U; !g_BenchmarkTimingAlarmed; ++ii)                                                            \
        {                                                                                                         \
            CODE;                                                                                                 \
            benchmark_poll_alarm();                                                                               \
        }                                                                                                         \
        tsc2 = benchmark_timing_hardclock();                                                                      \
        (double)((ii * BLOCK_SIZE * BLOCK_AMOUNT / 1024) / (((float)(tsc2 - tsc1)) / CLOCK_GetCoreSysClkFreq())); \
    })

/* Provide absolut cycle count of executed CODE */
#define CYCLES_COUNT(CODE)                   \
    ({                                       \
        uint64_t tsc1, tsc2;                 \
        tsc1 = benchmark_timing_hardclock(); \
        CODE;                                \
        tsc2 = benchmark_timing_hardclock(); \
                                             \
        (double)(tsc2 - tsc1);               \
    })

/* Provide cycles count for single CODE execution during given time */
#define CYCLES_COUNT_TIME(CODE, SEC)                                     \
    do                                                                   \
    {                                                                    \
        uint32_t ii;                                                     \
        uint64_t tsc1, tsc2;                                             \
        int ret;                                                         \
        benchmark_mbedtls_set_alarm(SEC);                                \
                                                                         \
        ret  = 0;                                                        \
        tsc1 = benchmark_timing_hardclock();                             \
                                                                         \
        for (ii = 1; !benchmark_mbedtls_timing_alarmed && !ret; ii++)    \
        {                                                                \
            ret = CODE;                                                  \
            benchmark_mbedtls_poll_alarm();                              \
        }                                                                \
                                                                         \
        tsc2 = benchmark_timing_hardclock();                             \
                                                                         \
        PRINTF("%6.2f CYCLES", (double)(((tsc2 - tsc1) / ((float)ii)))); \
        PRINTF("\r\n");                                                  \
                                                                         \
    } while (0)

/* Provide cycle count for single CODE execution with given ITERATIONS of execution */
#define CYCLES_COUNT_ITER(CODE, ITERATIONS)                              \
    ({                                                                   \
        uint32_t ii;                                                     \
        uint64_t tsc1, tsc2;                                             \
        int ret;                                                         \
        benchmark_mbedtls_set_alarm(3);                                  \
                                                                         \
        ret  = 0;                                                        \
        tsc1 = benchmark_timing_hardclock();                             \
                                                                         \
        for (ii = 0; ii < ITERATIONS && !ret; ii++)                      \
        {                                                                \
            ret = CODE;                                                  \
        }                                                                \
                                                                         \
        tsc2 = benchmark_timing_hardclock();                             \
                                                                         \
        PRINTF("%6.2f CYCLES", (double)(((tsc2 - tsc1) / ((float)ii)))); \
        PRINTF("\r\n");                                                  \
        })


/* Provide time spent in single code execution in seconds */
#define TIME_TOTAL(CODE)                                                                                    \
    ({                                                                                                      \
        uint64_t tsc;                                                                                       \
        tsc = benchmark_timing_hardclock();                                                                 \
        CODE;                                                                                               \
       (double)((benchmark_timing_hardclock() - tsc) / CLOCK_GetCoreSysClkFreq());                          \
    })

/* Provide time spent in single code execution in micro seconds */
#define TIME_TOTAL_USEC(CODE)                                                                               \
    ({                                                                                                      \
        uint64_t tsc;                                                                                       \
        tsc = benchmark_timing_hardclock();                                                                 \
        CODE;                                                                                               \
       (double)((double)(benchmark_timing_hardclock() - tsc) / (double)CLOCK_GetCoreSysClkFreq()) * 1000000;\
    })

/* Provide time spent in single code execution, measured during given iterations in sec */
#define TIME_TOTAL_ITER(CODE, ITERATIONS)                                                                   \
    ({                                                                                                      \
        uint32_t ii;                                                                                        \
        uint64_t tsc;                                                                                       \
                                                                                                            \
        tsc = benchmark_timing_hardclock();                                                                 \
        for (ii = 0; < ITERATIONS; ii++)                                                                    \
        {                                                                                                   \
            CODE;                                                                                           \
        }                                                                                                   \
                                                                                                            \
       (double)(((benchmark_timing_hardclock() - tsc) / (float)ii ) / CLOCK_GetCoreSysClkFreq());           \
    })


/* Provide time spent in single code execution, measured during given period of time (5s by default) */
#define TIME_TOTAL_INTERVAL(CODE)                                                                           \
    do                                                                                                      \
    {                                                                                                       \
        uint32_t ii;                                                                                        \
        uint64_t tsc;                                                                                       \
        int ret;                                                                                            \
        benchmark_mbedtls_set_alarm(5);                                                                     \
                                                                                                            \
        ret = 0;                                                                                            \
        tsc = benchmark_timing_hardclock();                                                                 \
        for (ii = 1; !benchmark_mbedtls_timing_alarmed && !ret; ii++)                                       \
        {                                                                                                   \
            CODE;                                                                                           \
            benchmark_mbedtls_poll_alarm();                                                                 \
        }                                                                                                   \
                                                                                                            \
        PRINTF("%6.2f /s",                                                                                  \
               (double)(((float)ii) / ((benchmark_timing_hardclock() - tsc) / CLOCK_GetCoreSysClkFreq()))); \
        PRINTF("\r\n");                                                                                     \
                                                                                                            \
    } while (0)

typedef struct
{
    const char *name;
    int (*function)(void);
} testcases_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile uint32_t s_MsCount = 0U;
static volatile int benchmark_mbedtls_timing_alarmed;
static uint64_t s_Timeout;

#endif /* CRYPTO_BENCHMARK_H */
