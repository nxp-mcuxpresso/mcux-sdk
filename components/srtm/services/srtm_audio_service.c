/*
 * Copyright 2017-2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>

#include "fsl_common.h"

#include "srtm_heap.h"
#include "srtm_list.h"
#include "srtm_dispatcher.h"
#include "srtm_service.h"
#include "srtm_service_struct.h"
#include "srtm_audio_service.h"
#include "srtm_message.h"
#include "srtm_message_struct.h"
#include "srtm_channel.h"
#include "srtm_channel_struct.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Protocol definition */
#define SRTM_AUDIO_CATEGORY (0x3U)

#define SRTM_AUDIO_VERSION (0x0102U)

#define SRTM_AUDIO_RETURN_CODE_SUCEESS     (0x0U)
#define SRTM_AUDIO_RETURN_CODE_FAIL        (0x1U)
#define SRTM_AUDIO_RETURN_CODE_UNSUPPORTED (0x2U)

/* Audio Service Request Command definition */
#define SRTM_AUDIO_CMD_TX_OPEN           (0x0U)
#define SRTM_AUDIO_CMD_TX_START          (0x1U)
#define SRTM_AUDIO_CMD_TX_PAUSE          (0x2U)
#define SRTM_AUDIO_CMD_TX_RESTART        (0x3U)
#define SRTM_AUDIO_CMD_TX_STOP           (0x4U)
#define SRTM_AUDIO_CMD_TX_CLOSE          (0x5U)
#define SRTM_AUDIO_CMD_TX_SET_PARAM      (0x6U)
#define SRTM_AUDIO_CMD_TX_SET_BUF        (0x7U)
#define SRTM_AUDIO_CMD_TX_SUSPEND        (0x8U)
#define SRTM_AUDIO_CMD_TX_RESUME         (0x9U)
#define SRTM_AUDIO_CMD_RX_OPEN           (0xAU)
#define SRTM_AUDIO_CMD_RX_START          (0xBU)
#define SRTM_AUDIO_CMD_RX_PAUSE          (0xCU)
#define SRTM_AUDIO_CMD_RX_RESTART        (0xDU)
#define SRTM_AUDIO_CMD_RX_STOP           (0xEU)
#define SRTM_AUDIO_CMD_RX_CLOSE          (0xFU)
#define SRTM_AUDIO_CMD_RX_SET_PARAM      (0x10U)
#define SRTM_AUDIO_CMD_RX_SET_BUF        (0x11U)
#define SRTM_AUDIO_CMD_RX_SUSPEND        (0x12U)
#define SRTM_AUDIO_CMD_RX_RESUME         (0x13U)
#define SRTM_AUDIO_CMD_SET_CODEC_REG     (0x14U)
#define SRTM_AUDIO_CMD_GET_CODEC_REG     (0x15U)
#define SRTM_AUDIO_CMD_TX_GET_BUF_OFFSET (0x16U)
#define SRTM_AUDIO_CMD_RX_GET_BUF_OFFSET (0x17U)

/* Audio Service Notification Command definition */
#define SRTM_AUDIO_NTF_TX_PERIOD_DONE (0x0U)
#define SRTM_AUDIO_NTF_RX_PERIOD_DONE (0x1U)

/* Audio Service Sample Format definition */
#define SRTM_AUDIO_SAMPLE_FORMAT_S16_LE (0x0U)
#define SRTM_AUDIO_SAMPLE_FORMAT_S24_LE (0x1U)

/* Audio Service Channel identifier definition */
#define SRTM_AUDIO_CHANNEL_LEFT   (0x0U)
#define SRTM_AUDIO_CHANNEL_RIGHT  (0x1U)
#define SRTM_AUDIO_CHANNEL_STEREO (0x2U)

/* Service handle */
typedef struct _srtm_audio_service
{
    struct _srtm_service service;
    srtm_list_t ifaces;
} * srtm_audio_service_t;

