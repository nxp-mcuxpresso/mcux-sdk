/*
 *
 * Copyright  2016-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LIN_H_
#define FSL_LIN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_common.h"

/*!
 * @addtogroup lin_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief LIN driver version */
#define FSL_LIN_DRIVER_VERSION (MAKE_VERSION(2, 2, 1))

/* node is slave */
#define LIN_SLAVE 0U
/* node si master */
#define LIN_MASTER 1U
/* make PID parity */
#define MAKE_PARITY 0U
/* check for PID parity */
#define CHECK_PARITY 1U
/* one time unit is 500 us */
#define LIN_TIME_OUT_UNIT_US 500U

/* make unconditional frame */
#define LIN_MAKE_UNCONDITIONAL_FRAME 0U
/* update unconditional frame */
#define LIN_UPDATE_UNCONDITIONAL_FRAME 1U
/* number of supported baudrates for autobaud features */
#define LIN_NUM_OF_SUPP_BAUDRATES 5U

/*!
 * @brief Callback function to get time interval in nano seconds
 */
typedef void (*lin_timer_get_time_interval_t)(uint32_t *nanoSeconds);
/*!
 * @brief LIN Driver callback function type
 */
typedef void (*lin_callback_t)(uint32_t instance, void *linState);

/*!
 * @brief List of LIN frame types.
 */
typedef enum
{
    LIN_FRM_UNCD  = 0x00U, /*!< unconditional frame */
    LIN_FRM_EVNT  = 0x01U, /*!< event triggered frame */
    LIN_FRM_SPRDC = 0x10U, /*!< sporadic frame */
    LIN_FRM_DIAG  = 0x11U  /*!< diagnostic frame */
} lin_frame_type;

/*!
 * @brief List of LIN frame response types.
 */
typedef enum
{
    LIN_RES_NOTHING = 0x00U, /*!< node is neither publisher nor subscriber */
    LIN_RES_PUB     = 0x01U, /*!< node is publisher */
    LIN_RES_SUB     = 0x10U  /*!< node is subscriber */
} lin_frame_response;

/*!
 * @brief Diagnostic mode
 */
typedef enum
{
    DIAG_NONE            = 0x00U, /*!< None */
    DIAG_INTERLEAVE_MODE = 0x01U, /*!< Interleave mode */
    DIAG_ONLY_MODE       = 0x02U  /*!< Diagnostic only mode */
} lin_diagnostic_mode;

/*!
 * @brief LIN hardware configuration structure
 */
typedef struct
{
    uint8_t hardware_instance; /*!< interface instance number */
    uint32_t baudRate;         /*!< baudrate of LIN Hardware Interface to configure */
    bool nodeFunction;         /*!< Node function as Master or Slave */
    bool autobaudEnable;       /*!< Enable Autobaud feature */
    lin_timer_get_time_interval_t
        timerGetTimeIntervalCallback; /*!< Callback function to get time interval in nano seconds */
} lin_user_config_t;

/*!
 * @brief Defines types for an enumerating event related to an Identifier.
 */
typedef enum
{
    LIN_NO_EVENT                  = 0x00U, /*!< No event yet */
    LIN_WAKEUP_SIGNAL             = 0x01U, /*!< Received a wakeup signal */
    LIN_BAUDRATE_ADJUSTED         = 0x02U, /*!< Indicate that baudrate was adjusted to Master's baudrate */
    LIN_RECV_BREAK_FIELD_OK       = 0x03U, /*!< Indicate that correct Break Field was received */
    LIN_SYNC_OK                   = 0x04U, /*!< Sync byte is correct */
    LIN_SYNC_ERROR                = 0x05U, /*!< Sync byte is incorrect */
    LIN_PID_OK                    = 0x06U, /*!< PID correct */
    LIN_PID_ERROR                 = 0x07U, /*!< PID incorrect */
    LIN_FRAME_ERROR               = 0x08U, /*!< Framing Error */
    LIN_READBACK_ERROR            = 0x09U, /*!< Readback data is incorrect */
    LIN_CHECKSUM_ERROR            = 0x0AU, /*!< Checksum byte is incorrect */
    LIN_TX_COMPLETED              = 0x0BU, /*!< Sending data completed */
    LIN_RX_COMPLETED              = 0x0CU, /*!< Receiving data completed */
    LIN_NO_DATA_TIMEOUT           = 0x0DU, /*!< No data timeout */
    LIN_BUS_ACTIVITY_TIMEOUT      = 0x0EU, /*!< Bus activity timeout */
    LIN_TIMEOUT_ERROR             = 0x0FU, /*!< Indicate that timeout has occurred */
    LIN_LAST_RESPONSE_SHORT_ERROR = 0x10U  /*!< Indicate that the last frame was too short */
} lin_event_id_t;

