/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ecspi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ecspi"
#endif

/*! @brief ECSPI transfer state, which is used for ECSPI transactiaonl APIs' internal state. */
enum
{
    kECSPI_Idle = 0x0, /*!< ECSPI is idle state */
    kECSPI_Busy        /*!< ECSPI is busy tranferring data. */
};

/*! @brief Typedef for ecspi master interrupt handler. ecspi master and slave handle is the same. */
typedef void (*ecspi_isr_t)(ECSPI_Type *base, ecspi_master_handle_t *ecspiHandle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Sends a buffer of data bytes in non-blocking way.
 *
 * @param base ECSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void ECSPI_WriteNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Receive a buffer of data bytes in non-blocking way.
 *
 * @param base ECSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void ECSPI_ReadNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Send a piece of data for ECSPI.
 *
 * This function computes the number of data to be written into D register or Tx FIFO,
 * and write the data into it. At the same time, this function updates the values in
 * master handle structure.
 *
 * @param base ECSPI base pointer
 * @param handle Pointer to ECSPI master handle structure.
 */
static void ECSPI_SendTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
 * @brief Receive a piece of data for ECSPI master.
 *
 * This function computes the number of data to receive from D register or Rx FIFO,
 * and write the data to destination address. At the same time, this function updates
 * the values in master handle structure.
 *
 * @param base ECSPI base pointer
 * @param handle Pointer to ECSPI master handle structure.
 */
static void ECSPI_ReceiveTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
 * @brief  Sets the ECSPI channel configuration structure to default values.
 *
 * This function is to get the channel configuration structure initialized for use in ECSPI_SetChannelConfig().
 * User may use the initialized structure unchanged in ECSPI_SetChannelConfig(), or modify
 * some fields of the structure before calling ECSPI_SetChannelConfig().
 *
 * @param config pointer to config structure
 */
static void ECSPI_GetDefaultChannelConfig(ecspi_channel_config_t *config);

/*!
 * @brief Common IRQ handler for SPI.
 *
 * @param base SPI base pointer.
 * @param instance SPI instance number.
 */
static void ECSPI_CommonIRQHandler(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Base pointer array */
static ECSPI_Type *const s_ecspiBases[] = ECSPI_BASE_PTRS;
/*! @brief ECSPI internal handle pointer array */
static ecspi_master_handle_t *s_ecspiHandle[ARRAY_SIZE(s_ecspiBases)];
/*! @brief IRQ name array */
static const IRQn_Type s_ecspiIRQ[] = ECSPI_IRQS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Clock array name */
static const clock_ip_name_t s_ecspiClock[] = ECSPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to master IRQ handler for each instance. */
static ecspi_isr_t s_ecspiMasterIsr;
/*! @brief Pointer to slave IRQ handler for each instance. */
static ecspi_isr_t s_ecspiSlaveIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Get the instance for ECSPI module.
 *
 * param base ECSPI base address
 */
uint32_t ECSPI_GetInstance(ECSPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_ecspiBases); instance++)
    {
        if (s_ecspiBases[instance] == base)
        {
            break;
        }
    }
    assert(instance <= ARRAY_SIZE(s_ecspiBases));
    return instance;
}

static void ECSPI_WriteNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    size_t i = 0U;

    for (i = 0U; i < size; i++)
    {
        if (buffer != NULL)
        {
            base->TXDATA = *buffer++;
        }
        else
        {
            ECSPI_WriteData(base, ECSPI_DUMMYDATA);
        }
    }
}

static void ECSPI_ReadNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    if (NULL != buffer)
    {
        while ((size--) != 0UL)
        {
            *buffer++ = ECSPI_ReadData(base);
        }
    }
    else
    {
        while ((size--) != 0UL)
        {
            (void)ECSPI_ReadData(base);
        }
    }
}

