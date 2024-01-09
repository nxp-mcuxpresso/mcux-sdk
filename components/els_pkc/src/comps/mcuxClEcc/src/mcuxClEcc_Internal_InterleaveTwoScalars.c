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

/**
 * @file  mcuxClEcc_Internal_InterleaveTwoScalars.c
 * @brief mcuxClEcc: implementation of ECC function mcuxClEcc_InterleaveTwoScalars
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
 * This function prepares two scalars to be used in scalar multiplication.
 * Each scalar will be bit-wised interleaved, e.g.,
 * (L0, L1, L2, ..., H0, H1, H2, ...) --> (L0, H0, L1, H1, L2, H2, ...).
 *
 * Inputs:
 *   iScalar0_iScalar1: two indices of PKC operands, containing two scalars;
 *   scalarBitLength: scalar length in bits.
 *
 * Inputs in pOperands[] and PKC workarea:
 *   buffers iScalar0 and iScalar1 contain two scalars.
 *
 * Prerequisites: N/A.
 *
 * Result in PKC workarea:
 *   buffers iScalar0 and iScalar1 contain two interleaved scalars (always in-place).
 *
 * Other modifications:
 *   buffers T0 and T1 are modified (as temp);
 *   offsets pOperands[ECC_V0/ECC_V1/ECC_V3] are modified;
 *   ps2 LEN and MCLEN are modified.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_InterleaveTwoScalars)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_InterleaveTwoScalars(uint16_t iScalar0_iScalar1, uint32_t scalarBitLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_InterleaveTwoScalars);

    uint32_t ps1LenRegBackup = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

    uint8_t iScalar0 = (uint8_t) (iScalar0_iScalar1 >> 8);
    uint8_t iScalar1 = (uint8_t) (iScalar0_iScalar1 & 0xFFu);

    uint32_t bitLenHalfScalar = scalarBitLength - (scalarBitLength >> 1);  /* ceil(bitLen / 2) */
    uint32_t byteLenHalfScalar_PKCWord = ((bitLenHalfScalar + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u)) * MCUXCLPKC_WORDSIZE;

    uint32_t offsets_V1_V0 = /* ECC_V0 */ (uint32_t) pOperands[iScalar0]
                             /* ECC_V1 */ + (((uint32_t) pOperands[ECC_T0] + byteLenHalfScalar_PKCWord) << 16);

    MCUXCLPKC_WAITFORREADY();
    /* MISRA Ex. 9 to Rule 11.3 - pOperands32 is pointer to 16-bit offset table */
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_V0, ECC_V1, offsets_V1_V0);
    pOperands[ECC_V3] = (uint16_t) (0u - bitLenHalfScalar);  /* PKC will ignore higher bits of shifting amount. */

    MCUXCLPKC_ENABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH(0u, 2u * byteLenHalfScalar_PKCWord);
    MCUXCLPKC_PS2_SETLENGTH(byteLenHalfScalar_PKCWord, byteLenHalfScalar_PKCWord);

    /* Interleave scalar0. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Interleave, mcuxClEcc_FUP_Interleave_LEN);

    /* Interleave scalar1. */
    MCUXCLPKC_WAITFORREADY();
    pOperands[ECC_V0] = pOperands[iScalar1];
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Interleave, mcuxClEcc_FUP_Interleave_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_DISABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenRegBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_InterleaveTwoScalars, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
