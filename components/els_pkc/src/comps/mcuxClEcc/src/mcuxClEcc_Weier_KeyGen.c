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
 * @file  mcuxClEcc_Weier_KeyGen.c
 * @brief Weierstrass curve ECDSA key generation API
 */


#include <stdint.h>
#include <stddef.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_FP.h>
#include <internal/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h>
#include <internal/mcuxClEcc_Weier_KeyGen_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_KeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_KeyGen(
        mcuxClSession_Handle_t pSession,
        const mcuxClEcc_KeyGen_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_KeyGen);

    /**********************************************************/
    /* Initialization                                         */
    /**********************************************************/

    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - mcuxClEcc_CpuWa_t is 32 bit aligned")
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, 0u);
    MCUX_CSSL_FP_FUNCTION_CALL(ret_SetupEnvironment,
        mcuxClEcc_Weier_SetupEnvironment(pSession,
                                        & pParam->curveParam,
                                        ECC_KEYGEN_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != ret_SetupEnvironment)
    {
        if (MCUXCLECC_STATUS_INVALID_PARAMS == ret_SetupEnvironment)
        {
            /* Session has been cleaned, PKC has been deinitialized in SetupEnvironment. */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment) );
        }

        MCUXCLECC_HANDLE_HW_UNAVAILABLE(ret_SetupEnvironment, mcuxClEcc_KeyGen);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Randomize buffers XA/YA/ZA/Z/X0/Y0/X1/Y1. */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt,
                              mcuxClPkc_RandomizeUPTRT(pSession,
                                                      &pOperands[WEIER_XA],
                                                      (WEIER_Y1 - WEIER_XA + 1u)) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_RNG_ERROR);
    }

    MCUXCLMATH_FP_QSQUARED(ECC_NQSQR, ECC_NS, ECC_N, ECC_T0);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;

    /**********************************************************/
    /* Import and check base point G                          */
    /**********************************************************/

    /* Import G to (X1,Y1). */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X1, pParam->curveParam.pG, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y1, pParam->curveParam.pG + byteLenP, byteLenP);

    /* Check G in (X1,Y1) affine NR. */
//  MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in import function.
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckStatus)
    {
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUXCLECC_FP_KEYGEN_BASE_POINT,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else if (MCUXCLECC_STATUS_OK != pointCheckStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }


    /**********************************************************/
    /* Generate multiplicative split private key d0 and d1,   */
    /* d = d0 * d1 mod n, where d0 is a 64-bit odd number.    */
    /**********************************************************/

    MCUX_CSSL_FP_FUNCTION_CALL(ret_CoreKeyGen, mcuxClEcc_Int_CoreKeyGen(pSession, byteLenN));
    if (MCUXCLECC_STATUS_OK != ret_CoreKeyGen)
    {
        if (MCUXCLECC_STATUS_RNG_ERROR == ret_CoreKeyGen)
        {
            mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_RNG_ERROR,
                MCUXCLECC_FP_KEYGEN_GENERATE_PRIKEY,
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
        }

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /**********************************************************/
    /* Derive the plain private key d = d0 * d1 mod n < n.    */
    /**********************************************************/

    /* Compute d in S2 using a blinded multiplication utilizing the random still stored in S3 after mcuxClEcc_Int_CoreKeyGen. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey,
                        mcuxClEcc_FUP_Weier_KeyGen_DerivePlainPrivKey_LEN);

    /**********************************************************/
    /* Calculate public key Q = d1 * (d0 * G)                 */
    /**********************************************************/

    /* Convert coordinates of G to Montgomery representation. */
    MCUXCLPKC_FP_CALC_MC1_MM(WEIER_X0, WEIER_X1, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_CALC_MC1_MM(WEIER_Y0, WEIER_Y1, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_CALC_OP1_NEG(WEIER_Z, ECC_P);  /* 1 in MR */
    /* G will be randomized (projective coordinate randomization) in SecurePointMult. */

    /* Calculate Q0 = d0 * G. */
    MCUX_CSSL_FP_FUNCTION_CALL(securePointMultStatusFirst, mcuxClEcc_SecurePointMult(pSession, ECC_S0, 64u));
    if(MCUXCLECC_STATUS_RNG_ERROR == securePointMultStatusFirst)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != securePointMultStatusFirst)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }

    /* In case d1 is even, perform scalar multiplication d1 * Q0 by computing (n-d1) * (-Q0) as this avoids the exceptional case d1 = n-1 */
    MCUX_CSSL_FP_BRANCH_DECL(scalarEvenBranch);
    MCUXCLPKC_FP_CALC_OP1_LSB0s(ECC_S1);
    uint32_t d1NoOfTrailingZeros = MCUXCLPKC_WAITFORFINISH_GETZERO();
    if(MCUXCLPKC_FLAG_NONZERO == d1NoOfTrailingZeros)
    {
        MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
        MCUXCLPKC_FP_CALC_MC1_MS(WEIER_Y0, ECC_PS, WEIER_Y0, ECC_PS);

        MCUX_CSSL_FP_BRANCH_POSITIVE(scalarEvenBranch,
            MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
    }

    /* Calculate Q = d1 * Q0. */
    MCUX_CSSL_FP_FUNCTION_CALL(securePointMultStatusSecond, mcuxClEcc_SecurePointMult(pSession, ECC_S1, byteLenN * 8u));
    if(MCUXCLECC_STATUS_RNG_ERROR == securePointMultStatusSecond)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != securePointMultStatusSecond)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(scalarEvenBranch, MCUXCLPKC_FLAG_NONZERO == d1NoOfTrailingZeros));


    /**********************************************************/
    /* Convert public key to affine coordinates and check     */
    /**********************************************************/

    /* T0 = ModInv(Z), where Z = (z * 256^LEN) \equiv z in MR. */
    MCUXCLMATH_FP_MODINV(ECC_T0, WEIER_Z, ECC_P, ECC_T1);
    /* T0 = z^(-1) * 256^(-LEN) \equiv z^(-1) * 256^(-2LEN) in MR. */

    /* Convert Q to affine coordinates. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine,
                        mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine_LEN);

    /* Check Q in (XA,YA) affine NR. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_XA, WEIER_YA);
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckQStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_STATUS_OK != pointCheckQStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /**********************************************************/
    /* Check n and p and export private and public key.       */
    /**********************************************************/

    /* Import prime p and order n again, and check (compare with) existing one. */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->curveParam.pN, byteLenN);

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    uint32_t zeroFlag_checkP = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    uint32_t zeroFlag_checkN = MCUXCLPKC_WAITFORFINISH_GETZERO();

    if (   (zeroFlag_checkP == MCUXCLPKC_FLAG_ZERO)
        && (zeroFlag_checkN == MCUXCLPKC_FLAG_ZERO) )
    {
        MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExport,
            mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                                  pParam->pPrivateKey,
                                                  MCUXCLPKC_PACKARGS2(ECC_S2, ECC_T0),
                                                  byteLenN) );
        if (MCUXCLPKC_STATUS_OK != ret_SecExport)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pPublicKey, WEIER_XA, byteLenP);
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pPublicKey + byteLenP, WEIER_YA, byteLenP);

        /* Clear PKC workarea. */
        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_KEYGEN_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUXCLECC_FP_KEYGEN_FINAL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_KeyGen, MCUXCLECC_STATUS_FAULT_ATTACK);
}
