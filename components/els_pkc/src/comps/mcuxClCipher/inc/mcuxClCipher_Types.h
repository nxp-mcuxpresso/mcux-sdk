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

/** @file  mcuxClCipher_Types.h
 *  @brief Type definitions for the mcuxClCipher component
 */

#ifndef MCUXCLCIPHER_TYPES_H_
#define MCUXCLCIPHER_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup clCipherTypes Cipher type definitions
 * @brief Types used by the Cipher operations.
 * @ingroup mcuxClCipher
 * @{
 */

/**
 * @brief Cipher mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Cipher interfaces need
 * to know about a particular Cipher mode/algorithm.
 */
struct mcuxClCipher_ModeDescriptor;

/**
 * @brief Cipher mode/algorithm descriptor type
 *
 * This type captures all the information that the Cipher interfaces need to
 * know about a particular Cipher mode/algorithm.
 */
typedef struct mcuxClCipher_ModeDescriptor mcuxClCipher_ModeDescriptor_t;

/**
 * @brief Cipher mode/algorithm type
 *
 * This type is used to refer to a Cipher mode/algorithm.
 */
typedef const mcuxClCipher_ModeDescriptor_t * const mcuxClCipher_Mode_t;

/**
 * @brief Cipher selftest mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Cipher selftest interfaces need
 * to know about a particular Cipher selftest mode/algorithm.
 */
struct mcuxClCipher_TestDescriptor;

/**
 * @brief Cipher selftest mode/algorithm descriptor type
 *
 * This type captures all the information that the Cipher selftest interfaces need to
 * know about a particular Cipher selftest mode/algorithm.
 */
typedef struct mcuxClCipher_TestDescriptor mcuxClCipher_TestDescriptor_t;

/**
 * @brief Cipher selftest mode/algorithm type
 *
 * This type is used to refer to a Cipher selftest mode/algorithm.
 */
typedef const mcuxClCipher_TestDescriptor_t * const mcuxClCipher_Test_t;

/**
 * @brief Cipher context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 */
struct mcuxClCipher_Context;

/**
 * @brief Cipher context type
 *
 * This type is used in the multi-part interfaces to store the information
 * about the current operation and the relevant internal state.
 */
typedef struct mcuxClCipher_Context mcuxClCipher_Context_t;

/**
 * @brief Cipher status code
 *
 * This type provides information about the status of the Cipher operation that
 * has been performed.
 */
typedef uint32_t mcuxClCipher_Status_t;

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCIPHER_TYPES_H_ */
