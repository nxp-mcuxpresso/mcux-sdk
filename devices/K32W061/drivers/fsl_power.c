/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_power.h"
#include "fsl_debug_console.h"
#include "fsl_iocon.h"

#include "rom_mpu.h"
#include "rom_pmc.h"
#include "rom_api.h"
#include "rom_lowpower.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.power_no_lib"
#endif

#ifndef FORCE_LDO_MEM_0V9_DBG
/* Only to be activated for backward compatibility on old
 * parts where the ATE did not set the LDO MEM 0V9 support
 * information yet
 * */
#define FORCE_LDO_MEM_0V9_DBG 0
#endif

#define POWER_LIB_VERSION 6042018

/* Do not disable the DC bus when going to power modes */
//#define POWER_DCBUS_NOT_DISABLED

//#define DUMP_CONFIG
//#define TRACE_ERR
//#define TRACE_VRB
//#define DISPLAY_ACTIVE_VOLTAGE

/* Force BODMEM enable in power down mode for test : 1uA power consumption increase */
//#define POWER_FORCE_BODMEM_IN_PD

/* On ES2, use directly the safe voltage in deep sleep provided by Patrick */
/* on ES2 powerdown1/2/3/4 , only BANK7 is maintained in retention */
#define POWER_DOWN_WARM_4K

#if defined(DUMP_CONFIG) || defined(TRACE_ERR) || defined(TRACE_VRB)
#define POWER_CONSOLE_DEINIT
#endif

/*******************************************************************************
 * Macros/Constants
 *******************************************************************************/

#if 1                         /* Cope with LDO CORE @ 1.0v in Active and LDO MEM @ 0.9 in power down */
#define POWER_BODMEM_TRIG 0x4 /* 0.80V  Considering LDOMEM = 0.9v */
#define POWER_BODMEM_HYST 0x1 /* 0.050V */

#define POWER_BODCORE_TRIG 0x6 /* 0.90V   Considering LDOCORE = 1.0v */
#define POWER_BODCORE_HYST 0x1 /* 0.050V */
#else                          // safest setting for LDO CORE @ 1.1v and LDO MEM @ 1.0v
#define POWER_BODMEM_TRIG 0x6  /* 0.90V - 0.925V +/- 3%   Considering LDOMEM = 1.9v */
#define POWER_BODMEM_HYST 0x0  /* 0.025V */

#define POWER_BODCORE_TRIG 0x7 /* 0.95V - 0.975V +/- 3%   Considering LDOCORE = 1.1v */
#define POWER_BODCORE_HYST 0x0 /* 0.025V */
#endif

#define BODVBAT_LVL_DEFAULT POWER_BOD_LVL_1_75V
#define BODVBAT_HYST_DEFAULT POWER_BOD_HYST_100MV

#define POWER_LDO_TRIM_UNDEFINED 0x7F

/* **********************   END OF POWER MODE DEFINITIONS   **************************************************/

#define VOLTAGE(Vpmu, Vpmuboost, Vmem, Vmemboost, Vcore, Vpmuboostenable, Vflashcore)                                  \
    (((Vpmu << LOWPOWER_VOLTAGE_LDO_PMU_INDEX) & LOWPOWER_VOLTAGE_LDO_PMU_MASK) |                                      \
     ((Vpmuboost << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_INDEX) & LOWPOWER_VOLTAGE_LDO_PMU_BOOST_MASK) |                     \
     ((Vpmuboostenable << LOWPOWER_VOLTAGE_LDO_PMU_BOOST_ENABLE_INDEX) & LOWPOWER_VOLTAGE_LDO_PMU_BOOST_ENABLE_MASK) | \
     ((Vmem << LOWPOWER_VOLTAGE_LDO_MEM_INDEX) & LOWPOWER_VOLTAGE_LDO_MEM_MASK) |                                      \
     ((Vmemboost << LOWPOWER_VOLTAGE_LDO_MEM_BOOST_INDEX) & LOWPOWER_VOLTAGE_LDO_MEM_BOOST_MASK) |                     \
     ((Vcore << LOWPOWER_VOLTAGE_LDO_CORE_INDEX) & LOWPOWER_VOLTAGE_LDO_CORE_MASK) |                                   \
     ((Vflashcore << LOWPOWER_VOLTAGE_LDO_FLASH_CORE_INDEX) & LOWPOWER_VOLTAGE_LDO_FLASH_CORE_MASK))

/*
 * Recommended Voltage settings
 */
#define VOLTAGE_PMU_DOWN 0x5      /* 0.8V  */
#define VOLTAGE_PMUBOOST_DOWN 0x3 /* 0.75V */

#define VOLTAGE_MEM_DOWN_0_9V 0x9       /* 0.9V  */
#define VOLTAGE_MEM_DOWN_0_96V 0xA      /* 0.96V  */
#define VOLTAGE_MEM_DOWN_1_0V 0xE       /* 1V    */
#define VOLTAGE_MEMBOOST_DOWN_0_85V 0x7 /* 0.85V */
#define VOLTAGE_MEMBOOST_DOWN_0_9V  0x9 /* 0.9V */
#define VOLTAGE_MEMBOOST_DOWN_0_96V 0xA /* 0.96V */

#define VOLTAGE_PMU_DEEP_SLEEP 0xA       /* 0.96V */
#define VOLTAGE_PMUBOOST_DEEP_SLEEP 0x9  /* 0.9V  */
#define VOLTAGE_MEM_DEEP_SLEEP 0x18      /* 1.1V  */
#define VOLTAGE_MEMBOOST_DEEP_SLEEP 0x13 /* 1.05V */
#define VOLTAGE_CORE_DEEP_SLEEP 0x2      /* 0.95V */
#define VOLTAGE_FLASH_CORE_DEEP_SLEEP 2  /* 0.95V */

#define VOLTAGE_PMU_DEEP_DOWN 0x5      /* 0.8V  */
#define VOLTAGE_PMUBOOST_DEEP_DOWN 0x3 /* 0.75V */

#define VOLTAGE_LDO_PMU_BOOST 0

#define POWER_ULPGB_TRIM_FLASH_ADDR (uint32_t *)0x9FCD4

#define POWER_GET_ACTIVE_TRIM_VALUE(__reg) ((int8_t)((__reg & (1 << 4)) ? -(__reg & 0xF) : (__reg & 0xF)))
#define POWER_GET_PWD_TRIM_VALUE(__reg) \
    ((int8_t)(((__reg >> 5) & (1 << 4)) ? -((__reg >> 5) & 0xF) : ((__reg >> 5) & 0xF)))

#define POWER_APPLY_ACTIVE_TRIM(__voltage)                                                                          \
    ((active_trim_val != POWER_LDO_TRIM_UNDEFINED) ? (MIN(0x1E, MAX(((int8_t)__voltage + active_trim_val), 0xA))) : \
                                                     (__voltage))
