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

/**
 * @file  mcuxClKey_Types.h
 * @brief Type definitions for the mcuxClKey component
 */

#ifndef MCUXCLKEY_TYPES_H_
#define MCUXCLKEY_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClCore_Buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClKey_Types mcuxClKey_Types
 * @brief Defines all types of @ref mcuxClKey
 * @ingroup mcuxClKey
 * @{
 */

/**
 * @brief Type for Key component error codes.
 */
typedef uint32_t mcuxClKey_Status_t;

/**
 * @brief Type for algorithm based key id.
 */
typedef uint16_t mcuxClKey_AlgorithmId_t;

/**
 * @brief Type for algorithm based key size.
 */
typedef uint32_t mcuxClKey_Size_t;

/**
 * @brief Deprecated type for Key component error codes, returned by functions with code-flow protection.
 */
typedef MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClKey_Status_t) mcuxClKey_Status_Protected_t;

/* Forward declaration */
struct mcuxClKey_Protection;

/**
 * @brief Forward declaration for Key descriptor structure
 *
 * This structure captures all the information that the Key interfaces need
 * to know about a particular key.
 */
struct mcuxClKey_Descriptor;

/**
 * @brief Key descriptor type
 *
 * This type captures all the information that the Key interfaces need to know
 * about a particular Key.
 */
typedef struct mcuxClKey_Descriptor mcuxClKey_Descriptor_t;

/**
 * @brief Key handle type
 *
 * This type is used to refer to the opaque key descriptor.
 */
typedef mcuxClKey_Descriptor_t * const mcuxClKey_Handle_t;

/**
 * @brief Forward declaration for Key type structure
 *
 * This structure captures all the information that the Key interfaces need to
 * know about a particular Key type.
 */
struct mcuxClKey_TypeDescriptor;

/**
 * @brief Key type descriptor type
 *
 * This type captures all the information that the Key interfaces need to know
 * about a particular Key type.
 */
typedef struct mcuxClKey_TypeDescriptor mcuxClKey_TypeDescriptor_t;

/**
 * @brief Key type handle type
 *
 * This type is used to refer to a key type descriptor.
 */
typedef const mcuxClKey_TypeDescriptor_t * mcuxClKey_Type_t;

/**
 * @brief Custom key type handle type
 *
 * This type is used to refer to a custom key type descriptor.
 */
typedef mcuxClKey_TypeDescriptor_t * mcuxClKey_CustomType_t;

/**
 * @brief Key protection mechanism descriptor structure
 *
 * This structure captures all the information that the Key interfaces need to
 * know about a particular Key protection mechanism.
 */
struct mcuxClKey_ProtectionDescriptor;

/**
 * @brief Key protection mechanism descriptor type
 *
 * This type captures all the information that the Key interfaces need to know
 * about a particular Key protection mechanism.
 */
typedef struct mcuxClKey_ProtectionDescriptor mcuxClKey_ProtectionDescriptor_t;

/**
 * Key protection mechanism type
 *
 * This type is used to refer to a Key protection mechanism.
 */
typedef const mcuxClKey_ProtectionDescriptor_t * mcuxClKey_Protection_t;


/**
 * @brief Key generation descriptor structure
 *
 * This structure captures all the information that the Key interfaces need to
 * know about a particular Key generation algorithm.
 */
struct mcuxClKey_GenerationDescriptor;

/**
 * @brief Key generation descriptor type
 *
 * This type captures all the information that the Key interfaces need to know
 * about a particular Key generation algorithm.
 */
typedef struct mcuxClKey_GenerationDescriptor mcuxClKey_GenerationDescriptor_t;

/**
 * @brief Key generation type
 *
 * This type is used to refer to a Key generation algorithm.
 */
typedef const mcuxClKey_GenerationDescriptor_t * const mcuxClKey_Generation_t;




/**
 * @}
 */ /* mcuxClKey_Types */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLKEY_TYPES_H_ */
