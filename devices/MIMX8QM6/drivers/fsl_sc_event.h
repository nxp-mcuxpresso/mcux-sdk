/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SC_EVENT_H_
#define _FSL_SC_EVENT_H_

#include "fsl_common.h"
#include "svc/irq/irq_api.h"
#include "svc/pad/pad_api.h"

/*!
 * @addtogroup sc_event_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Group interrupt driver version for SDK */
#define FSL_SC_EVENT_DRIVER_VERSION (MAKE_VERSION(2, 0, 1)) /*!< Version 2.0.1. */
/*@}*/

/*! @brief The SC Event handler memory pool size in bytes. */
#ifndef SC_EVENT_HANDLER_MEM_POOL_SIZE
#define SC_EVENT_HANDLER_MEM_POOL_SIZE (200U)
#endif

/*! 
 * @brief The SYSCTR SC Event maybe used as wakeup source in low power applications.
 * Such as in LPM module(lpm.c), the SYSCTR is used as wakeup source in tickless idle.
 */
#ifndef SC_EVENT_USE_SYSCTR
#define SC_EVENT_USE_SYSCTR (0)
#endif

#define SC_EVENT_IRQ_DUMMY (0xFFFFFFFU)                         /* Dummy mask. */
#define SC_EVENT_TYPE_TUPLE(group, irq) (((group) << 28) | (irq)) /* Marco to compose SC Event type. */
#define SC_EVENT_GET_IRQ_GROUP(type) (((uint32_t)(type) >> 28) & 0xFU)      /* Marco to get SC IRQ group. */
#define SC_EVENT_GET_IRQ(type) ((uint32_t)(type) & 0xFFFFFFFU)              /* Marco to get SC IRQ mask. */

/*!
 * @brief Get SC Event list object structure pointer.
 */
#define SC_EVENT_LIST_OBJ(type, field, list) (type)((uint32_t)(list) - (uint32_t)(&((type)0)->field))

/*! @brief SC Event type. */
typedef enum _sc_event
{
    kSCEvent_TempHigh = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_HIGH), /*!< Temp alarm interrupt */
    kSCEvent_TempCpu0High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_CPU0_HIGH), /*!< CPU0 temp alarm interrupt */
    kSCEvent_TempCpu1High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_CPU1_HIGH), /*!< CPU1 temp alarm interrupt */
    kSCEvent_TempGpu0High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_GPU0_HIGH), /*!< GPU0 temp alarm interrupt */
    kSCEvent_TempGpu1High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_GPU1_HIGH), /*!< GPU1 temp alarm interrupt */
    kSCEvent_TempDrc0High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_DRC0_HIGH), /*!< DRC0 temp alarm interrupt */
    kSCEvent_TempDrc1High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_DRC1_HIGH), /*!< DRC1 temp alarm interrupt */
    kSCEvent_TempVpuHigh =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_VPU_HIGH), /*!< VPU temp alarm interrupt */
    kSCEvent_TempPmic0High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC0_HIGH), /*!< PMIC0 temp alarm interrupt */
    kSCEvent_TempPmic1High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC1_HIGH),         /*!< PMIC1 temp alarm interrupt */
    kSCEvent_TempLow = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_LOW), /*!< Temp alarm interrupt */
    kSCEvent_TempCpu0Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_CPU0_LOW), /*!< CPU0 temp alarm interrupt */
    kSCEvent_TempCpu1Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_CPU1_LOW), /*!< CPU1 temp alarm interrupt */
    kSCEvent_TempGpu0Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_GPU0_LOW), /*!< GPU0 temp alarm interrupt */
    kSCEvent_TempGpu1Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_GPU1_LOW), /*!< GPU1 temp alarm interrupt */
    kSCEvent_TempDrc0Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_DRC0_LOW), /*!< DRC0 temp alarm interrupt */
    kSCEvent_TempDrc1Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_DRC1_LOW),                  /*!< DRC1 temp alarm interrupt */
    kSCEvent_TempVpuLow = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_VPU_LOW), /*!< VPU temp alarm interrupt */
    kSCEvent_TempPmic0Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC0_LOW), /*!< PMIC0 temp alarm interrupt */
    kSCEvent_TempPmic1Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC1_LOW), /*!< PMIC1 temp alarm interrupt */
    kSCEvent_TempPmic2High =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC2_HIGH), /*!< PMIC2 temp alarm interrupt */
    kSCEvent_TempPmic2Low =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_TEMP, SC_IRQ_TEMP_PMIC2_LOW), /*!< PMIC2 temp alarm interrupt */

    kSCEvent_Wdog = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WDOG, SC_IRQ_WDOG), /*!< Watchdog interrupt */

    kSCEvent_Rtc = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_RTC, SC_IRQ_RTC), /*!< RTC interrupt */

    kSCEvent_Button = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WAKE, SC_IRQ_BUTTON), /*!< Button interrupt */
    kSCEvent_Pad    = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WAKE, SC_IRQ_PAD),    /*!< Pad wakeup */
    kSCEvent_User1  = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WAKE, SC_IRQ_USR1),   /*!< User defined 1 */
    kSCEvent_User2  = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WAKE, SC_IRQ_USR2),   /*!< User defined 2 */
    kSCEvent_BcPad =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_WAKE, SC_IRQ_BC_PAD), /*!< Pad wakeup (broadcast to all partitions) */
#if (defined(SC_EVENT_USE_SYSCTR) && SC_EVENT_USE_SYSCTR)
    kSCEvent_SysCtr = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_SYSCTR, SC_IRQ_SYSCTR), /*!< System counter interrupts */
