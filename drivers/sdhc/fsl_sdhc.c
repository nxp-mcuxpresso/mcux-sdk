/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdhc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sdhc"
#endif

/*! @brief Clock setting */
/* Max SD clock divisor from base clock */
#define SDHC_MAX_DVS       ((SDHC_SYSCTL_DVS_MASK >> SDHC_SYSCTL_DVS_SHIFT) + 1U)
#define SDHC_PREV_DVS(x)   ((x) -= 1U)
#define SDHC_MAX_CLKFS     ((SDHC_SYSCTL_SDCLKFS_MASK >> SDHC_SYSCTL_SDCLKFS_SHIFT) + 1U)
#define SDHC_PREV_CLKFS(x) ((x) >>= 1U)

/* Typedef for interrupt handler. */
typedef void (*sdhc_isr_t)(SDHC_Type *base, sdhc_handle_t *handle);

/*! @brief ADMA table configuration */
typedef struct _sdhc_adma_table_config
{
    uint32_t *admaTable;     /*!< ADMA table address, can't be null if transfer way is ADMA1/ADMA2 */
    uint32_t admaTableWords; /*!< ADMA table length united as words, can't be 0 if transfer way is ADMA1/ADMA2 */
} sdhc_adma_table_config_t;
/*! @brief check flag avalibility */
#define IS_SDHC_FLAG_SET(reg, flag) (((reg) & ((uint32_t)flag)) != 0UL)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance.
 *
 * @param base SDHC peripheral base address.
 * @return Instance number.
 */
static uint32_t SDHC_GetInstance(SDHC_Type *base);

/*!
 * @brief Start transfer according to current transfer state
 *
 * @param base SDHC peripheral base address.
 * @param command Command to be sent.
 * @param data Data to be transferred.
 * @param DMA mode selection
 */
static void SDHC_StartTransfer(SDHC_Type *base, sdhc_command_t *command, sdhc_data_t *data, sdhc_dma_mode_t dmaMode);

/*!
 * @brief Receive command response
 *
 * @param base SDHC peripheral base address.
 * @param command Command to be sent.
 */
static status_t SDHC_ReceiveCommandResponse(SDHC_Type *base, sdhc_command_t *command);

/*!
 * @brief Read DATAPORT when buffer enable bit is set.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be read.
 * @param transferredWords The number of data words have been transferred last time transaction.
 * @return The number of total data words have been transferred after this time transaction.
 */
static uint32_t SDHC_ReadDataPort(SDHC_Type *base, sdhc_data_t *data, uint32_t transferredWords);

/*!
 * @brief Read data by using DATAPORT polling way.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be read.
 * @retval kStatus_Fail Read DATAPORT failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_ReadByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data);

/*!
 * @brief Write DATAPORT when buffer enable bit is set.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be read.
 * @param transferredWords The number of data words have been transferred last time.
 * @return The number of total data words have been transferred after this time transaction.
 */
static uint32_t SDHC_WriteDataPort(SDHC_Type *base, sdhc_data_t *data, uint32_t transferredWords);

/*!
 * @brief Write data by using DATAPORT polling way.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be transferred.
 * @retval kStatus_Fail Write DATAPORT failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_WriteByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data);

/*!
 * @brief Send command by using polling way.
 *
 * @param base SDHC peripheral base address.
 * @param command Command to be sent.
 * @retval kStatus_Fail Send command failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_SendCommandBlocking(SDHC_Type *base, sdhc_command_t *command);

/*!
 * @brief Transfer data by DATAPORT and polling way.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be transferred.
 * @retval kStatus_Fail Transfer data failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_TransferByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data);

/*!
 * @brief Transfer data by ADMA2 and polling way.
 *
 * @param base SDHC peripheral base address.
 * @param data Data to be transferred.
 * @retval kStatus_Fail Transfer data failed.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_TransferByAdma2Blocking(SDHC_Type *base, sdhc_data_t *data);

/*!
 * @brief Transfer data by polling way.
 *
 * @param dmaMode DMA mode.
 * @param base SDHC peripheral base address.
 * @param data Data to be transferred.
 * @retval kStatus_Fail Transfer data failed.
 * @retval kStatus_InvalidArgument Argument is invalid.
 * @retval kStatus_Success Operate successfully.
 */
static status_t SDHC_TransferDataBlocking(sdhc_dma_mode_t dmaMode, SDHC_Type *base, sdhc_data_t *data);

/*!
 * @brief Handle card detect interrupt.
 *
 * @param base SDHC peripheral base address.
 * @param handle SDHC handle.
 * @param interruptFlags Card detect related interrupt flags.
 */
static void SDHC_TransferHandleCardDetect(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags);

/*!
 * @brief Handle command interrupt.
 *
 * @param base SDHC peripheral base address.
 * @param handle SDHC handle.
 * @param interruptFlags Command related interrupt flags.
 */
static void SDHC_TransferHandleCommand(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags);

/*!
 * @brief Handle data interrupt.
 *
 * @param base SDHC peripheral base address.
 * @param handle SDHC handle.
 * @param interruptFlags Data related interrupt flags.
 */
static void SDHC_TransferHandleData(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags);

/*!
 * @brief Handle SDIO card interrupt signal.
 *
 * @param base SDHC peripheral base address.
 * @param handle SDHC handle.
 */
static void SDHC_TransferHandleSdioInterrupt(SDHC_Type *base, sdhc_handle_t *handle);

/*!
 * @brief Handle SDIO block gap event.
 *
 * @param base SDHC peripheral base address.
 * @param handle SDHC handle.
 */
