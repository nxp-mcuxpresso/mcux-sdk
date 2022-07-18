/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// This file contains functions designed to operate on, or compute, orientations.
// These may be in rotation matrix form, quaternion form, or Euler angles.
// It also includes functions designed to operate with specify reference frames
// (Android, Windows 8, NED).
//

/*! \file orientation.c
    \brief Functions to convert between various orientation representations

    Functions to convert between various orientation representations.  Also
    includes functions for manipulating quaternions.
*/

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "sensor_fusion.h"
#include "orientation.h"
#include "fusion.h"
#include "matrix.h"
#include "approximations.h"

// compile time constants that are private to this file
#define SMALLQ0 1E-4F		// limit of quaternion scalar component requiring special algorithm
#define CORRUPTQUAT 0.001F	// threshold for deciding rotation quaternion is corrupt
#define SMALLMODULUS 0.01F	// limit where rounding errors may appear

#if F_USING_ACCEL  // Need tilt conversion routines
// Aerospace NED accelerometer 3DOF tilt function computing rotation matrix fR
#if (THISCOORDSYSTEM == NED) || (THISCOORDSYSTEM == ANDROID)
void f3DOFTiltNED(float fR[][3], float fGc[])
{
	// the NED self-consistency twist occurs at 90 deg pitch

	// local variables
	int16 i;				// counter
	float fmodGxyz;			// modulus of the x, y, z accelerometer readings
	float fmodGyz;			// modulus of the y, z accelerometer readings
	float frecipmodGxyz;	// reciprocal of modulus
	float ftmp;				// scratch variable

	// compute the accelerometer squared magnitudes
	fmodGyz = fGc[CHY] * fGc[CHY] + fGc[CHZ] * fGc[CHZ];
	fmodGxyz = fmodGyz + fGc[CHX] * fGc[CHX];

	// check for freefall special case where no solution is possible
	if (fmodGxyz == 0.0F)
	{
		f3x3matrixAeqI(fR);
		return;
	}

	// check for vertical up or down gimbal lock case
	if (fmodGyz == 0.0F)
	{
		f3x3matrixAeqScalar(fR, 0.0F);
		fR[CHY][CHY] = 1.0F;
		if (fGc[CHX] >= 0.0F)
		{
			fR[CHX][CHZ] = 1.0F;
			fR[CHZ][CHX] = -1.0F;
		}
		else
		{
			fR[CHX][CHZ] = -1.0F;
			fR[CHZ][CHX] = 1.0F;
		}
		return;
	}

	// compute moduli for the general case
	fmodGyz = sqrtf(fmodGyz);
	fmodGxyz = sqrtf(fmodGxyz);
	frecipmodGxyz = 1.0F / fmodGxyz;
	ftmp = fmodGxyz / fmodGyz;

	// normalize the accelerometer reading into the z column
	for (i = CHX; i <= CHZ; i++)
	{
		fR[i][CHZ] = fGc[i] * frecipmodGxyz;
	}

	// construct x column of orientation matrix
	fR[CHX][CHX] = fmodGyz * frecipmodGxyz;
	fR[CHY][CHX] = -fR[CHX][CHZ] * fR[CHY][CHZ] * ftmp;
	fR[CHZ][CHX] = -fR[CHX][CHZ] * fR[CHZ][CHZ] * ftmp;

	// construct y column of orientation matrix
	fR[CHX][CHY] = 0.0F;
	fR[CHY][CHY] = fR[CHZ][CHZ] * ftmp;
	fR[CHZ][CHY] = -fR[CHY][CHZ] * ftmp;

	return;
}
#endif // #if THISCOORDSYSTEM == NED

// Android accelerometer 3DOF tilt function computing rotation matrix fR
#if THISCOORDSYSTEM == ANDROID
void f3DOFTiltAndroid(float fR[][3], float fGc[])
{
	// the Android tilt matrix is mathematically identical to the NED tilt matrix
	// the Android self-consistency twist occurs at 90 deg roll
	f3DOFTiltNED(fR, fGc);
	return;
}
#endif // #if THISCOORDSYSTEM == ANDROID

// Windows 8 accelerometer 3DOF tilt function computing rotation matrix fR
#if (THISCOORDSYSTEM == WIN8) || (THISCOORDSYSTEM == ANDROID)
void f3DOFTiltWin8(float fR[][3], float fGc[])
{
	// the Win8 self-consistency twist occurs at 90 deg roll

	// local variables
	float fmodGxyz;			// modulus of the x, y, z accelerometer readings
	float fmodGxz;			// modulus of the x, z accelerometer readings
	float frecipmodGxyz;	// reciprocal of modulus
	float ftmp;				// scratch variable
	int8 i;					// counter

	// compute the accelerometer squared magnitudes
	fmodGxz = fGc[CHX] * fGc[CHX] + fGc[CHZ] * fGc[CHZ];
	fmodGxyz = fmodGxz + fGc[CHY] * fGc[CHY];

	// check for freefall special case where no solution is possible
	if (fmodGxyz == 0.0F)
	{
		f3x3matrixAeqI(fR);
		return;
	}

	// check for vertical up or down gimbal lock case
	if (fmodGxz == 0.0F)
	{
		f3x3matrixAeqScalar(fR, 0.0F);
		fR[CHX][CHX] = 1.0F;
		if (fGc[CHY] >= 0.0F)
		{
			fR[CHY][CHZ] = -1.0F;
			fR[CHZ][CHY] = 1.0F;
		}
		else
		{
			fR[CHY][CHZ] = 1.0F;
			fR[CHZ][CHY] = -1.0F;
		}
		return;
	}

	// compute moduli for the general case
	fmodGxz = sqrtf(fmodGxz);
	fmodGxyz = sqrtf(fmodGxyz);
	frecipmodGxyz = 1.0F / fmodGxyz;
	ftmp = fmodGxyz / fmodGxz;
	if (fGc[CHZ] < 0.0F)
	{
		ftmp = -ftmp;
	}

	// normalize the negated accelerometer reading into the z column
	for (i = CHX; i <= CHZ; i++)
	{
		fR[i][CHZ] = -fGc[i] * frecipmodGxyz;
	}

	// construct x column of orientation matrix
	fR[CHX][CHX] = -fR[CHZ][CHZ] * ftmp;
	fR[CHY][CHX] = 0.0F;
	fR[CHZ][CHX] = fR[CHX][CHZ] * ftmp;;

	// // construct y column of orientation matrix
	fR[CHX][CHY] = fR[CHX][CHZ] * fR[CHY][CHZ] * ftmp;
	fR[CHY][CHY] = -fmodGxz * frecipmodGxyz;
	if (fGc[CHZ] < 0.0F)
	{
		fR[CHY][CHY] = -fR[CHY][CHY];
	}
	fR[CHZ][CHY] = fR[CHY][CHZ] * fR[CHZ][CHZ] * ftmp;

	return;
}
#endif // #if (THISCOORDSYSTEM == WIN8)
#endif // #if F_USING_ACCEL  // Need tilt conversion routines

