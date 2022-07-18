/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef CALSTORE_H
#define CALSTORE_H

  
/*! \file calibration_storage.h
    \brief Provides functions to store calibration to NVM
   
    Users who are not using NXP hardware will need to supply their own drivers
    in place of those defined here.
*/

void SaveMagCalibrationToNVM(SensorFusionGlobals *sfg);
void SaveGyroCalibrationToNVM(SensorFusionGlobals *sfg);
void SaveAccelCalibrationToNVM(SensorFusionGlobals *sfg);
void EraseMagCalibrationFromNVM(void);
void EraseGyroCalibrationFromNVM(void);
void EraseAccelCalibrationFromNVM(void);
#endif
