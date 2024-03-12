/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

/**
 * @file  mcuxClOsccaSm2_Internal_Hash.h
 * @brief internal header for abstracting hash calls in mcuxClOsccaSm2
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_HASH_H_
#define MCUXCLOSCCASM2_INTERNAL_HASH_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClHash_Types.h>
#include <mcuxClHash_Functions.h>
#include <mcuxClHash_Constants.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClSession_Internal.h>


/******************************************************************************/
/* Macros to wrapper the init and partial compute the hash                    */
/******************************************************************************/
#define MCUXCLOSCCASM2_FP_CALC_HASHINITPRO(pSession, pCtx, algoHash, pIn, inSize, hashRet) \
    do{                                                                     \
        /* Initialize the hash context */                                   \
        MCUX_CSSL_FP_FUNCTION_CALL(retInitHash,                              \
            mcuxClHash_init(pSession,                                        \
                            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES() \
                           (mcuxClHash_Context_t)(pCtx),                     \
                            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY() \
                           algoHash) );                                     \
        if (MCUXCLHASH_STATUS_OK != retInitHash)                             \
        {                                                                   \
            hashRet = retInitHash;                                          \
            break;                                                          \
        }                                                                   \
                                                                            \
        /* Update hash context with partial input */                        \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcessHash,                           \
            mcuxClHash_process(pSession,                                     \
                              (mcuxClHash_Context_t)(pCtx),                  \
                              (pIn),                                        \
                              inSize) );                                    \
        if (MCUXCLHASH_STATUS_OK != retProcessHash)                          \
        {                                                                   \
            hashRet = retProcessHash;                                       \
            break;                                                          \
        }                                                                   \
        hashRet = MCUXCLHASH_STATUS_OK;                                      \
    } while(false)

#define MCUXCLOSCCASM2_FP_CALLED_CALC_HASHINITPRO                            \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_init),                            \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)

/******************************************************************************/
/* Macros to wrapper partial hash compute                                     */
/******************************************************************************/
#define MCUXCLOSCCASM2_FP_CALC_HASHPROCESS(pSession, pCtx, pIn, inSize, hashRet) \
    do{                                                                     \
        /* Update hash context with partial input */                        \
        MCUX_CSSL_FP_FUNCTION_CALL(retProcessHash,                           \
            mcuxClHash_process(pSession,                                     \
                              MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES() \
                              (mcuxClHash_Context_t)(pCtx),                  \
                              MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY() \
                              (pIn),                                        \
                              inSize) );                                    \
        if (MCUXCLHASH_STATUS_OK != retProcessHash)                          \
        {                                                                   \
            hashRet = retProcessHash;                                       \
            break;                                                          \
        }                                                                   \
        hashRet = MCUXCLHASH_STATUS_OK;                                      \
    } while(false)

#define MCUXCLOSCCASM2_FP_CALLED_CALC_HASHPROCESS                            \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)

/******************************************************************************/
/* Macros to wrapper partial hash compute and final hash process              */
/******************************************************************************/
#define MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(pSession, pCtx, pIn, inSize, pOutput, hashRet) \
    do{                                                                     \
        uint32_t outLength = 0u;                                            \
        /* Update hash context with partial input */                        \
        MCUX_CSSL_FP_FUNCTION_CALL(retProHash,                               \
            mcuxClHash_process(pSession,                                     \
                              MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES() \
                              (mcuxClHash_Context_t)(pCtx),                  \
                              MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY() \
                              (mcuxCl_InputBuffer_t) (pIn),                  \
                              inSize) );                                    \
        if (MCUXCLHASH_STATUS_OK != retProHash)                              \
        {                                                                   \
            hashRet = retProHash;                                           \
            break;                                                          \
        }                                                                   \
                                                                            \
        /* Finalize hash computation */                                     \
        MCUX_CSSL_FP_FUNCTION_CALL(retFinalHash,                             \
            mcuxClHash_finish(pSession,                                      \
                              (mcuxClHash_Context_t)(pCtx),                  \
                              (pOutput),                                    \
                              &outLength) );                                \
        if (MCUXCLHASH_STATUS_OK != retFinalHash)                            \
        {                                                                   \
            hashRet = retFinalHash;                                         \
            break;                                                          \
        }                                                                   \
        hashRet = MCUXCLHASH_STATUS_OK;                                      \
    } while(false)

#define MCUXCLOSCCASM2_FP_CALLED_CALC_HASHFINALPRO                           \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process),                         \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)

/******************************************************************************/
/* Macros to wrapper the SM3 hash context copy                                */
/******************************************************************************/
#define MCUXCLOSCCASM2_FP_CONTEXT_HASHCOPY(pCtxDst, pCtxOri)                              \
    do{                                                                                  \
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES() \
        ((mcuxClHash_Context_t)pCtxDst)->unprocessedLength = ((mcuxClHash_Context_t)pCtxOri)->unprocessedLength;    \
        ((mcuxClHash_Context_t)pCtxDst)->processedLength[0U] = ((mcuxClHash_Context_t)pCtxOri)->processedLength[0U];\
        ((mcuxClHash_Context_t)pCtxDst)->processedLength[1U] = ((mcuxClHash_Context_t)pCtxOri)->processedLength[1U];\
        ((mcuxClHash_Context_t)pCtxDst)->processedLength[2U] = ((mcuxClHash_Context_t)pCtxOri)->processedLength[2U];\
        ((mcuxClHash_Context_t)pCtxDst)->processedLength[3U] = ((mcuxClHash_Context_t)pCtxOri)->processedLength[3U];\
        ((mcuxClHash_Context_t)pCtxDst)->algo = ((mcuxClHash_Context_t)pCtxOri)->algo;                                        \
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_copy((uint8_t *)mcuxClHash_getUnprocessedPtr((mcuxClHash_Context_t)pCtxDst),                 \
                                                        (uint8_t *)mcuxClHash_getUnprocessedPtr((mcuxClHash_Context_t)pCtxOri),                 \
                                                        MCUXCLOSCCASM3_BLOCK_SIZE_SM3,                                           \
                                                        MCUXCLOSCCASM3_BLOCK_SIZE_SM3));                                         \
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_copy((uint8_t *)mcuxClHash_getStatePtr((mcuxClHash_Context_t)pCtxDst),                       \
                                                        (uint8_t *)mcuxClHash_getStatePtr((mcuxClHash_Context_t)pCtxOri),                       \
                                                        MCUXCLOSCCASM3_STATE_SIZE_SM3,                                           \
                                                        MCUXCLOSCCASM3_STATE_SIZE_SM3));                                         \
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY() \
    } while(false)

#endif /* MCUXCLOSCCASM2_INTERNAL_HASH_H_ */
