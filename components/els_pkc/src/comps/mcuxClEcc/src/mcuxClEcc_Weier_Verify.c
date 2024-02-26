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
 * @file  mcuxClEcc_Weier_Verify.c
 * @brief Weierstrass curve ECDSA signature verification API
 */


#include <stdint.h>
#include <stddef.h>

#include <mcuxClPkc.h>
#include <mcuxClMath.h>
#include <mcuxClSession.h>
#include <mcuxCsslMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClMath_Internal_Utils.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Resource.h>
#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_Weier_Verify_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_PointArithmetic_FUP.h>
#include <internal/mcuxClEcc_Weier_Internal_FP.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Verify(
        mcuxClSession_Handle_t pSession,
        const mcuxClEcc_Verify_Param_t * pParam)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Verify);


    /**********************************************************/
    /* Initialization                                         */
    /**********************************************************/
    /* mcuxClEcc_CpuWa_t will be allocated and placed in the beginning of CPU workarea free space by SetupEnvironment. */
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("MISRA Ex. 9 to Rule 11.3 - mcuxClEcc_CpuWa_t is 32 bit aligned")
    mcuxClEcc_CpuWa_t *pCpuWorkarea = (mcuxClEcc_CpuWa_t *) mcuxClSession_allocateWords_cpuWa(pSession, 0u);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

    MCUX_CSSL_FP_FUNCTION_CALL(ret_SetupEnvironment,
        mcuxClEcc_Weier_SetupEnvironment(pSession,
                                        & pParam->curveParam,
                                        ECC_VERIFY_NO_OF_BUFFERS) );
    if (MCUXCLECC_STATUS_OK != ret_SetupEnvironment)
    {
        if (MCUXCLECC_STATUS_INVALID_PARAMS == ret_SetupEnvironment)
        {
            /* Session has been cleaned, PKC has been deinitialized in SetupEnvironment. */
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_Weier_SetupEnvironment) );
        }

        MCUXCLECC_HANDLE_HW_UNAVAILABLE(ret_SetupEnvironment, mcuxClEcc_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    uint16_t *pOperands = MCUXCLPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("32-bit aligned UPTRT table is assigned in CPU workarea")
    uint32_t *pOperands32 = (uint32_t *) pOperands;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()
    const uint32_t operandSize = MCUXCLPKC_PS1_GETOPLEN();

    const uint32_t byteLenP = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenP_mask) >> mcuxClEcc_DomainParam_misc_byteLenP_offset;
    const uint32_t byteLenN = (pParam->curveParam.misc & mcuxClEcc_DomainParam_misc_byteLenN_mask) >> mcuxClEcc_DomainParam_misc_byteLenN_offset;


    /**********************************************************/
    /* Import signature r and s, and                          */
    /* check both r,s are in range [1, n-1]                   */
    /**********************************************************/

    /* Import r to S3 and s to T1. */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_S3, pParam->pSignature, byteLenN);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->pSignature + byteLenN, byteLenN);

    /* If r < n, then t2 = r; otherwise t2 = r - n. */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T2, ECC_S3, ECC_N, ECC_N);

    /* Check r != 0, r != n. */
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {   /* r = 0 or n. */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }

    /* Check r < n. */
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_S3, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {   /* r > n. */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }

    /* If s < n, then t3 = s; otherwise t3 = s - n. */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_T3, ECC_T1, ECC_N, ECC_N);

    /* Check s != 0, s != n. */
    if (MCUXCLPKC_FLAG_ZERO == MCUXCLPKC_WAITFORFINISH_GETZERO())
    {   /* s = 0 or n. */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }

    /* Check s < n. */
    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    if (MCUXCLPKC_FLAG_CARRY != MCUXCLPKC_WAITFORFINISH_GETCARRY())
    {   /* s > n. */
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_MC1_MS,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
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

    /* Check if hash is 0 modulo n (one subtraction is enough, because bit length of hash <= bit length of n). */
    MCUXCLPKC_FP_CALC_MC1_MS(ECC_S2, ECC_S2, ECC_N, ECC_N);
    uint32_t checkHashZero = MCUXCLPKC_WAITFORFINISH_GETZERO();


    /**********************************************************/
    /* Calculate s^(-1), and                                  */
    /* u1 = hash * s^(-1) mod n and u2 = r * s^(-1) mod n     */
    /**********************************************************/

    /* Calculate s^(-1) * 256^LEN mod n. */
    MCUXCLPKC_FP_CALC_MC1_MR(ECC_T2, ECC_T1, ECC_N);      // t2 = s * (256^LEN)^(-1)
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T2, ECC_N, ECC_T3);  // t1 = t2^(-1) = s^(-1) * 256^LEN, using T3 as temp

    /* Initialize z coordinate, z = 1 in MR, in Z. */
    /* Calculate u1 and u2, store result in S0 and S1. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_InitZ_CalcU1U2,
                        mcuxClEcc_Fup_Verify_InitZ_CalcU1U2_LEN);
    /* Check if u1 is zero. */
    if (checkHashZero != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }


    /**********************************************************/
    /* Calculate P1 = u1 * G                                  */
    /**********************************************************/

    /* Interleave u1 in S0 and u2 in S1. */
    MCUXCLECC_FP_INTERLEAVETWOSCALARS(MCUXCLPKC_PACKARGS2(ECC_S0, ECC_S1), byteLenN * 8u);

    /* Calculate P1 = u1 * G, if u1 != 0 */
    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {
        /* Import G to (X1,Y1). */
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X1, pParam->curveParam.pG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y1, pParam->curveParam.pG + byteLenP, byteLenP);
        /* Import PrecG to (X2, Y2). */
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X2, pParam->pPrecG, byteLenP);
        MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y2, pParam->pPrecG + byteLenP, byteLenP);

        /* Check G in (X1,Y1) affine NR. */