static void ECSPI_SendTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(base != NULL);
    assert(handle != NULL);

    uint32_t dataCounts       = 0U;
    uint32_t txRemainingBytes = (uint32_t)(handle->txRemainingBytes);
    /* Caculate the data size to send */
    dataCounts =
        ((uint32_t)FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(base) - (uint32_t)ECSPI_GetTxFifoCount(base)) < txRemainingBytes ?
            ((uint32_t)FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(base) - (uint32_t)ECSPI_GetTxFifoCount(base)) :
            txRemainingBytes;
    while ((dataCounts--) != 0UL)
    {
        ECSPI_WriteNonBlocking(base, handle->txData, 1);
        if (NULL != handle->txData)
        {
            handle->txData += 1U;
        }
        handle->txRemainingBytes -= 1U;
    }
}

static void ECSPI_ReceiveTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(base != NULL);

    uint32_t dataCounts = 0U;
    /* Caculate the data size need to receive */
    dataCounts =
        (ECSPI_GetRxFifoCount(base) < handle->rxRemainingBytes) ? ECSPI_GetRxFifoCount(base) : handle->rxRemainingBytes;

    ECSPI_ReadNonBlocking(base, handle->rxData, dataCounts);
    if (NULL != handle->rxData)
    {
        handle->rxData += dataCounts;
    }
    handle->rxRemainingBytes -= dataCounts;
}
static void ECSPI_GetDefaultChannelConfig(ecspi_channel_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->channelMode           = kECSPI_Slave;                    /*!< ECSPI peripheral operates in slave mode.*/
    config->clockInactiveState    = kECSPI_ClockInactiveStateLow;    /*!< Clock line (SCLK) inactive state */
    config->dataLineInactiveState = kECSPI_DataLineInactiveStateLow; /*!< Data line (MOSI&MISO) inactive state */
    config->chipSlectActiveState  = kECSPI_ChipSelectActiveStateLow; /*!< Chip select(SS) line active state */
    config->polarity              = kECSPI_PolarityActiveHigh;       /*!< Clock polarity */
    config->phase                 = kECSPI_ClockPhaseFirstEdge;      /*!< clock phase */
}

/*!
 * brief  Sets the ECSPI configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in ECSPI_MasterInit().
 * User may use the initialized structure unchanged in ECSPI_MasterInit, or modify
 * some fields of the structure before calling ECSPI_MasterInit. After calling this API,
 * the master is ready to transfer.
 * Example:
   code
   ecspi_master_config_t config;
   ECSPI_MasterGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to config structure
 */
void ECSPI_MasterGetDefaultConfig(ecspi_master_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->channel           = kECSPI_Channel0;
    config->burstLength       = 8;
    config->samplePeriodClock = kECSPI_spiClock;
    config->baudRate_Bps      = 500000;
    config->chipSelectDelay   = 0;
    config->samplePeriod      = 0;
    config->txFifoThreshold   = 1;
    config->rxFifoThreshold   = 0;
    /* Default configuration of channel */
    ECSPI_GetDefaultChannelConfig(&config->channelConfig);
    /*!< ECSPI peripheral operates in slave mode.*/
    config->channelConfig.channelMode = kECSPI_Master;
    config->enableLoopback            = false;
}

/*!
 * brief Initializes the ECSPI with configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by ECSPI_MasterGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   code
   ecspi_master_config_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   ECSPI_MasterInit(ECSPI0, &config);
   endcode
 *
 * param base ECSPI base pointer
 * param config pointer to master configuration structure
 * param srcClock_Hz Source clock frequency.
 */
