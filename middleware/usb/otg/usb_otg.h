/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_OTG_H__
#define __USB_OTG_H__

#include "usb.h"
#include "usb_misc.h"
#include "usb_spec.h"

/*!
 * @addtogroup usb_otg_drv
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief USB OTG task message queue count */
#define USB_OTG_MSG_COUNT (8)

/*! @brief USB OTG host request flag */
#define USB_OTG_STATUS_HOST_REQUEST_FLAG (0x01U)

/*! @brief USB OTG controller handle type define */
typedef void *usb_otg_controller_handle;

/*! @brief please reference to 7.4 in OTG spec */
typedef enum _usb_otg_status_type
{
    kOtg_StatusId                     = 0x0001U,   /*! id */
    kOtg_StatusAdpChange              = 0x0002U,   /*! adp_change */
    kOtg_StatusSrpDet                 = 0x0004U,   /*! a_srp_det */
    kOtg_StatusVbusVld                = 0x0008U,   /*! a_vbus_vld */
    kOtg_StatusAConn                  = 0x0010U,   /*! a_conn */
    kOtg_StatusBusResume              = 0x0020U,   /*! a_bus_resume */
    kOtg_StatusBusSuspend             = 0x0040U,   /*! a_bus_suspend */
    kOtg_StatusSe0Srp                 = 0x0080U,   /*! b_se0_srp */
    kOtg_StatusSsendSrp               = 0x0100U,   /*! b_ssend_srp */
    kOtg_StatusSessVld                = 0x0200U,   /*! b_sess_vld */
    kOtg_StatusBusDrop                = 0x0400U,   /*! a_bus_drop */
    kOtg_StatusBusReq                 = 0x0800U,   /*! a_bus_req and b_bus_req */
    kOtg_StatusPowerUp                = 0x1000U,   /*! power_up */
    kOtg_StatusTimeOut                = 0x2000U,   /*! all the timeout in the state machine */
    kOtg_StatusBConn                  = 0x4000U,   /*! b_conn */
    kOtg_StatusClrErr                 = 0x8000U,   /*! a_clr_err */
    kOtg_StatusBSrpDone               = 0x10000U,  /*! b_srp_done */
    kOtg_StatusADisconn               = 0x20000U,  /*! a_conn(non) */
    kOtg_StatusBDisconn               = 0x40000U,  /*! b_conn(non) */
    kOtg_StatusVbusInvld              = 0x80000U,  /*! a_vbus_vld(non) */
    kOtg_StatusSessInvld              = 0x100000U, /*! b_sess_vld(non) */
    kOtg_StatusCheckIdleInAPeripheral = 0x200000U, /*! check the idle timeout when in a_peripheral state */

    kOtg_StatusBHNPFeature = 0x40000000U, /*! This status is valid when
                                              (1) b_hnp_enable feature is sent when A-device works as host; Or
                                              (2) b_hnp_enable feature is received when B-device works as device */
    kOtg_StatusChange = (int)0x80000000U, /*! there are status change, need call control interface
                                      (kOtg_ControlUpdateStatus) to update status */
} usb_otg_status_type_t;

/*! @brief Please reference to chapter 7 in OTG spec */
typedef enum _usb_otg_device_state
{
    kOtg_State_Start = 0U,  /*! state state */
    kOtg_State_AIdle,       /*! a_idle state */
    kOtg_State_AWaitVrise,  /*! a_wait_vrise state */
    kOtg_State_AWaitBcon,   /*! a_wait_bcon state */
    kOtg_State_AHost,       /*! a_host state */
    kOtg_State_AWaitVfall,  /*! a_wait_vfall state */
    kOtg_State_ASuspend,    /*! a_suspend state */
    kOtg_State_APeripheral, /*! a_peripheral state */
    kOtg_State_AVbusErr,    /*! a_vbus_err state */

    kOtg_State_BIdleEh,     /*! b_idle_eh state */
    kOtg_State_BIdle,       /*! b_idle or bp_idle state, when the device is peripheral-only B-device it means bp_idle */
    kOtg_State_BSrpInit,    /*! b_srp_init or bp_srp_init state, when the device is peripheral-only B-device it means
                               bp_srp_init */
    kOtg_State_BPeripheral, /*! b_peripheral or bp_peripheral state, when the device is peripheral-only B-device it
                               means bp_peripheral */
    kOtg_State_BWaitAcon,   /*! b_wait_acon state */
    kOtg_State_BHost,       /*! b_host state */
} usb_otg_device_state_t;

/*! @brief The event value for callback to applcation when event type is kOtg_EventStackInit */
typedef enum _usb_otg_stack_init_type
{
    kOtg_StackNone = 0U,    /*! default state */
    kOtg_StackHostInit,     /*! notify application to initialize host stack */
    kOtg_StackHostDeinit,   /*! notify application to de-initialize host stack */
    kOtg_StackDeviceInit,   /*! notify application to initialize device stack */
    kOtg_StackDeviceDeinit, /*! notify application to de-initialize device stack */
} usb_otg_stack_init_type_t;

/*! @brief The event types for callback to applcation */
typedef enum _usb_otg_event_type
{
    /*! OTG state change event, the event values are #usb_otg_device_state_t */
    kOtg_EventStateChange = 0U,
    /*! host/device stack handle event, the event values are #usb_otg_stack_init_type_t */
    kOtg_EventStackInit,
} usb_otg_event_type_t;