//      MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in import function.
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);
        MCUX_CSSL_FP_FUNCTION_CALL(pointCheckBasePointStatus, mcuxClEcc_PointCheckAffineNR());
        if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckBasePointStatus)
        {
            mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUXCLECC_FP_VERIFY_INIT,
                MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
        }
        else if (MCUXCLECC_STATUS_OK != pointCheckBasePointStatus)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Do nothing. */
        }

        /* Check PrecG in (X2,Y2) affine NR. */
//      MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in _PointCheckAffineNR.
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X2, WEIER_Y2);
        MCUX_CSSL_FP_FUNCTION_CALL(pointCheckPrecPointStatus, mcuxClEcc_PointCheckAffineNR());
        if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckPrecPointStatus)
        {
            mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_PARAMS,
                MCUXCLECC_FP_VERIFY_INIT,
                MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
        }
        else if (MCUXCLECC_STATUS_OK != pointCheckPrecPointStatus)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
        }
        else
        {
            /* Do nothing. */
        }

        /* Convert coordinates of G and PrecG to MR.   */
        /* G:     (X1,Y1) affine NR -> (XA,YA, 1) Jacobian;     */
        /* PrecG: (X2,X2) affine NR -> (X3,Y3, Z=1) relative-z. */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR,
                            mcuxClEcc_FUP_Weier_Verify_Convert_G_PrecG_toMR_LEN);

        /* Prepare 3 pre-computed points for G, with the same z coordinate. */
        /* The relative z-coordinate, z' is stored in Z, instead of ZA.     */
        /* Input: G     in (XA,YA, 1) Jacobian;                      */
        /*        PrecG in (X3,Y3, Z=1) relative-z.  (ps, not in ZA) */
        /* Output: Prec1 = G (unchanged)   in (XA,YA, 1) Jacobian;   */
        /*         Prec2 = PrecG (updated) in (X2,Y2, Z) relative-z; */
        /*         Prec3 = G + PrecG       in (X3,Y3, Z) relative-z. */
