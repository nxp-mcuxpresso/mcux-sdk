/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CRYPTO_BENCHMARK_AES_H
#define CRYPTO_BENCHMARK_AES_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"
#include "crypto_benchmark.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t aes_ecb_benchmark(void);
status_t aes_cbc_benchmark(void);
status_t aes_cfb_benchmark(void);
status_t aes_ofb_benchmark(void);
status_t aes_ctr_benchmark(void);
status_t aes_ccm_benchmark(void);
status_t aes_gcm_benchmark(void);

status_t wrapper_aes_ecb_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *key, size_t key_length);

status_t wrapper_aes_cbc_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length);

status_t wrapper_aes_cfb_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length);

status_t wrapper_aes_ofb_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length);

status_t wrapper_aes_ctr_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *key,
                                 size_t key_length);

status_t wrapper_aes_ccm_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *aad,
                                 size_t aad_length,
                                 uint8_t *tag,
                                 size_t tag_length,
                                 const uint8_t *key,
                                 size_t key_length);

status_t wrapper_aes_gcm_compute(const uint8_t *input,
                                 size_t input_length,
                                 uint8_t *cipher,
                                 const uint8_t *iv,
                                 size_t iv_length,
                                 const uint8_t *aad,
                                 size_t aad_length,
                                 uint8_t *tag,
                                 size_t tag_length,
                                 const uint8_t *key,
                                 size_t key_length);

#if defined(CRYPTO_BENCHMARK_AES_ECB_OPAQUE) && (CRYPTO_BENCHMARK_AES_ECB_OPAQUE == 1)
status_t wrapper_aes_ecb_opaque_compute(const uint8_t *input, size_t input_length, uint8_t *cipher, uint32_t key_id);
status_t wrapper_aes_ecb_opaque_setup(void);
status_t wrapper_aes_ecb_opaque_cleanup(void);
status_t wrapper_aes_ecb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_ecb_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_ECB_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_CBC_OPAQUE) && (CRYPTO_BENCHMARK_AES_CBC_OPAQUE == 1)
status_t wrapper_aes_cbc_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id);
status_t wrapper_aes_cbc_opaque_setup(void);
status_t wrapper_aes_cbc_opaque_cleanup(void);
status_t wrapper_aes_cbc_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_cbc_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_CBC_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_CFB_OPAQUE) && (CRYPTO_BENCHMARK_AES_CFB_OPAQUE == 1)
status_t wrapper_aes_cfb_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id);
status_t wrapper_aes_cfb_opaque_setup(void);
status_t wrapper_aes_cfb_opaque_cleanup(void);
status_t wrapper_aes_cfb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_cfb_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_CFB_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_OFB_OPAQUE) && (CRYPTO_BENCHMARK_AES_OFB_OPAQUE == 1)
status_t wrapper_aes_ofb_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id);
status_t wrapper_aes_ofb_opaque_setup(void);
status_t wrapper_aes_ofb_opaque_cleanup(void);
status_t wrapper_aes_ofb_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_ofb_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_OFB_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_CTR_OPAQUE) && (CRYPTO_BENCHMARK_AES_CTR_OPAQUE == 1)
status_t wrapper_aes_ctr_opaque_compute(
    const uint8_t *input, size_t input_length, uint8_t *cipher, const uint8_t *iv, size_t iv_length, uint32_t key_id);
status_t wrapper_aes_ctr_opaque_setup(void);
status_t wrapper_aes_ctr_opaque_cleanup(void);
status_t wrapper_aes_ctr_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_ctr_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_CTR_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_CCM_OPAQUE) && (CRYPTO_BENCHMARK_AES_CCM_OPAQUE == 1)
status_t wrapper_aes_ccm_opaque_compute(const uint8_t *input,
                                        size_t input_length,
                                        uint8_t *cipher,
                                        const uint8_t *iv,
                                        size_t iv_length,
                                        const uint8_t *aad,
                                        size_t aad_length,
                                        uint8_t *tag,
                                        size_t tag_length,
                                        uint32_t key_id);
status_t wrapper_aes_ccm_opaque_setup(void);
status_t wrapper_aes_ccm_opaque_cleanup(void);
status_t wrapper_aes_ccm_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_ccm_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_CCM_OPAQUE */

#if defined(CRYPTO_BENCHMARK_AES_GCM_OPAQUE) && (CRYPTO_BENCHMARK_AES_GCM_OPAQUE == 1)
status_t wrapper_aes_gcm_opaque_compute(const uint8_t *input,
                                        size_t input_length,
                                        uint8_t *cipher,
                                        const uint8_t *iv,
                                        size_t iv_length,
                                        const uint8_t *aad,
                                        size_t aad_length,
                                        uint8_t *tag,
                                        size_t tag_length,
                                        uint32_t key_id);
status_t wrapper_aes_gcm_opaque_setup(void);
status_t wrapper_aes_gcm_opaque_cleanup(void);
status_t wrapper_aes_gcm_opaque_key_generate(uint16_t key_size, uint32_t *aes_key_id);
status_t wrapper_aes_gcm_opaque_key_delete(uint32_t aes_key_id);
#endif /* CRYPTO_BENCHMARK_AES_GCM_OPAQUE */

/*******************************************************************************
 * Variables
 ******************************************************************************/

#endif /* CRYPTO_BENCHMARK_AES_H */
