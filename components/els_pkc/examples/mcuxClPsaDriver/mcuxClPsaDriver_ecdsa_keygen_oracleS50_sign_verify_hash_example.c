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

#include "common.h"

#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxCsslFlowProtection.h> // Code flow protection
#include <mcuxClPsaDriver.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>


/**
 * @brief Hash of message to be signed
 */
static const uint8_t hash[PSA_HASH_LENGTH(PSA_ALG_SHA_256)] __attribute__ ((aligned (4))) = {
  0x89, 0x01, 0x41, 0x9f, 0x26, 0x14, 0xc9, 0x42, 0xc9, 0xee, 0x5e, 0xfb, 0xdf, 0xba, 0x0c, 0xca,
  0x70, 0x6b, 0x3a, 0x4e, 0xd1, 0xa8, 0x5f, 0x69, 0x28, 0xb7, 0x60, 0xff, 0x1b, 0xba, 0xb0, 0xe7
};

/**
 * @brief Signature
 */
static uint8_t signature[PSA_SIGN_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR_BASE, 256u, PSA_ALG_ECDSA_ANY)] __attribute__ ((aligned (4))) = {0u};

/* Oracle-internal location defines, needed here to verify/show Oracle behaviour for generate key */
#ifndef PSA_KEY_LOCATION_ORACLE_S50_STORAGE
#define PSA_KEY_LOCATION_ORACLE_S50_STORAGE        ((psa_key_location_t)(0x03U))
#endif

#define LIFETIME_INTERNAL  PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_ORACLE_S50_STORAGE)
#define LIFETIME_EXTERNAL  PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)


/*
 * Example of ECDSA signature generation (in the Oracle S50 storage) and verification for:
 * - key size 256
 * - SHA-256
 * - signature scheme PSA_ALG_ECDSA_ANY
 */