void ECSPI_MasterInit(ECSPI_Type *base, const ecspi_master_config_t *config, uint32_t srcClock_Hz)
{
    assert((config != NULL) && (srcClock_Hz != 0U));
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Reset control register to default value */
    ECSPI_SoftwareReset(base);
    /* Config CONREG register */
    base->CONREG =
        ECSPI_CONREG_BURST_LENGTH((uint32_t)config->burstLength - 1UL) | ECSPI_CONREG_SMC(1U) | ECSPI_CONREG_EN(1U);
    /* Config CONFIGREG register */
    ECSPI_SetChannelConfig(base, config->channel, &config->channelConfig);
    /* Config DMAREG register */
    base->DMAREG |=
        ECSPI_DMAREG_TX_THRESHOLD(config->txFifoThreshold) | ECSPI_DMAREG_RX_THRESHOLD(config->rxFifoThreshold);
    /* Config PERIODREG register */
    base->PERIODREG |= ECSPI_PERIODREG_CSRC(config->samplePeriodClock) |
                       ECSPI_PERIODREG_SAMPLE_PERIOD(config->samplePeriod) |
                       ECSPI_PERIODREG_CSD_CTL(config->chipSelectDelay);
    /* Config TESTING register if enable the loopback function. */
    base->TESTREG |= ECSPI_TESTREG_LBC(config->enableLoopback);
    /* Set baud rate */
    ECSPI_SetBaudRate(base, config->baudRate_Bps, srcClock_Hz);
}

/*!
 * brief  Sets the ECSPI configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in ECSPI_SlaveInit().
 * User may use the initialized structure unchanged in ECSPI_SlaveInit(), or modify
 * some fields of the structure before calling ECSPI_SlaveInit(). After calling this API,
 * the master is ready to transfer.
 * Example:
   code
   ecspi_Slaveconfig_t config;
   ECSPI_SlaveGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to config structure
 */
void ECSPI_SlaveGetDefaultConfig(ecspi_slave_config_t *config)
{
    /* Default configuration of channel nember */

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
    config->channel = kECSPI_Channel0;

    config->burstLength     = 8;
    config->txFifoThreshold = 1;
    config->rxFifoThreshold = 0;
    /* Set default channel configuration */
    ECSPI_GetDefaultChannelConfig(&config->channelConfig);
    /* ECSPI peripheral operates in slave mode.*/
    config->channelConfig.channelMode = kECSPI_Slave;
}

/*!
 * brief Initializes the ECSPI with configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by ECSPI_SlaveGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   code
   ecspi_Salveconfig_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   ECSPI_SlaveInit(ECSPI1, &config);
   endcode
 *
 * param base ECSPI base pointer
 * param config pointer to master configuration structure
 */
void ECSPI_SlaveInit(ECSPI_Type *base, const ecspi_slave_config_t *config)
{
    assert((base != NULL) && (config != NULL));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset control register to default value */
    ECSPI_SoftwareReset(base);
    /* Config CONREG register */
    base->CONREG = ECSPI_CONREG_BURST_LENGTH(config->burstLength - 1UL) | ECSPI_CONREG_EN(1UL);
    /* Config DMAREG register */
    base->DMAREG |=
        ECSPI_DMAREG_TX_THRESHOLD(config->txFifoThreshold) | ECSPI_DMAREG_RX_THRESHOLD(config->rxFifoThreshold);
    /* Setup channel configuration */
    ECSPI_SetChannelConfig(base, config->channel, &config->channelConfig);
}

/*!
 * brief De-initializes the ECSPI.
 *
 * Calling this API resets the ECSPI module, gates the ECSPI clock.
 * The ECSPI module can't work unless calling the ECSPI_MasterInit/ECSPI_SlaveInit to initialize module.
 *
 * param base ECSPI base pointer
 */
