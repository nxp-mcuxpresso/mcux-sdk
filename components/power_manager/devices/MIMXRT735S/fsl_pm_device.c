/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pm_core.h"
#include "fsl_pm_device.h"

#include "fsl_clock.h"
#include "fsl_power.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
#if defined(PMC0)
#define PMC_PDRCFG_REG(x)    (*((volatile uint32_t *)((uint32_t)(&(PMC0->PDRUNCFG0)) + ((uint32_t)(x) << 2U))))
#define SLEEPCON_RCFGSET_REG (SLEEPCON0->RUNCFG_SET)
#define SLEEPCON_RCFGCLR_REG (SLEEPCON0->RUNCFG_CLR)
#else
#define PMC_PDRCFG_REG(x)    (*((volatile uint32_t *)((uint32_t)(&(PMC1->PDRUNCFG0)) + ((uint32_t)(x) << 2U))))
#define SLEEPCON_RCFGSET_REG (SLEEPCON1->RUNCFG_SET)
#define SLEEPCON_RCFGCLR_REG (SLEEPCON1->RUNCFG_CLR)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup);
static void PM_DEV_CleanExitLowPowerMode(void);
static void PM_DEV_EnablePeripheralsDeepSleep(pm_resc_mask_t *pSoftRescMask,
                                              pm_resc_group_t *pSysRescGroup,
                                              uint32_t *enabledResources);
static void PM_DEV_DisablePeripheralsSleep(pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup);

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable);
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!
 *  |  Module         |    Sleep     | Deep Sleep |    Full DSR   | Deep Power Down | Full Deep Power Down |
 *  | COMP_MAINCLK    |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | SENSEP_MAINCLK  |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | SENSES_MAINCLK  |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | RAM0CLK         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | RAM1CLK         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | COMN_MAINCLK    |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | MEDIA_MAINCLK   |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | XTAL            |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | FRO0            |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | FRO1            |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | FRO2            |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | LPOSC           |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | MAIN PLL        |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | AUDIO PLL       |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | ADC0            |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | FRO0_EN         |    EN/GATE   |   EN/GATE  |    EN/GATE    |      OFF        |       OFF            |
 *  | FRO2_EN         |    EN/GATE   |   EN/GATE  |    EN/GATE    |      OFF        |       OFF            |
 *  | V2NMED          |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | VNCOM           |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | V2DSP           |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | V2MIPI          |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | DCDC_HP         |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | PMC_TEMP        |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | PMCREF_HP       |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | HVD1V8          |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | PORVDD1_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | LVDVDD1_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | HVDVDD1         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | AGDET1          |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | PORVDD2_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | LVDVDD2_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | HVDVDD2         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | AGDET2          |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | PORVDDN_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | LVDVDDN_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | HVDVDDN         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | OTP             |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | ROM             |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | PORVDDN_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | LVDVDDN_HP      |    HP/LP     |   HP/LP    |      OFF      |      OFF        |       OFF            |
 *  | HVDVDDN         |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | OTP             |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | ROM             |    ON/OFF    |   ON/OFF   |      OFF      |      OFF        |       OFF            |
 *  | SRAM0-29        |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 *  | USDHC0-1 RAM    |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 *  | USB0-1 RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | JPEGDEC RAM     |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | PNGDEC RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | MIPI-DSI RAM    |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 *  | GPU RAM         |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | DMA2-3 RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | DMA0-1 RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | CPU0 code cache |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | CPU0 data cache |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | HiFi4 ICache    |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | HiFi4 DCache    |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | HiFi4 ITCM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | HiFi4 DTCM      |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | EZHV RAM        |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | NPU             |   ON/RET/OFF | ON/RET/OFF |      OFF      |      OFF        |       OFF            |
 *  | XSPI0-2         |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 *  | LCDIF RAM       |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 *  | OCOTP RAM       |   ON/RET/OFF | ON/RET/OFF |    RET/OFF    |      OFF        |       OFF            |
 */

