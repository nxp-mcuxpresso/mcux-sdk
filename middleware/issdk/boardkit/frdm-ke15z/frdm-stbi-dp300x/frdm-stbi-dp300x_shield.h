/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_stbc_agm01_shield.h
 * @brief The frdm_stbc_agm01_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-k64f and frmd-stbc-agm01 shield
 */

#ifndef _FRDM_STBC_DIFF_P_SHIELD_H_
#define _FRDM_STBC_DIFF_P_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBI-DP300x"

// DIFF-P Conversion Factors
#define NPS3000VV_PRESSURE_DIV_FACTOR (8)
#define NPS3001DV_PRESSURE_DIV_FACTOR (8)
#define NPS3002VV_PRESSURE_DIV_FACTOR (4)
#define NPS3005DV_PRESSURE_DIV_FACTOR (4)

// DIFF-P Sensor Information
#define DIFF_P_I2C_ADDR 0x60
#define DIFF_P_INT1 D5
#define DIFF_P_INT2 D2
#define DIFF_P_CS D10

#endif /* _FRDM_STBC_DIFF_P_SHIELD_H_ */