void ECSPI_Deinit(ECSPI_Type *base)
{
    /* Disable ECSPI module before shutting down */
    base->CONREG &= ~ECSPI_CONREG_EN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the clock */
    CLOCK_DisableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Sets the baud rate for ECSPI transfer. This is only used in master.
 *
 * param base ECSPI base pointer
 * param baudRate_Bps baud rate needed in Hz.
 * param srcClock_Hz ECSPI source clock frequency in Hz.
 */
void ECSPI_SetBaudRate(ECSPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    assert(base != NULL);

    uint8_t bestPreDividerValue = 0U, preDividerValue = 0U;
    uint8_t bestPostDividerValue = 0U, postDividerValue = 0U;
    uint32_t realBaudrate = 0U;
    uint32_t diff         = 0xFFFFFFFFU;
    uint32_t min_diff     = 0xFFFFFFFFU;

    for (preDividerValue = 0U; preDividerValue < 16U; preDividerValue++)
    {
        if (diff == 0U)
        {
            break;
        }

        for (postDividerValue = 0U; postDividerValue < 16U; postDividerValue++)
        {
            if (diff == 0U)
            {
                break;
            }

            realBaudrate = (srcClock_Hz / (preDividerValue + 1UL)) >> postDividerValue;
            if (realBaudrate > baudRate_Bps)
            {
                diff = realBaudrate - baudRate_Bps;
                if (diff < min_diff)
                {
                    min_diff             = diff;
                    bestPreDividerValue  = preDividerValue;
                    bestPostDividerValue = postDividerValue;
                }
            }
            else
            {
                diff = baudRate_Bps - realBaudrate;
                if (diff < min_diff)
                {
                    min_diff             = diff;
                    bestPreDividerValue  = preDividerValue;
                    bestPostDividerValue = postDividerValue;
                }
            }
        }
    }

    base->CONREG |= ECSPI_CONREG_PRE_DIVIDER(bestPreDividerValue) | ECSPI_CONREG_POST_DIVIDER(bestPostDividerValue);
}

/*!
 * brief Set channel select configuration for transfer.
 *
 * The purpose of this API is to set the channel will be use to transfer.
 * User may use this API after instance has been initialized or before transfer start.
 * The configuration structure #_ecspi_channel_config_ can be filled by user from scratch.
 * After calling this API, user can select this channel as transfer channel.
 *
 * param base ECSPI base pointer
 * param channel Channel source.
 * param config Configuration struct of channel
 */
void ECSPI_SetChannelConfig(ECSPI_Type *base, ecspi_channel_source_t channel, const ecspi_channel_config_t *config)
{
    switch (channel)
    {
        case kECSPI_Channel0:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode);
            base->CONFIGREG |= (ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) |
                                ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) |
                                ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) |
                                ECSPI_CONFIGREG_SCLK_POL(config->polarity) | ECSPI_CONFIGREG_SCLK_PHA(config->phase));
            break;

        case kECSPI_Channel1:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 1U;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 1U) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 1U) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 1U) |
                 (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 1U) | (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 1U));
            break;

        case kECSPI_Channel2:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 2;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 2) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 2) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 2) |
                 (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 2) | (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 2));
            break;

        case kECSPI_Channel3:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 3;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 3) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 3) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 3) |
                 (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 3) | (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 3));
            break;

        default:
            assert(false);
            break;
    }
}

/*!
 * brief Sends a buffer of data bytes using a blocking method.
 *
 * note This function blocks via polling until all bytes have been sent.
 *
 * param base ECSPI base pointer
 * param buffer The data bytes to send
 * param size The number of data bytes to send
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_ECSPI_Timeout The transfer timed out and was aborted.
 */
status_t ECSPI_WriteBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    size_t i = 0U;
#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (i < size)
    {
        /* Wait for TX fifo buffer empty */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->STATREG & ECSPI_STATREG_TE_MASK) == 0UL) && (--waitTimes != 0U))
#else
        while ((base->STATREG & ECSPI_STATREG_TE_MASK) == 0UL)
#endif
        {
        }

#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_ECSPI_Timeout;
        }
#endif

        /* Write data to tx register */
        if (NULL != buffer)
        {
            ECSPI_WriteData(base, *buffer++);
        }
        else
        {
            ECSPI_WriteData(base, ECSPI_DUMMYDATA);
        }
        i++;
    }
    return kStatus_Success;
}

static status_t ECSPI_ReadBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    assert(base != NULL);

    uint32_t state = 0U;
    size_t i       = 0U;
#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (i < size)
    {
        /* Wait for RX FIFO buffer ready */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->STATREG & ECSPI_STATREG_RR_MASK) == 0UL) && (--waitTimes != 0U))
#else
        while ((base->STATREG & ECSPI_STATREG_RR_MASK) == 0UL)
#endif
        {
            /* Get status flags of ECSPI */
            state = ECSPI_GetStatusFlags(base);
            /* If hardware overflow happen */
            if ((ECSPI_STATREG_RO_MASK & state) != 0UL)
            {
                /* Clear overflow flag for next transfer */
                ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
                return kStatus_ECSPI_HardwareOverFlow;
            }
        }

