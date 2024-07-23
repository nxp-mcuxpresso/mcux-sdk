/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mipi_dsi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mipi_dsi_imx"
#endif

/* The timeout cycles to wait for DSI status. */
#ifndef FSL_MIPI_DSI_TIMEOUT
#define FSL_MIPI_DSI_TIMEOUT 0x1000U
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to MIPI DSI bases for each instance. */
static MIPI_DSI_Type *const s_dsiBases[] = MIPI_DSI_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to MIPI DSI clocks for each instance. */

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

static uint32_t HsLpTimingTable[63][5] = {
    {80, 21, 17, 15, 10},      {90, 23, 17, 16, 10},      {100, 22, 17, 16, 10},     {110, 25, 18, 17, 11},
    {120, 26, 20, 18, 11},     {130, 27, 19, 19, 11},     {140, 27, 19, 19, 11},     {150, 28, 20, 20, 12},
    {160, 30, 21, 22, 13},     {170, 30, 21, 23, 13},     {180, 31, 21, 23, 13},     {190, 32, 22, 24, 13},
    {205, 35, 22, 25, 13},     {220, 37, 26, 27, 15},     {235, 38, 28, 27, 16},     {250, 41, 29, 30, 17},
    {275, 43, 29, 32, 18},     {300, 45, 32, 35, 19},     {325, 48, 33, 36, 18},     {350, 51, 35, 40, 20},
    {400, 59, 37, 44, 21},     {450, 65, 40, 49, 23},     {500, 71, 41, 54, 24},     {550, 77, 44, 57, 26},
    {600, 82, 46, 64, 27},     {650, 87, 48, 67, 28},     {700, 94, 52, 71, 29},     {750, 99, 52, 75, 31},
    {800, 105, 55, 82, 32},    {850, 110, 58, 85, 32},    {900, 115, 58, 88, 35},    {950, 120, 62, 93, 36},
    {1000, 128, 63, 99, 38},   {1050, 132, 65, 102, 38},  {1100, 138, 67, 106, 39},  {1150, 146, 69, 112, 42},
    {1200, 151, 71, 117, 43},  {1250, 153, 74, 120, 45},  {1300, 160, 73, 124, 46},  {1350, 165, 76, 130, 47},
    {1400, 172, 78, 134, 49},  {1450, 177, 80, 138, 49},  {1500, 183, 81, 143, 52},  {1550, 191, 84, 147, 52},
    {1600, 194, 85, 152, 52},  {1650, 201, 86, 155, 53},  {1700, 208, 88, 161, 53},  {1750, 212, 89, 165, 53},
    {1800, 220, 90, 171, 54},  {1850, 223, 92, 175, 54},  {1900, 231, 91, 180, 55},  {1950, 236, 95, 185, 56},
    {2000, 243, 97, 190, 56},  {2050, 248, 99, 194, 58},  {2100, 252, 100, 199, 59}, {2150, 259, 102, 204, 61},
    {2200, 266, 105, 210, 62}, {2250, 269, 109, 213, 63}, {2300, 272, 109, 217, 65}, {2350, 281, 112, 225, 66},
    {2400, 283, 115, 226, 66}, {2450, 282, 115, 226, 67}, {2500, 281, 118, 227, 67}};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Clear the RX FIFO.
 *
 * @param base MIPI DSI host peripheral base address.
 */
static void DSI_ApbClearRxFifo(MIPI_DSI_Type *base);

/*!
 * @brief Gets how may bits in one pixel.
 *
 * @param coding The color coding for the pixel format.
 * @return Bit count in one pixel.
 */
static uint8_t DSI_GetBitsPerPixel(dsi_dpi_color_coding_t coding);

/*!
 * @brief Checks and updates the horizontal timing parameter in pixel cycle.
 *
 * @param cycle Horizontal timing parameter cycles in pixel.
 * @param bpp Bits in one pixel.
 * @param div divider value.
 * @return the updated cycle.
 */
static uint16_t DSI_CheckAndUpdatePixCycle(uint16_t cycle, uint8_t bpp, uint8_t div);

/*!
 * @brief Updates the Horizontal timing parameter cycles.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the DPI interface configuration.
 * @param laneNum How may lanes in use.
 */
static void DSI_ConfigureHorizontalParams(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum);

/*!
 * @brief Configures the video mode configuration for DPI interface.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the DPI interface configuration.
 * @param laneNum How may lanes in use.
 */
static void DSI_SetVideoModeConfig(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum);

/*!
 * @brief Prepares and starts the DSI APB transfer.
 *
 * This function fills TX data to DSI TX FIFO, sets the packet control
 * register then start the trasnfer by writting the header.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param xfer The transfer definition.
 * @retval kStatus_Success It is ready to start transfer.
 * @retval kStatus_DSI_NotSupported The transfer format is not supported.
 */
static status_t DSI_PrepareApbTransfer(MIPI_DSI_Type *base, dsi_transfer_t *xfer);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void DSI_ApbClearRxFifo(MIPI_DSI_Type *base)
{
    while ((base->CMD_PKT_STATUS & MIPI_DSI_CMD_PKT_STATUS_gen_pld_r_empty_MASK) == 0U)
    {
        (void)base->GEN_PLD_DATA;
    }
}

