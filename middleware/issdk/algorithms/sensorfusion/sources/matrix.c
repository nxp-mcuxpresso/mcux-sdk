/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file matrix.c
    \brief Matrix manipulation functions

    Contains functions for basic manipulation of 3x3 matrices
*/

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"

#include "sensor_fusion.h"
#include "matrix.h"

// compile time constants that are private to this file
#define CORRUPTMATRIX   0.001F  // column vector modulus limit for rotation matrix

// function sets the 3x3 matrix A to the identity matrix
void f3x3matrixAeqI(float A[][3])
{
    float   *pAij;  // pointer to A[i][j]
    int8    i,
            j;      // loop counters
    for (i = 0; i < 3; i++)
    {
        // set pAij to &A[i][j=0]
        pAij = A[i];
        for (j = 0; j < 3; j++)
        {
            *(pAij++) = 0.0F;
        }

        A[i][i] = 1.0F;
    }

    return;
}

// function sets 3x3 matrix A to 3x3 matrix B
void f3x3matrixAeqB(float A[][3], float B[][3])
{
    float   *pAij;  // pointer to A[i][j]
    float   *pBij;  // pointer to B[i][j]
    int8    i,
            j;      // loop counters
    for (i = 0; i < 3; i++)
    {
        // set pAij to &A[i][j=0] and pBij to &B[i][j=0]
        pAij = A[i];
        pBij = B[i];
        for (j = 0; j < 3; j++)
        {
            *(pAij++) = *(pBij++);
        }
    }

    return;
}

// function sets the matrix A to the identity matrix
void fmatrixAeqI(float *A[], int16 rc)
{
    // rc = rows and columns in A
    float   *pAij;  // pointer to A[i][j]
    int8    i,
            j;      // loop counters
    for (i = 0; i < rc; i++)
    {
        // set pAij to &A[i][j=0]
        pAij = A[i];
        for (j = 0; j < rc; j++)
        {
            *(pAij++) = 0.0F;
        }

        A[i][i] = 1.0F;
    }

    return;
}

// function sets every entry in the 3x3 matrix A to a constant scalar
void f3x3matrixAeqScalar(float A[][3], float Scalar)
{
    float   *pAij;  // pointer to A[i][j]
    int8    i,
            j;      // counters
    for (i = 0; i < 3; i++)
    {
        // set pAij to &A[i][j=0]
        pAij = A[i];
        for (j = 0; j < 3; j++)
        {
            *(pAij++) = Scalar;
        }
    }

    return;
}

// function multiplies all elements of 3x3 matrix A by the specified scalar
void f3x3matrixAeqAxScalar(float A[][3], float Scalar)
{
    float   *pAij;  // pointer to A[i][j]
    int8    i,
            j;      // loop counters
    for (i = 0; i < 3; i++)
    {
        // set pAij to &A[i][j=0]
        pAij = A[i];
        for (j = 0; j < 3; j++)
        {
            *(pAij++) *= Scalar;
        }
    }

    return;
}

// function negates all elements of 3x3 matrix A
void f3x3matrixAeqMinusA(float A[][3])
{
    float   *pAij;  // pointer to A[i][j]
    int8    i,
            j;      // loop counters
    for (i = 0; i < 3; i++)
    {
        // set pAij to &A[i][j=0]
        pAij = A[i];
        for (j = 0; j < 3; j++)
        {
            *pAij = -*pAij;
            pAij++;
        }
    }

    return;
}

