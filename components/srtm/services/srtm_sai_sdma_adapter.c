/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_sai_sdma_adapter.h"
#include "srtm_heap.h"
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
#include "fsl_memory.h"
#endif
#include "fsl_sai.h"
#include "fsl_sai_sdma.h"
#include "srtm_dispatcher.h"
#include "srtm_message.h"
#include "srtm_service_struct.h"
#include "fsl_sdma_script.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _srtm_sai_sdma_buf_runtime
{
    uint32_t leadIdx;          /* ready period index for playback or recording. */
    uint32_t chaseIdx;         /* consumed period index for playback or recording. */
    uint32_t loadIdx;          /* used to indicate period index preloaded either to DMA transfer or to local buffer. */
    uint32_t remainingPeriods; /* periods to be consumed/filled */
    uint32_t remainingLoadPeriods; /* periods to be preloaded either to DMA transfer or to local buffer. */
    uint32_t offset;               /* period offset to copy */
} * srtm_sai_sdma_buf_runtime_t;

struct _srtm_sai_sdma_local_period
{
    uint32_t dataSize;     /* bytes of copied data */
    uint32_t endRemoteIdx; /* period index of remote buffer if local period contains remote buffer end. */
    uint32_t remoteIdx;    /* save remote period index which the local period end points to */
    uint32_t remoteOffset; /* save remote period offset which the local period end points to */
};

struct _srtm_sai_sdma_local_runtime
{
    uint32_t periodSize;
    struct _srtm_sai_sdma_buf_runtime bufRtm;
    struct _srtm_sai_sdma_local_period periodsInfo[SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS];
};

typedef struct _srtm_sai_sdma_runtime
{
    srtm_audio_state_t state;
    sai_sdma_handle_t saiHandle;
    uint8_t bitWidth;
    uint8_t format;
    sai_mono_stereo_t streamMode;
    uint32_t srate;
    uint8_t *bufAddr;
    uint32_t bufSize;
    uint32_t periodSize;
    uint32_t periods;
    uint32_t readyIdx;                        /* period ready index. */
    srtm_procedure_t proc;                    /* proc message to trigger DMA transfer in SRTM context. */
    struct _srtm_sai_sdma_buf_runtime bufRtm; /* buffer provided by audio client. */
    srtm_sai_sdma_local_buf_t localBuf;
    struct _srtm_sai_sdma_local_runtime localRtm; /* buffer set by application. */
    bool freeRun;               /* flag to indicate that no periodReady will be sent by audio client. */
    uint32_t finishedBufOffset; /* offset from bufAddr where the data transfer has completed. */
    bool isSuspend;             /* flag to indicate that if M4 playback in suspend status. */
} * srtm_sai_sdma_runtime_t;

/* SAI SDMA adapter */
typedef struct _srtm_sai_sdma_adapter
{
    struct _srtm_sai_adapter adapter;
    uint32_t index;

    I2S_Type *sai;
    SDMAARM_Type *dma;
    srtm_sai_sdma_config_t txConfig;
    srtm_sai_sdma_config_t rxConfig;
    sdma_handle_t txDmaHandle;
    sdma_handle_t rxDmaHandle;
    struct _srtm_sai_sdma_runtime rxRtm;
    struct _srtm_sai_sdma_runtime txRtm;
} * srtm_sai_sdma_adapter_t;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static const sai_mono_stereo_t saiChannelMap[] = {kSAI_MonoLeft, kSAI_MonoRight, kSAI_Stereo};
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static const char *saiDirection[] = {"Rx", "Tx"};
#endif
static short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_SaiSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter,
                                              srtm_audio_state_t *pTxState,
                                              srtm_audio_state_t *pRxState)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    *pTxState = handle->txRtm.state;
    *pRxState = handle->rxRtm.state;
}

static void SRTM_SaidmaAdapter_LocalBufferUpdate(uint32_t *dest, uint32_t *src, uint32_t count)
{
    while (count != 0U)
    {
        *dest = *src;
        dest++;
        src++;
        count--;
    }
}

static void SRTM_SaiSdmaAdapter_RecycleTxMessage(srtm_message_t msg, void *param)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param;

    assert(handle->txRtm.proc == NULL);

    handle->txRtm.proc = msg;
}

static void SRTM_SaiSdmaAdapter_RecycleRxMessage(srtm_message_t msg, void *param)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param;
    assert(handle->rxRtm.proc == NULL);

    handle->rxRtm.proc = msg;
}

