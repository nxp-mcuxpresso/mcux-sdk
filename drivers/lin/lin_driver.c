/*
 * Copyright  2019,2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "lin_driver.h"
#include "fsl_lin_lpuart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lin_stack"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief Table to save LPUART state structure pointers */
lin_state_t *g_linStatePtr[FSL_FEATURE_SOC_LPUART_COUNT];

/*! @brief Table to save LIN user config structure pointers */
lin_user_config_t *g_linUserconfigPtr[FSL_FEATURE_SOC_LPUART_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

static inline uint8_t BIT(const uint8_t A, uint8_t B)
{
    uint8_t tmp = A;

    tmp = (uint8_t)(((uint8_t)((uint8_t)(tmp) >> (uint8_t)(B))) & 0x01U);
    return tmp;
}

/*!
 * brief Calculates baudrate registers values for given baudrate
 *
 * param instance LPUART instance
 * param instance baudRate_Bps LPUART baudrate
 * param instance srcClock_Hz LPUART clock frequency
 * param instance osr LPUART baudrate OSR value, return value
 * param instance sbr LPUART baudrate SBR value, return value
 *
 */
void LIN_DRV_CalculateBaudrate(
    uint32_t instance, uint32_t baudRate_Bps, uint32_t srcClock_Hz, uint32_t *osr, uint16_t *sbr)
{
    /* calculates baudrate registers values for required baudrate */
    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        (void)LIN_LPUART_CalculateBaudRate(base, baudRate_Bps, srcClock_Hz, osr, sbr);
    }
}

/*!
 * brief Set baudrate registers values
 *
 * param instance LPUART instance
 * param instance osr LPUART baudrate OSR value
 * param instance sbr LPUART baudrate SBR value
 *
 */
void LIN_DRV_SetBaudrate(uint32_t instance, uint32_t osr, uint16_t sbr)
{
    /* sets baudrate registers values for LPUART instance */
    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        LIN_LPUART_SetBaudRate(base, &osr, &sbr);
    }
}

/*!
 * brief Initializes an instance LIN Hardware Interface for LIN Network.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must select the LIN Hardware Interface clock source in the application to initialize the LIN Hardware
 * Interface.
 *
 * param instance LPUART instance
 * param linUserConfig user configuration structure of type #lin_user_config_t
 * param linCurrentState pointer to the LIN Hardware Interface driver state structure
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_Init(uint32_t instance, lin_user_config_t *linUserConfig, lin_state_t *linCurrentState)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_Init(base, linUserConfig, linCurrentState, LIN_LPUART_CLOCK_FREQ);

        /* Save runtime structure pointer. */
        g_linStatePtr[instance] = linCurrentState;
        /* Save LIN user config structure pointer. */
        g_linUserconfigPtr[instance] = linUserConfig;
    }

    return retVal;
}

/*!
 * brief Shuts down the LIN Hardware Interface by disabling interrupts and transmitter/receiver.
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_Deinit(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];

        /* Call lower level function */
        retVal = LIN_LPUART_Deinit(base);

        /* Clear runtime structure pointer. */
        g_linStatePtr[instance] = (void *)NULL;
        /* Clear LIN user config structure pointer. */
        g_linUserconfigPtr[instance] = (void *)NULL;
    }

    return retVal;
}

/*!
 * brief Installs callback function that is used for LIN_DRV_IRQHandler.
 *
 * note After a callback is installed, it bypasses part of the LIN Hardware Interface IRQHandler logic.
 * Therefore, the callback needs to handle the indexes of txBuff and txSize.
 *
 * param instance LPUART instance.
 * param function the LIN receive callback function.
 * return Former LIN callback function pointer.
 */
lin_callback_t LIN_DRV_InstallCallback(uint32_t instance, lin_callback_t function)
{
    lin_callback_t currentCallback = (void *)NULL;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        lin_state_t *linCurrentState = g_linStatePtr[instance];

        /* Get the current callback function. */
        currentCallback = linCurrentState->Callback;

        /* Install new callback function. */
        linCurrentState->Callback = function;
    }

    return currentCallback;
}

