/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file output_stream.c
    \brief Implements streaming function for the status subsystem.  See status.h
*/

#include "sensor_fusion.h"  // top level magCal and sensor fusion interfaces
#include "control.h"        // Command/Streaming interface - application specific
#include "debug.h"          // for test purposes
#define MAXPACKETRATEHZ 40
#define RATERESOLUTION 1000

///////////////////////////////////////////////////////////////////////////////////////////////////////

// UART packet drivers
///////////////////////////////////////////////////////////////////////////////////////////////////////
// function appends a variable number of source bytes to a destimation buffer
// for transmission as the bluetooth packet
// bluetooth packets are delimited by inserting the special byte 0x7E at the start
// and end of packets. this function must therefore handle the case of 0x7E appearing
// as general data. this is done here with the substitutions:
// a) replace 0x7E by 0x7D and 0x5E (one byte becomes two)
// b) replace 0x7D by 0x7D and 0x5D (one byte becomes two)
// the inverse mapping must be performed at the application receiving the bluetooth stream: ie:
// replace 0x7D and 0x5E with 0x7E
// replace 0x7D and 0x5D with 0x7D
// NOTE: do not use this function to append the start and end bytes 0x7E to the bluetooth
// buffer. instead add the start and end bytes 0x7E explicitly as in:

// sUARTOutputBuffer[iByteCount++] = 0x7E;
void sBufAppendItem(uint8_t *pDest, uint16_t *pIndex, uint8_t *pSource,
                    uint16_t iBytesToCopy)
{
    uint16_t    i;  // loop counter

    // loop over number of bytes to add to the destination buffer
    for (i = 0; i < iBytesToCopy; i++)
    {
        switch (pSource[i])
        {
            case 0x7E:
                // special case 1: replace 0x7E (start and end byte) with 0x7D and 0x5E
                pDest[(*pIndex)++] = 0x7D;
                pDest[(*pIndex)++] = 0x5E;
                break;

            case 0x7D:
                // special case 2: replace 0x7D with 0x7D and 0x5D
                pDest[(*pIndex)++] = 0x7D;
                pDest[(*pIndex)++] = 0x5D;
                break;

            default:
                // general case, simply add this byte without change
                pDest[(*pIndex)++] = pSource[i];
                break;
        }
    }

    return;
}

// utility function for sending int16_t zeros
void sBufAppendZeros(uint8_t *pDest, uint16_t *pIndex, uint16_t numZeros) {
    int16_t scratch16 = 0;
    uint16_t i;
    for (i=0; i<numZeros; i++) {
        sBufAppendItem(pDest, pIndex, (uint8_t *) &scratch16, 2);
    }
}
// utility function for reading common algorithm parameters
void readCommon( SV_ptr data,
                 Quaternion *fq,
                 int16_t *iPhi,
                 int16_t *iThe,
                 int16_t *iRho,
                 int16_t iOmega[],
                 uint16_t *isystick) {
    *fq = data->fq;
    iOmega[CHX] = (int16_t) (data->fOmega[CHX] * 20.0F);
    iOmega[CHY] = (int16_t) (data->fOmega[CHY] * 20.0F);
    iOmega[CHZ] = (int16_t) (data->fOmega[CHZ] * 20.0F);
    *iPhi = (int16_t) (10.0F * data->fPhi);
    *iThe = (int16_t) (10.0F * data->fThe);
    *iRho = (int16_t) (10.0F * data->fRho);
    *isystick = (uint16_t) (data->systick / 20);
}

// throttle back by fractional multiplier
///    (OVERSAMPLE_RATIO * MAXPACKETRATEHZ) / SENSORFS
uint16_t throttle()
{
    static int32 iThrottle = 0;
    uint8_t skip;
    // The UART (serial over USB and over Bluetooth)
    // is limited to 115kbps which is more than adequate for the 31kbps
    // needed at the default 25Hz output rate but insufficient for 100Hz or
    // 200Hz output rates.  There is little point is providing output data
    // faster than 25Hz video rates but since the UARTs can
    // support a higher rate, the limit is set to MAXPACKETRATEHZ=40Hz.

    // the increment applied to iThrottle is in the range 0 to (RATERESOLUTION - 1)
    iThrottle += ((int32) MAXPACKETRATEHZ * (int32) RATERESOLUTION) / (int32) FUSION_HZ;
    if (iThrottle >= RATERESOLUTION) {
        // update the throttle counter and transmit the packets over UART (USB and Bluetooth)
	iThrottle -= RATERESOLUTION;
        skip = false;
    } else {
        skip = true;
    }
    return(skip);
}

