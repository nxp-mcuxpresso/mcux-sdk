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

/** @file  mcuxClRsa_Util_Decrypt.c
 *  @brief mcuxClRsa: implementation of RSA Decryption function
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxClToolchain.h>

#include <mcuxClCipher_Constants.h>
#include <mcuxClCipher_Types.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Macros.h>
#include <mcuxClHash.h>
#include <mcuxClPkc.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClBuffer.h>

#include <internal/mcuxClCipher_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClBuffer_Internal.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <mcuxCsslAnalysis.h>

MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClRsa_Util_decrypt(
    mcuxClSession_Handle_t           pSession,
    mcuxClCipher_Context_t * const   pContext UNUSED_PARAM,
    mcuxClKey_Handle_t               key,
    mcuxClCipher_Mode_t              mode,
    mcuxCl_InputBuffer_t             pLabel,
    uint32_t                        labelLength,
    mcuxCl_InputBuffer_t             pIn,
    uint32_t                        inLength UNUSED_PARAM,
    mcuxCl_Buffer_t                  pOut,
    uint32_t * const                pOutLength,
    uint32_t                        steps UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_Util_decrypt);

  /*****************************************************/
  /* Verify and set up the RSA key type                */
  /*****************************************************/

  mcuxClRsa_Key rsaKey;
  mcuxClKey_AlgorithmId_t keyAlgoId = mcuxClKey_getAlgoId(key);
  if(MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATEPLAIN == keyAlgoId)
  {
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClRsa_KeyData_Plain_t * pRsaKeyData = (mcuxClRsa_KeyData_Plain_t *) mcuxClKey_getKeyData(key);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    rsaKey.keytype = MCUXCLRSA_KEY_PRIVATEPLAIN;
    rsaKey.pMod1 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->modulus);
    rsaKey.pExp1 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->exponent);
  }
  else if((MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRT == keyAlgoId) || (MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRTDFA == keyAlgoId))
  {
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClRsa_KeyData_Crt_t * pRsaKeyData = (mcuxClRsa_KeyData_Crt_t *) mcuxClKey_getKeyData(key);
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
    rsaKey.pMod1 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->p);
    rsaKey.pMod2 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->q);
    rsaKey.pQInv = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->qInv);
    rsaKey.pExp1 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->dp);
    rsaKey.pExp2 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->dq);
    if(MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATECRT == keyAlgoId)
    {
      rsaKey.keytype = MCUXCLRSA_KEY_PRIVATECRT;
    }
    else
    {
      rsaKey.keytype = MCUXCLRSA_KEY_PRIVATECRT_DFA;
      rsaKey.pExp3 = (mcuxClRsa_KeyEntry_t *) &(pRsaKeyData->e);
    }
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT);
  }

  /*****************************************************/
  /* Initialization                                    */
  /*****************************************************/

  /* Initialize PKC */
  uint32_t cpuWaUsedWord = sizeof(mcuxClPkc_State_t) / sizeof(uint32_t);
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaUsedWord);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
  if(NULL == pkcStateBackup )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION);
  }

  MCUXCLPKC_FP_REQUEST_INITIALIZE(pSession, pkcStateBackup, mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  /*****************************************************/
  /* Import the input                                  */
  /*****************************************************/

  const uint32_t keyBitLength = mcuxClKey_getSize(key);
  const uint32_t keyByteLength = keyBitLength / 8u;

  /* Allocate input buffer in PKC WA */
  const uint32_t inputSizeWord = ((MCUXCLRSA_KEY_PRIVATEPLAIN == rsaKey.keytype) ? MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength) : MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(keyByteLength)) / sizeof(uint32_t);
  uint8_t * pInput = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, inputSizeWord);
  if(NULL == pInput)
  {
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }

  /* Import the input to PKC RAM in little endian. */
  MCUX_CSSL_FP_FUNCTION_CALL(readStatus, mcuxClBuffer_read_reverse(pIn, 0u, pInput, keyByteLength));
  if(MCUXCLBUFFER_STATUS_OK != readStatus)
  {
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, readStatus,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse));
  }

  /*****************************************************/
  /* Perform RSA private operation                     */
  /*****************************************************/

  /* Allocate encodedMessage buffer in CPU WA */
  cpuWaUsedWord += MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(keyByteLength);
  const uint32_t encodedMessageSizeWord = MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(keyByteLength);
  uint8_t * pEncodedMessage = (uint8_t *) mcuxClSession_allocateWords_cpuWa(pSession, encodedMessageSizeWord);
  if(NULL == pEncodedMessage)
  {
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }

  uint32_t retVal_RsaPrivate = MCUXCLRSA_STATUS_ERROR;
  MCUXCLBUFFER_INIT(pEncodedMessageBuf, NULL, pEncodedMessage, keyByteLength);
  if(MCUXCLRSA_KEYTYPE_INTERNAL_PRIVATEPLAIN == keyAlgoId)
  {
    MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPrivatePlain, mcuxClRsa_privatePlain(pSession, &rsaKey, (uint8_t *)pInput, pEncodedMessageBuf));
    retVal_RsaPrivate = retVal_RsaPrivatePlain;
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPrivateCrt, mcuxClRsa_privateCRT(pSession, &rsaKey, (uint8_t *)pInput, pEncodedMessageBuf));
    retVal_RsaPrivate = retVal_RsaPrivateCrt;
  }

  /* Check return value */
  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPrivate)
  {
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT,
        MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == rsaKey.keytype),
                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == rsaKey.keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == rsaKey.keytype)),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK != retVal_RsaPrivate)
  {
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_ERROR);
  }
  /* To save PKC space, remove the ones already allocated before decryption */
  else
  {
    /* Recover pkc workarea */
    mcuxClSession_freeWords_pkcWa(pSession, inputSizeWord);
  }

  /*****************************************************/
  /* Perform padding operation                         */
  /*****************************************************/

  /* Get the algorithm descriptor */
  mcuxClRsa_Cipher_AlgorithmDescriptor_t * pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) mode->pAlgorithm;

      mcuxClRsa_PadVerModeEngine_t pPaddingFunction = pAlgorithmDescriptor->pCryptMode;
      MCUX_CSSL_FP_COUNTER_STMT(uint32_t paddingFunctionId = pAlgorithmDescriptor->crypt_FunId);

  /* Call the padding function */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_PaddingOperation, pPaddingFunction(
                              /* mcuxClSession_Handle_t       pSession,           */ pSession,
                              /* mcuxCl_InputBuffer_t         pInput,             */ pEncodedMessageBuf,
                              /* const uint32_t              inputLength,        */ keyByteLength,
                              /* mcuxCl_Buffer_t              pVerificationInput, */ NULL, /* unused */
                              /* mcuxClHash_Algo_t            pHashAlgo,          */ pAlgorithmDescriptor->pHashAlgo,
                              /* mcuxCl_InputBuffer_t         pLabel,             */ pLabel,
                              /* const uint32_t              saltlabelLength,    */ labelLength,
                              /* const uint32_t              keyBitLength,       */ keyBitLength,
                              /* const uint32_t              options,            */ 0u, /* unused */
                              /* mcuxCl_Buffer_t              pOutput             */ pOut,
                              /* uint32_t * const            pOutLength          */ pOutLength
  ));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_PaddingOperation)
  {
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT,
        MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == rsaKey.keytype),
                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
        MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == rsaKey.keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == rsaKey.keytype)),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
        paddingFunctionId,
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK != retVal_PaddingOperation)
  {
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_ERROR);
  }
  else
  {
    /* Left empty intentionally */
  }


  /*****************************************************/
  /* Clean up and exit                                 */
  /*****************************************************/

  MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
          mcuxClRsa_Util_decrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_decrypt, MCUXCLCIPHER_STATUS_OK,
    MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_read_reverse),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == rsaKey.keytype),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
    MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == rsaKey.keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == rsaKey.keytype)),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
    paddingFunctionId,
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
}
