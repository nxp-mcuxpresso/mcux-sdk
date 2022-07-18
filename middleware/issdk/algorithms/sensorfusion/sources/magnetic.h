/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file magnetic.h
    \brief Lower level magnetic calibration interface

    Many developers can utilize the NXP Sensor Fusion Library without ever
    making any adjustment to the lower level magnetic calibration functions
    defined in this file.
*/

#ifndef MAGNETIC_H
#define MAGNETIC_H

#ifndef F_USING_MAG
#define F_USING_MAG 0x0002  // normally should be defined in build.h
#endif

#if F_USING_MAG
/// @name Magnetic Calibration Constants
///@{
#define MAGBUFFSIZEX 14				///< x dimension in magnetometer buffer (12x24 equals 288 elements)
#define MAGBUFFSIZEY (2 * MAGBUFFSIZEX)		///< y dimension in magnetometer buffer (12x24 equals 288 elements)
#define MINMEASUREMENTS4CAL 110			///< minimum number of measurements for 4 element calibration
#define MINMEASUREMENTS7CAL 220			///< minimum number of measurements for 7 element calibration
#define MINMEASUREMENTS10CAL 330		///< minimum number of measurements for 10 element calibration
#define MAXMEASUREMENTS 360			///< maximum number of measurements used for calibration
#define CAL_INTERVAL_SECS 300			///< 300s or 5min interval for regular calibration checks
#define MINBFITUT 10.0F				///< minimum acceptable geomagnetic field B (uT) for valid calibration
#define MAXBFITUT 90.0F				///< maximum acceptable geomagnetic field B (uT) for valid calibration
#define FITERRORAGINGSECS 86400.0F		///< 24 hours: time (s) for fit error to increase (age) by e=2.718
#define MESHDELTACOUNTS 50			///< magnetic buffer mesh spacing in counts (here 5uT)
#define DEFAULTB 50.0F				///< default geomagnetic field (uT)
///@}

/// The Magnetometer Measurement Buffer holds a 3-dimensional "constellation"
/// of data points.
///
/// The constellation of points are used to compute magnetic hard/soft iron compensation terms.
/// The contents of this buffer are updated on a continuing basis.
struct MagBuffer
{
	int16_t iBs[3][MAGBUFFSIZEX][MAGBUFFSIZEY];		///< uncalibrated magnetometer readings
	int32_t index[MAGBUFFSIZEX][MAGBUFFSIZEY];		///< array of time indices
	int16_t tanarray[MAGBUFFSIZEX - 1];			///< array of tangents of (100 * angle)
	int16_t iMagBufferCount;				///< number of magnetometer readings
};

/// Magnetic Calibration Structure
struct MagCalibration
{
	// start of elements stored to flash memory on Save (16 * 4 = 64 bytes)
	float fV[3];					///< current hard iron offset x, y, z, (uT)
	float finvW[3][3];				///< current inverse soft iron matrix
	float fB;					///< current geomagnetic field magnitude (uT)
	float fBSq;					///< square of fB (uT^2)
	float fFitErrorpc;				///< current fit error %
	int32_t iValidMagCal;				///< solver used: 0 (no calibration) or 4, 7, 10 element
	// end of elements stored to flash memory
	// start of working elements not stored to flash memory
	float ftrV[3];					///< trial value of hard iron offset z, y, z (uT)
	float ftrinvW[3][3];			        ///< trial inverse soft iron matrix size
	float ftrB;					///< trial value of geomagnetic field magnitude in uT
	float ftrFitErrorpc;			        ///< trial value of fit error %
	float fA[3][3];					///< ellipsoid matrix A
	float finvA[3][3];				///< inverse of ellipsoid matrix A
	float fmatA[10][10];			        ///< scratch 10x10 float matrix used by calibration algorithms
	float fmatB[10][10];			        ///< scratch 10x10 float matrix used by calibration algorithms
	float fvecA[10];				///< scratch 10x1 vector used by calibration algorithms
	float fvecB[4];					///< scratch 4x1 vector used by calibration algorithms
	float fYTY;					///< Y^T.Y for 4 element calibration = (iB^2)^2
	int32_t iSumBs[3];				///< sum of measurements in buffer (counts)
	int32_t iMeanBs[3];				///< average magnetic measurement (counts)
	int32_t itimeslice;				///< counter for tine slicing magnetic calibration calculations
	int8_t iCalInProgress;			        ///< flag denoting that a calibration is in progress
	int8_t iNewCalibrationAvailable;	        ///< flag denoting that a new calibration has been computed
	int8_t iInitiateMagCal;			        ///< flag to start a new magnetic calibration
	int8_t iMagBufferReadOnly;		        ///< flag to denote that the magnetic measurement buffer is temporarily read only
	int8_t i4ElementSolverTried;		        ///< flag to denote at least one attempt made with 4 element calibration
	int8_t i7ElementSolverTried;		        ///< flag to denote at least one attempt made with 4 element calibration
	int8_t i10ElementSolverTried;		        ///< flag to denote at least one attempt made with 4 element calibration
};


struct MagSensor;  // actual typedef is located in sensor_fusion_types.h

/// @name Function prototypes for functions in magnetic.c
/// These functions comprise the core of the magnetic calibration features of
/// the library.  Parameter descriptions are not included here,
/// as details are provided in sensor_fusion.h.
///@{
void fInitializeMagCalibration(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer);
void iUpdateMagBuffer(struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag, int32_t loopcounter);
void fInvertMagCal(struct MagSensor *pthisMag, struct MagCalibration *pthisMagCal);
void fRunMagCalibration(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor* pthisMag, int32_t loopcounter);
void fUpdateMagCalibration4(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateMagCalibration7(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateMagCalibration10(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateMagCalibration4Slice(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateMagCalibration7Slice(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
void fUpdateMagCalibration10Slice(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag);
///@}
#else    // if F_USING_MAG
struct MagBuffer
{
    void *placeholder;
};

/// Magnetic Calibration Structure
struct MagCalibration
{
    void *placeholder;
};
#endif   // if F_USING_MAG
#endif   // #ifndef MAGNETIC_H