//      MCUXCLPKC_WAITFORREADY();  <== unnecessary, because VT2/VT3/VX0/VY0/VZ0/VX1/VY1 are not used in the FUP program before.
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VT2, WEIER_VT3, WEIER_X2, WEIER_Y2);  /* output: Prec2 */
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X3, WEIER_Y3);  /* input: PrecG; output: Prec3 */
        pOperands[WEIER_VZ0] = pOperands[WEIER_Z];                                      /* input: z';    output: z' */
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX1, WEIER_VY1, WEIER_XA, WEIER_YA);  /* input: G */
        MCUXCLECC_FP_CALCFUP_ADD_ONLY();
        /* Hint: since z' (@ Z) = 1, the initial part of double-add FUP program (4 mul) can be skipped, */
        /*       by manually copying G in (XA,YA) to (X2,Y2), which needs extra code size.              */

        /* Update z = z * z' = z' (skipped because z=1, and z' has been stored in Z). */
        /* Update Prec1: (XA,YA, 1) -> (X1,Y1, Z) Jacobian. */
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Update_G_to_Prec1,
                            mcuxClEcc_Fup_Verify_Update_G_to_Prec1_LEN);

        /* Calculate P1 = u1 * G. */
        /* Input: 3 Prec_i, in (Xi,Yi, Z) Jacobian.        */
        /* Output: P1 in (XA,YA, ZA) relative-z, w.r.t. Z. */
//      MCUXCLPKC_WAITFORREADY();  <==unnecessary, because VT is not used in the FUP program before.
        pOperands[WEIER_VT] = pOperands[ECC_S2];  /* Use S2 as 5th temp. */

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_Int_PointMult(ECC_S0, byteLenN * 8u));

        /* Update z = z * z', so P1: (XA,YA, ZA) relative-z -> (XA,YA, Z) Jacobian. */
        MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, WEIER_Z, WEIER_ZA, ECC_P);
        MCUXCLPKC_FP_CALC_OP1_OR_CONST(WEIER_Z, ECC_T0, 0u);
    }

    /* Reset z' = 1 in MR (or initialize z' if u1 == 0). */
    MCUXCLPKC_FP_CALC_OP1_NEG(WEIER_ZA, ECC_P);


    /**********************************************************/
    /* Calculate P2 = u2 * Q, and update P1 accordingly       */
    /**********************************************************/

    /* Import public key Q to (X1,Y1) affine NR. */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_X1, pParam->pPublicKey, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(WEIER_Y1, pParam->pPublicKey + byteLenP, byteLenP);

    /* Check Q in (X1,Y1) affine NR. */
//  MCUXCLPKC_WAITFORREADY();  <== there is WaitForFinish in import function.
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X1, WEIER_Y1);
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckPubKeyStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_INTSTATUS_POINTCHECK_NOT_OK == pointCheckPubKeyStatus)
    {
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_PARAMS,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
            MCUXCLECC_FP_VERIFY_CALC_P1,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointCheckAffineNR),
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }
    else if (MCUXCLECC_STATUS_OK != pointCheckPubKeyStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }
    else
    {
        /* Do nothing. */
    }

    /* Convert Q: (X1,Y1) affine NR -> (X0,Y0, Z) Jacobian. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR,
                        mcuxClEcc_Fup_Verify_Convert_pubkeyQ_toJacobianMR_LEN);

    /* Calculate PrecQ = (2^(byteLenN *4)) * Q. */
    /* Input: Q in (X0,Y0, ZA=1) relative-z.    */
    /* Output: PrecQ in (X3,Y3, ZA) relative-z. */
