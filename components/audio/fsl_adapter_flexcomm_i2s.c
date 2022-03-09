/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#include "fsl_dma.h"
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
#include "fsl_adapter_audio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief hal i2s state structure. */
typedef struct _hal_audio_state
{
    hal_audio_transfer_callback_t callback;
    void *callbackParam;
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    i2s_dma_handle_t xferDmaHandle;
    dma_handle_t dmaHandle;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
    uint8_t dmaInstance;
    uint8_t instance;
    uint8_t occupied;
} hal_audio_state_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to i2s bases for each instance. */
static I2S_Type *const s_i2sBases[] = I2S_BASE_PTRS;
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
/*! @brief Resource for each i2s instance. */
static uint8_t s_dmaOccupied[ARRAY_SIZE((DMA_Type *[])DMA_BASE_PTRS)];
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

/*******************************************************************************
 * Code
 ******************************************************************************/

static hal_audio_status_t HAL_AudioGetStatus(status_t status)
{
    hal_audio_status_t returnStatus;
    switch (status)
    {
        case kStatus_Success:
            returnStatus = kStatus_HAL_AudioSuccess;
            break;

        case kStatus_I2S_Busy:
            returnStatus = kStatus_HAL_AudioBusy;
            break;

        case kStatus_I2S_BufferComplete:
        case kStatus_I2S_Done:
        case kStatus_NoTransferInProgress:
            returnStatus = kStatus_HAL_AudioIdle;
            break;

        default:
            returnStatus = kStatus_HAL_AudioError;
            break;
    }
    return returnStatus;
}

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
static void HAL_AudioCallbackDMA(I2S_Type *base, i2s_dma_handle_t *handle, status_t status, void *userData)
{
    hal_audio_state_t *audioHandle;

    assert(userData);

    audioHandle = (hal_audio_state_t *)userData;

    if (NULL != audioHandle->callback)
    {
        audioHandle->callback(audioHandle, HAL_AudioGetStatus(status), audioHandle->callbackParam);
    }
}
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