// function directly calculates the symmetric inverse of a symmetric 3x3 matrix
// only the on and above diagonal terms in B are used and need to be specified
void f3x3matrixAeqInvSymB(float A[][3], float B[][3])
{
    float   fB11B22mB12B12; // B[1][1] * B[2][2] - B[1][2] * B[1][2]
    float   fB12B02mB01B22; // B[1][2] * B[0][2] - B[0][1] * B[2][2]
    float   fB01B12mB11B02; // B[0][1] * B[1][2] - B[1][1] * B[0][2]
    float   ftmp;           // determinant and then reciprocal

    // calculate useful products
    fB11B22mB12B12 = B[1][1] * B[2][2] - B[1][2] * B[1][2];
    fB12B02mB01B22 = B[1][2] * B[0][2] - B[0][1] * B[2][2];
    fB01B12mB11B02 = B[0][1] * B[1][2] - B[1][1] * B[0][2];

    // set ftmp to the determinant of the input matrix B
    ftmp = B[0][0] *
        fB11B22mB12B12 +
        B[0][1] *
        fB12B02mB01B22 +
        B[0][2] *
        fB01B12mB11B02;

    // set A to the inverse of B for any determinant except zero
    if (ftmp != 0.0F)
    {
        ftmp = 1.0F / ftmp;
        A[0][0] = fB11B22mB12B12 * ftmp;
        A[1][0] = A[0][1] = fB12B02mB01B22 * ftmp;
        A[2][0] = A[0][2] = fB01B12mB11B02 * ftmp;
        A[1][1] = (B[0][0] * B[2][2] - B[0][2] * B[0][2]) * ftmp;
        A[2][1] = A[1][2] = (B[0][2] * B[0][1] - B[0][0] * B[1][2]) * ftmp;
        A[2][2] = (B[0][0] * B[1][1] - B[0][1] * B[0][1]) * ftmp;
    }
    else
    {
        // provide the identity matrix if the determinant is zero
        f3x3matrixAeqI(A);
    }

    return;
}

// function calculates the determinant of a 3x3 matrix
float f3x3matrixDetA(float A[][3])
{
    return
        (
            A[CHX][CHX] *
                (
                    A[CHY][CHY] *
                    A[CHZ][CHZ] -
                    A[CHY][CHZ] *
                    A[CHZ][CHY]
                ) +
                        A[CHX][CHY] *
                        (A[CHY][CHZ] * A[CHZ][CHX] - A[CHY][CHX] * A[CHZ][CHZ]) +
                        A[CHX][CHZ] *
                        (A[CHY][CHX] * A[CHZ][CHY] - A[CHY][CHY] * A[CHZ][CHX])
        );
}

