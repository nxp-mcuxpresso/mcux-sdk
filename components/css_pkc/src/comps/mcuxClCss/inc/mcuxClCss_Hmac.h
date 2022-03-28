/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClCss_Hmac.h
 * @brief CSSv2 header for HMAC support.
 * 
 * This header exposes functions that enable using the CSSv2 for the generation of hashed-key message authentication
 * codes (HMAC).
 * The supported hash algorithm is SHA2-256.
 */

/**
 * @defgroup mcuxClCss_Hmac mcuxClCss_Hmac
 * @brief This part of the @ref mcuxClCss driver supports functionality for hashed-key message authentication codes.
 * @ingroup mcuxClCss
 * @{
 */
#ifndef MCUXCLCSS_HMAC_H_
#define MCUXCLCSS_HMAC_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * MACROS
 **********************************************/
/**
 * @defgroup mcuxClCss_Hmac_Macros mcuxClCss_Hmac_Macros
 * @brief Defines all macros of @ref mcuxClCss_Hmac
 * @ingroup mcuxClCss_Hmac
 * @{
 */
/**
 * @defgroup MCUXCLCSS_HMAC_EXTERNAL_KEY_ MCUXCLCSS_HMAC_EXTERNAL_KEY_
 * @brief Defines valid options to be used by #mcuxClCss_HmacOption_t
 * @ingroup mcuxClCss_Hmac_Macros
 * @{
 */
#define MCUXCLCSS_HMAC_EXTERNAL_KEY_ENABLE  1U ///< Set #mcuxClCss_HmacOption_t.extkey to this value to use an external key
#define MCUXCLCSS_HMAC_EXTERNAL_KEY_DISABLE 0U ///< Set #mcuxClCss_HmacOption_t.extkey to this value to use a key from the CSSv2 keystore
/**
 * @}
 */

#define MCUXCLCSS_HMAC_PADDED_KEY_SIZE ((size_t) 64U) ///< HMAC Key size: 64 bytes
#define MCUXCLCSS_HMAC_OUTPUT_SIZE ((size_t) 32U)     ///< HMAC Output size: 32 bytes
/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Hmac_Types mcuxClCss_Hmac_Types
 * @brief Defines all types of @ref mcuxClCss_Hmac
 * @ingroup mcuxClCss_Hmac
 * @{
 */
/**
 * @brief Command option bit field for #mcuxClCss_Hmac_Async.
 * 
 * Valid option values can be found under @ref MCUXCLCSS_HMAC_EXTERNAL_KEY_.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_CipherOption_t word-wise
    struct
    {
        uint32_t :13;       ///< RFU
        uint32_t extkey :1; ///< Whether an external key should be used
        uint32_t :18;       ///< RFU
    } bits;                 ///< Access #mcuxClCss_CipherOption_t word-wise
} mcuxClCss_HmacOption_t;
/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Hmac_Functions mcuxClCss_Hmac_Functions
 * @brief Defines all functions of @ref mcuxClCss_Hmac
 * @ingroup mcuxClCss_Hmac
 * @{
 */
/**
 * @brief Performs HMAC with SHA-256.
 * 
 * It must be ensured that SHA-Direct mode is disabled when calling this function (see #mcuxClCss_ShaDirect_Disable).
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options     The command options. For more information, see #mcuxClCss_HmacOption_t.
 * @param[in]      keyIdx      The HMAC key index, if an internal key shall be used
 * @param[in]      pPaddedKey  Pointer to a memory location containing the padded HMAC key
 * @param[in]      pInput      Pointer to a memory location which contains the data to be authenticated
 * @param[in]      inputLength Size of @p pInput in bytes
 * @param    [out] pOutput     The output message authentication code
 * 
 * The properties of some parameters change with respect to selected options.
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_HMAC_EXTERNAL_KEY_ENABLE</dt>
 *          <dd>@p keyIdx is ignored.
 * 
 *          @p pPaddedKey must contain the padded HMAC key, which can mean one of two things depending on the length of the original HMAC key, L<sub>kHMAC</sub>:
 *          <ul><li>If L<sub>kHMAC</sub> &le; #MCUXCLCSS_HMAC_PADDED_KEY_SIZE, @p pPaddedKey must be the HMAC key padded with zero-bytes to fill the required length of #MCUXCLCSS_HMAC_PADDED_KEY_SIZE bytes.</li>
 * 
 *          <li>If L<sub>kHMAC</sub> &gt; #MCUXCLCSS_HMAC_PADDED_KEY_SIZE, @p pPaddedKey must contain the SHA-256 hash of the HMAC key, padded with zero-bytes to fill the required length of #MCUXCLCSS_HMAC_PADDED_KEY_SIZE bytes.</li></ul></dd>
 * 
 *      <dt>@p options.extkey == #MCUXCLCSS_HMAC_EXTERNAL_KEY_DISABLE</dt>
 *          <dd>@p keyIdx must be a valid key index with the correct usage rights for HMAC.
 * 
 *          @p pPaddedKey is ignored.</dd>
 *
 *  </dl></dd>
 * </dl>
 * 
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if an invalid parameter was specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Hmac_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Hmac_Async(
    mcuxClCss_HmacOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pPaddedKey,
    uint8_t const * pInput,
    size_t inputLength,
    uint8_t * pOutput
    );

#endif /* MCUXCLCSS_HMAC_H_ */
/**
 * @}
 * 
 * @}
 */
