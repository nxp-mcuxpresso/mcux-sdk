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
 * @file  mcuxClCss_Cmac.h
 * @brief CSSv2 header for CMAC support.
 * This header exposes functions that enable using the CSSv2 for the generation of cipher-based message authentication
 * codes (CMAC).
 * The supported cipher algorithm is AES-128 and AES-256.
 */

/**
 * @defgroup mcuxClCss_Cmac mcuxClCss_Cmac
 * @brief This part of the @ref mcuxClCss driver supports functionality for cipher-based message authentication codes (CMAC).
 * @ingroup mcuxClCss
 * @{
 */

#ifndef MCUXCLCSS_CMAC_H_
#define MCUXCLCSS_CMAC_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * MACROS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cmac_Macros mcuxClCss_Cmac_Macros
 * @brief Defines all macros of @ref mcuxClCss_Cmac
 * @ingroup mcuxClCss_Cmac
 * @{
 */

/**
 * @defgroup MCUXCLCSS_CMAC_KEY_SIZE_ MCUXCLCSS_CMAC_KEY_SIZE_
 * @brief Valid CMAC key sizes in bytes
 * @ingroup mcuxClCss_Cmac_Macros
 * @{ */
#define MCUXCLCSS_CMAC_KEY_SIZE_128 ((size_t) 16U) ///< Size of 128 bit CMAC key (16 bytes)
#define MCUXCLCSS_CMAC_KEY_SIZE_256 ((size_t) 32U) ///< Size of 256 bit CMAC key (32 bytes)
/** @} */

/**
 * @defgroup MCUXCLCSS_CMAC_ MCUXCLCSS_CMAC_
 * @brief Option values for #mcuxClCss_CmacOption_t
 * @ingroup mcuxClCss_Cmac_Macros
 * @{ */
#define MCUXCLCSS_CMAC_EXTERNAL_KEY_ENABLE  1U ///< Set #mcuxClCss_CmacOption_t.extkey to this value to use an external key
#define MCUXCLCSS_CMAC_EXTERNAL_KEY_DISABLE 0U ///< Set #mcuxClCss_CmacOption_t.extkey to this value to use a key from the CSSv2 keystore
#define MCUXCLCSS_CMAC_INITIALIZE_DISABLE   0U ///< Set #mcuxClCss_CmacOption_t.initialize to this value if the message chunk does not include the first block of the message
#define MCUXCLCSS_CMAC_INITIALIZE_ENABLE    1U ///< Set #mcuxClCss_CmacOption_t.initialize to this value if the message chunk includes the first block of the message
#define MCUXCLCSS_CMAC_FINALIZE_DISABLE     0U ///< Set #mcuxClCss_CmacOption_t.finalize to this value if the message chunk does not include the last block of the message
#define MCUXCLCSS_CMAC_FINALIZE_ENABLE      1U ///< Set #mcuxClCss_CmacOption_t.finalize to this value if the message chunk includes the last block of the message
#define MCUXCLCSS_CMAC_STATE_IN_DISABLE     0U ///< Set #mcuxClCss_CmacOption_t.sie to this value to use the CMAC state that is present inside CSS
#define MCUXCLCSS_CMAC_STATE_IN_ENABLE      1U ///< Set #mcuxClCss_CmacOption_t.sie to this value to import the CMAC state from memory
#define MCUXCLCSS_CMAC_STATE_OUT_DISABLE    0U ///< Set #mcuxClCss_CmacOption_t.soe to this value to keep the CMAC state inside CSS at the end of the command
#define MCUXCLCSS_CMAC_STATE_OUT_ENABLE     1U ///< Set #mcuxClCss_CmacOption_t.soe to this value to export the CMAC state to memory at the end of the command
/**
 * @}
 */

#define MCUXCLCSS_CMAC_OUT_SIZE ((size_t) 16U) ///< Size of CMAC output: 128 bit (16 bytes)

/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cmac_Types mcuxClCss_Cmac_Types
 * @brief Defines all types of @ref mcuxClCss_Cmac
 * @ingroup mcuxClCss_Cmac
 * @{
 */
/**
 * @brief Command option bit field for #mcuxClCss_Cmac_Async.
 */
typedef union
{
    struct
    {
        uint32_t value; ///< Accesses the bit field as a full word
    } word;             ///< Access #mcuxClCss_CmacOption_t word-wise
    struct
    {
        uint32_t initialize : 1; ///< Request initial processing for the first block of the message
        uint32_t finalize : 1;   ///< Request final processing for the last block of the message
        uint32_t soe : 1;        ///< This field is managed internally
        uint32_t sie : 1;        ///< This field is managed internally
        uint32_t :9;             ///< RFU
        uint32_t extkey :1;      ///< An external key should be used
        uint32_t :18;            ///< RFU
    } bits;                      ///< Access #mcuxClCss_CmacOption_t bit-wise
} mcuxClCss_CmacOption_t;
/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_Cmac_Functions mcuxClCss_Cmac_Functions
 * @brief Defines all functions of @ref mcuxClCss_Cmac
 * @ingroup mcuxClCss_Cmac
 * @{
 */
/**
 * @brief Performs CMAC with AES-128 or AES-256
 * 
 * 
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]      options     The command options. For more information, see #mcuxClCss_CmacOption_t.
 * @param[in]      keyIdx      The CMAC key index
 * @param[in]      pKey        Pointer to the padded CMAC key
 * @param[in]      keyLength   Size of @p pKey in bytes. Must be a @ref MCUXCLCSS_CMAC_KEY_SIZE_ "valid CMAC key size". See the parameter properties section in the function description.
 * @param[in]      pInput      Pointer to a memory location which contains the data, padded via SP 800-38b standard, to be authenticated
 * @param[in]      inputLength Size of @p pInput in bytes before padding
 * @param[in, out] pMac        Pointer to the CMAC command state input/output. See the parameter properties section in the function description.
 * 
 * The properties of some parameters change with respect to selected options.
 *
 * <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>@p options.extkey == #MCUXCLCSS_CMAC_EXTERNAL_KEY_ENABLE</dt>
 *          <dd>@p keyIdx is ignored.</dd>
 *
 *      <dt>@p options.extkey == #MCUXCLCSS_CMAC_EXTERNAL_KEY_DISABLE</dt>
 *          <dd>@p pKey is ignored.
 *
 *          @p keyLength is ignored.</dd>
 * 
 *      <dt>(@p options.finalize == #MCUXCLCSS_CMAC_FINALIZE_DISABLE) && (@p options.soe == #MCUXCLCSS_CMAC_STATE_OUT_ENABLE)</dt>
 *          <dd>The intermediate state is written to @p pMac. </dd>
 * 
 *      <dt>@p options.finalize == #MCUXCLCSS_CMAC_FINALIZE_ENABLE</dt>
 *          <dd>The resulting MAC is written to @p pMac.
 * 
 *          @p options.soe is ignored.</dd>
 *  </dl></dd>
 * </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if an invalid parameter was specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_Cmac_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Cmac_Async(
    mcuxClCss_CmacOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pKey,
    size_t keyLength,
    uint8_t const * pInput,
    size_t inputLength, 
    uint8_t * pMac
    );

#endif /* MCUXCLCSS_CMAC_H_ */

/**
 * @}
 * 
 * @}
 */
