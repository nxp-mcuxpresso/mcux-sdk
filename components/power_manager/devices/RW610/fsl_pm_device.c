/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pm_core.h"
#include "fsl_pm_device.h"

#include "fsl_power.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup);
static void PM_DEV_CleanExitLowPowerMode(void);

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable);
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!
 *  |          Module         |  PM0/PM1    |     PM2     |     PM3     |     PM4     |
 *  |  CAU_SOC_SLP_REF_CLK    |     ON      |     ON      |   ON/OFF    |    ON/OFF   |
 *  |  SYSOSC_FRO_PLL_CLK     |     ON      |     OFF     |     OFF     |     OFF     |
 *  |  ENET_CLK               |     ON      |   ON/OFF    |     OFF     |     OFF     |
 *  |  ENET_MEM               |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  SDIO_MEM               |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  OTP_MEM                |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  ROM_MEM                |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  FLEXSPI_MEM            |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  POWERQUAD_MEM          |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  PKC_MEM                |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  CSS_MEM                |     ON      |ON/RETENTION |     OFF     |     OFF     |
 *  |  SRAM_0K_384K           |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  SRAM_384K_448K         |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  SRAM_448K_512K         |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  SRAM_512K_640K         |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  SRAM_640K_896K         |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  SRAM_896K_1216K        |     ON      | ON/Standby  |RETENTION/OFF|     OFF     |
 *  |  AON_MEM_0K_8K          |     ON      | ON/Standby  |  RETENTION  |  RETENTION  |
 *  |  AON_MEM_8K_16K         |     ON      | ON/Standby  |  RETENTION  |RETENTION/OFF|
 *  |  GAU_ANA                |     ON      |   ON/OFF    |     OFF     |     OFF     |
 *  |  USB_ANA                |     ON      |   ON/OFF    |     OFF     |     OFF     |
 *  |  BUCK18                 |     ON      |     ON      |   ON/SLEEP  |     OFF     |
 *  |  BUCK11                 |     ON      |     ON      |   ON/SLEEP  |     OFF     |
 */
const pm_device_option_t g_devicePMOption = {
    .states =
        {
            /* PM0 */
            {
                .exitLatency = 0U,
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                    },
            },
            /* PM1 */
            {
                .exitLatency = 1U, /* 58ns plus some margin */
                .fixConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0U] = 0x00000000UL,
                    },
            },
            /* PM2 */
            {
                .exitLatency = 2000U, /* 320us plus some margin */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x00000002UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x35555FF4UL,
                    },
            },
            /* PM3 */
            {
                .exitLatency = 8000U, /* 5ms plus some margin */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0x30555FF6UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0xC0AAA001UL,
                    },
            },
            /* PM4 */
            {
                .exitLatency = 40000U, /* 33ms plus some margin */
                .fixConstraintsMask =
                    {
                        .rescMask[0] = 0xF5FFFFF6UL,
                    },
                .varConstraintsMask =
                    {
                        .rescMask[0] = 0x08000001UL,
                    },
            },
        },
    .stateCount = 5U,
    .enter      = PM_DEV_EnterLowPowerMode,
    .clean      = PM_DEV_CleanExitLowPowerMode,

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
    .manageWakeupSource = PM_DEV_ManageWakeupSource,
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */
};

/* SRAM Constraints mask */
static const uint32_t s_sramMask[] = {0x3FU, 0x40U, 0x80U, 0x300U, 0x3C00, 0x7C000U, 0x80000U, 0x100000U};

/*******************************************************************************
 * Code
 ******************************************************************************/
