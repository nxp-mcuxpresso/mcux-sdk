/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_ADAPTER_RFIMU_H__
#define __FSL_ADAPTER_RFIMU_H__

#include "fsl_adapter_rfcommon.h"
#include "fsl_adapter_rpmsg.h"

/*!
 * @addtogroup IMU_Adapter
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef IMU_TASK_PRIORITY
#if defined(__ZEPHYR__)
#define IMU_TASK_PRIORITY (3U)
#elif defined(CPU2)
#define IMU_TASK_PRIORITY (2U)
#else
#define IMU_TASK_PRIORITY                                                                                       \
    (6U) /* makesure the calculated priority of HAL_ImuMainCpu13 task is the same with tcp/ip task(priority 2), \
            otherwise the throughput of udp rx will be very low */
#endif
#endif

#ifndef IMU_TASK_STACK_SIZE
#define IMU_TASK_STACK_SIZE (2048U)
#endif

#define IMU_MAX_MSG_CNT_LONG      (16U)
#define IMU_MAX_MSG_CNT_SHORT     (2U)
#define IMU_SYNC_MAGIC_PATTERN    (0xABCDEF89U)
#define IMU_TXQ_BUFSIZE           (32U) /*! must be power of 2 */
#define IMU_TXQ_BUFSIZE_THRESHOLD (8U)
#define IMU_TXQ_ENTRY_MASK        (IMU_TXQ_BUFSIZE - 1U)
#define IMU_EVENT_TRIGGERS        ((1U << kIMU_LinkMax) - 1U)
/*! @brief IMU message payload size. */
#define IMU_PAYLOAD_SIZE (8U)

#define RPMSG_EVENT_ENDPOINT_QUERY_RSP (1U << 0U)

#ifndef RPMSG_TXQ13_BUFSIZE
#define RPMSG_TXQ13_BUFSIZE (8U)
#endif

#ifndef RPMSG_TXQ23_BUFSIZE
#define RPMSG_TXQ23_BUFSIZE (16U)
#endif

#ifndef RPMSG_TXQ13_BUFLENGTH
#define RPMSG_TXQ13_BUFLENGTH (512U)
#endif

#ifndef RPMSG_TXQ23_BUFLENGTH
#define RPMSG_TXQ23_BUFLENGTH (264U)
#endif

#define RPMSG_TXQ13_ENTRY_MASK (RPMSG_TXQ13_BUFSIZE - 1U)
#define RPMSG_TXQ23_ENTRY_MASK (RPMSG_TXQ23_BUFSIZE - 1U)

#ifdef CONFIG_IMU_GDMA
#define IMU_GDMA_ENABLE (1U)
#else
#define IMU_GDMA_ENABLE (0U)
#endif
/*! @brief IMU initialization state. */
enum imu_init_state_t
{
    IMU_UNINITIALIZED,
    IMU_INITIALIZING,
    IMU_INITIALIZED
};

/*! @brief RPMSG type. */
typedef enum _imu_msg_type_t
{
    IMU_MSG_CONTROL,
    IMU_MSG_COMMAND,
    IMU_MSG_COMMAND_RESPONSE,
    IMU_MSG_EVENT,
    IMU_MSG_TX_DATA,
    IMU_MSG_RX_DATA,
    IMU_MSG_MULTI_TX_DATA,
    IMU_MSG_MULTI_RX_DATA,
    IMU_MSG_RPMSG,
    IMU_MSG_MAX,
    /* The header is 8 bits hence max types =255 */
} imu_msg_type_t;

/*! @brief RPMSG control message subtype. */
typedef enum _imu_ctrl_msg_subtype_t
{
    IMU_MSG_CONTROL_DEFAULT,
    IMU_MSG_CONTROL_SYNC,
    IMU_MSG_CONTROL_SYNC_ACK,
    IMU_MSG_CONTROL_ACK_FOR_UNLOCK,
    IMU_MSG_CONTROL_ERROR,
    IMU_MSG_CONTROL_SHUTDOWN,
    IMU_MSG_CONTROL_CMD_BUF_ADDR,
    IMU_MSG_CONTROL_EVT_ACK,
    IMU_MSG_CONTROL_COMMAND_RSP_ACK,
    IMU_MSG_CONTROL_TX_BUF_ADDR,
    IMU_MSG_CONTROL_FREE_RX_BUF,
    IMU_MSG_CONTROL_RPMSG_EPT_QUIRY,
    IMU_MSG_CONTROL_RPMSG_EPT_QUIRY_RSP,
    IMU_MSG_CONTROL_RPMSG_BUF_FREE,
    IMU_MSG_CONTROL_EVT_DUMP,
    IMU_MSG_CONTROL_MAX,
    /* The header is 8 bits hence max types =255 */
} imu_ctrl_msg_subtype_t;

