/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file rd_kl25z_gdl.h
* @brief The rd_kl25z_gdl.h file declares mapping of the Kinetis
         Device peripherals to the rd-kl25z board
*/

#ifndef _RD_KL25Z_GDL_H_
#define _RD_KL25Z_GDL_H_

/* The Data Logger Board Name */
#define SHIELD_NAME "RD_KL25_AGMP01"

// FXAS21002 Sensor Information
#define FXAS21002_I2C_ADDR 0x20
#define INT1_FXAS21002 D9

// FXOS8700 Sensor Information
#define FXOS8700_I2C_ADDR 0x1E

// MPL3115 Sensor Information
#define MPL3115_I2C_ADDR 0x60

// GREEN LED on RD-KL25Z
#define LED_GREEN A1

#endif /* _RD_KL25Z_GDL_H_ */
