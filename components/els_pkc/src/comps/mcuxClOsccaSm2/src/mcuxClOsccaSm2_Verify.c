/*--------------------------------------------------------------------------*/
/* Copyright 2018-2024 NXP                                                  */
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
 * @file: mcuxClOsccaSm2_Verify.c
 * @brief: SM2 Signature Verification
 */

#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxClSignature.h>
#include <mcuxClOscca_Types.h>
#include <mcuxClOscca_PlatformTypes.h>
#include <mcuxClOscca_Memory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>
#include <internal/mcuxClSignature_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Verify_Init)
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Verify_Init(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    mcuxCl_InputBuffer_t pSignature
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Verify_Init);

    /* Set up domain parameters, to be used internally in SM2 functions */
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);

    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, pSm2DomainParams, 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    uint32_t bufferSize = MCUXCLOSCCAPKC_PS1_GETOPLEN() + MCUXCLOSCCAPKC_WORD_SIZE;

    /* prepare the ECC environment */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(pSm2DomainParams));
    MCUX_CSSL_FP_FUNCTION_CALL(genZRetVerify, mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
    if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZRetVerify)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* check the s */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_scalar, pSignature + pSm2DomainParams->n.wNumBytes,
            pSm2DomainParams->n.wNumBytes, bufferSize));

    /* make sure the s is at [1, n-1] */
    MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_scalar, TI_n);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    if (MCUXCLOSCCAPKC_GETCARRY() == false)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART);
    }

    MCUXCLOSCCAPKC_FXIOP1_SUB_YC(TI_s, TI_scalar, 1U);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    if (MCUXCLOSCCAPKC_GETCARRY() == true)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish));
    }

    /* import the point G */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1,
            pSm2DomainParams->pG, pSm2DomainParams->p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
            pSm2DomainParams->pG + pSm2DomainParams->p.wNumBytes,
            pSm2DomainParams->p.wNumBytes));

    /* compute the sG */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointMultMontgomery((uint32_t)TI_scalar));
    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyJacPo1,mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2VerifyJacPo1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck));
    }

    /* save the sG */
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(TI_tmpx, TI_xa, 0);
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(TI_tmpy, TI_ya, 0);
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(TI_tmpz, TI_z1, 0);
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(TI_tmpconz, TI_z, 0);

    /* check the r */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_scalar1, pSignature, pSm2DomainParams->n.wNumBytes, bufferSize));
    /* make sure the r is at [1, n-1] */
    MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_scalar1, TI_n);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    if (MCUXCLOSCCAPKC_GETCARRY() == false)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART,
                                                                    6u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import));
    }

    MCUXCLOSCCAPKC_FXIOP1_SUB_YC(TI_s, TI_scalar1, 1U);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
    if (MCUXCLOSCCAPKC_GETCARRY() == true)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART,
                                                                    7u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Verify_Init, MCUXCLOSCCASM2_STATUS_OK,
                            MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART,
                            MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_SECOND_PART);
}

