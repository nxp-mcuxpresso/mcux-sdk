/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdarg.h>
#include <stdlib.h>

#include "fsl_common.h"
#include "fsl_str.h"
#include "fsl_component_log.h"

#ifdef SDK_OS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if (LOG_ENABLE_ASYNC_MODE > 0)
/* MAX argument count is fixed count + user's count */
#define LOG_MAX_ACTUAL_ARGUMENT_COUNT (LOG_MAX_ARGUMENT_COUNT + 2)

#define LOG_GEN_ARG(n, i)         (busy->argv[n - (i)])
#define LOG_GEN_ARGUMENT_GET_N(n) n

#define LOG_GEN_ARGUMENT_1(n, i)  LOG_GEN_ARG(n, i)
#define LOG_GEN_ARGUMENT_2(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_1(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_3(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_2(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_4(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_3(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_5(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_4(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_6(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_5(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_7(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_6(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_8(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_7(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_9(n, i)  LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_8(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_10(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_9(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_11(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_10(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_12(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_11(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_13(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_12(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_14(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_13(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_15(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_14(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_16(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_15(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_17(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_16(n, LOG_GEN_ARGUMENT_GET_N(i - 1))
#define LOG_GEN_ARGUMENT_18(n, i) LOG_GEN_ARG(n, i), LOG_GEN_ARGUMENT_17(n, LOG_GEN_ARGUMENT_GET_N(i - 1))

#define _LOG_GEN_ARGUMENT_CAT(macro, sub) macro##sub
#define LOG_GEN_ARGUMENT_CAT(macro, sub)  _LOG_GEN_ARGUMENT_CAT(macro, sub)
#define LOG_GEN_ARGUMENT(n)               LOG_GEN_ARGUMENT_CAT(LOG_GEN_ARGUMENT_, LOG_GEN_ARGUMENT_GET_N(n))((n - 1), (n - 1))
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)
typedef struct log_string_node
{
    struct log_string_node *next;
    LOG_ARGUMENT_TYPE argv[LOG_MAX_ACTUAL_ARGUMENT_COUNT];
    char const *formatString;
    unsigned int timeStamp;
    log_level_t level;
    uint32_t argc;
} log_string_node_t;
#endif

typedef struct log_print_buffer
{
    uint8_t *buffer;
    size_t length;
    size_t sofar;
} log_print_buffer_t;

typedef struct log_context
{
    log_backend_t *backend;
#if (LOG_ENABLE_ASYNC_MODE > 0)
    log_print_buffer_t printBuffer;
#endif
#if LOG_ENABLE_TIMESTAMP
    log_get_timestamp_callback_t getTimeStamp;
#endif
#ifdef SDK_OS_FREE_RTOS
    SemaphoreHandle_t mutex;
#endif
#if (LOG_ENABLE_ASYNC_MODE > 0)
    log_string_node_t stringNode[LOG_MAX_BUFF_LOG_COUNT];
    log_string_node_t *idle;
    log_string_node_t *pend;
#if !(LOG_ENABLE_OVERWRITE > 0)
    SemaphoreHandle_t idleCount;
#endif
#endif
    uint8_t initialized;
} log_context_t;

#if LOG_ENABLE_COLOR
#define LOG_COLOR_CODE_DEFAULT \
    "\x1B"                     \
    "[0m"
#define LOG_COLOR_CODE_MAGENTA \
    "\x1B"                     \
    "[1;35m"
#define LOG_COLOR_CODE_MAGENTA_BG \
    "\x1B"                        \
    "[0;35m"
#define LOG_COLOR_CODE_RED \
    "\x1B"                 \
    "[1;31m"
#define LOG_COLOR_CODE_RED_BG \
    "\x1B"                    \
    "[0;31m"
#define LOG_COLOR_CODE_YELLOW \
    "\x1B"                    \
    "[1;33m"
#define LOG_COLOR_CODE_YELLOW_BG \
    "\x1B"                       \
    "[0;33m"
#define LOG_COLOR_CODE_GREEN \
    "\x1B"                   \
    "[1;32m"
#define LOG_COLOR_CODE_GREEN_BG \
    "\x1B"                      \
    "[0;32m"
#define LOG_COLOR_CODE_CYAN \
    "\x1b"                  \
    "[1;36m"
#define LOG_COLOR_CODE_CYAN_BG \
    "\x1b"                     \
    "[0;36m"
#define LOG_COLOR_CODE_BLUE \
    "\x1B"                  \
    "[1;34m"
