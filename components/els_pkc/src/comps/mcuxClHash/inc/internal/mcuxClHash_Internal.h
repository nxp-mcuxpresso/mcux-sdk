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

/** @file  mcuxClHash_internal.h
 *  @brief Definitions and declarations of the *INTERNAL* layer of the
 *         @ref mcuxClHash component
 */

#ifndef MCUXCLHASH_INTERNAL_H_
#define MCUXCLHASH_INTERNAL_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClHash_Types.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>


#include <mcuxClEls_Hash.h>
#include <internal/mcuxClHash_Internal_els_sha2.h>
#include <internal/mcuxClHash_Core_els_sha2.h>


#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClHash_Internal_Constants mcuxClHash_Internal_Constants
 * @brief Defines all internal constants of @ref mcuxClHash component
 * @ingroup mcuxClHash_Constants
 * @{
 */
#define MCUXCLHASH_BLOCK_SIZE_SHA_1              (64U) ///< SHA-1 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_224            (64U) ///< SHA-224 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_256            (64U) ///< SHA-256 block size: 512 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_384           (128U) ///< SHA-384 block size: 1024 bit (128 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA_512           (128U) ///< SHA-512 block size: 1024 bit (128 bytes)
#define MCUXCLHASH_BLOCK_SIZE_MD5                (64U) ///< MD5 block size: MD5 bit (64 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_224          (144U) ///< SHA3-224 block size: 1152 bit (144 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_256          (136U) ///< SHA3-256 block size: 1088 bit (136 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_384          (104U) ///< SHA3-384 block size: 832 bit (104 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SHA3_512           (72U) ///< SHA3-512 block size: 576 bit (72 bytes)
#define MCUXCLHASH_BLOCK_SIZE_SM3                (64U) ///< SM3 block size: 512 bit (64 bytes)

#define MCUXCLHASH_STATE_SIZE_SHA_1         (20U) ///< SHA-1 state size: 160 bit (20 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_224       (32U) ///< SHA-224 state size: 256 bit (32 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_256       (32U) ///< SHA-224 state size: 256 bit (32 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_384       (64U) ///< SHA-224 state size: 512 bit (64 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA_512       (64U) ///< SHA-224 state size: 623 bit (64 bytes)
#define MCUXCLHASH_STATE_SIZE_MD5           (16U) ///< MD5 state size: 64 bit (8 bytes)
#define MCUXCLHASH_STATE_SIZE_SM3           (32u) ///< SM3 state size: 256 bit (32 bytes)
#define MCUXCLHASH_STATE_SIZE_SHA3         (200U) ///< SHA3 all variants state size: 1600 bits (200 bytes)

#define MCUXCLHASH_COUNTER_SIZE_SHA_1              (8U) ///< Counter size for SHA-1 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_224            (8U) ///< Counter size for SHA-224 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_256            (8U) ///< Counter size for SHA-256 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_384            (16U) ///< Counter size for SHA-384 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA_512            (16U) ///< Counter size for SHA-512 padding
#define MCUXCLHASH_COUNTER_SIZE_MD5                (8U) ///< Counter size for MD5 padding
#define MCUXCLHASH_COUNTER_SIZE_SHA3               (16U) ///< Counter size for SHA3 padding
#define MCUXCLHASH_COUNTER_SIZE_MIYAGUCHI_PRENEEL  (1U) ///< Counter size for Miyaguchi Preneel, only indicates whether a block has already been processed

#define MCUXCLHASH_NO_OF_ROUNDS_SHA_1       (80U) ///< Number of rounds for SHA-1 algorithm
#define MCUXCLHASH_NO_OF_ROUNDS_MD5         (64u) ///< Number of rounds for MD5 algorithm

/**@}*/


/**********************************************
 * Type declarations
 **********************************************/
 /**
 * @defgroup mcuxClHash_Internal_Types mcuxClHash_Internal_Types
 * @brief Defines all internal types of the @ref mcuxClHash component
 * @ingroup mcuxClHash_Types
 * @{
 */

/**
 * @brief Hash Context data storage structure
 *
 * @if MCUXCL_FEATURE_HASH_MULTIPART
 * Maintains the data buffers associated with the state of a hash computation when using the streaming API.
 *
 * See #mcuxClHash_init for information about the streaming API.
 * @endif
 */
typedef struct mcuxClHash_ContextBuffer
{
 /* Warning: Entries must be added in the correct sorted order, from max to min. */
  uint8_t unprocessed[MCUXCLHASH_BLOCK_SIZE_SHA_512];
  uint8_t state[MCUXCLHASH_STATE_SIZE_SHA_512];
} mcuxClHash_ContextBuffer_t;

/**
 * @brief support bigger input length up to 2^128 bits
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_processedLength_add)
static inline void mcuxClHash_processedLength_add(uint64_t *pLen128, uint32_t addLen)
{
    if (pLen128[0] > (0xffffffffffffffffu - addLen))
    {
        pLen128[1] += 1u;
    }
    pLen128[0] += addLen;
}

/**
 * @brief support 128bit number compare
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_processedLength_cmp)
static inline int mcuxClHash_processedLength_cmp(uint64_t *pLen128, uint64_t cmpLenHigh64, uint64_t cmpLenLow64)
{
  return pLen128[1] > cmpLenHigh64 ? 1 : (cmpLenHigh64 > pLen128[1] ? -1 : ((pLen128[0] > cmpLenLow64 ? 1 : (pLen128[0] == cmpLenLow64 ? 0 : -1))));
}

/**
 * @brief Hash Context counter structure
 *
 * Maintains the counters associated with the state of a hash computation when using the streaming API.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
typedef struct mcuxClHash_ContextData {
  uint32_t unprocessedLength;
  uint32_t PADDING_FOR_64BIT_ALIGNMENT;
  uint64_t processedLength[2];
} mcuxClHash_ContextData_t;

/**
 * @brief Hash Context structure
 *
 * Maintains the state of a hash computation when using the streaming API.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
struct mcuxClHash_ContextDescriptor
{
  mcuxClHash_ContextBuffer_t buffer;
  mcuxClHash_ContextData_t data;
  const mcuxClHash_AlgorithmDescriptor_t * algo;
  uint32_t PADDING_FOR_64BIT_ALIGNMENT;
  /* if needed: mcuxCl_InputBuffer_t iv, */
};

