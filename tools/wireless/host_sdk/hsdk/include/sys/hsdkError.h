/*
 * \file hsdkError.h
 * This is the header file that contains the error macros.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HSDK_ERROR__
#define __HSDK_ERROR__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <Windows.h>
#define HSDK_ERROR_SUCCESS ERROR_SUCCESS
#define HSDK_ERROR_INVALID ERROR_INVALID_DATA
#define HSDK_ERROR_ALLOC ERROR_NOT_ENOUGH_MEMORY
#else
#include <errno.h>
#define HSDK_ERROR_SUCCESS 0
#define HSDK_ERROR_INVALID EINVAL
#define HSDK_ERROR_ALLOC ENOMEM
#endif

#ifdef __cplusplus
}
#endif

#endif
