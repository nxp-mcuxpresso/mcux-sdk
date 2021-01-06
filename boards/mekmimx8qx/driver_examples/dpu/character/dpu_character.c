/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dpu.h"
#include "dpu_example.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
#include "fsl_prg.h"
#include "fsl_dpr.h"
#endif

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 *******************************************************************************/


/* ARGB8888, 4 bytes per pixel. */
#define APP_BPP 4

#define APP_MAKE_COLOR(red, green, blue, alpha) \
    ((((uint32_t)(alpha)) << 24U) | (((uint32_t)(red)) << 16U) | (((uint32_t)(green)) << 8U) | ((uint32_t)(blue)))

#define APP_COLOR_BLUE    APP_MAKE_COLOR(0, 0, 0xFF, 0xFF)
#define APP_COLOR_GREEN   APP_MAKE_COLOR(0, 0xFF, 0, 0xFF)
#define APP_COLOR_RED     APP_MAKE_COLOR(0xFF, 0, 0, 0xFF)
#define APP_COLOR_YELLOW  APP_MAKE_COLOR(0xFF, 0xFF, 0, 0xFF)
#define APP_COLOR_CYAN    APP_MAKE_COLOR(0, 0xFF, 0xFF, 0xFF)
#define APP_COLOR_MAGENTA APP_MAKE_COLOR(0xFF, 0, 0xFF, 0xFF)
#define APP_COLOR_BLACK   APP_MAKE_COLOR(0, 0, 0, 0xFF)
#define APP_COLOR_WHITE   APP_MAKE_COLOR(0xFF, 0xFF, 0xFF, 0xFF)
#define APP_COLOR_SILVER  APP_MAKE_COLOR(0xC0, 0xC0, 0xC0, 0xFF)
#define APP_COLOR_GRAY    APP_MAKE_COLOR(0x80, 0x80, 0x80, 0xFF)

#define APP_BOARDER 8

/* Font definitions */
#define FONT_HSIZE 6
#define FONT_VSIZE 8

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
/* Fetch Decode 1 is used in safety stream. */
#define APP_SAFETY_STREAM_DPR APP_FETCH_DECODE1_DPR
#define APP_SAFETY_STREAM_PRG APP_FETCH_DECODE1_PRG
#endif

#define APP_FB_WIDTH  APP_PANEL_WIDTH
#define APP_FB_HEIGHT APP_PANEL_HEIGHT

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
#define APP_FB_ADDR_ALIGN_BYTE   DPU_FETCH_UNIT_BURST_SIZE
#define APP_FB_STRIDE_ALIGN_BYTE DPU_FETCH_UNIT_BURST_SIZE
#else
#define APP_FB_ADDR_ALIGN_BYTE   (32U)
#define APP_FB_STRIDE_ALIGN_BYTE APP_BPP
#endif

#define APP_FB_STRIDE_BYTE  (SDK_SIZEALIGN(APP_BPP * APP_FB_WIDTH, APP_FB_STRIDE_ALIGN_BYTE))
#define APP_FB_STRIDE_PIXEL (APP_FB_STRIDE_BYTE / APP_BPP)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Frame buffer to display. */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_displayFrameBuffer[2][APP_FB_HEIGHT][APP_FB_STRIDE_PIXEL],
                              APP_FB_ADDR_ALIGN_BYTE);

volatile uint8_t s_inactiveFbIdx;
volatile bool s_safetyStreamPending;

