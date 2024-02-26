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
 * @file  mcuxClMath_Utils.c
 * @brief mcuxClMath: implementation of Math utility functions
 */


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClMath.h>

#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClMath_Internal_Utils.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_InitLocalUptrt)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_InitLocalUptrt(uint32_t i3_i2_i1_i0, uint32_t i7_i6_i5_i4, uint16_t *localPtrUptrt, uint8_t noOfIndices, const uint16_t **oldPtrUptrt)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_InitLocalUptrt);

    const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();

    uint32_t indices = i3_i2_i1_i0;

    /* Support up to 8 indices. */
    uint32_t noOfIndicesSupported = (8u < noOfIndices) ? 8u : noOfIndices;

    for (uint32_t i = 0; i < noOfIndicesSupported; i++)
    {
        /* Copy PKC offset to new UPTRT. */
        uint32_t index = indices & 0xFFu;
        localPtrUptrt[i] = pUptrt[index];

        if (3u == i)
        {
            indices = i7_i6_i5_i4;
        }
        else
        {
            indices >>= 8;
        }
    }

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_SETUPTRT(localPtrUptrt);

    *oldPtrUptrt = pUptrt;
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_InitLocalUptrt);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_LeadingZeros)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_LeadingZeros(uint8_t iX, uint32_t *pNumLeadingZeros)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_LeadingZeros);

    const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
    /* Assume pUptrt[iX] is exactly a multiple of MCUXCLPKC_WORDSIZE. */
    const uint32_t *pX = MCUXCLPKC_OFFSET2PTRWORD(pUptrt[iX]);

    uint32_t len = (uint32_t) MCUXCLPKC_PS1_GETOPLEN() / (sizeof(uint32_t));  /* Assume PS1 OPLEN is exactly a multiple of MCUXCLPKC_WORDSIZE. */
    uint32_t numLeadingZeros = 0u;

    do
    {
        len--;
        uint32_t xi = pX[len];
        if (0u != xi)
        {
            *pNumLeadingZeros = numLeadingZeros + mcuxClMath_CountLeadingZerosWord(xi);
            MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_LeadingZeros);
        }

        numLeadingZeros += ((sizeof(uint32_t)) * 8u);
    } while (0u < len);

    *pNumLeadingZeros = numLeadingZeros;
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_LeadingZeros);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_TrailingZeros)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClMath_TrailingZeros(uint8_t iX)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_TrailingZeros);

    const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
    /* Assume pUptrt[iX] is exactly a multiple of MCUXCLPKC_WORDSIZE. */
    const uint32_t *pX = MCUXCLPKC_OFFSET2PTRWORD(pUptrt[iX]);

    uint32_t opWords = (uint32_t) MCUXCLPKC_PS1_GETOPLEN() / (sizeof(uint32_t));  /* Assume PS1 OPLEN is exactly a multiple of MCUXCLPKC_WORDSIZE. */
    uint32_t index = 0u;
    uint32_t numTrailingZeroes = 0u;

    do
    {
        uint32_t xi = pX[index];
        if (0u != xi)
        {
            numTrailingZeroes = (index * (sizeof(uint32_t)) * 8u) + mcuxClMath_CountTrailingZeroesWord(xi);
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_TrailingZeros, numTrailingZeroes);
        }

        index++;
    } while (index < opWords);

    numTrailingZeroes = index * (sizeof(uint32_t)) * 8u;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_TrailingZeros, numTrailingZeroes);
}


/**
 * [DESIGN]
 * Since the max shifting amount of PKC shift operation is (8 * MCUXCLPKC_WORDSIZE - 1),
 * this function prepares the shifted modulus in the following steps:
 * (1) ignore zero most significant PKC word(s) (if any) of modulus (iN), and
 *     shift-left non-zero PKC word(s) of modulus and store result in most significant
 *     PKC word(s) of shifted modulus (iNShifted), such that there is
 *     no leading zero bit in shifted modulus;
 * (2) if there is any zero most significant PKC word(s) in modulus, then clean
 *     the same number of least significant PKC word(s) of shifted modulus.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ShiftModulus)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ShiftModulus(uint16_t iNShifted_iN)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ShiftModulus);

    /* Unpack indices. */
    uint8_t iN  = (uint8_t) (iNShifted_iN & 0xFFu);
    uint8_t iNS = (uint8_t) ((iNShifted_iN >> 8) & 0xFFu);

    /* Count the number of leading zeros of modulus n. */
    MCUXCLPKC_WAITFORFINISH();
    uint32_t leadingZeroBits;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(iN, &leadingZeroBits));
    uint32_t leadingZeroPkcWords_InBytes = leadingZeroBits / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;

    /* Set PS2 LEN, to exclude leading zero PKC word(s). */
    uint32_t ps1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    /* MCLEN on higher 16 bits is not used. */
    MCUXCLPKC_PS2_SETLENGTH_REG(ps1LenReg - leadingZeroPkcWords_InBytes);

    const uint16_t * pUptrt = MCUXCLPKC_GETUPTRT();
    uint16_t offsetN  = pUptrt[iN];
    uint16_t offsetNS = pUptrt[iNS];

    /* Copy and shift nonzero PKC word(s) of modulus. */
    uint32_t shiftAmount = leadingZeroBits & ((MCUXCLPKC_WORDSIZE * 8u) - 1u);
    MCUXCLPKC_PS2_SETMODE(MCUXCLPKC_OP_SHL);
    MCUXCLPKC_PS2_SETXY(0, offsetN);
    MCUXCLPKC_PS2_SETZR(shiftAmount, (offsetNS + leadingZeroPkcWords_InBytes) & 0xFFFFu);
    MCUXCLPKC_PS2_START_L0();

    /* Clear least significant PKC word(s) of iNShifted, if leadingZeroBits >= a PKC word. */
    if (0u != leadingZeroPkcWords_InBytes)
    {
        MCUXCLPKC_WAITFORREADY();
        /* MCLEN on higher 16 bits is not used. */
        MCUXCLPKC_PS2_SETLENGTH_REG(leadingZeroPkcWords_InBytes);
        MCUXCLPKC_FP_CALC_OP2_CONST(iNS, 0);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClMath_ShiftModulus,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        MCUX_CSSL_FP_CONDITIONAL_IMPL((0u != leadingZeroPkcWords_InBytes),
            MCUXCLPKC_FP_CALLED_CALC_OP2_CONST));
}