static void SDHC_TransferHandleSdioBlockGap(SDHC_Type *base, sdhc_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief SDHC internal handle pointer array */
static sdhc_handle_t *s_sdhcHandle[FSL_FEATURE_SOC_SDHC_COUNT];

/*! @brief SDHC base pointer array */
static SDHC_Type *const s_sdhcBase[] = SDHC_BASE_PTRS;

/*! @brief SDHC IRQ name array */
static const IRQn_Type s_sdhcIRQ[] = SDHC_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief SDHC clock array name */
static const clock_ip_name_t s_sdhcClock[] = SDHC_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* SDHC ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static sdhc_isr_t s_sdhcIsr = (sdhc_isr_t)DefaultISR;
#else
static sdhc_isr_t s_sdhcIsr;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t SDHC_GetInstance(SDHC_Type *base)
{
    uint8_t instance = 0;

    while ((instance < ARRAY_SIZE(s_sdhcBase)) && (s_sdhcBase[instance] != base))
    {
        instance++;
    }

    assert(instance < ARRAY_SIZE(s_sdhcBase));

    return instance;
}

static void SDHC_StartTransfer(SDHC_Type *base, sdhc_command_t *command, sdhc_data_t *data, sdhc_dma_mode_t dmaMode)
{
    uint32_t flags                            = 0U;
    sdhc_transfer_config_t sdhcTransferConfig = {0};

    /* Define the flag corresponding to each response type. */
    if (command->responseType == kCARD_ResponseTypeR1) /* Response 1 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR1b) /* Response 1 with busy */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48BusyFlag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR2) /* Response 2 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength136Flag | (uint32_t)kSDHC_EnableCrcCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR3) /* Response 3 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag);
    }
    else if (command->responseType == kCARD_ResponseTypeR4) /* Response 4 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag);
    }
    else if (command->responseType == kCARD_ResponseTypeR5) /* Response 5 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR5b) /* Response 5 with busy */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48BusyFlag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR6) /* Response 6 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else if (command->responseType == kCARD_ResponseTypeR7) /* Response 7 */
    {
        flags |= ((uint32_t)kSDHC_ResponseLength48Flag | (uint32_t)kSDHC_EnableCrcCheckFlag |
                  (uint32_t)kSDHC_EnableIndexCheckFlag);
    }
    else
    {
        /* Intentional empty for kCARD_ResponseTypeNone */
    }

    if (command->type == kCARD_CommandTypeAbort)
    {
        flags |= (uint32_t)kSDHC_CommandTypeAbortFlag;
    }

    if (data != NULL)
    {
        flags |= (uint32_t)kSDHC_DataPresentFlag;

        if (dmaMode != kSDHC_DmaModeNo)
        {
            flags |= (uint32_t)kSDHC_EnableDmaFlag;
        }

        if (data->rxData != NULL)
        {
            flags |= (uint32_t)kSDHC_DataReadFlag;
        }
        if (data->blockCount > 1U)
        {
            flags |= ((uint32_t)kSDHC_MultipleBlockFlag | (uint32_t)kSDHC_EnableBlockCountFlag);
            if (data->enableAutoCommand12)
            {
                /* Enable Auto command 12. */
                flags |= (uint32_t)kSDHC_EnableAutoCommand12Flag;
            }
        }

        sdhcTransferConfig.dataBlockSize  = data->blockSize;
        sdhcTransferConfig.dataBlockCount = data->blockCount;
    }
    else
    {
        sdhcTransferConfig.dataBlockSize  = 0U;
        sdhcTransferConfig.dataBlockCount = 0U;
    }

    sdhcTransferConfig.commandArgument = command->argument;
    sdhcTransferConfig.commandIndex    = command->index;
    sdhcTransferConfig.flags           = flags;
    SDHC_SetTransferConfig(base, &sdhcTransferConfig);
}

static status_t SDHC_ReceiveCommandResponse(SDHC_Type *base, sdhc_command_t *command)
{
    assert(command != NULL);

    uint32_t response0 = base->CMDRSP[0];
    uint32_t response1 = base->CMDRSP[1];
    uint32_t response2 = base->CMDRSP[2];

    if (command->responseType != kCARD_ResponseTypeNone)
    {
        command->response[0U] = response0;
        if (command->responseType == kCARD_ResponseTypeR2)
        {
            /* R3-R2-R1-R0(lowest 8 bit is invalid bit) has the same format as R2 format in SD specification document
            after removed internal CRC7 and end bit. */
            command->response[0U] <<= 8U;
            command->response[1U] = (response1 << 8U) | ((response0 & 0xFF000000U) >> 24U);
            command->response[2U] = (response2 << 8U) | ((response1 & 0xFF000000U) >> 24U);
            command->response[3U] = (base->CMDRSP[3] << 8U) | ((response2 & 0xFF000000U) >> 24U);
        }
    }

    /* check response error flag */
    if ((command->responseErrorFlags != 0U) &&
        ((command->responseType == kCARD_ResponseTypeR1) || (command->responseType == kCARD_ResponseTypeR1b) ||
         (command->responseType == kCARD_ResponseTypeR6) || (command->responseType == kCARD_ResponseTypeR5)))
    {
        if (((command->responseErrorFlags) & (command->response[0U])) != 0U)
        {
            return kStatus_SDHC_SendCommandFailed;
        }
    }

    return kStatus_Success;
}

static uint32_t SDHC_ReadDataPort(SDHC_Type *base, sdhc_data_t *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t totalWords;
    uint32_t wordsCanBeRead; /* The words can be read at this time. */
    uint32_t readWatermark = ((base->WML & SDHC_WML_RDWML_MASK) >> SDHC_WML_RDWML_SHIFT);

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    /* If watermark level is equal or bigger than totalWords, transfers totalWords data. */
    if (readWatermark >= totalWords)
    {
        wordsCanBeRead = totalWords;
    }
    /* If watermark level is less than totalWords and left words to be sent is equal or bigger than readWatermark,
    transfers watermark level words. */
    else if ((readWatermark < totalWords) && ((totalWords - transferredWords) >= readWatermark))
    {
        wordsCanBeRead = readWatermark;
    }
    /* If watermark level is less than totalWords and left words to be sent is less than readWatermark, transfers left
    words. */
    else
    {
        wordsCanBeRead = (totalWords - transferredWords);
    }

    i = 0U;
    while (i < wordsCanBeRead)
    {
        data->rxData[transferredWords++] = SDHC_ReadData(base);
        i++;
    }

    return transferredWords;
}

static status_t SDHC_ReadByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data)
{
    uint32_t totalWords;
    uint32_t transferredWords = 0U;
    status_t error            = kStatus_Success;

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    while ((error == kStatus_Success) && (transferredWords < totalWords))
    {
        while (!(IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base),
                                  ((uint32_t)kSDHC_BufferReadReadyFlag | (uint32_t)kSDHC_DataErrorFlag))))
        {
        }

        if (IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base), kSDHC_DataErrorFlag))
        {
            if (!(data->enableIgnoreError))
            {
                error = kStatus_Fail;
            }
        }
        if (error == kStatus_Success)
        {
            transferredWords = SDHC_ReadDataPort(base, data, transferredWords);
        }
        /* clear buffer ready and error */
        SDHC_ClearInterruptStatusFlags(base, (uint32_t)kSDHC_BufferReadReadyFlag | (uint32_t)kSDHC_DataErrorFlag);
    }

    /* Clear data complete flag after the last read operation. */
    SDHC_ClearInterruptStatusFlags(base, (uint32_t)kSDHC_DataCompleteFlag | (uint32_t)kSDHC_DataErrorFlag);

    return error;
}

static uint32_t SDHC_WriteDataPort(SDHC_Type *base, sdhc_data_t *data, uint32_t transferredWords)
{
    uint32_t i;
    uint32_t totalWords;
    uint32_t wordsCanBeWrote; /* Words can be wrote at this time. */
    uint32_t writeWatermark = ((base->WML & SDHC_WML_WRWML_MASK) >> SDHC_WML_WRWML_SHIFT);

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = ((data->blockCount * data->blockSize) / sizeof(uint32_t));

    /* If watermark level is equal or bigger than totalWords, transfers totalWords data.*/
    if (writeWatermark >= totalWords)
    {
        wordsCanBeWrote = totalWords;
    }
    /* If watermark level is less than totalWords and left words to be sent is equal or bigger than watermark,
    transfers watermark level words. */
    else if ((writeWatermark < totalWords) && ((totalWords - transferredWords) >= writeWatermark))
    {
        wordsCanBeWrote = writeWatermark;
    }
    /* If watermark level is less than totalWords and left words to be sent is less than watermark, transfers left
    words. */
    else
    {
        wordsCanBeWrote = (totalWords - transferredWords);
    }

    i = 0U;
    while (i < wordsCanBeWrote)
    {
        SDHC_WriteData(base, data->txData[transferredWords++]);
        i++;
    }

    return transferredWords;
}

