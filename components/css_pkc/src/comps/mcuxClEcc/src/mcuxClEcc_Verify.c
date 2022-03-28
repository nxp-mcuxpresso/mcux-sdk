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

/** @file  mcuxClEcc_Verify.c
 *  @brief mcuxClEcc: implementation of ECDSA signature verification
 */

#include <stdint.h>
#include <stddef.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxCsslMemory_Compare.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslParamIntegrity.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>

#include <mcuxClEcc.h>
#include <internal/mcuxClEcc_Internal.h>
#include <internal/mcuxClEcc_Verify_FUP_programs.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Verify)
mcuxClEcc_Status_Protected_t mcuxClEcc_Verify(mcuxClSession_Handle_t pSession,
                                            const mcuxClEcc_Verify_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Verify,

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Initialize),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_GenerateUPTRT),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc)
    );

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;
    const uint32_t byteLenMax = ((byteLenP > byteLenN) ? byteLenP : byteLenN);
    const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenMax);
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
    const uint32_t wordSizePkcWa = (bufferSize * ECC_VERIFY_NO_OF_BUFFERS) / (sizeof(uint32_t));
    pSession->pkcWa.used += wordSizePkcWa;

    mcuxClPkc_State_t pkcStateBackup;
    MCUXCLPKC_FP_INITIALIZE(& pkcStateBackup);

    uint32_t pOperands32[(ECC_VERIFY_NO_OF_VIRTUALS + ECC_VERIFY_NO_OF_BUFFERS + 1u) / 2u];

    uint16_t *pOperands = (uint16_t *) pOperands32;
    MCUXCLPKC_SETUPTRT(pOperands);

    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);

    MCUXCLPKC_FP_GENERATEUPTRT(pOperands + ECC_VERIFY_NO_OF_VIRTUALS,
                              (const uint8_t *) pPkcWorkarea,
                              (uint16_t) bufferSize,
                              ECC_VERIFY_NO_OF_BUFFERS);

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

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLMATH_FP_NDASH(ECC_P, ECC_T0);
    MCUXCLMATH_FP_NDASH(ECC_N, ECC_T0);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_PS, ECC_P);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_NS, ECC_N);
    MCUXCLMATH_FP_QSQUARED(ECC_PQSQR, ECC_PS, ECC_P, ECC_T0);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pA, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_R0, ECC_T0, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_R1, pParam->curveParam.pB, byteLenP);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VA, ECC_VB, ECC_R0, ECC_R1);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S3, pParam->pSignature, byteLenN);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->pSignature + byteLenN, byteLenN);

    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc) );

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T2, ECC_S3, ECC_N, ECC_N);

    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_S3, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T3, ECC_T1, ECC_N, ECC_N);

    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    uint32_t byteLenHash = (pParam->optLen & mcuxClEcc_Verify_Param_optLen_byteLenHash_mask) >> mcuxClEcc_Verify_Param_optLen_byteLenHash_offset;
    uint32_t byteLenHashImport = ((byteLenHash < byteLenN) ? byteLenHash: byteLenN);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S2, pParam->pHash, byteLenHashImport);

    if (byteLenHash >= byteLenN)
    {

        uint8_t nMSByte = ptrN[byteLenN - 1u];
        uint32_t nMSByte_LeadZeros = (uint32_t) __CLZ((uint32_t) nMSByte) - (8u * ((sizeof(uint32_t)) - 1u));

        MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S2, ECC_S2, (uint8_t) nMSByte_LeadZeros);
    }

    MCUXCLPKC_FP_CALC_MC1_MS(ECC_S2, ECC_S2, ECC_N, ECC_N);
    uint32_t checkHashZero = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T2, ECC_T1, ECC_N);
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T2, ECC_N, ECC_T3);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_InitZ_CalcU1U2,
                        mcuxClEcc_Fup_Verify_InitZ_CalcU1U2_LEN);

    if (checkHashZero != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUXCLECC_FP_INTERLEAVE(MCUXCLPKC_PACKARGS2(ECC_S0, ECC_S1), byteLenN * 8u);

    MCUX_CSSL_FP_EXPECT(
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
            MCUXCLPKC_FP_CALLED_CALC_OP1_SHR),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MS,

        MCUXCLPKC_FP_CALLED_CALC_MC1_MR,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Interleave) );

    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {

        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_X1, pParam->curveParam.pG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_Y1, pParam->curveParam.pG + byteLenP, byteLenP);

        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_X2, pParam->pPrecG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_Y2, pParam->pPrecG + byteLenP, byteLenP);

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
        {
            pSession->pkcWa.used -= wordSizePkcWa;
            MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
        }

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X2, ECC_Y2);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
        {
            pSession->pkcWa.used -= wordSizePkcWa;
            MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
        }

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Convert_G_PrecG_toMR,
                            mcuxClEcc_Fup_Verify_Convert_G_PrecG_toMR_LEN);

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_X2, ECC_Y2);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
        pOperands[ECC_VZ0] = pOperands[ECC_Z];
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_XA, ECC_YA);
        MCUXCLECC_FP_CALCFUP_ADD_ONLY();

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Update_G_to_Prec1,
                            mcuxClEcc_Fup_Verify_Update_G_to_Prec1_LEN);

        pOperands[ECC_VT] = pOperands[ECC_S2];
        MCUXCLECC_FP_INT_POINTMULT(ECC_S0, byteLenN * 8u);

        MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_Z, ECC_ZA, ECC_P);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_Z, ECC_T0, 0u);
    }

    MCUXCLPKC_FP_CALC_OP1_NEG(ECC_ZA, ECC_P);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_X1, pParam->pPublicKey, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_Y1, pParam->pPublicKey + byteLenP, byteLenP);

    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult),
            MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
            MCUXCLPKC_FP_CALLED_CALC_OP1_OR_CONST),
        MCUXCLPKC_FP_CALLED_CALC_OP1_NEG,

        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc) );

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_INVALID_PARAMS,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR,
                        mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR_LEN);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ,  ECC_ZA, ECC_Z);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX2, ECC_VY2, ECC_X0, ECC_Y0);
    pOperands[ECC_VZ2] = pOperands[ECC_ZA];
    pOperands[ECC_VT] = pOperands[ECC_S2];
    MCUXCLECC_FP_REPEATPOINTDOUBLE((byteLenN * 8u) / 2u);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VT2, ECC_VT3, ECC_X2, ECC_Y2);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X3, ECC_Y3);
    pOperands[ECC_VZ0] = pOperands[ECC_ZA];
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_X0, ECC_Y0);
    MCUXCLECC_FP_CALCFUP_ADD_ONLY();

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z,
                        mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z_LEN);

    MCUXCLECC_FP_INT_POINTMULT(ECC_S1, byteLenN * 8u);

    MCUX_CSSL_FP_EXPECT(
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_RepeatPointDouble),
        MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Int_PointMult) );

    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_XA, ECC_YA);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VZ0, ECC_VZ,  ECC_ZA, ECC_Z);
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX1, ECC_VY1, ECC_X0, ECC_Y0);
        if (MCUXCLECC_INTSTATUS_POINTADD_NEUTRAL_POINT == MCUXCLECC_FP_POINTFULLADD())
        {
            pSession->pkcWa.used -= wordSizePkcWa;
            MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
        }
    }

    MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, ECC_Z, ECC_ZA, ECC_P);
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T0, ECC_P, ECC_T2);

    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR,
                        mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR_LEN);

    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X0, ECC_Y0);
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOTOK == MCUXCLECC_FP_POINTCHECKAFFINENR())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_EXPECT(

        MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != checkHashZero),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd)),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ModInv),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),

        MCUXCLPKC_FP_CALLED_CALC_OP1_CMP );

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_X1, ECC_S3);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_NOT_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->curveParam.pN, byteLenN);

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    uint32_t zeroFlag_checkP = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    uint32_t zeroFlag_checkN = MCUXCLPKC_WAITFORFINISH_GETZERO();

    uint8_t *pImportR = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);
    uint8_t *pCalcR   = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_X1]);
    mcuxCsslParamIntegrity_Checksum_t compareR_paramChkSum = mcuxCsslParamIntegrity_Protect(3u, pImportR, pCalcR, operandSize);
    MCUX_CSSL_FP_FUNCTION_CALL(cmpareR_result, mcuxCsslMemory_Compare(compareR_paramChkSum, pImportR, pCalcR, operandSize));

    if (   (MCUXCSSLMEMORY_COMPARE_EQUAL == cmpareR_result)
        && (zeroFlag_checkP == MCUXCLPKC_FLAG_ZERO)
        && (zeroFlag_checkN == MCUXCLPKC_FLAG_ZERO) )
    {

        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pOutputR, ECC_X1, byteLenN);

        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_VERIFY_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare),

            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
}
