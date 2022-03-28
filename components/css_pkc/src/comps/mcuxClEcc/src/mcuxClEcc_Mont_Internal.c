/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxClEcc_Mont_Internal.c
 * @brief mcuxClEcc: implementation of MontDh internal functions
 */

#include <stdint.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClMemory.h>

#include <internal/mcuxClPkc_Operations.h>

#include <mcuxClEcc.h>

#include <internal/mcuxClEcc_Mont_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_Mont_DhSetupEnvironment)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Mont_DhSetupEnvironment(mcuxClSession_Handle_t pSession,
                                                                               mcuxClEcc_Mont_DomainParams_t *pDomainParams,
                                                                               uint8_t noOfBuffers)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_Mont_DhSetupEnvironment);

    MCUX_CSSL_FP_FUNCTION_CALL(retSetupEnv,
        mcuxClEcc_SetupEnvironment(pSession, &(pDomainParams->common), noOfBuffers));
    (void) retSetupEnv;

    const uint16_t *pOperands = MCUXCLPKC_GETUPTRT();

    MCUXCLPKC_FP_CALC_OP1_CONST(ECC_T0, 0u);
    uint32_t byteLenP = (uint32_t) pDomainParams->common.byteLenP;
    MCUXCLPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_CALL(retCodeImport,
        mcuxClMemory_copy(MCUXCLPKC_OFFSET2PTR(pOperands[ECC_T0]),
                         pDomainParams->pA24,
                         byteLenP, byteLenP));
    (void) retCodeImport;

    MCUXCLPKC_FP_CALC_MC1_MM(ECC_CP0, ECC_T0, ECC_PQSQR, ECC_P);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEcc_Mont_DhSetupEnvironment, MCUXCLECC_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEcc_SetupEnvironment),
        MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUXCLPKC_FP_CALLED_CALC_MC1_MM );
}