/* Audio interface */
typedef struct _srtm_audio_iface
{
    srtm_list_t node;
    uint8_t index;
    srtm_sai_adapter_t sai;
    srtm_codec_adapter_t codec;
    /* Only 1 peer core is allowed to use the audio interface at any time */
    srtm_channel_t channel;
    srtm_list_t freeProcs;
    uint32_t useCount;
} * srtm_audio_iface_t;

srtm_audio_format_map_t saiFormatMap[6] = {{SRTM_Audio_Stereo16Bits, 16U}, {SRTM_Audio_Stereo24Bits, 24U},
                                           {SRTM_Audio_Stereo32Bits, 32U}, {SRTM_Audio_DSD8bits, 8U},
                                           {SRTM_Audio_DSD16bits, 16U},    {SRTM_Audio_DSD32bits, 32U}};
static uint8_t s_audIdx;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static srtm_audio_iface_t SRTM_AudioService_FindInterface(srtm_audio_service_t handle, uint8_t index);
static srtm_audio_iface_t SRTM_AudioService_FindInterfaceByChannel(srtm_audio_service_t handle, srtm_channel_t channel);
static srtm_audio_iface_t SRTM_AudioService_FindInterfaceByAdapter(srtm_audio_service_t handle, srtm_sai_adapter_t sai);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SRTM_AudioService_RecycleMessage(srtm_message_t msg, void *param)
{
    uint32_t primask;
    srtm_audio_iface_t iface = (srtm_audio_iface_t)param;

    /* Put message back to freeProcs */
    primask = DisableGlobalIRQ();
    SRTM_List_AddTail(&iface->freeProcs, &msg->node);
    EnableGlobalIRQ(primask);
}

/* CALLED IN SRTM DISPATCHER TASK */
static void SRTM_AudioService_HandlePeriodDone(srtm_dispatcher_t dispatcher,
                                               srtm_audio_dir_t dir,
                                               srtm_audio_service_t handle,
                                               uint32_t index)
{
    srtm_notification_t notif;
    struct _srtm_audio_payload *payload;
    uint32_t audioIdx        = index >> 24U;
    uint32_t periodIdx       = index & 0xFFFFFFU;
    srtm_audio_iface_t iface = SRTM_AudioService_FindInterface(handle, (uint8_t)audioIdx);

    assert((iface != NULL) && (iface->channel != NULL));

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s: %s\r\n", __func__, dir == SRTM_AudioDirTx ? "Tx" : "Rx");

    /* First allocate a notification and send to peer core */
    notif =
        SRTM_Notification_Create(iface->channel, SRTM_AUDIO_CATEGORY, SRTM_AUDIO_VERSION,
                                 dir == SRTM_AudioDirTx ? SRTM_AUDIO_NTF_TX_PERIOD_DONE : SRTM_AUDIO_NTF_RX_PERIOD_DONE,
                                 (uint16_t)sizeof(struct _srtm_audio_payload));
    if (notif == NULL)
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_ERROR, "%s(%d): alloc %s notification failed.\r\n", __func__, audioIdx,
                           dir == SRTM_AudioDirTx ? "Tx" : "Rx");
    }
    else
    {
        payload            = (struct _srtm_audio_payload *)(void *)SRTM_CommMessage_GetPayload(notif);
        payload->index     = (uint8_t)audioIdx;
        payload->periodIdx = periodIdx;

        (void)SRTM_Dispatcher_DeliverNotification(handle->service.dispatcher, notif);
    }
}

static void SRTM_AudioService_HandleTxPeriodDone(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    SRTM_AudioService_HandlePeriodDone(dispatcher, SRTM_AudioDirTx, (srtm_audio_service_t)param1,
                                       (uint32_t)(uint8_t *)param2);
}

static void SRTM_AudioService_HandleRxPeriodDone(srtm_dispatcher_t dispatcher, void *param1, void *param2)
{
    SRTM_AudioService_HandlePeriodDone(dispatcher, SRTM_AudioDirRx, (srtm_audio_service_t)param1,
                                       (uint32_t)(uint8_t *)param2);
}

