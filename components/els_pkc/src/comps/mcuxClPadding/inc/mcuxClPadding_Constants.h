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

/** @file  mcuxClPadding_Constants.h
 *  @brief Constants definitions for the mcuxClPadding component
 */

#ifndef MCUXCLPADDING_CONSTANTS_H_
#define MCUXCLPADDING_CONSTANTS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup clPadding Constants definitions
 * @brief Constants used by the Padding component.
 * @ingroup mcuxClPadding
 * @{
 */

/**********************************************
 * CONSTANTS
 **********************************************/

/**
 * @brief Return codes
 */
#define MCUXCLPADDING_STATUS_OK           ((mcuxClPadding_Status_t) 0x0FF42E03u) ///< Padding operation successful
#define MCUXCLPADDING_STATUS_NOT_OK       ((mcuxClPadding_Status_t) 0x0FF453FCu) ///< Incorrect padding
#define MCUXCLPADDING_STATUS_ERROR        ((mcuxClPadding_Status_t) 0x0FF45330u) ///< Error occurred during Padding operation
#define MCUXCLPADDING_STATUS_FAULT_ATTACK ((mcuxClPadding_Status_t) 0x0FF4F0F0u) ///< Fault attack (unexpected behaviour) detected

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPADDING_CONSTANTS_H_ */
