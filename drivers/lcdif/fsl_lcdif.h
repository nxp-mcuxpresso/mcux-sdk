/*
 * Copyright (c) 2019-2021,2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LCDIF_H_
#define FSL_LCDIF_H_

#include "fsl_common.h"

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/*!
 * @addtogroup lcdif_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_LCDIF_DRIVER_VERSION (MAKE_VERSION(2, 2, 0))
/*! @} */

/*! @brief Construct the cursor color, every element should be in the range of 0 ~ 255. */
#define LCDIF_MAKE_CURSOR_COLOR(r, g, b) (((r) << 16U) | ((g) << 8U) | ((b) << 0U))

/*! @brief Construct the gamma value set to LCDIF gamma table, every element should be in the range of 0~255. */
#define LCDIF_MAKE_GAMMA_VALUE(r, g, b) (((r) << 16U) | ((g) << 8U) | ((b) << 0U))

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*! @brief Construct the colour value for the background layer. */
#define LCDIF_MAKE_BACKGROUND_VALUE(a, r, g, b) (((a) << 24U) | ((r) << 16U) | ((g) << 8U) | ((b) << 0U))
#endif

/*! @brief Calculate the aligned address for LCDIF buffer. */
#define LCDIF_ALIGN_ADDR(addr, align) ((((addr) / (align) * (align)) == (addr)) ? (addr) : ((addr) / (align) * (align) + (align)))

/*! @brief The frame buffer should be 128 byte aligned. */
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
#define LCDIF_FB_ALIGN    64U
#define LCDIF_FB_UV_ALIGN 32U
#else
#define LCDIF_FB_ALIGN 128U
#endif

/*! @brief Gamma index max value. */
#define LCDIF_GAMMA_INDEX_MAX 256U

/*! @brief The cursor size is 32 x 32 */
#define LCDIF_CURSOR_SIZE 32U

#ifndef LCDIF_FRAMEBUFFERCONFIG0_OUTPUT_MASK
#define LCDIF_FRAMEBUFFERCONFIG0_OUTPUT_MASK (1U << 8U)
#endif

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#define LCDIF_ADDR_CPU_2_IP(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_Local2DMA))
#else
#define LCDIF_ADDR_CPU_2_IP(addr) ((uint32_t)addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

/*!
 * @brief LCDIF signal polarity flags
 */
enum _lcdif_polarity_flags
{
    kLCDIF_VsyncActiveLow            = 0U,         /*!< VSYNC active low. */
    kLCDIF_VsyncActiveHigh           = (1U << 0U), /*!< VSYNC active high. */
    kLCDIF_HsyncActiveLow            = 0U,         /*!< HSYNC active low. */
    kLCDIF_HsyncActiveHigh           = (1U << 1U), /*!< HSYNC active high. */
    kLCDIF_DataEnableActiveLow       = 0U,         /*!< Data enable line active low. */
    kLCDIF_DataEnableActiveHigh      = (1U << 2U), /*!< Data enable line active high. */
    kLCDIF_DriveDataOnFallingClkEdge = 0U, /*!< Drive data on falling clock edge, capture data on rising clock edge. */
    kLCDIF_DriveDataOnRisingClkEdge  = (1U << 3U), /*!< Drive data on falling clock edge, capture data
                                                                         on rising clock edge. */
};

/*! @brief LCDIF DPI output format. */
typedef enum _lcdif_output_format
{
    kLCDIF_Output16BitConfig1 = 0U, /*!< 16-bit configuration 1. RGB565: XXXXXXXX_RRRRRGGG_GGGBBBBB. */
    kLCDIF_Output16BitConfig2 = 1U, /*!< 16-bit configuration 2. RGB565: XXXRRRRR_XXGGGGGG_XXXBBBBB. */
    kLCDIF_Output16BitConfig3 = 2U, /*!< 16-bit configuration 3. RGB565: XXRRRRRX_XXGGGGGG_XXBBBBBX. */
    kLCDIF_Output18BitConfig1 = 3U, /*!< 18-bit configuration 1. RGB666: XXXXXXRR_RRRRGGGG_GGBBBBBB. */
    kLCDIF_Output18BitConfig2 = 4U, /*!< 18-bit configuration 2. RGB666: XXRRRRRR_XXGGGGGG_XXBBBBBB. */
    kLCDIF_Output24Bit        = 5U, /*!< 24-bit. */
} lcdif_output_format_t;

/*! @brief Configuration for LCDIF module to work in DBI mode. */
typedef struct _lcdif_dpi_config
{
    uint16_t panelWidth;          /*!< Display panel width, pixels per line. */
    uint16_t panelHeight;         /*!< Display panel height, how many lines per panel. */
    uint8_t hsw;                  /*!< HSYNC pulse width. */
    uint8_t hfp;                  /*!< Horizontal front porch. */
    uint8_t hbp;                  /*!< Horizontal back porch. */
    uint8_t vsw;                  /*!< VSYNC pulse width. */
    uint8_t vfp;                  /*!< Vrtical front porch. */
    uint8_t vbp;                  /*!< Vertical back porch. */
    uint32_t polarityFlags;       /*!< OR'ed value of @ref _lcdif_polarity_flags, used to contol the signal polarity. */
    lcdif_output_format_t format; /*!< DPI output format. */
} lcdif_dpi_config_t;

