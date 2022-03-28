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
 * @file  mcuxClKey_Functions.h
 * @brief Top-level API of the mcuxClKey component. It is capable to load and flush
 *        keys into memory locations or coprocessors.
 */

#ifndef MCUXCLKEY_FUNCTIONS_H_
#define MCUXCLKEY_FUNCTIONS_H_

#include <mcuxClSession.h>
#include <mcuxClKey_Types.h>
#include <mcuxCsslFlowProtection.h>

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClKey_Functions mcuxClKey_Functions
 * @brief Defines all functions of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**
 * @brief Initializes a key handle.
 *
 * @param[in]      session     Session handle to provide session dependent information
 * @param[in,out]  key         Key handle that will be initialized
 * @param[in]      type        Define which key type shall be initialized
 * @param[in]      protection  Define the protection and flush mechanism that shall be initialized
 * @param[in]      srcKeyData  Provide pointer to source data of the key. This can be a pointer to a plain key buffer, a share, or a key blob. The protection function defines the purpose of this parameter
 * @param[in]      srcAuxData  Provide pointer to aux data of the key. This can be a pointer to a a share, or a wrapping key, or derivation data. The protection function defines the purpose of this parameter
 * @param[in]      srcAuxSlot  Provide aux key slot in case the key is present in a coprocessor keyslot. The protection function defines the purpose of this parameter
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_init)
mcuxClKey_Status_Protected_t mcuxClKey_init(
    mcuxClSession_Handle_t session,
    mcuxClKey_Handle_t key,
    const mcuxClKey_Type_t * type,
    const mcuxClKey_Protection_t * protection,
    const uint8_t * const srcKeyData,
    const uint8_t * const srcAuxData,
    uint32_t srcAuxSlot
);

/**
 * @brief Load key into destination key slot of a coprocessor
 *
 * @param[in]  session  Session handle to provide session dependent information
 * @param[in]  key      Key handle that provides information to load the key
 * @param[out] dstSlot  Provide destination key slot in case the key has to loaded to a key slot. The protection function defines the purpose of this parameter
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_loadCopro)
mcuxClKey_Status_Protected_t mcuxClKey_loadCopro(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  uint32_t dstSlot
);

/**
 * @brief Load key into destination memory buffer
 *
 * @param[in]  session  Session handle to provide session dependent information
 * @param[in]  key      Key handle that provides information to load the key
 * @param[out] dstData  Provide pointer to destination key memory in case the key has to be loaded to memory. The protection function defines the purpose of this parameter
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_loadMemory)
mcuxClKey_Status_Protected_t mcuxClKey_loadMemory(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  uint32_t * dstData
);

/**
 * @brief Flush key from destination which can be a key slot of coprocessor or memory buffer
 *
 * @param[in] session  Session handle to provide session dependent information
 * @param[in] key      Key handle that provides information to flush the key
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_flush)
mcuxClKey_Status_Protected_t mcuxClKey_flush(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key
);

/**
 * @brief Set the requested key properties of the destination key.
 *
 * @param[in,out]  key             key handle that provides information to flush the key
 * @param[in]      key_properties  Set requested key properties of the destination key
 *
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_setKeyproperties)
mcuxClKey_Status_Protected_t mcuxClKey_setKeyproperties(
    mcuxClKey_Handle_t key,
    mcuxClCss_KeyProp_t key_properties
);

/**
 * @}
 */ /* mcuxClKey_Functions */

#endif /* MCUXCLKEY_FUNCTIONS_H_ */
