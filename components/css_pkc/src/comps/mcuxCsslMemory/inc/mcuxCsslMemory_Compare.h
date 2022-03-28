/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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
 * @file  mcuxCsslMemory_Compare.h
 * @brief Include file for constant time memory compare function
 */

#ifndef MCUXCSSLMEMORY_COMPARE_H
#define MCUXCSSLMEMORY_COMPARE_H

#include <stdint.h>
#include <stdlib.h>
#include <mcuxCsslParamIntegrity.h>
#include <mcuxCsslFlowProtection.h>

/**
 * @defgroup mcuxCsslMemory_Compare mcuxCssl Memory Compare
 * @brief Control Flow Protected Memory Compare Function
 *
 * @ingroup mcuxCsslMemory
 * @{
 */

/**
 * @defgroup mcuxCsslMemory_Compare_Macros mcuxCsslMemory_Compare Macro Definitions
 * @brief mcuxCsslMemory_Compare Macro Definitions
 *
 * @ingroup mcuxCsslMemory_Compare
 * @{
 */

#define MCUXCSSLMEMORY_COMPARE_EQUAL (0xE1E1E1E1u) ///< The two contents are equal

#define MCUXCSSLMEMORY_COMPARE_NOT_EQUAL (0x1E1E1E1Eu) ///< The two contents are not equal

#define MCUXCSSLMEMORY_COMPARE_INVALID_PARAMETER (0x69696969u) ///< A parameter was invalid

#define MCUXCSSLMEMORY_COMPARE_FAULT (0x96969696u) ///< A fault occurred in the execution of mcuxCsslMemory_Compare

/**
 * @}
 */

/**
 * @defgroup mcuxCsslMemory_Compare_Types mcuxCsslMemory_Compare Type Definitions
 * @brief mcuxCsslMemory_Compare Type Definitions
 *
 * @ingroup mcuxCsslMemory_Compare
 * @{
 */

typedef uint64_t mcuxCsslMemory_CompareResult_t; ///< return type for CSSL Memory compare

/**
 * @}
 */

/**
 * @defgroup mcuxCsslMemory_Compare_Functions mcuxCsslMemory_Compare Function Definitions
 * @brief mcuxCsslMemory_Compare Function Definitions
 *
 * @ingroup mcuxCsslMemory_Compare
 * @{
 */

/**
 * @brief Compares the two memory regions @p lhs and @p rhs
 * 
 * The implementation is secure in the following aspects:
 * 
 * * Constant execution time: The execution sequence of the code is always identical for equal @p cnt parameters,
 *     i.e. no branches are performed based on the data in @p lhs or @p rhs.
 * * Parameter integrity protection: An incorrect parameter checksum makes the function return immediately.
 * * Code flow protection: The function call is protected. Additionally, the result depends on all steps of the calculation.
 * 
 * @param chk The parameter checksum, generated with #mcuxCsslParamIntegrity_Protect.
 * @param lhs The left-hand side data to compare. Must not be NULL.
 * @param rhs The right-hand side data to compare. Must not be NULL.
 * @param cnt The number of bytes to compare. Must be different from zero.
 * @return A status code encapsulated in a flow-protection type.
 * @retval #MCUXCSSLMEMORY_COMPARE_EQUAL If the contents of @p lhs and @p rhs are equal.
 * @retval #MCUXCSSLMEMORY_COMPARE_NOT_EQUAL If the contents of @p lhs and @p rhs are not equal.
 * @retval #MCUXCSSLMEMORY_COMPARE_INVALID_PARAMETER If one of the parameters was invalid (i.e. @p lhs or @p rhs was NULL or @p cnt was zero).
 * @retval #MCUXCSSLMEMORY_COMPARE_FAULT If a fault was detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxCsslMemory_Compare)
mcuxCsslMemory_CompareResult_t mcuxCsslMemory_Compare
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void const * lhs,
    void const * rhs,
    size_t cnt
);

/**
 * @}
 */

/**
 * @}
 */

#endif
