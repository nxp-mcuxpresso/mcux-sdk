/*
 * Copyright 2018-2022, NXP
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
#include "srtm_message_struct.h"
#include "srtm_service_struct.h"
#include "fsl_sdma_script.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SRTM_SDMA_MAX_TRANSFER_SIZE UINT16_MAX

typedef enum _srtm_sai_sdma_suspend_state
{
    SRTM_NotSuspended,
    SRTM_Suspended,
    SRTM_WakingUp,
} srtm_sai_sdma_suspend_state;

typedef struct _srtm_sai_sdma_buf_runtime
{
    uint32_t leadIdx;          /* ready period index for playback or recording. */
    uint32_t chaseIdx;         /* consumed period index for playback or recording. */
    uint32_t loadIdx;          /* used to indicate period index preloaded either to DMA transfer or to local buffer. */
    uint32_t remainingPeriods; /* periods to be consumed/filled */
    uint32_t remainingLoadPeriods; /* periods to be preloaded either to DMA transfer or to local buffer. */
    uint32_t offset;               /* period offset to copy */
} * srtm_sai_sdma_buf_runtime_t;

#if SRTM_SAI_CONFIG_SupportLocalBuf
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
#endif

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
    uint32_t readyIdx; /* period ready index. */
    uint32_t
        maxXferSize; /* The maximum bytes can be transfered by each DMA transmission with given channels and format. */
    uint32_t
        countsPerPeriod;   /* The DMA transfer count for each period. If the periodSize is larger than maxXferSize,
                              the period will be splited into multiple transmissions. Not used if localBuf is enabled. */
    uint32_t curXferIdx;   /* The current transmission index in countsPerPeriod. Not used if localBuf is enabled. */
    srtm_procedure_t proc; /* proc message to trigger DMA transfer in SRTM context. */
    struct _srtm_sai_sdma_buf_runtime bufRtm; /* buffer provided by audio client. */
#if SRTM_SAI_CONFIG_SupportLocalBuf
    srtm_sai_sdma_local_buf_t localBuf;
    struct _srtm_sai_sdma_local_runtime localRtm; /* buffer set by application. */
#endif
    bool freeRun; /* flag to indicate that no periodReady will be sent by audio client. */
    bool stoppedOnSuspend;
    bool paramSet;
    uint32_t finishedBufOffset;               /* offset from bufAddr where the data transfer has completed. */
    srtm_sai_sdma_suspend_state suspendState; /* service state in client suspend. */
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_data_callback_t dataCallback; /* Callback function to provide data */
    void *dataCallbackParam;                    /* Callback function argument to be passed back to application */
#endif
} * srtm_sai_sdma_runtime_t;

/* SAI SDMA adapter */
typedef struct _srtm_sai_sdma_adapter
{
    struct _srtm_sai_adapter adapter;
    uint32_t index;

    I2S_Type *sai;
    SDMAARM_Type *dma;
    srtm_sai_sdma_config_t txConfig;
    sdma_handle_t txDmaHandle;
    struct _srtm_sai_sdma_runtime txRtm;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_config_t rxConfig;
    sdma_handle_t rxDmaHandle;
    struct _srtm_sai_sdma_runtime rxRtm;
#endif
} * srtm_sai_sdma_adapter_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if (SRTM_SAI_CONFIG_Rx_Enabled && SRTM_SAI_CONFIG_SupportLocalBuf)
static void SRTM_SaiSdmaAdapter_RxCopyData(srtm_sai_sdma_adapter_t handle);
#endif
static void SRTM_SaiSdmaAdapter_AddNewPeriods(srtm_sai_sdma_runtime_t rtm, uint32_t periodIdx);
/*******************************************************************************
 * Variables
 ******************************************************************************/

static const sai_mono_stereo_t saiChannelMap[] = {kSAI_MonoLeft, kSAI_MonoRight, kSAI_Stereo};
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static const char *saiDirection[] = {"Rx", "Tx"};
#endif
#ifdef SRTM_SINGLE_SDMA_MULTI_FIFO_SCRIPT
short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;
#else
static short g_sdma_multi_fifo_script[] = FSL_SDMA_MULTI_FIFO_SCRIPT;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_SaiSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter,
                                              srtm_audio_state_t *pTxState,
                                              srtm_audio_state_t *pRxState)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    *pTxState = handle->txRtm.state;
#if SRTM_SAI_CONFIG_Rx_Enabled
    *pRxState = handle->rxRtm.state;
#else
    *pRxState                          = SRTM_AudioStateClosed;
#endif
}

#if SRTM_SAI_CONFIG_SupportLocalBuf
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
#endif

static void SRTM_SaiSdmaAdapter_RecycleTxMessage(srtm_message_t msg, void *param)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param;

    assert(handle->txRtm.proc == NULL);

    handle->txRtm.proc = msg;
}

#if SRTM_SAI_CONFIG_Rx_Enabled
static void SRTM_SaiSdmaAdapter_RecycleRxMessage(srtm_message_t msg, void *param)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param;
    assert(handle->rxRtm.proc == NULL);

    handle->rxRtm.proc = msg;
}
#endif