const pm_device_option_t g_devicePMOption = {
    .states =
        {
            /* Sleep */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                        .rescMask[1U] = 0x00000000UL,
                        .rescMask[2U] = 0x0UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0xFFFFFFFFUL,
                        .rescMask[2U] = 0xFFFFFFFFUL,
                    },
            },
            /* Deep Sleep */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                        .rescMask[1U] = 0x00000000UL,
                        .rescMask[2U] = 0x0UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0xFFFFFFFFUL,
                        .rescMask[2U] = 0xFFFFFFFFUL,
                    },
            },
            /* DSR */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                        .rescMask[1U] = 0x00000000UL,
                        .rescMask[2U] = 0x0UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0xFFFFFFFFUL,
                        .rescMask[2U] = 0xFFFFFFFFUL,
                    },
            },
            /* Deep Power Down */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0xFFFFFFFFUL,
                        .rescMask[2U] = 0xFFFFFFFFUL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x0UL,
                        .rescMask[1U] = 0x0UL,
                        .rescMask[2U] = 0x0UL,
                    },
            },
            /* Full Deep Power Down */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0xFFFFFFFFUL,
                        .rescMask[2U] = 0xFFFFFFFFUL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x0UL,
                        .rescMask[1U] = 0x0UL,
                        .rescMask[2U] = 0x0UL,
                    },
            },
        },
    .stateCount = PM_LP_STATE_COUNT,
    .enter      = PM_DEV_EnterLowPowerMode,
    .clean      = PM_DEV_CleanExitLowPowerMode,

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    .manageWakeupSource = PM_DEV_ManageWakeupSource,
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */
};

/* PDSLEEPCFG masks for each System SRAM resource constraint */
static const enabled_resources_t enResSRAMs[RESC_GROUP_SRAMS_SIZE] = {
    [kResc_SRAM0_32KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM0_MASK},
    [kResc_SRAM1_32KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM1_MASK},
    [kResc_SRAM2_32KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM2_MASK},
    [kResc_SRAM3_32KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM3_MASK},
    [kResc_SRAM4_64KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM4_MASK},
    [kResc_SRAM5_64KB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM5_MASK},
    [kResc_SRAM6_128KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM6_MASK},
    [kResc_SRAM7_128KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM7_MASK},
    [kResc_SRAM8_256KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM8_MASK},
    [kResc_SRAM9_256KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM9_MASK},
    [kResc_SRAM10_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM10_MASK},
    [kResc_SRAM11_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM11_MASK},
    [kResc_SRAM12_1MB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM12_MASK},
    [kResc_SRAM13_1MB - RESC_GROUP_SRAMS_START]   = {3U, PMC_PDSLEEPCFG2_SRAM13_MASK},
    [kResc_SRAM14_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM14_MASK},
    [kResc_SRAM15_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM15_MASK},
    [kResc_SRAM16_256KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM16_MASK},
    [kResc_SRAM17_256KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM17_MASK},
    [kResc_SRAM18_32KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM18_MASK},
    [kResc_SRAM19_32KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM19_MASK},
    [kResc_SRAM20_32KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM20_MASK},
    [kResc_SRAM21_32KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM21_MASK},
    [kResc_SRAM22_64KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM22_MASK},
    [kResc_SRAM23_64KB - RESC_GROUP_SRAMS_START]  = {3U, PMC_PDSLEEPCFG2_SRAM23_MASK},
    [kResc_SRAM24_128KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM24_MASK},
    [kResc_SRAM25_128KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM25_MASK},
    [kResc_SRAM26_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM26_MASK},
    [kResc_SRAM27_512KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM27_MASK},
    [kResc_SRAM28_256KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM28_MASK},
    [kResc_SRAM29_256KB - RESC_GROUP_SRAMS_START] = {3U, PMC_PDSLEEPCFG2_SRAM29_MASK},

    [kResc_SRAM_USDHC0 - RESC_GROUP_SRAMS_START]      = {5U, PMC_PDSLEEPCFG4_SDHC0_SRAM_MASK},
    [kResc_SRAM_USDHC1 - RESC_GROUP_SRAMS_START]      = {5U, PMC_PDSLEEPCFG4_SDHC1_SRAM_MASK},
    [kResc_SRAM_USB0 - RESC_GROUP_SRAMS_START]        = {5U, PMC_PDSLEEPCFG4_USB0_SRAM_MASK},
    [kResc_SRAM_USB1 - RESC_GROUP_SRAMS_START]        = {5U, PMC_PDSLEEPCFG4_USB1_SRAM_MASK},
    [kResc_SRAM_JPEGDEC - RESC_GROUP_SRAMS_START]     = {5U, PMC_PDSLEEPCFG4_JPEG_MASK},
    [kResc_SRAM_PNGDEC - RESC_GROUP_SRAMS_START]      = {5U, PMC_PDSLEEPCFG4_PNG_MASK},
    [kResc_SRAM_MIPI - RESC_GROUP_SRAMS_START]        = {5U, PMC_PDSLEEPCFG4_MIPI_MASK},
    [kResc_SRAM_GPU - RESC_GROUP_SRAMS_START]         = {5U, PMC_PDSLEEPCFG4_GPU_MASK},
    [kResc_SRAM_DMA23 - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_DMA2_3_MASK},
    [kResc_SRAM_DMA01PE - RESC_GROUP_SRAMS_START]     = {5U, PMC_PDSLEEPCFG4_DMA0_1_P_E_MASK},
    [kResc_SRAM_CPU0_ICACHE - RESC_GROUP_SRAMS_START] = {5U, PMC_PDSLEEPCFG4_CPU0_CCACHE_MASK},
    [kResc_SRAM_CPU0_DCACHE - RESC_GROUP_SRAMS_START] = {5U, PMC_PDSLEEPCFG4_CPU0_SCACHE_MASK},
    [kResc_SRAM_DSP_ICACHE - RESC_GROUP_SRAMS_START]  = {5U, PMC_PDSLEEPCFG4_DSP_ICACHE_MASK},
    [kResc_SRAM_DSP_DCACHE - RESC_GROUP_SRAMS_START]  = {5U, PMC_PDSLEEPCFG4_DSP_DCACHE_MASK},
    [kResc_SRAM_DSP_ITCM - RESC_GROUP_SRAMS_START]    = {5U, PMC_PDSLEEPCFG4_DSP_ITCM_MASK},
    [kResc_SRAM_DSP_DTCM - RESC_GROUP_SRAMS_START]    = {5U, PMC_PDSLEEPCFG4_DSP_DTCM_MASK},
    [kResc_SRAM_EZHV - RESC_GROUP_SRAMS_START]        = {5U, PMC_PDSLEEPCFG4_EZH_TCM_MASK},
    [kResc_SRAM_NPU - RESC_GROUP_SRAMS_START]         = {5U, PMC_PDSLEEPCFG4_NPU_MASK},
    [kResc_SRAM_XSPI0 - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_XSPI0_MASK},
    [kResc_SRAM_XSPI1 - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_XSPI1_MASK},
    [kResc_SRAM_XSPI2 - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_XSPI2_MASK},
    [kResc_SRAM_LCDIF - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_LCD_MASK},
    [kResc_SRAM_OCOTP - RESC_GROUP_SRAMS_START]       = {5U, PMC_PDSLEEPCFG4_OCOTP_MASK},
};