static void SRTM_SaiSdmaAdaptor_ResetLocalBuf(srtm_sai_sdma_runtime_t rtm)
{
    uint32_t i, n;

    if (rtm->localBuf.buf != NULL)
    {
        (void)memset(&rtm->localRtm.bufRtm, 0, sizeof(struct _srtm_sai_sdma_buf_runtime));
        rtm->localRtm.periodSize =
            (rtm->localBuf.bufSize / rtm->localBuf.periods) & (~SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK);
        /* Calculate how many local periods each remote period */
        n                        = (rtm->periodSize + rtm->localRtm.periodSize - 1U) / rtm->localRtm.periodSize;
        rtm->localRtm.periodSize = ((rtm->periodSize + n - 1U) / n + SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK) &
                                   (~SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK);
        for (i = 0U; i < SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS; i++)
        {
            rtm->localRtm.periodsInfo[i].dataSize     = 0U;
            rtm->localRtm.periodsInfo[i].endRemoteIdx = UINT32_MAX;
            rtm->localRtm.periodsInfo[i].remoteIdx    = 0U;
            rtm->localRtm.periodsInfo[i].remoteOffset = 0U;
        }
    }
}

static void SRTM_SaiSdmaAdapter_GetXfer(srtm_sai_sdma_runtime_t rtm, sai_transfer_t *xfer)
{
    srtm_sai_sdma_buf_runtime_t bufRtm;

    if (rtm->localBuf.buf != NULL)
    {
        bufRtm         = &rtm->localRtm.bufRtm;
        xfer->dataSize = rtm->localRtm.periodsInfo[bufRtm->loadIdx].dataSize;
        xfer->data     = rtm->localBuf.buf + bufRtm->loadIdx * rtm->localRtm.periodSize;
    }
    else
    {
        bufRtm         = &rtm->bufRtm;
        xfer->dataSize = rtm->periodSize;
        xfer->data     = rtm->bufAddr + bufRtm->loadIdx * rtm->periodSize;
    }
}

static void SRTM_SaiSdmaAdapter_DmaTransfer(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_buf_runtime_t bufRtm;
    uint32_t i;
    status_t status;
    uint32_t periods;
    sai_transfer_t xfer;
    uint32_t num;

    if (rtm->localBuf.buf != NULL)
    {
        bufRtm  = &rtm->localRtm.bufRtm;
        periods = rtm->localBuf.periods;
    }
    else
    {
        bufRtm  = &rtm->bufRtm;
        periods = rtm->periods;
    }

    num = bufRtm->remainingLoadPeriods;

    for (i = 0U; i < num; i++)
    {
        SRTM_SaiSdmaAdapter_GetXfer(rtm, &xfer);
        if (dir == SRTM_AudioDirTx)
        {
            status = SAI_TransferSendSDMA(handle->sai, &rtm->saiHandle, &xfer);
        }
        else
        {
            status = SAI_TransferReceiveSDMA(handle->sai, &rtm->saiHandle, &xfer);
        }
        if (status != kStatus_Success)
        {
            /* Audio queue full */
            break;
        }
        bufRtm->loadIdx = (bufRtm->loadIdx + 1U) % periods;
        bufRtm->remainingLoadPeriods--;
    }
}

static void SRTM_SaiSdmaAdapter_CopyData(srtm_sai_sdma_adapter_t handle)
{
    srtm_sai_sdma_runtime_t rtm;
    uint32_t srcSize, dstSize, size;
    srtm_sai_sdma_buf_runtime_t srcRtm, dstRtm;
    uint8_t *src, *dst;

    rtm    = &handle->txRtm;
    srcRtm = &rtm->bufRtm;
    dstRtm = &rtm->localRtm.bufRtm;

    while ((srcRtm->remainingLoadPeriods != 0U) && ((rtm->localBuf.periods - dstRtm->remainingPeriods) != 0U))
    {
        src     = rtm->bufAddr + srcRtm->loadIdx * rtm->periodSize;
        dst     = rtm->localBuf.buf + dstRtm->leadIdx * rtm->localRtm.periodSize;
        srcSize = rtm->periodSize - srcRtm->offset;
        dstSize = rtm->localRtm.periodSize - dstRtm->offset;
        size    = MIN(srcSize, dstSize);
        SRTM_SaidmaAdapter_LocalBufferUpdate((uint32_t *)(void *)(dst + dstRtm->offset),
                                             (uint32_t *)(void *)(src + srcRtm->offset), size / 4U);

        srcRtm->offset += size;
        dstRtm->offset += size;
        if (srcRtm->offset == rtm->periodSize) /* whole remote buffer loaded */
        {
            rtm->localRtm.periodsInfo[dstRtm->leadIdx].endRemoteIdx = srcRtm->loadIdx;
            srcRtm->loadIdx                                         = (srcRtm->loadIdx + 1U) % rtm->periods;
            srcRtm->offset                                          = 0U;
            srcRtm->remainingLoadPeriods--;
        }

        if (dstRtm->offset == rtm->localRtm.periodSize || srcRtm->offset == 0U)
        {
            /* local period full or remote period ends */
            rtm->localRtm.periodsInfo[dstRtm->leadIdx].dataSize     = dstRtm->offset;
            rtm->localRtm.periodsInfo[dstRtm->leadIdx].remoteIdx    = srcRtm->loadIdx;
            rtm->localRtm.periodsInfo[dstRtm->leadIdx].remoteOffset = srcRtm->offset;
            dstRtm->leadIdx                                         = (dstRtm->leadIdx + 1U) % rtm->localBuf.periods;
            dstRtm->remainingPeriods++;
            dstRtm->remainingLoadPeriods++;
            dstRtm->offset = 0U;
        }
    }
}