static uint8_t DSI_GetBitsPerPixel(dsi_dpi_color_coding_t coding)
{
    uint8_t bpp = 0U;
    switch (coding)
    {
        case kDSI_DpiYCbCr12Bit:
            bpp = 12U;
        case kDSI_DpiRGB16Bit:
        case kDSI_DpiRGB16BitLoose0:
        case kDSI_DpiRGB16BitLoose1:
        case kDSI_DpiYCbCr16Bit:
            bpp = 16U;
            break;
        case kDSI_DpiRGB18Bit:
        case kDSI_DpiRGB18BitLoose:
            bpp = 18U;
            break;
        case kDSI_DpiYCbCr20Bit:
            bpp = 20U;
            break;
        case kDSI_DpiRGB24Bit:
        case kDSI_DpiYCbCr24Bit:
        case kDSI_DpiDcs24Bit:
            bpp = 24U;
            break;
        case kDSI_DpiRGB30Bit:
            bpp = 30U;
            break;
        case kDSI_DpiRGB36Bit:
            bpp = 36U;
            break;
        default:
            assert(false);
            break;
    }

    return bpp;
}

static uint16_t DSI_CheckAndUpdatePixCycle(uint16_t cycle, uint8_t bpp, uint8_t div)
{
    uint16_t updatedCycle = cycle;
    for (uint8_t i = 0U; i < div; i++)
    {
        /* Make sure the byte count of the HSW/HBP/width can be evenly divided by the lane number,
           that is no paddings for these parameters. */
        if ((((cycle + (uint16_t)i) * (uint16_t)bpp) % div) == 0U)
        {
            updatedCycle = cycle + (uint16_t)i;
            break;
        }
    }
    return updatedCycle;
}

static void DSI_ConfigureHorizontalParams(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum)
{
    uint8_t bpp = DSI_GetBitsPerPixel(config->colorCoding);
    uint8_t div = 8U * laneNum;

    /* Check, update and configure the horizontal timing parameters. */
    base->VID_HSA_TIME   = (uint32_t)DSI_CheckAndUpdatePixCycle(config->hsw, bpp, div);
    base->VID_HBP_TIME   = (uint32_t)DSI_CheckAndUpdatePixCycle(config->hbp, bpp, div);
    base->VID_HLINE_TIME = (uint32_t)DSI_CheckAndUpdatePixCycle(
        (config->pixelPayloadSize + config->hsw + config->hbp + config->hfp), bpp, div);
}

static void DSI_SetVideoModeConfig(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum)
{
    assert(config);

    /* Configure the video mode, low-power command enable and frame ack configuration. */
    uint32_t regVal = (uint32_t)config->videoMode | MIPI_DSI_VID_MODE_CFG_frame_bta_ack_en((uint32_t)config->enableAck);

    /* Configure the pattern generator. */
    if (config->pattern == kDSI_PatternVertical)
    {
        regVal |= MIPI_DSI_VID_MODE_CFG_vpg_en_MASK;
    }
    else if (config->pattern == kDSI_PatternHorizontal)
    {
        regVal |= MIPI_DSI_VID_MODE_CFG_vpg_en_MASK | MIPI_DSI_VID_MODE_CFG_vpg_orientation_MASK;
    }
    else
    {
        /* Nothing. */
    }

    /* Configure the switch to low-power inside all phases. */
    if (config->enablelpSwitch)
    {
        regVal |= MIPI_DSI_VID_MODE_CFG_lp_vsa_en_MASK | MIPI_DSI_VID_MODE_CFG_lp_vbp_en_MASK |
                  MIPI_DSI_VID_MODE_CFG_lp_vfp_en_MASK | MIPI_DSI_VID_MODE_CFG_lp_vact_en_MASK |
                  MIPI_DSI_VID_MODE_CFG_lp_hbp_en_MASK | MIPI_DSI_VID_MODE_CFG_lp_hfp_en_MASK;
    }

    base->VID_MODE_CFG = regVal;

    /* Configure pixel payload size. */
    base->VID_PKT_SIZE = (uint32_t)config->pixelPayloadSize;

    /* Configure the vertical parameters. */
    base->VID_VSA_LINES     = config->vsw;
    base->VID_VBP_LINES     = config->vbp;
    base->VID_VFP_LINES     = config->vfp;
    base->VID_VACTIVE_LINES = config->panelHeight;

    /* Configure the horizontal parameters. */
    DSI_ConfigureHorizontalParams(base, config, laneNum);
}

/*!
 * brief Gets the MIPI DSI host controller instance from peripheral base address.
 *
 * param base MIPI DSI peripheral base address.
 * return MIPI DSI instance.
 */
uint32_t DSI_GetInstance(MIPI_DSI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_dsiBases); instance++)
    {
        if (s_dsiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_dsiBases));

    return instance;
}

