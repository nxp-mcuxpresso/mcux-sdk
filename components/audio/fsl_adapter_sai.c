/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
#include "fsl_dmamux.h"
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#include "fsl_edma.h"
#include "fsl_sai.h"
#include "fsl_sai_edma.h"
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#include "fsl_dma.h"
#include "fsl_sai.h"
#include "fsl_sai_dma.h"
#else
#endif /* FSL_FEATURE_SOC_EDMA_COUNT, FSL_FEATURE_SOC_DMA4_COUNT or FSL_FEATURE_SOC_DMA_COUNT */
#include "fsl_adapter_audio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief hal audio state structure. */
typedef struct _hal_audio_state
{
    hal_audio_transfer_callback_t callback;
    void *callbackParam;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    sai_edma_handle_t xferDmaHandle;
    edma_handle_t dmaHandle;
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    sai_dma_handle_t xferDmaHandle;
    dma_handle_t dmaHandle;
#else
#endif
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    uint8_t dmaMuxInstance;
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#endif /* FSL_FEATURE_SOC_EDMA_COUNT or FSL_FEATURE_SOC_DMA4_COUNT */
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

/*! @brief Pointers to audio bases for each instance. */
static I2S_Type *const s_i2sBases[] = I2S_BASE_PTRS;
/*! @brief Resource for each i2s instance. */
static uint8_t s_i2sOccupied[ARRAY_SIZE(s_i2sBases)];
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
/*! @brief Resource for each dma instance. */
static uint8_t s_dmaOccupied[ARRAY_SIZE((DMA_Type *[])DMA_BASE_PTRS)];
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
/*! @brief Resource for each dma mux instance. */
static uint8_t s_dmaMuxOccupied[ARRAY_SIZE((DMAMUX_Type *[])DMAMUX_BASE_PTRS)];
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#endif /* FSL_FEATURE_SOC_EDMA_COUNT or FSL_FEATURE_SOC_DMA4_COUNT */
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (defined(FSL_FEATURE_SOC_I2S_COUNT) && (FSL_FEATURE_SOC_I2S_COUNT > 0U))
static void HAL_AudioFifoErrorIsr(I2S_Type *base)
{
    if (0U != (base->TCSR & (uint32_t)kSAI_FIFOErrorFlag))
    {
        /* Clear the FIFO error flag */
        SAI_TxClearStatusFlags(base, kSAI_FIFOErrorFlag);
        /* Reset FIFO */
        SAI_TxSoftwareReset(base, kSAI_ResetTypeFIFO);
    }

    if (0U != (base->RCSR & (uint32_t)kSAI_FIFOErrorFlag))
    {
        /* Clear the FIFO error flag */
        SAI_RxClearStatusFlags(base, kSAI_FIFOErrorFlag);
        /* Reset FIFO */
        SAI_RxSoftwareReset(base, kSAI_ResetTypeFIFO);
    }

    SDK_ISR_EXIT_BARRIER;
}
#endif

/* IRQHandler for I2S0 */
#if defined(I2S0) && (FSL_FEATURE_SOC_I2S_COUNT > 0U)
void I2S0_Tx_IRQHandler(void);
void I2S0_Rx_IRQHandler(void);
void I2S0_Tx_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(I2S0);
}
void I2S0_Rx_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(I2S0);
}
#endif

/* IRQHandler for SAI1 */
#if defined(SAI1) && (FSL_FEATURE_SOC_I2S_COUNT > 0U)
void SAI1_IRQHandler(void);
void SAI1_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI1);
}
#endif

/* IRQHandler for SAI2 */
#if defined(SAI2) && (FSL_FEATURE_SOC_I2S_COUNT > 0U)
void SAI2_IRQHandler(void);
void SAI2_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI2);
}
#endif

/* IRQHandler for SAI3 */
#if defined(SAI3) && (FSL_FEATURE_SOC_I2S_COUNT > 0U)
void SAI3_TX_IRQHandler(void);
void SAI3_RX_IRQHandler(void);
void SAI3_TX_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI3);
}
void SAI3_RX_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI3);
}
#endif