// set packets out over UART_A to shield / Bluetooth module and over UART_B to OpenSDA / USB
//#pragma diag_suppress=Pe177,Pe550       // Suppress "never used" and "set but never used"
void CreateAndSendPackets(SensorFusionGlobals *sfg, uint8_t *sUARTOutputBuffer)
{
    Quaternion      fq;                 // quaternion to be transmitted
    float           ftmp;               // scratch
    static uint32_t iTimeStamp = 0;     // 1MHz time stamp
    uint16_t        iIndex;             // output buffer counter
    int32_t         scratch32;          // scratch int32_t
    int16_t         scratch16;          // scratch int16_t
    int16_t         iPhi,
                    iThe,
                    iRho;               // integer angles to be transmitted
    int16_t         iDelta;             // magnetic inclination angle if available
    int16_t         iOmega[3];          // scaled angular velocity vector
    uint16_t        isystick;           // algorithm systick time
    int16_t         i, j, k;            // general purpose
    uint8_t         tmpuint8_t;         // scratch uint8_t
    uint8_t         flags;              // byte of flags
    uint8_t         AngularVelocityPacketOn,
                    DebugPacketOn,
                    RPCPacketOn;
    int8_t          AccelCalPacketOn;
    static uint8_t  iPacketNumber = 0;  // packet number

    // update the 1MHz time stamp counter expected by the PC GUI (independent of project clock rates)
    iTimeStamp += 1000000 / FUSION_HZ;

#if (MAXPACKETRATEHZ < FUSION_HZ)
    uint8_t  skip_packet = throttle(); // possible UART bandwidth problem
    if (skip_packet) return;  // need to skip packet transmission to avoid UART overrun
#endif

    // cache local copies of control flags so we don't have to keep dereferencing pointers below
    quaternion_type quaternionPacketType;
    quaternionPacketType = sfg->pControlSubsystem->QuaternionPacketType;
    AngularVelocityPacketOn = sfg->pControlSubsystem->AngularVelocityPacketOn;
    DebugPacketOn = sfg->pControlSubsystem->DebugPacketOn;
    RPCPacketOn = sfg->pControlSubsystem->RPCPacketOn;
    AccelCalPacketOn = sfg->pControlSubsystem->AccelCalPacketOn;

    // zero the counter for bytes accumulated into the transmit buffer
    iIndex = 0;

    // ************************************************************************
    // Main type 1: range 0 to 35 = 36 bytes
    // Debug type 2: range 0 to 7 = 8 bytes
    // Angular velocity type 3: range 0 to 13 = 14 bytes
    // Euler angles type 4: range 0 to 13 = 14 bytes
    // Altitude/Temp type 5: range 0 to 13 = 14 bytes
    // Magnetic type 6: range 0 to 16 = 18 bytes
    // Kalman packet 7: range 0 to 47 = 48 bytes
    // Precision Accelerometer packet 8: range 0 to 46 = 47 bytes
    //
    // Total excluding intermittent packet 8 is:
    // 152 bytes vs 256 bytes size of sUARTOutputBuffer
    // at 25Hz, data rate is 25*152 = 3800 bytes/sec = 38.0kbaud = 33% of 115.2kbaud
    // at 40Hz, data rate is 40*152 = 6080 bytes/sec = 60.8kbaud = 53% of 115.2kbaud
    // at 50Hz, data rate is 50*152 = 7600 bytes/sec = 76.0kbaud = 66% of 115.2kbaud
    // ************************************************************************
    // ************************************************************************
    // fixed length packet type 1
    // this packet type is always transmitted
    // total size is 0 to 35 equals 36 bytes
    // ************************************************************************
    // [0]: packet start byte (need a iIndex++ here since not using sBufAppendItem)
    sUARTOutputBuffer[iIndex++] = 0x7E;

    // [1]: packet type 1 byte (iIndex is automatically updated in sBufAppendItem)
    tmpuint8_t = 0x01;
    sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

    // [2]: packet number byte
    sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
    iPacketNumber++;

    // [6-3]: 1MHz time stamp (4 bytes)
    sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iTimeStamp, 4);

    // [12-7]: integer accelerometer data words (scaled to 8192 counts per g for PC GUI)
    // send non-zero data only if the accelerometer sensor is enabled and used by the selected quaternion
    if (sfg->iFlags & F_USING_ACCEL) {
        switch (quaternionPacketType)
        {
            case Q3:
            case Q6MA:
            case Q6AG:
            case Q9:
#if F_USING_ACCEL
                // accelerometer data is used for the selected quaternion so transmit but clip at 4g
                scratch32 = (sfg->Accel.iGc[CHX] * 8192) / sfg->Accel.iCountsPerg;
                if (scratch32 > 32767) scratch32 = 32767;
                if (scratch32 < -32768) scratch32 = -32768;
                scratch16 = (int16_t) (scratch32);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

                scratch32 = (sfg->Accel.iGc[CHY] * 8192) / sfg->Accel.iCountsPerg;
                if (scratch32 > 32767) scratch32 = 32767;
                if (scratch32 < -32768) scratch32 = -32768;
                scratch16 = (int16_t) (scratch32);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

                scratch32 = (sfg->Accel.iGc[CHZ] * 8192) / sfg->Accel.iCountsPerg;
                if (scratch32 > 32767) scratch32 = 32767;
                if (scratch32 < -32768) scratch32 = -32768;
                scratch16 = (int16_t) (scratch32);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;
#endif // F_USING_ACCEL
            case Q3M:
            case Q3G:
            default:
                // accelerometer data is not used in currently selected algorithm so transmit zero
                sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
                break;
        }
     } else {
                // accelerometer structure is not defined so transmit zero
                sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
        }
    // [18-13]: integer calibrated magnetometer data words (already scaled to 10 count per uT for PC GUI)
    // send non-zero data only if the magnetometer sensor is enabled and used by the selected quaternion
    if (sfg->iFlags & F_USING_MAG)
        switch (quaternionPacketType)
        {
            case Q3M:
            case Q6MA:
            case Q9:
#if F_USING_MAG
                // magnetometer data is used for the selected quaternion so transmit
                scratch16 = (int16_t) (sfg->Mag.iBc[CHX] * 10) / (sfg->Mag.iCountsPeruT);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) ((sfg->Mag.iBc[CHY] * 10) / sfg->Mag.iCountsPeruT);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) ((sfg->Mag.iBc[CHZ] * 10) / sfg->Mag.iCountsPeruT);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;
