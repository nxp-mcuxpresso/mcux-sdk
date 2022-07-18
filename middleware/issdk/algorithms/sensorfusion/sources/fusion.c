/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// This is the file that contains the fusion routines.  It is STRONGLY RECOMMENDED
// that the casual developer NOT TOUCH THIS FILE.

/*! \file fusion.c
    \brief Lower level sensor fusion interface
*/

#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#include "sensor_fusion.h"
#include "fusion.h"
#include "orientation.h"
#include "matrix.h"
#include "approximations.h"
#include "drivers.h"
#include "control.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// intialization functions for the sensor fusion algorithms
//////////////////////////////////////////////////////////////////////////////////////////////////

// function initializes the sensor fusion and magnetic calibration and sets loopcounter to zero
void fInitializeFusion(SensorFusionGlobals *sfg)
{
    // reset the quaternion type to the default packet type
    // sfg->pControlSubsystem->QuaternionPacketType = sfg->pControlSubsystem->DefaultQuaternionPacketType;

    // force a reset of all the algorithms next time they execute
    // the initialization will result in the default and current quaternion being set to the most sophisticated
    // algorithm supported by the build
#if F_1DOF_P_BASIC
    sfg->SV_1DOF_P_BASIC.resetflag    = true;
#endif
#if F_3DOF_B_BASIC
    sfg->SV_3DOF_B_BASIC.resetflag    = true;
#endif
#if F_3DOF_G_BASIC
    sfg->SV_3DOF_G_BASIC.resetflag    = true;
#endif
#if F_3DOF_Y_BASIC
    sfg->SV_3DOF_Y_BASIC.resetflag    = true;
#endif
#if F_6DOF_GB_BASIC
    sfg->SV_6DOF_GB_BASIC.resetflag   = true;
#endif
#if F_6DOF_GY_KALMAN
    sfg->SV_6DOF_GY_KALMAN.resetflag  = true;
#endif
#if F_9DOF_GBY_KALMAN
    sfg->SV_9DOF_GBY_KALMAN.resetflag = true;
#endif

    // reset the loop counter to zero for first iteration
    sfg->loopcounter = 0;
    return;
}

void fFuseSensors(struct SV_1DOF_P_BASIC *pthisSV_1DOF_P_BASIC,
                  struct SV_3DOF_G_BASIC *pthisSV_3DOF_G_BASIC,
                  struct SV_3DOF_B_BASIC *pthisSV_3DOF_B_BASIC,
                  struct SV_3DOF_Y_BASIC *pthisSV_3DOF_Y_BASIC,
                  struct SV_6DOF_GB_BASIC *pthisSV_6DOF_GB_BASIC,
                  struct SV_6DOF_GY_KALMAN *pthisSV_6DOF_GY_KALMAN,
                  struct SV_9DOF_GBY_KALMAN *pthisSV_9DOF_GBY_KALMAN,
                  struct AccelSensor *pthisAccel,
                  struct MagSensor *pthisMag,
                  struct GyroSensor *pthisGyro,
                  struct PressureSensor *pthisPressure,
                  struct MagCalibration *pthisMagCal)
{
    // 1DOF Pressure: call the low pass filter algorithm
#if F_1DOF_P_BASIC
    if (pthisSV_1DOF_P_BASIC)
    {
        ARM_systick_start_ticks(&(pthisSV_1DOF_P_BASIC->systick));
        fRun_1DOF_P_BASIC(pthisSV_1DOF_P_BASIC, pthisPressure);
        pthisSV_1DOF_P_BASIC->systick = ARM_systick_elapsed_ticks(pthisSV_1DOF_P_BASIC->systick);
    }
#endif

    // 3DOF Accel Basic: call the tilt algorithm
#if F_3DOF_G_BASIC
    if (pthisSV_3DOF_G_BASIC)
    {
        ARM_systick_start_ticks(&(pthisSV_3DOF_G_BASIC->systick));
        fRun_3DOF_G_BASIC(pthisSV_3DOF_G_BASIC, pthisAccel);
        pthisSV_3DOF_G_BASIC->systick = ARM_systick_elapsed_ticks(pthisSV_3DOF_G_BASIC->systick);
    }
#endif

    // 3DOF Magnetometer Basic: call the 2D vehicle compass algorithm
#if F_3DOF_B_BASIC
    if (pthisSV_3DOF_B_BASIC)
    {
        ARM_systick_start_ticks(&(pthisSV_3DOF_B_BASIC->systick));
        fRun_3DOF_B_BASIC(pthisSV_3DOF_B_BASIC, pthisMag);
        pthisSV_3DOF_B_BASIC->systick = ARM_systick_elapsed_ticks(pthisSV_3DOF_B_BASIC->systick);
    }
#endif

    // 3DOF Gyro Basic: call the gyro integration algorithm
#if F_3DOF_Y_BASIC
    if (pthisSV_3DOF_Y_BASIC)
    {
        ARM_systick_start_ticks(&(pthisSV_3DOF_Y_BASIC->systick));
        fRun_3DOF_Y_BASIC(pthisSV_3DOF_Y_BASIC, pthisGyro);
        pthisSV_3DOF_Y_BASIC->systick = ARM_systick_elapsed_ticks(pthisSV_3DOF_Y_BASIC->systick);
    }
#endif

    // 6DOF Accel / Mag: Basic: call the eCompass orientation algorithm
#if F_6DOF_GB_BASIC
    if (pthisSV_6DOF_GB_BASIC)
    {
        ARM_systick_start_ticks(&(pthisSV_6DOF_GB_BASIC->systick));
        fRun_6DOF_GB_BASIC(pthisSV_6DOF_GB_BASIC, pthisMag, pthisAccel);
        pthisSV_6DOF_GB_BASIC->systick = ARM_systick_elapsed_ticks(pthisSV_6DOF_GB_BASIC->systick);
    }
#endif

    // 6DOF Accel / Gyro: call the Kalman filter orientation algorithm
#if F_6DOF_GY_KALMAN
    if (pthisSV_6DOF_GY_KALMAN)
    {
        ARM_systick_start_ticks(&(pthisSV_6DOF_GY_KALMAN->systick));
        fRun_6DOF_GY_KALMAN(pthisSV_6DOF_GY_KALMAN, pthisAccel, pthisGyro);
        pthisSV_6DOF_GY_KALMAN->systick = ARM_systick_elapsed_ticks(pthisSV_6DOF_GY_KALMAN->systick);
    }
#endif

    // 9DOF Accel / Mag / Gyro: call the Kalman filter orientation algorithm
#if F_9DOF_GBY_KALMAN
    if (pthisSV_9DOF_GBY_KALMAN)
    {
        ARM_systick_start_ticks(&(pthisSV_9DOF_GBY_KALMAN->systick));
        fRun_9DOF_GBY_KALMAN(pthisSV_9DOF_GBY_KALMAN, pthisAccel, pthisMag,
                             pthisGyro, pthisMagCal);
        pthisSV_9DOF_GBY_KALMAN->systick = ARM_systick_elapsed_ticks(pthisSV_9DOF_GBY_KALMAN->systick);
    }
#endif
    return;
}

void fInit_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV,
                        struct PressureSensor *pthisPressure, float flpftimesecs)
{
    // set algorithm sampling interval (typically 40Hz) and low pass filter
    // Note: the MPL3115 sensor only updates its output every 1s and is therefore repeatedly oversampled at 40Hz
    // but executing the exponenial filter at the 40Hz rate also performs an interpolation giving smoother output.
    // set algorithm sampling interval (typically 40Hz)
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;

    // set low pass filter constant with maximum value 1.0 (all pass) decreasing to 0.0 (increasing low pass)
    if (flpftimesecs > pthisSV->fdeltat)
        pthisSV->flpf = pthisSV->fdeltat / flpftimesecs;
    else
        pthisSV->flpf = 1.0F;

    // initialize the low pass filters to current measurement
    pthisSV->fLPH = pthisPressure->fH;
    pthisSV->fLPT = pthisPressure->fT;

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}   // end fInit_1DOF_P_BASIC

void fInit_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV,
                        struct AccelSensor *pthisAccel, float flpftimesecs)
{
    // set algorithm sampling interval (typically 40Hz)
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;

    // set low pass filter constant with maximum value 1.0 (all pass) decreasing to 0.0 (increasing low pass)
    if (flpftimesecs > pthisSV->fdeltat)
        pthisSV->flpf = pthisSV->fdeltat / flpftimesecs;
    else
        pthisSV->flpf = 1.0F;

    // apply the tilt estimation algorithm to initialize the low pass orientation matrix and quaternion
#if THISCOORDSYSTEM == NED
    f3DOFTiltNED(pthisSV->fLPR, pthisAccel->fGc);
#elif THISCOORDSYSTEM == ANDROID
    f3DOFTiltAndroid(pthisSV->fLPR, pthisAccel->fGc);
#else // WIN8
    f3DOFTiltWin8(pthisSV->fLPR, pthisAccel->fGc);
#endif
    fQuaternionFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPq));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}   // end fInit_3DOF_G_BASIC

void fInit_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV,
                        struct MagSensor *pthisMag, float flpftimesecs)
{
    // set algorithm sampling interval (typically 40Hz)
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;

    // set low pass filter constant with maximum value 1.0 (all pass) decreasing to 0.0 (increasing low pass)
    if (flpftimesecs > pthisSV->fdeltat)
        pthisSV->flpf = pthisSV->fdeltat / flpftimesecs;
    else
        pthisSV->flpf = 1.0F;

