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
#include "fsl_cache.h"
#include "fsl_otfad.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_common.h"
#include "fsl_power.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t s_plain_text[16];
static uint8_t s_cipher_text[16];
static uint8_t s_decrypted_text[16];

extern status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
extern status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src);
extern status_t flexspi_nor_enable_octal_mode(FLEXSPI_Type *base);
extern void flexspi_nor_flash_init(FLEXSPI_Type *base);

void OTFAD_GetEncryptedCounter(uint8_t *counter);
void OTFAD_EncryptData(uint8_t *counter, uint8_t *plainText, uint8_t *cipherText);
/*******************************************************************************
 * Code
 ******************************************************************************/
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

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {

    /*  OPI DDR read */
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 0] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xEE, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x11),
    [4 * NOR_CMD_LUT_SEQ_IDX_READ + 1] = FLEXSPI_LUT_SEQ(
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x29),
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
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x16),
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
        kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_DUMMY_DDR, kFLEXSPI_8PAD, 0x20),
    [4 * NOR_CMD_LUT_SEQ_IDX_READSTATUS_OPI + 2] =
        FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),
};


int main(void)
{
    uint32_t i      = 0;
    status_t status = kStatus_Success;
    otfad_config_t config;
    uint8_t encryptedCounter[16];
    uint32_t sysAddress = EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE;
    otfad_encryption_config_t encryptionConfig;
    uint8_t contextHit;

    BOARD_InitPins();
    BOARD_InitFlexSPI0BPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Define the init structure for the reset pin*/
    gpio_pin_config_t reset_config = {
        kGPIO_DigitalOutput,
        1,
    };

    /* Init output reset pin. */
    GPIO_PortInit(GPIO, 2);
    GPIO_PinInit(GPIO, 2, 12, &reset_config);

#if !defined(FSL_SDK_DRIVER_QUICK_ACCESS_ENABLE)
    POWER_DisablePD(kPDRUNCFG_APD_FLEXSPI_SRAM);
    POWER_DisablePD(kPDRUNCFG_PPD_FLEXSPI_SRAM);
    POWER_ApplyPD();
#endif
    /* Attach AUX0_PLL clock to flexspi withe divider 4*/
    BOARD_SetFlexspiClock(2, 4);

    /*
     * config.misc.interruptRequest    = 0x00U;
     * config.misc.forceError          = 0x00U;
     * config.misc.forceSVM            = 0x00U;
     * config.misc.forceLDM            = 0x00U;
     * config.misc.keyBlobScramble     = 0x00U;
     * config.misc.keyBlobProcess      = 0x00U;
     * config.misc.restrictedRegAccess = 0x00U;
     * config.startKeyBlobProcessing = 0x00U;
     * config.enableOTFAD = false;
     */
    OTFAD_GetDefaultConfig(&config);

    /* Global OTFAD enbale */
    config.enableOTFAD = true;
    /* Flexspi base address */
    config.flexspiBaseAddr = EXAMPLE_FLEXSPI;

    /* Initialize FlexSPI */
    flexspi_nor_flash_init(EXAMPLE_FLEXSPI);

    PRINTF("\r\nOTFAD example started!\r\n");

    /* Initialize OTFAD. */
    OTFAD_Init(EXAMPLE_OTFAD, &config);

    encryptionConfig.contextIndex  = 0U;
    encryptionConfig.valid         = true;
    encryptionConfig.AESdecryption = true;
    encryptionConfig.readOnly      = 0U;
    encryptionConfig.startAddr     = sysAddress;
    encryptionConfig.endAddr       = sysAddress + 0xfffU;

    /* Key: 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F */
    encryptionConfig.key[0] = 0x03020100;
    encryptionConfig.key[1] = 0x07060504;
    encryptionConfig.key[2] = 0x0B0A0908;
    encryptionConfig.key[3] = 0x0F0E0D0C;
    /* Counter: 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF */
    encryptionConfig.counter[0] = 0x67452301;
    encryptionConfig.counter[1] = 0xEFCDAB89;

    status = OTFAD_SetEncryptionConfig(EXAMPLE_OTFAD, &encryptionConfig);

    if (status != kStatus_Success)
    {
        PRINTF("AES encryption configuration failure\r\n");
        return -1;
    }

    status = OTFAD_HitDetermination(EXAMPLE_OTFAD, sysAddress, &contextHit);
    if (status != kStatus_Success)
    {
        return status;
    }
    else
    {
        PRINTF("Hit context: 0x%x\r\n", contextHit);
    }

    /* Enter octal mode. */
    status = flexspi_nor_enable_octal_mode(EXAMPLE_FLEXSPI);
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

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, FLASH_PAGE_SIZE);
#endif

    /* Get encrypted counter for encryption and decryption */
    OTFAD_GetEncryptedCounter(encryptedCounter);

    for (i = 0U; i < 16U; i++)
    {
        s_plain_text[i] = i;
    }

    /* Encrypt data with encrypted counter */
    OTFAD_EncryptData(encryptedCounter, s_plain_text, s_cipher_text);

    /* Write ciphertext into external memory */
    status = flexspi_nor_flash_page_program(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE, (void *)s_cipher_text);
    if (status != kStatus_Success)
    {
        PRINTF("Ciphertext program failure !\r\n");
        return -1;
    }

#if defined(CACHE_MAINTAIN) && CACHE_MAINTAIN
    DCACHE_InvalidateByRange(EXAMPLE_FLEXSPI_AMBA_BASE + EXAMPLE_SECTOR * SECTOR_SIZE, sizeof(s_cipher_text));
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
    uint8_t plainText[16];
    uint8_t *encryptedCounter = counter;

    status = OTFAD_HitDetermination(EXAMPLE_OTFAD, sysAddress, &contextHit);

    if (status == kStatus_Success)
    {
        /* Erase sector */
        status = flexspi_nor_flash_erase_sector(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE);
    }

    flexspi_nor_flash_erase_sector(EXAMPLE_FLEXSPI, EXAMPLE_SECTOR * SECTOR_SIZE);

    for (i = 0U; i < 16U; i++)
    {
        plainText[i] = 0x00U;
    }

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
