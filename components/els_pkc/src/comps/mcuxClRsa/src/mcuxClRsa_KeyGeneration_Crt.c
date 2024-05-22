/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClRsa_KeyGeneration_Crt.c
 *  @brief mcuxClRsa: implementation of RSA key generation function
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>
#include <mcuxClMath.h>
#include <mcuxClPkc.h>
#include <mcuxClRandom.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_KeyGeneration_Crt_FUP.h>


#ifdef MCUXCL_FEATURE_RSA_STRENGTH_CHECK
#define MCUXCLRSA_KEYGEN_CRT_FP_SECSTRENGTH  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength)
#else
#define MCUXCLRSA_KEYGEN_CRT_FP_SECSTRENGTH  (0u)
#endif

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_KeyGeneration_Crt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_KeyGeneration_Crt(
  mcuxClSession_Handle_t pSession,
  mcuxClKey_Type_t type,
  mcuxClKey_Protection_t protection,
  mcuxClKey_Handle_t privKey,
  uint8_t * pPrivData,
  uint32_t * const pPrivDataLength,
  mcuxClKey_Handle_t pubKey,
  uint8_t * pPubData,
  uint32_t * const pPubDataLength)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_KeyGeneration_Crt);

  const uint32_t backup_cpuWaUsed = mcuxClSession_getUsage_cpuWa(pSession);
  const uint32_t backup_pkcWaUsed = mcuxClSession_getUsage_pkcWa(pSession);

  /*
   * 1. Check the key type, i.e.:
   * - algorithm IDs
   * - key sizes (it should be 1024, 2048, 3072, 4096, 6144 or 8192).
   *
   * If did not pass verification, function returns MCUXCLRSA_STATUS_INVALID_INPUT error.
   *
   */
  const uint32_t bitLenKey = type->size;
  if(((MCUXCLKEY_ALGO_ID_RSA | MCUXCLKEY_ALGO_ID_KEY_PAIR) != type->algoId)
       || ((MCUXCLKEY_SIZE_2048 != bitLenKey)
            && (MCUXCLKEY_SIZE_3072 != bitLenKey)
            && (MCUXCLKEY_SIZE_4096 != bitLenKey)
            ))
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_INVALID_INPUT);
  }

  /*
   * 2. Check entropy provided by RNG
   *    If the RNG does not provide an appropriate level of entropy (security strength)
   *    for the given key size, this function returns MCUXCLRSA_STATUS_RNG_ERROR error.
   */
#ifdef MCUXCL_FEATURE_RSA_STRENGTH_CHECK
  uint32_t securityStrength = MCUXCLRSA_GET_MINIMUM_SECURITY_STRENGTH(bitLenKey);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_checkSecurityStrength, mcuxClRandom_checkSecurityStrength(pSession, securityStrength));
  if(MCUXCLRANDOM_STATUS_OK != ret_checkSecurityStrength)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_RNG_ERROR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength));
  }
