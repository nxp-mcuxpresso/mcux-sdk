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
 * @file  mcuxClCss_KeyManagement.h
 * @brief CSSv2 header for key management.
 *
 * This header exposes functions that can be used to manage the keystore of CSSv2.
 * This includes:
 * - Importing keys
 * - Exporting keys
 * - Deleting keys
 */

/**
 * @defgroup mcuxClCss_KeyManagement mcuxClCss_KeyManagement
 * @brief This part of the @ref mcuxClCss driver supports functionality for keys management
 * @ingroup mcuxClCss
 * @{
 */

#ifndef MCUXCLCSS_KEYMANAGEMENT_H_
#define MCUXCLCSS_KEYMANAGEMENT_H_

#include <mcuxClCss_Common.h> // Common functionality

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClCss_KeyManagement_Macros mcuxClCss_KeyManagement_Macros
 * @brief Defines all macros of @ref mcuxClCss_KeyManagement
 * @ingroup mcuxClCss_KeyManagement
 * @{
 */

/**
 * @defgroup MCUXCLCSS_KEYIMPORT_VALUE_KFMT_ MCUXCLCSS_KEYIMPORT_VALUE_KFMT_
 * @brief Defines valid options (word value) to be used by #mcuxClCss_KeyImport_Async
 * @ingroup mcuxClCss_KeyManagement_Macros
 *
 * @{
 */

#define MCUXCLCSS_KEYIMPORT_VALUE_KFMT_UDF      ((uint32_t) 0u<< 6u) ///< Key format UDF with shares in RTL or memory
#define MCUXCLCSS_KEYIMPORT_VALUE_KFMT_RFC3394  ((uint32_t) 1u<< 6u) ///< Key format RFC3394 with shares in memory
#define MCUXCLCSS_KEYIMPORT_VALUE_KFMT_PUF      ((uint32_t) 2u<< 6u) ///< Key from PUF

/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_KEYIMPORT_KFMT_ MCUXCLCSS_KEYIMPORT_KFMT_
 * @brief Defines valid options (bit values) to be used by #mcuxClCss_KeyImport_Async
 * @ingroup mcuxClCss_KeyManagement_Macros
 *
 * @{
 */
#define MCUXCLCSS_KEYIMPORT_KFMT_UDF             ((uint32_t) 0x00u) ///< Key format UDF with shares in RTL or memory
#define MCUXCLCSS_KEYIMPORT_KFMT_RFC3394         ((uint32_t) 0x01u) ///< Key format RFC3394 with shares in memory
#define MCUXCLCSS_KEYIMPORT_KFMT_PUF             ((uint32_t) 0x02u) ///< Key from PUF

#define MCUXCLCSS_RFC3394_OVERHEAD               ((size_t) 16u)     ///< Overhead between RFC3394 blob and key size
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_RFC3394_ MCUXCLCSS_RFC3394_
 * @brief Defines specifying the length of RFC3394 containers
 * @ingroup mcuxClCss_KeyManagement_Macros
 *
 * @{
 */
#define MCUXCLCSS_RFC3394_CONTAINER_SIZE_128     ((size_t) 256u/8u) ///< Size of RFC3394 container for 128 bit key
#define MCUXCLCSS_RFC3394_CONTAINER_SIZE_256     ((size_t) 384u/8u) ///< Size of RFC3394 container for 256 bit key
/**
 * @}
 */

/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_KeyManagement_Types mcuxClCss_KeyManagement_Types
 * @brief Defines all types of @ref mcuxClCss_KeyManagement
 * @ingroup mcuxClCss_KeyManagement
 * @{
 */

/**
 * @brief Command option bit field for #mcuxClCss_KeyImport_Async
 *
 * Bit field to configure #mcuxClCss_KeyImport_Async. 
 * See @ref MCUXCLCSS_KEYIMPORT_KFMT_ for possible options in case the struct is accessed bit-wise.
 * See @ref MCUXCLCSS_KEYIMPORT_VALUE_KFMT_ for possible options in case the struct is accessed word-wise.
 */
typedef union
{
    struct
    {
        uint32_t value;     ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_KEYIMPORT_VALUE_KFMT_
    } word;                 ///< Access #mcuxClCss_KeyImportOption_t word-wise
    struct
    {
        uint32_t :4;        ///< RFU
        uint32_t revf :1;   ///< This field is managed internally
        uint32_t :1;        ///< RFU
        uint32_t kfmt :2;   ///< Defines the key import format, one of @ref MCUXCLCSS_KEYIMPORT_KFMT_
        uint32_t :24;       ///< RFU
    } bits;                 ///< Access #mcuxClCss_KeyImportOption_t bit-wise
} mcuxClCss_KeyImportOption_t;

/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClCss_KeyManagement_Functions mcuxClCss_KeyManagement_Functions
 * @brief Defines all functions of @ref mcuxClCss_KeyManagement
 * @ingroup mcuxClCss_KeyManagement
 * @{
 */

/** 
 * @brief Deletes a key from keystore at the given index.
 * 
 * Before execution, CSS will wait until #mcuxClCss_HwState_t.drbgentlvl == #MCUXCLCSS_STATUS_DRBGENTLVL_LOW. This can lead to a delay if the DRBG is in a state with less security strength at the time of the call.
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]    keyIdx  The index of the key to be deleted
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_KeyDelete_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyDelete_Async(
        mcuxClCss_KeyIndex_t keyIdx
);



/** @brief Imports a key from external storage to an internal key register.
 * 
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]    options          One of @ref MCUXCLCSS_KEYIMPORT_KFMT_
 * @param[in]    pImportKey       Pointer to the RFC3394 container of the key to be imported
 * @param[in]    importKeyLength  Length of the RFC3394 container of the key to be imported
 * @param[in]    wrappingKeyIdx   Index of the key wrapping key, if importing RFC3394 format
 * @param[in]    targetKeyIdx     The desired key index of the imported key
 *
 *  <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p options.kfmt != #MCUXCLCSS_KEYIMPORT_KFMT_RFC3394</dt><dd>
 *       <ul style="list-style: none;">
 *         <li>@p pImportKey is ignored.</li>
 *         <li>@p importKeyLength is ignored.</li>
 *         <li>@p wrappingKeyIdx is ignored.</li>
 *         <li>@p targetKeyIdx is ignored. The unpacked key is automatically stored in key slots 0, 1.</li>
 *       </ul></dd>
 *     </dt>
 *   </dl></dd>
 *  </dl>
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_KeyImport_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyImport_Async(
    mcuxClCss_KeyImportOption_t options,
    uint8_t const * pImportKey,
    size_t importKeyLength,
    mcuxClCss_KeyIndex_t wrappingKeyIdx,
    mcuxClCss_KeyIndex_t targetKeyIdx
    );


/** @brief Exports a key from an internal key register to external storage, using a wrapping key.
 * 
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]    wrappingKeyIdx     The key used for key wrapping
 * @param[in]    exportKeyIdx       The key to export
 * @param[out]   pOutput            The memory address of the exported key
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_INVALID_PARAM    if invalid parameters were specified
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK_WAIT             on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_KeyExport_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_KeyExport_Async(
    mcuxClCss_KeyIndex_t wrappingKeyIdx, ///< [in]  The key used for key wrapping
    mcuxClCss_KeyIndex_t exportKeyIdx,   ///< [in]  The key to export
    uint8_t * pOutput                   ///< [out] The memory address of the exported key
    );

/** @brief Exports the properties of the keys stored in the CSS internal keystore
 *
 * Call #mcuxClCss_WaitForOperation to complete the operation.
 *
 * @param[in]    keyIdx     Request key properties of the index defined here
 * @param[out]   pKeyProp   Key properties of the index provided
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 * @retval #MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT if a running operation prevented the request
 * @retval #MCUXCLCSS_STATUS_OK                  on successful request */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCss_GetKeyProperties)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetKeyProperties(
    mcuxClCss_KeyIndex_t keyIdx,
    mcuxClCss_KeyProp_t * pKeyProp
    );

/**
 * @}
 */
#endif /* MCUXCLCSS_KEYMANAGEMENT_H_ */

/**
 * @}
 */
