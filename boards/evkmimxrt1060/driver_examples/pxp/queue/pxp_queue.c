/*
 * Copyright  2017-2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_pxp.h"
#include "display_support.h"

#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_PXP PXP

/* Use RGB565 or XRGB8888 */
#define USE_RGB565 0

#define APP_IMG_WIDTH  DEMO_BUFFER_WIDTH
#define APP_IMG_HEIGHT DEMO_BUFFER_HEIGHT

/* PS input buffer is square. */
#if APP_IMG_WIDTH > APP_IMG_HEIGHT
#define APP_PS_SIZE APP_IMG_HEIGHT
#else
#define APP_PS_SIZE APP_IMG_WIDTH
#endif

#define APP_PS_ULC_X ((APP_IMG_WIDTH / 2) - (APP_PS_SIZE / 2))
#define APP_PS_ULC_Y ((APP_IMG_HEIGHT / 2) - (APP_PS_SIZE / 2))
#define APP_PS_LRC_X ((APP_IMG_WIDTH / 2) + (APP_PS_SIZE / 2) - 1U)
#define APP_PS_LRC_Y ((APP_IMG_HEIGHT / 2) + (APP_PS_SIZE / 2) - 1U)

#if USE_RGB565

typedef uint16_t pixel_t;
#define APP_BPP            2U /* Use 16-bit RGB565 format. */
#define APP_RED            0xF100U
#define APP_GREEN          0x07E0U
#define APP_BLUE           0x001FU
#define APP_WHITE          0xFFFFU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB565
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB565
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB565
#define APP_DC_FORMAT      kVIDEO_PixelFormatRGB565

#else

typedef uint32_t pixel_t;
#define APP_BPP            4U /* Use 32-bit XRGB888 format. */
#define APP_RED            0x00FF0000U
#define APP_GREEN          0x0000FF00U
#define APP_BLUE           0x000000FFU
#define APP_WHITE          0xFFFFFFU
#define APP_PXP_PS_FORMAT  kPXP_PsPixelFormatRGB888
#define APP_PXP_AS_FORMAT  kPXP_AsPixelFormatRGB888
#define APP_PXP_OUT_FORMAT kPXP_OutputPixelFormatRGB888
#define APP_DC_FORMAT      kVIDEO_PixelFormatXRGB8888

#endif

typedef struct _pxp_command
{
    uint32_t CTRL;
    uint32_t STAT;
    uint32_t OUT_CTRL;
    uint32_t OUT_BUF;
    uint32_t OUT_BUF2;
    uint32_t OUT_PITCH;
    uint32_t OUT_LRC;
    uint32_t OUT_PS_ULC;
    uint32_t OUT_PS_LRC;
    uint32_t OUT_AS_ULC;
    uint32_t OUT_AS_LRC;
    uint32_t PS_CTRL;
    uint32_t PS_BUF;
    uint32_t PS_UBUF;
    uint32_t PS_VBUF;
    uint32_t PS_PITCH;
    uint32_t PS_BACHGROUND;
    uint32_t PS_SCALE;
    uint32_t PS_OFFSET;
    uint32_t PS_CLRKEYLOW;
    uint32_t PS_CLRKEYHIGH;
    uint32_t AS_CTRL;
    uint32_t AS_BUF;
    uint32_t AS_PITCH;
    uint32_t AS_CLRKEYLOW;
    uint32_t AS_CLRKEYHIGH;
    uint32_t CSC1_COEF0;
    uint32_t CSC1_COEF1;
    uint32_t CSC1_COEF2;
#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
    uint32_t CSC2_CTRL;
    uint32_t CSC2_COEF0;
    uint32_t CSC2_COEF1;
    uint32_t CSC2_COEF2;
    uint32_t CSC2_COEF3;
    uint32_t CSC2_COEF4;
    uint32_t CSC2_COEF5;
#else
    uint32_t CSC2_RESERVE[7];
#endif
#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
    uint32_t LUT_CTRL;
    uint32_t LUT_ADDR;
    uint32_t LUT_DATA;
    uint32_t LUT_EXTMEM;
    uint32_t CFA;
#else
    uint32_t LUT_RESERVE[5];
#endif
    uint32_t HIST_CTRL;
    uint32_t HIST2_PARAM;
    uint32_t HIST4_PARAM;
    uint32_t HIST8_PARAM0;
    uint32_t HIST8_PARAM1;
    uint32_t HIST16_PARAM0;
    uint32_t HIST16_PARAM1;
    uint32_t HIST16_PARAM2;
    uint32_t HIST16_PARAM3;
    uint32_t POWER;
    uint32_t NEXT;
} pxp_command_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void APP_InitInputBuffer(void);
static void APP_InitLcdif(void);
static void APP_InitPxp(void);
static void APP_InitPxpCommand(void);
static void APP_RotateCmdQueue(void);
static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_BufferLcd[2][APP_IMG_HEIGHT][APP_IMG_WIDTH], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pixel_t s_psBufferPxp[APP_PS_SIZE][APP_PS_SIZE], FRAME_BUFFER_ALIGN);
AT_NONCACHEABLE_SECTION_ALIGN(static pxp_command_t pxpCommand, 4); /* 32-bit align. */

