/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_bee.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FLEXSPI_START_ADDR 0x60000000U
/* User key feature is not enabled in fuses on RT1064 */
#define DCP_USE_USER_KEY 0
/* FAC region configuration registers */
#define REG0_START_ADDR_GPR GPR18
#define REG0_END_ADDR_GPR   GPR19
#define REG0_DECRYPT_EN_GPR GPR11
#define REG0_DECRYPT_EN     IOMUXC_GPR_GPR11_BEE_DE_RX_EN(1) /* FlexSPI data decryption enabled for region-0 */
#define AES_KEY_LEN     16
#define AES_NONCE_LEN   16
#define BEE_REGION_SIZE 0x10000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(BEE_USE_USER_KEY) && BEE_USE_USER_KEY

/* AES user key must be stored in little_endian. */
/* aesKey = 01020304_05060708_090A0B0C_0D0E0F10h */
static const uint8_t aesKey[] __attribute__((aligned)) = {0x10, 0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09,
                                                          0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01};
#endif

static const uint8_t aesNonce[] __attribute__((aligned)) = {0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                                                            0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    bee_region_config_t beeConfig;
    IOMUXC_GPR_Type *iomuxc = IOMUXC_GPR;
    status_t status;

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nBEE Example.\r\n");

    /* Get default configuration. */
    BEE_GetDefaultConfig(&beeConfig);

    /* Set BEE region 0 to work in AES CTR mode */
    beeConfig.region0Mode = kBEE_AesCtrMode;
    /* Configure BEE region 0 to use whole address space of FAC by setting bottom and top address of BEE region 1 to
     * zero */
    beeConfig.region1Bot = 0U;
    beeConfig.region1Top = 0U;

    /* Configure Start address and end address of access protected region-0 */
    iomuxc->REG0_START_ADDR_GPR = FLEXSPI_START_ADDR;
    iomuxc->REG0_END_ADDR_GPR   = FLEXSPI_START_ADDR + BEE_REGION_SIZE;
    /* Enable BEE data decryption of memory region-0 */
    iomuxc->REG0_DECRYPT_EN_GPR = REG0_DECRYPT_EN;

    /* Init BEE driver and apply the configuration */
    BEE_Init(BEE);
    BEE_SetConfig(BEE, &beeConfig);

/* Set AES user key for region0. BEE_KEY0_SEL fuse must be set to SW-GP2 to be able to use this feature. */
#if defined(BEE_USE_USER_KEY) && BEE_USE_USER_KEY
    status = BEE_SetRegionKey(BEE, kBEE_Region0, aesKey, AES_KEY_LEN);
    if (status != kStatus_Success)
    {
        PRINTF("Error setting region0 user key!\r\n");
    }
#endif

    status = BEE_SetRegionNonce(BEE, kBEE_Region0, aesNonce, AES_NONCE_LEN);
    if (status != kStatus_Success)
    {
        PRINTF("Error setting region0 nonce!\r\n");
    }

    /* Enable BEE decryption */
    BEE_Enable(BEE);

    PRINTF("BEE was successfully configured for reading from 0x%x to 0x%x.\r\n", FLEXSPI_START_ADDR,
           FLEXSPI_START_ADDR + BEE_REGION_SIZE);

    /* Disable and deinit BEE */
    BEE_Deinit(BEE);
    PRINTF("Example end.\r\n");

    while (1)
    {
    }
}
