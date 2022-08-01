/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file driver_pit.h
    \brief Provides a simple abstraction for a periodic interval timer.

   Bare metal implementations of the sensor fusion library require at least
   one periodic interrupt for use as a timebase for sensor fusion functions.
   The Periodic Interval Timer (PIT) is one such module that is commonly
   found on NXP Kinetis MCUs.  The PIT functions are only referenced at the
   main() level.  There is no interaction within the fusion routines themselves.
*/


#ifndef SENSOR_FUSION_INCLUDES_DRIVER_PIT_H_
#define SENSOR_FUSION_INCLUDES_DRIVER_PIT_H_

void pit_init(uint32_t microseconds);
extern volatile bool pitIsrFlag;


#endif /* SENSOR_FUSION_INCLUDES_DRIVER_PIT_H_ */