    // initialize the low pass filtered magnetometer orientation matrix and quaternion using fBc
#if THISCOORDSYSTEM == NED
    f3DOFMagnetometerMatrixNED(pthisSV->fLPR, pthisMag->fBc);
#elif THISCOORDSYSTEM == ANDROID
    f3DOFMagnetometerMatrixAndroid(pthisSV->fLPR, pthisMag->fBc);
#else // WIN8
    f3DOFMagnetometerMatrixWin8(pthisSV->fLPR, pthisMag->fBc);
#endif
    fQuaternionFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPq));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}   // end fInit_3DOF_B_BASIC

void fInit_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV)
{
    // compute the sampling time intervals (secs)
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;

    // initialize orientation estimate to flat
    f3x3matrixAeqI(pthisSV->fR);
    fqAeq1(&(pthisSV->fq));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}   // end fInit_3DOF_Y_BASIC

void fInit_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV,
                         struct AccelSensor *pthisAccel,
                         struct MagSensor *pthisMag, float flpftimesecs)
{
    float ftmp;

    // set algorithm sampling interval (typically 40Hz)
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;

    // set low pass filter constant with maximum value 1.0 (all pass) decreasing to 0.0 (increasing low pass)
    if (flpftimesecs > pthisSV->fdeltat)
        pthisSV->flpf = pthisSV->fdeltat / flpftimesecs;
    else
        pthisSV->flpf = 1.0F;

    // initialize the instantaneous orientation matrix, inclination angle and quaternion
#if THISCOORDSYSTEM == NED
    feCompassNED(pthisSV->fLPR, &(pthisSV->fLPDelta), &ftmp, &ftmp, pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp );
#elif THISCOORDSYSTEM == ANDROID
    feCompassAndroid(pthisSV->fLPR, &(pthisSV->fLPDelta), &ftmp, &ftmp, pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp);
#else // WIN8
    feCompassWin8(pthisSV->fLPR, &(pthisSV->fLPDelta), &ftmp, &ftmp, pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp);
#endif
    fQuaternionFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPq));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}   // end fInit_6DOF_GB_BASIC

// function initalizes the 6DOF accel + gyro Kalman filter algorithm
void fInit_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV,
                          struct AccelSensor *pthisAccel,
                          struct GyroSensor *pthisGyro)
{
    float   *pFlash;    // pointer to flash float words
    int8    i;          // loop counter

    // compute and store useful product terms to save floating point calculations later
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;
    pthisSV->fQwbOver3 = FQWB_6DOF_GY_KALMAN / 3.0F;
    pthisSV->fAlphaOver2 = FPIOVER180 * pthisSV->fdeltat / 2.0F;
    pthisSV->fAlphaSqOver4 = pthisSV->fAlphaOver2 * pthisSV->fAlphaOver2;
    pthisSV->fAlphaQwbOver6 = pthisSV->fAlphaOver2 * pthisSV->fQwbOver3;
    pthisSV->fAlphaSqQvYQwbOver12 = pthisSV->fAlphaSqOver4 * (FQVY_6DOF_GY_KALMAN + FQWB_6DOF_GY_KALMAN) / 3.0F;
    pthisSV->fMaxGyroOffsetChange = sqrtf(fabs(FQWB_6DOF_GY_KALMAN)) / (float)FUSION_HZ;

    // zero the a posteriori gyro offset and error vectors
    for (i = CHX; i <= CHZ; i++)
    {
        pthisSV->fqgErrPl[i] = 0.0F;
        pthisSV->fbErrPl[i] = 0.0F;
    }

    // check to see if a gyro calibration exists in flash
    // the standard value for erased flash is 0xFF in each byte but for portability check against 0x12345678
#ifndef SIMULATION
    pFlash = (float *) (CALIBRATION_NVM_ADDR + GYRO_NVM_OFFSET);
    if (*((uint32 *) pFlash++) == 0x12345678)
    {
        // copy the gyro calibration from flash into the state vector
        for (i = CHX; i <= CHZ; i++) pthisSV->fbPl[i] = *(pFlash++);
    }
    else
    {
#endif
        // set the gyro offset to the current measurement if within limits
        for (i = CHX; i <= CHZ; i++)
        {
            if ((pthisGyro->fYs[i] >= FMIN_6DOF_GY_BPL) &&
                (pthisGyro->fYs[i] <= FMAX_6DOF_GY_BPL))
                pthisSV->fbPl[i] = pthisGyro->fYs[i];
            else
                pthisSV->fbPl[i] = 0.0F;
        }
#ifndef SIMULATION
    }
#endif
    // initialize the a posteriori orientation state vector to the tilt orientation
#if THISCOORDSYSTEM == NED
    f3DOFTiltNED(pthisSV->fRPl, pthisAccel->fGc);
#elif THISCOORDSYSTEM == ANDROID
    f3DOFTiltAndroid(pthisSV->fRPl, pthisAccel->fGc);
#else // Win8
    f3DOFTiltWin8(pthisSV->fRPl, pthisAccel->fGc);
#endif
    fQuaternionFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fqPl));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
}                       // end fInit_6DOF_GY_KALMAN

// function initializes the 9DOF Kalman filter
void fInit_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV, struct AccelSensor *pthisAccel, struct MagSensor *pthisMag,
    struct GyroSensor *pthisGyro, struct MagCalibration *pthisMagCal)
{
    float ftmp;// scratch
    float *pFlash;// pointer to flash float words
    int8 i;// loop counter

    // compute and store useful product terms to save floating point calculations later
    pthisSV->fdeltat = 1.0F / (float) FUSION_HZ;
    pthisSV->fgdeltat = GTOMSEC2 * pthisSV->fdeltat;
    pthisSV->fQwbOver3 = FQWB_9DOF_GBY_KALMAN / 3.0F;
    pthisSV->fAlphaOver2 = FPIOVER180 * pthisSV->fdeltat / 2.0F;
    pthisSV->fAlphaSqOver4 = pthisSV->fAlphaOver2 * pthisSV->fAlphaOver2;
    pthisSV->fAlphaQwbOver6 = pthisSV->fAlphaOver2 * pthisSV->fQwbOver3;
    pthisSV->fAlphaSqQvYQwbOver12 = pthisSV->fAlphaSqOver4 * (FQVY_9DOF_GBY_KALMAN + FQWB_9DOF_GBY_KALMAN) / 3.0F;
    pthisSV->fMaxGyroOffsetChange = sqrtf(fabs(FQWB_9DOF_GBY_KALMAN)) / (float)FUSION_HZ;

    // zero the a posteriori error vectors and inertial outputs
    for (i = CHX; i <= CHZ; i++) {
        pthisSV->fqgErrPl[i] = 0.0F;
        pthisSV->fqmErrPl[i] = 0.0F;
        pthisSV->fbErrPl[i] = 0.0F;
        pthisSV->fVelGl[i] = 0.0F;
        pthisSV->fDisGl[i] = 0.0F;
    }

    // check to see if a gyro calibration exists in flash
    // the standard value for erased flash is 0xFF in each byte but for portability check against 0x12345678
#ifndef SIMULATION
    pFlash = (float *) (CALIBRATION_NVM_ADDR + GYRO_NVM_OFFSET);
    if (*((uint32*) pFlash++) == 0x12345678) {
    // copy the gyro calibration from flash into the state vector
        for (i = CHX; i <= CHZ; i++)
            pthisSV->fbPl[i] = *(pFlash++);
    } else {
#endif
        // set the gyro offset to the current measurement if within limits
        for (i = CHX; i <= CHZ; i++) {
            if ((pthisGyro->fYs[i] >= FMIN_9DOF_GBY_BPL) && (pthisGyro->fYs[i] <= FMAX_9DOF_GBY_BPL))
                pthisSV->fbPl[i] = pthisGyro->fYs[i];
            else
                pthisSV->fbPl[i] = 0.0F;
        }
#ifndef SIMULATION
     }
#endif

    // initialize the posteriori orientation state vector to the instantaneous eCompass orientation
    pthisSV->iFirstAccelMagLock = false;
#if THISCOORDSYSTEM == NED
    feCompassNED(pthisSV->fRPl, &(pthisSV->fDeltaPl), &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
        pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp);
#elif THISCOORDSYSTEM == ANDROID
    feCompassAndroid(pthisSV->fRPl, &(pthisSV->fDeltaPl),  &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
        pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp);
#else  // WIN8
    feCompassWin8(pthisSV->fRPl, &(pthisSV->fDeltaPl), &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
        pthisMag->fBc, pthisAccel->fGc, &ftmp, &ftmp);
#endif
    fQuaternionFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fqPl));

    // clear the reset flag
    pthisSV->resetflag = false;

    return;
} // end fInit_9DOF_GBY_KALMAN

//////////////////////////////////////////////////////////////////////////////////////////////////

// run time functions for the sensor fusion algorithms
//////////////////////////////////////////////////////////////////////////////////////////////////

// 1DOF pressure function
void fRun_1DOF_P_BASIC(struct SV_1DOF_P_BASIC *pthisSV,
                       struct PressureSensor *pthisPressure)
{
    // if requested, do a reset and return
    if (pthisSV->resetflag)
    {
        fInit_1DOF_P_BASIC(pthisSV, pthisPressure, FLPFSECS_1DOF_P_BASIC);
        return;
    }

    // exponentially low pass filter the pressure and temperature.
    // when executed at (typically) 40Hz, this filter interpolates the raw signals which are
    // output every 1s in Auto Acquisition mode.
    pthisSV->fLPH += pthisSV->flpf * (pthisPressure->fH - pthisSV->fLPH);
    pthisSV->fLPT += pthisSV->flpf * (pthisPressure->fT - pthisSV->fLPT);

    return;
}   // end fRun_1DOF_P_BASIC