#define LOG_COLOR_CODE_BLUE_BG \
    "\x1B"                     \
    "[0;34m"

#define LOG_COLOR_PRINT                  " %s%s%s "
#define LOG_COLOR_PRINT_PARAMETER(level) log_get_color(level), log_get_level_name(level), log_get_color(kLOG_LevelNone)
#else
#define LOG_COLOR_PRINT                  " %s "
#define LOG_COLOR_PRINT_PARAMETER(level) log_get_level_name(level)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static log_context_t s_logContext;
#if LOG_ENABLE_COLOR
static const char *s_logColor[] = {
    LOG_COLOR_CODE_DEFAULT, LOG_COLOR_CODE_MAGENTA, LOG_COLOR_CODE_RED,  LOG_COLOR_CODE_YELLOW,
    LOG_COLOR_CODE_GREEN,   LOG_COLOR_CODE_CYAN,    LOG_COLOR_CODE_BLUE,
};
#endif
static const char *s_logLevelName[] = {
    "None", "FATAL", "ERROR", "WARN ", "INFO ", "DEBUG", "TRACE",
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void log_output_low_level(uint8_t *buffer, size_t length)
{
    log_backend_t *backend = s_logContext.backend;

    while (NULL != backend)
    {
        if (NULL != backend->putStr)
        {
            backend->putStr(buffer, length);
        }
        backend = backend->next;
    }
}

static void log_print_to_buffer(char *buf, int32_t *indicator, char val, int len)
{
    log_print_buffer_t *buffer = (log_print_buffer_t *)((void *)(buf));
    int i                      = 0;

    for (i = 0; i < len; i++)
    {
        if ((((size_t)(*indicator)) + buffer->sofar + ((size_t)1)) >= buffer->length)
        {
            break;
        }

        if ((val == '\n') &&
            ((0 == (*indicator)) ||
             (((uint8_t)'\r') != buffer->buffer[((size_t)(*indicator)) + buffer->sofar - ((size_t)1)])))
        {
            buffer->buffer[((size_t)(*indicator)) + buffer->sofar] = (uint8_t)'\r';
            (*indicator)++;
        }

        buffer->buffer[((size_t)(*indicator)) + buffer->sofar] = (uint8_t)val;
        (*indicator)++;
    }
}

static int log_sprintf_internal(log_print_buffer_t *printBuf, char const *format, ...)
{
    va_list ap;
    int ret;

    va_start(ap, format);
    /* format print log first */
    ret = StrFormatPrintf(format, ap, (char *)printBuf, log_print_to_buffer);
    va_end(ap);

    return ret;
}

static char const *log_get_level_name(log_level_t level)
{
    assert(((uint8_t)level < ARRAY_SIZE(s_logLevelName)));
    return s_logLevelName[(int)level];
}

#if LOG_ENABLE_COLOR
static char const *log_get_color(log_level_t level)
{
    assert(((uint8_t)level < ARRAY_SIZE(s_logColor)));
    return s_logColor[(int)level];
}
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)
static int LOG_DumpInternal(void)
{
    log_string_node_t *busy;
    uint32_t primask;
    int length = -1;

    primask = DisableGlobalIRQ();
    busy    = s_logContext.pend;
    if (NULL != s_logContext.pend)
    {
        s_logContext.pend = s_logContext.pend->next;
    }
    EnableGlobalIRQ(primask);

    if (NULL != busy)
    {
        switch (busy->argc)
        {
            case 2:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(2));
                break;
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 2
            case 3:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(3));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 3
            case 4:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(4));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 4
            case 5:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(5));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 5
            case 6:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(6));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 6
            case 7:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(7));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 7
            case 8:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(8));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 8
            case 9:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(9));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 9
            case 10:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(10));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 10
            case 11:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(11));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 11
            case 12:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(12));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 12
            case 13:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(13));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 13
            case 14:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(14));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 14
            case 15:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(15));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 15
            case 16:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(16));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 16
            case 17:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(17));
                break;
#endif
#if LOG_MAX_ACTUAL_ARGUMENT_COUNT > 17
            case 18:
                LOG_Printf(NULL, busy->level, busy->timeStamp, (const char *)busy->formatString, LOG_GEN_ARGUMENT(18));
                break;
#endif
            default:
                /* Fix MISRA C-2012 Rule 16.4 */
                break;
        }

        primask           = DisableGlobalIRQ();
        busy->next        = s_logContext.idle;
        s_logContext.idle = busy;
