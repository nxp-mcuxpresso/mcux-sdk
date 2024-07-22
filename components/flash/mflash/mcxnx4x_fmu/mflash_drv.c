/*
 * Copyright 2017-2020, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>

#include "mflash_drv.h"

#define IFLASH_CMD_RD1ALL  0x00U // Read 1s all
#define IFLASH_CMD_RD1BLK  0x01U // Read 1s block
#define IFLASH_CMD_RD1SCR  0x02U // Read 1s sector
#define IFLASH_CMD_RD1PG   0x03U // Read 1s page
#define IFLASH_CMD_RD1PHR  0x04U // Read 1s phrase
#define IFLASH_CMD_RDMISR  0x05U // Read into MISR
#define IFLASH_CMD_RD1ISCR 0x12U // Read 1s IFR sector
#define IFLASH_CMD_RD1IPG  0x13U // Read 1s IFR page
#define IFLASH_CMD_RD1IPHR 0x14U // Read 1s IFR phrase
#define IFLASH_CMD_RDIMISR 0x15U // Read IFR into MISR
#define IFLASH_CMD_PGMPG   0x23U // Program page
#define IFLASH_CMD_PGMPHR  0x24U // Program phrase
#define IFLASH_CMD_ERSALL  0x40U // Erase all
#define IFLASH_CMD_ERSSCR  0x42U // Erase sector

#define IFLASH_ERROR_STAT_FLAGS (FMU_FSTAT_ACCERR_MASK | FMU_FSTAT_PVIOL_MASK | FMU_FSTAT_CMDABT_MASK)

static void iflash_prepare(void)
{
    uint32_t fmu_fstat = FMU0->FSTAT;

    while ((fmu_fstat & FMU_FSTAT_CCIF_MASK) != FMU_FSTAT_CCIF(1))
    {
        fmu_fstat = FMU0->FSTAT;
    }

    if ((fmu_fstat & IFLASH_ERROR_STAT_FLAGS) != 0UL)
    {
        FMU0->FSTAT = IFLASH_ERROR_STAT_FLAGS;
    }
}

static status_t iflash_launch_command(bool pe_command, uint8_t pe_type)
{
    FMU0->FSTAT = FMU_FSTAT_CCIF_MASK;

    if (pe_command)
    {
        uint32_t fmu_fstat = FMU0->FSTAT;

        while ((fmu_fstat & FMU_FSTAT_PEWEN_MASK) != FMU_FSTAT_PEWEN(pe_type))
        {
            if ((fmu_fstat & FMU_FSTAT_CCIF_MASK) != 0UL)
            {
                return kStatus_Fail;
            }

            fmu_fstat = FMU0->FSTAT;
        }
    }

    return kStatus_Success;
}

static status_t iflash_finish_command(bool pe_command)
{
    uint32_t fmu_fstat;

    if (pe_command)
    {
        fmu_fstat = FMU0->FSTAT;

        while ((fmu_fstat & FMU_FSTAT_PERDY_MASK) != FMU_FSTAT_PERDY(1))
        {
            if ((fmu_fstat & FMU_FSTAT_CCIF_MASK) != 0UL)
            {
                return kStatus_Fail;
            }

            fmu_fstat = FMU0->FSTAT;
        }

        FMU0->FSTAT = FMU_FSTAT_PERDY_MASK;
    }

    fmu_fstat = FMU0->FSTAT;

    while ((fmu_fstat & FMU_FSTAT_CCIF_MASK) == 0UL)
    {
        fmu_fstat = FMU0->FSTAT;
    }

    return kStatus_Success;
}

int32_t mflash_drv_init(void)
{
    /* enable the Flash clock if not already set */
    CLOCK_SetupClockCtrl(SYSCON_CLOCK_CTRL_FRO12MHZ_ENA_MASK);

    return kStatus_Success;
}

int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    status_t ret;
    uint32_t primask;

    if ((sector_addr % MFLASH_SECTOR_SIZE) != 0UL)
    {
        return kStatus_InvalidArgument;
    }

    primask = __get_PRIMASK();
    __disable_irq();

    iflash_prepare();

    FMU0->FCCOB[0] = IFLASH_CMD_ERSSCR;
    FMU0->FCCOB[1] = 0x00U;

    ret = iflash_launch_command(true, 1);

    if (ret != kStatus_Success)
    {
        goto cleanup;
    }

    *(uint32_t *)(sector_addr)        = 0UL;
    *(uint32_t *)(sector_addr + 0x04UL) = 0UL;
    *(uint32_t *)(sector_addr + 0x08UL) = 0UL;
    *(uint32_t *)(sector_addr + 0x0CUL) = 0UL;

    ret = iflash_finish_command(true);

cleanup:

    if (primask == 0UL)
    {
        __enable_irq();
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return ret;
}

int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    status_t ret;
    uint32_t primask;

    if ((page_addr % MFLASH_PAGE_SIZE) != 0UL)
    {
        return kStatus_InvalidArgument;
    }

    primask = __get_PRIMASK();
    __disable_irq();

    iflash_prepare();

    FMU0->FCCOB[0] = IFLASH_CMD_PGMPG;
    FMU0->FCCOB[1] = 0x00U;

    ret = iflash_launch_command(true, 2);
    if (ret != kStatus_Success)
    {
        goto cleanup;
    }

    for (uint32_t i = 0UL; i < MFLASH_PAGE_SIZE; i += 4UL)
    {
        *(uint32_t *)(page_addr + i) = ((uint32_t *)data)[i / 4UL];
    }

    ret = iflash_finish_command(true);

cleanup:

    if (primask == 0UL)
    {
        __enable_irq();
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return ret;
}

int32_t mflash_drv_phrase_program(uint32_t phrase_addr, uint32_t *data)
{
    status_t ret;
    uint32_t primask;

    if ((phrase_addr % MFLASH_PHRASE_SIZE) != 0UL)
    {
        return kStatus_InvalidArgument;
    }

    primask = __get_PRIMASK();
    __disable_irq();

    iflash_prepare();

    FMU0->FCCOB[0] = IFLASH_CMD_PGMPHR;
    FMU0->FCCOB[1] = 0x00U;

    ret = iflash_launch_command(true, 1);
    if (ret != kStatus_Success)
    {
        goto cleanup;
    }

    for (uint32_t i = 0UL; i < MFLASH_PHRASE_SIZE; i += 4UL)
    {
        *(uint32_t *)(phrase_addr + i) = ((uint32_t *)data)[i / 4UL];
    }

    ret = iflash_finish_command(true);

cleanup:

    if (primask == 0UL)
    {
        __enable_irq();
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return ret;
}

int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    (void)memcpy((void *)buffer, (void *)addr, len);
    return kStatus_Success;
}

void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
    /* FLASH is directly mapped in the address space */
    return (void *)(addr);
}

uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    /* FLASH is directly mapped in the address space */
    return (uint32_t)ptr;
}
