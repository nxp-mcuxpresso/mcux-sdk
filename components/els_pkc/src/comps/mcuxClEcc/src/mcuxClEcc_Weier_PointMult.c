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
 * @file  mcuxClEcc_Weier_PointMult.c
 * @brief Weierstrass curve point multiplication API
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
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_FP.h>
#include <internal/mcuxClEcc_Weier_PointMult_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_PointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointMult(
        mcuxClSession_Handle_t pSession,
        const mcuxClEcc_PointMult_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_PointMult);

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
                                        ECC_POINTMULT_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != ret_SetupEnvironment)
    {
        if (MCUXCLECC_STATUS_INVALID_PARAMS == ret_SetupEnvironment)
        {
            /* Session has been cleaned, PKC has been deinitialized in SetupEnvironment. */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment) );
        }

        MCUXCLECC_HANDLE_HW_UNAVAILABLE(ret_SetupEnvironment, mcuxClEcc_PointMult);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Randomize buffers XA/YA/ZA/Z/X0/Y0/X1/Y1. */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt,
                              mcuxClPkc_RandomizeUPTRT(pSession,
                                                      &pOperands[WEIER_XA],
                                                      (WEIER_Y1 - WEIER_XA + 1u)) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    MCUXCLMATH_FP_QDASH(ECC_NQSQR, ECC_NS, ECC_N, ECC_T0, (uint16_t) (operandSize + bufferSize));  /* **CAUTION** */

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;

    /**********************************************************/
    /* Import and check point P                               */
    /**********************************************************/

    /* Import P to (X1,Y1). */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X1, pParam->pPoint, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y1, pParam->pPoint + byteLenP, byteLenP);

    /* Check P in (X1,Y1) affine NR. */
//  MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in import function.
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckStatus)
    {
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUXCLECC_FP_POINTMULT_BASE_POINT,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else if (MCUXCLECC_STATUS_OK != pointCheckStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }


    /**********************************************************/
    /* Securely import scalar d, and multiplicative split to  */
    /* d = d0 * d1 mod n, where d0 is a 64-bit odd number.    */
    /**********************************************************/

    // TODO: CLNS-3449: check if reducing the blinding factor d0 to 32-bit,
    //       and use mcuxClEcc_GenerateMultiplicativeBlinding.
    /* Generate 64-bit random number d0 in buffer S0 of size = operandSize. */
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S0, 0u);
    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_S3, 0u);
    uint8_t *ptrS0 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S0]);
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_randWord1, mcuxClRandom_ncGenerate(pSession, ptrS0, 8u));
    if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_randWord1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }

    /* Set MSBit of d0 (to ensure d0 != 0) using the PKC
     *
     * NOTE: PKC PS1 can be used, because operandSize >= 64.*/
    uint32_t *ptr32S3 = MCUXCLPKC_OFFSET2PTRWORD(pOperands[ECC_S3]);
    ptr32S3[0u] = 0x00000000u;
    ptr32S3[1u] = 0x80000000u;
    MCUXCLPKC_FP_CALC_OP1_OR(ECC_S0, ECC_S0, ECC_S3);

    /* T0 = ModInv(d0), with temp T1. */
    MCUXCLPKC_FP_CALC_OP1_OR_CONST(ECC_S1, ECC_S0, 0u);
    MCUXCLMATH_FP_MODINV(ECC_T0, ECC_S1, ECC_N, ECC_T1);

    MCUXCLPKC_WAITFORREADY();

    /* Securely import scalar d to buffer S1 of size = bufferSize, with temp T1. */
    MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize);
    MCUX_CSSL_FP_FUNCTION_CALL(ret_SecImport,
        mcuxClPkc_SecureImportBigEndianToPkc(pSession, MCUXCLPKC_PACKARGS2(ECC_S1, ECC_T1),
                                            pParam->pScalar, byteLenN) );
    if (MCUXCLPKC_STATUS_OK != ret_SecImport)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Generate (buffer size minus 1 bit) random number d' in buffer S2. */
    uint8_t *ptrS2 = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S2]);  /* PKC word is CPU word aligned. */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClRandom_ncGenerate(pSession, ptrS2, bufferSize));
    if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_GetRandom)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }

    MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S2, ECC_S2, 1u);

    /* S3 = d" = d + d' */
    MCUXCLPKC_FP_CALC_OP1_ADD(ECC_S3, ECC_S1, ECC_S2);

    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS1_SETLENGTH(operandSize, operandSize);
    MCUXCLPKC_PS2_SETLENGTH(bufferSize, operandSize);

    /* Split scalar d = d0 * d1, and convert coordinates of P to Montgomery representation. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR,
                        mcuxClEcc_FUP_Weier_PointMult_SplitScalar_ConvertPoint2MR_LEN);

    /* Check if d is zero. */
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        /* Clear PKC workarea. */
        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_POINTMULT_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_NEUTRAL_POINT,
            MCUXCLECC_FP_POINTMULT_SCALAR,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }


    /**********************************************************/
    /* Calculate scalar multiplications Q = d1 * (d0 * P)     */
    /**********************************************************/

    /* P has been converted to MR, and Z has been initialized to 1 (in MR). */
    /* P will be randomized (projective coordinate randomization) in SecurePointMult. */

    /* Calculate Q0 = d0 * P. */
    MCUX_CSSL_FP_FUNCTION_CALL(securePointMultStatusFirst, mcuxClEcc_SecurePointMult(pSession, ECC_S0, 64u));
    if(MCUXCLECC_STATUS_RNG_ERROR == securePointMultStatusFirst)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != securePointMultStatusFirst)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
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
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_RNG_ERROR);
    }
    else if(MCUXCLECC_STATUS_OK != securePointMultStatusSecond)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }
    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(scalarEvenBranch, MCUXCLPKC_FLAG_NONZERO == d1NoOfTrailingZeros));

    /**********************************************************/
    /* Convert result point to affine coordinates and check   */
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
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
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
        MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportXa,
            mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                                  pParam->pResult,
                                                  MCUXCLPKC_PACKARGS2(WEIER_XA, ECC_T0),
                                                  byteLenP) );
        if (MCUXCLPKC_STATUS_OK != ret_SecExportXa)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL(ret_SecExportYa,
            mcuxClPkc_SecureExportBigEndianFromPkc(pSession,
                                                  pParam->pResult + byteLenP,
                                                  MCUXCLPKC_PACKARGS2(WEIER_YA, ECC_T1),
                                                  byteLenP) );
        if (MCUXCLPKC_STATUS_OK != ret_SecExportYa)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Clear PKC workarea. */
        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_POINTMULT_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_PointMult, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUXCLECC_FP_POINTMULT_FINAL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_PointMult, MCUXCLECC_STATUS_FAULT_ATTACK);
}