#define POWER_APPLY_PWD_TRIM(__voltage)                                                                         \
    ((pwd_trim_val != POWER_LDO_TRIM_UNDEFINED) ? (MIN(0x9, MAX(((int8_t)__voltage + pwd_trim_val), 0x1))) : \
                                                     (__voltage))

#define POWER_APPLY_TRIM(__voltage) \
    ((__voltage < 0xA) ? POWER_APPLY_PWD_TRIM(__voltage) : POWER_APPLY_ACTIVE_TRIM(__voltage))

#define POWER_READ_REG32(A) *(volatile uint32_t *)(A)

/*******************************************************************************
 * Types
 ******************************************************************************/
static LPC_LOWPOWER_LDOVOLTAGE_T lowpower_ldovoltage_reset = {
    .LDOPMU             = 0x18, // 1.1V
    .LDOPMUBOOST        = 0x13, // 1.05V
    .LDOMEM             = 0x18, // 1.1V
    .LDOMEMBOOST        = 0x13, // 1.05V
    .LDOCORE            = 0x5,  // 1.1V
    .LDOFLASHNV         = 0x5,  // 1.9V
#if defined(gPWR_LdoFlashOptim) && (gPWR_LdoFlashOptim > 0)
    .LDOFLASHCORE       = 0x5,  // 1.10V
#else
    .LDOFLASHCORE       = 0x6,  // 1.15V
#endif
    .LDOADC             = 0x5,  // 1.1V
    .LDOPMUBOOST_ENABLE = 1,    // Force Boost activation on LDOPMU
};

static LPC_LOWPOWER_LDOVOLTAGE_T lowpower_ldovoltage_min = {
    .LDOPMU             = 0xE, // 1V
    .LDOPMUBOOST        = 0xA, // 0.96V
    .LDOMEM             = 0xE, // 1V
    .LDOMEMBOOST        = 0xA, // 0.96V
    .LDOCORE            = 0x3, // 1V
    .LDOFLASHNV         = 0x5, // 1.9V
#if defined(gPWR_LdoFlashOptim) && (gPWR_LdoFlashOptim == 2)
    .LDOFLASHCORE       = 0x3,  // 1V
#elif defined(gPWR_LdoFlashOptim) && (gPWR_LdoFlashOptim == 1)
    .LDOFLASHCORE       = 0x5,  // 1.1V
#else
    .LDOFLASHCORE       = 0x6,  // 1.15V
#endif
    .LDOADC             = 0x5, // 1.1V
    .LDOPMUBOOST_ENABLE = 1,   // Force Boost activation on LDOPMU
};

/* trimming value to apply to active/pwd voltage - Initialized from flash in POWER_Init() */
static int8_t active_trim_val = POWER_LDO_TRIM_UNDEFINED;
static int8_t pwd_trim_val    = POWER_LDO_TRIM_UNDEFINED;

/*******************************************************************************
 * Local prototypes
 ******************************************************************************/

#ifdef DUMP_CONFIG
static void LF_DumpConfig(LPC_LOWPOWER_T *LV_LowPowerMode);
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

static void POWER_FlexcomClocksDisable(void)
{
    CLOCK_AttachClk(kNONE_to_USART_CLK);
    CLOCK_AttachClk(kNONE_to_FRG_CLK);
    CLOCK_AttachClk(kNONE_to_I2C_CLK);
    CLOCK_AttachClk(kNONE_to_SPI_CLK);

    CLOCK_DisableClock(kCLOCK_Usart0);
    CLOCK_DisableClock(kCLOCK_I2c0);
    CLOCK_DisableClock(kCLOCK_Spi0);
}

#ifdef FOR_BOD_DEBUG
/******   BODMEM ********/
static void POWER_BodMemDisable(void)
{
    PMC->PDRUNCFG &= ~PMC_PDRUNCFG_ENA_BOD_MEM_MASK;
    PMC->BODMEM &= ~PMC_BODMEM_RESETENABLE_MASK;
}

static void POWER_BodMemSetup(void)
{
    // TODO : really needed?
    POWER_BodMemDisable();

    /* Configure BODMEM so it can be enabled before going to power down */
    PMC->BODMEM = (PMC->BODMEM & ~(PMC_BODMEM_TRIGLVL_MASK | PMC_BODMEM_HYST_MASK)) |
                  (PMC_BODMEM_TRIGLVL(POWER_BODMEM_TRIG) | PMC_BODMEM_HYST(POWER_BODMEM_HYST));

    /* Clear BODMEM interrupt */
    SYSCON->ANACTRL_INTENCLR = SYSCON_ANACTRL_INTENSET_BODMEM_MASK;

    /* Enable the BODMEM */
    PMC->PDRUNCFG |= PMC_PDRUNCFG_ENA_BOD_MEM_MASK;
}

static void POWER_BodMemEnableInt(void)
{
    /* Warning, we should wait for the LDO to set up (27us) before clearing the status and enabling the interrupts
     * (RFT1852) However, we expect this function to be called more than 27us after POWER_BodCoreConfigure() so we can
     * discard the 27us delay here */
    // CLOCK_uDelay(27);

    /* clear initial status  (RFT1891) and enable interrupt */
    SYSCON->ANACTRL_STAT     = SYSCON_ANACTRL_STAT_BODMEM_MASK;
    SYSCON->ANACTRL_INTENSET = SYSCON_ANACTRL_INTENSET_BODMEM_MASK;

    /* BODMEM Reset enable */
    PMC->BODMEM |= PMC_BODMEM_RESETENABLE_MASK;
}

/******   BODCORE ********/
static void POWER_BodCoreDisable(void)
{
    PMC->PDRUNCFG &= ~PMC_PDRUNCFG_ENA_BOD_CORE_MASK;
    PMC->BODCORE &= ~PMC_BODCORE_RESETENABLE_MASK;
}

static void POWER_BodCoreSetup(void)
{
    /* TODO : shall we disable it first? */
    POWER_BodCoreDisable();

    /* Configure BODMEM so it can be enabled before going to power down */
    PMC->BODCORE = (PMC->BODCORE & ~(PMC_BODCORE_TRIGLVL_MASK | PMC_BODCORE_HYST_MASK)) |
                   (PMC_BODCORE_TRIGLVL(POWER_BODCORE_TRIG) | PMC_BODCORE_HYST(POWER_BODCORE_TRIG));

    /* Clear BODCORE interrupt */
    SYSCON->ANACTRL_INTENCLR = SYSCON_ANACTRL_INTENSET_BODCORE_MASK;

    /* Enable the BODCORE */
    PMC->PDRUNCFG |= PMC_PDRUNCFG_ENA_BOD_CORE_MASK;
}

