/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file magnetic.c
    \brief Lower level magnetic calibration interface

    Many developers can utilize the NXP Sensor Fusion Library without ever
    making any adjustment to the lower level magnetic calibration functions
    defined in this file.
*/

#include "sensor_fusion.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"

#if F_USING_MAG
// function resets the magnetometer buffer and magnetic calibration
void fInitializeMagCalibration(struct MagCalibration *pthisMagCal,
                               struct MagBuffer *pthisMagBuffer)
{
    float   *pFlash;    // pointer into flash memory
    int8    i,
            j;          // loop counters

    // set magnetic buffer index to invalid value -1 to denote no measurement present
    pthisMagBuffer->iMagBufferCount = 0;
    for (i = 0; i < MAGBUFFSIZEX; i++)
        for (j = 0; j < MAGBUFFSIZEY; j++) pthisMagBuffer->index[i][j] = -1;

    // initialize the array of (MAGBUFFSIZEX - 1) elements of 100 * tangents used for buffer indexing
    // entries cover the range 100 * tan(-PI/2 + PI/MAGBUFFSIZEX), 100 * tan(-PI/2 + 2*PI/MAGBUFFSIZEX) to
    // 100 * tan(-PI/2 + (MAGBUFFSIZEX - 1) * PI/MAGBUFFSIZEX).
    // for MAGBUFFSIZEX=12, the entries range in value from -373 to +373
    for (i = 0; i < (MAGBUFFSIZEX - 1); i++)
        pthisMagBuffer->tanarray[i] = (int16) (100.0F * tanf(PI * (-0.5F + (float) (i + 1) / MAGBUFFSIZEX)));

    // check to see if the stored magnetic calibration has been erased
    // the standard value for erased flash is 0xFF in each byte but for portability check against 0x12345678
#ifndef SIMULATION

    pFlash = (float *) (CALIBRATION_NVM_ADDR + MAG_NVM_OFFSET);
    if (*((uint32 *) pFlash++) == 0x12345678)
    {
        // a magnetic calibration is present in flash
        // copy magnetic calibration elements (15x float + 1x int32 total 64 bytes) from flash to RAM
        for (i = CHX; i <= CHZ; i++) pthisMagCal->fV[i] = *(pFlash++);
        for (i = CHX; i <= CHZ; i++)
            for (j = CHX; j <= CHZ; j++)
                pthisMagCal->finvW[i][j] = *(pFlash++);
        pthisMagCal->fB = *(pFlash++);
        pthisMagCal->fBSq = *(pFlash++);
        pthisMagCal->fFitErrorpc = *(pFlash++);
        pthisMagCal->iValidMagCal = *((int32 *) pFlash);
    }
    else
    {
#endif
        // flash has been erased and no magnetic calibration is present
        // initialize the magnetic calibration in RAM to null default
        pthisMagCal->fV[CHX] = pthisMagCal->fV[CHY] = pthisMagCal->fV[CHZ] = 0.0F;
        f3x3matrixAeqI(pthisMagCal->finvW);
        pthisMagCal->fB = DEFAULTB;
        pthisMagCal->fBSq = DEFAULTB * DEFAULTB;
        pthisMagCal->fFitErrorpc = 100.0F;
        pthisMagCal->iValidMagCal = 0;
#ifndef SIMULATION
    }
#endif

    // initialize remaining elements of the magnetic calibration structure
    pthisMagCal->iCalInProgress = 0;
    pthisMagCal->iInitiateMagCal = 0;
    pthisMagCal->iNewCalibrationAvailable = 0;
    pthisMagCal->iMagBufferReadOnly = false;
    pthisMagCal->i4ElementSolverTried = false;
    pthisMagCal->i7ElementSolverTried = false;
    pthisMagCal->i10ElementSolverTried = false;

    return;
}

// function updates the magnetic measurement buffer with most recent magnetic data (typically 200Hz)

// the uncalibrated measurements iBs are stored in the buffer but the calibrated measurements iBc are used for indexing.
void iUpdateMagBuffer(struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag,
                      int32 loopcounter)
{
    // local variables
    int32   idelta;     // absolute vector distance
    int32   i;          // counter
    int16   itanj,
            itank;      // indexing accelerometer ratios
    int8    j,
            k,
            l,
            m;          // counters
    int8    itooclose;  // flag denoting measurement is too close to existing ones

    // calculate the magnetometer buffer bins from the tangent ratios
    if (pthisMag->iBc[CHZ] == 0) return;
    itanj = (100 * (int32) pthisMag->iBc[CHX]) / ((int32) pthisMag->iBc[CHZ]);
    itank = (100 * (int32) pthisMag->iBc[CHY]) / ((int32) pthisMag->iBc[CHZ]);

    // map tangent ratios to bins j and k using equal angle bins: C guarantees left to right execution of the test
    // and add an offset of MAGBUFFSIZEX bins to k to mimic atan2 on this ratio
    // j will vary from 0 to MAGBUFFSIZEX - 1 and k from 0 to 2 * MAGBUFFSIZEX - 1
    j = k = 0;
    while ((j < (MAGBUFFSIZEX - 1) && (itanj >= pthisMagBuffer->tanarray[j])))
        j++;
    while ((k < (MAGBUFFSIZEX - 1) && (itank >= pthisMagBuffer->tanarray[k])))
        k++;
    if (pthisMag->iBc[CHX] < 0) k += MAGBUFFSIZEX;

    // case 1: buffer is full and this bin has a measurement: over-write without increasing number of measurements
    // this is the most common option at run time
    if ((pthisMagBuffer->iMagBufferCount == MAXMEASUREMENTS) &&
        (pthisMagBuffer->index[j][k] != -1))
    {
        // store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
        for (i = CHX; i <= CHZ; i++)
        {
            pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
        }

        pthisMagBuffer->index[j][k] = loopcounter;
        return;
    }                   // end case 1

    // case 2: the buffer is full and this bin does not have a measurement: store and retire the oldest
    // this is the second most common option at run time
    if ((pthisMagBuffer->iMagBufferCount == MAXMEASUREMENTS) &&
        (pthisMagBuffer->index[j][k] == -1))
    {
        // store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
        for (i = CHX; i <= CHZ; i++)
        {
            pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
        }

        pthisMagBuffer->index[j][k] = loopcounter;

        // set l and m to the oldest active entry and disable it
        i = loopcounter;
        l = m = 0;      // to avoid compiler complaint
        for (j = 0; j < MAGBUFFSIZEX; j++)
        {
            for (k = 0; k < MAGBUFFSIZEY; k++)
            {
                // check if the time stamp is older than the oldest found so far (normally fails this test)
                if (pthisMagBuffer->index[j][k] < i)
                {
                    // check if this bin is active (normally passes this test)
                    if (pthisMagBuffer->index[j][k] != -1)
                    {
                        // set l and m to the indices of the oldest entry found so far
                        l = j;
                        m = k;

                        // set i to the time stamp of the oldest entry found so far
                        i = pthisMagBuffer->index[l][m];
                    }   // end of test for active
                }       // end of test for older
            }           // end of loop over k
        }               // end of loop over j

        // deactivate the oldest measurement (no need to zero the measurement data)
        pthisMagBuffer->index[l][m] = -1;
        return;
    }                   // end case 2

    // case 3: buffer is not full and this bin is empty: store and increment number of measurements
    if ((pthisMagBuffer->iMagBufferCount < MAXMEASUREMENTS) &&
        (pthisMagBuffer->index[j][k] == -1))
    {
        // store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
        for (i = CHX; i <= CHZ; i++)
        {
            pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
        }

        pthisMagBuffer->index[j][k] = loopcounter;
        (pthisMagBuffer->iMagBufferCount)++;
        return;
    }                   // end case 3

    // case 4: buffer is not full and this bin has a measurement: over-write if close or try to slot in
    // elsewhere if not close to the other measurements so as to create a mesh at power up
    if ((pthisMagBuffer->iMagBufferCount < MAXMEASUREMENTS) &&
        (pthisMagBuffer->index[j][k] != -1))
    {
        // calculate the vector difference between current measurement and the buffer entry
        idelta = 0;
        for (i = CHX; i <= CHZ; i++)
        {
            idelta += abs((int32) pthisMag->iBs[i] -
                          (int32) pthisMagBuffer->iBs[i][j][k]);
        }

        // check to see if the current reading is close to this existing magnetic buffer entry
        if (idelta < MESHDELTACOUNTS)
        {
            // simply over-write the measurement and return
            for (i = CHX; i <= CHZ; i++)
            {
                pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
            }

            pthisMagBuffer->index[j][k] = loopcounter;
        }
        else
        {
            // reset the flag denoting that the current measurement is close to any measurement in the buffer
            itooclose = 0;

            // to avoid compiler warning
            l = m = 0;

            // loop over the buffer j from 0 potentially up to MAGBUFFSIZEX - 1
            j = 0;
            while (!itooclose && (j < MAGBUFFSIZEX))
            {
                // loop over the buffer k from 0 potentially up to MAGBUFFSIZEY - 1
                k = 0;
                while (!itooclose && (k < MAGBUFFSIZEY))
                {
                    // check whether this buffer entry already has a measurement or not
                    if (pthisMagBuffer->index[j][k] != -1)
                    {
                        // calculate the vector difference between current measurement and the buffer entry
                        idelta = 0;
                        for (i = CHX; i <= CHZ; i++)
                        {
                            idelta += abs((int32) pthisMag->iBs[i] -
                                          (int32) pthisMagBuffer->iBs[i][j][k]);
                        }

                        // check to see if the current reading is close to this existing magnetic buffer entry
                        if (idelta < MESHDELTACOUNTS)
                        {
                            // set the flag to abort the search
                            itooclose = 1;
                        }
                    }
                    else
                    {
                        // store the location of this empty bin for future use
                        l = j;
                        m = k;
                    }   // end of test for valid measurement in this bin

                    k++;
                }       // end of k loop

                j++;
            }           // end of j loop

            // if none too close, store the measurement in the last empty bin found and return
            // l and m are guaranteed to be set if no entries too close are detected
            if (!itooclose)
            {
                for (i = CHX; i <= CHZ; i++)
                {
                    pthisMagBuffer->iBs[i][l][m] = pthisMag->iBs[i];
                }

                pthisMagBuffer->index[l][m] = loopcounter;
                (pthisMagBuffer->iMagBufferCount)++;
            }
        }               // end of test for closeness to current buffer entry

        return;
    }                   // end case 4

    // this line should be unreachable
    return;
}

