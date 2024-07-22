/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdifv3.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdifv3"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for LCDIF module.
 *
 * @param base LCDIF peripheral base address
 */
static uint32_t LCDIFV3_GetInstance(const LCDIF_Type *base);

/*!
 * @brief Reset register value to default status.
 *
 * @param base LCDIF peripheral base address
 */
static void LCDIFV3_ResetRegister(LCDIF_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LCDIF clock for each instance. */
static const clock_ip_name_t s_lcdifv3Clocks[] = LCDIFV3_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t LCDIFV3_GetInstance(const LCDIF_Type *base)
{
    static LCDIF_Type *const s_lcdifv3Bases[] = LCDIF_BASE_PTRS;

    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdifv3Bases); instance++)
    {
        if (s_lcdifv3Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdifv3Bases));

    return instance;
}

static void LCDIFV3_ResetRegister(LCDIF_Type *base)
{
    base->DISP_PARA         = 0U;
    base->CTRL.RW           = 0x80000000U;
    base->DISP_SIZE         = 0U;
    base->HSYN_PARA         = 0x30003U;
    base->VSYN_PARA         = 0x30003U;
    base->VSYN_HSYN_WIDTH   = 0x30003U;
    base->INT_ENABLE_D0     = 0U;
    base->INT_ENABLE_D1     = 0U;
    /* Clear interrupt status. */
    base->INT_STATUS_D0     = 0xFFFFFFFFU;
    base->INT_STATUS_D1     = 0xFFFFFFFFU;

    base->CTRLDESCL_1       = 0U;
    base->CTRLDESCL_3       = 0U;
    base->CTRLDESCL_LOW_4   = 0U;
    base->CTRLDESCL_HIGH_4  = 0U;
    base->CTRLDESCL_5       = 0U;

    base->CSC_COEF0 = 0x0U;
    base->CSC_COEF1 = 0x0U;
    base->CSC_COEF2 = 0x0U;
    base->CSC_COEF3 = 0x0U;
    base->CSC_COEF4 = 0x0U;
    base->CSC_COEF5 = 0x0U;
}

/*!
 * brief Initializes the LCDIF v3.
 *
 * This function ungates the LCDIF v3 clock and release the peripheral reset.
 *
 * param base LCDIF v3 peripheral base address.
 */
