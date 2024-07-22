/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_LCDIFV3_H_
#define FSL_LCDIFV3_H_

#include "fsl_common.h"

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && (0 != FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET))
#include "fsl_memory.h"
#endif

/*!
 * @addtogroup lcdifv3
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief LCDIF v3 driver version */
#define FSL_LCDIFV3_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

#if defined(FSL_FEATURE_LCDIFV3_LAYER_COUNT) && (!defined(LCDIFV3_LAYER_COUNT))
#define LCDIFV3_LAYER_COUNT FSL_FEATURE_LCDIFV3_LAYER_COUNT
#endif

#if defined(FSL_FEATURE_LCDIFV3_LAYER_CSC_COUNT) && (!defined(LCDIFV3_LAYER_CSC_COUNT))
#define LCDIFV3_LAYER_CSC_COUNT FSL_FEATURE_LCDIFV3_LAYER_CSC_COUNT
#endif

#if (defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && (0 != FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET))
#define LCDIFV3_ADDR_CPU_2_IP(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_Local2DMA))
#else
#define LCDIFV3_ADDR_CPU_2_IP(addr) (addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

/*! @brief LCDIF v3 FIFO empty interrupt. */
#define LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 24U))
/*! @brief LCDIF v3 DMA done interrupt. */
#define LCDIFV3_MAKE_DMA_DONE_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 16U))
/*! @brief LCDIF v3 DMA error interrupt. */
#define LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(layer) (1UL << ((uint32_t)(layer) + 8U))


/*!
 * @brief LCDIF v3 signal polarity flags
 */
enum _lcdifv3_polarity_flags
{
    kLCDIFV3_VsyncActiveHigh          = 0U, /*!< VSYNC active high. */
    kLCDIFV3_HsyncActiveHigh          = 0U, /*!< HSYNC active high. */
    kLCDIFV3_DataEnableActiveHigh     = 0U, /*!< Data enable line active high. */
    kLCDIFV3_DriveDataOnRisingClkEdge = 0U, /*!< Output data on rising clock edge, capture data
                                                 on falling clock edge. */
    kLCDIFV3_DataActiveHigh = 0U,           /*!< Data active high. */

    kLCDIFV3_VsyncActiveLow            = LCDIF_CTRL_INV_VS_MASK,   /*!< VSYNC active low. */
    kLCDIFV3_HsyncActiveLow            = LCDIF_CTRL_INV_HS_MASK,   /*!< HSYNC active low. */
    kLCDIFV3_DataEnableActiveLow       = LCDIF_CTRL_INV_DE_MASK,   /*!< Data enable line active low. */
    kLCDIFV3_DriveDataOnFallingClkEdge = LCDIF_CTRL_INV_PXCK_MASK, /*!< Output data on falling clock edge, capture
                                                                        data on rising clock edge. */
    kLCDIFV3_DataActiveLow = LCDIF_CTRL_NEG_MASK,                  /*!< Data active high. */
};

/*!
 * @brief The LCDIF v3 interrupts.
 */
