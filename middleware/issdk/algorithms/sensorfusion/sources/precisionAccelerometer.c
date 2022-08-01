/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "sensor_fusion.h"
#include "fusion.h"

/*! \file precisionAccelerometer.c
    \brief Implements accelerometer calibration routines
*/

// function resets the accelerometer buffer and accelerometer calibration
void fInitializeAccelCalibration(struct AccelCalibration *pthisAccelCal,
                                 struct AccelBuffer *pthisAccelBuffer,
                                 volatile int8 *AccelCalPacketOn)
{
    float   *pFlash;    // pointer into flash memory
    int8_t  i,
            j;          // loop counters

    // set flags to false to denote no precision accelerometer measurements
    pthisAccelBuffer->iStoreFlags = 0;

    // perform one transmission of the precision calibration (using invalid value MAX_ACCEL_CAL_ORIENTATIONS for calibration only)
    *AccelCalPacketOn = MAX_ACCEL_CAL_ORIENTATIONS;

    // check to see if the stored accelerometer calibration has been erased
    // the standard value for erased flash is 0xFF in each byte but for portability check against 0x12345678
#ifndef SIMULATION
    pFlash = (float *) (CALIBRATION_NVM_ADDR + ACCEL_NVM_OFFSET);
    if (*((uint32 *) pFlash++) == 0x12345678)
    {
        // a precision accelerometer calibration is present in flash
        // copy accelerometer calibration elements (21x float total 84 bytes) from flash to RAM
        for (i = CHX; i <= CHZ; i++) pthisAccelCal->fV[i] = *(pFlash++);
        for (i = CHX; i <= CHZ; i++)
            for (j = CHX; j <= CHZ; j++)
                pthisAccelCal->finvW[i][j] = *(pFlash++);
        for (i = CHX; i <= CHZ; i++)
            for (j = CHX; j <= CHZ; j++)
                pthisAccelCal->fR0[i][j] = *(pFlash++);
    }
    else
    {
#endif
        // flash has been erased and no accelerometer calibration is present
        // initialize the precision accelerometer calibration in RAM to null default
        pthisAccelCal->fV[CHX] = pthisAccelCal->fV[CHY] = pthisAccelCal->fV[CHZ] = 0.0F;
        f3x3matrixAeqI(pthisAccelCal->finvW);
        f3x3matrixAeqI(pthisAccelCal->fR0);
#ifndef SIMULATION
    }
#endif

    // set current averaging location and counter to -1 for invalid
    pthisAccelBuffer->iStoreLocation = pthisAccelBuffer->iStoreCounter = -1;

    return;
}

void fUpdateAccelBuffer(struct AccelCalibration *pthisAccelCal,
                        struct AccelBuffer *pthisAccelBuffer,
                        struct AccelSensor *pthisAccel, volatile int8 *AccelCalPacketOn)
{
    int16_t i;          // loop counter

    // iStoreCounter > 0: precision measurements are still on-going
    // iStoreCounter = 0: the precision measurement has just finished
    // iStoreCounter = -1: no precision measurement is in progress
    // check if a new precision measurement has started and zero sums if one has
    if (pthisAccelBuffer->iStoreCounter == (ACCEL_CAL_AVERAGING_SECS * FUSION_HZ))
    {
        for (i = CHX; i <= CHZ; i++) pthisAccelBuffer->fSumGs[i] = 0.0F;
    }

    // accumulate sum if averaging not yet complete
    if (pthisAccelBuffer->iStoreCounter > 0)
    {
        for (i = CHX; i <= CHZ; i++)
            pthisAccelBuffer->fSumGs[i] += pthisAccel->fGs[i];
        pthisAccelBuffer->iStoreCounter--;
    }

