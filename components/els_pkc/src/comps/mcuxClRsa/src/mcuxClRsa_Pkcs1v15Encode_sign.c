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

/** @file  mcuxClRsa_Pkcs1v15Encode_sign.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PKCS1-v1_5-ENCODE
 */

#include <stdint.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMemory.h>

#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClMemory_Copy_Internal.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Macros.h>


/**********************************************************/
/* Hash algorithm identifiers as DigestInfo types         */
/**********************************************************/
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
  ///< Formula for calculating the OID table index from the digest size

/**********************************************************/
/* Specifications of PKCS#1 v1.5 mode structures          */
/**********************************************************/
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_224 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode_sign),
    .pHashAlgo1         = &mcuxClHash_AlgorithmDescriptor_Sha224,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode_sign
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_256 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode_sign),
    .pHashAlgo1         = &mcuxClHash_AlgorithmDescriptor_Sha256,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode_sign
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_384 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode_sign),
    .pHashAlgo1         = &mcuxClHash_AlgorithmDescriptor_Sha384,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode_sign
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_PKCS1v15_Sha2_512 = {
    .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pkcs1v15Encode_sign),
    .pHashAlgo1         = &mcuxClHash_AlgorithmDescriptor_Sha512,
    .pHashAlgo2         = NULL,
    .pPaddingFunction   = mcuxClRsa_pkcs1v15Encode_sign
};


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pkcs1v15Encode_sign, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_pkcs1v15Encode_sign(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  mcuxCl_Buffer_t              pVerificationInput UNUSED_PARAM,
  mcuxClHash_Algo_t            pHashAlgo,
  const uint8_t *             pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength UNUSED_PARAM,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pkcs1v15Encode_sign);
  /*****************************************************/
  /* Initialization                                    */
  /*****************************************************/

  /* Length of the encoded message. */
  const uint32_t emLen = (keyBitLength + 7u) / 8u; /* byte length, rounded up */
  /* Length of the output of hash function. */
  const uint32_t hLength = pHashAlgo->hashSize;

  /* Length of the T-padding containing the hash algorithm identifier. */
  uint8_t const * phashAlgorithmIdentifier     = mcuxClRsa_oidTable[DIGESTSIZE_TO_INDEX(hLength)].value;
  /* Length of the T-padding DigestInfo containing the hash algorithm identifier. */
  const uint32_t hashAlgorithmIdentifierLength = mcuxClRsa_oidTable[DIGESTSIZE_TO_INDEX(hLength)].length;

  /* Number of required padding bytes */
  const uint32_t paddingLength = emLen - hashAlgorithmIdentifierLength - hLength - 3u;

  /*****************************************************/
  /* If emLen < tLen + 11, return 'invalid input'.     */
  /*****************************************************/
  if(emLen < (hashAlgorithmIdentifierLength + hLength + 11u))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_sign, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /*****************************************************/
  /* Prepare the padding                               */
  /*****************************************************/
  /* Setup session. */
  const uint32_t wordSizePkcWa = (emLen + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t));
  uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, wordSizePkcWa);
  if (NULL == pPkcWorkarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_sign, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  /*
   * Set buffers in PKC workarea
   * PKC = | 0x00 || 0x01 || PS || 0x00 | T || H |
   */
  /* General pointer to encoded message at the beginning of the buffer */
  mcuxCl_Buffer_t pEm = pPkcWorkarea;
  /* Pointer to the buffer for the padding bytes PS */
  mcuxCl_Buffer_t pPs = pEm + 2u;
  /* Pointer to the buffer for the algorithm identifier T */
  mcuxCl_Buffer_t pT = pPs + paddingLength + 1u;

  /* Pointer to the buffer for the hash H */
  mcuxCl_Buffer_t pH = pT + hashAlgorithmIdentifierLength;


  /* Write 0x00 0x01 prefix */
  *(pEm)     = (uint8_t) 0x00;
  *(pEm + 1u) = (uint8_t) 0x01;

  /* Write padding bytes */
  MCUXCLMEMORY_FP_MEMORY_SET_WITH_BUFF(pPs, 0xFFU, paddingLength, emLen - 2u);

  /* Write 0x00 divider */
  *(pPs + paddingLength) = (uint8_t) 0x00;

  /* Write DigestInfo T */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_copy(pT,
                                             phashAlgorithmIdentifier,
                                             hashAlgorithmIdentifierLength,
                                             hashAlgorithmIdentifierLength));

  /*****************************************************/
  /* Perform hash operation or just copy the digest    */
  /*****************************************************/
  if(MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    /* Call hash function on pInput and store the result in the buffer at pH */
    uint32_t hashOutputSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(hash_result, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pInput,
                                                             inputLength,
                                                             pH,
                                                             &hashOutputSize

    ));
    if(MCUXCLHASH_STATUS_OK != hash_result)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_sign, MCUXCLRSA_STATUS_ERROR);
    }
  }
  else if (MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    /* Copy pInput to buffer at pH (located at the end of the buffer) */
    MCUXCLMEMORY_FP_MEMORY_COPY(pH, pInput, hLength);
  }
  else
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_sign, MCUXCLRSA_STATUS_ERROR);
  }

  /*****************************************************/
  /* Prepare the encoded message for output            */
  /*****************************************************/

  /* Copy encoded message to beginning of PKC workarea and switch the endianness */
  MCUXCLMEMORY_FP_MEMORY_COPY(pOutput, pPkcWorkarea, emLen);

  mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("the pOutput PKC buffer is CPU word aligned.")
  MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pOutput, emLen);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/
  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pkcs1v15Encode_sign, MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness));
}
