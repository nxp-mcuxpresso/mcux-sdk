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
 * @file:  mcuxClAeadModes_Multipart_Els_Ccm_Example.c
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

static const uint8_t msg_plain[24] = {
  0x20u, 0x21u, 0x22u, 0x23u, 0x24u, 0x25u, 0x26u, 0x27u,
  0x28u, 0x29u, 0x2au, 0x2bu, 0x2cu, 0x2du, 0x2eu, 0x2fu,
  0x30u, 0x31u, 0x32u, 0x33u, 0x34u, 0x35u, 0x36u, 0x37u
};

static const uint8_t msg_adata[20] = {
  0x00u, 0x01u, 0x02u, 0x03u, 0x04u, 0x05u, 0x06u, 0x07u,
  0x08u, 0x09u, 0x0au, 0x0bu, 0x0cu, 0x0du, 0x0eu, 0x0fu,
  0x10u, 0x11u, 0x12u, 0x13u
};

static const uint8_t aes128_iv[12] = {
  0x10u, 0x11u, 0x12u, 0x13u, 0x14u, 0x15u, 0x16u, 0x17u,
  0x18u, 0x19u, 0x1au, 0x1bu
};

static const uint8_t aes128_key[16] = {
  0x40u, 0x41u, 0x42u, 0x43u, 0x44u, 0x45u, 0x46u, 0x47u,
  0x48u, 0x49u, 0x4au, 0x4bu, 0x4cu, 0x4du, 0x4eu, 0x4fu
};

static const uint8_t msg_tag_expected[8] = {
  0x48u, 0x43u, 0x92u, 0xfbu, 0xc1u, 0xb0u, 0x99u, 0x51
};

static const uint8_t msg_enc_expected[24] = {
  0xe3u, 0xb2u, 0x01u, 0xa9u, 0xf5u, 0xb7u, 0x1au, 0x7a,
  0x9bu, 0x1cu, 0xeau, 0xecu, 0xcdu, 0x97u, 0xe7u, 0x0b,
  0x61u, 0x76u, 0xaau, 0xd9u, 0xa4u, 0x42u, 0x8au, 0xa5
};

MCUXCLEXAMPLE_FUNCTION(mcuxClAeadModes_Multipart_Els_Ccm_Example)
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
    MCUXCLEXAMPLE_ALLOCATE_AND_INITIALIZE_SESSION(session, MCUXCLAEAD_WA_SIZE_MAX + MCUXCLRANDOMMODES_NCINIT_WACPU_SIZE, 0u);

    /* Initialize the PRNG */
    MCUXCLEXAMPLE_INITIALIZE_PRNG(session);

    /* Initialize key */
    uint32_t keyDesc[MCUXCLKEY_DESCRIPTOR_SIZE_IN_WORDS];
    mcuxClKey_Handle_t key = (mcuxClKey_Handle_t) &keyDesc;

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

    uint8_t ctxBuf[MCUXCLAEAD_CONTEXT_SIZE];
    mcuxClAead_Context_t *ctx = (mcuxClAead_Context_t *) ctxBuf;

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_init, token_init, mcuxClAead_init(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxClKey_Handle_t key,         */ key,
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_CCM_ENC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* uint32_t inSize,               */ sizeof(msg_plain),
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* uint32_t tagSize               */ sizeof(msg_tag_expected)
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_init) != token_init) || (MCUXCLAEAD_STATUS_OK != result_init))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

  /*
   * mcuxClAead_process_adata() processes the header data. This needs to be completed
   * before other data can be processed. Therefore all calls to mcuxClAead_process_adata()
   * need to be made before calls to mcuxClAead_process().
   */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_aad, token_aad, mcuxClAead_process_adata(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata)
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process_adata) != token_aad) || (MCUXCLAEAD_STATUS_OK != result_aad))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_indata, token_indata, mcuxClAead_process(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_InputBuffer_t pIn,       */ msg_plain,
    /* uint32_t inSize,               */ sizeof(msg_plain),
    /* mcuxCl_Buffer_t pOut,           */ msg_enc,
    /* uint32_t * const pOutSize      */ &msg_enc_size
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process) != token_indata) || (MCUXCLAEAD_STATUS_OK != result_indata))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_final, token_final, mcuxClAead_finish(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_Buffer_t pOut,           */ &msg_enc[msg_enc_size],
    /* uint32_t * const pOutSize      */ &msg_enc_size,
    /* mcuxCl_Buffer_t pTag,           */ msg_tag
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_finish) != token_final) || (MCUXCLAEAD_STATUS_OK != result_final))
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

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_init, token_init, mcuxClAead_init(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxClKey_Handle_t key,         */ key,
    /* mcuxClAead_Mode_t mode,         */ mcuxClAead_Mode_AES_CCM_DEC,
    /* mcuxCl_InputBuffer_t pNonce,    */ aes128_iv,
    /* uint32_t nonceSize,            */ sizeof(aes128_iv),
    /* uint32_t inSize,               */ sizeof(msg_plain),
    /* uint32_t adataSize,            */ sizeof(msg_adata),
    /* uint32_t tagSize               */ sizeof(msg_tag_expected)
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_init) != token_init) || (MCUXCLAEAD_STATUS_OK != result_init))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

  /*
   * mcuxClAead_process_adata() processes the header data. This needs to be completed
   * before other data can be processed. Therefore all calls to mcuxClAead_process_adata()
   * need to be made before calls to mcuxClAead_process().
   */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_aad, token_aad, mcuxClAead_process_adata(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_InputBuffer_t pAdata,    */ msg_adata,
    /* uint32_t adataSize,            */ sizeof(msg_adata)
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process_adata) != token_aad) || (MCUXCLAEAD_STATUS_OK != result_aad))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_indata, token_indata, mcuxClAead_process(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_InputBuffer_t pIn,       */ msg_enc,
    /* uint32_t inSize,               */ msg_enc_size,
    /* mcuxCl_Buffer_t pOut,           */ msg_dec,
    /* uint32_t * const pOutSize      */ &msg_dec_size
    ));

    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_process) != token_indata) || (MCUXCLAEAD_STATUS_OK != result_indata))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result_verify, token_verify, mcuxClAead_verify(
    /* mcuxClSession_Handle_t session, */ session,
    /* mcuxClAead_Context_t pContext,  */ ctx,
    /* mcuxCl_Buffer_t pTag,           */ msg_tag,
    /* mcuxCl_Buffer_t pOut,           */ &msg_dec[msg_dec_size],
    /* uint32_t * const pOutSize      */ &msg_dec_size
    ));
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClAead_verify) != token_verify) || (MCUXCLAEAD_STATUS_OK != result_verify))
    {
        return MCUXCLEXAMPLE_STATUS_ERROR;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

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
