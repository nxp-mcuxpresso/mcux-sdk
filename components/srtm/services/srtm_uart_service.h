/*
 * Copyright 2022-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRTM_UART_SERVICE_H__
#define __SRTM_UART_SERVICE_H__

#include "srtm_service.h"
#include "srtm_service_struct.h"
#include "fsl_component_serial_manager.h"
#include "task.h" /* freertos */

/*!
 * @addtogroup srtm_service
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @brief Switch to disable UART service debugging messages. */
#ifndef SRTM_UART_SERVICE_DEBUG_OFF
#define SRTM_UART_SERVICE_DEBUG_OFF (0)
#endif

#if SRTM_UART_SERVICE_DEBUG_OFF
#undef SRTM_DEBUG_VERBOSE_LEVEL
#define SRTM_DEBUG_VERBOSE_LEVEL SRTM_DEBUG_VERBOSE_NONE
#endif

#ifndef SRTM_UART_ENDPOINT_MAX_NUM
#define SRTM_UART_ENDPOINT_MAX_NUM (32U)
#endif

#ifndef SRTM_UART_RECEIVE_BUFFER_SIZE
#define SRTM_UART_RECEIVE_BUFFER_SIZE (1024U)
#endif

#ifndef SRTM_UART_FRAME_DATA_SIZE
#define SRTM_UART_FRAME_DATA_SIZE (512U)
#endif

#ifndef SRTM_UART_WANT_TO_READ_BYTES
#define SRTM_UART_WANT_TO_READ_BYTES (100U)
#endif

#ifndef SRTM_UART_RECEIVER_TASK_PRIO
#define SRTM_UART_RECEIVER_TASK_PRIO (3U)
#endif

#define SRTM_UART_INVALID_BUS_ID (0xFFU)

#define SRTM_UART_SUPPORT_RPMSG_OVER_UART_FLAG (1 << 0U)

#define SRTM_UART_SUPPORT_MULTI_UART_MSG_FLAG (1 << 1U)
#define SRTM_UART_PEER_BOARD_SUPPORT_RPMSG_FLAG (1 << 2U)
#define SRTM_UART_PORT_NUM_SHIFT (11U)
/* [10] = 0b1: specify port number, 0b0: not specify port number */
#define SRTM_UART_SPECIFY_PORT_NUM_MASK (0x1 << 10U)
/* [15:11] = port number, such as: /dev/ttyRPMSG10, 10 is the port number. /dev/ttyUSB3, 3 is the port number(dst uart id) */
#define SRTM_UART_PORT_NUM_MASK (0x1F << SRTM_UART_PORT_NUM_SHIFT)


/* Protocol definition */
#define SRTM_UART_CATEGORY (0xBU)

#define SRTM_UART_VERSION (0x0100U)

#define SRTM_UART_RETURN_CODE_SUCEESS     (0x0U)
#define SRTM_UART_RETURN_CODE_FAIL        (0x1U)
#define SRTM_UART_RETURN_CODE_UNSUPPORTED (0x2U)

#define SRTM_UART_CMD_SEND (0x1U)
#define SRTM_UART_CMD_HELLO (0x2U)

/* define multi uart message protocol to send data through uart to destination uart */
#define MULTI_UART_MSG_PREAMBLE0 (0x24U)
#define MULTI_UART_MSG_PREAMBLE1 (0x55U)
#define MULTI_UART_MSG_PREAMBLE2 (0x54U)
#define MULTI_UART_MSG_PREAMBLE3 (0x2CU)
#define MULTI_UART_MSG_END0 (0x45U)
#define MULTI_UART_MSG_END1 (0x24U)

SRTM_PACKED_BEGIN struct multi_uart_msg_header
{
    uint8_t preamble[4];
    uint8_t dst_uart_id; /* two boards are runnig rpmsg: [/dev/ttyRPMSG5](first board) -> [/dev/ttyRPMSG6](second board), 6 is the destination uart id */
                /* first board is running rpmsg, second board is not running rpmsg: [/dev/ttyRPMSG4, first board] --> [/dev/ttyUSB8, second board], 8 is the destination uart id */
    uint8_t data_len;
} SRTM_PACKED_END;

SRTM_PACKED_BEGIN struct multi_uart_msg
{
    struct multi_uart_msg_header header;
    uint8_t data[1];
} SRTM_PACKED_END;

/**
 * @brief SRTM UART adapter structure pointer.
 */
typedef struct _srtm_uart_adapter *srtm_uart_adapter_t;

/**
 * @brief SRTM UART adapter structure
 */
struct _srtm_uart_adapter
{
    /* Bound service */
    srtm_service_t service;
    srtm_status_t (*sendNotify)(srtm_service_t service, srtm_channel_t chan, uint8_t *data, uint16_t data_len); /* send notify from mcore to acore */
    srtm_status_t (*send)(srtm_uart_adapter_t adapter,
                            uint8_t bus_id,
                            uint8_t *data,
                            uint32_t data_len); /* send data to uart */
    void (*bindChanByUartId)(srtm_channel_t chan, uint8_t bus_id, uint16_t flags, uint8_t uart_id);
    serial_read_handle_t (*findReadHandleByBusId)(srtm_uart_adapter_t adapter, uint8_t bus_id);
    srtm_status_t (*findBusIdByReadHandle)(srtm_uart_adapter_t adapter,
                                          serial_read_handle_t read_handle, uint8_t *bus_id);
    TaskHandle_t (*findReceiverTaskHandleByReadHandle)(srtm_uart_adapter_t adapter,
                                                       serial_read_handle_t read_handle);
};

/* Service handle */
typedef struct _srtm_uart_service
{
    struct _srtm_service service;
    srtm_uart_adapter_t adapter;
} * srtm_uart_service_t;

/**
 * @brief SRTM UART payload structure
 */
SRTM_PACKED_BEGIN struct _srtm_uart_payload
{
    uint8_t busId;
    union
    {
        uint8_t reserved; /* used in request packet */
        uint8_t retCode;  /* used in response packet */
    };
    uint16_t flags;
    uint8_t data[1];
} SRTM_PACKED_END;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Create UART service.
 *
 * @param adapter UART adapter to handle real UART operations.
 * @return SRTM service handle on success and NULL on failure.
 */
srtm_service_t SRTM_UartService_Create(srtm_uart_adapter_t adapter);

/*!
 * @brief Destroy UART service.
 *
 * @param service SRTM service to destroy.
 */
void SRTM_UartService_Destroy(srtm_service_t service);

/*!
 * @brief Provide a callback when received data from uart
 *
 */
void SRTM_Uart_RxCallBack(void *pData, serial_manager_callback_message_t *message, serial_manager_status_t status);

/*!
 * @brief Provide a callback after data transfer is finished
 *
 */
void SRTM_Uart_TxCallBack(void *pData, serial_manager_callback_message_t *message, serial_manager_status_t status);
#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* __SRTM_UART_SERVICE_H__ */