/*!
 * brief Initializes the MIPI DSI host with the user configuration.
 *
 * This function initializes the MIPI DSI host with the configuration, it should
 * be called before other MIPI DSI driver functions.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the user configuration structure.
 */
void DSI_Init(MIPI_DSI_Type *base, dsi_config_t *config)
{
    assert(config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset the module before configuration. */
    base->PWR_UP = 0U;

    /* Configure mode. */
    base->MODE_CFG = (uint32_t)config->mode;

    /* Configure package flags, whether to enable BTA, CRC, EoTp tx/rx, etc. */
    base->PCKHDL_CFG = (uint32_t)config->packageFlags;

    /* Configure lp clock control */
    base->LPCLK_CTRL = MIPI_DSI_LPCLK_CTRL_phy_txrequestclkhs_MASK |
                       MIPI_DSI_LPCLK_CTRL_auto_clklane_ctrl((uint32_t)config->enableNoncontinuousClk);

    /* Configure the peripheral resonse. */
    base->HS_RD_TO_CNT = (uint32_t)config->HsRxDeviceReady_ByteClk;
    base->LP_RD_TO_CNT = (uint32_t)config->lpRxDeviceReady_ByteClk;
    base->HS_WR_TO_CNT = (uint32_t)config->HsTxDeviceReady_ByteClk;
    base->LP_WR_TO_CNT = (uint32_t)config->lpTxDeviceReady_ByteClk;

    DSI_ApbClearRxFifo(base);

    /* Disable all interrupts by default, user could enable the desired interrupts later.
     */
    base->INT_MSK0 = 0U;
    base->INT_MSK1 = 0U;
}

/*!
 * brief Deinitializes an MIPI DSI host.
 *
 * This function should be called after all bother MIPI DSI driver functions.
 *
 * param base MIPI DSI host peripheral base address.
 */
void DSI_Deinit(MIPI_DSI_Type *base)
{
    base->PWR_UP   = 0U;
    base->PHY_RSTZ = 0U;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration to initialize the MIPI DSI host.
 *
 * The default value is:
 * code
 * config->mode = kDSI_CommandMode;
 * config->packageFlags = kDSI_DpiEnableAll;
 * config->enableNoncontinuousClk = true;
 * config->HsRxDeviceReady_ByteClk = 0U;
 * config->lpRxDeviceReady_ByteClk = 0U;
 * config->HsTxDeviceReady_ByteClk = 0U;
 * config->lpTxDeviceReady_ByteClk = 0U;
 * endcode
 *
 * param config Pointer to a user-defined configuration structure.
 */
void DSI_GetDefaultConfig(dsi_config_t *config)
{
    assert(config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->mode                   = kDSI_CommandMode;
    config->packageFlags           = kDSI_DpiEnableAll;
    config->enableNoncontinuousClk = true;
    /* The following device ready time shall be set according to the device specific requirements. */
    config->HsRxDeviceReady_ByteClk = 0U;
    config->lpRxDeviceReady_ByteClk = 0U;
    config->HsTxDeviceReady_ByteClk = 0U;
    config->lpTxDeviceReady_ByteClk = 0U;
}

/*!
 * brief Configure the DPI interface.
 *
 * This function sets the DPI interface configuration, it should be used in
 * video mode.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the DPI interface configuration.
 *
 */
void DSI_SetDpiConfig(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum)
{
    assert(config);

    base->DPI_VCID    = (uint32_t)config->virtualChannel;
    base->DPI_CFG_POL = (uint32_t)config->polarityFlags;

    if (kDSI_DpiRGB18BitLoose == config->colorCoding)
    {
        base->DPI_COLOR_CODING = (uint32_t)config->colorCoding | MIPI_DSI_DPI_COLOR_CODING_loosely18_en_MASK;
    }
    else
    {
        base->DPI_COLOR_CODING = (uint32_t)config->colorCoding;
    }

    /* Configure the DPI low power command timing. */
    /* TODO largest packet sizes during hfp or during vsa/vpb/vfp should be computed according to byte lane, lane number
     */
    base->DPI_LP_CMD_TIM =
        MIPI_DSI_DPI_LP_CMD_TIM_outvact_lpcmd_time(16U) | MIPI_DSI_DPI_LP_CMD_TIM_invact_lpcmd_time(4U);

    DSI_SetVideoModeConfig(base, config, laneNum);
}

/*!
 * brief Configures the command mode configuration.
 *
 * This function configures the timeout values for DSI command mode.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the command mode configuration structure.
 * param phyByteClkFreq_Hz Bit clock frequency in each lane.
 */
void DSI_SetCommandModeConfig(MIPI_DSI_Type *base, const dsi_command_config_t *config, uint32_t phyByteClkFreq_Hz)
{
    /* Calculate the divider for BTA timeout. */
    uint16_t btaToDiv = (config->btaTo_Ns / 1000U) * (phyByteClkFreq_Hz / 1000000U);
    /* Calculate the divider for hs tx timeout. */
    uint16_t hsToDiv = (config->hsTxTo_Ns / 1000U) * (phyByteClkFreq_Hz / 1000000U);
    /* Calculate the divider for lp rx timeout. */
    uint16_t lpToDiv = (config->lpRxTo_Ns / 1000U) * (phyByteClkFreq_Hz / 1000000U);
    /* Calculate escape clock division. */
    uint8_t escClkDiv = (phyByteClkFreq_Hz >> 3U) / config->escClkFreq_Hz + 1U;

    base->BTA_TO_CNT = (uint32_t)btaToDiv;
    base->TO_CNT_CFG =
        MIPI_DSI_TO_CNT_CFG_lprx_to_cnt((uint32_t)lpToDiv) | MIPI_DSI_TO_CNT_CFG_hstx_to_cnt((uint32_t)hsToDiv);
    base->CLKMGR_CFG =
        MIPI_DSI_CLKMGR_CFG_to_clk_division(0U) | MIPI_DSI_CLKMGR_CFG_tx_esc_clk_division((uint32_t)escClkDiv);
}

/*!
 * brief Gets the default D-PHY configuration.
 *
 * Gets the default D-PHY configuration, the timing parameters are set according
 * to D-PHY specification. User can use the configuration directly, or change
 * the parameters according device specific requirements.
 *
 * param config Pointer to the D-PHY configuration.
 * param phyByteClkFreq_Hz Byte clock frequency.
 * param laneNum How may lanes in use.
 */
void DSI_GetDefaultDphyConfig(dsi_dphy_config_t *config, uint32_t phyByteClkFreq_Hz, uint8_t laneNum)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));
    uint8_t i;

    /* 4 lanes */
    config->numLanes = laneNum;
    /* Calculate lane bit clock frequency. */
    uint32_t laneBitClkFreq_Hz = phyByteClkFreq_Hz * 8U / laneNum;
    /* Max read length is 10000 bytes. This should be changed according to device specific max read leagth. */
    config->maxRead_ByteClk = 10000U;
    /* Min time PHY needs to stay in StopState before requesting an hs transmission. */
    config->tStopState_ByteClk = 0x20U;

    /* Get the clock&data lane state change timing parameters according to the lane bit clock frequency. */
    for (i = 0U; i < ARRAY_SIZE(HsLpTimingTable); i++)
    {
        if (laneBitClkFreq_Hz <= (HsLpTimingTable[i][0U] * 1000000U))
        {
            break;
        }
    }

    if (i == ARRAY_SIZE(HsLpTimingTable))
    {
        i--;
    }

    config->tClkLp2Hs_ByteClk  = HsLpTimingTable[i][1U];
    config->tClkHs2Lp_ByteClk  = HsLpTimingTable[i][2U];
    config->tDataLp2Hs_ByteClk = HsLpTimingTable[i][3U];
    config->tDataHs2Lp_ByteClk = HsLpTimingTable[i][4U];
}

