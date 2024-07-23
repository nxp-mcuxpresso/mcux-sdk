/*
 * Copyright 2021-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdarg.h>

#include "fsl_pm_core.h"
#include "fsl_pm_device.h"

/*
 * $Coverage Justification Reference$
 *
 * $Justification pm_core_c_ref_1$
 * This depends on device implementation. The "clean" function is not NULL with tested devices.
 *
 * $Justification pm_core_c_ref_2$
 * Error doesn't happen in test case.
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern pm_device_option_t g_devicePMOption;
AT_ALWAYS_ON_DATA(static pm_handle_t *s_pmHandle);

static uint32_t s_defaultPMIrqMask = 0UL;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static uint8_t PM_findDeepestState(uint64_t duration);

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
static status_t PM_notifyPowerStateEntry(uint8_t powerState);
static status_t PM_notifyPowerStateExit(uint8_t powerState);
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

static void PM_SetAllowedLowestPowerMode(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/***************************************************************
 * Private Funtions
 ***************************************************************/
static uint8_t PM_findDeepestState(uint64_t duration)
{
    uint8_t i              = 0U;
    uint8_t ret            = 0xFFU;
    uint8_t j              = 0U;
    pm_state_t *state      = NULL;
    bool stateSatisfy      = false;
    pm_state_t *stateArray = s_pmHandle->deviceOption->states;
    uint8_t stateCount     = (s_pmHandle->deviceOption->stateCount);
    pm_resc_mask_t tmpSoftRescMask;

    for (i = stateCount; i >= 1U; i--)
    {
        state = &stateArray[(i - 1U)];

        stateSatisfy = false;
        /*
         * The next power state's exit latency should be smaller than low power duration.
         * And the next power state should satisfy the whole system's constraints.
         */
        if (duration == 0U)
        {
            stateSatisfy = true;
        }
        else
        {
            if (state->exitLatency < duration)
            {
                /* If the total latency is less than the duration, then this state
                 * satisfies the duration constraints */
                stateSatisfy = true;
            }
        }

        /* If the state satisfies the duration constraints, check the other system
         * constraints */
        if (stateSatisfy == true)
        {
            for (j = 0U; j < PM_RESC_MASK_ARRAY_SIZE; j++)
            {
                if ((s_pmHandle->resConstraintMask.rescMask[j] & state->fixConstraintsMask.rescMask[j]) == 0UL)
                {
                    tmpSoftRescMask.rescMask[j] =
                        state->varConstraintsMask.rescMask[j] & (s_pmHandle->resConstraintMask.rescMask[j]);
                }
                else
                {
                    stateSatisfy = false;
                    break;
                }
            }
        }

        if (stateSatisfy && ((i - 1U) <= s_pmHandle->powerModeConstraint))
        {
            (void)memcpy(&s_pmHandle->softConstraints, &tmpSoftRescMask, sizeof(pm_resc_mask_t));
            ret = (i - 1U);
            break;
        }
    }

    return ret;
}

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
static status_t PM_notifyPowerStateEntry(uint8_t powerState)
{
    uint8_t i;
    pm_notify_callback_func_t callback;
    pm_notify_element_t *currElement = NULL;
    status_t status                  = kStatus_PMSuccess;

    /* Execute from group0 to group2. */
    for (i = (uint8_t)kPM_NotifyGroup0; i <= (uint8_t)kPM_NotifyGroup2; i++)
    {
        s_pmHandle->curNotifyGroup = (pm_notify_group_t)i;
        if (LIST_GetSize((list_handle_t) & (s_pmHandle->notifyList[i])) != 0UL)
        {
            currElement = (pm_notify_element_t *)(void *)(s_pmHandle->notifyList[i].head);

            do
            {
                callback = currElement->notifyCallback;
                status   = callback(kPM_EventEnteringSleep, powerState, currElement->data);
                if (status != kStatus_Success)
                {
                    s_pmHandle->curNotifyElement = currElement;
                    return kStatus_PMNotifyEventError;
                }
                currElement = (pm_notify_element_t *)(void *)currElement->link.next;
            } while (currElement != NULL);
        }
    }

    s_pmHandle->curNotifyGroup   = kPM_NotifyGroup2;
    s_pmHandle->curNotifyElement = NULL;
    return kStatus_PMSuccess;
}

