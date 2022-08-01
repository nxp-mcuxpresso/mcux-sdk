/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Sensor fusion requires a fairly extensive set of data structures, which are
// defined in this file.  The top level structure is shown near the bottom.  The
// size of this structure (SensorFusionGlobals) varies dramatically as a function
// of which fusion variations have been selected in build.h.

/*! \file sensor_fusion.h
    \brief The sensor_fusion.h file implements the top level programming interface
*/

#ifndef SENSOR_FUSION_TYPES_H
#define SENSOR_FUSION_TYPES_H

// Standard includes that everyone needs
#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdint.h"


#include "issdk_hal.h"                  // Hardware Abstraction Layer board dependencies beyond those generated in board.h by PEX
#include "build.h"                      // This is where the build parameters are defined
#include "magnetic.h"                   // Magnetic calibration functions/structures
#include "precisionAccelerometer.h"     // Accel calibration functions/structures
#include "orientation.h"                // Functions for manipulating orientations
#include "register_io_spi.h"

/// @name Integer Typedefs
/// Typedefs to map common integer types to standard form
///@{
typedef unsigned char byte;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
///@}

/// the quaternion type to be transmitted
typedef enum quaternion {
    Q3,         ///< Quaternion derived from 3-axis accel (tilt)
    Q3M,        ///< Quaternion derived from 3-axis mag only (auto compass algorithm)
    Q3G,        ///< Quaternion derived from 3-axis gyro only (rotation)
    Q6MA,       ///< Quaternion derived from 3-axis accel + 3 axis mag (eCompass)
    Q6AG,       ///< Quaternion derived from 3-axis accel + 3-axis gyro (gaming)
    Q9          ///< Quaternion derived from full 9-axis sensor fusion
} quaternion_type;

/// @name Vector Components
/// Index values for accessing vector terms
///@{
#define CHX 0   ///< Used to access X-channel entries in various data data structures
#define CHY 1   ///< Used to access Y-channel entries in various data data structures
#define CHZ 2   ///< Used to access Z-channel entries in various data data structures
///@}

// booleans
#define true 1  ///< Boolean TRUE
#define false 0 ///< Boolean FALSE

/// @name Generic bit-field values
/// Generic bit-field values
///@{
#define B0 (1 << 0)
#define B1 (1 << 1)
#define B2 (1 << 2)
#define B3 (1 << 3)
///@}

/// @name Math Constants
/// useful multiplicative conversion constants
///@{
#define PI 3.141592654F				///< pi
#define PIOVER2 1.570796327F			///< pi / 2
#define FPIOVER180 0.01745329251994F	        ///< degrees to radians conversion = pi / 180
#define F180OVERPI 57.2957795130823F	        ///< radians to degrees conversion = 180 / pi
#define F180OVERPISQ 3282.8063500117F	        ///< square of F180OVERPI
#define ONETHIRD 0.33333333F			///< one third
#define ONESIXTH 0.166666667F			///< one sixth
#define ONESIXTEENTH 0.0625F			///< one sixteenth
#define ONEOVER12 0.083333333F			///< 1 / 12
#define ONEOVER48 0.02083333333F		///< 1 / 48
#define ONEOVER120 0.0083333333F		///< 1 / 120
#define ONEOVER3840 0.0002604166667F	        ///< 1 / 3840
#define ONEOVERSQRT2 0.707106781F		///< 1/sqrt(2)
#define SQRT15OVER4  0.968245837F		///< sqrt(15)/4
#define GTOMSEC2 9.80665			///< standard gravity in m/s2
///@}

// Placeholder structures (redefined later, but needed now for pointer definitions)
struct SensorFusionGlobals;                     ///< Top level structure has pointers to everything else
struct StatusSubsystem;                         ///< Application-specific status subsystem
struct PhysicalSensor;                          ///< We'll have one of these for each physical sensor (FXOS8700 = 1 physical sensor)
struct ControlSubsystem;                        ///< Application-specific serial communications system

typedef enum {                                  ///  These are the state definitions for the status subsystem
	OFF,                                    ///< Application hasn't started
	INITIALIZING,                           ///< Initializing sensors and algorithms
	LOWPOWER,                               ///< Running in reduced power mode
	NORMAL,                                 ///< Operation is Nominal
        RECEIVING_WIRED,                        ///< Receiving commands over wired interface (momentary)
        RECEIVING_WIRELESS,                     ///< Receiving commands over wireless interface (momentary)
	HARD_FAULT,                             ///< Non-recoverable FAULT = something went very wrong
        SOFT_FAULT                              ///< Recoverable FAULT = something went wrong, but we can keep going
} fusion_status_t;

