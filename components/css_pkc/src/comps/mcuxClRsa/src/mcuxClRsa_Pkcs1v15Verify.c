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

/** @file  mcuxClRsa_Pkcs1v15Verify.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PKCS1-v1_5-VERIFY
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslMemory_Compare.h>

#include <mcuxClHash.h>
#include <mcuxClRsa.h>

#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_224 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Verify),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA224,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Verify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_256 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Verify),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA256,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Verify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_384 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Verify),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA384,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Verify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_PKCS1v15_Sha2_512 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Verify),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA512,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Verify
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pkcs1v15Verify)
mcuxClRsa_Status_Protected_t mcuxClRsa_pkcs1v15Verify(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pkcs1v15Verify);

  const uint32_t emLen = (keyBitLength + 7u) / 8u;
  const uint32_t wordSizePkcWa = (emLen + sizeof(uint32_t) - 1u) / sizeof(uint32_t);

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);

  pSession->pkcWa.used += wordSizePkcWa;

  MCUX_CSSL_FP_FUNCTION_CALL(encode_result, mcuxClRsa_pkcs1v15Encode(pSession,
                                                                   pInput,
                                                                   inputLength,
                                                                   NULL,
                                                                   pHashAlgo,
                                                                   pLabel,
                                                                   saltlabelLength,
                                                                   keyBitLength,
                                                                   options,
                                                                   pPkcWorkarea));

  pSession->pkcWa.used -= wordSizePkcWa;

  if(MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK != encode_result)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Verify, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(compare_result, mcuxCsslMemory_Compare(
    mcuxCsslParamIntegrity_Protect(3u, pPkcWorkarea, pVerificationInput, emLen),
      pPkcWorkarea,
      pVerificationInput,
      emLen
    ));

  if(MCUXCSSLMEMORY_COMPARE_EQUAL != compare_result)
  {
    if(MCUXCSSLMEMORY_COMPARE_NOT_EQUAL == compare_result)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Verify, MCUXCLRSA_STATUS_VERIFY_FAILED,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare));
    }
    else
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Verify, MCUXCLRSA_STATUS_ERROR);
    }
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Verify, MCUXCLRSA_STATUS_VERIFY_OK,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare));

}
