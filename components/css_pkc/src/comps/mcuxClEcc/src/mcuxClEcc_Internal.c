/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClEcc_Internal.c
 *  @brief mcuxClEcc: implementation of ECC internal functions
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Interleave)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Interleave(uint16_t iScalar0_iScalar1, uint32_t bitLenScalar)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Interleave);

    uint32_t ps1LenRegBackup = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t *pOperands32 = (uint32_t *) pOperands;

    uint8_t iScalar0 = (uint8_t) (iScalar0_iScalar1 >> 8);
    uint8_t iScalar1 = (uint8_t) (iScalar0_iScalar1 & 0xFFu);

    uint32_t bitLenHalfScalar = bitLenScalar - (bitLenScalar >> 1);
    uint32_t byteLenHalfScalar_PKCWord = ((bitLenHalfScalar + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u)) * MCUXCLPKC_WORDSIZE;

    uint32_t offsets_VY0_VX0 =  (uint32_t) pOperands[iScalar0]
                                + (((uint32_t) pOperands[ECC_T0] + byteLenHalfScalar_PKCWord) << 16);
    uint32_t offsets_VZ_VZ0  =  0x01u
                                + ((0u - bitLenHalfScalar) << 16);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, offsets_VY0_VX0);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ, offsets_VZ_VZ0);

    MCUXCLPKC_ENABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH(0u, 2u * byteLenHalfScalar_PKCWord);
    MCUXCLPKC_PS2_SETLENGTH(byteLenHalfScalar_PKCWord, byteLenHalfScalar_PKCWord);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Interleave, mcuxClEcc_Fup_Interleave_LEN);

    MCUXCLPKC_WAITFORREADY();
    pOperands[ECC_VX0] = pOperands[iScalar1];
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Interleave, mcuxClEcc_Fup_Interleave_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_DISABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenRegBackup);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Interleave, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
