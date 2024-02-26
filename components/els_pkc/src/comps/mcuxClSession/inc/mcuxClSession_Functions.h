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
 * @file  mcuxClSession_Functions.h
 * @brief Top-level API of the mcuxClSession component
 */

#ifndef MCUXCLSESSION_FUNCTIONS_H_
#define MCUXCLSESSION_FUNCTIONS_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClSession_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClSession_Functions mcuxClSession_Functions
 * @brief Defines all functions of @ref mcuxClSession
 * @ingroup mcuxClSession
 * @{
 */

/**
 * @brief Initialize a Crypto Library session.
 *
 * @param  pSession     Session to be initialized.
 * @param  pCpuWaBuffer Pointer to buffer to be used as workarea for CPU operations.
 *                      This pointer shall be CPU-word aligned.
 * @param  cpuWaLength  Size (in bytes) of the workarea for CPU operations.
 *                      The size shall be a multiple of CPU wordsize.
 * @param  pPkcWaBuffer Pointer to buffer to be used as workarea for PKC operations.
 *                      This pointer shall be PKC-word aligned.
 * @param  pkcWaLength  Size (in bytes) of the workarea for PKC operations.
 *                      The size shall be a multiple of **CPU** wordsize.
 *
 * @return status
 * @retval #MCUXCLSESSION_STATUS_OK     Session has been initialized successfully
 * @retval #MCUXCLSESSION_STATUS_ERROR  Error occurred during session initializing.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_init(
  mcuxClSession_Handle_t pSession,
  uint32_t * const pCpuWaBuffer,
  uint32_t cpuWaLength,
  uint32_t * const pPkcWaBuffer,
  uint32_t pkcWaLength
  /* TBD: sclRandom_Context_t * const rngCtx */
);

/**
 * @brief Set the RTF option in a Crypto Library session.
 *
 * @param  pSession    Session to be initialized.
 * @param  pRtf        buffer to store the rtf result.
 * @param  RtfOptions  Options to define RTF processing.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_setRtf)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_setRtf(
  mcuxClSession_Handle_t pSession,
  uint8_t * const pRtf,
  mcuxClSession_Rtf_t RtfOptions
);







/**
 * @brief Clean up a Crypto Library session.
 *
 * This function will (securely) cleanup the session, which will still be usable afterwards.
 *
 * @param  pSession Session to be cleaned.
 *
 * @return status
 * @retval #MCUXCLSESSION_STATUS_OK  Session operation successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_cleanup)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_cleanup(
  mcuxClSession_Handle_t pSession
);

/**
 * @brief Destroy a Crypto Library session.
 *
 * This function will (securely) cleanup the session, including uninitialization etc.
 * The session will no longer be usable afterwards.
 *
 * @param  pSession Session to be destroyed.
 *
 * @return status
 * @retval #MCUXCLSESSION_STATUS_OK     Session operation successful
 * @retval #MCUXCLSESSION_STATUS_ERROR  Error occurred during Session operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_destroy)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_destroy(
  mcuxClSession_Handle_t pSession
);

#ifdef MCUXCL_FEATURE_SESSION_HAS_RANDOM
/**
 * @brief Function to switch to another random configuration.
 *
 * @param  session     Session to set the new random configuration.
 * @param  randomMode  Random data generation mode/algorithm. It should be the same mode used to initialize randomCtx.
 * @param  randomCtx   Random context.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_setRandom)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_setRandom(
    mcuxClSession_Handle_t session,
    mcuxClRandom_Mode_t randomMode,
    mcuxClRandom_Context_t randomCtx
);
#endif // MCUXCL_FEATURE_SESSION_HAS_RANDOM

/**
 * @}
 */ /* mcuxClSession_Functions */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSESSION_FUNCTIONS_H_ */
