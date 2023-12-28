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

/** @file  mcuxClMacModes_Els_Cbcmac.c
 *  @brief implementation of CBC-MAC part of mcuxClMac component */

#include <mcuxClKey.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClAes.h>

#include <mcuxClEls.h>
#include <mcuxClEls_Cmac.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClKey_Internal.h>

#include <mcuxClToolchain.h>

#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClMacModes_MemoryConsumption.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <internal/mcuxClMacModes_Wa.h>
#include <internal/mcuxClMacModes_Els_Types.h>
#include <internal/mcuxClMacModes_Els_Cbcmac.h>
#include <internal/mcuxClMacModes_Algorithms.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CBCMAC_Oneshot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Oneshot(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClMacModes_Context_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t *const pOut,
    uint32_t *const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CBCMAC_Oneshot);

    // Check if key matches the algorithm
    if (MCUXCLKEY_ALGO_ID_AES != mcuxClKey_getAlgorithm(pContext->key))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pContext->common.pMode->common.pAlgorithm;

    // Disable initialize/finalize for cbc-mac compitability.
    pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;
    pContext->cmac_options.bits.finalize = MCUXCLELS_CMAC_FINALIZE_DISABLE;

    // Get key location
    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key))
    {
        pContext->cmac_options.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_ENABLE;
    }
    else if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->key))
    {
        pContext->cmac_options.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_DISABLE;
    }
    else
    {
        // Error: no key loaded
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    size_t noOfFullBlocks = inLength / MCUXCLAES_BLOCK_SIZE;
    size_t remainingBytes = inLength - (noOfFullBlocks * MCUXCLAES_BLOCK_SIZE);
    MCUXCLMEMORY_FP_MEMORY_SET(pOut, 0x00, MCUXCLELS_CMAC_OUT_SIZE);

    if(0u != noOfFullBlocks)
    {
        // Call ELS cmac on all full blocks
        MCUX_CSSL_FP_FUNCTION_CALL(cmacResult1, mcuxClEls_Cmac_Async(
                              pContext->cmac_options,
                              (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                              (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                              (size_t) mcuxClKey_getSize(pContext->key),
                              pIn,
                              noOfFullBlocks * MCUXCLAES_BLOCK_SIZE,
                              pOut));

        // mcuxClEls_Cmac_Async is a flow-protected function: Check the protection token and the return value
        if (MCUXCLELS_STATUS_OK_WAIT != cmacResult1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async));
        }

        MCUX_CSSL_FP_FUNCTION_CALL(waitResult1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(pOut, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        if (MCUXCLELS_STATUS_OK != waitResult1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        }
    }
    uint32_t paddingOutLength = 0u;
    // Call padding function
    MCUX_CSSL_FP_FUNCTION_CALL(paddingResult, pAlgo->addPadding(
    /* uint32_t blockLength */          MCUXCLAES_BLOCK_SIZE,
    /* const uint8_t *const pIn */      (pIn + (MCUXCLAES_BLOCK_SIZE * noOfFullBlocks)), // this should be only the last block!
    /* uint32_t lastBlockLength */      remainingBytes,
    /* uint32_t totalInputLength */     inLength,
    /* uint8_t *const pOut */           (uint8_t*)pContext->blockBuffer,
    /* uint32_t *const pOutLength */    &paddingOutLength));

    // padding functions are flow-protected: Check the protection token and the return value
    if (MCUXCLPADDING_STATUS_OK != paddingResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    if(paddingOutLength != 0u)
    {
        // Call ELS cmac on the padded block
        MCUX_CSSL_FP_FUNCTION_CALL(cmacResult2, mcuxClEls_Cmac_Async(
                                pContext->cmac_options,
                                (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                                (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                                (size_t) mcuxClKey_getSize(pContext->key),
                                (uint8_t*)pContext->blockBuffer,
                                MCUXCLAES_BLOCK_SIZE,
                                pOut));

        // mcuxClEls_Cmac_Async is a flow-protected function: Check the protection token and the return value
        if (MCUXCLELS_STATUS_OK_WAIT != cmacResult2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async));
        }

        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));

        MCUX_CSSL_FP_FUNCTION_CALL(waitResult2, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != waitResult2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK

        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(pOut, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    }

    if((0u != inLength) || (paddingOutLength != 0u))
    {
        *pOutLength = MCUXCLELS_CMAC_OUT_SIZE;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Oneshot, MCUXCLMAC_STATUS_OK,
            MCUX_CSSL_FP_CONDITIONAL((noOfFullBlocks != 0u),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN),
            pAlgo->protectionToken_addPadding,
            MCUX_CSSL_FP_CONDITIONAL((paddingOutLength != 0u),
                MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CBCMAC_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Init(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClMacModes_Context_t * const pContext)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CBCMAC_Init, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    pContext->blockBufferUsed = 0;

    pContext->totalInput = 0;

    MCUXCLMEMORY_FP_MEMORY_SET((uint8_t*)(pContext->blockBuffer), 0x00, MCUXCLAES_BLOCK_SIZE);
    MCUXCLMEMORY_FP_MEMORY_SET((uint8_t*)(pContext->state), 0x00, MCUXCLAES_BLOCK_SIZE);

    pContext->cmac_options.word.value = 0U;
   
    // Disable initialize/finalize for cbc-mac compitability.
    pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;
    pContext->cmac_options.bits.finalize = MCUXCLELS_CMAC_FINALIZE_DISABLE;

    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key))
    {
        pContext->cmac_options.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_ENABLE;
    }
    else if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->key))
    {
        pContext->cmac_options.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_DISABLE;
    }
    else
    {
        // Error: no key loaded
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Init, MCUXCLMAC_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_CBCMAC_Init, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CBCMAC_Update)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Update(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClMacModes_Context_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CBCMAC_Update);

    size_t pInNrProcessedBytes = 0;

    // Check if there are remaining bytes in the context from previous calls to this function
    // pContext->blockBufferUsed can be at most MCUXCLAES_BLOCK_SIZE - 1
    // The case where inLength + pContext->blockBufferUsed is less than a block size is handeled later
    const bool hasBlockSizedBytesInBuffer = ((0u < pContext->blockBufferUsed) && (MCUXCLAES_BLOCK_SIZE <= (inLength + pContext->blockBufferUsed)));
    if (hasBlockSizedBytesInBuffer)
    {
        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));

        // Copy as many bytes from pIn to pContext->blockBuffer in order to create one full block
        MCUXCLMEMORY_FP_MEMORY_COPY(((uint8_t*)pContext->blockBuffer + pContext->blockBufferUsed), pIn, MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed);
        // Process this block
        MCUX_CSSL_FP_FUNCTION_CALL(cmacResult, mcuxClEls_Cmac_Async(
                                pContext->cmac_options,
                                (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                                (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                                (size_t) mcuxClKey_getSize(pContext->key),
                                (uint8_t*) pContext->blockBuffer,
                                MCUXCLAES_BLOCK_SIZE,
                                (uint8_t*) pContext->state));

        if (MCUXCLELS_STATUS_OK_WAIT != cmacResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }

        pContext->totalInput += MCUXCLAES_BLOCK_SIZE;

        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        MCUX_CSSL_FP_FUNCTION_CALL(waitResult, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != waitResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK

        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        pInNrProcessedBytes = MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed;

        pContext->blockBufferUsed = 0;

    }

    // Check if there are full blocks to process
    const bool hasFullBlocks = (MCUXCLAES_BLOCK_SIZE <= (inLength - pInNrProcessedBytes));
    if(hasFullBlocks)
    {
        size_t noOfFullBlocks = (inLength - pInNrProcessedBytes) / MCUXCLAES_BLOCK_SIZE;

        MCUX_CSSL_FP_FUNCTION_CALL(cmacResult, mcuxClEls_Cmac_Async(
                                pContext->cmac_options,
                                (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                                (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                                (size_t) mcuxClKey_getSize(pContext->key),
                                pIn + pInNrProcessedBytes,
                                noOfFullBlocks * MCUXCLAES_BLOCK_SIZE,
                                (uint8_t*) pContext->state));

        if (MCUXCLELS_STATUS_OK_WAIT != cmacResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }

        pContext->totalInput += noOfFullBlocks * MCUXCLAES_BLOCK_SIZE;

        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
        MCUX_CSSL_FP_FUNCTION_CALL(waitResult, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != waitResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLAES_BLOCK_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

        pInNrProcessedBytes += (noOfFullBlocks * MCUXCLAES_BLOCK_SIZE);
    }

    // Check if there are remaining bytes and copy them to the context
    if(pInNrProcessedBytes < inLength)
    {
        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
        MCUXCLMEMORY_FP_MEMORY_COPY(((uint8_t*)pContext->blockBuffer + pContext->blockBufferUsed), (pIn + pInNrProcessedBytes), (inLength - pInNrProcessedBytes));
        // Update number of bytes in blockBuffer
        pContext->blockBufferUsed += (inLength - pInNrProcessedBytes);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_OK,
                        MCUX_CSSL_FP_CONDITIONAL(hasBlockSizedBytesInBuffer,
                            MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async)),
                        MCUX_CSSL_FP_CONDITIONAL(hasFullBlocks,
                            MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async)));

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CBCMAC_Finalize)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CBCMAC_Finalize(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClMacModes_Context_t * const pContext,
    uint8_t *const pOut,
    uint32_t *const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CBCMAC_Finalize);

    mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pContext->common.pMode->common.pAlgorithm;

    // Check if additional block needs to be processed
    uint32_t paddingOutLength = 0u;

    // Call padding function
    MCUX_CSSL_FP_FUNCTION_CALL(paddingResult, pAlgo->addPadding(
    /* uint32_t blockLength */          MCUXCLELS_CIPHER_BLOCK_SIZE_AES,
    /* const uint8_t *const pIn */      (uint8_t*)pContext->blockBuffer,
    /* uint32_t lastBlockLength */      pContext->blockBufferUsed,
    /* uint32_t totalInputLength */     pContext->totalInput,
    /* uint8_t *const pOut */           (uint8_t*)pContext->blockBuffer,
    /* uint32_t *const pOutLength */    &paddingOutLength));

    // padding functions are flow-protected: Check the protection token and the return value
    if (MCUXCLPADDING_STATUS_OK != paddingResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_ERROR);
    }

    if(paddingOutLength != 0u)
    {
        // Call ELS cmac on padded block
        MCUX_CSSL_FP_FUNCTION_CALL(cmacResult, mcuxClEls_Cmac_Async(
                                pContext->cmac_options,
                                (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                                (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                                (size_t) mcuxClKey_getSize(pContext->key),
                                (uint8_t*)pContext->blockBuffer,
                                MCUXCLAES_BLOCK_SIZE,
                                (uint8_t*)pContext->state));

        // mcuxClEls_Cmac_Async is a flow-protected function: Check the protection token and the return value
        if (MCUXCLELS_STATUS_OK_WAIT != cmacResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_ERROR);
        }

        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));

        MCUX_CSSL_FP_FUNCTION_CALL(waitResult, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != waitResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK

        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Update, MCUXCLMAC_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    }

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));

    // Copy final result from the context to the output
    MCUXCLMEMORY_FP_MEMORY_COPY(pOut, (uint8_t*)pContext->state, MCUXCLAES_BLOCK_SIZE);

    *pOutLength = MCUXCLELS_CMAC_OUT_SIZE;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CBCMAC_Finalize, MCUXCLMAC_STATUS_OK,
                        pAlgo->protectionToken_addPadding,
                        MCUX_CSSL_FP_CONDITIONAL((paddingOutLength != 0u),
                            MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async)));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_NoPadding = {
  .engineInit = mcuxClMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_None,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
};

const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method1 = {
  .engineInit = mcuxClMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method1,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method1),
};

const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_PaddingISO9797_1_Method2 = {
  .engineInit = mcuxClMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method2,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method2),
};

const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CBCMAC_Padding_PKCS7 = {
  .engineInit = mcuxClMacModes_Engine_CBCMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Init),
  .engineUpdate =  mcuxClMacModes_Engine_CBCMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Update),
  .engineFinalize =  mcuxClMacModes_Engine_CBCMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_CBCMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CBCMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_PKCS7,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_PKCS7),
};


MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()