/*!
 * brief Sends Frame data out through the LIN Hardware Interface using blocking method.
 *  This function will calculate the checksum byte and send it with the frame data.
 *  Blocking means that the function does not return until the transmission is complete.
 *
 * param instance LPUART instance
 * param txBuff source buffer containing 8-bit data chars to send
 * param txSize the number of bytes to send
 * param timeoutMSec timeout value in milli seconds
 * return An error code or lin_status_t LIN_BUS_BUSY if the bus is currently busy, transmission
 * cannot be started.
 */
lin_status_t LIN_DRV_SendFrameDataBlocking(uint32_t instance,
                                           const uint8_t *txBuff,
                                           uint8_t txSize,
                                           uint32_t timeoutMSec)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_SendFrameDataBlocking(base, txBuff, txSize, timeoutMSec);
    }

    return retVal;
}

/*!
 * brief Sends frame data out through the LIN Hardware Interface using non-blocking method.
 *  This enables an a-sync method for transmitting data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the transmit status to know when the transmit is complete.
 *  This function will calculate the checksum byte and send it with the frame data.
 * note If users use LIN_TimeoutService in a timer interrupt handler, then before using this function,
 * users have to set timeout counter to an appropriate value by using LIN_SetTimeoutCounter(instance, timeoutValue).
 * The timeout value should be big enough to complete the transmission. Timeout in real time is (timeoutValue) * (time
 * period that LIN_TimeoutService is called). For example, if LIN_TimeoutService is called in an timer
 * interrupt with period of 500 micro seconds, then timeout in real time is
 * timeoutValue * 500 micro seconds.
 * param instance LPUART instance
 * param txBuff  source buffer containing 8-bit data chars to send
 * param txSize  the number of bytes to send
 * return An error code or lin_status_t LIN_BUS_BUSY if the bus is currently busy, transmission
 * cannot be started. LIN_SUCCESS if the transmission was completed.
 */
lin_status_t LIN_DRV_SendFrameData(uint32_t instance, const uint8_t *txBuff, uint8_t txSize)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_SendFrameData(base, txBuff, txSize);
    }

    return retVal;
}

/*!
 * brief Get status of an on-going non-blocking transmission
 *  While sending frame data using non-blocking method, users can
 *  use this function to get status of that transmission.
 *  The bytesRemaining shows number of bytes that still needed to transmit.
 *
 * param instance LPUART instance
 * param bytesRemaining Number of bytes still needed to transmit
 * return lin_status_t LIN_TX_BUSY if the transmission is still in progress.
 * LIN_TIMEOUT if timeout occurred and transmission was not completed.
 * LIN_SUCCESS if the transmission was successful.
 */
lin_status_t LIN_DRV_GetTransmitStatus(uint32_t instance, uint8_t *bytesRemaining)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_GetTransmitStatus(base, bytesRemaining);
    }

    return retVal;
}

/*!
 * brief Receives frame data through the LIN Hardware Interface using blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it
 *  will receive the frame data. Blocking means that the function does
 *  not return until the reception is complete.
 *
 * param instance LPUART instance
 * param rxBuff  buffer containing 8-bit received data
 * param rxSize the number of bytes to receive
 * param timeoutMSec timeout value in milli seconds
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_ReceiveFrameDataBlocking(uint32_t instance, uint8_t *rxBuff, uint8_t rxSize, uint32_t timeoutMSec)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_RecvFrmDataBlocking(base, rxBuff, rxSize, timeoutMSec);
    }

    return retVal;
}

/*!
 * brief Receives frame data through the LIN Hardware Interface using non- blocking method.
 *  This function will check the checksum byte. If the checksum is correct, it
 *  will receive it with the frame data.
 *  Non-blocking  means that the function returns immediately.
 *  The application has to get the receive status to know when the reception is complete.
 * note If users use LIN_TimeoutService in a timer interrupt handler, then before using this function,
 * users have to set timeout counter to an appropriate value by using LIN_SetTimeoutCounter(instance, timeoutValue).
 * The timeout value should be big enough to complete the reception. Timeout in real time is (timeoutValue) * (time
 * period
 * that LIN_TimeoutService is called). For example, if LIN_TimeoutService is called in an timer
 * interrupt with period of 500 micro seconds, then timeout in real time is
 * timeoutValue * 500 micro seconds.
 *
 * param instance LPUART instance
 * param rxBuff  buffer containing 8-bit received data
 * param rxSize the number of bytes to receive
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_ReceiveFrameData(uint32_t instance, uint8_t *rxBuff, uint8_t rxSize)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_RecvFrmData(base, rxBuff, rxSize);
    }

    return retVal;
}

/*!
 * brief Aborts an on-going non-blocking transmission/reception.
 *  While performing a non-blocking transferring data, users can call this function
 *  to terminate immediately the transferring.
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_AbortTransferData(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_AbortTransferData(base);
    }

    return retVal;
}

/*!
 * brief Get status of an on-going non-blocking reception
 *  While receiving frame data using non-blocking method, users can
 *  use this function to get status of that receiving.
 *  This function return the current event ID, LIN_RX_BUSY while receiving
 *  and return LIN_SUCCESS, or timeout (LIN_TIMEOUT) when the reception is complete.
 *  The bytesRemaining shows number of bytes that still needed to receive.
 *
 * param instance LPUART instance
 * param bytesRemaining Number of bytes still needed to receive
 * return lin_status_t LIN_RX_BUSY, LIN_TIMEOUT or LIN_SUCCESS
 */
