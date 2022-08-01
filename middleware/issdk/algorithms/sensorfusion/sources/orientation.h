/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file orientation.h
    \brief Functions to convert between various orientation representations

    Functions to convert between various orientation representations.  Also
    includes functions for manipulating quaternions.
*/
 
#ifndef ORIENTATION_H
#define ORIENTATION_H

/// quaternion structure definition
typedef struct Quaternion       
{
	float q0;	        ///< scalar component
	float q1;	        ///< x vector component
	float q2;	        ///< y vector component
	float q3;	        ///< z vector component
} Quaternion;
              
// function prototypes
/// Aerospace NED accelerometer 3DOF tilt function, computing rotation matrix fR
void f3DOFTiltNED(
    float fR[][3],              ///< computed rotation matrix (output)
    float fGc[]                 ///< calibrated accelerometer input vector
);
/// Android accelerometer 3DOF tilt function computing, rotation matrix fR
void f3DOFTiltAndroid(
    float fR[][3],              ///< computed rotation matrix (output)
    float fGc[]                 ///< calibrated accelerometer input vector
);
/// Windows 8 accelerometer 3DOF tilt function computing, rotation matrix fR
void f3DOFTiltWin8(
    float fR[][3],              ///< computed rotation matrix (output)
    float fGc[]                 ///< calibrated accelerometer input vector
);
/// Aerospace NED magnetometer 3DOF flat eCompass function, computing rotation matrix fR
void f3DOFMagnetometerMatrixNED(
    float fR[][3],              ///< computed rotation matrix (output)
    float fBc[]                 ///< calibrated magnetometer reading (input)
);
/// Android magnetometer 3DOF flat eCompass function, computing rotation matrix fR
void f3DOFMagnetometerMatrixAndroid(
    float fR[][3],              ///< computed rotation matrix (output)
    float fBc[]                 ///< calibrated magnetometer reading (input)
);
/// Windows 8 magnetometer 3DOF flat eCompass function, computing rotation matrix fR
void f3DOFMagnetometerMatrixWin8(
    float fR[][3],              ///< computed rotation matrix (output)
    float fBc[]                 ///< calibrated magnetometer reading (input)
);
/// NED: basic 6DOF e-Compass function, computing rotation matrix fR and magnetic inclination angle fDelta
void feCompassNED(
    float fR[][3],              ///< computed rotation matrix (output)
    float *pfDelta,             ///< magnetic inclination angle (output)
    float *pfsinDelta,          ///< sin of the inclination angle
    float *pfcosDelta,          ///< cos of the inclination angle
    float fBc[],                ///< calibrated magnetometer vector (input)
    float fGc[],                ///< calibrated accelerometer input vector (input)
    float *pfmodBc,             ///< modulus of the calibrated magnetic vector
    float *pfmodGc              ///< modulus of the calibrated accelerometer vector
);
/// Android: basic 6DOF e-Compass function, computing rotation matrix fR and magnetic inclination angle fDelta
void feCompassAndroid(
    float fR[][3],              ///< computed rotation matrix (output)
    float *pfDelta,             ///< magnetic inclination angle (output)
    float *pfsinDelta,          ///< sin of the inclination angle
    float *pfcosDelta,          ///< cos of the inclination angle
    float fBc[],                ///< calibrated magnetometer reading (input)
    float fGc[],                ///< calibrated accelerometer input vector (input) 
    float *pfmodBc,             ///< modulus of the calibrated magnetic vector
    float *pfmodGc              ///< modulus of the calibrated accelerometer vector
);
/// Win8: basic 6DOF e-Compass function, computing rotation matrix fR and magnetic inclination angle fDelta
void feCompassWin8(
    float fR[][3],              ///< computed rotation matrix (output)
    float *pfDelta,             ///< magnetic inclination angle (output)
    float *pfsinDelta,          ///< sin of the inclination angle
    float *pfcosDelta,          ///< cos of the inclination angle
    float fBc[],                ///< calibrated magnetometer reading (input)
    float fGc[],                ///< calibrated accelerometer input vector (input) 
    float *pfmodBc,             ///< modulus of the calibrated magnetic vector
    float *pfmodGc              ///< modulus of the calibrated accelerometer vector
);
/// extract the NED angles in degrees from the NED rotation matrix
void fNEDAnglesDegFromRotationMatrix(
    float R[][3],               ///< rotation matrix input
    float *pfPhiDeg,            ///< output: the roll angle range -180.0 <= Phi < 180.0 deg
    float *pfTheDeg,            ///< output: the pitch angle -90.0 <= Theta <= 90.0 deg
    float *pfPsiDeg,            ///< output: the yaw (compass) angle 0.0 <= Psi < 360.0 deg
    float *pfRhoDeg,            ///< output: For NED, the compass heading Rho equals the yaw angle Psi
    float *pfChiDeg             ///< output: the tilt angle from vertical Chi (0 <= Chi <= 180 deg)
);
/// extract the Android angles in degrees from the Android rotation matrix
void fAndroidAnglesDegFromRotationMatrix(
    float R[][3],               ///< rotation matrix input
    float *pfPhiDeg,            ///< the roll angle -90.0 <= Phi <= 90.0 deg
    float *pfTheDeg,            ///< the pitch angle -180.0 <= The < 180.0 deg
    float *pfPsiDeg,            ///< yaw angle Psi with range 0.0 <= Psi < 360.0 deg
    float *pfRhoDeg,            ///< the compass heading angle Rho equals the yaw angle Psi
    float *pfChiDeg             ///< the tilt angle from vertical Chi (0 <= Chi <= 180 deg)
);
/// extract the Windows 8 angles in degrees from the Windows 8 rotation matrix
void fWin8AnglesDegFromRotationMatrix(
    float R[][3],               ///< rotation matrix input
    float *pfPhiDeg,            ///< the roll angle -90.0 <= Phi <= 90.0 deg
    float *pfTheDeg,            ///< pitch angle Theta in the range -180.0 <= The < 180.0 deg
    float *pfPsiDeg,            ///< yaw angle Psi in range 0.0 <= Psi < 360.0 deg
    float *pfRhoDeg,            ///< the compass angle Rho = 360 - Psi
    float *pfChiDeg             ///< tilt angle from vertical Chi (0 <= Chi <= 180 deg)
);
/// compute the orientation quaternion from a 3x3 rotation matrix
void fQuaternionFromRotationMatrix(
    float R[][3],               ///< Rotation matrix (input)
    Quaternion *pq              ///< Quaternion (output)
);
/// compute the rotation matrix from an orientation quaternion
void fRotationMatrixFromQuaternion(
    float R[][3],               ///< Rotation matrix (output)
    const Quaternion *pq        ///< Quaternion (input)
);
/// function compute the quaternion product qB * qC
void qAeqBxC(
    Quaternion *pqA, 
    const Quaternion *pqB, 
    const Quaternion *pqC
);
/// function compute the quaternion product qA = qA * qB
void qAeqAxB(
    Quaternion *pqA, 
    const Quaternion *pqB
);
/// function compute the quaternion product conjg(qA) * qB
Quaternion qconjgAxB(
    const Quaternion *pqA,
    const Quaternion *pqB
);
/// function normalizes a rotation quaternion and ensures q0 is non-negative
void fqAeqNormqA(
    Quaternion *pqA
);
/// set a quaternion to the unit quaternion
void fqAeq1(
    Quaternion *pqA
);
/// computes normalized rotation quaternion from a rotation vector (deg)
void fQuaternionFromRotationVectorDeg(
    Quaternion *pq,             ///< quaternion (output)
    const float rvecdeg[],      ///< rotation vector in degrees
    float fscaling              ///< delta Time
);
/// computes rotation vector (deg) from rotation quaternion
void fRotationVectorDegFromQuaternion(
    Quaternion *pq,             ///< quaternion (input)
    float rvecdeg[]             ///< rotation vector in degrees (output)
);
/// function low pass filters an orientation quaternion and computes virtual gyro rotation rate
void fLPFOrientationQuaternion(
    Quaternion *pq, 
    Quaternion *pLPq, 
    float flpf, 
    float fdeltat, 
    float fOmega[]
);
/// function computes the rotation quaternion that rotates unit vector u onto unit vector v as v=q*.u.q
/// using q = 1/sqrt(2) * {sqrt(1 + u.v) - u x v / sqrt(1 + u.v)}
void fveqconjgquq(
  Quaternion *pfq, 
  float fu[], 
  float fv[]
);

#endif   // #ifndef ORIENTATION_H
