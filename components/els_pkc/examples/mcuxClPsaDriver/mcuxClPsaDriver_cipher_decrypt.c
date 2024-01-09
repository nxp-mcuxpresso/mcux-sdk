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
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>
#include <mcuxClCore_Examples.h>
#include <mcuxClAes.h> // Interface to AES-related definitions and types
#include <mcuxClExample_ELS_Helper.h>

#define LIFETIME_INTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_EXTERNAL_STORAGE)
#define LIFETIME_EXTERNAL PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_LIFETIME_VOLATILE, PSA_KEY_LOCATION_LOCAL_STORAGE)

bool mcuxClPsaDriver_cipher_decrypt(void)
{
	/* Expected output for the AES operation */
    const uint8_t aes128_result[MCUXCLAES_BLOCK_SIZE] = {
        0x6b, 0xc1, 0xbe, 0xe2,
        0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11,
        0x73, 0x93, 0x17, 0x2a
    };


	/* Input for the AES operation */
    const uint8_t aes128_input[MCUXCLAES_BLOCK_SIZE] = {
        0x3a, 0xd7, 0x7b, 0xb4,
        0x0d, 0x7a, 0x36, 0x60,
        0xa8, 0x9e, 0xca, 0xf3,
        0x24, 0x66, 0xef, 0x97
    };

	/* AES key */
    const uint8_t aes128_key[MCUXCLELS_CIPHER_KEY_SIZE_AES_128] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

	/* Output buffer for the AES operation */
	uint8_t aes128_output[MCUXCLAES_BLOCK_SIZE];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

	/* Set up PSA key attributes. */
    psa_key_attributes_t attributes = {
		.core = {								// Core attributes
			.type = PSA_KEY_TYPE_AES, 			// Key is for AES operations
			.bits = 0U, 						// No key bits
			.lifetime = LIFETIME_EXTERNAL,      // Volatile (RAM), Local Storage (plain) key
			.id = 0U, 							// ID zero
			.policy = {
				.usage = PSA_KEY_USAGE_DECRYPT, // Key may be used for decryption
				.alg = PSA_ALG_ECB_NO_PADDING, 	// Key may be used for ECB mode without padding only
				.alg2 = PSA_ALG_NONE},
			.flags = 0u}, 						// No flags
		.domain_parameters = NULL,				// No domain parameters
		.domain_parameters_size = 0u};

	/* Variable for the output length of the decrypt operation */
	size_t output_length = 0u;

	/* Call the decryption operation */
	psa_status_t result = psa_driver_wrapper_cipher_decrypt(
		&attributes, 						// const psa_key_attributes_t *attributes,
		aes128_key, 						// const uint8_t *key_buffer
		MCUXCLELS_CIPHER_KEY_SIZE_AES_128,   // size_t key_buffer_size
		PSA_ALG_ECB_NO_PADDING, 			// psa_algorithm_t alg
		aes128_input, 						// const uint8_t *input
		MCUXCLAES_BLOCK_SIZE, 	// size_t input_length
		aes128_output,						// uint8_t *output
		MCUXCLAES_BLOCK_SIZE,		// size_t output_size
		&output_length);					// size_t *output_length

	/* Check the return value */
	if(result != PSA_SUCCESS) {
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}

	/* Check the output length */
	if(output_length != MCUXCLAES_BLOCK_SIZE) {
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}

	/* Check the content */
    for (size_t i = 0U; i < MCUXCLAES_BLOCK_SIZE; i++)
    {
        if (aes128_output[i] != aes128_result[i]) // Expect that the resulting decrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

	/* Return */
	return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_cipher_decrypt(void)
{
    bool result = mcuxClPsaDriver_cipher_decrypt();
    return result;
}
