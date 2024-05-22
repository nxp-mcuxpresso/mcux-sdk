/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClEls_Hash.h
 * @brief ELS header for hashing.
 * 
 * This header exposes functions that enable using the ELS for hashing.
 * There are two modes to hash a message: The asynchronous way as an ELS command, and the SHA-Direct mode which feeds
 * data to the internal registers of the ELS and is synchronous (blocking).
 * The SHA-Direct mode is meant to be used when another command should be executed in parallel on the ELS while the
 * hash operation is still ongoing. For this, use the DMA callback option in #mcuxClEls_Hash_ShaDirect.
 */

/**
 * @defgroup mcuxClEls_Hash mcuxClEls_Hash
 * @brief This part of the @ref mcuxClEls driver supports hashing
 * @ingroup mcuxClEls
 * @{
 */

#ifndef MCUXCLELS_HASH_H_
#define MCUXCLELS_HASH_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClEls_Common.h> // Common functionality

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @defgroup mcuxClEls_Hash_Macros mcuxClEls_Hash_Macros
 * @brief Defines all macros of @ref mcuxClEls_Hash
 * @ingroup mcuxClEls_Hash
 * @{
 */

/**
 * @defgroup MCUXCLELS_HASH_ MCUXCLELS_HASH_
 * @brief Defines valid options to be used by #mcuxClEls_HashOption_t
 * @ingroup mcuxClEls_Hash_Macros
 * @{
 */

#define MCUXCLELS_HASH_INIT_ENABLE  1U ///< Set this option at #mcuxClEls_HashOption_t.hashini to initialize the hash
#define MCUXCLELS_HASH_INIT_DISABLE 0U ///< Set this option at #mcuxClEls_HashOption_t.hashini to continue the hash

#define MCUXCLELS_HASH_LOAD_ENABLE  1U ///< Set this option at #mcuxClEls_HashOption_t.hashld to load the hash state from @p pDigest
#define MCUXCLELS_HASH_LOAD_DISABLE 0U ///< Set this option at #mcuxClEls_HashOption_t.hashld to not load the hash state

#define MCUXCLELS_HASH_OUTPUT_ENABLE  1U ///< Set this option at #mcuxClEls_HashOption_t.hashoe to output the hash to @p pDigest
#define MCUXCLELS_HASH_OUTPUT_DISABLE 0U ///< Set this option at #mcuxClEls_HashOption_t.hashoe to not output the hash

#define MCUXCLELS_HASH_RTF_UPDATE_ENABLE  1U ///< Set this option at #mcuxClEls_HashOption_t.rtfupd to update the run-time fingerprint (only supported by #mcuxClEls_Hash_Async)
#define MCUXCLELS_HASH_RTF_UPDATE_DISABLE 0U ///< Set this option at #mcuxClEls_HashOption_t.rtfupd to not update the run-time fingerprint

#define MCUXCLELS_HASH_RTF_OUTPUT_ENABLE  1U ///< Set this option at #mcuxClEls_HashOption_t.rtfoe to output the run-time fingerprint (only supported by #mcuxClEls_Hash_Async)
#define MCUXCLELS_HASH_RTF_OUTPUT_DISABLE 0U ///< Set this option at #mcuxClEls_HashOption_t.rtfoe to not output the run-time fingerprint

#define MCUXCLELS_HASH_MODE_SHA_224        1U  ///< Set this option at #mcuxClEls_HashOption_t.hashmd to use the hash algorithm SHA-224
#define MCUXCLELS_HASH_MODE_SHA_256        0U  ///< Set this option at #mcuxClEls_HashOption_t.hashmd to use the hash algorithm SHA-256
#define MCUXCLELS_HASH_MODE_SHA_384        2U   ///< Set this option at #mcuxClEls_HashOption_t.hashmd to use the hash algorithm SHA-384
#define MCUXCLELS_HASH_MODE_SHA_512        3U   ///< Set this option at #mcuxClEls_HashOption_t.hashmd to use the hash algorithm SHA-512


#define MCUXCLELS_HASH_VALUE_MODE_SHA_224  ((uint32_t) MCUXCLELS_HASH_MODE_SHA_224 << 4)  ///< Set this option at #mcuxClEls_HashOption_t.word.value to use the hash algorithm SHA-224
#define MCUXCLELS_HASH_VALUE_MODE_SHA_256  ((uint32_t) MCUXCLELS_HASH_MODE_SHA_256 << 4)  ///< Set this option at #mcuxClEls_HashOption_t.word.value to use the hash algorithm SHA-256
#define MCUXCLELS_HASH_VALUE_MODE_SHA_384  ((uint32_t) MCUXCLELS_HASH_MODE_SHA_384 << 4)  ///< Set this option at #mcuxClEls_HashOption_t.word.value to use the hash algorithm SHA-384
#define MCUXCLELS_HASH_VALUE_MODE_SHA_512  ((uint32_t) MCUXCLELS_HASH_MODE_SHA_512 << 4)  ///< Set this option at #mcuxClEls_HashOption_t.word.value to use the hash algorithm SHA-512


/**
 * @}
 */

/**
 * @defgroup MCUXCLELS_HASH_BLOCK_SIZE_ MCUXCLELS_HASH_BLOCK_SIZE_
 * @brief Defines block sizes used by the supported hash algorithms
 * @ingroup mcuxClEls_Hash_Macros
 * @{
 */
#define MCUXCLELS_HASH_BLOCK_SIZE_SHA_224  64U ///< SHA-224 output size: 512 bit (64 bytes)
#define MCUXCLELS_HASH_BLOCK_SIZE_SHA_256  64U ///< SHA-256 output size: 512 bit (64 bytes)
#define MCUXCLELS_HASH_BLOCK_SIZE_SHA_384  128U ///< SHA-384 output size: 1024 bit (128 bytes)
#define MCUXCLELS_HASH_BLOCK_SIZE_SHA_512  128U ///< SHA-512 output size: 1024 bit (128 bytes)
/**
 * @}
 */

/**
 * @defgroup MCUXCLELS_HASH_STATE_SIZE_ MCUXCLELS_HASH_STATE_SIZE_
 * @brief Defines the intermediate state sizes of the supported hash algorithms
 * @ingroup mcuxClEls_Hash_Macros
 * @{
 */
#define MCUXCLELS_HASH_STATE_SIZE_SHA_224  32U ///< SHA-224 state size: 256 bit (32 bytes)
#define MCUXCLELS_HASH_STATE_SIZE_SHA_256  32U ///< SHA-256 state size: 256 bit (32 bytes)
#define MCUXCLELS_HASH_STATE_SIZE_SHA_384  64U  ///< SHA-384 state size: 512 bit (64 bytes)
#define MCUXCLELS_HASH_STATE_SIZE_SHA_512  64U  ///< SHA-512 state size: 512 bit (64 bytes)
/**
 * @}
 */

/**
 * @defgroup MCUXCLELS_HASH_OUTPUT_SIZE_ MCUXCLELS_HASH_OUTPUT_SIZE_
 * @brief Defines the output sizes of the supported hash algorithms (do not use for allocation)
 * @ingroup mcuxClEls_Hash_Macros
 * @{
 */
#define MCUXCLELS_HASH_OUTPUT_SIZE_SHA_224 28U ///< SHA-224 output size: 224 bit (28 bytes)
#define MCUXCLELS_HASH_OUTPUT_SIZE_SHA_256 32U ///< SHA-256 output size: 256 bit (32 bytes)
#define MCUXCLELS_HASH_OUTPUT_SIZE_SHA_384 48U ///< SHA-384 output size: 384 bit (48 bytes)
#define MCUXCLELS_HASH_OUTPUT_SIZE_SHA_512 64U ///< SHA-512 output size: 512 bit (64 bytes)
/**
 * @}
 */

/**
 * @ingroup mcuxClEls_Hash_Macros
 * @{
 */
#define MCUXCLELS_HASH_RTF_OUTPUT_SIZE ((size_t)32U) ///< Size of run-time fingerprint appended to the hash in @p pDigest in bytes, if #MCUXCLELS_HASH_RTF_OUTPUT_ENABLE was specified
/**
 * @}
 *
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @defgroup mcuxClEls_Hash_Types mcuxClEls_Hash_Types
 * @brief Defines all types of @ref mcuxClEls_Hash
 * @ingroup mcuxClEls_Hash
 * @{
 */

/**
 * @brief Command option bit field for #mcuxClEls_Hash_Async and #mcuxClEls_Hash_ShaDirect.
 * 
 * Bit field to configure #mcuxClEls_Hash_Async and #mcuxClEls_Hash_ShaDirect. See @ref MCUXCLELS_HASH_ for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClEls_HashOption_t word-wise
    struct
    {
        uint32_t :2;         ///< RFU
        uint32_t hashini :1; ///< Defines if the hash engine shall be initialized
        uint32_t hashld :1;  ///< Defines if the hash engine shall be initialized with an externally provided digest
        uint32_t hashmd :2;  ///< Defines which hash algorithm shall be used
        uint32_t hashoe :1;  ///< Defines if the hash digest shall be moved to the output buffer
        uint32_t rtfupd :1;  ///< RTF (Runtime Fingerprint) Update
        uint32_t rtfoe :1;   ///< RTF (Runtime Fingerprint) Output Enabled
        uint32_t :23;        ///< RFU
    } bits;                  ///< Access #mcuxClEls_HashOption_t bit-wise
} mcuxClEls_HashOption_t;

/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * @defgroup mcuxClEls_Hash_Functions mcuxClEls_Hash_Functions
 * @brief Defines all functions of @ref mcuxClEls_Hash
 * @ingroup mcuxClEls_Hash
 * @{
 */

/**
 * @brief Computes the hash of a message.
 * 
 * Call #mcuxClEls_WaitForOperation to complete the operation.
 * @if MCUXCL_FEATURE_ELS_SHA_DIRECT
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClEls_ShaDirect_Disable).
 * @endif
 * 
 * @param[in]       options     The command options. For more information, see #mcuxClEls_HashOption_t.
 * @param[in]       pInput      Padded input data to be hashed
 * @param[in]       inputLength Size of @p pInput in bytes. Since the input is padded, the length must be a multiple of the block size, see @ref MCUXCLELS_HASH_BLOCK_SIZE_.
 * @param[in, out]  pDigest     Pointer to the memory area that contains/receives the (intermediate) hash digest, allocated by the caller, see @ref MCUXCLELS_HASH_STATE_SIZE_.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.hashini == #MCUXCLELS_HASH_INIT_ENABLE</dt>
 *          <dd>@p options.hashld has no effect and shall be #MCUXCLELS_HASH_LOAD_DISABLE. No data is read from @p pDigest.</dd>
 *
 *      <dt>@p options.hashld == #MCUXCLELS_HASH_LOAD_DISABLE</dt>
 *          <dd>@p pDigest is not expected to contain an initial state. No data is read from @p pDigest.</dd>
 *
 *      <dt>@p options.rtfoe == #MCUXCLELS_HASH_RTF_UPDATE_ENABLE</dt>
 *          <dd>When this option is used the current runtime fingerprint (RTF) value will be appended to the output @p pDigest; an additional #MCUXCLELS_HASH_RTF_OUTPUT_SIZE bytes has to be allocated for @p pDigest.</dd>
 *
 *      <dt>@p options.hashoe == #MCUXCLELS_HASH_OUTPUT_ENABLE</dt>
 *          <dd>The hash state is written to @p pDigest. The size varies depending on the choice of @p options.hashmd, for more information see @ref MCUXCLELS_HASH_STATE_SIZE_ . In cases where the state size and output size differ - see @ref MCUXCLELS_HASH_OUTPUT_SIZE_ -, the state must be truncated by the caller to obtain the final hash value.</dd>
 *
 *  </dl></dd>
 * </dl>
 * 
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLELS_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLELS_STATUS_, see individual documentation for more information
 * @endif
 * @retval #MCUXCLELS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLELS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLELS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEls_Hash_Async)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_Hash_Async(
    mcuxClEls_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest
    );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLELS_HASH_H_ */

/**
 * @}
 *
 * @}
 */
