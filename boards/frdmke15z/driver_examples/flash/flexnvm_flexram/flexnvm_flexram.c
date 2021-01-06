/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
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
static status_t FLEXRAM_TraditionalRamWrite(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t i);

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
    PRINTF("\r\n End of FlexRAM as traditional RAM example \r\n");
    while (1)
    {
    }
}

/*! @brief This function is used to program FlexRAM as traditional Ram with the desired data, start address and length.
 */
static status_t FLEXRAM_TraditionalRamWrite(flexnvm_config_t *config,
                                            uint32_t start,
                                            uint8_t *src,
                                            uint32_t lengthInBytes)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    status_t status = kStatus_FTFx_InvalidArgument;
    /* Validates the range of the given address */
    if ((start < config->ftfxConfig.flexramBlockBase) ||
        ((start + lengthInBytes) > (config->ftfxConfig.flexramBlockBase + config->ftfxConfig.flexramTotalSize)))
    {
        return kStatus_FTFx_AddressError;
    }

    PRINTF("\r\n Make FlexRAM available for traditional RAM!\r\n ");
    /* Switch function of FlexRAM if needed */
    if (0U == (FTFx->FCNFG & FTFx_FCNFG_RAMRDY_MASK))
    {
        status = FTFx_CMD_SetFlexramFunction(&s_flashDriver.ftfxConfig, kFTFx_FlexramFuncOptAvailableAsRam);
        if (status != kStatus_FTFx_Success)
        {
            return kStatus_FTFx_RecoverFlexramAsRamError;
        }
    }
    /* wait for flexram as traditional ram. */
    while (0U == (FTFx->FCNFG & FTFx_FCNFG_RAMRDY_MASK))
        ;

    while (lengthInBytes > 0U)
    {
        if ((0U == (start & 0x3U)) && (0U == ((uint32_t)src & 0x3U)) && (lengthInBytes >= 4U))
        {
            *(uint32_t *)start = *(uint32_t *)(uint32_t)src;
            start += 4U;
            src = &src[4];
            lengthInBytes -= 4U;
        }
        else if ((0U == (start & 0x1U)) && (0U == ((uint32_t)src & 0x1U)) && (lengthInBytes >= 2U))
        {
            *(uint16_t *)start = *(uint16_t *)(uint32_t)src;
            start += 2U;
            src = &src[2];
            lengthInBytes -= 2U;
        }
        else
        {
            *(uint8_t *)start = *src;
            start += 1U;
            src = &src[1];
            lengthInBytes -= 1U;
        }
        /* Wait till EEERDY bit is clear */
        while (1U == (FTFx->FCNFG & FTFx_FCNFG_EEERDY_MASK))
        {
        }

        /* Check for protection violation error */
        if (0U != (FTFx->FSTAT & FTFx_FSTAT_FPVIOL_MASK))
        {
            return kStatus_FTFx_ProtectionViolation;
        }
    }

    status = kStatus_FTFx_Success;
    return status;
}

/*!
 * @brief Use Standard Software Drivers (SSD) to modify flexram
 *
 * @details This function uses SSD to demonstrate flash mode:
 *            + Check flexram information.
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
    PRINTF("\r\n FlexRAM as traditional RAM Example Start \r\n");

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

        uint32_t flexramBlockBase = 0;
        uint32_t flexramTotalSize = 0;
        /* Get flexram properties*/
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyFlexRamBlockBaseAddr, &flexramBlockBase);
        FLEXNVM_GetProperty(&s_flashDriver, kFLEXNVM_PropertyFlexRamTotalSize, &flexramTotalSize);

        PRINTF("\r\n FlexRAM Base Address: 0x%x\r\n", flexramBlockBase);
        PRINTF("\r\n FlexRAM Total Size: 0x%x\r\n", flexramTotalSize);

        /* Print message for user.*/
        PRINTF("\r\n write 16 bytes data to flexram basse address:0x%x\r\n\r\n", flexramBlockBase);
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer[i] = i + 1;
            PRINTF("%d ", s_buffer[i]);
        }

        destAdrss = flexramBlockBase;
        PRINTF("\r\n\r\n Stat to program... \r\n");
        result = FLEXRAM_TraditionalRamWrite(&s_flashDriver, destAdrss, (uint8_t *)s_buffer, sizeof(s_buffer));
        if (result != kStatus_FTFx_Success)
        {
            error_trap();
        }

        /* Verify programming by reading back from flexRAM directly*/
        for (uint32_t i = 0; i < BUFFER_LEN; i++)
        {
            s_buffer_rbc[i] = *(volatile uint32_t *)(destAdrss + i * 4);
            if (s_buffer_rbc[i] == s_buffer[i])
            {
                PRINTF("%d ", s_buffer_rbc[i]);
            }
            else
            {
                error_trap();
            }
        }

        PRINTF("\r\n\r\n Successfully Programmed and Verified Location 0x%x -> 0x%x \r\n", destAdrss,
               (destAdrss + sizeof(s_buffer)));
    }

    app_finalize();

    return 0;
}
