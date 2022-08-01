/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file matrix.h
    \brief Matrix manipulation functions

    Contains functions for basic manipulation of 3x3 matrices
*/

#ifndef MATRIX_H
#define MATRIX_H

// function prototypes

/// function sets the 3x3 matrix A to the identity matrix
void f3x3matrixAeqI(
    float A[][3]
);
/// function sets 3x3 matrix A to 3x3 matrix B
void f3x3matrixAeqB(
    float A[][3], 
    float B[][3]
);
/// function sets the matrix A to the identity matrix
void fmatrixAeqI(
    float *A[],                 ///< pointer to the matrix
    int16 rc                    ///< dimension of the matrix
);
/// function sets every entry in the 3x3 matrix A to a constant scalar
void f3x3matrixAeqScalar(
    float A[][3], 
    float Scalar
);
/// function directly calculates the symmetric inverse of a symmetric 3x3 matrix
/// only the on and above diagonal terms in B are used and need to be specified
void f3x3matrixAeqInvSymB(
    float A[][3], 
    float B[][3]
);
/// function multiplies all elements of 3x3 matrix A by the specified scalar
void f3x3matrixAeqAxScalar(
    float A[][3], 
    float Scalar
);
/// function negates all elements of 3x3 matrix A
void f3x3matrixAeqMinusA(
    float A[][3]
);
/// function calculates the determinant of a 3x3 matrix
float f3x3matrixDetA(
    float A[][3]
);
/// function computes all eigenvalues and eigenvectors of a real symmetric matrix A[0..n-1][0..n-1]
/// stored in the top left of a 10x10 array A[10][10]
void fEigenCompute10(
    float A[][10],              ///< real symmetric matrix A[0..n-1][0..n-1]
    float eigval[],             ///< eigval[0..n-1] returns the eigenvalues of A[][].
    float eigvec[][10],         ///< eigvec[0..n-1][0..n-1] returns the normalized eigenvectors of A[][]
    int8 n                      ///< n can vary up to and including 10 but the matrices A and eigvec must have 10 columns.
);
/// function computes all eigenvalues and eigenvectors of a real symmetric matrix A[0..n-1][0..n-1]
/// stored in the top left of a 4x4 array A[4][4]
/// A[][] is changed on output.
/// The eigenvectors are not sorted by value.
/// This function is identical to eigencompute10 except for the workaround for 4x4 matrices since C cannot
/// handle functions accepting matrices with variable numbers of columns.
void fEigenCompute4(
    float A[][4], 
    float eigval[],             ///< eigval[0..n-1] returns the eigenvalues of A[][].
    float eigvec[][4],          ///< eigvec[0..n-1][0..n-1] returns the normalized eigenvectors of A[][]
    int8 n                      ///< n can vary up to and including 4 but the matrices A and eigvec must have 4 columns.
);
void fComputeEigSlice(
    float fmatA[10][10], 
    float fmatB[10][10], 
    float fvecA[10], 
    int8 i, 
    int8 j, 
    int8 iMatrixSize
);
/// function uses Gauss-Jordan elimination to compute the inverse of matrix A in situ
/// on exit, A is replaced with its inverse
void fmatrixAeqInvA(
    float *A[], 
    int8 iColInd[], 
    int8 iRowInd[], 
    int8 iPivot[], 
    int8 isize, 
    int8* pierror
);
/// function rotates 3x1 vector u onto 3x1 vector using 3x3 rotation matrix fR.
/// the rotation is applied in the inverse direction if itranpose is true
void fveqRu(
    float fv[],         ///< 3x1 output vector
    float fR[][3],      ///< rotation matrix
    float fu[],         ///< 3x1 input vector
    int8 itranspose     ///< true if inverse direction desired
);
/// function multiplies the 3x1 vector V by a 3x3 matrix A
void fVeq3x3AxV(
    float V[3],         ///< used for both input and output
    float A[][3]
);

#endif   // #ifndef MATRIX_H
