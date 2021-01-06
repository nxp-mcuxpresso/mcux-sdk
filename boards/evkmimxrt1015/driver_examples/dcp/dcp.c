/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
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

#include "fsl_dcp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define DCP_TEST_USE_OTP_KEY 0 /* Set to 1 to select OTP key for AES encryption/decryption. */

#define TEST_ASSERT(a)       \
    if (!(a))                \
    {                        \
        PRINTF("error\r\n"); \
        do                   \
        {                    \
        } while (1);         \
    }

#if DCP_TEST_USE_OTP_KEY
typedef enum _dcp_otp_key_select
{
    kDCP_OTPMKKeyLow  = 1U, /* Use [127:0] from snvs key as dcp key */
    kDCP_OTPMKKeyHigh = 2U, /* Use [255:128] from snvs key as dcp key */
    kDCP_OCOTPKeyLow  = 3U, /* Use [127:0] from ocotp key as dcp key */
    kDCP_OCOTPKeyHigh = 4U  /* Use [255:128] from ocotp key as dcp key */
} dcp_otp_key_select;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
#if DCP_TEST_USE_OTP_KEY
status_t DCP_OTPKeySelect(dcp_otp_key_select keySelect)
{
    if (keySelect == kDCP_OTPMKKeyLow)
    {
        IOMUXC_GPR->GPR3 &= ~(1 << IOMUXC_GPR_GPR3_DCP_KEY_SEL_SHIFT);
        IOMUXC_GPR->GPR10 &= ~(1 << IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX_SHIFT);
    }

    else if (keySelect == kDCP_OTPMKKeyHigh)
    {
        IOMUXC_GPR->GPR3 |= (1 << IOMUXC_GPR_GPR3_DCP_KEY_SEL_SHIFT);
        IOMUXC_GPR->GPR10 &= ~(1 << IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX_SHIFT);
    }

    else if (keySelect == kDCP_OCOTPKeyLow)
    {
        IOMUXC_GPR->GPR3 &= ~(1 << IOMUXC_GPR_GPR3_DCP_KEY_SEL_SHIFT);
        IOMUXC_GPR->GPR10 |= (1 << IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX_SHIFT);
    }

    else if (keySelect == kDCP_OCOTPKeyHigh)
    {
        IOMUXC_GPR->GPR3 |= (1 << IOMUXC_GPR_GPR3_DCP_KEY_SEL_SHIFT);
        IOMUXC_GPR->GPR10 |= (1 << IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX_SHIFT);
    }

    else
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}
#endif

void TestAesEcb(void)
{
    /* Input data for DCP like IV, key and plaintext should be handled properly
     * when DCACHE is used (e.g. Clean&Invalidate, use non-cached memory)
     */
    static const uint8_t keyAes128[] __attribute__((aligned)) = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                                                 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    static const uint8_t plainAes128[]                        = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                                          0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
    static const uint8_t cipherAes128[]                       = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                                           0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};
#if DCP_TEST_USE_OTP_KEY
#warning Please update cipherAes128 variables to match expected AES ciphertext for your OTP key.
#endif

    AT_NONCACHEABLE_SECTION_INIT(static uint8_t cipher[16]);
    AT_NONCACHEABLE_SECTION_INIT(static uint8_t output[16]);
    status_t status;

    dcp_handle_t m_handle;

    m_handle.channel    = kDCP_Channel0;
    m_handle.swapConfig = kDCP_NoSwap;

#if DCP_TEST_USE_OTP_KEY
    m_handle.keySlot = kDCP_OtpKey;
#else
    m_handle.keySlot = kDCP_KeySlot0;
#endif

    status = DCP_AES_SetKey(DCP, &m_handle, keyAes128, 16);
    TEST_ASSERT(kStatus_Success == status);

    DCP_AES_EncryptEcb(DCP, &m_handle, plainAes128, cipher, 16);
    TEST_ASSERT(memcmp(cipher, cipherAes128, 16) == 0);

    DCP_AES_DecryptEcb(DCP, &m_handle, cipher, output, 16);
    TEST_ASSERT(memcmp(output, plainAes128, 16) == 0);

    PRINTF("AES ECB Test pass\r\n");
}