    // check if the measurement accumulation is complete and, if so, store average and set packet transmit flag
    if (pthisAccelBuffer->iStoreCounter == 0)
    {
        // store the measurement, set the relevant flag and decrement the counter down to -1 denoting completion
        for (i = CHX; i <= CHZ; i++)
        {
            pthisAccelBuffer->fGsStored[pthisAccelBuffer->iStoreLocation][i] =
                    pthisAccelBuffer->fSumGs[i] /
                (float) (ACCEL_CAL_AVERAGING_SECS * FUSION_HZ);
        }

        pthisAccelBuffer->iStoreFlags |=
            (
                1 <<
                pthisAccelBuffer->iStoreLocation
            );
        pthisAccelBuffer->iStoreCounter--;

        // compute the new precision accelerometer calibration including rotation using all measurements
        fRunAccelCalibration(pthisAccelCal, pthisAccelBuffer, pthisAccel);

        // and make one packet transmission of this measurement with the new calibration
        *AccelCalPacketOn = pthisAccelBuffer->iStoreLocation;
    }

    return;
}

// function maps the accelerometer data fGs (g) onto precision calibrated and de-rotated data fGc (g), iGc (counts)
void fInvertAccelCal(struct AccelSensor *pthisAccel,
                     struct AccelCalibration *pthisAccelCal)
{
    // local variables
    float   ftmp[3];    // temporary array
    int8_t  i;          // loop counter

    //subtract the offset vector fV (g): ftmp[]=fGs[]-V[]
    for (i = CHX; i <= CHZ; i++)
        ftmp[i] = pthisAccel->fGs[i] - pthisAccelCal->fV[i];

    // apply the inverse rotation correction matrix finvW: fGc=inv(W)*(fGs[]-V[])
    for (i = CHX; i <= CHZ; i++)
    {
        pthisAccel->fGc[i] = pthisAccelCal->finvW[i][CHX] *
            ftmp[CHX] +
            pthisAccelCal->finvW[i][CHY] *
            ftmp[CHY] +
            pthisAccelCal->finvW[i][CHZ] *
            ftmp[CHZ];
    }

    // apply the inverse of the forward rotation matrix fR0: fGc=inv(R).inv(W)*(fGs[]-V[])
    for (i = CHX; i <= CHZ; i++) ftmp[i] = pthisAccel->fGc[i];
    for (i = CHX; i <= CHZ; i++)
    {
        pthisAccel->fGc[i] = pthisAccelCal->fR0[CHX][i] *
            ftmp[CHX] +
            pthisAccelCal->fR0[CHY][i] *
            ftmp[CHY] +
            pthisAccelCal->fR0[CHZ][i] *
            ftmp[CHZ];
        pthisAccel->iGc[i] = (int16_t) (pthisAccel->fGc[i] * pthisAccel->iCountsPerg);
    }

    return;
}

// function runs the precision accelerometer calibration
void fRunAccelCalibration(struct AccelCalibration *pthisAccelCal,
                          struct AccelBuffer *pthisAccelBuffer,
                          struct AccelSensor *pthisAccel)
{
    float   fGc0[3];        // calibrated but not de-rotated measurement 0
    uint8_t iMeasurements;  // number of stored measurements
    int8_t  i;              // loop counters

    // calculate how many measurements are present in the accelerometer measurement buffer
    iMeasurements = 0;
    for (i = 0; i < MAX_ACCEL_CAL_ORIENTATIONS; i++)
    {
        if (pthisAccelBuffer->iStoreFlags & (1 << i)) iMeasurements++;
    }

    // perform the highest quality calibration possible given this number
    if (iMeasurements >= 9)
    {
        // perform the 10 element calibration
        fComputeAccelCalibration10(pthisAccelBuffer, pthisAccelCal, pthisAccel);
    }
    else if (iMeasurements >= 6)
    {
        // perform the 7 element calibration
        fComputeAccelCalibration7(pthisAccelBuffer, pthisAccelCal, pthisAccel);
    }
    else if (iMeasurements >= 4)
    {
        // perform the 4 element calibration
        fComputeAccelCalibration4(pthisAccelBuffer, pthisAccelCal, pthisAccel);
    }