// function maps the uncalibrated magnetometer data fBs (uT) onto calibrated averaged data fBc (uT), iBc (counts)
void fInvertMagCal(struct MagSensor *pthisMag, struct MagCalibration *pthisMagCal)
{
    // local variables
    float   ftmp[3];    // temporary array
    int8    i;          // loop counter

    // remove the computed hard iron offsets (uT): ftmp[]=fBs[]-V[]
    for (i = CHX; i <= CHZ; i++)
    {
        ftmp[i] = pthisMag->fBs[i] - pthisMagCal->fV[i];
    }

    // remove the computed soft iron offsets (uT and counts): fBc=inv(W)*(fBs[]-V[])
    for (i = CHX; i <= CHZ; i++)
    {
        pthisMag->fBc[i] = pthisMagCal->finvW[i][CHX] *
            ftmp[CHX] +
            pthisMagCal->finvW[i][CHY] *
            ftmp[CHY] +
            pthisMagCal->finvW[i][CHZ] *
            ftmp[CHZ];
        pthisMag->iBc[i] = (int16) (pthisMag->fBc[i] * pthisMag->fCountsPeruT);
    }

    return;
}

// function runs the magnetic calibration
void fRunMagCalibration(struct MagCalibration *pthisMagCal, struct MagBuffer *pthisMagBuffer,
                        struct MagSensor *pthisMag, int32 loopcounter)
{
    int8    i,
            j;  // loop counters

    // determine whether to initiate a new magnetic calibration
    if (!pthisMagCal->iCalInProgress)
    {
        // clear the flag
        pthisMagCal->iInitiateMagCal = 0;

        // try one calibration attempt with the best model available given the number of measurements
        if ((pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS10CAL) &&
            (!pthisMagCal->i10ElementSolverTried))
        {
            pthisMagCal->i10ElementSolverTried = true;
            pthisMagCal->iInitiateMagCal = 10;
        }
        else if ((pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS7CAL) &&
                 (!pthisMagCal->i7ElementSolverTried))
        {
            pthisMagCal->i7ElementSolverTried = true;
            pthisMagCal->iInitiateMagCal = 7;
        }
        else if ((pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS4CAL) &&
                 (!pthisMagCal->i4ElementSolverTried))
        {
            pthisMagCal->i4ElementSolverTried = true;
            pthisMagCal->iInitiateMagCal = 4;
        }

        // otherwise start a calibration at regular interval defined by CAL_INTERVAL_SECS
        else if (!pthisMagCal->iInitiateMagCal &&
                 !(loopcounter % (CAL_INTERVAL_SECS * FUSION_HZ)))
        {
            if (pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS10CAL)
            {
                pthisMagCal->i10ElementSolverTried = true;
                pthisMagCal->iInitiateMagCal = 10;
            }
            else if (pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS7CAL)
            {
                pthisMagCal->i7ElementSolverTried = true;
                pthisMagCal->iInitiateMagCal = 7;
            }
            else if (pthisMagBuffer->iMagBufferCount >= MINMEASUREMENTS4CAL)
            {
                pthisMagCal->i4ElementSolverTried = true;
                pthisMagCal->iInitiateMagCal = 4;
            }
        }

        // store the selected calibration model (if any) to be run
        pthisMagCal->iCalInProgress = pthisMagCal->iInitiateMagCal;
    }

    // on entry each of the calibration functions resets iInitiateMagCal and on completion sets
    // iCalInProgress=0 and iNewCalibrationAvailable=4,7,10 according to the solver used
    switch (pthisMagCal->iCalInProgress)
    {
        case 0:
            break;

        case 4:
            fUpdateMagCalibration4Slice(pthisMagCal, pthisMagBuffer, pthisMag);
            break;

        case 7:
            fUpdateMagCalibration7Slice(pthisMagCal, pthisMagBuffer, pthisMag);
            break;

        case 10:
            fUpdateMagCalibration10Slice(pthisMagCal, pthisMagBuffer, pthisMag);
            break;

        default:
            break;
    }

    // evaluate the new calibration to determine whether to accept it
    if (pthisMagCal->iNewCalibrationAvailable)
    {
        // the geomagnetic field strength must be in range (earth is 22uT to 67uT) with reasonable fit error
        if ((pthisMagCal->ftrB >= MINBFITUT) && (pthisMagCal->ftrB <= MAXBFITUT) &&
            (pthisMagCal->ftrFitErrorpc <= 15.0F))
        {
            // the fit error must be improved or be from a more sophisticated solver but still 5 bars (under 3.5% fit error)
            if ((pthisMagCal->ftrFitErrorpc <= pthisMagCal->fFitErrorpc) || ((
                    pthisMagCal->iNewCalibrationAvailable > pthisMagCal->
                    iValidMagCal) && (pthisMagCal->ftrFitErrorpc <= 3.5F)))
            {
                // accept the new calibration
                pthisMagCal->iValidMagCal = pthisMagCal->iNewCalibrationAvailable;
                pthisMagCal->fFitErrorpc = pthisMagCal->ftrFitErrorpc;
                pthisMagCal->fB = pthisMagCal->ftrB;
                pthisMagCal->fBSq = pthisMagCal->fB * pthisMagCal->fB;
                for (i = CHX; i <= CHZ; i++)
                {
                    pthisMagCal->fV[i] = pthisMagCal->ftrV[i];
                    for (j = CHX; j <= CHZ; j++)
                        pthisMagCal->finvW[i][j] = pthisMagCal->ftrinvW[i][j];
                }
            }
        }
        else if(pthisMagCal->i10ElementSolverTried)
        {
            // the magnetic buffer is presumed corrupted so clear out all measurements and restart calibration attempts
            pthisMagBuffer->iMagBufferCount = 0;
            for (i = 0; i < MAGBUFFSIZEX; i++)
                for (j = 0; j < MAGBUFFSIZEY; j++)
                    pthisMagBuffer->index[i][j] = -1;
            pthisMagCal->i4ElementSolverTried = false;
            pthisMagCal->i7ElementSolverTried = false;
            pthisMagCal->i10ElementSolverTried = false;
        }       // end of test for new calibration within field strength and fit error limits

        // reset the new calibration flag
        pthisMagCal->iNewCalibrationAvailable = 0;
    }           // end of test for new calibration available

    // age the existing fit error very slowly to avoid one good calibration locking out future updates.
    // this prevents a calibration remaining for ever if a unit is never powered down
    if (pthisMagCal->iValidMagCal)
        pthisMagCal->fFitErrorpc += 1.0F / ((float) FUSION_HZ * FITERRORAGINGSECS);

    return;
}