/*! @brief LCDIF frame buffer pixel format. */
typedef enum _lcdif_fb_format
{
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
    kLCDIF_PixelFormatARGB4444      = 1,          /*!< ARGB4444, 16-bit each pixel, 4-bit each element. */
    kLCDIF_PixelFormatARGB1555      = 2,          /*!< ARGB1555, 16-bit each pixel, 5-bit each element. */
    kLCDIF_PixelFormatRGB565        = 3,          /*!< RGB565, 16-bit each pixel. */
    kLCDIF_PixelFormatARGB8888      = 4,          /*!< ARGB8888, 32-bit each pixel, 8-bit each element. */
    kLCDIF_PixelFormatRGB888        = 5,          /*!< RGB888, 24-bit each pixel, 8-bit each element. */
    kLCDIF_PixelFormatARGB8565      = 6,          /*!< ARGB8565, 24-bit each pixel. */
    kLCDIF_PixelFormatARGB8888Tiled = 0x1U << 3U, /*!< ARGB8888, 32-bit each pixel, 8-bit each element in tiled format,
                                                     not supported in overlay layer 1. */
    kLCDIF_PixelFormatYUV422Tiled = 0x2U << 3U,   /*!< YUV422, in tiled format, not supported in overlay layer 1. */
    kLCDIF_PixelFormatYUV420Tiled =
        0x3U << 3U, /*!< YUV420, in tiled format, need 2 plane, not supported in overlay layer 1. */
    kLCDIF_PixelFormatRGB888Tiled =
        0x8U
        << 3U, /*!< RGB888, 24-bit each pixel, 8-bit each element in tiled format, not supported in overlay layer 1. */
    kLCDIF_PixelFormatARGB8565Tiled =
        0x9U << 3U, /*!< ARGB8565, 24-bit each pixel in tiled format, not supported in overlay layer 1. */
#else
    kLCDIF_PixelFormatXRGB444  = 1, /*!< XRGB4444, deprecated, use kLCDIF_PixelFormatXRGB4444 instead. */
    kLCDIF_PixelFormatXRGB4444 = 1, /*!< XRGB4444, 16-bit each pixel, 4-bit each element. R4G4B4 in reference manual. */
    kLCDIF_PixelFormatXRGB1555 = 2, /*!< XRGB1555, 16-bit each pixel, 5-bit each element. R5G5B5 in reference manual. */
    kLCDIF_PixelFormatRGB565   = 3, /*!< RGB565, 16-bit each pixel. R5G6B5 in reference manual. */
    kLCDIF_PixelFormatXRGB8888 = 4, /*!< XRGB8888, 32-bit each pixel, 8-bit each element. R8G8B8 in reference manual. */
#endif
} lcdif_fb_format_t;

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*! @brief LCDIF layer input pixel order. */
typedef enum _lcdif_layer_input_order
{
    kLCDIF_PixelInputOrderARGB = 0, /*!< Input order ARGB. */
    kLCDIF_PixelInputOrderRGBA = 1, /*!< Input order RGBA. */
    kLCDIF_PixelInputOrderABGR = 2, /*!< Input order ABGR. */
    kLCDIF_PixelInputOrderBGRA = 3, /*!< Input order BGRA. */
} lcdif_layer_input_order_t;

/*! @brief LCDIF layer rotation or flip configuration. */
typedef enum _lcdif_layer_rotate_flip
{
    kLCDIF_Rotate0        = 0U, /*!< Clock wise rotate 0 degree. */
    kLCDIF_Rotate90       = 1U, /*!< Clock wise rotate 90 degree, not supported yet. */
    kLCDIF_Rotate180      = 2U, /*!< Clock wise rotate 180 degree. */
    kLCDIF_Rotate270      = 3U, /*!< Clock wise rotate 270 degree, not supported yet. */
    kLCDIF_FlipHorizontal = 4U, /*!< Horizontal flip. */
    kLCDIF_FlipVertical   = 5U, /*!< Vertical flip. */
} lcdif_layer_rotate_flip_t;

/*! @brief LCDIF layer color key configuration. */
typedef struct _lcdif_layer_colorkey
{
    bool enable;        /*!< Enable the color keying. */
    uint32_t lowValue;  /* The low value for the color key range, in 32-bit ARGB8888 format. */
    uint32_t highValue; /* The high value for the color key range, in 32-bit ARGB8888 format. */
} lcdif_layer_colorkey_t;

/*!
 * @brief Alpha blend alpha component mode.
 * @anchor lcdif_layer_alpha_mode_t
 */
enum
{
    kLCDIF_AlphaStraight = 0U, /*!< Use straight alpha, s0_alpha' = s0_alpha. */
    kLCDIF_AlphaInversed       /*!< Use inversed alpha, s0_alpha' = 0xFF - s0_alpha. */
};

/*! @brief LCDIF layer global alpha mode for alpha blend.
 *  @anchor lcdif_layer_global_alpha_mode_t
 */
enum
{
    kLCDIF_AlphaLocal = 0U, /*!< Use the alpha(or inversed alpha) component directly. */
    kLCDIF_AlphaGlobal,     /*!< Use the global alpha instead. */
    kLCDIF_AlphaScaled,     /*!< Multiply the alpha(or inversed alpha) component by the global alpha. */
};

/*!
 * @brief Alpha blend factor mode.
 * @anchor lcdif_layer_alpha_factor_mode_t
 */
enum
{
    kLCDIF_AlphaFactorZero     = 0, /*!< Use 0 as the blending factor. */
    kLCDIF_AlphaFactorOne      = 1, /*!< Use 1 as the blending factor. */
    kLCDIF_AlphaFactorStraight = 2, /*!< Use the modified alpha component(As'' for source layer or Ad'' for destination
                                       layer) as the blending factor. */
    kLCDIF_AlphaFactorInversed = 3, /*!< Use the inversed alpha component(1-As'' for source layer or 1-Ad'' for
                                       destination layer) as the blending factor. */
};

/*! @brief LCDIF frame buffer alpha blend configuration.
 *
 * The alpha blending formula is C = Fs x Cs + Fd x Cd, and A = Fs x As'' + Fd x Ad''.
 * C/A: generated final color/alpha component,
 * Cs/Cd: original color component for source and destination layer,
 * As''/Ad'': modified alpha component for source and destination layer, take As'' as example,
 *            As' = As or (1 - As), chosen by srcAlphaMode
 *            As'' = As' or Ags or (As' x Ags), chosen by srcGlobalAlphaMode, Ags configured by srcGlobalAlpha
 * Fs/Fd: blending factor for source/destination layer, take Fs as example,
 *        Fs = 0 or 1 or As'' or (1 - As''), chosen by srcFactorMode
 */
typedef struct
{
    uint32_t enable : 1;       /*!< Enables or disables alpha blend configuration. */
    uint32_t srcAlphaMode : 1; /*!< Use the straight(As) or inversed(1-As) alpha value for modified alpha for the source
                                  layer, see @ref lcdif_layer_alpha_mode_t. */
    uint32_t : 1;
    uint32_t srcGlobalAlphaMode : 2; /*!< Source layer global alpha mode, see @ref lcdif_layer_global_alpha_mode_t. */
    uint32_t : 1;
    uint32_t srcFactorMode : 2;      /*!< Source layer blend factor mode, see @ref lcdif_layer_alpha_factor_mode_t. */
    uint32_t useSrcAlpha : 1;   /*!< Set to true to use source alpha for the source blending factor, otherwise use the
                                   destination alpha. */
    uint32_t dstAlphaMode : 1;  /*!< Use the straight(Ad) or inversed(1-Ad) alpha value for modified alpha for the
                                   destination layer, see @ref lcdif_layer_alpha_mode_t. */
    uint32_t
        dstGlobalAlphaMode : 2; /*!< Destination layer global alpha mode, see @ref lcdif_layer_global_alpha_mode_t. */
    uint32_t : 1;
    uint32_t dstFactorMode : 2; /*!< Destination layer blend factor mode, see @ref lcdif_layer_alpha_factor_mode_t. */
    uint32_t useDstAlpha : 1;   /*!< Set to true to use destination alpha for the destination blending factor, otherwise
                                   use the source alpha. */
    uint32_t srcGlobalAlpha : 8; /*!< Source layer global alpha value, 0~255. */
    uint32_t dstGlobalAlpha : 8; /*!< Destination layer global alpha value, 0~255. */
} lcdif_layer_alpha_blend_config_t;

