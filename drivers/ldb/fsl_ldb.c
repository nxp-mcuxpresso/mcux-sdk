/*
 * Copyright 2018-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ldb.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ldb"
#endif

#define LDB_CH_COUNT 2U

#define LDB_DPI_24BIT 5U

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)

#define LDB_PM_CTRL_REG_CH_MODE_MASK(ch)        ((uint32_t)LDB_PM_CTRL_REG_CH0_MODE_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch)  ((uint32_t)LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch) ((uint32_t)LDB_PM_CTRL_REG_CH0_BIT_MAPPING_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di) ((uint32_t)LDB_PM_CTRL_REG_DI0_VS_POLARITY_MASK << (di))

#define LDB_PM_CTRL_REG_CH_MASK(ch)                                              \
    (LDB_PM_CTRL_REG_CH_MODE_MASK(ch) | LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch) | \
     LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch))

#define LDB_PM_CTRL_REG_DI_MASK(di) (LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di))

#else

#define LDB_PM_CTRL_REG_CH_MODE_MASK(ch)        ((uint32_t)LDB_PM_CTRL_REG_CH0_MODE_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch)  ((uint32_t)LDB_PM_CTRL_REG_CH0_DATA_WIDTH_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch) ((uint32_t)LDB_PM_CTRL_REG_CH0_BIT_MAPPING_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_10B_EN_MASK(ch)      ((uint32_t)LDB_PM_CTRL_REG_CH0_10B_EN_MASK << (ch))
#define LDB_PM_CTRL_REG_DI_DATA_WIDTH_MASK(di)  ((uint32_t)LDB_PM_CTRL_REG_DI0_DATA_WIDTH_MASK << ((di)*2U))
#define LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di) ((uint32_t)LDB_PM_CTRL_REG_DI0_VS_POLARITY_MASK << (di))

#define LDB_PM_CTRL_REG_CH_MASK(ch)                                              \
    (LDB_PM_CTRL_REG_CH_MODE_MASK(ch) | LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch) | \
     LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch) | LDB_PM_CTRL_REG_CH_10B_EN_MASK(ch))

#define LDB_PM_CTRL_REG_DI_MASK(di) (LDB_PM_CTRL_REG_DI_DATA_WIDTH_MASK(di) | LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di))

#endif

#define LDB_SS_CTRL_CH_VSYNC_POL_MASK(ch) ((uint32_t)LDB_SS_CTRL_CH0_VSYNC_POL_MASK << ((ch)*2U))
#define LDB_SS_CTRL_CH_HSYNC_POL_MASK(ch) ((uint32_t)LDB_SS_CTRL_CH0_HSYNC_POL_MASK << ((ch)*2U))

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to ldb bases for each instance. */
static LDB_Type *const s_ldbBases[] = LDB_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LDB clocks for each instance. */
static const clock_ip_name_t s_ldbClocks[] = LDB_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the LDB instance from peripheral base address.
 *
 * @param base LDB peripheral base address.
 * @return LDB instance.
 */
static uint32_t LDB_GetInstance(LDB_Type *base);

/*!
 * @brief Get the register value based on pixel map.
 *
 * @param outputBus Pixel map.
 * @param ch Channel.
 * @return Register value.
 */
static uint32_t LDB_GetPixelMapConfig(ldb_output_bus_t outputBus, uint8_t ch);

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t LDB_GetInstance(LDB_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0U; instance < ARRAY_SIZE(s_ldbBases); instance++)
    {
        if (s_ldbBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_ldbBases));

    return instance;
}

static uint32_t LDB_GetPixelMapConfig(ldb_output_bus_t outputBus, uint8_t ch)
{
#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    return outputBus << (ch * 2U);
#else
    uint32_t reg = 0U;

    /* Handle the LDB_PM_CTRL_REG_DI_DATA_WIDTH */
    reg |= (((uint32_t)outputBus & LDB_PM_CTRL_REG_CH0_10B_EN_MASK) << (ch));
    reg |= (((uint32_t)outputBus & ~LDB_PM_CTRL_REG_CH0_10B_EN_MASK) << (ch * 2U));

    return reg;
#endif
}

