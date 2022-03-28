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
 * @file  mcuxClMath_SecModExp.c
 * @brief mcuxClMath: secure modular exponentiation
 */

#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClPkc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClMath_Functions.h>
#include <mcuxClMath_Types.h>

#include <internal/mcuxClMath_Private_SecModExp.h>

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_SecModExp_SqrMultAws)

#define MCUXCLMATH_FP_SECMODEXP_SQRMULTAWS(pExp, byteLenExp, numSqr)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retVal, mcuxClMath_SecModExp_SqrMultAws(pExp, byteLenExp, numSqr));  \
        if (MCUXCLMATH_ERRORCODE_OK != retVal)  \
        {  \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_ERRORCODE_ERROR);  \
        }  \
    } while(false)

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_SecModExp_SqrMultAws)
static mcuxClMath_Status_Protected_t mcuxClMath_SecModExp_SqrMultAws(const uint32_t *pExp, uint32_t byteLenExp, uint32_t numSqr)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_SecModExp_SqrMultAws);

    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_Aws_Init,
                        mcuxClMath_Fup_Aws_Init_LEN);

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    const uint32_t *pOperands32 = (const uint32_t *) pOperands;

    uint16_t ofsN = pOperands[SECMODEXP_N];
    const uint32_t ofsA1_ofsA0 = pOperands32[SECMODEXP_A0 / 2u];
    uint32_t ofsAs = ofsA1_ofsA0;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETMODE(MCUXCLPKC_MC_MM);

    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop);
    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop_LoadExpWord);
    MCUX_CSSL_FP_LOOP_DECL(SquMulLoop_Square);

    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop, byteLenExp * 4u),
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop_LoadExpWord, byteLenExp / 4u),
        MCUX_CSSL_FP_LOOP_ITERATIONS(SquMulLoop_Square, byteLenExp * 4u * numSqr) );

    uint32_t expWord0 = 0u;
    uint32_t expWord1 = 0u;

    uint32_t ofsM3_ofsM1 = pOperands32[SECMODEXP_M1 / 2u];
    uint32_t ofsM2_ofsM0 = pOperands32[SECMODEXP_M0 / 2u];

    uint32_t ofsMsHi8 = (ofsM3_ofsM1 & 0xFF00FF00u) | ((ofsM2_ofsM0 & 0xFF00FF00u) >> 8u);

    uint32_t ofsMsLo8 = ((ofsM3_ofsM1 & 0x00FF00FFu) << 8u) | (ofsM2_ofsM0 & 0x00FF00FFu);

    ofsMsHi8 = (ofsMsHi8 << 4u) | (ofsMsHi8 >> 28u);
    ofsMsLo8 = (ofsMsLo8 << 4u) | (ofsMsLo8 >> 28u);

    uint32_t bitLenExp = byteLenExp * 8u;
    int32_t bitIndex = (int32_t) bitLenExp - 2;
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop,
                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord));

        if (0x1Eu == ((uint32_t) bitIndex & 0x1Fu))
        {
            MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop_LoadExpWord,
                                       MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord));

            uint32_t randomWordStack;
            MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord, mcuxClCss_Prng_GetRandomWord(&randomWordStack));
            if (MCUXCLCSS_STATUS_OK != ret_PRNG_randWord)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_ERRORCODE_ERROR);
            }
            expWord1 = randomWordStack;
            MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
            expWord0 = pExp[(uint32_t) bitIndex / 32u] ^ expWord1;
        }

        uint32_t iterSqr = numSqr;
        do
        {
            MCUX_CSSL_FP_LOOP_ITERATION(SquMulLoop_Square);

            ofsAs = (ofsAs << 16u) | (ofsAs >> 16u);

            uint32_t Sqr_ofsY_ofsX = (ofsAs & 0xFFFF0000u) | (ofsAs >> 16u);
            uint32_t Sqr_ofsR_ofsZ = (ofsAs << 16u)        | ofsN;
            MCUXCLPKC_WAITFORREADY();
            MCUXCLPKC_PS1_SETXY_REG(Sqr_ofsY_ofsX);
            MCUXCLPKC_PS1_SETZR_REG(Sqr_ofsR_ofsZ);
            MCUXCLPKC_PS1_START_L1();

            iterSqr--;
        } while (0u < iterSqr);

        uint32_t rndWordStack;
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord2, mcuxClCss_Prng_GetRandomWord(&rndWordStack));
        if (MCUXCLCSS_STATUS_OK != ret_PRNG_randWord2)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_ERRORCODE_ERROR);
        }
        uint32_t rndWord = rndWordStack;

        uint32_t ofsY_ofsX;
        MCUXCLMATH_SECMODEXP_SECUREOFFSETSELECT(expWord0, expWord1, ofsAs, ofsY_ofsX, rndWord, bitIndex, ofsMsHi8, ofsMsLo8);
        uint32_t ofsR_ofsZ = (ofsAs << 16u) | ofsN;

        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS1_SETXY_REG(ofsY_ofsX);
        MCUXCLPKC_PS1_SETZR_REG(ofsR_ofsZ);
        MCUXCLPKC_PS1_START_L1();

        bitIndex -= 2;
    } while (0 <= bitIndex);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp_SqrMultAws, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_SecModExp)
