/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClHashModes_Internal_Memory.h
 *  @brief Internal memory consumption definitions of the mcuxClHashModes component
 */

#ifndef MCUXCLHASHMODES_INTERNAL_MEMORY_H_
#define MCUXCLHASHMODES_INTERNAL_MEMORY_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash_Types.h>
#include <internal/mcuxClHash_Internal.h>


#ifdef __cplusplus
extern "C" {
#endif


/**********************************************
 * Block, State and Counter sizes
 **********************************************/

#define MCUXCLHASH_BLOCK_SIZE_MD5                (64U) ///< MD5 block size: MD5 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_1              (64U) ///< SHA-1 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_224            (64U) ///< SHA-224 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_256            (64U) ///< SHA-256 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_384           (128U) ///< SHA-384 block size: 1024 bit (128 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_512           (128U) ///< SHA-512 block size: 1024 bit (128 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_224          (144U) ///< SHA3-224 block size: 1152 bit (144 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_256          (136U) ///< SHA3-256 block size: 1088 bit (136 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_384          (104U) ///< SHA3-384 block size: 832 bit (104 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_512           (72U) ///< SHA3-512 block size: 576 bit (72 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_SHAKE_128    (168U) ///< SHAKE-128 block size: 1344 bit (168 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_SHAKE_256    (136U) ///< SHAKE-256 block size: 1088 bit (136 bytes)
#define MCUXCLHASH_BLOCK_SIZE_MAX               (MCUXCLHASH_BLOCK_SIZE_SHA3_SHAKE_128) ///< Maximum block size

#define MCUXCLHASH_STATE_SIZE_MD5                (16U) ///< MD5 state size: 64 bit (8 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_1              (20U) ///< SHA-1 state size: 160 bit (20 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_224            (32U) ///< SHA-224 state size: 256 bit (32 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_256            (32U) ///< SHA-256 state size: 256 bit (32 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_384            (64U) ///< SHA-384 state size: 512 bit (64 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_512            (64U) ///< SHA-512 state size: 512 bit (64 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA3               (200U) ///< SHA3 all variants state size: 1600 bits (200 bytes)
#define MCUXCLHASH_STATE_SIZE_SECSHA_1           (2U * MCUXCLHASH_STATE_SIZE_SHA_1) ///< SECSHA-1 state size: 160 bit (2*20 bytes)
#define MCUXCLHASH_STATE_SIZE_SECSHA_224         (2U * MCUXCLHASH_STATE_SIZE_SHA_224) ///< SECSHA-224 state size: 2*256 bit (2*32 bytes). Includes the mask.
#define MCUXCLHASH_STATE_SIZE_SECSHA_256         (2U * MCUXCLHASH_STATE_SIZE_SHA_256) ///< SECSHA-256 state size: 2*256 bit (2*32 bytes). Includes the mask.
#define MCUXCLHASH_STATE_SIZE_SECSHA_384         (2U * MCUXCLHASH_STATE_SIZE_SHA_384) ///< SECSHA-384 state size: 2*512 bit (2*64 bytes). Includes the mask.
#define MCUXCLHASH_STATE_SIZE_SECSHA_512         (2U * MCUXCLHASH_STATE_SIZE_SHA_512) ///< SECSHA-512 state size: 2*512 bit (2*64 bytes). Includes the mask.
#define MCUXCLHASH_STATE_SIZE_SECSHA3            (2U * MCUXCLHASH_STATE_SIZE_SHA3) ///< SECSHA3 all variants state size: 2*1600 bits (2*200 bytes). Includes the mask.
#define MCUXCLHASH_STATE_SIZE_MAX                (MCUXCLHASH_STATE_SIZE_SHA3) ///< Maximum block size

#define MCUXCLHASH_COUNTER_SIZE_MIYAGUCHI_PRENEEL   (1U) ///< Counter size for Miyaguchi Preneel, only indicates whether a block has already been processed
#define MCUXCLHASH_COUNTER_SIZE_MD5                 (8U) ///< Counter size for MD5 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_1               (8U) ///< Counter size for SHA-1 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_224             (8U) ///< Counter size for SHA-224 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_256             (8U) ///< Counter size for SHA-256 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_384            (16U) ///< Counter size for SHA-384 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_512            (16U) ///< Counter size for SHA-512 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA3               (16U) ///< Counter size for SHA3 padding
#define MCUXCLHASH_COUNTER_SIZE_MAX                (16U) ///< Maximal counter size for any supported algorithm


/**********************************************
 * Workarea sizes
 **********************************************/

/**
 * @brief WaCpu buffer is used in oneshot mode to add padding to the last message block.
 * Further it is used to store the resulting hash and in case of SHA-256 an RTF.
 * Regardless of SHA-2 variant, the size requirement is dominated by block size.
 * In streaming mode WaCpu buffer is not used at all.
 * For mcuxClHash_verify and mcuxClHash_compare an extra temporary buffer of size state is used.
 */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_MIYAGUCHI_PRENEEL (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_MD5 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224 (MCUXCLHASH_BLOCK_SIZE_SHA_224 + MCUXCLHASH_STATE_SIZE_SHA_224)      ///< CPU workarea consumption of SHA2-224
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256 (MCUXCLHASH_BLOCK_SIZE_SHA_256 + MCUXCLHASH_STATE_SIZE_SHA_256)      ///< CPU workarea consumption of SHA2-256
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384 (MCUXCLHASH_BLOCK_SIZE_SHA_384 + MCUXCLHASH_STATE_SIZE_SHA_384)     ///< CPU workarea consumption of SHA2-384
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512 (MCUXCLHASH_BLOCK_SIZE_SHA_512 + MCUXCLHASH_STATE_SIZE_SHA_512)     ///< CPU workarea consumption of SHA2-512
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA_1 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_224 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_256 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_384 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_512 (4u)

#define MCUXCLHASHMODES_MAX(a,b) ((a) > (b) ? (a) : (b))

#define MCUXCLHASHMODES_INTERNAL_WACPU_MAX (MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_MIYAGUCHI_PRENEEL, \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_MD5,         \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1,        \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224,    \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256,    \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384,    \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512,    \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3,        \
                                      MCUXCLHASHMODES_MAX(MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_256, \
                                      MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_512))))))))))

#define MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL       (sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLHASH_BLOCK_SIZE_MAX + MCUXCLHASH_STATE_SIZE_MAX)
/* TODO: CLNS-10242*/
#define MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL_NO_SECSHA       (sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLHASH_BLOCK_SIZE_SHA3_SHAKE_128 + MCUXCLHASH_STATE_SIZE_SHA3)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_INTERNAL_MEMORY_H_ */
