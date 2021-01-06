/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __USB_OTG_PERIPHERAL_H__
#define __USB_OTG_PERIPHERAL_H__

#include "usb_otg_config.h"

/*!
 * @addtogroup usb_otg_peripheral_driver
 * @{
 */

#if ((defined USB_OTG_KHCI_PERIPHERAL_ENABLE) && (USB_OTG_KHCI_PERIPHERAL_ENABLE))

/*!
 * @brief Enable OTG peripheral.
 *
 * This function enable OTG peripheral function.
 *
 * @retval kStatus_USB_Success              success.
 * @retval other values                     Fail.
 */
usb_status_t USB_OtgPeripheralEnable(void);

/*!
 * @brief Disable OTG peripheral.
 *
 * This function disable OTG peripheral function.
 *
 * @retval kStatus_USB_Success              success.
 * @retval other values                     Fail.
 */
usb_status_t USB_OtgPeripheralDisable(void);

/*!
 * @brief Get the peripheral status.
 *
 * This function is nonblocking, return the result immediately.
 *
 * @param[in] statusType      Please reference to #usb_otg_status_type_t.
 * @param[out] statusValue    The status value.
 *
 * @retval kStatus_USB_Success              success.
 * @retval other values                     Fail.
 */
usb_status_t USB_OtgPeripheralGetStatus(uint32_t statusType, uint32_t *statusValue);

/*!
 * @brief Control the peripheral.
 *
 * This function control the peripheral to implement the different functions.
 *
 * @param controllerHandle  The controller instance handle.
 * @param controlType       The control type, please reference to #usb_otg_control_t.
 * @param controlValue1     The control value, it is 0 or 1 usually.
 * @param controlValue2     It only be used in the kOtg_ControlRequestStatus control now.
 *
 * @retval kStatus_USB_Success              success.
 * @retval other values                     Fail.
 */
usb_status_t USB_OtgPeripheralControl(usb_otg_controller_handle controllerHandle,
                                      uint32_t controlType,
                                      uint32_t controlValue1,
                                      uint32_t controlValue2);

#endif

/*! @}*/

#endif
