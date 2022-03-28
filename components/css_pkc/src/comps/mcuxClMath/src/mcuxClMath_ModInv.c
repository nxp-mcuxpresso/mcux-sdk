/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClMath_ModInv.c
 *  @brief mcuxClMath: modular inversion implementation
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_FUP_programs.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ModInv)
mcuxClMath_Status_Protected_t mcuxClMath_ModInv(uint32_t iR_iX_iN_iT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ModInv);

    uint32_t backupPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    uint32_t operandSize = MCUXCLPKC_PS1_UNPACK_OPLEN(backupPs1LenReg);
    operandSize &= ~((uint32_t) MCUXCLPKC_WORDSIZE - 1u);  /* round down to a multiple of PKC wordsize, to calculate exp correctly. */

    /* Prepare local UPTRT. */
    uint16_t pOperands[MODINV_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt = MCUXCLMATH_FP_INITLOCALUPTRT(iR_iX_iN_iT, 0, pOperands, 4u);

    /* WAITFORREADY in mcuxClMath_InitLocalUptrt(...). */
    uint16_t offsetT = pOperands[MODINV_T];
    pOperands[MODINV_T1] = (uint16_t) (offsetT + MCUXCLPKC_WORDSIZE);
    pOperands[MODINV_CONST1] = 0x0001u;

    MCUXCLPKC_PS1_SETLENGTH(31u, operandSize);
    MCUXCLPKC_PS2_SETLENGTH(0u, operandSize + MCUXCLPKC_WORDSIZE);

    MCUXCLPKC_FP_CALCFUP(mcuxClMath_ModInv_Fup1, mcuxClMath_ModInv_Fup1_LEN );

    /* MISRA Ex. 9 - Rule 11.3 - PKC buffer is CPU word aligned. */
    const volatile uint32_t *pExp = (volatile uint32_t *) MCUXCLPKC_OFFSET2PTR(offsetT);
    /* MISRA Ex. 9 - Rule 11.3 - PKC buffer is CPU word aligned. */
    volatile uint32_t *pR = (volatile uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[MODINV_R]);

    MCUXCLPKC_WAITFORFINISH();
    MCUXCLPKC_PS1_SETLENGTH_REG(backupPs1LenReg);
    uint32_t exponent = *pExp;
    uint32_t operandBitLen = operandSize << 3;
    const mcuxClPkc_FUPEntry_t* mcuxClMath_ModInv_Fup3;

    if (exponent <= operandBitLen)
    {
        exponent = operandBitLen - exponent;
        mcuxClMath_ModInv_Fup3 = mcuxClMath_ModInv_Fup3a;
    }
    else
    {
        exponent = (operandBitLen * 2u) - exponent;
        mcuxClMath_ModInv_Fup3 = mcuxClMath_ModInv_Fup3b;
    }

    /* Set R = 2^(operandBitLEn - exponent) or 2^(2*operandBitLEn - exponent). */
    pR[exponent >> 5] = (uint32_t) 1u << (exponent & 0x0000001Fu);

    /* Convert AlmostMontgomeryInverse to modular inverse. */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_ModInv_Fup3, mcuxClMath_ModInv_Fup3_LEN);

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_ModInv, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* Fup1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));  /* Fup3a or Fup3b */
}
