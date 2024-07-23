/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_s2xx_common_init.h" /* ELE Crypto port layer */

/******************************************************************************/
/*************************** Mutex ********************************************/
/******************************************************************************/
/*
 * Define global mutexes for HW accelerator
 */
mcux_mutex_t ele_hwcrypto_mutex;

/******************************************************************************/
/******************** CRYPTO_InitHardware *************************************/
/******************************************************************************/

ele_s2xx_ctx_t g_ele_ctx = {0u}; /* Global context */

uint32_t g_isCryptoHWInitialized = false;

psa_status_t ele_to_psa_status(status_t ele_status)
{
    psa_status_t status = PSA_ERROR_HARDWARE_FAILURE;
    switch (ele_status)
    {
        case kStatus_InvalidArgument:
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
        case kStatus_Success:
            status = PSA_SUCCESS;
            break;
        case kStatus_Fail:
            status = PSA_ERROR_HARDWARE_FAILURE;
            break;
        default:
            status = PSA_ERROR_HARDWARE_FAILURE;
            break;
    }

    return status;
}

static status_t ele_close_handles(void)
{
    sss_status_t status = kStatus_SSS_Fail;

    do
    {
        /****************** Close RNG Context **********************/
        status = sss_sscp_rng_free(&g_ele_ctx.rngctx);
        if (status != kStatus_SSS_Success)
        {
            PRINTF("sss_sscp_rng_free failed\n");
            break;
        }

        /****************** Close Key Store  ***********************************/
        status = sss_sscp_key_store_free(&g_ele_ctx.keyStore);
        if (status != kStatus_SSS_Success)
        {
            PRINTF("sss_sscp_key_store_free failed\n");
            break;
        }

        /****************** Close EdgeLock session ******************/
        status = sss_sscp_close_session(&g_ele_ctx.sssSession);
        if (status != kStatus_SSS_Success)
        {
            PRINTF("sss_sscp_close_session failed\n");
            break;
        }

        /****************** Close SSCP context ******************/
        sscp_mu_deinit(&g_ele_ctx.sscpContext);

    } while (0);
    
    return 0;
}

/*!
 * @brief Application init for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_InitHardware(void)
{
    status_t result = kStatus_Fail;

    if (g_isCryptoHWInitialized == true)
    {
        return 0;
    }

    /* Mutex for access to ele_crypto HW */
    if (mcux_mutex_init(&ele_hwcrypto_mutex))
    {
        PRINTF("NO memory - init failed\n");
        return kStatus_Fail;
    }

    if ((result = mcux_mutex_lock(&ele_hwcrypto_mutex)) != 0)
    {
        PRINTF("Mutex lock failed\n");
        return kStatus_Fail;
    }

    do
    {
        /****************** Wait for ELE MU is ready ***********************/
        sss_sscp_rng_t rctx;
        result = ELEMU_mu_wait_for_ready(ELEMUA, ELE_MAX_SUBSYSTEM_WAIT);
        if (result != kStatus_Success)
        {
            break;
        }

#if (defined(ELEMU_HAS_LOADABLE_FW) && ELEMU_HAS_LOADABLE_FW)
        result = ELEMU_loadFwLocal(ELEMUA);
        if (result != kStatus_Success)
        {
            break;
        }
#endif /* ELEMU_HAS_LOADABLE_FW */

        /****************** Init SSCP service   ***********************/
        result = sscp_mu_init(&g_ele_ctx.sscpContext, (ELEMU_Type *)(uintptr_t)ELEMUA);
        if (result != kStatus_SSCP_Success)
        {
            break;
        }
        /****************** Open ELE Session  ***********************/
        result = sss_sscp_open_session(&g_ele_ctx.sssSession, 0u, ELE_SUBSYSTEM, &g_ele_ctx.sscpContext);

        if (result != kStatus_SSS_Success)
        {
            break;
        }

        result = sss_sscp_key_store_init(&g_ele_ctx.keyStore, &g_ele_ctx.sssSession);

        if (result != kStatus_SSS_Success)
        {
            break;
        }

        /****************** Start RNG ***********************/
        /* RNG call used to init ELE TRNG required e.g. by sss_sscp_key_store_generate_key service
       if TRNG initialization is no needed for used operations, the following code can be removed
       to increase the perfomance.*/
        result = sss_sscp_rng_context_init(&g_ele_ctx.sssSession, &rctx, ELE_HIGH_QUALITY_RNG);

        if (result != kStatus_SSS_Success)
        {
            break;
        }

        /*Providing NULL output buffer, as we just need to initialize TRNG, not get random data*/
        result = sss_sscp_rng_get_random(&rctx, NULL, 0x0u);

        if (result != kStatus_SSS_Success)
        {
            break;
        }

        result = sss_sscp_rng_free(&rctx);

        if (result != kStatus_SSS_Success)
        {
            break;
        }

        result = kStatus_Success;

        g_isCryptoHWInitialized = true;

    } while (0);

    if (result != kStatus_Success)
    {
        ele_close_handles();
    }

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        PRINTF("Mutex unlock failed\n");
        return kStatus_Fail;
    }

    return result;
}

/*!
 * @brief Application Deinit for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic deinit for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_DeinitHardware(void)
{
    status_t result = kStatus_Fail;

    if (g_isCryptoHWInitialized == false)
    {
        return 0;
    }

    if (mcux_mutex_lock(&ele_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }

    result = ele_close_handles();
    if (result == kStatus_Success)
    {
        g_isCryptoHWInitialized = false;
    }

    if (mcux_mutex_unlock(&ele_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }

    if (result == kStatus_Success)
    {
        mcux_mutex_free(&ele_hwcrypto_mutex);
    }

    return result;
}
