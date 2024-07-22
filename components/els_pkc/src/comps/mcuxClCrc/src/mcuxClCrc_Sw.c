/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

#include <mcuxClCore_Platform.h>
#include <mcuxClCrc.h>
#include <internal/mcuxClCrc_Internal_Functions.h>
#include <internal/mcuxClCrc_Internal_Constants.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslDataIntegrity.h>
#include <mcuxClCore_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCrc_Internal_updateCRC16)
MCUX_CSSL_FP_PROTECTED_TYPE(uint16_t) mcuxClCrc_Internal_updateCRC16(const uint8_t *pBytes, uint32_t length, uint16_t seed16)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCrc_Internal_updateCRC16);
    uint16_t crc = seed16;

    for (uint32_t byteIndex = 0U; byteIndex < length; byteIndex++)
    {
        crc ^= ((uint16_t) pBytes[byteIndex] << 8u);
        for (uint32_t bitIndex = 0u; bitIndex < 8u; bitIndex++)
        {
            if (0u != (crc & 0x8000u))
            {
                crc = (uint16_t) ((((uint32_t) crc << 1u) ^ MCUXCLCRC_DEFAULT_POLY_16) & (uint32_t) 0xFFFFu);
            }
            else
            {
                crc <<= 1u;
            }
        }
    }

    /* Do FA protection, only for compatibility with HW-based implementation */
    MCUX_CSSL_DI_RECORD(identifier, (uint32_t)pBytes + length);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCrc_Internal_updateCRC16, crc);
}

#ifdef MCUXCL_FEATURE_CRC_CRC32
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCrc_Internal_updateCRC32)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClCrc_Internal_updateCRC32(const uint8_t *pBytes, uint32_t length, uint32_t seed32)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCrc_Internal_updateCRC32);

    uint32_t crc = seed32;

    for (uint32_t byteIndex = 0u; byteIndex < length; byteIndex++)
    {
        crc ^= ((uint32_t) pBytes[byteIndex] << 24u);
        for (uint32_t bitIndex = 0u; bitIndex < 8u; bitIndex++)
        {
            if (0u != (crc & 0x80000000u))
            {
                crc = (crc << 1u) ^ MCUXCLCRC_DEFAULT_POLY_32;
            }
            else
            {
                crc <<= 1u;
            }
        }
    }
          
    /* Do FA protection, only for compatibility with HW-based implementation */
    MCUX_CSSL_DI_RECORD(identifier, (uint32_t)pBytes + length);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCrc_Internal_updateCRC32, crc);
}
#endif /* MCUXCL_FEATURE_CRC_CRC32 */
