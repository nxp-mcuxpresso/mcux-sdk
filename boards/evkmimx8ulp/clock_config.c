/*
 * Copyright 2020-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "clock_config.h"
#include "board.h"
#include "fsl_upower.h"

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*
 * SYSOSC clock setting.
 * SYSOSC clock         : 24MHz
 */
const cgc_sosc_config_t g_cgcSysOscConfig = {.freq        = BOARD_XTAL0_CLK_HZ,
                                             .enableMode  = 0, /* Disabled in Deep Sleep/Power down */
                                             .monitorMode = kCGC_SysOscMonitorDisable,
                                             .workMode    = kCGC_SysOscModeOscLowPower};

/*
 * FRO clock setting.
 * FRO clock            : 192MHz
 */
const cgc_fro_config_t g_cgcFroConfig = {.enableMode = 0 /*0 - FRO is disabled in Sleep/Deep Sleep Modes*/};

/*
 * MAX FREQ:
 * PLL0 VCO: 480 MHz
 * PLL0 PFD0: 400 MHz
 * PLL0 PFD1: 480 MHz
 * PLL0 PFD2: 480 MHz
 * PLL0 PFD3: 400 MHz
 *
 * PLL0 clock setting.
 * PLL0 clock VCO       : 24 * 20 = 480MHz
 * PLL0 VCODIV output   : 0MHz
 * PLL0 PFD1DIV output  : 0MHz
 * PLL0 PFD2DIV output  : 0MHz
 */
const cgc_pll0_config_t g_cgcPll0Config = {.enableMode = kCGC_PllEnable,
                                           .div1 = 0U,
                                           .pfd1Div = 0U,
                                           .pfd2Div = 0U,
                                           .src = kCGC_PllSrcSysOsc,
                                           .mult = kCGC_Pll0Mult20
                                          }; /* x20 */

/*
 * MAX FREQ:
 * PLL1 VCO: 542 MHz
 * PLL1 PFD0: 432 MHz
 * PLL1 PFD1: 400 MHz
 * PLL1 PFD2: 542 MHz
 * PLL1 PFD3: 480 MHz
 *
 * PLL1 clock setting.
 * PLL1 clock VCO       : 24 * 22.528 = 540.672MHz
 * PLL1 VCODIV output   : 0MHz
 * PLL1 PFD1DIV output  : 0MHz
 * PLL1 PFD2DIV output  : 540.672 / 44 = 12.288MHz
 */
const cgc_pll1_config_t g_cgcPll1Config = {.enableMode = kCGC_PllEnable,
                                           .div1 = 0U,
                                           .pfd1Div = 0U,
                                           .pfd2Div = 44U,
                                           .src = kCGC_PllSrcSysOsc,
                                           .mult = kCGC_Pll1Mult22,
                                           .num = 528000U,
                                           .denom = 1000000U};

/*
 * Select FRO as system clock source, before configuring other clock sources.
 * Clock source   : FRO
 * Core clock     : 192 / (0 + 1) = 192MHz
 * Bus clock      : 192 / ((0 + 1) * (1 + 1)) = 96MHz
 * Slow clock     : 192 / ((0 + 1) * (1 + 3)) = 48MHz
 */
cgc_rtd_sys_clk_config_t g_sysClkConfigFroSource = {
    .divCore = 0, /* Core clock divider. */
    .divBus  = 1, /* Bus clock divider. */
    .divSlow = 3, /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcFro, /* System clock source. */
    .locked  = 0, /* Register not locked. */
};

// clang-format off
/*
 * Note: CM33 slow clock must be slower and an integer division of CM33 system IP bus.
 * System clock source and divider in Normal RUN mode.
 *
 * Clock source   : PLL0 main clock 480 MHz.
 * Core clock     : 480 / (2 + 1) = 160 MHz
 * Bus clock      : 480 / ((2 + 1) * (2 + 1)) = 53.33 MHz
 * Slow clock     : 480 / ((2 + 1) * (8 + 1)) = 17.77778 MHz
 *
 * Clock source   : PLL0PFD0 main clock 392.7272 MHz.
 * Core clock     : 392.7272 / (1 + 1) = 196.3636 MHz
 * Bus clock      : 392.7272 / ((1 + 1) * (1 + 1)) = 98.1818 MHz
 * Slow clock     : 392.7272 / ((1 + 1) * (9 + 1)) = 19.63636 MHz
 *
 * Clock source   : PLL1PFD0 main clock 423.134608 MHz.
 * Core clock     : 423.134608 / (1 + 1) = 211.567304 MHz
 * Bus clock      : 423.134608 / ((1 + 1) * (1 + 1)) = 105.783652 MHz
 * Slow clock     : 423.134608 / ((1 + 1) * (9 + 1)) =  21.1567304 MHz
 *
 * Clock source   : PLL1PFD0 main clock 405.504 MHz.
 * Core clock     : 405.504 / (1 + 1) = 202.752 MHz
 * Bus clock      : 405.504 / ((1 + 1) * (1 + 1)) = 101.376 MHz
 * Slow clock     : 405.504 / ((1 + 1) * (9 + 1)) = 20.2752 MHz
 *
 * Clock source   : PLL1PFD0 main clock 389.28384 MHz.
 * Core clock     : 389.28384 / (1 + 1) =  194.64192 MHz
 * Bus clock      : 389.28384 / ((1 + 1) * (1 + 1)) = 97.32096 MHz
 * Slow clock     : 389.28384 / ((1 + 1) * (9 + 1)) = 21.62688 MHz
 * +---------------------------------------------------------------------------------------------------------------------------------------+
 * |  RTD Power Mode |    Biasing Option |  Drive Mode | Max CM33_CORECLK freq/MHz | Max CM33_BUSCLK freq/MHz |  Max CM33_SLOWCLK freq/MHz |
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * |    ACTIVE       |        ARBB       |     UD      |        38.4               |         20               |          12.5              |
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * |    ACTIVE       |        AFBB       |     ND      |        160                |         65               |           20               |
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * |    ACTIVE       |        AFBB       |     OD      |        216                |         108              |           24               |
 * +---------------------------------------------------------------------------------------------------------------------------------------+
 *
 */