#if SRTM_SAI_CONFIG_SupportLocalBuf
static void SRTM_SaiSdmaAdaptor_ResetLocalBuf(srtm_sai_sdma_runtime_t rtm, srtm_audio_dir_t dir)
{
    uint32_t i, n, alignment, maxPeriodSize;

    alignment = ((uint32_t)(rtm->bitWidth) >> 3U) * (rtm->streamMode == kSAI_Stereo ? 2UL : 1UL);

    if ((alignment % SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT) != 0U)
    {
        alignment *= SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT;
    }

    if (rtm->localBuf.buf != NULL)
    {
        (void)memset(&rtm->localRtm.bufRtm, 0, sizeof(struct _srtm_sai_sdma_buf_runtime));
        maxPeriodSize =
            (rtm->localBuf.bufSize / rtm->localBuf.periods) & (~SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK);

        if (dir == SRTM_AudioDirTx)
        {
            /* Calculate how many local periods each remote period */
            n = (rtm->periodSize + maxPeriodSize - 1U) / maxPeriodSize;
            /* Calculate local period size per remote period */
            rtm->localRtm.periodSize =
                ((rtm->periodSize + n - 1U) / n + SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK) &
                (~SRTM_SAI_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT_MASK);
            /* The period size should be a multiple of bytes per sample */
            rtm->localRtm.periodSize = (rtm->localRtm.periodSize + alignment - 1U) / alignment * alignment;
            if (rtm->localRtm.periodSize > maxPeriodSize)
            {
                rtm->localRtm.periodSize -= alignment;
            }

            for (i = 0U; i < SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS; i++)
            {
                rtm->localRtm.periodsInfo[i].dataSize     = 0U;
                rtm->localRtm.periodsInfo[i].endRemoteIdx = UINT32_MAX;
                rtm->localRtm.periodsInfo[i].remoteIdx    = 0U;
                rtm->localRtm.periodsInfo[i].remoteOffset = 0U;
            }
        }
#if SRTM_SAI_CONFIG_Rx_Enabled
        else /* RX */
        {
            rtm->localRtm.periodSize = rtm->localBuf.bufSize / rtm->localBuf.periods;
            rtm->localRtm.periodSize = rtm->localRtm.periodSize / alignment * alignment;

            rtm->localRtm.bufRtm.remainingLoadPeriods = rtm->localBuf.periods;
            rtm->localRtm.bufRtm.remainingPeriods     = rtm->localBuf.periods;

            for (i = 0U; i < SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS; i++)
            {
                rtm->localRtm.periodsInfo[i].dataSize = rtm->localRtm.periodSize;
            }
        }
#endif /* SRTM_SAI_CONFIG_Rx_Enabled */
    }
}
#endif

static status_t SRTM_SaiSdmaAdapter_PeriodTransferSDMA(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    status_t status = kStatus_Success;
    uint32_t count;
    sai_transfer_t xfer;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = (dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm);
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif
    srtm_sai_sdma_buf_runtime_t bufRtm;

#if SRTM_SAI_CONFIG_SupportLocalBuf
    if (rtm->localBuf.buf != NULL)
    {
        bufRtm = &rtm->localRtm.bufRtm;

        /* The period size in local buffer should be smaller than the max size of one DMA transfer. */
        xfer.dataSize = rtm->localRtm.periodsInfo[bufRtm->loadIdx].dataSize;
        xfer.data     = rtm->localBuf.buf + bufRtm->loadIdx * rtm->localRtm.periodSize;

        if (dir == SRTM_AudioDirTx)
        {
            status = SAI_TransferSendSDMA(handle->sai, &rtm->saiHandle, &xfer);
        }
#if SRTM_SAI_CONFIG_Rx_Enabled
        else
        {
            status = SAI_TransferReceiveSDMA(handle->sai, &rtm->saiHandle, &xfer);
        }
#endif
        if (status != kStatus_Success)
        {
            /* Audio queue full */
            return status;
        }
        bufRtm->loadIdx = (bufRtm->loadIdx + 1U) % rtm->localBuf.periods;
        bufRtm->remainingLoadPeriods--;
    }
    else
#endif /* SRTM_SAI_CONFIG_SupportLocalBuf */
    {
        bufRtm = &rtm->bufRtm;

        count = rtm->periodSize - bufRtm->offset;
        while (count > rtm->maxXferSize) /* Split the period into several DMA transfer. */
        {
            xfer.dataSize = rtm->maxXferSize;
            xfer.data     = rtm->bufAddr + bufRtm->loadIdx * rtm->periodSize + bufRtm->offset;
            if (dir == SRTM_AudioDirTx)
            {
                status = SAI_TransferSendSDMA(handle->sai, &rtm->saiHandle, &xfer);
            }
#if SRTM_SAI_CONFIG_Rx_Enabled
            else
            {
                status = SAI_TransferReceiveSDMA(handle->sai, &rtm->saiHandle, &xfer);
            }
#endif

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

            if (dir == SRTM_AudioDirTx)
            {
                status = SAI_TransferSendSDMA(handle->sai, &rtm->saiHandle, &xfer);
            }
#if SRTM_SAI_CONFIG_Rx_Enabled
            else
            {
                status = SAI_TransferReceiveSDMA(handle->sai, &rtm->saiHandle, &xfer);
            }
#endif

            if (status != kStatus_Success)
            {
                return status;
            }
            bufRtm->offset = 0; /* All the transfers for the one period are submitted. */
        }

        if (bufRtm->offset == 0U) /* All transmissions in a preiod are submitted successfully. */
        {
            bufRtm->loadIdx = (bufRtm->loadIdx + 1U) % rtm->periods;
            bufRtm->remainingLoadPeriods--;
        }
    }

    return kStatus_Success;
}

static void SRTM_SaiSdmaAdapter_DmaTransfer(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif
#if SRTM_SAI_CONFIG_SupportLocalBuf
    srtm_sai_sdma_buf_runtime_t bufRtm = (rtm->localBuf.buf != NULL) ? &rtm->localRtm.bufRtm : &rtm->bufRtm;
#else
    srtm_sai_sdma_buf_runtime_t bufRtm = &rtm->bufRtm;
#endif
    uint32_t i;
    status_t status;
    uint32_t num;

    num = bufRtm->remainingLoadPeriods;

    for (i = 0U; i < num; i++)
    {
        status = SRTM_SaiSdmaAdapter_PeriodTransferSDMA(handle, dir);
        if (status != kStatus_Success)
        {
            /* Audio queue full */
            break;
        }
    }
}