/* CALLED IN AUDIO DRIVER ISR */
static srtm_status_t SRTM_AudioService_PeriodDone(srtm_service_t service,
                                                  srtm_audio_dir_t dir,
                                                  uint8_t index,
                                                  uint32_t periodIdx)
{
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;
    srtm_audio_iface_t iface    = SRTM_AudioService_FindInterface(handle, index);
    uint32_t primask;
    srtm_list_t *list;
    srtm_procedure_t proc = NULL;
    srtm_status_t status;

    assert(iface != NULL);

    primask = DisableGlobalIRQ();
    if (!SRTM_List_IsEmpty(&iface->freeProcs))
    {
        list = iface->freeProcs.next;
        SRTM_List_Remove(list);
        proc = SRTM_LIST_OBJ(srtm_procedure_t, node, list);
    }
    EnableGlobalIRQ(primask);

    assert(proc != NULL); /* For debugging the shortage of procedure messages */

    if (proc == NULL)
    {
        status = SRTM_Status_OutOfMemory;
    }
    else
    {
        proc->channel = iface->channel;
        proc->procMsg.cb =
            dir == SRTM_AudioDirTx ? SRTM_AudioService_HandleTxPeriodDone : SRTM_AudioService_HandleRxPeriodDone;
        proc->procMsg.param1 = service;
        proc->procMsg.param2 = (void *)(uint8_t *)((((uint32_t)index) << 24U) | (periodIdx & 0xFFFFFFU));
        status               = SRTM_Dispatcher_PostProc(service->dispatcher, proc);
    }

    return status;
}

static uint16_t SRTM_AudioService_GetRespLen(uint8_t command)
{
    return (uint16_t)sizeof(struct _srtm_audio_payload);
}