static void POWER_BodCoreEnableInt(void)
{
    /* Warning, we should wait for the LDO to set up (27us) before clearing the status and enabling the interrupts
     * (RFT1852) However, we expect this function to be called more than 27us after POWER_BodCoreConfigure() so we can
     * discard the 27us delay here */
    // CLOCK_uDelay(27);

    /* clear initial status  (RFT1891) and enable interrupt */
    SYSCON->ANACTRL_STAT     = SYSCON_ANACTRL_STAT_BODCORE_MASK;
    SYSCON->ANACTRL_INTENSET = SYSCON_ANACTRL_INTENSET_BODCORE_MASK;

    /* BOD IC Reset enable */
    PMC->BODCORE |= PMC_BODCORE_RESETENABLE_MASK;
}
#endif

static void POWER_UpdateTrimmingVoltageValue(void)
{
    uint32_t ulpbg_trim_flash_val;
    /* Save a bit of time is the trimming values are already retrieved */

    if ((active_trim_val == POWER_LDO_TRIM_UNDEFINED) || (pwd_trim_val == POWER_LDO_TRIM_UNDEFINED))
    {
        /* set the trimming values for active and pwd from N-2 page Flash */
        ulpbg_trim_flash_val = *POWER_ULPGB_TRIM_FLASH_ADDR;
        active_trim_val      = POWER_GET_ACTIVE_TRIM_VALUE(ulpbg_trim_flash_val);
        pwd_trim_val         = POWER_GET_PWD_TRIM_VALUE(ulpbg_trim_flash_val);
    }
#ifdef DUMP_CONFIG
    PRINTF("reg=0x%x active_trim=0x%X pwd_trim=0x%X\r\n", ulpbg_trim_flash_val, active_trim_val, pwd_trim_val);
#endif
}

static uint32_t POWER_GetIoClampConfig(void)
{
    uint32_t io_clamp = 0;

    for (int i = 0; i < 22; i++)
    {
        if ((i == 10) | (i == 11))
        {
            io_clamp |= (((IOCON->PIO[0][i] & IOCON_IO_CLAMPING_COMBO_MFIO_I2C) >> 12) << i);
        }
        else
        {
            io_clamp |= (((IOCON->PIO[0][i] & IOCON_IO_CLAMPING_NORMAL_MFIO) >> 11) << i);
        }
    }
    return io_clamp;
}

/*!
 * brief Power Library API to return the library version.
 *
 * param none
 * return version number of the power library
 */
uint32_t POWER_GetLibVersion(void)
{
    return POWER_LIB_VERSION;
}

/*!
 * brief determine cause of reset
 * return reset_cause
 */
reset_cause_t POWER_GetResetCause(void)
{
    reset_cause_t reset_cause = RESET_UNDEFINED;
    uint32_t pmc_reset        = pmc_reset_get_cause();

    if (pmc_reset & PMC_RESETCAUSE_POR_MASK)
    {
        reset_cause |= RESET_POR;
    }

    if (pmc_reset & PMC_RESETCAUSE_PADRESET_MASK)
    {
        reset_cause |= RESET_EXT_PIN;
    }

    if (pmc_reset & PMC_RESETCAUSE_BODRESET_MASK)
    {
        reset_cause |= RESET_BOR;
    }

    if (pmc_reset & PMC_RESETCAUSE_SYSTEMRESET_MASK)
    {
        reset_cause |= RESET_SYS_REQ;
    }

    if (pmc_reset & PMC_RESETCAUSE_WDTRESET_MASK)
    {
        reset_cause |= RESET_WDT;
    }

    if (pmc_reset & PMC_RESETCAUSE_WAKEUPIORESET_MASK)
    {
        reset_cause |= RESET_WAKE_DEEP_PD;
    }

    if (pmc_reset & PMC_RESETCAUSE_WAKEUPPWDNRESET_MASK)
    {
        reset_cause |= RESET_WAKE_PD;
    }

    if (pmc_reset & PMC_RESETCAUSE_SWRRESET_MASK)
    {
        reset_cause |= RESET_SW_REQ;
    }

    return reset_cause;
}

/*!
 * brief Clear cause of reset
 */
void POWER_ClearResetCause(void)
{
    pmc_reset_clear_cause(0xFFFFFFFF);
}

void POWER_DisplayActiveVoltage(void)
{
    LPC_LOWPOWER_LDOVOLTAGE_T ldo_voltage;

    Chip_LOWPOWER_GetSystemVoltages(&ldo_voltage);

    PRINTF("LDOPMU       : %d\n", (int)(ldo_voltage.LDOPMU & 0x1fUL));
    PRINTF("LDOPMUBOOST  : %d\n", (int)(ldo_voltage.LDOPMUBOOST & 0x1fUL));
    PRINTF("LDOMEM       : %d\n", (int)(ldo_voltage.LDOMEM & 0x1fUL));
    PRINTF("LDOMEMBOOST  : %d\n", (int)(ldo_voltage.LDOMEMBOOST & 0x1fUL));
    PRINTF("LDOCORE      : %d\n", (int)(ldo_voltage.LDOCORE & 0x07UL));
    PRINTF("LDOFLASHCORE : %d\n", (int)(ldo_voltage.LDOFLASHCORE & 0x07UL));
    PRINTF("LDOFLASHNV   : %d\n", (int)(ldo_voltage.LDOFLASHNV & 0x07UL));
    PRINTF("LDOADC       : %d\n", (int)(ldo_voltage.LDOADC & 0x07UL));

    PRINTF("LDOPMUBOOST_ENABLE : %d\n", ldo_voltage.LDOPMUBOOST_ENABLE);

    PRINTF("\n");
}

void POWER_ApplyActiveVoltage(const LPC_LOWPOWER_LDOVOLTAGE_T *ldo_voltage)
{
#if 0
    /* When slow CPU clock is used (2MHz for instance)
     * every cycle matters, so  optimize execution by removing the copy */
    LPC_LOWPOWER_LDOVOLTAGE_T ldo_voltage_l;

    memcpy(&ldo_voltage_l, ldo_voltage, sizeof(LPC_LOWPOWER_LDOVOLTAGE_T));

    /* Apply some trimming on LDOPMU and LDOMEM to avoid extra consumption */
    ldo_voltage_l.LDOPMU      = POWER_APPLY_TRIM(ldo_voltage->LDOPMU);
    ldo_voltage_l.LDOPMUBOOST = POWER_APPLY_TRIM(ldo_voltage->LDOPMUBOOST);

    ldo_voltage_l.LDOMEM      = POWER_APPLY_TRIM(ldo_voltage->LDOMEM);
    ldo_voltage_l.LDOMEMBOOST = POWER_APPLY_TRIM(ldo_voltage->LDOMEMBOOST);
    Chip_LOWPOWER_SetSystemVoltages(&ldo_voltage_l);
#else
    Chip_LOWPOWER_SetSystemVoltages((LPC_LOWPOWER_LDOVOLTAGE_T *) ldo_voltage);
#endif
}

