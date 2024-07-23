/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>

#include "srtm_pdm_edma_adapter.h"
#include "srtm_heap.h"
#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET)
#include "fsl_memory.h"
#endif
#include "fsl_pdm.h"
#include "fsl_pdm_edma.h"
#include "srtm_dispatcher.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"
#include "srtm_service_struct.h"

#if SRTM_DDR_RETENTION_USED
#include "lpm.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SRTM_EDMA_MAX_TRANSFER_SIZE 0xFFFFU

typedef enum _srtm_pdm_edma_suspend_state
{
    SRTM_NotSuspended,
    SRTM_Suspended,
    SRTM_WakingUp,
} srtm_pdm_edma_suspend_state;

typedef struct _srtm_pdm_edma_buf_runtime
{
    uint32_t leadIdx;          /* ready period index for playback or recording. */
    uint32_t chaseIdx;         /* consumed period index for recording. */
    uint32_t loadIdx;          /* used to indicate period index preloaded either to DMA transfer or to local buffer. */
    uint32_t remainingPeriods; /* periods to be consumed/filled */
    uint32_t remainingLoadPeriods; /* periods to be preloaded either to DMA transfer or to local buffer. */
    uint32_t offset;               /* period offset, non-zero value means current period is not finished. */
} *srtm_pdm_edma_buf_runtime_t;

struct _srtm_pdm_edma_local_runtime
{
    uint32_t periodSize;
    struct _srtm_pdm_edma_buf_runtime bufRtm;
};

#define TCD_QUEUE_SIZE 2U
AT_QUICKACCESS_SECTION_DATA_ALIGN(static edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE], sizeof(edma_tcd_t));
AT_QUICKACCESS_SECTION_DATA_ALIGN(static edma_tcd_t tcdMemoryPoolPtrMem2Mem[TCD_QUEUE_SIZE], sizeof(edma_tcd_t));
static volatile bool g_w_Transfer_Done = false;
static volatile bool g_w_Transfer_End  = false;
static volatile bool g_r_Transfer_Done = false;

struct _srtm_pdm_ext_buf_edma_handle
{
    edma_handle_t rDmaHandle; /* Extra buffer read DMA handle. */
    edma_handle_t wDmaHandle; /* Extra buffer write DMA handle. */
};

typedef struct _srtm_pdm_edma_runtime
{
    srtm_audio_state_t state;
    pdm_edma_handle_t pdmHandle;
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
    struct _srtm_pdm_edma_buf_runtime bufRtm;     /* buffer provided by audio client. */
    srtm_pdm_edma_local_buf_t localBuf;
    struct _srtm_pdm_edma_local_runtime localRtm; /* buffer set by application. */
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_pdm_edma_ext_buf_t extBuf;
    struct _srtm_pdm_edma_local_runtime extBufRtm; /* Extra buffer set by application. */
    bool extBufPumpRunning;                        /* Extra buffer pump is running. */
#endif
    bool freeRun; /* flag to indicate that no periodReady will be sent by audio client. */
    bool stoppedOnSuspend;
    bool paramSet;
    uint32_t finishedBufOffset;                   /* offset from bufAddr where the data transfer has completed. */
    srtm_pdm_edma_suspend_state suspendState;     /* service state in client suspend. */
    srtm_pdm_edma_data_callback_t dataCallback;   /* Callback function to provide data when client is suspend */
    void *dataCallbackParam;                      /* Callback function argument to be passed back to application */
#if SRTM_PDM_EDMA_ADAPTER_USE_HWVAD
    srtm_pdm_edma_hwvad_callback_t hwvadCallback; /* Callback function which is called when voice detacted by HWVAD. */
    void *hwvadCallbackParam;                     /* Callback function argument to be passed back to application */
#endif
} *srtm_pdm_edma_runtime_t;

/* SAI EDMA adapter */
typedef struct _srtm_pdm_edma_adapter
{
    struct _srtm_sai_adapter adapter;
    uint32_t index;

    PDM_Type *pdm;
    EDMA_Type *dma;
    srtm_pdm_edma_config_t rxConfig;
    edma_handle_t rxDmaHandle;
    struct _srtm_pdm_edma_runtime rxRtm;
#if SRTM_PDM_EDMA_ADAPTER_USE_HWVAD
    srtm_pdm_hwvad_config_t hwvadConfig;
#endif
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    struct _srtm_pdm_ext_buf_edma_handle extBufDmaHandle; /* Extra buffer read/write DMA handle. */
#endif
} *srtm_pdm_edma_adapter_t;

/* Data injection.
 * bootloader can modify this value afer having started this application
 * and before starting Linux. According to the values read when Linux
 * starts the corresponding audio device, then Cortex-M will switch to data
 * injection mode, reading data from the provided address in memory.
 * This is important that these variables are located in a specific section in
 * linker script so that their address don't change at each compilation, and
 * thus easier to locate for bootloader.
 */
#if SRTM_PDM_EDMA_DATA_INJECTION
typedef struct
{
    /* Need to be kept in same positions to avoid confusion for users.*/
    uint32_t data_inject_mode;
    uint8_t *data_inject_addr;
    uint32_t data_inject_size;
    uint32_t data_inject_idx;
} data_inject_ctrl_t;
__attribute__((section(".bss.DataInject"))) data_inject_ctrl_t data_inject_ctrl = {0};
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if SRTM_PDM_EDMA_ADAPTER_USE_HWVAD
static void SRTM_PdmEdmaAdapter_HwvadCallback(status_t status, void *userData);
#endif
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
static void SRTM_PdmEdmaAdapter_PumpExtraBuf(srtm_pdm_edma_adapter_t handle);
static void SRTM_PdmEdmaAdapter_ExtPeriodCopyAndNotifyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2);
static void SRTM_PdmEdmaAdapter_DmaM2MCallback(edma_handle_t *edma_handle,
                                               void *param,
                                               bool transferDone,
                                               uint32_t bds);