// 3DOF orientation function which calls tilt functions and implements low pass filters
void fRun_3DOF_G_BASIC(struct SV_3DOF_G_BASIC *pthisSV,
                       struct AccelSensor *pthisAccel)
{
    // if requested, do a reset and return
    if (pthisSV->resetflag)
    {
        fInit_3DOF_G_BASIC(pthisSV, pthisAccel, FLPFSECS_3DOF_G_BASIC);
        return;
    }

    // apply the tilt estimation algorithm to get the instantaneous orientation matrix
#if THISCOORDSYSTEM == NED
    f3DOFTiltNED(pthisSV->fR, pthisAccel->fGc);
#elif THISCOORDSYSTEM == ANDROID
    f3DOFTiltAndroid(pthisSV->fR, pthisAccel->fGc);
#else // WIN8
    f3DOFTiltWin8(pthisSV->fR, pthisAccel->fGc);
#endif

    // compute the instantaneous quaternion and low pass filter
    fQuaternionFromRotationMatrix(pthisSV->fR, &(pthisSV->fq));
    fLPFOrientationQuaternion(&(pthisSV->fq), &(pthisSV->fLPq), pthisSV->flpf,
                              pthisSV->fdeltat, pthisSV->fOmega);

    // compute the low pass rotation matrix and rotation vector from low pass filtered quaternion
    fRotationMatrixFromQuaternion(pthisSV->fLPR, &(pthisSV->fLPq));
    fRotationVectorDegFromQuaternion(&(pthisSV->fLPq), pthisSV->fLPRVec);

    // calculate the Euler angles from the low pass orientation matrix
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                    &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                    &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                        &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                        &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                     &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                     &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#endif

    // force the yaw and compass angles to zero
    pthisSV->fLPPsi = pthisSV->fLPRho = 0.0F;

    return;
}   // end fRun_3DOF_G_BASIC

// 2D automobile eCompass
void fRun_3DOF_B_BASIC(struct SV_3DOF_B_BASIC *pthisSV, struct MagSensor *pthisMag)
{
    // if requested, do a reset and return
    if (pthisSV->resetflag)
    {
        fInit_3DOF_B_BASIC(pthisSV, pthisMag, FLPFSECS_3DOF_B_BASIC);
        return;
    }

    // calculate the 3DOF magnetometer orientation matrix from fBc
#if THISCOORDSYSTEM == NED
    f3DOFMagnetometerMatrixNED(pthisSV->fR, pthisMag->fBc);
#elif THISCOORDSYSTEM == ANDROID
    f3DOFMagnetometerMatrixAndroid(pthisSV->fR, pthisMag->fBc);
#else // WIN8
    f3DOFMagnetometerMatrixWin8(pthisSV->fR, pthisMag->fBc);
#endif

    //  compute the instantaneous quaternion and low pass filter
    fQuaternionFromRotationMatrix(pthisSV->fR, &(pthisSV->fq));
    fLPFOrientationQuaternion(&(pthisSV->fq), &(pthisSV->fLPq), pthisSV->flpf,
                              pthisSV->fdeltat, pthisSV->fOmega);

    // compute the low pass rotation matrix and rotation vector from low pass filtered quaternion
    fRotationMatrixFromQuaternion(pthisSV->fLPR, &(pthisSV->fLPq));
    fRotationVectorDegFromQuaternion(&(pthisSV->fLPq), pthisSV->fLPRVec);

    // calculate the Euler angles from the low pass orientation matrix
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                    &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                    &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                        &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                        &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                     &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                     &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#endif
    return;
}

// basic gyro integration function
void fRun_3DOF_Y_BASIC(struct SV_3DOF_Y_BASIC *pthisSV,
                       struct GyroSensor *pthisGyro)
{
    Quaternion  ftmpq;  // scratch quaternion
    int8        i;      // loop counter

    // if requested, do a reset and return
    if (pthisSV->resetflag)
    {
        fInit_3DOF_Y_BASIC(pthisSV);
        return;
    }

    // perform an approximate gyro integration for this algorithm using the average of all gyro measurments
    // in the FIFO rather than computing the products of the individual quaternions.
    // the reason is this algorithm does not estimate and subtract the gyro offset so any loss of integration accuracy
    // from using the average gyro measurement is irrelevant.
    // calculate the angular velocity (deg/s) and rotation vector from the average measurement
    for (i = CHX; i <= CHZ; i++) pthisSV->fOmega[i] = pthisGyro->fYs[i];

    // compute the incremental rotation quaternion ftmpq, rotate the orientation quaternion fq
    // and re-normalize fq to prevent error propagation
    fQuaternionFromRotationVectorDeg(&ftmpq, pthisSV->fOmega, pthisSV->fdeltat);
    qAeqAxB(&(pthisSV->fq), &ftmpq);
    fqAeqNormqA(&(pthisSV->fq));

    // get the rotation matrix and rotation vector from the orientation quaternion fq
    fRotationMatrixFromQuaternion(pthisSV->fR, &(pthisSV->fq));
    fRotationVectorDegFromQuaternion(&(pthisSV->fq), pthisSV->fRVec);

    // compute the Euler angles from the orientation matrix
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fR, &(pthisSV->fPhi),
                                    &(pthisSV->fThe), &(pthisSV->fPsi),
                                    &(pthisSV->fRho), &(pthisSV->fChi));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fR, &(pthisSV->fPhi),
                                        &(pthisSV->fThe), &(pthisSV->fPsi),
                                        &(pthisSV->fRho), &(pthisSV->fChi));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fR, &(pthisSV->fPhi),
                                     &(pthisSV->fThe), &(pthisSV->fPsi),
                                     &(pthisSV->fRho), &(pthisSV->fChi));
#endif
    return;
}                       // end fRun_3DOF_Y_BASIC

// 6DOF eCompass orientation function
void fRun_6DOF_GB_BASIC(struct SV_6DOF_GB_BASIC *pthisSV,
                        struct MagSensor *pthisMag, struct AccelSensor *pthisAccel)
{
    float ftmp1, ftmp2, ftmp3, ftmp4;

    // if requested, do a reset and return
    if (pthisSV->resetflag)
    {
        fInit_6DOF_GB_BASIC(pthisSV, pthisAccel, pthisMag,
                            FLPFSECS_6DOF_GB_BASIC);
        return;
    }

    // call the eCompass algorithm to get the instantaneous orientation matrix and inclination angle
#if THISCOORDSYSTEM == NED
    feCompassNED(pthisSV->fR, &(pthisSV->fDelta), &ftmp1, &ftmp2, pthisMag->fBc, pthisAccel->fGc, &ftmp3, &ftmp4);
#elif THISCOORDSYSTEM == ANDROID
    feCompassAndroid(pthisSV->fR, &(pthisSV->fDelta), &ftmp1, &ftmp2, pthisMag->fBc, pthisAccel->fGc, &ftmp3, &ftmp4);
#else  // WIN8
    feCompassWin8(pthisSV->fR, &(pthisSV->fDelta), &ftmp1, &ftmp2, pthisMag->fBc, pthisAccel->fGc, &ftmp3, &ftmp4);
#endif

    //  compute the instantaneous quaternion and low pass filter
    fQuaternionFromRotationMatrix(pthisSV->fR, &(pthisSV->fq));
    fLPFOrientationQuaternion(&(pthisSV->fq), &(pthisSV->fLPq), pthisSV->flpf,
                              pthisSV->fdeltat, pthisSV->fOmega);

    // compute the low pass rotation matrix and rotation vector from low pass filtered quaternion
    fRotationMatrixFromQuaternion(pthisSV->fLPR, &(pthisSV->fLPq));
    fRotationVectorDegFromQuaternion(&(pthisSV->fLPq), pthisSV->fLPRVec);

    // calculate the Euler angles from the low pass orientation matrix
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                    &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                    &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                        &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                        &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fLPR, &(pthisSV->fLPPhi),
                                     &(pthisSV->fLPThe), &(pthisSV->fLPPsi),
                                     &(pthisSV->fLPRho), &(pthisSV->fLPChi));
#endif

    // low pass filter the geomagnetic inclination angle with a simple exponential filter
    pthisSV->fLPDelta += pthisSV->flpf * (pthisSV->fDelta - pthisSV->fLPDelta);

    return;
}   // end fRun_6DOF_GB_BASIC

// 6DOF accelerometer+gyroscope orientation function implemented using indirect complementary Kalman filter
void fRun_6DOF_GY_KALMAN(struct SV_6DOF_GY_KALMAN *pthisSV,
                         struct AccelSensor *pthisAccel,
                         struct GyroSensor *pthisGyro)
{
    // local scalars and arrays
    float       ftmpMi3x1[3];       // temporary vector used for a priori calculations
    float       ftmp3DOF3x1[3];     // temporary vector used for 3DOF calculations
    float       ftmpA3x3[3][3];     // scratch 3x3 matrix
    float       fQvGQa;             // accelerometer noise covariance to 1g sphere
    float       fC3x6ik;            // element i, k of measurement matrix C
    float       fC3x6jk;            // element j, k of measurement matrix C
    float       fmodGc;             // modulus of fGc[]
    Quaternion  fqMi;               // a priori orientation quaternion
    Quaternion  ftmpq;              // scratch quaternion
    float       ftmp;               // scratch float
    int8        ierror;             // matrix inversion error flag
    int8        i,
                j,
                k;                  // loop counters

    // working arrays for 3x3 matrix inversion
    float       *pfRows[3];
    int8        iColInd[3];
    int8        iRowInd[3];
    int8        iPivot[3];

    // if requested, do a reset initialization with no further processing
    if (pthisSV->resetflag)
    {
        fInit_6DOF_GY_KALMAN(pthisSV, pthisAccel, pthisGyro);
        return;
    }