#endif
            // magnetometer data is not used in currently selected algorithm so transmit zero
            case Q3:
            case Q3G:
            case Q6AG:
            default:
                sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
                break;
        }
    else
    {
        // magnetometer structure is not defined so transmit zero
        sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
    }

    // [24-19]: uncalibrated gyro data words (scaled to 20 counts per deg/s for PC GUI)
    // send non-zero data only if the gyro sensor is enabled and used by the selected quaternion
    if (sfg->iFlags & F_USING_GYRO)
    {
        switch (quaternionPacketType)
        {
            case Q3G:
            case Q6AG:
#if F_USING_GYRO
        case Q9:

              // gyro data is used for the selected quaternion so transmit
                scratch16 = (int16_t) ((sfg->Gyro.iYs[CHX] * 20) / sfg->Gyro.iCountsPerDegPerSec);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) ((sfg->Gyro.iYs[CHY] * 20) / sfg->Gyro.iCountsPerDegPerSec);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) ((sfg->Gyro.iYs[CHZ] * 20) / sfg->Gyro.iCountsPerDegPerSec);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;
#endif
            case Q3:
            case Q3M:
            case Q6MA:
            default:
                // gyro data is not used in currently selected algorithm so transmit zero
                sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
                break;
        }
    }
    else
    {
        // gyro structure is not defined so transmit zero
        sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
    }

    // initialize default quaternion, flags byte, angular velocity and orientation
    fq.q0 = 1.0F;
    fq.q1 = fq.q2 = fq.q3 = 0.0F;
    flags = 0x00;
    iOmega[CHX] = iOmega[CHY] = iOmega[CHZ] = 0;
    iPhi = iThe = iRho = iDelta = 0;
    isystick = 0;

    // flags byte 33: quaternion type in least significant nibble
    // Q3:   coordinate nibble, 1
    // Q3M:	 coordinate nibble, 6
    // Q3G:	 coordinate nibble, 3
    // Q6MA: coordinate nibble, 2
    // Q6AG: coordinate nibble, 4
    // Q9:   coordinate nibble, 8
    // flags byte 33: coordinate in most significant nibble
    // Aerospace/NED:	0, quaternion nibble
    // Android:	  		1, quaternion nibble
    // Windows 8: 		2, quaternion nibble
    // set the quaternion, flags, angular velocity and Euler angles
    switch (quaternionPacketType)
    {
#if F_3DOF_G_BASIC
        case Q3:
            if (sfg->iFlags & F_3DOF_G_BASIC)
            {
                flags |= 0x01;
                readCommon((SV_ptr)&sfg->SV_3DOF_G_BASIC, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
#if F_3DOF_B_BASIC
        case Q3M:
            if (sfg->iFlags & F_3DOF_B_BASIC)
            {
                flags |= 0x06;
                readCommon((SV_ptr)&sfg->SV_3DOF_B_BASIC, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
#if F_3DOF_Y_BASIC
        case Q3G:
            if (sfg->iFlags & F_3DOF_Y_BASIC)
            {
                flags |= 0x03;
                readCommon((SV_ptr)&sfg->SV_3DOF_Y_BASIC, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
#if F_6DOF_GB_BASIC
        case Q6MA:
            if (sfg->iFlags & F_6DOF_GB_BASIC)
            {
                flags |= 0x02;
                iDelta = (int16_t) (10.0F * sfg->SV_6DOF_GB_BASIC.fLPDelta);
                readCommon((SV_ptr)&sfg->SV_6DOF_GB_BASIC, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
#if F_6DOF_GY_KALMAN
        case Q6AG:
            if (sfg->iFlags & F_6DOF_GY_KALMAN)
            {
                flags |= 0x04;
                readCommon((SV_ptr)&sfg->SV_6DOF_GY_KALMAN, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
#if F_9DOF_GBY_KALMAN
        case Q9:
            if (sfg->iFlags & F_9DOF_GBY_KALMAN)
             {
                flags |= 0x08;
                iDelta = (int16_t) (10.0F * sfg->SV_9DOF_GBY_KALMAN.fDeltaPl);
                readCommon((SV_ptr)&sfg->SV_9DOF_GBY_KALMAN, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
            }
            break;
#endif
        default:
            // use the default data already initialized
            break;
    }

    // [32-25]: scale the quaternion (30K = 1.0F) and add to the buffer
    scratch16 = (int16_t) (fq.q0 * 30000.0F);
    sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q1 * 30000.0F);
    sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q2 * 30000.0F);
    sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q3 * 30000.0F);
    sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

    // set the coordinate system bits in flags from default NED (00)
#if THISCOORDSYSTEM == ANDROID
    // set the Android flag bits
    flags |= 0x10;
#elif THISCOORDSYSTEM == WIN8
    // set the Win8 flag bits
    flags |= 0x20;
#endif // THISCOORDSYSTEM

    // [33]: add the flags byte to the buffer
    sBufAppendItem(sUARTOutputBuffer, &iIndex, &flags, 1);

    // [34]: add the shield (bits 7-5) and Kinetis (bits 4-0) byte
    tmpuint8_t = ((THIS_SHIELD & 0x07) << 5) | (THIS_BOARD & 0x1F);
    sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

    // [35]: add the tail byte for the standard packet type 1
    sUARTOutputBuffer[iIndex++] = 0x7E;

    // ************************************************************************
    // Variable length debug packet type 2
    // total size is 0 to 7 equals 8 bytes
    // ************************************************************************
    if (DebugPacketOn)
    {
        // [0]: packet start byte
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // [1]: packet type 2 byte
        tmpuint8_t = 0x02;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

        // [2]: packet number byte
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
        iPacketNumber++;

        // [4-3] software version number
        scratch16 = THISBUILD;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [6-5] systick count / 20
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &isystick, 2);

        // [7 in practice but can be variable]: add the tail byte for the debug packet type 2
        sUARTOutputBuffer[iIndex++] = 0x7E;
    }

    // ************************************************************************
    // Angular Velocity packet type 3
    // total bytes for packet type 2 is range 0 to 13 = 14 bytes
    // ************************************************************************
    if (AngularVelocityPacketOn)
    {
        // [0]: packet start byte
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // [1]: packet type 3 byte (angular velocity)
        tmpuint8_t = 0x03;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

        // [2]: packet number byte
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
        iPacketNumber++;

        // [6-3]: time stamp (4 bytes)
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iTimeStamp, 4);

        // [12-7]: add the scaled angular velocity vector to the output buffer
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iOmega[CHX], 2);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iOmega[CHY], 2);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iOmega[CHZ], 2);

        // [13]: add the tail byte for the angular velocity packet type 3
        sUARTOutputBuffer[iIndex++] = 0x7E;
    }

    // ************************************************************************
    // Roll, Pitch, Compass Euler angles packet type 4
    // total bytes for packet type 4 is range 0 to 13 = 14 bytes
    // ************************************************************************
    if (RPCPacketOn)
    {
        // [0]: packet start byte
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // [1]: packet type 4 byte (Euler angles)
        tmpuint8_t = 0x04;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

        // [2]: packet number byte
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
        iPacketNumber++;

        // [6-3]: time stamp (4 bytes)
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iTimeStamp, 4);

        // [12-7]: add the angles (resolution 0.1 deg per count) to the transmit buffer
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iPhi, 2);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iThe, 2);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iRho, 2);

        // [13]: add the tail byte for the roll, pitch, compass angle packet type 4
        sUARTOutputBuffer[iIndex++] = 0x7E;
    }

    // ************************************************************************
    // Altitude / Temperature packet type 5
    // total bytes for packet type 5 is range 0 to 13 = 14 bytes
    // ************************************************************************
