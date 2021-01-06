/*
 * Copyright 2018, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_video_common.h"
#include "fsl_display.h"
#include "fsl_it6263.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IT6263_LVDS_ID (0x66U / 2U)

#define IT6263_HDMI_VENDER_ID 0x01ca1376U
#define IT6263_LVDS_VENDER_ID 0x15ca6162U

#define IT6263_I2C_WriteReg(handle, addr, reg, value)                                 \
    VIDEO_I2C_WriteReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, (value), \
                       ((const it6263_resource_t *)((handle)->resource))->i2cSendFunc)

#define IT6263_I2C_ReadReg(handle, addr, reg, value)                                 \
    VIDEO_I2C_ReadReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, (value), \
                      ((const it6263_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define IT6263_I2C_ModifyReg(handle, addr, reg, mask, value)                                 \
    VIDEO_I2C_ModifyReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, mask, (value), \
                        ((const it6263_resource_t *)((handle)->resource))->i2cReceiveFunc,   \
                        ((const it6263_resource_t *)((handle)->resource))->i2cSendFunc)

#define IT6263_I2C_ReadRegs(handle, addr, reg, value, len)                              \
    VIDEO_I2C_ReadReg(addr, kVIDEO_RegAddr8Bit, (reg), (video_reg_width_t)len, (value), \
                      ((const it6263_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define IT6263_SET_LVDS_ID_REG    0x1DU
#define IT6263_ENABLE_LVDS_ID_REG 0x1EU

#define IT6263_HDMI_VENDER_ID_REG 0
#define IT6263_LVDS_VENDER_ID_REG 0

#define IT6263_LVDS_COLOR_DEPTH(x)   ((x) << 0U)
#define IT6263_LVDS_COLOR_DEPTH_MASK (3U << 0U)
#define IT6263_LVDS_MAP(x)           ((x) << 4U)
#define IT6263_LVDS_MAP_MASK         (1U << 4U)
#define IT6263_LVDS_DUAL_MODE(x)     ((x) << 7U)
#define IT6263_LVDS_DUAL_MODE_MASK   (1U << 7U)

/* Color depth. */
#define IT6263_LVDS_COLOR_6BIT  IT6263_LVDS_COLOR_DEPTH(0U)
#define IT6263_LVDS_COLOR_8BIT  IT6263_LVDS_COLOR_DEPTH(1U)
#define IT6263_LVDS_COLOR_10BIT IT6263_LVDS_COLOR_DEPTH(2U)
#define IT6263_LVDS_COLOR_12BIT IT6263_LVDS_COLOR_DEPTH(3U)

/* Pixel map. */
#define IT6263_LVDS_JEIDA IT6263_LVDS_MAP(0U)
#define IT6263_LVDS_VESA  IT6263_LVDS_MAP(1U)

/* Dual mode. */
#define IT6263_LVDS_DISO   IT6263_LVDS_DUAL_MODE(1U) /* Dual In / Single Out */
#define IT6263_LVDS_DIRECT IT6263_LVDS_DUAL_MODE(0U) /* Single In / Single Out or Dual In / Dual Out */

/* HDMI register 0x04. */
#define HDMI_REG_SW_RST                0x04U
#define IT6263_HDMI_04_SOFTREFRST_MASK (1U << 5U)
#define IT6263_HDMI_04_SOFTARST_MASK   (1U << 4U)
#define IT6263_HDMI_04_SOFTVRST_MASK   (1U << 3U)
#define IT6263_HDMI_04_AUDRST_MASK     (1U << 2U)
#define IT6263_HDMI_04_HDCPRST_MASK    (1U << 0U)
#define IT6263_HDMI_04_ALLRST_MASK     ((1U << 5U) | (1U << 4U) | (1U << 3U) | (1U << 2U) | (1U << 0U))

/* HDMI register 0x61. */
#define IT6263_HDMI_61_DRV_PWD_MASK (1U << 5U)
#define IT6263_HDMI_61_DRV_RST_MASK (1U << 4U)

/* HDMI register 0xC1. */
#define IT6263_HDMI_C1_AVMUTE_MASK (1U << 0U)

/* HDMI register 0xC6. */
#define IT6263_HDMI_C6_PKTGENCTRLRPT_MASK (1U << 1U)
#define IT6263_HDMI_C6_PKTGENCTRLEN_MASK  (1U << 0U)

/* LVDS register 0x05. */
#define IT6263_LVDS_05_SOFTREFRST_MASK (1U << 0U)
#define IT6263_LVDS_05_SOFTRST_MASK    (1U << 1U)