/*!
 * brief Initializes the D-PHY
 *
 * This function configures the D-PHY timing and setups the D-PHY PLL based on
 * user configuration. The default configuration can be obtained by calling the
 * function @ref DSI_GetDefaultDphyConfig.
 *
 * param base MIPI DSI host peripheral base address.
 * param config Pointer to the D-PHY configuration.
 * retval kStatus_Success Data transfer finished with no error.
 * retval kStatus_Timeout Transfer failed because of timeout.
 */
void DSI_InitDphy(MIPI_DSI_Type *base, const dsi_dphy_config_t *config)
{
    /* Clear PHY state. */
    base->PHY_RSTZ      = 0U;
    base->PHY_TST_CTRL0 = 0U;
    base->PHY_TST_CTRL0 = MIPI_DSI_PHY_TST_CTRL0_phy_testclr_MASK;
    base->PHY_TST_CTRL0 = 0U;

    /* Configure PHY parameters. */
    base->PHY_IF_CFG = MIPI_DSI_PHY_IF_CFG_n_lanes(config->numLanes - 1U) |
                       MIPI_DSI_PHY_IF_CFG_phy_stop_wait_time(config->tStopState_ByteClk);
    base->PHY_TMR_LPCLK_CFG = MIPI_DSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time(config->tClkLp2Hs_ByteClk) |
                              MIPI_DSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time(config->tClkHs2Lp_ByteClk);
    base->PHY_TMR_CFG = MIPI_DSI_PHY_TMR_CFG_phy_lp2hs_time(config->tDataLp2Hs_ByteClk) |
                        MIPI_DSI_PHY_TMR_CFG_phy_hs2lp_time(config->tDataHs2Lp_ByteClk);
    base->PHY_TMR_RD_CFG = MIPI_DSI_PHY_TMR_RD_CFG_max_rd_time(config->maxRead_ByteClk);

    /* Enable the PHY */
    base->PHY_RSTZ = MIPI_DSI_PHY_RSTZ_phy_shutdownz_MASK | MIPI_DSI_PHY_RSTZ_phy_rstz_MASK |
                     MIPI_DSI_PHY_RSTZ_phy_enableclk_MASK | MIPI_DSI_PHY_RSTZ_phy_forcepll_MASK;
}

