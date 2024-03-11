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

/** @file  mcuxClKey_agreement.c
 *  @brief Implementation of th key agreement functionality. */


#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClSession_Internal_EntryExit.h>
#include <internal/mcuxClKey_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_agreement)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t)  mcuxClKey_agreement(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Handle_t key,
    mcuxClKey_Handle_t otherKey,
    mcuxClKey_Agreement_AdditionalInput_t additionalInputs[],
    uint32_t numberOfInputs,
    uint8_t * pOut,
    uint32_t * const pOutLength
)
{
    MCUXCLSESSION_ENTRY(pSession, mcuxClKey_agreement, diRefValue, MCUXCLKEY_STATUS_FAULT_ATTACK)

    /* Call protocol specific key agreement function according to passed agreement descriptor. */
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Agreement,
                              agreement->pAgreementFct(pSession, agreement, key, otherKey,
                              additionalInputs, numberOfInputs, pOut, pOutLength));

    MCUXCLSESSION_EXIT(pSession, mcuxClKey_agreement, diRefValue, ret_Agreement, MCUXCLKEY_STATUS_FAULT_ATTACK,
        agreement->protectionTokenAgreementFct)
}