static status_t PM_notifyPowerStateExit(uint8_t powerState)
{
    int8_t i;
    pm_notify_element_t *currElement = NULL;

    if (s_pmHandle->curNotifyElement != NULL)
    {
        i = (int8_t)(s_pmHandle->curNotifyGroup);
    }
    else
    {
        /* execute Group 2 first on exit from low power */
        i = (int8_t)kPM_NotifyGroup2;
    }

    /* Execute from group2 to group0. */
    for (; i >= (int8_t)kPM_NotifyGroup0; i--)
    {
        if (LIST_GetSize((list_handle_t) & (s_pmHandle->notifyList[i])) != 0UL)
        {
            currElement = (pm_notify_element_t *)(void *)(s_pmHandle->notifyList[i].head);

            do
            {
                (void)(currElement->notifyCallback(kPM_EventExitingSleep, powerState, currElement->data));
                if (currElement == s_pmHandle->curNotifyElement)
                {
                    break;
                }
                currElement = (pm_notify_element_t *)(void *)(currElement->link.next);
            } while (currElement != NULL);
        }
    }

    return kStatus_PMSuccess;
}
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

static void PM_SetAllowedLowestPowerMode(void)
{
    uint8_t lowestPowerMode = PM_LP_STATE_COUNT - 1U;
    uint8_t index;

    for (index = 0U; index < PM_LP_STATE_COUNT; index++)
    {
        if (s_pmHandle->powerModeConstraintCount[index] > 0U)
        {
            lowestPowerMode = index;
            break;
        }
    }

    s_pmHandle->powerModeConstraint = lowestPowerMode;
}

static void PM_EnterCriticalDefault(void)
{
    s_defaultPMIrqMask = DisableGlobalIRQ();
}

static void PM_ExitCriticalDefault(void)
{
    EnableGlobalIRQ(s_defaultPMIrqMask);
}

/***************************************************************
 * Public Funtions
 ***************************************************************/
/*!
 * brief Initialize the power manager handle, this function should be invoked before using other power manager
 * APIs.
 *
 * note In default, the power manager is disabled.
 *
 * param handle Pointer to the pm_handle_t structure, upper layer software should pre-allocate the handle global
 * variable.
 */
void PM_CreateHandle(pm_handle_t *handle)
{
    assert(handle != NULL);

    /* Clear handle. */
    (void)memset(handle, 0, sizeof(*handle));

    handle->enable = false;
    /* Initial value is set to 1 as Power Manager is disabled by default */
    handle->disableCount = 1;
    handle->deviceOption = &g_devicePMOption;
#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
    handle->timerStart       = NULL;
    handle->timerStop        = NULL;
    handle->getTimerDuration = NULL;
    handle->getTimestamp     = NULL;
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

    handle->enterCritical = PM_EnterCriticalDefault;
    handle->exitCritical  = PM_ExitCriticalDefault;

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
    /* Create notify lists. */
    LIST_Init((list_handle_t) & (handle->notifyList[kPM_NotifyGroup0]), 0UL);
    LIST_Init((list_handle_t) & (handle->notifyList[kPM_NotifyGroup1]), 0UL);
    LIST_Init((list_handle_t) & (handle->notifyList[kPM_NotifyGroup2]), 0UL);
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    LIST_Init((list_handle_t) & (handle->wakeupSourceList), 0UL);
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

    s_pmHandle = handle;

    if (s_pmHandle->deviceOption->prepare != NULL)
    {
        s_pmHandle->deviceOption->prepare();
    }

    /* Need to clean some device register for proper functioning */
    /*
     * $Branch Coverage Justification$
     * $ref pm_core_c_ref_1$.
     */
    if (s_pmHandle->deviceOption->clean != NULL)
    {
        s_pmHandle->deviceOption->clean();
    }

    PM_SetAllowedLowestPowerMode();
}

