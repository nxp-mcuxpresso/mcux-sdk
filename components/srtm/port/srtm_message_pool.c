/*
 * Copyright 2018, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "srtm_message_pool.h"
#include "srtm_heap.h"
#include "srtm_list.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Simple algorithm:
 * Here we suppose most SRTM messages data are small.
 * By default we set each message buffer to 96 (0x60) bytes (including struct _srtm_message
 * which occupies 52 bytes). So we have 44 bytes for the SRTM message data (10bytes header +
 * 34 bytes payload which is sufficient for all current SRTM category).
 */
/* Total buffer size for messages in the pool. */
#ifndef SRTM_MESSAGE_POOL_SIZE
#define SRTM_MESSAGE_POOL_SIZE (0x1000)
#endif

/* Each message buffer size */
#ifndef SRTM_MESSAGE_BUF_SIZE
#define SRTM_MESSAGE_BUF_SIZE (0x60)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Define a structure to hold SRTM_MESSAGE_BUF_SIZE buffer. */
typedef struct
{
    srtm_list_t node;
    uint8_t buf[SRTM_MESSAGE_BUF_SIZE - sizeof(srtm_list_t)];
} srtm_message_buf_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static srtm_message_buf_t srtmMsgs[SRTM_MESSAGE_POOL_SIZE / sizeof(srtm_message_buf_t)];
static srtm_list_t srtmMsgList;
#ifdef SRTM_DEBUG_MESSAGE_FUNC
/* Used for probe current and minimum free message buffer count in debugger. */
static uint32_t freeMsgCount;
static uint32_t minFreeMsgCount;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
void *SRTM_MessagePool_Alloc(uint32_t size)
{
    uint32_t i;
    void *buf;
    uint32_t primask;

    if (srtmMsgList.next == NULL)
    {
        primask = DisableGlobalIRQ();
        if (srtmMsgList.next == NULL)
        {
            /* Message list not initialized, initialize now */
            SRTM_List_Init(&srtmMsgList);
            for (i = 0; i < sizeof(srtmMsgs) / sizeof(srtm_message_buf_t); i++)
            {
                SRTM_List_AddTail(&srtmMsgList, &srtmMsgs[i].node);
            }
#ifdef SRTM_DEBUG_MESSAGE_FUNC
            freeMsgCount    = sizeof(srtmMsgs) / sizeof(srtm_message_buf_t);
            minFreeMsgCount = freeMsgCount;
#endif
        }
        EnableGlobalIRQ(primask);
    }

    if (size > sizeof(srtm_message_buf_t))
    {
        SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_INFO,
                           "Message size larger than SRTM_MESSAGE_BUF_SIZE %d, allocated in heap.\r\n",
                           SRTM_MESSAGE_BUF_SIZE);
        buf = SRTM_Heap_Malloc(size);
    }
    else
    {
        primask = DisableGlobalIRQ();
        if (SRTM_List_IsEmpty(&srtmMsgList))
        {
            EnableGlobalIRQ(primask);
            SRTM_DEBUG_MESSAGE(SRTM_DEBUG_VERBOSE_WARN, "Message pool (size %d) used up, allocated in heap.\r\n",
                               SRTM_MESSAGE_POOL_SIZE);
            buf = SRTM_Heap_Malloc(size);
        }
        else
        {
            buf = (void *)srtmMsgList.next;
            SRTM_List_Remove(srtmMsgList.next);
#ifdef SRTM_DEBUG_MESSAGE_FUNC
            freeMsgCount--;
            if (freeMsgCount < minFreeMsgCount)
            {
                minFreeMsgCount = freeMsgCount;
            }
#endif
            EnableGlobalIRQ(primask);
        }
    }

    return buf;
}

void SRTM_MessagePool_Free(void *buf)
{
    srtm_message_buf_t *msgBuf;
    uint32_t primask;

    if ((buf >= (void *)&srtmMsgs[0]) && (buf < (void *)(&srtmMsgs[sizeof(srtmMsgs) / sizeof(srtm_message_buf_t)])))
    {
        /* buffer locates in message pool */
        assert(((uint32_t)(uint8_t *)(buf) - (uint32_t)&srtmMsgs[0]) % sizeof(srtm_message_buf_t) == 0U);
        msgBuf  = (srtm_message_buf_t *)buf;
        primask = DisableGlobalIRQ();
        SRTM_List_AddTail(&srtmMsgList, &msgBuf->node);
#ifdef SRTM_DEBUG_MESSAGE_FUNC
        freeMsgCount++;
#endif
        EnableGlobalIRQ(primask);
    }
    else
    {
        SRTM_Heap_Free(buf);
    }
}
