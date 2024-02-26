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

/** @file  mcuxClHash_Types.h
 *  @brief Type definitions for the mcuxClHash component
 */

#ifndef MCUXCLHASH_TYPES_H_
#define MCUXCLHASH_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClHash_Types mcuxClHash_Types
 * @brief Defines all types of the @ref mcuxClHash component
 * @ingroup mcuxClHash
 * @{
 */

/**
 * @brief Hash mode/algorithm descriptor type
 *
 * This type captures all the information that the Hash interfaces need to
 * know about a particular Hash mode/algorithm.
 *
 */
typedef struct mcuxClHash_AlgorithmDescriptor mcuxClHash_AlgorithmDescriptor_t;

/**
 * @brief Hash mode/algorithm type
 *
 * This type is used to refer to a Hash mode/algorithm.
 *
 */
typedef const mcuxClHash_AlgorithmDescriptor_t * const mcuxClHash_Algo_t;



/**
 * @brief Hash Context buffer type
 *
 * This type is used in the streaming interfaces to store the information
 * about the current operation and the relevant internal state.
 *
 */
typedef struct mcuxClHash_ContextDescriptor mcuxClHash_ContextDescriptor_t;

/**
 * @brief Hash Context type
 *
 * This type is used to refer to the Hash context.
 * It needs to be placed at a 64 Bit-aligned address.
 *
 */
typedef mcuxClHash_ContextDescriptor_t * const mcuxClHash_Context_t;

/**
 * @brief Hash Status type
 *
 * This type is used for hash return values: \ref mcuxClHashStatusValues
 *
 */
typedef uint32_t mcuxClHash_Status_t;

/**@}*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLHASH_TYPES_H_ */