const unsigned char FONTTYPE6_8[][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // - -
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00}, // -!-
    {0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}, // -"-
    {0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00}, // -#-
    {0x20, 0x78, 0xC0, 0x70, 0x28, 0xF0, 0x20, 0x00}, // -$-
    {0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18, 0x00}, // -%-
    {0x40, 0xA0, 0xA0, 0x40, 0xA8, 0x90, 0x68, 0x00}, // -&-
    {0x30, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00}, // -'-
    {0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00}, // -(-
    {0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00}, // -)-
    {0x20, 0xA8, 0x70, 0x20, 0x70, 0xA8, 0x20, 0x00}, // -*-
    {0x20, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x20, 0x00}, // -+-
    {0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0x80, 0x00}, // -,-
    {0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00}, // ---
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, // -.-
    {0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00}, // -/-
    {0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, 0x00}, // -0-
    {0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}, // -1-
    {0x70, 0x88, 0x08, 0x30, 0x40, 0x80, 0xF8, 0x00}, // -2-
    {0xF8, 0x08, 0x10, 0x30, 0x08, 0x88, 0x70, 0x00}, // -3-
    {0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, 0x00}, // -4-
    {0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, 0x00}, // -5-
    {0x38, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, 0x00}, // -6-
    {0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, 0x00}, // -7-
    {0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00}, // -8-
    {0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0xE0, 0x00}, // -9-
    {0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, 0x00}, // -:-
    {0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x80, 0x00}, // -;-
    {0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00}, // -<-
    {0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00}, // -=-
    {0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x00}, // ->-
    {0x70, 0x88, 0x10, 0x20, 0x20, 0x00, 0x20, 0x00}, // -?-
    {0x70, 0x88, 0xB8, 0xA8, 0xB8, 0x80, 0x78, 0x00}, // -@-
    {0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x00}, // -A-
    {0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00}, // -B-
    {0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00}, // -C-
    {0xF0, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF0, 0x00}, // -D-
    {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00}, // -E-
    {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x00}, // -F-
    {0x70, 0x88, 0x80, 0x80, 0xB8, 0x88, 0x78, 0x00}, // -G-
    {0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00}, // -H-
    {0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}, // -I-
    {0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00}, // -J-
    {0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00}, // -K-
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00}, // -L-
    {0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88, 0x00}, // -M-
    {0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00}, // -N-
    {0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00}, // -O-
    {0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00}, // -P-
    {0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, 0x00}, // -Q-
    {0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00}, // -R-
    {0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00}, // -S-
    {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00}, // -T-
    {0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00}, // -U-
    {0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00}, // -V-
    {0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88, 0x00}, // -W-
    {0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00}, // -X-
    {0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00}, // -Y-
    {0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00}, // -Z-
    {0xF0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xF0, 0x00}, // -[-
    {0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00}, // -\-
    {0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00}, // -]-
    {0x20, 0x70, 0xA8, 0x20, 0x20, 0x20, 0x20, 0x00}, // -^-
    {0x00, 0x20, 0x40, 0xF8, 0x40, 0x20, 0x00, 0x00}, // -_-
    {0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00}, // -`-
    {0x00, 0x00, 0xE0, 0x10, 0x70, 0x90, 0x68, 0x00}, // -a-
    {0x80, 0x80, 0xB0, 0xC8, 0x88, 0xC8, 0xB0, 0x00}, // -b-
    {0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x70, 0x00}, // -c-
    {0x08, 0x08, 0x68, 0x98, 0x88, 0x98, 0x68, 0x00}, // -d-
    {0x00, 0x00, 0x70, 0x88, 0xF0, 0x80, 0x70, 0x00}, // -e-
    {0x30, 0x48, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x00}, // -f-
    {0x00, 0x00, 0x70, 0x88, 0x88, 0x78, 0x08, 0xF0}, // -g-
    {0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00}, // -h-
    {0x20, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00}, // -i-
    {0x10, 0x00, 0x00, 0x30, 0x10, 0x10, 0x10, 0x60}, // -j-
    {0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x98, 0x00}, // -k-
    {0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00}, // -l-
    {0x00, 0x00, 0x50, 0xA8, 0xA8, 0xA8, 0xA8, 0x00}, // -m-
    {0x00, 0x00, 0xB0, 0x48, 0x48, 0x48, 0x48, 0x00}, // -n-
    {0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00}, // -o-
    {0x00, 0x00, 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80}, // -p-
    {0x00, 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x08}, // -q-
    {0x00, 0x00, 0xB0, 0x48, 0x40, 0x40, 0x40, 0x00}, // -r-
    {0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xF0, 0x00}, // -s-
    {0x40, 0x40, 0xF8, 0x40, 0x40, 0x48, 0x30, 0x00}, // -t-
    {0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x68, 0x00}, // -u-
    {0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00}, // -v-
    {0x00, 0x00, 0xA8, 0xA8, 0xA8, 0xA8, 0x50, 0x00}, // -w-
    {0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00}, // -x-
    {0x00, 0x00, 0x88, 0x88, 0x98, 0x68, 0x08, 0xF0}, // -y-
    {0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00}, // -z-
    {0x20, 0x40, 0x40, 0x80, 0x40, 0x40, 0x20, 0x00}, // -{-
    {0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x00}, // -|-
    {0x20, 0x10, 0x10, 0x08, 0x10, 0x10, 0x20, 0x00}, // -}-
    {0x00, 0x00, 0x40, 0xA8, 0x10, 0x00, 0x00, 0x00}, // -~-
    {0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x00}, // --
};