/*! @brief LCDIF Porter Duff blend mode. Note: don't change the enum item value */
typedef enum _lcdif_porter_duff_blend_mode
{
    kLCDIF_PorterDuffSrc = 0, /*!< Source Only */
    kLCDIF_PorterDuffAtop,    /*!< Source Atop */
    kLCDIF_PorterDuffOver,    /*!< Source Over */
    kLCDIF_PorterDuffIn,      /*!< Source In. */
    kLCDIF_PorterDuffOut,     /*!< Source Out. */
    kLCDIF_PorterDuffDst,     /*!< Destination Only. */
    kLCDIF_PorterDuffDstAtop, /*!< Destination Atop. */
    kLCDIF_PorterDuffDstOver, /*!< Destination Over. */
    kLCDIF_PorterDuffDstIn,   /*!< Destination In. */
    kLCDIF_PorterDuffDstOut,  /*!< Destination Out. */
    kLCDIF_PorterDuffPlus,    /*!< Clear. */
    kLCDIF_PorterDuffXor,     /*!< XOR. */
    kLCDIF_PorterDuffClear,   /*!< Clear. */
    kLCDIF_PorterDuffMax,
} lcdif_porter_duff_blend_mode_t;

/*! @brief LCDIF Color space convert standard between RGB and YUV when the input format is tiled YUV. */
typedef enum _lcdif_layer_convert_standard
{
    kLCDIF_ConvertBT601 = 0x0U, /*!< Use standard BT601. */
    kLCDIF_ConvertBT709 = 0x1U, /*!< Use standard BT709. */
} lcdif_layer_convert_standard_t;

/*! @brief LCDIF frame buffer configuration.
 *
 * For LCDIF of DC8000 version, there are 3 layers in the pre-processing,
 * all shares the same frame buffer configuration.
 */
typedef struct _lcdif_fb_config
{
    bool enable;      /*!< Enable the layer output. */
    bool enableClear; /*!< Enable the color clear for this layer, onve enabled, the whole layer will be filled with the
                         color configured in clearValue. */
    uint32_t clearValue;                     /*!< The value used for layer clear. */
    lcdif_fb_format_t format;                /*!< Frame buffer output pixel format. */
    lcdif_layer_convert_standard_t standard; /*!< Color space convert standard, not used for overlay layer 1 since it
                                                does not support tile YUV input. */
    bool enableUVSwizzle; /*!< Swizzle the U/V components, not used for overlay layer 1 since it does not support tile
                             YUV input. */
    lcdif_layer_input_order_t inOrder;        /*!< Color component order of the input pixel. */
    lcdif_layer_colorkey_t colorkey;          /*!< Color key configuration. */
    lcdif_layer_rotate_flip_t rotateFlipMode; /*!< LCDIF frame buffer rotation or flip configuration. */
    lcdif_layer_alpha_blend_config_t alpha;   /*!< The alpha blending configuration. */
    /* The background layer with a constant color is used, the other layers do not need to fill the whole screen. */
    uint16_t topLeftX; /*!< The x value of thr top-left coordinate. */
    uint16_t topLeftY; /*!< The y value of thr top-left coordinate. */
    uint16_t width;    /*!< The width of the layer. */
    uint16_t height;   /*!< The height of the layer. */
} lcdif_fb_config_t;

/*! @brief LCDIF the layer order from bottom to top.
 *
 * There are 5 layers in total, apart from the background layer fixed in the bottom, and the cursor
 * layer on top that does not participate in the color key and alpha blend, the order of the other 3 layers
 * video/graphic layer, overlay layer 0 and 1 can be changed. During color key or alpha blend process, between
 * 2 adjacent layers, the lower layer is considered as destination layer and the upper layer is considered
 * as source layer. The precess is performed from bottom to top, after processing 2 layes, the generated new
 * layer will be considered as destination layer then participate in the next process with the next upper layer.
 */
typedef enum _lcdif_layer_order
{
    kLCDIF_VideoOverlay0Overlay1 = 0U, /*!< In the order of video, overlay0, overlay1. */
    kLCDIF_VideoOverlay1Overlay0 = 1U, /*!< In the order of video, overlay1, overlay0. */
    kLCDIF_Overlay0VideoOverlay1 = 2U, /*!< In the order of overlay0, video, overlay1. */
    kLCDIF_Overlay0Overlay1Video = 3U, /*!< In the order of overlay0, overlay1, video. */
    kLCDIF_Overlay1VideoOverlay0 = 4U, /*!< In the order of overlay1, video, overlay0. */
    kLCDIF_Overlay1Overlay0Video = 5U, /*!< In the order of overlay1, overlay0, video. */
} lcdif_layer_order_t;

/*! @brief LCDIF the pixel source endian mode. */
typedef enum _lcdif_endian_mode
{
    kLCDIF_NoSwap       = 0U, /*!< No swap. */
    kLCDIF_HalfWordSwap = 1U, /*!< 16-bit boundary swap, from 0123 to 1032. */
    kLCDIF_WordSwap     = 2U, /*!< 32-bit boundary swap, from 0123 to 3210. */
} lcdif_endian_mode_t;

/*! @brief LCDIF panel configuration. */
typedef struct _lcdif_panel_config
{
    bool enable;                /*!< Enable the frame buffer output. */
    bool enableGamma;           /*!< Enable the gamma correction. */
    lcdif_layer_order_t order;  /*!< Layer order. */
    lcdif_endian_mode_t endian; /*!< Pixel source endian mode. */
} lcdif_panel_config_t;
#else
/*! @brief LCDIF frame buffer configuration. */
typedef struct _lcdif_fb_config
{
    bool enable;              /*!< Enable the frame buffer output. */
    bool enableGamma;         /*!< Enable the gamma correction. */
    lcdif_fb_format_t format; /*!< Frame buffer pixel format. */
} lcdif_fb_config_t;
#endif

