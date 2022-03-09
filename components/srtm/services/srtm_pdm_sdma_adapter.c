/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_pdm_sdma_adapter.h"
#include "srtm_heap.h"
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
#include "fsl_memory.h"
#endif
#include "fsl_pdm.h"
#include "fsl_pdm_sdma.h"
#include "srtm_dispatcher.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"
#include "srtm_service_struct.h"
#include "fsl_sdma_script.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRTM_SDMA_MAX_TRANSFER_SIZE UINT16_MAX

typedef enum _srtm_pdm_sdma_suspend_state
{
    SRTM_NotSuspended,
    SRTM_Suspended,
    SRTM_WakingUp,
} srtm_pdm_sdma_suspend_state;

typedef struct _srtm_pdm_sdma_buf_runtime
{
    uint32_t leadIdx;          /* ready period index for playback or recording. */
    uint32_t chaseIdx;         /* consumed period index for recording. */
    uint32_t loadIdx;          /* used to indicate period index preloaded either to DMA transfer or to local buffer. */
    uint32_t remainingPeriods; /* periods to be consumed/filled */
    uint32_t remainingLoadPeriods; /* periods to be preloaded either to DMA transfer or to local buffer. */
    uint32_t offset;               /* period offset, non-zero value means current period is not finished. */
} * srtm_pdm_sdma_buf_runtime_t;

typedef struct _srtm_pdm_sdma_runtime
{
    srtm_audio_state_t state;
    pdm_sdma_handle_t pdmHandle;
    uint8_t bitWidth;
    uint8_t format;
    uint8_t pdmChannels; /* Enabled PDM channels. */
    uint32_t srate;
    uint8_t *bufAddr;
    uint32_t bufSize;
    uint32_t periodSize;
    uint32_t periods;
    uint32_t readyIdx; /* period ready index. */
    uint32_t
        maxXferSize; /* The maximum bytes can be transfered by each DMA transmission with given channels and format. */
    uint32_t countsPerPeriod; /* The DMA transfer count for each period. If the periodSize is larger than maxXferSize,
                                the period will be splited into multiple transmissions. */
    uint32_t curXferIdx;      /* The current transmission index in countsPerPeriod. */
    srtm_procedure_t proc;    /* proc message to trigger DMA transfer in SRTM context. */
    struct _srtm_pdm_sdma_buf_runtime bufRtm; /* buffer provided by audio client. */
    bool freeRun;                             /* flag to indicate that no periodReady will be sent by audio client. */
    bool stoppedOnSuspend;
    bool paramSet;
    uint32_t finishedBufOffset;                 /* offset from bufAddr where the data transfer has completed. */
    srtm_pdm_sdma_suspend_state suspendState;   /* service state in client suspend. */
    srtm_pdm_sdma_data_callback_t dataCallback; /* Callback function to provide data when client is suspend */
    void *dataCallbackParam;                    /* Callback function argument to be passed back to application */
} * srtm_pdm_sdma_runtime_t;

/* SAI SDMA adapter */
typedef struct _srtm_pdm_sdma_adapter
{
    struct _srtm_sai_adapter adapter;
    uint32_t index;

    PDM_Type *pdm;
    SDMAARM_Type *dma;
    srtm_pdm_sdma_config_t rxConfig;
    sdma_handle_t rxDmaHandle;
    struct _srtm_pdm_sdma_runtime rxRtm;
} * srtm_pdm_sdma_adapter_t;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static const char *saiDirection[] = {"Rx", "Tx"};
#endif
static short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_PdmSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter, srtm_audio_state_t *pRxState)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    *pRxState = handle->rxRtm.state;
}

static void SRTM_PdmSdmaAdapter_RecycleRxMessage(srtm_message_t msg, void *param)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param;
    assert(handle->rxRtm.proc == NULL);

    handle->rxRtm.proc = msg;
}

