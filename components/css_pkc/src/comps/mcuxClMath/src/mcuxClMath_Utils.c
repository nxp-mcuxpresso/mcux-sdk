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

/** @file  mcuxClMath_Utils.c
 *  @brief mcuxClMath: implementation of Math utility functions
 */


#include <stdint.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClMath.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_InitLocalUptrt)
mcuxClMath_Status_Protected_t mcuxClMath_InitLocalUptrt(uint32_t i3_i2_i1_i0, uint32_t i7_i6_i5_i4, uint16_t *localPtrUptrt, uint8_t noOfIndices, const uint16_t **oldPtrUptrt)
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
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_InitLocalUptrt, MCUXCLMATH_ERRORCODE_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_LeadingZeros)
mcuxClMath_Status_Protected_t mcuxClMath_LeadingZeros(uint8_t iX, uint32_t *nLeadingZeros)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_LeadingZeros);

    const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
    uint32_t offsetX = (uint32_t) pUptrt[iX];  /* Assume offsetX is initialized properly (must be a multiple of PKC wordsize). */
    const uint32_t *pX = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(offsetX);  /* PKC word is CPU word aligned. */

    uint32_t len = (uint32_t) MCUXCLPKC_PS1_GETOPLEN() / (sizeof(uint32_t));  /* Assume OPLEN is initialized properly (must be a multiple of PKC wordsize). */
    uint32_t noOfLeadingZeros = 0u;

    do
    {
        len--;
        uint32_t xi = pX[len];
        if (0u != xi)
        {
            *nLeadingZeros = noOfLeadingZeros + __CLZ(xi);
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_LeadingZeros, MCUXCLMATH_ERRORCODE_OK);
        }

        noOfLeadingZeros += ((sizeof(uint32_t)) * 8u);
    } while (0u < len);

    *nLeadingZeros = noOfLeadingZeros;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_LeadingZeros, MCUXCLMATH_ERRORCODE_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_TrailingZeros)
mcuxClMath_Status_Protected_t mcuxClMath_TrailingZeros(uint8_t iX, uint32_t *nTrailingZeros)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_TrailingZeros);

    const uint16_t *pUptrt = MCUXCLPKC_GETUPTRT();
    uint32_t offsetX = (uint32_t) pUptrt[iX];  /* Assume offsetX is initialized properly (must be a multiple of PKC wordsize). */
    const uint32_t *pX = (const uint32_t *) MCUXCLPKC_OFFSET2PTR(offsetX);  /* PKC word is CPU word aligned. */

    uint32_t opWords = (uint32_t) MCUXCLPKC_PS1_GETOPLEN() / (sizeof(uint32_t));  /* Assume OPLEN is initialized properly (must be a multiple of PKC wordsize). */
    uint32_t index = 0u;

    do
    {
        uint32_t xi = pX[index];
        if (0u != xi)
        {
            *nTrailingZeros = (index * (sizeof(uint32_t)) * 8u) + __CLZ(__RBIT(xi));
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_TrailingZeros, MCUXCLMATH_ERRORCODE_OK);
        }

        index++;
    } while (index < opWords);

    *nTrailingZeros = index * (sizeof(uint32_t)) * 8u;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_TrailingZeros, MCUXCLMATH_ERRORCODE_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClMath_ShiftModulus)
mcuxClMath_Status_Protected_t mcuxClMath_ShiftModulus(uint16_t iNShifted_iN)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClMath_ShiftModulus);

    /* Unpack indices. */
    uint8_t iN  = (uint8_t) (iNShifted_iN & 0xFFu);
    uint8_t iNS = (uint8_t) ((iNShifted_iN >> 8) & 0xFFu);

    /* Count the number of leading zeros of modulus n. */
    MCUXCLPKC_WAITFORFINISH();
    uint32_t leadingZeroBits = MCUXCLMATH_FP_LEADINGZEROS(iN);
    uint32_t leadingZeroPkcWords_InBytes = leadingZeroBits / (MCUXCLPKC_WORDSIZE * 8u) * MCUXCLPKC_WORDSIZE;

    /* Set PS2 LEN, to exclude leading zero word(s). */
    uint32_t ps1LenReg = MCUXCLPKC_PS1_GETLENGTH_REG();
    MCUXCLPKC_PS2_SETLENGTH_REG(ps1LenReg - leadingZeroPkcWords_InBytes);  /* Don't care mclen on higher 16 bits. */

    const uint16_t * pUptrt = MCUXCLPKC_GETUPTRT();
    uint16_t offsetN  = pUptrt[iN];
    uint16_t offsetNS = pUptrt[iNS];

    /* Copy and shift nonzero words of modulus. */
    uint32_t shiftAmount = leadingZeroBits & ((MCUXCLPKC_WORDSIZE * 8u) - 1u);
    MCUXCLPKC_PS2_SETMODE(MCUXCLPKC_OP_SHL);
    MCUXCLPKC_PS2_SETXY(0, offsetN);
    MCUXCLPKC_PS2_SETZR(shiftAmount, (offsetNS + leadingZeroPkcWords_InBytes) & 0xFFFFu);
    MCUXCLPKC_PS2_START_L0();

    /* Clear least significant word(s) of NShifted, if leadingZeroBits >= a PKC word. */
    if (0u != leadingZeroPkcWords_InBytes)
    {
        MCUXCLPKC_PS2_SETLENGTH_REG(leadingZeroPkcWords_InBytes);  /* Don't care mclen on higher 16 bits. */
        MCUXCLPKC_FP_CALC_OP2_CONST(iNS, 0);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_ShiftModulus, MCUXCLMATH_ERRORCODE_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        MCUX_CSSL_FP_CONDITIONAL_IMPL((0u != leadingZeroPkcWords_InBytes),
            MCUXCLPKC_FP_CALLED_CALC_OP2_CONST));
}
