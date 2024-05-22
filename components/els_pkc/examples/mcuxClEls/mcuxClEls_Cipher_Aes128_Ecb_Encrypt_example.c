/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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
 * @file  mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
 * @brief Example AES-128 ECB encryption using the ELS (CLNS component mcuxClEls)
 *
 * @example  mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
 * @brief    Example AES-128 ECB encryption using the ELS (CLNS component mcuxClEls)
 */

#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClCore_Examples.h>
#include <mcuxClExample_ELS_Helper.h>

/** Plaintext input for the AES encryption. */
static uint8_t const aes128_input[MCUXCLELS_CIPHER_BLOCK_SIZE_AES] = {0x6BU, 0xC1U, 0xBEU, 0xE2U,
                                                                     0x2EU, 0x40U, 0x9FU, 0x96U,
                                                                     0xE9U, 0x3DU, 0x7EU, 0x11U,
                                                                     0x73U, 0x93U, 0x17U, 0x2AU};

/** Expected ciphertext output of the AES encryption. */
static uint8_t const aes128_expected_output[MCUXCLELS_CIPHER_BLOCK_SIZE_AES] = {0x3AU, 0xD7U, 0x7BU, 0xB4U,
                                                                               0x0DU, 0x7AU, 0x36U, 0x60U,
                                                                               0xA8U, 0x9EU, 0xCAU, 0xF3U,
                                                                               0x24U, 0x66U, 0xEFU, 0x97U};

/** Key for the AES encryption. */
static uint32_t const aes128_key[MCUXCLELS_CIPHER_KEY_SIZE_AES_128 / sizeof(uint32_t)] = {0x16157E2B, 0xA6D2AE28, 0x8815F7AB, 0x3C4FCF09};

/** Destination buffer to receive the ciphertext output of the AES encryption. */
static uint8_t aes128_output[MCUXCLELS_CIPHER_BLOCK_SIZE_AES];



/** Performs AES-128 ECB encryption using mcuxClEls functions.
 * @retval MCUXCLEXAMPLE_STATUS_OK    The example code completed successfully
 * @retval MCUXCLEXAMPLE_STATUS_ERROR The example code failed */
MCUXCLEXAMPLE_FUNCTION(mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example)
{
    /** Initialize ELS, Enable the ELS **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    
    mcuxClEls_CipherOption_t cipher_options = {0U};                        // Initialize a new configuration for the planned mcuxClEls_Cipher_Async operation.
    cipher_options.bits.cphmde = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;  // Configure the AES block cipher mode of operation to be the ECB (Electronic Codebook) mode.
    cipher_options.bits.dcrpt = MCUXCLELS_CIPHER_ENCRYPT;                  // Configure that the mcuxClEls_Cipher_Async operation shall perform  encryption.
    cipher_options.bits.extkey = MCUXCLELS_CIPHER_EXTERNAL_KEY;            // Configure that an external key should be used.
            
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Cipher_Async( // Perform the encryption.
            cipher_options,                                 // Set the prepared configuration.
            (mcuxClEls_KeyIndex_t) 0U,                       // This parameter (keyIdx) is ignored, since an external key is used.
            (const uint8_t *) aes128_key, MCUXCLELS_CIPHER_KEY_SIZE_AES_128,   // The AES key for the encryption (external key).
            aes128_input, sizeof(aes128_input),             // The plaintext to encrypt. Note that this plaintext's length is a multiple of the block length, so no padding is required.
            NULL,                                           // This parameter (pIV) is ignored, since the ECB mode is used.
            aes128_output                                   // Output buffer, which the operation will write the ciphertext to.
            ));
    // mcuxClEls_Cipher_Async is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that no error occurred, meaning that the mcuxClEls_Cipher_Async operation was started.
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
    
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Cipher_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    for (size_t i = 0U; i < sizeof(aes128_output); i++)
    {
        if (aes128_output[i] != aes128_expected_output[i])
        {
           return MCUXCLEXAMPLE_STATUS_ERROR; // Expect that the resulting ciphertext matches our expected output
        }
    }
    
    /** Disable the ELS **/
    if(!mcuxClExample_Els_Disable())
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    
    return MCUXCLEXAMPLE_STATUS_OK;
}
