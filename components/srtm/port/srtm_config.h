/*
 * Copyright 2021, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SRTM_CONFIG_H
#define _SRTM_CONFIG_H

#ifdef SDK_OS_FREE_RTOS
#include "FreeRTOS.h"

#if configSUPPORT_STATIC_ALLOCATION
#define SRTM_STATIC_API 1
typedef StaticSemaphore_t srtm_sem_buf_t;
typedef StaticSemaphore_t srtm_mutex_buf_t;
#endif

#endif /* SDK_OS_FREE_RTOS */

#endif