void POWER_ApplyLdoActiveVoltage(pm_ldo_volt_t ldoVolt)
{
    switch (ldoVolt)
    {
        case PM_LDO_VOLT_1_0V:
            POWER_ApplyActiveVoltage(&lowpower_ldovoltage_min);

            /* expect to have 1.0v on an other bank from 1.1V */
            assert( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == 0 );
            break;

        case PM_LDO_VOLT_1_1V_DEFAULT:
        default:
            POWER_ApplyActiveVoltage(&lowpower_ldovoltage_reset);
            break;
    }
}

void POWER_ApplyLdoActiveVoltage_1V1(void)
{
    /* expecting to be on 1.0V on the voltage bank 0*/
    assert( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == 0);

    PMC->CTRL |= PMC_CTRL_SELLDOVOLTAGE_MASK;
}

void POWER_ApplyLdoActiveVoltage_1V0(void)
{
    /* expecting to be on 1.1V on the voltage bank 1*/
    assert( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == PMC_CTRL_SELLDOVOLTAGE_MASK);

    PMC->CTRL &= ~PMC_CTRL_SELLDOVOLTAGE_MASK;
}


/*!
 * brief Initialize the sdk power drivers
 *
 * Optimize the LDO voltage for power saving
 * Initialize the power domains
 * Activate the BOD
 *
 * return none
 */
void POWER_Init(void)
{
    static bool warm_start = false;
#ifdef FOR_BOD_DEBUG
    /* Enable the clock for the analog interrupt control module - required for the BOD
     * and set up BOD core and mem*/
    POWER_BodSetUp();
    /* Need to let 27us elapse before activating BOD detector  */
#endif
    if (warm_start == false)
    {
        POWER_SetTrimDefaultActiveVoltage();

        warm_start = true;
    }

    /* Voltage should be at 1.1v at this stage (bank 1) */
    assert( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == PMC_CTRL_SELLDOVOLTAGE_MASK);

#ifdef DISPLAY_ACTIVE_VOLTAGE
    POWER_DisplayActiveVoltage();
#endif

#if 0
    /* In order to avoid the 27us wait time, parallelize with caller activities */
#ifdef FOR_BOD_DEBUG
    /* This time, need to wait for LDO to be set up (27us) */
    CLOCK_uDelay(27);
    /* enable interrupt and SW reset for the BODCORE */
    POWER_BodActivate();
#endif
#endif
}

void POWER_SetTrimDefaultActiveVoltage(void)
{
    POWER_UpdateTrimmingVoltageValue();

    /* Apply some trimming on LDOPMU and LDOMEM to avoid extra consumption */
    lowpower_ldovoltage_reset.LDOPMU      = POWER_APPLY_TRIM(lowpower_ldovoltage_reset.LDOPMU);
    lowpower_ldovoltage_reset.LDOPMUBOOST = POWER_APPLY_TRIM(lowpower_ldovoltage_reset.LDOPMUBOOST);

    lowpower_ldovoltage_reset.LDOMEM      = POWER_APPLY_TRIM(lowpower_ldovoltage_reset.LDOMEM);
    lowpower_ldovoltage_reset.LDOMEMBOOST = POWER_APPLY_TRIM(lowpower_ldovoltage_reset.LDOMEMBOOST);

    /* Apply some trimming on LDOPMU and LDOMEM to avoid extra consumption */
    lowpower_ldovoltage_min.LDOPMU      = POWER_APPLY_TRIM(lowpower_ldovoltage_min.LDOPMU);
    lowpower_ldovoltage_min.LDOPMUBOOST = POWER_APPLY_TRIM(lowpower_ldovoltage_min.LDOPMUBOOST);

    lowpower_ldovoltage_min.LDOMEM      = POWER_APPLY_TRIM(lowpower_ldovoltage_min.LDOMEM);
    lowpower_ldovoltage_min.LDOMEMBOOST = POWER_APPLY_TRIM(lowpower_ldovoltage_min.LDOMEMBOOST);

    /* Always startup at 1.1V to cope with higher current load when enabling clocks */
    POWER_ApplyLdoActiveVoltage(PM_LDO_VOLT_1_1V_DEFAULT);
    if ( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == 0)
    {
        /* wrong bank, call the function twice to select bank 1 as from POR reset
             This can happen in case of different reset than POR */
        POWER_ApplyLdoActiveVoltage(PM_LDO_VOLT_1_1V_DEFAULT);
    }

    /* configuration of SELLDOVOLTAGE for 1.1v */
    assert( (PMC->CTRL & PMC_CTRL_SELLDOVOLTAGE_MASK) == PMC_CTRL_SELLDOVOLTAGE_MASK);

#ifdef DISPLAY_ACTIVE_VOLTAGE
    POWER_DisplayActiveVoltage();
#endif
}

#ifdef FOR_BOD_DEBUG
void POWER_BodSetUp(void)
{
    /* Enable the clock for the analog interrupt control module - required for the BOD */
    CLOCK_EnableClock(kCLOCK_AnaInt);

    POWER_BodCoreSetup();
    POWER_BodMemSetup();
}

void POWER_BodActivate(void)
{
    /* enable interrupt and SW reset for the BODCORE */
    POWER_BodCoreEnableInt();

    CLOCK_DisableClock(kCLOCK_AnaInt);
}
#endif

/*!
 * brief Get default Vbat BOD config parameters, level 1.75V, Hysteresis  100mV
 *
 * param bod_cfg_p
 * return none
 */
void POWER_BodVbatGetDefaultConfig(pm_bod_cfg_t *bod_cfg_p)
{
    bod_cfg_p->bod_level = BODVBAT_LVL_DEFAULT;
    bod_cfg_p->bod_hyst  = BODVBAT_HYST_DEFAULT;
    bod_cfg_p->bod_cfg   = POWER_BOD_ENABLE | POWER_BOD_INT_ENABLE;
}

/*!
 * brief Configure the VBAT BOD
 *
 * param bod_cfg_p
 * return false if configuration parameters are incorrect
 */
