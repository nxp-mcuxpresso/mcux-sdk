/*
 * Copyright 2017-2018, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_video_common.h"
#include "fsl_camera.h"
#include "fsl_camera_device.h"
#include "fsl_ov5640.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OV5640_DelayMs VIDEO_DelayMs

#define OV5640_SCCB_ADDR            0x3CU
#define OV5640_RESOLUTION_PARAM_NUM 0x16U

#define OV5640_WriteReg(handle, reg, val)                             \
    SCCB_WriteReg(OV5640_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (val), \
                  ((ov5640_resource_t *)((handle)->resource))->i2cSendFunc)

#define OV5640_WriteMultiRegs(handle, reg, val, len)                             \
    SCCB_WriteMultiRegs(OV5640_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (val), len, \
                        ((ov5640_resource_t *)((handle)->resource))->i2cSendFunc)

#define OV5640_ReadReg(handle, reg, val)                             \
    SCCB_ReadReg(OV5640_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (val), \
                 ((ov5640_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define OV5640_ModifyReg(handle, reg, clrMask, val)                               \
    SCCB_ModifyReg(OV5640_SCCB_ADDR, kSCCB_RegAddr16Bit, (reg), (clrMask), (val), \
                   ((ov5640_resource_t *)((handle)->resource))->i2cReceiveFunc,   \
                   ((ov5640_resource_t *)((handle)->resource))->i2cSendFunc)

#define OV5640_POLARITY_CTRL00_VSYNC_MASK           (1U << 0U)
#define OV5640_POLARITY_CTRL00_HREF_MASK            (1U << 1U)
#define OV5640_POLARITY_CTRL00_GATE_PCLK_HREF_MASK  (1U << 2U)
#define OV5640_POLARITY_CTRL00_GATE_PCLK_VSYNC_MASK (1U << 3U)
#define OV5640_POLARITY_CTRL00_PCLK_MASK            (1U << 5U)

#define OV5640_SDE_CTRL0_REG  0x5580
#define OV5640_SDE_CTRL1_REG  0x5581
#define OV5640_SDE_CTRL2_REG  0x5582
#define OV5640_SDE_CTRL3_REG  0x5583
#define OV5640_SDE_CTRL4_REG  0x5584
#define OV5640_SDE_CTRL5_REG  0x5585
#define OV5640_SDE_CTRL6_REG  0x5586
#define OV5640_SDE_CTRL7_REG  0x5587
#define OV5640_SDE_CTRL8_REG  0x5588
#define OV5640_SDE_CTRL9_REG  0x5589
#define OV5640_SDE_CTRL10_REG 0x558a
#define OV5640_SDE_CTRL11_REG 0x558b
#define OV5640_SDE_CTRL12_REG 0x558c

#define OV5640_AWB_R_H_REG  0x3400
#define OV5640_AWB_R_L_REG  0x3401
#define OV5640_AWB_G_H_REG  0x3402
#define OV5640_AWB_G_L_REG  0x3403
#define OV5640_AWB_B_H_REG  0x3404
#define OV5640_AWB_B_L_REG  0x3405
#define OV5640_AWB_CTRL_REG 0x3406

#define OV5640_CHECK_RET(x)            \
    do                                 \
    {                                  \
        status = (x);                  \
        if (kStatus_Success != status) \
        {                              \
            return status;             \
        }                              \
    } while (false)

typedef struct _ov5640_reg_val
{
    uint16_t regAddr; /*!< Register address. */
    uint8_t regVal;   /*!<Register value. */
} ov5640_reg_val_t;

typedef struct _ov5640_resolution_param
{
    uint32_t resolution; /*!< Resolution, see @ref video_resolution_t and @ref FSL_VIDEO_RESOLUTION. */
    uint8_t param[OV5640_RESOLUTION_PARAM_NUM]; /*!< Parameter 0x3800 to 0x3813. */
} ov5640_resolution_param_t;

typedef struct
{
    uint32_t resolution;
    uint8_t framePerSec;
    uint8_t pllCtrl1;
    uint8_t pllCtrl2;
    uint8_t vfifoCtrl0C;
    uint8_t pclkDiv;
    uint8_t pclkPeriod;
} ov5640_clock_config_t;