/*! @brief USB OTG descriptor */
typedef struct _usb_otg_descriptor
{
    /*! Size of Descriptor */
    uint8_t bLength;
    /*! OTG type = 9 */
    uint8_t bDescriptorType;
    /*! @brief Attribute Fields
     *
     * D7..3: Reserved (reset to zero)
     * D2: ADP support
     * D1: HNP support
     * D0: SRP support
     */
    uint8_t bmAttributes;
    /*! OTG and EH supplement release number in binary-coded decimal */
    uint8_t bcdOTG[2];
} usb_otg_descriptor_t;

/*!
 * @brief OTG callback function typedef.
 *
 * This callback function is used to notify application events, the events include #usb_otg_event_type_t.
 * This callback pointer is passed when initializing OTG.
 *
 * @param param           The assigned parameter when initializing OTG.
 * @param eventType       Please reference to #usb_otg_event_type_t.
 * @param event_code      Please reference to #usb_otg_device_state_t and #usb_otg_stack_init_type_t.
 */
typedef void (*usb_otg_callback_t)(void *param, uint8_t eventType, uint32_t eventValue);

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @name USB OTG APIs
 * @{
 */

/*!
 * @brief Initializes the USB OTG stack.
 *
 * This function initializes the USB OTG module specified by the controllerId.
 *
 * @param[in] controllerId      The controller ID of the USB IP. See the enumeration #usb_controller_index_t.
 * @param[out] otgHandle        Return the OTG handle.
 * @param[in] otgCallbackFn     OTG callback function, it is #usb_otg_callback_t.
 * @param[in] callbackParameter The callback parameter.
 *
 * @retval kStatus_USB_Success              The OTG is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_AllocFail            Allocation memory fail.
 * @retval kStatus_USB_Error                message queue create fail, controller is not fount, controller initialize
 * fail.
 */
usb_status_t USB_OtgInit(uint8_t controllerId,
                         usb_otg_handle *otgHandle,
                         usb_otg_callback_t otgCallbackFn,
                         void *callbackParameter);

/*!
 * @brief Deinitializes the USB OTG stack.
 *
 * This function deinitializes the USB OTG module specified by the otgHandle.
 *
 * @param[in] otgHandle  the OTG handle.
 *
 * @retval kStatus_USB_Success              The OTG is initialized successfully.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                Controller deinitialization fail.
 */
usb_status_t USB_OtgDeinit(usb_otg_handle otgHandle);

/*!
 * @brief OTG stack task function.
 *
 * The function implement the OTG stack state machine.
 * In bare metal environment, this function should be called periodically in the main function.
 * In the RTOS environment, this function should be used as a function entry to create a task.
 *
 * @param[in] otgHandle The OTG handle.
 */
void USB_OtgTaskFunction(usb_otg_handle otgHandle);

/*!
 * @brief OTG KHCI ISR function.
 *
 * The function is the KHCI interrupt service routine.
 *
 * @param[in] otgHandle The OTG handle.
 */
void USB_OtgKhciIsrFunction(usb_otg_handle otgHandle);

/*!
 * @brief A-device drop bus.
 *
 * This function drop the bus.
 *
 * @param[in] otgHandle  the OTG handle.
 * @param[in] drop       1 or 0.
 *
 * @retval kStatus_USB_Success              Success.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                The device is not A-device or Send message error.
 */
usb_status_t USB_OtgBusDrop(usb_otg_handle otgHandle, uint8_t drop);

/*!
 * @brief bus request.
 *
 * This function can be called in the follow situations:
 * 1. A-device request bus, change from a_idle to a_wait_vrise.
 * 2. HNP, B-device is in the b_peripheral and request the bus.
 * 3. A-device is in the a_peripheral and request the bus.
 * 4. B-device request bus (SRP), change from b_idle to b_srp_init
 * 5. Poll device status, "host request flag" is set.
 *
 * @param[in] otgHandle  the OTG handle.
 *
 * @retval kStatus_USB_Success              Success.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                Send message error.
 */
usb_status_t USB_OtgBusRequest(usb_otg_handle otgHandle);

/*!
 * @brief bus request.
 *
 * This function can be called in the follow situations:
 * 1. A-device set the bus request false when in a_idle.
 * 2. A-device release bus when A-device is host (a_host).
 * 3. B-device release bus when B-device is host (b_host).
 *
 * @param[in] otgHandle  the OTG handle.
 *
 * @retval kStatus_USB_Success              Success.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                Send message error.
 */
usb_status_t USB_OtgBusRelease(usb_otg_handle otgHandle);

/*!
 * @brief clear error.
 *
 * This function clears the error.
 *
 * @param[in] otgHandle  the OTG handle.
 *
 * @retval kStatus_USB_Success              Success.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                The device is not in error state or send message error.
 */
usb_status_t USB_OtgClearError(usb_otg_handle otgHandle);

/*!
 * @brief Notify OTG stack about the status changes.
 *
 * This function notify the #usb_otg_status_type_t and values.
 *
 * @param[in] otgHandle   the OTG handle.
 * @param[in] statusType  please reference to #usb_otg_status_type_t
 * @param[in] statusValue the value is 1 or 0
 *
 * @retval kStatus_USB_Success              Success.
 * @retval kStatus_USB_InvalidHandle        The otgHandle is a NULL pointer.
 * @retval kStatus_USB_Error                Send message error.
 */
usb_status_t USB_OtgNotifyChange(usb_otg_handle otgHandle, uint32_t statusType, uint32_t statusValue);

/*! @}*/

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* __USB_OTG_H__ */