/*!
 * brief Initializes the LDB module.
 *
 * param base LDB peripheral base address.
 */
void LDB_Init(LDB_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    (void)CLOCK_EnableClock(s_ldbClocks[LDB_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    base->PHY_SS_CTRL = 0U;
    base->PM_CTRL_REG = 0U;

    base->PHY_CTRL = LDB_PHY_CTRL_LVDS_EN(0) /* Disable. */
                     | LDB_PHY_CTRL_RFB(1)   /* Clock edge. 0: Falling edge. 1: Rising edge. */
                     | LDB_PHY_CTRL_CA(4)    /* Output current. */
                     | LDB_PHY_CTRL_CCM(4);  /* voltage control . */

    base->PXL2DPI = LDB_DPI_24BIT;
    base->ULPS    = LDB_ULPS_ULPS_ENABLE_MASK; /* Set to lowpower mode. */
#else
    base->PHY_SS_CTRL = 0U;
    base->PM_CTRL_REG = 0U;

    /*
     * Initialize the PHY.
     *
     * CA:
     * 2   1   0   (mA)
     * 0   0   0   2.52
     * 0   0   1   2.77
     * 0   1   0   3.02
     * 0   1   1   3.27
     * 1   0   0   3.52 <
     * 1   0   1   3.77
     * 1   1   0   4.01
     * 1   1   1   4.26
     *
     * CCM:
     * 2   1   0   (V)
     * 0   0   0   0.95
     * 0   0   1   1.0
     * 0   1   0   1.05
     * 0   1   1   1.10
     * 1   0   0   1.15
     * 1   0   1   1.20 <
     * 1   1   0   1.25
     * 1   1   1   1.30
     */
    base->PHY_CTRL = LDB_PHY_CTRL_PD(0)       /* Power up. */
                     | LDB_PHY_CTRL_RFB(1)    /* Clock edge. 0: Falling edge. 1: Rising edge. */
                     | LDB_PHY_CTRL_NB(0)     /* 0: 7-bit. 1: 10-bit. */
                     | LDB_PHY_CTRL_TST(0x25) /* Test valud, default 0x25. */
                     | LDB_PHY_CTRL_CA(4)     /* Output current. */
                     | LDB_PHY_CTRL_CCM(5);   /* voltage control . */
#endif /* FSL_FEATURE_LDB_COMBO_PHY */
}

/*!
 * brief De-initializes the LDB module.
 *
 * param base LDB peripheral base address.
 */
void LDB_Deinit(LDB_Type *base)
{
#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    base->PHY_CTRL = 0U;
#else
    base->PHY_CTRL |= LDB_PHY_CTRL_PD_MASK;
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    (void)CLOCK_DisableClock(s_ldbClocks[LDB_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Initializes the LDB channel.
 *
 * param base LDB peripheral base address.
 * param channel Channel index.
 * param config Pointer to the configuration.
 * return Return kStatus_Success if success.
 */
status_t LDB_InitChannel(LDB_Type *base, uint8_t channel, const ldb_channel_config_t *config)
{
    assert(channel < LDB_CH_COUNT);

    uint32_t reg;
    uint32_t reg_m;
    uint32_t pixelClock_MHz;

    reg = base->PHY_SS_CTRL & ~(LDB_SS_CTRL_CH_VSYNC_POL_MASK(channel) | LDB_SS_CTRL_CH_HSYNC_POL_MASK(channel));

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputVsyncActiveHigh))
    {
        reg |= LDB_SS_CTRL_CH_VSYNC_POL_MASK(channel);
    }

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputHsyncActiveHigh))
    {
        reg |= LDB_SS_CTRL_CH_HSYNC_POL_MASK(channel);
    }

    base->PHY_SS_CTRL = reg;

    /* CH0 to DI0, CH1 to DI1 */
    reg = base->PM_CTRL_REG & ~(LDB_PM_CTRL_REG_DI_MASK(channel) | LDB_PM_CTRL_REG_CH_MASK(channel));

    reg |= LDB_GetPixelMapConfig(config->outputBus, channel);

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputVsyncActiveHigh))
    {
        reg |= LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(channel);
    }

    if (channel == 0U)
    {
        reg |= (1U << LDB_PM_CTRL_REG_CH0_MODE_SHIFT);
    }
    else
    {
        reg |= (3U << LDB_PM_CTRL_REG_CH1_MODE_SHIFT);
    }

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    reg |= LDB_PM_CTRL_REG_CH_SEL(channel);
#endif

    base->PM_CTRL_REG = reg;

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    reg = (base->PHY_CTRL & ~LDB_PHY_CTRL_RFB_MASK);

    /*
     * DPHY_CO is configured based on pixel clock and NB.
     *
     * if NB = 1:
     *         input pixel clock           REG_M
     *            25M ~ 32M                  2
     *            33M ~ 64M                  1
     *            65M ~ 165M                 0
     *
     * if NB = 0:
     *         input pixel clock           REG_M
     *            25M ~ 45M                  2
     *            46M ~ 92M                  1
     *            93M ~ 165M                 0
     *
     * Current driver only supports NB=0 (7bit).
     */
    pixelClock_MHz = config->pixelClock_Hz / 1000000U;
    if (pixelClock_MHz <= 45U)
    {
        reg_m = 2U;
    }
    else if (pixelClock_MHz <= 92U)
    {
        reg_m = 1U;
    }
    else
    {
        reg_m = 0U;
    }