/**
 * @brief Hash one-shot skeleton function type
 *
 * This function will accumulate, padd, etc. the input message and then process it with the Hash core function (mcuxClHash_AlgoCore_t)
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHash_AlgoSkeleton_OneShot_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) (*mcuxClHash_AlgoSkeleton_OneShot_t)(
                                    mcuxClSession_Handle_t session,
                                    mcuxClHash_Algo_t algorithm,
                                    mcuxCl_InputBuffer_t pIn,
                                    uint32_t inSize,
                                    mcuxCl_Buffer_t pOut,
                                    uint32_t *const pOutSize));

/**
 * @brief Hash process skeleton function type
 *
 * This function will accumulate the input message and then process it with the Hash core function (mcuxClHash_AlgoEngine_t)
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHash_AlgoSkeleton_Process_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) (*mcuxClHash_AlgoSkeleton_Process_t)(
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t context,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize));

/**
 * @brief Hash multi-part skeleton function type
 *
 * This function will accumulate, padd, etc. the input message and then process it with the Hash core function (mcuxClHash_AlgoCore_t)
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHash_AlgoSkeleton_Finish_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) (*mcuxClHash_AlgoSkeleton_Finish_t)(
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t context,
                        mcuxCl_Buffer_t pOut,
                        uint32_t *const pOutSize));

/**
 * @brief Hash Algorithm structure
 *
 */
struct mcuxClHash_AlgorithmDescriptor
{
  mcuxClHash_els_AlgoCore_t els_core;                       ///< ELS hash core function (access to ELS coprocessor)
  uint32_t protection_token_els_core;                      ///< Protection token value for the used core
  mcuxClHash_AlgoSkeleton_OneShot_t oneShotSkeleton;        ///< One-shot hash skeleton function
  uint32_t protection_token_oneShotSkeleton;               ///< Protection token value for the used one-shot skeleton
  mcuxClHash_AlgoSkeleton_Process_t processSkeleton;        ///< Process hash skeleton function
  uint32_t protection_token_processSkeleton;               ///< Protection token value for the used process skeleton
  mcuxClHash_AlgoSkeleton_Finish_t finishSkeleton;          ///< Multi-part hash skeleton function
  uint32_t protection_token_finishSkeleton;                ///< Protection token value for the used multi-part skeleton
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
  mcuxClHash_AlgoDmaProtection_t dmaProtection;             ///< DMA protection function
  uint32_t protection_token_dma_protection;                ///< Protection token value for the used DMA protection function
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
  size_t blockSize;                                        ///< Size of the block used by the hash algorithm
  size_t hashSize;                                         ///< Size of the output of the hash algorithm
  size_t stateSize;                                        ///< Size of the state used by the hash algorithm
  uint32_t counterSize;                                    ///< Size of the counter used by the hash algorithm


  uint32_t rtfSize;                                        ///< Size of the Runtime Fingerprint used by the hash function; has to be set to zero when not supported
  mcuxClEls_HashOption_t hashOptions;
};

/**@}*/

/**********************************************
 * Function declarations
 **********************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASH_INTERNAL_H_ */