/* IRQHandler for SAI4 */
#if defined(SAI4) && (FSL_FEATURE_SOC_I2S_COUNT > 0U)
void SAI4_TX_IRQHandler(void);
void SAI4_RX_IRQHandler(void);
void SAI4_TX_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI4);
}
void SAI4_RX_IRQHandler(void)
{
    HAL_AudioFifoErrorIsr(SAI4);
}
#endif

static hal_audio_status_t HAL_AudioGetStatus(status_t status)
{
    hal_audio_status_t returnStatus;
    switch (status)
    {
        case kStatus_Success:
            returnStatus = kStatus_HAL_AudioSuccess;
            break;

        case kStatus_SAI_TxBusy:
        case kStatus_SAI_RxBusy:
            returnStatus = kStatus_HAL_AudioBusy;
            break;

        case kStatus_SAI_TxIdle:
        case kStatus_SAI_RxIdle:
        case kStatus_NoTransferInProgress:
            returnStatus = kStatus_HAL_AudioIdle;
            break;

        case kStatus_SAI_QueueFull:
            returnStatus = kStatus_HAL_AudioQueueFull;
            break;

        default:
            returnStatus = kStatus_HAL_AudioError;
            break;
    }
    return returnStatus;
}

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
static void HAL_AudioCallbackEDMA(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
    hal_audio_state_t *audioHandle;

    assert(userData);

    audioHandle = (hal_audio_state_t *)userData;

    if (NULL != audioHandle->callback)
    {
        audioHandle->callback(audioHandle, HAL_AudioGetStatus(status), audioHandle->callbackParam);
    }
}
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
static void HAL_AudioCallbackDMA(I2S_Type *base, sai_dma_handle_t *handle, status_t status, void *userData)
{
    hal_audio_state_t *audioHandle;

    assert(userData);

    audioHandle = (hal_audio_state_t *)userData;

    if (NULL != audioHandle->callback)
    {
        audioHandle->callback(audioHandle, HAL_AudioGetStatus(status), audioHandle->callbackParam);
    }
}
#else
#endif

static hal_audio_status_t HAL_AudioCommonInit(hal_audio_handle_t handle,
                                              const hal_audio_config_t *config,
                                              bool direction)
{
    hal_audio_state_t *audioHandle;
    sai_transceiver_t saiConfig;
    hal_audio_dma_config_t *dmaConfig;
    hal_audio_ip_config_t *featureConfig;
#if (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    EDMA_Type *dmaBases[] = EDMA_BASE_PTRS;
#else
    DMA_Type *dmaBases[] = DMA_BASE_PTRS;
#endif /* FSL_FEATURE_SOC_DMA4_COUNT */
    IRQn_Type txIrqNumber[] = I2S_TX_IRQS;
    IRQn_Type rxIrqNumber[] = I2S_RX_IRQS;
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL) && (FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL > 0U))
    IRQn_Type dmaIrqNumber[][FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL] = EDMA_CHN_IRQS;
#else
    IRQn_Type dmaIrqNumber[][FSL_FEATURE_EDMA_MODULE_CHANNEL] = DMA_CHN_IRQS;
#endif /* FSL_FEATURE_EDMA_MODULE_MAX_CHANNEL */
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    edma_config_t audioDmaConfig;
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */
    edma_channel_Preemption_config_t preemptionConfig;
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    DMAMUX_Type *dmaMuxBases[] = DMAMUX_BASE_PTRS;
    hal_audio_dma_mux_config_t *dmaMuxConfig;
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    IRQn_Type dmaIrqNumber[][FSL_FEATURE_DMA_MODULE_CHANNEL] = DMA_CHN_IRQS;
#else
#endif /* FSL_FEATURE_SOC_EDMA_COUNT, FSL_FEATURE_SOC_DMA4_COUNT or FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && (FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE > 0U))
    uint32_t u32Temp;
    uint8_t lineNum;