#if F_USING_PRESSURE
    if (sfg->iFlags & F_1DOF_P_BASIC)
    {
        if (sfg->pControlSubsystem->AltPacketOn && sfg->Pressure.iWhoAmI)
        {
            // [0]: packet start byte
            sUARTOutputBuffer[iIndex++] = 0x7E;

            // [1]: packet type 5 byte
            tmpuint8_t = 0x05;
            sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

            // [2]: packet number byte
            sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
            iPacketNumber++;

            // [6-3]: time stamp (4 bytes)
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &iTimeStamp,
                           4);

            // [10-7]: altitude (4 bytes, metres times 1000)
            scratch32 = (int32_t) (sfg->SV_1DOF_P_BASIC.fLPH * 1000.0F);
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch32, 4);

            // [12-11]: temperature (2 bytes, deg C times 100)
            scratch16 = (int16_t) (sfg->SV_1DOF_P_BASIC.fLPT * 100.0F);
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

            // [13]: add the tail byte for the altitude / temperature packet type 5
            sUARTOutputBuffer[iIndex++] = 0x7E;
        }
    }
#endif

    // ************************************************************************
    // magnetic buffer packet type 6
    // currently total size is 0 to 17 equals 18 bytes
    // this packet is only transmitted if a magnetic algorithm is computed
    // ************************************************************************
