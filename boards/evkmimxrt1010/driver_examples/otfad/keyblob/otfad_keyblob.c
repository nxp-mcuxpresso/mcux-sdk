/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi.h"
#include "app.h"
#include "fsl_debug_console.h"
#include "fsl_otfad.h"
#include "fsl_common.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src, uint32_t length);
extern status_t flexspi_nor_enable_quad_mode(FLEXSPI_Type *base);
extern status_t flexspi_nor_erase_chip(FLEXSPI_Type *base);
extern void flexspi_nor_flash_init(FLEXSPI_Type *base);

void OTFAD_GetEncryptedCounter(uint8_t *counter);
void OTFAD_EncryptData(uint8_t *counter, uint8_t *plainText, uint8_t *cipherText);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t s_plain_text[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                   0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
/*
 * Pre-encrypted text with below key and counter under CTR-AES-128
 *
 * System address: 0x60008000
 *
 * Key: {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f}
 *
 * Counter: {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}
 */
static uint8_t s_encrypted_text[16] = {0x53, 0x67, 0xad, 0x77, 0x02, 0x1d, 0x5d, 0x6b,
                                       0x2c, 0xb7, 0x63, 0xd1, 0x2f, 0x8a, 0x03, 0x7a};
static uint8_t s_decrypted_text[16];
/*-------------------keyblob0------------------------
 * Raw keyblob0(both address need to be 1KB aligned):
 * start address = "0x60014000",
 * end address   = "0x60014fff",
 * key           = "000102030405060708090A0B0C0D0E0F",
 * counter       = "0123456789ABCDEF"
 *
 * KEK for keyblob encryption:
 *     "00000000000000000000000000000000"
 * KEK for OTFAD decryption(default fuse):
 *     "00000000000000000000000000000000"
 *-------------------keyblob1------------------------
 * Raw keyblob1(both address need to be 1KB aligned):
 * start address = "0x60015000",
 * end address   = "0x60015fff",
 * key           = "000102030405060708090A0B0C0D0E0F",
 * counter       = "0123456789ABCDEF"
 *
 * KEK for keyblob encryption:
 *     "00000000000000000000000000000000"
 * KEK for OTFAD decryption(default fuse):
 *     "00000000000000000000000000000000"
 *-------------------keyblob2------------------------
 * Raw keyblob2(both address need to be 1KB aligned):
 * start address = "0x60016000",
 * end address   = "0x60016fff",
 * key           = "000102030405060708090A0B0C0D0E0F",
 * counter       = "0123456789ABCDEF"
 *
 * KEK for keyblob encryption:
 *     "00000000000000000000000000000000"
 * KEK for OTFAD decryption(default fuse):
 *     "00000000000000000000000000000000"
 *-------------------keyblob03------------------------
 * Raw keyblob3(both address need to be 1KB aligned):
 * start address = "0x60017000",
 * end address   = "0x60017fff",
 * key           = "000102030405060708090A0B0C0D0E0F",
 * counter       = "0123456789ABCDEF"
 *
 * KEK for keyblob encryption:
 *     "00000000000000000000000000000000"
 * KEK for OTFAD decryption(default fuse):
 *     "00000000000000000000000000000000"
 */
uint8_t keyBlob[4][64] = {
    {0xd1, 0xc8, 0xf3, 0x5b, 0x0d, 0x74, 0x81, 0xe3, 0x04, 0x7a, 0x13, 0x9e, 0x9b, 0x43, 0x2b, 0xdd,
     0xd9, 0x43, 0xb1, 0x0c, 0x48, 0x06, 0xf0, 0x2a, 0x3a, 0x09, 0x80, 0xd0, 0x09, 0xd6, 0x74, 0xfe,
     0x53, 0x7b, 0x05, 0x47, 0x24, 0xeb, 0x02, 0x5f, 0x37, 0xcc, 0x06, 0xd0, 0xd8, 0xa2, 0xd9, 0x5f,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x4d, 0xc7, 0x44, 0x61, 0x3e, 0xa6, 0xfd, 0x61, 0xc5, 0x86, 0xee, 0x56, 0xd8, 0x96, 0xcf,
     0x54, 0x6b, 0xe0, 0x25, 0xca, 0x6b, 0xe8, 0x0f, 0x5f, 0xbe, 0xda, 0xea, 0xc4, 0x48, 0xbf, 0xd6,
     0xd7, 0x0f, 0x10, 0x14, 0x47, 0x8b, 0xfb, 0x85, 0xc3, 0xae, 0xc7, 0xdd, 0x93, 0x3d, 0xaa, 0x6c,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x90, 0xa4, 0xd7, 0xc8, 0xf4, 0x39, 0x3b, 0x62, 0x8e, 0x23, 0x07, 0x7b, 0x52, 0x33, 0xc5, 0x60,
     0xe1, 0xb3, 0xbe, 0xf7, 0x6c, 0xc6, 0x44, 0x98, 0xcc, 0xc2, 0x7a, 0x2c, 0xf5, 0x7c, 0xe4, 0x7a,
     0xcb, 0x84, 0xbf, 0x91, 0x2e, 0xea, 0xf2, 0xb4, 0x7f, 0xc9, 0x84, 0xe5, 0xa0, 0x92, 0xac, 0xd5,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x01, 0x25, 0x83, 0xf3, 0xca, 0x55, 0xf4, 0x7e, 0x98, 0x09, 0x75, 0x54, 0x1f, 0xba, 0x9b, 0xef,
     0xe4, 0x1e, 0x3c, 0xd2, 0x26, 0xdd, 0x6d, 0x09, 0xc9, 0x26, 0x75, 0x5e, 0xdb, 0x25, 0xb7, 0x61,
     0x05, 0xda, 0xb3, 0x5b, 0x5b, 0x37, 0x22, 0x8a, 0x8c, 0x41, 0xdc, 0x54, 0x60, 0x83, 0x2d, 0x03,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

/*******************************************************************************
 * Code
 ******************************************************************************/
flexspi_device_config_t deviceconfig = {
    .flexspiRootClk       = 133000000,
    .flashSize            = FLASH_SIZE,
    .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval           = 2,
    .CSHoldTime           = 3,
    .CSSetupTime          = 3,
    .dataValidTime        = 0,
    .columnspace          = 0,
    .enableWordAddress    = 0,
    .AWRSeqIndex          = 0,
    .AWRSeqNumber         = 0,
    .ARDSeqIndex          = NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD,
    .ARDSeqNumber         = 1,
    .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 0,
};

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
    /* Normal read mode -SDR */
    /* Normal read mode -SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x03, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_NORMAL + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Fast read mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x0B, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_1PAD, 0x08, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Fast read quad mode - SDR */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xEB, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_4PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ_FAST_QUAD + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_4PAD, 0x06, kFLEXSPI_Command_READ_SDR, kFLEXSPI_4PAD, 0x04),

    /* Read extend parameters */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x81, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Write Enable */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITEENABLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x06, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Erase Sector  */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASESECTOR] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x20, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),

    /* Page Program - single mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x02, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_SINGLE + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Page Program - quad mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x32, kFLEXSPI_Command_RADDR_SDR, kFLEXSPI_1PAD, 0x18),
    [4 * NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD + 1] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_4PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),

    /* Read ID */
    [4 * NOR_CMD_LUT_SEQ_IDX_READID] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x9F, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Enable Quad mode */
    [4 * NOR_CMD_LUT_SEQ_IDX_WRITESTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x31, kFLEXSPI_Command_WRITE_SDR, kFLEXSPI_1PAD, 0x04),

    /* Read status register */
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUSREG] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0x05, kFLEXSPI_Command_READ_SDR, kFLEXSPI_1PAD, 0x04),

    /* Erase whole chip */
    [4 * NOR_CMD_LUT_SEQ_IDX_ERASECHIP] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_1PAD, 0xC7, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0),
};

