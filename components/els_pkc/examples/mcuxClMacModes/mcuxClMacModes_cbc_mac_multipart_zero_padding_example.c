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

#include <mcuxClCore_Examples.h> // Defines and assertions for examples

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClKey.h>
#include <mcuxClAes.h> // Interface to AES-related definitions and types
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClMac.h> // Interface to the entire mcuxClMac component
#include <mcuxClMacModes.h> // Interface to the entire mcuxClMacModes component
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_Key_Helper.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_RNG_Helper.h>

/** Performs a CMAC computation using functions of the mcuxClKey component.
 * @retval MCUXCLEXAMPLE_STATUS_OK         The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR      The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClMacModes_cbc_mac_multipart_zero_padding_example)
{
    static uint8_t key256[] = {
        0x12u, 0xE6u, 0xDFu, 0x61u, 0xD7u, 0xEBu, 0xD1u, 0xAEu,
        0x7Au, 0x59u, 0x93u, 0x0Eu, 0x05u, 0x8Au, 0x76u, 0x4Fu,
        0x2Eu, 0x1Bu, 0x6Eu, 0xC7u, 0xA1u, 0xDEu, 0xF8u, 0x68u,
        0x19u, 0x66u, 0x43u, 0x47u, 0x83u, 0x8Bu, 0x30u, 0x6Du
    };

    static const uint8_t inputZeroPadd[] = {
        0x51u, 0x44u, 0xA5u, 0xDCu, 0x29u, 0x0Eu, 0x16u, 0x85u,
        0xB5u, 0x0Bu, 0x2Bu, 0x0Bu, 0xA9u, 0x1Eu, 0x8Cu, 0xD3u,
        0x6Eu, 0xD9u, 0xADu, 0x87u, 0x58u
    };

    static const uint8_t resZeroPadd[] = {
        0xC2u, 0x21u, 0x5Bu, 0xC7u, 0xA2u, 0x28u, 0x68u, 0x93u,
        0x2Eu, 0x5Au, 0xFCu, 0x22u, 0xB7u, 0xF2u, 0x25u, 0x0Eu
    };

    /* Example input size. */
    size_t cmac_input_size = 21u;


    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }


    /* Key buffer for the key in memory. */
    uint32_t key_buffer[MCUXCLKEY_SIZE_256 / sizeof(uint32_t)];

    /* Output buffer for the computed MAC. */
    static uint8_t result_buffer[MCUXCLELS_CMAC_OUT_SIZE];

    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    /* Allocate and initialize session */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLMAC_MAX_CPU_WA_BUFFER_SIZE + MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE, 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);
    

    /**************************************************************************/
    /* Key setup                                                              */
    /**************************************************************************/
    /* Create and initialize mcuxClKey_Descriptor_t structure. */
    uint32_t keyDesc[MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) &keyDesc;

    /* Set key properties. */
    mcuxClEls_KeyProp_t cmac_key_properties;

    cmac_key_properties.word.value = 0u;
    cmac_key_properties.bits.ucmac = MCUXCLELS_KEYPROPERTY_CMAC_TRUE;
    cmac_key_properties.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_128;
    cmac_key_properties.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;

    //Initializes a key handle, Set key properties and Load key.
    if(!mcuxClExample_Key_Init_And_Load(session,
                                       key,
                                       mcuxClKey_Type_Aes256,
                                       (mcuxCl_Buffer_t) key256,
                                       sizeof(key256),
                                       &cmac_key_properties,
                                       key_buffer, MCUXCLEXAMPLE_CONST_EXTERNAL_KEY))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* MAC computation                                                        */
    /**************************************************************************/
    // init
    // process
    // finish
    uint8_t context[MCUXCLMAC_CONTEXT_SIZE];
    mcuxClMac_Context_t * ctx = (mcuxClMac_Context_t *) context;

    /* Call the mcuxClMac_init */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(initResult, initToken, mcuxClMac_init(
        /* mcuxClSession_Handle_t session:       */ session,
        /* mcuxClMac_Context_t * const pContext: */ ctx,
        /* const mcuxClKey_Handle_t key:         */ key,
        /* mcuxClMac_Mode_t mode:                */ mcuxClMac_Mode_CBCMAC_PaddingISO9797_1_Method1
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_init) != initToken) || (MCUXCLMAC_STATUS_OK != initResult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call the mcuxClMac_process */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(processResult, processToken, mcuxClMac_process(
        /* mcuxClSession_Handle_t session:       */ session,
        /* mcuxClMac_Context_t * const pContext: */ ctx,
        /* mcuxCl_InputBuffer_t pIn:             */ inputZeroPadd,
        /* uint32_t inLength:                   */ cmac_input_size
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_process) != processToken) || (MCUXCLMAC_STATUS_OK != processResult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Call the mcuxClMac_finish */
    uint32_t result_size = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(finishResult, finishToken, mcuxClMac_finish(
        /* mcuxClSession_Handle_t session:       */ session,
        /* mcuxClMac_Context_t * const pContext: */ ctx,
        /* mcuxCl_Buffer_t pMac:                 */ result_buffer,
        /* uint32_t * const pMacLength:         */ &result_size
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_finish) != finishToken) || (MCUXCLMAC_STATUS_OK != finishResult))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Verification                                                           */
    /**************************************************************************/

    /* Compare the output size with the expected MAC size */
    if(sizeof(resZeroPadd) != result_size)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Compare the result to the reference value. */
    if(!mcuxClCore_assertEqual(resZeroPadd, result_buffer, sizeof(resZeroPadd)))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Flush the key. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_flush(session,
                                                                  key));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClKey_flush) != token) || (MCUXCLKEY_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /** Destroy Session and cleanup Session **/
    if(!mcuxClExample_Session_Clean(session))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    return MCUXCLEXAMPLE_STATUS_OK;
}
