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
 * @file  mcuxClPrng_Internal_Types.h
 * @brief Type definitions of mcuxClPrng component
 */


#ifndef MCUXCLPRNG_INTERNAL_TYPES_H_
#define MCUXCLPRNG_INTERNAL_TYPES_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Types of mcuxClPrng                                     */
/**********************************************************/
/**
 * @defgroup mcuxClPrng_Internal_Types mcuxClPrng_Internal_Types
 * @brief Defines all types of @ref mcuxClPrng
 * @ingroup mcuxClPrng
 * @{
 */

/**
 * @brief Type for status codes of mcuxClPrng component functions.
 *
 * This type provides information about the status of the Prng operation
 * that has been performed.
 */
typedef uint32_t mcuxClPrng_Status_t;

/**
 * @}
 */ /* mcuxClPrng_Internal_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPRNG_INTERNAL_TYPES_H_ */