static void SRTM_SaiSdmaAdapter_AddNewPeriods(srtm_sai_sdma_runtime_t rtm, uint32_t periodIdx)
{
    srtm_sai_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;
    uint32_t newPeriods;
    uint32_t primask;

    assert(periodIdx < rtm->periods);

    newPeriods = (periodIdx + rtm->periods - bufRtm->leadIdx) % rtm->periods;
    if (newPeriods == 0U) /* in case buffer is empty and filled all */
    {
        newPeriods = rtm->periods;
    }

    bufRtm->leadIdx = periodIdx;
    primask         = DisableGlobalIRQ();
    bufRtm->remainingPeriods += newPeriods;
    EnableGlobalIRQ(primask);
    bufRtm->remainingLoadPeriods += newPeriods;
}

static void SRTM_SaiSdmaAdapter_Transfer(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    srtm_sai_sdma_runtime_t rtm = &handle->txRtm;

    if (dir == SRTM_AudioDirTx && (rtm->localBuf.buf != NULL))
    {
        if (rtm->localRtm.bufRtm.remainingPeriods <= rtm->localBuf.threshold)
        {
            /* Copy data from remote buffer to local buffer. */
            SRTM_SaiSdmaAdapter_CopyData(handle);
        }
    }
    /* Trigger DMA if having more data to playback/record. */
    SRTM_SaiSdmaAdapter_DmaTransfer(handle, dir);

    if (rtm->freeRun && rtm->bufRtm.remainingPeriods < rtm->periods)
    {
        /* In free run, we assume consumed period is filled immediately. */
        SRTM_SaiSdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);
    }
}

static void SRTM_SaiSdmaAdapter_TxTransferProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;
    srtm_sai_sdma_runtime_t rtm    = &handle->txRtm;

    if (rtm->state == SRTM_AudioStateStarted)
    {
        SRTM_SaiSdmaAdapter_Transfer(handle, SRTM_AudioDirTx);
    }
}

static void SRTM_SaiSdmaAdapter_RxTransferProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;
    srtm_sai_sdma_runtime_t rtm    = &handle->rxRtm;

    if (rtm->state == SRTM_AudioStateStarted)
    {
        /* Trigger DMA if having more buffer to record. */
        SRTM_SaiSdmaAdapter_Transfer(handle, SRTM_AudioDirRx);
    }
}

static void SRTM_SaiSdmaTxCallback(I2S_Type *sai, sai_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)userData;
    srtm_sai_sdma_runtime_t rtm    = &handle->txRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    bool consumed                  = true;
    if (rtm->localBuf.buf != NULL)
    {
        if (rtm->localRtm.periodsInfo[rtm->localRtm.bufRtm.chaseIdx].endRemoteIdx < rtm->periods)
        {
            /* The local buffer contains data from remote buffer end */
            rtm->bufRtm.remainingPeriods--; /* Now one of the remote buffer has been consumed. */
            rtm->bufRtm.chaseIdx = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
            rtm->localRtm.periodsInfo[rtm->localRtm.bufRtm.chaseIdx].endRemoteIdx = UINT32_MAX;
        }
        else
        {
            /* Remote period not consumed. */
            consumed = false;
        }

        rtm->finishedBufOffset = rtm->localRtm.periodsInfo[rtm->localRtm.bufRtm.chaseIdx].remoteIdx * rtm->periodSize +
                                 rtm->localRtm.periodsInfo[rtm->localRtm.bufRtm.chaseIdx].remoteOffset;
        rtm->localRtm.bufRtm.remainingPeriods--;
        rtm->localRtm.bufRtm.chaseIdx = (rtm->localRtm.bufRtm.chaseIdx + 1U) % rtm->localBuf.periods;
    }
    else
    {
        rtm->bufRtm.remainingPeriods--;
        rtm->bufRtm.chaseIdx   = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
        rtm->finishedBufOffset = rtm->bufRtm.chaseIdx * rtm->periodSize;
    }

    /* Notify period done message */
    if ((adapter->service != NULL) && (adapter->periodDone != NULL) && consumed &&
        (rtm->freeRun || (rtm->bufRtm.remainingPeriods <= handle->txConfig.threshold) || (!(rtm->isSuspend))))
    {
        /* In free run, we need to make buffer as full as possible, threshold is ignored. */
        (void)adapter->periodDone(adapter->service, SRTM_AudioDirTx, handle->index, rtm->bufRtm.chaseIdx);
    }

    if ((adapter->service != NULL) && ((rtm->state == SRTM_AudioStateStarted) && (rtm->proc != NULL)))
    {
        /* Fill data or add buffer to DMA scatter-gather list if there's remaining buffer to send */
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, rtm->proc);
        rtm->proc = NULL;
    }
}