// clang-format on
#define SELECT_PLL0PFD0_AS_SOURCE_CLK (0)
#define SELECT_PLL1PFD0_AS_SOURCE_CLK (0)
//#define SELECT_PLL1PFD0_AS_SOURCE_CLK (1)
cgc_rtd_sys_clk_config_t g_sysClkConfigRun = {
#if SELECT_PLL0PFD0_AS_SOURCE_CLK
    .divBus  = 1,   /* Bus clock divider. */
    .divSlow = 9,   /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcPll0Pfd0, /* PLL0PFD0 main clock source. */
    .divCore = 1,   /* Core clock divider. */
#elif SELECT_PLL1PFD0_AS_SOURCE_CLK
    .divBus  = 1,   /* Bus clock divider. */
    .divSlow = 9,   /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcPll1Pfd0, /* PLL1PFD0 main clock source. */
    .divCore = 1,   /* Core clock divider. */
#else
    .divBus  = 1,   /* Bus clock divider. */
    .divSlow = 7,   /* Slow clock divider. */
    .src     = kCGC_RtdSysClkSrcPll0, /* PLL0 main clock source. */
    .divCore = 2,   /* Core clock divider. */
#endif
    .locked  = 0, /* Register not locked. */
};

static cgc_rtd_sys_clk_src_t clk_src[] = {
    kCGC_RtdSysClkSrcFro,
    kCGC_RtdSysClkSrcLvds,
    kCGC_RtdSysClkSrcLvds,
};
/*******************************************************************************
 * Code
 ******************************************************************************/
void BOARD_InitClock(void)
{
    CLOCK_InitFro(&g_cgcFroConfig);

    if (!CLOCK_IsSysOscValid())
    {
        CLOCK_InitSysOsc(&g_cgcSysOscConfig);
    }

    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    /* Then set SOSC, FRO DIV needed by application */
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv1Clk, 1);
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv2Clk, 1);
    CLOCK_SetRtdSysOscAsyncClkDiv(kCGC_AsyncDiv3Clk, 0);

    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv1Clk, 1);
    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv2Clk, 1);
    CLOCK_SetRtdFroAsyncClkDiv(kCGC_AsyncDiv3Clk, 0);

    /* RTC OSC clock is enabled by default, but spin till it is stable */
    while(!CLOCK_IsRtcOscValid())
    {
    }
    CLOCK_SetXtal32Freq(CLK_RTC_32K_CLK);
}

void BOARD_CalculateDivider(uint32_t src_freq, uint32_t dest_freq, int * divider)
{
    uint32_t div = 1;

    if (divider != NULL)
    {
        while ((src_freq / div) > dest_freq)
        {
            div++;
        }

        *divider = div;
    }
}

void BOARD_InitPlls(void)
{
    /* Initialize PLL0 480MHz */
    CLOCK_InitPll0(&g_cgcPll0Config);

    /* Enable Pll0 Pfd0(MAX Freq is 400 MHz) 392.7272 MHz = (18 * 480) / 22 */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd0Clk, 22U);
    /* Enable Pll0 Pfd1(MAX Freq is 480 MHz) 480 MHz = (18 * 480) / 18 */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd1Clk, 18U);
    /* Enable Pll0 Pfd2(MAX Freq is 480 MHz) 480MHz */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd2Clk, 18U);
    /* Enable Pll0 Pfd3(MAX Freq is 400 MHz) 392.7272 MHz = (18 * 480) / 22 */
    CLOCK_EnablePll0PfdClkout(kCGC_PllPfd3Clk, 22U);

    /* Initialize PLL1(MAX Freq is 542 MHz) 540.672 MHz */
    CLOCK_InitPll1(&g_cgcPll1Config);
    /* Enable Pll1 Pfd0(MAX Freq is 432 MHz) 423.134608 MHz = (18 * 540.672) / 23 */
    CLOCK_EnablePll1PfdClkout(kCGC_PllPfd0Clk, 23U);
    /* Enable Pll1 Pfd2(MAX Freq is 542 MHz) 540.672MHz */
    CLOCK_EnablePll1PfdClkout(kCGC_PllPfd2Clk, 18U);
}