const unsigned char BIT_MASK[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*
 * Draw rectangle (not fill).
 *
 * bufferIdx: Buffer index.
 * ulx: X coordinate of upper left corner
 * uly: Y coordinate of upper left corner
 * lrx: X coordinate of lower right corner
 * lry: Y coordinate of lower right corner
 * color: Color of the rectangle
 */
void APP_DrawRectangle(uint8_t bufferIdx, uint16_t ulx, uint32_t uly, uint16_t lrx, uint16_t lry, uint32_t color)
{
    uint32_t i;

    for (i = ulx; i <= lrx; i++)
    {
        s_displayFrameBuffer[bufferIdx][uly][i] = color;
    }

    for (i = uly + 1; i < lry; i++)
    {
        s_displayFrameBuffer[bufferIdx][i][ulx] = color;
        s_displayFrameBuffer[bufferIdx][i][lrx] = color;
    }

    for (i = ulx; i <= lrx; i++)
    {
        s_displayFrameBuffer[bufferIdx][lry][i] = color;
    }
}

/*
 * Draw character
 *
 * bufferIdx: Buffer index.
 * x: X coordinate of upper left corner
 * y: Y coordinate of upper left corner
 * scale: Scale to enlarge the char
 * fgColor: Foreground color
 * bgColor: Background color
 * Return: Return 1 if success, otherwise 0.
 */
int32_t APP_DrawChar(
    uint8_t bufferIdx, char ch, uint16_t x, uint32_t y, uint16_t scale, uint32_t fgColor, uint32_t bgColor)
{
    unsigned char data;
    uint8_t i, j;
    uint16_t k;
    uint32_t color;

    if (x > (APP_FB_WIDTH - FONT_HSIZE * scale))
        return (0);
    if (y > (APP_FB_HEIGHT - FONT_VSIZE * scale))
        return (0);

    if (ch >= 0x20)
        ch -= 0x20;
    else
        return (0);

    for (i = 0; i < FONT_VSIZE; i++)
    {
        data = FONTTYPE6_8[(uint8_t)ch][i];

        for (j = 0; j < FONT_HSIZE; j++)
        {
            if ((data & BIT_MASK[j]) == 0)
            {
                color = bgColor;
            }
            else
            {
                color = fgColor;
            }

            k = scale;
            while (k--)
            {
                s_displayFrameBuffer[bufferIdx][y][x] = color;
                x++;
            }
        }
        x -= (FONT_HSIZE * scale);

        k = scale - 1;
        while (k--)
        {
            memcpy(&s_displayFrameBuffer[bufferIdx][y + 1][x], &s_displayFrameBuffer[bufferIdx][y][x],
                   FONT_HSIZE * scale * APP_BPP);
            y++;
        }
        y++;
    }

    return 1;
}

void APP_InitContentStream(void)
{
    /*
                 +-----------------+
                 |                 |
                 |  Const Frame 0  |
                 |                 |
                 +-----------------+
                          |
                          |
                          v
                 +-----------------+
                 |                 |
                 |  ExtDst 0 or 1  |
                 |                 |
                 +-----------------+
      */

    dpu_const_frame_config_t cfConfig;

    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, APP_CONTENT_STREAM_PIPELINE);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, APP_CONTENT_STREAM_EXTDST, DPU_MAKE_SRC_REG1(kDPU_UnitSrcConstFrame0));

    /* Const frame. */
    cfConfig.frameWidth  = APP_PANEL_WIDTH;
    cfConfig.frameHeight = APP_PANEL_HEIGHT;
    cfConfig.constColor  = 0;

    DPU_InitConstFrame(APP_DPU, kDPU_ConstFrame0);
    DPU_SetConstFrameConfig(APP_DPU, kDPU_ConstFrame0, &cfConfig);

    DPU_TriggerPipelineShadowLoad(APP_DPU, APP_CONTENT_STREAM_PIPELINE);
}

