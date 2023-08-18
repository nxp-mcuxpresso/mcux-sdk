/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

#include <mcuxClHash.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxClOsccaSm3.h>
#include <internal/mcuxClOsccaSm3_Internal.h>
#include <internal/mcuxClOsccaSm3_Core_sm3.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

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
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(uint32_t *workArea, uint32_t *stateBuff)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi);

    for(uint32_t i = 0; i < MCUXCLOSCCASM3_SGI_LOOP_SIZE; i++)
    {
        workArea[i] = (uint32_t)stateBuff[i];
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_Safo_Hash_PreLoad(workArea));
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_Safo_Hash_PreLoad));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_ProcessMessageBlock_Sgi(uint32_t *workArea, uint32_t *stateBuff, uint32_t *pInput)
{
   MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_ProcessMessageBlock_Sgi);

   MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_Safo_Hash_Auto(workArea, pInput));

   for(uint32_t i = 0u; i < MCUXCLOSCCASM3_SGI_LOOP_SIZE; i++)
   {
       stateBuff[i] = (uint32_t)workArea[i];
   }

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

    /* Check if enough space is available in CPU workarea */
    if((session->cpuWa.used + ((MCUXCLOSCCASM3_BLOCK_SIZE_SM3 + 2u * MCUXCLOSCCASM3_STATE_SIZE_SM3) / sizeof(uint32_t))) > session->cpuWa.size)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_FAILURE);
    }

    uint8_t *stateBuffer;
    /* MISRA Ex. 9 to Rule 11.3 */
    MCUX_CSSL_FP_FUNCTION_CALL(bufPrepRes1, mcuxClSession_allocateCpuBuffer(session, (uint32_t **)&stateBuffer, MCUXCLOSCCASM3_STATE_SIZE_SM3/sizeof(uint32_t)));
    if(MCUXCLSESSION_STATUS_OK != bufPrepRes1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_FAILURE);
    }
    uint8_t *accumulationBuffer;
    MCUX_CSSL_FP_FUNCTION_CALL(bufPrepRes2, mcuxClSession_allocateCpuBuffer(session, (uint32_t **)&accumulationBuffer, MCUXCLOSCCASM3_BLOCK_SIZE_SM3/sizeof(uint32_t)));
    if(MCUXCLSESSION_STATUS_OK != bufPrepRes2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_FAILURE);
    }
    uint32_t *workArea;
    MCUX_CSSL_FP_FUNCTION_CALL(bufPrepRes3, mcuxClSession_allocateCpuBuffer(session, (uint32_t **)&workArea, MCUXCLOSCCASM3_STATE_SIZE_SM3/sizeof(uint32_t)));
    if(MCUXCLSESSION_STATUS_OK != bufPrepRes3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_FAILURE);
    }

    /**************************************************************************************
     * Step 1: Initialize SAFO to perform Hash operation
     **************************************************************************************/

    /** \brief Global standard initialization vectors for SM3 */
    MCUXCLMEMORY_FP_MEMORY_COPY(stateBuffer, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);

    //Load initial IV to HW SM3
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)stateBuffer));

    /**************************************************************************************
    * Step 2: Process full blocks of input data
    **************************************************************************************/
    uint32_t inputLen = inSize;
    uint32_t updateLoopCount = 0u; //for flow protection
    const uint8_t *pInput = pIn;
    while((0U != inputLen) && (inputLen >= MCUXCLOSCCASM3_BLOCK_SIZE_SM3))
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(accumulationBuffer, pInput, MCUXCLOSCCASM3_BLOCK_SIZE_SM3);

        /* Switch endianess of words in accumulation buffer */
        /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)accumulationBuffer, MCUXCLOSCCASM3_BLOCK_SIZE_SM3));

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)stateBuffer, (uint32_t *)accumulationBuffer));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)stateBuffer));

        pInput += MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
        inputLen -= MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
        updateLoopCount++;
    }

    /**************************************************************************************
    * Step 3: Pad the input data and process last block
    **************************************************************************************/
    if(0U != inputLen)
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(accumulationBuffer, pInput, inputLen);
    }

    /* get the accumulation buffer index */
    uint32_t accumulationBufferIndex = inSize & (MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - 1U);

    /* Padding the last block, it's big endian */
    /* Set the first byte to 0x80*/
    accumulationBuffer[accumulationBufferIndex] = (uint8_t) (0x80U);
    accumulationBufferIndex++;

    /* then fill with zeros */
    MCUXCLMEMORY_FP_MEMORY_CLEAR(&accumulationBuffer[accumulationBufferIndex], MCUXCLOSCCASM3_BLOCK_SIZE_SM3 - accumulationBufferIndex);

    /* check if we can put the byte counter into this block */
    if((accumulationBufferIndex + 8U ) > MCUXCLOSCCASM3_BLOCK_SIZE_SM3)
    {
        /* need another block */
        /* Switch endianess of words in accumulation buffer */
        /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)accumulationBuffer, MCUXCLOSCCASM3_BLOCK_SIZE_SM3));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)stateBuffer, (uint32_t *)accumulationBuffer));
        MCUXCLMEMORY_FP_MEMORY_CLEAR(accumulationBuffer,MCUXCLOSCCASM3_BLOCK_SIZE_SM3);
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)stateBuffer));
    }

    /* Perform padding by adding data counter - length is added from end of the array; byte-length is converted to bit-length */
    uint32_t counterEntry = MCUXCLOSCCASM3_BLOCK_SIZE_SM3;
    accumulationBuffer[--counterEntry] = (uint8_t)(inSize <<  3u);
    accumulationBuffer[--counterEntry] = (uint8_t)(inSize >>  5u);
    accumulationBuffer[--counterEntry] = (uint8_t)(inSize >> 13u);
    accumulationBuffer[--counterEntry] = (uint8_t)(inSize >> 21u);
    accumulationBuffer[counterEntry - 1u] = (uint8_t)(inSize >> 29u);

    /* Switch endianess of words in accumulation buffer */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)accumulationBuffer, MCUXCLOSCCASM3_BLOCK_SIZE_SM3));

    /* Process the data in the accumulation buffer */
    /* Return code will be handled by Exit-Gate functionality within processMessageBlock */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)stateBuffer, (uint32_t *)accumulationBuffer));

    /**************************************************************************************
     * Step 4: Copy result to output buffers
     **************************************************************************************/
    /* Switch endianess of words in state buffer */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)stateBuffer, MCUXCLOSCCASM3_STATE_SIZE_SM3));
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, stateBuffer, algorithm->hashSize);

    MCUX_CSSL_FP_FUNCTION_CALL(free_result, mcuxClSession_freeAllCpuBuffers(session));

    if(MCUXCLSESSION_STATUS_OK != free_result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_FAILURE);
    }
    *pOutSize = algorithm->hashSize;
    /* Check the security counter value and the return code */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm3_sm3_oneShotSkeleton, MCUXCLHASH_STATUS_OK, MCUXCLHASH_STATUS_FAULT_ATTACK,
                                                     3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_allocateCpuBuffer),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi),
                                                     updateLoopCount * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
                                                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness)
                                                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)),
                                                     (0U != inputLen ? 1u : 0u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi),
                                                     2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness),
                                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_freeAllCpuBuffers),
                                                     ((accumulationBufferIndex + 8U ) > MCUXCLOSCCASM3_BLOCK_SIZE_SM3 ? 1u : 0u) *
                                                     (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
                                                     + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_sm3_processSkeleton, mcuxClHash_AlgoSkeleton_Process_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClOsccaSm3_sm3_processSkeleton (
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t pContext,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize)
{
    mcuxClHash_Context_t pSM3Ctx = pContext;
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pSM3Ctx->data.processedLength, 0, 0);
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_sm3_processSkeleton,
                (((processedLengthNotZero == 0) && (pContext->data.unprocessedLength == 0u)) ? (uint32_t)1u : (uint32_t)0u)
                  * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi));

    /* Buffer in CPU WA to store the middle block of data in the phase, if enough space available */
    if((session->cpuWa.used + (MCUXCLOSCCASM3_STATE_SIZE_SM3 / sizeof(uint32_t))) > session->cpuWa.size)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_processSkeleton, MCUXCLHASH_FAILURE);
    }
    uint32_t *workArea = (uint32_t*) &(session->cpuWa.buffer[session->cpuWa.used]);
    /**************************************************************************************
     * Step 1: Initialization - Calculate sizes, set pointers, and set initial IV,
       continuation from external state, or from internal state
     **************************************************************************************/
    /* MISRA Ex. 9 to Rule 11.3 */
    uint8_t *pInput = (uint8_t *)pIn;
    uint32_t inLength = inSize;
    uint8_t *pUnprocessed = pSM3Ctx->buffer.unprocessed;
    uint8_t *pState = pSM3Ctx->buffer.state;
    const size_t algoBlockSize = pSM3Ctx->algo->blockSize;

    /* Initialize state with IV */
    if((processedLengthNotZero == 0) && (pSM3Ctx->data.unprocessedLength == 0u))
    {
        /** \brief Global standard initialization vectors for SM3 */
        MCUXCLMEMORY_FP_MEMORY_COPY(pState, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);

    }
     /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)pState));

    /**************************************************************************************/
    /*                Process all whole blocks of input data                              */
    /**************************************************************************************/
    uint32_t loopTimes = 0u;
    uint32_t loopTimes1 = 0u;
    while(0u < inLength)
    {
        /* Take into account something might be already in unprocessed buffer */
        uint32_t dataToCopyLength = (inLength < (algoBlockSize - pSM3Ctx->data.unprocessedLength)) ? inLength : (algoBlockSize - pSM3Ctx->data.unprocessedLength);
        /* Copy input to accumulation buffer */
        /* Copy input to accumulation buffer */
        MCUXCLMEMORY_FP_MEMORY_COPY(pUnprocessed + pSM3Ctx->data.unprocessedLength, pInput, dataToCopyLength);

        /* Update counter / pSM3Ctx data / input pointer */
        inLength -= dataToCopyLength;
        pInput += dataToCopyLength;
        pSM3Ctx->data.unprocessedLength += dataToCopyLength;
        loopTimes++;
        /* When whole unprocessed buffer filled, process block and update pSM3Ctx data*/
        if(pSM3Ctx->data.unprocessedLength == algoBlockSize)
        {
            /* Switch endianess in accumulation buffer */
            /* Switch endianess of words in accumulation buffer */
            /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)pUnprocessed, algoBlockSize));
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)pState, (uint32_t *)pUnprocessed));
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)pState));

            /*Data processed, nothing in the buffer,  state buffer updated*/
            pSM3Ctx->data.unprocessedLength = 0u;
            /* Update byteCounter by adding algoBlockSize to it */
            mcuxClHash_processedLength_add(pSM3Ctx->data.processedLength, algoBlockSize);
            loopTimes1++;
        }
    }

    /**************************************************************************************/
    /*                          Exit + FP balancing                                       */
    /**************************************************************************************/

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_processSkeleton, MCUXCLHASH_STATUS_OK,
                loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                loopTimes1 * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)
                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness)));
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
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(pSM3Ctx->data.processedLength, 0, 0);
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_sm3_finishSkeleton,
               (((processedLengthNotZero == 0) && (pContext->data.unprocessedLength == 0u)) ? (uint32_t)1u : (uint32_t)0u)
                  * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi));

    /* No further input to be added, processedLength can be updated now. Will be used for final length value attached inside padding */
    /* Buffer in CPU WA to store the middle block of data in the phase, if enough space available */
    if((session->cpuWa.used + (MCUXCLOSCCASM3_STATE_SIZE_SM3 / sizeof(uint32_t))) > session->cpuWa.size)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_finishSkeleton, MCUXCLHASH_FAILURE);
    }
    uint32_t *workArea = (uint32_t*) &(session->cpuWa.buffer[session->cpuWa.used]);
    /* Initialize state with IV */
    if((processedLengthNotZero == 0) && (pSM3Ctx->data.unprocessedLength == 0u))
    {
        /** \brief Global standard initialization vectors for SM3 */
        MCUXCLMEMORY_FP_MEMORY_COPY(pSM3Ctx->buffer.state, (const uint8_t*)gkmcuxClOsccaSm3_SM3_IV, MCUXCLOSCCASM3_STATE_SIZE_SM3);
    }

    /* need preload Update phase prehash into HW SM3 */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)pSM3Ctx->buffer.state));

    mcuxClHash_processedLength_add(pSM3Ctx->data.processedLength, pSM3Ctx->data.unprocessedLength);

    uint8_t *pUnprocessed = pSM3Ctx->buffer.unprocessed;
    uint8_t *pState = pSM3Ctx->buffer.state;
    const size_t algoBlockSize = pSM3Ctx->algo->blockSize;
    pUnprocessed[pSM3Ctx->data.unprocessedLength++] = 0x80u; //set first bit of padding

    uint32_t remainingBlockLength = algoBlockSize - (pSM3Ctx->data.unprocessedLength);
    uint32_t loopTimes = 0U;
    if(MCUXCLOSCCASM3_COUNTER_SIZE_SM3 > remainingBlockLength) // need room for 64 bit counter
    {
        loopTimes++;
        /* Set remaining bytes in accumulation buffer to zero */
        MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessed + pSM3Ctx->data.unprocessedLength, 0x00u, remainingBlockLength);

        /* Switch endianess of words in accumulation buffer */
        /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)pUnprocessed, algoBlockSize));
        /* Call core function */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)pState, (uint32_t *)pUnprocessed));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi(workArea, (uint32_t *)pState));

        remainingBlockLength = algoBlockSize;
        pSM3Ctx->data.unprocessedLength = 0u;
    }

    /* Set remaining bytes in accumulation buffer to zero */
    MCUXCLMEMORY_FP_MEMORY_SET(pUnprocessed + pSM3Ctx->data.unprocessedLength, 0x00u, remainingBlockLength);

    /* Perform padding by adding data counter - length is added from end of the array; byte-length is converted to bit-length */
    uint32_t counterEntry = algoBlockSize;
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] <<  3u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >>  5u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 13u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 21u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 29u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 37u);
    pUnprocessed[--counterEntry] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 45u);
    pUnprocessed[counterEntry - 1u] = (uint8_t)(pSM3Ctx->data.processedLength[0] >> 53u);

    /* Switch endianess of words in accumulation buffer */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)pUnprocessed, algoBlockSize));

    /* Call core function to process last block */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_ProcessMessageBlock_Sgi(workArea, (uint32_t *)pState, (uint32_t *)pUnprocessed));

    /* Switch endianess of words in state buffer */
    /* MISRA Ex. 9 to Rule 11.3 - re-interpreting the memory */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm3_core_sm3_switch_endianness((uint32_t*)pState, MCUXCLOSCCASM3_STATE_SIZE_SM3));
    /* Copy hash digest to output buffer */
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, pState, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);
    *pOutSize += pSM3Ctx->algo->hashSize;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm3_sm3_finishSkeleton, MCUXCLHASH_STATUS_OK,
                            loopTimes * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set)
                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi)
                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_SetMessagePreLoadIV_Sgi)
                                        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_ProcessMessageBlock_Sgi),
                            2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm3_core_sm3_switch_endianness),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));

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
    .blockSize                        = MCUXCLOSCCASM3_BLOCK_SIZE_SM3,
    .hashSize                         = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3,
    .stateSize                        = MCUXCLOSCCASM3_STATE_SIZE_SM3,
    .counterSize                      = MCUXCLOSCCASM3_COUNTER_SIZE_SM3,
};
#endif /* MCUXCL_FEATURE_HASH_HW_SM3 */
