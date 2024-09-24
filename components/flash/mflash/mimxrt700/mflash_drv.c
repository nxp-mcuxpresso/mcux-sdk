/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#include "mflash_drv.h"
#include "fsl_xspi.h"
#include "fsl_cache.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define XSPI_INSTANCE        XSPI0
#define XSPI_CLOCK           kCLOCK_Xspi0
#define XSPI_RX_SAMPLE_CLOCK kXSPI_ReadSampleClkExternalInputFromDqsPad

/* Octal mode used by default, pinmux already set to this mode.
   NOTE: Quad mode has not beed tested */

#if !defined(MFLASH_USE_OCTAL_MODE) || MFLASH_USE_OCTAL_MODE
#define USE_OCTAL_MODE true
#else
#define USE_OCTAL_MODE false
#endif

#define NOR_CMD_LUT_SEQ_IDX_READ              0
#define NOR_CMD_LUT_SEQ_IDX_READ_STATUS       1
#define NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI   2
#define NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE      3
#define NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE_OPI  4
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OCTAL 7
#define NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR      8
#define NOR_CMD_LUT_SEQ_IDX_READ_ID_SPI       9
#define NOR_CMD_LUT_SEQ_IDX_READ_ID_OPI       10
#define NOR_CMD_LUT_SEQ_IDX_ERASE_CHIP        11
#define NOR_CMD_LUT_SEQ_IDX_ENTER_OPI         12

#define CUSTOM_LUT_LENGTH        80
#define FLASH_BUSY_STATUS_OFFSET 0
#define FLASH_WE_STATUS_OFFSET   7
#define FLASH_ENABLE_OCTAL_CMD   0x02

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static xspi_device_ddr_config_t flashDDrConfig = {
    .ddrDataAlignedClk         = kXSPI_DDRDataAlignedWith2xInternalRefClk,
    .enableDdr                 = true,
    .enableByteSwapInOctalMode = false,
};
static xspi_device_config_t deviceconfig = {
    .xspiRootClk     = 400000000,                                   /*!< 400MHz */
    .enableCknPad    = false,                                       /*!< Do not support differential clock */
    .deviceInterface = kXSPI_StrandardExtendedSPI,                  /*!< Support Single IO and Octal IO */
    .interfaceSettings.strandardExtendedSPISettings.pageSize = 256, /*!< 256 byte page buffer. */
    .CSHoldTime                                              = 3,
    .CSSetupTime                                             = 3,
    .sampleClkConfig.sampleClkSource       = kXSPI_SampleClkFromExternalDQS, /*!< Device support Data strobe signal.  */
    .sampleClkConfig.enableDQSLatency      = false,
    .sampleClkConfig.dllConfig.dllMode     = kXSPI_AutoUpdateMode,
    .sampleClkConfig.dllConfig.useRefValue = true,
    .sampleClkConfig.dllConfig.enableCdl8  = false,
    .ptrDeviceDdrConfig                    = &flashDDrConfig,
    .addrMode                              = kXSPI_DeviceByteAddressable,
    .columnAddrWidth                       = 0U,
    .enableCASInterleaving                 = false,
    .deviceSize[0]                         = MFLASH_FLASH_SIZE / 1024U,
    .deviceSize[1]    = MFLASH_FLASH_SIZE / 1024U, /*!< Single DIE flash, so deviceSize1 should equal to deviceSize0. */
    .ptrDeviceRegInfo = NULL,                      /*!< Not used in this example. */
};

