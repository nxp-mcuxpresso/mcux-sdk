/*--------------------------------------------------------------------------*/
/* Copyright 2020-2024 NXP                                                  */
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
 * @file  mcuxClKey_Types_Internal.h
 * @brief Type definitions for the mcuxClKey component
 */

#ifndef MCUXCLKEY_TYPES_INTERNAL_H_
#define MCUXCLKEY_TYPES_INTERNAL_H_

#include <stdint.h>
#include <stdbool.h>

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClKey_Types.h>

#ifdef MCUXCL_FEATURE_KEY_DERIVATION
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMacModes_Common_Wa.h>
#include <internal/mcuxClMac_Internal_Constants.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <mcuxClHash_Types.h>
#endif /* MCUXCL_FEATURE_KEY_DERIVATION */

#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * FUNCTION TYPE DEFINITIONS
 **********************************************/

/**
 * @brief Functions to load a key into coprocessor or memory buffer.
 *
 * @param[in]  key  Key handle that provides information to load the key
 *
 * @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_LoadFuncPtr_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_LoadFuncPtr_t)(mcuxClKey_Handle_t key));

/**
 * @brief Functions to store a key.
 *
 * @param[in]  key  Key handle that provides information to store the key
 *
 * @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_StoreFuncPtr_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_StoreFuncPtr_t)(mcuxClKey_Handle_t key));

/**
 * @brief Functions to flush a key from coprocessor or memory buffer.
 *
 * @param[in]  key  Key handle that provides information to flush the key
 *
 * @return An error code that can be any error code in @ref MCUXCLKEY_STATUS_, see individual documentation for more information
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_FlushFuncPtr_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_FlushFuncPtr_t)(mcuxClKey_Handle_t key));


#ifdef MCUXCL_FEATURE_KEY_DERIVATION
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_DerivationEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_DerivationEngine_t)(
  mcuxClSession_Handle_t pSession,
  mcuxClKey_Derivation_t derivationMode,
  mcuxClKey_Handle_t derivationKey,
  mcuxClKey_DerivationInput_t inputs[],
  uint32_t numberOfInputs,
  mcuxClKey_Handle_t derivedKey));
#endif /* MCUXCL_FEATURE_KEY_DERIVATION */


/**********************************************
 * DATA TYPE DEFINITIONS
 **********************************************/

/**
 * @brief Type for key load location options.
 */
typedef uint16_t mcuxClKey_LoadStatus_t;


/**********************************************
 * STRUCTURES
 **********************************************/

/**
 * @brief Struct to map algorithm id and size.
 */
struct mcuxClKey_TypeDescriptor {
  mcuxClKey_AlgorithmId_t    algoId; ///< the identifier of the algorithm, refer to #mcuxClKey_KeyTypes
  /* uint16_t                  PADDING_FOR_32BIT_ALIGNMENT; */
  mcuxClKey_Size_t           size;   ///< the key size for the key type in bytes, refer to #mcuxClKey_KeySize
  void *                    info;   ///< pointer to additional information for this key type (e.g. curve parameters, public exponent)
};

/**
 * @brief Struct for key internal storage information (destination key)
 * Key data can be provided in @param pData or loaded to a @param slot
 * @param status is one of MCUXCLKEY_LOADSTATUS_
 */
typedef struct mcuxClKey_Location {
  uint8_t *             pData;    ///< Pointer to the data buffer
  uint32_t              length;   ///< Length of the data buffer
  uint32_t              slot;     ///< Key slot to which the key is loaded
  mcuxClKey_LoadStatus_t status;   ///< Load status of the key
  uint16_t              PADDING_FOR_32BIT_ALIGNMENT;
} mcuxClKey_Location_t;

/**
 * @brief Struct for key external storage information (source for mcuxClKey_Location_t)
 */
typedef struct mcuxClKey_Container {
  uint8_t *               pData;      ///< Pointer to the data buffer
  uint32_t                length;     ///< Length of the data buffer
  uint32_t                used;       ///< Length of the used part of the data buffer
  mcuxClKey_Descriptor_t * parentKey;  ///< Handle of the parent of the key
  uint8_t *               pAuxData;   ///< Pointer to auxiliary data needed by the key protection mechanism
} mcuxClKey_Container_t;

/**
 * @brief Type for mapping load, store and flush functions.
 */
struct mcuxClKey_ProtectionDescriptor {
  mcuxClKey_LoadFuncPtr_t    loadFunc;   ///< Function pointer to a load function
  mcuxClKey_StoreFuncPtr_t   storeFunc;  ///< Function pointer to an store function
  uint32_t protectionTokenLoad;         ///< Protection token of the load function
  uint32_t protectionTokenStore;        ///< Protection token of the store function
};

/**
 * @brief Struct of the key handle.
 */
