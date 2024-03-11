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

/** @file  mcuxClCipherModes_Els_Aes.c
 *  @brief implementation of the Skeleton functions of the mcuxClCipher component */

#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Macros.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClAes.h>
#include <internal/mcuxClCipher_Internal.h>
#include <internal/mcuxClCipherModes_Common.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_SkeletonAes)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipherModes_SkeletonAes(
    mcuxClSession_Handle_t session,
    mcuxClCipher_Context_t * const pContext,
    mcuxClKey_Handle_t pKey,
    mcuxClCipher_Mode_t pMode,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    uint32_t steps //!< steps is a bitmask with one bit reserved for each of the steps below
    )
{
    /* [Design]
        ATTN: pOutLength will be incremented by the number of bytes of encrypted data that have been
              written to the @p pOut buffer. Except otherwise mentioned processing steps output data
              to pOut and update pOutLength

        - Oneshot Initialization (steps == oneshot)
            - check if inLength is a multiple of granularity (in the mode), if not exit with ERROR

        - Init processing (steps == oneshot / init)
            - if mode requires IV: copy pIv to ivState in context and check IV length == blocklength otherwise error
            - set blockBufferUsed in context to zero

        - Update processing (steps == oneshot / update)
            - if blockBufferUsed != 0 (this will never be the case for oneshot)
                - set elsOptions
                - add the new data from the input to blockBuffer and process if possible
                - adapt blockBufferUsed
            - set elsOptions
            - process remaining complete blocks from the input
            - add remaining data to blockBuffer, adapt blockBufferUsed (this can happen for oneshot)

        - Finish processing (steps == oneshot / finish)
            - dataToCopy = blockBufferUsed rounded up to the next multiple of granularity from the context
            - Check if the padding function does not point to NULL, if it does exit with ERROR
            - Apply the padding function on blockBuffer from context
            - If the output of the padding function is longer than zero, set elsOptions and process the blockBuffer,
              store the result in blockBuffer
            - copy dataToCopy bytes from blockBuffer to the output and update pOutLength accordingly
            - clean up context

    */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipherModes_SkeletonAes);
    /* Keep track of where we are in output */
    uint8_t * pOutput = (uint8_t *) pOut;

    /* Correct Context type for Aes ELS Skeleton */
    mcuxClCipherModes_Context_Aes_Els_t * pCtx = NULL;
    uint32_t cpuWaSizeInWords = 0;

    if(NULL == session)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
    }

    if(MCUXCLCIPHER_OPTION_ONESHOT == steps)
    {
        /* Create context for Oneshot, needed by ELS */
        cpuWaSizeInWords = MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(sizeof(mcuxClCipherModes_Context_Aes_Els_t));
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx = (mcuxClCipherModes_Context_Aes_Els_t *) mcuxClSession_allocateWords_cpuWa(session, cpuWaSizeInWords);
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
        if(NULL == pCtx)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_FAILURE);
        }

        /* inLength needs to be a multiple of the granularity, if this is not the case, return an error.
           The granularity is set in the mode as such:
           - for CTR it is set to 1
           - for paddingNone it is set to blocksize
           - for other padding modes it is set to 1
        */
        if (0u != (inLength % ((mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *)pMode->pAlgorithm)->granularity))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
        }
    }
    else
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx = (mcuxClCipherModes_Context_Aes_Els_t *) pContext;
        MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    }

    if ((MCUXCLCIPHER_OPTION_INIT == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pCtx is of type mcuxClCipherModes_Context_Aes_Els_t *")
        MCUX_CSSL_FP_FUNCTION_CALL(initResult, mcuxClCipherModes_SkeletonAes_Init(pCtx, pKey, pMode, pIv, ivLength));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        if(MCUXCLCIPHER_STATUS_OK != initResult)
        {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, initResult, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Init));
        }
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pCtx is of type mcuxClCipherModes_Context_Aes_Els_t *")
    if((MCUXCLCIPHER_OPTION_INIT != steps) && ((*pOutLength > (UINT32_MAX - inLength)) || ((*pOutLength + inLength) > (UINT32_MAX - pCtx->common.blockBufferUsed))))
    {
        return MCUXCLCIPHER_STATUS_INVALID_INPUT;
    }
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    
    if ((MCUXCLCIPHER_OPTION_PROCESS == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        uint32_t outLen = 0u;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pCtx is of type mcuxClCipherModes_Context_Aes_Els_t *")
        MCUX_CSSL_FP_FUNCTION_CALL(processResult, mcuxClCipherModes_SkeletonAes_Process(session, pCtx, pIn, inLength, pOut, &outLen));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        if (MCUXCLCIPHER_STATUS_OK != processResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, processResult,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Process));
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("False Positive, *pOutLength will not overflow As it was checked above")
        *pOutLength += outLen;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        pOutput += outLen;
    }

    if ((MCUXCLCIPHER_OPTION_FINISH == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The pCtx is of type mcuxClCipherModes_Context_Aes_Els_t *")
        MCUX_CSSL_FP_FUNCTION_CALL(finishResult, mcuxClCipherModes_SkeletonAes_Finish(session, pCtx, (mcuxCl_Buffer_t)pOutput, pOutLength));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        if(MCUXCLCIPHER_STATUS_OK != finishResult)
        {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, finishResult,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Finish));
        }
    }

    if(MCUXCLCIPHER_OPTION_ONESHOT == steps)
    {
        /* Free context in Session */
        mcuxClSession_freeWords_cpuWa(session, cpuWaSizeInWords);
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLCIPHER_OPTION_INIT == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Init)),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLCIPHER_OPTION_PROCESS == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Process)),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLCIPHER_OPTION_FINISH == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_SkeletonAes_Finish)));
}
