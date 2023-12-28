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
 * @file  mcuxClMath_SecModExp.c
 * @brief mcuxClMath: secure modular exponentiation
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClRandom.h>
#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClMath_Internal_SecModExp.h>
#include <internal/mcuxClMath_SecModExp_FUP.h>

/**
 * [DESIGN]
 * Internal square-and-multiply-always modular exponentiation function, which supports:
 * (1) when numSqr = 1, double-exponentiation (Shamir's trick), m1^e1 * m2^e2.
 *     m1 and m2 need to be stored in PKC operands M1 and M2, and
 *     exponent e1 and e2 should be interleaved.
 * (2) when numSqr = 2, fixed 2-bit window algorithm, x^e.
 *     x and x^2 need to be stored in PKC operands M1 and M2.
 *
 * CAUTION: expByteLength should be a multiple of CPU word length.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_SecModExp_SqrMultAws)
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_SecModExp_SqrMultAws)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMath_Status_t)
mcuxClMath_SecModExp_SqrMultAws(mcuxClSession_Handle_t session, const uint32_t *pExp, uint32_t expByteLength, uint32_t numSqr, uint32_t secOption)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_SecModExp_SqrMultAws);

    /* Prepare m3 = m1 * m2 mod n, m0 = 1, a0 = 1. */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_Aws_Init,
                        mcuxClMath_Fup_Aws_Init_LEN);

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 - Rule 11.3 - UPTR table is 32-bit aligned in SecModExp")
    MCUX_CSSL_ANALYSIS_COVERITY_START_DEVIATE(CERT_EXP36_C, "UPTR table is 32-bit aligned in SecModExp")
    const uint32_t *pOperands32 = (const uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_DEVIATE(CERT_EXP36_C)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

    /* A0 and A1 will be the intermediate result A(t) and temp buffer A(1-t). */
    /* In the beginning, A0 is the intermediate result, i.e., t = 0. */
    uint16_t ofsN = pOperands[SECMODEXP_N];
    const uint32_t ofsA1_ofsA0 = pOperands32[SECMODEXP_A0 / 2u];  /* hi16 = ofsA1, lo16 = ofsA0. */
    uint32_t ofsAs = ofsA1_ofsA0;

    /* Prepare modular multiplications in the loop */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETMODE(MCUXCLPKC_MC_MM);

    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop);
    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop_LoadExpWord);
    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop_Square);
    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop_OperandRerandomization);

    /* Balance FP in advance to avoid keeping expByteLength in reg/stack. */
    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop, expByteLength * 4u),
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop_LoadExpWord, expByteLength / 4u),
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop_Square, expByteLength * 4u * numSqr),
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLMATH_SECMODEXP_OPTION_DIS_RERAND != secOption), MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop_OperandRerandomization, 32u)));

    /* Assume expByteLength is a multiple of CPU word size (4), otherwise, some higher bits of exponent will be ignored. */
    uint32_t expWord0 = 0u;
    uint32_t expWord1 = 0u;

    uint32_t rnd64_0;
    uint32_t rnd64_1;

    uint32_t ofsM3_ofsM1 = pOperands32[SECMODEXP_M1 / 2u];  /* (offsetM3, offsetM1) = (M3H, M3L, M1H, M1L) */
    uint32_t ofsM2_ofsM0 = pOperands32[SECMODEXP_M0 / 2u];  /* (offsetM2, offsetM0) = (M2H, M2L, M0H, M0L) */
    /* Prepare (M3H, M2H, M1H, M0H), where e.g., M3H is the higher 8 bits of the 16-bit offset M3. */
    uint32_t ofsMsHi8 = (ofsM3_ofsM1 & 0xFF00FF00u) | ((ofsM2_ofsM0 & 0xFF00FF00u) >> 8u);
    /* Prepare (M3L, M2L, M1L, M0L), where e.g., M3L is the lower 8 bits of the 16-bit offset M3. */
    uint32_t ofsMsLo8 = ((ofsM3_ofsM1 & 0x00FF00FFu) << 8u) | (ofsM2_ofsM0 & 0x00FF00FFu);

    /* Rotate left 4-bit, such that the rotation amount in SecureOffsetSelect is always nonzero (4/12/20/28). */
    ofsMsHi8 = (ofsMsHi8 << 4u) | (ofsMsHi8 >> 28u);
    ofsMsLo8 = (ofsMsLo8 << 4u) | (ofsMsLo8 >> 28u);


    /* Prepare pointer to the random buffers (R0 || R1 || R2 || R2H), which will be used for the operand re-randomization. */
    uint32_t *p32R0 = MCUXCLPKC_OFFSET2PTRWORD(pOperands[SECMODEXP_R0]);  /* operand R0 shall be PKC word aligned. */

    /* Scan from most to least significant bits of exponent,        */
    /* which is stored in little-endian in CPU-word aligned buffer. */
    uint32_t bitLenExp = expByteLength * 8u;
    int32_t bitIndex = (int32_t) bitLenExp - 2;
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop,
                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));

        /* Load next CPU word of exponent. */
        if (0x1Eu == ((uint32_t) bitIndex & 0x1Fu))
        {
            MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop_LoadExpWord,
                                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));

            /* Read one CPU word of exponent and mask it. */
            uint32_t randomWordStack;
            MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate1, mcuxClRandom_ncGenerate(session, (uint8_t *) &randomWordStack, sizeof(uint32_t)));
            if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate1)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_STATUS_ERROR);
            }
            expWord1 = randomWordStack;  /* avoid compiler writing randomWord back to stack */
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy

            MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "bitIndex < 8*expByteLength, and expByteLength is bounded by memory size (and smaller than 2^16).")
            expWord0 = pExp[(uint32_t) bitIndex / 32u] ^ expWord1;
            MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)
        }

        /* Re-randomize base operands, for the first 64 bits of exponent processed */
        /* TODO CLNS-7824: analyze how to use the SecModExp in RsaKg MillerRabinTest, and remove secOption */
        if ((((int32_t) bitLenExp - 64) <= bitIndex) && (MCUXCLMATH_SECMODEXP_OPTION_DIS_RERAND != secOption))
        {
          MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop_OperandRerandomization,
                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                     MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));

          /* Generate random numbers in R0, R1, R2 and R2H.
           * In order to optimize calls to the PRNG function, one single random number, of 128 bits, is generated over R0 and R1, and split with the CPU across the four buffers.
           * In order to avoid overflows when adding in-place multiples of the modulus over 2*32=2^6 iterations in total, 26-bit random numbers are used.
           * The upper words of buffers R2 and R2H have already been cleared.*/
          MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
          MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate2, mcuxClRandom_ncGenerate(session, (uint8_t *) p32R0, 16u));
          if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate2)
          {
              MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_STATUS_ERROR);
          }

          p32R0[4u] = p32R0[1u] >> 6u;  /* Copy random from R0[63:32] to R2, and keep only 26 bits */
          p32R0[6u] = p32R0[3u] >> 6u;  /* Copy random from R1[63:32] to R2H, and keep only 26 bits */
          p32R0[0u] >>= 6u;  /* Clear R0[63:26] */
          p32R0[1u] = 0x00000000u;
          p32R0[2u] >>= 6u;  /* Clear R1[63:26] */
          p32R0[3u] = 0x00000000u;

          /* Add random multiples of the modulus, in-place, to the base operands M0, M1, M2 and M3. */
          MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_Aws_Rerand,
                              mcuxClMath_Fup_Aws_Rerand_LEN);
        }

        uint32_t iterSqr = numSqr;
        do
        {
            MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop_Square);

            /* Swap intermediate result A(t) and temp buffer A(1-t), i.e., let t := 1-t. */
            ofsAs = (ofsAs << 16u) | (ofsAs >> 16u);  /* hi16 = ofsA(1-t), lo16 = ofsA(t). */

            /* Calculate A(t) = A(1-t) * A(1-t) mod N. */
            uint32_t Sqr_ofsY_ofsX = (ofsAs & 0xFFFF0000u) | (ofsAs >> 16u);
            uint32_t Sqr_ofsR_ofsZ = (ofsAs << 16u)        | ofsN;
            MCUXCLPKC_WAITFORREADY();
            MCUXCLPKC_PS1_SETXY_REG(Sqr_ofsY_ofsX);
            MCUXCLPKC_PS1_SETZR_REG(Sqr_ofsR_ofsZ);
            MCUXCLPKC_PS1_START_L1();

            iterSqr--;
        } while (0u < iterSqr);

        /* Generate a fresh random word for secure offset selection.*/
        uint32_t rndWordStack;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate3, mcuxClRandom_ncGenerate(session, (uint8_t *) &rndWordStack, sizeof(uint32_t)));
        if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate3)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_STATUS_ERROR);
        }
        uint32_t rndWord = rndWordStack;                    /* avoid compiler writing rndWord back to stack */

        /* Modular Multiplication: X    * Y      mod Z =: R,    */
        /* for t = 0 or 1,         M[i] * A(1-t) mod N =: A(t). */

        /* Securely select ofsX, set ofsY_ofsX, and also swap A0 and A1 (i.e., let t := 1-t). */
        uint32_t ofsY_ofsX;
        uint32_t maskVal;
        MCUXCLMATH_SECMODEXP_SECUREOFFSETSELECT(expWord0, expWord1, ofsAs, ofsY_ofsX, rndWord, (uint32_t)bitIndex, ofsMsHi8, ofsMsLo8, rnd64_0, rnd64_1, maskVal);
        uint32_t ofsR_ofsZ = (ofsAs << 16u) | ofsN;
        MCUXCLPKC_WAITFORREADY();  
        MCUXCLMATH_SECMODEXP_WRITEOFFSET(ofsY_ofsX,maskVal);
        MCUXCLPKC_PS1_SETZR_REG(ofsR_ofsZ);
        MCUXCLPKC_PS1_START_L1();

        bitIndex -= 2;
    } while (0 <= bitIndex);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_SecModExp)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMath_Status_t) mcuxClMath_SecModExp(
    mcuxClSession_Handle_t session, const uint8_t *pExp, uint32_t *pExpTemp, uint32_t expByteLength, uint32_t iT3_iX_iT2_iT1, uint32_t iN_iTE_iT0_iR, uint32_t secOption)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_SecModExp);

    /* Create local UPTR table. */
    uint32_t pOperands32[(SECMODEXP_UPTRT_SIZE + 1u) / 2u];
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 - Rule 11.3 - Cast to 16-bit pointer table")
    uint16_t *pOperands = (uint16_t *) pOperands32;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint16_t *backupPtrUptrt;
    /* Mapping to internal indices:                         M3  M1 M2  M0   N  TE  A1  A0 */
    /* mcuxClMath_InitLocalUptrt always returns _OK. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_InitLocalUptrt(iT3_iX_iT2_iT1, iN_iTE_iT0_iR, pOperands, 8u, &backupPtrUptrt));

    uint32_t ps1LenBackup = MCUXCLPKC_PS1_GETLENGTH_REG();

    /* Import exponent (big-endian to little-endian). */
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(CERT_INT30_C, "pkcLenExpPlus in range [expByteLength+1, expByteLength+MCUXCLPKC_WORDSIZE].")
    uint32_t pkcLenExpPlus = MCUXCLPKC_ROUNDUP_SIZE(expByteLength + 1u);
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(CERT_INT30_C)
    MCUXCLPKC_PS1_SETLENGTH_REG(pkcLenExpPlus);  /* MCLEN on higher 16 bits is not used. */

    MCUX_CSSL_FP_FUNCTION_CALL(ret_SecImport, mcuxClPkc_SecureImportBigEndianToPkc(session, MCUXCLPKC_PACKARGS2(SECMODEXP_A0, SECMODEXP_A1), pExp, expByteLength));
    if (MCUXCLPKC_STATUS_OK != ret_SecImport)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }

    /******************************************************/
    /* Euclidean exponent split: exp = b * q + r,         */
    /* where b is 64-bit random (MSb and LSb set)         */
    /******************************************************/

    /* Generate random expB and blind exponent, expA = exp + expB. */
    uint8_t *pA1 = MCUXCLPKC_OFFSET2PTR(pOperands[SECMODEXP_A1]);
    /* A1 = expB < (256^pkcLenExpPlus)/2. */
    MCUX_CSSL_ANALYSIS_COVERITY_START_FALSE_POSITIVE(INTEGER_OVERFLOW, "pkcLenExpPlus in range [expByteLength+1, expByteLength+MCUXCLPKC_WORDSIZE].")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate1, mcuxClRandom_ncGenerate(session, pA1, pkcLenExpPlus));
    if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }
    pA1[pkcLenExpPlus - 1u] &= 0x7Fu;
    MCUX_CSSL_ANALYSIS_COVERITY_STOP_FALSE_POSITIVE(INTEGER_OVERFLOW)

    /* A0 = expA = exp + expB < 256^pkcLenExpPlus. */
    MCUXCLPKC_FP_CALC_OP1_ADD(SECMODEXP_A0, SECMODEXP_A0, SECMODEXP_A1);

    /* Partition buffer TE to "TE || NDASH || R0 || R1 || (R2L, R2H)". */
    uint32_t offsetTE = (uint32_t) pOperands[SECMODEXP_TE];
    uint32_t offsetNDASH = offsetTE + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR0 = offsetNDASH + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR1 = offsetR0 + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR2 = offsetR1 + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR2H = offsetR2 + MCUXCLPKC_WORDSIZE;
    pOperands32[SECMODEXP_NDASH / 2u] = (offsetR0 << 16u) + offsetNDASH;
    pOperands32[SECMODEXP_R1 / 2u] = (offsetR2 << 16u) + offsetR1;
    pOperands32[SECMODEXP_R2H / 2u] = offsetR2H;  /* Also initialize SECMODEXP_ZERO */
    pOperands[SECMODEXP_ONE] = 0x0001u;

    /* Generate a 64-bit random b with both MSbit and LSbit set. */
    uint32_t *p32R0 = MCUXCLPKC_OFFSET2PTRWORD((uint16_t) offsetR0);  /* opernad R0 shall be PKC word aligned. */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate2, mcuxClRandom_ncGenerate(session, (uint8_t *) p32R0, 8u));
    if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }
    p32R0[0] |= 0x00000001u;
    p32R0[1] |= 0x80000000u;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(MCUXCLPKC_WORDSIZE, MCUXCLPKC_WORDSIZE);

    /* Calculate NDash and QDash of b.
     * As the MSB of b is set, shifting the modulus is not necessary. */
    MCUXCLMATH_FP_NDASH(SECMODEXP_R0, SECMODEXP_M2);
    MCUXCLMATH_FP_QDASH(SECMODEXP_M0, SECMODEXP_R0, SECMODEXP_R0, SECMODEXP_M3, (uint16_t) pkcLenExpPlus);

