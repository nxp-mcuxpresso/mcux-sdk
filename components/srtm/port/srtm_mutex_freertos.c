/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FreeRTOS.h>
#include <semphr.h>

#include "srtm_mutex.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
srtm_mutex_t SRTM_Mutex_Create(void)
{
    return xSemaphoreCreateMutex();
}

void SRTM_Mutex_Destroy(srtm_mutex_t mutex)
{
    assert(mutex);

    vSemaphoreDelete(mutex);
}

srtm_status_t SRTM_Mutex_Lock(srtm_mutex_t mutex)
{
    assert(mutex);

    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdFALSE)
    {
        return SRTM_Status_Error;
    }

    return SRTM_Status_Success;
}

srtm_status_t SRTM_Mutex_Unlock(srtm_mutex_t mutex)
{
    assert(mutex);

    if (xSemaphoreGive(mutex) == pdFALSE)
    {
        return SRTM_Status_Error;
    }

    return SRTM_Status_Success;
}