#endif
static void SRTM_PdmEdmaAdapter_CopyData(srtm_pdm_edma_adapter_t handle);
static void SRTM_PdmEdmaAdapter_AddNewPeriods(srtm_pdm_edma_runtime_t rtm, uint32_t periodIdx);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#ifdef SRTM_DEBUG_MESSAGE_FUNC
static const char *saiDirection[] = {"Rx", "Tx"};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void SRTM_PdmEdmaAdapter_GetAudioServiceState(srtm_sai_adapter_t adapter, srtm_audio_state_t *pRxState)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    *pRxState = handle->rxRtm.state;
}

static void SRTM_PdmEdmaAdapter_LocalBufferUpdate(uint32_t *dest, uint32_t *src, uint32_t count)
{
    while (count != 0U)
    {
        *dest = *src;
        dest++;
        src++;
        count--;
    }
}

static void SRTM_PdmEdmaAdapter_RecycleRxMessage(srtm_message_t msg, void *param)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param;
    assert(handle->rxRtm.proc == NULL);

    handle->rxRtm.proc = msg;
}

static void SRTM_PdmEdmaAdaptor_ResetLocalBuf(srtm_pdm_edma_runtime_t rtm)
{
    uint8_t bytePerSample;

    if (rtm->localBuf.buf != NULL)
    {
        (void)memset(&rtm->localRtm.bufRtm, 0, sizeof(struct _srtm_pdm_edma_buf_runtime));

        bytePerSample = (rtm->bitWidth >> 3U) * rtm->pdmChannels;

        if (rtm->localBuf.samplesPerPeriod == 0U)
        {
            /* default: use numbers of periods defined for this buffer */
            if ((bytePerSample % SRTM_PDM_EDMA_MAX_LOCAL_PERIOD_ALIGNMENT) != 0U)
            {
                bytePerSample *= SRTM_PDM_EDMA_MAX_LOCAL_PERIOD_ALIGNMENT;
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

static status_t SRTM_PdmEdmaAdapter_PeriodReceiveEDMA(srtm_pdm_edma_adapter_t handle)
{
    status_t status = kStatus_Success;
    uint32_t count;
    pdm_edma_transfer_t xfer;
    srtm_pdm_edma_runtime_t rtm = &handle->rxRtm;
    srtm_pdm_edma_buf_runtime_t bufRtm;

#if SRTM_PDM_EDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS
    if (rtm->localBuf.buf == NULL)
    {
        /* Compiler can remove all code below supporting case where local buf isn't used. */
        return kStatus_Fail;
    }
#endif

    (void)memset(&xfer, 0, sizeof(xfer));

    if (rtm->localBuf.buf != NULL)
    {
        bufRtm = &rtm->localRtm.bufRtm;

        xfer.dataSize = rtm->localRtm.periodSize;
        xfer.data     = rtm->localBuf.buf + bufRtm->loadIdx * rtm->localRtm.periodSize;
        status        = PDM_TransferReceiveEDMA(handle->pdm, &rtm->pdmHandle, &xfer);

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
            status        = PDM_TransferReceiveEDMA(handle->pdm, &rtm->pdmHandle, &xfer);
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
            status        = PDM_TransferReceiveEDMA(handle->pdm, &rtm->pdmHandle, &xfer);
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

static void SRTM_PdmEdmaAdapter_DmaTransfer(srtm_pdm_edma_adapter_t handle)
{
    srtm_pdm_edma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_edma_buf_runtime_t bufRtm = (rtm->localBuf.buf != NULL) ? &rtm->localRtm.bufRtm : &rtm->bufRtm;
    uint32_t i;
    status_t status;
    uint32_t num;

    num = bufRtm->remainingLoadPeriods;

    for (i = 0U; i < num; i++)
    {
        status = SRTM_PdmEdmaAdapter_PeriodReceiveEDMA(handle);

        if (status != kStatus_Success)
        {
            /* Audio queue full. */
            break;
        }
    }
}

static void SRTM_PdmEdmaAdapter_PeriodCopyAndNotify(srtm_pdm_edma_adapter_t handle)
{
    srtm_sai_adapter_t adapter  = &handle->adapter;
    srtm_pdm_edma_runtime_t rtm = &handle->rxRtm;
    uint32_t srcSize, dstSize, size;
    srtm_pdm_edma_buf_runtime_t srcRtm, dstRtm;

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
#if SRTM_DDR_RETENTION_USED
        LPM_ddr_pre_access();
#endif
        SRTM_PdmEdmaAdapter_LocalBufferUpdate((uint32_t *)(void *)(dst + dstRtm->offset),
                                              (uint32_t *)(void *)(src + srcRtm->offset), size / 4U);
#if SRTM_DDR_RETENTION_USED
#if SRTM_PDM_EDMA_DATA_INJECTION
        if (data_inject_ctrl.data_inject_mode == 0)
#endif
        {
            LPM_ddr_post_access();
        }
#endif

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
            SRTM_PdmEdmaAdapter_AddNewPeriods(rtm, dstRtm->chaseIdx);

            if ((adapter->service != NULL) && (adapter->periodDone != NULL))
            {
                (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
            }
        }
    }
}

static void SRTM_PdmEdmaAdapter_DataCopyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;

    /* More data need to be copied. */
    SRTM_PdmEdmaAdapter_CopyData(handle);
}

static void SRTM_PdmEdmaAdapter_CopyData(srtm_pdm_edma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;

    srtm_pdm_edma_runtime_t rtm = &handle->rxRtm;
    srtm_pdm_edma_buf_runtime_t srcRtm, dstRtm;
    srcRtm = &rtm->localRtm.bufRtm;
    dstRtm = &rtm->bufRtm;
    srtm_procedure_t proc;

    SRTM_PdmEdmaAdapter_PeriodCopyAndNotify(handle);

    /* More data need to be copied. */
    if ((srcRtm->remainingPeriods != rtm->localBuf.periods) && (dstRtm->remainingPeriods != 0U))
    {
        proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_DataCopyProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
    }
}

static void SRTM_PdmEdmaAdapter_AddNewPeriods(srtm_pdm_edma_runtime_t rtm, uint32_t periodIdx)
{
    srtm_pdm_edma_buf_runtime_t bufRtm = &rtm->bufRtm;
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

static void SRTM_PdmEdmaAdapter_Transfer(srtm_pdm_edma_adapter_t handle)
{
    srtm_pdm_edma_runtime_t rtm = &handle->rxRtm;

    /* Trigger DMA if having more data to playback/record. */
    SRTM_PdmEdmaAdapter_DmaTransfer(handle);

    if (rtm->localBuf.buf != NULL)
    {
        if ((rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods) &&
            ((rtm->suspendState != SRTM_Suspended) || (rtm->dataCallback == NULL)))
        {
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
            if (!rtm->extBufPumpRunning)
#endif
            {
                SRTM_PdmEdmaAdapter_CopyData(handle);
            }
        }
    }

    if (rtm->freeRun && (rtm->bufRtm.remainingPeriods < rtm->periods))
    {
        /* In free run, we assume consumed period is filled immediately. */
        SRTM_PdmEdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);
    }
}

static void SRTM_PdmEdmaAdapter_RxTransferProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
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
        SRTM_PdmEdmaAdapter_Transfer(handle);
    }
}

#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
static void SRTM_PdmEdmaAdaptor_ResetExtBuf(srtm_pdm_edma_runtime_t rtm)
{
    uint32_t periods = 0U;

    if ((rtm->extBuf.buf != NULL) && (rtm->localBuf.buf != NULL))
    {
        (void)memset(&rtm->extBufRtm.bufRtm, 0, sizeof(struct _srtm_pdm_edma_buf_runtime));
        periods =
            rtm->localBuf.periods - rtm->localBuf.threshold; /* Local buffer periods for each ext buffer period. */
        rtm->extBufRtm.periodSize = rtm->localRtm.periodSize * periods;
        assert(rtm->extBufRtm.periodSize <= SRTM_EDMA_MAX_TRANSFER_SIZE);
        rtm->extBuf.periods                    = rtm->extBuf.bufSize / rtm->extBufRtm.periodSize;
        rtm->extBufRtm.bufRtm.remainingPeriods = rtm->extBuf.periods;

        if (rtm->extBuf.periods == 0U)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "The extra buffer is too small.\r\n");
        }
    }
}

