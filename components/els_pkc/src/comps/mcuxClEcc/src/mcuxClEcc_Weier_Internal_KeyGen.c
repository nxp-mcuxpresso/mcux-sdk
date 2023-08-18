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
 * @file  mcuxClEcc_Weier_Internal_KeyGen.c
 * @brief Weierstrass curve internal key generation
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxClEcc.h>
#include <mcuxClRandom.h>

#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_KeyGen_FUP.h>


/**
 * This function implements secure ECDSA private key / ephemeral key generation,
 * according to FIPS 186-4. It outputs multiplicative split d0 and d1 as well as d,
 * satisfying d0*d1 mod n = d = (c mod (n-1)) + 1, in which d is the private key
 * derived from a (bitLen(n)+64)-bit true (DRBG) random number c and d0 is a 64-bit
 * odd random number (with bits 0 and 63 set).
 *
 * Inputs:
 *   nByteLength: byte length of n (base point order).
 *
 * Inputs in pOperands[] and PKC workarea: N/A.
 *
 * Prerequisites:
 *   ps1Len = (operandSize, operandSize);
 *   curve order n in N, NDash of n in NFULL;
 *   no on-going calculation on N;
 *   buffers S1, S2 and S3 are with doubled-size (2*operandSize).
 *
 * Result in PKC workarea:
 *   buffers S0 and S1 contain multiplicative split private key d0 and d1 (operandSize);
 *   buffer S2 contains private key d2 (operandSize).
 *
 * Other modifications:
 *   buffers T0, XA, YA, ZA and Z are modified (as temp, buffer size);
 *   buffers S1, S2 and S3 are modified (as temp, double buffer size);
 *   offsets pOperands[VT] is modified.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Int_CoreKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_CoreKeyGen(mcuxClSession_Handle_t pSession,
                                                                      uint32_t nByteLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Int_CoreKeyGen,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST,
        MCUXCLPKC_FP_CALLED_CALC_OP2_CONST );

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    const uint32_t mcLen_opLen = MCUXCLPKC_PS1_GETLENGTH_REG();
    const uint32_t opLen = MCUXCLPKC_PS1_UNPACK_OPLEN(mcLen_opLen);

    /* Count leading zeros in most significant word of n. */
    MCUXCLCORE_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - PKC word is CPU word aligned.");
    const uint32_t *ptr32N = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();
    const uint32_t wordNumN = (nByteLength + (sizeof(uint32_t)) - 1u) / (sizeof(uint32_t));
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint32_t nMSWord = ptr32N[wordNumN - 1u];
    uint32_t nMSWord_LeadZeros = mcuxClMath_CountLeadingZerosWord(nMSWord);
    uint32_t bitLenN65 = (wordNumN * (sizeof(uint32_t)) * 8u) - nMSWord_LeadZeros + 65u;
    uint32_t pkcByteLenN65 = (bitLenN65 + (MCUXCLPKC_WORDSIZE * 8u) - 1u) / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;

    /* Clear buffer S1. */
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);

    /* Clear buffers S2 and S3, with OPLEN = pkcByteLenN65. */
//  MCUXCLPKC_WAITFORREADY();  <== not necessary when setting PS2 after submitting a PS1 computation via mcuxClPkc_Calc(...)
    MCUXCLPKC_PS2_SETLENGTH(0u, pkcByteLenN65);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_S2, 0u);
    MCUXCLPKC_FP_CALC_OP2_CONST(ECC_S3, 0u);


    /**********************************************************/
    /* Step 1: generate 64-bit odd random d0, (MSb/LSb set);  */
    /*         compute v = ModInv(d0) = d0^(-1) mod n.        */
    /**********************************************************/

    MCUXCLCORE_ANALYSIS_START_SUPPRESS_POINTER_CASTING("MISRA Ex. 9 to Rule 11.3 - PKC word is CPU word aligned.");
    uint32_t *ptr32S0 = (uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
    MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_POINTER_CASTING();

    /* Generate S0 = 64-bit random d0, with PRNG. */
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Prng1, mcuxClRandom_ncGenerate(pSession, (uint8_t*)&ptr32S0[0], (2U * sizeof(uint32_t))));
    if (MCUXCLRANDOM_STATUS_OK != ret_Prng1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) );
    }
    ptr32S0[0] |= 0x00000001u;  /* Set LSbit. */
    ptr32S0[1] |= 0x80000000u;  /* Set MSbit. */


    /**********************************************************/
    /* Step 2: generate (bitLenN+64)-bit DRBG random seed c.  */
    /* a. c is in a buffer of size, pkcSize(bitLenN+65).      */
    /**********************************************************/

    /* S2 = (wordNumN * 4 + 8)-byte random c, with DRBG. */
    uint8_t *ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);

    /* Derive the security strength required for the RNG from bitLenN / 2 and check whether it can be provided. */
#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
    MCUX_CSSL_FP_FUNCTION_CALL(ret_checkSecurityStrength, mcuxClRandom_checkSecurityStrength(pSession, MCUXCLECC_MIN((nByteLength * 8u) / 2u, 256u)));
    if (MCUXCLRANDOM_STATUS_OK != ret_checkSecurityStrength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength) );
    }