#endif
    kSCEvent_Rebooted =
        SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_REBOOTED, SC_EVENT_IRQ_DUMMY), /*!< Partition reboot complete */

    kSCEvent_Reboot = SC_EVENT_TYPE_TUPLE(SC_IRQ_GROUP_REBOOT, SC_EVENT_IRQ_DUMMY) /*!< Partition reboot starting */
} sc_event_t;

/*! @brief SC Event callback function.
 *
 *  The SC Event callback returns a status from the underlying layer.
 *  The status reflects the SC IRQ status got by sc_irq_status SCFW API. It's the bitmask of enabled IRQ in a group.
 *  Such as for kSCEvent_Reboot/kSCEvent_Rebooted event, if more than one partition reboot event is enabled, this status
 *  flag can be used to identify which partition the event comes from. Refer to SCFW API sc_irq_status for more details.
 */
typedef void (*sc_event_callback_t)(uint32_t status, void *userData);

/*! @brief SC Event Semaphore Wait function.
 *
 *  The Semaphore Wait/Post function is used in RTOS envirnoment to pass Semaphore Wait/Post function into SC Event
 *  driver. Unused in baremetal envirnonment. The task can wait the event by calling SCEvent_WaitEvent function.
 */
typedef status_t (*sc_event_sema4_wait_t)(void *sem, uint32_t timeout);

/*! @brief SC Event Semaphore Post function.
 *
 *  The Semaphore Wait/Post function is used in RTOS envirnoment to pass Semaphore Wait/Post function into SC Event
 *  driver. Unused in baremetal envirnonment. The post function is called to give semaphore if event triggered in IRQ.
 */
typedef void (*sc_event_sema4_post_t)(void *sem);

/**
 * @brief SC Event list fields
 */
typedef struct _sc_event_list
{
    struct _sc_event_list *prev; /*!< previous list node */
    struct _sc_event_list *next; /*!< next list node */
} sc_event_list_t;

/*! @brief SC Event handler structure. */
struct _sc_event_handler
{
    sc_event_list_t node;
    sc_event_t event;             /*!< Event type. */
    sc_event_callback_t callback; /*!< Event callback. */
    void *data;                   /*!< User data. */
};

/*!
 * @brief SC Event handler is a pointer to the SC Event handler instance
 */
typedef struct _sc_event_handler *sc_event_handler_t;
/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Initialize SC Event module.

 * This function enable the IPC MU interrupt, setup to listen the event comes from SCU/SCFW.
 *
 * @param priority The SC IRQ interrupt priority. Once any SC IRQ enabled, the SCU will broadcast MU interrupt through
 *  the IPC MU to M4 cores.
 *
 * @retval None.
 */
void SCEvent_Init(uint8_t priority);

/*!
 * @brief Deinitialize SC Event.
 *
 * This function disable the IPC MU interrupt.
 *
 */
void SCEvent_Deinit(void);

/*!
 * @brief Register SC Event handler.

 * This function register the handler for the specified event. When the event is enabled  by SCEvent_Config and happens,
 * the callback will be called from SCEvent_process. More than one callback can be added for an event.
 * But the total registered events are limited to
 * SC_EVENT_HANDLER_MEM_POOL_SIZE/(sizeof(struct _sc_event_handler)).
 *
 * @param event The event to be registered with.
 * @param callback The callback function. This function will be called from SCEvent_process.
 * @param userData User defined callback function parameter.
 *
 * @retval SC Event handler.
 */
sc_event_handler_t SCEvent_RegisterEventHandler(sc_event_t event, sc_event_callback_t callback, void *userData);

/*!
 * @brief Unregister SC Event handler.

 * This function unregister and delete the given event handler.
 *
 * @param handler The SC Event handler to unregister.
 *
 * @retval none.
 */
void SCEvent_UnregisterEventHandler(sc_event_handler_t handler);

/*!
 * @brief Configure SC Event.

 * This function enables/disables response for the event comes from SCU/SCFW.
 *
 * @param event The event to be configured.
 * @param enable Enable the event or not.
 * @param pt Which partition the event comes from. Only applicable for partition reboot event: kSCEvent_Rebooted,
 kSCEvent_Reboot.
 *
 * @retval kStatus_Success - Configure SC Event Successfully.
 * @retval kStatus_Fail    - Failed to configure SC Event.
 */
status_t SCEvent_Config(sc_event_t event, bool enable, uint32_t pt);

/*!
 * @brief SCEvent Process function.
 *
 * This function is used to check SC event status and handle all the registered event handlers. The SCFW API call is
 * a blocking call and used to check SC IRQ status, so this function should be executed in task context to make sure
 * other event(interrupt) handled in time. In RTOS enviroment, application creats a task and wait for some events came
 * using SCEvent_WaitEvent to run this function to handle the events. In baremetal enviroment, application need
 * preiodically call this function to make sure the pending events handled.
 */
void SCEvent_Process(void);

/*!
 * @brief Set Semaphore and Semaphore wait/post funciton in RTOS environment.
 *
 *  The Semaphore Wait/Post function is used in RTOS envirnoment to pass Semaphore Wait/Post function into SC Event
 * driver. Unused in baremetal envirnonment. The SCEvent_process will wait the Semaphore registered by
 * SCEvent_SetWaitPostFunc until the event comes, and give the Semaphore, then it will handle the event and call the
 * event handler's callback.
 *
 * @param wait Semaphore wait function.
 * @param post Semaphore post function.
 * @param sem Semaphore.
 * @param timeout timeout.
 *
 * @retval kStatus_Success if succeed, kStatus_Timeout if timeout.
 */
status_t SCEvent_WaitEvent(sc_event_sema4_wait_t wait, sc_event_sema4_post_t post, void *sem, uint32_t timeout);

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SC_EVENT_H_ */
