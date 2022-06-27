/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_component_mem_manager.h"
#include "fsl_component_generic_list.h"
#include "fsl_component_messaging.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (defined(MSG_USE_MACRO) && (MSG_USE_MACRO == 0U))
void MSG_QueueInit(messaging_t *msgQueue)
{
    assert(msgQueue);

    LIST_Init(msgQueue, 0);
}

void MSG_QueueDeinit(messaging_t *msgQueue)
{
    assert(msgQueue);
    while (NULL != MSG_QueueGetHead(msgQueue))
    {
        (void)MEM_BufferFree(LIST_RemoveHead(msgQueue));
    }
}
#endif
messaging_status_t MSG_QueueAddTail(messaging_t *msgQueue, void *msg)
{
    list_status_t listStatus;

    assert(msgQueue);
    assert(msg);

    msg = (list_element_t *)msg - 1;

    listStatus = LIST_AddTail(msgQueue, (list_element_t *)msg);

    return ((list_status_t)kLIST_Ok == listStatus) ? (messaging_status_t)kMSG_Success : (messaging_status_t)kMSG_Error;
}

messaging_status_t MSG_QueueAddHead(messaging_t *msgQueue, void *msg)
{
    list_status_t listStatus;

    assert(msgQueue);
    assert(msg);

    msg = (list_element_t *)msg - 1;

    listStatus = LIST_AddHead(msgQueue, (list_element_t *)msg);

    return ((list_status_t)kLIST_Ok == listStatus) ? (messaging_status_t)kMSG_Success : (messaging_status_t)kMSG_Error;
}

messaging_status_t MSG_QueueAddPrev(void *msg, void *newMsg)
{
    list_element_t *pElem;
    list_element_t *pNewElem;
    list_status_t listStatus;

    assert(msg);
    assert(newMsg);

    pElem    = (list_element_t *)msg - 1;
    pNewElem = (list_element_t *)newMsg - 1;

    listStatus = LIST_AddPrevElement((list_element_t *)pElem, (list_element_t *)pNewElem);

    return ((list_status_t)kLIST_Ok == listStatus) ? (messaging_status_t)kMSG_Success : (messaging_status_t)kMSG_Error;
}

messaging_status_t MSG_QueueRemove(void *msg)
{
    list_element_t *p;
    list_status_t listStatus;

    assert(msg);

    p          = (list_element_t *)msg - 1;
    listStatus = LIST_RemoveElement((list_element_t *)p);

    return ((list_status_t)kLIST_Ok == listStatus) ? (messaging_status_t)kMSG_Success : (messaging_status_t)kMSG_Error;
}

void *MSG_QueueRemoveHead(messaging_t *msgQueue)
{
    void *buffer;

    assert(msgQueue);

    buffer = LIST_RemoveHead(msgQueue);

    return (buffer != NULL) ? ((list_element_t *)buffer + 1) : buffer;
}

void *MSG_QueueGetHead(messaging_t *msgQueue)
{
    void *buffer;

    assert(msgQueue);

    buffer = LIST_GetHead(msgQueue);

    return (buffer != NULL) ? ((list_element_t *)buffer + 1) : buffer;
}

void *MSG_QueueGetNext(void *msg)
{
    list_element_t *p;

    assert(msg);

    p = (list_element_t *)msg - 1;
    p = LIST_GetNext(p);

    return (p != NULL) ? ((list_element_t *)p + 1) : p;
}

void *MSG_QueueGetPrev(void *msg)
{
    list_element_t *p;

    assert(msg);

    p = (list_element_t *)msg - 1;
    p = LIST_GetPrev(p);

    return (p != NULL) ? ((list_element_t *)p + 1) : p;
}

void *MSG_Alloc(uint32_t length)
{
    void *buffer;

    assert(length);

    buffer = MEM_BufferAlloc(length + sizeof(list_element_t));
    if (buffer != NULL)
    {
        buffer = (list_element_t *)buffer + 1;
    }
    return buffer;
}

void MSG_Free(void *buffer)
{
    if (buffer != NULL)
    {
        (void)MSG_QueueRemove(buffer);
        (void)MEM_BufferFree((list_element_t *)buffer - 1);
    }
}