// function computes all eigenvalues and eigenvectors of a real symmetric matrix A[0..n-1][0..n-1]
// stored in the top left of a 10x10 array A[10][10]
// A[][] is changed on output.
// eigval[0..n-1] returns the eigenvalues of A[][].
// eigvec[0..n-1][0..n-1] returns the normalized eigenvectors of A[][]
// the eigenvectors are not sorted by value
// n can vary up to and including 10 but the matrices A and eigvec must have 10 columns.
void fEigenCompute10(float A[][10], float eigval[], float eigvec[][10], int8 n)
{
    // maximum number of iterations to achieve convergence: in practice 6 is typical
#define NITERATIONS 15
    // various trig functions of the jacobi rotation angle phi
    float   cot2phi,
            tanhalfphi,
            tanphi,
            sinphi,
            cosphi;

    // scratch variable to prevent over-writing during rotations
    float   ftmp;

    // residue from remaining non-zero above diagonal terms
    float   residue;

    // matrix row and column indices
    int8    i,
            j;

    // general loop counter
    int8    k;

    // timeout ctr for number of passes of the algorithm
    int8    ctr;

    // initialize eigenvectors matrix and eigenvalues array
    for (i = 0; i < n; i++)
    {
        // loop over all columns
        for (j = 0; j < n; j++)
        {
            // set on diagonal and off-diagonal elements to zero
            eigvec[i][j] = 0.0F;
        }

        // correct the diagonal elements to 1.0
        eigvec[i][i] = 1.0F;

        // initialize the array of eigenvalues to the diagonal elements of A
        eigval[i] = A[i][i];
    }

    // initialize the counter and loop until converged or NITERATIONS reached
    ctr = 0;
    do
    {
        // compute the absolute value of the above diagonal elements as exit criterion
        residue = 0.0F;

        // loop over rows excluding last row
        for (i = 0; i < n - 1; i++)
        {
            // loop over above diagonal columns
            for (j = i + 1; j < n; j++)
            {
                // accumulate the residual off diagonal terms which are being driven to zero
                residue += fabsf(A[i][j]);
            }
        }

        // check if we still have work to do
        if (residue > 0.0F)
        {
            // loop over all rows with the exception of the last row (since only rotating above diagonal elements)
            for (i = 0; i < n - 1; i++)
            {
                // loop over columns j (where j is always greater than i since above diagonal)
                for (j = i + 1; j < n; j++)
                {
                    // only continue with this element if the element is non-zero
                    if (fabsf(A[i][j]) > 0.0F)
                    {
                        // calculate cot(2*phi) where phi is the Jacobi rotation angle
                        cot2phi = 0.5F * (eigval[j] - eigval[i]) / (A[i][j]);

                        // calculate tan(phi) correcting sign to ensure the smaller solution is used
                        tanphi = 1.0F / (fabsf(cot2phi) + sqrtf(1.0F + cot2phi * cot2phi));
                        if (cot2phi < 0.0F)
                        {
                            tanphi = -tanphi;
                        }

                        // calculate the sine and cosine of the Jacobi rotation angle phi
                        cosphi = 1.0F / sqrtf(1.0F + tanphi * tanphi);
                        sinphi = tanphi * cosphi;

                        // calculate tan(phi/2)
                        tanhalfphi = sinphi / (1.0F + cosphi);

                        // set tmp = tan(phi) times current matrix element used in update of leading diagonal elements
                        ftmp = tanphi * A[i][j];

                        // apply the jacobi rotation to diagonal elements [i][i] and [j][j] stored in the eigenvalue array
                        // eigval[i] = eigval[i] - tan(phi) * A[i][j]
                        eigval[i] -= ftmp;

                        // eigval[j] = eigval[j] + tan(phi) * A[i][j]
                        eigval[j] += ftmp;

                        // by definition, applying the jacobi rotation on element i, j results in 0.0
                        A[i][j] = 0.0F;

                        // apply the jacobi rotation to all elements of the eigenvector matrix
                        for (k = 0; k < n; k++)
                        {
                            // store eigvec[k][i]
                            ftmp = eigvec[k][i];

                            // eigvec[k][i] = eigvec[k][i] - sin(phi) * (eigvec[k][j] + tan(phi/2) * eigvec[k][i])
                            eigvec[k][i] = ftmp - sinphi * (eigvec[k][j] + tanhalfphi * ftmp);

                            // eigvec[k][j] = eigvec[k][j] + sin(phi) * (eigvec[k][i] - tan(phi/2) * eigvec[k][j])
                            eigvec[k][j] = eigvec[k][j] + sinphi * (ftmp - tanhalfphi * eigvec[k][j]);
                        }

                        // apply the jacobi rotation only to those elements of matrix m that can change
                        for (k = 0; k <= i - 1; k++)
                        {
                            // store A[k][i]
                            ftmp = A[k][i];

                            // A[k][i] = A[k][i] - sin(phi) * (A[k][j] + tan(phi/2) * A[k][i])
                            A[k][i] = ftmp - sinphi * (A[k][j] + tanhalfphi * ftmp);

                            // A[k][j] = A[k][j] + sin(phi) * (A[k][i] - tan(phi/2) * A[k][j])
                            A[k][j] = A[k][j] + sinphi * (ftmp - tanhalfphi * A[k][j]);
                        }

                        for (k = i + 1; k <= j - 1; k++)
                        {
                            // store A[i][k]
                            ftmp = A[i][k];

                            // A[i][k] = A[i][k] - sin(phi) * (A[k][j] + tan(phi/2) * A[i][k])
                            A[i][k] = ftmp - sinphi * (A[k][j] + tanhalfphi * ftmp);

                            // A[k][j] = A[k][j] + sin(phi) * (A[i][k] - tan(phi/2) * A[k][j])
                            A[k][j] = A[k][j] + sinphi * (ftmp - tanhalfphi * A[k][j]);
                        }

                        for (k = j + 1; k < n; k++)
                        {
                            // store A[i][k]
                            ftmp = A[i][k];

                            // A[i][k] = A[i][k] - sin(phi) * (A[j][k] + tan(phi/2) * A[i][k])
                            A[i][k] = ftmp - sinphi * (A[j][k] + tanhalfphi * ftmp);

                            // A[j][k] = A[j][k] + sin(phi) * (A[i][k] - tan(phi/2) * A[j][k])
                            A[j][k] = A[j][k] + sinphi * (ftmp - tanhalfphi * A[j][k]);
                        }
                    }   // end of test for matrix element A[i][j] non-zero
                }       // end of loop over columns j
            }           // end of loop over rows i
        }               // end of test for non-zero value of residue
    } while ((residue > 0.0F) && (ctr++ < NITERATIONS));

    // end of main loop
    return;
}

