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

/** @file  mcuxClMacModes_Els_Types.h
 *  @brief Internal header for MAC types for modes using the ELS HW
 */

#ifndef MCUXCLMACMODES_ELS_TYPES_H_
#define MCUXCLMACMODES_ELS_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClMac_Types.h>
#include <mcuxClKey_Types.h>
#include <internal/mcuxClPadding_Internal.h>
#include <mcuxClMac_Constants.h>
#include <mcuxClMac_Types.h>
#include <mcuxClMacModes_MemoryConsumption.h>
#include <internal/mcuxClMacModes_Internal_Constants.h>
#include <internal/mcuxClMacModes_Els_Ctx.h>
#include <internal/mcuxClMacModes_Wa.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Engine function types
 */

/**
 * @brief Mac engine function type for the oneshot computation
 *
 * This function will perform the actual MAC operation
 *
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_ComputeEngine_t)(
  mcuxClSession_Handle_t session,
  mcuxClMacModes_Context_t * const pContext,
  const uint8_t *const pIn,
  uint32_t inLength,
  uint8_t *const pOut,
  uint32_t *const outLength
);

/**
 * @brief Mac engine function type for the init phase of a multi-part computation
 *
 * This function will perform the actual MAC init operation
 *
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_InitEngine_t)(
  mcuxClSession_Handle_t session,
  mcuxClMacModes_Context_t * const pContext
);

/**
 * @brief Mac engine function type for the update phase of a multi-part computation
 *
 * This function will perform the actual MAC update operation
 *
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_UpdateEngine_t)(
  mcuxClSession_Handle_t session,
  mcuxClMacModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength
);

/**
 * @brief Mac engine function type for the finish phase of a multi-part computation
 *
 * This function will perform the actual MAC finish operation
 *
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) (*mcuxClMac_FinishEngine_t)(
  mcuxClSession_Handle_t session,
  mcuxClMacModes_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const outLength
);



/**
 * Internal structures / types
 */

/**
 * @brief Mac Mode structure
 *
 * This internal structure provides all implementation details for an ELS-based mode to the top level mcuxClMacMode functions.
 * It consists of Init, Update, Finalize and Oneshot engines and the output size.
 *
 */
typedef struct mcuxClMacModes_AlgorithmDescriptor
{
  mcuxClMac_InitEngine_t engineInit;           ///< engine function to perform the init operation
  uint32_t protectionToken_engineInit;        ///< protection token of the engine function to perform the init operation
  mcuxClMac_UpdateEngine_t engineUpdate;       ///< engine function to perform the update operation
  uint32_t protectionToken_engineUpdate;      ///< protection token of the engine function to perform the update operation
  mcuxClMac_FinishEngine_t engineFinalize;     ///< engine function to perform the finalize operation
  uint32_t protectionToken_engineFinalize;    ///< protection token of the engine function to perform the finalize operation
  mcuxClMac_ComputeEngine_t engineOneshot;     ///< engine function to perform the Mac operation in one shot
  uint32_t protectionToken_engineOneshot;     ///< protection token of the engine function to perform the Mac operation in one shot
  mcuxClPadding_addPaddingMode_t addPadding;   ///< padding function to be used. One of mcuxClPaddingMode
  uint32_t protectionToken_addPadding;        ///< protection token of the padding funtion
} mcuxClMacModes_AlgorithmDescriptor_t;

/**
 * @brief MAC mode algorithm type for algorithms using ELS
 *
 * This type is used to refer to an ELS-based MAC mode algorithm.
 */
typedef const mcuxClMacModes_AlgorithmDescriptor_t * const mcuxClMacModes_Algorithm_t;


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* MCUXCLMACMODES_ELS_TYPES_H_ */