// declare typedefs for function prototypes that need to be installed
typedef int8_t (initializeSensor_t) (
    struct PhysicalSensor *sensor,
    struct SensorFusionGlobals *sfg
) ;
typedef int8_t (readSensor_t) (
    struct PhysicalSensor *sensor,
    struct SensorFusionGlobals *sfg
) ;
typedef int8_t (readSensors_t) (
    struct SensorFusionGlobals *sfg,
    uint16_t read_loop_counter
) ;
typedef int8_t (installSensor_t) (
    struct SensorFusionGlobals *sfg,    ///< Global data structure pointer
    struct PhysicalSensor *sensor,      ///< SF Structure to store sensor configuration
    uint16_t addr,                      ///< I2C address or SPI_ADDR
    uint16_t schedule,                  ///< Specifies sampling interval
    void *bus_driver,                   ///< I2C or SPI handle
    registerDeviceInfo_t *busInfo,      ///< information required for bus power management
    initializeSensor_t *initialize,     ///< SF Sensor Initialization Function pointer
    readSensor_t *read                  ///< SF Sensor Read Function pointer
);
#define SPI_ADDR 0x00   // Use SPI_ADDR as the address parameter to the installSensor function for SPI-based sensors.
                        // 0x00 is reserved for I2C General Call, and will therefore never occur for any sensor type

typedef void   (initializeFusionEngine_t) 	(struct SensorFusionGlobals *sfg);
typedef void   (runFusion_t) 			(struct SensorFusionGlobals *sfg);
typedef void   (clearFIFOs_t) 			(struct SensorFusionGlobals *sfg);
typedef void   (conditionSensorReadings_t) 	(struct SensorFusionGlobals *sfg);
typedef void   (applyPerturbation_t) 		(struct SensorFusionGlobals *sfg) ;
typedef void   (setStatus_t) 			(struct SensorFusionGlobals *sfg, fusion_status_t status);
typedef void   (updateStatus_t) 		(struct SensorFusionGlobals *sfg);
typedef void   (ssSetStatus_t) 			(struct StatusSubsystem *pStatus, fusion_status_t status);
typedef void   (ssUpdateStatus_t) 		(struct StatusSubsystem *pStatus);

/// \brief An instance of PhysicalSensor structure type should be allocated for each physical sensors (combo devices = 1)
///
/// These structures sit 'on-top-of' the pre-7.0 sensor fusion structures and give us the ability to do run
/// time driver installation.
struct PhysicalSensor {
        registerDeviceInfo_t deviceInfo;        ///< I2C device context
	void *bus_driver;  			///< should be of type (ARM_DRIVER_I2C* for I2C-based sensors, ARM_DRIVER_SPI* for SPI)
        registerDeviceInfo_t *busInfo;          ///< information required for bus power management
	uint16_t addr;  			///< I2C address if applicable
        uint16_t isInitialized;                 ///< Bitfields to indicate sensor is active (use SensorBitFields from build.h)
        spiSlaveSpecificParams_t slaveParams;   ///< SPI specific parameters.  Not used for I2C.
	struct PhysicalSensor *next;		///< pointer to next sensor in this linked list
        uint16_t schedule;                      ///< Parameter to control sensor sampling rate
	initializeSensor_t *initialize;  	///< pointer to function to initialize sensor using the supplied drivers
	readSensor_t *read;			///< pointer to function to read       sensor using the supplied drivers
};

// Now start "standard" sensor fusion structure definitions

/// \brief The PressureSensor structure stores raw and processed measurements for an altimeter.
///
/// The PressureSensor structure stores raw and processed measurements, as well as
/// metadata for a pressure sensor/altimeter.
struct PressureSensor
{
	uint8_t iWhoAmI;		        ///< sensor whoami
        bool  isEnabled;                        ///< true if the device is sampling
	int32_t iH;				///< most recent unaveraged height (counts)
	int32_t iP;				///< most recent unaveraged pressure (counts)
	float fH;				///< most recent unaveraged height (m)
	float fT;				///< most recent unaveraged temperature (C)
	float fmPerCount;		        ///< meters per count
	float fCPerCount;		        ///< degrees Celsius per count
	int16_t iT;				///< most recent unaveraged temperature (counts)
};

