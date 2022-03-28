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

/** @file  mcuxClRsa_Sign.c
 *  @brief mcuxClRsa: implementation of RSA Sign function
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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_sign)
mcuxClRsa_Status_Protected_t mcuxClRsa_sign(
  mcuxClSession_Handle_t           pSession,
  const mcuxClRsa_Key * const      pKey,
  const uint8_t * const           pMessageOrDigest,
  const uint32_t                  messageLength,
  const mcuxClRsa_SignVerifyMode   pPaddingMode,
  const uint32_t                  saltLength,
  const uint32_t                  options,
  uint8_t * const                 pSignature)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_sign);

  uint8_t * pPaddedMessage = (uint8_t *)&pSession->pkcWa.buffer[pSession->pkcWa.used];

  mcuxClPkc_State_t * pkcStateBackup = (mcuxClPkc_State_t *)&pSession->cpuWa.buffer[pSession->cpuWa.used];
  pSession->cpuWa.used += (sizeof(mcuxClPkc_State_t) / (sizeof(uint32_t)));
  MCUXCLPKC_FP_INITIALIZE(pkcStateBackup);

  uint32_t keyBitLength = 0u;

  if(MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype)
  {
    keyBitLength = 8u * (pKey->pMod1->keyEntryLength);
  }
  else if((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype))
  {
    MCUXCLRSA_CALC_MODLEN_FROM_CRTKEY(pKey, keyBitLength);
  }
  else
  {
      MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
  }

  pSession->pkcWa.used += MCUXCLPKC_ROUNDUP_SIZE((keyBitLength / 8u) / (sizeof(uint32_t)));

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_PaddingOperation, pPaddingMode->pPaddingFunction(
                               pSession,
                               pMessageOrDigest,
                               messageLength,
                               NULL,
                               pPaddingMode->pHashAlgo1,
                               NULL,
                               saltLength,
                               keyBitLength,
                               options,
                               pPaddedMessage
  ));

  pSession->pkcWa.used -= MCUXCLPKC_ROUNDUP_SIZE((keyBitLength / 8u) / (sizeof(uint32_t)));

  if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_PaddingOperation)
  {
      MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                              pPaddingMode->EncodeVerify_FunId,
                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
  }
  else if(MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK != retVal_PaddingOperation)
  {
      MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
  }
  else
  {
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
    else
    {
          MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
    }

      if(MCUXCLRSA_STATUS_INVALID_INPUT == retVal_RsaPrivate)
    {
          MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_INVALID_INPUT,
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                                pPaddingMode->EncodeVerify_FunId,
                                MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
                                MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype)),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
    }
    else if(MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK != retVal_RsaPrivate)
    {
          MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_ERROR);
    }
    else
    {

          MCUXCLPKC_FP_DEINITIALIZE(pkcStateBackup);

          pSession->cpuWa.used -= (sizeof(mcuxClPkc_State_t) / (sizeof(uint32_t)));

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_sign, MCUXCLRSA_STATUS_SIGN_OK,
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
                      pPaddingMode->EncodeVerify_FunId,
                      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_KEY_PRIVATEPLAIN == pKey->keytype),
                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privatePlain)),
                      MCUX_CSSL_FP_CONDITIONAL(((MCUXCLRSA_KEY_PRIVATECRT == pKey->keytype) || (MCUXCLRSA_KEY_PRIVATECRT_DFA == pKey->keytype)),
                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_privateCRT)),
                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize));
    }
  }
}
