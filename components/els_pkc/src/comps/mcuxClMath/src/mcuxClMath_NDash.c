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
 * @file  mcuxClMath_NDash.c
 * @brief mcuxClMath: implementation of the function mcuxClMath_NDash
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_Internal_NDash.h>
#include <internal/mcuxClMath_NDash_FUP.h>


/**
 * [Design]
 * This function calculates NDash = (-n)^(-1) mod 256^(MCUXCLPKC_WORDSIZE),
 * where n is an odd number, by using mathematical induction:
 *
 * Let x0 \equiv 1 (mod 2), and suppose xi \equiv (-n)^(-1) (mod 2^(2^i)).
 * Since 1 + xi * n \equiv 0 (mod 2^(2^i)), so
 * (1 + xi * n)^2 = 1 + (2*xi + xi^2 *n) * n \equiv 0 (mod 2^(2^(i+1))), and
 * x_{i+1} \equiv 2*xi + xi^2 * n = (xi * n + 2) * xi (mod 2^(2^(i+1))).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_NDash)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_NDash(uint16_t iN_iT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_NDash);

    /* Prepare local UPTRT. */
    uint16_t pOperands[NDASH_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt;
    /* mcuxClMath_InitLocalUptrt always returns _OK. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_InitLocalUptrt((uint32_t) iN_iT, 0, pOperands, 2u, &backupPtrUptrt));

    /* WAITFORREADY in mcuxClMath_InitLocalUptrt(...). */
    uint16_t offsetNDash = pOperands[NDASH_N] - MCUXCLPKC_WORDSIZE;
    pOperands[NDASH_NDASH] = offsetNDash;
    pOperands[NDASH_CONST2] = 2u;
    pOperands[NDASH_CONST0] = 0u;

    MCUXCLPKC_PS2_SETLENGTH(0, MCUXCLPKC_WORDSIZE);

    /* x1 \equiv 1 (mod 4), if n mod 4 = 3; */
    /*    \equiv 3 (mod 4), if n mod 4 = 1. */
    MCUXCLPKC_FP_CALC_OP2_NEG(NDASH_NDASH, NDASH_N);

    for (uint32_t bit = 2u; bit < (MCUXCLPKC_WORDSIZE * 8u); bit <<= 1)
    {
        MCUXCLPKC_FP_CALCFUP(mcuxClMath_NDash_Fup, mcuxClMath_NDash_Fup_LEN);
    }

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);


#if (16u == MCUXCLPKC_WORDSIZE)
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_NDash,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUXCLPKC_FP_CALLED_CALC_OP2_NEG,
        /* hard-coded (log2PkcWordsize + 3) - 1 = 5 iterations of the loop. */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x2 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x3 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x5 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x6 = ... (mod 2^(2^6)). */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)    /* calculate x7 = ... (mod 2^(2^7)). */
        );
#else
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_NDash,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUXCLPKC_FP_CALLED_CALC_OP2_NEG,
        /* hard-coded (log2PkcWordsize + 3) - 1 = 5 iterations of the loop. */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x2 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x3 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* calculate x5 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)    /* calculate x6 = ... (mod 2^(2^6)). */
        );
#endif


}