#if F_USING_MAG // Need eCompass conversion routines
// Aerospace NED magnetometer 3DOF flat eCompass function computing rotation matrix fR
#if THISCOORDSYSTEM == NED
void f3DOFMagnetometerMatrixNED(float fR[][3], float fBc[])
{
	// local variables
	float fmodBxy;			// modulus of the x, y magnetometer readings

	// compute the magnitude of the horizontal (x and y) magnetometer reading
	fmodBxy = sqrtf(fBc[CHX] * fBc[CHX] + fBc[CHY] * fBc[CHY]);

	// check for zero field special case where no solution is possible
	if (fmodBxy == 0.0F)
	{
		f3x3matrixAeqI(fR);
		return;
	}

	// define the fixed entries in the z row and column
	fR[CHZ][CHX] = fR[CHZ][CHY] = fR[CHX][CHZ] = fR[CHY][CHZ] = 0.0F;
	fR[CHZ][CHZ] = 1.0F;

	// define the remaining entries
	fR[CHX][CHX] = fR[CHY][CHY] = fBc[CHX] / fmodBxy;
	fR[CHY][CHX] = fBc[CHY] / fmodBxy;
	fR[CHX][CHY] = -fR[CHY][CHX];

	return;
}
#endif // #if THISCOORDSYSTEM == NED

// Android magnetometer 3DOF flat eCompass function computing rotation matrix fR
#if (THISCOORDSYSTEM == ANDROID) || (THISCOORDSYSTEM == WIN8)
void f3DOFMagnetometerMatrixAndroid(float fR[][3], float fBc[])
{
	// local variables
	float fmodBxy;			// modulus of the x, y magnetometer readings

	// compute the magnitude of the horizontal (x and y) magnetometer reading
	fmodBxy = sqrtf(fBc[CHX] * fBc[CHX] + fBc[CHY] * fBc[CHY]);

	// check for zero field special case where no solution is possible
	if (fmodBxy == 0.0F)
	{
		f3x3matrixAeqI(fR);
		return;
	}

	// define the fixed entries in the z row and column
	fR[CHZ][CHX] = fR[CHZ][CHY] = fR[CHX][CHZ] = fR[CHY][CHZ] = 0.0F;
	fR[CHZ][CHZ] = 1.0F;

	// define the remaining entries
	fR[CHX][CHX] = fR[CHY][CHY] = fBc[CHY] / fmodBxy;
	fR[CHX][CHY] = fBc[CHX] / fmodBxy;
	fR[CHY][CHX] = -fR[CHX][CHY];

	return;
}
#endif // #if THISCOORDSYSTEM == ANDROID

// Windows 8 magnetometer 3DOF flat eCompass function computing rotation matrix fR
#if (THISCOORDSYSTEM == WIN8)
void f3DOFMagnetometerMatrixWin8(float fR[][3], float fBc[])
{
	// call the Android function since it is identical to the Windows 8 matrix
	f3DOFMagnetometerMatrixAndroid(fR, fBc);

	return;
}
#endif // #if (THISCOORDSYSTEM == WIN8)

// NED: basic 6DOF e-Compass function computing rotation matrix fR and magnetic inclination angle fDelta
#if THISCOORDSYSTEM == NED
void feCompassNED(float fR[][3], float *pfDelta, float *pfsinDelta, float *pfcosDelta, float fBc[], float fGc[], float *pfmodBc, float *pfmodGc)
{
	// local variables
	float fmod[3];					// column moduli
	float fGcdotBc;					// dot product of vectors G.Bc
	float ftmp;						// scratch variable
	int8 i, j;						// loop counters

	// set the inclination angle to zero in case it is not computed later
	*pfDelta = *pfsinDelta = 0.0F;
	*pfcosDelta = 1.0F;

	// place the un-normalized gravity and geomagnetic vectors into the rotation matrix z and x axes
	for (i = CHX; i <= CHZ; i++)
	{
		fR[i][CHZ] = fGc[i];
		fR[i][CHX] = fBc[i];
	}

	// set y vector to vector product of z and x vectors
	fR[CHX][CHY] = fR[CHY][CHZ] * fR[CHZ][CHX] - fR[CHZ][CHZ] * fR[CHY][CHX];
	fR[CHY][CHY] = fR[CHZ][CHZ] * fR[CHX][CHX] - fR[CHX][CHZ] * fR[CHZ][CHX];
	fR[CHZ][CHY] = fR[CHX][CHZ] * fR[CHY][CHX] - fR[CHY][CHZ] * fR[CHX][CHX];

	// set x vector to vector product of y and z vectors
	fR[CHX][CHX] = fR[CHY][CHY] * fR[CHZ][CHZ] - fR[CHZ][CHY] * fR[CHY][CHZ];
	fR[CHY][CHX] = fR[CHZ][CHY] * fR[CHX][CHZ] - fR[CHX][CHY] * fR[CHZ][CHZ];
	fR[CHZ][CHX] = fR[CHX][CHY] * fR[CHY][CHZ] - fR[CHY][CHY] * fR[CHX][CHZ];

	// calculate the rotation matrix column moduli
	fmod[CHX] = sqrtf(fR[CHX][CHX] * fR[CHX][CHX] + fR[CHY][CHX] * fR[CHY][CHX] + fR[CHZ][CHX] * fR[CHZ][CHX]);
	fmod[CHY] = sqrtf(fR[CHX][CHY] * fR[CHX][CHY] + fR[CHY][CHY] * fR[CHY][CHY] + fR[CHZ][CHY] * fR[CHZ][CHY]);
	fmod[CHZ] = sqrtf(fR[CHX][CHZ] * fR[CHX][CHZ] + fR[CHY][CHZ] * fR[CHY][CHZ] + fR[CHZ][CHZ] * fR[CHZ][CHZ]);

	// normalize the rotation matrix columns
	if (!((fmod[CHX] == 0.0F) || (fmod[CHY] == 0.0F) || (fmod[CHZ] == 0.0F)))
	{
		// loop over columns j
		for (j = CHX; j <= CHZ; j++)
		{
			ftmp = 1.0F / fmod[j];
			// loop over rows i
			for (i = CHX; i <= CHZ; i++)
			{
				// normalize by the column modulus
				fR[i][j] *= ftmp;
			}
		}
	}
	else
	{
		// no solution is possible so set rotation to identity matrix
		f3x3matrixAeqI(fR);
		return;
	}

	// compute the geomagnetic inclination angle (deg)
	*pfmodGc = fmod[CHZ];
	*pfmodBc = sqrtf(fBc[CHX] * fBc[CHX] + fBc[CHY] * fBc[CHY] + fBc[CHZ] * fBc[CHZ]);
	fGcdotBc = fGc[CHX] * fBc[CHX] + fGc[CHY] * fBc[CHY] + fGc[CHZ] * fBc[CHZ];
	if (!((*pfmodGc == 0.0F) || (*pfmodBc == 0.0F)))
	{
		*pfsinDelta = fGcdotBc / (*pfmodGc * *pfmodBc);
		*pfcosDelta = sqrtf(1.0F - *pfsinDelta * *pfsinDelta);
		*pfDelta = fasin_deg(*pfsinDelta);
	}

	return;
}
#endif // #if THISCOORDSYSTEM == NED

