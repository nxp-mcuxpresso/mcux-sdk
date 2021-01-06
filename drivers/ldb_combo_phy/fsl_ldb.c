/*
 * Copyright 2019-2020 NXP
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
#define FSL_COMPONENT_ID "platform.drivers.ldb_combo_phy"
#endif

#define LDB_CH_COUNT 2U

#define LDB_DPI_24BIT 5U

#define LDB_PM_CTRL_REG_CH_MODE_MASK(ch) ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_MODE_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch) \
    ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_DATA_WIDTH_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch) \
    ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_BIT_MAPPING_MASK << ((ch)*2U))
#define LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di) ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_DI0_VS_POLARITY_MASK << (di))

#define LDB_PM_CTRL_REG_CH_MASK(ch)                                              \
    (LDB_PM_CTRL_REG_CH_MODE_MASK(ch) | LDB_PM_CTRL_REG_CH_DATA_WIDTH_MASK(ch) | \
     LDB_PM_CTRL_REG_CH_BIT_MAPPING_MASK(ch))

#define LDB_PM_CTRL_REG_DI_MASK(di) (LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(di))

#define LDB_SS_CTRL_CH_VSYNC_POL_MASK(ch) ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_SS_CRTL_CH0_VSYNC_POL_MASK << ((ch)*2U))
#define LDB_SS_CTRL_CH_HSYNC_POL_MASK(ch) ((uint32_t)MIPI_DSI_LVDS_COMBO_CSR_SS_CRTL_CH0_HSYNC_POL_MASK << ((ch)*2U))

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to LDB PHY control blocks. */
static MIPI_DSI_HOST_Type *const s_ldbPhyBases[] = MIPI_DSI_HOST_BASE_PTRS;
/*! @brief Pointers to ldb bases for each instance. */
static LDB_Type *const s_ldbBases[] = MIPI_DSI_LVDS_COMBO_CSR_BASE_PTRS;

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

/*!
 * @brief Get the register value based on pixel map.
 *
 * @param outputBus Pixel map.
 * @param ch Channel.
 * @return Register value.
 */
static MIPI_DSI_HOST_Type *LDB_GetPhyControlBlock(LDB_Type *base);

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
    return (uint32_t)outputBus << (ch * 2U);
}

static MIPI_DSI_HOST_Type *LDB_GetPhyControlBlock(LDB_Type *base)
{
    return s_ldbPhyBases[LDB_GetInstance(base)];
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

    base->SS_CRTL = 0U;
    base->PM_CTRL = 0U;

    base->LVDS_PHY_CTRL =
        MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_LVDS_EN(0) /* Disable. */
        | MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_RFB(1)   /* Clock edge. 0: Falling edge. 1: Rising edge. */
        | MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_CA(4)    /* Output current. */
        | MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_CCM(4);  /* voltage control . */

    base->PXL2DPI_CTRL = LDB_DPI_24BIT;
    base->ULPS_CTRL    = MIPI_DSI_LVDS_COMBO_CSR_ULPS_CTRL_TX_ULPS_MASK; /* Set to lowpower mode. */
}

/*!
 * brief De-initializes the LDB module.
 *
 * param base LDB peripheral base address.
 */
void LDB_Deinit(LDB_Type *base)
{
    base->LVDS_PHY_CTRL = 0U;

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

    MIPI_DSI_HOST_Type *phy = LDB_GetPhyControlBlock(base);

    reg = base->SS_CRTL & ~(LDB_SS_CTRL_CH_VSYNC_POL_MASK(channel) | LDB_SS_CTRL_CH_HSYNC_POL_MASK(channel));

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputVsyncActiveHigh))
    {
        reg |= LDB_SS_CTRL_CH_VSYNC_POL_MASK(channel);
    }

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputHsyncActiveHigh))
    {
        reg |= LDB_SS_CTRL_CH_HSYNC_POL_MASK(channel);
    }

    base->SS_CRTL = reg;

    /* CH0 to DI0, CH1 to DI1 */
    reg = base->PM_CTRL & ~(LDB_PM_CTRL_REG_DI_MASK(channel) | LDB_PM_CTRL_REG_CH_MASK(channel));

    reg |= LDB_GetPixelMapConfig(config->outputBus, channel);

    if (0U != (config->inputFlag & (uint32_t)kLDB_InputVsyncActiveHigh))
    {
        reg |= LDB_PM_CTRL_REG_DI_VS_POLARITY_MASK(channel);
    }

    if (channel == 0U)
    {
        reg |= (1UL << MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH0_MODE_SHIFT);
    }
    else
    {
        reg |= (3UL << MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH1_MODE_SHIFT);
    }

    reg |= MIPI_DSI_LVDS_COMBO_CSR_PM_CTRL_CH_SEL(channel);

    base->PM_CTRL = reg;

    reg = (base->LVDS_PHY_CTRL & ~MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_RFB_MASK);

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

    if (0U != ((uint32_t)kLDB_InputDataLatchOnRisingEdge & config->inputFlag))
    {
        reg |= MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_RFB_MASK;
    }

    base->LVDS_PHY_CTRL = reg;
    phy->DPHY_PD_PLL    = 0U;
    phy->DPHY_PD_TX     = 0U;
    phy->DPHY_CO        = reg_m;
    base->ULPS_CTRL     = 0U;
    base->LVDS_PHY_CTRL = reg | MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_LVDS_EN_MASK;

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

    MIPI_DSI_HOST_Type *phy = LDB_GetPhyControlBlock(base);

    base->LVDS_PHY_CTRL &= ~MIPI_DSI_LVDS_COMBO_CSR_LVDS_PHY_CTRL_LVDS_EN_MASK;
    base->ULPS_CTRL  = MIPI_DSI_LVDS_COMBO_CSR_ULPS_CTRL_TX_ULPS_MASK;
    phy->DPHY_PD_TX  = MIPI_DSI_HOST_DPHY_PD_TX_dphy_pd_tx_MASK;
    phy->DPHY_PD_PLL = MIPI_DSI_HOST_DPHY_PD_PLL_dphy_pd_pll_MASK;
}
