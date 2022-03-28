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

/** @file  mcuxClEcc_Sign.c
 *  @brief mcuxClEcc: implementation of ECDSA signature generation
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

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Sign)
mcuxClEcc_Status_Protected_t mcuxClEcc_Sign(mcuxClSession_Handle_t pSession,
                                          const mcuxClEcc_Sign_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Sign);

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;
    const uint32_t byteLenMax = ((byteLenP > byteLenN) ? byteLenP : byteLenN);
    const uint32_t operandSize = MCUXCLPKC_ROUNDUP_SIZE(byteLenMax);
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    uint8_t *pPkcWorkarea = (uint8_t *) (& pSession->pkcWa.buffer[pSession->pkcWa.used]);
    const uint32_t wordSizePkcWa = (bufferSize * ECC_SIGN_NO_OF_BUFFERS) / (sizeof(uint32_t));
    pSession->pkcWa.used += wordSizePkcWa;

    mcuxClPkc_State_t pkcStateBackup;
    MCUXCLPKC_FP_INITIALIZE(& pkcStateBackup);

    uint32_t pOperands32[(ECC_SIGN_NO_OF_VIRTUALS + ECC_SIGN_NO_OF_BUFFERS + 1u) / 2u];

    uint16_t *pOperands = (uint16_t *) pOperands32;
    MCUXCLPKC_SETUPTRT(pOperands);

    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);

    uint16_t * pOperands_group0 = & pOperands[ECC_SIGN_NO_OF_VIRTUALS];
    MCUXCLPKC_FP_GENERATEUPTRT(pOperands_group0, pPkcWorkarea,
                              (uint16_t) bufferSize, ECC_SIGN_NO_OF_BUFFERS0);
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt0,
                              mcuxClPkc_RandomizeUPTRT(pOperands_group0, ECC_SIGN_NO_OF_BUFFERS0) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt0)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_RNG_ERROR);
    }

    uint16_t * pOperands_group1 = & pOperands[ECC_SIGN_NO_OF_VIRTUALS + ECC_SIGN_NO_OF_BUFFERS0];
    const uint8_t * pPkcWorkarea_group1 = & pPkcWorkarea[bufferSize * ECC_SIGN_NO_OF_BUFFERS0];
    MCUXCLPKC_FP_GENERATEUPTRT(pOperands_group1, pPkcWorkarea_group1,
                              (uint16_t) (bufferSize * 2u), ECC_SIGN_NO_OF_BUFFERS1 / 2u);
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt1,
                              mcuxClPkc_RandomizeUPTRT(pOperands_group1, ECC_SIGN_NO_OF_BUFFERS1 / 2u) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_RNG_ERROR);
    }

    uint32_t offsetsS0S1 = MCUXCLECC_LOAD_2OFFSETS(pOperands32, ECC_S0, ECC_S1);
    uint32_t offsetsS2S3 = MCUXCLECC_LOAD_2OFFSETS(pOperands32, ECC_S2, ECC_S3);
    uint32_t offsetsT0T1 = offsetsS0S1 + ((bufferSize << 16) + bufferSize);
    uint32_t offsetsT2T3 = offsetsS2S3 + ((bufferSize << 16) + bufferSize);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_T0, ECC_T1, offsetsT0T1);
    MCUXCLECC_STORE_2OFFSETS(pOperands32, ECC_T2, ECC_T3, offsetsT2T3);

    uint16_t * pOperands_group2 = & pOperands[ECC_SIGN_NO_OF_VIRTUALS + ECC_SIGN_NO_OF_BUFFERS0 + ECC_SIGN_NO_OF_BUFFERS1];
    const uint8_t * pPkcWorkarea_group2 = & pPkcWorkarea[bufferSize * (ECC_SIGN_NO_OF_BUFFERS0 + ECC_SIGN_NO_OF_BUFFERS1)];
    MCUXCLPKC_FP_GENERATEUPTRT(pOperands_group2, pPkcWorkarea_group2,
                              (uint16_t) bufferSize, ECC_SIGN_NO_OF_BUFFERS2);
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt2,
                              mcuxClPkc_RandomizeUPTRT(pOperands_group2, ECC_SIGN_NO_OF_BUFFERS2) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_RNG_ERROR);
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

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_INVALID_PARAMS,
            MCUXCLECC_FP_SIGN_CURVE_PARAM_0,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
    }

    MCUXCLMATH_FP_NDASH(ECC_P, ECC_T0);
    MCUXCLMATH_FP_NDASH(ECC_N, ECC_T0);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_PS, ECC_P);
    MCUXCLMATH_FP_SHIFTMODULUS(ECC_NS, ECC_N);
    MCUXCLMATH_FP_QSQUARED(ECC_PQSQR, ECC_PS, ECC_P, ECC_T0);
    MCUXCLMATH_FP_QSQUARED(ECC_NQSQR, ECC_NS, ECC_N, ECC_T0);

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pA, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_R0, ECC_T0, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_R1, pParam->curveParam.pB, byteLenP);
    MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VA, ECC_VB, ECC_R0, ECC_R1);

    uint32_t fail_r = 0u;
    uint32_t fail_s = 0u;
    MCUX_CSSL_FP_LOOP_DECL(MainLoop_R);
    MCUX_CSSL_FP_LOOP_DECL(MainLoop_S);
    do
    {

        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_X1, pParam->curveParam.pG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_Y1, pParam->curveParam.pG + byteLenP, byteLenP);

        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_X1, ECC_Y1);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
        {
            if ((0u == fail_r) && (0u == fail_s))
            {
                pSession->pkcWa.used -= wordSizePkcWa;
                MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_INVALID_PARAMS,
                    MCUXCLECC_FP_SIGN_CURVE_PARAM,
                    MCUXCLECC_FP_SIGN_LOOP_R_0,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(ret_CoreKeyGen, mcuxClEcc_Int_CoreKeyGen(pSession, byteLenN));
        if (MCUXCLECC_STATUS_OK != ret_CoreKeyGen)
        {
            if ( (MCUXCLECC_INTSTATUS_RNG_ERROR == ret_CoreKeyGen)
                 && (0u == fail_r) && (0u == fail_s) )
            {
                pSession->pkcWa.used -= wordSizePkcWa;
                MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_RNG_ERROR,
                    MCUXCLECC_FP_SIGN_CURVE_PARAM,
                    MCUXCLECC_FP_SIGN_LOOP_R_1,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_Deinitialize) );
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop_R,
            MCUXCLECC_FP_SIGN_LOOP_R );

        MCUXCLPKC_FP_CALC_MC1_MM(ECC_X0, ECC_X1, ECC_PQSQR, ECC_P);
        MCUXCLPKC_FP_CALC_MC1_MM(ECC_Y0, ECC_Y1, ECC_PQSQR, ECC_P);
        MCUXCLPKC_FP_CALC_OP1_NEG(ECC_Z, ECC_P);

        MCUXCLECC_FP_SECUREPOINTMULT(ECC_S0, 64u);

        volatile uint32_t *ptrS1 = (volatile uint32_t *)MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S1]);
        MCUX_CSSL_FP_BRANCH_DECL(scalarEvenBranch);
        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
        uint32_t k1Lsbit = (*ptrS1 & 0x01u);
        if(k1Lsbit == 0u)
        {
            MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
            MCUXCLPKC_FP_CALC_MC1_MS(ECC_Y0, ECC_PS, ECC_Y0, ECC_PS);
		    		MCUX_CSSL_FP_BRANCH_POSITIVE(scalarEvenBranch,
									MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
									MCUXCLPKC_FP_CALLED_CALC_MC1_MS
                                    );
        }

        MCUXCLECC_FP_SECUREPOINTMULT(ECC_S1, byteLenN * 8u);
        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(scalarEvenBranch, k1Lsbit == 0u));

        MCUXCLMATH_FP_MODINV(ECC_T0, ECC_Z, ECC_P, ECC_T1);

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_KeyGen_Convert_PubKey,
                            mcuxClEcc_KeyGen_Convert_PubKey_LEN);

        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_COPY_2OFFSETS(pOperands32, ECC_VX0, ECC_VY0, ECC_XA, ECC_YA);
        if (MCUXCLECC_INTSTATUS_POINTCHECK_OK != MCUXCLECC_FP_POINTCHECKAFFINENR())
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUXCLPKC_FP_CALC_MC1_MS(ECC_XA, ECC_XA, ECC_N, ECC_N);

        fail_r += MCUXCLPKC_WAITFORFINISH_GETZERO();
        if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_GETZERO())
        {
            continue;
        }

        MCUXCLPKC_FP_SECUREIMPORTBIGENDIANTOPKC(ECC_ZA, pParam->pPrivateKey, ECC_T0, byteLenN);

        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();
        uint8_t * ptrZ = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_Z]);

        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClCss_Prng_GetRandom(ptrZ, operandSize));
        if (MCUXCLCSS_STATUS_OK != ret_PRNG_GetRandom)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_RNG_ERROR);
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

        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop_S,
            MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                MCUXCLPKC_FP_CALLED_CALC_OP1_SHR ),
            MCUXCLECC_FP_SIGN_LOOP_S );

        if(k1Lsbit == 0u)
        {
            MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
            MCUX_CSSL_FP_EXPECT(MCUXCLPKC_FP_CALLED_CALC_OP1_SUB);
        }

        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Sign_CalculateS,
                            mcuxClEcc_Sign_CalculateS_LEN);

        MCUXCLMATH_FP_MODINV(ECC_T0, ECC_T2, ECC_N, ECC_T3);

        MCUXCLPKC_FP_CALC_MC1_MM(ECC_YA, ECC_T0, ECC_T1, ECC_N);
        MCUXCLPKC_FP_CALC_MC1_MS(ECC_YA, ECC_YA, ECC_N, ECC_N);

        fail_s += MCUXCLPKC_WAITFORFINISH_GETZERO();

    } while(MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_GETZERO());

    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->curveParam.pN, byteLenN);

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    uint32_t zeroFlag_checkP = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    uint32_t zeroFlag_checkN = MCUXCLPKC_WAITFORFINISH_GETZERO();

    if (   (zeroFlag_checkP == MCUXCLPKC_FLAG_ZERO)
        && (zeroFlag_checkN == MCUXCLPKC_FLAG_ZERO) )
    {
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pSignature, ECC_XA, byteLenN);
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pSignature + byteLenN, ECC_YA, byteLenN);

        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_SIGN_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        pSession->pkcWa.used -= wordSizePkcWa;
        MCUXCLPKC_FP_DEINITIALIZE(& pkcStateBackup);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_SIGN_OK,
            MCUXCLECC_FP_SIGN_BEFORE_LOOP,
            MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop_R, fail_r + fail_s + 1u),
            MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop_S, fail_s + 1u),
            MCUXCLECC_FP_SIGN_FINAL );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
}
