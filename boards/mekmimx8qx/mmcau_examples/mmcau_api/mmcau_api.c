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
#include <stdlib.h>
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_mmcau.h"

#include "fsl_lpuart.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CORE_CLK_FREQ DEFAULT_SYSTEM_CLOCK
/* Number of cycles for througput measurement. One data buffer of certain size if processed this times. */
#define CYCLES_FOR_THROUGHPUT 128

/*AES specific*/
#define AES128           128
#define AES128_KEY_SIZE  16
#define AES_BLOCK_LENGTH 16

/*DES specific*/
#define DES3_BLOCK_LENGTH 8
#define DES3_KEY_LENGTH   24

/*length of AES & DES encrypted data array*/
#define OUTPUT_ARRAY_LEN 512
/*length of result hash in bytes*/
#define SHA1_RESULT_LENGTH   20
#define SHA256_RESULT_LENGTH 32
#define MD5_RESULT_LENGTH    16

/*size of one crypto block*/
#define CRYPTO_BLOCK_LENGTH 64
/*size of padded hash input string*/
#define TEST_LENGTH 64

/*MMCAU result codes*/
#define MMCAU_OK    0
#define MMCAU_ERROR -1

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*16 bytes key: "ultrapassword123"*/
const uint8_t g_aesKey128[AES128_KEY_SIZE] = {0x75, 0x6c, 0x74, 0x72, 0x61, 0x70, 0x61, 0x73,
                                              0x73, 0x77, 0x6f, 0x72, 0x64, 0x31, 0x32, 0x33};

/*initialization vector: 16 bytes: "mysecretpassword"*/
const uint8_t g_aesIV[AES_BLOCK_LENGTH] = {0x6d, 0x79, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74,
                                           0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64};

/*24 bytes key: "verynicepassword12345678"
  Note: parity is fixed inside DES crypto function*/
