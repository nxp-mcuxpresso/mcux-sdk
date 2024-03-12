/*--------------------------------------------------------------------------*/
/* Copyright 2021, 2023 NXP                                                 */
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
 * @file  mcuxClCrc.h
 * @brief Top-level include file for the mcuxClCrc component
 *
 * This includes headers for all of the functionality provided by the mcuxClCrc component.
 *
 * @defgroup mcuxClCrc mcuxClCrc
 * @brief CRC component
 *
 * The mcuxClCrc component implements the CRC functionality supported by CLNS.
 */

#ifndef MCUXCLCRC_H_
#define MCUXCLCRC_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClCrc_Functions mcuxClCrc_Functions
 * @brief Defines all functions of @ref mcuxClCrc
 * @ingroup mcuxClCrc
 * @{
 */

/**
 * @brief Compute a 16-bit CRC checksum
 *
 * Compute the 16-bit CRC checksum of a given byte string with the platform-specified
 * 16-bit CRC algorithm.
 *
 * @param[in]  pBytes   pointer to the byte string
 * @param[in]  length   length (in bytes) of the string
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #crcResult    16-bit CRC checksum
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCrc_computeCRC16)
MCUX_CSSL_FP_PROTECTED_TYPE(uint16_t) mcuxClCrc_computeCRC16(const uint8_t *pBytes, uint32_t length);

#ifdef MCUXCL_FEATURE_CRC_CRC32
/**
 * @brief Compute a 32-bit CRC checksum
 *
 * Compute the 32-bit CRC checksum of a given byte string with the platform-specified
 * 32-bit CRC algorithm.
 *
 * @param[in]  pBytes   pointer to the byte string
 * @param[in]  length   length (in bytes) of the string
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #crcResult    32-bit CRC checksum
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCrc_computeCRC32)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClCrc_computeCRC32(const uint8_t *pBytes, uint32_t length);
#endif /* MCUXCL_FEATURE_CRC_CRC32 */

/**
 * @}
 */ /* mcuxClCrc_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCRC_H_ */
