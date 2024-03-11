/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/** @file  mcuxClOsccaSm2_GenerateKeyPair.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 Key Generation function in KEY API
 */

#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClRandom.h>
#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <internal/mcuxClOsccaPkc_FupMacros.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Types_Internal.h>
#include <internal/mcuxClKey_Functions_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClKey_GenerationDescriptor_t mcuxClKey_GenerationDescriptor_SM2 =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .pKeyGenFct = mcuxClOsccaSm2_GenerateKeyPair,
    .protectionTokenKeyGenFct = MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_GenerateKeyPair),
    .pProtocolDescriptor = NULL
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_GenerateKeyPair, mcuxClKey_KeyGenFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClOsccaSm2_GenerateKeyPair(
    mcuxClSession_Handle_t session,
    mcuxClKey_Generation_t generation,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_GenerateKeyPair);

    /* Verify that the key handles are correctly initialized for the SM2 use case */
    if(MCUXCLKEY_ALGO_ID_SM2 != mcuxClKey_getAlgorithm(privKey)
            || MCUXCLKEY_ALGO_ID_SM2 != mcuxClKey_getAlgorithm(pubKey)
            || mcuxClKey_getTypeInfo(privKey) != mcuxClKey_getTypeInfo(pubKey)
            || MCUXCLKEY_ALGO_ID_PRIVATE_KEY != mcuxClKey_getKeyUsage(privKey)
            || MCUXCLKEY_ALGO_ID_PUBLIC_KEY != mcuxClKey_getKeyUsage(pubKey)
            )
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAILURE);
    }

    /* Unused input parameters */
    (void) generation;

    /* Set up domain parameters, to be used internally in SM2 functions */
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(privKey);
    uint8_t *pPrivateKey = mcuxClKey_getKeyData(privKey);
    uint8_t *pPublicKey = mcuxClKey_getKeyData(pubKey);

    MCUXCLBUFFER_INIT_RW(pPrivKeyBuf, NULL, pPrivateKey, pSm2DomainParams->n.wNumBytes);
    MCUXCLBUFFER_INIT_RW(pPubKeyBuf, NULL, pPublicKey, 2u * pSm2DomainParams->p.wNumBytes);
    /* Initializ the privateKey buffer with random data */
    MCUX_CSSL_FP_FUNCTION_CALL(randomGenRet, mcuxClRandom_ncGenerate(session, pPrivKeyBuf, pSm2DomainParams->n.wNumBytes));
    if (MCUXCLRANDOM_STATUS_OK != randomGenRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_ERROR,
                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate));
    }

    /****************************************************************/
    /* OSCCA SM2 private and public key generation                  */
    /****************************************************************/
    MCUXCLOSCCASM2_FP_REQUEST_PKC(session, mcuxClOsccaSm2_GenerateKeyPair);

    MCUX_CSSL_FP_FUNCTION_CALL(eccInitRet, mcuxClOsccaSm2_EccInit(session, pSm2DomainParams, 0,
            MCUXCLOSCCAPKC_PKCPACKARGS(0, 0, MCUXCLOSCCASM2_NO_OF_VIRTUALS, MCUXCLOSCCASM2_NO_OF_BUFFERS)));
    if (MCUXCLOSCCASM2_STATUS_ECCINIT_OK != eccInitRet)
    {
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_GenerateKeyPair);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAILURE,
                                  MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                  MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit));
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPrepareParameters(pSm2DomainParams));

    MCUX_CSSL_FP_FUNCTION_CALL(genZRetKeyGen, mcuxClOsccaSm2_EccGenerateZ(session, TI_z, TI_s));
    if (MCUXCLOSCCASM2_STATUS_ECCGENZ_OK != genZRetKeyGen)
    {
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_GenerateKeyPair);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAILURE,
                                  MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                  MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit));
    }

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointWithInit(TI_sx1, pSm2DomainParams->pG, pSm2DomainParams->p.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccImportInputPointYNegNoInit(TI_y_neg, pSm2DomainParams->pG + pSm2DomainParams->p.wNumBytes, pSm2DomainParams->p.wNumBytes));
    uint16_t * pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    pOperands[TI_xa] = pOperands[TI_sx1];
    pOperands[TI_ya] = pOperands[TI_sy1];
    pOperands[TI_z1] = pOperands[TI_sz1_dash];
    MCUX_CSSL_FP_FUNCTION_CALL(KeyCheckRet, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyCheckRet)
    {
        MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_GenerateKeyPair);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_INVALID_INPUT,
                                  MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                  MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC,
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit));
    }

    /* Variables related to flow protection to count execution of loops */
    uint32_t mainLoopCounterCheck1 = 0u;
    uint32_t mainLoopCounterCheck2 = 0u;

    /* generate a random k */
    do
    {
        ++mainLoopCounterCheck1;

        MCUX_CSSL_FP_FUNCTION_CALL(KeyGenRngRet, mcuxClOsccaSm2_EccGenRandomBytes(session, TI_scalar, pSm2DomainParams->n.wNumBytes));
        if (MCUXCLOSCCASM2_STATUS_ECCGENRAND_OK != KeyGenRngRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAULT_ATTACK);
        }
        MCUXCLOSCCAPKC_FXIOP1_ADD_YC(TI_t, TI_scalar, 1);
        /*
         * make sure the k is at [1, n-2]
         * t = _scalar + 1 < n <--> _scalar < n - 1
        */
        MCUXCLOSCCAPKC_FXIOP1_CMP_YZ(TI_t, TI_n);
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
    }while(mainLoopCounterCheck1 < UINT32_MAX);

    if (UINT32_MAX == mainLoopCounterCheck1)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(pointMulRet, mcuxClOsccaSm2_EccSecurePointMult(session, (uint32_t)TI_scalar));
    if (MCUXCLOSCCASM2_STATUS_SECUREPOINTMULT_OK != pointMulRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL(KeyGenJacRet, mcuxClOsccaSm2_EccJacPointCheck(TI_xa, TI_ya));
    if (MCUXCLOSCCASM2_STATUS_ECCJACPOINT_NOT_EQUAL == KeyGenJacRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_FAULT_ATTACK);
    }
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_EccPointConvert2Affine());

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_SecureExport(TI_scalar, pPrivKeyBuf, pSm2DomainParams->n.wNumBytes));
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_xa, pPubKeyBuf, pSm2DomainParams->p.wNumBytes));
    MCUXCLBUFFER_UPDATE(pPubKeyBuf, pSm2DomainParams->p.wNumBytes);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm2_Export(TI_ya, pPubKeyBuf, pSm2DomainParams->p.wNumBytes));

    /* Free workarea allocated in mcuxClOsccaSm2_GenerateKeyPair */
    mcuxClSession_freeWords_cpuWa(session, MCUXCLOSCCASM2_KEY_GENERATEKEYPAIR_SIZEOF_WA_CPU / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_KEYGEN_SIZEOF_WA_PKC(pSm2DomainParams->p.wNumBytes, pSm2DomainParams->n.wNumBytes) / sizeof(uint32_t));

    MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_GenerateKeyPair);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_GenerateKeyPair, MCUXCLKEY_STATUS_OK, MCUXCLKEY_STATUS_FAULT_ATTACK,
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecureExport),
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult),
                                                         2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck),
                                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine),
                                                         (mainLoopCounterCheck1 * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenRandomBytes)
                                                                                 + 2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)
                                                                                 + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish))
                                                        + mainLoopCounterCheck2 * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)
                                                                                 + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish))
                                                         ),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                                                        MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                        MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
}
