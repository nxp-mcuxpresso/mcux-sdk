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
 * @file  mcuxCsslMemory_Types.h
 * @brief Type definitions for the mcuxCsslMemory component
 */

#ifndef MCUXCSSLMEMORY_TYPES_H
#define MCUXCSSLMEMORY_TYPES_H

#include <stdint.h>

/**
 * @defgroup mcuxCsslMemory_Types mcuxCsslMemory_Types
 * @brief Defines common macros and types of @ref mcuxCsslMemory
 * @ingroup mcuxCsslMemory
 * @{
 */

/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxCsslMemory_Types_Macros mcuxCsslMemory_Types_Macros
 * @brief Defines all macros of @ref mcuxCsslMemory_Types
 * @ingroup mcuxCsslMemory_Types
 * @{
 */
#define MCUXCSSLMEMORY_STATUS_OK                 ((mcuxCsslMemory_Status_t) 0xE1E11E1Eu) ///< The operation was successful
#define MCUXCSSLMEMORY_STATUS_EQUAL              ((mcuxCsslMemory_Status_t) 0xE1E1E1E1u) ///< The two contents of the Memory Compare are equal
#define MCUXCSSLMEMORY_STATUS_NOT_EQUAL          ((mcuxCsslMemory_Status_t) 0x1E1E1E1Eu) ///< The two contents of the Memory Compare are not equal
#define MCUXCSSLMEMORY_STATUS_INVALID_PARAMETER  ((mcuxCsslMemory_Status_t) 0x69696969u) ///< A parameter was invalid
#define MCUXCSSLMEMORY_STATUS_FAULT              ((mcuxCsslMemory_Status_t) 0x96969696u) ///< A fault occurred in the execution

#define MCUXCSSLMEMORY_KEEP_ORDER     ((uint32_t) 0xE1E139A5u)  ///< Data storing in destination buffer in original order.
#define MCUXCSSLMEMORY_REVERSE_ORDER  ((uint32_t) 0xE1E1395Au)  ///< Data storing in destination buffer with reversed order.
/**
 * @}
 */


/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @defgroup mcuxCsslMemory_Types_Types mcuxCsslMemory_Types_Types
 * @brief Defines all types of @ref mcuxCsslMemory_Types
 * @ingroup mcuxCsslMemory_Types
 * @{
 */

/**
 * @brief Type for CSSL Memory status codes.
 */
typedef uint32_t mcuxCsslMemory_Status_t;
/**
 * @}
 *
 * @}
 */

#endif /* MCUXCSSLMEMORY_TYPES_H */