#define IT6263_CHECK_RET(x)            \
    do                                 \
    {                                  \
        status = (x);                  \
        if (kStatus_Success != status) \
        {                              \
            return status;             \
        }                              \
    } while (false)

/*******************************************************************************
 * Variables
 ******************************************************************************/
const display_operations_t it6263_ops = {
    .init   = IT6263_Init,
    .deinit = IT6263_Deinit,
    .start  = IT6263_Start,
    .stop   = IT6263_Stop,
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static void IT6263_HardwareReset(display_handle_t *handle)
{
    const it6263_resource_t *resource = (const it6263_resource_t *)(handle->resource);

    resource->pullResetPin(true);

    VIDEO_DelayMs(1);

    resource->pullResetPin(false);

    VIDEO_DelayMs(40);

    resource->pullResetPin(true);

    VIDEO_DelayMs(10);
}

static status_t IT6263_LVDSReset(display_handle_t *handle)
{
    status_t status;

    /* Reset the AFE PLL. */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x3C, 0x1, 0x0));
    VIDEO_DelayMs(1);
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x3C, 0x1, 0x1));

    /* Reset the PCLK. */
    status =
        IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x05, IT6263_LVDS_05_SOFTRST_MASK, IT6263_LVDS_05_SOFTRST_MASK);
    if (kStatus_Success != status)
    {
        return status;
    }

    VIDEO_DelayMs(1);
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x05, IT6263_LVDS_05_SOFTRST_MASK, 0));

    VIDEO_DelayMs(1);

    return kStatus_Success;
}

static status_t IT6263_InitLVDS_ID(display_handle_t *handle)
{
    status_t status;

    uint8_t i2cAddr = (((const it6263_resource_t *)(handle->resource))->i2cAddr) / 2U;

    status = IT6263_I2C_WriteReg(handle, i2cAddr, IT6263_SET_LVDS_ID_REG, IT6263_LVDS_ID * 2U);

    if (kStatus_Success == status)
    {
        status = IT6263_I2C_WriteReg(handle, i2cAddr, IT6263_ENABLE_LVDS_ID_REG, 1);
    }

    return status;
}

static status_t IT6263_Identify(display_handle_t *handle)
{
    status_t status;
    uint32_t hdmiVendorID = 0U;
    uint32_t lvdsVendorID = 0U;

    uint8_t i2cAddr = (((const it6263_resource_t *)(handle->resource))->i2cAddr) / 2U;

    status = IT6263_I2C_ReadRegs(handle, i2cAddr, IT6263_HDMI_VENDER_ID_REG, &hdmiVendorID, sizeof(hdmiVendorID));
    if (kStatus_Success != status)
    {
        return status;
    }

    status =
        IT6263_I2C_ReadRegs(handle, IT6263_LVDS_ID, IT6263_LVDS_VENDER_ID_REG, &lvdsVendorID, sizeof(lvdsVendorID));
    if (kStatus_Success != status)
    {
        return status;
    }

    if ((hdmiVendorID != IT6263_HDMI_VENDER_ID) || (lvdsVendorID != IT6263_LVDS_VENDER_ID))
    {
        return kStatus_Fail;
    }
    else
    {
        return kStatus_Success;
    }
}

static status_t IT6263_InitLVDS(display_handle_t *handle)
{
    status_t status;
    uint8_t mask;
    uint8_t val;

    /* Configure LVDS. */
    mask = IT6263_LVDS_COLOR_DEPTH_MASK | IT6263_LVDS_MAP_MASK | IT6263_LVDS_DUAL_MODE_MASK;
    val  = IT6263_LVDS_COLOR_8BIT | IT6263_LVDS_JEIDA | IT6263_LVDS_DIRECT;

    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x2C, mask, val));

    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x52, 0x02, 0x00));

    /* AFE */
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, IT6263_LVDS_ID, 0x3E, 0xAA));
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, IT6263_LVDS_ID, 0x3F, 0x02));
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, IT6263_LVDS_ID, 0x47, 0xAA));
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, IT6263_LVDS_ID, 0x48, 0x02));
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, IT6263_LVDS_ID, 0x4F, 0x11));

    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, IT6263_LVDS_ID, 0x3C, 0x07, 0));

    return kStatus_Success;
}