/*!
 * brief Calculates the D-PHY PLL dividers to generate the desired output frequency.
 *
 * The phy byte clock frequency(byte count per second) is generated by multiplying the refClkFreq_Hz,
 * the formula is as follows, m & n is configured by mediamix control block.
 *
 * desiredOutFreq_Hz = refClkFreq_Hz * (M + 2) / (N + 1).
 * M: 40 ~ 625
 * N: 0 ~ 15
 *
 * param m Control of the feedback multiplication ratio.
 * param n Control of the input frequency division ratio.
 * param refClkFreq_Hz The D-PHY input reference clock frequency (REF_CLK).
 * param desiredOutFreq_Hz Desired PLL output frequency.
 * return The actually output frequency using the returned dividers. If can not
 * find suitable dividers, return 0.
 */
uint32_t DSI_DphyGetPllDivider(uint32_t *m, uint32_t *n, uint32_t refClkFreq_Hz, uint32_t desiredOutFreq_Hz)
{
    uint32_t mCur;
    uint8_t nCur;
    uint32_t curOutFreq;
    uint32_t diffCur;
    uint32_t diff     = 0xFFFFFFFFU;
    uint32_t bestFreq = 0U;

    for (nCur = 0U; nCur <= 0xFU; nCur++)
    {
        /* Calculate the m value */
        mCur = desiredOutFreq_Hz * (nCur + 1U) / refClkFreq_Hz - 2U;

        if (mCur > 625U)
        {
            continue;
        }

        curOutFreq = refClkFreq_Hz * (mCur + 2U) / (nCur + 1U);

        if (curOutFreq > desiredOutFreq_Hz)
        {
            diffCur = (curOutFreq - desiredOutFreq_Hz);
        }
        else
        {
            diffCur = (desiredOutFreq_Hz - curOutFreq);
        }

        /* Save the better configuration. */
        if (diffCur < diff)
        {
            diff     = diffCur;
            *m       = mCur;
            *n       = nCur;
            bestFreq = curOutFreq;

            /* If the output PLL frequency is exactly the disired value, return directly. */
            if (0U == diff)
            {
                break;
            }
        }
    }

    return bestFreq;
}

/*!
 * brief Power up the DSI
 *
 * param base MIPI DSI host peripheral base address.
 * retval kStatus_Success Data transfer finished with no error.
 * retval kStatus_Timeout Transfer failed because of timeout.
 */
status_t DSI_PowerUp(MIPI_DSI_Type *base)
{
    uint32_t waitTimes = FSL_MIPI_DSI_TIMEOUT;
    base->PHY_RSTZ     = 0xfU;
    base->PWR_UP       = 1UL;

    /* Wait for the PHY lock state to set. */
    while (((base->PHY_STATUS & MIPI_DSI_PHY_STATUS_phy_lock_MASK) == 0U) && (0U != waitTimes))
    {
        waitTimes--;
    }

    if (waitTimes == 0U)
    {
        return kStatus_Timeout;
    }

    waitTimes = FSL_MIPI_DSI_TIMEOUT;
    /* Wait for the PHY stopstateclklane to set. */
    while (((base->PHY_STATUS & MIPI_DSI_PHY_STATUS_phy_stopstate0lane_MASK) != 0U) && (0U != waitTimes))
    {
        waitTimes--;
    }

    if (waitTimes == 0U)
    {
        return kStatus_Timeout;
    }
    else
    {
        return kStatus_Success;
    }
}

/*!
 * brief Configures the APB packet to send.
 *
 * This function configures the next APB packet transfer feature. After configuration,
 * user can write the payload by calling MIPI_DSI_WriteTxPayload then call MIPI_DSI_WriteTxHeader
 * to start the tranasfer or just call MIPI_DSI_WriteTxHeader alone if it is a short packet.
 *
 * param base MIPI DSI host peripheral base address.
 * param flags The transfer control flags, see ref _dsi_transfer_flags.
 */
void DSI_SetPacketControl(MIPI_DSI_Type *base, uint8_t flags)
{
    uint32_t pktCtrl = 0U;

    /* If using low power transmission, set all related bits. */
    if (0U != (flags & (uint8_t)kDSI_TransferUseLowPower))
    {
        pktCtrl |= MIPI_DSI_CMD_MODE_CFG_dcs_sw_0p_tx_MASK | MIPI_DSI_CMD_MODE_CFG_dcs_sw_1p_tx_MASK |
                   MIPI_DSI_CMD_MODE_CFG_dcs_sr_0p_tx_MASK | MIPI_DSI_CMD_MODE_CFG_dcs_lw_tx_MASK |
                   MIPI_DSI_CMD_MODE_CFG_max_rd_pkt_size_MASK | MIPI_DSI_CMD_MODE_CFG_gen_sw_0p_tx_MASK |
                   MIPI_DSI_CMD_MODE_CFG_gen_sw_1p_tx_MASK | MIPI_DSI_CMD_MODE_CFG_gen_sw_2p_tx_MASK |
                   MIPI_DSI_CMD_MODE_CFG_gen_sr_0p_tx_MASK | MIPI_DSI_CMD_MODE_CFG_gen_sr_1p_tx_MASK |
                   MIPI_DSI_CMD_MODE_CFG_gen_sr_2p_tx_MASK | MIPI_DSI_CMD_MODE_CFG_gen_lw_tx_MASK;

        /* Set low power command enable bit in video mode. */
        base->VID_MODE_CFG |= MIPI_DSI_VID_MODE_CFG_lp_cmd_en_MASK;
    }
    else
    {
        /* Clear low power command enable bit in video mode. */
        base->VID_MODE_CFG &= ~MIPI_DSI_VID_MODE_CFG_lp_cmd_en_MASK;
    }

    if (0U != (flags & (uint8_t)kDSI_TransferPerformBTA))
    {
        pktCtrl |= MIPI_DSI_CMD_MODE_CFG_ack_rqst_en_MASK;
    }

    base->CMD_MODE_CFG = pktCtrl;
}