#if F_USING_MAG
    static int16_t  MagneticPacketID = 0;   // magnetic packet number
    if (sfg->iFlags & F_USING_MAG)
    {
        // [0]: packet start byte
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // [1]: packet type 6 byte
        tmpuint8_t = 0x06;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

        // [2]: packet number byte
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
        iPacketNumber++;

        // [4-3]: number of active measurements in the magnetic buffer
        sBufAppendItem(sUARTOutputBuffer, &iIndex,
                       (uint8_t *) &(sfg->MagBuffer.iMagBufferCount), 2);

        // [6-5]: fit error (%) with resolution 0.01%
        if (sfg->MagCal.fFitErrorpc > 327.67F)
            scratch16 = 32767;
        else
            scratch16 = (int16_t) (sfg->MagCal.fFitErrorpc * 100.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [8-7]: geomagnetic field strength with resolution 0.1uT
        scratch16 = (int16_t) (sfg->MagCal.fB * 10.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // always calculate magnetic buffer row and column (low overhead and saves warnings)
        k = MagneticPacketID - 10;
        j = k / MAGBUFFSIZEX;
        i = k - j * MAGBUFFSIZEX;

        // [10-9]: int16_t: ID of magnetic variable to be transmitted
        // ID 0 to 4 inclusive are magnetic calibration coefficients
        // ID 5 to 9 inclusive are for future expansion
        // ID 10 to (MAGBUFFSIZEX=12) * (MAGBUFFSIZEY=24)-1 or 10 to 10+288-1 are magnetic buffer elements
        // where the convention is used that a negative value indicates empty buffer element (index=-1)
        if ((MagneticPacketID >= 10) && (sfg->MagBuffer.index[i][j] == -1))
        {
            // use negative ID to indicate inactive magnetic buffer element
            scratch16 = -MagneticPacketID;
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        }
        else
        {
            // use positive ID unchanged for variable or active magnetic buffer entry
            scratch16 = MagneticPacketID;
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        }

        // [12-11]: int16_t: variable 1 to be transmitted this iteration
        // [14-13]: int16_t: variable 2 to be transmitted this iteration
        // [16-15]: int16_t: variable 3 to be transmitted this iteration
        switch (MagneticPacketID)
        {
            case 0:
                // item 1: currently unused
                scratch16 = 0;
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

                // item 2: currently unused
                scratch16 = 0;
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

                // item 3: magnetic inclination angle with resolution 0.1 deg
                scratch16 = iDelta;
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;

            case 1:
                // items 1 to 3: hard iron components range -3276uT to +3276uT encoded with 0.1uT resolution
                scratch16 = (int16_t) (sfg->MagCal.fV[CHX] * 10.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.fV[CHY] * 10.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.fV[CHZ] * 10.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;

            case 2:
                // items 1 to 3: diagonal soft iron range -32. to +32. encoded with 0.001 resolution
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHX][CHX] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHY][CHY] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHZ][CHZ] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;

            case 3:
                // items 1 to 3: off-diagonal soft iron range -32. to +32. encoded with 0.001 resolution
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHX][CHY] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHX][CHZ] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                scratch16 = (int16_t) (sfg->MagCal.finvW[CHY][CHZ] * 1000.0F);
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
                break;

            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                // cases 4 to 9 inclusive are for future expansion so transmit zeroes for now
                sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
                break;

            default:
                // 10 and upwards: this handles the magnetic buffer elements
                sBufAppendItem(sUARTOutputBuffer, &iIndex,
                               (uint8_t *) &(sfg->MagBuffer.iBs[CHX][i][j]), 2);
                sBufAppendItem(sUARTOutputBuffer, &iIndex,
                               (uint8_t *) &(sfg->MagBuffer.iBs[CHY][i][j]), 2);
                sBufAppendItem(sUARTOutputBuffer, &iIndex,
                               (uint8_t *) &(sfg->MagBuffer.iBs[CHZ][i][j]), 2);
                break;
        }

        // wrap the variable ID back to zero if necessary
        MagneticPacketID++;
        if (MagneticPacketID >= (10 + MAGBUFFSIZEX * MAGBUFFSIZEY))
            MagneticPacketID = 0;

        // [17]: add the tail byte for the magnetic packet type 6
        sUARTOutputBuffer[iIndex++] = 0x7E;
    }