static void SRTM_PdmEdmaAdapter_LocalBufFullDMACb(edma_handle_t *dmahandle,
                                                  void *param,
                                                  bool transferDone,
                                                  uint32_t tcds)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    uint32_t periodsPerExt =
        rtm->localBuf.periods - rtm->localBuf.threshold; /* The number of localBuf periods for each extra buffer. */

    if (transferDone)
    {
        g_w_Transfer_Done = true;
        if (g_w_Transfer_End)
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
}

static void SRTM_PdmEdmaAdapter_LocalBufFullProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle        = (srtm_pdm_edma_adapter_t)param1;
    srtm_pdm_edma_runtime_t rtm           = &handle->rxRtm;
    edma_transfer_config_t transferConfig = {0U};
    uint32_t periods                      = 0U;
    uint8_t *src, *dst;
    uint32_t size;

    uint32_t periodsPerExt =
        rtm->localBuf.periods - rtm->localBuf.threshold; /* local buffer periods number for each extra period */

    periods = rtm->localBuf.periods - rtm->localRtm.bufRtm.leadIdx;
    src     = rtm->localBuf.buf + rtm->localRtm.bufRtm.leadIdx * rtm->localRtm.periodSize;
    dst     = rtm->extBuf.buf + rtm->extBufRtm.bufRtm.chaseIdx * rtm->extBufRtm.periodSize;

    if (rtm->extBuf.buff_access_cb != NULL)
    {
        rtm->extBuf.buff_access_cb(true);
    }

    if (periods < periodsPerExt) /* The localbuf is a ringbuffer, there are more periods need to be copied. */
    {
        size = periods * rtm->localRtm.periodSize;

        EDMA_PrepareTransfer(&transferConfig, (void *)src, sizeof(uint32_t), (void *)dst, sizeof(uint32_t), size, size,
                             kEDMA_MemoryToMemory);

        EDMA_ResetChannel(rtm->extBuf.mem2memDmaBase, rtm->extBuf.bufWriteDmaChannel);
        (void)EDMA_SubmitTransfer(&handle->extBufDmaHandle.wDmaHandle, &transferConfig);

        src = rtm->localBuf.buf; /* Return back to buffer start.*/
        dst = dst + size;

        size             = (periodsPerExt - periods) * rtm->localRtm.periodSize;
        g_w_Transfer_End = false; // Don't update circular buffer indexes when this first partial transfer is done

        EDMA_PrepareTransfer(&transferConfig, (void *)src, sizeof(uint32_t), (void *)dst, sizeof(uint32_t), size, size,
                             kEDMA_MemoryToMemory);
        (void)EDMA_SubmitTransfer(&handle->extBufDmaHandle.wDmaHandle, &transferConfig);

        /* Trigger transfer start */
        EDMA_StartTransfer(&handle->extBufDmaHandle.wDmaHandle);
        /* Wait for the first TCD finished */
        while (g_w_Transfer_Done != true)
        {
        }
        g_w_Transfer_Done = false;
        g_w_Transfer_End  = true; // circular buffers indexes can be updated when this final transfer is complete
        /* Trigger the second tcd */
        EDMA_StartTransfer(&handle->extBufDmaHandle.wDmaHandle);
        /* Wait for the second TCD finished */
        while (g_w_Transfer_Done != true)
        {
        }
        g_w_Transfer_Done = false;
    }
    else
    {
        size             = periodsPerExt * rtm->localRtm.periodSize;
        g_w_Transfer_End = true; // circular buffers indexes can be updated when this final transfer is complete
        EDMA_PrepareTransfer(&transferConfig, (void *)src, sizeof(uint32_t), (void *)dst, sizeof(uint32_t), size, size,
                             kEDMA_MemoryToMemory);

        EDMA_ResetChannel(rtm->extBuf.mem2memDmaBase, rtm->extBuf.bufWriteDmaChannel);
        (void)EDMA_SubmitTransfer(&handle->extBufDmaHandle.wDmaHandle, &transferConfig);

        /* Trigger transfer start */
        EDMA_StartTransfer(&handle->extBufDmaHandle.wDmaHandle);
        /* Wait for the first TCD finished */
        while (g_w_Transfer_Done != true)
        {
        }
        g_w_Transfer_Done = false;
    }

    if (rtm->extBuf.buff_access_cb != NULL)
    {
        rtm->extBuf.buff_access_cb(false);
    }
}
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER */

static void SRTM_PdmEdmaRxCallback(PDM_Type *sai, pdm_edma_handle_t *edmaHandle, status_t status, void *userData)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)userData;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    uint32_t chaseIdx              = UINT32_MAX;
    bool periodDone                = false;
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_procedure_t extProc;
#endif
#if SRTM_PDM_EDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS
    if (rtm->localBuf.buf == NULL)
    {
        /* Compiler can remove all code below supporting case where local buf isn't used. */
        return;
    }
#endif

    /* When localBuf is used, the period size should not exceed the max size supported by one DMA tranfer. */
    if (rtm->localBuf.buf != NULL)
    {
#if SRTM_PDM_EDMA_DATA_INJECTION
        if (data_inject_ctrl.data_inject_mode != 0)
        {
#if SRTM_DDR_RETENTION_USED
            /* Ensure DDR is not in retention (could have been done by another process) */
            LPM_ddr_pre_access();
#endif
            /* loop to beginning of the file */
            if (data_inject_ctrl.data_inject_idx + rtm->localRtm.periodSize > data_inject_ctrl.data_inject_size)
            {
                data_inject_ctrl.data_inject_idx = 0;
            }
            /* overwrite data received by DMA with test data */
            memcpy(rtm->localBuf.buf + rtm->localRtm.bufRtm.chaseIdx * rtm->localRtm.periodSize,
                   data_inject_ctrl.data_inject_addr + data_inject_ctrl.data_inject_idx, rtm->localRtm.periodSize);
            data_inject_ctrl.data_inject_idx += rtm->localRtm.periodSize;
        }
#endif

        rtm->localRtm.bufRtm.remainingPeriods--;                       /* One of the local period is filled */

        chaseIdx                      = rtm->localRtm.bufRtm.chaseIdx; /* For callback */
        rtm->localRtm.bufRtm.chaseIdx = (rtm->localRtm.bufRtm.chaseIdx + 1U) % rtm->localBuf.periods;

        /* Rx is always freeRun, assume filled period is consumed immediately. */
        periodDone = true;
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
        /* If extra 2nd buffer is used. Copy the data from localbuffer to the extra buffer. During the extra buffer
         * pump, the local buffer may full again. */
        if (rtm->extBuf.buf != NULL)
        {
            if (((rtm->localRtm.bufRtm.chaseIdx + rtm->localBuf.threshold) % rtm->localBuf.periods) ==
                rtm->localRtm.bufRtm.leadIdx) /* Local RX buffer is almost full, backup the audio data. */
            {
                extProc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_LocalBufFullProc, handle, NULL);
                if ((adapter->service != NULL) && (extProc != NULL))
                {
                    (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, extProc);
                }
            }
        }
        else
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER */
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
            SRTM_PdmEdmaAdapter_AddNewPeriods(rtm, rtm->bufRtm.chaseIdx);

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
            SRTM_PdmEdmaAdapter_Transfer(handle);
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

static void SRTM_PdmEdmaAdapter_InitPDM(srtm_pdm_edma_adapter_t handle)
{
    PDM_Init(handle->pdm, (const pdm_config_t *)(&handle->rxConfig.config));

    EDMA_CreateHandle(&handle->rxDmaHandle, handle->dma, handle->rxConfig.dmaChannel);

    PDM_TransferCreateHandleEDMA(handle->pdm, &handle->rxRtm.pdmHandle, SRTM_PdmEdmaRxCallback, (void *)handle,
                                 &handle->rxDmaHandle);
    PDM_TransferInstallEDMATCDMemory(&handle->rxRtm.pdmHandle, tcdMemoryPoolPtr, TCD_QUEUE_SIZE);
}

