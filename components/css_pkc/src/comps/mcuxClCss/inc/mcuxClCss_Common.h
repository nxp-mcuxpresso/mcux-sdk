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
 * @file  mcuxClCss_Common.h
 * @brief CSSv2 header for common functionality.
 *
 * This header exposes functions that support hardware state management for other CSSv2 commands.
 */

/**
 * @defgroup mcuxClCss_Common mcuxClCss_Common
 * @brief This part of the @ref mcuxClCss driver supports common functionality
 * @ingroup mcuxClCss
 * @{
 */
#ifndef MCUXCLCSS_COMMON_H_
#define MCUXCLCSS_COMMON_H_

#include <mcuxClCss_Types.h> // Common types
#include <mcuxCsslFlowProtection.h>

/**
 * @defgroup mcuxClCss_Common_Macros mcuxClCss_Common_Macros
 * @brief Defines all macros of @ref mcuxClCss_Common
 * @ingroup mcuxClCss_Common
 * @{
 */

#define MCUXCLCSS_API    ///< Marks a function as a public API function of the mcuxClCss component

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @def MCUXCLCSS_HW_VERSION
 * @brief Compatible CSS hardware IP version for the CLNS release that this header is part of.
 * <table>
 *     <caption>Compatible CSS hardware IP version</caption>
 *     <tr><th>Version component<th>Value
 *     <tr><td>Level            <td>0
 *     <tr><td>Major            <td>2
 *     <tr><td>Minor            <td>19
 *     <tr><td>Revision         <td>0
 * </table> */
#define MCUXCLCSS_HW_VERSION ((mcuxClCss_HwVersion_t) { \
        .bits = { \
            .level = (uint32_t) 0, \
            .major = (uint32_t) 2, \
            .minor = (uint32_t) 19, \
            .revision = (uint32_t) 0 \
        } \
    })

/**
 * @defgroup mcuxClCss_InterruptOptionEn_t_Macros mcuxClCss_InterruptOptionEn_t
 * @brief Defines interrupt enable option values
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_CSS_INTERRUPT_ENABLE              ((uint32_t) 1U) ///< Set this option at #mcuxClCss_InterruptOptionEn_t.cssint to allow CSS to trigger an interrupt
#define MCUXCLCSS_CSS_INTERRUPT_DISABLE             ((uint32_t) 0U) ///< Set this option at #mcuxClCss_InterruptOptionEn_t.cssint to prevent CSS from triggering an interrupt
/**@}*/

/**
 * @defgroup mcuxClCss_InterruptOptionRst_t_Macros mcuxClCss_InterruptOptionRst_t
 * @brief Defines interrupt reset option values
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_CSS_RESET_CLEAR             ((uint32_t) 1U) ///< Set this option at #mcuxClCss_InterruptOptionRst_t.cssint to reset the CSS interrupt flag
#define MCUXCLCSS_CSS_RESET_KEEP              ((uint32_t) 0U) ///< Set this option at #mcuxClCss_InterruptOptionRst_t.cssint to keep the CSS interrupt flag
/**@}*/

/**
 * @defgroup mcuxClCss_InterruptOptionSet_t_Macros mcuxClCss_InterruptOptionSet_t
 * @brief Defines interrupt set option values
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_CSS_INTERRUPT_SET          ((uint32_t) 1U) ///< Set this option at #mcuxClCss_InterruptOptionSet_t.cssint to set the CSS interrupt flag
#define MCUXCLCSS_CSS_INTERRUPT_KEEP         ((uint32_t) 0U) ///< Set this option at #mcuxClCss_InterruptOptionSet_t.cssint to leave the CSS interrupt flag unchanged
/**@}*/

/**
 * @defgroup MCUXCLCSS_ERROR_FLAGS_ MCUXCLCSS_ERROR_FLAGS_
 * @brief Options for error flag clearing
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_ERROR_FLAGS_KEEP  ((mcuxClCss_ErrorHandling_t) 0x0u) ///< Set this option at #mcuxClCss_ErrorHandling_t to not clear any error flags
#define MCUXCLCSS_ERROR_FLAGS_CLEAR ((mcuxClCss_ErrorHandling_t) 0x1u) ///< Set this option at #mcuxClCss_ErrorHandling_t to clear all CSS error flags
/**@}*/

