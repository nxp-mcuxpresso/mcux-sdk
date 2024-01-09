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
 * @file  mcuxClEcc_Weier_Sign.c
 * @brief Weierstrass curve ECDSA signature generation API
 */


#include <stdint.h>
#include <stddef.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEcc.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClEcc_Internal_Random.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Internal_FP.h>
#include <internal/mcuxClEcc_Weier_Sign_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Sign)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Sign(
        mcuxClSession_Handle_t pSession,
        const mcuxClEcc_Sign_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Sign);

    /**********************************************************/
    /* Initialization                                         */
    /**********************************************************/

    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    /* MISRA Ex. 9 to Rule 11.3 - mcuxClEcc_CpuWa_t is 32 bit aligned */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - mcuxClEcc_CpuWa_t is 32 bit aligned")
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    uint8_t *pPkcWorkarea = (uint8_t *) mcuxClSession_allocateWords_pkcWa(pSession, 0u);
    MCUX_CSSL_FP_FUNCTION_CALL(ret_SetupEnvironment,
        mcuxClEcc_Weier_SetupEnvironment(pSession,
                                        & pParam->curveParam,
                                        ECC_SIGN_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != ret_SetupEnvironment)
    {
        if (MCUXCLECC_STATUS_INVALID_PARAMS == ret_SetupEnvironment)
        {
            /* Session has been cleaned, PKC has been deinitialized in SetupEnvironment. */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment) );
        }

        MCUXCLECC_HANDLE_HW_UNAVAILABLE(ret_SetupEnvironment, mcuxClEcc_Sign);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Randomize buffers XA/YA/ZA/Z/X0/Y0/X1/Y1. */
    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_FP_FUNCTION_CALL(retRandomUptrt,
                              mcuxClPkc_RandomizeUPTRT(pSession,
                                                      &pOperands[WEIER_XA],
                                                      (WEIER_Y1 - WEIER_XA + 1u)) );
    if (MCUXCLPKC_STATUS_OK != retRandomUptrt)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_RNG_ERROR);
    }

    MCUXCLMATH_FP_QSQUARED(ECC_NQSQR, ECC_NS, ECC_N, ECC_T0);

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();
    const uint32_t bufferSize = operandSize + MCUXCLPKC_WORDSIZE;

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;

    /* Main loop of signature generation until both r and s are nonzero. */
    uint32_t fail_r = 0u;
    uint32_t fail_s = 0u;
    MCUX_CSSL_FP_LOOP_DECL(MainLoop_R);
    MCUX_CSSL_FP_LOOP_DECL(MainLoop_S);
    do
    {
        /**********************************************************/
        /* Import and check base point G                          */
        /**********************************************************/

        /* Import G to (X1,Y1). */  /* TODO: create a function to import and check point. */
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X1, pParam->curveParam.pG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y1, pParam->curveParam.pG + byteLenP, byteLenP);

        /* Check G in (X1,Y1) affine NR. */