/*! @brief LCDIF interrupt and status. */
enum _lcdif_interrupt
{
    kLCDIF_Display0FrameDoneInterrupt =
        LCDIF_DISPLAYINTR_DISP0_MASK, /*!< The last pixel of visible area in frame is shown. */
#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
    kLCDIF_Display0DbiConfigErrorInterrupt =
        LCDIF_DISPLAYINTR_DISP0_DBI_CFG_ERROR_MASK,                          /*!< The DBI command is illegal. */
    kLCDIF_PanelUnderflowInterrupt = LCDIF_DISPLAYINTR_PANEL_UNDERFLOW_MASK, /*!< The AXI clock and pixel clock mismatch
                                                                                causing data supply insufficient. */
    kLCDIF_SoftwareResetDoneInterrupt = LCDIF_DISPLAYINTR_SOFT_RESET_DONE_MASK, /*!< A software reset has completed. */
    kLCDIF_BusErrorInterrupt          = LCDIF_DISPLAYINTR_BUS_ERROR_MASK, /*!< An AXI bus transfer error occurrs. */
#endif
};

/*! @brief LCDIF cursor format. */
typedef enum _lcdif_cursor_format
{
    kLCDIF_CursorMasked   = 1, /*!< Masked format. */
    kLCDIF_CursorARGB8888 = 2, /*!< ARGB8888. */
} lcdif_cursor_format_t;

/*! @brief LCDIF cursor configuration. */
typedef struct _lcdif_cursor_config
{
    bool enable;                  /*!< Enable the cursor or not. */
    lcdif_cursor_format_t format; /*!< Cursor format. */
    uint8_t hotspotOffsetX;       /*!< Offset of the hotspot to top left point, range 0 ~ 31 */
    uint8_t hotspotOffsetY;       /*!< Offset of the hotspot to top left point, range 0 ~ 31 */
} lcdif_cursor_config_t;

/*!
 * @brief LCDIF dither configuration.
 *
 * 1. Decide which bit of pixel color to enhance. This is configured by the
 * @ref lcdif_dither_config_t::redSize, @ref lcdif_dither_config_t::greenSize,
 * and @ref lcdif_dither_config_t::blueSize. For example, setting redSize=6
 * means it is the 6th bit starting from the MSB that we want to enhance, in other words,
 * it is the RedColor[2]bit from RedColor[7:0]. greenSize and blueSize function
 * in the same way.
 *
 * 2. Create the look-up table.
 *  a. The Look-Up Table includes 16 entries, 4 bits for each.
 *  b. The Look-Up Table provides a value U[3:0] through the index X[1:0] and Y[1:0].
 *  c. The color value RedColor[3:0] is used to compare with this U[3:0].
 *  d. If RedColor[3:0] > U[3:0], and RedColor[7:2] is not 6'b111111, then the
 *     final color value is: NewRedColor = RedColor[7:2] + 1'b1.
 *  e. If RedColor[3:0] <= U[3:0], then NewRedColor = RedColor[7:2].
 */
typedef struct _lcdif_dither_config
{
    bool enable;       /*!< Enable or not. */
#if !(defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000)
    uint8_t redSize;   /*!< Red color size, valid region 4-8. */
    uint8_t greenSize; /*!< Green color size, valid region 4-8. */
    uint8_t blueSize;  /*!< Blue color size, valid region 4-8. */
#endif
    uint32_t low;      /*!< Low part of the look up table. */
    uint32_t high;     /*!< High part of the look up table. */
} lcdif_dither_config_t;

/*! @brief LCDIF DBI command flag. */
enum _lcdif_dbi_cmd_flag
{
    kLCDIF_DbiCmdAddress = 0U, /*!< Send address (or command). */
    kLCDIF_DbiCmdWriteMem,     /*!< Start write memory. */
    kLCDIF_DbiCmdData,         /*!< Send data. */
    kLCDIF_DbiCmdReadMem,      /*!< Start read memory. */
};

/*! @brief LCDIF DBI output format. */
typedef enum _lcdif_dbi_out_format
{
    /*! 8-bit data bus width, pixel RGB332. For type A or B. 1 pixel sent in 1 cycle. */
    kLCDIF_DbiOutD8RGB332 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(0),
    /*! 8-bit data bus width, pixel RGB444. For type A or B. 2 pixels sent in 3 cycles. */
    kLCDIF_DbiOutD8RGB444 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(1),
    /*! 8-bit data bus width, pixel RGB565. For type A or B. 1 pixel sent in 2 cycles. */
    kLCDIF_DbiOutD8RGB565 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(2),
    /*! 8-bit data bus width, pixel RGB666. For type A or B. 1 pixel sent in 3 cycles, data bus 2 LSB not used. */
    kLCDIF_DbiOutD8RGB666 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(3),
    /*! 8-bit data bus width, pixel RGB888. For type A or B. 1 pixel sent in 3 cycles. */
    kLCDIF_DbiOutD8RGB888 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(4),
    /*! 9-bit data bus width, pixel RGB666. For type A or B. 1 pixel sent in 2 cycles. */
    kLCDIF_DbiOutD9RGB666 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(5),
    /*! 16-bit data bus width, pixel RGB332. For type A or B. 2 pixels sent in 1 cycle. */
    kLCDIF_DbiOutD16RGB332 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(6),
    /*! 16-bit data bus width, pixel RGB444. For type A or B. 1 pixel sent in 1 cycle, data bus 4 MSB not used. */
    kLCDIF_DbiOutD16RGB444 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(7),
    /*! 16-bit data bus width, pixel RGB565. For type A or B. 1 pixel sent in 1 cycle. */
    kLCDIF_DbiOutD16RGB565 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(8),
    /*! 16-bit data bus width, pixel RGB666. For type A or B. 2 pixels sent in 3 cycles. */
    kLCDIF_DbiOutD16RGB666Option1 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(9),
    /*! 16-bit data bus width, pixel RGB666. For type A or B. 1 pixel sent in 2 cycles. */
    kLCDIF_DbiOutD16RGB666Option2 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(10),
    /*! 16-bit data bus width, pixel RGB888. For type A or B. 2 pixels sent in 3 cycles. */
    kLCDIF_DbiOutD16RGB888Option1 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(11),
    /*! 16-bit data bus width, pixel RGB888. For type A or B. 1 pixel sent in 2 cycles. */
    kLCDIF_DbiOutD16RGB888Option2 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(12),

#if (defined(FSL_FEATURE_LCDIF_HAS_TYPEC) && FSL_FEATURE_LCDIF_HAS_TYPEC)
    /*! 1-bit data bus width, pixel RGB565. For type C option 1, use extra bit to distinguish Data and Command (DC). */
    kLCDIF_DbiOutD1RGB565Option1 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(13) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(1),
    /*! 1-bit data bus width, pixel RGB565. For type C option 2, use extra byte to distinguish Data and Command (DC). */
    kLCDIF_DbiOutD1RGB565Option2 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(13) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(2),
    /*! 1-bit data bus width, pixel RGB565. For type C option 3, use extra DC line to distinguish Data and Command (DC).
     */
    kLCDIF_DbiOutD1RGB565Option3 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(13) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(3),
    /*! 1-bit data bus width, pixel RGB888. For type C option 1, use extra bit to distinguish Data and Command (DC). */
    kLCDIF_DbiOutD1RG888Option1 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(14) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(1),
    /*! 1-bit data bus width, pixel RGB888. For type C option 2, use extra byte to distinguish Data and Command (DC). */
    kLCDIF_DbiOutD1RG888Option2 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(14) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(2),
    /*! 1-bit data bus width, pixel RGB888. For type C option 3, use extra DC line to distinguish Data and Command (DC).
     */
    kLCDIF_DbiOutD1RG888Option3 = LCDIF_DBICONFIG0_DBI_DATA_FORMAT(14) | LCDIF_DBICONFIG0_DBI_TYPEC_OPT(3),
#endif
} lcdif_dbi_out_format_t;

