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
 * @file  mcuxClMath_ReduceModEven.c
 * @brief mcuxClMath: implementation of the function mcuxClMath_ReduceModEven
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClPkc_Operations.h>


#define REDUCEMODEVEN_T0   0u
#define REDUCEMODEVEN_N    1u
#define REDUCEMODEVEN_X    2u  /* offsetX and offsetR shall be in the same CPU word. */
#define REDUCEMODEVEN_R    3u
#define REDUCEMODEVEN_T3   4u
#define REDUCEMODEVEN_T2   5u
#define REDUCEMODEVEN_T1   6u
#define REDUCEMODEVEN_T0H  7u
#define REDUCEMODEVEN_XH   8u  /* offsetXH and offsetRH shall be in the same CPU word. */
#define REDUCEMODEVEN_RH   9u
#define REDUCEMODEVEN_UPTRT_SIZE  10u


/**
 * [DESIGN]
 * Modular reduction with even modulus, r = x mod n, where n = n' * 2^k (n' is odd and nonzero).
 * Assume xH = x / 2^k, xL = x mod 2^k
 *   rL = r mod 2^k = (x mod n) mod 2^k = x mod 2^k = xL
 *   (r - rL) = (r - xL) \equiv (x - xL) mod (n'*2^k)
 *   rH = ((r - rL) / 2^k) \equiv ((x - xL) / 2^k) mod (n' * 2^k)
 *   rH = xH mod n'
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ReduceModEven)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ReduceModEven(uint32_t iR_iX_iN_iT0, uint32_t iT1_iT2_iT3)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ReduceModEven);

    uint32_t backupPs1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();

    /* Assume both OPLEN and MCLEN are initialized properly (must be a multiple of MCUXCLPKC_WORDSIZE). */
    uint32_t pkcByteLenN = MCUXCLPKC_PS1_UNPACK_OPLEN(backupPs1LenReg);
    uint32_t pkcByteLenX = MCUXCLPKC_PS1_UNPACK_MCLEN(backupPs1LenReg);

    /* Prepare local UPTRT. */
    uint32_t pOperands32[(REDUCEMODEVEN_UPTRT_SIZE + 1u) / 2u];
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 - Rule 11.3 - Cast to 16-bit pointer table");
    uint16_t *pOperands = (uint16_t *) pOperands32;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES();
    const uint16_t *backupPtrUptrt;
    /* mcuxClMath_InitLocalUptrt always returns _OK. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_InitLocalUptrt(iR_iX_iN_iT0, iT1_iT2_iT3, pOperands, 7u, &backupPtrUptrt));
    pOperands[REDUCEMODEVEN_T0H] = pOperands[REDUCEMODEVEN_T0] + MCUXCLPKC_WORDSIZE;


    /****************************************************************/
    /* Step 1: count k = trailing zeros of n                        */
    /****************************************************************/

    MCUXCLPKC_WAITFORFINISH();  /* Avoid any ongoing computation of N. */
    MCUX_CSSL_FP_FUNCTION_CALL(numTrailZeroBits, mcuxClMath_TrailingZeros(REDUCEMODEVEN_N));


    /****************************************************************/
    /* Step 2: T0H = n >> k = n', and T0L = NDash(T0H)              */
    /* a. OPLEN = pkcLenN                                           */
    /* b. operand T0 is of size, (pkcLenN + pkcWordSize)            */
    /*    T0L is the least significant pkcWord (for NDash), and     */
    /*    T0H is the higher significant pkcWord(s), size = pkcLenN  */
    /* c. use T3 as temp when calculating NDash, size = 2 pkcWords  */
    /****************************************************************/

    // (optional) we might create a new function to support both shift left and right, and use it also in mcuxClMath_ShiftModulus.
    // In ECC, n-1 (the curve order - 1) is usually with only few trailing zeros, we don't really need a highly optimized right shifting here.

    uint32_t shiftAmountThisIteration = (numTrailZeroBits >= (MCUXCLPKC_WORDSIZE * 8u)) ?
                                        ((MCUXCLPKC_WORDSIZE * 8u) - 1u) : numTrailZeroBits;
    uint32_t shiftAmountRemaining = numTrailZeroBits - shiftAmountThisIteration;
    MCUXCLPKC_FP_CALC_OP1_SHR(REDUCEMODEVEN_T0H, REDUCEMODEVEN_N, shiftAmountThisIteration);

    MCUX_CSSL_FP_LOOP_DECL(RightShift);
    while (0u != shiftAmountRemaining)
    {
        MCUX_CSSL_FP_LOOP_ITERATION(RightShift,
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR );

        shiftAmountThisIteration = (shiftAmountRemaining >= (MCUXCLPKC_WORDSIZE * 8u)) ?
                                   ((MCUXCLPKC_WORDSIZE * 8u) - 1u) : shiftAmountRemaining;
        shiftAmountRemaining -= shiftAmountThisIteration;
        MCUXCLPKC_FP_CALC_OP1_SHR(REDUCEMODEVEN_T0H, REDUCEMODEVEN_T0H, shiftAmountThisIteration);
    }

    MCUXCLMATH_FP_NDASH(REDUCEMODEVEN_T0H,  /* iN */
                       REDUCEMODEVEN_T3);  /* iT */


    /****************************************************************/
    /* Step 3: T1 = ShiftModulus(T0H)                               */
    /* a. OPLEN = pkcLenN' = pkcSize(bitLenN - k) <= pkcLenN        */
    /* b. result T1 is of size, pkcLenN'                            */
    /****************************************************************/

    /* Number of trailing zero pkcWord(s). */
    /* **Caution** This length might be 0 if the trailing zeros are less than a PKC word. */
    uint32_t pkcByteLenTZWords = numTrailZeroBits / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;
    /* pkcLenN' */
    uint32_t pkcByteLenNPrime = pkcByteLenN - pkcByteLenTZWords;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(pkcByteLenNPrime, pkcByteLenNPrime);  /* Also set MCLEN for the next step. */
    MCUXCLMATH_FP_SHIFTMODULUS(REDUCEMODEVEN_T1,    /* iNShifted */
                              REDUCEMODEVEN_T0H);  /* iN */


    /****************************************************************/
    /* Step 4: T2 = QDash(T0H), QDash_len = pkcSize(bitLenX - k)    */
    /* a. OPLEN = MCLEN = pkcLenN' = pkcSize(bitLenN - k)           */
    /* b. result T2 is of size, pkcLenN'                            */
    /* c. use T3 as temp, size = (pkcLenN + pkcWordSize)            */
    /****************************************************************/

    MCUXCLMATH_FP_QDASH(REDUCEMODEVEN_T2,   /* iQDash */
                       REDUCEMODEVEN_T1,   /* iNShifted */
                       REDUCEMODEVEN_T0H,  /* iN */
                       REDUCEMODEVEN_T3,   /* iT */
                       (uint16_t) (pkcByteLenX - pkcByteLenTZWords));  /* QDash_len */


    /****************************************************************/
    /* Step 5: X = X << ((-k) mod (8*pkcWordSize)), i.e.,           */
    /*         shift XH to be aligned with PKC word                 */
    /* a. clean extra pkcWord (at offsetX + pkcLenN) before shift   */
    /* b. OPLEN = pkcLenX + pkcWordSize                             */
    /* c. XL is the least significant pkcWord(s), size = pkcSize(k) */
    /*    XH is the higher significant pkcWord(s),                  */
    /*                                  size = pkcSize(bitLenX - k) */
    /****************************************************************/

    uint32_t shiftAmountNeg = (0u - numTrailZeroBits) & (((uint32_t) MCUXCLPKC_WORDSIZE * 8u) - 1u);
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH(0, MCUXCLPKC_WORDSIZE);

    /* Clean the extra pkcWord. */
    MCUXCLPKC_PS2_SETMODE(MCUXCLPKC_OP_CONST);  /* offsetX and offsetY are not used. */
    MCUXCLPKC_PS2_SETZR(0u, pOperands[REDUCEMODEVEN_X] + pkcByteLenX);
    MCUXCLPKC_PS2_START_L0();

    MCUXCLPKC_PS1_SETLENGTH(0, pkcByteLenX + MCUXCLPKC_WORDSIZE);
    MCUXCLPKC_FP_CALC_OP1_SHL(REDUCEMODEVEN_X, REDUCEMODEVEN_X, shiftAmountNeg);


    /****************************************************************/
    /* Step 6: T3 = MMul(XH, T2, T0H) = xH * 256^pkcLenN' mod n'    */
    /* a. MCLEN = pkcLenXH = pkcSize(bitLenX - k), OPLEN = pkcLenN' */
    /****************************************************************/

    /* pkcLenXH. */
    uint32_t pkcByteLenXH = pkcByteLenX - pkcByteLenTZWords;
    /* pkcLenXL = pkcSize(k) = pkcByteLenTZWords, if length of trailing zeros are exactly a multiple of PKC word; or */
    /*                       = (pkcByteLenTZWords + pkcWordSize), otherwise.   **Caution**                           */
    uint32_t pkcByteLenXL = (numTrailZeroBits + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;

    /* Set offsetXH = offsetX + pkcSize(k) and offsetRH = offsetR + pkcSize(k). */
    pOperands32[REDUCEMODEVEN_XH / 2u] = pOperands32[REDUCEMODEVEN_X / 2u] + ((pkcByteLenXL << 16) + pkcByteLenXL);

//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS2 after submitting a PS1 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS2_SETLENGTH(pkcByteLenXH, pkcByteLenNPrime);
    MCUXCLPKC_FP_CALC_MC2_MM(REDUCEMODEVEN_T3, REDUCEMODEVEN_XH, REDUCEMODEVEN_T2, REDUCEMODEVEN_T0H);


    /****************************************************************/
    /* Step 7: R = MRed(T3, T0H) \equiv xH (mod n') <= n'           */
    /* a. MCLEN = OPLEN = pkcLenN'                                  */
    /****************************************************************/

//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS1 after submitting a PS2 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS1_SETLENGTH(pkcByteLenNPrime, pkcByteLenNPrime);
    /* **Caution** Result space = pkcLenN' + pkcWordSize <= pkcLenN + pkcWordSize. */
    MCUXCLPKC_FP_CALC_MC1_MR(REDUCEMODEVEN_R, REDUCEMODEVEN_T3, REDUCEMODEVEN_T0H);


    /****************************************************************/
    /* Step 8: RH = MSub(R, T0H, T0H) = (xH mod n') < n'            */
    /* a. OPLEN = pkcLenN'                                          */
    /* b. RH is at offset pkcSize(k) from R                         */
    /****************************************************************/

    MCUXCLPKC_FP_CALC_MC1_MS(REDUCEMODEVEN_RH, REDUCEMODEVEN_R, REDUCEMODEVEN_T0H, REDUCEMODEVEN_T0H);


    /****************************************************************/
    /* Step 9: copy XL to RL                                        */
    /* a. OPLEN = pkcLenXL = pkcSize(k) >= pkcWordSize              */
    /*    if k = 0 (n is odd), OPLEN = 0 will trigger PKC alarm     */
    /****************************************************************/

//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS2 after submitting a PS1 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS2_SETLENGTH(0u, pkcByteLenXL);
    MCUXCLPKC_FP_CALC_OP2_OR_CONST(REDUCEMODEVEN_R, REDUCEMODEVEN_X, 0u);


    /****************************************************************/
    /* Step 10: R = R >> ((-k) mod (8*pkcWordSize))                 */
    /* a. OPLEN = pkcSize(k) + pkcSize(bitLenN - k)                 */
    /*          = pkcLenN or (pkcLenN + pkcWordSize)                */
    /****************************************************************/

//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS1 after submitting a PS2 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS1_SETLENGTH(0u, pkcByteLenNPrime + pkcByteLenXL);
    MCUXCLPKC_FP_CALC_OP1_SHR(REDUCEMODEVEN_R, REDUCEMODEVEN_R, shiftAmountNeg);


    /****************************************************************/
    /* Step 11: X = X >> ((-k) mod (8*pkcWordSize))                 */
    /* a. OPLEN = pkcLenX + pkcWordSize                             */
    /****************************************************************/

//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS2 after submitting a PS1 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS2_SETLENGTH(0u, pkcByteLenX + MCUXCLPKC_WORDSIZE);
    MCUXCLPKC_FP_CALC_OP2_SHR(REDUCEMODEVEN_X, REDUCEMODEVEN_X, shiftAmountNeg);

    /* Restore pUptrt and ps1 OPLEN/MCLEN. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);
    MCUXCLPKC_PS1_SETLENGTH_REG(backupPs1LenReg);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_ReduceModEven,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        /* S01 */ MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_TrailingZeros),
        /* S02 */ MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
                  MCUX_CSSL_FP_LOOP_ITERATIONS(RightShift, (numTrailZeroBits - 1u) / ((MCUXCLPKC_WORDSIZE * 8u) - 1u)),
                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        /* S03 */ MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        /* S04 */ MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash),
        /* S05 */ MCUXCLPKC_FP_CALLED_CALC_OP1_SHL,
        /* S06 */ MCUXCLPKC_FP_CALLED_CALC_MC2_MM,
        /* S07 */ MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        /* S08 */ MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        /* S09 */ MCUXCLPKC_FP_CALLED_CALC_OP2_OR_CONST,
        /* S10 */ MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
        /* S11 */ MCUXCLPKC_FP_CALLED_CALC_OP2_SHR );
}