bool POWER_BodVbatConfig(pm_bod_cfg_t *bod_cfg_p)
{
    uint32_t comparator_interrupt;

    if (bod_cfg_p->bod_cfg & POWER_BOD_ENABLE)
    {
        if ((bod_cfg_p->bod_level >= POWER_BOD_LVL_1_75V) && (bod_cfg_p->bod_level <= POWER_BOD_LVL_3_3V) &&
            (bod_cfg_p->bod_hyst <= POWER_BOD_HYST_100MV))
        {
            uint32_t bodvbat = PMC->BODVBAT;
            bodvbat &= ~(PMC_BODVBAT_TRIGLVL_MASK | PMC_BODVBAT_HYST_MASK);
            bodvbat |= PMC_BODVBAT_TRIGLVL(bod_cfg_p->bod_level);
            bodvbat |= PMC_BODVBAT_HYST(bod_cfg_p->bod_hyst);
            PMC->BODVBAT = bodvbat;
        }
        else
        {
            return false;
        }
    }

    /* enable the clock for the analog interrupt control module */
    CLOCK_EnableClock(kCLOCK_AnaInt);

    if (bod_cfg_p->bod_cfg & POWER_BOD_HIGH)
    {
        /* Disable Interrupt on BODVBAT High */
        SYSCON->ANACTRL_INTENCLR = SYSCON_ANACTRL_INTENCLR_BODVBATHIGH_MASK;

        /* clear initial status of interrupt */
        SYSCON->ANACTRL_STAT = SYSCON_ANACTRL_STAT_BODVBATHIGH_MASK;

        /* enable comparator interrupt       */
        comparator_interrupt = SYSCON_ANACTRL_INTENSET_BODVBATHIGH_MASK;
    }
    else
    {
        /*  BOD IC Interrupt enable */
        SYSCON->ANACTRL_INTENCLR = SYSCON_ANACTRL_INTENCLR_BODVBAT_MASK;

        /* clear initial status of interrupt */
        SYSCON->ANACTRL_STAT = SYSCON_ANACTRL_STAT_BODVBAT_MASK;

        /* enable comparator interrupt      */
        comparator_interrupt = SYSCON_ANACTRL_INTENSET_BODVBAT_MASK;
    }

    if (bod_cfg_p->bod_cfg & POWER_BOD_ENABLE)
    {
        if (bod_cfg_p->bod_cfg & POWER_BOD_INT_ENABLE)
        {
            SYSCON->ANACTRL_INTENSET = comparator_interrupt;
            NVIC_EnableIRQ(WDT_BOD_IRQn);
        }
        else
        {
            NVIC_DisableIRQ(WDT_BOD_IRQn);
        }
#ifdef FOR_BOD_DEBUG
        if (bod_cfg_p->bod_cfg & POWER_BOD_RST_ENABLE)
        {
            PMC->BODVBAT |= PMC_BODVBAT_RESETENABLE_MASK;
        }
        else
        {
            PMC->BODVBAT &= ~PMC_BODVBAT_RESETENABLE_MASK;
        }
#endif
    }

    // PRINTF( "BODVBAT=0x%X ANACTRL_CTRL=0x%X _STAT=0x%X _VAL=0x%X _INTENSET=0x%X\n", PMC->BODVBAT,
    // SYSCON->ANACTRL_CTRL, SYSCON->ANACTRL_STAT, SYSCON->ANACTRL_VAL, SYSCON->ANACTRL_INTENSET);

    return true;
}

bool POWER_EnterDeepSleepMode(pm_power_config_t *pm_power_config)
{
    /* [RFT1911] Disable the DC bus to prevent extra consumption */
#ifndef POWER_DCBUS_NOT_DISABLED
    ASYNC_SYSCON->DCBUSCTRL =
        (ASYNC_SYSCON->DCBUSCTRL & ~ASYNC_SYSCON_DCBUSCTRL_ADDR_MASK) | (1 << ASYNC_SYSCON_DCBUSCTRL_ADDR_SHIFT);
#endif

    /* [artf555998] Enable new ES2 feature for fast wakeup */
    PMC->CTRLNORST = PMC_CTRLNORST_FASTLDOENABLE_MASK;

    return false;
}


