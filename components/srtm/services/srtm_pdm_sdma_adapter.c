/*
 * Copyright 2021-2022 NXP
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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SRTM_SDMA_MAX_TRANSFER_SIZE 0xFFFFU

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
} *srtm_pdm_sdma_buf_runtime_t;

struct _srtm_pdm_sdma_local_runtime
{
    uint32_t periodSize;
    struct _srtm_pdm_sdma_buf_runtime bufRtm;
};

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
struct _srtm_pdm_ext_buf_sdma_handle
{
    sdma_handle_t rDmaHandle;        /* Extra buffer read DMA handle. */
    sdma_handle_t wDmaHandle;        /* Extra buffer write DMA handle. */
    sdma_context_data_t rDmaCtx;     /* Extra buffer read DMA context. */
    sdma_context_data_t wDmaCtx;     /* Extra buffer write DMA context. */
    sdma_buffer_descriptor_t bd[2U]; /* SDMA buffer descriptor used for extra buffer write. */
};
#endif

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
    struct _srtm_pdm_sdma_buf_runtime bufRtm;     /* buffer provided by audio client. */
    srtm_pdm_sdma_local_buf_t localBuf;
    struct _srtm_pdm_sdma_local_runtime localRtm; /* buffer set by application. */
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_pdm_sdma_ext_buf_t extBuf;
    struct _srtm_pdm_sdma_local_runtime extBufRtm; /* Extra buffer set by application. */
    bool extBufPumpRunning;                        /* Extra buffer pump is running. */
#endif
    bool freeRun; /* flag to indicate that no periodReady will be sent by audio client. */
    bool stoppedOnSuspend;
    bool paramSet;
    uint32_t finishedBufOffset;                   /* offset from bufAddr where the data transfer has completed. */
    srtm_pdm_sdma_suspend_state suspendState;     /* service state in client suspend. */
    srtm_pdm_sdma_data_callback_t dataCallback;   /* Callback function to provide data when client is suspend */
    void *dataCallbackParam;                      /* Callback function argument to be passed back to application */
#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
    srtm_pdm_sdma_hwvad_callback_t hwvadCallback; /* Callback function which is called when voice detacted by HWVAD. */
    void *hwvadCallbackParam;                     /* Callback function argument to be passed back to application */
#endif
} *srtm_pdm_sdma_runtime_t;

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
#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
    srtm_pdm_hwvad_config_t hwvadConfig;
#endif
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    struct _srtm_pdm_ext_buf_sdma_handle extBufDmaHandle; /* Extra buffer read/write DMA handle. */
#endif
} *srtm_pdm_sdma_adapter_t;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
static void SRTM_PdmSdmaAdapter_HwvadCallback(status_t status, void *userData);
#endif
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
static void SRTM_PdmSdmaAdapter_PumpExtraBuf(srtm_pdm_sdma_adapter_t handle);
static void SRTM_PdmSdmaAdapter_ExtPeriodCopyAndNotifyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2);
#endif
static void SRTM_PdmSdmaAdapter_CopyData(srtm_pdm_sdma_adapter_t handle);
static void SRTM_PdmSdmaAdapter_AddNewPeriods(srtm_pdm_sdma_runtime_t rtm, uint32_t periodIdx);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static const char *saiDirection[] = {"Rx", "Tx"};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_PdmSdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter, srtm_audio_state_t *pRxState)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    *pRxState = handle->rxRtm.state;
}

static void SRTM_PdmSdmaAdapter_LocalBufferUpdate(uint32_t *dest, uint32_t *src, uint32_t count)
{
    while (count != 0U)
    {
        *dest = *src;
        dest++;
        src++;
        count--;
    }
}

static void SRTM_PdmSdmaAdapter_RecycleRxMessage(srtm_message_t msg, void *param)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param;
    assert(handle->rxRtm.proc == NULL);

    handle->rxRtm.proc = msg;
}