typedef struct
{
    uint8_t lightMode;
    uint8_t awbCtrl;
    uint8_t awbR_H;
    uint8_t awbR_L;
    uint8_t awbG_H;
    uint8_t awbG_L;
    uint8_t awbB_H;
    uint8_t awbB_L;
} ov5640_light_mode_config_t;

typedef struct
{
    uint8_t effect;
    uint8_t sdeCtrl0;
    uint8_t sdeCtrl3;
    uint8_t sdeCtrl4;
} ov5640_special_effect_config_t;

typedef status_t (*ov5640_cmd_func_t)(camera_device_handle_t *handle, int32_t arg);

typedef struct
{
    camera_device_cmd_t cmd;
    ov5640_cmd_func_t func;
} ov5640_cmd_func_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
status_t OV5640_Init(camera_device_handle_t *handle, const camera_config_t *config);

status_t OV5640_Deinit(camera_device_handle_t *handle);

status_t OV5640_Control(camera_device_handle_t *handle, camera_device_cmd_t cmd, int32_t arg);

status_t OV5640_Start(camera_device_handle_t *handle);

status_t OV5640_Stop(camera_device_handle_t *handle);

status_t OV5640_InitExt(camera_device_handle_t *handle, const camera_config_t *config, const void *specialConfig);

status_t OV5640_SetSpecialEffect(camera_device_handle_t *handle, int32_t effect);

status_t OV5640_SetLightMode(camera_device_handle_t *handle, int32_t lightMode);

status_t OV5640_SetSaturation(camera_device_handle_t *handle, int32_t saturation);

status_t OV5640_SetContrast(camera_device_handle_t *handle, int32_t contrast);

