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

/**
 * @file  mcuxClPrng_Internal_Constants.h
 * @brief Constant definitions of mcuxClPrng component
 */


#ifndef MCUXCLPRNG_INTERNAL_CONSTANTS_H_
#define MCUXCLPRNG_INTERNAL_CONSTANTS_H_

#include <internal/mcuxClPrng_Internal_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Constants of mcuxClPrng                                 */
/**********************************************************/
/**
 * @defgroup mcuxClPrng_Internal_Constants mcuxClPrng_Internal_Constants
 * @brief Defines all contstants of @ref mcuxClPrng
 * @ingroup mcuxClPrng
 * @{
 */

/** @addtogroup MCUXCLPRNG_STATUS_
 * mcuxClPrng return code definitions
 * @{ */
#define MCUXCLPRNG_STATUS_ERROR                  ((mcuxClPrng_Status_t) 0x0FF55330u)  ///< An error occurred during the PRNG operation
#define MCUXCLPRNG_STATUS_OK                     ((mcuxClPrng_Status_t) 0x0FF52E03u)  ///< PRNG operation returned successfully
#define MCUXCLPRNG_STATUS_FAULT_ATTACK           ((mcuxClPrng_Status_t) 0x0FF5F0F0u)  ///< A fault attack is detected
/** @} */


/**
 * @}
 */ /* mcuxClPrng_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPRNG_INTERNAL_CONSTANTS_H_ */
