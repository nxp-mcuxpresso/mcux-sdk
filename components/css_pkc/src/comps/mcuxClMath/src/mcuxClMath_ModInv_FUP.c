/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClMath_ModInv.c
 *  @brief mcuxClMath: modular inversion implementation
 */


#include <mcuxClMath_ModInv_FUP.h>

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup1[7], 4u) = {{0x10u,0x00u,0xa3u,0xf2u,0xbfu,0xc7u},{0x40u,0x0fu,0x00u,0x00u,0x00u,0x00u},{0x00u,0x1au,0x00u,0x00u,0x05u,0x03u},{0x80u,0x5du,0x01u,0x02u,0x03u,0x04u},{0x00u,0x0eu,0x00u,0x03u,0x03u,0x01u},{0x00u,0x0fu,0x00u,0x03u,0x03u,0x03u},{0x80u,0x2au,0x01u,0x01u,0x04u,0x02u}};

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup3a[3], 4u) = {{0x10u,0x00u,0x16u,0x82u,0xf9u,0xbfu},{0x80u,0x00u,0x02u,0x03u,0x01u,0x00u},{0x00u,0x0eu,0x00u,0x00u,0x00u,0x03u}};

SDK_ALIGN(const mcuxClPkc_FUPEntry_t mcuxClMath_ModInv_Fup3b[3], 4u) = {{0x10u,0x00u,0x00u,0xf6u,0x90u,0xd4u},{0x80u,0x00u,0x02u,0x03u,0x01u,0x00u},{0x80u,0x33u,0x00u,0x00u,0x01u,0x03u}};