static status_t SDHC_WriteByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data)
{
    uint32_t totalWords;
    uint32_t transferredWords = 0U;
    status_t error            = kStatus_Success;

    /*
     * Add non aligned access support ,user need make sure your buffer size is big
     * enough to hold the data,in other words,user need make sure the buffer size
     * is 4 byte aligned
     */
    if (data->blockSize % sizeof(uint32_t) != 0U)
    {
        data->blockSize +=
            sizeof(uint32_t) - (data->blockSize % sizeof(uint32_t)); /* make the block size as word-aligned */
    }

    totalWords = (data->blockCount * data->blockSize) / sizeof(uint32_t);

    while ((error == kStatus_Success) && (transferredWords < totalWords))
    {
        while (!(IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base),
                                  ((uint32_t)kSDHC_BufferWriteReadyFlag | (uint32_t)kSDHC_DataErrorFlag))))
        {
        }

        if (IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base), kSDHC_DataErrorFlag))
        {
            if (!(data->enableIgnoreError))
            {
                error = kStatus_Fail;
            }
        }
        if (error == kStatus_Success)
        {
            transferredWords = SDHC_WriteDataPort(base, data, transferredWords);
        }

        /* Clear buffer enable flag to trigger transfer. Clear error flag when SDHC encounter error. */
        SDHC_ClearInterruptStatusFlags(base, ((uint32_t)kSDHC_BufferWriteReadyFlag | (uint32_t)kSDHC_DataErrorFlag));
    }

    /* Wait write data complete or data transfer error after the last writing operation. */
    while (!(IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base),
                              ((uint32_t)kSDHC_DataCompleteFlag | (uint32_t)kSDHC_DataErrorFlag))))
    {
    }
    if (IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base), kSDHC_DataErrorFlag))
    {
        if (!(data->enableIgnoreError))
        {
            error = kStatus_Fail;
        }
    }

    SDHC_ClearInterruptStatusFlags(base, ((uint32_t)kSDHC_DataCompleteFlag | (uint32_t)kSDHC_DataErrorFlag));

    return error;
}

static status_t SDHC_SendCommandBlocking(SDHC_Type *base, sdhc_command_t *command)
{
    status_t error = kStatus_Success;

    /* Wait command complete or SDHC encounters error. */
    while (!(IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base),
                              ((uint32_t)kSDHC_CommandCompleteFlag | (uint32_t)kSDHC_CommandErrorFlag))))
    {
    }

    if (IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base), kSDHC_CommandErrorFlag))
    {
        error = kStatus_Fail;
    }
    /* Receive response when command completes successfully. */
    if (error == kStatus_Success)
    {
        error = SDHC_ReceiveCommandResponse(base, command);
    }

    SDHC_ClearInterruptStatusFlags(base, ((uint32_t)kSDHC_CommandCompleteFlag | (uint32_t)kSDHC_CommandErrorFlag));

    return error;
}

static status_t SDHC_TransferByDataPortBlocking(SDHC_Type *base, sdhc_data_t *data)
{
    status_t error = kStatus_Success;

    if (data->rxData != NULL)
    {
        error = SDHC_ReadByDataPortBlocking(base, data);
        if (error != kStatus_Success)
        {
            return error;
        }
    }
    else
    {
        error = SDHC_WriteByDataPortBlocking(base, data);
        if (error != kStatus_Success)
        {
            return error;
        }
    }

    return kStatus_Success;
}

static status_t SDHC_TransferByAdma2Blocking(SDHC_Type *base, sdhc_data_t *data)
{
    status_t error = kStatus_Success;

    /* Wait data complete or SDHC encounters error. */
    while (!(IS_SDHC_FLAG_SET(
        SDHC_GetInterruptStatusFlags(base),
        ((uint32_t)kSDHC_DataCompleteFlag | (uint32_t)kSDHC_DataErrorFlag | (uint32_t)kSDHC_DmaErrorFlag))))
    {
    }
    if (IS_SDHC_FLAG_SET(SDHC_GetInterruptStatusFlags(base),
                         ((uint32_t)kSDHC_DataErrorFlag | (uint32_t)kSDHC_DmaErrorFlag)))
    {
        if (!(data->enableIgnoreError))
        {
            error = kStatus_Fail;
        }
    }
    SDHC_ClearInterruptStatusFlags(base, ((uint32_t)kSDHC_DataCompleteFlag | (uint32_t)kSDHC_DmaCompleteFlag |
                                          (uint32_t)kSDHC_DataErrorFlag | (uint32_t)kSDHC_DmaErrorFlag));

    return error;
}

#if defined FSL_SDHC_ENABLE_ADMA1
#define SDHC_TransferByAdma1Blocking(base, data) SDHC_TransferByAdma2Blocking(base, data)
#endif /* FSL_SDHC_ENABLE_ADMA1 */

static status_t SDHC_TransferDataBlocking(sdhc_dma_mode_t dmaMode, SDHC_Type *base, sdhc_data_t *data)
{
    status_t error = kStatus_Success;

    if (dmaMode == kSDHC_DmaModeNo)
    {
        error = SDHC_TransferByDataPortBlocking(base, data);
        if (error != kStatus_Success)
        {
            return error;
        }
    }
#if defined FSL_SDHC_ENABLE_ADMA1
    else if (dmaMode == kSDHC_DmaModeAdma1)
    {
        error = SDHC_TransferByAdma1Blocking(base, data);
        if (error != kStatus_Success)
        {
            return error;
        }
    }
#endif /* FSL_SDHC_ENABLE_ADMA1 */

    /*kSDHC_DmaModeAdma2*/
    else
    {
        error = SDHC_TransferByAdma2Blocking(base, data);
        if (error != kStatus_Success)
        {
            return error;
        }
    }

    return kStatus_Success;
}

static void SDHC_TransferHandleCardDetect(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags)
{
    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_CardInsertionFlag))
    {
        if (handle->callback.CardInserted != NULL)
        {
            handle->callback.CardInserted(base, handle->userData);
        }
    }
    else
    {
        if (handle->callback.CardRemoved != NULL)
        {
            handle->callback.CardRemoved(base, handle->userData);
        }
    }
}

static void SDHC_TransferHandleCommand(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags)
{
    assert(handle->command != NULL);

    if ((IS_SDHC_FLAG_SET(interruptFlags, kSDHC_CommandErrorFlag)) && (handle->data == NULL) &&
        (handle->callback.TransferComplete != NULL))
    {
        handle->callback.TransferComplete(base, handle, kStatus_SDHC_SendCommandFailed, handle->userData);
    }
    else
    {
        /* Receive response */
        if (kStatus_Success != SDHC_ReceiveCommandResponse(base, handle->command))
        {
            if (handle->callback.TransferComplete != NULL)
            {
                handle->callback.TransferComplete(base, handle, kStatus_SDHC_SendCommandFailed, handle->userData);
            }
        }
        else
        {
            if (handle->callback.TransferComplete != NULL)
            {
                handle->callback.TransferComplete(base, handle, kStatus_SDHC_TransferCommandComplete, handle->userData);
            }
        }
    }

    SDHC_DisableInterruptSignal(base, kSDHC_CommandFlag);
    handle->command = NULL;
}

