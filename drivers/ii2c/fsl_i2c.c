/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ii2c"
#endif

/*! @brief i2c transfer state. */
enum _i2c_transfer_states
{
    kIdleState             = 0x0U, /*!< I2C bus idle. */
    kCheckAddressState     = 0x1U, /*!< 7-bit address check state. */
    kSendCommandState      = 0x2U, /*!< Send command byte phase. */
    kSendDataState         = 0x3U, /*!< Send data transfer phase. */
    kReceiveDataBeginState = 0x4U, /*!< Receive data transfer phase begin. */
    kReceiveDataState      = 0x5U, /*!< Receive data transfer phase. */
};

/*! @brief Common sets of flags used by the driver. */
enum _i2c_flag_constants
{
    kClearFlags = kI2C_ArbitrationLostFlag | kI2C_IntPendingFlag,
    kIrqFlags   = kI2C_GlobalInterruptEnable,
};

/*! @brief Typedef for interrupt handler. */
typedef void (*i2c_isr_t)(I2C_Type *base, void *i2cHandle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for I2C module.
 *
 * @param base I2C peripheral base address.
 */
static uint32_t I2C_GetInstance(I2C_Type *base);

/*!
 * @brief Set up master transfer, send slave address and decide the initial
 * transfer state.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * @param xfer pointer to i2c_master_transfer_t structure.
 */
static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer);

/*!
 * @brief Check and clear status operation.
 *
 * @param base I2C peripheral base address.
 * @param status current i2c hardware status.
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 */
static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status);

/*!
 * @brief Master run transfer state machine to perform a byte of transfer.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state
 * @param isDone input param to get whether the thing is done, true is done
 * @retval kStatus_Success No error found.
 * @retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * @retval kStatus_I2C_Nak Received Nak error.
 * @retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 */
static status_t I2C_MasterTransferRunStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone);

/*!
 * @brief I2C common interrupt handler.
 *
 * @param base I2C peripheral base address.
 * @param handle pointer to i2c_master_handle_t structure which stores the transfer state
 */
static void I2C_TransferCommonIRQHandler(I2C_Type *base, void *handle);

/*!
 * @brief Wait for status ready.
 *
 * @param base I2C peripheral base address.
 * @param statusFlag statusFlag #_i2c_flags
 * @retval kStatus_I2C_Timeout Wait signal timeout.
 * @retval kStatus_Success Polling flag successfully.
 */
static status_t I2C_WaitForStatusReady(I2C_Type *base, uint8_t statusFlag);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief SCL clock divider used to calculate baudrate. */
static const uint16_t s_i2cDividerTable[] = {
    30,  32,  36,  42,  48,  52,  60,  72,  80,   88,   104,  128,  144,  160,  192,  240,
    288, 320, 384, 480, 576, 640, 768, 960, 1152, 1280, 1536, 1920, 2304, 2560, 3072, 3840,
    22,  24,  26,  28,  32,  36,  40,  44,  48,   56,   64,   72,   80,   96,   112,  128,
    160, 192, 224, 256, 320, 384, 448, 512, 640,  768,  896,  1024, 1280, 1536, 1792, 2048};

/*! @brief Pointers to i2c bases for each instance. */
static I2C_Type *const s_i2cBases[] = I2C_BASE_PTRS;

/*! @brief Pointers to i2c IRQ number for each instance. */
static const IRQn_Type s_i2cIrqs[] = I2C_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to i2c clocks for each instance. */
static const clock_ip_name_t s_i2cClocks[] = I2C_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointers to i2c handles for each instance. */
static void *s_i2cHandle[ARRAY_SIZE(s_i2cBases)];

/*! @brief Pointer to master IRQ handler for each instance. */
static i2c_isr_t s_i2cMasterIsr;

/*! @brief Pointer to slave IRQ handler for each instance. */
static i2c_isr_t s_i2cSlaveIsr;

/*******************************************************************************
 * Codes
 ******************************************************************************/

static uint32_t I2C_GetInstance(I2C_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_i2cBases); instance++)
    {
        if (s_i2cBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_i2cBases));

    return instance;
}

static status_t I2C_WaitForStatusReady(I2C_Type *base, uint8_t statusFlag)
{
#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait for TCF bit and manually trigger tx interrupt. */
    while ((0U == (base->I2SR & statusFlag)) && (0U != --waitTimes))
    {
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait for TCF bit and manually trigger tx interrupt. */
    while (0U == (base->I2SR & statusFlag))
    {
    }
#endif
    return kStatus_Success;
}

static status_t I2C_InitTransferStateMachine(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    status_t result           = kStatus_Success;
    i2c_direction_t direction = xfer->direction;

    /* Initialize the handle transfer information. */
    handle->transfer = *xfer;

    /* Save total transfer size. */
    handle->transferSize = xfer->dataSize;

    /* Initial transfer state. */
    if (handle->transfer.subaddressSize > 0U)
    {
        if (xfer->direction == kI2C_Read)
        {
            direction = kI2C_Write;
        }
    }

    handle->state = (uint8_t)kCheckAddressState;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

    /* Handle no start option. */
    if ((handle->transfer.flags & (uint32_t)kI2C_TransferNoStartFlag) != 0U)
    {
        /* No need to send start flag, directly go to send command or data */
        if (handle->transfer.subaddressSize > 0U)
        {
            handle->state = (uint8_t)kSendCommandState;
        }
        else
        {
            if (direction == kI2C_Write)
            {
                /* Next state, send data. */
                handle->state = (uint8_t)kSendDataState;
            }
            else
            {
                /* Only support write with no stop signal. */
                return kStatus_InvalidArgument;
            }
        }

        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_TransferCompleteFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }
        I2C_MasterTransferHandleIRQ(base, handle);
    }
    /* If repeated start is requested, send repeated start. */
    else if ((handle->transfer.flags & (uint32_t)kI2C_TransferRepeatedStartFlag) != 0U)
    {
        result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I2C_MasterStart(base, handle->transfer.slaveAddress, direction);
    }

    return result;
}