#if SRTM_SAI_CONFIG_SupportLocalBuf
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

        if ((dstRtm->offset == rtm->localRtm.periodSize) || (srcRtm->offset == 0U))
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
#endif

#if (SRTM_SAI_CONFIG_Rx_Enabled && SRTM_SAI_CONFIG_SupportLocalBuf)
static void SRTM_SaiSdmaAdapter_RxPeriodCopyAndNotify(srtm_sai_sdma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;
    srtm_sai_sdma_runtime_t rtm;
    uint32_t srcSize, dstSize, size;
    srtm_sai_sdma_buf_runtime_t srcRtm, dstRtm;
    uint8_t *src, *dst;
    uint32_t primask;
    rtm    = &handle->rxRtm;
    srcRtm = &rtm->localRtm.bufRtm;
    dstRtm = &rtm->bufRtm;

    /* Local buffer is not empty and remote buffer is not full. */
    if ((srcRtm->remainingPeriods != rtm->localBuf.periods) && (dstRtm->remainingPeriods != 0U))
    {
        src     = rtm->localBuf.buf + srcRtm->leadIdx * rtm->localRtm.periodSize;
        dst     = rtm->bufAddr + dstRtm->chaseIdx * rtm->periodSize;
        srcSize = rtm->localRtm.periodSize - srcRtm->offset;
        dstSize = rtm->periodSize - dstRtm->offset;
        size    = MIN(srcSize, dstSize);
        SRTM_SaidmaAdapter_LocalBufferUpdate((uint32_t *)(void *)(dst + dstRtm->offset),
                                             (uint32_t *)(void *)(src + srcRtm->offset), size / 4U);

        srcRtm->offset += size;
        dstRtm->offset += size;
        if (srcRtm->offset == rtm->localRtm.periodSize) /* whole local buffer copied */
        {
            srcRtm->leadIdx = (srcRtm->leadIdx + 1U) % rtm->localBuf.periods;
            srcRtm->offset  = 0U;
            primask         = DisableGlobalIRQ();
            srcRtm->remainingPeriods++;
            srcRtm->remainingLoadPeriods++;
            EnableGlobalIRQ(primask);
        }

        if (dstRtm->offset == rtm->periodSize)
        {
            /* One period is filled. */
            dstRtm->chaseIdx = (dstRtm->chaseIdx + 1U) % rtm->periods;
            dstRtm->remainingPeriods--; /* Now one of the remote buffer has been consumed. Assume the ready period is
                                           consumed by host immediately. */
            dstRtm->remainingLoadPeriods--; /* Unused. */
            rtm->finishedBufOffset = dstRtm->chaseIdx * rtm->periodSize;
            dstRtm->offset         = 0U;

            SRTM_SaiSdmaAdapter_AddNewPeriods(rtm, dstRtm->chaseIdx);

            if ((adapter->service != NULL) && (adapter->periodDone != NULL))
            {
                if (((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL)))
                {
                    (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
                }
            }
        }
    }
}

static void SRTM_SaiSdmaAdapter_RxDataCopyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;

    /* More data need to be copied. */
    SRTM_SaiSdmaAdapter_RxCopyData(handle);
}

static void SRTM_SaiSdmaAdapter_RxCopyData(srtm_sai_sdma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;
    srtm_sai_sdma_runtime_t rtm;
    srtm_sai_sdma_buf_runtime_t srcRtm, dstRtm;
    rtm    = &handle->rxRtm;
    srcRtm = &rtm->localRtm.bufRtm;
    dstRtm = &rtm->bufRtm;
    srtm_procedure_t proc;

    SRTM_SaiSdmaAdapter_RxPeriodCopyAndNotify(handle);

    /* More data need to be copied. */
    if ((srcRtm->remainingPeriods != rtm->localBuf.periods) && (dstRtm->remainingPeriods != 0U))
    {
        proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_RxDataCopyProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
    }
}
#endif

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
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = (dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm);
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif

#if SRTM_SAI_CONFIG_SupportLocalBuf
    if (rtm->localBuf.buf != NULL)
    {
        if ((dir == SRTM_AudioDirTx) && (rtm->localRtm.bufRtm.remainingPeriods <= rtm->localBuf.threshold))
        {
            /* Copy data from remote buffer to local buffer. */
            SRTM_SaiSdmaAdapter_CopyData(handle);
        }
    }
#endif

    /* Trigger DMA if having more data to playback/record. */
    SRTM_SaiSdmaAdapter_DmaTransfer(handle, dir);

#if (SRTM_SAI_CONFIG_Rx_Enabled && SRTM_SAI_CONFIG_SupportLocalBuf)
    if ((rtm->localBuf.buf != NULL) && (dir == SRTM_AudioDirRx))
    {
        if ((rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods) &&
            ((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL)))
        {
            /* Copy data from local buffer to remote buffer and notify remote. */
            SRTM_SaiSdmaAdapter_RxCopyData(handle);
        }
    }
#endif

    if (rtm->freeRun && (rtm->bufRtm.remainingPeriods < rtm->periods))
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