// 4 element calibration using 4x4 matrix inverse
void fUpdateMagCalibration4Slice(struct MagCalibration *pthisMagCal,
                                 struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    int8    i,
            j,
            k;                  // loop counters

    // working arrays for 4x4 matrix inversion
    float   *pfRows[4];
    int8    iColInd[4];
    int8    iRowInd[4];
    int8    iPivot[4];

    // reset the time slice to zero if iInitiateMagCal is set and then clear iInitiateMagCal
    if (pthisMagCal->iInitiateMagCal)
    {
        pthisMagCal->itimeslice = 0;
        pthisMagCal->iInitiateMagCal = false;
        pthisMagCal->iMagBufferReadOnly = true;
    }

    // time slice 0: 18.8K ticks = 0.39ms for 300 measurements on KL25Z
    // initialize matrices and compute average of measurements in magnetic buffer
    if (pthisMagCal->itimeslice == 0)
    {
        int16   iM;             // number of measurements in the buffer

        // zero on and above diagonal matrix X^T.X (in fmatA), vector X^T.Y (in fvecA), scalar Y^T.Y (in fYTY)
        pthisMagCal->fYTY = 0.0F;
        for (i = 0; i < 4; i++)
        {
            pthisMagCal->fvecA[i] = 0.0F;
            for (j = i; j < 4; j++) pthisMagCal->fmatA[i][j] = 0.0F;
        }

        // zero total number of measurements and measurement sums
        iM = 0;
        for (i = 0; i < 3; i++) pthisMagCal->iSumBs[i] = 0;

        // compute the sum of measurements in the magnetic buffer
        for (i = 0; i < MAGBUFFSIZEX; i++)
        {
            for (j = 0; j < MAGBUFFSIZEY; j++)
            {
                if (pthisMagBuffer->index[i][j] != -1)
                {
                    iM++;
                    for (k = 0; k < 3; k++)
                        pthisMagCal->iSumBs[k] += (int32) pthisMagBuffer->iBs[k][i][j];
                }
            }
        }

        // compute the magnetic buffer measurement averages with rounding
        for (i = 0; i < 3; i++)
        {
            if (pthisMagCal->iSumBs[i] >= 0)
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] +
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
            else
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] -
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
        }

        // for defensive programming, re-store the number of active measurements in the buffer
        pthisMagBuffer->iMagBufferCount = iM;

        // increment the time slice
        (pthisMagCal->itimeslice)++;
    }                           // end of time slice 0

    // time slices 1 to MAGBUFFSIZEX: each up to 81K ticks = 1.7ms
    // accumulate the matrices fmatA=X^T.X and fvecA=X^T.Y and Y^T.Y from the magnetic buffer
    else if ((pthisMagCal->itimeslice >= 1) &&
             (pthisMagCal->itimeslice <= MAGBUFFSIZEX))
    {
        float   fBsZeroMeanSq;  // squared magnetic measurement (counts^2)
        int32   iBsZeroMean[3]; // zero mean magnetic buffer measurement (counts)

        // accumulate the measurement matrix elements XTX (in fmatA), XTY (in fvecA) and YTY on the zero mean measurements
        i = pthisMagCal->itimeslice - 1;
        for (j = 0; j < MAGBUFFSIZEY; j++)
        {
            if (pthisMagBuffer->index[i][j] != -1)
            {
                // compute zero mean measurements
                for (k = 0; k < 3; k++)
                    iBsZeroMean[k] = (int32) pthisMagBuffer->iBs[k][i][j] - (int32) pthisMagCal->iMeanBs[k];

                // accumulate the non-zero elements of zero mean XTX (in fmatA)
                pthisMagCal->fmatA[0][0] += (float) (iBsZeroMean[0] * iBsZeroMean[0]);
                pthisMagCal->fmatA[0][1] += (float) (iBsZeroMean[0] * iBsZeroMean[1]);
                pthisMagCal->fmatA[0][2] += (float) (iBsZeroMean[0] * iBsZeroMean[2]);
                pthisMagCal->fmatA[1][1] += (float) (iBsZeroMean[1] * iBsZeroMean[1]);
                pthisMagCal->fmatA[1][2] += (float) (iBsZeroMean[1] * iBsZeroMean[2]);
                pthisMagCal->fmatA[2][2] += (float) (iBsZeroMean[2] * iBsZeroMean[2]);

                // accumulate XTY (in fvecA)
                fBsZeroMeanSq = (float)
                    (
                        iBsZeroMean[CHX] *
                        iBsZeroMean[CHX] +
                        iBsZeroMean[CHY] *
                        iBsZeroMean[CHY] +
                        iBsZeroMean[CHZ] *
                        iBsZeroMean[CHZ]
                    );
                for (k = 0; k < 3; k++)
                    pthisMagCal->fvecA[k] += (float) iBsZeroMean[k] * fBsZeroMeanSq;
                pthisMagCal->fvecA[3] += fBsZeroMeanSq;

                // accumulate fYTY
                pthisMagCal->fYTY += fBsZeroMeanSq * fBsZeroMeanSq;
            }
        }

        // increment the time slice
        (pthisMagCal->itimeslice)++;
    }                   // end of time slices 1 to MAGBUFFSIZEX

    // time slice MAGBUFFSIZEX+1: 18.3K ticks = 0.38ms on KL25Z (constant) (stored in systick[2])
    // re-enable magnetic buffer for writing and invert fmatB = fmatA = X^T.X in situ
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX + 1))
    {
        int8    ierror; // matrix inversion error flag

        // set fmatA[3][3] = X^T.X[3][3] to number of measurements found
        pthisMagCal->fmatA[3][3] = (float) pthisMagBuffer->iMagBufferCount;

        // enable the magnetic buffer for writing now that the matrices have been computed
        pthisMagCal->iMagBufferReadOnly = false;

        // set fmatA and fmatB to above diagonal elements of fmatA
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j <= i; j++)
                pthisMagCal->fmatB[i][j] = pthisMagCal->fmatB[j][i] = pthisMagCal->fmatA[i][j] = pthisMagCal->fmatA[j][i];
        }

        // set fmatB = inv(fmatB) = inv(X^T.X)
        for (i = 0; i < 4; i++) pfRows[i] = pthisMagCal->fmatB[i];
        fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 4, &ierror);

        // increment the time slice
        (pthisMagCal->itimeslice)++;
    }                   // // end of time slice MAGBUFFSIZEX+1

    // time slice MAGBUFFSIZEX+2: 17.2K ticks = 0.36ms on KL25Z (constant) (stored in systick[3])
    // compute the solution vector and the calibration coefficients
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX + 2))
    {
        float   fE;     // error function = r^T.r
        float   ftmp;   // scratch

        // the trial inverse soft iron matrix invW always equals the identity matrix for 4 element calibration
        f3x3matrixAeqI(pthisMagCal->ftrinvW);

        // calculate solution vector fvecB = beta (4x1) = inv(X^T.X).X^T.Y = fmatB * fvecA (counts)
        for (i = 0; i < 4; i++)
        {
            pthisMagCal->fvecB[i] = pthisMagCal->fmatB[i][0] * pthisMagCal->fvecA[0];
            for (j = 1; j < 4; j++)
                pthisMagCal->fvecB[i] += pthisMagCal->fmatB[i][j] * pthisMagCal->fvecA[j];
        }

        // compute the hard iron vector (uT) correction for zero mean data
        ftmp = 0.5F * pthisMag->fuTPerCount;
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrV[i] = ftmp * pthisMagCal->fvecB[i];

        // compute the geomagnetic field strength B (uT)
        pthisMagCal->ftrB = pthisMagCal->fvecB[3] *
            pthisMag->fuTPerCount *
            pthisMag->fuTPerCount;
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrB += pthisMagCal->ftrV[i] * pthisMagCal->ftrV[i];
        pthisMagCal->ftrB = sqrtf(fabs(pthisMagCal->ftrB));

        // add in the previously subtracted magnetic buffer mean to get true hard iron offset (uT)
        ftmp = pthisMag->fuTPerCount / (float) pthisMagBuffer->iMagBufferCount;
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrV[i] += (float) pthisMagCal->iSumBs[i] * ftmp;

        // calculate E = r^T.r = Y^T.Y - 2 * beta^T.(X^T.Y) + beta^T.(X^T.X).beta
        // set E = beta^T.(X^T.Y) = fvecB^T.fvecA
        fE = pthisMagCal->fvecB[0] * pthisMagCal->fvecA[0];
        for (i = 1; i < 4; i++)
            fE += pthisMagCal->fvecB[i] * pthisMagCal->fvecA[i];

        // set E = YTY - 2 * beta^T.(X^T.Y) = YTY - 2 * E;
        fE = pthisMagCal->fYTY - 2.0F * fE;

        // set fvecA = (X^T.X).beta = fmatA.fvecB
        for (i = 0; i < 4; i++)
        {
            pthisMagCal->fvecA[i] = pthisMagCal->fmatA[i][0] * pthisMagCal->fvecB[0];
            for (j = 1; j < 4; j++)
                pthisMagCal->fvecA[i] += pthisMagCal->fmatA[i][j] * pthisMagCal->fvecB[j];
        }

        // add beta^T.(X^T.X).beta = fvecB^T * fvecA to give fit error E (un-normalized counts^4)
        for (i = 0; i < 4; i++)
            fE += pthisMagCal->fvecB[i] * pthisMagCal->fvecA[i];

        // normalize fit error to the number of measurements and take square root to get error in uT^2
        fE = sqrtf(fabs(fE) / (float) pthisMagBuffer->iMagBufferCount) *
            pthisMag->fuTPerCount *
            pthisMag->fuTPerCount;

        // obtain dimensionless error by dividing square square of the geomagnetic field and convert to percent
        pthisMagCal->ftrFitErrorpc = 50.0F * fE / (pthisMagCal->ftrB * pthisMagCal->ftrB);

        // reset the calibration in progress flag to allow writing to the magnetic buffer and flag
        // that a new 4 element calibration is available
        pthisMagCal->iCalInProgress = 0;
        pthisMagCal->iNewCalibrationAvailable = 4;
    }                   // end of time slice MAGBUFFSIZEX+2

    return;
}

