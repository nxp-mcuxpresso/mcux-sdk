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

/** @file  mcuxClRsa_ComputeD.c
 *  @brief mcuxClRsa: function, which is called to compute private exponent d
 *         compliant with FIPS 186-4.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxClMemory.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClRsa.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>
#include <internal/mcuxClRsa_ComputeD_FUP.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_ComputeD)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_ComputeD(
  mcuxClSession_Handle_t           pSession,
  mcuxClRsa_KeyEntry_t *           pE,
  mcuxClRsa_KeyEntry_t *           pP,
  mcuxClRsa_KeyEntry_t *           pQ,
  mcuxClRsa_KeyEntry_t *           pD,
  const uint32_t                  keyBitLength
  )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_ComputeD);

    /*
     * Initialization:
     * - allocate buffers in PKC RAM
     * - update session (PKC workarea used...)
     */
    /* Size definitions */
    const uint32_t byteLenPQ = pP->keyEntryLength;  // P and Q have the same byte length
    const uint32_t primePQAlignLen = MCUXCLRSA_PKC_ROUNDUP_SIZE(byteLenPQ);

    const uint32_t keyLen = byteLenPQ * 2u;  // LCM have 2 times length of PQ
    const uint32_t keyAlignLen = MCUXCLRSA_PKC_ROUNDUP_SIZE(keyLen);

    /* Memory layout: | PSub1 (primePQAlignLen) | QSub1 (primePQAlignLen) | nDash (FW) | Lcm (keyAlignLen) | Phi (keyAlignLen) | T (keyAlignLen+FW) */
    uint32_t bufferSizeTotal = (primePQAlignLen * 2u) /* PSub1, QSub1 */ +
                               (keyAlignLen * 3u) + 2u * MCUXCLRSA_PKC_WORDSIZE /* Ndsah+Lcm, Phi, T */;
    uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, bufferSizeTotal / (sizeof(uint32_t)));
    if (NULL == pPkcWorkarea)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_ComputeD, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    uint8_t *pPSub1 = pPkcWorkarea;
    uint8_t *pQSub1 = pPSub1 + primePQAlignLen;
    uint8_t *pLcm = pQSub1 + primePQAlignLen + MCUXCLRSA_PKC_WORDSIZE /* offset for Ndsah */;
    uint8_t *pPhi = pLcm + keyAlignLen;
    uint8_t *pT = pPhi + keyAlignLen;

    /* Setup UPTR table */
    const uint32_t cpuWaSizeWord = MCUXCLRSA_ROUND_UP_TO_CPU_WORDSIZE(MCUXCLRSA_INTERNAL_COMPD_UPTRT_SIZE * (sizeof(uint16_t))) / (sizeof(uint32_t));
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
    uint16_t * pOperands = (uint16_t *) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    if (NULL == pOperands)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_ComputeD, MCUXCLRSA_STATUS_FAULT_ATTACK);
    }

    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_P]         = MCUXCLPKC_PTR2OFFSET(pP->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_Q]         = MCUXCLPKC_PTR2OFFSET(pQ->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_D]         = MCUXCLPKC_PTR2OFFSET(pD->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_E]         = MCUXCLPKC_PTR2OFFSET(pE->pKeyEntryData);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PSUB1]     = MCUXCLPKC_PTR2OFFSET(pPSub1);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1]     = MCUXCLPKC_PTR2OFFSET(pQSub1);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_LCM]       = MCUXCLPKC_PTR2OFFSET(pLcm);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI]       = MCUXCLPKC_PTR2OFFSET(pPhi);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_T]         = MCUXCLPKC_PTR2OFFSET(pT);
    pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_CONSTANT]  = 1u;

    /* Backup Ps1 length and UPTRT to recover in the end */
    uint16_t *pUptrtBak = MCUXCLPKC_GETUPTRT();
    uint32_t backupPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    /* Set UPTRT table */
    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_SETUPTRT(pOperands);

    /*
     * call the FUP code to do the below steps
     * 1. Compute p' = p-1
     * 2. Compute q' = q-1
     * 3. Compute lcm(p-1, q-1)=|(p-1)(q-1)|/gcd(p-1,q-1)
     * 3.1 Compute a = (p-1)(q-1)
     * 3.2 Compute b = gcd(p-1,q-1)
     */
    MCUXCLPKC_PS1_SETLENGTH(primePQAlignLen, primePQAlignLen);
    MCUXCLPKC_FP_CALCFUP(mcuxClRsa_ComputeD_Steps123_FUP,
        mcuxClRsa_ComputeD_Steps123_FUP_LEN);
    MCUXCLPKC_WAITFORFINISH();
    uint32_t leadingZeroN;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1, &leadingZeroN));
    uint32_t realGcdByteLen = primePQAlignLen - (leadingZeroN >> 3u);

    /*
     * 3.3 Compute lcm(p-1, q-1)= a/b
     *
     * Used functions: mcuxClMath_ExactDivide
     */
    MCUXCLPKC_PS1_SETLENGTH(keyAlignLen, keyAlignLen);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_LCM, 0u);
    MCUXCLPKC_WAITFORFINISH();
    MCUXCLMATH_FP_EXACTDIVIDE(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_LCM,
                        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI,
                        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_QSUB1,
                        MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_T,
                        MCUXCLRSA_PKC_ROUNDUP_SIZE(keyLen),
                        MCUXCLRSA_PKC_ROUNDUP_SIZE(realGcdByteLen));

    /*
     * 4. Compute d := e^(-1) mod lcm(p-1, q-1)
     *
     * Used functions: mcuxClRsa_ModInv
     */

    MCUXCLPKC_PS1_SETLENGTH(keyAlignLen, keyAlignLen);
    const uint32_t eAlignLen = MCUXCLRSA_PKC_ROUNDUP_SIZE(pE->keyEntryLength);
    MCUXCLPKC_PS2_SETLENGTH(0, eAlignLen);
    /* Clear the PHI buffer */
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, 0u);
    /* Copy e to the PHI buffer (the content pointed by pE should not be destroyed) */
    MCUXCLPKC_FP_CALC_OP2_OR_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_E, 0u);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClRsa_ModInv(MCUXCLPKC_PACKARGS4(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_D, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_LCM, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_T)));
    //don't need check the return value, it always return ok

    /*
     * 5. Determine the length of d without leading zeros
     */
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_D, &leadingZeroN));
    pD->keyEntryLength = keyAlignLen - (leadingZeroN >> 3u);

    /*
     * 6. Verify FIPS 186-4 condition on lower bound of d
     *    If d <= 2^(nlen/2), then function returns MCUXCLRSA_STATUS_INVALID_INPUT error.
     *
     * Used functions: FAME operation.
     */
    /* Clear buffers phi, its length is nlen */
    MCUXCLPKC_PS1_SETLENGTH(0u, keyAlignLen);
    MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, 0u);
    MCUXCLPKC_WAITFORFINISH();

    uint32_t idx = (keyBitLength >> 1u) >> 3u;
    uint32_t lowBoundByte = ((uint32_t)1u << ((keyBitLength >> 1u) & 7u));
    pPhi[idx] = (uint8_t)lowBoundByte;
    MCUXCLPKC_FP_CALC_OP1_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_PHI, MCUXCLRSA_INTERNAL_UPTRTINDEX_COMPD_D);
    MCUXCLPKC_WAITFORFINISH();

    /* Recover session, Ps1 length and Uptrt */
    mcuxClSession_freeWords_pkcWa(pSession, bufferSizeTotal / (sizeof(uint32_t)));
    mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);
    MCUXCLPKC_PS1_SETLENGTH_REG(backupPs1LenReg);
    MCUXCLPKC_SETUPTRT(pUptrtBak);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_ComputeD,
            ((MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY()) ? MCUXCLRSA_STATUS_INVALID_INPUT : MCUXCLRSA_STATUS_KEYGENERATION_OK),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ExactDivide),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP2_OR_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRsa_ModInv),
            2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP
            );
}
