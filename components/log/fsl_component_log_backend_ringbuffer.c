/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_common.h"

#include "fsl_component_log.h"

#include "fsl_component_log_backend_ringbuffer.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __WEAK_FUNC __attribute__((weak))
#endif

typedef struct log_backend_ring_buffer
{
    uint8_t *ringBuffer;
    size_t ringBufferLength;
    size_t ringBufferHead;
    size_t ringBufferTail;
    uint8_t initialized;
} log_backend_ring_buffer_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
__WEAK_FUNC void log_backend_ringbuffer_update(uint8_t *buffer, size_t head, size_t tail);
__WEAK_FUNC void log_backend_ringbuffer_update(uint8_t *buffer, size_t head, size_t tail)
{
    (void)buffer;
    (void)head;
    (void)tail;
}

static void log_init_backend_ringbuffer_puts(uint8_t *buffer, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static log_backend_ring_buffer_t s_logBackendRingBuffer;

LOG_BACKEND_DEFINE(backend_ring_buffer, log_init_backend_ringbuffer_puts);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void log_init_backend_ringbuffer_puts(uint8_t *buffer, size_t length)
{
    uint32_t remainingBufferLength;
    uint32_t copyLength;
    uint32_t primask;

    if ((0U == s_logBackendRingBuffer.initialized) || (0U == length))
    {
        return;
    }

    primask               = DisableGlobalIRQ();
    remainingBufferLength = (s_logBackendRingBuffer.ringBufferHead + s_logBackendRingBuffer.ringBufferLength -
                             s_logBackendRingBuffer.ringBufferTail) %
                            s_logBackendRingBuffer.ringBufferLength;
    remainingBufferLength = s_logBackendRingBuffer.ringBufferLength - remainingBufferLength - 1U;

    if (length >= s_logBackendRingBuffer.ringBufferLength)
    {
        buffer = &buffer[length - s_logBackendRingBuffer.ringBufferLength + 1U];
        length = s_logBackendRingBuffer.ringBufferLength - 1U;
    }
    copyLength = length;

    if ((s_logBackendRingBuffer.ringBufferHead + copyLength) > s_logBackendRingBuffer.ringBufferLength)
    {
        copyLength = s_logBackendRingBuffer.ringBufferLength - s_logBackendRingBuffer.ringBufferHead;
    }
    (void)memcpy(&s_logBackendRingBuffer.ringBuffer[s_logBackendRingBuffer.ringBufferHead], &buffer[0], copyLength);
    if (copyLength < length)
    {
        (void)memcpy(&s_logBackendRingBuffer.ringBuffer[0], &buffer[copyLength], length - copyLength);
    }

    if (length >= remainingBufferLength)
    {
        s_logBackendRingBuffer.ringBufferHead += length;
        s_logBackendRingBuffer.ringBufferHead =
            s_logBackendRingBuffer.ringBufferHead % s_logBackendRingBuffer.ringBufferLength;
        s_logBackendRingBuffer.ringBufferTail =
            s_logBackendRingBuffer.ringBufferHead + s_logBackendRingBuffer.ringBufferLength + 1U;
        s_logBackendRingBuffer.ringBufferTail =
            s_logBackendRingBuffer.ringBufferTail % s_logBackendRingBuffer.ringBufferLength;
    }
    else
    {
        s_logBackendRingBuffer.ringBufferHead += length;
        s_logBackendRingBuffer.ringBufferHead =
            s_logBackendRingBuffer.ringBufferHead % s_logBackendRingBuffer.ringBufferLength;
    }
    EnableGlobalIRQ(primask);

    log_backend_ringbuffer_update(s_logBackendRingBuffer.ringBuffer, s_logBackendRingBuffer.ringBufferHead,
                                  s_logBackendRingBuffer.ringBufferTail);
}

void LOG_InitBackendRingbuffer(log_backend_ring_buffer_config_t *config)
{
    log_status_t ret;
    assert((NULL != config) && (NULL != config->ringBuffer) && (0U != config->ringBufferLength));

    if (0U != s_logBackendRingBuffer.initialized)
    {
        return;
    }

    (void)memset(&s_logBackendRingBuffer, 0, sizeof(s_logBackendRingBuffer));

    s_logBackendRingBuffer.ringBuffer       = config->ringBuffer;
    s_logBackendRingBuffer.ringBufferLength = config->ringBufferLength;

    ret = LOG_BackendRegister(&backend_ring_buffer);
    if (kStatus_LOG_Success == ret)
    {
        s_logBackendRingBuffer.initialized = 1U;
    }
    assert(kStatus_LOG_Success == ret);
    return;
}

void LOG_DeinitBackendRingbuffer(void)
{
    log_status_t ret;

    ret = LOG_BackendUnregister(&backend_ring_buffer);
    if (kStatus_LOG_Success == ret)
    {
        s_logBackendRingBuffer.initialized = 0U;
    }
    assert(kStatus_LOG_Success == ret);
    return;
}