#endif

  /*
   * 3. Check if E is FIPS compliant, i.e., is odd values in the range 2^16 < e < 2^256,
   *    determine the length without leading zeros.
   *    If did not pass verification, function returns MCUXCLRSA_STATUS_INVALID_INPUT error.
   */
  mcuxClRsa_KeyEntry_t * pPublicExponent = (mcuxClRsa_KeyEntry_t *) type->info;
  uint32_t byteLenE;
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_VerifyE, mcuxClRsa_VerifyE(pPublicExponent, &byteLenE));
  if(MCUXCLRSA_STATUS_KEYGENERATION_OK != retVal_VerifyE)
  {
#if defined(MCUXCL_FEATURE_RSA_STRENGTH_CHECK)
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_INVALID_INPUT,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE));
#else
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_INVALID_INPUT,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE));
#endif
  }

  /* 4. Initialize PKC. */
  const uint32_t cpuWaSizeWord = MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(sizeof(mcuxClPkc_State_t)) / (sizeof(uint32_t));
  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  /* Session buffer is 32 bit aligned */
  mcuxClPkc_State_t * pPkcStateBackup = (mcuxClPkc_State_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
  if (NULL == pPkcStateBackup)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  MCUXCLPKC_FP_REQUEST_INITIALIZE(pSession, pPkcStateBackup, mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  /*
   * 5. Allocate buffers in PKC RAM
   *    - size aligned to FAME word
   *    - they are be stored in little-endian byte order
   */
  const uint32_t byteLenKey = bitLenKey / 8u;
  const uint32_t pkcByteLenKey = MCUXCLRSA_PKC_ROUNDUP_SIZE(byteLenKey);
  const uint32_t byteLenPrime = byteLenKey / 2u;
  const uint32_t pkcByteLenPrime = MCUXCLRSA_PKC_ROUNDUP_SIZE(byteLenPrime);

  const uint16_t bufferSizePQb = (uint16_t)pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE;

  /* Allocate space in session for p, q and e for now */
  const uint32_t pkcWaSizeWord = (pkcByteLenPrime + (pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE) * 2u) / (sizeof(uint32_t));
  uint8_t * pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
  if (NULL == pPkcWorkarea)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  uint8_t * pPkcBufferE = pPkcWorkarea;
  uint8_t * pPkcBufferP = pPkcBufferE + pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE /* offset for Ndash before p */;
  uint8_t * pPkcBufferQ = pPkcBufferP + pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE /* offset for Ndash before q */;
  /* dp, dq, qinv should be operand size add one PCK word */
  uint8_t * pPkcBufferDp = pPkcBufferQ + pkcByteLenPrime;
  uint8_t * pPkcBufferDq = pPkcBufferDp + bufferSizePQb;
  uint8_t * pPkcBufferQinv = pPkcBufferDq + bufferSizePQb;
  uint8_t * pPkcBufferT1 = pPkcBufferQinv + bufferSizePQb;
  uint8_t * pPkcBufferT2 = pPkcBufferT1 + bufferSizePQb;
  uint8_t * pPkcBufferT3 = pPkcBufferT2 + MCUXCLRSA_PKC_WORDSIZE + bufferSizePQb; /* offset for Ndash before modulus */

  /* Setup UPTR table. */
  const uint32_t uptrtSizeWord = MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(MCUXCLRSA_INTERNAL_KEYGENERATION_CRT_UPTRT_SIZE * (sizeof(uint16_t))) / (sizeof(uint32_t));
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
  uint16_t * pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, uptrtSizeWord);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
  if (NULL == pOperands)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  MCUXCLPKC_SETUPTRT(pOperands);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P] = MCUXCLPKC_PTR2OFFSET(pPkcBufferP);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_Q] = MCUXCLPKC_PTR2OFFSET(pPkcBufferQ);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DP] = MCUXCLPKC_PTR2OFFSET(pPkcBufferDp);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DQ] = MCUXCLPKC_PTR2OFFSET(pPkcBufferDq);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_E] = MCUXCLPKC_PTR2OFFSET(pPkcBufferE);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_QINV] = MCUXCLPKC_PTR2OFFSET(pPkcBufferQinv);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1] = MCUXCLPKC_PTR2OFFSET(pPkcBufferT1);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T2] = MCUXCLPKC_PTR2OFFSET(pPkcBufferT2);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3] = MCUXCLPKC_PTR2OFFSET(pPkcBufferT3);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_CONSTANT0] = 0u;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_CONSTANT1] = 1u;

  /*
   * 6. Copy E to PKC RAM.
   *    It is stored in little-endian byte order (copied with reverse order and without leading zeros).
   *
   *  Used functions: mcuxClPkc_ImportBigEndianToPkc
   */
  MCUXCLPKC_PS1_SETLENGTH(pkcByteLenPrime, pkcByteLenPrime);
  uint32_t leadingZerosE = pPublicExponent->keyEntryLength - byteLenE;
  MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_E, pPublicExponent->pKeyEntryData + leadingZerosE, byteLenE);

  mcuxClRsa_KeyEntry_t e;
  e.keyEntryLength = byteLenE;
  e.pKeyEntryData = pPkcBufferE;

  /*
   * 7. Generate prime p.
   *    Continuation if mcuxClRsa_GenerateProbablePrime returns MCUXCLRSA_STATUS_KEYGENERATION_OK,
   *    otherwise function ends with MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED or error.
   *
   * Used functions: mcuxClRsa_GenerateProbablePrime
   */
  mcuxClRsa_KeyEntry_t p;
  p.pKeyEntryData = pPkcBufferP;
  p.keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_GenerateProbablePrime_P, mcuxClRsa_GenerateProbablePrime(pSession, &e, &p, bitLenKey));
  if(MCUXCLRSA_STATUS_KEYGENERATION_OK != retVal_GenerateProbablePrime_P)
  {
    mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
            mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);


    if(MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED == retVal_GenerateProbablePrime_P)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt,
        MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED,
        MCUXCLRSA_KEYGEN_CRT_FP_SECSTRENGTH,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE),
        MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_GenerateProbablePrime),
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, retVal_GenerateProbablePrime_P);
    }
  }

  /*
   * 8. Generate prime q.
   *    Continuation if mcuxClRsa_GenerateProbablePrime returns MCUXCLRSA_STATUS_KEYGENERATION_OK,
   *    otherwise function ends with MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED or error.
   *
   * Used functions: mcuxClRsa_GenerateProbablePrime
   */
  mcuxClRsa_KeyEntry_t q;
  q.pKeyEntryData = pPkcBufferQ;
  q.keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(retVal_GenerateProbablePrime_Q, mcuxClRsa_GenerateProbablePrime(pSession, &e, &q, bitLenKey));

  if(MCUXCLRSA_STATUS_KEYGENERATION_OK != retVal_GenerateProbablePrime_Q)
  {
    mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
            mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

    if(MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED == retVal_GenerateProbablePrime_Q)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt,
        MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED,
        MCUXCLRSA_KEYGEN_CRT_FP_SECSTRENGTH,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE),
        MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_GenerateProbablePrime),
        MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, retVal_GenerateProbablePrime_Q);
    }
  }

  /*
   * 9. Check if |p - q| <= 2^(nlen/2 - 100)
   *    Continuation if mcuxClRsa_TestPQDistance function returns MCUXCLRSA_STATUS_KEYGENERATION_OK
   *    otherwise function ends with MCUXCLRSA_STATUS_ERROR error code.
   *
   * Used functions: mcuxClRsa_TestPQDistance
   *
   * NOTE: This is a deviation from the method specified in the FIPS 186-4, where this check is performed while generating the prime q
   *       (see step 5.4 in Appendix B.3.3).
   *       The @ref mcuxClRsa_GenerateProbablePrime function does not perform this check, it is done after generating p and q.
   *       For this reason, if p and q does not meet this FIPS requirements, no new prime q number will be generated. Instead
   *       of function ends with error.
   *       Rationale of this deviation:
   *       This check will fail if at least 100 most significant bits of p and q are identical. This can happen
   *       with very low probability and it's usually treated as a hardware failure.
   */
  MCUX_CSSL_FP_FUNCTION_CALL(
    retVal_TestPQDistance,
    mcuxClRsa_TestPQDistance(
      MCUXCLPKC_PACKARGS4(
        0,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_Q,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
      pkcByteLenPrime));
  if(MCUXCLRSA_STATUS_KEYGENERATION_OK != retVal_TestPQDistance)
  {
    mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
    MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
            mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

    mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }


  /*
   * 10. Compute dp := e^(-1) mod (p-1)
   *
   * Used functions: mcuxClRsa_ModInv
   */

  /* Update session about space for dp, dq, qInv, T1, T2, and T3 buffers */
  if (NULL == mcuxClSession_allocateWords_pkcWa(pSession,
                                               (6u * (pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE) + MCUXCLRSA_PKC_WORDSIZE) / (sizeof(uint32_t))) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  MCUXCLPKC_FP_CALCFUP(mcuxClRsa_KeyGeneration_Crt_Steps10_FUP,
          mcuxClRsa_KeyGeneration_Crt_Steps10_FUP_LEN);
  MCUXCLPKC_WAITFORREADY();
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(
    mcuxClRsa_ModInv(
      MCUXCLPKC_PACKARGS4(
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DP,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1)));

  /*
   * 11. Compute dq := e^(-1) mod (q-1)
   *
   * Used functions: mcuxClRsa_ModInv
   */
  MCUXCLPKC_FP_CALCFUP(mcuxClRsa_KeyGeneration_Crt_Steps11_FUP,
          mcuxClRsa_KeyGeneration_Crt_Steps11_FUP_LEN);
  MCUXCLPKC_WAITFORREADY();
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(
    mcuxClRsa_ModInv(
      MCUXCLPKC_PACKARGS4(
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DQ,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1)));

  /*
   * 12. Compute qInv := q^(-1) mod p
   *
   * Used functions: mcuxClMath_ModInv
   */
  MCUXCLPKC_FP_CALCFUP(mcuxClRsa_KeyGeneration_Crt_Steps12_FUP,
          mcuxClRsa_KeyGeneration_Crt_Steps12_FUP_LEN);
  MCUXCLPKC_WAITFORREADY();
  /* Calculate NDash of p */
  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3, MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1);
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(
    mcuxClMath_ModInv(
      MCUXCLPKC_PACKARGS4(
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_QINV,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T2,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T3,
        MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1)));

  /*
   * 13. Compute n := p*q
   *
   * Used functions: FAME Plain Multiplication
   */

  /* Free up space for T1, T2, and T3 buffers */
  mcuxClSession_freeWords_pkcWa(pSession, (3u * (pkcByteLenPrime + MCUXCLRSA_PKC_WORDSIZE) + MCUXCLRSA_PKC_WORDSIZE) / (sizeof(uint32_t)));
  /* Update session about space for N buffer */
  if (NULL == mcuxClSession_allocateWords_pkcWa(pSession,
                                               pkcByteLenKey / (sizeof(uint32_t))) )
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);
  }

  /* Set buffer and operand for N */
  uint8_t * pPkcBufferN = pPkcBufferQinv + bufferSizePQb;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_N] = MCUXCLPKC_PTR2OFFSET(pPkcBufferN);

  /* Compute n := p*q */
  MCUXCLPKC_FP_CALC_MC1_PM(
    MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_N,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_Q);
  MCUXCLPKC_WAITFORFINISH();

  /*
   * 14. Write public key (computed n, e) to the buffer pointed by pPubData.
   *     This buffer contains RSA key (mcuxClRsa_Key data type, i.e.: key type and key entries)
   *     followed by the key data, i.e.: n, e.
   *     Key entries stored in big-endian byte order (copy with reverse order).
   *
   * Used functions: mcuxClPkc_ExportBigEndianFromPkc (to export n and e).
   */

  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Key *pRsaPubKey = (mcuxClRsa_Key *) pPubData;
  pRsaPubKey->keytype = MCUXCLRSA_KEY_PUBLIC;
  *pPubDataLength = sizeof(mcuxClRsa_Key);

  pRsaPubKey->pMod1 = (mcuxClRsa_KeyEntry_t *) (pPubData + *pPubDataLength);
  *pPubDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPubKey->pMod2 = NULL;
  pRsaPubKey->pQInv = NULL;

  pRsaPubKey->pExp1 = (mcuxClRsa_KeyEntry_t *) (pPubData + *pPubDataLength);
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  *pPubDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPubKey->pExp2 = NULL;
  pRsaPubKey->pExp3 = NULL;

  pRsaPubKey->pMod1->pKeyEntryData = pPubData + *pPubDataLength;
  pRsaPubKey->pMod1->keyEntryLength = byteLenKey;

  MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(
    pRsaPubKey->pMod1->pKeyEntryData,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_N,
    pRsaPubKey->pMod1->keyEntryLength);
  *pPubDataLength += pRsaPubKey->pMod1->keyEntryLength;

  pRsaPubKey->pExp1->pKeyEntryData = pPubData + *pPubDataLength;
  pRsaPubKey->pExp1->keyEntryLength = e.keyEntryLength;
  MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(
    pRsaPubKey->pExp1->pKeyEntryData,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_E,
    pRsaPubKey->pExp1->keyEntryLength);
  *pPubDataLength += pRsaPubKey->pExp1->keyEntryLength;

  /*
   * 15. Write RSA CRT key (p, q, qInv, dp, dq) to the buffer pointed by pPrivData.
   *     This buffer contains RSA key (mcuxClRsa_Key data type, i.e.: key type and key entries)
   *     followed by the key data, i.e.: p, q, qInv, dp, dq.
   *     Key entries stored in big-endian byte order (copy with reverse order).
   *
   * Used functions: mcuxClPkc_SecureExportBigEndianFromPkc
   */

  MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
  mcuxClRsa_Key *pRsaPrivCrtKey = (mcuxClRsa_Key *) pPrivData;

  pRsaPrivCrtKey->keytype = MCUXCLRSA_KEY_PRIVATECRT;
  *pPrivDataLength = sizeof(mcuxClRsa_Key);


  pRsaPrivCrtKey->pMod1 = (mcuxClRsa_KeyEntry_t *) (pPrivData + *pPrivDataLength);
  *pPrivDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPrivCrtKey->pMod2 = (mcuxClRsa_KeyEntry_t *) (pPrivData + *pPrivDataLength);
  *pPrivDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPrivCrtKey->pQInv = (mcuxClRsa_KeyEntry_t *) (pPrivData + *pPrivDataLength);
  *pPrivDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPrivCrtKey->pExp1 = (mcuxClRsa_KeyEntry_t *) (pPrivData + *pPrivDataLength);
  *pPrivDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPrivCrtKey->pExp2 = (mcuxClRsa_KeyEntry_t *) (pPrivData + *pPrivDataLength);
  *pPrivDataLength += sizeof(mcuxClRsa_KeyEntry_t);
  pRsaPrivCrtKey->pExp3 = NULL;
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

  pRsaPrivCrtKey->pMod1->pKeyEntryData = pPrivData + *pPrivDataLength;
  pRsaPrivCrtKey->pMod1->keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportP,
      mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                            pRsaPrivCrtKey->pMod1->pKeyEntryData,
                                            MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P,
                                                               MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
                                            pRsaPrivCrtKey->pMod1->keyEntryLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExportP)
  {
      mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
              mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }
  *pPrivDataLength += pRsaPrivCrtKey->pMod1->keyEntryLength;

  pRsaPrivCrtKey->pMod2->pKeyEntryData = pPrivData + *pPrivDataLength;
  pRsaPrivCrtKey->pMod2->keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportQ,
      mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                            pRsaPrivCrtKey->pMod2->pKeyEntryData,
                                            MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_Q,
                                                               MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
                                            pRsaPrivCrtKey->pMod2->keyEntryLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExportQ)
  {
      mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
              mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }
  *pPrivDataLength += pRsaPrivCrtKey->pMod2->keyEntryLength;

  pRsaPrivCrtKey->pQInv->pKeyEntryData = pPrivData + *pPrivDataLength;;
  pRsaPrivCrtKey->pQInv->keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportQinv,
      mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                            pRsaPrivCrtKey->pQInv->pKeyEntryData,
                                            MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_QINV,
                                                               MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
                                            pRsaPrivCrtKey->pQInv->keyEntryLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExportQinv)
  {
      mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
              mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }
  *pPrivDataLength += pRsaPrivCrtKey->pQInv->keyEntryLength;

  pRsaPrivCrtKey->pExp1->pKeyEntryData = pPrivData + *pPrivDataLength;
  pRsaPrivCrtKey->pExp1->keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportDp,
      mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                            pRsaPrivCrtKey->pExp1->pKeyEntryData,
                                            MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DP,
                                                               MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
                                            pRsaPrivCrtKey->pExp1->keyEntryLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExportDp)
  {
      mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
              mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }
  *pPrivDataLength += pRsaPrivCrtKey->pExp1->keyEntryLength;

  pRsaPrivCrtKey->pExp2->pKeyEntryData = pPrivData + *pPrivDataLength;
  pRsaPrivCrtKey->pExp2->keyEntryLength = byteLenPrime;
  MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportDq,
      mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                            pRsaPrivCrtKey->pExp2->pKeyEntryData,
                                            MCUXCLPKC_PACKARGS2(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_DQ,
                                                               MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_T1),
                                            pRsaPrivCrtKey->pExp2->keyEntryLength));
  if (MCUXCLPKC_STATUS_OK != ret_SecExportDq)
  {
      mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
      MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
              mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

      mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }
  *pPrivDataLength += pRsaPrivCrtKey->pExp2->keyEntryLength;

  /*
   * 16. Initialization of key handles for public and private key
   *     a. copy key protection into handle
   *     b. initialize the key type in handle:
   *     -set type->algoId to RSA + public/private
   *     -set length of the key in type->size
   *     -set type->info to NULL
   *     c. set pSrcKeyData to point to the start of the provided buffer
   *     d. set dstKey.loadLocation to MCUXCLKEY_LOADSTATUS_NOTLOADED
   *     e. set other fields of dstKey to zero
   */
  mcuxClKey_Descriptor_t * pPubKey = (mcuxClKey_Descriptor_t *) pubKey;
  mcuxClKey_setProtectionType(pPubKey, protection);
  // TODO CLNS-5165: move the generation of these types into the key component - TBD with architects, is this still what we want to do?
  mcuxClKey_TypeDescriptor_t keyType_public = { MCUXCLKEY_ALGO_ID_RSA ^ MCUXCLKEY_ALGO_ID_PUBLIC_KEY, type->size, NULL };
  mcuxClKey_setTypeDescriptor(pPubKey, keyType_public);
  mcuxClKey_setKeyData(pPubKey, pPubData);
  mcuxClKey_setLoadStatus(pPubKey, MCUXCLKEY_LOADSTATUS_NOTLOADED);
  mcuxClKey_setLoadedKeyData(pPubKey, NULL);
  mcuxClKey_setLoadedKeySlot(pPubKey, 0u);

  mcuxClKey_Descriptor_t * pPrivKey = (mcuxClKey_Descriptor_t *) privKey;
  mcuxClKey_setProtectionType(pPrivKey, protection);
  // TODO CLNS-5165: move the generation of these types into the key component
  mcuxClKey_TypeDescriptor_t keyType_private = { MCUXCLKEY_ALGO_ID_RSA ^ MCUXCLKEY_ALGO_ID_PRIVATE_KEY, type->size, NULL };
  mcuxClKey_setTypeDescriptor(pPrivKey, keyType_private);
  mcuxClKey_setKeyData(pPrivKey, pPrivData);
  mcuxClKey_setLoadStatus(pPrivKey, MCUXCLKEY_LOADSTATUS_NOTLOADED);
  mcuxClKey_setLoadedKeyData(pPrivKey, NULL);
  mcuxClKey_setLoadedKeySlot(pPrivKey, 0u);

  /* Create link between private and public key handles */
  MCUX_CSSL_FP_FUNCTION_CALL(ret_linkKeyPair, mcuxClKey_linkKeyPair(pSession, privKey, pubKey));
  if (MCUXCLKEY_STATUS_OK != ret_linkKeyPair)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_ERROR);
  }

  /* Clear PKC workarea. */
  uint32_t pkcWaSize = MCUXCLRSA_KEYGENERATION_CRT_WAPKC_SIZE(bitLenKey);
  MCUXCLPKC_PS1_SETLENGTH(0u, pkcWaSize);
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
  MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_KEYGENERATION_CRT_P, 0u);

  mcuxClSession_setUsage_pkcWa(pSession, backup_pkcWaUsed);
  MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, pPkcStateBackup,
          mcuxClRsa_KeyGeneration_Crt, MCUXCLRSA_STATUS_FAULT_ATTACK);

  mcuxClSession_setUsage_cpuWa(pSession, backup_cpuWaUsed);

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClRsa_KeyGeneration_Crt,
    MCUXCLRSA_STATUS_KEYGENERATION_OK,
    MCUXCLRSA_STATUS_FAULT_ATTACK,
    MCUXCLRSA_KEYGEN_CRT_FP_SECSTRENGTH,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_VerifyE),
    MCUXCLPKC_FP_CALLED_REQUEST_INITIALIZE,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_GenerateProbablePrime),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_TestPQDistance),
    3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_ModInv),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
    MCUXCLPKC_FP_CALLED_CALC_MC1_PM,
    5u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureExportBigEndianFromPkc),
    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),
    MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_linkKeyPair),
    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
}
