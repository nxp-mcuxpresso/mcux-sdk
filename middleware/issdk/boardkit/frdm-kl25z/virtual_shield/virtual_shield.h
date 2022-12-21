/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file virtual_shield.h
* @brief The virtual_shield.h file declares mapping of NXP sensor pins
         to I2C addresses and standard Arduino pin names.
  Within the NXP KSDK, Arduino pin names are defined as a function of
  MCU pin names in the <base_board>.h file found in the "board" folder of
  your project.

  This file does not map to real world hardware.  You may need to modify it
  (specifically device addresses) to match your hardware.
*/

#ifndef _VIRTUAL_SHIELD_H_
#define _VIRTUAL_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "VIRTUAL_SENSOR_SHIELD"

// FXOS8700 Sensor Information
/*
   In order to route INT1 signal from FXOS8700 to the K64F,
   Pins 1-2 of Jumper J3 on the FRDM-FXS-MULT2-B should be connected.
   In order to route INT2 signal from FXOS8700 to the K64F,
   Pins 1-2 of Jumper J4 on the FRDM-FXS-MULT2-B should be connected.
*/
#define FXOS8700_I2C_ADDR 0x1E
#define FXOS8700_INT1 D2
#define FXOS8700_INT2 D4

// FXAS21002 Sensor Information
/*
   In order to route INT1 signal from FXAS21002 to the K64F,
   Pins 1-2 of Jumper J6 on the FRDM-FXS-MULT2-B should be connected.
*/
#define FXAS21002_I2C_ADDR 0x20
#define FXAS21002_INT1 D5

// MAG3110 Sensor Information
/*
   In order to route INT1 signal from MAG3110 to the K64F,
   Pins 2-3 of Jumper J3 on the FRDM-FXS-MULT2-B should be connected.
*/
#define MAG3110_I2C_ADDR 0x0E
#define MAG3110_INT1 D2

// MPL3115 Sensor Information
/*
   In order to route INT1 signal from MPL3115 to the K64F,
   Pins 2-3 of Jumper J5 on the FRDM-FXS-MULT2-B should be connected.
*/
#define MPL3115_I2C_ADDR 0x60
#define MPL3115_INT1 D8

// MMA8652 Sensor Information
/*
   In order to route INT1 signal from MMA8652 to the K64F,
   Pins 2-3 of Jumper J4 on the FRDM-FXS-MULT2-B should be connected.
*/
#define MMA8652_I2C_ADDR 0x1D
#define MMA8652_INT1 D4

// FXLS8471Q Sensor Information
/*
   In order to route INT1 signal from FXLS8471Q to the FRDM-K64F,
   Pins 2-3 of Jumper J6 on the FRDM-FXS-MULT2-B should be connected.
*/
#define FXLS8471_INT1 D5
#define FXLS8471_SPI_CS D10

// FXLS8962 Sensor Information
#define FXLS8962_I2C_ADDR 0x18
#define FXLS8962_CS D10
#define FXLS8962_MOSI D11
#define FXLS8962_MISO D12
#define FXLS8962_SCLK D13
#define FXLS8962_INT1 D2
#define FXLS8962_INT2 A0
// FXLC95000 Sensor Information
#define FXLC95000_I2C_ADDR 0x4D // Does not match NXP shield boards
#define FXLC95000_CS A2
#define FXLC95000_INT1 D2
#define FXLC95000_PDB_B D8
#define FXLC95000_SSB_IO3 D10
#define FXLC95000_RST_GPIO A3

// MMA9553 Sensor Information
#define MMA9553_I2C_ADDR 0x4C
#define MMA9553_SSB_IO3 D10

// MMA8491 Sensor Information
#define MMA8491_I2C_ADDR 0x55
#define MMA8491_EN A1
#define MMA8491_XOUT D2
#define MMA8491_YOUT D5
#define MMA8491_ZOUT D8

#define RESET_GPIO A3

///@name Shield Parameters
/// Use this section to define the shield board: 3 bit code 0 to 7 inclusive
/// transmitted in bits 7-5 for display purposes only.
/// Since this is a virtual shield, we use the MULTIB display option as an easy default.
///@{
#define SHIELD_MULTIB 0
#define SHIELD_NONE 1
#define SHIELD_AGM01 2
#define SHIELD_AGM02 3
#define THIS_SHIELD SHIELD_MULTIB

// spare 5 to 7 inclusive
///@}

#endif /* _VIRTUAL_SHIELD_H_ */
