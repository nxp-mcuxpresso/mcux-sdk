/*
 * Copyright 2017, 2019 NXP
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

#if (APP_PANEL_WIDTH < APP_PANEL_HEIGHT)
#define APP_PORTRAIT 1
#else
#define APP_PORTRAIT 0
#endif

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

#if APP_PORTRAIT
#define APP_STREAM_WIDTH  (APP_PANEL_WIDTH)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT / 2)
#else
#define APP_STREAM_WIDTH  (APP_PANEL_WIDTH / 2)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT)
#endif

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
#define APP_STREAM_FB_ADDR_ALIGN_BYTE   DPU_FETCH_UNIT_BURST_SIZE
#define APP_STREAM_FB_STRIDE_ALIGN_BYTE DPU_FETCH_UNIT_BURST_SIZE
#else
#define APP_STREAM_FB_ADDR_ALIGN_BYTE   (32U)
#define APP_STREAM_FB_STRIDE_ALIGN_BYTE APP_BPP
#endif

#define APP_STREAM_FB_STRIDE_BYTE  (SDK_SIZEALIGN(APP_BPP * APP_STREAM_WIDTH, APP_STREAM_FB_STRIDE_ALIGN_BYTE))
#define APP_STREAM_FB_STRIDE_PIXEL (APP_STREAM_FB_STRIDE_BYTE / APP_BPP)

#define APP_WIN_WIDTH  (APP_STREAM_WIDTH * 1 / 2)
#define APP_WIN_HEIGHT (APP_STREAM_HEIGHT * 1 / 4)

#define APP_WIN0_OFFSET_X (0)
#define APP_WIN0_OFFSET_Y (0)

#define APP_WIN1_OFFSET_X (APP_WIN_WIDTH)
#define APP_WIN1_OFFSET_Y (0)

#define APP_WIN2_OFFSET_X (0)
#define APP_WIN2_OFFSET_Y (APP_WIN_HEIGHT * 3)

#define APP_WIN3_OFFSET_X (APP_WIN_WIDTH)
#define APP_WIN3_OFFSET_Y (APP_WIN_HEIGHT * 3)

#define APP_FLOAT_WIN_INIT_OFFSET_X (0)
#define APP_FLOAT_WIN_INIT_OFFSET_Y (APP_WIN_HEIGHT)

/* Structure for safety stream or content stream. */
typedef struct app_dpu_stream
{
    /* General. */
    uint16_t height;
    uint16_t width;
    uint16_t strideBytes;

    /* Fetch decode unit. */
    dpu_unit_t fetchUnit;
    uint32_t frameBuffers[2];
    volatile uint8_t activeFbIdx; /* Active frame buffer index. */

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    DPR_Type *dpr;
    PRG_Type *prg;
#endif

    /* Const frame. */
    dpu_unit_t constFrame;
    uint32_t constColor;

    /* Layer blend. */
    dpu_unit_t layerBlend;
    uint8_t layerBlendPrimSrc;
    uint8_t layerBlendSecSrc;

    /* Ext Dst. */
    dpu_unit_t extDst;
    uint8_t extDstSrc;

    /* Pipeline. */
    dpu_unit_t pipeline;

    volatile bool isShadowLoadPending;

    /* Interrupt. */
    uint32_t intGroup0;
    uint32_t intGroup1;
} app_dpu_stream_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Frame buffer for red window */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_redWinFrameBuffer[APP_WIN_HEIGHT][APP_WIN_WIDTH], 32);
/* Frame buffer for green window */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_greenWinFrameBuffer[APP_WIN_HEIGHT][APP_WIN_WIDTH], 32);
/* Frame buffer for blue window */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_blueWinFrameBuffer[APP_WIN_HEIGHT][APP_WIN_WIDTH], 32);
/* Frame buffer for white window */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_whiteWinFrameBuffer[APP_WIN_HEIGHT][APP_WIN_WIDTH], 32);
/* Frame buffer for floating window */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_floatWinFrameBuffer[APP_WIN_HEIGHT][APP_WIN_WIDTH], 32);
/* Frame buffer to display. */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_displayFrameBuffer[4][APP_STREAM_HEIGHT][APP_STREAM_FB_STRIDE_PIXEL],
                              APP_STREAM_FB_ADDR_ALIGN_BYTE);

