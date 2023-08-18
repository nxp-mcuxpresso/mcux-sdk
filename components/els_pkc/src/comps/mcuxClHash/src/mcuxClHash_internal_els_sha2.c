/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
#include <internal/mcuxClHash_Core_els_sha2.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEls.h>
#include <internal/mcuxClSession_Internal.h>
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
#include <mcuxClPkc_Types.h>
#include <internal/mcuxClPkc_Macros.h>
#endif

/**********************************************************
 * Helper functions
 **********************************************************/

/* Writes the correct RTF flags to the hashOptions struct, based on the rtf parameter */
static inline mcuxClHash_Status_t mcuxClHash_els_selectRtfFlags(mcuxClSession_Rtf_t rtf,
                                                              mcuxClEls_HashOption_t *hashOptions)
{
    /* Set RTF processing options */
    if(MCUXCLSESSION_RTF_UPDATE_TRUE == rtf)
    {
        hashOptions->bits.rtfupd = MCUXCLELS_HASH_RTF_UPDATE_ENABLE;
    }
    else if(MCUXCLSESSION_RTF_UPDATE_FALSE == rtf)
    {
        hashOptions->bits.rtfupd = MCUXCLELS_HASH_RTF_UPDATE_DISABLE;
    }
    else
    {
        return MCUXCLHASH_FAILURE;
    }
    return MCUXCLHASH_STATUS_OK;
}

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_els_dmaProtectionAddressReadback)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_els_dmaProtectionAddressReadback(uint8_t * startAddress,
                                                                                             size_t expectedLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_els_dmaProtectionAddressReadback,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_CompareDmaFinalOutputAddress));

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClEls_CompareDmaFinalOutputAddress(startAddress, expectedLength));

    if (MCUXCLELS_STATUS_OK != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_dmaProtectionAddressReadback, MCUXCLHASH_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_dmaProtectionAddressReadback, MCUXCLHASH_STATUS_OK);
}
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */


/**********************************************************
 * *INTERNAL* layer functions
 **********************************************************/

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_els_oneShotSkeleton_sha2, mcuxClHash_AlgoSkeleton_OneShot_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_els_oneShotSkeleton_sha2 (
                                    mcuxClSession_Handle_t session,
                                    mcuxClHash_Algo_t algorithm,
                                    mcuxCl_InputBuffer_t pIn,
                                    uint32_t inSize,
                                    mcuxCl_Buffer_t pOut,
                                    uint32_t *const pOutSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_els_oneShotSkeleton_sha2);

#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
    const bool isInputInPKC =
         (((uint32_t) pIn + inSize)> (uint32_t) MCUXCLPKC_RAM_START_ADDRESS)
         && ((uint32_t) pIn < ((uint32_t) MCUXCLPKC_RAM_START_ADDRESS + MCUXCLPKC_RAM_SIZE));
#endif

    /**************************************************************************************
     * Step 1: Set ELS options for initialization, continuation from external state, or from
     * internal state
     **************************************************************************************/

    /* Start setting initial options for ELS hash */
    mcuxClEls_HashOption_t hash_options = algorithm->hashOptions;
    hash_options.bits.hashoe = MCUXCLELS_HASH_OUTPUT_DISABLE;
    hash_options.bits.hashini = MCUXCLELS_HASH_INIT_ENABLE;
    hash_options.bits.hashld  = MCUXCLELS_HASH_LOAD_DISABLE;

    /* Set RTF processing options */
    if(MCUXCLHASH_STATUS_OK != mcuxClHash_els_selectRtfFlags(session->rtf, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, MCUXCLHASH_FAILURE);
    }

    /**************************************************************************************
     * Step 2: Process full blocks of input data
     **************************************************************************************/

    /* All blocks can be processed in bulk directly from in */
    size_t const sizeOfFullBlocks = (inSize / algorithm->blockSize) * algorithm->blockSize;

    if (0u < sizeOfFullBlocks)
    {
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
        /* Check if pIn is in PKC workarea. */
        if (false != isInputInPKC)
        {
            /* Allocate buffer in CPU WA to copy the input block of data from PKC WA */
            uint8_t * pInCpu = (uint8_t *) mcuxClSession_allocateWords_cpuWa(session, algorithm->blockSize / sizeof(uint32_t));
            size_t processedIn = 0u;
            while(processedIn < sizeOfFullBlocks)
            {
                MCUXCLMEMORY_FP_MEMORY_COPY(pInCpu, &pIn[processedIn], algorithm->blockSize);
                MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, algorithm->els_core(hash_options.word.value,
                                                               pInCpu,
                                                               algorithm->blockSize,
                                                               NULL));
                hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;

                if (MCUXCLHASH_STATUS_OK != resultElsCore)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
                }
                processedIn += algorithm->blockSize;
            }
            /* Free workarea (pInCpu) */
            mcuxClSession_freeWords_cpuWa(session, algorithm->blockSize / sizeof(uint32_t));
        }
        else
        {
            MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, algorithm->els_core(hash_options.word.value,
                                                           pIn,
                                                           sizeOfFullBlocks,
                                                           NULL));
            if (MCUXCLHASH_STATUS_OK != resultElsCore)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
            }

            hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        }
