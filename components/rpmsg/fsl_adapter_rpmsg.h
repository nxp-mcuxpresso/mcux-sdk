/*
 * Copyright 2020, 2022-2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_RPMSG_ADAPTER_H__
#define __FSL_RPMSG_ADAPTER_H__

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
#define HAL_RPMSG_HANDLE_SIZE (52U)

#ifndef REMOTE_CORE_BOOT_ADDRESS
#define REMOTE_CORE_BOOT_ADDRESS (0x01000000U)
#endif

#ifndef MAX_EP_COUNT
#define MAX_EP_COUNT (5U)
#endif

#define RPMSG_WAITFOREVER (0xFFFFFFFFU)

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
    kStatus_HAL_RpmsgTimeout,
} hal_rpmsg_status_t;

/*! @brief RPMSG return status */
typedef enum _hal_rpmsg_return_status
{
    kStatus_HAL_RL_RELEASE = 0U,
    kStatus_HAL_RL_HOLD,
} hal_rpmsg_return_status_t;

/*! @brief The callback function of RPMSG adapter.
 *
 * @note If Rpmsg RX callback function return kStatus_HAL_RL_RELEASE mode, no need to call HAL_RpmsgFreeRxBuffer.
 * @note If Rpmsg RX callback function return kStatus_HAL_RL_HOLD mode,then need to call HAL_RpmsgFreeRxBuffer.
 *
 */
typedef hal_rpmsg_return_status_t (*rpmsg_rx_callback_t)(void *param, uint8_t *data, uint32_t len);

/*! @brief The configure structure of RPMSG adapter. */
typedef struct _hal_rpmsg_config
{
    uint8_t local_addr;           /* Local address for rx */
    uint8_t remote_addr;          /* Remote address for tx */
    rpmsg_rx_callback_t callback; /* RPMGS Rx callback  */
    void *param;                  /* RPMGS Rx callback parameter */
    uint8_t imuLink;
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
 * @retval kStatus_HAL_RpmsgSuccess RPMSG module initialize succeed.
 */
hal_rpmsg_status_t HAL_RpmsgMcmgrInit(void);

/*!
 * @brief Initializes the RPMSG adapter for RPMSG channel configure.
 *
 * @note This API should be called to software RPMSG communication configure, and it be
 * called whenever application need it.
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
 * @brief Send data to another RPMSG module with timeout.
 *
 * This function will send a specified length of data to another core by RPMSG.
 *
 * @note This API should be called to send data.
 *
 * @param handle           RPMSG handle pointer.
 * @param data             Pointer to where the send data from.
 * @param length           The send data length.
 * @param timeout          Timeout in ms, 0 if nonblocking, RPMSG_WAITFOREVER for wait for forever.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG send data succeed.
 */
hal_rpmsg_status_t HAL_RpmsgSendTimeout(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length, uint32_t timeout);

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
 * @brief Allocates the tx buffer for message payload with timeout.
 *
 * This API can only be called at process context to get the tx buffer in vring. By this way, the
 * application can directly put its message into the vring tx buffer without copy from an application buffer.
 * It is the application responsibility to correctly fill the allocated tx buffer by data and passing correct
 * parameters to the rpmsg_lite_send_nocopy() function to perform data no-copy-send mechanism.
 *
 *
 * @param handle           RPMSG handle pointer.
 * @param size             The send data length.
 * @param timeout          Timeout in ms, 0 if nonblocking, RPMSG_WAITFOREVER for wait for forever.
 * @retval The tx buffer address on success and RL_NULL on failure.
 */
void *HAL_RpmsgAllocTxBufferTimeout(hal_rpmsg_handle_t handle, uint32_t size, uint32_t timeout);

/*!
 * @brief Allocates the tx buffer for message payload.
 *
 * This API can only be called at process context to get the tx buffer in vring. By this way, the
 * application can directly put its message into the vring tx buffer without copy from an application buffer.
 * It is the application responsibility to correctly fill the allocated tx buffer by data and passing correct
 * parameters to the rpmsg_lite_send_nocopy() function to perform data no-copy-send mechanism.
 *
 *
 * @param handle           RPMSG handle pointer.
 * @param size           The send data length.
 * @retval The tx buffer address on success and RL_NULL on failure.
 */
void *HAL_RpmsgAllocTxBuffer(hal_rpmsg_handle_t handle, uint32_t size);

/*!
 * @brief Send data with NoCopy to another RPMSG module.
 *
 * This function will send a specified length of data to another core by RPMSG.
 * This function sends txbuf of length len to the remote dst address,
 * and uses ept->addr as the source address.
 * The application has to take the responsibility for:
 *  1. tx buffer allocation (HAL_RpmsgAllocTxBuffer())
 *  2. filling the data to be sent into the pre-allocated tx buffer
 *  3. not exceeding the buffer size when filling the data
 *  4. data cache coherency
 *
 * After the HAL_RpmsgNoCopySend() function is issued the tx buffer is no more owned
 * by the sending task and must not be touched anymore unless the HAL_RpmsgNoCopySend()
 * function fails and returns an error.
 *
 * @note This API should be called to send data.
 *
 * @param handle           RPMSG handle pointer.
 * @param data             Pointer to where the send data from.
 * @param length           The send data length.
 * @retval kStatus_HAL_RpmsgSuccess RPMSG send data succeed.
 */
hal_rpmsg_status_t HAL_RpmsgNoCopySend(hal_rpmsg_handle_t handle, uint8_t *data, uint32_t length);

/*!
 * @brief Releases the rx buffer for future reuse in vring.
 * This API can be called at process context when the
 * message in rx buffer is processed.
 *
 * @note The HAL_RpmsgFreeRxBuffer need be called only if Rpmsg RX callback function return kStatus_HAL_RL_HOLD mode.
 *
 * @param handle           RPMSG handle pointer.
 * @param data             Pointer to where the received data from perr.

 *
 * @return Status of function execution, RL_SUCCESS on success.
 */
hal_rpmsg_status_t HAL_RpmsgFreeRxBuffer(hal_rpmsg_handle_t handle, uint8_t *data);

/*!
 * @brief Install RPMSG rx callback.
 *
 * @note The function must be called because rpmsg adapter just support asynchronous receive mode
 *        should make sure the callback function is installed before the data received from peer soc,
 *        and the rx callback function will be called when the rx process complete.
 *
 *
 * @param handle    RPMSG handle pointer.
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
#endif /* __FSL_RPMSG_ADAPTER_H__ */
