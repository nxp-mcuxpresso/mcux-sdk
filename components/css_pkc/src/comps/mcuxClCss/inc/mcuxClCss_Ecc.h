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
 * @file mcuxClCss_Ecc.h
 * @brief CSSv2 header for elliptic curve cryptography
 * This header exposes functions that enable using the CSSv2 for elliptic curve cryptography.
 * All functions operate on the NIST P-256 curve.
 * The ECC operations supported are:
 * - ECC key generation
 * - ECC Diffie-Hellman key exchange
 * - ECDSA signature generation/verification
 */


#ifndef MCUXCLCSS_ECC_H_
#define MCUXCLCSS_ECC_H_

#include <mcuxClCss_Common.h> // Common types & functionality


/**
 * @defgroup mcuxClCss_Ecc mcuxClCss_Ecc
 * @brief This part of the @ref mcuxClCss driver supports functionality for elliptic curve cryptography
 * @ingroup mcuxClCss
 * @{
 */


/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClCss_Ecc_Macros mcuxClCss_Ecc_Macros
 * @brief Defines all macros of @ref mcuxClCss_Ecc
 * @ingroup mcuxClCss_Ecc
 * @{
 */

/**
 * @defgroup MCUXCLCSS_ECC_VALUE_ MCUXCLCSS_ECC (Sign and Verify) option word values
 * @brief Constants for #mcuxClCss_EccSignOption_t and #mcuxClCss_EccVerifyOption_t
 * @ingroup mcuxClCss_Ecc_Macros
 * @{
 */
#define MCUXCLCSS_ECC_VALUE_HASHED              ((uint32_t) 0u<< 0u) ///< Set this option at #mcuxClCss_EccSignOption_t.value or #mcuxClCss_EccVerifyOption_t.value to specify input is the hash of the message
#define MCUXCLCSS_ECC_VALUE_NOT_HASHED          ((uint32_t) 1u<< 0u) ///< Set this option at #mcuxClCss_EccSignOption_t.value or #mcuxClCss_EccVerifyOption_t.value to specify input is the plain message
#define MCUXCLCSS_ECC_VALUE_RTF                 ((uint32_t) 1u<< 1u) ///< Set this option at #mcuxClCss_EccSignOption_t.value to include the RTF in the signature, only for #mcuxClCss_EccSignOption_t
#define MCUXCLCSS_ECC_VALUE_NO_RTF              ((uint32_t) 0u<< 1u) ///< Set this option at #mcuxClCss_EccSignOption_t.value to not include the RTF in the signature, only for #mcuxClCss_EccSignOption_t
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_KEYGEN_VALUE_ MCUXCLCSS_KEYGEN option word values
 * @brief Constants for #mcuxClCss_EccKeyGenOption_t
 * @ingroup mcuxClCss_Ecc_Macros
 * @{
 */
#define MCUXCLCSS_KEYGEN_VALUE_SIGN_PUBLICKEY   ((uint32_t) 1u<< 0u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to sign the public key
#define MCUXCLCSS_KEYGEN_VALUE_TYPE_SIGN        ((uint32_t) 0u<< 1u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to specify output key will be a signing key usable by #mcuxClCss_EccSign_Async
#define MCUXCLCSS_KEYGEN_VALUE_TYPE_KEYEXCHANGE ((uint32_t) 1u<< 1u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to specify output key will be a Diffie Helman key usable by #mcuxClCss_EccKeyExchange_Async
#define MCUXCLCSS_KEYGEN_VALUE_DETERMINISTIC    ((uint32_t) 0u<< 2u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to specify output key is deterministic
#define MCUXCLCSS_KEYGEN_VALUE_RANDOM           ((uint32_t) 1u<< 2u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to specify output key is random
#define NXFCLCSS_KEYGEN_VALUE_GEN_PUB_KEY      ((uint32_t) 0u<< 3u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to generate a public key
#define NXFCLCSS_KEYGEN_VALUE_NO_PUB_KEY       ((uint32_t) 1u<< 3u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to not generate a public key
#define MCUXCLCSS_KEYGEN_VALUE_NO_RANDOM_DATA   ((uint32_t) 0u<< 5u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to not use random data for signing the public key
#define MCUXCLCSS_KEYGEN_VALUE_USE_RANDOM_DATA  ((uint32_t) 1u<< 5u) ///< Set this option at #mcuxClCss_EccKeyGenOption_t.value to use random data for signing the public key
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_ECC_VALUE_BITS MCUXCLCSS_ECC (Sign and Verify) option bit field values
 * @brief Bit field constants for #mcuxClCss_EccSignOption_t and #mcuxClCss_EccVerifyOption_t
 * @ingroup mcuxClCss_Ecc_Macros
 * @{
 */
#define MCUXCLCSS_ECC_HASHED                     0U ///< Set this option at #mcuxClCss_EccSignOption_t.echashchl or #mcuxClCss_EccVerifyOption_t.echashchl to specify input is the hash of the message
#define MCUXCLCSS_ECC_NOT_HASHED                 1U ///< Set this option at #mcuxClCss_EccSignOption_t.echashchl or #mcuxClCss_EccVerifyOption_t.echashchl to specify input is the plain message

#define MCUXCLCSS_ECC_RTF                        1U ///< Set this option at #mcuxClCss_EccSignOption_t.signrtf to include the RTF in the signature
#define MCUXCLCSS_ECC_NO_RTF                     0U ///< Set this option at #mcuxClCss_EccSignOption_t.signrtf to not include the RTF in the signature
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_KEYGEN_VALUE_BITS MCUXCLCSS_KEYGEN option bit field values
 * @brief Bit field constants for #mcuxClCss_EccKeyGenOption_t
 * @ingroup mcuxClCss_Ecc_Macros
 * @{
 */
#define MCUXCLCSS_ECC_PUBLICKEY_SIGN_ENABLE      1U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsign to sign the public key (signature will be concatenated to the output public key)
#define MCUXCLCSS_ECC_PUBLICKEY_SIGN_DISABLE     0U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsign to not sign the public key

#define MCUXCLCSS_ECC_OUTPUTKEY_SIGN             0U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgtypedh to specify output key will be a signing key usable by #mcuxClCss_EccSign_Async
#define MCUXCLCSS_ECC_OUTPUTKEY_KEYEXCHANGE      1U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgtypedh to specify output key will be a Diffie Helman key usable by #mcuxClCss_EccKeyExchange_Async

#define MCUXCLCSS_ECC_OUTPUTKEY_DETERMINISTIC    0U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsrc to specify output key is deterministic
#define MCUXCLCSS_ECC_OUTPUTKEY_RANDOM           1U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsrc to specify output key is random

#define MCUXCLCSS_ECC_GEN_PUBLIC_KEY             0U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.skip_pbk to generate a public key
#define MCUXCLCSS_ECC_SKIP_PUBLIC_KEY            1U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.skip_pbk to not generate a public key.
                                                   ///< If #MCUXCLCSS_ECC_OUTPUTKEY_KEYEXCHANGE set, this option will be ignored and a public key will be generated.

#define MCUXCLCSS_ECC_NO_RANDOM_DATA             0U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsign_rnd to not include user provided random data for the signature
#define MCUXCLCSS_ECC_INCLUDE_RANDOM_DATA        1U ///< Set this option at #mcuxClCss_EccKeyGenOption_t.kgsign_rnd to include user provided random data for the signature.
                                                   ///< #MCUXCLCSS_ECC_PUBLICKEY_SIGN_ENABLE must be set in this case.
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_ECC_SIZE MCUXCLCSS_ECC_SIZE
 * @brief Defines size of public key and signature in bytes
 * @ingroup mcuxClCss_Ecc_Macros
 * @{
 */
#define MCUXCLCSS_ECC_PUBLICKEY_SIZE     ((size_t) 64U) ///< Size of the public key
#define MCUXCLCSS_ECC_SIGNATURE_SIZE     ((size_t) 64U) ///< Size of the signature
#define MCUXCLCSS_ECC_SIGNATURE_R_SIZE   ((size_t) 32U) ///< Size of the signature part r
/**
 * @}
 */

/**
 * @}
 */ /* mcuxClCss_Ecc_Macros */


/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Ecc_Types mcuxClCss_Ecc_Types
 * @brief Defines all types of @ref mcuxClCss_Ecc
 * @ingroup mcuxClCss_Ecc
 * @{
 */

/**
 * @brief Data type for ECC parameters in CSS format
 * @deprecated All CSS ECC functions now operate on uint8_t. This type will be removed soon.
 */
typedef uint8_t mcuxClCss_EccByte_t;

/**
 * @brief Command option bit field for #mcuxClCss_EccSign_Async
 * Bit field to configure #mcuxClCss_EccSign_Async. See @ref MCUXCLCSS_ECC_VALUE_BITS for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value;         ///< Access the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_ECC_VALUE_
    } word;                     ///< Access #mcuxClCss_EccSignOption_t word-wise
    struct
    {
        uint32_t echashchl :1;  ///< Define type of input, plain message or hash of message
        uint32_t signrtf :1;    ///< Define if signing the Run-Time Fingerprint
        uint32_t :2;            ///< RFU
        uint32_t revf :1;       ///< This field is managed internally
        uint32_t :27;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_EccSignOption_t bit-wise
} mcuxClCss_EccSignOption_t;

/**
 * @brief Command option bit field for #mcuxClCss_EccVerify_Async
 * Bit field to configure #mcuxClCss_EccVerifyOption_t. See @ref MCUXCLCSS_ECC_VALUE_BITS for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value;         ///< Access the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_ECC_VALUE_
    } word;                     ///< Access #mcuxClCss_EccVerifyOption_t word-wise
    struct
    {
        uint32_t echashchl :1;  ///< Define type of input, plain message or hash of message
        uint32_t :3;            ///< RFU
        uint32_t revf :1;       ///< This field is managed internally
        uint32_t :27;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_EccVerifyOption_t bit-wise
} mcuxClCss_EccVerifyOption_t;

/**
 * @brief Command option bit field for #mcuxClCss_EccKeyGen_Async
 * Bit field to configure #mcuxClCss_EccKeyGenOption_t. See @ref MCUXCLCSS_KEYGEN_VALUE_BITS for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value;         ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_KEYGEN_VALUE_
    } word;                     ///< Access #mcuxClCss_EccKeyGenOption_t word-wise
    struct
    {
        uint32_t kgsign :1;     ///< Define if signing the output public key
        uint32_t kgtypedh :1;   ///< Define the usage of the output key
        uint32_t kgsrc :1;      ///< Define if the output key is deterministic or random
        uint32_t skip_pbk :1;   ///< Define if generating a public key
        uint32_t revf :1;       ///< This field is managed internally
        uint32_t kgsign_rnd :1; ///< Define if using user provided random data for the signature.
        uint32_t :26;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_EccKeyGenOption_t bit-wise
} mcuxClCss_EccKeyGenOption_t;

/**
 * @}
 */ /* mcuxClCss_Ecc_Types */


/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Ecc_Functions mcuxClCss_Ecc_Functions
 * @brief Defines all functions of @ref mcuxClCss_Ecc
 * @ingroup mcuxClCss_Ecc
 * @{
 */

/**
 * @brief Generates an ECC key pair on the NIST P-256 curve.
 * 
 * Before execution, CSS will wait until #mcuxClCss_HwState_t.drbgentlvl == #MCUXCLCSS_STATUS_DRBGENTLVL_HIGH. This can lead to a delay if the DRBG is in a state with less security strength at the time of the call.
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 * The public key will be stored in the standard ANSI X9.62 byte order (big-endian).
 *
 * @param[in]  options                The command options. For more information, see #mcuxClCss_EccKeyGenOption_t.
 * @param[in]  signingKeyIdx          The index of the key to sign the generated public key.
 * @param[in]  privateKeyIdx          Output key index.
 * @param[in]  generatedKeyProperties The desired key properties of the generated key.
 * @param[in]  pRandomData            Random data provided by the user.
 * @param[out] pPublicKey             Pointer to the memory area which receives the public key and optionally the key signature.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p options.kgsign == #MCUXCLCSS_ECC_PUBLICKEY_SIGN_DISABLE</dt>
 *       <dd>@p signingKeyIdx is ignored.</dd>
 *     <dt>@p options.kgsrc == #MCUXCLCSS_ECC_OUTPUTKEY_DETERMINISTIC</dt>
 *       <dd>@p privateKeyIdx also defines the key index of the source key material.
 *           The source key material will be overwritten by the output public key.</dd>
 *     <dt>@p options.kgsign_rnd == #MCUXCLCSS_ECC_NO_RANDOM_DATA</dt>
 *       <dd>@p pRandomData is ignored.</dd>
 *     <dt>@p pPublicKey must be aligned on a 4-byte boundary.</dt>
 *   </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_EccKeyGen_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccKeyGen_Async(
    mcuxClCss_EccKeyGenOption_t options,
    mcuxClCss_KeyIndex_t signingKeyIdx,
    mcuxClCss_KeyIndex_t privateKeyIdx,
    mcuxClCss_KeyProp_t generatedKeyProperties,
    uint8_t const * pRandomData,
    uint8_t * pPublicKey
    );

/**
 * @brief Performs a Diffie-Hellman key exchange with an internal ECC private key and an external ECC public key.
 * 
 * Before execution, CSS will wait until #mcuxClCss_HwState_t.drbgentlvl == #MCUXCLCSS_STATUS_DRBGENTLVL_LOW. This can lead to a delay if the DRBG is in a state with less security strength at the time of the call.
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 * The public key must be stored in the standard ANSI X9.62 byte order (big-endian).
 *
 * @param[in] privateKeyIdx          The private key index.
 * @param[in] pPublicKey             Pointer to the public key of a third party.
 * @param[in] sharedSecretIdx        The index in the CSSv2 keystore that receives the shared secret that is generated by the ECDH operation.
 * @param[in] sharedSecretProperties The desired key properties of the shared secret.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p pPublicKey </dt>
 *       <dd>The public key consists of the 256-bit X coordinate and the 256-bit Y coordinate.
 *           The point must lie on the NIST P-256 curve, be encoded in X9.62 format and aligned on a 4-byte boundary.</dd>
 *   </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_EccKeyExchange_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccKeyExchange_Async(
    mcuxClCss_KeyIndex_t privateKeyIdx,
    uint8_t const * pPublicKey,
    mcuxClCss_KeyIndex_t sharedSecretIdx,
    mcuxClCss_KeyProp_t sharedSecretProperties
    );


/**
 * @brief Generates an ECDSA signature of a given message.
 *
 * The curve is NIST P-256.
 * The message hash, must be stored in the standard ANSI X9.62 format.
 * If the message is provided in plain, no prior conversion is necessary.
 * The signature will be stored in the standard ANSI X9.62 byte order (big-endian).
 * No matter the value of @p options.echashchl, it must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * 
 * Before execution, CSS will wait until #mcuxClCss_HwState_t.drbgentlvl == #MCUXCLCSS_STATUS_DRBGENTLVL_HIGH. This can lead to a delay if the DRBG is in a state with less security strength at the time of the call.
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]  options            The command options. For more information, see #mcuxClCss_EccSignOption_t.
 * @param[in]  keyIdx             The private key index.
 * @param[in]  pInputHash         The hash of the message to sign in X9.62 format.
 * @param[in]  pInputMessage      The message to sign.
 * @param[in]  inputMessageLength Size of @p pInputMessage in bytes.
 * @param[out] pOutput            Pointer to the memory area which receives the generated signature in X9.62 format. (64 bytes)
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p options.echashchl == #MCUXCLCSS_ECC_HASHED</dt>
 *       <dd>@p pInputHash is used, and it must be aligned on a 4-byte boundary.
 *           @p pInputMessage is ignored.</dd>
 *     <dt>@p options.echashchl == #MCUXCLCSS_ECC_NOT_HASHED</dt>
 *       <dd>@p pInputHash is ignored.
 *           @p pInputMessage and @p inputMessageLength are used.</dd>
 *     <dt>@p pOptput must be aligned on a 4-byte boundary.</dt>
 *   </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_EccSign_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccSign_Async(
    mcuxClCss_EccSignOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pInputHash,
    uint8_t const * pInputMessage,
    size_t inputMessageLength,
    uint8_t * pOutput
    );

/**
 * @brief Verifies an ECDSA signature of a given message.
 *
 * The curve is NIST P-256.
 * The message hash, must be stored in the standard ANSI X9.62 format.
 * If the message is provided in plain, no prior conversion is necessary.
 * The signature and public key must be stored in the standard ANSI X9.62 byte order (big-endian).
 * No matter the value of @p options.echashchl, it must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * 
 * Before execution, CSS will wait until #mcuxClCss_HwState_t.drbgentlvl == #MCUXCLCSS_STATUS_DRBGENTLVL_LOW. This can lead to a delay if the DRBG is in a state with less security strength at the time of the call.
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]  options             The command options. For more information, see #mcuxClCss_EccVerifyOption_t.
 * @param[in]  pInputHash          The hash of the signed message in X9.62 format.
 * @param[in]  pInputMessage       The message to sign.
 * @param[in]  inputMessageLength  Size of @p pInputMessage in bytes.
 * @param[in]  pSignatureAndPubKey Pointer to the memory area which contains the concatenation of the signature and the public key.
 * @param[out] pOutput             Pointer to the memory area which will receive the recalculated value of the R component in case of a successful
 *                                 signature verification.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p options.echashchl == #MCUXCLCSS_ECC_HASHED</dt>
 *       <dd>@p pInputHash is used, and it must be aligned on a 4-byte boundary.
 *           @p pInputMessage is ignored.</dd>
 *     <dt>@p options.echashchl == #MCUXCLCSS_ECC_NOT_HASHED</dt>
 *       <dd>@p pInputHash is ignored.
 *           @p pInputMessage and @p inputMessageLength are used.</dd>
 *     <dt>@p pSignatureAndPubKey </dt>
 *       <dd>It must be aligned on a 4-byte boundary.
 *           The signature to be verified consists of the 256-bit R component and the 256-bit S component.
 *           The public key is the one for verification. (Uncompressed, X and Y components)
 *           The signature and the public key are in X9.62 format.</dd>
 *     <dt>@p pOutput </dt>
 *       <dd>It must be aligned on a 4-byte boundary.
 *           The output shall be compared to the first 32 bytes stored at @p pSignatureAndPublicKey.</dd>
 *   </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_EccVerify_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccVerify_Async(
    mcuxClCss_EccVerifyOption_t options,
    uint8_t const * pInputHash,
    uint8_t const * pInputMessage,
    size_t inputMessageLength,
    uint8_t const * pSignatureAndPubKey,
    uint8_t * pOutput
    );


/**
 * @}
 */ /* mcuxClCss_Ecc_Functions */


/**
 * @}
 */ /* mcuxClCss_Ecc */

#endif /* MCUXCLCSS_ECC_H_ */