void LCDIFV3_Init(LCDIF_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    uint32_t instance = LCDIFV3_GetInstance(base);
    /* Enable the clock. */
    CLOCK_EnableClock(s_lcdifv3Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    LCDIFV3_ResetRegister(base);

    /* Out of reset. */
    base->CTRL.RW = 0U;
}

/*!
 * brief Deinitializes the LCDIF peripheral.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV3_Deinit(LCDIF_Type *base)
{
    LCDIFV3_ResetRegister(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && (0 != FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
    uint32_t instance = LCDIFV3_GetInstance(base);
    /* Disable the clock. */
    CLOCK_DisableClock(s_lcdifv3Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Reset the LCDIF v3.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV3_Reset(LCDIF_Type *base)
{
    LCDIFV3_ResetRegister(base);

    /* Release and ready to work. */
    base->CTRL.RW = 0U;
}

/*!
 * brief Gets the LCDIF display default configuration structure.
 *
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV3_DisplayGetDefaultConfig(lcdifv3_display_config_t *config)
{
    assert(NULL != config);

    config->panelWidth    = 0U;
    config->panelHeight   = 0U;
    config->hsw           = 3U;
    config->hfp           = 3U;
    config->hbp           = 3U;
    config->vsw           = 3U;
    config->vfp           = 3U;
    config->vbp           = 3U;
    config->polarityFlags = (uint32_t)kLCDIFV3_VsyncActiveHigh | (uint32_t)kLCDIFV3_HsyncActiveHigh |
                            (uint32_t)kLCDIFV3_DataEnableActiveHigh | (uint32_t)kLCDIFV3_DriveDataOnRisingClkEdge |
                            (uint32_t)kLCDIFV3_DataActiveHigh;
    config->lineOrder = kLCDIFV3_LineOrderRGBOrYUV;
}

/*!
 * brief Set the LCDIF v3 display configurations.
 *
 * param base LCDIF peripheral base address.
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV3_SetDisplayConfig(LCDIF_Type *base, const lcdifv3_display_config_t *config)
{
    assert(NULL != config);

    /* Configure the parameters. */
    base->DISP_SIZE = ((uint32_t)config->panelWidth << LCDIF_DISP_SIZE_DELTA_X_SHIFT) |
                      ((uint32_t)config->panelHeight << LCDIF_DISP_SIZE_DELTA_Y_SHIFT);

    base->HSYN_PARA =  ((uint32_t)config->hbp << LCDIF_HSYN_PARA_BP_H_SHIFT) |
                      ((uint32_t)config->hfp << LCDIF_HSYN_PARA_FP_H_SHIFT);

    base->VSYN_PARA = ((uint32_t)config->vbp << LCDIF_VSYN_PARA_BP_V_SHIFT) |
                      ((uint32_t)config->vfp << LCDIF_VSYN_PARA_FP_V_SHIFT);
     
    base->VSYN_HSYN_WIDTH = ((uint32_t)config->hsw << LCDIF_VSYN_HSYN_WIDTH_PW_H_SHIFT) |
                            ((uint32_t)config->vsw << LCDIF_VSYN_HSYN_WIDTH_PW_V_SHIFT);
    
    base->DISP_PARA = LCDIF_DISP_PARA_LINE_PATTERN((uint32_t)config->lineOrder);

    base->CTRL.RW = (uint32_t)(config->polarityFlags);
}

/*!
 * brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * param base LCDIFv3 peripheral base address.
 * param layerIndex Index of the layer.
 * param mode The conversion mode.
 */
void LCDIFV3_SetCscMode(LCDIF_Type *base, lcdifv3_csc_mode_t mode)
{
    /*
     * The equations used for Colorspace conversion are:
     *
     * YUV/YCbCr -> RGB
     * R = A1(Y-D1) + A2(U-D2) + A3(V-D3)
     * G = B1(Y-D1) + B2(U-D2) + B3(V-D3)
     * B = C1(Y-D1) + C2(U-D2) + C3(V-D3)
     *
     * RGB -> YUV/YCbCr
     * Y = A1*R + A2*G + A3*B + D1
     * U = B1*R + B2*G + B3*B + D2
     * V = C1*R + C2*G + C3*B + D3
     */

    base->CSC_CTRL &= ~(LCDIF_CSC_CTRL_CSC_MODE_MASK | LCDIF_CSC_CTRL_BYPASS_MASK);
    if (kLCDIFV3_CscYUV2RGB == mode || kLCDIFV3_CscYCbCr2RGB == mode)
    {
        base->CSC_COEF0 = LCDIF_CSC_COEF0_A1(0x0U)
                                            | LCDIF_CSC_COEF0_A2(0x0U);
        base->CSC_COEF1 = LCDIF_CSC_COEF1_A3(0x0U)
                                            | LCDIF_CSC_COEF1_B1(0x0U);
        base->CSC_COEF2 = LCDIF_CSC_COEF2_B2(0x0U)
                                            | LCDIF_CSC_COEF2_B3(0x0U);
        base->CSC_COEF3 = LCDIF_CSC_COEF3_C1(0x0U)
                                            | LCDIF_CSC_COEF3_C2(0x0U);
        base->CSC_COEF4 = LCDIF_CSC_COEF4_C3(0x0U)
                                            | LCDIF_CSC_COEF4_D1(0x0U);
        base->CSC_COEF5 = LCDIF_CSC_COEF5_D2(0x0U)
                                            | LCDIF_CSC_COEF5_D3(0x0U);

    }
    else if (kLCDIFV3_CscRGB2YUV == mode || kLCDIFV3_CscRGB2YCbCr == mode)
    {

        base->CSC_COEF0 = LCDIF_CSC_COEF0_A1(0x0U)
                                            | LCDIF_CSC_COEF0_A2(0x0U);
        base->CSC_COEF1 = LCDIF_CSC_COEF1_A3(0x0U)
                                            | LCDIF_CSC_COEF1_B1(0x0U);
        base->CSC_COEF2 = LCDIF_CSC_COEF2_B2(0x0U)
                                            | LCDIF_CSC_COEF2_B3(0x0U);
        base->CSC_COEF3 = LCDIF_CSC_COEF3_C1(0x0U)
                                            | LCDIF_CSC_COEF3_C2(0x0U);
        base->CSC_COEF4 = LCDIF_CSC_COEF4_C3(0x0U)
                                            | LCDIF_CSC_COEF4_D1(0x0U);
        base->CSC_COEF5 = LCDIF_CSC_COEF5_D2(0x0U)
                                            | LCDIF_CSC_COEF5_D3(0x0U);
    }
    else
    {
        base->CSC_COEF0 = 0x0U;
        base->CSC_COEF1 = 0x0U;
        base->CSC_COEF2 = 0x0U;
        base->CSC_COEF3 = 0x0U;
        base->CSC_COEF4 = 0x0U;
        base->CSC_COEF5 = 0x0U;
	base->CSC_CTRL |= LCDIF_CSC_CTRL_BYPASS(1);
    }
    base->CSC_CTRL |= LCDIF_CSC_CTRL_CSC_MODE(mode);
}

/*!
 * brief Set the layer source buffer configuration.
 *
 * param base LCDIFv3 peripheral base address.
 * param config Pointer to the configuration.
 */
void LCDIFV3_SetLayerBufferConfig(LCDIF_Type *base, uint8_t layerIndex, const lcdifv3_buffer_config_t *config)
{
    assert(NULL != config);
    uint32_t reg;
    base->CTRLDESCL_3 = config->strideBytes;
    reg = base->CTRLDESCL_5;
    reg = (reg & ~(LCDIF_CTRLDESCL_5_BPP_MASK | LCDIF_CTRLDESCL_5_YUV_FORMAT_MASK)) | (uint32_t)config->pixelFormat;

    base->CTRLDESCL_5 = reg;
}