/*!
 * brief Enable/disable power manager functions.
 *
 * param enable Used to enable/disable power manager functions.
 */
void PM_EnablePowerManager(bool enable)
{
    /* Check whether Power Manager has been initialized or not */
    assert(s_pmHandle != NULL);

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (enable == true)
    {
        assert(s_pmHandle->disableCount > 0);

        s_pmHandle->disableCount--;

        if (s_pmHandle->disableCount == 0)
        {
            s_pmHandle->enable = true;
        }
    }
    else
    {
        s_pmHandle->disableCount++;

        if (s_pmHandle->disableCount >= 1)
        {
            s_pmHandle->enable = false;
        }
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }
}

/*!
 * brief Power manager core API, this API should be used on RTOS's IDLE task.
 *
 * This function contains several steps:
 * 1. Compute target power state based on the policy module.
 * 2. Notify upper layer software of the power mode entering.
 * 3. Enter into target power state.
 * 4. Exit from low power state, if wakeup event occurred.
 * 5. Notify upper layer software of the power mode exiting.
 *
 * The target power state is determined based on two factors:
 *   a. The input parameter should be larger than state's exitLatency attribution.
 *   b. resConstraintsMask logical AND state's lossFeature should equal to 0, because constraint can be understand as
 * some features can not loss.
 *
 * param duration The time in low power mode, this value is calculate from RTOS API.
 */
void PM_EnterLowPower(uint64_t duration)
{
    uint8_t stateIndex;
    status_t status = kStatus_PMSuccess;

    if (s_pmHandle->enable)
    {
        /* 1. Based on duration and system constraints compute the next allowed deepest power state. */
        stateIndex = PM_findDeepestState(duration);
        if (stateIndex != 0xFFU)
        {
            s_pmHandle->targetState = stateIndex;

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
            /* Notify the enter of power state */
            status = PM_notifyPowerStateEntry(stateIndex);
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

            if (status == kStatus_PMSuccess)
            {
#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
                if (s_pmHandle->getTimestamp != NULL)
                {
                    s_pmHandle->entryTimestamp = s_pmHandle->getTimestamp();
                }

                /* Start low power timer if needed */
                if ((s_pmHandle->timerStart != NULL) && (duration != 0UL))
                {
                    s_pmHandle->timerStart(duration - (s_pmHandle->deviceOption->states[stateIndex].exitLatency));
                }
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

                /* Enter into low power state. */
                s_pmHandle->deviceOption->enter(stateIndex, &s_pmHandle->softConstraints, &s_pmHandle->sysRescGroup);

#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
                /* Stop low power timer if it is started */
                if (s_pmHandle->timerStop != NULL)
                {
                    s_pmHandle->timerStop();
                }

                if (s_pmHandle->getTimestamp != NULL)
                {
                    s_pmHandle->exitTimestamp = s_pmHandle->getTimestamp();
                }
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */
            }

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
            /* Notify the exit of power state. */
            (void)PM_notifyPowerStateExit(stateIndex);
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

            /*
             * $Branch Coverage Justification$
             * $ref pm_core_c_ref_1$.
             */
            if (s_pmHandle->deviceOption->clean != NULL)
            {
                s_pmHandle->deviceOption->clean();
            }
        }
    }
}

#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
/*!
 * brief Register timer controller related functions to power manager.
 *
 * If low power timer is the wakeup source, please remember to register it into power manager by using
 * PM_RegisterWakeupSource() function.
 *
 * param handle Pointer to the pm_handle_t structure
 * param timerStart Low power timer start function, this parameter can be NULL, and it means low power timer is not set
 *  as the wakeup source.
 * param timerStop Low power timer stop function, this parameter can also be set as NULL.
 * param timerSync Low power timer sync function, this parameter can also be set as NULL.
 * param getTimestamp Low power timestamp function, this parameter can also be set as NULL.
 * param getTimerDuration Get timer count function. this parameter can also be set as NULL.
 */
