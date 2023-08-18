/*--------------------------------------------------------------------------*/
/* Copyright 2021-2022 NXP                                                  */
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

/** @file  mcuxClEls_Crc.c
 *  @brief ELS implementation for CRC functionality.
 *  This file implements the CRC related functions declared in mcuxClEls_Common.h
 */

#include <platform_specific_headers.h>
#include <ip_css_design_configuration.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClEls.h>
#include <internal/mcuxClEls_Internal.h>

#ifdef MCUXCL_FEATURE_ELS_CMD_CRC
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_ConfigureCommandCRC)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_ConfigureCommandCRC(
    mcuxClEls_CommandCrcConfig_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_ConfigureCommandCRC);
    MCUXCLELS_SFR_WRITE(ELS_CMDCRC_CTRL, options.word.value);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_ConfigureCommandCRC, MCUXCLELS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_GetCommandCRC)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_GetCommandCRC(
    uint32_t* commandCrc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_GetCommandCRC);

    if(NULL == commandCrc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_GetCommandCRC, MCUXCLELS_STATUS_SW_INVALID_PARAM);
    }

    *commandCrc = MCUXCLELS_SFR_READ(ELS_CMDCRC);
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_GetCommandCRC, MCUXCLELS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_VerifyVsRefCRC)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_VerifyVsRefCRC(
    uint32_t refCrc)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_VerifyVsRefCRC, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetCommandCRC));

    /* Get the hardware CRC from ELS - no return value check as function always returns OK */
    uint32_t hwCrc = 0u;
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClEls_GetCommandCRC(&hwCrc));

    /* Compare against given reference CRC */
    if(hwCrc != refCrc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_VerifyVsRefCRC, MCUXCLELS_STATUS_SW_FAULT);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_VerifyVsRefCRC, MCUXCLELS_STATUS_OK);
}

static const uint32_t crc32_LUT[32] =
{
    /* 0x00, 0x01, 0x02, ..., 0x0F */
    0x00000000u, 0x04C11DB7u, 0x09823B6Eu, 0x0D4326D9u, 0x130476DCu, 0x17C56B6Bu, 0x1A864DB2u, 0x1E475005u,
    0x2608EDB8u, 0x22C9F00Fu, 0x2F8AD6D6u, 0x2B4BCB61u, 0x350C9B64u, 0x31CD86D3u, 0x3C8EA00Au, 0x384FBDBDu,
    /* 0x00, 0x10, 0x20, ..., 0xF0 */
    0x00000000u, 0x4C11DB70u, 0x9823B6E0u, 0xD4326D90u, 0x34867077u, 0x7897AB07u, 0xACA5C697u, 0xE0B41DE7u,
    0x690CE0EEu, 0x251D3B9Eu, 0xF12F560Eu, 0xBD3E8D7Eu, 0x5D8A9099u, 0x119B4BE9u, 0xC5A92679u, 0x89B8FD09u
};

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClEls_UpdateRefCRC)
MCUXCLELS_API MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEls_Status_t) mcuxClEls_UpdateRefCRC(
    uint8_t   command,
    uint32_t  options,
    uint32_t* refCrc
    )
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClEls_UpdateRefCRC);

    if(NULL == refCrc)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_UpdateRefCRC, MCUXCLELS_STATUS_SW_INVALID_PARAM);
    }

    /* Construct datain */
    // DATAIN = {ELS_CMD[4:0], options[31:0], 3'h0}
    uint8_t pDatain[5];
    pDatain[4] =  command << 3;
    pDatain[4] |= (uint8_t)(options >> 29);
    pDatain[3] =  (uint8_t)(options >> 21);
    pDatain[2] =  (uint8_t)(options >> 13);
    pDatain[1] =  (uint8_t)(options >> 5);
    pDatain[0] =  ((uint8_t)(options & 0x1Fu)) << 3;

    /* byte-wise CRC32 with nibble-wise LUT */
    uint8_t lookupIndex;
    uint32_t lookupValueLowBits, lookupValueHighBits;
    for(uint32_t byte = 1u; byte <= 5u; byte++)
    {
        lookupIndex = pDatain[5u - byte] ^ ((uint8_t)(*refCrc >> 24));
        lookupValueLowBits = crc32_LUT[(lookupIndex & 0x0Fu)];
        lookupValueHighBits = crc32_LUT[(lookupIndex >> 4) + 16u];
        *refCrc = lookupValueHighBits ^ lookupValueLowBits ^ (*refCrc << 8);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClEls_UpdateRefCRC, MCUXCLELS_STATUS_OK);
}


#endif /* MCUXCL_FEATURE_ELS_CMD_CRC */
