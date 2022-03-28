/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
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
 * @file  mcuxCsslMemory_Copy.h
 * @brief Include file for robust memory copy function
 */

#ifndef MCUXCSSLMEMORY_COPY_H
#define MCUXCSSLMEMORY_COPY_H

/**
 * @defgroup mcuxCsslMemory_Copy mcuxCssl Memory Copy
 * @brief Control Flow Protected Memory Copy Function
 *
 * @ingroup mcuxCsslMemory
 * @{
 */

/**
 * @defgroup mcuxCsslMemory_Copy_Macros mcuxCsslMemory_Copy Macro Definitions
 * @brief mcuxCsslMemory_Copy Macro Definitions
 *
 * @ingroup mcuxCsslMemory_Copy
 * @{
 */


#define MCUXCSSLMEMORY_COPY_SUCCESS ((mcuxCsslMemory_CopyResult_t)0xE1E1E1E1u) ///< Copied; the two buffer contents are equal

#define MCUXCSSLMEMORY_COPY_INVALID_PARAMETER ((mcuxCsslMemory_CopyResult_t)0x69696969u) ///< A parameter was invalid

#define MCUXCSSLMEMORY_COPY_FAULT ((mcuxCsslMemory_CopyResult_t)0x96969696u) ///< A fault occurred in the execution of mcuxCsslMemory_Compare

/**
 * @}
 */

/**
 * @defgroup mcuxCsslMemory_Copy_Types mcuxCsslMemory_Copy Type Definitions
 * @brief mcuxCsslMemory_Copy Type Definitions
 *
 * @ingroup mcuxCsslMemory_Copy
 * @{
 */

typedef uint64_t mcuxCsslMemory_CopyResult_t; ///< return type for CSSL Memory copy

/**
 * @}
 */

/**
 * @defgroup mcuxCsslMemory_Copy_Functions mcuxCsslMemory_Copy Function Definitions
 * @brief mcuxCsslMemory_Copy Function Definitions
 *
 * @ingroup mcuxCsslMemory_Copy
 * @{
 */

/**
 * @brief Copies @p cnt bytes of data from @p src to @p dst
 * 
 * The implementation is secure in the following aspects:
 * 
 * * Constant execution time: If @p src and @p dst have the same offset to the nearest 16-byte boundary, and if @p cnt
 *     is the same, the execution sequence of the code is always identical.
 * * Parameter integrity protection: An incorrect parameter checksum makes the function return immediately.
 * * Code flow protection: The function call is protected. Additionally, the result depends on all steps of the calculation.
 * * Buffer overflow protection: No data is written to @p dst beyond @p dst_size bytes.
 * 
 * @param[in]     chk       The parameter checksum, generated with #mcuxCsslParamIntegrity_Protect.
 * @param[in]     src       The data to be copied. Must not be NULL. Must not overlap with @p dst.
 * @param   [out] dst       The destination pointer. Must not be NULL. Must not overlap with @p src.
 * @param[in]     dst_size  The size of the destination data buffer in bytes.
 * @param[in]     cnt       The number of bytes to copy. Must be different from zero.
 * @return A status code encapsulated in a flow-protection type.
 * @retval #MCUXCSSLMEMORY_COPY_SUCCESS If the contents of @p src and @p dst are equal.
 * @retval #MCUXCSSLMEMORY_COPY_INVALID_PARAMETER If one of the parameters was invalid (i.e. @p src or @p dst was NULL or @p cnt was zero).
 * @retval #MCUXCSSLMEMORY_COPY_FAULT If a fault was detected.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxCsslMemory_Copy)
mcuxCsslMemory_CopyResult_t mcuxCsslMemory_Copy
(
    mcuxCsslParamIntegrity_Checksum_t chk,
    void const * src,
    void * dst,
    size_t dst_size,
    size_t cnt
);

/**
 * @}
 */

/**
 * @}
 */

#endif