#endif /* FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE */
    uint8_t channelNum;

    assert(handle);
    assert(config);
    assert(config->dmaConfig);
    assert(config->ipConfig);
    /* If asserted, please check if the value of SAI_XFER_QUEUE_SIZE defined in the fsl_sai.h is modified.
       If modified, please modify the value of HAL_AUDIO_QUEUE_SIZE defined in the fsl_adapter_audio.h to be the same as
       SAI_XFER_QUEUE_SIZE. */
    assert(HAL_AUDIO_HANDLE_SIZE >= sizeof(hal_audio_state_t));
    assert(config->instance < ARRAY_SIZE(s_i2sBases));
    assert(config->dmaConfig->instance < ARRAY_SIZE(dmaBases));

    dmaConfig     = (hal_audio_dma_config_t *)config->dmaConfig;
    featureConfig = (hal_audio_ip_config_t *)config->ipConfig;
    audioHandle   = (hal_audio_state_t *)handle;

    assert(featureConfig->sai.lineMask != 0U);

    if (audioHandle->occupied != 0U)
    {
        return kStatus_HAL_AudioSuccess;
    }

    audioHandle->instance    = config->instance;
    audioHandle->dmaInstance = dmaConfig->instance;
    audioHandle->occupied    = 1;

    SAI_GetClassicI2SConfig(&saiConfig, (sai_word_width_t)config->bitWidth, kSAI_Stereo, featureConfig->sai.lineMask);

#if (defined(FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE) && (FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE > 0U))
    lineNum = 0;
    u32Temp = featureConfig->sai.lineMask;
    while (u32Temp > 0U)
    {
        u32Temp &= u32Temp - 1U;
        lineNum++;
    }

    if (lineNum > 1U)
    {
        saiConfig.fifo.fifoCombine = kSAI_FifoCombineModeEnabledOnWrite;
    }
#endif /* FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE */

#if (defined(FSL_FEATURE_SAI_HAS_FIFO) && (FSL_FEATURE_SAI_HAS_FIFO > 0U))
    if (config->fifoWatermark < (uint16_t)FSL_FEATURE_SAI_FIFO_COUNTn(s_i2sBases[audioHandle->instance]))
    {
        saiConfig.fifo.fifoWatermark = (uint8_t)config->fifoWatermark;
    }
    else
    {
        saiConfig.fifo.fifoWatermark = (uint8_t)FSL_FEATURE_SAI_FIFO_COUNTn(s_i2sBases[audioHandle->instance]) - 1U;
    }
#endif /* FSL_FEATURE_SAI_HAS_FIFO */

    if ((uint8_t)config->bclkPolarity == (uint8_t)kHAL_AudioSampleOnFallingEdge)
    {
        saiConfig.bitClock.bclkPolarity = kSAI_SampleOnFallingEdge;
    }
    else
    {
        saiConfig.bitClock.bclkPolarity = kSAI_SampleOnRisingEdge;
    }

    channelNum = (uint8_t)config->lineChannels;

    if (channelNum == (uint8_t)kHAL_AudioMono)
    {
        saiConfig.frameSync.frameSyncWidth = config->bitWidth >> 1U;
        saiConfig.serialData.dataWordNum   = 1U;
        channelNum                         = 1;
    }
    else if (channelNum < (uint8_t)kHAL_AudioStereo)
    {
        saiConfig.frameSync.frameSyncWidth  = config->bitWidth;
        saiConfig.serialData.dataWordNum    = 2U;
        saiConfig.serialData.dataMaskedWord = 0x1UL << channelNum;
        channelNum                          = 2;
    }
    else
    {
        saiConfig.frameSync.frameSyncWidth = config->bitWidth * channelNum >> 1U;
        saiConfig.serialData.dataWordNum   = channelNum;
    }

    if ((uint8_t)featureConfig->sai.syncMode == (uint8_t)kHAL_AudioSaiModeAsync)
    {
        saiConfig.syncMode = kSAI_ModeAsync;
    }
    else
    {
        saiConfig.syncMode = kSAI_ModeSync;
    }

    switch (config->msaterSlave)
    {
        case kHAL_AudioMaster:
            saiConfig.masterSlave = kSAI_Master;
            break;

        case kHAL_AudioSlave:
            saiConfig.masterSlave = kSAI_Slave;
            break;

        case kHAL_AudioBclkMasterFrameSyncSlave:
            saiConfig.masterSlave = kSAI_Bclk_Master_FrameSync_Slave;
            break;

        case kHAL_AudioBclkSlaveFrameSyncMaster:
            saiConfig.masterSlave = kSAI_Bclk_Slave_FrameSync_Master;
            break;

        default:
            assert(false);
            break;
    }

    switch (config->dataFormat)
    {
        case kHAL_AudioDataFormatI2sClassic:
            saiConfig.frameSync.frameSyncEarly    = true;
            saiConfig.frameSync.frameSyncPolarity = kSAI_PolarityActiveLow;
            break;

        case kHAL_AudioDataFormatLeftJustified:
            saiConfig.frameSync.frameSyncEarly    = false;
            saiConfig.frameSync.frameSyncPolarity = kSAI_PolarityActiveHigh;
            break;

        case kHAL_AudioDataFormatRightJustified:
            saiConfig.frameSync.frameSyncEarly    = false;
            saiConfig.frameSync.frameSyncPolarity = kSAI_PolarityActiveHigh;
            break;

        case kHAL_AudioDataFormatDspModeA:
            saiConfig.frameSync.frameSyncEarly    = true;
            saiConfig.frameSync.frameSyncPolarity = kSAI_PolarityActiveHigh;
            if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthOneBitClk)
            {
                saiConfig.frameSync.frameSyncWidth = 1;
            }
            else if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthPerWordWidth)
            {
                saiConfig.frameSync.frameSyncWidth = config->bitWidth;
            }
            else
            {
                /* no action */
            }
            break;

        case kHAL_AudioDataFormatDspModeB:
            saiConfig.frameSync.frameSyncEarly    = false;
            saiConfig.frameSync.frameSyncPolarity = kSAI_PolarityActiveHigh;
            if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthOneBitClk)
            {
                saiConfig.frameSync.frameSyncWidth = 1;
            }
            else if ((uint8_t)config->frameSyncWidth == (uint8_t)kHAL_AudioFrameSyncWidthPerWordWidth)
            {
                saiConfig.frameSync.frameSyncWidth = config->bitWidth;
            }
            else
            {
                /* no action */
            }
            break;

        default:
            assert(false);
            break;
    }

    if (s_i2sOccupied[audioHandle->instance] == 0U)
    {
        SAI_Init(s_i2sBases[audioHandle->instance]);
    }
    s_i2sOccupied[audioHandle->instance]++;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    assert(dmaConfig->dmaMuxConfig);

    dmaMuxConfig = (hal_audio_dma_mux_config_t *)dmaConfig->dmaMuxConfig;

    audioHandle->dmaMuxInstance = dmaMuxConfig->dmaMuxConfig.dmaMuxInstance;

