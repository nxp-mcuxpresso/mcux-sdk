/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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

/** @file  mcuxClAead_Constants.h
 *  @brief Constants for use with the mcuxClAead component */

#ifndef MCUXCLAEAD_CONSTANTS_H_
#define MCUXCLAEAD_CONSTANTS_H_

/**
 * @defgroup mcuxClAead_Constants mcuxClAead_Constants
 * @brief Constants of @ref mcuxClAead component
 * @ingroup mcuxClAead
 * @{
 */

/**
 * @defgroup MCUXCLAEAD_STATUS_ MCUXCLAEAD_STATUS_
 * @brief Return code definitions
 * @ingroup mcuxClAead_Constants
 * @{
 */

#include <mcuxClConfig.h> // Exported features flags header

/* Error codes */
/* TODO CLNS-8684: Unionize and describe return codes */
#define MCUXCLAEAD_STATUS_ERROR              ((mcuxClAead_Status_t) 0x01115330u)
#define MCUXCLAEAD_STATUS_FAULT_ATTACK       ((mcuxClAead_Status_t) 0x0111F0F0u)
#define MCUXCLAEAD_STATUS_OK                 ((mcuxClAead_Status_t) 0x01112E03u)
#define MCUXCLAEAD_STATUS_NOT_OK             ((mcuxClAead_Status_t) 0x011153FCu)

/**@}*/

/**@}*/

#endif /* MCUXCLAEAD_CONSTANTS_H_ */
