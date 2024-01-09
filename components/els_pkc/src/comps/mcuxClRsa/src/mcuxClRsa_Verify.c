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

/** @file  mcuxClRsa_Verify.c
 *  @brief mcuxClRsa: implementation of RSA Verify function
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClRsa.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_verify(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  mcuxCl_InputBuffer_t             pMessageOrDigest,
  const uint32_t                  messageLength,
  mcuxCl_Buffer_t                  pSignature,
  const mcuxClRsa_SignVerifyMode   pVerifyMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  mcuxCl_Buffer_t                  pOutput
  )
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_verify);

  /*****************************************************/
  /* Initialization                                    */
  /*****************************************************/

  /* Locate paddedMessage buffer at beginning of PKC WA and update session info */
  const uint32_t modulusByteLength = pKey->pMod1->keyEntryLength;
  const uint32_t pkcWaSizeWord = MCUXCLRSA_PKC_ROUNDUP_SIZE(modulusByteLength) / (sizeof(uint32_t));

  uint8_t * pPaddedMessage = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
  if (NULL == pPaddedMessage)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  /* Initialize PKC */
  const uint32_t cpuWaSizeWord = (sizeof(mcuxClPkc_State_t)) / (sizeof(uint32_t));
  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
  if (NULL == pkcStateBackup)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  MCUXCLPKC_FP_REQUEST_INITIALIZE(pSession, pkcStateBackup, mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);

  /*****************************************************/
  /* Perform RSA_public                                */
  /*****************************************************/

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPublic, mcuxClRsa_public(pSession, pKey, pSignature, pPaddedMessage));

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPublic)
  {
    /* De-initialize PKC */
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
                              MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }
  else if(MCUXCLRSA_STATUS_INTERNAL_KEYOP_OK != retVal_RsaPublic)
  {

    /* De-initialize PKC */
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_ERROR);
  }
  else
  {

    /*****************************************************/
    /* Perform padding operation                         */
    /*****************************************************/

    const uint32_t keyBitLength = 8u * modulusByteLength;


    MCUX_CSSL_FP_FUNCTION_CALL(retVal_PaddingOperation, pVerifyMode->pPaddingFunction(pSession,
                                                                                     pMessageOrDigest,
                                                                                     messageLength,
                                                                                     pPaddedMessage,
                                                                                     pVerifyMode->pHashAlgo1,
                                                                                     NULL,
                                                                                     saltLength,
                                                                                     keyBitLength,
                                                                                     options,
                                                                                     pOutput,
                                                                                     NULL));

    /*****************************************************/
    /* Exit                                              */
    /*****************************************************/

    /* De-initialize PKC */
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pkcStateBackup, mcuxClRsa_verify, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_verify, retVal_PaddingOperation,
                    MCUXCLRSA_STATUS_FAULT_ATTACK,
                    MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
                    pVerifyMode->EncodeVerify_FunId,
                    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
  }
}