/* Both request and notify are called from SRTM dispatcher context */
static srtm_status_t SRTM_AudioService_Request(srtm_service_t service, srtm_request_t request)
{
    srtm_status_t status;
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;
    srtm_audio_iface_t iface;
    srtm_sai_adapter_t sai;
    srtm_codec_adapter_t codec;
    srtm_channel_t channel;
    uint8_t command;
    uint32_t payloadLen;
    uint32_t regVal;
    uint32_t bufOffset;
    srtm_response_t response;
    struct _srtm_audio_payload *audioReq;
    uint8_t *audioRespBuf;
    struct _srtm_audio_payload *audioResp;

    assert(service->dispatcher != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    channel    = SRTM_CommMessage_GetChannel(request);
    command    = SRTM_CommMessage_GetCommand(request);
    audioReq   = (struct _srtm_audio_payload *)(void *)SRTM_CommMessage_GetPayload(request);
    payloadLen = SRTM_CommMessage_GetPayloadLen(request);

    response = SRTM_Response_Create(channel, SRTM_AUDIO_CATEGORY, SRTM_AUDIO_VERSION, command,
                                    SRTM_AudioService_GetRespLen(command));
    if (response == NULL)
    {
        return SRTM_Status_OutOfMemory;
    }

    audioRespBuf = (uint8_t *)SRTM_CommMessage_GetPayload(response);
    audioResp    = (struct _srtm_audio_payload *)(void *)audioRespBuf;

    status = SRTM_Service_CheckVersion(service, request, SRTM_AUDIO_VERSION);
    if ((status != SRTM_Status_Success) || (audioReq == NULL) || (payloadLen != sizeof(struct _srtm_audio_payload)))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: format error!\r\n", __func__);
        audioRespBuf[0] = (audioReq != NULL) ? audioReq->index : 0U;
        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_UNSUPPORTED;
    }
    else
    {
        audioRespBuf[0] = audioReq->index;
        iface           = SRTM_AudioService_FindInterfaceByChannel(handle, request->channel);
        if (iface == NULL)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: audio interface for channel 0x%x not found!\r\n", __func__,
                               request->channel);
            audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_FAIL;
        }
        else
        {
            audioRespBuf[0] = iface->index;
            sai             = iface->sai;
            codec           = iface->codec;
            switch (command)
            {
                case SRTM_AUDIO_CMD_TX_OPEN:
                    /* Only when no one else is using the audio interface, we can open it. */
                    if ((sai != NULL) && (sai->open != NULL))
                    {
                        status = sai->open(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: audio interface %d tx open unavailable!\r\n",
                                           __func__, iface->index);
                        status = SRTM_Status_Error;
                    }
                    if (status == SRTM_Status_Success)
                    {
                        iface->useCount++;
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_SUCEESS;
                    }
                    else
                    {
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_FAIL;
                    }
                    break;
                case SRTM_AUDIO_CMD_TX_START:
                    if ((sai != NULL) && (sai->start != NULL))
                    {
                        status = sai->start(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_PAUSE:
                    if ((sai != NULL) && (sai->pause != NULL))
                    {
                        status = sai->pause(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_RESTART:
                    if ((sai != NULL) && (sai->restart != NULL))
                    {
                        status = sai->restart(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_STOP:
                    if ((sai != NULL) && (sai->stop != NULL))
                    {
                        status = sai->stop(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_CLOSE:
                    if ((sai != NULL) && (sai->close != NULL))
                    {
                        status = sai->close(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    if (status == SRTM_Status_Success)
                    {
                        assert(iface->useCount > 0U);
                        iface->useCount--;
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_SUCEESS;
                    }
                    else
                    {
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_FAIL;
                    }
                    break;
                case SRTM_AUDIO_CMD_TX_SET_PARAM:
                    if ((sai != NULL) && (sai->setParam != NULL))
                    {
                        status = sai->setParam(sai, SRTM_AudioDirTx, iface->index, audioReq->format, audioReq->channels,
                                               audioReq->srate);
                    }
                    status = ((status == SRTM_Status_Success) && (codec != NULL) && (codec->setParam != NULL)) ?
                                 codec->setParam(codec, iface->index, audioReq->format, audioReq->srate) :
                                 status;
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_SET_BUF:
                    if ((sai != NULL) && (sai->setBuf != NULL))
                    {
                        status = sai->setBuf(sai, SRTM_AudioDirTx, iface->index, (uint8_t *)audioReq->bufAddr,
                                             audioReq->bufSize, audioReq->periodSize, audioReq->periodIdx);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_SUSPEND:
                    if ((sai != NULL) && (sai->suspend != NULL))
                    {
                        status = sai->suspend(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_RESUME:
                    if ((sai != NULL) && (sai->resume != NULL))
                    {
                        status = sai->resume(sai, SRTM_AudioDirTx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_OPEN:
                    /* Only when no one else is using the audio interface, we can open it. */
                    if ((sai != NULL) && (sai->open != NULL))
                    {
                        status = sai->open(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: audio interface %d rx open unavailable!\r\n",
                                           __func__, iface->index);
                        status = SRTM_Status_Error;
                    }
                    if (status == SRTM_Status_Success)
                    {
                        iface->useCount++;
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_SUCEESS;
                    }
                    else
                    {
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_FAIL;
                    }
                    break;
                case SRTM_AUDIO_CMD_RX_START:
                    if ((sai != NULL) && (sai->start != NULL))
                    {
                        status = sai->start(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_PAUSE:
                    if ((sai != NULL) && (sai->pause != NULL))
                    {
                        status = sai->pause(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_RESTART:
                    if ((sai != NULL) && (sai->restart != NULL))
                    {
                        status = sai->restart(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_STOP:
                    if ((sai != NULL) && (sai->stop != NULL))
                    {
                        status = sai->stop(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_CLOSE:
                    if ((sai != NULL) && (sai->close != NULL))
                    {
                        status = sai->close(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    if (status == SRTM_Status_Success)
                    {
                        assert(iface->useCount > 0U);
                        iface->useCount--;
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_SUCEESS;
                    }
                    else
                    {
                        audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_FAIL;
                    }
                    break;
                case SRTM_AUDIO_CMD_RX_SET_PARAM:
                    if ((sai != NULL) && (sai->setParam != NULL))
                    {
                        status = sai->setParam(sai, SRTM_AudioDirRx, iface->index, audioReq->format, audioReq->channels,
                                               audioReq->srate);
                    }
                    status = ((status == SRTM_Status_Success) && (codec != NULL) && (codec->setParam != NULL)) ?
                                 codec->setParam(codec, iface->index, audioReq->format, audioReq->srate) :
                                 status;
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_SET_BUF:
                    if ((sai != NULL) && (sai->setBuf != NULL))
                    {
                        status = sai->setBuf(sai, SRTM_AudioDirRx, iface->index, (uint8_t *)audioReq->bufAddr,
                                             audioReq->bufSize, audioReq->periodSize, audioReq->periodIdx);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_SUSPEND:
                    if ((sai != NULL) && (sai->suspend != NULL))
                    {
                        status = sai->suspend(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_RESUME:
                    if ((sai != NULL) && (sai->resume != NULL))
                    {
                        status = sai->resume(sai, SRTM_AudioDirRx, iface->index);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_SET_CODEC_REG:
                    if ((codec != NULL) && (codec->setReg != NULL))
                    {
                        status = codec->setReg(codec, audioReq->reg, audioReq->regVal);
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioRespBuf[1] =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_GET_CODEC_REG:
                    audioResp->reg = audioReq->reg;
                    if ((codec != NULL) && (codec->getReg != NULL))
                    {
                        status            = codec->getReg(codec, audioReq->reg, &regVal);
                        audioResp->regVal = regVal;
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioResp->retCode =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_TX_GET_BUF_OFFSET:
                    if ((sai != NULL) && (sai->getBufOffset != NULL))
                    {
                        status               = sai->getBufOffset(sai, SRTM_AudioDirTx, iface->index, &bufOffset);
                        audioResp->bufOffset = bufOffset;
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioResp->retCode =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                case SRTM_AUDIO_CMD_RX_GET_BUF_OFFSET:
                    if ((sai != NULL) && (sai->getBufOffset != NULL))
                    {
                        status               = sai->getBufOffset(sai, SRTM_AudioDirRx, iface->index, &bufOffset);
                        audioResp->bufOffset = bufOffset;
                    }
                    else
                    {
                        status = SRTM_Status_Error;
                    }
                    audioResp->retCode =
                        status == SRTM_Status_Success ? SRTM_AUDIO_RETURN_CODE_SUCEESS : SRTM_AUDIO_RETURN_CODE_FAIL;
                    break;
                default:
                    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__, command);
                    audioRespBuf[1] = SRTM_AUDIO_RETURN_CODE_UNSUPPORTED;
                    break;
            }
        }
    }

    return SRTM_Dispatcher_DeliverResponse(service->dispatcher, response);
}

static srtm_status_t SRTM_AudioService_Notify(srtm_service_t service, srtm_notification_t notif)
{
    srtm_status_t status;
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;
    srtm_audio_iface_t iface;
    srtm_sai_adapter_t sai;
    uint8_t command;
    struct _srtm_audio_payload *payload;
    uint32_t payloadLen;

    assert(service->dispatcher != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    command    = SRTM_CommMessage_GetCommand(notif);
    payload    = (struct _srtm_audio_payload *)(void *)SRTM_CommMessage_GetPayload(notif);
    payloadLen = SRTM_CommMessage_GetPayloadLen(notif);

    status = SRTM_Service_CheckVersion(service, notif, SRTM_AUDIO_VERSION);
    if ((status != SRTM_Status_Success) || (payload == NULL) || (payloadLen != sizeof(struct _srtm_audio_payload)))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: format error!\r\n", __func__);
        status = SRTM_Status_ServiceNotFound;
    }
    else
    {
        iface = SRTM_AudioService_FindInterfaceByChannel(handle, notif->channel);
        if (iface == NULL)
        {
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: audio interface for channel 0x%x not found!\r\n", __func__,
                               notif->channel);
            status = SRTM_Status_ServiceNotFound;
        }
        else
        {
            sai = iface->sai;
            switch (command)
            {
                case SRTM_AUDIO_NTF_TX_PERIOD_DONE:
                    if ((sai != NULL) && (sai->periodReady != NULL))
                    {
                        status = sai->periodReady(sai, SRTM_AudioDirTx, iface->index, payload->periodIdx);
                    }
                    break;
                case SRTM_AUDIO_NTF_RX_PERIOD_DONE:
                    if ((sai != NULL) && (sai->periodReady != NULL))
                    {
                        status = sai->periodReady(sai, SRTM_AudioDirRx, iface->index, payload->periodIdx);
                    }
                    break;
                default:
                    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "%s: command %d unsupported!\r\n", __func__, command);
                    break;
            }
        }
    }

    return status;
}

static srtm_audio_iface_t SRTM_AudioService_CreateIface(srtm_audio_service_t handle,
                                                        uint8_t index,
                                                        srtm_sai_adapter_t sai,
                                                        srtm_codec_adapter_t codec)
{
    srtm_audio_iface_t iface = NULL;
    srtm_procedure_t proc;
    uint32_t i;

    if ((sai != NULL) || (codec != NULL))
    {
        iface = (srtm_audio_iface_t)SRTM_Heap_Malloc(sizeof(struct _srtm_audio_iface));
        assert(iface != NULL);

        if (sai != NULL)
        {
            sai->service    = &handle->service;
            sai->periodDone = SRTM_AudioService_PeriodDone;
        }
        iface->index    = index;
        iface->useCount = 0;
        iface->sai      = sai;
        iface->codec    = codec;
        iface->channel  = NULL;
        /* Create procedure messages list to be used in ISR */
        SRTM_List_Init(&iface->freeProcs);
        for (i = 0; i < SRTM_AUDIO_SERVICE_CONFIG_PROC_NUMBER; i++)
        {
            proc = SRTM_Procedure_Create(NULL, NULL, NULL);
            assert(proc != NULL);
            SRTM_Message_SetFreeFunc(proc, SRTM_AudioService_RecycleMessage, iface);
            SRTM_List_AddTail(&iface->freeProcs, &proc->node);
        }
    }

    return iface;
}

static void SRTM_AudioService_DestroyIface(srtm_audio_iface_t iface)
{
    srtm_list_t *list;
    srtm_procedure_t proc;

    assert(iface != NULL);

    /* iface must be unregistered from audio service */
    SRTM_List_Remove(&iface->node);

    while (!SRTM_List_IsEmpty(&iface->freeProcs))
    {
        list = iface->freeProcs.next;
        SRTM_List_Remove(list);
        proc = SRTM_LIST_OBJ(srtm_procedure_t, node, list);
        SRTM_Message_SetFreeFunc(proc, NULL, NULL);
        SRTM_Message_Destroy(proc);
    }

    SRTM_Heap_Free(iface);
}

static srtm_audio_iface_t SRTM_AudioService_FindInterface(srtm_audio_service_t handle, uint8_t index)
{
    srtm_list_t *list;
    srtm_audio_iface_t iface     = NULL;
    srtm_audio_iface_t cur_iface = NULL;

    for (list = handle->ifaces.next; list != &handle->ifaces; list = list->next)
    {
        cur_iface = SRTM_LIST_OBJ(srtm_audio_iface_t, node, list);
        if (cur_iface->index == index)
        {
            iface = cur_iface;
            break;
        }
    }

    return iface;
}

static srtm_audio_iface_t SRTM_AudioService_FindInterfaceByChannel(srtm_audio_service_t handle, srtm_channel_t channel)
{
    srtm_list_t *list;
    srtm_audio_iface_t iface     = NULL;
    srtm_audio_iface_t cur_iface = NULL;

    for (list = handle->ifaces.next; list != &handle->ifaces; list = list->next)
    {
        cur_iface = SRTM_LIST_OBJ(srtm_audio_iface_t, node, list);
        if (cur_iface->channel == channel)
        {
            iface = cur_iface;
            break;
        }
    }

    return iface;
}

static srtm_audio_iface_t SRTM_AudioService_FindInterfaceByAdapter(srtm_audio_service_t handle, srtm_sai_adapter_t sai)
{
    srtm_list_t *list;
    srtm_audio_iface_t iface     = NULL;
    srtm_audio_iface_t cur_iface = NULL;

    for (list = handle->ifaces.next; list != &handle->ifaces; list = list->next)
    {
        cur_iface = SRTM_LIST_OBJ(srtm_audio_iface_t, node, list);
        if (cur_iface->sai == sai)
        {
            iface = cur_iface;
            break;
        }
    }

    return iface;
}

srtm_service_t SRTM_AudioService_Create(srtm_sai_adapter_t sai, srtm_codec_adapter_t codec)
{
    srtm_audio_service_t handle;
    srtm_audio_iface_t iface;

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    handle = (srtm_audio_service_t)SRTM_Heap_Malloc(sizeof(struct _srtm_audio_service));
    assert(handle != NULL);

    SRTM_List_Init(&handle->service.node);
    handle->service.dispatcher = NULL;
    handle->service.category   = SRTM_AUDIO_CATEGORY;
    handle->service.destroy    = SRTM_AudioService_Destroy;
    handle->service.request    = SRTM_AudioService_Request;
    handle->service.notify     = SRTM_AudioService_Notify;

    SRTM_List_Init(&handle->ifaces);
    iface = SRTM_AudioService_CreateIface(handle, 0, sai, codec);
    if (iface != NULL)
    {
        SRTM_List_AddTail(&handle->ifaces, &iface->node);
    }

    return &handle->service;
}

void SRTM_AudioService_Destroy(srtm_service_t service)
{
    srtm_list_t *list;
    srtm_audio_iface_t iface;
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;

    assert(service != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    /* Service must be unregistered from dispatcher before destroy */
    assert(SRTM_List_IsEmpty(&service->node));

    while (!SRTM_List_IsEmpty(&handle->ifaces))
    {
        list = handle->ifaces.next;
        SRTM_List_Remove(list);
        iface = SRTM_LIST_OBJ(srtm_audio_iface_t, node, list);
        SRTM_AudioService_DestroyIface(iface);
    }

    SRTM_Heap_Free(handle);
}

void SRTM_AudioService_Reset(srtm_service_t service, srtm_peercore_t core)
{
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;
    srtm_list_t *list;
    srtm_audio_iface_t iface;

    assert(service != NULL);

    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s\r\n", __func__);

    for (list = handle->ifaces.next; list != &handle->ifaces; list = list->next)
    {
        iface = SRTM_LIST_OBJ(srtm_audio_iface_t, node, list);
        if ((iface->sai != NULL) && (iface->useCount > 0U) && (iface->channel->core == core))
        {
            (void)iface->sai->stop(iface->sai, SRTM_AudioDirRx, iface->index);
            (void)iface->sai->stop(iface->sai, SRTM_AudioDirTx, iface->index);
            (void)iface->sai->close(iface->sai, SRTM_AudioDirRx, iface->index);
            (void)iface->sai->close(iface->sai, SRTM_AudioDirTx, iface->index);
        }
        iface->channel  = NULL;
        iface->useCount = 0;
    }
}

srtm_status_t SRTM_AudioService_BindChannel(srtm_service_t service, srtm_sai_adapter_t sai, srtm_channel_t channel)
{
    srtm_status_t status = SRTM_Status_Success;
    srtm_audio_iface_t iface;
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;

    assert(service != NULL);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s(0x%x)\r\n", __func__, channel);

    iface = SRTM_AudioService_FindInterfaceByAdapter(handle, sai);
    if (iface != NULL)
    {
        iface->channel = channel;
    }
    else
    {
        status = SRTM_Status_ServiceNotFound;
    }

    return status;
}

srtm_status_t SRTM_AudioService_AddAudioInterface(srtm_service_t service, srtm_sai_adapter_t sai)
{
    srtm_status_t status = SRTM_Status_Success;
    srtm_audio_iface_t iface;
    srtm_audio_service_t handle = (srtm_audio_service_t)(void *)service;
    uint8_t index               = ++s_audIdx;

    assert(service != NULL);
    SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO, "%s(%d)\r\n", __func__, index);

    iface = SRTM_AudioService_CreateIface(handle, index, sai, NULL);
    if (iface != NULL)
    {
        SRTM_List_AddTail(&handle->ifaces, &iface->node);
    }
    else
    {
        status = SRTM_Status_InvalidParameter;
    }

    return status;
}