void POWER_GetPowerDownConfig(pm_power_config_t *pm_power_config, void* pm_config)
{
    int radio_retention;
    int autostart_32mhz_xtal;
    int keep_ao_voltage;
    int sram_cfg;
    int wakeup_src0;
    int wakeup_src1;
    uint8_t voltage_mem_down;
    uint8_t voltage_membootst_down;

    LPC_LOWPOWER_T* lp_config = (LPC_LOWPOWER_T*)pm_config;

    memset(lp_config, 0, sizeof(LPC_LOWPOWER_T));

    sram_cfg             = pm_power_config->pm_config & PM_CFG_SRAM_ALL_RETENTION;
    radio_retention      = pm_power_config->pm_config & PM_CFG_RADIO_RET;
    autostart_32mhz_xtal = pm_power_config->pm_config & PM_CFG_XTAL32M_AUTOSTART;
    keep_ao_voltage      = pm_power_config->pm_config & PM_CFG_KEEP_AO_VOLTAGE;

    wakeup_src0 = (int)pm_power_config->pm_wakeup_src & 0xFFFFFFFF;
    wakeup_src1 = (int)(pm_power_config->pm_wakeup_src >> 32) & 0xFFFFFFFF;
#ifdef TRACE_VRB
    PRINTF("POWER_EnterPowerDownMode:\n");
    PRINTF("  wakeup_src0      : 0x%x\n", wakeup_src0);
    PRINTF("  wakeup_src1      : 0x%x\n", wakeup_src1);
    PRINTF("  wakeup_io        : 0x%x\n", pm_power_config->pm_wakeup_io);
    PRINTF("  pm_config        : 0x%x\n", pm_power_config->pm_config);
#endif

    lp_config->CFG = LOWPOWER_CFG_MODE_POWERDOWN;

    /* PDRUNCFG : on ES2, flag discard to keep the same configuration than active */
    lp_config->CFG |= LOWPOWER_CFG_PDRUNCFG_DISCARD_MASK;

    /* PDSLEEPCFG (note: LDOMEM will be enabled by lowpower API if one memory bank in retention*/
    lp_config->PMUPWDN |= LOWPOWER_PMUPWDN_DCDC | LOWPOWER_PMUPWDN_BIAS | LOWPOWER_PMUPWDN_BODVBAT;

    /* Disable All banks except those given in sram_cfg */
    lp_config->DIGPWDN |= ((LOWPOWER_DIGPWDN_SRAM_ALL_MASK) & ~(sram_cfg << LOWPOWER_DIGPWDN_SRAM0_INDEX));

    // TODO : if COMM0 is disabled, need to switch off the clocks also for safe wake up
    lp_config->DIGPWDN |= LOWPOWER_DIGPWDN_COMM0; // PDSLEEP DISABLE COM0

    lp_config->DIGPWDN |=
        LOWPOWER_DIGPWDN_MCU_RET; // PDSLEEP DISABLE retention  : on ES1, CPU retention, on ES2 Zigbee retention

    // lp_config->DIGPWDN |= LOWPOWER_DIGPWDN_NTAG_FD;         // DPDWKSRC DISABLE NTAG  - not used in lowpower API in
    // power down

    lp_config->SLEEPPOSTPONE = 0;
    lp_config->GPIOLATCH     = 0;

    /* A bit in the flash is now set (bit 31 at address 0x9FCD4).
     * If this bit is set, RAM retention in sleep should use voltage of 0.9v.
     * If it is not set, RAM retention in sleep should use voltage of 1.0v. */
    if ( (*POWER_ULPGB_TRIM_FLASH_ADDR & 0x80000000) || FORCE_LDO_MEM_0V9_DBG)
    {
        /* exception if pwd_trim_val is 2 or above : POWER_APPLY_TRIM will cap the value to
             VOLTAGE_MEM_DOWN_0_9V  (9) and the LDO output voltage will remain to 0.85v.
              This is not enough if we consider device aging, so let s increase the
              LDO voltage setting to 0.96v. In fact, 0.91v will be provided by the LDO */
        if ( (pwd_trim_val != POWER_LDO_TRIM_UNDEFINED) && ( pwd_trim_val > 1)  )
        {
            voltage_mem_down       = VOLTAGE_MEM_DOWN_0_96V;
            voltage_membootst_down = VOLTAGE_MEMBOOST_DOWN_0_9V;
        }
        else
        {
            /* Apply normal trimming,  note that trimming on voltage_mem_down will be capped
                to 0x9 if pwd_trim_value == 1 , so it will be not trimmed correctly
                but we don t expect any issue as it will still provide 0.875v real and boost will be equal
                to 0.85v so no extra power consumption */
            voltage_mem_down       = POWER_APPLY_TRIM(VOLTAGE_MEM_DOWN_0_9V);
            voltage_membootst_down = POWER_APPLY_TRIM(VOLTAGE_MEMBOOST_DOWN_0_85V);
        }
    }
    else
    {
        voltage_mem_down       = POWER_APPLY_TRIM(VOLTAGE_MEM_DOWN_1_0V);
        voltage_membootst_down = POWER_APPLY_TRIM(VOLTAGE_MEMBOOST_DOWN_0_96V);
    }

    if (keep_ao_voltage)
    {
        LPC_LOWPOWER_LDOVOLTAGE_T ldo_voltage;

        Chip_LOWPOWER_GetSystemVoltages(&ldo_voltage);

        /* keep the same voltage than in active for the Always ON powerdomain */
        lp_config->VOLTAGE = VOLTAGE(POWER_APPLY_TRIM(ldo_voltage.LDOPMU),
                                     POWER_APPLY_TRIM(ldo_voltage.LDOPMUBOOST),
                                     voltage_mem_down,
                                     voltage_membootst_down,
                                     0,
                                     VOLTAGE_LDO_PMU_BOOST,
                                     0);
    }
    else
    {
        lp_config->VOLTAGE = VOLTAGE(POWER_APPLY_TRIM(VOLTAGE_PMU_DOWN),
                                     POWER_APPLY_TRIM(VOLTAGE_PMUBOOST_DOWN),
                                     voltage_mem_down,
                                     voltage_membootst_down, 0,
                                     VOLTAGE_LDO_PMU_BOOST,
                                     0);
    }

    lp_config->WAKEUPSRCINT0 = wakeup_src0;
    lp_config->WAKEUPSRCINT1 = wakeup_src1;

    /* Variation from reference */
    if (radio_retention)
    {
        /* Enable Zigbee retention */
        lp_config->DIGPWDN &= ~LOWPOWER_DIGPWDN_MCU_RET;
    }

    /* Configure IO wakeup source */
    if (lp_config->WAKEUPSRCINT1 & LOWPOWER_WAKEUPSRCINT1_IO_IRQ)
    {
        lp_config->WAKEUPIOSRC = pm_power_config->pm_wakeup_io;
    }

    if (lp_config->WAKEUPSRCINT0 & LOWPOWER_WAKEUPSRCINT0_SYSTEM_IRQ)
    {
        /* Need to enable the BIAS for VBAT BOD */
        lp_config->PMUPWDN &= ~(LOWPOWER_PMUPWDN_BIAS | LOWPOWER_PMUPWDN_BODVBAT);
    }

    if (lp_config->WAKEUPSRCINT0 &
        (LOWPOWER_WAKEUPSRCINT0_USART0_IRQ | LOWPOWER_WAKEUPSRCINT0_I2C0_IRQ | LOWPOWER_WAKEUPSRCINT0_SPI0_IRQ))
    {
        /* Keep Flexcom0 in power down mode */
        lp_config->DIGPWDN &= ~LOWPOWER_DIGPWDN_COMM0;
    }

    /* On ES2 , Analog comparator is already enabled in PDRUNCFG + RFT1877 : No need to keep the bias */
    if (sram_cfg)
    {
        /* Configure the SRAM to SMB1 (low leakage biasing) */
        SYSCON->SRAMCTRL =
            (SYSCON->SRAMCTRL & (~SYSCON_SRAMCTRL_SMB_MASK)) | (SYSCON_SRAMCTRL_SMB(1) << SYSCON_SRAMCTRL_SMB_SHIFT);

        /*
         * BODMEM requires the bandgap enable in power down, this induces a power consumption increase of 1uA
         * so Enable BODMEM only if bandgap is already enabled for BODVBAT (see code above)
         */
#ifndef POWER_FORCE_BODMEM_IN_PD
        if ((lp_config->PMUPWDN & LOWPOWER_PMUPWDN_BIAS) == 0)
#endif
        {
#ifdef FOR_BOD_DEBUG
            CLOCK_EnableClock(kCLOCK_AnaInt);

            /* Note: BODMEM should be already enabled in the POWER_Init() function but do it again if not */
            if (!(PMC->PDRUNCFG & PMC_PDRUNCFG_ENA_BOD_MEM_MASK))
            {
                POWER_BodMemSetup();
                /* This time, need to wait for LDO to be set up (27us) */
                CLOCK_uDelay(27);
            }
            POWER_BodMemEnableInt();
#endif
        }
#ifndef POWER_FORCE_BODMEM_IN_PD
        else
        {
#ifdef FOR_BOD_DEBUG
            /* Disable the BODMEM otherwise */
            POWER_BodMemDisable();
#endif
        }
#endif
    }
    else
    {
#ifdef FOR_BOD_DEBUG
        /* Disable the BODMEM otherwise */
        POWER_BodMemDisable();
#endif
    }
#ifdef FOR_BOD_DEBUG
    /* Disable BodCore , no longer used in power down */
    POWER_BodCoreDisable();
#endif
    if (wakeup_src0 & LOWPOWER_WAKEUPSRCINT0_NFCTAG_IRQ)
    {
        lp_config->WAKEUPSRCINT1 |= LOWPOWER_WAKEUPSRCINT1_IO_IRQ;
        lp_config->WAKEUPIOSRC |= LOWPOWER_WAKEUPIOSRC_NTAG_FD;
    }

    /* On Power down, NTAG field detect is enabled by IO so don t need to set the LOWPOWER_DIGPWDN_NTAG_FD */
    // lp_config->DIGPWDN &= ~LOWPOWER_DIGPWDN_NTAG_FD;      // used for deep down only

    if (autostart_32mhz_xtal)
    {
        lp_config->CFG |= LOWPOWER_CFG_XTAL32MSTARTENA_MASK;
    }

    /* get IO clamping state already set by the application and give it to lowpower API
     * Lowpower API overrides the IO configuration with GPIOLATCH setting
     */
    lp_config->GPIOLATCH = POWER_GetIoClampConfig();

    /* [RFT1911] Disable the DC bus to prevent extra consumption */
#ifndef POWER_DCBUS_NOT_DISABLED
    ASYNC_SYSCON->DCBUSCTRL =
        (ASYNC_SYSCON->DCBUSCTRL & ~ASYNC_SYSCON_DCBUSCTRL_ADDR_MASK) | (1 << ASYNC_SYSCON_DCBUSCTRL_ADDR_SHIFT);
#endif

    /* [artf555998] Enable new ES2 feature for fast wakeup */
    PMC->CTRLNORST = PMC_CTRLNORST_FASTLDOENABLE_MASK;

#ifdef DUMP_CONFIG
    LF_DumpConfig(&lp_config);
#endif
}

