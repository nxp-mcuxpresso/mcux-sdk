/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! File: frdm_stba_a896x_shield.h
* @brief The frdm_stba_a896x_shield.h file declares arduino pin mapping for frdm_stba_a896x_shield with frdm-k22f.
*/

#ifndef _FRDM_STBA_A896X_SHIELD_H_
#define _FRDM_STBA_A896X_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBA-A896x"

// FXLS896x Sensor Information
#define FXLS896x_I2C_ADDR 0x18
#define FXLS896x_CS       D10
#define FXLS896x_MOSI     D11
#define FXLS896x_MISO     D12
#define FXLS896x_SCLK     D13
#define FXLS896x_INT1     D2
#define FXLS896x_INT2     A0

// FRDM-STBA-A896x Shield Reset
#define RESET_GPIO A3

#endif /* _FRDM_STBA_A896X_SHIELD_H_ */
