/*--------------------------------------------------------------------------*/
/* Copyright 2020-2024 NXP                                                  */
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

/** @file  mcuxClMacModes_Els_Cmac.c
 *  @brief implementation of CMAC part of mcuxClMac component */

#include <mcuxClEls.h>
#include <mcuxClEls_Cmac.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Macros.h>
#include <mcuxClToolchain.h>
#include <internal/mcuxClKey_Internal.h>
#include <mcuxClAes.h>

#include <internal/mcuxClMac_Internal_Types.h>
#include <mcuxClMacModes_MemoryConsumption.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <internal/mcuxClMacModes_Common_Wa.h>
#include <internal/mcuxClMacModes_Els_Types.h>
#include <internal/mcuxClMacModes_Els_Cmac.h>
#include <internal/mcuxClMacModes_Common_Algorithms.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CMAC_ProcessBlocks)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CMAC_ProcessBlocks(
    mcuxClMacModes_Context_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inputLen,
    uint8_t *const pOut)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CMAC_ProcessBlocks);

    MCUX_CSSL_FP_FUNCTION_CALL(resultCmac, mcuxClEls_Cmac_Async(
                          pContext->cmac_options,
                          (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key),
                          (uint8_t const *) mcuxClKey_getLoadedKeyData(pContext->key),
                          (size_t) mcuxClKey_getSize(pContext->key),
                          pIn,
                          inputLen,
                          pOut
                          ));
    // mcuxClEls_Cmac_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLELS_STATUS_OK_WAIT != resultCmac)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_ProcessBlocks, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async) );
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if (MCUXCLELS_STATUS_OK != resultWait) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_ProcessBlocks, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
    }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    if(NULL != pOut)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult1, mcuxClEls_CompareDmaFinalOutputAddress(pOut, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_ProcessBlocks, MCUXCLMAC_STATUS_FAULT_ATTACK);
        }
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_ProcessBlocks, MCUXCLMAC_STATUS_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
      MCUX_CSSL_FP_CONDITIONAL(NULL != pOut, MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN));
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CMAC_Oneshot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CMAC_Oneshot(
    mcuxClSession_Handle_t session,
    mcuxClMacModes_Context_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t *const pOut,
    uint32_t *const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CMAC_Oneshot);
    uint32_t const completeLen = (inLength/MCUXCLAES_BLOCK_SIZE)*MCUXCLAES_BLOCK_SIZE;
    uint32_t const remainingLen = inLength%MCUXCLAES_BLOCK_SIZE;
    mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t)pContext->common.pMode->common.pAlgorithm;

    // Check if key matches to the algorithm
    if (MCUXCLKEY_ALGO_ID_AES != mcuxClKey_getAlgorithm(pContext->key))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    /* Create workarea */
    /* MISRA Ex. 9 to Rule 11.3 - reinterpret memory */
    uint32_t cpuWaSizeInWords = MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(sizeof(mcuxClMacModes_WorkArea_t));
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClMacModes_WorkArea_t *workArea = (mcuxClMacModes_WorkArea_t *) mcuxClSession_allocateWords_cpuWa(session, cpuWaSizeInWords);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    if(NULL == workArea)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, MCUXCLMAC_STATUS_FAILURE);
    }

    pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_ENABLE;
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
      // error: no key loaded
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    //processing part of the data which is a multiple of the block size
    if (completeLen != 0u)
    {
      //data length is a multiple of the block size ==> no padding needed
      if(0u == remainingLen)
      {
        pContext->cmac_options.bits.finalize = MCUXCLELS_CMAC_FINALIZE_ENABLE;
      }

      MCUX_CSSL_FP_FUNCTION_CALL(processFBResult, mcuxClMacModes_Engine_CMAC_ProcessBlocks(
                                            pContext,
                                            pIn,
                                            completeLen,
                                            pOut));
      if (MCUXCLMAC_STATUS_OK != processFBResult)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, processFBResult,
                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
      }

      pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;
    }

    //apply padding or process empty message
    if((0u != remainingLen) || (0u == inLength))
    {
      uint32_t paddingOutLen = 0u;
      MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(
                                               MCUXCLAES_BLOCK_SIZE,
                                               MCUXCLBUFFER_GET(pIn) + completeLen,
                                               remainingLen,
                                               inLength,
      MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("workArea is mcuxClMacModes_WorkArea_t *type")
                                               (uint8_t *)workArea->paddingBuff,
      MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
                                               &paddingOutLen));
      /* Don't use this as input length for Elc Cmac */
      (void)paddingOutLen;
      if (MCUXCLPADDING_STATUS_OK != padResult)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, MCUXCLMAC_STATUS_ERROR,
                                  pAlgo->protectionToken_addPadding,
                                  MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks)));
      }

      pContext->cmac_options.bits.finalize = MCUXCLELS_CMAC_FINALIZE_ENABLE;

      MCUX_CSSL_FP_FUNCTION_CALL(processFBResult, mcuxClMacModes_Engine_CMAC_ProcessBlocks(
                                            pContext,
                                            (uint8_t *)workArea->paddingBuff,
                                            remainingLen,
                                            pOut));
      if (MCUXCLMAC_STATUS_OK != processFBResult)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Oneshot, processFBResult,
                                    MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks)),
                                    pAlgo->protectionToken_addPadding,
                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
      }
    }

    *pOutLength = MCUXCLELS_CMAC_OUT_SIZE;

    /* Free workArea in Session */
    mcuxClSession_freeWords_cpuWa(session, cpuWaSizeInWords);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_CMAC_Oneshot, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks)),
        MCUX_CSSL_FP_CONDITIONAL((0u != remainingLen) || (0u == inLength),
          pAlgo->protectionToken_addPadding,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks)
        )
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CMAC_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CMAC_Init(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CMAC_Init, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
  pContext->blockBufferUsed = 0;
  MCUXCLMEMORY_FP_MEMORY_SET((uint8_t*)(pContext->blockBuffer),0x00,MCUXCLAES_BLOCK_SIZE);
  MCUXCLMEMORY_FP_MEMORY_SET((uint8_t*)(pContext->state), 0x00, MCUXCLAES_BLOCK_SIZE);

  pContext->cmac_options.word.value = 0U;

  pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_ENABLE;
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
    // error: no key loaded
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Init, MCUXCLMAC_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_CMAC_Init, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CMAC_Update)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CMAC_Update(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CMAC_Update);
  size_t remainingLength = inLength;
  size_t alreadyProcessedBytes = 0;

  MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(UINT32_MAX - inLength, pContext->blockBufferUsed, UINT32_MAX, MCUXCLMAC_STATUS_ERROR)
  //check if there are "old" bytes to process
  if((pContext->blockBufferUsed > 0U) && ((pContext->blockBufferUsed + inLength) > MCUXCLAES_BLOCK_SIZE))
  {
    //copy new input data
    MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t*)pContext->blockBuffer + pContext->blockBufferUsed, pIn, MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed);
    //perform cmac operation
    MCUX_CSSL_FP_FUNCTION_CALL(processFBResult, mcuxClMacModes_Engine_CMAC_ProcessBlocks(
                                          pContext,
                                          (uint8_t*)pContext->blockBuffer,
                                          MCUXCLAES_BLOCK_SIZE,
                                          (uint8_t*)pContext->state));
    if (MCUXCLMAC_STATUS_OK != processFBResult)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Update, processFBResult,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
    }

    //update options for the next operations
    pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("remainingLength >= (MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed)")
    remainingLength -= (MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    alreadyProcessedBytes = (MCUXCLAES_BLOCK_SIZE - pContext->blockBufferUsed);
  }

  /* Balance the SC */
  if((pContext->blockBufferUsed > 0U) && ((pContext->blockBufferUsed + inLength) > MCUXCLAES_BLOCK_SIZE))
  {
    pContext->blockBufferUsed = 0;
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks)
                                    );
  }

  //check if there are full block of input data available
  size_t completeLen = 0u;
  if(MCUXCLAES_BLOCK_SIZE < remainingLength)
  {
    completeLen = (remainingLength/MCUXCLAES_BLOCK_SIZE)*MCUXCLAES_BLOCK_SIZE;

    //if remaining length is a multiple of the block size,
    //keep on block. We need it for the finalize operation
    if(remainingLength == completeLen)
    {
      completeLen -= MCUXCLAES_BLOCK_SIZE;
    }

    MCUX_CSSL_FP_FUNCTION_CALL(processFBResult, mcuxClMacModes_Engine_CMAC_ProcessBlocks(
                                          pContext,
                                          pIn + alreadyProcessedBytes,
                                          completeLen,
                                          (uint8_t *)(pContext->state)));
    if (MCUXCLMAC_STATUS_OK != processFBResult)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Update, processFBResult,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
    }

    pContext->cmac_options.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("alreadyProcessedBytes += completeLen can't be max than UINT32_MAX")
    alreadyProcessedBytes += completeLen;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

  }
  /* Balance the SC */
  if (completeLen > 0u)
  {
    remainingLength -= completeLen;
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
  }

  //check if there is still input data left that needs to be copied to the context
  if(remainingLength != 0u)
  {
    //maximum 16 bytes left
    MCUXCLMEMORY_FP_MEMORY_COPY_WITH_BUFF((uint8_t*)pContext->blockBuffer + pContext->blockBufferUsed,
                     pIn + alreadyProcessedBytes,
                     remainingLength,
                     sizeof(pContext->blockBuffer) - pContext->blockBufferUsed);

    pContext->blockBufferUsed += (uint8_t) remainingLength;
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_CMAC_Update, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK,
    MCUX_CSSL_FP_CONDITIONAL(remainingLength != 0u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy))
  );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_CMAC_Finalize)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_CMAC_Finalize(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t *const pOutLength)
{
  pContext->cmac_options.bits.finalize = MCUXCLELS_CMAC_FINALIZE_ENABLE;
  mcuxClMacModes_Algorithm_t pAlgo = (mcuxClMacModes_Algorithm_t) pContext->common.pMode->common.pAlgorithm;

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_CMAC_Finalize,
                             pAlgo->protectionToken_addPadding);

  // apply padding if needed
  uint32_t paddingOutLen = 0u;
  MCUX_CSSL_FP_FUNCTION_CALL(padResult, pAlgo->addPadding(
                                           MCUXCLAES_BLOCK_SIZE,
                                           (uint8_t *)pContext->blockBuffer,
                                           pContext->blockBufferUsed,
                                           MCUXCLAES_BLOCK_SIZE,
                                           (uint8_t *)pContext->blockBuffer,
                                           &paddingOutLen));
  /* Don't use this as input length for Elc Cmac */
  (void) paddingOutLen;
  if (MCUXCLPADDING_STATUS_OK != padResult)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Finalize, MCUXCLMAC_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(processFBResult, mcuxClMacModes_Engine_CMAC_ProcessBlocks(
                                        pContext,
                                        (const uint8_t *)pContext->blockBuffer,
                                        pContext->blockBufferUsed,
                                        (uint8_t *)(pContext->state)));
  if (MCUXCLMAC_STATUS_OK != processFBResult)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_CMAC_Finalize, processFBResult,
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks));
  }

  //copy result to output buffer
  MCUXCLMEMORY_FP_MEMORY_COPY(pOut,(uint8_t*)pContext->state,pContext->common.pMode->common.macByteSize);


  *pOutLength = MCUXCLELS_CMAC_OUT_SIZE;

  //context isn't needed any longer; destroy it
  MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t*)(pContext), sizeof(mcuxClMacModes_Context_t));

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_CMAC_Finalize, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_ProcessBlocks),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_CMAC = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  .engineInit = mcuxClMacModes_Engine_CMAC_Init,
  .protectionToken_engineInit =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_Init),
  .engineUpdate =  mcuxClMacModes_Engine_CMAC_Update,
  .protectionToken_engineUpdate =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_Update),
  .engineFinalize =  mcuxClMacModes_Engine_CMAC_Finalize,
  .protectionToken_engineFinalize =  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_CMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_CMAC_Oneshot),
  .addPadding = mcuxClPadding_addPadding_MAC_ISO9797_1_Method2,
  .protectionToken_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_MAC_ISO9797_1_Method2)
};