#else
        MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, algorithm->els_core(hash_options.word.value,
                                                       pIn,
                                                       sizeOfFullBlocks,
                                                       NULL));
        if (MCUXCLHASH_STATUS_OK != resultElsCore)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
        }
        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
#endif
    }

    /**************************************************************************************
     * Step 3: Padd the input data and process last block
     **************************************************************************************/

    /* Buffer in CPU WA to store the last block of data in the finalization phase */
    uint8_t *shablock = (uint8_t *) mcuxClSession_allocateWords_cpuWa(session, algorithm->blockSize / sizeof(uint32_t));
    if(NULL == shablock)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, MCUXCLHASH_FAILURE);
    }
    size_t posdst = inSize - sizeOfFullBlocks;
    size_t buflen = algorithm->blockSize;

    /* Copy the data to the buffer in the workspace. */
    MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(shablock, &pIn[sizeOfFullBlocks], posdst, buflen);


    buflen -= posdst;

    /* add first byte of the padding: (remaining) < (block length) so there is space in the buffer */
    shablock[posdst] = 0x80u;
    posdst += 1u;
    buflen -= 1u;

    /* Process partial padded block if needed */
    if ( (algorithm->blockSize - algorithm->counterSize) < posdst ) // need room for 64 bit counter and one additional byte
    {
        MCUXCLMEMORY_FP_MEMORY_SET(&shablock[posdst], 0x00, buflen);

        /* It is currently necessary to set buflen to algorithm->blockSize to distinguish whether this if-branch was taken
         * (for the conditional expectations in the exit statement!). Otherwise we could set it to posdst here and save
         * some performance overhead */
        buflen = algorithm->blockSize;
        posdst = 0u;

        MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, algorithm->els_core(hash_options.word.value,
                                                              shablock,
                                                              algorithm->blockSize,
                                                              NULL));

        if (MCUXCLHASH_STATUS_OK != resultElsCore)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
        }

        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
    }

    /* Perform padding by adding data counter */
    MCUXCLMEMORY_FP_MEMORY_SET(&shablock[posdst], 0x00, buflen);
    posdst = algorithm->blockSize;
    shablock[--posdst] = (uint8_t)(inSize <<  3u);
    shablock[--posdst] = (uint8_t)(inSize >>  5u);
    shablock[--posdst] = (uint8_t)(inSize >> 13u);
    shablock[--posdst] = (uint8_t)(inSize >> 21u);
    shablock[posdst-1u] = (uint8_t)(inSize >> 29u);

    /* Set output options */
    hash_options.bits.hashoe  = MCUXCLELS_HASH_OUTPUT_ENABLE;
    hash_options.bits.rtfoe = hash_options.bits.rtfupd;

    /* Process last block */
    MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, algorithm->els_core(hash_options.word.value,
                                                 shablock,
                                                 algorithm->blockSize,
                                                 shablock /* shablock is large enough to hold internal state of hash algorithm + RTF */));

    if (MCUXCLHASH_STATUS_OK != resultElsCore)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
    }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    uint32_t rtfSize = 0;
    rtfSize = (MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf) ? algorithm->rtfSize : 0u;
    if(NULL != algorithm->dmaProtection)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(resultDma, algorithm->dmaProtection(shablock,
                                                                      algorithm->stateSize + rtfSize));

        if (MCUXCLHASH_STATUS_OK != resultDma)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultDma);
        }
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    /**************************************************************************************
     * Step 4: Copy result to output buffers
     **************************************************************************************/

    /* Copy RTF to corresponding buffer */
    if((MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf) && (NULL != session->pRtf))
    {
        MCUXCLMEMORY_FP_MEMORY_COPY(session->pRtf, &shablock[algorithm->hashSize], algorithm->rtfSize);
    }

    /* Copy hash digest to output buffer */
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, shablock, algorithm->hashSize);
    *pOutSize += algorithm->hashSize;

    /* Free workarea (shablock) */
    mcuxClSession_freeWords_cpuWa(session, algorithm->blockSize / sizeof(uint32_t));

    /* Set expectations and exit */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, MCUXCLHASH_STATUS_OK,
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
                            MCUX_CSSL_FP_CONDITIONAL((0u != sizeOfFullBlocks),
                              MCUX_CSSL_FP_CONDITIONAL(false != isInputInPKC,
                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), algorithm->protection_token_els_core) *
                                 (sizeOfFullBlocks / algorithm->blockSize),
                            MCUX_CSSL_FP_CONDITIONAL(false == isInputInPKC,
                                 algorithm->protection_token_els_core)),
