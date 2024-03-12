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

/** @file  mcuxClAes_Types.h
 *  @brief Type definitions for the mcuxClAes component
 */

#ifndef MCUXCLAES_TYPES_H_
#define MCUXCLAES_TYPES_H_

#include <stdint.h>

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClKey_Constants.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClAes_Types mcuxClAes_Types
 * @brief Types associated with @ref mcuxClAes
 * @ingroup mcuxClAes
 * @{
 */

/**
 * @brief AES status code
 *
 * This type provides information about the status of the AES operation that
 * has been performed.
 */
typedef uint32_t mcuxClAes_Status_t;

/**
 * @}
 */ /* mcuxClAes_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAES_TYPES_H_ */
