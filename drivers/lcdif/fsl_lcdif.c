/*
 * Copyright (c) 2019-2021,2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdif"
#endif

#if defined(LCDIF_RSTS)
#define LCDIF_RESETS_ARRAY LCDIF_RSTS
#elif defined(DCNANO_RSTS)
#define LCDIF_RESETS_ARRAY DCNANO_RSTS
#endif

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
typedef union
{
    lcdif_layer_alpha_blend_config_t _alphaConfig;
    uint32_t _u32;
} lcdif_reg32_convert_t;
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * brief Get the instance from the base address
 *
 * param base LCDIF peripheral base address
 *
 * return The LCDIF module instance
 */
static uint32_t LCDIF_GetInstance(LCDIF_Type *base);

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*!
 * brief Gets the layer config register value
 *
 * param config Pointer to the configuration structure.
 *
 * return The value for layer configuration register.
 */
static uint32_t LCDIF_GetLayerConfig(const lcdif_fb_config_t *config);
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! brief Pointers to LCDIF bases for each instance. */
static LCDIF_Type *const s_lcdifBases[] = LCDIF_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! brief Pointers to LCDIF clocks for each LCDIF submodule. */
static const clock_ip_name_t s_lcdifClocks[] = LCDIF_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(LCDIF_RESETS_ARRAY)
/* Reset array */
static const reset_ip_name_t s_lcdifResets[] = LCDIF_RESETS_ARRAY;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t LCDIF_GetInstance(LCDIF_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdifBases); instance++)
    {
        if (MSDK_REG_SECURE_ADDR(s_lcdifBases[instance]) == MSDK_REG_SECURE_ADDR(base))
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdifBases));

    return instance;
}

/*!
 * brief Initialize the LCDIF.
 *
 * This function initializes the LCDIF to work.
 *
 * param base LCDIF peripheral base address.
 *
 * retval kStatus_Success Initialize successfully.
 */
status_t LCDIF_Init(LCDIF_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIF_GetInstance(base);
    CLOCK_EnableClock(s_lcdifClocks[instance]);
#endif

#if defined(LCDIF_RESETS_ARRAY)
    RESET_ReleasePeripheralReset(s_lcdifResets[LCDIF_GetInstance(base)]);
#endif

    base->FRAMEBUFFERCONFIG0 = 0;
    /* Clear interrupt status and disable interrupt. */
    base->DISPLAYINTRENABLE = 0;
    (void)(base->DISPLAYINTR);

    return kStatus_Success;
}

/*!
 * brief De-initialize the LCDIF.
 *
 * This function disables the LCDIF peripheral clock.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIF_Deinit(LCDIF_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIF_GetInstance(base);
    CLOCK_DisableClock(s_lcdifClocks[instance]);
#endif
}

/*!
 * brief Get the default configuration for to initialize the LCDIF DPI mode.
 *
 * The default configuration value is:
 *
 * code
 * config->panelWidth = 0;
 * config->panelHeight = 0;
 * config->hsw = 0;
 * config->hfp = 0;
 * config->hbp = 0;
 * config->vsw = 0;
 * config->vfp = 0;
 * config->vbp = 0;
 * config->polarityFlags = kLCDIF_VsyncActiveLow | kLCDIF_HsyncActiveLow | kLCDIF_DataEnableActiveHigh |
 * kLCDIF_DriveDataOnFallingClkEdge; config->format = kLCDIF_Output24Bit;
 * endcode
 *
 * param config Pointer to the LCDIF DPI configuration.
 */
void LCDIF_DpiModeGetDefaultConfig(lcdif_dpi_config_t *config)
{
    assert(NULL != config);

    (void)memset(config, 0, sizeof(*config));

    config->panelWidth    = 0;
    config->panelHeight   = 0;
    config->hsw           = 0;
    config->hfp           = 0;
    config->hbp           = 0;
    config->vsw           = 0;
    config->vfp           = 0;
    config->vbp           = 0;
    config->polarityFlags = (uint32_t)kLCDIF_VsyncActiveLow | (uint32_t)kLCDIF_HsyncActiveLow |
                            (uint32_t)kLCDIF_DataEnableActiveHigh | (uint32_t)kLCDIF_DriveDataOnFallingClkEdge;
    config->format = kLCDIF_Output24Bit;
}