/*! @brief LCDIF DBI type. */
typedef enum _lcdif_dbi_type
{
    kLCDIF_DbiTypeA_FixedE   = 0U, /*!< Selects DBI type A fixed E mode, 68000, Motorola mode. */
    kLCDIF_DbiTypeA_ClockedE = 1U, /*!< Selects DBI Type A Clocked E mode, 68000, Motorola mode. */
    kLCDIF_DbiTypeB          = 2U, /*!< Selects DBI type B, 8080, Intel mode. */
#if (defined(FSL_FEATURE_LCDIF_HAS_TYPEC) && FSL_FEATURE_LCDIF_HAS_TYPEC)
    kLCDIF_DbiTypeC = 3U,          /*!< Selects DBI type C, SPI mode. */
#endif
} lcdif_dbi_type_t;

/*! @brief LCDIF DBI output swizzle. */
typedef enum _lcdif_dbi_out_swizzle
{
    kLCDIF_DbiOutSwizzleRGB = 0U, /*!< RGB */
    kLCDIF_DbiOutSwizzleBGR = 1U, /*!< BGR */
} lcdif_dbi_out_swizzle_t;

/*! @brief LCDIF DBI configuration. */
typedef struct _lcdif_dbi_config
{
    lcdif_dbi_out_swizzle_t swizzle; /*!< Swizzle. */
    lcdif_dbi_out_format_t format;   /*!< Output format. */
    uint8_t acTimeUnit;              /*!< Time unit for AC characteristics. */
    lcdif_dbi_type_t type;           /*!< DBI type. */
#if (defined(FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY) && FSL_FEATURE_LCDIF_HAS_DBIX_POLARITY)
    bool reversePolarity;            /*!< Reverse the DC pin polarity. */
#endif

    /*! WR signal period, Cycle number = writeWRPeriod * (acTimeUnit + 1), must be no less than 3.
     * Only for type A and type b.
     */
    uint16_t writeWRPeriod;
    /*! Cycle number = writeWRAssert * (acTimeUnit + 1), only for type A and type B.
     * With kLCDIF_DbiTypeA_FixedE: Not used.
     * With kLCDIF_DbiTypeA_ClockedE: Time to assert E.
     * With kLCDIF_DbiTypeB: Time to assert WRX.
     */
    uint8_t writeWRAssert;

    /*! Cycle number = writeCSAssert * (acTimeUnit + 1), only for type A and type B.
     * With kLCDIF_DbiTypeA_FixedE: Time to assert CSX.
     * With kLCDIF_DbiTypeA_ClockedE: Not used.
     * With kLCDIF_DbiTypeB: Time to assert CSX.
     */
    uint8_t writeCSAssert;

    /*! Cycle number = writeWRDeassert * (acTimeUnit + 1), only for type A and type B.
     * With kLCDIF_DbiTypeA_FixedE: Not used.
     * With kLCDIF_DbiTypeA_ClockedE: Time to de-assert E.
     * With kLCDIF_DbiTypeB: Time to de-assert WRX.
     */
    uint16_t writeWRDeassert;

    /*! Cycle number = writeCSDeassert * (acTimeUnit + 1), only for type A and type B.
     * With kLCDIF_DbiTypeA_FixedE: Time to de-assert CSX.
     * With kLCDIF_DbiTypeA_ClockedE: Not used.
     * With kLCDIF_DbiTypeB: Time to de-assert CSX.
     */
    uint16_t writeCSDeassert;

#if (defined(FSL_FEATURE_LCDIF_HAS_TYPEC) && FSL_FEATURE_LCDIF_HAS_TYPEC)
    /* Type C AC configuration. */
    uint8_t typeCTas;     /*!< How many sdaClk cycles in Tas phase, only for Type C option 3, at least 1. */
    uint8_t typeCSCLTwrl; /*!< How many sdaClk cycles in Twrl phase, only for Type C, at least 1. */
    uint8_t typeCSCLTwrh; /*!< How many sdaClk cycles in Twrh phase, only for Type C, at least 1. */
#endif
} lcdif_dbi_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initialize the LCDIF.
 *
 * This function initializes the LCDIF to work.
 *
 * @param base LCDIF peripheral base address.
 *
 * @retval kStatus_Success Initialize successfully.
 */
status_t LCDIF_Init(LCDIF_Type *base);

/*!
 * @brief De-initialize the LCDIF.
 *
 * This function disables the LCDIF peripheral clock.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIF_Deinit(LCDIF_Type *base);

/*! @} */

/*!
 * @name DPI mode
 * @{
 */

/*!
 * @brief Get the default configuration for to initialize the LCDIF.
 *
 * The default configuration value is:
 *
 * @code
   config->panelWidth = 0;
   config->panelHeight = 0;
   config->hsw = 0;
   config->hfp = 0;
   config->hbp = 0;
   config->vsw = 0;
   config->vfp = 0;
   config->vbp = 0;
   config->polarityFlags = kLCDIF_VsyncActiveLow | kLCDIF_HsyncActiveLow | kLCDIF_DataEnableActiveHigh |
   kLCDIF_DriveDataOnFallingClkEdge; config->format = kLCDIF_Output24Bit;
   @endcode
 *
 * @param config Pointer to the LCDIF configuration.
 */
void LCDIF_DpiModeGetDefaultConfig(lcdif_dpi_config_t *config);

/*!
 * @brief Initialize the LCDIF to work in DPI mode.
 *
 * This function configures the LCDIF DPI display.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration structure.
 *
 * @retval kStatus_Success Initialize successfully.
 * @retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t LCDIF_DpiModeSetConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dpi_config_t *config);

/* @} */

/*!
 * @name DBI mode
 * @{
 */

