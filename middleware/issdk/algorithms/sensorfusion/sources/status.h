/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SENSOR_FUSION_STATUS_H_
#define SENSOR_FUSION_STATUS_H_


/*! \file status.h
    \brief Application-specific status subsystem

    Applications may change how they choose to display status information.
    The default implementation here uses LEDs on NXP Freedom boards.
    You may swap out implementations as long as the "Required" methods and states
    are retained.
*/
/// StatusSubsystem() provides an object-like interface for communicating status to the user
typedef struct StatusSubsystem {
	// Required internal states
	fusion_status_t		previous;       ///< Previous status state - fusion_status_t is defined in sensor_fusion.h
	fusion_status_t		status;         ///< Current status
	fusion_status_t		next;           ///< Pending status change
	// Required methods
	ssSetStatus_t           *set;	        ///< change status immediately - no delay
	ssSetStatus_t           *queue;         ///< queue status change for next regular interval
	ssUpdateStatus_t        *update;        ///< make pending status active/visible
	ssUpdateStatus_t        *test ;         ///< unit test which simply increments to next state
	// application-specific internal variables
	uint8_t toggle;                         ///< This implementation can change LED color and have either solid/toggle
} StatusSubsystem ;

/// initializeStatusSubsystem() should be called once at startup to initialize the
/// data structure and to put hardware into the proper state for communicating status.
void initializeStatusSubsystem (
  StatusSubsystem *pStatus                      ///< pointer to the status subsystem
);

#endif /* SENSOR_FUSION_STATUS_H_ */
