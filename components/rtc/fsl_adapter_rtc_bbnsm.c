/*
 * Copyright 2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_bbnsm.h"
#include "fsl_adapter_rtc.h"

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
typedef struct _hal_rtc_handle_struct_t
{
    uint8_t instance;
} hal_rtc_handle_struct_t;

static BBNSM_Type *const s_bbnsmBase[] = BBNSM_BASE_PTRS;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
hal_rtc_status_t HAL_RtcInit(hal_rtc_handle_t halRtcHandle, uint8_t instance)
{
    bbnsm_rtc_config_t bbnsmConfig;
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;

    assert(halRtcHandle);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    halRtcState->instance = instance;
    BBNSM_RTC_GetDefaultConfig(&bbnsmConfig);
    BBNSM_RTC_Init(s_bbnsmBase[instance], &bbnsmConfig);

    return kStatus_HAL_RtcSuccess;
}

/*! -------------------------------------------------------------------------
 * @brief   DeInitialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
void HAL_RtcDeinit(hal_rtc_handle_t halRtcHandle)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;

    assert(halRtcHandle);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));
    BBNSM_RTC_Deinit(s_bbnsmBase[halRtcState->instance]);
}
/*! -------------------------------------------------------------------------
 * \brief     Sets the absolute time.
 * \param[in] microseconds - Time in microseconds.
 *---------------------------------------------------------------------------*/
hal_rtc_status_t HAL_RtcSetTime(hal_rtc_handle_t halRtcHandle, uint64_t microseconds)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t seconds                     = (uint32_t)(microseconds / SECOND_TO_MICROSECOND);

    assert(halRtcHandle);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));
    BBNSM_RTC_SetSeconds(s_bbnsmBase[halRtcState->instance], seconds);

    return kStatus_HAL_RtcSuccess;
}

/*! -------------------------------------------------------------------------
 * \brief     Gets the absolute time.
 * \param[in] microseconds - Time in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t HAL_RtcGetTime(hal_rtc_handle_t halRtcHandle)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    return (uint64_t)BBNSM_RTC_GetSeconds(s_bbnsmBase[halRtcState->instance]) * SECOND_TO_MICROSECOND;
}
/*! -------------------------------------------------------------------------
 * \brief     Sets the alarm absolute time in seconds.
 * \param[in] microseconds - Time in seconds for the alarm.
 *---------------------------------------------------------------------------*/
hal_rtc_status_t HAL_RtcSetAlarm(hal_rtc_handle_t halRtcHandle, uint64_t microseconds)
{
    uint32_t seconds                     = (uint32_t)(microseconds / SECOND_TO_MICROSECOND);
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    /* Set alarm time in seconds */
    return (hal_rtc_status_t)BBNSM_RTC_SetAlarm(s_bbnsmBase[halRtcState->instance], seconds);
}

uint64_t HAL_RtcGetAlarm(hal_rtc_handle_t halRtcHandle)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    return BBNSM_RTC_GetAlarm(s_bbnsmBase[halRtcState->instance]) * SECOND_TO_MICROSECOND;
}

uint32_t HAL_RtcGetEnabledInterrupts(hal_rtc_handle_t halRtcHandle)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t bbnsm_flags                 = 0U;
    uint32_t flags                       = 0U;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    bbnsm_flags = BBNSM_GetEnabledInterrupts(s_bbnsmBase[halRtcState->instance]);
    if ((bbnsm_flags & (uint32_t)kBBNSM_RTC_AlarmInterrupt) != 0x0U)
        flags |= (uint32_t)kHAL_RTC_AlarmInterrupt;

    return flags;
}

uint32_t HAL_RtcGetStatusFlags(hal_rtc_handle_t halRtcHandle)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t bbnsm_flags                 = 0U;
    uint32_t flags                       = 0U;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    bbnsm_flags = BBNSM_GetStatusFlags(s_bbnsmBase[halRtcState->instance]);
    if ((bbnsm_flags & (uint32_t)kBBNSM_RTC_AlarmInterruptFlag) != 0x0U)
        flags |= (uint32_t)kHAL_RTC_AlarmInterruptFlag;

    return flags;
}

void HAL_RtcClearStatusFlags(hal_rtc_handle_t halRtcHandle, uint32_t flags)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t bbnsm_flags                 = 0U;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    if ((flags & (uint32_t)kHAL_RTC_AlarmInterruptFlag) != 0x0U)
        bbnsm_flags |= (uint32_t)kBBNSM_RTC_AlarmInterruptFlag;

    BBNSM_ClearStatusFlags(s_bbnsmBase[halRtcState->instance], bbnsm_flags);
}

void HAL_RtcEnableInterrupts(hal_rtc_handle_t halRtcHandle, uint32_t flags)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t bbnsm_flags                 = 0U;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    if ((flags & (uint32_t)kHAL_RTC_AlarmInterrupt) != 0x0U)
        bbnsm_flags |= (uint32_t)kBBNSM_RTC_AlarmInterruptFlag;

    BBNSM_EnableInterrupts(s_bbnsmBase[halRtcState->instance], bbnsm_flags);
}

void HAL_RtcDisableInterrupts(hal_rtc_handle_t halRtcHandle, uint32_t flags)
{
    hal_rtc_handle_struct_t *halRtcState = halRtcHandle;
    uint32_t bbnsm_flags                 = 0U;

    assert(halRtcState);
    assert(halRtcState->instance < (sizeof(s_bbnsmBase) / sizeof(s_bbnsmBase[0])));

    if ((flags & (uint32_t)kHAL_RTC_AlarmInterrupt) != 0x0U)
        bbnsm_flags |= (uint32_t)kBBNSM_RTC_AlarmInterrupt;

    BBNSM_DisableInterrupts(s_bbnsmBase[halRtcState->instance], bbnsm_flags);
}