static void SRTM_PdmSdmaAdaptor_ResetLocalBuf(srtm_pdm_sdma_runtime_t rtm)
{
    uint8_t bytePerSample;

    if (rtm->localBuf.buf != NULL)
    {
        (void)memset(&rtm->localRtm.bufRtm, 0, sizeof(struct _srtm_pdm_sdma_buf_runtime));

        bytePerSample = (rtm->bitWidth >> 3U) * rtm->pdmChannels;

        if (rtm->localBuf.samplesPerPeriod == 0U)
        {
            /* default: use numbers of periods defined for this buffer */
            if ((bytePerSample % SRTM_PDM_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT) != 0U)
            {
                bytePerSample *= SRTM_PDM_SDMA_MAX_LOCAL_PERIOD_ALIGNMENT;
            }
            rtm->localRtm.periodSize = rtm->localBuf.bufSize / rtm->localBuf.periods;
            rtm->localRtm.periodSize = rtm->localRtm.periodSize / bytePerSample * bytePerSample;
        }
        else
        {
            /* Compute number of periods in the buffer based on its size and the size of each period
             * which depends on the number of samples and the size of each sample */
            rtm->localRtm.periodSize = bytePerSample * rtm->localBuf.samplesPerPeriod;
            rtm->localBuf.periods    = rtm->localBuf.bufSize / rtm->localRtm.periodSize;
        }

        rtm->localRtm.bufRtm.remainingLoadPeriods = rtm->localBuf.periods;
        rtm->localRtm.bufRtm.remainingPeriods     = rtm->localBuf.periods;
    }
}

static status_t SRTM_PdmSdmaAdapter_PeriodReceiveSDMA(srtm_pdm_sdma_adapter_t handle)
{
    status_t status = kStatus_Success;
    uint32_t count;
    pdm_transfer_t xfer;
    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t bufRtm;

#if SRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS
    if (rtm->localBuf.buf == NULL)
    {
        /* Compiler can remove all code below supporting case where local buf isn't used. */
        return kStatus_Fail;
    }
#endif

    if (rtm->localBuf.buf != NULL)
    {
        bufRtm = &rtm->localRtm.bufRtm;

        xfer.dataSize = rtm->localRtm.periodSize;
        xfer.data     = rtm->localBuf.buf + bufRtm->loadIdx * rtm->localRtm.periodSize;
        status        = PDM_TransferReceiveSDMA(handle->pdm, &rtm->pdmHandle, &xfer);

        if (status != kStatus_Success)
        {
            /* Audio queue full */
            return status;
        }
        bufRtm->loadIdx = (bufRtm->loadIdx + 1U) % rtm->localBuf.periods;
        bufRtm->remainingLoadPeriods--;
    }
    else
    {
        bufRtm = &rtm->bufRtm;

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
    }

    return kStatus_Success;
}

