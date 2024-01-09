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
 * @file  mcuxClKey_Functions.h
 * @brief Top-level API of the mcuxClKey component. It is capable to load and flush
 *        keys into memory locations or coprocessors.
 */

#ifndef MCUXCLKEY_FUNCTIONS_H_
#define MCUXCLKEY_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>
#include <mcuxClSession_Types.h>

#include <mcuxClKey_Types.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Buffer.h>
#include <mcuxClEls.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * @addtogroup mcuxClAPI MCUX CL -- API
 *
 * @defgroup mcuxClKey Key API
 * @brief Key handling operations.
 * @ingroup mcuxClAPI
 */

/**
 * @defgroup mcuxClKey_Functions mcuxClKey_Functions
 * @brief Defines all functions of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**
 * @brief Initializes a key handle.
 *
 * Initializes a key handle with default protection values.
 *
 * @param[in]      pSession         Session handle to provide session dependent information
 * @param[in,out]  key              Key handle that will be initialized
 * @param[in]      type             Define which key type shall be initialized
 * @param[in]      pKeyData         Provide pointer to source data of the key. This can be a pointer to a plain key buffer, a share, or a key blob. The protection function defines the purpose of this parameter
 * @param[in]      keyDataLength    Length of the provided key data @p pKeyData
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_init(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    mcuxClKey_Type_t type,
    mcuxCl_InputBuffer_t pKeyData,
    uint32_t keyDataLength
);

/**
 * @brief Establishes a key pair link between a private and public key handle.
 *
 * @param[in]      pSession    Session handle to provide session dependent information
 * @param[in,out]  privKey     Key handle of private key
 * @param[in,out]  pubKey      Key handle of public key
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_linkKeyPair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_linkKeyPair(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
);

/**
 * @brief Configures they protection mechanism for to the given key handle.
 *
 * @param[in]      pSession    Session handle to provide session dependent information
 * @param[in,out]  key         Key handle that will be configured
 * @param[in]      protection  Define the protection and flush mechanism that shall be used with this @p key
 * @param[in]      pAuxData    Provide pointer to additional data the protection function may use
 * @param[in]      parentKey   Provide parent key information in case it exists. The protection function defines the purpose of this parameter
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_setProtection)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_setProtection(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    mcuxClKey_Protection_t protection,
    mcuxCl_Buffer_t pAuxData,
    mcuxClKey_Handle_t parentKey
);

/**
 * @brief Load key into destination key slot of a coprocessor
 *
 * @param[in]  pSession Session handle to provide session dependent information
 * @param[in]  key      Key handle that provides information to load the key
 * @param[out] dstSlot  Provide destination key slot in case the key has to loaded to a key slot. The protection function defines the purpose of this parameter
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_loadCopro)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_loadCopro(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    uint32_t dstSlot
);

/**
 * @brief Load key into destination memory buffer
 *
 * @param[in]  pSession Session handle to provide session dependent information
 * @param[in]  key      Key handle that provides information to load the key
 * @param[out] dstData  Provide pointer to destination key memory in case the key has to be loaded to memory. The protection function defines the purpose of this parameter
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_loadMemory)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_loadMemory(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    uint32_t * dstData
);

/**
 * @brief Flush key from destination which can be a key slot of coprocessor or memory buffer
 *
 * @param[in] pSession Session handle to provide session dependent information
 * @param[in] key      Key handle that provides information to flush the key
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_flush)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_flush(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key
);



/**
 * @brief Set the requested key properties of the destination key.
 *
 * @param[in,out]  key             key handle that provides information to flush the key
 * @param[in]      key_properties  Pointer to the requested key properties of the destination key. Will be set in key->container.pAuxData
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_ERROR  on unsuccessful operation
 * @retval #MCUXCLKEY_STATUS_OK     on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_setKeyproperties)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_setKeyproperties(
    mcuxClKey_Handle_t key,
    mcuxClEls_KeyProp_t * key_properties
);






/**
 * @}
 */ /* mcuxClKey_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_FUNCTIONS_H_ */