static void SDHC_TransferHandleData(SDHC_Type *base, sdhc_handle_t *handle, uint32_t interruptFlags)
{
    assert(handle->data != NULL);

    status_t transferStatus   = kStatus_SDHC_BusyTransferring;
    uint32_t transferredWords = handle->transferredWords;

    if ((!(handle->data->enableIgnoreError)) &&
        (IS_SDHC_FLAG_SET(interruptFlags, ((uint32_t)kSDHC_DataErrorFlag | (uint32_t)kSDHC_DmaErrorFlag))))
    {
        transferStatus = kStatus_SDHC_TransferDataFailed;
    }
    else
    {
        if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_BufferReadReadyFlag))
        {
            handle->transferredWords = SDHC_ReadDataPort(base, handle->data, transferredWords);
        }
        else if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_BufferWriteReadyFlag))
        {
            handle->transferredWords = SDHC_WriteDataPort(base, handle->data, transferredWords);
        }
        else
        {
            /* Intentional empty */
        }

        if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_DataCompleteFlag))
        {
            transferStatus = kStatus_SDHC_TransferDataComplete;
        }
    }

    if ((transferStatus != kStatus_SDHC_BusyTransferring) && (handle->callback.TransferComplete != NULL))
    {
        handle->callback.TransferComplete(base, handle, transferStatus, handle->userData);
        SDHC_DisableInterruptSignal(base, (uint32_t)kSDHC_DataFlag | (uint32_t)kSDHC_DataDMAFlag);
        handle->data = NULL;
    }
}

static void SDHC_TransferHandleSdioInterrupt(SDHC_Type *base, sdhc_handle_t *handle)
{
    if (handle->callback.SdioInterrupt != NULL)
    {
        handle->callback.SdioInterrupt(base, handle->userData);
    }
}

static void SDHC_TransferHandleSdioBlockGap(SDHC_Type *base, sdhc_handle_t *handle)
{
    if (handle->callback.SdioBlockGap != NULL)
    {
        handle->callback.SdioBlockGap(base, handle->userData);
    }
}

/*!
 * brief SDHC module initialization function.
 *
 * Configures the SDHC according to the user configuration.
 *
 * Example:
   code
   sdhc_config_t config;
   config.cardDetectDat3 = false;
   config.endianMode = kSDHC_EndianModeLittle;
   config.dmaMode = kSDHC_DmaModeAdma2;
   config.readWatermarkLevel = 128U;
   config.writeWatermarkLevel = 128U;
   SDHC_Init(SDHC, &config);
   endcode
 *
 * param base SDHC peripheral base address.
 * param config SDHC configuration information.
 * retval kStatus_Success Operate successfully.
 */
