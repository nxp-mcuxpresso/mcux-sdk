/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_snvs_hp.h"
#include "fsl_snvs_lp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HAC_INIT_VALUE 0xFEDCBA98

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_CheckResult(bool condition, char *log);
static void DEMO_ShowSSMState(snvs_hp_ssm_state_t ssmState);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t hacValue;
    snvs_hp_ssm_state_t ssmState;

    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init SNVS */
    SNVS_LP_Init(SNVS);
    SNVS_HP_Init(SNVS);

    PRINTF("\r\nSNVS HP HAC example:\r\n");

    PRINTF("Press anykey to start the example:\r\n");

    GETCHAR();

    /* Step 1: Set and load the HAC initial value. */
    SNVS_HP_SetHighAssuranceCounterInitialValue(SNVS, HAC_INIT_VALUE);
    SNVS_HP_LoadHighAssuranceCounter(SNVS);

    /* Check the result, now the HAC initial value should be loaded. */
    hacValue = SNVS_HP_GetHighAssuranceCounter(SNVS);
    DEMO_CheckResult((HAC_INIT_VALUE == hacValue), "HAC initial value load failed");

    /* Step 2: Enable the HAC. */
    SNVS_HP_EnableHighAssuranceCounter(SNVS, true);

    /* Check current SSM state. */
    PRINTF("Check current SSM state\r\n");
    ssmState = SNVS_HP_GetSSMState(SNVS);
    DEMO_ShowSSMState(ssmState);

    /* Current state should be NON_SECURE, CHECK, TRUSTED or SECURE. */
    DEMO_CheckResult(((kSNVS_SSMCheck == ssmState) || (kSNVS_SSMNonSecure == ssmState) ||
                      (kSNVS_SSMTrusted == ssmState) || (kSNVS_SSMSecure == ssmState)),
                     "Invalid SSM mode");

    /* Step 3: Trigger software sucurity violation and enter soft fail mode. */
    PRINTF("Triger software sucurity violation to enter soft fail mode\r\n");
    SNVS_HP_SetSoftwareFatalSecurityViolation(SNVS);

    ssmState = SNVS_HP_GetSSMState(SNVS);
    DEMO_CheckResult((kSNVS_SSMSoftFail == ssmState), "Could not enter soft fail mode ");

    PRINTF("Switched to soft fail mode\r\n");

    /* Step 4: Stop the HAC. */
    SNVS_HP_StartHighAssuranceCounter(SNVS, false);
    hacValue = SNVS_HP_GetHighAssuranceCounter(SNVS);

    /* Delay for a while, to check whether the HAC is stopped. */
    for (volatile uint32_t i = 0; i < 0x5; i++)
    {
    }

    DEMO_CheckResult((hacValue == SNVS_HP_GetHighAssuranceCounter(SNVS)), "Could not stop HAC");

    PRINTF("The HAC stopped, current counter value is 0x%08x.\r\n", hacValue);

    /* Step 5: Clear the HAC, enter hard fail mode directly. */
    PRINTF("Clear the HAC to enter hard fail mode, and perform system reset.\r\n");
    PRINTF("Example success. The system will reset next.\r\n");
    /* Delay for a while, to make sure UART output finished. */
    for (volatile uint32_t i = 0; i < 0x200000; i++)
    {
    }

    SNVS_HP_ClearHighAssuranceCounter(SNVS);

    /* Should never get here. */
    while (1)
        ;
}

static void DEMO_CheckResult(bool condition, char *log)
{
    if (!condition)
    {
        PRINTF("FAIL: %s\r\n", log);
        while (1)
            ;
    }
}

static void DEMO_ShowSSMState(snvs_hp_ssm_state_t ssmState)
{
    PRINTF("SSM state: ");

    switch (ssmState)
    {
        case kSNVS_SSMInit:
            PRINTF("Init");
            break;
        case kSNVS_SSMHardFail:
            PRINTF("Hard Fail");
            break;
        case kSNVS_SSMSoftFail:
            PRINTF("Soft Fail");
            break;
        case kSNVS_SSMInitInter:
            PRINTF("Init Intermediate");
            break;
        case kSNVS_SSMCheck:
            PRINTF("Check");
            break;
        case kSNVS_SSMNonSecure:
            PRINTF("Non-Secure");
            break;
        case kSNVS_SSMTrusted:
            PRINTF("Trusted");
            break;
        case kSNVS_SSMSecure:
            PRINTF("Secure");
            break;
        default:
            PRINTF("error");
            break;
    }

    PRINTF("\r\n");
}
