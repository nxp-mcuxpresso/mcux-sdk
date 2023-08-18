/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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

/** @file  mcuxClCipher_Constants.h
 *  @brief Constants for use with the mcuxClCipher component */

#ifndef MCUXCLCIPHER_CONSTANTS_H_
#define MCUXCLCIPHER_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClCipher_Constants mcuxClCipher_Constants
 * @brief Constants of @ref mcuxClCipher component
 * @ingroup mcuxClCipher
 * @{
 */

/* Error codes */
/* TODO  CLNS-5679: discuss values */
#define MCUXCLCIPHER_STATUS_ERROR                        ((mcuxClCipher_Status_t) 0xE0AE0001u)
#define MCUXCLCIPHER_STATUS_FAILURE                      ((mcuxClCipher_Status_t) 0xE0AE0020u)
#define MCUXCLCIPHER_STATUS_INVALID_INPUT                ((mcuxClCipher_Status_t) 0xE0AE0030u)
#define MCUXCLCIPHER_STATUS_ERROR_MEMORY_ALLOCATION      ((mcuxClCipher_Status_t) 0xE0AE0040u) // memory allocation error
#define MCUXCLCIPHER_STATUS_FAULT_ATTACK                 ((mcuxClCipher_Status_t) 0xE0AEF0F0u)
#define MCUXCLCIPHER_STATUS_OK                           ((mcuxClCipher_Status_t) 0x00AE0000u)

/** @}*/
#endif /* MCUXCLCIPHER_CONSTANTS_H_ */
