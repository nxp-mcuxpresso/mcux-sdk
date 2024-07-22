/*
 * Copyright 2023 NXP
 * All rights reserved.
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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex,
                                       pm_resc_mask_t *pSoftRescMask,
                                       pm_resc_group_t *pSysRescGroup);
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
 *  |  Module         |    Sleep     | Deep Sleep | Deep Power Down | Full Deep Power Down |
 *  | MAIN CLK        |     ON       |   ON/OFF   |      OFF        |       OFF            |
 *  | VDDCOREREG      |    HP/LP     |   HP/LP    |      OFF        |       OFF            |
 *  | PMC_REF         |    HP/LP     |   HP/LP    |      OFF        |       OFF            |
 *  | HVD_1V8         |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | POR_CORE        |    HP/LP     |   HP/LP    |      OFF        |       OFF            |
 *  | LVDCORE         |    HP/LP     |   HP/LP    |      OFF        |       OFF            |
 *  | HVDCORE         |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | SYSXTAL         |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | LPOSC           |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | SFRO            |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | FFRO            |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | SYS PLL         |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | AUDIO PLL       |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | ADC             |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | ADC TEMP        |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | ACMP            |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | PowerQuad RAM   |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | FLEXSPI RAM     |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | USB RAM         |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | USDHC0 RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | USDHC1 RAM      |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | CASPER RAM      |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | DSP CACHE       |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | DSP TCM         |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | ROM             |    ON/OFF    |   ON/OFF   |      OFF        |       OFF            |
 *  | SRAM0-7 32KB    |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | SRAM8-11 64KB   |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | SRAM12-15 128KB |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 *  | SRAM16-29 256KB |   ON/RET/OFF | ON/RET/OFF |      OFF        |       OFF            |
 */

const pm_device_option_t g_devicePMOption = {
    .states =
        {
            /* Sleep */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                        .rescMask[1U] = 0x0000000UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFEUL,
                        .rescMask[1U] = 0x3FFFFFFUL,
                    },
            },
            /* Deep Sleep */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                        .rescMask[1U] = 0x0000000UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0x3FFFFFFUL,
                    },
            },
            /* Deep Power Down */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0x3FFFFFFUL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x0UL,
                        .rescMask[1U] = 0x0UL,
                    },
            },
            /* Full Deep Power Down */
            {
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0xFFFFFFFFUL,
                        .rescMask[1U] = 0x3FFFFFFUL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x0UL,
                        .rescMask[1U] = 0x0UL,
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

/* Table of PDSLEEPCFG group number and mask for each Peripheral constraint */
static const enabled_resources_peripherals_t enResPeripherals[RESC_GROUP_PERIPHERALS_SIZE] = {
    [kResc_MAIN_CLK - RESC_GROUP_PERIPHERALS_START]      = {0, SYSCTL0_PDSLEEPCFG0_MAINCLK_SHUTOFF_MASK},
    [kResc_VDDCOREREG_HP - RESC_GROUP_PERIPHERALS_START] = {0, SYSCTL0_PDSLEEPCFG0_VDDCOREREG_LP_MASK},
    [kResc_PMCREF_HP - RESC_GROUP_PERIPHERALS_START]     = {0, SYSCTL0_PDSLEEPCFG0_PMCREF_LP_MASK},
    [kResc_HVD1V8 - RESC_GROUP_PERIPHERALS_START]        = {0, SYSCTL0_PDSLEEPCFG0_HVD1V8_PD_MASK},
    [kResc_PORCORE_HP - RESC_GROUP_PERIPHERALS_START]    = {0, SYSCTL0_PDSLEEPCFG0_PORCORE_LP_MASK},
    [kResc_LVDCORE_HP - RESC_GROUP_PERIPHERALS_START]    = {0, SYSCTL0_PDSLEEPCFG0_LVDCORE_LP_MASK},
    [kResc_HVDCORE - RESC_GROUP_PERIPHERALS_START]       = {0, SYSCTL0_PDSLEEPCFG0_HVDCORE_PD_MASK},
    [kResc_SYSXTAL - RESC_GROUP_PERIPHERALS_START]       = {0, SYSCTL0_PDSLEEPCFG0_SYSXTAL_PD_MASK},
    [kResc_LPOSC - RESC_GROUP_PERIPHERALS_START]         = {0, SYSCTL0_PDSLEEPCFG0_LPOSC_PD_MASK},
    [kResc_SFRO - RESC_GROUP_PERIPHERALS_START]          = {0, SYSCTL0_PDSLEEPCFG0_SFRO_PD_MASK},
    [kResc_FFRO - RESC_GROUP_PERIPHERALS_START]          = {0, SYSCTL0_PDSLEEPCFG0_FFRO_PD_MASK},
    [kResc_SYSPLLLDO - RESC_GROUP_PERIPHERALS_START]     = {0, SYSCTL0_PDSLEEPCFG0_SYSPLLLDO_PD_MASK},
    [kResc_SYSPLLANA - RESC_GROUP_PERIPHERALS_START]     = {0, SYSCTL0_PDSLEEPCFG0_SYSPLLANA_PD_MASK},
    [kResc_AUDIOPLLLDO - RESC_GROUP_PERIPHERALS_START]   = {0, SYSCTL0_PDSLEEPCFG0_AUDPLLLDO_PD_MASK},
    [kResc_AUDIOPLLANA - RESC_GROUP_PERIPHERALS_START]   = {0, SYSCTL0_PDSLEEPCFG0_AUDPLLANA_PD_MASK},
    [kResc_ADC_ACTIVE - RESC_GROUP_PERIPHERALS_START]    = {0, SYSCTL0_PDSLEEPCFG0_ADC_PD_MASK},
    [kResc_ADC_TEMP - RESC_GROUP_PERIPHERALS_START]      = {0, SYSCTL0_PDSLEEPCFG0_ADCTEMPSNS_PD_MASK},
    [kResc_ACMP - RESC_GROUP_PERIPHERALS_START]          = {0, SYSCTL0_PDSLEEPCFG0_ACMP_PD_MASK},

    [kResc_ROM - RESC_GROUP_PERIPHERALS_START] = {1, SYSCTL0_PDSLEEPCFG1_ROM_PD_MASK},
};

/* Table of PDSLEEPCFG1 masks for each dedicated Peripheral RAM (PRAM) constraint */
static const enabled_resources_prams_t enResPRAMs[RESC_GROUP_PRAMS_SIZE] = {
    [kResc_SRAM_PQ - RESC_GROUP_PRAMS_START]      = {SYSCTL0_PDSLEEPCFG1_PQ_SRAM_APD_MASK,
                                                     SYSCTL0_PDSLEEPCFG1_PQ_SRAM_PPD_MASK},
    [kResc_SRAM_FLEXSPI - RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_APD_MASK,
                                                     SYSCTL0_PDSLEEPCFG1_FLEXSPI_SRAM_PPD_MASK},
    [kResc_SRAM_USB -
        RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_USBHS_SRAM_APD_MASK, SYSCTL0_PDSLEEPCFG1_USBHS_SRAM_PPD_MASK},
    [kResc_SRAM_USDHC0 -
        RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_USDHC0_SRAM_APD_MASK, SYSCTL0_PDSLEEPCFG1_USDHC0_SRAM_PPD_MASK},
    [kResc_SRAM_USDHC1 -
        RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_USDHC1_SRAM_APD_MASK, SYSCTL0_PDSLEEPCFG1_USDHC1_SRAM_PPD_MASK},
    [kResc_SRAM_CASPER -
        RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_CASPER_SRAM_APD_MASK, SYSCTL0_PDSLEEPCFG1_CASPER_SRAM_PPD_MASK},
    [kResc_SRAM_DSPCACHE - RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_DSPCACHE_REGF_APD_MASK,
                                                      SYSCTL0_PDSLEEPCFG1_DSPCACHE_REGF_PPD_MASK},
    [kResc_SRAM_DSPTCM -
        RESC_GROUP_PRAMS_START] = {SYSCTL0_PDSLEEPCFG1_DSPTCM_REGF_APD_MASK, SYSCTL0_PDSLEEPCFG1_DSPTCM_REGF_PPD_MASK},
};

/* PDSLEEPCFG masks for each System SRAM resource constraint */
static const uint32_t enResSRAMs[RESC_GROUP_SRAMS_SIZE] = {
    [kResc_SRAM0_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF0_APD_MASK,
    [kResc_SRAM1_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF1_APD_MASK,
    [kResc_SRAM2_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF2_APD_MASK,
    [kResc_SRAM3_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF3_APD_MASK,
    [kResc_SRAM4_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF4_APD_MASK,
    [kResc_SRAM5_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF5_APD_MASK,
    [kResc_SRAM6_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF6_APD_MASK,
    [kResc_SRAM7_32KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF7_APD_MASK,
    [kResc_SRAM8_64KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF8_APD_MASK,
    [kResc_SRAM9_64KB - RESC_GROUP_SRAMS_START]   = SYSCTL0_PDSLEEPCFG2_SRAM_IF9_APD_MASK,
    [kResc_SRAM10_64KB - RESC_GROUP_SRAMS_START]  = SYSCTL0_PDSLEEPCFG2_SRAM_IF10_APD_MASK,
    [kResc_SRAM11_64KB - RESC_GROUP_SRAMS_START]  = SYSCTL0_PDSLEEPCFG2_SRAM_IF11_APD_MASK,
    [kResc_SRAM12_128KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF12_APD_MASK,
    [kResc_SRAM13_128KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF13_APD_MASK,
    [kResc_SRAM14_128KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF14_APD_MASK,
    [kResc_SRAM15_128KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF15_APD_MASK,
    [kResc_SRAM16_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF16_APD_MASK,
    [kResc_SRAM17_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF17_APD_MASK,
    [kResc_SRAM18_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF18_APD_MASK,
    [kResc_SRAM19_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF19_APD_MASK,
    [kResc_SRAM20_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF20_APD_MASK,
    [kResc_SRAM21_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF21_APD_MASK,
    [kResc_SRAM22_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF22_APD_MASK,
    [kResc_SRAM23_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF23_APD_MASK,
    [kResc_SRAM24_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF24_APD_MASK,
    [kResc_SRAM25_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF25_APD_MASK,
    [kResc_SRAM26_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF26_APD_MASK,
    [kResc_SRAM27_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF27_APD_MASK,
    [kResc_SRAM28_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF28_APD_MASK,
    [kResc_SRAM29_256KB - RESC_GROUP_SRAMS_START] = SYSCTL0_PDSLEEPCFG2_SRAM_IF29_APD_MASK,
};

static void PM_DEV_EnablePeripheralsDeepSleep(pm_resc_mask_t *pSoftRescMask,
                                                pm_resc_group_t *pSysRescGroup,
                                                uint32_t *enabledResources)
{
    uint32_t rescMask;
    uint32_t rescGroup;
    resc_name_t resc;
    uint32_t feature;

    /* Configure Dedicated Peripheral RAMs (PRAMs) */
    for (resc = RESC_GROUP_PRAMS_START; resc <= RESC_GROUP_PRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_PRAMS_START;

        if (rescMask && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Exclude APD & PPD bits in PDSLEEPCFG1 for each enabled PRAM */
            enabledResources[1] |= enResPRAMs[feature].apd_mask | enResPRAMs[feature].ppd_mask;
        }
        else if (rescMask && ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U))
        {
            /* Exclude APD bit in PDSLEEPCFG1 for each retained PRAM */
            enabledResources[1] |= enResPRAMs[feature].apd_mask;
        }
    }

    /* Configure System RAMs (SRAMs) */
    for (resc = RESC_GROUP_SRAMS_START; resc <= RESC_GROUP_SRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_SRAMS_START;

        if (rescMask && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Exclude APD bit in PDSLEEPCFG2 & PPD bit in PDSLEEPCFG3 */
            enabledResources[2] |= enResSRAMs[feature];
            enabledResources[3] |= enResSRAMs[feature];
        }
        else if (rescMask && ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U))
        {
            /* Exclude APD bit in PDSLEEPCFG2 */
            enabledResources[2] |= enResSRAMs[feature];
        }
    }

    /* Configure remaining peripherals with single PDSLEEPCFG bit */
    for (resc = RESC_GROUP_PERIPHERALS_START; resc <= RESC_GROUP_PERIPHERALS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_PERIPHERALS_START;

        if (rescMask && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Exclude peripheral bit in corresponding PDSLEECFG group */
            enabledResources[enResPeripherals[feature].group] |= enResPeripherals[feature].mask;
        }
    }

    /* Enable RBB */
    enabledResources[0] |= SYSCTL0_PDSLEEPCFG0_RBB_PD_MASK;
}

static void PM_DEV_DisablePeripheralsSleep(pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup)
{
    uint32_t rescMask;
    uint32_t rescGroup;
    resc_name_t resc;
    uint32_t feature;

    /* Configure Dedicated Peripheral RAMs (PRAMs) */
    for (resc = RESC_GROUP_PRAMS_START; resc <= RESC_GROUP_PRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_PRAMS_START;

        if (rescMask)
        {
            if ((rescGroup & PM_RESOURCE_FULL_ON) != 0U)
            {
                /* Clear APD and PPD bits in PDRUNCFG1 for each enabled PSRAM */
                SYSCTL0_PDRCFGCLR_REG(1) = enResPRAMs[feature].apd_mask | enResPRAMs[feature].ppd_mask;
            }
            else if ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U)
            {
                /* Clear APD bit in PDRUNCFG1 for each retained PSRAM */
                SYSCTL0_PDRCFGCLR_REG(1) = enResPRAMs[feature].apd_mask;
                /* Set   PPD bit in PDRUNCFG1 for each retained PSRAM */
                SYSCTL0_PDRCFGSET_REG(1) = enResPRAMs[feature].ppd_mask;
            }
        }
        else
        {
            /* Set APD and PPD bits in PDRUNCFG1 for each disabled PSRAM */
            SYSCTL0_PDRCFGSET_REG(1) = enResPRAMs[feature].apd_mask | enResPRAMs[feature].ppd_mask;
        }
    }

    /* Configure System RAMs (SRAMs) */
    for (resc = RESC_GROUP_SRAMS_START; resc <= RESC_GROUP_SRAMS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_SRAMS_START;

        if (rescMask)
        {
            if ((rescGroup & PM_RESOURCE_FULL_ON) != 0U)
            {
                /* Clear APD bit in PDRUNCFG2 and PPD bit in PDRUNCFG3 for each enabled SRAM */
                SYSCTL0_PDRCFGCLR_REG(2) = enResSRAMs[feature];
                SYSCTL0_PDRCFGCLR_REG(3) = enResSRAMs[feature];
            }
            else if ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U)
            {
                /* Clear APD bit in PDRUNCFG2 for each retained SRAM */
                SYSCTL0_PDRCFGCLR_REG(2) = enResSRAMs[feature];
                /* Set   PPD bit in PDRUNCFG3 for each retained SRAM */
                SYSCTL0_PDRCFGSET_REG(3) = enResSRAMs[feature];
            }
        }
        else
        {
            /* Set APD bit in PDRUNCFG2 and PPD bit in PDRUNCFG3 for each disabled SRAM */
            SYSCTL0_PDRCFGSET_REG(2) = enResSRAMs[feature];
            SYSCTL0_PDRCFGSET_REG(3) = enResSRAMs[feature];
        }
    }

    /* Configure remaining peripherals with single PDRUNCFG bit */
    for (resc = RESC_GROUP_PERIPHERALS_START; resc <= RESC_GROUP_PERIPHERALS_END; resc++)
    {
        rescMask  = PM_RESC_MASK(pSoftRescMask, resc);
        rescGroup = PM_RESC_GROUP(pSysRescGroup, resc);
        feature   = resc - RESC_GROUP_PERIPHERALS_START;

        if (rescMask && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            /* Clear peripheral bit in corresponding PDRUNCFG register */
            SYSCTL0_PDRCFGCLR_REG(enResPeripherals[feature].group) = enResPeripherals[feature].mask;
        }
        else
        {
            /* Set peripheral bit in corresponding PDRUNCFG register */
            SYSCTL0_PDRCFGSET_REG(enResPeripherals[feature].group) = enResPeripherals[feature].mask;
        }
    }

    POWER_ApplyPD();
}

static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex,
                                       pm_resc_mask_t *pSoftRescMask,
                                       pm_resc_group_t *pSysRescGroup)
{
    uint32_t enabledResources[4] = {0, 0, 0, 0}; /* SYSPDSLEEPCFG0-3 */

    assert(pSoftRescMask != NULL);
    assert(pSysRescGroup != NULL);

    switch (stateIndex)
    {
        case PM_LP_STATE_SLEEP:
            /*
             * Change SYSPDRUNCFG depending on constraints, POWER_EnablePD/Power_DisablePD then POWER_ApplyPD
             */
            PM_DEV_DisablePeripheralsSleep(pSoftRescMask, pSysRescGroup);
            break;
        case PM_LP_STATE_DEEP_SLEEP:
            /*
             * Change SYSPDSLEEPCFG depending on constraints
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
            return;
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