    // calculate the rotation correction matrix to rotate calibrated measurement 0 to flat
    if (pthisAccelBuffer->iStoreFlags & 1)
    {
        // apply offset and gain calibration but not rotation to measurement 0 (flat) if present
        // set ftmpA3x1 = invW . (fGs - fV)
        for (i = CHX; i <= CHZ; i++)
            fGc0[i] = pthisAccelBuffer->fGsStored[0][i] - pthisAccelCal->fV[i];
        fVeq3x3AxV(fGc0, pthisAccelCal->finvW);

        // compute the new final rotation matrix if rotation 0 (flat) is present.
        // multiplying by the transpose of this matrix therefore forces measurement zero to flat.
#if THISCOORDSYSTEM == NED
                f3DOFTiltNED(pthisAccelCal->fR0, fGc0);
#endif
#if THISCOORDSYSTEM == ANDROID
                f3DOFTiltAndroid(pthisAccelCal->fR0, fGc0);
#endif
#if THISCOORDSYSTEM == WIN8
                f3DOFTiltWin8(pthisAccelCal->fR0, fGc0);
#endif
    }

    return;
}

// calculate the 4 element calibration from the available measurements
void fComputeAccelCalibration4(struct AccelBuffer *pthisAccelBuffer,
                               struct AccelCalibration *pthisAccelCal,
                               struct AccelSensor *pthisAccel)
{
    int32   i,
            j;      // loop counters
    float   ftmp;   // scratch
    int8_t  ierror; // flag from matrix inversion

    // working arrays for 4x4 matrix inversion
    float   *pfRows[4];
    int8_t  iColInd[4];
    int8_t  iRowInd[4];
    int8_t  iPivot[4];

    // zero the 4x4 matrix XTX (in upper left of fmatA) and 4x1 vector XTY (in upper fvecA)
    for (i = 0; i < 4; i++)
    {
        pthisAccelCal->fvecA[i] = 0.0F;
        for (j = 0; j < 4; j++)
        {
            pthisAccelCal->fmatA[i][j] = 0.0F;
        }
    }

    // accumulate fXTY (in fvecA) and fXTX4x4 (in fmatA)
    for (i = 0; i < MAX_ACCEL_CAL_ORIENTATIONS; i++)
    {
        // accumulate vector X^T.Y if this entry is valid
        if ((pthisAccelBuffer->iStoreFlags) & (1 << i))
        {
            ftmp = pthisAccelBuffer->fGsStored[i][CHX] *
                pthisAccelBuffer->fGsStored[i][CHX] +
                pthisAccelBuffer->fGsStored[i][CHY] *
                pthisAccelBuffer->fGsStored[i][CHY] +
                pthisAccelBuffer->fGsStored[i][CHZ] *
                pthisAccelBuffer->fGsStored[i][CHZ];
            pthisAccelCal->fvecA[0] += pthisAccelBuffer->fGsStored[i][CHX] * ftmp;
            pthisAccelCal->fvecA[1] += pthisAccelBuffer->fGsStored[i][CHY] * ftmp;
            pthisAccelCal->fvecA[2] += pthisAccelBuffer->fGsStored[i][CHZ] * ftmp;
            pthisAccelCal->fvecA[3] += ftmp;

            // accumulate above diagonal terms of matrix X^T.X
            pthisAccelCal->fmatA[CHX][CHX] += pthisAccelBuffer->fGsStored[i][
                    CHX] *
                pthisAccelBuffer->fGsStored[i][CHX];
            pthisAccelCal->fmatA[CHX][CHY] += pthisAccelBuffer->fGsStored[i][
                    CHX] *
                pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fmatA[CHX][CHZ] += pthisAccelBuffer->fGsStored[i][
                    CHX] *
                pthisAccelBuffer->fGsStored[i][CHZ];
            pthisAccelCal->fmatA[CHX][3] += pthisAccelBuffer->fGsStored[i][CHX];
            pthisAccelCal->fmatA[CHY][CHY] += pthisAccelBuffer->fGsStored[i][
                    CHY] *
                pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fmatA[CHY][CHZ] += pthisAccelBuffer->fGsStored[i][
                    CHY] *
                pthisAccelBuffer->fGsStored[i][CHZ];;
            pthisAccelCal->fmatA[CHY][3] += pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fmatA[CHZ][CHZ] += pthisAccelBuffer->fGsStored[i][
                    CHZ] *
                pthisAccelBuffer->fGsStored[i][CHZ];;
            pthisAccelCal->fmatA[CHZ][3] += pthisAccelBuffer->fGsStored[i][CHZ];
            pthisAccelCal->fmatA[3][3] += 1.0F;
        }
    }