static void SRTM_SaiSdmaRxCallback(I2S_Type *sai, sai_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)userData;
    srtm_sai_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    rtm->bufRtm.remainingPeriods--;
    rtm->bufRtm.chaseIdx   = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
    rtm->finishedBufOffset = rtm->bufRtm.chaseIdx * rtm->periodSize;

    /* Rx is always freeRun, we assume filled period is consumed immediately. */
    SRTM_SaiSdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);

    if ((adapter->service != NULL) && (adapter->periodDone != NULL))
    {
        /* Rx is always freeRun */
        (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
    }

    if ((adapter->service != NULL) && (rtm->state == SRTM_AudioStateStarted) && (rtm->proc != NULL))
    {
        /* Add buffer to DMA scatter-gather list if there's remaining buffer to send */
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, rtm->proc);
        rtm->proc = NULL;
    }
}

static void SRTM_SaiSdmaAdapter_InitSAI(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;

    SAI_Init(handle->sai);
    if (dir == SRTM_AudioDirTx)
    {
        SDMA_CreateHandle(&handle->txDmaHandle, handle->dma, handle->txConfig.dmaChannel, &handle->txConfig.txcontext);
        handle->txDmaHandle.priority = handle->txConfig.ChannelPriority;
        if (rtm->format >= (uint8_t)SRTM_Audio_DSD8bits) /* DSD mode, need enable SDMA multi fifo */
        {
            SDMA_LoadScript(handle->dma, FSL_SDMA_SCRIPT_CODE_START_ADDR, (void *)g_sdma_multi_fifo_script,
                            FSL_SDMA_SCRIPT_CODE_SIZE);
        }
        SAI_TransferTxCreateHandleSDMA(handle->sai, &handle->txRtm.saiHandle, SRTM_SaiSdmaTxCallback, (void *)handle,
                                       &handle->txDmaHandle, handle->txConfig.eventSource);
    }
    else
    {
        SDMA_CreateHandle(&handle->rxDmaHandle, handle->dma, handle->rxConfig.dmaChannel, &handle->rxConfig.rxcontext);
        handle->rxDmaHandle.priority = handle->rxConfig.ChannelPriority;
        SAI_TransferRxCreateHandleSDMA(handle->sai, &handle->rxRtm.saiHandle, SRTM_SaiSdmaRxCallback, (void *)handle,
                                       &handle->rxDmaHandle, handle->rxConfig.eventSource);
    }
}

static void SRTM_SaiSdmaAdapter_DeinitSAI(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    if (dir == SRTM_AudioDirTx)
    {
        SAI_TxReset(handle->sai);
    }
    else
    {
        SAI_RxReset(handle->sai);
    }
}
static void SRTM_SaiSdmaAdapter_ReconfigSAI(srtm_sai_adapter_t adapter,
                                            srtm_audio_dir_t dir,
                                            uint8_t format,
                                            uint32_t srate)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm    = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *cfg    = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;
    uint32_t sai_source_clk;
    if (format >= (uint8_t)SRTM_Audio_DSD8bits && format <= (uint8_t)SRTM_Audio_DSD32bits)
    {
        format = format - 45U; /* Skip due to the format value from 3 to 47 not defined in SDK. */
        srate  = srate / 2U;
    }
    if ((rtm->format != format || rtm->srate != srate) && cfg->extendConfig.clkSetting != NULL)
    {
        if (cfg->extendConfig.pcmSaiSetting != NULL && cfg->extendConfig.dsdSaiSetting != NULL)
        {
            if (format <= (uint8_t)SRTM_Audio_Stereo32Bits) /* PCM mode */
            {
                cfg->extendConfig.pcmSaiSetting();
            }
            else
            {
                cfg->extendConfig.dsdSaiSetting();
            }
        }
        /* If the sampling rate is 11025Hz or its multiple, set the sai mclk to 22.5792Mhz,
         * for the other cases, set the sai mclk to 24.576Mhz.
         */
        if ((srate % (uint32_t)kSAI_SampleRate11025Hz) == 0U)
        {
            sai_source_clk = cfg->extendConfig.clkSetting(SRTM_CLK22M);
        }
        else
        {
            sai_source_clk = cfg->extendConfig.clkSetting(SRTM_CLK24M);
        }
        cfg->mclkConfig.mclkSourceClkHz = sai_source_clk;
        cfg->mclkConfig.mclkHz          = sai_source_clk;
    }
}

