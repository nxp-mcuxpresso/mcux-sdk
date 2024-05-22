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

/**
 * @file  mcuxClTrng_Internal_Constants.h
 * @brief Constant definitions of mcuxClTrng component
 */


#ifndef MCUXCLTRNG_INTERNAL_CONSTANTS_H_
#define MCUXCLTRNG_INTERNAL_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <stdint.h>
#include <internal/mcuxClTrng_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Constants of mcuxClTrng                                 */
/**********************************************************/
/**
 * @defgroup mcuxClTrng_Internal_Constants mcuxClTrng_Internal_Constants
 * @brief Defines all contstants of @ref mcuxClTrng
 * @ingroup mcuxClTrng
 * @{
 */

/** @addtogroup MCUXCLTRNG_STATUS_
 * mcuxClTrng return code definitions
 * @{ */
#define MCUXCLTRNG_STATUS_ERROR                  ((mcuxClTrng_Status_t) 0x0FF15330u)  ///< An error occurred during the TRNG operation
#define MCUXCLTRNG_STATUS_OK                     ((mcuxClTrng_Status_t) 0x0FF12E03u)  ///< TRNG operation returned successfully
#define MCUXCLTRNG_STATUS_FAULT_ATTACK           ((mcuxClTrng_Status_t) 0x0FF1F0F0u)  ///< A fault attack is detected
/** @} */

#ifdef MCUXCL_FEATURE_TRNG_ELS
/**
 * @brief Defines all macros of @ref mcuxClTrng_ELS
 * @ingroup mcuxClTrng_ELS
 * @{
 */
#define MCUXCLTRNG_ELS_TRNG_OUTPUT_SIZE  (32u)                    ///< output byte size of #mcuxClEls_Rng_DrbgRequestRaw_Async
#endif

/**
 * @}
 */ /* mcuxClTrng_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLTRNG_INTERNAL_CONSTANTS_H_ */
