/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

#include <mcuxClHash.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_verify)
mcuxClRsa_Status_Protected_t mcuxClRsa_verify(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  const uint8_t * const           pMessageOrDigest,
  const uint32_t                  messageLength,
  uint8_t * const                 pSignature,
  const mcuxClRsa_SignVerifyMode   pVerifyMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  uint8_t * const                 pOutput)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_verify);

  const uint32_t modulusByteLength = pKey->pMod1->keyEntryLength;
  uint8_t * pPaddedMessage = (uint8_t *)&pSession->pkcWa.buffer[pSession->pkcWa.used];
  pSession->pkcWa.used += (MCUXCLPKC_ROUNDUP_SIZE(modulusByteLength) / (sizeof(uint32_t)));

  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *)&pSession->cpuWa.buffer[pSession->cpuWa.used];
  pSession->cpuWa.used += (sizeof(mcuxClPkc_State_t) / (sizeof(uint32_t)));
  MCUXCLPKC_FP_INITIALIZE(pkcStateBackup);

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_RsaPublic, mcuxClRsa_public(pSession, pKey, pSignature, pPaddedMessage));

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPublic)
  {

	MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
							  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
  }
  else if(MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK != retVal_RsaPublic)
  {

	MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, MCUXCLRSA_STATUS_ERROR);
  }
  else
  {

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
                                                                                     pOutput));

      MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

      pSession->pkcWa.used -= (MCUXCLPKC_ROUNDUP_SIZE(modulusByteLength) / (sizeof(uint32_t)));
    pSession->cpuWa.used -= (sizeof(mcuxClPkc_State_t) / (sizeof(uint32_t)));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_verify, retVal_PaddingOperation,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_public),
                    pVerifyMode->EncodeVerify_FunId,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
  }
}