#if SRTM_SAI_CONFIG_Rx_Enabled
static void SRTM_SaiSdmaAdapter_RxTransferProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;
    srtm_sai_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = (uint32_t)(uint8_t *)param2;
    uint8_t *bufAddr;
    uint32_t bufSize;

    if ((rtm->suspendState == SRTM_Suspended) && (rtm->dataCallback != NULL) && (chaseIdx != UINT32_MAX))
    {
#if SRTM_SAI_CONFIG_SupportLocalBuf
        if (rtm->localBuf.buf != NULL)
        {
            bufAddr = rtm->localBuf.buf + chaseIdx * rtm->localRtm.periodSize;
            bufSize = rtm->localRtm.periodsInfo[chaseIdx].dataSize;
        }
        else
#endif
        {
            bufAddr = rtm->bufAddr + chaseIdx * rtm->periodSize;
            bufSize = rtm->periodSize;
        }
        rtm->dataCallback(adapter, (void *)bufAddr, bufSize, rtm->dataCallbackParam);
    }

    if (rtm->state == SRTM_AudioStateStarted)
    {
        /* Trigger DMA if having more buffer to record. */
        SRTM_SaiSdmaAdapter_Transfer(handle, SRTM_AudioDirRx);
    }
}
#endif

static void SRTM_SaiSdmaTxCallback(I2S_Type *sai, sai_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)userData;
    srtm_sai_sdma_runtime_t rtm    = &handle->txRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    bool consumed                  = true;
    bool periodDone                = false;

#if SRTM_SAI_CONFIG_SupportLocalBuf
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

        periodDone = true;
    }
    else
#endif
    {
        if (rtm->curXferIdx == rtm->countsPerPeriod)
        {
            rtm->curXferIdx = 1U;
            periodDone      = true;

            rtm->bufRtm.remainingPeriods--;
            rtm->bufRtm.chaseIdx   = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
            rtm->finishedBufOffset = rtm->bufRtm.chaseIdx * rtm->periodSize;
        }
        else
        {
            rtm->curXferIdx++;
            periodDone = false;
            SRTM_SaiSdmaAdapter_DmaTransfer(handle, SRTM_AudioDirTx);
        }
    }

    if (periodDone)
    {
        /* Notify period done message */
        if ((adapter->service != NULL) && (adapter->periodDone != NULL) && consumed &&
            (rtm->freeRun || (rtm->bufRtm.remainingPeriods <= handle->txConfig.threshold) ||
             (rtm->suspendState != SRTM_Suspended)))
        {
            /* In free run, we need to make buffer as full as possible, threshold is ignored. */
            (void)adapter->periodDone(adapter->service, SRTM_AudioDirTx, handle->index, rtm->bufRtm.chaseIdx);
        }

        if ((adapter->service != NULL) && (rtm->proc != NULL))
        {
            /* Fill data or add buffer to DMA scatter-gather list if there's remaining buffer to send */
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
}

#if SRTM_SAI_CONFIG_Rx_Enabled
static void SRTM_SaiSdmaRxCallback(I2S_Type *sai, sai_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)userData;
    srtm_sai_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = UINT32_MAX;

    bool periodDone = false; /* One period transfer is finished. Indicating local period when localBuf is used. */
#if SRTM_SAI_CONFIG_SupportLocalBuf
    /* When localBuf is used, the period size should not exceed the max size supported by one DMA tranfer. */
    if (rtm->localBuf.buf != NULL)
    {
        rtm->localRtm.bufRtm.remainingPeriods--; /* One of the local period is filled */

        chaseIdx                      = rtm->localRtm.bufRtm.chaseIdx; /* For callback */
        rtm->localRtm.bufRtm.chaseIdx = (rtm->localRtm.bufRtm.chaseIdx + 1U) % rtm->localBuf.periods;

        /* Rx is always freeRun, we assume filled period is consumed immediately. */
        periodDone = true;
        if ((rtm->suspendState == SRTM_Suspended) && (rtm->dataCallback != NULL))
        {
            /* Local RX buffer is full. Allow overwrite. remainingPeriods should be 0*/
            if (rtm->localRtm.bufRtm.chaseIdx == rtm->localRtm.bufRtm.leadIdx)
            {
                rtm->localRtm.bufRtm.leadIdx = (rtm->localRtm.bufRtm.leadIdx + 1U) % rtm->localBuf.periods;
                rtm->localRtm.bufRtm.remainingLoadPeriods =
                    (rtm->localRtm.bufRtm.remainingLoadPeriods + 1U) % rtm->localBuf.periods;
                rtm->localRtm.bufRtm.remainingPeriods =
                    (rtm->localRtm.bufRtm.remainingPeriods + 1U) % rtm->localBuf.periods;
            }
        }
    }
    else /* The localBuf is not used, the period size may exceed the max size supported by one DMA tranfer.*/
#endif
    {
        if (rtm->curXferIdx == rtm->countsPerPeriod) /* All the transfer in a period is done. */
        {
            rtm->curXferIdx = 1U;
            periodDone      = true;

            rtm->bufRtm.remainingPeriods--;
            chaseIdx               = rtm->bufRtm.chaseIdx; /* For callback */
            rtm->bufRtm.chaseIdx   = (rtm->bufRtm.chaseIdx + 1U) % rtm->periods;
            rtm->finishedBufOffset = rtm->bufRtm.chaseIdx * rtm->periodSize;

            /* Rx is always freeRun, we assume filled period is consumed immediately. */
            SRTM_SaiSdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);

            if ((adapter->service != NULL) && (adapter->periodDone != NULL))
            {
                /* Rx is always freeRun */
                if ((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL))
                {
                    (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
                }
            }
        }
        else
        {
            rtm->curXferIdx++;
            SRTM_SaiSdmaAdapter_DmaTransfer(handle, SRTM_AudioDirRx);
        }
    }

    if (periodDone)
    {
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
            ; /* Intentional empty. */
        }
    }
}
#endif