void SDHC_Init(SDHC_Type *base, const sdhc_config_t *config)
{
    assert(config != NULL);
#if !defined FSL_SDHC_ENABLE_ADMA1
    assert(config->dmaMode != kSDHC_DmaModeAdma1);
#endif /* FSL_SDHC_ENABLE_ADMA1 */
    assert((config->writeWatermarkLevel >= 1UL) && (config->writeWatermarkLevel <= 128UL));
    assert((config->readWatermarkLevel >= 1UL) && (config->readWatermarkLevel <= 128UL));

    uint32_t proctl;
    uint32_t wml;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable SDHC clock. */
    CLOCK_EnableClock(s_sdhcClock[SDHC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset SDHC. */
    base->SYSCTL |= SDHC_SYSCTL_RSTA_MASK | SDHC_SYSCTL_RSTC_MASK | SDHC_SYSCTL_RSTD_MASK;

    proctl = base->PROCTL;
    wml    = base->WML;

    proctl &= ~(SDHC_PROCTL_D3CD_MASK | SDHC_PROCTL_EMODE_MASK | SDHC_PROCTL_DMAS_MASK);
    /* Set DAT3 as card detection pin */
    if (config->cardDetectDat3)
    {
        proctl |= SDHC_PROCTL_D3CD_MASK;
    }
    /* Endian mode and DMA mode */
    proctl |= (SDHC_PROCTL_EMODE(config->endianMode) | SDHC_PROCTL_DMAS(config->dmaMode));

    /* Watermark level */
    wml &= ~(SDHC_WML_RDWML_MASK | SDHC_WML_WRWML_MASK);
    wml |= (SDHC_WML_RDWML(config->readWatermarkLevel) | SDHC_WML_WRWML(config->writeWatermarkLevel));

    base->WML    = wml;
    base->PROCTL = proctl;

    /* Disable all clock auto gated off feature because of DAT0 line logic(card buffer full status) can't be updated
    correctly when clock auto gated off is enabled. */
    base->SYSCTL |= (SDHC_SYSCTL_PEREN_MASK | SDHC_SYSCTL_HCKEN_MASK | SDHC_SYSCTL_IPGEN_MASK);

    /* Enable interrupt status but doesn't enable interrupt signal, clear all the interrupt status */
    base->IRQSTATEN = kSDHC_AllInterruptFlags;
    base->IRQSIGEN  = 0U;
    base->IRQSTAT   = kSDHC_AllInterruptFlags;
}

/*!
 * brief Deinitializes the SDHC.
 *
 * param base SDHC peripheral base address.
 */
void SDHC_Deinit(SDHC_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable clock. */
    CLOCK_DisableClock(s_sdhcClock[SDHC_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Resets the SDHC.
 *
 * param base SDHC peripheral base address.
 * param mask The reset type mask(_sdhc_reset).
 * param timeout Timeout for reset.
 * retval true Reset successfully.
 * retval false Reset failed.
 */
bool SDHC_Reset(SDHC_Type *base, uint32_t mask, uint32_t timeout)
{
    base->SYSCTL |= (mask & (SDHC_SYSCTL_RSTA_MASK | SDHC_SYSCTL_RSTC_MASK | SDHC_SYSCTL_RSTD_MASK));
    /* Delay some time to wait reset success. */
    while (IS_SDHC_FLAG_SET(base->SYSCTL, mask))
    {
        if (timeout == 0UL)
        {
            break;
        }
        timeout--;
    }

    return (timeout == 0UL ? false : true);
}

/*!
 * brief Gets the capability information.
 *
 * param base SDHC peripheral base address.
 * param capability Structure to save capability information.
 */
void SDHC_GetCapability(SDHC_Type *base, sdhc_capability_t *capability)
{
    assert(capability != NULL);

    uint32_t htCapability;
    uint32_t hostVer;
    uint32_t maxBlockLength;

    hostVer      = base->HOSTVER;
    htCapability = base->HTCAPBLT;

    /* Get the capability of SDHC. */
    capability->specVersion    = ((hostVer & SDHC_HOSTVER_SVN_MASK) >> SDHC_HOSTVER_SVN_SHIFT);
    capability->vendorVersion  = ((hostVer & SDHC_HOSTVER_VVN_MASK) >> SDHC_HOSTVER_VVN_SHIFT);
    maxBlockLength             = ((htCapability & SDHC_HTCAPBLT_MBL_MASK) >> SDHC_HTCAPBLT_MBL_SHIFT);
    capability->maxBlockLength = (512UL << maxBlockLength);
    /* Other attributes not in HTCAPBLT register. */
    capability->maxBlockCount = SDHC_MAX_BLOCK_COUNT;
    capability->flags = (htCapability & ((uint32_t)kSDHC_SupportAdmaFlag | (uint32_t)kSDHC_SupportHighSpeedFlag |
                                         (uint32_t)kSDHC_SupportDmaFlag | (uint32_t)kSDHC_SupportSuspendResumeFlag |
                                         (uint32_t)kSDHC_SupportV330Flag));
#if defined FSL_FEATURE_SDHC_HAS_V300_SUPPORT && FSL_FEATURE_SDHC_HAS_V300_SUPPORT
    capability->flags |= (htCapability & (uint32_t)kSDHC_SupportV300Flag);
#endif
#if defined FSL_FEATURE_SDHC_HAS_V180_SUPPORT && FSL_FEATURE_SDHC_HAS_V180_SUPPORT
    capability->flags |= (htCapability & (uint32_t)kSDHC_SupportV180Flag);
#endif
    /* eSDHC on all kinetis boards will support 4/8 bit data bus width. */
    capability->flags |= ((uint32_t)kSDHC_Support4BitFlag | (uint32_t)kSDHC_Support8BitFlag);
}

/*!
 * brief Sets the SD bus clock frequency.
 *
 * param base SDHC peripheral base address.
 * param srcClock_Hz SDHC source clock frequency united in Hz.
 * param busClock_Hz SD bus clock frequency united in Hz.
 *
 * return The nearest frequency of busClock_Hz configured to SD bus.
 */
uint32_t SDHC_SetSdClock(SDHC_Type *base, uint32_t srcClock_Hz, uint32_t busClock_Hz)
{
    assert(srcClock_Hz != 0U);
    assert((busClock_Hz != 0U) && (busClock_Hz <= srcClock_Hz));

    uint32_t totalDiv         = 0U;
    uint32_t divisor          = 0U;
    uint32_t prescaler        = 0U;
    uint32_t sysctl           = 0U;
    uint32_t nearestFrequency = 0U;

    /* calucate total divisor first */
    totalDiv = srcClock_Hz / busClock_Hz;

    if (totalDiv > (SDHC_MAX_CLKFS * SDHC_MAX_DVS))
    {
        return 0UL;
    }

    if (totalDiv != 0U)
    {
        /* calucate the divisor (srcClock_Hz / divisor) <= busClock_Hz */
        if ((srcClock_Hz / totalDiv) > busClock_Hz)
        {
            totalDiv++;
        }

        /* divide the total divisor to div and prescaler */
        if (totalDiv > SDHC_MAX_DVS)
        {
            prescaler = totalDiv / SDHC_MAX_DVS;
            /* prescaler must be a value which equal 2^n and smaller than SDHC_MAX_CLKFS */
            while (((SDHC_MAX_CLKFS % prescaler) != 0U) || (prescaler == 1U))
            {
                prescaler++;
            }
            /* calucate the divisor */
            divisor = totalDiv / prescaler;
            /* fine tuning the divisor until divisor * prescaler >= totalDiv */
            while ((divisor * prescaler) < totalDiv)
            {
                divisor++;
            }

            nearestFrequency = srcClock_Hz / (divisor == 0U ? 1U : divisor) / prescaler;
        }
        else
        {
            divisor          = totalDiv;
            prescaler        = 0U;
            nearestFrequency = srcClock_Hz / divisor;
        }
    }
    /* in this condition , srcClock_Hz = busClock_Hz, */
    else
    {
        /* total divider = 1U */
        divisor          = 0U;
        prescaler        = 0U;
        nearestFrequency = srcClock_Hz;
    }

    /* calucate the value write to register */
    if (divisor != 0U)
    {
        SDHC_PREV_DVS(divisor);
    }
    /* calucate the value write to register */
    if (prescaler != 0U)
    {
        SDHC_PREV_CLKFS(prescaler);
    }

    /* Disable SD clock. It should be disabled before changing the SD clock frequency.*/
    base->SYSCTL &= ~SDHC_SYSCTL_SDCLKEN_MASK;

    /* Set the SD clock frequency divisor, SD clock frequency select, data timeout counter value. */
    sysctl = base->SYSCTL;
    sysctl &= ~(SDHC_SYSCTL_DVS_MASK | SDHC_SYSCTL_SDCLKFS_MASK | SDHC_SYSCTL_DTOCV_MASK);
    sysctl |= (SDHC_SYSCTL_DVS(divisor) | SDHC_SYSCTL_SDCLKFS(prescaler) | SDHC_SYSCTL_DTOCV(0xEU));
    base->SYSCTL = sysctl;

    /* Wait until the SD clock is stable. */
    while (!(IS_SDHC_FLAG_SET(base->PRSSTAT, SDHC_PRSSTAT_SDSTB_MASK)))
    {
    }
    /* Enable the SD clock. */
    base->SYSCTL |= SDHC_SYSCTL_SDCLKEN_MASK;

    return nearestFrequency;
}

/*!
 * brief Sends 80 clocks to the card to set it to the active state.
 *
 * This function must be called each time the card is inserted to ensure that the card can receive the command
 * correctly.
 *
 * param base SDHC peripheral base address.
 * param timeout Timeout to initialize card.
 * retval true Set card active successfully.
 * retval false Set card active failed.
 */
bool SDHC_SetCardActive(SDHC_Type *base, uint32_t timeout)
{
    base->SYSCTL |= SDHC_SYSCTL_INITA_MASK;
    /* Delay some time to wait card become active state. */
    while (IS_SDHC_FLAG_SET(base->SYSCTL, SDHC_SYSCTL_INITA_MASK))
    {
        if (timeout == 0UL)
        {
            break;
        }
        timeout--;
    }

    return (timeout == 0UL ? false : true);
}

/*!
 * brief Sets the card transfer-related configuration.
 *
 * This function fills the card transfer-related command argument/transfer flag/data size. The command and data are sent
 by
 * SDHC after calling this function.
 *
 * Example:
   code
   sdhc_transfer_config_t transferConfig;
   transferConfig.dataBlockSize = 512U;
   transferConfig.dataBlockCount = 2U;
   transferConfig.commandArgument = 0x01AAU;
   transferConfig.commandIndex = 8U;
   transferConfig.flags |= (kSDHC_EnableDmaFlag | kSDHC_EnableAutoCommand12Flag | kSDHC_MultipleBlockFlag);
   SDHC_SetTransferConfig(SDHC, &transferConfig);
   endcode
 *
 * param base SDHC peripheral base address.
 * param config Command configuration structure.
 */
void SDHC_SetTransferConfig(SDHC_Type *base, const sdhc_transfer_config_t *config)
{
    assert(config != NULL);
    assert(config->dataBlockSize <= (SDHC_BLKATTR_BLKSIZE_MASK >> SDHC_BLKATTR_BLKSIZE_SHIFT));
    assert(config->dataBlockCount <= (SDHC_BLKATTR_BLKCNT_MASK >> SDHC_BLKATTR_BLKCNT_SHIFT));

    base->BLKATTR = ((base->BLKATTR & ~(SDHC_BLKATTR_BLKSIZE_MASK | SDHC_BLKATTR_BLKCNT_MASK)) |
                     (SDHC_BLKATTR_BLKSIZE(config->dataBlockSize) | SDHC_BLKATTR_BLKCNT(config->dataBlockCount)));
    base->CMDARG  = config->commandArgument;
    base->XFERTYP = (((config->commandIndex << SDHC_XFERTYP_CMDINX_SHIFT) & SDHC_XFERTYP_CMDINX_MASK) |
                     (config->flags & (SDHC_XFERTYP_DMAEN_MASK | SDHC_XFERTYP_MSBSEL_MASK | SDHC_XFERTYP_DPSEL_MASK |
                                       SDHC_XFERTYP_CMDTYP_MASK | SDHC_XFERTYP_BCEN_MASK | SDHC_XFERTYP_CICEN_MASK |
                                       SDHC_XFERTYP_CCCEN_MASK | SDHC_XFERTYP_RSPTYP_MASK | SDHC_XFERTYP_DTDSEL_MASK |
                                       SDHC_XFERTYP_AC12EN_MASK)));
}

/*!
 * brief Enables or disables the SDIO card control.
 *
 * param base SDHC peripheral base address.
 * param mask SDIO card control flags mask(_sdhc_sdio_control_flag).
 * param enable True to enable, false to disable.
 */
void SDHC_EnableSdioControl(SDHC_Type *base, uint32_t mask, bool enable)
{
    uint32_t proctl = base->PROCTL;
    uint32_t vendor = base->VENDOR;

    if (enable)
    {
        if (IS_SDHC_FLAG_SET(mask, kSDHC_StopAtBlockGapFlag))
        {
            proctl |= SDHC_PROCTL_SABGREQ_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_ReadWaitControlFlag))
        {
            proctl |= SDHC_PROCTL_RWCTL_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_InterruptAtBlockGapFlag))
        {
            proctl |= SDHC_PROCTL_IABG_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_ExactBlockNumberReadFlag))
        {
            vendor |= SDHC_VENDOR_EXBLKNU_MASK;
        }
    }
    else
    {
        if (IS_SDHC_FLAG_SET(mask, kSDHC_StopAtBlockGapFlag))
        {
            proctl &= ~SDHC_PROCTL_SABGREQ_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_ReadWaitControlFlag))
        {
            proctl &= ~SDHC_PROCTL_RWCTL_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_InterruptAtBlockGapFlag))
        {
            proctl &= ~SDHC_PROCTL_IABG_MASK;
        }
        if (IS_SDHC_FLAG_SET(mask, kSDHC_ExactBlockNumberReadFlag))
        {
            vendor &= ~SDHC_VENDOR_EXBLKNU_MASK;
        }
    }

    base->PROCTL = proctl;
    base->VENDOR = vendor;
}

