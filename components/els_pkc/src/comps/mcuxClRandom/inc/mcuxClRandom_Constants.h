/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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
 * @file  mcuxClRandom_Constants.h
 * @brief Constant definitions of mcuxClRandom component
 */


#ifndef MCUXCLRANDOM_CONSTANTS_H_
#define MCUXCLRANDOM_CONSTANTS_H_


#include <mcuxClConfig.h> // Exported features flags header

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Constants of mcuxClRandom                               */
/**********************************************************/
/**
 * @defgroup mcuxClRandom_Constants mcuxClRandom_Constants
 * @brief Defines all contstants of @ref mcuxClRandom
 * @ingroup mcuxClRandom
 * @{
 */

/** @addtogroup MCUXCLRANDOM_STATUS_
 * mcuxClRandom return code definitions
 * @{ */
#define MCUXCLRANDOM_STATUS_ERROR                  0x0BBB5330u  ///< Random function returned error
#define MCUXCLRANDOM_STATUS_LOW_SECURITY_STRENGTH  0x0BBB5334u  ///< Security strength of given RNG lower than requested
#define MCUXCLRANDOM_STATUS_INVALID_PARAM          0x0BBB53F8u  ///< Random function parameter invalid
#define MCUXCLRANDOM_STATUS_OK                     0x0BBB2E03u  ///< Random function returned successfully
#define MCUXCLRANDOM_STATUS_FAULT_ATTACK           0x0BBBF0F0u  ///< Random function returned fault attack
/** @} */

/**
 * @}
 */ /* mcuxClRandom_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOM_TYPES_H_ */