lin_status_t LIN_DRV_GetReceiveStatus(uint32_t instance, uint8_t *bytesRemaining)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_GetReceiveStatus(base, bytesRemaining);
    }

    return retVal;
}

/*!
 * brief Puts current LIN node to sleep mode
 * This function changes current node state to LIN_NODE_STATE_SLEEP_MODE
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_GoToSleepMode(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_GoToSleepMode(base);
    }

    return retVal;
}

/*!
 * brief Puts current LIN node to Idle state
 * This function changes current node state to LIN_NODE_STATE_IDLE
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_GotoIdleState(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_GotoIdleState(base);
    }

    return retVal;
}

/*!
 * brief Sends a wakeup signal through the LIN Hardware Interface
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_SendWakeupSignal(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_SendWakeupSignal(base);
    }

    return retVal;
}

lin_node_state_t LIN_DRV_GetCurrentNodeState(uint32_t instance)
{
    lin_node_state_t retVal = LIN_NODE_STATE_UNINIT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        const lin_state_t *linCurrentState = g_linStatePtr[instance];

        if (linCurrentState != (void *)NULL)
        {
            /* return current state of node */
            retVal = linCurrentState->currentNodeState;
        }
    }

    return retVal;
}

/*!
 * brief Callback function for Timer Interrupt Handler
 * Users may use (optional, not required) LIN_TimeoutService to check if timeout has occurred during non-blocking frame
 * data
 * transmission and reception. User may initialize a timer (for example FTM) in Output Compare Mode
 * with period of 500 micro seconds (recommended). In timer IRQ handler, call this function.
 *
 * param instance LPUART instance
 * return void
 */
void LIN_DRV_TimeoutService(uint32_t instance)
{
    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        /* Get the current LIN state of this LPUART instance. */
        lin_state_t *linCurrentState = g_linStatePtr[instance];

        /* Get LIN node's current state */
        lin_node_state_t state = linCurrentState->currentNodeState;

        switch (state)
        {
            /* If the node is SENDING DATA */
            case LIN_NODE_STATE_SEND_DATA:
                /* Check if timeout Counter is 0 */
                if (linCurrentState->timeoutCounter == 0U)
                {
                    /* Set timeout Counter flag */
                    linCurrentState->timeoutCounterFlag = true;
                    /* Callback to handle timeout Counter flag */
                    if (linCurrentState->Callback != (void *)NULL)
                    {
                        linCurrentState->Callback(instance, linCurrentState);
                    }

                    /* Check if the transmission is non-blocking */
                    if (linCurrentState->isTxBlocking == false)
                    {
                        /* Clear Bus busy flag */
                        linCurrentState->isBusBusy   = false;
                        linCurrentState->isTxBusy    = false;
                        linCurrentState->txCompleted = true;
                    }
                    /* Change the node's current state to IDLE */
                    (void)LIN_DRV_GotoIdleState(instance);
                }
                /* If timeout Counter is not 0, then decrease timeout Counter by one */
                else
                {
                    linCurrentState->timeoutCounter--;
                }
                break;
            /* If the node is RECEIVING DATA */
            case LIN_NODE_STATE_RECV_DATA:

                /* Check if timeout Counter is 0 */
                if (linCurrentState->timeoutCounter == 0U)
                {
                    /* Set timeout Counter flag */
                    linCurrentState->timeoutCounterFlag = true;

                    /* Callback to handle timeout Counter flag */
                    if (linCurrentState->Callback != (void *)NULL)
                    {
                        linCurrentState->Callback(instance, linCurrentState);
                    }

                    /* Check if the reception is non-blocking */
                    if (linCurrentState->isRxBlocking == false)
                    {
                        /* Clear Bus busy flag */
                        linCurrentState->isBusBusy   = false;
                        linCurrentState->isRxBusy    = false;
                        linCurrentState->rxCompleted = true;
                    }
                    /* Change the node's current state to IDLE */
                    (void)LIN_DRV_GotoIdleState(instance);
                }
                /* If timeout Counter is not 0, then decrease timeout Counter by one */
                else
                {
                    linCurrentState->timeoutCounter--;
                }
                break;
            default:
                /* The node state is not SENDING nor RECEIVING data */
                break;
        }
    }
}

