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

/** @file  mcuxClKey.c
 *  @brief Implementation of the Key component to deal with keys used by
 *  higher-level components. This file implements the functions declared in
 *  mcuxClKey.h. */

#include <mcuxClKey.h>
#include <mcuxClCss.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_init)
mcuxClKey_Status_Protected_t mcuxClKey_init(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    const mcuxClKey_Type_t * type,
    const mcuxClKey_Protection_t * protection,
    const uint8_t * const srcKeyData,
    const uint8_t * const srcAuxData,
    uint32_t srcAuxSlot
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_init);

    /* Fill key structure */
    key->type = *type;
    key->protection = protection;
    key->pSrcKeyData = srcKeyData;
    key->srcAux.pData = srcAuxData;
    key->srcAux.slot = srcAuxSlot;
    key->dstKey.loadLocation = mcuxClKey_LoadLocation_NOTLOADED;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_init, MCUXCLKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_loadMemory)
mcuxClKey_Status_Protected_t mcuxClKey_loadMemory(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    uint32_t * dstData
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_loadMemory, key->protection->protectionTokenLoad);

    /* Set additional parameters */
    key->dstKey.pData = (uint8_t *) dstData;
    key->dstKey.loadLocation = mcuxClKey_LoadLocation_MEMORY;

    /* Perform key loading */
    MCUX_CSSL_FP_FUNCTION_CALL(result, key->protection->loadFunc(key));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_loadMemory, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_loadCopro)
mcuxClKey_Status_Protected_t mcuxClKey_loadCopro(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    uint32_t dstSlot
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_loadCopro, key->protection->protectionTokenLoad);

    /* Set additional parameters */
    key->dstKey.slot = dstSlot;
    key->dstKey.loadLocation = mcuxClKey_LoadLocation_COPRO;

    /* Perform key loading */
    MCUX_CSSL_FP_FUNCTION_CALL(result, key->protection->loadFunc(key));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_loadCopro, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_flush)
mcuxClKey_Status_Protected_t mcuxClKey_flush(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_flush, key->protection->protectionTokenFlush);
    /* Set additional parameter */
    key->dstKey.loadLocation = mcuxClKey_LoadLocation_NOTLOADED;

    /* Perform key flushing */
    MCUX_CSSL_FP_FUNCTION_CALL(result, key->protection->flushFunc(key));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_flush, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClKey_setKeyproperties)
mcuxClKey_Status_Protected_t mcuxClKey_setKeyproperties(
    mcuxClKey_Handle_t key,
    mcuxClCss_KeyProp_t key_properties
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClKey_setKeyproperties);

    key->dstKey.key_properties = key_properties;
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClKey_setKeyproperties, MCUXCLKEY_STATUS_OK);
}