static void SRTM_SaiSdmaAdapter_InitSAI(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif

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
#if SRTM_SAI_CONFIG_Rx_Enabled
    else
    {
        SDMA_CreateHandle(&handle->rxDmaHandle, handle->dma, handle->rxConfig.dmaChannel, &handle->rxConfig.rxcontext);
        handle->rxDmaHandle.priority = handle->rxConfig.ChannelPriority;
        SAI_TransferRxCreateHandleSDMA(handle->sai, &handle->rxRtm.saiHandle, SRTM_SaiSdmaRxCallback, (void *)handle,
                                       &handle->rxDmaHandle, handle->rxConfig.eventSource);
    }
#endif
}

static void SRTM_SaiSdmaAdapter_DeinitSAI(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
    if (dir == SRTM_AudioDirTx)
    {
        SAI_TxReset(handle->sai);
    }
#if SRTM_SAI_CONFIG_Rx_Enabled
    else
    {
        SAI_RxReset(handle->sai);
    }
#endif
}

static void SRTM_SaiSdmaAdapter_ReconfigSAI(srtm_sai_adapter_t adapter,
                                            srtm_audio_dir_t dir,
                                            uint8_t format,
                                            uint32_t srate)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *cfg = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
    srtm_sai_sdma_config_t *cfg        = &handle->txConfig;
#endif
    uint32_t saiSrcClk;

    if ((format >= (uint8_t)SRTM_Audio_DSD8bits) && (format <= (uint8_t)SRTM_Audio_DSD32bits))
    {
        srate = srate / 2U;
    }

    if (((rtm->format != format) || (rtm->srate != srate)) && (cfg->extendConfig.audioDevConf != NULL))
    {
        saiSrcClk                       = cfg->extendConfig.audioDevConf((srtm_audio_format_type_t)format, srate);
        cfg->mclkConfig.mclkSourceClkHz = saiSrcClk;
        cfg->mclkConfig.mclkHz          = saiSrcClk;
    }
}

static void SRTM_SaiSdmaAdapter_SetFormat(srtm_sai_sdma_adapter_t handle, srtm_audio_dir_t dir)
{
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_config_t *cfg = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;
#else
    srtm_sai_sdma_config_t *cfg        = &handle->txConfig;
#endif
    srtm_sai_sdma_runtime_t rtm, paramRtm;
    uint8_t channels, bitWidth;
    bool sync = cfg->config.syncMode == kSAI_ModeSync;

#if SRTM_SAI_CONFIG_Rx_Enabled
    if (dir == SRTM_AudioDirTx)
    {
        rtm = &handle->txRtm;
        if (!rtm->paramSet)
        {
            /* There must be a path with param configured before start. */
            assert(handle->rxRtm.paramSet);
            paramRtm = &handle->rxRtm;
        }
        else
        {
            paramRtm = (sync && (handle->rxConfig.config.syncMode == kSAI_ModeAsync) && handle->rxRtm.paramSet) ?
                           &handle->rxRtm :
                           rtm;
        }
    }
    else
    {
        rtm = &handle->rxRtm;
        if (!rtm->paramSet)
        {
            /* There must be a path with param configured before start. */
            assert(handle->txRtm.paramSet);
            paramRtm = &handle->txRtm;
        }
        else
        {
            paramRtm = (sync && (handle->txConfig.config.syncMode == kSAI_ModeAsync) && handle->txRtm.paramSet) ?
                           &handle->txRtm :
                           rtm;
        }
    }
#else
    rtm                                = &handle->txRtm;
    paramRtm                           = rtm;
#endif

    channels                                   = paramRtm->streamMode == kSAI_Stereo ? 2U : 1U;
    bitWidth                                   = paramRtm->bitWidth == 24U ? 32U : paramRtm->bitWidth;
    cfg->config.serialData.dataMaskedWord      = (uint32_t)paramRtm->streamMode;
    cfg->config.serialData.dataWord0Length     = bitWidth;
    cfg->config.serialData.dataWordLength      = bitWidth;
    cfg->config.serialData.dataWordNLength     = bitWidth;
    cfg->config.serialData.dataFirstBitShifted = paramRtm->bitWidth;
    cfg->config.frameSync.frameSyncWidth       = bitWidth;

    /* set master clock to async mclk. */
    if (!sync)
    {
        SAI_SetMasterClockConfig(handle->sai, &cfg->mclkConfig);
    }

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
        SAI_TxSetBitClockRate(handle->sai, cfg->mclkConfig.mclkHz, paramRtm->srate, bitWidth, channels);
    }
#if SRTM_SAI_CONFIG_Rx_Enabled
    else
    {
        cfg->config.channelMask = 1U << cfg->dataLine1;
        SAI_TransferRxSetConfigSDMA(handle->sai, &rtm->saiHandle, &cfg->config);
        /* set bit clock */
        SAI_RxSetBitClockRate(handle->sai, cfg->mclkConfig.mclkHz, paramRtm->srate, bitWidth, channels);
    }
#endif
}

