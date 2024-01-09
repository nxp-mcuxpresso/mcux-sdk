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

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClHash.h>             // Interface to the entire mcuxClHash component
#include <mcuxClHashModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClToolchain.h> // memory segment definitions
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClPsaDriver.h>

bool mcuxClPsaDriver_sha224_oneshot_example(void)
{
	/* Input for the SHA-224 operation */
    const uint8_t data[3] = {
        0x61u, 0x62u, 0x63u
    };

	/* Expected output for the SHA-224 operation */
    const uint8_t hashExpected[MCUXCLHASH_OUTPUT_SIZE_SHA_224] = {
        0x23u, 0x09u, 0x7Du, 0x22u, 0x34u, 0x05u, 0xD8u, 0x22u,
        0x86u, 0x42u, 0xA4u, 0x77u, 0xBDu, 0xA2u, 0x55u, 0xB3u,
        0x2Au, 0xADu, 0xBCu, 0xE4u, 0xBDu, 0xA0u, 0xB3u, 0xF7u,
        0xE3u, 0x6Cu, 0x9Du, 0xA7u
    };

	/* Output buffer for the SHA-224 operation */
    uint8_t hashOutput[MCUXCLHASH_OUTPUT_SIZE_SHA_224];

    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

	/* Variable for the output length of the encryption operation */
	size_t hashOutput_length;

	/* Call the hashing operation */
	psa_status_t result = psa_driver_wrapper_hash_compute(
	    PSA_ALG_SHA_224,                     // psa_algorithm_t alg
	    data,                                // const uint8_t *input
	    sizeof(data),                        // size_t input_length
	    hashOutput,                          // uint8_t *hash
	    MCUXCLHASH_OUTPUT_SIZE_SHA_224,       // size_t hash_size
	    &hashOutput_length);                 // size_t *hash_length

	/* Check the return value */
	if(result != PSA_SUCCESS) {
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}

	/* Check the output length */
	if(hashOutput_length != MCUXCLHASH_OUTPUT_SIZE_SHA_224) {
		return MCUXCLEXAMPLE_STATUS_ERROR;
	}

	/* Check the content */
    for (size_t i = 0U; i < MCUXCLHASH_OUTPUT_SIZE_SHA_224; i++)
    {
        if (hashOutput[i] != hashExpected[i]) // Expect that the resulting encrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

	/* Return */
	return MCUXCLEXAMPLE_STATUS_OK;
}
bool nxpClPsaDriver_sha224_oneshot_example(void)
{
    bool result = mcuxClPsaDriver_sha224_oneshot_example();
    return result;
}