/**
 * For a given elliptic curve E with base point G and a signature (r,s) calculated from a message digest e,
 * using the key pair (d,Q) the function mcuxClOsccaSm2_Verify checks whether the signature is valid
 *
 * Returns:
 *  - MCUXCLOSCCASM2_STATUS_OK                    if the signature has been successfully validated
 *  - MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE     if the signature is invalid
 *  - MCUXCLOSCCASM2_STATUS_FAULT_ATTACK          if a fault attack was detected, and also invalid inputs
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Verify, mcuxClSignature_VerifyFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Verify(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    mcuxClSignature_Mode_t mode UNUSED_PARAM,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_InputBuffer_t pSignature,
    uint32_t signatureSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Verify);
    uint16_t *pOperands;
    uint32_t operandSize, bufferSize;

    /*****************************************************/
    /* Perform verify operation                          */
    /*****************************************************/
    /* Set up SM2 key, to be used internally in SM2 functions */
    /* Set up domain parameters, to be used internally in SM2 functions */
    uint8_t* pPublicKey = mcuxClKey_getKeyData(key);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);
    uint32_t pkcWaWordSizeUsed = MCUXCLOSCCASM2_VERIFY_SIZEOF_WA_PKC(pSm2DomainParams->p.wNumBytes, pSm2DomainParams->n.wNumBytes) / sizeof(uint32_t);

    /* For sm2 sign, the pIn is the digest, length is MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 */
    if((((uint32_t)pSm2DomainParams->n.wNumBytes * 2U) != signatureSize) || (MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 != inSize))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS);
    }

    MCUXCLOSCCASM2_FP_REQUEST_PKC(session, mcuxClOsccaSm2_Verify);

    MCUX_CSSL_FP_FUNCTION_CALL(initRet, mcuxClOsccaSm2_Verify_Init(session, key, pSignature));
    if (MCUXCLOSCCASM2_STATUS_FAULT_ATTACK == initRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    if (MCUXCLOSCCASM2_STATUS_OK != initRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    /* compute the r + s % n */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
                (const void*)mcuxClOsccaSm2_FUP_CheckRPlusS,
                MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_CheckRPlusS)));
    /* make sure the r + s % n != 0 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyRobCom1,mcuxClOsccaSm2_RobustCompareToZero(MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]), operandSize));
    if (MCUXCLOSCCASM2_STATUS_CMP_EQUAL == SM2VerifyRobCom1)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);

    }

    /* import the public key */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1, pPublicKey, pSm2DomainParams->p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg, pPublicKey + pSm2DomainParams->p.wNumBytes,
            pSm2DomainParams->p.wNumBytes));

    /* check if the pubkey is valid */
    MCUXCLOSCCAPKC_FXIOP1_NEG(TI_sz1_dash, TI_modulus);
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyJacPo2,mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2VerifyJacPo2)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    /* computer tP */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointMultMontgomery((uint32_t)TI_scalar));
    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyJacPo3,mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2VerifyJacPo3)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }
    /*
     * convert tP and retransfer it to common-Z jacobian coordinate
     */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(TI_z, TI_tmpconz, 0);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccTransAffinePoint2Jac());

    /* compute the sG + tP */
    pOperands[TI_x0] = pOperands[TI_xa];
    pOperands[TI_y0] = pOperands[TI_ya];
    pOperands[TI_xa] = pOperands[TI_tmpx];
    pOperands[TI_ya] = pOperands[TI_tmpy];
    pOperands[TI_z1] = pOperands[TI_tmpz];
    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyAD1,mcuxClOsccaSm2_EccPointAddOrDouble());
    if (MCUXCLOSCCASM2_STATUS_POINTADD_INFINITE == SM2VerifyAD1)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL);
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery),
                                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                                    2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccTransAffinePoint2Jac),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAddOrDouble),
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_s, pIn, inSize, bufferSize));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_u, pSignature, pSm2DomainParams->n.wNumBytes, bufferSize));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_StartFupProgram(
                (const void*)mcuxClOsccaSm2_FUP_CheckSignature,
                MCUXCLOSCCAPKC_FUP_LEN(mcuxClOsccaSm2_FUP_CheckSignature)));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());

    MCUX_CSSL_FP_FUNCTION_CALL(SM2VerifyRobCom2,mcuxClOsccaSm2_RobustCompareToZero((uint8_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_v]), operandSize));
    if ((MCUXCLOSCCASM2_STATUS_CMP_EQUAL != SM2VerifyRobCom2) || (!MCUXCLOSCCAPKC_GETZERO()))
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Verify */
        mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);
        /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
        MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + 2u * (operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL) +
                        (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_v]));
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
        MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_FINAL_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);

    }

    /* Need to add mcuxClOsccaSm2_RobustCompareToZero input param before clear functions */
    MCUX_CSSL_SC_SUB((uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_t]) + 2u * operandSize + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL +
                    (uint32_t)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[TI_v]) + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL);



    /* Free workarea allocated in mcuxClOsccaSm2_Verify */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, pkcWaWordSizeUsed);

    MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Verify);
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Verify, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Verify_Init),
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART,
                                                                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_FINAL_PART,
                                                                    MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                                    MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
}

