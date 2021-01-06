/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_flash.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BUFFER_LEN 4

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void error_trap(void);
void app_finalize(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Flash driver Structure */
static flexnvm_config_t s_flashDriver;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * @brief Gets called when an error occurs.
 *
 * @details Print error message and trap forever.
 */
void error_trap(void)
{
    PRINTF("\r\n\r\n\r\n\t---- HALTED DUE TO FLASH ERROR! ----");
    while (1)
    {
    }
}

/*
 * @brief Gets called when the app is complete.
 *
 * @details Print finshed message and trap forever.
 */
void app_finalize(void)
{
    /* Print finished message. */
    PRINTF("\r\n End of FlexNVM Dflash Example \r\n");
    while (1)
    {
    }
}

/*!
 * @brief Use Standard Software Drivers (SSD) to modify dflash.
 *
 * @details This function uses SSD to demonstrate flash mode:
 *            + Check dflash information.
 *            + Erase a sector and verify.
 *            + Program a sector and verify.
 */
int main(void)
{
    ftfx_security_state_t securityStatus = kFTFx_SecurityStateNotSecure; /* Return protection status */
    status_t result; /* Return code from each flash driver function */

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Clean up Flash driver Structure*/
    memset(&s_flashDriver, 0, sizeof(flexnvm_config_t));

    /* print welcome message */
    PRINTF("\r\n FlexNVM DFlash Example Start \r\n");

#if defined(SIM_FCFG2_PFLSH_MASK)
    if (SIM->FCFG2 & SIM_FCFG2_PFLSH_MASK)
    {
        PRINTF("\r\n Current device doesn't support FlexNVM feature \r\n");
        app_finalize();
    }
#endif

    /* Setup flash driver structure for device and initialize variables. */
    result = FLEXNVM_Init(&s_flashDriver);
    if (kStatus_FTFx_Success != result)
    {
        error_trap();
    }

    /* Check security status. */
    result = FLEXNVM_GetSecurityState(&s_flashDriver, &securityStatus);
    if (kStatus_FTFx_Success != result)
    {
        error_trap();
    }
    /* Print security status. */
    switch (securityStatus)
    {
        case kFTFx_SecurityStateNotSecure:
            PRINTF("\r\n Flash is UNSECURE!");
            break;
        case kFTFx_SecurityStateBackdoorEnabled:
            PRINTF("\r\n Flash is SECURE, BACKDOOR is ENABLED!");
            break;
        case kFTFx_SecurityStateBackdoorDisabled:
            PRINTF("\r\n Flash is SECURE, BACKDOOR is DISABLED!");
            break;
        default:
            break;
    }
    PRINTF("\r\n");

    /* Debug message for user. */
    /* Test flexnvm dflash feature only if flash is unsecure. */
    if (kFTFx_SecurityStateNotSecure != securityStatus)
    {
        PRINTF("\r\n Data Flash opeation will not be executed, as Flash is SECURE!");
        app_finalize();
    }
    else
    {
        uint32_t s_buffer[BUFFER_LEN];     /* Buffer for program */
        uint32_t s_buffer_rbc[BUFFER_LEN]; /* Buffer for readback */
        uint32_t destAdrss;                /* Address of the target location */
        uint32_t i, failAddr, failDat;

        uint32_t dflashBlockBase  = 0;
        uint32_t dflashTotalSize  = 0;
        uint32_t dflashSectorSize = 0;

        /* Get flash properties*/
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyDflashBlockBaseAddr, &dflashBlockBase);
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyDflashTotalSize, &dflashTotalSize);
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyDflashSectorSize, &dflashSectorSize);

        /* Print flash information - DFlash. */
        PRINTF("\r\n DFlash Information: ");
        if (dflashTotalSize)
        {
            PRINTF("\r\n Data Flash Base Address: (0x%x) ", dflashBlockBase);
            PRINTF("\r\n Data Flash Total Size:\t%d KB, Hex: (0x%x)", (dflashTotalSize / 1024), dflashTotalSize);
            PRINTF("\r\n Data Flash Sector Size:\t%d KB, Hex: (0x%x) ", (dflashSectorSize / 1024), dflashSectorSize);
        }
        else
        {
            PRINTF("\r\n There is no D-Flash (FlexNVM) on this Device.");
            app_finalize();
        }

        /* Erase several sectors on upper pflash block where there is no code */
        PRINTF("\r\n Erase a sector of Data Flash");

        /* Erase a sector from destAdrss. */
        destAdrss = dflashBlockBase + (dflashTotalSize - dflashSectorSize);
        result    = FLEXNVM_DflashErase(&s_flashDriver, destAdrss, dflashSectorSize, kFTFx_ApiEraseKey);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

        /* Verify sector if it's been erased. */
        result = FLEXNVM_DflashVerifyErase(&s_flashDriver, destAdrss, dflashSectorSize, kFTFx_MarginValueUser);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

        /* Print message for user. */
        PRINTF("\r\n Successfully Erased Sector 0x%x -> 0x%x\r\n", destAdrss, (destAdrss + dflashSectorSize));

        /* Print message for user. */
        PRINTF("\r\n Program a buffer to a sector of Data Flash ");
        /* Prepare user buffer. */
        for (i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer[i] = i;
        }
        /* Program user buffer into flash*/
        destAdrss = dflashBlockBase + (dflashTotalSize - dflashSectorSize);
        result    = FLEXNVM_DflashProgram(&s_flashDriver, destAdrss, (uint8_t *)s_buffer, sizeof(s_buffer));
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

        /* Verify programming by Program Check command with user margin levels */
        result = FLEXNVM_DflashVerifyProgram(&s_flashDriver, destAdrss, sizeof(s_buffer), (const uint8_t *)s_buffer,
                                             kFTFx_MarginValueUser, &failAddr, &failDat);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
        /* Clean the D-Cache before reading the flash data*/
        SCB_CleanInvalidateDCache();
#endif
        /* Verify programming by reading back from flash directly*/
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer_rbc[i] = *(volatile uint32_t *)(destAdrss + i * 4);
            if (s_buffer_rbc[i] != s_buffer[i])
            {
                error_trap();
            }
        }

        PRINTF("\r\n Successfully Programmed and Verified Location 0x%x -> 0x%x \r\n", destAdrss,
               (destAdrss + sizeof(s_buffer)));
    }

    app_finalize();

    return 0;
}
