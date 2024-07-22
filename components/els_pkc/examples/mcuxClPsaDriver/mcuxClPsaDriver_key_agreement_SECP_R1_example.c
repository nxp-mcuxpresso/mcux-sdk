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
 * @file  mcuxClPsaDriver_key_agreement_SECP_R1_example.c
 * @brief Example for secp256r1 key agreement
 * 
 * @example mcuxClPsaDriver_key_agreement_SECP_R1_example.c
 * @brief Example for secp256r1 key agreement
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

#define PSA_SECP_R1_CURVE_BITS                      (256u)
#define PSA_SECP_R1_PRIVATE_KEY_SIZE                ((PSA_SECP_R1_CURVE_BITS) / 8u)
#define PSA_SECP_R1_PUBLIC_KEY_SIZE                 ((512u / 8u) + 1u)
#define PSA_SECP_R1_RAW_KEY_AGREEMENT_OUTPUT_SIZE \
  MCUX_CSSL_ANALYSIS_START_PATTERN_EXTERNAL_MACRO() \
  (PSA_RAW_KEY_AGREEMENT_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1), PSA_SECP_R1_CURVE_BITS)) \
  MCUX_CSSL_ANALYSIS_STOP_PATTERN_EXTERNAL_MACRO()

static const uint8_t pAlicePrivKeyData[PSA_SECP_R1_PRIVATE_KEY_SIZE] __attribute__ ((aligned (4))) = {
  0x5Du, 0x37u, 0x8Du, 0xFDu, 0x5Cu, 0xDDu, 0x7Au, 0x37u,
  0xE7u, 0x0Fu, 0x1Au, 0xF7u, 0xFEu, 0x99u, 0xA5u, 0x16u,
  0xD4u, 0xE0u, 0xC4u, 0x34u, 0xD8u, 0x49u, 0x85u, 0xFBu,
  0x12u, 0x50u, 0x32u, 0x06u, 0x73u, 0x9Au, 0x96u, 0xF4u,
};

static const uint8_t pBobPubKeyData[PSA_SECP_R1_PUBLIC_KEY_SIZE] __attribute__ ((aligned (4))) = {
  0x04u,
  0xF4u, 0x7Au, 0x9Au, 0xA6u, 0x2Du, 0x6Bu, 0x5Cu, 0x57u,
  0x1Eu, 0xC6u, 0x6Au, 0xDFu, 0x00u, 0x1Eu, 0x2Cu, 0x2Du,
  0x21u, 0x72u, 0xDEu, 0x07u, 0x2Bu, 0xA5u, 0xB9u, 0xB4u,
  0xB2u, 0xB5u, 0xC3u, 0xEBu, 0xC9u, 0x50u, 0xE0u, 0x21u,
  0x12u, 0xF9u, 0xD0u, 0xA3u, 0xA8u, 0x85u, 0x0Bu, 0x9Bu,
  0xA6u, 0xE1u, 0x4Bu, 0x3Bu, 0x7Du, 0x54u, 0xD8u, 0x7Bu,
  0xF9u, 0x82u, 0xECu, 0x38u, 0x1Bu, 0x81u, 0x5Bu, 0x7Du,
  0x9Fu, 0x29u, 0x51u, 0x9Fu, 0x52u, 0x95u, 0x24u, 0xD6u
};


MCUXCLEXAMPLE_FUNCTION(mcuxClPsaDriver_key_agreement_SECP_R1_example)
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
    uint8_t shared_secret[PSA_SECP_R1_RAW_KEY_AGREEMENT_OUTPUT_SIZE];
    size_t shared_secret_length = 0u;

    psa_key_attributes_t keyagreementAttr = {
      .core = {                                                             // Core attributes
        .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),     		  // Keypair family with curve secp256r1
        .bits = PSA_SECP_R1_PRIVATE_KEY_SIZE * 8u,                          // Key bits of secp256r1
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
      PSA_SECP_R1_RAW_KEY_AGREEMENT_OUTPUT_SIZE,
      &shared_secret_length);

    /* Check the return value */
    if(status != PSA_SUCCESS)
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Check the output length */
    if(shared_secret_length != PSA_SECP_R1_RAW_KEY_AGREEMENT_OUTPUT_SIZE)
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