static status_t I2C_CheckAndClearError(I2C_Type *base, uint32_t status)
{
    status_t result = kStatus_Success;

    /* Check arbitration lost. */
    if ((status & (uint32_t)kI2C_ArbitrationLostFlag) != 0U)
    {
        /* Clear arbitration lost flag. */
        base->I2SR &= (~(uint8_t)kI2C_ArbitrationLostFlag);

        /* Reset I2C controller*/
        base->I2CR &= ~(uint16_t)I2C_I2CR_IEN_MASK;
        base->I2CR |= I2C_I2CR_IEN_MASK;

        result = kStatus_I2C_ArbitrationLost;
    }
    /* Check NAK */
    else if ((status & (uint32_t)kI2C_ReceiveNakFlag) != 0U)
    {
        result = kStatus_I2C_Nak;
    }
    else
    {
        /* Avoid MISRA 2012 rule 15.7 violation */
    }

    return result;
}

static status_t I2C_MasterTransferRunStateMachine(I2C_Type *base, i2c_master_handle_t *handle, bool *isDone)
{
    status_t result        = kStatus_Success;
    uint32_t statusFlags   = base->I2SR;
    *isDone                = false;
    volatile uint8_t dummy = 0U;
    bool ignoreNak         = ((handle->state == (uint8_t)kSendDataState) && (handle->transfer.dataSize == 0U)) ||
                     ((handle->state == (uint8_t)kReceiveDataState) && (handle->transfer.dataSize == 1U));

    /* Add this to avoid build warning. */
    dummy++;

    /* Check & clear error flags. */
    result = I2C_CheckAndClearError(base, statusFlags);

    /* Ignore Nak when it's appeared for last byte. */
    if ((result == kStatus_I2C_Nak) && ignoreNak)
    {
        result = kStatus_Success;
    }

    /* Handle Check address state to check the slave address is Acked in slave
       probe application. */
    if (handle->state == (uint8_t)kCheckAddressState)
    {
        if ((statusFlags & (uint32_t)kI2C_ReceiveNakFlag) != 0U)
        {
            result = kStatus_I2C_Addr_Nak;
        }
        else
        {
            if (handle->transfer.subaddressSize > 0U)
            {
                handle->state = (uint8_t)kSendCommandState;
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Next state, send data. */
                    handle->state = (uint8_t)kSendDataState;
                }
                else
                {
                    /* Next state, receive data begin. */
                    handle->state = (uint8_t)kReceiveDataBeginState;
                }
            }
        }
    }

    if (result != kStatus_Success)
    {
        return result;
    }

    /* Run state machine. */
    switch (handle->state)
    {
        /* Send I2C command. */
        case (uint8_t)kSendCommandState:
            if (handle->transfer.subaddressSize != 0U)
            {
                handle->transfer.subaddressSize--;
                base->I2DR = (uint16_t)((handle->transfer.subaddress) >> (8U * handle->transfer.subaddressSize));
            }
            else
            {
                if (handle->transfer.direction == kI2C_Write)
                {
                    /* Send first byte of data. */
                    if (handle->transfer.dataSize > 0U)
                    {
                        /* Next state, send data. */
                        handle->state = (uint8_t)kSendDataState;
                        base->I2DR    = *handle->transfer.data;
                        handle->transfer.data++;
                        handle->transfer.dataSize--;
                    }
                    else
                    {
                        *isDone = true;
                    }
                }
                else
                {
                    /* Send repeated start and slave address. */
                    result = I2C_MasterRepeatedStart(base, handle->transfer.slaveAddress, kI2C_Read);

                    /* Next state, receive data begin. */
                    handle->state = (uint8_t)kReceiveDataBeginState;
                }
            }
            break;

        /* Send I2C data. */
        case (uint8_t)kSendDataState:
            /* Send one byte of data. */
            if (handle->transfer.dataSize > 0U)
            {
                base->I2DR = *handle->transfer.data;
                handle->transfer.data++;
                handle->transfer.dataSize--;
            }
            else
            {
                *isDone = true;
            }
            break;

        /* Start I2C data receive. */
        case (uint8_t)kReceiveDataBeginState:
            base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

            /* Send nak at the last receive byte. */
            if (handle->transfer.dataSize == 1U)
            {
                base->I2CR |= I2C_I2CR_TXAK_MASK;
            }

            /* Read dummy to release the bus. */
            dummy = (uint8_t)base->I2DR;

            /* Next state, receive data. */
            handle->state = (uint8_t)kReceiveDataState;
            break;

        /* Receive I2C data. */
        case (uint8_t)kReceiveDataState:
            /* Receive one byte of data. */
            if (0U != handle->transfer.dataSize--)
            {
                if (handle->transfer.dataSize == 0U)
                {
                    *isDone = true;

                    /* Send stop if kI2C_TransferNoStop is not asserted. */
                    if (0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag))
                    {
                        result = I2C_MasterStop(base);
                    }
                    else
                    {
                        base->I2CR |= I2C_I2CR_MTX_MASK;
                    }
                }

                /* Send NAK at the last receive byte. */
                if (handle->transfer.dataSize == 1U)
                {
                    base->I2CR |= I2C_I2CR_TXAK_MASK;
                }

                /* Read the data byte into the transfer buffer. */
                *handle->transfer.data = (uint8_t)base->I2DR;
                handle->transfer.data++;
            }
            break;

        default:
            assert(false);
            break;
    }

    return result;
}

