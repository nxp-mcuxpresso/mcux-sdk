/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

#include <mcuxClKey.h>
#include <mcuxClSession.h>
#include <mcuxClCss.h>

/**
 * @defgroup mcuxClMac_Types mcuxClMac_Types
 * @brief Defines all types of the @ref mcuxClMac component
 * @ingroup mcuxClMac
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
 * @brief Type for Mac component error codes.
 */
typedef uint32_t mcuxClMac_Status_t;

/**
 * @brief Type for error codes used by code-flow protected Mac component functions.
 */
typedef uint64_t mcuxClMac_Status_Protected_t;

#define MCUXCLMAC_ERRORCODE_OK           ((mcuxClMac_Status_t) 0xE4E4E4E4u) ///< Mac operation successful
#define MCUXCLMAC_ERRORCODE_ERROR        ((mcuxClMac_Status_t) 0xE4E44E4Eu) ///< Error occurred during Mac operation
#define MCUXCLMAC_ERRORCODE_FAULT_ATTACK ((mcuxClMac_Status_t) 0xE4E40F0Fu) ///< Fault attack (unexpected behaviour) detected

/**
 * @brief Mac Mode structure
 *
 * This internal structure provides all implementation details for a mode to the top level mcuxClMac functions
 *
 */
struct mcuxClMac_Mode;

/**
 * @brief Mac Mode type
 *
 * This internal type provides all implementation details for a mode to the top level mcuxClMac functions
 *
 */
typedef struct mcuxClMac_Mode mcuxClMac_Mode_t;

/**
 * @brief Mode definition for CMAC
 *
 */
extern const mcuxClMac_Mode_t mcuxClMac_Mode_CMAC;

/**
 * @brief Mode definition for HMAC_SHA2_256
 *
 * HMAC_SHA2_256 can only be executed in Oneshot mode.
 * Partial processing is not supported.
 *
 * The input buffer will be modified by applying padding to it. The caller
 * must ensure that the input buffer is large enough by determining its size
 * using #MCUXCLMAC_GET_HMAC_INPUTBUFFER_LENGTH on the input.
 *
 * Also note that HMAC only works with keys loaded into coprocessor (see
 * @ref mcuxClKey for details).
 */
extern const mcuxClMac_Mode_t mcuxClMac_Mode_HMAC_SHA2_256;

#define MCUXCL_HMAC_SIZE_OF_LENGTH_FIELD 8U ///< Size of HMAC length field
#define MCUXCL_HMAC_MIN_PADDING_LENGTH (MCUXCL_HMAC_SIZE_OF_LENGTH_FIELD + 1U) ///< Size of minimum HMAC padding length
#define MCUXCLMAC_GET_HMAC_INPUTBUFFER_LENGTH(dataLength) (((dataLength + MCUXCL_HMAC_MIN_PADDING_LENGTH) + (MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256) - 1) / (MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256)) * MCUXCLCSS_HASH_BLOCK_SIZE_SHA_256 ///< Formula to calculate input buffer size for HMAC with SHA-256

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
 * @brief Mac Cpu Work Area structure
 *
 */
struct mcuxClMac_WaCpu_t;

/**
 * @brief Mac Cpu Work Area type
 *
 */
typedef struct mcuxClMac_WaCpu_t mcuxClMac_WaCpu_t;

/**
 * @}
 */ /* mcuxClMac_Types */

#endif /* MCUXCLMAC_TYPES_H_ */