//  MCUXCLPKC_WAITFORREADY();  <== unnecessary, because VX0/VY0/VZ0/VZ/VX2/VY2/VZ2 are not used in the FUP program before.
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X3, WEIER_Y3);  /* output: PrecQ */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VZ0, WEIER_VZ,  WEIER_ZA, WEIER_Z);   /* input: z, z'; output z' */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX2, WEIER_VY2, WEIER_X0, WEIER_Y0);  /* input: Q */
    pOperands[WEIER_VZ2] = pOperands[WEIER_ZA];
    pOperands[WEIER_VT] = pOperands[ECC_S2];  /* Use S2 as 5th temp. */

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_RepeatPointDouble((byteLenN * 8u) / 2u));

    /* Prepare 3 pre-computed points for Q, with the same z coordinate. */
    /* Input: Q     in (X0, Y0, Z) Jacobian;                       */
    /*        PrecQ in (X3, Y3, ZA) relative-z.                    */
    /* Output: Prec1 = Q (unchanged)   in (X0, Y0, Z) Jacobian;    */
    /*         Prec2 = PrecQ (updated) in (X2, Y2, ZA) relative-z; */
    /*         Prec3 = Q + PrecQ       in (X3, Y3, ZA) relative-z. */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VT2, WEIER_VT3, WEIER_X2, WEIER_Y2);  /* output: Prec2 */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X3, WEIER_Y3);  /* input: PrecQ; output: Prec3 */
    pOperands[WEIER_VZ0] = pOperands[WEIER_ZA];                                     /* input/output: z' */
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX1, WEIER_VY1, WEIER_X0, WEIER_Y0);  /* input: Q */
    MCUXCLECC_FP_CALCFUP_ADD_ONLY();

    /* Update Q:  (X0,Y0, old Z) -> (X1,Y1, new Z) Jacobian; */
    /*        P1: (XA,YA, old Z) -> (X0,Y0, new Z) Jacobian. */
    /* Update z = z * z'. */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z,
                        mcuxClEcc_Fup_Verify_Update_pubkeyQ_P1_z_LEN);

    /* Calculate P2 = u2 * Q. */
    /* Input: 3 Prec_i, in (Xi,Yi, Z) Jacobian.        */
    /* Output: P2 in (XA,YA, ZA) relative-z, w.r.t. Z. */
//  pOperands[WEIER_VT] = pOperands[ECC_S2];  <== the 5th temp WEIER_VT has been set before calling _RepeatPointDouble.

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEcc_Int_PointMult(ECC_S1, byteLenN * 8u));

    /**********************************************************/
    /* Calculate (x1, y1) = P1 + P2, and check the result     */
    /**********************************************************/

    /* Calculate P2 += P1, if u1 != 0. */
    if (MCUXCLPKC_FLAG_ZERO != checkHashZero)
    {
        /* Input: P1 in (X0,Y0, Z) Jacobian;          */
        /*        P2 in (XA,YA, ZA) relative-z.       */
        /* Output: P1 + P2 in (XA,YA, ZA) relative-z. */
        MCUXCLPKC_WAITFORREADY();
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_XA, WEIER_YA);  /* input: P2; output P1 + P2 */
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VZ0, WEIER_VZ, WEIER_ZA, WEIER_Z);    /* input: z' and z; output z' */
        MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX1, WEIER_VY1, WEIER_X0, WEIER_Y0);  /* input: P1 */
        MCUX_CSSL_FP_FUNCTION_CALL(statusPointFullAdd, mcuxClEcc_PointFullAdd());
        if (MCUXCLECC_STATUS_NEUTRAL_POINT == statusPointFullAdd)
        {
            mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
            MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
                mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

            mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
                MCUXCLECC_FP_VERIFY_INIT,
                MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
                MCUXCLECC_FP_VERIFY_CALC_P1,
                MCUXCLECC_FP_VERIFY_CALC_P2,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_PointFullAdd),
                MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
        }
    }

    /* Convert P1 + P2 (or P2 if u1 == 0) to (X0,Y0), affine NR. */
    /* Calculate R = x mod n, in X1. */
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_T0, WEIER_Z, WEIER_ZA, ECC_P);  // t0 = z*z' * 256^LEN         = z*z' in MR
    MCUXCLMATH_FP_MODINV(ECC_T1, ECC_T0, ECC_P, ECC_T2);     // t1 = (z*z')^(-1) * 256^(-LEN), use T2 as temp
    /* MISRA Ex. 22, while(0) is allowed */
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR,
                        mcuxClEcc_Fup_Verify_Convert_P1plusP2_toAffineNR_CalcR_LEN);

    /* Check if P1 + P2 is valid. */