/*!
 * @brief Defines Error codes of the LIN driver.
 */
typedef enum
{
    LIN_IFC_NOT_SUPPORT             = 0x00U, /*!< This interface is not supported */
    LIN_INITIALIZED                 = 0x01U, /*!< LIN Hardware has been initialized */
    LIN_SUCCESS                     = 0x02U, /*!< Successfully done */
    LIN_ERROR                       = 0x03U, /*!< Error */
    LIN_TX_BUSY                     = 0x04U, /*!< Transmitter is busy */
    LIN_RX_BUSY                     = 0x05U, /*!< Receiver is busy */
    LIN_BUS_BUSY                    = 0x06U, /*!< Bus is busy */
    LIN_NO_TRANSFER_IN_PROGRESS     = 0x07U, /*!< No data transfer is in progress */
    LIN_TIMEOUT                     = 0x08U, /*!< Timeout */
    LIN_LPUART_STAT_CLOCK_GATED_OFF = 0x09U  /*!< LPUART is gated from clock manager */
} lin_status_t;

/*!
 * @brief Define type for an enumerating LIN Node state.
 */
typedef enum
{
    LIN_NODE_STATE_UNINIT              = 0x00U, /*!< Uninitialized state */
    LIN_NODE_STATE_SLEEP_MODE          = 0x01U, /*!< Sleep mode state */
    LIN_NODE_STATE_IDLE                = 0x02U, /*!< Idle state */
    LIN_NODE_STATE_SEND_BREAK_FIELD    = 0x03U, /*!< Send break field state */
    LIN_NODE_STATE_RECV_SYNC           = 0x04U, /*!< Receive the synchronization byte state */
    LIN_NODE_STATE_SEND_PID            = 0x05U, /*!< Send PID state */
    LIN_NODE_STATE_RECV_PID            = 0x06U, /*!< Receive PID state */
    LIN_NODE_STATE_RECV_DATA           = 0x07U, /*!< Receive data state */
    LIN_NODE_STATE_RECV_DATA_COMPLETED = 0x08U, /*!< Receive data completed state */
    LIN_NODE_STATE_SEND_DATA           = 0x09U, /*!< Send data state */
    LIN_NODE_STATE_SEND_DATA_COMPLETED = 0x0AU  /*!< Send data completed state */
} lin_node_state_t;

/*!
 *  @brief List of protocols
 */
typedef enum
{
    LIN_PROTOCOL_21    = 0x00U, /*!< LIN protocol version 2.1 */
    LIN_PROTOCOL_J2602 = 0x01U  /*!< J2602 protocol */
} lin_protocol_handle;

/*!
 *  @brief List of supported baudrates for autobaud feature
 */
typedef enum
{
    kLIN_BAUD_2400,
    kLIN_BAUD_4800,
    kLIN_BAUD_9600,
    kLIN_BAUD_14400,
    kLIN_BAUD_19200
} lin_supported_baudrates_t;

/*!
 * @brief Runtime state of the LIN driver.
 *
 * Note that the caller provides memory for the driver state structures during
 * initialization because the driver does not statically allocate memory.
 */
typedef struct
{
    const uint8_t *txBuff; /*!< The buffer of data being sent. */
    uint8_t *rxBuff;       /*!< The buffer of received data. */
    uint8_t frame_index;
    uint8_t cntByte;            /*!< To count number of bytes already transmitted or received. */
    volatile uint8_t txSize;    /*!< The remaining number of bytes to be received. */
    volatile uint8_t rxSize;    /*!< The remaining number of bytes to be received. */
    uint8_t checkSum;           /*!< Checksum byte. */
    volatile bool isTxBusy;     /*!< True if the LIN interface is transmitting frame data. */
    volatile bool isRxBusy;     /*!< True if the LIN interface is receiving frame data. */
    volatile bool isBusBusy;    /*!< True if there are data, frame headers being transferred on bus */
    volatile bool isTxBlocking; /*!< True if transmit is blocking transaction. */
    volatile bool isRxBlocking; /*!< True if receive is blocking transaction. */
    lin_callback_t Callback;    /*!< Callback function to invoke after receiving a byte or transmitting a byte. */
    uint8_t currentId;          /*!< Current ID */
    uint8_t currentPid;         /*!< Current PID */
    volatile lin_event_id_t currentEventId;     /*!< Current ID Event */
    volatile lin_node_state_t currentNodeState; /*!< Current Node state */
    volatile uint32_t timeoutCounter;           /*!< Value of the timeout counter */
    volatile bool timeoutCounterFlag;           /*!< Timeout counter flag */
    volatile bool baudrateEvalEnable;           /*!< Baudrate Evaluation Process Enable */
    volatile uint8_t fallingEdgeInterruptCount; /*!< Falling Edge count of a sync byte */
    uint32_t linSourceClockFreq;                /*!< Frequency of the source clock for LIN */
    volatile bool txCompleted;                  /*!< Used to wait for LIN interface ISR to complete transmission.*/
    volatile bool rxCompleted;                  /*!< Used to wait for LIN interface ISR to complete reception*/
} lin_state_t;

/*!
 *  @brief Structure of baudrate properties
 */
typedef struct
{
    uint32_t baudRate;
    uint32_t osrValue;
    uint16_t sbrValue;
} lin_baudrate_values_t;

/*!
 *  @brief Informations of frame
 */
typedef struct
{
    lin_frame_type frm_type;         /*!< Frame information (unconditional or event triggered..) */
    uint8_t frm_len;                 /*!< Length of the frame */
    lin_frame_response frm_response; /*!< Action response when received PID */
    uint8_t frm_offset;              /*!< Frame byte offset in frame buffer */
    uint8_t flag_offset;             /*!< Flag byte offset in flag buffer */
    uint8_t flag_size;               /*!< Flag size in flag buffer */
    uint32_t delay;                  /*!< Frame delay */
    const uint8_t *frame_data_ptr;   /*!< List of Signal to which the frame is associated and its offset */
} lin_frame_struct;

/*!
 *  @brief Protocol configuration structure
 */
typedef struct
{
    lin_protocol_handle protocol_version;     /*!< Protocol version */
    lin_protocol_handle language_version;     /*!< Language version */
    uint8_t number_of_configurable_frames;    /*!< Number of frame except diagnostic frames */
    uint8_t frame_start;                      /*!< Start index of frame list */
    const lin_frame_struct *frame_tbl_ptr;    /*!< Frame list except diagnostic frames */
    const uint16_t *list_identifiers_ROM_ptr; /*!< Configuration in ROM */
    uint8_t *list_identifiers_RAM_ptr;        /*!< Configuration in RAM */
    uint16_t max_idle_timeout_cnt;            /*!< Max Idle timeout counter */
    uint16_t max_message_length;              /*!< Max message length*/
} lin_protocol_user_config_t;                 /* defined in lin_cfg.c */

/*!
 * @brief Product id structure
 */
typedef struct
{
    uint16_t supplier_id; /*!< Supplier ID */
    uint16_t function_id; /*!< Function ID */
    uint8_t variant;      /*!< Variant value */
} lin_product_id;

/*!
 *  @brief Serial number
 */
typedef struct
{
    uint8_t serial_0; /*!< Serial 0 */
    uint8_t serial_1; /*!< Serial 1 */
    uint8_t serial_2; /*!< Serial 2 */
    uint8_t serial_3; /*!< Serial 3 */
} lin_serial_number;

/*!
 * @brief Protocol state structure
 */