/* Currently only 1 audio instance is adequate, so index is just ignored */
static srtm_status_t SRTM_SaiSdmaAdapter_Open(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
    srtm_sai_sdma_config_t *thisCfg = dir == SRTM_AudioDirTx ? &handle->txConfig : &handle->rxConfig;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
    srtm_sai_sdma_config_t *thisCfg    = &handle->txConfig;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    /* Record the index */
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

    if (thisCfg->extendConfig.audioMclkConf != NULL)
    {
        thisCfg->extendConfig.audioMclkConf(handle->sai, &thisCfg->mclkConfig);
    }

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Start(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm;
    srtm_sai_sdma_config_t *thisCfg;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t otherRtm;
    srtm_sai_sdma_config_t *otherCfg;
    srtm_audio_dir_t otherDir;
#endif

#if SRTM_SAI_CONFIG_Rx_Enabled
    uint32_t *threshold = dir == SRTM_AudioDirTx ? &handle->txConfig.threshold : &handle->rxConfig.threshold;
    uint32_t *guardTime = dir == SRTM_AudioDirTx ? &handle->txConfig.guardTime : &handle->rxConfig.guardTime;
#else
    uint32_t *threshold                = &handle->txConfig.threshold;
    uint32_t *guardTime                = &handle->txConfig.guardTime;
#endif

    uint8_t channelNum;
    uint32_t guardPeroids;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);
#if SRTM_SAI_CONFIG_Rx_Enabled
    if (dir == SRTM_AudioDirTx)
    {
#endif
        thisRtm = &handle->txRtm;
        thisCfg = &handle->txConfig;
#if SRTM_SAI_CONFIG_Rx_Enabled
        otherRtm = &handle->rxRtm;
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
#endif

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
#if SRTM_SAI_CONFIG_Rx_Enabled
    if (otherRtm->state != SRTM_AudioStateStarted)
    {
#endif
        SAI_Init(handle->sai);
        if (thisCfg->extendConfig.audioDevInit != NULL)
        {
            thisCfg->extendConfig.audioDevInit(true);
        }
#if SRTM_SAI_CONFIG_Rx_Enabled
    }

    if (otherCfg->config.syncMode == kSAI_ModeSync)
    {
        /* The other direction in sync mode, it will initialize both directions. */
        if (otherRtm->state != SRTM_AudioStateStarted)
        {
            /* Only when the other direction is not started, we can initialize, else the device setting is reused. */
            SRTM_SaiSdmaAdapter_InitSAI(handle, dir);
            /* Use our own format. */
            SRTM_SaiSdmaAdapter_SetFormat(handle, dir);
        }
    }
    else
#endif
    {
        /* The other direction has dedicated clock, it will not initialize this direction.
           Do initialization by ourselves. */
        SRTM_SaiSdmaAdapter_InitSAI(handle, dir);
        /* Use our own format. */
        SRTM_SaiSdmaAdapter_SetFormat(handle, dir);

#if SRTM_SAI_CONFIG_Rx_Enabled
        if ((thisCfg->config.syncMode == kSAI_ModeSync) && (otherRtm->state != SRTM_AudioStateStarted))
        {
            /* This direction in sync mode and the other not started, need to initialize the other direction. */
            SRTM_SaiSdmaAdapter_InitSAI(handle, otherDir);
            /* Set other direction format to ours. */
            SRTM_SaiSdmaAdapter_SetFormat(handle, otherDir);
        }
#endif
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
        guardPeroids = (uint32_t)(((uint64_t)thisRtm->srate * thisRtm->bitWidth * channelNum * (*guardTime) +
                                   (uint64_t)thisRtm->periodSize * 8U * 1000U - 1U) /
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
    thisRtm->state = SRTM_AudioStateStarted;
    /* Reset buffer index */
    thisRtm->bufRtm.loadIdx    = thisRtm->bufRtm.chaseIdx;
    thisRtm->bufRtm.offset     = 0;
    thisRtm->finishedBufOffset = thisRtm->bufRtm.chaseIdx * thisRtm->periodSize;
    if (thisRtm->freeRun)
    {
        /* Assume buffer full in free run */
        thisRtm->readyIdx = thisRtm->bufRtm.leadIdx;
    }
#if SRTM_SAI_CONFIG_SupportLocalBuf
    SRTM_SaiSdmaAdaptor_ResetLocalBuf(thisRtm, dir);
#endif
    SRTM_SaiSdmaAdapter_AddNewPeriods(thisRtm, thisRtm->readyIdx);
    SRTM_SaiSdmaAdapter_Transfer(handle, dir);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_End(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, bool stop)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm;
    srtm_sai_sdma_config_t *thisCfg;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t otherRtm;
    srtm_sai_sdma_config_t *otherCfg;
    srtm_audio_dir_t otherDir;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

#if SRTM_SAI_CONFIG_Rx_Enabled
    if (dir == SRTM_AudioDirTx)
    {
#endif
        thisRtm = &handle->txRtm;
        thisCfg = &handle->txConfig;
#if SRTM_SAI_CONFIG_Rx_Enabled
        otherRtm = &handle->rxRtm;
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
#endif

    if (thisRtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (thisRtm->state == SRTM_AudioStateStarted)
    {
        if (dir == SRTM_AudioDirTx)
        {
            SAI_TransferTerminateSendSDMA(handle->sai, &thisRtm->saiHandle);
        }
#if SRTM_SAI_CONFIG_Rx_Enabled
        else
        {
            SAI_TransferTerminateReceiveSDMA(handle->sai, &thisRtm->saiHandle);
        }
#endif

#if SRTM_SAI_CONFIG_Rx_Enabled
        if (otherCfg->config.syncMode == kSAI_ModeSync)
        {
            /* The other direction in sync mode, it will deinitialize this direction when it's stopped. */
            if (otherRtm->state != SRTM_AudioStateStarted)
            {
#endif
                /* The other direction not started, we can deinitialize this direction. */
                SRTM_SaiSdmaAdapter_DeinitSAI(handle, dir);
#if SRTM_SAI_CONFIG_Rx_Enabled
            }
        }
        else
        {
            /* The other direction has dedicated clock, its stop will not affect this direction.
               Do deinitialization by ourselves. */
            SRTM_SaiSdmaAdapter_DeinitSAI(handle, dir);
            if ((thisCfg->config.syncMode == kSAI_ModeSync) && (otherRtm->state != SRTM_AudioStateStarted))
            {
                /* This direction in sync mode and the other not started, need to deinitialize the other direction. */
                SRTM_SaiSdmaAdapter_DeinitSAI(handle, otherDir);
            }
        }

        if (otherRtm->state != SRTM_AudioStateStarted)
        {
#endif
            /* If both Tx and Rx are not running, we can deinitialize this SAI instance. */
            SAI_Deinit(handle->sai);
            /* Deinit audio device. */
            if (thisCfg->extendConfig.audioDevInit != NULL)
            {
                thisCfg->extendConfig.audioDevInit(false);
            }
#if SRTM_SAI_CONFIG_Rx_Enabled
        }
#endif
    }

    thisCfg->threshold               = 1U;
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

static srtm_status_t SRTM_SaiSdmaAdapter_Stop(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    return SRTM_SaiSdmaAdapter_End(adapter, dir, index, true);
}

static srtm_status_t SRTM_SaiSdmaAdapter_Close(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif

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

    rtm->state    = SRTM_AudioStateClosed;
    rtm->paramSet = false;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_Pause(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (dir == SRTM_AudioDirTx)
    {
        /* Disable request */
        SAI_TxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, false);
        /* Disable SAI */
        SAI_TxEnable(handle->sai, false);
    }
#if SRTM_SAI_CONFIG_Rx_Enabled
    else
    {
        /* Disable request*/
        SAI_RxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, false);
        /* Disable SAI*/
        SAI_RxEnable(handle->sai, false);
    }
#endif

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
#if SRTM_SAI_CONFIG_Rx_Enabled
    else
    {
        /* Enable request */
        SAI_RxEnableDMA(handle->sai, kSAI_FIFORequestDMAEnable, true);
        /* Enable SAI */
        SAI_RxEnable(handle->sai, true);
    }
#endif

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_SetParam(
    srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint8_t format, uint8_t channels, uint32_t srate)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif
    uint32_t bytePerSample;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d. fmt %d, ch %d, srate %d\r\n", __func__, saiDirection[dir],
                       index, format, channels, srate);

    if (rtm->state != SRTM_AudioStateOpened)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s in wrong state %d!\r\n", __func__, saiDirection[dir],
                           rtm->state);
        return SRTM_Status_InvalidState;
    }

    if ((format > (uint8_t)SRTM_Audio_DSD32bits) || (channels >= ARRAY_SIZE(saiChannelMap)))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s: %s unsupported format or channels %d, %d!\r\n", __func__,
                           saiDirection[dir], format, channels);
        return SRTM_Status_InvalidParameter;
    }

    SRTM_SaiSdmaAdapter_ReconfigSAI(adapter, dir, format, srate);

    if (format >= (uint8_t)SRTM_Audio_DSD8bits)
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

    /* Caluate the max bytes can be done by each SDMA transfer. */
    bytePerSample    = ((uint32_t)(rtm->bitWidth) >> 3U) * (channels != 0U ? (uint32_t)channels : 1UL);
    rtm->maxXferSize = (uint32_t)SRTM_SDMA_MAX_TRANSFER_SIZE / bytePerSample * bytePerSample;

    rtm->format     = format;
    rtm->streamMode = saiChannelMap[channels];
    rtm->paramSet   = true;

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
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif
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

    rtm->countsPerPeriod = (rtm->periodSize + rtm->maxXferSize - 1U) / rtm->maxXferSize;
    rtm->curXferIdx      = 1U;

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
#if SRTM_SAI_CONFIG_Rx_Enabled
    if (dir == SRTM_AudioDirTx)
    {
#endif
        thisRtm = &handle->txRtm;
        thisCfg = &handle->txConfig;
#if SRTM_SAI_CONFIG_Rx_Enabled
    }
    else
    {
        thisRtm = &handle->rxRtm;
        thisCfg = &handle->rxConfig;
    }
#endif

    if ((thisRtm->state == SRTM_AudioStateStarted) && thisCfg->stopOnSuspend)
    {
        thisRtm->stoppedOnSuspend = true;
        status                    = SRTM_SaiSdmaAdapter_End(adapter, dir, index, false);
    }

    thisRtm->suspendState = SRTM_Suspended;

    return status;
}

