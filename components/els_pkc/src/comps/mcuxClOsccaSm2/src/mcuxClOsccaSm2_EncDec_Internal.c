/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

/** @file  mcuxClOsccaSm2_EncDec_Internal.c
 *  @brief mcuxClOsccaSm2: implementation internal functions of SM2 Encrypt and Decryption function
 */

#include <mcuxClMemory.h>
#include <mcuxClHash.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaSm3.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClOsccaSm2_Internal_Hash.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Encrypt_Internal_PointMult)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Encrypt_Internal_PointMult(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Encrypt_Param_t *pParams,
    uint8_t *pC1
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Encrypt_Internal_PointMult);

    /* Variables related to flow protection to count execution of loops */
    uint32_t mainLoopCounterCheck1 = 0U;
    uint32_t mainLoopCounterCheck2 = 0U;
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(&(pParams->domainParameters)));

    MCUX_CSSL_FP_FUNCTION_CALL(genZEncryptRet, mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
    if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZEncryptRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_FAILURE,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters));
    }

    /* import the point G, need in loop for invalid k case */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1,
            pParams->domainParameters.pG, pParams->domainParameters.p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
            pParams->domainParameters.pG + pParams->domainParameters.p.wNumBytes,
            pParams->domainParameters.p.wNumBytes));

    /* check if the G is valid */
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(SM2EncEccJacRet1, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2EncEccJacRet1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck));

    }

    /* compute the C1
     * Generate a random number k and computer the kG
     */

    while(mainLoopCounterCheck1 < UINT32_MAX)
    {
        ++mainLoopCounterCheck1;
        MCUX_CSSL_FP_FUNCTION_CALL(rngRet, mcuxClOsccaSm2_EccGenRandomBytes(session, TI_scalar, pParams->domainParameters.n.wNumBytes));
        if (MCUXCLOSCCASM2_STATUS_ECCGENRAND_OK != rngRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult,MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        /* make sure the d is at [1, n-1] */
        MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_scalar, TI_n);
        MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaPkc_WaitforFinish());
        if (false == MCUXCLOSCCAPKC_GETCARRY())
        {
            continue;
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("mainLoopCounterCheck2 can't wrap, because it always smaller than mainLoopCounterCheck1.")
        ++mainLoopCounterCheck2;
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
    if (UINT32_MAX == mainLoopCounterCheck1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
    if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2EncEccJacRet2, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL  == SM2EncEccJacRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult,MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    /* save the C1 */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_xa, pC1, pParams->domainParameters.p.wNumBytes));

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_ya, pC1 + pParams->domainParameters.p.wNumBytes, pParams->domainParameters.p.wNumBytes));

    /* import the public key */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1,
            pParams->pPublicKey, pParams->domainParameters.p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
            pParams->pPublicKey + pParams->domainParameters.p.wNumBytes,
            pParams->domainParameters.p.wNumBytes));

    /* check if the pubkey is valid */
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(SM2EncEccJacRet3, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2EncEccJacRet3)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_ENCRYPT_INVALID_PARAMS,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ),
                                                  2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                  2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                  2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export),
                                                  3U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine),
                                                  MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_LOOP);

    }

    /* compute the x2,y2 by k * publickey */
    MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet2, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
    if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(SM2EncEccJacRet4, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == SM2EncEccJacRet4)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult,MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_PointMult, MCUXCLOSCCASM2_STATUS_ENCRYPT_OK,
                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_INIT_POINTMULT);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Encrypt_Internal_Init)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Encrypt_Internal_Init(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Encrypt_Param_t *pParams
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Encrypt_Internal_Init);

    if(NULL == pParams->pC1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAILURE);
    }

    uint32_t cpuWaBy_WOInit = 3U * (uint32_t)pParams->domainParameters.p.wNumBytes + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE + MCUXCLOSCCA_SIZE_ALIGN_OFFSET;
    uint8_t *pX2 = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, ((uint32_t)pParams->domainParameters.p.wNumBytes + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
    if(NULL == pX2)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAILURE);
    }
    uint8_t *pC1 = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, (2U * (uint32_t)pParams->domainParameters.p.wNumBytes + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
    if(NULL == pC1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAILURE);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
    mcuxClOsccaSm2_Internal_EncDecCtx_t* pCtx = (mcuxClOsccaSm2_Internal_EncDecCtx_t*)pParams->pEncDecCtx;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pY2 = (uint8_t *)mcuxClOscca_alignAddressWithOffset(pParams->pEncDecCtx, sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));

    /*
     * cpu workarea layout for STATE_INIT
     * X2 || 0x4 || C1
     */
    *pC1 = MCUXCLOSCCASM2_CRYPTO_UNCOMPRESSED;

    /* inititlize the pkc and ECC parameters */
    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, &(pParams->domainParameters), 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0,
            MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Encrypt_Internal_Init */
        mcuxClSession_freeWords_cpuWa(session, cpuWaBy_WOInit / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAILURE,
                    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit));
    }

    MCUX_CSSL_FP_FUNCTION_CALL(encInitPointMultRet, mcuxClOsccaSm2_Encrypt_Internal_PointMult(session, pParams, pC1 + 1u));
    if (MCUXCLOSCCASM2_STATUS_ENCRYPT_OK != encInitPointMultRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Encrypt_Internal_Init */
        mcuxClSession_freeWords_cpuWa(session, (cpuWaBy_WOInit + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, encInitPointMultRet,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt_Internal_PointMult),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit));
    }

    /* Change endianess of x2 and y2, cause Hash needs big endian representation */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_xa, pX2, pParams->domainParameters.p.wNumBytes));

    /* Backup y2 to the context and perform all necessary operations for INIT PHASE
     * (INITIALIZE hash contexts, update hashCtxT with y2 and finish initialization of the EncDecCtx)
     */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_ya, pY2, pParams->domainParameters.p.wNumBytes));

    MCUX_CSSL_FP_FUNCTION_CALL(SM2EncryptRet1, mcuxClOsccaSm2_SecondPartOfInitPhase(
            session,
            pParams->domainParameters.p.wNumBytes,
            pX2,
            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
            pCtx
            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
            ));
    if (MCUXCLOSCCASM2_STATUS_SECOND_PART_INIT_OK != SM2EncryptRet1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUXCLMEMORY_FP_MEMORY_COPY(pParams->pC1, pC1, (uint32_t)pParams->domainParameters.p.wNumBytes * 2u + MCUXCLOSCCASM2_ENCDEC_FORMAT_INDICATOR_SIZE);

    /* Free workarea allocated in mcuxClOsccaSm2_Encrypt_Internal_Init */
    mcuxClSession_freeWords_cpuWa(session, (cpuWaBy_WOInit + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));
    /* Balance security counter */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Encrypt_Internal_Init,MCUXCLOSCCASM2_STATUS_ENCRYPT_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_INIT_PART);
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Encrypt_Internal_Final)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Encrypt_Internal_Final(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Encrypt_Param_t *pParams
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Encrypt_Internal_Final);

    /* Allocate workarea usage in mcuxClOsccaSm2_Encrypt_Internal_Final */
    uint8_t *pPkcWa = (uint8_t*)mcuxClSession_allocateWords_pkcWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
    if(NULL == pPkcWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAILURE);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
    mcuxClOsccaSm2_Internal_EncDecCtx_t* pCtx = (mcuxClOsccaSm2_Internal_EncDecCtx_t*)pParams->pEncDecCtx;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pY2 = (uint8_t *)mcuxClOscca_alignAddressWithOffset(pParams->pEncDecCtx, sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));
    if (MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE == (pParams->options & MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE))
    {
        uint8_t* pC3 = (uint8_t*)pPkcWa;
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
        if(MCUXCLOSCCASM2_T_ZERO == pCtx->tZeroOrNot)
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        if(MCUXCLOSCCASM2_T_NOT_ZERO != pCtx->tZeroOrNot)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        /*Finalize calculation of C3 by hashing on already initialized context y2*/
        uint32_t hashFin = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx->hashCtxC3, pY2, pParams->domainParameters.p.wNumBytes, pC3, hashFin);
        if(MCUXCLHASH_STATUS_OK != hashFin)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        else
        {
            if(NULL == pParams->pC3)
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
            }
            MCUXCLMEMORY_FP_MEMORY_COPY(pParams->pC3, pC3, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);

            MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t*)pParams->pEncDecCtx,
                        (uint32_t)pParams->domainParameters.p.wNumBytes + sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));
        }
    }
    else
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
        /* Unless it's the FINALIZE case, the CRC shall be set at the end of the function call*/
        MCUXCLOSCCASM2_SET_ENC_DEC_CTX_CRC(pCtx, (uint32_t)pParams->domainParameters.p.wNumBytes);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    }

    /* Free workarea allocated in mcuxClOsccaSm2_Encrypt_Internal_Final */
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
    /* Balance security counter */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Encrypt_Internal_Final,MCUXCLOSCCASM2_STATUS_ENCRYPT_OK,
                                                      MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE == (pParams->options & MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE) ?
                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_FINALIZE_PART : MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCrc_computeCRC16));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Decrypt_Param_t *pParams
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare);
    /* initialize the pkc and ECC parameters */
    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, &(pParams->domainParameters), 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        /* will return FA on upper layer */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare, MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(&(pParams->domainParameters)));

    MCUX_CSSL_FP_FUNCTION_CALL(genZRet, mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
    if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZRet)
    {
        /* will return FA on upper layer */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare, MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare, MCUXCLOSCCASM2_STATUS_INTERNAL_OK,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Decrypt_Param_t *pParams)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult);

    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    uint32_t bufferSize = operandSize + MCUXCLOSCCAPKC_WORD_SIZE;
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    uint8_t const *pC1 = pParams->pC1;
    /* Skip the first format indicator byte */
    pC1++;

    /* import C1 and check it */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1, pC1, pParams->domainParameters.p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg,
            pC1 + pParams->domainParameters.p.wNumBytes,
            pParams->domainParameters.p.wNumBytes));

    /* check if the C1 is valid */
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(EccJacRet1, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == EccJacRet1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult,MCUXCLOSCCASM2_STATUS_DECRYPT_NOK,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck));

    }

    /* import the private key */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Import(TI_scalar, pParams->pPrivateKey, pParams->domainParameters.n.wNumBytes, bufferSize));

    /* compute the d * C1 */
    MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
    if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet)
    {
        /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult */
        /* will return FA on upper layer */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult, MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(EccJacRet2, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == EccJacRet2)
    {
        /* will return FA on upper layer */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult, MCUXCLOSCCASM2_STATUS_INTERNAL_ERROR);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult, MCUXCLOSCCASM2_STATUS_INTERNAL_OK,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Decrypt_Internal_Init)
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Decrypt_Internal_Init(
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Decrypt_Param_t *pParams
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Decrypt_Internal_Init);

    if(NULL == pParams->pC1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* check the first byte of cipher text */
    if (MCUXCLOSCCASM2_CRYPTO_UNCOMPRESSED != pParams->pC1[0])
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_DECRYPT_NOK);
    }

    uint32_t cpuWaBy_WOInit = (uint32_t)pParams->domainParameters.p.wNumBytes + MCUXCLOSCCA_SIZE_ALIGN_OFFSET;
    uint8_t *pCpuWa = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, cpuWaBy_WOInit / sizeof(uint32_t));
    if(NULL == pCpuWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
    mcuxClOsccaSm2_Internal_EncDecCtx_t* pCtx = (mcuxClOsccaSm2_Internal_EncDecCtx_t*)pParams->pEncDecCtx;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pY2 = (uint8_t *)mcuxClOscca_alignAddressWithOffset(pParams->pEncDecCtx, sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));
    /*
     * cpu workarea layout for STATE_INIT
     * X2
     */
    uint8_t *pX2 = pCpuWa;

    /* Initialize the pkc and ECC parameters, note: it will allocate CPU and PKC WA inside */
    MCUX_CSSL_FP_FUNCTION_CALL(eccPrepareRet, mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare(session, pParams));
    if (MCUXCLOSCCASM2_STATUS_INTERNAL_OK != eccPrepareRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* compute the d * C1 */
    MCUX_CSSL_FP_FUNCTION_CALL(DecPointMult, mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult(session, pParams));
    if (MCUXCLOSCCASM2_STATUS_INTERNAL_OK != DecPointMult)
    {
        if (MCUXCLOSCCASM2_STATUS_DECRYPT_NOK != DecPointMult)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Init */
        mcuxClSession_freeWords_cpuWa(session, (cpuWaBy_WOInit + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
        mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init,MCUXCLOSCCASM2_STATUS_DECRYPT_NOK,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult)
                                                  );
    }

    /* Change endianess of x2 and y2, cause Hash needs big endian representation */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_xa, pX2, pParams->domainParameters.p.wNumBytes));

    /*Backup y2 to the context and perform all necessary operations for INIT PHASE
     *(INITIALIZE hash contexts, update hashCtxT with y2 and finish initialization of the EncDecCtx)
     */
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_ya, pY2, pParams->domainParameters.p.wNumBytes));

    MCUX_CSSL_FP_FUNCTION_CALL(DecRet1,mcuxClOsccaSm2_SecondPartOfInitPhase(
            session,
            pParams->domainParameters.p.wNumBytes,
            pX2,
            MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
            pCtx
            MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()
            ));
    if (MCUXCLOSCCASM2_STATUS_SECOND_PART_INIT_OK != DecRet1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Init */
    mcuxClSession_freeWords_cpuWa(session, (cpuWaBy_WOInit + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU) / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_INTERNAL_SIZEOF_WA_PKC(pParams->domainParameters.p.wNumBytes, pParams->domainParameters.n.wNumBytes) / sizeof(uint32_t));

    /* Balance security counter */
     MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Decrypt_Internal_Init, MCUXCLOSCCASM2_STATUS_DECRYPT_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt_Internal_Init_EccPrepare),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Decrypt_Internal_Init_PointMult),
                                                  2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecondPartOfInitPhase));
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Decrypt_Internal_Final)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Decrypt_Internal_Final(
    mcuxClSession_Handle_t session,
    mcuxClOsccaSm2_Decrypt_Param_t *pParams
)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Decrypt_Internal_Final);

    /* Allocate workarea usage in mcuxClOsccaSm2_Decrypt_Internal_Final */
    uint8_t *pPkcWa = (uint8_t*)mcuxClSession_allocateWords_pkcWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
    if(NULL == pPkcWa)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAILURE);
    }
    uint8_t *pC3Local = pPkcWa;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
    mcuxClOsccaSm2_Internal_EncDecCtx_t* pCtx = (mcuxClOsccaSm2_Internal_EncDecCtx_t*)pParams->pEncDecCtx;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    uint8_t *pY2 = (uint8_t *)mcuxClOscca_alignAddressWithOffset(pParams->pEncDecCtx, sizeof(mcuxClOsccaSm2_Internal_EncDecCtx_t));
    if (MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE == (pParams->options & MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE))
    {
        /*****************************************************************************/
        /* Step a: If tZeroOrNot = T_ZERO, return MCUXCLOSCCASM2_STATUS_FAULT_ATTACK. */
        /*****************************************************************************/
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
        if(MCUXCLOSCCASM2_T_NOT_ZERO != pCtx->tZeroOrNot)
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        /*******************************************************************************************************/
        /* Step b: Finalize the calculation of u using hash context HashCtxC3 (use hashing option FINALIZE).   */
        /*******************************************************************************************************/
        /* Switch hash context to hashCtxC3 */
        uint32_t hashFin = MCUXCLHASH_STATUS_FAULT_ATTACK;
        MCUXCLOSCCASM2_FP_CALC_HASHFINALPRO(session, pCtx->hashCtxC3, pY2, pParams->domainParameters.p.wNumBytes, pC3Local, hashFin);
        if(MCUXCLHASH_STATUS_OK != hashFin)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        /****************************************************************************************************************************/
        /* Step c: Robustly import C3, and robustly compare it to pC3Local. If not equal, return MCUXCLOSCCASM2_STATUS_DECRYPT_NOK.    */
        /****************************************************************************************************************************/
        if(NULL == pParams->pC3)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }
        MCUX_CSSL_FP_FUNCTION_CALL(status, mcuxClOsccaSm2_RobustCompareBoolean(pC3Local, pParams->pC3, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3));
        if ((uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL != status)
        {
            MCUX_CSSL_SC_SUB((uint32_t)pC3Local + (uint32_t)pParams->pC3 + (uint32_t)MCUXCLOSCCASM2_STATUS_NOT_EQUAL + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);
            /* Free workarea allocated in mcuxClOsccaSm2_Decrypt_Internal_Final */
            mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
            MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t*)pParams->pEncDecCtx, MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pParams->domainParameters.p.wNumBytes));
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_DECRYPT_NOK,
                                                      MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_FINALIZE_PART,
                                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));

        }
        else
        {
            MCUX_CSSL_SC_SUB((uint32_t)pC3Local + (uint32_t)pParams->pC3 + (uint32_t)MCUXCLOSCCASM2_STATUS_CMP_EQUAL + MCUXCLOSCCASM3_OUTPUT_SIZE_SM3);
            MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t*)pParams->pEncDecCtx, MCUXCLOSCCASM2_ENC_DEC_CTX_SIZE(pParams->domainParameters.p.wNumBytes));
        }
    }
    /********************************************************************************/
    /* If option FINALIZE is not chosen, set the CRC over mcuxClOsccaSm2_EncDecCtx_t */
    /********************************************************************************/
    else
    {
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("Reinterpret the external parameter to internal context structure.")
        /* Unless it's the FINALIZE case, the CRC shall be set at the end of the function call */
        MCUXCLOSCCASM2_SET_ENC_DEC_CTX_CRC(pCtx, pParams->domainParameters.p.wNumBytes);
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
    }

    /* Free workarea allocated in mcuxClOsccaSm2_Encrypt_Internal_Final */
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 / sizeof(uint32_t));
    /* Balance security counter */
     MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Decrypt_Internal_Final, MCUXCLOSCCASM2_STATUS_DECRYPT_OK,
                                                      MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE == (pParams->options & MCUXCLOSCCASM2_OPT_ENC_DEC_STATE_FINALIZE) ?
                    MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_FINALIZE_C3_OK : MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCrc_computeCRC16));
}
