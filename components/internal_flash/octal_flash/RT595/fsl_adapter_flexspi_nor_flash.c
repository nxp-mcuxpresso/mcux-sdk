/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*!*********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "fsl_common.h"
#include "fsl_flexspi.h"

#include "fsl_adapter_flash.h"
#include "fsl_cache.h"

/*****************************************************************************
 *****************************************************************************
 * Private macros
 *****************************************************************************
 *****************************************************************************/

#define NOR_CMD_LUT_SEQ_IDX_READ            0
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS      1
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE     2
#define NOR_CMD_LUT_SEQ_IDX_READID_OPI      3
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI 4
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR     5
#define NOR_CMD_LUT_SEQ_IDX_CHIPERASE       6
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM     7
#define NOR_CMD_LUT_SEQ_IDX_ENTEROPI        8
/* NOTE: Workaround for debugger.
   Must define AHB write FlexSPI sequence index to 9 to avoid debugger issue.
   Debugger can attach to the CM33 core only when ROM executes to certain place.
   At that point, AHB write FlexSPI sequence index is set to 9, but in LUT, the
   command is not filled by ROM. If the debugger sets software breakpoint at flash
   after reset/attachment, FlexSPI AHB write command will be triggered. It may
   cause AHB bus hang if the command in LUT sequence index 9 is any read opeartion.
   So we need to ensure at any time, the FlexSPI LUT sequence 9 for the flash must
   be set to STOP command to avoid unexpected debugger behaivor.
 */
#define NOR_CMD_LUT_SEQ_IDX_WRITE          9
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI 10

#define CUSTOM_LUT_LENGTH        60
#define FLASH_BUSY_STATUS_POL    1
#define FLASH_BUSY_STATUS_OFFSET 0
#define FLASH_ERROR_STATUS_MASK  0x0e
#define FLASH_ENABLE_OCTAL_CMD   0x02
#define CACHE_MAINTAIN           1

#define FLASH_SIZE                      0x10000 /* 512Mb/KByte */
#define FLASH_PAGE_SIZE                 256U
#define SECTOR_SIZE                     0x1000U /* 4K */
#define FLASH_PORT                      kFLEXSPI_PortA1
#define EXAMPLE_FLEXSPI_RX_SAMPLE_CLOCK kFLEXSPI_ReadSampleClkExternalInputFromDqsPad

#define FLEXSPI_AMBA_BASE FlexSPI0_AMBA_BASE

/* Weak function. */
#if defined(__GNUC__)
#define __WEAK_FUNC __attribute__((weak))
#elif defined(__ICCARM__)
#define __WEAK_FUNC __weak
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __WEAK_FUNC __attribute__((weak))
#endif

/*!*********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

/*!*********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
__WEAK_FUNC void flash_reset_config(void);

/*!*********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
static FLEXSPI_Type *s_flexspiBase[] = FLEXSPI_BASE_PTRS;

flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 99000000,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 3,
    .CSSetupTime          = 3,
    .dataValidTime        = 2,
    .columnspace          = 0,
    .enableWordAddress    = 0,
    .AWRSeqIndex          = NOR_CMD_LUT_SEQ_IDX_WRITE,
    .AWRSeqNumber         = 1,
    .ARDSeqIndex          = NOR_CMD_LUT_SEQ_IDX_READ,
    .ARDSeqNumber         = 1,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 0,
};

static const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {

    /*  OPI DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xEE, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x11),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /* Read status register */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x60),
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x08),
    [4 * NOR_CMD_LUT_SEQ_IDX_READID_OPI + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /*  Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x06, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xF9),

    /*  Erase Sector */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x21, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xDE),
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_STOP, kFLEXSPI_8PAD, 0),

    /*  Erase Chip */
    [4 * NOR_CMD_LUT_SEQ_IDX_CHIPERASE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x60, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x9F),

    /*  Program */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x12, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xED),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x04),

    /* Enter OPI mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x72, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_ENTEROPI + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /*  Dummy write, do nothing when AHB write command is triggered. */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

    /*  Read status register using Octal DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xFA),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

};

/*****************************************************************************
 *****************************************************************************
 * Private functions
 *****************************************************************************
 *****************************************************************************/

