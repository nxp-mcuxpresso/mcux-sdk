/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "ele_crypto.h" /* ELE Crypto SW */
#include "fsl_s3mu.h"   /* Messaging unit driver */
#include "ele_fw.h"     /* ELE FW, can be placed in bootable container in real world app */
#include "ele.h"

/******************************************************************************/
/******************** CRYPTO_InitHardware *************************************/
/******************************************************************************/

uint32_t g_isCryptoHWInitialized = false;

ele_ctx_t g_ele_ctx = {0u}; /* Global context */

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

    do
    {
        /****************** Load EdgeLock FW ***********************/
        if (g_ele_ctx.is_fw_loaded != true)
        {
            result = ELE_LoadFw(S3MU, ele_fw);
            if (result != kStatus_Success)
            {
                break;
            }
            else
            {
                g_ele_ctx.is_fw_loaded = true;
            }
        }

        /****************** Initialize EdgeLock services ************/
        result = ELE_InitServices(S3MU);
        if (result != kStatus_Success)
        {
            break;
        }

        /****************** Open EdgeLock session ******************/
        result = ELE_OpenSession(S3MU, &g_ele_ctx.session_handle);
        if (result != kStatus_Success)
        {
            break;
        }

        /****************** Start RNG ***********************/
        result = ELE_StartRng(S3MU);
        if (result != kStatus_Success)
        {
            break;
        }

        g_isCryptoHWInitialized = true;

    } while (0);

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

    do
    {
        /****************** Close EdgeLock session ******************/
        result = ELE_CloseSession(S3MU, g_ele_ctx.session_handle);
        if (result != kStatus_Success)
        {
            break;
        }

        g_ele_ctx.session_handle = 0u;
        g_isCryptoHWInitialized  = false;

    } while (0);

    return result;
}
