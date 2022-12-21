/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm-stba-pd7250_shieldd.h
 * @brief The frdm-stba-pd7250_shield.h file declares mapping of the Kinetis
         Device peripherals to the frdm-ke15z and frdm-stba-pd7250 shield
 */

#ifndef _FRDM_STBA_PD7250_SHIELD_H_
#define _FRDM_STBA_PD7250_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBI-DP300x"

// DBAP Sensor Information
#define DBAP_I2C_ADDR   0x60
#define DIFF_P_INT1     D5
#define DIFF_P_INT2     D2
#define DIFF_P_CS       D10

#endif /* _FRDM_STBA_PD7250_SHIELD_H_ */