/// \brief The AccelSensor structure stores raw and processed measurements for a 3-axis accelerometer.
///
/// The AccelSensor structure stores raw and processed measurements, as well as metadata
/// for a single 3-axis accelerometer.  This structure is
/// normally "fed" by the sensor driver and "consumed" by the fusion routines.
struct AccelSensor
{
	uint8_t iWhoAmI;			///< sensor whoami
        bool  isEnabled;                        ///< true if the device is sampling
	uint8_t iFIFOCount;			///< number of measurements read from FIFO
        uint16_t iFIFOExceeded;                 ///< Number of samples received in excess of software FIFO size
	int16_t iGsFIFO[ACCEL_FIFO_SIZE][3];	///< FIFO measurements (counts)
        // End of common fields which can be referenced via FifoSensor union type
	float fGs[3];			        ///< averaged measurement (g)
	float fGc[3];				///< averaged precision calibrated measurement (g)
	float fgPerCount;			///< g per count
	float fCountsPerg;			///< counts per g
	int16_t iGs[3];				///< averaged measurement (counts)
	int16_t iGc[3];				///< averaged precision calibrated measurement (counts)
	int16_t iCountsPerg;			///< counts per g
};

/// \brief The MagSensor structure stores raw and processed measurements for a 3-axis magnetic sensor.
///
/// The MagSensor structure stores raw and processed measurements, as well as metadata
/// for a single 3-axis magnetometer.  This structure is
/// normally "fed" by the sensor driver and "consumed" by the fusion routines.
struct MagSensor
{
	uint8_t iWhoAmI;			///< sensor whoami
        bool  isEnabled;                        ///< true if the device is sampling
	uint8_t iFIFOCount;			///< number of measurements read from FIFO
        uint16_t iFIFOExceeded;                 ///< Number of samples received in excess of software FIFO size
	int16_t iBsFIFO[MAG_FIFO_SIZE][3];	///< FIFO measurements (counts)
        // End of common fields which can be referenced via FifoSensor union type
	float fBs[3];				///< averaged un-calibrated measurement (uT)
	float fBc[3];				///< averaged calibrated measurement (uT)
	float fuTPerCount;			///< uT per count
	float fCountsPeruT;			///< counts per uT
	int16_t iBs[3];				///< averaged uncalibrated measurement (counts)
	int16_t iBc[3];				///< averaged calibrated measurement (counts)
	int16_t iCountsPeruT;			///< counts per uT
};

/// \brief The GyroSensor structure stores raw and processed measurements for a 3-axis gyroscope.
///
/// The GyroSensor structure stores raw and processed measurements, as well as metadata
/// for a single 3-axis gyroscope.  This structure is
/// normally "fed" by the sensor driver and "consumed" by the fusion routines.
struct GyroSensor
{
	uint8_t iWhoAmI;			///< sensor whoami
        bool  isEnabled;                        ///< true if the device is sampling
	uint8_t iFIFOCount;			///< number of measurements read from FIFO
        uint16_t iFIFOExceeded;                 ///< Number of samples received in excess of software FIFO size
	int16_t iYsFIFO[GYRO_FIFO_SIZE][3];	///< FIFO measurements (counts)
        // End of common fields which can be referenced via FifoSensor union type
	float fYs[3];				///< averaged measurement (deg/s)
	float fDegPerSecPerCount;		///< deg/s per count
	int16_t iCountsPerDegPerSec;		///< counts per deg/s
	int16_t iYs[3];				///< average measurement (counts)
};

/// \brief The FifoSensor union allows us to use common pointers for Accel, Mag & Gyro logical sensor structures.
///
/// Common elements include: iWhoAmI, isEnabled, iFIFOCount, iFIFOExceeded and the FIFO itself.
union FifoSensor  {
    struct GyroSensor Gyro;
    struct MagSensor  Mag;
    struct AccelSensor Accel;
};

