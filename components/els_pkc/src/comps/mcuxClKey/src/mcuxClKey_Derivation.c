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

/** @file  mcuxClKey_Derivation.c
 *  @brief Implementation of Key Derivation engines */

#include <mcuxClKey.h>
#include <internal/mcuxClKey_Internal.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClSession_Internal_EntryExit.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxCsslAnalysis.h>

const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_derivationKey_variableLength = {.algoId = MCUXCLKEY_ALGO_ID_SYMMETRIC_KEY, .size = 0u, .info = NULL};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_derivation)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivation(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[],
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClKey_derivation, diRefValue, MCUXCLKEY_STATUS_FAULT_ATTACK, derivationMode->derivationAlgorithm->protectionTokenDerivationEngine)

    MCUX_CSSL_FP_FUNCTION_CALL(result, derivationMode->derivationAlgorithm->pDerivationEngine(
        pSession,
        derivationMode,
        derivationKey,
        inputs,
        numberOfInputs,
        derivedKey));

    MCUXCLSESSION_EXIT(pSession, mcuxClKey_derivation, diRefValue, result, MCUXCLKEY_STATUS_FAULT_ATTACK)
}