void APP_InitSafetyStream(void)
{
    dpu_const_frame_config_t cfConfig;
    dpu_layer_blend_config_t lbConfig;
    dpu_fetch_unit_config_t fetchConfig;
    dpu_src_buffer_config_t sbConfig;

    /*
     +-----------------+   +-----------------+
     |                 |   |                 |
     |   FetchDecode1  |   |  Const Frame 4  |
     |                 |   |                 |
     +-----------------+   +-----------------+
             |                      |
             |                      |
             |                      |
             |                      v
             |             +-----------------+
             |             |                 |
             +------------>|   LayerBlend 2  |
                           |                 |
                           +-----------------+
                                    |
                                    v
                           +-----------------+
                           |                 |
                           |  ExtDst 4 or 5  |
                           |                 |
                           +-----------------+
     */

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    dpr_buffer_config_t dprConfig;
    prg_buffer_config_t prgConfig;
#endif

    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, APP_SAFETY_STREAM_PIPELINE);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, APP_SAFETY_STREAM_EXTDST, DPU_MAKE_SRC_REG1(kDPU_UnitSrcLayerBlend2));

    /* LayerBlend */
    DPU_InitLayerBlend(APP_DPU, kDPU_LayerBlend2, DPU_MAKE_SRC_REG2(kDPU_UnitSrcConstFrame4, kDPU_UnitSrcFetchDecode1));

    /*
     * Show the FetchDecode output.
     *
     * lgConfig.constAlpha = 0U;
     * lgConfig.secAlphaBlendMode = kDPU_BlendOne;
     * lgConfig.primAlphaBlendMode = kDPU_BlendZero;
     * lgConfig.secColorBlendMode = kDPU_BlendOne;
     * lgConfig.primColorBlendMode = kDPU_BlendZero;
     * lgConfig.enableAlphaMask = true;
     * lgConfig.alphaMaskMode = kDPU_AlphaMaskPrim;
     */
    DPU_LayerBlendGetDefaultConfig(&lbConfig);
    DPU_SetLayerBlendConfig(APP_DPU, kDPU_LayerBlend2, &lbConfig);
    DPU_EnableLayerBlend(APP_DPU, kDPU_LayerBlend2, true);

    /* Const frame. */
    cfConfig.frameWidth  = APP_PANEL_WIDTH;
    cfConfig.frameHeight = APP_PANEL_HEIGHT;
    cfConfig.constColor  = 0;

    DPU_InitConstFrame(APP_DPU, kDPU_ConstFrame4);
    DPU_SetConstFrameConfig(APP_DPU, kDPU_ConstFrame4, &cfConfig);

    /* Fetch decode. */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
    fetchConfig.frameHeight = APP_PANEL_HEIGHT;
    fetchConfig.frameWidth  = APP_PANEL_WIDTH;
    DPU_InitFetchUnit(APP_DPU, kDPU_FetchDecode1, &fetchConfig);

    /* Frame buffer for fetch unit. */
    DPU_SrcBufferGetDefaultConfig(&sbConfig);
    sbConfig.strideBytes  = APP_FB_STRIDE_BYTE;
    sbConfig.bitsPerPixel = 32;
    sbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    sbConfig.bufferHeight = APP_FB_HEIGHT;
    sbConfig.bufferWidth  = APP_FB_WIDTH;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    sbConfig.baseAddr     = (uint32_t)s_displayFrameBuffer[0];

    /*
     * The first active frame buffer is 0. The s_inactiveFbIdx is set to 0 here,
     * when the first shadow load interrupt occurs, s_inactiveFbIdx will be set to 1.
     */
    s_inactiveFbIdx       = 0;
    s_safetyStreamPending = true;

    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchDecode1, 0, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchDecode1, 0, 0, 0);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchDecode1, 0, true);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Configure PRG. */
    PRG_BufferGetDefaultConfig(&prgConfig);
    prgConfig.width       = APP_FB_WIDTH;
    prgConfig.height      = APP_FB_HEIGHT;
    prgConfig.strideBytes = APP_FB_STRIDE_BYTE;
    prgConfig.dataType    = kPRG_DataType32Bpp;

    PRG_Init(APP_SAFETY_STREAM_PRG);
    PRG_SetBufferConfig(APP_SAFETY_STREAM_PRG, &prgConfig);
    PRG_SetBufferAddr(APP_SAFETY_STREAM_PRG, sbConfig.baseAddr);
    PRG_Enable(APP_SAFETY_STREAM_PRG, true);
    PRG_UpdateRegister(APP_SAFETY_STREAM_PRG);

    /* Configure DPR. */
    DPR_BufferGetDefaultConfig(&dprConfig);
    dprConfig.width       = APP_FB_WIDTH;
    dprConfig.height      = APP_FB_HEIGHT;
    dprConfig.strideBytes = APP_FB_STRIDE_BYTE;
    dprConfig.dataType    = kDPR_DataType32Bpp;

    DPR_Init(APP_SAFETY_STREAM_DPR);
    DPR_SetBufferConfig(APP_SAFETY_STREAM_DPR, &dprConfig);
    DPR_SetBufferAddr(APP_SAFETY_STREAM_DPR, sbConfig.baseAddr);
    DPR_Start(APP_SAFETY_STREAM_DPR);
