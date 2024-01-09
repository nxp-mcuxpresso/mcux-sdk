/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClAeadModes_Els_GcmEngineAes.c
 *  @brief implementation of the AES GCM Engine functions of the mcuxClAeadModes component */

#include <mcuxClToolchain.h>
#include <mcuxClAead.h>
#include <internal/mcuxClAeadModes_Internal.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEls.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClAes.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_EngineAesGcmEls)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAeadModes_EngineAesGcmEls (
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClAeadModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t options  //!< options is a bitmask with one bit reserved for each of the operations
  )
{
    /* [Design]

        - Note:
            - options is a bitmask:  1: aad, 2: iv, 4: data, 8: finish

        - Preconditions
            - mode in context has been initialized
            - inLength is a multiple of the block size (16 bytes)

        - IV (options == iv)
            - if(options == finish), the IV final process
            - or use ELS in auth cipher mode initialize stage to create the partial starting counter state J0

        - AAD (options == aad)
            - use ELS in auth cipher mode AAD stage to create the starting tag

        - DATA (options == data)
            - use ELS in auth cipher mode Process message stage to output the processed text to pOut and update the tag to state of Context

        - FINAL  (options == finish)
            - use ELS in auth cipher mode Final stage to create the final tag to pOut

        - exit
    */

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_EngineAesGcmEls);

    /* Initialize ELS key info based on the key in the context. */
    mcuxClEls_KeyIndex_t keyIdx = (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key);
    uint8_t const * pKey = mcuxClKey_getLoadedKeyData(pContext->key);
    uint32_t keyLength = mcuxClKey_getSize(pContext->key);

    /* Initialize ELS options. */
    mcuxClEls_AeadOption_t elsOptions;
    elsOptions.word.value = 0u;
    elsOptions.bits.dcrpt  = (uint8_t)pContext->common.mode->algorithm->direction;
    elsOptions.bits.acpsie = (uint8_t)MCUXCLELS_AEAD_STATE_IN_ENABLE;
    elsOptions.bits.lastinit = (uint8_t)MCUXCLELS_AEAD_LASTINIT_FALSE;

    if (MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key))
    {
        elsOptions.bits.extkey = MCUXCLELS_CIPHER_EXTERNAL_KEY;
    }
    else if (MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->key))
    {
        elsOptions.bits.extkey = MCUXCLELS_CIPHER_INTERNAL_KEY;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
    }

    if(0u != (options & MCUXCLAEADMODES_ENGINE_OPTION_IV_MASK))
    {
        if((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_MASK) == MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL)
        {
            /* Disable state input for one-time init */
            elsOptions.bits.acpsie = (uint8_t)MCUXCLELS_AEAD_STATE_IN_DISABLE;

            MCUX_CSSL_FP_FUNCTION_CALL(retInit, mcuxClEls_Aead_Init_Async(elsOptions,
                                                                        keyIdx,
                                                                        pKey,
                                                                        keyLength,
                                                                        pIn,
                                                                        inLength,
                                                                        pContext->state));

            if (MCUXCLELS_STATUS_OK_WAIT != retInit)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
            }
            MCUX_CSSL_FP_FUNCTION_CALL(ivWaitRet, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLAEADMODES_DMA_STEP));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

            if (MCUXCLELS_STATUS_OK != ivWaitRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
            }
        }
        else
        {
            if((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START) == MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START)
            {
                /* Disable state input for first partial init */
                elsOptions.bits.acpsie = (uint8_t)MCUXCLELS_AEAD_STATE_IN_DISABLE;
            }

            if((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL) == MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL)
            {
                /* Enable lastinit for final partial init */
                elsOptions.bits.lastinit = (uint8_t)MCUXCLELS_AEAD_LASTINIT_TRUE;
            }

            MCUX_CSSL_FP_FUNCTION_CALL(retInitPartial, mcuxClEls_Aead_PartialInit_Async(elsOptions,
                                                                                      keyIdx,
                                                                                      pKey,
                                                                                      keyLength,
                                                                                      pIn,
                                                                                      inLength,
                                                                                      pContext->state));

            if(MCUXCLELS_STATUS_OK_WAIT != retInitPartial)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
            }

            MCUX_CSSL_FP_FUNCTION_CALL(ivWaitRet, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

            if (MCUXCLELS_STATUS_OK != ivWaitRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
            }


#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLAEADMODES_DMA_STEP));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
        }
    }

    if((options & MCUXCLAEADMODES_ENGINE_OPTION_AAD) == MCUXCLAEADMODES_ENGINE_OPTION_AAD)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ret_updateAad, mcuxClEls_Aead_UpdateAad_Async(elsOptions,
                                                                               keyIdx,
                                                                               pKey,
                                                                               keyLength,
                                                                               pIn,
                                                                               inLength,
                                                                               pContext->state));

        if (ret_updateAad != MCUXCLELS_STATUS_OK_WAIT)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(aadWait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (aadWait != MCUXCLELS_STATUS_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_SkeletonAesGcm, MCUXCLAEAD_STATUS_ERROR);
        }


