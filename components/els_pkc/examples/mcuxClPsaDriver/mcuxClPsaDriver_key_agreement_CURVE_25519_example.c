/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClPsaDriver_CURVE_25519_example.c
 * @brief Example for montgomery curve 25519 key agreement
 * 
 * @example mcuxClPsaDriver_CURVE_25519_example.c
 * @brief Example for montgomery curve 25519 key agreement
 */

#include "common.h"

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>
#include <psa_crypto_driver_wrappers.h>
#include <mcuxClCore_Examples.h>


#define LIFETIME_INTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_EXTERNAL_STORAGE)
#define LIFETIME_EXTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)

#define PSA_MONTGOMERY_CURVE_BITS                      (255u)
#define PSA_MONTGOMERY_PRIVATE_KEY_SIZE                ((PSA_MONTGOMERY_CURVE_BITS + 7u) / 8u)
#define PSA_MONTGOMERY_PUBLIC_KEY_SIZE                 ((PSA_MONTGOMERY_CURVE_BITS + 7u) / 8u)
#define PSA_MONTGOMERY_RAW_KEY_AGREEMENT_OUTPUT_SIZE \
    MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_MACRO() \
    (PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY), PSA_MONTGOMERY_CURVE_BITS)) \
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_MACRO()

static const uint8_t pAlicePrivKeyData[PSA_MONTGOMERY_PRIVATE_KEY_SIZE] __attribute__ ((aligned (4))) = {
    0x77u, 0x7u, 0x6du, 0xau, 0x73u, 0x18u, 0xa5u, 0x7du,
    0x3cu, 0x16u, 0xc1u, 0x72u, 0x51u, 0xb2u, 0x66u, 0x45u,
    0xdfu, 0x4cu, 0x2fu, 0x87u, 0xebu, 0xc0u, 0x99u, 0x2au,
    0xb1u, 0x77u, 0xfbu, 0xa5u, 0x1du, 0xb9u, 0x2cu, 0x2a
};

static const uint8_t pBobPubKeyData[PSA_MONTGOMERY_PUBLIC_KEY_SIZE] __attribute__ ((aligned (4))) = {
    0xdeu, 0x9eu, 0xdbu, 0x7du, 0x7bu, 0x7du, 0xc1u, 0xb4u,
    0xd3u, 0x5bu, 0x61u, 0xc2u, 0xecu, 0xe4u, 0x35u, 0x37u,
    0x3fu, 0x83u, 0x43u, 0xc8u, 0x5bu, 0x78u, 0x67u, 0x4du,
    0xadu, 0xfcu, 0x7eu, 0x14u, 0x6fu, 0x88u, 0x2bu, 0x4f
};

MCUXCLEXAMPLE_FUNCTION(mcuxClPsaDriver_key_agreement_CURVE_25519_example)
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

    /**********************************************************************************************/
    /*************************************     Example   ******************************************/
    /***********************        ECDH Key agreement SECP 256 R1           **********************/
    /**********************************************************************************************/
    uint8_t shared_secret[PSA_MONTGOMERY_RAW_KEY_AGREEMENT_OUTPUT_SIZE];
    size_t shared_secret_length = 0u;

    psa_key_attributes_t keyagreementAttr = {
      .core = {                                                             // Core attributes
        .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_MONTGOMERY),     	// Keypair family with Montgomery curve 25519
        .bits = PSA_MONTGOMERY_PRIVATE_KEY_SIZE * 8u,                       // Key bits of curve25519
        .lifetime = LIFETIME_EXTERNAL,                                      // Volatile (RAM), S50 Temporary Storage for private key
        .id = 0U,                                                           // ID zero
        .policy = {
          .usage = PSA_ALG_NONE,
          .alg = PSA_ALG_ECDH,
          .alg2 = PSA_ALG_NONE},
        .flags = 0U},                                                         // No flags
      .domain_parameters = NULL,
      .domain_parameters_size = 0U};

    psa_status_t status = psa_driver_wrapper_key_agreement(
      &keyagreementAttr,
      pAlicePrivKeyData,
      sizeof(pAlicePrivKeyData),
      PSA_ALG_ECDH,
      pBobPubKeyData,
      sizeof(pBobPubKeyData),
      shared_secret,
      PSA_MONTGOMERY_RAW_KEY_AGREEMENT_OUTPUT_SIZE,
      &shared_secret_length);

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(shared_secret_length != PSA_MONTGOMERY_RAW_KEY_AGREEMENT_OUTPUT_SIZE)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_KeyDelete_Async operation to complete.
    // mcuxClEls_LimitedWaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

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