/* Table of PDSLEEPCFG group number and mask for each Peripheral constraint */
static const enabled_resources_t enResPeripherals[RESC_GROUP_PERIPHERALS_SIZE] = {
#if defined(PMC0)
    [kResc_COMP_MAINCLK - RESC_GROUP_PERIPHERALS_START]   = {0U, SLEEPCON0_SLEEPCFG_COMP_MAINCLK_SHUTOFF_MASK},
    [kResc_SENSEP_MAINCLK - RESC_GROUP_PERIPHERALS_START] = {0U, SLEEPCON0_SLEEPCFG_SENSEP_MAINCLK_SHUTOFF_MASK},
    [kResc_SENSES_MAINCLK - RESC_GROUP_PERIPHERALS_START] = {0U, SLEEPCON0_SLEEPCFG_SENSES_MAINCLK_SHUTOFF_MASK},
    [kResc_RAM0CLK - RESC_GROUP_PERIPHERALS_START]        = {0U, SLEEPCON0_SLEEPCFG_RAM0_CLK_SHUTOFF_MASK},
    [kResc_RAM1CLK - RESC_GROUP_PERIPHERALS_START]        = {0U, SLEEPCON0_SLEEPCFG_RAM1_CLK_SHUTOFF_MASK},
    [kResc_COMN_MAINCLK - RESC_GROUP_PERIPHERALS_START]   = {0U, SLEEPCON0_SLEEPCFG_COMN_MAINCLK_SHUTOFF_MASK},
    [kResc_MEDIA_MAINCLK - RESC_GROUP_PERIPHERALS_START]  = {0U, SLEEPCON0_SLEEPCFG_MEDIA_MAINCLK_SHUTOFF_MASK},
    [kResc_XTAL - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON0_SLEEPCFG_XTAL_PD_MASK},
    [kResc_FRO0 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON0_SLEEPCFG_FRO0_PD_MASK},
    [kResc_FRO1 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON0_SLEEPCFG_FRO1_PD_MASK},
    [kResc_FRO2 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON0_SLEEPCFG_FRO2_PD_MASK},
    [kResc_LPOSC - RESC_GROUP_PERIPHERALS_START]          = {0U, SLEEPCON0_SLEEPCFG_LPOSC_PD_MASK},
    [kResc_PLLANA - RESC_GROUP_PERIPHERALS_START]         = {0U, SLEEPCON0_SLEEPCFG_PLLANA_PD_MASK},
    [kResc_PLLLDO - RESC_GROUP_PERIPHERALS_START]         = {0U, SLEEPCON0_SLEEPCFG_PLLLDO_PD_MASK},
    [kResc_AUDPLLANA - RESC_GROUP_PERIPHERALS_START]      = {0U, SLEEPCON0_SLEEPCFG_AUDPLLANA_PD_MASK},
    [kResc_ADC0 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON0_SLEEPCFG_ADC0_PD_MASK},
#else
    [kResc_SENSEP_MAINCLK - RESC_GROUP_PERIPHERALS_START] = {0U, SLEEPCON1_SLEEPCFG_SENSEP_MAINCLK_SHUTOFF_MASK},
    [kResc_SENSES_MAINCLK - RESC_GROUP_PERIPHERALS_START] = {0U, SLEEPCON1_SLEEPCFG_SENSES_MAINCLK_SHUTOFF_MASK},
    [kResc_RAM0CLK - RESC_GROUP_PERIPHERALS_START]        = {0U, SLEEPCON1_SLEEPCFG_RAM0_CLK_SHUTOFF_MASK},
    [kResc_RAM1CLK - RESC_GROUP_PERIPHERALS_START]        = {0U, SLEEPCON1_SLEEPCFG_RAM1_CLK_SHUTOFF_MASK},
    [kResc_COMN_MAINCLK - RESC_GROUP_PERIPHERALS_START]   = {0U, SLEEPCON1_SLEEPCFG_COMN_MAINCLK_SHUTOFF_MASK},
    [kResc_MEDIA_MAINCLK - RESC_GROUP_PERIPHERALS_START]  = {0U, SLEEPCON1_SLEEPCFG_MEDIA_MAINCLK_SHUTOFF_MASK},
    [kResc_XTAL - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON1_SLEEPCFG_XTAL_PD_MASK},
    [kResc_FRO2 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON1_SLEEPCFG_FRO2_PD_MASK},
    [kResc_LPOSC - RESC_GROUP_PERIPHERALS_START]          = {0U, SLEEPCON1_SLEEPCFG_LPOSC_PD_MASK},
    [kResc_PLLANA - RESC_GROUP_PERIPHERALS_START]         = {0U, SLEEPCON1_SLEEPCFG_PLLANA_PD_MASK},
    [kResc_PLLLDO - RESC_GROUP_PERIPHERALS_START]         = {0U, SLEEPCON1_SLEEPCFG_PLLLDO_PD_MASK},
    [kResc_AUDPLLANA - RESC_GROUP_PERIPHERALS_START]      = {0U, SLEEPCON1_SLEEPCFG_AUDPLLANA_PD_MASK},
    [kResc_ADC0 - RESC_GROUP_PERIPHERALS_START]           = {0U, SLEEPCON1_SLEEPCFG_ADC0_PD_MASK},
#endif

    [kResc_V2NMED - RESC_GROUP_PERIPHERALS_START]  = {1U, PMC_PDSLEEPCFG0_V2NMED_DSR_MASK},
    [kResc_VNCOM - RESC_GROUP_PERIPHERALS_START]   = {1U, PMC_PDSLEEPCFG0_VNCOM_DSR_MASK},
    [kResc_V2DSP - RESC_GROUP_PERIPHERALS_START]   = {1U, PMC_PDSLEEPCFG0_V2DSP_PD_MASK},
    [kResc_V2MIPI - RESC_GROUP_PERIPHERALS_START]  = {1U, PMC_PDSLEEPCFG0_V2MIPI_PD_MASK},
    [kResc_DCDC_HP - RESC_GROUP_PERIPHERALS_START] = {1U, PMC_PDSLEEPCFG0_DCDC_LP_MASK},

    [kResc_PMC_TEMP - RESC_GROUP_PERIPHERALS_START]   = {2U, PMC_PDSLEEPCFG1_TEMP_PD_MASK},
    [kResc_PMCREF_HP - RESC_GROUP_PERIPHERALS_START]  = {2U, PMC_PDSLEEPCFG1_PMCREF_LP_MASK},
    [kResc_HVD1V8 - RESC_GROUP_PERIPHERALS_START]     = {2U, PMC_PDSLEEPCFG1_HVD1V8_PD_MASK},
    [kResc_PORVDD1_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_POR1_LP_MASK},
    [kResc_LVDVDD1_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_LVD1_LP_MASK},
    [kResc_HVDVDD1 - RESC_GROUP_PERIPHERALS_START]    = {2U, PMC_PDSLEEPCFG1_HVD1_PD_MASK},
    [kResc_AGDET1 - RESC_GROUP_PERIPHERALS_START]     = {2U, PMC_PDSLEEPCFG1_AGDET1_PD_MASK},
    [kResc_PORVDD2_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_POR2_LP_MASK},
    [kResc_LVDVDD2_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_LVD2_LP_MASK},
    [kResc_HVDVDD2 - RESC_GROUP_PERIPHERALS_START]    = {2U, PMC_PDSLEEPCFG1_HVD2_PD_MASK},
    [kResc_AGDET2 - RESC_GROUP_PERIPHERALS_START]     = {2U, PMC_PDSLEEPCFG1_AGDET2_PD_MASK},
    [kResc_PORVDDN_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_PORN_LP_MASK},
    [kResc_LVDVDDN_HP - RESC_GROUP_PERIPHERALS_START] = {2U, PMC_PDSLEEPCFG1_LVDN_LP_MASK},
    [kResc_HVDVDDN - RESC_GROUP_PERIPHERALS_START]    = {2U, PMC_PDSLEEPCFG1_HVDN_PD_MASK},
    [kResc_OTP - RESC_GROUP_PERIPHERALS_START]        = {2U, PMC_PDSLEEPCFG1_OTP_PD_MASK},
    [kResc_ROM - RESC_GROUP_PERIPHERALS_START]        = {2U, PMC_PDSLEEPCFG1_ROM_PD_MASK},
};