// Android: basic 6DOF e-Compass function computing rotation matrix fR and magnetic inclination angle fDelta
#if THISCOORDSYSTEM == ANDROID
void feCompassAndroid(float fR[][3], float *pfDelta, float *pfsinDelta, float *pfcosDelta, float fBc[], float fGc[],
		float *pfmodBc, float *pfmodGc)
{
	// local variables
	float fmod[3];					// column moduli
	float fGcdotBc;					// dot product of vectors G.Bc
	float ftmp;						// scratch variable
	int8 i, j;						// loop counters

	// set the inclination angle to zero in case it is not computed later
	*pfDelta = *pfsinDelta = 0.0F;
	*pfcosDelta = 1.0F;

	// place the un-normalized gravity and geomagnetic vectors into the rotation matrix z and y axes
	for (i = CHX; i <= CHZ; i++)
	{
		fR[i][CHZ] = fGc[i];
		fR[i][CHY] = fBc[i];
	}

	// set x vector to vector product of y and z vectors
	fR[CHX][CHX] = fR[CHY][CHY] * fR[CHZ][CHZ] - fR[CHZ][CHY] * fR[CHY][CHZ];
	fR[CHY][CHX] = fR[CHZ][CHY] * fR[CHX][CHZ] - fR[CHX][CHY] * fR[CHZ][CHZ];
	fR[CHZ][CHX] = fR[CHX][CHY] * fR[CHY][CHZ] - fR[CHY][CHY] * fR[CHX][CHZ];

	// set y vector to vector product of z and x vectors
	fR[CHX][CHY] = fR[CHY][CHZ] * fR[CHZ][CHX] - fR[CHZ][CHZ] * fR[CHY][CHX];
	fR[CHY][CHY] = fR[CHZ][CHZ] * fR[CHX][CHX] - fR[CHX][CHZ] * fR[CHZ][CHX];
	fR[CHZ][CHY] = fR[CHX][CHZ] * fR[CHY][CHX] - fR[CHY][CHZ] * fR[CHX][CHX];

	// calculate the rotation matrix column moduli
	fmod[CHX] = sqrtf(fR[CHX][CHX] * fR[CHX][CHX] + fR[CHY][CHX] * fR[CHY][CHX] + fR[CHZ][CHX] * fR[CHZ][CHX]);
	fmod[CHY] = sqrtf(fR[CHX][CHY] * fR[CHX][CHY] + fR[CHY][CHY] * fR[CHY][CHY] + fR[CHZ][CHY] * fR[CHZ][CHY]);
	fmod[CHZ] = sqrtf(fR[CHX][CHZ] * fR[CHX][CHZ] + fR[CHY][CHZ] * fR[CHY][CHZ] + fR[CHZ][CHZ] * fR[CHZ][CHZ]);

	// normalize the rotation matrix columns
	if (!((fmod[CHX] == 0.0F) || (fmod[CHY] == 0.0F) || (fmod[CHZ] == 0.0F)))
	{
		// loop over columns j
		for (j = CHX; j <= CHZ; j++)
		{
			ftmp = 1.0F / fmod[j];
			// loop over rows i
			for (i = CHX; i <= CHZ; i++)
			{
				// normalize by the column modulus
				fR[i][j] *= ftmp;
			}
		}
	}
	else
	{
		// no solution is possible so set rotation to identity matrix
		f3x3matrixAeqI(fR);
		return;
	}

	// compute the geomagnetic inclination angle (deg)
	*pfmodGc = fmod[CHZ];
	*pfmodBc = sqrtf(fBc[CHX] * fBc[CHX] + fBc[CHY] * fBc[CHY] + fBc[CHZ] * fBc[CHZ]);
	fGcdotBc = fGc[CHX] * fBc[CHX] + fGc[CHY] * fBc[CHY] + fGc[CHZ] * fBc[CHZ];
	if (!((*pfmodGc == 0.0F) || (*pfmodBc == 0.0F)))
	{
		*pfsinDelta = -fGcdotBc / (*pfmodGc * *pfmodBc);
		*pfcosDelta = sqrtf(1.0F - *pfsinDelta * *pfsinDelta);
		*pfDelta = fasin_deg(*pfsinDelta);
	}

	return;
}
#endif // #if THISCOORDSYSTEM == ANDROID

