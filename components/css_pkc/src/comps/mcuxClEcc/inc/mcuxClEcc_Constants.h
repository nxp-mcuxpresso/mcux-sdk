/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxClEcc_Constants.h
 * @brief Constants definition for domain parameters of supported curves
 */


#ifndef MCUXCLECC_CONSTANTS_H_
#define MCUXCLECC_CONSTANTS_H_


#include <mcuxClEcc_Types.h>

/**
 * @defgroup mcuxClEcc_Constants mcuxClEcc_Constants
 * @brief Defines constants of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */

/** Curve25519 domain parameters */
extern const mcuxClEcc_Mont_DomainParams_t mcuxClEcc_Mont_DomainParams_Curve25519;


/* https://docs.oracle.com/en/java/javacard/3.1/jc_api_srvc/api_classic/constant-values.html#javacard.security.NamedParameterSpec.X25519
 * Supported curveID based on javacard api
 */

#define MCUXCLECC_CURVEID_MONT_X25519 (259u)

/**
 * @}
 */ /* mcuxClEcc_Constants */

#endif /* MCUXCLECC_CONSTANTS_H_ */
