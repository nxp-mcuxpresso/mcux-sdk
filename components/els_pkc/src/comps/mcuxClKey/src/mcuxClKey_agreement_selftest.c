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

/** @file  mcuxClKey_agreement_selftest.c
 *  @brief Implementation of the Key component key agreement selftest functionality.
 */

#include <mcuxClKey.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClSession_Internal_EntryExit.h>
#include <internal/mcuxClKey_Internal.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_agreement_selftest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_agreement_selftest(
    mcuxClSession_Handle_t session,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Test_t test
)
{
    MCUXCLSESSION_ENTRY(session, mcuxClKey_agreement_selftest, diRefValue, MCUXCLKEY_STATUS_FAULT_ATTACK)

    /* do key exchange selftest */
    MCUX_CSSL_FP_FUNCTION_CALL(selftest_result, test->pSelfTestFct(
    /* mcuxClSession_Handle_t   pSession:      */   session,
    /* mcuxClKey_Agreement_t agreement:        */   agreement
    ));

    MCUXCLSESSION_EXIT(session, mcuxClKey_agreement_selftest, diRefValue, selftest_result, MCUXCLKEY_STATUS_FAILURE,
        test->protectionTokenSelfTestFct)
}