#if !(LOG_ENABLE_OVERWRITE > 0)
        (void)xSemaphoreGive(s_logContext.idleCount);
#endif
        EnableGlobalIRQ(primask);
    }
    return length;
}
#endif

log_status_t LOG_Init(void)
{
#if (LOG_ENABLE_ASYNC_MODE > 0)
    uint8_t i;
#endif

    if (0U != s_logContext.initialized)
    {
        return kStatus_LOG_Initialized;
    }

    (void)memset(&s_logContext, 0, sizeof(s_logContext));
#if (LOG_ENABLE_ASYNC_MODE > 0)
    s_logContext.idle = &s_logContext.stringNode[0];
    for (i = 1U; i < ((uint8_t)LOG_MAX_BUFF_LOG_COUNT); i++)
    {
        s_logContext.stringNode[i].next = s_logContext.idle;
        s_logContext.idle               = &s_logContext.stringNode[i];
    }
#if !(LOG_ENABLE_OVERWRITE > 0)
    s_logContext.idleCount = xSemaphoreCreateCounting(LOG_MAX_BUFF_LOG_COUNT, LOG_MAX_BUFF_LOG_COUNT);
    if (NULL == s_logContext.idleCount)
    {
        return kStatus_LOG_LackResource;
    }
#endif
#endif

#ifdef SDK_OS_FREE_RTOS
    s_logContext.mutex = xSemaphoreCreateRecursiveMutex();
    if (NULL == s_logContext.mutex)
    {
        return kStatus_LOG_LackResource;
    }
#endif
    s_logContext.initialized = 1U;

    return kStatus_LOG_Success;
}

log_status_t LOG_Deinit(void)
{
    if (0U == s_logContext.initialized)
    {
        return kStatus_LOG_Uninitialized;
    }
#ifdef SDK_OS_FREE_RTOS
    if (NULL != s_logContext.mutex)
    {
        vSemaphoreDelete(s_logContext.mutex);
        s_logContext.mutex = NULL;
    }
#endif
    s_logContext.initialized = 0U;
    return kStatus_LOG_Success;
}

#if LOG_ENABLE_TIMESTAMP
log_status_t LOG_SetTimestamp(log_get_timestamp_callback_t getTimeStamp)
{
    if (0U == s_logContext.initialized)
    {
        return kStatus_LOG_Uninitialized;
    }

    s_logContext.getTimeStamp = getTimeStamp;

    return kStatus_LOG_Success;
}

unsigned int LOG_GetTimestamp(void)
{
    if (0U == s_logContext.initialized)
    {
        return 0;
    }

    if (NULL != s_logContext.getTimeStamp)
    {
        return s_logContext.getTimeStamp();
    }
    return 0;
}
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)
void LOG_AsyncPrintf(log_module_t const *module,
                     log_level_t level,
                     unsigned int timeStamp,
                     char const *format,
                     uint32_t argc,
                     LOG_ARGUMENT_TYPE argv[])
{
    log_string_node_t *node = NULL;
    log_string_node_t *p    = NULL;
    uint32_t primask;

    assert((((uint32_t)LOG_MAX_ACTUAL_ARGUMENT_COUNT) >= argc));

    do
    {
        primask = DisableGlobalIRQ();
        if (NULL != s_logContext.idle)
        {
            node              = s_logContext.idle;
            s_logContext.idle = s_logContext.idle->next;
        }
        EnableGlobalIRQ(primask);

        if (NULL == node)
        {
#if (LOG_ENABLE_OVERWRITE > 0)
            primask = DisableGlobalIRQ();
            node    = s_logContext.pend;
            if (NULL != s_logContext.pend)
            {
                s_logContext.pend = s_logContext.pend->next;
            }
            EnableGlobalIRQ(primask);
            if (NULL == node)
            {
                break;
            }
#else
            (void)xSemaphoreTake(s_logContext.idleCount, (TickType_t)10);
            primask = DisableGlobalIRQ();
            if (NULL != s_logContext.idle)
            {
                node              = s_logContext.idle;
                s_logContext.idle = s_logContext.idle->next;
            }
            EnableGlobalIRQ(primask);
#endif
        }
    }
#if (LOG_ENABLE_OVERWRITE > 0)
    while (false);
#else
    while (NULL == node);
#endif

#if (LOG_ENABLE_OVERWRITE > 0)
    if (NULL != node)
#endif
    {
        node->formatString = format;
        node->timeStamp    = timeStamp;
        node->level        = level;
        node->argc         = argc;
        node->next         = NULL;
        (void)memcpy(node->argv, argv, sizeof(argv[0]) * argc);

        if (NULL != s_logContext.pend)
        {
            p = s_logContext.pend;
            while (NULL != p->next)
            {
                p = p->next;
            }
            p->next = node;
        }
        else
        {
            s_logContext.pend = node;
        }
    }
}
#endif

