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

/** @file  mcuxClHash_Constants.h
 *  @brief Constants for use with the mcuxClHash component */

#ifndef MCUXCLHASH_CONSTANTS_H_
#define MCUXCLHASH_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header

/**
 * @defgroup mcuxClHash_Constants mcuxClHash_Constants
 * @brief Constants of @ref mcuxClHash component
 * @ingroup mcuxClHash
 * @{
 */

/**
 * @defgroup MCUXCLHASH_STATUS_ MCUXCLHASH_STATUS_
 * @brief Return code definitions
 * @ingroup mcuxClHash_Constants
 * @{
 */
#define MCUXCLHASH_STATUS_OK                                  ((mcuxClHash_Status_t) 0x06662E03u)                   ///< Hash operation successful
#define MCUXCLHASH_STATUS_COMPARE_EQUAL                       ((mcuxClHash_Status_t) 0x06662E07u)                   ///< Hash operation and comparison of result successful
#define MCUXCLHASH_COMPARE_EQUAL                              MCUXCLHASH_STATUS_COMPARE_EQUAL                       ///< \deprecated Replaced by MCUXCLHASH_STATUS_COMPARE_EQUAL
#define MCUXCLHASH_STATUS_FAILURE                             ((mcuxClHash_Status_t) 0x06665330u)                   ///< Hash operation failed
#define MCUXCLHASH_FAILURE                                    MCUXCLHASH_STATUS_FAILURE                             ///< \deprecated Replaced by MCUXCLHASH_STATUS_FAILURE
#define MCUXCLHASH_STATUS_INVALID_PARAMS                      ((mcuxClHash_Status_t) 0x066653F8u)                   ///< Hash function called with invalid parameters
#define MCUXCLHASH_STATUS_EXPORT_STATE_NOT_MULTIPLE_OF_BLOCK  ((mcuxClHash_Status_t) 0x06665338u)                   ///< Export on state, for which a NON-multiple of the blocksize has been hashed
#define MCUXCLHASH_EXPORT_STATE_NOT_MULTIPLE_OF_BLOCK         MCUXCLHASH_STATUS_EXPORT_STATE_NOT_MULTIPLE_OF_BLOCK  ///< \deprecated Replaced by MCUXCLHASH_STATUS_EXPORT_STATE_NOT_MULTIPLE_OF_BLOCK
#define MCUXCLHASH_STATUS_COMPARE_NOT_EQUAL                   ((mcuxClHash_Status_t) 0x06668930u)                   ///< Hash operation succeeded, but comparison of result failed
#define MCUXCLHASH_COMPARE_NOT_EQUAL                          ((mcuxClHash_Status_t) 0x06668930u)                   ///< \deprecated Replaced by MCUXCLHASH_STATUS_COMPARE_NOT_EQUAL
#define MCUXCLHASH_STATUS_FULL                                ((mcuxClHash_Status_t) 0x0666538Eu)                   ///< Hash operation failed because the total input size exceeds the upper limit
#define MCUXCLHASH_STATUS_FAULT_ATTACK                        ((mcuxClHash_Status_t) 0x0666F0F0u)                   ///< Fault attack (unexpected behavior) detected
/**@}*/

/**@}*/

#endif /* MCUXCLHASH_CONSTANTS_H_ */