/*! @brief IMU message header structure. */
typedef struct IMU_Hdr_t_
{
    volatile uint8_t type;
    volatile uint8_t sub_type; // user of icc module needs to define own msg sub_types
    volatile uint8_t seq_num;  // may be used by user of icc module for own purpose
    volatile uint8_t length;   // length of Payload in bytes
} IMU_Hdr_t;

/*! @brief IMU message structure. */
typedef struct IMU_Msg_t_
{
    IMU_Hdr_t Hdr;
    volatile uint32_t PayloadPtr[IMU_PAYLOAD_SIZE];
} IMU_Msg_t;

/*! @brief IMU message wrapper 1. */
typedef struct IMU_Msg_Wrapper_long_t_
{
    volatile uint32_t magic[2];
    IMU_Msg_t msgQ[2][IMU_MAX_MSG_CNT_LONG];
} IMU_Msg_Wrapper_long_t;

/*! @brief IMU message wrapper 2. */
typedef struct IMU_Msg_Wrapper_short_t_
{
    volatile uint32_t magic[2];
    IMU_Msg_t msgQ[2][IMU_MAX_MSG_CNT_SHORT];
} IMU_Msg_Wrapper_short_t;

/* rpmsg_std_hdr contains a reserved field,
 * this implementation of RPMSG uses this reserved
 * field to hold the idx and totlen of the buffer
 * not being returned to the vring in the receive
 * callback function. This way, the no-copy API
 * can use this field to return the buffer later.
 */
struct rpmsg_hdr_reserved
{
    uint16_t rfu; /* reserved for future usage */
    uint16_t idx;
};

/*!
 * Common header for all rpmsg messages.
 * Every message sent/received on the rpmsg bus begins with this header.
 */
struct rpmsg_std_hdr
{
    uint32_t src;                       /*!< source endpoint address */
    uint32_t dst;                       /*!< destination endpoint address */
    struct rpmsg_hdr_reserved reserved; /*!< reserved for future use */
    uint16_t len;                       /*!< length of payload (in bytes) */
    uint16_t flags;                     /*!< message flags */
};

/*!
 * Common message structure.
 * Contains the header and the payload.
 */
struct rpmsg_std_msg
{
    struct rpmsg_std_hdr hdr; /*!< RPMsg message header */
    uint32_t data;            /*!< bytes of message payload data */
};

typedef hal_rpmsg_status_t (*imu_callback_t)(IMU_Msg_t *pImuMsg, uint32_t length);

/*! @brief IMU interrupt callback */
typedef void (*imu_irq_callback_t)(void);

/*! @brief Checks whether a tx buffer queue is empty */
#define IS_WLAN_TXBQ_EMPTY(q) ((q)->writeIndex == (q)->readIndex)

/*! @brief Checks whether a tx buffer queue is full */
#define IS_WLAN_TXBQ_FULL(q)                                                  \
    ((((q)->writeIndex & (1UL << 31U)) != ((q)->readIndex & (1UL << 31U))) && \
     (((q)->writeIndex & IMU_TXQ_ENTRY_MASK) == ((q)->readIndex & IMU_TXQ_ENTRY_MASK)))

/*! @brief Increments write pointer*/
#define INCR_WLAN_TXBQ_WR_INDEX(q, n)                                \
    {                                                                \
        unsigned int wrapBit = (q)->writeIndex & (1UL << 31U);       \
        unsigned int val     = (q)->writeIndex & IMU_TXQ_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & IMU_TXQ_ENTRY_MASK;     \
        if ((n) > 0U)                                                \
        {                                                            \
            if (newVal <= val)                                       \
            {                                                        \
                (q)->writeIndex = newVal | (wrapBit ^ (1UL << 31U)); \
            }                                                        \
            else                                                     \
            {                                                        \
                (q)->writeIndex = newVal | wrapBit;                  \
            }                                                        \
        }                                                            \
    }