bool mcuxClPsaDriver_ecdsa_keygen_oracleS50_sign_verify_hash_example(void)
{
  /** Initialize ELS, Enable the ELS **/
  if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /*
   * Generate a private key
   */

  /* Set up PSA key attributes for the private key to generate. */
  const psa_key_attributes_t genkey_attributes = {
    .core = {                                                            // Core attributes
      .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),         // Curve secp256r1
      .bits = 256u,                                                      // Private key size for curve secp256r1 in bits
      .lifetime = LIFETIME_INTERNAL,                                     // Volatile (RAM), Oracle S50 storage for private key
      .id = 0U,                                                          // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_SIGN_HASH,                                // Key may be used for signing a hash
        .alg = PSA_ALG_ECDSA_ANY,                                        // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE},
      .flags = 0U},                                                      // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U
  };

  size_t private_key_buffer_size = PSA_BITS_TO_BYTES(256u);
  uint32_t private_key_buffer[PSA_BITS_TO_BYTES(256u) / sizeof(uint32_t)] = {0u};
  size_t private_key_buffer_length = 0U;

  psa_status_t status = psa_driver_wrapper_generate_key(
              &genkey_attributes,
              (uint8_t *) private_key_buffer, private_key_buffer_size, &private_key_buffer_length);

  /* Check the return value */
  if(status != PSA_SUCCESS)
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Check the output length */
  if(private_key_buffer_length != PSA_BITS_TO_BYTES(256u))
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }


  /*
   * Sign hash: PSA_ALG_ECDSA_ANY, SHA_256
   */

  /* Set up PSA key attributes for the private key to generate a signature. */
  const psa_key_attributes_t sign_attributes = {
    .core = {                                                            // Core attributes
      .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),         // Curve secp256r1
      .bits = 256u,                                                      // Private key size for curve secp256r1 in bits
      .lifetime = LIFETIME_EXTERNAL,                                     // Volatile (RAM), local storage for private key
      .id = 0U,                                                          // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_SIGN_HASH,                                // Key may be used for signing a hash
        .alg = PSA_ALG_ECDSA_ANY,                                        // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE},
      .flags = 0U},                                                      // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U
  };

  size_t signature_length;

  status = psa_driver_wrapper_sign_hash(
    &sign_attributes,                // const psa_key_attributes_t *attributes,
    (uint8_t *) private_key_buffer,  // const uint8_t *key_buffer,
    private_key_buffer_size,         // size_t key_buffer_size,
    PSA_ALG_ECDSA_ANY,               // psa_algorithm_t alg,
    hash,                            // const uint8_t *hash,
    sizeof(hash),                    // size_t hash_length,
    signature,                       // uint8_t *signature,
    sizeof(signature),               // size_t signature_size,
    &signature_length                // size_t *signature_length
    );

  /* Check the return value */
  if(status != PSA_SUCCESS)
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Check the signature length */
  if(signature_length != PSA_SIGN_OUTPUT_SIZE(PSA_KEY_TYPE_ECC_KEY_PAIR_BASE, 256u, PSA_ALG_ECDSA_ANY))
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }


  /*
   * Export the public key to verify the signature
   */

  /* Set up PSA key attributes for the public key to export. */
  const psa_key_attributes_t export_attributes = {
    .core = {                                                            // Core attributes
      .type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),         // Curve secp256r1
      .bits = 256u,                                                      // Private key size for curve secp256r1 in bits
      .lifetime = LIFETIME_EXTERNAL,                                     // Volatile (RAM), local storage for public key
      .id = 0U,                                                          // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_EXPORT,                                   // Key may be used to export a public key
        .alg = PSA_ALG_ECDSA_ANY,                                        // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE},
      .flags = 0U},                                                      // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U
  };

  /* Call export_public_key operation */
  size_t public_key_buffer_size = 2u * PSA_BITS_TO_BYTES(256u) + 1u;
  uint8_t public_key_buffer[2u * PSA_BITS_TO_BYTES(256u) + 1u] = {0U};
  size_t public_key_buffer_length = 0U;

  status = psa_driver_wrapper_export_public_key(
              &export_attributes,
              (uint8_t *) private_key_buffer, private_key_buffer_length,
              public_key_buffer, public_key_buffer_size, &public_key_buffer_length);

  /* Check the return value */
  if(status != PSA_SUCCESS)
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Check the output length */
  if(public_key_buffer_length != public_key_buffer_size)
  {
      return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /*
   * Verify hash: PSA_ALG_ECDSA_ANY, SHA_256
   */

  /* Set up PSA key attributes for the public key to export. */
  const psa_key_attributes_t verify_attributes = {
    .core = {                                                            // Core attributes
      .type = PSA_KEY_TYPE_ECC_PUBLIC_KEY(PSA_ECC_FAMILY_SECP_R1),       // Curve secp256r1 public key
      .bits = 256u,                                                      // Private key size for curve secp256r1 in bits
      .lifetime = LIFETIME_EXTERNAL,                                     // Volatile (RAM), local storage for public key
      .id = 0U,                                                          // ID zero
      .policy = {
        .usage = PSA_KEY_USAGE_VERIFY_HASH,                              // Key may be used to verify a hash
        .alg = PSA_ALG_ECDSA_ANY,                                        // ECDSA signature scheme without specifying a hash algorithm
        .alg2 = PSA_ALG_NONE},
      .flags = 0U},                                                      // No flags
    .domain_parameters = NULL,
    .domain_parameters_size = 0U
  };

  status = psa_driver_wrapper_verify_hash(
    &verify_attributes,         // const psa_key_attributes_t *attributes,
    public_key_buffer,          // const uint8_t *key_buffer,
    public_key_buffer_size,     // size_t key_buffer_size,
    PSA_ALG_ECDSA_ANY,          // psa_algorithm_t alg,
    hash,                       // const uint8_t *hash,
    sizeof(hash),               // size_t hash_length,
    signature,                  // const uint8_t *signature,
    sizeof(signature)           // size_t signature_length
    );

  /* Check the return value */
  if(status != PSA_SUCCESS)
  {
    return MCUXCLEXAMPLE_STATUS_ERROR;
  }

  /* Return */
  return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_ecdsa_keygen_oracleS50_sign_verify_hash_example(void)
{
    bool result = mcuxClPsaDriver_ecdsa_keygen_oracleS50_sign_verify_hash_example();
    return result;
}
