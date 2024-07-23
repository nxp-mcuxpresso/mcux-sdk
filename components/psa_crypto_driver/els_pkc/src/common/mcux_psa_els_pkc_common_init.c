/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_els_pkc_common_init.h"
#include "mcux_els.h"
#include "mcux_pkc.h"

/******************************************************************************/
/*************************** Mutex ********************************************/
/******************************************************************************/
/*
 * Define global mutexes for HW accelerator
 */
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
mcux_mutex_t els_pkc_hwcrypto_mutex;
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

/******************************************************************************/
/******************** CRYPTO_InitHardware *************************************/
/******************************************************************************/

bool g_isCryptoHWInitialized = false;

psa_status_t els_pkc_to_psa_status(status_t els_pkc_status)
{
    psa_status_t status = PSA_ERROR_HARDWARE_FAILURE;
    switch (els_pkc_status)
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

static psa_status_t els_pkc_init_hardware(void)
{
    status_t status = kStatus_Fail;

#if defined(ELS)
    /* Enable ELS and related clocks */
    status = ELS_PowerDownWakeupInit(ELS);
    if (status != kStatus_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif

#if defined(PKC)
    /* Enable PKC related clocks and RAM zero */
    status = PKC_PowerDownWakeupInit(PKC);
    if (status != kStatus_Success)
    {
        return PSA_ERROR_GENERIC_ERROR;
    }
#endif

    return PSA_SUCCESS;
}

static status_t els_pkc_close_handles(void)
{
    status_t result = kStatus_Success;
    //* TODO */
    return result;
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
        return kStatus_Success;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    /* Mutex for access to els_pkc_crypto HW */
    if (mcux_mutex_init(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if ((result = mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) != 0)
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    /* Initialize the els_pkc hardware*/
    result = els_pkc_init_hardware();
    if (result != kStatus_Success)
    {
        /* close the els_pkc handles*/
        result = els_pkc_close_handles();
        if (result == kStatus_Success)
        {
            g_isCryptoHWInitialized = false;
        }
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

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
        return kStatus_Success;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_lock(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    /* close the els_pkc handles*/
    result = els_pkc_close_handles();
    if (result == kStatus_Success)
    {
        g_isCryptoHWInitialized = false;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }

    if (result == kStatus_Success)
    {
        mcux_mutex_free(&els_pkc_hwcrypto_mutex);
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
    return result;
}