/*!
 * brief Configures the MMC boot feature.
 *
 * Example:
   code
   sdhc_boot_config_t config;
   config.ackTimeoutCount = 4;
   config.bootMode = kSDHC_BootModeNormal;
   config.blockCount = 5;
   config.enableBootAck = true;
   config.enableBoot = true;
   config.enableAutoStopAtBlockGap = true;
   SDHC_SetMmcBootConfig(SDHC, &config);
   endcode
 *
 * param base SDHC peripheral base address.
 * param config The MMC boot configuration information.
 */
void SDHC_SetMmcBootConfig(SDHC_Type *base, const sdhc_boot_config_t *config)
{
    assert(config != NULL);
    assert(config->ackTimeoutCount <= (SDHC_MMCBOOT_DTOCVACK_MASK >> SDHC_MMCBOOT_DTOCVACK_SHIFT));
    assert(config->blockCount <= (SDHC_MMCBOOT_BOOTBLKCNT_MASK >> SDHC_MMCBOOT_BOOTBLKCNT_SHIFT));

    uint32_t mmcboot = 0U;

    mmcboot = (SDHC_MMCBOOT_DTOCVACK(config->ackTimeoutCount) | SDHC_MMCBOOT_BOOTMODE(config->bootMode) |
               SDHC_MMCBOOT_BOOTBLKCNT(config->blockCount));
    if (config->enableBootAck)
    {
        mmcboot |= SDHC_MMCBOOT_BOOTACK_MASK;
    }
    if (config->enableBoot)
    {
        mmcboot |= SDHC_MMCBOOT_BOOTEN_MASK;
    }
    if (config->enableAutoStopAtBlockGap)
    {
        mmcboot |= SDHC_MMCBOOT_AUTOSABGEN_MASK;
    }
    base->MMCBOOT = mmcboot;
}

/*!
 * brief Sets the ADMA descriptor table configuration.
 *
 * param base SDHC peripheral base address.
 * param dmaMode DMA mode.
 * param table ADMA table address.
 * param tableWords ADMA table buffer length united as Words.
 * param data Data buffer address.
 * param dataBytes Data length united as bytes.
 * retval kStatus_OutOfRange ADMA descriptor table length isn't enough to describe data.
 * retval kStatus_Success Operate successfully.
 */