static hal_audio_status_t HAL_AudioCommonInit(hal_audio_handle_t handle,
                                              const hal_audio_config_t *config,
                                              bool direction)
{
    hal_audio_state_t *audioHandle;
    i2s_config_t i2sConfig;
    hal_audio_dma_config_t *dmaConfig;
    DMA_Type *dmaBases[] = DMA_BASE_PTRS;
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    IRQn_Type dmaIrqNumber[] = DMA_IRQS;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
    uint8_t channelNum;

    assert(handle);
    assert(config);
    assert(config->dmaConfig);
    /* If asserted, please check if the value of I2S_NUM_BUFFERS defined in the fsl_i2s.h is modified.
       If modified, please modify the value of HAL_AUDIO_QUEUE_SIZE defined in the fsl_adapter_audio.h to be the same as
       I2S_NUM_BUFFERS. */
    assert(HAL_AUDIO_HANDLE_SIZE >= sizeof(hal_audio_state_t));
    assert(config->instance < ARRAY_SIZE(s_i2sBases));
    assert(config->dmaConfig->instance < ARRAY_SIZE(dmaBases));

    dmaConfig   = (hal_audio_dma_config_t *)config->dmaConfig;
    audioHandle = (hal_audio_state_t *)handle;

    if (audioHandle->occupied != 0U)
    {
        return kStatus_HAL_AudioSuccess;
    }

    audioHandle->instance    = config->instance;
    audioHandle->dmaInstance = dmaConfig->instance;
    audioHandle->occupied    = 1;
    channelNum               = (uint8_t)config->lineChannels;

    if (direction)
    {
        I2S_TxGetDefaultConfig(&i2sConfig);
    }
    else
    {
        I2S_RxGetDefaultConfig(&i2sConfig);
    }

    if (channelNum == (uint8_t)kHAL_AudioMono)
    {
        i2sConfig.oneChannel = true;
        channelNum           = 1;
    }
    else if (channelNum == (uint8_t)kHAL_AudioMonoRight)
    {
        i2sConfig.oneChannel = true;
        i2sConfig.position   = config->bitWidth;
        channelNum           = 2;
    }
    else if (channelNum == (uint8_t)kHAL_AudioMonoLeft)
    {
        i2sConfig.oneChannel = true;
        channelNum           = 2;
    }
    else
    {
        /* no action */
    }

    i2sConfig.divider =
        (uint16_t)(config->srcClock_Hz / (uint32_t)config->sampleRate_Hz / (uint32_t)config->bitWidth / channelNum);
    i2sConfig.dataLength = config->bitWidth;
    if (0U == config->frameLength)
    {
        i2sConfig.frameLength = (uint16_t)config->bitWidth * channelNum;
    }
    else
    {
        i2sConfig.frameLength = config->frameLength;
    }

    if ((uint8_t)kHAL_AudioSampleOnFallingEdge == (uint8_t)config->bclkPolarity)
    {
        i2sConfig.sckPol = true;
    }
    else
    {
        i2sConfig.sckPol = false;
    }

    switch (config->msaterSlave)
    {
        case kHAL_AudioMaster:
            i2sConfig.masterSlave = kI2S_MasterSlaveNormalMaster;
            break;

        case kHAL_AudioSlave:
            i2sConfig.masterSlave = kI2S_MasterSlaveNormalSlave;
            i2sConfig.divider     = 1; /* As slave, divider need to set to 1 according to the spec. */
            break;

        case kHAL_AudioBclkMasterFrameSyncSlave:
            i2sConfig.masterSlave = kI2S_MasterSlaveWsSyncMaster;
            break;

        case kHAL_AudioBclkSlaveFrameSyncMaster:
            i2sConfig.masterSlave = kI2S_MasterSlaveExtSckMaster;
            i2sConfig.divider     = 1; /* As slave, divider need to set to 1 according to the spec. */
            break;

        default:
            assert(false);
            break;
    }

    switch (config->dataFormat)
    {
        case kHAL_AudioDataFormatI2sClassic:
            i2sConfig.mode  = kI2S_ModeI2sClassic;
            i2sConfig.wsPol = false;

            if ((uint8_t)config->lineChannels == (uint8_t)kHAL_AudioMonoRight)
            {
                i2sConfig.position += 0x100U; /* Special case for i2s classic mode */
            }
            break;

        case kHAL_AudioDataFormatLeftJustified:
        case kHAL_AudioDataFormatRightJustified:
            i2sConfig.mode  = kI2S_ModeDspWs50;
            i2sConfig.wsPol = true;
            break;

        case kHAL_AudioDataFormatDspModeA:
        case kHAL_AudioDataFormatDspModeB:
            i2sConfig.wsPol = true;

            if ((uint8_t)config->dataFormat == (uint8_t)kHAL_AudioDataFormatDspModeA)
            {
                i2sConfig.position += 1U;
            }

            if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthOneBitClk)
            {
                i2sConfig.mode = kI2S_ModeDspWsShort;
            }
            else if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthPerWordWidth)
            {
                i2sConfig.mode = kI2S_ModeDspWsLong;
            }
            else
            {
                i2sConfig.mode = kI2S_ModeDspWs50;
            }
            break;

        default:
            assert(false);
            break;
    }

    if (direction)
    {
        I2S_TxInit(s_i2sBases[audioHandle->instance], &i2sConfig);
    }
    else
    {
        I2S_RxInit(s_i2sBases[audioHandle->instance], &i2sConfig);
    }

    if (channelNum > (uint8_t)kHAL_AudioStereo)
    {
#if (defined(FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL) && FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL)
        bool oneChannel = (channelNum % 2U != 0U) ? true : false;

        if (channelNum <= (uint8_t)kHAL_AudioStereo4Channel)
        {
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel1, oneChannel,
                                       (uint32_t)config->bitWidth * 2U + i2sConfig.position);
        }
        else if (channelNum <= (uint8_t)kHAL_AudioStereo6Channel)
        {
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel1, false,
                                       (uint32_t)config->bitWidth * 2U + i2sConfig.position);
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel2, oneChannel,
                                       (uint32_t)config->bitWidth * 4U + i2sConfig.position);
        }
        else if (channelNum <= (uint8_t)kHAL_AudioStereo8Channel)
        {
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel1, false,
                                       (uint32_t)config->bitWidth * 2U + i2sConfig.position);
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel2, false,
                                       (uint32_t)config->bitWidth * 4U + i2sConfig.position);
            I2S_EnableSecondaryChannel(s_i2sBases[audioHandle->instance], kI2S_SecondaryChannel3, oneChannel,
                                       (uint32_t)config->bitWidth * 6U + i2sConfig.position);
        }
        else

        {
            assert(false);
        }
#else
        assert(false);
#endif
    }

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    if (s_dmaOccupied[dmaConfig->instance] == 0U)
    {
        DMA_Init(dmaBases[dmaConfig->instance]);
    }
    s_dmaOccupied[dmaConfig->instance]++;
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    DMA_EnableChannel(dmaBases[dmaConfig->instance], dmaConfig->channel);

    if ((uint8_t)kHAL_AudioDmaChannelPriorityDefault != (uint8_t)dmaConfig->priority)
    {
        assert((dma_priority_t)dmaConfig->priority <= kDMA_ChannelPriority7);

        DMA_SetChannelPriority(dmaBases[dmaConfig->instance], dmaConfig->channel, (dma_priority_t)dmaConfig->priority);
    }

    NVIC_SetPriority((IRQn_Type)dmaIrqNumber[dmaConfig->instance], HAL_AUDIO_ISR_PRIORITY);
    DMA_CreateHandle(&audioHandle->dmaHandle, dmaBases[dmaConfig->instance], dmaConfig->channel);

    if (direction)
    {
        I2S_TxTransferCreateHandleDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                      &audioHandle->dmaHandle, HAL_AudioCallbackDMA, audioHandle);
    }
    else
    {
        I2S_RxTransferCreateHandleDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                      &audioHandle->dmaHandle, HAL_AudioCallbackDMA, audioHandle);
    }
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

    return kStatus_HAL_AudioSuccess;
}

