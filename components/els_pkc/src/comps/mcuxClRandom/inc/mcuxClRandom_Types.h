/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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
 * @file  mcuxClRandom_Types.h
 * @brief Type definitions of mcuxClRandom component
 */


#ifndef MCUXCLRANDOM_TYPES_H_
#define MCUXCLRANDOM_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <mcuxClCore_Platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/* Types of mcuxClRandom                                   */
/**********************************************************/
/**
 * @defgroup mcuxClRandom_Types mcuxClRandom_Types
 * @brief Defines all types of @ref mcuxClRandom
 * @ingroup mcuxClRandom
 * @{
 */

/**
 * @brief Type for status codes of mcuxClRandom component functions.
 *
 * This type provides information about the status of the Random operation
 * that has been performed.
 */
typedef uint32_t mcuxClRandom_Status_t;

/**
 * @brief Random context structure
 *
 * This structure is used to store the information about the current random
 * data generator and the relevant internal state.
 */
struct mcuxClRandom_Context;

/**
 * @brief Random context type
 *
 * This type is used to store the information about the current random data
 * generator and the relevant internal state.
 */
typedef struct mcuxClRandom_Context mcuxClRandom_ContextDescriptor_t;

/**
 * @brief Random context type
 *
 * This type is used to refer to a Random context.
 */
typedef mcuxClRandom_ContextDescriptor_t * mcuxClRandom_Context_t;

/**
 * @brief Random data generation mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Random interfaces need
 * to know about a particular Random data generation mode/algorithm.
 */
struct mcuxClRandom_ModeDescriptor;

/**
 * @brief Random data generation mode/algorithm descriptor type
 *
 * This type captures all the information that the Random interfaces need to
 * know about a particular Random data generation mode/algorithm.
 */
typedef struct mcuxClRandom_ModeDescriptor mcuxClRandom_ModeDescriptor_t;

/**
 * @brief Random data generation mode/algorithm type
 *
 * This type is used to refer to a Random data generation mode/algorithm.
 */
typedef const mcuxClRandom_ModeDescriptor_t * mcuxClRandom_Mode_t;

/**
 * @brief Random config structure
 *
 * This structure is used to store context and mode pointers.
 */
struct mcuxClRandom_Config {
    mcuxClRandom_Mode_t    mode;      ///< Random data generation mode/algorithm
    mcuxClRandom_Context_t ctx;       ///< Context for the Rng
};

/**
 * @brief Random config type
 *
 * This type is used to store context and mode.
 */
typedef struct mcuxClRandom_Config mcuxClRandom_Config_t;

/**
 * @}
 */ /* mcuxClRandom_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLRANDOM_TYPES_H_ */