#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state  , MCUXCLAEADMODES_DMA_STEP));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */
    }

    if(0u != (options & MCUXCLAEADMODES_ENGINE_OPTION_DATA_MASK))
    {
        if(((options & MCUXCLAEADMODES_ENGINE_OPTION_DATA_FINAL) == MCUXCLAEADMODES_ENGINE_OPTION_DATA_FINAL)
            && (MCUXCLAES_BLOCK_SIZE != pContext->partialDataLength))
        {
            /* Enable special processing for final, partial block */
            elsOptions.bits.msgendw = (uint8_t)pContext->partialDataLength;
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_updateData, mcuxClEls_Aead_UpdateData_Async(elsOptions,
                                                                                 keyIdx,
                                                                                 pKey,
                                                                                 keyLength,
                                                                                 pIn,
                                                                                 inLength,
                                                                                 pOut,
                                                                                 pContext->state));

        if (ret_updateData != MCUXCLELS_STATUS_OK_WAIT)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(waitData, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (waitData != MCUXCLELS_STATUS_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state  , MCUXCLAEADMODES_DMA_STEP));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    }

    if((options & MCUXCLAEADMODES_ENGINE_OPTION_FINISH) == MCUXCLAEADMODES_ENGINE_OPTION_FINISH)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ret_finish, mcuxClEls_Aead_Finalize_Async(elsOptions,
                                                                           keyIdx,
                                                                           pKey,
                                                                           keyLength,
                                                                           pContext->aadLength,
                                                                           pContext->dataLength,
                                                                           pOut,
                                                                           pContext->state));

        if (ret_finish != MCUXCLELS_STATUS_OK_WAIT)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(waitFinish, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (waitFinish != MCUXCLELS_STATUS_OK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pOut  , MCUXCLELS_AEAD_TAG_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_EngineAesGcmEls, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_MASK) == MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Aead_Init_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START) == MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START)
                                 || ((options & MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT) == MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Aead_PartialInit_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_AAD) == MCUXCLAEADMODES_ENGINE_OPTION_AAD),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Aead_UpdateAad_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL((0u != (options & MCUXCLAEADMODES_ENGINE_OPTION_DATA_MASK)),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Aead_UpdateData_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_FINISH) == MCUXCLAEADMODES_ENGINE_OPTION_FINISH),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Aead_Finalize_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        )
    );
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClAeadModes_AlgorithmDescriptor_t mcuxClAeadModes_AlgorithmDescriptor_Aes_Gcm_enc = {
    .pSkeleton = mcuxClAeadModes_SkeletonAesGcm,
    .pEngine = mcuxClAeadModes_EngineAesGcmEls,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_SkeletonAesGcm),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_EngineAesGcmEls),
    .direction = MCUXCLELS_AEAD_ENCRYPT
};

const mcuxClAeadModes_AlgorithmDescriptor_t mcuxClAeadModes_AlgorithmDescriptor_Aes_Gcm_dec = {
    .pSkeleton = mcuxClAeadModes_SkeletonAesGcm,
    .pEngine = mcuxClAeadModes_EngineAesGcmEls,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_SkeletonAesGcm),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_EngineAesGcmEls),
    .direction = MCUXCLELS_AEAD_DECRYPT
};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()