static void SRTM_PdmEdmaAdapter_SetConfig(srtm_pdm_edma_adapter_t handle)
{
    srtm_pdm_edma_runtime_t rtm = &handle->rxRtm;
    uint32_t ch                 = 0;

    /* There must be a path with parameters configured before start. */
    assert(handle->rxRtm.paramSet);

    for (ch = 0; ch < rtm->pdmChannels; ch++)
    {
        PDM_TransferSetChannelConfigEDMA(handle->pdm, &rtm->pdmHandle, ch, &handle->rxConfig.channelConfig);
    }

    (void)PDM_SetSampleRateConfig(handle->pdm, handle->rxConfig.pdmSrcClk, rtm->srate);

    PDM_Reset(handle->pdm);

#if SRTM_PDM_EDMA_ADAPTER_USE_HWVAD
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
        PDM_EnableHwvadInterruptCallback(handle->pdm, SRTM_PdmEdmaAdapter_HwvadCallback, (void *)handle, true);
    }
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_HWVAD */
}

static void SRTM_PdmEdmaAdapter_DeinitPDM(srtm_pdm_edma_adapter_t handle)
{
    assert(handle != NULL);
    PDM_Reset(handle->pdm);
    PDM_Deinit(handle->pdm);
}

/* Currently only 1 audio instance is adequate, so index is just ignored */
static srtm_status_t SRTM_PdmEdmaAdapter_Open(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    /* Only support RX. */
    assert(dir == SRTM_AudioDirRx);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

#if SRTM_PDM_EDMA_DATA_INJECTION
    if (data_inject_ctrl.data_inject_mode != 0)
    {
        PRINTF("test mode 0x%x src :0x%x len:0x%x \r\n", data_inject_ctrl.data_inject_mode,
               data_inject_ctrl.data_inject_addr, data_inject_ctrl.data_inject_size);
        data_inject_ctrl.data_inject_idx = 0;
    }
#endif

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

static srtm_status_t SRTM_PdmEdmaAdapter_Start(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_edma_adapter_t handle  = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_edma_config_t *thisCfg = &handle->rxConfig;
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    edma_config_t userConfig;
#endif

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
        SRTM_PdmEdmaAdapter_InitPDM(handle);
        /* Use our own format. */
        SRTM_PdmEdmaAdapter_SetConfig(handle);
    }

#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    if ((thisRtm->extBuf.buf != NULL) && (thisRtm->extBuf.mem2memDmaBase != NULL))
    {
        EDMA_GetDefaultConfig(&userConfig);
        EDMA_Init(thisRtm->extBuf.mem2memDmaBase, &userConfig);

        EDMA_CreateHandle(&handle->extBufDmaHandle.rDmaHandle, thisRtm->extBuf.mem2memDmaBase,
                          thisRtm->extBuf.bufReadDmaChannel);
        EDMA_SetCallback(&handle->extBufDmaHandle.rDmaHandle, SRTM_PdmEdmaAdapter_DmaM2MCallback, handle);
        EDMA_ResetChannel(thisRtm->extBuf.mem2memDmaBase, thisRtm->extBuf.bufReadDmaChannel);

        EDMA_CreateHandle(&handle->extBufDmaHandle.wDmaHandle, thisRtm->extBuf.mem2memDmaBase,
                          thisRtm->extBuf.bufWriteDmaChannel);
        EDMA_SetCallback(&handle->extBufDmaHandle.wDmaHandle, SRTM_PdmEdmaAdapter_LocalBufFullDMACb, handle);
        EDMA_ResetChannel(thisRtm->extBuf.mem2memDmaBase, thisRtm->extBuf.bufWriteDmaChannel);
        EDMA_InstallTCDMemory(&handle->extBufDmaHandle.wDmaHandle, tcdMemoryPoolPtrMem2Mem, TCD_QUEUE_SIZE);
    }
#endif

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
    SRTM_PdmEdmaAdaptor_ResetLocalBuf(thisRtm);
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    SRTM_PdmEdmaAdaptor_ResetExtBuf(thisRtm);
#endif
    SRTM_PdmEdmaAdapter_AddNewPeriods(thisRtm, thisRtm->readyIdx);
    SRTM_PdmEdmaAdapter_Transfer(handle);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_End(srtm_sai_adapter_t adapter, uint8_t index, bool stop)
{
    srtm_pdm_edma_adapter_t handle  = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_edma_config_t *thisCfg = &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %d\r\n", __func__, index);

    if (thisRtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (thisRtm->state == SRTM_AudioStateStarted)
    {
        PDM_TransferTerminateReceiveEDMA(handle->pdm, &thisRtm->pdmHandle);

        SRTM_PdmEdmaAdapter_DeinitPDM(handle);

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

static srtm_status_t SRTM_PdmEdmaAdapter_Stop(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    assert(dir == SRTM_AudioDirRx);

    return SRTM_PdmEdmaAdapter_End(adapter, index, true);
}

static srtm_status_t SRTM_PdmEdmaAdapter_Close(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (rtm->state == SRTM_AudioStateClosed)
    {
        /* Stop may called when audio service reset. */
        return SRTM_Status_Success;
    }

    if (rtm->state != SRTM_AudioStateOpened)
    {
        (void)SRTM_PdmEdmaAdapter_End(adapter, index, true);
    }

    rtm->state    = SRTM_AudioStateClosed;
    rtm->paramSet = false;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_Pause(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);
    /* Disable request*/
    PDM_EnableDMA(handle->pdm, false);
    /* Disable PDM*/
    PDM_Enable(handle->pdm, false);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_Restart(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    assert(dir == SRTM_AudioDirRx);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    PDM_EnableDMA(handle->pdm, true);
    PDM_Enable(handle->pdm, true);

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_SetParam(
    srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index, uint8_t format, uint8_t channels, uint32_t srate)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    srtm_pdm_edma_config_t *cfg    = &handle->rxConfig;
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

    /* Caluate the max bytes can be done by each EDMA transfer. */
    bytePerSample    = ((uint32_t)rtm->bitWidth >> 3U) * channels;
    rtm->maxXferSize = (uint32_t)SRTM_EDMA_MAX_TRANSFER_SIZE / bytePerSample * bytePerSample;

    rtm->srate       = srate;
    rtm->pdmChannels = channels;
    rtm->format      = format;

    rtm->paramSet = true;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_SetBuf(srtm_sai_adapter_t adapter,
                                                srtm_audio_dir_t dir,
                                                uint8_t index,
                                                uint8_t *bufAddr,
                                                uint32_t bufSize,
                                                uint32_t periodSize,
                                                uint32_t periodIdx)
{
    srtm_pdm_edma_adapter_t handle     = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm        = &handle->rxRtm;
    srtm_pdm_edma_buf_runtime_t bufRtm = &rtm->bufRtm;

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

static srtm_status_t SRTM_PdmEdmaAdapter_Suspend(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_pdm_edma_adapter_t handle  = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t thisRtm = &handle->rxRtm;
    srtm_pdm_edma_config_t *thisCfg = &handle->rxConfig;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if ((thisRtm->state == SRTM_AudioStateStarted) && thisCfg->stopOnSuspend)
    {
        thisRtm->stoppedOnSuspend = true;
        status                    = SRTM_PdmEdmaAdapter_End(adapter, index, false);
    }

    thisRtm->suspendState = SRTM_Suspended;

    return status;
}

static void SRTM_PdmEdmaAdapter_HostWakeProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    /* Notify application if the host is waken by other reason. */
    if ((rtm->suspendState == SRTM_NotSuspended) && (rtm->dataCallback != NULL))
    {
        rtm->dataCallback(adapter, (void *)(0), 0U, rtm->dataCallbackParam);
    }
}

static srtm_status_t SRTM_PdmEdmaAdapter_Resume(srtm_sai_adapter_t adapter, srtm_audio_dir_t dir, uint8_t index)
{
    srtm_status_t status            = SRTM_Status_Success;
    srtm_pdm_edma_adapter_t handle  = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t thisRtm = &handle->rxRtm;
    srtm_procedure_t proc;
#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    srtm_procedure_t extProc;
#endif

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    if (thisRtm->stoppedOnSuspend)
    {
        thisRtm->stoppedOnSuspend = false;
        status                    = SRTM_PdmEdmaAdapter_Start(adapter, SRTM_AudioDirRx, index);
    }

    thisRtm->suspendState = SRTM_NotSuspended;

#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
    /* In case the remote wake itself. Pump the extra buffer. */
    if ((thisRtm->extBuf.buf != NULL) && (!thisRtm->extBufPumpRunning))
    {
        if (thisRtm->extBufRtm.bufRtm.remainingPeriods < thisRtm->extBuf.periods)
        {
            /* Pump the audio data in extra buffer and then local buffer to remote. */
            extProc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_ExtPeriodCopyAndNotifyProc, handle, NULL);
            if ((adapter->service != NULL) && (extProc != NULL))
            {
                thisRtm->extBufPumpRunning = true;
#if SRTM_DDR_RETENTION_USED
                LPM_ddr_pre_access();
#endif
                (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, extProc);
            }
        }
    }
#endif

    if ((dir == SRTM_AudioDirRx) && (thisRtm->dataCallback != NULL))
    {
        /* Call the dataCallback to notify the host is wakeup. */
        proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_HostWakeProc, handle, NULL);
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

void SRTM_PdmEdmaAdapter_SetRxLocalBuf(srtm_sai_adapter_t adapter, srtm_pdm_edma_local_buf_t *localBuf)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (localBuf != NULL)
    {
        (void)memcpy(&rtm->localBuf, localBuf, sizeof(srtm_pdm_edma_local_buf_t));
    }
    else
    {
        rtm->localBuf.buf = NULL;
    }
}

static srtm_status_t SRTM_PdmEdmaAdapter_GetBufOffset(srtm_sai_adapter_t adapter,
                                                      srtm_audio_dir_t dir,
                                                      uint8_t index,
                                                      uint32_t *pOffset)
{
    assert(dir == SRTM_AudioDirRx);

    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s%d\r\n", __func__, saiDirection[dir], index);

    *pOffset = rtm->finishedBufOffset;

    return SRTM_Status_Success;
}

static srtm_status_t SRTM_PdmEdmaAdapter_PeriodReady(srtm_sai_adapter_t adapter,
                                                     srtm_audio_dir_t dir,
                                                     uint8_t index,
                                                     uint32_t periodIdx)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_status_t status           = SRTM_Status_Success;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

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

srtm_sai_adapter_t SRTM_PdmEdmaAdapter_Create(PDM_Type *pdm, EDMA_Type *dma, srtm_pdm_edma_config_t *rxConfig)
{
    srtm_pdm_edma_adapter_t handle;

    assert((pdm != NULL) && (dma != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_pdm_edma_adapter_t)SRTM_Heap_Malloc(sizeof(struct _srtm_pdm_edma_adapter));
    assert(handle != NULL);
    (void)memset(handle, 0, sizeof(struct _srtm_pdm_edma_adapter));

    handle->pdm = pdm;
    handle->dma = dma;

    if (rxConfig != NULL)
    {
        (void)memcpy(&handle->rxConfig, rxConfig, sizeof(srtm_pdm_edma_config_t));
        handle->rxRtm.proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_RxTransferProc, handle, NULL);
        assert(handle->rxRtm.proc != NULL);
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, SRTM_PdmEdmaAdapter_RecycleRxMessage, handle);
    }

    /* Adapter interfaces. */
    handle->adapter.open         = SRTM_PdmEdmaAdapter_Open;
    handle->adapter.start        = SRTM_PdmEdmaAdapter_Start;
    handle->adapter.pause        = SRTM_PdmEdmaAdapter_Pause;
    handle->adapter.restart      = SRTM_PdmEdmaAdapter_Restart;
    handle->adapter.stop         = SRTM_PdmEdmaAdapter_Stop;
    handle->adapter.close        = SRTM_PdmEdmaAdapter_Close;
    handle->adapter.setParam     = SRTM_PdmEdmaAdapter_SetParam;
    handle->adapter.setBuf       = SRTM_PdmEdmaAdapter_SetBuf;
    handle->adapter.suspend      = SRTM_PdmEdmaAdapter_Suspend;
    handle->adapter.resume       = SRTM_PdmEdmaAdapter_Resume;
    handle->adapter.getBufOffset = SRTM_PdmEdmaAdapter_GetBufOffset;
    handle->adapter.periodReady  = SRTM_PdmEdmaAdapter_PeriodReady;

    return &handle->adapter;
}

void SRTM_PdmEdmaAdapter_Destroy(srtm_sai_adapter_t adapter)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (handle->rxRtm.proc != NULL)
    {
        SRTM_Message_SetFreeFunc(handle->rxRtm.proc, NULL, NULL);
        SRTM_Procedure_Destroy(handle->rxRtm.proc);
    }

    SRTM_Heap_Free(handle);
}

void SRTM_PdmEdmaAdapter_SetDataHandlerOnHostSuspend(srtm_sai_adapter_t adapter,
                                                     srtm_pdm_edma_data_callback_t cb,
                                                     void *param)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle->rxRtm.dataCallback      = cb;
    handle->rxRtm.dataCallbackParam = param;
}

static void SRTM_PdmEdmaAdapter_ResumeHostProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    if (handle->rxRtm.suspendState == SRTM_Suspended)
    {
        handle->rxRtm.suspendState = SRTM_WakingUp;

#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
        if (rtm->extBuf.buf != NULL)
        {
            if (rtm->extBufRtm.bufRtm.remainingPeriods < rtm->extBuf.periods)
            {
                rtm->extBufPumpRunning = true;
                /* Pump the audio data in extra buffer and then local buffer to remote. */
                SRTM_PdmEdmaAdapter_PumpExtraBuf(handle);
            }
        }
        /* ExtBuf not used, local buffer is used, only copy local buffer. */
        else if (rtm->localBuf.buf != NULL)
#else
        if (rtm->localBuf.buf != NULL)
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER */
        {
            if (rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods)
            {
                /* Copy the audio data from the local buffer to the remote in case the local buffer is overwritten
                 * during host wakeup. */
                SRTM_PdmEdmaAdapter_CopyData(handle);
            }
        }
        else
        {
            /* Intentional empty. */
        }
    }
}

#if SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER
void SRTM_PdmEdmaAdapter_SetRxExtBuf(srtm_sai_adapter_t adapter, srtm_pdm_edma_ext_buf_t *extBuf)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    assert(adapter != NULL);
    assert(rtm->localBuf.buf != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s:[0x%x:0x%x]\r\n", __func__, rtm->extBuf.buf, rtm->extBuf.bufSize);

    if (extBuf != NULL)
    {
        (void)memcpy(&rtm->extBuf, extBuf, sizeof(srtm_pdm_edma_ext_buf_t));
    }
    else
    {
        rtm->extBuf.buf = NULL;
    }
    /* callback configured through a dedicated API to keep compatibility */
    rtm->extBuf.buff_access_cb = NULL;
}

void SRTM_PdmEdmaAdapter_SetRxExtBufAccessCb(srtm_sai_adapter_t adapter, buff_access_enable cb_func)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    rtm->extBuf.buff_access_cb = cb_func;
}