void TestAesCbc(void)
{
    /* Input data for DCP like IV, key and plaintext should be handled properly
     * when DCACHE is used (e.g. Clean&Invalidate, use non-cached memory)
     */
    static const uint8_t keyAes128[] __attribute__((aligned)) = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                                                 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    static const uint8_t plainAes128[]                        = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                                          0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
    static const uint8_t ive[]                                = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    static const uint8_t cipherAes128[] = {0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46,
                                           0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d};
#if DCP_TEST_USE_OTP_KEY
#warning Please update cipherAes128 variables to match expected AES ciphertext for your OTP key.
#endif

    AT_NONCACHEABLE_SECTION_INIT(static uint8_t cipher[16]);
    AT_NONCACHEABLE_SECTION_INIT(static uint8_t output[16]);
    status_t status;

    dcp_handle_t m_handle;

    m_handle.channel    = kDCP_Channel0;
    m_handle.swapConfig = kDCP_NoSwap;

#if DCP_TEST_USE_OTP_KEY
    m_handle.keySlot = kDCP_OtpKey;
#else
    m_handle.keySlot = kDCP_KeySlot0;
#endif

    status = DCP_AES_SetKey(DCP, &m_handle, keyAes128, 16);
    TEST_ASSERT(kStatus_Success == status);

    DCP_AES_EncryptCbc(DCP, &m_handle, plainAes128, cipher, 16, ive);
    TEST_ASSERT(memcmp(cipher, cipherAes128, 16) == 0);

    DCP_AES_DecryptCbc(DCP, &m_handle, cipher, output, 16, ive);
    TEST_ASSERT(memcmp(output, plainAes128, 16) == 0);

    PRINTF("AES CBC Test pass\r\n");
}