struct mcuxClKey_Descriptor {
  mcuxClKey_Container_t                    container;   ///< Container for external (protected) storage of the key, it cannot be used directly by an operation
  /* TODO CLNS-5378: use pointer to the keyType instead of full struct? To be discussed */
  mcuxClKey_TypeDescriptor_t               type;        ///< Type of the key
  mcuxClKey_Location_t                     location;    ///< Internal location of the key
  const mcuxClKey_ProtectionDescriptor_t * protection;  ///< Protection mechanism applied to the key stored in the container
  void *                                  pLinkedData; ///< Pointer to auxiliary data linked to the key
};

/**
 * @brief Function prototype for protocol specific key generation function pointer.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_KeyGenFct_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (* mcuxClKey_KeyGenFct_t)(
        mcuxClSession_Handle_t pSession,
        mcuxClKey_Generation_t generation,
        mcuxClKey_Handle_t privKey,
        mcuxClKey_Handle_t pubKey
));

/**
 * @brief Struct of generation descriptor
 */
struct mcuxClKey_GenerationDescriptor
{
  mcuxClKey_KeyGenFct_t pKeyGenFct;    ///< Pointer to the protocol specific key pair generation function
  uint32_t protectionTokenKeyGenFct;  ///< Protection token of the protocol specific key generation function
  const void *pProtocolDescriptor;    ///< Pointer to additional parameters for the protocol specific key generation function
};

#ifdef MCUXCL_FEATURE_KEY_DERIVATION

/**
 * @brief Struct of derivation algorithm descriptor
 */
struct mcuxClKey_DerivationAlgorithmDescriptor {
  mcuxClKey_DerivationEngine_t pDerivationEngine;   ///< Pointer to the key derivation engine
  uint32_t protectionTokenDerivationEngine;        ///< Protection token of the key derivation engine
};

/**
 * @brief Generic key derivation function descriptor structure.
 *
 * @param    derivationAlgorithm     Function pointer to the key derivation algorithm function
 * @param    macMode                 Mac mode type, in case a Mac mode is used within the key derivation algorithm
 * @param    hashFunction            Hash algorithm type, in case a hash algorithm is used within the key derivation algorithm (note that for HMAC modes the hash algorithm is determined by the macMode)
 * @param    options                 Generic options field containing algorithm-specific parameters (e.g., counter length or iteration count)
 */
struct mcuxClKey_DerivationMode {
  const mcuxClKey_DerivationAlgorithmDescriptor_t * derivationAlgorithm;
  const mcuxClMac_ModeDescriptor_t * macMode;
  const mcuxClHash_AlgorithmDescriptor_t * hashFunction;
  uint32_t options;
};

typedef struct mcuxClKeyDerivation_WorkArea {
  uint8_t input_Wa[8u];
  uint8_t context_Wa[MCUXCLMAC_MAX_CONTEXT_SIZE];
  uint8_t macResult_Wa[MCUXCLMAC_MAX_OUTPUT_SIZE];
}mcuxClKeyDerivation_WorkArea_t;
#endif /* MCUXCL_FEATURE_KEY_DERIVATION */


#ifdef MCUXCL_FEATURE_KEY_AGREEMENT
/**
 * Mode/Skeleton function types
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_AgreementFct_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_AgreementFct_t) (
    mcuxClSession_Handle_t pSession,
    mcuxClKey_Agreement_t agreement,
    mcuxClKey_Handle_t key,
    mcuxClKey_Handle_t otherKey,
    mcuxClKey_Agreement_AdditionalInput_t additionalInputs[],
    uint32_t numberOfInputs,
    uint8_t * pOut,
    uint32_t * const pOutLength
));

/**
 * @brief Key agreement descriptor structure
 *
 * This structure captures all the information that the Key interfaces need to
 * know about a particular Key agreement algorithm.
 */
struct mcuxClKey_AgreementDescriptor {
  mcuxClKey_AgreementFct_t   pAgreementFct;  ///< Pointer to the protocol specific key agreement function
  uint32_t protectionTokenAgreementFct;     ///< Protection token of the protocol specific key agreement function
  const void *pProtocolDescriptor;          ///< Pointer to additional parameters for the protocol specific key agreement function
};

#ifdef MCUXCL_FEATURE_KEY_SELFTEST
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClKey_Agreement_SelfTestFct_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) (*mcuxClKey_Agreement_SelfTestFct_t) (
  mcuxClSession_Handle_t  session,
  mcuxClKey_Agreement_t   agreement
));
#endif /* MCUXCL_FEATURE_KEY_SELFTEST */
#endif /* MCUXCL_FEATURE_KEY_AGREEMENT */

#ifdef MCUXCL_FEATURE_KEY_SELFTEST
struct mcuxClKey_TestDescriptor {
#ifdef MCUXCL_FEATURE_KEY_AGREEMENT
  mcuxClKey_Agreement_SelfTestFct_t pSelfTestFct;
  uint32_t               protectionTokenSelfTestFct;
#endif /* MCUXCL_FEATURE_KEY_AGREEMENT */
};
#endif /* MCUXCL_FEATURE_KEY_SELFTEST */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_TYPES_INTERNAL_H_ */
