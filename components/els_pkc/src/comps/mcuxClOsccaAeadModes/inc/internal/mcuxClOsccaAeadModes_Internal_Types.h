/*--------------------------------------------------------------------------*/
/* Copyright  2022-2024 NXP                                                 */
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

/** @file  mcuxClOsccaAeadModes_Internal_Types.h
 *  @brief Internal type definitions for the mcuxClOsccaAeadModes component */


#ifndef MCUXCLOSCCAAEADMODES_INTERNAL_TYPES_H_
#define MCUXCLOSCCAAEADMODES_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClAead_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClBuffer.h>
#include <mcuxClSession_Types.h>
#include <internal/mcuxClAead_Ctx.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup MCUXCLOSCCAAEADMODES_OPTION_ MCUXCLOSCCAAEADMODES_OPTION_
 * @brief Options for the skeleton function
 * @ingroup mcuxClAead_Internal_Types
 * @{
 */

/* Options for the skeleton function */
#define MCUXCLOSCCAAEADMODES_OPTION_ONESHOT     0x0000000Fu
#define MCUXCLOSCCAAEADMODES_OPTION_INIT        0x00000001u
#define MCUXCLOSCCAAEADMODES_OPTION_PROCESS_AAD 0x00000002u
#define MCUXCLOSCCAAEADMODES_OPTION_PROCESS     0x00000004u
#define MCUXCLOSCCAAEADMODES_OPTION_FINISH      0x00000008u
#define MCUXCLOSCCAAEADMODES_OPTION_VERIFY      0x00000010u

/* Options for the engine function */
#define MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AUTH              0x00000001u
#define MCUXCLOSCCAAEADMODES_ENGINE_OPTION_ENC               0x00000002u
#define MCUXCLOSCCAAEADMODES_ENGINE_OPTION_AEAD              0x00000003u
#define MCUXCLOSCCAAEADMODES_ENGINE_OPTION_INIT              0x00000008u

/**
 * @brief AEAD context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 */
typedef struct mcuxClOsccaAeadModes_Context{
    mcuxClAead_Context_t common;
    uint8_t     partialData[16u];
    uint32_t    partialDataLength;
    uint32_t    aadLength;
    uint32_t    dataLength;
    uint32_t    tagLength;
    uint8_t     state[80u];
    uint32_t    processedDataLength;
    uint32_t    direction;
    mcuxClKey_Descriptor_t            *key;
} mcuxClOsccaAeadModes_Context_t;


/**
 * @brief Function type for an AEAD mode skeleton function
 *
 * An AEAD mode skeleton function encrypts or decrypts the input message @p pIn to the output @p pOut according to the @p mode.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClOsccaAeadModes_Skeleton_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClOsccaAeadModes_Skeleton_t) (
  mcuxClSession_Handle_t session,
  mcuxClOsccaAeadModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag,
  uint32_t tagLength,
  uint32_t options  //!< 15: oneshot, 1: init, 2: update aad, 4: update, 8: finish, 16: verify
));

/**
 * @brief Function type for an AEAD mode engine function
 *
 * An AEAD mode engine function encrypts or decrypts a single block @p pIn to the output @p pOut.
 */
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClOsccaAeadModes_Engine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClOsccaAeadModes_Engine_t) (
  mcuxClSession_Handle_t session,
  mcuxClOsccaAeadModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t options  //!< 1: auth, 2: enc, 3: aead, 4: init, 8: finish
));

/**
 * @brief AEAD mode/algorithm descriptor structure
 *
 * This structure captures all the information that the AEAD interfaces need
 * to know about a particular AEAD mode/algorithm.
 */
typedef struct mcuxClOsccaAead_AlgorithmDescriptor {
    mcuxClOsccaAeadModes_Skeleton_t  pSkeleton;
    mcuxClOsccaAeadModes_Engine_t    pEngine;
    uint32_t                  protection_token_skeleton;
    uint32_t                  protection_token_engine;
    uint32_t                  direction;
} mcuxClOsccaAeadModes_algorithm_t;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCAAEADMODES_INTERNAL_TYPES_H_ */
