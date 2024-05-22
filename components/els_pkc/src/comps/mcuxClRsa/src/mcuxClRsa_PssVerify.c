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

/** @file  mcuxClRsa_PssVerify.c
 *  @brief mcuxClRsa: function, which is called to execute EMSA-PSS-VERIFY
 */

#include <stdint.h>
#include <mcuxClToolchain.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClMemory.h>

#include <mcuxClHash.h>
#include <mcuxClHashModes.h>
#include <internal/mcuxClHash_Internal.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslMemory.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClMemory_Copy_Internal.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>


/**********************************************************/
/* Specification of PSS-verify mode structures            */
/**********************************************************/
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_224 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha224,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_256 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha256,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_384 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha384,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};
const mcuxClRsa_SignVerifyMode_t mcuxClRsa_Mode_Verify_Pss_Sha2_512 =
{
  .EncodeVerify_FunId = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_pssVerify),
  .pHashAlgo1 = &mcuxClHash_AlgorithmDescriptor_Sha512,
  .pHashAlgo2 = NULL,
  .pPaddingFunction = mcuxClRsa_pssVerify
};

/* Define to avoid preprocessor directives inside the function exit macro,
   as this would violate the MISRA rule 20.6 otherwise. */
#define FP_RSA_PSSVERIFY_SWITCHENDIANNESS \
  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness)