static void SRTM_PdmEdmaAdapter_DmaM2MCallback(edma_handle_t *edma_handle, void *param, bool transferDone, uint32_t bds)
{
    g_r_Transfer_Done = transferDone;
}

static void SRTM_PdmEdmaAdapter_DmaMemcpy(srtm_pdm_edma_adapter_t handle, uint32_t *dest, uint32_t *src, uint32_t count)
{
    edma_transfer_config_t transferConfig = {0U};
    srtm_pdm_edma_runtime_t rtm           = &handle->rxRtm;

    EDMA_PrepareTransfer(&transferConfig, (void *)src, sizeof(dest[0]), (void *)dest, sizeof(dest[0]), count, count,
                         kEDMA_MemoryToMemory);

    g_r_Transfer_Done = false;
    EDMA_ResetChannel(rtm->extBuf.mem2memDmaBase, rtm->extBuf.bufReadDmaChannel);
    (void)EDMA_SubmitTransfer(&handle->extBufDmaHandle.rDmaHandle, &transferConfig);
    EDMA_StartTransfer(&handle->extBufDmaHandle.rDmaHandle);

    while (g_r_Transfer_Done != true)
    {
    }
}

static void SRTM_PdmEdmaAdapter_ExtPeriodCopyAndNotifyProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    uint32_t srcSize, dstSize, size;
    srtm_pdm_edma_buf_runtime_t srcRtm, dstRtm;

    uint8_t *src, *dst;
    srtm_procedure_t proc;

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