// 7 element calibration using direct eigen-decomposition
void fUpdateMagCalibration7Slice(struct MagCalibration *pthisMagCal,
                                 struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    float   fresidue;   // eigen-decomposition residual sum
    float   ftmp;       // scratch variable
    int8    i,
            j,
            k,
            l;          // loop counters
#define MATRIX_7_SIZE   7
    // reset the time slice to zero if iInitiateMagCal is set and then clear iInitiateMagCal
    if (pthisMagCal->iInitiateMagCal)
    {
        pthisMagCal->itimeslice = 0;
        pthisMagCal->iInitiateMagCal = false;
        pthisMagCal->iMagBufferReadOnly = true;
    }

    // time slice 0: 18.1K KL25Z ticks for 300 measurements = 0.38ms on KL25Z (variable) stored in systick[0]
    // zero measurement matrix and calculate the mean values in the magnetic buffer
    if (pthisMagCal->itimeslice == 0)
    {
        int16   iM;     // number of measurements in the magnetic buffer

        // zero the on and above diagonal elements of the 7x7 symmetric measurement matrix fmatA
        for (i = 0; i < MATRIX_7_SIZE; i++)
            for (j = i; j < MATRIX_7_SIZE; j++)
                pthisMagCal->fmatA[i][j] = 0.0F;

        // compute the sum of measurements in the magnetic buffer
        iM = 0;
        for (i = 0; i < 3; i++) pthisMagCal->iSumBs[i] = 0;
        for (i = 0; i < MAGBUFFSIZEX; i++)
        {
            for (j = 0; j < MAGBUFFSIZEY; j++)
            {
                if (pthisMagBuffer->index[i][j] != -1)
                {
                    iM++;
                    for (k = 0; k < 3; k++)
                        pthisMagCal->iSumBs[k] += (int32) pthisMagBuffer->iBs[k][i][j];
                }
            }
        }

        // compute the magnetic buffer measurement averages with nearest integer rounding
        for (i = 0; i < 3; i++)
        {
            if (pthisMagCal->iSumBs[i] >= 0)
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] +
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
            else
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] -
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
        }

        // as defensive programming also ensure the number of measurements found is re-stored
        pthisMagBuffer->iMagBufferCount = iM;

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice 0

    // time slices 1 to MAGBUFFSIZEX * MAGBUFFSIZEY: accumulate matrices: 8.6K KL25Z ticks = 0.18ms (with max stored in systick[1])
    else if ((pthisMagCal->itimeslice >= 1) &&
             (pthisMagCal->itimeslice <= MAGBUFFSIZEX * MAGBUFFSIZEY))
    {
        // accumulate the symmetric matrix fmatA on the zero mean measurements
        i = (pthisMagCal->itimeslice - 1) / MAGBUFFSIZEY;   // matrix row i ranges 0 to MAGBUFFSIZEX-1
        j = (pthisMagCal->itimeslice - 1) % MAGBUFFSIZEY;   // matrix column j ranges 0 to MAGBUFFSIZEY-1
        if (pthisMagBuffer->index[i][j] != -1)
        {
            // set fvecA to be vector of zero mean measurements and their squares
            for (k = 0; k < 3; k++)
            {
                pthisMagCal->fvecA[k + 3] = (float)
                    (
                        (int32) pthisMagBuffer->iBs[k][i][j] -
                        (int32) pthisMagCal->iMeanBs[k]
                    );
                pthisMagCal->fvecA[k] = pthisMagCal->fvecA[k + 3] * pthisMagCal->fvecA[k + 3];
            }

            // update non-zero elements fmatA[0-2][6] of fmatA ignoring fmatA[6][6] which is set later.
            // elements fmatA[3-5][6] are zero as a result of subtracting the mean value
            for (k = 0; k < 3; k++)
                pthisMagCal->fmatA[k][6] += pthisMagCal->fvecA[k];

            // update the remaining on and above diagonal elements fmatA[0-5][0-5]
            for (k = 0; k < (MATRIX_7_SIZE - 1); k++)
            {
                for (l = k; l < (MATRIX_7_SIZE - 1); l++)
                    pthisMagCal->fmatA[k][l] += pthisMagCal->fvecA[k] * pthisMagCal->fvecA[l];
            }
        }

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slices 1 to MAGBUFFSIZEX * MAGBUFFSIZEY

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 1: 0.8K ticks on KL25Z = 0.02ms on KL25Z (constant) (stored in systick[2])
    // re-enable magnetic buffer for writing and prepare fmatA, fmatB, fvecA for eigendecomposition
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 1))
    {
        // set fmatA[6][6] to the number of magnetic measurements found
        pthisMagCal->fmatA[MATRIX_7_SIZE - 1][MATRIX_7_SIZE - 1] = (float) pthisMagBuffer->iMagBufferCount;

        // clear the magnetic buffer read only flag now that the matrices have been computed
        pthisMagCal->iMagBufferReadOnly = false;

        // set below diagonal elements of 7x7 matrix fmatA to above diagonal elements
        for (i = 1; i < MATRIX_7_SIZE; i++)
            for (j = 0; j < i; j++)
                pthisMagCal->fmatA[i][j] = pthisMagCal->fmatA[j][i];

        // set matrix of eigenvectors fmatB to identity matrix and eigenvalues vector fvecA to diagonal elements of fmatA
        for (i = 0; i < MATRIX_7_SIZE; i++)
        {
            for (j = 0; j < MATRIX_7_SIZE; j++)
                pthisMagCal->fmatB[i][j] = 0.0F;
            pthisMagCal->fmatB[i][i] = 1.0F;
            pthisMagCal->fvecA[i] = pthisMagCal->fmatA[i][i];
        }

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 1

    // repeating 21 time slices MAGBUFFSIZEX * MAGBUFFSIZEY + 2 to MAGBUFFSIZEX * MAGBUFFSIZEY + 22 inclusive
    // to perform the eigendecomposition of the measurement matrix fmatA.
    // 19.6k ticks = 0.41ms on KL25Z (with max stored in systick[3]).
    // for a 7x7 matrix there are 21 above diagonal elements: 6+5+4+3+2+1+0=21
    else if ((pthisMagCal->itimeslice >= (MAGBUFFSIZEX * MAGBUFFSIZEY + 2)) &&
             (pthisMagCal->itimeslice <= (MAGBUFFSIZEX * MAGBUFFSIZEY + 22)))
    {
        // set k to the matrix element in range 0 to 20 to be zeroed and used it to set row i and column j
        k = pthisMagCal->itimeslice - (MAGBUFFSIZEX * MAGBUFFSIZEY + 2);
        if (k < 6)
        {
            i = 0;
            j = k + 1;
        }
        else if (k < 11)
        {
            i = 1;
            j = k - 4;
        }
        else if (k < 15)
        {
            i = 2;
            j = k - 8;
        }
        else if (k < 18)
        {
            i = 3;
            j = k - 11;
        }
        else if (k < 20)
        {
            i = 4;
            j = k - 13;
        }
        else
        {
            i = 5;
            j = 6;
        }

        // only continue if matrix element i, j has not already been zeroed
        if (fabsf(pthisMagCal->fmatA[i][j]) > 0.0F)
            fComputeEigSlice(pthisMagCal->fmatA, pthisMagCal->fmatB,
                             pthisMagCal->fvecA, i, j, MATRIX_7_SIZE);

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 2 to MAGBUFFSIZEX * MAGBUFFSIZEY + 22 inclusive

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 23: 2.6k ticks on KL25Z = 0.05ms on KL25Z (constant) (stored in systick[4])
    // compute the sum of the absolute values of above diagonal elements in fmatA as eigen-decomposition exit criterion
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 23))
    {
        // sum residue of all above-diagonal elements
        fresidue = 0.0F;
        for (i = 0; i < MATRIX_7_SIZE; i++)
            for (j = i + 1; j < MATRIX_7_SIZE; j++)
                fresidue += fabsf(pthisMagCal->fmatA[i][j]);

        // determine whether to re-enter the eigen-decomposition or skip to calculation of the calibration coefficients
        if (fresidue > 0.0F)
            // continue the eigen-decomposition
            (pthisMagCal->itimeslice) = MAGBUFFSIZEX * MAGBUFFSIZEY + 2;
        else
            // continue to compute the calibration coefficients since the eigen-decomposition is complete
            (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 23

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 24: 27.8k ticks = 0.58ms on KL25Z (constant) (stored in systick[5])
    // compute the calibration coefficients from the solution eigenvector
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 24))
    {
        float   fdetA;  // determinant of ellipsoid matrix A
        int8    imin;   // column of solution eigenvector with minimum eigenvalue

        // set imin to the index of the smallest eigenvalue in fvecA
        imin = 0;
        for (i = 1; i < MATRIX_7_SIZE; i++)
            if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[imin]) imin = i;

        // the ellipsoid fA must have positive determinant but the eigensolver can equally easily return a negated
        // normalized eigenvector without changing the eigenvalue. compute the determinant of ellipsoid matrix A
        // from first three elements of eigenvector and negate the eigenvector if negative.
        fdetA = pthisMagCal->fmatB[CHX][imin] *
            pthisMagCal->fmatB[CHY][imin] *
            pthisMagCal->fmatB[CHZ][imin];
        if (fdetA < 0.0F)
        {
            fdetA = fabs(fdetA);
            for (i = 0; i < MATRIX_7_SIZE; i++)
                pthisMagCal->fmatB[i][imin] = -pthisMagCal->fmatB[i][imin];
        }

        // set diagonal elements of ellipsoid matrix A to the solution vector imin with smallest eigenvalue and
        // zero off-diagonal elements since these are always zero in the 7 element model
        // compute the hard iron offset fV for zero mean data (counts)
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrV[i] = -0.5F *
                pthisMagCal->fmatB[i + 3][imin] /
                pthisMagCal->fmatB[i][imin];

        // set ftmp to the square of the geomagnetic field strength fB (counts) corresponding to current value of fdetA
        ftmp = -pthisMagCal->fmatB[6][imin];
        for (i = CHX; i <= CHZ; i++)
            ftmp += pthisMagCal->fmatB[i][imin] *
                pthisMagCal->ftrV[i] *
                pthisMagCal->ftrV[i];

        // calculate the trial normalized fit error as a percentage normalized by the geomagnetic field strength squared
        pthisMagCal->ftrFitErrorpc = 50.0F * sqrtf(fabsf(pthisMagCal->fvecA[imin]) /
                                                           (float) pthisMagBuffer->iMagBufferCount) / fabsf(ftmp);

        // compute the geomagnetic field strength (uT) for current value of fdetA
        pthisMagCal->ftrB = sqrtf(fabsf(ftmp)) * pthisMag->fuTPerCount;

        // compute the normalized ellipsoid matrix A with unit determinant and derive invW also with unit determinant.
        ftmp = powf(fabs(fdetA), -(ONETHIRD));
        for (i = CHX; i <= CHZ; i++)
        {
            pthisMagCal->fA[i][i] = pthisMagCal->fmatB[i][imin] * ftmp;
            pthisMagCal->ftrinvW[i][i] = sqrtf(fabsf(pthisMagCal->fA[i][i]));
        }

        pthisMagCal->fA[CHX][CHY] = pthisMagCal->fA[CHX][CHZ] = pthisMagCal->fA[CHY][CHZ] = 0.0F;
        pthisMagCal->ftrinvW[CHX][CHY] = pthisMagCal->ftrinvW[CHX][CHZ] = pthisMagCal->ftrinvW[CHY][CHZ] = 0.0F;

        // each element of fA has been scaled by fdetA^(-1/3) so the square of geomagnetic field strength B^2
        // must be adjusted by the same amount and B by the square root to keep the ellipsoid equation valid:
        // (Bk-V)^T.A.(Bk-V) = (Bk-V)^T.(invW)^T.invW.(Bk-V) = B^2
        pthisMagCal->ftrB *= sqrt(fabs(ftmp));

        // compute the final hard iron offset (uT) by adding in previously subtracted zero mean offset (counts)
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrV[i] =
                (
                    pthisMagCal->ftrV[i] +
                    (float) pthisMagCal->iMeanBs[i]
                ) *
                pthisMag->fuTPerCount;

        // reset the calibration in progress flag to allow writing to the magnetic buffer and flag
        // that a new 7 element calibration is available
        pthisMagCal->iCalInProgress = 0;
        pthisMagCal->iNewCalibrationAvailable = 7;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 24

    return;
}