/* Blit engine sequence completed. */
volatile bool s_isBlitEngineSeqComplete = false;
/* Blit engine shadow load. */
volatile bool s_isBlitEngineShadowPending = false;

app_dpu_stream_t safetyStream = {
    /* General. */
    .height      = APP_STREAM_HEIGHT,
    .width       = APP_STREAM_WIDTH,
    .strideBytes = APP_STREAM_FB_STRIDE_BYTE,

    /* Fetch unit. */
    .fetchUnit    = kDPU_FetchDecode1,
    .frameBuffers = {(uint32_t)s_displayFrameBuffer[0], (uint32_t)s_displayFrameBuffer[1]},

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    .dpr = APP_FETCH_DECODE1_DPR,
    .prg = APP_FETCH_DECODE1_PRG,
#endif

    /* Const frame. */
    .constFrame = kDPU_ConstFrame4,
    .constColor = DPU_MAKE_CONST_COLOR(0x00, 0x00, 0x00, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend2,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame4,
    .layerBlendSecSrc  = kDPU_UnitSrcFetchDecode1,

    /* Ext Dst. */
    .extDst    = APP_SAFETY_STREAM_EXTDST,
    .extDstSrc = kDPU_UnitSrcLayerBlend2,

    /* Pipeline. */
    .pipeline = APP_SAFETY_STREAM_PIPELINE,

    /* Interrupt. */
    .intGroup0 = APP_SAFETY_STREAM_INT_GROUP0,
    .intGroup1 = APP_SAFETY_STREAM_INT_GROUP1,
};

app_dpu_stream_t contentStream = {
    /* General. */
    .height      = APP_STREAM_HEIGHT,
    .width       = APP_STREAM_WIDTH,
    .strideBytes = APP_STREAM_FB_STRIDE_BYTE,

    /* Fetch unit. */
    .fetchUnit    = kDPU_FetchDecode0,
    .frameBuffers = {(uint32_t)s_displayFrameBuffer[2], (uint32_t)s_displayFrameBuffer[3]},

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    .dpr = APP_FETCH_DECODE0_DPR,
    .prg = APP_FETCH_DECODE0_PRG,
#endif

    /* Const frame. */
    .constFrame = kDPU_ConstFrame0,
    .constColor = DPU_MAKE_CONST_COLOR(0xFF, 0xFF, 0xFF, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend0,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame0,
    .layerBlendSecSrc  = kDPU_UnitSrcFetchDecode0,

    /* Ext Dst. */
    .extDst    = APP_CONTENT_STREAM_EXTDST,
    .extDstSrc = kDPU_UnitSrcLayerBlend0,

    /* Pipeline. */
    .pipeline = APP_CONTENT_STREAM_PIPELINE,

    /* Interrupt. */
    .intGroup0 = APP_CONTENT_STREAM_INT_GROUP0,
    .intGroup1 = APP_CONTENT_STREAM_INT_GROUP1,
};

/*******************************************************************************
 * Code
 ******************************************************************************/
void APP_InitFrameBuffer(uint32_t frameBuffer, uint16_t height, uint16_t width, uint16_t strideBytes, uint32_t color)
{
    uint32_t i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            ((uint32_t *)(frameBuffer + strideBytes * i))[j] = color;
        }
    }
}

bool APP_IsStreamShadowPending(app_dpu_stream_t *stream)
{
    return stream->isShadowLoadPending;
}

void APP_TriggerStreamShadowLoad(app_dpu_stream_t *stream)
{
    stream->isShadowLoadPending = true;
    DPU_TriggerPipelineShadowLoad(APP_DPU, stream->pipeline);
}

