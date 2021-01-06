/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_sdram.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Defines the sdram nop delay counts in initialize sequence. */
#define SDRAM_DELAY_COUNTS (125U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static status_t SDRAM_InitSequence(SDRAM_Type *base,
                                   uint32_t address,
                                   sdramc_block_selection_t whichBlock,
                                   sdram_burst_len_t burstLen,
                                   sdram_burst_type_t burstType,
                                   sdram_cas_latency_t casLatency,
                                   sdram_operation_mode_t opMode,
                                   sdram_write_burst_mode_t writeBurstMode);

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t SDRAM_Init(SDRAM_Type *base, uint32_t address, uint32_t busClock_Hz)
{
    assert(address);

    sdramc_config_t config;
    sdramc_refresh_config_t refConfig;
    sdramc_blockctl_config_t ctlConfig;

    /* SDRAM refresh timing configuration. */
    refConfig.refreshTime = kSDRAMC_RefreshThreeClocks;
    /* Refresh time 4096 rows/ 64ms. */
    refConfig.sdramRefreshRow = 15625;
    refConfig.busClock_Hz     = busClock_Hz;

    /* SDRAM controller configuration. */
    /* Port size: 16 bit, Command bit location: bit 20. */
    ctlConfig.portSize = kSDRAMC_PortSize16Bit;
    ctlConfig.location = kSDRAMC_Commandbit20;
    ctlConfig.block    = kSDRAMC_Block0;
    /* SDRAM with trcd-15ns(min), trp-15ns(min), tras-37ns (min). */
    ctlConfig.latency     = kSDRAMC_LatencyOne;
    ctlConfig.address     = address;
    ctlConfig.addressMask = 0xfc0000;

    config.refreshConfig  = &refConfig;
    config.blockConfig    = &ctlConfig;
    config.numBlockConfig = 1;

    /* SDRAM controller initialization. */
    SDRAMC_Init(base, &config);

    /* SDRAM initialization sequence. */
    return SDRAM_InitSequence(base, address, kSDRAMC_Block0, kSDRAM_MrsBurstLenOne, kSDRAM_MrsSequential,
                              kSDRAM_MrsLatencyTwo, kSDRAM_MrsStandOperation, kSDRAM_MrsWriteBurst);
}

/*!
 * @brief The SDRAM Initializes sequence.
 *
 */
static status_t SDRAM_InitSequence(SDRAM_Type *base,
                                   uint32_t address,
                                   sdramc_block_selection_t whichBlock,
                                   sdram_burst_len_t burstLen,
                                   sdram_burst_type_t burstType,
                                   sdram_cas_latency_t casLatency,
                                   sdram_operation_mode_t opMode,
                                   sdram_write_burst_mode_t writeBurstMode)
{
    uint32_t count   = SDRAM_DELAY_COUNTS;
    uint8_t *mrsAddr = NULL;
    uint32_t addr    = 0U;

    /* Issue a PALL command. */
    SDRAMC_SendCommand(base, whichBlock, kSDRAMC_PrechargeCommand);

    /* Accessing a SDRAM location. */
    *(uint8_t *)(address) = SDRAM_COMMAND_ACCESSVALUE;

    /* Enable the refresh. */
    SDRAMC_SendCommand(base, whichBlock, kSDRAMC_AutoRefreshEnableCommand);

    /* Wait for at least 8 refresh cycles. */
    while (count != 0U)
    {
        __NOP();
        count--;
    }

    /* Issue MSR command. */
    SDRAMC_SendCommand(base, whichBlock, kSDRAMC_ImrsCommand);

    /* Put the right value on SDRAM address bus for SDRAM mode register,
     *  The address of SDRAM Pins is as below:
     *  A2 ~ A0:   burst length   0
     *     000->1
     *     001->2
     *     010->4
     *     011->8
     *     res
     * A3:   burst type
     *        0 -> seq
     *        1 -> Interleave
     *
     * A6 ~ A4:  CAS latency  (should be set to equal to the tcasl in "sdram_latency_t")
     *       000-> res
     *       001-> 1
     *       010-> 2
     *       011-> 3
     *       res
     * A8 ~ A7:  Operationg Mode
     *       00->Stardard Operation
     *       res
     * A9:    Write Burst Mode
     *       0-> Programmed Burst Length
     *      1-> Single Location Access
     */
    /* A2-A0. */
    if (((uint8_t)burstLen & 0x1U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A0;
    }
    if (((uint8_t)burstLen & 0x2U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A1;
    }
    if (((uint8_t)burstLen & 0x4U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A2;
    }

    /* Sdram address A3. */
    if (((uint8_t)burstType & 0x1U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A3;
    }

    /* Sdram address A6-A4. */
    if (((uint8_t)casLatency & 0x1U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A4;
    }
    if (((uint8_t)casLatency & 0x2U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A5;
    }
    if (((uint8_t)casLatency & 0x4U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A6;
    }

    /* Sdram address A8-A7. */
    if (((uint8_t)opMode & 0x1U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A7;
    }
    if (((uint8_t)opMode & 0x2U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A8;
    }

    /* Sdram address A9. */
    if (((uint8_t)writeBurstMode & 0x1U) != 0x00U)
    {
        addr |= 1UL << SDRAM_A9;
    }
    /* Set MRS register. */
    mrsAddr = (uint8_t *)(address + addr);
    /* Access sdram location. */
    *mrsAddr = SDRAM_COMMAND_ACCESSVALUE;

    return kStatus_Success;
}