/*!
 * @brief Initialize the LCDIF to work in DBI mode.
 *
 * This function configures the LCDIF DBI display.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration structure.
 * @retval kStatus_Success Initialize successfully.
 * @retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t LCDIF_DbiModeSetConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dbi_config_t *config);

/*!
 * @brief Get the default configuration to initialize the LCDIF DBI mode.
 *
 * The default configuration value is:
 *
 * @code
   config->swizzle         = kLCDIF_DbiOutSwizzleRGB;
   config->format          = kLCDIF_DbiOutD8RGB332;
   config->acTimeUnit      = 0;
   config->type            = kLCDIF_DbiTypeA_ClockedE;
   config->reversePolarity = false;
   config->writeWRPeriod   = 3U;
   config->writeWRAssert   = 0U;
   config->writeCSAssert   = 0U;
   config->writeWRDeassert = 0U;
   config->writeCSDeassert = 0U;
   config->typeCTas        = 1U;
   config->typeCSCLTwrl    = 1U;
   config->typeCSCLTwrh    = 1U;
   @endcode
 *
 * @param config Pointer to the LCDIF DBI configuration.
 */
void LCDIF_DbiModeGetDefaultConfig(lcdif_dbi_config_t *config);

/*!
 * @brief Reset the DBI module.
 *
 * @param displayIndex Display index.
 * @param base LCDIF peripheral base address.
 */
static inline void LCDIF_DbiReset(LCDIF_Type *base, uint8_t displayIndex)
{
    base->DBIIFRESET0 = LCDIF_DBIIFRESET0_DBI_IF_LEVEL_RESET_MASK;
}

#if (defined(FSL_FEATURE_LCDIF_HAS_TYPEC) && FSL_FEATURE_LCDIF_HAS_TYPEC)
/*!
 * @brief Check whether the FIFO is full in DBI mode type C.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @retval true FIFO full.
 * @retval false FIFO not full.
 */
static inline bool LCDIF_DbiIsTypeCFifoFull(LCDIF_Type *base, uint8_t displayIndex)
{
    return (base->DCSTATUS0 & LCDIF_DCSTATUS0_DBI_TYPEC_FIFO_FULL_MASK) != 0UL;
}
#endif

/*!
 * @brief Select the update area in DBI mode.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param startX X coordinate for start pixel.
 * @param startY Y coordinate for start pixel.
 * @param endX X coordinate for end pixel.
 * @param endY Y coordinate for end pixel.
 * @param isTiled true if the pixel data is tiled.
 */
void LCDIF_DbiSelectArea(LCDIF_Type *base,
                         uint8_t displayIndex,
                         uint16_t startX,
                         uint16_t startY,
                         uint16_t endX,
                         uint16_t endY,
                         bool isTiled);

/*!
 * @brief Send command to DBI port.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param cmd the DBI command to send.
 */
static inline void LCDIF_DbiSendCommand(LCDIF_Type *base, uint8_t displayIndex, uint8_t cmd)
{
    base->DBICMD0 = LCDIF_DBICMD0_DBI_COMMANDFLAG(kLCDIF_DbiCmdAddress) | (uint32_t)cmd;
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
void LCDIF_DbiSendData(LCDIF_Type *base, uint8_t displayIndex, const uint8_t *data, uint32_t dataLen_Byte);

/*!
 * @brief Send command followed by data to DBI port.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param cmd the DBI command to send.
 * @param data pointer to data buffer.
 * @param dataLen_Byte data buffer length in byte.
 */
void LCDIF_DbiSendCommandAndData(
    LCDIF_Type *base, uint8_t displayIndex, uint8_t cmd, const uint8_t *data, uint32_t dataLen_Byte);

/*!
 * @brief Send pixel data in frame buffer to panel controller memory.
 *
 * This function starts sending the pixel data in frame buffer to panel controller,
 * user can monitor interrupt @ref kLCDIF_Display0FrameDoneInterrupt to know when
 * then data sending finished.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 */
static inline void LCDIF_DbiWriteMem(LCDIF_Type *base, uint8_t displayIndex)
{
    base->DBICMD0 = LCDIF_DBICMD0_DBI_COMMANDFLAG(kLCDIF_DbiCmdWriteMem);
}
/* @} */

/*!
 * @name Frame buffer
 * @{
 */

/*!
 * @brief Configure the LCDIF frame buffer.
 *
 * @Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version.
 * Apart from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API to
 * configure the legacy video layer, and use @ref LCDIF_SetOverlayFrameBufferConfig to configure the overlay layers.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration structure.
 */
void LCDIF_SetFrameBufferConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_fb_config_t *config);

/*!
 * @brief Get default frame buffer configuration.
 *
 * @Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version.
 Apart
 * from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API
 * to get the default configuration for all the 3 layers.
 *
 * The default configuration is
 * @code
    config->enable = true;
    config->enableGamma = false;
    config->format = kLCDIF_PixelFormatRGB565;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void LCDIF_FrameBufferGetDefaultConfig(lcdif_fb_config_t *config);

/*!
 * @brief Set the frame buffer to LCDIF.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param address Frame buffer address.
 * @note The address must be 128 bytes aligned.
 */
static inline void LCDIF_SetFrameBufferAddr(LCDIF_Type *base, uint8_t displayIndex, uint32_t address)
{
    /* The frame buffer address and stride must be aligned. */
    assert(0U == (address & (LCDIF_FB_ALIGN - 1U)));

    base->FRAMEBUFFERADDRESS0 = LCDIF_ADDR_CPU_2_IP(address);
}

/*!
 * @brief Set the frame buffer stride.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param strideBytes The stride in byte.
 */
void LCDIF_SetFrameBufferStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes);

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*!
 * @brief Set the frame buffer to LCDIF for UV plane when the input format is YUV420.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param address Frame buffer address.
 */
static inline void LCDIF_SetFrameBufferUVAddr(LCDIF_Type *base, uint8_t displayIndex, uint32_t address)
{
    /* The frame buffer address and stride must be 64-byte aligned. */
    assert(0U == (address & (LCDIF_FB_ALIGN - 1U)));

    base->DCTILEUVFRAMEBUFFERADR0 = LCDIF_ADDR_CPU_2_IP(address);
}

/*
 * @brief Set the frame buffer stride for UV plane when the input format is YUV420.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param strideBytes The stride in byte.
 */
static inline void LCDIF_SetFrameBufferUVStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes)
{
    base->DCTILEUVFRAMEBUFFERSTR0 = LCDIF_ALIGN_ADDR(strideBytes, LCDIF_FB_ALIGN);
}

/*!
 * @brief Configure the video layer position.
 *
 * @Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version.
 * Apart from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API to
 * configure the legacy video layer, and use @ref LCDIF_SetOverlayLayerPosition to configure the overlay layers.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param topLeftX The x value of thr top-left coordinate.
 * @param topLeftY The y value of thr top-left coordinate.
 * @param width The width of the layer.
 * @param height The height of the layer.
 */