#endif

    // *******************************************************************************
    // Kalman filter packet type 7
    // total bytes for packet type 7 is range 0 to 41 inclusive = 42 bytes
    // this packet is only transmitted when a Kalman algorithm is computed
    // and then non-zero data is transmitted only when a Kalman quaternion is selected
    // *******************************************************************************
    bool kalman = false;
#if F_6DOF_GY_KALMAN
    uint8_t six_axis_kalman = (sfg->iFlags & F_6DOF_GY_KALMAN) && (quaternionPacketType == Q6AG);
    kalman = six_axis_kalman;
#endif
#if F_9DOF_GBY_KALMAN
    uint8_t nine_axis_kalman = (sfg->iFlags & F_9DOF_GBY_KALMAN) && (quaternionPacketType == Q9);
    kalman = kalman | nine_axis_kalman;
#endif
#if F_6DOF_GY_KALMAN || F_9DOF_GBY_KALMAN
    if (kalman)
    {
        if ((quaternionPacketType == Q6AG) || (quaternionPacketType == Q9))
        {
            // [0]: packet start byte
            sUARTOutputBuffer[iIndex++] = 0x7E;

            // [1]: packet type 7 byte
            tmpuint8_t = 0x07;
            sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

            // [2]: packet number byte
            sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
            iPacketNumber++;

            // [4-3]: fzgErr[CHX] resolution scaled by 30000
            // [6-5]: fzgErr[CHY] resolution scaled by 30000
            // [8-7]: fzgErr[CHZ] resolution scaled by 30000
            for (i = CHX; i <= CHZ; i++)
            {
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    scratch16 = (int16_t) (sfg->SV_6DOF_GY_KALMAN.fZErr[i] * 30000.0F);
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fZErr[i] * 30000.0F);
#endif
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16,2);
            }

            // [10-9]: fgErrPl[CHX] resolution scaled by 30000
            // [12-11]: fgErrPl[CHY] resolution scaled by 30000
            // [14-13]: fgErrPl[CHZ] resolution scaled by 30000
            for (i = CHX; i <= CHZ; i++)
            {
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    scratch16 = (int16_t) (sfg->SV_6DOF_GY_KALMAN.fqgErrPl[i] * 30000.0F);
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fqgErrPl[i] * 30000.0F);
#endif
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16,2);
            }

            // [16-15]: fzmErr[CHX] resolution scaled by 30000
            // [18-17]: fzmErr[CHY] resolution scaled by 30000
            // [20-19]: fzmErr[CHZ] resolution scaled by 30000
            for (i = CHX; i <= CHZ; i++)
            {
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    scratch16 = 0;
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fZErr[i + 3] * 30000.0F);
#endif
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            }

            // [22-21]: fmErrPl[CHX] resolution scaled by 30000
            // [24-23]: fmErrPl[CHY] resolution scaled by 30000
            // [26-25]: fmErrPl[CHZ] resolution scaled by 30000
            for (i = CHX; i <= CHZ; i++)
            {
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    scratch16 = 0;
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fqmErrPl[i] * 30000.0F);
#endif
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            }

            // [28-27]: fbPl[CHX] resolution 0.001 deg/sec
            // [30-29]: fbPl[CHY] resolution 0.001 deg/sec
            // [32-31]: fbPl[CHZ] resolution 0.001 deg/sec
            for (i = CHX; i <= CHZ; i++)
            {
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    scratch16 = (int16_t) (sfg->SV_6DOF_GY_KALMAN.fbPl[i] * 1000.0F);
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fbPl[i] * 1000.0F);
#endif
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            }

            // [34-33]: fDeltaPl resolution 0.01deg
            scratch16 = 0;
