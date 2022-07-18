/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file debug.c
    \brief ApplyPerturbation function used to analyze dynamic performance

    The ApplyPerturbation function applies a user-specified step function to
    prior fusion results which is then "released" in the next fusion cycle.
    When used in conjustion with the NXP Sensor Fusion Toolbox, this provides
    a visual indication of the dynamic behavior of the library.

    Also included is some code for white-box testing within the IAR debug
    environment.  It can be used to evaluate propagation delays for tilt and
    eCompass algorithms.  It makes no sense with regard to "Rotation", because
    that algorithm is simple gyro integration, and will never return to the
    starting point.  It will also overestimate delays for the kalman filters,
    as there is no actual gyro data corresponding to the simulated step function.
    So those filters are not operating as they would in the normal world.
*/

#include "sensor_fusion.h"
#include "control.h"
#include "stdlib.h"
#include "build.h"

/// The ApplyPerturbation function applies a user-specified step function to
/// prior fusion results which is then "released" in the next fusion cycle.
/// When used in conjustion with the NXP Sensor Fusion Toolbox, this provides
/// a visual indication of the dynamic behavior of the library.
/// This function is normally involved via the "sfg." global pointer.
void ApplyPerturbation(SensorFusionGlobals *sfg)
{
#ifdef INCLUDE_DEBUG_FUNCTIONS
    // volatile keyword used to force compiler not to optimize out these
    // variables.  this does unfortunately result in a couple of warnings (which
    // can be ignored) farther down in this code.
    volatile static uint16_t iTestProgress;        ///< Perturbation test status
    volatile static uint16_t iTestDelay = 0;       ///< Measured delay
    //volatile static uint16_t iTestAngle = 0;       ///< Integer Residual angle associated with measured delay
    volatile float angle=0.0f;                     ///< Float Residual angle associated with measured delay
    volatile static float threshold=0;
    static Quaternion StartingQ = {
        .q0 = 1.0,
        .q1 = 0.0,
        .q2 = 0.0,
        .q3 = 0.0
    };
    Quaternion CurrentQ =  {
        .q0 = 1.0,
        .q1 = 0.0,
        .q2 = 0.0,
        .q3 = 0.0
    };
    // cache local copies of control flags so we don't have to keep dereferencing pointers below
    quaternion_type quaternionPacketType;
    quaternionPacketType = sfg->pControlSubsystem->QuaternionPacketType;

    Quaternion  ftmpq;  // scratch quaternion

    // calculate the test perturbation
    switch (sfg->iPerturbation)
    {
        case 1:  // 180 degrees about X
            ftmpq.q0 = 0.0F;
            ftmpq.q1 = 1.0F;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = 0.0F;
            threshold = 90.0;
            break;

        case 2:  // 180 degrees about Y
            ftmpq.q0 = 0.0F;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = 1.0F;
            ftmpq.q3 = 0.0F;
            threshold = 90.0;
            break;

        case 3:  // 180 degrees about Z
            ftmpq.q0 = 0.0F;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = 1.0F;
            threshold = 90.0;
            break;

        case 4:  // -90 degrees about X
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = -ONEOVERSQRT2;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = 0.0F;
            threshold = 45.0;
            break;

        case 5:  // +90 degrees about X
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = ONEOVERSQRT2;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = 0.0F;
            threshold = 45.0;
            break;

        case 6:  // -90 degrees about Y
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = -ONEOVERSQRT2;
            ftmpq.q3 = 0.0F;
            threshold = 45.0;
            break;

        case 7:  // +90 degrees about Y
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = ONEOVERSQRT2;
            ftmpq.q3 = 0.0F;
            threshold = 45.0;
            break;

        case 8:  // -90 degrees about Z
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = -ONEOVERSQRT2;
            threshold = 45.0;
            break;

        case 9:  // +90 degrees about Z
            ftmpq.q0 = ONEOVERSQRT2;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = ONEOVERSQRT2;
            threshold = 45.0;
            break;

        default: // No rotation
            ftmpq.q0 = 1.0F;
            ftmpq.q1 = 0.0F;
            ftmpq.q2 = 0.0F;
            ftmpq.q3 = 0.0F;
            break;
    }

    switch (quaternionPacketType) {
#if F_3DOF_G_BASIC
    case (Q3):
        CurrentQ = sfg->SV_3DOF_G_BASIC.fLPq;
        qAeqAxB(&(sfg->SV_3DOF_G_BASIC.fLPq), &ftmpq);
        break;
#endif
#if F_3DOF_B_BASIC
    case (Q3M):
        CurrentQ = sfg->SV_3DOF_B_BASIC.fLPq;
        qAeqAxB(&(sfg->SV_3DOF_B_BASIC.fLPq), &ftmpq);
        break;
#endif
#if F_3DOF_Y_BASIC
    case (Q3G):
        CurrentQ = sfg->SV_3DOF_Y_BASIC.fq;
        qAeqAxB(&(sfg->SV_3DOF_Y_BASIC.fq), &ftmpq);
        break;
#endif
#if F_6DOF_GB_BASIC
    case (Q6MA):
        CurrentQ = sfg->SV_6DOF_GB_BASIC.fLPq;
        qAeqAxB(&(sfg->SV_6DOF_GB_BASIC.fLPq), &ftmpq);
        break;
#endif
#if F_6DOF_GY_KALMAN
    case (Q6AG):
        CurrentQ = sfg->SV_6DOF_GY_KALMAN.fqPl;
        qAeqAxB(&(sfg->SV_6DOF_GY_KALMAN.fqPl), &ftmpq);
        break;
#endif
#if F_9DOF_GBY_KALMAN
    case (Q9):
        CurrentQ = sfg->SV_9DOF_GBY_KALMAN.fqPl;
        qAeqAxB(&(sfg->SV_9DOF_GBY_KALMAN.fqPl), &ftmpq);
        break;
#endif
    default:
        CurrentQ.q0 = 1.0;
        CurrentQ.q1 = 0.0;
        CurrentQ.q2 = 0.0;
        CurrentQ.q3 = 0.0;
        break;
    }

    // Begin of code for white-box testing - requires IAR debugger
    switch (iTestProgress) {
    case 0:  // no test in progress, check to see if we should start one
        if (sfg->iPerturbation>0) {
            // Start Test
            iTestProgress = 1;
            sfg->iPerturbation = 0;
            iTestDelay = 0;
            //iTestAngle = 0;
            // We'll need the complex conjugate of the starting quaternion
            StartingQ.q0 = CurrentQ.q0;
            StartingQ.q1 = -1 * CurrentQ.q1;
            StartingQ.q2 = -1 * CurrentQ.q2;
            StartingQ.q3 = -1 * CurrentQ.q3;
        }
        break;
    default:  // Test in progress, check to see if trigger reached
        iTestDelay += 1;
        qAeqAxB(&CurrentQ, &StartingQ);
        angle = 2 * F180OVERPI * acos(CurrentQ.q0);
        angle = fmod(fabs(angle), 180.0);
        //iTestAngle = (uint16_t) (10 * angle);
        // In IAR, you can use a Log breakpoint to monitor "return to stationary pose".
        // Use the following expression in the Message field and check the
        // checkbox for C-Spy macro.  Then Click any of the "Test" buttons
        // in the Sensor Fusion Toolbox and monitor the results in the Messages window.
        //"Delay=", iTestDelay:%d, " Angle=",iTestAngle:%d
        if (angle<threshold)           iTestProgress=2;  // triggered
        if (angle < (0.2 * threshold)) iTestProgress=0;  // test is done
        if (iTestDelay>100) iTestProgress=0;  // abort test
        break;
    }
    // End of code for white-box testing
#endif
}