static status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t baseAddr, bool enableOctal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write enable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    if (enableOctal)
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_OPI;
    }
    else
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;
    }

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base, bool enableOctal)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    if (enableOctal)
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI;
    }
    else
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READSTATUS;
    }

    flashXfer.data     = &readValue;
    flashXfer.dataSize = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (FLASH_BUSY_STATUS_POL)
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = true;
            }
            else
            {
                isBusy = false;
            }
        }
        else
        {
            if (readValue & (1U << FLASH_BUSY_STATUS_OFFSET))
            {
                isBusy = false;
            }
            else
            {
                isBusy = true;
            }
        }

    } while (isBusy);

    return status;
}
status_t flexspi_nor_enable_octal_mode(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;
    uint32_t writeValue = FLASH_ENABLE_OCTAL_CMD;

    /* Write enable */
    status = flexspi_nor_write_enable(base, 0, false);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable quad mode. */
    flashXfer.deviceAddress = 0;
    flashXfer.port          = FLASH_PORT;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ENTEROPI;
    flashXfer.data          = &writeValue;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base, true);

    return status;
}
static void flexspi_nor_invalid_flexspi_cache(void)
{
    CACHE64_CTRL0->CCR |= CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while (CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_GO_MASK)
    {
    }
    CACHE64_CTRL0->CCR &= ~(CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK);
}

/*!*********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*!
 * @brief Initializes the global flash properties structure members.
 *
 * This function initializes the Flash module for the other Flash APIs.
 *
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_ExecuteInRamFunctionNotReady Execute-in-RAM function is not available.
 * @retval #kStatus_HAL_Flash_PartitionStatusUpdateFailure Failed to update the partition status.
 */
hal_flash_status_t HAL_FlashInit(void)
{
    FLEXSPI_Type *base;
    /* As cache depends on FlexSPI power and clock, cache must be initialized after FlexSPI power/clock is set */
    cache64_config_t cacheCfg;
    CACHE64_GetDefaultConfig(&cacheCfg);
    CACHE64_Init(CACHE64_POLSEL0, &cacheCfg);
    flexspi_config_t config;
    uint32_t key;
    uint32_t localLUT[CUSTOM_LUT_LENGTH];

    memcpy(localLUT, customLUT, sizeof(customLUT));

    base = NULL;
    for (uint8_t i = 0; i < (sizeof(s_flexspiBase) / sizeof(FLEXSPI_Type *)); i++)
    {
        if (NULL != s_flexspiBase[i])
        {
            base = s_flexspiBase[i];
            break;
        }
    }
    if (NULL == base)
    {
        return kStatus_HAL_Flash_Fail;
    }
    key = DisableGlobalIRQ();
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    bool CacheEnableFlag = false;
    if (CACHE64_CTRL_CCR_ENCACHE_MASK == (CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK))
    {
        CACHE64_DisableCache(CACHE64_CTRL0);
        CacheEnableFlag = true;
    }
#endif /* __DCACHE_PRESENT */

    /*Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch = true;
    config.rxSampleClock               = EXAMPLE_FLEXSPI_RX_SAMPLE_CLOCK;
#if !(defined(FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN) && FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN)
    config.enableCombination = true;
#endif
    config.ahbConfig.enableAHBBufferable = true;
    config.ahbConfig.enableAHBCachable   = true;
    FLEXSPI_Init(base, &config);

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(base, &deviceconfig, FLASH_PORT);

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(base, 0, localLUT, CUSTOM_LUT_LENGTH);

    /* Do software reset. */
    FLEXSPI_SoftwareReset(base);

#if defined(EXAMPLE_INVALIDATE_FLEXSPI_CACHE)
    EXAMPLE_INVALIDATE_FLEXSPI_CACHE();
#endif
    flexspi_nor_enable_octal_mode(base);
    EnableGlobalIRQ(key);
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    if (CacheEnableFlag)
    {
        CACHE64_EnableCache(CACHE64_CTRL0);
    }
#endif /* __DCACHE_PRESENT */
    flexspi_nor_invalid_flexspi_cache();
    return kStatus_HAL_Flash_Success;
}

