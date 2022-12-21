/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! File: frdm_stbi_a8974_shield.h
* @brief The frdm_stbi_a8974_shield.h file declares arduino pin mapping for frdm_stbi_a8974_shield with frdm-k22f.
*/

#ifndef _FRDM_STBI_A8974_SHIELD_H_
#define _FRDM_STBI_A8974_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBI-A8974"

// FXLS8974 Sensor Information
#define FXLS8974_I2C_ADDR 0x18
#define FXLS8974_CS       D10
#define FXLS8974_MOSI     D11
#define FXLS8974_MISO     D12
#define FXLS8974_SCLK     D13
#define FXLS8974_INT1     D2
#define FXLS8974_INT2     A0

// FRDM-STBI-A8974 Shield Reset
#define RESET_GPIO A3

#endif /* _FRDM_STBI_A8974_SHIELD_H_ */
