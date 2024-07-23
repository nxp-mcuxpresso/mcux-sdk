/*
 * Copyright 2021-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PM_CORE_H_
#define _FSL_PM_CORE_H_

#include "fsl_common.h"
#include "fsl_component_generic_list.h"

#include "fsl_pm_config.h"

/*!
 * @defgroup PM Framework: Power Manager Framework
 * @details This document consists of sections titled with <b>Framework Overview</b>, <b>Data Structures</b>,
 *          <b>Enumerations</b>, <b>Functions</b>, etc., each with an overview list and detailed documentation.
 *          It is recommended to read the <b>Framework Overview</b> first for it includes a comprehensive description
 *          of the framework. Other sections give detailed information for APIs, enums, macros, etc., for your further
 *          reference.
 * @{
 */

/*******************************************************************************
 * Introducation of power manager framework
 ******************************************************************************/
/*!
 * Framework Overview
 * ==================
 * The power manager framework manages the transition of both active-to-sleep and sleep-to-active states of the MCU. It
 * provides the upper layer software the ability to set and release constraints of the hardware basic
 * resources(such as clock, power, ram, etc.) and the ability to register callback
 * functions to be invoked before entering/after exiting the sleep mode. In addition, the upper layer software
 * can register the wakeup source service function to be executed if related wakeup source occurs.
 *
 *              +-----------------------------------------------------------------+
 *              |                       Application Software                      |
 *              +-----------------------------------------------------------------+
 *              +-----------------------------------------------------------------+
 *              |                       Stacks and Components                     |
 *              +-----------------------------------------------------------------+
 *              +-----------------------------------------------------------------+
 *              |                       Power Manager Framework                   |
 *              +-----------------------------------------------------------------+
 *              +---------------+    +---------------+    +-----------------------+
 *              | Power Drivers |    | Clock Drivers |    | Wakeup Source Drivers |
 *              +---------------+    +---------------+    +-----------------------+
 *
 * As shown above, the power manager framework safely manages the transitions to and from power saving states by using
 * MCUXpresso SDK drivers, and the upper layer software only need to use the APIs of power manager framework. Different
 * MCUs have the same top-level APIs, concepts and conventions.
 *
 * Definitions and Terms:
 * ======================
 *  - \b Constraint\n
 *      A system-level declaration that asks the power manager to prevent a specific action. For
 *      example, if the application sets the constraint as that the ARM PLL should not be turned off, then the power
 * manager framework will compute the deepest power state with the ARM PLL being turned on. Otherwise, a decision might
 * be made to transit to a sleep state with ARM PLL being turned off.
 *
 *  - \b Notification\n
 *      A callback mechanism that allows the upper layer software to be notified of specific power
 *      transitions. Some hardware peripherals may need several steps to enter into or exit the low power mode, so
 * multiple callbacks are necessary to avoid undesired waiting loop. To address this problem, there are 3 groups of
 * notification set in the power manager framework. The power manager will execute registered notification callback
 * functions from group0 to group2 before entering into low power mode while from group2 to group0 after exiting from
 * low power mode.
 *
 *  - \b Wakeup \b Source\n
 *      Structure that contains the wakeup source Id and its service functions. The upper layer software
 *      can create the wakeup source object by invoking PM_RegisterWakeupSource() function. The parameter \b wsId is
 *      the MCU wakeup source definition available. If the MCU exits from the low power mode based on the registered
 *      wakeup source, the function PM_TriggerWakeSourceService() should be invoked to execute wakeup source service
 *      function.
 *
 * Power Manager Framework Architecture:
 * =====================================
 *  The power manager framework consists of four modules: policy module, sequencer module, wakeup source
 *  manager module, and notification module.
 *  - The policy module can gather all the constraints from the whole system and then compute the deepest allowed power
 *  state.
 *  - The sequencer module is in charge of the power mode entry and exit sequences.
 *  - The wakeup source manager module is in charge of configuring wakeup sources in low power entry and processing
 *  registered wakeup source handler callback.
 *  - The notification module is in charge of notifying the upper layer software of speciic power transitions and
 * events.
 *
 *  To make the power manager framework adapts to different MCU families, the power manager framework adopts a
 * layer-designed idea, extracting common parts as the pm_core level, and separating device-related parts as the
 * pm_device level. In details, the pm_core level contains policy module, wakeup source manager module, and notification
 * module. The pm_device level contains sequencer module.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (defined(FSL_PM_SUPPORT_ALWAYS_ON_SECTION) && FSL_PM_SUPPORT_ALWAYS_ON_SECTION)
/*! @name Always On Region */
#if (defined(__ICCARM__))
#define AT_ALWAYS_ON_DATA(var)      var @"AlwaysOnData"
#define AT_ALWAYS_ON_DATA_INIT(var) var @"AlwaysOnData.init"
#elif (defined(__CC_ARM) || defined(__ARMCC_VERSION))
#define AT_ALWAYS_ON_DATA(var)      __attribute__((section(".bss.AlwaysOnData"))) var
#define AT_ALWAYS_ON_DATA_INIT(var) __attribute__((section("AlwaysOnData.init"))) var
#elif (defined(__GNUC__))
#define AT_ALWAYS_ON_DATA(var)      __attribute__((section(".AlwaysOnData"))) var
#define AT_ALWAYS_ON_DATA_INIT(var) __attribute__((section(".AlwaysOnData.init"))) var
#else
#error Toolchain not supported.
#endif /* defined(__ICCARM__) */
#else
#define AT_ALWAYS_ON_DATA(var)      var
#define AT_ALWAYS_ON_DATA_INIT(var) var
/*! @} */
#endif /* FSL_PM_SUPPORT_ALWAYS_ON_SECTION */

