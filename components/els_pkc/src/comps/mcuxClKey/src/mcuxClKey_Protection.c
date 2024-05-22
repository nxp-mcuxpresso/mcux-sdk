/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/** @file  mcuxClKey_Protection.c
 *  @brief Implementation of the Key protection functions that are supported
 *  by component. */

#include <mcuxClEls.h>
#include <mcuxClKey.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_protect_fct_none, mcuxClKey_LoadFuncPtr_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_protect_fct_none(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_protect_fct_none);

    if(MCUXCLKEY_LOADSTATUS_MEMORY == mcuxClKey_getLoadStatus(key))
    {
        // copy key source to destination memory buffer
        uint32_t len = mcuxClKey_getSize(key);

        MCUXCLMEMORY_FP_MEMORY_COPY(mcuxClKey_getLoadedKeyData(key), mcuxClKey_getKeyData(key), len);

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_none, MCUXCLKEY_STATUS_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_none, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_protect_fct_ckdf, mcuxClKey_LoadFuncPtr_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_protect_fct_ckdf(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_protect_fct_ckdf, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Ckdf_Sp800108_Async));

    if(NULL == key->container.parentKey)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_ERROR);
    }

    mcuxClEls_KeyIndex_t key_idx_sk     = (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(mcuxClKey_getParentKey(key));
    mcuxClEls_KeyIndex_t key_idx_mack   = (mcuxClEls_KeyIndex_t) mcuxClKey_getLoadedKeySlot(key);
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    mcuxClEls_KeyProp_t  key_properties = *((mcuxClEls_KeyProp_t*) mcuxClKey_getAuxData(key));
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    MCUX_CSSL_FP_FUNCTION_CALL(resultCkdf, mcuxClEls_Ckdf_Sp800108_Async(
                                 key_idx_sk,
                                 key_idx_mack,
                                 key_properties,
                                 mcuxClKey_getKeyData(key)
    ));
    // mcuxClEls_Ckdf_Sp800108_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLELS_STATUS_OK_WAIT != resultCkdf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_ERROR); // Expect that no error occurred, meaning that the mcuxClEls_Ckdf_Sp800108_Async operation was started.
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    if (MCUXCLELS_STATUS_OK != resultWait)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_ERROR, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation));
}


const mcuxClKey_ProtectionDescriptor_t mcuxClKey_ProtectionDescriptor_None = {&mcuxClKey_protect_fct_none,
                                                                            NULL,
                                                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_protect_fct_none),
                                                                            0u};

const mcuxClKey_ProtectionDescriptor_t mcuxClKey_ProtectionDescriptor_Ckdf = {&mcuxClKey_protect_fct_ckdf,
                                                                            NULL,
                                                                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_protect_fct_ckdf),
                                                                            0u};


