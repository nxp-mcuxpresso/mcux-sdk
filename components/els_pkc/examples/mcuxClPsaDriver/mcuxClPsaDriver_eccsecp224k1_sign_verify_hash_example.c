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

#include "common.h"

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClPsaDriver.h>
#include <mcuxClCore_Examples.h>


/**
 * @brief ECC private key used in signature.
 */
#define BITLEN_P (224u)
#define BITLEN_N (225u)
#define BYTELEN_P (PSA_BITS_TO_BYTES(BITLEN_P))
#define BYTELEN_N (PSA_BITS_TO_BYTES(BITLEN_N))

static const uint8_t privateKeyBuffer[BYTELEN_N] __attribute__ ((aligned (4))) = {
  0x00, 0x1au, 0xf2u, 0xc6u, 0xedu, 0x73u, 0x82u, 0x32u,
  0xaau, 0x5du, 0x1fu, 0x9cu, 0x06u, 0xe3u, 0xf2u, 0x06u,
  0xb3u, 0xc2u, 0xaeu, 0xc0u, 0x11u, 0x65u, 0xe5u, 0x65u,
  0xd0u, 0x7fu, 0xa1u, 0xe6u, 0x2au,
};

/**
 * @brief ECC public key used in verification.
 */
static const uint8_t publicKeyBuffer[2u * BYTELEN_P + 1u] __attribute__ ((aligned (4))) = {
  0x04u,
  0x37u, 0x52u, 0x4du, 0xa5u, 0xf5u, 0xd0u, 0xc9u, 0x91u,
  0x3du, 0xbcu, 0xfdu, 0x1eu, 0x6cu, 0x5fu, 0xa0u, 0x49u,
  0xb6u, 0xf0u, 0x7du, 0xc9u, 0xa5u, 0x66u, 0x94u, 0x30u,
  0xb4u, 0x4eu, 0x82u, 0xa4u,
  0xafu, 0x8au, 0x0du, 0xc5u, 0xfeu, 0x07u, 0x99u, 0x45u,
  0xaau, 0x48u, 0x74u, 0xdcu, 0xdbu, 0x1fu, 0xd8u, 0x86u,
  0x1fu, 0xf2u, 0xe8u, 0x22u, 0xb4u, 0x6bu, 0x3eu, 0x12u,
  0xaeu, 0x12u, 0xfau, 0x90u,
};

/**
 * @brief Hash of message to be signed
 */
static const uint8_t hash[PSA_HASH_LENGTH(PSA_ALG_SHA_224)] __attribute__ ((aligned (4))) = {
  0x89, 0x01, 0x41, 0x9f, 0x26, 0x14, 0xc9, 0x42,
  0xc9, 0xee, 0x5e, 0xfb, 0xdf, 0xba, 0x0c, 0xca,
  0x70, 0x6b, 0x3a, 0x4e, 0xd1, 0xa8, 0x5f, 0x69,
  0x28, 0xb7, 0x60, 0xff
};

/**
 * @brief Signature
 */
static uint8_t signature[PSA_SIGN_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR_BASE, BITLEN_N, PSA_ALG_ECDSA_ANY)] __attribute__ ((aligned (4))) = {0};

/*
 *Example of ECDSA signature generation and verification for:
 * - secp224k1 curve (modulus length: 224bits, base point order length: 225bits)
 * - SHA-224
 * - signature scheme PSA_ALG_ECDSA_ANY
 */
bool mcuxClPsaDriver_eccsecp224k1_sign_verify_hash_example(void)
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

  /*
   * Sign hash: PSA_ALG_ECDSA_ANY, SHA_224
   */

  /* Set up PSA key attributes. */
  const psa_key_attributes_t sign_attributes = {
    .core = {                                                                                                                // Core attributes
      .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1),                                                             // SECPK1 curves family
      .bits = BITLEN_P,                                                                                                      // ... of bitlength 224bits
      .lifetime = PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE), // Volatile (RAM), Local Storage for private key
      .id = 0U,                                                                                                              // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_SIGN_HASH,                                                                                    // Key may be used for signing a hash
        .alg = PSA_ALG_ECDSA_ANY,                                                                                            // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE
        },
      .flags = 0U
      },                                                                                                                             // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U};

  size_t signature_length;

  psa_status_t sign_status = psa_driver_wrapper_sign_hash(
    &sign_attributes,           //const psa_key_attributes_t *attributes,
    privateKeyBuffer,           //const uint8_t *key_buffer,
    sizeof(privateKeyBuffer),   //size_t key_buffer_size,
    PSA_ALG_ECDSA_ANY,          //psa_algorithm_t alg,
    hash,                       //const uint8_t *hash,
    sizeof(hash),               //size_t hash_length,
    signature,                  //uint8_t *signature,
    sizeof(signature),          //size_t signature_size,
    &signature_length           //size_t *signature_length
    );

  /* Check the return value */
  if(sign_status != PSA_SUCCESS)
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Check the signature length */
  if(signature_length != PSA_SIGN_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR_BASE, BITLEN_N, PSA_ALG_ECDSA_ANY))
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /*
   * Verify hash: PSA_ALG_ECDSA_ANY, SHA_224
   */

  /* Set up PSA key attributes. */
  const psa_key_attributes_t verify_attributes = {
    .core = {                                                                                                                // Core attributes
      .type = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_K1),                                                           // SECPK1 curves family
      .bits = BITLEN_P,                                                                                                      // ... of bitlength 224bits
      .lifetime = PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE), // Volatile (RAM), Local Storage for public key
      .id = 0U,                                                                                                              // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_VERIFY_HASH,                                                                                  // Key may be used for verify a hash
        .alg = PSA_ALG_ECDSA_ANY,                                                                                            // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE
        },
      .flags = 0U
      },                                                                                                                             // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U};

  psa_status_t verify_status = psa_driver_wrapper_verify_hash(
    &verify_attributes,         //const psa_key_attributes_t *attributes,
    publicKeyBuffer,            //const uint8_t *key_buffer,
    sizeof(publicKeyBuffer),    //size_t key_buffer_size,
    PSA_ALG_ECDSA_ANY,          //psa_algorithm_t alg,
    hash,                       //const uint8_t *hash,
    sizeof(hash),               //size_t hash_length,
    signature,                  //const uint8_t *signature,
    sizeof(signature)           //size_t signature_length
    );

  /* Check the return value */
  if(verify_status != PSA_SUCCESS)
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Return */
  return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_eccsecp224k1_sign_verify_hash_example(void)
{
    bool result = mcuxClPsaDriver_eccsecp224k1_sign_verify_hash_example();
    return result;
}
