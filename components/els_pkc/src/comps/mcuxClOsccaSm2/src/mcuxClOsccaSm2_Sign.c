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

/** @file  mcuxClOsccaSm2_Sign.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 Sign function
 */

#include <mcuxClToolchain.h>
#include <mcuxClMemory.h>
#include <mcuxClRandom.h>
#include <mcuxClSession.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxClSignature.h>
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

/**
 * The function mcuxClOsccaSm2_Sign performs an SM2 Signature Generation according
 * to " State Standard SM2 Algorithm for the People's Republic of China ".
 *
 * Returns:
 *  -  MCUXCLOSCCASM2_STATUS_OK                   if signature is generated successfully;
 *  -  MCUXCLOSCCASM2_STATUS_INVALID_PARAMS       if parameters are invalid;
 *  -  MCUXCLOSCCASM2_STATUS_RNG_ERROR            if random number (DRBG / PRNG) error (unexpected behavior);
 *  -  MCUXCLOSCCASM2_STATUS_FAULT_ATTACK         if fault attack (unexpected behavior) is detected.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Sign, mcuxClSignature_SignFct_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Sign(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    mcuxClSignature_Mode_t mode UNUSED_PARAM,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inSize,
    mcuxCl_Buffer_t pSignature,
    uint32_t * const pSignatureSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Sign);

    /* Check if key matches the algorithm */
    if (MCUXCLKEY_ALGO_ID_SM2 != mcuxClKey_getAlgorithm(key))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS);
    }
    /* Set up SM2 key */
    /* Set up domain parameters */
    uint8_t* privateKey  = mcuxClKey_getKeyData(key);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);
    uint32_t byteCountN = pSm2DomainParams->n.wNumBytes;

    /*****************************************************/
    /* Perform sign operation                            */
    /*****************************************************/
    /* For sm2 sign, the pIn is the digest, length is MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 */
    if(MCUXCLOSCCASM3_OUTPUT_SIZE_SM3 != inSize)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_INVALID_PARAMS);
    }

    /******************************************************************/
    /* Step 1: Compute private key inverse                            */
    /******************************************************************/
    /* Create buffer for private key inverse */
    uint8_t * pPrivateKeyInverse = (uint8_t *)mcuxClSession_allocateWords_cpuWa(session, (byteCountN + MCUXCLOSCCA_SIZE_ALIGN_OFFSET)/ (sizeof(uint32_t)));
    if (NULL == pPrivateKeyInverse)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUXCLOSCCASM2_FP_REQUEST_PKC(session, mcuxClOsccaSm2_Sign);

    /* Create parameter structure for function mcuxClOsccaSm2_InvertPrivateKey */
    mcuxClOsccaSm2_InvertPrivateKey_Param_t paramsInvPrivKey;
    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsInvPrivKey.domainParameters, (*pSm2DomainParams));
    paramsInvPrivKey.pPrivateKey = privateKey;
    paramsInvPrivKey.pPrivateKeyInverse = pPrivateKeyInverse;

    /* Call function mcuxClOsccaSm2_InvertPrivateKey */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2InvPriKeyRet, mcuxClOsccaSm2_InvertPrivateKey(session, &paramsInvPrivKey));
    if (MCUXCLOSCCASM2_STATUS_INVERT_PRIVATE_KEY_OK != SM2InvPriKeyRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /****************************************************************/
    /* Step 2: Set-up local structure                               */
    /****************************************************************/
    MCUX_CSSL_FP_FUNCTION_CALL(initRet, mcuxClOsccaSm2_Signature_Internal_Init(session, key, MCUXCLOSCCASM2_SIGN_PHASE_INIT));
    if (MCUXCLOSCCASM2_STATUS_OK != initRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    uint32_t retX, retXPlusK, retS;
    /* Variables related to flow protection to count execution of loops */
    uint32_t mainLoopCounterCheck = 0U;
    uint32_t loopCounterFirstCheck = 0U;
    uint32_t loopCounterSecondCheck = 0U;

    do  // while(s == 0)
    {
        ++mainLoopCounterCheck;
        do  // while(x + k == 0)
        {
            ++loopCounterFirstCheck;
            do  // while(x == 0)
            {
                ++loopCounterSecondCheck;
                /******************************************************************/
                /* Step 2: Process point multiplication:                          */
                /*         get a random k and the corresponding kG                */
                /******************************************************************/
                MCUX_CSSL_FP_FUNCTION_CALL(signKeyGenRet, mcuxClOsccaSm2_Signature_Internal_Init(session, key, MCUXCLOSCCASM2_SIGN_PHASE_KEYGENPROCESS));
                if (MCUXCLOSCCASM2_STATUS_OK != signKeyGenRet)
                {
                    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
                }

                /******************************************************************/
                /* Step 3: set r = Q.x + e mod n and check that r>0 and r + k > 0 */
                /******************************************************************/
                MCUX_CSSL_FP_FUNCTION_CALL(checkRRet, mcuxClOsccaSm2_Signature_Internal_Finish(session, key, MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_R, pIn, NULL, NULL, NULL));
                retX = checkRRet;
            }while((MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE == retX) && (loopCounterSecondCheck < UINT32_MAX));

            if((MCUXCLOSCCASM2_STATUS_OK != retX) || (loopCounterSecondCheck == UINT32_MAX))
            {
                MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
            }

            /* Check that r + k > 0 */
            MCUX_CSSL_FP_FUNCTION_CALL(checkRPlusKRet, mcuxClOsccaSm2_Signature_Internal_Finish(session, key, MCUXCLOSCCASM2_SIGN_PHASE_KEYCHECK_RPLUSK, NULL, NULL, NULL, NULL));
            retXPlusK = checkRPlusKRet;

        }while ((MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE == retXPlusK) && (loopCounterFirstCheck < UINT32_MAX));

        if((MCUXCLOSCCASM2_STATUS_OK != retXPlusK) || (loopCounterFirstCheck == UINT32_MAX))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
        }

        /* Import Digest again and compute r for verification */
        /******************************************************************/
        /* Step 5: Compute s and check that s > 0                         */
        /******************************************************************/
        MCUX_CSSL_FP_FUNCTION_CALL(computeSRet, mcuxClOsccaSm2_Signature_Internal_Finish(session, key, MCUXCLOSCCASM2_SIGN_PHASE_COMPUTE_S, pIn, pPrivateKeyInverse, NULL, NULL));
        retS = computeSRet;
    } while((MCUXCLOSCCASM2_STATUS_INVALID_SIGNATURE == retS) && (mainLoopCounterCheck < UINT32_MAX));

    if ((MCUXCLOSCCASM2_STATUS_OK != retS) || (mainLoopCounterCheck == UINT32_MAX))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(exportRet, mcuxClOsccaSm2_Signature_Internal_Finish(session, key, MCUXCLOSCCASM2_SIGN_PHASE_EXPORT, NULL, NULL, pSignature, pSignatureSize));
    if (MCUXCLOSCCASM2_STATUS_OK != exportRet)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    /* Free workarea allocated in mcuxClOsccaSm2_Sign */
    mcuxClSession_freeWords_cpuWa(session, (byteCountN + MCUXCLOSCCASM2_COMMON_SIZEOF_WA_CPU + MCUXCLOSCCA_SIZE_ALIGN_OFFSET) / sizeof(uint32_t));
    mcuxClSession_freeWords_pkcWa(session, MCUXCLOSCCASM2_SIGN_SIZEOF_WA_PKC(pSm2DomainParams->p.wNumBytes, pSm2DomainParams->n.wNumBytes) / sizeof(uint32_t));

    MCUXCLOSCCASM2_FP_RELEASE_PKC(session, mcuxClOsccaSm2_Sign);

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Sign, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                                  loopCounterSecondCheck * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Init) +
                                                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Finish)),
                                                  (loopCounterFirstCheck + mainLoopCounterCheck) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Finish),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Finish),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Signature_Internal_Init),
                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_InvertPrivateKey),
                                                  MCUXCLOSCCASM2_FP_CALLED_REQUEST_PKC,
                                                  MCUXCLOSCCASM2_FP_CALLED_RELEASE_PKC);
}
