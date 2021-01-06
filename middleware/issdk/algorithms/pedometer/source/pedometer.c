/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** 
 * @file pedometer.c
* @brief The pedometer.c file contains the interface definitions for
* pedometer application.
*/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "pedometer.h"

/*******************************************************************************
 * Macros, globals
 ******************************************************************************/
#define PEDOMETER_STATUS_ACTIVITY_BITNUM 0
#define PEDOMETER_STATUS_SUSPEND_BITNUM 3
#define PEDOMETER_STATUS_ACTCHG_BITNUM 4
#define PEDOMETER_STATUS_STEPCHG_BITNUM 5
#define PEDOMETER_STATUS_SUSPCHG_BITNUM 6
#define PEDOMETER_STATUS_MRGFLG_BITNUM 7

#define PEDOMETER_STATUS_ACTIVITY_MASK (7 << PEDOMETER_STATUS_ACTIVITY_BITNUM)
#define PEDOMETER_STATUS_SUSPEND_MASK (1 << PEDOMETER_STATUS_SUSPEND_BITNUM)
#define PEDOMETER_STATUS_ACTCHG_MASK (1 << PEDOMETER_STATUS_ACTCHG_BITNUM)
#define PEDOMETER_STATUS_STEPCHG_MASK (1 << PEDOMETER_STATUS_STEPCHG_BITNUM)
#define PEDOMETER_STATUS_SUSPCHG_MASK (1 << PEDOMETER_STATUS_SUSPCHG_BITNUM)
#define PEDOMETER_STATUS_MRGFLG_MASK (1 << PEDOMETER_STATUS_MRGFLG_BITNUM)

#define PEDOMETER_STATUS_CHG_MASK \
    (PEDOMETER_STATUS_ACTCHG_MASK | PEDOMETER_STATUS_STEPCHG_MASK | PEDOMETER_STATUS_SUSPCHG_MASK)
#define SQUARED(x) ((x) * (x))
/* below values are the best set of value for the algorthm and computed during the algorithm definition.*/
/******************************************************************************
 * Private Function Declarations
 *****************************************************************************/

/* Update status variables */
static void status_update(pedometer_t *pedometer, uint32_t events, bool suspend);

/* Determine autonomous suspend state */
static bool suspend_compute(pedometer_t *pPedometer, ped_accel_t *pData);

/* compute the debounce. */
static bool debounce_count(bool dbcntm, bool condition, debounce_count_t *count, debounce_count_t threshold);

/* Cast uint32_t to uint16_t with saturate */
static uint16_t uint32_to_uint16(uint32_t val);

/******************************************************************************
 * Private Variable Definitions
 ******************************************************************************/

static const pedometer_t pedometer_default = {.status =
                                                  {
                                                      .version = 2,
                                                  },
                                              .config = {
                                                  .sleepcount_threshold = 1,
                                                  .bits = {.config = 1},
                                                  .keynetik =
                                                      {
                                                          .height = 175,
                                                          .weight = 80,
                                                          .filtersteps = PEDO_FILTER_STEPS_DEFAULT,
                                                          .bits =
                                                              {
                                                                  .filtertime = PEDO_FILTER_TIME_DEFAULT,
                                                              },
                                                          .speedperiod = PEDO_SPEED_PERIOD_DEFAULT,
                                                          .stepthreshold = PEDO_STEP_THRESHOLD_DEFAULT,
                                                      },
                                                  .stepcoalesce = 1,
                                                  .oneG = PEDO_ONEG_8G,
                                                  .frequency = PEDO_FREQHZ_DEFAULT,
                                              }};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
** ===================================================================
**     Method      :  pedometer_init
**     brief       :  The interface function initialize the pedometer.
**     params[in]  :  pedometer_t *pPedometer, handle to the pedometer.
**
** ===================================================================
*/
void pedometer_init(pedometer_t *pPedometer)
{
    *pPedometer = pedometer_default;
    KeynetikInitialize(pPedometer->config.oneG, pPedometer->config.frequency, &pPedometer->config.keynetik);
    pPedometer->private.stepchg_stepcount = 0;
}