#if SRTM_SAI_CONFIG_Rx_Enabled
static void SRTM_SaiSdmaAdapter_HostWakeProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;
    srtm_sai_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    /* Notify application if the host is waken by other reason. */
    if ((rtm->suspendState == SRTM_NotSuspended) && (rtm->dataCallback != NULL))
    {
        rtm->dataCallback(adapter, (void *)(0), 0U, rtm->dataCallbackParam);
    }
}
#endif

static srtm_status_t SRTM_SaiSdmaAdapter_Resume(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status           = SRTM_Status_Success;
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_sai_sdma_runtime_t thisRtm;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_procedure_t proc;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

#if SRTM_SAI_CONFIG_Rx_Enabled
    if (dir == SRTM_AudioDirTx)
    {
        thisRtm = &handle->txRtm;
    }
    else
    {
        thisRtm = &handle->rxRtm;
    }
#else
    thisRtm                            = &handle->txRtm;
#endif

    if (thisRtm->stoppedOnSuspend)
    {
        thisRtm->stoppedOnSuspend = false;
        status                    = SRTM_SaiSdmaAdapter_Start(adapter, dir, index);
    }

    thisRtm->suspendState = SRTM_NotSuspended;

#if SRTM_SAI_CONFIG_Rx_Enabled
    if ((dir == SRTM_AudioDirRx) && (thisRtm->dataCallback != NULL))
    {
        /* Call the dataCallback to notify the host is wakeup. */
        proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_HostWakeProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
        else
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: : proc busy!\r\n", __func__);
        }
    }