static void SRTM_SaiSdmaAdapter_SetFormat(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir, bool sync)
{
    srtm_sai_sdma_config_t *cfg = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;
    srtm_sai_sdma_runtime_t rtm;
    uint8_t channels, bitWidth;

    if (dir == SRTM_AudioDirTx)
    {
        if (sync)
        {
            rtm = &handle->rxRtm; /* Using the RX parameters to config the SAI if TX is in sync mode */
        }
        else
        {
            rtm = &handle->txRtm;
        }
    }
    else
    {
        if (sync)
        {
            rtm = &handle->txRtm; /* Using the TX parameters to config the SAI if RX is in sync mode */
        }
        else
        {
            rtm = &handle->rxRtm;
        }
    }

    channels                                   = rtm->streamMode == kSAI_Stereo ? 2U : 1U;
    bitWidth                                   = rtm->bitWidth == 24U ? 32U : rtm->bitWidth;
    cfg->config.serialData.dataMaskedWord      = (uint32_t)rtm->streamMode;
    cfg->config.serialData.dataWord0Length     = bitWidth;
    cfg->config.serialData.dataWordLength      = bitWidth;
    cfg->config.serialData.dataWordNLength     = bitWidth;
    cfg->config.serialData.dataFirstBitShifted = rtm->bitWidth;
    cfg->config.frameSync.frameSyncWidth       = bitWidth;

    /* set master clock */
    SAI_SetMasterClockConfig(handle->sai, &cfg->mclkConfig);

    if (dir == SRTM_AudioDirTx)
    {
        if (rtm->format >= (uint8_t)SRTM_Audio_DSD8bits) /* DSD mode */
        {
            cfg->config.channelMask          = 1U << cfg->dataLine1 | 1U << cfg->dataLine2;
            cfg->config.serialData.dataOrder = kSAI_DataLSB; /* LSB transfer first */
            cfg->config.serialData.dataFirstBitShifted =
                1U; /* The value should be fixed to 1 when in LSB transfer mode */
        }
        else
        {
            cfg->config.channelMask          = 1U << cfg->dataLine1;
            cfg->config.serialData.dataOrder = kSAI_DataMSB; /* MSB transfer first */
        }
        SAI_TransferTxSetConfigSDMA(handle->sai, &rtm->saiHandle, &cfg->config);
        /* set bit clock */
        SAI_TxSetBitClockRate(handle->sai, cfg->mclkConfig.mclkHz, rtm->srate, bitWidth, channels);
    }
    else
    {
        cfg->config.channelMask = 1U << cfg->dataLine1;
        SAI_TransferRxSetConfigSDMA(handle->sai, &rtm->saiHandle, &cfg->config);
        /* set bit clock */
        SAI_RxSetBitClockRate(handle->sai, cfg->mclkConfig.mclkHz, rtm->srate, bitWidth, channels);
    }
}

