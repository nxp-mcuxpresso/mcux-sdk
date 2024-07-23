/*
 *     Copyright 2021 - 2024 NXP
 *     All rights reserved.
 *
 *     SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_els.h"
#include <mcuxClEls.h>              /* Interface to the entire nxpClEls component */
#include <mcuxCsslFlowProtection.h> /* Code flow protection */
#include "fsl_ocotp.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ELS_OTP_DTRNG_CFG_31_0_FUSE_IDX (128u)
#define ELS_DTRNG_CFG_SIZE_IN_WORD      (21)
#define ELS_DTRNG_CFG_SIZE_IN_BYTE      (ELS_DTRNG_CFG_SIZE_IN_WORD * 4)

#define IS_OCOTP_CLK_ENABLED() (bool)((CLKCTL0->PSCCTL1 & CLKCTL0_PSCCTL1_OTP_MASK) >> CLKCTL0_PSCCTL1_OTP_SHIFT)

typedef struct els_dtrng_cfg
{
    uint8_t configData[84];
} els_dtrng_cfg_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t ELS_PRNG_KickOff(void);
static status_t ELS_check_key(mcuxClEls_KeyIndex_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp);
static status_t get_dtrng_config_data(els_dtrng_cfg_t *dtrngConfig);
static status_t els_dtrng_cfg_load(void);
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
status_t ELS_PowerDownWakeupInit(ELS_Type *base)
{
    status_t status = kStatus_InvalidArgument;

    /* De-assert reset */
    RESET_ClearPeripheralReset(kELS_RST_SHIFT_RSTn);

    /* Enable ELS clock */
    CLOCK_EnableClock(kCLOCK_Els);

    /* Enable ElsApB clock */
    CLOCK_EnableClock(kCLOCK_ElsApb);

    /* Enable ELS and related clocks */
    /* Initialize ELS */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Enable_Async());

    /* mcuxClEls_Enable_Async is a flow-protected function: Check the protection token and the return value */
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Enable_Async) != token) || (MCUXCLELS_STATUS_OK_WAIT != result))
    {
        status = kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Wait for the mcuxClEls_Enable_Async operation to complete. */
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

    /* mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return value */
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        status = kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    /* Reload DTRNG configuration from OTP-Fuses */
    if (status != kStatus_Fail)
    {
        /* Load DTRNG configs*/
        status = els_dtrng_cfg_load();
    }

    if (status == kStatus_Success)
    {
        /* Kick-off ELS PRNG */
        status = ELS_PRNG_KickOff();
    }

    return status;
}

static status_t ELS_check_key(mcuxClEls_KeyIndex_t keyIdx, mcuxClEls_KeyProp_t *pKeyProp)
{
    status_t status = kStatus_Success;
    /* Check if ELS required keys are available in ELS keystore, get the key properties from the ELS*/
    MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_GetKeyProperties(keyIdx, pKeyProp));

    /* mcuxClCss_GetKeyProperties is a flow-protected function: Check the protection token and the return value */
    if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_GetKeyProperties) != token) || (MCUXCLELS_STATUS_OK != result))
    {
        status = kStatus_Fail;
    }
    MCUX_CSSL_FP_FUNCTION_CALL_END();

    return status;
}

static status_t ELS_PRNG_KickOff(void)
{
    mcuxClEls_KeyProp_t key_properties;
    status_t status             = kStatus_InvalidArgument;
    mcuxClEls_KeyIndex_t keyIdx = 0;

    /* Check if PRNG already ready */
    if ((ELS->ELS_STATUS & ELS_ELS_STATUS_PRNG_RDY_MASK) == 0u)
    {
        /* Get free ELS key slot */
        for (keyIdx = 0; keyIdx < MCUXCLELS_KEY_SLOTS; keyIdx++)
        {
            /* find a free key slot in ELS keystore */
            status = ELS_check_key(keyIdx, &key_properties);
            if (status != kStatus_Success)
            {
                status = kStatus_SlotUnavailable;
                break;
            }
            /* Found free key slot */
            if (key_properties.bits.kactv == 0u)
            {
                break;
            }
        }

        /* Free key slot found */
        if (status == kStatus_Success && keyIdx < MCUXCLELS_KEY_SLOTS)
        {
            /* delete empty temp keyslot; */
            /* Even if KDELETE is requested to delete an inactive key, the els entropy level will be raised to low and
             * the PRNG will go ready, */
            MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result0, token0, mcuxClEls_KeyDelete_Async(keyIdx));
            if ((token0 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_KeyDelete_Async)) ||
                (result0 != MCUXCLELS_STATUS_OK_WAIT))
            {
                status = kStatus_Fail;
            }
            else
            {
                /* mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return
                 * value */
                MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(result1, token1,
                                                     mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));
                if ((token1 != MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation)) ||
                    (result1 != MCUXCLELS_STATUS_OK))
                {
                    status = kStatus_Fail;
                }
                else
                {
                    status = kStatus_Success;
                }
            }
        }
        else
        {
            status = kStatus_SlotUnavailable;
        }
    }
    else
    {
        status = kStatus_Success;
    }
    return status;
}

static status_t get_dtrng_config_data(els_dtrng_cfg_t *dtrngConfig)
{
    assert(dtrngConfig);
    status_t status;
    bool ocotp_init_status = IS_OCOTP_CLK_ENABLED();

    if (ocotp_init_status == false)
    {
        /* Init OCOTP*/
        status = OCOTP_OtpInit();
    }
    else
    {
        status = kStatus_Success;
    }

    /* Read the DTRNG configs from otpfuses*/
    if (status == kStatus_Success)
    {
        uint32_t fuseIdxStart = ELS_OTP_DTRNG_CFG_31_0_FUSE_IDX;
        for (int i = 0; i < (ELS_DTRNG_CFG_SIZE_IN_BYTE / 4); i++)
        {
            status = OCOTP_OtpFuseRead(fuseIdxStart, (uint32_t *)(&dtrngConfig->configData[4 * i]));
            assert(status == kStatus_Success);
            ++fuseIdxStart;
        }

        /* if ocotp "was"  initialized before, skip deinit*/
        if (ocotp_init_status == false)
        {
            /* De-init OCOTP*/
            status = OCOTP_OtpDeinit();
            assert(status == kStatus_Success);
        }
    }

    return status;
}

static status_t els_dtrng_cfg_load(void)
{
    status_t status;
    els_dtrng_cfg_t dtrng_cfgs;

    /* Read the dtrng configs from otp*/
    status = get_dtrng_config_data(&dtrng_cfgs);

    if (status == kStatus_Success)
    {
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_Rng_Dtrng_ConfigLoad_Async(dtrng_cfgs.configData));

        /* mcuxClEls_Rng_Dtrng_ConfigLoad_Async is a flow-protected function: Check the protection token and the return
         * value */
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_Rng_Dtrng_ConfigLoad_Async) != token) ||
            (MCUXCLELS_STATUS_OK_WAIT != result))
        {
            status = kStatus_Fail;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();

        /* Wait for the mcuxClEls_Rng_Dtrng_ConfigLoad_Async operation to complete. */
        MCUX_CSSL_FP_FUNCTION_CALL_BEGIN(result, token, mcuxClEls_WaitForOperation(MCUXCLELS_ERROR_FLAGS_CLEAR));

        /* mcuxClCss_WaitForOperation is a flow-protected function: Check the protection token and the return value */
        if ((MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClEls_WaitForOperation) != token) || (MCUXCLELS_STATUS_OK != result))
        {
            status = kStatus_Fail;
        }
        MCUX_CSSL_FP_FUNCTION_CALL_END();
    }
    return status;
}
