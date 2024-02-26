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
 * @file  mcuxClPkc_Types.h
 * @brief Type definitions of mcuxClPkc component
 */


#ifndef MCUXCLPKC_TYPES_H
#define MCUXCLPKC_TYPES_H


#include <platform_specific_headers.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>


/**
 * @defgroup mcuxClPkc_Macros mcuxClPkc_Macros
 * @brief Defines all macros of @ref mcuxClPkc
 * @ingroup mcuxClPkc
 * @{
 */


/**********************************************
 * CONSTANTS
 **********************************************/
/* None */


/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @addtogroup MCUXCLPKC_STATUS_
 * mcuxClPkc return code definitions
 * @{
 */
/**
 * @brief Type for error codes used by PKC component functions.
 */
typedef uint32_t mcuxClPkc_Status_t;

/**
 * @brief Deprecated type for error codes used by code-flow protected PKC component functions.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_Status_Protected_t;

#define MCUXCLPKC_STATUS_OK  ((mcuxClPkc_Status_t) 0x0AAA2E03u)  ///< PKC operation successful
#define MCUXCLPKC_STATUS_NOK ((mcuxClPkc_Status_t) 0x0AAA53FCu)  ///< PKC operation not successful
/**
 * @}
 */ /* MCUXCLPKC_STATUS_ */


/**********************************************************/
/* Helper macros                                          */
/**********************************************************/
/**
 * @addtogroup MCUXCLPKC_MISC_
 * mcuxClPkc misc macros and definitions
 * @{
 */
/** @brief Round-up a length to a multiple of PKC wordsize. */
#define MCUXCLPKC_ROUNDUP_SIZE(byteLen)  \
    (((uint32_t) (byteLen) + (uint32_t)MCUXCLPKC_WORDSIZE - (uint32_t)1u) & (~((uint32_t) MCUXCLPKC_WORDSIZE - (uint32_t)1u)))

/** @brief Macros for packing 4 8-bit parameters. */
#define MCUXCLPKC_PACKARGS4(byte3_MSByte, byte2, byte1, byte0_LSByte)  \
    (  ((uint32_t) (byte3_MSByte) << 24) | ((uint32_t) (byte2) << 16)  \
     | ((uint32_t) (byte1) << 8) | ((uint32_t) (byte0_LSByte)) )

/** @brief Macros for packing 2 8-bit parameters. */
#define MCUXCLPKC_PACKARGS2(hi8, lo8)  \
    ( ((uint16_t) (hi8) << 8) | ((uint16_t) (lo8)) )


/**********************************************************/
/* PKC information                                        */
/**********************************************************/
#define MCUXCLPKC_RAM_START_ADDRESS  PKC_RAM_ADDR  ///< PKC workarea address
#define MCUXCLPKC_WORDSIZE  8u  ///< PKC wordsize in byte


/**
 * @}
 */ /* MCUXCLPKC_MISC_ */

/**
 * @}
 */ /* mcuxClEcc_Macros */

#endif /* #MCUXCLPKC_TYPES_H */
