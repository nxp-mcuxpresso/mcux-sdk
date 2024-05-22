/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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
 * @file  mcuxClEcc_Mont_Internal_DhSetupEnvironment.c
 * @brief Montgomery curve internal setup environment
 */


#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMemory.h>
#include <mcuxClEcc.h>

#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClEcc_Mont_Internal.h>


/**
 * \brief This function sets up environment used by MontDH functions.
 *
 * On top of generic ECC environment setup function, mcuxClEcc_SetupEnvironment,
 * this function further imports the ladder constant A24 = (A+2)/4 mod p,
 * converts it to Montgomery representation, and stores in buffer ECC_CP0.
 *
 * Inputs:
 *  - pSession: pointer to session descriptor;
 *  - pDomainParams: pointer to MontDH domain parameter structure;
 *  - noOfBuffers: number of buffers in PKC workarea used by calling API.
 *
 * Results:
 *  - results of mcuxClEcc_SetupEnvironment;
 *  - Buffer ECC_CP0 contains the ladder constant (A+2)/4 mod p in MR.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_MontDH_SetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_MontDH_SetupEnvironment(mcuxClSession_Handle_t pSession,
                                                                               mcuxClEcc_MontDH_DomainParams_t *pDomainParams,
                                                                               uint8_t noOfBuffers)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_MontDH_SetupEnvironment);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnvironment,
        mcuxClEcc_SetupEnvironment(pSession, &(pDomainParams->common), noOfBuffers) );
    if (MCUXCLECC_STATUS_OK != retSetupEnvironment)
    {
        MCUXCLECC_HANDLE_HW_UNAVAILABLE(retSetupEnvironment, mcuxClEcc_MontDH_SetupEnvironment);
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_SetupEnvironment, MCUXCLECC_STATUS_FAULT_ATTACK);
    }

    /* Import ladder constant (A+2)/4 mod p. */
    MCUXCLPKC_FP_IMPORTLITTLEENDIANTOPKC(ECC_T0,
                                        pDomainParams->common.pLadderConst,
                                        (uint32_t) pDomainParams->common.byteLenP);

    /* Convert ladder constant to Montgomery representation. */
    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP0, ECC_T0, ECC_PQSQR, ECC_P);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_MontDH_SetupEnvironment, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SetupEnvironment),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ImportLittleEndianToPkc),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM );
}
