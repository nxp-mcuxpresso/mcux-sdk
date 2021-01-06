/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "fsl_ltc_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DMAMUX0                     DMA_CH_MUX0
#define LTC_REQUEST_INPUT_FIFO      kDmaRequestMux0LTCRx
#define LTC_REQUEST_OUTPUT_FIFO     kDmaRequestMux0LTCTx
#define DMA_CHANNEL_LTC_INPUT_FIFO  0
#define DMA_CHANNEL_LTC_OUTPUT_FIFO 1
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

/* Variable used by LTC EDMA */
ltc_edma_handle_t g_ltcEdmaHandle;
edma_handle_t g_ltcInputFifoEdmaHandle;
edma_handle_t g_ltcOutputFifoEdmaHandle;
volatile bool g_ltcEdmaDone       = false;
volatile status_t g_ltcEdmaStatus = kStatus_Success;

static void ltc_EdmaUserCallback(LTC_Type *base, ltc_edma_handle_t *handle, status_t status, void *userData);
static void ltc_EdmaWait(void);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void ltc_print_msg(const uint8_t *data, uint32_t length);
static void ltc_example_task(void);
static void ltc_aes_cbc_exam(void);

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
    PRINTF("------------------------- AES-CBC method --------------------------------------\r\n");
    /*   ENCRYPTION   */
    PRINTF("AES CBC Encryption of %u bytes.\r\n", g_length);

    /* Call AES_cbc encryption */
    LTC_AES_EncryptCbcEDMA(LTC0, &g_ltcEdmaHandle, aes_test_full, cipher, g_length, ive, key128, AES128_KEY_SIZE);
    ltc_EdmaWait();
    if (g_ltcEdmaStatus != kStatus_Success)
    {
        PRINTF("AES CBC encryption failed !\r\n");
        return;
    }

    /* Result message */
    PRINTF("AES CBC encryption finished.\r\n\r\n");

    /*   DECRYPTION   */
    PRINTF("AES CBC Decryption of %u bytes.\r\n", g_length);

    /* Call AES_cbc decryption */
    LTC_AES_DecryptCbcEDMA(LTC0, &g_ltcEdmaHandle, cipher, output, g_length, ive, key128, AES128_KEY_SIZE,
                           kLTC_EncryptKey);
    ltc_EdmaWait();
    if (g_ltcEdmaStatus != kStatus_Success)
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

/* @brief LTC EDMA user callback */
static void ltc_EdmaUserCallback(LTC_Type *base, ltc_edma_handle_t *handle, status_t status, void *userData)
{
    /* Not used.*/
    userData = userData;
    base     = base;
    handle   = handle;

    g_ltcEdmaDone   = true;
    g_ltcEdmaStatus = status;
}

/* @brief Wait for LTC eDMA complete. */
static void ltc_EdmaWait(void)
{
    while (g_ltcEdmaDone == false)
    {
    }
    /* Reset flag.*/
    g_ltcEdmaDone = false;
}

/*!
 * @brief Function ltc_example_task demonstrates use of LTC driver
 * encryption/decryption functions on short sample text.
 */
static void ltc_example_task(void)
{
    edma_config_t config;

/* Set default ltc device instance num */
#if !FSL_FEATURE_SOC_LTC_COUNT
    PRINTF("Unsupported platform selected !\r\n");
    return;
#endif

    /* Initialize LTC driver.
     * This enables clocking and resets the module to a known state. */
    LTC_Init(LTC0);

    /* Init DMAMUX */
    DMAMUX_Init(DMAMUX0);
    /* Set channel for LTC FIFOs */
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL_LTC_INPUT_FIFO, LTC_REQUEST_INPUT_FIFO);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL_LTC_OUTPUT_FIFO, LTC_REQUEST_OUTPUT_FIFO);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL_LTC_INPUT_FIFO);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL_LTC_OUTPUT_FIFO);

    /* Init the EDMA module */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(DMA0, &config);
    EDMA_CreateHandle(&g_ltcInputFifoEdmaHandle, DMA0, DMA_CHANNEL_LTC_INPUT_FIFO);
    EDMA_CreateHandle(&g_ltcOutputFifoEdmaHandle, DMA0, DMA_CHANNEL_LTC_OUTPUT_FIFO);

    /* Create LTC EDMA handle. */
    LTC_CreateHandleEDMA(LTC0, &g_ltcEdmaHandle, ltc_EdmaUserCallback, NULL, &g_ltcInputFifoEdmaHandle,
                         &g_ltcOutputFifoEdmaHandle);

    /* Print welcome string */
    PRINTF("................ LTC (AES EDMA)  DRIVER  EXAMPLE ............................. \r\n\r\n");

    memset(&output[0], 0, OUTPUT_ARRAY_LEN);
    memset(&cipher[0], 0, OUTPUT_ARRAY_LEN);
    g_length = sizeof(aes_test_full) - 1u;

    PRINTF("Testing input string: \r\n");
    ltc_print_msg(&aes_test_full[0], g_length);
    /* Format console output */
    PRINTF("\r\n");

    /******* AES-CBC method *********/
    ltc_aes_cbc_exam();

    /* Goodbye message */
    PRINTF(".............. THE  END  OF  THE  LTC (AES EDMA)  DRIVER  EXAMPLE .............\r\n");
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