    // compute the average angular velocity (used for display only) from the average measurement minus gyro offset
    for (i = CHX; i <= CHZ; i++)
        pthisSV->fOmega[i] = (float) pthisGyro->iYs[i] *
            pthisGyro->fDegPerSecPerCount -
            pthisSV->fbPl[i];

    // initialize the a priori orientation quaternion fqMi to the previous iteration's a posteriori estimate
    // and incrementally rotate fqMi by the contents of the gyro FIFO buffer
    fqMi = pthisSV->fqPl;
    if (pthisGyro->iFIFOCount > 0)
    {
        // set ftmp to the interval between the FIFO gyro measurements
        ftmp = pthisSV->fdeltat / (float) pthisGyro->iFIFOCount;

        // normal case, loop over all the buffered gyroscope measurements
        for (j = 0; j < pthisGyro->iFIFOCount; j++)
        {
            // calculate the instantaneous angular velocity subtracting the gyro offset
            for (i = CHX; i <= CHZ; i++)
                ftmpMi3x1[i] = (float) pthisGyro->iYsFIFO[j][i] *
                    pthisGyro->fDegPerSecPerCount -
                    pthisSV->fbPl[i];

            // compute the incremental rotation quaternion ftmpq and integrate the a priori orientation quaternion fqMi
            fQuaternionFromRotationVectorDeg(&ftmpq, ftmpMi3x1, ftmp);
            qAeqAxB(&fqMi, &ftmpq);
        }
    }
    else
    {
        // special case with no new FIFO measurements, use the previous iteration's average gyro reading to compute
        // the incremental rotation quaternion ftmpq and integrate the a priori orientation quaternion fqMi
        fQuaternionFromRotationVectorDeg(&ftmpq, pthisSV->fOmega,
                                         pthisSV->fdeltat);
        qAeqAxB(&fqMi, &ftmpq);
    }

    // set ftmp3DOF3x1 to the 3DOF gravity vector in the sensor frame
    fmodGc = sqrtf(fabs(pthisAccel->fGc[CHX] * pthisAccel->fGc[CHX] +
                   pthisAccel->fGc[CHY] * pthisAccel->fGc[CHY] +
                   pthisAccel->fGc[CHZ] * pthisAccel->fGc[CHZ]));
    if (fmodGc != 0.0F)
    {
        // normal non-freefall case
        ftmp = 1.0F / fmodGc;
        ftmp3DOF3x1[CHX] = pthisAccel->fGc[CHX] * ftmp;
        ftmp3DOF3x1[CHY] = pthisAccel->fGc[CHY] * ftmp;
        ftmp3DOF3x1[CHZ] = pthisAccel->fGc[CHZ] * ftmp;
    }
    else
    {
        // use zero tilt in case of freefall
        ftmp3DOF3x1[CHX] = 0.0F;
        ftmp3DOF3x1[CHY] = 0.0F;
        ftmp3DOF3x1[CHZ] = 1.0F;
    }

    // correct accelerometer gravity vector for different coordinate systems
#if THISCOORDSYSTEM == NED
    // +1g in accelerometer z axis (z down) when PCB is flat so no correction needed
#elif THISCOORDSYSTEM == ANDROID
    // +1g in accelerometer z axis (z up) when PCB is flat so negate the vector to obtain gravity
    ftmp3DOF3x1[CHX] = -ftmp3DOF3x1[CHX];
    ftmp3DOF3x1[CHY] = -ftmp3DOF3x1[CHY];
    ftmp3DOF3x1[CHZ] = -ftmp3DOF3x1[CHZ];
#else // WIN8
    // -1g in accelerometer z axis (z up) when PCB is flat so no correction needed
#endif

    // set ftmpMi3x1 to the a priori gravity vector in the sensor frame from the a priori quaternion
    ftmpMi3x1[CHX] = 2.0F * (fqMi.q1 * fqMi.q3 - fqMi.q0 * fqMi.q2);
    ftmpMi3x1[CHY] = 2.0F * (fqMi.q2 * fqMi.q3 + fqMi.q0 * fqMi.q1);
    ftmpMi3x1[CHZ] = 2.0F * (fqMi.q0 * fqMi.q0 + fqMi.q3 * fqMi.q3) - 1.0F;

    // correct a priori gravity vector for different coordinate systems
#if THISCOORDSYSTEM == NED
    // z axis is down (NED) so no correction needed
#else // ANDROID and WIN8
    // z axis is up (ANDROID and WIN8 ENU) so no negate the vector to obtain gravity
    ftmpMi3x1[CHX] = -ftmpMi3x1[CHX];
    ftmpMi3x1[CHY] = -ftmpMi3x1[CHY];
    ftmpMi3x1[CHZ] = -ftmpMi3x1[CHZ];
#endif

    // calculate the rotation quaternion between 3DOF and a priori gravity vectors (ignored minus signs cancel here)
    // and copy the quaternion vector components to the measurement error vector fZErr
    fveqconjgquq(&ftmpq, ftmp3DOF3x1, ftmpMi3x1);
    pthisSV->fZErr[CHX] = ftmpq.q1;
    pthisSV->fZErr[CHY] = ftmpq.q2;
    pthisSV->fZErr[CHZ] = ftmpq.q3;