/*!
 * @brief Initialize the LCDIF to work in DPI mode.
 *
 * This function configures the LCDIF DPI display.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 *
 * retval kStatus_Success Initialize successfully.
 * retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t LCDIF_DpiModeSetConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dpi_config_t *config)
{
    assert(NULL != config);

    uint32_t regHsync;
    uint32_t regVsync;
    uint32_t regPanelConfig;

    /* Reset the frame buffer. */
    base->FRAMEBUFFERCONFIG0 = 0;

    /* Change to DPI mode. */
    base->DBICONFIG0 &= ~LCDIF_DBICONFIG0_BUS_OUTPUT_SEL_MASK;

    base->DPICONFIG0 = (uint32_t)config->format;

    base->HDISPLAY0 =
        ((uint32_t)config->panelWidth << LCDIF_HDISPLAY0_DISPLAY_END_SHIFT) |
        (((uint32_t)config->panelWidth + config->hsw + config->hfp + config->hbp) << LCDIF_HDISPLAY0_TOTAL_SHIFT);

    base->VDISPLAY0 =
        ((uint32_t)config->panelHeight << LCDIF_VDISPLAY0_DISPLAY_END_SHIFT) |
        (((uint32_t)config->panelHeight + config->vsw + config->vfp + config->vbp) << LCDIF_VDISPLAY0_TOTAL_SHIFT);

    /* HSYNC */
    regHsync = (((uint32_t)config->panelWidth + config->hfp) << LCDIF_HSYNC0_START_SHIFT) |
               (((uint32_t)config->panelWidth + config->hfp + config->hsw) << LCDIF_HSYNC0_END_SHIFT) |
               LCDIF_HSYNC0_PULSE_MASK;

    if ((uint32_t)kLCDIF_HsyncActiveHigh != (config->polarityFlags & (uint32_t)kLCDIF_HsyncActiveHigh))
    {
        regHsync |= LCDIF_HSYNC0_POLARITY_MASK;
    }

    base->HSYNC0 = regHsync;

    /* VSYNC */
    regVsync = (((uint32_t)config->panelHeight + config->vfp) << LCDIF_VSYNC0_START_SHIFT) |
               (((uint32_t)config->panelHeight + config->vfp + config->vsw) << LCDIF_VSYNC0_END_SHIFT) |
               LCDIF_VSYNC0_PULSE_MASK;

    if ((uint32_t)kLCDIF_VsyncActiveHigh != (config->polarityFlags & (uint32_t)kLCDIF_VsyncActiveHigh))
    {
        regVsync |= LCDIF_VSYNC0_POLARITY_MASK;
    }

    base->VSYNC0 = regVsync;

    /* DE, Data, clock. */
    regPanelConfig = LCDIF_PANELCONFIG0_DE_MASK | LCDIF_PANELCONFIG0_CLOCK_MASK;

    if ((uint32_t)kLCDIF_DataEnableActiveHigh != ((uint32_t)kLCDIF_DataEnableActiveHigh & config->polarityFlags))
    {
        regPanelConfig |= LCDIF_PANELCONFIG0_DE_POLARITY_MASK;
    }

    if ((uint32_t)kLCDIF_DriveDataOnRisingClkEdge ==
        ((uint32_t)kLCDIF_DriveDataOnRisingClkEdge & config->polarityFlags))
    {
        regPanelConfig |= LCDIF_PANELCONFIG0_CLOCK_POLARITY_MASK;
    }

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
    base->PANELCONFIG0 = regPanelConfig;
#else
    base->PANELCONFIG0 = regPanelConfig | LCDIF_PANELCONFIG0_SEQUENCING_MASK;
#endif
    return kStatus_Success;
}

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*!
 * @brief Gets default frame buffer configuration.
 *
 * Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version. Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to get the default configuration for all the 3 layers.
 *
 * @param config Pointer to the configuration structure.
 */
void LCDIF_FrameBufferGetDefaultConfig(lcdif_fb_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->enable         = true;
    config->rotateFlipMode = kLCDIF_Rotate0;
    config->inOrder        = kLCDIF_PixelInputOrderARGB;
    config->format         = kLCDIF_PixelFormatRGB565;
    config->standard       = kLCDIF_ConvertBT601;

    /* kLCDIF_PorterDuffSrc */
    config->alpha.srcAlphaMode       = kLCDIF_AlphaStraight;
    config->alpha.srcGlobalAlphaMode = kLCDIF_AlphaLocal;
    config->alpha.srcFactorMode      = kLCDIF_AlphaFactorOne;
    config->alpha.useSrcAlpha        = (uint32_t) true;
    config->alpha.dstAlphaMode       = kLCDIF_AlphaStraight;
    config->alpha.dstGlobalAlphaMode = kLCDIF_AlphaLocal;
    config->alpha.dstFactorMode      = kLCDIF_AlphaFactorZero;
    config->alpha.useDstAlpha        = (uint32_t) true;
}