#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_ECSPI_Timeout;
        }
#endif

        /* Read data from rx register */
        if (NULL != buffer)
        {
            *buffer++ = ECSPI_ReadData(base);
        }
        else
        {
            (void)ECSPI_ReadData(base);
        }
        i++;
    }
    return kStatus_Success;
}

/*!
 * brief Initializes the ECSPI master handle.
 *
 * This function initializes the ECSPI master handle which can be used for other ECSPI master transactional APIs.
 * Usually,
 * for a specified ECSPI instance, call this API once to get the initialized handle.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
void ECSPI_MasterTransferCreateHandle(ECSPI_Type *base,
                                      ecspi_master_handle_t *handle,
                                      ecspi_master_callback_t callback,
                                      void *userData)
{
    assert(base != NULL);
    assert(handle != NULL);

    uint32_t instance = ECSPI_GetInstance(base);

    /* Initialize the handle */
    s_ecspiHandle[instance] = handle;
    handle->callback        = callback;
    handle->userData        = userData;
    s_ecspiMasterIsr        = ECSPI_MasterTransferHandleIRQ;

    /* Enable ECSPI NVIC */
    (void)EnableIRQ(s_ecspiIRQ[instance]);
}

/*!
 * brief Transfers a block of data using a polling method.
 *
 * param base SPI base pointer
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_ECSPI_Timeout The transfer timed out and was aborted.
 */
status_t ECSPI_MasterTransferBlocking(ECSPI_Type *base, ecspi_transfer_t *xfer)
{
    assert((base != NULL) && (xfer != NULL));

    status_t state;
    uint32_t burstLength = 0U;
    uint32_t dataCounts  = 0U;
    /* Check if the argument is legal */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return kStatus_InvalidArgument;
    }
    /* Select ECSPI channel to current channel
     * Note:
     *     xfer.channel must be configured before transfer, because every channel has
     *     it's own configuration,if don't configure this parameter, transfer channel
     *     will use the default channel0.
     */
    ECSPI_SetChannelSelect(base, xfer->channel);
    /* Caculate the data size need to be send for one burst */
    burstLength = ((base->CONREG & ECSPI_CONREG_BURST_LENGTH_MASK) >> ECSPI_CONREG_BURST_LENGTH_SHIFT) + 1UL;
    dataCounts  = ((burstLength % 32UL) != 0UL) ? (burstLength / 32UL + 1UL) : (burstLength / 32UL);

    while (xfer->dataSize > 0UL)
    {
        /* ECSPI will transmit and receive at the same time, if txData is NULL,
         * instance will transmit dummy data, the dummy data can be set by user.
         * if rxData is NULL, data will be read from RX FIFO buffer, but the
         * data will be ignored by driver.
         * Note that, txData and rxData can not be both NULL.
         */
        state = ECSPI_WriteBlocking(base, xfer->txData, dataCounts);
        if (kStatus_Success != state)
        {
            return state;
        }
        if (NULL != xfer->txData)
        {
            xfer->txData += dataCounts;
        }
        state = ECSPI_ReadBlocking(base, xfer->rxData, dataCounts);
        if (kStatus_Success != state)
        {
            return state;
        }
        if (NULL != xfer->rxData)
        {
            xfer->rxData += dataCounts;
        }

        xfer->dataSize -= dataCounts;
    }

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking ECSPI interrupt transfer.
 *
 * note The API immediately returns after transfer initialization is finished.
 * note If ECSPI transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * param base ECSPI peripheral base address.
 * param handle pointer to ecspi_master_handle_t structure which stores the transfer state
 * param xfer pointer to ecspi_transfer_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_ECSPI_Busy ECSPI is not idle, is running another transfer.
 */