status_t OV5640_SetBrightness(camera_device_handle_t *handle, int32_t brightness);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const ov5640_reg_val_t ov5640InitParam[] = {
    {0x3008, 0x42},

    /* System setting. */
    {0x3103, 0x03},
    {0x3000, 0x00},
    {0x3004, 0xff},
    {0x3002, 0x1c},
    {0x3006, 0xc3},
    {0x302e, 0x08},
    {0x3037, 0x13},
    {0x3108, 0x01},
    {0x3618, 0x00},
    {0x3612, 0x29},
    {0x3708, 0x64},
    {0x3709, 0x52},
    {0x370c, 0x03},
    {0x3820, 0x41},
    {0x3821, 0x07},
    {0x3630, 0x36},
    {0x3631, 0x0e},
    {0x3632, 0xe2},
    {0x3633, 0x12},
    {0x3621, 0xe0},
    {0x3704, 0xa0},
    {0x3703, 0x5a},
    {0x3715, 0x78},
    {0x3717, 0x01},
    {0x370b, 0x60},
    {0x3705, 0x1a},
    {0x3905, 0x02},
    {0x3906, 0x10},
    {0x3901, 0x0a},
    {0x3731, 0x12},
    {0x3600, 0x08},
    {0x3601, 0x33},
    {0x302d, 0x60},
    {0x3620, 0x52},
    {0x371b, 0x20},
    {0x471c, 0x50},
    {0x3a13, 0x43},
    {0x3a18, 0x00},
    {0x3a19, 0x7c},
    {0x3635, 0x13},
    {0x3636, 0x03},
    {0x3634, 0x40},
    {0x3622, 0x01},
    {0x3c01, 0x00},
    {0x3a00, 0x58},
    {0x4001, 0x02},
    {0x4004, 0x02},
    {0x4005, 0x1a},
    {0x5001, 0xa3},

    /* AEC */
    {0x3a0f, 0x30},
    {0x3a10, 0x28},
    {0x3a1b, 0x30},
    {0x3a1e, 0x26},
    {0x3a11, 0x60},
    {0x3a1f, 0x14},

    /* AWB */
    {0x5180, 0xff},
    {0x5181, 0xf2},
    {0x5182, 0x00},
    {0x5183, 0x14},
    {0x5184, 0x25},
    {0x5185, 0x24},
    {0x5186, 0x09},
    {0x5187, 0x09},
    {0x5188, 0x09},
    {0x5189, 0x88},
    {0x518a, 0x54},
    {0x518b, 0xee},
    {0x518c, 0xb2},
    {0x518d, 0x50},
    {0x518e, 0x34},
    {0x518f, 0x6b},
    {0x5190, 0x46},
    {0x5191, 0xf8},
    {0x5192, 0x04},
    {0x5193, 0x70},
    {0x5194, 0xf0},
    {0x5195, 0xf0},
    {0x5196, 0x03},
    {0x5197, 0x01},
    {0x5198, 0x04},
    {0x5199, 0x6c},
    {0x519a, 0x04},
    {0x519b, 0x00},
    {0x519c, 0x09},
    {0x519d, 0x2b},
    {0x519e, 0x38},

    /* Color Matrix */
    {0x5381, 0x1e},
    {0x5382, 0x5b},
    {0x5383, 0x08},
    {0x5384, 0x0a},
    {0x5385, 0x7e},
    {0x5386, 0x88},
    {0x5387, 0x7c},
    {0x5388, 0x6c},
    {0x5389, 0x10},
    {0x538a, 0x01},
    {0x538b, 0x98},

    /* sharp */
    {0x5300, 0x08},
    {0x5301, 0x30},
    {0x5302, 0x10},
    {0x5303, 0x00},
    {0x5304, 0x08},
    {0x5305, 0x30},
    {0x5306, 0x08},
    {0x5307, 0x16},
    {0x5309, 0x08},
    {0x530a, 0x30},
    {0x530b, 0x04},
    {0x530c, 0x06},

    /* Gamma */
    {0x5480, 0x01},
    {0x5481, 0x08},
    {0x5482, 0x14},
    {0x5483, 0x28},
    {0x5484, 0x51},
    {0x5485, 0x65},
    {0x5486, 0x71},
    {0x5487, 0x7d},
    {0x5488, 0x87},
    {0x5489, 0x91},
    {0x548a, 0x9a},
    {0x548b, 0xaa},
    {0x548c, 0xb8},
    {0x548d, 0xcd},
    {0x548e, 0xdd},
    {0x548f, 0xea},
    {0x5490, 0x1d},

    /* UV adjust. */
    {0x5580, 0x02},
    {0x5583, 0x40},
    {0x5584, 0x10},
    {0x5589, 0x10},
    {0x558a, 0x00},
    {0x558b, 0xf8},

    /* Lens correction. */
    {0x5800, 0x23},
    {0x5801, 0x14},
    {0x5802, 0x0f},
    {0x5803, 0x0f},
    {0x5804, 0x12},
    {0x5805, 0x26},
    {0x5806, 0x0c},
    {0x5807, 0x08},
    {0x5808, 0x05},
    {0x5809, 0x05},
    {0x580a, 0x08},
    {0x580b, 0x0d},
    {0x580c, 0x08},
    {0x580d, 0x03},
    {0x580e, 0x00},
    {0x580f, 0x00},
    {0x5810, 0x03},
    {0x5811, 0x09},
    {0x5812, 0x07},
    {0x5813, 0x03},
    {0x5814, 0x00},
    {0x5815, 0x01},
    {0x5816, 0x03},
    {0x5817, 0x08},
    {0x5818, 0x0d},
    {0x5819, 0x08},
    {0x581a, 0x05},
    {0x581b, 0x06},
    {0x581c, 0x08},
    {0x581d, 0x0e},
    {0x581e, 0x29},
    {0x581f, 0x17},
    {0x5820, 0x11},
    {0x5821, 0x11},
    {0x5822, 0x15},
    {0x5823, 0x28},
    {0x5824, 0x46},
    {0x5825, 0x26},
    {0x5826, 0x08},
    {0x5827, 0x26},
    {0x5828, 0x64},
    {0x5829, 0x26},
    {0x582a, 0x24},
    {0x582b, 0x22},
    {0x582c, 0x24},
    {0x582d, 0x24},
    {0x582e, 0x06},
    {0x582f, 0x22},
    {0x5830, 0x40},
    {0x5831, 0x42},
    {0x5832, 0x24},
    {0x5833, 0x26},
    {0x5834, 0x24},
    {0x5835, 0x22},
    {0x5836, 0x22},
    {0x5837, 0x26},
    {0x5838, 0x44},
    {0x5839, 0x24},
    {0x583a, 0x26},
    {0x583b, 0x28},
    {0x583c, 0x42},
    {0x583d, 0xce},
};