/*!
 * @brief Power manager status.
 * @anchor _pm_status
 */
enum
{
    kStatus_PMSuccess                  = kStatus_Success,
    kStatus_PMFail                     = kStatus_Fail,
    kStatus_PMWakeupSourceEnableError  = MAKE_STATUS(kStatusGroup_POWER_MANAGER, 1U),
    kStatus_PMWakeupSourceDisableError = MAKE_STATUS(kStatusGroup_POWER_MANAGER, 2U),
    kStatus_PMWakeupSourceServiceBusy  = MAKE_STATUS(kStatusGroup_POWER_MANAGER, 3U),
    kStatus_PMPowerStateNotAllowed     = MAKE_STATUS(kStatusGroup_POWER_MANAGER, 4U),
    kStatus_PMNotifyEventError         = MAKE_STATUS(kStatusGroup_POWER_MANAGER, 5U),
};

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
/*!
 * @brief Power manager event type, used in notification module to inform the upper layer software
 * of the power transition event.
 */
typedef enum _pm_event_type
{
    kPM_EventEnteringSleep = 0U, /*!< Entering a sleep state. */
    kPM_EventExitingSleep,       /*!< Exiting a sleep state. */
} pm_event_type_t;

/*!
 * @brief The enumeration of notification group.
 */
typedef enum _pm_notify_group
{
    kPM_NotifyGroup0 =
        0U,           /*!< Notify group0, before entering power state the notifiers in group0 are executed firstly. */
    kPM_NotifyGroup1, /*!< Notify group1. */
    kPM_NotifyGroup2, /*!< Notify group2, after exiting power state the notifiers in group2 are executed firstly. */
} pm_notify_group_t;

/*!
 * @brief Power manager notify callback function used with the PM_RegisterNotify() API.
 *
 * @param eventType Identify the type of power event.
 * @param powerState The power state which will enter into, actually it is the index of states array
 * in @ref pm_device_option_t structure.
 * @param data      Pointer to a custom argument.
 */
typedef status_t (*pm_notify_callback_func_t)(pm_event_type_t eventType, uint8_t powerState, void *data);

/*!
 * @brief Power manager notify object structure.
 */
typedef struct _pm_notify_element
{
    list_element_t link;                      /*!< For placing on the notify list. */
    pm_notify_callback_func_t notifyCallback; /*!< Registered notification callback function.  */
    void *data;                               /*!< Pointer to a custom argument. */
} pm_notify_element_t;

#endif /* FSL_PM_SUPPORT_NOTIFICATION */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
/*!
 * @brief Wakeup source service function used with PM_RegisterWakeupSource() function.
 */
typedef void (*pm_wake_up_source_service_func_t)(void);

/*!
 * @brief Wakeup source object structure.
 *
 * In PM_RegisterWakeupSource(), the wakeup source object in this structure type is allocated from the heap.
 * In PM_UnregisterWakeupSource(), the wakeup source object in this structure type is destoried from the heap.
 */
