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
#include "fsl_debug_console.h"

#include "fsl_component_log_backend_debugconsole.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void log_init_backend_debugconsole_puts(uint8_t *buffer, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint8_t initialized;

LOG_BACKEND_DEFINE(backend_debug_console, log_init_backend_debugconsole_puts);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void log_init_backend_debugconsole_puts(uint8_t *buffer, size_t length)
{
    if ((0U == initialized) || (0U == length))
    {
        return;
    }

    for (size_t i = 0; i < length; i++)
    {
        (void)PUTCHAR((int)buffer[i]);
    }
}

void LOG_InitBackendDebugconsole(void)
{
    log_status_t ret;
    if (initialized > 0U)
    {
        return;
    }

    ret = LOG_BackendRegister(&backend_debug_console);
    if (kStatus_LOG_Success == ret)
    {
        initialized = 1U;
    }
    assert(kStatus_LOG_Success == ret);
    return;
}

void LOG_DeinitBackendDebugconsole(void)
{
    log_status_t ret;

    ret = LOG_BackendUnregister(&backend_debug_console);
    if (kStatus_LOG_Success == ret)
    {
        initialized = 0U;
    }
    assert(kStatus_LOG_Success == ret);
    return;
}