#if F_9DOF_GBY_KALMAN
            if (nine_axis_kalman)       scratch16 = (int16_t) (sfg->SV_9DOF_GBY_KALMAN.fDeltaPl * 100.0F);
#endif
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

            // [36-35]: fAccGl[CHX] resolution 1/8192 g
            // [38-37]: fAccGl[CHY] resolution 1/8192 g
            // [40-39]: fAccGl[CHZ] resolution 1/8192 g
            for (i = CHX; i <= CHZ; i++)
            {
                // default to zero data
                ftmp = 0.0F;
#if F_6DOF_GY_KALMAN
                if (six_axis_kalman)    ftmp = sfg->SV_6DOF_GY_KALMAN.fAccGl[i] * 8192.0F;
#endif
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   ftmp = sfg->SV_9DOF_GBY_KALMAN.fAccGl[i] * 8192.0F;
#endif

                // check for clipping
                if (ftmp > 32767.0F)            scratch16 = 32767;
                else if (ftmp < -32768.0F)      scratch16 = -32768;
                else                            scratch16 = (int16_t) ftmp;
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            }

            // [42-41]: fDisGl[CHX] resolution 0.01m
            // [44-43]: fDisGl[CHY] resolution 0.01m
            // [46-45]: fDisGl[CHZ] resolution 0.01m
            for (i = CHX; i <= CHZ; i++)
            {
                // default to zero data
                ftmp = 0.0F;
#if F_9DOF_GBY_KALMAN
                if (nine_axis_kalman)   ftmp = sfg->SV_9DOF_GBY_KALMAN.fDisGl[i] * 100.0F;
#endif

                // check for clipping
                if (ftmp > 32767.0F)            scratch16 = 32767;
                else if (ftmp < -32768.0F)      scratch16 = -32768;
                else                            scratch16 = (int16_t) ftmp;
                sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            }

            // [47]: add the tail byte for the Kalman packet type 7
            sUARTOutputBuffer[iIndex++] = 0x7E;
        }
    }   // end of check for Kalman packet