/*!
 * brief Writes tx header to command FIFO. This will trigger the packet transfer.
 *
 * param base MIPI DSI host peripheral base address.
 * param wordCount For long packet, this is the byte count of the payload.
 *                 For short packet, this is (data1 << 8) | data0.
 * param virtualChannel Virtual channel.
 * param dataType The packet data type, (DI).
 */
void DSI_WriteTxHeader(MIPI_DSI_Type *base, uint16_t wordCount, uint8_t virtualChannel, dsi_tx_data_type_t dataType)
{
    /* Wait for the generic command FIFO not full. */
    while ((base->CMD_PKT_STATUS & MIPI_DSI_CMD_PKT_STATUS_gen_cmd_full_MASK) != 0U)
    {
    }

    uint32_t header = MIPI_DSI_GEN_HDR_gen_dt(dataType) | MIPI_DSI_GEN_HDR_gen_vc(virtualChannel) |
                      MIPI_DSI_GEN_HDR_gen_wc_lsbyte((uint8_t)wordCount) |
                      MIPI_DSI_GEN_HDR_gen_wc_msbyte((uint8_t)(wordCount >> 8U));
    base->GEN_HDR = header;
}

/*!
 * brief Fills the long APB packet payload.
 *
 * Write the long packet payload to TX FIFO.
 *
 * param base MIPI DSI host peripheral base address.
 * param payload Pointer to the payload.
 * param payloadSize Payload size in byte.
 */
void DSI_WriteTxPayload(MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize)
{
    DSI_WriteTxPayloadExt(base, payload, payloadSize, false, 0U);
}

/*!
 * brief Writes payload data to generic payload FIFO.
 *
 * Write the long packet payload to TX FIFO. This function could be used in two ways
 *
 * 1. Include the DCS command in the 1st byte of @p payload. In this case, the DCS command
 *    is the first byte of @p payload. The parameter @p sendDcsCmd is set to false,
 *    the @p dcsCmd is not used. This function is the same as @ref DSI_WriteTxPayload
 *    when used in this way.
 *
 * 2. The DCS command in not in @p payload, but specified by parameter @p dcsCmd.
 *    In this case, the parameter @p sendDcsCmd is set to true, the @p dcsCmd is the DCS
 *    command to send. The @p payload is sent after @p dcsCmd.
 *
 * param base MIPI DSI host peripheral base address.
 * param payload Pointer to the payload.
 * param payloadSize Payload size in byte.
 * param sendDcsCmd If set to true, the DCS command is specified by @p dcsCmd,
 *       otherwise the DCS command is included in the @p payload.
 * param dcsCmd The DCS command to send, only used when @p sendDCSCmd is true.
 */
void DSI_WriteTxPayloadExt(
    MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize, bool sendDcsCmd, uint8_t dcsCmd)
{
    uint8_t i;
    uint32_t wordToWrite;
    uint8_t byteEachWrite = sizeof(uint32_t);

    payloadSize = sendDcsCmd ? payloadSize + 1U : payloadSize;

    /* Write the first 4-byte. */
    if (sendDcsCmd)
    {
        wordToWrite = dcsCmd;
    }
    else
    {
        wordToWrite = *payload;
        payload++;
    }

    payloadSize--;

    for (i = 1U; i < 4U; i++)
    {
        if (payloadSize > 0U)
        {
            wordToWrite |= ((uint32_t)(*payload) << (i << 3U));
            payload++;
            payloadSize--;
        }
        else
        {
            break;
        }
    }

    base->GEN_PLD_DATA = wordToWrite;

    /* Wait for the generic payload FIFO not empty. */
    while ((base->CMD_PKT_STATUS & MIPI_DSI_CMD_PKT_STATUS_gen_buff_pld_empty_MASK) != 0U)
    {
    }

    /* Write the rest payload data if any. */
    while (payloadSize != 0U)
    {
        /* Wait for the generic payload FIFO not full. */
        while ((base->CMD_PKT_STATUS & MIPI_DSI_CMD_PKT_STATUS_gen_pld_w_full_MASK) != 0U)
        {
        }

        if (payloadSize < byteEachWrite)
        {
            memcpy(&wordToWrite, payload, payloadSize);
            base->GEN_PLD_DATA = wordToWrite;
            payloadSize        = 0U;
        }
        else
        {
            memcpy(&wordToWrite, payload, byteEachWrite);
            base->GEN_PLD_DATA = wordToWrite;
            payloadSize -= byteEachWrite;
            payload += byteEachWrite;
        }
    }
}