// 10 element calibration using direct eigen-decomposition
void fUpdateMagCalibration10Slice(struct MagCalibration *pthisMagCal,
                                  struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    float   fresidue;   // eigen-decomposition residual sum
    float   ftmp;       // scratch variable
    int8    i,
            j,
            k,
            l;          // loop counters
#define MATRIX_10_SIZE  10
    // reset the time slice to zero if iInitiateMagCal is set and then clear iInitiateMagCal
    if (pthisMagCal->iInitiateMagCal)
    {
        pthisMagCal->itimeslice = 0;
        pthisMagCal->iInitiateMagCal = false;
        pthisMagCal->iMagBufferReadOnly = true;
    }

    // time slice 0: 18.7k KL25Z ticks for 300 measurements = 0.39ms on KL25Z (variable) stored in systick[0]
    // zero measurement matrix fmatA and calculate the mean values in the magnetic buffer
    if (pthisMagCal->itimeslice == 0)
    {
        int16   iM;     // number of measurements in the magnetic buffer

        // zero the on and above diagonal elements of the 10x10 symmetric measurement matrix fmatA
        for (i = 0; i < MATRIX_10_SIZE; i++)
            for (j = i; j < MATRIX_10_SIZE; j++)
                pthisMagCal->fmatA[i][j] = 0.0F;

        // compute the sum of measurements in the magnetic buffer
        iM = 0;
        for (i = 0; i < 3; i++) pthisMagCal->iSumBs[i] = 0;
        for (i = 0; i < MAGBUFFSIZEX; i++)
        {
            for (j = 0; j < MAGBUFFSIZEY; j++)
            {
                if (pthisMagBuffer->index[i][j] != -1)
                {
                    iM++;
                    for (k = 0; k < 3; k++)
                        pthisMagCal->iSumBs[k] += (int32) pthisMagBuffer->iBs[k][i][j];
                }
            }
        }

        // compute the magnetic buffer measurement averages with nearest integer rounding
        for (i = 0; i < 3; i++)
        {
            if (pthisMagCal->iSumBs[i] >= 0)
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] +
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
            else
                pthisMagCal->iMeanBs[i] =
                    (
                        pthisMagCal->iSumBs[i] -
                        ((int32) iM >> 1)
                    ) /
                    (int32) iM;
        }

        // as defensive programming also ensure the number of measurements found is re-stored
        pthisMagBuffer->iMagBufferCount = iM;

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice 0

    // time slices 1 to MAGBUFFSIZEX * MAGBUFFSIZEY: accumulate matrices: 17.9k KL25Z ticks = 0.37ms for 300 measurements
    // (with max measured stored in systick[1])
    else if ((pthisMagCal->itimeslice >= 1) &&
             (pthisMagCal->itimeslice <= MAGBUFFSIZEX * MAGBUFFSIZEY))
    {
        // accumulate the symmetric matrix fmatA on the zero mean measurements
        i = (pthisMagCal->itimeslice - 1) / MAGBUFFSIZEY;   // matrix row i ranges 0 to MAGBUFFSIZEX-1
        j = (pthisMagCal->itimeslice - 1) % MAGBUFFSIZEY;   // matrix column j ranges 0 to MAGBUFFSIZEY-1
        if (pthisMagBuffer->index[i][j] != -1)
        {
            // set fvecA[6-8] to the zero mean measurements
            for (k = 0; k < 3; k++)
                pthisMagCal->fvecA[k + 6] = (float)
                    (
                        (int32) pthisMagBuffer->iBs[k][i][j] -
                        (int32) pthisMagCal->iMeanBs[k]
                    );

            // compute fvecA[0-5] from fvecA[6-8]
            pthisMagCal->fvecA[0] = pthisMagCal->fvecA[6] * pthisMagCal->fvecA[6];
            pthisMagCal->fvecA[1] = 2.0F *
                pthisMagCal->fvecA[6] *
                pthisMagCal->fvecA[7];
            pthisMagCal->fvecA[2] = 2.0F *
                pthisMagCal->fvecA[6] *
                pthisMagCal->fvecA[8];
            pthisMagCal->fvecA[3] = pthisMagCal->fvecA[7] * pthisMagCal->fvecA[7];
            pthisMagCal->fvecA[4] = 2.0F *
                pthisMagCal->fvecA[7] *
                pthisMagCal->fvecA[8];
            pthisMagCal->fvecA[5] = pthisMagCal->fvecA[8] * pthisMagCal->fvecA[8];

            // update non-zero elements fmatA[0-5][9] of fmatA ignoring fmatA[9][9] which is set later.
            // elements fmatA[6-8][9] are zero as a result of subtracting the mean value
            for (k = 0; k < 6; k++)
                pthisMagCal->fmatA[k][9] += pthisMagCal->fvecA[k];

            // update the remaining on and above diagonal elements fmatA[0-8][0-8]
            for (k = 0; k < (MATRIX_10_SIZE - 1); k++)
            {
                for (l = k; l < (MATRIX_10_SIZE - 1); l++)
                    pthisMagCal->fmatA[k][l] += pthisMagCal->fvecA[k] * pthisMagCal->fvecA[l];
            }
        }

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slices 1 to MAGBUFFSIZEX * MAGBUFFSIZEY

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 1: 1.2k ticks on KL25Z = 0.025ms on KL25Z (constant) (stored in systick[2])
    // re-enable magnetic buffer for writing and prepare fmatA, fmatB, fvecA for eigendecomposition
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 1))
    {
        // set fmatA[9][9] to the number of magnetic measurements found
        pthisMagCal->fmatA[MATRIX_10_SIZE - 1][MATRIX_10_SIZE - 1] = (float) pthisMagBuffer->iMagBufferCount;

        // clear the magnetic buffer read only flag now that the matrices have been computed
        pthisMagCal->iMagBufferReadOnly = false;

        // set below diagonal elements of 10x10 matrix fmatA to above diagonal elements
        for (i = 1; i < MATRIX_10_SIZE; i++)
            for (j = 0; j < i; j++)
                pthisMagCal->fmatA[i][j] = pthisMagCal->fmatA[j][i];

        // set matrix of eigenvectors fmatB to identity matrix and eigenvalues vector fvecA to diagonal elements of fmatA
        for (i = 0; i < MATRIX_10_SIZE; i++)
        {
            for (j = 0; j < MATRIX_10_SIZE; j++)
                pthisMagCal->fmatB[i][j] = 0.0F;
            pthisMagCal->fmatB[i][i] = 1.0F;
            pthisMagCal->fvecA[i] = pthisMagCal->fmatA[i][i];
        }

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 1

    // repeating 45 time slices MAGBUFFSIZEX * MAGBUFFSIZEY + 2 to MAGBUFFSIZEX * MAGBUFFSIZEY + 46 inclusive
    // to perform the eigendecomposition of the measurement matrix fmatA.
    // 28.2k ticks = 0.56ms on KL25Z (with max stored in systick[3]).
    // for a 10x10 matrix there are 45 above diagonal elements: 9+8+7+6+5+4+3+2+1+0=45
    else if ((pthisMagCal->itimeslice >= (MAGBUFFSIZEX * MAGBUFFSIZEY + 2)) &&
             (pthisMagCal->itimeslice <= (MAGBUFFSIZEX * MAGBUFFSIZEY + 46)))
    {
        // set k to the matrix element of interest in range 0 to 44 to be zeroed and set row i and column j
        k = pthisMagCal->itimeslice - (MAGBUFFSIZEX * MAGBUFFSIZEY + 2);
        if (k < 9)
        {
            i = 0;
            j = k + 1;
        }
        else if (k < 17)
        {
            i = 1;
            j = k - 7;
        }
        else if (k < 24)
        {
            i = 2;
            j = k - 14;
        }
        else if (k < 30)
        {
            i = 3;
            j = k - 20;
        }
        else if (k < 35)
        {
            i = 4;
            j = k - 25;
        }
        else if (k < 39)
        {
            i = 5;
            j = k - 29;
        }
        else if (k < 42)
        {
            i = 6;
            j = k - 32;
        }
        else if (k < 44)
        {
            i = 7;
            j = k - 34;
        }
        else
        {
            i = 8;
            j = 9;
        }

        // only continue if matrix element i, j has not already been zeroed
        if (fabsf(pthisMagCal->fmatA[i][j]) > 0.0F)
            fComputeEigSlice(pthisMagCal->fmatA, pthisMagCal->fmatB,
                             pthisMagCal->fvecA, i, j, MATRIX_10_SIZE);

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 2 to MAGBUFFSIZEX * MAGBUFFSIZEY + 46 inclusive

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 47: 5.6k ticks on KL25Z = 0.12ms on KL25Z (constant) (stored in systick[4])
    // compute the sum of the absolute values of above diagonal elements in fmatA as eigen-decomposition exit criterion
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 47))
    {
        // sum residue of all above-diagonal elements
        fresidue = 0.0F;
        for (i = 0; i < MATRIX_10_SIZE; i++)
            for (j = i + 1; j < MATRIX_10_SIZE; j++)
                fresidue += fabsf(pthisMagCal->fmatA[i][j]);

        // determine whether to re-enter the eigen-decomposition or skip to calculation of the calibration coefficients
        if (fresidue > 0.0F)
            // continue the eigen-decomposition
            (pthisMagCal->itimeslice) = MAGBUFFSIZEX * MAGBUFFSIZEY + 2;
        else
            // continue to compute the calibration coefficients since the eigen-decomposition is complete
            (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 47

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 48: 38.5k ticks = 0.80ms on KL25Z (constant) (stored in systick[5])
    // compute the calibration coefficients (excluding invW) from the solution eigenvector
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 48))
    {
        float   fdetA;  // determinant of ellipsoid matrix A
        int8    imin;   // column of solution eigenvector with minimum eigenvalue

        // set imin to the index of the smallest eigenvalue in fvecA
        imin = 0;
        for (i = 1; i < MATRIX_10_SIZE; i++)
            if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[imin]) imin = i;

        // set the ellipsoid matrix A from elements 0 to 5 of the solution eigenvector.
        pthisMagCal->fA[CHX][CHX] = pthisMagCal->fmatB[0][imin];
        pthisMagCal->fA[CHX][CHY] = pthisMagCal->fA[CHY][CHX] = pthisMagCal->fmatB[1][imin];
        pthisMagCal->fA[CHX][CHZ] = pthisMagCal->fA[CHZ][CHX] = pthisMagCal->fmatB[2][imin];
        pthisMagCal->fA[CHY][CHY] = pthisMagCal->fmatB[3][imin];
        pthisMagCal->fA[CHY][CHZ] = pthisMagCal->fA[CHZ][CHY] = pthisMagCal->fmatB[4][imin];
        pthisMagCal->fA[CHZ][CHZ] = pthisMagCal->fmatB[5][imin];

        // negate A and the entire solution vector A has negative determinant
        fdetA = f3x3matrixDetA(pthisMagCal->fA);
        if (fdetA < 0.0F)
        {
            f3x3matrixAeqMinusA(pthisMagCal->fA);
            fdetA = fabs(fdetA);
            for (i = 0; i < MATRIX_10_SIZE; i++)
                pthisMagCal->fmatB[i][imin] = -pthisMagCal->fmatB[i][imin];
        }

        // set finvA to the inverse of the ellipsoid matrix fA
        f3x3matrixAeqInvSymB(pthisMagCal->finvA, pthisMagCal->fA);

        // compute the hard iron offset fV for zero mean data (counts)
        for (i = CHX; i <= CHZ; i++)
        {
            pthisMagCal->ftrV[i] = pthisMagCal->finvA[i][0] *
                pthisMagCal->fmatB[6][imin] +
                pthisMagCal->finvA[i][1] *
                pthisMagCal->fmatB[7][imin] +
                pthisMagCal->finvA[i][2] *
                pthisMagCal->fmatB[8][imin];
            pthisMagCal->ftrV[i] *= -0.5F;
        }

        // compute the geomagnetic field strength B (counts) for current (un-normalized) ellipsoid matrix determinant.
        ftmp = pthisMagCal->fA[CHX][CHY] *
            pthisMagCal->ftrV[CHX] *
            pthisMagCal->ftrV[CHY] +
            pthisMagCal->fA[CHX][CHZ] *
            pthisMagCal->ftrV[CHX] *
            pthisMagCal->ftrV[CHZ] +
            pthisMagCal->fA[CHY][CHZ] *
            pthisMagCal->ftrV[CHY] *
            pthisMagCal->ftrV[CHZ];
        ftmp *= 2.0F;
        ftmp -= pthisMagCal->fmatB[9][imin];
        ftmp += pthisMagCal->fA[CHX][CHX] *
            pthisMagCal->ftrV[CHX] *
            pthisMagCal->ftrV[CHX];
        ftmp += pthisMagCal->fA[CHY][CHY] *
            pthisMagCal->ftrV[CHY] *
            pthisMagCal->ftrV[CHY];
        ftmp += pthisMagCal->fA[CHZ][CHZ] *
            pthisMagCal->ftrV[CHZ] *
            pthisMagCal->ftrV[CHZ];
        pthisMagCal->ftrB = sqrtf(fabsf(ftmp));

        // calculate the normalized fit error as a percentage
        pthisMagCal->ftrFitErrorpc = 50.0F * sqrtf(fabsf(
                                                       pthisMagCal->fvecA[imin] /
                                                   (float) pthisMagBuffer->iMagBufferCount
                                                   )) / (pthisMagCal->ftrB * pthisMagCal->ftrB);

        // convert the trial geomagnetic field strength B from counts to uT for un-normalized soft iron matrix A
        pthisMagCal->ftrB *= pthisMag->fuTPerCount;

        // compute the final hard iron offset (uT) by adding in previously subtracted zero mean offset (counts)
        for (i = CHX; i <= CHZ; i++)
            pthisMagCal->ftrV[i] =
                (
                    pthisMagCal->ftrV[i] +
                    (float) pthisMagCal->iMeanBs[i]
                ) *
                pthisMag->fuTPerCount;

        // normalize the ellipsoid matrix A to unit determinant
        ftmp = powf(fabs(fdetA), -(ONETHIRD));
        f3x3matrixAeqAxScalar(pthisMagCal->fA, ftmp);

        // each element of fA has been scaled by fdetA^(-1/3) so the square of geomagnetic field strength B^2
        // must be adjusted by the same amount and B by the square root to keep the ellipsoid equation valid:
        // (Bk-V)^T.A.(Bk-V) = (Bk-V)^T.(invW)^T.invW.(Bk-V) = B^2
        pthisMagCal->ftrB *= sqrt(fabs(ftmp));

        // prepare for eigendecomposition of fA to compute finvW from the square root of fA by setting
        // fmatA (upper left) to the 3x3 matrix fA, set fmatB (eigenvectors to identity matrix and
        // fvecA (eigenvalues) to diagonal elements of fmatA = fA
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                pthisMagCal->fmatA[i][j] = pthisMagCal->fA[i][j];
                pthisMagCal->fmatB[i][j] = 0.0F;
            }

            pthisMagCal->fmatB[i][i] = 1.0F;
            pthisMagCal->fvecA[i] = pthisMagCal->fmatA[i][i];
        }

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 48

    // repeating 3 time slices MAGBUFFSIZEX * MAGBUFFSIZEY + 49 to MAGBUFFSIZEX * MAGBUFFSIZEY + 51 inclusive
    // 9.7kticks = 0.2ms on KL25Z (with max stored in systick[6]).
    // perform the eigendecomposition of the 3x3 ellipsoid matrix fA which has 3 above diagonal elements: 2+1+0=3
    else if ((pthisMagCal->itimeslice >= (MAGBUFFSIZEX * MAGBUFFSIZEY + 49)) &&
             (pthisMagCal->itimeslice <= (MAGBUFFSIZEX * MAGBUFFSIZEY + 51)))
    {
        // set k to the matrix element of interest in range 0 to 2 to be zeroed and set row i and column j
        k = pthisMagCal->itimeslice - (MAGBUFFSIZEX * MAGBUFFSIZEY + 49);
        if (k == 0)
        {
            i = 0;
            j = 1;
        }
        else if (k == 1)
        {
            i = 0;
            j = 2;
        }
        else
        {
            i = 1;
            j = 2;
        }

        // only continue with eigen-decomposition if matrix element i, j has not already been zeroed
        if (fabsf(pthisMagCal->fmatA[i][j]) > 0.0F)
            fComputeEigSlice(pthisMagCal->fmatA, pthisMagCal->fmatB,
                             pthisMagCal->fvecA, i, j, 3);

        // increment the time slice for the next iteration
        (pthisMagCal->itimeslice)++;
    }                   // end of time slices MAGBUFFSIZEX * MAGBUFFSIZEY + 49 to MAGBUFFSIZEX * MAGBUFFSIZEY + 51 inclusive

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 52: 0.3k ticks = 0.006ms on KL25Z (constant) (stored in systick[7])
    // determine whether the eigen-decomposition of fA is complete
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 52))
    {
        // sum residue of all above-diagonal elements and use to determine whether
        // to re-enter the eigen-decomposition or skip to calculation of the calibration coefficients
        fresidue = fabsf(pthisMagCal->fmatA[0][1]) + fabsf(pthisMagCal->fmatA[0][2]) + fabsf(pthisMagCal->fmatA[1][2]);
        if (fresidue > 0.0F)
            // continue the eigen-decomposition
            (pthisMagCal->itimeslice) = MAGBUFFSIZEX * MAGBUFFSIZEY + 49;
        else
            // continue to compute the calibration coefficients since the eigen-decomposition is complete
            (pthisMagCal->itimeslice)++;
    }                   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 52

    // time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 53: 9.3k ticks = 0.19ms on KL25Z (constant) (stored in systick[8])
    // compute the inverse gain matrix invW from the eigendecomposition of the ellipsoid matrix A
    else if (pthisMagCal->itimeslice == (MAGBUFFSIZEX * MAGBUFFSIZEY + 53))
    {
        // set pthisMagCal->fmatB to be eigenvectors . diag(sqrt(sqrt(eigenvalues))) = fmatB . diag(sqrt(sqrt(fvecA))
        for (j = 0; j < 3; j++)     // loop over columns j
        {
            ftmp = sqrtf(sqrtf(fabsf(pthisMagCal->fvecA[j])));
            for (i = 0; i < 3; i++) // loop over rows i
                pthisMagCal->fmatB[i][j] *= ftmp;
        }

        // set ftrinvW to eigenvectors * diag(sqrt(eigenvalues)) * eigenvectors^T
        // = fmatB * fmatB^T = sqrt(fA) (guaranteed symmetric)
        // loop over on and above diagonal elements
        for (i = 0; i < 3; i++)
        {
            for (j = i; j < 3; j++)
            {
                pthisMagCal->ftrinvW[i][j] = pthisMagCal->ftrinvW[j][i] =
                        pthisMagCal->fmatB[i][0] *
                    pthisMagCal->fmatB[j][0] +
                    pthisMagCal->fmatB[i][1] *
                    pthisMagCal->fmatB[j][1] +
                    pthisMagCal->fmatB[i][2] *
                    pthisMagCal->fmatB[j][2];
            }
        }

        // reset the calibration in progress flag to allow writing to the magnetic buffer and flag
        // that a new 10 element calibration is available
        pthisMagCal->iCalInProgress = 0;
        pthisMagCal->iNewCalibrationAvailable = 10;
    }   // end of time slice MAGBUFFSIZEX * MAGBUFFSIZEY + 53

    return;
}

