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

/** @file  mcuxClRsa_PssEncode.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PSS-ENCODE
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClMemory.h>
#include <mcuxClHash.h>

#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_224 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA224,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_256 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA256,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_384 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA384,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_512 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA512,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pssEncode)
mcuxClRsa_Status_Protected_t mcuxClRsa_pssEncode(
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
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pssEncode);

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);

  const uint32_t emLen = keyBitLength / 8U;
  const uint32_t padding1Length = MCUXCLRSA_PSS_PADDING1_LEN;
  const uint32_t hLen = pHashAlgo->hashSize;
  const uint32_t sLen = saltlabelLength;
  const uint32_t mprimLen = padding1Length + hLen + sLen;
  const uint32_t dbLen = emLen - hLen - 1u;
  const uint32_t padding2Length = emLen - hLen - sLen - 2u;
  const uint32_t padding3Length = padding2Length + 1u;

  uint8_t * const pMprim = pPkcWorkarea;
  uint8_t * const pMHash = pMprim + padding1Length;
  uint8_t * const pSalt = pMHash + hLen;

  uint8_t * const pEm = pOutput;
  uint8_t * const pH = pEm + dbLen;

  const uint32_t wordSizePkcWa = MCUXCLRSA_PSSENCODE_WAPKC_SIZE_WO_MGF1(sLen, hLen) / sizeof(uint32_t);
  pSession->pkcWa.used += wordSizePkcWa;

  if((emLen < (hLen + sLen + 2u)) || (hLen < sLen) || ((1024u == keyBitLength) && (512u == (8u * hLen)) && ((hLen - 2u) < sLen)))
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

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
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
    }
  }
  else if (MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
      MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result_1, mcuxClMemory_copy(pMHash, pInput, hLen, hLen));
    (void)memcopy_result_1;
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(pSalt, sLen));
  if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
  {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(ret_MemoryClear, mcuxClMemory_clear(pMprim, padding1Length, padding1Length));
  (void) ret_MemoryClear;

  MCUX_CSSL_FP_FUNCTION_CALL(hash_result_2, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pMprim,
                                                             mprimLen,
                                                             pH,
                                                             NULL));

  if(MCUXCLHASH_STATUS_OK != hash_result_2)
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1, mcuxClRsa_mgf1(pSession, pHashAlgo, pH, hLen, dbLen, pEm));

  if(MCUXCLRSA_INTERNAL_STATUS_MGF_OK != retVal_mcuxClRsa_mgf1)
  {
    pSession->pkcWa.used -= wordSizePkcWa;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  *(pEm + padding2Length) ^= 0x01u;

  MCUX_CSSL_FP_LOOP_DECL(loop1);
  for(uint32_t i = 0u; i < sLen; ++i)
  {
    *(pEm + padding3Length + i) ^= *(pSalt + i);
     MCUX_CSSL_FP_LOOP_ITERATION(loop1);
  }

  *(pEm) &= 0x7fu;

  *(pEm + emLen - 1U) = 0xbcu;

  MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pEm, emLen);
  pSession->pkcWa.used -= wordSizePkcWa;

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, sLen),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness));
}
