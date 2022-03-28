/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClCMac.c
 *  @brief implementation of CMAC part of mcuxClMac component */

#include <mcuxClMac.h>

#include <mcuxClCss.h>
#include <mcuxClCss_Cmac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClMac_internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_CMAC_Oneshot)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Oneshot(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_CMAC_Oneshot);
    size_t const completeLen = (inSize/MCUXCLCSS_CIPHER_BLOCK_SIZE_AES)*MCUXCLCSS_CIPHER_BLOCK_SIZE_AES;
    /* MISRA Ex. 9 to Rule 11.3 */
    uint8_t *aesBlock = (uint8_t*) &(context->session->cpuWa.buffer[context->session->cpuWa.used]);
    size_t bufLen = MCUXCLCSS_CIPHER_BLOCK_SIZE_AES;
    size_t const remainingLen = inSize - completeLen;
    *outSize = MCUXCLCSS_CMAC_OUT_SIZE;

    // Check if key matches to the algorithm
    if (MCUXCLKEY_ALGO_ID_AES != MCUXCLKEY_GET_ALGOID(context->key))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR);
    }

    context->cmac_options.bits.initialize = MCUXCLCSS_CMAC_INITIALIZE_ENABLE;
    if(mcuxClKey_LoadLocation_MEMORY == MCUXCLKEY_GET_KEYLOADLOCATION(context->key))
    {
      context->cmac_options.bits.extkey = MCUXCLCSS_CMAC_EXTERNAL_KEY_ENABLE;
    }
    else if(mcuxClKey_LoadLocation_COPRO == MCUXCLKEY_GET_KEYLOADLOCATION(context->key))
    {
      context->cmac_options.bits.extkey = MCUXCLCSS_CMAC_EXTERNAL_KEY_DISABLE;
    }
    else
    {
      // error: no key loaded
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR);
    }

    //processing part of the data which is a multiple of the block size
    if (completeLen != 0u)
    {
      //data length is a multiple of the block size ==> no padding needed
      if(0u == remainingLen)
      {
        context->cmac_options.bits.finalize = MCUXCLCSS_CMAC_FINALIZE_ENABLE;
      }

      MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Cmac_Async(
                            context->cmac_options,
                            (mcuxClCss_KeyIndex_t) MCUXCLKEY_GET_KEYSLOT(context->key),
                            (uint8_t const *) MCUXCLKEY_GET_KEYDATA(context->key),
                            (size_t) MCUXCLKEY_GET_KEYSIZE(context->key),
                            in,
                            completeLen,
                            out
                            ));
      // mcuxClCss_Cmac_Async is a flow-protected function: Check the protection token and the return value
      if (MCUXCLCSS_STATUS_OK_WAIT != result)
      {
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async) );
      }

      MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

      if (MCUXCLCSS_STATUS_OK != resultWait) {
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
      }


      context->cmac_options.bits.initialize = MCUXCLCSS_CMAC_INITIALIZE_DISABLE;

    }

    //apply padding or process empty message
    if((0u != remainingLen) || (0u == inSize))
    {
      //maximum 15 bytes left to process
      MCUX_CSSL_FP_FUNCTION_CALL(copyResult, mcuxClMemory_copy(aesBlock, in + completeLen, remainingLen, bufLen ));
      bufLen -= remainingLen;

      /* Check that the buffer is long enough */
      if(copyResult != 0U) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
      }


      MCUX_CSSL_FP_FUNCTION_CALL(setResult1, mcuxClMemory_set(aesBlock + remainingLen,0x80,0x01U,bufLen));
      bufLen--;

      if(setResult1 != 0U) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
      }

      //fill the rest of the buffer with 0x00
      MCUX_CSSL_FP_FUNCTION_CALL(setResult2, mcuxClMemory_set(aesBlock + remainingLen + 1, 0x00, bufLen, bufLen ));

      if(setResult2 != 0U) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
      }

      context->cmac_options.bits.finalize = MCUXCLCSS_CMAC_FINALIZE_ENABLE;

      MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Cmac_Async(
                          context->cmac_options,
                          (mcuxClCss_KeyIndex_t) MCUXCLKEY_GET_KEYSLOT(context->key),
                          (uint8_t const *) MCUXCLKEY_GET_KEYDATA(context->key),
                          (size_t) MCUXCLKEY_GET_KEYSIZE(context->key),
                          aesBlock,
                          remainingLen,
                          out
                          ));
      // mcuxClCss_Cmac_Async is a flow-protected function: Check the protection token and the return value
      if (MCUXCLCSS_STATUS_OK_WAIT != result)
      {
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
              MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async) );
      }

      MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

      if (MCUXCLCSS_STATUS_OK != resultWait) {
          MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
              MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u,
                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
      }


    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Oneshot, MCUXCLMAC_ERRORCODE_OK,
        MCUX_CSSL_FP_CONDITIONAL(completeLen != 0u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)),
        MCUX_CSSL_FP_CONDITIONAL((0u != remainingLen) || (0u == inSize), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation))
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_CMAC_Init)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Init(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_CMAC_Init, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
  context->nrOfUnprocessedBytes = 0;
  MCUX_CSSL_FP_FUNCTION_CALL(resultSet1, mcuxClMemory_set((uint8_t*)(context->unprocessed),0x00,MCUXCLCSS_CIPHER_BLOCK_SIZE_AES,MCUXCLCSS_CIPHER_BLOCK_SIZE_AES));
  MCUX_CSSL_FP_FUNCTION_CALL(resultSet2, mcuxClMemory_set((uint8_t*)(context->state),0x00,MCUXCLCSS_CIPHER_BLOCK_SIZE_AES,MCUXCLCSS_CIPHER_BLOCK_SIZE_AES));
  if((resultSet1 != 0U) || (resultSet2 != 0U)) {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Init, MCUXCLMAC_ERRORCODE_ERROR);
  }

  context->cmac_options.word.value = 0U;

  context->cmac_options.bits.initialize = MCUXCLCSS_CMAC_INITIALIZE_ENABLE;
  if(mcuxClKey_LoadLocation_MEMORY == MCUXCLKEY_GET_KEYLOADLOCATION(context->key))
  {
    context->cmac_options.bits.extkey = MCUXCLCSS_CMAC_EXTERNAL_KEY_ENABLE;
  }
  else if(mcuxClKey_LoadLocation_COPRO == MCUXCLKEY_GET_KEYLOADLOCATION(context->key))
  {
    context->cmac_options.bits.extkey = MCUXCLCSS_CMAC_EXTERNAL_KEY_DISABLE;
  }
  else
  {
    // error: no key loaded
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Init, MCUXCLMAC_ERRORCODE_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Init, MCUXCLMAC_ERRORCODE_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_CMAC_Update)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Update(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_CMAC_Update);
  size_t remainingLength = inSize;
  size_t alreadyProcessedBytes = 0;

  //check if there are "old" bytes to process
  if((context->nrOfUnprocessedBytes > 0U) && ((context->nrOfUnprocessedBytes + inSize) > MCUXCLCSS_CIPHER_BLOCK_SIZE_AES))
  {
    //copy new input data
    MCUX_CSSL_FP_FUNCTION_CALL(resultCopy, mcuxClMemory_copy((uint8_t*)context->unprocessed + context->nrOfUnprocessedBytes,
                      in,
                      MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - context->nrOfUnprocessedBytes,
                      MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - context->nrOfUnprocessedBytes ));

    if(resultCopy != 0U) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
    }

    //perform cmac operation
    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Cmac_Async(
                        context->cmac_options,
                        (mcuxClCss_KeyIndex_t) MCUXCLKEY_GET_KEYSLOT(context->key),
                        (uint8_t const *) MCUXCLKEY_GET_KEYDATA(context->key),
                        (size_t) MCUXCLKEY_GET_KEYSIZE(context->key),
                        (uint8_t*)context->unprocessed,
                        MCUXCLCSS_CIPHER_BLOCK_SIZE_AES,
                        (uint8_t*)context->state
                        ));

    // mcuxClCss_Cmac_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLCSS_STATUS_OK_WAIT != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async) );
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if (MCUXCLCSS_STATUS_OK != resultWait) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
    }


    //update options for the next operations
    context->cmac_options.bits.initialize = MCUXCLCSS_CMAC_INITIALIZE_DISABLE;

    remainingLength -= (MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - context->nrOfUnprocessedBytes);
    alreadyProcessedBytes = (MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - context->nrOfUnprocessedBytes);

    context->nrOfUnprocessedBytes = 0;

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
  }

  //check if there are full block of input data available
  if(MCUXCLCSS_CIPHER_BLOCK_SIZE_AES < remainingLength)
  {
    size_t  completeLen = (remainingLength/MCUXCLCSS_CIPHER_BLOCK_SIZE_AES)*MCUXCLCSS_CIPHER_BLOCK_SIZE_AES;

    //if remaining length is a multiple of the block size,
    //keep on block. We need it for the finalize operation
    if(remainingLength == completeLen)
    {
      completeLen -= MCUXCLCSS_CIPHER_BLOCK_SIZE_AES;
    }

    //perform cmac operation
    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Cmac_Async(
                                 context->cmac_options,
                                 (mcuxClCss_KeyIndex_t) MCUXCLKEY_GET_KEYSLOT(context->key),
                                 (uint8_t const *) MCUXCLKEY_GET_KEYDATA(context->key),
                                 (size_t) MCUXCLKEY_GET_KEYSIZE(context->key),
                                 in + alreadyProcessedBytes,
                                 completeLen,
                                 (uint8_t*)context->state
                                 ));
    // mcuxClCss_Cmac_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLCSS_STATUS_OK_WAIT != result) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async) );
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if (MCUXCLCSS_STATUS_OK != resultWait) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
    }


    context->cmac_options.bits.initialize = MCUXCLCSS_CMAC_INITIALIZE_DISABLE;

    remainingLength -= completeLen;
    alreadyProcessedBytes += completeLen;

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
  }

  //check if there is still input data left that needs to be copied to the context
  if(remainingLength != 0u)
  {
    //maximum 16 bytes left
    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClMemory_copy((uint8_t*)context->unprocessed + context->nrOfUnprocessedBytes,
                     in + alreadyProcessedBytes,
                     remainingLength,
                     sizeof(context->unprocessed) - context->nrOfUnprocessedBytes));

    if(result != 0U) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
    }

    context->nrOfUnprocessedBytes += (uint8_t) remainingLength;
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Update, MCUXCLMAC_ERRORCODE_OK,
    MCUX_CSSL_FP_CONDITIONAL(remainingLength != 0u, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy))
  );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_CMAC_Finalize)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Finalize(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_CMAC_Finalize);
  context->cmac_options.bits.finalize = MCUXCLCSS_CMAC_FINALIZE_ENABLE;

  //apply padding if needed
  if(MCUXCLCSS_CIPHER_BLOCK_SIZE_AES > context->nrOfUnprocessedBytes)
  {
    ((uint8_t*)(context->unprocessed))[context->nrOfUnprocessedBytes] = 0x80U;

    //fill the rest of the buffer with 0x00
    MCUX_CSSL_FP_FUNCTION_CALL(resultSet1, mcuxClMemory_set(((uint8_t*)context->unprocessed) + context->nrOfUnprocessedBytes + 1u, 0x00,
                    MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - ((size_t) context->nrOfUnprocessedBytes + 1u),
                    MCUXCLCSS_CIPHER_BLOCK_SIZE_AES - ((size_t) context->nrOfUnprocessedBytes + 1u) ));
    if(resultSet1 != 0U) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
    }

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
  }

  //perform cmac operation
  MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Cmac_Async(context->cmac_options,
                               (mcuxClCss_KeyIndex_t) (MCUXCLKEY_GET_KEYSLOT(context->key)),
                               (uint8_t const *) MCUXCLKEY_GET_KEYDATA(context->key),
                               (size_t) MCUXCLKEY_GET_KEYSIZE(context->key),
                               (uint8_t*)(context->unprocessed),
                               context->nrOfUnprocessedBytes,
                               (uint8_t*)(context->state)));
  // mcuxClCss_Cmac_Async is a flow-protected function: Check the protection token and the return value
  if (MCUXCLCSS_STATUS_OK_WAIT != result) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async) );
  }

  MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

  if (MCUXCLCSS_STATUS_OK != resultWait) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
  }


  if(MCUXCLCSS_CMAC_OUT_SIZE < *outSize) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
  }

  //copy result to output buffer
  MCUX_CSSL_FP_FUNCTION_CALL(resultCopy, mcuxClMemory_copy(out,
                   (uint8_t*)context->state,
                   *outSize,
                   *outSize ));

  if(resultCopy != 0U) {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) );
  }

  //context isn't needed any longer; destroy it
  MCUX_CSSL_FP_FUNCTION_CALL(resultSet, mcuxClMemory_set((uint8_t*)(context),0x00,sizeof(mcuxClMac_Context_t),sizeof(mcuxClMac_Context_t)));

  if(resultSet != 0U) {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
  }


  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_CMAC_Finalize, MCUXCLMAC_ERRORCODE_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Cmac_Async),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
}

const mcuxClMac_Mode_t mcuxClMac_Mode_CMAC = {mcuxClMac_Engine_CMAC_Init,
                                      mcuxClMac_Engine_CMAC_Update,
                                      mcuxClMac_Engine_CMAC_Finalize,
                                      mcuxClMac_Engine_CMAC_Oneshot,
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_CMAC_Init),
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_CMAC_Update),
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_CMAC_Finalize),
                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_CMAC_Oneshot),
                                      MCUXCLCSS_CMAC_OUT_SIZE};