static const ov5640_resolution_param_t resolutionParam[] = {
    {
        .resolution = (uint32_t)kVIDEO_ResolutionVGA,
        .param      = {0x00, 0x00, 0x00, 0x04, 0x0a, 0x3f, 0x07, 0x9b, 0x02, 0x80, 0x01,
                  0xe0, 0x07, 0x68, 0x03, 0xd8, 0x00, 0x10, 0x00, 0x06, 0x31, 0x31},
    },
    {
        .resolution = (uint32_t)kVIDEO_ResolutionQVGA,
        .param      = {0x00, 0x00, 0x00, 0x04, 0x0a, 0x3f, 0x07, 0x9b, 0x01, 0x40, 0x00,
                  0xf0, 0x07, 0x68, 0x03, 0xd8, 0x00, 0x10, 0x00, 0x06, 0x31, 0x31},
    },
    {
        .resolution = FSL_VIDEO_RESOLUTION(480, 272),
        .param      = {0x00, 0x00, 0x00, 0xfa, 0x0a, 0x3f, 0x06, 0xa9, 0x01, 0xE0, 0x01,
                  0x10, 0x07, 0x64, 0x02, 0xe4, 0x00, 0x10, 0x00, 0x04, 0x31, 0x31},
    },
    {
        .resolution = (uint32_t)kVIDEO_Resolution720P,
        .param      = {0x00, 0x00, 0x00, 0xfa, 0x0a, 0x3f, 0x06, 0xa9, 0x05, 0x00, 0x02,
                  0xd0, 0x07, 0x64, 0x02, 0xe4, 0x00, 0x10, 0x00, 0x04, 0x31, 0x31},
    },
    {
        .resolution = (uint32_t)kVIDEO_Resolution1080P,
        .param      = {0x01, 0x50, 0x01, 0xb2, 0x08, 0xef, 0x05, 0xf1, 0x07, 0x80, 0x04,
                  0x38, 0x09, 0xc4, 0x04, 0x60, 0x00, 0x10, 0x00, 0x04, 0x11, 0x11},
    },
};

/* DVP */
static const ov5640_clock_config_t s_ov5640DvpClockConfigs[] = {
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionVGA,
        .framePerSec = 15,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x46,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x22,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionVGA,
        .framePerSec = 30,
        .pllCtrl1    = 0x11,
        .pllCtrl2    = 0x46,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x22,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionQVGA,
        .framePerSec = 15,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x46,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x22,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionQVGA,
        .framePerSec = 30,
        .pllCtrl1    = 0x11,
        .pllCtrl2    = 0x46,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x22,
    },
    {
        .resolution  = FSL_VIDEO_RESOLUTION(480, 272),
        .framePerSec = 15,
        .pllCtrl1    = 0x41,
        .pllCtrl2    = 0x69,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x16,
    },
    {
        .resolution  = FSL_VIDEO_RESOLUTION(480, 272),
        .framePerSec = 30,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x69,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x16,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution720P,
        .framePerSec = 15,
        .pllCtrl1    = 0x41,
        .pllCtrl2    = 0x69,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x16,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution720P,
        .framePerSec = 30,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x69,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x16,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution1080P,
        .framePerSec = 15,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x69,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x16,
    },
};

/* MIPI */
static const ov5640_clock_config_t s_ov5640MipiClockConfigs[] = {
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionVGA,
        .framePerSec = 15,
        .pllCtrl1    = 0x22,
        .pllCtrl2    = 0x38,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionVGA,
        .framePerSec = 30,
        .pllCtrl1    = 0x14,
        .pllCtrl2    = 0x38,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionQVGA,
        .framePerSec = 15,
        .pllCtrl1    = 0x22,
        .pllCtrl2    = 0x38,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_ResolutionQVGA,
        .framePerSec = 30,
        .pllCtrl1    = 0x14,
        .pllCtrl2    = 0x38,
        .vfifoCtrl0C = 0x22,
        .pclkDiv     = 0x02,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution720P,
        .framePerSec = 15,
        .pllCtrl1    = 0x41,
        .pllCtrl2    = 0x54,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution720P,
        .framePerSec = 30,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x54,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution1080P,
        .framePerSec = 15,
        .pllCtrl1    = 0x21,
        .pllCtrl2    = 0x54,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x0a,
    },
    {
        .resolution  = (uint32_t)kVIDEO_Resolution1080P,
        .framePerSec = 30,
        .pllCtrl1    = 0x11,
        .pllCtrl2    = 0x54,
        .vfifoCtrl0C = 0x20,
        .pclkDiv     = 0x04,
        .pclkPeriod  = 0x0a,
    },
};

