/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClEcc_DeterministicECDSA.c
 * @brief Implementation of the deterministic ECDSA functionality
 */


#include <mcuxClCore_Platform.h>

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEcc.h>
#include <mcuxClMac.h>

#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClEcc_ECDSA_Internal.h>




MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor(
    mcuxClSession_Handle_t session,
    mcuxClEcc_ECDSA_SignatureProtocolDescriptor_t * const pDeterministicECDSAProtocolDescriptor,
    mcuxClMac_Mode_t hmacMode )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor);
    pDeterministicECDSAProtocolDescriptor->generateOption = MCUXCLECC_ECDSA_SIGNATURE_GENERATE_DETERMINISTIC;
    pDeterministicECDSAProtocolDescriptor->verifyOption = 0u;
    pDeterministicECDSAProtocolDescriptor->pHmacModeDesc = hmacMode;

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClEcc_DeterministicECDSA_GenerateProtocolDescriptor,
                                         MCUXCLECC_STATUS_OK, MCUXCLECC_STATUS_FAULT_ATTACK);
}
