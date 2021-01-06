/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
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
#if defined(FSL_FEATURE_HAS_L1CACHE) && FSL_FEATURE_HAS_L1CACHE
#include "fsl_cache.h"
#endif /* FSL_FEATURE_HAS_L1CACHE */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FSL_SUPPORT_ERASE_SECTOR_NON_BLOCKING 1U
#define BUFFER_LEN                            4

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void error_trap(void);
void app_finalize(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Flash driver Structure */
static flash_config_t s_flashDriver;
/*! @brief Flash cache driver Structure */
static ftfx_cache_config_t s_cacheDriver;
/*! @brief Buffer for program */
static uint32_t s_buffer[BUFFER_LEN];
/*! @brief Buffer for readback */
static uint32_t s_buffer_rbc[BUFFER_LEN];

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
    PRINTF("\r\n End of PFlash Example \r\n");
    while (1)
    {
    }
}

/*!
 * @brief Use Standard Software Drivers (SSD) to modify pflash.
 *
 * @details This function uses SSD to demonstrate flash mode:
 *            + Check pflash information.
 *            + Erase a sector and verify.
 *            + Program a sector and verify.
 */
int main(void)
{
    ftfx_security_state_t securityStatus = kFTFx_SecurityStateNotSecure; /* Return protection status */
    status_t result;   /* Return code from each flash driver function */
    uint32_t destAddr; /* Address of the target location */
    uint32_t i, failAddr, failDat;

    uint32_t pflashBlockBase  = 0;
    uint32_t pflashTotalSize  = 0;
    uint32_t pflashSectorSize = 0;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Clean up Flash, Cache driver Structure*/
    memset(&s_flashDriver, 0, sizeof(flash_config_t));
    memset(&s_cacheDriver, 0, sizeof(ftfx_cache_config_t));

    /* Setup flash driver structure for device and initialize variables. */
    result = FLASH_Init(&s_flashDriver);
    if (kStatus_FTFx_Success != result)
    {
        error_trap();
    }
    /* Setup flash cache driver structure for device and initialize variables. */
    result = FTFx_CACHE_Init(&s_cacheDriver);
    if (kStatus_FTFx_Success != result)
    {
        error_trap();
    }
    /* Get flash properties*/
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0BlockBaseAddr, &pflashBlockBase);
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0TotalSize, &pflashTotalSize);
    FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize);

    /* print welcome message */
    PRINTF("\r\n PFlash Example Start \r\n");
    /* Print flash information - PFlash. */
    PRINTF("\r\n PFlash Information: ");
    PRINTF("\r\n Total Program Flash Size:\t%d KB, Hex: (0x%x)", (pflashTotalSize / 1024), pflashTotalSize);
    PRINTF("\r\n Program Flash Sector Size:\t%d KB, Hex: (0x%x) ", (pflashSectorSize / 1024), pflashSectorSize);

    /* Check security status. */
    result = FLASH_GetSecurityState(&s_flashDriver, &securityStatus);
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

    /* Test pflash basic opeation only if flash is unsecure. */
    if (kFTFx_SecurityStateNotSecure == securityStatus)
    {
        /* Pre-preparation work about flash Cache/Prefetch/Speculation. */
        FTFx_CACHE_ClearCachePrefetchSpeculation(&s_cacheDriver, true);

        /* Debug message for user. */
        /* Erase several sectors on upper pflash block where there is no code */
        PRINTF("\r\n Erase a sector of flash");

/* In case of the protected sectors at the end of the pFlash just select
the block from the end of pFlash to be used for operations
SECTOR_INDEX_FROM_END = 1 means the last sector,
SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
in case of FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP it is
SECTOR_INDEX_FROM_END = 1 means the last 2 sectors with width of 2 sectors,
SECTOR_INDEX_FROM_END = 2 means the last 4 sectors back
with width of 2 sectors ...
*/
#ifndef SECTOR_INDEX_FROM_END
#define SECTOR_INDEX_FROM_END 1U
#endif

#ifdef TEST_TARGET_ADDRESS
        destAddr = TEST_TARGET_ADDRESS;
#else
/* Erase a sector from destAddr. */
#if defined(FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP) && FSL_FEATURE_FLASH_HAS_PFLASH_BLOCK_SWAP
        /* Note: we should make sure that the sector shouldn't be swap indicator sector*/
        destAddr = pflashBlockBase + (pflashTotalSize - (SECTOR_INDEX_FROM_END * pflashSectorSize * 2));
#else
        destAddr = pflashBlockBase + (pflashTotalSize - (SECTOR_INDEX_FROM_END * pflashSectorSize));
#endif
#endif // TEST_TARGET_ADDRESS
        /* Print message for user. */
        PRINTF("\r\n Program a buffer to a sector of flash ");
        /* Prepare user buffer. */
        for (i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer[i] = i;
        }

#if defined(FSL_SUPPORT_ERASE_SECTOR_NON_BLOCKING) && FSL_SUPPORT_ERASE_SECTOR_NON_BLOCKING
        result = FLASH_EraseSectorNonBlocking(&s_flashDriver, destAddr, kFTFx_ApiEraseKey);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
        /* Before programming the flash, check whether the erase sector command is completed,*/
        /* and get the flash status. */
        result = FLASH_GetCommandState();
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
#else
        result   = FLASH_Erase(&s_flashDriver, destAddr, pflashSectorSize, kFTFx_ApiEraseKey);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
#endif
        /* Verify sector if it's been erased. */
        result = FLASH_VerifyErase(&s_flashDriver, destAddr, pflashSectorSize, kFTFx_MarginValueUser);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
        /* Print message for user. */
        PRINTF("\r\n Successfully Erased Sector 0x%x -> 0x%x\r\n", destAddr, (destAddr + pflashSectorSize));

        /* Program user buffer into flash*/
        result = FLASH_Program(&s_flashDriver, destAddr, (uint8_t *)s_buffer, sizeof(s_buffer));
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

        /* Verify programming by Program Check command with user margin levels */
        result = FLASH_VerifyProgram(&s_flashDriver, destAddr, sizeof(s_buffer), (const uint8_t *)s_buffer,
                                     kFTFx_MarginValueUser, &failAddr, &failDat);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }

        /* Post-preparation work about flash Cache/Prefetch/Speculation. */
        FTFx_CACHE_ClearCachePrefetchSpeculation(&s_cacheDriver, false);

#if defined(FSL_FEATURE_HAS_L1CACHE) && FSL_FEATURE_HAS_L1CACHE
        L1CACHE_InvalidateCodeCache();
#endif /* FSL_FEATURE_HAS_L1CACHE */

#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
        /* Clean the D-Cache before reading the flash data*/
        SCB_CleanInvalidateDCache();
#endif
        /* Verify programming by reading back from flash directly*/
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer_rbc[i] = *(volatile uint32_t *)(destAddr + i * 4);
            if (s_buffer_rbc[i] != s_buffer[i])
            {
                error_trap();
            }
        }

        PRINTF("\r\n Successfully Programmed and Verified Location 0x%x -> 0x%x \r\n", destAddr,
               (destAddr + sizeof(s_buffer)));

        /* Erase the context we have progeammed before*/
        /* Note: we should make sure that the sector which will be set as swap indicator should be blank*/
        FLASH_Erase(&s_flashDriver, destAddr, pflashSectorSize, kFTFx_ApiEraseKey);
    }
    else
    {
        PRINTF("\r\n Erase/Program opeation will not be executed, as Flash is SECURE!");
    }

    app_finalize();

    return 0;
}