// function computes all eigenvalues and eigenvectors of a real symmetric matrix A[0..n-1][0..n-1]
// stored in the top left of a 4x4 array A[4][4]
// A[][] is changed on output.
// eigval[0..n-1] returns the eigenvalues of A[][].
// eigvec[0..n-1][0..n-1] returns the normalized eigenvectors of A[][]
// the eigenvectors are not sorted by value
// n can vary up to and including 4 but the matrices A and eigvec must have 4 columns.
// this function is identical to eigencompute10 except for the workaround for 4x4 matrices since C cannot

// handle functions accepting matrices with variable numbers of columns.
void fEigenCompute4(float A[][4], float eigval[], float eigvec[][4], int8 n)
{
    // maximum number of iterations to achieve convergence: in practice 6 is typical
#define NITERATIONS 15
    // various trig functions of the jacobi rotation angle phi
    float   cot2phi,
            tanhalfphi,
            tanphi,
            sinphi,
            cosphi;

    // scratch variable to prevent over-writing during rotations
    float   ftmp;

    // residue from remaining non-zero above diagonal terms
    float   residue;

    // matrix row and column indices
    int8    ir,
            ic;

    // general loop counter
    int8    j;

    // timeout ctr for number of passes of the algorithm
    int8    ctr;

    // initialize eigenvectors matrix and eigenvalues array
    for (ir = 0; ir < n; ir++)
    {
        // loop over all columns
        for (ic = 0; ic < n; ic++)
        {
            // set on diagonal and off-diagonal elements to zero
            eigvec[ir][ic] = 0.0F;
        }

        // correct the diagonal elements to 1.0
        eigvec[ir][ir] = 1.0F;

        // initialize the array of eigenvalues to the diagonal elements of m
        eigval[ir] = A[ir][ir];
    }

    // initialize the counter and loop until converged or NITERATIONS reached
    ctr = 0;
    do
    {
        // compute the absolute value of the above diagonal elements as exit criterion
        residue = 0.0F;

        // loop over rows excluding last row
        for (ir = 0; ir < n - 1; ir++)
        {
            // loop over above diagonal columns
            for (ic = ir + 1; ic < n; ic++)
            {
                // accumulate the residual off diagonal terms which are being driven to zero
                residue += fabsf(A[ir][ic]);
            }
        }

        // check if we still have work to do
        if (residue > 0.0F)
        {
            // loop over all rows with the exception of the last row (since only rotating above diagonal elements)
            for (ir = 0; ir < n - 1; ir++)
            {
                // loop over columns ic (where ic is always greater than ir since above diagonal)
                for (ic = ir + 1; ic < n; ic++)
                {
                    // only continue with this element if the element is non-zero
                    if (fabsf(A[ir][ic]) > 0.0F)
                    {
                        // calculate cot(2*phi) where phi is the Jacobi rotation angle
                        cot2phi = 0.5F *
                            (eigval[ic] - eigval[ir]) /
                            (A[ir][ic]);

                        // calculate tan(phi) correcting sign to ensure the smaller solution is used
                        tanphi = 1.0F / (fabsf(cot2phi) + sqrtf(1.0F + cot2phi * cot2phi));
                        if (cot2phi < 0.0F)
                        {
                            tanphi = -tanphi;
                        }

                        // calculate the sine and cosine of the Jacobi rotation angle phi
                        cosphi = 1.0F / sqrtf(1.0F + tanphi * tanphi);
                        sinphi = tanphi * cosphi;

                        // calculate tan(phi/2)
                        tanhalfphi = sinphi / (1.0F + cosphi);

                        // set tmp = tan(phi) times current matrix element used in update of leading diagonal elements
                        ftmp = tanphi * A[ir][ic];

                        // apply the jacobi rotation to diagonal elements [ir][ir] and [ic][ic] stored in the eigenvalue array
                        // eigval[ir] = eigval[ir] - tan(phi) * A[ir][ic]
                        eigval[ir] -= ftmp;

                        // eigval[ic] = eigval[ic] + tan(phi) * A[ir][ic]
                        eigval[ic] += ftmp;

                        // by definition, applying the jacobi rotation on element ir, ic results in 0.0
                        A[ir][ic] = 0.0F;

                        // apply the jacobi rotation to all elements of the eigenvector matrix
                        for (j = 0; j < n; j++)
                        {
                            // store eigvec[j][ir]
                            ftmp = eigvec[j][ir];

                            // eigvec[j][ir] = eigvec[j][ir] - sin(phi) * (eigvec[j][ic] + tan(phi/2) * eigvec[j][ir])
                            eigvec[j][ir] = ftmp - sinphi * (eigvec[j][ic] + tanhalfphi * ftmp);

                            // eigvec[j][ic] = eigvec[j][ic] + sin(phi) * (eigvec[j][ir] - tan(phi/2) * eigvec[j][ic])
                            eigvec[j][ic] = eigvec[j][ic] + sinphi * (ftmp - tanhalfphi * eigvec[j][ic]);
                        }

                        // apply the jacobi rotation only to those elements of matrix m that can change
                        for (j = 0; j <= ir - 1; j++)
                        {
                            // store A[j][ir]
                            ftmp = A[j][ir];

                            // A[j][ir] = A[j][ir] - sin(phi) * (A[j][ic] + tan(phi/2) * A[j][ir])
                            A[j][ir] = ftmp - sinphi * (A[j][ic] + tanhalfphi * ftmp);

                            // A[j][ic] = A[j][ic] + sin(phi) * (A[j][ir] - tan(phi/2) * A[j][ic])
                            A[j][ic] = A[j][ic] + sinphi * (ftmp - tanhalfphi * A[j][ic]);
                        }

                        for (j = ir + 1; j <= ic - 1; j++)
                        {
                            // store A[ir][j]
                            ftmp = A[ir][j];

                            // A[ir][j] = A[ir][j] - sin(phi) * (A[j][ic] + tan(phi/2) * A[ir][j])
                            A[ir][j] = ftmp - sinphi * (A[j][ic] + tanhalfphi * ftmp);

                            // A[j][ic] = A[j][ic] + sin(phi) * (A[ir][j] - tan(phi/2) * A[j][ic])
                            A[j][ic] = A[j][ic] + sinphi * (ftmp - tanhalfphi * A[j][ic]);
                        }

                        for (j = ic + 1; j < n; j++)
                        {
                            // store A[ir][j]
                            ftmp = A[ir][j];

                            // A[ir][j] = A[ir][j] - sin(phi) * (A[ic][j] + tan(phi/2) * A[ir][j])
                            A[ir][j] = ftmp - sinphi * (A[ic][j] + tanhalfphi * ftmp);

                            // A[ic][j] = A[ic][j] + sin(phi) * (A[ir][j] - tan(phi/2) * A[ic][j])
                            A[ic][j] = A[ic][j] + sinphi * (ftmp - tanhalfphi * A[ic][j]);
                        }
                    }   // end of test for matrix element already zero
                }       // end of loop over columns
            }           // end of loop over rows
        }               // end of test for non-zero residue
    } while ((residue > 0.0F) && (ctr++ < NITERATIONS));

    // end of main loop
    return;
}

