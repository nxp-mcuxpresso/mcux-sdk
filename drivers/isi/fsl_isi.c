/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_isi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.isi"
#endif

/* The macros for color space convertion. */
#define ISI_CSC_COEFF_FRAC_BITS  8U
#define ISI_CSC_COEFF_SIGN_SHIFT 10U
#define ISI_CSC_COEFF_MAX        3.99609375 /* 11.11111111b */

/* The number of output buffer. */
#define ISI_OUT_BUFFER_CNT 2U

typedef union _isi_u32_f32
{
    float f32;
    uint32_t u32;
} isi_u32_f32_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for ISI module.
 *
 * @param base ISI peripheral base address.
 */
static uint32_t ISI_GetInstance(ISI_Type *base);

/*!
 * @brief Convert IEEE 754 float value to the value could be written to registers.
 *
 * This function converts the float value to integer value to set the scaler
 * and CSC parameters.
 *
 * @param floatValue The float value to convert.
 * @param intBits Bits number of integer part in result.
 * @param fracBits Bits number of fractional part in result.
 * @return The value to set to register.
 */
static uint32_t ISI_ConvertFloat(float floatValue, uint8_t intBits, uint8_t fracBits);

/*!
 * @brief Convert the desired scale fact to pre-decimation (DEC) and SCALE_FACTO.
 *
 * @param inputDimension Input dimension.
 * @param outputDimension Output dimension.
 * @param dec The decimation value.
 * @param scale The scale value set to register SCALE_FACTOR.
 */
static void ISI_GetScalerParam(uint16_t inputDimension, uint16_t outputDimension, uint8_t *dec, uint32_t *scale);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to ISI bases for each instance. */
static ISI_Type *const s_isiBases[] = ISI_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to isi clocks for each instance. */
static const clock_ip_name_t s_isiClocks[] = ISI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/
static void ISI_GetScalerParam(uint16_t inputDimension, uint16_t outputDimension, uint8_t *dec, uint32_t *scale)
{
    uint32_t scaleFact = ((uint32_t)inputDimension << 12U) / outputDimension;

    if (scaleFact >= (16UL << 12U))
    {
        /* Desired fact is two large, use the largest support value. */
        *dec   = 3U;
        *scale = 0x2000U;
    }
    else
    {
        if (scaleFact > (8UL << 12U))
        {
            *dec = 3U;
        }
        else if (scaleFact > (4UL << 12U))
        {
            *dec = 2U;
        }
        else if (scaleFact > (2UL << 12U))
        {
            *dec = 1U;
        }
        else
        {
            *dec = 0U;
        }

        *scale = scaleFact >> (*dec);

        if (0U == *scale)
        {
            *scale = 1U;
        }
    }
}

static uint32_t ISI_GetInstance(ISI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_isiBases); instance++)
    {
        if (s_isiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_isiBases));

    return instance;
}

static uint32_t ISI_ConvertFloat(float floatValue, uint8_t intBits, uint8_t fracBits)
{
    /* One bit reserved for sign bit. */
    assert(intBits + fracBits < 32U);

    isi_u32_f32_t u32_f32;
    uint32_t ret;
    uint32_t expBits;

    u32_f32.f32        = floatValue;
    uint32_t floatBits = u32_f32.u32;
    expBits            = (floatBits & 0x7F800000U) >> 23U;
    int32_t expValue   = (int32_t)expBits - 127;

    ret = (floatBits & 0x007FFFFFU) | 0x00800000U;
    expValue += (int32_t)fracBits;

    if (expValue < 0)
    {
        return 0U;
    }
    else if (expValue > 23)
    {
        /* should not exceed 31-bit when left shift. */
        assert((expValue - 23) <= 7);
        ret <<= ((uint32_t)expValue - 23UL);
    }
    else
    {
        ret >>= (23UL - (uint32_t)expValue);
    }

    /* Set the sign bit. */
    if (0U != (floatBits & 0x80000000UL))
    {
        ret = ((~ret) + 1U) & ~(((uint32_t)-1) << (intBits + fracBits + 1U));
    }

    return ret;
}

