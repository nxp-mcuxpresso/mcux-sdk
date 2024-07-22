/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_st7796s.h"

#define ST7796S_ERROR_CHECK(x)      \
    do                              \
    {                               \
        status_t ret = (x);         \
        if (ret != kStatus_Success) \
        {                           \
            return ret;             \
        }                           \
    } while (false)

#define ST7796S_CMD_SWRESET (0x01U)
#define ST7796S_CMD_SLPIN   (0x10U)
#define ST7796S_CMD_SLPOUT  (0x11U)
#define ST7796S_CMD_INVOFF  (0x20U)
#define ST7796S_CMD_INVON   (0x21U)
#define ST7796S_CMD_DISPOFF (0x28U)
#define ST7796S_CMD_DISPON  (0x29U)
#define ST7796S_CMD_CASET   (0x2AU)
#define ST7796S_CMD_RASET   (0x2BU)
#define ST7796S_CMD_RAMWR   (0x2CU)
#define ST7796S_CMD_TEOFF   (0x34U)
#define ST7796S_CMD_TEON    (0x35U)
#define ST7796S_CMD_MADCTL  (0x36U)
#define ST7796S_CMD_COLMOD  (0x3AU)
#define ST7796S_CMD_CSCON   (0xF0U)
#define ST7796S_CMD_INVTR   (0xB4U)
#define ST7796S_CMD_FRMCTR1 (0xB1U)
#define ST7796S_CMD_BPC     (0xB5U)
#define ST7796S_CMD_DFC     (0xB6U)
#define ST7796S_CMD_PWR1    (0xC0U)
#define ST7796S_CMD_PWR2    (0xC1U)
#define ST7796S_CMD_PWR3    (0xC2U)
#define ST7796S_CMD_VCMPCTL (0xC5U)
#define ST7796S_CMD_DOCA    (0xE8U)
#define ST7796S_CMD_PGC     (0xE0U)
#define ST7796S_CMD_NGC     (0xE1U)

/*
 * This is the panel-specific initialization parameters for driver section,
 * including analog power/voltage control, gamma correction, scan timing, etc.
 * Data format: | 1 Byte parameter length | 1 Byte command byte | N Bytes command parameter |
 */
static const uint8_t s_st7796s_driver_preset_pars035[] = {
    /* clang-format off */
    0x01, ST7796S_CMD_CSCON,   0xC3,                            // Enable command part 1
    0x01, ST7796S_CMD_CSCON,   0x96,                            // Enable command part 2
    0x01, ST7796S_CMD_INVTR,   0x01,                            // Display inversion
    0x02, ST7796S_CMD_FRMCTR1, 0x80, 0x10,                      // Frame rate control 1
    0x04, ST7796S_CMD_BPC,     0x1F, 0x50, 0x00, 0x20,          // Blanking porch control
    0x03, ST7796S_CMD_DFC,     0x8A, 0x07, 0x3B,                // Display function control
    0x02, ST7796S_CMD_PWR1,    0x80, 0x64,                      // Power control 1
    0x01, ST7796S_CMD_PWR2,    0x13,                            // Power control 2
    0x01, ST7796S_CMD_PWR3,    0xA7,                            // Power control 3
    0x01, ST7796S_CMD_VCMPCTL, 0x09,                            // VCOM control
    0x08, ST7796S_CMD_DOCA,    0x40, 0x8A, 0x00, 0x00, 0x29, 0x19, 0xA5, 0x33, // DOCA
    0x0E, ST7796S_CMD_PGC,     0xF0, 0x06, 0x0B, 0x07, 0x06, 0x05, 0x2E, 0x33, 0x47, 0x3A, 0x17, 0x16, 0x2E, 0x31, // PGC
    0x0E, ST7796S_CMD_NGC,     0xF0, 0x09, 0x0D, 0x09, 0x08, 0x23, 0x2E, 0x33, 0x46, 0x38, 0x13, 0x13, 0x2C, 0x32, // NGC
    0x01, ST7796S_CMD_CSCON,   0x3C, // Disable command part 1
    0x01, ST7796S_CMD_CSCON,   0x69, // Disable command part 2
    /* clang-format on */
};