void fComputeEigSlice(float fmatA[10][10], float fmatB[10][10], float fvecA[10],
                      int8 i, int8 j, int8 iMatrixSize)
{
    float   cot2phi;    // cotangent of half jacobi rotation angle
    float   tanhalfphi; // tangent of half jacobi rotation angle
    float   tanphi;     // tangent of jacobi rotation angle
    float   sinphi;     // sine of jacobi rotation angle
    float   cosphi;     // cosine of jacobi rotation angle
    float   ftmp;       // scratch
    int8    k;          // loop counter

    // calculate cot(2*phi) where phi is the Jacobi rotation angle
    cot2phi = 0.5F * (fvecA[j] - fvecA[i]) / (fmatA[i][j]);

    // calculate tan(phi) correcting sign to ensure the smaller solution is used
    tanphi = 1.0F / (fabsf(cot2phi) + sqrtf(1.0F + cot2phi * cot2phi));
    if (cot2phi < 0.0F) tanphi = -tanphi;

    // calculate the sine and cosine of the Jacobi rotation angle phi
    cosphi = 1.0F / sqrtf(1.0F + tanphi * tanphi);
    sinphi = tanphi * cosphi;

    // calculate tan(phi/2)
    tanhalfphi = sinphi / (1.0F + cosphi);

    // set tmp = tan(phi) times current matrix element used in update of leading diagonal elements
    ftmp = tanphi * fmatA[i][j];

    // apply the jacobi rotation to diagonal elements [i][i] and [j][j] stored in the eigenvalue array
    // fvecA[i] = fvecA[i] - tan(phi) * fmatA[i][j]
    fvecA[i] -= ftmp;

    // fvecA[j] = fvecA[j] + tan(phi) * fmatA[i][j]
    fvecA[j] += ftmp;

    // by definition, applying the jacobi rotation on element i, j results in 0.0
    fmatA[i][j] = 0.0F;

    // apply the jacobi rotation to all elements of the eigenvector matrix
    for (k = 0; k < iMatrixSize; k++)
    {
        // store fmatB[k][i]
        ftmp = fmatB[k][i];

        // fmatB[k][i] = fmatB[k][i] - sin(phi) * (fmatB[k][j] + tan(phi/2) * fmatB[k][i])
        fmatB[k][i] = ftmp - sinphi * (fmatB[k][j] + tanhalfphi * ftmp);

        // fmatB[k][j] = fmatB[k][j] + sin(phi) * (fmatB[k][i] - tan(phi/2) * fmatB[k][j])
        fmatB[k][j] = fmatB[k][j] + sinphi * (ftmp - tanhalfphi * fmatB[k][j]);
    }

    // apply the jacobi rotation only to those elements of matrix that can change
    for (k = 0; k <= i - 1; k++)
    {
        // store fmatA[k][i]
        ftmp = fmatA[k][i];

        // fmatA[k][i] = fmatA[k][i] - sin(phi) * (fmatA[k][j] + tan(phi/2) * fmatA[k][i])
        fmatA[k][i] = ftmp - sinphi * (fmatA[k][j] + tanhalfphi * ftmp);

        // fmatA[k][j] = fmatA[k][j] + sin(phi) * (fmatA[k][i] - tan(phi/2) * fmatA[k][j])
        fmatA[k][j] = fmatA[k][j] + sinphi * (ftmp - tanhalfphi * fmatA[k][j]);
    }

    for (k = i + 1; k <= j - 1; k++)
    {
        // store fmatA[i][k]
        ftmp = fmatA[i][k];

        // fmatA[i][k] = fmatA[i][k] - sin(phi) * (fmatA[k][j] + tan(phi/2) * fmatA[i][k])
        fmatA[i][k] = ftmp - sinphi * (fmatA[k][j] + tanhalfphi * ftmp);

        // fmatA[k][j] = fmatA[k][j] + sin(phi) * (fmatA[i][k] - tan(phi/2) * fmatA[k][j])
        fmatA[k][j] = fmatA[k][j] + sinphi * (ftmp - tanhalfphi * fmatA[k][j]);
    }

    for (k = j + 1; k < iMatrixSize; k++)
    {
        // store fmatA[i][k]
        ftmp = fmatA[i][k];

        // fmatA[i][k] = fmatA[i][k] - sin(phi) * (fmatA[j][k] + tan(phi/2) * fmatA[i][k])
        fmatA[i][k] = ftmp - sinphi * (fmatA[j][k] + tanhalfphi * ftmp);

        // fmatA[j][k] = fmatA[j][k] + sin(phi) * (fmatA[i][k] - tan(phi/2) * fmatA[j][k])
        fmatA[j][k] = fmatA[j][k] + sinphi * (ftmp - tanhalfphi * fmatA[j][k]);
    }

    return;
}