/*!
 * brief Set Value for Timeout Counter that is used in LIN_TimeoutService
 *
 * param instance LPUART instance
 * param timeoutValue  Timeout Value to be set
 * return void
 */
void LIN_SetTimeoutCounter(uint32_t instance, uint32_t timeoutValue)
{
    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        /* Get the current LIN state of this LPUART instance. */
        lin_state_t *linCurrentState = g_linStatePtr[instance];

        /* Clear Timeout Counter Flag */
        linCurrentState->timeoutCounterFlag = false;

        /* Set new value for Timeout Counter */
        linCurrentState->timeoutCounter = timeoutValue;
    }
}

/*!
 * brief Sends frame header out through the LIN Hardware Interface using a non-blocking method.
 *  This function sends LIN Break field, sync field then the ID with
 *  correct parity.
 *
 * param instance LPUART instance
 * param id  Frame Identifier
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_MasterSendHeader(uint32_t instance, uint8_t id)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_MasterSendHeader(base, id);
    }

    return retVal;
}

/*!
 * brief Enables LIN hardware interrupts.
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_EnableIRQ(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_EnableIRQ(base);
    }

    return retVal;
}

/*!
 * @brief Disables LIN hardware interrupts.
 *
 * @param instance LPUART instance
 * @return Operation status.
 */
lin_status_t LIN_DRV_DisableIRQ(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        retVal = LIN_LPUART_DisableIRQ(base);
    }

    return retVal;
}
/*!
 * brief Interrupt handler for LIN Hardware Interface.
 *
 * param instance LPUART instance
 * return void
 */
void LIN_DRV_IRQHandler(uint8_t instance)
{
    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        LPUART_Type *base = g_linLpuartBase[instance];
        /* Call lower level function */
        LIN_LPUART_IRQHandler(base);
    }
    SDK_ISR_EXIT_BARRIER;
}

/*!
 * brief This function capture bits time to detect break char, calculate
 * baudrate from sync bits and enable transceiver if autobaud successful.
 * This function should only be used in Slave.
 * The timer should be in mode input capture of both rising and falling edges.
 * The timer input capture pin should be externally connected to RXD pin.
 *
 * param instance LPUART instance
 * return lin_status_t
 */
lin_status_t LIN_AutoBaudCapture(uint32_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    if (instance < (uint32_t)FSL_FEATURE_SOC_LPUART_COUNT)
    {
        retVal = LIN_LPUART_AutoBaudCapture(instance);
    }

    return retVal;
}

/*!
 * brief Makes the checksum byte for a frame
 *
 * param buffer Pointer to Tx buffer
 * param sizeBuffer Number of bytes that are contained in the buffer.
 * param PID Protected Identifier byte.
 * return the checksum byte.
 */