//      MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in import function.
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);
        MCUX_CSSL_FP_FUNCTION_CALL(pointCheckStatus, mcuxClEcc_PointCheckAffineNR());
        if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckStatus)
        {
            if ((0u == fail_r) && (0u == fail_s))
            {
                mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
                MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                    mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);

                mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_INVALID_PARAMS,
                    MCUXCLECC_FP_SIGN_BEFORE_LOOP,
                    MCUXCLECC_FP_SIGN_LOOP_R_0,
                    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
            }

            /* The result of checking G is inconsistent. */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else if (MCUXCLECC_STATUS_OK != pointCheckStatus)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Do nothing. */
        }

        /**********************************************************/
        /* Generate multiplicative split ephemeral key k0 and k1, */
        /* k = k0 * k1 mod n, where k0 is a 64-bit odd number     */
        /**********************************************************/

        MCUX_CSSL_FP_FUNCTION_CALL(ret_CoreKeyGen, mcuxClEcc_Int_CoreKeyGen(pSession, byteLenN));
        if (MCUXCLECC_STATUS_OK != ret_CoreKeyGen)
        {
            if ( (MCUXCLECC_STATUS_RNG_ERROR == ret_CoreKeyGen)
                 && (0u == fail_r) && (0u == fail_s) )
            {
                mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
                MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                    mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);

                mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_RNG_ERROR,
                    MCUXCLECC_FP_SIGN_BEFORE_LOOP,
                    MCUXCLECC_FP_SIGN_LOOP_R_1,
                    MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
            }

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop_R,
            MCUXCLECC_FP_SIGN_LOOP_R );


        /**********************************************************/
        /* Calculate Q = k1 * (k0 * G)                            */
        /**********************************************************/

        /* Convert coordinates of G to Montgomery representation. */
        MCUXCLPKC_FP_CALC_MC1_MM(WEIER_X0, WEIER_X1, ECC_PQSQR, ECC_P);
        MCUXCLPKC_FP_CALC_MC1_MM(WEIER_Y0, WEIER_Y1, ECC_PQSQR, ECC_P);
        MCUXCLPKC_FP_CALC_OP1_NEG(WEIER_Z, ECC_P);  /* 1 in MR */
        /* G will be randomized (projective coordinate randomization) in SecurePointMult. */

        /* Calculate Q0 = k0 * G. */
        MCUX_CSSL_FP_FUNCTION_CALL(securePointMultStatusFirst, mcuxClEcc_SecurePointMult(pSession, ECC_S0, 64u));
        if(MCUXCLECC_STATUS_RNG_ERROR == securePointMultStatusFirst)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_RNG_ERROR);
        }
        else if(MCUXCLECC_STATUS_OK != securePointMultStatusFirst)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Do nothing. */
        }

        /* In case k1 is even, perform scalar multiplication k1 * Q0 by computing (n - k1) * (-Q0)
         *     as this avoids the exceptional case k1 = n-1. scalar modification will need to be reverted later on
         */
        MCUX_CSSL_FP_BRANCH_DECL(scalarEvenBranch);
        MCUXCLPKC_FP_CALC_OP1_LSB0s(ECC_S1);
        uint32_t k1NoOfTrailingZeros = MCUXCLPKC_WAITFORFINISH_GETZERO();
        if(MCUXCLPKC_FLAG_NONZERO == k1NoOfTrailingZeros)
        {
            MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
            MCUXCLPKC_FP_CALC_MC1_MS(WEIER_Y0, ECC_PS, WEIER_Y0, ECC_PS);

            MCUX_CSSL_FP_BRANCH_POSITIVE(scalarEvenBranch,
                MCUXCLPKC_FP_CALLED_CALC_OP1_SUB,
                MCUXCLPKC_FP_CALLED_CALC_MC1_MS );
        }

        /* Calculate Q = k1 * Q0. */
        MCUX_CSSL_FP_FUNCTION_CALL(securePointMultStatusSecond, mcuxClEcc_SecurePointMult(pSession, ECC_S1, byteLenN * 8u));
        if(MCUXCLECC_STATUS_RNG_ERROR == securePointMultStatusSecond)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_RNG_ERROR);
        }
        else if(MCUXCLECC_STATUS_OK != securePointMultStatusSecond)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Do nothing. */
        }
        MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(scalarEvenBranch, MCUXCLPKC_FLAG_NONZERO == k1NoOfTrailingZeros));


        /**********************************************************/
        /* Convert Q to affine coordinates and check              */
        /**********************************************************/

        /* T0 = ModInv(Z), where Z = (z * 256^LEN) \equiv z in MR. */
        MCUXCLMATH_FP_MODINV(ECC_T0, WEIER_Z, ECC_P, ECC_T1);
        /* T0 = z^(-1) * 256^(-LEN) \equiv z^(-1) * 256^(-2LEN) in MR. */

        /* Convert Q to affine coordinates. */
        /* MISRA Ex. 22, while(0) is allowed */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine,
                            mcuxClEcc_FUP_Weier_ConvertPoint_ToAffine_LEN);

        /* Check Q in (XA,YA) affine NR. */
        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_XA, WEIER_YA);
        MCUX_CSSL_FP_FUNCTION_CALL(pointCheckQStatus, mcuxClEcc_PointCheckAffineNR());
        if (MCUXCLECC_STATUS_OK != pointCheckQStatus)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /**********************************************************/
        /* Calculate r = Q.x mod n, and check if r is zero        */
        /**********************************************************/

        MCUXCLPKC_FP_CALC_MC1_MS(WEIER_XA, WEIER_XA, ECC_N, ECC_N);  /* Hasse's theorem: Abs(n - (p+1)) <= 2 * sqrt(p). */

        fail_r += MCUXCLPKC_WAITFORFINISH_GETZERO();
        if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_GETZERO())
        {
            continue;
        }

        /**********************************************************/
        /* Securely import private key                            */
        /**********************************************************/

        MCUX_CSSL_FP_FUNCTION_CALL(ret_SecImport,
            mcuxClPkc_SecureImportBigEndianToPkc(pSession, MCUXCLPKC_PACKARGS2(WEIER_ZA, ECC_T0),
                                                pParam->pPrivateKey, byteLenN) );
        if (MCUXCLPKC_STATUS_OK != ret_SecImport)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
        }

        /* Generate random number d1 (to blind the private key). */
        MCUXCLPKC_PKC_CPU_ARBITRATION_WORKAROUND();  // avoid CPU accessing to PKC workarea when PKC is busy
        uint8_t * ptrZ = MCUXCLPKC_OFFSET2PTR(pOperands[WEIER_Z]);
        MCUX_CSSL_FP_FUNCTION_CALL(ret_PRNG_GetRandom, mcuxClRandom_ncGenerate(pSession, ptrZ, operandSize));
        if (MCUXCLRANDOM_STATUS_OK != ret_PRNG_GetRandom)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_RNG_ERROR);
        }


        /**********************************************************/
        /* Import message hash, and truncate if longer than n     */
        /**********************************************************/

        /* Import message hash (up to byteLenN bytes). */
        uint32_t byteLenHash = (pParam->optLen & mcuxClEcc_Verify_Param_optLen_byteLenHash_mask) >> mcuxClEcc_Verify_Param_optLen_byteLenHash_offset;
        uint32_t byteLenHashImport = MCUXCLECC_TRUNCATED_HASH_LEN(byteLenHash, byteLenN);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S2, pParam->pHash, byteLenHashImport);

        /* Truncate message hash if its bit length is longer than that of n. */
        if (byteLenHash >= byteLenN)
        {
            /* Count leading zeros in MSByte of n. */
            const volatile uint8_t * ptrN = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_N]);
            uint8_t nMSByte = ptrN[byteLenN - 1u];
            uint32_t nMSByte_LeadZeros = (uint32_t) mcuxClMath_CountLeadingZerosWord((uint32_t) nMSByte) - (8u * ((sizeof(uint32_t)) - 1u));

            /* Only keep the first bitLenN bits of hash. */
            MCUXCLPKC_FP_CALC_OP1_SHR(ECC_S2, ECC_S2, (uint8_t) nMSByte_LeadZeros);
        }

        MCUX_CSSL_FP_LOOP_ITERATION(MainLoop_S,
            MCUX_CSSL_FP_CONDITIONAL((byteLenHash >= byteLenN),
                MCUXCLPKC_FP_CALLED_CALC_OP1_SHR ),
            MCUXCLECC_FP_SIGN_LOOP_S );


        /**********************************************************/
        /* Securely calculate signature s, and check if s is zero */
        /**********************************************************/
        /* Revert scalar modification by computing n-k1 in place again before calculating signature s */
        if(MCUXCLPKC_FLAG_NONZERO == k1NoOfTrailingZeros)
        {
            MCUXCLPKC_FP_CALC_OP1_SUB(ECC_S1, ECC_N, ECC_S1);
            MCUX_CSSL_FP_EXPECT(MCUXCLPKC_FP_CALLED_CALC_OP1_SUB);
        }
        /* Now, XA = r,  S2 = z (hash of message);   */
        /*      S0 = k0, S1 = k1, k = k0 * k1 mod n; */
        /*      ZA = d,  Z  = d1.                    */
        /* s = k^(-1) * (z + r * d) = (k0*k1)^(-1) * (z + r * (d0-d1)) mod n. */

        /* T1 = s'  = k1*(z+r*d) * R^(-2) mod n <= n; */
        /* T2 = k0' = (k*k1) * R^(-3) mod n.          */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_Sign_CalculateS,
                            mcuxClEcc_FUP_Weier_Sign_CalculateS_LEN);

        /* T0 = h0 = ModInv(k0') = (k*k1)^(-1) * R^3 mod n. */
        MCUXCLMATH_FP_MODINV(ECC_T0, ECC_T2, ECC_N, ECC_T3);

        /* YA = s = h0 * s' - n mod n < n. */
        /* MM(h0, s') < 2n because s' <= n. */
        MCUXCLPKC_FP_CALC_MC1_MM(WEIER_YA, ECC_T0, ECC_T1, ECC_N);
        MCUXCLPKC_FP_CALC_MC1_MS(WEIER_YA, WEIER_YA, ECC_N, ECC_N);

        fail_s += MCUXCLPKC_WAITFORFINISH_GETZERO();

    } while(MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_GETZERO());


    /**********************************************************/
    /* Check n and p and export signature r and s             */
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
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pSignature, WEIER_XA, byteLenN);
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pSignature + byteLenN, WEIER_YA, byteLenN);

        /* Clear PKC workarea. */
        MCUXCLPKC_PS1_SETLENGTH(0u, bufferSize * ECC_SIGN_NO_OF_BUFFERS);
        pOperands[ECC_P] = MCUXCLPKC_PTR2OFFSET(pPkcWorkarea);
        MCUXCLPKC_FP_CALC_OP1_CONST(ECC_P, 0u);

        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_Sign, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUXCLECC_FP_SIGN_BEFORE_LOOP,
            MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop_R, fail_r + fail_s + 1u),
            MCUX_CSSL_FP_LOOP_ITERATIONS(MainLoop_S, fail_s + 1u),
            MCUXCLECC_FP_SIGN_FINAL);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Sign, MCUXCLECC_STATUS_FAULT_ATTACK);
}