void LOG_Printf(log_module_t const *module, log_level_t level, unsigned int timeStamp, char const *format, ...)
{
    va_list ap;
    log_print_buffer_t buffer;
    uint8_t printBuf[LOG_MAX_MEESSAGE_LENGTH];

    (void)module;

    if (0U == s_logContext.initialized)
    {
        return;
    }

#ifdef SDK_OS_FREE_RTOS
    if (((BaseType_t)0) == (BaseType_t)xSemaphoreTakeRecursive(s_logContext.mutex, portMAX_DELAY))
    {
        return;
    }
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)
    if (NULL != s_logContext.printBuffer.buffer)
    {
        (void)memcpy(&buffer, &s_logContext.printBuffer, sizeof(buffer));
    }
    else
#endif
    {
        buffer.buffer = printBuf;
        buffer.length = LOG_MAX_MEESSAGE_LENGTH;
        buffer.sofar  = 0;
    }

    /* print timestamp */
#if LOG_ENABLE_TIMESTAMP
    buffer.sofar += (size_t)log_sprintf_internal(&buffer, "%12d:", timeStamp);
#endif
    /* print level name */
    buffer.sofar += (size_t)log_sprintf_internal(&buffer, LOG_COLOR_PRINT, LOG_COLOR_PRINT_PARAMETER(level));

    va_start(ap, format);
    /* format print log first */
    buffer.sofar += (size_t)StrFormatPrintf(format, ap, (char *)&buffer, log_print_to_buffer);

    va_end(ap);
#if (LOG_ENABLE_ASYNC_MODE > 0)
    s_logContext.printBuffer.sofar = buffer.sofar;
#endif
    log_output_low_level(buffer.buffer, buffer.sofar);

#ifdef SDK_OS_FREE_RTOS
    if (((BaseType_t)0) == (BaseType_t)xSemaphoreGiveRecursive(s_logContext.mutex))
    {
        return;
    }
#endif
}

log_status_t LOG_BackendRegister(log_backend_t *backend)
{
    log_backend_t *p = s_logContext.backend;
    log_status_t ret = kStatus_LOG_BackendExist;
    uint32_t regPrimask;

    assert(NULL != backend);

    if (0U == s_logContext.initialized)
    {
        return kStatus_LOG_Uninitialized;
    }

    regPrimask = DisableGlobalIRQ();
    while (NULL != p)
    {
        if (p == backend)
        {
            break;
        }
        p = p->next;
    }
    if (NULL == p)
    {
        backend->next        = s_logContext.backend;
        s_logContext.backend = backend;
        ret                  = kStatus_LOG_Success;
    }
    EnableGlobalIRQ(regPrimask);
    return ret;
}

log_status_t LOG_BackendUnregister(log_backend_t *backend)
{
    log_backend_t *p = s_logContext.backend;
    log_backend_t *q = s_logContext.backend;
    log_status_t ret = kStatus_LOG_BackendNotFound;
    uint32_t regPrimask;

    assert(NULL != backend);

    if (0U == s_logContext.initialized)
    {
        return kStatus_LOG_Uninitialized;
    }

    regPrimask = DisableGlobalIRQ();
    while (NULL != p)
    {
        if (p == backend)
        {
            if (q == p)
            {
                s_logContext.backend = p->next;
            }
            else
            {
                q->next = p->next;
            }
            p->next = NULL;
            ret     = kStatus_LOG_Success;
        }
        q = p;
        p = p->next;
    }
    EnableGlobalIRQ(regPrimask);

    return ret;
}

#if (LOG_ENABLE_ASYNC_MODE > 0)
void LOG_Dump(uint8_t *buffer, size_t length, size_t *outLength)
{
    s_logContext.printBuffer.buffer = buffer;
    s_logContext.printBuffer.length = length;
    s_logContext.printBuffer.sofar  = (size_t)0;
    (void)LOG_DumpInternal();
    if ((NULL != buffer) && (((size_t)0) != length) && (NULL != outLength))
    {
        *outLength = s_logContext.printBuffer.sofar;
    }
}
#endif