static void I2C_TransferCommonIRQHandler(I2C_Type *base, void *handle)
{
    /* Check if master interrupt. */
    if (((base->I2SR & (uint8_t)kI2C_ArbitrationLostFlag) != 0U) || ((base->I2CR & (uint8_t)I2C_I2CR_MSTA_MASK) != 0U))
    {
        s_i2cMasterIsr(base, handle);
    }
    else
    {
        s_i2cSlaveIsr(base, handle);
    }
    __DSB();
}

/*!
 * brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and configure the I2C with master configuration.
 *
 * note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can be custom filled
 * or it can be set with default values by using the I2C_MasterGetDefaultConfig().
 * After calling this API, the master is ready to transfer.
 * This is an example.
 * code
 * i2c_master_config_t config = {
 * .enableMaster = true,
 * .baudRate_Bps = 100000
 * };
 * I2C_MasterInit(I2C0, &config, 12000000U);
 * endcode
 *
 * param base I2C base pointer
 * param masterConfig A pointer to the master configuration structure
 * param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_MasterInit(I2C_Type *base, const i2c_master_config_t *masterConfig, uint32_t srcClock_Hz)
{
    assert((masterConfig != NULL) && (srcClock_Hz != 0U));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable I2C clock. */
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module. */
    base->IADR = 0;
    base->IFDR = 0;
    base->I2CR = 0;
    base->I2SR = 0;

    /* Disable I2C prior to configuring it. */
    base->I2CR &= ~((uint16_t)I2C_I2CR_IEN_MASK);

    /* Clear all flags. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

    /* Configure baud rate. */
    I2C_MasterSetBaudRate(base, masterConfig->baudRate_Bps, srcClock_Hz);

    /* Enable the I2C peripheral based on the configuration. */
    base->I2CR = I2C_I2CR_IEN(masterConfig->enableMaster);
}

/*!
 * brief De-initializes the I2C master peripheral. Call this API to gate the I2C clock.
 * The I2C master module can't work unless the I2C_MasterInit is called.
 * param base I2C base pointer
 */
void I2C_MasterDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Sets the I2C master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_MasterInit().
 * Use the initialized structure unchanged in the I2C_MasterInit() or modify
 * the structure before calling the I2C_MasterInit().
 * This is an example.
 * code
 * i2c_master_config_t config;
 * I2C_MasterGetDefaultConfig(&config);
 * endcode
 * param masterConfig A pointer to the master configuration structure.
 */
void I2C_MasterGetDefaultConfig(i2c_master_config_t *masterConfig)
{
    assert(masterConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(masterConfig, 0, sizeof(*masterConfig));

    /* Default baud rate at 100kbps. */
    masterConfig->baudRate_Bps = 100000U;

    /* Enable the I2C peripheral. */
    masterConfig->enableMaster = true;
}

/*!
 * brief Enables I2C interrupt requests.
 *
 * param base I2C base pointer
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kI2C_GlobalInterruptEnable
 *     arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_EnableInterrupts(I2C_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kI2C_GlobalInterruptEnable) != 0U)
    {
        base->I2CR |= I2C_I2CR_IIEN_MASK;
    }
}

/*!
 * brief Disables I2C interrupt requests.
 *
 * param base I2C base pointer
 * param mask interrupt source
 *     The parameter can be combination of the following source if defined:
 *     arg kI2C_GlobalInterruptEnable
 *     arg kI2C_StopDetectInterruptEnable/kI2C_StartDetectInterruptEnable
 *     arg kI2C_SdaTimeoutInterruptEnable
 */
void I2C_DisableInterrupts(I2C_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kI2C_GlobalInterruptEnable) != 0U)
    {
        base->I2CR &= ~(uint16_t)I2C_I2CR_IIEN_MASK;
    }
}

/*!
 * brief Sets the I2C master transfer baud rate.
 *
 * param base I2C base pointer
 * param baudRate_Bps the baud rate value in bps
 * param srcClock_Hz Source clock
 */
void I2C_MasterSetBaudRate(I2C_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t computedRate;
    uint32_t absError;
    uint32_t bestError = UINT32_MAX;
    uint32_t bestIcr   = 0u;
    uint8_t i;

    /* Scan table to find best match. */
    for (i = 0u; i < sizeof(s_i2cDividerTable) / sizeof(s_i2cDividerTable[0]); ++i)
    {
        computedRate = srcClock_Hz / s_i2cDividerTable[i];
        absError     = baudRate_Bps > computedRate ? (baudRate_Bps - computedRate) : (computedRate - baudRate_Bps);

        if (absError < bestError)
        {
            bestIcr   = i;
            bestError = absError;

            /* If the error is 0, then we can stop searching because we won't find a better match. */
            if (absError == 0U)
            {
                break;
            }
        }
    }

    /* Set frequency register based on best settings. */
    base->IFDR = I2C_IFDR_IC(bestIcr);
}

/*!
 * brief Sends a START on the I2C bus.
 *
 * This function is used to initiate a new master mode transfer by sending the START signal.
 * The slave address is sent following the I2C START signal.
 *
 * param base I2C peripheral base pointer
 * param address 7-bit slave device address.
 * param direction Master transfer directions(transmit/receive).
 * retval kStatus_Success Successfully send the start signal.
 * retval kStatus_I2C_Busy Current bus is busy.
 */
