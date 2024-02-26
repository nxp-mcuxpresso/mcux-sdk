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

#ifndef MCUXCLEXAMPLE_RFC3394_HELPER_H_
#define MCUXCLEXAMPLE_RFC3394_HELPER_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>
#include <mcuxClEls.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClMemory_Copy.h>

/**
 * Function that performs RFC3394 key wrapping.
 * @retval true  Wrapping successful.
 * @retval false Wrapping error. */
static inline bool mcuxClExample_rfc3394_wrap(
    const uint8_t * pInput,         //< pointer to key to be wrapped
    size_t inputLength,             //< length of key to be wrapped in bytes
    const uint8_t * pKek_in,        //< pointer to key wrapping key
    mcuxClEls_KeyIndex_t keyIdx,     //< keyslot index of key wrapping key
    uint8_t extkey,                 //< 0-use key stored internally at keyIdx as wrapping key, 1-use external pKek_in as wrapping key
    size_t kekLength,               //< length of key wrapping key in bytes
    uint8_t * pOutput,              //< pointer to output buffer, size has to be inputLength + 16 bytes
    mcuxClEls_KeyProp_t properties   //< properties of the key to be wrapped
)
{
    uint32_t concat[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };

    uint32_t input[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };
    uint8_t pKek[MCUXCLELS_CIPHER_KEY_SIZE_AES_256] = { 0u };

    if (extkey == MCUXCLELS_CIPHER_EXTERNAL_KEY)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (pKek,
                                                                     pKek_in,
                                                                     kekLength,
                                                                     kekLength));

        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
        {
            return false;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    }

    // Intermediate state is stored in pOutput as it is large enough

    // initialize buffer
    concat[0] = 0xA6A6A6A6u;   // first half of concat is the A from the standard, initialized to RFC3394 IV
    concat[1] = 0xA6A6A6A6u;
    concat[2] = properties.word.value;  // second half of concat is R(input)/B(output), first R consists of properties...
    concat[3] = 0x00000000u;            // ... and ELS padding (zeros)
    concat[2] = (concat[2] << 24u) | (concat[2] >> 24u) | ((concat[2] & 0x0000ff00u) << 8u) | ((concat[2] >> 8u) & 0x0000ff00u); // swap endianness

    // initialize ELS encryption parameters
    mcuxClEls_CipherOption_t cipher_options;
    cipher_options.word.value   = 0;
    cipher_options.bits.cphmde  = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipher_options.bits.dcrpt   = MCUXCLELS_CIPHER_ENCRYPT;
    cipher_options.bits.extkey  = extkey;

    // input has to be multiple of 64 bits
    if (inputLength % sizeof(uint64_t) != 0u)
    {
        return false;
    }

    uint32_t *pSource = (uint32_t*) pInput;
    uint32_t *pDest   = (uint32_t*) pOutput;
    uint32_t std_n = inputLength/sizeof(uint64_t) + 1; // n value from standard
    for(size_t jdx = 0u; jdx < 6u; jdx++)
    {
        for(size_t idx = 0u; idx < std_n; idx++)
        {
            input[0]=concat[0];
            input[1]=concat[1];
            input[2]=concat[2];
            input[3]=concat[3];

            // Encrypt concatenated A and chunk to be processed
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Cipher_Async(
                cipher_options,
                keyIdx,
                pKek,
                kekLength,
                (uint8_t*) input,
                MCUXCLELS_CIPHER_BLOCK_SIZE_AES,
                NULL,
                (uint8_t*) concat));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            // Write out processed key chunk
            pDest[2u*idx + 2u] = concat[2u];
            pDest[2u*idx + 3u] = concat[3u];

            if( idx == std_n - 1u)
            {
                // Load next key chunk
                concat[2u] = pDest[2u];
                concat[3u] = pDest[3u];
                pSource = pDest + 4;
            }
            else
            {
                // Load next key chunk
                concat[2u] = pSource[2u*idx + 0u];
                concat[3u] = pSource[2u*idx + 1u];
            }

            // XOR round constant into A
            uint32_t gdx = std_n * jdx + (idx+1);  // all values should fit into a uint32_t
            gdx = (gdx << 24u) | (gdx >> 24u) | ((gdx & 0x0000ff00u) << 8u) | ((gdx >> 8u) & 0x0000ff00u); // swap endianness
            concat[1u] ^= gdx;
        }
    }
    // Write out processed key chunk
    pDest[0u] = concat[0u];
    pDest[1u] = concat[1u];

    return true;
}