/*! @brief Increments read pointer */
#define INCR_WLAN_TXBQ_RD_INDEX(q, n)                               \
    {                                                               \
        unsigned int wrapBit = (q)->readIndex & (1UL << 31U);       \
        unsigned int val     = (q)->readIndex & IMU_TXQ_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & IMU_TXQ_ENTRY_MASK;    \
        if ((n) > 0U)                                               \
        {                                                           \
            if (newVal <= val)                                      \
            {                                                       \
                (q)->readIndex = newVal | (wrapBit ^ (1UL << 31U)); \
            }                                                       \
            else                                                    \
            {                                                       \
                (q)->readIndex = newVal | wrapBit;                  \
            }                                                       \
        }                                                           \
    }

/*! @brief Checks whether a tx buffer queue is empty */
#define IS_RPMSG_TXBQ13_EMPTY(q) ((q)->writeIndex == (q)->readIndex)
#define IS_RPMSG_TXBQ23_EMPTY(q) ((q)->writeIndex == (q)->readIndex)

/*! @brief Checks whether a tx buffer queue is full */
#define IS_RPMSG_TXBQ13_FULL(q)                                               \
    ((((q)->writeIndex & (1UL << 31U)) != ((q)->readIndex & (1UL << 31U))) && \
     (((q)->writeIndex & RPMSG_TXQ13_ENTRY_MASK) == ((q)->readIndex & RPMSG_TXQ13_ENTRY_MASK)))
#define IS_RPMSG_TXBQ23_FULL(q)                                               \
    ((((q)->writeIndex & (1UL << 31U)) != ((q)->readIndex & (1UL << 31U))) && \
     (((q)->writeIndex & RPMSG_TXQ23_ENTRY_MASK) == ((q)->readIndex & RPMSG_TXQ23_ENTRY_MASK)))

/*! @brief Increments write pointer*/
#define INCR_RPMSG_TXBQ13_WR_INDEX(q, n)                                 \
    {                                                                    \
        unsigned int wrapBit = (q)->writeIndex & (1UL << 31U);           \
        unsigned int val     = (q)->writeIndex & RPMSG_TXQ13_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & RPMSG_TXQ13_ENTRY_MASK;     \
        if ((n) > 0U)                                                    \
        {                                                                \
            if (newVal <= val)                                           \
            {                                                            \
                (q)->writeIndex = newVal | (wrapBit ^ (1UL << 31U));     \
            }                                                            \
            else                                                         \
            {                                                            \
                (q)->writeIndex = newVal | wrapBit;                      \
            }                                                            \
        }                                                                \
    }

#define INCR_RPMSG_TXBQ23_WR_INDEX(q, n)                                 \
    {                                                                    \
        unsigned int wrapBit = (q)->writeIndex & (1UL << 31U);           \
        unsigned int val     = (q)->writeIndex & RPMSG_TXQ23_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & RPMSG_TXQ23_ENTRY_MASK;     \
        if ((n) > 0U)                                                    \
        {                                                                \
            if (newVal <= val)                                           \
            {                                                            \
                (q)->writeIndex = newVal | (wrapBit ^ (1UL << 31U));     \
            }                                                            \
            else                                                         \
            {                                                            \
                (q)->writeIndex = newVal | wrapBit;                      \
            }                                                            \
        }                                                                \
    }

/*! @brief Increments read pointer */
#define INCR_RPMSG_TXBQ13_RD_INDEX(q, n)                                \
    {                                                                   \
        unsigned int wrapBit = (q)->readIndex & (1UL << 31U);           \
        unsigned int val     = (q)->readIndex & RPMSG_TXQ13_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & RPMSG_TXQ13_ENTRY_MASK;    \
        if ((n) > 0U)                                                   \
        {                                                               \
            if (newVal <= val)                                          \
            {                                                           \
                (q)->readIndex = newVal | (wrapBit ^ (1UL << 31U));     \
            }                                                           \
            else                                                        \
            {                                                           \
                (q)->readIndex = newVal | wrapBit;                      \
            }                                                           \
        }                                                               \
    }

#define INCR_RPMSG_TXBQ23_RD_INDEX(q, n)                                \
    {                                                                   \
        unsigned int wrapBit = (q)->readIndex & (1UL << 31U);           \
        unsigned int val     = (q)->readIndex & RPMSG_TXQ23_ENTRY_MASK; \
        unsigned int newVal  = (val + (n)) & RPMSG_TXQ23_ENTRY_MASK;    \
        if ((n) > 0U)                                                   \
        {                                                               \
            if (newVal <= val)                                          \
            {                                                           \
                (q)->readIndex = newVal | (wrapBit ^ (1UL << 31U));     \
            }                                                           \
            else                                                        \
            {                                                           \
                (q)->readIndex = newVal | wrapBit;                      \
            }                                                           \
        }                                                               \
    }

