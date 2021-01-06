/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_pxp.h"

#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_PXP PXP

#define INPUT_BUF_WIDTH   128
#define INPUT_BUF_HEIGHT  64
#define OUTPUT_BUF_WIDTH  64
#define OUTPUT_BUF_HEIGHT 32
#define COPY_WIDTH        16
#define COPY_HEIGHT       8
#define SRC_OFFSET_X      0
#define SRC_OFFSET_Y      0
#define DEST_OFFSET_X     10
#define DEST_OFFSET_Y     20

#define APP_ASSERT(cond)     \
    if (true != (cond))      \
    {                        \
        PRINTF("ERROR\r\n"); \
        while (1)            \
            ;                \
    }

#define APP_BUF_FORMAT         kPXP_AsPixelFormatARGB8888
#define APP_BUF_BYTE_PER_PIXEL 4

#if APP_BUF_BYTE_PER_PIXEL == 2
typedef uint16_t pixel_t;
#else
typedef uint32_t pixel_t;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void APP_InitInputBuffer(void);
static void APP_InitPxp(void);
static void APP_CopyPicture(void);
static void APP_VerifyCopy(
    uint16_t x_i, uint16_t y_i, uint16_t x_o, uint16_t y_o, uint16_t copyWidth, uint16_t copyHeight);

/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION(static pixel_t s_inputBuf[INPUT_BUF_HEIGHT][INPUT_BUF_WIDTH]);
AT_NONCACHEABLE_SECTION(static pixel_t s_outputBuf[OUTPUT_BUF_HEIGHT][OUTPUT_BUF_WIDTH]);

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPXP picture copy example start...\r\n");

    APP_InitInputBuffer();
    APP_InitPxp();
    APP_CopyPicture();

    PRINTF("\r\nPXP picture copy example success...\r\n");

    while (1)
    {
    }
}

static void APP_InitInputBuffer(void)
{
    uint8_t val = 0;
    uint16_t x, y;
    uint8_t *data = (void *)s_inputBuf;

    for (y = 0; y < INPUT_BUF_HEIGHT; y++)
    {
        for (x = 0; x < INPUT_BUF_WIDTH; x++)
        {
            for (uint8_t i = 0; i < APP_BUF_BYTE_PER_PIXEL; i++)
            {
                *(data++) = val;
                val += 3;
            }
        }
    }
}

static void APP_InitPxp(void)
{
    PXP_Init(APP_PXP);
}

