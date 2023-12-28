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

/** @file  mcuxClPsaDriver_Constants.h
 *  @brief Defines the constants for the @ref mcuxClPsaDriver component
 */

#ifndef MCUXCLPSADRIVER_CONSTANTS_H_
#define MCUXCLPSADRIVER_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClPsaDriver_Constants mcuxClPsaDriver_Constants
 * @brief Defines the internal for the @ref mcuxClPsaDriver component
 * @ingroup mcuxClPsaDriver
 * @{
 */

/* Definition of maximum lengths of key for RSA in bits */
#define MCUXCLPSADRIVER_RSA_KEY_SIZE_MAX (4096u)

/* Definition of maximum lengths of base point order n in bytes */
#define MCUXCLPSADRIVER_ECC_N_SIZE_MAX (256u/8u)  //only secp256r1 supported for now

/* Definition of maximum lengths of prime modulus in bytes */
#define MCUXCLPSADRIVER_ECC_P_SIZE_MAX (256u/8u)  //only secp256r1 supported for now

/**
 * @}
 */ /* mcuxClPsaDriver_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPSADRIVER_CONSTANTS_H_ */