#else
                            MCUX_CSSL_FP_CONDITIONAL((0u != sizeOfFullBlocks), algorithm->protection_token_els_core),
#endif
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                            MCUX_CSSL_FP_CONDITIONAL((buflen == algorithm->blockSize), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), algorithm->protection_token_els_core),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                            (algorithm->protection_token_els_core),
                            #ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
                            (algorithm->protection_token_dma_protection),
                            #endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
                            MCUX_CSSL_FP_CONDITIONAL((MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf),  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_els_process_sha2, mcuxClHash_AlgoSkeleton_Process_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_els_process_sha2 (
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t context,
                        mcuxCl_InputBuffer_t pIn,
                        uint32_t inSize)
{

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_els_process_sha2);

    /**************************************************************************************
     * Step 1: Initialization - Calculate sizes, set pointers, and set ELS options for
     * initialization, continuation from external state, or from internal state
     **************************************************************************************/

    /* Total length of data to be processed */
    size_t unprocessedTotalLength = context->data.unprocessedLength + inSize;

    const mcuxClHash_AlgorithmDescriptor_t * pAlgoDesc = context->algo;
    const size_t algoBlockSize = context->algo->blockSize;
    /* The amount of unprocessed data that fills complete blocks */
    size_t  unprocessedCompleteBlockLength = (unprocessedTotalLength / algoBlockSize) * (algoBlockSize);

    /* Need to store the initial values of these variables for correct calculation of flow protection values at the end of the function */
    MCUX_CSSL_FP_COUNTER_STMT(const size_t initialUnprocessedCompleteBlockLength = unprocessedCompleteBlockLength);
    MCUX_CSSL_FP_COUNTER_STMT(const size_t initialUnprocessedContextLength = context->data.unprocessedLength);

#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
    const bool isInputInPKC =
        (((uint32_t) pIn + inSize) > (uint32_t) MCUXCLPKC_RAM_START_ADDRESS)
        && ((uint32_t) pIn < ((uint32_t) MCUXCLPKC_RAM_START_ADDRESS + MCUXCLPKC_RAM_SIZE));
#endif

    /* Pointer to the buffer where the state is stored. Either it ends up in the work area, or in the state buffer of the context */
    uint8_t *partialdigest = context->buffer.state;

    /* Input pointer that changes throughout the function */
    const uint8_t *pInput = (const uint8_t *)pIn;
    /* Start setting initial options for ELS hash */
    mcuxClEls_HashOption_t hash_options = pAlgoDesc->hashOptions;
    hash_options.bits.hashoe = MCUXCLELS_HASH_OUTPUT_ENABLE;
    hash_options.bits.hashini = MCUXCLELS_HASH_INIT_ENABLE;
    hash_options.bits.hashld  = MCUXCLELS_HASH_LOAD_DISABLE;


    /**************************************************************************************
     * Step 2: Load state (partial digest), if data had been processed before
     **************************************************************************************/

    /* Set hash init/load flags depending on whether there is a valid state to load or not */
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(context->data.processedLength, 0, 0);
    if(0 != processedLengthNotZero)
    {
        /* There is already a valid state in the context -> load state from context */
        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        hash_options.bits.hashld  = MCUXCLELS_HASH_LOAD_ENABLE;
    }

    /* Set RTF processing options */
    if(MCUXCLHASH_STATUS_OK != mcuxClHash_els_selectRtfFlags(session->rtf, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, MCUXCLHASH_FAILURE);
    }

    /**************************************************************************************
     * Step 3: Process full blocks
     **************************************************************************************/

    /* The first block can either be completely in `pInput`, or partially in the context buffer. */
    if((0u != unprocessedCompleteBlockLength) && (0u != context->data.unprocessedLength))
    {
        /* There is some data in the context buffer. Append enough data from `pInput` to complete a block. */
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(context->buffer.unprocessed + context->data.unprocessedLength,
                                                                    pInput,
                                                                    algoBlockSize - context->data.unprocessedLength,
                                                                    sizeof(context->buffer.unprocessed) - context->data.unprocessedLength);
        MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                          context->buffer.unprocessed,
                                                          algoBlockSize,
                                                          partialdigest));

        if (MCUXCLHASH_STATUS_OK != resultElsCore)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, resultElsCore);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        if(NULL != pAlgoDesc->dmaProtection)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(resultDma, pAlgoDesc->dmaProtection(partialdigest, pAlgoDesc->stateSize));

            if (MCUXCLHASH_STATUS_OK != resultDma)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, resultDma);
            }
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        hash_options.bits.hashld = MCUXCLELS_HASH_LOAD_DISABLE;

        pInput += algoBlockSize - context->data.unprocessedLength;

        mcuxClHash_processedLength_add(context->data.processedLength, algoBlockSize);
        context->data.unprocessedLength = 0u;

        unprocessedCompleteBlockLength -= algoBlockSize;
        unprocessedTotalLength -= algoBlockSize;
    }

    /* At this point, there is no more data in the context buffer, so remaining blocks can be processed in bulk directly from pIn */
    if (0u != unprocessedCompleteBlockLength)
    {
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
        /* Check pInput is in PKC workarea. */
        if (false != isInputInPKC)
        {
            size_t processedIn = 0u;
            while(processedIn < unprocessedCompleteBlockLength)
            {
                /* Copy block of the input data in the context buffer. */
                MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(context->buffer.unprocessed,
                                                                            &pInput[processedIn],
                                                                            algoBlockSize,
                                                                            sizeof(context->buffer.unprocessed));

                MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                               context->buffer.unprocessed,
                                                               algoBlockSize,
                                                               partialdigest));
                if (MCUXCLHASH_STATUS_OK != resultElsCore)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_oneShotSkeleton_sha2, resultElsCore);
                }
                processedIn += algoBlockSize;
                
                hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
                hash_options.bits.hashld = MCUXCLELS_HASH_LOAD_DISABLE;
            }
        }
        else
        {
            MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                              pInput,
                                                              unprocessedCompleteBlockLength,
                                                              partialdigest));

            if (MCUXCLHASH_STATUS_OK != resultElsCore)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, resultElsCore);
            }

        }
