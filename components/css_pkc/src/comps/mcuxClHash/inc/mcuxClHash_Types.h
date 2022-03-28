/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClHash_Types.h
 *  @brief Type definitions for the mcuxClHash component
 */

#ifndef MCUXCLHASH_TYPES_H_
#define MCUXCLHASH_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxClSession_Types.h>

 /**
 * @defgroup mcuxClHash_Types mcuxClHash_Types
 * @brief Defines all types of the @ref mcuxClHash component
 * @ingroup mcuxClHash
 * @{
 */

/***********************************************************
 *  EXTERNAL TYPES
 **********************************************************/
/**
 * @brief Hash Algorithm type
 *
 * This is an abstract type defining the hash algorithm.
 *
 */
typedef struct mcuxClHash_Algo mcuxClHash_Algo_t;

/**
 * @brief Hash Context type
 *
 * This is an abstract type defining the hash context.
 *
 */
typedef struct mcuxClHash_Context mcuxClHash_Context_t;

/**
 * @brief Hash Protected Status type
 *
 */
typedef uint64_t mcuxClHash_Status_Protected_t;

/**
 * @brief Hash Status type
 *
 * This type is used for hash return values: \ref mcuxClHashStatusValues
 *
 */
typedef uint32_t mcuxClHash_Status_t;

/**@}*/

/***********************************************************
 *  MACROS RELATED TO FUNCTION STATUS
 **********************************************************/

/**
 * @defgroup MCUXCLHASH_STATUS_ MCUXCLHASH_STATUS_
 * @brief Return code definitions
 * @ingroup mcuxClHash_Macros
 * @{
 */
#define MCUXCLHASH_STATUS_OK                 ((mcuxClHash_Status_t) 0xE1E1E1E1u )  ///< Hash operation successful
#define MCUXCLHASH_STATUS_ERROR              ((mcuxClHash_Status_t) 0xE1E11E1Eu )  ///< Error occured during Hash operation
#define MCUXCLHASH_STATUS_FAULT_ATTACK       ((mcuxClHash_Status_t) 0xE1E1F0F0u )  ///< Fault attack (unexpected behaviour) detected

/**@}*/


/***********************************************************
 *  INTERNAL TYPES
 **********************************************************/

/*
 * \defgroup InternalOptions  mcuxClHash internal option values. Not used by external API
 * @{
 */
#define MCUXCLHASH_INIT      0x00000011u
#define MCUXCLHASH_UPDATE    0x00000022u
#define MCUXCLHASH_FINALIZE  0x00000088u
/*
 * @}
 */

/*
 * \defgroup InternalCounterlengh  mcuxClHash internal counter size values used for padding. Not used by external API
 * @{
 */
#define MCUXCLHASH_COUNTER_SIZE_SHA_256  8
#define MCUXCLHASH_COUNTER_SIZE_SHA_224  MCUXCLHASH_COUNTER_SIZE_SHA_256
#define MCUXCLHASH_COUNTER_SIZE_SHA_512  16
#define MCUXCLHASH_COUNTER_SIZE_SHA_384  MCUXCLHASH_COUNTER_SIZE_SHA_512
/*
 * @}
 */

/*
 * @brief Hash Context data storage structure
 *
 * Maintains the data buffers associated with the state of a hash computation when using the streaming API.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
typedef struct mcuxClHash_ContextBuffer
{
  uint8_t unprocessed[128u];
  uint8_t state[64u];
}mcuxClHash_ContextBuffer_t;

/*
 * @brief Hash Context counter structure
 *
 * Maintains the counters associated with the state of a hash computation when using the streaming API. The counters
 * are limited to 32 bits, so only up to 2^32 bytes of data can be hashed in a single context.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
typedef struct mcuxClHash_ContextData {
  uint32_t unprocessedLength;
  uint32_t processedLength;
}mcuxClHash_ContextData_t;

/*
 * @brief Hash Context structure
 *
 * Maintains the state of a hash computation when using the streaming API.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
struct mcuxClHash_Context
{
  mcuxClHash_ContextBuffer_t buffer;
  mcuxClHash_ContextData_t data;
  const mcuxClHash_Algo_t * algo;
  /* if needed: const uint8_t *const iv, */
};

/*
 * @brief Hash Engine function type
 *
 * This function will process one or more blocks of the Hash algorithm
 *
 */
typedef mcuxClHash_Status_Protected_t (*mcuxClHash_AlgoEngine_t)(
                        uint32_t options,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out
                        );

/*
 * @brief Hash Skeleton function type
 *
 * This function will accumulate, padd, etc. the input message and then process it with the Hash engine function (mcuxClHash_AlgoEngine_t)
 *
 */
typedef mcuxClHash_Status_Protected_t (*mcuxClHash_AlgoSkeleton_t)(
                        mcuxClSession_Handle_t session,
                        const mcuxClHash_Algo_t *algo,
                        mcuxClHash_ContextData_t *context,
                        mcuxClHash_ContextBuffer_t *buffer,
                        const uint8_t *const in,
                        uint32_t inSize,
                        uint8_t *const out,
                        uint8_t *const rtf,
                        uint32_t options
                        );

/*
 * @brief DMA protection function type
 *
 * This function will verify if the DMA transfer of the last hardware accelerator operation finished on the expected address
 *
 */
typedef mcuxClHash_Status_Protected_t (*mcuxClHash_AlgoDmaProtection_t)(
                        uint8_t *startAddress,
                        size_t expectedLength
                        );

/*
 * @brief Hash Algorithm structure
 *
 */
struct mcuxClHash_Algo
{
  mcuxClHash_AlgoEngine_t engine;                ///< Hash engine function
  mcuxClHash_AlgoSkeleton_t skeleton;            ///< One-shot hash skeleton function
  mcuxClHash_AlgoSkeleton_t streamingSkeleton;   ///< Streaming hash skeleton function
  size_t blockSize;                             ///< Size of the block used by the hash algorithm
  size_t hashSize;                              ///< Size of the output of the hash algorithm
  size_t stateSize;                             ///< Size of the state used by the hash algorithm
  uint32_t counterSize;                         ///< Size of the counter used by the hash algorithm
  uint32_t rtfSize;                             ///< Size of the Runtime Fingerprint used by the hash function; has to be set to zero when not supported
  uint32_t protection_token_skeleton;           ///< Protection token value for the used one-shot skeleton
  uint32_t protection_token_streaming_skeleton; ///< Protection token value for the used streaming skeleton
  uint32_t protection_token_engine;             ///< Protection token value for the used engine
  // SHA-224 and SHA-512/t could be supported by adding an IV field
};


#endif /* MCUXCLHASH_TYPES_H_ */