typedef struct _hal_rpmsg_rx_state
{
    rpmsg_rx_callback_t callback;
    void *param;
} hal_rpmsg_rx_state_t;

/*! @brief rpmsg state structure. */
typedef struct _hal_rpmsg_state
{
    LIST_ELEM_st eptLink;
    uint32_t local_addr;
    uint32_t remote_addr;
    uint8_t imuLink;
    bool eptLinkIsReady;
    hal_rpmsg_rx_state_t rx;
} hal_rpmsg_state_t;

/*! @brief rpmsg ept buf structure. */
typedef struct _hal_rpmsg_ept_uf
{
    LIST_ELEM_st eptLink;
    uint32_t addr;
} hal_rpmsg_ept_buf_t;

/*! @brief IMU WLAN Tx buffer control structure */
typedef struct IMU_WLAN_TXQ_CTRL_st
{
    uint32_t writeIndex;
    uint32_t readIndex;
    uint32_t txBufQue[IMU_TXQ_BUFSIZE];
} IMU_WLAN_TXQ_CTRL_st;

/*! @brief RPMSG Tx buffer control structure */
typedef struct RPMSG_TXQ_CTRL_st
{
    uint32_t writeIndex;
    uint32_t readIndex;
    uint32_t txBufQue[RPMSG_TXQ23_BUFSIZE];
} RPMSG_TXQ_CTRL_st;

/*! @brief imu handle structure. */
typedef struct _hal_imu_handle_t
{
    /*! Word 0 */
    uint8_t imuLink;
    uint8_t imuSyncState; /*！ 0：Link Off, 1:Link Ongoing, 2: Link Up */
    uint8_t freeTxMportBufCnt;
    uint8_t imuMsgBufIdx;
    /*! Word 1 */
    bool cmd_buffer_available;
    bool cmd_response_buffer_available;
    bool rsvdbool1;
    bool rsvdbool2;
    /*! Word 2 */
    uint32_t *cmd_buffer;
    /*! Word 3 */
    IMU_WLAN_TXQ_CTRL_st wlanTxqCtl;
    /*! Word 37 */
    uint32_t imuMsgBuf[IMU_PAYLOAD_SIZE];
    /*! Word 45 */
    LIST_ELEM_st eptList;
    /*! Word 47 */
    RPMSG_TXQ_CTRL_st rpmsgTxqCtl;
    /*! Word 57 */
    imu_callback_t imuHandler[IMU_MSG_MAX];
} hal_imu_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Add wlan Tx packet for sending multiple Tx packets within one message.
 *
 * This function is used to add a wlan Tx packet for IMU_MSG_MULTI_TX_DATA.
 *
 * @param imuLink           IMU link ID.
 * @param txBuf             Tx buffer to be sent.
 * @param length            Length of Tx data.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuAddWlanTxPacket(uint8_t imuLink, uint8_t *txBuf, uint32_t length);

/*!
 * @brief Add wlan Tx packet for sending multiple Tx packets within one message.
 *
 * This function is used to add a wlan Tx packet with callback function for IMU_MSG_MULTI_TX_DATA.
 *
 * @param imuLink           IMU link ID.
 * @param txBuf             Tx buffer to be sent.
 * @param length            Length of Tx data.
 * @param cb                Callback function to add packet.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuAddWlanTxPacketExt(uint8_t imuLink,
                                             uint8_t *txBuf,
                                             uint32_t length,
                                             void (*cb)(void *destAddr, void *srcAddr, uint32_t len));

/*!
 * @brief Install wlan callback.
 *
 * This function is used to imstall wlan callback
 *
 * @param imuLink        IMU link ID.
 * @param callback       Callback to be installed.
 * @param type           Callback type.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuInstallCallback(uint8_t imuLink, imu_callback_t callback, uint8_t type);

/*!
 * @brief Install imu interrupt callback.
 *
 * This function is used to install imu interrupt callback
 *
 * @param imuLink        IMU link ID.
 * @param callback       Callback to be installed.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuInstallIrqCallback(uint8_t imuLink, imu_irq_callback_t callback);

/*!
 * @brief Send wlan command packet.
 *
 * This function is used to send wlan command packet
 *
 * @param imuLink        IMU link ID.
 * @param cmdBuf         Command buffer to be sent.
 * @param length         Length of command data.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuSendCommand(uint8_t imuLink, uint8_t *cmdBuf, uint32_t length);

/*!
 * @brief Add wlan Tx packet for sending one Tx packet within one message.
 *
 * This function is used to send a wlan Tx packet.
 *
 * @param imuLink           IMU link ID.
 * @param txBuf             Tx buffer to be sent.
 * @param length            Length of Tx data.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuSendTxData(uint8_t imuLink, uint8_t *txBuf, uint32_t length);

/*!
 * @brief Send multiple Tx packets within one message.
 *
 * This function is used to send multiple wlan Tx packets within one IMU message,
 * which have been added by HAL_ImuAddWlanTxPacket already.
 *
 * @param imuLink           IMU link ID.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuSendMultiTxData(uint8_t imuLink);

/*!
 * @brief Check if IMU link is up.
 *
 * This function is used to check if IMU link is up.
 *
 * @param imuLink        IMU link ID.
 * @retval kStatus_HAL_RpmsgSuccess for IMU link up or kStatus_HAL_RpmsgError for IMU link not up.
 */
