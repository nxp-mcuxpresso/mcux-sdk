/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file drivers.h
    \brief Provides function prototypes for driver level interfaces

    Users who are not using NXP hardware will need to supply their own drivers
    in place of those defined here.
*/

#ifndef DRIVERS_H
#define DRIVERS_H
#include "Driver_I2C.h"
#include "Driver_SPI.h"

// must #include "sensor_fusion.h" before this file

/// @name SysTick Macros
/// The ARM SysTick counter is used to time various fusion options.  Timings
/// are then conveyed to the NXP Sensor Fusion Toolbox, where they are displayed
/// for the developer.  These functions should be portable to any ARM M0+, M3,
/// M4 or M4F device.  If you are using a different CPU architecture, you will
/// need to provide an equivalent set of macros, remove the macro calls from
/// the fusion routines, or define a set of empty macros.
///@{
void ARM_systick_enable(void);
void ARM_systick_start_ticks(int32_t *pstart);
int32_t ARM_systick_elapsed_ticks(int32_t start_ticks);
void ARM_systick_delay_ms(uint32_t iSystemCoreClock, uint32_t delay_ms);
///@}

/// @name Sensor Drivers
/// Each physical sensor must be provided with one initialization function
/// and one "read" function.  These must be installed by the user using the
/// installSensor method defined in SensorFusionGlobals.  By "physical sensor",
/// we mean either individual sensor type (such as a 3-axis accelerometer) or
/// a combo-sensor such as the NXP FXOS8700 6-axis accel plus mag.  The init()
/// function for each sensor is responsible for initializing all sensors contained
/// in that package.  The read() function is responsible for reading those same
/// sensors and moving the results into the standard structures contained within
/// the SensorFusionGlobals object.
///@{
int8_t MPL3115_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXOS8700_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXAS21002_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8652_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8952_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MAG3110_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8451_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8471Q_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8962_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8972_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);

int8_t MPL3115_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXOS8700_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXAS21002_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8652_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8952_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MAG3110_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8451_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8471Q_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8962_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8972_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);

int8_t MPL3115_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXOS8700_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXAS21002_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8652_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8952_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MAG3110_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t MMA8451_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8471Q_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8962_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);
int8_t FXLS8972_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg);

///@}


#endif // DRIVERS_H
