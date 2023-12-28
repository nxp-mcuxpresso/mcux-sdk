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

/** @file  mcuxClCipherModes_Els_Aes.c
 *  @brief implementation of the Skeleton functions of the mcuxClCipher component */

#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClAes.h>
#include <internal/mcuxClCipher_Internal.h>
#include <internal/mcuxClCipherModes_Internal.h>


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

    /* Keep track of where we are in input and output */
    uint8_t const* pInput = (uint8_t const*) pIn;
    uint8_t * pOutput = (uint8_t *) pOut;

    /* Correct Context type for Aes ELS Skeleton */
    mcuxClCipherModes_Context_Aes_Els_t * pCtx = NULL;
    uint32_t cpuWaSizeInWords = 0;

    /* Correct algorithm type for Aes ELS Skeleton */
    const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = NULL;

    if ((MCUXCLCIPHER_OPTION_INIT == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        if(NULL == session)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
        }

        pAlgo = pMode->pAlgorithm;

        if(MCUXCLCIPHER_OPTION_ONESHOT == steps)
        {
            /* Create context for Oneshot, needed by ELS */
            /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
            cpuWaSizeInWords = MCUXCLCIPHERMODES_INTERNAL_COMPUTE_CPUWORDS(sizeof(mcuxClCipherModes_Context_Aes_Els_t));
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
            if (0u != (inLength % pAlgo->granularity))
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
            }
        }
        else
        {
            pCtx = (mcuxClCipherModes_Context_Aes_Els_t *) pContext;
        }

        /* Store mode and key in context */
        pCtx->common.pMode = pMode;
        pCtx->pKey = pKey;

        /* InitialDataLength is initialized with zero (for oneshot, this will always be zero). */
        pCtx->common.blockBufferUsed = 0u;
        /* Total number of bytes that were encrypted is initialized with zero */
        pCtx->common.totalInputLength = 0u;

        if ((0u != pAlgo->ivLength) && (ivLength != pAlgo->ivLength))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
        }

        /* If there is an IV, copy it to the ivState buffer. */
        if (0u != pAlgo->ivLength)
        {
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF((uint8_t *) pCtx->ivState, pIv, ivLength, MCUXCLAES_BLOCK_SIZE);
        }
    }
    else
    {
        /* MISRA Ex. 9 to Rule 11.3 */
        pCtx = (mcuxClCipherModes_Context_Aes_Els_t *) pContext;
        pAlgo = (const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *) pCtx->common.pMode->pAlgorithm;
    }

    // below variable definitions are used for flow protection of plaintext data process
    uint32_t processFPFlag_partData = 0u;
    uint32_t processFPFlag_partDataHandling = 0u;
    uint32_t bytesRemaining = 0u;

    if ((MCUXCLCIPHER_OPTION_PROCESS == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        const uint32_t inputLength = inLength;
        if (0u != pCtx->common.blockBufferUsed)
        {
            processFPFlag_partData = 1u;

            /* Number of bytes to copy into the partial data buffer. */
            uint32_t bytesToCopy = (((MCUXCLAES_BLOCK_SIZE - pCtx->common.blockBufferUsed) < (inLength)) ?
                                     (MCUXCLAES_BLOCK_SIZE - pCtx->common.blockBufferUsed) : (inLength));

            /* Add new data into the partial data buffer and process, if possible. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pCtx->blockBuffer + pCtx->common.blockBufferUsed,
                                                                   pInput,
                                                                   bytesToCopy,
                                                                   MCUXCLAES_BLOCK_SIZE);
            /* Update the number of bytes in the partial data buffer.*/
            pCtx->common.blockBufferUsed += bytesToCopy;

            if (MCUXCLAES_BLOCK_SIZE == pCtx->common.blockBufferUsed)
            {
                processFPFlag_partDataHandling = 1u;
                MCUX_CSSL_FP_FUNCTION_CALL(cipherResult, pAlgo->cryptEngine(session,
                                                                           pCtx,
                                                                           pCtx->blockBuffer,
                                                                           MCUXCLAES_BLOCK_SIZE,
                                                                           pOutput));
                if (cipherResult != MCUXCLCIPHER_STATUS_OK)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
                }
                /* Write to pOutLength how many bytes have been written. */
                *pOutLength += MCUXCLAES_BLOCK_SIZE;
                pOutput += MCUXCLAES_BLOCK_SIZE;

                /* The partial data buffer is now empty. */
                pCtx->common.blockBufferUsed = 0u;
            }
            /* Update input location and remaining length */
            pInput += bytesToCopy;
            inLength -= bytesToCopy;
        }

        /* Calculate bytes in the input that do not form a full block. */
        bytesRemaining = inLength % MCUXCLAES_BLOCK_SIZE;

        if (inLength >= MCUXCLAES_BLOCK_SIZE)
        {
            /* Calculate bytes in the input that form full blocks. */
            uint32_t bytesToProcess = inLength - bytesRemaining;
            /* Process remaining full blocks from the input. */
            MCUX_CSSL_FP_FUNCTION_CALL(cipherResult1, pAlgo->cryptEngine(session,
                                                                        pCtx,
                                                                        pInput,
                                                                        bytesToProcess,
                                                                        pOutput));
            if (cipherResult1 != MCUXCLCIPHER_STATUS_OK)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
            }
            /* Update input location */
            pInput += bytesToProcess;

            /* Write to pOutLength how many bytes have been written. */
            *pOutLength += bytesToProcess;
            pOutput += bytesToProcess;
        }

        if (0u != bytesRemaining)
        {
            /* If there are still bytes less than one block in the input, write them into the partial data buffer. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pCtx->blockBuffer,
                                                                   pInput,
                                                                   bytesRemaining,
                                                                   MCUXCLAES_BLOCK_SIZE);
            pCtx->common.blockBufferUsed = bytesRemaining;
        }
        /* Update total number of bytes that were encrypted */
        pCtx->common.totalInputLength += inputLength;
    }

    /* Number of bytes of the padded block - also used to determine how much data to copy to the output,
       therefore it is initialized to the partial data length in case no padding is applied (CTR) . */
    uint32_t padOutLength = pCtx->common.blockBufferUsed;

    if ((MCUXCLCIPHER_OPTION_FINISH == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps))
    {
        if (NULL != pAlgo->addPadding)
        {
            /* Apply the padding function specified in the mode on the partial data. */
            MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(pAlgo->blockLength,
                                                                   pCtx->blockBuffer,
                                                                   pCtx->common.blockBufferUsed,
                                                                   pCtx->common.totalInputLength,
                                                                   pCtx->blockBuffer,
                                                                   &padOutLength));

            if (MCUXCLPADDING_STATUS_OK != padResult)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
            }
        }

        if (padOutLength > 0u)
        {
            /* If padding was added, process the data in the partial data buffer. */
            MCUX_CSSL_FP_FUNCTION_CALL(cipherResult2,  pAlgo->cryptEngine(session,
                                                                         pCtx,
                                                                         pCtx->blockBuffer,
                                                                         MCUXCLAES_BLOCK_SIZE,
                                                                         pCtx->blockBuffer));
            if (cipherResult2 != MCUXCLCIPHER_STATUS_OK)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes, MCUXCLCIPHER_STATUS_ERROR);
            }

            /* Copy the padding to the output and update pOutLength accordingly. */
            MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pOutput,
                                                                   pCtx->blockBuffer,
                                                                   padOutLength,
                                                                   MCUXCLAES_BLOCK_SIZE);
            *pOutLength += padOutLength;
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
            MCUX_CSSL_FP_CONDITIONAL((0u != ivLength),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
            )
        ),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLCIPHER_OPTION_PROCESS == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps)),
            MCUX_CSSL_FP_CONDITIONAL((1u == processFPFlag_partData),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_CONDITIONAL((1u == processFPFlag_partDataHandling),
                    pAlgo->protection_token_engine)
            ),
            MCUX_CSSL_FP_CONDITIONAL((inLength >= MCUXCLAES_BLOCK_SIZE),
                pAlgo->protection_token_engine
            ),
            MCUX_CSSL_FP_CONDITIONAL((0u != bytesRemaining),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy))
        ),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLCIPHER_OPTION_FINISH == steps) || (MCUXCLCIPHER_OPTION_ONESHOT == steps)),
            MCUX_CSSL_FP_CONDITIONAL((NULL != pAlgo->addPadding),
                pAlgo->protection_token_addPadding),
            MCUX_CSSL_FP_CONDITIONAL((padOutLength > 0u),
                pAlgo->protection_token_engine,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
            )
        )
    );
}