static uint32_t LCDIF_GetLayerConfig(const lcdif_fb_config_t *config)
{
    return LCDIF_FRAMEBUFFERCONFIG0_ROT_ANGLE(config->rotateFlipMode) |
           LCDIF_FRAMEBUFFERCONFIG0_UV_SWIZZLE(config->enableUVSwizzle) |
           LCDIF_FRAMEBUFFERCONFIG0_SWIZZLE(config->inOrder) |
           LCDIF_FRAMEBUFFERCONFIG0_COLOR_KEY_EN(config->colorkey.enable) |
           LCDIF_FRAMEBUFFERCONFIG0_ENABLE((uint32_t)config->enable) | ((uint32_t)config->format & 0x7UL);
}

/*!
 * brief Configure the video layer for LCDIF frame buffer.
 *
 * Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version. Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to configure the legacy video layer, and use @ref LCDIF_SetOverlayLayerConfig to configure the overlay layers.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 */
void LCDIF_SetFrameBufferConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_fb_config_t *config)
{
    assert(NULL != config);

    lcdif_reg32_convert_t pid;
    pid._alphaConfig = config->alpha;

    base->LAYERCLOCKGATE = (base->LAYERCLOCKGATE & (~LCDIF_LAYERCLOCKGATE_DISABLE_VIDEO_CLK_MASK)) |
                           LCDIF_LAYERCLOCKGATE_DISABLE_VIDEO_CLK(!config->enable);
    base->FRAMEBUFFERCONFIG0    = LCDIF_GetLayerConfig(config);
    base->FRAMEBUFFERCLEARVALUE = config->clearValue;
    base->VIDEOTL               = LCDIF_VIDEOTL_X(config->topLeftX) | LCDIF_VIDEOTL_Y(config->topLeftY);
    base->FRAMEBUFFERSIZE = LCDIF_FRAMEBUFFERSIZE_WIDTH(config->width) | LCDIF_FRAMEBUFFERSIZE_HEIGHT(config->height);
    base->FRAMEBUFFERCOLORKEY     = config->colorkey.lowValue;
    base->FRAMEBUFFERCOLORKEYHIGH = config->colorkey.highValue;
    base->VIDEOGLOBALALPHA        = (uint32_t)(pid._u32 >> 16U);
    base->VIDEOALPHABLENDCONFIG   = (pid._u32 & 0xFFFFUL);
    base->DCTILEINCFG0 = ((uint32_t)config->format >> 3U) | LCDIF_DCTILEINCFG0_YUV_STANDARD((uint32_t)config->standard);
}

/*!
 * brief Configure the video layer position.
 *
 * Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version. Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to configure the legacy video layer, and use @ref LCDIF_SetOverlayLayerPosition to configure the overlay layers.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param topLeftX The x value of thr top-left coordinate.
 * param topLeftY The y value of thr top-left coordinate.
 * param width The width of the layer.
 * param height The height of the layer.
 */
void LCDIF_SetFrameBufferPosition(
    LCDIF_Type *base, uint8_t displayIndex, uint16_t topLeftX, uint16_t topLeftY, uint16_t width, uint16_t height)
{
    base->VIDEOTL         = LCDIF_VIDEOTL_X(topLeftX) | LCDIF_VIDEOTL_Y(topLeftY);
    base->FRAMEBUFFERSIZE = LCDIF_FRAMEBUFFERSIZE_WIDTH(width) | LCDIF_FRAMEBUFFERSIZE_HEIGHT(height);
}

