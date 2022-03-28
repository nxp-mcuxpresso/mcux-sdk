/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxClMath_ExactDivideOdd.c
 * @brief mcuxClMath: implementation of exact divide with odd divisor
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClMath_Private_ExactDivideOdd.h>

/* Suppose X is a multiple of Y, this function finds R such that (-X) + Y * R = 0.
 *
 * TODO
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ExactDivideOdd)
mcuxClMath_Status_Protected_t mcuxClMath_ExactDivideOdd(uint32_t iR_iX_iY_iT, uint32_t pkcByteLenX, uint32_t pkcByteLenY)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ExactDivideOdd);

    uint32_t backupPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();

    /* Prepare local UPTRT. */
    uint16_t pOperands[DivOdd_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt = MCUXCLMATH_FP_INITLOCALUPTRT(iR_iX_iY_iT, 0u, pOperands, 4u);
    uint32_t offsetT = (uint32_t) pOperands[DivOdd_T];
    pOperands[DivOdd_T1] = (uint16_t) (offsetT + MCUXCLPKC_WORDSIZE);
    pOperands[DivOdd_Ri] = 2u;  /* for _Fup_ExactDivideOdd_NDashY */

    MCUX_CSSL_FP_LOOP_DECL(NDashY);

    /* Calculate T = NDash(Y) = (-Y)^(-1) mod W. */
    MCUXCLPKC_PS2_SETLENGTH(0u, MCUXCLPKC_WORDSIZE);
    /* MISRA Ex. 9 to Rule 11.3 - PKC buffer is CPU word aligned */
    volatile uint32_t *pT = (volatile uint32_t *) MCUXCLPKC_OFFSET2PTR(offsetT);
    MCUXCLPKC_WAITFORFINISH();
    pT[0] = 1u;  /* 1 = (-Y)^(-1) mod 2. */
    for (uint32_t bit = 1u; bit < (MCUXCLPKC_WORDSIZE * 8u); bit <<= 1u)
    {
        /* Suppose T = T{bit} \equiv (-Y)^(-1)             (mod 2^(bit)),   */
        /* calculate T{2*bit} \equiv (2 + T{bit}*Y)*T{bit} (mod 2^(2*bit)). */
        MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_ExactDivideOdd_NDashY,
                            mcuxClMath_Fup_ExactDivideOdd_NDashY_LEN);

        MCUX_CSSL_FP_LOOP_ITERATION(NDashY,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    /* Calculate X0 = -X mod W^(lenR). */
    uint32_t pkcByteLenR = pkcByteLenX - pkcByteLenY + MCUXCLPKC_WORDSIZE;
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(0u, pkcByteLenR);
    MCUXCLPKC_FP_CALC_OP1_NEG(DivOdd_X, DivOdd_X);

    /* Prepare for carry handling. */
    uint32_t offsetX = (uint32_t) pOperands[DivOdd_X];
    pOperands[DivOdd_Xa] = (uint16_t) (offsetX + pkcByteLenY);
    pOperands[DivOdd_Xb] = (uint16_t) (offsetX + pkcByteLenY + MCUXCLPKC_WORDSIZE);
    uint32_t pkcByteLenCarryHandling = (pkcByteLenR > (pkcByteLenY + MCUXCLPKC_WORDSIZE))
                                       ? pkcByteLenR - (pkcByteLenY + MCUXCLPKC_WORDSIZE) : 0u;

    MCUX_CSSL_FP_LOOP_DECL(DivideLoop);
    MCUX_CSSL_FP_LOOP_DECL(CarryHandling);

    /* Balance FP in advance to avoid keeping variables in register/stack. */
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(DivideLoop, pkcByteLenR / MCUXCLPKC_WORDSIZE),
        MCUX_CSSL_FP_LOOP_ITERATIONS(CarryHandling, pkcByteLenCarryHandling / MCUXCLPKC_WORDSIZE) );

    /* Calculate R such that X0 + Y*R mod W^lenR. */
    uint32_t remainingPkcByteLenR = pkcByteLenR;
    uint32_t offsetRi = (uint32_t) pOperands[DivOdd_R];
    do
    {
        /* Prepare oplen = t * MCUXCLPKC_WORDSIZE. */
        uint32_t effectivePkcByteLenY = (remainingPkcByteLenR > pkcByteLenY)
                                        ? pkcByteLenY : remainingPkcByteLenR;

        MCUXCLPKC_WAITFORREADY();
        pOperands[DivOdd_Ri] = (uint16_t) offsetRi;
        MCUXCLPKC_PS1_SETLENGTH(0u, effectivePkcByteLenY);  /* don't care MCLen. */

        /* Calculate R[i], and X{i+1} = (Xi + R[i]*Y)   / W        */
        /*                            = (X0 + R[i~0]*Y) / W^(i+1). */
        /* ps, this FUP only calculates the least t significant words of X{i+1}. */
        MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_ExactDivideOdd_DivideLoop,
                            mcuxClMath_Fup_ExactDivideOdd_DivideLoop_LEN);

        MCUX_CSSL_FP_LOOP_ITERATION(DivideLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        offsetRi += MCUXCLPKC_WORDSIZE;

        /* Handle carry and copy most significant words of X{i+1}. */
        if (0u < pkcByteLenCarryHandling)
        {
            MCUXCLPKC_WAITFORFINISH();
            uint8_t carry = (uint8_t) MCUXCLPKC_GETCARRY();
            MCUXCLPKC_PS1_SETLENGTH(0u, pkcByteLenCarryHandling);  /* don't care MCLen. */
            MCUXCLPKC_FP_CALC_OP1_ADD_CONST(DivOdd_Xa, DivOdd_Xb, carry);

            MCUX_CSSL_FP_LOOP_ITERATION(CarryHandling,
                MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST );

            pkcByteLenCarryHandling -= MCUXCLPKC_WORDSIZE;
        }

        remainingPkcByteLenR -= MCUXCLPKC_WORDSIZE;
    } while (0u != remainingPkcByteLenR);

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);
    MCUXCLPKC_PS1_SETLENGTH_REG(backupPs1LenReg);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_ExactDivideOdd, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_LOOP_ITERATIONS(NDashY, MCUXCLPKC_LOG2_WORDSIZE + 3u),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG );
}
