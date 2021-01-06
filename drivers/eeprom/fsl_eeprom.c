/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_eeprom.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.eeprom"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the EEPROM instance from peripheral base address.
 *
 * @param base EEPROM peripheral base address.
 * @return EEPROM instance.
 */
static uint32_t EEPROM_GetInstance(EEPROM_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Array of EEPROM peripheral base address. */
static EEPROM_Type *const s_eepromBases[] = EEPROM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of EEPROM clock name. */
static const clock_ip_name_t s_eepromClock[] = EEPROM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t EEPROM_GetInstance(EEPROM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_eepromBases); instance++)
    {
        if (s_eepromBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_eepromBases));

    return instance;
}

/*!
 * brief Get EEPROM default configure settings.
 *
 * param config  EEPROM config structure pointer.
 */
void EEPROM_GetDefaultConfig(eeprom_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->autoProgram     = kEEPROM_AutoProgramWriteWord;
    config->writeWaitPhase1 = 0x5U;
    config->writeWaitPhase2 = 0x9U;
    config->writeWaitPhase3 = 0x3U;
    config->readWaitPhase1  = 0xFU;
    config->readWaitPhase2  = 0x8U;
    config->lockTimingParam = false;
}

static void EEPROM_Flush(EEPROM_Type *base)
{
    /* Write all prepared words */
    EEPROM_ClearInterruptFlag(base, (uint32_t)kEEPROM_ProgramFinishInterruptEnable);
    base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;

    /* Waiting for operation finished */
    while ((EEPROM_GetInterruptStatus(base) & (uint32_t)kEEPROM_ProgramFinishInterruptEnable) == 0UL)
    {
    }
}

/*!
 * brief Initializes the EEPROM with the user configuration structure.
 *
 * This function configures the EEPROM module with the user-defined configuration. This function also sets the
 * internal clock frequency to about 155kHz according to the source clock frequency.
 *
 * param base     EEPROM peripheral base address.
 * param config   The pointer to the configuration structure.
 * param sourceClock_Hz EEPROM source clock frequency in Hz.
 */
void EEPROM_Init(EEPROM_Type *base, const eeprom_config_t *config, uint32_t sourceClock_Hz)
{
    assert(config != NULL);

    uint32_t clockDiv = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the SAI clock */
    CLOCK_EnableClock(s_eepromClock[EEPROM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_EEPROM_HAS_NO_RESET) && FSL_FEATURE_EEPROM_HAS_NO_RESET)
    /* Reset the EEPROM module */
    RESET_PeripheralReset(kEEPROM_RST_SHIFT_RSTn);
#endif /* FSL_FEATURE_EEPROM_HAS_NO_RESET */

#if (defined(FSL_SDK_ENABLE_DRIVER_POWER_CONTROL) && (FSL_SDK_ENABLE_DRIVER_POWER_CONTROL))
    POWER_DisablePD(kPDRUNCFG_PD_EEPROM);

    /* Delay larger than 100us. */
    uint32_t count = SystemCoreClock / 1000;
    while (count--)
    {
        __NOP();
    }
#endif /* FSL_SDK_ENABLE_DRIVER_POWER_CONTROL */

    /* Set the clock divider */
    clockDiv = sourceClock_Hz / (uint32_t)FSL_FEATURE_EEPROM_INTERNAL_FREQ;
    if ((sourceClock_Hz % (uint32_t)FSL_FEATURE_EEPROM_INTERNAL_FREQ) >
        ((uint32_t)FSL_FEATURE_EEPROM_INTERNAL_FREQ / 2UL))
    {
        clockDiv += 1UL;
    }

    if (sourceClock_Hz / clockDiv > (uint32_t)FSL_FEATURE_EEPROM_INTERNAL_FREQ)
    {
        clockDiv += 1UL;
    }

    base->CLKDIV = clockDiv - 1UL;

    /* Set the auto program feature */
    EEPROM_SetAutoProgram(base, config->autoProgram);

    /* Set time delay parameter */
    base->RWSTATE =
        EEPROM_RWSTATE_RPHASE1(config->readWaitPhase1 - 1UL) | EEPROM_RWSTATE_RPHASE2(config->readWaitPhase2 - 1UL);
    base->WSTATE = EEPROM_WSTATE_PHASE1(config->writeWaitPhase1 - 1UL) |
                   EEPROM_WSTATE_PHASE2(config->writeWaitPhase2 - 1UL) |
                   EEPROM_WSTATE_PHASE3(config->writeWaitPhase3 - 1UL);
    base->WSTATE |= EEPROM_WSTATE_LCK_PARWEP(config->lockTimingParam);

    /* Clear the remaining write operation  */
    base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
    while ((EEPROM_GetInterruptStatus(base) & (uint32_t)kEEPROM_ProgramFinishInterruptEnable) == 0UL)
    {
    }
}

/*!
 * brief Deinitializes the EEPROM regions.
 *
 * param base     EEPROM peripheral base address.
 */
