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

/** @file  mcuxClHMac.c
 *  @brief implementation of the HMAC part of mcuxClMac component */

#include <mcuxClMac.h>

#include <mcuxClCss.h>
#include <mcuxClCss_Hmac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClMac_internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_HMAC_Init)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Init(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_HMAC_Init);
  //HMAC doesn't support partial processing
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Init, MCUXCLMAC_ERRORCODE_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_HMAC_Update)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Update(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_HMAC_Update);
  //HMAC doesn't support partial processing
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Update, MCUXCLMAC_ERRORCODE_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_HMAC_Finalize)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Finalize(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_HMAC_Finalize);
  //HMAC doesn't support partial processing
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Finalize, MCUXCLMAC_ERRORCODE_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMac_Engine_HMAC_Oneshot)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Oneshot(mcuxClMac_Context_t *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMac_Engine_HMAC_Oneshot,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
    size_t completeLen = (inSize/MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256)*MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256;
    size_t lastDataChunkLength = inSize - completeLen;
    size_t totalPaddingLength = 0;

    uint8_t *pDataIn = (uint8_t*)in;

    mcuxClCss_HmacOption_t hmac_options = {0};

    hmac_options.bits.extkey = MCUXCLCSS_HMAC_EXTERNAL_KEY_DISABLE;

    //apply padding
    //append the padding to the input buffer
    //caller needs to assure that the buffer is big enough

    //compute total padding length
    if((MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256 - MCUXCL_HMAC_MIN_PADDING_LENGTH)
                  < lastDataChunkLength)
    {
      totalPaddingLength = (2u*MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256) - lastDataChunkLength;
    }
    else
    {
      totalPaddingLength = MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256 - lastDataChunkLength;
    }

    pDataIn += inSize;
    //set 0x80 byte
    MCUX_CSSL_FP_FUNCTION_CALL(setResult1, mcuxClMemory_set ( pDataIn, 0x80, 1u, 1u));
    if(setResult1 != 0U) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR);
    }

    //set 0x00 bytes (+3 0x00 bytes because inSize is only 32 bits while length field in padding is 64 bits
    MCUX_CSSL_FP_FUNCTION_CALL(setResult2, mcuxClMemory_set(pDataIn+1,0x00,totalPaddingLength-MCUXCL_HMAC_MIN_PADDING_LENGTH+1u+3u,totalPaddingLength-1u));
    if(setResult2 != 0U) {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set) );
    }
    pDataIn += totalPaddingLength - 1u;

    //length of the unpadded message in bits
	//css requires that the length of the key is added as well, hence +64
    uint64_t lengthField = (uint64_t) inSize + 64U;

    *pDataIn-- = (uint8_t)(lengthField << 3);
    *pDataIn-- = (uint8_t)(lengthField >> 5);
    *pDataIn-- = (uint8_t)(lengthField >> 13);
    *pDataIn-- = (uint8_t)(lengthField >> 21);
	*pDataIn-- = (uint8_t)(lengthField >> 29);

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_Hmac_Async(
                          hmac_options,
                          (mcuxClCss_KeyIndex_t) (MCUXCLKEY_GET_KEYSLOT(context->key)),
                          NULL,
                          in,
                          inSize+totalPaddingLength,
                          out));
    // mcuxClCss_Hmac_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLCSS_STATUS_OK_WAIT != result) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Hmac_Async) );
    }
    
    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if ((MCUXCLCSS_STATUS_OK != resultWait)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Oneshot, MCUXCLMAC_ERRORCODE_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Hmac_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
    }


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMac_Engine_HMAC_Oneshot, MCUXCLMAC_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Hmac_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) );
}

const mcuxClMac_Mode_t mcuxClMac_Mode_HMAC_SHA2_256 = {mcuxClMac_Engine_HMAC_Init,
                                               mcuxClMac_Engine_HMAC_Update,
                                               mcuxClMac_Engine_HMAC_Finalize,
                                               mcuxClMac_Engine_HMAC_Oneshot,
                                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_HMAC_Init),
                                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_HMAC_Update),
                                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_HMAC_Finalize),
                                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_Engine_HMAC_Oneshot),
                                               MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_256};