static uint8_t curLcdBufferIdx = 0;

/*
 * When new frame buffer sent to display, it might not be shown immediately.
 * Application could use callback to get new frame shown notification, at the
 * same time, when this flag is set, application could write to the older
 * frame buffer.
 */
static volatile bool s_newFrameShown = false;
static dc_fb_info_t fbInfo;

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nPXP command queue example start...\r\n");

    APP_InitInputBuffer();
    APP_InitPxpCommand();
    APP_InitPxp();
    APP_InitLcdif();

    APP_RotateCmdQueue();

    while (1)
    {
    }
}

static void APP_InitLcdif(void)
{
    status_t status;

    BOARD_PrepareDisplayController();

    status = g_dc.ops->init(&g_dc);
    if (kStatus_Success != status)
    {
        PRINTF("Display initialization failed\r\n");
        assert(0);
    }

    g_dc.ops->getLayerDefaultConfig(&g_dc, 0, &fbInfo);
    fbInfo.pixelFormat = APP_DC_FORMAT;
    fbInfo.width       = APP_IMG_WIDTH;
    fbInfo.height      = APP_IMG_HEIGHT;
    fbInfo.startX      = DEMO_BUFFER_START_X;
    fbInfo.startY      = DEMO_BUFFER_START_Y;
    fbInfo.strideBytes = APP_IMG_WIDTH * APP_BPP;
    g_dc.ops->setLayerConfig(&g_dc, 0, &fbInfo);

    g_dc.ops->setCallback(&g_dc, 0, APP_BufferSwitchOffCallback, NULL);

    s_newFrameShown = false;
    g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_BufferLcd[curLcdBufferIdx]);

    /* For the DBI interface display, application must wait for the first
     * frame buffer sent to the panel.
     */
    if ((g_dc.ops->getProperty(&g_dc) & kDC_FB_ReserveFrameBuffer) == 0)
    {
        while (s_newFrameShown == false)
        {
        }
    }

    s_newFrameShown = true;

    g_dc.ops->enableLayer(&g_dc, 0);
}

static void APP_InitPxp(void)
{
    PXP_Init(APP_PXP);
}

