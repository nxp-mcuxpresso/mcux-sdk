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

/** @file  mcuxClAeadModes_Els_CcmEngineAes.c
 *  @brief implementation of the AES CCM Engine functions of the mcuxClAeadModes component */

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


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_EngineAesCcmEls)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAeadModes_EngineAesCcmEls (
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
            - options is a bitmask:  1: auth, 2: enc, 3: aead, 4: init, 8: finish
            - processing is done in this particular order such that in-place encryption/decryption is supported

        - Preconditions
            - mode in context has been initialized
            - inLength is a multiple of the block size (16 bytes)

        - Initialization
            - set pData equal to pIn

        - Decryption  (options == enc / aead AND direction = decryption)
            - set pData equal to pOut
            - use ELS in CTR mode to decrypt the data pIn and store the output at pOut

        - Authentication (options == auth / aead)
            - use ELS in CBC-MAC mode to update the state in the context with the contents of pData

        - Encryption  (options == enc / aead AND direction = encryption)
            - use ELS in CTR mode to encrypt the data pIn and store the output at pOut

        - exit
    */

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_EngineAesCcmEls);
    const uint32_t direction = pContext->common.mode->algorithm->direction;

    /* Initialize ELS key info based on the key in the context. */
    mcuxClEls_KeyIndex_t keyIdx = (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->key);
    uint8_t const * pKey = mcuxClKey_getLoadedKeyData(pContext->key);
    uint32_t keyLength = mcuxClKey_getSize(pContext->key);

    /* Initialize ELS CMAC options. */
    mcuxClEls_CmacOption_t cmacOpt;
    cmacOpt.bits.initialize = MCUXCLELS_CMAC_INITIALIZE_DISABLE;
    cmacOpt.bits.finalize = MCUXCLELS_CMAC_FINALIZE_DISABLE;

    /* Initialize ELS Cipher options. */
    mcuxClEls_CipherOption_t cipherElsOpt;
    cipherElsOpt.word.value = 0u;
    cipherElsOpt.bits.dcrpt  = MCUXCLELS_CIPHER_ENCRYPT;
    cipherElsOpt.bits.cphmde = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CTR;
    cipherElsOpt.bits.cphsoe = MCUXCLELS_CIPHER_STATE_OUT_ENABLE;
    #ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
    cipherElsOpt.bits.cphsie = MCUXCLELS_CIPHER_STATE_IN_ENABLE;
    #endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */

    // Get key location
    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->key))
    {
        cmacOpt.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_ENABLE;
        cipherElsOpt.bits.extkey = MCUXCLELS_CIPHER_EXTERNAL_KEY;
    }
    else if(MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->key))
    {
        cmacOpt.bits.extkey = MCUXCLELS_CMAC_EXTERNAL_KEY_DISABLE;
        cipherElsOpt.bits.extkey = MCUXCLELS_CIPHER_INTERNAL_KEY;
    }
    else
    {
        // Error: no key loaded
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
    }

    if(options == MCUXCLAEADMODES_ENGINE_OPTION_INIT)
    {

    }

    if(((options & MCUXCLAEADMODES_ENGINE_OPTION_ENC) == MCUXCLAEADMODES_ENGINE_OPTION_ENC)
        && (MCUXCLELS_AEAD_DECRYPT == direction))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ctrRet, mcuxClEls_Cipher_Async(cipherElsOpt,
                                                               keyIdx,
                                                               pKey,
                                                               keyLength,
                                                               pIn,
                                                               inLength,
                                                               &pContext->state[48],
                                                               pOut));

        if(MCUXCLELS_STATUS_OK_WAIT != ctrRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ctrWaitRet, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != ctrWaitRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK

        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(&pContext->state[48], MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */


    }

    if((options & MCUXCLAEADMODES_ENGINE_OPTION_AUTH) == MCUXCLAEADMODES_ENGINE_OPTION_AUTH)
    {
        if((options == MCUXCLAEADMODES_ENGINE_OPTION_AEAD) && (MCUXCLELS_AEAD_DECRYPT == direction))
        {
            MCUX_CSSL_FP_FUNCTION_CALL(cmacResult, mcuxClEls_Cmac_Async(cmacOpt,
                                                                     keyIdx,
                                                                     pKey,
                                                                     keyLength,
                                                                     pOut,
                                                                     inLength,
                                                                     pContext->state));

            if( MCUXCLELS_STATUS_OK_WAIT != cmacResult)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
            }
        }
        else
        {
            MCUX_CSSL_FP_FUNCTION_CALL(cmacResult, mcuxClEls_Cmac_Async(cmacOpt,
                                                                      keyIdx,
                                                                      pKey,
                                                                      keyLength,
                                                                      pIn,
                                                                      inLength,
                                                                      pContext->state));
            if( MCUXCLELS_STATUS_OK_WAIT != cmacResult)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
            }
        }

        MCUX_CSSL_FP_FUNCTION_CALL(cmacWaitResult, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != cmacWaitResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress((uint8_t*)pContext->state, MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */


    }

    if(((options & MCUXCLAEADMODES_ENGINE_OPTION_ENC) == MCUXCLAEADMODES_ENGINE_OPTION_ENC)
      && (MCUXCLELS_AEAD_ENCRYPT == direction))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ctrRet, mcuxClEls_Cipher_Async(cipherElsOpt,
                                                               keyIdx,
                                                               pKey,
                                                               keyLength,
                                                               pIn,
                                                               inLength,
                                                               &pContext->state[48],
                                                               pOut));

        if(MCUXCLELS_STATUS_OK_WAIT != ctrRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ctrWaitRet, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        if (MCUXCLELS_STATUS_OK != ctrWaitRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
        MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(&pContext->state[48], MCUXCLELS_CMAC_OUT_SIZE));

        if (MCUXCLELS_STATUS_OK != addressComparisonResult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_ERROR);
        }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_EngineAesCcmEls, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_ENC) == MCUXCLAEADMODES_ENGINE_OPTION_ENC)
                                && (MCUXCLELS_AEAD_DECRYPT == direction),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_AUTH) == MCUXCLAEADMODES_ENGINE_OPTION_AUTH),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cmac_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        ),
        MCUX_CSSL_FP_CONDITIONAL(((options & MCUXCLAEADMODES_ENGINE_OPTION_ENC) == MCUXCLAEADMODES_ENGINE_OPTION_ENC)
                                && (MCUXCLELS_AEAD_ENCRYPT == direction),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async),
                                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
                                                                        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN
        )
    );
}
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClAeadModes_AlgorithmDescriptor_t mcuxClAeadModes_AlgorithmDescriptor_Aes_Ccm_enc = {
    .pSkeleton = mcuxClAeadModes_SkeletonAesCcm,
    .pEngine = mcuxClAeadModes_EngineAesCcmEls,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_SkeletonAesCcm),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_EngineAesCcmEls),
    .direction = MCUXCLELS_AEAD_ENCRYPT
};

const mcuxClAeadModes_AlgorithmDescriptor_t mcuxClAeadModes_AlgorithmDescriptor_Aes_Ccm_dec = {
    .pSkeleton = mcuxClAeadModes_SkeletonAesCcm,
    .pEngine = mcuxClAeadModes_EngineAesCcmEls,
    .protection_token_skeleton = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_SkeletonAesCcm),
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAeadModes_EngineAesCcmEls),
    .direction = MCUXCLELS_AEAD_DECRYPT
};
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()