#else
        MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                          pInput,
                                                          unprocessedCompleteBlockLength,
                                                          partialdigest));

        if (MCUXCLHASH_STATUS_OK != resultElsCore)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, resultElsCore);
        }
#endif

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        if(NULL != pAlgoDesc->dmaProtection)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(resultDma, pAlgoDesc->dmaProtection(partialdigest, pAlgoDesc->stateSize));

            if (MCUXCLHASH_STATUS_OK != resultDma)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, resultDma);
            }
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        hash_options.bits.hashld = MCUXCLELS_HASH_LOAD_DISABLE;

        pInput += unprocessedCompleteBlockLength;

        mcuxClHash_processedLength_add(context->data.processedLength, unprocessedCompleteBlockLength);

        unprocessedTotalLength -= unprocessedCompleteBlockLength;
    }

    /**************************************************************************************
     * Step 4: Process incomplete blocks
     **************************************************************************************/

    if(0u < unprocessedTotalLength)
    {
        /* Append data from `pInput` to accumulation buffer. */
        MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF(context->buffer.unprocessed + context->data.unprocessedLength,
                                                                    pInput,
                                                                    (unprocessedTotalLength - context->data.unprocessedLength),
                                                                    sizeof(context->buffer.unprocessed) - context->data.unprocessedLength);
        context->data.unprocessedLength = unprocessedTotalLength;

    }

    /**************************************************************************************
     * Step 5: Exit
     **************************************************************************************/

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_process_sha2, MCUXCLHASH_STATUS_OK,
                           MCUX_CSSL_FP_CONDITIONAL((0u != initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength),
                                                   pAlgoDesc->protection_token_els_core,
                                                   #ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
                                                   pAlgoDesc->protection_token_dma_protection,
                                                   #endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
                                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                           MCUX_CSSL_FP_CONDITIONAL((((0u != initialUnprocessedCompleteBlockLength) && (0u == initialUnprocessedContextLength)) || ((algoBlockSize < initialUnprocessedCompleteBlockLength) && (0u != initialUnprocessedContextLength))),
                                                   #ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
                                                   pAlgoDesc->protection_token_dma_protection,
                                                   #endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
                                                   MCUX_CSSL_FP_CONDITIONAL(false != isInputInPKC,
                                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                                                           pAlgoDesc->protection_token_els_core)
                                                                           * initialUnprocessedCompleteBlockLength / algoBlockSize,
                                                   MCUX_CSSL_FP_CONDITIONAL(false == isInputInPKC,
                                                                           pAlgoDesc->protection_token_els_core)),
#else

                                                   pAlgoDesc->protection_token_els_core),
