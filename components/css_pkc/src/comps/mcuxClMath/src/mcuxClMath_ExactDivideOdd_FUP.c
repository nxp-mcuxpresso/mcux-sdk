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

/**
 * @file  mcuxClMath_ExactDivideOdd.c
 * @brief mcuxClMath: implementation of exact divide with odd divisor
 */


#include <mcuxClMath_ExactDivideOdd_FUP.h>

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_ExactDivideOdd_DivideLoop[5], 4u) = {{0x10u,0x00u,0x89u,0x71u,0x09u,0xadu},{0x40u,0x20u,0x02u,0x00u,0x00u,0x00u},{0x40u,0x00u,0x02u,0x00u,0x00u,0x04u},{0x40u,0x0eu,0x00u,0x04u,0x04u,0x05u},{0x00u,0x62u,0x00u,0x01u,0x02u,0x02u}};

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClMath_Fup_ExactDivideOdd_NDashY[4], 4u) = {{0x10u,0x00u,0x8fu,0x8au,0x30u,0x35u},{0x40u,0x00u,0x00u,0x01u,0x00u,0x04u},{0x40u,0x1au,0x00u,0x04u,0x05u,0x04u},{0x40u,0x00u,0x04u,0x00u,0x00u,0x00u}};