status_t ECSPI_MasterTransferNonBlocking(ECSPI_Type *base, ecspi_master_handle_t *handle, ecspi_transfer_t *xfer)
{
    assert((base != NULL) && (handle != NULL) && (xfer != NULL));

    /* Check if ECSPI is busy */
    if (handle->state == (uint32_t)kECSPI_Busy)
    {
        return kStatus_ECSPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    /* Set the handle information */
    handle->channel          = xfer->channel;
    handle->txData           = xfer->txData;
    handle->rxData           = xfer->rxData;
    handle->transferSize     = xfer->dataSize;
    handle->txRemainingBytes = xfer->dataSize;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Set the ECSPI state to busy */
    handle->state = kECSPI_Busy;

    /* Select ECSPI channel to current channel
     * Note:
     *     xfer.channel must be configured before transferfer, because every channel has
     *     it's own configuration, if don't configure this parameter, transfer channel
     *     will use the default channel0.
     */
    ECSPI_SetChannelSelect(base, xfer->channel);

    /* First send data to Tx FIFO to start a ECSPI transfer */
    ECSPI_SendTransfer(base, handle);

    if (NULL != xfer->rxData)
    {
        /* Enable Rx data request interrupt and receive overflow interrupt, when data in RX FIFO buffer is greater
         * than the RX_THRESHOLD, then a interrupt occurred. Only enable Rx interrupt,
         * use rx interrupt to driver ECSPI transfer.
         */
        ECSPI_EnableInterrupts(
            base, (uint32_t)kECSPI_RxFifoReadyInterruptEnable | (uint32_t)kECSPI_RxFifoOverFlowInterruptEnable);
    }
    else
    {
        /* Enable Tx data request interrupt, when data in TX FIFO buffer is greater
         * than the TX_THRESHOLD, then a interrupt occurred.
         */
        ECSPI_EnableInterrupts(base, kECSPI_TxFifoDataRequstInterruptEnable);
    }

    return kStatus_Success;
}

/*!
 * brief Gets the bytes of the ECSPI interrupt transferred.
 *
 * param base ECSPI peripheral base address.
 * param handle Pointer to ECSPI transfer handle, this should be a static variable.
 * param count Transferred bytes of ECSPI master.
 * retval kStatus_ECSPI_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ECSPI_MasterTransferGetCount(ECSPI_Type *base, ecspi_master_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kStatus_ECSPI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        /* Return remaing bytes in different cases */
        if (handle->rxData != NULL)
        {
            *count = handle->transferSize - handle->rxRemainingBytes;
        }
        else
        {
            *count = handle->transferSize - handle->txRemainingBytes;
        }
    }

    return status;
}

/*!
 * brief Aborts an ECSPI transfer using interrupt.
 *
 * param base ECSPI peripheral base address.
 * param handle Pointer to ECSPI transfer handle, this should be a static variable.
 */
void ECSPI_MasterTransferAbort(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(handle != NULL);

    /* Stop interrupts */
    if (NULL != handle->rxData)
    {
        ECSPI_DisableInterrupts(
            base, (uint32_t)kECSPI_RxFifoReadyInterruptEnable | (uint32_t)kECSPI_RxFifoOverFlowInterruptEnable);
    }
    else
    {
        ECSPI_DisableInterrupts(base, kECSPI_TxFifoDataRequstInterruptEnable);
    }
    /* Transfer finished, set the state to Done*/
    handle->state = kECSPI_Idle;

    /* Clear the internal state */
    handle->rxRemainingBytes = 0;
    handle->txRemainingBytes = 0;
}

/*!
 * brief Interrupts the handler for the ECSPI.
 *
 * param base ECSPI peripheral base address.
 * param handle pointer to ecspi_master_handle_t structure which stores the transfer state.
 */