hal_rpmsg_status_t HAL_ImuLinkIsUp(uint8_t imuLink);

/*!
 * @brief Start IMU link
 *
 * This function is used to start specified IMU link.
 *
 * @param imuLink        IMU link ID.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuInit(imu_link_t link);

/*!
 * @brief Stop IMU link
 *
 * This function is used to stop specified IMU link.
 *
 * @param imuLink        IMU link ID.
 * @param flag           flag with bits to control.
 *        flag bit0: control if need send imu msg to fw (imu tx return /imu shutdown)
 *        flag bit1: control if need destroy ImuTask and ImuQFlagsRef
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuDeinit(imu_link_t link, uint32_t flag);

/*!
 * @brief Return all tx buffer.
 *
 * This function is used to return all tx buffer to CPU1.
 *
 * @param imuLink              IMU link ID.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuReturnAllTxBuf(imu_link_t link);

/*!
 * @brief Receive IMU message.
 *
 * This function is used to receive and process IMU message
 *
 * @param imuLink              IMU link ID.
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuReceive(uint8_t imuLink);

/*!
 * @brief Check if tx buffer queue empty.
 *
 * This function is used to check if tx buffer queue empty
 *
 * @param imuLink              IMU link ID.
 * @retval TRUE or FALSE.
 */
bool HAL_ImuIsTxBufQueueEmpty(uint8_t imuLink);

#if defined(IMU_GDMA_ENABLE) && (IMU_GDMA_ENABLE == 1)
/*!
 * @brief Copy data by GDMA.
 *
 * This function is used to copy data by GDMA between shared memory and local memory.
 *
 * @param destAddr          Source address of data.
 * @param srcAddr           Destination address of data.
 * @param len               Data Length.
 */
void HAL_ImuGdmaCopyData(void *destAddr, void *srcAddr, uint32_t len);

/*! @}*/
#endif

#ifdef CONFIG_FW_DUMP_EVENT
/*!
 * @brief Send fw dump event ack.
 *
 * This function is used to Send fw dump event ack to fw, When the event data process is completed.
 *
 * @param imuLink              IMU link ID.
 * @param rxBuf                Rx buffer to be sent.
 * @param length               Length of Rx buffer
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuSendEventDumpAck(imu_link_t link, uint8_t *rxBuf, uint8_t length);
#endif

/*!
 * @brief Create imu task mutex.
 *
 * This function creates a imu task mutex.
 *
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuCreateTaskLock(void);

/*!
 * @brief Delete imu task mutex.
 *
 * This function deletes the imu task mutex.
 */
void HAL_ImuDeleteTaskLock(void);

/*!
 * @brief Acquire imu task mutex.
 *
 * This function acquires the imu task mutex. Only one thread can acquire the mutex at any
 * given time.
 *
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuGetTaskLock(void);

/*!
 * @brief Release imu task mutex.
 *
 * This function releases the imu task mutex.
 *
 * @retval kStatus_HAL_RpmsgSuccess or kStatus_HAL_RpmsgError.
 */
hal_rpmsg_status_t HAL_ImuPutTaskLock(void);

/*!
 * @brief Reset imu readIndex and writeIndex to 0.
 *
 * This function reset the imu txq.
 */
void HAL_ImuResetWlanTxq(uint8_t imuLink);

#if defined(__cplusplus)
}
#endif
/*! @}*/
#endif /* __FSL_ADAPTER_RFIMU_H__ */
