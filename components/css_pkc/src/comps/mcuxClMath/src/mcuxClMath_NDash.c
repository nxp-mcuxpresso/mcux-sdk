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

/** @file  mcuxClMath_NDash.c
 *  @brief mcuxClMath: implementation of the function mcuxClMath_NDash
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>

#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClMath_FUP_programs.h>


/* Calculates (-n)^(-1) mod 256^("PKC wordsize"):
 * Suppose xi \equiv (-n)^(-1) (mod 2^(2^i)), and x0 \equiv 1 (mod 2).
 * 1 + xi * n \equiv 0 (mod 2^(2^i)) implies (1 + xi * n)^2 = 1 + (2*xi + xi^2 *n) * n \equiv 0 (mod 2^(2^(i+1))).
 * => x_{i+1} \equiv 2*xi + xi^2 * n = (xi * n + 2) * xi (mod 2^(2^(i+1))).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_NDash)
mcuxClMath_Status_Protected_t mcuxClMath_NDash(uint16_t iN_iT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_NDash);

    /* Prepare local UPTRT. */
    uint16_t pOperands[NDASH_UPTRT_SIZE];
    const uint16_t *backupPtrUptrt = MCUXCLMATH_FP_INITLOCALUPTRT((uint32_t) iN_iT, 0, pOperands, 2u);

    /* WAITFORREADY in mcuxClMath_InitLocalUptrt(...). */
    uint16_t offsetNDash = pOperands[NDASH_N] - MCUXCLPKC_WORDSIZE;
    pOperands[NDASH_NDASH] = offsetNDash;
    pOperands[NDASH_C2] = 2u;

    MCUXCLPKC_PS2_SETLENGTH(0, MCUXCLPKC_WORDSIZE);

    /* MISRA Ex. 9 - Rule 11.3 - PKC buffer is CPU word aligned. */
    volatile uint32_t *pNDash = (volatile uint32_t *) MCUXCLPKC_OFFSET2PTR(offsetNDash);

    /* x1 \equiv 1 (mod 4), if n mod 4 = 3; */
    /*    \equiv 3 (mod 4), if n mod 4 = 1. */
    MCUXCLPKC_WAITFORFINISH();
    uint32_t N0 = pNDash[MCUXCLPKC_WORDSIZE / (sizeof(uint32_t))];  /* Assume PKC wordsize is a multiple of CPU wordsize. */
    pNDash[0] = 0u - N0;

    for (uint32_t bit = 2u; bit < (MCUXCLPKC_WORDSIZE * 8u); bit <<= 1)
    {
        MCUXCLPKC_FP_CALCFUP(mcuxClMath_NDash_Fup, mcuxClMath_NDash_Fup_LEN);
    }

#if (8u != MCUXCLPKC_WORDSIZE)
#error update log2PkcWordsize in flow protection
#endif

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_NDash, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        /* hard-coded (log2PkcWordsize + 3) - 1 = 5 iterations of the loop. */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* iteration with bit = 2 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* bit = 4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* bit = 8 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),   /* bit = 16 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));  /* bit = 32 */
}
