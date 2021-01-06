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

/*! @brief Set 32B FlexRAM Size(EEESIZE) for EEprom, Subsystem A = B = EEESIZE / 2 */
#define EEPROM_DATA_SET_SIZE_CODE (0x39U)

/*! @brief Set EEprom backup memory */
#if ((FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011 != 0xFFFFFFFF) && \
     (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0011 != 0x00000000) && \
     (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0011 != 0xFFFF) &&    \
     (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0011 != 0x0000))
#define FLEXNVM_PARTITION_CODE (0x3U)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0100 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0100 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0100 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0x4U)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_0101 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0101 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_0101 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0x5U)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1001 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1001 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1001 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0x9U)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1010 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1010 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1010 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0xaU)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1011 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1011 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1011 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0xbU)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1100 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1100 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1100 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0xcU)
#elif (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101 != 0xFFFFFFFF) && \
    (FSL_FEATURE_FLASH_FLEX_NVM_DFLASH_SIZE_FOR_DEPART_1101 != 0x00000000) &&   \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1101 != 0xFFFF) &&      \
    (FSL_FEATURE_FLASH_FLEX_NVM_EEPROM_SIZE_FOR_EEESIZE_1101 != 0x0000)
#define FLEXNVM_PARTITION_CODE (0xdU)
#else
#define FLEXNVM_PARTITION_CODE (0x8U)
#endif
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
    PRINTF("\r\n End of FlexNVM EEprom Example \r\n");
    while (1)
    {
    }
}

/*!
 * @brief Use Standard Software Drivers (SSD) to modify eeprom.
 *
 * @details This function uses SSD to demonstrate flash mode:
 *            + Check eeprom information.
 *            + Program a sector.
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
    PRINTF("\r\n FlexNVM EEprom Example Start \r\n");

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
        PRINTF("\r\n EEprom opeation will not be executed, as Flash is SECURE!");
        app_finalize();
    }
    else
    {
        uint32_t s_buffer[BUFFER_LEN];     /* Buffer for program */
        uint32_t s_buffer_rbc[BUFFER_LEN]; /* Buffer for readback */
        uint32_t destAdrss;                /* Address of the target location */

        uint32_t dflashBlockBase  = 0;
        uint32_t dflashTotalSize  = 0;
        uint32_t eepromBlockBase  = 0;
        uint32_t eepromTotalSize  = 0;
        uint32_t flexramBlockBase = 0;
        uint32_t flexramTotalSize = 0;

        /* Get flash properties*/
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyDflashBlockBaseAddr, &dflashBlockBase);
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyFlexRamBlockBaseAddr, &flexramBlockBase);
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyFlexRamTotalSize, &flexramTotalSize);

        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyEepromTotalSize, &eepromTotalSize);
        if (!eepromTotalSize)
        {
            /* Note: The EEPROM backup size must be at least 16 times the EEPROM partition size in FlexRAM. */
            uint32_t eepromDataSizeCode   = EEPROM_DATA_SET_SIZE_CODE;
            uint32_t flexnvmPartitionCode = FLEXNVM_PARTITION_CODE;

            PRINTF("\r\n There is no available EEprom (FlexNVM) on this Device by default.");
            PRINTF("\r\n Example is trying to configure FlexNVM block as EEprom.");

            result = FLEXNVM_ProgramPartition(&s_flashDriver, kFTFx_PartitionFlexramLoadOptLoadedWithValidEepromData,
                                              eepromDataSizeCode, flexnvmPartitionCode);
            if (kStatus_FTFx_Success != result)
            {
                error_trap();
            }

            /* Reset MCU */
            PRINTF("\r\n Perform a system reset \r\n");
            NVIC_SystemReset();
        }

        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyDflashTotalSize, &dflashTotalSize);
        eepromBlockBase = dflashBlockBase + dflashTotalSize;

        /* Print flash information - EEprom. */
        PRINTF("\r\n EEprom Information: ");
        PRINTF("\r\n EEprom Base Address: (0x%x) ", eepromBlockBase);
        PRINTF("\r\n EEprom Total Size:\t%d B", eepromTotalSize);

        PRINTF("\r\n Make FlexRAM available for EEPROM ");
        result = FLEXNVM_SetFlexramFunction(&s_flashDriver, kFTFx_FlexramFuncOptAvailableForEeprom);
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
        PRINTF("\r\n Now EEPROM data is read and written by accessing the FlexRAM address space ");
        PRINTF("\r\n FlexRAM Base Address: (0x%x) ", flexramBlockBase);

        /* Print message for user. */
        /* Prepare buffer. */
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer[i] = i + 1;
        }

        PRINTF("\r\n Read 16 bytes data from start of EEPROM space");
        destAdrss = flexramBlockBase;
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
            /* Clean the D-Cache before reading the flash data*/
            SCB_CleanInvalidateDCache();
#endif
            s_buffer_rbc[i] = *(volatile uint32_t *)(destAdrss + i * 4);
            if (s_buffer_rbc[i] == s_buffer[i])
            {
                if (i == BUFFER_LEN - 1)
                {
                    PRINTF("\r\n The first 16 bytes data in EEPROM are what we have progrommed before");

                    for (uint32_t i = 0; i < BUFFER_LEN; i++)
                    {
                        s_buffer[i] = 0xFFFFFFFFU;
                    }
                    result = FLEXNVM_EepromWrite(&s_flashDriver, destAdrss, (uint8_t *)s_buffer, sizeof(s_buffer));
                    if (kStatus_FTFx_Success != result)
                    {
                        error_trap();
                    }
                    PRINTF("\r\n Recover the first 16 bytes memory space of EEprom as 0xFFs");
                    app_finalize();
                }
            }
            else if (s_buffer_rbc[i] != 0)
            {
                PRINTF("\r\n The first 16 bytes data in EEPROM are not all 0x00s");
                PRINTF("\r\n Program the first 16 bytes memory space of EEprom as 0x00s");
                /* Prepare buffer. */
                for (uint32_t i = 0; i < BUFFER_LEN; i++)
                {
                    s_buffer[i] = 0;
                }
                result = FLEXNVM_EepromWrite(&s_flashDriver, destAdrss, (uint8_t *)s_buffer, sizeof(s_buffer));
                if (kStatus_FTFx_Success != result)
                {
                    error_trap();
                }
                PRINTF("\r\n Successfully Programmed Location 0x%x -> 0x%x \r\n", destAdrss,
                       (destAdrss + sizeof(s_buffer)));

                /* Reset MCU */
                PRINTF("\r\n Perform a system reset \r\n");
                NVIC_SystemReset();
            }
            else
            {
                if (i == BUFFER_LEN - 1)
                {
                    PRINTF("\r\n The first 16 bytes data in EEPROM are all 0x00s");
                }
            }
        }

        PRINTF("\r\n Program a buffer(16 bytes) into the first 16 bytes memory space of EEprom");
        result = FLEXNVM_EepromWrite(&s_flashDriver, destAdrss, (uint8_t *)s_buffer, sizeof(s_buffer));
        if (kStatus_FTFx_Success != result)
        {
            error_trap();
        }
        PRINTF("\r\n Successfully Programmed Location 0x%x -> 0x%x \r\n", destAdrss, (destAdrss + sizeof(s_buffer)));

        /* Reset MCU */
        PRINTF("\r\n Perform a system reset \r\n");
        NVIC_SystemReset();
    }

    app_finalize();

    return 0;
}