typedef struct _pm_wakeup_source
{
    list_element_t link; /*!< For placing on the wake up source list. */
    uint32_t wsId; /*!< The wakeup source id that the MCU supports, this value is used to config wakeup source manager
                      hardware peripheral. NXP will provided wakeup source id for each specific MCU. */
    pm_wake_up_source_service_func_t service; /*! Wakeup source service function that should be executed if the
                                    corresponding wakeup event occurred. */
    bool enabled : 1U;                        /*!< Enable/disable wakeup source. */
    bool active : 1U;                         /*!< Indicate whether the corresponding wakeup event occurs. */
} pm_wakeup_source_t;
#endif                                        /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*!
 * @brief The definition of Power manager resource constraint group, the group contains the operation mode of each
 * constraint.
 */
typedef struct _pm_resc_group
{
    uint32_t groupSlice[PM_RESC_GROUP_ARRAY_SIZE]; /*!< The resource constraint group. */
} pm_resc_group_t;

/*!
 * @brief The definition of power manager resource constraint mask.
 */
typedef struct _pm_resc_mask
{
    uint32_t rescMask[PM_RESC_MASK_ARRAY_SIZE]; /*!< The resource constraint mask. */
} pm_resc_mask_t;

/*!
 * @brief The counter of resource's power mode.
 * @note The counter is consist of 3 sub-counter.
 */
typedef union _pm_resc_opMode_counter
{
    uint8_t u8Count;
    struct _subCounter
    {
        uint8_t partOn1Counter : PM_PARTABLE_ON1_COUNTER_SIZE;
        uint8_t partOn2Counter : PM_PARTABLE_ON2_COUNTER_SIZE;
        uint8_t fullOnCounter : PM_FULL_ON_COUNTER_SIZE;
    } subConter;
} pm_resc_opMode_counter_t;

/*!
 * @brief The abstraction of MCU power state.
 */
typedef struct _pm_state
{
    uint32_t exitLatency;              /*!< The latency that the power state need to exit, in us */
    pm_resc_mask_t fixConstraintsMask; /*!< Some constraints that must be satisfied in the power state. */
    pm_resc_mask_t varConstraintsMask; /*!< Some optional and configurable constraints. */
} pm_state_t;

/*!
 * @brief Device power related options., including power states array, power state counts.
 *
 */
typedef struct _pm_device_option
{
    pm_state_t states[PM_LP_STATE_COUNT]; /*!< The array of device's power state, states array must be ordered in
                                            decreasing power consumption. */
    uint8_t stateCount;                   /*!< The counts of device's power state. */
    void (*prepare)(void);                /*!< prepare for power state transition */
    void (*enter)(uint8_t powerState,
                  pm_resc_mask_t *pSoftRescMask,
                  pm_resc_group_t *pSysRescGroup); /*!< enter power state */
    void (*clean)(void);                           /*!< clean after power state transition */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    status_t (*manageWakeupSource)(pm_wakeup_source_t *ws, bool enable); /*!< The function used to enable/disable
                                                                             wakeup source, this function is
                                                                             implemented in pm_device level. */
    bool (*isWakeupSource)(
        pm_wakeup_source_t *ws); /*!< Used to know if the wake up source triggered the last wake up. */
#endif                           /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */
} pm_device_option_t;

#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
typedef void (*pm_low_power_timer_start_func_t)(uint64_t timeout);
typedef void (*pm_low_power_timer_stop_func_t)(void);
typedef uint64_t (*pm_low_power_timer_get_timestamp_func_t)(void);
typedef uint64_t (*pm_low_power_timer_get_duration_func_t)(uint64_t entryTimestamp, uint64_t exitTimestamp);
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

typedef void (*pm_enter_critical)(void);
typedef void (*pm_exit_critical)(void);

/*!
 * @brief Handle structure for power manager.
 *
 */
