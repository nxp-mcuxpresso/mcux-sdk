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

#ifndef MCUXCLEXAMPLE_KEY_HELPER_H_
#define MCUXCLEXAMPLE_KEY_HELPER_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClKey.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

/**
 * Load key via mcuxClKey_loadMemory or mcuxClKey_loadCopro according to the key_loading_option parameter.
 * [in]      pSession:         Pointer to the session handle.
 * [in,out]  pKey:             Pointer to the key handle.
 * [in]      type:             Define which key type shall be initialized
 * [in]      pData:            Provide pointer to source data of the key
 * [in]      keyDataLength:    Number of bytes available in the pData buffer.
 * [in]      key_properties:   Pointer to the requested key properties of the destination key. Will be set in key->container.pAuxData
 * [in]      dst:              if MCUXCLEXAMPLE_CONST_EXTERNAL_KEY, Pointer to dstData, if MCUXCLEXAMPLE_CONST_INTERNAL_KEY, Pointer to dstSlot value
 * [in]      key_loading_option:0 = external key, 1 = internal key
 **/
#define MCUXCLEXAMPLE_CONST_EXTERNAL_KEY 0U
#define MCUXCLEXAMPLE_CONST_INTERNAL_KEY 1U
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClExample_Key_Init_And_Load)
static inline bool mcuxClExample_Key_Init_And_Load(mcuxClSession_Handle_t pSession,
                                                  mcuxClKey_Handle_t pKey,
                                                  mcuxClKey_Type_t type,
                                                  mcuxCl_Buffer_t pData,
                                                  uint32_t keyDataLength,
                                                  mcuxClEls_KeyProp_t * key_properties,
                                                  uint32_t * dst,
                                                  uint8_t key_loading_option)
{
    /* Init the key. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_init(pSession,
                                                                 pKey,
                                                                 type,
                                                                 pData,
                                                                 keyDataLength));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_init) != token) || (MCUXCLKEY_STATUS_OK != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Set the key properties. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_setKeyproperties(pKey,
                                                                             key_properties));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_setKeyproperties) != token) || (MCUXCLKEY_STATUS_OK != result))
    {
        return false;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    if(MCUXCLEXAMPLE_CONST_EXTERNAL_KEY == key_loading_option)
    {
        /* load key into destination memory buffer */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_loadMemory(
                                   /* mcuxClSession_Handle_t pSession:   */ pSession,
                                   /* mcuxClKey_Handle_t key:            */ pKey,
                                   /* uint32_t * dstData:               */ dst));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_loadMemory) != token) || (MCUXCLKEY_STATUS_OK != result))
        {
            return false;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
    }
    else
    {
        /* load key into destination key slot of coprocessor (key_slot = '*dst') */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_loadCopro(
                                  /* mcuxClSession_Handle_t pSession:   */ pSession,
                                  /* mcuxClKey_Handle_t key:            */ pKey,
                                  /* uint32_t dstSlot:                 */ *dst));

        if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_loadCopro) != token) || (MCUXCLKEY_STATUS_OK != result))
        {
            return false;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
    }
    return true;
}

#endif /* MCUXCLEXAMPLE_KEY_HELPER_H_ */