void APP_CheckAndUpdateStreamStatus(app_dpu_stream_t *stream, uint32_t intGroup0Flags, uint32_t intGroup1Flags)
{
    if ((intGroup0Flags & stream->intGroup0) || (intGroup1Flags & stream->intGroup1))
    {
        stream->isShadowLoadPending = false;
    }
}

void APP_TriggerStreamFrameBufferSwitch(app_dpu_stream_t *stream)
{
    uint32_t newBufferAddr = stream->frameBuffers[stream->activeFbIdx ^ 1U];

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    DPR_SetBufferAddr(stream->dpr, newBufferAddr);

    PRG_SetBufferAddr(stream->prg, newBufferAddr);

    PRG_UpdateRegister(stream->prg);
#endif

    DPU_SetFetchUnitSrcBufferAddr(APP_DPU, stream->fetchUnit, 0, newBufferAddr);
    APP_TriggerStreamShadowLoad(stream);
    stream->activeFbIdx ^= 1;
}

bool APP_IsBlitEngineShadowPending(void)
{
    return s_isBlitEngineShadowPending;
}

void APP_TriggerAndStartBlitEngine(void)
{
    s_isBlitEngineShadowPending = true;
    DPU_TriggerPipelineShadowLoad(APP_DPU, kDPU_PipelineStore9);
    DPU_StartStore(APP_DPU, kDPU_Store9);
}

void APP_TriggerBlitEngineSeqComplete(void)
{
    s_isBlitEngineSeqComplete = false;
    DPU_TriggerPipelineCompleteInterrupt(APP_DPU, kDPU_PipelineStore9);
}

bool APP_IsBlitEngineSeqComplete(void)
{
    return s_isBlitEngineSeqComplete;
}

uint32_t APP_GetStreamInactiveFrameBuffer(app_dpu_stream_t *stream)
{
    return stream->frameBuffers[stream->activeFbIdx ^ 1];
}

void APP_InitStream(app_dpu_stream_t *stream)
{
    dpu_const_frame_config_t cfConfig;
    dpu_layer_blend_config_t lbConfig;
    dpu_fetch_unit_config_t fetchConfig;
    dpu_src_buffer_config_t sbConfig;

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    dpr_buffer_config_t dprConfig;
    prg_buffer_config_t prgConfig;
#endif

    /* Pipeline. */
    DPU_InitPipeline(APP_DPU, stream->pipeline);

    /* ExtDst. */
    DPU_InitExtDst(APP_DPU, stream->extDst, DPU_MAKE_SRC_REG1(stream->extDstSrc));

    /* Layer blend. */
    DPU_InitLayerBlend(APP_DPU, stream->layerBlend,
                       DPU_MAKE_SRC_REG2(stream->layerBlendPrimSrc, stream->layerBlendSecSrc));
    DPU_LayerBlendGetDefaultConfig(&lbConfig);
    DPU_SetLayerBlendConfig(APP_DPU, stream->layerBlend, &lbConfig);
    DPU_EnableLayerBlend(APP_DPU, stream->layerBlend, true);

    /* Const frame. */
    cfConfig.frameWidth  = stream->width;
    cfConfig.frameHeight = stream->height;
    cfConfig.constColor  = stream->constColor;

    DPU_InitConstFrame(APP_DPU, stream->constFrame);
    DPU_SetConstFrameConfig(APP_DPU, stream->constFrame, &cfConfig);

    /* Fetch unit. */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
    fetchConfig.frameHeight = stream->height;
    fetchConfig.frameWidth  = stream->width;
    DPU_InitFetchUnit(APP_DPU, stream->fetchUnit, &fetchConfig);

    /* Frame buffer. */
    DPU_SrcBufferGetDefaultConfig(&sbConfig);
    sbConfig.strideBytes  = stream->strideBytes;
    sbConfig.bitsPerPixel = 32;
    sbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    sbConfig.bufferHeight = stream->height;
    sbConfig.bufferWidth  = stream->width;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    sbConfig.baseAddr     = stream->frameBuffers[0];

    /*
     * The first active frame buffer is 0. The activeFbIdx is set to 1 here,
     * when the first shadow load interrupt occurs, activeFbIdx will be set to 0.
     */
    stream->activeFbIdx = 1;

    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, stream->fetchUnit, 0, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, stream->fetchUnit, 0, 0, 0);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, stream->fetchUnit, 0, true);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)

    /* Config PGR. */
    PRG_BufferGetDefaultConfig(&prgConfig);
    prgConfig.width       = stream->width;
    prgConfig.height      = stream->height;
    prgConfig.strideBytes = stream->strideBytes;
    prgConfig.dataType    = kPRG_DataType32Bpp;

    PRG_Init(stream->prg);
    PRG_SetBufferConfig(stream->prg, &prgConfig);
    PRG_SetBufferAddr(stream->prg, sbConfig.baseAddr);
    PRG_Enable(stream->prg, true);
    PRG_UpdateRegister(stream->prg);

    /* Config DPR */
    DPR_BufferGetDefaultConfig(&dprConfig);
    dprConfig.width       = stream->width;
    dprConfig.height      = stream->height;
    dprConfig.strideBytes = stream->strideBytes;
    dprConfig.dataType    = kDPR_DataType32Bpp;

    DPR_Init(stream->dpr);
    DPR_SetBufferConfig(stream->dpr, &dprConfig);
    DPR_SetBufferAddr(stream->dpr, sbConfig.baseAddr);
    DPR_Start(stream->dpr);
