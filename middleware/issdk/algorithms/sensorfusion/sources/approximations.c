/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/*! \file approximations.c
    \brief Math approximations file

    Significant efficiencies were found by creating a set of trig functions
    which trade off precision for improved power/CPU performance.  Full details
    are included in Application Note AN5015: Trigonometry Approximations
*/

#include "math.h"
#include "stdlib.h"
#include "stdint.h"

#include "approximations.h"

// function returns an approximation to angle(deg)=asin(x) for x in the range -1 <= x <= 1
// and returns -90 <= angle <= 90 deg

// maximum error is 10.29E-6 deg
float fasin_deg(float x)
{
    // for robustness, check for invalid argument
    if (x >= 1.0F) return 90.0F;
    if (x <= -1.0F) return -90.0F;

    // call the atan which will return an angle in the correct range -90 to 90 deg
    // this line cannot fail from division by zero or negative square root since |x| < 1
    return (fatan_deg(x / sqrtf(1.0F - x * x)));
}

// function returns an approximation to angle(deg)=acos(x) for x in the range -1 <= x <= 1
// and returns 0 <= angle <= 180 deg

// maximum error is 14.67E-6 deg
float facos_deg(float x)
{
    // for robustness, check for invalid arguments
    if (x >= 1.0F) return 0.0F;
    if (x <= -1.0F) return 180.0F;

    // call the atan which will return an angle in the incorrect range -90 to 90 deg
    // these lines cannot fail from division by zero or negative square root
    if (x == 0.0F) return 90.0F;
    if (x > 0.0F) return fatan_deg((sqrtf(1.0F - x * x) / x));
    return 180.0F + fatan_deg((sqrtf(1.0F - x * x) / x));
}

// function returns angle in range -90 to 90 deg

// maximum error is 9.84E-6 deg
float fatan_deg(float x)
{
    float   fangledeg;                  // compute computed (deg)
    int8_t    ixisnegative;             // argument x is negative
    int8_t    ixexceeds1;               // argument x is greater than 1.0
    int8_t    ixmapped;                 // argument in range tan(15 deg) to tan(45 deg)=1.0
#define TAN15DEG    0.26794919243F      // tan(15 deg) = 2 - sqrt(3)
#define TAN30DEG    0.57735026919F      // tan(30 deg) = 1/sqrt(3)
    // reset all flags
    ixisnegative = ixexceeds1 = ixmapped = 0;

    // test for negative argument to allow use of tan(-x)=-tan(x)
    if (x < 0.0F)
    {
        x = -x;
        ixisnegative = 1;
    }

    // test for argument above 1 to allow use of atan(x)=pi/2-atan(1/x)
    if (x > 1.0F)
    {
        x = 1.0F / x;
        ixexceeds1 = 1;
    }

    // at this point, x is in the range 0 to 1 inclusive
    // map argument onto range -tan(15 deg) to tan(15 deg)
    // using tan(angle-30deg) = (tan(angle)-tan(30deg)) / (1 + tan(angle)tan(30deg))
    // tan(15deg) maps to tan(-15 deg) = -tan(15 deg)
    // 1. maps to (sqrt(3) - 1) / (sqrt(3) + 1) = 2 - sqrt(3) = tan(15 deg)
    if (x > TAN15DEG)
    {
        x = (x - TAN30DEG) / (1.0F + TAN30DEG * x);
        ixmapped = 1;
    }

    // call the atan estimator to obtain -15 deg <= angle <= 15 deg
    fangledeg = fatan_15deg(x);

    // undo the distortions applied earlier to obtain -90 deg <= angle <= 90 deg
    if (ixmapped) fangledeg += 30.0F;
    if (ixexceeds1) fangledeg = 90.0F - fangledeg;
    if (ixisnegative) fangledeg = -fangledeg;

    return (fangledeg);
}

// function returns approximate atan2 angle in range -180 to 180 deg

// maximum error is 14.58E-6 deg
float fatan2_deg(float y, float x)
{
    // check for zero x to avoid division by zero
    if (x == 0.0F)
    {
        // return 90 deg for positive y
        if (y > 0.0F) return 90.0F;

        // return -90 deg for negative y
        if (y < 0.0F) return -90.0F;

        // otherwise y= 0.0 and return 0 deg (invalid arguments)
        return 0.0F;
    }

    // from here onwards, x is guaranteed to be non-zero
    // compute atan2 for quadrant 1 (0 to 90 deg) and quadrant 4 (-90 to 0 deg)
    if (x > 0.0F) return (fatan_deg(y / x));

    // compute atan2 for quadrant 2 (90 to 180 deg)
    if ((x < 0.0F) && (y > 0.0F)) return (180.0F + fatan_deg(y / x));

    // compute atan2 for quadrant 3 (-180 to -90 deg)
    return (-180.0F + fatan_deg(y / x));
}

// approximation to inverse tan function (deg) for x in range
// -tan(15 deg) to tan(15 deg) giving an output -15 deg <= angle <= 15 deg

// using modified Pade[3/2] approximation
float fatan_15deg(float x)
{
    float   x2;                 // x^2
#define PADE_A  96.644395816F   // theoretical Pade[3/2] value is 5/3*180/PI=95.49296
#define PADE_B  25.086941612F   // theoretical Pade[3/2] value is 4/9*180/PI=25.46479
#define PADE_C  1.6867633134F   // theoretical Pade[3/2] value is 5/3=1.66667
    // compute the approximation to the inverse tangent
    // the function is anti-symmetric as required for positive and negative arguments
    x2 = x * x;
    return (x * (PADE_A + x2 * PADE_B) / (PADE_C + x2));
}
