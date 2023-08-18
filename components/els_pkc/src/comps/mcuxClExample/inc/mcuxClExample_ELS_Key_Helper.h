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

#if defined(MCUXCL_FEATURE_ELS_KEY_MGMT_KEYPROV) || defined(MCUXCL_FEATURE_ELS_KEY_MGMT_KEYPROV_ROM)
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

static bool mcuxClExample_load_els_key(
    mcuxClEls_KeyIndex_t helperKeyIdx,
    mcuxClEls_KeyIndex_t targetKeyIdx,
    mcuxClEls_KeyProp_t properties,
    const uint8_t* pKey
)
{
    size_t key_size = ((MCUXCLELS_KEYPROPERTY_KEY_SIZE_256 == properties.bits.ksize) ? MCUXCLELS_CIPHER_KEY_SIZE_AES_256 : MCUXCLELS_CIPHER_KEY_SIZE_AES_128);
    uint8_t wrapped_key[MCUXCLELS_CIPHER_KEY_SIZE_AES_256 + ELS_RFC_PADDING_LENGTH];

    /**
    * Step 0: check if a key is already loaded in wrapping_key_slot, if so skip the next step
    */
    mcuxClEls_KeyProp_t key_properties_targeted;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetKeyProperties(targetKeyIdx, &key_properties_targeted));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    if (MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE == key_properties_targeted.bits.kactv)
    {
        return true;
    }

    /**
    * Step 1: load the AES helper key using mcuxClExample_provision_key into helperKeyIdx
    */
    mcuxClEls_KeyProp_t AesHelperKeyProp = {0};
    AesHelperKeyProp.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    AesHelperKeyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    AesHelperKeyProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
    AesHelperKeyProp.bits.uaes = MCUXCLELS_KEYPROPERTY_AES_TRUE;
    AesHelperKeyProp.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    AesHelperKeyProp.bits.kbase = MCUXCLELS_KEYPROPERTY_BASE_SLOT;

    if(true != mcuxClExample_provision_key(helperKeyIdx, AesHelperKeyProp))
    {
        return false;
    }

    /**
    * Step 2: wrap the incoming key into a buffer on the stack and load the rfc3394-wrapped key into the targetKeyIdx
    */
    mcuxClExample_rfc3394_wrap(pKey, key_size, NULL, helperKeyIdx, MCUXCLELS_CIPHER_INTERNAL_KEY, MCUXCLELS_CIPHER_KEY_SIZE_AES_256, wrapped_key, properties);

    /**
    * Step 3: delete the AES helper key from helperKeyIdx
    */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(helperKeyIdx));
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

    /**
    * Step 4: import the kwk using mcuxClExample_provision_key into helperKeyIdx
    */
    mcuxClEls_KeyProp_t kwkHelperKeyProp = {0};
    kwkHelperKeyProp.bits.ukwk = MCUXCLELS_KEYPROPERTY_KWK_TRUE;
    kwkHelperKeyProp.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_256;
    kwkHelperKeyProp.bits.upprot_priv = MCUXCLELS_KEYPROPERTY_PRIVILEGED_TRUE;
    kwkHelperKeyProp.bits.upprot_sec = MCUXCLELS_KEYPROPERTY_SECURE_TRUE;
    kwkHelperKeyProp.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;
    kwkHelperKeyProp.bits.kbase = MCUXCLELS_KEYPROPERTY_BASE_SLOT;

    if(true != mcuxClExample_provision_key(helperKeyIdx, kwkHelperKeyProp))
    {
        return false;
    }

    mcuxClEls_KeyImportOption_t wrapped_key_options = {0};
    wrapped_key_options.bits.kfmt = MCUXCLELS_KEYIMPORT_KFMT_RFC3394;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyImport_Async(wrapped_key_options, wrapped_key, key_size + ELS_RFC_PADDING_LENGTH, helperKeyIdx, targetKeyIdx));
    // mcuxClEls_KeyImport_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyImport_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
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

    /**
    * Step 5: delete kwk from helperKeyIdx
    */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_KeyDelete_Async(helperKeyIdx));
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

#endif /*((MCUXCL_FEATURE_ELS_KEY_MGMT_KEYPROV == 1) || (MCUXCL_FEATURE_ELS_KEY_MGMT_KEYPROV_ROM == 1))*/
#endif /* MCUXCLEXAMPLE_ELS_KEY_HELPER_H_ */
