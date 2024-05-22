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

/**
 * @file  mcuxClMath_ExactDivideOdd.c
 * @brief mcuxClMath: implementation of exact divide with odd divisor
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClMath_ExactDivideOdd_FUP.h>
#include <internal/mcuxClMath_Internal_ExactDivideOdd.h>


/**
 * [DESIGN]
 * This function assumes the dividend X is exactly a multiple of the divisor Y.
 * Since the most significant PKC word of Y is assumed to be nonzero, the result
 * length is rPkcByteLen = xPkcByteLength - yPkcByteLength + MCUXCLPKC_WORDSIZE.
 * This function calculates R = X/Y by solving R satisfying ((-X) + R*Y) mod W^rPkcWord,
 * where W = 256^MCUXCLPKC_WORDSIZE and rPkcWord = rPkcByteLen / MCUXCLPKC_WORDSIZE.
 *
 * R is solved from its least significant PKC word R[0] to the most significant word R[rPkcWord - 1].
 * Let X0 = (-X) mod 256^rPkcByteLen. Since X0 + R*Y mod W = 0,
 * R[0] = NDash(Y) * X0[0] mod W, where NDash(Y) = (-Y)^(-1) mod W. And X1 = (X0 + R[0]*Y)/W.
 * This function calculates R[i] = NDash(Y) * Xi[0] mod W, and
 * X{i+1} = (Xi + R[i]*Y)/W = (X0 + R[i:0]*Y)/(W^(i+1)), until i = rPkcWord - 1.
 *
 * Since X0 = (X{i+1}*(W^(i+1)) - R[i:0]*Y) \equiv 0 (mod W^rPkcWord), this function
 * needs to calculate only the least significant (rPkcWord - (i+1)) PKC words of X{i+1}.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ExactDivideOdd)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ExactDivideOdd(uint32_t iR_iX_iY_iT, uint32_t xPkcByteLength, uint32_t yPkcByteLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ExactDivideOdd);

    uint32_t backupPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();

    /* Prepare local UPTRT. */
    uint16_t pOperands[DivOdd_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt;
    /* mcuxClMath_InitLocalUptrt always returns _OK. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_InitLocalUptrt(iR_iX_iY_iT, 0u, pOperands, 4u, &backupPtrUptrt));
    uint16_t offsetT = pOperands[DivOdd_T];
    pOperands[DivOdd_T1] = (uint16_t) (offsetT + MCUXCLPKC_WORDSIZE);
    pOperands[DivOdd_Ri] = 2u;  /* for _Fup_ExactDivideOdd_NDashY */
    pOperands[DivOdd_CONST0] = 0u;

    MCUX_CSSL_FP_LOOP_DECL(NDashY);

    MCUXCLPKC_PS2_SETLENGTH(0u, MCUXCLPKC_WORDSIZE);  /* MCLEN on higher 16 bits is not used. */
    volatile uint32_t *pT = (volatile uint32_t *) MCUXCLPKC_OFFSET2PTRWORD(offsetT);
    MCUXCLPKC_WAITFORFINISH();
    pT[0] = 1u;  /* 1 = (-Y)^(-1) mod 2. */

    /* Calculate T = NDash(Y) = (-Y)^(-1) mod W, where W = 256^MCUXCLPKC_WORDSIZE. */
    for (uint32_t bit = 1u; bit < (MCUXCLPKC_WORDSIZE * 8u); bit <<= 1u)
    {
        MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_ExactDivideOdd_NDashY,
                            mcuxClMath_Fup_ExactDivideOdd_NDashY_LEN);

        MCUX_CSSL_FP_LOOP_ITERATION(NDashY,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    uint32_t rPkcByteLen = xPkcByteLength - yPkcByteLength + MCUXCLPKC_WORDSIZE;
    MCUXCLPKC_WAITFORREADY();

    /* Calculate X0 = -X mod W^rPkcWord, where rPkcWord = rPkcByteLen / MCUXCLPKC_WORDSIZE. */
    MCUXCLPKC_PS1_SETLENGTH(0u, rPkcByteLen);  /* MCLEN on higher 16 bits is not used. */
    MCUXCLPKC_FP_CALC_OP1_NEG(DivOdd_X, DivOdd_X);

    /* Prepare for carry handling. */
    /* When the length of Y is small, the MACCR in the FUP program in the loop       */
    /* only calculates, e.g., (X[yPkcWord:0] + R[0]*Y)/W in the first iteration.     */
    /* Carry propagation to X[rPkcWord-1:yPkcWord+1] needs to be handled separately. */
    uint32_t offsetX = (uint32_t) pOperands[DivOdd_X];
    pOperands[DivOdd_Xa] = (uint16_t) (offsetX + yPkcByteLength);
    pOperands[DivOdd_Xb] = (uint16_t) (offsetX + yPkcByteLength + MCUXCLPKC_WORDSIZE);
    uint32_t pkcByteLenCarryHandling = (rPkcByteLen > (yPkcByteLength + MCUXCLPKC_WORDSIZE))
                                       ? (rPkcByteLen - (yPkcByteLength + MCUXCLPKC_WORDSIZE)) : 0u;

    MCUX_CSSL_FP_LOOP_DECL(DivideLoop);
    MCUX_CSSL_FP_LOOP_DECL(CarryHandling);

    /* Balance FP in advance to avoid keeping variables in register/stack. */
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(DivideLoop, rPkcByteLen / MCUXCLPKC_WORDSIZE),
        MCUX_CSSL_FP_LOOP_ITERATIONS(CarryHandling, pkcByteLenCarryHandling / MCUXCLPKC_WORDSIZE) );

    /* This loop calculates R[rPkcWord-1:0] such that X0 + R*Y mod W^rPkcWord = 0. */
    uint32_t rRemainingPkcByteLen = rPkcByteLen;
    uint32_t offsetRi = (uint32_t) pOperands[DivOdd_R];
    do
    {
        /* In iteration i (i = 0 ~ rPkcWord-1), calculate R[i] and X{i+1}. */

        /* Prepare OPLEN = min(yPkcWord, rPkcWord-i) * MCUXCLPKC_WORDSIZE. */
        uint32_t effectivePkcByteLenY = (rRemainingPkcByteLen > yPkcByteLength)
                                        ? yPkcByteLength : rRemainingPkcByteLen;

        MCUXCLPKC_WAITFORREADY();
        pOperands[DivOdd_Ri] = (uint16_t) offsetRi;
        MCUXCLPKC_PS1_SETLENGTH(0u, effectivePkcByteLenY);  /* MCLEN on higher 16 bits is not used. */

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
            MCUXCLPKC_PS1_SETLENGTH(0u, pkcByteLenCarryHandling);  /* MCLEN on higher 16 bits is not used. */
            MCUXCLPKC_FP_CALC_OP1_ADD_CONST(DivOdd_Xa, DivOdd_Xb, carry);

            MCUX_CSSL_FP_LOOP_ITERATION(CarryHandling,
                MCUXCLPKC_FP_CALLED_CALC_OP1_ADD_CONST );

            pkcByteLenCarryHandling -= MCUXCLPKC_WORDSIZE;
        }

        rRemainingPkcByteLen -= MCUXCLPKC_WORDSIZE;
    } while (0u != rRemainingPkcByteLen);

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);
    MCUXCLPKC_PS1_SETLENGTH_REG(backupPs1LenReg);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_ExactDivideOdd,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_LOOP_ITERATIONS(NDashY, MCUXCLPKC_LOG2_WORDSIZE + 3u),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG );
}
