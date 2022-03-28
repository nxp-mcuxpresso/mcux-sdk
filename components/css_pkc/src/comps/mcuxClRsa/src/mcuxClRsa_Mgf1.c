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

/** @file  mcuxClRsa_Mgf1.c
 *  @brief mcuxClRsa: function, which is called to execute the mask generation function MGF1 of PKCS #1 v2.2.
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClMemory.h>
#include <mcuxClHash.h>
#include <mcuxClSession.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_mgf1)
mcuxClRsa_Status_Protected_t mcuxClRsa_mgf1(
  mcuxClSession_Handle_t     pSession,
  const mcuxClHash_Algo_t *  pHashAlgo,
  const uint8_t *           pInput,
  const uint32_t            inputLength,
  const uint32_t            outputLength,
  uint8_t *                 pOutput)
{

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_mgf1);

  const uint32_t hLen = pHashAlgo->hashSize;

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
  const uint32_t wordSizePkcWa = (MCUXCLRSA_MGF1_WAPKC_SIZE(hLen, hLen) / (sizeof(uint32_t)));
  pSession->pkcWa.used += wordSizePkcWa;

  uint8_t * pHashOutput = pPkcWorkarea;

  uint8_t * pHashInput = pHashOutput + hLen;

  MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result_1, mcuxClMemory_copy(pHashInput, pInput, inputLength, inputLength));
  (void)memcopy_result_1;

  const uint32_t mxCounter = ((outputLength + hLen - 1U) / hLen);

  uint32_t tLen = 0U;

  for(uint32_t counter = 0U; counter < mxCounter; counter++)
  {
    pHashInput[inputLength]     = (uint8_t) (counter >> 24);
    pHashInput[inputLength + 1U] = (uint8_t) (counter >> 16);
    pHashInput[inputLength + 2U] = (uint8_t) (counter >> 8);
    pHashInput[inputLength + 3U] = (uint8_t) (counter);

    MCUX_CSSL_FP_FUNCTION_CALL(hash_result, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pHashInput,
                                                             inputLength + 4U,
                                                             pHashOutput,
                                                             NULL));

    if(MCUXCLHASH_STATUS_OK != hash_result)
    {
      pSession->pkcWa.used -= wordSizePkcWa;
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_mgf1, MCUXCLRSA_STATUS_ERROR);
    }

    uint32_t concatenateLen = (tLen + hLen > outputLength) ? (outputLength - tLen) : hLen;
    MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result, mcuxClMemory_copy((uint8_t *) pOutput + tLen, pHashOutput, concatenateLen, concatenateLen));
    (void)memcopy_result;

    tLen += concatenateLen;
  }

  pSession->pkcWa.used -= wordSizePkcWa;

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_mgf1, MCUXCLRSA_INTERNAL_STATUS_MGF_OK,
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute) * mxCounter,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) * mxCounter);

}