#endif
                           MCUX_CSSL_FP_CONDITIONAL((0u < unprocessedTotalLength),
                                                   (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy))));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHash_els_finish_sha2, mcuxClHash_AlgoSkeleton_Finish_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClHash_Status_t) mcuxClHash_els_finish_sha2 (
                        mcuxClSession_Handle_t session,
                        mcuxClHash_Context_t context,
                        mcuxCl_Buffer_t pOut,
                        uint32_t *const pOutSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHash_els_finish_sha2);

    /**************************************************************************************
     * Step 1: Initialization - Calculate sizes, set pointers, and set ELS options for
     * initialization, continuation from external state, or from internal state
     **************************************************************************************/

    if(NULL == pOut)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, MCUXCLHASH_STATUS_INVALID_PARAMS);
    }

    /* Pointer to the buffer where the state is stored. Either it ends up in the work area, or in the state buffer of the context */
    uint8_t *partialdigest = context->buffer.state;

    /* Start setting initial options for ELS hash */
    const mcuxClHash_AlgorithmDescriptor_t *pAlgoDesc = context->algo;
    mcuxClEls_HashOption_t hash_options = pAlgoDesc->hashOptions;
    hash_options.bits.hashoe = MCUXCLELS_HASH_OUTPUT_ENABLE;
    hash_options.bits.hashini = MCUXCLELS_HASH_INIT_ENABLE;
    hash_options.bits.hashld  = MCUXCLELS_HASH_LOAD_DISABLE;

    /* Set RTF processing options */
    if(MCUXCLHASH_STATUS_OK != mcuxClHash_els_selectRtfFlags(session->rtf, &hash_options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, MCUXCLHASH_FAILURE);
    }

    /**************************************************************************************
     * Step 2: Load state (partial digest), if data had been processed before
     **************************************************************************************/

    /* Set hash init/load flags depending on whether there is a valid state to load or not */
    int32_t processedLengthNotZero = mcuxClHash_processedLength_cmp(context->data.processedLength, 0, 0);
    if(0 != processedLengthNotZero)
    {
        /* There is already a valid state in the context -> load state from context */
        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        hash_options.bits.hashld  = MCUXCLELS_HASH_LOAD_ENABLE;
    }

    /**************************************************************************************
     * Step 3: Padd data and process last block
     **************************************************************************************/

    /* Pointer to the buffer where the last block of data is stored in the finalization phase */
    uint8_t *shablock = context->buffer.unprocessed;

    /* Buffer in CPU WA to store the digest and RTF output in the finalization phase */
    uint8_t *pOutput = (uint8_t *) mcuxClSession_allocateWords_cpuWa(session, (pAlgoDesc->stateSize + pAlgoDesc->rtfSize) / sizeof(uint32_t));
    if(NULL == pOutput)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, MCUXCLHASH_FAILURE);
    }

    size_t posdst, buflen;
    buflen = pAlgoDesc->blockSize - context->data.unprocessedLength;
    posdst  = context->data.unprocessedLength;

    // add first byte of the padding: (remaining) < (block length) so there is space in the buffer
    shablock[posdst] = 0x80u;
    posdst += 1u;
    buflen -= 1u;

    /* Process partial padded block if needed */
    if (pAlgoDesc->blockSize - pAlgoDesc->counterSize - 1u < context->data.unprocessedLength) // need room for 64 bit counter and one additional byte
    {
        MCUXCLMEMORY_FP_MEMORY_SET(shablock + posdst, 0x00u, buflen);
        buflen = pAlgoDesc->blockSize;
        posdst = 0u;

        MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                         shablock,
                                                         pAlgoDesc->blockSize,
                                                         partialdigest));

        if (MCUXCLHASH_STATUS_OK != resultElsCore)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, resultElsCore);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        if(NULL != pAlgoDesc->dmaProtection)
        {
            MCUX_CSSL_FP_FUNCTION_CALL(resultDma, pAlgoDesc->dmaProtection(partialdigest, pAlgoDesc->stateSize));

            if (MCUXCLHASH_STATUS_OK != resultDma)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, resultDma);
            }
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        hash_options.bits.hashini = MCUXCLELS_HASH_INIT_DISABLE;
        hash_options.bits.hashld = MCUXCLELS_HASH_LOAD_ENABLE;
    }

    /* Perform padding by adding data counter */
    MCUXCLMEMORY_FP_MEMORY_SET(shablock + posdst, 0x00u, buflen);

    posdst = pAlgoDesc->blockSize;
    mcuxClHash_processedLength_add(context->data.processedLength, context->data.unprocessedLength);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] <<  3u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >>  5u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 13u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 21u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 29u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 37u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 45u);
    shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 53u);
    if (context->algo->counterSize > 8u)
    {
        shablock[--posdst] = (uint8_t)(context->data.processedLength[0] >> 61u) |
            (uint8_t)(context->data.processedLength[1] << 5u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >>  5u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 13u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 21u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 29u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 37u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 45u);
        shablock[--posdst] = (uint8_t)(context->data.processedLength[1] >> 53u);
    }
    hash_options.bits.hashoe  = MCUXCLELS_HASH_OUTPUT_ENABLE;

    MCUXCLMEMORY_FP_MEMORY_COPY(pOutput, partialdigest, pAlgoDesc->stateSize);

    /* Set RTF processing options */
    hash_options.bits.rtfoe = hash_options.bits.rtfupd;

    /* Process last block */
    MCUX_CSSL_FP_FUNCTION_CALL(resultElsCore, pAlgoDesc->els_core(hash_options.word.value,
                                                      shablock,
                                                      pAlgoDesc->blockSize,
                                                      pOutput));

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    uint32_t rtfSize = 0;
    rtfSize = (MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf) ? pAlgoDesc->rtfSize : 0u;
    if(NULL != pAlgoDesc->dmaProtection)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(resultDma, pAlgoDesc->dmaProtection(pOutput,
                                                                      pAlgoDesc->stateSize + rtfSize));

        if (MCUXCLHASH_STATUS_OK != resultDma)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, resultDma);
        }
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    if (MCUXCLHASH_STATUS_OK != resultElsCore)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, resultElsCore);
    }

    /**************************************************************************************
     * Step 4: Copy result to output buffers and clear context
     **************************************************************************************/

    /* Copy RTF to corresponding buffer */
    if((MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf))
    {
        if (NULL == session->pRtf)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, MCUXCLHASH_STATUS_INVALID_PARAMS);
        }
        else
        {
            MCUXCLMEMORY_FP_MEMORY_COPY(session->pRtf, pOutput + pAlgoDesc->hashSize, pAlgoDesc->rtfSize);
        }
    }

    /* Copy hash digest to output buffer */
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, pOutput, pAlgoDesc->hashSize);

    *pOutSize += pAlgoDesc->hashSize;

    /* Free workarea (pOutput) */
    mcuxClSession_freeWords_cpuWa(session, (pAlgoDesc->stateSize + pAlgoDesc->rtfSize) / sizeof(uint32_t));

    /* Backup unprocessedLength before context clearing */
    MCUX_CSSL_FP_COUNTER_STMT(const size_t unprocessedLength = context->data.unprocessedLength);

    /* Clear context */
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)context,sizeof(mcuxClHash_ContextDescriptor_t));


    /**************************************************************************************
     * Step 5: Exit
     **************************************************************************************/

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHash_els_finish_sha2, MCUXCLHASH_STATUS_OK,
                              MCUX_CSSL_FP_CONDITIONAL(pAlgoDesc->blockSize - pAlgoDesc->counterSize - 1u < unprocessedLength,
                                                      #ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
                                                      pAlgoDesc->protection_token_dma_protection,
                                                      #endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
                                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                                                      pAlgoDesc->protection_token_els_core),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                              pAlgoDesc->protection_token_els_core,
                              #ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
                              pAlgoDesc->protection_token_dma_protection,
                              #endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
                              MCUX_CSSL_FP_CONDITIONAL((MCUXCLSESSION_RTF_UPDATE_TRUE == session->rtf),
                                                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

}


