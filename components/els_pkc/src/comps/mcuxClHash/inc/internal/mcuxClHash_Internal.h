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

/** @file  mcuxClHash_Internal.h
 *  @brief Definitions and declarations of the *INTERNAL* layer of the
 *         @ref mcuxClHash component
 */

#ifndef MCUXCLHASH_INTERNAL_H_
#define MCUXCLHASH_INTERNAL_H_

#include <mcuxClHash_Types.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClSession_Types.h>
#include <mcuxCsslAnalysis.h>

#ifdef __cplusplus
extern "C" {
#endif


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
 * @brief Hash Context structure
 *
 * Maintains the state of a hash computation when using the streaming API.
 * 
 * This structure only holds metadata, and the actual hash algorithm's state is part of the context but stored behind this structure.
 *
 * See #mcuxClHash_init for information about the streaming API.
 */
struct mcuxClHash_ContextDescriptor
{
  uint64_t processedLength[2];
  uint32_t unprocessedLength;
  const mcuxClHash_AlgorithmDescriptor_t * algo;
};

#define MCUXCLHASH_CONTEXT_DATA_OFFSET             (sizeof(mcuxClHash_ContextDescriptor_t)) ///< Offset of data buffers from the start of the context


/**
 * @brief Hash one-shot skeleton function type
 *
 * This function will accumulate, pad, etc. the input message and then process it with the Hash core function (mcuxClHash_AlgoCore_t)
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
  mcuxClHash_AlgoSkeleton_OneShot_t oneShotSkeleton;        ///< One-shot hash skeleton function
  uint32_t protection_token_oneShotSkeleton;               ///< Protection token value for the used one-shot skeleton
  mcuxClHash_AlgoSkeleton_Process_t processSkeleton;        ///< Process hash skeleton function
  uint32_t protection_token_processSkeleton;               ///< Protection token value for the used process skeleton
  mcuxClHash_AlgoSkeleton_Finish_t finishSkeleton;          ///< Multi-part hash skeleton function
  uint32_t protection_token_finishSkeleton;                ///< Protection token value for the used multi-part skeleton
  size_t blockSize;                                        ///< Size of the block used by the hash algorithm
  size_t hashSize;                                         ///< Size of the output of the hash algorithm
  size_t stateSize;                                        ///< Size of the state used by the hash algorithm
  uint32_t counterSize;                                    ///< Size of the counter used by the hash algorithm
  const void *pAlgorithmDetails;                           ///< Contains algorithm specific details not needed on API level
};

/**@}*/

/**********************************************
 * Function declarations
 **********************************************/
/**
 * @brief support bigger input length up to 2^128 bits
 */
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
static inline int mcuxClHash_processedLength_cmp(uint64_t *pLen128, uint64_t cmpLenHigh64, uint64_t cmpLenLow64)
{
  return pLen128[1] > cmpLenHigh64 ? 1 : (cmpLenHigh64 > pLen128[1] ? -1 : ((pLen128[0] > cmpLenLow64 ? 1 : (pLen128[0] == cmpLenLow64 ? 0 : -1))));
}

static inline uint32_t mcuxClHash_getContextWordSize(mcuxClHash_Algo_t algo)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Context size will never overflow.")
  return (sizeof(mcuxClHash_ContextDescriptor_t) + algo->stateSize + algo->blockSize) / sizeof(uint32_t);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
}

/**
 * @brief Returns the address of the state within the given context
 * 
*/
static inline uint32_t *mcuxClHash_getStatePtr(mcuxClHash_Context_t pContext)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Context and offset are word-aligned")
  return (uint32_t *)((uint8_t *)pContext + MCUXCLHASH_CONTEXT_DATA_OFFSET);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
}

/**
 * @brief Returns the address of the unprocessed buffer within the given context
 * 
 * @param[in] stateSize Byte size of the state includidng a potential mask
 * 
*/
static inline uint32_t *mcuxClHash_getUnprocessedPtr(mcuxClHash_Context_t pContext)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Context, offset and all state sizes are word-aligned")
  return (uint32_t *)((uint8_t *)pContext + MCUXCLHASH_CONTEXT_DATA_OFFSET + pContext->algo->stateSize);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASH_INTERNAL_H_ */