enum _lcdifv3_interrupt
{
    kLCDIFV3_Layer0FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(0), /*!< Layer 0 FIFO empty. */
    kLCDIFV3_Layer1FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(1), /*!< Layer 1 FIFO empty. */
    kLCDIFV3_Layer2FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(2), /*!< Layer 2 FIFO empty. */
    kLCDIFV3_Layer3FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(3), /*!< Layer 3 FIFO empty. */
    kLCDIFV3_Layer4FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(4), /*!< Layer 4 FIFO empty. */
    kLCDIFV3_Layer5FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(5), /*!< Layer 5 FIFO empty. */
    kLCDIFV3_Layer6FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(6), /*!< Layer 6 FIFO empty. */
    kLCDIFV3_Layer7FifoEmptyInterrupt  = LCDIFV3_MAKE_FIFO_EMPTY_INTERRUPT(7), /*!< Layer 7 FIFO empty. */
    kLCDIFV3_Layer0DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(0),   /*!< Layer 0 DMA done. */
    kLCDIFV3_Layer1DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(1),   /*!< Layer 1 DMA done. */
    kLCDIFV3_Layer2DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(2),   /*!< Layer 2 DMA done. */
    kLCDIFV3_Layer3DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(3),   /*!< Layer 3 DMA done. */
    kLCDIFV3_Layer4DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(4),   /*!< Layer 4 DMA done. */
    kLCDIFV3_Layer5DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(5),   /*!< Layer 5 DMA done. */
    kLCDIFV3_Layer6DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(6),   /*!< Layer 6 DMA done. */
    kLCDIFV3_Layer7DmaDoneInterrupt    = LCDIFV3_MAKE_DMA_DONE_INTERRUPT(7),   /*!< Layer 7 DMA done. */
    kLCDIFV3_Layer0DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(0),  /*!< Layer 0 DMA error. */
    kLCDIFV3_Layer1DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(1),  /*!< Layer 1 DMA error. */
    kLCDIFV3_Layer2DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(2),  /*!< Layer 2 DMA error. */
    kLCDIFV3_Layer3DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(3),  /*!< Layer 3 DMA error. */
    kLCDIFV3_Layer4DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(4),  /*!< Layer 4 DMA error. */
    kLCDIFV3_Layer5DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(5),  /*!< Layer 5 DMA error. */
    kLCDIFV3_Layer6DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(6),  /*!< Layer 6 DMA error. */
    kLCDIFV3_Layer7DmaErrorInterrupt   = LCDIFV3_MAKE_DMA_ERROR_INTERRUPT(7),  /*!< Layer 7 DMA error. */
    kLCDIFV3_VerticalBlankingInterrupt = (1U << 2U), /*!< Start of vertical blanking period. */
    kLCDIFV3_OutputUnderrunInterrupt   = (1U << 1U), /*!< Output buffer underrun. */
    kLCDIFV3_VsyncEdgeInterrupt        = (1U << 0U), /*!< Interrupt at VSYNC edge. */
};

/*! @brief The LCDIF v3 output line order. */
typedef enum _lcdifv3_line_order
{
    kLCDIFV3_LineOrderRGBOrYUV = 0,    /*!< RGB/YUV */
    kLCDIFV3_LineOrderRBG,             /*!< RBG */
    kLCDIFV3_LineOrderGBR,             /*!< GBR */
    kLCDIFV3_LineOrderGRBOrUYV,        /*!< GRB/UYV */
    kLCDIFV3_LineOrderBRG,             /*!< BRG */
    kLCDIFV3_LineOrderBGR,             /*!< BGR */
    kLCDIFV3_LineOrderRGB555,          /*!< RGB555 */
    kLCDIFV3_LineOrderRGB565,          /*!< RGB565 */
    kLCDIFV3_LineOrderYUYVAt15To0,     /*!< YUYV at [15:0] */
    kLCDIFV3_LineOrderUYVYAt15To0,     /*!< UYVY at [15:0] */
    kLCDIFV3_LineOrderYVYUAt15To0,     /*!< YVYU at [15:0] */
    kLCDIFV3_LineOrderVYUYAt15To0,     /*!< VYUY at [15:0] */
    kLCDIFV3_LineOrderYUYVAt23To8,     /*!< YUYV at [23:8] */
    kLCDIFV3_LineOrderUYVYAt23To8,     /*!< UYVY at [23:8] */
    kLCDIFV3_LineOrderYVYUAt23To8,     /*!< YVYU at [23:8] */
    kLCDIFV3_LineOrderVYUYAt23To8,     /*!< VYUY at [23:8] */
} lcdifv3_line_order_t;

/*!
 * @brief LCDIF v3 display configure structure.
 */
typedef struct _lcdifv3_display_config
{
    uint16_t panelWidth;    /*!< Display panel width, pixels per line. */
    uint16_t panelHeight;   /*!< Display panel height, how many lines per panel. */
    uint8_t hsw;            /*!< HSYNC pulse width. */
    uint8_t hfp;            /*!< Horizontal front porch. */
    uint8_t hbp;            /*!< Horizontal back porch. */
    uint8_t vsw;            /*!< VSYNC pulse width. */
    uint8_t vfp;            /*!< Vrtical front porch. */
    uint8_t vbp;            /*!< Vertical back porch. */
    uint32_t polarityFlags; /*!< OR'ed value of @ref _lcdifv3_polarity_flags, used to contol the signal polarity. */
    lcdifv3_line_order_t lineOrder; /*!< Line order. */
} lcdifv3_display_config_t;

/*! @brief LCDIF v3 color space conversion mode. */
typedef enum _lcdifv3_csc_mode
{
    kLCDIFV3_CscYUV2RGB = 0U,   /*!< YUV to RGB. */
    kLCDIFV3_CscYCbCr2RGB,      /*!< YCbCr to RGB. */
    kLCDIFV3_CscRGB2YUV,        /*!< RGB to YUV. */
    kLCDIFV3_CscRGB2YCbCr,      /*!< RGB to YCbCr. */
} lcdifv3_csc_mode_t;