status_t I2C_MasterStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result      = kStatus_Success;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);

    /* Return an error if the bus is already in use. */
    if ((statusFlags & (uint32_t)kI2C_BusBusyFlag) != 0U)
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* Send the START signal. */
        base->I2CR |= I2C_I2CR_MSTA_MASK | I2C_I2CR_MTX_MASK;

        base->I2DR = (uint16_t)(((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

/*!
 * brief Sends a REPEATED START on the I2C bus.
 *
 * param base I2C peripheral base pointer
 * param address 7-bit slave device address.
 * param direction Master transfer directions(transmit/receive).
 * retval kStatus_Success Successfully send the start signal.
 * retval kStatus_I2C_Busy Current bus is busy but not occupied by current I2C master.
 */
status_t I2C_MasterRepeatedStart(I2C_Type *base, uint8_t address, i2c_direction_t direction)
{
    status_t result      = kStatus_Success;
    uint32_t statusFlags = I2C_MasterGetStatusFlags(base);

    /* Return an error if the bus is already in use, but not by us. */
    if (((statusFlags & (uint32_t)kI2C_BusBusyFlag) != 0U) && ((base->I2CR & (uint16_t)I2C_I2CR_MSTA_MASK) == 0U))
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* We are already in a transfer, so send a repeated start. */
        base->I2CR |= I2C_I2CR_RSTA_MASK | I2C_I2CR_MTX_MASK;

        base->I2DR = (uint16_t)(((uint32_t)address) << 1U | ((direction == kI2C_Read) ? 1U : 0U));
    }

    return result;
}

/*!
 * brief Sends a STOP signal on the I2C bus.
 *
 * retval kStatus_Success Successfully send the stop signal.
 * retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterStop(I2C_Type *base)
{
    /* Issue the STOP command on the bus. */
    base->I2CR &= ~((uint16_t)I2C_I2CR_MSTA_MASK | (uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

#if I2C_RETRY_TIMES
    uint32_t waitTimes = I2C_RETRY_TIMES;
    /* Wait for IBB bit is cleared. */
    while ((0U != (base->I2SR & (uint8_t)kI2C_BusBusyFlag)) && (0U != --waitTimes))
    {
    }
    if (0U == waitTimes)
    {
        return kStatus_I2C_Timeout;
    }
#else
    /* Wait for IBB bit is cleared. */
    while (0U != (base->I2SR & (uint8_t)kI2C_BusBusyFlag))
    {
    }
#endif
    return kStatus_Success;
}

/*!
 * brief Performs a polling send transaction on the I2C bus.
 *
 * param base  The I2C peripheral base pointer.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize, uint32_t flags)
{
    status_t result     = kStatus_Success;
    uint8_t statusFlags = 0;

    if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_TransferCompleteFlag) != kStatus_Success)
    {
        return kStatus_I2C_Timeout;
    }

    /* Clear the IICIF flag. */
    base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to transmit data. */
    base->I2CR |= I2C_I2CR_MTX_MASK;

    while (0U != txSize--)
    {
        /* Send a byte of data. */
        base->I2DR = *txBuff++;

        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }

        statusFlags = (uint8_t)base->I2SR;

        /* Clear the IICIF flag. */
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

        /* Check if arbitration lost or no acknowledgement (NAK), return failure status. */
        if ((statusFlags & (uint8_t)kI2C_ArbitrationLostFlag) != 0U)
        {
            base->I2SR = (uint16_t)kI2C_ArbitrationLostFlag;
            result     = kStatus_I2C_ArbitrationLost;
        }

        if (((statusFlags & (uint8_t)kI2C_ReceiveNakFlag) != 0U) && (txSize != 0U))
        {
            base->I2SR = (uint16_t)kI2C_ReceiveNakFlag;
            result     = kStatus_I2C_Nak;
        }

        if (result != kStatus_Success)
        {
            /* Breaking out of the send loop. */
            break;
        }
    }

    if (((result == kStatus_Success) && (0U == (flags & (uint32_t)kI2C_TransferNoStopFlag))) ||
        (result == kStatus_I2C_Nak))
    {
        /* Clear the IICIF flag. */
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

        /* Send stop. */
        result = I2C_MasterStop(base);
    }

    return result;
}

/*!
 * brief Performs a polling receive transaction on the I2C bus.
 *
 * note The I2C_MasterReadBlocking function stops the bus before reading the final byte.
 * Without stopping the bus prior for the final read, the bus issues another read, resulting
 * in garbage data being read into the data register.
 *
 * param base I2C peripheral base pointer.
 * param rxBuff The pointer to the data to store the received data.
 * param rxSize The length in bytes of the data to be received.
 * param flags Transfer control flag to decide whether need to send a stop, use kI2C_TransferDefaultFlag
 *  to issue a stop and kI2C_TransferNoStop to not send a stop.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_Timeout Send stop signal failed, timeout.
 */
status_t I2C_MasterReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize, uint32_t flags)
{
    status_t result        = kStatus_Success;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_TransferCompleteFlag) != kStatus_Success)
    {
        return kStatus_I2C_Timeout;
    }

    /* Clear the IICIF flag. */
    base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to receive data. */
    base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

    /* If rxSize equals 1, configure to send NAK. */
    if (rxSize == 1U)
    {
        /* Issue NACK on read. */
        base->I2CR |= I2C_I2CR_TXAK_MASK;
    }

    /* Do dummy read. */
    dummy = (uint8_t)base->I2DR;

    while (0U != (rxSize--))
    {
        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }

        /* Clear the IICIF flag. */
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

        /* Single byte use case. */
        if (rxSize == 0U)
        {
            if (0U == (flags & (uint32_t)kI2C_TransferNoStopFlag))
            {
                /* Issue STOP command before reading last byte. */
                result = I2C_MasterStop(base);
            }
            else
            {
                /* Change direction to Tx to avoid extra clocks. */
                base->I2CR |= I2C_I2CR_MTX_MASK;
            }
        }

        if (rxSize == 1U)
        {
            /* Issue NACK on read. */
            base->I2CR |= I2C_I2CR_TXAK_MASK;
        }

        /* Read from the data register. */
        *rxBuff++ = (uint8_t)base->I2DR;
    }

    return result;
}

