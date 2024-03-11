/*--------------------------------------------------------------------------*/
/* Copyright 2021-2024 NXP                                                  */
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
#include <mcuxClBuffer.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Macros.h>
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
  uint32_t processedLength[4];
  uint32_t unprocessedLength;
  const mcuxClHash_AlgorithmDescriptor_t * algo;
};

#define MCUXCLHASH_CONTEXT_DATA_OFFSET             (sizeof(mcuxClHash_ContextDescriptor_t)) ///< Offset of data buffers from the start of the context
#define MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET    (7u) ///< Start of data buffers is moved at most 7 Bytes back to ensure 64 Bit alignment of pState.


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
  uint8_t processedLengthCheckMask;                        ///< Mask of the highest byte of the processed length that cannot be set
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
 * @brief Adds a 32 Bit constant to an 128 Bit counter
 * 
 * This function is used to support bigger input length up to 2^128 Bit
 * 
 * @param[in out] pLen128 128 Bit counter to increment
 * @param[in] addLen 32 Bit constant to increment counter with
 */
void mcuxClHash_processedLength_add(uint32_t *pLen128, uint32_t addLen);


/**
 * @brief Compares an 128 Bit counter value against a 32 Bit constant.
 * 
 * @param[in] pLen128 128 Bit counter
 * @param[in] cmpLenLow32 32 Bit constant
 * 
 * @return ternary value indicating greater, equal, smaller relationship
 * @retval 1    Counter value is bigger than constant
 * @retval 0    Counter and constant have equal value
 * @retval -1   Counter value is smaller than constant
 */
int mcuxClHash_processedLength_cmp(uint32_t *pLen128, uint32_t cmpLenLow32);

/**
 * @brief convert 128 bit number of bytes to number of bits
 * 
 * @param pLen128[in out] 128 Bit number represented as uint32_t array. Upper 3 bits need to be zero to avoid overflow.
 */
static inline void mcuxClHash_processedLength_toBits(uint32_t *pLen128)
{
  pLen128[3] = (pLen128[3] << 3u) | (pLen128[2] >> 29u);
  pLen128[2] = (pLen128[2] << 3u) | (pLen128[1] >> 29u);
  pLen128[1] = (pLen128[1] << 3u) | (pLen128[0] >> 29u);
  pLen128[0] = pLen128[0] << 3u;
}


/**
 * @brief Computes an upper bound of the context size for a given hash algorithm.
 * 
 * This allows usage of smaller context buffers and should be preferred over MCUXCLHASH_CONTEXT_SIZE 
 * if the Hash algorithm is chosen by the user but the hash context is allocated within the CL.
 *
 * @param[in] algo Hash algorithm, SecSha is currently not supported 
 * 
 * @return Byte size of a Hash context
 */
static inline uint32_t mcuxClHash_getContextWordSize(mcuxClHash_Algo_t algo)
{
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("Context size will never overflow.")
  return MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(sizeof(mcuxClHash_ContextDescriptor_t) + MCUXCLHASH_CONTEXT_MAX_ALIGNMENT_OFFSET + algo->stateSize + algo->blockSize);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
}

/**
 * @brief Returns the address of the state within the given context
 * 
 * @param[in] pContext The given context
 *
*/
static inline uint32_t *mcuxClHash_getStatePtr(mcuxClHash_Context_t pContext)
{
  uint8_t *pState = (uint8_t *)pContext + MCUXCLHASH_CONTEXT_DATA_OFFSET;
  /* Align state to 64 Bit */
  size_t stateOffset = ((uint32_t)pState % sizeof(uint64_t));
  if(0u != stateOffset)
  {
    pState += (sizeof(uint64_t) - stateOffset);
  }
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("pState is now 64 Bit aligned")
  return (uint32_t *)pState;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
}

/**
 * @brief Returns the address of the unprocessed buffer within the given context
 *
 * @param[in] pContext The given context
 *
*/
static inline uint32_t *mcuxClHash_getUnprocessedPtr(mcuxClHash_Context_t pContext)
{
  uint8_t *pUnprocessed = (uint8_t *)mcuxClHash_getStatePtr(pContext) + pContext->algo->stateSize;
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("pUnprocessed is 32 Bit aligned since the state pointer is 64 Bit aligned and the state size is at least 32 Bit aligned.")
  return (uint32_t *)pUnprocessed;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING()
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASH_INTERNAL_H_ */
