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

/**
 * @file  mcuxClMacModes_Constants.h
 * @brief Constants for the mcuxClMacModes component
 */

#ifndef MCUXCLMACMODES_CONSTANTS_H_
#define MCUXCLMACMODES_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClMacModes_Constants mcuxClMacModes Constants
 * @brief Constants of @ref mcuxClMacModes component
 * @ingroup mcuxClMacModes
 * @{
 */

/* Output sizes */
#define MCUXCLMAC_CBCMAC_OUTPUT_SIZE                   (16u)                                              ///< Size of CBCMAC output in bytes:       128 bits (16 bytes)
#define MCUXCLMAC_CBCMAC_OUTPUT_SIZE_IN_WORDS          (MCUXCLMAC_CBCMAC_OUTPUT_SIZE / sizeof(uint32_t)) ///< Size of CBCMAC output in bytes:       128 bits (16 bytes)
#define MCUXCLMAC_CMAC_OUTPUT_SIZE                     (16u)                                              ///< Size of CMAC output in bytes:         128 bits (16 bytes)
#define MCUXCLMAC_CMAC_OUTPUT_SIZE_IN_WORDS            (MCUXCLMAC_CMAC_OUTPUT_SIZE / sizeof(uint32_t))   ///< Size of CMAC output in bytes:         128 bits (16 bytes)

#define MCUXCLMACMODES_MAX_OUTPUT_SIZE                 (16u)

#define MCUXCLMACMODES_MAX_OUTPUT_SIZE_IN_WORDS        (MCUXCLMACMODES_MAX_OUTPUT_SIZE / sizeof(uint32_t))

/** @}*/

#endif /* MCUXCLMACMODES_CONSTANTS_H_ */
