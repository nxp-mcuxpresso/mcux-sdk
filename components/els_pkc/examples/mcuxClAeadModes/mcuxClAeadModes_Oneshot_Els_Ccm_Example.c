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
 * @file:  mcuxClAeadModes_Oneshot_Els_Ccm_Example.c
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

/* NIST Special Publication 800-38C example 2 test vectors */
static const uint8_t msg_plain[16] = {
  0x20u, 0x21u, 0x22u, 0x23u, 0x24u, 0x25u, 0x26u, 0x27u,
  0x28u, 0x29u, 0x2au, 0x2bu, 0x2cu, 0x2du, 0x2eu, 0x2fu
};

static const uint8_t msg_adata[16] = {
  0x00u, 0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u,
  0x08u, 0x09u, 0x0au, 0x0bu, 0x0cu, 0x0du, 0x0eu, 0x0fu
};

static const uint8_t aes128_iv[8] = {
  0x10u, 0x11u, 0x12u, 0x13u, 0x14u, 0x15u, 0x16u, 0x17u
};

static const uint8_t aes128_key[16] = {
  0x40u, 0x41u, 0x42u, 0x43u, 0x44u, 0x45u, 0x46u, 0x47u,
  0x48u, 0x49u, 0x4au, 0x4bu, 0x4cu, 0x4du, 0x4eu, 0x4fu
};

static const uint8_t msg_tag_expected[6] = {
  0x1fu, 0xc6u, 0x4fu, 0xbfu, 0xacu, 0xcdu
};

static const uint8_t msg_enc_expected[16] = {
  0xd2u, 0xa1u, 0xf0u, 0xe0u, 0x51u, 0xeau, 0x5fu, 0x62u,
  0x08u, 0x1au, 0x77u, 0x92u, 0x07u, 0x3du, 0x59u, 0x3du
};

MCUXCLEXAMPLE_FUNCTION(mcuxClAeadModes_Oneshot_Els_Ccm_Example)
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

    uint8_t msg_tag[sizeof(msg_tag_expected)];

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_enc, token_enc, mcuxClAead_crypt(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClKey_Handle_t key,         */ key,
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_CCM_ENC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* mcuxCl_InputBuffer_t pIn,       */ msg_plain,
    /* uint32_t inSize,               */ sizeof(msg_plain),
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* mcuxCl_Buffer_t pOut,           */ msg_enc,
    /* uint32_t * const pOutSize      */ &msg_enc_size,
    /* mcuxCl_Buffer_t pTag,           */ msg_tag,
    /* uint32_t tagSize               */ sizeof(msg_tag_expected)
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
    for (size_t i = 0U; i < sizeof(msg_tag_expected); i++)
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
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_CCM_DEC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* mcuxCl_InputBuffer_t pIn,       */ msg_enc,
    /* uint32_t inSize,               */ msg_enc_size,
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* mcuxCl_Buffer_t pOut,           */ msg_dec,
    /* uint32_t * const pOutSize      */ &msg_dec_size,
    /* mcuxCl_Buffer_t pTag,          */ msg_tag,
    /* uint32_t tagSize               */ sizeof(msg_tag_expected)
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