/**
 * @defgroup MCUXCLCSS_RESET_ MCUXCLCSS_RESET_
 * @brief Options for reset handling
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_RESET_DO_NOT_CANCEL ((mcuxClCss_ResetOption_t) 0x0u) ///< Set this option at #mcuxClCss_ResetOption_t to abort the requested command if another CSS operation is still running
#define MCUXCLCSS_RESET_CANCEL        ((mcuxClCss_ResetOption_t) 0x1u) ///< Set this option at #mcuxClCss_ResetOption_t to execute the requested command even if another CSS operation is still running
/**@}*/

/**
 * @defgroup MCUXCLCSS_STATUS_PPROT_ MCUXCLCSS_STATUS_PPROT_
 * @brief Values for the privilege/security level of CSS commands
 *
 * Note that some keys and memory areas may only be accessible when CSS is on a certain privilege/security level.
 *
 * The default value, before any command has been executed, is #MCUXCLCSS_STATUS_PPROT_UNPRIVILEGED_NONSECURE.
 *
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_STATUS_PPROT_UNPRIVILEGED_SECURE    ((uint32_t) 0x0u) ///< This value of #mcuxClCss_HwState_t.pprot means that the most recently started CSS operation was or is running in unprivileged secure mode
#define MCUXCLCSS_STATUS_PPROT_PRIVILEGED_SECURE      ((uint32_t) 0x1u) ///< This value of #mcuxClCss_HwState_t.pprot means that the most recently started CSS operation was or is running in privileged secure mode
#define MCUXCLCSS_STATUS_PPROT_UNPRIVILEGED_NONSECURE ((uint32_t) 0x2u) ///< This value of #mcuxClCss_HwState_t.pprot means that the most recently started CSS operation was or is running in unprivileged non-secure mode
#define MCUXCLCSS_STATUS_PPROT_PRIVILEGED_NONSECURE   ((uint32_t) 0x3u) ///< This value of #mcuxClCss_HwState_t.pprot means that the most recently started CSS operation was or is running in privileged non-secure mode
/**@}*/

/**
 * @defgroup MCUXCLCSS_STATUS_ECDSAVFY_ MCUXCLCSS_STATUS_ECDSAVFY_
 * @brief ECDSA verify check values
 * @ingroup mcuxClCss_Common_Macros
 * @{
 */
#define MCUXCLCSS_STATUS_ECDSAVFY_NORUN  ((uint32_t) 0x0u) ///< This value of #mcuxClCss_HwState_t.ecdsavfy means that no ECDSA verify operation has been executed
#define MCUXCLCSS_STATUS_ECDSAVFY_FAIL   ((uint32_t) 0x1u) ///< This value of #mcuxClCss_HwState_t.ecdsavfy means that the most recently finished ECDSA signature verification failed
#define MCUXCLCSS_STATUS_ECDSAVFY_OK     ((uint32_t) 0x2u) ///< This value of #mcuxClCss_HwState_t.ecdsavfy means that the most recently finished ECDSA signature verification passed
#define MCUXCLCSS_STATUS_ECDSAVFY_ERROR  ((uint32_t) 0x3u) ///< This value of #mcuxClCss_HwState_t.ecdsavfy means that an error has occurred
/**@}*/

/**
 * @defgroup MCUXCLCSS_STATUS_DRBGENTLVL_ MCUXCLCSS_STATUS_DRBGENTLVL_
 * @brief Constants for Entropy quality of the current DRBG instance
 * @ingroup mcuxClCss_Common_Macros
 * @{ */
#define MCUXCLCSS_STATUS_DRBGENTLVL_NONE ((uint32_t) 0x0u) ///< This value of #mcuxClCss_HwState_t.drbgentlvl means that the DRBG is not running
#define MCUXCLCSS_STATUS_DRBGENTLVL_LOW  ((uint32_t) 0x1u) ///< This value of #mcuxClCss_HwState_t.drbgentlvl means that the DRBG can generate random numbers with a low security strength (sufficient for commands with a low DRBG security strength requirement, see the function description to check which level is required)
#define MCUXCLCSS_STATUS_DRBGENTLVL_HIGH ((uint32_t) 0x2u) ///< This value of #mcuxClCss_HwState_t.drbgentlvl means that the DRBG can generate random numbers with 128 bits of security strength (sufficient for commands with a high DRBG security strength requirement, see the function description to check which level is required)
/** @} */