/*!
 * brief Performs a master polling transfer on the I2C bus.
 *
 * note The API does not return until the transfer succeeds or fails due
 * to arbitration lost or receiving a NAK.
 *
 * param base I2C peripheral base address.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_Busy Previous transmission still not finished.
 * retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_MasterTransferBlocking(I2C_Type *base, i2c_master_transfer_t *xfer)
{
    assert(xfer);

    i2c_direction_t direction = xfer->direction;
    status_t result           = kStatus_Success;

    /* Clear all status before transfer. */
    I2C_MasterClearStatusFlags(base, (uint32_t)kClearFlags);

    if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_TransferCompleteFlag) != kStatus_Success)
    {
        return kStatus_I2C_Timeout;
    }

    /* Change to send write address when it's a read operation with command. */
    if ((xfer->subaddressSize > 0U) && (xfer->direction == kI2C_Read))
    {
        direction = kI2C_Write;
    }

    /* Handle no start option, only support write with no start signal. */
    if ((xfer->flags & (uint32_t)kI2C_TransferNoStartFlag) != 0U)
    {
        if (direction == kI2C_Read)
        {
            return kStatus_InvalidArgument;
        }
    }
    /* If repeated start is requested, send repeated start. */
    else if ((xfer->flags & (uint32_t)kI2C_TransferRepeatedStartFlag) != 0U)
    {
        result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, direction);
    }
    else /* For normal transfer, send start. */
    {
        result = I2C_MasterStart(base, xfer->slaveAddress, direction);
    }

    if (0U == (xfer->flags & (uint32_t)kI2C_TransferNoStartFlag))
    {
        /* Return if error. */
        if (result != kStatus_Success)
        {
            return result;
        }

        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }

        /* Check if there's transfer error. */
        result = I2C_CheckAndClearError(base, base->I2SR);

        /* Return if error. */
        if (result != kStatus_Success)
        {
            if (result == kStatus_I2C_Nak)
            {
                result = kStatus_I2C_Addr_Nak;

                (void)I2C_MasterStop(base);
            }

            return result;
        }
    }

    /* Send subaddress. */
    if (xfer->subaddressSize != 0U)
    {
        do
        {
            /* Clear interrupt pending flag. */
            base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

            xfer->subaddressSize--;
            base->I2DR = (uint16_t)((xfer->subaddress) >> (8U * xfer->subaddressSize));

            if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
            {
                return kStatus_I2C_Timeout;
            }

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->I2SR);

            if (result != kStatus_Success)
            {
                if (result == kStatus_I2C_Nak)
                {
                    (void)I2C_MasterStop(base);
                }

                return result;
            }

        } while (xfer->subaddressSize > 0U);

        if (xfer->direction == kI2C_Read)
        {
            /* Clear pending flag. */
            base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

            /* Send repeated start and slave address. */
            result = I2C_MasterRepeatedStart(base, xfer->slaveAddress, kI2C_Read);

            /* Return if error. */
            if (result != kStatus_Success)
            {
                return result;
            }

            if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
            {
                return kStatus_I2C_Timeout;
            }

            /* Check if there's transfer error. */
            result = I2C_CheckAndClearError(base, base->I2SR);

            if (result != kStatus_Success)
            {
                if (result == kStatus_I2C_Nak)
                {
                    result = kStatus_I2C_Addr_Nak;

                    (void)I2C_MasterStop(base);
                }

                return result;
            }
        }
    }

    /* Transmit data. */
    if (xfer->direction == kI2C_Write)
    {
        if (xfer->dataSize > 0U)
        {
            /* Send Data. */
            result = I2C_MasterWriteBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
        }
        else if (0U == (xfer->flags & (uint32_t)kI2C_TransferNoStopFlag))
        {
            /* Send stop. */
            result = I2C_MasterStop(base);
        }
        else
        {
            /* Avoid MISRA 2012 rule 15.7 violation */
        }
    }
    /* Receive Data. */
    if ((xfer->direction == kI2C_Read) && (xfer->dataSize > 0U))
    {
        result = I2C_MasterReadBlocking(base, xfer->data, xfer->dataSize, xfer->flags);
    }

    return result;
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure to store the transfer state.
 * param callback pointer to user callback function.
 * param userData user parameter passed to the callback function.
 */
void I2C_MasterTransferCreateHandle(I2C_Type *base,
                                    i2c_master_handle_t *handle,
                                    i2c_master_transfer_callback_t callback,
                                    void *userData)
{
    assert(handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save master interrupt handler. */
    s_i2cMasterIsr = I2C_MasterTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_i2cIrqs[instance]);
}

/*!
 * brief Performs a master interrupt non-blocking transfer on the I2C bus.
 *
 * note Calling the API returns immediately after transfer initiates. The user needs
 * to call I2C_MasterGetTransferCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_I2C_Busy, the transfer
 * is finished.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * param xfer pointer to i2c_master_transfer_t structure.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_I2C_Busy Previous transmission still not finished.
 * retval kStatus_I2C_Timeout Transfer error, wait signal timeout.
 */
status_t I2C_MasterTransferNonBlocking(I2C_Type *base, i2c_master_handle_t *handle, i2c_master_transfer_t *xfer)
{
    assert(handle);
    assert(xfer);

    status_t result = kStatus_Success;

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != (uint8_t)kIdleState)
    {
        result = kStatus_I2C_Busy;
    }
    else
    {
        /* Start up the master transfer state machine. */
        result = I2C_InitTransferStateMachine(base, handle, xfer);

        if (result == kStatus_Success)
        {
            /* Enable the I2C interrupts. */
            I2C_EnableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);
        }
    }

    return result;
}

/*!
 * brief Aborts an interrupt non-blocking transfer early.
 *
 * note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state
 * retval kStatus_I2C_Timeout Timeout during polling flag.
 * retval kStatus_Success Successfully abort the transfer.
 */