/*!
 * brief Initializes the ISI peripheral.
 *
 * This function ungates the ISI clock, it should be called before any other
 * ISI functions.
 *
 * param base ISI peripheral base address.
 */
void ISI_Init(ISI_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the clock. */
    (void)CLOCK_EnableClock(s_isiClocks[ISI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable channel clock. */
    ISI_Reset(base);
    base->CHNL_CTRL = ISI_CHNL_CTRL_CLK_EN_MASK;
}

/*!
 * brief Deinitializes the ISI peripheral.
 *
 * This function gates the ISI clock.
 *
 * param base ISI peripheral base address.
 */
void ISI_Deinit(ISI_Type *base)
{
    ISI_Reset(base);
    /* Stop channel, disable the channel clock. */
    base->CHNL_CTRL = 0U;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable the clock. */
    (void)CLOCK_DisableClock(s_isiClocks[ISI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Reset the ISI peripheral.
 *
 * This function resets the ISI channel processing pipeline similar to a hardware
 * reset. The channel will need to be reconfigured after reset before it can be used.
 *
 * param base ISI peripheral base address.
 */
void ISI_Reset(ISI_Type *base)
{
    base->CHNL_CTRL |= ISI_CHNL_CTRL_SW_RST_MASK;
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    base->CHNL_CTRL &= ~ISI_CHNL_CTRL_SW_RST_MASK;
}

/*!
 * brief Set the ISI channel basic configurations.
 *
 * This function sets the basic configurations, generally the channel could be
 * started to work after this function. To enable other features such as croping,
 * flipping, please call the functions accordingly.
 *
 * param base ISI peripheral base address
 * param config Pointer to the configuration structure.
 */
void ISI_SetConfig(ISI_Type *base, const isi_config_t *config)
{
    assert(NULL != config);

    uint32_t reg;

    /* Set control bit fields in register CHNL_CTRL. */
    reg = base->CHNL_CTRL;
    reg &= ~(ISI_CHNL_CTRL_CHNL_BYPASS_MASK | ISI_CHNL_CTRL_CHAIN_BUF_MASK | ISI_CHNL_CTRL_BLANK_PXL_MASK |
             ISI_CHNL_CTRL_MIPI_VC_ID_MASK | ISI_CHNL_CTRL_SRC_TYPE_MASK | ISI_CHNL_CTRL_SRC_MASK);
    reg |= ISI_CHNL_CTRL_CHNL_BYPASS(config->isChannelBypassed) | ISI_CHNL_CTRL_CHAIN_BUF(config->chainMode) |
           ISI_CHNL_CTRL_BLANK_PXL(config->blankPixel) | ISI_CHNL_CTRL_MIPI_VC_ID(config->mipiChannel) |
           ISI_CHNL_CTRL_SRC_TYPE(config->isSourceMemory) | ISI_CHNL_CTRL_SRC(config->sourcePort);
    base->CHNL_CTRL = reg;

    /* Set control bit fields in register CHNL_IMG_CTRL. */
    reg = base->CHNL_IMG_CTRL;
    reg &= ~(ISI_CHNL_IMG_CTRL_FORMAT_MASK | ISI_CHNL_IMG_CTRL_DEINT_MASK | ISI_CHNL_IMG_CTRL_YCBCR_MODE_MASK);
    reg |= ISI_CHNL_IMG_CTRL_FORMAT(config->outputFormat) | ISI_CHNL_IMG_CTRL_DEINT(config->deintMode) |
           ISI_CHNL_IMG_CTRL_YCBCR_MODE(config->isYCbCr);
    base->CHNL_IMG_CTRL = reg;

    base->CHNL_IMG_CFG = ((uint32_t)(config->inputHeight) << ISI_CHNL_IMG_CFG_HEIGHT_SHIFT) |
                         ((uint32_t)(config->inputWidth) << ISI_CHNL_IMG_CFG_WIDTH_SHIFT);

    base->CHNL_SCL_IMG_CFG =
        ISI_CHNL_SCL_IMG_CFG_WIDTH(config->inputWidth) | ISI_CHNL_SCL_IMG_CFG_HEIGHT(config->inputHeight);

    /* Set output buffer configuration. */
    base->CHNL_OUT_BUF_PITCH = config->outputLinePitchBytes;

    /* Set channel buffer panic threshold. */
    reg = base->CHNL_OUT_BUF_CTRL;
    reg &= ~(ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_V_MASK | ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_U_MASK |
             ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_Y_MASK);
    reg |= ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_V(config->thresholdV) |
           ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_U(config->thresholdU) |
           ISI_CHNL_OUT_BUF_CTRL_OFLW_PANIC_SET_THD_Y(config->thresholdY);
    base->CHNL_OUT_BUF_CTRL = reg;
}

/*!
 * brief Get the ISI channel default basic configurations.
 *
 * The default value is:
 * code
    config->isChannelBypassed = false;
    config->isSourceMemory = false;
    config->isYCbCr = false;
    config->chainMode = kISI_ChainDisable;
    config->deintMode = kISI_DeintDisable;
    config->blankPixel = 0xFFU;
    config->sourcePort = 0U;
    config->mipiChannel = 0U;
    config->inputHeight = 1080U;
    config->inputWidth = 1920U;
    config->outputFormat = kISI_OutputRGBA8888;
    config->outputLinePitchBytes = 0U;
    config->thresholdY = kISI_ThresholdDisable;
    config->thresholdU = kISI_ThresholdDisable;
    config->thresholdV = kISI_ThresholdDisable;
   endcode
 *
 * param config Pointer to the configuration structure.
 */
void ISI_GetDefaultConfig(isi_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->isChannelBypassed    = false;
    config->isSourceMemory       = false;
    config->isYCbCr              = false;
    config->chainMode            = kISI_ChainDisable;
    config->deintMode            = kISI_DeintDisable;
    config->blankPixel           = 0xFFU;
    config->sourcePort           = 0U;
    config->mipiChannel          = 0U;
    config->inputHeight          = 1080U;
    config->inputWidth           = 1920U;
    config->outputFormat         = kISI_OutputRGBA8888;
    config->outputLinePitchBytes = 0U;
    config->thresholdY           = kISI_ThresholdDisable;
    config->thresholdU           = kISI_ThresholdDisable;
    config->thresholdV           = kISI_ThresholdDisable;
}

/*!
 * brief Set the ISI channel scaler configurations.
 *
 * This function sets the scaling configurations. If the ISI channel is bypassed,
 * then the scaling feature could not be used.
 *
 * ISI only supports down scaling but not up scaling.
 *
 * param base ISI peripheral base address
 * param inputWidth Input image width.
 * param inputHeight Input image height.
 * param outputWidth Output image width.
 * param outputHeight Output image height.
 * note Total bytes in one line after down scaling must be more than 256 bytes.
 */
void ISI_SetScalerConfig(
    ISI_Type *base, uint16_t inputWidth, uint16_t inputHeight, uint16_t outputWidth, uint16_t outputHeight)
{
    uint8_t decX, decY;
    uint32_t scaleX, scaleY;

    ISI_GetScalerParam(inputWidth, outputWidth, &decX, &scaleX);
    ISI_GetScalerParam(inputHeight, outputHeight, &decY, &scaleY);

    /* Set the pre-decimation configuration. */
    base->CHNL_IMG_CTRL = (base->CHNL_IMG_CTRL & ~(ISI_CHNL_IMG_CTRL_DEC_X_MASK | ISI_CHNL_IMG_CTRL_DEC_Y_MASK)) |
                          ISI_CHNL_IMG_CTRL_DEC_X(decX) | ISI_CHNL_IMG_CTRL_DEC_Y(decY);

    /* Set the bilinear scaler engine configuration. */
    /* The scaler factor is represented as ##.####_####_#### in register. */
    base->CHNL_SCALE_FACTOR = ISI_CHNL_SCALE_FACTOR_X_SCALE(scaleX) | ISI_CHNL_SCALE_FACTOR_Y_SCALE(scaleY);

    base->CHNL_SCL_IMG_CFG = ISI_CHNL_SCL_IMG_CFG_WIDTH(outputWidth) | ISI_CHNL_SCL_IMG_CFG_HEIGHT(outputHeight);
}

/*!
 * brief Set the ISI color space conversion configurations.
 *
 * This function sets the color space conversion configurations. After setting
 * the configuration, use the function ref ISI_EnableColorSpaceConversion to
 * enable this feature. If the ISI channel is bypassed, then the color space
 * conversion feature could not be used.
 *
 * param base ISI peripheral base address
 * param config Pointer to the configuration structure.
 */
void ISI_SetColorSpaceConversionConfig(ISI_Type *base, const isi_csc_config_t *config)
{
    assert(NULL != config);
    uint32_t coeff;

    /*
     * The CSC coefficient has a sign bit, 2 bits integer, and 8 bits of fraction as ###.####_####.
     * This function converts the float value to the register format.
     */
    coeff = (ISI_ConvertFloat(config->A1, 2, 8) << ISI_CHNL_CSC_COEFF0_A1_SHIFT);
    coeff |= (ISI_ConvertFloat(config->A2, 2, 8) << ISI_CHNL_CSC_COEFF0_A2_SHIFT);
    base->CHNL_CSC_COEFF0 = coeff;

    coeff = (ISI_ConvertFloat(config->A3, 2, 8) << ISI_CHNL_CSC_COEFF1_A3_SHIFT);
    coeff |= (ISI_ConvertFloat(config->B1, 2, 8) << ISI_CHNL_CSC_COEFF1_B1_SHIFT);
    base->CHNL_CSC_COEFF1 = coeff;

    coeff = (ISI_ConvertFloat(config->B2, 2, 8) << ISI_CHNL_CSC_COEFF2_B2_SHIFT);
    coeff |= (ISI_ConvertFloat(config->B3, 2, 8) << ISI_CHNL_CSC_COEFF2_B3_SHIFT);
    base->CHNL_CSC_COEFF2 = coeff;

    coeff = (ISI_ConvertFloat(config->C1, 2, 8) << ISI_CHNL_CSC_COEFF3_C1_SHIFT);
    coeff |= (ISI_ConvertFloat(config->C2, 2, 8) << ISI_CHNL_CSC_COEFF3_C2_SHIFT);
    base->CHNL_CSC_COEFF3 = coeff;

    base->CHNL_CSC_COEFF4 =
        (ISI_ConvertFloat(config->C3, 2, 8) << ISI_CHNL_CSC_COEFF4_C3_SHIFT) | ISI_CHNL_CSC_COEFF4_D1(config->D1);
    base->CHNL_CSC_COEFF5 = ISI_CHNL_CSC_COEFF5_D2(config->D2) | ISI_CHNL_CSC_COEFF5_D3(config->D3);

    base->CHNL_IMG_CTRL =
        (base->CHNL_IMG_CTRL & ~ISI_CHNL_IMG_CTRL_CSC_MODE_MASK) | ISI_CHNL_IMG_CTRL_CSC_MODE(config->mode);
}

/*!
 * brief Get the ISI color space conversion default configurations.
 *
 * The default value is:
 * code
    config->mode = kISI_CscYUV2RGB;
    config->A1 = 0.0;
    config->A2 = 0.0;
    config->A3 = 0.0;
    config->B1 = 0.0;
    config->B2 = 0.0;
    config->B3 = 0.0;
    config->C1 = 0.0;
    config->C2 = 0.0;
    config->C3 = 0.0;
    config->D1 = 0;
    config->D2 = 0;
    config->D3 = 0;
   endcode
 *
 * param config Pointer to the configuration structure.
 */
void ISI_ColorSpaceConversionGetDefaultConfig(isi_csc_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->mode = kISI_CscYUV2RGB;
    config->A1   = 0.0f;
    config->A2   = 0.0f;
    config->A3   = 0.0f;
    config->B1   = 0.0f;
    config->B2   = 0.0f;
    config->B3   = 0.0f;
    config->C1   = 0.0f;
    config->C2   = 0.0f;
    config->C3   = 0.0f;
    config->D1   = 0;
    config->D2   = 0;
    config->D3   = 0;
}

/*!
 * brief Set the ISI cropping configurations.
 *
 * This function sets the cropping configurations. After setting the configuration,
 * use the function ref ISI_EnableCrop to enable the feature. Cropping still
 * works when the ISI channel is bypassed.
 *
 * param base ISI peripheral base address
 * param config Pointer to the configuration structure.
 * note The upper left corner and lower right corner should be configured base on
 * the image resolution output from the scaler.
 */
void ISI_SetCropConfig(ISI_Type *base, const isi_crop_config_t *config)
{
    assert(NULL != config);

    base->CHNL_CROP_ULC = ISI_CHNL_CROP_ULC_X(config->upperLeftX) | ISI_CHNL_CROP_ULC_Y(config->upperLeftY);
    base->CHNL_CROP_LRC = ISI_CHNL_CROP_LRC_X(config->lowerRightX) | ISI_CHNL_CROP_LRC_Y(config->lowerRightY);
}

/*!
 * brief Get the ISI cropping default configurations.
 *
 * The default value is:
 * code
    config->upperLeftX = 0U;
    config->upperLeftY = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
   endcode
 *
 * param config Pointer to the configuration structure.
 */
void ISI_CropGetDefaultConfig(isi_crop_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->upperLeftX  = 0U;
    config->upperLeftY  = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
}

/*!
 * brief Set the alpha value for region of interest.
 *
 * Set the alpha insertion configuration for specific region of interest.
 * The function ref ISI_EnableRegionAlpha could be used to enable the alpha
 * insertion. Alpha insertion still works when channel bypassed.
 *
 * param base ISI peripheral base address
 * param index Index of the region of interest, Could be 0, 1, 2, and 3.
 * param config Pointer to the configuration structure.
 * note The upper left corner and lower right corner should be configured base on
 * the image resolution output from the scaler.
 */
void ISI_SetRegionAlphaConfig(ISI_Type *base, uint8_t index, const isi_region_alpha_config_t *config)
{
    assert(NULL != config);
    assert(index < ISI_ROI_NUM);

    uint32_t reg                    = base->ROI[index].CHNL_ROI_ALPHA & ~ISI_CHNL_ROI_ALPHA_ALPHA_MASK;
    base->ROI[index].CHNL_ROI_ALPHA = reg | ISI_CHNL_ROI_ALPHA_ALPHA(config->alpha);

    base->ROI[index].CHNL_ROI_ULC = ISI_CHNL_ROI_ULC_X(config->upperLeftX) | ISI_CHNL_ROI_ULC_Y(config->upperLeftY);
    base->ROI[index].CHNL_ROI_LRC = ISI_CHNL_ROI_LRC_X(config->lowerRightX) | ISI_CHNL_ROI_LRC_Y(config->lowerRightY);
}

/*!
 * brief Get the regional alpha insertion default configurations.
 *
 * The default configuration is:
 * code
    config->upperLeftX = 0U;
    config->upperLeftY = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
    config->alpha = 0U;
   endcode
 *
 * param config Pointer to the configuration structure.
 */
void ISI_RegionAlphaGetDefaultConfig(isi_region_alpha_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->upperLeftX  = 0U;
    config->upperLeftY  = 0U;
    config->lowerRightX = 0U;
    config->lowerRightY = 0U;
    config->alpha       = 0U;
}

/*!
 * brief Enable or disable the alpha value insertion for region of interest.
 *
 * Alpha insertion still works when channel bypassed.
 *
 * param base ISI peripheral base address
 * param index Index of the region of interest, Could be 0, 1, 2, and 3.
 * param enable True to enable, false to disable.
 */
void ISI_EnableRegionAlpha(ISI_Type *base, uint8_t index, bool enable)
{
    assert(index < ISI_ROI_NUM);

    if (enable)
    {
        base->ROI[index].CHNL_ROI_ALPHA |= ISI_CHNL_ROI_ALPHA_ALPHA_EN_MASK;
    }
    else
    {
        base->ROI[index].CHNL_ROI_ALPHA &= ~ISI_CHNL_ROI_ALPHA_ALPHA_EN_MASK;
    }
}

/*!
 * brief Set the input memory configuration.
 *
 * param base ISI peripheral base address
 * param config Pointer to the configuration structure.
 */
void ISI_SetInputMemConfig(ISI_Type *base, const isi_input_mem_config_t *config)
{
    assert(NULL != config);

    uint32_t reg;

    base->CHNL_IN_BUF_ADDR  = config->adddr;
    base->CHNL_IN_BUF_PITCH = ISI_CHNL_IN_BUF_PITCH_FRM_PITCH(config->framePitchBytes) |
                              ISI_CHNL_IN_BUF_PITCH_LINE_PITCH(config->linePitchBytes);

    reg = base->CHNL_MEM_RD_CTRL;
    reg &= ~ISI_CHNL_MEM_RD_CTRL_IMG_TYPE_MASK;
    reg |= ISI_CHNL_MEM_RD_CTRL_IMG_TYPE(config->format);
    base->CHNL_MEM_RD_CTRL = reg;
}

/*!
 * brief Get the input memory default configurations.
 *
 * The default configuration is:
 * code
    config->adddr = 0U;
    config->linePitchBytes = 0U;
    config->framePitchBytes = 0U;
    config->format = kISI_InputMemBGR8P;
   endcode
 *
 * param config Pointer to the configuration structure.
 */
void ISI_InputMemGetDefaultConfig(isi_input_mem_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->adddr           = 0U;
    config->linePitchBytes  = 0U;
    config->framePitchBytes = 0U;
    config->format          = kISI_InputMemBGR888;
}

/*!
 * brief Trigger the ISI pipeline to read the input memory.
 *
 * param base ISI peripheral base address
 */
void ISI_TriggerInputMemRead(ISI_Type *base)
{
    uint32_t reg;

    reg = base->CHNL_MEM_RD_CTRL;
    /* Clear CHNL_MEM_RD_CTRL[READ_MEM]. */
    base->CHNL_MEM_RD_CTRL = reg & ~ISI_CHNL_MEM_RD_CTRL_READ_MEM_MASK;
    /* Set CHNL_MEM_RD_CTRL[READ_MEM]. */
    base->CHNL_MEM_RD_CTRL = reg | ISI_CHNL_MEM_RD_CTRL_READ_MEM_MASK;
}

/*!
 * brief Set the ISI output buffer address.
 *
 * This function sets the output buffer address and trigger the ISI to shadow the
 * address, it is used for fast run-time setting.
 *
 * param base ISI peripheral base address
 * param index Index of output buffer, could be 0 and 1.
 * param addrY RGB or Luma (Y) output buffer address.
 * param addrU Chroma (U/Cb/UV/CbCr) output buffer address.
 * param addrV Chroma (V/Cr) output buffer address.
 */
void ISI_SetOutputBufferAddr(ISI_Type *base, uint8_t index, uint32_t addrY, uint32_t addrU, uint32_t addrV)
{
    assert(index < ISI_OUT_BUFFER_CNT);

    if (0U == index)
    {
        base->CHNL_OUT_BUF1_ADDR_Y = addrY;
        base->CHNL_OUT_BUF1_ADDR_U = addrU;
        base->CHNL_OUT_BUF1_ADDR_V = addrV;
        base->CHNL_OUT_BUF_CTRL ^= ISI_CHNL_OUT_BUF_CTRL_LOAD_BUF1_ADDR_MASK;
    }
    else
    {
        base->CHNL_OUT_BUF2_ADDR_Y = addrY;
        base->CHNL_OUT_BUF2_ADDR_U = addrU;
        base->CHNL_OUT_BUF2_ADDR_V = addrV;
        base->CHNL_OUT_BUF_CTRL ^= ISI_CHNL_OUT_BUF_CTRL_LOAD_BUF2_ADDR_MASK;
    }
}