/* Macros to switch endianness */
#define MCUXCLRSA_INTERNAL_SWITCHENDIANNESS(ptr, length)  MCUXCLPKC_FP_SWITCHENDIANNESS(ptr, length)


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_pssVerify, mcuxClRsa_PadVerModeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_pssVerify(
  mcuxClSession_Handle_t       pSession,
  mcuxCl_InputBuffer_t         pInput,
  const uint32_t              inputLength,
  mcuxCl_Buffer_t              pVerificationInput,
  mcuxClHash_Algo_t            pHashAlgo,
  const uint8_t *             pLabel UNUSED_PARAM,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  mcuxCl_Buffer_t              pOutput UNUSED_PARAM,
  uint32_t * const            pOutLength UNUSED_PARAM)
{

  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_pssVerify);

  /* Setup session. */

  /* Length of the encoded message. */
  const uint32_t emLen = keyBitLength / 8U; /* only byte-level granularity of keys is supported, thus keyBitLength is a multiple of 8 */
  /* Length of padding with 8 zero bytes. */
  const uint32_t padding1Length = MCUXCLRSA_PSS_PADDING1_LEN;
  /* Length of the output of hash function. */
  const uint32_t hLen = pHashAlgo->hashSize;
  /* Length of the EMSA-PSS salt. */
  const uint32_t sLen = saltlabelLength;
  /* Length of DB (and maskedDB). */
  const uint32_t dbLen = emLen - hLen - 1U;

  const uint16_t wordSizePkcWa = (uint16_t)(MCUXCLRSA_INTERNAL_PSSVERIFY_MAX_WAPKC_SIZE_WO_MGF1(emLen) / sizeof(uint32_t));
  uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, wordSizePkcWa);
  if (NULL == pPkcWorkarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  /*
   * Set buffers in PKC workarea
   * PKC = | M'= (padding | mHash | salt) || dbMask (and DB) || H' |
   */
  /* Pointer to the encoded message */
  mcuxCl_Buffer_t pEm = pVerificationInput;
  /* Pointer to the buffer for the M' = | padding_1 | mHash | salt | */
  mcuxCl_Buffer_t pMprim = pPkcWorkarea;
  /* Pointer to the buffer for the mHash in the M'*/
  mcuxCl_Buffer_t pMHash = pMprim + padding1Length;
  /* Pointer to the buffer for the salt in the M'*/
  mcuxCl_Buffer_t pSalt = pMHash + hLen;

  /* Pointer to the buffer for the dbMask'*/
  mcuxCl_Buffer_t pDbMask = pSalt + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sLen);
  /* Pointer to the buffer for the H' */
  mcuxCl_Buffer_t pHprim = pDbMask + dbLen;

  const uint32_t mprimLen = padding1Length + hLen + sLen;

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
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
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
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 3: If BYTE_LENGTH(keyBitLength) < (pHashAlgo->hashSize + saltlabelLength + 2)
  *  return MCUXCLRSA_STATUS_VERIFY_FAILED else continue operation. */
  /* Additional checks on salt-length for FIPS 186-4 compliance */
  /* The constraint on sLen for FIPS186.5 is always met, so no additional check is needed. In step 10, we check that the zero-padding has the expected length w.r.t. sLen. */
  /* Step 4: Check if the leftmost octet of Em (before endianess switch) has hexadecimal value 0xbc.*/
  if((((1024U == keyBitLength) && (512U == (8U * hLen)) && ((hLen - 2U) < sLen)) || (hLen < sLen))
          || (emLen < (hLen + sLen + 2U)) || (0xbcU != *pEm))
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)));
  }

  /* Switch endianess of EM buffer to big-endian byte order in place */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("the pEm PKC buffer is CPU word aligned.")
  MCUXCLRSA_INTERNAL_SWITCHENDIANNESS((uint32_t *) pEm, emLen);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  /* Step 5: Let maskedDB be the leftmost emLen-hLen-1 octets of EM and let H be the next hLen octets. */
  mcuxCl_Buffer_t maskedDB = pEm;
  mcuxCl_Buffer_t pH = pEm + dbLen;

  /* Step 6: Check if 8*emLen-emBits leftmost bits equal to zero. Note that, as keyBitLength is a multiple of 8, 8 * emLen - emBits = 1 bit.*/
  if(0U != ((*maskedDB) & 0x80u))
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
          FP_RSA_PSSVERIFY_SWITCHENDIANNESS);
  }

  /* Step 7: dbMask = MGF(H, BYTE_LENGTH(keyBitLength) - pHashAlgo->hashSize - 1) */

  MCUX_CSSL_FP_FUNCTION_CALL(retVal_mcuxClRsa_mgf1, mcuxClRsa_mgf1(pSession, pHashAlgo, pH, hLen, dbLen, pDbMask));

  if(MCUXCLRSA_STATUS_INTERNAL_MGF_OK != retVal_mcuxClRsa_mgf1)
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 8: DB = pOutput(0 : BYTE_LENGTH(keyBitLength) - pHashAlgo->hashSize - 1) XOR dbMask.*/
  mcuxCl_Buffer_t pDB = pDbMask; // reuse the space of DbMask

  MCUX_CSSL_FP_LOOP_DECL(loop1);
  for(uint32_t i = 0u; i < dbLen; ++i)
  {
    *(pDB + i) = *(maskedDB + i) ^ *(pDbMask + i);
     MCUX_CSSL_FP_LOOP_ITERATION(loop1);
  }

  /* Step 9: Set the leftmost 8emLen - emBits bits of the leftmost octet in DB to zero. */
  pDB[0] &= 0x7Fu;

  /* Step 10 */
  /* Check (DB(0 : BYTE_LENGTH(keyBitLength) - pHashAlgo->hashSize - saltlabelLength - 2) == [0x00, ..., 0x00])
   * and that (DB(BYTE_LENGTH(keyBitLength) - pHashAlgo->hashSize - saltlabelLength - 1) == 0x01) ? */
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
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_VERIFY_FAILED,
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
      MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
          FP_RSA_PSSVERIFY_SWITCHENDIANNESS,
          MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
          MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, dbLen),
          MCUX_CSSL_FP_LOOP_ITERATIONS(loop2, padding2Length));
  }

  /* Step 11: Copy salt to mPrime buffer */
  MCUXCLMEMORY_FP_MEMORY_COPY(pSalt, pDB + dbLen - sLen, sLen);

  /* Step 12 */
  /* mPrime = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 || mHash || DB(BYTE_LENGTH(keyBitLength) - saltlabelLength: BYTE_LENGTH(keyBitLength))] */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_clear(pMprim, padding1Length, padding1Length));

  /* Step 13: HPrime = Hash(mPrime) */
  uint32_t hashOutputSize = 0u;
  MCUX_CSSL_FP_FUNCTION_CALL(hash_result_2, mcuxClHash_compute(pSession,
                                                             pHashAlgo,
                                                             pMprim,
                                                             mprimLen,
                                                             pHprim,
                                                             &hashOutputSize
    ));

  if(MCUXCLHASH_STATUS_OK != hash_result_2)
  {
    mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, MCUXCLRSA_STATUS_ERROR);
  }

  /* Step 14 verify5 = (HPrime == H) ? true : false. */