typedef struct _pm_handle
{
    bool enable;                      /*!< Enable/disable power manager. */
    int8_t disableCount;              /*!< Used to support nested call to PM_EnablePowerManager. */
    pm_device_option_t *deviceOption; /*!< Pointer to device specific power option. */
    uint8_t targetState;              /*!< The target power state computed by the policy, actually it is the
                                           index in device states array. */

    pm_resc_mask_t resConstraintMask; /*!< Current system's resource constraint mask. */
    pm_resc_mask_t softConstraints;   /*!< Current system's optional resource constraint mask. */
    pm_resc_opMode_counter_t resConstraintCount[PM_CONSTRAINT_COUNT]; /*!< The count of each resource constraint,
                                                    if the constraint's count is 0, it means the system has
                                                    removed that contraint. */

    pm_resc_group_t sysRescGroup;                        /*!< Current system's resource constraint group. */

    uint8_t powerModeConstraint;                         /*!< Used to store system allowed lowest power mode. */
    uint8_t powerModeConstraintCount[PM_LP_STATE_COUNT]; /*!< The count of each power mode constraint. */

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
    list_label_t notifyList[3U];           /*!< The header of 3 group notification. */
    pm_notify_group_t curNotifyGroup;      /*!< Store current notification group. */
    pm_notify_element_t *curNotifyElement; /*!< Store current notification element. */
#endif                                     /* FSL_PM_SUPPORT_NOTIFICATION */

#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
    pm_low_power_timer_start_func_t timerStart; /*!< If RTOS supports tickless, start low power timer before entering
                                                     low power mode. */
    pm_low_power_timer_stop_func_t timerStop; /*!< If RTOS supports tickless, stop low power timer after waking up from
                                                   low power mode. */
    pm_low_power_timer_get_timestamp_func_t getTimestamp; /*!< This function is used to get a timestamp before and after
                                                               low power mode to be able to compute the duration */
    pm_low_power_timer_get_duration_func_t
        getTimerDuration;                                 /*!< This function can be used to retrun the actual
                                                               low power duration based on the entry/exit timestamps */
    uint64_t entryTimestamp;
    uint64_t exitTimestamp;
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    list_label_t wakeupSourceList;
#endif                               /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

    pm_enter_critical enterCritical; /* Power manager critical entry function, default set as NULL. */
    pm_exit_critical exitCritical;   /* Power manager critical exit function, default set as NULL. */
} pm_handle_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Power Manager Policy
 * @{
 */

/*!
 * @brief Initialize the power manager handle, this function should be invoked before using other power manager
 * APIs.
 *
 * @note In default, the power manager is disabled.
 *
 * @param handle Pointer to the @ref pm_handle_t structure, upper layer software should pre-allocate the handle global
 * variable.
 */
void PM_CreateHandle(pm_handle_t *handle);

/*!
 * @brief Enable/disable power manager functions.
 *
 * @param enable Used to enable/disable power manager functions.
 */
void PM_EnablePowerManager(bool enable);

/*!
 * @brief Power manager core API, this API should be used on RTOS's IDLE task.
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
 * @param duration The time in low power mode, this value is calculate from RTOS API.
 */
void PM_EnterLowPower(uint64_t duration);

#if (defined(FSL_PM_SUPPORT_LP_TIMER_CONTROLLER) && FSL_PM_SUPPORT_LP_TIMER_CONTROLLER)
/*!
 * @brief Register timer controller related functions to power manager.
 *
 * If low power timer is the wakeup source, please remember to register it into power manager by using
 * PM_RegisterWakeupSource() function.
 *
 * @param handle Pointer to the @ref pm_handle_t structure
 * @param timerStart Low power timer start function, this parameter can be NULL, and it means low power timer is not set
 *  as the wakeup source.
 * @param timerStop Low power timer stop function, this parameter can also be set as NULL.
 * @param timerSync Low power timer sync function, this parameter can also be set as NULL.
 * @param getTimestamp Low power timestamp function, this parameter can also be set as NULL.
 * @param getTimerDuration Get timer duration function. this parameter can also be set as NULL.
 */
void PM_RegisterTimerController(pm_handle_t *handle,
                                pm_low_power_timer_start_func_t timerStart,
                                pm_low_power_timer_stop_func_t timerStop,
                                pm_low_power_timer_get_timestamp_func_t getTimestamp,
                                pm_low_power_timer_get_duration_func_t getTimerDuration);

/*!
 * @brief Get the actual low power state duration.
 */
uint64_t PM_GetLastLowPowerDuration(void);
#endif /* FSL_PM_SUPPORT_LP_TIMER_CONTROLLER */

/*!
 * @brief Register critical region related functions to power manager.
 *
 * @note There are multiple-methods to implement critical region(E.g. interrupt controller, locker, semaphore).
 *
 * @param handle Pointer to the @ref pm_handle_t structure
 * @param criticalEntry Enter critical function to register.
 * @param criticalExit  Exit critical function to register.
 */
void PM_RegisterCriticalRegionController(pm_handle_t *handle,
                                         pm_enter_critical criticalEntry,
                                         pm_exit_critical criticalExit);

/*! @} */

#if (defined(FSL_PM_SUPPORT_NOTIFICATION) && FSL_PM_SUPPORT_NOTIFICATION)
/*!
 * @name Notification Module Interfaces
 * @{
 */

/*!
 * @brief Register notify element into the selected group.
 *
 * @param groupId The group of the notify list, this will affect the execution sequence.
 * @param notifyElement The pointer to @ref pm_notify_element_t.
 * @return status_t The status of register notify object behavior.
 */
status_t PM_RegisterNotify(pm_notify_group_t groupId, pm_notify_element_t *notifyElement);

/*!
 * @brief Update notify element's callback function and application data.
 *
 * @param notifyElement The pointer to the notify element to update.
 * @param callback The callback function to be updated.
 * @param data Pointer to the callback function private data.
 */
void PM_UpdateNotify(void *notifyElement, pm_notify_callback_func_t callback, void *data);

/*!
 * @brief Remove notify element from its notify group.
 *
 * @param notifyElement The pointer to the notify element to remove.
 */
status_t PM_UnregisterNotify(void *notifyElement);

/*! @} */
#endif /* FSL_PM_SUPPORT_NOTIFICATION */

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
/*!
 * @name Wakeup Source Manager Interfaces
 * @{
 */

/*!
 * @brief Initialize the wakeup source object.
 *
 * @param ws    Pointer to the @ref pm_wakeup_source_t variable.
 * @param wsId  Used to select the wakeup source, the wsId of each wakeup source can be found in fsl_pm_device.h
 * @param service The function to be invoked when wake up source asserted.
 * @param enable Used to enable/disable the selected wakeup source.
 */
void PM_InitWakeupSource(pm_wakeup_source_t *ws, uint32_t wsId, pm_wake_up_source_service_func_t service, bool enable);

/*!
 * @brief Enable wakeup source.
 *
 * @param ws Pointer to the wakeup source object to be enabled.
 * @return status_t The status of enable wakeup source behavior.
 */
status_t PM_EnableWakeupSource(pm_wakeup_source_t *ws);

/*!
 * @brief Disable wakeup source
 *
 * @param ws Pointer to the wakeup source object to be disabled.
 * @return status_t The status of disable wakeup source behavior.
 */
status_t PM_DisableWakeupSource(pm_wakeup_source_t *ws);

/*!
 * @brief Checks if any enabled wake up source is responsible for last wake up
 *       event. In such case, it will call the wake up source callback if it
 *       has been registered. Likely to be called from Wake Up Unit IRQ Handler.
 *
 * @return status_t The status of handling the wake up event.
 */
status_t PM_HandleWakeUpEvent(void);

/*!
 * @brief If the specfic wakeup event occurs, invoke this API to execute its service function.
 *
 * @param ws Pointer to the wakeup source object.
 * @return status_t The status of trigger wakeup source behavior.
 */
status_t PM_TriggerWakeSourceService(pm_wakeup_source_t *ws);
/*! @} */
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*!
 * @name Constraints Interfaces
 * @{
 */

/*!
 * @brief Used to set constraints(including power mode constraint and resource constraints)
 *
 * For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3
 *  @code
 *      PM_SetConstraints(Sleep_Mode, 3, PM_RESC_1, PM_RESC_2, PM_RESC_3);
 *  @endcode
 *
 * @param powerModeConstraint The lowest power mode allowed, the power mode constraint macros
 *                            can be found in fsl_pm_device.h
 * @param rescNum The number of resource constraints to be set.
 * @return status_t The status of set constraints behavior.
 */
status_t PM_SetConstraints(uint8_t powerModeConstraint, int32_t rescNum, ...);

/*!
 * @brief Used to release constraints(including power mode constraint and resource constraints)
 *
 * For example, if the device support 3 resource constraints: PM_RESC_1, PM_RESC_2, PM_RESC3
 *  @code
 *      PM_ReleaseConstraints(Sleep_Mode, 1, PM_RESC_1);
 *  @endcode
 *
 * @param powerModeConstraint The lowest power mode allowed, the power mode constraint macros
 *                            can be found in fsl_pm_device.h
 * @param rescNum The number of resource constraints to be released.
 * @return status_t The status of set constraints behavior.
 */
status_t PM_ReleaseConstraints(uint8_t powerModeConstraint, int32_t rescNum, ...);

/*!
 * @brief Get current system resource constraints.
 *
 * @return Current system constraints.
 */
pm_resc_mask_t PM_GetResourceConstraintsMask(void);

/*!
 * @brief Get current system allowed power mode.
 *
 * @return Allowed lowest power mode.
 */
uint8_t PM_GetAllowedLowestPowerMode(void);

/*! @} */

#if defined(__cplusplus)
}
#endif
/*!
 * @}
 */

#endif /* _FSL_PM_CORE_H_ */