#endif
#if F_USING_ACCEL
    // *************************************************************************
    // fixed length packet type 8 transmitted whenever a precision accelerometer
    // measurement has been stored.
    // total size is 0 to 40 equals 41 bytes
    // *************************************************************************
    // check to see which packet (if any) is to be transmitted
    if (AccelCalPacketOn != -1)
    {
        // [0]: packet start byte (need a iIndex++ here since not using sBufAppendItem)
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // [1]: packet type 8 byte (iIndex is automatically updated in sBufAppendItem)
        tmpuint8_t = 0x08;
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

        // [2]: packet number byte
        sBufAppendItem(sUARTOutputBuffer, &iIndex, &iPacketNumber, 1);
        iPacketNumber++;

        // [3]: AccelCalPacketOn in range 0-11 denotes stored location and MAXORIENTATIONS denotes transmit
        // precision accelerometer calibration on power on before any measurements have been obtained.
        sBufAppendItem(sUARTOutputBuffer, &iIndex,
                       (uint8_t *) &(AccelCalPacketOn), 1);

        // [9-4]: stored accelerometer measurement fGs (scaled to 8192 counts per g)
        if ((AccelCalPacketOn >= 0) &&
            (AccelCalPacketOn < MAX_ACCEL_CAL_ORIENTATIONS))
        {
            scratch16 = (int16_t) (sfg->AccelBuffer.fGsStored[AccelCalPacketOn][CHX] * 8192.0F);
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            scratch16 = (int16_t) (sfg->AccelBuffer.fGsStored[AccelCalPacketOn][CHY] * 8192.0F);
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
            scratch16 = (int16_t) (sfg->AccelBuffer.fGsStored[AccelCalPacketOn][CHZ] * 8192.0F);
            sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        }
        else
        {
            // transmit zero bytes since this is the power on or reset transmission of the precision calibration
            sBufAppendZeros(sUARTOutputBuffer, &iIndex, 3);
        }

        // [15-10]: precision accelerometer offset vector fV (g scaled by 32768.0)
        scratch16 = (int16_t) (sfg->AccelCal.fV[CHX] * 32768.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fV[CHY] * 32768.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fV[CHZ] * 32768.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [21-16]: precision accelerometer inverse gain matrix diagonal finvW - 1.0 (scaled by 10000.0)
        scratch16 = (int16_t) ((sfg->AccelCal.finvW[CHX][CHX] - 1.0F) * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->AccelCal.finvW[CHY][CHY] - 1.0F) * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->AccelCal.finvW[CHZ][CHZ] - 1.0F) * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [27-22]: precision accelerometer inverse gain matrix off-diagonal finvW (scaled by 10000)
        scratch16 = (int16_t) (sfg->AccelCal.finvW[CHX][CHY] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.finvW[CHX][CHZ] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.finvW[CHY][CHZ] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [33-28]: precision accelerometer rotation matrix diagonal fR0 (scaled by 10000)
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHX][CHX] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHY][CHY] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHZ][CHZ] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [45-34]: precision accelerometer inverse rotation matrix off-diagonal fR0 (scaled by 10000)
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHX][CHY] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHX][CHZ] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHY][CHX] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHY][CHZ] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHZ][CHX] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) (sfg->AccelCal.fR0[CHZ][CHY] * 10000.0F);
        sBufAppendItem(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        // [46]: add the tail byte for the packet type 8
        sUARTOutputBuffer[iIndex++] = 0x7E;

        // disable future packets of this type until a new measurement has been obtained
        sfg->pControlSubsystem->AccelCalPacketOn = -1;
    }
#endif  // F_USING_ACCEL
    // ********************************************************************************
    // all packets have now been constructed in the output buffer so now transmit.
    // The final iIndex++ gives the number of bytes to transmit which is one more than
    // the last index in the buffer. this function is non-blocking
    // ********************************************************************************
    sfg->pControlSubsystem->write(sfg->pControlSubsystem, sUARTOutputBuffer, iIndex);
    return;
}