#endif

    APP_TriggerStreamShadowLoad(stream);

    DPU_EnableInterrupts(APP_DPU, 0, stream->intGroup0);
    DPU_EnableInterrupts(APP_DPU, 1, stream->intGroup1);
}

void APP_DPU_Display(void)
{
    dpu_display_timing_config_t displayTimingConfig;
    dpu_display_config_t displayConfig;

    /* Step 1: Initialize the content stream and safety stream. */
    APP_InitStream(&contentStream);
    APP_InitStream(&safetyStream);

    /* Step 2: Configure the display stream. */
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

    displayConfig.displayMode = kDPU_DisplayPrimOnTop;

    displayConfig.primAreaStartX = 1;
    displayConfig.primAreaStartY = 1;
#if APP_PORTRAIT
    displayConfig.secAreaStartX = 1;
    displayConfig.secAreaStartY = APP_STREAM_HEIGHT + 1;
#else
    displayConfig.secAreaStartX = APP_STREAM_WIDTH + 1;
    displayConfig.secAreaStartY = 1;
#endif

    DPU_SetDisplayConfig(APP_DPU, APP_DPU_DISPLAY_INDEX, &displayConfig);

    DPU_TriggerDisplayShadowLoad(APP_DPU, APP_DPU_DISPLAY_INDEX);

    /*
     * Initialize workflow:
     * 1. Init DPU
     * 2. Configure pixel link.
     * 3. Init and start display interface.
     * 4. Start DPU
     */
    APP_InitPixelLink();

    APP_StartDisplayInterface();

    DPU_StartDisplay(APP_DPU, APP_DPU_DISPLAY_INDEX);

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    PRG_EnableShadowLoad(safetyStream.prg, true);
    PRG_UpdateRegister(safetyStream.prg);
    DPR_StartRepeat(safetyStream.dpr);

    PRG_EnableShadowLoad(contentStream.prg, true);
    PRG_UpdateRegister(contentStream.prg);
    DPR_StartRepeat(contentStream.dpr);
#endif

    while (APP_IsStreamShadowPending(&safetyStream))
    {
    }
    while (APP_IsStreamShadowPending(&contentStream))
    {
    }
}

