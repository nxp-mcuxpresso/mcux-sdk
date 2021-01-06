/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sc_event.h"
#include "fsl_mu.h"
#include "assert.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.sc_event"
#endif

#if defined(MIMX8QM_CM4_CORE0)
#define IPC_MU CM4_0__MU1_A
#define SCEvent_MU_IRQHandler M4_0_MU1_A_IRQHandler
#define IPC_MU_IRQn M4_0_MU1_A_IRQn
#define IPC_MU_RSRC SC_R_M4_0_MU_1A
#elif defined(MIMX8QM_CM4_CORE1)
#define IPC_MU CM4_1__MU1_A
#define SCEvent_MU_IRQHandler M4_1_MU1_A_IRQHandler
#define IPC_MU_IRQn M4_1_MU1_A_IRQn
#define IPC_MU_RSRC SC_R_M4_1_MU_1A
#else
#error "Unsupported CPU."
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Define a structure to hold SRTM_MESSAGE_BUF_SIZE buffer. */
typedef struct
{
    sc_event_list_t node;
    uint8_t buf[sizeof(struct _sc_event_handler) - sizeof(sc_event_list_t)];
} sc_event_handler_buf_t;
/*******************************************************************************
 * Code
 ******************************************************************************/
static volatile bool s_irq; /* MU interrupt status. */

static uint32_t s_irqEnabled[SC_IRQ_NUM_GROUP] = {0U};
static sc_event_list_t s_registeredHandler;
static sc_ipc_t ipc; /* ipc handle */

static sc_event_handler_buf_t s_handlerBuf[SC_EVENT_HANDLER_MEM_POOL_SIZE / sizeof(sc_event_handler_t)];
static sc_event_list_t s_freeHandlerPool;

static void *s_sem                      = NULL;
static sc_event_sema4_post_t s_postFunc = NULL;

void SCEvent_MU_IRQHandler(void);
/*!
 * @brief Initialize SC Event Handler list head.
 *
 * @param list SC Event Handler list head pointer.
 */
static inline void SCEvent_List_Init(sc_event_list_t *list)
{
    assert(list);

    list->prev = list;
    list->next = list;
}

/*!
 * @brief Check whether SC Event Handler list is empty.
 *
 * @param list SC Event Handler list head pointer.
 * @return TRUE when list is empty, FALSE otherwise.
 */
static inline bool SCEvent_List_IsEmpty(sc_event_list_t *list)
{
    assert(list);

    return list->next == list;
}

/*!
 * @brief Add list node at list tail.
 *
 * @param list SC Event Handler list head pointer.
 * @param node SC Event Handler list node pointer to add.
 */
static inline void SCEvent_List_AddTail(sc_event_list_t *list, sc_event_list_t *node)
{
    assert(list);
    assert(node);

    node->prev       = list->prev;
    node->next       = list;
    list->prev->next = node;
    list->prev       = node;
}

/*!
 * @brief Remove list node from list.
 *
 * @param node SC Event Handler list node pointer to remove.
 */
static inline void SCEvent_List_Remove(sc_event_list_t *node)
{
    assert(node);

    node->prev->next = node->next;
    node->next->prev = node->prev;
    /* clear node */
    SCEvent_List_Init(node);
}

/*!
 * @brief Allocate memory with specific size.
 *
 * @param size memory size to allocate.
 *
 * @return allocated memory address.
 */
static void *SCEvent_Pool_Alloc(uint32_t size)
{
    uint32_t i;
    void *buf;
    uint32_t primask;

    if (s_freeHandlerPool.next == NULL)
    {
        primask = DisableGlobalIRQ();
        if (s_freeHandlerPool.next == NULL)
        {
            /* Handler list not initialized, initialize now. */
            SCEvent_List_Init(&s_freeHandlerPool);
            for (i = 0U; i < sizeof(s_handlerBuf) / sizeof(sc_event_handler_buf_t); i++)
            {
                SCEvent_List_AddTail(&s_freeHandlerPool, &s_handlerBuf[i].node);
            }
        }
        EnableGlobalIRQ(primask);
    }

    if (size > sizeof(sc_event_handler_buf_t))
    {
        return NULL;
    }
    else
    {
        primask = DisableGlobalIRQ();
        if (SCEvent_List_IsEmpty(&s_freeHandlerPool))
        {
            return NULL;
        }
        else
        {
            buf = (void *)s_freeHandlerPool.next;
            SCEvent_List_Remove(s_freeHandlerPool.next);
            EnableGlobalIRQ(primask);
        }
    }

    return buf;
}

/*!
 * @brief Free the allocated memory.
 *
 * @param buf the address of the allocated memory
 */
static void SCEvent_Pool_Free(void *buf)
{
    sc_event_handler_t hBuf;
    uint32_t primask;

    /* buffer locates in handler pool */
    assert(((uint32_t)((sc_event_handler_buf_t*)buf) - (uint32_t)&s_handlerBuf[0]) % sizeof(sc_event_handler_buf_t) == 0U);
    hBuf    = (sc_event_handler_t)buf;
    primask = DisableGlobalIRQ();
    SCEvent_List_AddTail(&s_freeHandlerPool, &hBuf->node);
    EnableGlobalIRQ(primask);
}

void SCEvent_Init(uint8_t priority)
{
    ipc = SystemGetScfwIpcHandle();
    NVIC_SetPriority(IPC_MU_IRQn, priority);
    (void)EnableIRQ(IPC_MU_IRQn);
    MU_EnableInterrupts(IPC_MU, MU_SR_GIPn_MASK);

    SCEvent_List_Init(&s_registeredHandler);
}

