/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_rng.h"
#include "fsl_rnga.h"

hal_rng_status_t HAL_RngInit(void)
{
    /* Init RNGA */
    RNGA_Init(RNG);
    return kStatus_HAL_RngSuccess;
}

void HAL_RngDeinit(void)
{
    RNGA_Deinit(RNG);
    return;
}

hal_rng_status_t HAL_RngGetData(void *pRandomNo, uint32_t dataSize)
{
    hal_rng_status_t status = kStatus_HAL_RngSuccess;

    if (NULL == pRandomNo)
    {
        status = kStatus_HAL_RngNullPointer;
    }
    if (kStatus_Success != RNGA_GetRandomData(RNG, pRandomNo, dataSize))
    {
        status = kStatus_HAL_RngInternalError;
    }
    return status;
}

hal_rng_status_t HAL_RngHwGetData(void *pRandomNo, uint32_t dataSize)
{
    return KStatus_HAL_RngNotSupport;
}

hal_rng_status_t HAL_RngSetSeed(uint32_t seed)
{
    RNGA_Seed(RNG, seed);
    return kStatus_HAL_RngSuccess;
}