void APP_DPU_BlitBlend(void)
{
    dpu_fetch_unit_config_t fetchConfig;
    dpu_dst_buffer_config_t dbConfig;
    dpu_src_buffer_config_t sbConfig;
    dpu_blit_blend_config_t bbConfig;

    /* For the floating window. */
    int16_t offsetIncX = 1;
    int16_t offsetIncY = 1;
    uint16_t offsetX   = APP_FLOAT_WIN_INIT_OFFSET_X;
    uint16_t offsetY   = APP_FLOAT_WIN_INIT_OFFSET_Y;

    /* Pipeline initialize */
    DPU_InitPipeline(APP_DPU, kDPU_PipelineStore9);

    /* Store unit. */
    DPU_InitStore(APP_DPU, kDPU_Store9, DPU_MAKE_SRC_REG1(kDPU_UnitSrcBlitBlend9));

    DPU_DstBufferGetDefaultConfig(&dbConfig);
    dbConfig.baseAddr     = 0;
    dbConfig.strideBytes  = APP_STREAM_FB_STRIDE_BYTE;
    dbConfig.bitsPerPixel = 32U;
    dbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    dbConfig.bufferHeight = APP_STREAM_HEIGHT;
    dbConfig.bufferWidth  = APP_STREAM_WIDTH;

    DPU_SetStoreDstBufferConfig(APP_DPU, kDPU_Store9, &dbConfig);

    /* Blit blend. */
    DPU_InitBlitBlend(APP_DPU, kDPU_BlitBlend9, DPU_MAKE_SRC_REG2(kDPU_UnitSrcRop9, kDPU_UnitSrcFetchWarp9));

    DPU_BlitBlendGetDefaultConfig(&bbConfig);
    bbConfig.redBlendFuncSrc   = kDPU_BlitBlendFuncGlSrcColor;
    bbConfig.redBlendFuncDst   = kDPU_BlitBlendFuncGlDstColor;
    bbConfig.greenBlendFuncSrc = kDPU_BlitBlendFuncGlSrcColor;
    bbConfig.greenBlendFuncDst = kDPU_BlitBlendFuncGlDstColor;
    bbConfig.blueBlendFuncSrc  = kDPU_BlitBlendFuncGlSrcColor;
    bbConfig.blueBlendFuncDst  = kDPU_BlitBlendFuncGlDstColor;
    bbConfig.alphaBlendFuncSrc = kDPU_BlitBlendFuncGlSrcAlpha;
    bbConfig.alphaBlendFuncDst = kDPU_BlitBlendFuncGlDstAlpha;

    DPU_EnableBlitBlend(APP_DPU, kDPU_BlitBlend9, true);

    /* Rop */
    DPU_InitRop(APP_DPU, kDPU_Rop9, DPU_MAKE_SRC_REG3(kDPU_UnitSrcFetchDecode9, kDPU_UnitSrcNone, kDPU_UnitSrcNone));
    /* When the ROP unit disabled, only the primary input is output directly. */
    DPU_EnableRop(APP_DPU, kDPU_Rop9, false);

    /*
     * Configure the fetch units.
     *
     * The fetch warp 9 uses 4 sublayers to show the 4 windows.
     * The fetch decode 9 shows the float window.
     */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
    fetchConfig.frameHeight = APP_STREAM_HEIGHT;
    fetchConfig.frameWidth  = APP_STREAM_WIDTH;

    DPU_SrcBufferGetDefaultConfig(&sbConfig);
    sbConfig.bitsPerPixel = 32;
    sbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);
    sbConfig.strideBytes  = 4 * APP_WIN_WIDTH;
    sbConfig.bufferHeight = APP_WIN_HEIGHT;
    sbConfig.bufferWidth  = APP_WIN_WIDTH;

    /* Fetch decode 9 used for the float window. */
    DPU_InitFetchUnit(APP_DPU, kDPU_FetchDecode9, &fetchConfig);
    sbConfig.baseAddr = (uint32_t)s_floatWinFrameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchDecode9, 0, &sbConfig);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchDecode9, 0, true);

    /* Fetch warp 9 used for the fixed 4 windows. */
    DPU_InitFetchUnit(APP_DPU, kDPU_FetchWarp9, &fetchConfig);

    sbConfig.baseAddr = (uint32_t)s_redWinFrameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchWarp9, 0, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchWarp9, 0, APP_WIN0_OFFSET_X, APP_WIN0_OFFSET_Y);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchWarp9, 0, true);

    sbConfig.baseAddr = (uint32_t)s_greenWinFrameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchWarp9, 1, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchWarp9, 1, APP_WIN1_OFFSET_X, APP_WIN1_OFFSET_Y);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchWarp9, 1, true);

    sbConfig.baseAddr = (uint32_t)s_blueWinFrameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchWarp9, 2, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchWarp9, 2, APP_WIN2_OFFSET_X, APP_WIN2_OFFSET_Y);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchWarp9, 2, true);

    sbConfig.baseAddr = (uint32_t)s_whiteWinFrameBuffer;
    DPU_SetFetchUnitSrcBufferConfig(APP_DPU, kDPU_FetchWarp9, 3, &sbConfig);
    DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchWarp9, 3, APP_WIN3_OFFSET_X, APP_WIN3_OFFSET_Y);
    DPU_EnableFetchUnitSrcBuffer(APP_DPU, kDPU_FetchWarp9, 3, true);

    DPU_EnableInterrupts(APP_DPU, 0, APP_BLIT_SEQ_INT_GROUP0);
    DPU_EnableInterrupts(APP_DPU, 1, APP_BLIT_SEQ_INT_GROUP0);
    DPU_EnableInterrupts(APP_DPU, 0, APP_BLIT_SHD_LD_INT_GROUP0);
    DPU_EnableInterrupts(APP_DPU, 1, APP_BLIT_SHD_LD_INT_GROUP1);

    for (;;)
    {
        if (0U == offsetX)
        {
            offsetIncX = 1;
        }
        else if (APP_STREAM_WIDTH - APP_WIN_WIDTH - 1 <= offsetX)
        {
            offsetX    = APP_STREAM_WIDTH - APP_WIN_WIDTH - 1;
            offsetIncX = -1;
        }

        if (0U == offsetY)
        {
            offsetIncY = 1;
        }
        else if (APP_STREAM_HEIGHT - APP_WIN_HEIGHT - 1 <= offsetY)
        {
            offsetY    = APP_STREAM_HEIGHT - APP_WIN_HEIGHT - 1;
            offsetIncY = -1;
        }

        /* Update the format: offset. */
        offsetX += offsetIncX;
        offsetY += offsetIncY;

        DPU_SetFetchUnitOffset(APP_DPU, kDPU_FetchDecode9, 0, offsetX, offsetY);

        /* Output to the safety stream frame buffer. */
        DPU_SetStoreDstBufferAddr(APP_DPU, kDPU_Store9, APP_GetStreamInactiveFrameBuffer(&safetyStream));

        /* BlitBlend configure for safety stream. */
        bbConfig.redBlendMode   = kDPU_BlitBlendModeGlFuncAdd;
        bbConfig.greenBlendMode = kDPU_BlitBlendModeGlFuncAdd;
        bbConfig.blueBlendMode  = kDPU_BlitBlendModeGlFuncAdd;
        bbConfig.alphaBlendMode = kDPU_BlitBlendModeGlFuncAdd;

        DPU_SetBlitBlendConfig(APP_DPU, kDPU_BlitBlend9, &bbConfig);

        /* Pipeline configuration finished, start the process. */
        APP_TriggerAndStartBlitEngine();

        /* Wait for the shadow load. */
        while (APP_IsBlitEngineShadowPending())
        {
        }

        /* Output to the content stream frame buffer. */
        DPU_SetStoreDstBufferAddr(APP_DPU, kDPU_Store9, APP_GetStreamInactiveFrameBuffer(&contentStream));

        /* BlitBlend configure for content stream. */
        bbConfig.redBlendMode   = kDPU_BlitBlendModeGlFuncReverseSubtract;
        bbConfig.greenBlendMode = kDPU_BlitBlendModeGlFuncReverseSubtract;
        bbConfig.blueBlendMode  = kDPU_BlitBlendModeGlFuncReverseSubtract;
        bbConfig.alphaBlendMode = kDPU_BlitBlendModeGlFuncAdd;

        DPU_SetBlitBlendConfig(APP_DPU, kDPU_BlitBlend9, &bbConfig);

        /* Pipeline configuration finished, start the process. */
        APP_TriggerAndStartBlitEngine();

        /* To make sure the second blit completed, trigger the sequence complete interrupt. */
        APP_TriggerBlitEngineSeqComplete();

        while (!APP_IsBlitEngineSeqComplete())
        {
        }

        /* Display the new buffer. */
        APP_TriggerStreamFrameBufferSwitch(&safetyStream);
        APP_TriggerStreamFrameBufferSwitch(&contentStream);

        while (APP_IsStreamShadowPending(&safetyStream))
        {
        }
        while (APP_IsStreamShadowPending(&contentStream))
        {
        }
    }
}