#else
    /*
     * LDB_PHY_CTRL_M is configured based on pixel clock and NB.
     *
     * if NB = 1:
     *         input pixel clock           REG_M
     *            25M ~ 31M                  2
     *            32M ~ 62M                  1
     *            63M ~ 165M                 0
     *
     * if NB = 0:
     *         input pixel clock           REG_M
     *            25M ~ 43M                  2
     *            44M ~ 89M                  1
     *            90M ~ 165M                 0
     *
     * Current driver only supports NB=0 (7bit).
     */
    pixelClock_MHz = config->pixelClock_Hz / 1000000U;
    if (pixelClock_MHz < 24U)
    {
        return kStatus_InvalidArgument;
    }
    else if (pixelClock_MHz <= 43U)
    {
        reg_m = 2U;
    }
    else if (pixelClock_MHz <= 89U)
    {
        reg_m = 1U;
    }
    else if (pixelClock_MHz <= 165U)
    {
        reg_m = 0U;
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    reg            = (base->PHY_CTRL & ~(LDB_PHY_CTRL_RFB_MASK | LDB_PHY_CTRL_M_MASK)) | LDB_PHY_CTRL_M(reg_m);
#endif

    if (0U != ((uint32_t)kLDB_InputDataLatchOnRisingEdge & config->inputFlag))
    {
        reg |= LDB_PHY_CTRL_RFB_MASK;
    }

    base->PHY_CTRL = reg;

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    base->DPHY_PD_PLL = 0U;
    base->DPHY_PD_TX  = 0U;
    base->DPHY_CO     = reg_m;
    base->ULPS        = 0U;
    base->PHY_CTRL    = reg | LDB_PHY_CTRL_LVDS_EN_MASK;
#else
    base->PHY_CTRL = reg | ((uint32_t)LDB_PHY_CTRL_CH0_EN_MASK << channel);
#endif

    return kStatus_Success;
}

/*!
 * brief De-initializes the LDB channel.
 *
 * param base LDB peripheral base address.
 * param channel Channel index.
 */
void LDB_DeinitChannel(LDB_Type *base, uint8_t channel)
{
    assert(channel < LDB_CH_COUNT);

#if (defined(FSL_FEATURE_LDB_COMBO_PHY) && FSL_FEATURE_LDB_COMBO_PHY)
    base->PHY_CTRL &= ~LDB_PHY_CTRL_LVDS_EN_MASK;
    base->ULPS        = LDB_ULPS_ULPS_ENABLE_MASK;
    base->DPHY_PD_TX  = LDB_DPHY_PD_PLL_PD_MASK;
    base->DPHY_PD_PLL = LDB_DPHY_PD_PLL_PD_MASK;
#else
    base->PM_CTRL_REG &= ~(LDB_PM_CTRL_REG_CH_MODE_MASK(channel));

    /* Power off the PHY */
    base->PHY_CTRL &= ~((uint32_t)LDB_PHY_CTRL_CH0_EN_MASK << channel);
#endif
}
