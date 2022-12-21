/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_stbc_p3115_shield.h
* @brief The frdm_stbc_p3115_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-kl25z and frmd-stbc-p3115 shield
*/

#ifndef _FRDM_STBC_P3115_SHIELD_H_
#define _FRDM_STBC_P3115_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDMSTBC-P3115"

// MPL3115 Sensor Information
#define MPL3115_I2C_ADDR 0x60
#define MPL3115_INT1 D5
#define MPL3115_INT2 D2

#endif /* _FRDM_STBC_P3115_SHIELD_H_ */