// 4 element calibration using 4x4 matrix inverse
void fComputeMagCalibration4(struct MagCalibration *pthisMagCal,
                             struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    float   fBs2;       // fBs[CHX]^2+fBs[CHY]^2+fBs[CHZ]^2
    float   fSumBs4;    // sum of fBs2
    float   fscaling;   // set to FUTPERCOUNT * FMATRIXSCALING
    float   fE;         // error function = r^T.r
    int16   iOffset[3]; // offset to remove large DC hard iron bias in matrix
    int16   iCount;     // number of measurements counted
    int8    ierror;     // matrix inversion error flag
    int8    i,
            j,
            k,
            l;          // loop counters

    // working arrays for 4x4 matrix inversion
    float   *pfRows[4];
    int8    iColInd[4];
    int8    iRowInd[4];
    int8    iPivot[4];

    // compute fscaling to reduce multiplications later
    fscaling = pthisMag->fuTPerCount / DEFAULTB;

    // the trial inverse soft iron matrix invW always equals the identity matrix for 4 element calibration
    f3x3matrixAeqI(pthisMagCal->ftrinvW);

    // zero fSumBs4=Y^T.Y, fvecB=X^T.Y (4x1) and on and above diagonal elements of fmatA=X^T*X (4x4)
    fSumBs4 = 0.0F;
    for (i = 0; i < 4; i++)
    {
        pthisMagCal->fvecB[i] = 0.0F;
        for (j = i; j < 4; j++)
        {
            pthisMagCal->fmatA[i][j] = 0.0F;
        }
    }

    // the offsets are guaranteed to be set from the first element but to avoid compiler error
    iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

    // use entries from magnetic buffer to compute matrices
    iCount = 0;
    for (j = 0; j < MAGBUFFSIZEX; j++)
    {
        for (k = 0; k < MAGBUFFSIZEY; k++)
        {
            if (pthisMagBuffer->index[j][k] != -1)
            {
                // use first valid magnetic buffer entry as estimate (in counts) for offset
                if (iCount == 0)
                {
                    for (l = CHX; l <= CHZ; l++)
                    {
                        iOffset[l] = pthisMagBuffer->iBs[l][j][k];
                    }
                }

                // store scaled and offset fBs[XYZ] in fvecA[0-2] and fBs[XYZ]^2 in fvecA[3-5]
                for (l = CHX; l <= CHZ; l++)
                {
                    pthisMagCal->fvecA[l] = (float)
                        (
                            (int32) pthisMagBuffer->iBs[l][j][k] -
                            (int32) iOffset[l]
                        ) * fscaling;
                    pthisMagCal->fvecA[l + 3] = pthisMagCal->fvecA[l] * pthisMagCal->fvecA[l];
                }

                // calculate fBs2 = fBs[CHX]^2 + fBs[CHY]^2 + fBs[CHZ]^2 (scaled uT^2)
                fBs2 = pthisMagCal->fvecA[3] +
                    pthisMagCal->fvecA[4] +
                    pthisMagCal->fvecA[5];

                // accumulate fBs^4 over all measurements into fSumBs4=Y^T.Y
                fSumBs4 += fBs2 * fBs2;

                // now we have fBs2, accumulate fvecB[0-2] = X^T.Y =sum(fBs2.fBs[XYZ])
                for (l = CHX; l <= CHZ; l++)
                {
                    pthisMagCal->fvecB[l] += pthisMagCal->fvecA[l] * fBs2;
                }

                //accumulate fvecB[3] = X^T.Y =sum(fBs2)
                pthisMagCal->fvecB[3] += fBs2;

                // accumulate on and above-diagonal terms of fmatA = X^T.X ignoring fmatA[3][3]
                pthisMagCal->fmatA[0][0] += pthisMagCal->fvecA[CHX + 3];
                pthisMagCal->fmatA[0][1] += pthisMagCal->fvecA[CHX] * pthisMagCal->fvecA[CHY];
                pthisMagCal->fmatA[0][2] += pthisMagCal->fvecA[CHX] * pthisMagCal->fvecA[CHZ];
                pthisMagCal->fmatA[0][3] += pthisMagCal->fvecA[CHX];
                pthisMagCal->fmatA[1][1] += pthisMagCal->fvecA[CHY + 3];
                pthisMagCal->fmatA[1][2] += pthisMagCal->fvecA[CHY] * pthisMagCal->fvecA[CHZ];
                pthisMagCal->fmatA[1][3] += pthisMagCal->fvecA[CHY];
                pthisMagCal->fmatA[2][2] += pthisMagCal->fvecA[CHZ + 3];
                pthisMagCal->fmatA[2][3] += pthisMagCal->fvecA[CHZ];

                // increment the counter for next iteration
                iCount++;
            }
        }
    }

    // set the last element of the measurement matrix to the number of buffer elements used
    pthisMagCal->fmatA[3][3] = (float) iCount;

    // store the number of measurements accumulated (defensive programming, should never be needed)
    pthisMagBuffer->iMagBufferCount = iCount;

    // use above diagonal elements of symmetric fmatA to set both fmatB and fmatA to X^T.X
    for (i = 0; i < 4; i++)
    {
        for (j = i; j < 4; j++)
        {
            pthisMagCal->fmatB[i][j] = pthisMagCal->fmatB[j][i] = pthisMagCal->fmatA[j][i] = pthisMagCal->fmatA[i][j];
        }
    }

    // calculate in situ inverse of fmatB = inv(X^T.X) (4x4) while fmatA still holds X^T.X
    for (i = 0; i < 4; i++)
    {
        pfRows[i] = pthisMagCal->fmatB[i];
    }

    fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 4, &ierror);

    // calculate fvecA = solution beta (4x1) = inv(X^T.X).X^T.Y = fmatB * fvecB
    for (i = 0; i < 4; i++)
    {
        pthisMagCal->fvecA[i] = 0.0F;
        for (k = 0; k < 4; k++)
        {
            pthisMagCal->fvecA[i] += pthisMagCal->fmatB[i][k] * pthisMagCal->fvecB[k];
        }
    }

    // calculate E = r^T.r = Y^T.Y - 2 * beta^T.(X^T.Y) + beta^T.(X^T.X).beta
    // = fSumBs4 - 2 * fvecA^T.fvecB + fvecA^T.fmatA.fvecA
    // first set E = Y^T.Y - 2 * beta^T.(X^T.Y) = fSumBs4 - 2 * fvecA^T.fvecB
    fE = 0.0F;
    for (i = 0; i < 4; i++)
    {
        fE += pthisMagCal->fvecA[i] * pthisMagCal->fvecB[i];
    }

    fE = fSumBs4 - 2.0F * fE;

    // set fvecB = (X^T.X).beta = fmatA.fvecA
    for (i = 0; i < 4; i++)
    {
        pthisMagCal->fvecB[i] = 0.0F;
        for (k = 0; k < 4; k++)
        {
            pthisMagCal->fvecB[i] += pthisMagCal->fmatA[i][k] * pthisMagCal->fvecA[k];
        }
    }

    // complete calculation of E by adding beta^T.(X^T.X).beta = fvecA^T * fvecB
    for (i = 0; i < 4; i++)
    {
        fE += pthisMagCal->fvecB[i] * pthisMagCal->fvecA[i];
    }

    // compute the hard iron vector (in uT but offset and scaled by FMATRIXSCALING)
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->ftrV[l] = 0.5F * pthisMagCal->fvecA[l];
    }

    // compute the scaled geomagnetic field strength B (in uT but scaled by FMATRIXSCALING)
    pthisMagCal->ftrB = sqrtf(pthisMagCal->fvecA[3] + pthisMagCal->ftrV[CHX] *
                              pthisMagCal->ftrV[CHX] + pthisMagCal->ftrV[CHY] *
                              pthisMagCal->ftrV[CHY] + pthisMagCal->ftrV[CHZ] *
                              pthisMagCal->ftrV[CHZ]);

    // calculate the trial fit error (percent) normalized to number of measurements and scaled geomagnetic field strength
    pthisMagCal->ftrFitErrorpc = sqrtf(fE / (float) pthisMagBuffer->iMagBufferCount) * 100.0F / (2.0F * pthisMagCal->ftrB * pthisMagCal->ftrB);

    // correct the hard iron estimate for FMATRIXSCALING and the offsets applied (result in uT)
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] *
            DEFAULTB +
            (float) iOffset[l] *
            pthisMag->fuTPerCount;
    }

    // correct the geomagnetic field strength B to correct scaling (result in uT)
    pthisMagCal->ftrB *= DEFAULTB;

    return;
}