//  MCUXCLPKC_WAITFORREADY();  <== there is WAITFORREADY in QDASH
    MCUXCLPKC_PS2_SETLENGTH(pkcLenExpPlus, MCUXCLPKC_WORDSIZE);

    /* M2 = expB mod b, R1 = r = exp mod b. */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_EuclideanSplit_1,
                        mcuxClMath_Fup_EuclideanSplit_1_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH_REG(pkcLenExpPlus);  /* MCLEN on higher 16 bits is not used. */

    /* A0 = -(expA - (expB mod b) - ((expA - expB) mod b)); */
    /* A1 = -(expB - (expB mod b)).                         */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_EuclideanSplit_2,
                        mcuxClMath_Fup_EuclideanSplit_2_LEN);

    MCUX_CSSL_FP_LOOP_DECL(ExactDivideLoop);

    /* Calculate exact division:                                 */
    /*   A0 = (expA - (expB mod b) - ((expA - expB) mod b)) / b; */
    /*   A1 = (expB - (expB mod b)) / b.                         */
    uint32_t ofsV1_ofsV0 = pOperands32[SECMODEXP_A0 / 2u];
    uint32_t remainLength = pkcLenExpPlus;
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(ExactDivideLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS2_SETLENGTH_REG(remainLength);  /* MCLEN on higher 16 bits is not used. */
        pOperands32[SECMODEXP_V0 / 2u] = ofsV1_ofsV0;

        MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_ExactDivideLoop,
                            mcuxClMath_Fup_ExactDivideLoop_LEN);

        ofsV1_ofsV0 += (((uint32_t) MCUXCLPKC_WORDSIZE << 16u) + MCUXCLPKC_WORDSIZE);
        remainLength -= MCUXCLPKC_WORDSIZE;
    } while(0u != remainLength);

    /* Set PS2_LEN = pkcLenExpPlus to calculate q */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH_REG(pkcLenExpPlus);  /* MCLEN on higher 16 bits is not used. */

    /* FUP program:
     * 1)  A0 = q = A0 - A1 = ((expA - expB) - ((expA - expB) mod b)) / b = (exp - (exp mod b)) / b.
     * 2)  Interleave R0 = b and R1 = r, into (TE || NDASH). */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_CalcQAndInterleave,
                        mcuxClMath_Fup_CalcQAndInterleave_LEN);

    /* Export A0 = q. */
    const uint8_t *pA0 = MCUXCLPKC_OFFSET2PTR(pOperands[SECMODEXP_A0]);
    uint32_t wordLenExp = (expByteLength + 3u) & 0xFFFFFFFCu;
    MCUXCLPKC_WAITFORFINISH();
    MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t *) pExpTemp, pA0, wordLenExp);


    /* Calculate QSquared, to prepare for the upcoming calculation of M0 = 1 in MR, M0 < N */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenBackup);
    MCUXCLMATH_FP_SHIFTMODULUS(SECMODEXP_A0, SECMODEXP_N);
    MCUXCLMATH_FP_QSQUARED(SECMODEXP_A1, SECMODEXP_A0, SECMODEXP_N, SECMODEXP_M3);

    /* Prepare M2 = m^2.
     * This operation is randomized, by adding a random 16-bit multiple of the modulus to m before squaring: M2 = m + (r16 * N). */
    uint8_t *pR1 = MCUXCLPKC_OFFSET2PTR((uint16_t) offsetR1);
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate3, mcuxClRandom_ncGenerate(session, pR1, 4u));
    if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate3)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }
    /* Clear upper word and process lower word of R1 */
    p32R0[3u] = 0x00000000u;
    if(MCUXCLMATH_SECMODEXP_OPTION_DIS_RERAND == secOption)
    {
      /* TODO CLNS-7824: analyze how to use the SecModExp in RsaKg MillerRabinTest, and remove secOption to always re-randomize */
      p32R0[2u] = 0x00000000u;
    }
    else
    {
      p32R0[2u] >>= 16u;
    }

    /* Prepare base numbers for the first exponentiation:
     * 1)  Prepare M2 = m^2.
     * 2)  Prepare M0 = 1 in MR, M0 < N. */
    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_PrepareFirstExp,
                        mcuxClMath_Fup_PrepareFirstExp_LEN);

    /* Clear upper words of R2 and R2H to prepare operand re-randomization inside mcuxClMath_SecModExp_SqrMultAws. */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    p32R0[5u] = 0x00000000u;  /* Clear upper word of R2 */
    p32R0[7u] = 0x00000000u;  /* Clear upper word of R2H */

    /* Calculate 2-bit window exponentiation, A0 = m0 = m^q. */
    MCUX_CSSL_FP_FUNCTION_CALL(retSecModExp0, mcuxClMath_SecModExp_SqrMultAws(session, pExpTemp, wordLenExp, 2u, secOption));
    if (MCUXCLMATH_STATUS_OK != retSecModExp0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }

    /* Calculate double exponentiation, A0 = result = m^r * m0^b, with interleaved r and b. */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(SECMODEXP_M2, SECMODEXP_A0, 0u);
    const uint32_t *p32TE = MCUXCLPKC_OFFSET2PTRWORD(pOperands[SECMODEXP_TE]);  /* operand TE shall be PKC word aligned. */
    MCUX_CSSL_FP_FUNCTION_CALL(retSecModExp1, mcuxClMath_SecModExp_SqrMultAws(session, p32TE, 16u, 1u, secOption));
    if (MCUXCLMATH_STATUS_OK != retSecModExp1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_ERROR);
    }

    /* Restore pUptrt. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);

    /* Clear the local UPTR table on stack. */
    for (uint32_t i = 0u; i < ((SECMODEXP_UPTRT_SIZE + 1u) / 2u); i++)
    {
        pOperands32[i] = 0u;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),
        /* Euclidean exponent splitting */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUXCLPKC_FP_CALLED_CALC_OP1_ADD,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_LOOP_ITERATIONS(ExactDivideLoop, MCUXCLPKC_ROUNDUP_SIZE(expByteLength + 1u) / MCUXCLPKC_WORDSIZE),
        /* Calculate q, interleave b and r, and export q */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        /* Exponentiation 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp_SqrMultAws),
        /* Exponentiation 2 */
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp_SqrMultAws) );
}
