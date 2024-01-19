/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_SHA_H_
#define FSL_SHA_H_

#include "fsl_common.h"
/*!
 * @addtogroup sha
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Defines LPC SHA driver version 2.3.2.
 *
 * Current version: 2.3.2
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 * - Version 2.1.0
 *   - Updated "sha_ldm_stm_16_words" "sha_one_block" API to match QN9090. QN9090 has no ALIAS register.
 *   - Added "SHA_ClkInit" "SHA_ClkInit"
 * - Version 2.1.1
 *   - MISRA C-2012 issue fixed: rule 10.3, 10.4, 11.9, 14.4, 16.4 and 17.7.
 * - Version 2.2.0
 *   - Support MEMADDR pseudo DMA for loading input data in SHA_Update function (LPCXpresso54018 and LPCXpresso54628).
 * - Version 2.2.1
 *   - MISRA C-2012 issue fix.
 * - Version 2.2.2
 *   Modified SHA_Finish function. While using pseudo DMA with maximum optimization, compiler optimize out condition.
 *   Which caused block in this function and did not check state, which has been set in interrupt.
 * - Version 2.3.0
 *	 Modified SHA_Update to use blocking version of AHB Master mode when its available on chip. Added
 *SHA_UpdateNonBlocking() function which uses nonblocking AHB Master mode. Fixed incorrect calculation of SHA when
 *calling SHA_Update multiple times when is CPU used to load data. Added Reset into SHA_ClkInit and SHA_ClkDeinit
 *function.
 * - Version 2.3.1
 *	 Modified sha_process_message_data_master() to ensure that MEMCTRL will be written within 64 cycles of writing last
 *word to INDATA as is mentioned in errata, even with different optimization levels.
 * - Version 2.3.2
 *   Add -O2 optimization for GCC to sha_process_message_data_master(), because without it the function hangs under some
 *conditions.
 */
#define FSL_SHA_DRIVER_VERSION (MAKE_VERSION(2, 3, 2))
/*! @} */

/*! Supported cryptographic block cipher functions for HASH creation */
typedef enum _sha_algo_t
{
    kSHA_Sha1,   /*!< SHA_1 */
    kSHA_Sha256, /*!< SHA_256  */
} sha_algo_t;

/*! @brief SHA Context size. */
#define SHA_CTX_SIZE 22U

/*! @brief Storage type used to save hash context. */
typedef struct _sha_ctx_t
{
    uint32_t x[SHA_CTX_SIZE];
} sha_ctx_t;

/*! @brief background hash callback function. */
typedef void (*sha_callback_t)(SHA_Type *base, sha_ctx_t *ctx, status_t status, void *userData);

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name SHA Functional Operation
 * @{
 */

/*!
 * @addtogroup sha_algorithm_level_api
 * @{
 */
/*!
 * @brief Initialize HASH context
 *
 * This function initializes new hash context.
 *
 * @param base SHA peripheral base address
 * @param[out] ctx Output hash context
 * @param algo Underlaying algorithm to use for hash computation. Either SHA-1 or SHA-256.
 * @return Status of initialization
 */
status_t SHA_Init(SHA_Type *base, sha_ctx_t *ctx, sha_algo_t algo);

/*!
 * @brief Add data to current HASH
 *
 * Add data to current HASH. This can be called repeatedly with an arbitrary amount of data to be
 * hashed.
 *
 * @param base SHA peripheral base address
 * @param[in,out] ctx HASH context
 * @param message Input message
 * @param messageSize Size of input message in bytes
 * @return Status of the hash update operation
 */
status_t SHA_Update(SHA_Type *base, sha_ctx_t *ctx, const uint8_t *message, size_t messageSize);

/*!
 * @brief Finalize hashing
 *
 * Outputs the final hash and erases the context. SHA-1 or SHA-256 padding bits are automatically added by this
 * function.
 *
 * @param base SHA peripheral base address
 * @param[in,out] ctx HASH context
 * @param[out] output Output hash data
 * @param[in,out] outputSize On input, determines the size of bytes of the output array. On output, tells how many bytes
 * have been written to output.
 * @return Status of the hash finish operation
 */
status_t SHA_Finish(SHA_Type *base, sha_ctx_t *ctx, uint8_t *output, size_t *outputSize);

#if defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0)
/*!
 * @brief Initializes the SHA handle for background hashing.
 *
 * This function initializes the hash context for background hashing
 * (Non-blocking) APIs. This is less typical interface to hash function, but can be used
 * for parallel processing, when main CPU has something else to do.
 * Example is digital signature RSASSA-PKCS1-V1_5-VERIFY((n,e),M,S) algorithm, where
 * background hashing of M can be started, then CPU can compute S^e mod n
 * (in parallel with background hashing) and once the digest becomes available,
 * CPU can proceed to comparison of EM with EM'.
 *
 * @param base SHA peripheral base address.
 * @param[out] ctx Hash context.
 * @param callback Callback function.
 * @param userData User data (to be passed as an argument to callback function, once callback is invoked from isr).
 */
void SHA_SetCallback(SHA_Type *base, sha_ctx_t *ctx, sha_callback_t callback, void *userData);

/*!
 * @brief Create running hash on given data.
 *
 * Configures the SHA to compute new running hash as AHB master
 * and returns immediately. SHA AHB Master mode supports only aligned \p input
 * address and can be called only once per continuous block of data. Every call to this function
 * must be preceded with SHA_Init() and finished with _SHA_Finish().
 * Once callback function is invoked by SHA isr, it should set a flag
 * for the main application to finalize the hashing (padding) and to read out the final digest
 * by calling SHA_Finish().
 *
 * @param base SHA peripheral base address
 * @param ctx Specifies callback. Last incomplete 512-bit block of the input is copied into clear buffer for padding.
 * @param input 32-bit word aligned pointer to Input data.
 * @param inputSize Size of input data in bytes (must be word aligned)
 * @return Status of the hash update operation.
 */
status_t SHA_UpdateNonBlocking(SHA_Type *base, sha_ctx_t *ctx, const uint8_t *input, size_t inputSize);
#endif /* defined(FSL_FEATURE_SHA_HAS_MEMADDR_DMA) && (FSL_FEATURE_SHA_HAS_MEMADDR_DMA > 0) */

/*!
 * @brief Start SHA clock
 *
 * Start SHA clock
 *
 * @param base SHA peripheral base address
 *
 */
void SHA_ClkInit(SHA_Type *base);

/*!
 * @brief Stop SHA clock
 *
 * Stop SHA clock
 *
 * @param base SHA peripheral base address
 *
 */
void SHA_ClkDeinit(SHA_Type *base);

/*!
 *@}
 */ /* sha_algorithm_level_api */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @}*/
/*! @}*/ /* end of group sha */

#endif   /* FSL_SHA_H_ */
