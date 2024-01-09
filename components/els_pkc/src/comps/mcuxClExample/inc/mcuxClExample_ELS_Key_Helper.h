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

#ifndef MCUXCLEXAMPLE_ELS_KEY_HELPER_H_
#define MCUXCLEXAMPLE_ELS_KEY_HELPER_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClEls.h>
#include <mcuxClExample_RFC3394_Helper.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

/**
 * Delete keyslot via mcuxClEls_KeyDelete_Async.
 * [in]  keyIdx: The index of the key to be deleted
 **/
static inline bool mcuxClExample_Els_KeyDelete(mcuxClEls_KeyIndex_t keyIdx)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(keyIdx));
    // mcuxClEls_KeyDelete_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return false; // Expect that no error occurred, meaning that the mcuxClEls_KeyDelete_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_KeyDelete_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return true;
}

/**
 * Delete all keyslot via mcuxClEls_Reset_Async.
 **/
static inline bool mcuxClExample_Els_KeyDeleteAll(void)
{
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Reset_Async(0U));
    // mcuxClEls_Reset_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Reset_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Reset_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    return true;
}


/*
 * Check only if the mcuxClEls_KeyDelete_Async is defined "because mcuxClEls_KeyProvision_Async will be always defined"
 * via CL library or via the TEST OS
 * Function that loads a known key into the ELS key store
 * [in]    helperKeyIdx:              The index of the helper key
 * [in]    targetKeyIdx:              The key index at which the target key shall be loaded
 * [in]    targetKeyProperties:       The target properties of the key
 * [in]    pKey:                      Pointer to the key to be loaded
*/
#define ELS_RFC_PADDING_LENGTH 16U

#endif /* MCUXCLEXAMPLE_ELS_KEY_HELPER_H_ */