mcuxClMath_Status_Protected_t mcuxClMath_SecModExp(const uint8_t *pExp, uint32_t *pExpTemp, uint32_t byteLenExp, uint32_t iT3_iX_iT2_iT1, uint32_t iN_iTE_iT0_iR)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_SecModExp);

    uint32_t pOperands32[(SECMODEXP_UPTRT_SIZE + 1u) / 2u];

    uint16_t *pOperands = (uint16_t *) pOperands32;

    const uint16_t *backupPtrUptrt = MCUXCLMATH_FP_INITLOCALUPTRT(iT3_iX_iT2_iT1, iN_iTE_iT0_iR, pOperands, 8u);

    uint32_t ps1LenBackup = MCUXCLPKC_PS1_GETLENGTH_REG();

    uint32_t pkcLenExpPlus = MCUXCLPKC_ROUNDUP_SIZE(byteLenExp + 1u);
    MCUXCLPKC_PS1_SETLENGTH_REG(pkcLenExpPlus);
    MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(SECMODEXP_A0, pExp, SECMODEXP_A1, byteLenExp);

    uint8_t *pA1 = MCUXCLPKC_OFFSET2PTR(pOperands[SECMODEXP_A1]);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(pA1, pkcLenExpPlus));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_ERRORCODE_ERROR);
    }
    pA1[pkcLenExpPlus - 1u] &= 0x7Fu;

    MCUXCLPKC_FP_CALC_OP1_ADD(SECMODEXP_A0, SECMODEXP_A0, SECMODEXP_A1);

    uint32_t offsetTE = (uint32_t) pOperands[SECMODEXP_TE];
    uint32_t offsetR0 = offsetTE + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR1 = offsetR0 + MCUXCLPKC_WORDSIZE;
    uint32_t offsetR2 = offsetR1 + MCUXCLPKC_WORDSIZE;
    pOperands32[SECMODEXP_R0 / 2u] = (offsetR1 << 16u) + offsetR0;
    pOperands32[SECMODEXP_R2 / 2u] = offsetR2;

    uint8_t *pR0 = MCUXCLPKC_OFFSET2PTR(offsetR0);
    uint32_t *p32R0 = (uint32_t *) pR0;
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandomWord, mcuxClCss_Prng_GetRandomWord(&p32R0[0]));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandomWord)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_ERRORCODE_ERROR);
    }
    p32R0[0] |= 0x80000001u;
    p32R0[1] = 0u;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(MCUXCLPKC_WORDSIZE, MCUXCLPKC_WORDSIZE);

    MCUXCLPKC_FP_CALC_OP1_SHL(SECMODEXP_R1, SECMODEXP_R0, 32u);
    MCUXCLMATH_FP_NDASH(SECMODEXP_R0, SECMODEXP_M2);
    MCUXCLMATH_FP_QDASH(SECMODEXP_M0, SECMODEXP_R1, SECMODEXP_R0, SECMODEXP_M2, (uint16_t) pkcLenExpPlus);

    MCUXCLPKC_PS2_SETLENGTH(pkcLenExpPlus, MCUXCLPKC_WORDSIZE);

    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_EuclideanSplit_1,
                        mcuxClMath_Fup_EuclideanSplit_1_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH_REG(pkcLenExpPlus);

    MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_EuclideanSplit_2,
                        mcuxClMath_Fup_EuclideanSplit_2_LEN);

    MCUX_CSSL_FP_LOOP_DECL(ExactDivideLoop);

    uint32_t ofsV1_ofsV0 = pOperands32[SECMODEXP_A0 / 2u];
    uint32_t remainLength = pkcLenExpPlus;
    do
    {
        MCUX_CSSL_FP_LOOP_ITERATION(ExactDivideLoop,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );

        MCUXCLPKC_WAITFORREADY();
        MCUXCLPKC_PS2_SETLENGTH_REG(remainLength);
        pOperands32[SECMODEXP_V0 / 2u] = ofsV1_ofsV0;

        MCUXCLPKC_FP_CALCFUP(mcuxClMath_Fup_ExactDivideLoop,
                            mcuxClMath_Fup_ExactDivideLoop_LEN);

        ofsV1_ofsV0 += (((uint32_t) MCUXCLPKC_WORDSIZE << 16u) + MCUXCLPKC_WORDSIZE);
        remainLength -= MCUXCLPKC_WORDSIZE;
    } while(0u != remainLength);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH_REG(pkcLenExpPlus);
    MCUXCLPKC_FP_CALC_OP2_SUB(SECMODEXP_A0, SECMODEXP_A0, SECMODEXP_A1);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_ENABLEGF2();
    MCUXCLPKC_FP_CALC_OP1_MUL_GF2(SECMODEXP_R2, SECMODEXP_R0, SECMODEXP_R0);
    MCUXCLPKC_FP_CALC_OP1_SHL(SECMODEXP_TE, SECMODEXP_R2, 1u);
    MCUXCLPKC_FP_CALC_OP1_MUL_GF2(SECMODEXP_R2, SECMODEXP_R1, SECMODEXP_R1);
    MCUXCLPKC_FP_CALC_OP1_OR(SECMODEXP_TE, SECMODEXP_TE, SECMODEXP_R2);

    const uint8_t *pA0 = MCUXCLPKC_OFFSET2PTR(pOperands[SECMODEXP_A0]);
    uint32_t wordLenExp = (byteLenExp + 3u) & 0xFFFFFFFCu;
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    MCUX_CSSL_FP_FUNCTION_CALL(retCode_MemCopy, mcuxClMemory_copy((uint8_t *) pExpTemp, pA0, wordLenExp, wordLenExp));
    (void) retCode_MemCopy;

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_DISABLEGF2();
    MCUXCLPKC_PS1_SETLENGTH_REG(ps1LenBackup);

    MCUXCLPKC_FP_CALC_MC1_MM(SECMODEXP_A0, SECMODEXP_M1, SECMODEXP_M1, SECMODEXP_N);
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(SECMODEXP_M2, SECMODEXP_A0, 0u);
    MCUXCLMATH_FP_SECMODEXP_SQRMULTAWS(pExpTemp, wordLenExp, 2u);

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(SECMODEXP_M2, SECMODEXP_A0, 0u);

    uint32_t *p32TE = (uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[SECMODEXP_TE]);
    MCUXCLMATH_FP_SECMODEXP_SQRMULTAWS(p32TE, 8u, 1u);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(backupPtrUptrt);

    for (uint32_t i = 0u; i < ((SECMODEXP_UPTRT_SIZE + 1u) / 2u); i++)
    {
        pOperands32[i] = 0u;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_InitLocalUptrt),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SecureImportBigEndianToPkc),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandom),
        MCUXCLPKC_FP_CALLED_CALC_OP1_ADD,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Prng_GetRandomWord),
        MCUXCLPKC_FP_CALLED_CALC_OP1_SHL,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_LOOP_ITERATIONS(ExactDivideLoop, MCUXCLPKC_ROUNDUP_SIZE(byteLenExp + 1u) / MCUXCLPKC_WORDSIZE),
        MCUXCLPKC_FP_CALLED_CALC_OP2_SUB,

        MCUXCLPKC_FP_CALLED_CALC_OP1_MUL_GF2,
        MCUXCLPKC_FP_CALLED_CALC_OP1_SHL,
        MCUXCLPKC_FP_CALLED_CALC_OP1_MUL_GF2,
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),

        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp_SqrMultAws),

        MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp_SqrMultAws) );
}
