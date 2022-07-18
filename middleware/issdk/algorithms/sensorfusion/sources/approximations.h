/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef APPROXIMATIONS_H
#define APPROXIMATIONS_H

/*! \file approximations.h
    \brief Math approximations file

    Significant efficiencies were found by creating a set of trig functions
    which trade off precision for improved power/CPU performance.  Full details
    are included in Application Note AN5015: Trigonometry Approximations
*/

// function prototypes
float fasin_deg(float x);
float facos_deg(float x);
float fatan_deg(float x);
float fatan2_deg(float y, float x);
float fatan_15deg(float x);

#endif // APPROXIMATIONS_H
