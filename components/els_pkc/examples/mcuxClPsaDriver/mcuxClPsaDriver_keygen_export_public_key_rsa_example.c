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

/**
 * @file  mcuxClPsaDriver_keygen_export_public_key_rsa_example.c
 * @brief Example for generating and exporting rsa key
 *
 * @example mcuxClPsaDriver_keygen_export_public_key_rsa_example.c
 * @brief Example for generating and exporting rsa key
 */

#include "common.h"

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClRsa.h>
#include <mcuxClPkc.h>


/* Public RSA exponent e */
static const uint8_t PublicExp[] __attribute__ ((aligned (4))) =
{
    0x01, 0x00, 0x01
};

#define LIFETIME_INTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_EXTERNAL_STORAGE)
#define LIFETIME_EXTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)

bool mcuxClPsaDriver_keygen_export_public_key_rsa_example(void)
{
	/* Enable ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Enable_Async()); // Enable the ELS.
    // mcuxClEls_Enable_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Enable_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Enable_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /*****************************   Generate RSA key   *******************************************/
    /**********************************************************************************************/

    /* Set up PSA key attributes. */
    psa_key_attributes_t attributes = {
      .core = {                                                               // Core attributes
        .type = PSA_KEY_TYPE_RSA_KEY_PAIR,                                    // Keypair family with curve montgomery
        .bits = MCUXCLKEY_SIZE_2048,                                         // Key bits for RSA 2048
        .lifetime = LIFETIME_EXTERNAL,                                        // Volatile (RAM), S50 Temporary Storage for private key
        .id = 0U,                                                             // ID zero
        .policy = {
          .usage = PSA_ALG_NONE,
          .alg = PSA_ALG_NONE,
          .alg2 = PSA_ALG_NONE},
        .flags = 0U},                                                         // No flags
      .domain_parameters = (uint8_t*)PublicExp,
      .domain_parameters_size = sizeof(PublicExp)};

    /* Call generate_key operation */
    uint8_t key_buffer[PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(2048u)] = {0U};
    size_t key_buffer_size = PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(2048u);
    size_t key_buffer_length = 0U;

    psa_status_t status = psa_driver_wrapper_generate_key(
                &attributes,
                (uint8_t *)&key_buffer, key_buffer_size, &key_buffer_length );

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(key_buffer_length > PSA_KEY_EXPORT_RSA_KEY_PAIR_MAX_SIZE(2048u))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /******************   Export RSA public key   *************************************************/
    /**********************************************************************************************/

    uint8_t data[PSA_EXPORT_KEY_OUTPUT_SIZE(PSA_KEY_TYPE_RSA_PUBLIC_KEY,MCUXCLKEY_SIZE_2048)] = {0U};
    size_t data_size = PSA_EXPORT_KEY_OUTPUT_SIZE(PSA_KEY_TYPE_RSA_PUBLIC_KEY,MCUXCLKEY_SIZE_2048);
    size_t data_length = 0U;

    attributes.core.policy.usage = PSA_KEY_USAGE_EXPORT;
    status = psa_driver_wrapper_export_public_key(
                &attributes,
                key_buffer, key_buffer_size,
                data, data_size, &data_length);

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    if(data_length > data_size)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Disable ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Disable()); // Disable the ELS.
    // mcuxClEls_Disable is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Disable) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    /* Return */
    return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_keygen_export_public_key_rsa_example(void)
{
    bool result = mcuxClPsaDriver_keygen_export_public_key_rsa_example();
    return result;
}