static void APP_CopyPicture(void)
{
    pxp_pic_copy_config_t pxpCopyConfig;

    /*
     *                       Source buffer:
     *    srcPicBaseAddr
     *    +-----------------------------------------------------------+
     *    |                                                           |
     *    |  (srcOffsetX, srcOffsetY)                                 |
     *    |           +-------------------+                           |
     *    |           |                   |                           |
     *    |           |                   |                           |
     *    |           |                   | height                    |
     *    |           |                   |                           |
     *    |           |                   |                           |
     *    |           +-------------------+                           |
     *    |                 width                                     |
     *    |                                                           |
     *    |                       srcPicthBytes                       |
     *    +-----------------------------------------------------------+
     *
     *                      Destination buffer:
     *    destPicBaseAddr
     *    +-------------------------------------------+
     *    |                                           |
     *    |                                           |
     *    |                                           |
     *    |  (destOffsetX, destOffsetY)               |
     *    |       +-------------------+               |
     *    |       |                   |               |
     *    |       |                   |               |
     *    |       |                   | height        |
     *    |       |                   |               |
     *    |       |                   |               |
     *    |       +-------------------+               |
     *    |             width                         |
     *    |                                           |
     *    |                                           |
     *    |                                           |
     *    |                  destPicthBytes           |
     *    +-------------------------------------------+
     *
     */

    /* Clear the whole output buffer. */
    memset(s_outputBuf, 0, sizeof(s_outputBuf));

    pxpCopyConfig.srcPicBaseAddr  = (uint32_t)s_inputBuf;
    pxpCopyConfig.srcPitchBytes   = sizeof(pixel_t) * INPUT_BUF_WIDTH;
    pxpCopyConfig.srcOffsetX      = SRC_OFFSET_X;
    pxpCopyConfig.srcOffsetY      = SRC_OFFSET_Y;
    pxpCopyConfig.destPicBaseAddr = (uint32_t)s_outputBuf;
    pxpCopyConfig.destPitchBytes  = sizeof(pixel_t) * OUTPUT_BUF_WIDTH;
    pxpCopyConfig.destOffsetX     = DEST_OFFSET_X;
    pxpCopyConfig.destOffsetY     = DEST_OFFSET_Y;
    pxpCopyConfig.width           = COPY_WIDTH;
    pxpCopyConfig.height          = COPY_HEIGHT;
    pxpCopyConfig.pixelFormat     = APP_BUF_FORMAT;

    PXP_StartPictureCopy(APP_PXP, &pxpCopyConfig);

    PRINTF("Copy from (%d, %d) in input image to (%d, %d) in output image, size: (%d, %d) \r\n", SRC_OFFSET_X,
           SRC_OFFSET_Y, DEST_OFFSET_X, DEST_OFFSET_Y, COPY_WIDTH, COPY_HEIGHT);

    /* Wait for process complete. */
    while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
    {
    }

    PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

    /* Verify result. */
    APP_VerifyCopy(SRC_OFFSET_X, SRC_OFFSET_Y, DEST_OFFSET_X, DEST_OFFSET_Y, COPY_WIDTH, COPY_HEIGHT);
}

static void APP_VerifyCopy(
    uint16_t x_i, uint16_t y_i, uint16_t x_o, uint16_t y_o, uint16_t copyWidth, uint16_t copyHeight)
{
    uint16_t x, y;
    pixel_t src_pixel;

    /*
     * Verify both the copied region and not copied region.
     * The copied region should match the source buffer.
     * The not copied region should be 0.
     */

    for (y = 0; y < y_o; y++)
    {
        for (x = 0; x < OUTPUT_BUF_WIDTH; x++)
        {
            APP_ASSERT(s_outputBuf[y][x] == 0);
        }
    }

    for (; y < y_o + copyHeight; y++)
    {
        for (x = 0; x < x_o; x++)
        {
            APP_ASSERT(s_outputBuf[y][x] == 0);
        }

        for (; x < x_o + copyWidth; x++)
        {
            src_pixel = s_inputBuf[y_i + y - y_o][x_i + x - x_o];

#if APP_BUF_BYTE_PER_PIXEL == 2
            if (APP_BUF_FORMAT == kPXP_AsPixelFormatRGB444)
            {
                /* When XRGB4444 mode used, output pixel bits[12:15] are set to 1 by PXP. */
                src_pixel |= 0xF000;
            }
            else if (APP_BUF_FORMAT == kPXP_AsPixelFormatRGB555)
            {
                /* When XRGB1555 mode used, output pixel bits[15] are set to 1 by PXP. */
                src_pixel |= 0x8000;
            }
#else
            if (APP_BUF_FORMAT == kPXP_AsPixelFormatRGB888)
            {
                /* When XRGB8888 mode used, output pixel bits[24:31] are set to 1 by PXP. */
                src_pixel |= 0xFF000000;
            }
#endif

            APP_ASSERT(s_outputBuf[y][x] == src_pixel);
        }

        for (; x < OUTPUT_BUF_WIDTH; x++)
        {
            APP_ASSERT(s_outputBuf[y][x] == 0);
        }
    }

    for (; y < OUTPUT_BUF_HEIGHT; y++)
    {
        for (x = 0; x < OUTPUT_BUF_WIDTH; x++)
        {
            APP_ASSERT(s_outputBuf[y][x] == 0);
        }
    }
}
