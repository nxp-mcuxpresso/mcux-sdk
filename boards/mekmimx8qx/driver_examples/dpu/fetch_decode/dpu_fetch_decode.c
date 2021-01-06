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
 *************************************************************i*****************/


/* ARGB8888, 4 bytes per pixel. */
#define APP_BPP 4

/* Landscape or portrait. */
#if (APP_PANEL_WIDTH < APP_PANEL_HEIGHT)
#define APP_PORTRAIT 1
#else
#define APP_PORTRAIT 0
#endif

#if APP_PORTRAIT
#define APP_STREAM_WIDTH  (APP_PANEL_WIDTH)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT / 2)
#else
#define APP_STREAM_WIDTH  (APP_PANEL_WIDTH / 2)
#define APP_STREAM_HEIGHT (APP_PANEL_HEIGHT)
#endif

#define APP_SUBLAYER_WIDTH  160
#define APP_SUBLAYER_HEIGHT 120

#define APP_VIDEO_PLANE_WIDTH  (2 * APP_SUBLAYER_WIDTH)
#define APP_VIDEO_PLANE_HEIGHT (2 * APP_SUBLAYER_HEIGHT)

#define APP_STREAM_COUNT   2
#define APP_SUBLAYER_COUNT 1

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

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
#define APP_FB_ADDR_ALIGN_BYTE   DPU_FETCH_UNIT_BURST_SIZE
#define APP_FB_STRIDE_ALIGN_BYTE DPU_FETCH_UNIT_BURST_SIZE
#else
#define APP_FB_ADDR_ALIGN_BYTE   (32U)
#define APP_FB_STRIDE_ALIGN_BYTE APP_BPP
#endif

#define APP_FB_STRIDE_BYTE  (SDK_SIZEALIGN(APP_BPP * APP_SUBLAYER_WIDTH, APP_FB_STRIDE_ALIGN_BYTE))
#define APP_FB_STRIDE_PIXEL (APP_FB_STRIDE_BYTE / APP_BPP)

typedef void (*app_draw_func_t)(uint32_t *addr,
                                uint16_t startX,
                                uint16_t startY,
                                uint16_t width,
                                uint16_t height,
                                uint32_t color,
                                uint32_t strideWord);

typedef struct app_dpu_sublayer
{
    uint16_t offsetX;   /* Sublayer offset in the fetch unit output region. */
    uint16_t offsetY;   /* Sublayer offset in the fetch unit output region. */
    int16_t offsetIncX; /* Offset increase value when the frame update. */
    int16_t offsetIncY; /* Offset increase value when the frame update. */
    uint16_t height;    /* Height of the sublayer. */
    uint16_t width;     /* Width of the sublayer. */

    uint16_t strideBytes; /* Frame buffer stride. */

    uint32_t fbAddr[2]; /* Frame buffer address. */
    uint8_t fbIdx;      /* Active frame buffer index. */

    uint8_t sublayerIdx; /* Sublayer index in the fetch unit. */

    /*
     * These parameters are used to initialize the frame buffer.
     * The fbInitColor[0] is used to initialize fbAddr[0], the fbInitColor[1]
     * is used to initialize fbAddr[1].
     */
    app_draw_func_t fbInitFunc; /* Function to initialize frame buffer. */
    uint32_t fbInitColor[2];    /* Color used to initialize the frame buffer. */

} app_dpu_sublayer_t;

