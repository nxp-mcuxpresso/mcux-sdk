/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TIMER_STAMP_H_
#define _TIMER_STAMP_H_

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
***********************************************************************************/
#include "fsl_common.h"
#if defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#endif

/************************************************************************************
*************************************************************************************
* Public types
*************************************************************************************
************************************************************************************/
/*! @brief HAL timer configuration structure for HAL time stamp setting. */
typedef struct _hal_time_stamp_config
{
    uint32_t srcClock_Hz; /*!< Source clock of the timer */
    uint8_t  instance;    /*!< Hardware timer module instance, for example: if you want use FTM0,then the instance is configured to 0, if
                               you want use FTM2 hardware timer, then configure the instance to 2, detail information please refer to the
                               SOC corresponding RM.Invalid instance value will cause initialization failure. */
#if (defined(TM_ENABLE_TIME_STAMP_CLOCK_SELECT) && (TM_ENABLE_TIME_STAMP_CLOCK_SELECT > 0U))
    uint8_t clockSrcSelect;     /*!< Select clock source. It is just for lptmr timer clock select, if the lptmr does not
                                      want to use the default clock source*/
#endif
} hal_time_stamp_config_t;

/*! @brief Definition of time stamp adapter handle size. */
#define HAL_TIME_STAMP_HANDLE_SIZE                (8U)

/*!
 * @brief Defines the time stamp handle
 *
 * This macro is used to define a 4 byte aligned time stamp handle.
 * Then use "(hal_time_stamp_handle_t)name" to get the time stamp handle.
 *
 * The macro should be global and could be optional. You could also define time stamp handle by yourself.
 *
 * This is an example,
 * @code
 * TIME_STAMP_HANDLE_DEFINE(timeStampHandle);
 * @endcode
 *
 * @param name The name string of the time stamp handle.
 */
#define TIME_STAMP_HANDLE_DEFINE(name) uint32_t name[((HAL_TIME_STAMP_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

typedef void* hal_time_stamp_handle_t;
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes the timer Stamp adapter module for a timer basic operation.
 *
 * @note This API should be called at the beginning of the application using the time stamp adapter.
 * For Initializes time stamp adapter,
 *  @code
 *   TIME_STAMP_HANDLE_DEFINE(halTimeStampHandle);
 *   hal_time_stamp_config_t halTimeStampConfig;
 *   halTimeStampConfig.srcClock_Hz = BOARD_GetTimeSrcClock();
 *   halTimeStampConfig.instance = 0;
 *   HAL_TimeStampInit(((hal_time_stamp_handle_t) halTimeStampHandle, &halTimerConfig);
 *  @endcode
 *
 * @param halTimeStampHandle HAL time stamp adapter handle, the handle buffer with size #HAL_TIME_STAMP_HANDLE_SIZE
 * should be allocated at upper level.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #TIME_STAMP_HANDLE_DEFINE(halTimeStampHandle);
 * or
 * uint32_t halTimeStampHandle[((HAL_TIME_STAMP_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param halTimeStampConfig A pointer to the HAL time stamp configuration structure
 */
void HAL_TimeStampInit(hal_time_stamp_handle_t halTimeStampHandle, hal_time_stamp_config_t* halTimeStampConfig);

/*!
 * @brief Get the absolute time at the moment of the call.
 *
 * @param halTimerHandle     HAL timer adapter handle
 * @retval the absolute time(microsecond) at the moment of the call
 */
uint64_t HAL_GetTimeStamp(hal_time_stamp_handle_t halTimeStampHandle);

/*!
 * @brief Timer stamp adapter power up function.
 *
 * @note This API should be called by low power module when system exit from sleep mode.
 *
 * @param halTimerHandle     HAL timer adapter handle
 */
void HAL_TimeStampExitLowpower(hal_time_stamp_handle_t halTimeStampHandle);

/*!
 * @brief Timer stamp adapter power down function.
 *
 * @note This API should be called by low power module before system enter into sleep mode.
 *
 * @param halTimerHandle     HAL timer adapter handle
 */
void HAL_TimeStampEnterLowpower(hal_time_stamp_handle_t halTimeStampHandle);
#if defined(__cplusplus)
}
#endif
/*! @}*/
#endif /* _TIMER_STAMP_H_ */
