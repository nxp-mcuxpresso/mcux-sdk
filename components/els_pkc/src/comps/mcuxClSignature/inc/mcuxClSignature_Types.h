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

#ifndef MCUXCLSIGNATURE_TYPES_H_
#define MCUXCLSIGNATURE_TYPES_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClCore_Platform.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup mcuxClAPI MCUX CL -- API
 *
 * \addtogroup mcuxClSignature Signature API
 * \brief Signature operations.
 * \ingroup mcuxClAPI
 */

/**
 * \defgroup clSignatureTypes Signature type definitions
 * \brief Types used by the Signature operations.
 * \ingroup mcuxClSignature
 * @{
 */

/**
 * \brief Signature mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Signature interfaces need
 * to know about a particular Signature mode/algorithm.
 */
struct mcuxClSignature_ModeDescriptor;

/**
 * \brief Signature mode/algorithm descriptor type
 *
 * This type captures all the information that the Signature interfaces need
 * to know about a particular Signature mode/algorithm.
 */
typedef struct mcuxClSignature_ModeDescriptor mcuxClSignature_ModeDescriptor_t;

/**
 * \brief Signature mode/algorithm type
 *
 * This type is used to refer to a Signature mode/algorithm.
 */
typedef const mcuxClSignature_ModeDescriptor_t * const mcuxClSignature_Mode_t;

/**
 * \brief Signature selftest mode/algorithm descriptor structure
 *
 * This structure captures all the information that the Signature selftest interfaces need
 * to know about a particular Signature selftest mode/algorithm.
 */
struct mcuxClSignature_TestDescriptor;

/**
 * \brief Signature selftest mode/algorithm descriptor type
 *
 * This type captures all the information that the Signature selftest interfaces need
 * to know about a particular Signature selftest mode/algorithm.
 */
typedef struct mcuxClSignature_TestDescriptor mcuxClSignature_TestDescriptor_t;

/**
 * \brief Signature selftest mode/algorithm type
 *
 * This type is used to refer to a Signature selftest mode/algorithm.
 */
typedef const mcuxClSignature_TestDescriptor_t * const mcuxClSignature_Test_t;

/**
 * \brief Signature context structure
 *
 * This structure is used in the multi-part interfaces to store the
 * information about the current operation and the relevant internal state.
 */
struct mcuxClSignature_Context;

/**
 * \brief Signature context type
 *
 * This type is used in the multi-part interfaces to store the information
 * about the current operation and the relevant internal state.
 */
typedef struct mcuxClSignature_Context mcuxClSignature_Context_t;

/**
 * \brief Signature status code
 *
 * This type provides information about the status of the Signature operation
 * that has been performed.
 */
typedef uint32_t mcuxClSignature_Status_t;

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSIGNATURE_TYPES_H_ */
