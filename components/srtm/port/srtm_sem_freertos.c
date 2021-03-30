/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FreeRTOS.h>
#include <semphr.h>

#include "srtm_sem.h"
#include "fsl_common.h"

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
#if defined(SRTM_STATIC_API) && SRTM_STATIC_API
srtm_sem_t SRTM_Sem_Create(uint32_t maxCount, uint32_t initCount, srtm_sem_buf_t *stack)
{
    return xSemaphoreCreateCountingStatic(maxCount, initCount, stack);
}
#else
srtm_sem_t SRTM_Sem_Create(uint32_t maxCount, uint32_t initCount)
{
    return xSemaphoreCreateCounting(maxCount, initCount);
}
#endif

void SRTM_Sem_Destroy(srtm_sem_t sem)
{
    assert(sem);

    vSemaphoreDelete(sem);
}

srtm_status_t SRTM_Sem_Post(srtm_sem_t sem)
{
    srtm_status_t status     = SRTM_Status_Error;
    portBASE_TYPE taskToWake = pdFALSE;

    if (__get_IPSR() != 0U)
    {
        if (xSemaphoreGiveFromISR(sem, &taskToWake) == pdPASS)
        {
            portYIELD_FROM_ISR(taskToWake);
            status = SRTM_Status_Success;
        }
    }
    else
    {
        if (xSemaphoreGive(sem) == pdTRUE)
        {
            status = SRTM_Status_Success;
        }
    }

    return status;
}

srtm_status_t SRTM_Sem_Wait(srtm_sem_t sem, uint32_t timeout)
{
    uint32_t ticks;
    srtm_status_t status = SRTM_Status_Success;

    if (timeout == SRTM_WAIT_FOR_EVER)
    {
        ticks = portMAX_DELAY;
    }
    else if (timeout == SRTM_NO_WAIT)
    {
        ticks = 0U;
    }
    else
    {
        ticks = ((uint32_t)configTICK_RATE_HZ * (uint32_t)(timeout - 1U)) / 1000U + 1U;
    }

    if (xSemaphoreTake(sem, ticks) == pdFALSE)
    {
        status = SRTM_Status_Timeout;
    }

    return status;
}