/*
 * Clock in RUN mode:
 * SYSOSC  : Enable
 * FRO    : Enable
 * FIRC    : Enable
 * PLL0  : Enable
 * AUXPLL  : Enable
 *
 * Note: 
 *     Pls decrease cortex-m33's clock frequency before decreasing voltage.
 *     Pls increase voltage before increasing cortex-m33's clock frequency.
 */
void BOARD_BootClockRUN(void)
{
    int freq_divider = 1;

    UPOWER_Init(NULL);
    BOARD_InitClock();

    /* default voltage is 1.0 V for Real Time Domain, default cortex-m33's clock frequency is 92 MHz(clock source is FRO192CLK, div is 1, so 192 MHz / (1 + 1) = 96 MHz) */

    /* Call function BOARD_FlexspiClockSafeConfig() to move FlexSPI clock to a stable clock source to avoid
       instruction/data fetch issue when updating PLL and Main clock if XIP(execute code on FLEXSPI memory). */
    BOARD_FlexspiClockSafeConfig();

    BOARD_InitPlls();

    BOARD_UpdateM33CoreFreq(&g_sysClkConfigRun);

    /*
     * Call function BOARD_SetFlexspiClock() to set user configured clock source/divider for FlexSPI.
     * 5 - CM33 CORE/PLAT CLK
     */
    BOARD_CalculateDivider(SystemCoreClock, BOARD_NOR_FLASH_READ_MAXIMUM_FREQ, &freq_divider);
    BOARD_SetFlexspiClock(FLEXSPI0, 5U, freq_divider - 1, 0U); /* flexspi0's clock is CM33_PLATCLK / div */
}

/*
 * Init Clock after system exit from Power Down:
 * SYSOSC  : Enable
 * FRO    : Enable
 * FIRC    : Enable
 * PLL0  : Enable
 * AUXPLL  : Enable
 */
void BOARD_ResumeClockInit(void)
{
    uint32_t tmp_clk_cfg = 0U;
    uint32_t new_freq = 0U;
    uint32_t current_freq = CLOCK_GetFreq(kCLOCK_Cm33CorePlatClk); /* get cm33 core/platform clock frequency */
    int freq_divider = 1;

    memcpy(&tmp_clk_cfg, &g_sysClkConfigRun, sizeof(g_sysClkConfigRun));
    new_freq = CLOCK_GetRtdSysClkFreq(tmp_clk_cfg, kCGC_SysClkCorePlat);

    if (current_freq != new_freq)
    {
        BOARD_InitClock();

        /*
	 * Call function BOARD_FlexspiClockSafeConfig() to move FlexSPI clock to a stable clock source to avoid
         * instruction/data fetch issue when updating PLL and Main clock if XIP(execute code on FLEXSPI memory).
	 */
        BOARD_FlexspiClockSafeConfig();

        BOARD_InitPlls();

        BOARD_UpdateM33CoreFreq(&g_sysClkConfigRun);

        /*
         * Call function BOARD_SetFlexspiClock() to set user configured clock source/divider for FlexSPI.
         * 5 - CM33 CORE/PLAT CLK
         */
        BOARD_CalculateDivider(SystemCoreClock, BOARD_NOR_FLASH_READ_MAXIMUM_FREQ, &freq_divider);
        BOARD_SetFlexspiClock(FLEXSPI0, 5U, freq_divider - 1, 0U); /* flexspi0's clock is CM33_PLATCLK / div */
        /* Reinitialize debug console */
        BOARD_InitDebugConsole();
    }
}

