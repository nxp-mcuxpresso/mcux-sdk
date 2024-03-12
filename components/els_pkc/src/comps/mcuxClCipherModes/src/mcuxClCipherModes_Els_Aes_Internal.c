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

/** @file  mcuxClCipherModes_Els_Aes_Internal.c
 *  @brief implementation of internal functions for mcuxClCipherModes_SkeletonAes */

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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_SkeletonAes_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipherModes_SkeletonAes_Init(
    mcuxClCipherModes_Context_Aes_Els_t *pCtx,
    mcuxClKey_Handle_t pKey,
    mcuxClCipher_Mode_t pMode,
    mcuxCl_InputBuffer_t pIv,
    uint32_t ivLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipherModes_SkeletonAes_Init);

    /* Correct algorithm type for Aes ELS Skeleton */
    const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = NULL;
    pAlgo = pMode->pAlgorithm;
    /* Store mode and key in context */
    pCtx->common.pMode = pMode;
    pCtx->pKey = pKey;
    /* InitialDataLength is initialized with zero (for oneshot, this will always be zero). */
    pCtx->common.blockBufferUsed = 0u;
    /* Total number of bytes that were encrypted is initialized with zero */
    pCtx->common.totalInputLength = 0u;

    if ((0u != pAlgo->ivLength) && (ivLength != pAlgo->ivLength))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Init, MCUXCLCIPHER_STATUS_ERROR);
    }

    /* If there is an IV, copy it to the ivState buffer. */
    if (0u != pAlgo->ivLength)
    {
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF((uint8_t *) pCtx->ivState, pIv, ivLength, MCUXCLAES_BLOCK_SIZE);
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipherModes_SkeletonAes_Init, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
              MCUX_CSSL_FP_CONDITIONAL((0u != ivLength), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_SkeletonAes_Process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipherModes_SkeletonAes_Process(
    mcuxClSession_Handle_t session,
    mcuxClCipherModes_Context_Aes_Els_t *pCtx,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipherModes_SkeletonAes_Process);

    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = (const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Keep track of where we are in input and output */
    uint8_t const* pInput = (uint8_t const*) pIn;
    uint8_t * pOutput = (uint8_t *) pOut;
    // below variable definitions are used for flow protection of plaintext data process
    uint32_t processFPFlag_partData = 0u;
    uint32_t processFPFlag_partDataHandling = 0u;
    uint32_t bytesRemaining = 0u;

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
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER_WITH_DATA_TYPE((pCtx->common.blockBufferUsed),uint32_t, 0u, (UINT32_MAX - bytesToCopy), MCUXCLCIPHER_STATUS_ERROR)
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
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Process, MCUXCLCIPHER_STATUS_ERROR);
            }
            /* Write to pOutLength how many bytes have been written. */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("False Positive, *pOutLength will not overflow as it is checked by the caller")
            *pOutLength += MCUXCLAES_BLOCK_SIZE;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            pOutput += MCUXCLAES_BLOCK_SIZE;

            /* The partial data buffer is now empty. */
            pCtx->common.blockBufferUsed = 0u;
        }
        /* Update input location and remaining length */
        pInput += bytesToCopy;
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER_WITH_DATA_TYPE((inLength),uint32_t, bytesToCopy, (UINT32_MAX), MCUXCLCIPHER_STATUS_ERROR)
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
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Process, MCUXCLCIPHER_STATUS_ERROR);
        }
        /* Update input location */
        pInput += bytesToProcess;

        /* Write to pOutLength how many bytes have been written. */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("False Positive, *pOutLength will not overflow as it is checked by the caller")
        *pOutLength += bytesToProcess;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        pOutput += bytesToProcess;
    }

    if (0u != bytesRemaining)
    {
        /* If there are still bytes less than one block in the input, write them into the partial data buffer. */
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(pCtx->blockBuffer, pInput, bytesRemaining, MCUXCLAES_BLOCK_SIZE);
        pCtx->common.blockBufferUsed = bytesRemaining;
    }
    /* Update total number of bytes that were encrypted */
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER_WITH_DATA_TYPE((pCtx->common.totalInputLength),uint32_t, 0u, (UINT32_MAX - inputLength), MCUXCLCIPHER_STATUS_ERROR)
    pCtx->common.totalInputLength += inputLength;

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipherModes_SkeletonAes_Process, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
            MCUX_CSSL_FP_CONDITIONAL((1u == processFPFlag_partData), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_CONDITIONAL((1u == processFPFlag_partDataHandling), pAlgo->protection_token_engine)),
            MCUX_CSSL_FP_CONDITIONAL((inLength >= MCUXCLAES_BLOCK_SIZE), pAlgo->protection_token_engine),
            MCUX_CSSL_FP_CONDITIONAL((0u != bytesRemaining), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_SkeletonAes_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipherModes_SkeletonAes_Finish(
    mcuxClSession_Handle_t session,
    mcuxClCipherModes_Context_Aes_Els_t *pCtx,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipherModes_SkeletonAes_Finish);

    /* Number of bytes of the padded block - also used to determine how much data to copy to the output,
       therefore it is initialized to the partial data length in case no padding is applied (CTR) . */
    uint32_t padOutLength = pCtx->common.blockBufferUsed;
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *pAlgo = (const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t *) pCtx->common.pMode->pAlgorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()

    /* Keep track of where we are in output */
    uint8_t * pOutput = (uint8_t *) pOut;

    /* Apply the padding function specified in the mode on the partial data. */
    MCUX_CSSL_FP_FUNCTION_CALL(addPaddingResult, pAlgo->addPadding(pAlgo->blockLength,
                                                           pCtx->blockBuffer,
                                                           pCtx->common.blockBufferUsed,
                                                           pCtx->common.totalInputLength,
                                                           pCtx->blockBuffer,
                                                           &padOutLength));

    if (MCUXCLPADDING_STATUS_OK != addPaddingResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Finish, MCUXCLCIPHER_STATUS_ERROR);
    }

    if (padOutLength > 0u)
    {
        /* If padding was added, process the data in the partial data buffer. */
        MCUX_CSSL_FP_FUNCTION_CALL(cipherResult2, pAlgo->cryptEngine(session,
                                                                    pCtx,
                                                                    pCtx->blockBuffer,
                                                                    MCUXCLAES_BLOCK_SIZE,
                                                                    pCtx->blockBuffer));
        if (cipherResult2 != MCUXCLCIPHER_STATUS_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Finish, MCUXCLCIPHER_STATUS_ERROR);
        }

        uint32_t removePaddingOutLength = 0u;
        /* Copy the encrypted last block to the output buffer */
        MCUX_CSSL_FP_FUNCTION_CALL(delPaddingResult, pAlgo->removePaddingEnc(pAlgo->blockLength,
                                                                     pCtx->blockBuffer,
                                                                     pCtx->common.blockBufferUsed,
                                                                     pOutput,
                                                                     &removePaddingOutLength));
        if (MCUXCLPADDING_STATUS_OK != delPaddingResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_SkeletonAes_Finish, MCUXCLCIPHER_STATUS_ERROR);
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("False Positive, *pOutLength will not overflow as it is checked by the caller")
        *pOutLength += removePaddingOutLength;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClCipherModes_SkeletonAes_Finish, MCUXCLCIPHER_STATUS_OK, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                  pAlgo->protection_token_addPadding,
                  MCUX_CSSL_FP_CONDITIONAL((padOutLength > 0u), pAlgo->protection_token_engine,
                                                               pAlgo->protection_token_removePaddingEnc));
}