#if APP_USING_CACHE
#include "fsl_cache.h"
#endif

int main(void)
{
    status_t status = kStatus_Success;
    otfad_config_t config;
    uint32_t sysAddress = EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE;
    uint8_t contextHit;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Initialize FlexSPI */
    flexspi_nor_flash_init(EXAMPLE_FLEXSPI);

    PRINTF("\r\nOTFAD keyblob example started!\r\n");

#if !(defined(XIP_EXTERNAL_FLASH))
    /* Erase whole chip . */
    PRINTF("Erasing whole chip over FlexSPI...\r\n");

    status = flexspi_nor_erase_chip(EXAMPLE_FLEXSPI);
    if (status != kStatus_Success)
    {
        return status;
    }
    else
    {
        PRINTF("Erase whole chip finished !\r\n");
    }
#endif

    /* Enter quad mode. */
    status = flexspi_nor_enable_quad_mode(EXAMPLE_FLEXSPI);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Erase sectors. */
    PRINTF("Erasing Serial NOR over FlexSPI...\r\n");
    status = flexspi_nor_flash_erase_sector(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE);
    if (status != kStatus_Success)
    {
        PRINTF("Erase sector failure !\r\n");
        return -1;
    }
    else
    {
        PRINTF("Erase sector finished !\r\n");
    }

    /*
     * The four wrapped key blobs are programmed into the external flash memory at the following addresses:
     * Context 0 key blob @ SPI_BASE_ADDRESS + 0x00
     * Context 1 key blob @ SPI_BASE_ADDRESS + 0x40
     * Context 2 key blob @ SPI_BASE_ADDRESS + 0x80
     * Context 3 key blob @ SPI_BASE_ADDRESS + 0xC0
     */
    status = flexspi_nor_flash_program(EXAMPLE_FLEXSPI, 0U, (void *)keyBlob, sizeof(keyBlob));
    if (status != kStatus_Success)
    {
        PRINTF("KeyBlob program failure !\r\n");
        return -1;
    }

    /*
     * config.misc.interruptRequest    = false;
     * config.misc.forceError          = false;
     * config.misc.forceSVM            = false;
     * config.misc.forceLDM            = false;
     * config.misc.keyBlobScramble     = false;
     * config.misc.keyBlobProcess      = false;
     * config.misc.restrictedRegAccess = false;
     * config.startKeyBlobProcessing = false;
     * config.enableOTFAD = false;
     */
    OTFAD_GetDefaultConfig(&config);

    /* Enable key blob */
    config.keyBlobProcess = 0x01U;
    /* Start key blob processing */
    config.startKeyBlobProcessing = 0x01U;
    /* Global OTFAD enbale */
    config.enableOTFAD = true;
    /* Flexspi base address */
    config.flexspiBaseAddr = EXAMPLE_FLEXSPI;

    /* Initialize OTFAD and it will do keyblob process. */
    OTFAD_Init(EXAMPLE_OTFAD, &config);

    status = OTFAD_HitDetermination(EXAMPLE_OTFAD, sysAddress, &contextHit);
    if (status != kStatus_Success)
    {
        PRINTF("Hit context failed \r\n");
    }
    else
    {
        PRINTF("Hitted context: 0x%x\r\n", contextHit);
    }

    /* Write ciphertext into external memory */
    status = flexspi_nor_flash_program(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE, (void *)s_encrypted_text,
                                       sizeof(s_encrypted_text));

    if (status != kStatus_Success)
    {
        PRINTF("Ciphertext program failure !\r\n");
        return -1;
    }

#if APP_USING_CACHE
    /*
     * Invalidate the cache, so new read will read from memory directly.
     */
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    memcpy(s_decrypted_text, (void *)(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE),
           sizeof(s_decrypted_text));

    if (memcmp(s_decrypted_text, s_plain_text, sizeof(s_decrypted_text)) != 0)
    {
        PRINTF("Decrypted data -  Decryption error !\r\n ");
        return -1;
    }
    else
    {
        PRINTF("Decrypted data - successfully. \r\n");
    }

    OTFAD_Deinit(EXAMPLE_OTFAD);

    while (1)
    {
    }
}

