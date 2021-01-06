/*
 * Copyright 2017, 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CI_PI_H_
#define _FSL_CI_PI_H_

#include "fsl_common.h"

/*!
 * @addtogroup ci_pi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief CI_PI driver version. */
#define FSL_CI_PI_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

/*!
 * @brief CI_PI status flags.
 */
enum _ci_pi_flags
{
    kCI_PI_ChangeOfFieldFlag = CI_PI_CSR_CSI_STATUS_FIELD_TOGGLE_MASK, /*!< Change of field. */
    kCI_PI_EccErrorFlag      = CI_PI_CSR_CSI_STATUS_ECC_ERROR_MASK,    /*!< ECC error detected. */
};

/*!
 * @brief Input data format.
 */
typedef enum _ci_pi_input_format
{
    kCI_PI_InputUYVY8888_8BitBus      = 0x0, /*!< UYVY, every component is 8bit, data bus is 8bit */
    kCI_PI_InputUYVY10101010_10BitBus = 0x1, /*!< UYVY, every component is 10bit, data bus is 10bit. */
    kCI_PI_InputRGB888_8BitBus        = 0x2, /*!< RGB, every component is 8bit, data bus is 8bit. */
    kCI_PI_InputBGR888_8BitBus        = 0x3, /*!< BGR, every component is 8bit, data bus is 8bit. */
    kCI_PI_InputRGB888_24BitBus       = 0x4, /*!< RGB, every component is 8bit, data bus is 24 bit. */
    kCI_PI_InputYVYU8888_8BitBus      = 0x5, /*!< YVYU, every component is 8bit, data bus is 8bit */
    kCI_PI_InputYUV888_8BitBus        = 0x6, /*!< YUV, every component is 8bit, data bus is 8bit. */
    kCI_PI_InputYVYU8888_16BitBus     = 0x7, /*!< YVYU, every component is 8bit, data bus 16bit. */
    kCI_PI_InputYUV888_24BitBus       = 0x8, /*!< YUV, every component is 8bit, data bus is 24bit. */
    kCI_PI_InputBayer8_8BitBus        = 0x9, /*!< Bayer 8bit */
    kCI_PI_InputBayer10_10BitBus      = 0xa, /*!< Bayer 10bit */
    kCI_PI_InputBayer12_12BitBus      = 0xb, /*!< Bayer 12bit */
    kCI_PI_InputBayer16_16BitBus      = 0xc, /*!< Bayer 16bit */
} ci_pi_input_format_t;

/*! @brief CI_PI signal polarity. */
enum _ci_pi_polarity_flags
{
    kCI_PI_HsyncActiveLow        = 0U,                                    /*!< HSYNC is active low. */
    kCI_PI_HsyncActiveHigh       = CI_PI_CSR_CSI_CTRL_REG_HSYNC_POL_MASK, /*!< HSYNC is active high. */
    kCI_PI_DataLatchOnRisingEdge = 0, /*!< Pixel data latched at rising edge of pixel clock. */
    kCI_PI_DataLatchOnFallingEdge =
        CI_PI_CSR_CSI_CTRL_REG_PIXEL_CLK_POL_MASK, /*!< Pixel data latched at falling edge of pixel clock. */
    kCI_PI_DataEnableActiveHigh = 0U,              /*!< Data enable signal (DE) is active high. */
    kCI_PI_DataEnableActiveLow  = CI_PI_CSR_CSI_CTRL_REG_DE_POL_MASK,    /*!< Data enable signal (DE) is active low. */
    kCI_PI_VsyncActiveHigh      = CI_PI_CSR_CSI_CTRL_REG_VSYNC_POL_MASK, /*!< VSYNC is active high. */
    kCI_PI_VsyncActiveLow       = 0,                                     /*!< VSYNC is active low. */
};

/*!
 * @brief CI_PI work mode.
 *
 * The CCIR656 interlace mode is not supported currently.
 */