/*!
 * brief Configure the overlay layers for LCDIF frame buffer.
 *
 * Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version. Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to configure the overlay layers, and use @ref LCDIF_SetFrameBufferConfig to configure the legacy video layer.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 * param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerConfig(LCDIF_Type *base,
                                 uint8_t displayIndex,
                                 const lcdif_fb_config_t *config,
                                 uint8_t layerIndex)
{
    assert(NULL != config);

    lcdif_reg32_convert_t pid;
    pid._alphaConfig = config->alpha;

    switch (layerIndex)
    {
        case 0U:
            base->OVERLAYCONFIG     = LCDIF_GetLayerConfig(config);
            base->OVERLAYCLEARVALUE = config->clearValue;
            base->LAYERCLOCKGATE    = (base->LAYERCLOCKGATE & (~LCDIF_LAYERCLOCKGATE_DISABLE_OVERLAY0_CLK_MASK)) |
                                   LCDIF_LAYERCLOCKGATE_DISABLE_OVERLAY0_CLK(!config->enable);
            base->OVERLAYTL       = LCDIF_OVERLAYTL_X(config->topLeftX) | LCDIF_OVERLAYTL_Y(config->topLeftY);
            base->OVERLAYSIZE     = LCDIF_OVERLAYSIZE_WIDTH(config->width) | LCDIF_OVERLAYSIZE_HEIGHT(config->height);
            base->OVERLAYCOLORKEY = config->colorkey.lowValue;
            base->OVERLAYCOLORKEYHIGH     = config->colorkey.highValue;
            base->OVERLAYGLOBALALPHA      = (uint32_t)(pid._u32 >> 16U);
            base->OVERLAYALPHABLENDCONFIG = (pid._u32 & 0xFFFFUL);
            base->DCOVERLAYTILEINCFG =
                ((uint32_t)config->format >> 3U) | LCDIF_DCTILEINCFG0_YUV_STANDARD((uint32_t)config->standard);
            break;

        case 1U:
            base->OVERLAYCONFIG1    = LCDIF_GetLayerConfig(config);
            base->OVERLAYCLEARVALUE = config->clearValue;
            base->LAYERCLOCKGATE    = (base->LAYERCLOCKGATE & (~LCDIF_LAYERCLOCKGATE_DISABLE_OVERLAY1_CLK_MASK)) |
                                   LCDIF_LAYERCLOCKGATE_DISABLE_OVERLAY1_CLK(!config->enable);
            base->OVERLAYTL1       = LCDIF_OVERLAYTL_X(config->topLeftX) | LCDIF_OVERLAYTL_Y(config->topLeftY);
            base->OVERLAYSIZE1     = LCDIF_OVERLAYSIZE_WIDTH(config->width) | LCDIF_OVERLAYSIZE_HEIGHT(config->height);
            base->OVERLAYCOLORKEY1 = config->colorkey.lowValue;
            base->OVERLAYCOLORKEYHIGH1     = config->colorkey.highValue;
            base->OVERLAYGLOBALALPHA1      = (uint32_t)(pid._u32 >> 16U);
            base->OVERLAYALPHABLENDCONFIG1 = (pid._u32 & 0xFFFFUL);
            break;

        default:
            /* Only 2 overlay layers. */
            assert(false);
            break;
    }
}

/*!
 * brief Configure the overlay layer position.
 *
 * Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version. Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to configure the overlay layers, and use @ref LCDIF_SetFrameBufferPosition to configure the legacy video layer.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param topLeftX The x value of thr top-left coordinate.
 * param topLeftY The y value of thr top-left coordinate.
 * param width The width of the layer.
 * param height The height of the layer.
 * param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerPosition(LCDIF_Type *base,
                                   uint8_t displayIndex,
                                   uint16_t topLeftX,
                                   uint16_t topLeftY,
                                   uint16_t width,
                                   uint16_t height,
                                   uint8_t layerIndex)
{
    switch (layerIndex)
    {
        case 0U:
            base->OVERLAYTL   = LCDIF_OVERLAYTL_X(topLeftX) | LCDIF_OVERLAYTL_Y(topLeftY);
            base->OVERLAYSIZE = LCDIF_OVERLAYSIZE_WIDTH(width) | LCDIF_OVERLAYSIZE_HEIGHT(height);
            break;

        case 1U:
            base->OVERLAYTL1   = LCDIF_OVERLAYTL_X(topLeftX) | LCDIF_OVERLAYTL_Y(topLeftY);
            base->OVERLAYSIZE1 = LCDIF_OVERLAYSIZE_WIDTH(width) | LCDIF_OVERLAYSIZE_HEIGHT(height);
            break;

        default:
            /* Only 2 overlay layers. */
            assert(false);
            break;
    }
}

/*!
 * brief Get the alpha blend configuration by porter duff blend mode.
 *
 * param mode The blend mode.
 * param config Pointer to the configuration.
 * retval kStatus_Success Successfully get the configuration.
 * retval kStatus_InvalidArgument The blend mode not supported.
 */
