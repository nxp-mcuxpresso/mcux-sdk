/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
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

#include "fsl_ltc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define OUTPUT_ARRAY_LEN 512
#define AES_BLOCK_LENGTH 16
#define AES128           128
#define AES128_KEY_SIZE  16
#define CCM_PLAIN_SIZE   32
#define CCM_IV_SIZE      12
#define CCM_AAD_SIZE     20
#define CCM_KEY_SIZE     16
#define CCM_TAG_SIZE     8
#define CMAC_HASH_SIZE   16
#define CMAC_KEY_SIZE    16

/* LTC peripheral base address */
LTC_Type *base = LTC0;
static unsigned int g_length;

/*8-byte multiple*/
static const uint8_t aes_test_full[] =
    "Once upon a midnight dreary, while I pondered weak and weary,"
    "Over many a quaint and curious volume of forgotten lore,"
    "While I nodded, nearly napping, suddenly there came a tapping,"
    "As of some one gently rapping, rapping at my chamber door"
    "Its some visitor, I muttered, tapping at my chamber door"
    "Only this, and nothing more.";

/*16 bytes key: "ultrapassword123"*/
static const uint8_t key128[AES128_KEY_SIZE] = {0x75, 0x6c, 0x74, 0x72, 0x61, 0x70, 0x61, 0x73,
                                                0x73, 0x77, 0x6f, 0x72, 0x64, 0x31, 0x32, 0x33};
/*initialization vector: 16 bytes: "mysecretpassword"*/
static uint8_t ive[AES_BLOCK_LENGTH] = {0x6d, 0x79, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74,
                                        0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64};