/*!
 * brief Reads the long APB packet payload.
 *
 * Read the long packet payload from RX FIFO. This function reads directly from
 * RX FIFO status. Upper layer should make sure the whole rx packet has been received.
 *
 * param base MIPI DSI host peripheral base address.
 * param payload Pointer to the payload buffer.
 * param payloadSize Payload size in byte.
 */
void DSI_ReadRxData(MIPI_DSI_Type *base, uint8_t *payload, uint16_t payloadSize)
{
    uint32_t readWord;
    uint8_t byteEachRead = sizeof(uint32_t);

    while (payloadSize != 0U)
    {
        /* Wait for the generic read payload FIFO not empty. */
        while ((base->CMD_PKT_STATUS & MIPI_DSI_CMD_PKT_STATUS_gen_pld_r_empty_MASK) != 0U)
        {
        }

        readWord = base->GEN_PLD_DATA;
        if (payloadSize < byteEachRead)
        {
            memcpy(payload, &readWord, payloadSize);
            payloadSize = 0U;
        }
        else
        {
            memcpy(payload, &readWord, byteEachRead);
            payloadSize -= byteEachRead;
            payload += byteEachRead;
        }
    }
}

static status_t DSI_PrepareApbTransfer(MIPI_DSI_Type *base, dsi_transfer_t *xfer)
{
    uint16_t maxReadLength =
        (base->PHY_TMR_RD_CFG & MIPI_DSI_PHY_TMR_RD_CFG_max_rd_time_MASK) >> MIPI_DSI_PHY_TMR_RD_CFG_max_rd_time_SHIFT;
    /* The receive data size should be smaller than the max rx byte count. */
    assert(xfer->rxDataSize <= maxReadLength);

    if (xfer->rxDataSize > maxReadLength)
    {
        return kStatus_DSI_NotSupported;
    }

    uint8_t txDataIndex;
    uint16_t wordCount;
    uint32_t intFlags1, intFlags2, txDataSize;

    if (xfer->rxDataSize != 0U)
    {
        xfer->flags |= (uint8_t)kDSI_TransferPerformBTA;
    }

    /* Configure the packet transfer feature. */
    DSI_SetPacketControl(base, xfer->flags);

    /* ========================== Prepare TX. ========================== */
    /* If xfer->sendDcsCmd is true, then the DCS command is not included in the
       xfer->txData, but specified by xfer->dcsCmd. */
    txDataSize = xfer->sendDscCmd ? (uint32_t)xfer->txDataSize + 1U : (uint32_t)xfer->txDataSize;

    /* Short packet. */
    if (txDataSize <= 2U)
    {
        if (0U == txDataSize)
        {
            wordCount = 0U;
        }
        else /* txDataSize = 1 or 2 */
        {
            txDataIndex = 0;

            if (xfer->sendDscCmd)
            {
                /* DCS command byte. */
                wordCount = xfer->dscCmd;
            }
            else
            {
                /* The LSB byte in header. */
                wordCount = xfer->txData[txDataIndex++];
            }

            if (2U == txDataSize)
            {
                /* The DCS optional parameter byte or the MSB byte in header. */
                wordCount |= ((uint16_t)xfer->txData[txDataIndex] << 8U);
            }
        }
    }
    /* Long packet. */
    else
    {
        wordCount = (uint16_t)txDataSize;
        DSI_WriteTxPayloadExt(base, xfer->txData, xfer->txDataSize, xfer->sendDscCmd, xfer->dscCmd);
    }

    /* Clear the interrupt flags set by previous transfer. */
    DSI_GetAndClearInterruptStatus(base, &intFlags1, &intFlags2);

    /* Write header to trigger the transfer. */
    DSI_WriteTxHeader(base, wordCount, xfer->virtualChannel, xfer->txDataType);

    return kStatus_Success;
}

/*!
 * brief APB data transfer using blocking method.
 *
 * Perform APB data transfer using blocking method. This function waits until all
 * data send or received, or timeout happens.
 *
 * param base MIPI DSI host peripheral base address.
 * param xfer Pointer to the transfer structure.
 * retval kStatus_Success Data transfer finished with no error.
 * retval kStatus_Timeout Transfer failed because of timeout.
 * retval kStatus_DSI_RxDataError RX data error, user could use ref DSI_GetRxErrorStatus
 *        to check the error details.
 * retval kStatus_DSI_PhyError PHY error detected during transfer.
 * retval kStatus_DSI_ErrorReportReceived Error Report packet received, user could use
 *        ref DSI_GetAndClearHostStatus to check the error report status.
 * retval kStatus_DSI_NotSupported Transfer format not supported.
 * retval kStatus_Fail Transfer failed for other reasons.
 */
