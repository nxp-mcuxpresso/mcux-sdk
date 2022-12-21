/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 * @file frdm_stbc_a8491_shield.h
* @brief The frdm_stbc_a8491_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-kl25z and frmd-stbc-a8491 shield
*/

#ifndef _FRDM_STBC_A8491_SHIELD_H_
#define _FRDM_STBC_A8491_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDMSTBC-A8491"

// MMA8491 Sensor Information
#define MMA8491_I2C_ADDR 0x55
#define MMA8491_EN A1
#define MMA8491_XOUT D2
#define MMA8491_YOUT D5
#define MMA8491_ZOUT D8

#endif /* _FRDM_STBC_A8491_SHIELD_H_ */