void LCDIF_SetFrameBufferPosition(
    LCDIF_Type *base, uint8_t displayIndex, uint16_t topLeftX, uint16_t topLeftY, uint16_t width, uint16_t height);

/*!
 * @brief Configure the overlay layers for LCDIF frame buffer.
 *
 * @Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version.
 * Apart from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API to
 * configure the overlay layers, and use @ref LCDIF_SetFrameBufferConfig to configure the legacy video layer.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration structure.
 * @param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerConfig(LCDIF_Type *base,
                                 uint8_t displayIndex,
                                 const lcdif_fb_config_t *config,
                                 uint8_t layerIndex);

/*!
 * @brief Configure the overlay layer position.
 *
 * @Note: For LCDIF of version DC8000 there can be 3 layers in the pre-processing, compared with the older version.
 * Apart from the video layer, there are also 2 overlay layers which shares the same configurations. Use this API to
 * configure the overlay layers, and use @ref LCDIF_SetFrameBufferPosition to configure the legacy video layer.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param topLeftX The x value of thr top-left coordinate.
 * @param topLeftY The y value of thr top-left coordinate.
 * @param width The width of the layer.
 * @param height The height of the layer.
 * @param layerIndex Pointer to the configuration structure.
 */
void LCDIF_SetOverlayLayerPosition(LCDIF_Type *base,
                                   uint8_t displayIndex,
                                   uint16_t topLeftX,
                                   uint16_t topLeftY,
                                   uint16_t width,
                                   uint16_t height,
                                   uint8_t layerIndex);

/*!
 * @brief Sets the frame buffer address for overlay layer.
 *
 * @note The address must be 64 bytes aligned.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param address Frame buffer address.
 * @param layerIndex Which layer to configure.
 */
void LCDIF_SetOverlayLayerAddr(LCDIF_Type *base, uint8_t displayIndex, uint32_t address, uint8_t layerIndex);

/*!
 * @brief Sets the frame buffer stride for overlay layer.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param strideBytes The stride in byte.
 * @param layerIndex Which layer to configure.
 */
void LCDIF_SetOverlayLayerStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes, uint8_t layerIndex);

/*!
 * @brief Sets the frame buffer address for overlay layer 0 for UV plane when the input format is YUV420.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param address Frame buffer address.
 */
static inline void LCDIF_SetOverlayLayerUVAddr(LCDIF_Type *base, uint8_t displayIndex, uint32_t address)
{
    /* The frame buffer address and stride must be 32-byte aligned.*/
    assert(0U == (address & (LCDIF_FB_UV_ALIGN - 1U)));

    base->DCTILEUVOVERLAYADR = LCDIF_ADDR_CPU_2_IP(address);
}

/*
 * @brief Sets the frame buffer stride for overlay layer 0 for UV plane when the input format is YUV420.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param strideBytes The stride in byte.
 */
static inline void LCDIF_SetOverlayLayerUVStride(LCDIF_Type *base, uint8_t displayIndex, uint32_t strideBytes)
{
    base->DCTILEUVOVERLAYSTR = LCDIF_ALIGN_ADDR(strideBytes, LCDIF_FB_UV_ALIGN);
}

/*!
 * @brief Sets the color for background layer.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param color Background color in ARGB8888 format.
 */
static inline void LCDIF_SetFrameBufferBackground(LCDIF_Type *base, uint8_t displayIndex, uint32_t color)
{
    base->FRAMEBUFFERBACKGROUND = color;
}

/*!
 * brief Get the alpha blend configuration by porter duff blend mode.
 *
 * param mode The blend mode.
 * param config Pointer to the configuration.
 * retval kStatus_Success Successfully get the configuration.
 * retval kStatus_InvalidArgument The blend mode not supported.
 */
status_t LCDIF_GetPorterDuffConfig(lcdif_porter_duff_blend_mode_t mode, lcdif_layer_alpha_blend_config_t *config);
#endif
/* @} */

#if defined(FSL_FEATURE_LCDIF_VERSION_DC8000) & FSL_FEATURE_LCDIF_VERSION_DC8000
/*!
 * @name Panel control
 * @{
 */

/*!
 * @brief Gets default panel configuration.
 *
 * The default configuration is
 * @code
    config->enable = true;
    config->enableGamma = false;
    config->order       = kLCDIF_VideoOverlay0Overlay1;
    config->endian      = kLCDIF_NoSwap;
   @endcode
 *
 * @param config Pointer to the configuration structure.
 */
void LCDIF_PanelGetDefaultConfig(lcdif_panel_config_t *config);

/*!
 * @brief Configure the LCDIF panel.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param config Pointer to the configuration structure.
 */
void LCDIF_SetPanelConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_panel_config_t *config);

/*!
 * @brief Sets the layer order for the color key and alpha blend precess.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param order The order of the 3 configurable layers.
 */
static inline void LCDIF_SetLayerOrder(LCDIF_Type *base, uint8_t displayIndex, lcdif_layer_order_t order)
{
    base->BLENDSTACKORDER = (uint32_t)order;
}

/*!
 * @brief Sets the endian mode.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param mode The byte order for the endian mode.
 */
static inline void LCDIF_SetEndianMode(LCDIF_Type *base, uint8_t displayIndex, lcdif_endian_mode_t mode)
{
    base->SRCCONFIGENDIAN = (uint32_t)mode;
}

/*!
 * @brief Enables the module to update the new set of configuration in the next frame's VBLANK.
 *
 * @param base LCDIF peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void LCDIF_EnableUpdate(LCDIF_Type *base, bool enable)
{
    base->PANELCONTROL = (uint32_t)enable;
}

/*!
 * @brief Enables the gamma correction.
 *
 * @param base LCDIF peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void LCDIF_EnableGamma(LCDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->PANELFUNCTION |= LCDIF_PANELFUNCTION_GAMMA_MASK;
    }
    else
    {
        base->PANELFUNCTION &= ~LCDIF_PANELFUNCTION_GAMMA_MASK;
    }
}

/*!
 * @brief Enables the panel output.
 *
 * When disables, all pixels will be black which allows a panel to have correct timing without any pixels.
 *
 * @param base LCDIF peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void LCDIF_EnablePanel(LCDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->PANELFUNCTION |= LCDIF_PANELFUNCTION_OUTPUT_MASK;
    }
    else
    {
        base->PANELFUNCTION &= ~LCDIF_PANELFUNCTION_OUTPUT_MASK;
    }
}

/*!
 * @brief Starts the interface mode transfer. Self-clear.
 *
 * All registers will be copied to the working set and resets the pixel counter.
 *
 * @param base LCDIF peripheral base address.
 */