static status_t SRTM_PdmSdmaAdapter_PeriodReceiveSDMA(srtm_pdm_sdma_adapter_t handle)
{
    status_t status = kStatus_Success;
    uint32_t count;
    pdm_transfer_t xfer;
    srtm_pdm_sdma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;

    count = rtm->periodSize - bufRtm->offset;
    while (count > rtm->maxXferSize) /* Split the period into several DMA transfer. */
    {
        xfer.dataSize = rtm->maxXferSize;
        xfer.data     = rtm->bufAddr + bufRtm->loadIdx * rtm->periodSize + bufRtm->offset;
        status        = PDM_TransferReceiveSDMA(handle->pdm, &rtm->pdmHandle, &xfer);
        if (status == kStatus_Success)
        {
            count = count - rtm->maxXferSize;
            bufRtm->offset += rtm->maxXferSize;
        }
        else
        {
            return status;
        }
    }
    if (count > 0U)
    {
        xfer.dataSize = count;
        xfer.data     = rtm->bufAddr + bufRtm->loadIdx * rtm->periodSize + bufRtm->offset;
        status        = PDM_TransferReceiveSDMA(handle->pdm, &rtm->pdmHandle, &xfer);
        if (status != kStatus_Success)
        {
            return status;
        }
        bufRtm->offset = 0; /* All the transfers for the one period is done. */
    }

    if (bufRtm->offset == 0U) /* The whole period is finished. */
    {
        bufRtm->loadIdx = (bufRtm->loadIdx + 1U) % rtm->periods;
        bufRtm->remainingLoadPeriods--;
    }

    return kStatus_Success;
}

static void SRTM_PdmSdmaAdapter_DmaTransfer(srtm_pdm_sdma_adapter_t handle)
{
    srtm_pdm_sdma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;
    uint32_t i;
    status_t status;
    uint32_t num;

    num = bufRtm->remainingLoadPeriods;

    for (i = 0U; i < num; i++)
    {
        status = SRTM_PdmSdmaAdapter_PeriodReceiveSDMA(handle);

        if (status != kStatus_Success)
        {
            /* Audio queue full. */
            break;
        }
    }
}

static void SRTM_PdmSdmaAdapter_AddNewPeriods(srtm_pdm_sdma_runtime_t rtm, uint32_t periodIdx)
{
    srtm_pdm_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;
    uint32_t newPeriods;
    uint32_t primask;

    assert(periodIdx < rtm->periods);

    newPeriods = (periodIdx + rtm->periods - bufRtm->leadIdx) % rtm->periods;
    if (newPeriods == 0U) /* In case buffer is empty and filled all. */
    {
        newPeriods = rtm->periods;
    }

    bufRtm->leadIdx = periodIdx;
    primask         = DisableGlobalIRQ();
    bufRtm->remainingPeriods += newPeriods;
    EnableGlobalIRQ(primask);
    bufRtm->remainingLoadPeriods += newPeriods;
}

static void SRTM_PdmSdmaAdapter_Transfer(srtm_pdm_sdma_adapter_t handle)
{
    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;

    /* Trigger DMA if having more data to playback/record. */
    SRTM_PdmSdmaAdapter_DmaTransfer(handle);

    if (rtm->freeRun && (rtm->bufRtm.remainingPeriods < rtm->periods))
    {
        /* In free run, we assume consumed period is filled immediately. */
        SRTM_PdmSdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);
    }
}

static void SRTM_PdmSdmaAdapter_RxTransferProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = (uint32_t)(uint8_t *)param2;

    if ((rtm->suspendState == SRTM_Suspended) && (rtm->dataCallback != NULL) && (chaseIdx < rtm->periods))
    {
        rtm->dataCallback(adapter, (void *)(rtm->bufAddr + chaseIdx * rtm->periodSize), rtm->periodSize,
                          rtm->dataCallbackParam);
    }

    if (rtm->state == SRTM_AudioStateStarted)
    {
        /* Trigger DMA if having more buffer to record. */
        SRTM_PdmSdmaAdapter_Transfer(handle);
    }
}