    // copy above diagonal elements of fXTX4x4 = X^T.X to below diagonal elements
    pthisAccelCal->fmatA[CHY][CHX] = pthisAccelCal->fmatA[CHX][CHY];
    pthisAccelCal->fmatA[CHZ][CHX] = pthisAccelCal->fmatA[CHX][CHZ];
    pthisAccelCal->fmatA[CHZ][CHY] = pthisAccelCal->fmatA[CHY][CHZ];
    pthisAccelCal->fmatA[3][CHX] = pthisAccelCal->fmatA[CHX][3];
    pthisAccelCal->fmatA[3][CHY] = pthisAccelCal->fmatA[CHY][3];
    pthisAccelCal->fmatA[3][CHZ] = pthisAccelCal->fmatA[CHZ][3];

    // calculate in situ inverse of X^T.X
    for (i = 0; i < 4; i++)
    {
        pfRows[i] = pthisAccelCal->fmatA[i];
    }

    fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 4, &ierror);

    // calculate the solution vector fvecB = inv(X^T.X).X^T.Y
    for (i = 0; i < 4; i++)
    {
        pthisAccelCal->fvecB[i] = 0.0F;
        for (j = 0; j < 4; j++)
        {
            pthisAccelCal->fvecB[i] += pthisAccelCal->fmatA[i][j] * pthisAccelCal->fvecA[j];
        }
    }

    // extract the offset vector
    pthisAccelCal->fV[CHX] = 0.5F * pthisAccelCal->fvecB[CHX];
    pthisAccelCal->fV[CHY] = 0.5F * pthisAccelCal->fvecB[CHY];
    pthisAccelCal->fV[CHZ] = 0.5F * pthisAccelCal->fvecB[CHZ];

    // set ftmp to 1/W where W is the forward gain to fit the 1g sphere
    ftmp = 1.0F / sqrtf(fabsf(pthisAccelCal->fvecB[3] + pthisAccelCal->fV[CHX] *
                        pthisAccelCal->fV[CHX] + pthisAccelCal->fV[CHY] *
                        pthisAccelCal->fV[CHY] + pthisAccelCal->fV[CHZ] *
                        pthisAccelCal->fV[CHZ]));

    // copy the inverse gain 1/W to the inverse gain matrix
    pthisAccelCal->finvW[CHX][CHY] = pthisAccelCal->finvW[CHY][CHX] = 0.0F;
    pthisAccelCal->finvW[CHX][CHZ] = pthisAccelCal->finvW[CHZ][CHX] = 0.0F;
    pthisAccelCal->finvW[CHY][CHZ] = pthisAccelCal->finvW[CHZ][CHY] = 0.0F;
    pthisAccelCal->finvW[CHX][CHX] = pthisAccelCal->finvW[CHY][CHY] = pthisAccelCal->finvW[CHZ][CHZ] = ftmp;

    return;
}

// calculate the 7 element calibration from the available measurements
void fComputeAccelCalibration7(struct AccelBuffer *pthisAccelBuffer,
                               struct AccelCalibration *pthisAccelCal,
                               struct AccelSensor *pthisAccel)
{
    int32   i,
            j,
            m,
            n;      // loop counters
    float   det;    // matrix determinant
    float   fg0;    // fitted local gravity magnitude

    // zero the on and above diagonal elements of the 7x7 symmetric measurement matrix fmatA
    for (i = 0; i < 7; i++)
        for (j = i; j < 7; j++) pthisAccelCal->fmatA[i][j] = 0.0F;

    // last entry of vector fvecA is always 1.0 so move assignment outside the loop
    pthisAccelCal->fvecA[6] = 1.0F;

