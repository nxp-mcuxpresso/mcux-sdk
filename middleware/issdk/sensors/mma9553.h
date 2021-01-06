/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MMA9553_H_
#define MMA9553_H_

#include <stdint.h>

/*! @brief Size of fixed header bytes in sensor commands. */
#define MMA9553_HDR_SIZE  (4)

/*! @brief Size of Version Info. */
#define VERSION_INFO_SIZE (12)

/*! @brief Size of Standby Registers. */
#define STANDBY_REG_SIZE (4)

/*! @brief XYZ Data Register Offset. */
#define MMA9553_XYZ_DATA_OFFSET (26)

/*! @brief The MMA9553 I2C Slave Address */
#define MMA9553_I2C_ADDRESS (0x4C)

/*! @brief The Read Version Info Command. */
extern const uint8_t ReadVersionInfo[4];

/*! @brief Configure MBOX for QR Data and XYZ Axes Command. */
extern const uint8_t MBoxQRDataXYZ[16] ;

/*! @brief Set Sensor to Legacy (free running) Mode Command. */
extern const uint8_t SetLegacyMode[5];

/*! @brief Set Sensor to Legacy Mode with INT_O interrupt on completion of the AFE sampling. */
extern const uint8_t SetLegacyIntMode[5];




/*! @brief Set sensor to Wake Mode Command. */
extern const uint8_t WakeApplication[5] ;

/*! @brief Command to reset all applications of the sensor. */
extern const uint8_t ResetApplication[5];

/*! @brief Full-Scale Range Selections. */
extern const uint8_t SetFSRange_2g[5];
extern const uint8_t SetFSRange_4g[5];
extern const uint8_t SetFSRange_8g[5];

/*! @brief Sample Rate Commands. */
extern const uint8_t SetSampleRate_488Hz[5] ;
extern const uint8_t SetSampleRate_244Hz[5] ;
extern const uint8_t SetSampleRate_122Hz[5] ;
extern const uint8_t SetSampleRate_61Hz[5]  ;
extern const uint8_t SetSampleRate_30Hz[5]  ;
extern const uint8_t SetSampleRate_15Hz[5]  ;
extern const uint8_t SetSampleRate_7Hz[5]   ;
extern const uint8_t SetSampleRate_3Hz[5]   ;

/*! @brief AFE Priority Commands. */
extern const uint8_t SetAFEPriority_for488Hz[5];
extern const uint8_t SetAFEPriority_for224Hz[5];
extern const uint8_t SetAFEPriority_for122Hz[5];
extern const uint8_t SetAFEPriority_for61Hz[5];
extern const uint8_t SetAFEPriority_for30Hz[5];
extern const uint8_t SetAFEPriority_for15Hz[5];
extern const uint8_t SetAFEPriority_for7Hz[5];
extern const uint8_t SetAFEPriority_for3Hz[5];

/*! @brief MBox Priority Commands. */
extern const uint8_t SetMBoxPriority_for488Hz[5];
extern const uint8_t SetMBoxPriority_for244Hz[5];
extern const uint8_t SetMBoxPriority_for122Hz[5];
extern const uint8_t SetMBoxPriority_for61Hz[5];
extern const uint8_t SetMBoxPriority_for30Hz[5];
extern const uint8_t SetMBoxPriority_for15Hz[5];
extern const uint8_t SetMBoxPriority_for7Hz[5];
extern const uint8_t SetMBoxPriority_for3Hz[5];

/*! @brief Command to Read Pedometer Data. */
extern const uint8_t ReadPedometerData[4] ;

#endif  /* MMA9553_H_ */ 