static void PM_DEV_GetSleepConfig(pm_resc_mask_t *pSoftRescMask,
                                 pm_resc_group_t *pSysRescGroup,
                                 power_sleep_config_t *cfg)
{
    int32_t i;
    uint32_t rescMask, rescGroup;

    /* CAU Pd control */
    rescMask  = pSoftRescMask->rescMask[0] & 1U;
    rescGroup = pSysRescGroup->groupSlice[0] & 0xFU;
    POWER_ConfigCauInSleep((rescMask == 0U) || ((rescGroup & PM_RESOURCE_FULL_ON) == 0U));
    /* PM2 Peripheral Mem Pu control */
    for (i = 4; i <= 11; i++)
    {
        rescMask  = (pSoftRescMask->rescMask[0] >> (uint32_t)i) & 1U;
        rescGroup = (pSysRescGroup->groupSlice[i / 8] >> (4U * ((uint32_t)i % 8U))) & 0xFU;
        if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            cfg->pm2MemPuCfg |= 1UL << (32U - (uint32_t)i);
        }
    }

    /* PM2 SRAM Mem Pu control */
    for (i = 12; i <= 26; i += 2)
    {
        rescMask  = (pSoftRescMask->rescMask[0] >> (uint32_t)i) & 1U;
        rescGroup = (pSysRescGroup->groupSlice[i / 8] >> (4U * ((uint32_t)i % 8U))) & 0xFU;
        if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
        {
            cfg->pm2MemPuCfg |= s_sramMask[i / 2 - 6];
        }
    }

    /* PM2 Ana Pu control */
    rescMask  = (pSoftRescMask->rescMask[0] >> 28U) & 1U;
    rescGroup = (pSysRescGroup->groupSlice[28 / 8] >> (4U * (28U % 8U))) & 0xFU;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
    {
        cfg->pm2AnaPuCfg |= (uint32_t)kPOWER_Pm2AnaPuGau | (uint32_t)kPOWER_Pm2AnaPuAnaTop;
    }
    rescMask  = (pSoftRescMask->rescMask[0] >> 29U) & 1U;
    rescGroup = (pSysRescGroup->groupSlice[29 / 8] >> (4U * (29U % 8U))) & 0xFU;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
    {
        cfg->pm2AnaPuCfg |= (uint32_t)kPOWER_Pm2AnaPuUsb | (uint32_t)kPOWER_Pm2AnaPuAnaTop;
    }

    /* PM2 clock gate */
    rescMask     = (pSoftRescMask->rescMask[0] >> 2U) & 1U;
    rescGroup    = (pSysRescGroup->groupSlice[2 / 8] >> (4U * (2U % 8U))) & 0xFU;
    cfg->clkGate = (uint32_t)kPOWER_ClkGateAll;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
    {
        cfg->clkGate &= ~((uint32_t)kPOWER_ClkGateTddrMciEnet);
    }

    /* PM3/PM4 SRAM */
    cfg->memPdCfg = 0x13FU; /* All SRAM power down in PM3, AON SRAM1 power down in PM4. */
    for (i = 13; i <= 23; i += 2)
    {
        rescMask  = (pSoftRescMask->rescMask[0] >> (uint32_t)i) & 1U;
        rescGroup = (pSysRescGroup->groupSlice[i / 8] >> (4U * ((uint32_t)i % 8U))) & 0xFU;
        if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U))
        {
            cfg->memPdCfg &= ~(1UL << (((uint32_t)i - 13U) / 2U));
        }
    }
    rescMask  = (pSoftRescMask->rescMask[0] >> 27U) & 1U;
    rescGroup = (pSysRescGroup->groupSlice[27 / 8] >> (4U * (27U % 8U))) & 0xFU;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_PARTABLE_ON1) != 0U))
    {
        cfg->memPdCfg &= ~(1UL << 8U);
    }

    /* PM3 buck config */
    rescMask  = (pSoftRescMask->rescMask[0] >> 30U) & 1U;
    rescGroup = (pSysRescGroup->groupSlice[30 / 8] >> (4U * (30U % 8U))) & 0xFU;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
    {
        cfg->pm3BuckCfg |= (uint32_t)kPOWER_Pm3Buck18;
    }
    rescMask  = (pSoftRescMask->rescMask[0] >> 31U) & 1U;
    rescGroup = (pSysRescGroup->groupSlice[31 / 8] >> (4U * (31U % 8U))) & 0xFU;
    if ((rescMask == 1U) && ((rescGroup & PM_RESOURCE_FULL_ON) != 0U))
    {
        cfg->pm3BuckCfg |= (uint32_t)kPOWER_Pm3Buck11;
    }
}

static void PM_DEV_EnterLowPowerMode(uint8_t stateIndex, pm_resc_mask_t *pSoftRescMask, pm_resc_group_t *pSysRescGroup)
{
    power_sleep_config_t slpCfg = {0U};

    assert(pSoftRescMask != NULL);
    assert(pSysRescGroup != NULL);

    switch (stateIndex)
    {
        case PM_LP_STATE_PM0:
            break;
        case PM_LP_STATE_PM1:
            POWER_SetSleepMode(stateIndex);
            __WFI();
            break;

        default:
            PM_DEV_GetSleepConfig(pSoftRescMask, pSysRescGroup, &slpCfg);
            (void)POWER_EnterPowerMode(stateIndex, &slpCfg);
            break;
    }
}

static void PM_DEV_CleanExitLowPowerMode(void)
{
    /* Do nothing. */
}

#if (defined(FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER) && FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER)
static void PM_DEV_EnableWakeupSource(IRQn_Type source, uint32_t misc)
{
    if (source == PIN0_INT_IRQn)
    {
        POWER_ConfigWakeupPin(kPOWER_WakeupPin0, misc == 0U ? kPOWER_WakeupEdgeLow : kPOWER_WakeupEdgeHigh);
        NVIC_ClearPendingIRQ(PIN0_INT_IRQn);
    }
    else if (source == PIN1_INT_IRQn)
    {
        POWER_ConfigWakeupPin(kPOWER_WakeupPin1, misc == 0U ? kPOWER_WakeupEdgeLow : kPOWER_WakeupEdgeHigh);
        NVIC_ClearPendingIRQ(PIN1_INT_IRQn);
    }
    else
    {
        /* Do nothing */
    }
    (void)EnableIRQ(source);
    POWER_ClearWakeupStatus(source);
    POWER_EnableWakeup(source);
}

static void PM_DEV_DisableWakeupSource(IRQn_Type source, uint32_t misc)
{
    if (source == PIN0_INT_IRQn)
    {
        POWER_ConfigWakeupPin(kPOWER_WakeupPin0, misc == 0U ? kPOWER_WakeupEdgeHigh : kPOWER_WakeupEdgeLow);
        NVIC_ClearPendingIRQ(PIN0_INT_IRQn);
    }
    else if (source == PIN1_INT_IRQn)
    {
        POWER_ConfigWakeupPin(kPOWER_WakeupPin1, misc == 0U ? kPOWER_WakeupEdgeHigh : kPOWER_WakeupEdgeLow);
        NVIC_ClearPendingIRQ(PIN1_INT_IRQn);
    }
    else
    {
        /* Do nothing */
    }
    (void)DisableIRQ(source);
    POWER_ClearWakeupStatus(source);
    POWER_DisableWakeup(source);
}

static status_t PM_DEV_ManageWakeupSource(pm_wakeup_source_t *ws, bool enable)
{
    uint32_t irqn;
    uint32_t misc;

    assert(ws != NULL);
    PM_DECODE_WAKEUP_SOURCE_ID(ws->wsId);

    if (enable)
    {
        PM_DEV_EnableWakeupSource((IRQn_Type)irqn, misc);
    }
    else
    {
        PM_DEV_DisableWakeupSource((IRQn_Type)irqn, misc);
    }
    return kStatus_Success;
}
#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */
