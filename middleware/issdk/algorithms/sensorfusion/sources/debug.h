/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file debug.h
    \brief ApplyPerturbation function used to analyze dynamic performance

    The ApplyPerturbation function applies a user-specified step function to
    prior fusion results which is then "released" in the next fusion cycle.
    When used in conjustion with the NXP Sensor Fusion Toolbox, this provides
    a visual indication of the dynamic behavior of the library.
*/


#ifndef DEBUG_H
#define DEBUG_H

// prototypes for functions defined in debug.c
void ApplyPerturbation(SensorFusionGlobals *sfg);

#endif // #ifndef DEBUG_H