static const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /*Read*/
    [5 * NOR_CMD_LUT_SEQ_IDX_READ] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0xEE, kXSPI_Command_DDR, kXSPI_8PAD, 0x11),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ + 1] =
        XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x20, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 0x12),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ + 2] =
        XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 0x2, kXSPI_Command_READ_DDR, kXSPI_8PAD, 0x4),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ + 3] = XSPI_LUT_SEQ(kXSPI_Command_STOP, kXSPI_8PAD, 0x0, 0, 0, 0),

    /*Read status SPI*/
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_STATUS] =
        XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x05, kXSPI_Command_READ_SDR, kXSPI_1PAD, 0x04),

    /* Read Status OPI */
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x05, kXSPI_Command_DDR, kXSPI_8PAD, 0xFA),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI + 1] =
        XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x20, kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 0x12),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI + 2] =
        XSPI_LUT_SEQ(kXSPI_Command_DUMMY_SDR, kXSPI_8PAD, 0x2, kXSPI_Command_READ_DDR, kXSPI_8PAD, 0x4),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI + 3] = XSPI_LUT_SEQ(kXSPI_Command_STOP, kXSPI_8PAD, 0x0, 0, 0, 0),

    /*Write enable*/
    [5 * NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE] =
        XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x06, kXSPI_Command_STOP, kXSPI_1PAD, 0x04),

    /* Write Enable - OPI */
    [5 * NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE_OPI] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x06, kXSPI_Command_DDR, kXSPI_8PAD, 0xF9),

    /* Read ID */
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_ID_OPI + 0] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x9F, kXSPI_Command_DDR, kXSPI_8PAD, 0x60),
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_ID_OPI + 1] = XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR,
                                                             kXSPI_8PAD,
                                                             0x20,
                                                             kXSPI_Command_DUMMY_SDR,
                                                             kXSPI_8PAD,
                                                             0x04), /*address is 0x00,0x00,0x00,0x00*/
    [5 * NOR_CMD_LUT_SEQ_IDX_READ_ID_OPI + 2] =
        XSPI_LUT_SEQ(kXSPI_Command_READ_DDR, kXSPI_8PAD, 0x04, kXSPI_Command_STOP, kXSPI_1PAD, 0x0),

    /* Erase Sector */
    [5 * NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x21, kXSPI_Command_DDR, kXSPI_8PAD, 0xDE),
    [5 * NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR + 1] =
        XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x20, kXSPI_Command_STOP, kXSPI_8PAD, 0x0),

    /* Enable OPI DDR mode */
    [5 * NOR_CMD_LUT_SEQ_IDX_ENTER_OPI] =
        XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x72, kXSPI_Command_SDR, kXSPI_1PAD, 0x00),
    [5 * NOR_CMD_LUT_SEQ_IDX_ENTER_OPI + 1] =
        XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x00, kXSPI_Command_SDR, kXSPI_1PAD, 0x00),
    [5 * NOR_CMD_LUT_SEQ_IDX_ENTER_OPI + 2] =
        XSPI_LUT_SEQ(kXSPI_Command_SDR, kXSPI_1PAD, 0x00, kXSPI_Command_WRITE_SDR, kXSPI_1PAD, 0x01),

    /* Page program */
    [5 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OCTAL] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x12, kXSPI_Command_DDR, kXSPI_8PAD, 0xED),
    [5 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OCTAL + 1] =
        XSPI_LUT_SEQ(kXSPI_Command_RADDR_DDR, kXSPI_8PAD, 0x20, kXSPI_Command_WRITE_DDR, kXSPI_8PAD, 0x4),

    /* Erase Chip */
    [5 * NOR_CMD_LUT_SEQ_IDX_ERASE_CHIP] =
        XSPI_LUT_SEQ(kXSPI_Command_DDR, kXSPI_8PAD, 0x60, kXSPI_Command_DDR, kXSPI_8PAD, 0x9F),
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Temporary fix untill cache64 control is implemented in xspi driver */
static void CACHE64_Invalidate(void)
{
    CACHE64_CTRL0->CCR |= CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK | CACHE64_CTRL_CCR_GO_MASK;
    while ((CACHE64_CTRL0->CCR & CACHE64_CTRL_CCR_GO_MASK) != 0x00U)
    {
    }
    CACHE64_CTRL0->CCR &= ~(CACHE64_CTRL_CCR_INVW0_MASK | CACHE64_CTRL_CCR_INVW1_MASK);
}

static status_t xspi_nor_write_enable(XSPI_Type *base, uint32_t baseAddr, bool useOctal)
{
    xspi_transfer_t flashXfer;
    status_t status;

    /* Write enable */
    flashXfer.deviceAddress   = MFLASH_BASE_ADDRESS + baseAddr;
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.targetGroup     = kXSPI_TargetGroup0;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.lockArbitration = false;
    if (useOctal)
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE_OPI;
    }
    else
    {
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_WRITE_ENABLE;
    }

    status = XSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t xspi_nor_wait_bus_busy(XSPI_Type *base, bool useOctal)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    xspi_transfer_t flashXfer;

    flashXfer.deviceAddress = MFLASH_BASE_ADDRESS;
    flashXfer.cmdType       = kXSPI_Read;
    flashXfer.data          = &readValue;
    flashXfer.targetGroup   = kXSPI_TargetGroup0;
    if (useOctal)
    {
        flashXfer.dataSize = 2;
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READ_STATUS_OPI;
    }
    else
    {
        flashXfer.dataSize = 1;
        flashXfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_READ_STATUS;
    }
    flashXfer.lockArbitration = false;

    do
    {
        status = XSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }

        if ((readValue & (1U << FLASH_BUSY_STATUS_OFFSET)) != 0U)
        {
            isBusy = true;
        }
        else
        {
            isBusy = false;
        }

    } while (isBusy);

    return status;
}