/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @defgroup mcuxClCss_Common_Types mcuxClCss_Common_Types
 * @brief Defines all types of @ref mcuxClCss_Common
 * @ingroup mcuxClCss_Common
 * @{
 */

/**
 * @brief Result type of #mcuxClCss_GetHwVersion
 *
 * Contains the CSS version value.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_HwVersion_t word-wise
    struct
    {
        uint32_t revision :4; ///< Revision number
        uint32_t minor :8;    ///< Minor version
        uint32_t major :4;    ///< Major version
        uint32_t level :4;    ///< Release level version
        uint32_t :12;         ///< RFU
    } bits;                   ///< Access #mcuxClCss_HwVersion_t bit-wise
} mcuxClCss_HwVersion_t;

/**
 * @brief Result type of #mcuxClCss_GetHwState
 *
 * Contains CSS status information.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_HwState_t word-wise
    struct
    {
        uint32_t busy :1;       ///< CSS is busy
        uint32_t irq :1;        ///< CSS interrupt activated
        uint32_t err :1;        ///< CSS is in error state
        uint32_t prngready :1;  ///< CSS PRNG is seeded and ready to use
        uint32_t ecdsavfy :2;   ///< ECDSA verify operation state (For possible values of this field, see @ref MCUXCLCSS_STATUS_ECDSAVFY_)
        uint32_t pprot :2;      ///< The privilege/security level of the most recently started CSS command (For possible values of this field, see @ref MCUXCLCSS_STATUS_PPROT_)
        uint32_t drbgentlvl :2; ///< Entropy quality of the current DRBG instance (For possible values of this field, see @ref MCUXCLCSS_STATUS_DRBGENTLVL_)
        uint32_t dtrng_busy: 1; ///< Indicates the DTRNG is gathering entropy
        uint32_t :2;            ///< RFU
        uint32_t :3;            ///< RFU
        uint32_t :1;            ///< RFU
        uint32_t :15;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_HwState_t bit-wise
} mcuxClCss_HwState_t;

/**
 * @brief Type to handle CSS error clearing options
 *
 * For possible values, see @ref MCUXCLCSS_ERROR_FLAGS_.
 */
typedef uint32_t mcuxClCss_ErrorHandling_t;

/**
 * @brief Type to handle CSS reset options
 *
 * For possible values, see @ref MCUXCLCSS_RESET_.
 */
typedef uint32_t mcuxClCss_ResetOption_t;

/**
 * @brief Command option type for #mcuxClCss_SetIntEnableFlags and #mcuxClCss_GetIntEnableFlags
 *
 * Used to get/set CSS interrupt enable options.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_InterruptOptionEn_t word-wise
    struct
    {
        uint32_t cssint :1;  ///< Whether CSS interrupt should be used. (For possible values of this field, see @ref mcuxClCss_InterruptOptionEn_t_Macros)
        uint32_t :1;         ///< RFU
        uint32_t :30;        ///< RFU
    } bits;                  ///< Access #mcuxClCss_InterruptOptionEn_t bit-wise
} mcuxClCss_InterruptOptionEn_t;

/**
 * @brief Type to control which CSS interrupts should be reset when calling #mcuxClCss_ResetIntFlags
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_InterruptOptionRst_t word-wise
    struct
    {
        uint32_t cssint :1;  ///< Whether CSS interrupt should be reset. (For possible values of this field, see @ref mcuxClCss_InterruptOptionRst_t_Macros)
        uint32_t :1;         ///< RFU
        uint32_t :30;        ///< RFU
    } bits;                  ///< Access #mcuxClCss_InterruptOptionRst_t bit-wise
} mcuxClCss_InterruptOptionRst_t;

/**
 * @brief Type to control which CSS interrupts should be set when calling #mcuxClCss_SetIntFlags
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_InterruptOptionSet_t word-wise
    struct
    {
        uint32_t cssint :1;     ///< Whether CSS interrupt should be set. (For possible values of this field, see @ref mcuxClCss_InterruptOptionSet_t_Macros)
        uint32_t :2;            ///< RFU
        uint32_t :29;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_InterruptOptionSet_t bit-wise
} mcuxClCss_InterruptOptionSet_t;

/**
 * @brief Result type of #mcuxClCss_GetHwConfig
 *
 * Contains CSS configuration values.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_InterruptOptionSet_t word-wise
    struct
    {
        uint32_t ciphersup :1;       ///< Indicates whether the cipher command is supported
        uint32_t authciphersup :1;   ///< Indicates whether the auth_cipher command is supported
        uint32_t ecsignsup :1;       ///< Indicates whether the ecsign command is supported
        uint32_t ecvfysup :1;        ///< Indicates whether the ecvfy command is supported
        uint32_t eckxchsup :1;       ///< Indicates whether the dhkey_xch command is supported
        uint32_t keygensup :1;       ///< Indicates whether the keygen command is supported
        uint32_t keyinsup :1;        ///< Indicates whether the keyin command is supported
        uint32_t keyoutsup :1;       ///< Indicates whether the keyout command  is supported
        uint32_t kdeletesup :1;      ///< Indicates whether the kdelete command is supported
        uint32_t keyprovsup :1;      ///< Indicates whether the keyprov command is supported
        uint32_t ckdfsup :1;         ///< Indicates whether the ckdf command is supported
        uint32_t hkdfsup :1;         ///< Indicates whether the hkdf command is supported
        uint32_t tlsinitsup :1;      ///< Indicates whether the tls_init command is supported
        uint32_t hashsup :1;         ///< Indicates whether the hash command is supported
        uint32_t hmacsup :1;         ///< Indicates whether the hmac command is supported
        uint32_t cmacsup :1;         ///< Indicates whether the cmac command is supported
        uint32_t drbgreqsup :1;      ///< Indicates whether the drbg_req command is supported
        uint32_t drbgtestsup :1;     ///< Indicates whether the drbg_test command is supported
        uint32_t dtrgncfgloadsup :1; ///< Indicates whether the dtrng_cfg_load command is is supported
        uint32_t dtrngevalsup :1;    ///< Indicates whether the dtrng_eval command is supported
        uint32_t gdetcfgloadsup :1;  ///< Indicates whether the gdet_cfg_load command is supported
        uint32_t gdettrimsup :1;     ///< Indicates whether the gdet_trim command is supported
        uint32_t :10;                ///< RFU
    } bits;                          ///< Access #mcuxClCss_InterruptOptionSet_t bit-wise
} mcuxClCss_HwConfig_t;

#define drbgreqsub drbgreqsup ///< Deprecated name for #mcuxClCss_HwConfig_t.drbgreqsup



/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Common_Functions mcuxClCss_Common_Functions
 * @brief Defines all functions of @ref mcuxClCss_Common
 * @ingroup mcuxClCss_Common
 * @{
 */
/**
 * @brief Determines the version of the underlying CSS hardware IP.
 *
 * @attention This header was delivered as part of a CLNS release which is compatible with a specific CSS hardware IP version,
 *            which is defined by the macro #MCUXCLCSS_HW_VERSION.
 *
 * @param[out] result Pointer which will be filled with the CSS hardware version
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetHwVersion)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwVersion(
    mcuxClCss_HwVersion_t * result
    );

/**
 * @brief Determines the hardware configuration of the underlying CSS hardware IP.
 *
 * @param[out] result Pointer which will be filled with the CSS hardware configuration
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetHwConfig)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwConfig(
    mcuxClCss_HwConfig_t * result
    );

/**
 * @brief Determines the current state of the CSS.
 *
 * @param[out] result Pointer which will be filled with the CSS status information
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetHwState)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwState(
    mcuxClCss_HwState_t * result
    );

/**
 * @brief Enables the CSS.
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK_WAIT
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Enable_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Enable_Async(
    void
    );

/**
 * @brief Perform a synchronous reset of the CSS.
 *
 * This means that:
 * - any running CSS command will be stopped,
 * - all errors will be cleared,
 * - all keys will be deleted,
 * - any RNG entropy will be discarded,
 * - the glitch detector will be reset and
 * - the run-time fingerprint will be restored to its default value.
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in] options A value indicating whether any running CSS operations shall be canceled
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the reset
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Reset_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Reset_Async(
    mcuxClCss_ResetOption_t options
    );

/**
 * @brief Disable the CSSv2.
 *
 * This is useful as a power saving mechanism.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Disable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Disable(
    void
);

/**
 * @brief Set interrupt enable flags.
 *
 * @param[in] options The command options, determining which interrupts should be enabled or disabled. For more information, see #mcuxClCss_InterruptOptionEn_t.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_SetIntEnableFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetIntEnableFlags(
    mcuxClCss_InterruptOptionEn_t options
    );

/**
 * @brief Get interrupt enable flags.
 *
 * @param[out] result Pointer which is filled with the configuration of the interrupts enable register.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetIntEnableFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetIntEnableFlags(
    mcuxClCss_InterruptOptionEn_t * result
    );

/**
 * @brief Clear the interrupt status register.
 *
 * @param[in] options The command options, determining which interrupt status bits should be cleared. For more information, see #mcuxClCss_InterruptOptionRst_t.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_ResetIntFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ResetIntFlags(
    mcuxClCss_InterruptOptionRst_t options
    );

/**
 * @brief Set the interrupt status register, for debug and testing purposes.
 *
 * @param[in] options The command options, determining which interrupt status bits should be set. For more information, see #mcuxClCss_InterruptOptionSet_t.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_SetIntFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetIntFlags(
    mcuxClCss_InterruptOptionSet_t options
    );

/**
 * @brief Wait for a CSS operation and optionally clear the error status.
 *
 * If a CSS operation is active, this function waits for completion of that operation. For this, the
 * busy flag of CSS is polled. Additionally, this function checks and returns any applicable error indication.
 * If no operation is active, the function returns immediately.
 *
 * @param[in] errorHandling Define if error flags shall be cleared.
 *
 * @retval #MCUXCLCSS_STATUS_OK if the last operation was successful, or no operation was active
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_WaitForOperation)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_WaitForOperation(
    mcuxClCss_ErrorHandling_t errorHandling
    );

/**
 * @brief Await the completion of a CSS operation for a limited amount of time and optionally clear the error status.
 *
 * If a CSS operation is active, this function waits for completion of that operation until a counter expires.
 * For this, the busy flag of CSS is polled. The counting mechanism behaves like a simple for-loop from
 * @p counterLimit to one. This counter does not have a well-defined relationship to real-world time.
 * Additionally, this function checks and returns any applicable error indication.
 * If no operation is active, the function returns immediately.
 *
 * @param[in] counterLimit The limit of the wait counter.
 * @param[in] errorHandling Define if error flags shall be cleared.
 *
 * @retval #MCUXCLCSS_STATUS_OK if the last operation was successful, or no operation was active
 * @retval #MCUXCLCSS_STATUS_SW_COUNTER_EXPIRED if the counter expired while waiting for the operation to complete
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_LimitedWaitForOperation)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_LimitedWaitForOperation(
    uint32_t counterLimit,
    mcuxClCss_ErrorHandling_t errorHandling
    );

/**
 * @brief Resets all error flags that have been set by a previous operation.
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code is always #MCUXCLCSS_STATUS_OK
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_ResetErrorFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ResetErrorFlags(
    void);

/**
 * @brief Get the last CSS error code and optionally clear the error status.
 *
 * @param[in] errorHandling Define if error flags shall be cleared.
 *
 * @retval #MCUXCLCSS_STATUS_OK 	if the last operation was successful or no operation was active
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetErrorCode)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetErrorCode(
    mcuxClCss_ErrorHandling_t errorHandling
    );

/**
 * @brief Get the last CSS error code and level and optionally clear the error status.
 *
 * @param[in]  errorHandling    Define if error flags shall be cleared.
 * @param[out] errorLevel       Pointer to the location that will receive the value of the error level.
 *
 * @retval #MCUXCLCSS_STATUS_OK  if the last operation was successful or no operation was active
 * @retval #MCUXCLCSS_STATUS_    if the last operation resulted in an error
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetErrorLevel)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetErrorLevel(
    mcuxClCss_ErrorHandling_t errorHandling,
    uint32_t *errorLevel
    );

/**
 * @brief Set the random start delay for AES based operations. This impacts mcuxClCss_Aead_*, mcuxClCss_Cipher_*, mcuxClCss_Cmac_*, ncpClCss_Ckdf_*, mcuxClCss_KeyImport_Async, mcuxClCss_KeyExport_Async
 *
 * @param[in] delay Define the max random start delay. Acceptable values are a power of 2 minus one, starting from 0 to 1023 (0, 1, 3, 7, ..., 1023).
 *
 * @retval #MCUXCLCSS_STATUS_OK if the operation was successful
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_SetRandomStartDelay)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetRandomStartDelay(
    uint32_t delay
    );

/**
 * @brief Get the random start delay for AES based operations.
 *
 * @param[out] delay Pointer to store random start delay configuration.
 *
 * @retval #MCUXCLCSS_STATUS_OK if the operation was successful
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetRandomStartDelay)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetRandomStartDelay(
    uint32_t * delay
    );









#endif /* MCUXCLCSS_COMMON_H_ */

/**
 * @}
 *
 * @}
 */