#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    if (s_dmaMuxOccupied[audioHandle->dmaMuxInstance] == 0U)
    {
        DMAMUX_Init(dmaMuxBases[audioHandle->dmaMuxInstance]);
    }
    s_dmaMuxOccupied[audioHandle->dmaMuxInstance]++;
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    DMAMUX_SetSource(dmaMuxBases[audioHandle->dmaMuxInstance], dmaConfig->channel,
                     dmaMuxConfig->dmaMuxConfig.dmaRequestSource);

    DMAMUX_EnableChannel(dmaMuxBases[audioHandle->dmaMuxInstance], dmaConfig->channel);
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */

#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    EDMA_GetDefaultConfig(&audioDmaConfig);
#if (defined(FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION) && \
     (FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION > 0U))
    if (dmaConfig->dmaExtraConfig != NULL)
    {
        audioDmaConfig.enableMasterIdReplication =
            ((hal_audio_dma_extra_config_t *)dmaConfig->dmaExtraConfig)->edmaExtraConfig.enableMasterIdReplication;
    }
#endif /* FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION */
    if (s_dmaOccupied[dmaConfig->instance] == 0U)
    {
        EDMA_Init(dmaBases[dmaConfig->instance], &audioDmaConfig);
    }
    s_dmaOccupied[dmaConfig->instance]++;

#if (defined(FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG) && (FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG > 0U))
    if (dmaConfig->dmaChannelConfig != NULL)
    {
        EDMA_InitChannel(dmaBases[dmaConfig->instance], dmaConfig->channel, dmaConfig->dmaChannelConfig);
    }
#endif /* FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG */
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    NVIC_SetPriority((IRQn_Type)dmaIrqNumber[dmaConfig->instance][dmaConfig->channel], HAL_AUDIO_ISR_PRIORITY);
    EDMA_CreateHandle(&audioHandle->dmaHandle, dmaBases[dmaConfig->instance], dmaConfig->channel);

