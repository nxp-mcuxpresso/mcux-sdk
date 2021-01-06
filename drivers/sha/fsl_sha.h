/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SHA_H_
#define _FSL_SHA_H_

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
/*@{*/
/*! @brief Defines LPC SHA driver version 2.2.2.
 *
 * Current version: 2.2.2
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
 */
#define FSL_SHA_DRIVER_VERSION (MAKE_VERSION(2, 2, 2))
/*@}*/

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
 * @param manual 0 use nonblocking MEMADDR, MEMCRL (pseudo-DMA), 1 - manual load
 * @return Status of the hash update operation
 */
status_t SHA_Update(SHA_Type *base, sha_ctx_t *ctx, const uint8_t *message, size_t messageSize, bool manual);

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

#endif /* _FSL_SHA_H_ */
