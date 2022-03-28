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

/**
 * @file  mcuxClMath_ModExp_SqrMultL2R.c
 * @brief mcuxClMath: modular exponentiation, left-to-right binary square and multiply
 */


#include <platform_specific_headers.h>
#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ModExp_SqrMultL2R)
mcuxClMath_Status_Protected_t mcuxClMath_ModExp_SqrMultL2R(const uint8_t *pExp, uint32_t byteLenExp, uint32_t iR_iX_iN_iT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ModExp_SqrMultL2R);

    /* Count Hamming weight of exponent. */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint32_t hwExp = 0u;
    uint32_t byteIndex_MSNZByte = 0u;
    for (int32_t idx = (int32_t) byteLenExp - 1; idx >= 0; idx--)
    {
        uint32_t expByte = (uint32_t) pExp[idx];

        /* Find the last non-zero byte from LSByte (= first non-zero byte from MSByte). */
        if (0u != expByte)
        {
            byteIndex_MSNZByte = (uint32_t) idx;
        }

        expByte = expByte - ((expByte >> 1) & 0x55u);
        expByte = (expByte & 0x33u) + ((expByte & 0xCCu) >> 2);
        expByte = (expByte & 0x07u) + ((expByte & 0x70u) >> 4);
        hwExp += expByte;
    }
    uint32_t byteExp = (uint32_t) pExp[byteIndex_MSNZByte];

    /* Calculate bit index of starting bit (skip the most significant nonzero bit). */
    const uint32_t bitIndex_MSBitNext = (8u * (byteLenExp - byteIndex_MSNZByte)) - (__CLZ(byteExp) - 24u) - 2u;
    int32_t bitIndex = (int32_t) bitIndex_MSBitNext;

    /* Calculate the number of loop iteration for FP. */
    MCUX_CSSL_FP_COUNTER_STMT(const uint32_t loopIteration = (bitIndex_MSBitNext + 1u) + (hwExp - 1u));

    const uint32_t iR = (iR_iX_iN_iT >> 24) & 0xFFu;  /* Also used as T1. */
    const uint32_t iX = (iR_iX_iN_iT >> 16) & 0xFFu;
    const uint32_t iN = (iR_iX_iN_iT >>  8) & 0xFFu;
    const uint32_t iT = iR_iX_iN_iT & 0xFFu;          /* T0 */

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(iR, iX, 0u);  /* Copy X to R (T1). */

    uint32_t args[4];
    args[0] = MCUXCLPKC_PACKARGS4(iT,iR,iX,iN);  /* state=0b00, T0 = T1 * X  mod N */
    args[1] = MCUXCLPKC_PACKARGS4(iT,iR,iR,iN);  /* state=0b01, T0 = T1 * T1 mod N */
    args[2] = MCUXCLPKC_PACKARGS4(iR,iT,iX,iN);  /* state=0b10, T1 = T0 * X  mod N */
    args[3] = MCUXCLPKC_PACKARGS4(iR,iT,iT,iN);  /* state=0b11, T1 = T0 * T0 mod N */

    uint32_t state = 1u;
    uint32_t shift = 1u;  /* shift to next bit (=1) or not (=0) */

    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop);
    while(bitIndex >= 0)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MM);

        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_Calc(MCUXCLPKC_PARAMMODE_MC1(MM), args[state]));
        (void) retValTemp;  /* mcuxClPkc_Calc always returns OK. */

        state = 3u ^ state;  /* swap the two temp operands. */
        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
        uint32_t expBit = ((uint32_t) pExp[byteLenExp - 1u - ((uint32_t) bitIndex / 8u)] >> ((uint32_t) bitIndex & 7u)) & 1u;
        shift ^= expBit;     /* if expBit = 1, the while-loop will stay in this bit for one more iteration. */
        state |= shift;      /* always squaring if shifting to a new bit. */

        bitIndex -= (int32_t) shift;
    }

    /* The result is in T1 (R) if state.bit1 = 0; */
    /*                  T0 (T) if state.bit1 = 1. */
    if (0u != (state >> 1))
    {
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(iR, iT, 0u);  /* Copy result to R. */
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_ModExp_SqrMultL2R, MCUXCLMATH_ERRORCODE_OK,
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop, loopIteration),
        MCUX_CSSL_FP_CONDITIONAL((1u == (loopIteration & 0x01u)), MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST) );
}