#if defined(FLASH_ENABLE_OCTAL_CMD)
static status_t xspi_nor_enable_octal_mode(XSPI_Type *base)
{
    xspi_transfer_t flashXfer;
    status_t status;

    uint32_t writeValue = FLASH_ENABLE_OCTAL_CMD;

    /* Write enable */
    status = xspi_nor_write_enable(base, 0, false);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable quad mode. */
    flashXfer.deviceAddress   = MFLASH_BASE_ADDRESS;
    flashXfer.cmdType         = kXSPI_Write;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ENTER_OPI;
    flashXfer.targetGroup     = kXSPI_TargetGroup0;
    flashXfer.data            = &writeValue;
    flashXfer.dataSize        = 1;
    flashXfer.lockArbitration = false;

    status = XSPI_TransferBlocking(base, &flashXfer);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = xspi_nor_wait_bus_busy(base, true);

    return status;
}
#endif

static status_t xspi_nor_flash_read(XSPI_Type *base, uint32_t dstAddr, uint32_t *src, uint32_t length, bool useOctal)
{
    status_t status;
    xspi_transfer_t flashXfer;

    /* Prepare page program command */
    flashXfer.deviceAddress   = MFLASH_BASE_ADDRESS + dstAddr;
    flashXfer.cmdType         = kXSPI_Read;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_READ;
    flashXfer.targetGroup     = kXSPI_TargetGroup0;
    flashXfer.data            = src;
    flashXfer.dataSize        = length;
    flashXfer.lockArbitration = false;
    status                    = XSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = xspi_nor_wait_bus_busy(base, useOctal);

    return status;
}

static status_t xspi_nor_flash_erase_sector(XSPI_Type *base, uint32_t address, bool useOctal)
{
    status_t status;
    xspi_transfer_t flashXfer;

    /* Write enable */
    status = xspi_nor_write_enable(base, 0, useOctal);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress   = MFLASH_BASE_ADDRESS + address;
    flashXfer.cmdType         = kXSPI_Command;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_ERASE_SECTOR;
    flashXfer.targetGroup     = kXSPI_TargetGroup0;
    flashXfer.data            = NULL;
    flashXfer.dataSize        = 0UL;
    flashXfer.lockArbitration = false;
    status                    = XSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = xspi_nor_wait_bus_busy(base, useOctal);

    return status;
}

static status_t xspi_nor_flash_page_program(XSPI_Type *base, uint32_t dstAddr, uint32_t *src, bool useOctal)
{
    status_t status;
    xspi_transfer_t flashXfer;

    /* To make sure external flash be in idle status, added wait for busy before program data for
        an external flash without RWW(read while write) attribute.*/
    status = xspi_nor_wait_bus_busy(base, useOctal);

    if (kStatus_Success != status)
    {
        return status;
    }

    /* Write enable. */
    status = xspi_nor_write_enable(base, dstAddr, useOctal);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress   = MFLASH_BASE_ADDRESS + dstAddr;
    flashXfer.cmdType         = kXSPI_Write;
    flashXfer.seqIndex        = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_OCTAL;
    flashXfer.targetGroup     = kXSPI_TargetGroup0;
    flashXfer.data            = src;
    flashXfer.dataSize        = MFLASH_PAGE_SIZE;
    flashXfer.lockArbitration = false;
    status                    = XSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = xspi_nor_wait_bus_busy(base, useOctal);

    return status;
}

static int32_t mflash_drv_init_internal(XSPI_Type *base, bool useOctal)
{
    uint32_t primask;
    xspi_config_t config;
    xspi_ahb_access_config_t xspiAhbAccessConfig;
    xspi_ip_access_config_t xspiIpAccessConfig;
    status_t status = kStatus_Success;

    /* check the code is not running from the flash it's going to operate on */

    if ((uint32_t)mflash_drv_init_internal >= MFLASH_BASE_ADDRESS &&
        (uint32_t)mflash_drv_init_internal < (MFLASH_BASE_ADDRESS + MFLASH_FLASH_SIZE))
    {
        return kStatus_ReadOnly;
    }

    primask = __get_PRIMASK();
    __asm("cpsid i");

    CLOCK_AttachClk(kMAIN_PLL_PFD1_to_XSPI0);
    CLOCK_SetClkDiv(kCLOCK_DivXspi0Clk, 1u); /*400MHz*/

    POWER_DisablePD(kPDRUNCFG_APD_XSPI0);
    POWER_DisablePD(kPDRUNCFG_PPD_XSPI0);
    POWER_ApplyPD();

    config.ptrAhbAccessConfig = &xspiAhbAccessConfig;
    config.ptrIpAccessConfig  = &xspiIpAccessConfig;
    /* Get XSPI default settings and configure the xspi. */
    XSPI_GetDefaultConfig(&config);

    config.byteOrder                                       = kXSPI_64BitLE;
    config.ptrAhbAccessConfig->ahbErrorPayload.highPayload = 0x5A5A5A5AUL;
    config.ptrAhbAccessConfig->ahbErrorPayload.lowPayload  = 0x5A5A5A5AUL;
    config.ptrAhbAccessConfig->ptrAhbWriteConfig         = NULL; /* This demo does not demonstrate AHB write feature.*/
    config.ptrAhbAccessConfig->ARDSeqIndex               = NOR_CMD_LUT_SEQ_IDX_READ;
    config.ptrAhbAccessConfig->enableAHBBufferWriteFlush = true;
    config.ptrAhbAccessConfig->enableAHBPrefetch         = true;

    config.ptrIpAccessConfig->ptrSfpFradConfig               = NULL; /* This demo does not demonstrate SFP feature.*/
    config.ptrIpAccessConfig->ptrSfpMdadConfig               = NULL;
    config.ptrIpAccessConfig->ipAccessTimeoutValue           = 0xFFFFFFFFUL;
    config.ptrIpAccessConfig->sfpArbitrationLockTimeoutValue = 0xFFFFFFUL;
    XSPI_Init(base, &config);

    /* Configure flash settings according to serial flash feature. */
    XSPI_SetDeviceConfig(base, &deviceconfig);

    /* Update LUT*/
    XSPI_UpdateLUT(base, 0, customLUT, CUSTOM_LUT_LENGTH);

    if (useOctal)
    {
        /* Enter quad mode. */
        status = xspi_nor_enable_octal_mode(base);
    }

    if (primask == 0U)
    {
        __asm("cpsie i");
    }

    return status;
}