#endif

    const uint32_t keySeedLength = (wordNumN * (sizeof(uint32_t))) + 8u;
    MCUXCLECC_FP_RANDOM_HQRNG_PKCWA(mcuxClEcc_Int_CoreKeyGen, pSession, ptrS2, keySeedLength);


    /**********************************************************/
    /* Step 3: generate (bitLenN+64)-bit PRNG random number r;*/
    /*         compute c' = c + r.                            */
    /* a. OPLEN = pkcSize(bitLenN+65 bit).                    */
    /**********************************************************/

    /* S3 = (wordNumN * 4 + 8)-byte random r, with PRNG. */
    uint8_t *ptrS3 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom_r, mcuxClRandom_ncGenerate(pSession, ptrS3, (wordNumN * (sizeof(uint32_t))) + 8u));
    if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_GetRandom_r)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_STATUS_RNG_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength),
#endif
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate) );
    }

    /* Step 3: Truncate c and r to (bitLenN + 64)-bit, with OPLEN = pkcByteLenN65.                */
    /*         S2 = c' = c + r, the result fits in (bitLenN+65) bits, with OPLEN = pkcByteLenN65. */
    /*         ZA = d0, duplicate because ModInv(d0) will destroy input d0.                       */
    /* Step 4: Z = n-1. */
    pOperands[WEIER_VT] = (uint16_t) nMSWord_LeadZeros;
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34,
                        mcuxClEcc_FUP_Weier_CoreKeyGen_Steps34_LEN);

    /* T0 = v = ModInv(d0), with temp S1. */
    MCUXCLMATH_FP_MODINV(ECC_T0, WEIER_ZA, ECC_N, ECC_S1);

    /* Now, S0 = d0 (opLen), T0 = v (opLen), Z = n-1 (opLen), */
    /*      S2 = c' (pkcByteLenN65), S3 = r (pkcByteLenN65).  */


    /**********************************************************/
    /* Step 4: use ReduceModEven to compute:                  */
    /*         s = r mod (n-1);                               */
    /*         c" = c' mod (n-1) = (c+s) mod (n-1).           */
    /* a. ReduceModEven guarantees the result is < (n-1).     */
    /**********************************************************/

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(pkcByteLenN65, opLen);

    /* S1 = c" = ReduceModEven(c', n-1). */
    MCUXCLMATH_FP_REDUCEMODEVEN(ECC_S1, ECC_S2, WEIER_Z, WEIER_XA, ECC_S1, WEIER_YA, WEIER_ZA);
    /* S2 = s = ReduceModEven(r, n-1). */
    MCUXCLMATH_FP_REDUCEMODEVEN(ECC_S2, ECC_S3, WEIER_Z, WEIER_XA, ECC_S2, WEIER_YA, WEIER_ZA);


    /**********************************************************/
    /* Step 5: compute d' = (v*c") - (v*s) mod (v*(n-1)),     */
    /*                    = v * (c mod (n-1)).                */
    /* a. 3 plain multiplications (PM):                       */
    /*    MCLEN = OPLEN = opLen, RLEN = 2 * opLen;            */
    /* b. modular subtraction (MS): OPLEN = 2 * opLen.        */
    /**********************************************************/

    /**********************************************************/
    /* Step 6: compute d" = d' + v,                           */
    /*                    = v * ((c mod (n-1)) + 1) = v * d.  */
    /* a. plain addition (ADD): OPLEN = 2 * opLen;            */
    /* b. v shall be prepared in buffer of size, 2*opLen.     */
    /**********************************************************/

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH_REG(mcLen_opLen);  /* MCLEN = OPLEN = opLen. */
    MCUXCLPKC_PS2_SETLENGTH(0u, opLen * 2u);

    /* Step 5: S2 = d' = (v*c") - (v*s) mod (v*(n-1)); */
    /*         S3 = v * s, as another random number.   */
    /* Step 6: S2 = d" = d' + v.                       */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56,
                        mcuxClEcc_FUP_Weier_CoreKeyGen_Steps56_LEN);


    /**********************************************************/
    /* Step 7: compute d1 = d" mod n < n.                     */
    /* a. length of d" is (2 * opLen).                        */
    /**********************************************************/

    /**********************************************************/
    /* Step 8: compute d = d0 * d1 mod n < n.                 */
    /**********************************************************/

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH(opLen * 2u, opLen);

    /* Step 7: S1 = d1 = (d" mod n) < n. */
    /* Step 8: S2 = d0 * d1, SecureModMult with random S3 = v*s (only lower opLen). */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_CoreKeyGen_Steps78,
                        mcuxClEcc_FUP_Weier_CoreKeyGen_Steps78_LEN);


    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Int_CoreKeyGen, MCUXCLECC_STATUS_OK,
        /* Step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        /* Step 2 */
#ifdef MCUXCL_FEATURE_ECC_STRENGTH_CHECK
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_checkSecurityStrength),
#endif
        MCUXCLECC_FP_CALLED_RANDOM_HQRNG_PKCWA,
        /* Step 3 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        /* Step 4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ReduceModEven),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ReduceModEven),
        /* Steps 5/6 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        /* Steps 7/8 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
