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

/** @file  mcuxClRsa_Util_Encrypt.c
 *  @brief mcuxClRsa: implementation of RSA Encryption function
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <mcuxCsslAnalysis.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_Util_encrypt, mcuxClCipher_CryptFunc_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) mcuxClRsa_Util_encrypt(
    mcuxClSession_Handle_t           pSession,
    mcuxClCipher_Context_t * const   pContext UNUSED_PARAM,
    mcuxClKey_Handle_t               key,
    mcuxClCipher_Mode_t              mode,
    mcuxCl_InputBuffer_t             pLabel,
    uint32_t                        labelLength,
    mcuxCl_InputBuffer_t             pIn,
    uint32_t                        inLength,
    mcuxCl_Buffer_t                  pOut,
    uint32_t * const                pOutLength,
    uint32_t                        steps UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_Util_encrypt);

  /*****************************************************/
  /* Verification of the key                           */
  /*****************************************************/

  /* Check key type */
  if((MCUXCLRSA_KEYTYPE_INTERNAL_PUBLIC) != mcuxClKey_getAlgoId(key))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT);
  }

  /* Check key size */ //TODO: It should be clarified whether the check is needed
  uint32_t keyBitLength = mcuxClKey_getSize(key);
  const uint32_t keyByteLength = keyBitLength / 8u;
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_KeyData_Plain_t * pRsaKeyData = (mcuxClRsa_KeyData_Plain_t *) mcuxClKey_getKeyData(key);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
  if(keyByteLength != pRsaKeyData->modulus.keyEntryLength)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT);
  }

  /*****************************************************/
  /* Perform padding operation                         */
  /*****************************************************/

  /* Get the algorithm descriptor */
  mcuxClRsa_Cipher_AlgorithmDescriptor_t * pAlgorithmDescriptor = (mcuxClRsa_Cipher_AlgorithmDescriptor_t *) mode->pAlgorithm;

  /* Allocate paddedMessage buffer in CPU WA */
  const uint32_t paddedMessageSizeWord = MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(keyByteLength);
  uint32_t cpuWaUsedWord = paddedMessageSizeWord;
  uint8_t * pPaddedMessage = (uint8_t *) mcuxClSession_allocateWords_cpuWa(pSession, paddedMessageSizeWord);
  if(NULL == pPaddedMessage)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION);
  }

    mcuxClRsa_PadVerModeEngine_t pPaddingFunction = pAlgorithmDescriptor->pCryptMode;
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t paddingFunctionId = pAlgorithmDescriptor->crypt_FunId);

  /* Call the padding function */
  MCUXCLBUFFER_INIT(pPaddedMessageBuf, NULL, pPaddedMessage, keyByteLength);
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_PaddingOperation, pPaddingFunction(
                              /* mcuxClSession_Handle_t       pSession,           */ pSession,
                              /* mcuxCl_InputBuffer_t         pInput,             */ pIn,
                              /* const uint32_t              inputLength,        */ inLength,
                              /* mcuxCl_Buffer_t              pVerificationInput, */ NULL, /* unused */
                              /* mcuxClHash_Algo_t            pHashAlgo,          */ pAlgorithmDescriptor->pHashAlgo,
                              /* mcuxCl_InputBuffer_t         pLabel,             */ pLabel,
                              /* const uint32_t              saltlabelLength,    */ labelLength,
                              /* const uint32_t              keyBitLength,       */ keyBitLength,
                              /* const uint32_t              options,            */ 0u, /* unused */
                              /* mcuxCl_Buffer_t              pOutput             */ pPaddedMessageBuf,
                              /* uint32_t * const            pOutLength          */ NULL /* unused */
  ));
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_PaddingOperation)
  {
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT,
                              paddingFunctionId);
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK != retVal_PaddingOperation)
  {
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_ERROR);
  }
  else
  {
    /* Left empty intentionally */
  }

  /*****************************************************/
  /* Initialization of PKC                             */
  /*****************************************************/
  cpuWaUsedWord += sizeof(mcuxClPkc_State_t) / sizeof(uint32_t);
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *) mcuxClSession_allocateWords_cpuWa(pSession, (sizeof(mcuxClPkc_State_t)) / (sizeof(uint32_t)));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
  if(NULL == pkcStateBackup)
  {
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION,
                              paddingFunctionId);
  }

  MCUXCLPKC_FP_REQUEST_INITIALIZE(pSession, pkcStateBackup, mcuxClRsa_Util_encrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  /*****************************************************/
  /* Perform RSA public operation                     */
  /*****************************************************/

  /* Allocate output buffer in PKC WA */
  const uint32_t outSizeWord = MCUXCLRSA_INTERNAL_PUBLIC_OUTPUT_SIZE(keyByteLength) / (sizeof(uint32_t));
  uint8_t * pOutPublic = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, outSizeWord);
  if(NULL == pOutPublic)
  {
    mcuxClSession_freeWords_pkcWa(pSession, outSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_encrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              paddingFunctionId,
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }

  /* Set up RSA public key type */
  const mcuxClRsa_Key rsaPublicKey = {
    .keytype = MCUXCLRSA_KEY_PUBLIC,
     .pMod1 = (mcuxClRsa_KeyEntry_t *)&(pRsaKeyData->modulus),
     .pMod2 = NULL,
     .pQInv = NULL,
     .pExp1 = (mcuxClRsa_KeyEntry_t *)&(pRsaKeyData->exponent),
     .pExp2 = NULL,
     .pExp3 = NULL };

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPublic, mcuxClRsa_public(pSession, &rsaPublicKey, pPaddedMessageBuf, pOutPublic));

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPublic)
  {
    mcuxClSession_freeWords_pkcWa(pSession, outSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_encrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    //TODO: It should be clarified whether the PKC workarea and CPU workarea (it contains i.a. output form padding function) needs to be cleaned.

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_INVALID_INPUT,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              paddingFunctionId,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK != retVal_RsaPublic)
  {
    mcuxClSession_freeWords_pkcWa(pSession, outSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
            mcuxClRsa_Util_encrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_ERROR);
  }
  else
  {
    /* Left empty intentionally */
  }

  /*****************************************************/
  /* Export the encrypted data.                        */
  /*****************************************************/

  /* Export the output, which is located in PKC workarea in little endian. */
  MCUX_CSSL_FP_FUNCTION_CALL(writeStatus, mcuxClBuffer_write_reverse(pOut, 0u, pOutPublic, keyByteLength));

  /* Clean up */
  mcuxClSession_freeWords_pkcWa(pSession, outSizeWord);
  MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup,
          mcuxClRsa_Util_encrypt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  mcuxClSession_freeWords_cpuWa(pSession, cpuWaUsedWord);
  if(MCUXCLBUFFER_STATUS_OK != writeStatus)
  {

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, writeStatus,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              paddingFunctionId,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_reverse));
  }

  /* Set the number of bytes of encrypted data that have been written to the pOut */
  *pOutLength = keyByteLength;

  /*****************************************************/
  /* Exit                                              */
  /*****************************************************/



  //TODO: It should be clarified whether the PKC workarea and CPU workarea (it contains i.a. output form padding function) needs to be cleaned.

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_Util_encrypt, MCUXCLCIPHER_STATUS_OK,
    MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
    paddingFunctionId,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClBuffer_write_reverse),
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
}
