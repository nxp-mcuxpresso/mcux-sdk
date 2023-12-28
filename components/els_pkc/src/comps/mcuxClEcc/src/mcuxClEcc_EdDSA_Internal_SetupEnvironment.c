/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 * @file  mcuxClEcc_EdDSA_Internal_SetupEnvironment.c
 * @brief EdDSA internal setup environment
 */


#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClEcc_EdDSA_Internal.h>


/**
 * This function sets up the general environment used by EdDSA functions.
 * In particular, it sets up the utilized co-processors, prepares the PKC workarea layout,
 * and initializes it for Montgomery arithmetic modulo p and n.
 *
 * Input:
 *  - pSession              Handle for the current CL session
 *  - pCommonDomainParams   Pointer to domain parameter struct passed via API
 *  - noOfBuffers           Number of PKC buffers to be allocated
 *
 * Result:
 *  - The pointer table has been properly setup in CPU workarea and PKC buffers have been allocated
 *  - The PKC state has been backed up in CPU workarea and the PKC has been enabled
 *  - ps1Len = (operandSize, operandSize)
 *  - Buffers ECC_PFULL and ECC_NFULL contain p'||p and n'||n, respectively
 *  - Buffers ECC_PS and ECC_NS contain the p resp. n shifted to the PKC word boundary
 *  - Buffers ECC_PQSQR and ECC_NQSQR contain the R^2 values modulo p and n, respectively
 *  - Virtual pointers ECC_P and ECC_N point to the second PKC word of ECC_PFULL and ECC_NFULL, respectively
 *  - Virtual pointers ECC_ZERO and ECC_ONE have been initialized with 0 and 1, respecitvely
 *  - The domain parameters a and d are stored in buffers ECC_CP0 and ECC_CP1 in MR
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_EdDSA_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_EdDSA_SetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_EdDSA_DomainParams_t *pDomainParams,
    uint8_t noOfBuffers )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_EdDSA_SetupEnvironment);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnvironment,
        mcuxClEcc_SetupEnvironment(pSession, &(pDomainParams->common), noOfBuffers));
    if (MCUXCLECC_STATUS_OK != retSetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retSetupEnvironment, mcuxClEcc_EdDSA_SetupEnvironment);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_SetupEnvironment, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Import curve parameters a and d, convert them to MR modulo p, and store them in buffers ECC_CP0 and ECC_CP1. */
    uint32_t byteLenP = (uint32_t) pDomainParams->common.byteLenP;
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pDomainParams->common.pCurveParam1, byteLenP);
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T1, pDomainParams->common.pCurveParam2, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP0, ECC_T0, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP1, ECC_T1, ECC_PQSQR, ECC_P);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_EdDSA_SetupEnvironment, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SetupEnvironment),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM );
}
