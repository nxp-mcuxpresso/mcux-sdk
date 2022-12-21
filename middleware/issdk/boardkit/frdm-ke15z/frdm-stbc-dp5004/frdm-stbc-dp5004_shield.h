/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm_stbc_dp5004_shield.h
 * @brief The frdm_stbc_dp5004_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-ke15z and frmd-stbc-dp5004 shield
 */

#ifndef _FRDM_STBC_DP5004_SHIELD_H_
#define _FRDM_STBC_DP5004_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBC-DP5004"

// MPXV5004DP Sensor based parameters
#define MPXV5004DP_ZERO_ERROR 1185 /* Zero Error Offset. */
#define MPXV5004DP_PRESSURE_FROM_ADC_VALUE(x) (uint32_t)(x*1.25 - MPXV5004DP_ZERO_ERROR) /* Pressure in Pascals (Pa). */

/* Arduino Pin A0 (Sensor Analog Output Pin) maps to ADC0 Channel 0 on KE15Z (PTA0). */
#define MPXVDP5004_ADC12_CHANNEL  0U
#define MPXVDP5004_ADC12_CHANNEL_GROUP 0U

#endif /* _FRDM_STBC_DP5004_SHIELD_H_ */