typedef struct
{
    /* LIN data pointer */
    uint16_t baud_rate;           /*!< Adjusted baud rate */
    uint8_t *response_buffer_ptr; /*!< Response buffer */
    uint8_t response_length;      /*!< Response length  */
    uint8_t successful_transfer;  /*!< Sets when frame is transferred successfully */
    uint8_t error_in_response;   /*!< Sets when frame received/transmitter by the node contains an error in the response
                                    field */
    uint8_t timeout_in_response; /*!< Timeout response */
    bool go_to_sleep_flg;        /*!< Go to sleep flag */
    uint8_t current_id;          /*!< Current PID */
    uint8_t num_of_processed_frame;      /*!< Number of processed frames */
    uint8_t num_of_successfull_frame;    /*!< Number of processed frames */
    uint8_t next_transmit_tick;          /*!< Used to count the next transmit tick */
    bool save_config_flg;                /*!< Set when save configuration request has been received */
    lin_diagnostic_mode diagnostic_mode; /*!< Diagnostic mode */
    uint16_t frame_timeout_cnt;          /*!< Frame timeout counter */
    uint16_t idle_timeout_cnt;           /*!< Idle timeout counter, node will go to sleep when count down to 0 */
    bool transmit_error_resp_sig_flg;    /*!< Flag indicates that the error response signal is going to be sent */
    bool event_trigger_collision_flg;    /*!< Flag indicates collision on bus */
} lin_protocol_state_t;

/*!
 * @brief Attributes of LIN node
 */
typedef struct
{
    uint8_t *configured_NAD_ptr; /*!< NAD value used in configuration command */
    uint8_t initial_NAD;         /*!< Initial NAD */
    lin_product_id product_id;   /*!< Product ID */
    /* TODO */
    lin_serial_number serial_number; /*!< Serial number */
    uint8_t *resp_err_frm_id_ptr;    /*!< Pointer to the list of index of frames that carries response error signal */
    uint8_t num_frame_have_esignal;  /*!< The count of frames that carry response error signal */
    uint8_t response_error_byte_offset; /*!< Byte offset of response error signal */
    uint8_t response_error_bit_offset;  /*!< Bit offset of response error signal */
    uint8_t num_of_fault_state_signal;  /*!< Number of Fault state signal */
    uint16_t P2_min;                    /*!< P2 min */
    uint16_t ST_min;                    /*!< ST min */
    uint16_t N_As_timeout;              /*!< N_As_timeout */
    uint16_t N_Cr_timeout;              /*!< N_Cr_timeout */
} lin_node_attribute;

/*!
 * @brief LIN master data structure
 */
typedef struct
{
    uint8_t active_schedule_id;        /*!< Active schedule table id */
    uint8_t previous_schedule_id;      /*!< Previous schedule table id */
    uint8_t *schedule_start_entry_ptr; /*!< Start entry of each schedule table */
    bool event_trigger_collision_flg;
    uint8_t data_buffer[8]; /*!< Master data buffer */
    uint8_t frm_offset;
    uint8_t frm_size;
} lin_master_data_t;

/*! @brief Table of base addresses for LPUART instances. */
extern LPUART_Type *const g_linLpuartBase[FSL_FEATURE_SOC_LPUART_COUNT];

/*! @brief Table to save LPUART IRQ enumeration numbers defined in the CMSIS header file */
extern const IRQn_Type g_linLpuartRxTxIrqId[FSL_FEATURE_SOC_LPUART_COUNT];

#ifdef LPUART_ERR_IRQS
extern const IRQn_Type g_linLpuartErrIrqId[FSL_FEATURE_SOC_LPUART_COUNT];
#endif

/*! @brief Table to save LIN user config buadrate values */
extern lin_baudrate_values_t g_linConfigBaudrates[LIN_NUM_OF_SUPP_BAUDRATES];
/*! @brief Pointers to LPUART bases for each instance. */

/*! @brief Table to save LPUART state structure pointers */
extern lin_state_t *g_linStatePtr[FSL_FEATURE_SOC_LPUART_COUNT];

