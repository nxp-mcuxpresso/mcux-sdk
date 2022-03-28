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

/** @file  mcuxClMemory_Set.h
 *  @brief Memory header for set function.
 * This header exposes functions that enable using memory set functions.
 */

/**
 * @defgroup mcuxClMemory_Set mcuxClMemory_Set
 * @brief This function sets all bytes in a memory region to a specified value.
 * @ingroup mcuxClMemory
 * @{
 */

#ifndef MCUXCLMEMORY_SET_H_
#define MCUXCLMEMORY_SET_H_


/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * Sets all bytes of a memory buffer to a specified value.
 * 
 * @param[out]  dst     pointer to the buffer to be set.
 * @param[in]   val     byte value to be set.
 * @param[in]   len     size (in bytes) to be set.
 * @param[in]   buflen  buffer size (if buflen < len, only buflen bytes are set).
 *
 * @return A flow-protected value (see @ref mcuxCsslFlowProtection), indicating the number of bytes not copied (nonzero if the destination buffer is too small)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMemory_set)
mcuxClMemory_Status_Protected_t mcuxClMemory_set (uint8_t *dst, uint8_t val, size_t len, size_t buflen);

#endif /* MCUXCLMEMORY_SET_H_ */

/**
 * @}
 */
