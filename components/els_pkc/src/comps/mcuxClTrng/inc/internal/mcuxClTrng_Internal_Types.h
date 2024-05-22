/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClTrng_Internal_Types.h
 * @brief Type definitions of mcuxClTrng component
 */


#ifndef MCUXCLTRNG_INTERNAL_TYPES_H_
#define MCUXCLTRNG_INTERNAL_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <stdint.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Types of mcuxClTrng                                     */
/**********************************************************/
/**
 * @defgroup mcuxClTrng_Internal_Types mcuxClTrng_Internal_Types
 * @brief Defines all types of @ref mcuxClTrng
 * @ingroup mcuxClTrng
 * @{
 */

/**
 * @brief Type for status codes of mcuxClTrng component functions.
 *
 * This type provides information about the status of the Trng operation
 * that has been performed.
 */
typedef uint32_t mcuxClTrng_Status_t;

/**
 * @}
 */ /* mcuxClTrng_Internal_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLTRNG_INTERNAL_TYPES_H_ */
