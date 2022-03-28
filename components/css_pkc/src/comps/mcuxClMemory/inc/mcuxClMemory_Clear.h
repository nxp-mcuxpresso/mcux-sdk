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

/** @file  mcuxClMemory_Clear.h
 *  @brief Memory header for clear functions.
 * This header exposes functions that enable using memory clear function.
 */


/**
 * @defgroup mcuxClMemory_Clear mcuxClMemory_Clear
 * @brief This function clears a memory region.
 * @ingroup mcuxClMemory
 * @{
 */


#ifndef MCUXCLMEMORY_CLEAR_H_
#define MCUXCLMEMORY_CLEAR_H_


/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * Overwrites a memory buffer with null bytes.
 * 
 * @param[out]  dst     Pointer to the buffer to be cleared.
 * @param[in]   len     size (in bytes) to be cleared.
 * @param[in]   buflen  buffer size (if buflen < len, only buflen bytes are cleared).
 *
 * @return A flow-protected value (see @ref mcuxCsslFlowProtection), indicating the number of bytes not copied (nonzero if the destination buffer is too small)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMemory_clear)
mcuxClMemory_Status_Protected_t mcuxClMemory_clear (uint8_t *dst, size_t len, size_t buflen);


/**
 * @}
 */

#endif /* MCUXCLMEMORY_CLEAR_H_ */

/**
 * @}
 */