static uint8_t g_des3Key[DES3_KEY_LENGTH] = {0x76, 0x65, 0x72, 0x79, 0x6e, 0x69, 0x63, 0x65, 0x70, 0x61, 0x73, 0x73,
                                             0x77, 0x6f, 0x72, 0x64, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

/*initialization vector: 8 bytes: "mysecret"*/
static const uint8_t g_des3IV[DES3_BLOCK_LENGTH] = {0x6d, 0x79, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74};

static const uint8_t g_parityBits[128] = {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
                                          0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1,
                                          0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1,
                                          1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                                          0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

/*8-byte multiple*/
static const uint8_t g_testFull[] =
    "Once upon a midnight dreary, while I pondered weak and weary,"
    "Over many a quaint and curious volume of forgotten lore,"
    "While I nodded, nearly napping, suddenly there came a tapping,"
    "As of some one gently rapping, rapping at my chamber door"
    "Its some visitor, I muttered, tapping at my chamber door"
    "Only this, and nothing more.";

/* SHA test string: "The quick brown fox jumps over the lazy dog"
 * with padding bits included
 */
static uint8_t g_testSha[TEST_LENGTH] = {0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72, 0x6f,
                                         0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20,
                                         0x6f, 0x76, 0x65, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79,
                                         0x20, 0x64, 0x6f, 0x67, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x58};

/* MD5 test string: "The quick brown fox jumps over the lazy dog"
 * with padding bits included
 */
static uint8_t g_testMd5[TEST_LENGTH] = {0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72, 0x6f,
                                         0x77, 0x6e, 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20,
                                         0x6f, 0x76, 0x65, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79,
                                         0x20, 0x64, 0x6f, 0x67, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x00, 0x00, 0x00, 0x00, 0x58, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static uint8_t g_output[OUTPUT_ARRAY_LEN];
static uint8_t g_result[OUTPUT_ARRAY_LEN];

static volatile uint32_t g_msCount = 0;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void mmcau_print_msg(const uint8_t *data, uint32_t length);
static void mmcau_example_task(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Milliseconds counter since last POR/reset.
 */
void SysTick_Handler(void)
{
    g_msCount++;
}

/*!
 * @brief SysTick period configuration and interrupt enable.
 */
static uint32_t time_config(void)
{
    /* call CMSIS SysTick function. It enables the SysTick interrupt at low priority */
    return SysTick_Config(CORE_CLK_FREQ / 1000); /* 1 ms period */
}

/*!
 * @brief Get milliseconds since last POR/reset.
 */
static float time_get_ms(void)
{
    uint32_t currMsCount;
    uint32_t currTick;
    uint32_t loadTick;

    do
    {
        currMsCount = g_msCount;
        currTick    = SysTick->VAL;
    } while (currMsCount != g_msCount);

    loadTick = CORE_CLK_FREQ / 1000;
    return (float)currMsCount + ((float)loadTick - (float)currTick) / (float)loadTick;
}

/*!
 * @brief Get througput in MB/s
 * @param elapsedMs Time interval in milliseconds.
 * @param numBytes Number of bytes processed within the given interval.
 * @return Throughput in MB/s.
 */
static float mmcau_get_throughput(float elapsedMs, size_t numBytes)
{
    return ((float)(1000 * numBytes / 1024 / 1024) / elapsedMs);
}

/*!
 * @brief Function mmcau_print_msg prints data bytes into console.
 */
static void mmcau_print_msg(const uint8_t *data, uint32_t length)
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

/*
 * mmcau_encrypt_aes_cbc: AES encryption function
 *
 * Parameters:
 *   [in] key: key of 8 bytes
 *   [in] mode: 128, 192 or 256 AES mode
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
static int mmcau_encrypt_aes_cbc(const uint8_t *key,
                                 uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint16_t rounds;
    uint8_t tempBlock[AES_BLOCK_LENGTH];
    uint8_t tempIV[AES_BLOCK_LENGTH];
    /*
     * AES128 needs 44 longwords for expansion
     * AES192 needs 52 longwords for expansion
     * AES256 needs 60 longwords for expansion
     *    Reserving 60 longwords as the max space
     */
    uint32_t keyLen;
    uint8_t keyExpansion[60 * 4];

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate AES mode*/
    if ((mode != 128u) && (mode != 192u) && (mode != 256u))
    {
        return MMCAU_ERROR; /*wrong AES mode*/
    }

    /*validate data length*/
    if (dataLength % AES_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*calculate number of AES rounds*/
    if (mode == 128u)
    {
        rounds = 10u;
        keyLen = 16u;
    }
    else if (mode == 192u)
    {
        rounds = 12u;
        keyLen = 24u;
    }
    else /*AES256*/
    {
        rounds = 14u;
        keyLen = 32u;
    }

    /*expand AES key*/
    MMCAU_AES_SetKey(key, keyLen, keyExpansion);

    /*execute AES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / AES_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, AES_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, AES_BLOCK_LENGTH);

        /*xor for CBC*/
        for (i = 0; i < AES_BLOCK_LENGTH; i++)
        {
            tempBlock[i] ^= tempIV[i];
        }

        /*FSL: single AES round*/
        MMCAU_AES_EncryptEcb(tempBlock, keyExpansion, rounds, outputData);

        /*update initVector for next 3DES round*/
        memcpy((void *)tempIV, (void *)outputData, AES_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += AES_BLOCK_LENGTH;
        outputData += AES_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}

/*
 * mmcau_decrypt_aes_cbc: AES decryption function
 *
 * Parameters:
 *   [in] key: key of 8 bytes
 *   [in] mode: 128, 192 or 256 AES mode
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
static int mmcau_decrypt_aes_cbc(const uint8_t *key,
                                 uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint16_t rounds;
    uint8_t tempBlock[AES_BLOCK_LENGTH];
    uint8_t tempIV[AES_BLOCK_LENGTH];
    /*
     * AES128 needs 44 longwords for expansion
     * AES192 needs 52 longwords for expansion
     * AES256 needs 60 longwords for expansion
     *    Reserving 60 longwords as the max space
     */
    uint8_t keyExpansion[60 * 4];
    uint32_t keyLen;

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate AES mode*/
    if ((mode != 128u) && (mode != 192u) && (mode != 256u))
    {
        return MMCAU_ERROR; /*wrong AES mode*/
    }

    /*validate data length*/
    if (dataLength % AES_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*calculate number of AES rounds*/
    if (mode == 128u)
    {
        rounds = 10u;
        keyLen = 16u;
    }
    else if (mode == 192u)
    {
        rounds = 12u;
        keyLen = 24u;
    }
    else /*AES256*/
    {
        rounds = 14u;
        keyLen = 32u;
    }

    /*expand AES key*/
    MMCAU_AES_SetKey(key, keyLen, keyExpansion);

    /*execute AES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / AES_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, AES_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, AES_BLOCK_LENGTH);

        /*FSL: single AES round*/
        MMCAU_AES_DecryptEcb(inputData, keyExpansion, rounds, outputData);

        /*xor for CBC*/
        for (i = 0; i < AES_BLOCK_LENGTH; i++)
        {
            outputData[i] ^= tempIV[i];
        }

        /*update initVector for next AES round*/
        memcpy(tempIV, tempBlock, AES_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += AES_BLOCK_LENGTH;
        outputData += AES_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}

/*
 * mmcau_encrypt_3des_cbc: 3DES encryption function
 *
 * Parameters:
 *   [in] key: key of 24 bytes
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (3DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
int mmcau_encrypt_3des_cbc(
    uint8_t *key, const uint8_t *inputData, uint8_t *outputData, uint16_t dataLength, const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint8_t tempBlock[DES3_BLOCK_LENGTH];
    uint8_t tempIV[DES3_BLOCK_LENGTH];

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate data length*/
    if (dataLength % DES3_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*fix parity key if needed: keep in mind LSB of each byte is only used for parity*/
    for (i = 0; i < DES3_KEY_LENGTH; i++)
    {
        key[i] = ((key[i] & 0xFEu) | g_parityBits[key[i] >> 1]);
    }

    /* optional parity check */
    if ((MMCAU_DES_ChkParity(key) != kStatus_Success) ||
        (MMCAU_DES_ChkParity(key + DES3_BLOCK_LENGTH) != kStatus_Success) ||
        (MMCAU_DES_ChkParity(key + (2 * DES3_BLOCK_LENGTH)) != kStatus_Success))
    {
        return MMCAU_ERROR; /*wrong parity*/
    }

    /*execute 3DES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / DES3_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, DES3_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, DES3_BLOCK_LENGTH);

        /*xor for CBC*/
        for (i = 0; i < DES3_BLOCK_LENGTH; i++)
        {
            tempBlock[i] ^= tempIV[i];
        }

        /*FSL: 1st DES round*/
        MMCAU_DES_EncryptEcb(tempBlock, key, outputData);

        /*FSL: 2nd DES round*/
        /*adjust key to 2nd part*/
        MMCAU_DES_DecryptEcb(outputData, key + DES3_BLOCK_LENGTH, outputData);

        /*FSL: 3rd DES round*/
        /*adjust key to 3rd part*/
        MMCAU_DES_EncryptEcb(outputData, key + (2 * DES3_BLOCK_LENGTH), outputData);

        /*update initVector for next 3DES round*/
        memcpy(tempIV, outputData, DES3_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += DES3_BLOCK_LENGTH;
        outputData += DES3_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}

/*
 * mmcau_decrypt_3des_cbc: 3DES decryption function
 *
 * Parameters:
 *   [in] key: key of 24 bytes
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (3DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
int mmcau_decrypt_3des_cbc(
    uint8_t *key, const uint8_t *inputData, uint8_t *outputData, uint16_t dataLength, const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint8_t tempBlock[DES3_BLOCK_LENGTH];
    uint8_t tempIV[DES3_BLOCK_LENGTH];

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate data length*/
    if (dataLength % DES3_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*fix parity key if needed: keep in mind LSB of each byte is only used for parity*/
    for (i = 0; i < DES3_KEY_LENGTH; i++)
    {
        key[i] = ((key[i] & 0xFEu) | g_parityBits[key[i] >> 1]);
    }

    /* optional -- check parity*/

    if ((MMCAU_DES_ChkParity(key) != kStatus_Success) ||
        (MMCAU_DES_ChkParity(key + DES3_BLOCK_LENGTH) != kStatus_Success) ||
        (MMCAU_DES_ChkParity(key + (2 * DES3_BLOCK_LENGTH)) != kStatus_Success))
    {
        return MMCAU_ERROR; /*wrong parity*/
    }

    /*execute 3DES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / DES3_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, DES3_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, DES3_BLOCK_LENGTH);

        /*FSL: 1st DES round*/
        MMCAU_DES_DecryptEcb(inputData, key + (2 * DES3_BLOCK_LENGTH), outputData);

        /*FSL: 2nd DES round*/
        /*adjust key to 2nd part*/
        MMCAU_DES_EncryptEcb(outputData, key + DES3_BLOCK_LENGTH, outputData);

        /*FSL: 3rd DES round*/
        /*adjust key to 3rd part*/
        MMCAU_DES_DecryptEcb(outputData, key, outputData);

        /*xor for CBC*/
        for (i = 0; i < DES3_BLOCK_LENGTH; i++)
        {
            outputData[i] ^= tempIV[i];
        }

        /*update initVector for next 3DES round*/
        memcpy(tempIV, tempBlock, DES3_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += DES3_BLOCK_LENGTH;
        outputData += DES3_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}

/*!
 * @brief Function mmcau_example_task demonstrates use of mmcau
 *        encryption/decryption functions on short sample text.
 */
static void mmcau_example_task(void)
{
    uint32_t length;
    uint32_t blocks;
    uint32_t resultSha1[SHA1_RESULT_LENGTH / sizeof(uint32_t)];
    uint32_t resultSha256[SHA256_RESULT_LENGTH / sizeof(uint32_t)];
    uint32_t resultMd5[MD5_RESULT_LENGTH / sizeof(uint32_t)];
    uint8_t status;
    float timeBefore;
    float timeAfter;
    int cycles;

    /* Print welcome string */
    PRINTF("............................. MMCAU  DRIVER  EXAMPLE ............................. \r\n\r\n");
    memset(&g_output[0], 0, OUTPUT_ARRAY_LEN);
    memset(&g_result[0], 0, OUTPUT_ARRAY_LEN);
    length = sizeof(g_testFull) - 1u;

    PRINTF("Testing input string: \r\n");
    mmcau_print_msg(&g_testFull[0], length);
    /* Format console output */
    PRINTF("\r\n");

    /***************************************************/
    /******* FIRST PART USING AES-CBC method *********/
    /***************************************************/
    PRINTF("----------------------------------- AES-CBC method --------------------------------------\r\n");

    /*   ENCRYPTION   */
    PRINTF("AES CBC Encryption of %d bytes.\r\n", length);

    /* Call AES_cbc encryption */
    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        status = mmcau_encrypt_aes_cbc(g_aesKey128, AES128, g_testFull, g_output, length, g_aesIV);
        if (status != MMCAU_OK)
        {
            PRINTF("AES CBC encryption failed !\r\n");
            return;
        }
        cycles--;
    }
    timeAfter = time_get_ms();

    /* Result message */
    PRINTF("AES CBC encryption finished. Speed %f MB/s.\r\n\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));

    /*   DECRYPTION   */
    PRINTF("AES CBC Decryption of %d bytes.\r\n", length);

    /* Call AES_cbc decryption */
    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        status = mmcau_decrypt_aes_cbc(g_aesKey128, AES128, g_output, g_result, length, g_aesIV);
        if (status != MMCAU_OK)
        {
            PRINTF("AES CBC decryption failed !\r\n");
            return;
        }
        cycles--;
    }
    timeAfter = time_get_ms();

    /* Result message */
    PRINTF("AES CBC decryption finished. Speed %f MB/s.\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));
    /* Print decrypted string */
    PRINTF("Decrypted string :\r\n");
    mmcau_print_msg(g_result, length);
    PRINTF("\r\n");

    /***************************************************/
    /******* SECOND PART USING DES3-CBC method ********/
    /***************************************************/
    PRINTF("----------------------------------- DES3-CBC method --------------------------------------\r\n");
    length = sizeof(g_testFull) - 1u;

    /*   ENCRYPTION   */
    PRINTF("DES3 CBC Encryption of %d bytes.\r\n", length);
    /* Call DES3_cbc encryption */
    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        status = mmcau_encrypt_3des_cbc(g_des3Key, g_testFull, g_output, length, g_des3IV);
        if (status != MMCAU_OK)
        {
            PRINTF("DES3 CBC encryption failed !\r\n");
            return;
        }
        cycles--;
    }
    timeAfter = time_get_ms();

    /* Result message */
    PRINTF("DES3 CBC encryption finished. Speed %f MB/s.\r\n\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));

    /*   DECRYPTION   */
    PRINTF("DES3 CBC decryption of %d bytes.\r\n", length);
    /* Call DES3_cbc decryption */
    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        status = mmcau_decrypt_3des_cbc(g_des3Key, g_output, g_result, length, g_des3IV);
        if (status != MMCAU_OK)
        {
            PRINTF("DES3 CBC decryption failed !\r\n");
            return;
        }
        cycles--;
    }
    timeAfter = time_get_ms();
    /* Result message */
    PRINTF("DES3 CBC decryption finished. Speed %f MB/s.\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));
    /* Print decrypted string */
    PRINTF("Decrypted string :\r\n");
    mmcau_print_msg(g_result, length);
    PRINTF("\r\n");

    /***************************************************/
    /******* THIRD PART USES HASH FUNCTIONALITY ******/
    /***************************************************/
    /*get string length*/
    length = sizeof(g_testSha);
    PRINTF("--------------------------------------- HASH ------------------------------------------\r\n");
    PRINTF("Computing hash of %d bytes. \r\n", length);
    PRINTF("Input string: \r\n");
    mmcau_print_msg((uint8_t *)&g_testSha[0], 43u /* length of the test string (without padding bits) */);
    PRINTF("\r\n");

    /*calculate number of 512-bit blocks present in the message*/
    /*multiple of CRYPTO_BLOCK_LENGTH bytes alway because of padding*/
    blocks = length / CRYPTO_BLOCK_LENGTH;

    /*Compute SHA1, SHA256 and MD5*/
    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        MMCAU_SHA1_Update(g_testSha, blocks, resultSha1);
        cycles--;
    }
    timeAfter = time_get_ms();
    PRINTF("Computed SHA1 at speed %f MB/s:\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));
    for (int i = 0; i < SHA1_RESULT_LENGTH / sizeof(uint32_t); i++)
    {
        PRINTF("%08x", resultSha1[i]);
    }
    PRINTF("\r\n\r\n");

    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        MMCAU_SHA256_Update(g_testSha, blocks, resultSha256);
        cycles--;
    }
    timeAfter = time_get_ms();
    PRINTF("Computed SHA256 at speed %f MB/s:\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));
    for (int i = 0; i < SHA256_RESULT_LENGTH / sizeof(uint32_t); i++)
    {
        PRINTF("%08x", resultSha256[i]);
    }
    PRINTF("\r\n\r\n");

    cycles     = CYCLES_FOR_THROUGHPUT;
    timeBefore = time_get_ms();
    while (cycles)
    {
        MMCAU_MD5_Update(g_testMd5, blocks, resultMd5);
        cycles--;
    }
    timeAfter = time_get_ms();
    /* NOTE: CAU lib provides resultMd5[] in most significant byte first order */
    PRINTF("Computed MD5 at speed %f MB/s:\r\n",
           mmcau_get_throughput(timeAfter - timeBefore, CYCLES_FOR_THROUGHPUT * length));
    for (int i = 0; i < MD5_RESULT_LENGTH / sizeof(uint32_t); i++)
    {
        uint8_t *pByte = (uint8_t *)&resultMd5[i];
        for (int j = 0; j < 4; j++)
        {
            PRINTF("%02x", pByte[j]);
        }
    }
    /* Format console output */
    PRINTF("\r\n\r\n");

    /* Goodbye message */
    PRINTF(".............. THE  END  OF  THE  MMCAU  DRIVER  EXAMPLE ................................\r\n");
}

/*!
 * @brief MMCAU example.
 */
int main(void)
{
    /* Init hardware*/
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    /* Init time measurement. SysTick method deployed. */
    if (time_config())
    {
        PRINTF("ERROR in SysTick Configuration\r\n");
    }
    else
    {
        /* Call example task */
        mmcau_example_task();
    }

    while (1)
    {
    }
}
