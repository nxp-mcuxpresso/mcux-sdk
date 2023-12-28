/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

/** @file  mcuxClHmac_Internal_Types.h
 *  @brief Internal header for HMAC types  *
 */

#ifndef MCUXCLHMAC_INTERNAL_TYPES_H_
#define MCUXCLHMAC_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Buffer.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClKey_Types.h>
#include <mcuxClMac_Types.h>
#include <internal/mcuxClMac_Ctx.h>
#include <internal/mcuxClMac_Internal_Types.h>
#include <internal/mcuxClPadding_Types_Internal.h> /* for mcuxClHash_ContextBuffer_t */
#include <mcuxClHash_Types.h>
#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClHashModes_Internal.h>
#include <mcuxClEls_Hmac.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************/
/* Context types            */
/****************************/

/* Contains common part of any mac context for all modes and key descriptor of the key to be used. */
#define MCUXCLHMAC_CONTEXT_COMMON_ENTRIES  \
        mcuxClMac_Context_t common;        \
        mcuxClKey_Descriptor_t * key;

/**
 * @brief HMAC context structure for modes using ELS HW
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular HMAC mode/algorithm to work.
 */
typedef struct mcuxClHmac_Context_Generic
{
    MCUXCLHMAC_CONTEXT_COMMON_ENTRIES
} mcuxClHmac_Context_Generic_t;

/**
 * @brief HMAC context structure for modes using ELS HW
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular HMAC mode/algorithm to work.
 * It also contains information specific to the ELS HW implementation of HMAC.
 */
typedef struct mcuxClHmac_Context_Els
{
    MCUXCLHMAC_CONTEXT_COMMON_ENTRIES
    uint32_t preparedHmacKey[MCUXCLELS_HMAC_PADDED_KEY_SIZE / sizeof(uint32_t)];   /* Padded/Hashed HMAC key, buffer for external HMAC keys */
} mcuxClHmac_Context_Els_t;

/**
 * @brief HMAC context structure for modes using a SW implementation
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular HMAC mode/algorithm to work.
 * It also contains information specific to the SW implementation of HMAC.
 */
typedef struct mcuxClHmac_Context_Sw
{
    MCUXCLHMAC_CONTEXT_COMMON_ENTRIES
    mcuxClHash_ContextDescriptor_t *hashCtx;                                                             /* Hash context for SW-HMAC */
    uint32_t hashContextBuffer[MCUXCLHASHMODES_CONTEXT_MAX_SIZE_INTERNAL_NO_SECSHA / sizeof(uint32_t)];  /* Buffer to store the actual hash context data using maximum size of a hash context */
    uint32_t preparedHmacKey[MCUXCLHASH_BLOCK_SIZE_MAX / sizeof(uint32_t)];                              /* Padded/Hashed HMAC key, must be large enough to hold any block */
} mcuxClHmac_Context_Sw_t;


/****************************/
/* Engine function types    */
/****************************/

/**
 * @brief HMAC engine function type for the oneshot computation
 *
 * These functions will perform the actual HMAC operation.
 * See specific function declarations for details.
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHmac_ComputeEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClHmac_ComputeEngine_t)(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    const uint8_t *const pIn,
    uint32_t inLength,
    uint8_t *const pOut,
    uint32_t *const outLength
));

/**
 * @brief HMAC engine function type for the init phase of a multi-part computation
 *
 * These functions will perform the actual HMAC init operation.
 * See specific function declarations for details.
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHmac_InitEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClHmac_InitEngine_t)(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext
));

/**
 * @brief HMAC engine function type for the update phase of a multi-part computation
 *
 * These functions will perform the actual HMAC update operation.
 * See specific function declarations for details.
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHmac_UpdateEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClHmac_UpdateEngine_t)(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength
));

/**
 * @brief HMAC engine function type for the finalize phase of a multi-part computation
 *
 * These functions will perform the actual HMAC finalize operation.
 * See specific function declarations for details.
 *
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClHmac_FinalizeEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClHmac_FinalizeEngine_t)(
    mcuxClSession_Handle_t session,
    mcuxClHmac_Context_Generic_t * const pContext,
    mcuxCl_Buffer_t pOut,
    uint32_t * const outLength
));


/****************************/
/* Algorithm types          */
/****************************/

/**
 * @brief HMAC structure
 *
 * This internal structure provides all implementation details for the top level mcuxClHmac functions.
 * It consists of Init, Update, Finalize and Oneshot engines and the output size.
 *
 */
typedef struct mcuxClHMac_AlgorithmDescriptor
{
    mcuxClHmac_InitEngine_t engineInit;           ///< engine function to perform the init operation
    uint32_t protectionToken_engineInit;         ///< protection token of the engine function to perform the init operation
    mcuxClHmac_UpdateEngine_t engineUpdate;       ///< engine function to perform the update operation
    uint32_t protectionToken_engineUpdate;       ///< protection token of the engine function to perform the update operation
    mcuxClHmac_FinalizeEngine_t engineFinalize;   ///< engine function to perform the finalize operation
    uint32_t protectionToken_engineFinalize;     ///< protection token of the engine function to perform the finalize operation
    mcuxClHmac_ComputeEngine_t engineOneshot;     ///< engine function to perform the Mac operation in one shot
    uint32_t protectionToken_engineOneshot;      ///< protection token of the engine function to perform the Mac operation in one shot
    mcuxClPadding_addPaddingMode_t addPadding;   ///< padding function to be used. One of mcuxClPaddingMode
    uint32_t protectionToken_addPadding;        ///< protection token of the padding funtion
} mcuxClHmac_AlgorithmDescriptor_t;

/**
 * @brief HMAC algorithm type for algorithms
 *
 * This type is used to refer to an HMAC algorithm.
 */
typedef const mcuxClHmac_AlgorithmDescriptor_t * const mcuxClHmac_Algorithm_t;


/**
 * @brief Forward declaration of HMAC algorithm instances
 *
 */
extern const mcuxClHmac_AlgorithmDescriptor_t mcuxClHmac_AlgorithmDescriptor_Els;

extern const mcuxClHmac_AlgorithmDescriptor_t mcuxClHmac_AlgorithmDescriptor_Sw;


/****************************/
/* Mode descriptor types    */
/****************************/

/**
 * @brief HMAC specific mode descriptor structure
 *
 * This structure captures all the additional information for the SW-HMAC implementation
 * that is not contained in the @ref mcuxClMac_CommonModeDescriptor_t type.
 */
typedef struct mcuxClHmac_ModeDescriptor
{
    const mcuxClHash_AlgorithmDescriptor_t * hashAlgorithm;
} mcuxClHmac_ModeDescriptor_t;

/**
 * @brief Forward declaration of common mode descriptor needed for constructor of HMAC mode
 *
 */
extern const mcuxClMac_CommonModeDescriptor_t mcuxClHmac_CommonModeDescriptor_Sw;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHMAC_INTERNAL_TYPES_H_ */
