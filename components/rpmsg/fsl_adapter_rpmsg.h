/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_RPMSG_ADAPTER_H__
#define __HAL_RPMSG_ADAPTER_H__

#if defined(SDK_OS_FREE_RTOS)
#include "FreeRTOS.h"
#endif

/*!
 * @addtogroup RPMSG_Adapter
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief RPMSG Msaster/Remote role definition (0 - Master, 1 - Remote) */
#ifndef HAL_RPMSG_SELECT_ROLE
#define HAL_RPMSG_SELECT_ROLE (1U)
#endif

/*! @brief RPMSG handle size definition */
#define HAL_RPMSG_HANDLE_SIZE (300U)

#ifndef REMOTE_CORE_BOOT_ADDRESS
#define REMOTE_CORE_BOOT_ADDRESS (0x01000000U)
#endif

#ifndef MAX_EP_COUNT
#define MAX_EP_COUNT (5U)
#endif

/*!
 * @brief Defines the rpmsg handle
 *
 * This macro is used to define a 4 byte aligned rpmsg handle.
 * Then use "(hal_rpmsg_handle_t)name" to get the rpmsg handle.
 *
 * The macro should be global and could be optional. You could also define rpmsg handle by yourself.
 *
 * This is an example,
 * @code
 * RPMSG_HANDLE_DEFINE(rpmsgHandle);
 * @endcode
 *
 * @param name The name string of the rpmsg handle.
 */
#define RPMSG_HANDLE_DEFINE(name) uint32_t name[((HAL_RPMSG_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))]

/*! @brief The handle of RPMSG adapter */
typedef void *hal_rpmsg_handle_t;

/*! @brief RPMSG status */
typedef enum _hal_rpmsg_status
{
    kStatus_HAL_RpmsgSuccess = 0U,
    kStatus_HAL_RpmsgError,
    kStatus_HAL_RpmsgRxBusy,
    kStatus_HAL_RpmsgTxBusy,
    kStatus_HAL_RpmsgTxIdle,
    kStatus_HAL_RpmsgRxIdle,
} hal_rpmsg_status_t;

/*! @brief The callback function of RPMSG adapter. */
typedef void (*rpmsg_rx_callback_t)(void *param, uint8_t *data, uint32_t len);

/*! @brief The configure structure of RPMSG adapter. */
typedef struct _hal_rpmsg_config
{
    uint32_t local_addr;  /* Local address for rx */
    uint32_t remote_addr; /* Remote address for tx */
} hal_rpmsg_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Initializes the RPMSG adapter module for dual core communication.
 *
 * @note This API should be called at the beginning of the application using the RPMSG adapter driver.
 *
 * @param handle Pointer to point to a memory space of size #HAL_RPMSG_HANDLE_SIZE allocated by the caller.
 * The handle should be 4 byte aligned, because unaligned access doesn't be supported on some devices.
 * You can define the handle in the following two ways:
 * #RPMSG_HANDLE_DEFINE(handle);
 * or
 * uint32_t handle[((HAL_RPMSG_HANDLE_SIZE + sizeof(uint32_t) - 1U) / sizeof(uint32_t))];
 * @param config           Used for config local/remote endpoint addr.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG module initialize succeed.
 */
hal_rpmsg_status_t HAL_RpmsgInit(hal_rpmsg_handle_t handle, hal_rpmsg_config_t *config);

/*!
 * @brief DeInitilizate the RPMSG adapter module.
 *
 * @note This API should be called when not using the RPMSG adapter driver anymore.
 *
 * @param handle           RPMSG handle pointer.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG module deinitialize succeed.
 */
hal_rpmsg_status_t HAL_RpmsgDeinit(hal_rpmsg_handle_t handle);

/*!
 * @brief Send data to another RPMSG module.
 *
 * This function will send a specified length of data to another core by RPMSG.
 *
 * @note This API should be called to send data.
 *
 * @param handle           RPMSG handle pointer.
 * @param data             Pointer to where the send data from.
 * @param length           The send data length.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG send data succeed.
 */
hal_rpmsg_status_t HAL_RpmsgSend(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length);

/*!
 * @brief Install RPMSG rx callback.
 *
 * @note The rx callback function will be called when the rx process complete.
 *
 * @param handle           RPMSG handle pointer.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG install rx callback succeed.
 */
hal_rpmsg_status_t HAL_RpmsgInstallRxCallback(hal_rpmsg_handle_t handle, rpmsg_rx_callback_t callback, void *param);

/*!
 * @brief Prepares to enter low power consumption.
 *
 * This function is used to prepare to enter low power consumption.
 *
 * @param handle           RPMSG handle pointer.
 * @retval kStatus_HAL_RpmsgSuccess Successful operation.
 * @retval kStatus_HAL_RpmsgError An error occurred.
 */
hal_rpmsg_status_t HAL_RpmsgEnterLowpower(hal_rpmsg_handle_t handle);

/*!
 * @brief Prepares to exit low power consumption.
 *
 * This function is used to restore from low power consumption.
 *
 * @param handle           RPMSG handle pointer.
 * @retval kStatus_HAL_RpmsgSuccess Successful operation.
 * @retval kStatus_HAL_RpmsgError An error occurred.
 */
hal_rpmsg_status_t HAL_RpmsgExitLowpower(hal_rpmsg_handle_t handle);

/*! @}*/

#if defined(__cplusplus)
}
#endif
/*! @}*/
#endif /* __HAL_RPMSG_ADAPTER_H__ */
