/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 * @file  mcuxClHmac_Functions.h
 * @brief Functions for the mcuxClHmac component
 */

#ifndef MCUXCLHMAC_FUNCTIONS_H_
#define MCUXCLHMAC_FUNCTIONS_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClSession_Types.h>
#include <mcuxClMac_Types.h>
#include <mcuxClHash_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClHmac_Functions mcuxClHmac Functions
 * @brief Defines all functions of @ref mcuxClHmac
 * @ingroup mcuxClHmac
 * @{
*/

/**
 * @defgroup mcuxClHmac_Constructors APIs to construct HMAC modes
 * @brief Interfaces to construct HMAC modes of operation.
 * @ingroup mcuxClHmac_Functions
 * @{
 */

/**
 * @brief This function creates a HMAC mode descriptor for software implementations of HMAC.
 *
 * The SW-HMAC modes of operation require additional input, hence a
 * mode descriptor has to be constructed with this function.
 * The resulting descriptor will be written to @p mode.
 *
 * This function must be called before any SW-HMAC operation is performed.
 *
 * @param mode[out]             Pointer to HMAC custom mode to be initialized.
 * @param mcuxClHash_Algo_t[in]  Pointer to the Hash algorithm descriptor to be used. SecSha algorithm descriptors are not supported.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClHmac_createHmacMode)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMac_Status_t) mcuxClHmac_createHmacMode(
    mcuxClMac_CustomMode_t mode,
    mcuxClHash_Algo_t hashAlgorithm
);

/**
 * @}
 */ /* mcuxClHmac_Constructors */

/**
 * @}
 */ /* mcuxClHmac_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHMAC_FUNCTIONS_H_ */
