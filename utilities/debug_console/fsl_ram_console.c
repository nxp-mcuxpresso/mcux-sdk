/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <stdarg.h>
#include <stdlib.h>
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#include <stdio.h>
#endif

#include "fsl_debug_console.h"
#include "fsl_str.h"

#if (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE == DEBUGCONSOLE_RAM_CONSOLE))
static char *ram_console_buf;
static size_t ram_console_buf_size;
static int pos;

status_t RamConsole_Init(uintptr_t buf_addr, size_t buf_size)
{
    if (buf_addr == 0UL)
        return kStatus_Fail;

    ram_console_buf = (char *)buf_addr;
    ram_console_buf_size = buf_size;
    memset(ram_console_buf, 0, ram_console_buf_size);

    return kStatus_Success;
}

int RamConsole_Printf(const char *fmt_s, ...)
{
    va_list ap;
    int result = 0;

    va_start(ap, fmt_s);
    result = RamConsole_Vprintf(fmt_s, ap);
    va_end(ap);

    return result;
}

static void RamConsole_PrintCallback(char *buf, int32_t *indicator, char dbgVal, int len)
{
    int i = 0;

    for (i = 0; i < len; i++)
    {
#if 0
        if (((uint32_t)*indicator + 1UL) >= (uint32_t)DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN)
        {
            (void)DbgConsole_SendDataReliable((uint8_t *)buf, (size_t)(*indicator));
            *indicator = 0;
        }
#endif
        buf[*indicator] = dbgVal;
        (*indicator)++;
    }
}

/* See fsl_debug_console.h for documentation of this function. */
int RamConsole_Vprintf(const char *fmt_s, va_list formatStringArg)
{
    int logLength = 0;
    char printBuf[DEBUG_CONSOLE_PRINTF_MAX_LOG_LEN] = {'\0'};
    int i;

    if (NULL == ram_console_buf)
        return -1;

    /* format print log first */
    logLength = StrFormatPrintf(fmt_s, formatStringArg, printBuf, RamConsole_PrintCallback);
    /* print log */
    for (i = 0; i < logLength; i++)
    {
        ram_console_buf[pos] = printBuf[i];
        pos = (pos + 1) % ram_console_buf_size;
    }

    return logLength;
}

/* See fsl_debug_console.h for documentation of this function. */
int RamConsole_Putchar(int ch)
{
    if (NULL == ram_console_buf)
        return -1;

    /* print char */
    ram_console_buf[pos] = ch;
    pos = (pos + 1) % ram_console_buf_size;

    return ch;
}
#endif