    // loop over all orientations
    for (i = 0; i < MAX_ACCEL_CAL_ORIENTATIONS; i++)
    {
        // accumulate fvecA if this entry is valid
        if ((pthisAccelBuffer->iStoreFlags) & (1 << i))
        {
            // compute the remaining members of the measurement vector fvecA
            pthisAccelCal->fvecA[0] = pthisAccelBuffer->fGsStored[i][CHX] * pthisAccelBuffer->fGsStored[i][CHX];
            pthisAccelCal->fvecA[1] = pthisAccelBuffer->fGsStored[i][CHY] * pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fvecA[2] = pthisAccelBuffer->fGsStored[i][CHZ] * pthisAccelBuffer->fGsStored[i][CHZ];
            pthisAccelCal->fvecA[3] = pthisAccelBuffer->fGsStored[i][CHX];
            pthisAccelCal->fvecA[4] = pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fvecA[5] = pthisAccelBuffer->fGsStored[i][CHZ];

            // accumulate the on-and above-diagonal terms of fmatA=Sigma{fvecA^T * fvecA}
            for (m = 0; m < 7; m++)
                for (n = m; n < 7; n++)
                    pthisAccelCal->fmatA[m][n] += pthisAccelCal->fvecA[m] * pthisAccelCal->fvecA[n];
        }           // end of test for stored data
    }               // end of loop over orientations

    // copy the above diagonal elements of symmetric product matrix fmatA to below the diagonal
    for (m = 1; m < 7; m++)
        for (n = 0; n < m; n++)
            pthisAccelCal->fmatA[m][n] = pthisAccelCal->fmatA[n][m];

    // set fvecA to the unsorted eigenvalues and fmatB to the unsorted normalized eigenvectors of fmatA
    fEigenCompute10(pthisAccelCal->fmatA, pthisAccelCal->fvecA,
                    pthisAccelCal->fmatB, 7);

    // set ellipsoid matrix A from elements of the solution vector column j with smallest eigenvalue
    j = 0;
    for (i = 1; i < 7; i++)
        if (pthisAccelCal->fvecA[i] < pthisAccelCal->fvecA[j]) j = i;

    // negate the entire solution vector if ellipsoid matrix has negative determinant
    det = pthisAccelCal->fmatB[0][j] *
        pthisAccelCal->fmatB[1][j] *
        pthisAccelCal->fmatB[2][j];
    if (det < 0.0F)
    {
        for (i = 0; i < 7; i++)
        {
            pthisAccelCal->fmatB[i][j] = -pthisAccelCal->fmatB[i][j];
        }
    }

    // compute invW and V and fitted gravity g0 from solution vector j
    f3x3matrixAeqScalar(pthisAccelCal->finvW, 0.0F);
    pthisAccelCal->finvW[CHX][CHX] = sqrtf(fabsf(pthisAccelCal->fmatB[0][j]));
    pthisAccelCal->finvW[CHY][CHY] = sqrtf(fabsf(pthisAccelCal->fmatB[1][j]));
    pthisAccelCal->finvW[CHZ][CHZ] = sqrtf(fabsf(pthisAccelCal->fmatB[2][j]));
    pthisAccelCal->fV[CHX] = -0.5F *
        pthisAccelCal->fmatB[3][j] /
        pthisAccelCal->fmatB[0][j];
    pthisAccelCal->fV[CHY] = -0.5F *
        pthisAccelCal->fmatB[4][j] /
        pthisAccelCal->fmatB[1][j];
    pthisAccelCal->fV[CHZ] = -0.5F *
        pthisAccelCal->fmatB[5][j] /
        pthisAccelCal->fmatB[2][j];
    fg0 = sqrtf(fabsf(pthisAccelCal->fmatB[0][j] * pthisAccelCal->fV[CHX] *
                pthisAccelCal->fV[CHX] + pthisAccelCal->fmatB[1][j] *
                pthisAccelCal->fV[CHY] * pthisAccelCal->fV[CHY] +
                pthisAccelCal->fmatB[2][j] * pthisAccelCal->fV[CHZ] *
                pthisAccelCal->fV[CHZ] - pthisAccelCal->fmatB[6][j]));

    // normalize invW to fit the 1g sphere
    pthisAccelCal->finvW[CHX][CHX] /= fg0;
    pthisAccelCal->finvW[CHY][CHY] /= fg0;
    pthisAccelCal->finvW[CHZ][CHZ] /= fg0;

    return;
}