typedef struct app_dpu_stream
{
    /* General. */
    uint16_t height;
    uint16_t width;

    /* Fetch unit. */
    dpu_unit_t fetchUnit;
    app_dpu_sublayer_t *sublayers;
    uint8_t sublayerCount;
    uint16_t planeHeight;
    uint16_t planeWidth;

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Prefetch. */
    DPR_Type *dpr;
    PRG_Type *prg;
#endif

    /* Scaler unit. */
    dpu_unit_t vscaler;
    dpu_unit_t hscaler;
    uint8_t vscalerSrc;
    uint8_t hscalerSrc;

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


static void APP_DrawRectangle(uint32_t *addr,
                              uint16_t startX,
                              uint16_t startY,
                              uint16_t width,
                              uint16_t height,
                              uint32_t color,
                              uint32_t strideWord);

/*******************************************************************************
 * Variables
 ******************************************************************************/

AT_NONCACHEABLE_SECTION_ALIGN(
    uint32_t s_frameBuffers[APP_STREAM_COUNT][APP_SUBLAYER_COUNT][2][APP_SUBLAYER_HEIGHT][APP_FB_STRIDE_PIXEL], 32);

app_dpu_sublayer_t safetySreamSublayer[] = {
    /* When prefetch enabled, the DPU fetch unit could not fetch
     * multiple sublayers, so there should be only one sublayer here.
     */
    /* sublayer 0 */
    {
        .offsetX     = 0,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .strideBytes = APP_FB_STRIDE_BYTE,
        .fbAddr      = {(uint32_t)s_frameBuffers[0][0][0], (uint32_t)s_frameBuffers[0][0][1]},
        .fbIdx       = 0,
        .sublayerIdx = 0,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_BLUE, APP_COLOR_GREEN},
    },
};

