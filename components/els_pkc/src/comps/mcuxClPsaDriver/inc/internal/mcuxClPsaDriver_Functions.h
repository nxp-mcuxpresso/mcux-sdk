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

/** @file  mcuxClPsaDriver_Functions.h
 *  @brief Helper function definitions for the mcuxClPsaDriver component
 */

#ifndef MCUXCLPSADRIVER_FUNCTIONS_H_
#define MCUXCLPSADRIVER_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <crypto_types.h>

#include <mcuxClAeadModes.h>
#include <mcuxClCipherModes.h>
#include <mcuxClMacModes.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClRsa_Types.h>

#include <internal/mcuxClEcc_Weier_Internal.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClKey_Types_Internal.h>

/**
 * @defgroup mcuxClPsaDriver_Functions mcuxClPsaDriver_Functions
 * @brief Defines all internal functions of @ref mcuxClPsaDriver
 * @ingroup mcuxClPsaDriver
 * @{
 */

extern unsigned int psa_driver_wrapper_get_clns_operation_id(void);

static inline bool key_type_is_raw_bytes( psa_key_type_t type )
{
    return( PSA_KEY_TYPE_IS_UNSTRUCTURED( type ) );
}

static inline bool mcuxClPsaDriver_psa_driver_wrapper_aead_doesKeyPolicySupportAlg(const psa_key_attributes_t *attributes, psa_algorithm_t alg)
{
    return (PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(attributes->core.policy.alg) == PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg));
}

static inline bool mcuxClPsaDriver_psa_driver_wrapper_aead_isAlgSupported(const psa_key_attributes_t *attributes)
{
    return ((attributes->core.type == PSA_KEY_TYPE_AES)
                && (PSA_ALG_IS_AEAD_ON_BLOCK_CIPHER(attributes->core.policy.alg)));
}

static inline mcuxClAead_Mode_t mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeEnc(const psa_algorithm_t alg)
{
    /* Recover default algorithm (could be CCM with changed tag size) */
    const psa_algorithm_t algDefault = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);

    const mcuxClAead_ModeDescriptor_t * mode = NULL;
    switch(algDefault)
    {
        case PSA_ALG_CCM:
        case PSA_ALG_CCM_STAR_NO_TAG:
            mode = mcuxClAead_Mode_AES_CCM_ENC;
            break;
        case PSA_ALG_GCM:
            mode = mcuxClAead_Mode_AES_GCM_ENC;
            break;
        default:
            mode = NULL;
            break;
    }
    return (mcuxClAead_Mode_t) mode;
}

static inline bool mcuxClPsaDriver_psa_driver_wrapper_cipher_isAlgSupported(const psa_key_attributes_t *attributes)
{
    if( PSA_KEY_TYPE_AES == attributes->core.type
               && (   PSA_ALG_ECB_NO_PADDING == attributes->core.policy.alg
                   || PSA_ALG_CBC_NO_PADDING == attributes->core.policy.alg
                   || PSA_ALG_CTR            == attributes->core.policy.alg ))
    {
        return true;
    }

    return false;
}

static inline bool mcuxClPsaDriver_psa_driver_wrapper_cipher_doesKeyPolicySupportAlg(const psa_key_attributes_t *attributes, psa_algorithm_t alg)
{
    return (attributes->core.policy.alg == alg);
}

static inline uint8_t mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectEnc(const psa_algorithm_t alg,
                                                   const mcuxClCipher_ModeDescriptor_t **mode)
{
    uint8_t iv_required = 1u;
    switch (alg)
    {
    case PSA_ALG_ECB_NO_PADDING:
        *mode = mcuxClCipher_Mode_AES_ECB_Enc_NoPadding;
        iv_required = 0u;
        break;
    case PSA_ALG_CBC_NO_PADDING:
        *mode = mcuxClCipher_Mode_AES_CBC_Enc_NoPadding;
        break;
    case PSA_ALG_CTR:
        *mode = mcuxClCipher_Mode_AES_CTR;
        break;
    default:
        *mode = NULL;
        iv_required = 0u;
        break;
    }

    return iv_required;
}

static inline mcuxClAead_Mode_t mcuxClPsaDriver_psa_driver_wrapper_aead_selectModeDec(const psa_algorithm_t alg)
{
    /* Recover default algorithm (could be CCM with changed tag size) */
    const psa_algorithm_t algDefault = PSA_ALG_AEAD_WITH_DEFAULT_LENGTH_TAG(alg);

    const mcuxClAead_ModeDescriptor_t *mode = NULL;
    switch (algDefault)
    {
    case PSA_ALG_CCM:
    case PSA_ALG_CCM_STAR_NO_TAG:
        mode = &mcuxClAead_ModeDescriptor_AES_CCM_DEC;
        break;
    case PSA_ALG_GCM:
        mode = &mcuxClAead_ModeDescriptor_AES_GCM_DEC;
        break;
    default:
        mode = NULL;
        break;
    }
    return (mcuxClAead_Mode_t)mode;
}

