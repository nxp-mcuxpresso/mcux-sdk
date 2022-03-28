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

/** @file  mcuxClRsa_Pkcs1v15Encode.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PKCS1-v1_5-ENCODE
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClMemory.h>

#include <mcuxClHash.h>
#include <mcuxClCss_Hash.h>

#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Macros.h>

static const uint8_t mcuxClRsa_oidSha2_224[] = {0x30, 0x2d, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
                                       0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x04, 0x05,
                                       0x00, 0x04, 0x1c};

static const uint8_t mcuxClRsa_oidSha2_256[] = {0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
                                       0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
                                       0x00, 0x04, 0x20};

static const uint8_t mcuxClRsa_oidSha2_384[] = {0x30, 0x41, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
                                       0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02, 0x05,
                                       0x00, 0x04, 0x30};

static const uint8_t mcuxClRsa_oidSha2_512[] = {0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
                                       0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05,
                                       0x00, 0x04, 0x40};

struct mcuxClRsa_oid_t {
  size_t length;
  const uint8_t * value;
};

static const struct mcuxClRsa_oid_t mcuxClRsa_oidTable[] = {
  { sizeof(mcuxClRsa_oidSha2_224), mcuxClRsa_oidSha2_224 },
  { sizeof(mcuxClRsa_oidSha2_256), mcuxClRsa_oidSha2_256 },
  { sizeof(mcuxClRsa_oidSha2_384), mcuxClRsa_oidSha2_384 },
  { sizeof(mcuxClRsa_oidSha2_512), mcuxClRsa_oidSha2_512 }
};

#define DIGESTSIZE_TO_INDEX(len) (((len) - 16u) / 16u)

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_224 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA224,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_256 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA256,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_384 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA384,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_512 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode),
    .pHashAlgo1         = (const mcuxClHash_Algo_t *)&mcuxClHash_AlgoSHA512,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pkcs1v15Encode)
mcuxClRsa_Status_Protected_t mcuxClRsa_pkcs1v15Encode(
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
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pkcs1v15Encode);

  const uint32_t emLen = (keyBitLength + 7u) / 8u;
  const uint32_t hLength = pHashAlgo->hashSize;

  uint8_t const * phashAlgorithmIdentifier     = mcuxClRsa_oidTable[DIGESTSIZE_TO_INDEX(hLength)].value;
  const uint32_t hashAlgorithmIdentifierLength = mcuxClRsa_oidTable[DIGESTSIZE_TO_INDEX(hLength)].length;

  const uint32_t paddingLength = emLen - hashAlgorithmIdentifierLength - hLength - 3u;

  if(emLen < (hashAlgorithmIdentifierLength + hLength + 11u))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);

  uint8_t * const pEm = pPkcWorkarea;
  uint8_t * const pPs = pEm + 2u;
  uint8_t * const pT = pPs + paddingLength + 1u;
  uint8_t * const pH = pT + hashAlgorithmIdentifierLength;

  *(pEm)     = (uint8_t) 0x00;
  *(pEm + 1u) = (uint8_t) 0x01;

  MCUX_CSSL_FP_FUNCTION_CALL(memset_result, mcuxClMemory_set(pPs, 0xFFU, paddingLength, emLen - 2u));
  if(0u != memset_result)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode, MCUXCLRSA_STATUS_ERROR);
  }

  *(pPs + paddingLength) = (uint8_t) 0x00;

  MCUX_CSSL_FP_FUNCTION_CALL(memcopy_result, mcuxClMemory_copy(pT,
                                                             phashAlgorithmIdentifier,
                                                             hashAlgorithmIdentifierLength,
                                                             hashAlgorithmIdentifierLength));
  (void)memcopy_result;

  if(MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    const uint32_t wordSizePkcWa = (emLen + sizeof(uint32_t) - 1u) / sizeof(uint32_t);
    pSession->pkcWa.used += wordSizePkcWa;

    MCUX_CSSL_FP_FUNCTION_CALL(hash_result, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pInput,
                                                             inputLength,
                                                             pH,
                                                             (uint8_t *)NULL));

    pSession->pkcWa.used -= wordSizePkcWa;

    if(MCUXCLHASH_STATUS_OK != hash_result)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode, MCUXCLRSA_STATUS_ERROR);
    }
  }
  else if (MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    MCUX_CSSL_FP_FUNCTION_CALL(memcopy_digest_result, mcuxClMemory_copy(pH, pInput, hLength, hLength));
    (void) memcopy_digest_result;
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode, MCUXCLRSA_STATUS_ERROR);
  }

  MCUX_CSSL_FP_FUNCTION_CALL(memcopy_output_result, mcuxClMemory_copy(pOutput, pPkcWorkarea, emLen, emLen));
  (void) memcopy_output_result;

  MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pOutput, emLen);

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode, MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness));
}