status_t IT6263_Init(display_handle_t *handle, const display_config_t *config)
{
    assert(handle);

    status_t status;

    uint8_t i2cAddr = ((const it6263_resource_t *)(handle->resource))->i2cAddr / 2U;

    IT6263_HardwareReset(handle);

    /* Software reset. */
    status = IT6263_I2C_WriteReg(handle, i2cAddr, 0x04, IT6263_HDMI_04_ALLRST_MASK);
    if (kStatus_Success != status)
    {
        return status;
    }

    VIDEO_DelayMs(1);

    status = IT6263_InitLVDS_ID(handle);
    if (kStatus_Success != status)
    {
        return status;
    }

    status = IT6263_Identify(handle);
    if (kStatus_Success != status)
    {
        return status;
    }

    IT6263_CHECK_RET(IT6263_LVDSReset(handle));

    IT6263_CHECK_RET(IT6263_InitLVDS(handle));

    /*
     * Set color:
     * 0 RGB
     * 1 YUV422
     * 2 YUV444
     */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x70, 0x03U << 6U, 0));

    /*
     * No color space conversion.
     * 0: No conversion
     * 1: RGB -> YUV
     * 2: YUV -> RGB
     */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x72, 0x03U << 0U, 0));

    /*
     * HDMI color dpeth:
     * 000 - color depth is not indicate (as 8bit)
     * 100 - 8/8/8 bit color
     * 101 - 10/10/10 bit color
     * 110 - 12/12/12 bit color)
     */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0xC1, 0x07U << 4U, 0x04U << 0U));

    /* Select HDMI. */
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0xC0, 0x01));

    /* Set AFE */
    if (config->pixelClock_Hz > 80000000U)
    {
        IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x62, 0x88));
        IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x64, 0x84));
    }
    else
    {
        IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x62, 0x18));
        IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x64, 0x0C));
    }
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x63, 0x10));

    /*
     * Output Color Mode
     * 00 - RGB444 mode
     * 01 - YCbCr422 mode
     * 10 - YCbCr444 mode
     */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x0F, 0x03U << 0U, 0x01U << 0U)); /* Bank 0 */
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x58, 0x03U << 5U, 0x00U << 5U));
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x0F, 0x03U << 0U, 0x00U << 0U)); /* Bank 1 */

    /* software video reset */
    status = IT6263_I2C_ModifyReg(handle, i2cAddr, 0x04, IT6263_HDMI_04_SOFTVRST_MASK, IT6263_HDMI_04_SOFTVRST_MASK);
    if (kStatus_Success != status)
    {
        return status;
    }

    VIDEO_DelayMs(100);

    return kStatus_Success;
}

status_t IT6263_Deinit(display_handle_t *handle)
{
    const it6263_resource_t *resource = (const it6263_resource_t *)(handle->resource);

    resource->pullResetPin(false);

    return kStatus_Success;
}

status_t IT6263_Start(display_handle_t *handle)
{
    status_t status;

    uint8_t i2cAddr = ((const it6263_resource_t *)(handle->resource))->i2cAddr / 2U;

    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0x04, IT6263_HDMI_04_SOFTVRST_MASK, 0));
    IT6263_CHECK_RET(IT6263_I2C_WriteReg(handle, i2cAddr, 0x61, 0));
    IT6263_CHECK_RET(IT6263_I2C_ModifyReg(handle, i2cAddr, 0xC1, IT6263_HDMI_C1_AVMUTE_MASK, 0));
    return IT6263_I2C_WriteReg(handle, i2cAddr, 0xc6,
                               IT6263_HDMI_C6_PKTGENCTRLRPT_MASK | IT6263_HDMI_C6_PKTGENCTRLEN_MASK);
}

status_t IT6263_Stop(display_handle_t *handle)
{
    status_t status;
    uint8_t i2cAddr = ((const it6263_resource_t *)(handle->resource))->i2cAddr / 2U;

    status = IT6263_I2C_ModifyReg(handle, i2cAddr, 0xC1, IT6263_HDMI_C1_AVMUTE_MASK, IT6263_HDMI_C1_AVMUTE_MASK);

    if (kStatus_Success == status)
    {
        status = IT6263_I2C_WriteReg(handle, i2cAddr, 0xC6, 0);
    }

    if (kStatus_Success == status)
    {
        status =
            IT6263_I2C_ModifyReg(handle, i2cAddr, 0x04, IT6263_HDMI_04_SOFTVRST_MASK, IT6263_HDMI_04_SOFTVRST_MASK);
    }

    if (kStatus_Success == status)
    {
        status = IT6263_I2C_WriteReg(handle, i2cAddr, 0x61, IT6263_HDMI_61_DRV_PWD_MASK | IT6263_HDMI_61_DRV_RST_MASK);
    }

    return status;
}
