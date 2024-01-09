/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClKey_example.c
 * @brief Example for the mcuxClKey component
 *
 * @example mcuxClKey_example.c
 * @brief   Example for the mcuxClKey component
 */

#include <mcuxClKey.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClAes.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_Key_Helper.h>


/* Example AES-128 key. */
static uint32_t aes128_key[MCUXCLAES_AES128_KEY_SIZE_IN_WORDS] =
{
    0xb97d0b7cu, 0xd0101f81u, 0x7a6c470eu, 0xe0f6920du
};



/** Performs an example initialization and cleanup of the mcuxClKey component.
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClKey_example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/
    mcuxClSession_Descriptor_t session;
    //Allocate and initialize session
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(&session, 0u, 0u);

    /**************************************************************************/
    /* Key setup                                                              */
    /**************************************************************************/

    /* Create and initialize mcuxClKey_Descriptor_t structure. */
    uint32_t keyDesc[MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) &keyDesc;

    /* Set key properties. */
    mcuxClEls_KeyProp_t key_properties;

    key_properties.word.value = 0u;
    key_properties.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_128;
    key_properties.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;

    /* Key buffer for the key in memory. */
    uint32_t key_buffer[MCUXCLAES_AES128_KEY_SIZE_IN_WORDS];
    //Initializes a key handle, Set key properties and Load key.
    if(!mcuxClExample_Key_Init_And_Load(&session,
                                       key,
                                       mcuxClKey_Type_Aes128,
                                       (uint8_t *) aes128_key,
                                       sizeof(aes128_key),
                                       &key_properties,
                                       key_buffer, MCUXCLEXAMPLE_CONST_EXTERNAL_KEY))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* The key could now be used for a cryptographic operation.               */
    /**************************************************************************/


    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Flush the key. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(resultFlush, tokenFlush, mcuxClKey_flush(
                                                                 &session,
                                                                 key));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_flush) != tokenFlush) || (MCUXCLKEY_STATUS_OK != resultFlush))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(&session))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
