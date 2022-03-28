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
 * @file  mcuxClRsa_Internal_Types.h
 * @brief Internal type definitions for the mcuxClRsa component
 */

#ifndef MCUXCLRSA_INTERNAL_TYPES_H_
#define MCUXCLRSA_INTERNAL_TYPES_H_

#include <mcuxClRsa_Types.h>

 /**
 * @defgroup mcuxClRsa_Internal_Macros mcuxClRsa_Internal_Macros
 * @brief Defines all internal macros of the @ref mcuxClRsa component
 * @ingroup mcuxClRsa
 * @{
 */

/**
 * @defgroup MCUXCLRSA_INTERNAL_STATUS_ MCUXCLRSA_INTERNAL_STATUS_
 * @brief Internal return code definitions
 * @ingroup mcuxClRsa_Internal_Macros
 * @{
 */
#define MCUXCLRSA_INTERNAL_STATUS_KEYOP_OK    ((mcuxClRsa_Status_t) 0xB2B25A5Au )
#define MCUXCLRSA_INTERNAL_STATUS_ENCODE_OK   ((mcuxClRsa_Status_t) 0xB2B29A9Au )
#define MCUXCLRSA_INTERNAL_STATUS_MGF_OK      ((mcuxClRsa_Status_t) 0xB2B2AAAAu )
/** @} */

/**
 * @}
 */

/***********************************************************
 *  TYPES RELATED TO PADDING FUNCTIONALITY
 **********************************************************/

 /**
 * @brief Function type for padding engine
 *
 * Generic function pointer to padding function declarations
 *
 * @param[in]  pSession                Pointer to session.
 * @param[in]  pInput                  Pointer to input message or message digest to padding function.
 * @param[in]  inputLength             Length of input in bytes.
 * @param[in]  pVerificationInput      Pointer to encoded message that is verified.
 * @param[in]  pHashAlgo               Pointer to hash algorithm used in padding function.
 * @param[in]  pLabel                  Pointer to label in case of OAEP padding.
 * @param[in]  saltlabelLength         Length of salt in case of PSS padding, or label in case of OAEP padding.
 * @param[in]  keyBitLength            Bitlength of public modulus n.
 * @param[in]  options                 Options.
 * @param[out] pOutput                 Output of padding or verification function.
 *
 * @return Status of the padding operation
 */
typedef mcuxClRsa_Status_Protected_t (* mcuxClRsa_PadVerModeEngine_t)(
  mcuxClSession_Handle_t       pSession,
  const uint8_t * const       pInput,
  const uint32_t              inputLength,
  uint8_t * const             pVerificationInput,
  const mcuxClHash_Algo_t *    pHashAlgo,
  const uint8_t *             pLabel,
  const uint32_t              saltlabelLength,
  const uint32_t              keyBitLength,
  const uint32_t              options,
  uint8_t * const             pOutput);

/**
 * @brief Structure type for Sign/Verify mode, i.e. required information to execute a selected sign/verify mode.
 */
struct mcuxClRsa_SignVerifyMode_t
{
  uint32_t                      EncodeVerify_FunId;
  const mcuxClHash_Algo_t *      pHashAlgo1;
  mcuxClHash_Algo_t *            pHashAlgo2;
  mcuxClRsa_PadVerModeEngine_t   pPaddingFunction;
};

#endif /* MCUXCLRSA_INTERNAL_TYPES_H_ */