void PM_RegisterTimerController(pm_handle_t *handle,
                                pm_low_power_timer_start_func_t timerStart,
                                pm_low_power_timer_stop_func_t timerStop,
                                pm_low_power_timer_get_timestamp_func_t getTimestamp,
                                pm_low_power_timer_get_duration_func_t getTimerDuration)
{
    assert(handle != NULL);

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    handle->timerStart       = timerStart;
    handle->timerStop        = timerStop;
    handle->getTimerDuration = getTimerDuration;
    handle->getTimestamp     = getTimestamp;

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }
}

void PM_RegisterCriticalRegionController(pm_handle_t *handle,
                                         pm_enter_critical criticalEntry,
                                         pm_exit_critical criticalExit)
{
    assert(handle != NULL);

    handle->enterCritical = criticalEntry;
    handle->exitCritical  = criticalExit;
}

/*!
 * brief Get the actual low power state duration.
 */
uint64_t PM_GetLastLowPowerDuration(void)
{
    return s_pmHandle->getTimerDuration(s_pmHandle->entryTimestamp, s_pmHandle->exitTimestamp);
}
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
/*!
 * brief Register notify element into the selected group.
 *
 * param groupId The group of the notify list, this will affect the execution sequence.
 * param notifyElement The pointer to pm_notify_element_t.
 * return status_t The status of register notify object behavior.
 */
status_t PM_RegisterNotify(pm_notify_group_t groupId, pm_notify_element_t *notifyElement)
{
    assert(notifyElement != NULL);

    status_t status = kStatus_PMSuccess;

    if (LIST_AddTail((list_handle_t) & (s_pmHandle->notifyList[groupId]),
                     (list_element_handle_t) & (notifyElement->link)) != kLIST_Ok)
    {
        status = kStatus_PMFail;
    }

    return status;
}

/*!
 * brief Update notify element's callback function and application data.
 *
 * param notifyElement The pointer to the notify element to update.
 * param callback The callback function to be updated.
 * param data Pointer to the callback function private data.
 */
void PM_UpdateNotify(void *notifyElement, pm_notify_callback_func_t callback, void *data)
{
    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    ((pm_notify_element_t *)notifyElement)->data           = data;
    ((pm_notify_element_t *)notifyElement)->notifyCallback = callback;

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }
}

/*!
 * brief Remove notify element from its notify group.
 *
 * param notifyElement The pointer to the notify element to remove.
 */
status_t PM_UnregisterNotify(void *notifyElement)
{
    status_t status = kStatus_PMSuccess;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (LIST_RemoveElement((list_element_handle_t) & (((pm_notify_element_t *)notifyElement)->link)) != kLIST_Ok)
    {
        status = kStatus_PMFail;
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return status;
}
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
/*!
 * brief Initialize the wakeup source object.
 *
 * param ws    Pointer to the pm_wakeup_source_t variable.
 * param wsId  Used to select the wakeup source, the wsId of each wakeup source can be found in fsl_pm_device.h
 * param service The function to be invoked when wake up source asserted.
 * param enable Used to enable/disable the selected wakeup source.
 */
void PM_InitWakeupSource(pm_wakeup_source_t *ws, uint32_t wsId, pm_wake_up_source_service_func_t service, bool enable)
{
    assert(ws != NULL);

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    ws->wsId    = wsId;
    ws->service = service;
    ws->enabled = enable;
    ws->active  = false;

    if (enable == true)
    {
        (void)LIST_AddTail((list_handle_t) & (s_pmHandle->wakeupSourceList), (list_element_handle_t) & (ws->link));
    }

    (void)(s_pmHandle->deviceOption->manageWakeupSource(ws, enable));

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }
}