#endif

    DPU_TriggerPipelineShadowLoad(APP_DPU, APP_SAFETY_STREAM_PIPELINE);
}

void APP_InitDisplayStream(void)
{
    dpu_display_timing_config_t displayTimingConfig;
    dpu_display_config_t displayConfig;

    DPU_DisplayTimingGetDefaultConfig(&displayTimingConfig);

    displayTimingConfig.flags  = APP_DPU_TIMING_FLAGS;
    displayTimingConfig.width  = APP_PANEL_WIDTH;
    displayTimingConfig.hsw    = APP_HSW;
    displayTimingConfig.hfp    = APP_HFP;
    displayTimingConfig.hbp    = APP_HBP;
    displayTimingConfig.height = APP_PANEL_HEIGHT;
    displayTimingConfig.vsw    = APP_VSW;
    displayTimingConfig.vfp    = APP_VFP;
    displayTimingConfig.vbp    = APP_VBP;

    DPU_InitDisplayTiming(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayTimingConfig);

    DPU_DisplayGetDefaultConfig(&displayConfig);

    /* Only show the safety stream. */
    displayConfig.displayMode = kDPU_DisplayOnlyPrim;

    displayConfig.primAreaStartX = 1;
    displayConfig.primAreaStartY = 1;

    displayConfig.secAreaStartX = 1;
    displayConfig.secAreaStartY = 1;

    DPU_SetDisplayConfig(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayConfig);

    DPU_TriggerDisplayShadowLoad(APP_DPU, APP_DPU_DISPLAY_INDEX);
}

void DPU_IRQHandler(void)
{
    uint32_t intGroup0Flags, intGroup1Flags;
    intGroup0Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 0);
    intGroup1Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 1);

    /*
     * If the safety stream shadow load interrupt happens, the inactive buffer
     * becames active buffer, pending status cleared.
     */
    if ((intGroup0Flags & APP_SAFETY_STREAM_INT_GROUP0) || (intGroup1Flags & APP_SAFETY_STREAM_INT_GROUP1))
    {
        s_inactiveFbIdx ^= 1;
        s_safetyStreamPending = false;
    }

    DPU_ClearInterruptsPendingFlags(APP_DPU, 0, intGroup0Flags);
    DPU_ClearInterruptsPendingFlags(APP_DPU, 1, intGroup1Flags);
}

