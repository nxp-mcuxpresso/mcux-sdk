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

/** @file  mcuxClRsa_TestPrimeCandidate.c
 *  @brief mcuxClRsa: function, which is called to test a prime candidate
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMemory.h>

#include <mcuxClPkc.h>

#include <mcuxClRsa.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClRsa_TestPrimeCandidate_FUP.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_TestPrimeCandidate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_TestPrimeCandidate(
  mcuxClSession_Handle_t           pSession,
  mcuxClRsa_KeyEntry_t *           pE,
  mcuxClRsa_KeyEntry_t *           pPrimeCandidate,
  const uint32_t                  keyBitLength,
  const uint32_t                  iNumToCmp_iA0)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_TestPrimeCandidate,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CMP);

    mcuxClRsa_Status_t status = MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_CMP_FAILED;

    const uint32_t primeByteLength = keyBitLength/8u/2u;
    const uint32_t pkcOperandSize = MCUXCLRSA_PKC_ROUNDUP_SIZE(primeByteLength);

    /* Backup Ps1 length and UPTRT, resore them when returning */
    uint16_t *bakUPTRT = MCUXCLPKC_GETUPTRT();
    uint32_t bakPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint32_t bakPs2LenReg = MCUXCLPKC_PS2_GETLENGTH_REG();

    /* Get iNumToCmp and iA0 indices */
    const uint32_t uptrtIndexNumToCmp = (iNumToCmp_iA0 >> 8u) & 0xFFu;
    const uint32_t uptrtIndexA0 = iNumToCmp_iA0 & 0xFFu;

    /* Share the area with mcuxClRsa_MillerRabinTest*/
    const uint32_t pkcWaSizeWord = MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WAPKC_SIZE(primeByteLength) / (sizeof(uint32_t));
    uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
    if (NULL == pPkcWorkarea)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_TestPrimeCandidate, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    uint8_t *pGCD1 = pPkcWorkarea;
    uint8_t *pGCD2 = pGCD1 + pkcOperandSize;

    /* Setup UPTR table */
    const uint32_t cpuWaSizeWord = MCUXCLRSA_INTERNAL_TESTPRIMECANDIDATE_WACPU_SIZE_WO_MILLERRABIN / sizeof(uint32_t);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
    uint16_t * pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    if (NULL == pOperands)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_TestPrimeCandidate, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_E] = MCUXCLPKC_PTR2OFFSET(pE->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE] = MCUXCLPKC_PTR2OFFSET(pPrimeCandidate->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE_64MOST] = MCUXCLPKC_PTR2OFFSET(pPrimeCandidate->pKeyEntryData + pkcOperandSize - MCUXCLRSA_PKC_WORDSIZE);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_NUMTOCOMPARE] = bakUPTRT[uptrtIndexNumToCmp];
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_A0] = bakUPTRT[uptrtIndexA0];
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1] = MCUXCLPKC_PTR2OFFSET(pGCD1);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD2] = MCUXCLPKC_PTR2OFFSET(pGCD2);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT0] = 0u;
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT1] = 1u;
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CONSTANT2] = 2u;

    /* Set UPTRT table */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(pOperands);

	MCUXCLPKC_PS1_SETLENGTH(pkcOperandSize, pkcOperandSize);
	MCUXCLPKC_PS2_SETLENGTH(0u, MCUXCLRSA_PKC_WORDSIZE);

    do
    {
        /*
        * 1. Check if prime candidate < sqrt(2)(2^((nlen/2)-1))
        *    This check is done using only 64 most significant bits of sqrt(2)(2^(nlen/2)-1)
        *    rounded up, this is 0xb504f333f9de6485u.
        *    This deviation from FIPS 186-4 has been approved.
        *
        * Used functions: FAME operations (MCUXCLPKC_OP_CMP)
        */
        MCUXCLPKC_FP_CALC_OP2_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE_64MOST, MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_NUMTOCOMPARE);
        if (MCUXCLPKC_FLAG_CARRY == MCUXCLPKC_WAITFORFINISH_GETCARRY())
        {
            status = MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_CMP_FAILED;
            MCUX_CSSL_FP_EXPECT(0u - (2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)) - MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_MillerRabinTest));
            break;
        }

        /*
        * 2. Pre-check the prime candidate: GCD(prime candidate, A0)
        *    where: A0 - product of the first 9 prime numbers (hardcoded value).
        */
        MCUXCLPKC_FP_CALCFUP(mcuxClRsa_TestPrimeCandidate_Steps2_FUP,
                    mcuxClRsa_TestPrimeCandidate_Steps2_FUP_LEN);
        if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
        {
            status = MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_GCDA0_FAILED;
            MCUX_CSSL_FP_EXPECT(0u - MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) - MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_MillerRabinTest));
            break;
        }

        /*
        * 3. Check if prime_candidate - 1 is coprime to the public exponent e:
        *    GCD(prime_candidate - 1, e))
        */
        MCUXCLPKC_FP_CALCFUP(mcuxClRsa_TestPrimeCandidate_Steps3_FUP,
                    mcuxClRsa_TestPrimeCandidate_Steps3_FUP_LEN);
        if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
        {
            status = MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_GCDE_FAILED;
            MCUX_CSSL_FP_EXPECT(0u - MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_MillerRabinTest));
            break;
        }

        /*
        * 4. Run Miller-Rabin test
        *
        * Used functions: mcuxClRsa_MillerRabinTest
        */
        uint32_t  iP_iT = (MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_CANDIDATE << 8u) | MCUXCLRSA_INTERNAL_UPTRTINDEX_TESTPRIME_GCD1;
        MCUX_CSSL_FP_FUNCTION_CALL(retTest, mcuxClRsa_MillerRabinTest(pSession, iP_iT, keyBitLength));
        status = (mcuxClRsa_Status_t) retTest;
    }while (false);

    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);
    MCUXCLPKC_PS1_SETLENGTH_REG(bakPs1LenReg);
    MCUXCLPKC_PS2_SETLENGTH_REG(bakPs2LenReg);
    MCUXCLPKC_SETUPTRT(bakUPTRT);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_TestPrimeCandidate, status,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_MillerRabinTest));
}