// function uses Gauss-Jordan elimination to compute the inverse of matrix A in situ

// on exit, A is replaced with its inverse
void fmatrixAeqInvA(float *A[], int8 iColInd[], int8 iRowInd[], int8 iPivot[],
                    int8 isize, int8 *pierror)
{
    float   largest;    // largest element used for pivoting
    float   scaling;    // scaling factor in pivoting
    float   recippiv;   // reciprocal of pivot element
    float   ftmp;       // temporary variable used in swaps
    int8    i,
            j,
            k,
            l,
            m;          // index counters
    int8    iPivotRow,
            iPivotCol;  // row and column of pivot element

    // to avoid compiler warnings
    iPivotRow = iPivotCol = 0;

    // default to successful inversion
    *pierror = false;

    // initialize the pivot array to 0
    for (j = 0; j < isize; j++)
    {
        iPivot[j] = 0;
    }

    // main loop i over the dimensions of the square matrix A
    for (i = 0; i < isize; i++)
    {
        // zero the largest element found for pivoting
        largest = 0.0F;

        // loop over candidate rows j
        for (j = 0; j < isize; j++)
        {
            // check if row j has been previously pivoted
            if (iPivot[j] != 1)
            {
                // loop over candidate columns k
                for (k = 0; k < isize; k++)
                {
                    // check if column k has previously been pivoted
                    if (iPivot[k] == 0)
                    {
                        // check if the pivot element is the largest found so far
                        if (fabsf(A[j][k]) >= largest)
                        {
                            // and store this location as the current best candidate for pivoting
                            iPivotRow = j;
                            iPivotCol = k;
                            largest = (float) fabsf(A[iPivotRow][iPivotCol]);
                        }
                    }
                    else if (iPivot[k] > 1)
                    {
                        // zero determinant situation: exit with identity matrix and set error flag
                        fmatrixAeqI(A, isize);
                        *pierror = true;
                        return;
                    }
                }
            }
        }

        // increment the entry in iPivot to denote it has been selected for pivoting
        iPivot[iPivotCol]++;

        // check the pivot rows iPivotRow and iPivotCol are not the same before swapping
        if (iPivotRow != iPivotCol)
        {
            // loop over columns l
            for (l = 0; l < isize; l++)
            {
                // and swap all elements of rows iPivotRow and iPivotCol
                ftmp = A[iPivotRow][l];
                A[iPivotRow][l] = A[iPivotCol][l];
                A[iPivotCol][l] = ftmp;
            }
        }

        // record that on the i-th iteration rows iPivotRow and iPivotCol were swapped
        iRowInd[i] = iPivotRow;
        iColInd[i] = iPivotCol;

        // check for zero on-diagonal element (singular matrix) and return with identity matrix if detected
        if (A[iPivotCol][iPivotCol] == 0.0F)
        {
            // zero determinant situation: exit with identity matrix and set error flag
            fmatrixAeqI(A, isize);
            *pierror = true;
            return;
        }

        // calculate the reciprocal of the pivot element knowing it's non-zero
        recippiv = 1.0F / A[iPivotCol][iPivotCol];

        // by definition, the diagonal element normalizes to 1
        A[iPivotCol][iPivotCol] = 1.0F;

        // multiply all of row iPivotCol by the reciprocal of the pivot element including the diagonal element
        // the diagonal element A[iPivotCol][iPivotCol] now has value equal to the reciprocal of its previous value
        for (l = 0; l < isize; l++)
        {
            if (A[iPivotCol][l] != 0.0F) A[iPivotCol][l] *= recippiv;
        }

        // loop over all rows m of A
        for (m = 0; m < isize; m++)
        {
            if (m != iPivotCol)
            {
                // scaling factor for this row m is in column iPivotCol
                scaling = A[m][iPivotCol];

                // zero this element
                A[m][iPivotCol] = 0.0F;

                // loop over all columns l of A and perform elimination
                for (l = 0; l < isize; l++)
                {
                    if ((A[iPivotCol][l] != 0.0F) && (scaling != 0.0F))
                        A[m][l] -= A[iPivotCol][l] * scaling;
                }
            }
        }
    }                   // end of loop i over the matrix dimensions

    // finally, loop in inverse order to apply the missing column swaps
    for (l = isize - 1; l >= 0; l--)
    {
        // set i and j to the two columns to be swapped
        i = iRowInd[l];
        j = iColInd[l];

        // check that the two columns i and j to be swapped are not the same
        if (i != j)
        {
            // loop over all rows k to swap columns i and j of A
            for (k = 0; k < isize; k++)
            {
                ftmp = A[k][i];
                A[k][i] = A[k][j];
                A[k][j] = ftmp;
            }
        }
    }

    return;
}