// Win8: basic 6DOF e-Compass function computing rotation matrix fR and magnetic inclination angle fDelta
#if (THISCOORDSYSTEM == WIN8)
void feCompassWin8(float fR[][3], float *pfDelta, float *pfsinDelta, float *pfcosDelta, float fBc[], float fGc[],
		float *pfmodBc, float *pfmodGc)
{
	// local variables
	float fmod[3];					// column moduli
	float fGcdotBc;					// dot product of vectors G.Bc
	float ftmp;						// scratch variable
	int8 i, j;						// loop counters

	// set the inclination angle to zero in case it is not computed later
	*pfDelta = *pfsinDelta = 0.0F;
	*pfcosDelta = 1.0F;

	// place the negated un-normalized gravity and un-normalized geomagnetic vectors into the rotation matrix z and y axes
	for (i = CHX; i <= CHZ; i++)
	{
		fR[i][CHZ] = -fGc[i];
		fR[i][CHY] = fBc[i];
	}

	// set x vector to vector product of y and z vectors
	fR[CHX][CHX] = fR[CHY][CHY] * fR[CHZ][CHZ] - fR[CHZ][CHY] * fR[CHY][CHZ];
	fR[CHY][CHX] = fR[CHZ][CHY] * fR[CHX][CHZ] - fR[CHX][CHY] * fR[CHZ][CHZ];
	fR[CHZ][CHX] = fR[CHX][CHY] * fR[CHY][CHZ] - fR[CHY][CHY] * fR[CHX][CHZ];

	// set y vector to vector product of z and x vectors
	fR[CHX][CHY] = fR[CHY][CHZ] * fR[CHZ][CHX] - fR[CHZ][CHZ] * fR[CHY][CHX];
	fR[CHY][CHY] = fR[CHZ][CHZ] * fR[CHX][CHX] - fR[CHX][CHZ] * fR[CHZ][CHX];
	fR[CHZ][CHY] = fR[CHX][CHZ] * fR[CHY][CHX] - fR[CHY][CHZ] * fR[CHX][CHX];

	// calculate the rotation matrix column moduli
	fmod[CHX] = sqrtf(fR[CHX][CHX] * fR[CHX][CHX] + fR[CHY][CHX] * fR[CHY][CHX] + fR[CHZ][CHX] * fR[CHZ][CHX]);
	fmod[CHY] = sqrtf(fR[CHX][CHY] * fR[CHX][CHY] + fR[CHY][CHY] * fR[CHY][CHY] + fR[CHZ][CHY] * fR[CHZ][CHY]);
	fmod[CHZ] = sqrtf(fR[CHX][CHZ] * fR[CHX][CHZ] + fR[CHY][CHZ] * fR[CHY][CHZ] + fR[CHZ][CHZ] * fR[CHZ][CHZ]);

	// normalize the rotation matrix columns
	if (!((fmod[CHX] == 0.0F) || (fmod[CHY] == 0.0F) || (fmod[CHZ] == 0.0F)))
	{
		// loop over columns j
		for (j = CHX; j <= CHZ; j++)
		{
			ftmp = 1.0F / fmod[j];
			// loop over rows i
			for (i = CHX; i <= CHZ; i++)
			{
				// normalize by the column modulus
				fR[i][j] *= ftmp;
			}
		}
	}
	else
	{
		// no solution is possible so set rotation to identity matrix
		f3x3matrixAeqI(fR);
		return;
	}

	// compute the geomagnetic inclination angle (deg)
	*pfmodGc = fmod[CHZ];
	*pfmodBc = sqrtf(fBc[CHX] * fBc[CHX] + fBc[CHY] * fBc[CHY] + fBc[CHZ] * fBc[CHZ]);
	fGcdotBc = fGc[CHX] * fBc[CHX] + fGc[CHY] * fBc[CHY] + fGc[CHZ] * fBc[CHZ];
	if (!((*pfmodGc == 0.0F) || (*pfmodBc == 0.0F)))
	{
		*pfsinDelta = fGcdotBc / (*pfmodGc * *pfmodBc);
		*pfcosDelta = sqrtf(1.0F - *pfsinDelta * *pfsinDelta);
		*pfDelta = fasin_deg(*pfsinDelta);
	}

	return;
}
#endif // #if (THISCOORDSYSTEM == WIN8)
#endif // #if F_USING_MAG // Need eCompass conversion routines

// extract the NED angles in degrees from the NED rotation matrix
#if THISCOORDSYSTEM == NED
void fNEDAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg)
{
	// calculate the pitch angle -90.0 <= Theta <= 90.0 deg
	*pfTheDeg = fasin_deg(-R[CHX][CHZ]);

	// calculate the roll angle range -180.0 <= Phi < 180.0 deg
	*pfPhiDeg = fatan2_deg(R[CHY][CHZ], R[CHZ][CHZ]);

	// map +180 roll onto the functionally equivalent -180 deg roll
	if (*pfPhiDeg == 180.0F)
	{
		*pfPhiDeg = -180.0F;
	}

	// calculate the yaw (compass) angle 0.0 <= Psi < 360.0 deg
	if (*pfTheDeg == 90.0F)
	{
		// vertical upwards gimbal lock case
		*pfPsiDeg = fatan2_deg(R[CHZ][CHY], R[CHY][CHY]) + *pfPhiDeg;
	}
	else if (*pfTheDeg == -90.0F)
	{
		// vertical downwards gimbal lock case
		*pfPsiDeg = fatan2_deg(-R[CHZ][CHY], R[CHY][CHY]) - *pfPhiDeg;
	}
	else
	{
		// general case
		*pfPsiDeg = fatan2_deg(R[CHX][CHY], R[CHX][CHX]);
	}

	// map yaw angle Psi onto range 0.0 <= Psi < 360.0 deg
	if (*pfPsiDeg < 0.0F)
	{
		*pfPsiDeg += 360.0F;
	}

	// check for rounding errors mapping small negative angle to 360 deg
	if (*pfPsiDeg >= 360.0F)
	{
		*pfPsiDeg = 0.0F;
	}

	// for NED, the compass heading Rho equals the yaw angle Psi
	*pfRhoDeg = *pfPsiDeg;

	// calculate the tilt angle from vertical Chi (0 <= Chi <= 180 deg)
	*pfChiDeg = facos_deg(R[CHZ][CHZ]);

	return;
}
#endif // #if THISCOORDSYSTEM == NED