/* Currently only 1 audio instance is adequate, so index is just ignored */
static srtm_status_t SRTM_SaiSdmaAdapter_Open(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm    = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *cfg    = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    /* Record the index */
    handle->index = index;

    if (rtm->state != SRTM_AudioStateClosed)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    /* Enable the clock. */
    if (cfg->extendConfig.clkGate != NULL)
    {
        cfg->extendConfig.clkGate(true);
    }

    /* Init the audio device. */
    if (cfg->extendConfig.audioDevInit != NULL)
    {
        cfg->extendConfig.audioDevInit(true);
    }

    rtm->state   = SRTM_AudioStateOpened;
    rtm->freeRun = true;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Start(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm, otherRtm;
    srtm_sai_sdma_config_t *thisCfg, *otherCfg;
    srtm_audio_dir_t otherDir;

    uint32_t *threshold = dir == SRTM_AudioDirTx ? &handle->txConfig.threshold : &handle->rxConfig.threshold;
    uint32_t *guardTime = dir == SRTM_AudioDirTx ? &handle->txConfig.guardTime : &handle->rxConfig.guardTime;

    uint8_t channelNum;
    uint32_t guardPeroids;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);
    if (dir == SRTM_AudioDirTx)
    {
        thisRtm  = &handle->txRtm;
        otherRtm = &handle->rxRtm;
        thisCfg  = &handle->txConfig;
        otherCfg = &handle->rxConfig;
        otherDir = SRTM_AudioDirRx;
    }
    else
    {
        thisRtm  = &handle->rxRtm;
        otherRtm = &handle->txRtm;
        thisCfg  = &handle->rxConfig;
        otherCfg = &handle->txConfig;
        otherDir = SRTM_AudioDirTx;
    }

    if (thisRtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           thisRtm->state);
        return SRTM_Status_InvalidState;
    }

    if (thisRtm->periods == 0U)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s valid buffer not set!\r\n", __func__, saiDirection[dir]);
        return SRTM_Status_InvalidState;
    }

    if (thisRtm->srate == 0U)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s valid format param not set!\r\n", __func__,
                           saiDirection[dir]);
        return SRTM_Status_InvalidState;
    }

    if (otherCfg->config.syncMode == kSAI_ModeSync)
    {
        /* The other direction in sync mode, it will initialize both directions. */
        if (otherRtm->state != SRTM_AudioStateStarted)
        {
            /* Only when the other direction is not started, we can initialize, else the device setting is reused. */
            SRTM_SaiSdmaAdapter_InitSAI(handle, dir);
            /* Use our own format. */
            SRTM_SaiSdmaAdapter_SetFormat(handle, dir, false);
        }
    }
    else
    {
        /* The other direction has dedicated clock, it will not initialize this direction.
           Do initialization by ourselves. */
        SRTM_SaiSdmaAdapter_InitSAI(handle, dir);
        /* Use our own format. */
        SRTM_SaiSdmaAdapter_SetFormat(handle, dir, false);

        if (thisCfg->config.syncMode == kSAI_ModeSync && otherRtm->state != SRTM_AudioStateStarted)
        {
            /* This direction in sync mode and the other not started, need to initialize the other direction. */
            SRTM_SaiSdmaAdapter_InitSAI(handle, otherDir);
            /* Set other direction format to ours. */
            SRTM_SaiSdmaAdapter_SetFormat(handle, otherDir, true);
        }
    }

    if (thisRtm->streamMode == kSAI_Stereo)
    {
        channelNum = 2U;
    }
    else
    {
        channelNum = 1U;
    }
    /* Caculate the threshold based on the guardTime.*/
    if (*guardTime != 0U)
    {
        guardPeroids = (uint32_t)((uint64_t)thisRtm->srate * thisRtm->bitWidth * channelNum * (*guardTime) /
                                  ((uint64_t)thisRtm->periodSize * 8U * 1000U));
        /* If the guardPeroids calculated based on the guardTime is larger than the threshold value ,
         * then the threshold should be enlarged to make sure there is enough time for A core resume and fill the DDR
         * buffer.
         */
        if (guardPeroids > *threshold)
        {
            *threshold = guardPeroids > thisRtm->periods ? thisRtm->periods : guardPeroids;
        }
    }
    thisRtm->state     = SRTM_AudioStateStarted;
    thisRtm->isSuspend = false;
    /* Reset buffer index */
    thisRtm->bufRtm.loadIdx    = thisRtm->bufRtm.chaseIdx;
    thisRtm->bufRtm.offset     = 0;
    thisRtm->finishedBufOffset = thisRtm->bufRtm.chaseIdx * thisRtm->periodSize;
    if (thisRtm->freeRun)
    {
        /* Assume buffer full in free run */
        thisRtm->readyIdx = thisRtm->bufRtm.leadIdx;
    }
    SRTM_SaiSdmaAdaptor_ResetLocalBuf(thisRtm);

    SRTM_SaiSdmaAdapter_AddNewPeriods(thisRtm, thisRtm->readyIdx);
    SRTM_SaiSdmaAdapter_Transfer(handle, dir);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_End(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, bool stop)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm, otherRtm;
    srtm_sai_sdma_config_t *thisCfg, *otherCfg;
    srtm_audio_dir_t otherDir;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (dir == SRTM_AudioDirTx)
    {
        thisRtm  = &handle->txRtm;
        otherRtm = &handle->rxRtm;
        thisCfg  = &handle->txConfig;
        otherCfg = &handle->rxConfig;
        otherDir = SRTM_AudioDirRx;
    }
    else
    {
        thisRtm  = &handle->rxRtm;
        otherRtm = &handle->txRtm;
        thisCfg  = &handle->rxConfig;
        otherCfg = &handle->txConfig;
        otherDir = SRTM_AudioDirTx;
    }

    if (thisRtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (thisRtm->state == SRTM_AudioStateStarted)
    {
        if (dir == SRTM_AudioDirTx)
        {
            SAI_TransferAbortSendSDMA(handle->sai, &thisRtm->saiHandle);
        }
        else
        {
            SAI_TransferAbortReceiveSDMA(handle->sai, &thisRtm->saiHandle);
        }

        if (otherCfg->config.syncMode == kSAI_ModeSync)
        {
            /* The other direction in sync mode, it will deinitialize this direction when it's stopped. */
            if (otherRtm->state != SRTM_AudioStateStarted)
            {
                /* The other direction not started, we can deinitialize this direction. */
                SRTM_SaiSdmaAdapter_DeinitSAI(handle, dir);
            }
        }
        else
        {
            /* The other direction has dedicated clock, its stop will not affect this direction.
               Do deinitialization by ourselves. */
            SRTM_SaiSdmaAdapter_DeinitSAI(handle, dir);
            if (thisCfg->config.syncMode == kSAI_ModeSync && otherRtm->state != SRTM_AudioStateStarted)
            {
                /* This direction in sync mode and the other not started, need to deinitialize the other direction. */
                SRTM_SaiSdmaAdapter_DeinitSAI(handle, otherDir);
            }
        }

        if (otherRtm->state != SRTM_AudioStateStarted)
        {
            /* If both Tx and Rx are not running, we can deinitialize this SAI instance. */
            SAI_Deinit(handle->sai);
        }
    }

    thisCfg->threshold               = 1U;
    thisRtm->isSuspend               = false;
    thisRtm->bufRtm.remainingPeriods = thisRtm->bufRtm.remainingLoadPeriods = 0U;
    if (!thisRtm->freeRun)
    {
        thisRtm->readyIdx = thisRtm->bufRtm.leadIdx;
        thisRtm->freeRun  = stop; /* Reset to freeRun if stopped. */
    }
    thisRtm->bufRtm.leadIdx = thisRtm->bufRtm.chaseIdx;
    thisCfg->stopOnSuspend  = true;

    thisRtm->state = SRTM_AudioStateOpened;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Stop(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    return SRTM_SaiSdmaAdapter_End(adapter, dir, index, true);
}

static srtm_status_t SRTM_SaiSdmaAdapter_Close(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm    = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *cfg    = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (rtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (rtm->state != SRTM_AudioStateOpened)
    {
        (void)SRTM_SaiSdmaAdapter_End(adapter, dir, index, true);
    }

    /* Disable the clock. */
    if (cfg->extendConfig.clkGate != NULL)
    {
        cfg->extendConfig.clkGate(false);
    }

    /* Deinit the audio device. */
    if (cfg->extendConfig.audioDevInit != NULL)
    {
        cfg->extendConfig.audioDevInit(false);
    }

    rtm->state = SRTM_AudioStateClosed;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Pause(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    if (dir == SRTM_AudioDirTx)
    {
        /* Disable request */
        SAI_TxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, false);
        /* Disable SAI */
        SAI_TxEnable(handle->sai, false);
    }
    else
    {
        /* Disable request*/
        SAI_RxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, false);
        /* Disable SAI*/
        SAI_RxEnable(handle->sai, false);
    }

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Restart(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (dir == SRTM_AudioDirTx)
    {
        /* Enable request */
        SAI_TxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, true);
        /* Enable SAI */
        SAI_TxEnable(handle->sai, true);
    }
    else
    {
        /* Enable request */
        SAI_RxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, true);
        /* Enable SAI */
        SAI_RxEnable(handle->sai, true);
    }

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_SetParam(
    srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint8_t format, uint8_t channels, uint32_t srate)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm    = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d. fmt %d, ch %d, srate %d\r\n", __func__, saiDirection[dir],
                       index, format, channels, srate);

    if (rtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    if (format > (uint8_t)SRTM_Audio_DSD32bits || channels >= ARRAY_SIZE(saiChannelMap))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s unsupported format or channels %d, %d!\r\n", __func__,
                           saiDirection[dir], format, channels);
        return SRTM_Status_InvalidParameter;
    }

    SRTM_SaiSdmaAdapter_ReconfigSAI(adapter, dir, format, srate);

    if (format >= (uint8_t)SRTM_Audio_DSD8bits && format <= (uint8_t)SRTM_Audio_DSD32bits)
    {
        /* DSD mode always two channels and get the sample frequcy to caculate the BCLK in the sai driver. */
        rtm->srate    = srate / 2U;
        rtm->bitWidth = saiFormatMap[format - 45U].bitwidth;
    }
    else if (format <= (uint8_t)SRTM_Audio_Stereo32Bits)
    {
        rtm->srate    = srate;
        rtm->bitWidth = saiFormatMap[format].bitwidth;
    }
    else
    {
        return SRTM_Status_Error;
    }

    rtm->format     = format;
    rtm->streamMode = saiChannelMap[channels];

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_SetBuf(srtm_sai_adapter_t adapter,
                                                srtm_audio_dir_t dir,
                                                uint8_t index,
                                                uint8_t *bufAddr,
                                                uint32_t bufSize,
                                                uint32_t periodSize,
                                                uint32_t periodIdx)
{
    srtm_sai_sdma_adapter_t handle     = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm        = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d. buf [0x%x, 0x%x]; prd size 0x%x, idx %d\r\n", __func__,
                       saiDirection[dir], index, bufAddr, bufSize, periodSize, periodIdx);
    if (rtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    rtm->bufAddr    = bufAddr;
    rtm->periodSize = periodSize;
    rtm->periods    = (periodSize != 0U) ? bufSize / periodSize : 0U;
    rtm->bufSize    = periodSize * rtm->periods;

    assert(periodIdx < rtm->periods);

    bufRtm->chaseIdx = periodIdx;
    bufRtm->leadIdx  = periodIdx;

    bufRtm->remainingPeriods = bufRtm->remainingLoadPeriods = 0U;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Suspend(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status           = SRTM_Status_Success;
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm;
    srtm_sai_sdma_config_t *thisCfg;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (dir == SRTM_AudioDirTx)
    {
        thisRtm = &handle->txRtm;
        thisCfg = &handle->txConfig;
    }
    else
    {
        thisRtm = &handle->rxRtm;
        thisCfg = &handle->rxConfig;
    }
    thisRtm->isSuspend = true;

    if (thisRtm->state == SRTM_AudioStateStarted && thisCfg->stopOnSuspend)
    {
        status = SRTM_SaiSdmaAdapter_End(adapter, dir, index, false);
    }

    return status;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Resume(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status           = SRTM_Status_Success;
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm;
    srtm_sai_sdma_config_t *thisCfg;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (dir == SRTM_AudioDirTx)
    {
        thisRtm = &handle->txRtm;
        thisCfg = &handle->txConfig;
    }
    else
    {
        thisRtm = &handle->rxRtm;
        thisCfg = &handle->rxConfig;
    }
    thisRtm->isSuspend = false;
    if (thisRtm->state == SRTM_AudioStateStarted && thisCfg->stopOnSuspend)
    {
        status = SRTM_SaiSdmaAdapter_Start(adapter, dir, index);
    }

    return status;
}

static srtm_status_t SRTM_SaiSdmaAdapter_GetBufOffset(srtm_sai_adapter_t adapter,
                                                      srtm_audio_dir_t dir,
                                                      uint8_t index,
                                                      uint32_t *pOffset)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm    = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    *pOffset = rtm->finishedBufOffset;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_PeriodReady(srtm_sai_adapter_t adapter,
                                                     srtm_audio_dir_t dir,
                                                     uint8_t index,
                                                     uint32_t periodIdx)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_sai_sdma_adapter_t handle  = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t rtm     = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *thisCfg = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d - period %d\r\n", __func__, saiDirection[dir], index,
                       periodIdx);

    if (rtm->state == SRTM_AudioStateStarted)
    {
        if (dir == SRTM_AudioDirTx)
        {
            SRTM_SaiSdmaAdapter_AddNewPeriods(rtm, periodIdx);
            /* Add buffer to DMA scatter-gather list if there's remaining buffer to send.
               Needed in case buffer xflow */
            SRTM_SaiSdmaAdapter_Transfer(handle, dir);
        }
    }
    else
    {
        rtm->freeRun           = false;
        rtm->readyIdx          = periodIdx;
        thisCfg->stopOnSuspend = false;
    }

    return status;
}

