/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClAeadModes_Els_Types.h
 *  @brief Internal: Definitions type for the mcuxClAeadModes component */


#ifndef MCUXCLAEADMODES_ELS_TYPES_H_
#define MCUXCLAEADMODES_ELS_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClAead_Types.h>
#include <internal/mcuxClAead_Internal_Ctx.h>
#include <mcuxClEls_Aead.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup MCUXCLAEADMODES_OPTION_ MCUXCLAEADMODES_OPTION_
 * @brief Options for the skeleton function
 * @ingroup mcuxClAead_Internal_Types
 * @{
 */

/* Options for the skeleton function */
#define MCUXCLAEADMODES_OPTION_ONESHOT     0x0000000Fu
#define MCUXCLAEADMODES_OPTION_INIT        0x00000001u
#define MCUXCLAEADMODES_OPTION_PROCESS_AAD 0x00000002u
#define MCUXCLAEADMODES_OPTION_PROCESS     0x00000004u
#define MCUXCLAEADMODES_OPTION_FINISH      0x00000008u
#define MCUXCLAEADMODES_OPTION_VERIFY      0x00000010u

/* Options for the engine function */
#define MCUXCLAEADMODES_ENGINE_OPTION_AUTH              0x00000001u
#define MCUXCLAEADMODES_ENGINE_OPTION_ENC               0x00000002u
#define MCUXCLAEADMODES_ENGINE_OPTION_AEAD              0x00000003u
#define MCUXCLAEADMODES_ENGINE_OPTION_INIT              0x00000008u
#define MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL          MCUXCLAEADMODES_ENGINE_OPTION_INIT
#define MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START  0x00000010u
#define MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT   0x00000020u
#define MCUXCLAEADMODES_ENGINE_OPTION_AAD               0x00000040u
#define MCUXCLAEADMODES_ENGINE_OPTION_DATA              0x00000080u
#define MCUXCLAEADMODES_ENGINE_OPTION_DATA_FINAL        0x00000100u
#define MCUXCLAEADMODES_ENGINE_OPTION_FINISH            0x00000200u

#define MCUXCLAEADMODES_ENGINE_OPTION_IV_MASK     (MCUXCLAEADMODES_ENGINE_OPTION_IV_FINAL | MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_START | MCUXCLAEADMODES_ENGINE_OPTION_IV_PARTIAL_CONT)
#define MCUXCLAEADMODES_ENGINE_OPTION_DATA_MASK   (MCUXCLAEADMODES_ENGINE_OPTION_DATA | MCUXCLAEADMODES_ENGINE_OPTION_DATA_FINAL)


struct mcuxClAeadModes_Context;
typedef struct mcuxClAeadModes_Context mcuxClAeadModes_Context_t;

/* Offset for the expected final address from the input address to compare with the DMA final output address */
#define MCUXCLAEADMODES_DMA_STEP 0x50u
/**
 * @brief Function type for an AEAD mode skeleton function
 *
 * An AEAD mode skeleton function encrypts or decrypts the input message @p pIn to the output @p pOut according to the @p mode.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_ModeSkeleton_t) (
  mcuxClSession_Handle_t session,
  mcuxClAeadModes_Context_t * const pContext,
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
);

/**
 * @brief Function type for an AEAD mode engine function
 *
 * An AEAD mode engine function encrypts or decrypts a single block @p pIn to the output @p pOut.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) (*mcuxClAead_ModeEngine_t) (
  mcuxClSession_Handle_t session,
  mcuxClAeadModes_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  uint32_t options  //!< 1: auth, 2: enc, 3: aead, 4: init, 8: finish
);

/**
 * @brief AEAD mode/algorithm descriptor structure
 *
 * This structure captures all the information that the AEAD interfaces need
 * to know about a particular AEAD mode/algorithm.
 */
typedef struct mcuxClAead_AlgorithmDescriptor {
    mcuxClAead_ModeSkeleton_t  pSkeleton;
    mcuxClAead_ModeEngine_t    pEngine;
    uint32_t                  protection_token_skeleton;
    uint32_t                  protection_token_engine;
    uint32_t                  direction;
} mcuxClAeadModes_AlgorithmDescriptor_t;

/**
 * @brief AEAD context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 */
struct mcuxClAeadModes_Context{
    mcuxClAead_Context_t common;
    uint8_t     partialData[16];
    uint32_t    partialDataLength;
    uint32_t    aadLength;
    uint32_t    dataLength;
    uint32_t    tagLength;
    uint8_t     state[MCUXCLELS_AEAD_CONTEXT_SIZE];
    uint32_t    processedDataLength;
    mcuxClKey_Descriptor_t            *key;
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEADMODES_ELS_TYPES_H_ */
