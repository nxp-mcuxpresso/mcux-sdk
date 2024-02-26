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

/**
 * @file:  mcuxClAeadModes_Oneshot_Els_Gcm_Example.c
 * @brief: Example Aead application
 */

#include <mcuxClExample_ELS_Helper.h>
#include <mcuxClExample_Session_Helper.h>
#include <mcuxClExample_Key_Helper.h>
#include <mcuxClEls.h> // Interface to the entire mcuxClEls component
#include <mcuxClSession.h> // Interface to the entire mcuxClSession component
#include <mcuxClKey.h> // Interface to the entire mcuxClKey component
#include <mcuxClAes.h> // Interface to AES-related definitions and types
#include <mcuxClAead.h> // Interface to the entire mcuxClAead component
#include <mcuxClAeadModes.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h> // Code flow protection
#include <mcuxClToolchain.h> // memory segment definitions
#include <mcuxClCore_Examples.h>
#include <stdbool.h>  // bool type for the example's return code
#include <mcuxClExample_RNG_Helper.h>

/** Key for the AES encryption. */
static uint8_t aes128_key[16u] = {0x2BU, 0x7EU, 0x15U, 0x16U,
                                  0x28U, 0xAEU, 0xD2U, 0xA6U,
                                  0xABU, 0xF7U, 0x15U, 0x88U,
                                  0x09U, 0xCFU, 0x4FU, 0x3CU};

/** IV of the AES encryption. */
static uint8_t aes128_iv[12u] = {0xF8U, 0xD2U, 0x68U, 0x76U,
                                 0x81U, 0x6FU, 0x0FU, 0xBAU,
                                 0x86U, 0x2BU, 0xD8U, 0xA3U};

/** Plaintext input for the AES encryption. */
static uint8_t const msg_plain[16u] = {0x6BU, 0xC1U, 0xBEU, 0xE2U,
                                       0x2EU, 0x40U, 0x9FU, 0x96U,
                                       0xE9U, 0x3DU, 0x7EU, 0x11U,
                                       0x73U, 0x93U, 0x17U, 0x2AU};

/** Additional authenticated data. */
static uint8_t const msg_adata[16u] = {0xCAU, 0xEAU, 0x07U, 0x26U,
                                       0x62U, 0xE2U, 0x20U, 0x06U,
                                       0x2DU, 0x45U, 0x46U, 0x41U,
                                       0x5EU, 0xFFU, 0xFAU, 0xD2U};

/** Expected ciphertext output of the AES-GCM encryption. */
static uint8_t const msg_enc_expected[16u] = {0x4FU, 0x74U, 0x2DU, 0xF6U,
                                              0x9DU, 0x1CU, 0x03U, 0x6BU,
                                              0x56U, 0xBCU, 0xC2U, 0x81U,
                                              0x5FU, 0xDAU, 0x8DU, 0x6DU};

/** Expected authentication tag output. */
static uint8_t const msg_tag_expected[16u] = {0xB2U, 0xC5U, 0xCFU, 0xC3U,
                                              0xF2U, 0x8CU, 0x9FU, 0x78U,
                                              0xFCU, 0x25U, 0xBCU, 0x10U,
                                              0xC9U, 0xCAU, 0xFFU, 0xD5U};

MCUXCLEXAMPLE_FUNCTION(mcuxClAeadModes_Oneshot_Els_Gcm_Example)
{
    /**************************************************************************/
    /* Preparation                                                            */
    /**************************************************************************/

    /** Initialize ELS, MCUXCLELS_RESET_DO_NOT_CANCEL **/
    if(!mcuxClExample_Els_Init(MCUXCLELS_RESET_DO_NOT_CANCEL))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /* Initialize session */
    mcuxClSession_Descriptor_t sessionDesc;
    mcuxClSession_Handle_t session = &sessionDesc;

    /* Allocate and initialize session */
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLAEAD_CRYPT_CPU_WA_BUFFER_SIZE + MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE, 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);

    /* Initialize key */
    uint32_t keyDesc[MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) &keyDesc;

    /* Set key properties. */
    mcuxClEls_KeyProp_t key_properties;

    key_properties.word.value = 0u;
    key_properties.bits.ksize = MCUXCLELS_KEYPROPERTY_KEY_SIZE_128;
    key_properties.bits.kactv = MCUXCLELS_KEYPROPERTY_ACTIVE_TRUE;

    uint32_t dstData[8];
    //Initializes a key handle, Set key properties and Load key.
    if(!mcuxClExample_Key_Init_And_Load(session,
                                       key,
                                       mcuxClKey_Type_Aes128,
                                       (mcuxCl_Buffer_t) aes128_key,
                                       sizeof(aes128_key),
                                       &key_properties,
                                       dstData, MCUXCLEXAMPLE_CONST_EXTERNAL_KEY))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }

    /**************************************************************************/
    /* Encryption                                                             */
    /**************************************************************************/

    uint8_t msg_enc[sizeof(msg_enc_expected)];
    uint32_t msg_enc_size = 0u;

    uint8_t msg_tag[32];

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_enc, token_enc, mcuxClAead_crypt(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClKey_Handle_t key,         */ key,
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_GCM_ENC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* mcuxCl_InputBuffer_t pIn,       */ msg_plain,
    /* uint32_t inSize,               */ sizeof(msg_plain),
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* mcuxCl_Buffer_t pOut,           */ msg_enc,
    /* uint32_t * const pOutSize      */ &msg_enc_size,
    /* mcuxCl_Buffer_t pTag,           */ msg_tag,
    /* uint32_t tagSize               */ 16u
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_crypt) != token_enc) || (MCUXCLAEAD_STATUS_OK != result_enc))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    for (size_t i = 0U; i < msg_enc_size; i++)
    {
        if (msg_enc[i] != msg_enc_expected[i]) // Expect that the resulting encrypted msg matches our expected output
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }
    // TODO: change to MCUXCLELS_AEAD_TAG_SIZE
    for (size_t i = 0U; i < 16u; i++)
    {
        if (msg_tag[i] != msg_tag_expected[i]) // Expect that the resulting authentication tag matches our expected output
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }


    /**************************************************************************/
    /* Decryption                                                             */
    /**************************************************************************/

    uint8_t msg_dec[sizeof(msg_plain)];
    uint32_t msg_dec_size = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_dec, token_dec, mcuxClAead_crypt(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClKey_Handle_t key,         */ key,
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_GCM_DEC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* mcuxCl_InputBuffer_t pIn,       */ msg_enc,
    /* uint32_t inSize,               */ msg_enc_size,
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* mcuxCl_Buffer_t pOut,           */ msg_dec,
    /* uint32_t * const pOutSize      */ &msg_dec_size,
    /* mcuxCl_Buffer_t pTag,           */ msg_tag,
    /* uint32_t tagSize               */ 16u
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_crypt) != token_dec) || (MCUXCLAEAD_STATUS_OK != result_dec))
    {
         return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    for (size_t i = 0U; i < msg_dec_size; i++)
    {
        if (msg_dec[i] != msg_plain[i]) // Expect that the resulting decrypted msg matches our initial message
        {
            return MCUXCLEXAMPLE_STATUS_ERROR;
        }
    }

    /**************************************************************************/
    /* Cleanup                                                                */
    /**************************************************************************/

    /* Flush the key. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClKey_flush(session, key));

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