drive_mode_e BOARD_CalculateCoreClkDivider(cgc_rtd_sys_clk_src_t clk_src, int *core_clk_divider, int *bus_clk_divider, int *slow_clk_divider, drive_mode_e drive_mode)
{
    drive_mode_e new_drive_mode = drive_mode;
    const rtd_sys_clk_src_and_clk_name_t clk_src_and_clk_name[] = {
        {kCGC_RtdSysClkSrcFro, kCLOCK_FroClk},
        {kCGC_RtdSysClkSrcPll0Pfd0, kCLOCK_Pll0Pfd0Clk},
        {kCGC_RtdSysClkSrcPll1Pfd0, kCLOCK_Pll1Pfd0Clk},
        {kCGC_RtdSysClkSrcSysOsc, kCLOCK_SysOscClk},
        {kCGC_RtdSysClkSrcRtcOsc, kCLOCK_RtcOscClk},
        {kCGC_RtdSysClkSrcLvds, kCLOCK_LvdsClk},
        {kCGC_RtdSysClkSrcPll0, kCLOCK_Pll0Clk}
    };

    // clang-format off
    /*
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     * |  RTD Power Mode |    Biasing Option |  Drive Mode | Max CM33_CORECLK freq/MHz | Max CM33_BUSCLK freq/MHz |  Max CM33_SLOWCLK freq/MHz |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        ARBB       |     UD      |        38.4               |         20               |          12.5              |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        AFBB       |     ND      |        160                |         65               |           20               |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        AFBB       |     OD      |        216                |         108              |           24               |
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     *
     */
    // clang-format on


    drive_mode_and_clk_t drive_mode_and_clk[] = {
        { DRIVE_MODE_UD, CM33_CORE_MAX_FREQ_UD, CM33_BUS_MAX_FREQ_UD, CM33_SLOW_MAX_FREQ_UD},
        { DRIVE_MODE_ND, CM33_CORE_MAX_FREQ_ND, CM33_BUS_MAX_FREQ_ND, CM33_SLOW_MAX_FREQ_ND},
        { DRIVE_MODE_OD, CM33_CORE_MAX_FREQ_OD, CM33_BUS_MAX_FREQ_OD, CM33_SLOW_MAX_FREQ_OD},
    };
    uint32_t freq = 0U;
    cgc_rtd_sys_clk_config_t tmp_sys_clk_cfg;
    uint32_t tmp_cfg;

    memset((void *)&tmp_sys_clk_cfg, 0, sizeof(tmp_sys_clk_cfg));

    freq = CLOCK_GetFreq(clk_src_and_clk_name[(int)clk_src].clk_name);

    if (core_clk_divider != NULL)
    {
        BOARD_CalculateDivider(freq, drive_mode_and_clk[drive_mode].max_core_clk_freq, core_clk_divider);
        tmp_sys_clk_cfg.src = clk_src;
        tmp_sys_clk_cfg.divCore = *core_clk_divider - 1;
        freq /= (*core_clk_divider); /* calculate core clock frequency */
        if ((slow_clk_divider != NULL) && (bus_clk_divider != NULL))
        {
            BOARD_CalculateDivider(freq, drive_mode_and_clk[drive_mode].max_bus_clk_freq, bus_clk_divider);
            BOARD_CalculateDivider(freq, drive_mode_and_clk[drive_mode].max_slow_clk_freq, slow_clk_divider);
            /* Note: CM33 slow clock must be slower and an integer division of CM33 system IP bus. */
            while (((*slow_clk_divider <= *bus_clk_divider) || ((*slow_clk_divider) % (*bus_clk_divider) != 0U)))
            {
                *slow_clk_divider = *slow_clk_divider + 1;
            }
            tmp_sys_clk_cfg.divBus = *bus_clk_divider - 1;
            tmp_sys_clk_cfg.divSlow = *slow_clk_divider - 1;
        }
        memcpy(&tmp_cfg, &tmp_sys_clk_cfg, sizeof(tmp_sys_clk_cfg));
        freq = CLOCK_GetRtdSysClkFreq(tmp_cfg, kCGC_SysClkCorePlat);
        new_drive_mode = BOARD_GetDriveModeByCoreFreq(freq);
    }

    return new_drive_mode;
}

drive_mode_e BOARD_SwitchToFROClk(drive_mode_e drive_mode)
{
    drive_mode_e new_drive_mode = drive_mode;

    /* Switch to FRO when the current clock source is non FRO */
    if (((CGC_RTD->CM33CLK & CGC_CM33CLK_SCS_MASK) >> CGC_CM33CLK_SCS_SHIFT) != kCGC_RtdSysClkSrcFro)
    {
        int core_clk_divider = 0;
        int bus_clk_divider = 0;
        int slow_clk_divider = 0;

        /* Now start to set up FRO clock. */
        /* Step 1. Configure clock. */
        CGC_RTD->FROCSR = (uint32_t)g_cgcFroConfig.enableMode;

        /* Step 2. Wait for FRO clock to be valid. */
        while (0UL == (CGC_RTD->FROCSR & CGC_FROCSR_FROVLD_MASK))
        {
        }

        if (!CLOCK_IsSysOscValid())
        {
            CLOCK_InitSysOsc(&g_cgcSysOscConfig);
        }

        new_drive_mode = BOARD_CalculateCoreClkDivider((cgc_rtd_sys_clk_src_t)g_sysClkConfigFroSource.src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, drive_mode);
        assert(new_drive_mode == drive_mode);
        g_sysClkConfigFroSource.divCore = core_clk_divider - 1;
        g_sysClkConfigFroSource.divBus = bus_clk_divider - 1;
        g_sysClkConfigFroSource.divSlow = slow_clk_divider - 1;
        CLOCK_SetCm33SysClkConfig(&g_sysClkConfigFroSource);
        SystemCoreClockUpdate();

        for (int i = 0; i < 100; i++)
        {
            __asm volatile("NOP");
        }
    }
    return new_drive_mode;
}