static void (*power_hook_fn)();

void POWER_GoToPowerDown( void* pm_config )
{
    LPC_LOWPOWER_T* lp_config = (LPC_LOWPOWER_T*)pm_config;

    /* If flexcom is maintained, do not disable the console and the clocks - let the application do it if needed */
    if (lp_config->DIGPWDN & LOWPOWER_DIGPWDN_COMM0)
    {
        /* remove console if not done */
        DbgConsole_Deinit();

        /* Disable clocks to FLEXCOM power domain. This power domain is not reseted on wakeup by HW */
        POWER_FlexcomClocksDisable();
    }

    if ( (void*)power_hook_fn != NULL )
    {
         /* Call hook function */
        (*power_hook_fn)();
    }


    Chip_LOWPOWER_SetLowPowerMode( lp_config );
}


void POWER_RegisterPowerDownEntryHookFunction( void (*pm_hook_function)() )
{
    power_hook_fn = pm_hook_function;
}

bool POWER_EnterPowerDownMode(pm_power_config_t *pm_power_config)
{
   LPC_LOWPOWER_T lp_config;

   /* get lp_config */
   POWER_GetPowerDownConfig(pm_power_config, (void*)&lp_config);

   POWER_GoToPowerDown(&lp_config);

   return false;
}


bool POWER_EnterDeepDownMode(pm_power_config_t *pm_power_config)
{
    int autostart_32mhz_xtal;
    int wakeup_src0;
    int wakeup_src1;
    LPC_LOWPOWER_T lp_config;

    memset(&lp_config, 0, sizeof(lp_config));

    autostart_32mhz_xtal = pm_power_config->pm_config & PM_CFG_XTAL32M_AUTOSTART;

    wakeup_src0 = (int)pm_power_config->pm_wakeup_src & 0xFFFFFFFF;
    wakeup_src1 = (int)(pm_power_config->pm_wakeup_src >> 32) & 0xFFFFFFFF;

#ifdef TRACE_VRB
    PRINTF("POWER_EnterDeepDownMode:\n");
    PRINTF("  wakeup_src0      : 0x%x\n", wakeup_src0);
    PRINTF("  wakeup_src1      : 0x%x\n", wakeup_src1);
#else
    (void)wakeup_src0;
#endif

    lp_config.CFG = LOWPOWER_CFG_MODE_DEEPPOWERDOWN;

    lp_config.PMUPWDN = LOWPOWER_PMUPWDN_DCDC | LOWPOWER_PMUPWDN_BIAS | LOWPOWER_PMUPWDN_BODVBAT |
                        LOWPOWER_PMUPWDN_FRO192M | LOWPOWER_PMUPWDN_FRO1M;

    lp_config.DIGPWDN = LOWPOWER_DIGPWDN_IO;

    if (wakeup_src1 & LOWPOWER_WAKEUPSRCINT1_IO_IRQ)
    {
        lp_config.DIGPWDN &= ~LOWPOWER_DIGPWDN_IO;
        lp_config.WAKEUPIOSRC = pm_power_config->pm_wakeup_io;
    }

    if (wakeup_src0 & LOWPOWER_WAKEUPSRCINT0_NFCTAG_IRQ)
    {
        lp_config.DIGPWDN &= ~LOWPOWER_DIGPWDN_NTAG_FD;
    }
    else
    {
        lp_config.DIGPWDN |= LOWPOWER_DIGPWDN_NTAG_FD;
    }

    lp_config.VOLTAGE = VOLTAGE(POWER_APPLY_TRIM(VOLTAGE_PMU_DEEP_DOWN), POWER_APPLY_TRIM(VOLTAGE_PMUBOOST_DEEP_DOWN),
                                0, 0, 0, VOLTAGE_LDO_PMU_BOOST, 0);

    if (autostart_32mhz_xtal)
    {
        lp_config.CFG |= LOWPOWER_CFG_XTAL32MSTARTENA_MASK;
    }

    /* [RFT1911] Disable the DC bus to prevent extra consumption */
#ifndef POWER_DCBUS_NOT_DISABLED
    ASYNC_SYSCON->DCBUSCTRL =
        (ASYNC_SYSCON->DCBUSCTRL & ~ASYNC_SYSCON_DCBUSCTRL_ADDR_MASK) | (1 << ASYNC_SYSCON_DCBUSCTRL_ADDR_SHIFT);
#endif

    /* [artf555998] Enable new ES2 feature for fast wakeup */
    PMC->CTRLNORST = PMC_CTRLNORST_FASTLDOENABLE_MASK;

#ifdef DUMP_CONFIG
    LF_DumpConfig(&lp_config);
#endif

    /* remove console if not done */
    DbgConsole_Deinit();

    /* Disable clocks to FLEXCOM power domain. This power domain is not reseted on wakeup by HW */
    POWER_FlexcomClocksDisable();

    Chip_LOWPOWER_SetLowPowerMode(&lp_config);

    /* If we go here, the power mode has been aborted - this can happen only if WFI is executed in lowpower API*/
    return false;
}

/*!
 * brief Power Library API to enter different power mode.
 *
 * If requested mode is PM_POWER_DOWN, the API will perform the clamping of the DIOs
 * if the PIO register has the bit IO_CLAMPING set: SYSCON->RETENTIONCTRL.IOCLAMP
 * will be set
 *
 * return false if chip could not go to sleep. Configuration structure is incorrect
 */
