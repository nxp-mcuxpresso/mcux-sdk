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

#include "fsl_cau3.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


#define TEST_ASSERT(a)       \
    if (!(a))                \
    {                        \
        PRINTF("error\r\n"); \
        do                   \
        {                    \
        } while (1);         \
    }

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void TestAesEcb(void)
{
    static const uint8_t keyAes128[] __attribute__((aligned)) = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                                                                 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    static const uint8_t plainAes128[]                        = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
                                          0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
    static const uint8_t cipherAes128[]                       = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
                                           0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};
    uint8_t cipher[16];
    uint8_t output[16];
    status_t status;

    cau3_handle_t m_handle;
    cau3_handle_t *handle = &m_handle;

    /* CAU3 driver supports 4 key slots. */
    handle->keySlot = kCAU3_KeySlot1;

    /* After enryption/decryption request is sent to CAU3, the Host CPU will execute WFE instruction opcode
     * until CAU3 signals task done by setting the event.
     */
    handle->taskDone = kCAU3_TaskDoneEvent;

    /* Loads the key into CAU3's DMEM memory and expands the AES key schedule. */
    status = CAU3_AES_SetKey(CAU3, handle, keyAes128, 16);
    TEST_ASSERT(kStatus_Success == status);

    CAU3_AES_Encrypt(CAU3, handle, plainAes128, cipher);
    TEST_ASSERT(memcmp(cipher, cipherAes128, 16) == 0);

    CAU3_AES_Decrypt(CAU3, handle, cipher, output);
    TEST_ASSERT(memcmp(output, plainAes128, 16) == 0);

    PRINTF("AES ECB Test pass\r\n");
}

void TestSha256(void)
{
    status_t status;
    size_t outLength;
    unsigned int length;
    unsigned char output[32];

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

    length    = sizeof(message) - 1;
    outLength = sizeof(output);
    memset(&output, 0, outLength);

    /************************ SHA-256 **************************/
    status = CAU3_HASH(CAU3, kCAU3_Sha256, message, length, output, &outLength);
    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(outLength == 32u);
    TEST_ASSERT(memcmp(output, sha256, outLength) == 0);

    PRINTF("SHA-256 Test pass\r\n");
}

void TestModMul(void)
{
    status_t status;

    /* CAU3 PKHA APIs treat integer as little endian array of bytes.
     * simple_mp_int_t union type provides imlicit conversion from uint32_t to little endian bytes - assuming little
     * endian ARM
     * architecture.
     */
    typedef union _simple_mp_int
    {
        uint32_t val;
        uint8_t b[4];
    } simple_mp_int_t;

    /*
       Example for Modular multiplication

       (30 * 10) mod 297 = 3
    */
    simple_mp_int_t A;
    simple_mp_int_t B;
    simple_mp_int_t N;
    simple_mp_int_t res;
    simple_mp_int_t expected;
    size_t sizeRes;

    A.val        = 30U;
    B.val        = 10U;
    N.val        = 297U;
    expected.val = 3U;

    /* CAU3 PKHA APIs use little endian integers.
     *
     */

    status =
        CAU3_PKHA_ModMul(CAU3, A.b, sizeof(A), B.b, sizeof(B), N.b, sizeof(N), res.b, &sizeRes, kCAU3_PKHA_IntegerArith,
                         kCAU3_PKHA_NormalValue, kCAU3_PKHA_NormalValue, kCAU3_PKHA_NoTimingEqualized);

    TEST_ASSERT(kStatus_Success == status);
    TEST_ASSERT(CAU3_PKHA_CompareBigNum(res.b, sizeRes, expected.b, sizeof(expected)) == 0);

    PRINTF("ModMul Test pass\r\n");
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("CAU3 Driver Example\r\n\r\n");

    /* Initialize CAU3 */
    CAU3_Init(CAU3);

    /* Call CAU3 APIs */
    TestAesEcb();
    TestSha256();
    TestModMul();

    while (1)
    {
    }
}
