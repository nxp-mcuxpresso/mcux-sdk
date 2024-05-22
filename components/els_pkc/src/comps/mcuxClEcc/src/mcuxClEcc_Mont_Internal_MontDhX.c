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
 * @file  mcuxClEcc_Mont_Internal_MontDhX.c
 * @brief implementation of MontDhX functions
 */


#include <stdint.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClEcc_Mont_Internal.h>
#include <internal/mcuxClEcc_Mont_Internal_MontDhX_FUP.h>


/**
 * \brief This function decodes an encoded Curve25519 or Curve448 scalar kEnc.
 *
 * Input:
 *  - pDomainParameters: pointer to domain parameter structure passed via API.
 *
 * Prerequisites:
 *  - the encoded secret scalar kEnc is contained in buffer ECC_S2;
 *  - ps1Len = (operandSize, operandSize).
 *
 * Result:
 *  - the decoded secret scalar k is contained in buffer ECC_S3.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_MontDH_DecodeScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_DecodeScalar(
    mcuxClEcc_MontDH_DomainParams_t *pDomainParameters)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_MontDH_DecodeScalar);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t c = (uint32_t) pDomainParameters->c;
    uint32_t t = (uint32_t) pDomainParameters->t;

    MCUXCLPKC_WAITFORREADY();
    pOperands[MONT_V0] = (uint16_t) c;         /* Clear c LSbits by right shift */
    pOperands[MONT_V1] = (uint16_t) (c - t);   /* Clear bit t ~ MSbits by left shift. PKC will left shift (c - t mod PKCWordBitLen) bits */
    pOperands[MONT_V2] = (uint16_t) (0u - t);  /* Left rotate the bit "1" back to bit position t */

    /* MISRA Ex. 22, while(0) is allowed */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_MontDhDecodeScalar,
                        mcuxClEcc_FUP_MontDhDecodeScalar_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_DecodeScalar, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));
}


/**
 * \brief This function imports and decodes an encoded Curve25519 or Curve448
 * x-coordinate uEnc.
 *
 * Inputs:
 *  - pDomainParameters: pointer to domain parameter structure passed via API;
 *  - pCoordinateEnc: pointer to encoded x-coordinate.
 *
 * Prerequisite:
 *  - ps1Len = (operandSize, operandSize).
 *
 * Result:
 *  - the decoded x-coordinate u is contained in buffer MONT_X0 in MR.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_MontDH_DecodeCoordinate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_DecodeCoordinate(
    mcuxClEcc_MontDH_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateEnc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_MontDH_DecodeCoordinate);

    /* Import encoded x-coordinate uEnc. */
    uint32_t byteLenP = (uint32_t) pDomainParameters->common.byteLenP;
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pCoordinateEnc, byteLenP);

    /* If leadingZerosP != 0 (X25519), mask MSByte according to rfc7748, Ch5. */
    uint32_t leadingZerosP;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(ECC_P, &leadingZerosP));
    if (0u != leadingZerosP)
    {
        uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
        uint32_t bitLenP = (operandSize * 8u) - leadingZerosP;
        uint32_t mask = ((uint32_t) 1u << (bitLenP % 32u)) - 1u;

        const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
        uint8_t *pT0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T0]);
        uint32_t *p32T0 = (uint32_t *) pT0;  /* PKC word is CPU word aligned. */
        p32T0[bitLenP / 32u] &= mask;
    }

    /* Covert x-coordinate to Montgomery representation. */
    MCUXCLPKC_FP_CALC_MC1_MM(MONT_X0, ECC_T0, ECC_PQSQR, ECC_P);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_DecodeCoordinate, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM);
}