/// The SV_1DOF_P_BASIC structure contains state information for a pressure sensor/altimeter.
struct SV_1DOF_P_BASIC
{
	float fLPH;				///< low pass filtered height (m)
	float fLPT;				///< low pass filtered temperature (C)
	float fdeltat;				///< fusion time interval (s)
	float flpf;				///< low pass filter coefficient
	int32_t systick;			///< systick timer
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// This is the 3DOF basic accelerometer state vector structure.
struct SV_3DOF_G_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;				///< low pass roll (deg)
	float fLPThe;				///< low pass pitch (deg)
	float fLPPsi;				///< low pass yaw (deg)
	float fLPRho;				///< low pass compass (deg)
	float fLPChi;				///< low pass tilt from vertical (deg)
	float fLPR[3][3];			///< low pass filtered orientation matrix
	Quaternion fLPq;			///< low pass filtered orientation quaternion
	float fLPRVec[3];			///< rotation vector
	float fOmega[3];			///< angular velocity (deg/s)
	int32_t systick;			///< systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];				///< unfiltered orientation matrix
	Quaternion fq;				///< unfiltered orientation quaternion
	float fdeltat;				///< fusion time interval (s)
	float flpf;				///< low pass filter coefficient
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// This is the 3DOF basic magnetometer state vector structure/
struct SV_3DOF_B_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;			        ///< low pass roll (deg)
	float fLPThe;				///< low pass pitch (deg)
	float fLPPsi;				///< low pass yaw (deg)
	float fLPRho;				///< low pass compass (deg)
	float fLPChi;				///< low pass tilt from vertical (deg)
	float fLPR[3][3];			///< low pass filtered orientation matrix
	Quaternion fLPq;			///< low pass filtered orientation quaternion
	float fLPRVec[3];			///< rotation vector
	float fOmega[3];			///< angular velocity (deg/s)
	int32_t systick;			///< systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];				///< unfiltered orientation matrix
	Quaternion fq;				///< unfiltered orientation quaternion
	float fdeltat;				///< fusion time interval (s)
	float flpf;				///< low pass filter coefficient
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// SV_3DOF_Y_BASIC structure is the 3DOF basic gyroscope state vector structure.
struct SV_3DOF_Y_BASIC
{
	// start: elements common to all motion state vectors
	float fPhi;				///< roll (deg)
	float fThe;				///< pitch (deg)
	float fPsi;				///< yaw (deg)
	float fRho;				///< compass (deg)
	float fChi;				///< tilt from vertical (deg)
	float fR[3][3];				///< unfiltered orientation matrix
	Quaternion fq;				///< unfiltered orientation quaternion
	float fRVec[3];				///< rotation vector
	float fOmega[3];			///< angular velocity (deg/s)
	int32_t systick;			///< systick timer
	// end: elements common to all motion state vectors
	float fdeltat;				///< fusion filter sampling interval (s)
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// SV_6DOF_GB_BASIC is the 6DOF basic accelerometer and magnetometer state vector structure.
struct SV_6DOF_GB_BASIC
{
	// start: elements common to all motion state vectors
	float fLPPhi;				///< low pass roll (deg)
	float fLPThe;				///< low pass pitch (deg)
	float fLPPsi;				///< low pass yaw (deg)
	float fLPRho;				///< low pass compass (deg)
	float fLPChi;				///< low pass tilt from vertical (deg)
	float fLPR[3][3];			///< low pass filtered orientation matrix
	Quaternion fLPq;			///< low pass filtered orientation quaternion
	float fLPRVec[3];			///< rotation vector
	float fOmega[3];			///< virtual gyro angular velocity (deg/s)
	int32_t systick;			///< systick timer
	// end: elements common to all motion state vectors
	float fR[3][3];				///< unfiltered orientation matrix
	Quaternion fq;				///< unfiltered orientation quaternion
	float fDelta;				///< unfiltered inclination angle (deg)
	float fLPDelta;				///< low pass filtered inclination angle (deg)
	float fdeltat;				///< fusion time interval (s)
	float flpf;				///< low pass filter coefficient
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// SV_6DOF_GY_KALMAN is the 6DOF Kalman filter accelerometer and gyroscope state vector structure.
struct SV_6DOF_GY_KALMAN
{
	// start: elements common to all motion state vectors
	float fPhiPl;				///< roll (deg)
	float fThePl;				///< pitch (deg)
	float fPsiPl;				///< yaw (deg)
	float fRhoPl;				///< compass (deg)
	float fChiPl;				///< tilt from vertical (deg)
	float fRPl[3][3];			///< a posteriori orientation matrix
	Quaternion fqPl;			///< a posteriori orientation quaternion
	float fRVecPl[3];			///< rotation vector
	float fOmega[3];			///< average angular velocity (deg/s)
	int32_t systick;			///< systick timer;
	// end: elements common to all motion state vectors
	float fQw6x6[6][6];			///< covariance matrix Qw
	float fK6x3[6][3];			///< kalman filter gain matrix K
	float fQwCT6x3[6][3];			///< Qw.C^T matrix
	float fQv;				///< measurement noise covariance matrix leading diagonal
	float fZErr[3];				///< measurement error vector
	float fqgErrPl[3];			///< gravity vector tilt orientation quaternion error (dimensionless)
	float fbPl[3];				///< gyro offset (deg/s)
	float fbErrPl[3];			///< gyro offset error (deg/s)
	float fAccGl[3];			///< linear acceleration (g) in global frame
	float fdeltat;				///< sensor fusion interval (s)
	float fAlphaOver2;			///< PI / 180 * fdeltat / 2
	float fAlphaSqOver4;		        ///< (PI / 180 * fdeltat)^2 / 4
	float fAlphaSqQvYQwbOver12;		///< (PI / 180 * fdeltat)^2 * (QvY + Qwb) / 12
	float fAlphaQwbOver6;			///< (PI / 180 * fdeltat) * Qwb / 6
	float fQwbOver3;			///< Qwb / 3
	float fMaxGyroOffsetChange;		///< maximum permissible gyro offset change per iteration (deg/s)
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// SV_9DOF_GBY_KALMAN is the 9DOF Kalman filter accelerometer, magnetometer and gyroscope state vector structure.
struct SV_9DOF_GBY_KALMAN
{
	// start: elements common to all motion state vectors
	float fPhiPl;				///< roll (deg)
	float fThePl;				///< pitch (deg)
	float fPsiPl;				///< yaw (deg)
	float fRhoPl;				///< compass (deg)
	float fChiPl;				///< tilt from vertical (deg)
	float fRPl[3][3];			///< a posteriori orientation matrix
	Quaternion fqPl;			///< a posteriori orientation quaternion
	float fRVecPl[3];			///< rotation vector
	float fOmega[3];			///< average angular velocity (deg/s)
	int32_t systick;			///< systick timer;
	// end: elements common to all motion state vectors
	float fQw9x9[9][9];			///< covariance matrix Qw
	float fK9x6[9][6];			///< kalman filter gain matrix K
	float fQwCT9x6[9][6];			///< Qw.C^T matrix
	float fZErr[6];				///< measurement error vector
	float fQv6x1[6];			///< measurement noise covariance matrix leading diagonal
	float fDeltaPl;				///< a posteriori inclination angle from Kalman filter (deg)
	float fsinDeltaPl;			///< sin(fDeltaPl)
	float fcosDeltaPl;			///< cos(fDeltaPl)
	float fqgErrPl[3];			///< gravity vector tilt orientation quaternion error (dimensionless)
	float fqmErrPl[3];			///< geomagnetic vector tilt orientation quaternion error (dimensionless)
	float fbPl[3];				///< gyro offset (deg/s)
	float fbErrPl[3];			///< gyro offset error (deg/s)
	float fAccGl[3];			///< linear acceleration (g) in global frame
	float fVelGl[3];			///< velocity (m/s) in global frame
	float fDisGl[3];			///< displacement (m) in global frame
	float fdeltat;				///< sensor fusion interval (s)
	float fgdeltat;				///< g (m/s2) * fdeltat
	float fAlphaOver2;			///< PI / 180 * fdeltat / 2
	float fAlphaSqOver4;			///< (PI / 180 * fdeltat)^2 / 4
	float fAlphaSqQvYQwbOver12;		///< (PI / 180 * fdeltat)^2 * (QvY + Qwb) / 12
	float fAlphaQwbOver6;			///< (PI / 180 * fdeltat) * Qwb / 6
	float fQwbOver3;			///< Qwb / 3
	float fMaxGyroOffsetChange;		///< maximum permissible gyro offset change per iteration (deg/s)
	int8_t iFirstAccelMagLock;		///< denotes that 9DOF orientation has locked to 6DOF eCompass
	int8_t resetflag;			///< flag to request re-initialization on next pass
};

/// Excluding SV_1DOF_P_BASIC, Any of the SV_ fusion structures above could
/// be cast to type SV_COMMON for dereferencing.
struct SV_COMMON {
	float fPhi;				///< roll (deg)
	float fThe;				///< pitch (deg)
	float fPsi;				///< yaw (deg)
	float fRho;				///< compass (deg)
	float fChi;				///< tilt from vertical (deg)
	float fRM[3][3];			///< orientation matrix
	Quaternion fq;			        ///< orientation quaternion
	float fRVec[3];			        ///< rotation vector
	float fOmega[3];			///< average angular velocity (deg/s)
	int32_t systick;			///< systick timer;
};
typedef struct SV_COMMON *SV_ptr;

/// \brief The top level fusion structure
///
/// The top level fusion structure grows/shrinks based upon flag definitions
/// contained in build.h.  These same flags will populate the .iFlags field for
/// run-time access.
typedef struct SensorFusionGlobals
{
	// Subsystem Pointers
        ///@{
        /// @name SubsystemPointers
        /// The Status and Control subsystems can be used as-is, or completely
        /// replaced with alternate implementations, as long as those implementations
        /// provide the same interfaces defined in control.h and status.h.
	struct ControlSubsystem *pControlSubsystem;
	struct StatusSubsystem *pStatusSubsystem;
        ///@}
        ///@{
        /// @name MiscFields
        uint32_t iFlags;                        ///< a bit-field of sensors and algorithms used
	struct PhysicalSensor *pSensors;    	        ///< a linked list of physical sensors
	volatile uint8_t iPerturbation;	        ///< test perturbation to be applied
	// Book-keeping variables
	int32_t loopcounter;			///< counter incrementing each iteration of sensor fusion (typically 25Hz)
	int32_t systick_I2C;			///< systick counter to benchmark I2C reads
	int32_t systick_Spare;			///< systick counter for counts spare waiting for timing interrupt
        ///@}
        ///@{
        /// @name SensorRelatedStructures
        /// These structures provide homes for sensor readings, as well as
        /// various calibration functions.  Only those needed for a specific
        /// build are included.
#if     F_1DOF_P_BASIC
	struct PressureSensor	Pressure;       ///< pressure sensor storage
#endif
#if     F_USING_ACCEL
	struct AccelSensor 	Accel;                  ///< accelerometer storage
	struct AccelCalibration AccelCal;              ///< structures for accel calibration
	struct AccelBuffer AccelBuffer;                ///< storage for points used for calibration
#endif
#if     F_USING_MAG
	struct MagSensor 	Mag;                    ///< magnetometer storage
	struct MagCalibration MagCal;                  ///< mag cal storage
	struct MagBuffer MagBuffer;                    ///< mag cal constellation points
#endif
#if     F_USING_GYRO
	struct GyroSensor 	Gyro;                   ///< gyro storage
#endif
        ///@}
        ///@{
        /// @name FusionSpecificStructures
#if     F_1DOF_P_BASIC
	struct SV_1DOF_P_BASIC SV_1DOF_P_BASIC;        ///< Pressure
#endif
#if     F_3DOF_G_BASIC
	struct SV_3DOF_G_BASIC SV_3DOF_G_BASIC;        ///< Gravity
#endif
#if     F_3DOF_B_BASIC
	struct SV_3DOF_B_BASIC SV_3DOF_B_BASIC;        ///< Magnetic
#endif
#if     F_3DOF_Y_BASIC
	struct SV_3DOF_Y_BASIC SV_3DOF_Y_BASIC;        ///< Gyro
#endif
#if     F_6DOF_GB_BASIC            // 6DOF accel and mag eCompass: (accel + mag)
	struct SV_6DOF_GB_BASIC SV_6DOF_GB_BASIC;      ///< eCompass (Gravity + Magnetic)
#endif
#if     F_6DOF_GY_KALMAN
	struct SV_6DOF_GY_KALMAN SV_6DOF_GY_KALMAN;    ///< 6-axis gravity + angular rates Kalman storage
#endif
#if     F_9DOF_GBY_KALMAN
	struct SV_9DOF_GBY_KALMAN SV_9DOF_GBY_KALMAN;  ///< 9-axis storage
#endif
        ///@}
        ///@{
        /// @name FunctionPointers
        /// Function pointers (the SF library external interface)
	installSensor_t 	*installSensor;         ///< function for installing a new sensor into t
	initializeFusionEngine_t *initializeFusionEngine ;  ///< set sensor fusion structures to initial values
	applyPerturbation_t     *applyPerturbation ;	///< apply step function for testing purposes
	readSensors_t		*readSensors;		///< read all physical sensors
	runFusion_t		*runFusion;		///< run the fusion routines
        conditionSensorReadings_t *conditionSensorReadings;  ///< preprocessing step for sensor fusion
        clearFIFOs_t            *clearFIFOs;            ///< clear sensor FIFOs
	setStatus_t		*setStatus;		///< change status indicator immediately
	setStatus_t		*queueStatus;  	        ///< queue status change for next regular interval
	updateStatus_t		*updateStatus; 		///< status=next status
	updateStatus_t		*testStatus; 		///< increment to next enumerated status value (test only)
        ///@}
} SensorFusionGlobals;

// The following functions are defined in sensor_fusion.c
void initSensorFusionGlobals(
    SensorFusionGlobals *sfg,                           ///< Global data structure pointer
    struct StatusSubsystem *pStatusSubsystem,           ///< Status subsystem pointer
    struct ControlSubsystem *pControlSubsystem          ///< Control subsystem pointer
);
installSensor_t installSensor;
initializeFusionEngine_t initializeFusionEngine ;
/// conditionSensorReadings() transforms raw software FIFO readings into forms that
/// can be consumed by the sensor fusion engine.  This include sample averaging
/// and (in the case of the gyro) integrations, applying hardware abstraction layers,
/// and calibration functions.
/// This function is normally involved via the "sfg." global pointer.
void conditionSensorReadings(
    SensorFusionGlobals *sfg                            ///< Global data structure pointer
);
void clearFIFOs(
    SensorFusionGlobals *sfg                            ///< Global data structure pointer
);
runFusion_t runFusion;
readSensors_t readSensors;
void zeroArray(
    struct StatusSubsystem *pStatus,                    ///< Status subsystem pointer
    void* data,                                         ///< pointer to array to be zeroed
    uint16_t size,                                      ///< data type size = 8, 16 or 32
    uint16_t numElements,                               ///< number of elements to zero out
    uint8_t check                                       ///< true if you would like to verify writes, false otherwise
);
/// \brief conditionSample ensures that we never encounter the maximum negative two's complement
/// value for a 16-bit variable (-32768).
///
/// conditionSample ensures that we never encounter the maximum negative two's complement
/// value for a 16-bit variable (-32768).  This value cannot be negated, because the maximum
/// positive value is +32767.  We need the ability to negate to gaurantee that subsequent
/// HAL operations can be run successfully.
void conditionSample(
    int16_t sample[3]                                   ///< 16-bit register value from triaxial sensor read
);

// The following functions are defined in <hal_board_name>.c.
// Please note that these are board-dependent

/// \brief addToFifo is called from within sensor driver read functions
///
/// addToFifo is called from within sensor driver read functions to transfer new readings into
/// the sensor structure corresponding to accel, gyro or mag.  This function ensures that the software
/// FIFOs are not overrun.
///
/// example usage: if (status==SENSOR_ERROR_NONE) addToFifo((FifoSensor*) &(sfg->Mag), MAG_FIFO_SIZE, sample);
void addToFifo(
    union FifoSensor *sensor,                                 ///< pointer to structure of type AccelSensor, MagSensor or GyroSensor
    uint16_t maxFifoSize,                               ///< the size of the software (not hardware) FIFO
    int16_t sample[3]                                   ///< the sample to add
);
/// \brief Apply the accelerometer Hardware Abstraction Layer
void ApplyAccelHAL(
    struct AccelSensor *Accel                                  ///< pointer to accelerometer logical sensor
);
/// \brief Apply the magnetometer Hardware Abstraction Layer
void ApplyMagHAL(
    struct MagSensor *Mag                                     ///< pointer to magnetometer logical sensor
);
/// \brief Apply the gyroscope Hardware Abstraction Layer
void ApplyGyroHAL(
    struct GyroSensor *Gyro                                    ///< pointer to gyroscope logical sensor
);
/// \brief ApplyPerturbation is a reverse unit-step test function
///
/// The ApplyPerturbation function applies a user-specified step function to
/// prior fusion results which is then "released" in the next fusion cycle.
/// When used in conjuction with the NXP Sensor Fusion Toolbox, this provides
/// a visual indication of the dynamic behavior of the library. ApplyPerturbation()
/// is defined in debug.c.

// The following function is defined in debug.c:
applyPerturbation_t ApplyPerturbation;

#include "matrix.h"  // this is only down here so we can take advantage of _t style typedefs above

#endif // SENSOR_FUSION_TYPES_H