    // update Qw using the a posteriori error vectors from the previous iteration.
    // as Qv increases or Qw decreases, K -> 0 and the Kalman filter is weighted towards the a priori prediction
    // as Qv decreases or Qw increases, KC -> I and the Kalman filter is weighted towards the measurement.
    // initialize Qw to all zeroes
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++) pthisSV->fQw6x6[i][j] = 0.0F;

    // partial diagonal gyro offset terms
    pthisSV->fQw6x6[3][3] = pthisSV->fbErrPl[CHX] * pthisSV->fbErrPl[CHX];
    pthisSV->fQw6x6[4][4] = pthisSV->fbErrPl[CHY] * pthisSV->fbErrPl[CHY];
    pthisSV->fQw6x6[5][5] = pthisSV->fbErrPl[CHZ] * pthisSV->fbErrPl[CHZ];

    // diagonal gravity vector components
    pthisSV->fQw6x6[0][0] = pthisSV->fqgErrPl[CHX] *
        pthisSV->fqgErrPl[CHX] +
        pthisSV->fAlphaSqQvYQwbOver12 +
        pthisSV->fAlphaSqOver4 *
        pthisSV->fQw6x6[3][3];
    pthisSV->fQw6x6[1][1] = pthisSV->fqgErrPl[CHY] *
        pthisSV->fqgErrPl[CHY] +
        pthisSV->fAlphaSqQvYQwbOver12 +
        pthisSV->fAlphaSqOver4 *
        pthisSV->fQw6x6[4][4];
    pthisSV->fQw6x6[2][2] = pthisSV->fqgErrPl[CHZ] *
        pthisSV->fqgErrPl[CHZ] +
        pthisSV->fAlphaSqQvYQwbOver12 +
        pthisSV->fAlphaSqOver4 *
        pthisSV->fQw6x6[5][5];

    // remaining diagonal gyro offset components
    pthisSV->fQw6x6[3][3] += pthisSV->fQwbOver3;
    pthisSV->fQw6x6[4][4] += pthisSV->fQwbOver3;
    pthisSV->fQw6x6[5][5] += pthisSV->fQwbOver3;

    // off diagonal gravity and gyro offset components
    pthisSV->fQw6x6[0][3] = pthisSV->fQw6x6[3][0] = pthisSV->fqgErrPl[CHX] *
        pthisSV->fbErrPl[CHX] -
        pthisSV->fAlphaOver2 *
        pthisSV->fQw6x6[3][3];
    pthisSV->fQw6x6[1][4] = pthisSV->fQw6x6[4][1] = pthisSV->fqgErrPl[CHY] *
        pthisSV->fbErrPl[CHY] -
        pthisSV->fAlphaOver2 *
        pthisSV->fQw6x6[4][4];
    pthisSV->fQw6x6[2][5] = pthisSV->fQw6x6[5][2] = pthisSV->fqgErrPl[CHZ] *
        pthisSV->fbErrPl[CHZ] -
        pthisSV->fAlphaOver2 *
        pthisSV->fQw6x6[5][5];

    // calculate the vector fQv containing the diagonal elements of the measurement covariance matrix Qv
    ftmp = fmodGc - 1.0F;
    fQvGQa = 3.0F * ftmp * ftmp;
    if (fQvGQa < FQVG_6DOF_GY_KALMAN) fQvGQa = FQVG_6DOF_GY_KALMAN;
    pthisSV->fQv = ONEOVER12 * fQvGQa + pthisSV->fAlphaSqQvYQwbOver12;

    // calculate the 6x3 Kalman gain matrix K = Qw * C^T * inv(C * Qw * C^T + Qv)
    // set fQwCT6x3 = Qw.C^T where Qw has size 6x6 and C^T has size 6x3
    for (i = 0; i < 6; i++)         // loop over rows
    {
        for (j = 0; j < 3; j++)     // loop over columns
        {
            pthisSV->fQwCT6x3[i][j] = 0.0F;

            // accumulate matrix sum
            for (k = 0; k < 6; k++)
            {
                // determine fC3x6[j][k] since the matrix is highly sparse
                fC3x6jk = 0.0F;
                if (k == j) fC3x6jk = 1.0F;
                if (k == (j + 3)) fC3x6jk = -pthisSV->fAlphaOver2;

                // accumulate fQwCT6x3[i][j] += Qw6x6[i][k] * C[j][k]
                if ((pthisSV->fQw6x6[i][k] != 0.0F) && (fC3x6jk != 0.0F))
                {
                    if (fC3x6jk == 1.0F)
                        pthisSV->fQwCT6x3[i][j] += pthisSV->fQw6x6[i][k];
                    else
                        pthisSV->fQwCT6x3[i][j] += pthisSV->fQw6x6[i][k] * fC3x6jk;
                }
            }
        }
    }

    // set symmetric ftmpA3x3 = C.(Qw.C^T) + Qv = C.fQwCT6x3 + Qv
    for (i = 0; i < 3; i++)         // loop over rows
    {
        for (j = i; j < 3; j++)     // loop over on and above diagonal columns
        {
            // zero off diagonal and set diagonal to Qv
            if (i == j)
                ftmpA3x3[i][j] = pthisSV->fQv;
            else
                ftmpA3x3[i][j] = 0.0F;

            // accumulate matrix sum
            for (k = 0; k < 6; k++)
            {
                // determine fC3x6[i][k]
                fC3x6ik = 0.0F;
                if (k == i) fC3x6ik = 1.0F;
                if (k == (i + 3)) fC3x6ik = -pthisSV->fAlphaOver2;

                // accumulate ftmpA3x3[i][j] += C[i][k] & fQwCT6x3[k][j]
                if ((fC3x6ik != 0.0F) && (pthisSV->fQwCT6x3[k][j] != 0.0F))
                {
                    if (fC3x6ik == 1.0F)
                        ftmpA3x3[i][j] += pthisSV->fQwCT6x3[k][j];
                    else
                        ftmpA3x3[i][j] += fC3x6ik * pthisSV->fQwCT6x3[k][j];
                }
            }
        }
    }

    // set ftmpA3x3 below diagonal elements to above diagonal elements
    ftmpA3x3[1][0] = ftmpA3x3[0][1];
    ftmpA3x3[2][0] = ftmpA3x3[0][2];
    ftmpA3x3[2][1] = ftmpA3x3[1][2];

    // invert ftmpA3x3 in situ to give ftmpA3x3 = inv(C * Qw * C^T + Qv) = inv(ftmpA3x3)
    for (i = 0; i < 3; i++) pfRows[i] = ftmpA3x3[i];
    fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 3, &ierror);

    // on successful inversion set Kalman gain matrix fK6x3 = Qw * C^T * inv(C * Qw * C^T + Qv) = fQwCT6x3 * ftmpA3x3
    if (!ierror)
    {
        // normal case
        for (i = 0; i < 6; i++)     // loop over rows
        {
            for (j = 0; j < 3; j++) // loop over columns
            {
                pthisSV->fK6x3[i][j] = 0.0F;
                for (k = 0; k < 3; k++)
                {
                    if ((pthisSV->fQwCT6x3[i][k] != 0.0F) &&
                        (ftmpA3x3[k][j] != 0.0F))
                    {
                        pthisSV->fK6x3[i][j] += pthisSV->fQwCT6x3[i][k] * ftmpA3x3[k][j];
                    }
                }
            }
        }
    }
    else
    {
        // ftmpA3x3 was singular so set Kalman gain matrix fK6x3 to zero
        for (i = 0; i < 6; i++)     // loop over rows
        {
            for (j = 0; j < 3; j++) // loop over columns
            {
                pthisSV->fK6x3[i][j] = 0.0F;
            }
        }
    }

    // calculate the a posteriori gravity and geomagnetic tilt quaternion errors and gyro offset error vector
    // from the Kalman matrix fK6x3 and from the measurement error vector fZErr.
    for (i = CHX; i <= CHZ; i++)
    {
        // gravity tilt vector error component
        if (pthisSV->fK6x3[i][CHX] != 0.0F)
            pthisSV->fqgErrPl[i] = pthisSV->fK6x3[i][CHX] * pthisSV->fZErr[CHX];
        else
            pthisSV->fqgErrPl[i] = 0.0F;
        if (pthisSV->fK6x3[i][CHY] != 0.0F)
            pthisSV->fqgErrPl[i] += pthisSV->fK6x3[i][CHY] * pthisSV->fZErr[CHY];
        if (pthisSV->fK6x3[i][CHZ] != 0.0F)
            pthisSV->fqgErrPl[i] += pthisSV->fK6x3[i][CHZ] * pthisSV->fZErr[CHZ];

        // gyro offset vector error component
        if (pthisSV->fK6x3[i + 3][CHX] != 0.0F)
            pthisSV->fbErrPl[i] = pthisSV->fK6x3[i + 3][CHX] * pthisSV->fZErr[CHX];
        else
            pthisSV->fbErrPl[i] = 0.0F;
        if (pthisSV->fK6x3[i + 3][CHY] != 0.0F)
            pthisSV->fbErrPl[i] += pthisSV->fK6x3[i + 3][CHY] * pthisSV->fZErr[CHY];
        if (pthisSV->fK6x3[i + 3][CHZ] != 0.0F)
            pthisSV->fbErrPl[i] += pthisSV->fK6x3[i + 3][CHZ] * pthisSV->fZErr[CHZ];
    }

    // set ftmpq to the gravity tilt correction (conjugate) quaternion
    ftmpq.q1 = -pthisSV->fqgErrPl[CHX];
    ftmpq.q2 = -pthisSV->fqgErrPl[CHY];
    ftmpq.q3 = -pthisSV->fqgErrPl[CHZ];
    ftmp = ftmpq.q1 * ftmpq.q1 + ftmpq.q2 * ftmpq.q2 + ftmpq.q3 * ftmpq.q3;

    // determine the scalar component q0 to enforce normalization
    if (ftmp <= 1.0F)
    {
        // normal case
        ftmpq.q0 = sqrtf(fabsf(1.0F - ftmp));
    }
    else
    {
        // if vector component exceeds unity then set to 180 degree rotation and force normalization
        ftmp = 1.0F / sqrtf(ftmp);
        ftmpq.q0 = 0.0F;
        ftmpq.q1 *= ftmp;
        ftmpq.q2 *= ftmp;
        ftmpq.q3 *= ftmp;
    }

    // apply the gravity tilt correction quaternion so fqPl = fqMi.(fqgErrPl)* = fqMi.ftmpq and normalize
    qAeqBxC(&(pthisSV->fqPl), &fqMi, &ftmpq);

    // normalize the a posteriori quaternion and compute the a posteriori rotation matrix and rotation vector
    fqAeqNormqA(&(pthisSV->fqPl));
    fRotationMatrixFromQuaternion(pthisSV->fRPl, &(pthisSV->fqPl));
    fRotationVectorDegFromQuaternion(&(pthisSV->fqPl), pthisSV->fRVecPl);

    // update the a posteriori gyro offset vector: b+[k] = b-[k] - be+[k] = b+[k] - be+[k] (deg/s)
    // limiting the correction to the maximum permitted by the random walk model
    for (i = CHX; i <= CHZ; i++)
    {
        if (pthisSV->fbErrPl[i] > pthisSV->fMaxGyroOffsetChange)
            pthisSV->fbPl[i] -= pthisSV->fMaxGyroOffsetChange;
        else if (pthisSV->fbErrPl[i] < -pthisSV->fMaxGyroOffsetChange)
            pthisSV->fbPl[i] += pthisSV->fMaxGyroOffsetChange;
        else
            pthisSV->fbPl[i] -= pthisSV->fbErrPl[i];
    }

    // compute the linear acceleration fAccGl in the global frame
    // first de-rotate the accelerometer measurement fGc from the sensor to global frame
    // using the transpose (inverse) of the orientation matrix fRPl
    fveqRu(pthisSV->fAccGl, pthisSV->fRPl, pthisAccel->fGc, 1);

    // sutract the fixed gravity vector in the global frame leaving linear acceleration
#if THISCOORDSYSTEM == NED
    // gravity positive NED
    pthisSV->fAccGl[CHX] = -pthisSV->fAccGl[CHX];
    pthisSV->fAccGl[CHY] = -pthisSV->fAccGl[CHY];
    pthisSV->fAccGl[CHZ] = -(pthisSV->fAccGl[CHZ] - 1.0F);
#elif THISCOORDSYSTEM == ANDROID
    // acceleration positive ENU
    pthisSV->fAccGl[CHZ] = pthisSV->fAccGl[CHZ] - 1.0F;
#else // WIN8
    // gravity positive ENU
    pthisSV->fAccGl[CHX] = -pthisSV->fAccGl[CHX];
    pthisSV->fAccGl[CHY] = -pthisSV->fAccGl[CHY];
    pthisSV->fAccGl[CHZ] = -(pthisSV->fAccGl[CHZ] + 1.0F);
