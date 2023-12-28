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

/** @file  mcuxClCipherModes_Els_EngineAes.c
 *  @brief implementation of the Engine functions of the mcuxClCipher component */

#include <mcuxClToolchain.h>
#include <mcuxClEls.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClAes.h>
#include <internal/mcuxClCipher_Internal.h>
#include <internal/mcuxClCipherModes_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCipherModes_EngineEls)
  MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClCipherModes_EngineEls(
  mcuxClSession_Handle_t session UNUSED_PARAM,
  mcuxClCipherModes_Context_Aes_Els_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut
)
{
    /* [Design]

        - Preconditions
            - mode and state in context have been initialized
            - inLength is a multiple of the block size (16 bytes)

        - Operation
            - set elsOptions according to mode's required operations
            - if (CBC Decryption) : copy last input block to temporary buffer
            - perform the required operation by calling mcuxClEls_Cipher_Async
            - if (CBC Encryption) : copy last output block to ivState
            - if (CBC Decryption) : copy temporary buffer to ivState

        - Exit
    */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCipherModes_EngineEls);

    mcuxClCipherModes_Algorithm_Aes_Els_t pAlgo = (mcuxClCipherModes_Algorithm_Aes_Els_t) pContext->common.pMode->pAlgorithm;

    /* Initialize ELS key info based on the key in the context. */
    mcuxClEls_KeyIndex_t keyIdx = (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(pContext->pKey);
    uint8_t const * pKey = mcuxClKey_getLoadedKeyData(pContext->pKey);
    uint8_t tempBlock[MCUXCLAES_BLOCK_SIZE];
    uint8_t* nextState = NULL;
    uint32_t keyLength = mcuxClKey_getSize(pContext->pKey);

    /* Initialize ELS options. */
    mcuxClEls_CipherOption_t elsOptions;
    elsOptions.word.value = 0u;
    elsOptions.bits.dcrpt  = (uint8_t) pAlgo->direction;
    elsOptions.bits.cphmde = (uint8_t) pAlgo->mode;

    if(elsOptions.bits.cphmde != MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB) {
        elsOptions.bits.cphsoe = MCUXCLELS_CIPHER_STATE_OUT_ENABLE;
        #ifndef MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS
        elsOptions.bits.cphsie = MCUXCLELS_CIPHER_STATE_IN_ENABLE;
        #endif /* MCUXCL_FEATURE_ELS_NO_INTERNAL_STATE_FLAGS */
    }

    /* Copy last input block to a temp buffer to handle in-place operations. Needed in case of CBC Mode decryption */
    if(MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC == elsOptions.bits.cphmde)
    {
        if (MCUXCLELS_CIPHER_DECRYPT == pAlgo->direction)
        {
            MCUXCLMEMORY_FP_MEMORY_COPY(tempBlock, (uint8_t const*)(pIn + inLength - MCUXCLAES_BLOCK_SIZE), MCUXCLAES_BLOCK_SIZE);
            nextState = tempBlock;
        }
        else
        {
            nextState = (uint8_t*)(pOut + inLength - MCUXCLAES_BLOCK_SIZE);
        }
    }
    if (MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(pContext->pKey))
    {
        elsOptions.bits.extkey = MCUXCLELS_CIPHER_EXTERNAL_KEY;
    }
    else if (MCUXCLKEY_LOADSTATUS_COPRO == mcuxClKey_getLoadStatus(pContext->pKey))
    {
        elsOptions.bits.extkey = MCUXCLELS_CIPHER_INTERNAL_KEY;
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_EngineEls, MCUXCLCIPHER_STATUS_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(cipherResult, mcuxClEls_Cipher_Async(elsOptions,
                                                                  keyIdx,
                                                                  pKey,
                                                                  keyLength,
                                                                  pIn,
                                                                  inLength,
                                                                  (uint8_t *) pContext->ivState,
                                                                  pOut));
    if (cipherResult != MCUXCLELS_STATUS_OK_WAIT)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_EngineEls, MCUXCLCIPHER_STATUS_ERROR);
    }
    MCUX_CSSL_FP_FUNCTION_CALL(wait1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
    if (wait1 != MCUXCLELS_STATUS_OK)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_EngineEls, MCUXCLCIPHER_STATUS_ERROR);
    }

#ifdef MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK
    uint8_t *pFinalOutputStartAddress = pOut;
    uint32_t finalLength = inLength;
    if (MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CTR == pAlgo->mode)
    {
        pFinalOutputStartAddress = (uint8_t *)pContext->ivState;
        finalLength = MCUXCLAES_BLOCK_SIZE;
    }
    MCUX_CSSL_FP_FUNCTION_CALL(addressComparisonResult, mcuxClEls_CompareDmaFinalOutputAddress(pFinalOutputStartAddress, finalLength));
    if (MCUXCLELS_STATUS_OK != addressComparisonResult)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_EngineEls, MCUXCLCIPHER_STATUS_ERROR);
    }
#endif /* MCUXCL_FEATURE_ELS_DMA_FINAL_ADDRESS_READBACK */

    if(MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC == elsOptions.bits.cphmde)
    {
        MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t *) pContext->ivState, nextState, MCUXCLAES_BLOCK_SIZE);
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCipherModes_EngineEls, MCUXCLCIPHER_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation),
        MCUXCLELS_DMA_READBACK_PROTECTION_TOKEN,
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC == elsOptions.bits.cphmde),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
                                MCUX_CSSL_FP_CONDITIONAL((MCUXCLELS_CIPHER_DECRYPT == pAlgo->direction),
                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy))
                                ),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async));

}

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_NoPadding_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_None
    granularity = 16
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_None,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = 0u,
    .granularity = 16u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method1_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_ISO9797_1_Method1
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method1,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method1),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = 0u,
    .granularity = 1u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingISO9797_1_Method2_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_ISO9797_1_Method2
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method2,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method2),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = 0u,
    .granularity = 1u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Enc_PaddingPKCS7_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_PKCS7
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_PKCS7,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_PKCS7),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = 0u,
    .granularity = 1u
};



/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_ECB_Dec_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_None
    granularity = 16
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_None,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB,
    .direction = MCUXCLELS_CIPHER_DECRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = 0u,
    .granularity = 16u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_NoPadding_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_None
    granularity = 16
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_None,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 16u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method1_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_ISO9797_1_Method1
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method1,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method1),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 1u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingISO9797_1_Method2_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_ISO9797_1_Method2
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_ISO9797_1_Method2,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_ISO9797_1_Method2),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 1u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Enc_PaddingPKCS7_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_PKCS7
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_PKCS7,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_PKCS7),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 1u
};


/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CBC_Dec_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    mcuxClPadding_addPadding_None
    granularity = 16
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = mcuxClPadding_addPadding_None,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPadding_addPadding_None),
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CBC,
    .direction = MCUXCLELS_CIPHER_DECRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 16u
};

/* MISRA Ex. 20 - Rule 5.1 */
const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t mcuxClCipherModes_AlgorithmDescriptor_AES_CTR_Els = {
/* [Design]
    mcuxClCipherModes_ModeSkeletonAes
    granularity = 1
*/
    .cryptEngine = mcuxClCipherModes_EngineEls,
    .addPadding = NULL,
    .protection_token_engine = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCipherModes_EngineEls),
    .protection_token_addPadding = 0u,
    .mode = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_CTR,
    .direction = MCUXCLELS_CIPHER_ENCRYPT,
    .blockLength = MCUXCLAES_BLOCK_SIZE,
    .ivLength = MCUXCLAES_BLOCK_SIZE,
    .granularity = 1u
};
