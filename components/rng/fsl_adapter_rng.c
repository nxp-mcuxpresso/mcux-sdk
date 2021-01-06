/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_adapter_rng.h"
#include "fsl_rng.h"

hal_rng_status_t HAL_RngInit(void)
{
    /*MISRA C-2012 Rule 8.2*/
    return kStatus_HAL_RngSuccess;
}

void HAL_RngDeinit(void)
{
    /*MISRA C-2012 Rule 8.2*/
    return;
}

hal_rng_status_t HAL_RngGetData(void *pRandomNo, uint32_t dataSize)
{
    uint32_t skip;
    uint32_t random_32;
    uint8_t *random_p;
    uint32_t random_size;
    uint8_t *data_p = (uint8_t *)pRandomNo;
    uint32_t i;
    hal_rng_status_t status = kStatus_HAL_RngSuccess;

    if (NULL == pRandomNo)
    {
        status = kStatus_HAL_RngNullPointer;
    }

    do
    {
        /* Read Entropy.*/
        random_32 = RNG_GetRandomData();

        random_p = (uint8_t *)&random_32;

        if (dataSize < sizeof(random_32))
        {
            random_size = dataSize;
        }
        else
        {
            random_size = sizeof(random_32);
        }

        for (i = 0; i < random_size; i++)
        {
            *data_p++ = *random_p++;
        }

        dataSize -= random_size;
        /* Skip next 32 random numbers for better entropy */
        for (skip = 0; skip < 32U; skip++)
        {
            (void)RNG_GetRandomData();
        }
    } while (dataSize > 0U);
    return status;
}

hal_rng_status_t HAL_RngHwGetData(void *pRandomNo, uint32_t dataSize)
{
    return KStatus_HAL_RngNotSupport;
}

hal_rng_status_t HAL_RngSetSeed(uint32_t seed)
{
    (void)RNG_GetRandomData();
    return kStatus_HAL_RngSuccess;
}
