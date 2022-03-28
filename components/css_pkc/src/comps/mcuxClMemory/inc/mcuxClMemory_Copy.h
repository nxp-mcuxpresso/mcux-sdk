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

/** @file  mcuxClMemory_Copy.h
 *  @brief Memory header for copy functions.
 * This header exposes functions that enable using memory copy function.
 */

/**
 * @defgroup mcuxClMemory_Copy mcuxClMemory_Copy
 * @brief This function copies a memory region from @p src to @p dst.
 * @ingroup mcuxClMemory
 * @{
 */

#ifndef MCUXCLMEMORY_COPY_H_
#define MCUXCLMEMORY_COPY_H_

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * Copies a memory buffer to another location.
 * 
 * The two buffers must not overlap.
 * 
 * @param[out] dst     pointer to the buffer to be copied.
 * @param[in]  src     pointer to the buffer to copy.
 * @param[in]  len     size (in bytes) to be copied.
 * @param[in]  buflen  buffer size (if buflen < len, only buflen bytes are copied).
 *
 * @return A flow-protected value (see @ref mcuxCsslFlowProtection), indicating the number of bytes not copied (nonzero if the destination buffer is too small)
 */

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMemory_copy)
mcuxClMemory_Status_Protected_t mcuxClMemory_copy (uint8_t *dst, uint8_t const *src, size_t len, size_t buflen);

#endif /* MCUXCLMEMORY_COPY_H_ */

/**
 * @}
 */