status_t LCDIF_GetPorterDuffConfig(lcdif_porter_duff_blend_mode_t mode, lcdif_layer_alpha_blend_config_t *config)
{
    status_t status;

    lcdif_reg32_convert_t pid;

    static const uint32_t pdCtrl[] = {
        /* kLCDIF_PorterDuffSrc */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorOne) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorZero),

        /* kLCDIF_PorterDuffAtop */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorStraight) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorInversed),

        /* kLCDIF_PorterDuffOver */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorOne) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorInversed),

        /* kLCDIF_PorterDuffIn */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorStraight) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorZero),

        /* kLCDIF_PorterDuffOut */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorInversed) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorZero),

        /* kLCDIF_PorterDuffDst */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorZero) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorOne),

        /* kLCDIF_PorterDuffDstAtop */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorInversed) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorStraight),

        /* kLCDIF_PorterDuffDstOver */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorInversed) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorOne),

        /* kLCDIF_PorterDuffDstIn */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorZero) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorStraight),

        /* kLCDIF_PorterDuffDstOut */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorZero) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorInversed),

        /* kLCDIF_PorterDuffPlus */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorOne) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorOne),

        /* kLCDIF_PorterDuffXor */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorInversed) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorInversed),

        /* kLCDIF_PorterDuffClear */
        LCDIF_VIDEOALPHABLENDCONFIG_ALPHA_BLEND_MASK |
            LCDIF_VIDEOALPHABLENDCONFIG_SRC_BLENDING_MODE(kLCDIF_AlphaFactorZero) |
            LCDIF_VIDEOALPHABLENDCONFIG_DST_BLENDING_MODE(kLCDIF_AlphaFactorZero),
    };

    if (mode >= kLCDIF_PorterDuffMax)
    {
        status = kStatus_InvalidArgument;
    }
    else
    {
        pid._u32 = pdCtrl[(uint32_t)mode] |
                   LCDIF_VIDEOALPHABLENDCONFIG_SRC_GLOBAL_ALPHA_MODE((uint32_t)kLCDIF_AlphaLocal) |
                   LCDIF_VIDEOALPHABLENDCONFIG_DST_GLOBAL_ALPHA_MODE((uint32_t)kLCDIF_AlphaLocal) |
                   LCDIF_VIDEOALPHABLENDCONFIG_SRC_ALPHA_FACTOR((uint32_t) false) |
                   LCDIF_VIDEOALPHABLENDCONFIG_DST_ALPHA_FACTOR((uint32_t) false) |
                   LCDIF_VIDEOALPHABLENDCONFIG_SRC_ALPHA_MODE((uint32_t)kLCDIF_AlphaStraight) |
                   LCDIF_VIDEOALPHABLENDCONFIG_DST_ALPHA_MODE((uint32_t)kLCDIF_AlphaStraight);

        *config = pid._alphaConfig;

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Sets the frame buffer address for overlay layer.
 *
 * note The address must be 128 bytes aligned.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param address Frame buffer address.
 * param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerAddr(LCDIF_Type *base, uint8_t displayIndex, uint32_t address, uint8_t layerIndex)
{
    /* The frame buffer address and stride must be 128 bytes aligned. */
    assert(0U == (address & (LCDIF_FB_ALIGN - 1U)));
    assert(layerIndex < 2U);

    switch (layerIndex)
    {
        case 0U:
            base->OVERLAYADDRESS = LCDIF_ADDR_CPU_2_IP(address);
            break;

        case 1U:
            base->OVERLAYADDRESS1 = LCDIF_ADDR_CPU_2_IP(address);
            break;

        default:
            /* Only 2 overlay layers. */
            assert(false);
            break;
    }
}

/*!
 * brief Sets the frame buffer stride for overlay layer.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param strideBytes The stride in byte.
 * param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes, uint8_t layerIndex)
{
    assert(layerIndex < 2U);

    switch (layerIndex)
    {
        case 0U:
            base->OVERLAYSTRIDE = strideBytes;
            break;

        case 1U:
            base->OVERLAYSTRIDE1 = strideBytes;
            break;

        default:
            /* Only 2 overlay layers. */
            assert(false);
            break;
    }
}

/*!
 * brief Gets default panel configuration.
 *
 * The default configuration is
 *   config->enable = true;
 *   config->enableGamma = false;
 *   config->order       = kLCDIF_VideoOverlay0Overlay1;
 *   config->endian      = kLCDIF_NoSwap;
 *
 * param config Pointer to the configuration structure.
 */
void LCDIF_PanelGetDefaultConfig(lcdif_panel_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->enable      = true;
    config->enableGamma = false;
    config->order       = kLCDIF_VideoOverlay0Overlay1;
    config->endian      = kLCDIF_NoSwap;
}

/*!
 * brief Configure the LCDIF panel.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 */
