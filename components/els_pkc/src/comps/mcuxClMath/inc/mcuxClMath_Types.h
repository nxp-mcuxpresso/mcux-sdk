/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021, 2023 NXP                                            */
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
 * @file  mcuxClMac_Types.h
 * @brief Type definitions for the mcuxClMac component
 */


#ifndef MCUXCLMATH_TYPES_H_
#define MCUXCLMATH_TYPES_H_

#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>


/**********************************************
 * CONSTANTS
 **********************************************/
/* None */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClMath_Macros mcuxClMath_Macros
 * @brief Defines all macros of @ref mcuxClMath
 * @ingroup mcuxClMath
 * @{
 */

/**
 * @brief Type for error codes used by Math component functions.
 */
typedef uint32_t mcuxClMath_Status_t;

/**
 * @brief Deprecated type for error codes used by code-flow protected Math component functions.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMath_Status_t) mcuxClMath_Status_Protected_t;

#define MCUXCLMATH_STATUS_OK        ((mcuxClMath_Status_t) 0x0FF32E03u)  ///< Math operation successful
#define MCUXCLMATH_ERRORCODE_OK     MCUXCLMATH_STATUS_OK                 ///< \deprecated Replaced by MCUXCLMATH_STATUS_OK
#define MCUXCLMATH_STATUS_ERROR     ((mcuxClMath_Status_t) 0x0FF35330u)  ///< Error occurred during Math operation
#define MCUXCLMATH_ERRORCODE_ERROR  MCUXCLMATH_STATUS_ERROR              ///< \deprecated Replaced by MCUXCLMATH_STATUS_ERROR

/**
 * @brief Option to disable the operand re-randomization in the secure modular exponentiation.
 * TODO CLNS-7824: analyze how to use the SecModExp in RsaKg MillerRabinTest, and remove secOption to always re-randomize
 */
#define MCUXCLMATH_SECMODEXP_OPTION_DIS_RERAND (0xA5A5A5A5u)

/**
 * @}
 */ /* mcuxClMath_Macros */


#endif /* MCUXCLMATH_TYPES_H_ */