static uint8_t cipher[OUTPUT_ARRAY_LEN];
static uint8_t output[OUTPUT_ARRAY_LEN];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ltc_print_msg(const uint8_t *data, uint32_t length);
static void ltc_example_task(void);
static void ltc_aes_cbc_exam(void);
static void ltc_aes_ccm_exam(void);
static void ltc_aes_cmac_exam(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Function ltc_print_msg prints data into console.
 */
static void ltc_print_msg(const uint8_t *data, uint32_t length)
{
    uint32_t i;

    PRINTF("          ");
    for (i = 0; i < length; i++)
    {
        PUTCHAR(data[i]);
        if (data[i] == ',')
        {
            PRINTF("\r\n          ");
        }
    }
    PRINTF("\r\n");
}

/*!
 * @brief Function ltc_aes_cbc_exam demonstrates
   use of AES CBC method and prints decrypted text.
 */
static void ltc_aes_cbc_exam(void)
{
    status_t status;

    PRINTF("----------------------------------- AES-CBC method --------------------------------------\r\n");
    /*   ENCRYPTION   */
    PRINTF("AES CBC Encryption of %u bytes.\r\n", g_length);

    /* Call AES_cbc encryption */
    status = LTC_AES_EncryptCbc(base, aes_test_full, cipher, g_length, ive, key128, AES128_KEY_SIZE);
    if (status != kStatus_Success)
    {
        PRINTF("AES CBC encryption failed !\r\n");
        return;
    }

    /* Result message */
    PRINTF("AES CBC encryption finished.\r\n\r\n");

    /*   DECRYPTION   */
    PRINTF("AES CBC Decryption of %u bytes.\r\n", g_length);

    /* Call AES_cbc decryption */
    status = LTC_AES_DecryptCbc(base, cipher, output, g_length, ive, key128, AES128_KEY_SIZE, kLTC_EncryptKey);
    if (status != kStatus_Success)
    {
        PRINTF("AES CBC decryption failed !\r\n");
        return;
    }

    /* Result message */
    PRINTF("AES CBC decryption finished.\r\n");
    /* Print decrypted string */
    PRINTF("Decrypted string :\r\n");
    ltc_print_msg(output, g_length);

    /* Just format console */
    PRINTF("\r\n");
}

/*!
 * @brief Function ltc_aes_ccm_exam demonstrates
   use of AES CCM method and prints decrypted text.
 */
static void ltc_aes_ccm_exam(void)
{
    unsigned int j, i;
    uint8_t nonce[]           = {0x00, 0x00, 0x00, 0x03, 0x02, 0x01, 0x00, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
    uint8_t key[CCM_KEY_SIZE] = {0};
    uint8_t aad[CCM_AAD_SIZE];
    uint8_t tag[CCM_TAG_SIZE] = {0};

    PRINTF("----------------------------------- AES-CCM method --------------------------------------\r\n");
    /* Generate sample key and aad */
    j = 0;
    for (i = 0x40; i <= 0x4f; i++)
    {
        key[j++] = (uint8_t)i;
    }

    for (i = 0x0; i <= 0x13; i++)
    {
        aad[i] = (uint8_t)i;
    }

    /* clear working buffers */
    memset(&cipher[0], 0, g_length);
    memset(&output[0], 0, g_length);

    /*   ENCRYPTION   */
    PRINTF("AES CCM Encryption of  %u bytes.\r\n", g_length);
    PRINTF("    using iv length  : %u bytes \r\n", CCM_IV_SIZE);
    PRINTF("    using aad length : %u bytes \r\n", CCM_AAD_SIZE);
    PRINTF("    using key length : %u bytes \r\n", CCM_KEY_SIZE);
    PRINTF("    using tag length : %u bytes \r\n", CCM_TAG_SIZE);

    /* Call AES CCM encryption */
    if (kStatus_Success != LTC_AES_EncryptTagCcm(base, &aes_test_full[0], &cipher[0], g_length, &nonce[0], CCM_IV_SIZE,
                                                 &aad[0], CCM_AAD_SIZE, &key[0], CCM_KEY_SIZE, &tag[0], CCM_TAG_SIZE))
    {
        PRINTF("AES CCM encryption failed !!!\r\n");
        return;
    }

    /* Result message */
    PRINTF("AES CCM encryption finished.\r\n\r\n");

    /*   DECRYPTION   */
    PRINTF("AES CCM decryption of %u bytes.\r\n", g_length);

    /* Call AES CCM decryption */
    if (kStatus_Success != LTC_AES_DecryptTagCcm(base, &cipher[0], &output[0], g_length, &nonce[0], CCM_IV_SIZE,
                                                 &aad[0], CCM_AAD_SIZE, &key[0], CCM_KEY_SIZE, &tag[0], CCM_TAG_SIZE))
    {
        PRINTF("AES CCM decryption failed !!!\r\n");
        return;
    }

    /* Result message */
    PRINTF("AES CCM decryption finished.\r\n");
    PRINTF("Decrypted string: \r\n");
    ltc_print_msg(output, g_length);
    PRINTF("\r\n");
}

/*!
 * @brief Function ltc_aes_cmac_exam demonstrates
   use of AES CMAC functionality. Initializes CMAC driver and
   put sample text to compute hash.
 */
static void ltc_aes_cmac_exam(void)
{
    uint32_t i, j, hash_size;
    uint8_t key[CMAC_KEY_SIZE]    = {0};
    uint8_t hash[CMAC_HASH_SIZE]  = {0};
    uint8_t hash2[CMAC_HASH_SIZE] = {0};
    ltc_hash_ctx_t ctx; /* CMAC context */

    PRINTF("----------------------------------- AES-XCBC-MAC --------------------------------------\r\n");
    PRINTF("AES XCBC-MAC Computing hash of %u bytes \r\n", g_length);

    /* Create sample key */
    j = 0;
    for (i = 0x40; i <= 0x4f; i++)
    {
        key[j++] = (uint8_t)i;
    }

    /* Initialize the CMAC with a given key, and selects a block cipher to use. */
    if (kStatus_Success != LTC_HASH_Init(base, &ctx, kLTC_XcbcMac, &key[0], CMAC_KEY_SIZE))
    {
        PRINTF("Initialization of LTC HASH driver error\r\n");
        return;
    }
    /* Call CMAC hash update to add data to create hash.
       It can be called once with whole array size, but this shows that
       function update can be called asynchronously (e.g during receiving some data).
    */
    for (i = 0; i < g_length; i++)
    { /* cmac context, data, data length */
        if (kStatus_Success != LTC_HASH_Update(&ctx, &aes_test_full[i], 1))
        {
            PRINTF("Update input hash data error\r\n");
            return;
        }
    }
    /* Save hash size into variable, because in case that hash_size was set bigger
       as 16 bytes, driver will re-set to 16 bytes length */
    hash_size = CMAC_HASH_SIZE;

    /* Call LTC_HASH_Finish function to get counted hash.
       standard(maximum) hash size is 16 bytes */
    if (kStatus_Success != LTC_HASH_Finish(&ctx, &hash[0], &hash_size))
    {
        PRINTF("Get final hash error\r\n");
        return;
    }

    /* compute the same message by one call. we should get the same result. */
    hash_size = CMAC_HASH_SIZE;
    LTC_HASH(base, kLTC_XcbcMac, aes_test_full, g_length, key, CMAC_KEY_SIZE, hash2, &hash_size);
    if (memcmp(hash, hash2, hash_size))
    {
        PRINTF("Error: hash compare\r\n");
    }

    PRINTF("Computed hash:\r\n");
    /* Print hash */
    for (i = 0; i < hash_size; i++)
    {
        PRINTF("%.2x ", hash[i]);
    }
    /* Format console output */
    PRINTF("\r\n\r\n");
}

/*!
 * @brief Function ltc_example_task demonstrates use of LTC driver
 * encryption/decryption functions on short sample text.
 */
static void ltc_example_task(void)
{
/* Set default ltc device instance num */
#if !FSL_FEATURE_SOC_LTC_COUNT
    PRINTF("Unsupported platform selected !\r\n");
    return;
#endif

    /* Initialize LTC driver.
     * This enables clocking and resets the module to a known state. */
    LTC_Init(base);

    /* Print welcome string */
    PRINTF("............................. LTC (AES)  DRIVER  EXAMPLE ............................. \r\n\r\n");

    memset(&output[0], 0, OUTPUT_ARRAY_LEN);
    memset(&cipher[0], 0, OUTPUT_ARRAY_LEN);
    g_length = sizeof(aes_test_full) - 1u;

    PRINTF("Testing input string: \r\n");
    ltc_print_msg(&aes_test_full[0], g_length);
    /* Format console output */
    PRINTF("\r\n");

    /******* FIRST PART USING AES-CBC method *********/
    ltc_aes_cbc_exam();

    /******* SECOND PART USING AES-CCM method ********/
    ltc_aes_ccm_exam();

    /******* THIRD PART USES HASH FUNCTIONALITY ******/
    ltc_aes_cmac_exam();

    /* Goodbye message */
    PRINTF(".............. THE  END  OF  THE  LTC (AES)  DRIVER  EXAMPLE ................................\r\n");
}

int main(void)
{
    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Call example task */
    ltc_example_task();

    while (1)
    {
    }
}