/*!
 * brief Enable wakeup source.
 *
 * param ws Pointer to the wakeup source object to be enabled.
 * return status_t The status of enable wakeup source behavior.
 */
status_t PM_EnableWakeupSource(pm_wakeup_source_t *ws)
{
    assert(ws != NULL);

    status_t status = kStatus_PMSuccess;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (!(ws->enabled))
    {
        /* Add wake up source to list so PM can parse the list if wake up event
         * occurs, and trigger the service callback if needed */
        (void)LIST_AddTail((list_handle_t) & (s_pmHandle->wakeupSourceList), (list_element_handle_t) & (ws->link));
        status = s_pmHandle->deviceOption->manageWakeupSource(ws, true);

        if (status == kStatus_Success)
        {
            ws->enabled = true;
        }
        else
        {
            /*
             * $Line Coverage Justification$
             * $ref pm_core_c_ref_2$.
             */
            status = kStatus_PMWakeupSourceEnableError;
        }
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return status;
}

/*!
 * brief Disable wakeup source
 *
 * param ws Pointer to the wakeup source object to be disabled.
 * return status_t The status of disable wakeup source behavior.
 */
status_t PM_DisableWakeupSource(pm_wakeup_source_t *ws)
{
    assert(ws != NULL);

    status_t status = kStatus_PMSuccess;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (ws->enabled)
    {
        /* Remove the wake up source from the list */
        (void)LIST_RemoveElement((list_element_handle_t) & (ws->link));
        status = s_pmHandle->deviceOption->manageWakeupSource(ws, false);

        if (status == kStatus_Success)
        {
            ws->enabled = false;
        }
        else
        {
            /*
             * $Line Coverage Justification$
             * $ref pm_core_c_ref_2$.
             */
            status = kStatus_PMWakeupSourceDisableError;
        }
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return status;
}

/*!
 * brief Checks if any enabled wake up source is responsible for last wake up
 *       event. In such case, it will call the wake up source callback if it
 *       has been registered. Likely to be called from Wake Up Unit IRQ Handler.
 *
 * return status_t The status of handling the wake up event.
 */
status_t PM_HandleWakeUpEvent(void)
{
    status_t status = kStatus_PMSuccess;
    pm_wakeup_source_t *currWakeUpSource;

    if (LIST_GetSize((list_handle_t) & (s_pmHandle->wakeupSourceList)) != 0UL)
    {
        currWakeUpSource = (pm_wakeup_source_t *)(void *)(s_pmHandle->wakeupSourceList.head);

        /* the list should contain only enabled ws */
        assert(currWakeUpSource->enabled == true);

        do
        {
            if (currWakeUpSource->service != NULL)
            {
                if (s_pmHandle->deviceOption->isWakeupSource(currWakeUpSource) == true)
                {
                    /* The wake up source trigger the last wake up event
                     * we can call the callback */
                    status = PM_TriggerWakeSourceService(currWakeUpSource);
                }
            }

            currWakeUpSource = (pm_wakeup_source_t *)(void *)currWakeUpSource->link.next;
        } while (currWakeUpSource != NULL);
    }

    return status;
}

/*!
 * brief If the specfic wakeup event occurs, invoke this API to execute its service function.
 *
 * param ws Pointer to the wakeup source object.
 * return status_t The status of trigger wakeup source behavior.
 */
status_t PM_TriggerWakeSourceService(pm_wakeup_source_t *ws)
{
    assert(ws != NULL);

    status_t status = kStatus_PMSuccess;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (ws->enabled)
    {
        if (ws->active)
        {
            status = kStatus_PMWakeupSourceServiceBusy;
        }
        else
        {
            ws->active = true;
            ws->service();
            ws->active = false;

            status = kStatus_PMSuccess;
        }
    }
    else
    {
        /*
         * $Line Coverage Justification$
         * $ref pm_core_c_ref_2$.
         */
        status = kStatus_PMWakeupSourceEnableError;
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return status;
}
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*!
 * brief Used to set constraints(including power mode constraint and resource constraints)
 *
 * For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3
 *  code
 *      PM_SetConstraints(Sleep_Mode, 3, PM_RESC_1, PM_RESC_2, PM_RESC_3);
 *  endcode
 *
 * param powerModeConstraint The lowest power mode allowed, the power mode constraint macros
 *                            can be found in fsl_pm_device.h
 * param rescNum The number of resource constraints to be set.
 * return status_t The status of set constraints behavior.
 */
status_t PM_SetConstraints(uint8_t powerModeConstraint, int32_t rescNum, ...)
{
    status_t ret = kStatus_Success;
    uint32_t opMode;
    uint32_t rescShift;
    int32_t inputResc;
    va_list ap;
    int32_t i;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (powerModeConstraint != PM_LP_STATE_NO_CONSTRAINT)
    {
        if (powerModeConstraint >= PM_LP_STATE_COUNT)
        {
            /* wrong power mode index passed in parameter */
            ret = kStatus_Fail;
        }
        else
        {
            /* Set power mode constraint */
            s_pmHandle->powerModeConstraintCount[powerModeConstraint]++;
            PM_SetAllowedLowestPowerMode();
        }
    }
    else
    {
        /* No power mode constraint to apply, only ressource constraints */
        ;
    }

    if (rescNum != 0)
    {
        va_start(ap, rescNum);

        for (i = 0; i < rescNum; i++)
        {
            inputResc = (int32_t)va_arg(ap, int32_t);
            PM_DECODE_RESC(inputResc);

            assert(rescShift < (uint32_t)PM_CONSTRAINT_COUNT);

            if (opMode != PM_RESOURCE_OFF)
            {
                switch (opMode)
                {
                    case PM_RESOURCE_FULL_ON:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.fullOnCounter <
                               ((1U << PM_FULL_ON_COUNTER_SIZE) - 1U));
                        s_pmHandle->resConstraintCount[rescShift].subConter.fullOnCounter++;
                        break;
                    }
                    case PM_RESOURCE_PARTABLE_ON2:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.partOn2Counter <
                               ((1U << PM_PARTABLE_ON2_COUNTER_SIZE) - 1U));
                        s_pmHandle->resConstraintCount[rescShift].subConter.partOn2Counter++;
                        break;
                    }
                    case PM_RESOURCE_PARTABLE_ON1:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.partOn1Counter <
                               ((1U << PM_PARTABLE_ON1_COUNTER_SIZE) - 1U));
                        s_pmHandle->resConstraintCount[rescShift].subConter.partOn1Counter++;
                        break;
                    }
                    default:
                    {
                        assert(false);
                        break;
                    }
                }
                /* Set corresponding bit of operate mode in system resource group. */
                s_pmHandle->sysRescGroup.groupSlice[rescShift / 8UL] |=
                    ((uint32_t)opMode << (4UL * ((uint32_t)rescShift % 8UL)));
                /* Enable corresponding bit of constraint in system resource mask. */
                s_pmHandle->resConstraintMask.rescMask[rescShift / 32UL] |= (1UL << ((uint32_t)rescShift % 32UL));
            }
        }
        va_end(ap);
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return ret;
}