static void SRTM_PdmSdmaAdapter_DmaTransfer(srtm_pdm_sdma_adapter_t handle)
{
    srtm_pdm_sdma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t bufRtm = (rtm->localBuf.buf != NULL) ? &rtm->localRtm.bufRtm : &rtm->bufRtm;
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

static void SRTM_PdmSdmaAdapter_PeriodCopyAndNotify(srtm_pdm_sdma_adapter_t handle)
{
    srtm_sai_adapter_t adapter  = &handle->adapter;
    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;
    uint32_t srcSize, dstSize, size;
    srtm_pdm_sdma_buf_runtime_t srcRtm, dstRtm;

    uint8_t *src, *dst;
    uint32_t primask;

    srcRtm = &rtm->localRtm.bufRtm;
    dstRtm = &rtm->bufRtm;

    if ((srcRtm->remainingPeriods != rtm->localBuf.periods) && (dstRtm->remainingPeriods != 0U))
    {
        src     = rtm->localBuf.buf + srcRtm->leadIdx * rtm->localRtm.periodSize;
        dst     = rtm->bufAddr + dstRtm->chaseIdx * rtm->periodSize;
        srcSize = rtm->localRtm.periodSize - srcRtm->offset;
        dstSize = rtm->periodSize - dstRtm->offset;
        size    = MIN(srcSize, dstSize);
        SRTM_PdmSdmaAdapter_LocalBufferUpdate((uint32_t *)(void *)(dst + dstRtm->offset),
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

            /* Rx is always freeRun, we assume filled period is consumed immediately. */
            SRTM_PdmSdmaAdapter_AddNewPeriods(rtm, dstRtm->chaseIdx);

            if ((adapter->service != NULL) && (adapter->periodDone != NULL))
            {
                (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
            }
        }
    }
}

static void SRTM_PdmSdmaAdapter_DataCopyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;

    /* More data need to be copied. */
    SRTM_PdmSdmaAdapter_CopyData(handle);
}

static void SRTM_PdmSdmaAdapter_CopyData(srtm_pdm_sdma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;

    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t srcRtm, dstRtm;
    srcRtm = &rtm->localRtm.bufRtm;
    dstRtm = &rtm->bufRtm;
    srtm_procedure_t proc;

    SRTM_PdmSdmaAdapter_PeriodCopyAndNotify(handle);

    /* More data need to be copied. */
    if ((srcRtm->remainingPeriods != rtm->localBuf.periods) && (dstRtm->remainingPeriods != 0U))
    {
        proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_DataCopyProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
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

    if (rtm->localBuf.buf != NULL)
    {
        if ((rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods) &&
            ((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL)))
        {
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
            if (!rtm->extBufPumpRunning)
#endif
            {
                SRTM_PdmSdmaAdapter_CopyData(handle);
            }
        }
    }

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
    uint8_t *bufAddr;
    uint32_t bufSize;

    if ((rtm->suspendState == SRTM_Suspended) && (rtm->dataCallback != NULL) && (chaseIdx != UINT32_MAX))
    {
        if (rtm->localBuf.buf != NULL)
        {
            bufAddr = rtm->localBuf.buf + chaseIdx * rtm->localRtm.periodSize;
            bufSize = rtm->localRtm.periodSize;
        }
        else
        {
            bufAddr = rtm->bufAddr + chaseIdx * rtm->periodSize;
            bufSize = rtm->periodSize;
        }

        rtm->dataCallback(adapter, (void *)(bufAddr), bufSize, rtm->dataCallbackParam);
    }

    if (rtm->state == SRTM_AudioStateStarted)
    {
        /* Trigger DMA if having more buffer to record. */
        SRTM_PdmSdmaAdapter_Transfer(handle);
    }
}

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
static void SRTM_PdmSdmaAdaptor_ResetExtBuf(srtm_pdm_sdma_runtime_t rtm)
{
    uint32_t periods = 0U;

    if ((rtm->extBuf.buf != NULL) && (rtm->localBuf.buf != NULL))
    {
        (void)memset(&rtm->extBufRtm.bufRtm, 0, sizeof(struct _srtm_pdm_sdma_buf_runtime));
        periods =
            rtm->localBuf.periods - rtm->localBuf.threshold; /* Local buffer periods for each ext buffer period. */
        rtm->extBufRtm.periodSize = rtm->localRtm.periodSize * periods;
        assert(rtm->extBufRtm.periodSize <= SRTM_SDMA_MAX_TRANSFER_SIZE);
        rtm->extBuf.periods                    = rtm->extBuf.bufSize / rtm->extBufRtm.periodSize;
        rtm->extBufRtm.bufRtm.remainingPeriods = rtm->extBuf.periods;

        if (rtm->extBuf.periods == 0U)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "The extra buffer is too small.\r\n");
        }
    }
}

static void SRTM_PdmSdmaAdapter_LocalBufFullDMACb(sdma_handle_t *dmahandle,
                                                  void *param,
                                                  bool transferDone,
                                                  uint32_t tcds)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    uint32_t periodsPerExt =
        rtm->localBuf.periods - rtm->localBuf.threshold; /* The number of localBuf periods for each extra buffer. */

    if (transferDone)
    {
        rtm->extBufRtm.bufRtm.remainingPeriods--;                            /* A period is filled. */
        rtm->extBufRtm.bufRtm.chaseIdx =
            (rtm->extBufRtm.bufRtm.chaseIdx + 1U) % rtm->extBuf.periods;     /* Move the write pointer. */

        if (rtm->extBufRtm.bufRtm.chaseIdx == rtm->extBufRtm.bufRtm.leadIdx) /* Extra buffer overwrite. */
        {
            rtm->extBufRtm.bufRtm.leadIdx = (rtm->extBufRtm.bufRtm.leadIdx + 1U) % rtm->extBuf.periods;
            rtm->extBufRtm.bufRtm.remainingPeriods++;
        }

        rtm->localRtm.bufRtm.leadIdx = (rtm->localRtm.bufRtm.leadIdx + periodsPerExt) % rtm->localBuf.periods;
        rtm->localRtm.bufRtm.remainingLoadPeriods = rtm->localRtm.bufRtm.remainingLoadPeriods + periodsPerExt;
        rtm->localRtm.bufRtm.remainingPeriods     = rtm->localRtm.bufRtm.remainingPeriods + periodsPerExt;
    }
}