/*! @brief LCDIF v3 pixel format. */
typedef enum _lcdifv3_pixel_format
{
    kLCDIFV3_PixelFormatRGB565    = LCDIF_CTRLDESCL_5_BPP(4U),   /*!< RGB565, two pixels use 32 bits. */
    kLCDIFV3_PixelFormatARGB1555  = LCDIF_CTRLDESCL_5_BPP(5U),   /*!< ARGB1555, two pixels use 32 bits. */
    kLCDIFV3_PixelFormatARGB4444  = LCDIF_CTRLDESCL_5_BPP(6U),   /*!< ARGB4444, two pixels use 32 bits. */
    kLCDIFV3_PixelFormatYVYU      = LCDIF_CTRLDESCL_5_BPP(7U) |
                               LCDIF_CTRLDESCL_5_YUV_FORMAT(0U), /*!< YVYU {Y2,V1,Y1,U1} */
    kLCDIFV3_PixelFormatYUYV = LCDIF_CTRLDESCL_5_BPP(7U) |
                               LCDIF_CTRLDESCL_5_YUV_FORMAT(1U), /*!< YUYV {Y2,U1,Y1,V1} */
    kLCDIFV3_PixelFormatVYUY = LCDIF_CTRLDESCL_5_BPP(7U) |
                               LCDIF_CTRLDESCL_5_YUV_FORMAT(2U), /*!< VYUY {V1,Y2,U1,Y1} */
    kLCDIFV3_PixelFormatUYVY = LCDIF_CTRLDESCL_5_BPP(7U) |
                               LCDIF_CTRLDESCL_5_YUV_FORMAT(3U), /*!< UYVY {U1,Y2,V1,Y1} */
    kLCDIFV3_PixelFormatRGB888   = LCDIF_CTRLDESCL_5_BPP(8U),    /*!< RGB888 packed, one pixel uses 24 bits. */
    kLCDIFV3_PixelFormatARGB8888 = LCDIF_CTRLDESCL_5_BPP(9U),    /*!< ARGB8888 unpacked, one pixel uses 32 bits. */
    kLCDIFV3_PixelFormatABGR8888 = LCDIF_CTRLDESCL_5_BPP(10U),   /*!< ABGR8888 unpacked, one pixel uses 32 bits. */
} lcdifv3_pixel_format_t;

/*! @brief LCDIF v3 source buffer configuration. */
typedef struct _lcdifv3_buffer_config
{
    uint16_t strideBytes;
    lcdifv3_pixel_format_t pixelFormat; /*!< Source buffer pixel format. */
} lcdifv3_buffer_config_t;

/*!
 * @brief LCDIF v3 PoterDuff alpha mode.
 */
typedef enum _lcdifv3_pd_alpha_mode
{
    kLCDIFV3_PD_AlphaStraight = 0, /*!< Straight mode. */
    kLCDIFV3_PD_AlphaInversed = 1, /*!< Inversed mode. */
} lcdifv3_pd_alpha_mode_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name LCDIF v3 initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the LCDIF v3.
 *
 * This function ungates the LCDIF v3 clock and release the peripheral reset.
 *
 * @param base LCDIF v3 peripheral base address.
 */
void LCDIFV3_Init(LCDIF_Type *base);

/*!
 * @brief Deinitializes the LCDIF peripheral.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV3_Deinit(LCDIF_Type *base);

/*!
 * @brief Reset the LCDIF v3.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV3_Reset(LCDIF_Type *base);

/*! @} */

/*!
 * @name Display
 * @{
 */

/*!
 * @brief Gets the LCDIF display default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * @code
    config->panelWidth    = 0U;
    config->panelHeight   = 0U;
    config->hsw           = 3U;
    config->hfp           = 3U;
    config->hbp           = 3U;
    config->vsw           = 3U;
    config->vfp           = 3U;
    config->vbp           = 3U;
    config->polarityFlags = kLCDIFV3_VsyncActiveHigh | kLCDIFV3_HsyncActiveHigh | kLCDIFV3_DataEnableActiveHigh |
                            kLCDIFV3_DriveDataOnRisingClkEdge | kLCDIFV3_DataActiveHigh;
    config->lineOrder       = kLCDIFV3_LineOrderRGB;
    @endcode
 *
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV3_DisplayGetDefaultConfig(lcdifv3_display_config_t *config);

/*!
 * @brief Set the LCDIF v3 display configurations.
 *
 * @param base LCDIF peripheral base address.
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV3_SetDisplayConfig(LCDIF_Type *base, const lcdifv3_display_config_t *config);

/*!
 * @brief Enable or disable the display
 *
 * @param base LCDIF peripheral base address.
 * @param enable Enable or disable.
 */
