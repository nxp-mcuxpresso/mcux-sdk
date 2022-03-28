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

/** @file  mcuxClMath_QDash.c
 *  @brief mcuxClMath: implementation of the functions mcuxClMath_QDash and mcuxClMathQSquared
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_FUP_programs.h>


/* Computes Q * Q' mod n, where Q = 256^(ps1 LEN) mod n, and Q' = 256^len mod n. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_QDash)
mcuxClMath_Status_Protected_t mcuxClMath_QDash(uint32_t iQDash_iNShifted_iN_iT, uint16_t len)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_QDash);

    uint16_t pOperands[QDASH_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt = MCUXCLMATH_FP_INITLOCALUPTRT(iQDash_iNShifted_iN_iT, 0, pOperands, 4u);

    /* Prepare 2Q mod n, which is the Montgomery representation of 2. */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_QDash_Fup_Init,mcuxClMath_QDash_Fup_Init_LEN );

    /* Prepare exponent for calculating (2^8)^(len) = 2^(8 * len). */
    uint32_t exponent = (uint32_t) len << 3;

    /* Scan exponent from MSbit (bit 15 + 3), and skip leading zeros plus one more bit (leading 1). */
    uint32_t bitMask = (uint32_t) 1u << ((8u * (sizeof(uint16_t))) - 1u + 3u);
    uint32_t bit;
    do
    {
        bit = exponent & bitMask;
        bitMask >>= 1;
    } while(0u == bit);  /* Assume exponent != 0, otherwise, this is an endless loop. */

    MCUX_CSSL_FP_LOOP_DECL(QDash_SquareMultiply);
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(QDash_SquareMultiply,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));

        if (0u == (exponent & bitMask))
        {
            /* Squaring only. */
            MCUXCLPKC_FP_CALCFUP(mcuxClMath_QDash_Fup_Loop0, mcuxClMath_QDash_Fup_Loop0_LEN);
        }
        else
        {
            /* Squaring and multiplication. */
            MCUXCLPKC_FP_CALCFUP(mcuxClMath_QDash_Fup_Loop1, mcuxClMath_QDash_Fup_Loop1_LEN);
        }

        bitMask >>= 1;
    } while(0u != bitMask);  /* Assume exponent != 0, there are at least 3 squarings. */

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);

    uint32_t leadingZeroExponent = (uint32_t) __CLZ((uint32_t) len) - 3u;
    MCUX_CSSL_FP_COUNTER_STMT(uint32_t lterationsSquareMultiply = ((sizeof(uint32_t)) * 8u) - leadingZeroExponent - 1u);  /* Skip the first nonzero bit. */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_QDash, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_LOOP_ITERATIONS(QDash_SquareMultiply, lterationsSquareMultiply));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_QSquared)
mcuxClMath_Status_Protected_t mcuxClMath_QSquared(uint32_t iQSqr_iNShifted_iN_iT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_QSquared,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash));

    uint16_t len = (uint16_t) MCUXCLPKC_PS1_GETOPLEN();
    MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClMath_QDash(iQSqr_iNShifted_iN_iT, len));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_QSquared, retValTemp);
}