/*!
 * \brief  Verify erase data in Flash
 *
 * @param start           The address of the Flash location
 * @param lengthInBytes   The number of bytes to be checked
 * @param margin          Flash margin value
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 */
hal_flash_status_t HAL_FlashVerifyErase(uint32_t start, uint32_t lengthInBytes, hal_flash_margin_value_t margin)
{
    hal_flash_status_t state;
    uint32_t address;
    uint32_t value;

    (void)margin;

    if (start < FLEXSPI_AMBA_BASE)
    {
        return kStatus_HAL_Flash_Fail;
    }

    address = start;

    while (address < (start + lengthInBytes))
    {
        value = 0U;
        if ((address + sizeof(uint32_t)) < (start + lengthInBytes))
        {
            state = HAL_FlashRead(address, sizeof(uint32_t), (uint8_t *)&value);
            if (0xffffffffUL != value)
            {
                return kStatus_HAL_Flash_Fail;
            }
            address += sizeof(uint32_t);
        }
        else
        {
            state = HAL_FlashRead(address, 1, (uint8_t *)&value);
            if (0xffU != value)
            {
                return kStatus_HAL_Flash_Fail;
            }
            address++;
        }

        if (kStatus_HAL_Flash_Success != state)
        {
            return kStatus_HAL_Flash_Fail;
        }
    }

    return kStatus_HAL_Flash_Success;
}

/*!
 * \brief  Write alligned data to FLASH
 *
 * @param dest            The address of the Flash location
 * @param size            The number of bytes to be programed
 * @param pData           Pointer to the data to be programmed to Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashProgram(uint32_t dest, uint32_t size, uint8_t *pData)
{
    FLEXSPI_Type *base;
    uint32_t address;
    uint32_t writeLength;
    status_t status;
    flexspi_transfer_t flashXfer;
    uint32_t key;

#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    bool CacheEnableFlag = false;
    if (CACHE64_CTRL_CCR_ENCACHE_MASK == (CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK))
    {
        CACHE64_DisableCache(CACHE64_CTRL0);
        CacheEnableFlag = true;
    }
#endif /* __DCACHE_PRESENT */

    if (dest < FLEXSPI_AMBA_BASE)
    {
        return kStatus_HAL_Flash_Fail;
    }

    dest = dest - FLEXSPI_AMBA_BASE;

    base = s_flexspiBase[0];

    address = dest;
    while (address < (dest + size))
    {
        if (0U != (address & ((FLASH_PAGE_SIZE - 1U))))
        {
            writeLength = address - (address & (~(FLASH_PAGE_SIZE - 1U)));
            writeLength = FLASH_PAGE_SIZE - writeLength;

            if ((dest + size - address) < writeLength)
            {
                writeLength = (dest + size - address);
            }
        }
        else
        {
            writeLength = dest + size - address;
        }
        if (writeLength > FLASH_PAGE_SIZE)
        {
            writeLength = FLASH_PAGE_SIZE;
        }

        key = DisableGlobalIRQ();
        /* Write enable */
        status = flexspi_nor_write_enable(base, address, true);

        if (status != kStatus_Success)
        {
            EnableGlobalIRQ(key);
            break;
        }

        flashXfer.deviceAddress = address;
        flashXfer.port          = FLASH_PORT;
        flashXfer.cmdType       = kFLEXSPI_Write;
        flashXfer.SeqNumber     = 1;
        flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
        flashXfer.data          = (uint32_t *)((void *)(&pData[address - dest]));
        flashXfer.dataSize      = writeLength;

        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            EnableGlobalIRQ(key);
            break;
        }

        status = flexspi_nor_wait_bus_busy(base, true);
        if (status != kStatus_Success)
        {
            EnableGlobalIRQ(key);
            break;
        }
        address += writeLength;

        FLEXSPI_SoftwareReset(base);
        /*SDK_DelayAtLeastUs(2U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);*/
        for (uint32_t i = 0; i < 500; i++)
        {
            __NOP();
        }
        EnableGlobalIRQ(key);
    }
    __DSB();
    __DSB();
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    if (CacheEnableFlag)
    {
        CACHE64_EnableCache(CACHE64_CTRL0);
    }
#endif /* __DCACHE_PRESENT */

    return (hal_flash_status_t)status;
}