static inline void LCDIF_Start(LCDIF_Type *base)
{
    base->PANELWORKING = LCDIF_PANELWORKING_WORKING_MASK;
}

/*!
 * @brief Resets the module. Self-clear.
 *
 * @param base LCDIF peripheral base address.
 */
static inline void LCDIF_Reset(LCDIF_Type *base)
{
    base->SOFTRESET = LCDIF_SOFTRESET_RESET_MASK;
}

/*!
 * @brief Set the update of the double buffer register ready.
 *
 * Call this API after updating any double buffered register
 * to let the change take effect in next v-blank.
 *
 * @param base LCDIF peripheral base address.
 */
static inline void LCDIF_SetUpdateReady(LCDIF_Type *base)
{
    base->PANELCONTROL |= LCDIF_PANELCONTROL_VALID_MASK;
}
/* @} */
#endif

/*!
 * @name Dither
 * @{
 */

/*!
 * @brief Set the dither configuration.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Index to configure.
 * @param config Pointer to the configuration structure.
 */
void LCDIF_SetDitherConfig(LCDIF_Type *base, uint8_t displayIndex, const lcdif_dither_config_t *config);

/*! @} */

/*!
 * @name Gamma correction
 * @{
 */

/*!
 * @brief Set the gamma translation values to the LCDIF gamma table.
 *
 * @param base LCDIF peripheral base address.
 * @param displayIndex Display index.
 * @param startIndex Start index in the gamma table that the value will be set to.
 * @param gamma The gamma values to set to the gamma table in LCDIF, could be defined using LCDIF_MAKE_GAMMA_VALUE.
 * @param gammaLen The length of the @p gamma.
 */
void LCDIF_SetGammaData(
    LCDIF_Type *base, uint8_t displayIndex, uint16_t startIndex, const uint32_t *gamma, uint16_t gammaLen);

/*! @} */

/*!
 * @name Interrupts
 *
 * The interrupt must be enabled, otherwise the interrupt flags will not assert.
 *
 * @{
 */

/*!
 * @brief Enables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param mask The interrupts to enable, pass in as OR'ed value of @ref _lcdif_interrupt.
 */
static inline void LCDIF_EnableInterrupts(LCDIF_Type *base, uint32_t mask)
{
    base->DISPLAYINTRENABLE |= mask;
}

/*!
 * @brief Disable LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param mask The interrupts to disable, pass in as OR'ed value of @ref _lcdif_interrupt.
 */
static inline void LCDIF_DisableInterrupts(LCDIF_Type *base, uint32_t mask)
{
    base->DISPLAYINTRENABLE &= ~mask;
}

/*!
 * @brief Get and clear LCDIF interrupt pending status.
 *
 * @param base LCDIF peripheral base address.
 * @return The interrupt pending status.
 *
 * @note The interrupt must be enabled, otherwise the interrupt flags will not assert.
 */
static inline uint32_t LCDIF_GetAndClearInterruptPendingFlags(LCDIF_Type *base)
{
    return base->DISPLAYINTR;
}

/*! @} */

/*!
 * @name Cursor
 *
 * Top-left point and Hot spot are two different cursor point.
 *
 *   Top-left point is used as the base address for the cursor.
 *   Hot spot is used in a search for a corresponding screen coordinate when
 *   a selection is made, such as when the "Enter" key or left mouse button
 *   is pushed.
 *
 * @verbatim

     Top-left point
          +-------------------------------+
          |                               |
          |   Hot spot                    |
          |      +-------                 |
          |      |    \                   |
          |      | \   \                  |
          |      |  \   \                 |
          |          \   \                |
          |           \   \               |
          |            \   \              |
          |             \   \             |
          |              \                |
          |                               |
          +-------------------------------+

   @endverbatim
 *
 * For format masked, one cursor pixel is 2bits. 32x32 cursor pixels have 32
 * cursor color rows. Each cursor color row is 64bits.
 *
 * cursorColorRow_H[31:0] = colorRow[63:32]
 * cursorColorRow_L[31:0] = colorRow[31:0]
 * xorCursor = cursorColorRow_H[cursorXPos[4:0]]
 * andCursor = cursorColorRow_L[cursorXPos[4:0]]
 *
 * The output cursor color is:
 *
 *  andCursor    xorCursor          cursor color
 *      0           0           Background register color
 *      0           1           Foreground register color
 *      1           0           Frame buffer pixel color
 *      1           1           Invert frame buffer pixel color
 *
 * @{
 */

/*!
 * @brief Get the hardware cursor default configuration
 *
 * The default configuration values are:
 *
 * @code
    config->enable = true;
    config->format = kLCDIF_CursorMasked;
    config->hotspotOffsetX = 0;
    config->hotspotOffsetY = 0;
   @endcode
 *
 * @param config Pointer to the hardware cursor configuration structure.
 */
void LCDIF_CursorGetDefaultConfig(lcdif_cursor_config_t *config);

/*!
 * @brief Configure the cursor.
 *
 * @param base LCDIF peripheral base address.
 * @param config Cursor configuration.
 */
void LCDIF_SetCursorConfig(LCDIF_Type *base, const lcdif_cursor_config_t *config);

/*!
 * @brief Set the cursor hotspot postion
 *
 * @param base LCDIF peripheral base address.
 * @param x X coordinate of the hotspot, range 0 ~ 8191.
 * @param y Y coordinate of the hotspot, range 0 ~ 8191.
 */
static inline void LCDIF_SetCursorHotspotPosition(LCDIF_Type *base, uint16_t x, uint16_t y)
{
    base->CURSORLOCATION =
        ((uint32_t)y << LCDIF_CURSORLOCATION_Y_SHIFT) | ((uint32_t)x << LCDIF_CURSORLOCATION_X_SHIFT);
}

/*!
 * @brief Set the cursor memory address.
 *
 * @param base LCDIF peripheral base address.
 * @param address Memory address.
 */
static inline void LCDIF_SetCursorBufferAddress(LCDIF_Type *base, uint32_t address)
{
    base->CURSORADDRESS = LCDIF_ADDR_CPU_2_IP(address);
}

/*!
 * @brief Set the cursor color
 *
 * @param base LCDIF peripheral base address.
 * @param background  Background color, could be defined use @ref LCDIF_MAKE_CURSOR_COLOR
 * @param foreground  Foreground color, could be defined use @ref LCDIF_MAKE_CURSOR_COLOR
 */
void LCDIF_SetCursorColor(LCDIF_Type *base, uint32_t background, uint32_t foreground);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_LCDIF_H_ */