/*** ===================================================================
**     Method      :  pedometer_configure
**     brief       :  The interface function to configure the pedometer
**     params[in]  :  pedometer_t *pPedometer, handle to the pedometer.
**     params[in]  :  pedometer_config_t configuration parameter.
** ===================================================================
*/
void pedometer_configure(pedometer_t *pPedometer, const pedometer_config_t *pConfig)
{
    pPedometer->config = *pConfig;
    KeynetikInitialize(pPedometer->config.oneG, pPedometer->config.frequency, &pPedometer->config.keynetik);
    pPedometer->private.stepchg_stepcount = 0;
}
/*
** ===================================================================
**     Method      :  pedometer_run
**     brief       :  The interface function excutes the pedometer algorithm.
**     params[in]  :  pedometer_t *pPedometer, handle to the pedometer.
**     params[in]  :  ped_accel_t data   acceleration data.
** ===================================================================
*/
int32_t pedometer_run(pedometer_t *pPedometer, ped_accel_t *pData)
{
    uint32_t events = 0;
    /* if suspend, don't execute the alogrithm and save the power.*/
    bool suspend = suspend_compute(pPedometer, pData);
    if (!suspend)
    {
        events = KeynetikHandleIncomingEvent(pData->accel[0], pData->accel[1], pData->accel[2]);
    }
    status_update(pPedometer, events, suspend);
    return events;
}
/*
** ===================================================================
**     Method      :  status_update
**     brief       :  update the status of the pedometer output
**     params[in]  :  pedometer_t *pPedometer, handle to the pedometer.
**     params[in]  :  uint32_t events    kynetic event
**     params[in]  :  bool suspend     suspend flag
** ===================================================================
*/
static void status_update(pedometer_t *pPedometer, uint32_t events, bool suspend)
{
    bool activity_stable =
        debounce_count(pPedometer->config.bits.activity_dbcntm, !(events & KEYNETIK_ACTIVITYCHANGED),
                       &pPedometer->private.activitycount, pPedometer->config.activitycount_threshold);

    activitylevel_t activity = activity_stable ? keynetikActivityLevel : pPedometer->status.status.bits.activity;
    uint16_t stepcount = uint32_to_uint16(keynetikStepCount);
    uint8_t newstatus = (activity << PEDOMETER_STATUS_ACTIVITY_BITNUM) & PEDOMETER_STATUS_ACTIVITY_MASK;

    if ((newstatus ^ pPedometer->status.status.byte) & PEDOMETER_STATUS_ACTIVITY_MASK)
        newstatus |= PEDOMETER_STATUS_ACTCHG_MASK;

    if (pPedometer->config.stepcoalesce &&
        (stepcount - pPedometer->private.stepchg_stepcount >= pPedometer->config.stepcoalesce))
    {
        pPedometer->private.stepchg_stepcount = stepcount;
        newstatus |= PEDOMETER_STATUS_STEPCHG_MASK;
    }

    if (suspend)
        newstatus |= PEDOMETER_STATUS_SUSPEND_MASK;

    if ((newstatus ^ pPedometer->status.status.byte) & PEDOMETER_STATUS_SUSPEND_MASK)
        newstatus |= PEDOMETER_STATUS_SUSPCHG_MASK;

    if (newstatus & PEDOMETER_STATUS_CHG_MASK)
        newstatus |= PEDOMETER_STATUS_MRGFLG_MASK;
    /* Update the status such stepcount, distance, speed etc..*/
    pPedometer->status.stepcount = uint32_to_uint16(keynetikStepCount);
    pPedometer->status.distance = uint32_to_uint16(keynetikDistance);
    pPedometer->status.speed = keynetikSpeed;
    pPedometer->status.calories = uint32_to_uint16(keynetikCalories);
    pPedometer->status.status.byte = newstatus;
}
/*
** ===================================================================
**     Method      :  suspend_compute
**     brief       :  compute the suspend status.
**     params[in]  :  pedometer_t *pPedometer, handle to the pedometer.
**     params[in]  :  ped_accel_t data   acceleration data.
** ===================================================================
*/
static bool suspend_compute(pedometer_t *pPedometer, ped_accel_t *pData)
{
    /* compute the magnitude*/
    uint32_t mag2 = SQUARED(pData->accel[0]) + SQUARED(pData->accel[1]) + SQUARED(pData->accel[2]);
    bool stationary =
        (mag2 > SQUARED(pPedometer->config.sleepminimum)) && (mag2 < SQUARED(pPedometer->config.sleepmaximum));
    bool suspend = debounce_count(pPedometer->config.bits.sleep_dbcntm, stationary, &pPedometer->status.sleepcount,
                                  pPedometer->config.sleepcount_threshold);
    return (suspend);
}
/*
** ===================================================================
**     Method      :  uint32_to_uint16
**     brief       :  conversion function from 32 to 16.
**     params[in]  :  uint32_t x, imput
**     params[in]  :  ped_accel_data data   acceleration data.
** ===================================================================
*/
uint16_t uint32_to_uint16(uint32_t val)
{
    if (val > 0x0000FFFF)
        return (0xFFFF);
    return ((uint16_t)val);
}
/*
** ===================================================================
**     Method      :  debounce_count
**     brief       :  compute the debouct status.
**     params[in]  :  bool dbcntm,
**     params[in]  :  bool condition
**     params[in]  :  debounce_count_t *count,
**     params[in]  :  debounce_count_t threshold, debouce threshold
** ===================================================================
*/
static bool debounce_count(bool dbcntm, bool condition, debounce_count_t *count, debounce_count_t threshold)
{
    if (condition)
    {
        /* increment count up to, but not above the threshold */
        *count = (*count + 1) < threshold ? *count + 1 : threshold;
    }
    else
    {
        if (dbcntm)
            *count = 0;
        else
            /* decrement count down to, but not below zero */
            *count = (*count - 1) > 0 ? *count - 1 : 0;
    }
    return ((bool)(*count >= threshold));
}
