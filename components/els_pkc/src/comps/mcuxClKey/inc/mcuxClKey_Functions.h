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
#ifdef MCUXCL_FEATURE_KEY_DERIVATION
#include <mcuxClMac_Types.h>
#endif /* MCUXCL_FEATURE_KEY_DERIVATION */

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
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
 * @param[in]      pKeyData         Provide pointer to source data of the key. This can be a pointer to a plain key, a share, or a key blob. The protection function defines the purpose of this parameter
 * @param[in]      keyDataLength    Length of the provided key data @p pKeyData
 *
 * @if (MCUXCL_FEATURE_CSSL_FP_USE_SECURE_COUNTER && MCUXCL_FEATURE_CSSL_SC_USE_SW_LOCAL)
 *  @return A code-flow protected error code (see @ref mcuxCsslFlowProtection). The error code can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @else
 *  @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 * @endif
 *
 * @retval #MCUXCLKEY_STATUS_FAILURE  Key initialization failed
 * @retval #MCUXCLKEY_STATUS_OK       on successful operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_init(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Handle_t key,
    mcuxClKey_Type_t type,
    const uint8_t * pKeyData,
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
    uint8_t * pAuxData,
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


#ifdef MCUXCL_FEATURE_KEY_DERIVATION
/**
 * @brief Execute a key derivation function (KDF) to derive a cryptographic key from several inputs.
 *
 * @param[in]      pSession                   Handle for the current CL session.
 * @param[in]      derivationMode             structure which contains information on which algorithm(s) to be used (Hash, HMac-hash, CMac-mode)
 * @param[in]      derivationKey              key handle to a key derivation key
 * @param[in]      inputs[]                   array of multiple inputs to the key derivation function, such as IV, label, context, salt, seed
 * @param[in]      numberOfInputs             number of different inputs given in inputs
 * @param[out]     derivedKey                 key handle for the derived output key
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
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_derivation)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_derivation(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Derivation_t derivationMode,
    mcuxClKey_Handle_t derivationKey,
    mcuxClKey_DerivationInput_t inputs[],
    uint32_t numberOfInputs,
    mcuxClKey_Handle_t derivedKey
);
#endif /* MCUXCL_FEATURE_KEY_DERIVATION */

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

#ifdef MCUXCL_FEATURE_KEY_GENERATION
/**
 * @brief Key-pair generation function.
 * @api
 *
 * This function can be used to perform a key-pair generation operation.
 * The generated keys are linked with each other using mcuxClKey_linkKeyPair.
 *
 * Note: the key handles @p privKey and @p pubKey must already be initialized
 * and contain a proper key type (matching to the @p generation algorithm),
 * protection mechanism and enough space for key data buffers.
 *
 * @param[in]     pSession     Handle for the current CL session.
 * @param[in]     generation   Key generation algorithm that determines the key
 *                             data stored in @p privKey and @p pubKey.
 * @param[in/out] privKey      Key handle for the private key.
 * @param[in/out] pubKey       Key handle for the public key.
 *
 * @return Status of the mcuxClKey_generate_keypair operation.
 * @retval #MCUXCLKEY_STATUS_OK                 Key generation operation executed successfully.
 * @retval #MCUXCLKEY_STATUS_INVALID_INPUT      The input parameters are not valid.
 * @retval #MCUXCLKEY_STATUS_ERROR              An error occurred during the execution.
 * @retval #MCUXCLKEY_STATUS_FAILURE            The key generation failed.
 *                                             RSA-specific: this occurs in case the key generation exceeds the limit of iterations to generate a prime.
 * @retval #MCUXCLKEY_STATUS_FAULT_ATTACK       An error occurred during the execution.
 *
 * @attention This function uses DRBG and PRNG which have to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_generate_keypair)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_generate_keypair(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Generation_t generation,
    mcuxClKey_Handle_t privKey,
    mcuxClKey_Handle_t pubKey
); /* generate a fresh new key (pair) */
#endif /* MCUXCL_FEATURE_KEY_GENERATION */


#ifdef MCUXCL_FEATURE_KEY_AGREEMENT
/**
 * @brief Key agreement function.
 * @api
 *
 * This function can be used to perform a key agreement operation.
 *
 * @param      pSession    Handle for the current CL session.
 * @param      agreement   Key agreement algorithm that determines the value of
 *                         @p pOut.
 * @param      key         First key to be used for the agreement operation.
 * @param      otherKey    Other key to be used for the agreement operation.
 * @param      additionalInputs additional input needed for the agreement operation.
 * @param      numberOfInputs number of the additional inputs needed for the agreement operation.
 * @param[out] pOut        Pointer to a memory location to store the agreed key.
 * @param[out] pOutLength  Will be incremented by the number of bytes written to @p pOut.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_agreement)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_agreement(
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Handle_t key,
    mcuxClKey_Handle_t otherKey,
    mcuxClKey_Agreement_AdditionalInput_t additionalInputs[],
    uint32_t numberOfInputs,
    uint8_t * pOut,
    uint32_t * const pOutLength
); /* determine a shared key on based on public and private inputs */

#ifdef MCUXCL_FEATURE_KEY_SELFTEST
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClKey_agreement_selftest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_agreement_selftest(
    mcuxClSession_Handle_t session,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Test_t test
);
#endif /* MCUXCL_FEATURE_KEY_SELFTEST */

#endif /* MCUXCL_FEATURE_KEY_AGREEMENT */



/**
 * @}
 */ /* mcuxClKey_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_FUNCTIONS_H_ */