#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
#if (defined(FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) && (FSL_FEATURE_EDMA_HAS_CHANNEL_MUX > 0U))
    assert(dmaConfig->dmaChannelMuxConfig);
    EDMA_SetChannelMux(dmaBases[dmaConfig->instance], dmaConfig->channel,
                       (dma_request_source_t)((hal_audio_dma_channel_mux_config_t *)dmaConfig->dmaChannelMuxConfig)
                           ->dmaChannelMuxConfig.dmaRequestSource);
#endif /* FSL_FEATURE_EDMA_HAS_CHANNEL_MUX */
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    if ((uint8_t)kHAL_AudioDmaChannelPriorityDefault != (uint8_t)dmaConfig->priority)
    {
        preemptionConfig.enableChannelPreemption = dmaConfig->enablePreemption;
        preemptionConfig.enablePreemptAbility    = dmaConfig->enablePreemptAbility;
        preemptionConfig.channelPriority         = (uint8_t)dmaConfig->priority;
        EDMA_SetChannelPreemptionConfig(dmaBases[dmaConfig->instance], dmaConfig->channel, &preemptionConfig);
    }

    if (direction)
    {
        SAI_TransferTxCreateHandleEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                       HAL_AudioCallbackEDMA, audioHandle, &audioHandle->dmaHandle);
        SAI_TransferTxSetConfigEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &saiConfig);
    }
    else
    {
        SAI_TransferRxCreateHandleEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                       HAL_AudioCallbackEDMA, audioHandle, &audioHandle->dmaHandle);
        SAI_TransferRxSetConfigEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &saiConfig);
    }

#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    if (s_dmaOccupied[dmaConfig->instance] == 0U)
    {
        DMA_Init(dmaBases[dmaConfig->instance]);
    }
    s_dmaOccupied[dmaConfig->instance]++;
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    NVIC_SetPriority((IRQn_Type)dmaIrqNumber[dmaConfig->instance][dmaConfig->channel], HAL_AUDIO_ISR_PRIORITY);
    DMA_CreateHandle(&audioHandle->dmaHandle, dmaBases[dmaConfig->instance], dmaConfig->channel);

    if (direction)
    {
        SAI_TransferTxCreateHandleDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                      HAL_AudioCallbackDMA, audioHandle, &audioHandle->dmaHandle);
        SAI_TransferTxSetConfigDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &saiConfig);
    }
    else
    {
        SAI_TransferRxCreateHandleDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle,
                                      HAL_AudioCallbackDMA, audioHandle, &audioHandle->dmaHandle);
        SAI_TransferRxSetConfigDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &saiConfig);
    }
#else
#endif /* FSL_FEATURE_SOC_EDMA_COUNT, FSL_FEATURE_SOC_DMA4_COUNT or FSL_FEATURE_SOC_DMA_COUNT */

    if (direction)
    {
        SAI_TxSetBitClockRate(s_i2sBases[audioHandle->instance], config->srcClock_Hz, config->sampleRate_Hz,
                              config->bitWidth, channelNum);

        (void)EnableIRQ(txIrqNumber[audioHandle->instance]);

        SAI_TxEnableInterrupts(s_i2sBases[audioHandle->instance], kSAI_FIFOErrorInterruptEnable);
    }
    else
    {
        SAI_RxSetBitClockRate(s_i2sBases[audioHandle->instance], config->srcClock_Hz, config->sampleRate_Hz,
                              config->bitWidth, channelNum);

        (void)EnableIRQ(rxIrqNumber[audioHandle->instance]);

        SAI_RxEnableInterrupts(s_i2sBases[audioHandle->instance], kSAI_FIFOErrorInterruptEnable);
    }

    return kStatus_HAL_AudioSuccess;
}

