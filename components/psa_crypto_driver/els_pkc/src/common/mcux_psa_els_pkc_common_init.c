/*
 * Copyright 2022-2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcux_psa_els_pkc_common_init.h"
#include "mcux_els.h"
#include "mcux_pkc.h"

#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
#include "fsl_trng.h"
#define MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED
#endif

/******************************************************************************/
/*************************** Globals and Mutex ********************************************/
/******************************************************************************/
/*
 * Define global mutexes for HW accelerator
 */
#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
mcux_mutex_t els_pkc_hwcrypto_mutex;
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

static uint32_t g_isCryptoHWInitialized = ELS_PKC_CRYPTOHW_UNINITIALIZED;

/******************************************************************************/
/******************** static/common functions *************************************/
/******************************************************************************/

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
#if defined(MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED)
static status_t trng_initialize(void)
{
    status_t status;

    /* Initilize the TRNG driver */
    trng_config_t trngConfig;

    /* Get default TRNG configs*/
    status = TRNG_GetDefaultConfig(&trngConfig);

    if (status == kStatus_Success)
    {
        /* Set sample mode of the TRNG ring oscillator to Von Neumann, for better random data.*/
        /* Initialize TRNG */
        status = TRNG_Init(TRNG, &trngConfig);
    }
    return status;
}
#endif

static psa_status_t common_init_els_pkc_and_trng(void)
{
    status_t status = kStatus_Fail;

#if defined(ELS)
    /* Enable ELS and related clocks */
    status = ELS_PowerDownWakeupInit(ELS);
#endif /*defined(ELS)*/

#if defined(PKC)
    if (status == kStatus_Success)
    {
        /* Enable PKC related clocks and RAM zero */
        status = PKC_PowerDownWakeupInit(PKC);
    }
#endif /*defined(PKC)*/

    /* Initilize the TRNG driver */
    if (status == kStatus_Success)
    {
#if defined(MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED)
        /* Initialize TRNG */
        status = trng_initialize();
#endif /*defined(MBEDTLS_MCUX_USE_TRNG_AS_ENTROPY_SEED)*/
    }

    return els_pkc_to_psa_status(status);
}

static status_t els_pkc_close_handles(void)
{
    status_t result = kStatus_Success;
    //* TODO */
    return result;
}

/******************************************************************************/
/******************** CRYPTO_InitHardware **************************************/
/******************************************************************************/
/*!
 * @brief Application init for Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
status_t CRYPTO_InitHardware(void)
{
    status_t result = kStatus_Fail;

    if (g_isCryptoHWInitialized == ELS_PKC_CRYPTOHW_INITIALIZED)
    {
        return kStatus_Success;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)

    /* Mutex for access to els_pkc_crypto HW */
    if ((result = mcux_mutex_init(&els_pkc_hwcrypto_mutex)) != 0)
    {
        return kStatus_Fail;
    }

    if ((result = mcux_mutex_lock(&els_pkc_hwcrypto_mutex)) != 0)
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    /* Initialize the els_pkc and trng*/
    result = common_init_els_pkc_and_trng();
    if (result != kStatus_Success)
    {
        /* close the els_pkc handles*/
        result = els_pkc_close_handles();
        if (result == kStatus_Success)
        {
            g_isCryptoHWInitialized = ELS_PKC_CRYPTOHW_UNINITIALIZED;
        }
    }
    else
    {
        g_isCryptoHWInitialized = ELS_PKC_CRYPTOHW_INITIALIZED;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */

    return result;
}

/******************************************************************************/
/******************** CRYPTO_ReInitHardware **************************************/
/******************************************************************************/
/*!
 * @brief Application Re-init for various Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications after
 * wake up from different power modes. Mutex re-init is not required as RAM is
 * retained and mutexes are already available.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 * NOTE: The function must be called in single thread context
 */
status_t CRYPTO_ReInitHardware(void)
{
    status_t status;
    /* Only initialize if global static variable is set to initialized, to
       make sure that CRYPTO_InitHardware is already called once */
    if (g_isCryptoHWInitialized == ELS_PKC_CRYPTOHW_INITIALIZED)
    {
        /* Initialize the els_pkc and trng*/
        status = common_init_els_pkc_and_trng();
    }
    else
    {
        status = kStatus_Success;
    }
    return status;
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

    if (g_isCryptoHWInitialized == ELS_PKC_CRYPTOHW_UNINITIALIZED)
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
        g_isCryptoHWInitialized = ELS_PKC_CRYPTOHW_UNINITIALIZED;
    }

#if defined(PSA_CRYPTO_DRIVER_THREAD_EN)
    if (mcux_mutex_unlock(&els_pkc_hwcrypto_mutex))
    {
        return kStatus_Fail;
    }

    if (result == kStatus_Success)
    {
        if (mcux_mutex_free(&els_pkc_hwcrypto_mutex))
        {
            return kStatus_Fail;
        }
    }
#endif /* defined(PSA_CRYPTO_DRIVER_THREAD_EN) */
    return result;
}