/*******************************************************************************
 * Code
 ******************************************************************************/

static void PM_DEV_EnablePeripheralsDeepSleep(pm_resc_mask_t *pSoftRescMask,
                                              pm_resc_group_t *pSysRescGroup,
                                              uint32_t *enabledResources)
{
    uint32_t rescMask;
    uint32_t rescGroup;
    resc_name_t resc;
    uint32_t feature;

    /* Configure System RAMs */
    for (resc = RESC_GROUP_SRAMS_START; resc <= RESC_GROUP_SRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = (uint32_t)resc - (uint32_t)RESC_GROUP_SRAMS_START;

        if ((rescMask != 0U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Exclude APD & PPD bits in PDSLEEPCFG for each enabled SRAM */
            enabledResources[enResSRAMs[feature].group] |= enResSRAMs[feature].mask;
            enabledResources[enResSRAMs[feature].group + 1UL] |= enResSRAMs[feature].mask;
        }
        else if ((rescMask != 0U) && ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U))
        {
            /* Exclude APD bit in PDSLEEPCFG2/4 for each retained SRAM */
            enabledResources[enResSRAMs[feature].group] |= enResSRAMs[feature].mask;
        }
        else
        {
            /* Intentional empty. */
        }
    }

    /* Configure remaining peripherals */
    for (resc = RESC_GROUP_PERIPHERALS_START; resc <= RESC_GROUP_PERIPHERALS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = (uint32_t)resc - (uint32_t)RESC_GROUP_PERIPHERALS_START;

        if ((rescMask != 0U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Exclude peripheral bit in corresponding PDSLEECFG group */
            enabledResources[enResPeripherals[feature].group] |= enResPeripherals[feature].mask;
        }
    }
}

static void PM_DEV_DisablePeripheralsSleep(pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup)
{
    uint32_t rescMask;
    uint32_t rescGroup;
    resc_name_t resc;
    uint32_t feature;

    /* Configure System RAMs (SRAMs) */
    for (resc = RESC_GROUP_SRAMS_START; resc <= RESC_GROUP_SRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = (uint32_t)resc - (uint32_t)RESC_GROUP_SRAMS_START;

        if (rescMask != 0U)
        {
            if ((rescGroup & PM_RESOURCE_FULL_ON) != 0U)
            {
                /* Clear APD bit in PDRUNCFG and PPD bit for each enabled SRAM */
                PMC_PDRCFG_REG(enResSRAMs[feature].group - 1UL) &= ~enResSRAMs[feature].mask;
                PMC_PDRCFG_REG(enResSRAMs[feature].group) &= ~enResSRAMs[feature].mask;
            }
            else if ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U)
            {
                /* Clear APD bit in PDRUNCFG for each retained SRAM */
                PMC_PDRCFG_REG(enResSRAMs[feature].group - 1UL) &= ~enResSRAMs[feature].mask;
                /* Set PPD bit in PDRUNCFG for each retained SRAM */
                PMC_PDRCFG_REG(enResSRAMs[feature].group) |= enResSRAMs[feature].mask;
            }
            else
            {
                /* Intentional empty. */
            }
        }
        else
        {
            /* Set APD bit and PPD bit in PDRUNCFG for each disabled SRAM */
            PMC_PDRCFG_REG(enResSRAMs[feature].group - 1UL) |= enResSRAMs[feature].mask;
            PMC_PDRCFG_REG(enResSRAMs[feature].group) |= enResSRAMs[feature].mask;
        }
    }

    /* Configure remaining peripherals with single PDRUNCFG bit */
    for (resc = RESC_GROUP_PERIPHERALS_START; resc <= RESC_GROUP_PERIPHERALS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = (uint32_t)resc - (uint32_t)RESC_GROUP_PERIPHERALS_START;

        if ((rescMask != 0U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            if (enResPeripherals[feature].group == 0U)
            {
                SLEEPCON_RCFGCLR_REG = enResPeripherals[feature].mask;
            }
            else
            {
                /* Clear peripheral bit in corresponding PDRUNCFG register */
                PMC_PDRCFG_REG(enResPeripherals[feature].group - 1UL) &= ~enResPeripherals[feature].mask;
            }
        }
        else
        {
            /* Set peripheral bit in corresponding PDRUNCFG register */
            if (enResPeripherals[feature].group == 0U)
            {
                SLEEPCON_RCFGSET_REG = enResPeripherals[feature].mask;
            }
            else
            {
                /* Clear peripheral bit in corresponding PDRUNCFG register */
                PMC_PDRCFG_REG(enResPeripherals[feature].group - 1UL) |= enResPeripherals[feature].mask;
            }
        }
    }

    POWER_ApplyPD();
}

static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup)
{
    uint32_t enabledResources[7] = {0U, 0U, 0U, 0U, 0U, 0U, 0U};

    assert(pSoftRescMask != NULL);
    assert(pSysRescGroup != NULL);

    switch (stateIndex)
    {
        case PM_LP_STATE_SLEEP:
            /*
             * Change PDRUNCFG depending on constraints, POWER_EnablePD then POWER_ApplyPD
             */
            PM_DEV_DisablePeripheralsSleep(pSoftRescMask, pSysRescGroup);
            break;
        case PM_LP_STATE_DEEP_SLEEP:
        case PM_LP_STATE_DSR:
            /*
             * Change PDSLEEPCFG depending on constraints
             */
            PM_DEV_EnablePeripheralsDeepSleep(pSoftRescMask, pSysRescGroup, enabledResources);
            break;
        case PM_LP_STATE_DEEP_POWER_DOWN:
            /*
             * Do nothing
             */
            break;
        case PM_LP_STATE_FULL_DEEP_POWER_DOWN:
            /*
             * Do nothing
             */
            break;
        default:
            /* Should not goes here. */
            break;
    }
    POWER_EnterPowerMode((power_mode_cfg_t)stateIndex, enabledResources);
}

static void PM_DEV_CleanExitLowPowerMode(void)
{
    /* Do nothing. */
}

static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable)
{
    uint32_t irqn;
    uint32_t misc;

    (void)(misc);

    assert(ws != NULL);
    PM_DECODE_WAKEUP_SOURCE_ID(ws->wsId);

    if (enable)
    {
        EnableDeepSleepIRQ((IRQn_Type)irqn);
    }
    else
    {
        DisableDeepSleepIRQ((IRQn_Type)irqn);
    }
    return kStatus_Success;
}
