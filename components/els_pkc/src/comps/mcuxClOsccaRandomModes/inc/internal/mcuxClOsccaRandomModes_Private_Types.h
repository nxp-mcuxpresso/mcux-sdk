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
 * @file  mcuxClOsccaRandomModes_Private_Types.h
 * @brief Internal private type definitions of mcuxClOsccaRandomModes component
 */


#ifndef MCUXCLOSCCARANDOMMODES_PRIVATE_TYPES_H_
#define MCUXCLOSCCARANDOMMODES_PRIVATE_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Internal private types of mcuxClOsccaRandomModes        */
/**********************************************************/
/**
 * @defgroup mcuxClOsccaRandomModes_Private_Types mcuxClOsccaRandomModes_Private_Types
 * @brief Defines all private types of @ref mcuxClOsccaRandomModes
 * @ingroup mcuxClOsccaRandomModes_Private_Types
 * @{
 */

/**
 * @brief Defines to specify which mode a OSCCA RNG is operated in
 */
#define MCUXCLOSCCARANDOMMODES_OSCCA_MODE  (0xd6d6d6d6u)

/**
 * @}
 */ /* mcuxClOsccaRandomModes_Private_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCARANDOMMODES_PRIVATE_TYPES_H_ */