// extract the Android angles in degrees from the Android rotation matrix
#if THISCOORDSYSTEM == ANDROID
void fAndroidAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg)
{
	// calculate the roll angle -90.0 <= Phi <= 90.0 deg
	*pfPhiDeg = fasin_deg(R[CHX][CHZ]);

	// calculate the pitch angle -180.0 <= The < 180.0 deg
	*pfTheDeg = fatan2_deg(-R[CHY][CHZ], R[CHZ][CHZ]);

	// map +180 pitch onto the functionally equivalent -180 deg pitch
	if (*pfTheDeg == 180.0F)
	{
		*pfTheDeg = -180.0F;
	}

	// calculate the yaw (compass) angle 0.0 <= Psi < 360.0 deg
	if (*pfPhiDeg == 90.0F)
	{
		// vertical downwards gimbal lock case
		*pfPsiDeg = fatan2_deg(R[CHY][CHX], R[CHY][CHY]) - *pfTheDeg;
	}
	else if (*pfPhiDeg == -90.0F)
	{
		// vertical upwards gimbal lock case
		*pfPsiDeg = fatan2_deg(R[CHY][CHX], R[CHY][CHY]) + *pfTheDeg;
	}
	else
	{
		// general case
		*pfPsiDeg = fatan2_deg(-R[CHX][CHY], R[CHX][CHX]);
	}

	// map yaw angle Psi onto range 0.0 <= Psi < 360.0 deg
	if (*pfPsiDeg < 0.0F)
	{
		*pfPsiDeg += 360.0F;
	}

	// check for rounding errors mapping small negative angle to 360 deg
	if (*pfPsiDeg >= 360.0F)
	{
		*pfPsiDeg = 0.0F;
	}

	// the compass heading angle Rho equals the yaw angle Psi
	// this definition is compliant with Motorola Xoom tablet behavior
	*pfRhoDeg = *pfPsiDeg;

	// calculate the tilt angle from vertical Chi (0 <= Chi <= 180 deg)
	*pfChiDeg = facos_deg(R[CHZ][CHZ]);

	return;
}
#endif // #if THISCOORDSYSTEM == ANDROID

// extract the Windows 8 angles in degrees from the Windows 8 rotation matrix
#if (THISCOORDSYSTEM == WIN8)
void fWin8AnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg,
		float *pfRhoDeg, float *pfChiDeg)
{
	// calculate the roll angle -90.0 <= Phi <= 90.0 deg
	if (R[CHZ][CHZ] == 0.0F)
	{
		if (R[CHX][CHZ] >= 0.0F)
		{
			// tan(phi) is -infinity
			*pfPhiDeg = -90.0F;
		}
		else
		{
			// tan(phi) is +infinity
			*pfPhiDeg = 90.0F;
		}
	}
	else
	{
		// general case
		*pfPhiDeg = fatan_deg(-R[CHX][CHZ] / R[CHZ][CHZ]);
	}

	// first calculate the pitch angle The in the range -90.0 <= The <= 90.0 deg
	*pfTheDeg = fasin_deg(R[CHY][CHZ]);

	// use R[CHZ][CHZ]=cos(Phi)*cos(The) to correct the quadrant of The remembering
	// cos(Phi) is non-negative so that cos(The) has the same sign as R[CHZ][CHZ].
	if (R[CHZ][CHZ] < 0.0F)
	{
		// wrap The around +90 deg and -90 deg giving result 90 to 270 deg
		*pfTheDeg = 180.0F - *pfTheDeg;
	}

	// map the pitch angle The to the range -180.0 <= The < 180.0 deg
	if (*pfTheDeg >= 180.0F)
	{
		*pfTheDeg -= 360.0F;
	}

	// calculate the yaw angle Psi
	if (*pfTheDeg == 90.0F)
	{
		// vertical upwards gimbal lock case: -270 <= Psi < 90 deg
		*pfPsiDeg = fatan2_deg(R[CHX][CHY], R[CHX][CHX]) - *pfPhiDeg;
	}
	else if (*pfTheDeg == -90.0F)
	{
		// vertical downwards gimbal lock case: -270 <= Psi < 90 deg
		*pfPsiDeg = fatan2_deg(R[CHX][CHY], R[CHX][CHX]) + *pfPhiDeg;
	}
	else
	{
		// general case: -180 <= Psi < 180 deg
		*pfPsiDeg = fatan2_deg(-R[CHY][CHX], R[CHY][CHY]);

		// correct the quadrant for Psi using the value of The (deg) to give -180 <= Psi < 380 deg
		if (fabsf(*pfTheDeg) >= 90.0F)
		{
			*pfPsiDeg += 180.0F;
		}
	}

	// map yaw angle Psi onto range 0.0 <= Psi < 360.0 deg
	if (*pfPsiDeg < 0.0F)
	{
		*pfPsiDeg += 360.0F;
	}

	// check for any rounding error mapping small negative angle to 360 deg
	if (*pfPsiDeg >= 360.0F)
	{
		*pfPsiDeg = 0.0F;
	}

	// compute the compass angle Rho = 360 - Psi
	*pfRhoDeg = 360.0F - *pfPsiDeg;

	// check for rounding errors mapping small negative angle to 360 deg and zero degree case
	if (*pfRhoDeg >= 360.0F)
	{
		*pfRhoDeg = 0.0F;
	}

	// calculate the tilt angle from vertical Chi (0 <= Chi <= 180 deg)
	*pfChiDeg = facos_deg(R[CHZ][CHZ]);

	return;
}
#endif // #if (THISCOORDSYSTEM == WIN8)

