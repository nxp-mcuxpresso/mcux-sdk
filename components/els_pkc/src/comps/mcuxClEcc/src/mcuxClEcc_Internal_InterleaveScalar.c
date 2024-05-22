/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/**
 * @file  mcuxClEcc_Internal_InterleaveOneScalar.c
 * @brief mcuxClEcc: implementation of ECC function mcuxClEcc_InterleaveScalar
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_Interleave_FUP.h>


/**
 * This function prepares one scalar to be used in scalar multiplication.
 * The scalar will be bit-wised interleaved, e.g.,
 * (L0, L1, L2, ..., H0, H1, H2, ...) --> (L0, H0, L1, H1, L2, H2, ...).
 *
 * Inputs:
 *   iScalar index of PKC operand which contains the scalar;
 *   scalarBitLength: scalar length in bits.
 *   numberOfInterleavings: scalar will be numberOfInterleavings times interleaved
 *
 * Inputs in pOperands[] and PKC workarea:
 *   buffer iScalar which contains the scalar.
 *
 * Prerequisites: N/A.
 *
 * Result in PKC workarea:
 *   buffer iScalar which contain the interleaved scalar (always in-place).
 *
 * Other modifications:
 *   buffers T0 and T1 are modified (as temp);
 *   offsets pOperands[ECC_V0/ECC_V1/ECC_V3] are modified;
 *   ps2 LEN and MCLEN are modified.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_InterleaveScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_InterleaveScalar(uint16_t iScalar, uint32_t scalarBitLength, uint32_t numberOfInterleavings)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_InterleaveScalar);

    uint32_t ps1LenRegBackup = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - UPTR table is 32-bit aligned in ECC component.");
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();
    uint32_t bitLenHalfScalar = scalarBitLength - (scalarBitLength >> 1);  /* ceil(bitLen / 2) */
    uint32_t byteLenHalfScalar_PKCWord = ((bitLenHalfScalar + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u)) * MCUXCLPKC_WORDSIZE;

    uint32_t offsets_V1_V0 = /* ECC_V0 */ (uint32_t) pOperands[iScalar]
                             /* ECC_V1 */ + (((uint32_t) pOperands[ECC_T0] + byteLenHalfScalar_PKCWord) << 16);

    MCUXCLPKC_WAITFORREADY();
    /* MISRA Ex. 9 to Rule 11.3 - pOperands32 is pointer to 16-bit offset table */
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_V0, ECC_V1, offsets_V1_V0);
    pOperands[ECC_V3] = (uint16_t) (0u - bitLenHalfScalar);  /* PKC will ignore higher bits of shifting amount. */

    MCUXCLPKC_ENABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH(0u, 2u * byteLenHalfScalar_PKCWord);
    MCUXCLPKC_PS2_SETLENGTH(byteLenHalfScalar_PKCWord, byteLenHalfScalar_PKCWord);

    /* Interleave iScalar. */
    for(uint32_t i = numberOfInterleavings; i > 0u ; i--)
    {
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Interleave, mcuxClEcc_FUP_Interleave_LEN);
    }

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_DISABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenRegBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_InterleaveScalar, MCUXCLECC_STATUS_OK,
        numberOfInterleavings * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)
    );
}