static void SRTM_PdmSdmaAdapter_LocalBufFullProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle        = (srtm_pdm_sdma_adapter_t)param1;
    srtm_pdm_sdma_runtime_t rtm           = &handle->rxRtm;
    sdma_transfer_config_t transferConfig = {0U};
    bool lastBd                           = true;
    uint32_t periods                      = 0U;
    uint8_t *src, *dst;
    uint32_t size;

    uint32_t periodsPerExt =
        rtm->localBuf.periods - rtm->localBuf.threshold; /* local buffer periods number for each extra period */

    periods = rtm->localBuf.periods - rtm->localRtm.bufRtm.leadIdx;
    src     = rtm->localBuf.buf + rtm->localRtm.bufRtm.leadIdx * rtm->localRtm.periodSize;
    dst     = rtm->extBuf.buf + rtm->extBufRtm.bufRtm.chaseIdx * rtm->extBufRtm.periodSize;

    if (rtm->extBufPumpRunning)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "Warn:Local buffer full during extra buffer pump.\r\n");
    }

    SDMA_CreateHandle(&handle->extBufDmaHandle.wDmaHandle, handle->dma, rtm->extBuf.bufWriteDmaChannel,
                      &handle->extBufDmaHandle.wDmaCtx);
    SDMA_SetCallback(&handle->extBufDmaHandle.wDmaHandle, SRTM_PdmSdmaAdapter_LocalBufFullDMACb, handle);
    SDMA_InstallBDMemory(&handle->extBufDmaHandle.wDmaHandle, handle->extBufDmaHandle.bd, 2U);

    if (periods < periodsPerExt) /* The localbuf is a ringbuffer, there are more periods need to be copied. */
    {
        lastBd = false;
        size   = periods * rtm->localRtm.periodSize;

        SDMA_ConfigBufferDescriptor(&handle->extBufDmaHandle.bd[0], (uint32_t)src, (uint32_t)dst,
                                    kSDMA_TransferSize4Bytes, size, lastBd, lastBd, false, kSDMA_MemoryToMemory);
        SDMA_PrepareTransfer(&transferConfig, (uint32_t)src, (uint32_t)dst, sizeof(uint32_t), sizeof(uint32_t),
                             sizeof(uint32_t), size, 0U, kSDMA_PeripheralTypeMemory, kSDMA_MemoryToMemory);

        src = rtm->localBuf.buf; /* Return back to buffer start.*/
        dst = dst + size;

        size = (periodsPerExt - periods) * rtm->localRtm.periodSize;

        SDMA_ConfigBufferDescriptor(&handle->extBufDmaHandle.bd[1], (uint32_t)src, (uint32_t)dst,
                                    kSDMA_TransferSize4Bytes, size, true, true, false, kSDMA_MemoryToMemory);
    }
    else
    {
        lastBd = true;
        size   = periodsPerExt * rtm->localRtm.periodSize;

        SDMA_ConfigBufferDescriptor(&handle->extBufDmaHandle.bd[0], (uint32_t)src, (uint32_t)dst,
                                    kSDMA_TransferSize4Bytes, size, lastBd, lastBd, false, kSDMA_MemoryToMemory);
        SDMA_PrepareTransfer(&transferConfig, (uint32_t)src, (uint32_t)dst, sizeof(uint32_t), sizeof(uint32_t),
                             sizeof(uint32_t), size, 0U, kSDMA_PeripheralTypeMemory, kSDMA_MemoryToMemory);
    }

    SDMA_SubmitTransfer(&handle->extBufDmaHandle.wDmaHandle, &transferConfig);
    SDMA_SetChannelPriority(handle->dma, rtm->extBuf.bufWriteDmaChannel, rtm->extBuf.channelPriority);
    SDMA_StartTransfer(&handle->extBufDmaHandle.wDmaHandle);
}
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER */

static void SRTM_PdmSdmaRxCallback(PDM_Type *sai, pdm_sdma_handle_t *sdmaHandle, status_t status, void *userData)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)userData;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = UINT32_MAX;
    bool periodDone                = false;
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_procedure_t extProc;
#endif

#if SRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS
    if (rtm->localBuf.buf == NULL)
    {
        /* Compiler can remove all code below supporting case where local buf isn't used. */
        return;
    }
#endif

    /* When localBuf is used, the period size should not exceed the max size supported by one DMA tranfer. */
    if (rtm->localBuf.buf != NULL)
    {
        rtm->localRtm.bufRtm.remainingPeriods--;                       /* One of the local period is filled */

        chaseIdx                      = rtm->localRtm.bufRtm.chaseIdx; /* For callback */
        rtm->localRtm.bufRtm.chaseIdx = (rtm->localRtm.bufRtm.chaseIdx + 1U) % rtm->localBuf.periods;

        /* Rx is always freeRun, assume filled period is consumed immediately. */
        periodDone = true;
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
        /* If extra 2nd buffer is used. Copy the data from localbuffer to the extra buffer. During the extra buffer
         * pump, the local buffer may full again. */
        if (rtm->extBuf.buf != NULL)
        {
            if (((rtm->localRtm.bufRtm.chaseIdx + rtm->localBuf.threshold) % rtm->localBuf.periods) ==
                rtm->localRtm.bufRtm.leadIdx) /* Local RX buffer is almost full, backup the audio data. */
            {
                extProc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_LocalBufFullProc, handle, NULL);
                if ((adapter->service != NULL) && (extProc != NULL))
                {
                    (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, extProc);
                }
            }
        }
        else
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER */
        {
            if ((rtm->suspendState == SRTM_Suspended) && (rtm->dataCallback != NULL))
            {
                if (((rtm->localRtm.bufRtm.chaseIdx + rtm->localBuf.threshold) % rtm->localBuf.periods) ==
                    rtm->localRtm.bufRtm.leadIdx) /* Local RX buffer is full. Allow overwrite. */
                {
                    rtm->localRtm.bufRtm.leadIdx = (rtm->localRtm.bufRtm.leadIdx + 1U) %
                                                   rtm->localBuf.periods; /* Overwrite will happen, move the leadIdx. */
                    rtm->localRtm.bufRtm.remainingLoadPeriods =
                        (rtm->localRtm.bufRtm.remainingLoadPeriods + 1U) % rtm->localBuf.periods;
                    rtm->localRtm.bufRtm.remainingPeriods =
                        (rtm->localRtm.bufRtm.remainingPeriods + 1U) % rtm->localBuf.periods;
                }
            }
        }
    }
    else /* The localBuf is not used, the period size may exceed the max size supported by one DMA tranfer.*/
    {
        if (rtm->curXferIdx == rtm->countsPerPeriod) /* All the transfer in a period is done. */
        {
            rtm->curXferIdx = 1U;
            periodDone      = true;

            rtm->bufRtm.remainingPeriods--;
            chaseIdx               = rtm->bufRtm.chaseIdx; /* For callback. */
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
            }
        }
        else
        {
            rtm->curXferIdx++;
            SRTM_PdmSdmaAdapter_Transfer(handle);
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
            ; /* Intentional empty */
        }
    }
}

