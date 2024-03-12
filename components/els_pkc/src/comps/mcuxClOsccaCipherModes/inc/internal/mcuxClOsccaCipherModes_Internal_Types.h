/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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

/** @file  mcuxClOsccaCipherModes_Internal_Types.h
 *  @brief Internal type definitions for the mcuxClOsccaCipherModes component
 */

#ifndef MCUXCLOSCCACIPHERMODES_INTERNAL_TYPES_H_
#define MCUXCLOSCCACIPHERMODES_INTERNAL_TYPES_H_

#include <stddef.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClKey_Types.h>
#include <mcuxClSession.h>
#include <mcuxClCipher.h>
#include <mcuxClPadding.h>
#include <internal/mcuxClPadding_Internal.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <internal/mcuxClCipher_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef MCUXCL_FEATURE_CIPHERMODES_SM4
#define MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_ECB 0x00U
#define MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CBC 0x01U
#define MCUXCLOSCCACIPHERPARAM_ALGORITHM_SM4_CTR 0x02U
#define MCUXCLOSCCACIPHER_ENCRYPT  (MCUXCLOSCCASM4_ENCRYPT)
#define MCUXCLOSCCACIPHER_DECRYPT  (MCUXCLOSCCASM4_DECRYPT)

/**
 * @brief Cipher context structure for SM4 modes
 *
 * This structure is used to store the information about the current operation
 * and the relevant internal SM4 state.
 */
typedef struct mcuxClOsccaCipherModes_Context_Sm4
{
  mcuxClCipher_Context_t   common;

  uint32_t roundKeys[128];
  uint8_t  state[3][MCUXCLOSCCASM4_BLOCK_SIZE];     ///< state/intermediate result of the cipher operation
  uint32_t out;                                      ///< out index in state buffer
  uint32_t in;                                       ///< in index in state buffer
  uint32_t iv;                                       ///< iv index in state buffer
} mcuxClOsccaCipherModes_Context_Sm4_t;

/**
 * @brief Cipher mode algorithm descriptor structure for SM4 algorithms
 *
 * This structure captures all the information that the Cipher interfaces need
 * to know about SM4 Cipher mode algorithm.
 */
typedef struct mcuxClCipherModes_AlgorithmDescriptor_SM4
{
  mcuxClPadding_addPaddingMode_t  addPadding;
  uint32_t                       protection_token_addPadding;
  uint32_t                       mode;
  uint32_t                       direction;
  uint32_t                       blockLength;
  uint32_t                       granularity;
} mcuxClCipherModes_AlgorithmDescriptor_SM4_t;

/**
 * @brief Cipher mode algorithm type for SM4 algorithms
 *
 * This type is used to refer to SM4 Cipher mode algorithm.
 */
typedef const mcuxClCipherModes_AlgorithmDescriptor_SM4_t * const mcuxClCipherModes_Algorithm_SM4_t;


#endif /* MCUXCL_FEATURE_CIPHERMODES_SM4 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCACIPHERMODES_INTERNAL_TYPES_H_ */
