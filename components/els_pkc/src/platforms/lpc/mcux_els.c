/*
 *     Copyright 2021 - 2023 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_els.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief NMPA related Registers
 */
#define FLASH_NMPA_DTRNG_CFG_START   (0x3FD00U)
#define FLASH_NMPA_DTRNG_CFG_END     (0x3FD50U)
#define FLASH_NMPA_DTRNG_CFG_SIZE    (21U)

#define GET_DTRNG_CFG(offset)   (*((volatile unsigned int *)(FLASH_NMPA_DTRNG_CFG_START + (4U *(offset)))))

#define FLASH_NMPA_GDET_CFG_START   (0x3FC28U)
#define FLASH_NMPA_GDET_CFG_END     (0x3FC3CU)
#define FLASH_NMPA_GDET_CFG_SIZE    (6U)

#define GET_GDET_CFG(offset)   (*((volatile unsigned int *)(FLASH_NMPA_GDET_CFG_START + (4U *(offset)))))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t ELS_PRNG_KickOff(void);
static status_t ELS_check_key(uint8_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief ELS Init after power down.
 *
 * This function enable all ELS related clocks, enable ELS and start ELS PRNG.
 * Normally all of these actions are done automatically by boot ROM, but if an application uses Power Down mode
 * this function must be called before using ELS after wake-up.
 *
 * param base ELS peripheral address.
 *
 * return kStatus_Success upon success, kStatus_Fail otherwise
 */
status_t ELS_PowerDownWakeupInit(S50_Type *base)
{
    status_t status = kStatus_Fail;
    uint32_t DtrngCfg[FLASH_NMPA_DTRNG_CFG_SIZE];
    uint32_t GdetCfg[FLASH_NMPA_GDET_CFG_SIZE];

    /* Enable GDET and DTRNG clocks */
    SYSCON->ELS_CLK_CTRL =
        SYSCON_ELS_CLK_CTRL_SET_GDET_REFCLK_EN_SET_MASK | SYSCON_ELS_CLK_CTRL_SET_DTRNG_REFCLK_EN_SET_MASK;

    /* Enable ELS clock */
    CLOCK_EnableClock(kCLOCK_Css);

    /* Enable GDET interrupt, input event to ITRC */
    ELS->ELS_INT_ENABLE |= S50_ELS_INT_ENABLE_GDET_INT_EN_MASK;

    /* Enable ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Enable_Async()); // Enable the ELS.
    // mcuxClEls_Enable_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Enable_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return kStatus_Fail ;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Enable_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Reload GDET and DTRNG  configuration from NMPA */
    /* This is normally done automatically by boot ROM */
    /* When boot ROM is not involved this must be done by SW*/ 

    /* Get Config values from Flash */
    for (size_t i = 0; i < FLASH_NMPA_DTRNG_CFG_SIZE; i++)
    {
        DtrngCfg[i] = GET_DTRNG_CFG(i);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Rng_Dtrng_ConfigLoad_Async((uint8_t *)DtrngCfg)); // Reload the DTRNG config.
    // mcuxClEls_Rng_Dtrng_ConfigLoad_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_Dtrng_ConfigLoad_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return kStatus_Fail ;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_Rng_Dtrng_ConfigLoad_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Get Config values from Flash */
    for (size_t i = 0; i < FLASH_NMPA_GDET_CFG_SIZE; i++)
    {
        GdetCfg[i] = GET_GDET_CFG(i);
    }

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GlitchDetector_LoadConfig_Async((uint8_t *)GdetCfg)); // Reload the GDET config.
    // mcuxClEls_GlitchDetector_LoadConfig_Async is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GlitchDetector_LoadConfig_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        return kStatus_Fail ;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR)); // Wait for the mcuxClEls_GlitchDetector_LoadConfig_Async operation to complete.
    // mcuxClEls_WaitForOperation is a flow-protected function: Check the protection token and the return value
    if((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();
  
    /* Kick-off ELS PRNG */
    status = ELS_PRNG_KickOff();
    if (status != kStatus_Success)
    {
        return status;
    }
        
    return kStatus_Success;
}

static status_t ELS_check_key(uint8_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp)
{
    /* Check if ELS required keys are available in ELS keystore */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token,
                                     mcuxClEls_GetKeyProperties(keyIdx, pKeyProp)); // Get key properties from the ELS.
    // mcuxClEls_GetKeyProperties is a flow-protected function: Check the protection token and the return value
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        return kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return kStatus_Success;
}

static status_t ELS_PRNG_KickOff(void)
{
    mcuxClEls_KeyProp_t key_properties;
    status_t status = kStatus_Fail;
    mcuxClEls_KeyIndex_t keyIdx = 0;

    /* Check if PRNG already ready */
    if ((ELS->ELS_STATUS & S50_ELS_STATUS_PRNG_RDY_MASK) == 0u)
    {
        /* Get free ELS key slot */
        for(keyIdx = 0; keyIdx < MCUXCLELS_KEY_SLOTS; keyIdx++)
        {
            /* find a free key slot in ELS keystore */
            status = ELS_check_key(keyIdx, &key_properties);
            if (status != kStatus_Success)
            {
                return kStatus_SlotUnavailable;
            }
            
            /* Found free key slot */
            if(key_properties.bits.kactv == 0U)
            {
                break; 
            }
        }

        /* Free key slot found */
        if(keyIdx < MCUXCLELS_KEY_SLOTS) 
        {        
            /* delete empty temp keyslot; */
            /* Even if KDELETE is requested to delete an inactive key, the els entropy level will be raised to low and the
             * PRNG will go ready, */
            MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result0, token0, mcuxClEls_KeyDelete_Async(keyIdx));
            if ((token0 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async)) ||
                (result0 != MCUXCLELS_STATUS_OK_WAIT))
            {
                return kStatus_Fail;
            }
            /* mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return value */
            MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result1, token1, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
            if ((token1 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)) || (result1 != MCUXCLELS_STATUS_OK))
            {
                return kStatus_Fail;
            }
        }
        else
        {
          return kStatus_SlotUnavailable;
        }
    }
    return kStatus_Success;
}