/**********************************************************
 * Algorithm descriptor implementations
 **********************************************************/


//#pragma coverity compliance block deviate "MISRA C-2012 Rule 5.1" "MISRA Ex. 20 - Rule 5.1 - Names with similar 31-character prefix are allowed"
const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha224 = {
//#pragma coverity compliance end_block "MISRA C-2012 Rule 5.1"
    .els_core                         = mcuxClHash_els_core_sha2,
    .protection_token_els_core        = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_core_sha2),
    .oneShotSkeleton                  = mcuxClHash_els_oneShotSkeleton_sha2,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_oneShotSkeleton_sha2),
    .processSkeleton                  = mcuxClHash_els_process_sha2,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_process_sha2),
    .finishSkeleton                   = mcuxClHash_els_finish_sha2,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_finish_sha2),
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    .dmaProtection                    = mcuxClHash_els_dmaProtectionAddressReadback,
    .protection_token_dma_protection  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_dmaProtectionAddressReadback),
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    .blockSize                        = MCUXCLHASH_BLOCK_SIZE_SHA_224,
    .hashSize                         = MCUXCLHASH_OUTPUT_SIZE_SHA_224,
    .stateSize                        = MCUXCLHASH_STATE_SIZE_SHA_224,
    .counterSize                      = MCUXCLHASH_COUNTER_SIZE_SHA_224,
    .rtfSize                          = 0u,
    .hashOptions.word.value           = MCUXCLELS_HASH_VALUE_MODE_SHA_224,
};


