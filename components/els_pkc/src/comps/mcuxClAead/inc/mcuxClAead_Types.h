/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021,2023 NXP                                             */
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

/** @file  mcuxClAead_Types.h
 *  @brief Type definitions for the mcuxClAead component
 */

#ifndef MCUXCLAEAD_TYPES_H_
#define MCUXCLAEAD_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <mcuxClSession.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup clAeadTypes AEAD type definitions
 * @brief Types used by the AEAD operations.
 * @ingroup mcuxClAead
 * @{
 */

/**
 * @brief AEAD mode/algorithm descriptor structure
 *
 * This structure captures all the information that the AEAD interfaces need
 * to know about a particular AEAD mode/algorithm.
 */
struct mcuxClAead_ModeDescriptor;

/**
 * @brief AEAD mode/algorithm descriptor type
 *
 * This type captures all the information that the AEAD interfaces need to
 * know about a particular AEAD mode/algorithm.
 */
typedef struct mcuxClAead_ModeDescriptor mcuxClAead_ModeDescriptor_t;


/**
 * @brief AEAD mode/algorithm type
 *
 * This type is used to refer to an AEAD mode/algorithm.
 */
typedef const mcuxClAead_ModeDescriptor_t * const mcuxClAead_Mode_t;

/**
 * @brief Aead selftest mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Aead selftest interfaces need
 * to know about a particular Aead selftest mode/algorithm.
 */
struct mcuxClAead_TestDescriptor;

/**
 * @brief Aead selftest mode/algorithm descriptor type
 *
 * This type captures all the information that the Aead selftest interfaces need
 * to know about a particular Aead selftest mode/algorithm.
 */
typedef struct mcuxClAead_TestDescriptor mcuxClAead_TestDescriptor_t;

/**
 * @brief Aead selftest mode/algorithm type
 *
 * This type is used to refer to a Aead selftest mode/algorithm.
 */
typedef const mcuxClAead_TestDescriptor_t * const mcuxClAead_Test_t;

/**
 * @brief AEAD context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 */
struct mcuxClAead_Context;

/**
 * @brief AEAD context type
 *
 * This type is used in the multi-part interfaces to store the information
 * about the current operation and the relevant internal state.
 */
typedef struct mcuxClAead_Context mcuxClAead_Context_t;

/**
 * @brief AEAD status code
 *
 * This type provides information about the status of the AEAD operation that
 * has been performed.
 */
typedef uint32_t mcuxClAead_Status_t;

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLAEAD_TYPES_H_ */