static void APP_RotateCmdQueue(void)
{
    uint8_t i;

    static const pxp_rotate_degree_t degrees[] = {
        kPXP_Rotate0,
        kPXP_Rotate90,
        kPXP_Rotate180,
        kPXP_Rotate270,
    };

    for (;;)
    {
        for (i = 0; i < ARRAY_SIZE(degrees); i++)
        {
            /*
             * Wait for the new set frame buffer active, so that the older frame
             * buffer is inactive, then PXP could output to the older frame buffer.
             */
            while (s_newFrameShown == false)
            {
            }

            /* Switch to the other LCD buffer. */
            curLcdBufferIdx ^= 1U;

            /* Prepare next buffer for LCD. */
            pxpCommand.CTRL    = (pxpCommand.CTRL & ~PXP_CTRL_ROTATE_MASK) | PXP_CTRL_ROTATE(degrees[i]);
            pxpCommand.OUT_BUF = (uint32_t)s_BufferLcd[curLcdBufferIdx];
            __DSB();

            while (PXP_IsNextCommandPending(APP_PXP))
            {
            }
            PXP_SetNextCommand(APP_PXP, &pxpCommand);

            /* Wait for process complete. */
            while (!(kPXP_CompleteFlag & PXP_GetStatusFlags(APP_PXP)))
            {
            }

            PXP_ClearStatusFlags(APP_PXP, kPXP_CompleteFlag);

            /* Now new frame is ready, pass it to LCDIF. */
            s_newFrameShown = false;
            g_dc.ops->setFrameBuffer(&g_dc, 0, (void *)s_BufferLcd[curLcdBufferIdx]);

            /* Show the active frame buffer for a while. */
            SDK_DelayAtLeastUs(1 * 1000 * 1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }
    }
}

static void APP_InitInputBuffer(void)
{
    uint32_t i, j;

    /*
     * The PS input buffer is:
     *
     *  -----------------------------
     *  |             |             |
     *  |             |             |
     *  |   BLUE      |     RED     |
     *  |             |             |
     *  |             |             |
     *  |-------------+-------------|
     *  |                           |
     *  |                           |
     *  |           GREEN           |
     *  |                           |
     *  |                           |
     *  -----------------------------
     */
    for (i = 0; i < (APP_PS_SIZE / 2); i++)
    {
        for (j = 0; j < (APP_PS_SIZE / 2); j++)
        {
            s_psBufferPxp[i][j] = APP_BLUE;
        }

        for (; j < APP_PS_SIZE; j++)
        {
            s_psBufferPxp[i][j] = APP_RED;
        }
    }

    for (; i < APP_PS_SIZE; i++)
    {
        for (j = 0; j < APP_PS_SIZE; j++)
        {
            s_psBufferPxp[i][j] = APP_GREEN;
        }
    }

    memset(s_BufferLcd, 0x0U, sizeof(s_BufferLcd));
}

static void APP_InitPxpCommand(void)
{
    pxpCommand.CTRL       = PXP_CTRL_ROT_POS(1) | PXP_CTRL_ENABLE_MASK;
    pxpCommand.STAT       = 0x00000000;                              /* STAT, don't care */
    pxpCommand.OUT_CTRL   = PXP_OUT_CTRL_FORMAT(APP_PXP_OUT_FORMAT); /* OUT_CTRL */
    pxpCommand.OUT_BUF    = (uint32_t)s_BufferLcd[0];                /* OUT_BUF */
    pxpCommand.OUT_BUF2   = 0x00000000;                              /* OUT_BUF2 */
    pxpCommand.OUT_PITCH  = APP_BPP * APP_IMG_WIDTH;                 /* OUT_PITCH */
    pxpCommand.OUT_LRC    = PXP_OUT_LRC_Y(APP_IMG_HEIGHT - 1U) | PXP_OUT_LRC_X(APP_IMG_WIDTH - 1U); /* OUT_LRC */
    pxpCommand.OUT_PS_ULC = PXP_OUT_PS_ULC_Y(APP_PS_ULC_Y) | PXP_OUT_PS_ULC_X(APP_PS_ULC_X);        /* OUT_PS_ULC */
    pxpCommand.OUT_PS_LRC = PXP_OUT_PS_LRC_Y(APP_PS_LRC_Y) | PXP_OUT_PS_LRC_X(APP_PS_LRC_X);        /* OUT_PS_LRC */
    /* Disable AS. */
    pxpCommand.OUT_AS_ULC    = 0x3FFF3FFF;                            /* OUT_AS_ULC */
    pxpCommand.OUT_AS_LRC    = 0x00000000;                            /* OUT_AS_LRC */
    pxpCommand.PS_CTRL       = PXP_PS_CTRL_FORMAT(APP_PXP_PS_FORMAT); /* PS_CTRL */
    pxpCommand.PS_BUF        = (uint32_t)s_psBufferPxp;               /* PS_BUF */
    pxpCommand.PS_UBUF       = 0x00000000;                            /* PS_UBUF */
    pxpCommand.PS_VBUF       = 0x00000000;                            /* PS_VBUF */
    pxpCommand.PS_PITCH      = APP_BPP * APP_PS_SIZE;                 /* PS_PITCH */
    pxpCommand.PS_BACHGROUND = 0x00000000;                            /* PS_BACHGROUND */
    pxpCommand.PS_SCALE      = 0x10001000;                            /* PS_SCALE */
    pxpCommand.PS_OFFSET     = 0x00000000;                            /* PS_OFFSET */
    pxpCommand.PS_CLRKEYLOW  = 0x00FFFFFF;                            /* PS_CLRKEYLOW */
    pxpCommand.PS_CLRKEYHIGH = 0x00000000;                            /* PS_CLRKEYHIGH */
    pxpCommand.AS_CTRL       = 0x00000000;                            /* AS_CTRL */
    pxpCommand.AS_BUF        = 0x00000000;                            /* AS_BUF */
    pxpCommand.AS_PITCH      = 0x00000000;                            /* AS_PITCH */
    pxpCommand.AS_CLRKEYLOW  = 0x00FFFFFF;                            /* AS_CLRKEYLOW */
    pxpCommand.AS_CLRKEYHIGH = 0x00000000;                            /* AS_CLRKEYHIGH */
    pxpCommand.CSC1_COEF0    = PXP_CSC1_COEF0_BYPASS_MASK;            /* CSC1_COEF0, don't care. */
    pxpCommand.CSC1_COEF1    = 0x00000000;                            /* CSC1_COEF1, don't care. */
    pxpCommand.CSC1_COEF2    = 0x00000000;                            /* CSC1_COEF2, don't care. */
#if !(defined(FSL_FEATURE_PXP_HAS_NO_CSC2) && FSL_FEATURE_PXP_HAS_NO_CSC2)
    pxpCommand.CSC2_CTRL  = PXP_CSC2_CTRL_BYPASS_MASK; /* CSC2_CTRL */
    pxpCommand.CSC2_COEF0 = 0x00000000;                /* CSC2_COEF0, don't care. */
    pxpCommand.CSC2_COEF1 = 0x00000000;                /* CSC2_COEF1, don't care. */
    pxpCommand.CSC2_COEF2 = 0x00000000;                /* CSC2_COEF2, don't care. */
    pxpCommand.CSC2_COEF3 = 0x00000000;                /* CSC2_COEF3, don't care. */
    pxpCommand.CSC2_COEF4 = 0x00000000;                /* CSC2_COEF4, don't care. */
    pxpCommand.CSC2_COEF5 = 0x00000000;                /* CSC2_COEF5, don't care. */
#endif
#if !(defined(FSL_FEATURE_PXP_HAS_NO_LUT) && FSL_FEATURE_PXP_HAS_NO_LUT)
    pxpCommand.LUT_CTRL   = PXP_LUT_CTRL_BYPASS_MASK; /* LUT_CTRL */
    pxpCommand.LUT_ADDR   = 0x00000000;               /* LUT_ADDR */
    pxpCommand.LUT_DATA   = 0x00000000;               /* LUT_DATA */
    pxpCommand.LUT_EXTMEM = 0x00000000;               /* LUT_EXTMEM */
    pxpCommand.CFA        = 0x00000000;               /* CFA */
#endif
    pxpCommand.HIST_CTRL     = 0x00000020; /* HIST_CTRL */
    pxpCommand.HIST2_PARAM   = 0x00000F00; /* HIST2_PARAM */
    pxpCommand.HIST4_PARAM   = 0x0F0A0500; /* HIST4_PARAM */
    pxpCommand.HIST8_PARAM0  = 0x06040200; /* HIST8_PARAM0 */
    pxpCommand.HIST8_PARAM1  = 0x0F0D0B09; /* HIST8_PARAM1 */
    pxpCommand.HIST16_PARAM0 = 0x03020100; /* HIST16_PARAM0 */
    pxpCommand.HIST16_PARAM1 = 0x07060504; /* HIST16_PARAM1 */
    pxpCommand.HIST16_PARAM2 = 0x0B0A0908; /* HIST16_PARAM2 */
    pxpCommand.HIST16_PARAM3 = 0x0F0E0D0C; /* HIST16_PARAM3 */
    pxpCommand.POWER         = 0x00000000; /* POWER */
    pxpCommand.NEXT          = 0x00000000; /* NEXT, don't care */
}

static void APP_BufferSwitchOffCallback(void *param, void *switchOffBuffer)
{
    s_newFrameShown = true;
}