static const ov5640_light_mode_config_t s_ov5640LightModeConfigs[] = {
    /* Auto. */
    {
        .lightMode = CAMERA_LIGHT_MODE_AUTO,
        .awbCtrl   = 0x00,
        .awbR_H    = 0x04,
        .awbR_L    = 0x00,
        .awbG_H    = 0x04,
        .awbG_L    = 0x00,
        .awbB_H    = 0x04,
        .awbB_L    = 0x00,
    },
    /* Sunny. */
    {
        .lightMode = CAMERA_LIGHT_MODE_SUNNY,
        .awbCtrl   = 0x01,
        .awbR_H    = 0x06,
        .awbR_L    = 0x1c,
        .awbG_H    = 0x04,
        .awbG_L    = 0x00,
        .awbB_H    = 0x04,
        .awbB_L    = 0xf3,
    },
    /* Office. */
    {
        .lightMode = CAMERA_LIGHT_MODE_OFFICE,
        .awbCtrl   = 0x01,
        .awbR_H    = 0x05,
        .awbR_L    = 0x48,
        .awbG_H    = 0x04,
        .awbG_L    = 0x00,
        .awbB_H    = 0x07,
        .awbB_L    = 0xcf,
    },
    /* Cloudy. */
    {
        .lightMode = CAMERA_LIGHT_MODE_CLOUDY,
        .awbCtrl   = 0x01,
        .awbR_H    = 0x06,
        .awbR_L    = 0x48,
        .awbG_H    = 0x04,
        .awbG_L    = 0x00,
        .awbB_H    = 0x04,
        .awbB_L    = 0xd3,
    },
    /* Home. */
    {
        .lightMode = CAMERA_LIGHT_MODE_HOME,
        .awbCtrl   = 0x01,
        .awbR_H    = 0x04,
        .awbR_L    = 0x10,
        .awbG_H    = 0x04,
        .awbG_L    = 0x00,
        .awbB_H    = 0x08,
        .awbB_L    = 0x40,
    },
};

static const ov5640_special_effect_config_t s_ov5640SpecialEffectConfigs[] = {
    /* Normal. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_NORMAL,
        .sdeCtrl0 = 0x06,
        .sdeCtrl3 = 0x40,
        .sdeCtrl4 = 0x10,
    },
    /* Bluish. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_BLUISH,
        .sdeCtrl0 = 0x1e,
        .sdeCtrl3 = 0xa0,
        .sdeCtrl4 = 0x40,
    },
    /* Redish. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_REDISH,
        .sdeCtrl0 = 0x1e,
        .sdeCtrl3 = 0x80,
        .sdeCtrl4 = 0xc0,
    },
    /* B & W */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_BW,
        .sdeCtrl0 = 0x1e,
        .sdeCtrl3 = 0x80,
        .sdeCtrl4 = 0x80,
    },
    /* Sepia. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_SEPIA,
        .sdeCtrl0 = 0x1e,
        .sdeCtrl3 = 0x40,
        .sdeCtrl4 = 0xa0,
    },
    /* Negtive. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_NEGTIVE,
        .sdeCtrl0 = 0x40,
        .sdeCtrl3 = 0x40,
        .sdeCtrl4 = 0x10,
    },
    /* Greenish. */
    {
        .effect   = CAMERA_SPECIAL_EFFECT_GREENISH,
        .sdeCtrl0 = 0x1e,
        .sdeCtrl3 = 0x60,
        .sdeCtrl4 = 0x60,
    },
};

static const ov5640_cmd_func_map_t s_ov5640CmdFuncMap[] = {
    {
        kCAMERA_DeviceLightMode,
        OV5640_SetLightMode,
    },
    {
        kCAMERA_DeviceSaturation,
        OV5640_SetSaturation,
    },
    {
        kCAMERA_DeviceBrightness,
        OV5640_SetBrightness,
    },
    {
        kCAMERA_DeviceContrast,
        OV5640_SetContrast,
    },
    {
        kCAMERA_DeviceSpecialEffect,
        OV5640_SetSpecialEffect,
    },
};