// function rotates 3x1 vector u onto 3x1 vector using 3x3 rotation matrix fR.

// the rotation is applied in the inverse direction if itranpose is true
void fveqRu(float fv[], float fR[][3], float fu[], int8 itranspose)
{
    if (!itranspose)
    {
        // normal, non-transposed rotation
        fv[CHX] = fR[CHX][CHX] *
            fu[CHX] +
            fR[CHX][CHY] *
            fu[CHY] +
            fR[CHX][CHZ] *
            fu[CHZ];
        fv[CHY] = fR[CHY][CHX] *
            fu[CHX] +
            fR[CHY][CHY] *
            fu[CHY] +
            fR[CHY][CHZ] *
            fu[CHZ];
        fv[CHZ] = fR[CHZ][CHX] *
            fu[CHX] +
            fR[CHZ][CHY] *
            fu[CHY] +
            fR[CHZ][CHZ] *
            fu[CHZ];
    }
    else
    {
        // transposed (inverse rotation)
        fv[CHX] = fR[CHX][CHX] *
            fu[CHX] +
            fR[CHY][CHX] *
            fu[CHY] +
            fR[CHZ][CHX] *
            fu[CHZ];
        fv[CHY] = fR[CHX][CHY] *
            fu[CHX] +
            fR[CHY][CHY] *
            fu[CHY] +
            fR[CHZ][CHY] *
            fu[CHZ];
        fv[CHZ] = fR[CHX][CHZ] *
            fu[CHX] +
            fR[CHY][CHZ] *
            fu[CHY] +
            fR[CHZ][CHZ] *
            fu[CHZ];
    }

    return;
}

// function multiplies the 3x1 vector V by a 3x3 matrix A
void fVeq3x3AxV(float V[3], float A[][3])
{
    float   ftmp[3];    // scratch vector

    // set ftmp = V
    ftmp[CHX] = V[CHX];
    ftmp[CHY] = V[CHY];
    ftmp[CHZ] = V[CHZ];

    // set V = A * ftmp = A * V
    V[CHX] = A[CHX][CHX] *
        ftmp[CHX] +
        A[CHX][CHY] *
        ftmp[CHY] +
        A[CHX][CHZ] *
        ftmp[CHZ];
    V[CHY] = A[CHY][CHX] *
        ftmp[CHX] +
        A[CHY][CHY] *
        ftmp[CHY] +
        A[CHY][CHZ] *
        ftmp[CHZ];
    V[CHZ] = A[CHZ][CHX] *
        ftmp[CHX] +
        A[CHZ][CHY] *
        ftmp[CHY] +
        A[CHZ][CHZ] *
        ftmp[CHZ];

    return;
}