status_t I2C_MasterTransferAbort(I2C_Type *base, i2c_master_handle_t *handle)
{
    assert(handle);

    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    /* Disable interrupt. */
    I2C_DisableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);

    /* Reset the state to idle. */
    handle->state = (uint8_t)kIdleState;

    /* Send STOP signal. */
    if (handle->transfer.direction == kI2C_Read)
    {
        base->I2CR |= I2C_I2CR_TXAK_MASK;

        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

        base->I2CR &= ~((uint16_t)I2C_I2CR_MSTA_MASK | (uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);
        dummy = (uint8_t)base->I2DR;
    }
    else
    {
        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;
        base->I2CR &= ~((uint16_t)I2C_I2CR_MSTA_MASK | (uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);
    }
    return kStatus_Success;
}

/*!
 * brief Gets the master transfer status during a interrupt non-blocking transfer.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_master_handle_t structure which stores the transfer state.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t I2C_MasterTransferGetCount(I2C_Type *base, i2c_master_handle_t *handle, size_t *count)
{
    assert(handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->transferSize - handle->transfer.dataSize;

    return kStatus_Success;
}

/*!
 * brief Master interrupt handler.
 *
 * param base I2C base pointer.
 * param i2cHandle pointer to i2c_master_handle_t structure.
 */
void I2C_MasterTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(i2cHandle);

    i2c_master_handle_t *handle = (i2c_master_handle_t *)i2cHandle;
    status_t result             = kStatus_Success;
    bool isDone;

    /* Clear the interrupt flag. */
    base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

    /* Check transfer complete flag. */
    result = I2C_MasterTransferRunStateMachine(base, handle, &isDone);

    if (isDone || (result != kStatus_Success))
    {
        /* Send stop command if transfer done or received Nak. */
        if ((0U == (handle->transfer.flags & (uint32_t)kI2C_TransferNoStopFlag)) || (result == kStatus_I2C_Nak) ||
            (result == kStatus_I2C_Addr_Nak))
        {
            /* Ensure stop command is a need. */
            if ((base->I2CR & I2C_I2CR_MSTA_MASK) != 0U)
            {
                if (I2C_MasterStop(base) != kStatus_Success)
                {
                    result = kStatus_I2C_Timeout;
                }
            }
        }

        /* Restore handle to idle state. */
        handle->state = (uint8_t)kIdleState;

        /* Disable interrupt. */
        I2C_DisableInterrupts(base, (uint32_t)kI2C_GlobalInterruptEnable);

        /* Call the callback function after the function has completed. */
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}

/*!
 * brief Initializes the I2C peripheral. Call this API to ungate the I2C clock
 * and initialize the I2C with the slave configuration.
 *
 * note This API should be called at the beginning of the application.
 * Otherwise, any operation to the I2C module can cause a hard fault
 * because the clock is not enabled. The configuration structure can partly be set
 * with default values by I2C_SlaveGetDefaultConfig() or it can be custom filled by the user.
 * This is an example.
 * code
 * i2c_slave_config_t config = {
 * .enableSlave = true,
 * .slaveAddress = 0x1DU,
 * };
 * I2C_SlaveInit(I2C0, &config);
 * endcode
 *
 * param base I2C base pointer
 * param slaveConfig A pointer to the slave configuration structure
 * param srcClock_Hz I2C peripheral clock frequency in Hz
 */
void I2C_SlaveInit(I2C_Type *base, const i2c_slave_config_t *slaveConfig)
{
    assert(slaveConfig != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable I2C clock. */
    CLOCK_EnableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module. */
    base->IADR = 0;
    base->IFDR = 0;
    base->I2CR = 0;
    base->I2SR = 0;

    base->IADR = (uint16_t)((uint32_t)(slaveConfig->slaveAddress)) << 1U;
    base->I2CR = I2C_I2CR_IEN(slaveConfig->enableSlave);
}

/*!
 * brief De-initializes the I2C slave peripheral. Calling this API gates the I2C clock.
 * The I2C slave module can't work unless the I2C_SlaveInit is called to enable the clock.
 * param base I2C base pointer
 */
void I2C_SlaveDeinit(I2C_Type *base)
{
    /* Disable I2C module. */
    I2C_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable I2C clock. */
    CLOCK_DisableClock(s_i2cClocks[I2C_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief  Sets the I2C slave configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in the I2C_SlaveInit().
 * Modify fields of the structure before calling the I2C_SlaveInit().
 * This is an example.
 * code
 * i2c_slave_config_t config;
 * I2C_SlaveGetDefaultConfig(&config);
 * endcode
 * param slaveConfig A pointer to the slave configuration structure.
 */
void I2C_SlaveGetDefaultConfig(i2c_slave_config_t *slaveConfig)
{
    assert(slaveConfig);

    /* Initializes the configure structure to zero. */
    (void)memset(slaveConfig, 0, sizeof(*slaveConfig));

    /* Enable the I2C peripheral. */
    slaveConfig->enableSlave = true;
}

/*!
 * brief Performs a polling send transaction on the I2C bus.
 *
 * param base  The I2C peripheral base pointer.
 * param txBuff The pointer to the data to be transferred.
 * param txSize The length in bytes of the data to be transferred.
 * retval kStatus_Success Successfully complete the data transmission.
 * retval kStatus_I2C_ArbitrationLost Transfer error, arbitration lost.
 * retval kStataus_I2C_Nak Transfer error, receive NAK during transfer.
 */
status_t I2C_SlaveWriteBlocking(I2C_Type *base, const uint8_t *txBuff, size_t txSize)
{
    status_t result        = kStatus_Success;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_AddressMatchFlag) != kStatus_Success)
    {
        return kStatus_I2C_Timeout;
    }

    /* Read dummy to release bus. */
    dummy = (uint8_t)base->I2DR;

    result = I2C_MasterWriteBlocking(base, txBuff, txSize, (uint32_t)kI2C_TransferDefaultFlag);

    /* Switch to receive mode. */
    base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

    /* Read dummy to release bus. */
    dummy = (uint8_t)base->I2DR;

    return result;
}

/*!
 * brief Performs a polling receive transaction on the I2C bus.
 *
 * param base I2C peripheral base pointer.
 * param rxBuff The pointer to the data to store the received data.
 * param rxSize The length in bytes of the data to be received.
 */
status_t I2C_SlaveReadBlocking(I2C_Type *base, uint8_t *rxBuff, size_t rxSize)
{
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_AddressMatchFlag) != kStatus_Success)
    {
        return kStatus_I2C_Timeout;
    }

    /* Read dummy to release bus. */
    dummy = (uint8_t)base->I2DR;

    /* Clear the IICIF flag. */
    base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

    /* Setup the I2C peripheral to receive data. */
    base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK);

    while (0U != rxSize--)
    {
        if (I2C_WaitForStatusReady(base, (uint8_t)kI2C_IntPendingFlag) != kStatus_Success)
        {
            return kStatus_I2C_Timeout;
        }
        /* Clear the IICIF flag. */
        base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

        /* Read from the data register. */
        *rxBuff++ = (uint8_t)base->I2DR;
    }
    return kStatus_Success;
}

