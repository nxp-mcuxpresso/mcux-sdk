/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClHash_Internal_Memory.h
 *  @brief Internal memory consumption definitions of the mcuxClHash component */

#ifndef MCUXCLHASH_INTERNAL_MEMORY_H_
#define MCUXCLHASH_INTERNAL_MEMORY_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <internal/mcuxClHash_Internal.h>

/**
 * @defgroup MCUXCLHASH_INTERNAL_WA MCUXCLHASH_INTERNAL_WA
 * @brief Workarea size constants of mcuxClHash component
 * @ingroup mcuxClHash_Internal_Constants
 * @{
 */

/**
 * @brief WaCpu buffer is used in oneshot mode to add padding to the last message block.
 * Further it is used to store the resulting hash and in case of SHA-256 an RTF.
 * Regardless of SHA-2 variant, the size requirement is dominated by block size.
 * In streaming mode WaCpu buffer is not used at all.
 * For mcuxClHash_verify and mcuxClHash_compare an extra temporary buffer of size state is used.
 */

#define MCUXCLHASH_INTERNAL_WACPU_SIZE_MIYAGUCHI_PRENEEL (1u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_MD5 (1u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1 (1u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224 (MCUXCLHASH_BLOCK_SIZE_SHA_224 + MCUXCLHASH_STATE_SIZE_SHA_224)      ///< CPU workarea consumption of SHA2-224
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256 (MCUXCLHASH_BLOCK_SIZE_SHA_256 + MCUXCLHASH_STATE_SIZE_SHA_256)      ///< CPU workarea consumption of SHA2-256
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384 (MCUXCLHASH_BLOCK_SIZE_SHA_384 + MCUXCLHASH_STATE_SIZE_SHA_384)     ///< CPU workarea consumption of SHA2-384
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512 (MCUXCLHASH_BLOCK_SIZE_SHA_512 + MCUXCLHASH_STATE_SIZE_SHA_512)     ///< CPU workarea consumption of SHA2-512
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3 (1u)

#define MCUXCLHASH_MAX(a,b) ((a) > (b) ? (a) : (b))

#define MCUXCLHASH_INTERNAL_WACPU_MAX (MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_MIYAGUCHI_PRENEEL, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_MD5, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384, \
                                      MCUXCLHASH_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512, \
                                                    MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3))))))))

/** @} */


#endif /* MCUXCLHASH_INTERNAL_MEMORY_H_ */
