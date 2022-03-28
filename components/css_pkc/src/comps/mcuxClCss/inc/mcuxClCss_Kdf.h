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

/// @file  mcuxClCss_Kdf.h
/// @brief CSSv2 header for key derivation.
/// This header exposes functions that enable using the CSSv2 for various key derivation commands.
/// The supported key derivation algorithms are:
/// <ul>

/**
 * @file  mcuxClCss_Kdf.h
 * @brief CSSv2 header for key derivation.
 *
 * This header exposes functions that enable using the CSSv2 for various key derivation commands.
 * The supported key derivation algorithms are CKDF, HKDF, TLS
 */


/**
 * @defgroup mcuxClCss_Kdf mcuxClCss_Kdf
 * @brief This part of the @ref mcuxClCss driver supports functionality for key derivation
 * @ingroup mcuxClCss
 * @{
 */

/**
 * @defgroup mcuxClCss_Kdf_Macros mcuxClCss_Kdf_Macros
 * @brief Defines all macros of @ref mcuxClCss_Kdf
 * @ingroup mcuxClCss_Kdf
 * @{
 */







#ifndef MCUXCLCSS_KDF_H_
#define MCUXCLCSS_KDF_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @defgroup mcuxClCss_Kdf_Define mcuxClCss_Kdf_Define
 * @brief  constants
 * @ingroup mcuxClCss_Kdf_Macros
 * @{
 */

#define MCUXCLCSS_HKDF_VALUE_RTF_DERIV             ((uint32_t) 1u<< 0u) ///< Use RTF as derivation input
#define MCUXCLCSS_HKDF_VALUE_MEMORY_DERIV          ((uint32_t) 0u<< 0u) ///< Use derivation input from system memory

#define MCUXCLCSS_CKDF_RTF_DERIV                   1U ///< Use RTF as derivation input
#define MCUXCLCSS_CKDF_SYSTEM_MEMORY_DERIV         0U ///< Use derivation input from system memory

#define MCUXCLCSS_CKDF_DERIVATIONDATA_SIZE         12u ///< Size of CKDF derivation data

#define MCUXCLCSS_CKDF_ALGO_SP800108               0x0u ///< Use SP800-108 algorithm

#define MCUXCLCSS_HKDF_RFC5869_DERIVATIONDATA_SIZE 32u ///< Size of HKDF derivation data
#define MCUXCLCSS_HKDF_SP80056C_TARGETKEY_SIZE     32u ///< Size of HKDF SP800-56C derived key

#define MCUXCLCSS_HKDF_ALGO_RFC5869                0x0u ///< Use RFC5869 algorithm
#define MCUXCLCSS_HKDF_ALGO_SP80056C               0x1u ///< Use SP800-56C algorithm


#define MCUXCLCSS_TLS_DERIVATIONDATA_SIZE          ((size_t) 80u) ///< Size of TLS derivation data
#define MCUXCLCSS_TLS_RANDOM_SIZE                  ((size_t) 32u) ///< Size of random bytes for TLS

#define MCUXCLCSS_TLS_INIT                         0u ///< Perform master key generation
#define MCUXCLCSS_TLS_FINALIZE                     1u ///< Perform session key generation

/**
 * @}
 */ /* MCUXCLCSS_KDF_DEFINE */

/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @defgroup mcuxClCss_Kdf_Types mcuxClCss_Kdf_Types
 * @brief Defines all types of @ref mcuxClCss_Kdf
 * @ingroup mcuxClCss_Kdf
 * @{
 */

/** Internal command option bit field for CKDF functions. */
typedef union
{
    struct
    {
        uint32_t value;         ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_HKDF_VALUE_
    } word;
    struct
    {
        uint32_t :12;
        uint32_t ckdf_algo :2;  ///< Defines which algorithm and mode shall be used. This option is set internally and will be ignored:
                                ///< #MCUXCLCSS_CKDF_ALGO_SP800108  = Use SP800-108 algorithm
        uint32_t :18;
    } bits;
} mcuxClCss_CkdfOption_t;

/** Command option bit field for #mcuxClCss_Hkdf_Rfc5869_Async. */
typedef union
{
    struct
    {
        uint32_t value;         ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_HKDF_VALUE_
    } word;
    struct
    {
        uint32_t rtfdrvdat :1;  ///< #MCUXCLCSS_CKDF_SYSTEM_MEMORY_DERIV=use derivation input from system memory, #MCUXCLCSS_CKDF_RTF_DERIV=use RTF (runtime fingerprint) as derivation input
        uint32_t hkdf_algo :1;  ///< Defines which algorithm shall be used. This option is set internally and will be ignored:
                                ///< #MCUXCLCSS_HKDF_ALGO_RFC5869 = Use RFC5869 algorithm
                                ///< #MCUXCLCSS_HKDF_ALGO_SP80056C = Use SP800-56C algorithm
        uint32_t :30;
    } bits;
} mcuxClCss_HkdfOption_t;

/** Internal command option bit field for #mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async, and #mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async. */
typedef union
{
    struct
    {
        uint32_t value;         ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_HKDF_VALUE_
    } word;
    struct
    {
        uint32_t :10;
        uint32_t mode :1;       ///< Defines which phase of the key generation is performed. This option is set internally and will be ignored:
                                ///< #MCUXCLCSS_TLS_INIT  = Calculate master key from premaster key
                                ///< #MCUXCLCSS_TLS_FINALIZE = Calculate session keys from master key
        uint32_t :21;
    } bits;
} mcuxClCss_TlsOption_t;

/**
 * @}
 */ /* mcuxClCss_Kdf_Types */

/**
 * @}
 */ /* mcuxClCss_Kdf_Macros */


/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Kdf_Functions mcuxClCss_Kdf_Functions
 * @brief Defines all functions of @ref mcuxClCss_Kdf
 * @ingroup mcuxClCss_Kdf
 * @{
 */


/**
 * @brief Derives a key using the HKDF (HMAC-based key derivation function) according to RFC5869.
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 * @param[in] options The command options. For more information, see #mcuxClCss_HkdfOption_t.
 * @param[in] derivationKeyIdx Key index used for derivation. Must be a 256-bit key with HKDF property bit set to 1.
 * @param[in] targetKeyIdx Key bank number of the derived key. Will be a 256-bit key, the user must ensure there is enough space in the keystore to hold the derived key.
 * @param[in] targetKeyProperties Requested properties for the derived key. The ksize field will be ignored.
 * @param[in] pDerivationData The algorithm-specific derivation data, the length is #MCUXCLCSS_HKDF_RFC5869_DERIVATIONDATA_SIZE bytes
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 *
 *
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Hkdf_Rfc5869_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hkdf_Rfc5869_Async(
    mcuxClCss_HkdfOption_t options,
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx,
    mcuxClCss_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData
    );

/** Derives a key using the HKDF (HMAC-based key derivation function) according to SP800-56C one-step approach with Sha2-256.
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in] derivationKeyIdx  Key index used for derivation. Must be a 256-bit key with HKDF property bit set to 1.
 * @param[out] pTagetKey Memory area to store the derived key. Will be a 256-bit key, the user must ensure there is enough space in the keystore to hold the derived key.
 * @param[in] pDerivationData The algorithm-specific derivation data
 * @param[in] derivationDataLength Length of the derivation data
 *
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Hkdf_Sp80056c_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hkdf_Sp80056c_Async(
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    uint8_t * pTagetKey,
    uint8_t const * pDerivationData,
    size_t derivationDataLength
    );


/** Derives a key using the NIST SP 800-108 CMAC-based Extract-and-Expand Key Derivation Function.
 * 
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 *   @param[in] derivationKeyIdx Key index used for derivation
 *   @param[in] targetKeyIdx Key bank number of the derived key
 *   @param[in] targetKeyProperties Requested properties for the derived key. Only set usage bits.
 *   @param[in] pDerivationData The algorithm-specific derivation data, the length is #MCUXCLCSS_CKDF_DERIVATIONDATA_SIZE bytes
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Ckdf_Sp800108_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Ckdf_Sp800108_Async(
    mcuxClCss_KeyIndex_t derivationKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx,
    mcuxClCss_KeyProp_t targetKeyProperties,
    uint8_t const * pDerivationData
    );



/** Generates a TLS master key based on a pre-master key and derivation data, according to the TLS 1.2 specification.
 * The pre-master key is overwritten in this operation.
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in] pDerivationData The TLS derivation data, consisting of Label, Client Random and Server Random from the TLS 1.2 specification.
 *                            Note: The order is different from #mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async.
 * @param[in] keyProperties Desired key properties. Only #mcuxClCss_KeyProp_t::upprot_priv and #mcuxClCss_KeyProp_t::upprot_sec are used, the rest are ignored.
 * @param[in] keyIdx The index of the TLS pre-master key, which is overwritten with the master key
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClCss_KeyProp_t keyProperties,
    mcuxClCss_KeyIndex_t keyIdx
    );

/** Generates TLS session keys based on a master key and derivation data, according to the TLS 1.2 specification.
 * The master key and the following five key indices are overwritten in this operation.
 * The keys are written in the following order:
 * <ol>
 *     <li> Client Encryption Key
 *     <li> Client Message Authentication Key
 *     <li> Server Encryption Key
 *     <li> Server Message Authentication Key
 * </ol>
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in] pDerivationData The TLS derivation data, consisting of Label, Server Random and Client Random from the TLS 1.2 specification.
 *                            Note: The order is different from #mcuxClCss_TlsGenerateMasterKeyFromPreMasterKey_Async.
 * @param[in] keyProperties Desired key properties. Only #mcuxClCss_KeyProp_t::upprot_priv and #mcuxClCss_KeyProp_t::upprot_sec are used, the rest are ignored.
 * @param[in]  keyIdx  The index of the TLS master key, which is overwritten with one of the session keys.
 *                     There must be three further consecutive unoccupied key indices following this index.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_TlsGenerateSessionKeysFromMasterKey_Async(
    uint8_t const * pDerivationData,
    mcuxClCss_KeyProp_t keyProperties,
    mcuxClCss_KeyIndex_t keyIdx
    );

/**
 * @}
 */ /* mcuxClCss_Kdf_Functions */

/**
 * @}
 */ /* mcuxClCss_Kdf */

#endif /* MCUXCLCSS_KDF_H_ */