/**
 * Function that performs RFC3394 key unwrapping.
 * @retval true  Unwrapping successful.
 * @retval false Unwrapping error. */
static inline bool mcuxClExample_rfc3394_unwrap(
    const uint8_t * pInput,        //< pointer to rfc3394 blob to be wrapped
    size_t inputLength,            //< length of key the rfc3394 blob in bytes
    const uint8_t * pKek_in,       //< pointer to key wrapping key
    mcuxClEls_KeyIndex_t keyIdx,    //< keyslot index of key wrapping key
    uint8_t extkey,                //< 0-use key stored internally at keyIdx as wrapping key, 1-use external pKek_in as wrapping key
    size_t kekLength,              //< length of key wrapping key in bytes
    uint8_t * pOutput              //< pointer to output buffer, size has to inputLength - 8 bytes, contents will be properties|zeros|key
)
{
    uint32_t concat[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };

    uint32_t input[MCUXCLELS_CIPHER_BLOCK_SIZE_AES/sizeof(uint32_t)] = { 0u };
    uint8_t pKek[MCUXCLELS_CIPHER_KEY_SIZE_AES_256] = { 0u };

    if (extkey == MCUXCLELS_CIPHER_EXTERNAL_KEY)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_VOID_BEGIN(token, mcuxClMemory_copy (pKek,
                                                                     pKek_in,
                                                                     kekLength,
                                                                     kekLength));

        if (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) != token)
        {
            return false;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_VOID_END();
    }

    // initialize buffer
    concat[0] = ((uint32_t*) pInput)[0];     // first half of concat is the A from the standard, to first chunk of input
    concat[1] = ((uint32_t*) pInput)[1];

    // initialize ELS encryption parameters
    mcuxClEls_CipherOption_t cipher_options;
    cipher_options.word.value   = 0;
    cipher_options.bits.cphmde  = MCUXCLELS_CIPHERPARAM_ALGORITHM_AES_ECB;
    cipher_options.bits.dcrpt   = MCUXCLELS_CIPHER_DECRYPT;
    cipher_options.bits.extkey  = extkey;

    // input has to be multiple of 64 bits
    if (inputLength % sizeof(uint64_t) != 0u)
    {
        return false;
    }


    uint32_t std_n = inputLength/sizeof(uint64_t) - 1; // n value from standard
    uint32_t *pSource = ((uint32_t*) pInput ) + 2u; // skip first 64 bits
    uint32_t *pDest   = ((uint32_t*) pOutput) + 0u;
    for(size_t jdx = 6u; jdx > 0u; jdx--)
    {
        for(size_t idx = std_n; idx > 0u; idx--)
        {
            // Load next key chunk
            concat[2u] = pSource[2u*(idx-1) + 0u];
            concat[3u] = pSource[2u*(idx-1) + 1u];

            // XOR round constant into A
            uint32_t gdx = std_n * (jdx-1u) + idx;  // all values should fit into a uint32_t
            gdx = (gdx << 24u) | (gdx >> 24u) | ((gdx & 0x0000ff00u) << 8u) | ((gdx >> 8u) & 0x0000ff00u); // swap endianness
            concat[1u] ^= gdx;

            input[0]=concat[0];
            input[1]=concat[1];
            input[2]=concat[2];
            input[3]=concat[3];

            // Decrypt concatenated A and chunk to be processed
            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Cipher_Async(
                cipher_options,
                keyIdx,
                pKek,
                kekLength,
                (uint8_t*) input,
                MCUXCLELS_CIPHER_BLOCK_SIZE_AES,
                NULL,
                (uint8_t*) concat));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Cipher_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
            {
                return false;
            }
            MCUX_CSSL_FP_FUNCTION_CALL_END();

            // Write out processed key chunk
            pDest[2u*(idx-1) + 0u] = concat[2u];
            pDest[2u*(idx-1) + 1u] = concat[3u];
        }
        pSource = pDest;
    }
    pDest[0] = (pDest[0] << 24u) | (pDest[0] >> 24u) | ((pDest[0] & 0x0000ff00u) << 8u) | ((pDest[0] >> 8u) & 0x0000ff00u); // swap endianness
    // Check padding
    if((concat[0u] != 0xA6A6A6A6u) || (concat[1u] != 0xA6A6A6A6u))
    {
        return false;
    }
    return true;
}

#endif /* MCUXCLEXAMPLE_RFC3394_HELPER_H_ */
