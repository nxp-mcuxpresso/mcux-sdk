/*
 * Copyright 2017-2018, 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_video_common.h"
#include "fsl_display.h"
#include "fsl_adv7535.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ADV7535_CHIP_REVISION 0x14U

#define ADV7535_DSI_CEC_ADDR (0x78U >> 1)

#define ADV7535_I2C_WriteReg(handle, addr, reg, value)                                \
    VIDEO_I2C_WriteReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, (value), \
                       ((const adv7535_resource_t *)((handle)->resource))->i2cSendFunc)

#define ADV7535_I2C_ReadReg(handle, addr, reg, value)                                \
    VIDEO_I2C_ReadReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, (value), \
                      ((const adv7535_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define ADV7535_I2C_ModifyReg(handle, addr, reg, mask, value)                                \
    VIDEO_I2C_ModifyReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, mask, (value), \
                        ((const adv7535_resource_t *)((handle)->resource))->i2cReceiveFunc,  \
                        ((const adv7535_resource_t *)((handle)->resource))->i2cSendFunc)

#define ADV7535_CHECK_RET(x)           \
    do                                 \
    {                                  \
        status = (x);                  \
        if (kStatus_Success != status) \
        {                              \
            return status;             \
        }                              \
    } while (false)

typedef struct _adv7533_reg_val
{
    uint8_t reg;   /* Register index. */
    uint8_t mask;  /* Mask of the value. */
    uint8_t value; /* Register value. */
} adv7533_reg_val_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const adv7533_reg_val_t s_adv7533FixedRegs[] = {
    /* Fixed registers that must be set on power up. */
    /* 0x16[5:1] = 0b10000 */
    {0x16U, (0x1FU << 1U), (0x10U << 1)},

    /* 0x9A = 0xE0 */
    {0x9AU, 0xFF, 0x0E},

    /* 0xBA[7:3] = 0b01110 */
    {0xBAU, (0x1FU << 3U), (0x0EU << 3U)},

    /* 0xDE = 0x82 */
    {0xDEU, 0xFF, 0x82},

    /* 0xE4[6] = 1 */
    {0xE4U, (1 << 6), (1 << 6)},

    /* 0xE5 = 0x80 */
    {0xE5U, 0xFF, 0x80},
};

static const adv7533_reg_val_t s_adv7533CecFixedRegs[] = {
    /* CEC memory 0x15[5:4] = 1 */
    {0x15U, (3U << 4U), (1 << 4)},

    /* CEC memory 0x17[7:4] = 0b1101 */
    {0x17U, (0xFU << 4U), (0x0D << 4U)},

    /* CEC memory 0x24[4] = 0 */
    {0x24U, (1 << 4U), (0x0 << 4U)},

    /* CEC memory 0x57[0] = 1 */
    {0x57U, (1 << 0U), (0x1 << 0U)},

    /* CEC memory 0x57[4] = 1 */
    {0x57U, (1 << 4U), (0x1 << 4U)},
};