void SCEvent_Deinit(void)
{
    sc_event_list_t *list;
    sc_event_handler_t handler;

    /* Unregister all handler. */
    while (!SCEvent_List_IsEmpty(&s_registeredHandler))
    {
        list = s_registeredHandler.next;
        SCEvent_List_Remove(list);
        handler = SC_EVENT_LIST_OBJ(sc_event_handler_t, node, list);
        SCEvent_Pool_Free(handler);
    }

    MU_DisableInterrupts(IPC_MU, MU_SR_GIPn_MASK);
    (void)DisableIRQ(IPC_MU_IRQn);
}

status_t SCEvent_Config(sc_event_t event, bool enable, uint32_t pt)
{
    uint32_t status;
    sc_err_t err;
    uint32_t mask = SC_EVENT_GET_IRQ(event);
    uint8_t group = (uint8_t)SC_EVENT_GET_IRQ_GROUP(event);

    /*
     * The SCFW IRQ pending flags will be set even the IRQ not enabled. If it's the first IRQ to be enabled in the
     * group, clear the group's pending IRQ status in case some IRQ has already pending.
     */
    if ((s_irqEnabled[group] == 0U) && enable)
    {
        err = sc_irq_status(ipc, IPC_MU_RSRC, group, &status);
        if (err != SC_ERR_NONE)
        {
            return kStatus_Fail;
        }
    }

    if (mask == SC_EVENT_IRQ_DUMMY)
    {
        err = sc_irq_enable(ipc, IPC_MU_RSRC, group, (0x1UL << pt), enable);
        if (err != SC_ERR_NONE)
        {
            return kStatus_Fail;
        }

        if (enable)
        {
            s_irqEnabled[group] |= 0x1UL << pt;
        }
        else
        {
            /* Clear the flag if IRQ disabled. */
            s_irqEnabled[group] &= (~(0x1UL << pt)) & SC_EVENT_IRQ_DUMMY;
        }
    }
    else
    {
        err = sc_irq_enable(ipc, IPC_MU_RSRC, group, mask, enable);
        if (err != SC_ERR_NONE)
        {
            return kStatus_Fail;
        }
        if (enable)
        {
            s_irqEnabled[group] |= mask;
        }
        else
        {
            s_irqEnabled[group] &= ~mask;
        }
    }

    return kStatus_Success;
}

sc_event_handler_t SCEvent_RegisterEventHandler(sc_event_t event, sc_event_callback_t callback, void *userData)
{
    assert(callback);
    uint32_t primask;
    sc_event_handler_t handler = (sc_event_handler_t)SCEvent_Pool_Alloc(sizeof(sc_event_handler_buf_t));

    if (handler == NULL)
    {
        return NULL;
    }
    else
    {
        (void)memset(handler, 0, sizeof(sc_event_handler_buf_t));
        /* clear node */
        SCEvent_List_Init(&handler->node);

        handler->event    = event;
        handler->callback = callback;
        handler->data     = userData;

        /* Add handler into registered handler list. */
        primask = DisableGlobalIRQ();
        SCEvent_List_AddTail(&s_registeredHandler, &handler->node);
        EnableGlobalIRQ(primask);
        return handler;
    }
}

void SCEvent_UnregisterEventHandler(sc_event_handler_t handler)
{
    assert(handler);
    uint32_t primask;

    primask = DisableGlobalIRQ();
    SCEvent_List_Remove(&handler->node);
    EnableGlobalIRQ(primask);

    SCEvent_Pool_Free(handler);
}

void SCEvent_Process(void)
{
    sc_err_t err;
    uint32_t mask; /* Enabled IRQ mask. */
    uint8_t group; /* Event group. */
    uint32_t irqStatus[SC_IRQ_NUM_GROUP] = {0U};

    sc_event_list_t *list;
    sc_event_handler_t handler;

    if (s_irq)
    {
        for (list = s_registeredHandler.next; list != &s_registeredHandler; list = list->next)
        {
            handler = SC_EVENT_LIST_OBJ(sc_event_handler_t, node, list);

            mask  = SC_EVENT_GET_IRQ(handler->event);
            group = (uint8_t)SC_EVENT_GET_IRQ_GROUP(handler->event);
            /* Only read and clear status once for a group. */
            if (irqStatus[group] == 0U)
            {
                err = sc_irq_status(ipc, IPC_MU_RSRC, group, &irqStatus[group]);
                if (err != SC_ERR_NONE)
                {
                    continue;
                }

            }
            /* If there's event pending and the event IRQ enabled, call the handler. */
            if ((irqStatus[group] & mask & s_irqEnabled[group]) != 0U)
            {
                handler->callback(irqStatus[group], handler->data);
            }
        }

        /* Clean up the status. */
        (void)memset(irqStatus, 0, sizeof(irqStatus));

        s_irq = false;
    }
}

status_t SCEvent_WaitEvent(sc_event_sema4_wait_t wait, sc_event_sema4_post_t post, void *sem, uint32_t timeout)
{
    status_t ret = kStatus_Success;
    uint32_t primask;

    assert(post);
    assert(wait);

    primask = DisableGlobalIRQ();
    if (!s_irq) /* Return immediately if there's event pending. */
    {
        s_sem      = sem;
        s_postFunc = post;
        EnableGlobalIRQ(primask);
        ret = wait(sem, timeout);
        s_postFunc = NULL;
    }
    else
    {
        EnableGlobalIRQ(primask);
    }
    
    return ret;
}

/*!
 * IRQ Handler for SCEvent Triggling MU IRQ
 */
void SCEvent_MU_IRQHandler(void)
{
    /* Clear interrupt flag */
    MU_ClearStatusFlags(IPC_MU, MU_SR_GIPn_MASK);

    if (s_postFunc != NULL)
    {
        s_postFunc(s_sem);
    }

    s_irq = true;

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