#if SRTM_DDR_RETENTION_USED
            LPM_ddr_pre_access();
#endif
            SRTM_PdmEdmaAdapter_DmaMemcpy(handle, (uint32_t *)(void *)(dst + dstRtm->offset),
                                          (uint32_t *)(void *)(src + srcRtm->offset), size);

            srcRtm->offset += size;
            dstRtm->offset += size;

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
                dstRtm->remainingPeriods--; /* Now one of the remote buffer has been consumed. Assume the ready period
                                               is consumed by host immediately. */
                dstRtm->remainingLoadPeriods--; /* Unused. */
                rtm->finishedBufOffset = dstRtm->chaseIdx * rtm->periodSize;
                dstRtm->offset         = 0U;

                /* Rx is always freeRun, we assume filled period is consumed immediately. */
                SRTM_PdmEdmaAdapter_AddNewPeriods(rtm, dstRtm->chaseIdx);

                if ((adapter->service != NULL) && (adapter->periodDone != NULL))
                {
                    (void)adapter->periodDone(adapter->service, SRTM_AudioDirRx, handle->index, rtm->bufRtm.chaseIdx);
                }
            }

            /* Pump more data. */
            proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_ExtPeriodCopyAndNotifyProc, handle, NULL);
            if ((adapter->service != NULL) && (proc != NULL))
            {
                (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
            }
        }
        else
        {
            rtm->extBufPumpRunning = false;
#if SRTM_DDR_RETENTION_USED
#if SRTM_PDM_EDMA_DATA_INJECTION
            if (data_inject_ctrl.data_inject_mode == 0)
#endif
            {
                LPM_ddr_post_access();
            }
#endif
            /* Pump local buffer ASAP. */
            if (rtm->localBuf.buf != NULL)
            {
                if (rtm->localRtm.bufRtm.remainingPeriods < rtm->localBuf.periods)
                {
                    SRTM_PdmEdmaAdapter_CopyData(handle);
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
static void SRTM_PdmEdmaAdapter_PumpExtraBuf(srtm_pdm_edma_adapter_t handle)
{
    srtm_sai_adapter_t adapter = &handle->adapter;
    srtm_procedure_t proc;

    proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_ExtPeriodCopyAndNotifyProc, handle, NULL);
    if ((adapter->service != NULL) && (proc != NULL))
    {
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
    }
}
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_EXTRA_BUFFER */

void SRTM_PdmEdmaAdapter_ResumeHost(srtm_sai_adapter_t adapter)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_procedure_t proc;

    assert(adapter != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_ResumeHostProc, handle, NULL);
    if ((adapter->service != NULL) && (proc != NULL))
    {
        (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
    }
}

srtm_audio_format_type_t SRTM_PdmEdmaAdapter_GetDataFormat(srtm_sai_adapter_t adapter)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;

    return (srtm_audio_format_type_t)rtm->format;
}

#if SRTM_PDM_EDMA_ADAPTER_USE_HWVAD
static void SRTM_PdmEdmaAdapter_HwvadProc(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)param1;
    srtm_pdm_edma_runtime_t rtm    = &handle->rxRtm;
    srtm_sai_adapter_t adapter     = &handle->adapter;

    if ((rtm->hwvadCallback != NULL) && (rtm->state == SRTM_AudioStateStarted))
    {
        rtm->hwvadCallback(adapter, rtm->hwvadCallbackParam);
    }
}