status_t SDHC_SetAdmaTableConfig(SDHC_Type *base,
                                 sdhc_dma_mode_t dmaMode,
                                 uint32_t *table,
                                 uint32_t tableWords,
                                 const uint32_t *data,
                                 uint32_t dataBytes)
{
    status_t error               = kStatus_Success;
    const uint32_t *startAddress = data;
    uint32_t entries;
    uint32_t i;
#if defined FSL_SDHC_ENABLE_ADMA1
    sdhc_adma1_descriptor_t *adma1EntryAddress;
#endif
    sdhc_adma2_descriptor_t *adma2EntryAddress;

    if ((((table == NULL) || (tableWords == 0UL)) &&
         ((dmaMode == kSDHC_DmaModeAdma1) || (dmaMode == kSDHC_DmaModeAdma2))) ||
        (data == NULL) || (dataBytes == 0UL)
#if !defined FSL_SDHC_ENABLE_ADMA1
        || (dmaMode == kSDHC_DmaModeAdma1)
#endif
    )
    {
        error = kStatus_InvalidArgument;
    }
    else if (((dmaMode == kSDHC_DmaModeAdma2) && (((uint32_t)startAddress % SDHC_ADMA2_LENGTH_ALIGN) != 0UL))
#if defined FSL_SDHC_ENABLE_ADMA1
             || ((dmaMode == kSDHC_DmaModeAdma1) && (((uint32_t)startAddress % SDHC_ADMA1_LENGTH_ALIGN) != 0UL))
#endif
    )
    {
        error = kStatus_SDHC_DMADataBufferAddrNotAlign;
    }
    else
    {
#if defined FSL_SDHC_ENABLE_ADMA1
        if (dmaMode == kSDHC_DmaModeAdma1)
        {
            /*
             * Add non aligned access support ,user need make sure your buffer size is big
             * enough to hold the data,in other words,user need make sure the buffer size
             * is 4 byte aligned
             */
            if (dataBytes % sizeof(uint32_t) != 0U)
            {
                dataBytes +=
                    sizeof(uint32_t) - (dataBytes % sizeof(uint32_t)); /* make the data length as word-aligned */
            }

            /* Check if ADMA descriptor's number is enough. */
            entries = ((dataBytes / SDHC_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) + 1U);
            /* ADMA1 needs two descriptors to finish a transfer */
            entries <<= 1U;
            if (entries > ((tableWords * sizeof(uint32_t)) / sizeof(sdhc_adma1_descriptor_t)))
            {
                error = kStatus_OutOfRange;
            }
            else
            {
                adma1EntryAddress = (sdhc_adma1_descriptor_t *)(uint32_t)(table);
                for (i = 0U; i < entries; i += 2U)
                {
                    /* Each descriptor for ADMA1 is 32-bit in length */
                    if ((dataBytes - ((uint32_t)startAddress - (uint32_t)data)) <=
                        SDHC_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY)
                    {
                        /* The last piece of data, setting end flag in descriptor */
                        adma1EntryAddress[i] = ((uint32_t)(dataBytes - ((uint32_t)startAddress - (uint32_t)data))
                                                << SDHC_ADMA1_DESCRIPTOR_LENGTH_SHIFT);
                        adma1EntryAddress[i] |= (uint32_t)kSDHC_Adma1DescriptorTypeSetLength;
                        adma1EntryAddress[i + 1U] = (uint32_t)(startAddress);
                        adma1EntryAddress[i + 1U] |=
                            ((uint32_t)kSDHC_Adma1DescriptorTypeTransfer | (uint32_t)kSDHC_Adma1DescriptorEndFlag);
                    }
                    else
                    {
                        adma1EntryAddress[i] = ((uint32_t)SDHC_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY
                                                << SDHC_ADMA1_DESCRIPTOR_LENGTH_SHIFT);
                        adma1EntryAddress[i] |= (uint32_t)kSDHC_Adma1DescriptorTypeSetLength;
                        adma1EntryAddress[i + 1U] = ((uint32_t)(startAddress));
                        adma1EntryAddress[i + 1U] |= (uint32_t)kSDHC_Adma1DescriptorTypeTransfer;
                        startAddress += SDHC_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY / sizeof(uint32_t);
                    }
                }

                /* When use ADMA, disable simple DMA */
                base->DSADDR  = 0U;
                base->ADSADDR = (uint32_t)table;
            }
        }
        else
#endif /* FSL_SDHC_ENABLE_ADMA1 */
            if (dmaMode == kSDHC_DmaModeAdma2)
        {
            /*
             * Add non aligned access support ,user need make sure your buffer size is big
             * enough to hold the data,in other words,user need make sure the buffer size
             * is 4 byte aligned
             */
            if (dataBytes % sizeof(uint32_t) != 0U)
            {
                dataBytes +=
                    sizeof(uint32_t) - (dataBytes % sizeof(uint32_t)); /* make the data length as word-aligned */
            }

            /* Check if ADMA descriptor's number is enough. */
            entries = ((dataBytes / SDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY) + 1U);
            if (entries > ((tableWords * sizeof(uint32_t)) / sizeof(sdhc_adma2_descriptor_t)))
            {
                error = kStatus_OutOfRange;
            }
            else
            {
                adma2EntryAddress = (sdhc_adma2_descriptor_t *)(uint32_t)(table);
                for (i = 0U; i < entries; i++)
                {
                    /* Each descriptor for ADMA2 is 64-bit in length */
                    if ((dataBytes - ((uint32_t)startAddress - (uint32_t)data)) <=
                        SDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY)
                    {
                        /* The last piece of data, setting end flag in descriptor */
                        adma2EntryAddress[i].address   = startAddress;
                        adma2EntryAddress[i].attribute = ((dataBytes - ((uint32_t)startAddress - (uint32_t)data))
                                                          << SDHC_ADMA2_DESCRIPTOR_LENGTH_SHIFT);
                        adma2EntryAddress[i].attribute |=
                            ((uint32_t)kSDHC_Adma2DescriptorTypeTransfer | (uint32_t)kSDHC_Adma2DescriptorEndFlag);
                    }
                    else
                    {
                        adma2EntryAddress[i].address = startAddress;
                        adma2EntryAddress[i].attribute =
                            (((SDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY / sizeof(uint32_t)) * sizeof(uint32_t))
                             << SDHC_ADMA2_DESCRIPTOR_LENGTH_SHIFT);
                        adma2EntryAddress[i].attribute |= (uint32_t)kSDHC_Adma2DescriptorTypeTransfer;
                        startAddress += (SDHC_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY / sizeof(uint32_t));
                    }
                }

                /* When use ADMA, disable simple DMA */
                base->DSADDR  = 0U;
                base->ADSADDR = (uint32_t)table;
            }
        }
        else
        {
            /* Intentional empty */
        }
    }

    return error;
}

/*!
 * brief Transfers the command/data using a blocking method.
 *
 * This function waits until the command response/data is received or the SDHC encounters an error by polling the status
 * flag.
 * This function support non word align data addr transfer support, if data buffer addr is not align in DMA mode,
 * the API will continue finish the transfer by polling IO directly
 * The application must not call this API in multiple threads at the same time. Because of that this API doesn't support
 * the re-entry mechanism.
 *
 * note There is no need to call the API 'SDHC_TransferCreateHandle' when calling this API.
 *
 * param base SDHC peripheral base address.
 * param admaTable ADMA table address, can't be null if transfer way is ADMA1/ADMA2.
 * param admaTableWords ADMA table length united as words, can't be 0 if transfer way is ADMA1/ADMA2.
 * param transfer Transfer content.
 * retval kStatus_InvalidArgument Argument is invalid.
 * retval kStatus_SDHC_PrepareAdmaDescriptorFailed Prepare ADMA descriptor failed.
 * retval kStatus_SDHC_SendCommandFailed Send command failed.
 * retval kStatus_SDHC_TransferDataFailed Transfer data failed.
 * retval kStatus_Success Operate successfully.
 */
status_t SDHC_TransferBlocking(SDHC_Type *base, uint32_t *admaTable, uint32_t admaTableWords, sdhc_transfer_t *transfer)
{
    assert(transfer != NULL);

    status_t error = kStatus_Success;
    sdhc_dma_mode_t dmaMode =
        (sdhc_dma_mode_t)(uint8_t)((base->PROCTL & SDHC_PROCTL_DMAS_MASK) >> SDHC_PROCTL_DMAS_SHIFT);
    sdhc_command_t *command = transfer->command;
    sdhc_data_t *data       = transfer->data;

    /* make sure the cmd/block count is valid */
    if ((command == NULL) || ((data != NULL) && (data->blockCount > SDHC_MAX_BLOCK_COUNT)))
    {
        return kStatus_InvalidArgument;
    }

    /* Wait until command/data bus out of busy status. */
    while (IS_SDHC_FLAG_SET(SDHC_GetPresentStatusFlags(base), kSDHC_CommandInhibitFlag))
    {
    }
    while ((data != NULL) && (IS_SDHC_FLAG_SET(SDHC_GetPresentStatusFlags(base), kSDHC_DataInhibitFlag)))
    {
    }

    /* Update ADMA descriptor table according to different DMA mode(no DMA, ADMA1, ADMA2).*/
    if ((data != NULL) && (NULL != admaTable))
    {
        error = SDHC_SetAdmaTableConfig(base, (sdhc_dma_mode_t)dmaMode, admaTable, admaTableWords,
                                        (data->rxData != NULL ? data->rxData : data->txData),
                                        (data->blockCount * data->blockSize));
        /* in this situation , we disable the DMA instead of polling transfer mode */
        if (error != kStatus_Success)
        {
            dmaMode = (sdhc_dma_mode_t)kSDHC_DmaModeNo;
        }
    }

    if (data != NULL)
    {
        SDHC_ClearInterruptStatusFlags(
            base,
            (uint32_t)(dmaMode == kSDHC_DmaModeNo ? kSDHC_DataFlag : kSDHC_DataDMAFlag) | (uint32_t)kSDHC_CommandFlag);
    }
    else
    {
        SDHC_ClearInterruptStatusFlags(base, kSDHC_CommandFlag);
    }

    /* Send command and receive data. */
    SDHC_StartTransfer(base, command, data, (sdhc_dma_mode_t)dmaMode);

    error = SDHC_SendCommandBlocking(base, command);
    if (kStatus_Success != error)
    {
        return error;
    }

    if (data != NULL)
    {
        error = SDHC_TransferDataBlocking((sdhc_dma_mode_t)dmaMode, base, data);
        if (kStatus_Success != error)
        {
            return error;
        }
    }

    return kStatus_Success;
}

