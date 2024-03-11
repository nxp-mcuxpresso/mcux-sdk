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

/** @file  mcuxClOsccaSm2_Signature_PreHash.c
 *  @brief mcuxClOsccaSm2: implementation of SM2 prehash function
 */

#include <mcuxClOsccaSm3.h>
#include <mcuxClOsccaSm2.h>
#include <mcuxClSession.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaSm2_Internal.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm2_Signature_PreHash)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm2_Status_t) mcuxClOsccaSm2_Signature_PreHash(
    mcuxClSession_Handle_t             session,
    mcuxClKey_Handle_t                 key,
    mcuxCl_InputBuffer_t               pIdentifier,
    uint16_t                          identifierSize,
    mcuxCl_Buffer_t                    pPrehash,
    uint32_t * const                  prehashSize
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm2_Signature_PreHash);

    /****************************************************************/
    /* Preparation: setup SM2 key                                   */
    /****************************************************************/
    /* Set up SM2 key, to be used internally in SM2 functions */
    /* Set up domain parameters, to be used internally in SM2 functions */
    uint8_t* pPublicKey = mcuxClKey_getKeyData(key);
    mcuxClOsccaSm2_DomainParam_t *pSm2DomainParams = (mcuxClOsccaSm2_DomainParam_t *) mcuxClKey_getTypeInfo(key);

    /****************************************************************/
    /* OSCCA SM2 prehash compute                                    */
    /****************************************************************/

    /* Create parameter structure for function mcuxClOsccaSm2_ComputePrehash */
    mcuxClOsccaSm2_ComputePrehash_Param_t paramsPreHash;

    MCUXCLOSCCASM2_FP_DOMAINPARAMETER_COPY(paramsPreHash.domainParameters, (*pSm2DomainParams));
    paramsPreHash.pIdentifier = pIdentifier;
    paramsPreHash.identifierLength = identifierSize;
    paramsPreHash.pPublicKey = pPublicKey;
    paramsPreHash.pPrehash = pPrehash;

    /* Call function mcuxClOsccaSm2_ComputePrehash */
    MCUX_CSSL_FP_FUNCTION_CALL(SM2PreHashRet, mcuxClOsccaSm2_ComputePrehash(session, &paramsPreHash));
    if(MCUXCLOSCCASM2_STATUS_COMPUTE_PREHASH_OK != SM2PreHashRet)
    {
        /* FA is the only negative return code from mcuxClOsccaSm2_ComputePrehash. */
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm2_Signature_PreHash, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP("Caller should set *prehashSize properly to make sure not wrap.")
    *prehashSize += MCUXCLOSCCASM3_OUTPUT_SIZE_SM3;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaSm2_Signature_PreHash, MCUXCLOSCCASM2_STATUS_OK, MCUXCLOSCCASM2_STATUS_FAULT_ATTACK,
                                              MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_ComputePrehash));

}
