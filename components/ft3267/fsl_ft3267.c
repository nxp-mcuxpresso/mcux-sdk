/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ft3267.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _ft3267_touch_point
{
    uint8_t XH;
    uint8_t XL;
    uint8_t YH;
    uint8_t YL;
    uint8_t RESERVED[2];
} ft3267_touch_point_t;

typedef struct _ft3267_touch_data
{
    uint8_t GEST_ID;
    uint8_t TD_STATUS;
    ft3267_touch_point_t TOUCH[FT3267_MAX_TOUCHES];
} ft3267_touch_data_t;

#define TOUCH_POINT_GET_EVENT(T) ((touch_event_t)(uint8_t)((T).XH >> 6U))
#define TOUCH_POINT_GET_ID(T)    ((T).YH >> 4)
#define TOUCH_POINT_GET_X(T)     (int)(uint16_t)((((uint16_t)(T).XH & 0x0fU) << 8) | (uint16_t)(T).XL)
#define TOUCH_POINT_GET_Y(T)     (int)(uint16_t)((((uint16_t)(T).YH & 0x0fU) << 8) | (uint16_t)(T).YL)

#define FT3267_SUBADDR_SIZE (1U)

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t FT3267_Init(ft3267_handle_t *handle, const ft3267_config_t *config)
{
    if ((NULL == handle) || (NULL == config))
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(*handle));

    handle->I2C_ReceiveFunc  = config->I2C_ReceiveFunc;
    handle->pullResetPinFunc = config->pullResetPinFunc;
    handle->pullPowerPinFunc = config->pullPowerPinFunc;

    /* Power on sequence */
    if (NULL != handle->pullPowerPinFunc)
    {
        handle->pullPowerPinFunc(true);
    }

    /* Reset the controller. */
    if (NULL != handle->pullResetPinFunc)
    {
        handle->pullResetPinFunc(false);
        config->timeDelayMsFunc(5U);
        handle->pullResetPinFunc(true);
    }

    return kStatus_Success;
}

status_t FT3267_Deinit(ft3267_handle_t *handle)
{
    status_t status;

    if (NULL == handle)
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        if (NULL != handle->pullResetPinFunc)
        {
            handle->pullResetPinFunc(false);
        }

        if (NULL != handle->pullPowerPinFunc)
        {
            handle->pullPowerPinFunc(true);
        }

        status = kStatus_Success;
    }

    return status;
}

status_t FT3267_GetSingleTouch(ft3267_handle_t *handle, touch_event_t *touch_event, int *touch_x, int *touch_y)
{
    status_t status;
    touch_event_t touch_event_local;

    status =
        handle->I2C_ReceiveFunc(FT3267_I2C_ADDRESS, 1U, FT3267_SUBADDR_SIZE, handle->touchBuf, FT3267_TOUCH_DATA_LEN);

    if (status == kStatus_Success)
    {
        ft3267_touch_data_t *touch_data = (ft3267_touch_data_t *)(void *)(handle->touchBuf);

        touch_event_local = TOUCH_POINT_GET_EVENT(touch_data->TOUCH[0]);

        /* Update coordinates only if there is touch detected */
        if ((touch_event_local == kTouch_Down) || (touch_event_local == kTouch_Contact))
        {
            if (NULL != touch_x)
            {
                *touch_x = TOUCH_POINT_GET_X(touch_data->TOUCH[0]);
            }
            if (NULL != touch_y)
            {
                *touch_y = TOUCH_POINT_GET_Y(touch_data->TOUCH[0]);
            }
        }

        if (touch_event != NULL)
        {
            *touch_event = touch_event_local;
        }
    }

    return status;
}

status_t FT3267_GetMultiTouch(ft3267_handle_t *handle, int *touch_count, touch_point_t touch_array[FT3267_MAX_TOUCHES])
{
    status_t status;
    uint32_t i;

    status =
        handle->I2C_ReceiveFunc(FT3267_I2C_ADDRESS, 1U, FT3267_SUBADDR_SIZE, handle->touchBuf, FT3267_TOUCH_DATA_LEN);

    if (status == kStatus_Success)
    {
        ft3267_touch_data_t *touch_data = (ft3267_touch_data_t *)(void *)(handle->touchBuf);

        /* Check for valid number of touches - otherwise ignore touch information */
        if (touch_data->TD_STATUS > FT3267_MAX_TOUCHES)
        {
            touch_data->TD_STATUS = 0;
        }

        /* Decode number of touches */
        if (NULL != touch_count)
        {
            *touch_count = (int)touch_data->TD_STATUS;
        }

        /* Decode valid touch points */
        for (i = 0; i < touch_data->TD_STATUS; i++)
        {
            touch_array[i].TOUCH_ID    = TOUCH_POINT_GET_ID(touch_data->TOUCH[i]);
            touch_array[i].TOUCH_EVENT = TOUCH_POINT_GET_EVENT(touch_data->TOUCH[i]);
            touch_array[i].TOUCH_X     = TOUCH_POINT_GET_X(touch_data->TOUCH[i]);
            touch_array[i].TOUCH_Y     = TOUCH_POINT_GET_Y(touch_data->TOUCH[i]);
        }

        /* Clear vacant elements of touch_array */
        for (; i < FT3267_MAX_TOUCHES; i++)
        {
            touch_array[i].TOUCH_ID    = 0;
            touch_array[i].TOUCH_EVENT = kTouch_Reserved;
            touch_array[i].TOUCH_X     = 0;
            touch_array[i].TOUCH_Y     = 0;
        }
    }

    return status;
}
