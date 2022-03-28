/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxClCss_Aead.h
 * @brief CSSv2 header for Authenticated Encryption with Associated Data (AEAD).
 * 
 * This header exposes functions that enable using the CSSv2 for Authenticated Encryption with Associated Data (AEAD).
 * The AEAD algorithm supported by CSSv2 is AES in Galois/Counter Mode (GCM), as described in NIST Special Publication
 * 800-38D.
 */

 /**
 * @defgroup mcuxClCss_Aead mcuxClCss_Aead
 * @brief This part of the @ref mcuxClCss driver supports Authenticated Encryption with Associated Data (AEAD).
 * @ingroup mcuxClCss
 * @{
 */
#ifndef MCUXCLCSS_AEAD_H_
#define MCUXCLCSS_AEAD_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClCss_Aead_Macros mcuxClCss_Aead_Macros
 * @brief Defines all macros of @ref mcuxClCss_Aead
 * @ingroup mcuxClCss_Aead
 * @{
 */
/**
 * @defgroup MCUXCLCSS_AEAD_ MCUXCLCSS_AEAD_
 * @brief Defines macros used to initialize #mcuxClCss_AeadOption_t
 * @ingroup mcuxClCss_Aead_Macros
 * @{
 */
#define MCUXCLCSS_AEAD_ENCRYPT ((uint32_t) 0U) ///< Set #mcuxClCss_AeadOption_t.dcrpt to this value to encrypt data
#define MCUXCLCSS_AEAD_DECRYPT ((uint32_t) 1U) ///< Set #mcuxClCss_AeadOption_t.dcrpt to this value to decrypt data

#define MCUXCLCSS_AEAD_STATE_IN_DISABLE ((uint32_t) 0U) ///< Set #mcuxClCss_AeadOption_t.acpsie to this value to load the GCM state from CSSv2
#define MCUXCLCSS_AEAD_STATE_IN_ENABLE  ((uint32_t) 1U) ///< Set #mcuxClCss_AeadOption_t.acpsie to this value to load the GCM state from the context

#define MCUXCLCSS_AEAD_LASTINIT_TRUE ((uint32_t) 1U)  ///< Set #mcuxClCss_AeadOption_t.lastinit to this value if this is the last call to init
#define MCUXCLCSS_AEAD_LASTINIT_FALSE ((uint32_t) 0U) ///< Set #mcuxClCss_AeadOption_t.lastinit to this value if this is not the last call to init

#define MCUXCLCSS_AEAD_EXTERN_KEY ((uint32_t) 1U) ///< Set #mcuxClCss_AeadOption_t.extkey to this value to use an external key
#define MCUXCLCSS_AEAD_INTERN_KEY ((uint32_t) 0U) ///< Set #mcuxClCss_AeadOption_t.extkey to this value to use a key from the CSS keystore

/**
 * @}
 */

#define MCUXCLCSS_AEAD_IV_BLOCK_SIZE  16U  ///< AES-GCM IV Granularity:  128 bit (16 bytes)
#define MCUXCLCSS_AEAD_AAD_BLOCK_SIZE 16U  ///< AES-GCM AAD Granularity: 128 bit (16 bytes)
#define MCUXCLCSS_AEAD_CONTEXT_SIZE   80U  ///< context size: 512 bit (64 bytes) + 16 bytes for finalize
/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Aead_Macros mcuxClCss_Aead_Macros
 * @brief Defines all macros of @ref mcuxClCss_Aead
 * @ingroup mcuxClCss_Aead
 * @{
 */
/**
 * @brief Command option bit field for #mcuxClCss_Aead_Init_Async, #mcuxClCss_Aead_UpdateAad_Async, #mcuxClCss_Aead_UpdateData_Async and #mcuxClCss_Aead_Finalize_Async.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_AeadOption_t word-wise
    struct
    {
        uint32_t :1;          ///< RFU
        uint32_t dcrpt :1;    ///< Defines if encryption or decryption shall be performed
        uint32_t acpmod :2;   ///< This field is managed internally
        uint32_t acpsoe :1;   ///< This field is managed internally
        uint32_t acpsie :1;   ///< This field is managed internally
        uint32_t msgendw :4;  ///< The size of the last data block (plain/cipher text) in bytes, without padding
        uint32_t lastinit :1; ///< Defines whether this is the last call to init
        uint32_t :2;          ///< RFU
        uint32_t extkey :1;   ///< Defines whether an external key shall be used
        uint32_t :18;         ///< RFU
    } bits;                   ///< Access #mcuxClCss_AeadOption_t bit-wise
} mcuxClCss_AeadOption_t;
/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Aead_Functions mcuxClCss_Aead_Functions
 * @brief Defines all functions of @ref mcuxClCss_Aead
 * @ingroup mcuxClCss_Aead
 * @{
 */

/**
 * @brief AES-GCM initialization
 *
 * This is the first stage of AEAD encryption/decryption. This generates the initial context out of the IV @p pIV and the key (@p pKey or @p keyIdx).
 *
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options   The AEAD command options. For more information, see #mcuxClCss_AeadOption_t.
 * @param[in]      keyIdx    Index of the key inside the CSSv2 keystore
 * @param[in]      pKey      Pointer to the key
 * @param[in]      keyLength Size of @p pKey in bytes
 * @param[in]      pIV       Pointer to memory area that contains the IV
 * @param[in]      ivLength  Size of @p pIV in bytes, with padding
 * @param    [out] pAeadCtx  Pointer to the memory area that receives the AEAD context structure. Must be at least #MCUXCLCSS_AEAD_CONTEXT_SIZE bytes long.
 *
 * The properties of some parameters change with respect to selected options.
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_EXTERN_KEY</dt>
 *          <dd>@p keyIdx is ignored.
 *
 *          @p pKey must be a valid AES key and @p keyLength a valid AES key size (see @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_).</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_INTERN_KEY</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights.
 *
 *          @p pKey and @p keyLength are ignored.</dd>
 *  </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Aead_Init_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Aead_Init_Async(
    mcuxClCss_AeadOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pIV,
    size_t ivLength,
    uint8_t * pAeadCtx
    );

/**
 * @brief AES-GCM partial initialization
 * 
 * This is the first stage of AEAD encryption/decryption. This generates the initial context out of the IV @p pIV and the key (@p pKey or @p keyIdx).
 * 
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options   The AEAD command options. For more information, see #mcuxClCss_AeadOption_t.
 * @param[in]      keyIdx    Index of the key inside the CSSv2 keystore
 * @param[in]      pKey      Pointer to the key
 * @param[in]      keyLength Size of @p pKey in bytes
 * @param[in]      pIV       Pointer to memory area that contains the IV
 * @param[in]      ivLength  Size of @p pIV in bytes, with padding
 * @param    [out] pAeadCtx  Pointer to the memory area that receives the AEAD context structure. Must be at least #MCUXCLCSS_AEAD_CONTEXT_SIZE bytes long.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_EXTERN_KEY</dt>
 *          <dd>@p keyIdx is ignored.
 *
 *          @p pKey must be a valid AES key and @p keyLength a valid AES key size (see @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_).</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_INTERN_KEY</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights.
 *
 *          @p pKey and @p keyLength are ignored.</dd>
 *
 *      <dt>@p options.msgendw</dt>
 *          <dd>This field is ignored</dd>
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Aead_PartialInit_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Aead_PartialInit_Async(
    mcuxClCss_AeadOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pIV,
    size_t ivLength,
    uint8_t * pAeadCtx
    );

/**
 * @brief AES-GCM update of the Additional Authenticated Data (AAD)
 * 
 * This is the second stage of AEAD encryption/decryption. This updates the internal authentication tag with the AAD.
 * 
 * #mcuxClCss_Aead_Init_Async must have been called before calling this function.
 * 
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options   The AEAD command options. For more information, see #mcuxClCss_AeadOption_t.
 * @param[in]      keyIdx    Index of the key inside the CSSv2 keystore
 * @param[in]      pKey      Pointer to the key
 * @param[in]      keyLength Size of @p pKey in bytes
 * @param[in]      pAad      Memory area that contains the AAD
 * @param[in]      aadLength Length of the @p pAad in bytes with padding
 * @param[in, out] pAeadCtx  Pointer to the AEAD context structure. Must be at least #MCUXCLCSS_AEAD_CONTEXT_SIZE bytes long.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_EXTERN_KEY</dt>
 *          <dd>@p keyIdx is ignored.
 *
 *          @p pKey must be a valid AES key and @p keyLength a valid AES key size (see @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_).</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_INTERN_KEY</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights.
 *
 *          @p pKey and @p keyLength are ignored.</dd>
 *
 *      <dt>@p options.msgendw</dt>
 *          <dd>This field is ignored</dd>
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Aead_UpdateAad_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Aead_UpdateAad_Async(
    mcuxClCss_AeadOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pAad,
    size_t aadLength,
    uint8_t * pAeadCtx
    );

/**
 * @brief AES-GCM update of the encrypted data
 * 
 * This is the third stage of AEAD encryption/decryption. This updates the internal authentication tag with the AAD
 * and outputs the ciphertext (in case of encryption) or plaintext (in case of decryption).
 * 
 * #mcuxClCss_Aead_Init_Async, #mcuxClCss_Aead_UpdateAad_Async must have been called before calling this function.
 *
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options     The AEAD command options. For more information, see #mcuxClCss_AeadOption_t.
 * @param[in]      keyIdx      Index of the key inside the CSSv2 keystore
 * @param[in]      pKey        Pointer to the key
 * @param[in]      keyLength   Size of @p pKey in bytes
 * @param[in]      pInput      Pointer to the memory location of the data to be processed
 * @param[in]      inputLength Size of @p pInput in bytes with padding
 * @param    [out] pOutput     Pointer to the processed data memory location
 * @param[in, out] pAeadCtx    Pointer to the AEAD context structure. Must be at least #MCUXCLCSS_AEAD_CONTEXT_SIZE bytes long.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_EXTERN_KEY</dt>
 *          <dd>@p keyIdx is ignored.
 *
 *          @p pKey must be a valid AES key and @p keyLength a valid AES key size (see @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_).</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_INTERN_KEY</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights.
 *
 *          @p pKey and @p keyLength are ignored.</dd>
 *
 *      <dt>@p options.msgendw</dt>
 *          <dd>This field is ignored</dd>
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Aead_UpdateData_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Aead_UpdateData_Async(
    mcuxClCss_AeadOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pOutput,
    uint8_t * pAeadCtx
    );

/**
 * @brief AES-GCM final encryption/decryption
 * 
 * This is the fourth stage of AEAD encryption/decryption. This updates the authentication tag with the final data
 * length block and outputs the tag at the desired location.
 * 
 * #mcuxClCss_Aead_Init_Async, #mcuxClCss_Aead_UpdateAad_Async and #mcuxClCss_Aead_UpdateData_Async must have been called
 * before calling this function.
 *
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options    The AEAD command options. For more information, see #mcuxClCss_AeadOption_t.
 * @param[in]      keyIdx     Index of the key inside the CSSv2 keystore
 * @param[in]      pKey       Pointer to the key
 * @param[in]      keyLength  Size of @p pKey in bytes
 * @param[in]      aadLength  Length of the complete Additional Authenticated Data (AAD) in bytes, without padding.
 * @param[in]      dataLength Length of the complete plaintext/ciphertext in bytes, without padding.
 * @param    [out] pTag       Pointer where the resulting tag will be stored
 * @param[in]      pAeadCtx   Pointer to the AEAD context structure. Must be at least #MCUXCLCSS_AEAD_CONTEXT_SIZE bytes long.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_EXTERN_KEY</dt>
 *          <dd>@p keyIdx is ignored.
 *
 *          @p pKey must be a valid AES key and @p keyLength a valid AES key size (see @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_).</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_AEAD_INTERN_KEY</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights.
 *
 *          @p pKey and @p keyLength are ignored.</dd>
 *
 *      <dt>@p options.msgendw</dt>
 *          <dd>This field has to be set to the size of the last data block (plain/cipher text) in bytes, without padding</dd>
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Aead_Finalize_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Aead_Finalize_Async(
    mcuxClCss_AeadOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    size_t aadLength,
    size_t dataLength,
    uint8_t * pTag,
    uint8_t * pAeadCtx
    );

#endif /* MCUXCLCSS_AEAD_H_ */

/**
 * @}
 * 
 * @}
 */
