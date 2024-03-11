/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/** @file  mcuxClOsccaSm2_Cipher_Crypt.c
 *  @brief implementation of the Internal Encryption and Decryption functions of the mcuxClOsccaSm2 component when CRYPT mode */

#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <mcuxClKey.h>
#include <mcuxClCipher.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClBuffer.h>
#include <internal/mcuxClBuffer_Internal.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClCipher_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process, mcuxClCipher_CryptFunc_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process(
  mcuxClSession_Handle_t session,
  mcuxClOsccaSm2_Cipher_Context_t *pCtx,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxClOsccaSm2_Decrypt_Param_t* pParamsDec
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process);

    /* Set up SM2 key, to be used internally in SM2 functions */
    uint8_t* pKeyData = mcuxClKey_getKeyData(pCtx->pKey);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(pCtx->pKey);
    mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *pAlgo = (mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *) pCtx->common.pMode->pAlgorithm;
    uint32_t c1Len = (uint32_t)pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE;
    uint32_t c3Len = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint32_t processDataLen = pCtx->proDataLen;
    uint32_t inLen = inLength;

    // pIn = C1 || C3 || Cipher
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("reinterpret the API strcture type to internal structure type.")
    pParamsDec->pPrivateKey = pKeyData;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint32_t inOffset = 0u;

    //for first process, input C1 part
    if(processDataLen < c1Len)
    {
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set inLength properly to make sure not to wrap")
       uint32_t remainC1Len = (pCtx->proDataLen + inLen <= c1Len) ? inLen : (c1Len - pCtx->proDataLen);
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
       //copy new input data
       MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read(pIn, inOffset, pCtx->pC1Buffer + pCtx->proDataLen, remainC1Len));
       (void)readStatus;

       pCtx->proDataLen = pCtx->proDataLen + remainC1Len;
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("The range of inOffset will be [1 : c1Len]")
       inOffset += remainC1Len;
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
       inLen -= remainC1Len;
    }

    //for second process, staging C3 input, then process in the final stage
    if((inLen > 0U) && (processDataLen < (c1Len + c3Len)))
    {
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set inLength properly to make sure not to wrap")
       uint32_t remainC3Len = (pCtx->proDataLen + inLen <= (c1Len + c3Len)) ? inLen : (c1Len + c3Len - pCtx->proDataLen);
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_ARRAY_OUT_OF_BOUNDS("pCtx->proDataLen - c1Len cannot be negative" )
       MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read(pIn, inOffset, pCtx->pC3Buffer + pCtx->proDataLen - c1Len, remainC3Len));
       (void)readStatus;
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ARRAY_OUT_OF_BOUNDS()

       pCtx->proDataLen = pCtx->proDataLen + remainC3Len;
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("The range of inOffset will be [c1Len+1 : c3Len]")
       inOffset += remainC3Len;
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
       inLen -= remainC3Len;
    }

    //Process C1 part and new input data
    if((pCtx->proDataLen >= c1Len + c3Len) && (processDataLen <= c1Len + c3Len) && (inLen > 0U))
    {
       pParamsDec->pC1 = pCtx->pC1Buffer;
       MCUXCLBUFFER_DERIVE_RO(pInput, pIn, inOffset);
       pParamsDec->pInput = pInput;
       pParamsDec->pC3 = NULL;
       pParamsDec->pOutput = pOut;
       pParamsDec->inputLength = (uint16_t)inLen;
       pParamsDec->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_INIT | MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE;
       /* Call function mcuxClOsccaSm2_Decrypt */
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsDec->pC3")
       MCUX_CSSL_FP_FUNCTION_CALL(SM2DecRet, pAlgo->pDecryptMode(session, pParamsDec));
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
       if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != (uint16_t)SM2DecRet)
       {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
       }
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
       *pOutLength += inLen;
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
       pCtx->proDataLen += inLen;
    }

    if((inLen > 0U) && (processDataLen > c1Len + c3Len) && (pCtx->proDataLen > c1Len + c3Len))
    {
       pParamsDec->pC1 = NULL;
       pParamsDec->pInput = pIn;
       pParamsDec->pC3 = NULL;
       pParamsDec->pOutput = pOut;
       pParamsDec->inputLength = (uint16_t)inLen;
       pParamsDec->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE;
       /* Call function mcuxClOsccaSm2_Decrypt */
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsDec->pC1 and pParamsDec->pC3")
       MCUX_CSSL_FP_FUNCTION_CALL(SM2DecRet, pAlgo->pDecryptMode(session, pParamsDec));
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
       if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != (uint16_t)SM2DecRet)
       {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
       }
       pCtx->proDataLen += inLen;
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
       *pOutLength += inLen;
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process, MCUXCLCIPHER_STATUS_OK,
                            MCUX_CSSL_FP_CONDITIONAL((processDataLen < c1Len), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
                            MCUX_CSSL_FP_CONDITIONAL(((pCtx->proDataLen > c1Len) && (processDataLen < (c1Len + c3Len))),
                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read)),
                            MCUX_CSSL_FP_CONDITIONAL(((inLen > 0U) && (pCtx->proDataLen >= c1Len + c3Len)), pAlgo->decrypt_FunId)
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, mcuxClCipher_CryptFunc_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt(
  mcuxClSession_Handle_t session,
  mcuxClOsccaSm2_Cipher_Context_t *pCtx,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxClOsccaSm2_EncDec_Common_Param_t* pCommParms,
  uint32_t steps
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt);

    /* Set up SM2 key, to be used internally in SM2 functions */
    uint8_t* pKeyData = mcuxClKey_getKeyData(pCtx->pKey);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(pCtx->pKey);
    mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *pAlgo = (mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *) pCtx->common.pMode->pAlgorithm;
    uint32_t c1Len = (uint32_t)pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE;
    uint32_t c3Len = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;

    // pIn = C1 || C3 || Cipher
    /* Create a structure for mcuxClOsccaSm2_Decrypt function */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaSm2_Decrypt_Param_t* pParamsDec = (mcuxClOsccaSm2_Decrypt_Param_t*)pCommParms;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("reinterpret the API strcture type to internal structure type.")
    pParamsDec->pPrivateKey = pKeyData;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    if(steps == MCUXCLCIPHER_OPTION_ONESHOT)
    {
        pParamsDec->pC1 = pIn;
        MCUXCLBUFFER_DERIVE_RO(pInput, pIn, c1Len + c3Len);
        pParamsDec->pInput = pInput;
        MCUXCLBUFFER_DERIVE_RO(pC3, pIn, c1Len);
        pParamsDec->pC3 = pC3;
        pParamsDec->pOutput = pOut;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set inLength properly to make sure not wrap.")
        pParamsDec->inputLength = (uint16_t)(inLength - (c1Len + c3Len));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        pParamsDec->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT;
        /* Call function mcuxClOsccaSm2_Decrypt */
        MCUX_CSSL_FP_FUNCTION_CALL(SM2DecRet, pAlgo->pDecryptMode(session, pParamsDec));
        if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != (uint16_t)SM2DecRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
        *pOutLength += (inLength - (c1Len + c3Len));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    if(steps == MCUXCLCIPHER_OPTION_PROCESS)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(SM2DecProRet, mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process(session, pCtx,
                                                pIn, inLength, pOut, pOutLength, pParamsDec));
        if (MCUXCLCIPHER_STATUS_OK != SM2DecProRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
        }
    }

    if(steps == MCUXCLCIPHER_OPTION_FINISH)
    {
       /* Check if the input data is valid */
       if (0u == pCtx->proDataLen)
       {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
       }

       pParamsDec->pC1 = NULL;
       pParamsDec->pInput = NULL;
       pParamsDec->pC3 = pCtx->pC3Buffer;
       pParamsDec->pOutput = NULL;
       pParamsDec->inputLength = 0U;
       pParamsDec->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE;
       /* Call function mcuxClOsccaSm2_Decrypt */
       MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsDec->pC1, pParamsDec->pInput and pParamsDec->pOutput")
       MCUX_CSSL_FP_FUNCTION_CALL(SM2DecRet, pAlgo->pDecryptMode(session, pParamsDec));
       MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
       if (MCUXCLOSCCASM2_STATUS_DECRYPT_OK != (uint16_t)SM2DecRet)
       {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
       }
       pCtx->proDataLen = 0U;
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt, MCUXCLCIPHER_STATUS_OK,
                    MCUX_CSSL_FP_CONDITIONAL((steps == MCUXCLCIPHER_OPTION_ONESHOT), pAlgo->decrypt_FunId),
                    MCUX_CSSL_FP_CONDITIONAL((steps == MCUXCLCIPHER_OPTION_PROCESS), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt_Process)),
                    MCUX_CSSL_FP_CONDITIONAL((steps == MCUXCLCIPHER_OPTION_FINISH), pAlgo->decrypt_FunId)
    );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, mcuxClCipher_CryptFunc_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt(
  mcuxClSession_Handle_t session,
  mcuxClOsccaSm2_Cipher_Context_t *pCtx,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxClOsccaSm2_EncDec_Common_Param_t* pCommParms,
  uint32_t steps
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt);

    /* Set up SM2 key, to be used internally in SM2 functions */
    uint8_t* pKeyData = mcuxClKey_getKeyData(pCtx->pKey);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(pCtx->pKey);
    mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *pAlgo = (mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *) pCtx->common.pMode->pAlgorithm;
    uint32_t c1Len = (uint32_t)pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE;
    uint32_t c3Len = MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    uint32_t processDataLen = pCtx->proDataLen;

    /* Create a structure for mcuxClOsccaSm2_Encrypt function */
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClOsccaSm2_Encrypt_Param_t* pParamsEnc = (mcuxClOsccaSm2_Encrypt_Param_t*)pCommParms;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("reinterpret the API strcture type to internal structure type.")
    pParamsEnc->pPublicKey = pKeyData;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    if(steps == MCUXCLCIPHER_OPTION_ONESHOT)
    {
        pParamsEnc->pInput = pIn;
        pParamsEnc->pC1 = pOut;
        MCUXCLBUFFER_DERIVE_RW(pOutput, pOut, c1Len + c3Len);
        pParamsEnc->pOutput = pOutput;
        MCUXCLBUFFER_DERIVE_RW(pC3, pOut, c1Len);
        pParamsEnc->pC3 = pC3;
        pParamsEnc->inputLength = (uint16_t)inLength;
        pParamsEnc->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_ONE_SHOT;
        /* Call function mcuxClOsccaSm2_Encrypt */
        MCUX_CSSL_FP_FUNCTION_CALL(SM2EncRet, pAlgo->pEncryptMode(session, pParamsEnc));
        if (MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != (uint16_t)SM2EncRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
        *pOutLength += c1Len + c3Len + inLength;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    }

    if(steps == MCUXCLCIPHER_OPTION_PROCESS)
    {
        //for first process, output C1 part
        if(0U == processDataLen)
        {
            pParamsEnc->pInput = pIn;
            pParamsEnc->pC1 = pOut;
            pParamsEnc->pC3 = NULL;
            MCUXCLBUFFER_DERIVE_RW(pOutput, pOut, c1Len + c3Len);
            pParamsEnc->pOutput = pOutput;
            pParamsEnc->inputLength = (uint16_t)inLength;
            pParamsEnc->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_INIT | MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE;
            /* Call function mcuxClOsccaSm2_Encrypt */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsEnc->pC3")
            MCUX_CSSL_FP_FUNCTION_CALL(SM2EncRet, pAlgo->pEncryptMode(session, pParamsEnc));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
            if (MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != (uint16_t)SM2EncRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
            }

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
            *pOutLength += c1Len + c3Len + inLength;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            pCtx->proDataLen = inLength;
        }
        //for later process, output C2 part
        else
        {
            pParamsEnc->pInput = pIn;
            pParamsEnc->pC1 = NULL;
            pParamsEnc->pC3 = NULL;
            pParamsEnc->pOutput = pOut;
            pParamsEnc->inputLength = (uint16_t)inLength;
            pParamsEnc->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_UPDATE;
            /* Call function mcuxClOsccaSm2_Encrypt */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsEnc->pC1 and pParamsEnc->pC3")
            MCUX_CSSL_FP_FUNCTION_CALL(SM2EncRet, pAlgo->pEncryptMode(session, pParamsEnc));
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
            if (MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != (uint16_t)SM2EncRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
            }
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *pOutLength properly to make sure not wrap.")
            *pOutLength += inLength;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        }
    }

    if(steps == MCUXCLCIPHER_OPTION_FINISH)
    {
        /* Check if the input data is valid */
        if (0u == pCtx->proDataLen)
        {
           MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
        }

        pParamsEnc->pInput = NULL;
        pParamsEnc->pC1 = NULL;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("The integer overflow is intentional")
        MCUXCLBUFFER_DERIVE_RW(pC3, pOut, c1Len - *pOutLength);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        pParamsEnc->pC3 = pC3;
        pParamsEnc->pOutput = NULL;
        pParamsEnc->inputLength = 0U;
        pParamsEnc->options = MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE;
        /* Call function mcuxClOsccaSm2_Encrypt */
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_DEREFERENCE_NULL_POINTER("It is intentional to set NULL to pParamsEnc->pInput, pParamsEnc->pOutput and pParamsEnc->pC1")
        MCUX_CSSL_FP_FUNCTION_CALL(SM2EncRet, pAlgo->pEncryptMode(session, pParamsEnc));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DEREFERENCE_NULL_POINTER()
        if (MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != (uint16_t)SM2EncRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
        }
        *pOutLength += 0U;
        pCtx->proDataLen = 0U;
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt, MCUXCLCIPHER_STATUS_OK, pAlgo->encrypt_FunId);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, mcuxClCipher_CryptFunc_t)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaSm2_Cipher_SkeletonSM2_Core(
  mcuxClSession_Handle_t session,
  mcuxClOsccaSm2_Cipher_Context_t *pCtx,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t cpuWaUsedByte,
  uint32_t steps
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core);

    /* Set up domain parameters, to be used internally in SM2 functions */
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(pCtx->pKey);
    mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *pAlgo = (mcuxClOsccaSm2_Cipher_AlgorithmDescriptor_t *) pCtx->common.pMode->pAlgorithm;
    if ((steps == MCUXCLCIPHER_OPTION_ONESHOT) || (steps == MCUXCLCIPHER_OPTION_INIT))
    {
        /* Create SM2 encryption/decryption internal context */
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(pSm2DomainParams->p.wNumBytes, 8u, 80u, MCUXCLCIPHER_STATUS_INVALID_INPUT)
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("cpu workarea size + MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pSm2DomainParams->p.wNumBytes) can't exceed UINT32_MAX.")
        cpuWaUsedByte += MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pSm2DomainParams->p.wNumBytes);
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx->pEncDecCtx = (mcuxClOsccaSm2_EncDecCtx_t *)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pSm2DomainParams->p.wNumBytes) / sizeof(uint32_t));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
        if(NULL == pCtx->pEncDecCtx)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_FAILURE);
        }

        if((steps == MCUXCLCIPHER_OPTION_INIT) && (MCUXCLOSCCASM2_DECRYPT == pAlgo->direction))
        {
            /* Create C1 temp buffer for SM2 decryption */
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("cpu workarea size + pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE can't exceed UINT32_MAX.")
            cpuWaUsedByte += (uint32_t)pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            pCtx->pC1Buffer = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, ((uint32_t)pSm2DomainParams->p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
            if(NULL == pCtx->pC1Buffer)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_FAILURE);
            }

            pCtx->proDataLen = 0U;
        }

        if((steps == MCUXCLCIPHER_OPTION_INIT) && (MCUXCLOSCCASM2_ENCRYPT == pAlgo->direction))
        {
           pCtx->proDataLen = 0U;
        }
    }

    if(steps != MCUXCLCIPHER_OPTION_INIT)
    {
        /*****************************************************/
        /* Perform SM2 Enc/Dec operation                     */
        /*****************************************************/
        /* Create a common parameter structure for SM2 Encryption and Decryption function */
        mcuxClOsccaSm2_EncDec_Common_Param_t* pCommParms = NULL;
        /* Create SM2 encryption/decryption internal context */
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCommParms = (mcuxClOsccaSm2_EncDec_Common_Param_t*)mcuxClSession_allocateWords_cpuWa(session, MCUXCLOSCCASM2_CIPHER_ENCDEC_FIXED_SIZEOF_WA_CPU / sizeof(uint32_t));
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
        if(NULL == pCommParms)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_FAILURE);
        }

        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("reinterpret the API strcture type to internal structure type.")
        pCommParms->pEncDecCtx = (mcuxClOsccaSm2_EncDecCtx_t*)pCtx->pEncDecCtx;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        pCommParms->domainParameters.pA = pSm2DomainParams->pA;
        pCommParms->domainParameters.pB = pSm2DomainParams->pB;
        pCommParms->domainParameters.p.pMPInt = pSm2DomainParams->p.pMPInt;
        pCommParms->domainParameters.p.wNumBytes = pSm2DomainParams->p.wNumBytes;
        pCommParms->domainParameters.pG = pSm2DomainParams->pG;
        pCommParms->domainParameters.n.pMPInt = pSm2DomainParams->n.pMPInt;
        pCommParms->domainParameters.n.wNumBytes = pSm2DomainParams->n.wNumBytes;

        if(MCUXCLOSCCASM2_DECRYPT == pAlgo->direction)
        {
            /* Call function mcuxClOsccaSm2_Decrypt */
            MCUX_CSSL_FP_FUNCTION_CALL(SM2DecRet, mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt(session, pCtx,
                                                    pIn, inLength, pOut, pOutLength, pCommParms, steps));
            if (MCUXCLCIPHER_STATUS_OK != SM2DecRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
            }
        }
        else
        {
            /* Call function mcuxClOsccaSm2_Encrypt */
            MCUX_CSSL_FP_FUNCTION_CALL(SM2EncRet, mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt(session, pCtx,
                                                    pIn, inLength, pOut, pOutLength, pCommParms, steps));
            if (MCUXCLCIPHER_STATUS_OK != SM2EncRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
            }
        }

        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_CIPHER_ENCDEC_FIXED_SIZEOF_WA_CPU / sizeof(uint32_t));
    }

    if ((steps == MCUXCLCIPHER_OPTION_ONESHOT) || (steps == MCUXCLCIPHER_OPTION_FINISH))
    {
        mcuxClSession_freeWords_cpuWa(session, cpuWaUsedByte / sizeof(uint32_t));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core, MCUXCLCIPHER_STATUS_OK,
        MCUX_CSSL_FP_CONDITIONAL(steps != MCUXCLCIPHER_OPTION_INIT,
            MCUX_CSSL_FP_CONDITIONAL(MCUXCLOSCCASM2_DECRYPT == pAlgo->direction, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Cipher_SkeletonSM2_Decrypt)),
            MCUX_CSSL_FP_CONDITIONAL(MCUXCLOSCCASM2_ENCRYPT == pAlgo->direction, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Cipher_SkeletonSM2_Encrypt))));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Cipher_SkeletonSM2, mcuxClCipher_CryptFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClOsccaSm2_Cipher_SkeletonSM2(
  mcuxClSession_Handle_t session,
  mcuxClCipher_Context_t * const pContext,
  mcuxClKey_Handle_t pKey,
  mcuxClCipher_Mode_t pMode,
  mcuxCl_InputBuffer_t pIv UNUSED_PARAM,
  uint32_t ivLength UNUSED_PARAM,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t steps
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Cipher_SkeletonSM2);

    /* Correct Context type for SM2 Skeleton */
    mcuxClOsccaSm2_Cipher_Context_t * pCtx = NULL;
    uint32_t cpuWaUsedByte = 0U;
    if(MCUXCLCIPHER_OPTION_ONESHOT == steps)
    {
        if(NULL == session)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2, MCUXCLCIPHER_STATUS_ERROR);
        }

        /* Create context for OneShot */
        cpuWaUsedByte = sizeof(mcuxClOsccaSm2_Cipher_Context_t) + MCUXCLOSCCA_SIZE_ALIGN_OFFSET;
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx = (mcuxClOsccaSm2_Cipher_Context_t *)mcuxClSession_allocateWords_cpuWa(session, cpuWaUsedByte / sizeof(uint32_t));
        if(NULL == pCtx)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2, MCUXCLCIPHER_STATUS_FAILURE);
        }

        pCtx->pKey = pKey;
        pCtx->common.pMode = pMode;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    }
    else if (MCUXCLCIPHER_OPTION_INIT == steps)
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx = (mcuxClOsccaSm2_Cipher_Context_t *) pContext;
        pCtx->pKey = pKey;
        pCtx->common.pMode = pMode;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    }
    else
    {
        MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
        pCtx = (mcuxClOsccaSm2_Cipher_Context_t *) pContext;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("The type of pCtx is mcuxClOsccaSm2_Cipher_Context_t*")
    MCUX_CSSL_FP_FUNCTION_CALL(RetCipherCore, mcuxClOsccaSm2_Cipher_SkeletonSM2_Core(session, pCtx,
                                            pIn, inLength, pOut, pOutLength, cpuWaUsedByte, steps));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    if (MCUXCLCIPHER_STATUS_FAULT_ATTACK == RetCipherCore)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Cipher_SkeletonSM2, MCUXCLCIPHER_STATUS_FAULT_ATTACK);
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Cipher_SkeletonSM2, RetCipherCore, MCUXCLCIPHER_STATUS_FAULT_ATTACK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Cipher_SkeletonSM2_Core));
}
