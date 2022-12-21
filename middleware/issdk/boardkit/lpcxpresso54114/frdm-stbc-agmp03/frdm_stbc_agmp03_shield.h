/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! @file: frdm_stbc_agmp03_shield.h
* @brief The frdm_stbc_agmp03_shield.h file declares mapping of the Kinetis
         Device peripherals to the lpcxpresso54114 and frmd-stbc-agmp03 shield.
*/

#ifndef _FRDM_STBC_AGMP03_SHIELD_H_
#define _FRDM_STBC_AGMP03_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBC-AGMP03"

// FXLS8962 Sensor Information
#define FXLS8962_I2C_ADDR 0x18
#define FXLS8962_CS D10
#define FXLS8962_MOSI D11
#define FXLS8962_MISO D12
#define FXLS8962_SCLK D13
#define FXLS8962_INT1 D2
#define FXLS8962_INT2 A0

// FXAS21002 Sensor Information
#define FXAS21002_I2C_ADDR 0x20
#define FXAS21002_INT1 D8
#define FXAS21002_INT2 A2
#define FXAS21002_CS A1

// MPL3115 Sensor Information
#define MPL3115_I2C_ADDR 0x60
#define MPL3115_INT1 D7

// MAG3110 Sensor Information
#define MAG3110_I2C_ADDR 0x0E
#define MAG3110_INT1 D5

// FRDM-STBC-AGMP03 Shield Reset
#define RESET_GPIO A3

///@name Shield Parameters
/// Use this section to define the shield board: 3 bit code 0 to 7 inclusive
/// transmitted in bits 7-5 for display purposes only.
///@{
#define SHIELD_MULTIB 0
#define SHIELD_NONE 1
#define SHIELD_AGM01 2
#define SHIELD_AGM02 3
#define SHIELD_AGMP03 4
#define SHIELD_AGM04 5
#define THIS_SHIELD SHIELD_AGMP03

// spare 5 to 7 inclusive
///@}

#endif /* _FRDM_STBC_AGMP03_SHIELD_H_ */