/* API - initialize 'mflash' */
int32_t mflash_drv_init(void)
{
    /* Necessary to have double wrapper call in non_xip memory */
    return mflash_drv_init_internal(XSPI_INSTANCE, USE_OCTAL_MODE);
}

static int32_t mflash_drv_read_internal(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status_t status;
    status = xspi_nor_flash_read(XSPI_INSTANCE, addr, buffer, len, USE_OCTAL_MODE);

    if (primask == 0U)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* API - Read data */
int32_t mflash_drv_read(uint32_t addr, uint32_t *buffer, uint32_t len)
{
    /* Check alignment */
    if (((uint32_t)buffer % 4) || (len % 4))
    {
        return kStatus_InvalidArgument;
    }

    return mflash_drv_read_internal(addr, buffer, len);
}

/* Internal - erase single sector */
static int32_t mflash_drv_sector_erase_internal(uint32_t sector_addr)
{
    status_t status;
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status = xspi_nor_flash_erase_sector(XSPI_INSTANCE, sector_addr, USE_OCTAL_MODE);

    // invalidate_caches();
    DCACHE_InvalidateByRange(MFLASH_BASE_ADDRESS + sector_addr, MFLASH_SECTOR_SIZE);
    CACHE64_Invalidate();

    if (primask == 0U)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* Calling wrapper for 'mflash_drv_sector_erase_internal'.
 * Erase one sector starting at 'sector_addr' - must be sector aligned.
 */
int32_t mflash_drv_sector_erase(uint32_t sector_addr)
{
    if (0 == mflash_drv_is_sector_aligned(sector_addr))
        return kStatus_InvalidArgument;

    return mflash_drv_sector_erase_internal(sector_addr);
}

/* Internal - write single page */
static int32_t mflash_drv_page_program_internal(uint32_t page_addr, uint32_t *data)
{
    uint32_t primask = __get_PRIMASK();

    __asm("cpsid i");

    status_t status;
    status = xspi_nor_flash_page_program(XSPI_INSTANCE, page_addr, data, USE_OCTAL_MODE);

    DCACHE_InvalidateByRange(MFLASH_BASE_ADDRESS + page_addr, MFLASH_PAGE_SIZE);
    CACHE64_Invalidate();

    if (primask == 0U)
    {
        __asm("cpsie i");
    }

    /* Flush pipeline to allow pending interrupts take place
     * before starting next loop */
    __ISB();

    return status;
}

/* Calling wrapper for 'mflash_drv_page_program_internal'.
 * Write 'data' to 'page_addr' - must be page aligned.
 * NOTE: Don't try to store constant data that are located in XIP !!
 */
int32_t mflash_drv_page_program(uint32_t page_addr, uint32_t *data)
{
    if (0 == mflash_drv_is_page_aligned(page_addr))
        return kStatus_InvalidArgument;

    return mflash_drv_page_program_internal(page_addr, data);
}

/* API - Get pointer to FLASH region */
void *mflash_drv_phys2log(uint32_t addr, uint32_t len)
{
    /* FLASH starts at MFLASH_BASE_ADDRESS */
    return (void *)(addr + MFLASH_BASE_ADDRESS);
}

/* API - Get pointer to FLASH region */
uint32_t mflash_drv_log2phys(void *ptr, uint32_t len)
{
    /* FLASH starts at MFLASH_BASE_ADDRESS */
    return ((uint32_t)ptr - MFLASH_BASE_ADDRESS);
}
