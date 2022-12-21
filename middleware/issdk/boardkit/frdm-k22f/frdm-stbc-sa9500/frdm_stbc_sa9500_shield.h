/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! File: frdm_stbc_sa9500_shield.h
* @brief The frdm_stbc_sa9500_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-k22f and frmd-stbc-agm01 shield
*/

#ifndef _frdm_stbc_sa9500_shield_H_
#define _frdm_stbc_sa9500_shield_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBC-SA9500"

// FXLC95000 Sensor Information
#define FXLC95000_I2C_ADDR 0x4C
#define FXLC95000_INT1 D2
#define FXLC95000_PDB_B D8
#define FXLC95000_SSB_IO3 D10
#define FXLC95000_RST_GPIO A3

#endif /* _frdm_stbc_sa9500_shield_H_ */
