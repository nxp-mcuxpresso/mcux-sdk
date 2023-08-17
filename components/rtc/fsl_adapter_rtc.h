/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTC_H_
#define _RTC_H_

#define SECOND_TO_MICROSECOND (1000000ULL)

/*!
 * @addtogroup RTC_Adapter
 * @{
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
***********************************************************************************/

/************************************************************************************
*************************************************************************************
* Public types
*************************************************************************************
************************************************************************************/

/*! @brief Hal rtc status. */
typedef enum _hal_rtc_status
{
    kStatus_HAL_RtcSuccess = kStatus_Success, /*!< Success */
    kStatus_HAL_RtcFail    = kStatus_Fail,    /*!< Failure*/
} hal_rtc_status_t;

typedef enum _hal_rtc_interrupts
{
    kHAL_RTC_AlarmInterrupt    = 1U << 0U,
    kHAL_RTC_RolloverInterrupt = 1U << 1U,
} hal_rtc_interrupts_t;

typedef enum _hal_rtc_status_flags
{
    kHAL_RTC_AlarmInterruptFlag    = 1U << 0U,
    kHAL_RTC_RolloverInterruptFlag = 1U << 1U,
} hal_rtc_status_flags_t;

/*! @brief Hal rtc handle size. */
#define HAL_RTC_HANDLE_SIZE (8U)

/*!
 * @brief Defines the RTC handle
 *
 * This macro is used to define a 4 byte aligned rtc handle.
 * Then use "(hal_rtc_handle_t)name" to get the rtc handle.
 *
 * The macro should be global and could be optional. You could also define RTC handle by yourself.
 *
 * This is an example,
 * @code
 *   HAL_RTC_HANDLE_DEFINE(rtcHandle);
 * @endcode
 *
 * @param name The name string of the RTC handle.
 */
#define HAL_RTC_HANDLE_DEFINE(name) uint32_t name[(HAL_RTC_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t)]

/*! @brief Hal rtc handle. */
typedef void *hal_rtc_handle_t;

/*! @brief The callback function of rtc */
typedef void (*hal_rtc_callback_t)(void *param);

/*
 * @brief   Enable/Disable RTC API
 * VALID RANGE: TRUE/FALSE
 */
#ifndef RTC_FUNCTIONS_ENABLE
#define RTC_FUNCTIONS_ENABLE (0)
#endif

#ifndef RTC_LEGACY_FUNCTION_PROTOTYPE
#define RTC_LEGACY_FUNCTION_PROTOTYPE (0)
#endif

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#if (defined(RTC_LEGACY_FUNCTION_PROTOTYPE) && (RTC_LEGACY_FUNCTION_PROTOTYPE > 0))

/*! -------------------------------------------------------------------------
 * @brief   initialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
void HAL_RTCInit(void);

/*! -------------------------------------------------------------------------
 * @brief   Returns the absolute time at the moment of the call.
 * @return  Absolute time at the moment of the call in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t HAL_RTCGetTimestamp(void);

#endif

#if (defined(RTC_FUNCTIONS_ENABLE) && (RTC_FUNCTIONS_ENABLE > 0))

/*! -------------------------------------------------------------------------
 * @brief     Sets the absolute time.
 * @param[in] microseconds
 *---------------------------------------------------------------------------*/
void HAL_RTCSetTime(uint64_t microseconds);

/*! -------------------------------------------------------------------------
 * @brief     Sets the alarm absolute time in microseconds.
 * @param[in] microseconds Time in microseconds for the alarm.
 * @param[in] callback function pointer.
 * @param[in] param Parameter for callback.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetAlarm(uint64_t microseconds, hal_rtc_callback_t callback, void *param);

/*! -------------------------------------------------------------------------
 * @brief     Sets the alarm relative time in seconds.
 * @param[in] seconds number of seconds until the alarm.
 * @param[in] callback function pointer.
 * @param[in] param Parameter for callback.
 *---------------------------------------------------------------------------*/
void HAL_RTCSetAlarmRelative(uint32_t seconds, hal_rtc_callback_t callback, void *param);
#endif /* RTC_FUNCTIONS_ENABLE */
/*! @}*/

/*! -------------------------------------------------------------------------
 * @brief   initialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
hal_rtc_status_t HAL_RtcInit(hal_rtc_handle_t halRtcHandle, uint8_t instance);

/*! -------------------------------------------------------------------------
 * @brief   DeInitialize the RTC part of the timer module
 *---------------------------------------------------------------------------*/
void HAL_RtcDeinit(hal_rtc_handle_t halRtcHandle);

/*! -------------------------------------------------------------------------
 * @brief     Set the absolute time.
 * @param[in] microseconds
 *---------------------------------------------------------------------------*/
hal_rtc_status_t HAL_RtcSetTime(hal_rtc_handle_t halRtcHandle, uint64_t microseconds);

/*! -------------------------------------------------------------------------
 * @brief     Get the absolute time.
 * @param[in] microseconds
 *---------------------------------------------------------------------------*/
uint64_t HAL_RtcGetTime(hal_rtc_handle_t halRtcHandle);

/*! -------------------------------------------------------------------------
 * @brief     Set the alarm absolute time in microseconds.
 * @param[in] microseconds Time in microseconds for the alarm.
 *---------------------------------------------------------------------------*/
hal_rtc_status_t HAL_RtcSetAlarm(hal_rtc_handle_t halRtcHandle, uint64_t microseconds);

/*! -------------------------------------------------------------------------
 * @brief     Get the alarm absolute time in microseconds.
 *---------------------------------------------------------------------------*/
uint64_t HAL_RtcGetAlarm(hal_rtc_handle_t halRtcHandle);

uint32_t HAL_RtcGetStatusFlags(hal_rtc_handle_t halRtcHandle);

void HAL_RtcClearStatusFlags(hal_rtc_handle_t halRtcHandle, uint32_t flags);

uint32_t HAL_RtcGetEnabledInterrupts(hal_rtc_handle_t halRtcHandle);

void HAL_RtcEnableInterrupts(hal_rtc_handle_t halRtcHandle, uint32_t flags);

void HAL_RtcDisableInterrupts(hal_rtc_handle_t halRtcHandle, uint32_t flags);

/*! @}*/

#endif /* _RTC_H_ */
