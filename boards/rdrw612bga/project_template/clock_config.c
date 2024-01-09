/*
 * Copyright 2021-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_power.h"
#include "fsl_clock.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const clock_avpll_config_t g_avpllConfig_BOARD_BootClockRUN = {
    .ch1Freq = kCLOCK_AvPllChFreq12p288m,
    .ch2Freq = kCLOCK_AvPllChFreq64m,
    .enableCali = true
};

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_ClockPreConfig
 * Description   : Clock pre configuration weak function.
 *                 Called before clock tree(Such as PLL, Main clock) configuration.
 * Note          : Users need override this function to configure static voltage compansation and sensors, and in XIP
 *                 case, move FlexSPI clock to a stable clock source to avoid instruction/data fetch issue when
 *                 updating the system clock tree.
 *                 After the clock tree is changed and stable, CM33 core and FlexSPI flash can run at full speed.
 *END**************************************************************************/
__attribute__((weak)) void BOARD_ClockPreConfig(void)
{
}

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_ClockPostConfig
 * Description   : Clock post configuration weak function.
 *                 Called after clock tree(Such as PLL, Main clock) configuration.
 * Note          : Users need override this function to update FlexSPI clock source and set flash to full speed.
 *END**************************************************************************/
__attribute__((weak)) void BOARD_ClockPostConfig(void)
{
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/

/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    POWER_DisableGDetVSensors();

    if ((PMU->CAU_SLP_CTRL & PMU_CAU_SLP_CTRL_SOC_SLP_RDY_MASK) == 0U)
    {
        /* LPOSC not enabled, enable it */
        CLOCK_EnableClock(kCLOCK_RefClkCauSlp);
    }
    if ((SYSCTL2->SOURCE_CLK_GATE & SYSCTL2_SOURCE_CLK_GATE_REFCLK_SYS_CG_MASK) != 0U)
    {
        /* REFCLK_SYS not enabled, enable it */
        CLOCK_EnableClock(kCLOCK_RefClkSys);
    }

    /* Initialize T3 clocks and t3pll_mci_48_60m_irc configured to 48.3MHz */
    CLOCK_InitT3RefClk(kCLOCK_T3MciIrc48m);
    /* Enable FFRO */
    CLOCK_EnableClock(kCLOCK_T3PllMciIrcClk);
    /* Enable T3 256M clock and SFRO */
    CLOCK_EnableClock(kCLOCK_T3PllMci256mClk);

    /* Call function BOARD_ClockPreConfig() to configure static voltage compansation and sensors, and in XIP
       case, move FlexSPI clock to a stable clock source to avoid instruction/data fetch issue when updating
       the system clock tree. */
    BOARD_ClockPreConfig();

    /* First let M33 run on SOSC */
    CLOCK_AttachClk(kSYSOSC_to_MAIN_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivSysCpuAhbClk, 1);

    /* tcpu_mci_clk configured to 260MHz, tcpu_mci_flexspi_clk 312MHz. */
    CLOCK_InitTcpuRefClk(3120000000UL, kCLOCK_TcpuFlexspiDiv10);
    /* Enable tcpu_mci_clk 260MHz. Keep tcpu_mci_flexspi_clk gated. */
    CLOCK_EnableClock(kCLOCK_TcpuMciClk);

    /* tddr_mci_flexspi_clk 320MHz */
    CLOCK_InitTddrRefClk(kCLOCK_TddrFlexspiDiv10);
    CLOCK_EnableClock(kCLOCK_TddrMciFlexspiClk); /* 320MHz */

    /* Enable AUX0 PLL to 260MHz. */
    CLOCK_SetClkDiv(kCLOCK_DivAux0PllClk, 1U);

    /* Init AVPLL and enable both channels. */
    CLOCK_InitAvPll(&g_avpllConfig_BOARD_BootClockRUN);
    CLOCK_SetClkDiv(kCLOCK_DivAudioPllClk, 1U);

    /* Configure MainPll to 260MHz, then let CM33 run on Main PLL. */
    CLOCK_SetClkDiv(kCLOCK_DivSysCpuAhbClk, 1U);
    CLOCK_SetClkDiv(kCLOCK_DivMainPllClk, 1U);
    CLOCK_AttachClk(kMAIN_PLL_to_MAIN_CLK);

    /* Set SYSTICKFCLKDIV divider to value 1 */
    CLOCK_SetClkDiv(kCLOCK_DivSystickClk, 1U);
    CLOCK_AttachClk(kSYSTICK_DIV_to_SYSTICK_CLK);

    /* Set PLL FRG clock to 20MHz. */
    CLOCK_SetClkDiv(kCLOCK_DivPllFrgClk, 13U);

    /* Call function BOARD_ClockPostConfig() to set flexspi clock source to aux0_pll_clk in XIP. */
    BOARD_ClockPostConfig();

    /* Measure main_clk on CLKOUT. Set CLKOUTFCLKDIV divider to value 100 */
    CLOCK_AttachClk(kMAIN_CLK_to_CLKOUT);
    SOCCTRL->TST_TSTBUS_CTRL2 = (SOCCTRL->TST_TSTBUS_CTRL2 &
	    ~(SOCCIU_TST_TSTBUS_CTRL2_CLK_OUT_PAGE_SEL_MASK | SOCCIU_TST_TSTBUS_CTRL2_CLK_OUT_SEL_MASK)) |
            SOCCIU_TST_TSTBUS_CTRL2_CLK_OUT_PAGE_SEL(3) | SOCCIU_TST_TSTBUS_CTRL2_CLK_OUT_SEL(14);
    CLOCK_SetClkDiv(kCLOCK_DivClockOut, 100U);

    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockLPR ***********************
 ******************************************************************************/
/*******************************************************************************
 * Variables for BOARD_BootClockLPR configuration
 ******************************************************************************/

/*******************************************************************************
 * Code for BOARD_BootClockLPR configuration
 ******************************************************************************/
void BOARD_BootClockLPR(void)
{
    POWER_DisableGDetVSensors();

    CLOCK_DisableClock(kCLOCK_Pkc);
    CLOCK_DisableClock(kCLOCK_Wwdt0);
    CLOCK_DisableClock(kCLOCK_Flexcomm0);
    CLOCK_DisableClock(kCLOCK_Flexcomm2);
    CLOCK_DisableClock(kCLOCK_Flexcomm3);
    CLOCK_DisableClock(kCLOCK_Crc);
    CLOCK_DisableClock(kCLOCK_Itrc);

    RESET_SetPeripheralReset(kPKC_RST_SHIFT_RSTn);
    RESET_SetPeripheralReset(kWWDT_RST_SHIFT_RSTn);
    RESET_SetPeripheralReset(kFC0_RST_SHIFT_RSTn);
    RESET_SetPeripheralReset(kFC2_RST_SHIFT_RSTn);
    RESET_SetPeripheralReset(kFC3_RST_SHIFT_RSTn);
    RESET_SetPeripheralReset(kCRC_RST_SHIFT_RSTn);

    if ((PMU->CAU_SLP_CTRL & PMU_CAU_SLP_CTRL_SOC_SLP_RDY_MASK) == 0U)
    {
        /* LPOSC not enabled, enable it */
        CLOCK_EnableClock(kCLOCK_RefClkCauSlp);
    }
    if ((SYSCTL2->SOURCE_CLK_GATE & SYSCTL2_SOURCE_CLK_GATE_REFCLK_SYS_CG_MASK) != 0U)
    {
        /* REFCLK_SYS not enabled, enable it */
        CLOCK_EnableClock(kCLOCK_RefClkSys);
    }

    /* Initialize T3 clocks and t3pll_mci_48_60m_irc configured to 48.3MHz */
    CLOCK_InitT3RefClk(kCLOCK_T3MciIrc48m);
    /* Enable T3 256M clock and SFRO */
    CLOCK_EnableClock(kCLOCK_T3PllMci256mClk);

    /* Call function BOARD_ClockPreConfig() to configure static voltage compansation and sensors, and in XIP
       case, move FlexSPI clock to a stable clock source to avoid instruction/data fetch issue when updating
       the system clock tree. */
    BOARD_ClockPreConfig();

    /* First let M33 run on SOSC */
    CLOCK_AttachClk(kSYSOSC_to_MAIN_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivSysCpuAhbClk, 1);

    /* tcpu_mci_clk configured to 260MHz, tcpu_mci_flexspi_clk 312MHz. */
    CLOCK_InitTcpuRefClk(3120000000UL, kCLOCK_TcpuFlexspiDiv10);
    /* Enable tcpu_mci_clk 260MHz. Keep tcpu_mci_flexspi_clk gated. */
    CLOCK_EnableClock(kCLOCK_TcpuMciClk);

    /* Enable AUX0 PLL to 260MHz. */
    CLOCK_SetClkDiv(kCLOCK_DivAux0PllClk, 1U);

    /* Configure MainPll to 260MHz, then let CM33 run on Main PLL. */
    CLOCK_SetClkDiv(kCLOCK_DivSysCpuAhbClk, 1U);
    CLOCK_SetClkDiv(kCLOCK_DivMainPllClk, 1U);
    CLOCK_AttachClk(kMAIN_PLL_to_MAIN_CLK);

    /* Set SYSTICKFCLKDIV divider to value 1 */
    CLOCK_SetClkDiv(kCLOCK_DivSystickClk, 1U);
    CLOCK_AttachClk(kSYSTICK_DIV_to_SYSTICK_CLK);

    /* Set PLL FRG clock to 20MHz. */
    CLOCK_SetClkDiv(kCLOCK_DivPllFrgClk, 13U);

    /* Call function BOARD_ClockPostConfig() to set flexspi clock source to aux0_pll_clk in XIP. */
    BOARD_ClockPostConfig();

    /* Deinitialize TDDR clocks */
    CLOCK_DeinitTddrRefClk();

    /* Deinitialize AVPLL clocks */
    CLOCK_DeinitAvPll();

    /* Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}