void EEPROM_Deinit(EEPROM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the SAI clock */
    CLOCK_DisableClock(s_eepromClock[EEPROM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Write a word data in address of EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * param base     EEPROM peripheral base address.
 * param offset   Offset from the begining address of EEPROM. This value shall be 4-byte aligned.
 * param data     Data need be write.
 */
status_t EEPROM_WriteWord(EEPROM_Type *base, uint32_t offset, uint32_t data)
{
    uint32_t *addr  = NULL;
    status_t status = kStatus_Success;

    if ((offset % 4UL != 0UL) || (offset > (uint32_t)FSL_FEATURE_EEPROM_SIZE))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* Set auto program settings */
        if (base->AUTOPROG != (uint32_t)kEEPROM_AutoProgramDisable)
        {
            EEPROM_SetAutoProgram(base, kEEPROM_AutoProgramWriteWord);
        }

        EEPROM_ClearInterruptFlag(base, (uint32_t)kEEPROM_ProgramFinishInterruptEnable);

        /* Compute the page */
        addr  = (uint32_t *)((uint32_t)FSL_FEATURE_EEPROM_BASE_ADDRESS + offset);
        *addr = data;

        /* Check if manual program erase is needed. */
        if (base->AUTOPROG != (uint32_t)kEEPROM_AutoProgramWriteWord)
        {
            base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
        }

        /* Waiting for operation to finish */
        while ((EEPROM_GetInterruptStatus(base) & (uint32_t)kEEPROM_ProgramFinishInterruptEnable) == 0UL)
        {
        }
    }

    return status;
}

/*!
 * brief Write data from a user allocated buffer in address of EEPROM.
 *
 * Users can write any bytes data into EEPROM address by wBuf.
 *
 * param base     EEPROM peripheral base address.
 * param offset   Offset from the begining address of EEPROM.
 * param wBuf     Data need be write.
 * param size     Number of bytes to write.
 */
void EEPROM_Write(EEPROM_Type *base, uint32_t offset, void *wBuf, uint32_t size)
{
    uint8_t *src;
    bool unalignedStart;
    uint32_t memUnit   = 0;
    uint32_t alignSize = 0;

#if (defined(FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED) && FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED)
    uint16_t *dst;
    alignSize = 2;
    memUnit   = FSL_FEATURE_EEPROM_ROW_SIZE;
#else
    uint32_t i = 0;
    uint32_t *dst;
    uint32_t data32_Align  = 0;
    uint32_t unalignedSize = 0;
    alignSize              = 4;
    memUnit                = FSL_FEATURE_EEPROM_SIZE / FSL_FEATURE_EEPROM_PAGE_COUNT;
#endif /* FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED */

    /* Offset and size must be positive */
    assert(size > 0UL);
    /* All bytes must be written to a valid EEPROM address */
    assert((offset + size) <= (uint32_t)FSL_FEATURE_EEPROM_SIZE);

    src = wBuf;

#if (defined(FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED) && FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED)
    dst            = &((uint16_t *)FSL_FEATURE_EEPROM_BASE_ADDRESS)[offset / alignSize];
    unalignedStart = (offset % alignSize != 0UL);
#else
    dst                    = &((uint32_t *)FSL_FEATURE_EEPROM_BASE_ADDRESS)[offset / alignSize];
    unalignedStart         = (offset % alignSize) != 0UL;
    unalignedSize          = alignSize - (offset % alignSize);
#endif /* FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED */

    while (size > 0UL)
    {
        /* If first byte is to be copied to non aligned EEPROM byte */
        if (unalignedStart)
        {
/* The first byte from the buffer is not 16-bits aligned.
 * Read the LSB from EEPROM to complete it.
 */
#if (defined(FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED) && FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED)
            *dst = (uint16_t)(((uint16_t)src[0] << 8UL) | (*dst & 0x00ffUL));
#else
            /* The first byte from the buffer is not 32-bits aligned.
             * Read the rest of data after position offset and realign them.
             */
            for (i = 0; i < unalignedSize; i++)
            {
                data32_Align |= (uint32_t)((uint32_t)src[i] << (8UL * ((alignSize - unalignedSize) + i)));
            }
            *dst = (*dst & (0xffffffffUL >> (8UL * unalignedSize))) | data32_Align;
#endif                                                 /* FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED */
            src += (alignSize - (offset % alignSize)); /* Operate src to let wBuf pointer offset correct*/
            size -= (alignSize - (offset % alignSize));
            unalignedStart = false;
        }
        else if (size >= alignSize)
        {
#if (defined(FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED) && FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED)
            /* Combine two bytes from the buffer to a 16-bits word */
            *dst = (uint16_t)(((uint16_t)src[1] << 8UL) | (uint16_t)src[0]);
#else
            /* Combine four bytes from the buffer to a 32-bits word */
            *dst = (uint32_t)(((uint32_t)src[3] << 24UL) | ((uint32_t)src[2] << 16UL) | ((uint32_t)src[1] << 8UL) |
                              src[0]);
#endif                        /* FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED */
            src += alignSize; /* Normal operate src to offset wBuf pointer by 4 bytes*/
            size -= alignSize;
        }
        else
        {
/* The last several bytes from the buffer is not 32-bit aligned.
 * Read the rest of bytes of non 32-bit aligned data
 * and realign them by 32-bit aligned */
#if (defined(FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED) && FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED)
            *dst = (uint16_t)((*dst & 0xff00UL) | src[0]);
#else
            data32_Align = 0; /* Clear data32_Align */
            for (i = 0; i < (size % alignSize); i++)
            {
                data32_Align |= (uint32_t)((uint32_t)src[i] << (8UL * i));
            }
            *dst = (*dst & (0xffffffffUL << (8UL * (size % alignSize)))) | data32_Align;
#endif /* FSL_FEATURE_EEPROM_TWOBYTES_ALIGNED */
            size -= (size % alignSize);
        }

        dst++; /* EEPROM mempory pointer go ahead */

        /* When memory unit size reached, have to flush. */
        if ((((uint32_t)dst % memUnit) == 0UL) && (size > 0UL))
        {
            EEPROM_Flush(base);
        }
    }

    /* Normal need to flush after write data into eeprom */
    EEPROM_Flush(base);
}
#if !(defined(FSL_FEATURE_EEPROM_PAGE_COUNT) && FSL_FEATURE_EEPROM_PAGE_COUNT)
status_t EEPROM_WriteRow(EEPROM_Type *base, uint32_t rowNum, uint32_t *data)
{
    uint32_t i      = 0;
    uint32_t *addr  = NULL;
    status_t status = kStatus_Success;

    if ((rowNum > FSL_FEATURE_EEPROM_ROW_COUNT) || (!data))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* Set auto program settings */
        if (base->AUTOPROG != (uint32_t)kEEPROM_AutoProgramDisable)
        {
            EEPROM_SetAutoProgram(base, kEEPROM_AutoProgramLastWord);
        }

        EEPROM_ClearInterruptFlag(base, (uint32_t)kEEPROM_ProgramFinishInterruptEnable);

        addr = (uint32_t *)((uint32_t)FSL_FEATURE_EEPROM_BASE_ADDRESS +
                            rowNum * ((uint32_t)FSL_FEATURE_EEPROM_SIZE / (uint32_t)FSL_FEATURE_EEPROM_ROW_COUNT));
        for (i = 0; i < ((uint32_t)FSL_FEATURE_EEPROM_SIZE / (uint32_t)FSL_FEATURE_EEPROM_ROW_COUNT) / 4UL; i++)
        {
            addr[i] = data[i];
        }

        if (base->AUTOPROG == kEEPROM_AutoProgramDisable)
        {
            base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
        }

        /* Waiting for operation to finish */
        while ((EEPROM_GetInterruptStatus(base) & (uint32_t)kEEPROM_ProgramFinishInterruptEnable) == 0UL)
        {
        }
    }

    return status;
}
#else
/*!
 * brief Write a page data into EEPROM.
 *
 * Users can write a page or at least a word data into EEPROM address.
 *
 * param base     EEPROM peripheral base address.
 * param pageNum  Page number to be written.
 * param data     Data need be write. This array data size shall equals to the page size.
 */
status_t EEPROM_WritePage(EEPROM_Type *base, uint32_t pageNum, uint32_t *data)
{
    uint32_t i = 0;
    uint32_t *addr = NULL;
    status_t status = kStatus_Success;

    if ((pageNum > (uint32_t)FSL_FEATURE_EEPROM_PAGE_COUNT) || (data == NULL))
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        /* Set auto program settings */
        if (base->AUTOPROG != (uint32_t)kEEPROM_AutoProgramDisable)
        {
            EEPROM_SetAutoProgram(base, kEEPROM_AutoProgramLastWord);
        }

        EEPROM_ClearInterruptFlag(base, (uint32_t)kEEPROM_ProgramFinishInterruptEnable);

        addr = (uint32_t *)((uint32_t)FSL_FEATURE_EEPROM_BASE_ADDRESS +
                            pageNum * ((uint32_t)FSL_FEATURE_EEPROM_SIZE / (uint32_t)FSL_FEATURE_EEPROM_PAGE_COUNT));
        for (i = 0; i < ((uint32_t)FSL_FEATURE_EEPROM_SIZE / (uint32_t)FSL_FEATURE_EEPROM_PAGE_COUNT) / 4UL; i++)
        {
            addr[i] = data[i];
        }

        if (base->AUTOPROG == (uint32_t)kEEPROM_AutoProgramDisable)
        {
            base->CMD = FSL_FEATURE_EEPROM_PROGRAM_CMD;
        }

        /* Waiting for operation to finish */
        while ((EEPROM_GetInterruptStatus(base) & (uint32_t)kEEPROM_ProgramFinishInterruptEnable) == 0UL)
        {
        }
    }

    return status;
}
#endif /* FSL_FEATURE_EEPROM_PAGE_COUNT */