static void SRTM_PdmSdmaRxCallback(PDM_Type *sai, pdm_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)userData;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = UINT32_MAX;

    if (rtm->curXferIdx == rtm->countsPerPeriod) /* All the transfer in a period is done. */
    {
        rtm->curXferIdx = 1U;

        rtm->bufRtm.remainingPeriods--;
        rtm->bufRtm.chaseIdx   = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
        rtm->finishedBufOffset = rtm->bufRtm.chaseIdx * rtm->periodSize;

        /* Rx is always freeRun, we assume filled period is consumed immediately. */
        SRTM_PdmSdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);

        if ((adapter->service != NULL) && (adapter->periodDone != NULL))
        {
            /* Rx is always freeRun */
            if ((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL))
            {
                (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
            }
            else
            {
                chaseIdx = rtm->bufRtm.chaseIdx; /* For callback. */
            }
        }

        if ((adapter->service != NULL) && (rtm->proc != NULL))
        {
            rtm->proc->procMsg.param2 = (void *)(uint8_t *)chaseIdx;
            /* Add buffer to DMA scatter-gather list if there's remaining buffer to record. */
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, rtm->proc);
            rtm->proc = NULL;
        }
        else if (rtm->proc == NULL)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: proc busy!\r\n", __func__);
        }
        else
        {
            ; /* Intentional empty */
        }
    }
    else
    {
        rtm->curXferIdx++;
        SRTM_PdmSdmaAdapter_Transfer(handle);
    }
}

static void SRTM_PdmSdmaAdapter_InitPDM(srtm_pdm_sdma_adapter_t handle)
{
    PDM_Init(handle->pdm, (const pdm_config_t *)(&handle->rxConfig.config));

    SDMA_CreateHandle(&handle->rxDmaHandle, handle->dma, handle->rxConfig.dmaChannel, &handle->rxConfig.rxContext);
    handle->rxDmaHandle.priority =
        handle->rxConfig.channelPriority; /* The priority will be set in SDMA_StartTransfer. */
    SDMA_LoadScript(handle->dma, FSL_SDMA_SCRIPT_CODE_START_ADDR, (void *)g_sdma_multi_fifo_script,
                    FSL_SDMA_SCRIPT_CODE_SIZE);

    PDM_TransferCreateHandleSDMA(handle->pdm, &handle->rxRtm.pdmHandle, SRTM_PdmSdmaRxCallback, (void *)handle,
                                 &handle->rxDmaHandle, handle->rxConfig.eventSource);
}

static void SRTM_PdmSdmaAdapter_SetConfig(srtm_pdm_sdma_adapter_t handle)
{
    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;
    uint32_t ch                 = 0;

    /* There must be a path with parameters configured before start. */
    assert(handle->rxRtm.paramSet);

    for (ch = 0; ch < rtm->pdmChannels; ch++)
    {
        PDM_SetChannelConfigSDMA(handle->pdm, &rtm->pdmHandle, ch, &handle->rxConfig.channelConfig);
    }

    (void)PDM_SetSampleRateConfig(handle->pdm, handle->rxConfig.pdmSrcClk, rtm->srate);

    PDM_Reset(handle->pdm);
}

static void SRTM_PdmSdmaAdapter_DeinitPDM(srtm_pdm_sdma_adapter_t handle)
{
    assert(handle != NULL);
    PDM_Reset(handle->pdm);
    PDM_Deinit(handle->pdm);
}

