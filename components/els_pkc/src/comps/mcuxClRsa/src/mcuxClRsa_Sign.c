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

/** @file  mcuxClRsa_Sign.c
 *  @brief mcuxClRsa: implementation of RSA Sign function
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClHash.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClKey_Internal.h>
#include <mcuxCsslAnalysis.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_sign)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_sign(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  mcuxCl_InputBuffer_t             pMessageOrDigest,
  const uint32_t                  messageLength,
  const mcuxClRsa_SignVerifyMode   pPaddingMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  mcuxCl_Buffer_t                  pSignature
  )
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_sign);

  /*****************************************************/
  /* Initialization                                    */
  /*****************************************************/

  /* Initialize PKC */
  uint32_t cpuWaUsedBackup = mcuxClSession_getUsage_cpuWa(pSession);
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *) mcuxClSession_allocateWords_cpuWa(pSession, (sizeof(mcuxClPkc_State_t)) / (sizeof(uint32_t)));
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
  if (NULL == pkcStateBackup)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  MCUXCLPKC_FP_REQUEST_INITIALIZE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

  /*****************************************************/
  /* Perform padding operation                         */
  /*****************************************************/
  uint32_t pkcWaTotalSize = 0u;

  uint32_t keyBitLength = 0u;

  if(MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype)
  {
    keyBitLength = 8u * (pKey->pMod1->keyEntryLength);
    pkcWaTotalSize = MCUXCLRSA_SIGN_PLAIN_WAPKC_SIZE(keyBitLength);
  }
  else if((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype))
  {
    MCUXCLRSA_CALC_MODLEN_FROM_CRTKEY(pKey, keyBitLength);
    pkcWaTotalSize = MCUXCLRSA_SIGN_CRT_WAPKC_SIZE(keyBitLength);
  }
  else
  {
    /* De-initialize PKC */
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);
    mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }

  /* Locate paddedMessage buffer at beginning of PKC WA and update session info */
  uint32_t keyByteLength = keyBitLength / 8u;
  uint32_t pkcWaUsedByte = (MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype) ? MCUXCLRSA_INTERNAL_PRIVATEPLAIN_INPUT_SIZE(keyByteLength) : MCUXCLRSA_PKC_ROUNDUP_SIZE(keyByteLength);
  uint32_t pkcWaUsedBackup = mcuxClSession_getUsage_pkcWa(pSession);
  uint8_t * const pPkcWorakarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaUsedByte / (sizeof(uint32_t)));
  if (NULL == pPkcWorakarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }
  uint8_t * pPaddedMessage = pPkcWorakarea;

  /* Call the padding function */
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_PaddingOperation, pPaddingMode->pPaddingFunction(
                              /* mcuxClSession_Handle_t       pSession,           */ pSession,
                              /* mcuxCl_InputBuffer_t         pInput,             */ pMessageOrDigest,
                              /* const uint32_t              inputLength,        */ messageLength,
                              /* mcuxCl_Buffer_t              pVerificationInput, */ NULL,
                              /* mcuxClHash_Algo_t            pHashAlgo,          */ pPaddingMode->pHashAlgo1,
                              /* const uint8_t *             pLabel,             */ NULL,
                              /* const uint32_t              saltlabelLength,    */ saltLength,
                              /* const uint32_t              keyBitLength,       */ keyBitLength,
                              /* const uint32_t              options,            */ options,
                              /* mcuxCl_Buffer_t              pOutput             */ pPaddedMessage,
                              /* uint32_t * const            pOutLength          */ NULL
  ));

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_PaddingOperation)
  {
    /* De-initialize PKC */
    mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

    /* Clear pkcWa */
    MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              pPaddingMode->EncodeVerify_FunId,
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK != retVal_PaddingOperation)
  {
    /* De-initialize PKC */
    mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

    /* Clear pkcWa */
    MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
  }
  else
  {
    if (pkcWaUsedByte > keyByteLength)
    {
      /* Clear PKC workarea after the input */
      MCUXCLMEMORY_FP_MEMORY_CLEAR(pPaddedMessage + keyByteLength, pkcWaUsedByte - keyByteLength);
    }

    /*****************************************************/
    /* Perform RSA private operation                     */
    /*****************************************************/
    uint32_t retVal_RsaPrivate = MCUXCLRSA_STATUS_ERROR;

    if(MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype)
    {
      MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPrivatePlain, mcuxClRsa_privatePlain(pSession, pKey, pPaddedMessage, pSignature));
      retVal_RsaPrivate = retVal_RsaPrivatePlain;
    }
    else if((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype))
    {
      MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPrivateCrt, mcuxClRsa_privateCRT(pSession, pKey, pPaddedMessage, pSignature));
      retVal_RsaPrivate = retVal_RsaPrivateCrt;
    }
    else /* Key type has already been tested: any other type here is a fault */
    {
      /* De-initialize PKC */
      mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

      /* Clear pkcWa */
      MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
    }

    /* Check return value */
    if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPrivate)
    {
      /* De-initialize PKC */
      mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

      /* Clear pkcWa */
      MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                                MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                                pPaddingMode->EncodeVerify_FunId,
                                MCUX_CSSL_FP_CONDITIONAL((pkcWaUsedByte > keyByteLength),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)),
                                MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
                                MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype)),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
                                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
    }
    else if(MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK != retVal_RsaPrivate)
    {
      /* De-initialize PKC */
      mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

      /* Clear pkcWa */
      MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
    }
    else
    {
      /*****************************************************/
      /* Exit                                              */
      /*****************************************************/

      /* De-initialize PKC */
      mcuxClSession_setUsage_pkcWa(pSession, pkcWaUsedBackup);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, cpuWaUsedBackup);

      /* Clear pkcWa */
      MCUXCLMEMORY_FP_MEMORY_CLEAR(pPkcWorakarea,pkcWaTotalSize);

      MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_sign, MCUXCLRSA_STATUS_SIGN_OK,
                      MCUXCLRSA_STATUS_FAULT_ATTACK,
                      MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                      pPaddingMode->EncodeVerify_FunId,
                      MCUX_CSSL_FP_CONDITIONAL((pkcWaUsedByte > keyByteLength),
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)),
                      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype),
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
                      MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype)),
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
                      MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE,
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
    }
  }
}
