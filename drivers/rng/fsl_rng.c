/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rng.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rng"
#endif

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Prototypes
 *******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t RNG_GetRandomData(void *data, size_t dataSize)
{
    status_t result = kStatus_Fail;
    uint32_t random32;
    uint32_t randomSize;
    uint8_t *pRandom;
    uint8_t *pData = (uint8_t *)data;
    uint32_t i, j;

    /* Check input parameters.*/
    if (!(data != NULL) && (dataSize != 0U))
    {
        result = kStatus_InvalidArgument;
    }
    else
    {
        do
        {
            /* Read Entropy.*/
            random32 = RNG_GetRandomDataWord();
            pRandom  = (uint8_t *)&random32;

            if (dataSize < sizeof(random32))
            {
                randomSize = dataSize;
            }
            else
            {
                randomSize = sizeof(random32);
            }

            for (i = 0; i < randomSize; i++)
            {
                *pData++ = *pRandom++;
            }

            dataSize -= randomSize;

            /* Discard next 32 random numbers for better entropy */
            for (j = 0; j < 32U; j++)
            {
                (void)RNG_GetRandomDataWord();
            }

        } while (dataSize > 0U);

        result = kStatus_Success;
    }

    return result;
}