srtm_sai_adapter_t SRTM_SaiSdmaAdapter_Create(I2S_Type *sai,
                                              SDMAARM_Type *dma,
                                              srtm_sai_sdma_config_t *txConfig,
                                              srtm_sai_sdma_config_t *rxConfig)
{
    srtm_sai_sdma_adapter_t handle;

    assert((sai != NULL) && (dma != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_sai_sdma_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_sai_sdma_adapter));
    assert(handle != NULL);
    memset(handle, 0, sizeof(struct _srtm_sai_sdma_adapter));

    handle->sai = sai;
    handle->dma = dma;
    if (txConfig != NULL)
    {
        (void)memcpy(&handle->txConfig, txConfig, sizeof(srtm_sai_sdma_config_t));
        handle->txRtm.proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_TxTransferProc, handle, NULL);
        assert(handle->txRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->txRtm.proc, SRTM_SaiSdmaAdapter_RecycleTxMessage, handle);
    }
    if (rxConfig != NULL)
    {
        (void)memcpy(&handle->rxConfig, rxConfig, sizeof(srtm_sai_sdma_config_t));
        handle->rxRtm.proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_RxTransferProc, handle, NULL);
        assert(handle->rxRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, SRTM_SaiSdmaAdapter_RecycleRxMessage, handle);
    }

    /* Adapter interfaces. */
    handle->adapter.open         = SRTM_SaiSdmaAdapter_Open;
    handle->adapter.start        = SRTM_SaiSdmaAdapter_Start;
    handle->adapter.pause        = SRTM_SaiSdmaAdapter_Pause;
    handle->adapter.restart      = SRTM_SaiSdmaAdapter_Restart;
    handle->adapter.stop         = SRTM_SaiSdmaAdapter_Stop;
    handle->adapter.close        = SRTM_SaiSdmaAdapter_Close;
    handle->adapter.setParam     = SRTM_SaiSdmaAdapter_SetParam;
    handle->adapter.setBuf       = SRTM_SaiSdmaAdapter_SetBuf;
    handle->adapter.suspend      = SRTM_SaiSdmaAdapter_Suspend;
    handle->adapter.resume       = SRTM_SaiSdmaAdapter_Resume;
    handle->adapter.getBufOffset = SRTM_SaiSdmaAdapter_GetBufOffset;
    handle->adapter.periodReady  = SRTM_SaiSdmaAdapter_PeriodReady;

    return &handle->adapter;
}

void SRTM_SaiSdmaAdapter_Destroy(srtm_sai_adapter_t adapter)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (handle->txRtm.proc != NULL)
    {
        SRTM_Message_SetFreeFunc(handle->txRtm.proc, NULL, NULL);
        SRTM_Procedure_Destroy(handle->txRtm.proc);
    }

    if (handle->rxRtm.proc != NULL)
    {
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, NULL, NULL);
        SRTM_Procedure_Destroy(handle->rxRtm.proc);
    }

    SRTM_Heap_Free(handle);
}

void SRTM_SaiSdmaAdapter_SetTxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_sdma_local_buf_t *localBuf)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (localBuf != NULL)
    {
        assert(localBuf->periods <= SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS);
        (void)memcpy(&handle->txRtm.localBuf, localBuf, sizeof(srtm_sai_sdma_local_buf_t));
    }
    else
    {
        handle->txRtm.localBuf.buf = NULL;
    }
}