void LCDIF_SetPanelConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_panel_config_t *config)
{
    assert(NULL != config);

    base->BLENDSTACKORDER = (uint32_t)config->order;
    base->SRCCONFIGENDIAN = (uint32_t)config->endian;
    base->PANELFUNCTION = (base->PANELFUNCTION & ~(LCDIF_PANELFUNCTION_OUTPUT_MASK | LCDIF_PANELFUNCTION_GAMMA_MASK)) |
                          LCDIF_PANELFUNCTION_OUTPUT((uint32_t)config->enable) |
                          LCDIF_PANELFUNCTION_GAMMA((uint32_t)config->enableGamma);
}

#else

/*!
 * @brief Get default frame buffer configuration.
 *
 * The default configuration is
 *   config->enable = true;
 *   config->enableGamma = false;
 *   config->format = kLCDIF_PixelFormatRGB565;
 *
 * @param config Pointer to the configuration structure.
 */
void LCDIF_FrameBufferGetDefaultConfig(lcdif_fb_config_t *config)
{
    assert(config != NULL);

    (void)memset(config, 0, sizeof(*config));

    config->enable      = true;
    config->enableGamma = false;
    config->format      = kLCDIF_PixelFormatRGB565;
}

/*!
 * brief Configure the LCDIF frame buffer.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 */
void LCDIF_SetFrameBufferConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_fb_config_t *config)
{
    assert(NULL != config);
    uint32_t reg;

    if (config->enable)
    {
        reg = LCDIF_FRAMEBUFFERCONFIG0_RESET_MASK | LCDIF_FRAMEBUFFERCONFIG0_OUTPUT_MASK | (uint32_t)config->format;
        if (config->enableGamma)
        {
            reg |= LCDIF_FRAMEBUFFERCONFIG0_GAMMA_MASK;
        }
        base->FRAMEBUFFERCONFIG0 = reg;
    }
    else
    {
        base->FRAMEBUFFERCONFIG0 = 0U;
    }
}

#endif

/*
 * @brief Set the frame buffer stride.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param strideBytes The stride in byte.
 */
void LCDIF_SetFrameBufferStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes)
{
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
    base->FRAMEBUFFERSTRIDE0 = strideBytes;
#else
    base->FRAMEBUFFERSTRIDE0 = LCDIF_ALIGN_ADDR(strideBytes, LCDIF_FB_ALIGN);
#endif
}

/*!
 * brief Set the dither configuration.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Index to configure.
 * param config Pointer to the configuration structure.
 */
void LCDIF_SetDitherConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dither_config_t *config)
{
    assert(NULL != config);

    if (config->enable)
    {
        base->DISPLAYDITHERTABLELOW0  = config->low;
        base->DISPLAYDITHERTABLEHIGH0 = config->high;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
        base->PANELFUNCTION |= LCDIF_PANELFUNCTION_DITHER_MASK;
#else
        base->DISPLAYDITHERCONFIG0 = ((uint32_t)config->redSize << LCDIF_DISPLAYDITHERCONFIG0_RED_SIZE_SHIFT) |
                                     ((uint32_t)config->greenSize << LCDIF_DISPLAYDITHERCONFIG0_GREEN_SIZE_SHIFT) |
                                     ((uint32_t)config->blueSize << LCDIF_DISPLAYDITHERCONFIG0_BLUE_SIZE_SHIFT) |
                                     LCDIF_DISPLAYDITHERCONFIG0_ENABLE_MASK;
#endif
    }
    else
    {
        base->DISPLAYDITHERTABLELOW0  = 0U;
        base->DISPLAYDITHERTABLEHIGH0 = 0U;
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
        base->PANELFUNCTION &= ~LCDIF_PANELFUNCTION_DITHER_MASK;
#else
        base->DISPLAYDITHERCONFIG0 = 0U;
#endif
    }
}

/*!
 * brief Set the gamma translation values to the LCDIF gamma table.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param startIndex Start index in the gamma table that the value will be set to.
 * param gamma The gamma values to set to the gamma table in LCDIF, could be defined using LCDIF_MAKE_GAMMA_VALUE.
 * param gammaLen The length of the p gamma.
 */
void LCDIF_SetGammaData(
    LCDIF_Type *base, uint8_t displayIndex, uint16_t startIndex, const uint32_t *gamma, uint16_t gammaLen)
{
    assert(startIndex + gammaLen <= LCDIF_GAMMA_INDEX_MAX);

    base->GAMMAINDEX0 = startIndex;

    while (0U != (gammaLen--))
    {
        base->GAMMADATA0 = *(gamma++);
    }
}

