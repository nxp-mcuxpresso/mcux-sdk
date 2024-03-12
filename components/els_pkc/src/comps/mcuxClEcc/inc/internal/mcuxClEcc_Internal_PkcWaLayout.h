/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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

/**
 * @file  mcuxClEcc_Internal_PkcWaLayout.h
 * @brief internal header of mcuxClEcc functionalities
 */


#ifndef MCUXCLECC_INTERNAL_PKCWALAYOUT_H_
#define MCUXCLECC_INTERNAL_PKCWALAYOUT_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClPkc_Functions.h>


#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************/
/*                                                        */
/* Definition of generic CPU and PKC workarea layout      */
/*                                                        */
/**********************************************************/

/**
 * Generic ECC PKC workarea memory layout.
 */
#define ECC_P    0x00u
#define ECC_N    0x01u
#define ECC_ONE  0x02u
#define ECC_ZERO 0x03u

#define ECC_V0   0x04u
#define ECC_V1   0x05u
#define ECC_V2   0x06u
#define ECC_V3   0x07u
#define ECC_V4   0x08u
#define ECC_V5   0x09u
#define ECC_V6   0x0Au
#define ECC_V7   0x0Bu
#define ECC_V8   0x0Cu
#define ECC_V9   0x0Du
#define ECC_VA   0x0Eu
#define ECC_VB   0x0Fu

#define ECC_PS     0x10u
#define ECC_NS     0x11u
#define ECC_CP0    0x12u
#define ECC_CP1    0x13u
#define ECC_PFULL  0x14u
#define ECC_NFULL  0x15u
#define ECC_PQSQR  0x16u
#define ECC_NQSQR  0x17u

#define ECC_S0  0x18u
#define ECC_T0  0x19u
#define ECC_S1  0x1Au
#define ECC_T1  0x1Bu
#define ECC_S2  0x1Cu
#define ECC_T2  0x1Du
#define ECC_S3  0x1Eu
#define ECC_T3  0x1Fu

#define ECC_COORD00  0x20u
#define ECC_COORD01  0x21u
#define ECC_COORD02  0x22u
#define ECC_COORD03  0x23u
#define ECC_COORD04  0x24u
#define ECC_COORD05  0x25u
#define ECC_COORD06  0x26u
#define ECC_COORD07  0x27u
#define ECC_COORD08  0x28u
#define ECC_COORD09  0x29u
#define ECC_COORD10  0x2Au
#define ECC_COORD11  0x2Bu
#define ECC_COORD12  0x2Cu
#define ECC_COORD13  0x2Du
#define ECC_COORD14  0x2Eu
#define ECC_COORD15  0x2Fu
#define ECC_COORD16  0x30u
#define ECC_COORD17  0x31u
#define ECC_COORD18  0x32u
#define ECC_COORD19  0x33u
#define ECC_COORD20  0x34u
#define ECC_COORD21  0x35u
#define ECC_COORD22  0x36u
#define ECC_COORD23  0x37u
#define ECC_COORD24  0x38u
#define ECC_COORD25  0x39u
#define ECC_COORD26  0x3Au
#define ECC_COORD27  0x3Bu

#define ECC_NO_OF_VIRTUALS  ECC_PS


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_INTERNAL_PKCWALAYOUT_H_ */
