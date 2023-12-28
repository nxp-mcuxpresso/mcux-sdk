/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClHmac_Els.c
 *  @brief Implementation of ELS engine functions for the HMAC component */

#include <mcuxClToolchain.h>
#include <mcuxClMac.h>
#include <mcuxClEls.h>
#include <mcuxClEls_Hash.h>
#include <mcuxClEls_Hmac.h>
#include <mcuxClMemory.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClHmac_Constants.h>
#include <mcuxClHmac_MemoryConsumption.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClHmac_Internal_Functions.h>
#include <internal/mcuxClHmac_Internal_Types.h>
#include <internal/mcuxClHmac_Core_Functions_Els.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Oneshot_Els, mcuxClHmac_ComputeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Oneshot_Els(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t * const pOut,
    uint32_t * const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Oneshot_Els,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret structure for different HMAC context types")
    mcuxClHmac_Context_Els_t * const pCtxEls = (mcuxClHmac_Context_Els_t *) pContext;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    size_t completeLen = (inLength / MCUXCLHMAC_ELS_BLOCK_SIZE) * MCUXCLHMAC_ELS_BLOCK_SIZE;
    size_t lastDataChunkLength = inLength - completeLen;
    size_t totalPaddingLength = 0u;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const is discarded to perform byte-wise padding")
    uint8_t *pDataIn = (uint8_t*) pIn;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()

    /* Apply padding to the input buffer */
    //caller needs to assure that the buffer is big enough

    //compute total padding length
    if((MCUXCLHMAC_ELS_BLOCK_SIZE - MCUXCLHMAC_ELS_MIN_PADDING_LENGTH) < lastDataChunkLength)
    {
        totalPaddingLength = (2u * MCUXCLHMAC_ELS_BLOCK_SIZE) - lastDataChunkLength;
    }
    else
    {
        totalPaddingLength = MCUXCLHMAC_ELS_BLOCK_SIZE - lastDataChunkLength;
    }
    pDataIn += inLength;

    //set 0x80 byte
    MCUXCLMEMORY_FP_MEMORY_SET(pDataIn, 0x80, 1u);

    //set 0x00 bytes (+3 0x00 bytes because inLength is only 32 bits while length field in padding is 64 bits
    MCUXCLMEMORY_FP_MEMORY_SET_WITH_BUFF(pDataIn + 1, 0x00, totalPaddingLength - MCUXCLHMAC_ELS_MIN_PADDING_LENGTH + 1u + 3u, totalPaddingLength - 1u);
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

    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pCtxEls->key))
    {
        hmac_options.bits.extkey = MCUXCLELS_HMAC_EXTERNAL_KEY_ENABLE;

        /* Prepare the external HMAC key */
        MCUX_CSSL_FP_FUNCTION_CALL(prepareKeyResult, mcuxClHmac_prepareHMACKey(session, pCtxEls->key, pCtxEls->preparedHmacKey));

        if(MCUXCLMAC_STATUS_OK != prepareKeyResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_ERROR,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_prepareHMACKey),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));
        }
    }
    else if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pCtxEls->key))
    {
        hmac_options.bits.extkey = MCUXCLELS_HMAC_EXTERNAL_KEY_DISABLE;
    }
    else
    {
        // error: no key loaded
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClEls_Hmac_Async(
                          hmac_options,
                          (mcuxClEls_KeyIndex_t) (mcuxClKey_getLoadedKeySlot(pCtxEls->key)),
                          (uint8_t const *) pCtxEls->preparedHmacKey,
                          pIn,
                          inLength + totalPaddingLength,
                          pOut));

    if (MCUXCLELS_STATUS_OK_WAIT != result)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pCtxEls->key)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_prepareHMACKey)
            ),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if ((MCUXCLELS_STATUS_OK != resultWait))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
            MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pCtxEls->key)),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_prepareHMACKey)
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
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_FAULT_ATTACK);
        }
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    *pOutLength = MCUXCLELS_HMAC_OUTPUT_SIZE;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Oneshot_Els, MCUXCLMAC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pCtxEls->key)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_prepareHMACKey)
        ),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Hmac_Async),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
        MCUX_CSSL_FP_CONDITIONAL(NULL != pOut,  MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN)
         );
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Init_Els, mcuxClHmac_InitEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Init_Els(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClHmac_Context_Generic_t * const pContext UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Init_Els);
    //ELS HMAC doesn't support partial processing
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Init_Els, MCUXCLMAC_STATUS_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Update_Els, mcuxClHmac_UpdateEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Update_Els(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClHmac_Context_Generic_t * const pContext UNUSED_PARAM,
    const uint8_t *const pIn UNUSED_PARAM,
    uint32_t inLength UNUSED_PARAM)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Update_Els);
    //HMAC doesn't support partial processing
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Update_Els, MCUXCLMAC_STATUS_ERROR);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClHmac_Engine_Finalize_Els, mcuxClHmac_FinalizeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_Engine_Finalize_Els(
    mcuxClSession_Handle_t session UNUSED_PARAM,
    mcuxClHmac_Context_Generic_t * const pContext UNUSED_PARAM,
    uint8_t *const pOut UNUSED_PARAM,
    uint32_t *const pOutLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClHmac_Engine_Finalize_Els);
    //HMAC doesn't support partial processing
    *pOutLength = 0u;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClHmac_Engine_Finalize_Els, MCUXCLMAC_STATUS_ERROR);
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClHmac_AlgorithmDescriptor_t mcuxClHmac_AlgorithmDescriptor_Els = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .engineInit = mcuxClHmac_Engine_Init_Els,
    .protectionToken_engineInit = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Init_Els),
    .engineUpdate = mcuxClHmac_Engine_Update_Els,
    .protectionToken_engineUpdate = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Update_Els),
    .engineFinalize = mcuxClHmac_Engine_Finalize_Els,
    .protectionToken_engineFinalize = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Finalize_Els),
    .engineOneshot = mcuxClHmac_Engine_Oneshot_Els,
    .protectionToken_engineOneshot = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHmac_Engine_Oneshot_Els),
    .addPadding = NULL,
    .protectionToken_addPadding = 0u,
};