#ifndef MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS
  MCUX_CSSL_FP_FUNCTION_CALL(compare_result, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, pH, pHprim, hLen),
                                                                  pH,
                                                                  pHprim,
                                                                  hLen));

  mcuxClRsa_Status_t pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_FAILED;
  if(compare_result == MCUXCSSLMEMORY_STATUS_EQUAL)
  {
    pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_OK;
  }
#else
  /* Becasue pH and pHprim are unaligned and taking into account the properties:
   * - dbLen = emLen - hLen - 1U
   * - emLen % CpuWord = 0
   * - hLen % CpuWord = 0
   * - pEm % CpuWord = 0
   * - pDbMask % CpuWord = 0
   * - pH % CpuWord = CpuWord-unalignedBytes
   * - pHprim  % CpuWord = CpuWord-unalignedBytes
   * - unalignedBytes = (CpuWord - dbLen) & (CpuWord - 1) <- it is unaligned part of pH and pHprim
   * , the first unalignedBytes bytes will be compared separately (byte-wise) then the rest will be compared with aligned address.
   */
  uint32_t unalignedBytes = ((sizeof(uint32_t)) - dbLen) & ((sizeof(uint32_t)) - 1u);
  MCUX_CSSL_FP_FUNCTION_CALL(compare_result1, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, pH, pHprim, unalignedBytes),
                                                                  pH,
                                                                  pHprim,
                                                                  unalignedBytes));

  mcuxClRsa_Status_t pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_FAILED;
  if(compare_result1 == MCUXCSSLMEMORY_STATUS_EQUAL)
  {
    pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_OK;
  }

  MCUX_CSSL_FP_FUNCTION_CALL(compare_result2, mcuxCsslMemory_Compare(mcuxCsslParamIntegrity_Protect(3u, pH + unalignedBytes,
                                                                  pHprim + unalignedBytes, hLen - unalignedBytes),
                                                                  pH + unalignedBytes,
                                                                  pHprim + unalignedBytes,
                                                                  hLen - unalignedBytes));

  if(compare_result2 == MCUXCSSLMEMORY_STATUS_EQUAL)
  {
    pssVerifyStatus = MCUXCLRSA_STATUS_VERIFY_OK;
  }
#endif

  /************************************************************************************************/
  /* Function exit                                                                                */
  /************************************************************************************************/
  mcuxClSession_freeWords_pkcWa(pSession, wordSizePkcWa);

/* Use temporary defines to avoid preprocessor directives inside the function exit macro below,
   as this would violate the MISRA rule 20.6 otherwise. */
#if defined(MCUXCL_FEATURE_PKC_PKCRAM_NO_UNALIGNED_ACCESS)
  #define FP_RSA_PSSVERIFY_COMPARISON \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
#else
  #define FP_RSA_PSSVERIFY_COMPARISON \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare), \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear)
#endif

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_pssVerify, pssVerifyStatus,
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_PLAIN == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute)),
    MCUX_CSSL_FP_CONDITIONAL((MCUXCLRSA_OPTION_MESSAGE_DIGEST == (options & MCUXCLRSA_OPTION_MESSAGE_MASK)),
      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)),
    FP_RSA_PSSVERIFY_SWITCHENDIANNESS,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_mgf1),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop1, dbLen),
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop2, padding2Length),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_compute),
    FP_RSA_PSSVERIFY_COMPARISON
  );

#undef FP_RSA_PSSVERIFY_COMPARISON

}