//#pragma coverity compliance block deviate "MISRA C-2012 Rule 5.1" "MISRA Ex. 20 - Rule 5.1 - Names with similar 31-character prefix are allowed"
const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha256 = {
//#pragma coverity compliance end_block "MISRA C-2012 Rule 5.1"
    .els_core                         = mcuxClHash_els_core_sha2,
    .protection_token_els_core        = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_core_sha2),
    .oneShotSkeleton                  = mcuxClHash_els_oneShotSkeleton_sha2,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_oneShotSkeleton_sha2),
    .processSkeleton                  = mcuxClHash_els_process_sha2,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_process_sha2),
    .finishSkeleton                   = mcuxClHash_els_finish_sha2,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_finish_sha2),
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    .dmaProtection                    = mcuxClHash_els_dmaProtectionAddressReadback,
    .protection_token_dma_protection  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_dmaProtectionAddressReadback),
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    .blockSize                        = MCUXCLHASH_BLOCK_SIZE_SHA_256,
    .hashSize                         = MCUXCLHASH_OUTPUT_SIZE_SHA_256,
    .stateSize                        = MCUXCLHASH_STATE_SIZE_SHA_256,
    .counterSize                      = MCUXCLHASH_COUNTER_SIZE_SHA_256,
    .rtfSize                          = MCUXCLELS_HASH_RTF_OUTPUT_SIZE,
    .hashOptions.word.value           = MCUXCLELS_HASH_VALUE_MODE_SHA_256,
};