status_t DSI_TransferBlocking(MIPI_DSI_Type *base, dsi_transfer_t *xfer)
{
    status_t status;
    uint32_t pktStatus;
    uint32_t intFlags1 = 0U, intFlags2 = 0U;

    status = DSI_PrepareApbTransfer(base, xfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    pktStatus = MIPI_DSI_CMD_PKT_STATUS_gen_cmd_empty_MASK | MIPI_DSI_CMD_PKT_STATUS_gen_pld_w_empty_MASK;
    while (true)
    {
        /* Wait for generic write command and payload FIFO is empty */
        if ((base->CMD_PKT_STATUS & pktStatus) == pktStatus)
        {
            break;
        }

        /* Hs forward tx time out. */
        DSI_GetAndClearInterruptStatus(base, &intFlags1, &intFlags2);
        if ((intFlags2 & kDSI_TimeoutErrorHtx) != 0U)
        {
            return kStatus_Timeout;
        }
    }

    /* No rx data, return directly. */
    if (0U == (xfer->flags & (uint32_t)kDSI_TransferPerformBTA))
    {
        return kStatus_Success;
    }

    pktStatus = MIPI_DSI_CMD_PKT_STATUS_gen_rd_cmd_busy_MASK;
    while (true)
    {
        /* Wait for the entire response is stored. */
        if ((base->CMD_PKT_STATUS & pktStatus) == pktStatus)
        {
            break;
        }

        /* Low power rx time out. */
        DSI_GetAndClearInterruptStatus(base, &intFlags1, &intFlags2);
        if ((intFlags2 & kDSI_TimeoutErrorLrx) != 0U)
        {
            return kStatus_Timeout;
        }
    }

    /* Process the received frame. */
    uint32_t rxPktHeader;
    uint16_t actualRxByteCount;
    uint8_t rxDataType;
    bool readRxDataFromPayload;

    /* If rx error detected in the received packet. */
    if (0U != ((uint32_t)kDSI_RxErrorEccMultiBit & intFlags2))
    {
        return kStatus_DSI_EccMultiBitError;
    }

    if (0U != ((uint32_t)kDSI_RxErrorCrc & intFlags2))
    {
        return kStatus_DSI_CrcError;
    }

    if (0U != ((uint32_t)kDSI_RxErrorPacketSize & intFlags2))
    {
        return kStatus_DSI_PacketSizeError;
    }

    if (0U != ((uint32_t)kDSI_RxErrorEotMissing & intFlags2))
    {
        return kStatus_DSI_EotMissingError;
    }

    /* If phy error detected in the received packet. */
    if (0U != ((uint32_t)kDSI_PhyErrorAll & intFlags1))
    {
        return kStatus_DSI_PhyError;
    }

    rxPktHeader = base->GEN_PLD_DATA;
    rxDataType  = rxPktHeader & 0x3FU;

    /* If received error report. */
    if ((uint8_t)kDSI_RxDataAckAndErrorReport == rxDataType)
    {
        /* The corresponding acknowledge and error report status should be set. */
        if (0U != ((uint32_t)kDSI_ErrorReportAll & intFlags1))
        {
            return kStatus_DSI_ErrorReportReceived; // TODO distinguish the error report?
        }
        else
        {
            return kStatus_Fail;
        }
    }
    else
    {
        if ((kDSI_RxDataGenShortRdResponseOneByte == rxDataType) ||
            (kDSI_RxDataDcsShortRdResponseOneByte == rxDataType))
        {
            readRxDataFromPayload = false;
            actualRxByteCount     = 1U;
        }
        else if ((kDSI_RxDataGenShortRdResponseTwoByte == rxDataType) ||
                 (kDSI_RxDataDcsShortRdResponseTwoByte == rxDataType))
        {
            readRxDataFromPayload = false;
            actualRxByteCount     = 2U;
        }
        else if ((kDSI_RxDataGenLongRdResponse == rxDataType) || (kDSI_RxDataDcsLongRdResponse == rxDataType))
        {
            readRxDataFromPayload = true;
            actualRxByteCount     = (uint16_t)(rxPktHeader >> 8U);
        }
        else /* kDSI_RxDataEoTp */
        {
            readRxDataFromPayload = false;
            xfer->rxDataSize      = 0U;
            actualRxByteCount     = 0U;
        }

        xfer->rxDataSize = MIN(xfer->rxDataSize, actualRxByteCount);

        if (xfer->rxDataSize > 0U)
        {
            if (readRxDataFromPayload)
            {
                DSI_ReadRxData(base, xfer->rxData, xfer->rxDataSize);
            }
            else
            {
                xfer->rxData[0] = (uint8_t)((rxPktHeader >> 8U) & 0xFFU);

                if (2U == xfer->rxDataSize)
                {
                    xfer->rxData[1] = (uint8_t)((rxPktHeader >> 16U) & 0xFFU);
                }
            }
        }
    }

    return kStatus_Success;
}
