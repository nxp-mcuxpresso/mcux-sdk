/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
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

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define BUFFER_LEN 16

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
/*! @brief Buffer for program */
static uint8_t s_buffer[BUFFER_LEN];
/*! @brief Buffer for readback */
static uint8_t s_buffer_rbc[BUFFER_LEN];

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
    status_t result;    /* Return code from each flash driver function */
    uint32_t destAdrss; /* Address of the target location */
    uint32_t i;

    uint32_t EEpromBlockBase  = 0;
    uint32_t EEpromTotalSize  = 0;
    uint32_t EEpromSectorSize = 0;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Clean up Flash driver Structure*/
    memset(&s_flashDriver, 0, sizeof(flash_config_t));

    FLASH_SetProperty(&s_flashDriver, kFLASH_PropertyFlashClockFrequency, 20000000U);
    /* Setup flash driver structure for device and initialize variables. */
    result = FLASH_Init(&s_flashDriver);
    if (kStatus_FLASH_Success != result)
    {
        error_trap();
    }
    /* Get EEprom properties*/
    EEpromBlockBase  = s_flashDriver.EEpromBlockBase;
    EEpromTotalSize  = s_flashDriver.EEpromTotalSize;
    EEpromSectorSize = s_flashDriver.EEpromSectorSize;

    /* print welcome message */
    PRINTF("\r\n EEprom Example Start \r\n");
    /* Print EEpromEEprom information - EEprom. */
    PRINTF("\r\n EEprom Information: ");
    PRINTF("\r\n EEprom Base Address: (0x%x) ", EEpromBlockBase);
    PRINTF("\r\n EEprom Total Size:\t%d B", EEpromTotalSize);
    PRINTF("\r\n EEprom Sector Size:\t%d B", EEpromSectorSize);

    /* Debug message for user. */
    /* Erase several sectors on upper EEprom block where there is no code */
    PRINTF("\r\n Erase eight sector of EEprom");

/* In case of the protected sectors at the end of the EEprom just select
the block from the end of EEprom to be used for operations
SECTOR_INDEX_FROM_END = 1 means the last sector,
SECTOR_INDEX_FROM_END = 2 means (the last sector - 1) ...
*/
#ifndef SECTOR_INDEX_FROM_END
#define SECTOR_INDEX_FROM_END 8U
#endif

    /* Erase a sector from destAdrss. */
    destAdrss = EEpromBlockBase + (EEpromTotalSize - (SECTOR_INDEX_FROM_END * EEpromSectorSize));
    /*! Eeprom can be written directly by running the FLASH_EepromWrite function,
    Execute this erase function ensures that the eeprom is in the erased state*/
    result = FLASH_EraseEEprom(&s_flashDriver, destAdrss, sizeof(s_buffer), kFLASH_ApiEraseKey);
    if (kStatus_FLASH_Success != result)
    {
        error_trap();
    }
    /* Prepare user buffer. */
    for (i = 0; i < BUFFER_LEN; i++)
    {
        s_buffer[i] = 0xFF;
    }
    /* Verify erase by reading back from eeprom directly*/
    for (i = 0; i < BUFFER_LEN; i++)
    {
        s_buffer_rbc[i] = *(volatile uint8_t *)(destAdrss + i);
        if (s_buffer_rbc[i] != s_buffer[i])
        {
            error_trap();
        }
    }
    /* Print message for user. */
    PRINTF("\r\n Program a buffer to a sector of eeprom ");

    /* Prepare user buffer. */
    for (i = 0; i < BUFFER_LEN; i++)
    {
        s_buffer[i] = i;
    }
    /* Program user buffer into eeprom*/
    for (uint32_t i = 0; i < (sizeof(s_buffer) / 4); i++)
    {
        result = FLASH_EepromWrite(&s_flashDriver, destAdrss + i * 4, (uint8_t *)(&s_buffer[0] + i * 4), 4);
        if (kStatus_FLASH_Success != result)
        {
            error_trap();
        }
    }

#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
    /* Clean the D-Cache before reading the eeprom data*/
    SCB_CleanInvalidateDCache();
#endif
    /* Verify programming by reading back from eeprom directly*/
    for (i = 0; i < BUFFER_LEN; i++)
    {
        s_buffer_rbc[i] = *(volatile uint8_t *)(destAdrss + i);
        if (s_buffer_rbc[i] != s_buffer[i])
        {
            error_trap();
        }
    }
    PRINTF("\r\n Successfully Programmed and Verified Location 0x%x -> 0x%x \r\n", destAdrss,
           (destAdrss + sizeof(s_buffer)));

    FLASH_EraseEEprom(&s_flashDriver, destAdrss, sizeof(s_buffer), kFLASH_ApiEraseKey);
    app_finalize();

    return 0;
}