const camera_device_operations_t ov5640_ops = {
    .init     = OV5640_Init,
    .deinit   = OV5640_Deinit,
    .start    = OV5640_Start,
    .stop     = OV5640_Stop,
    .control  = OV5640_Control,
    .init_ext = OV5640_InitExt,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t OV5640_LoadRegVal(camera_device_handle_t *handle, const ov5640_reg_val_t regVal[], uint32_t num)
{
    uint32_t i;
    status_t status;

    for (i = 0; i < num; i++)
    {
        status = OV5640_WriteReg(handle, regVal[i].regAddr, regVal[i].regVal);

        if (kStatus_Success != status)
        {
            return status;
        }
    }

    return kStatus_Success;
}

static status_t OV5640_SoftwareReset(camera_device_handle_t *handle)
{
    ov5640_reg_val_t param[] = {{0x3103, 0x11}, {0x3008, 0x82}};

    return OV5640_LoadRegVal(handle, param, ARRAY_SIZE(param));
}

static const uint8_t *OV5640_GetResolutionParam(uint32_t resolution)
{
    /*
     * This function returns the parameter for specific resolution, if
     * the resolution is not supported, returns NULL.
     */
    uint32_t i;

    for (i = 0; i < ARRAY_SIZE(resolutionParam); i++)
    {
        if (resolution == resolutionParam[i].resolution)
        {
            return resolutionParam[i].param;
        }
    }

    return NULL;
}

static const ov5640_clock_config_t *OV5640_GetClockConfig(const camera_config_t *config)
{
    uint32_t i;

    if (kCAMERA_InterfaceMIPI == config->interface)
    {
        for (i = 0; i < ARRAY_SIZE(s_ov5640MipiClockConfigs); i++)
        {
            if ((config->framePerSec == s_ov5640MipiClockConfigs[i].framePerSec) &&
                (config->resolution == s_ov5640MipiClockConfigs[i].resolution))
            {
                return &s_ov5640MipiClockConfigs[i];
            }
        }
    }
    else
    {
        for (i = 0; i < ARRAY_SIZE(s_ov5640DvpClockConfigs); i++)
        {
            if ((config->framePerSec == s_ov5640DvpClockConfigs[i].framePerSec) &&
                (config->resolution == s_ov5640DvpClockConfigs[i].resolution))
            {
                return &s_ov5640DvpClockConfigs[i];
            }
        }
    }

    return NULL;
}

static status_t OV5640_SetPixelFormat(camera_device_handle_t *handle, video_pixel_format_t pixelFormat)
{
    status_t status;
    uint8_t param[2];

    switch (pixelFormat)
    {
        case kVIDEO_PixelFormatYUYV:
            param[0] = 0x3F;
            param[1] = 0x00;
            break;

        case kVIDEO_PixelFormatRGB565:
        default:
            param[0] = 0x6f;
            param[1] = 0x01;
            break;
    }

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4300, param[0]));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x501f, param[1]));

    return kStatus_Success;
}