static status_t ST7796S_WriteCommand(st7796s_handle_t *handle,
                                     uint8_t command,
                                     const uint8_t *params,
                                     uint8_t param_len)
{
#if MCUX_DBI_LEGACY
    ST7796S_ERROR_CHECK(handle->xferOps->writeCommand(handle->xferOpsData, command));

    for (uint8_t i = 0; i < param_len; i++)
    {
        uint16_t param_data = params[i];

        ST7796S_ERROR_CHECK(handle->xferOps->writeData(handle->xferOpsData, &param_data, 2U));
    }

    return kStatus_Success;
#else
    return DBI_IFACE_WriteCmdData(handle->dbiIface, command, params, param_len);
#endif
}

static status_t ST7796S_PresetDriver(st7796s_handle_t *handle, st7796s_driver_preset_t preset)
{
    const uint8_t *preset_ptr;
    uint16_t preset_len;

    if (kST7796S_DriverPresetLCDPARS035 == preset)
    {
        preset_ptr = s_st7796s_driver_preset_pars035;
        preset_len = ARRAY_SIZE(s_st7796s_driver_preset_pars035);
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    uint16_t i = 0;

    while (i < preset_len)
    {
        uint8_t param_len = preset_ptr[i];

        ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, preset_ptr[i + 1u], &preset_ptr[i + 2u], param_len));
        i += ((uint16_t)param_len + 2u); /* Next = parameter length + command byte + length itself */
    }

    return kStatus_Success;
}

static status_t ST7796S_SoftwareReset(st7796s_handle_t *handle)
{
    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_SWRESET, NULL, 0));
    SDK_DelayAtLeastUs(5 * 1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    return kStatus_Success;
}

static status_t ST7796S_SleepMode(st7796s_handle_t *handle, bool sleep)
{
    uint8_t slp_cmd;
    if (sleep)
    {
        slp_cmd = ST7796S_CMD_SLPIN;
    }
    else
    {
        slp_cmd = ST7796S_CMD_SLPOUT;
    }

    return ST7796S_WriteCommand(handle, slp_cmd, NULL, 0);
}

#if MCUX_DBI_LEGACY
status_t ST7796S_Init(st7796s_handle_t *handle,
                      const st7796s_config_t *config,
                      const dbi_xfer_ops_t *xferOps,
                      void *xferOpsData)
#else
status_t ST7796S_Init(st7796s_handle_t *handle, const st7796s_config_t *config, dbi_iface_t *dbiIface)
#endif
{
#if MCUX_DBI_LEGACY
    handle->xferOps     = xferOps;
    handle->xferOpsData = xferOpsData;
#else
    handle->dbiIface = dbiIface;
#endif

    ST7796S_ERROR_CHECK(ST7796S_SoftwareReset(handle));
    ST7796S_ERROR_CHECK(ST7796S_PresetDriver(handle, config->driverPreset));
    ST7796S_ERROR_CHECK(ST7796S_SleepMode(handle, false));
    ST7796S_ERROR_CHECK(ST7796S_Config(handle, config));

    return kStatus_Success;
}

status_t ST7796S_InvertDisplay(st7796s_handle_t *handle, bool invert)
{
    uint8_t inv_cmd;
    if (invert)
    {
        inv_cmd = ST7796S_CMD_INVON;
    }
    else
    {
        inv_cmd = ST7796S_CMD_INVOFF;
    }

    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, inv_cmd, NULL, 0U));

    return kStatus_Success;
}

status_t ST7796S_EnableDisplay(st7796s_handle_t *handle, bool enable)
{
    uint8_t disp_cmd;
    if (enable)
    {
        disp_cmd = ST7796S_CMD_DISPON;
    }
    else
    {
        disp_cmd = ST7796S_CMD_DISPOFF;
    }

    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, disp_cmd, NULL, 0U));

    return kStatus_Success;
}