/* Disable PLL0 and PLL1 */
void BOARD_DisablePlls(void)
{
    /* Disable clocks for power saving */
    CGC_RTD->PLL0CSR = 0;
    CGC_RTD->PLL1CSR = 0;
}

drive_mode_e BOARD_GetRtdDriveMode(void)
{
    static drive_mode_e rtd_drive_mode;
    int32_t status                   = -1;
    int voltage                      = 0;
    uint32_t mask = __get_PRIMASK();

    (void)status; /*fix build warning when with -Os optimizetion level */
    /* check the global interrupt whether is enabled */
    if (mask == 0U)
    {
        /* get current drive mode(Accoring to voltage of buck2, buck2 is the supply voltage for RTD Domain) */
        status                  = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
        assert(status == 0);
        switch (voltage)
        {
            case PMIC_VOLTAGE_1_1V:
                rtd_drive_mode = DRIVE_MODE_OD;
                break;
            case PMIC_VOLTAGE_1_0V:
                rtd_drive_mode = DRIVE_MODE_ND;
                break;
            case PMIC_VOLTAGE_0_9V:
                rtd_drive_mode = DRIVE_MODE_UD;
                break;
            default:
                assert(false);
                break;
        }
    }

    return rtd_drive_mode;
}

drive_mode_e BOARD_GetDriveModeByCoreFreq(uint32_t freq)
{
    drive_mode_e drive_mode = DRIVE_MODE_ND;

    if ((freq > CM33_CORE_MAX_FREQ_ND) && (freq <= CM33_CORE_MAX_FREQ_OD))
    {
        drive_mode = DRIVE_MODE_OD;
    }
    else if ((freq > CM33_CORE_MAX_FREQ_UD) && (freq <= CM33_CORE_MAX_FREQ_ND))
    {
        drive_mode = DRIVE_MODE_ND;
    }
    else if ((freq > 0U) && (freq <= CM33_CORE_MAX_FREQ_UD))
    {
        drive_mode = DRIVE_MODE_UD;
    }
    else
    {
        assert(false);
    }

    return drive_mode;
}

