/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_ocotp.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_OCOTP_FREQ_HZ (CLOCK_GetFreq(kCLOCK_IpgClk))
/* NOTE: enable this feature will write data to the fuse map, and this operation is
 * irreversible. Please refer to the referance manual before using the read/write
 * function, and calling the write API cautiously.
 */
#define EXAMPLE_OCOTP_SHADOW_REGISTER_READ_WRITE_ENABLE 0U

#if defined(EXAMPLE_OCOTP_SHADOW_REGISTER_READ_WRITE_ENABLE) && (EXAMPLE_OCOTP_SHADOW_REGISTER_READ_WRITE_ENABLE)

#ifndef EXAMPLE_OCOTP_FUSE_MAP_ADDRESS
#define EXAMPLE_OCOTP_FUSE_MAP_ADDRESS 0x22
#endif

#ifndef EXAMPLE_OCOTP_FUSE_WRITE_VALUE
#define EXAMPLE_OCOTP_FUSE_WRITE_VALUE 0x12345678
#endif

#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief OCOTP example.
 *
 * @details Just prints version of driver by using OCOTP API.
 */

int main(void)
{
    uint32_t version;

    /* Init hardware*/
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("OCOTP Peripheral Driver Example\r\n\r\n");

    /*
     * When the macro FSL_FEATURE_OCOTP_HAS_TIMING_CTRL is defined as 0, then the
     * OCOTP clock frequency is not used, pass in 0 directly.
     */
#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    OCOTP_Init(OCOTP, EXAMPLE_OCOTP_FREQ_HZ);
#else
    OCOTP_Init(OCOTP, 0U);
#endif

    /* Get the OCOTP controller version. */
    version = OCOTP_GetVersion(OCOTP);
    PRINTF("OCOTP controller version: 0x%08X\r\n\r\n", version);

    /* Example code to write a fuse value and reload the shasdow register to read it back. */
#if defined(EXAMPLE_OCOTP_SHADOW_REGISTER_READ_WRITE_ENABLE) && (EXAMPLE_OCOTP_SHADOW_REGISTER_READ_WRITE_ENABLE)
    status_t status   = kStatus_Success;
    uint32_t fuseData = 0U;

    status = OCOTP_ReadFuseShadowRegisterExt(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, &fuseData, 1);

    if (status != kStatus_Success)
    {
        PRINTF("Could not read fuse data\r\n");
        while (1)
            ;
    }

    PRINTF("The origin value of fuse address 0x%02X is 0x%08X\r\n", EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, fuseData);

    status = OCOTP_WriteFuseShadowRegister(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, EXAMPLE_OCOTP_FUSE_WRITE_VALUE);

    if (kStatus_Success == status)
    {
        PRINTF("OCOTP Write operation success!\r\n");

        status = OCOTP_ReadFuseShadowRegisterExt(OCOTP, EXAMPLE_OCOTP_FUSE_MAP_ADDRESS, &fuseData, 1);

        if (status != kStatus_Success)
        {
            PRINTF("Could not read fuse data\r\n");
            while (1)
                ;
        }

        PRINTF("The new value is 0x%08X\r\n", fuseData);
    }
    else
    {
        PRINTF("OCOTP write operation failed. Access deny!\r\n");
    }
#endif

    while (1)
    {
    }
}
