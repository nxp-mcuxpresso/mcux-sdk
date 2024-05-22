/*--------------------------------------------------------------------------*/
/* Copyright 2022 NXP                                                       */
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
 * @file  mcuxClEcc_TwEd_Internal_PointValidation_FUP.c
 * @brief mcuxClEcc: FUP programs used in ECC functions for Twisted Edwards curves
 */


#include <internal/mcuxClPkc_FupMacros.h>
#include <internal/mcuxClEcc_TwEd_Internal.h>
#include <internal/mcuxClEcc_TwEd_Internal_PointValidation_FUP.h>

const mcuxClPkc_FUPEntry_t mcuxClEcc_FUP_TwEd_PointValidation[14] MCUX_FUP_ATTRIBUTE = {{0x10u,0x00u,0x67u,0xe4u,0x10u,0x75u},{0x80u,0x00u,0x04u,0x04u,0x00u,0x19u},{0x80u,0x00u,0x05u,0x05u,0x00u,0x1bu},{0x80u,0x00u,0x04u,0x05u,0x00u,0x06u},{0x80u,0x2au,0x00u,0x06u,0x00u,0x06u},{0x80u,0x00u,0x12u,0x19u,0x00u,0x1du},{0x80u,0x21u,0x10u,0x1du,0x1bu,0x1du},{0x80u,0x00u,0x13u,0x19u,0x00u,0x1fu},{0x80u,0x00u,0x1fu,0x1bu,0x00u,0x19u},{0x80u,0x2au,0x10u,0x1du,0x19u,0x1du},{0x00u,0x09u,0x00u,0x00u,0x00u,0x1fu},{0x80u,0x2au,0x10u,0x1du,0x1fu,0x1du},{0x80u,0x33u,0x1du,0x00u,0x00u,0x1fu},{0x80u,0x2au,0x00u,0x1fu,0x00u,0x1fu}};



/* FUP program: calculate curve equation for given point         */
/* Prerequisites:                                                */
/* Input: P = (x,y) in (TWED_V0,TWED_V1);                        */
/* Output: ECC_T3 = 0 if input point is a valid point            */