/*!
 * brief Initializes the I2C handle which is used in transactional functions.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure to store the transfer state.
 * param callback pointer to user callback function.
 * param userData user parameter passed to the callback function.
 */
void I2C_SlaveTransferCreateHandle(I2C_Type *base,
                                   i2c_slave_handle_t *handle,
                                   i2c_slave_transfer_callback_t callback,
                                   void *userData)
{
    assert(handle);

    uint32_t instance = I2C_GetInstance(base);

    /* Zero handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set callback and userData. */
    handle->callback = callback;
    handle->userData = userData;

    /* Save the context in global variables to support the double weak mechanism. */
    s_i2cHandle[instance] = handle;

    /* Save slave interrupt handler. */
    s_i2cSlaveIsr = I2C_SlaveTransferHandleIRQ;

    /* Enable NVIC interrupt. */
    (void)EnableIRQ(s_i2cIrqs[instance]);
}

/*!
 * brief Starts accepting slave transfers.
 *
 * Call this API after calling the I2C_SlaveInit() and I2C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and passes events to the
 * callback that was passed into the call to I2C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the a eventMask parameter to
 * the OR'd combination of #i2c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI2C_SlaveTransmitEvent and #kLPI2C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI2C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * param base The I2C peripheral base address.
 * param handle Pointer to #i2c_slave_handle_t structure which stores the transfer state.
 * param eventMask Bit mask formed by OR'ing together #i2c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI2C_SlaveAllEvents to enable all events.
 *
 * retval #kStatus_Success Slave transfers were successfully started.
 * retval #kStatus_I2C_Busy Slave transfers have already been started on this handle.
 */
status_t I2C_SlaveTransferNonBlocking(I2C_Type *base, i2c_slave_handle_t *handle, uint32_t eventMask)
{
    assert(handle != NULL);

    /* Check if the I2C bus is idle - if not return busy status. */
    if (handle->state != (uint8_t)kIdleState)
    {
        return kStatus_I2C_Busy;
    }
    else
    {
        /* Disable LPI2C IRQ sources while we configure stuff. */
        (void)I2C_DisableInterrupts(base, (uint32_t)kIrqFlags);

        /* Clear transfer in handle. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Record that we're busy. */
        handle->state = (uint8_t)kCheckAddressState;

        /* Set up event mask. tx and rx are always enabled. */
        handle->eventMask = eventMask | (uint32_t)kI2C_SlaveTransmitEvent | (uint32_t)kI2C_SlaveReceiveEvent;

        /* Clear all flags. */
        I2C_SlaveClearStatusFlags(base, (uint32_t)kClearFlags);

        /* Enable I2C internal IRQ sources. NVIC IRQ was enabled in CreateHandle() */
        I2C_EnableInterrupts(base, (uint32_t)kIrqFlags);
    }

    return kStatus_Success;
}

/*!
 * brief Aborts the slave transfer.
 *
 * note This API can be called at any time to stop slave for handling the bus events.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure which stores the transfer state.
 */
void I2C_SlaveTransferAbort(I2C_Type *base, i2c_slave_handle_t *handle)
{
    assert(handle);

    if (handle->state != (uint8_t)kIdleState)
    {
        /* Disable interrupts. */
        I2C_DisableInterrupts(base, (uint32_t)kIrqFlags);

        /* Reset transfer info. */
        (void)memset(&handle->transfer, 0, sizeof(handle->transfer));

        /* Reset the state to idle. */
        handle->state = (uint8_t)kIdleState;
    }
}

/*!
 * brief Gets the slave transfer remaining bytes during a interrupt non-blocking transfer.
 *
 * param base I2C base pointer.
 * param handle pointer to i2c_slave_handle_t structure.
 * param count Number of bytes transferred so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */
status_t I2C_SlaveTransferGetCount(I2C_Type *base, i2c_slave_handle_t *handle, size_t *count)
{
    assert(handle);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (handle->state == (uint8_t)kIdleState)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    /* For an active transfer, just return the count from the handle. */
    *count = handle->transfer.transferredCount;

    return kStatus_Success;
}

/*!
 * brief Slave interrupt handler.
 *
 * param base I2C base pointer.
 * param i2cHandle pointer to i2c_slave_handle_t structure which stores the transfer state
 */
