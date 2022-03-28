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

/** @file  mcuxClSession_Functions.h
 *  @brief Top-level API of the mcuxClSession component */

#ifndef MCUXCLSESSION_FUNCTIONS_H_
#define MCUXCLSESSION_FUNCTIONS_H_

#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>

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
 * \brief Initialize a Crypto Library session.
 *
 * \param  session     Session to be initialized.
 * \param  cpuWaBuffer Buffer to be used as workarea for CPU operations.
 * \param  cpuWaSize   Size of the workarea for CPU operations.
 * \param  pkcWaBuffer Buffer to be used as workarea for PKC operations.
 * \param  pkcWaSize   Size of the workarea for PKC operations.
 * \param  rngCtx      Context to be used for RNG operations.
 *
 * \return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_init)
mcuxClSession_Status_Protected_t mcuxClSession_init(
  mcuxClSession_Handle_t session,
  uint32_t * const cpuWaBuffer,
  uint32_t cpuWaSize,
  uint32_t * const pkcWaBuffer,
  uint32_t pkcWaSize
  /* TBD: sclRandom_Context_t * const rngCtx */
);

/**
 * \brief Set the RTF option in a Crypto Library session.
 *
 * \param  session     Session to be initialized.
 * \param  RtfOptions  Options to define RTF processing.
 *
 * \return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_setRtf)
mcuxClSession_Status_Protected_t mcuxClSession_setRtf(
  mcuxClSession_Handle_t session,
  mcuxClSession_Rtf_t RtfOptions
);

/**
 * \brief Clean up a Crypto Library session.
 *
 * This function will (securely) cleanup the session, which will still be usable afterwards.
 *
 * \param  session Session to be cleaned.
 *
 * \return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_cleanup)
mcuxClSession_Status_Protected_t mcuxClSession_cleanup(
  mcuxClSession_Handle_t session
);

/**
 * \brief Destroy a Crypto Library session.
 *
 * This function will (securely) cleanup the session, including uninitialization etc.
 * The session will no longer be usable afterwards.
 *
 * \param  session Session to be destroyed.
 *
 * \return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_destroy)
mcuxClSession_Status_Protected_t mcuxClSession_destroy(
  mcuxClSession_Handle_t session
);

/**
 * @}
 */ /* mcuxClSession_Functions */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSESSION_FUNCTIONS_H_ */