typedef enum _ci_pi_work_mode
{
    kCI_PI_GatedClockMode = CI_PI_CSR_CSI_CTRL_REG_GCLK_MODE_EN_MASK, /*!< HSYNC, VSYNC, and PIXCLK signals are used. */
    kCI_PI_GatedClockDataEnableMode =
        CI_PI_CSR_CSI_CTRL_REG_GCLK_MODE_EN_MASK |
        CI_PI_CSR_CSI_CTRL_REG_VALID_SEL_MASK,                           /*!< DE, VSYNC, and PIXCLK signals are used. */
    kCI_PI_NonGatedClockMode      = 0U,                                  /*!< VSYNC, and PIXCLK signals are used. */
    kCI_PI_CCIR656ProgressiveMode = CI_PI_CSR_CSI_CTRL_REG_CCIR_EN_MASK, /*!< CCIR656 progressive mode. */
} ci_pi_work_mode_t;

typedef struct _ci_pi_config
{
    uint16_t width;
    uint16_t vsyncWidth;
    uint16_t hsyncWidth;
    uint32_t polarityFlags; /*!< Timing signal polarity flags, OR'ed value of @ref _ci_pi_polarity_flags. */
    uint8_t pixelLinkAddr;
    ci_pi_input_format_t inputFormat;

    ci_pi_work_mode_t workMode; /*!< Work mode. */
    bool useExtVsync;           /*!< In CCIR656 progressive mode, set true to use external VSYNC signal, set false
                                  to use internal VSYNC signal decoded from SOF. */
    bool swapUV;                /*!< Swap UV. */
} ci_pi_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cIFusIFus)
extern "C" {
#endif

/*!
 * @brief Enables and configures the CI_PI peripheral module.
 *
 * @param base CI_PI peripheral address.
 * @param config CI_PI module configuration structure.
 */
void CI_PI_Init(CI_PI_CSR_Type *base, const ci_pi_config_t *config);

/*!
 * @brief Disables the CI_PI peripheral module.
 *
 * @param base CI_PI peripheral address.
 */
void CI_PI_Deinit(CI_PI_CSR_Type *base);

/*!
 * @brief Get the default configuration to initialize CI_PI.
 *
 * The default configuration value is:
 *
 * @code
    config->width = 0;
    config->vsyncWidth = 3U;
    config->hsyncWidth = 2U;
    config->polarityFlags = 0;
    config->pixelLinkAddr = 0;
    config->inputFormat = kCI_PI_InputUYVY8888_8BitBus;
    config->workMode = kCI_PI_NonGatedClockMode;
    config->useExtVsync = false;
    config->swapUV = false;
    @endcode
 *
 * @param config Pointer to the configuration.
 */
void CI_PI_GetDefaultConfig(ci_pi_config_t *config);

/*!
 * @brief Resets the CI_PI peripheral module.
 *
 * @param base CI_PI peripheral address.
 */
static inline void CI_PI_Reset(CI_PI_CSR_Type *base)
{
    uint32_t i = 0;

    base->CSI_CTRL_REG.SET = CI_PI_CSR_CSI_CTRL_REG_SOFTRST_MASK;

    i = 0x10;
    while (0U != (i--))
    {
        __NOP();
    }

    base->CSI_CTRL_REG.CLR = CI_PI_CSR_CSI_CTRL_REG_SOFTRST_MASK;
}

/*!
 * @brief Starts the CI_PI peripheral module to output captured frame.
 *
 * @param base CI_PI peripheral address.
 */
void CI_PI_Start(CI_PI_CSR_Type *base);

/*!
 * @brief Stops the CI_PI peripheral module.
 *
 * @param base CI_PI peripheral address.
 */
void CI_PI_Stop(CI_PI_CSR_Type *base);

/*!
 * @brief Gets the CI_PI peripheral module status.
 *
 * @param base CI_PI peripheral address.
 * @return Status returned as the OR'ed value of @ref _ci_pi_flags.
 */
static inline uint32_t CI_PI_GetStatus(CI_PI_CSR_Type *base)
{
    return base->CSI_STATUS.RW;
}

#if defined(__cIFusIFus)
}
#endif
/*!
 * @}
 */
#endif /* _FSL_CI_PI_H_ */
