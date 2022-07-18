/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file control.h
    \brief Defines control sub-system

   Each sensor fusion application will probably have its own set of functions
   to control the fusion process and report results.  This file defines the
   programming interface that should be followed in order for the fusion functions
   to operate correctly out of the box.  The actual command interpreter is
   defined separately in DecodeCommandBytes.c.  The output streaming function
   is defined in output_stream.c. Via these three files, the NXP Sensor Fusion
   Library provides a default set of functions which are compatible with the
   Sensor Fusion Toolbox.  Use of the toolbox is highly recommended at least
   during initial development, as it provides many useful debug features.
   The NXP development team will typically require use of the toolbox as a
   pre-requisite for providing software support.
*/

// Requires sensor_fusion.h to occur first in the #include stackup
#ifndef SENSOR_FUSION_CONTROL_H_
#define SENSOR_FUSION_CONTROL_H_

/// @name Control Port Function Type Definitions
/// The "write" and "stream" commands provide two control functions visible at the main()
/// level.  These typedefs define the structure of those two calls.
///@{
typedef int8_t (writePort_t) (struct ControlSubsystem *pComm, uint8_t buffer[], uint16_t nbytes);
typedef void (streamData_t)(SensorFusionGlobals *sfg, uint8_t *sUARTOutputBuffer);
///@}

/// \brief he ControlSubsystem encapsulates command and data streaming functions.
///
/// The ControlSubsystem encapsulates command and data streaming functions
/// for the library.  A C++-like typedef structure which includes executable methods
/// for the subsystem is defined here.
typedef struct ControlSubsystem {
	quaternion_type DefaultQuaternionPacketType;	///< default quaternion transmitted at power on
	volatile quaternion_type QuaternionPacketType;	///< quaternion type transmitted over UART
	volatile uint8_t AngularVelocityPacketOn;	///< flag to enable angular velocity packet
	volatile uint8_t DebugPacketOn;			///< flag to enable debug packet
	volatile uint8_t RPCPacketOn;			///< flag to enable roll, pitch, compass packet
	volatile uint8_t AltPacketOn;			///< flag to enable altitude packet
	volatile int8_t  AccelCalPacketOn;              ///< variable used to coordinate accelerometer calibration
	writePort_t      *write;                        ///< low level function to write a char buffer to the serial stream
	streamData_t	 *stream;                       ///< function to create packets for serial stream
} ControlSubsystem;

int8_t initializeControlPort(ControlSubsystem *pComm);  ///< Call this once to initialize structures, ports, etc.

// Located in output_stream.c:
/// Called once per fusion cycle to stream information required by the NXP Sensor Fusion Toolbox.
/// Packet protocols are defined in the NXP Sensor Fusion for Kinetis Product Development Kit User Guide.
void CreateAndSendPackets(SensorFusionGlobals *sfg, uint8_t *sUARTOutputBuffer);

// Located in DecodeCommandBytes.c:
/// This function is responsible for decoding commands sent by the NXP Sensor Fusion Toolbox and setting
/// the appropriate flags in the ControlSubsystem data structure.
/// Packet protocols are defined in the NXP Sensor Fusion for Kinetis Product Development Kit User Guide.
void DecodeCommandBytes(SensorFusionGlobals *sfg, char iCommandBuffer[], uint8 sUART_InputBuffer[], uint16 nbytes);

/// Used to initialize the Blue Radios Bluetooth module found on the
/// FRDM-FXS-MULT2-B sensor shield from NXP.
void BlueRadios_Init(void);

/// Utility function used to place data in output buffer about to be transmitted via UART
void sBufAppendItem(uint8_t *pDest, uint16_t *pIndex, uint8_t *pSource, uint16_t iBytesToCopy);

// externals
extern uint8_t sUARTOutputBuffer[256];                  ///< main output buffer defined in control.c

#endif /* SENSOR_FUSION_CONTROL_H_ */