#endif

    // compute the a posteriori Euler angles from the a posteriori orientation matrix fRPl
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl),
                                    &(pthisSV->fThePl), &(pthisSV->fPsiPl),
                                    &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl),
                                        &(pthisSV->fThePl), &(pthisSV->fPsiPl),
                                        &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl),
                                     &(pthisSV->fThePl), &(pthisSV->fPsiPl),
                                     &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#endif
    return;
}   // end fRun_6DOF_GY_KALMAN
#if F_9DOF_GBY_KALMAN
// 9DOF accelerometer+magnetometer+gyroscope orientation function implemented using indirect complementary Kalman filter
void fRun_9DOF_GBY_KALMAN(struct SV_9DOF_GBY_KALMAN *pthisSV,
                          struct AccelSensor *pthisAccel,
                          struct MagSensor *pthisMag,
                          struct GyroSensor *pthisGyro,
                          struct MagCalibration *pthisMagCal)
{
    // local scalars and arrays
    float       ftmpA6x6[6][6];     // scratch 6x6 matrix
    float       fRMi[3][3];         // a priori orientation matrix
    float       fR6DOF[3][3];       // eCompass (6DOF accelerometer+magnetometer) orientation matrix
    float       fgMi[3];            // a priori estimate of the gravity vector (sensor frame)
    float       fmMi[3];            // a priori estimate of the geomagnetic vector (sensor frame)
    float       fgPl[3];            // a posteriori estimate of the gravity vector (sensor frame)
    float       fmPl[3];            // a posteriori estimate of the geomagnetic vector (sensor frame)
    float       ftmpA3x3[3][3];     // scratch 3x3 matrix
    float       ftmpA3x1[3];        // scratch 3x1 vector
    float       fQvGQa;             // accelerometer noise covariance to 1g sphere
    float       fQvBQd;             // magnetometer noise covariance to geomagnetic sphere
    float       fC6x9ik;            // element i, k of measurement matrix C
    float       fC6x9jk;            // element j, k of measurement matrix C
    Quaternion  fqMi;               // a priori orientation quaternion
    Quaternion  fq6DOF;             // eCompass (6DOF accelerometer+magnetometer) orientation quaternion
    Quaternion  ftmpq;              // scratch quaternion used for gyro integration
    float       fDelta6DOF;         // geomagnetic inclination angle computed from accelerometer and magnetometer (deg)
    float       fsinDelta6DOF;    // sin(fDelta6DOF)
    float       fcosDelta6DOF;    // cos(fDelta6DOF)
    float       fmodGc;    // modulus of calibrated accelerometer measurement (g)
    float       fmodBc;    // modulus of calibrated magnetometer measurement (uT)
    float       ftmp;               // scratch float
    int8        ierror;             // matrix inversion error flag
    int8        i,
                j,
                k;                  // loop counters

    // working arrays for 6x6 matrix inversion
    float       *pfRows[6];
    int8        iColInd[6];
    int8        iRowInd[6];
    int8        iPivot[6];

    // if requested, do a reset initialization with no further processing
    if (pthisSV->resetflag) {
      fInit_9DOF_GBY_KALMAN(pthisSV, pthisAccel, pthisMag, pthisGyro, pthisMagCal);
      return;
    }

    // compute the average angular velocity (used for display only) from the average measurement minus gyro offset
    for (i = CHX; i <= CHZ; i++) pthisSV->fOmega[i] = (float)pthisGyro->iYs[i] * pthisGyro->fDegPerSecPerCount - pthisSV->fbPl[i];

    // initialize the a priori orientation quaternion fqMi to the previous iteration's a posteriori estimate fqPl
    // and incrementally rotate fqMi by the contents of the gyro FIFO buffer
    fqMi = pthisSV->fqPl;
    if (pthisGyro->iFIFOCount > 0) {
        // set ftmp to the average interval between FIFO gyro measurements
        ftmp = pthisSV->fdeltat / (float)pthisGyro->iFIFOCount;

        // normal case, loop over all the buffered gyroscope measurements
        for (j = 0; j < pthisGyro->iFIFOCount; j++) {
        // calculate the instantaneous angular velocity subtracting the gyro offset
            for (i = CHX; i <= CHZ; i++) ftmpA3x1[i] = (float)pthisGyro->iYsFIFO[j][i] * pthisGyro->fDegPerSecPerCount - pthisSV->fbPl[i];
            // compute the incremental rotation quaternion ftmpq and integrate the a priori orientation quaternion fqMi
            fQuaternionFromRotationVectorDeg(&ftmpq, ftmpA3x1, ftmp);
            qAeqAxB(&fqMi, &ftmpq);
        }
    } else {
        // special case with no new FIFO measurements, use the previous iteration's average gyro reading to compute
        // the incremental rotation quaternion ftmpq and integrate the a priori orientation quaternion fqMi
        fQuaternionFromRotationVectorDeg(&ftmpq, pthisSV->fOmega, pthisSV->fdeltat);
        qAeqAxB(&fqMi, &ftmpq);
    }

    // compute the a priori orientation matrix fRMi from the new a priori orientation quaternion fqMi
    fRotationMatrixFromQuaternion(fRMi, &fqMi);

    // compute the 6DOF orientation matrix fR6DOF, inclination angle fDelta6DOF and the squared
    // deviations of the accelerometer and magnetometer measurements from the 1g gravity and geomagnetic spheres.
#if THISCOORDSYSTEM == NED
    feCompassNED(fR6DOF, &fDelta6DOF, &fsinDelta6DOF, &fcosDelta6DOF, pthisMag->fBc, pthisAccel->fGc, &fmodBc, &fmodGc);
#elif THISCOORDSYSTEM == ANDROID
    feCompassAndroid(fR6DOF, &fDelta6DOF, &fsinDelta6DOF, &fcosDelta6DOF, pthisMag->fBc, pthisAccel->fGc, &fmodBc, &fmodGc);
#else // WIN8
    feCompassWin8(fR6DOF, &fDelta6DOF, &fsinDelta6DOF, &fcosDelta6DOF, pthisMag->fBc, pthisAccel->fGc, &fmodBc, &fmodGc);
#endif

    // compute the 6DOF orientation quaternion fq6DOF from the 6DOF orientation matrix fR6OF
    fQuaternionFromRotationMatrix(fR6DOF, &fq6DOF);

    // calculate the acceleration noise variance relative to 1g sphere
    ftmp = fmodGc - 1.0F;
    fQvGQa = 3.0F * ftmp * ftmp;
    if (fQvGQa < FQVG_9DOF_GBY_KALMAN)
    fQvGQa = FQVG_9DOF_GBY_KALMAN;

    // calculate magnetic noise variance relative to geomagnetic sphere
    ftmp = fmodBc - pthisMagCal->fB;
    fQvBQd = 3.0F * ftmp * ftmp;
    if (fQvBQd < FQVB_9DOF_GBY_KALMAN)
    fQvBQd = FQVB_9DOF_GBY_KALMAN;

    // do a once-only orientation lock immediately after the first valid magnetic calibration by:
    // i) setting the a priori and a posteriori orientations to the 6DOF eCompass orientation
    // ii) setting the geomagnetic inclination angle fDeltaPl now that the first calibrated 6DOF estimate is available
    if (pthisMagCal->iValidMagCal && !pthisSV->iFirstAccelMagLock) {
        fqMi = pthisSV->fqPl = fq6DOF;
        f3x3matrixAeqB(fRMi, fR6DOF);
        pthisSV->fDeltaPl = fDelta6DOF;
        pthisSV->fsinDeltaPl = fsinDelta6DOF;
        pthisSV->fcosDeltaPl = fcosDelta6DOF;
        pthisSV->iFirstAccelMagLock = true;
    }

    // set ftmpA3x1 to the normalized 6DOF gravity vector and set fgMi to the normalized a priori gravity vector
    // with both estimates computed in the sensor frame
#if THISCOORDSYSTEM == NED
    ftmpA3x1[CHX] = fR6DOF[CHX][CHZ];
    ftmpA3x1[CHY] = fR6DOF[CHY][CHZ];
    ftmpA3x1[CHZ] = fR6DOF[CHZ][CHZ];
    fgMi[CHX] = fRMi[CHX][CHZ];
    fgMi[CHY] = fRMi[CHY][CHZ];
    fgMi[CHZ] = fRMi[CHZ][CHZ];
#else // ANDROID and WIN8 (ENU gravity positive)
    ftmpA3x1[CHX] = -fR6DOF[CHX][CHZ];
    ftmpA3x1[CHY] = -fR6DOF[CHY][CHZ];
    ftmpA3x1[CHZ] = -fR6DOF[CHZ][CHZ];
    fgMi[CHX] = -fRMi[CHX][CHZ];
    fgMi[CHY] = -fRMi[CHY][CHZ];
    fgMi[CHZ] = -fRMi[CHZ][CHZ];
#endif

    // set ftmpq to the quaternion that rotates the 6DOF gravity tilt vector ftmpA3x1 to the a priori estimate fgMi
    // and copy its vector components into the measurement error vector fZErr[0-2].
    fveqconjgquq(&ftmpq, ftmpA3x1, fgMi);
    pthisSV->fZErr[0] = ftmpq.q1;
    pthisSV->fZErr[1] = ftmpq.q2;
    pthisSV->fZErr[2] = ftmpq.q3;

    // set ftmpA3x1 to the normalized 6DOF geomagnetic vector and set fmMi to the normalized a priori geomagnetic vector
    // with both estimates computed in the sensor frame
#if THISCOORDSYSTEM == NED
    ftmpA3x1[CHX] = fR6DOF[CHX][CHX] * fcosDelta6DOF + fR6DOF[CHX][CHZ] * fsinDelta6DOF;
    ftmpA3x1[CHY] = fR6DOF[CHY][CHX] * fcosDelta6DOF + fR6DOF[CHY][CHZ] * fsinDelta6DOF;
    ftmpA3x1[CHZ] = fR6DOF[CHZ][CHX] * fcosDelta6DOF + fR6DOF[CHZ][CHZ] * fsinDelta6DOF;
    fmMi[CHX] = fRMi[CHX][CHX] * pthisSV->fcosDeltaPl + fRMi[CHX][CHZ] * pthisSV->fsinDeltaPl;
    fmMi[CHY] = fRMi[CHY][CHX] * pthisSV->fcosDeltaPl + fRMi[CHY][CHZ] * pthisSV->fsinDeltaPl;
    fmMi[CHZ] = fRMi[CHZ][CHX] * pthisSV->fcosDeltaPl + fRMi[CHZ][CHZ] * pthisSV->fsinDeltaPl;
#else // ANDROID and WIN8 (both ENU coordinate systems)
    ftmpA3x1[CHX] = fR6DOF[CHX][CHY] * fcosDelta6DOF - fR6DOF[CHX][CHZ] * fsinDelta6DOF;
    ftmpA3x1[CHY] = fR6DOF[CHY][CHY] * fcosDelta6DOF - fR6DOF[CHY][CHZ] * fsinDelta6DOF;
    ftmpA3x1[CHZ] = fR6DOF[CHZ][CHY] * fcosDelta6DOF - fR6DOF[CHZ][CHZ] * fsinDelta6DOF;
    fmMi[CHX] = fRMi[CHX][CHY] * pthisSV->fcosDeltaPl - fRMi[CHX][CHZ] * pthisSV->fsinDeltaPl;
    fmMi[CHY] = fRMi[CHY][CHY] * pthisSV->fcosDeltaPl - fRMi[CHY][CHZ] * pthisSV->fsinDeltaPl;
    fmMi[CHZ] = fRMi[CHZ][CHY] * pthisSV->fcosDeltaPl - fRMi[CHZ][CHZ] * pthisSV->fsinDeltaPl;
#endif