// 7 element calibration using direct eigen-decomposition
void fComputeMagCalibration7(struct MagCalibration *pthisMagCal,
                             struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    float   det;        // matrix determinant
    float   fscaling;   // set to FUTPERCOUNT * FMATRIXSCALING
    float   ftmp;       // scratch variable
    int16   iOffset[3]; // offset to remove large DC hard iron bias
    int16   iCount;     // number of measurements counted
    int8    i,
            j,
            k,
            l,
            m,
            n;          // loop counters

    // compute fscaling to reduce multiplications later
    fscaling = pthisMag->fuTPerCount / DEFAULTB;

    // the offsets are guaranteed to be set from the first element but to avoid compiler error
    iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

    // zero the on and above diagonal elements of the 7x7 symmetric measurement matrix fmatA
    for (m = 0; m < 7; m++)
    {
        for (n = m; n < 7; n++)
        {
            pthisMagCal->fmatA[m][n] = 0.0F;
        }
    }

    // add megnetic buffer entries into product matrix fmatA
    iCount = 0;
    for (j = 0; j < MAGBUFFSIZEX; j++)
    {
        for (k = 0; k < MAGBUFFSIZEY; k++)
        {
            if (pthisMagBuffer->index[j][k] != -1)
            {
                // use first valid magnetic buffer entry as offset estimate (bit counts)
                if (iCount == 0)
                {
                    for (l = CHX; l <= CHZ; l++)
                    {
                        iOffset[l] = pthisMagBuffer->iBs[l][j][k];
                    }
                }

                // apply the offset and scaling and store in fvecA
                for (l = CHX; l <= CHZ; l++)
                {
                    pthisMagCal->fvecA[l + 3] = (float)
                        (
                            (int32) pthisMagBuffer->iBs[l][j][k] -
                            (int32) iOffset[l]
                        ) * fscaling;
                    pthisMagCal->fvecA[l] = pthisMagCal->fvecA[l + 3] * pthisMagCal->fvecA[l + 3];
                }

                // accumulate the on-and above-diagonal terms of pthisMagCal->fmatA=Sigma{fvecA^T * fvecA}
                // with the exception of fmatA[6][6] which will sum to the number of measurements
                // and remembering that fvecA[6] equals 1.0F
                // update the right hand column [6] of fmatA except for fmatA[6][6]
                for (m = 0; m < 6; m++)
                {
                    pthisMagCal->fmatA[m][6] += pthisMagCal->fvecA[m];
                }

                // update the on and above diagonal terms except for right hand column 6
                for (m = 0; m < 6; m++)
                {
                    for (n = m; n < 6; n++)
                    {
                        pthisMagCal->fmatA[m][n] += pthisMagCal->fvecA[m] * pthisMagCal->fvecA[n];
                    }
                }

                // increment the measurement counter for the next iteration
                iCount++;
            }
        }
    }

    // finally set the last element fmatA[6][6] to the number of measurements
    pthisMagCal->fmatA[6][6] = (float) iCount;

    // store the number of measurements accumulated (defensive programming, should never be needed)
    pthisMagBuffer->iMagBufferCount = iCount;

    // copy the above diagonal elements of fmatA to below the diagonal
    for (m = 1; m < 7; m++)
    {
        for (n = 0; n < m; n++)
        {
            pthisMagCal->fmatA[m][n] = pthisMagCal->fmatA[n][m];
        }
    }

    // set tmpA7x1 to the unsorted eigenvalues and fmatB to the unsorted eigenvectors of fmatA
    fEigenCompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB,
                    7);

    // find the smallest eigenvalue
    j = 0;
    for (i = 1; i < 7; i++)
    {
        if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[j])
        {
            j = i;
        }
    }

    // set ellipsoid matrix A to the solution vector with smallest eigenvalue, compute its determinant
    // and the hard iron offset (scaled and offset)
    f3x3matrixAeqScalar(pthisMagCal->fA, 0.0F);
    det = 1.0F;
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->fA[l][l] = pthisMagCal->fmatB[l][j];
        det *= pthisMagCal->fA[l][l];
        pthisMagCal->ftrV[l] = -0.5F *
            pthisMagCal->fmatB[l + 3][j] /
            pthisMagCal->fA[l][l];
    }

    // negate A if it has negative determinant
    if (det < 0.0F)
    {
        f3x3matrixAeqMinusA(pthisMagCal->fA);
        pthisMagCal->fmatB[6][j] = -pthisMagCal->fmatB[6][j];
        det = -det;
    }

    // set ftmp to the square of the trial geomagnetic field strength B (counts times FMATRIXSCALING)
    ftmp = -pthisMagCal->fmatB[6][j];
    for (l = CHX; l <= CHZ; l++)
    {
        ftmp += pthisMagCal->fA[l][l] *
            pthisMagCal->ftrV[l] *
            pthisMagCal->ftrV[l];
    }

    // normalize the ellipsoid matrix A to unit determinant
    f3x3matrixAeqAxScalar(pthisMagCal->fA, powf(det, -(ONETHIRD)));

    // convert the geomagnetic field strength B into uT for normalized soft iron matrix A and normalize
    pthisMagCal->ftrB = sqrtf(fabsf(ftmp)) * DEFAULTB * powf(det, -(ONESIXTH));

    // compute trial invW from the square root of A also with normalized determinant and hard iron offset in uT
    f3x3matrixAeqI(pthisMagCal->ftrinvW);
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->ftrinvW[l][l] = sqrtf(fabsf(pthisMagCal->fA[l][l]));
        pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] *
            DEFAULTB +
            (float) iOffset[l] *
            pthisMag->fuTPerCount;
    }

    return;
}