status_t OV5640_Init(camera_device_handle_t *handle, const camera_config_t *config)
{
    status_t status;
    ov5640_resource_t *resource = (ov5640_resource_t *)(handle->resource);
    uint8_t reg;
    const ov5640_clock_config_t *clockConfig;

    /* Verify the configuration. */
    const uint8_t *resParam = OV5640_GetResolutionParam(config->resolution);

    if (NULL == resParam)
    {
        return kStatus_InvalidArgument;
    }

    if ((kVIDEO_PixelFormatYUYV != config->pixelFormat) && (kVIDEO_PixelFormatRGB565 != config->pixelFormat))
    {
        return kStatus_InvalidArgument;
    }

    if ((kCAMERA_InterfaceNonGatedClock != config->interface) && (kCAMERA_InterfaceGatedClock != config->interface) &&
        (kCAMERA_InterfaceCCIR656 != config->interface) && (kCAMERA_InterfaceMIPI != config->interface))
    {
        return kStatus_InvalidArgument;
    }

    /* Only support 2 data lanes. */
    if ((kCAMERA_InterfaceMIPI == config->interface) && (2U != config->csiLanes))
    {
        return kStatus_InvalidArgument;
    }

    clockConfig = OV5640_GetClockConfig(config);

    if (NULL == clockConfig)
    {
        return kStatus_InvalidArgument;
    }

    resource->pullPowerDownPin(true);
    resource->pullResetPin(false);

    /* Delay 5ms. */
    OV5640_DelayMs(5);

    resource->pullPowerDownPin(false);

    /* Delay 1ms. */
    OV5640_DelayMs(1);

    resource->pullResetPin(true);

    /* Delay 20ms. */
    OV5640_DelayMs(20);

    OV5640_CHECK_RET(OV5640_SoftwareReset(handle));

    /* Delay 5ms. */
    OV5640_DelayMs(5);

    /* Initialize. */
    status = OV5640_LoadRegVal(handle, ov5640InitParam, ARRAY_SIZE(ov5640InitParam));
    if (kStatus_Success != status)
    {
        return status;
    }

    /* Resolution. */
    OV5640_CHECK_RET(OV5640_WriteMultiRegs(handle, 0x3800, resParam, OV5640_RESOLUTION_PARAM_NUM));

    if ((uint32_t)kVIDEO_Resolution1080P == config->resolution)
    {
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3709, 0x12));
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3821, 0x06));
    }

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x302c, 0xc2));

    /* Pixel format. */
    OV5640_CHECK_RET(OV5640_SetPixelFormat(handle, config->pixelFormat));

    /* Clock. */
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3035, clockConfig->pllCtrl1));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3036, clockConfig->pllCtrl2));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x460c, clockConfig->vfifoCtrl0C));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3824, clockConfig->pclkDiv));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4837, clockConfig->pclkPeriod));

    /* Interface. */
    if (kCAMERA_InterfaceMIPI == config->interface)
    {
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3034, 0x18));

        /* Set Frex, Vsync, Href, PCLK, data, GPIO to input. */
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3017, 0x00));
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3018, 0x00));

        /*
         * Set to MIPI mode, set data lane. Currently only support 2 data lanes,
         * if need to use 1 data lane, write 0x25 to register 0x300e.
         */
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x300e, 0x45));

        /* Virtual channel. */
        OV5640_CHECK_RET(OV5640_ModifyReg(handle, 0x4814, (3U << 6), (uint8_t)(config->mipiChannel) << 6));

        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4800, 0x04));
    }
    else
    {
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3034, 0x1a));

        /* Set Frex, Vsync, Href, PCLK, data, GPIO to output. */
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3017, 0xFF));
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3018, 0xFF));

        /* DVP mode */
        OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x300e, 0x58));

        if (kCAMERA_InterfaceCCIR656 == config->interface)
        {
            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4719, 0x01));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4730, 0x01));
        }
    }

    /* Signal polarity */
    reg = 0;
    if ((uint32_t)kCAMERA_HrefActiveHigh != (config->controlFlags & (uint32_t)kCAMERA_HrefActiveHigh))
    {
        reg |= OV5640_POLARITY_CTRL00_HREF_MASK;
    }
    if ((uint32_t)kCAMERA_VsyncActiveHigh != (config->controlFlags & (uint32_t)kCAMERA_VsyncActiveHigh))
    {
        reg |= OV5640_POLARITY_CTRL00_VSYNC_MASK;
    }
    if ((uint32_t)kCAMERA_DataLatchOnRisingEdge == (config->controlFlags & (uint32_t)kCAMERA_DataLatchOnRisingEdge))
    {
        reg |= OV5640_POLARITY_CTRL00_PCLK_MASK;
    }

    if (kCAMERA_InterfaceNonGatedClock == config->interface)
    {
        reg |= OV5640_POLARITY_CTRL00_GATE_PCLK_HREF_MASK | OV5640_POLARITY_CTRL00_GATE_PCLK_VSYNC_MASK;
    }

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x4740, reg));

    /* Lenc on, raw gamma on, BPC on, WPC on, CIP on. */
    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x5000, 0xa7));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3008, 0x02));

    return kStatus_Success;
}

status_t OV5640_Deinit(camera_device_handle_t *handle)
{
    ((ov5640_resource_t *)(handle->resource))->pullPowerDownPin(true);

    return kStatus_Success;
}

status_t OV5640_Control(camera_device_handle_t *handle, camera_device_cmd_t cmd, int32_t arg)
{
    for (uint8_t i = 0; i < ARRAY_SIZE(s_ov5640CmdFuncMap); i++)
    {
        if (s_ov5640CmdFuncMap[i].cmd == cmd)
        {
            return s_ov5640CmdFuncMap[i].func(handle, arg);
        }
    }

    return kStatus_InvalidArgument;
}