    // set ftmpq to the quaternion that rotates the 6DOF geomagnetic tilt vector ftmpA3x1 to the a priori estimate fmMi
    // and copy its vector components into the measurement error vector fZErr[3-5].
    fveqconjgquq(&ftmpq, ftmpA3x1, fmMi);
    pthisSV->fZErr[3] = ftmpq.q1;
    pthisSV->fZErr[4] = ftmpq.q2;
    pthisSV->fZErr[5] = ftmpq.q3;

    // update Qw using the a posteriori error vectors from the previous iteration.
    // as Qv increases or Qw decreases, K -> 0 and the Kalman filter is weighted towards the a priori prediction
    // as Qv decreases or Qw increases, KC -> I and the Kalman filter is weighted towards the measurement.
    // initialize on and above diagonal elements of Qw to zero
    for (i = 0; i < 9; i++)
        for (j = i; j < 9; j++)
            pthisSV->fQw9x9[i][j] = 0.0F;
    // partial diagonal gyro offset terms
    pthisSV->fQw9x9[6][6] = pthisSV->fbErrPl[CHX] * pthisSV->fbErrPl[CHX];
    pthisSV->fQw9x9[7][7] = pthisSV->fbErrPl[CHY] * pthisSV->fbErrPl[CHY];
    pthisSV->fQw9x9[8][8] = pthisSV->fbErrPl[CHZ] * pthisSV->fbErrPl[CHZ];
    // set ftmpA3x1 to alpha^2 / 4 * fbErrPl.fbErrPl + fAlphaSqQvYQwbOver12
    ftmpA3x1[0] = pthisSV->fAlphaSqOver4 * pthisSV->fQw9x9[6][6] + pthisSV->fAlphaSqQvYQwbOver12;
    ftmpA3x1[1] = pthisSV->fAlphaSqOver4 * pthisSV->fQw9x9[7][7] + pthisSV->fAlphaSqQvYQwbOver12;
    ftmpA3x1[2] = pthisSV->fAlphaSqOver4 * pthisSV->fQw9x9[8][8] + pthisSV->fAlphaSqQvYQwbOver12;
    // diagonal gravity vector components
    pthisSV->fQw9x9[0][0] = pthisSV->fqgErrPl[CHX] * pthisSV->fqgErrPl[CHX] + ftmpA3x1[0];
    pthisSV->fQw9x9[1][1] = pthisSV->fqgErrPl[CHY] * pthisSV->fqgErrPl[CHY] + ftmpA3x1[1];
    pthisSV->fQw9x9[2][2] = pthisSV->fqgErrPl[CHZ] * pthisSV->fqgErrPl[CHZ] + ftmpA3x1[2];
    // diagonal geomagnetic vector components
    pthisSV->fQw9x9[3][3] = pthisSV->fqmErrPl[CHX] * pthisSV->fqmErrPl[CHX] + ftmpA3x1[0];
    pthisSV->fQw9x9[4][4] = pthisSV->fqmErrPl[CHY] * pthisSV->fqmErrPl[CHY] + ftmpA3x1[1];
    pthisSV->fQw9x9[5][5] = pthisSV->fqmErrPl[CHZ] * pthisSV->fqmErrPl[CHZ] + ftmpA3x1[2];
    // diagonal gyro offset components
    pthisSV->fQw9x9[6][6] += pthisSV->fQwbOver3;
    pthisSV->fQw9x9[7][7] += pthisSV->fQwbOver3;;
    pthisSV->fQw9x9[8][8] += pthisSV->fQwbOver3;;
    // set ftmpA3x1 to alpha / 2 * fQw9x9[6-8][6-8]
    ftmpA3x1[0] = pthisSV->fAlphaOver2 * pthisSV->fQw9x9[6][6];
    ftmpA3x1[1] = pthisSV->fAlphaOver2 * pthisSV->fQw9x9[7][7];
    ftmpA3x1[2] = pthisSV->fAlphaOver2 * pthisSV->fQw9x9[8][8];
    // off diagonal gravity and gyro offset components
    pthisSV->fQw9x9[0][6] = pthisSV->fqgErrPl[CHX] * pthisSV->fbErrPl[CHX] - ftmpA3x1[0];
    pthisSV->fQw9x9[1][7] = pthisSV->fqgErrPl[CHY] * pthisSV->fbErrPl[CHY] - ftmpA3x1[1];
    pthisSV->fQw9x9[2][8] = pthisSV->fqgErrPl[CHZ] * pthisSV->fbErrPl[CHZ] - ftmpA3x1[2];
    // off diagonal geomagnetic and gyro offset components
    pthisSV->fQw9x9[3][6] = pthisSV->fqmErrPl[CHX] * pthisSV->fbErrPl[CHX] - ftmpA3x1[0];
    pthisSV->fQw9x9[4][7] = pthisSV->fqmErrPl[CHY] * pthisSV->fbErrPl[CHY] - ftmpA3x1[1];
    pthisSV->fQw9x9[5][8] = pthisSV->fqmErrPl[CHZ] * pthisSV->fbErrPl[CHZ] - ftmpA3x1[2];
    // set below diagonal elements of Qw to above diagonal elements
    for (i = 1; i < 9; i++)
        for (j = 0; j < i; j++)
            pthisSV->fQw9x9[i][j] = pthisSV->fQw9x9[j][i];

    // calculate the vector fQv6x1 containing the diagonal elements of the measurement covariance matrix Qv
    pthisSV->fQv6x1[0] = pthisSV->fQv6x1[1] = pthisSV->fQv6x1[2] = ONEOVER12 * fQvGQa + pthisSV->fAlphaSqQvYQwbOver12;
    pthisSV->fQv6x1[3] = pthisSV->fQv6x1[4] = pthisSV->fQv6x1[5] = ONEOVER12 * fQvBQd / pthisMagCal->fBSq + pthisSV->fAlphaSqQvYQwbOver12;

    // calculate the Kalman gain matrix K = Qw * C^T * inv(C * Qw * C^T + Qv)
    // set fQwCT9x6 = Qw.C^T where Qw has size 9x9 and C^T has size 9x6
    for (i = 0; i < 9; i++) { // loop over rows
        for (j = 0; j < 6; j++) { // loop over columns
            pthisSV->fQwCT9x6[i][j] = 0.0F;
            // accumulate matrix sum
            for (k = 0; k < 9; k++) {
                // determine fC6x9[j][k] since the matrix is highly sparse
                fC6x9jk = 0.0F;
                // handle rows 0 to 2
                if (j < 3) {
                    if (k == j) fC6x9jk = 1.0F;
                    if (k == (j + 6)) fC6x9jk = -pthisSV->fAlphaOver2;
                } else if (j < 6) {
                    // handle rows 3 to 5
                    if (k == j) fC6x9jk = 1.0F;
                    if (k == (j + 3)) fC6x9jk = -pthisSV->fAlphaOver2;
                }

                // accumulate fQwCT9x6[i][j] += Qw9x9[i][k] * C[j][k]
                if ((pthisSV->fQw9x9[i][k] != 0.0F) && (fC6x9jk != 0.0F)) {
                    if (fC6x9jk == 1.0F) pthisSV->fQwCT9x6[i][j] += pthisSV->fQw9x9[i][k];
                    else pthisSV->fQwCT9x6[i][j] += pthisSV->fQw9x9[i][k] * fC6x9jk;
                }
            }
        }
    }

    // set symmetric ftmpA6x6 = C.(Qw.C^T) + Qv = C.fQwCT9x6 + Qv
    for (i = 0; i < 6; i++) { // loop over rows
      for (j = i; j < 6; j++) { // loop over on and above diagonal columns
          // zero off diagonal and set diagonal to Qv
          if (i == j) ftmpA6x6[i][j] = pthisSV->fQv6x1[i];
          else ftmpA6x6[i][j] = 0.0F;
          // accumulate matrix sum
          for (k = 0; k < 9; k++) {
              // determine fC6x9[i][k]
              fC6x9ik = 0.0F;
              // handle rows 0 to 2
              if (i < 3) {
                  if (k == i) fC6x9ik = 1.0F;
                  if (k == (i + 6)) fC6x9ik = -pthisSV->fAlphaOver2;
              } else if (i < 6) {
                  // handle rows 3 to 5
                  if (k == i) fC6x9ik = 1.0F;
                  if (k == (i + 3)) fC6x9ik = -pthisSV->fAlphaOver2;
              }

              // accumulate ftmpA6x6[i][j] += C[i][k] & fQwCT9x6[k][j]
              if ((fC6x9ik != 0.0F) && (pthisSV->fQwCT9x6[k][j] != 0.0F)) {
                  if (fC6x9ik == 1.0F) ftmpA6x6[i][j] += pthisSV->fQwCT9x6[k][j];
                  else ftmpA6x6[i][j] += fC6x9ik * pthisSV->fQwCT9x6[k][j];
              }
          }
      }
    }
    // set ftmpA6x6 below diagonal elements to above diagonal elements
    for (i = 1; i < 6; i++) // loop over rows
        for (j = 0; j < i; j++) // loop over below diagonal columns
            ftmpA6x6[i][j] = ftmpA6x6[j][i];