//#pragma coverity compliance block deviate "MISRA C-2012 Rule 5.1" "MISRA Ex. 20 - Rule 5.1 - Names with similar 31-character prefix are allowed"
const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha384 = {
//#pragma coverity compliance end_block "MISRA C-2012 Rule 5.1"
    .els_core                         = mcuxClHash_els_core_sha2,
    .protection_token_els_core        = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_core_sha2),
    .oneShotSkeleton                  = mcuxClHash_els_oneShotSkeleton_sha2,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_oneShotSkeleton_sha2),
    .processSkeleton                  = mcuxClHash_els_process_sha2,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_process_sha2),
    .finishSkeleton                   = mcuxClHash_els_finish_sha2,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_finish_sha2),
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    .dmaProtection                    = mcuxClHash_els_dmaProtectionAddressReadback,
    .protection_token_dma_protection  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_dmaProtectionAddressReadback),
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    .blockSize                        = MCUXCLHASH_BLOCK_SIZE_SHA_384,
    .hashSize                         = MCUXCLHASH_OUTPUT_SIZE_SHA_384,
    .stateSize                        = MCUXCLHASH_STATE_SIZE_SHA_384,
    .counterSize                      = MCUXCLHASH_COUNTER_SIZE_SHA_384,
    .rtfSize                          = 0u,
    .hashOptions.word.value           = MCUXCLELS_HASH_VALUE_MODE_SHA_384,
};


//#pragma coverity compliance block deviate "MISRA C-2012 Rule 5.1" "MISRA Ex. 20 - Rule 5.1 - Names with similar 31-character prefix are allowed"
const mcuxClHash_AlgorithmDescriptor_t mcuxClHash_AlgorithmDescriptor_Sha512 = {
//#pragma coverity compliance end_block "MISRA C-2012 Rule 5.1"
    .els_core                         = mcuxClHash_els_core_sha2,
    .protection_token_els_core        = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_core_sha2),
    .oneShotSkeleton                  = mcuxClHash_els_oneShotSkeleton_sha2,
    .protection_token_oneShotSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_oneShotSkeleton_sha2),
    .processSkeleton                  = mcuxClHash_els_process_sha2,
    .protection_token_processSkeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_process_sha2),
    .finishSkeleton                   = mcuxClHash_els_finish_sha2,
    .protection_token_finishSkeleton  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_finish_sha2),
#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    .dmaProtection                    = mcuxClHash_els_dmaProtectionAddressReadback,
    .protection_token_dma_protection  = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_els_dmaProtectionAddressReadback),
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    .blockSize                        = MCUXCLHASH_BLOCK_SIZE_SHA_512,
    .hashSize                         = MCUXCLHASH_OUTPUT_SIZE_SHA_512,
    .stateSize                        = MCUXCLHASH_STATE_SIZE_SHA_512,
    .counterSize                      = MCUXCLHASH_COUNTER_SIZE_SHA_512,
    .rtfSize                          = 0u,
    .hashOptions.word.value           = MCUXCLELS_HASH_VALUE_MODE_SHA_512,
};