app_dpu_stream_t safetyStream = {
    /* General. */
    .height = APP_STREAM_HEIGHT,
    .width  = APP_STREAM_WIDTH,

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Prefetch. */
    .dpr = APP_FETCH_DECODE1_DPR,
    .prg = APP_FETCH_DECODE1_PRG,
#endif

    /* Fetch unit. */
    .fetchUnit     = kDPU_FetchDecode1,
    .sublayers     = safetySreamSublayer,
    .sublayerCount = ARRAY_SIZE(safetySreamSublayer),
    .planeHeight   = APP_VIDEO_PLANE_HEIGHT,
    .planeWidth    = APP_VIDEO_PLANE_WIDTH,

    /*
     * Scaler unit.
     * For up-scaling horizontally, the path is ->VSCALER -> HSCALER ->
     * For Down-scaling horizontally, the path is ->HSCALER -> VSCALER ->
     */
    .vscaler = kDPU_Vscaler5,
    .hscaler = kDPU_Hscaler5,
#if (APP_VIDEO_PLANE_WIDTH > APP_STREAM_WIDTH)
    .vscalerSrc = kDPU_UnitSrcHScaler5,
    .hscalerSrc = kDPU_UnitSrcFetchDecode1,
#else
    .vscalerSrc       = kDPU_UnitSrcFetchDecode1,
    .hscalerSrc       = kDPU_UnitSrcVScaler5,
#endif

    /* Const frame. */
    .constFrame = kDPU_ConstFrame4,
    .constColor = DPU_MAKE_CONST_COLOR(0x00, 0x00, 0x00, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend2,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame4,
#if (APP_VIDEO_PLANE_WIDTH > APP_STREAM_WIDTH)
    .layerBlendSecSrc = kDPU_UnitSrcVScaler5,
#else
    .layerBlendSecSrc = kDPU_UnitSrcHScaler5,
#endif

    /* Ext Dst. */
    .extDst    = APP_SAFETY_STREAM_EXTDST,
    .extDstSrc = kDPU_UnitSrcLayerBlend2,

    /* Pipeline. */
    .pipeline = APP_SAFETY_STREAM_PIPELINE,

    /* Interrupt. */
    .intGroup0 = APP_SAFETY_STREAM_INT_GROUP0,
    .intGroup1 = APP_SAFETY_STREAM_INT_GROUP1,
};

app_dpu_sublayer_t contentSreamSublayer[] = {
    /* When prefetch enabled, the DPU fetch unit could not fetch
     * multiple sublayers, so there should be only one sublayer here.
     */
    /* sublayer 0 */
    {
        .offsetX     = 0,
        .offsetY     = 0,
        .offsetIncX  = 1,
        .offsetIncY  = 1,
        .height      = APP_SUBLAYER_HEIGHT,
        .width       = APP_SUBLAYER_WIDTH,
        .strideBytes = APP_FB_STRIDE_BYTE,
        .fbAddr      = {(uint32_t)s_frameBuffers[1][0][0], (uint32_t)s_frameBuffers[1][0][1]},
        .fbIdx       = 0,
        .sublayerIdx = 0,
        .fbInitFunc  = APP_DrawRectangle,
        .fbInitColor = {APP_COLOR_RED, APP_COLOR_YELLOW},
    },
};

app_dpu_stream_t contentStream = {
    /* General. */
    .height = APP_STREAM_HEIGHT,
    .width  = APP_STREAM_WIDTH,

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Prefetch. */
    .dpr = APP_FETCH_DECODE0_DPR,
    .prg = APP_FETCH_DECODE0_PRG,
#endif

    /* Fetch unit. */
    .fetchUnit     = kDPU_FetchDecode0,
    .sublayers     = contentSreamSublayer,
    .sublayerCount = ARRAY_SIZE(contentSreamSublayer),
    .planeHeight   = APP_VIDEO_PLANE_HEIGHT,
    .planeWidth    = APP_VIDEO_PLANE_WIDTH,

    /*
     * Scaler unit.
     * For up-scaling horizontally, the path is ->VSCALER -> HSCALER ->
     * For Down-scaling horizontally, the path is ->HSCALER -> VSCALER ->
     */
    .vscaler = kDPU_Vscaler4,
    .hscaler = kDPU_Hscaler4,
#if (APP_VIDEO_PLANE_WIDTH > APP_STREAM_WIDTH)
    .vscalerSrc = kDPU_UnitSrcHScaler4,
    .hscalerSrc = kDPU_UnitSrcFetchDecode0,
#else
    .vscalerSrc       = kDPU_UnitSrcFetchDecode0,
    .hscalerSrc       = kDPU_UnitSrcVScaler4,
#endif

    /* Const frame. */
    .constFrame = kDPU_ConstFrame0,
    .constColor = DPU_MAKE_CONST_COLOR(0xFF, 0xFF, 0xFF, 0xFF),

    /* Layer blend. */
    .layerBlend        = kDPU_LayerBlend0,
    .layerBlendPrimSrc = kDPU_UnitSrcConstFrame0,
#if (APP_VIDEO_PLANE_WIDTH > APP_STREAM_WIDTH)
    .layerBlendSecSrc = kDPU_UnitSrcVScaler4,
#else
    .layerBlendSecSrc = kDPU_UnitSrcHScaler4,
#endif

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
bool APP_IsStreamShadowPending(app_dpu_stream_t *stream)
{
    return stream->isShadowLoadPending;
}

void APP_TriggerStreamShadowLoad(app_dpu_stream_t *stream)
{
    /* Trigger the shadow load. */
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

void APP_UpdateSublayer(app_dpu_stream_t *stream,
                        app_dpu_sublayer_t *sublayer,
                        uint16_t planeHeight,
                        uint16_t planeWidth,
                        dpu_unit_t fetchUnit)
{
    /* Switch to use the other frame buffer or not. */
    bool fbSwitch = false;
    uint32_t newBufferAddr;

    if (0U == sublayer->offsetX)
    {
        sublayer->offsetIncX = 1;
        fbSwitch             = true;
    }
    else if (planeWidth - sublayer->width - 1 <= sublayer->offsetX)
    {
        sublayer->offsetX    = planeWidth - sublayer->width - 1;
        sublayer->offsetIncX = -1;
        fbSwitch             = true;
    }

    if (0U == sublayer->offsetY)
    {
        sublayer->offsetIncY = 1;
        fbSwitch             = true;
    }
    else if (planeHeight - sublayer->height - 1 <= sublayer->offsetY)
    {
        sublayer->offsetY    = planeHeight - sublayer->height - 1;
        sublayer->offsetIncY = -1;
        fbSwitch             = true;
    }

    if (fbSwitch)
    {
        sublayer->fbIdx ^= 1;
        newBufferAddr = (uint32_t)sublayer->fbAddr[sublayer->fbIdx];

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
        DPR_SetBufferAddr(stream->dpr, newBufferAddr);

        PRG_SetBufferAddr(stream->prg, newBufferAddr);

        PRG_UpdateRegister(stream->prg);
#endif

        DPU_SetFetchUnitSrcBufferAddr(APP_DPU, fetchUnit, sublayer->sublayerIdx, newBufferAddr);
    }

    /* Update the format: color and offset. */
    sublayer->offsetX += sublayer->offsetIncX;
    sublayer->offsetY += sublayer->offsetIncY;

    DPU_SetFetchUnitOffset(APP_DPU, fetchUnit, sublayer->sublayerIdx, sublayer->offsetX, sublayer->offsetY);
}

void APP_UpdateStream(app_dpu_stream_t *stream)
{
    uint8_t sublayerIdx;

    if (!APP_IsStreamShadowPending(stream))
    {
        for (sublayerIdx = 0; sublayerIdx < stream->sublayerCount; sublayerIdx++)
        {
            APP_UpdateSublayer(stream, &(stream->sublayers[sublayerIdx]), stream->planeHeight, stream->planeWidth,
                               stream->fetchUnit);
        }

        APP_TriggerStreamShadowLoad(stream);
    }
}

void APP_InitFrameBuffer(app_dpu_sublayer_t *sublayer)
{
    sublayer->fbIdx = 0;
    sublayer->fbInitFunc((uint32_t *)sublayer->fbAddr[0], 0, 0, sublayer->width, sublayer->height,
                         sublayer->fbInitColor[0], sublayer->width);
    sublayer->fbInitFunc((uint32_t *)sublayer->fbAddr[1], 0, 0, sublayer->width, sublayer->height,
                         sublayer->fbInitColor[1], sublayer->width);
}

void APP_InitStream(app_dpu_stream_t *stream)
{
    dpu_const_frame_config_t cfConfig;
    dpu_layer_blend_config_t lbConfig;
    dpu_fetch_unit_config_t fetchConfig;
    dpu_src_buffer_config_t sbConfig;
    dpu_scaler_config_t scConfig;

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
    lbConfig.constAlpha         = 32;
    lbConfig.primColorBlendMode = kDPU_BlendConstAlpha;
    lbConfig.secColorBlendMode  = kDPU_BlendConstAlphaInv;
    DPU_SetLayerBlendConfig(APP_DPU, stream->layerBlend, &lbConfig);
    DPU_EnableLayerBlend(APP_DPU, stream->layerBlend, true);

    /* Const frame. */
    cfConfig.frameWidth  = stream->width;
    cfConfig.frameHeight = stream->height;
    cfConfig.constColor  = stream->constColor;

    DPU_InitConstFrame(APP_DPU, stream->constFrame);
    DPU_SetConstFrameConfig(APP_DPU, stream->constFrame, &cfConfig);

    /* Scaler. */
    DPU_ScalerGetDefaultConfig(&scConfig);

    DPU_InitScaler(APP_DPU, stream->hscaler);
    scConfig.srcReg     = DPU_MAKE_SRC_REG1(stream->hscalerSrc);
    scConfig.inputSize  = stream->planeWidth;
    scConfig.outputSize = stream->width;
    DPU_SetScalerConfig(APP_DPU, stream->hscaler, &scConfig);

    DPU_InitScaler(APP_DPU, stream->vscaler);
    scConfig.srcReg     = DPU_MAKE_SRC_REG1(stream->vscalerSrc);
    scConfig.inputSize  = stream->planeHeight;
    scConfig.outputSize = stream->height;
    DPU_SetScalerConfig(APP_DPU, stream->vscaler, &scConfig);

    /* Fetch unit. */
    DPU_FetchUnitGetDefaultConfig(&fetchConfig);
    fetchConfig.frameHeight = stream->planeHeight;
    fetchConfig.frameWidth  = stream->planeWidth;
    DPU_InitFetchUnit(APP_DPU, stream->fetchUnit, &fetchConfig);

    DPU_SrcBufferGetDefaultConfig(&sbConfig);

    sbConfig.strideBytes  = APP_FB_STRIDE_BYTE;
    sbConfig.bitsPerPixel = 32;
    sbConfig.pixelFormat  = kDPU_PixelFormatARGB8888;
    sbConfig.bufferHeight = APP_SUBLAYER_HEIGHT;
    sbConfig.bufferWidth  = APP_SUBLAYER_WIDTH;
    sbConfig.constColor   = DPU_MAKE_CONST_COLOR(0, 0, 0, 0);

    /* When prefetch enabled, the DPU fetch unit could not fetch
     * multiple sublayers, so there should be only one sublayer here.
     */
    for (uint8_t i = 0; i < stream->sublayerCount; i++)
    {
        sbConfig.baseAddr = stream->sublayers[i].fbAddr[0];

        APP_InitFrameBuffer(&stream->sublayers[i]);
        DPU_SetFetchUnitSrcBufferConfig(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx, &sbConfig);
        DPU_SetFetchUnitOffset(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx,
                               stream->sublayers[i].offsetX, stream->sublayers[i].offsetY);
        DPU_EnableFetchUnitSrcBuffer(APP_DPU, stream->fetchUnit, stream->sublayers[i].sublayerIdx, true);
    }

#if (defined(APP_DPU_USE_PREFETCH) && APP_DPU_USE_PREFETCH)
    /* Configure PRG. */
    PRG_BufferGetDefaultConfig(&prgConfig);
    prgConfig.width       = sbConfig.bufferWidth;
    prgConfig.height      = sbConfig.bufferHeight;
    prgConfig.strideBytes = sbConfig.strideBytes;
    prgConfig.dataType    = kPRG_DataType32Bpp;

    PRG_Init(stream->prg);
    PRG_SetBufferConfig(stream->prg, &prgConfig);
    PRG_SetBufferAddr(stream->prg, sbConfig.baseAddr);
    PRG_Enable(stream->prg, true);
    PRG_UpdateRegister(stream->prg);

    /* Configure DPR. */
    DPR_BufferGetDefaultConfig(&dprConfig);
    dprConfig.width       = sbConfig.bufferWidth;
    dprConfig.height      = sbConfig.bufferHeight;
    dprConfig.strideBytes = sbConfig.strideBytes;
    dprConfig.dataType    = kDPR_DataType32Bpp;

    DPR_Init(stream->dpr);
    DPR_SetBufferConfig(stream->dpr, &dprConfig);
    DPR_SetBufferAddr(stream->dpr, sbConfig.baseAddr);
    DPR_Start(stream->dpr);
#endif

    /* Trigger the pipeline. */
    APP_TriggerStreamShadowLoad(stream);

    /* Enable stream shadow load interrupt. */
    DPU_EnableInterrupts(APP_DPU, 0, stream->intGroup0);
    DPU_EnableInterrupts(APP_DPU, 1, stream->intGroup1);
}

static void APP_DrawRectangle(uint32_t *addr,
                              uint16_t startX,
                              uint16_t startY,
                              uint16_t width,
                              uint16_t height,
                              uint32_t color,
                              uint32_t strideWord)
{
    uint16_t x, y;

    for (y = startY; y < startY + height; y++)
    {
        for (x = startX; x < startX + width; x++)
        {
            *(addr + strideWord * y + x) = color;
        }
    }
}

void APP_DPU_FetchDecode(void)
{
    dpu_display_timing_config_t displayTimingConfig;
    dpu_display_config_t displayConfig;

    DPU_Init(APP_DPU);

    DPU_PreparePathConfig(APP_DPU);

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

    displayConfig.secAreaStartX = 1;
    displayConfig.secAreaStartY = 1;

#if APP_PORTRAIT
    displayConfig.primAreaStartX = 1;
    displayConfig.primAreaStartY = APP_STREAM_HEIGHT + 1;
#else
    displayConfig.primAreaStartX = APP_STREAM_WIDTH + 1;
    displayConfig.primAreaStartY = 1;
#endif

    APP_InitStream(&safetyStream);
    APP_InitStream(&contentStream);

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
}

void DPU_IRQHandler(void)
{
    uint32_t intGroup0Flags, intGroup1Flags;
    intGroup0Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 0);
    intGroup1Flags = DPU_GetInterruptsPendingFlags(APP_DPU, 1);

    APP_CheckAndUpdateStreamStatus(&safetyStream, intGroup0Flags, intGroup1Flags);
    APP_CheckAndUpdateStreamStatus(&contentStream, intGroup0Flags, intGroup1Flags);

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
    PRINTF("DPU Decode Example:\r\n");

    /* Start the DPU. */
    APP_DPU_FetchDecode();

    /* Run and update the display content */
    while (1)
    {
        APP_UpdateStream(&safetyStream);
        APP_UpdateStream(&contentStream);
    }
}