void TestSha1(void)
{
    status_t status;
    size_t outLength;
    unsigned int length;
    /* Input data for DCP like input and output should be handled properly
     * when DCACHE is used (e.g. Clean&Invalidate, use non-cached memory)
     */
    AT_NONCACHEABLE_SECTION(static unsigned char outputSha[20]);

    static const uint8_t message[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

    /* Expected SHA-1 for the message. */
    static const uint8_t sha1[] = {0x84, 0x98, 0x3e, 0x44, 0x1c, 0x3b, 0xd2, 0x6e, 0xba, 0xae,
                                   0x4a, 0xa1, 0xf9, 0x51, 0x29, 0xe5, 0xe5, 0x46, 0x70, 0xf1};

    dcp_handle_t m_handle;

    m_handle.channel    = kDCP_Channel0;
    m_handle.keySlot    = kDCP_KeySlot0;
    m_handle.swapConfig = kDCP_NoSwap;

    length    = sizeof(message) - 1;
    outLength = sizeof(outputSha);
    memset(&outputSha, 0, outLength);

    /************************ SHA-1 **************************/
    status = DCP_HASH(DCP, &m_handle, kDCP_Sha1, message, length, outputSha, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 20u);
    TEST_ASSERT(memcmp(outputSha, sha1, outLength) == 0);

    PRINTF("SHA-1 Test pass\r\n");
}

void TestSha256(void)
{
    status_t status;
    size_t outLength;
    unsigned int length;
    /* Input data for DCP like input and output should be handled properly
     * when DCACHE is used (e.g. Clean&Invalidate, use non-cached memory)
     */
    AT_NONCACHEABLE_SECTION(static unsigned char outputSha256[32]);

    static const uint8_t message[] =
        "Be that word our sign of parting, bird or fiend! I shrieked upstarting"
        "Get thee back into the tempest and the Nights Plutonian shore!"
        "Leave no black plume as a token of that lie thy soul hath spoken!"
        "Leave my loneliness unbroken! quit the bust above my door!"
        "Take thy beak from out my heart, and take thy form from off my door!"
        "Quoth the raven, Nevermore.  ";

    /* Expected SHA-256 for the message. */
    static const unsigned char sha256[] = {0x63, 0x76, 0xea, 0xcc, 0xc9, 0xa2, 0xc0, 0x43, 0xf4, 0xfb, 0x01,
                                           0x34, 0x69, 0xb3, 0x0c, 0xf5, 0x28, 0x63, 0x5c, 0xfa, 0xa5, 0x65,
                                           0x60, 0xef, 0x59, 0x7b, 0xd9, 0x1c, 0xac, 0xaa, 0x31, 0xf7};

    dcp_handle_t m_handle;

    m_handle.channel    = kDCP_Channel0;
    m_handle.keySlot    = kDCP_KeySlot0;
    m_handle.swapConfig = kDCP_NoSwap;

    length    = sizeof(message) - 1;
    outLength = sizeof(outputSha256);
    memset(&outputSha256, 0, outLength);

    /************************ SHA-256 **************************/
    status = DCP_HASH(DCP, &m_handle, kDCP_Sha256, message, length, outputSha256, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 32u);
    TEST_ASSERT(memcmp(outputSha256, sha256, outLength) == 0);

    PRINTF("SHA-256 Test pass\r\n");
}

void TestCrc32(void)
{
    status_t status;
    size_t outLength;
    unsigned int length;
    /* Input data for DCP like input and output should be handled properly
     * when DCACHE is used (e.g. Clean&Invalidate, use non-cached memory)
     */
    AT_NONCACHEABLE_SECTION_INIT(static uint8_t output[4]);

    dcp_handle_t m_handle;

    m_handle.channel    = kDCP_Channel0;
    m_handle.keySlot    = kDCP_KeySlot0;
    m_handle.swapConfig = kDCP_NoSwap;

    /************************ Test Messages **************************/
    static const uint8_t message_32[]                              = "abcdbcdecdefdefgefghfghighijhijk";
    static const uint8_t __attribute__((aligned(4))) message_256[] = {
        0x2D, 0x09, 0x73, 0xA7, 0xAA, 0x69, 0xC4, 0xFF, 0xF6, 0xC8, 0x9C, 0x0D, 0xCE, 0x82, 0x19, 0x85,
        0xB4, 0x2B, 0x8B, 0x20, 0x84, 0x07, 0xCA, 0x66, 0x9E, 0xCF, 0xA5, 0x0B, 0x19, 0x70, 0x04, 0x65,
        0x33, 0xB1, 0x49, 0xE0, 0xAA, 0x77, 0xE9, 0x17, 0x7F, 0x11, 0xF7, 0x57, 0xE2, 0x40, 0x23, 0x5D,
        0x81, 0x17, 0x1F, 0x90, 0x3B, 0xE4, 0xAB, 0x7D, 0x63, 0x4D, 0xE1, 0x57, 0x3E, 0x2D, 0x35, 0x0F, /* 64 bytes */

        0x09, 0xA4, 0x33, 0x29, 0x60, 0xB5, 0xF4, 0x08, 0xBB, 0xA1, 0xB1, 0x18, 0xB2, 0x83, 0x3C, 0xDC,
        0xC8, 0xF5, 0x0B, 0x28, 0x71, 0xA9, 0x62, 0x44, 0x8E, 0x1E, 0x58, 0xE1, 0xA9, 0x4E, 0xD8, 0x15,
        0x44, 0xF9, 0xFF, 0x1B, 0xED, 0x3C, 0xA1, 0x65, 0xF6, 0xDC, 0x45, 0x64, 0xCF, 0x85, 0x07, 0xF2,
        0x83, 0x74, 0x54, 0xD3, 0xD4, 0xA0, 0xDA, 0xEC, 0x4D, 0x88, 0x9D, 0x9B, 0x25, 0xFA, 0x6D, 0xD0, /* 128 bytes */

        0x41, 0xBA, 0x93, 0xA7, 0x60, 0x46, 0x8F, 0xD3, 0x06, 0x8A, 0x98, 0xBD, 0xFB, 0x8B, 0x64, 0xA0,
        0x33, 0x23, 0x5A, 0x65, 0x9C, 0x57, 0x14, 0x28, 0xE2, 0x52, 0xCE, 0x6F, 0x5A, 0x4D, 0xE2, 0x63,
        0x5E, 0x1C, 0xE9, 0xF6, 0xE7, 0x3E, 0x80, 0x25, 0x85, 0xAB, 0xED, 0xFE, 0xBB, 0x98, 0x83, 0xFB,
        0xCF, 0x43, 0x71, 0x4F, 0xF3, 0x94, 0x76, 0x08, 0x72, 0x5E, 0xEB, 0x11, 0xF3, 0xDE, 0xF1, 0x3C, /* 192 bytes */

        0x95, 0xCF, 0x1B, 0x8F, 0x7D, 0xF8, 0x59, 0x2C, 0x4F, 0xCB, 0xB1, 0xBB, 0xCF, 0x74, 0x47, 0x42,
        0x1E, 0x69, 0x80, 0x26, 0xAA, 0x56, 0xEE, 0x91, 0xE9, 0x43, 0xB8, 0x7F, 0xF9, 0x01, 0xCB, 0x0C,
        0x1D, 0xF2, 0xFD, 0xAD, 0xC2, 0xB0, 0xC2, 0x00, 0x53, 0x09, 0x37, 0x07, 0xD0, 0x2E, 0x43, 0xC9,
        0xED, 0x08, 0x3C, 0x38, 0xE8, 0x1B, 0xC3, 0xBD, 0x7C, 0x59, 0xAA, 0xCA, 0xEA, 0x06, 0x34, 0x76, /* 256 bytes */
        0x00, 0x00, 0x00, 0x00};
    /* Expected CRC-32 for the message.
     * CRC-32 params:
     * width=32 poly=0x04c11db7 init=0xffffffff refin=false refout=false xorout=0x00000000
     * http://reveng.sourceforge.net/crc-catalogue/
     */
    static const unsigned char crc32_32[]  = {0x7f, 0x04, 0x6a, 0xdd};
    static const unsigned char crc32_256[] = {0xce, 0xda, 0x1d, 0x36};
    static const unsigned char crc32_260[] = {0x07, 0xe3, 0xde, 0x8e};

    /************************ CRC-32 - Test Message 32 **************************/
    length    = sizeof(message_32) - 1;
    outLength = sizeof(output);
    memset(&output, 0, outLength);

    status = DCP_HASH(DCP, &m_handle, kDCP_Crc32, message_32, length, output, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 4u);
    TEST_ASSERT(memcmp(output, crc32_32, outLength) == 0);

    /************************ CRC-32 - Test Message 256 *************************/

    length    = 256;
    outLength = sizeof(output);
    memset(&output, 0, outLength);

    status = DCP_HASH(DCP, &m_handle, kDCP_Crc32, message_256, length, output, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 4u);
    TEST_ASSERT(memcmp(output, crc32_256, outLength) == 0);

    /************************ CRC-32 - Test Message 260 *************************/
    length    = 260;
    outLength = sizeof(output);
    memset(&output, 0, outLength);

    status = DCP_HASH(DCP, &m_handle, kDCP_Crc32, message_256, length, output, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 4u);
    TEST_ASSERT(memcmp(output, crc32_260, outLength) == 0);

    PRINTF("CRC-32 Test pass\r\n");
}

/*!
 * @brief Main function
 */
int main(void)
{
    dcp_config_t dcpConfig;

    /* Init hardware*/
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Note: When DCACHE is enabled input and output buffers should be in non-cached memory
     * or handled properly (DCACHE Clean and Invalidate).
     * Disable DCHACHE by calling SCB_DisableDCache();
     */

    PRINTF("DCP Driver Example\r\n\r\n");

    /* Initialize DCP */
    DCP_GetDefaultConfig(&dcpConfig);

#if DCP_TEST_USE_OTP_KEY
    /* Set OTP key type in IOMUX registers before initializing DCP. */
    /* Software reset of DCP must be issued after changing the OTP key type. */
    DCP_OTPKeySelect(kDCP_OTPMKKeyLow);
#endif

    /* Reset and initialize DCP */
    DCP_Init(DCP, &dcpConfig);

    /* Call DCP APIs */
    TestAesEcb();
    TestAesCbc();
    TestSha1();
    TestSha256();
    TestCrc32();

    /* Deinitialize DCP */
    DCP_Deinit(DCP);

    while (1)
    {
    }
}