static inline uint8_t mcuxClPsaDriver_psa_driver_wrapper_cipher_modeSelectDec(const psa_algorithm_t alg,
                                                   const mcuxClCipher_ModeDescriptor_t **mode)
{
    uint8_t iv_required = 1u;
    switch (alg)
    {
    case PSA_ALG_ECB_NO_PADDING:
        *mode = mcuxClCipher_Mode_AES_ECB_Dec_NoPadding;
        iv_required = 0u;
        break;
    case PSA_ALG_CBC_NO_PADDING:
        *mode = mcuxClCipher_Mode_AES_CBC_Dec_NoPadding;
        break;
    case PSA_ALG_CTR:
        *mode = mcuxClCipher_Mode_AES_CTR;
        break;
    default:
        *mode = NULL;
        iv_required = 0u;
        break;
    }

    return iv_required;
}

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_abort(
   psa_aead_operation_t *operation);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce,
    size_t nonce_length,
    const uint8_t *additional_data,
    size_t additional_data_length,
    const uint8_t *ciphertext,
    size_t ciphertext_length,
    uint8_t *plaintext,
    size_t plaintext_size,
    size_t *plaintext_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_decrypt_setup(
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer,
   size_t key_buffer_size,
   psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, 
	size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce,
    size_t nonce_length,
    const uint8_t *additional_data,
    size_t additional_data_length,
    const uint8_t *plaintext,
    size_t plaintext_length,
    uint8_t *ciphertext,
    size_t ciphertext_size, 
    size_t *ciphertext_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_encrypt_setup(
   psa_aead_operation_t *operation,
   const psa_key_attributes_t *attributes,
   const uint8_t *key_buffer,
   size_t key_buffer_size,
   psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_finish(
   psa_aead_operation_t *operation,
   uint8_t *ciphertext,
   size_t ciphertext_size,
   size_t *ciphertext_length,
   uint8_t *tag,
   size_t tag_size,
   size_t *tag_length);

psa_status_t mcuxClPsaDriver_psa_driver_get_tag_len(
    psa_aead_operation_t *operation,
    uint8_t *tag_len);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_set_lengths(
   psa_aead_operation_t *operation,
   size_t ad_length,
   size_t plaintext_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_set_nonce(
   psa_aead_operation_t *operation,
   const uint8_t *nonce,
   size_t nonce_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_update_ad(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_verify(
   psa_aead_operation_t *operation,
   uint8_t *plaintext,
   size_t plaintext_size,
   size_t *plaintext_length,
   const uint8_t *tag,
   size_t tag_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_aead_update(
   psa_aead_operation_t *operation,
   const uint8_t *input,
   size_t input_length,
   uint8_t *output,
   size_t output_size,
   size_t *output_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *iv,
    size_t iv_length,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_abort(
    psa_cipher_operation_t *operation);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t * attributes,
    const uint8_t * key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_encrypt_setup(
    psa_cipher_operation_t *operation,
    const psa_key_attributes_t * attributes,
    const uint8_t * key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_finish(
    psa_cipher_operation_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_decrypt(
    const psa_key_attributes_t * attributes,
    const uint8_t * key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_set_iv(
    psa_cipher_operation_t *operation,
    const uint8_t *iv,
    size_t iv_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_cipher_update(
    psa_cipher_operation_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_createClKey(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    mcuxClKey_Descriptor_t *out_key_descriptor
);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_updatePointerTag(
    const uint8_t **p,
    uint8_t tag);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_get_integer(
    const uint8_t **p,
    mcuxClRsa_KeyEntry_t  * key);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_der_integer(
    uint8_t **p,
    mcuxClRsa_KeyEntry_t  * key);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_export_public_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    uint8_t *data,
    size_t data_size,
    size_t *data_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_generate_ecp_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_rsa_key(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_key_generate(
    const psa_key_attributes_t *attributes,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length);

const mcuxClEcc_Weier_DomainParams_t* mcuxClPsaDriver_psa_driver_wrapper_getEccDomainParams(
    const psa_key_attributes_t *attributes);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_abort(
    psa_hash_operation_t *operation);
    
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_clone(
    const psa_hash_operation_t *source_operation,
    psa_hash_operation_t *target_operation);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_compute(
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_finish(
    psa_hash_operation_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length);

const mcuxClHash_AlgorithmDescriptor_t * mcuxClPsaDriver_psa_driver_wrapper_hash_set_algorithmDescriptor(
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_setup(
    psa_hash_operation_t *operation,
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_hash_update(
    psa_hash_operation_t *operation,
    const uint8_t *input,
    size_t input_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_computeLayer(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length);

const mcuxClMac_ModeDescriptor_t * mcuxClPsaDriver_psa_driver_wrapper_mac_getMode(
    const psa_key_attributes_t *attributes,
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_finalizeLayer(
    psa_mac_operation_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_setupLayer(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_mac_operation_t *operation,
    psa_algorithm_t alg);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_updateLayer(
    psa_mac_operation_t *operation,
    const uint8_t *input,
    size_t input_length);
		
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_mac_abort(psa_mac_operation_t *operation);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign_message(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign_hash(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *hash,
    size_t hash_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_sign(
    mcuxClKey_Descriptor_t *pKey,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length,
    bool isHash);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(
    mcuxClKey_Descriptor_t *key_descriptor);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(
    mcuxClKey_Descriptor_t *key_descriptor);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(
    mcuxClKey_Descriptor_t *key_descriptor);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_verify(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, 
    size_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *signature,
    size_t signature_length,
    bool isHash);

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_exportKey(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer,
    size_t key_buffer_size,
    uint8_t *data,
    size_t data_size,
    size_t *data_length);

/**
 * @}
 */ /* mcuxClRsa_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPSADRIVER_FUNCTIONS_H_ */