// 10 element calibration using direct eigen-decomposition
void fComputeMagCalibration10(struct MagCalibration *pthisMagCal,
                              struct MagBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
    // local variables
    float   det;            // matrix determinant
    float   fscaling;       // set to FUTPERCOUNT * FMATRIXSCALING
    float   ftmp;           // scratch variable
    int16   iOffset[3];     // offset to remove large DC hard iron bias in matrix
    int16   iCount;         // number of measurements counted
    int8    i,
            j,
            k,
            l,
            m,
            n;              // loop counters

    // compute fscaling to reduce multiplications later
    fscaling = pthisMag->fuTPerCount / DEFAULTB;

    // the offsets are guaranteed to be set from the first element but to avoid compiler error
    iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

    // zero the on and above diagonal elements of the 10x10 symmetric measurement matrix fmatA
    for (m = 0; m < 10; m++)
    {
        for (n = m; n < 10; n++)
        {
            pthisMagCal->fmatA[m][n] = 0.0F;
        }
    }

    // add magnetic buffer entries into the 10x10 product matrix fmatA
    iCount = 0;
    for (j = 0; j < MAGBUFFSIZEX; j++)
    {
        for (k = 0; k < MAGBUFFSIZEY; k++)
        {
            if (pthisMagBuffer->index[j][k] != -1)
            {
                // use first valid magnetic buffer entry as estimate for offset to help solution (bit counts)
                if (iCount == 0)
                {
                    for (l = CHX; l <= CHZ; l++)
                    {
                        iOffset[l] = pthisMagBuffer->iBs[l][j][k];
                    }
                }

                // apply the fixed offset and scaling and enter into fvecA[6-8]
                for (l = CHX; l <= CHZ; l++)
                {
                    pthisMagCal->fvecA[l + 6] = (float)
                        (
                            (int32) pthisMagBuffer->iBs[l][j][k] -
                            (int32) iOffset[l]
                        ) * fscaling;
                }

                // compute measurement vector elements fvecA[0-5] from fvecA[6-8]
                pthisMagCal->fvecA[0] = pthisMagCal->fvecA[6] * pthisMagCal->fvecA[6];
                pthisMagCal->fvecA[1] = 2.0F *
                    pthisMagCal->fvecA[6] *
                    pthisMagCal->fvecA[7];
                pthisMagCal->fvecA[2] = 2.0F *
                    pthisMagCal->fvecA[6] *
                    pthisMagCal->fvecA[8];
                pthisMagCal->fvecA[3] = pthisMagCal->fvecA[7] * pthisMagCal->fvecA[7];
                pthisMagCal->fvecA[4] = 2.0F *
                    pthisMagCal->fvecA[7] *
                    pthisMagCal->fvecA[8];
                pthisMagCal->fvecA[5] = pthisMagCal->fvecA[8] * pthisMagCal->fvecA[8];

                // accumulate the on-and above-diagonal terms of fmatA=Sigma{fvecA^T * fvecA}
                // with the exception of fmatA[9][9] which equals the number of measurements
                // update the right hand column [9] of fmatA[0-8][9] ignoring fmatA[9][9]
                for (m = 0; m < 9; m++)
                {
                    pthisMagCal->fmatA[m][9] += pthisMagCal->fvecA[m];
                }

                // update the on and above diagonal terms of fmatA ignoring right hand column 9
                for (m = 0; m < 9; m++)
                {
                    for (n = m; n < 9; n++)
                    {
                        pthisMagCal->fmatA[m][n] += pthisMagCal->fvecA[m] * pthisMagCal->fvecA[n];
                    }
                }

                // increment the measurement counter for the next iteration
                iCount++;
            }
        }
    }

    // set the last element fmatA[9][9] to the number of measurements
    pthisMagCal->fmatA[9][9] = (float) iCount;

    // store the number of measurements accumulated (defensive programming, should never be needed)
    pthisMagBuffer->iMagBufferCount = iCount;

    // copy the above diagonal elements of symmetric product matrix fmatA to below the diagonal
    for (m = 1; m < 10; m++)
    {
        for (n = 0; n < m; n++)
        {
            pthisMagCal->fmatA[m][n] = pthisMagCal->fmatA[n][m];
        }
    }

    // set pthisMagCal->fvecA to the unsorted eigenvalues and fmatB to the unsorted normalized eigenvectors of fmatA
    fEigenCompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB,
                    10);

    // set ellipsoid matrix A from elements of the solution vector column j with smallest eigenvalue
    j = 0;
    for (i = 1; i < 10; i++)
    {
        if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[j])
        {
            j = i;
        }
    }

    pthisMagCal->fA[0][0] = pthisMagCal->fmatB[0][j];
    pthisMagCal->fA[0][1] = pthisMagCal->fA[1][0] = pthisMagCal->fmatB[1][j];
    pthisMagCal->fA[0][2] = pthisMagCal->fA[2][0] = pthisMagCal->fmatB[2][j];
    pthisMagCal->fA[1][1] = pthisMagCal->fmatB[3][j];
    pthisMagCal->fA[1][2] = pthisMagCal->fA[2][1] = pthisMagCal->fmatB[4][j];
    pthisMagCal->fA[2][2] = pthisMagCal->fmatB[5][j];

    // negate entire solution if A has negative determinant
    det = f3x3matrixDetA(pthisMagCal->fA);
    if (det < 0.0F)
    {
        f3x3matrixAeqMinusA(pthisMagCal->fA);
        pthisMagCal->fmatB[6][j] = -pthisMagCal->fmatB[6][j];
        pthisMagCal->fmatB[7][j] = -pthisMagCal->fmatB[7][j];
        pthisMagCal->fmatB[8][j] = -pthisMagCal->fmatB[8][j];
        pthisMagCal->fmatB[9][j] = -pthisMagCal->fmatB[9][j];
        det = -det;
    }

    // compute the inverse of the ellipsoid matrix
    f3x3matrixAeqInvSymB(pthisMagCal->finvA, pthisMagCal->fA);

    // compute the trial hard iron vector in offset bit counts times FMATRIXSCALING
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->ftrV[l] = 0.0F;
        for (m = CHX; m <= CHZ; m++)
        {
            pthisMagCal->ftrV[l] += pthisMagCal->finvA[l][m] * pthisMagCal->fmatB[m + 6][j];
        }

        pthisMagCal->ftrV[l] *= -0.5F;
    }

    // compute the trial geomagnetic field strength B in bit counts times FMATRIXSCALING
    pthisMagCal->ftrB = sqrtf(fabsf(pthisMagCal->fA[0][0] *
                              pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHX] +
                              2.0F * pthisMagCal->fA[0][1] *
                              pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHY] +
                              2.0F * pthisMagCal->fA[0][2] *
                              pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHZ] +
                              pthisMagCal->fA[1][1] * pthisMagCal->ftrV[CHY] *
                              pthisMagCal->ftrV[CHY] + 2.0F *
                              pthisMagCal->fA[1][2] * pthisMagCal->ftrV[CHY] *
                              pthisMagCal->ftrV[CHZ] + pthisMagCal->fA[2][2] *
                              pthisMagCal->ftrV[CHZ] * pthisMagCal->ftrV[CHZ] -
                              pthisMagCal->fmatB[9][j]));

    // calculate the trial normalized fit error as a percentage
    pthisMagCal->ftrFitErrorpc = 50.0F * sqrtf(fabsf(pthisMagCal->fvecA[j]) /
                                                   (float) pthisMagBuffer->iMagBufferCount) / (pthisMagCal->ftrB * pthisMagCal->ftrB);

    // correct for the measurement matrix offset and scaling and get the computed hard iron offset in uT
    for (l = CHX; l <= CHZ; l++)
    {
        pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] *
            DEFAULTB +
            (float) iOffset[l] *
            pthisMag->fuTPerCount;
    }

    // convert the trial geomagnetic field strength B into uT for un-normalized soft iron matrix A
    pthisMagCal->ftrB *= DEFAULTB;

    // normalize the ellipsoid matrix A to unit determinant and correct B by root of this multiplicative factor
    f3x3matrixAeqAxScalar(pthisMagCal->fA, powf(det, -(ONETHIRD)));
    pthisMagCal->ftrB *= powf(det, -(ONESIXTH));

    // compute trial invW from the square root of fA (both with normalized determinant)
    // set fvecA to the unsorted eigenvalues and fmatB to the unsorted eigenvectors of fmatA
    // where fmatA holds the 3x3 matrix fA in its top left elements
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            pthisMagCal->fmatA[i][j] = pthisMagCal->fA[i][j];
        }
    }

    fEigenCompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB,
                    3);

    // set pthisMagCal->fmatB to be eigenvectors . diag(sqrt(sqrt(eigenvalues))) = fmatB . diag(sqrt(sqrt(fvecA))
    for (j = 0; j < 3; j++) // loop over columns j
    {
        ftmp = sqrtf(sqrtf(fabsf(pthisMagCal->fvecA[j])));
        for (i = 0; i < 3; i++) // loop over rows i
        {
            pthisMagCal->fmatB[i][j] *= ftmp;
        }
    }

    // set ftrinvW to eigenvectors * diag(sqrt(eigenvalues)) * eigenvectors^T
    // = fmatB * fmatB^T = sqrt(fA) (guaranteed symmetric)
    // loop over rows
    for (i = 0; i < 3; i++)
    {
        // loop over on and above diagonal columns
        for (j = i; j < 3; j++)
        {
            pthisMagCal->ftrinvW[i][j] = 0.0F;

            // accumulate the matrix product
            for (k = 0; k < 3; k++)
            {
                pthisMagCal->ftrinvW[i][j] += pthisMagCal->fmatB[i][k] * pthisMagCal->fmatB[j][k];
            }

            // copy to below diagonal element
            pthisMagCal->ftrinvW[j][i] = pthisMagCal->ftrinvW[i][j];
        }
    }

    return;
}
#endif
