/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClEcc_PointMult.c
 * @brief mcuxClEcc: implementation of ECC point multiplication
 */

#include <stdint.h>
#include <stddef.h>

#include <mcuxClCss_Rng.h>
#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Internal_FP.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointMult)
mcuxClEcc_Status_Protected_t mcuxClEcc_PointMult(mcuxClSession_Handle_t pSession,
                                               const mcuxClEcc_PointMult_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointMult);

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;
    const uint32_t byteLenMax = ((byteLenP > byteLenN) ? byteLenP : byteLenN);
    const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenMax);
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
    const uint32_t wordSizePkcWa = (bufferSize * ECC_POINTMULT_NO_OF_BUFFERS) / (sizeof(uint32_t));
    pSession->pkcWa.used += wordSizePkcWa;

    mcuxClPkc_State_t pkcStateBackup;
    MCUXCLPKC_FP_INITIALIZE(& pkcStateBackup);

    uint32_t pOperands32[(ECC_POINTMULT_NO_OF_VIRTUALS + ECC_POINTMULT_NO_OF_BUFFERS + 1u) / 2u];

    uint16_t *pOperands = (uint16_t *) pOperands32;
    MCUXCLPKC_SETUPTRT(pOperands);

    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);

    uint16_t * pOperands_realBuffer = & pOperands[ECC_POINTMULT_NO_OF_VIRTUALS];

    MCUXCLPKC_FP_GENERATEUPTRT(pOperands_realBuffer, pPkcWorkarea,
                              (uint16_t) bufferSize, ECC_POINTMULT_NO_OF_BUFFERS);
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt, mcuxClPkc_RandomizeUPTRT(pOperands_realBuffer, ECC_POINTMULT_NO_OF_BUFFERS));
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_RNG_ERROR);
    }

    uint32_t nOffset_pOffset = MCUXCLECC_LOAD_2OFFSETS(pOperands32, ECC_PFULL, ECC_NFULL);
    nOffset_pOffset += (((uint32_t) MCUXCLPKC_WORDSIZE << 16) | (uint32_t) MCUXCLPKC_WORDSIZE);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_P, ECC_N, nOffset_pOffset);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_P, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_N, pParam->curveParam.pN, byteLenN);

    const volatile uint8_t * ptrP = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_P]);
    const volatile uint8_t * ptrN = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
    uint32_t p0 = ((const volatile uint32_t *) ptrP)[0];
    uint32_t n0 = ((const volatile uint32_t *) ptrN)[0];
    if (0x01u != (0x01u & p0 & n0))
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_INVALID_PARAMS,
            MCUXCLECC_FP_POINTMULT_CURVE_PARAM_0,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLMATH_FP_NDASH(ECC_P, ECC_T0);
    MCUXCLMATH_FP_NDASH(ECC_N, ECC_T0);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_PS, ECC_P);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_NS, ECC_N);
    MCUXCLMATH_FP_QSQUARED(ECC_PQSQR, ECC_PS, ECC_P, ECC_T0);
    MCUXCLMATH_FP_QDASH(ECC_NQSQR, ECC_NS, ECC_N, ECC_T0, (uint16_t) (operandSize + bufferSize));

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pA, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_R0, ECC_T0, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_R1, pParam->curveParam.pB, byteLenP);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VA, ECC_VB, ECC_R0, ECC_R1);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_X1, pParam->pPoint, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_Y1, pParam->pPoint + byteLenP, byteLenP);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_INVALID_PARAMS,
            MCUXCLECC_FP_POINTMULT_BASE_POINT,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);
    uint32_t *ptr32S0 = (uint32_t *) MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord1,mcuxClCss_Prng_GetRandom((uint8_t*)&ptr32S0[0],(2u * sizeof(uint32_t))));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_randWord1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_RNG_ERROR);
    }
    ptr32S0[0] |= 0x00000001u;
    ptr32S0[1] |= 0x80000000u;

    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_S1, ECC_S0, 0u);
    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_S1, ECC_N, ECC_T1);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize);
    MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(ECC_S1, pParam->pScalar, ECC_T1, byteLenN);

    uint8_t *ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);

    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(ptrS2, bufferSize));
    if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_RNG_ERROR);
    }
    MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S2, ECC_S2, 1u);

    MCUXCLPKC_FP_CALC_OP1_ADD(ECC_S3, ECC_S1, ECC_S2);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
    MCUXCLPKC_PS2_SETLENGTH(bufferSize, operandSize);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_PointMult_SplitScalar_ConvertPoint2MR,
                        mcuxClEcc_PointMult_SplitScalar_ConvertPoint2MR_LEN);

    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {

        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_POINTMULT_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_NEUTRAL_POINT,
            MCUXCLECC_FP_POINTMULT_SCALAR,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLECC_FP_SECUREPOINTMULT(ECC_S0, 64u);

    volatile uint32_t *ptrS1 = (volatile uint32_t *)MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S1]);
	MCUX_CSSL_FP_BRANCH_DECL(scalarEvenBranch);
    MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
    uint32_t d1Lsbit = (*ptrS1 & 0x01u);
    if(d1Lsbit == 0u)
    {
        MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
        MCUXCLPKC_FP_CALC_MC1_MS(ECC_Y0, ECC_PS, ECC_Y0, ECC_PS);
		MCUX_CSSL_FP_BRANCH_POSITIVE(scalarEvenBranch,
									MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
									MCUXCLPKC_FP_CALLED_CALC_MC1_MS);
    }

    MCUXCLECC_FP_SECUREPOINTMULT(ECC_S1, byteLenN * 8u);
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(scalarEvenBranch, d1Lsbit == 0u));

    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_Z, ECC_P, ECC_T1);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_KeyGen_Convert_PubKey,
                        mcuxClEcc_KeyGen_Convert_PubKey_LEN);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_XA, ECC_YA);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->curveParam.pN, byteLenN);

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    uint32_t zeroFlag_checkP = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    uint32_t zeroFlag_checkN = MCUXCLPKC_WAITFORFINISH_GETZERO();

    if (   (zeroFlag_checkP == MCUXCLPKC_FLAG_ZERO)
        && (zeroFlag_checkN == MCUXCLPKC_FLAG_ZERO) )
    {
        MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC(pParam->pResult,            ECC_XA, ECC_T0, byteLenP);
        MCUXCLPKC_FP_SECUREEXPORTBIGENDIANFROMPKC(pParam->pResult + byteLenP, ECC_YA, ECC_T1, byteLenP);

        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_POINTMULT_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_EXPECT(MCUXCLECC_FP_POINTMULT_CONVERT_POINT);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_POINTMULT_OK,
            MCUXCLECC_FP_POINTMULT_FINAL );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
}
