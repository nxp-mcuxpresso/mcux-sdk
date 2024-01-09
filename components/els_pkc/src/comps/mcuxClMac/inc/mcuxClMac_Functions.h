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
 * @file  mcuxClMac_Functions.h
 * @brief Top-level API of the mcuxClMac component
 */

#ifndef MCUXCLMAC_FUNCTIONS_H_
#define MCUXCLMAC_FUNCTIONS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxClMac_Types.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClMac_Functions mcuxClMac Functions
 * @brief Defines all functions of @ref mcuxClMac
 * @ingroup mcuxClMac
 * @{
*/

/****************************************************************************/
/* ONESHOT                                                                  */
/****************************************************************************/

/**
 * @defgroup mcuxClMac_OneShot One-shot MAC interfaces
 * @brief Interfaces to perform MAC operations in one shot.
 * @ingroup mcuxClMac_Functions
 * @{
 */

/**
 * @brief One-shot message authentication code (MAC) computation function.
 *
 * This function performs a MAC computation in one shot. The algorithm to be
 * used will be determined based on the key that is provided.
 *
 * For example, to perform an AES MAC computation with a 128-bit key in CMAC
 * mode on padded data, the following needs to be provided:
 *  - AES128 key
 *  - CMAC mode
 *  - Input data
 *  - Output data buffer, at least the size of a single AES block
 *
 * @attention In some cases restrictions may apply, e.g. the input buffer must
 * be prepared for padding. Please refer to mcuxClMac_Modes.h to find further
 * details and restrictions for each specific mode.
 *
 * @param[in]  session     Handle for the current CL session.
 * @param[in]  key         Key to be used to authenticate the data.
 * @param[in]  mode        Mode that should be used during the MAC operation.
 * @param[in]  pIn         Pointer to the input buffer that contains the data that
 *                         needs to be authenticated.
 * @param[in]  inLength    Number of bytes of data in the @p pIn buffer.
 * @param[out] pMac        Pointer to the output buffer where the MAC needs to be written.
 * @param[out] pMacLength  Will be incremented by the number of bytes of data that
 *                         have been written to the @p pMac buffer.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_STATUS_OK            Mac operation successful
 * @retval MCUXCLMAC_STATUS_ERROR         Error occurred during Mac operation
 * @retval MCUXCLMAC_STATUS_INVALID_PARAM An invalid parameter was given to the function
 * @retval MCUXCLMAC_STATUS_FAULT_ATTACK  Fault attack detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_compute)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_compute(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
);

/**
 * @}
 */ /* mcuxClMac_OneShot */


/****************************************************************************/
/* MULTIPART                                                                */
/****************************************************************************/

/**
 * @defgroup mcuxClMac_MultiPart Multi part MAC interfaces
 * @brief Interfaces to perform MAC operations in multi part.
 * @ingroup mcuxClMac_Functions
 * @{
 */

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
 * @param[in]  session   Handle for the current CL session.
 * @param[in]  pContext  MAC context which is used to maintain the state and
 *                       store other relevant information about the operation.
 * @param[in]  key       Key to be used to MAC the data.
 * @param[in]  mode      Mode that should be used during the MAC operation.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_STATUS_OK            Mac operation successful
 * @retval MCUXCLMAC_STATUS_ERROR         Error occurred during Mac operation
 * @retval MCUXCLMAC_STATUS_INVALID_PARAM An invalid parameter was given to the function
 * @retval MCUXCLMAC_STATUS_FAULT_ATTACK  Fault attack detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_init(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClMac_Mode_t mode
); /* init */

/**
 * @brief Data processing for a multipart MAC computation.
 *
 * This function performs the data processing for a multipart MAC computation.
 * The algorithm and key to be used will be determined based on the context that is provided.

 * This function can be called multiple times, after the multipart context
 * initialization.
 *
 * For example, to perform a multipart AES MAC computation with a 128-bit key
 * in CMAC mode on padded data, the following needs to be provided in this step:
 *  - Input data
 *
 * The size of the context depends on the mode used
 * (see @ref mcuxClMac_MemoryConsumption).
 *
 * @see mcuxClMac_init
 *
 * @param      session   Handle for the current CL session.
 * @param[in]  pContext  MAC context which is used to maintain the state and
 *                       store other relevant information about the operation.
 * @param[in]  pIn       Pointer to the input buffer that contains the data that
 *                       need to be processed.
 * @param[in]  inLength  Number of bytes of data in the @p in buffer.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_STATUS_OK            Mac operation successful
 * @retval MCUXCLMAC_STATUS_ERROR         Error occurred during Mac operation
 * @retval MCUXCLMAC_STATUS_INVALID_PARAM An invalid parameter was given to the function
 * @retval MCUXCLMAC_STATUS_FAULT_ATTACK  Fault attack detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_process(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength
); /* update */

/**
 * @brief Finalize a MAC generation for a multipart MAC computation.
 *
 * This function performs the final MAC generation step for a multipart MAC
 * computation.
 * The algorithm and key to be used will be determined based on the context that is provided.
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
 * @param[in]  session     Handle for the current CL session.
 * @param[in]  pContext    MAC context which is used to maintain the state and
 *                         store other relevant information about the operation.
 * @param[out] pMac        Pointer to the output buffer where the MAC needs to be written.
 * @param[out] pMacLength  Will be incremented by the number of bytes of data that
 *                         have been written to the @p pMac buffer.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMAC_STATUS_OK            Mac operation successful
 * @retval MCUXCLMAC_STATUS_ERROR         Error occurred during Mac operation
 * @retval MCUXCLMAC_STATUS_INVALID_PARAM An invalid parameter was given to the function
 * @retval MCUXCLMAC_STATUS_FAULT_ATTACK  Fault attack detected
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClMac_finish(
  mcuxClSession_Handle_t session,
  mcuxClMac_Context_t * const pContext,
  mcuxCl_Buffer_t pMac,
  uint32_t * const pMacLength
); /* finalize compute */

/**
 * @}
 */ /* mcuxClMac_MultiPart */

/**
 * @}
 */ /* mcuxClMac_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMAC_FUNCTIONS_H_ */
