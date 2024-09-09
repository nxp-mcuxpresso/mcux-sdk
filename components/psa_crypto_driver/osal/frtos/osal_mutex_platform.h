/*
 * Copyright 2023 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef OSAL_MUTEX_PLATFORM_H
#define OSAL_MUTEX_PLATFORM_H

/** \file osal_mutex_platform.h
 *
 * This file contains the definition for mcux_mutex_t
 *
 */

#include "FreeRTOS.h"
#include "semphr.h"

typedef SemaphoreHandle_t mcux_mutex_t;

#endif /* OSAL_MUTEX_PLATFORM_H */