static void SRTM_PdmSdmaAdapter_InitPDM(srtm_pdm_sdma_adapter_t handle)
{
    PDM_Init(handle->pdm, (const pdm_config_t *)(&handle->rxConfig.config));

    SDMA_CreateHandle(&handle->rxDmaHandle, handle->dma, handle->rxConfig.dmaChannel, &handle->rxConfig.rxContext);
    handle->rxDmaHandle.priority =
        handle->rxConfig.channelPriority; /* The priority will be set in SDMA_StartTransfer. */

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

#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
    if (handle->hwvadConfig.mode == kSRTM_PDM_Hwvad_EnvelopeBasedMode)
    {
        PDM_SetHwvadInEnvelopeBasedMode(handle->pdm, &handle->hwvadConfig.hwvadConfig,
                                        &handle->hwvadConfig.noiseFilterConfig, &handle->hwvadConfig.zcdConfig,
                                        handle->hwvadConfig.signalGain);
    }

    if (handle->hwvadConfig.mode == kSRTM_PDM_Hwvad_EnergyBasedMode)
    {
        PDM_SetHwvadInEnergyBasedMode(handle->pdm, &handle->hwvadConfig.hwvadConfig,
                                      &handle->hwvadConfig.noiseFilterConfig, &handle->hwvadConfig.zcdConfig,
                                      handle->hwvadConfig.signalGain);
    }

    if (handle->hwvadConfig.mode != kSRTM_PDM_Hwvad_Disabled) /* Enable the Hwvad IRQ. */
    {
        PDM_EnableHwvadInterruptCallback(handle->pdm, SRTM_PdmSdmaAdapter_HwvadCallback, (void *)handle, true);
    }
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_HWVAD */
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
    SRTM_PdmSdmaAdaptor_ResetLocalBuf(thisRtm);
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    SRTM_PdmSdmaAdaptor_ResetExtBuf(thisRtm);
#endif
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
        PDM_TransferTerminateReceiveSDMA(handle->pdm, &thisRtm->pdmHandle);

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
    rtm->format      = format;

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

static void SRTM_PdmSdmaAdapter_HostWakeProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    /* Notify application if the host is waken by other reason. */
    if ((rtm->suspendState == SRTM_NotSuspended) && (rtm->dataCallback != NULL))
    {
        rtm->dataCallback(adapter, (void *)(0), 0U, rtm->dataCallbackParam);
    }
}

static srtm_status_t SRTM_PdmSdmaAdapter_Resume(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_pdm_sdma_adapter_t handle  = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t thisRtm = &handle->rxRtm;
    srtm_procedure_t proc;
#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_procedure_t extProc;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (thisRtm->stoppedOnSuspend)
    {
        thisRtm->stoppedOnSuspend = false;
        status                    = SRTM_PdmSdmaAdapter_Start(adapter, SRTM_AudioDirRx, index);
    }

    thisRtm->suspendState = SRTM_NotSuspended;

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
    /* In case the remote wake itself. Pump the extra buffer. */
    if ((thisRtm->extBuf.buf != NULL) && (!thisRtm->extBufPumpRunning))
    {
        if (thisRtm->extBufRtm.bufRtm.remainingPeriods < thisRtm->extBuf.periods)
        {
            /* Pump the audio data in extra buffer and then local buffer to remote. */
            extProc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_ExtPeriodCopyAndNotifyProc, handle, NULL);
            if ((adapter->service != NULL) && (extProc != NULL))
            {
                thisRtm->extBufPumpRunning = true;
                (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, extProc);
            }
        }
    }
#endif

    if ((dir == SRTM_AudioDirRx) && (thisRtm->dataCallback != NULL))
    {
        /* Call the dataCallback to notify the host is wakeup. */
        proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_HostWakeProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
        else
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: : proc busy!\r\n", __func__);
        }
    }

    return status;
}

void SRTM_PdmSdmaAdapter_SetRxLocalBuf(srtm_sai_adapter_t adapter, srtm_pdm_sdma_local_buf_t *localBuf)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (localBuf != NULL)
    {
        (void)memcpy(&rtm->localBuf, localBuf, sizeof(srtm_pdm_sdma_local_buf_t));
    }
    else
    {
        rtm->localBuf.buf = NULL;
    }
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
        /* RX is always free run. */
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
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    if (handle->rxRtm.suspendState == SRTM_Suspended)
    {
        handle->rxRtm.suspendState = SRTM_WakingUp;

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
        if (rtm->extBuf.buf != NULL)
        {
            if (rtm->extBufRtm.bufRtm.remainingPeriods < rtm->extBuf.periods)
            {
                rtm->extBufPumpRunning = true;
                /* Pump the audio data in extra buffer and then local buffer to remote. */
                SRTM_PdmSdmaAdapter_PumpExtraBuf(handle);
            }
        }
        /* ExtBuf not used, local buffer is used, only copy local buffer. */
        else if (rtm->localBuf.buf != NULL)
#else
        if (rtm->localBuf.buf != NULL)
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER */
        {
            if (rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods)
            {
                /* Copy the audio data from the local buffer to the remote in case the local buffer is overwritten
                 * during host wakeup. */
                SRTM_PdmSdmaAdapter_CopyData(handle);
            }
        }
        else
        {
            /* Intentional empty. */
        }
    }
}

