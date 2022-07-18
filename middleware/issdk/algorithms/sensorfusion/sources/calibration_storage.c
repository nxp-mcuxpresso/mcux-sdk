/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/*! \file calibration_storage.c
    \brief Provides functions to store calibration to NVM

    Users who are not using NXP hardware will need to supply their own drivers
    in place of those defined here.
*/
#include <stdio.h>
#include "sensor_fusion.h"
#include "driver_KSDK_NVM.h"
#include "calibration_storage.h"

void SaveMagCalibrationToNVM(SensorFusionGlobals *sfg)
{
#if F_USING_MAG
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;						// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer (smallest size writeable to flash)
        uint32_t itmp32;

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);
	// default to no magnetic calibration in header
	iNVMBuffer[MAG_NVM_OFFSET] = iNVMBuffer[MAG_NVM_OFFSET + 1] = iNVMBuffer[MAG_NVM_OFFSET + 2] = iNVMBuffer[MAG_NVM_OFFSET + 3] = 0xFF;

	// fill the buffer with the magnetic calibration in bytes 0 to 67 (total 68 bytes)
	// [0-3]: four byte header denoting magnetic calibration present
	itmp32 = 0x12345678;
	pSrc = (uint8 *) &itmp32;
	pDst = iNVMBuffer + MAG_NVM_OFFSET;
	for (i = 0; i < 4; i++)
		*(pDst++) = *(pSrc++);
	// [4-67]: magnetic calibration: 15x float + 1x int32 total 64 bytes
	pSrc = (uint8 *) &(sfg->MagCal);
	for (i = 0; i < 64; i++)
		*(pDst++) = *(pSrc++);

	// write the whole buffer contents to NVM
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);
#endif // if F_USING_MAG
	return;
}

void SaveGyroCalibrationToNVM(SensorFusionGlobals *sfg)
{
#if F_USING_GYRO && (F_9DOF_GBY_KALMAN || F_6DOF_GY_KALMAN)
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;						// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer
        uint32_t itmp32;

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);
	// default to no gyroscope calibration in header
	iNVMBuffer[GYRO_NVM_OFFSET] = iNVMBuffer[GYRO_NVM_OFFSET + 1] = iNVMBuffer[GYRO_NVM_OFFSET + 2] = iNVMBuffer[GYRO_NVM_OFFSET + 3] = 0xFF;

	// define the four header bytes
	// [0-3]: four byte header denoting gyro calibration present
	itmp32 = 0x12345678;
	pSrc = (uint8 *) &itmp32;
	pDst = iNVMBuffer + GYRO_NVM_OFFSET;
	for (i = 0; i < 4; i++)
		*(pDst++) = *(pSrc++);

	// [4-15]: 3 gyro offset floats totalling 12 bytes
#if F_9DOF_GBY_KALMAN
	pSrc = (uint8 *) sfg->SV_9DOF_GBY_KALMAN.fbPl;
#elif F_6DOF_GY_KALMAN
	pSrc = (uint8 *) sfg->SV_6DOF_GY_KALMAN.fbPl;
#endif
	for (i = 0; i < 12; i++)
		*(pDst++) = *(pSrc++);

	// write the buffer contents to NVM
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);
#endif
	return;
}

void SaveAccelCalibrationToNVM(SensorFusionGlobals *sfg)
{
#if F_USING_ACCEL
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;							// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer
        uint32_t itmp32;

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);
	// default to no accelerometer calibration in header
	iNVMBuffer[ACCEL_NVM_OFFSET] = iNVMBuffer[ACCEL_NVM_OFFSET + 1] = iNVMBuffer[ACCEL_NVM_OFFSET + 2] = iNVMBuffer[ACCEL_NVM_OFFSET + 3] = 0xFF;

	// [0-3]: four byte header denoting accelerometer calibration present
	itmp32 = 0x12345678;
	pSrc = (uint8 *) &itmp32;
	pDst = iNVMBuffer + ACCEL_NVM_OFFSET;
	for (i = 0; i < 4; i++)
		*(pDst++) = *(pSrc++);

	// [4-87]: 21 precision accelerometer calibration floats totalling 84 bytes
	pSrc = (uint8 *) &(sfg->AccelCal);
	for (i = 0; i < 84; i++)
		*(pDst++) = *(pSrc++);

	// write the buffer contents to NVM
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);
#endif
	return;
}

void EraseMagCalibrationFromNVM(void)
{
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;						// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);

	// set no magnetic calibration in header
	iNVMBuffer[MAG_NVM_OFFSET] = iNVMBuffer[MAG_NVM_OFFSET + 1] = iNVMBuffer[MAG_NVM_OFFSET + 2] = iNVMBuffer[MAG_NVM_OFFSET + 3] = 0xFF;

	// write the buffer to flash
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);

	return;
}

void EraseGyroCalibrationFromNVM(void)
{
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;							// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);

	// set no gyroscope calibration in header
	iNVMBuffer[GYRO_NVM_OFFSET] = iNVMBuffer[GYRO_NVM_OFFSET + 1] = iNVMBuffer[GYRO_NVM_OFFSET + 2] = iNVMBuffer[GYRO_NVM_OFFSET + 3] = 0xFF;

	// write the buffer to flash
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);

	return;
}

void EraseAccelCalibrationFromNVM(void)
{
	uint8_t *pSrc, *pDst;					// scratch pointers
	int16_t i;							// loop counter
	uint8_t iNVMBuffer[256];				// NVM write buffer

	// copy existing magnetic, gyro and accelerometer calibrations to buffer
	pSrc = (uint8 *) CALIBRATION_NVM_ADDR;
	pDst = iNVMBuffer;
	for (i = 0; i < 256; i++)
		*(pDst++) = *(pSrc++);

	// set no gyroscope calibration in header
	iNVMBuffer[ACCEL_NVM_OFFSET] = iNVMBuffer[ACCEL_NVM_OFFSET + 1] = iNVMBuffer[ACCEL_NVM_OFFSET + 2] = iNVMBuffer[ACCEL_NVM_OFFSET + 3] = 0xFF;

	// write the buffer to flash
	NVM_SetBlockFlash(iNVMBuffer, CALIBRATION_NVM_ADDR, 256);

	return;
}
