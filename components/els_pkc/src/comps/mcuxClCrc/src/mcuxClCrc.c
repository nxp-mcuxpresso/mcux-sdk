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

#include <mcuxClCore_Platform.h>
#include <mcuxClCrc.h>
#include <internal/mcuxClCrc_Internal_Functions.h>
#include <internal/mcuxClCrc_Internal_Constants.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslDataIntegrity.h>
#include <mcuxClCore_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCrc_computeCRC16)
MCUX_CSSL_FP_PROTECTED_TYPE(uint16_t) mcuxClCrc_computeCRC16(const uint8_t *pBytes, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCrc_computeCRC16);

    MCUX_CSSL_DI_EXPUNGE(mcuxClCrc_Internal_updateCRC16_pBytes, (uint32_t)pBytes + length);
    MCUX_CSSL_FP_FUNCTION_CALL(crcRet, mcuxClCrc_Internal_updateCRC16(pBytes, length, MCUXCLCRC_DEFAULT_SEED_16));
    uint16_t crcResult = (uint16_t)crcRet ^ MCUXCLCRC_DEFAULT_CRC_OUT_MASK_16;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCrc_computeCRC16, crcResult, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCrc_Internal_updateCRC16));
}

#ifdef MCUXCL_FEATURE_CRC_CRC32
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCrc_computeCRC32)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClCrc_computeCRC32(const uint8_t *pBytes, uint32_t length)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCrc_computeCRC32);

    MCUX_CSSL_DI_EXPUNGE(mcuxClCrc_Internal_updateCRC32_pBytes, (uint32_t)pBytes + length);
    MCUX_CSSL_FP_FUNCTION_CALL(crcRet, mcuxClCrc_Internal_updateCRC32(pBytes, length, MCUXCLCRC_DEFAULT_SEED_32));
    uint32_t crcResult = (uint32_t)crcRet ^ MCUXCLCRC_DEFAULT_CRC_OUT_MASK_32;

    /* byte reverse */
    uint32_t swapData = ((crcResult << 24) & 0xFF000000u)
                    | ((crcResult << 8)  & 0x00FF0000u)
                    | ((crcResult >> 8)  & 0x0000FF00u)
                    | ((crcResult >> 24) & 0x000000FFu);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCrc_computeCRC32, swapData, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCrc_Internal_updateCRC32));
}
#endif /* MCUXCL_FEATURE_CRC_CRC32 */