/**
 * \brief This function implements the X25519 and X448 functions specified
 * in rfc7748, depending on the used curve, which basically performs
 * a secure x-only scalar multiplication of an encoded scalar kEnc and
 * an encoded x-coordinate uEnc and returns the encoded resulting x-coordinate
 * as MontDhX(kEnc, uEnc). Here, the encoding of scalars and x-coordinates
 * are following the specification in rfc7748.
 *
 * Inputs:
 *  - pSession: pointer to mcuxClSession_Descriptor.
 *  - pDomainParameters: pointer to domain parameter structure passed via API;
 *  - pCoordinateUEnc: pointer to encoded x-coordinate uEnc.
 *
 * Return values:
 *  - MCUXCLECC_STATUS_OK: if the function executed successfully;
 *  - MCUXCLECC_STATUS_NEUTRAL_POINT: if the resulting point is zero.
 *
 * Prerequisite:
 *  - the encoded secret scalar kEnc is contained in buffer ECC_S2.
 *
 * Result:
 *  - the decoded secret scalar k is stored in buffer ECC_S2;
 *  - if MCUXCLECC_STATUS_OK is returned, then the result MontDhX(kEnc, uEnc)
 *    is stored in buffer MONT_X0 (in NR, in the range [0, p-1]);
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_MontDH_X)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_X(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_MontDH_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateUEnc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_MontDH_X);

    /* Decode the scalar kEnc and obtain ECC_S3 = k. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_MontDH_DecodeScalar(pDomainParameters));

    /* Compute the cofactorless scalar k' = k/h  for cofactorless blinded scalar multiplication */
    MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S3, ECC_S3, (uint32_t) pDomainParameters->c & 0xFFu);

    /* Generate multiplicative scalar splitting k' = phi*sigma mod n and store (phi, sigma) in (ECC_S1, ECC_S0). */
    MCUX_CSSL_FP_FUNCTION_CALL(retGenMulBlind,
        mcuxClEcc_GenerateMultiplicativeBlinding(pSession, ECC_S3));
    if (MCUXCLECC_STATUS_OK != retGenMulBlind)
    {
        /* GenerateMultiplicativeBlinding is returning only OK or RNG_ERROR */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_RNG_ERROR);

    }
    MCUXCLPKC_WAITFORFINISH();
    /* Decode x-coordinate uEnc and obtain X0 = u in MR. */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_MontDH_DecodeCoordinate(pDomainParameters, pCoordinateUEnc));

    /* Securely calculate, R' = sigma * (u, 1), stored result in buffers (X0, Z0). */
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    uint32_t leadingZeroN;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClMath_LeadingZeros(ECC_N, &leadingZeroN));
    uint32_t bitLenN = (operandSize * 8u) - leadingZeroN;
    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult0,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(pSession, ECC_S1, bitLenN, MCUXCLECC_SCALARMULT_OPTION_AFFINE_INPUT));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Securely calculate, R'' = phi * R', stored result in buffers (X0, Z0). */
    /* Secure multiplication is not needed here, but we do not have non secure one */
    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult1,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(pSession, ECC_S0, MCUXCLECC_SCALARBLINDING_BITSIZE, MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    /* Copy cofactor to the buffer ECC_S0 overwriting phi */
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
    MCUXCLPKC_WAITFORFINISH();
    *(pS0) = (1u << pDomainParameters->c);
    /* Securely calculate, R = cofactor * R'', stored result in buffers (X0, Z0). */
    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult2,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(pSession, ECC_S0, (uint32_t)(pDomainParameters->c) + 1u, MCUXCLECC_SCALARMULT_OPTION_PROJECTIVE_INPUT));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T0, MONT_Z0, ECC_P);        /* T0 = Z in NR, in range [0, p] */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0, ECC_P, ECC_P);  /* T0 = Z in NR, in range [0, p-1] */

    /* Check against NEUTRAL_POINT. */
    uint32_t zeroFlag = MCUXCLPKC_WAITFORFINISH_GETZERO();
    if (MCUXCLPKC_FLAG_ZERO == zeroFlag)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_NEUTRAL_POINT,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_DecodeScalar),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_GenerateMultiplicativeBlinding),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_DecodeCoordinate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
    }

    /* Calculate T1 = Z^(-1) in NR. */
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T0, ECC_P, MONT_Z0);
    /* Calculate X0 = X * Z^(-1) in NR. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_MontDhX_CalcAffineX,
                        mcuxClEcc_FUP_MontDhX_CalcAffineX_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_X, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_DecodeScalar),
        MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_GenerateMultiplicativeBlinding),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_MontDH_DecodeCoordinate),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup) );
}