// computes normalized rotation quaternion from a rotation vector (deg)
void fQuaternionFromRotationVectorDeg(Quaternion *pq, const float rvecdeg[], float fscaling)
{
	float fetadeg;			// rotation angle (deg)
	float fetarad;			// rotation angle (rad)
	float fetarad2;			// eta (rad)^2
	float fetarad4;			// eta (rad)^4
	float sinhalfeta;		// sin(eta/2)
	float fvecsq;			// q1^2+q2^2+q3^2
	float ftmp;				// scratch variable

	// compute the scaled rotation angle eta (deg) which can be both positve or negative
	fetadeg = fscaling * sqrtf(rvecdeg[CHX] * rvecdeg[CHX] + rvecdeg[CHY] * rvecdeg[CHY] + rvecdeg[CHZ] * rvecdeg[CHZ]);
	fetarad = fetadeg * FPIOVER180;
	fetarad2 = fetarad * fetarad;

	// calculate the sine and cosine using small angle approximations or exact
	// angles under sqrt(0.02)=0.141 rad is 8.1 deg and 1620 deg/s (=936deg/s in 3 axes) at 200Hz and 405 deg/s at 50Hz
	if (fetarad2 <= 0.02F)
	{
		// use MacLaurin series up to and including third order
		sinhalfeta = fetarad * (0.5F - ONEOVER48 * fetarad2);
	}
	else if (fetarad2 <= 0.06F)
	{
		// use MacLaurin series up to and including fifth order
		// angles under sqrt(0.06)=0.245 rad is 14.0 deg and 2807 deg/s (=1623deg/s in 3 axes) at 200Hz and 703 deg/s at 50Hz
		fetarad4 = fetarad2 * fetarad2;
		sinhalfeta = fetarad * (0.5F - ONEOVER48 * fetarad2 + ONEOVER3840 * fetarad4);
	}
	else
	{
		// use exact calculation
		sinhalfeta = (float)sinf(0.5F * fetarad);
	}

	// compute the vector quaternion components q1, q2, q3
	if (fetadeg != 0.0F)
	{
		// general case with non-zero rotation angle
		ftmp = fscaling * sinhalfeta / fetadeg;
		pq->q1 = rvecdeg[CHX] * ftmp;		// q1 = nx * sin(eta/2)
		pq->q2 = rvecdeg[CHY] * ftmp;		// q2 = ny * sin(eta/2)
		pq->q3 = rvecdeg[CHZ] * ftmp;		// q3 = nz * sin(eta/2)
	}
	else
	{
		// zero rotation angle giving zero vector component
		pq->q1 = pq->q2 = pq->q3 = 0.0F;
	}

	// compute the scalar quaternion component q0 by explicit normalization
	// taking care to avoid rounding errors giving negative operand to sqrt
	fvecsq = pq->q1 * pq->q1 + pq->q2 * pq->q2 + pq->q3 * pq->q3;
	if (fvecsq <= 1.0F)
	{
		// normal case
		pq->q0 = sqrtf(1.0F - fvecsq);
	}
	else
	{
		// rounding errors are present
		pq->q0 = 0.0F;
	}

	return;
}

// compute the orientation quaternion from a 3x3 rotation matrix
void fQuaternionFromRotationMatrix(float R[][3], Quaternion *pq)
{
	float fq0sq;			// q0^2
	float recip4q0;			// 1/4q0

	// get q0^2 and q0
	fq0sq = 0.25F * (1.0F + R[CHX][CHX] + R[CHY][CHY] + R[CHZ][CHZ]);
	pq->q0 = sqrtf(fabsf(fq0sq));

	// normal case when q0 is not small meaning rotation angle not near 180 deg
	if (pq->q0 > SMALLQ0)
	{
		// calculate q1 to q3
		recip4q0 = 0.25F / pq->q0;
		pq->q1 = recip4q0 * (R[CHY][CHZ] - R[CHZ][CHY]);
		pq->q2 = recip4q0 * (R[CHZ][CHX] - R[CHX][CHZ]);
		pq->q3 = recip4q0 * (R[CHX][CHY] - R[CHY][CHX]);
	} // end of general case
	else
	{
		// special case of near 180 deg corresponds to nearly symmetric matrix
		// which is not numerically well conditioned for division by small q0
		// instead get absolute values of q1 to q3 from leading diagonal
		pq->q1 = sqrtf(fabsf(0.5F + 0.5F * R[CHX][CHX] - fq0sq));
		pq->q2 = sqrtf(fabsf(0.5F + 0.5F * R[CHY][CHY] - fq0sq));
		pq->q3 = sqrtf(fabsf(0.5F + 0.5F * R[CHZ][CHZ] - fq0sq));

		// correct the signs of q1 to q3 by examining the signs of differenced off-diagonal terms
		if ((R[CHY][CHZ] - R[CHZ][CHY]) < 0.0F) pq->q1 = -pq->q1;
		if ((R[CHZ][CHX] - R[CHX][CHZ]) < 0.0F) pq->q2 = -pq->q2;
		if ((R[CHX][CHY] - R[CHY][CHX]) < 0.0F) pq->q3 = -pq->q3;
	} // end of special case

	// ensure that the resulting quaternion is normalized even if the input rotation matrix was not
	fqAeqNormqA(pq);


	return;
}

// compute the rotation matrix from an orientation quaternion
void fRotationMatrixFromQuaternion(float R[][3], const Quaternion *pq)
{
	float f2q;
	float f2q0q0, f2q0q1, f2q0q2, f2q0q3;
	float f2q1q1, f2q1q2, f2q1q3;
	float f2q2q2, f2q2q3;
	float f2q3q3;

	// set f2q to 2*q0 and calculate products
	f2q = 2.0F * pq->q0;
	f2q0q0 = f2q * pq->q0;
	f2q0q1 = f2q * pq->q1;
	f2q0q2 = f2q * pq->q2;
	f2q0q3 = f2q * pq->q3;
	// set f2q to 2*q1 and calculate products
	f2q = 2.0F * pq->q1;
	f2q1q1 = f2q * pq->q1;
	f2q1q2 = f2q * pq->q2;
	f2q1q3 = f2q * pq->q3;
	// set f2q to 2*q2 and calculate products
	f2q = 2.0F * pq->q2;
	f2q2q2 = f2q * pq->q2;
	f2q2q3 = f2q * pq->q3;
	f2q3q3 = 2.0F * pq->q3 * pq->q3;

	// calculate the rotation matrix assuming the quaternion is normalized
	R[CHX][CHX] = f2q0q0 + f2q1q1 - 1.0F;
	R[CHX][CHY] = f2q1q2 + f2q0q3;
	R[CHX][CHZ] = f2q1q3 - f2q0q2;
	R[CHY][CHX] = f2q1q2 - f2q0q3;
	R[CHY][CHY] = f2q0q0 + f2q2q2 - 1.0F;
	R[CHY][CHZ] = f2q2q3 + f2q0q1;
	R[CHZ][CHX] = f2q1q3 + f2q0q2;
	R[CHZ][CHY] = f2q2q3 - f2q0q1;
	R[CHZ][CHZ] = f2q0q0 + f2q3q3 - 1.0F;

	return;
}