static void SRTM_PdmEdmaAdapter_HwvadCallback(status_t status, void *userData)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)userData;
    srtm_sai_adapter_t adapter     = &handle->adapter;
    srtm_procedure_t proc;

    if (status == kStatus_PDM_HWVAD_VoiceDetected)
    {
        proc = SRTM_Procedure_Create(SRTM_PdmEdmaAdapter_HwvadProc, handle, NULL);
        if ((adapter->service != NULL) && (proc != NULL))
        {
            (void)SRTM_Dispatcher_PostProc(adapter->service->dispatcher, proc);
        }
    }
}

srtm_status_t SRTM_PdmEdmaAdapter_ConfigHwvad(srtm_sai_adapter_t adapter,
                                              const srtm_pdm_hwvad_config_t *hwvadConfig,
                                              srtm_pdm_edma_hwvad_callback_t cb,
                                              void *param)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;
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

void SRTM_PdmEdmaAdapter_EnableHwvad(srtm_sai_adapter_t adapter, bool enable)
{
    srtm_pdm_edma_adapter_t handle = (srtm_pdm_edma_adapter_t)(void *)adapter;

    assert(adapter != NULL);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    if (enable)
    {
        if (handle->rxRtm.state == SRTM_AudioStateStarted)
        {
            PDM_EnableHwvadInterruptCallback(handle->pdm, SRTM_PdmEdmaAdapter_HwvadCallback, (void *)adapter, true);
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
#endif /* SRTM_PDM_EDMA_ADAPTER_USE_HWVAD */