static hal_audio_status_t HAL_AudioCommonDeinit(hal_audio_handle_t handle, bool direction)
{
    hal_audio_state_t *audioHandle;
#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
#if (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    EDMA_Type *dmaBases[] = EDMA_BASE_PTRS;
#else
    DMA_Type *dmaBases[]                                      = DMA_BASE_PTRS;
#endif /* FSL_FEATURE_SOC_DMA4_COUNT */
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    DMAMUX_Type *dmaMuxBases[] = DMAMUX_BASE_PTRS;
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#endif /* FSL_FEATURE_SOC_EDMA_COUNT or FSL_FEATURE_SOC_DMA4_COUNT */
#endif /* HAL_AUDIO_DMA_INIT_ENABLE */

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    if (audioHandle->occupied == 0U)
    {
        return kStatus_HAL_AudioSuccess;
    }
    audioHandle->occupied = 0;

    if (direction)
    {
        (void)HAL_AudioTransferAbortSend(handle);
    }
    else
    {
        (void)HAL_AudioTransferAbortReceive(handle);
    }

    if (s_i2sOccupied[audioHandle->instance] != 0U)
    {
        s_i2sOccupied[audioHandle->instance]--;

        if (s_i2sOccupied[audioHandle->instance] == 0U)
        {
            SAI_Deinit(s_i2sBases[audioHandle->instance]);
        }
    }

#if (defined(HAL_AUDIO_DMA_INIT_ENABLE) && (HAL_AUDIO_DMA_INIT_ENABLE > 0U))
    if (s_dmaOccupied[audioHandle->dmaInstance] != 0U)
    {
        s_dmaOccupied[audioHandle->dmaInstance]--;

        if (s_dmaOccupied[audioHandle->dmaInstance] == 0U)
        {
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
            EDMA_Deinit(dmaBases[audioHandle->dmaInstance]);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
            DMA_Deinit(dmaBases[audioHandle->dmaInstance]);
#else
#endif
        }
    }

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && (FSL_FEATURE_SOC_DMAMUX_COUNT > 0U))
    if (s_dmaMuxOccupied[audioHandle->dmaMuxInstance] != 0U)
    {
        s_dmaMuxOccupied[audioHandle->dmaMuxInstance]--;

        if (s_dmaMuxOccupied[audioHandle->dmaMuxInstance] == 0U)
        {
            DMAMUX_Deinit(dmaMuxBases[audioHandle->dmaMuxInstance]);
        }
    }
#endif /* FSL_FEATURE_SOC_DMAMUX_COUNT */
#endif /* FSL_FEATURE_SOC_EDMA_COUNT or FSL_FEATURE_SOC_DMA4_COUNT */
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
    sai_transfer_t transfer;
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    transfer.data     = (uint8_t *)xfer->data;
    transfer.dataSize = xfer->dataSize;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferSendEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &transfer));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferSendDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &transfer));
#else
#endif
}

hal_audio_status_t HAL_AudioTransferReceiveNonBlocking(hal_audio_handle_t handle, hal_audio_transfer_t *xfer)
{
    sai_transfer_t transfer;
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

    transfer.data     = (uint8_t *)xfer->data;
    transfer.dataSize = xfer->dataSize;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferReceiveEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &transfer));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferReceiveDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, &transfer));
#else
#endif
}

hal_audio_status_t HAL_AudioTransferGetSendCount(hal_audio_handle_t handle, size_t *count)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferGetSendCountEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, count));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferGetSendCountDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, count));
#else
#endif
}

hal_audio_status_t HAL_AudioTransferGetReceiveCount(hal_audio_handle_t handle, size_t *count)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferGetReceiveCountEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, count));
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    return HAL_AudioGetStatus(
        SAI_TransferGetReceiveCountDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle, count));
#else
#endif
}

hal_audio_status_t HAL_AudioTransferAbortSend(hal_audio_handle_t handle)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    SAI_TransferTerminateSendEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    SAI_TransferAbortSendDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#else
#endif

    return kStatus_HAL_AudioSuccess;
}

hal_audio_status_t HAL_AudioTransferAbortReceive(hal_audio_handle_t handle)
{
    hal_audio_state_t *audioHandle;

    assert(handle);

    audioHandle = (hal_audio_state_t *)handle;

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && (FSL_FEATURE_SOC_EDMA_COUNT > 0U)) || \
    (defined(FSL_FEATURE_SOC_DMA4_COUNT) && (FSL_FEATURE_SOC_DMA4_COUNT > 0U))
    SAI_TransferTerminateReceiveEDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#elif (defined(FSL_FEATURE_SOC_DMA_COUNT) && (FSL_FEATURE_SOC_DMA_COUNT > 0U))
    SAI_TransferAbortReceiveDMA(s_i2sBases[audioHandle->instance], &audioHandle->xferDmaHandle);
#else
#endif

    return kStatus_HAL_AudioSuccess;
}