/*!
 * brief Used to release constraints(including power mode constraint and resource constraints)
 *
 * For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3
 *  code
 *      PM_ReleaseConstraints(Sleep_Mode, 1, PM_RESC_1);
 *  endcode
 *
 * param powerModeConstraint The lowest power mode allowed, the power mode constraint macros
 *                            can be found in fsl_pm_device.h
 * param rescNum The number of resource constraints to be released.
 * return status_t The status of set constraints behavior.
 */
status_t PM_ReleaseConstraints(uint8_t powerModeConstraint, int32_t rescNum, ...)
{
    status_t ret = kStatus_Success;
    uint32_t opMode;
    uint32_t rescShift;
    int32_t inputResc;
    va_list ap;
    int32_t i;
    uint32_t curRescOpMode;
    uint32_t opModeToRelease;

    if (s_pmHandle->enterCritical != NULL)
    {
        s_pmHandle->enterCritical();
    }

    if (powerModeConstraint != PM_LP_STATE_NO_CONSTRAINT)
    {
        if (powerModeConstraint >= PM_LP_STATE_COUNT)
        {
            /* wrong power mode index passed in parameter */
            ret = kStatus_Fail;
        }
        else
        {
            /* Release power mode constraint */
            if (s_pmHandle->powerModeConstraintCount[powerModeConstraint] > 0U)
            {
                s_pmHandle->powerModeConstraintCount[powerModeConstraint]--;
            }
            PM_SetAllowedLowestPowerMode();
        }
    }
    else
    {
        /* No power mode constraint to release, only ressource constraints */
        ;
    }

    if (rescNum != 0)
    {
        va_start(ap, rescNum);

        for (i = 0; i < rescNum; i++)
        {
            inputResc = (int32_t)va_arg(ap, int32_t);
            PM_DECODE_RESC(inputResc);

            curRescOpMode   = s_pmHandle->sysRescGroup.groupSlice[rescShift / 8UL];
            opModeToRelease = ((uint32_t)opMode << (4UL * ((uint32_t)rescShift % 8UL)));
            if ((curRescOpMode & opModeToRelease) != 0UL)
            {
                uint8_t subCounterValue = 0U;
                switch (opMode)
                {
                    case PM_RESOURCE_FULL_ON:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.fullOnCounter >= 1U);
                        s_pmHandle->resConstraintCount[rescShift].subConter.fullOnCounter--;
                        subCounterValue = (s_pmHandle->resConstraintCount[rescShift].u8Count & PM_FULL_ON_COUNTER_MASK);
                        break;
                    }
                    case PM_RESOURCE_PARTABLE_ON2:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.partOn2Counter >= 1U);
                        s_pmHandle->resConstraintCount[rescShift].subConter.partOn2Counter--;
                        subCounterValue =
                            (s_pmHandle->resConstraintCount[rescShift].u8Count & PM_PARTABLE_ON2_COUNTER_MASK);
                        break;
                    }
                    case PM_RESOURCE_PARTABLE_ON1:
                    {
                        assert(s_pmHandle->resConstraintCount[rescShift].subConter.partOn1Counter >= 1U);
                        s_pmHandle->resConstraintCount[rescShift].subConter.partOn1Counter--;
                        subCounterValue =
                            (s_pmHandle->resConstraintCount[rescShift].u8Count & PM_PARTABLE_ON1_COUNTER_MASK);
                        break;
                    }
                    default:
                    {
                        assert(false);
                        break;
                    }
                }

                if (subCounterValue == 0U)
                {
                    /* Clear corresponding bit of operate mode in system resource group. */
                    s_pmHandle->sysRescGroup.groupSlice[rescShift / 8UL] &=
                        ~((uint32_t)opMode << (4UL * ((uint32_t)rescShift % 8UL)));
                    if (s_pmHandle->resConstraintCount[rescShift].u8Count == 0U)
                    {
                        /* Disable corresponding bit of constraint in system resource mask. */
                        s_pmHandle->resConstraintMask.rescMask[rescShift / 32UL] &=
                            ~(1UL << ((uint32_t)rescShift % 32UL));
                    }
                }
            }
        }
        va_end(ap);
    }

    if (s_pmHandle->exitCritical != NULL)
    {
        s_pmHandle->exitCritical();
    }

    return ret;
}

/*!
 * brief Get current system resource constraints.
 *
 * return Current system constraints.
 */
pm_resc_mask_t PM_GetResourceConstraintsMask(void)
{
    return s_pmHandle->resConstraintMask;
}

/*!
 * brief Get current system allowed power mode.
 *
 * return Allowed lowest power mode.
 */
uint8_t PM_GetAllowedLowestPowerMode(void)
{
    return s_pmHandle->powerModeConstraint;
}
