/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_video_common.h"
#include "fsl_camera.h"
#include "fsl_camera_device.h"
#include "fsl_ov7670.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OV7670_SCCB_ADDR 0x21U

#define OV7670_WriteReg(handle, reg, val)                            \
    SCCB_WriteReg(OV7670_SCCB_ADDR, kSCCB_RegAddr8Bit, (reg), (val), \
                  ((ov7670_resource_t *)((handle)->resource))->i2cSendFunc)

#define OV7670_ReadReg(handle, reg, val)                            \
    SCCB_ReadReg(OV7670_SCCB_ADDR, kSCCB_RegAddr8Bit, (reg), (val), \
                 ((ov7670_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define OV7670_ModifyReg(handle, reg, clrMask, val)                              \
    SCCB_ModifyReg(OV7670_SCCB_ADDR, kSCCB_RegAddr8Bit, (reg), (clrMask), (val), \
                   ((ov7670_resource_t *)((handle)->resource))->i2cReceiveFunc,  \
                   ((ov7670_resource_t *)((handle)->resource))->i2cSendFunc)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t OV7670_Init(camera_device_handle_t *handle, const camera_config_t *config);

status_t OV7670_Deinit(camera_device_handle_t *handle);

status_t OV7670_Control(camera_device_handle_t *handle, camera_device_cmd_t cmd, int32_t arg);

status_t OV7670_Start(camera_device_handle_t *handle);

status_t OV7670_Stop(camera_device_handle_t *handle);

status_t OV7670_InitExt(camera_device_handle_t *handle, const camera_config_t *config, const void *specialConfig);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief OV7670 resolution options                                          */
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_VGA_DEFAULT   = {140, 16};
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_QVGA_DEFAULT  = {272, 16};
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_QQVGA_DEFAULT = {140, 16};
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_CIF_DEFAULT   = {140, 16};
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_QCIF_DEFAULT  = {140, 16};
ov7670_window_start_point_t OV7670_WINDOW_START_POINT_QQCIF_DEFAULT = {140, 16};

/*! @brief Night mode initialization structure data                           */
ov7670_output_format_config_t OV7670_FORMAT_RawBayerRGB       = {0x01, 0x00, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_ProcessedBayerRGB = {0x05, 0x00, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_YUV422            = {0x00, 0x00, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_GRB422            = {0x04, 0x00, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_RGB565            = {0x04, 0xd0, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_RGB555            = {0x04, 0xf0, 0x00};
ov7670_output_format_config_t OV7670_FORMAT_xRGB444           = {0x04, 0xd0, 0x2};
ov7670_output_format_config_t OV7670_FORMAT_RGBx444           = {0x04, 0xd0, 0x3};

/*! @brief resolution initialization structure data                           */
ov7670_resolution_config_t OV7670_RESOLUTION_VGA = {0x00, 0x00, 0x00, 0x3a, 0x35, 0x11, 0xf0, 0x02};   /*!< 640 x 480 */
ov7670_resolution_config_t OV7670_RESOLUTION_QVGA_ORIGINAL = {0x10, 0x00, 0x00, 0x3a,
                                                              0x35, 0x11, 0xf0, 0x02};                 /*!< 320 x 240 */
ov7670_resolution_config_t OV7670_RESOLUTION_QVGA  = {0x10, 0x04, 0x19, 0x3a, 0x35, 0x11, 0xf1, 0x02}; /*!< 320 x 240 */
ov7670_resolution_config_t OV7670_RESOLUTION_QQVGA = {0x10, 0x04, 0x1A, 0x3a, 0x35, 0x22, 0xf2, 0x02}; /*!< 160 x 120 */

ov7670_resolution_config_t OV7670_RESOLUTION_CIF = {0x20, 0x08, 0x11, 0x3a, 0x35, 0x11, 0xf1, 0x02};   /*!< 352 x 288 */
ov7670_resolution_config_t OV7670_RESOLUTION_QCIF_ORIGINAL = {0x21, 0x08, 0x11, 0x3a,
                                                              0x35, 0x11, 0xf1, 0x02};                 /*!< 176 x 144 */
ov7670_resolution_config_t OV7670_RESOLUTION_QCIF  = {0x28, 0x00, 0x11, 0x3a, 0x35, 0x11, 0xf1, 0x02}; /*!< 176 x 144 */
ov7670_resolution_config_t OV7670_RESOLUTION_QQCIF = {0x28, 0x0c, 0x12, 0x3a, 0x35, 0x22, 0xf2, 0x02}; /*!< 88 x 72 */

/*! @brief Special effects configuration initialization structure data       */
ov7670_windowing_config_t OV7670_WINDOW_VGA   = {0x36, 0x13, 0x01, 0x0a, 0x02, 0x7a};
ov7670_windowing_config_t OV7670_WINDOW_QVGA  = {0x80, 0x15, 0x03, 0x00, 0x03, 0x7b};
ov7670_windowing_config_t OV7670_WINDOW_QQVGA = {0x64, 0x16, 0x04, 0x0a, 0x03, 0x7b};
ov7670_windowing_config_t OV7670_WINDOW_CIF   = {0x12, 0x15, 0x0b, 0x0a, 0x03, 0x7b};
ov7670_windowing_config_t OV7670_WINDOW_QCIF  = {0x80, 0x39, 0x03, 0x0a, 0x03, 0x7b};
ov7670_windowing_config_t OV7670_WINDOW_QQCIF = {0x64, 0x3a, 0x03, 0x06, 0x03, 0x7b};

/*! @brief Frame rate initialization structure data                           */
ov7670_frame_rate_config_t OV7670_30FPS_26MHZ_XCLK = {0x80, 0x0a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_25FPS_26MHZ_XCLK = {0x80, 0x0a, 0x00, 0x00, 0x99, 0x00};
ov7670_frame_rate_config_t OV7670_15FPS_26MHZ_XCLK = {0x00, 0x0a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_14FPS_26MHZ_XCLK = {0x00, 0x0a, 0x00, 0x00, 0x46, 0x00};

ov7670_frame_rate_config_t OV7670_30FPS_24MHZ_XCLK = {0x80, 0x0a, 0x00, 0x00, 0x00, 0x00};
ov7670_frame_rate_config_t OV7670_25FPS_24MHZ_XCLK = {0x80, 0x0a, 0x00, 0x00, 0x66, 0x00};
ov7670_frame_rate_config_t OV7670_15FPS_24MHZ_XCLK = {0x00, 0x0a, 0x00, 0x00, 0x00, 0x00};
ov7670_frame_rate_config_t OV7670_14FPS_24MHZ_XCLK = {0x00, 0x0a, 0x00, 0x00, 0x1a, 0x00};

ov7670_frame_rate_config_t OV7670_30FPS_13MHZ_XCLK = {0x00, 0x4a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_25FPS_13MHZ_XCLK = {0x00, 0x4a, 0x00, 0x00, 0x99, 0x00};
ov7670_frame_rate_config_t OV7670_15FPS_13MHZ_XCLK = {0x01, 0x4a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_14FPS_13MHZ_XCLK = {0x01, 0x4a, 0x00, 0x00, 0x46, 0x00};

ov7670_frame_rate_config_t OV7670_30FPS_12MHZ_XCLK = {0x00, 0x4a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_25FPS_12MHZ_XCLK = {0x00, 0x4a, 0x00, 0x00, 0x66, 0x00};
ov7670_frame_rate_config_t OV7670_15FPS_12MHZ_XCLK = {0x01, 0x4a, 0x00, 0x00, 0x2b, 0x00};
ov7670_frame_rate_config_t OV7670_14FPS_12MHZ_XCLK = {0x01, 0x4a, 0x00, 0x00, 0x46, 0x00};

/*! @brief Night mode initialization structure data                           */
ov7670_night_mode_config_t OV7670_NIGHT_MODE_DISABLED       = {0x00};
ov7670_night_mode_config_t OV7670_NIGHT_MODE_AUTO_FR_DIVBY2 = {0xa0};
ov7670_night_mode_config_t OV7670_NIGHT_MODE_AUTO_FR_DIVBY4 = {0xc0};
ov7670_night_mode_config_t OV7670_NIGHT_MODE_AUTO_FR_DIVBY8 = {0xe0};

/*! @brief Banding filter initialization structure data                       */
ov7670_filter_config_t OV7670_FILTER_DISABLED                          = {0x00, 0x98, 0x7f, 0x02, 0x03, 0x02};
ov7670_filter_config_t OV7670_FILTER_30FPS_60HZ                        = {0x20, 0x98, 0x7f, 0x02, 0x03, 0x02};
ov7670_filter_config_t OV7670_FILTER_15FPS_60HZ                        = {0x20, 0x4c, 0x3f, 0x05, 0x07, 0x02};
ov7670_filter_config_t OV7670_FILTER_25FPS_50HZ                        = {0x20, 0x98, 0x7f, 0x03, 0x03, 0x0a};
ov7670_filter_config_t OV7670_FILTER_14FPS_50HZ                        = {0x20, 0x4c, 0x3f, 0x06, 0x07, 0x0a};
ov7670_filter_config_t OV7670_FILTER_30FPS_60HZ_AUTO_LIGHT_FREQ_DETECT = {0x20, 0x98, 0x7f, 0x02, 0x03, 0x12};
ov7670_filter_config_t OV7670_FILTER_15FPS_60HZ_AUTO_LIGHT_FREQ_DETECT = {0x20, 0x4c, 0x3f, 0x05, 0x07, 0x12};
ov7670_filter_config_t OV7670_FILTER_25FPS_50HZ_AUTO_LIGHT_FREQ_DETECT = {0x20, 0x98, 0x7f, 0x03, 0x03, 0x1a};
ov7670_filter_config_t OV7670_FILTER_14FPS_50HZ_AUTO_LIGHT_FREQ_DETECT = {0x20, 0x4c, 0x3f, 0x06, 0x07, 0x1a};

/*! @brief White balance initialization structure data                        */
ov7670_white_balance_config_t OV7670_WHITE_BALANCE_DEFAULT  = {0x02, 0x9a, 0xc0, 0x55, 0x02, 0x14,
                                                               0xf0, 0x45, 0x61, 0x51, 0x79, 0x08};
ov7670_white_balance_config_t OV7670_WHITE_BALANCE_DISABLED = {0x00, 0x9a, 0xc0, 0x55, 0x02, 0x14,
                                                               0xf0, 0x45, 0x61, 0x51, 0x79, 0x00};
ov7670_white_balance_config_t OV7670_WHITE_BALANCE_SIMPLE   = {0x02, 0x9f, 0x10, 0x55, 0x02, 0x14,
                                                               0xf0, 0x45, 0x61, 0x51, 0x79, 0x08};

/*! @brief Light mode configuration initialization structure data             */
ov7670_light_mode_config_t OV7670_LIGHT_MODE_DISABLED = {0x05, 0x0a, 0x08, 0x00, 0x08};
ov7670_light_mode_config_t OV7670_LIGHT_MODE_AUTO     = {0xc5, 0x3a, 0x08, 0x00, 0x08};
ov7670_light_mode_config_t OV7670_LIGHT_MODE_SUNNY    = {0xc5, 0x6a, 0x5a, 0x00, 0x5c};
ov7670_light_mode_config_t OV7670_LIGHT_MODE_CLOUDY   = {0xc5, 0x0a, 0x58, 0x00, 0x60};
ov7670_light_mode_config_t OV7670_LIGHT_MODE_OFFICE   = {0xc5, 0x2a, 0x84, 0x00, 0x4c};
ov7670_light_mode_config_t OV7670_LIGHT_MODE_HOME     = {0xc5, 0x1a, 0x96, 0x00, 0x40};

/*! @brief Color saturation configuration initialization structure data       */
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_4PLUS   = {0xc0, 0xc0, 0x00, 0x33, 0x8d, 0xc0, 0x9e, 0x02};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_3PLUS   = {0x99, 0x99, 0x00, 0x28, 0x71, 0x99, 0x9e, 0x02};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_2PLUS   = {0xc0, 0xc0, 0x00, 0x33, 0x8d, 0xc0, 0x9e, 0x00};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_1PLUS   = {0x99, 0x99, 0x00, 0x28, 0x71, 0x99, 0x9e, 0x00};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_0       = {0x80, 0x80, 0x00, 0x22, 0x5e, 0x80, 0x9e, 0x00};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_DEFAULT = {0x40, 0x34, 0x0c, 0x17, 0x29, 0x40, 0x1e, 0x00};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_1MINUS  = {0x66, 0x66, 0x00, 0x1b, 0x4b, 0x66, 0x9e, 0x00};
ov7670_color_saturation_config_t OV7670_COLOR_SATURATION_2MINUS  = {0x40, 0x40, 0x00, 0x11, 0x2f, 0x40, 0x9e, 0x00};

/*! @brief Special effects configuration initialization structure data       */
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_ANTIQUE     = {0x18, 0, 255};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_SEPHIA      = {0x18, 16, 146};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_BLUISH      = {0x18, 240, 146};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_GREENISH    = {0x18, 0, 30};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_REDISH      = {0x18, 90, 240};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_BW          = {0x18, 110, 110};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_NEGATIVE    = {0x28, 0x80, 0x80};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_BW_NEGATIVE = {0x38, 110, 110};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_NORMAL      = {0x0c, 0x80, 0x80};
ov7670_special_effect_config_t OV7670_SPECIAL_EFFECT_DISABLED    = {0x08, 0x80, 0x80};

/*! @brief Special effects configuration initialization structure data       */
ov7670_gamma_curve_slope_config_t OV7670_GAMMA_CURVE_SLOPE_DEFAULT = {0x24, 0x04, 0x07, 0x10, 0x28, 0x36, 0x44, 0x52,
                                                                      0x60, 0x6c, 0x78, 0x8c, 0x9e, 0xbb, 0xd2, 0xe5};
ov7670_gamma_curve_slope_config_t OV7670_GAMMA_CURVE_SLOPE1        = {0x20, 0x10, 0x1e, 0x35, 0x5a, 0x69, 0x76, 0x80,
                                                                      0x88, 0x8f, 0x96, 0xa3, 0xaf, 0xc4, 0xd7, 0xe8};

const camera_device_operations_t ov7670_ops = {
    .init     = OV7670_Init,
    .deinit   = OV7670_Deinit,
    .start    = OV7670_Start,
    .stop     = OV7670_Stop,
    .control  = OV7670_Control,
    .init_ext = OV7670_InitExt,
};
/*******************************************************************************
 * Code
 ******************************************************************************/

static void OV7670_DelayMs(uint32_t ms)
{
    VIDEO_DelayMs(ms);
}

status_t OV7670_CameraInit(camera_device_handle_t *handle, const ov7670_config_t *config)
{
    uint8_t u8TempVal0, u8TempVal1;

    /* Reset Device */
    (void)OV7670_WriteReg(handle, OV7670_COM7_REG, 0x80);
    /* wait for a least 1ms */
    OV7670_DelayMs(5); /* 5ms */
    /* Read product ID nuumber MSB */
    if (OV7670_ReadReg(handle, OV7670_PID_REG, &u8TempVal0) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    /* Read product ID nuumber MSB */
    if (OV7670_ReadReg(handle, OV7670_VER_REG, &u8TempVal1) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    if ((u8TempVal0 != OV7670_PID_NUM) && (u8TempVal1 != OV7670_VER_NUM))
    {
        return kStatus_Fail;
    }

    /* NULL pointer means default setting. */
    if (config == NULL)
    {
        /* Reset Device */
        (void)OV7670_WriteReg(handle, OV7670_COM7_REG, 0x80);
        /* wait for a bit */
        OV7670_DelayMs(5); /* 5ms */
    }
    else
    {
        (void)OV7670_Configure(handle, config);
    }
    /* MVFP */
    if (OV7670_ReadReg(handle, OV7670_MVFP_REG, &u8TempVal1) != kStatus_Success)
    {
        return kStatus_Fail;
    }
    if (0U == (u8TempVal1 & OV7670_MVFP_MIRROR_MASK))
    {
        u8TempVal1 |= OV7670_MVFP_MIRROR_MASK;
        (void)OV7670_WriteReg(handle, OV7670_MVFP_REG, u8TempVal1);
    }
    return kStatus_Success;
}

status_t OV7670_ContrastAdjustment(camera_device_handle_t *handle, uint8_t val)
{
    status_t status = kStatus_Success;

    status = OV7670_WriteReg(handle, OV7670_CONTRAS_CENTER_REG, 0x80);
    status = OV7670_ModifyReg(handle, OV7670_MTXS_REG, 0x80, 0x00);
    status = OV7670_WriteReg(handle, OV7670_CONTRAS_REG, val);
    return status;
}

status_t OV7670_BrightnessAdjustment(camera_device_handle_t *handle, uint8_t val)
{
    status_t status = kStatus_Success;

    status = OV7670_WriteReg(handle, OV7670_BRIGHT_REG, val);

    return status;
}

status_t OV7670_Configure(camera_device_handle_t *handle, const ov7670_config_t *config)
{
    status_t status = kStatus_Success;

    ov7670_windowing_config_t *windowConfig;
    (void)OV7670_OutputFormat(handle, config->outputFormat);
    (void)OV7670_Resolution(handle, config->resolution);

    switch ((video_resolution_t)config->resolution)
    {
        case kVIDEO_ResolutionVGA:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_VGA;
            break;
        case kVIDEO_ResolutionQVGA:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_QVGA;
            break;
        case kVIDEO_ResolutionQQVGA:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_QQVGA;
            break;
        case kVIDEO_ResolutionCIF:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_CIF;
            break;
        case kVIDEO_ResolutionQCIF:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_QCIF;
            break;
        case kVIDEO_ResolutionQQCIF:
            windowConfig = (ov7670_windowing_config_t *)&OV7670_WINDOW_QQCIF;
            break;
        default:
            status = kStatus_Fail; /* not supported resolution */
            break;
    }

    if (kStatus_Success != status)
    {
        return status;
    }

    (void)OV7670_SetWindow(handle, windowConfig);
    (void)OV7670_FrameRateAdjustment(handle, config->frameRate);

    /* configure Hsync/Vsync for EZH */
    (void)OV7670_WriteReg(handle, OV7670_COM10_REG, 0x20); /* no PCLK toggle during Hblank, mandatory! */

    if (config->advancedConfig == NULL)
    {
        (void)OV7670_BandingFilterSelection(handle, (ov7670_filter_config_t *)&OV7670_FILTER_25FPS_50HZ);
        (void)OV7670_NightMode(handle, (ov7670_night_mode_config_t *)&OV7670_NIGHT_MODE_DISABLED);
        (void)OV7670_WhiteBalance(handle, (ov7670_white_balance_config_t *)&OV7670_WHITE_BALANCE_SIMPLE);
        (void)OV7670_LightMode(handle, (ov7670_light_mode_config_t *)&OV7670_LIGHT_MODE_DISABLED);
        (void)OV7670_ColorSaturation(handle, (ov7670_color_saturation_config_t *)&OV7670_COLOR_SATURATION_2PLUS);
        (void)OV7670_SpecialEffects(handle, (ov7670_special_effect_config_t *)&OV7670_SPECIAL_EFFECT_DISABLED);
        (void)OV7670_GammaCurveSlope(handle, (ov7670_gamma_curve_slope_config_t *)&OV7670_GAMMA_CURVE_SLOPE_DEFAULT);
    }
    else
    {
        (void)OV7670_BandingFilterSelection(handle, config->advancedConfig->filter);
        (void)OV7670_NightMode(handle, config->advancedConfig->nightMode);
        (void)OV7670_WhiteBalance(handle, config->advancedConfig->whiteBalance);
        (void)OV7670_LightMode(handle, config->advancedConfig->lightMode);
        (void)OV7670_ColorSaturation(handle, config->advancedConfig->colorSaturation);
        (void)OV7670_SpecialEffects(handle, config->advancedConfig->specialEffect);
        (void)OV7670_GammaCurveSlope(handle, config->advancedConfig->gammaCurveSlope);
    }

    (void)OV7670_ContrastAdjustment(handle, config->contrast);
    (void)OV7670_BrightnessAdjustment(handle, config->brightness);
    (void)OV7670_WriteReg(handle, 0xb0, 0x84); /*!< because of colors */
    (void)OV7670_WriteReg(handle, 0xff, 0xff);

    return kStatus_Success;
}

status_t OV7670_OutputFormat(camera_device_handle_t *handle, const ov7670_output_format_config_t *outputFormatConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_COM7_REG, 0x05, outputFormatConfig->com7);
    (void)OV7670_ModifyReg(handle, OV7670_RGB444_REG, 0x03, outputFormatConfig->rgb444);
    (void)OV7670_ModifyReg(handle, OV7670_COM15_REG, 0x30, outputFormatConfig->com15);

    return kStatus_Success;
}

status_t OV7670_Resolution(camera_device_handle_t *handle, uint32_t resolution)
{
    status_t status = kStatus_Success;

    ov7670_resolution_config_t *resolution_config;
    switch ((video_resolution_t)resolution)
    {
        case kVIDEO_ResolutionVGA:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_VGA;
            break;
        case kVIDEO_ResolutionQVGA:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_QVGA;
            break;
        case kVIDEO_ResolutionQQVGA:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_QQVGA;
            break;
        case kVIDEO_ResolutionCIF:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_CIF;
            break;
        case kVIDEO_ResolutionQCIF:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_QCIF;
            break;
        case kVIDEO_ResolutionQQCIF:
            resolution_config = (ov7670_resolution_config_t *)&OV7670_RESOLUTION_QQCIF;
            break;
        default:
            status = kStatus_Fail; /*!< not supported resolution */
            break;
    }

    if (kStatus_Success != status)
    {
        return status;
    }

    (void)OV7670_ModifyReg(handle, OV7670_COM7_REG, 0x38, resolution_config->com7);
    (void)OV7670_ModifyReg(handle, OV7670_COM3_REG, 0x0c, resolution_config->com3);
    (void)OV7670_WriteReg(handle, OV7670_COM14_REG, resolution_config->com14);
    (void)OV7670_WriteReg(handle, OV7670_SCALING_XSC_REG, resolution_config->scalingXsc);
    (void)OV7670_WriteReg(handle, OV7670_SCALING_YSC_REG, resolution_config->scalingYsc);
    (void)OV7670_ModifyReg(handle, OV7670_SCALING_DCWCTR_REG, 0x33, resolution_config->scalingDcwctr);
    (void)OV7670_WriteReg(handle, OV7670_SCALING_PCLK_DIV_REG, resolution_config->scalingPclkDiv);
    (void)OV7670_WriteReg(handle, OV7670_SCALING_PCLK_DELAY_REG, resolution_config->scalingPclkDelay);

    /* Autotomatically set output window after resolution change                */
    (void)OV7670_ModifyReg(handle, OV7670_TSLB_REG, 0x01, 0x01);

    return kStatus_Success;
}

status_t OV7670_SetWindow(camera_device_handle_t *handle, const ov7670_windowing_config_t *windowingConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_TSLB_REG, 0x01, 0x00);

    (void)OV7670_WriteReg(handle, OV7670_HREF_REG, windowingConfig->href);
    (void)OV7670_WriteReg(handle, OV7670_HSTART_REG, windowingConfig->hstart);
    (void)OV7670_WriteReg(handle, OV7670_HSTOP_REG, windowingConfig->hstop);
    (void)OV7670_WriteReg(handle, OV7670_VREF_REG, windowingConfig->vref);
    (void)OV7670_WriteReg(handle, OV7670_VSTART_REG, windowingConfig->vstart);
    (void)OV7670_WriteReg(handle, OV7670_VSTOP_REG, windowingConfig->vstop);

    return kStatus_Success;
}

status_t OV7670_FrameRateAdjustment(camera_device_handle_t *handle, const ov7670_frame_rate_config_t *frameRateConfig)
{
    (void)OV7670_WriteReg(handle, OV7670_CLKRC_REG, frameRateConfig->clkrc);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_DBLV_REG, frameRateConfig->dblv);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_EXHCH_REG, frameRateConfig->exhch);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_EXHCL_REG, frameRateConfig->exhcl);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_DM_LNL_REG, frameRateConfig->dm_lnl);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_DM_LNH_REG, frameRateConfig->dm_lnh);
    OV7670_DelayMs(2);

    return kStatus_Success;
}

status_t OV7670_NightMode(camera_device_handle_t *handle, const ov7670_night_mode_config_t *nightModeConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_COM11_REG, 0xe0, nightModeConfig->com11);

    OV7670_DelayMs(2);

    return kStatus_Success;
}

status_t OV7670_BandingFilterSelection(camera_device_handle_t *handle, const ov7670_filter_config_t *filterConfig)
{
    (void)OV7670_WriteReg(handle, OV7670_BD50ST_REG, filterConfig->bd50st);      /*!< 50Hz banding filter */
    (void)OV7670_WriteReg(handle, OV7670_BD60ST_REG, filterConfig->bd60st);      /*!< 60Hz banding filter */
    (void)OV7670_WriteReg(handle, OV7670_BD50MAX_REG, filterConfig->bd50max);    /*!< x step for 50hz */
    (void)OV7670_WriteReg(handle, OV7670_BD60MAX_REG, filterConfig->bd60max);    /*!< y step for 60hz */
    (void)OV7670_ModifyReg(handle, OV7670_COM11_REG, 0x1a, filterConfig->com11); /*!< Automatic Detect banding filter */
    (void)OV7670_ModifyReg(handle, OV7670_COM8_REG, 0x20, filterConfig->com8);   /*!< banding filter enable */

    return kStatus_Success;
}

status_t OV7670_WhiteBalance(camera_device_handle_t *handle, const ov7670_white_balance_config_t *whiteBalanceConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_COM8_REG, 0x02, whiteBalanceConfig->com8); /*!< AWB on/off  */
    (void)OV7670_WriteReg(handle, OV7670_AWBCTR0_REG, whiteBalanceConfig->awbctr0);
    (void)OV7670_WriteReg(handle, OV7670_AWBCTR1_REG, whiteBalanceConfig->awbctr1);
    (void)OV7670_WriteReg(handle, OV7670_AWBCTR2_REG, whiteBalanceConfig->awbctr2);
    (void)OV7670_WriteReg(handle, OV7670_AWBCTR3_REG, whiteBalanceConfig->awbctr3);
    (void)OV7670_WriteReg(handle, OV7670_AWBC1_REG, whiteBalanceConfig->awbc1);
    (void)OV7670_WriteReg(handle, OV7670_AWBC2_REG, whiteBalanceConfig->awbc2);
    (void)OV7670_WriteReg(handle, OV7670_AWBC3_REG, whiteBalanceConfig->awbc3);
    (void)OV7670_WriteReg(handle, OV7670_AWBC4_REG, whiteBalanceConfig->awbc4);
    (void)OV7670_WriteReg(handle, OV7670_AWBC5_REG, whiteBalanceConfig->awbc5);
    (void)OV7670_WriteReg(handle, OV7670_AWBC6_REG, whiteBalanceConfig->awbc6);
    (void)OV7670_WriteReg(handle, 0x59, 0x91);
    (void)OV7670_WriteReg(handle, 0x5a, 0x94);
    (void)OV7670_WriteReg(handle, 0x5b, 0xaa);
    (void)OV7670_WriteReg(handle, 0x5c, 0x71);
    (void)OV7670_WriteReg(handle, 0x5d, 0x8d);
    (void)OV7670_WriteReg(handle, 0x5e, 0x0f);
    (void)OV7670_WriteReg(handle, 0x5f, 0xf0);
    (void)OV7670_WriteReg(handle, 0x60, 0xf0);
    (void)OV7670_WriteReg(handle, 0x61, 0xf0);
    (void)OV7670_ModifyReg(handle, OV7670_COM16_REG, 0x08, whiteBalanceConfig->com16); /*!< AWB gain on */

    return kStatus_Success;
}

status_t OV7670_LightMode(camera_device_handle_t *handle, const ov7670_light_mode_config_t *lightModeConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_COM8_REG, 0xc5, lightModeConfig->com8);
    (void)OV7670_ModifyReg(handle, OV7670_COM9_REG, 0x7a, lightModeConfig->com9);
    (void)OV7670_WriteReg(handle, OV7670_RED_REG, lightModeConfig->red);
    (void)OV7670_WriteReg(handle, OV7670_GGAIN_REG, lightModeConfig->green);
    (void)OV7670_WriteReg(handle, OV7670_BLUE_REG, lightModeConfig->blue);
    (void)OV7670_WriteReg(handle, OV7670_GAIN_REG, 0x00);
    OV7670_DelayMs(2);

    /*!< Exposure value */
    (void)OV7670_WriteReg(handle, OV7670_AECH_REG, 0x00);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_AECHH_REG, 0x00);
    OV7670_DelayMs(2);
    (void)OV7670_ModifyReg(handle, OV7670_COM1_REG, 0x3, 0x00);
    OV7670_DelayMs(2);
    /*!< AGC/AEC stable operation region configuration */
    (void)OV7670_WriteReg(handle, OV7670_AEW_REG, 0x75);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_AEB_REG, 0x63);
    OV7670_DelayMs(2);
    (void)OV7670_WriteReg(handle, OV7670_VPT_REG, 0xd4);
    OV7670_DelayMs(2);

    return kStatus_Success;
}

status_t OV7670_ColorSaturation(camera_device_handle_t *handle,
                                const ov7670_color_saturation_config_t *colorSaturationConfig)
{
    (void)OV7670_WriteReg(handle, OV7670_MTX1_REG, colorSaturationConfig->mtx1);
    (void)OV7670_WriteReg(handle, OV7670_MTX2_REG, colorSaturationConfig->mtx2);
    (void)OV7670_WriteReg(handle, OV7670_MTX3_REG, colorSaturationConfig->mtx3);
    (void)OV7670_WriteReg(handle, OV7670_MTX4_REG, colorSaturationConfig->mtx4);
    (void)OV7670_WriteReg(handle, OV7670_MTX5_REG, colorSaturationConfig->mtx5);
    (void)OV7670_WriteReg(handle, OV7670_MTX6_REG, colorSaturationConfig->mtx6);
    (void)OV7670_WriteReg(handle, OV7670_MTXS_REG, colorSaturationConfig->mtxs);
    (void)OV7670_ModifyReg(handle, OV7670_COM16_REG, 0x02, colorSaturationConfig->com16);

    return kStatus_Success;
}

status_t OV7670_SpecialEffects(camera_device_handle_t *handle,
                               const ov7670_special_effect_config_t *specialEffectConfig)
{
    (void)OV7670_ModifyReg(handle, OV7670_TSLB_REG, 0xfe, specialEffectConfig->tslb);
    (void)OV7670_WriteReg(handle, OV7670_MANU_REG, specialEffectConfig->manu);
    (void)OV7670_WriteReg(handle, OV7670_MANV_REG, specialEffectConfig->manv);

    return kStatus_Success;
}

status_t OV7670_SetWindowByCoordinates(camera_device_handle_t *handle,
                                       ov7670_window_start_point_t *startPoint,
                                       uint32_t resolution)
{
    uint16_t u16Temp, u16Href, u16Vref;

    (void)OV7670_ModifyReg(handle, OV7670_TSLB_REG, 0x01, 0x00);

    u16Temp = startPoint->hstartCoordinate + FSL_VIDEO_EXTRACT_WIDTH(resolution);
    u16Href = (u16Temp & 0x07U);
    u16Href = u16Href << 3;
    u16Href |= (startPoint->hstartCoordinate & 0x07U);
    u16Href |= 0xc0U;
    (void)OV7670_WriteReg(handle, OV7670_HREF_REG, (uint8_t)u16Href);
    u16Temp = u16Temp >> 3;
    (void)OV7670_WriteReg(handle, OV7670_HSTOP_REG, (uint8_t)u16Temp);
    u16Temp = ((startPoint->hstartCoordinate & 0x7f8U) >> 3);
    (void)OV7670_WriteReg(handle, OV7670_HSTART_REG, (uint8_t)u16Temp);

    u16Temp = startPoint->vstartCoordinate + FSL_VIDEO_EXTRACT_HEIGHT(resolution);
    u16Vref = (u16Temp & 0x03U);
    u16Vref = u16Vref << 2;
    u16Vref |= (startPoint->vstartCoordinate & 0x03U);
    u16Vref &= 0xF0U;
    (void)OV7670_ModifyReg(handle, OV7670_VREF_REG, 0xc0, (uint8_t)u16Vref);
    u16Temp = u16Temp >> 2;
    (void)OV7670_WriteReg(handle, OV7670_VSTOP_REG, (uint8_t)u16Temp);
    u16Temp = ((startPoint->vstartCoordinate & 0x3fcU) >> 2);
    (void)OV7670_WriteReg(handle, OV7670_VSTART_REG, (uint8_t)u16Temp);

    return kStatus_Success;
}

status_t OV7670_GammaCurveSlope(camera_device_handle_t *handle,
                                const ov7670_gamma_curve_slope_config_t *gammaCurveSlopeConfig)
{
    (void)OV7670_WriteReg(handle, OV7670_SLOP_REG, gammaCurveSlopeConfig->slope);
    (void)OV7670_WriteReg(handle, OV7670_GAM1_REG, gammaCurveSlopeConfig->gam1);
    (void)OV7670_WriteReg(handle, OV7670_GAM2_REG, gammaCurveSlopeConfig->gam2);
    (void)OV7670_WriteReg(handle, OV7670_GAM3_REG, gammaCurveSlopeConfig->gam3);
    (void)OV7670_WriteReg(handle, OV7670_GAM4_REG, gammaCurveSlopeConfig->gam4);
    (void)OV7670_WriteReg(handle, OV7670_GAM5_REG, gammaCurveSlopeConfig->gam5);
    (void)OV7670_WriteReg(handle, OV7670_GAM6_REG, gammaCurveSlopeConfig->gam6);
    (void)OV7670_WriteReg(handle, OV7670_GAM7_REG, gammaCurveSlopeConfig->gam7);
    (void)OV7670_WriteReg(handle, OV7670_GAM8_REG, gammaCurveSlopeConfig->gam8);
    (void)OV7670_WriteReg(handle, OV7670_GAM9_REG, gammaCurveSlopeConfig->gam9);
    (void)OV7670_WriteReg(handle, OV7670_GAM10_REG, gammaCurveSlopeConfig->gam10);
    (void)OV7670_WriteReg(handle, OV7670_GAM11_REG, gammaCurveSlopeConfig->gam11);
    (void)OV7670_WriteReg(handle, OV7670_GAM12_REG, gammaCurveSlopeConfig->gam12);
    (void)OV7670_WriteReg(handle, OV7670_GAM13_REG, gammaCurveSlopeConfig->gam13);
    (void)OV7670_WriteReg(handle, OV7670_GAM14_REG, gammaCurveSlopeConfig->gam14);
    (void)OV7670_WriteReg(handle, OV7670_GAM15_REG, gammaCurveSlopeConfig->gam15);

    return kStatus_Success;
}

void OV7670_GetDefaultConfig(ov7670_config_t *config)
{
    config->outputFormat   = (ov7670_output_format_config_t *)&OV7670_FORMAT_RGB565;
    config->resolution     = (uint32_t)kVIDEO_ResolutionQQVGA;
    config->frameRate      = (ov7670_frame_rate_config_t *)&OV7670_25FPS_12MHZ_XCLK;
    config->contrast       = 0x30;
    config->brightness     = 0x10;
    config->advancedConfig = NULL;
}

status_t OV7670_Init(camera_device_handle_t *handle, const camera_config_t *config)
{
    status_t status;
    ov7670_resource_t *resource = (ov7670_resource_t *)(handle->resource);
    ov7670_config_t cameraConfig;

    if ((kVIDEO_PixelFormatYUYV != config->pixelFormat) && (kVIDEO_PixelFormatRGB565 != config->pixelFormat) &&
        (kVIDEO_PixelFormatRGBX4444 != config->pixelFormat) && (kVIDEO_PixelFormatXRGB4444 != config->pixelFormat) &&
        (kVIDEO_PixelFormatXRGB1555 != config->pixelFormat))
    {
        return kStatus_InvalidArgument;
    }

    if ((15U != config->framePerSec) && (30U != config->framePerSec) && (25U != config->framePerSec) &&
        (14U != config->framePerSec))
    {
        return kStatus_InvalidArgument;
    }

    if ((kCAMERA_InterfaceNonGatedClock != config->interface) && (kCAMERA_InterfaceGatedClock != config->interface))
    {
        return kStatus_InvalidArgument;
    }

    OV7670_GetDefaultConfig(&cameraConfig);
    cameraConfig.resolution = config->resolution;
    switch (resource->xclock)
    {
        case kOV7670_InputClock24MHZ:
            if (config->framePerSec == 30U)
            {
                cameraConfig.frameRate = &OV7670_30FPS_24MHZ_XCLK;
            }
            else if (config->framePerSec == 25U)
            {
                cameraConfig.frameRate = &OV7670_25FPS_24MHZ_XCLK;
            }
            else if (config->framePerSec == 15U)
            {
                cameraConfig.frameRate = &OV7670_15FPS_24MHZ_XCLK;
            }
            else if (config->framePerSec == 14U)
            {
                cameraConfig.frameRate = &OV7670_14FPS_24MHZ_XCLK;
            }
            else
            {
                assert(false);
            }
            break;
        case kOV7670_InputClock12MHZ:
            if (config->framePerSec == 30U)
            {
                cameraConfig.frameRate = &OV7670_30FPS_12MHZ_XCLK;
            }
            else if (config->framePerSec == 25U)
            {
                cameraConfig.frameRate = &OV7670_25FPS_12MHZ_XCLK;
            }
            else if (config->framePerSec == 15U)
            {
                cameraConfig.frameRate = &OV7670_15FPS_12MHZ_XCLK;
            }
            else if (config->framePerSec == 14U)
            {
                cameraConfig.frameRate = &OV7670_14FPS_12MHZ_XCLK;
            }
            else
            {
                assert(false);
            }
            break;
        case kOV7670_InputClock26MHZ:
            if (config->framePerSec == 30U)
            {
                cameraConfig.frameRate = &OV7670_30FPS_26MHZ_XCLK;
            }
            else if (config->framePerSec == 25U)
            {
                cameraConfig.frameRate = &OV7670_25FPS_26MHZ_XCLK;
            }
            else if (config->framePerSec == 15U)
            {
                cameraConfig.frameRate = &OV7670_15FPS_26MHZ_XCLK;
            }
            else if (config->framePerSec == 14U)
            {
                cameraConfig.frameRate = &OV7670_14FPS_26MHZ_XCLK;
            }
            else
            {
                assert(false);
            }
            break;
        case kOV7670_InputClock13MHZ:
            if (config->framePerSec == 30U)
            {
                cameraConfig.frameRate = &OV7670_30FPS_13MHZ_XCLK;
            }
            else if (config->framePerSec == 25U)
            {
                cameraConfig.frameRate = &OV7670_25FPS_13MHZ_XCLK;
            }
            else if (config->framePerSec == 15U)
            {
                cameraConfig.frameRate = &OV7670_15FPS_13MHZ_XCLK;
            }
            else if (config->framePerSec == 14U)
            {
                cameraConfig.frameRate = &OV7670_14FPS_13MHZ_XCLK;
            }
            else
            {
                assert(false);
            }
            break;
        default:
            assert(false);
            break;
    }

    switch (config->pixelFormat)
    {
        case kVIDEO_PixelFormatYUYV:
            cameraConfig.outputFormat = &OV7670_FORMAT_YUV422;
            break;

        case kVIDEO_PixelFormatXRGB1555:
            cameraConfig.outputFormat = &OV7670_FORMAT_RGB555;
            break;

        case kVIDEO_PixelFormatRGBX4444:
            cameraConfig.outputFormat = &OV7670_FORMAT_RGBx444;
            break;

        case kVIDEO_PixelFormatXRGB4444:
            cameraConfig.outputFormat = &OV7670_FORMAT_xRGB444;
            break;

        case kVIDEO_PixelFormatRGB565:
        default:
            cameraConfig.outputFormat = &OV7670_FORMAT_RGB565;
            break;
    }

    do
    {
        status = OV7670_CameraInit(handle, &cameraConfig);
    } while (status != kStatus_Success);

    return status;
}

status_t OV7670_Deinit(camera_device_handle_t *handle)
{
    return kStatus_Success;
}

status_t OV7670_Start(camera_device_handle_t *handle)
{
    return kStatus_Success;
}

status_t OV7670_Stop(camera_device_handle_t *handle)
{
    return kStatus_Success;
}

status_t OV7670_InitExt(camera_device_handle_t *handle, const camera_config_t *config, const void *specialConfig)
{
    return OV7670_Init(handle, config);
}

status_t OV7670_Control(camera_device_handle_t *handle, camera_device_cmd_t cmd, int32_t arg)
{
    return kStatus_InvalidArgument;
}