/*!
 * \brief  Write data to FLASH
 *
 * @param dest        The address of the Flash location
 * @param size        The number of bytes to be programed
 * @param pData       Pointer to the data to be programmed to Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashProgramUnaligned(uint32_t dest, uint32_t size, uint8_t *pData)
{
    return HAL_FlashProgram(dest, size, pData);
}

/*!
 * \brief  Erase to 0xFF one or more FLASH sectors.
 *
 * @param dest            The start address of the first sector to be erased
 * @param size            The amount of flash to be erased (multiple of sector size)
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashEraseSector(uint32_t dest, uint32_t size)
{
    FLEXSPI_Type *base;
    uint32_t address;
    status_t status = (status_t)kStatus_HAL_Flash_Error;
    flexspi_transfer_t flashXfer;
    uint32_t key;

    if (dest < FLEXSPI_AMBA_BASE)
    {
        return kStatus_HAL_Flash_Fail;
    }
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    bool CacheEnableFlag = false;
    if (CACHE64_CTRL_CCR_ENCACHE_MASK == (CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK))
    {
        CACHE64_DisableCache(CACHE64_CTRL0);
        CacheEnableFlag = true;
    }
#endif /* Cache64 present */
    dest = dest - FLEXSPI_AMBA_BASE;
    base = s_flexspiBase[0];

    address = dest;
    while (address < (dest + size))
    {
        /* Write enable */
        status = flexspi_nor_write_enable(base, 0, true);

        if (status != kStatus_Success)
        {
            break;
        }

        flashXfer.deviceAddress = address;
        flashXfer.port          = FLASH_PORT;
        flashXfer.cmdType       = kFLEXSPI_Command;
        flashXfer.SeqNumber     = 1;
        flashXfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;

        key    = DisableGlobalIRQ();
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            EnableGlobalIRQ(key);
            break;
        }

        status = flexspi_nor_wait_bus_busy(base, true);

        address += SECTOR_SIZE;

        /* Do software reset. */
        FLEXSPI_SoftwareReset(base);
        /*SDK_DelayAtLeastUs(2U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);*/
        for (uint32_t i = 0; i < 500; i++)
        {
            __NOP();
        }
        EnableGlobalIRQ(key);
    }
    if (status != kStatus_Success)
    {
        key = DisableGlobalIRQ();
        /* Do software reset. */
        FLEXSPI_SoftwareReset(base);
        /*SDK_DelayAtLeastUs(2U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);*/
        for (uint32_t i = 0; i < 500; i++)
        {
            __NOP();
        }
        EnableGlobalIRQ(key);
    }
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    if (CacheEnableFlag)
    {
        CACHE64_EnableCache(CACHE64_CTRL0);
    }
#endif /* Cache64 present */

    return (hal_flash_status_t)status;
}

/*!
 * \brief  Read data from FLASH
 *
 *
 * @param scr             The address of the Flash location to be read
 * @param size            The number of bytes to be read
 * @param pData           Pointer to the data to be read from Flash
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 *
 */
hal_flash_status_t HAL_FlashRead(uint32_t src, uint32_t size, uint8_t *pData)
{
#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    bool CacheEnableFlag = false;
    if (CACHE64_CTRL_CCR_ENCACHE_MASK == (CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_ENCACHE_MASK))
    {
        CACHE64_DisableCache(CACHE64_CTRL0);
        CacheEnableFlag = true;
    }
#endif /* __DCACHE_PRESENT */
    (void)memcpy(pData, (uint8_t *)src, size);

#if defined(FSL_FEATURE_SOC_CACHE64_CTRL_COUNT) && (FSL_FEATURE_SOC_CACHE64_CTRL_COUNT > 1U)
    if (CacheEnableFlag)
    {
        CACHE64_EnableCache(CACHE64_CTRL0);
    }
#endif /* __DCACHE_PRESENT */
    return kStatus_HAL_Flash_Success;
}

/*!
 * @brief Returns the desired hal flash property.
 *
 * @param Property        The desired property from the list of properties in
 *                        enum hal_flash_property_tag_t
 * @param value           A pointer to the value returned for the desired flash property.
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_Success Flash currently not support.
 */
hal_flash_status_t HAL_FlashGetProperty(hal_flash_property_tag_t property, uint32_t *value)
{
    return kStatus_HAL_Flash_Success;
}

/*!
 * @brief Set the desired hal flash property.
 *
 * @param Property        The desired property from the list of properties in
 *                        enum hal_flash_property_tag_t
 * @param value           The value would be set to the desired flash property.
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_Success Flash currently not support.
 */
hal_flash_status_t HAL_FlashSetProperty(hal_flash_property_tag_t property, uint32_t value)
{
    return kStatus_HAL_Flash_Success;
}

/*!
 * @brief Returns the security state via the pointer passed into the function.
 *
 * This function retrieves the current flash security status, including the
 * security enabling state and the backdoor key enabling state.
 *
 * @param state           A pointer to the value returned for the current security status
 *
 * @retval #kStatus_HAL_Flash_Success API was executed successfully.
 * @retval #kStatus_HAL_Flash_InvalidArgument An invalid argument is provided.
 * @retval #kStatus_HAL_Flash_Success Flash currently not support.
 */
hal_flash_status_t HAL_FlashGetSecurityState(hal_flash_security_state_t *state)
{
    return kStatus_HAL_Flash_Success;
}
