/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClAeadModes_Internal_Constants.h
 *  @brief Internal definitions for the mcuxClAeadModes component */


#ifndef MCUXCLAEADMODES_INTERNAL_CONSTANTS_H_
#define MCUXCLAEADMODES_INTERNAL_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

#define MCUXCLAEADMODES_ENCRYPTION (1u)
#define MCUXCLAEADMODES_DECRYPTION (2u)

/* Buffer B0 contains the first block B0, l(a), and the first AAD bytes */
#define MCUXCLAEADMODES_CCM_B0_SIZE     (32u)

/* The maximum lengths for tag and nonce are given by the limitations from CCM:
 * The only possible lengths are:
 *    nonce: 7,8,9,10,11,12,13
 *    tag: 4,6,8,10,12,14,16
 */
#define MCUXCLAEADMODES_TAGLEN_MAX           (16u)
#define MCUXCLAEADMODES_NONCELEN_MAX         (13u)

#endif /* MCUXCLAEADMODES_INTERNAL_CONSTANTS_H_ */
