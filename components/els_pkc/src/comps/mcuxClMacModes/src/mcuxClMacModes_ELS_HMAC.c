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

/** @file  mcuxClMacModes_ELS_HMAC.c
 *  @brief implementation of the HMAC part of mcuxClMac component using ELS */

#include <mcuxClToolchain.h>
#include <mcuxClMac.h>

#include <mcuxClEls.h>
#include <mcuxClEls_Hash.h>
#include <mcuxClEls_Hmac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxClMacModes_Constants.h>
#include <mcuxClMacModes_MemoryConsumption.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClMacModes_Internal_Functions.h>
#include <internal/mcuxClMacModes_ELS_Ctx.h>
#include <internal/mcuxClMacModes_Wa.h>
#include <internal/mcuxClMacModes_ELS_Types.h>
#include <internal/mcuxClMacModes_ELS_HMAC.h>
#include <internal/mcuxClMacModes_Algorithms.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_HMAC_Oneshot)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_HMAC_Oneshot(
    mcuxClSession_Handle_t session,
    mcuxClMacModes_Context_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t * const pOut,
    uint32_t * const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_HMAC_Oneshot,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    size_t completeLen = (inLength / MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE) * MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE;
    size_t lastDataChunkLength = inLength - completeLen;
    size_t totalPaddingLength = 0u;

    /* MISRA Ex. 12 - Rule 11.8 */
    uint8_t *pDataIn = (uint8_t*) pIn;

    /* Apply padding to the input buffer */
    //caller needs to assure that the buffer is big enough

    //compute total padding length
    if((MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE - MCUXCLMAC_HMAC_MIN_PADDING_LENGTH) < lastDataChunkLength)
    {
        totalPaddingLength = (2u * MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE) - lastDataChunkLength;
    }
    else
    {
        totalPaddingLength = MCUXCLMAC_HMAC_SHA_256_BLOCK_SIZE - lastDataChunkLength;
    }
    pDataIn += inLength;

    //set 0x80 byte
    MCUXCLMEMORY_FP_MEMORY_SET(pDataIn, 0x80, 1u);

    //set 0x00 bytes (+3 0x00 bytes because inLength is only 32 bits while length field in padding is 64 bits
    MCUXCLMEMORY_FP_MEMORY_SET_WITH_BUFF(pDataIn + 1, 0x00, totalPaddingLength - MCUXCLMAC_HMAC_MIN_PADDING_LENGTH + 1u + 3u, totalPaddingLength - 1u);
    pDataIn += totalPaddingLength - 1u;

    //length of the unpadded message in bits
    //ELS requires that the length of the key is added as well
    uint64_t lengthField = (uint64_t) inLength + MCUXCLELS_HMAC_PADDED_KEY_SIZE;

    *pDataIn-- = (uint8_t)(lengthField << 3);
    *pDataIn-- = (uint8_t)(lengthField >> 5);
    *pDataIn-- = (uint8_t)(lengthField >> 13);
    *pDataIn-- = (uint8_t)(lengthField >> 21);
    *pDataIn-- = (uint8_t)(lengthField >> 29);

    /* Set-up the HMAC ELS options */
    mcuxClEls_HmacOption_t hmac_options;
    hmac_options.word.value = 0u;

    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key))
    {
        hmac_options.bits.extkey = MCUXCLELS_HMAC_EXTERNAL_KEY_ENABLE;

        /* Prepare the external HMAC key */
        MCUX_CSSL_FP_FUNCTION_CALL(prepareKeyResult, mcuxClMacModes_prepareHMACKey(session, pContext->key, pContext->preparedHmacKey));

        if(MCUXCLMAC_STATUS_OK != prepareKeyResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_prepareHMACKey),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
        }
    }
    else if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->key))
    {
        hmac_options.bits.extkey = MCUXCLELS_HMAC_EXTERNAL_KEY_DISABLE;
    }
    else
    {
        // error: no key loaded
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClEls_Hmac_Async(
                          hmac_options,
                          (mcuxClEls_KeyIndex_t) (mcuxClKey_getLoadedKeySlot(pContext->key)),
                          (uint8_t const *) pContext->preparedHmacKey,
                          pIn,
                          inLength + totalPaddingLength,
                          pOut));

    if (MCUXCLELS_STATUS_OK_WAIT != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_prepareHMACKey)
            ),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if ((MCUXCLELS_STATUS_OK != resultWait))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_prepareHMACKey)
            ),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
    }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    if(NULL != pOut)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(pOut, MCUXCLELS_HMAC_OUTPUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_FAULT_ATTACK);
        }
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    *pOutLength = MCUXCLELS_HMAC_OUTPUT_SIZE;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClMacModes_Engine_HMAC_Oneshot, MCUXCLMAC_STATUS_OK, MCUXCLMAC_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_prepareHMACKey)
        ),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
        MCUX_CSSL_FP_CONDITIONAL(NULL != pOut,  MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN)
         );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_HMAC_Init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_HMAC_Init(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_HMAC_Init);
  //HMAC doesn't support partial processing
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Init, MCUXCLMAC_STATUS_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_HMAC_Update)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_HMAC_Update(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext UNUSED_PARAM,
  const uint8_t *const pIn UNUSED_PARAM,
  uint32_t inLength UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_HMAC_Update);
  //HMAC doesn't support partial processing
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Update, MCUXCLMAC_STATUS_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMacModes_Engine_HMAC_Finalize)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMacModes_Engine_HMAC_Finalize(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClMacModes_Context_t * const pContext UNUSED_PARAM,
  uint8_t *const pOut UNUSED_PARAM,
  uint32_t *const pOutLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMacModes_Engine_HMAC_Finalize);
  //HMAC doesn't support partial processing
  *pOutLength = 0u;
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMacModes_Engine_HMAC_Finalize, MCUXCLMAC_STATUS_ERROR);
}

MCUXCLCORE_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClMacModes_AlgorithmDescriptor_t mcuxClMacModes_AlgorithmDescriptor_HMAC_Els = {
MCUXCLCORE_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  .engineInit = mcuxClMacModes_Engine_HMAC_Init,
  .protectionToken_engineInit = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_HMAC_Init),
  .engineUpdate = mcuxClMacModes_Engine_HMAC_Update,
  .protectionToken_engineUpdate = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_HMAC_Update),
  .engineFinalize = mcuxClMacModes_Engine_HMAC_Finalize,
  .protectionToken_engineFinalize = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_HMAC_Finalize),
  .engineOneshot = mcuxClMacModes_Engine_HMAC_Oneshot,
  .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMacModes_Engine_HMAC_Oneshot),
  .addPadding = NULL,
  .protectionToken_addPadding = 0u,
};