void APP_ShowCharacter(void)
{
    uint16_t scale, scaleH, scaleV, x, y;
    char *stringToShow = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    uint32_t strLen    = strlen(stringToShow);
    uint8_t i;

    /* Find a scale suitable for current panel. */
    scaleH = (APP_FB_WIDTH - 4 * APP_BOARDER) / FONT_HSIZE;
    scaleV = (APP_FB_HEIGHT - 4 * APP_BOARDER) / FONT_VSIZE;

    scale = scaleH > scaleV ? scaleV : scaleH;

    /* Character upper left corner. */
    x = (APP_FB_WIDTH - scale * FONT_HSIZE) / 2;
    y = (APP_FB_HEIGHT - scale * FONT_VSIZE) / 2;

    while (1)
    {
        for (i = 0; i < strLen; i++)
        {
            /*
             * Wait for the shadow load pending status clear, then the inactive
             * buffer becames active buffer. We can access the inactive buffer now.
             */
            while (s_safetyStreamPending)
            {
            }

            /* Write to the inactive buffer. */
            APP_DrawChar(s_inactiveFbIdx, stringToShow[i], x, y, scale, APP_COLOR_BLUE, APP_COLOR_BLACK);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
            DPR_SetBufferAddr(APP_SAFETY_STREAM_DPR, (uint32_t)s_displayFrameBuffer[s_inactiveFbIdx]);

            PRG_SetBufferAddr(APP_SAFETY_STREAM_PRG, (uint32_t)s_displayFrameBuffer[s_inactiveFbIdx]);

            PRG_UpdateRegister(APP_SAFETY_STREAM_PRG);
#endif

            /* Pass the inactive buffer to DPU. */
            DPU_SetFetchUnitSrcBufferAddr(APP_DPU, kDPU_FetchDecode1, 0,
                                          (uint32_t)s_displayFrameBuffer[s_inactiveFbIdx]);
            s_safetyStreamPending = true;
            DPU_TriggerPipelineShadowLoad(APP_DPU, APP_SAFETY_STREAM_PIPELINE);

            /* Delay for a while to show the next character. */
            for (uint32_t j = 0; j < 0x2000000; j++)
            {
                __NOP();
            }
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0;

    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_PrepareDisplay();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    PRINTF("DPU Character Example:\r\n");

    /* Initialize the frameBuffer. */
    memset(s_displayFrameBuffer, 0, ARRAY_SIZE(s_displayFrameBuffer));
    /* Draw rectangle to the frame buffer. */
    for (i = 0; i < APP_BOARDER; i++)
    {
        APP_DrawRectangle(0, i, i, APP_FB_WIDTH - i - 1, APP_FB_HEIGHT - i - 1, APP_COLOR_YELLOW);
        APP_DrawRectangle(1, i, i, APP_FB_WIDTH - i - 1, APP_FB_HEIGHT - i - 1, APP_COLOR_YELLOW);
    }

    /*
     * Initialize workflow:
     * 1. Init DPU
     * 2. Configure pixel link.
     * 3. Init and start display interface.
     * 4. Start DPU
     */
    DPU_Init(APP_DPU);

    DPU_PreparePathConfig(APP_DPU);

    APP_InitContentStream();

    APP_InitSafetyStream();

    APP_InitDisplayStream();

    APP_InitPixelLink();

    APP_StartDisplayInterface();

    /* Enable interrupt. */
    DPU_EnableInterrupts(APP_DPU, 0, APP_SAFETY_STREAM_INT_GROUP0);
    DPU_EnableInterrupts(APP_DPU, 1, APP_SAFETY_STREAM_INT_GROUP0);

    DPU_StartDisplay(APP_DPU, APP_DPU_DISPLAY_INDEX);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    PRG_EnableShadowLoad(APP_SAFETY_STREAM_PRG, true);
    PRG_UpdateRegister(APP_SAFETY_STREAM_PRG);

    DPR_StartRepeat(APP_SAFETY_STREAM_DPR);
#endif

    APP_ShowCharacter();

    while (1)
    {
    }
}
