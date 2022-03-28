/*
 *     Copyright 2021 MCUX
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_css_pkc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TEMPORARY_KEY_SLOT_256 18u
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t CSS_PRNG_KickOff(void);
static status_t CSS_check_key(uint8_t keyIdx, mcuxClCss_KeyProp_t *pKeyProp);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief CSS Init after power down.
 *
 * This function enable all CSS related clocks, enable CSS and start CSS PRNG.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using CSS after wake-up.
 *
 * param base CSS peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t CSS_PowerDownWakeupInit(CSS_Type *base)
{
    status_t status = kStatus_Fail;

    /* Enable all CSS related clocks */
    ANACTRL->FRO192M_CTRL |= (ANACTRL_FRO192M_CTRL_ENA_96MHZCLK_MASK | ANACTRL_FRO192M_CTRL_ENA_12MHZCLK_MASK);
    SYSCON->CSS_CLK_CTRL_SET =
        (SYSCON_CSS_CLK_CTRL_SET_GDET_REFCLK_EN_SET_MASK | SYSCON_CSS_CLK_CTRL_SET_DTRNG_REFCLK_EN_SET_MASK);

    /* De-assert reset */
    RESET_ClearPeripheralReset(kCSS_RST_SHIFT_RSTn);

    /* Enable CSS clock */
    CLOCK_EnableClock(kCLOCK_Css);

    /* Enable CSS */
    mcuxClCss_Enable_Async();
    /* Wait until CSS is enabled */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation) != token) && (MCUXCLCSS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Kick-off CSS PRNG */
    status = CSS_PRNG_KickOff();
    if (status != kStatus_Success)
    {
        return status;
    }

    return kStatus_Success;
}

/*!
 * brief PKC Init after power down.
 *
 * This function enables RAM interleave, clocks, zeroize the PKC RAM and reset PKC peripheral.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using PKC after wake-up.
 *
 * param base PKC peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_PowerDownWakeupInit(PKC_Type *base)
{
    /* set PKC RAM to interleave mode */
    SYSCON->RAM_INTERLEAVE = SYSCON_RAM_INTERLEAVE_INTERLEAVE_MASK;
    /* Reset PKC */
    RESET_PeripheralReset(kPKC_RST_SHIFT_RSTn);
    /* enable PKC clock */
    CLOCK_EnableClock(kCLOCK_Pkc);

    /* Zeroize the PKC RAM */
    for (int i = 0; i < PKC_RAM_SIZE / sizeof(uint32_t); i++)
    {
        ((uint32_t *)PKC_RAM_ADDR)[i] = 0x0;
    }

    return kStatus_Success;
}

/*!
 * brief PKC Init after power down.
 *
 * This function enables RAM interleave, clocks and reset PKC peripheral.
 *
 * param base PKC peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t PKC_InitNoZeroize(PKC_Type *base)
{
    /* set PKC RAM to interleave mode */
    SYSCON->RAM_INTERLEAVE = SYSCON_RAM_INTERLEAVE_INTERLEAVE_MASK;
    /* Reset PKC */
    RESET_PeripheralReset(kPKC_RST_SHIFT_RSTn);
    /* enable PKC clock */
    CLOCK_EnableClock(kCLOCK_Pkc);

    return kStatus_Success;
}

static status_t CSS_check_key(uint8_t keyIdx, mcuxClCss_KeyProp_t *pKeyProp)
{
    /* Check if CSS required keys are available in CSS keystore */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                    mcuxClCss_GetKeyProperties(keyIdx, pKeyProp)); // Get key propertis from the CSS.
    // mcuxClCss_GetKeyProperties is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_GetKeyProperties) != token) || (MCUXCLCSS_STATUS_OK != result))
        return kStatus_Fail;
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return kStatus_Success;
}

static status_t CSS_PRNG_KickOff(void)
{
    mcuxClCss_KeyProp_t key_properties;
    status_t status = kStatus_Fail;

    /* Check if PRNG already ready */
    if((CSS->CSS_STATUS & CSS_CSS_STATUS_prng_rdy_MASK) == 0u)
    {
        /* Check if key slot 18 is available in CSS keystore */
        /* Note if you are using slot 18 in your application, please change TEMPORARY_KEY_SLOT_256 to any unused slot */
        status = CSS_check_key(TEMPORARY_KEY_SLOT_256, &key_properties);
        if (status != kStatus_Success || key_properties.bits.kactv == 1u)
        {
            return kStatus_SlotUnavailable;
        }
    
        /* delete empty temp keyslot; */
        /* Even if KDELETE is requested to delete an inactive key, the css entropy level will be raised to low and the PRNG
         * will go ready, */
        MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result0, token0, mcuxClCss_KeyDelete_Async(TEMPORARY_KEY_SLOT_256));
        if ((token0 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_KeyDelete_Async)) || (result0 != MCUXCLCSS_STATUS_OK_WAIT))
        {
            return kStatus_Fail;
        }

        MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result1, token1, mcuxClCss_WaitForOperation(MCUXCLCSS_ERROR_FLAGS_CLEAR));
        if ((token1 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClCss_WaitForOperation)) || (result1 != MCUXCLCSS_STATUS_OK))
        {
            return kStatus_Fail;
        }
    }

    return kStatus_Success;
}