int32_t BOARD_UpdateM33CoreFreq(cgc_rtd_sys_clk_config_t *config)
{
    uint32_t m33_dest_core_frequency = 0;
    int32_t status                   = -1;
    int voltage                      = 0;
    uint32_t tmp_cfg;
    drive_mode_e drive_mode;
    int i = 0;

    for (i = 0; i < ARRAY_SIZE(clk_src); i++)
    {
        if (clk_src[i] == kCGC_RtdSysClkSrcLvds)
        {
             clk_src[i] = (cgc_rtd_sys_clk_src_t)g_sysClkConfigRun.src;
             if (i == DRIVE_MODE_OD)
             {
                 /* Max freq of Pll1Pfd0 is 432 MHz, the frequency is 423.134608 MHz = (18 * 540.672) / 23(In BOARD_InitPlls()] */
                 clk_src[i] = kCGC_RtdSysClkSrcPll1Pfd0; /* Use the clock source to provide higher frequency for cortex-m33 */
             }
        }
    }
    if (BOARD_IS_XIP_FLEXSPI0())
    {
        /*
         * Workaround: For flash target mode, after Mcore resume from Power down mode.
         * Apply UPOWER_GetPmicVoltage function will cause DDR exit retention process fail.
         * Try add delay function, it still fail.
         */
        pca9460_buck3ctrl_t tmp_buck3_ctrl;
        pca9460_ldo1_cfg_t tmp_ldo1_cfg;

        tmp_buck3_ctrl.val = 0U;
        tmp_ldo1_cfg.val = 0U;

        UPOWER_ReadPmicReg(PCA9460_BUCK3CTRL_ADDR, &(tmp_buck3_ctrl.val));
        UPOWER_ReadPmicReg(PCA9460_LDO1_CFG_ADDR, &(tmp_ldo1_cfg.val));
        UPOWER_ReadPmicReg(PCA9460_BUCK3CTRL_ADDR, &(tmp_buck3_ctrl.val));
        UPOWER_ReadPmicReg(PCA9460_LDO1_CFG_ADDR, &(tmp_ldo1_cfg.val));
    }

    drive_mode = BOARD_GetRtdDriveMode();
    (void)drive_mode; /* fix warning */

    memcpy(&tmp_cfg, config, sizeof(cgc_rtd_sys_clk_config_t));

    /* Get current clock frequency(SystemCoreClock) */
    SystemCoreClockUpdate();
    /*
     * 160 MHz  < m33 core frequency <= 216 MHz: 1.1 V w/AFBB
     * 38.4 MHz  < m33 core frequency <= 160 MHz: 1.0 V w/AFBB
     * 0 MHz < m33 core frequency <= 38.4 MHz: 0.9 V w/ARBB
     */
    m33_dest_core_frequency = CLOCK_GetRtdSysClkFreq(tmp_cfg, kCGC_SysClkCorePlat);
    status                  = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
    if (status == 0)
    {
        if (m33_dest_core_frequency < SystemCoreClock)
        {
            /* Decrease core frequency */
            /* Pls decrease cortex-m33's clock frequency before decreasing voltage. */

            /* check whether need decrease voltage */
            /* 160 MHz < current core clk of cortex-m33 <= 216 MHz */
            if (SystemCoreClock > CM33_CORE_MAX_FREQ_ND && SystemCoreClock <= CM33_CORE_MAX_FREQ_OD)
            {
                /* 160 MHz < next core clk for cortex-m33 <= 216 MHz */
                if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_ND &&
                    m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_OD)
                {
                    config->src = clk_src[DRIVE_MODE_OD];
                    CLOCK_SetCm33SysClkConfig(config);
                }
                /* 38.4 MHz < next core clk for cortex-m33 <= 160 MHz */
                else if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_UD &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_ND)
                {
                    config->src = clk_src[DRIVE_MODE_ND];
                    CLOCK_SetCm33SysClkConfig(config);
                    if (voltage != PMIC_VOLTAGE_1_0V)
                    {
	                /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_ND);
                        assert(status == 0);
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_1_0V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                            if (status == 0 && voltage == PMIC_VOLTAGE_1_0V)
                            {
                            }
                            else
                            {
                                assert(false);
                            }
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                }
                /* 0 MHz < next core clk for cortex-m33 <= 38.4 MHz */
                else if (m33_dest_core_frequency > 0 &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_UD)
                {
                    config->src = clk_src[DRIVE_MODE_UD];
                    CLOCK_SetCm33SysClkConfig(config);
                    if (voltage != PMIC_VOLTAGE_0_9V)
                    {
                        /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_UD);
                        assert(status == 0);
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_0_9V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                            if (status == 0 && voltage == PMIC_VOLTAGE_0_9V)
                            {
                            }
                            else
                            {
                                assert(false);
                            }
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                }
            }
            /* 38.4 MHz < current core clk of cortex-m33 <= 160 MHz */
            else if (SystemCoreClock > CM33_CORE_MAX_FREQ_UD && SystemCoreClock <= CM33_CORE_MAX_FREQ_ND)
            {
                /* 38.4 MHz < next core clk for cortex-m33 <= 160 MHz */
                if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_UD &&
                    m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_ND)
                {
                    config->src = clk_src[DRIVE_MODE_ND];
                    CLOCK_SetCm33SysClkConfig(config);
                }
                /* 0 MHz < next core clk for cortex-m33 <= 38.4 MHz */
                else if (m33_dest_core_frequency > 0 &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_UD)
                {
                    config->src = clk_src[DRIVE_MODE_UD];
                    CLOCK_SetCm33SysClkConfig(config);
                    if (voltage != PMIC_VOLTAGE_0_9V)
                    {
                        /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_UD);
                        assert(status == 0);
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_0_9V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                            if (status == 0 && voltage == PMIC_VOLTAGE_0_9V)
                            {
                            }
                            else
                            {
                                assert(false);
                            }
                        }
                    }
                }
            }
            /* 0 MHz < current core clk of cortex-m33 <= 38.4 MHz */
            else if (SystemCoreClock > 0 && SystemCoreClock <= CM33_CORE_MAX_FREQ_UD)
            {
                config->src = clk_src[DRIVE_MODE_UD];
                CLOCK_SetCm33SysClkConfig(config);
            }
        }
        else if (m33_dest_core_frequency > SystemCoreClock)
        {
            /* Increase voltage from 1.0 V to 1.1 V before increasing cortex-m33's clock frequency */
            /* check whether need increase voltage */
            /* 160 MHz < current core clk of cortex-m33 <= 216 MHz */
            if (SystemCoreClock > CM33_CORE_MAX_FREQ_ND && SystemCoreClock <= CM33_CORE_MAX_FREQ_OD)
            {
                /* 160 MHz < next core clk for cortex-m33 <= 216 MHz */
                if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_ND &&
                    m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_OD)
                {
                    config->src = clk_src[DRIVE_MODE_OD];
                }
            }
            /* 38.4 MHz < current core clk of cortex-m33 <= 160 MHz */
            else if (SystemCoreClock > CM33_CORE_MAX_FREQ_UD && SystemCoreClock <= CM33_CORE_MAX_FREQ_ND)
            {
                /* 160 MHz < next core clk for cortex-m33 <= 216 MHz */
                if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_ND &&
                    m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_OD)
                {
                    config->src = clk_src[DRIVE_MODE_OD];
                    if (voltage != PMIC_VOLTAGE_1_1V)
                    {
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_1_1V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                    if (status == 0 && voltage == PMIC_VOLTAGE_1_1V)
                    {
                        /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_OD);
                        assert(status == 0);
                    }
                    else
                    {
                        assert(false);
                    }
                }
                /* 38.4 MHz < next core clk for cortex-m33 <= 160 MHz */
                else if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_UD &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_ND)
                {
                    config->src = clk_src[DRIVE_MODE_ND];
                }
            }
            /* 0 MHz < current core clk of cortex-m33 <= 38.4 MHz */
            else if (SystemCoreClock > 0 && SystemCoreClock <= CM33_CORE_MAX_FREQ_UD)
            {
                /* 160 MHz < next core clk for cortex-m33 <= 216 MHz */
                if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_ND &&
                    m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_OD)
                {
                    config->src = clk_src[DRIVE_MODE_OD];
                    if (voltage != PMIC_VOLTAGE_1_1V)
                    {
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_1_1V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                    if (status == 0 && voltage == PMIC_VOLTAGE_1_1V)
                    {
                        /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_OD);
                        assert(status == 0);
                    }
                    else
                    {
                        assert(false);
                    }
                }
                /* 38.4 MHz < next core clk for cortex-m33 <= 160 MHz */
                else if (m33_dest_core_frequency > CM33_CORE_MAX_FREQ_UD &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_ND)
                {
                    config->src = clk_src[DRIVE_MODE_ND];
                    if (voltage != PMIC_VOLTAGE_1_0V)
                    {
                        status = UPOWER_ChngPmicVoltage(PMIC_BUCK2, PMIC_VOLTAGE_1_0V);
                        if (status == 0)
                        {
                            status = UPOWER_GetPmicVoltage(PMIC_BUCK2, &voltage);
                        }
                        else
                        {
                            assert(false);
                        }
                    }
                    if (status == 0 && voltage == PMIC_VOLTAGE_1_0V)
                    {
                        /* update bias configuration */
                        status = UPOWER_ChngRTDDomBias(DRIVE_MODE_ND);
                        assert(status == 0);
                    }
                    else
                    {
                        assert(false);
                    }
                }
                /* 0 MHz < next core clk for cortex-m33 <= 38.4 MHz */
                else if (m33_dest_core_frequency > 0 &&
                         m33_dest_core_frequency <= CM33_CORE_MAX_FREQ_UD)
                {
                    config->src = clk_src[DRIVE_MODE_UD];
                }
            }
            CLOCK_SetCm33SysClkConfig(config);
        }
    }

    /* update clock frequency */
    SystemCoreClockUpdate();
    /* update drive mode */
    drive_mode = BOARD_GetRtdDriveMode();
    (void)drive_mode; /* fix warning */

    return status;
}