#if SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER
void SRTM_PdmSdmaAdapter_SetRxExtBuf(srtm_sai_adapter_t adapter, srtm_pdm_sdma_ext_buf_t *extBuf)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    assert(adapter != NULL);
    assert(rtm->localBuf.buf != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s:[0x%x:0x%x]\r\n", __func__, rtm->extBuf.buf, rtm->extBuf.bufSize);

    if (extBuf != NULL)
    {
        (void)memcpy(&rtm->extBuf, extBuf, sizeof(srtm_pdm_sdma_ext_buf_t));
    }
    else
    {
        rtm->extBuf.buf = NULL;
    }
}

static void SRTM_PdmSdmaAdapter_DmaM2MCallback(sdma_handle_t *sdma_handle, void *param, bool transferDone, uint32_t bds)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param;

    srtm_sai_adapter_t adapter  = &handle->adapter;
    srtm_pdm_sdma_runtime_t rtm = &handle->rxRtm;
    srtm_pdm_sdma_buf_runtime_t srcRtm, dstRtm;

    srtm_procedure_t proc;

    srcRtm = &rtm->extBufRtm.bufRtm;
    dstRtm = &rtm->bufRtm;

    if (transferDone)
    {
        if (srcRtm->offset == rtm->extBufRtm.periodSize) /* A extra buffer period is copied. */
        {
            srcRtm->leadIdx = (srcRtm->leadIdx + 1U) % rtm->extBuf.periods;
            srcRtm->offset  = 0U;
            srcRtm->remainingPeriods++;
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

            /* Rx is always freeRun, we assume filled period is consumed immediately. */
            SRTM_PdmSdmaAdapter_AddNewPeriods(rtm, dstRtm->chaseIdx);

            if ((adapter->service != NULL) && (adapter->periodDone != NULL))
            {
                (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
            }
        }

        /* Pump more data. */
        proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_ExtPeriodCopyAndNotifyProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
    }
}

static void SRTM_PdmSdmaAdapter_DmaMemcpy(srtm_pdm_sdma_adapter_t handle, uint32_t *dest, uint32_t *src, uint32_t count)
{
    srtm_pdm_sdma_runtime_t rtm           = &handle->rxRtm;
    sdma_transfer_config_t transferConfig = {0U};

    SDMA_CreateHandle(&handle->extBufDmaHandle.rDmaHandle, handle->dma, rtm->extBuf.bufReadDmaChannel,
                      &handle->extBufDmaHandle.rDmaCtx);
    SDMA_SetCallback(&handle->extBufDmaHandle.rDmaHandle, SRTM_PdmSdmaAdapter_DmaM2MCallback, handle);

    SDMA_PrepareTransfer(&transferConfig, (uint32_t)src, (uint32_t)dest, sizeof(dest[0]), sizeof(dest[0]),
                         sizeof(src[0]), count, 0, kSDMA_PeripheralTypeMemory, kSDMA_MemoryToMemory);
    SDMA_SubmitTransfer(&handle->extBufDmaHandle.rDmaHandle, &transferConfig);
    SDMA_SetChannelPriority(handle->dma, rtm->extBuf.bufReadDmaChannel, rtm->extBuf.channelPriority);
    SDMA_StartTransfer(&handle->extBufDmaHandle.rDmaHandle);
}

