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
#include <mcuxClCore_Macros.h>
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
#define MCUXCLHASH_STATE_SIZE_SECSHA_1           (2U * MCUXCLHASH_STATE_SIZE_SHA_1) ///< SECSHA-1 state size: 2*160 bit (2*20 bytes). Includes the mask.
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
 * Checked input sizes
 **********************************************/

/**
 * @brief Check processed length mask is used to detect when the maximum input size to a hash function has been exceeded.
 * Specifically, SHA-1 and SHA-2 cannot exceed processing 2^64 and 2^128 _bits_ of input.
 * Therefore, a mask of the 3 highest bits of the highest byte of the counter is sufficient to check if this has occurred.
 * Checks are performed only in the multipart variants, in mcuxClHash_process/mcuxClHash_finish and mcuxClHash_import_state.
 */

#define MCUXCLHASH_PROCESSED_LENGTH_NO_LIMIT                        (0x0u)  ///< Mask of the highest bits in the processed counter when a hash function has no limit regarding the input size.
#define MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_SHA1                 (0xE0u) ///< Mask of the highest bits in the processed counter that should not be set for SHA-1.
#define MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_SHA2                 (0xE0u) ///< Mask of the highest bits in the processed counter that should not be set for SHA-2.
#define MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_MD5                  (MCUXCLHASH_PROCESSED_LENGTH_NO_LIMIT) ///< Mask of the highest bits in the processed counter that should not be set for MD5.
#define MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_SHA3                 (MCUXCLHASH_PROCESSED_LENGTH_NO_LIMIT) ///< Mask of the highest bits in the processed counter that should not be set for SHA-3.
#define MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_MIYAGUCHI_PRENEEL    (MCUXCLHASH_PROCESSED_LENGTH_NO_LIMIT) ///< Mask of the highest bits in the processed counter that should not be set for Miyaguchi-Preneel.

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
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1 (MCUXCLHASH_BLOCK_SIZE_SHA_1 + MCUXCLHASH_STATE_SIZE_SHA_1 * 2u)   ///< CPU workarea consumption of SHA-1
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224 (MCUXCLHASH_BLOCK_SIZE_SHA_224 + MCUXCLHASH_STATE_SIZE_SHA_224)      ///< CPU workarea consumption of SHA2-224
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224_NONBLOCKING (4u)      ///< CPU workarea consumption of SHA2-224
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256 (MCUXCLHASH_BLOCK_SIZE_SHA_256 + MCUXCLHASH_STATE_SIZE_SHA_256)      ///< CPU workarea consumption of SHA2-256
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256_NONBLOCKING (4u)      ///< CPU workarea consumption of SHA2-256
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384 (MCUXCLHASH_BLOCK_SIZE_SHA_384 + MCUXCLHASH_STATE_SIZE_SHA_384)     ///< CPU workarea consumption of SHA2-384
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384_NONBLOCKING (4u)     ///< CPU workarea consumption of SHA2-384
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512 (MCUXCLHASH_BLOCK_SIZE_SHA_512 + MCUXCLHASH_STATE_SIZE_SHA_512)     ///< CPU workarea consumption of SHA2-512
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512_NONBLOCKING (4u)     ///< CPU workarea consumption of SHA2-512

/* Work area size for the C implementation of SHA-3 */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_C_SHA3 (4u)

/* Work area sizes for SHA-3 non-blocking with the LTC coprocessor */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3_NONBLOCKING (4u)

/* Work area sizes for SHA-3 blocking with the LTC coprocessor */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3_BLOCKING (4u) /* Sha3 blocking with LTC does not need the CPU WA*/

/* Work area sizes for SHA-3 with the LTC coprocessor (without DMA) */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_SHA3 (4u) /* Sha3 with LTC does not need the CPU WA*/

/* Work area size for the C implementation of Shake */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_C_SHAKE (4u)

/* Work area size for Shake with the LTC coprocessor */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_SHAKE (4u) /* Shake with LTC does not need the CPU WA*/

/* Work area size for CShake with the LTC coprocessor */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_CSHAKE (4u)
typedef union
{
    uint8_t mcuxClHash_Internal_WaCpu_Size_C_Sha3[MCUXCLHASH_INTERNAL_WACPU_SIZE_C_SHA3];
    uint8_t mcuxClHash_Internal_WaCpu_Size_LTC_Sha3[MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_SHA3];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha3_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3_NONBLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha3_Blocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3_BLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_C_Shake[MCUXCLHASH_INTERNAL_WACPU_SIZE_C_SHAKE];
    uint8_t mcuxClHash_Internal_WaCpu_Size_LTC_Shake[MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_SHAKE];
    uint8_t mcuxClHash_Internal_WaCpu_Size_LTC_CShake[MCUXCLHASH_INTERNAL_WACPU_SIZE_LTC_CSHAKE];
} mcuxClHashModes_Internal_MaxUnion_Sha3Shake_CpuWa_t;

#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3 (sizeof(mcuxClHashModes_Internal_MaxUnion_Sha3Shake_CpuWa_t))


/* Work area size for SecSha-1 */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA_1 (4u)

/* Work area sizes for SecSha-2 */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_224 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_256 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_384 (4u)
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_512 (4u)

/* Work area size for SecSha-3 */
#define MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA3 (4u)

/*
 * A union is used here to determine the maximum size of the cpu wa. This type is NOT intended to be used in the code.
 * Usage of nested MAX is not possible here as the evaluated lines getting too long for the build system.
 */
typedef union
{
    uint8_t mcuxClHash_Internal_WaCpu_Size_Miyaguchi_Preneel[MCUXCLHASH_INTERNAL_WACPU_SIZE_MIYAGUCHI_PRENEEL];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Md5[MCUXCLHASH_INTERNAL_WACPU_SIZE_MD5];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha1[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA1];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_224[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_256[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_384[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_512[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha3[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3];
    uint8_t mcuxClHash_Internal_WaCpu_Size_SecSha2_256[MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_256];
    uint8_t mcuxClHash_Internal_WaCpu_Size_SecSha2_512[MCUXCLHASH_INTERNAL_WACPU_SIZE_SECSHA2_512];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_224_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_224_NONBLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_256_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_256_NONBLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_384_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_384_NONBLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha2_512_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA2_512_NONBLOCKING];
    uint8_t mcuxClHash_Internal_WaCpu_Size_Sha3_Nonblocking[MCUXCLHASH_INTERNAL_WACPU_SIZE_SHA3_NONBLOCKING];
} mcuxClHashModes_Internal_MaxUnion_WaCpu_t;
#define MCUXCLHASHMODES_INTERNAL_WACPU_MAX (sizeof(mcuxClHashModes_Internal_MaxUnion_WaCpu_t))

#define MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL       (MCUXCLCORE_ALIGN_TO_WORDSIZE(sizeof(uint32_t), sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + MCUXCLHASH_BLOCK_SIZE_MAX + MCUXCLHASH_STATE_SIZE_MAX))
/* TODO: CLNS-10242*/
#define MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL_NO_SECSHA       (MCUXCLCORE_ALIGN_TO_WORDSIZE(sizeof(uint32_t), sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + MCUXCLHASH_BLOCK_SIZE_SHA3_SHAKE_128 + MCUXCLHASH_STATE_SIZE_SHA3))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASHMODES_INTERNAL_MEMORY_H_ */
