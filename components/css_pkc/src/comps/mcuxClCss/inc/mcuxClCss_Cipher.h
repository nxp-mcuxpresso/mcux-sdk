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
 * @file  mcuxClCss_Cipher.h
 * @brief CSSv2 header for symmetric ciphers.
 *
 * This header exposes functions that enable using the CSSv2 for symmetric encryption/decryption.
 * The cipher algorithm supported by CSSv2 is AES in the following modes:
 * - Electronic Code Book (ECB) mode, 
 * - Cipher Block Chaining (CBC) mode, and 
 * - Counter (CTR) mode.
 * Supported key sizes are 128, 192, and 256 bits.
 */

/**
 * @defgroup mcuxClCss_Cipher mcuxClCss_Cipher
 * @brief This part of the @ref mcuxClCss driver supports functionality for symmetric ciphers
 * @ingroup mcuxClCss
 * @{
 */

#ifndef MCUXCLCSS_CIPHER_H_
#define MCUXCLCSS_CIPHER_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cipher_Macros mcuxClCss_Cipher_Macros
 * @brief Defines all macros of @ref mcuxClCss_Cipher
 * @ingroup mcuxClCss_Cipher
 * @{
 */

/**
 * @defgroup MCUXCLCSS_CIPHER_ MCUXCLCSS_CIPHER_
 * @brief Defines valid options to be used by #mcuxClCss_CipherOption_t
 * @ingroup mcuxClCss_Cipher_Macros
 *
 * Valid AES key sizes in bytes
 * @{
 */

#define MCUXCLCSS_CIPHER_ENCRYPT 0U                      ///< Set this option at #mcuxClCss_CipherOption_t.dcrpt to perform an encryption
#define MCUXCLCSS_CIPHER_DECRYPT 1U                      ///< Set this option at #mcuxClCss_CipherOption_t.dcrpt to perform a decryption

#define MCUXCLCSS_CIPHER_STATE_OUT_ENABLE  1U            ///< Set this option at #mcuxClCss_CipherOption_t.cphsoe to export the internal CSS state to @p pIV
#define MCUXCLCSS_CIPHER_STATE_OUT_DISABLE 0U            ///< Set this option at #mcuxClCss_CipherOption_t.cphsoe to not export the internal CSS state

#define MCUXCLCSS_CIPHER_STATE_IN_ENABLE  1U             ///< Set this option at #mcuxClCss_CipherOption_t.cphsie to import an external CSS state from @p pIV
#define MCUXCLCSS_CIPHER_STATE_IN_DISABLE 0U             ///< Set this option at #mcuxClCss_CipherOption_t.cphsie to not import an external CSS state

#define MCUXCLCSS_CIPHER_EXTERNAL_KEY 1U                 ///< Set this option at #mcuxClCss_CipherOption_t.extkey to use a key located in CPU memory provided by @p pKey
#define MCUXCLCSS_CIPHER_INTERNAL_KEY 0U                 ///< Set this option at #mcuxClCss_CipherOption_t.extkey to use a key located in CSS keystore privded by @p keyIdx

#define MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_ECB 0x00U    ///< Set this option at #mcuxClCss_CipherOption_t.cphmde to use AES engine in Electornic Code Book (ECB) mode
#define MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_CBC 0x01U    ///< Set this option at #mcuxClCss_CipherOption_t.cphmde to use AES engine in Cipher Block Chaining (CBC) mode
#define MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_CTR 0x02U    ///< Set this option at #mcuxClCss_CipherOption_t.cphmde to use AES engine in Counter (CTR) mode
/**
 * @}
 */


/**
 * @ingroup mcuxClCss_Cipher_Macros
 */
#define MCUXCLCSS_CIPHER_BLOCK_SIZE_AES   ((size_t) 16U) ///< Size of an AES input block: 128 bit (16 bytes)

/**
 * @defgroup MCUXCLCSS_CIPHER_KEY_SIZE_AES_ MCUXCLCSS_CIPHER_KEY_SIZE_AES_
 * @brief Defines valid AES key sizes in bytes
 * @ingroup mcuxClCss_Cipher_Macros
 * @{
 */

#define MCUXCLCSS_CIPHER_KEY_SIZE_AES_128 ((size_t) 16U) ///< Size of an AES128 key: 128 bit (16 bytes)
#define MCUXCLCSS_CIPHER_KEY_SIZE_AES_192 ((size_t) 24U) ///< Size of an AES192 key: 192 bit (24 bytes)
#define MCUXCLCSS_CIPHER_KEY_SIZE_AES_256 ((size_t) 32U) ///< Size of an AES192 key: 256 bit (32 bytes)
/**
 * @}
 *
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cipher_Types mcuxClCss_Cipher_Types
 * @brief Defines all types of @ref mcuxClCss_Cipher
 * @ingroup mcuxClCss_Cipher
 * @{
 */

/**
 * @brief Command option bit field for #mcuxClCss_Cipher_Async
 *
 * Bit field to configure #mcuxClCss_Cipher_Async. See @ref MCUXCLCSS_CIPHER_ for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value;     ///< Accesses the bit field as a full word
    } word;                 ///< Access #mcuxClCss_CipherOption_t word-wise
    struct
    {
        uint32_t :1;        ///< RFU
        uint32_t dcrpt :1;  ///< Define operation mode
        uint32_t cphmde :2; ///< Define cipher mode
        uint32_t cphsoe :1; ///< Define whether the CSSv2 internal cipher state should be extracted to external memory or kept internally
        uint32_t cphsie :1; ///< Define whether an external provided cipher state should be imported from external memory
        uint32_t :7;        ///< RFU
        uint32_t extkey :1; ///< Define whether an external key from memory or CSSv2 internal key should be used
        uint32_t :18;       ///< RFU
    } bits;                 ///< Access #mcuxClCss_CipherOption_t bit-wise
} mcuxClCss_CipherOption_t;
/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cipher_Functions mcuxClCss_Cipher_Functions
 * @brief Defines all functions of @ref mcuxClCss_Cipher
 * @ingroup mcuxClCss_Cipher
 * @{
 */

 /**
 * @brief Performs AES encryption/decryption.
 * 
 *
 * Performs an AES encryption/decryption. Call #mcuxClCss_WaitForOperation to complete the operation.
 * @param[in]       options     Encryption/decryption command options. For detailed information, see #mcuxClCss_CipherOption_t.
 * @param[in]       keyIdx      Index of the key inside the CSSv2 keystore. See parameter properties section in function description.
 * @param[in]       pKey        Memory area that contains the key. See parameter properties section in function description.
 * @param[in]       keyLength   Size of @p pKey in bytes. Must be a valid key size of @ref MCUXCLCSS_CIPHER_KEY_SIZE_AES_. See parameter properties section in function description.
 * @param[in]       pInput      Pointer to the input data to be encrypted/decrypted. Padding must be already applied.
 * @param[in]       inputLength Size of @p pInput in bytes, must be a multiple of the block size.
 * @param[in, out]  pIV         A pointer to the memory location which contains/receives the IV/state of cipher. See parameter properties section in function description.
 * @param[out]      pOutput     Pointer to the output buffer to store encrypted/decrypted data.
 *
 * The properties of some parameters change with respect to selected options.
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.cphmde == #MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_ECB</dt>
 *          <dd>@p pIV is ignored.
 *
 *      <dt>@p options.cphmde == #MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_CBC</dt>
 *          <dd>@p pIV must be set to the IV (when encrypting the first block) or to the last block of the ciphertext of the previous operation.
 *          CSSv2 will always read and write to this location.
 *
 *
 *          @p options.cphsoe is ignored.</dd>
 *
 *      <dt>@p options.cphmde == #MCUXCLCSS_CIPHERPARAM_ALGORITHM_AES_CTR</dt>
 *          <dd>@p pIV must be set to the IV (when encrypting the first block) or to the state output of the previous
 *          encryption/decryption operation. CSSv2 will write to this location if @p options.cphsoe == #MCUXCLCSS_CIPHER_STATE_OUT_ENABLE.</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_CIPHER_EXTERNAL_KEY</dt>
 *          <dd>@p keyIdx is ignored.</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_CIPHER_INTERNAL_KEY</dt>
 *          <dd>@p pKey is ignored.
 *
 *          @p keyLength is ignored.</dd>
 *
 *  </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Cipher_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Cipher_Async(
    mcuxClCss_CipherOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pIV,
    uint8_t * pOutput
    );

/**
 * @}
 */
#endif /* MCUXCLCSS_CIPHER_H_ */

/**
 * @}
 */