void setUp(void)
{
}

void tearDown(void)
{
}

void DPU_IRQHandler(void)
{
    uint32_t intGroup0Flags, intGroup1Flags;
    intGroup0Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 0);
    intGroup1Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 1);

    APP_CheckAndUpdateStreamStatus(&safetyStream, intGroup0Flags, intGroup1Flags);
    APP_CheckAndUpdateStreamStatus(&contentStream, intGroup0Flags, intGroup1Flags);

    if ((intGroup0Flags & APP_BLIT_SEQ_INT_GROUP0) || (intGroup1Flags & APP_BLIT_SEQ_INT_GROUP1))
    {
        s_isBlitEngineSeqComplete = true;
    }

    if ((intGroup0Flags & APP_BLIT_SHD_LD_INT_GROUP0) || (intGroup1Flags & APP_BLIT_SHD_LD_INT_GROUP0))
    {
        s_isBlitEngineShadowPending = false;
    }

    DPU_ClearInterruptsPendingFlags(APP_DPU, 0, intGroup0Flags);
    DPU_ClearInterruptsPendingFlags(APP_DPU, 1, intGroup1Flags);
    __DSB();
}

/*!
 * @brief Main function
 */
int main(void)
{
    sc_ipc_t ipc;

    ipc = BOARD_InitRpc();
    BOARD_InitPins(ipc);
    BOARD_BootClockRUN();
    BOARD_PrepareDisplay();
    BOARD_InitMemory();
    BOARD_InitDebugConsole();

    PRINTF("DPU BlitBlend Example:\r\n");

    APP_InitFrameBuffer((uint32_t)s_redWinFrameBuffer, APP_WIN_HEIGHT, APP_WIN_WIDTH, sizeof(s_redWinFrameBuffer[0]),
                        APP_COLOR_RED);
    APP_InitFrameBuffer((uint32_t)s_blueWinFrameBuffer, APP_WIN_HEIGHT, APP_WIN_WIDTH, sizeof(s_blueWinFrameBuffer[0]),
                        APP_COLOR_BLUE);
    APP_InitFrameBuffer((uint32_t)s_greenWinFrameBuffer, APP_WIN_HEIGHT, APP_WIN_WIDTH,
                        sizeof(s_greenWinFrameBuffer[0]), APP_COLOR_GREEN);
    APP_InitFrameBuffer((uint32_t)s_whiteWinFrameBuffer, APP_WIN_HEIGHT, APP_WIN_WIDTH,
                        sizeof(s_whiteWinFrameBuffer[0]), APP_COLOR_WHITE);
    APP_InitFrameBuffer((uint32_t)s_floatWinFrameBuffer, APP_WIN_HEIGHT, APP_WIN_WIDTH,
                        sizeof(s_floatWinFrameBuffer[0]), APP_COLOR_YELLOW);

    memset(s_displayFrameBuffer, 0, ARRAY_SIZE(s_displayFrameBuffer));

    DPU_Init(APP_DPU);
    DPU_PreparePathConfig(APP_DPU);

    /* Start the display. */
    APP_DPU_Display();

    /* Start the blit engine to output frame for display. */
    APP_DPU_BlitBlend();

    while (1)
    {
    }
}
