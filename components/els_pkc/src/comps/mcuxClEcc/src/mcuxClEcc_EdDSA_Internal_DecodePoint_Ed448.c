/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClEcc_EdDSA_Internal_DecodePoint_Ed448.c
 * @brief Function to decode a point
 */


#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClHash.h>
#include <mcuxClMath.h>

#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>
#include <internal/mcuxClEcc_EdDSA_Internal_Hash.h>
#include <internal/mcuxClEcc_EdDSA_Internal_DecodePoint_FUP.h>
#include <internal/mcuxClEcc_EdDSA_Internal_Ed448.h>


/**
 * This function decodes an encoded point Penc on Ed448 and converts it to homogeneous coordinates
 * (x:y:1) in MR. It also verifies that the resulting point lies on the curve Ed448.
 *
 * Input:
 *  - pDomainParams Pointer to ECC common domain parameters for Ed448
 *  - pEncPoint Pointer to encoded point
 *
 * Prerequisites:
 * - ps1Len = (operandSize, operandSize)
 * - Buffers ECC_CP0 and ECC_CP1 contain the curve parameters a and d in MR
 * - Buffer ECC_PFULL contains p'||p
 * - Buffer ECC_PS contains the shifted modulus associated to p
 *
 * Result:
 *  - Buffers ECC_COORD00, ECC_COORD01, ECC_COORD02 contain the homogeneous coordinates (x:y:1) in MR
 *
 * Return values:
 *  - MCUXCLECC_STATUS_OK                if the function executed successfully
 *  - MCUXCLECC_STATUS_INVALID_PARAMS    if the input point is invalid, i.e. the decoing failed
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_DecodePoint_Ed448, mcuxClEcc_EdDSA_DecodePointFunction_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_DecodePoint_Ed448(
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    const uint8_t *pEncPoint
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_DecodePoint_Ed448);

#if !(MCUXCLPKC_WORDSIZE == 8u)
    #error "This implementation only supports 64-bit PKC word"
#endif

    /* Step 1: Copy the encoded point to buffer ECC_T0. */
    const uint32_t encodedLen = (uint32_t) pDomainParams->b / 8u;
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pEncPoint, encodedLen);

    /* Step 2: Read and backup the LSBit x0 from buffer ECC_T0 and clear it in buffer ECC_T0. */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pT0LastByte = &MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T0])[encodedLen - 1u];
    /* MSByte should be 0x80 or 0x00 */
    uint8_t T0LastByte = *pT0LastByte;
    if ((0x80u != T0LastByte) && (0x00u != T0LastByte))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_DecodePoint_Ed448, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc)); /* Step 1 */
    }
    uint8_t x0 = T0LastByte >> 7u;
    *pT0LastByte = 0x00u;

    /* Step 3: Compute ECC_T0 - ECC_P. If the CARRY flag is not set, the decoding failed
    and #MCUXCLECC_STATUS_INVALID_PARAMS is returned. */
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_DecodePoint_Ed448, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),  /* Step 1 */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP);                               /* Step 3 */
    }

    /* Step 4: Set u = y^2-1 and v = d*y^2 - 1 and perform the following steps to compute the x-coordinate candidate x':
     *  - Set x~ = u^3 * v * (u^5*v^3)^((p-3)/4) mod p
     *  - If v * x~^2 =  u mod p, set x' = x~.
     *  - If v * x~^2 != u mod p, the decoding failed. */

    /* Compute (u^5*v^3)^((p-3)/4) mod p and the Y-, and Z-coordinate for the point decoding result (X:Y:Z) */
    uint8_t *pC3 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_COORD03]);
    pOperands[ECC_V0] = (uint16_t) 2u;
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common,
                        mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Common_LEN);
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448,
                        mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_PrepareExp_Ed448_LEN);
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("pC3 is 32-bit aligned.")
    MCUXCLPKC_FP_SWITCHENDIANNESS((uint32_t*)pC3, pDomainParams->common.byteLenP); // the exponent should be in big endian format for MCUXCLMATH_FP_MODEXP_SQRMULTL2R
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pC3, (uint32_t) pDomainParams->common.byteLenP, ECC_COORD00, ECC_COORD04, ECC_P, TWED_PP_Y0); // ECC_COORD00 = (u^5 * v^3)^((p-3)/4) mod p; use TWED_PP_Y0 as temp buffer

    /* Compute the x~ candidate, x~^2 * v - u */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448,
                        mcuxClEcc_FUP_EdDSA_Internal_DecodePoint_ComputeXCandidate_Ed448_LEN);
    uint32_t zeroFlag_check1 = MCUXCLPKC_WAITFORFINISH_GETZERO();            // If flag is set, x~^2 * v = u mod p

    /* If x~^2 * v != u, return #MCUXCLECC_STATUS_INVALID_PARAMS, decoding failed. */
    if (MCUXCLPKC_FLAG_NONZERO == zeroFlag_check1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_DecodePoint_Ed448, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),  /* Step 1 */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,                                /* Step 3 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),                  /* Step 4 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
    }

    /* Set x' = x~ */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_COORD00, ECC_T3, ECC_P, ECC_P);             // x' in MR in range [0,p-1]
    /* After this, we have x' in ECC_COORD00 in MR in range [0,p-1], y in MR in ECC_COORD01, 1 in MR in ECC_COORD02, and PKC_ZERO is set if and only if x' = 0 */

    /* Step 5: If the ZERO flag of the PKC is set and x0=1, return #MCUXCLECC_STATUS_INVALID_PARAMS, decoding failed. */
    if ((MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO()) && (1u == x0))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_DecodePoint_Ed448, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),  /* Step 1 */
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,                                /* Step 3 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),                  /* Step 4 */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS);
    }

    /* Step 6: If x0!=x' mod 2, set ECC_T3 = ECC_P - ECC_T3. Finally ECC_COORD00 contains x in MR. */
    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T3, ECC_COORD00, ECC_P);                    // x' mod p in NR in range [0,p-1] because ECC_COORD00 is in range [0,p-1]

    uint32_t *pT3FirstWord = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_T3]);    // Loading a word is usually cheaper than loading a byte
    MCUXCLPKC_WAITFORFINISH();
    uint8_t x0_candidate = (uint8_t)(*pT3FirstWord) & 0x01u;                // LSBit of x~

    /* Check if x0 != x' mod 2 */
    MCUX_CSSL_FP_BRANCH_DECL(x0Isx);
    if (x0 != x0_candidate)
    {
        MCUXCLPKC_FP_CALC_OP1_SUB(ECC_COORD00, ECC_P, ECC_COORD00);

        MCUX_CSSL_FP_BRANCH_POSITIVE(x0Isx, MCUXCLPKC_FP_CALLED_CALC_OP1_SUB);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_DecodePoint_Ed448, MCUXCLECC_STATUS_OK,
        /* Step 1 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        /* Step 3 */
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        /* Step 4 */
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_SwitchEndianness),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModExp_SqrMultL2R),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        /* Step 6 */
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(x0Isx, x0 != x0_candidate) );
}
