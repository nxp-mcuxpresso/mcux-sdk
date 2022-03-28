/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

#include <mcuxClCss.h>
#include <mcuxClKey.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClKey_Protections.h>
#include <internal/mcuxClKey_Protection_Internal.h>
#include <internal/mcuxClKey_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_protect_fct_none)
mcuxClKey_Status_Protected_t mcuxClKey_protect_fct_none(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_protect_fct_none);

    if(mcuxClKey_LoadLocation_MEMORY == key->dstKey.loadLocation)
    {
        // copy key source to destination memory buffer
        size_t len = MCUXCLKEY_GET_KEYSIZE(key);

        MCUX_CSSL_FP_FUNCTION_CALL(resultLen, mcuxClMemory_copy(key->dstKey.pData,
                                                              key->pSrcKeyData,
                                                              len, len));
        if (0U != resultLen)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_none, MCUXCLKEY_STATUS_ERROR);
        }

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_none, MCUXCLKEY_STATUS_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_none, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_protect_fct_ckdf)
mcuxClKey_Status_Protected_t mcuxClKey_protect_fct_ckdf(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_protect_fct_ckdf, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_Ckdf_Sp800108_Async));

    mcuxClCss_KeyIndex_t key_idx_sk    = (mcuxClCss_KeyIndex_t) key->srcAux.slot;
    mcuxClCss_KeyIndex_t key_idx_mack  = (mcuxClCss_KeyIndex_t) key->dstKey.slot;
    mcuxClCss_KeyProp_t key_properties = key->dstKey.key_properties;

    MCUX_CSSL_FP_FUNCTION_CALL(resultCkdf, mcuxClCss_Ckdf_Sp800108_Async(
                                 key_idx_sk,
                                 key_idx_mack,
                                 key_properties,
                                 key->srcAux.pData
    ));
    // mcuxClCss_Ckdf_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLCSS_STATUS_OK_WAIT != resultCkdf)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_ERROR); // Expect that no error occurred, meaning that the mcuxClCss_Ckdf_Async operation was started.
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));

    if (MCUXCLCSS_STATUS_OK != resultWait)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_ERROR, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_protect_fct_ckdf, MCUXCLKEY_STATUS_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_flush_fct_none)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_none(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_flush_fct_none);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_none, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_flush_fct_memory)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_memory(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_flush_fct_memory, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_set));

    size_t len = MCUXCLKEY_GET_KEYSIZE(key);
    //TODO may need to be replaced by a secure set function
    MCUX_CSSL_FP_FUNCTION_CALL(resultLen, mcuxClMemory_set(key->dstKey.pData, 0u, len, len));
    if (0U != resultLen)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_memory, MCUXCLKEY_STATUS_ERROR);
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_memory, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_flush_fct_css)
mcuxClKey_Status_Protected_t mcuxClKey_flush_fct_css(mcuxClKey_Handle_t key)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_flush_fct_css, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_KeyDelete_Async));

    MCUX_CSSL_FP_FUNCTION_CALL(resultDelete, mcuxClCss_KeyDelete_Async((mcuxClCss_KeyIndex_t) key->dstKey.slot));
    // mcuxClCss_KeyDelete_Async is a flow-protected function: Check the protection token and the return value
    if (MCUXCLCSS_STATUS_OK_WAIT != resultDelete) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_css, MCUXCLKEY_STATUS_ERROR); // Expect that no error occurred, meaning that the mcuxClCss_KeyDelete_Async operation was started.
    }

    MCUX_CSSL_FP_FUNCTION_CALL(resultWait, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    if ((MCUXCLCSS_STATUS_OK != resultWait)) {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_css, MCUXCLKEY_STATUS_ERROR, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush_fct_css, MCUXCLKEY_STATUS_OK, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation));
}


const mcuxClKey_Protection_t mcuxClKey_protection_none = {&mcuxClKey_protect_fct_none,
                                                        &mcuxClKey_flush_fct_none,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_protect_fct_none),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_flush_fct_none)};
const mcuxClKey_Protection_t mcuxClKey_protection_ckdf = {&mcuxClKey_protect_fct_ckdf,
                                                        &mcuxClKey_flush_fct_css,
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_protect_fct_ckdf),
                                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_flush_fct_css)};

