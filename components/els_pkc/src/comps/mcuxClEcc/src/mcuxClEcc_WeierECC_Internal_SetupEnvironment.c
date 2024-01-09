/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClEcc_WeierECC_Internal_SetupEnvironment.c
 * @brief Weierstrass curve internal setup environment
 */


#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClEcc_Weier_Internal.h>


/**
 * \brief This function sets up environment used by Weierstrass functions.
 *
 * On top of generic ECC environment setup function, mcuxClEcc_SetupEnvironment,
 * this function further imports the curve coefficients a and b, and converts
 * coefficient a into montgomery representation.
 *
 * Inputs:
 *  - pSession: pointer to session descriptor;
 *  - pDomainParams: pointer to Weier domain parameter structure;
 *  - noOfBuffers: number of buffers in PKC workarea used by calling API.
 *
 * Results:
 *  - results of mcuxClEcc_SetupEnvironment;
 *  - Buffer WEIER_A contains the coefficient a in MR.
 *  - Buffer WEIER_B contains the coefficient b in NR.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the results.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_WeierECC_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_WeierECC_SetupEnvironment(
    mcuxClSession_Handle_t pSession,
    mcuxClEcc_Weier_DomainParams_t *pWeierDomainParams,
    uint8_t noOfBuffers)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_WeierECC_SetupEnvironment);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnvironment,
        mcuxClEcc_SetupEnvironment(pSession, &(pWeierDomainParams->common), noOfBuffers) );
    if (MCUXCLECC_STATUS_OK != retSetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retSetupEnvironment, mcuxClEcc_WeierECC_SetupEnvironment);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_WeierECC_SetupEnvironment, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Import coefficients a and b, and convert a to MR. */
    uint32_t byteLenP = pWeierDomainParams->common.byteLenP;
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0, pWeierDomainParams->common.pCurveParam1, byteLenP);
    MCUXCLPKC_FP_CALC_MC1_MM(WEIER_A, ECC_T0, ECC_PQSQR, ECC_P);
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(WEIER_B, pWeierDomainParams->common.pCurveParam2, byteLenP);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_WeierECC_SetupEnvironment, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SetupEnvironment),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc) );
}
