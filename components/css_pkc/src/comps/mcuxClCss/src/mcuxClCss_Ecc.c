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
 * @file  mcuxClCss_Ecc.c
 * @brief CSSv2 implementation for elliptic curve cryptography.
 * This file implements the functions declared in mcuxClCss_Ecc.h.
 */

#include <mcuxClCss_Ecc.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <platform_specific_headers.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>


/**
 * @brief Command option bit field for #mcuxClCss_EccKeyExch_Async
 * Bit field to configure #mcuxClCss_EccKeyExchOption_t. See @ref MCUXCLCSS_KEYGEN_VALUE_BITS for possible options.
 */
typedef union
{
    struct
    {
        uint32_t value;         ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_KEYGEN_VALUE_
    } word;                     ///< Access #mcuxClCss_EccKeyExchOption_t word-wise
    struct
    {
        uint32_t :4;            ///< RFU
        uint32_t revf :1;       ///< This field is managed internally
        uint32_t :8;            ///< RFU
        uint32_t extkey :1;     ///< This field is managed internally
        uint32_t :18;           ///< RFU
    } bits;                     ///< Access #mcuxClCss_EccKeyExchOption_t bit-wise
} mcuxClCss_EccKeyExchOption_t;

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_EccKeyGen_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccKeyGen_Async(
    mcuxClCss_EccKeyGenOption_t options,
    mcuxClCss_KeyIndex_t signingKeyIdx,
    mcuxClCss_KeyIndex_t privateKeyIdx,
    mcuxClCss_KeyProp_t generatedKeyProperties,
    uint8_t const * pRandomData,
    uint8_t * pPublicKey)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_EccKeyGen_Async);

    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_EccKeyGen_Async, (CSS_KS_CNT <= signingKeyIdx) || (CSS_KS_CNT <= privateKeyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccKeyGen_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    options.bits.revf = MCUXCLCSS_REVERSEFETCH_ENABLE;

    MCUXCLCSS_SETKEYSTOREINDEX0(privateKeyIdx);
    MCUXCLCSS_SETKEYSTOREINDEX1(signingKeyIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(generatedKeyProperties);
    MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pRandomData);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pPublicKey);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_KEYGEN, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccKeyGen_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_EccKeyExchange_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccKeyExchange_Async(
        mcuxClCss_KeyIndex_t privateKeyIdx,
        uint8_t const * pPublicKey,
        mcuxClCss_KeyIndex_t sharedSecretIdx,
        mcuxClCss_KeyProp_t sharedSecretProperties)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_EccKeyExchange_Async);

    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_EccKeyExchange_Async, (CSS_KS_CNT <= privateKeyIdx) || (CSS_KS_CNT <= sharedSecretIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccKeyExchange_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    mcuxClCss_EccKeyExchOption_t options = {0};
    options.bits.revf = MCUXCLCSS_REVERSEFETCH_ENABLE;

    MCUXCLCSS_SETKEYSTOREINDEX0(privateKeyIdx);
    MCUXCLCSS_SETCSSINPUT1_FIXEDSIZE(pPublicKey);
    MCUXCLCSS_SETKEYSTOREINDEX1(sharedSecretIdx);
    MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(sharedSecretProperties);

    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_ECKXH, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccKeyExchange_Async, MCUXCLCSS_STATUS_OK_WAIT);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_EccSign_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccSign_Async(
    mcuxClCss_EccSignOption_t options,
    mcuxClCss_KeyIndex_t keyIdx,
    uint8_t const * pInputHash,
    uint8_t const * pInputMessage,
    size_t inputMessageLength,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_EccSign_Async);

    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_EccSign_Async, (CSS_KS_CNT <= keyIdx));

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccSign_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    options.bits.revf = MCUXCLCSS_REVERSEFETCH_ENABLE;

    MCUXCLCSS_SETKEYSTOREINDEX0(keyIdx);
    MCUXCLCSS_SETCSSINPUT0((options.bits.echashchl == 0u) ? pInputHash : pInputMessage, inputMessageLength);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_ECSIGN, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccSign_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_EccVerify_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_EccVerify_Async(
    mcuxClCss_EccVerifyOption_t options,
    uint8_t const * pInputHash,
    uint8_t const * pInputMessage,
    size_t inputMessageLength,
    uint8_t const * pSignatureAndPubKey,
    uint8_t * pOutput)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_EccVerify_Async);

    /* CSS SFRs are not cached => Tell SW to wait for CSS to come back from BUSY state before modifying the SFRs */
    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccVerify_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    options.bits.revf = MCUXCLCSS_REVERSEFETCH_ENABLE;

    MCUXCLCSS_SETCSSINPUT0((options.bits.echashchl == 0u) ? pInputHash : pInputMessage, inputMessageLength);
    MCUXCLCSS_SETCSSINPUT1_FIXEDSIZE(pSignatureAndPubKey);
    MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput);
    MCUXCLCSS_STARTCOMMAND(ID_CFG_CSS_CMD_ECVFY, options.word.value, CSS_CMD_BIG_ENDIAN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_EccVerify_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