    // invert ftmpA6x6 in situ to give ftmpA6x6 = inv(C * Qw * C^T + Qv) = inv(ftmpA6x6)
    for (i = 0; i < 6; i++)
        pfRows[i] = ftmpA6x6[i];
    fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 6, &ierror);

    // on successful inversion set Kalman gain matrix K9x6 = Qw * C^T * inv(C * Qw * C^T + Qv) = fQwCT9x6 * ftmpA6x6
    if (!ierror) {
    // normal case
    for (i = 0; i < 9; i++) // loop over rows
        for (j = 0; j < 6; j++) { // loop over columns
            pthisSV->fK9x6[i][j] = 0.0F;
            for (k = 0; k < 6; k++) {
                if ((pthisSV->fQwCT9x6[i][k] != 0.0F) && (ftmpA6x6[k][j] != 0.0F))
                    pthisSV->fK9x6[i][j] += pthisSV->fQwCT9x6[i][k] * ftmpA6x6[k][j];
            }
        }
    } else {
        // ftmpA6x6 was singular so set Kalman gain matrix to zero
        for (i = 0; i < 9; i++) // loop over rows
            for (j = 0; j < 6; j++) // loop over columns
                pthisSV->fK9x6[i][j] = 0.0F;
    }

    // calculate the a posteriori gravity and geomagnetic tilt quaternion errors and gyro offset error vector
    // from the Kalman matrix fK9x6 and the measurement error vector fZErr.
    for (i = CHX; i <= CHZ; i++) {
        pthisSV->fqgErrPl[i] = pthisSV->fqmErrPl[i] = pthisSV->fbErrPl[i] = 0.0F;
        for (j = 0; j < 6; j++) {
            // calculate gravity tilt quaternion vector error component fqgErrPl
            if (pthisSV->fK9x6[i][j] != 0.0F)
                pthisSV->fqgErrPl[i] += pthisSV->fK9x6[i][j] * pthisSV->fZErr[j];

            // calculate geomagnetic tilt quaternion vector error component fqmErrPl
            if (pthisSV->fK9x6[i + 3][j] != 0.0F)
                pthisSV->fqmErrPl[i] += pthisSV->fK9x6[i + 3][j] * pthisSV->fZErr[j];

            // calculate gyro offset vector error component fbErrPl
            if (pthisSV->fK9x6[i + 6][j] != 0.0F)
                pthisSV->fbErrPl[i] += pthisSV->fK9x6[i + 6][j] * pthisSV->fZErr[j];
        }
    }

    // set ftmpq to the a posteriori gravity tilt correction (conjugate) quaternion
    ftmpq.q1 = -pthisSV->fqgErrPl[CHX];
    ftmpq.q2 = -pthisSV->fqgErrPl[CHY];
    ftmpq.q3 = -pthisSV->fqgErrPl[CHZ];
    ftmpq.q0 = sqrtf(fabs(1.0F - ftmpq.q1 * ftmpq.q1 - ftmpq.q2 * ftmpq.q2 - ftmpq.q3 * ftmpq.q3));

    // set ftmpA3x3 to the gravity tilt correction matrix and rotate the normalized a priori estimate of the
    // gravity vector fgMi to obtain the normalized a posteriori estimate of the gravity vector fgPl
    fRotationMatrixFromQuaternion(ftmpA3x3, &ftmpq);
    fveqRu(fgPl, ftmpA3x3, fgMi, 0);

    // set ftmpq to the a posteriori geomagnetic tilt correction (conjugate) quaternion
    ftmpq.q1 = -pthisSV->fqmErrPl[CHX];
    ftmpq.q2 = -pthisSV->fqmErrPl[CHY];
    ftmpq.q3 = -pthisSV->fqmErrPl[CHZ];
    ftmpq.q0 = sqrtf(fabs(1.0F - ftmpq.q1 * ftmpq.q1 - ftmpq.q2 * ftmpq.q2 - ftmpq.q3 * ftmpq.q3));

    // set ftmpA3x3 to the geomagnetic tilt correction matrix and rotate the normalized a priori estimate of the
    // geomagnetic vector fmMi to obtain the normalized a posteriori estimate of the geomagnetic vector fmPl
    fRotationMatrixFromQuaternion(ftmpA3x3, &ftmpq);
    fveqRu(fmPl, ftmpA3x3, fmMi, 0);

    // compute the a posteriori orientation matrix fRPl from the vector product of the a posteriori gravity fgPl
    // and geomagnetic fmPl vectors both of which are normalized
#if THISCOORDSYSTEM == NED// gravity vector is +z and accel measurement is +z when flat so don't negate
    feCompassNED(pthisSV->fRPl, &(pthisSV->fDeltaPl), &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
      fmPl, fgPl, &fmodBc, &fmodGc);
#elif THISCOORDSYSTEM == ANDROID // gravity vector is -z and accel measurement is +z when flat so negate
    ftmpA3x1[CHX] = -fgPl[CHX];
    ftmpA3x1[CHY] = -fgPl[CHY];
    ftmpA3x1[CHZ] = -fgPl[CHZ];
    feCompassAndroid(pthisSV->fRPl, &(pthisSV->fDeltaPl), &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
    fmPl, ftmpA3x1, &fmodBc, &fmodGc);
#else // WIN8// gravity vector is -z and accel measurement is -1g when flat so don't negate
    feCompassWin8(pthisSV->fRPl, &(pthisSV->fDeltaPl), &(pthisSV->fsinDeltaPl), &(pthisSV->fcosDeltaPl),
    fmPl, fgPl, &fmodBc, &fmodGc);
#endif

    // compute the a posteriori quaternion fqPl and rotation vector fRVecPl from fRPl
    fQuaternionFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fqPl));
    fRotationVectorDegFromQuaternion(&(pthisSV->fqPl), pthisSV->fRVecPl);

    // update the a posteriori gyro offset vector: b+[k] = b-[k] - be+[k] = b+[k] - be+[k] (deg/s)
    for (i = CHX; i <= CHZ; i++) {
        // restrict the gyro offset correction to the maximum permitted by the random walk model
        if (pthisSV->fbErrPl[i] > pthisSV->fMaxGyroOffsetChange)
            pthisSV->fbPl[i] -= pthisSV->fMaxGyroOffsetChange;
        else if (pthisSV->fbErrPl[i] < -pthisSV->fMaxGyroOffsetChange)
            pthisSV->fbPl[i] += pthisSV->fMaxGyroOffsetChange;
        else
            pthisSV->fbPl[i] -= pthisSV->fbErrPl[i];
        // restrict gyro offset between specified limits
        if (pthisSV->fbPl[i] > FMAX_9DOF_GBY_BPL) pthisSV->fbPl[i] = FMAX_9DOF_GBY_BPL;
        if (pthisSV->fbPl[i] < FMIN_9DOF_GBY_BPL) pthisSV->fbPl[i] = FMIN_9DOF_GBY_BPL;
    }

    // compute the linear acceleration fAccGl in the global frame
    // first de-rotate the accelerometer measurement fGc from the sensor to global frame
    // using the transpose (inverse) of the orientation matrix fRPl
    fveqRu(pthisSV->fAccGl, pthisSV->fRPl, pthisAccel->fGc, 1);

    // subtract the fixed gravity vector in the global frame leaving linear acceleration
#if THISCOORDSYSTEM == NED
    // gravity positive NED
    pthisSV->fAccGl[CHX] = -pthisSV->fAccGl[CHX];
    pthisSV->fAccGl[CHY] = -pthisSV->fAccGl[CHY];
    pthisSV->fAccGl[CHZ] = -(pthisSV->fAccGl[CHZ] - 1.0F);
#elif THISCOORDSYSTEM == ANDROID
    // acceleration positive ENU
    pthisSV->fAccGl[CHZ] = pthisSV->fAccGl[CHZ] - 1.0F;
#else // WIN8
    // gravity positive ENU
    pthisSV->fAccGl[CHX] = -pthisSV->fAccGl[CHX];
    pthisSV->fAccGl[CHY] = -pthisSV->fAccGl[CHY];
    pthisSV->fAccGl[CHZ] = -(pthisSV->fAccGl[CHZ] + 1.0F);
#endif

    // integrate the acceleration to velocity and displacement in the global frame.
    // Note: integration errors accumulate without limit over time and this code should only be
    // used for inertial integration of the order of seconds.
    for (i = CHX; i <= CHZ; i++) {
        // integrate acceleration (in g) to velocity in m/s
        pthisSV->fVelGl[i] += pthisSV->fAccGl[i] * pthisSV->fgdeltat;
        // integrate velocity (in m/s) to displacement (m)
        pthisSV->fDisGl[i] += pthisSV->fVelGl[i] * pthisSV->fdeltat;
    }

    // compute the a posteriori Euler angles from the a posteriori orientation matrix fRPl
#if THISCOORDSYSTEM == NED
    fNEDAnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl), &(pthisSV->fThePl), &(pthisSV->fPsiPl), &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#elif THISCOORDSYSTEM == ANDROID
    fAndroidAnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl), &(pthisSV->fThePl), &(pthisSV->fPsiPl), &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#else // WIN8
    fWin8AnglesDegFromRotationMatrix(pthisSV->fRPl, &(pthisSV->fPhiPl), &(pthisSV->fThePl), &(pthisSV->fPsiPl), &(pthisSV->fRhoPl), &(pthisSV->fChiPl));
#endif

    return;
} // end fRun_9DOF_GBY_KALMAN
#endif // #if F_9DOF_GBY_KALMAN