/*!
 * brief Initialize the LCDIF to work in DBI mode.
 *
 * This function configures the LCDIF DBI display.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param config Pointer to the configuration structure.
 * retval kStatus_Success Initialize successfully.
 * retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t LCDIF_DbiModeSetConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dbi_config_t *config)
{
    base->FRAMEBUFFERCONFIG0 = 0;

    base->PANELCONFIG0 = 0U;

    /* Set to DBI mode. */
    base->DBICONFIG0 = LCDIF_DBICONFIG0_DBI_AC_TIME_UNIT(config->acTimeUnit) |
#if (defined(FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY) && FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY)
                       LCDIF_DBICONFIG0_DBIX_POLARITY(config->reversePolarity ? 0UL : 1UL) |
#endif
                       LCDIF_DBICONFIG0_BUS_OUTPUT_SEL(1) | (uint32_t)config->format |
                       LCDIF_DBICONFIG0_DBI_TYPE(config->type);

    /*Put DBI bus into idle*/
    base->DBIIFRESET0 = LCDIF_DBIIFRESET0_DBI_IF_LEVEL_RESET_MASK;

    /*Config AC characteristics*/
    base->DBIWRCHAR10 = LCDIF_DBIWRCHAR10_DBI_WR_CS_ASSERT(config->writeCSAssert) |
                        LCDIF_DBIWRCHAR10_DBI_WR_EOR_WR_ASSERT(config->writeWRAssert) |
                        LCDIF_DBIWRCHAR10_DBI_WR_PERIOD(config->writeWRPeriod);

    base->DBIWRCHAR20 = LCDIF_DBIWRCHAR20_DBI_WR_CS_DE_ASRT(config->writeCSDeassert) |
                        LCDIF_DBIWRCHAR20_DBI_WR_EOR_WR_DE_ASRT(config->writeWRDeassert);

    return kStatus_Success;
}

/*!
 * brief Get the default configuration to initialize the LCDIF DBI mode.
 *
 * The default configuration value is:
 *
 * code
 * config->swizzle         = kLCDIF_DbiOutSwizzleRGB;
 * config->format          = kLCDIF_DbiOutD8RGB332;
 * config->acTimeUnit      = 0;
 * config->type            = kLCDIF_DbiTypeA_ClockedE;
 * config->reversePolarity = false;
 * config->writeWRPeriod   = 3U;
 * config->writeWRAssert   = 0U;
 * config->writeCSAssert   = 0U;
 * config->writeWRDeassert = 0U;
 * config->writeCSDeassert = 0U;
 * config->typeCTas        = 1U;
 * config->typeCSCLTwrl    = 1U;
 * config->typeCSCLTwrh    = 1U;
 * endcode
 *
 * param config Pointer to the LCDIF DBI configuration.
 */
void LCDIF_DbiModeGetDefaultConfig(lcdif_dbi_config_t *config)
{
    config->swizzle    = kLCDIF_DbiOutSwizzleRGB;
    config->format     = kLCDIF_DbiOutD8RGB332;
    config->acTimeUnit = 0;

#if (defined(FSL_FEATURE_LCDIF_HAS_DBI_TYPE) && FSL_FEATURE_LCDIF_HAS_DBI_TYPE)
    config->type = kLCDIF_DbiTypeA_ClockedE;
#endif

#if (defined(FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY) && FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY)
    config->reversePolarity = false;
#endif

    config->writeWRPeriod   = 3U;
    config->writeWRAssert   = 0U;
    config->writeCSAssert   = 0U;
    config->writeWRDeassert = 0U;
    config->writeCSDeassert = 0U;

#if (defined(FSL_FEATURE_LCDIF_HAS_TYPEC) && FSL_FEATURE_LCDIF_HAS_TYPEC)
    config->typeCTas     = 1U;
    config->typeCSCLTwrl = 1U;
    config->typeCSCLTwrh = 1U;
#endif
}

/*!
 * brief Select the update area in DBI mode.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param startX X coordinate for start pixel.
 * param startY Y coordinate for start pixel.
 * param endX X coordinate for end pixel.
 * param endY Y coordinate for end pixel.
 * param isTiled true if the pixel data is tiled.
 */