uint8_t LIN_MakeChecksumByte(const uint8_t *buffer, uint8_t sizeBuffer, uint8_t PID)
{
    uint8_t length;
    uint16_t checksum;

    assert(0U != PID);
    /* For PID is 0x3C or 0x7D apply classic checksum, and for other PID: Enhanced checksum */
    if ((0x3CU != PID) && (0x7DU != PID))
    {
        /* For PID other than 0x3c and 0x7D: Add PID in checksum calculation */
        checksum = PID;
    }
    else
    {
        /* For 0x3C and 0x7D: Do not add PID in checksum calculation */
        checksum = 0U;
    }

    for (length = sizeBuffer; 0U < length; length--)
    {
        checksum += *(buffer);
        buffer++;
        /* Deal with the carry */
        if (checksum > 0xFFU)
        {
            checksum -= 0xFFU;
        }
    }

    /* Return reversed checksum */
    return (~(uint8_t)checksum);
}

/*!
 * brief Makes or checks parity bits. If action is checking parity, the function
 * returns ID value if parity bits are correct or 0xFF if parity bits are incorrect. If action
 * is making parity bits, then from input value of ID, the function returns PID.
 * This is not a public API as it is called by other API functions.
 *
 * param PID PID byte in case of checking parity bits or ID byte in case of making parity bits.
 * param typeAction: 1 for Checking parity bits, 0 for making parity bits
 * return 0xFF if parity bits are incorrect, ID in case of checking parity bits and
 * they are correct. Function returns PID in case of making parity bits.
 */
uint8_t LIN_ProcessParity(uint8_t PID, uint8_t typeAction)
{
    uint8_t parity;
    uint8_t retVal;

    parity =
        ((uint8_t)((uint8_t)((uint8_t)((uint8_t)(BIT(PID, 0U) ^ BIT(PID, 1U)) ^ BIT(PID, 2U)) ^ BIT(PID, 4U)) << 6U) |
         (uint8_t)(
             ((uint8_t)(~(uint8_t)((uint8_t)((uint8_t)(BIT(PID, 1U) ^ BIT(PID, 3U)) ^ BIT(PID, 4U)) ^ BIT(PID, 5U))))
             << 7U));

    /* Check if action is checking parity bits */
    if (CHECK_PARITY == typeAction)
    {
        /* If parity bits are incorrect */
        if ((PID & 0xC0U) != parity)
        {
            /* Return 0xFF if parity bits are incorrect */
            retVal = 0xFFU;
        }
        /* If parity bits are correct */
        else
        {
            /* Return ID if parity bits are correct */
            retVal = (uint8_t)(PID & 0x3FU);
        }
    }
    /* If action is making parity bits */
    else
    {
        /* Return PID in case of making parity bits */
        retVal = (uint8_t)(PID | parity);
    }

    return retVal;
}

/*!
 * brief Forwards a response to a lower level
 *
 * param instance LPUART instance
 * param response_buff response message
 * param response_length length of response
 * param max_frame_res_timeout maximal timeout duration for message
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_SetResponse(uint8_t instance,
                                 uint8_t *response_buff,
                                 uint8_t response_length,
                                 uint8_t max_frame_res_timeout)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    /* Set correct timeout value */
    LIN_SetTimeoutCounter(instance, max_frame_res_timeout);
    /* Start sending data from the buffer */
    retVal = LIN_DRV_SendFrameData(instance, response_buff, response_length);

    return retVal;
}

/*!
 * brief Forwards a response to a higher level
 *
 * param instance LPUART instance
 * param response_buff response message
 * param response_length length of response
 * param max_frame_res_timeout maximal timeout duration for message
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_RxResponse(uint8_t instance,
                                uint8_t *response_buff,
                                uint8_t response_length,
                                uint8_t max_frame_res_timeout)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    /* Set correct timeout value */
    LIN_SetTimeoutCounter(instance, max_frame_res_timeout);
    /* Start receiving frame data into input buffer */
    retVal = LIN_DRV_ReceiveFrameData(instance, response_buff, response_length);

    return retVal;
}

/*!
 * brief Put a node into idle state
 *
 * param instance LPUART instance
 * return An error code or lin_status_t
 */
lin_status_t LIN_DRV_IgnoreResponse(uint8_t instance)
{
    lin_status_t retVal = LIN_IFC_NOT_SUPPORT;

    /* Abort frame data transferring */
    retVal = LIN_DRV_GotoIdleState(instance);

    return retVal;
}