static void SRTM_PdmSdmaAdapter_ExtPeriodCopyAndNotifyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    uint32_t srcSize, dstSize, size;
    srtm_pdm_sdma_buf_runtime_t srcRtm, dstRtm;

    uint8_t *src, *dst;

    srcRtm = &rtm->extBufRtm.bufRtm;
    dstRtm = &rtm->bufRtm;

    if (rtm->state == SRTM_AudioStateStarted)
    {
        if ((srcRtm->remainingPeriods != rtm->extBuf.periods) && (dstRtm->remainingPeriods != 0U))
        {
            src     = rtm->extBuf.buf + srcRtm->leadIdx * rtm->extBufRtm.periodSize;
            dst     = rtm->bufAddr + dstRtm->chaseIdx * rtm->periodSize;
            srcSize = rtm->extBufRtm.periodSize - srcRtm->offset;
            dstSize = rtm->periodSize - dstRtm->offset;
            size    = MIN(srcSize, dstSize);

            SRTM_PdmSdmaAdapter_DmaMemcpy(handle, (uint32_t *)(void *)(dst + dstRtm->offset),
                                          (uint32_t *)(void *)(src + srcRtm->offset), size);

            srcRtm->offset += size;
            dstRtm->offset += size;
        }
        else
        {
            rtm->extBufPumpRunning = false;
            /* Pump local buffer ASAP. */
            if (rtm->localBuf.buf != NULL)
            {
                if (rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods)
                {
                    SRTM_PdmSdmaAdapter_CopyData(handle);
                }
            }
        }
    }
    else
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s:in wrong state %d during data pump!\r\n", __func__,
                           rtm->state);
    }
}

/* Pump Extra buffer, if no audio data in extra buffer it will start local buffer pump. */
static void SRTM_PdmSdmaAdapter_PumpExtraBuf(srtm_pdm_sdma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;

    SRTM_PdmSdmaAdapter_ExtPeriodCopyAndNotifyProc(adapter->service->dispatcher, handle, NULL);
}
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_EXTRA_BUFFER */

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

srtm_audio_format_type_t SRTM_PdmSdmaAdapter_GetDataFormat(srtm_sai_adapter_t adapter)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;

    return (srtm_audio_format_type_t)rtm->format;
}

#if SRTM_PDM_SDMA_ADAPTER_USE_HWVAD
static void SRTM_PdmSdmaAdapter_HwvadProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)param1;
    srtm_pdm_sdma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    if ((rtm->hwvadCallback != NULL) && (rtm->state == SRTM_AudioStateStarted))
    {
        rtm->hwvadCallback(adapter, rtm->hwvadCallbackParam);
    }
}

static void SRTM_PdmSdmaAdapter_HwvadCallback(status_t status, void *userData)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)userData;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    srtm_procedure_t proc;

    if (status == kStatus_PDM_HWVAD_VoiceDetected)
    {
        proc = SRTM_Procedure_Create(SRTM_PdmSdmaAdapter_HwvadProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
    }
}

srtm_status_t SRTM_PdmSdmaAdapter_ConfigHwvad(srtm_sai_adapter_t adapter,
                                              const srtm_pdm_hwvad_config_t *hwvadConfig,
                                              srtm_pdm_sdma_hwvad_callback_t cb,
                                              void *param)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;
    srtm_status_t status           = SRTM_Status_Success;

    assert(adapter != NULL);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (handle->rxRtm.state == SRTM_AudioStateStarted) /* The HWVAD should be configured before start. */
    {
        status = SRTM_Status_InvalidState;
    }
    else
    {
        handle->rxRtm.hwvadCallback      = cb;
        handle->rxRtm.hwvadCallbackParam = param;

        (void)memcpy(&handle->hwvadConfig, hwvadConfig, sizeof(srtm_pdm_hwvad_config_t));
    }

    return status;
}

void SRTM_PdmSdmaAdapter_EnableHwvad(srtm_sai_adapter_t adapter, bool enable)
{
    srtm_pdm_sdma_adapter_t handle = (srtm_pdm_sdma_adapter_t)(void *)adapter;

    assert(adapter != NULL);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (enable)
    {
        if (handle->rxRtm.state == SRTM_AudioStateStarted)
        {
            PDM_EnableHwvadInterruptCallback(handle->pdm, SRTM_PdmSdmaAdapter_HwvadCallback, (void *)adapter, true);
        }
    }
    else
    {
        if (handle->rxRtm.state == SRTM_AudioStateStarted)
        {
            PDM_EnableHwvadInterruptCallback(handle->pdm, NULL, NULL, false);
        }
    }
}
#endif /* SRTM_PDM_SDMA_ADAPTER_USE_HWVAD */
