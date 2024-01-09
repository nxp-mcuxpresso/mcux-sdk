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
MCUXCLEXAMPLE_FUNCTION(mcuxClMacModes_cbc_mac_oneshot_example)
{
    /* Example AES-128 key. */
    static const uint8_t aes128_key[MCUXCLAES_AES128_KEY_SIZE] = {
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa
    };

    /* Example input size. */
    size_t cmac_input_size_16 = 32u;

    /* Example input to the CMAC function. */
    static const uint8_t cmac_input16_in[] = {
        0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu,
        0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu,
        0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu,
        0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu, 0xddu
    };

    /* Example reference CMAC. */
    static const uint8_t cmac_output_reference16[MCUXCLELS_CMAC_OUT_SIZE] = {
        0x55u, 0xffu, 0x3du, 0x8cu, 0xa5u, 0xc7u, 0x4eu, 0x8fu,
        0x75u, 0x4du, 0x57u, 0xabu, 0xfau, 0xb4u, 0x76u, 0x97u
    };
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }


    /* Key buffer for the key in memory. */
    uint32_t key_buffer[MCUXCLAES_AES128_KEY_SIZE_IN_WORDS];

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
                                       mcuxClKey_Type_Aes128,
                                       (mcuxCl_Buffer_t) aes128_key,
                                       sizeof(aes128_key),
                                       &cmac_key_properties,
                                       key_buffer, MCUXCLEXAMPLE_CONST_EXTERNAL_KEY))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* MAC computation                                                        */
    /**************************************************************************/

    /* Call the mcuxClMac_compute function to compute a CMAC in one shot. */
    uint32_t result_size = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClMac_compute(
        /* mcuxClSession_Handle_t session:  */ session,
        /* const mcuxClKey_Handle_t key:    */ key,
        /* const mcuxClMac_Mode_t mode:     */ mcuxClMac_Mode_CBCMAC_NoPadding,
        /* mcuxCl_InputBuffer_t pIn:        */ cmac_input16_in,
        /* uint32_t inLength:              */ cmac_input_size_16,
        /* mcuxCl_Buffer_t pMac:            */ result_buffer,
        /* uint32_t * const pMacLength:    */ &result_size
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMac_compute) != token) || (MCUXCLMAC_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /**************************************************************************/
    /* Verification                                                           */
    /**************************************************************************/

    /* Compare the result to the reference value. */
    if(!mcuxClCore_assertEqual(cmac_output_reference16, result_buffer, sizeof(cmac_output_reference16)))
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