const display_operations_t adv7535_ops = {
    .init   = ADV7535_Init,
    .deinit = ADV7535_Deinit,
    .start  = ADV7535_Start,
    .stop   = ADV7535_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t ADV7535_I2C_ModifyRegs(display_handle_t *handle,
                                       uint8_t i2cAddr,
                                       const adv7533_reg_val_t values[],
                                       uint32_t len)
{
    status_t status = kStatus_Success;

    for (uint32_t i = 0; i < len; i++)
    {
        status = ADV7535_I2C_ModifyReg(handle, i2cAddr, values[i].reg, values[i].mask, values[i].value);

        if (kStatus_Success != status)
        {
            return status;
        }
    }

    return status;
}

status_t ADV7535_Init(display_handle_t *handle, const display_config_t *config)
{
    uint8_t chipRevision = 0U;
    uint8_t mainI2cAddr  = (((const adv7535_resource_t *)(handle->resource))->i2cAddr);
    status_t status;

    uint8_t lanes = config->dsiLanes;
    uint16_t total_width, total_height;

    if ((lanes <= 1U) || (lanes > 4U))
    {
        return kStatus_InvalidArgument;
    }

    /* Identify the device. */
    status = ADV7535_I2C_ReadReg(handle, mainI2cAddr, 0x00, &chipRevision);

    if (kStatus_Success != status)
    {
        return status;
    }

    if (ADV7535_CHIP_REVISION != chipRevision)
    {
        return kStatus_Fail;
    }

    /* -------- Power up sequence. -------- */
    /* 0x41[6] - HDMI Power-down (Power Up = 0 HPD Must be High). */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0x41, (0x01U << 6U), 0U << 6));

    /* 0xD6[6] - HPD Override (Override = 1). */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0xD6, (0x01U << 6U), 1U << 6));

    /*
     * DSI and CEC Map: 0x03[1] - Gate DSI LP Oscillator and DSI Bias Clock Powerdown, set to 0
     * to enable normal operation
     */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x03, (0x01U << 1U), 0U << 1));

    ADV7535_CHECK_RET(ADV7535_I2C_ModifyRegs(handle, mainI2cAddr, s_adv7533FixedRegs, ARRAY_SIZE(s_adv7533FixedRegs)));

    status =
        ADV7535_I2C_ModifyRegs(handle, ADV7535_DSI_CEC_ADDR, s_adv7533CecFixedRegs, ARRAY_SIZE(s_adv7533CecFixedRegs));
    if (kStatus_Success != status)
    {
        return status;
    }

    /* -------- Configure the video timing. --------*/

    /* Mute the HDMI. */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0xd5, 1U << 0, 1U << 0));

    /* Use automatic pixel clock divider: 0x16[2] = 0 */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x16, (0x01U << 2U), 0U << 2));

    /* MIPI DSI lanes: 0x1c[4:6]. */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x1c, (0x07U << 4U), (uint32_t)lanes << 4));

    /* Use internal timing generator, first disable it then configure: 0x27[7] = 1 */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x27, (0x01U << 7U), 1U << 7));

    /* Total width. */
    total_width = FSL_VIDEO_EXTRACT_WIDTH(config->resolution) + config->hfp + config->hbp + config->hsw;
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x28, (uint8_t)(total_width >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x29, (uint8_t)(total_width << 4U)));

    /* HSW. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2A, (uint8_t)(config->hsw >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2B, (uint8_t)(config->hsw << 4U)));

    /* HFP. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2C, (uint8_t)(config->hfp >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2D, (uint8_t)(config->hfp << 4U)));

    /* HBP. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2E, (uint8_t)(config->hbp >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x2F, (uint8_t)(config->hbp << 4U)));

    /* Total height. */
    total_height = FSL_VIDEO_EXTRACT_HEIGHT(config->resolution) + config->vfp + config->vbp + config->vsw;
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x30, (uint8_t)(total_height >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x31, (uint8_t)(total_height << 4U)));

    /* VSW. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x32, (uint8_t)(config->vsw >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x33, (uint8_t)(config->vsw << 4U)));

    /* VFP. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x34, (uint8_t)(config->vfp >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x35, (uint8_t)(config->vfp << 4U)));

    /* VBP. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x36, (uint8_t)(config->vbp >> 4U)));
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x37, (uint8_t)(config->vbp << 4U)));

    /* Toggle the 0x27[6] to use the new timing parameter. */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x27, (0x01U << 6U), 1U << 6));
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x27, (0x01U << 6U), 0U << 6));
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x27, (0x01U << 6U), 1U << 6));

    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0xd5, 1U << 0, 0U << 0));

    /* ----------- HDMI output. ----------- */
    /* 0xAF[1] - HDMI/DVI Mode Select (HDMI = 1) */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0xAF, (0x01U << 1U), 1U << 1));

    /* Disable the test pattern. */
    ADV7535_CHECK_RET(ADV7535_I2C_WriteReg(handle, ADV7535_DSI_CEC_ADDR, 0x55, 0x00));

    /* 0x40[7] - GC Packet Enable (Enable = 1) */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0x40, (0x01U << 7U), 1U << 7));

    /*
     * 0x4C[3:0] Color depth of video to RX.
     * 0000 = color depth not indicated
     * 0100 = 24 bits per pixel
     * 0101 = 30 bits per pixel
     * 0110 = 36 bits per pixel
     *
     * Here use 24 bpp
     */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0x4C, (0x0FU << 0U), 4U << 0));

    /* 0x49[1:0] - Down Dither Output Color Depth (12 bits = 0b10) */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0x49, (0x03U << 0U), 2U << 0));

    /* DSI and CEC Map: 0x03[7] - HDMI Output Enable (Enable = 1) */
    ADV7535_CHECK_RET(ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x03, (0x01U << 7U), 1U << 7));

    return kStatus_Success;
}

status_t ADV7535_Deinit(display_handle_t *handle)
{
    uint8_t mainI2cAddr = (((const adv7535_resource_t *)(handle->resource))->i2cAddr);

    /* 0x41[6] - HDMI Power-down */
    return ADV7535_I2C_ModifyReg(handle, mainI2cAddr, 0x41, (0x01U << 6U), 1U << 6);
}

status_t ADV7535_Start(display_handle_t *handle)
{
    /* DSI and CEC Map: 0x03[7] - HDMI Output Enable (Enable = 1) */
    return ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x03, (0x01U << 7U), 1U << 7);
}

status_t ADV7535_Stop(display_handle_t *handle)
{
    /* DSI and CEC Map: 0x03[7] - HDMI Output Enable (Enable = 1) */
    return ADV7535_I2C_ModifyReg(handle, ADV7535_DSI_CEC_ADDR, 0x03, (0x01U << 7U), 0U << 7);
}
