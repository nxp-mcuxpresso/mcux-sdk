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
 * @file  mcuxClCss_Hash.h
 * @brief CSSv2 header for hashing.
 * 
 * This header exposes functions that enable using the CSSv2 for hashing.
 * There are two modes to hash a message: The asynchronous way as a CSSv2 command, and the SHA-Direct mode which feeds
 * data to the internal registers of the CSSv2 and is synchronous (blocking).
 * The SHA-Direct mode is meant to be used when another command should be executed in parallel on the CSSv2 while the
 * hash operation is still ongoing. For this, use the DMA callback option in #mcuxClCss_Hash_ShaDirect.
 */

/**
 * @defgroup mcuxClCss_Hash mcuxClCss_Hash
 * @brief This part of the @ref mcuxClCss driver supports hashing
 * @ingroup mcuxClCss
 * @{
 */

#ifndef MCUXCLCSS_HASH_H_
#define MCUXCLCSS_HASH_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @defgroup mcuxClCss_Hash_Macros mcuxClCss_Hash_Macros
 * @brief Defines all macros of @ref mcuxClCss_Hash
 * @ingroup mcuxClCss_Hash
 * @{
 */

/**
 * @defgroup MCUXCLCSS_HASH_ MCUXCLCSS_HASH_
 * @brief Defines valid options to be used by #mcuxClCss_HashOption_t
 * @ingroup mcuxClCss_Hash_Macros
 * @{
 */

#define MCUXCLCSS_HASH_INIT_ENABLE  1U ///< Set this option at #mcuxClCss_HashOption_t.hashini to initialize the hash
#define MCUXCLCSS_HASH_INIT_DISABLE 0U ///< Set this option at #mcuxClCss_HashOption_t.hashini to continue the hash

#define MCUXCLCSS_HASH_LOAD_ENABLE  1U ///< Set this option at #mcuxClCss_HashOption_t.hashld to load the hash state from @p pDigest
#define MCUXCLCSS_HASH_LOAD_DISABLE 0U ///< Set this option at #mcuxClCss_HashOption_t.hashld to not load the hash state

#define MCUXCLCSS_HASH_OUTPUT_ENABLE  1U ///< Set this option at #mcuxClCss_HashOption_t.hashoe to output the hash to @p pDigest
#define MCUXCLCSS_HASH_OUTPUT_DISABLE 0U ///< Set this option at #mcuxClCss_HashOption_t.hashoe to not output the hash

#define MCUXCLCSS_HASH_RTF_UPDATE_ENABLE  1U ///< Set this option at #mcuxClCss_HashOption_t.rtfupd to update the run-time fingerprint (only supported by #mcuxClCss_Hash_Async)
#define MCUXCLCSS_HASH_RTF_UPDATE_DISABLE 0U ///< Set this option at #mcuxClCss_HashOption_t.rtfupd to not update the run-time fingerprint

#define MCUXCLCSS_HASH_RTF_OUTPUT_ENABLE  1U ///< Set this option at #mcuxClCss_HashOption_t.rtfoe to output the run-time fingerprint (only supported by #mcuxClCss_Hash_Async)
#define MCUXCLCSS_HASH_RTF_OUTPUT_DISABLE 0U ///< Set this option at #mcuxClCss_HashOption_t.rtfoe to not output the run-time fingerprint

#define MCUXCLCSS_HASH_MODE_SHA_224        1U  ///< Set this option at #mcuxClCss_HashOption_t.hashmd to use the hash algorithm SHA-224
#define MCUXCLCSS_HASH_MODE_SHA_256        0U  ///< Set this option at #mcuxClCss_HashOption_t.hashmd to use the hash algorithm SHA-256
#define MCUXCLCSS_HASH_MODE_SHA_384        2U   ///< Set this option at #mcuxClCss_HashOption_t.hashmd to use the hash algorithm SHA-384
#define MCUXCLCSS_HASH_MODE_SHA_512        3U   ///< Set this option at #mcuxClCss_HashOption_t.hashmd to use the hash algorithm SHA-512

/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_HASH_BLOCK_SIZE_ MCUXCLCSS_HASH_BLOCK_SIZE_
 * @brief Defines block sizes used by the supported hash algorithms
 * @ingroup mcuxClCss_Hash_Macros
 * @{
 */
#define MCUXCLCSS_HASH_BLOCK_SIZE_SHA_224  64U ///< SHA-224 output size: 512 bit (64 bytes)
#define MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256  64U ///< SHA-256 output size: 512 bit (64 bytes)
#define MCUXCLCSS_HASH_BLOCK_SIZE_SHA_384  128U ///< SHA-384 output size: 1024 bit (128 bytes)
#define MCUXCLCSS_HASH_BLOCK_SIZE_SHA_512  128U ///< SHA-512 output size: 1024 bit (128 bytes)
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_HASH_STATE_SIZE_ MCUXCLCSS_HASH_STATE_SIZE_
 * @brief Defines the intermediate state sizes of the supported hash algorithms
 * @ingroup mcuxClCss_Hash_Macros
 * @{
 */
#define MCUXCLCSS_HASH_STATE_SIZE_SHA_224  32U ///< SHA-224 state size: 256 bit (32 bytes)
#define MCUXCLCSS_HASH_STATE_SIZE_SHA_256  32U ///< SHA-256 state size: 256 bit (32 bytes)
#define MCUXCLCSS_HASH_STATE_SIZE_SHA_384  64U  ///< SHA-384 state size: 512 bit (64 bytes)
#define MCUXCLCSS_HASH_STATE_SIZE_SHA_512  64U  ///< SHA-512 state size: 512 bit (64 bytes)
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_HASH_OUTPUT_SIZE_ MCUXCLCSS_HASH_OUTPUT_SIZE_
 * @brief Defines the output sizes of the supported hash algorithms (do not use for allocation)
 * @ingroup mcuxClCss_Hash_Macros
 * @{
 */
#define MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_224 28U ///< SHA-224 output size: 224 bit (28 bytes)
#define MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_256 32U ///< SHA-256 output size: 256 bit (32 bytes)
#define MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_384 48U ///< SHA-384 output size: 384 bit (48 bytes)
#define MCUXCLCSS_HASH_OUTPUT_SIZE_SHA_512 64U ///< SHA-512 output size: 512 bit (64 bytes)
/**
 * @}
 */

/**
 * @ingroup mcuxClCss_Hash_Macros
 * @{
 */
#define MCUXCLCSS_HASH_RTF_OUTPUT_SIZE ((size_t)32U) ///< Size of run-time fingerprint appended to the hash in @p pDigest in bytes, if #MCUXCLCSS_HASH_RTF_OUTPUT_ENABLE was specified
/**
 * @}
 *
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @defgroup mcuxClCss_Hash_Types mcuxClCss_Hash_Types
 * @brief Defines all types of @ref mcuxClCss_Hash
 * @ingroup mcuxClCss_Hash
 * @{
 */

/**
 * @brief Command option bit field for #mcuxClCss_Hash_Async and #mcuxClCss_Hash_ShaDirect.
 * 
 * Bit field to configure #mcuxClCss_Hash_Async and #mcuxClCss_Hash_ShaDirect. See @ref MCUXCLCSS_HASH_ for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_HashOption_t word-wise
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
    } bits;                  ///< Access #mcuxClCss_HashOption_t bit-wise
} mcuxClCss_HashOption_t;

/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * @defgroup mcuxClCss_Hash_Functions mcuxClCss_Hash_Functions
 * @brief Defines all functions of @ref mcuxClCss_Hash
 * @ingroup mcuxClCss_Hash
 * @{
 */

/**
 * @brief Computes the hash of a message.
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * 
 * @param[in]       options     The command options. For more information, see #mcuxClCss_HashOption_t.
 * @param[in]       pInput      Padded input data to be hashed
 * @param[in]       inputLength Size of @p pInput in bytes. Since the input is padded, the length must be a multiple of the block size, see @ref MCUXCLCSS_HASH_BLOCK_SIZE_.
 * @param[in, out]  pDigest     Pointer to the memory area that contains/receives the (intermediate) hash digest, allocated by the caller, see @ref MCUXCLCSS_HASH_STATE_SIZE_.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.hashini == #MCUXCLCSS_HASH_INIT_ENABLE</dt>
 *          <dd>@p options.hashld has no effect and shall be #MCUXCLCSS_HASH_LOAD_DISABLE. No data is read from @p pDigest.</dd>
 *
 *      <dt>@p options.hashld == #MCUXCLCSS_HASH_LOAD_DISABLE</dt>
 *          <dd>@p pDigest is not expected to contain an initial state. No data is read from @p pDigest.</dd>
 *
 *      <dt>@p options.rtfoe == #MCUXCLCSS_HASH_RTF_UPDATE_ENABLE</dt>
 *          <dd>When this option is used the current runtime fingerprint (RTF) value will be appended to the output @p pDigest; an additional #MCUXCLCSS_HASH_RTF_OUTPUT_SIZE bytes has to be allocated for @p pDigest.</dd>
 *
 *      <dt>@p options.hashoe == #MCUXCLCSS_HASH_OUTPUT_ENABLE</dt>
 *          <dd>The hash state is written to @p pDigest. The size varies depending on the choice of @p options.hashmd, for more information see @ref MCUXCLCSS_HASH_STATE_SIZE_ . In cases where the state size and output size differ - see @ref MCUXCLCSS_HASH_OUTPUT_SIZE_ -, the state must be truncated by the caller to obtain the final hash value.</dd>
 *
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Hash_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hash_Async(
    mcuxClCss_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest
    );

/**
 * @brief Enables SHA-direct mode.
 * 
 * If this mode is enabled, it allows the application processor to access the CSS hash
 * engine, but at the same time it stops CSS operations from using the hash engine.
 * 
 * Therefore, in SHA-direct mode, hashing can only be done with #mcuxClCss_Hash_ShaDirect.
 * When SHA-direct mode is active, CSS operations which internally use the CSS hash engine
 * will result in an operational error (see #MCUXCLCSS_STATUS_HW_OPERATIONAL). To use those
 * operations, disable SHA-direct mode. Please consult function descriptions to check
 * whether and under which circumstances they internally use the CSS hash engine.
 * 
 * CSS operations which do not internally use the CSS hash engine can be performed in
 * parallel with a SHA-direct hash operation.
 * 
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK                  on success
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_ShaDirect_Enable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ShaDirect_Enable(
    void);

/**
 * @brief Disables SHA-direct mode.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK                  on success
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_ShaDirect_Disable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ShaDirect_Disable(
    void);

/**
 * @brief Calculates the hash of a message using SHA-Direct mode.
 * 
 * SHA-Direct mode must be enabled before calling this function. For more information, see #mcuxClCss_ShaDirect_Enable.
 * 
 * In order to perform a hash calculation in SHA-Direct mode, the CPU must feed the input data to a register in CSSv2's SHA core, or configure a DMA to copy the input data to that register. A DMA can be used because feeding input data to the SHA core while the SHA core is busy results in an AHB bus stall, and there is no need to check any further flags before copying further data.
 * If a DMA shall be used to perform this copy, a callback function must be provided by the caller that will configure and start the DMA.
 * If no callback function is specified, this function will resort to using the CPU.
 * 
 * @param[in]       options     The command options. For more information, see #mcuxClCss_HashOption_t.
 * @param[in]       pInput      Padded input data to be hashed.
 * @param[in]       inputLength Size of @p pInput in bytes. Since the input is padded, the length must be a multiple of the block size, see @ref MCUXCLCSS_HASH_BLOCK_SIZE_.
 * @param[in, out]  pDigest     Pointer to the memory area that contains/receives the (intermediate) hash digest, allocated by the caller, see @ref MCUXCLCSS_HASH_STATE_SIZE_.
 * @param[in]       pCallback   Callback function to load data into Sha core.
 * @param[in, out]  pCallerData Pointer forwarded by the operation to the callback function.
 * 
 * The properties of some parameters change with respect to selected options.
 * 
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.hashini == #MCUXCLCSS_HASH_INIT_ENABLE</dt>
 *          <dd>@p options.hashld has no effect and shall be #MCUXCLCSS_HASH_LOAD_DISABLE. No data is read from @p pDigest. </dd>
 *
 *      <dt>@p options.hashld == #MCUXCLCSS_HASH_LOAD_DISABLE</dt>
 *          <dd>@p pDigest is not expected to contain an initial state. No data is read from @p pDigest. </dd>
 *
 *      <dt>@p options.hashoe == #MCUXCLCSS_HASH_OUTPUT_ENABLE</dt>
 *          <dd>The hash state is written to @p pDigest. The size varies depending on the choice of @p options.hashmd, for more information see @ref MCUXCLCSS_HASH_STATE_SIZE_ . In cases where the state size and output size differ - see @ref MCUXCLCSS_HASH_OUTPUT_SIZE_ -, the state must be truncated by the caller to obtain the final hash value.</dd>
 *
 *      <dt>@p pCallback != @c NULL </dt>
 *          <dd>The callback function referenced by @p pCallback is called. Otherwise, the function uses a default implementation for the copy.</dd>
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_SW_FAULT            if the callback returned an error
 * @retval #MCUXCLCSS_STATUS_OK                  on success
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Hash_ShaDirect)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hash_ShaDirect(
    mcuxClCss_HashOption_t options,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pDigest,
    mcuxClCss_TransferToRegisterFunction_t pCallback,
    void * pCallerData
    );

#endif /* MCUXCLCSS_HASH_H_ */

/**
 * @}
 *
 * @}
 */
