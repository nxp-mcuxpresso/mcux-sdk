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

#include <mcuxCsslAnalysis.h>
#include <mcuxClHash.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxClOsccaSm3.h>
#include <internal/mcuxClOsccaSm3_Internal.h>
#include <internal/mcuxClOsccaSm3_Core_sm3.h>
#include <mcuxClMemory.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>

static const uint32_t gkmcuxClOsccaSm3_SM3_IV[8] =  {0xb0fb0e4eU,
                                                    0xe38dee4dU,
                                                    0x163138aaU,
                                                    0xa96f30bcU,
                                                    0xda8a0600U,
                                                    0x172442d7U,
                                                    0x4914b2b9U,
                                                    0x7380166fU};

/**********************************************************
 * Helper functions
 **********************************************************/

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(uint32_t *stateBuff)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_Safo_Hash_PreLoad(stateBuff));
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_Safo_Hash_PreLoad));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_ProcessMessageBlock_Sgi(uint32_t *stateBuff, uint32_t *pInput)
{
   MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_ProcessMessageBlock_Sgi);

   MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_Safo_Hash_Auto(stateBuff, pInput));

   MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_Safo_Hash_Auto));
}

/**********************************************************
 * *INTERNAL* layer functions
 **********************************************************/

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_sm3_oneShotSkeleton, mcuxClHash_AlgoSkeleton_OneShot_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClOsccaSm3_sm3_oneShotSkeleton (
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Algo_t algorithm,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize,
                        mcuxCl_Buffer_t pOut,
                        uint32_t *const pOutSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_sm3_oneShotSkeleton);

    uint32_t *workArea = mcuxClSession_allocateWords_cpuWa(session,
                                    (MCUXCLOSCCASM3_STATE_SIZE_SM3 + MCUXCLOSCCASM3_BLOCK_SIZE_SM3) / sizeof(uint32_t));
    if(NULL == workArea)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_STATUS_FAILURE);
    }

    uint32_t *stateBuffer = &workArea[0];
    uint32_t *accumulationBuffer = &workArea[MCUXCLOSCCASM3_STATE_SIZE_SM3/sizeof(uint32_t)];

    /**************************************************************************************
     * Step 1: Initialize SAFO to perform Hash operation
     **************************************************************************************/

    /** \brief Global standard initialization vectors for SM3 */
    MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t*)stateBuffer, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);

    //Load initial IV to HW SM3
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(stateBuffer));

    /**************************************************************************************
    * Step 2: Process full blocks of input data
    **************************************************************************************/
    uint32_t inputLen = inSize;
    uint32_t inputOffset = 0u;
    uint32_t updateLoopCount = 0u; //for flow protection
    uint8_t *accumulationBuffByte = (uint8_t*)accumulationBuffer;

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(inputOffset, 0u, UINT32_MAX, MCUXCLHASH_STATUS_FAULT_ATTACK)
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(updateLoopCount, 0u, UINT32_MAX, MCUXCLHASH_STATUS_FAULT_ATTACK)

    while((0U != inputLen) && (inputLen >= MCUXCLOSCCASM3_BLOCK_SIZE_SM3))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read_reverse(pIn, inputOffset, accumulationBuffByte, MCUXCLOSCCASM3_BLOCK_SIZE_SM3));
        (void)statusBufferRead; // No need to check it because the function only returns OK.

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(stateBuffer, accumulationBuffer));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(stateBuffer));

        inputOffset += MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
        inputLen -= MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
        updateLoopCount++;
    }

    /**************************************************************************************
    * Step 3: Pad the input data and process last block
    **************************************************************************************/
    if(0U != inputLen)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read_reverse(pIn, inputOffset,
            &accumulationBuffByte[MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - inputLen], inputLen));
        (void)statusBufferRead; // No need to check it because the function only returns OK.
    }

    /* get the accumulation buffer index */
    uint32_t accumulationBufferIndex = inSize & (MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1U);

    /* Padding the last block, it's big endian */
    /* Set the first byte to 0x80*/
    accumulationBuffByte[(MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1U) - (accumulationBufferIndex)] = (uint8_t) (0x80U);
    accumulationBufferIndex++;

    /* then fill with zeros */
    MCUXCLMEMORY_FP_MEMORY_CLEAR(accumulationBuffByte, MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - accumulationBufferIndex);

    /* check if we can put the byte counter into this block */
    if((accumulationBufferIndex + 8U ) > MCUXCLOSCCASM3_BLOCK_SIZE_SM3)
    {
        /* need another block */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(stateBuffer, accumulationBuffer));
        MCUXCLMEMORY_FP_MEMORY_CLEAR(accumulationBuffByte,MCUXCLOSCCASM3_BLOCK_SIZE_SM3);
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(stateBuffer));
    }

    /* Perform padding by adding data counter - length is added from end of the array; byte-length is converted to bit-length */
    accumulationBuffByte[0u] = (uint8_t)(inSize <<  3u);
    accumulationBuffByte[1u] = (uint8_t)(inSize >>  5u);
    accumulationBuffByte[2u] = (uint8_t)(inSize >> 13u);
    accumulationBuffByte[3u] = (uint8_t)(inSize >> 21u);
    accumulationBuffByte[4u] = (uint8_t)(inSize >> 29u);

    /* Process the data in the accumulation buffer */
    /* Return code will be handled by Exit-Gate functionality within processMessageBlock */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(stateBuffer, accumulationBuffer));

    /**************************************************************************************
     * Step 4: Copy result to output buffers
     **************************************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write_reverse(pOut, 0u, (uint8_t*)stateBuffer, algorithm->hashSize));
    (void)statusBufferWrite; // No need to check it because the function only returns OK.

    mcuxClSession_freeWords_cpuWa(session, (MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + MCUXCLOSCCASM3_STATE_SIZE_SM3) / sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutSize properly to make sure not to wrap")
    *pOutSize = algorithm->hashSize;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    /* Check the security counter value and the return code */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_STATUS_OK, MCUXCLHASH_STATUS_FAULT_ATTACK,
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi),
                                                     updateLoopCount * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse)
                                                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)),
                                                     (0U != inputLen ? 1u : 0u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_reverse),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi),
                                                     ((accumulationBufferIndex + 8U ) > MCUXCLOSCCASM3_BLOCK_SIZE_SM3 ? 1u : 0u) *
                                                     (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_sm3_processSkeleton, mcuxClHash_AlgoSkeleton_Process_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClOsccaSm3_sm3_processSkeleton (
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t pContext,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_sm3_processSkeleton);

    mcuxClHash_Context_t pSM3Ctx = pContext;
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pSM3Ctx->processedLength, 0u);
    uint32_t unprocessedLen = pSM3Ctx->unprocessedLength;

    /**************************************************************************************
     * Step 1: Initialization - Calculate sizes, set pointers, and set initial IV,
       continuation from external state, or from internal state
     **************************************************************************************/
    uint32_t inLength = inSize;
    uint32_t inputOffset = 0u;
    uint32_t *pUnprocessed = mcuxClHash_getUnprocessedPtr(pSM3Ctx);
    uint8_t *pUnprocessedByte = (uint8_t*)pUnprocessed;
    uint32_t *pState = mcuxClHash_getStatePtr(pSM3Ctx);
    const size_t algoBlockSize = MCUXCLOSCCASM3_BLOCK_SIZE_SM3;

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pSM3Ctx->unprocessedLength, 0u, MCUXCLOSCCASM3_BLOCK_SIZE_SM3, MCUXCLHASH_STATUS_FAULT_ATTACK)
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(inputOffset, 0u, UINT32_MAX, MCUXCLHASH_STATUS_FAULT_ATTACK)

    /* Compute counter increase, considering the amount of unprocessed data now and at the end of this function. */
    uint32_t counterIncrease = (inSize + unprocessedLen) - ((inSize + unprocessedLen) % algoBlockSize);
    mcuxClHash_processedLength_add(pSM3Ctx->processedLength, counterIncrease);

    /* Verify that the processed length will not exceed the algorithm's maximum allowed length. */
    uint8_t counterHighestByte = ((uint8_t *) pSM3Ctx->processedLength)[pSM3Ctx->algo->counterSize - 1u];
    if(0u != (counterHighestByte & pSM3Ctx->algo->processedLengthCheckMask))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_processSkeleton, MCUXCLHASH_STATUS_FULL);
    }

    /* Initialize state with IV */
    if((processedLengthNotZero == 0) && (unprocessedLen == 0u))
    {
        /** \brief Global standard initialization vectors for SM3 */
        MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t*)pState, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);

    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(pState));

    /**************************************************************************************/
    /*                Process all whole blocks of input data                              */
    /**************************************************************************************/
    uint32_t loopTimes = 0u;
    uint32_t loopTimes1 = 0u;
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(loopTimes, 0u, UINT32_MAX, MCUXCLHASH_STATUS_FAULT_ATTACK)
    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(loopTimes1, 0u, UINT32_MAX, MCUXCLHASH_STATUS_FAULT_ATTACK)
    while(0u < inLength)
    {
        /* Take into account something might be already in unprocessed buffer */
        uint32_t dataToCopyLength = (inLength < (algoBlockSize - pSM3Ctx->unprocessedLength)) ? inLength : (algoBlockSize - pSM3Ctx->unprocessedLength);

        /* Copy input to accumulation buffer */
        MCUX_CSSL_FP_FUNCTION_CALL(statusBufferRead, mcuxClBuffer_read_reverse(pIn, inputOffset,
            pUnprocessedByte + algoBlockSize - pSM3Ctx->unprocessedLength - dataToCopyLength, dataToCopyLength));
        (void)statusBufferRead; // No need to check it because the function only returns OK.

        /* Update counter / pSM3Ctx data / input pointer */
        inLength -= dataToCopyLength;
        inputOffset += dataToCopyLength;
        pSM3Ctx->unprocessedLength += dataToCopyLength;
        loopTimes++;
        /* When whole unprocessed buffer filled, process block and update pSM3Ctx data*/
        if(pSM3Ctx->unprocessedLength == algoBlockSize)
        {
            /* Switch endianess in accumulation buffer */
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(pState, pUnprocessed));
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(pState));

            /*Data processed, nothing in the buffer,  state buffer updated*/
            pSM3Ctx->unprocessedLength = 0u;
            loopTimes1++;
        }
    }

    /**************************************************************************************/
    /*                          Exit + FP balancing                                       */
    /**************************************************************************************/
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_processSkeleton, MCUXCLHASH_STATUS_OK,
                (((processedLengthNotZero == 0) && (unprocessedLen == 0u)) ? (uint32_t)1u : (uint32_t)0u)
                  * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi),
                loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
                loopTimes1 * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_sm3_finishSkeleton, mcuxClHash_AlgoSkeleton_Finish_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClOsccaSm3_sm3_finishSkeleton (
                            mcuxClSession_Handle_t session,
                            mcuxClHash_Context_t pContext,
                            mcuxCl_Buffer_t pOut,
                            uint32_t *const pOutSize
)
{
    mcuxClHash_Context_t pSM3Ctx = pContext;
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_sm3_finishSkeleton);

    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pSM3Ctx->processedLength, 0u);
    uint32_t unprocessedLen = pSM3Ctx->unprocessedLength;

    /* No further input to be added, processedLength can be updated now. Will be used for final length value attached inside padding */
    uint32_t *pState = mcuxClHash_getStatePtr(pSM3Ctx);
    /* Initialize state with IV */
    if((processedLengthNotZero == 0) && (unprocessedLen == 0u))
    {
        /** \brief Global standard initialization vectors for SM3 */
        MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t*)pState, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);
    }

    /* need preload Update phase prehash into HW SM3 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(pState));

    mcuxClHash_processedLength_add(pSM3Ctx->processedLength, pSM3Ctx->unprocessedLength);

    /* Verify that the processed length will not exceed the algorithm's maximum allowed length. */
    uint8_t counterHighestByte = ((uint8_t *) pSM3Ctx->processedLength)[pSM3Ctx->algo->counterSize - 1u];
    if(0u != (counterHighestByte & pSM3Ctx->algo->processedLengthCheckMask))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_finishSkeleton, MCUXCLHASH_STATUS_FULL,
                            ((((processedLengthNotZero == 0) && (unprocessedLen == 0u)) ? (uint32_t)1u : (uint32_t)0u)
                                      * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi));
    }

    MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pSM3Ctx->unprocessedLength, 0u, MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1u, MCUXCLHASH_STATUS_FAULT_ATTACK)

    uint32_t *pUnprocessed = mcuxClHash_getUnprocessedPtr(pSM3Ctx);
    uint8_t *pUnprocessedByte = (uint8_t *)pUnprocessed;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("the max value of pSM3Ctx->unprocessedLength is MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1U.")
    pUnprocessedByte[(MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1U) - (pSM3Ctx->unprocessedLength)] = 0x80u; //set first bit of padding
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    pSM3Ctx->unprocessedLength++;

    uint32_t remainingBlockLength = MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - (pSM3Ctx->unprocessedLength);
    uint32_t loopTimes = 0U;
    if(MCUXCLOSCCASM3_COUNTER_SIZE_SM3 > remainingBlockLength) // need room for 64 bit counter
    {
        loopTimes++;
        /* Set remaining bytes in accumulation buffer to zero */
        MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessedByte, 0x00u, remainingBlockLength);

        /* Call core function */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(pState, pUnprocessed));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(pState));

        remainingBlockLength = MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
        pSM3Ctx->unprocessedLength = 0u;
    }

    /* Set remaining bytes in accumulation buffer to zero */
    MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessedByte, 0x00u, remainingBlockLength);

    /* Perform padding by adding data counter - length is added from start of the array; byte-length is converted to bit-length */
    mcuxClHash_processedLength_toBits(pSM3Ctx->processedLength);
    for(uint32_t i = 0u; i < pSM3Ctx->algo->counterSize; ++i)
    {
        pUnprocessedByte[i] = ((uint8_t*)pSM3Ctx->processedLength)[i];
    }

    /* Call core function to process last block */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(pState, pUnprocessed));

    /* Switch endianess of words in state buffer */
    /* Copy hash digest to output buffer */
    MCUX_CSSL_FP_FUNCTION_CALL(statusBufferWrite, mcuxClBuffer_write_reverse(pOut, 0u, (uint8_t*)pState, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
    (void)statusBufferWrite; // No need to check it because the function only returns OK.

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutSize properly to make sure not to wrap")
    *pOutSize += pSM3Ctx->algo->hashSize;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_finishSkeleton, MCUXCLHASH_STATUS_OK,
                            ((((processedLengthNotZero == 0) && (unprocessedLen == 0u)) ? (uint32_t)1u : (uint32_t)0u)
                                      * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi),
                            loopTimes * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set)
                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_reverse));

}

/**********************************************************
 * Algorithm descriptor implementations
 **********************************************************/

#ifdef MCUXCL_FEATURE_HASH_HW_SM3
const mcuxClHash_AlgorithmDescriptor_t mcuxClOsccaSm3_AlgorithmDescriptor_Sm3 = {
    .oneShotSkeleton                  = mcuxClOsccaSm3_sm3_oneShotSkeleton,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_sm3_oneShotSkeleton),
    .processSkeleton                  = mcuxClOsccaSm3_sm3_processSkeleton,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_sm3_processSkeleton),
    .finishSkeleton                   = mcuxClOsccaSm3_sm3_finishSkeleton,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_sm3_finishSkeleton),
    .processedLengthCheckMask         = MCUXCLOSCCASM3_PROCESSED_LENGTH_CHECK_MASK,
    .blockSize                        = MCUXCLOSCCASM3_BLOCK_SIZE_SM3,
    .hashSize                         = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3,
    .stateSize                        = MCUXCLOSCCASM3_STATE_SIZE_SM3,
    .counterSize                      = MCUXCLOSCCASM3_COUNTER_SIZE_SM3,
};
#endif /* MCUXCL_FEATURE_HASH_HW_SM3 */
