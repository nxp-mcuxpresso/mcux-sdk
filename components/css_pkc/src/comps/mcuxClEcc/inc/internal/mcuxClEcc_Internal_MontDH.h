/*--------------------------------------------------------------------------*/
/* Copyright 2021 NXP                                                       */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClEcc_Internal_MontDH.h
 *  @brief Internal header of mcuxClEcc component
 */

#ifndef MCUXCLECC_INTERNAL_MONTDH_H_
#define MCUXCLECC_INTERNAL_MONTDH_H_

#define ECC_P    0x00u
#define ECC_N    0x01u

#define MONT_VX1  0x02u
#define MONT_VZ1  0x03u

#define MONT_VX2  0x04u
#define MONT_VZ2  0x05u
#define MONT_V0   0x06u
#define MONT_V1   0x07u

#define MONT_V2   0x08u
#define MONT_V3   0x09u
#define MONT_V4   0x0Au
#define MONT_V5   0x0Bu
#define MONT_V6   0x0Cu
#define MONT_V7   0x0Du
#define MONT_V8   0x0Eu
#define MONT_V9   0x0Fu

#define ECC_PS    0x10u
#define ECC_NS    0x11u
#define ECC_CP0   0x12u
#define ECC_CP1   0x13u

#define ECC_PFULL  0x14u
#define ECC_NFULL  0x15u
#define ECC_PQSQR  0x16u
#define ECC_NQSQR  0x17u

#define ECC_S0  0x18u
#define ECC_S1  0x19u
#define ECC_S2  0x1Au
#define ECC_S3  0x1Bu
#define ECC_T0  0x1Cu
#define ECC_T1  0x1Du
#define ECC_T2  0x1Eu
#define ECC_T3  0x1Fu

#define MONT_X0  0x20u
#define MONT_Z0  0x21u
#define MONT_X1  0x22u
#define MONT_Z1  0x23u
#define MONT_X2  0x24u
#define MONT_Z2  0x25u

#define ECC_MONTDH_NO_OF_VIRTUALS  0x10u
#define ECC_MONTDH_NO_OF_BUFFERS   0x18u

#define MCUXCLECC_PROJECTIVE        (0xA5A5A5A5u)
#define MCUXCLECC_AFFINE            (0x5A5A5A5Au)

#endif
