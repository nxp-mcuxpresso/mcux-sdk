/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file driver_KSDK_NVM.h
    \brief middleware driver for NVM on Kinetis devices
*/

#ifndef DRVNVM_H
#define DRVNVM_H

byte NVM_SetBlockFlash(uint8_t *Source, uint32_t Dest, uint16_t Count);

#endif
