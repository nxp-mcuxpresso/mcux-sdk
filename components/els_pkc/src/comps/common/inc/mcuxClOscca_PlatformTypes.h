/*--------------------------------------------------------------------------*/
/* Copyright 2016, 2021 NXP                                                 */
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
/* Security Classification:  Company Confidential                           */
/*--------------------------------------------------------------------------*/

/**
 *
 * @file:  mcuxClOscca_PlatformTypes.h
 * @brief: Platform type definitions
 *
 */
#ifndef MCUXCLOSCCA_PLATFORMTYPES_H_
#define MCUXCLOSCCA_PLATFORMTYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <platform_specific_headers.h>

typedef uint32_t mcuxClOscca_Size_t;
typedef uint32_t mcuxClOscca_Uint_t;
typedef int32_t mcuxClOscca_Int_t;

/**
 * global scratch pad structure definition
 */
typedef struct
{
  volatile uint16_t securityCounter;
  volatile uint16_t stackPointerBackup;
  uint32_t generalPurposeValue;
} mcuxClOscca_ScratchPad_t;

#define MCUX_CLOSCCA_SCRATCHPAD_SECTION __attribute__((section(".data.gmcuxClOscca_ScratchPad")))

/**
 * global scratch pad object
 */
extern mcuxClOscca_ScratchPad_t MCUX_CLOSCCA_SCRATCHPAD_SECTION gmcuxClOscca_ScratchPad;

#endif /* MCUXCLOSCCA_PLATFORMTYPES_H_ */