void I2C_SlaveTransferHandleIRQ(I2C_Type *base, void *i2cHandle)
{
    assert(i2cHandle);

    uint32_t status;
    bool doTransmit            = false;
    i2c_slave_handle_t *handle = (i2c_slave_handle_t *)i2cHandle;
    i2c_slave_transfer_t *xfer;
    volatile uint8_t dummy = 0;

    /* Add this to avoid build warning. */
    dummy++;

    status = I2C_SlaveGetStatusFlags(base);
    xfer   = &(handle->transfer);

    /* Clear the interrupt flag. */
    base->I2SR &= ~(uint16_t)kI2C_IntPendingFlag;

    /* Check NAK */
    if ((status & (uint32_t)kI2C_ReceiveNakFlag) != 0U)
    {
        /* Set receive mode. */
        base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

        /* Read dummy. */
        dummy = (uint8_t)base->I2DR;

        if (handle->transfer.dataSize != 0U)
        {
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_I2C_Nak;
            handle->state          = (uint8_t)kIdleState;

            if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
        else
        {
            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->state          = (uint8_t)kIdleState;

            if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
    }
    /* Check address match. */
    else if ((status & (uint32_t)kI2C_AddressMatchFlag) != 0U)
    {
        xfer->event = kI2C_SlaveAddressMatchEvent;

        /* Slave transmit, master reading from slave. */
        if ((status & (uint32_t)kI2C_TransferDirectionFlag) != 0U)
        {
            handle->state = (uint8_t)kSendDataState;
            /* Change direction to send data. */
            base->I2CR |= I2C_I2CR_MTX_MASK;

            doTransmit = true;
        }
        else
        {
            handle->state = (uint8_t)kReceiveDataState;
            /* Slave receive, master writing to slave. */
            base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

            /* Read dummy to release the bus. */
            dummy = (uint8_t)base->I2DR;
        }

        if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
        {
            handle->callback(base, xfer, handle->userData);
        }
    }
    /* Check transfer complete flag. */
    else if ((status & (uint32_t)kI2C_TransferCompleteFlag) != 0U)
    {
        /* Slave transmit, master reading from slave. */
        if (handle->state == (uint8_t)kSendDataState)
        {
            doTransmit = true;
        }
        else
        {
            /* If we're out of data, invoke callback to get more. */
            if ((NULL == xfer->data) || (0U == xfer->dataSize))
            {
                xfer->event = kI2C_SlaveReceiveEvent;

                if (handle->callback != NULL)
                {
                    handle->callback(base, xfer, handle->userData);
                }

                /* Clear the transferred count now that we have a new buffer. */
                xfer->transferredCount = 0;
            }

            /* Slave receive, master writing to slave. */
            uint8_t data = (uint8_t)base->I2DR;

            if (handle->transfer.dataSize != 0U)
            {
                /* Receive data. */
                *handle->transfer.data++ = data;
                handle->transfer.dataSize--;
                xfer->transferredCount++;

                if (0U == handle->transfer.dataSize)
                {
                    xfer->event            = kI2C_SlaveCompletionEvent;
                    xfer->completionStatus = kStatus_Success;
                    handle->state          = (uint8_t)kIdleState;

                    /* Proceed receive complete event. */
                    if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
                    {
                        handle->callback(base, xfer, handle->userData);
                    }
                }
            }
        }
    }
    else
    {
        /* Read dummy to release bus. */
        dummy = (uint8_t)base->I2DR;
    }

    /* Send data if there is the need. */
    if (doTransmit)
    {
        /* If we're out of data, invoke callback to get more. */
        if ((NULL == xfer->data) || (0U == xfer->dataSize))
        {
            xfer->event = kI2C_SlaveTransmitEvent;

            if (handle->callback != NULL)
            {
                handle->callback(base, xfer, handle->userData);
            }

            /* Clear the transferred count now that we have a new buffer. */
            xfer->transferredCount = 0;
        }

        if (handle->transfer.dataSize != 0U)
        {
            /* Send data. */
            base->I2DR = *handle->transfer.data++;
            handle->transfer.dataSize--;
            xfer->transferredCount++;
        }
        else
        {
            /* Switch to receive mode. */
            base->I2CR &= ~((uint16_t)I2C_I2CR_MTX_MASK | (uint16_t)I2C_I2CR_TXAK_MASK);

            /* Read dummy to release bus. */
            dummy = (uint8_t)base->I2DR;

            xfer->event            = kI2C_SlaveCompletionEvent;
            xfer->completionStatus = kStatus_Success;
            handle->state          = (uint8_t)kIdleState;

            /* Proceed txdone event. */
            if (((handle->eventMask & (uint32_t)xfer->event) != 0U) && (handle->callback != NULL))
            {
                handle->callback(base, xfer, handle->userData);
            }
        }
    }
}

#if defined(I2C1)
void I2C1_DriverIRQHandler(void);
void I2C1_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C1, s_i2cHandle[1]);
}
#endif

#if defined(I2C2)
void I2C2_DriverIRQHandler(void);
void I2C2_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C2, s_i2cHandle[2]);
}
#endif

#if defined(I2C3)
void I2C3_DriverIRQHandler(void);
void I2C3_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C3, s_i2cHandle[3]);
}
#endif

#if defined(I2C4)
void I2C4_DriverIRQHandler(void);
void I2C4_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C4, s_i2cHandle[4]);
}
#endif

#if defined(I2C5)
void I2C5_DriverIRQHandler(void);
void I2C5_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C5, s_i2cHandle[5]);
}
#endif

#if defined(I2C6)
void I2C6_DriverIRQHandler(void);
void I2C6_DriverIRQHandler(void)
{
    I2C_TransferCommonIRQHandler(I2C6, s_i2cHandle[6]);
}
#endif
