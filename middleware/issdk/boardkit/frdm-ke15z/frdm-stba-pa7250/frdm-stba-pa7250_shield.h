/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file frdm-stba-pa7250_shield.h
 * @brief The frdm-stba-pa7250_shield.h file declares mapping of the Kinetis
         Device peripherals to the frmd-ke15z and frdm-stba-pa7250 shield
 */

#ifndef _FRDM_STBA_PA7250_SHIELD_H_
#define _FRDM_STBA_PA7250_SHIELD_H_

/* The shield name */
#define SHIELD_NAME "FRDM-STBA-PA7250"

// MPXV5004DP Sensor based parameters
#define VCC                           (5.0)
#define BIT12RES                      (4096)
#define FXPS7250A4_OFFSET             (20) /* Zero Error Offset. */


/* Arduino Pin A0 (Sensor Analog Output Pin) maps to ADC0 Channel 0 on KE15Z (PTA0). */
#define FXPS7250A4_ADC12_CHANNEL 0U
#define FXPS7250A4_ADC12_CHANNEL_GROUP 0U

#endif /* _FRDM_STBA_PA7250_SHIELD_H_ */