status_t OV5640_Start(camera_device_handle_t *handle)
{
    return OV5640_WriteReg(handle, 0x3008, 0x02);
}

status_t OV5640_Stop(camera_device_handle_t *handle)
{
    return OV5640_WriteReg(handle, 0x3008, 0x42);
}

status_t OV5640_InitExt(camera_device_handle_t *handle, const camera_config_t *config, const void *specialConfig)
{
    return OV5640_Init(handle, config);
}

status_t OV5640_SetBrightness(camera_device_handle_t *handle, int32_t brightness)
{
    status_t status;

    if ((brightness < -4) || (brightness > 4))
    {
        return kStatus_InvalidArgument;
    }

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x03));
    if (brightness >= 0)
    {
        status = OV5640_WriteReg(handle, OV5640_SDE_CTRL8_REG, 0x01);
    }
    else
    {
        brightness = -brightness;
        status     = OV5640_WriteReg(handle, OV5640_SDE_CTRL8_REG, 0x09);
    }

    if (kStatus_Success != status)
    {
        return status;
    }

    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL7_REG, ((uint8_t)brightness) << 4U));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x13));
    return OV5640_WriteReg(handle, 0x3212, 0xa3);
}

status_t OV5640_SetContrast(camera_device_handle_t *handle, int32_t contrast)
{
    status_t status;
    uint8_t regVal;

    if ((-4 > contrast) || (4 < contrast))
    {
        return kStatus_InvalidArgument;
    }

    contrast = 0x20 + contrast * 0x04;
    regVal   = (uint8_t)contrast;

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x03));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL0_REG, 0x04));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL5_REG, regVal));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL6_REG, regVal));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x13));
    return OV5640_WriteReg(handle, 0x3212, 0xa3);
}

status_t OV5640_SetSaturation(camera_device_handle_t *handle, int32_t saturation)
{
    status_t status;
    uint8_t regVal;

    if ((-4 > saturation) || (4 < saturation))
    {
        return kStatus_InvalidArgument;
    }

    saturation = 0x40 + saturation * 0x10;
    regVal     = (uint8_t)saturation;

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x03));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL0_REG, 0x02));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL3_REG, regVal));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL4_REG, regVal));
    OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL8_REG, 0x41));

    OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x13));
    return OV5640_WriteReg(handle, 0x3212, 0xa3);
}

status_t OV5640_SetLightMode(camera_device_handle_t *handle, int32_t lightMode)
{
    status_t status;
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_ov5640LightModeConfigs); i++)
    {
        if (lightMode == (int32_t)s_ov5640LightModeConfigs[i].lightMode)
        {
            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x03));

            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_CTRL_REG, s_ov5640LightModeConfigs[i].awbCtrl));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_R_H_REG, s_ov5640LightModeConfigs[i].awbR_H));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_R_L_REG, s_ov5640LightModeConfigs[i].awbR_L));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_G_H_REG, s_ov5640LightModeConfigs[i].awbG_H));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_G_L_REG, s_ov5640LightModeConfigs[i].awbG_L));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_B_H_REG, s_ov5640LightModeConfigs[i].awbB_H));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_AWB_B_L_REG, s_ov5640LightModeConfigs[i].awbB_L));

            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x13));
            return OV5640_WriteReg(handle, 0x3212, 0xa3);
        }
    }

    /* No configuration found. */
    return kStatus_InvalidArgument;
}

status_t OV5640_SetSpecialEffect(camera_device_handle_t *handle, int32_t effect)
{
    status_t status;
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_ov5640SpecialEffectConfigs); i++)
    {
        if (effect == (int32_t)s_ov5640SpecialEffectConfigs[i].effect)
        {
            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x03));

            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL0_REG, s_ov5640SpecialEffectConfigs[i].sdeCtrl0));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL3_REG, s_ov5640SpecialEffectConfigs[i].sdeCtrl3));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, OV5640_SDE_CTRL4_REG, s_ov5640SpecialEffectConfigs[i].sdeCtrl4));

            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x5003, 0x08));
            OV5640_CHECK_RET(OV5640_WriteReg(handle, 0x3212, 0x13));
            return OV5640_WriteReg(handle, 0x3212, 0xa3);
        }
    }

    /* No configuration found. */
    return kStatus_InvalidArgument;
}