/*!
 * brief Creates the SDHC handle.
 *
 * param base SDHC peripheral base address.
 * param handle SDHC handle pointer.
 * param callback Structure pointer to contain all callback functions.
 * param userData Callback function parameter.
 */
void SDHC_TransferCreateHandle(SDHC_Type *base,
                               sdhc_handle_t *handle,
                               const sdhc_transfer_callback_t *callback,
                               void *userData)
{
    assert(handle != NULL);
    assert(callback != NULL);

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set the callback. */
    handle->callback.CardInserted     = callback->CardInserted;
    handle->callback.CardRemoved      = callback->CardRemoved;
    handle->callback.SdioInterrupt    = callback->SdioInterrupt;
    handle->callback.SdioBlockGap     = callback->SdioBlockGap;
    handle->callback.TransferComplete = callback->TransferComplete;
    handle->userData                  = userData;

    /* Save the handle in global variables to support the double weak mechanism. */
    s_sdhcHandle[SDHC_GetInstance(base)] = handle;

    /* save IRQ handler */
    s_sdhcIsr = SDHC_TransferHandleIRQ;

    (void)EnableIRQ(s_sdhcIRQ[SDHC_GetInstance(base)]);
}

/*!
 * brief Transfers the command/data using an interrupt and an asynchronous method.
 *
 * This function sends a command and data and returns immediately. It doesn't wait the transfer complete or encounter an
 * error.
 * This function support non word align data addr transfer support, if data buffer addr is not align in DMA mode,
 * the API will continue finish the transfer by polling IO directly
 * The application must not call this API in multiple threads at the same time. Because of that this API doesn't support
 * the re-entry mechanism.
 *
 * note Call the API 'SDHC_TransferCreateHandle' when calling this API.
 *
 * param base SDHC peripheral base address.
 * param handle SDHC handle.
 * param admaTable ADMA table address, can't be null if transfer way is ADMA1/ADMA2.
 * param admaTableWords ADMA table length united as words, can't be 0 if transfer way is ADMA1/ADMA2.
 * param transfer Transfer content.
 * retval kStatus_InvalidArgument Argument is invalid.
 * retval kStatus_SDHC_BusyTransferring Busy transferring.
 * retval kStatus_SDHC_PrepareAdmaDescriptorFailed Prepare ADMA descriptor failed.
 * retval kStatus_Success Operate successfully.
 */
status_t SDHC_TransferNonBlocking(
    SDHC_Type *base, sdhc_handle_t *handle, uint32_t *admaTable, uint32_t admaTableWords, sdhc_transfer_t *transfer)
{
    assert(transfer != NULL);

    sdhc_dma_mode_t dmaMode =
        (sdhc_dma_mode_t)(uint8_t)((base->PROCTL & SDHC_PROCTL_DMAS_MASK) >> SDHC_PROCTL_DMAS_SHIFT);
    status_t error          = kStatus_Success;
    sdhc_command_t *command = transfer->command;
    sdhc_data_t *data       = transfer->data;

    /* make sure cmd/block count is valid */
    if ((command == NULL) || ((data != NULL) && (data->blockCount > SDHC_MAX_BLOCK_COUNT)))
    {
        return kStatus_InvalidArgument;
    }

    /* Wait until command/data bus out of busy status. */
    if ((IS_SDHC_FLAG_SET(SDHC_GetPresentStatusFlags(base), kSDHC_CommandInhibitFlag)) ||
        ((data != NULL) && (IS_SDHC_FLAG_SET(SDHC_GetPresentStatusFlags(base), kSDHC_DataInhibitFlag))))
    {
        return kStatus_SDHC_BusyTransferring;
    }

    /* Update ADMA descriptor table according to different DMA mode(no DMA, ADMA1, ADMA2).*/
    if ((data != NULL) && (NULL != admaTable))
    {
        error = SDHC_SetAdmaTableConfig(base, dmaMode, admaTable, admaTableWords,
                                        (data->rxData != NULL ? data->rxData : data->txData),
                                        (data->blockCount * data->blockSize));
        /* in this situation , we disable the DMA instead of polling transfer mode */
        if (error != kStatus_Success)
        {
            /* change to polling mode */
            dmaMode = kSDHC_DmaModeNo;
        }
    }

    /* Save command and data into handle before transferring. */
    handle->command = command;
    handle->data    = data;
    /* transferredWords will only be updated in ISR when transfer way is DATAPORT. */
    handle->transferredWords = 0U;

    /* enable interrupt per transfer request */
    if (handle->data != NULL)
    {
        SDHC_ClearInterruptStatusFlags(
            base,
            (uint32_t)(dmaMode == kSDHC_DmaModeNo ? kSDHC_DataFlag : kSDHC_DataDMAFlag) | (uint32_t)kSDHC_CommandFlag);
        SDHC_EnableInterruptSignal(base, (uint32_t)(dmaMode == kSDHC_DmaModeNo ? kSDHC_DataFlag : kSDHC_DataDMAFlag) |
                                             (uint32_t)kSDHC_CommandFlag);
    }
    else
    {
        SDHC_ClearInterruptStatusFlags(base, kSDHC_CommandFlag);
        SDHC_EnableInterruptSignal(base, kSDHC_CommandFlag);
    }

    SDHC_StartTransfer(base, command, data, dmaMode);

    return kStatus_Success;
}

/*!
 * brief IRQ handler for the SDHC.
 *
 * This function deals with the IRQs on the given host controller.
 *
 * param base SDHC peripheral base address.
 * param handle SDHC handle.
 */
void SDHC_TransferHandleIRQ(SDHC_Type *base, sdhc_handle_t *handle)
{
    assert(handle != NULL);

    uint32_t interruptFlags;

    interruptFlags = SDHC_GetEnabledInterruptStatusFlags(base);

    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_CardDetectFlag))
    {
        SDHC_TransferHandleCardDetect(base, handle, interruptFlags);
    }
    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_CommandFlag))
    {
        SDHC_TransferHandleCommand(base, handle, interruptFlags);
    }
    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_DataFlag))
    {
        SDHC_TransferHandleData(base, handle, interruptFlags);
    }
    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_CardInterruptFlag))
    {
        SDHC_TransferHandleSdioInterrupt(base, handle);
    }
    if (IS_SDHC_FLAG_SET(interruptFlags, kSDHC_BlockGapEventFlag))
    {
        SDHC_TransferHandleSdioBlockGap(base, handle);
    }

    SDHC_ClearInterruptStatusFlags(base, interruptFlags);
}

#if defined(SDHC)
void SDHC_DriverIRQHandler(void);
void SDHC_DriverIRQHandler(void)
{
    assert(s_sdhcHandle[0] != NULL);

    s_sdhcIsr(SDHC, s_sdhcHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
