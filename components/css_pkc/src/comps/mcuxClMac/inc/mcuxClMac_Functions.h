/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClMac_Functions.h
 * @brief Top-level API of the mcuxClMac component
 */

#ifndef MCUXCLMAC_FUNCTIONS_H_
#define MCUXCLMAC_FUNCTIONS_H_

#include <mcuxClSession_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClMac_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClMac_Functions mcuxClMac_Functions
 * @brief Defines all functions of @ref mcuxClMac
 * @ingroup mcuxClMac
 * @{
 */

/****************************************************************************/
/* ONESHOT                                                                  */
/****************************************************************************/

/**
 * @brief One-shot message authentication code (MAC) computation.
 *
 * This function performs a MAC computation in one shot. The algorithm to be
 * used will be determined based on the key that is provided.
 *
 * For example, to perform an AES MAC computation with a 128-bit key in CMAC
 * mode on padded data, the following needs to be provided:
 *  - AES128 key
 *  - CMAC mode
 *  - Input data, size must be a multiple of the AES block size
 *  - Output data buffer, at least the size of a single AES block
 *
 * If the selected mode @p mode is HMAC, i.e. #mcuxClMac_Mode_HMAC_SHA2_256,
 * the input buffer @p in will be modified by applying padding to it. The caller
 * must ensure that the input buffer is large enough by determining its size
 * using #MCUXCLMAC_GET_HMAC_INPUTBUFFER_LENGTH on the data size @p inSize.
 *
 * Also note that HMAC only works with keys loaded into coprocessor (see
 * @ref mcuxClKey for details).
 *
 * @param[in]  session
 * @param[in]  key     Key to be used to authenticate the data.
 * @param[in]  mode    Mode that should be used during the MAC operation.
 * @param[in]  in      Pointer to the input buffer that contains the data that
 *                     needs to be authenticated.
 * @param[in]  inSize  Number of bytes of data in the @p in buffer.
 * @param[out] mac     Pointer to the output buffer where the MAC needs to be
 *                     written.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_ERRORCODE_OK      Mac operation successful
 * @retval MCUXCLMAC_ERRORCODE_ERROR   Error occurred during Mac operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_compute)
mcuxClMac_Status_Protected_t mcuxClMac_compute(
  mcuxClSession_Handle_t session,
  const mcuxClKey_Handle_t key,
  const mcuxClMac_Mode_t mode,
  const uint8_t * const in,
  uint32_t inSize,
  uint8_t * const mac
);

/****************************************************************************/
/* MULTIPART                                                                */
/****************************************************************************/

/**
 * @brief Initialization for a multipart MAC computation.
 *
 * This function performs the initialization of a context for a multipart MAC
 * computation. The algorithm to be used will be determined based on the key
 * that is provided.
 *
 * This function should only be called once, as the first step for a multipart
 * computation.
 *
 * For example, to perform a multipart AES MAC computation with a 128-bit key
 * in CMAC mode on padded data, the following needs to be provided in this step:
 *  - AES128 key
 *  - CMAC mode
 *
 * The size of the context depends on the mode used
 * (see @ref mcuxClMac_MemoryConsumption).
 *
 * @see mcuxClMac_process
 * @see mcuxClMac_finish
 *
 * @param[in] session
 * @param[in] context
 * @param[in] key     Key to be used to MAC the data.
 * @param[in] mode    Mode that should be used during the MAC operation.
 *
 * @return Status of the context initialization.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_init)
mcuxClMac_Status_Protected_t mcuxClMac_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  const mcuxClKey_Handle_t key,
  const mcuxClMac_Mode_t mode
); /* init */

/**
 * @brief Data processing for a multipart MAC computation.
 *
 * This function performs the data processing for a multipart MAC computation.
 *
 * This function can be called multiple times, after the multipart context
 * initialization.
 *
 * For example, to perform a multipart AES MAC computation with a 128-bit key
 * in CMAC mode on padded data, the following needs to be provided in this step:
 *  - Input data, size must be a multiple of the AES block size
 *
 * The size of the context depends on the mode used
 * (see @ref mcuxClMac_MemoryConsumption).
 *
 * @see mcuxClMac_init
 * @see mcuxClMac_finish
 *
 * @param[in]  session
 * @param[in]  context
 * @param[in]  in      Pointer to the input buffer that contains the data that
 *                     need to be processed.
 * @param[in]  inSize  Number of bytes of data in the @p in buffer.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_ERRORCODE_OK      Mac operation successful
 * @retval MCUXCLMAC_ERRORCODE_ERROR   Error occurred during Mac operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_process)
mcuxClMac_Status_Protected_t mcuxClMac_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  const uint8_t *const in,
  uint32_t inSize
); /* update */

/**
 * @brief MAC generation for a multipart MAC computation.
 *
 * This function performs the final MAC generation step for a multipart MAC
 * computation.
 *
 * This function should only be called once, as the last step for a multipart
 * computation.
 *
 * For example, to perform a multipart AES MAC computation with a 128-bit key
 * in CMAC mode on padded data, the following needs to be provided in this step:
 *  - Output data buffer, at least the size of a single AES block
 *
 * The size of the context depends on the mode used
 * (see @ref mcuxClMac_MemoryConsumption).
 *
 * @see mcuxClMac_init
 * @see mcuxClMac_process
 *
 * @param[in]  session
 * @param[in]  context
 * @param[out] mac     Pointer to the output buffer where the MAC needs to be
 *                     written.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_ERRORCODE_OK      Mac operation successful
 * @retval MCUXCLMAC_ERRORCODE_ERROR   Error occurred during Mac operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_finish)
mcuxClMac_Status_Protected_t mcuxClMac_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t *const context,
  uint8_t *const mac
); /* finalize compute */

/**
 * @}
 */ /* mcuxClMac_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_FUNCTIONS_H_ */