/*! @brief Table to save LIN user config structure pointers */
extern lin_user_config_t *g_linUserconfigPtr[FSL_FEATURE_SOC_LPUART_COUNT];

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name LIN DRIVER
 * @{
 */

/*!
 * @brief Calculates maximal header time lenght
 *
 *  Theader_Maximum = 1.4 * THeader_Nominal, THeader_Nominal = 34 * TBit,
 * ( 13 nominal bits of breack;   1 nominal bit of break delimiter; 10 bits for SYNC and 10 bits of PID)
 * The function is not include time for conveying break and break delimiter
 * TIME_OUT_UNIT is in micro second
 * @param baudRate baudrate
 *
 */
uint32_t LIN_CalcMaxHeaderTimeoutCnt(uint32_t baudRate);
/*!
 * @brief Calculates maximal header time length
 *
 *  TResponse_Maximum = 1.4 * TResponse_Nominal, TResponse_Nominal = 10 * (NData+ 1) * TBit
 *
 * @param baudRate Baudrate
 * @param size Frame size
 *
 */
uint32_t LIN_CalcMaxResTimeoutCnt(uint32_t baudRate, uint8_t size);

/*!
 * @brief Forwards a response to a lower level
 *
 * @param instance LPUART instance
 * @param response_buff response message
 * @param response_length length of response
 * @param max_frame_res_timeout maximal timeout duration for message
 * @return An error code or lin_status_t
 */
lin_status_t LIN_SetResponse(uint8_t instance,
                             uint8_t *response_buff,
                             uint8_t response_length,
                             uint8_t max_frame_res_timeout);
/*!
 * @brief Forwards a response to a higher level
 *
 * @param instance LPUART instance
 * @param response_buff response message
 * @param response_length length of response
 * @param max_frame_res_timeout maximal timeout duration for message
 * @return An error code or lin_status_t
 */
lin_status_t LIN_RxResponse(uint8_t instance,
                            uint8_t *response_buff,
                            uint8_t response_length,
                            uint8_t max_frame_res_timeout);
/*!
 * @brief Put a node into idle state
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_IgnoreResponse(uint8_t instance);
/*!
 * @brief Initializes linUserConfig variable for a slave node
 *
 * @param linUserConfig Pointer to LIN user config structure
 */
void LIN_GetSlaveDefaultConfig(lin_user_config_t *linUserConfig);
/*!
 * @brief Initializes linUserConfig variable for a master node
 *
 * @param linUserConfig Pointer to LIN user config structure
 */
void LIN_GetMasterDefaultConfig(lin_user_config_t *linUserConfig);
/*!
 * @brief Calculates baudrate registers values for given baudrate
 *
 * @param instance LPUART instance
 * @param instance baudRate_Bps LPUART baudrate
 * @param instance srcClock_Hz LPUART clock frequency
 * @param instance osr LPUART baudrate OSR value, return value
 * @param instance sbr LPUART baudrate SBR value, return value
 *
 */
void LIN_CalculateBaudrate(
    uint32_t instance, uint32_t baudRate_Bps, uint32_t srcClock_Hz, uint32_t *osr, uint16_t *sbr);
/*!
 * @brief Set baudrate registers values
 *
 * @param instance LPUART instance
 * @param instance osr LPUART baudrate OSR value
 * @param instance sbr LPUART baudrate SBR value
 *
 */
void LIN_SetBaudrate(uint32_t instance, uint32_t osr, uint16_t sbr);
/*!
 * @brief Initializes an instance LIN Hardware Interface for LIN Network.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LIN Hardware Interface clock source in the application to initialize the LIN Hardware
 * Interface.
 *
 * @param instance LPUART instance
 * @param linUserConfig user configuration structure of type #lin_user_config_t
 * @param linCurrentState pointer to the LIN Hardware Interface driver state structure
 * @return An error code or lin_status_t
 */
lin_status_t LIN_Init(uint32_t instance,
                      lin_user_config_t *linUserConfig,
                      lin_state_t *linCurrentState,
                      uint32_t clockSource);

/*!
 * @brief Shuts down the LIN Hardware Interface by disabling interrupts and transmitter/receiver.
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_Deinit(uint32_t instance);

/*!
 * @brief Installs callback function that is used for LIN_DRV_IRQHandler.
 *
 * @note After a callback is installed, it bypasses part of the LIN Hardware Interface IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * @param instance LPUART instance.
 * @param function the LIN receive callback function.
 * @return Former LIN callback function pointer.
 */
lin_callback_t LIN_InstallCallback(uint32_t instance, lin_callback_t function);

/*!
 * @brief Sends Frame data out through the LIN Hardware Interface using blocking method.
 *  This function will calculate the checksum byte and send it with the frame data.
 *  Blocking means that the function does not return until the transmission is complete.
 *
 * @param instance LPUART instance
 * @param txBuff source buffer containing 8-bit data chars to send
 * @param txSize the number of bytes to send
 * @param timeoutMSec timeout value in milli seconds
 * @return An error code or lin_status_t LIN_BUS_BUSY if the bus is currently busy, transmission
 * cannot be started.
 */
lin_status_t LIN_SendFrameDataBlocking(uint32_t instance, const uint8_t *txBuff, uint8_t txSize, uint32_t timeoutMSec);

/*!
 * @brief Sends frame data out through the LIN Hardware Interface using non-blocking method.
 *  This enables an a-sync method for transmitting data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the transmit status to know when the transmit is complete.
 *  This function will calculate the checksum byte and send it with the frame data.
 * @note If users use LIN_TimeoutService in a timer interrupt handler, then before using this function,
 * users have to set timeout counter to an appropriate value by using LIN_SetTimeoutCounter(instance, timeoutValue).
 * The timeout value should be big enough to complete the transmission. Timeout in real time is (timeoutValue) * (time
 * period that LIN_TimeoutService is called). For example, if LIN_TimeoutService is called in an timer
 * interrupt with period of 500 micro seconds, then timeout in real time is
 * timeoutValue * 500 micro seconds.
 * @param instance LPUART instance
 * @param txBuff  source buffer containing 8-bit data chars to send
 * @param txSize  the number of bytes to send
 * @return An error code or lin_status_t LIN_BUS_BUSY if the bus is currently busy, transmission
 * cannot be started. LIN_SUCCESS if the transmission was completed.
 */
lin_status_t LIN_SendFrameData(uint32_t instance, const uint8_t *txBuff, uint8_t txSize);

/*!
 * @brief Get status of an on-going non-blocking transmission
 *  While sending frame data using non-blocking method, users can
 *  use this function to get status of that transmission.
 *  The bytesRemaining shows number of bytes that still needed to transmit.
 *
 * @param instance LPUART instance
 * @param bytesRemaining Number of bytes still needed to transmit
 * @return lin_status_t LIN_TX_BUSY if the transmission is still in progress.
 * LIN_TIMEOUT if timeout occurred and transmission was not completed.
 * LIN_SUCCESS if the transmission was successful.
 */
lin_status_t LIN_GetTransmitStatus(uint32_t instance, uint8_t *bytesRemaining);

/*!
 * @brief Receives frame data through the LIN Hardware Interface using blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it
 *  will receive the frame data. Blocking means that the function does
 *  not return until the reception is complete.
 *
 * @param instance LPUART instance
 * @param rxBuff  buffer containing 8-bit received data
 * @param rxSize the number of bytes to receive
 * @param timeoutMSec timeout value in milli seconds
 * @return An error code or lin_status_t
 */
lin_status_t LIN_ReceiveFrameDataBlocking(uint32_t instance, uint8_t *rxBuff, uint8_t rxSize, uint32_t timeoutMSec);

/*!
 * @brief Receives frame data through the LIN Hardware Interface using non- blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it
 *  will receive it with the frame data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the receive status to know when the reception is complete.
 * @note If users use LIN_TimeoutService in a timer interrupt handler, then before using this function,
 * users have to set timeout counter to an appropriate value by using LIN_SetTimeoutCounter(instance, timeoutValue).
 * The timeout value should be big enough to complete the reception. Timeout in real time is (timeoutValue) * (time
 * period
 * that LIN_TimeoutService is called). For example, if LIN_TimeoutService is called in an timer
 * interrupt with period of 500 micro seconds, then timeout in real time is
 * timeoutValue * 500 micro seconds.
 *
 * @param instance LPUART instance
 * @param rxBuff  buffer containing 8-bit received data
 * @param rxSize the number of bytes to receive
 * @return An error code or lin_status_t
 */
lin_status_t LIN_ReceiveFrameData(uint32_t instance, uint8_t *rxBuff, uint8_t rxSize);

/*!
 * @brief Aborts an on-going non-blocking transmission/reception.
 *  While performing a non-blocking transferring data, users can call this function
 *  to terminate immediately the transferring.
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_AbortTransferData(uint32_t instance);

/*!
 * @brief Get status of an on-going non-blocking reception
 *  While receiving frame data using non-blocking method, users can
 *  use this function to get status of that receiving.
 *  This function return the current event ID, LIN_RX_BUSY while receiving
 *  and return LIN_SUCCESS, or timeout (LIN_TIMEOUT) when the reception is complete.
 *  The bytesRemaining shows number of bytes that still needed to receive.
 *
 * @param instance LPUART instance
 * @param bytesRemaining Number of bytes still needed to receive
 * @return lin_status_t LIN_RX_BUSY, LIN_TIMEOUT or LIN_SUCCESS
 */
lin_status_t LIN_GetReceiveStatus(uint32_t instance, uint8_t *bytesRemaining);

/*!
 * @brief Puts current LIN node to sleep mode
 * This function changes current node state to LIN_NODE_STATE_SLEEP_MODE
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_GoToSleepMode(uint32_t instance);

/*!
 * @brief Puts current LIN node to Idle state
 * This function changes current node state to LIN_NODE_STATE_IDLE
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_GotoIdleState(uint32_t instance);

/*!
 * @brief Sends a wakeup signal through the LIN Hardware Interface
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_SendWakeupSignal(uint32_t instance);

/*!
 * @brief Get the current LIN node state
 *
 * @param instance LPUART instance
 * @return current LIN node state
 */
lin_node_state_t LIN_GetCurrentNodeState(uint32_t instance);

/*!
 * @brief Callback function for Timer Interrupt Handler
 * Users may use (optional, not required) LIN_TimeoutService to check if timeout has occurred during non-blocking frame
 * data
 * transmission and reception. User may initialize a timer (for example FTM) in Output Compare Mode
 * with period of 500 micro seconds (recommended). In timer IRQ handler, call this function.
 *
 * @param instance LPUART instance
 * @return void
 */
void LIN_TimeoutService(uint32_t instance);

/*!
 * @brief Set Value for Timeout Counter that is used in LIN_TimeoutService
 *
 * @param instance LPUART instance
 * @param timeoutValue  Timeout Value to be set
 * @return void
 */
void LIN_SetTimeoutCounter(uint32_t instance, uint32_t timeoutValue);

/*!
 * @brief Sends frame header out through the LIN Hardware Interface using a non-blocking method.
 *  This function sends LIN Break field, sync field then the ID with
 *  correct parity.
 *
 * @param instance LPUART instance
 * @param id  Frame Identifier
 * @return An error code or lin_status_t
 */
lin_status_t LIN_MasterSendHeader(uint32_t instance, uint8_t id);

/*!
 * @brief Enables LIN hardware interrupts.
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_EnableIRQ(uint32_t instance);

/*!
 * @brief Disables LIN hardware interrupts.
 *
 * @param instance LPUART instance
 * @return An error code or lin_status_t
 */
lin_status_t LIN_DisableIRQ(uint32_t instance);

/*!
 * @brief Interrupt handler for LIN Hardware Interface.
 *
 * @param instance LPUART instance
 * @return void
 */
void LIN_IRQHandler(uint8_t instance);

/*!
 * @brief This function capture bits time to detect break char, calculate
 * baudrate from sync bits and enable transceiver if autobaud successful.
 * This function should only be used in Slave.
 * The timer should be in mode input capture of both rising and falling edges.
 * The timer input capture pin should be externally connected to RXD pin.
 *
 * @param instance LPUART instance
 * @return lin_status_t
 */
lin_status_t LIN_AutoBaudCapture(uint32_t instance);

/*!
 * @brief Makes or checks parity bits. If action is checking parity, the function
 * returns ID value if parity bits are correct or 0xFF if parity bits are incorrect. If action
 * is making parity bits, then from input value of ID, the function returns PID.
 * This is not a public API as it is called by other API functions.
 *
 * @param PID PID byte in case of checking parity bits or ID byte in case of making parity bits.
 * @param typeAction: 1 for Checking parity bits, 0 for making parity bits
 * @return 0xFF if parity bits are incorrect, ID in case of checking parity bits and
 * they are correct. Function returns PID in case of making parity bits.
 */
uint8_t LIN_ProcessParity(uint8_t PID, uint8_t typeAction);

/*!
 * @brief Makes the checksum byte for a frame
 *
 * @param buffer Pointer to Tx buffer
 * @param sizeBuffer Number of bytes that are contained in the buffer.
 * @param PID Protected Identifier byte.
 * @return the checksum byte.
 */
uint8_t LIN_MakeChecksumByte(const uint8_t *buffer, uint8_t sizeBuffer, uint8_t PID);

/*! @} */

#if defined(__cplusplus)
}
#endif

#endif /* FSL_LIN_H_ */