//  MCUXCLPKC_WAITFORREADY();  <== unnecessary, because VX0/VY0 are not used in the FUP program before.
    MCUXCLECC_COPY_2OFFSETS(pOperands32, WEIER_VX0, WEIER_VY0, WEIER_X0, WEIER_Y0);
    MCUX_CSSL_FP_FUNCTION_CALL(pointCheckStatus, mcuxClEcc_PointCheckAffineNR());
    if (MCUXCLECC_STATUS_OK != pointCheckStatus)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /**********************************************************/
    /* Check r = (x mod n) robustly, and check p and n        */
    /**********************************************************/

    /* Check if imported signature R is equal to the calculated R. */
    MCUXCLPKC_FP_CALC_OP1_CMP(WEIER_X1, ECC_S3);
    if (MCUXCLPKC_FLAG_ZERO != MCUXCLPKC_WAITFORFINISH_GETZERO())
    {
        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_INVALID_SIGNATURE,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
            MCUXCLECC_FP_VERIFY_CALC_P1,
            MCUXCLECC_FP_VERIFY_CALC_P2,
            MCUXCLECC_FP_VERIFY_CALC_P1_ADD_P2,
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }

    /* Import prime p and order n again, and check (compare with) existing one. */
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T0, pParam->curveParam.pP, byteLenP);
    MCUXCLPKC_FP_IMPORTBIGENDIANTOPKC(ECC_T1, pParam->curveParam.pN, byteLenN);

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T0, ECC_P);
    uint32_t zeroFlag_checkP = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUXCLPKC_FP_CALC_OP1_CMP(ECC_T1, ECC_N);
    uint32_t zeroFlag_checkN = MCUXCLPKC_WAITFORFINISH_GETZERO();

    /* Check signature R again by CPU. */
    uint8_t *pImportR = MCUXCLPKC_OFFSET2PTR(pOperands[ECC_S3]);
    uint8_t *pCalcR   = MCUXCLPKC_OFFSET2PTR(pOperands[WEIER_X1]);
    mcuxCsslParamIntegrity_Checksum_t compareR_paramChkSum = mcuxCsslParamIntegrity_Protect(3u, pImportR, pCalcR, operandSize);
    MCUX_CSSL_FP_FUNCTION_CALL(cmpareR_result, mcuxCsslMemory_Compare(compareR_paramChkSum, pImportR, pCalcR, operandSize));

    if (   (MCUXCSSLMEMORY_STATUS_EQUAL == cmpareR_result)
        && (zeroFlag_checkP == MCUXCLPKC_FLAG_ZERO)
        && (zeroFlag_checkN == MCUXCLPKC_FLAG_ZERO) )
    {

        /**********************************************************/
        /* Clean up and exit                                      */
        /**********************************************************/

        /* Export the calculated r. */
        MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pParam->pOutputR, WEIER_X1, byteLenN);

        mcuxClSession_freeWords_pkcWa(pSession, pCpuWorkarea->wordNumPkcWa);
        MCUXCLPKC_FP_DEINITIALIZE_RELEASE(pSession, &pCpuWorkarea->pkcStateBackup,
            mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);

        mcuxClSession_freeWords_cpuWa(pSession, pCpuWorkarea->wordNumCpuWa);

        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_Verify, MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK,
            MCUXCLECC_FP_VERIFY_INIT,
            MCUXCLECC_FP_VERIFY_PREPARE_AND_CHECK,
            MCUXCLECC_FP_VERIFY_CALC_P1,
            MCUXCLECC_FP_VERIFY_CALC_P2,
            MCUXCLECC_FP_VERIFY_CALC_P1_ADD_P2,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportBigEndianToPkc),
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUXCLPKC_FP_CALLED_CALC_OP1_CMP,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxCsslMemory_Compare),
            /* Clean up and exit */
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),
            MCUXCLPKC_FP_CALLED_DEINITIALIZE_RELEASE);
    }

    /* Results of checking R are inconsistent, or p or n got modified. */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Verify, MCUXCLECC_STATUS_FAULT_ATTACK);
}