void OTFAD_GetEncryptedCounter(uint8_t *counter)
{
    assert(counter != NULL);

    status_t status     = kStatus_Success;
    uint32_t sysAddress = EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE;
    uint8_t contextHit;

    uint8_t i;
    uint8_t plainText[16]     = {0x00U};
    uint8_t *encryptedCounter = counter;

    status = OTFAD_HitDetermination(EXAMPLE_OTFAD, sysAddress, &contextHit);

    if (status == kStatus_Success)
    {
        /* Erase sector */
        status = flexspi_nor_flash_erase_sector(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE);
    }

#if APP_USING_CACHE
    /*
     * Invalidate the cache, so new read will read from memory directly.
     */
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    if (kStatus_Success == status)
    {
        /* Read 16 bytes plain text */
        memcpy(plainText, (void *)(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE), sizeof(plainText));
    }

    for (i = 0U; i < 16U; i++)
    {
        /* Method:
         * cipherText = encryptedCounter ^ plainText = 0xFF
         * encryptedCounter = cipherText ^ 0xFF = plainText ^ 0xFF
         */
        encryptedCounter[i] = plainText[i] ^ 0xFF;
    }
}

void OTFAD_EncryptData(uint8_t *counter, uint8_t *plainText, uint8_t *cipherText)
{
    assert(counter != NULL);
    assert(plainText != NULL);
    assert(cipherText != NULL);

    uint8_t i;

    for (i = 0U; i < 16U; i++)
    {
        cipherText[i] = counter[i] ^ plainText[i];
    }
}
