/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __CONFIG_IMX_INC__
#define __CONFIG_IMX_INC__

#include "tfa2_dsp_fw.h"

#ifndef EPERM
#define EPERM 1 /* Not super-user */
#endif
#ifndef ENOENT
#define ENOENT 2 /* No such file or directory */
#endif
#ifndef EIO
#define EIO 5 /* I/O error */
#endif
#ifndef ENXIO
#define ENXIO 6 /* No such device or address */
#endif
#ifndef E2BIG
#define E2BIG 7 /* Arg list too long */
#endif
#ifndef ENOMEM
#define ENOMEM 12 /* Not enough core */
#endif
#ifndef EFAULT
#define EFAULT 14 /* Bad address */
#endif
#ifndef ENODEV
#define ENODEV 19 /* No such device */
#endif
#ifndef EINVAL
#define EINVAL 22 /* Invalid argument */
#endif
#ifndef ERANGE
#define ERANGE 34 /* Math result not representable */
#endif
#ifndef ETIME
#define ETIME 62 /* Timer expired */
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT 116 /* Connection timed out */
#endif

/* this is the I2C RPC buffer size */
#define TFADSP_COMMAND_BUFFER_MAX_WORDS 250
#define TFADSP_COMMAND_BUFFER_MAX_SIZE  (TFADSP_COMMAND_BUFFER_MAX_WORDS * sizeof(int))

#define kmalloc(ptr, flags) TFA9XXX_GetDSPMessageBuffer()
#define kfree(ptr)          (void)0

void TFA9XXX_NOP(const char *format, ...);
//#define TFA9XXX_DEBUG
#ifdef TFA9XXX_DEBUG
#include "fsl_debug_console.h"
#if defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE < 1)
#define TFA9XXX_Printf printf
#else
#define TFA9XXX_Printf DbgConsole_Printf
#endif
#else
#define TFA9XXX_Printf TFA9XXX_NOP
#endif

#define TFA9XXX_LOG_LEVEL \
    LOG_DEBUG /* verbose level of the TFA log: LOG_NONE, LOG_ERR, LOG_WARN, LOG_INFO or LOG_DEBUG */

#define tfaprintf(LOG_LEVEL, I, ...)        \
    do                                      \
    {                                       \
        if (LOG_LEVEL <= TFA9XXX_LOG_LEVEL) \
            TFA9XXX_Printf(__VA_ARGS__);    \
    } while (0)

#define le16toh(x)                (x)
#define msleep_interruptible(val) TFA9XXX_WaitMS(val)

static inline uint16_t get_unaligned_le16(const void *p)
{
    return le16toh(*(uint16_t *)p);
}

void usleep(uint32_t microSeconds);

uint8_t *TFA9XXX_GetDSPMessageBuffer(void);

/* wait in milli seconds */
void TFA9XXX_WaitMS(uint32_t val);

#endif /* __CONFIG_IMX_INC__ */