// calculate the 10 element calibration from the available measurements
void fComputeAccelCalibration10(struct AccelBuffer *pthisAccelBuffer,
                                struct AccelCalibration *pthisAccelCal,
                                struct AccelSensor *pthisAccel)
{
    int32   i,
            j,
            k,
            l,
            m,
            n;                  // loop counters
    float   det;                // matrix determinant
    float   ftmp;               // scratch
    float   fg0;                // fitted local gravity magnitude

    // zero the on and above diagonal elements of the 10x10 symmetric measurement matrix fmatA
    for (i = 0; i < 10; i++)
        for (j = i; j < 10; j++) pthisAccelCal->fmatA[i][j] = 0.0F;

    // last entry of vector fvecA is always 1.0 so move assignment outside the loop
    pthisAccelCal->fvecA[9] = 1.0F;

    // loop over all orientations
    for (i = 0; i < MAX_ACCEL_CAL_ORIENTATIONS; i++)
    {
        // accumulate fvecA if this entry is valid
        if ((pthisAccelBuffer->iStoreFlags) & (1 << i))
        {
            // compute the remaining members of the measurement vector fvecA
            pthisAccelCal->fvecA[6] = pthisAccelBuffer->fGsStored[i][CHX];
            pthisAccelCal->fvecA[7] = pthisAccelBuffer->fGsStored[i][CHY];
            pthisAccelCal->fvecA[8] = pthisAccelBuffer->fGsStored[i][CHZ];
            pthisAccelCal->fvecA[0] = pthisAccelCal->fvecA[6] * pthisAccelCal->fvecA[6];
            pthisAccelCal->fvecA[1] = 2.0F *
                pthisAccelCal->fvecA[6] *
                pthisAccelCal->fvecA[7];
            pthisAccelCal->fvecA[2] = 2.0F *
                pthisAccelCal->fvecA[6] *
                pthisAccelCal->fvecA[8];
            pthisAccelCal->fvecA[3] = pthisAccelCal->fvecA[7] * pthisAccelCal->fvecA[7];
            pthisAccelCal->fvecA[4] = 2.0F *
                pthisAccelCal->fvecA[7] *
                pthisAccelCal->fvecA[8];
            pthisAccelCal->fvecA[5] = pthisAccelCal->fvecA[8] * pthisAccelCal->fvecA[8];

            // accumulate the on-and above-diagonal terms of fmatA=Sigma{fvecA^T * fvecA}
            for (m = 0; m < 10; m++)
            {
                for (n = m; n < 10; n++)
                {
                    pthisAccelCal->fmatA[m][n] += pthisAccelCal->fvecA[m] * pthisAccelCal->fvecA[n];
                }
            }
        }                       // end of test for stored data
    }                           // end of loop over orientations

    // copy the above diagonal elements of symmetric product matrix fmatA to below the diagonal
    for (m = 1; m < 10; m++)
        for (n = 0; n < m; n++)
            pthisAccelCal->fmatA[m][n] = pthisAccelCal->fmatA[n][m];

    // set fvecA to the unsorted eigenvalues and fmatB to the unsorted normalized eigenvectors of fmatA
    fEigenCompute10(pthisAccelCal->fmatA, pthisAccelCal->fvecA,
                    pthisAccelCal->fmatB, 10);

    // set ellipsoid matrix A from elements of the solution vector column j with smallest eigenvalue
    j = 0;
    for (i = 1; i < 10; i++)
    {
        if (pthisAccelCal->fvecA[i] < pthisAccelCal->fvecA[j])
        {
            j = i;
        }
    }

    pthisAccelCal->fA[0][0] = pthisAccelCal->fmatB[0][j];
    pthisAccelCal->fA[0][1] = pthisAccelCal->fA[1][0] = pthisAccelCal->fmatB[1][j];
    pthisAccelCal->fA[0][2] = pthisAccelCal->fA[2][0] = pthisAccelCal->fmatB[2][j];
    pthisAccelCal->fA[1][1] = pthisAccelCal->fmatB[3][j];
    pthisAccelCal->fA[1][2] = pthisAccelCal->fA[2][1] = pthisAccelCal->fmatB[4][j];
    pthisAccelCal->fA[2][2] = pthisAccelCal->fmatB[5][j];