status_t ST7796S_SetPixelFormat(st7796s_handle_t *handle, st7796s_pixel_format_t pixelFormat)
{
    uint8_t pixel_fmt = (uint8_t)pixelFormat;
    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_COLMOD, &pixel_fmt, 0x01U));

    return kStatus_Success;
}

status_t ST7796S_SetTEConfig(st7796s_handle_t *handle, st7796s_te_config_t teConfig)
{
    if (teConfig == kST7796S_TEDisabled)
    {
        ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_TEOFF, NULL, 0U));
    }
    else
    {
        uint8_t te_cfg = 0x00U;
        if (teConfig == kST7796S_TEHVSync)
        {
            te_cfg |= 0x01U; /* Set TEM bit */
        }

        ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_TEON, &te_cfg, 1U));
    }

    return kStatus_Success;
}

status_t ST7796S_SelectArea(st7796s_handle_t *handle, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    uint8_t tx_buf[4];

    tx_buf[0] = (uint8_t)(startX >> 0x08U) & 0xFFU;
    tx_buf[1] = (uint8_t)startX & 0xFFU;
    tx_buf[2] = (uint8_t)(endX >> 0x08U) & 0xFFU;
    tx_buf[3] = (uint8_t)endX & 0xFFU;

    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_CASET, tx_buf, 4U));

    tx_buf[0] = (uint8_t)(startY >> 0x08U) & 0xFFU;
    tx_buf[1] = (uint8_t)startY & 0xFFU;
    tx_buf[2] = (uint8_t)(endY >> 0x08U) & 0xFFU;
    tx_buf[3] = (uint8_t)endY & 0xFFU;

    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_RASET, tx_buf, 4U));

    return kStatus_Success;
}

status_t ST7796S_Config(st7796s_handle_t *handle, const st7796s_config_t *config)
{
    ST7796S_ERROR_CHECK(ST7796S_InvertDisplay(handle, config->invertDisplay));
    ST7796S_ERROR_CHECK(ST7796S_SetPixelFormat(handle, config->pixelFormat));
    ST7796S_ERROR_CHECK(ST7796S_SetTEConfig(handle, config->teConfig));

    uint8_t tx_buf[1];

    tx_buf[0] = (uint8_t)config->orientationMode;
    if (!config->bgrFilter)
    {
        tx_buf[0] &= (uint8_t)(~0x08U);
    }

    if (config->flipDisplay)
    {
        if ((config->orientationMode == kST7796S_Orientation90) || (config->orientationMode == kST7796S_Orientation270))
        {
            tx_buf[0] ^= 0x80U;
        }
        else
        {
            tx_buf[0] ^= 0x40U;
        }
    }

    ST7796S_ERROR_CHECK(ST7796S_WriteCommand(handle, ST7796S_CMD_MADCTL, tx_buf, 1U));

    handle->orientationMode = config->orientationMode;

    return kStatus_Success;
}

status_t ST7796S_WritePixels(st7796s_handle_t *handle, uint16_t *pixels, uint32_t len)
{
#if MCUX_DBI_LEGACY
    ST7796S_ERROR_CHECK(handle->xferOps->writeMemory(handle->xferOpsData, ST7796S_CMD_RAMWR, pixels, len * 2u));
#else
    ST7796S_ERROR_CHECK(DBI_IFACE_WriteMemory(handle->dbiIface, (const uint8_t *)pixels, len * 2u));
#endif

    return kStatus_Success;
}

#if MCUX_DBI_LEGACY
void ST7796S_SetMemoryDoneCallback(st7796s_handle_t *handle, dbi_mem_done_callback_t callback, void *userData)
{
    handle->xferOps->setMemoryDoneCallback(handle->xferOpsData, callback, userData);
}
#endif