static inline void LCDIFV3_EnableDisplay(LCDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->DISP_PARA |= LCDIF_DISP_PARA_DISP_ON_MASK;
    }
    else
    {
        base->DISP_PARA &= ~LCDIF_DISP_PARA_DISP_ON_MASK;
    }
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param mask interrupt source, OR'ed value of _lcdifv3_interrupt.
 */
static inline void LCDIFV3_EnableInterrupts(LCDIF_Type *base, uint32_t mask)
{
    base->INT_ENABLE_D0 |= mask;
}

/*!
 * @brief Disables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask interrupt source, OR'ed value of _lcdifv3_interrupt.
 */
static inline void LCDIFV3_DisableInterrupts(LCDIF_Type *base, uint8_t domain, uint32_t mask)
{
    if (domain == 0U)
        base->INT_ENABLE_D0 &= ~mask;
    else
        base->INT_ENABLE_D1 &= ~mask; 
}

/*!
 * @brief Get LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @return Interrupt pending status, OR'ed value of _lcdifv3_interrupt.
 */
static inline uint32_t LCDIFV3_GetInterruptStatus(LCDIF_Type *base)
{
    return base->INT_STATUS_D0;
}

/*!
 * @brief Clear LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @param mask of the flags to clear, OR'ed value of _lcdifv3_interrupt.
 */
static inline void LCDIFV3_ClearInterruptStatus(LCDIF_Type *base, uint32_t mask)
{
    base->INT_STATUS_D0 = mask;
}

/*! @} */


/*!
 * @name Layer operation
 * @{
 */

/*!
 * @brief Set the layer dimension.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param width Layer width in pixel.
 * @param height Layer height.
 *
 * @note The layer width must be in multiples of the number of pixels that can be stored in 32 bits
 */
static inline void LCDIFV3_SetLayerSize(LCDIF_Type *base, uint8_t layerIndex, uint16_t width, uint16_t height)
{
    base->CTRLDESCL_1 =
        ((uint32_t)height << LCDIF_CTRLDESCL_1_HEIGHT_SHIFT) | ((uint32_t)width << LCDIF_CTRLDESCL_1_WIDTH_SHIFT);
}

/*!
 * @brief Set the layer source buffer configuration.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param config Pointer to the configuration.
 */
void LCDIFV3_SetLayerBufferConfig(LCDIF_Type *base, uint8_t layerIndex, const lcdifv3_buffer_config_t *config);

/*!
 * @brief Set the layer source buffer address.
 *
 * This function is used for fast runtime source buffer change.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param addr The new source buffer address passed to the layer, should be 64-bit aligned.
 */
static inline void LCDIFV3_SetLayerBufferAddr(LCDIF_Type *base, uint8_t layerIndex, uint32_t addr)
{
    base->CTRLDESCL_LOW_4 = LCDIFV3_ADDR_CPU_2_IP(addr);
}

/*!
 * @brief Enable or disable the layer.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param enable Pass in true to enable, false to disable.
 */

static inline void LCDIFV3_EnableLayer(LCDIF_Type *base, uint8_t layerIndex, bool enable)
{
    if (enable)
    {
        base->CTRLDESCL_5 |= LCDIF_CTRLDESCL_5_EN_MASK;
    }
    else
    {
        base->CTRLDESCL_5 &= ~LCDIF_CTRLDESCL_5_EN_MASK;
    }
}


/*!
 * @brief Trigger the layer configuration shadow load.
 *
 * The new layer configurations are written to the shadow registers first,
 * When all configurations written finished, call this function, then shadowed
 * control registers are updated to the active control registers on VSYNC of
 * next frame.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Layer layerIndex.
 */
static inline void LCDIFV3_TriggerLayerShadowLoad(LCDIF_Type *base, uint8_t layerIndex)
{
    base->CTRLDESCL_5 |= LCDIF_CTRLDESCL_5_SHADOW_LOAD_EN_MASK;
}

/*!
 * @brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * @param base LCDIFv3 peripheral base address.
 * @param layerIndex Index of the layer.
 * @param mode The conversion mode.
 */
void LCDIFV3_SetCscMode(LCDIF_Type *base, lcdifv3_csc_mode_t mode);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /*FSL_LCDIFV3_H_*/
