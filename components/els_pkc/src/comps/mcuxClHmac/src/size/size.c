/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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
 *
 * @file: size.c
 * @brief: This file contains objects which will be used to measure size of particular types.
 *
 */

#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClHmac_Internal_Types.h>
#include <internal/mcuxClHmac_Internal_Macros.h>
#include <internal/mcuxClHmac_Internal_Memory.h>

/*************************/
/**** Work area sizes ****/
/*************************/

MCUX_CSSL_ANALYSIS_START_PATTERN_OBJ_SIZES()

/* Context and WA for MAC computation */
volatile mcuxClHmac_Context_Sw_t mcuxClHmac_Context_Sw;

volatile mcuxClHmac_Context_Els_t mcuxClHmac_Context_Els;

volatile uint8_t mcuxClHmac_Context_Max[MCUXCLHMAC_INTERNAL_MAX_CONTEXT_SIZE];


volatile uint8_t mcuxClHmac_WorkArea_Init[MCUXCLHMAC_INTERNAL_WACPU_INIT];
volatile uint8_t mcuxClHmac_WorkArea_Finish[MCUXCLHMAC_INTERNAL_WACPU_FINISH];
volatile uint8_t mcuxClHmac_WorkArea_Max[MCUXCLHMAC_INTERNAL_MAX_WACPU];
volatile uint8_t mcuxClHmac_WorkArea_Process[4u];



/* Mode-specific structures */
volatile uint8_t mcuxClHmac_ModeDescriptor[sizeof(mcuxClMac_ModeDescriptor_t) + sizeof(mcuxClHmac_ModeDescriptor_t)];

MCUX_CSSL_ANALYSIS_STOP_PATTERN_OBJ_SIZES()