void ECSPI_MasterTransferHandleIRQ(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(handle != NULL);

    /* If hardware overflow happens */
    if ((base->STATREG & ECSPI_STATREG_RO_MASK) != 0UL)
    {
        /* Clear overflow flag for next transfer */
        ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
        if ((handle->callback) != NULL)
        {
            (handle->callback)(base, handle, kStatus_ECSPI_HardwareOverFlow, handle->userData);
        }
    }
    /* If need to receive data, do a receive */
    if ((handle->rxRemainingBytes) != 0UL)
    {
        ECSPI_ReceiveTransfer(base, handle);
    }

    /* We always need to send a data to make the ECSPI run */
    if ((handle->txRemainingBytes) != 0UL)
    {
        ECSPI_SendTransfer(base, handle);
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0UL) && (handle->rxRemainingBytes == 0UL))
    {
        /* Complete the transfer */
        ECSPI_MasterTransferAbort(base, handle);

        if ((handle->callback) != NULL)
        {
            (handle->callback)(base, handle, kStatus_Success, handle->userData);
        }
    }
}

/*!
 * brief Initializes the ECSPI slave handle.
 *
 * This function initializes the ECSPI slave handle which can be used for other ECSPI slave transactional APIs. Usually,
 * for a specified ECSPI instance, call this API once to get the initialized handle.
 *
 * param base ECSPI peripheral base address.
 * param handle ECSPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
void ECSPI_SlaveTransferCreateHandle(ECSPI_Type *base,
                                     ecspi_slave_handle_t *handle,
                                     ecspi_slave_callback_t callback,
                                     void *userData)
{
    assert(handle != NULL);

    /* Slave create handle share same logic with master create handle, the only difference
    is the Isr pointer. */
    ECSPI_MasterTransferCreateHandle(base, handle, callback, userData);
    s_ecspiSlaveIsr = ECSPI_SlaveTransferHandleIRQ;
}

/*!
 * brief Interrupts a handler for the ECSPI slave.
 *
 * param base ECSPI peripheral base address.
 * param handle pointer to ecspi_slave_handle_t structure which stores the transfer state
 */
void ECSPI_SlaveTransferHandleIRQ(ECSPI_Type *base, ecspi_slave_handle_t *handle)
{
    assert(handle != NULL);
    /* If hardware overflow happens */
    if ((base->STATREG & ECSPI_STATREG_RO_MASK) != 0UL)
    {
        /* Clear overflow flag for next transfer */
        ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
        if ((handle->callback) != NULL)
        {
            (handle->callback)(base, handle, kStatus_ECSPI_HardwareOverFlow, handle->userData);
        }
    }
    /* If needs to receive data, do a receive */
    if ((handle->rxRemainingBytes) != 0UL)
    {
        ECSPI_ReceiveTransfer(base, handle);
    }

    /* We always need to send a data to make the ECSPI run */
    if ((handle->txRemainingBytes) != 0UL)
    {
        ECSPI_SendTransfer(base, handle);
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0UL) && (handle->rxRemainingBytes == 0UL))
    {
        /* Complete the transfer */
        ECSPI_SlaveTransferAbort(base, handle);

        if ((handle->callback) != NULL)
        {
            (handle->callback)(base, handle, kStatus_Success, handle->userData);
        }
    }
}

static void ECSPI_CommonIRQHandler(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    if (ECSPI_IsMaster(base, handle->channel))
    {
        s_ecspiMasterIsr(base, handle);
    }
    else
    {
        s_ecspiSlaveIsr(base, handle);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(ECSPI1)
void ECSPI1_DriverIRQHandler(void);
void ECSPI1_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[1]);
    ECSPI_CommonIRQHandler(ECSPI1, s_ecspiHandle[1]);
}
#endif /* ECSPI1 */

#if defined(ECSPI2)
void ECSPI2_DriverIRQHandler(void);
void ECSPI2_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[2]);
    ECSPI_CommonIRQHandler(ECSPI2, s_ecspiHandle[2]);
}
#endif /* ECSPI2 */

#if defined(ECSPI3)
void ECSPI3_DriverIRQHandler(void);
void ECSPI3_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[3]);
    ECSPI_CommonIRQHandler(ECSPI3, s_ecspiHandle[3]);
}
#endif /* ECSPI3 */

#if defined(ECSPI4)
void ECSPI4_DriverIRQHandler(void);
void ECSPI4_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[4]);
    ECSPI_CommonIRQHandler(ECSPI4, s_ecspiHandle[4]);
}
#endif /* ECSPI4 */
