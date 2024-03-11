/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

#include <mcuxClToolchain.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHashModes_Internal.h>
#include <internal/mcuxClHashModes_Core_c_sha1.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <mcuxCsslAnalysis.h>


/**********************************************************
 * Defines and Macros
 **********************************************************/

/**********************************************************
 * Constants
 **********************************************************/

/**
 * @brief Sha-1 initialization vector
 */
const static uint32_t mcuxClHashModes_sha1_iv[] = {0x67452301u,
                                             0xEFCDAB89u,
                                             0x98BADCFEu,
                                             0x10325476u,
                                             0xC3D2E1F0u};

/**********************************************************
 * Helper functions
 **********************************************************/

/**********************************************************
 * *INTERNAL* layer functions
 **********************************************************/

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHashModes_C_oneShot_Sha1, mcuxClHash_AlgoSkeleton_OneShot_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHashModes_C_oneShot_Sha1 (
                                mcuxClSession_Handle_t session,
                                mcuxClHash_Algo_t algorithm UNUSED_PARAM,
                                mcuxCl_InputBuffer_t pIn,
                                uint32_t inSize,
                                mcuxCl_Buffer_t pOut,
                                uint32_t *const pOutSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHashModes_C_oneShot_Sha1);

    /**************************************************************************************
     * Step 1: Allocate buffers in workarea and initialize state
     **************************************************************************************/
    uint32_t *pState = mcuxClSession_allocateWords_cpuWa(session, MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLHASH_STATE_SIZE_SHA_1));
    if (NULL == pState)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_FAILURE);
    }

    uint32_t *pAccumulationBuffer = mcuxClSession_allocateWords_cpuWa(session, MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLHASH_BLOCK_SIZE_SHA_1));
    if (NULL == pAccumulationBuffer)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_FAILURE);
    }
    uint8_t *pAccumulationBytes = (uint8_t *) pAccumulationBuffer;

    /* Initialize state */
    MCUXCLMEMORY_FP_MEMORY_COPY(pState, (const uint8_t *)mcuxClHashModes_sha1_iv, MCUXCLHASH_STATE_SIZE_SHA_1);

    /**************************************************************************************
     * Step 2: Process full blocks of input data
     **************************************************************************************/
    uint32_t numberOfFullBlocks = inSize / MCUXCLHASH_BLOCK_SIZE_SHA_1;
    uint32_t offsetInputBuf = 0;

    while(0u < numberOfFullBlocks)
    {
        /* Copy input to accumulation buffer */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClBuffer_read(pIn, offsetInputBuf, pAccumulationBytes, MCUXCLHASH_BLOCK_SIZE_SHA_1));
        offsetInputBuf += MCUXCLHASH_BLOCK_SIZE_SHA_1;

        /* Switch endianness of words in accumulation buffer */
        mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pAccumulationBuffer, MCUXCLHASH_BLOCK_SIZE_SHA_1);

        /* Call core function */
        MCUX_CSSL_FP_FUNCTION_CALL(core_result1, mcuxClHashModes_core_c_sha1(pState, pAccumulationBuffer));
        if(MCUXCLHASH_STATUS_OK != core_result1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
        }

        numberOfFullBlocks--;
    }

    /**************************************************************************************
     * Step 3: Pad the input data and process last block
     **************************************************************************************/
    uint32_t sizeRemainingBlock = inSize & (MCUXCLHASH_BLOCK_SIZE_SHA_1 - 1u);

    /* Copy remaining input to accumulation buffer */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClBuffer_read(pIn, offsetInputBuf, pAccumulationBytes, sizeRemainingBlock));

    /* add first byte of the padding: (remaining) < (block length) so there is space in the buffer */
    pAccumulationBytes[sizeRemainingBlock] = 0x80u;
    sizeRemainingBlock++;

    uint32_t numberOfZeroBytes = MCUXCLHASH_BLOCK_SIZE_SHA_1 - sizeRemainingBlock;

    MCUX_CSSL_FP_COUNTER_STMT(const uint32_t  fpAdditionalPaddingBlock =
        (MCUXCLHASH_COUNTER_SIZE_SHA_1 > numberOfZeroBytes) ? 1u : 0u);

    /* Process partial padded block if needed */
    if(MCUXCLHASH_COUNTER_SIZE_SHA_1 > numberOfZeroBytes) // need room for 64 bit counter and one additional byte
    {
        /* Set remaining bytes in accumulation buffer to zero */
        MCUXCLMEMORY_FP_MEMORY_SET(&pAccumulationBytes[sizeRemainingBlock], 0x00u, numberOfZeroBytes);

        /* Switch endianness of words in accumulation buffer */
        mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pAccumulationBuffer, MCUXCLHASH_BLOCK_SIZE_SHA_1);

        /* Call core function */
        MCUX_CSSL_FP_FUNCTION_CALL(core_result2, mcuxClHashModes_core_c_sha1(pState, pAccumulationBuffer));
        if(MCUXCLHASH_STATUS_OK != core_result2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
        }

        numberOfZeroBytes = MCUXCLHASH_BLOCK_SIZE_SHA_1;
        sizeRemainingBlock = 0u;
    }

    /* Set remaining bytes in accumulation buffer to zero */
    MCUXCLMEMORY_FP_MEMORY_SET(&pAccumulationBytes[sizeRemainingBlock], 0x00u, numberOfZeroBytes);

    /* Perform padding by adding data counter - length is added from end of the array; byte-length is converted to bit-length */
    uint32_t counterEntry = MCUXCLHASH_BLOCK_SIZE_SHA_1;
    pAccumulationBytes[--counterEntry] = (uint8_t)(inSize <<  3u);
    pAccumulationBytes[--counterEntry] = (uint8_t)(inSize >>  5u);
    pAccumulationBytes[--counterEntry] = (uint8_t)(inSize >> 13u);
    pAccumulationBytes[--counterEntry] = (uint8_t)(inSize >> 21u);
    pAccumulationBytes[counterEntry - 1u] = (uint8_t)(inSize >> 29u);

    /* Switch endianness of words in accumulation buffer */
    mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pAccumulationBuffer, MCUXCLHASH_BLOCK_SIZE_SHA_1);

    /* Call core function to process last block */
    MCUX_CSSL_FP_FUNCTION_CALL(core_result3, mcuxClHashModes_core_c_sha1(pState, pAccumulationBuffer));
    if(MCUXCLHASH_STATUS_OK != core_result3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
    }

    /**************************************************************************************
     * Step 4: Copy result to output buffers
     **************************************************************************************/

    /* Switch endianness of words in state */
    mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pState, MCUXCLHASH_STATE_SIZE_SHA_1);

    /* Copy hash digest to output buffer */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClBuffer_write(pOut, 0, (uint8_t *) pState, MCUXCLHASH_OUTPUT_SIZE_SHA_1));

    /* Update output size */
    *pOutSize += MCUXCLHASH_OUTPUT_SIZE_SHA_1;

    /* Free workarea (pState and pAccumulationBuffer) */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLHASH_BLOCK_SIZE_SHA_1) + MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(MCUXCLHASH_STATE_SIZE_SHA_1));

    /* Set expectations and exit */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_oneShot_Sha1, MCUXCLHASH_STATUS_OK,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                            ((inSize / MCUXCLHASH_BLOCK_SIZE_SHA_1) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
                            ((inSize / MCUXCLHASH_BLOCK_SIZE_SHA_1) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read),
                            MCUX_CSSL_FP_CONDITIONAL((1u == fpAdditionalPaddingBlock),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHashModes_C_process_Sha1, mcuxClHash_AlgoSkeleton_Process_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHashModes_C_process_Sha1 (
                        mcuxClSession_Handle_t session UNUSED_PARAM,
                        mcuxClHash_Context_t pContext,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHashModes_C_process_Sha1);
    const mcuxClHash_AlgorithmDescriptor_t *algorithm = pContext->algo;
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pContext->processedLength, 0u);
    /* Initialize state with IV */
    if (0 == processedLengthNotZero)
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(mcuxClHash_getStatePtr(pContext), (const uint8_t *)mcuxClHashModes_sha1_iv, MCUXCLHASH_STATE_SIZE_SHA_1);
    }

    uint32_t offsetInputBuf = 0;
    /* Compute counter increase, considering the amount of unprocessed data now and at the end of this function. */
    uint32_t counterIncrease = (inSize + pContext->unprocessedLength) - ( (inSize + pContext->unprocessedLength) % algorithm->blockSize);
    mcuxClHash_processedLength_add(pContext->processedLength, counterIncrease);

    /* Verify that the processed length will not exceed the algorithm's maximum allowed length */
    uint8_t counterHighestByte = ((uint8_t *) pContext->processedLength)[algorithm->counterSize - 1u];
    if(0u != (counterHighestByte & algorithm->processedLengthCheckMask))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_process_Sha1, MCUXCLHASH_STATUS_FULL,
            MCUX_CSSL_FP_CONDITIONAL(0 == processedLengthNotZero, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
    }

    uint32_t *pUnprocessed = mcuxClHash_getUnprocessedPtr(pContext);
    uint8_t *pUnprocessedBytes = (uint8_t *) pUnprocessed;
    uint32_t *pState = mcuxClHash_getStatePtr(pContext);

    MCUX_CSSL_FP_COUNTER_STMT(const uint32_t  fpLoopCoreCalls =
        (0u < inSize) ? ((inSize + pContext->unprocessedLength) / MCUXCLHASH_BLOCK_SIZE_SHA_1) : 0u);
    /* One additional copy might be needed for new unprocessed data */
    MCUX_CSSL_FP_COUNTER_STMT(const uint32_t  fpLoopCopyOperations =
        ((0u != ((inSize + pContext->unprocessedLength) % MCUXCLHASH_BLOCK_SIZE_SHA_1)) && (0u < inSize)) ? fpLoopCoreCalls + 1u : fpLoopCoreCalls);

    /**************************************************************************************/
    /*                Process all whole blocks of input data                              */
    /**************************************************************************************/
    while(0u < inSize)
    {
        /* Take into account something might be already in unprocessed buffer */
        uint32_t dataToCopyLength = (inSize < (MCUXCLHASH_BLOCK_SIZE_SHA_1 - pContext->unprocessedLength)) ? inSize : (MCUXCLHASH_BLOCK_SIZE_SHA_1 - pContext->unprocessedLength);
        /* Copy input to accumulation buffer */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClBuffer_read(pIn, offsetInputBuf, pUnprocessedBytes + pContext->unprocessedLength, dataToCopyLength));

        /* Update counter / pContext data / input pointer */
        inSize -= dataToCopyLength;
        offsetInputBuf += dataToCopyLength;
        pContext->unprocessedLength += dataToCopyLength;
        /* When whole unprocessed buffer filled, process block and update pContext data*/
        if(pContext->unprocessedLength == MCUXCLHASH_BLOCK_SIZE_SHA_1)
        {
            /* Switch endianness of words in accumulation buffer */
            mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pUnprocessed, MCUXCLHASH_BLOCK_SIZE_SHA_1);

            /* Call core function */
            MCUX_CSSL_FP_FUNCTION_CALL(core_result1, mcuxClHashModes_core_c_sha1(pState, pUnprocessed));
            if(MCUXCLHASH_STATUS_OK != core_result1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_process_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
            }
            /*Data processed, nothing in the buffer,  state buffer updated*/
            pContext->unprocessedLength = 0u;
        }
    }

    /**************************************************************************************/
    /*                          Exit + FP balancing                                       */
    /**************************************************************************************/
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_process_Sha1, MCUXCLHASH_STATUS_OK,
        MCUX_CSSL_FP_CONDITIONAL(0 == processedLengthNotZero, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read) * fpLoopCopyOperations,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1) * fpLoopCoreCalls
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHashModes_C_finish_Sha1, mcuxClHash_AlgoSkeleton_Finish_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHashModes_C_finish_Sha1 (
                            mcuxClSession_Handle_t session UNUSED_PARAM,
                            mcuxClHash_Context_t pContext,
                            mcuxCl_Buffer_t pOut,
                            uint32_t *const pOutSize
                    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHashModes_C_finish_Sha1);

    const mcuxClHash_AlgorithmDescriptor_t *algorithm = pContext->algo;

    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pContext->processedLength, 0u);
    /* Initialize state with IV. Needed if process has never been called */
    if (0 == processedLengthNotZero)
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(mcuxClHash_getStatePtr(pContext), (const uint8_t *)mcuxClHashModes_sha1_iv, MCUXCLHASH_STATE_SIZE_SHA_1);
    }

    /* No further input to be added, processedLength can be updated now. Will be used for final length value attached inside padding */
    mcuxClHash_processedLength_add(pContext->processedLength, pContext->unprocessedLength);

    /* Verify that the processed length will not exceed the algorithm's maximum allowed length. */
    uint8_t counterHighestByte = ((uint8_t *) pContext->processedLength)[algorithm->counterSize - 1u];
    if(0u != (counterHighestByte & algorithm->processedLengthCheckMask))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_finish_Sha1, MCUXCLHASH_STATUS_FULL,
            MCUX_CSSL_FP_CONDITIONAL(0 == processedLengthNotZero, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
    }

    uint32_t *pUnprocessed = mcuxClHash_getUnprocessedPtr(pContext);
    uint8_t *pUnprocessedBytes = (uint8_t *) pUnprocessed;
    uint32_t *pState = mcuxClHash_getStatePtr(pContext);

    pUnprocessedBytes[pContext->unprocessedLength++] = 0x80u; //set first bit of padding

    uint32_t remainingBlockLength = MCUXCLHASH_BLOCK_SIZE_SHA_1 - (pContext->unprocessedLength);

    MCUX_CSSL_FP_COUNTER_STMT(const uint32_t  fpAdditionalPaddingBlock =
        (MCUXCLHASH_COUNTER_SIZE_SHA_1 > remainingBlockLength) ? 1u : 0u);

    if(MCUXCLHASH_COUNTER_SIZE_SHA_1 > remainingBlockLength) // need room for 64 bit counter
    {
        /* Set remaining bytes in accumulation buffer to zero */
        MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessedBytes + pContext->unprocessedLength, 0x00u, remainingBlockLength);

        /* Switch endianness of words in accumulation buffer */
        mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pUnprocessed, MCUXCLHASH_BLOCK_SIZE_SHA_1);

        /* Call core function */
        MCUX_CSSL_FP_FUNCTION_CALL(core_result1, mcuxClHashModes_core_c_sha1(pState, pUnprocessed));
        if(MCUXCLHASH_STATUS_OK != core_result1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_finish_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
        }
        remainingBlockLength = MCUXCLHASH_BLOCK_SIZE_SHA_1;
        pContext->unprocessedLength = 0u;
    }

    /* Set remaining bytes in accumulation buffer to zero */
    MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessedBytes + pContext->unprocessedLength, 0x00u, remainingBlockLength);

    /* Perform padding by adding data counter - length is added from end of the array; byte-length is converted to bit-length */
    mcuxClHash_processedLength_toBits(pContext->processedLength);
    for(uint32_t i = 0u; i < algorithm->counterSize; ++i)
    {
        pUnprocessedBytes[algorithm->blockSize - i - 1u] = ((uint8_t*)pContext->processedLength)[i];
    }

    /* Switch endianness of words in accumulation buffer */
    mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pUnprocessed, MCUXCLHASH_BLOCK_SIZE_SHA_1);

    /* Call core function to process last block */
    MCUX_CSSL_FP_FUNCTION_CALL(core_result2, mcuxClHashModes_core_c_sha1(pState, pUnprocessed));
    if(MCUXCLHASH_STATUS_OK != core_result2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_finish_Sha1, MCUXCLHASH_STATUS_FAULT_ATTACK);
    }

    /* Switch endianness word-wise, before copying result to output buffer. */
    mcuxClHashModes_internal_c_switchEndiannessOfBufferWords(pState, MCUXCLHASH_STATE_SIZE_SHA_1);

    /* Copy hash digest to output buffer */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClBuffer_write(pOut, 0, (uint8_t *) pState, MCUXCLHASH_OUTPUT_SIZE_SHA_1));

    *pOutSize += MCUXCLHASH_OUTPUT_SIZE_SHA_1;

    /* Clear context */
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *) pContext, MCUXCLHASH_CONTEXT_SIZE_SHA_1_IN_WORDS * sizeof(uint32_t));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHashModes_C_finish_Sha1, MCUXCLHASH_STATUS_OK,
                            MCUX_CSSL_FP_CONDITIONAL(0 == processedLengthNotZero, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                            MCUX_CSSL_FP_CONDITIONAL((1u == fpAdditionalPaddingBlock),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_core_c_sha1),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
                            );
}
/**********************************************************
 * Algorithm descriptor implementations
 **********************************************************/

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_C_Sha1 = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .oneShotSkeleton                  = mcuxClHashModes_C_oneShot_Sha1,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_C_oneShot_Sha1),
    .processSkeleton                  = mcuxClHashModes_C_process_Sha1,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_C_process_Sha1),
    .finishSkeleton                   = mcuxClHashModes_C_finish_Sha1,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHashModes_C_finish_Sha1),
    .processedLengthCheckMask         = MCUXCLHASH_PROCESSED_LENGTH_CHECK_MASK_SHA1,
    .blockSize                        = MCUXCLHASH_BLOCK_SIZE_SHA_1,
    .hashSize                         = MCUXCLHASH_OUTPUT_SIZE_SHA_1,
    .stateSize                        = MCUXCLHASH_STATE_SIZE_SHA_1,
    .counterSize                      = MCUXCLHASH_COUNTER_SIZE_SHA_1,
};
