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
 * @file  mcuxClEcc_Mont_MontDhX.c
 * @brief mcuxClEcc: implementation of MontDhX functions
 */

#include <stdint.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClMemory.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhDecodeScalar)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhDecodeScalar(
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhDecodeScalar);

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint32_t c = (uint32_t) pDomainParameters->c;
    uint32_t t = (uint32_t) pDomainParameters->t;

    MCUXCLPKC_WAITFORREADY();
    pOperands[MONT_V0] = (uint16_t) c;
    pOperands[MONT_V1] = (uint16_t) (c - t);
    pOperands[MONT_V2] = (uint16_t) 1u;
    pOperands[MONT_V3] = (uint16_t) (0u - t);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_MontDhDecodeScalar,
                        mcuxClEcc_FUP_MontDhDecodeScalar_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhDecodeScalar, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhDecodeCoordinate)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhDecodeCoordinate(
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateEnc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhDecodeCoordinate);

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint8_t *pT0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T0]);
    uint32_t byteLenP = (uint32_t) pDomainParameters->common.byteLenP;

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeMemCopy,
        mcuxClMemory_copy(pT0, pCoordinateEnc, byteLenP, byteLenP));
    (void) retCodeMemCopy;

    uint32_t leadingZerosP = MCUXCLMATH_FP_LEADINGZEROS(ECC_P);
    if (0u != leadingZerosP)
    {
        uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
        uint32_t bitLenP = (operandSize * 8u) - leadingZerosP;
        uint32_t mask = ((uint32_t) 1u << (bitLenP % 32u)) - 1u;

        uint32_t *p32T0 = (uint32_t *) pT0;
        p32T0[bitLenP / 32u] &= mask;
    }

    MCUXCLPKC_FP_CALC_MC1_MM(MONT_X0, ECC_T0, ECC_PQSQR, ECC_P);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhDecodeCoordinate, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhX)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhX(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_Mont_DomainParams_t *pDomainParameters,
    const uint8_t *pCoordinateUEnc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhX);

    MCUX_CSSL_FP_FUNCTION_CALL(retDecodeScalar,
        mcuxClEcc_Mont_DhDecodeScalar(pDomainParameters));
    (void) retDecodeScalar;

    MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S3,ECC_S3, pDomainParameters->c);

    MCUX_CSSL_FP_FUNCTION_CALL(retGenMulBlind,
        mcuxClEcc_GenerateMultiplicativeBlinding(pSession));
	if (MCUXCLECC_STATUS_OK != retGenMulBlind)
    {

       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_STATUS_MONT_RNG_ERROR);

    };
	MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(retDecodeCoordinate,
        mcuxClEcc_Mont_DhDecodeCoordinate(pDomainParameters, pCoordinateUEnc));
    (void) retDecodeCoordinate;

    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    uint32_t leadingZeroN = MCUXCLMATH_FP_LEADINGZEROS(ECC_N);
    uint32_t bitLenN = (operandSize * 8u) - leadingZeroN;
    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult0,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(ECC_S1, bitLenN, MCUXCLECC_AFFINE));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult1,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(ECC_S0, MCUXCLECC_MONT_DH_SCALAR_BLINDING_BYTELEN * 8u, MCUXCLECC_PROJECTIVE));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    uint8_t *pS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
    *(pS0) = (1u << pDomainParameters->c);

    MCUX_CSSL_FP_FUNCTION_CALL(retSecScalarMult2,
        mcuxClEcc_Mont_SecureScalarMult_XZMontLadder(ECC_S0, (uint32_t)(pDomainParameters->c) + 1u, MCUXCLECC_PROJECTIVE));
    if (MCUXCLECC_STATUS_OK != retSecScalarMult2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T0, MONT_Z0, ECC_P);
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T0, ECC_T0, ECC_P, ECC_P);

    uint32_t pkcStatus = MCUXCLPKC_WAITFORFINISH_GETSTATUS();
    uint32_t zeroFlag = (pkcStatus & MCUXCLPKC_STATUS_ZERO_MSK) >> MCUXCLPKC_STATUS_ZERO_POS;
    if (MCUXCLPKC_FLAG_ZERO == zeroFlag)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_INTSTATUS_POINTMULT_NEUTRAL_POINT,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhDecodeScalar),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_GenerateMultiplicativeBlinding),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhDecodeCoordinate),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_LeadingZeros),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_SecureScalarMult_XZMontLadder),
            MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
    }

    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T0, ECC_P, MONT_Z0);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_MontDhX_CalcAffineX,
                        mcuxClEcc_FUP_MontDhX_CalcAffineX_LEN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhX, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhDecodeScalar),
        MCUXCLPKC_FP_CALLED_CALC_OP1_SHR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_GenerateMultiplicativeBlinding),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Mont_DhDecodeCoordinate),
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
