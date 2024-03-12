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

/** @file  mcuxClOsccaSm2_Signature_Internal.c
 *  @brief mcuxClOsccaSm2: implementation of the internal functions of the mcuxClOsccaSm2 signature
 */
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClMemory.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxClSignature.h>
#include <mcuxClRandom.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClSignature_Internal.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_Internal_Init)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Signature_Internal_Init(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  uint16_t phase
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_Internal_Init);

    /******************************************************************/
    /* Step 1: Initialization                                         */
    /******************************************************************/
    /* Set up domain parameters */
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);
    uint32_t byteCountN = pSm2DomainParams->n.wNumBytes;

    if((phase & (~MCUXCLOSCCASM2_SIGN_PHASE_INIT_MASK)) != 0u)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_INIT) == MCUXCLOSCCASM2_SIGN_PHASE_INIT)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, pSm2DomainParams, 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
        if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(pSm2DomainParams));

        MCUX_CSSL_FP_FUNCTION_CALL(genZRetSign,mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
        if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZRetSign)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
    }

    uint32_t loopCounter1 = 0U;
    uint32_t loopCounter2 = 0U;
    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS) == MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS)
    {
        /******************************************************************/
        /* Step 2: Process point multiplication:                          */
        /*         get a random k and the corresponding kG                */
        /******************************************************************/
        /* import the point G */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1, pSm2DomainParams->pG, pSm2DomainParams->p.wNumBytes));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
                pSm2DomainParams->pG + pSm2DomainParams->p.wNumBytes, pSm2DomainParams->p.wNumBytes));

        while(loopCounter1 < UINT32_MAX)
        {
            ++loopCounter1;
            MCUX_CSSL_FP_FUNCTION_CALL(SM2SignRngRet, mcuxClOsccaSm2_EccGenRandomBytes(session, TI_scalar, byteCountN));
            if (MCUXCLOSCCASM2_STATUS_ECCGENRAND_OK != SM2SignRngRet)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
            }
            /* make sure the k is at [1, n-1] */
            MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_scalar, TI_n);
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
            if (false == MCUXCLOSCCAPKC_GETCARRY())
            {
                continue;
            }

            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("loopCounter2 can't wrap, because it always smaller than loopCounter1.")
            ++loopCounter2;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
            MCUXCLOSCCAPKC_FXIOP1_SUB_YC(TI_s, TI_scalar, 1U);
            MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
            if (true == MCUXCLOSCCAPKC_GETCARRY())
            {
                continue;
            }
            else
            {
                break;
            }
        }
        if (UINT32_MAX == loopCounter1)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
        if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL(ret, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
        if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == ret)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_Internal_Init, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_INIT) == MCUXCLOSCCASM2_SIGN_PHASE_INIT),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ)),
                                MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS) == MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                              loopCounter1 * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenRandomBytes)
                                                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)
                                                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                              loopCounter2 * ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)
                                                             + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine)));

}


MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxCl_InputBuffer_t pIn,
  uint8_t * const pPrivateKeyInverse
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS);

    /******************************************************************/
    /* Step 1: Initialization                                         */
    /******************************************************************/
    /* Set up SM2 key */
    /* Set up domain parameters */
    uint8_t* pKey = mcuxClKey_getKeyData(key);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);
    uint32_t byteCountN = pSm2DomainParams->n.wNumBytes;

    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    if ((NULL == pIn) || (NULL == pPrivateKeyInverse))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
    }

    /* Import Digest again and compute r for verification */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_e, pIn, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, bufferSize));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *) mcuxClOsccaSm2_FUP_Sign_Double_Check_r,
            MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_Sign_Double_Check_r)));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(ret, mcuxClOsccaSm2_RobustCompareToZero(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_s]), byteCountN));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != ret)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /******************************************************************/
    /* Step 2: Compute s and check that s > 0                         */
    /******************************************************************/
    /* d' = d + phi1
     * k' = k * Inverse(phi) mod n
     * T = Inverse(d + 1) + phi2
     * A = (k' + phi2) * phi - phi2 * phi - d' * sign_r
     * s = (T * A - A * phi2 + sign_r * phi1 * T - sign_r * phi1 * phir2) mod n
     */

    /* get the inverse of phi */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_ComputeModInv(MCUXCLOSCCAPKC_PKCPACKARGS(TI_phi, TI_v, TI_n, TI_s), TI_u));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_SecureImport(TI_d, pKey, byteCountN, bufferSize));

    /* get the random phi1 */
    MCUX_CSSL_FP_FUNCTION_CALL(randRetSign, mcuxClRandom_ncGenerate(session, MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_u]), operandSize));
    if (MCUXCLRANDOM_STATUS_OK != randRetSign)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Compute d', k' to TI_dDash and TI_kDash */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram( (const void *) mcuxClOsccaSm2_FUP_Sign_Prepare_KD,
                                             MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_Sign_Prepare_KD)));

    /* Import d again and verify it */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_SecureImport(TI_t, pKey, byteCountN, bufferSize));
    MCUXCLOSCCAPKC_FXIMC1_MADD(TI_v, TI_u, TI_t, TI_nshift);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    MCUX_CSSL_FP_FUNCTION_CALL(SM2SignComBoRet, mcuxClOsccaSm2_RobustCompareBoolean( MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_v]),
                                                    MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_s]), operandSize));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2SignComBoRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_v]) + (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_s]) +
                    (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL + operandSize);

    /* Secure import (d+1)^{-1} */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_SecureImport(TI_d_inv, pPrivateKeyInverse, byteCountN, bufferSize));

    /* get the random phi2 */
    MCUX_CSSL_FP_FUNCTION_CALL(randRetSign2, mcuxClRandom_ncGenerate(session, MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]), operandSize));
    if (MCUXCLRANDOM_STATUS_OK != randRetSign2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *) mcuxClOsccaSm2_FUP_Sign_Compute_s, MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_Sign_Compute_s)));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    /******************************************************************/
    /* Step 3: Re-import modulus and compare to detect FA             */
    /******************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_t, pSm2DomainParams->n.pMPInt, byteCountN, bufferSize));
    MCUXCLOSCCAPKC_FXIOP1_SUB(TI_t, TI_t, TI_n);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    if (false == MCUXCLOSCCAPKC_GETZERO())
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Check that s > 0 */
    MCUX_CSSL_FP_FUNCTION_CALL(retS, mcuxClOsccaSm2_RobustCompareToZero(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_sig_s]), byteCountN));
    if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL == retS)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
    }
    MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_sig_s]) + 2u * byteCountN + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL +
                    (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_s]) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                              3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecureImport),
                                              3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                              4u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeModInv),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_Internal_Finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Signature_Internal_Finish(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  uint16_t phase,
  mcuxCl_InputBuffer_t pIn,
  uint8_t * const pPrivateKeyInverse,
  mcuxCl_Buffer_t pSignature,
  uint32_t * const pSignatureSize
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_Internal_Finish);

    /******************************************************************/
    /* Step 1: Initialization                                         */
    /******************************************************************/
    /* Set up domain parameters */
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);
    uint32_t byteCountN = pSm2DomainParams->n.wNumBytes;

    if((phase & (~MCUXCLOSCCASM2_SIGN_PHASE_FINAL_MASK)) != 0u)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /******************************************************************/
    /* Step 2: Compute private key inverse                            */
    /******************************************************************/
    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_FINAL_INIT) == MCUXCLOSCCASM2_SIGN_PHASE_FINAL_INIT)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, pSm2DomainParams, 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
        if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(pSm2DomainParams));
    }

    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    /******************************************************************/
    /* Step 3: set r = Q.x + e mod n and check that r>0 and r + k > 0 */
    /******************************************************************/
    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R) == MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R)
    {
        if (NULL == pIn)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
        }

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_e, pIn, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3, bufferSize));

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram((const void *) mcuxClOsccaSm2_FUP_Sign_Check_r,
                                                       MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_Sign_Check_r)));

        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

        /* Check that r > 0 */
        MCUX_CSSL_FP_FUNCTION_CALL(retX, mcuxClOsccaSm2_RobustCompareToZero(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_sig_r]), byteCountN));
        if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL == retX)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
        }
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL + (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_sig_r]) + byteCountN);
    }

    /* Check that r + k > 0 */
    /* Generate a random number phi */
    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK) == MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(randRetSign, mcuxClRandom_ncGenerate(session, MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]), operandSize));
        if (MCUXCLRANDOM_STATUS_OK != randRetSign)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        /* Check that (r * phi + k * phi) > 0 */
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram( (const void *)mcuxClOsccaSm2_FUP_Sign_RPlusK,
                                                 MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_Sign_RPlusK)));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

        MCUX_CSSL_FP_FUNCTION_CALL(retXPlusK, mcuxClOsccaSm2_RobustCompareToZero(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]), byteCountN));
        if(MCUXCLOSCCASM2_STATUS_CMP_EQUAL == retXPlusK)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
        }
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL + (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + byteCountN);
    }

    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S) == MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(retComputeS, mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS(session, key, pIn, pPrivateKeyInverse));
        if(MCUXCLOSCCASM2_STATUS_OK != retComputeS)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, retComputeS);
        }
    }

    if((phase & MCUXCLOSCCASM2_SIGN_PHASE_EXPORT) == MCUXCLOSCCASM2_SIGN_PHASE_EXPORT)
    {
        if (NULL == pSignature || NULL == pSignatureSize)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE);
        }
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_sig_r, (uint8_t*)pSignature, byteCountN));
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_sig_s, (uint8_t*)pSignature + byteCountN, byteCountN));
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(*pSignatureSize, 0u, (uint32_t)pSm2DomainParams->p.wNumBytes, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS)
        MCUX_CSSL_ANALYSIS_ASSERT_PARAMETER(byteCountN, 8u, 80u, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS)
        *pSignatureSize += (uint32_t)byteCountN * 2U;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_Internal_Finish, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                            MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_FINAL_INIT) == MCUXCLOSCCASM2_SIGN_PHASE_FINAL_INIT),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters)),
                            MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R) == MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero)),
                            MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK) == MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero)),
                            MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S) == MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S),
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Finish_ComputeS)),
                            MCUX_CSSL_FP_CONDITIONAL(((phase & MCUXCLOSCCASM2_SIGN_PHASE_EXPORT) == MCUXCLOSCCASM2_SIGN_PHASE_EXPORT),
                                              2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export)));
}
