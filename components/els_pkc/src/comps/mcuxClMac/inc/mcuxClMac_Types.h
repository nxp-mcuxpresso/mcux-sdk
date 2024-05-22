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

/** @file  mcuxClMac_Types.h
 *  @brief Type definitions for the mcuxClMac component
 */

#ifndef MCUXCLMAC_TYPES_H_
#define MCUXCLMAC_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

/**
 * @defgroup mcuxClMac_Types mcuxClMac_Types
 * @brief Defines all types of the @ref mcuxClMac component
 * @ingroup mcuxClMac
 * @{
 */

/**********************************************
 * TYPEDEFS
 **********************************************/

/**
 * @brief Type for Mac component error codes.
 */
typedef uint32_t mcuxClMac_Status_t;

/**
 * @brief MAC mode/algorithm descriptor structure
 *
 * This structure captures all the information that the MAC interfaces need to
 * know about a particular MAC mode/algorithm.
 */
struct mcuxClMac_ModeDescriptor;

/**
 * @brief MAC mode/algorithm descriptor type
 *
 * This type captures all the information that the MAC interfaces need to
 * know about a particular MAC mode/algorithm.
*/
typedef struct mcuxClMac_ModeDescriptor mcuxClMac_ModeDescriptor_t;

/**
 * @brief MAC mode/algorithm type
 *
 * This type is used to refer to a MAC mode/algorithm.
 */
typedef const mcuxClMac_ModeDescriptor_t * const mcuxClMac_Mode_t;

/**
 * @brief MAC custom mode/algorithm type
 *
 * This type is used to refer to a custom MAC mode/algorithm that
 * can be created via a provided constructor.
 */
typedef mcuxClMac_ModeDescriptor_t * const mcuxClMac_CustomMode_t;

/**
 * @brief Mac selftest mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Mac selftest interfaces need
 * to know about a particular Mac selftest mode/algorithm.
 */
struct mcuxClMac_TestDescriptor;

/**
 * @brief Mac selftest mode/algorithm descriptor type
 *
 * This type captures all the information that the Mac selftest interfaces need
 * to know about a particular Mac selftest mode/algorithm.
 */
typedef struct mcuxClMac_TestDescriptor mcuxClMac_TestDescriptor_t;

/**
 * @brief Mac selftest mode/algorithm type
 *
 * This type is used to refer to a Mac selftest mode/algorithm.
 */
typedef const mcuxClMac_TestDescriptor_t * const mcuxClMac_Test_t;

/**
 * @brief Mac context structure
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular Mac mode/algorithm to work.
 */
struct mcuxClMac_Context;

/**
 * @brief Mac context type
 *
 * This type captures all the information that the Mac interface needs to
 * know for a particular Mac mode/algorithm to work.
 *
 * The size of the context depends on the mode used
 * (see @ref mcuxClMac_MemoryConsumption).
 *
 */
typedef struct mcuxClMac_Context mcuxClMac_Context_t;

/**
 * @}
 */ /* mcuxClMac_Types */

#endif /* MCUXCLMAC_TYPES_H_ */