/* Currently only 1 audio instance is adequate, so index is just ignored */
static srtm_status_t SRTM_PdmSdmaAdapter_Open(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    /* Only support RX. */
    assert(dir == SRTM_AudioDirRx);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    /* Record the index. */
    handle->index = index;

    if (rtm->state != SRTM_AudioStateClosed)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    rtm->state    = SRTM_AudioStateOpened;
    rtm->freeRun  = true;
    rtm->paramSet = false;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Start(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_sdma_adapter_t handle  = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_sdma_config_t *thisCfg = &handle->rxConfig;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

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

    /* Init the audio device. */
    if (thisRtm->state != SRTM_AudioStateStarted)
    {
        if (thisCfg->extendConfig.audioDevInit != NULL)
        {
            thisCfg->extendConfig.audioDevInit(true);
        }
        SRTM_PdmSdmaAdapter_InitPDM(handle);
        /* Use our own format. */
        SRTM_PdmSdmaAdapter_SetConfig(handle);
    }

    thisRtm->state = SRTM_AudioStateStarted;
    /* Reset buffer index. */
    thisRtm->bufRtm.loadIdx    = thisRtm->bufRtm.chaseIdx;
    thisRtm->bufRtm.offset     = 0;
    thisRtm->finishedBufOffset = thisRtm->bufRtm.chaseIdx * thisRtm->periodSize;
    if (thisRtm->freeRun)
    {
        /* Assume buffer full in free run. */
        thisRtm->readyIdx = thisRtm->bufRtm.leadIdx;
    }

    SRTM_PdmSdmaAdapter_AddNewPeriods(thisRtm, thisRtm->readyIdx);
    SRTM_PdmSdmaAdapter_Transfer(handle);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_End(srtm_sai_adapter_t adapter, uint8_t index, bool stop)
{
    srtm_pdm_sdma_adapter_t handle  = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_sdma_config_t *thisCfg = &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d\r\n", __func__, index);

    if (thisRtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (thisRtm->state == SRTM_AudioStateStarted)
    {
        PDM_TransferAbortReceiveSDMA(handle->pdm, &thisRtm->pdmHandle);

        SRTM_PdmSdmaAdapter_DeinitPDM(handle);

        if (thisCfg->extendConfig.audioDevInit != NULL)
        {
            thisCfg->extendConfig.audioDevInit(false);
        }
    }

    thisRtm->bufRtm.remainingPeriods = thisRtm->bufRtm.remainingLoadPeriods = 0U;
    if (!thisRtm->freeRun)
    {
        thisRtm->readyIdx = thisRtm->bufRtm.leadIdx;
        thisRtm->freeRun  = stop; /* Reset to freeRun if stopped. */
    }
    thisRtm->bufRtm.leadIdx = thisRtm->bufRtm.chaseIdx;

    thisRtm->state = SRTM_AudioStateOpened;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Stop(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    assert(dir == SRTM_AudioDirRx);

    return SRTM_PdmSdmaAdapter_End(adapter, index, true);
}

static srtm_status_t SRTM_PdmSdmaAdapter_Close(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (rtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (rtm->state != SRTM_AudioStateOpened)
    {
        (void)SRTM_PdmSdmaAdapter_End(adapter, index, true);
    }

    rtm->state    = SRTM_AudioStateClosed;
    rtm->paramSet = false;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Pause(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);
    /* Disable request*/
    PDM_EnableDMA(handle->pdm, false);
    /* Disable PDM*/
    PDM_Enable(handle->pdm, false);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Restart(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    PDM_EnableDMA(handle->pdm, true);
    PDM_Enable(handle->pdm, true);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_SetParam(
    srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint8_t format, uint8_t channels, uint32_t srate)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_pdm_sdma_config_t *cfg    = &handle->rxConfig;
    uint32_t bytePerSample;

    assert(dir == SRTM_AudioDirRx);

    /* Currently, the format of the MICFIL/PDM IP is fixed. */
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d. fmt %d, ch %d, srate %d\r\n", __func__, saiDirection[dir],
                       index, format, channels, srate);

    if (rtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    if (channels == 0U)
    {
        channels = 1U; /* To be compatible with SAI Mono channel definition. */
    }
    if (channels > (uint32_t)FSL_FEATURE_PDM_CHANNEL_NUM)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s unsupported channels %d, %d!\r\n", __func__,
                           saiDirection[dir], channels);
        return SRTM_Status_InvalidParameter;
    }

    if (((rtm->format != format) || (rtm->srate != srate)) && (cfg->extendConfig.audioDevConf != NULL))
    {
        handle->rxConfig.pdmSrcClk = cfg->extendConfig.audioDevConf((srtm_audio_format_type_t)format, srate);
    }

    if (format <= (uint8_t)SRTM_Audio_Stereo32Bits)
    {
        rtm->bitWidth = saiFormatMap[format].bitwidth;
    }
    else
    {
        return SRTM_Status_InvalidParameter;
    }

    /* Caluate the max bytes can be done by each SDMA transfer. */
    bytePerSample    = ((uint32_t)rtm->bitWidth >> 3U) * channels;
    rtm->maxXferSize = (uint32_t)SRTM_SDMA_MAX_TRANSFER_SIZE / bytePerSample * bytePerSample;

    rtm->srate       = srate;
    rtm->pdmChannels = channels;

    rtm->paramSet = true;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_SetBuf(srtm_sai_adapter_t adapter,
                                                srtm_audio_dir_t dir,
                                                uint8_t index,
                                                uint8_t *bufAddr,
                                                uint32_t bufSize,
                                                uint32_t periodSize,
                                                uint32_t periodIdx)
{
    srtm_pdm_sdma_adapter_t handle     = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d. buf [0x%x, 0x%x]; prd size 0x%x, idx %d\r\n", __func__,
                       saiDirection[dir], index, bufAddr, bufSize, periodSize, periodIdx);

    if (rtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    /* Check the periodSize. */
    if (periodSize % (rtm->bitWidth / 8UL * rtm->pdmChannels) != 0U)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: %s in wrong period size %d!\r\n", __func__, saiDirection[dir],
                           periodSize);
        return SRTM_Status_InvalidParameter;
    }

    rtm->bufAddr    = bufAddr;
    rtm->periodSize = periodSize;
    rtm->periods    = (periodSize != 0U) ? bufSize / periodSize : 0U;
    rtm->bufSize    = periodSize * rtm->periods;

    rtm->countsPerPeriod = (rtm->periodSize + rtm->maxXferSize - 1U) / rtm->maxXferSize;
    rtm->curXferIdx      = 1U; /* The first transfer. */

    assert(periodIdx < rtm->periods);

    bufRtm->chaseIdx = periodIdx;
    bufRtm->leadIdx  = periodIdx;

    bufRtm->remainingPeriods = bufRtm->remainingLoadPeriods = 0U;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Suspend(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_pdm_sdma_adapter_t handle  = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_sdma_config_t *thisCfg = &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if ((thisRtm->state == SRTM_AudioStateStarted) && thisCfg->stopOnSuspend)
    {
        thisRtm->stoppedOnSuspend = true;
        status                    = SRTM_PdmSdmaAdapter_End(adapter, index, false);
    }

    thisRtm->suspendState = SRTM_Suspended;

    return status;
}

static srtm_status_t SRTM_PdmSdmaAdapter_Resume(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_pdm_sdma_adapter_t handle  = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t thisRtm = &handle->rxRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (thisRtm->stoppedOnSuspend)
    {
        thisRtm->stoppedOnSuspend = false;
        status                    = SRTM_PdmSdmaAdapter_Start(adapter, SRTM_AudioDirRx, index);
    }

    thisRtm->suspendState = SRTM_NotSuspended;

    return status;
}

static srtm_status_t SRTM_PdmSdmaAdapter_GetBufOffset(srtm_sai_adapter_t adapter,
                                                      srtm_audio_dir_t dir,
                                                      uint8_t index,
                                                      uint32_t *pOffset)
{
    assert(dir == SRTM_AudioDirRx);

    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    *pOffset = rtm->finishedBufOffset;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmSdmaAdapter_PeriodReady(srtm_sai_adapter_t adapter,
                                                     srtm_audio_dir_t dir,
                                                     uint8_t index,
                                                     uint32_t periodIdx)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_status_t status           = SRTM_Status_Success;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d - period %d\r\n", __func__, saiDirection[dir], index,
                       periodIdx);

    if (rtm->state == SRTM_AudioStateStarted)
    {
        /* RX is always free run. */
    }
    else
    {
        rtm->freeRun  = false;
        rtm->readyIdx = periodIdx;
    }

    return status;
}

srtm_sai_adapter_t SRTM_PdmSdmaAdapter_Create(PDM_Type *pdm, SDMAARM_Type *dma, srtm_pdm_sdma_config_t *rxConfig)
{
    srtm_pdm_sdma_adapter_t handle;

    assert((pdm != NULL) && (dma != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_pdm_sdma_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_pdm_sdma_adapter));
    assert(handle != NULL);
    (void)memset(handle, 0, sizeof(struct _srtm_pdm_sdma_adapter));

    handle->pdm = pdm;
    handle->dma = dma;

    if (rxConfig != NULL)
    {
        (void)memcpy(&handle->rxConfig, rxConfig, sizeof(srtm_pdm_sdma_config_t));
        handle->rxRtm.proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_RxTransferProc, handle, NULL);
        assert(handle->rxRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, SRTM_PdmSdmaAdapter_RecycleRxMessage, handle);
    }

    /* Adapter interfaces. */
    handle->adapter.open         = SRTM_PdmSdmaAdapter_Open;
    handle->adapter.start        = SRTM_PdmSdmaAdapter_Start;
    handle->adapter.pause        = SRTM_PdmSdmaAdapter_Pause;
    handle->adapter.restart      = SRTM_PdmSdmaAdapter_Restart;
    handle->adapter.stop         = SRTM_PdmSdmaAdapter_Stop;
    handle->adapter.close        = SRTM_PdmSdmaAdapter_Close;
    handle->adapter.setParam     = SRTM_PdmSdmaAdapter_SetParam;
    handle->adapter.setBuf       = SRTM_PdmSdmaAdapter_SetBuf;
    handle->adapter.suspend      = SRTM_PdmSdmaAdapter_Suspend;
    handle->adapter.resume       = SRTM_PdmSdmaAdapter_Resume;
    handle->adapter.getBufOffset = SRTM_PdmSdmaAdapter_GetBufOffset;
    handle->adapter.periodReady  = SRTM_PdmSdmaAdapter_PeriodReady;

    return &handle->adapter;
}

void SRTM_PdmSdmaAdapter_Destroy(srtm_sai_adapter_t adapter)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (handle->rxRtm.proc != NULL)
    {
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, NULL, NULL);
        SRTM_Procedure_Destroy(handle->rxRtm.proc);
    }

    SRTM_Heap_Free(handle);
}

void SRTM_PdmSdmaAdapter_SetDataHandlerOnHostSuspend(srtm_sai_adapter_t adapter,
                                                     srtm_pdm_sdma_data_callback_t cb,
                                                     void *param)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->rxRtm.dataCallback      = cb;
    handle->rxRtm.dataCallbackParam = param;
}

static void SRTM_PdmSdmaAdapter_ResumeHostProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;

    if (handle->rxRtm.suspendState == SRTM_Suspended)
    {
        handle->rxRtm.suspendState = SRTM_WakingUp;
    }
}

void SRTM_PdmSdmaAdapter_ResumeHost(srtm_sai_adapter_t adapter)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_procedure_t proc;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_ResumeHostProc, handle, NULL);
    if ((adapter->service != NULL) && (proc != NULL))
    {
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
    }
}
