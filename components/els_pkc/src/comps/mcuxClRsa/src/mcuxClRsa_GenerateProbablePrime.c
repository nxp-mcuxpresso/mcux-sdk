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

/** @file  mcuxClRsa_GenerateProbablePrime.c
 *  @brief mcuxClRsa: function, which is called to generates probably prime number
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMemory.h>

#include <mcuxClPkc.h>
#include <mcuxClRandom.h>

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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_GenerateProbablePrime)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_GenerateProbablePrime(
  mcuxClSession_Handle_t           pSession,
  mcuxClRsa_KeyEntry_t *           pE,
  mcuxClRsa_KeyEntry_t *           pPrimeCandidate,
  const uint32_t                  keyBitLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_GenerateProbablePrime,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));

    mcuxClRsa_Status_t status = MCUXCLRSA_STATUS_KEYGENERATION_ITERATIONSEXCEEDED;
    uint32_t loopCounter = 0u;
    const uint32_t loopMax = 5u * (keyBitLength / 2u);
    uint32_t cntRandomGen = 0u;
    uint32_t cntTestPrime = 0u;

    /* Little-endian representation of 0xb504f333f9de6485u, which is 64 most significant bits of sqrt(2)(2^(nlen/2)-1) rounded up */
    static const uint8_t numToCompare[] = {0x85u, 0x64u, 0xDEu, 0xF9u, 0x33u, 0xF3u, 0x04u, 0xB5u};
    /* Little-endian representation of 0xC0CFD797u, which is the product of the first 9 prime numbers starting from 3*/
    static const uint8_t a0[] = {0x97u, 0xD7u, 0xCFu, 0xC0u};

    /*
    * Initialization:
    * - allocate buffers in PKC RAM
    * - copy 0xb504f333f9de6485u value into buffer located in PKC RAM
    * - copy A0 value into buffer located in PKC RAM
    * - update session (PKC workarea used...)
    */

    const uint32_t pkcWaSizeWord = (2u * MCUXCLRSA_PKC_WORDSIZE) / (sizeof(uint32_t));
    uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, pkcWaSizeWord);
    if (NULL == pPkcWorkarea)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_GenerateProbablePrime, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    uint8_t *pNumToCompare = pPkcWorkarea;
    uint8_t *pA0 = pPkcWorkarea + MCUXCLRSA_PKC_WORDSIZE;

    /* Setup UPTR table */
    const uint32_t cpuWaSizeWord =  MCUXCLRSA_INTERNAL_GENERATEPROBABLEPRIME_WACPU_SIZE_WO_TESTPRIME_AND_MILLERRABIN(keyBitLength/8u/2u) / (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
    uint16_t * pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    if (NULL == pOperands)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_GenerateProbablePrime, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_NUMTOCOMPARE] = MCUXCLPKC_PTR2OFFSET(pNumToCompare);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_A0] = MCUXCLPKC_PTR2OFFSET(pA0);
    const uint32_t iNumToCmp_iA0 = ((uint32_t)MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_NUMTOCOMPARE << 8u) | MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_A0;
 
    /* Backup Ps1 length and UPTRT, restore them when returning */
    uint16_t *bakUPTRT = MCUXCLPKC_GETUPTRT();
    uint32_t bakPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint32_t bakPs2LenReg = MCUXCLPKC_PS2_GETLENGTH_REG();

    /* Set UPTRT table */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(pOperands);

    MCUXCLPKC_PS1_SETLENGTH(0u, MCUXCLRSA_PKC_WORDSIZE);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_NUMTOCOMPARE, 0u);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_GENPRIME_A0, 0u);
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMemory_copy(pNumToCompare + MCUXCLRSA_PKC_WORDSIZE - sizeof(numToCompare),
        numToCompare, sizeof(numToCompare), sizeof(numToCompare)));

    MCUXCLMEMORY_FP_MEMORY_COPY(pA0, a0, sizeof(a0));


#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
    uint8_t * pPrimeKeyDataCpu = (uint8_t*) pOperands + MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE((MCUXCLRSA_INTERNAL_GENPRIME_UPTRT_SIZE * sizeof(uint16_t)));
#endif

    do
    {
        /*
        * Generate a random prime candidate for given key size using DRBG:
        *    - Ensure that prime candidate is odd;
        *    - Ensure that prime candidate is congruent 3 mod 4 (this deviation from FIPS 186-4 has been approved).
        *
        *    The session pointed to by pSession shall be initialized with the entropy level (security strength)
        *    in accordance with the value of keyBitLength, as specified in SP 800-57, Part 1.
        *
        * Used functions: RNG provided through the pSession
        */
        cntRandomGen++;
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
        MCUX_CSSL_FP_FUNCTION_CALL(retRandomGen, mcuxClRandom_generate(pSession, pPrimeKeyDataCpu, pPrimeCandidate->keyEntryLength));
        if(MCUXCLRANDOM_STATUS_OK != retRandomGen)
        {
            status = MCUXCLRSA_STATUS_RNG_ERROR;
            break;
        }
        MCUXCLMEMORY_FP_MEMORY_COPY(pPrimeCandidate->pKeyEntryData, pPrimeKeyDataCpu, pPrimeCandidate->keyEntryLength);

#else
        MCUX_CSSL_FP_FUNCTION_CALL(retRandomGen, mcuxClRandom_generate(pSession, pPrimeCandidate->pKeyEntryData, pPrimeCandidate->keyEntryLength));
        if (MCUXCLRANDOM_STATUS_OK != retRandomGen)
        {
            status = MCUXCLRSA_STATUS_RNG_ERROR;
            break;
        }
#endif
        pPrimeCandidate->pKeyEntryData[0] |= 0x03u;

        cntTestPrime++;
        MCUX_CSSL_FP_FUNCTION_CALL(retTest, mcuxClRsa_TestPrimeCandidate(pSession, pE, pPrimeCandidate, keyBitLength, iNumToCmp_iA0));
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
        if ((MCUXCLRSA_STATUS_KEYGENERATION_OK == retTest) || (MCUXCLRSA_STATUS_RNG_ERROR == retTest) || (MCUXCLRSA_STATUS_ERROR == retTest))
#else
        if ((MCUXCLRSA_STATUS_KEYGENERATION_OK == retTest) || (MCUXCLRSA_STATUS_RNG_ERROR == retTest))
#endif
        {
            status = retTest;
            break;
        }
        else if (MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_CMP_FAILED != retTest)
        {
            loopCounter++;
        }
        else
        {
            /* Do nothing to meet MISRA */
        }
    } while(loopCounter < loopMax);

    /* Recover session, Ps1 length and Uptrt */
    mcuxClSession_freeWords_pkcWa(pSession, pkcWaSizeWord);
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);
    MCUXCLPKC_PS1_SETLENGTH_REG(bakPs1LenReg);
    MCUXCLPKC_PS2_SETLENGTH_REG(bakPs2LenReg);
    MCUXCLPKC_SETUPTRT(bakUPTRT);

/* Check define outside of macro so the MISRA rule 20.6 does not get violated */
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_GenerateProbablePrime, status,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) * cntRandomGen,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) * cntRandomGen,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_TestPrimeCandidate) * cntTestPrime);
#else
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_GenerateProbablePrime, status,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) * cntRandomGen,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_TestPrimeCandidate) * cntTestPrime);
#endif

}