#endif
    return status;
}

static srtm_status_t SRTM_SaiSdmaAdapter_GetBufOffset(srtm_sai_adapter_t adapter,
                                                      srtm_audio_dir_t dir,
                                                      uint8_t index,
                                                      uint32_t *pOffset)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    *pOffset = rtm->finishedBufOffset;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_SaiSdmaAdapter_PeriodReady(srtm_sai_adapter_t adapter,
                                                     srtm_audio_dir_t dir,
                                                     uint8_t index,
                                                     uint32_t periodIdx)
{
    srtm_status_t status           = SRTM_Status_Success;
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm        = &handle->txRtm;
#endif

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
        /* The RX is alwasy free run. */
        if (dir == SRTM_AudioDirTx)
        {
            rtm->freeRun = false;
        }
        rtm->readyIdx = periodIdx;
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
    (void)memset(handle, 0, sizeof(struct _srtm_sai_sdma_adapter));

    handle->sai = sai;
    handle->dma = dma;
    if (txConfig != NULL)
    {
        (void)memcpy(&handle->txConfig, txConfig, sizeof(srtm_sai_sdma_config_t));
        handle->txRtm.proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_TxTransferProc, handle, NULL);
        assert(handle->txRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->txRtm.proc, SRTM_SaiSdmaAdapter_RecycleTxMessage, handle);
    }
#if SRTM_SAI_CONFIG_Rx_Enabled
    if (rxConfig != NULL)
    {
        (void)memcpy(&handle->rxConfig, rxConfig, sizeof(srtm_sai_sdma_config_t));
        handle->rxRtm.proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_RxTransferProc, handle, NULL);
        assert(handle->rxRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, SRTM_SaiSdmaAdapter_RecycleRxMessage, handle);
    }
#endif

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

#if SRTM_SAI_CONFIG_Rx_Enabled
    if (handle->rxRtm.proc != NULL)
    {
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, NULL, NULL);
        SRTM_Procedure_Destroy(handle->rxRtm.proc);
    }
#endif

    SRTM_Heap_Free(handle);
}

#if SRTM_SAI_CONFIG_SupportLocalBuf
static inline void SRTM_SaiSdmaAdapter_SetLocalBuf(srtm_sai_adapter_t adapter,
                                                   srtm_sai_sdma_local_buf_t *localBuf,
                                                   srtm_audio_dir_t dir)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
#if SRTM_SAI_CONFIG_Rx_Enabled
    srtm_sai_sdma_runtime_t rtm = dir == SRTM_AudioDirTx ? &handle->txRtm : &handle->rxRtm;
#else
    srtm_sai_sdma_runtime_t rtm = &handle->txRtm;
#endif

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (localBuf != NULL)
    {
        assert(localBuf->periods <= SRTM_SAI_SDMA_MAX_LOCAL_BUF_PERIODS);
        (void)memcpy(&rtm->localBuf, localBuf, sizeof(srtm_sai_sdma_local_buf_t));
    }
    else
    {
        rtm->localBuf.buf = NULL;
    }
}

void SRTM_SaiSdmaAdapter_SetTxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_sdma_local_buf_t *localBuf)
{
    SRTM_SaiSdmaAdapter_SetLocalBuf(adapter, localBuf, SRTM_AudioDirTx);
}

#if SRTM_SAI_CONFIG_Rx_Enabled
void SRTM_SaiSdmaAdapter_SetRxLocalBuf(srtm_sai_adapter_t adapter, srtm_sai_sdma_local_buf_t *localBuf)
{
    SRTM_SaiSdmaAdapter_SetLocalBuf(adapter, localBuf, SRTM_AudioDirRx);
}
#endif /* SRTM_SAI_CONFIG_Rx_Enabled */
#endif /* SRTM_SAI_CONFIG_SupportLocalBuf */

#if SRTM_SAI_CONFIG_Rx_Enabled
void SRTM_SaiSdmaAdapter_SetDataHandlerOnHostSuspend(srtm_sai_adapter_t adapter,
                                                     srtm_sai_sdma_data_callback_t cb,
                                                     void *param)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->rxRtm.dataCallback      = cb;
    handle->rxRtm.dataCallbackParam = param;
}

static void SRTM_SaiSdmaAdapter_ResumeHostProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)param1;
#if SRTM_SAI_CONFIG_SupportLocalBuf
    srtm_sai_sdma_runtime_t rtm = &handle->rxRtm;
#endif

    if (handle->rxRtm.suspendState == SRTM_Suspended)
    {
        handle->rxRtm.suspendState = SRTM_WakingUp;
        /* Copy the audio data from the local buffer to the remote in case the local buffer is overwritten during host
         * wakeup. */
#if SRTM_SAI_CONFIG_SupportLocalBuf
        if (rtm->localBuf.buf != NULL)
        {
            if (rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods)
            {
                SRTM_SaiSdmaAdapter_RxCopyData(handle);
            }
        }
#endif
    }
}

void SRTM_SaiSdmaAdapter_ResumeHost(srtm_sai_adapter_t adapter)
{
    srtm_sai_sdma_adapter_t handle = (srtm_sai_sdma_adapter_t)(void *)adapter;
    srtm_procedure_t proc;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    proc = SRTM_Procedure_Create(SRTM_SaiSdmaAdapter_ResumeHostProc, handle, NULL);
    if ((adapter->service != NULL) && (proc != NULL))
    {
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
    }
}
#endif