static hal_audio_status_t HAL_AudioCommonDeinit(hal_audio_handle_t handle, bool direction)
{
    hal_audio_state_t *audioHandle;
#if !(defined(FSL_FEATURE_FLEXCOMM_HAS_NO_RESET) && FSL_FEATURE_FLEXCOMM_HAS_NO_RESET)
    reset_ip_name_t flexcommResets[] = FLEXCOMM_RSTS;
#endif
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    DMA_Type *dmaBases[] = DMA_BASE_PTRS;
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    if (audioHandle->occupied == 0U)
    {
        return kStatus_HAL_AudioSuccess;
    }
    audioHandle->occupied = 0;

#if !(defined(FSL_FEATURE_FLEXCOMM_HAS_NO_RESET) && FSL_FEATURE_FLEXCOMM_HAS_NO_RESET)
    /* Reset the FLEXCOMM module */
    RESET_PeripheralReset(flexcommResets[audioHandle->instance]);
#endif

    /* if (direction)
    {
        HAL_AudioTransferAbortSend(handle);
    }
    else
    {
        HAL_AudioTransferAbortReceive(handle);
    } */

    I2S_Deinit(s_i2sBases[audioHandle->instance]);

#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    if (s_dmaOccupied[audioHandle->dmaInstance] != 0U)
    {
        s_dmaOccupied[audioHandle->dmaInstance]--;

        if (s_dmaOccupied[audioHandle->dmaInstance] == 0U)
        {
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
            DMA_Deinit(dmaBases[audioHandle->dmaInstance]);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
        }
    }
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    return kStatus_HAL_AudioSuccess;
}

hal_audio_status_t HAL_AudioTxInit(hal_audio_handle_t handle, const hal_audio_config_t *config)
{
    return HAL_AudioCommonInit(handle, config, true);
}

hal_audio_status_t HAL_AudioRxInit(hal_audio_handle_t handle, const hal_audio_config_t *config)
{
    return HAL_AudioCommonInit(handle, config, false);
}

hal_audio_status_t HAL_AudioTxDeinit(hal_audio_handle_t handle)
{
    return HAL_AudioCommonDeinit(handle, true);
}

hal_audio_status_t HAL_AudioRxDeinit(hal_audio_handle_t handle)
{
    return HAL_AudioCommonDeinit(handle, false);
}

hal_audio_status_t HAL_AudioTxInstallCallback(hal_audio_handle_t handle,
                                              hal_audio_transfer_callback_t callback,
                                              void *callbackParam)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    audioHandle->callback      = callback;
    audioHandle->callbackParam = callbackParam;

    return kStatus_HAL_AudioSuccess;
}

hal_audio_status_t HAL_AudioRxInstallCallback(hal_audio_handle_t handle,
                                              hal_audio_transfer_callback_t callback,
                                              void *callbackParam)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    audioHandle->callback      = callback;
    audioHandle->callbackParam = callbackParam;

    return kStatus_HAL_AudioSuccess;
}

hal_audio_status_t HAL_AudioTransferSendNonBlocking(hal_audio_handle_t handle, hal_audio_transfer_t *xfer)
{
    i2s_transfer_t transfer;
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    transfer.data     = (uint8_t *)xfer->data;
    transfer.dataSize = xfer->dataSize;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        I2S_TxTransferSendDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, transfer));
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
}

hal_audio_status_t HAL_AudioTransferReceiveNonBlocking(hal_audio_handle_t handle, hal_audio_transfer_t *xfer)
{
    i2s_transfer_t transfer;
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    transfer.data     = (uint8_t *)xfer->data;
    transfer.dataSize = xfer->dataSize;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        I2S_RxTransferReceiveDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, transfer));
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
}

hal_audio_status_t HAL_AudioTransferGetSendCount(hal_audio_handle_t handle, size_t *count)
{
    assert(handle);

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    *count = 0;
    return kStatus_HAL_AudioSuccess;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
}

hal_audio_status_t HAL_AudioTransferGetReceiveCount(hal_audio_handle_t handle, size_t *count)
{
    assert(handle);

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    *count = 0;
    return kStatus_HAL_AudioSuccess;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
}

hal_audio_status_t HAL_AudioTransferAbortSend(hal_audio_handle_t handle)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    I2S_TransferAbortDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

    return kStatus_HAL_AudioSuccess;
}

hal_audio_status_t HAL_AudioTransferAbortReceive(hal_audio_handle_t handle)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    I2S_TransferAbortDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

    return kStatus_HAL_AudioSuccess;
}