bool POWER_EnterPowerMode(pm_power_mode_t pm_power_mode, pm_power_config_t *pm_power_config)
{
    bool ret;
    switch (pm_power_mode)
    {
            /*  case PM_DEEP_SLEEP:
                    ret = POWER_EnterDeepSleepMode(pm_power_config);
                    break; */
        case PM_POWER_DOWN:
            ret = POWER_EnterPowerDownMode(pm_power_config);
            break;
        case PM_DEEP_DOWN:
            ret = POWER_EnterDeepDownMode(pm_power_config);
            break;
        default:
            ret = false;
    }

    return ret;
}

/*!
 * brief Set the DCDC output to 1.8v
 *
 * return none
 */
void POWER_SetDcdc1v8(void)
{
    /* DCDC settings */
    uint32_t myDCDC0 = PMC->DCDC0;
    uint32_t myDCDC1 = PMC->DCDC1;
    uint32_t valueRegister;

    // Set DCDC1.FORCEFULLCYCLE = 0x1
    myDCDC1 |= 0x04000000;

    // Set DCDC1.RSENSETRIM =  FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x00000780) >> 7);
    myDCDC1       = ((myDCDC1 & 0xFFFFFF0F) | valueRegister << 4);

    // Set DCDC1.LCENABLE = 0x0
    myDCDC1 &= 0xFDFFFFFF;

    // Set DCDC0.VOUT = 0x7
    myDCDC0 = ((myDCDC0 & 0xFFF1FFFF) | (0x7 << 17));

    // Set DCDC1.SETCURVE = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x00018000) >> 15);
    myDCDC1       = ((myDCDC1 & 0xFFFFF3FF) | (valueRegister << 10));

    // Set DCDC1.SETDC = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x00007800) >> 11);
    myDCDC1       = ((myDCDC1 & 0xFFFF0FFF) | (valueRegister << 12));

    // Set DCDC1.RTRIMOFFSET = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x03C00000) >> 22);
    myDCDC1       = ((myDCDC1 & 0xFFFFFFF0) | valueRegister);

    // Set DCDC1.TRIMAUTOCOT = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x3C000000) >> 26);
    myDCDC1       = ((myDCDC1 & 0xFE1FFFFF) | (valueRegister << 21));

    // Set DCDC0.TMOS = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x003E0000) >> 17);
    myDCDC0       = ((myDCDC0 & 0xFFFF07FF) | (valueRegister << 11));

    // Set DCDC0.RC = FLASH 1v8 70mA
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x0000007E) >> 1);
    myDCDC0       = ((myDCDC0 & 0xFFFFFFC0) | valueRegister);

    PMC->DCDC0 = myDCDC0;
    PMC->DCDC1 = myDCDC1;

    /* Measurements show that setting time for DCDC is around 40 us.
     * User needs to take this into account when handling other voltage
     * sensible components like the radio transceiver.
     */
}

/*!
 * brief Set the DCDC output to 1.3v
 *
 * return none
 */
void POWER_SetDcdc1v3(void)
{
    uint32_t myDCDC0 = PMC->DCDC0;
    uint32_t myDCDC1 = PMC->DCDC1;
    uint32_t valueRegister;

    // Reset the FORCEFULLCYCLE bit
    myDCDC1 &= ~0x04000000;

    // Set DCDC1.LCENABLE = 0x1
    myDCDC1 |= 0x02000000;

    // Set DCDC1.RSENSETRIM = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x00000780) >> 7);
    myDCDC1       = ((myDCDC1 & 0xFFFFFF0F) | (valueRegister << 4));

    // Set DCDC0.VOUT = 0x2
    myDCDC0 = ((myDCDC0 & 0xFFF1FFFF) | (0x2 << 17));

    // Set DCDC1.SETCURVE = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x00018000) >> 15);
    myDCDC1       = ((myDCDC1 & 0xFFFFF3FF) | (valueRegister << 10));

    // Set DCDC1.SETDC = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x00007800) >> 11);
    myDCDC1       = ((myDCDC1 & 0xFFFF0FFF) | (valueRegister << 12));

    // Set DCDC1.RTRIMOFFSET = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x03C00000) >> 22);
    myDCDC1       = ((myDCDC1 & 0xFFFFFFF0) | valueRegister);

    // Set DCDC1.TRIMAUTOCOT = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE4) & 0x3C000000) >> 26);
    myDCDC1       = ((myDCDC1 & 0xFE1FFFFF) | (valueRegister << 21));

    // Set DCDC0.TMOS = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x003E0000) >> 17);
    myDCDC0       = ((myDCDC0 & 0xFFFF07FF) | (valueRegister << 11));

    // Set DCDC0.RC = FLASH 60mA 1v3
    valueRegister = ((POWER_READ_REG32(0x0009FCE0) & 0x0000007E) >> 1);
    myDCDC0       = ((myDCDC0 & 0xFFFFFFC0) | valueRegister);

    PMC->DCDC0 = myDCDC0;
    PMC->DCDC1 = myDCDC1;
}

#ifdef DUMP_CONFIG
static void LF_DumpConfig(LPC_LOWPOWER_T *LV_LowPowerMode)
{
    PRINTF("Powerdown configuration\n");
    PRINTF("CFG:             0x%x\n", LV_LowPowerMode->CFG);
    PRINTF("PMUPWDN:         0x%x\n", LV_LowPowerMode->PMUPWDN);
    PRINTF("DIGPWDN:         0x%x\n", LV_LowPowerMode->DIGPWDN);
    PRINTF("VOLTAGE:         0x%x\n", LV_LowPowerMode->VOLTAGE);
    PRINTF("WAKEUPSRCINT0:   0x%x\n", LV_LowPowerMode->WAKEUPSRCINT0);
    PRINTF("WAKEUPSRCINT1:   0x%x\n", LV_LowPowerMode->WAKEUPSRCINT1);
    PRINTF("SLEEPPOSTPONE:   0x%x\n", LV_LowPowerMode->SLEEPPOSTPONE);
    PRINTF("WAKEUPIOSRC      0x%x\n", LV_LowPowerMode->WAKEUPIOSRC);
    PRINTF("GPIOLATCH        0x%x\n", LV_LowPowerMode->GPIOLATCH);
    PRINTF("TIMERCFG         0x%x\n", LV_LowPowerMode->TIMERCFG);
    PRINTF("TIMERBLECFG      0x%x\n", LV_LowPowerMode->TIMERBLECFG);
    PRINTF("TIMERCOUNTLSB    0x%x\n", LV_LowPowerMode->TIMERCOUNTLSB);
    PRINTF("TIMERCOUNTMSB    0x%x\n", LV_LowPowerMode->TIMERCOUNTMSB);
    PRINTF("TIMER2NDCOUNTLSB 0x%x\n", LV_LowPowerMode->TIMER2NDCOUNTLSB);
    PRINTF("TIMER2NDCOUNTMSB 0x%x\n", LV_LowPowerMode->TIMER2NDCOUNTMSB);
}

#endif