// computes rotation vector (deg) from rotation quaternion
void fRotationVectorDegFromQuaternion(Quaternion *pq, float rvecdeg[])
{
	float fetarad;			// rotation angle (rad)
	float fetadeg;			// rotation angle (deg)
	float sinhalfeta;		// sin(eta/2)
	float ftmp;				// scratch variable

	// calculate the rotation angle in the range 0 <= eta < 360 deg
	if ((pq->q0 >= 1.0F) || (pq->q0 <= -1.0F))
	{
		// rotation angle is 0 deg or 2*180 deg = 360 deg = 0 deg
		fetarad = 0.0F;
		fetadeg = 0.0F;
	}
	else
	{
		// general case returning 0 < eta < 360 deg
		fetarad = 2.0F * acosf(pq->q0);
		fetadeg = fetarad * F180OVERPI;
	}

	// map the rotation angle onto the range -180 deg <= eta < 180 deg
	if (fetadeg >= 180.0F)
	{
		fetadeg -= 360.0F;
		fetarad = fetadeg * FPIOVER180;
	}

	// calculate sin(eta/2) which will be in the range -1 to +1
	sinhalfeta = (float)sinf(0.5F * fetarad);

	// calculate the rotation vector (deg)
	if (sinhalfeta == 0.0F)
	{
		// the rotation angle eta is zero and the axis is irrelevant
		rvecdeg[CHX] = rvecdeg[CHY] = rvecdeg[CHZ] = 0.0F;
	}
	else
	{
		// general case with non-zero rotation angle
		ftmp = fetadeg / sinhalfeta;
		rvecdeg[CHX] = pq->q1 * ftmp;
		rvecdeg[CHY] = pq->q2 * ftmp;
		rvecdeg[CHZ] = pq->q3 * ftmp;
	}

	return;
}

// function low pass filters an orientation quaternion and computes virtual gyro rotation rate
void fLPFOrientationQuaternion(Quaternion *pq, Quaternion *pLPq, float flpf, float fdeltat, float fOmega[])
{
	// local variables
	Quaternion fdeltaq;			// delta rotation quaternion
	float rvecdeg[3];					// rotation vector (deg)
	float ftmp;							// scratch variable

	// set fdeltaq to the delta rotation quaternion conjg(fLPq[n-1) . fqn
	fdeltaq = qconjgAxB(pLPq, pq);
	if (fdeltaq.q0 < 0.0F)
	{
		fdeltaq.q0 = -fdeltaq.q0;
		fdeltaq.q1 = -fdeltaq.q1;
		fdeltaq.q2 = -fdeltaq.q2;
		fdeltaq.q3 = -fdeltaq.q3;
	}

	// set ftmp to a scaled value which equals flpf in the limit of small rotations (q0=1)
	// but which rises to 1 (all pass) as the delta rotation angle increases (q0 tends to zero)
	ftmp = flpf + (1.0F - flpf) * sqrtf(fabs(1.0F - fdeltaq.q0 *  fdeltaq.q0));

	// scale the vector component of the delta rotation quaternion by the corrected lpf value
	// and re-compute the scalar component q0 to ensure normalization
	fdeltaq.q1 *= ftmp;
	fdeltaq.q2 *= ftmp;
	fdeltaq.q3 *= ftmp;
	fdeltaq.q0 = sqrtf(fabsf(1.0F - fdeltaq.q1 * fdeltaq.q1 - fdeltaq.q2 * fdeltaq.q2 - fdeltaq.q3 * fdeltaq.q3));

	// calculate the delta rotation vector from fdeltaq and the virtual gyro angular velocity (deg/s)
	fRotationVectorDegFromQuaternion(&fdeltaq, rvecdeg);
	ftmp = 1.0F / fdeltat;
	fOmega[CHX] = rvecdeg[CHX] * ftmp;
	fOmega[CHY] = rvecdeg[CHY] * ftmp;
	fOmega[CHZ] = rvecdeg[CHZ] * ftmp;

	// set LPq[n] = LPq[n-1] . deltaq[n]
	qAeqAxB(pLPq, &fdeltaq);

	// renormalize the low pass filtered quaternion to prevent error accumulation.
	// the renormalization function also ensures that q0 is non-negative
	fqAeqNormqA(pLPq);

	return;
}

// function compute the quaternion product qA * qB
void qAeqBxC(Quaternion *pqA, const Quaternion *pqB, const Quaternion *pqC)
{
	pqA->q0 = pqB->q0 * pqC->q0 - pqB->q1 * pqC->q1 - pqB->q2 * pqC->q2 - pqB->q3 * pqC->q3;
	pqA->q1 = pqB->q0 * pqC->q1 + pqB->q1 * pqC->q0 + pqB->q2 * pqC->q3 - pqB->q3 * pqC->q2;
	pqA->q2 = pqB->q0 * pqC->q2 - pqB->q1 * pqC->q3 + pqB->q2 * pqC->q0 + pqB->q3 * pqC->q1;
	pqA->q3 = pqB->q0 * pqC->q3 + pqB->q1 * pqC->q2 - pqB->q2 * pqC->q1 + pqB->q3 * pqC->q0;

	return;
}