void BOARD_SwitchDriveMode(void)
{
    drive_mode_e current_rtd_drive_mode = DRIVE_MODE_OD, next_drive_mode = DRIVE_MODE_ND, new_drive_mode = DRIVE_MODE_ND;
    int core_clk_divider = 0;
    int bus_clk_divider = 0;
    int slow_clk_divider = 0;
    int status = -1;
    int freq_divider = 1;
    cgc_rtd_sys_clk_config_t tmp_sys_clk_cfg;
    uint32_t buck_idx = PMIC_BUCK2;
    cgc_rtd_sys_clk_src_t next_clk_src = kCGC_RtdSysClkSrcFro;
    static int switch_flag = SWITCH_DRIVE_MODE_INIT_STATE; /* 0: initial state; 1: switch from ND to OD; 2: switch from ND to UD; 3: switch from UD to ND; 4: switch from OD to ND */

    // clang-format off
    /*
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     * |  RTD Power Mode |    Biasing Option |  Drive Mode | Max CM33_CORECLK freq/MHz | Max CM33_BUSCLK freq/MHz |  Max CM33_SLOWCLK freq/MHz |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        ARBB       |     UD      |        38.4               |         20               |          12.5              |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       }        AFBB       |     ND      |        160                |         65               |           20               |
     * -----------------------------------------------------------------------------------------------------------------------------------------
     * |    ACTIVE       |        AFBB       |     OD      |        216                |         108              |           24               |
     * +---------------------------------------------------------------------------------------------------------------------------------------+
     *
     */
    // clang-format on

    // clang-format off
    /*
     * state machine for switching drive mode of RTD:
     * --<----
     * |     |
     * UD() -> ND -> OD
     *       |      |
     *       ---<----
     * UD: 0.9 V (only FRO is available for RTD in Under Drive Mode)
     * ND: 1.0 V
     * OD: 1.1 V
     */
    // clang-format on
    int voltage[] = {
        PMIC_VOLTAGE_0_9V,
	PMIC_VOLTAGE_1_0V,
	PMIC_VOLTAGE_1_1V
    };

    (void)status; /*fix build warning when with -Os optimizetion level */
    memcpy(&tmp_sys_clk_cfg, &g_sysClkConfigRun, sizeof(g_sysClkConfigRun));
    /* Get current Drive Mode of RTD */
    current_rtd_drive_mode = BOARD_GetRtdDriveMode();
    switch (current_rtd_drive_mode)
    {
        case DRIVE_MODE_UD:
            /* UD -> ND */
            next_drive_mode = DRIVE_MODE_ND;
            next_clk_src = clk_src[next_drive_mode];
            new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
            switch_flag = SWITCH_DRIVE_MODE_FROM_UD_TO_ND;
            break;
        case DRIVE_MODE_ND:
	    if (switch_flag == SWITCH_DRIVE_MODE_INIT_STATE)
            {
                 /* from ND -> OD */
                next_drive_mode = DRIVE_MODE_OD;
                next_clk_src = clk_src[next_drive_mode];
                new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
                if (new_drive_mode == current_rtd_drive_mode)
                {
                    /* from ND -> UD */
                    next_drive_mode = DRIVE_MODE_UD;
                    next_clk_src = clk_src[next_drive_mode];
                    new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
                    switch_flag = SWITCH_DRIVE_MODE_FROM_ND_TO_UD;
                }
                else
                {
                    switch_flag = SWITCH_DRIVE_MODE_FROM_ND_TO_OD;
                }
            }
	    else if (switch_flag == SWITCH_DRIVE_MODE_FROM_OD_TO_ND)
            {
                    next_drive_mode = DRIVE_MODE_UD;
                    next_clk_src = clk_src[next_drive_mode];
                    new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
                    switch_flag = SWITCH_DRIVE_MODE_FROM_ND_TO_UD;
            }
	    else if (switch_flag == SWITCH_DRIVE_MODE_FROM_UD_TO_ND)
            {
                    next_drive_mode = DRIVE_MODE_OD;
                    next_clk_src = clk_src[next_drive_mode];
                    new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
                    switch_flag = SWITCH_DRIVE_MODE_FROM_ND_TO_OD;
            }
            break;
        case DRIVE_MODE_OD:
            /* OD -> ND */
            next_drive_mode = DRIVE_MODE_ND;
            next_clk_src = clk_src[next_drive_mode];
            new_drive_mode = BOARD_CalculateCoreClkDivider(next_clk_src, &core_clk_divider, &bus_clk_divider, &slow_clk_divider, next_drive_mode);
            switch_flag = SWITCH_DRIVE_MODE_FROM_OD_TO_ND;
            break;
        default:
            assert(false);
            break;
    }
    next_drive_mode = new_drive_mode;
    g_sysClkConfigRun.divBus = bus_clk_divider - 1;
    g_sysClkConfigRun.divSlow = slow_clk_divider - 1;
    g_sysClkConfigRun.divCore = core_clk_divider - 1;
    g_sysClkConfigRun.src = next_clk_src;

    /* switch other clock source to FRO to avoid clock glitch issue */
    if (next_drive_mode > current_rtd_drive_mode)
    {
        status = UPOWER_ChngPmicVoltage(buck_idx, voltage[next_drive_mode]);
        assert(status == 0);
        new_drive_mode = BOARD_SwitchToFROClk(next_drive_mode);
        assert(new_drive_mode == next_drive_mode);
        UPOWER_ChngRTDDomBias(next_drive_mode);
    }
    else if (next_drive_mode < current_rtd_drive_mode)
    {
        new_drive_mode = BOARD_SwitchToFROClk(next_drive_mode);
        assert(new_drive_mode == next_drive_mode);
        status = UPOWER_ChngPmicVoltage(buck_idx, voltage[next_drive_mode]);
        assert(status == 0);
        /* Update bias configuration */
        UPOWER_ChngRTDDomBias(next_drive_mode);
    }
    else
    {
        new_drive_mode = BOARD_SwitchToFROClk(next_drive_mode);
        assert(new_drive_mode == next_drive_mode);
    }

    /* switch FRO back to other clock source */
    CLOCK_SetCm33SysClkConfig(&g_sysClkConfigRun);
    SystemCoreClockUpdate();

    /*
     * The cm33 platform clock(core clock) is used as clock source of flexspi0, so reinitialize flexspi0
     * 5 - CM33 CORE/PLAT CLK
     */
    BOARD_CalculateDivider(SystemCoreClock, BOARD_NOR_FLASH_READ_MAXIMUM_FREQ, &freq_divider);
    BOARD_SetFlexspiClock(FLEXSPI0, 5U, freq_divider - 1, 0U); /* flexspi0's clock is CM33_PLATCLK / div */

    /* Note: All of IP modules that use CM33_CORECLK, CM33_BUSCLK, CM33_SLOWCLK need be reinitialized again */
    assert(BOARD_GetRtdDriveMode() == next_drive_mode);
}