void LCDIF_DbiSelectArea(LCDIF_Type *base,
                         uint8_t displayIndex,
                         uint16_t startX,
                         uint16_t startY,
                         uint16_t endX,
                         uint16_t endY,
                         bool isTiled)
{
    uint16_t width  = endX - startX + 1U;
    uint16_t height = endY - startY + 1U;

    uint16_t vDisplayExtra = isTiled ? 2U : 1U; /* Used for waiting for the data FIFO to be filled */

    base->HDISPLAY0 = LCDIF_HDISPLAY0_DISPLAY_END((uint32_t)width) | LCDIF_HDISPLAY0_TOTAL((uint32_t)width);
    base->HSYNC0    = LCDIF_HSYNC0_START((uint32_t)startX) | LCDIF_HSYNC0_END((uint32_t)endX + 1UL);

    base->VDISPLAY0 = LCDIF_VDISPLAY0_DISPLAY_END((uint32_t)height) |
                      LCDIF_VDISPLAY0_TOTAL((uint32_t)height + (uint32_t)vDisplayExtra);

    if (isTiled)
    {
        base->VSYNC0 = LCDIF_VSYNC0_START((uint32_t)startY) | LCDIF_VSYNC0_END((uint32_t)endY + 1UL);
    }
}

/*!
 * brief Send data to DBI port.
 *
 * Can be used to send light weight data to panel. To send pixel data in frame buffer, use @ref LCDIF_DbiWriteMem.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param data pointer to data buffer.
 * param dataLen_Byte data buffer length in byte.
 */
void LCDIF_DbiSendData(LCDIF_Type *base, uint8_t displayIndex, const uint8_t *data, uint32_t dataLen_Byte)
{
    while (dataLen_Byte > 0U)
    {
        /* Send data. DBICMD bit set to 1, means currently send data, used in type C mode. */
        base->DBICMD0 = LCDIF_DBICMD0_DBI_COMMANDFLAG(kLCDIF_DbiCmdData) | (uint32_t)(*data) | (1UL << 8U);
        data++;
        dataLen_Byte--;
    }
}

/*!
 * brief Send command followed by data to DBI port.
 *
 * param base LCDIF peripheral base address.
 * param displayIndex Display index.
 * param cmd the DBI command to send.
 * param data pointer to data buffer.
 * param dataLen_Byte data buffer length in byte.
 */
void LCDIF_DbiSendCommandAndData(
    LCDIF_Type *base, uint8_t displayIndex, uint8_t cmd, const uint8_t *data, uint32_t dataLen_Byte)
{
    LCDIF_DbiSendCommand(base, displayIndex, cmd);
    LCDIF_DbiSendData(base, displayIndex, data, dataLen_Byte);
}

/*!
 * brief Get the hardware cursor default configuration
 *
 * The default configuration values are:
 *
 * code
 * config->enable = true;
 * config->format = kLCDIF_CursorMasked;
 * config->hotspotOffsetX = 0;
 * config->hotspotOffsetY = 0;
 * endcode
 *
 * param config Pointer to the hardware cursor configuration structure.
 */
void LCDIF_CursorGetDefaultConfig(lcdif_cursor_config_t *config)
{
    assert(NULL != config);

    (void)memset(config, 0, sizeof(*config));

    config->enable         = true;
    config->format         = kLCDIF_CursorMasked;
    config->hotspotOffsetX = 0;
    config->hotspotOffsetY = 0;
}

/*!
 * brief Configure the cursor.
 *
 * param base LCDIF peripheral base address.
 * param config Cursor configuration.
 */
void LCDIF_SetCursorConfig(LCDIF_Type *base, const lcdif_cursor_config_t *config)
{
    assert(NULL != config);

    uint32_t regConfig = 0U;

    if (config->enable)
    {
        regConfig |= (uint32_t)(config->format) << LCDIF_CURSORCONFIG_FORMAT_SHIFT;
        regConfig |= (((uint32_t)config->hotspotOffsetX << LCDIF_CURSORCONFIG_HOT_SPOT_X_SHIFT) |
                      ((uint32_t)config->hotspotOffsetY << LCDIF_CURSORCONFIG_HOT_SPOT_Y_SHIFT));
    }

    base->CURSORCONFIG = regConfig;
}

/*!
 * brief Set the cursor color
 *
 * param base LCDIF peripheral base address.
 * param background  Background color, could be defined use ref LCDIF_MAKE_CURSOR_COLOR
 * param foreground  Foreground color, could be defined use ref LCDIF_MAKE_CURSOR_COLOR
 */
void LCDIF_SetCursorColor(LCDIF_Type *base, uint32_t background, uint32_t foreground)
{
    base->CURSORBACKGROUND = background;
    base->CURSORFOREGROUND = foreground;
}
