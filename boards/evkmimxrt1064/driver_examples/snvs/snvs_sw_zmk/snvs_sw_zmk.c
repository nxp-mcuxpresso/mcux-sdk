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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_CheckResult(bool condition, char *log);

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
    static uint32_t ZMKey[] = {
        0x01234567, 0x89abcdef, 0x01234567, 0x89abcdef, 0x01234567, 0x89abcdef, 0x01234567, 0x89abcdef,
    };

    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Init SNVS */
    SNVS_LP_Init(SNVS);
    SNVS_HP_Init(SNVS);

    PRINTF("\r\nSNVS software Zeroizable Master Key example:\r\n");

    /* Disable the ZMK and ECC first. */
    SNVS_LP_EnableZeroizableMasterKeyECC(SNVS, false);
    SNVS_LP_SetZeroizableMasterKeyValid(SNVS, false);
    SNVS_HP_ClearSecurityViolationStatusFlags(SNVS, kSNVS_ZMK_EccFailFlag);

    /* Step 1: Set the ZMK key by software. */
    PRINTF("Set the ZMK key value\r\n");
    SNVS_LP_SetZeroizableMasterKeyProgramMode(SNVS, kSNVS_ZMKSoftwareProgram);
    SNVS_LP_WriteZeroizableMasterKey(SNVS, ZMKey);

    /* Now the ZMK is not zero. */
    DEMO_CheckResult((0 == (SNVS_HP_GetStatusFlags(SNVS) & (uint32_t)kSNVS_ZMK_ZeroFlag)), "ZMK not set");

    /* Step 2: Enable the ZMK. */
    PRINTF("Enable the ZMK\r\n");
    SNVS_LP_SetZeroizableMasterKeyValid(SNVS, true);

    /* Step 3: Enable the ECC. */
    PRINTF("Enable the ZMK ECC\r\n");
    SNVS_LP_EnableZeroizableMasterKeyECC(SNVS, true);

    /*
     * Use the ZMK as master key.
     */
    SNVS_HP_EnableMasterKeySelection(SNVS, true);
    SNVS_LP_SetMasterKeyMode(SNVS, kSNVS_ZMK);

    /*
     * When change the ZMK value, the new calculate ECC does not match the one
     * stored in register, then violation detected and ZMK key Zeroized.
     */
    PRINTF("Set new ZMK key to generate ZMK violation\r\n");
    ZMKey[0] ^= 1;
    SNVS_LP_WriteZeroizableMasterKey(SNVS, ZMKey);

    /* Now the ZMK is zero. */
    DEMO_CheckResult((0 != (SNVS_HP_GetStatusFlags(SNVS) & (uint32_t)kSNVS_ZMK_ZeroFlag)), "ZMK not zeroized");

    PRINTF("ZMK violation detected, ZMK key is zeroized\r\n");

    PRINTF("\r\nSNVS software ZMK example finished successfully\r\n");

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
