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

/** @file  mcuxClCss_Common.c
 *  @brief CSSv2 implementation for common functionality.
 * This file implements the functions declared in mcuxClCss_Common.h and adds helper functions used by other implementation headers. */

#include <stdbool.h>
#include <platform_specific_headers.h>
#include <mcuxClCss_Types.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCss.h>
#include <internal/mcuxClCss_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetHwVersion)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwVersion(
    mcuxClCss_HwVersion_t * result)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetHwVersion);
    result->word.value = IP_CSS->CSS_VERSION;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetHwVersion, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetHwConfig)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwConfig(
    mcuxClCss_HwConfig_t * result)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetHwConfig);
    result->word.value = IP_CSS->CSS_CONFIG;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetHwConfig, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetHwState)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetHwState(
    mcuxClCss_HwState_t * result)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetHwState);
    result->word.value = IP_CSS->CSS_STATUS;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetHwState, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Enable_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Enable_Async(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Enable_Async);
    IP_CSS->CSS_CTRL_b.CSS_EN = 1U;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Enable_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Disable)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Disable(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Disable);
    IP_CSS->CSS_CTRL_b.CSS_EN = 0U;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Disable, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetErrorCode)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetErrorCode(
    mcuxClCss_ErrorHandling_t errorHandling)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetErrorCode);

    mcuxClCss_Status_t result = MCUXCLCSS_STATUS_SW_FAULT;
    if (1U == IP_CSS->CSS_STATUS_b.CSS_ERR)
    {
        if (1U == IP_CSS->CSS_ERR_STATUS_b.FLT_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_FAULT;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.ITG_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_INTEGRITY;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.OPN_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_OPERATIONAL;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.ALG_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_ALGORITHM;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.BUS_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_BUS;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.PRNG_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_PRNG;
        }
        else if (1U == IP_CSS->CSS_ERR_STATUS_b.DTRNG_ERR)
        {
            result = MCUXCLCSS_STATUS_HW_DTRNG;
        }
        else
        {
            result = MCUXCLCSS_STATUS_SW_FAULT;
        }
    }
    else
    {
        result = MCUXCLCSS_STATUS_OK;
    }
    
    if (MCUXCLCSS_ERROR_FLAGS_CLEAR == errorHandling){
        (void) mcuxClCss_ResetErrorFlags();  /* always returns MCUXCLCSS_STATUS_OK. */
    }
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetErrorCode, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetErrorLevel)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetErrorLevel(
    mcuxClCss_ErrorHandling_t errorHandling,
    uint32_t *errorLevel)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetErrorLevel);

    *errorLevel = IP_CSS->CSS_ERR_STATUS_b.ERR_LVL;

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_GetErrorCode(errorHandling));

    /* Exit function with expectation: mcuxClCss_GetErrorCode was called unconditionally */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetErrorLevel, result,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetErrorCode));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_WaitForOperation)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_WaitForOperation(
    mcuxClCss_ErrorHandling_t errorHandling)
{
    /* Enter flow-protected function with expectation: mcuxClCss_GetErrorCode will be called (unconditionally) */
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_WaitForOperation,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetErrorCode));

    while (MCUXCLCSS_ISBUSY)
    {
        // Do nothing
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_GetErrorCode(errorHandling));
    
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_WaitForOperation, result);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_LimitedWaitForOperation)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_LimitedWaitForOperation(
    uint32_t counterLimit,
    mcuxClCss_ErrorHandling_t errorHandling)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_LimitedWaitForOperation);

    bool counterExpired = true;
    while (0U != counterLimit)
    {
        if (!MCUXCLCSS_ISBUSY)
        {
            counterExpired = false;
            break;
        }
        counterLimit--;
    }
    
    if (true == counterExpired)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_LimitedWaitForOperation, MCUXCLCSS_STATUS_SW_COUNTER_EXPIRED);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(result, mcuxClCss_GetErrorCode(errorHandling));

    /* Exit function with expectation: mcuxClCss_GetErrorCode was called */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_LimitedWaitForOperation, result,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetErrorCode));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_ResetErrorFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ResetErrorFlags(
    void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_ResetErrorFlags);
    IP_CSS->CSS_ERR_STATUS_CLR = (uint32_t) MCUXCLCSS_ERROR_FLAGS_CLEAR;
    // Poll error bit to be sure that error bits has been cleared. Required by HW spec.
    while (1U == IP_CSS->CSS_STATUS_b.CSS_ERR)
    {
        // Do nothing
    }
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ResetErrorFlags, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_Reset_Async)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_Reset_Async(
    mcuxClCss_ResetOption_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_Reset_Async);
    if (MCUXCLCSS_ISBUSY && (MCUXCLCSS_RESET_DO_NOT_CANCEL == options))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Reset_Async, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }
    
    IP_CSS->CSS_CTRL_b.CSS_RESET = 1U;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_Reset_Async, MCUXCLCSS_STATUS_OK_WAIT);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_SetIntEnableFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetIntEnableFlags(
    mcuxClCss_InterruptOptionEn_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_SetIntEnableFlags);
    IP_CSS->CSS_INT_ENABLE = options.word.value;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_SetIntEnableFlags, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetIntEnableFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetIntEnableFlags(
    mcuxClCss_InterruptOptionEn_t * result)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetIntEnableFlags);
    result->word.value = IP_CSS->CSS_INT_ENABLE_b.INT_EN;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetIntEnableFlags, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_ResetIntFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_ResetIntFlags(
    mcuxClCss_InterruptOptionRst_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_ResetIntFlags);
    IP_CSS->CSS_INT_STATUS_CLR = options.word.value;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_ResetIntFlags, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_SetIntFlags)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetIntFlags(
    mcuxClCss_InterruptOptionSet_t options)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_SetIntFlags);
    IP_CSS->CSS_INT_STATUS_SET = options.word.value;
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_SetIntFlags, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_SetRandomStartDelay)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_SetRandomStartDelay(
    uint32_t delay)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_SetRandomStartDelay);
    MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(mcuxClCss_SetRandomStartDelay, 1024u < delay);

    if (MCUXCLCSS_ISBUSY)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_SetRandomStartDelay, MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT);
    }

    IP_CSS->CSS_CFG_b.ADCTRL = delay;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_SetRandomStartDelay, MCUXCLCSS_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClCss_GetRandomStartDelay)
MCUXCLCSS_API mcuxClCss_Status_Protected_t mcuxClCss_GetRandomStartDelay(
    uint32_t *delay)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClCss_GetRandomStartDelay);

    * delay = IP_CSS->CSS_CFG_b.ADCTRL;

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClCss_GetRandomStartDelay, MCUXCLCSS_STATUS_OK);
}




