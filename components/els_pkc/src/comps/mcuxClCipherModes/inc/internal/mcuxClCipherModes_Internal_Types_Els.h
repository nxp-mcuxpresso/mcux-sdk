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

/** @file  mcuxClCipherModes_Internal_Types_Els.h
 *  @brief Internal type definitions for the mcuxClCipherModes component
 */

#ifndef MCUXCLCIPHERMODES_INTERNAL_TYPES_ELS_H_
#define MCUXCLCIPHERMODES_INTERNAL_TYPES_ELS_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClAes.h>
#include <internal/mcuxClAes_Internal_Constants.h>
#include <internal/mcuxClAes_Ctx.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession.h>

#include <internal/mcuxClPadding_Types_Internal.h>
#include <internal/mcuxClCipherModes_Internal_Constants.h>
#include <internal/mcuxClCipherModes_Wa.h>
#include <mcuxClCipher_Types.h>
#include <internal/mcuxClCipher_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Cipher context structure for ELS modes
 *
 * This structure is used to store the information about the current operation
 * and the relevant internal ELS state.
 */
typedef struct mcuxClCipherModes_Context_Aes_Els
{
  mcuxClCipher_Context_t   common;

  mcuxClKey_Descriptor_t * pKey;
  uint8_t     blockBuffer[MCUXCLAES_BLOCK_SIZE];   /* Buffer used when not enough data for full block */
  uint32_t    ivState[MCUXCLAES_BLOCK_SIZE_IN_WORDS]; /* IV and internal state */
} mcuxClCipherModes_Context_Aes_Els_t;

/**
 * @brief Engine function type for ELS modes
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClCipher_Status_t) (*mcuxClCipherModes_EngineFunc_AesEls_t) (
  mcuxClSession_Handle_t session,
  mcuxClCipherModes_Context_Aes_Els_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut
);

/**
 * @brief Cipher mode algorithm descriptor structure for AES algorithms using ELS
 *
 * This structure captures all the information that the Cipher interfaces need
 * to know about an ELS AES Cipher mode algorithm.
 */
typedef struct mcuxClCipherModes_AlgorithmDescriptor_Aes_Els
{
  mcuxClCipherModes_EngineFunc_AesEls_t    cryptEngine;
  mcuxClPadding_addPaddingMode_t           addPadding;
  uint32_t                    protection_token_engine;
  uint32_t                    protection_token_addPadding;
  uint32_t                    mode;
  uint32_t                    direction;
  uint32_t                    blockLength;
  uint32_t                    ivLength;
  uint32_t                    granularity;
} mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t;

/**
 * @brief Cipher mode algorithm type for AES algorithms using ELS
 *
 * This type is used to refer to an ELS AES Cipher mode algorithm.
 */
typedef const mcuxClCipherModes_AlgorithmDescriptor_Aes_Els_t * const mcuxClCipherModes_Algorithm_Aes_Els_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHERMODES_INTERNAL_TYPES_ELS_H_ */
