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
 * @file  mcuxClPadding_Types.h
 * @brief Type definitions for the mcuxClPadding component
 */


#ifndef MCUXCLPADDING_TYPES_H_
#define MCUXCLPADDING_TYPES_H_

#include <stdint.h>
#include <mcuxClConfig.h> // Exported features flags header


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup clPaddingTypes Padding type definitions
 * @brief Types used by the Padding component.
 * @ingroup mcuxClPadding
 * @{
 */


/**
 * @brief Padding status code
 *
 * This type provides information about the status of the Padding operation that
 * has been performed.
 */
typedef uint32_t mcuxClPadding_Status_t;

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPADDING_TYPES_H_ */