    // negate entire solution if A has negative determinant
    det = f3x3matrixDetA(pthisAccelCal->fA);
    if (det < 0.0F)
    {
        f3x3matrixAeqMinusA(pthisAccelCal->fA);
        pthisAccelCal->fmatB[6][j] = -pthisAccelCal->fmatB[6][j];
        pthisAccelCal->fmatB[7][j] = -pthisAccelCal->fmatB[7][j];
        pthisAccelCal->fmatB[8][j] = -pthisAccelCal->fmatB[8][j];
        pthisAccelCal->fmatB[9][j] = -pthisAccelCal->fmatB[9][j];
        det = -det;
    }

    // compute the inverse of the ellipsoid matrix
    f3x3matrixAeqInvSymB(pthisAccelCal->finvA, pthisAccelCal->fA);

    // compute the offset vector V
    for (l = CHX; l <= CHZ; l++)
    {
        pthisAccelCal->fV[l] = 0.0F;
        for (m = CHX; m <= CHZ; m++)
        {
            pthisAccelCal->fV[l] += pthisAccelCal->finvA[l][m] * pthisAccelCal->fmatB[m + 6][j];
        }

        pthisAccelCal->fV[l] *= -0.5F;
    }

    // compute the local gravity fit to these calibration coefficients
    fg0 = sqrtf(fabsf(pthisAccelCal->fA[0][0] * pthisAccelCal->fV[CHX] *
                pthisAccelCal->fV[CHX] + 2.0F * pthisAccelCal->fA[0][1] *
                pthisAccelCal->fV[CHX] * pthisAccelCal->fV[CHY] + 2.0F *
                pthisAccelCal->fA[0][2] * pthisAccelCal->fV[CHX] *
                pthisAccelCal->fV[CHZ] + pthisAccelCal->fA[1][1] *
                pthisAccelCal->fV[CHY] * pthisAccelCal->fV[CHY] + 2.0F *
                pthisAccelCal->fA[1][2] * pthisAccelCal->fV[CHY] *
                pthisAccelCal->fV[CHZ] + pthisAccelCal->fA[2][2] *
                pthisAccelCal->fV[CHZ] * pthisAccelCal->fV[CHZ] -
                pthisAccelCal->fmatB[9][j]));

    // compute trial invW from the square root of fA	
    // set fvecA to the unsorted eigenvalues and fmatB to the unsorted eigenvectors of fmatA
    // where fmatA holds the 3x3 matrix fA in its top left elements
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            pthisAccelCal->fmatA[i][j] = pthisAccelCal->fA[i][j];
    fEigenCompute10(pthisAccelCal->fmatA, pthisAccelCal->fvecA,
                    pthisAccelCal->fmatB, 3);

    // set fmatB to be eigenvectors . diag(sqrt(sqrt(eigenvalues))) = fmatB . diag(sqrt(sqrt(fvecA))
    for (j = 0; j < 3; j++)     // loop over columns j
    {
        ftmp = sqrtf(sqrtf(fabsf(pthisAccelCal->fvecA[j])));
        for (i = 0; i < 3; i++) // loop over rows i
        {
            pthisAccelCal->fmatB[i][j] *= ftmp;
        }
    }

    // set finvW to eigenvectors * diag(sqrt(eigenvalues)) * eigenvectors^T
    // = fmatB * fmatB^T = sqrt(fA) (guaranteed symmetric)
    // loop over rows
    for (i = 0; i < 3; i++)
    {
        // loop over on and above diagonal columns
        for (j = i; j < 3; j++)
        {
            pthisAccelCal->finvW[i][j] = 0.0F;

            // accumulate the matrix product
            for (k = 0; k < 3; k++)
            {
                pthisAccelCal->finvW[i][j] += pthisAccelCal->fmatB[i][k] * pthisAccelCal->fmatB[j][k];
            }

            // copy to below diagonal element
            pthisAccelCal->finvW[j][i] = pthisAccelCal->finvW[i][j];
        }
    }

    // scale finvW so that the calibrated measurements fit on the 1g sphere
    for (i = CHX; i <= CHZ; i++)
    {
        for (j = CHX; j <= CHZ; j++)
        {
            pthisAccelCal->finvW[i][j] /= fg0;
        }
    }

    return;
}
