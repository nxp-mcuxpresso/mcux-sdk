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

/** @file  mcuxClRsa_PssEncode.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PSS-ENCODE
 */

#include <stdint.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMemory.h>
#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <mcuxClRandom.h>

#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClMemory_Copy_Internal.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>


/**********************************************************/
/* Specification of PSS-sign mode structures            */
/**********************************************************/
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_224 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha224,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_256 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha256,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_384 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha384,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Sign_Pss_Sha2_512 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssEncode),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha512,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssEncode
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pssEncode, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_pssEncode(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  mcuxCl_Buffer_t              pVerificationInput UNUSED_PARAM,
  mcuxClHash_Algo_t            pHashAlgo,
  const uint8_t *             pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  mcuxCl_Buffer_t              pOutput,
  uint32_t * const            pOutLength UNUSED_PARAM)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pssEncode);

  /* Length of the encoded message. */
  const uint32_t emLen = keyBitLength / 8U; /* only byte-level granularity of keys is supported, thus keyBitLength is a multiple of 8 */
  /* Length of padding with 8 zero bytes. */
  const uint32_t padding1Length = MCUXCLRSA_PSS_PADDING1_LEN;
  /* Length of the output of hash function. */
  const uint32_t hLen = pHashAlgo->hashSize;
  /* Length of the EMSA-PSS salt. */
  const uint32_t sLen = saltlabelLength;
  /* Length of M' */
  const uint32_t mprimLen = padding1Length + hLen + sLen;
  /* Length of DB (and maskedDB). */
  const uint32_t dbLen = emLen - hLen - 1u;
  /* Length of PS padding */
  const uint32_t padding2Length = emLen - hLen - sLen - 2u;
  /* Length of PS padding plus one 0x01 byte */
  const uint32_t padding3Length = padding2Length + 1u;

  /*
   * Set buffers in the PKC workarea
   * M' = | M'= (padding | mHash | salt) |
   */
  const uint32_t wordSizePkcWa = MCUXCLRSA_INTERNAL_PSSENCODE_MAX_WAPKC_SIZE_WO_MGF1(emLen) / sizeof(uint32_t);
  mcuxCl_Buffer_t pMprim = (mcuxCl_Buffer_t) mcuxClSession_allocateWords_pkcWa(pSession, wordSizePkcWa);
  if (NULL == pMprim)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }
  /* Pointer to the buffer for the mHash in the M'*/
  mcuxCl_Buffer_t pMHash = pMprim + padding1Length;
  /* Pointer to the buffer for the salt in the M'*/
  mcuxCl_Buffer_t pSalt = pMHash + hLen;

  /* Pointer to the encoded message */
  mcuxCl_Buffer_t pEm = pOutput;
  /* Pointer to the hash */
  mcuxCl_Buffer_t pH = pEm + dbLen;

  /* Note: Step 1 from EMSA-PSS-VERIFY in PKCS #1 v2.2 can be avoided because messageLength
   * of function mcuxClRsa_sign is of type uint32_t and thus limited to 32 bits.
   */

  /* Step 3: If emLen < hLen + sLen + 2, output "encoding error" and stop. */
  /*
   * Here: If BYTE_LENGTH(keyBitLength) < (pHashAlgo->hashSize + saltlabelLength + 2)
   *  return MCUXCLRSA_STATUS_INVALID_INPUT else continue operation.
   *
   * Note: The check in Step 3 is moved before Step 2, since all lengths are already known.
   * Thus, no unnecessary hashing is performed in case of invalid input.
   *
   * Note: Additional checks on salt-length for FIPS 186-4 compliance are also done here.
   */

  if((emLen < (hLen + sLen + 2u)) || (hLen < sLen) || ((1024u == keyBitLength) && (512u == (8u * hLen)) && ((hLen - 2u) < sLen)))
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /* Step 2: Let mHash = Hash(M), an octet string of length hLen. */

  if(MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    /* Call hash function on pInput (Hash(pInput)) and store result in buffer mHash */
    uint32_t hashOutputSize = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(hash_result1, mcuxClHash_compute(pSession,
                                                              pHashAlgo,
                                                              pInput,
                                                              inputLength,
                                                              pMHash,
                                                              &hashOutputSize
    ));

    if(MCUXCLHASH_STATUS_OK != hash_result1)
    {
      mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
    }
  }
  else if (MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK))
  {
    /* Copy pInput to buffer mHash */
    MCUXCLMEMORY_FP_MEMORY_COPY(pMHash, pInput, hLen);
  }
  else
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 4: Generate a random octet string salt of length sLen; if sLen = 0, then salt is the empty string. */
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate, mcuxClRandom_ncGenerate(pSession, pSalt, sLen));
  if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate)
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 5: Let M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt; */
  /* M' is an octet string of length 8 + hLen + sLen with eight initial zero octets. */

  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_clear(pMprim, padding1Length, padding1Length));

  /* Step 6: Let H = Hash(M'), an octet string of length hLen. */
  uint32_t hashOutputSize = 0u;

  MCUX_CSSL_FP_FUNCTION_CALL(hash_result_2, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pMprim,
                                                             mprimLen,
                                                             pH,
                                                             &hashOutputSize
                                                             ));


  if(MCUXCLHASH_STATUS_OK != hash_result_2)
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 9: Let dbMask = MGF(H, emLen - hLen - 1). */
  /* Note: Step 9 has been moved up. Compute the MGF first and store the resulting mask directly in the
   * output buffer, where it is adjusted afterwards. This saves temporary buffer space and copy operations.
   */
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1, mcuxClRsa_mgf1(pSession, pHashAlgo, pH, hLen, dbLen, pEm));

  if(MCUXCLRSA_STATUS_INTERNAL_MGF_OK != retVal_mcuxClRsa_mgf1)
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 7: Generate an octet string PS consisting of emLen - sLen - hLen - 2 zero octets. */
  /* The length of PS may be 0. */
  /* Step 8: Let DB = PS || 0x01 || salt; DB is an octet string of length emLen - hLen - 1. */
  /* Step 10:  Let maskedDB = DB \xor dbMask. */

  /* PS consists of zeros only, so the first len(PS) bytes in the output buffer can be left as
   * they are because XOR with zero does not change the values.
   * The other items in DB, 0x01 and the salt, will be XORed directly onto the output buffer.
   */

  /* XOR 0x01 to the output buffer at the corresponding position. */
  *(pEm + padding2Length) ^= 0x01u;

  /* XOR the salt to the output buffer at the corresponding positions. */
  MCUX_CSSL_FP_LOOP_DECL(loop1);
  for(uint32_t i = 0u; i < sLen; ++i)
  {
    *(pEm + padding3Length + i) ^= *(pSalt + i);
     MCUX_CSSL_FP_LOOP_ITERATION(loop1);
  }

  /* Step 11:  Set the leftmost 8emLen - emBits bits of the leftmost octet in maskedDB to zero. */
  /* Since we assume the key length to be a multiple of 8, this becomes simply the leftmost bit. */

  *(pEm) &= 0x7fu;

  /* Step 12:  Let EM = maskedDB || H || 0xbc. */

  *(pEm + emLen - 1U) = 0xbcu;

  /* Step 13:  Output EM. */
  /* Switch endianess of EM buffer in-place to little-endian byte order. */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("the pEm PKC buffer is CPU word aligned.")
  MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t *) pEm, emLen);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/
  mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

/* Use temporary defines to avoid preprocessor directives inside the function exit macro below,
   as this would violate the MISRA rule 20.6 otherwise. */
  #define TMP_FEATURE_ELS_RNG \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssEncode, MCUXCLRSA_STATUS_INTERNAL_ENCODE_OK,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    TMP_FEATURE_ELS_RNG,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, sLen),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness));

#undef TMP_FEATURE_ELS_RNG
}