// function compute the quaternion product qA = qA * qB
void qAeqAxB(Quaternion *pqA, const Quaternion *pqB)
{
	Quaternion qProd;

	// perform the quaternion product
	qProd.q0 = pqA->q0 * pqB->q0 - pqA->q1 * pqB->q1 - pqA->q2 * pqB->q2 - pqA->q3 * pqB->q3;
	qProd.q1 = pqA->q0 * pqB->q1 + pqA->q1 * pqB->q0 + pqA->q2 * pqB->q3 - pqA->q3 * pqB->q2;
	qProd.q2 = pqA->q0 * pqB->q2 - pqA->q1 * pqB->q3 + pqA->q2 * pqB->q0 + pqA->q3 * pqB->q1;
	qProd.q3 = pqA->q0 * pqB->q3 + pqA->q1 * pqB->q2 - pqA->q2 * pqB->q1 + pqA->q3 * pqB->q0;

	// copy the result back into qA
	*pqA = qProd;

	return;
}

// function compute the quaternion product conjg(qA) * qB
Quaternion qconjgAxB(const Quaternion *pqA, const Quaternion *pqB)
{
	Quaternion qProd;

	qProd.q0 = pqA->q0 * pqB->q0 + pqA->q1 * pqB->q1 + pqA->q2 * pqB->q2 + pqA->q3 * pqB->q3;
	qProd.q1 = pqA->q0 * pqB->q1 - pqA->q1 * pqB->q0 - pqA->q2 * pqB->q3 + pqA->q3 * pqB->q2;
	qProd.q2 = pqA->q0 * pqB->q2 + pqA->q1 * pqB->q3 - pqA->q2 * pqB->q0 - pqA->q3 * pqB->q1;
	qProd.q3 = pqA->q0 * pqB->q3 - pqA->q1 * pqB->q2 + pqA->q2 * pqB->q1 - pqA->q3 * pqB->q0;

	return qProd;
}

// function normalizes a rotation quaternion and ensures q0 is non-negative
void fqAeqNormqA(Quaternion *pqA)
{
	float fNorm;					// quaternion Norm

	// calculate the quaternion Norm
	fNorm = sqrtf(pqA->q0 * pqA->q0 + pqA->q1 * pqA->q1 + pqA->q2 * pqA->q2 + pqA->q3 * pqA->q3);
	if (fNorm > CORRUPTQUAT)
	{
		// general case
		fNorm = 1.0F / fNorm;
		pqA->q0 *= fNorm;
		pqA->q1 *= fNorm;
		pqA->q2 *= fNorm;
		pqA->q3 *= fNorm;
	}
	else
	{
		// return with identity quaternion since the quaternion is corrupted
		pqA->q0 = 1.0F;
		pqA->q1 = pqA->q2 = pqA->q3 = 0.0F;
	}

	// correct a negative scalar component if the function was called with negative q0
	if (pqA->q0 < 0.0F)
	{
		pqA->q0 = -pqA->q0;
		pqA->q1 = -pqA->q1;
		pqA->q2 = -pqA->q2;
		pqA->q3 = -pqA->q3;
	}

	return;
}

// set a quaternion to the unit quaternion
void fqAeq1(Quaternion *pqA)
{
	pqA->q0 = 1.0F;
	pqA->q1 = pqA->q2 = pqA->q3 = 0.0F;

	return;
}

// function computes the rotation quaternion that rotates unit vector u onto unit vector v as v=q*.u.q
// using q = 1/sqrt(2) * {sqrt(1 + u.v) - u x v / sqrt(1 + u.v)}
void fveqconjgquq(Quaternion *pfq, float fu[], float fv[])
{
	float fuxv[3];				// vector product u x v
	float fsqrt1plusudotv;		// sqrt(1 + u.v)
	float ftmp;					// scratch

	// compute sqrt(1 + u.v) and scalar quaternion component q0 (valid for all angles including 180 deg)
	fsqrt1plusudotv = sqrtf(fabsf(1.0F + fu[CHX] * fv[CHX] + fu[CHY] * fv[CHY] + fu[CHZ] * fv[CHZ]));
	pfq->q0 = ONEOVERSQRT2 * fsqrt1plusudotv;

	// calculate the vector product uxv
	fuxv[CHX] = fu[CHY] * fv[CHZ] - fu[CHZ] * fv[CHY];
	fuxv[CHY] = fu[CHZ] * fv[CHX] - fu[CHX] * fv[CHZ];
	fuxv[CHZ] = fu[CHX] * fv[CHY] - fu[CHY] * fv[CHX];

	// compute the vector component of the quaternion
	if (fsqrt1plusudotv != 0.0F)
	{
		// general case where u and v are not anti-parallel where u.v=-1
		ftmp = ONEOVERSQRT2 / fsqrt1plusudotv;
		pfq->q1 = -fuxv[CHX] * ftmp;
		pfq->q2 = -fuxv[CHY] * ftmp;
		pfq->q3 = -fuxv[CHZ] * ftmp;
	}
	else
	{
		// degenerate case where u and v are anti-aligned and the 180 deg rotation quaternion is not uniquely defined.
		// first calculate the un-normalized vector component (the scalar component q0 is already set to zero)
		pfq->q1 = fu[CHY] - fu[CHZ];
		pfq->q2 = fu[CHZ] - fu[CHX];
		pfq->q3 = fu[CHX] - fu[CHY];
		// and normalize the quaternion for this case checking for fu[CHX]=fu[CHY]=fuCHZ] where q1=q2=q3=0.
		ftmp = sqrtf(fabsf(pfq->q1 * pfq->q1 + pfq->q2 * pfq->q2 + pfq->q3 * pfq->q3));
		if (ftmp != 0.0F)
		{
			// normal case where all three components of fu (and fv=-fu) are not equal
			ftmp = 1.0F / ftmp;
			pfq->q1 *= ftmp;
			pfq->q2 *= ftmp;
			pfq->q3 *= ftmp;
		}
		else
		{
			// final case where the three entries are equal but since the vectors are known to be normalized
			// the vector u must be 1/root(3)*{1, 1, 1} or -1/root(3)*{1, 1, 1} so simply set the
			// rotation vector to 1/root(2)*{1, -1, 0} to cover both cases
			pfq->q1 = ONEOVERSQRT2;
			pfq->q2 = -ONEOVERSQRT2;
			pfq->q3 = 0.0F;
		}
	}

	return;
}
