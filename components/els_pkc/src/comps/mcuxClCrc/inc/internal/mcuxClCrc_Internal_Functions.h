/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClCrc_Internal_Functions.h
 * @brief CRC internal functions of the mcuxClCrc component
 */

#ifndef MCUXCLCRC_INTERNAL_FUNCTIONS_H_
#define MCUXCLCRC_INTERNAL_FUNCTIONS_H_

#include <mcuxClCore_Platform.h>
#include <mcuxCsslFlowProtection.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClCrc_Internal_Functions mcuxClCrc_Internal_Functions
 * @brief Driver layer of the @ref mcuxClCrc component
 * @ingroup mcuxClCrc
 * @{
 */

/**
 * @defgroup mcuxClCrc_Internal_Functions mcuxClCrc_Internal_Functions
 * @brief Defines the CRC internal functions of component @ref mcuxClCrc
 * @ingroup mcuxClCrc_Internal_Functions
 * @{
 */

/**
 * @brief Compute 16-bit CRC checksum of a given byte string with a given seed
 *        and the platform-specified 16-bit CRC polynomial
 *
 * @param[in] pBytes  pointer to the byte string
 * @param[in] length  length (in bytes) of the string
 * @param[in] seed16  16-bit seed
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #crcResult  16-bit CRC checksum  (without applying the output mask)
 *
 * Data Integrity: Record(pBytes + length)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCrc_Internal_updateCRC16)
MCUX_CSSL_FP_PROTECTED_TYPE(uint16_t)  mcuxClCrc_Internal_updateCRC16(const uint8_t *pBytes, uint32_t length, uint16_t seed16);

#ifdef MCUXCL_FEATURE_CRC_CRC32
/**
 * @brief Compute 32-bit CRC checksum of a given byte string with a given seed
 *        and the platform-specified 32-bit CRC polynomial
 *
 * @param[in] pBytes  pointer to the byte string
 * @param[in] length  length (in bytes) of the string
 * @param[in] seed16  32-bit seed
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #crcResult  32-bit CRC checksum  (without applying the output mask)
 *
 * Data Integrity: Record(pBytes + length)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClCrc_Internal_updateCRC32)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClCrc_Internal_updateCRC32(const uint8_t *pBytes, uint32_t length, uint32_t seed32);
#endif /* MCUXCL_FEATURE_CRC_CRC32 */

/**
 * @}
 */ /* mcuxClCrc_Internal_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLCRC_INTERNAL_FUNCTIONS_H_ */
