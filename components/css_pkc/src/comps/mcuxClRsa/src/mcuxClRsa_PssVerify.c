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

/** @file  mcuxClRsa_PssVerify.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PSS-VERIFY
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClMemory.h>

#include <mcuxClHash.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory_Compare.h>

#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_224 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA224,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_256 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA256,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_384 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA384,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_512 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA512,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pssVerify)
mcuxClRsa_Status_Protected_t mcuxClRsa_pssVerify(
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

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pssVerify);

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);

  const uint32_t emLen = keyBitLength / 8U;
  const uint32_t padding1Length = MCUXCLRSA_PSS_PADDING1_LEN;
  const uint32_t hLen = pHashAlgo->hashSize;
  const uint32_t sLen = saltlabelLength;
  const uint32_t dbLen = emLen - hLen - 1U;

  uint8_t * const pEm = pVerificationInput;
  uint8_t * const pMprim = pPkcWorkarea;
  uint8_t * const pMHash = pMprim + padding1Length;
  uint8_t * const pSalt = pMHash + hLen;
  uint8_t * const pDbMask = pSalt + sLen;
  uint8_t * const pHprim = pDbMask + dbLen;

  const uint32_t mprimLen = padding1Length + hLen + sLen;
  const uint32_t wordSizePkcWa = MCUXCLRSA_PSSVERIFY_WAPKC_SIZE_WO_MGF1(emLen, sLen, hLen) / sizeof(uint32_t);
  pSession->pkcWa.used += wordSizePkcWa;

  if(MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
      MCUX_CSSL_FP_FUNCTION_CALL(hash_result1, mcuxClHash_compute(pSession,
                                                              pHashAlgo,
                                                              pInput,
                                                              inputLength,
                                                              pMHash,
                                                              NULL));

    if(MCUXCLHASH_STATUS_OK != hash_result1)
    {
      pSession->pkcWa.used -= wordSizePkcWa;
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
    }
  }
  else if (MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
      MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result_1, mcuxClMemory_copy(pMHash, pInput, hLen, hLen));
    (void)memcopy_result_1;
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  if((((1024U == keyBitLength) && (512U == (8U * hLen)) && ((hLen - 2U) < sLen)) || (hLen < sLen))
          || (emLen < (hLen + sLen + 2U)) || (0xbcU != *pEm))
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
  }

  MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pEm, emLen);
  uint8_t * const maskedDB = pEm;
  uint8_t * const pH = pEm + dbLen;

  if(0U != ((*maskedDB) & 0x80u))
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness));
  }

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1, mcuxClRsa_mgf1(pSession, pHashAlgo, pH, hLen, dbLen, pDbMask));

  if(MCUXCLRSA_INTERNAL_STATUS_MGF_OK != retVal_mcuxClRsa_mgf1)
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  uint8_t * const pDB = pDbMask;

  MCUX_CSSL_FP_LOOP_DECL(loop1);
  for(uint32_t i = 0u; i < dbLen; ++i)
  {
    *(pDB + i) = *(maskedDB + i) ^ *(pDbMask + i);
     MCUX_CSSL_FP_LOOP_ITERATION(loop1);
  }

  pDB[0] &= 0x7Fu;

  uint32_t counterZeros = 0u;
  const uint32_t padding2Length = emLen - hLen - sLen - 2u;

  MCUX_CSSL_FP_LOOP_DECL(loop2);
  for(uint32_t i = 0u; i < padding2Length; ++i)
  {
    if(0u == pDB[i])
    {
        ++counterZeros;
    }
    MCUX_CSSL_FP_LOOP_ITERATION(loop2);
  }
  if((counterZeros != padding2Length) || (0x01u != pDB[padding2Length]))
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
        MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, dbLen),
        MCUX_CSSL_FP_LOOP_ITERATIONS(loop2, padding2Length));
  }

  MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result_3, mcuxClMemory_copy(pSalt, pDB + dbLen - sLen, sLen, sLen));
  (void)memcopy_result_3;

  MCUX_CSSL_FP_FUNCTION_CALL(memclr_result, mcuxClMemory_clear(pMprim, padding1Length, padding1Length));
  (void)memclr_result;

  MCUX_CSSL_FP_FUNCTION_CALL(hash_result_2, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pMprim,
                                                             mprimLen,
                                                             pHprim,
                                                             NULL));

  if(MCUXCLHASH_STATUS_OK != hash_result_2)
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(compare_result, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, pH, pHprim, hLen),
                                                                  pH,
                                                                  pHprim,
                                                                  hLen));

  mcuxClRsa_Status_t pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_FAILED;
  if(MCUX_CSSL_FP_RESULT(compare_result) == MCUXCSSLMEMORY_COMPARE_EQUAL)
  {
    pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_OK;
  }

  pSession->pkcWa.used -= wordSizePkcWa;

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, pssVerifyStatus,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, dbLen),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop2, padding2Length),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare));

}
