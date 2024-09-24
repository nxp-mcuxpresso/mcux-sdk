/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_PCA9422_H_
#define FSL_PCA9422_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PCA9422 Default I2C address. */
#define PCA9422_DEFAULT_I2C_ADDR (0x61U)

/*! @brief Define the Register Memory Map of PCA9422. */
#define PCA9422_DEV_INFO      (0x00U)
#define PCA9422_TOP_INT       (0x01U)
#define PCA9422_SUB_INT0      (0x02U)
#define PCA9422_SUB_INT0_MASK (0x03U)
#define PCA9422_SUB_INT1      (0x04U)
#define PCA9422_SUB_INT1_MASK (0x05U)
#define PCA9422_SUB_INT2      (0x06U)
#define PCA9422_SUB_INT2_MASK (0x07U)
#define PCA9422_TOP_STAT      (0x08U)

#define PCA9422_TOP_CNTL0 (0x09U)
#define PCA9422_TOP_CNTL1 (0x0AU)
#define PCA9422_TOP_CNTL2 (0x0BU)
#define PCA9422_TOP_CNTL3 (0x0CU)
#define PCA9422_TOP_CNTL4 (0x0DU)

#define PCA9422_INT1        (0x0EU)
#define PCA9422_INT1_MASK   (0x0FU)
#define PCA9422_INT1_STATUS (0x10U)

#define PCA9422_PWR_STATE    (0x11U)
#define PCA9422_RESET_CTRL   (0x12U)
#define PCA9422_SW_RST       (0x13U)
#define PCA9422_PWR_SEQ_CTRL (0x14U)
#define PCA9422_SYS_CFG1     (0x15U)
#define PCA9422_SYS_CFG2     (0x16U)

#define PCA9422_REG_STATUS         (0x17U)
#define PCA9422_BUCK123_DVS_CFG1   (0x18U)
#define PCA9422_BUCK123_DVS_CFG2   (0x19U)
#define PCA9422_BUCK1CTRL          (0x1AU)
#define PCA9422_BUCK1OUT_DVS0      (0x1BU)
#define PCA9422_BUCK1OUT_DVS1      (0x1CU)
#define PCA9422_BUCK1OUT_DVS2      (0x1DU)
#define PCA9422_BUCK1OUT_DVS3      (0x1EU)
#define PCA9422_BUCK1OUT_DVS4      (0x1FU)
#define PCA9422_BUCK1OUT_DVS5      (0x20U)
#define PCA9422_BUCK1OUT_DVS6      (0x21U)
#define PCA9422_BUCK1OUT_DVS7      (0x22U)
#define PCA9422_BUCK1OUT_STBY      (0x23U)
#define PCA9422_BUCK1OUT_MAX_LIMIT (0x24U)
#define PCA9422_BUCK1OUT_SLEEP     (0x25U)

#define PCA9422_BUCK2CTRL          (0x26U)
#define PCA9422_BUCK2OUT_DVS0      (0x27U)
#define PCA9422_BUCK2OUT_DVS1      (0x28U)
#define PCA9422_BUCK2OUT_DVS2      (0x29U)
#define PCA9422_BUCK2OUT_DVS3      (0x2AU)
#define PCA9422_BUCK2OUT_DVS4      (0x2BU)
#define PCA9422_BUCK2OUT_DVS5      (0x2CU)
#define PCA9422_BUCK2OUT_DVS6      (0x2DU)
#define PCA9422_BUCK2OUT_DVS7      (0x2EU)
#define PCA9422_BUCK2OUT_STBY      (0x2FU)
#define PCA9422_BUCK2OUT_MAX_LIMIT (0x30U)
#define PCA9422_BUCK2OUT_SLEEP     (0x31U)

#define PCA9422_BUCK3CTRL          (0x32U)
#define PCA9422_BUCK3OUT_DVS0      (0x33U)
#define PCA9422_BUCK3OUT_DVS1      (0x34U)
#define PCA9422_BUCK3OUT_DVS2      (0x35U)
#define PCA9422_BUCK3OUT_DVS3      (0x36U)
#define PCA9422_BUCK3OUT_DVS4      (0x37U)
#define PCA9422_BUCK3OUT_DVS5      (0x38U)
#define PCA9422_BUCK3OUT_DVS6      (0x39U)
#define PCA9422_BUCK3OUT_DVS7      (0x3AU)
#define PCA9422_BUCK3OUT_STBY      (0x3BU)
#define PCA9422_BUCK3OUT_MAX_LIMIT (0x3CU)
#define PCA9422_BUCK3OUT_SLEEP     (0x3DU)
#define PCA9422_LPM_FPWM           (0x3EU)

#define PCA9422_LDO2_CFG      (0x3FU)
#define PCA9422_LDO2_OUT      (0x40U)
#define PCA9422_LDO2_OUT_STBY (0x41U)
#define PCA9422_LDO3_CFG      (0x42U)
#define PCA9422_LDO3_OUT      (0x43U)
#define PCA9422_LDO3_OUT_STBY (0x44U)
#define PCA9422_LDO23_CFG     (0x45U)
#define PCA9422_LDO4_CFG      (0x46U)
#define PCA9422_LDO4_OUT      (0x47U)
#define PCA9422_LDO4_OUT_STBY (0x48U)
#define PCA9422_LDO1_CFG1     (0x49U)
#define PCA9422_LDO1_CFG2     (0x4AU)

#define PCA9422_LDO2_OUT_SLEEP (0x4BU)
#define PCA9422_LDO3_OUT_SLEEP (0x4CU)
#define PCA9422_LDO4_OUT_SLEEP (0x4DU)

#define PCA9422_SW4_BB_CFG1       (0x4EU)
#define PCA9422_SW4_BB_CFG2       (0x4FU)
#define PCA9422_SW4_BB_CFG3       (0x50U)
#define PCA9422_SW4_BB_CFG4       (0x51U)
#define PCA9422_SW4_BB_MAX_LIMIT  (0x52U)
#define PCA9422_SW4_BB_MIN_LIMIT  (0x53U)
#define PCA9422_SW4_BB_VOUT_SLEEP (0x54U)

#define PCA9422_LED_CFG1    (0x55U)
#define PCA9422_LED_CFG2    (0x56U)
#define PCA9422_GPIO_STATUS (0x57U)
#define PCA9422_GPIO_CFG    (0x58U)

#define PCA9422_REGULATOR_EN (0x59U)
#define PCA9422_WAKEUP_SEQ1  (0x5AU)
#define PCA9422_WAKEUP_SEQ2  (0x5BU)

#define PCA9422_INT_DEVICE_0       (0x5C)
#define PCA9422_INT_DEVICE_1       (0x5D)
#define PCA9422_INT_CHARGER_0      (0x5E)
#define PCA9422_INT_CHARGER_1      (0x5F)
#define PCA9422_INT_CHARGER_2      (0x60)
#define PCA9422_INT_CHARGER_3      (0x61)
#define PCA9422_INT_DEVICE_0_MASK  (0x62)
#define PCA9422_INT_DEVICE_1_MASK  (0x63)
#define PCA9422_INT_CHARGER_0_MASK (0x64)
#define PCA9422_INT_CHARGER_1_MASK (0x65)
#define PCA9422_INT_CHARGER_2_MASK (0x66)
#define PCA9422_INT_CHARGER_3_MASK (0x67)
#define PCA9422_DEVICE_0_STS       (0x68)
#define PCA9422_DEVICE_1_STS       (0x69)
#define PCA9422_CHARGER_0_STS      (0x6A)
#define PCA9422_CHARGER_1_STS      (0x6B)
#define PCA9422_CHARGER_2_STS      (0x6C)
#define PCA9422_CHARGER_3_STS      (0x6D)

#define PCA9422_CHGIN_CNTL_0 (0x6E)
#define PCA9422_CHGIN_CNTL_1 (0x6F)
#define PCA9422_CHGIN_CNTL_2 (0x70)
#define PCA9422_CHGIN_CNTL_3 (0x71)

#define PCA9422_CHG_CNTL0  (0x72U)
#define PCA9422_CHG_CNTL1  (0x73U)
#define PCA9422_CHG_CNTL2  (0x74U)
#define PCA9422_CHG_CNTL3  (0x75U)
#define PCA9422_CHG_CNTL4  (0x76U)
#define PCA9422_CHG_CNTL5  (0x77U)
#define PCA9422_CHG_CNTL6  (0x78U)
#define PCA9422_CHG_CNTL7  (0x79U)
#define PCA9422_CHG_CNTL8  (0x7AU)
#define PCA9422_CHG_CNTL9  (0x7BU)
#define PCA9422_CHG_CNTL10 (0x7CU)

#define PCA9422_REG_LOCK (0x80U)

/*! @brief Define the Register Mask - device information */
#define PCA9422_DEV_ID  (0xF8U)
#define PCA9422_DEV_REV (0x07U)

/*! @brief Define the Register Masks - Top-level System Control Register. */
#define PCA9422_TOP_INT_SYS   (0x10U)
#define PCA9422_TOP_INT_CHG   (0x08U)
#define PCA9422_TOP_INT_SW_BB (0x04U)
#define PCA9422_TOP_INT_SW    (0x02U)
#define PCA9422_TOP_INT_LDO   (0x01U)

#define PCA9422_SUB_INT0_ON_SHORT_PUSH    (0x80U)
#define PCA9422_SUB_INT0_THERMAL_WARNING  (0x40U)
#define PCA9422_SUB_INT0_THSD             (0x20U)
#define PCA9422_SUB_INT0_THSD_EXIT        (0x10U)
#define PCA9422_SUB_INT0_VSYS_MIN_WARNING (0x08U)
#define PCA9422_SUB_INT0_WD_TIMER         (0x04U)
#define PCA9422_SUB_INT0_VSYS_OVP         (0x02U)
#define PCA9422_SUB_INT0_VSYS_OVP_EXT     (0x01U)
#define PCA9422_SUB_INT0_ALL              (0xFFU)

#define PCA9422_SUB_INT1_MODE_CMPL    (0x02U)
#define PCA9422_SUB_INT1_ON_LONG_PUSH (0x01U)
#define PCA9422_SUB_INT1_ALL          (0x03U)

#define PCA9422_SUB_INT2_VOUTSW1  (0x80U)
#define PCA9422_SUB_INT2_VOUTSW2  (0x40U)
#define PCA9422_SUB_INT2_VOUTSW3  (0x20U)
#define PCA9422_SUB_INT2_VOUTSW4  (0x10U)
#define PCA9422_SUB_INT2_VOUTLDO1 (0x08U)
#define PCA9422_SUB_INT2_VOUTLDO2 (0x04U)
#define PCA9422_SUB_INT2_VOUTLDO3 (0x02U)
#define PCA9422_SUB_INT2_VOUTLDO4 (0x01U)
#define PCA9422_SUB_INT2_ALL      (0xFFU)

#define PCA9422_TOP_STAT_SHIP_HISTORY (0x02U)
#define PCA9422_TOP_STAT_OCP_HISTORY  (0x01U)

#define PCA9422_TOP_CNTL0_WD_TIMER            (0xC0U)
#define PCA9422_TOP_CNTL0_SHIP_MODE_EN        (0x10U)
#define PCA9422_TOP_CNTL0_PWR_DN_EN           (0x08U)
#define PCA9422_TOP_CNTL0_nEN_CHG_IN_WATCHDOG (0x04U)
#define PCA9422_TOP_CNTL0_RESET_CFG           (0x02U)

#define PCA9422_TOP_CNTL1_SW_GLOBAL_RST_READY (0x04U)
#define PCA9422_TOP_CNTL1_THERMAL_WARNING     (0x03U)

#define PCA9422_TOP_CNTL2_THERM_SHDN   (0x1CU)
#define PCA9422_TOP_CNTL2_ON_GLT_SHORT (0x03U)

#define PCA9422_TOP_CNTL3_VSYS_MIN_WARNING (0x78U)
#define PCA9422_TOP_CNTL3_SW_GLOBAL_RST    (0x04U)
#define PCA9422_TOP_CNTL3_ON_GLT_LONG      (0x03U)

#define PCA9422_TOP_CNTL4_WE_TIMER_CLR (0x07U)

/*! @brief Define the Register Masks - Battery Charger Register. */
#define PCA9422_INT_DEVICE_0_CHGIN_SAFE_0V (0x04U)
#define PCA9422_INT_DEVICE_0_CHGIN_NOK     (0x02U)
#define PCA9422_INT_DEVICE_0_CHGIN_OK      (0x01U)

#define PCA9422_INT_DEVICE_1_CHGIN_I_LIMIT        (0x80U)
#define PCA9422_INT_DEVICE_1_VSYS_SUPPLEMENT_EXIT (0x40U)
#define PCA9422_INT_DEVICE_1_VSYS_SUPPLEMENT      (0x20U)
#define PCA9422_INT_DEVICE_1_VSYS_OVER_LOAD       (0x10U)
#define PCA9422_INT_DEVICE_1_CHGIN_AICL_RELEASE   (0x08U)
#define PCA9422_INT_DEVICE_1_CHGIN_AICL           (0x04U)
#define PCA9422_INT_DEVICE_1_CHGIN_OVP_EXIT       (0x02U)
#define PCA9422_INT_DEVICE_1_CHGIN_OVP            (0x01U)

#define PCA9422_INT_CHARGER_0_TOPOFF       (0x80U)
#define PCA9422_INT_CHARGER_0_CV_MODE      (0x40U)
#define PCA9422_INT_CHARGER_0_FAST_CHARGE  (0x20U)
#define PCA9422_INT_CHARGER_0_PRECHARGE    (0x10U)
#define PCA9422_INT_CHARGER_0_CHARGER_OFF  (0x08U)
#define PCA9422_INT_CHARGER_0_CHARGER_ON   (0x04U)
#define PCA9422_INT_CHARGER_0_CHG_QUAL_NOK (0x02U)
#define PCA9422_INT_CHARGER_0_CHG_QUAL_OK  (0x01U)

#define PCA9422_INT_CHARGER_1_THERM_HOT       (0x80U)
#define PCA9422_INT_CHARGER_1_THERM_WARM_PLUS (0x40U)
#define PCA9422_INT_CHARGER_1_THERM_WARM      (0x20U)
#define PCA9422_INT_CHARGER_1_THERM_COOL      (0x10U)
#define PCA9422_INT_CHARGER_1_THERM_COLD      (0x08U)
#define PCA9422_INT_CHARGER_1_VBAT_OVP_EXIT   (0x04U)
#define PCA9422_INT_CHARGER_1_VBAT_OVP        (0x02U)
#define PCA9422_INT_CHARGER_1_NO_BATTERY      (0x01U)

#define PCA9422_INT_CHARGER_2_RECHARGE            (0x80U)
#define PCA9422_INT_CHARGER_2_CHARGE_DONE         (0x40U)
#define PCA9422_INT_CHARGER_2_THERMAL_REGULATION  (0x20U)
#define PCA9422_INT_CHARGER_2_TOP_OFF_TIMER_OUT   (0x10U)
#define PCA9422_INT_CHARGER_2_FAST_CHG_TIMER_OUT  (0x08U)
#define PCA9422_INT_CHARGER_2_PRECHARGE_TIMER_OUT (0x04U)
#define PCA9422_INT_CHARGER_2_THERM_DISABLE       (0x02U)
#define PCA9422_INT_CHARGER_2_THERM_OPEN          (0x01U)

#define PCA9422_INT_CHARGER_3_VBAT_OCP (0x01U)

#define PCA9422_CHGIN_CNTL_O_CHGIN_PD_EN (0x02U)

#define PCA9422_CHGIN_CNTL_1_FORCE_DISCHARGE_VSYS_EN (0x08U)
#define PCA9422_CHGIN_CNTL_1_AICL_V                  (0x06U)
#define PCa9422_CHGIN_CNTL_1_AICL_EN                 (0x01U)

#define PCA9422_CHGIN_CNTL_2_CHGIN_IN_LIMIT (0x1FU)

#define PCA9422_CHGIN_CNTL_3_VSYS_REG (0xF0U)

#define PCA9422_CHARGER_CNTL_0_CHARGER_LOCK (0x30U)

#define PCA9422_CHARGER_CNTL_1_BAT_PRESENCE_DET_DISABLE (0x40U)
#define PCA9422_CHARGER_CNTL_1_AUTOSTOP_CHG_EN          (0x20U)
#define PCA9422_CHARGER_CNTL_1_CHARGER_EN               (0x10U)
#define PCA9422_CHARGER_CNTL_1_V_WARM_50C               (0x0CU)
#define PCA9422_CHARGER_CNTL_1_PRECHG_CURRENT           (0x02U)
#define PCA9422_CHARGER_CNTL_1_CHG_CURRENT_STEP         (0x01U)

#define PCA9422_CHARGER_CNTL_2_VBAT_REG (0x7FU)

#define PCA9422_CHARGER_CNTL_3_I_FAST_CHG (0x7FU)

#define PCA9422_CHARGER_CNTL_4_VBAT_OVP_DEB   (0xC0U)
#define PCA9422_CHARGER_CNTL_4_RECHARGE_TH    (0x30U)
#define PCA9422_CHARGER_CNTL_4_TOPOFF_CURRENT (0x0CU)
#define PCA9422_CHARGER_CNTL_4_PRE_CHG_TIMER  (0x03U)

#define PCA9422_CHARGER_CNTL_5_THERM_NTC_EN      (0x40U)
#define PCA9422_CHARGER_CNTL_5_OCP_DISCHARGE_DEB (0x30U)
#define PCA9422_CHARGER_CNTL_5_OCP_DISCHARGE     (0x03U)

#define PCA9422_CHARGER_CNTL_6_V_HOT_60C  (0xC0U)
#define PCA9422_CHARGER_CNTL_6_V_WARM_45C (0x30U)
#define PCA9422_CHARGER_CNTL_6_V_COOL_10C (0x0CU)
#define PCA9422_CHARGER_CNTL_6_V_COLD_0C  (0x03U)

#define PCA9422_CHARGER_CNTL_7_FAST_CHG_TIMER             (0xC0U)
#define PCA9422_CHARGER_CNTL_7_2X_ALL_TIMERS_EN           (0x20U)
#define PCA9422_CHARGER_CNTL_7_CHG_DISABLE_AT_COLD_HOT_EN (0x10U)
#define PCA9422_CHARGER_CNTL_7_NEW_I_VBAT_AT_10C          (0x0CU)
#define PCA9422_CHARGER_CNTL_7_NEW_VBAT_AT_45C            (0x03U)

#define PCA9422_CHARGER_CNTL_8_THERMAL_REGULATION (0x38U)
#define PCA9422_CHARGER_CNTL_8_TOP_OFF_TIMER      (0x07U)

#define PCA9422_CHARGER_CNTL_9_NEW_VBAT_AT_50C         (0xC0U)
#define PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_50C       (0x30U)
#define PCA9422_CHARGER_CNTL_9_NEW_I_VBAT_AT_45C       (0x0CU)
#define PCA9422_CHARGER_CNTL_9_FORCE_DISCHARGE_VBAT_EN (0x02U)
#define PCA9422_CHARGER_CNTL_9_USB_SUSPEND             (0x01U)

#define PCA9422_CHARGER_CNTL_10_AMUX_AUTO_OFF_WAIT  (0xC0U)
#define PCA9422_CHARGER_CNTL_10_AMUX_MODE           (0x20U)
#define PCA9422_CHARGER_CNTL_10_AMUX_VBAT_VSYS_GAIN (0x10U)
#define PCA9422_CHARGER_CNTL_10_AMUX_THERM_GAIN     (0x08U)
#define PCA9422_CHARGER_CNTL_10_AMUX_CHANNEL        (0x07U)

/*! @brief Define the Register Masks - Regulator Register. */
#define PCA9422_INT1_VR_FLT1     (0x08U)
#define PCA9422_INT1_BB_FAULT_OC (0x01U)

#define PCA9422_PWR_STATE_PWR_STAT (0xF0U)
#define PCA9422_PWR_STATE_PWR_MODE (0x0FU)

#define PCA9422_RESET_CTRL_TRESTART (0x08U)

#define PCA9422_SW_RST_SW_RST_KEY (0xFFU)

#define PCA9422_PWR_SEQ_CTRL_PSQ_TON_STEP  (0x0CU)
#define PCA9422_PWR_SEQ_CTRL_PSQ_TOFF_STEP (0x03U)

#define PCA9422_SYS_CFG1_STANDBY_CTRL (0x40U)
#define PCA9422_SYS_CFG1_STANDBY_CFG  (0x20U)
#define PCA9422_SYS_CFG1_DVS_CTRL2_EN (0x04U)
#define PCA9422_SYS_CFG1_TFLT_SD_WAIT (0x02U)
#define PCA9422_SYS_CFG1_THERM_SD_DIS (0x01U)

#define PCA9422_SYS_CFG2_PWR_SAVE        (0x30U)
#define PCA9422_SYS_CFG2_GPIO_PULLUP_CFG (0x08U)
#define PCA9422_SYS_CFG2_POK_PU          (0x04U)
#define PCA9422_SYS_CFG2_VSYS_UVLO_SEL   (0x03U)

#define PCA9422_REG_STATUS_VOUTSW1_OK  (0x80U)
#define PCA9422_REG_STATUS_VOUTSW2_OK  (0x40U)
#define PCA9422_REG_STATUS_VOUTSW3_OK  (0x20U)
#define PCA9422_REG_STATUS_VOUTSW4_OK  (0x10U)
#define PCA9422_REG_STATUS_VOUTLDO1_OK (0x08U)
#define PCA9422_REG_STATUS_VOUTLDO2_OK (0x04U)
#define PCA9422_REG_STATUS_VOUTLDO3_OK (0x02U)
#define PCA9422_REG_STATUS_VOUTLDO4_OK (0x01U)

/* BUCK */
#define PCA9422_BUCK123_DVS_CFG1_B1_DVS_UP  (0x80U)
#define PCA9422_BUCK123_DVS_CFG1_B1_DVS_DN  (0x40U)
#define PCA9422_BUCK123_DVS_CFG1_B2_DVS_UP  (0x20U)
#define PCA9422_BUCK123_DVS_CFG1_B2_DVS_DN  (0x10U)
#define PCA9422_BUCK123_DVS_CFG1_MODE_PULSE (0x08U)
#define PCA9422_BUCK123_DVS_CFG1_SMART_MODE (0x04U)
#define PCA9422_BUCK123_DVS_CFG1_BUCK_SEL   (0x03U)

#define PCA9422_BUCK123_DVS_CFG2_B1_DVS_CTRL (0xC0U)
#define PCA9422_BUCK123_DVS_CFG2_B2_DVS_CTRL (0x30U)
#define PCA9422_BUCK123_DVS_CFG2_B3_DVS_CTRL (0x0CU)
#define PCA9422_BUCK123_DVS_CFG2_B3_DVS_UP   (0x02U)
#define PCA9422_BUCK123_DVS_CFG2_B3_DVS_DN   (0x01U)

#define PCA9422_BUCKXCTRL_BX_RAMP   (0xC0U)
#define PCA9422_BUCKXCTRL_BX_LPMODE (0x30U)
#define PCA9422_BUCKXCTRL_BX_AD     (0x08U)
#define PCA9422_BUCKXCTRL_BX_FPWM   (0x04U)
#define PCA9422_BUCKXCTRL_BX_ENMODE (0x03U)

#define PCA9422_BUCKXOUT_DVS0_BX_DVS0           (0xFFU)
#define PCA9422_BUCKXOUT_DVS1_BX_DVS1           (0xFFU)
#define PCA9422_BUCKXOUT_DVS2_BX_DVS2           (0xFFU)
#define PCA9422_BUCKXOUT_DVS3_BX_DVS3           (0xFFU)
#define PCA9422_BUCKXOUT_DVS4_BX_DVS4           (0xFFU)
#define PCA9422_BUCKXOUT_DVS5_BX_DVS5           (0xFFU)
#define PCA9422_BUCKXOUT_DVS6_BX_DVS6           (0xFFU)
#define PCA9422_BUCKXOUT_DVS7_BX_DVS7           (0xFFU)
#define PCA9422_BUCKXOUT_STDBY_BX_STDBY         (0xFFU)
#define PCA9422_BUCKXOUT_MAX_LIMIT_BX_MAX_LIMIT (0xFFU)
#define PCA9422_BUCKXOUT_SLEEP_BX_SLEEP         (0xFFU)

#define PCA9422_LPM_FPWM_B3_LPM_FPWM_EN (0x04U)
#define PCA9422_LPM_FPWM_B2_LPM_FPWM_EN (0x02U)
#define PCA9422_LPM_FPWM_B1_LPM_FPWM_EN (0x01U)

/* LDO2 */
#define PCA9422_LDO2_CFG_L2_CSEL   (0xC0U)
#define PCA9422_LDO2_CFG_L2_LLSEL  (0x30U)
#define PCA9422_LDO2_CFG_L2_LPMODE (0x0CU)
#define PCA9422_LDO2_CFG_L2_ENMODE (0x03U)

#define PCA9422_LDO2_OUT_L2_AD        (0x80U)
#define PCA9422_LDO2_OUT_L2_INL2_MDET (0x40U)
#define PCA9422_LDO2_OUT_L2_OUT       (0x3FU)

#define PCA9422_LDO2_OUT_STBY_L2_OUT_STBY (0x3FU)

/* LDO3 */
#define PCA9422_LDO3_CFG_L3_CSEL   (0xC0U)
#define PCA9422_LDO3_CFG_L3_LLSEL  (0x30U)
#define PCA9422_LDO3_CFG_L3_LPMODE (0x0CU)
#define PCA9422_LDO3_CFG_L3_ENMODE (0x03U)

#define PCA9422_LDO3_OUT_L3_AD        (0x80U)
#define PCA9422_LDO3_OUT_L3_INL3_MDET (0x40U)
#define PCA9422_LDO3_OUT_L3_OUT       (0x3FU)

#define PCA9422_LDO3_OUT_STBY_L3_OUT_STBY (0x3FU)

#define PCA9422_LDO23_CFG_LDO3_MODE    (0x80U)
#define PCA9422_LDO23_CFG_LDO2_MODE    (0x40U)
#define PCA9422_LDO23_CFG_L2_INL2_VSEL (0x20U)
#define PCA9422_LDO23_CFG_L3_INL3_VSEL (0x10U)

/* LDO4 */
#define PCA9422_LDO4_CFG_L4_AD     (0x10U)
#define PCA9422_LDO4_CFG_L4_ENMODE (0x03U)
#define PCA9422_LDO4_OUT_L4_OUT    (0x7FU)

#define PCA9422_LDO4_OUT_STBY_L4_OUT_STBY (0x7FU)

/* LDO1 */
#define PCA9422_LDO1_CFG1_L1_AD  (0x80U)
#define PCA9422_LDO1_CFG1_L1_OUT (0x7FU)

#define PCA9422_LDO1_CFG2_L1_ENMODE (0x01U)

#define PCA9422_LDO2_OUT_SLEEP_L2_OUT_SLEEP (0x3FU)
#define PCA9422_LDO3_OUT_SLEEP_L3_OUT_SLEEP (0x3FU)
#define PCA9422_LDO4_OUT_SLEEP_L4_OUT_SLEEP (0x7FU)

/* SW4 BB */
#define PCA9422_SW4_BB_CFG1_BB_FPWM          (0x08U)
#define PCA9422_SW4_BB_CFG1_BB_FAULT_OC_CTRL (0x04U)
#define PCA9422_SW4_BB_CFG1_BB_SOFT_STDN     (0x02U)
#define PCA9422_SW4_BB_CFG1_BB_DIS           (0x01U)

#define PCA9422_SW4_BB_CFG2_BB_ENABLE  (0x40U)
#define PCA9422_SW4_BB_CFG2_BB_MODESEL (0x30U)
#define PCA9422_SW4_BB_CFG2_BB_ENMODE  (0x0CU)
#define PCA9422_SW4_BB_CFG2_BB_LPMODE  (0x03U)

#define PCA9422_SW4_BB_CFG3_BB_VOUT             (0xFFU)
#define PCA9422_SW4_BB_CFG4_BB_VOUT_STBY        (0xFFU)
#define PCA9422_SW4_BB_MAX_LIMIT_BB_MAX_LIMIT   (0xFFU)
#define PCA9422_SW4_BB_MIM_LIMIT_BB_MIM_LIMIT   (0xFFU)
#define PCA9422_SW4_BB_VOUT_SLEEP_BB_VOUT_SLEEP (0xFFU)

/* LED */
#define PCA9422_LED_CFG1_LED_EN   (0x80U)
#define PCA9422_LED_CFG1_LED_RAMP (0x40U)
#define PCA9422_LED_CFG1_LED_PWM  (0x3FU)

#define PCA9422_LED_CFG2_LEDOVRD     (0x20U)
#define PCA9422_LED_CFG2_LED_CFG     (0x10U)
#define PCA9422_LED_CFG2_LED_CURRENT (0x0CU)
#define PCA9422_LED_CFG2_LED_FREQ    (0x03U)

/* GPIO */
#define PCA9422_GPIO_STATUS_GPIO_STATUS (0x01U)

#define PCA9422_GPIO_CFG_GPIO_OUT      (0x80U)
#define PCA9422_GPIO_CFG_GPIO_R_CFG2   (0x40U)
#define PCA9422_GPIO_CFG_GPIO_R_CFG1   (0x20U)
#define PCA9422_GPIO_CFG_GPIO_OUT_CFG  (0x10U)
#define PCA9422_GPIO_CFG_GPIO_GPIO_CFG (0x0FU)

/* Regulator EN */
#define PCA9422_REGULATOR_EN_B1_ENABLE (0x20U)
#define PCA9422_REGULATOR_EN_B2_ENABLE (0x10U)
#define PCA9422_REGULATOR_EN_B3_ENABLE (0x08U)
#define PCA9422_REGULATOR_EN_L2_ENABLE (0x04U)
#define PCA9422_REGULATOR_EN_L3_ENABLE (0x02U)
#define PCA9422_REGULATOR_EN_L4_ENABLE (0x01U)

#define PCA9422_WAKEUP_SEQ1_BB_WAKEUP_GR (0xC0U)
#define PCA9422_WAKEUP_SEQ1_B3_WAKEUP_GR (0x30U)
#define PCA9422_WAKEUP_SEQ1_B2_WAKEUP_GR (0x0CU)
#define PCA9422_WAKEUP_SEQ1_B1_WAKEUP_GR (0x03U)

#define PCA9422_WAKEUP_SEQ2_WAKEUP_SEQ_CFG (0xC0U)
#define PCA9422_WAKEUP_SEQ2_L4_WAKEUP_GR   (0x30U)
#define PCA9422_WAKEUP_SEQ2_L3_WAKEUP_GR   (0x0CU)
#define PCA9422_WAKEUP_SEQ2_L2_WAKEUP_GR   (0x03U)

#define PCA94R22_REG_LOCK_UNLOCK_KEY (0xFFU)

/*! @brief PCA9422 Device information */
typedef enum _pca9422_dev_rev
{
    kPCA9422_DevRevA0 = 0x00U, /* Device revision A0 */
    kPCA9422_DevRevB0 = 0x01U, /* Device revision B0 */
} pca9422_dev_rev_t;

/*! @brief PCA9422 Top level function definition. */
/*! @brief PCA9422 Watchdog timer setting definition. */
typedef enum _pca9422_wd_timer
{
    kPCA9422_WdTimerDisabled = 0x00U, /* Watch dog timer disabled. */
    kPCA9422_WdTimer16s      = 0x40U, /* Watch dog timer timeout value is 16 sec. */
    kPCA9422_WdTimer32s      = 0x80U, /* Watch dog timer timeout value is 32 sec. */
    kPCA9422_WdTimer64s      = 0xC0U, /* Watch dog timer timeout value is 64 sec. */
} pca9422_wd_timer_t;

/*! @brief PCA9422 Battery Charger definition. */
/*! @brief PCA9422 AICL threshold on CHGIN definition. */
typedef enum _pca9422_aicl_v
{
    kPCA9422_AICLV4p5V = 0x00U, /* AICL Threshould on VIN is 4.5V */
    kPCA9422_AICLV4p6V = 0x02U, /* AICL Threshould on VIN is 4.6V */
    kPCA9422_AICLV4p7V = 0x04U, /* AICL Threshould on VIN is 4.7V */
    kPCA9422_AICLV4p8V = 0x06U, /* AICL Threshould on VIN is 4.8V */
} pca9422_aicl_v_t;

/*! @brief PCA9422 Input Current Limit on CHGIN definition. */
typedef enum _pca9422_chgin_ilim
{
    kPCA9422_ChgInIlim_45mA   = 0x00U,
    kPCA9422_ChgInIlim_70mA   = 0x01U,
    kPCA9422_ChgInIlim_95mA   = 0x02U,
    kPCA9422_ChgInIlim_120mA  = 0x03U,
    kPCA9422_ChgInIlim_145mA  = 0x04U,
    kPCA9422_ChgInIlim_170mA  = 0x05U,
    kPCA9422_ChgInIlim_195mA  = 0x06U,
    kPCA9422_ChgInIlim_220mA  = 0x07U,
    kPCA9422_ChgInIlim_245mA  = 0x08U,
    kPCA9422_ChgInIlim_270mA  = 0x09U,
    kPCA9422_ChgInIlim_295mA  = 0x0AU,
    kPCA9422_ChgInIlim_320mA  = 0x0BU,
    kPCA9422_ChgInIlim_345mA  = 0x0CU,
    kPCA9422_ChgInIlim_370mA  = 0x0DU,
    kPCA9422_ChgInIlim_395mA  = 0x0EU,
    kPCA9422_ChgInIlim_420mA  = 0x0FU,
    kPCA9422_ChgInIlim_445mA  = 0x10U,
    kPCA9422_ChgInIlim_470mA  = 0x11U,
    kPCA9422_ChgInIlim_495mA  = 0x12U,
    kPCA9422_ChgInIlim_520mA  = 0x13U,
    kPCA9422_ChgInIlim_545mA  = 0x14U,
    kPCA9422_ChgInIlim_570mA  = 0x15U,
    kPCA9422_ChgInIlim_595mA  = 0x16U,
    kPCA9422_ChgInIlim_620mA  = 0x17U,
    kPCA9422_ChgInIlim_645mA  = 0x18U,
    kPCA9422_ChgInIlim_670mA  = 0x19U,
    kPCA9422_ChgInIlim_695mA  = 0x1AU,
    kPCA9422_ChgInIlim_795mA  = 0x1BU,
    kPCA9422_ChgInIlim_895mA  = 0x1CU,
    kPCA9422_ChgInIlim_995mA  = 0x1DU,
    kPCA9422_ChgInIlim_1095mA = 0x1EU,
    kPCA9422_ChgInIlim_1195mA = 0x1FU,
} pca9422_chgin_ilim_t;

/*! @brief PCA9422 VSYS Regulation voltage definition. */
#define PCA9422_VSYS_REG_MIN      (4425U)
#define PCA9422_VSYS_REG_MAX      (4800U)
#define PCA9422_VSYS_REG_STEP     (25U)
#define PCA9422_VSYS_REG(_volt)   (((_volt) - PCA9422_VSYS_REG_MIN) / PCA9422_VSYS_REG_STEP)
#define PCA9422_VBAT_CLAMP_OFFSET (200U)

/*! @brief PCA9422 Unlock or lock all Charger Control register definition. */
#define PCA9422_CHARGER_LOCK_UNLOCK (0x30U)
#define PCA9422_CHARGER_LOCK_LOCK   (0x00U)

/*! @brief PCA922 V_WARM_50C threshold definition. */
typedef enum _pca9422_v_warm_50c
{
    kPCA9422_Vwarm50C40p75percent = 0x00U, /* Vwarm threshold is 40.75% of VTHREM_BIAS. */
    kPCA9422_Vwarm50C36p53percent = 0x04U, /* Vwarm threshold is 36.53% of VTHREM_BIAS. */
    kPCA9422_Vwarm50C32p63percent = 0x08U, /* Vwarm threshold is 32.63% of VTHREM_BIAS. */
    kPCA9422_Vwarm50C29p07percent = 0x0CU, /* Vwarm threshold is 29.07% of VTHREM_BIAS. */
} pca9422_v_warm_50c_t;

/*! @brief PCA922 V_WARM_45C threshold definition. */
typedef enum _pca9422_v_warm_45c
{
    kPCA9422_Vwarm45C40p75percent = 0x00U, /* Vwarm threshold is 40.75% of VTHREM_BIAS. */
    kPCA9422_Vwarm45C36p53percent = 0x10U, /* Vwarm threshold is 36.53% of VTHREM_BIAS. */
    kPCA9422_Vwarm45C32p63percent = 0x20U, /* Vwarm threshold is 32.63% of VTHREM_BIAS. */
    kPCA9422_Vwarm45C29p07percent = 0x30U, /* Vwarm threshold is 29.07% of VTHREM_BIAS. */
} pca9422_v_warm_45c_t;

/*! @brief PCA9422 Precharge Current definition. */
typedef enum _pca9422_prechg_i
{
    kPCA9422_PrechgI10percent = 0x00U, /* Precharge current is 10% of Fast charge current. */
    kPCA9422_PrechgI20percent = 0x02U, /* Precharge current is 20% of Fast charge current. */
} pca9422_prechg_i_t;

/*! @brief PCA9422 current step on battery charge current definition. */
typedef enum _pca9422_chg_i_step
{
    kPCA9422_ChgIStep2p5mA = 0x00U, /* Battery charge current step is 2.5mA. */
    kPCA9422_ChgIStep5p0mA = 0x01U, /* Battery charge current step is 5.0mA. */
} pca9422_chg_i_step_t;

/*! @brief PCA9422 fast charge current default value definition. */
#define PCA9422_I_FAST_CHG_DFT (0x27U)

/*! @brief PCA9422 VBAT floating voltage definition. */
#define PCA9422_VBAT_REG_MIN    (3600U)
#define PCA9422_VBAT_REG_MAX    (4600U)
#define PCA9422_VBAT_REG_STEP   (10U)
#define PCA9422_VBAT_REG(_volt) (((_volt) - PCA9422_VBAT_REG_MIN) / PCA9422_VBAT_REG_STEP)

/*! @brief PCA9422 fast charge current default value definition. */
#define PCA9422_I_FAST_CHG_DFT (0x27U) /* 100mA */

/*! @brief PCA9422 Recharge threshold definition. */
typedef enum _pca9422_recharge_th
{
    kPCA9422_RechargeTh100mV = 0x00U, /* Recharge threshold based on VBAT <= VBAT_REG - 100mV */
    kPCA9422_RechargeTh150mV = 0x10U, /* Recharge threshold based on VBAT <= VBAT_REG - 150mV */
    kPCA9422_RechargeTh200mV = 0x20U, /* Recharge threshold based on VBAT <= VBAT_REG - 200mV */
} pca9422_recharge_th_t;

/*! @brief PCA9422 Top-off current definition. */
typedef enum _pca9422_topoff_i
{
    kPCA9422_TopoffI2p5percent  = 0x00U, /* Topoff current is 2.5% of Fast charge current. */
    kPCA9422_TopoffI5p0percent  = 0x04U, /* Topoff current is 5.0% of Fast charge current. */
    kPCA9422_TopoffI7p5percent  = 0x08U, /* Topoff current is 7.5% of Fast charge current. */
    kPCA9422_TopoffI10p0percent = 0x0CU, /* Topoff current is 10.0% of Fast charge current. */
} pca9422_topoff_i_t;

/*! @brief PCA9422 Precharge timer definition. */
typedef enum _pca9422_precharge_timer
{
    kPCA9422_PrechgTimerDisable = 0x00U, /* Precharge timer is disabled. */
    kPCA9422_PrechgTimer15min   = 0x01U, /* Precharge timer set 15min. */
    kPCA9422_PrechgTimer30min   = 0x02U, /* Precharge timer set 30min. */
    kPCA9422_PrechgTimer60min   = 0x03U, /* Precharge timer set 60min. */
} pca9422_precharge_timer_t;

/*! @brief PCA9422 charger control 5 register default value definition. */
#define PCA9422_CHARGER_CNTL_5_DFT (0x01U)

/*! @brief PCA9422 V_HOT_60C threshold definition. */
typedef enum _pca9422_v_hot_60c
{
    kPCA9422_Vhot60C32p63percent = 0x00U, /* Vhot threshold is 32.63% of VTHREM_BIAS. */
    kPCA9422_Vhot60C29p07percent = 0x40U, /* Vhot threshold is 29.07% of VTHREM_BIAS. */
    kPCA9422_Vhot60C25p84percent = 0x80U, /* Vhot threshold is 25.84% of VTHREM_BIAS. */
    kPCA9422_Vhot60C22p94percent = 0xC0U, /* Vhot threshold is 22.94% of VTHREM_BIAS. */
} pca9422_v_hot_60c_t;

/*! @brief PCA9422 V_COOL_10C threshold definition. */
typedef enum _pca9422_v_cool_10c
{
    kPCA9422_Vcool10C74p18percent = 0x00U, /* Vcool threshold is 74.18% of VTHREM_BIAS. */
    kPCA9422_Vcool10C69p62percent = 0x04U, /* Vcool threshold is 69.62% of VTHREM_BIAS. */
    kPCA9422_Vcool10C64p82percent = 0x08U, /* Vcool threshold is 64.82% of VTHREM_BIAS. */
    kPCA9422_Vcool10C59p87percent = 0x0CU, /* Vcool threshold is 59.87% of VTHREM_BIAS. */
} pca9422_v_cool_10c_t;

/*! @brief PCA9422 V_COLD_0C threshold definition. */
typedef enum _pca9422_v_cold_0c
{
    kPCA9422_Vcold0C82p26percent = 0x00U, /* Vcold threshold is 82.26% of VTHREM_BIAS. */
    kPCA9422_Vcold0C78p42percent = 0x01U, /* Vcold threshold is 78.42% of VTHREM_BIAS. */
    kPCA9422_Vcold0C74p18percent = 0x02U, /* Vcold threshold is 74.18% of VTHREM_BIAS. */
    kPCA9422_Vcold0C69p62percent = 0x03U, /* Vcold threshold is 69.62% of VTHREM_BIAS. */
} pca9422_v_cold_0c_t;

/*! @brief PCA9422 Fast charge timer definition. */
typedef enum _pca9422_fast_chg_timer
{
    kPCA9422_FastchgTimerDisable = 0x00U, /* Fast charge timer is disabled */
    kPCA9422_FastchgTimer3h      = 0x40U, /* Fast charge timer set 3 hours */
    kPCA9422_FastchgTimer5h      = 0x80U, /* Fast charge timer set 5 hours */
    kPCA9422_FastchgTimer7h      = 0xC0U, /* Fast charge timer set 7 hours */
} pca9422_fast_chg_timer_t;

/*! @brief PCA9422 New charge current at COOL(10C) condition definition. */
typedef enum _pca9422_new_i_vbat_10c
{
    kPCA9422_NewIVbat10C_StayIFastchg = 0x00U,       /* Stays a current IFAST_CHG */
    kPCA9422_NewIVbat10C_0p75percentIFastchg =
        0x04U,                                       /* Set [2.5mA or 5.0mA + 0.75 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat10C_0p5percentIFastchg = 0x08U, /* Set [2.5mA or 5.0mA + 0.50 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat10C_0p25percentIFastchg =
        0x0CU,                                       /* Set [2.5mA or 5.0mA + 0.25 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
} pca9422_new_i_vbat_10c_t;

/*! @brief PCA9422 New charge current at WARM Plus(50C) condition definition. */
typedef enum _pca9422_new_i_vbat_50c
{
    kPCA9422_NewIVbat50C_StayIFastchg = 0x00U,       /* Stays a current IFAST_CHG */
    kPCA9422_NewIVbat50C_0p75percentIFastchg =
        0x10U,                                       /* Set [2.5mA or 5.0mA + 0.75 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat50C_0p5percentIFastchg = 0x20U, /* Set [2.5mA or 5.0mA + 0.50 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat50C_0p25percentIFastchg =
        0x30U,                                       /* Set [2.5mA or 5.0mA + 0.25 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
} pca9422_new_i_vbat_50c_t;

/*! @brief PCA9422 New charge current at WARM(45C) condition definition. */
typedef enum _pca9422_new_i_vbat_45c
{
    kPCA9422_NewIVbat45C_StayIFastchg = 0x00U,       /* Stays a current IFAST_CHG */
    kPCA9422_NewIVbat45C_0p75percentIFastchg =
        0x04U,                                       /* Set [2.5mA or 5.0mA + 0.75 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat45C_0p5percentIFastchg = 0x08U, /* Set [2.5mA or 5.0mA + 0.50 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
    kPCA9422_NewIVbat45C_0p25percentIFastchg =
        0x0CU,                                       /* Set [2.5mA or 5.0mA + 0.25 *I_FAST_CHG[6:0] x 2.5mA or 5.0mA] */
} pca9422_new_i_vbat_45c_t;

/*! @brief PCA9422 New VBAT_REG at WARM condition, WARM_45C or WARM_50C, definition. */
typedef enum _pca9422_new_vbat_45c
{
    kPCA9422_NewVbat45C_StayVbatReg       = 0x00U, /* Stays a current VVBAT_REG */
    kPCA9422_NewVbat45C_VbatRegMinus100mV = 0x01U, /* Set a new value with (VVBAT_REG – 100mV) */
    kPCA9422_NewVbat45C_VbatRegMinus150mV = 0x02U, /* Set a new value with (VVBAT_REG – 150mV) */
    kPCA9422_NewVbat45C_VbatRegMinus200mV = 0x03U, /* Set a new value with (VVBAT_REG – 200mV) */
} pca9422_new_vbat_45c_t;

/*! @brief PCA9422 New VBAT_REG at WARM condition, WARM_45C or WARM_50C, definition. */
typedef enum _pca9422_new_vbat_50c
{
    kPCA9422_NewVbat50C_StayVbatReg       = 0x00U, /* Stays a current VVBAT_REG */
    kPCA9422_NewVbat50C_VbatRegMinus100mV = 0x40U, /* Set a new value with (VVBAT_REG – 100mV) */
    kPCA9422_NewVbat50C_VbatRegMinus150mV = 0x80U, /* Set a new value with (VVBAT_REG – 150mV) */
    kPCA9422_NewVbat50C_VbatRegMinus200mV = 0xC0U, /* Set a new value with (VVBAT_REG – 200mV) */
} pca9422_new_vbat_50c_t;

/*! @brief PCA9422 thermal regulation threshold definition. */
typedef enum _pca9422_thermal_reg
{
    kPCA9422_ThermalRegulationDisable = 0x00U, /* Thermal regulation threshold is disabled */
    kPCA9422_ThermalRegulation60C     = 0x08U, /* Thermal regulation threshuold is 60C */
    kPCA9422_ThermalRegulation70C     = 0x10U, /* Thermal regulation threshuold is 70C */
    kPCA9422_ThermalRegulation80C     = 0x18U, /* Thermal regulation threshuold is 80C */
    kPCA9422_ThermalRegulation90C     = 0x20U, /* Thermal regulation threshuold is 90C */
    kPCA9422_ThermalRegulation100C    = 0x28U, /* Thermal regulation threshuold is 100C */
} pca9422_thermal_regulation_t;

/*! @brief PCA9422 Top-off timer definition. */
typedef enum _pca9422_top_off_timer
{
    kPCA9422_TopoffTimerDisable = 0x00U,
    kPCA9422_TopoffTimer5min    = 0x01U,
    kPCA9422_TopoffTimer10min   = 0x02U,
    kPCA9422_TopoffTimer15min   = 0x03U,
    kPCA9422_TopoffTimer20min   = 0x04U,
    kPCA9422_TopoffTimer25min   = 0x05U,
    kPCA9422_TopoffTimer30min   = 0x06U,
    kPCA9422_TopoffTimer35min   = 0x07U,
} pca9422_top_off_timer_t;

/*! @brief PCA9422 AMUX wait time definition. */
typedef enum _pca9422_amux_auto_off_wait
{
    kPCA9422_AMUXAutoOffWait_256us   = 0x00U,
    kPCA9422_AMUXAutoOffWait_1088us  = 0x40U,
    kPCA9422_AMUXAutoOffWait_8192us  = 0x80U,
    kPCA9422_AMUXAutoOffWait_32768us = 0xC0U,
} pca9422_amux_auto_off_wait_t;

/*! @brief PCA9422 AMUX mode definition. */
typedef enum _pca9422_amux_mode
{
    kPCA9422_AMUXModeManual      = 0x00U,
    kPCA9422_AMUXModeAutoOneshot = 0x20U,
} pca9422_amux_mode_t;

/*! @brief PCA9422 AMUX VBAT/VSYS channel scale factor definition. */
typedef enum _pca9422_amux_vbat_vsys_gain
{
    kPCA9422_AMUXVbatVsysGain_1dvd3 = 0x00U, /* 1/3 */
    kPCA9422_AMUXVbatVsysGain_1dvd4 = 0x10U, /* 1/4 */
} pca9422_amux_vbat_vsys_gain_t;

/*! @brief PCA9422 AMUX THERM and THERM_BIAS channel scale factor definition. */
typedef enum _pca9422_amux_therm_gain
{
    kPCA9422_AMUXThermGain_1       = 0x00U, /* 1 */
    kPCA9422_AMUXThermGain_1dvd1p5 = 0x08U, /* 1/1.5 */
} pca9422_amux_therm_gain_t;

/* @brief PCA9422 AMUX channel definition. */
typedef enum _pca9422_amux_channel
{
    kPCA9422_AMUXChannel_Off       = 0x00U,
    kPCA9422_AMUXChannel_Vbat      = 0x01U,
    kPCA9422_AMUXChannel_Therm     = 0x02U,
    kPCA9422_AMUXChannel_ThermBias = 0x03U,
    kPCA9422_AMUXChannel_Vsys      = 0x04U,
    kPCA9422_AMUXChannel_Vin       = 0x05U,
    kPCA9422_AMUXChannel_Max       = 0x06U,
} pca9422_amux_channel_t;

/* @brief PCA9422 AMUX configuration structure definition */
typedef struct _pca9422_amux_config
{
    /* AMUX wait time to be automatically disabled in automatic one-shot mode. */
    uint8_t waitTime;
    /* AMUX mode */
    uint8_t amuxMode;
    /* VBAT/VSYS channel scale factor */
    uint8_t vbatGain;
    /* THERM and THERM_BIAS channels scale factor */
    uint8_t thermGain;
    /* AMUX channel */
    uint8_t amuxChannel;
} pca9422_amux_config_t;

/*! @brief PCA9422 Regulator */
/*! @brief PCA9422 Regulator Status definition. */
typedef enum _pca9422_reg_status
{
    kPCA9422_RegStatusVoutSw1OK  = 0x80U, /* SW1 VOUT Power good status */
    kPCA9422_RegStatusVoutSw2OK  = 0x40U, /* SW2 VOUT Power good status */
    kPCA9422_RegStatusVoutSw3OK  = 0x20U, /* SW3 VOUT Power good status */
    kPCA9422_RegStatusVoutSw4OK  = 0x10U, /* SW4 VOUT Power good status */
    kPCA9422_RegStatusVoutLdo1OK = 0x08U, /* LDO1 VOUT Power good status */
    kPCA9422_RegStatusVoutLdo2OK = 0x04U, /* LDO2 VOUT Power good status */
    kPCA9422_RegStatusVoutLdo3OK = 0x02U, /* LDO3 VOUT Power good status */
    kPCA9422_RegStatusVoutLdo4OK = 0x01U, /* LDO4 VOUT Power good status */
} pca9422_reg_status_t;

/*! @brief PCA9422 Power mode definition. */
typedef enum _pca9422_power_mode
{
    kPCA9422_ActiveModeDVS0 = 0x00U, /* Active mode - DVS0 */
    kPCA9422_ActiveModeDVS1 = 0x01U, /* Active mode - DVS1 */
    kPCA9422_ActiveModeDVS2 = 0x02U, /* Active mode - DVS2 */
    kPCA9422_ActiveModeDVS3 = 0x03U, /* Active mode - DVS3 */
    kPCA9422_ActiveModeDVS4 = 0x04U, /* Active mode - DVS4 */
    kPCA9422_ActiveModeDVS5 = 0x05U, /* Active mode - DVS5 */
    kPCA9422_ActiveModeDVS6 = 0x06U, /* Active mode - DVS6 */
    kPCA9422_ActiveModeDVS7 = 0x07U, /* Active mode - DVS7 */
    kPCA9422_StandbyMode    = 0x08U, /* STANDBY mode */
    kPCA9422_NoneMode       = 0x09U, /* None mode */
    kPCA9422_DPStandbyMode  = 0x0AU, /* DPSTANDBY mode */
    kPCA9422_SleepMode      = 0x0BU, /* SLEEP mode */
    kPCA9422_PowerModeMax   = 0x0CU, /* Max Power mode */
} pca9422_power_mode_t;

/*! @brief PCA9422 Standby control definition */
typedef enum _pca9422_standby_ctrl
{
    kPCA9422_StandbyCtrlPins                = 0x00U,
    kPCA9422_StandbyCtrlStandbyConfigandPin = 0x40U,
} pca9422_standby_ctrl_t;

/*! @brief PCA9422 Standby configuration definition */
typedef enum _pca9422_standby_cfg
{
    kPCA9422_StandbyCfgStandby   = 0x00U,
    kPCA9422_StandbyCfgDPStandby = 0x20U,
} pca9422_standby_cfg_t;

/*! @brief PCA9422 DVS_CTRL2 pin enable definition */
typedef enum _pca9422_dvs_ctrl2_en
{
    kPCA9422_DVSCtrl2PinIgnore     = 0x00U,
    kPCA9422_DVSCtrl2PinUseDVSCtrl = 0x04U,
} pca9422_dvs_ctrl2_en_t;

/*! @brief PCA9422 Power Save mode definition */
typedef enum _pca9422_power_save_mode
{
    kPCA9422_PowerSaveUseLowIq         = 0x00U,
    kPCA9422_PowerSaveStandbyDPStandby = 0x10U,
    kPCA9422_PowerSaveDPStandby        = 0x20U,
    kPCA9422_PowerSaveNormal           = 0x30U,
} pca9422_power_save_mode_t;

/*! @brief PCA9422 GPIO pull-up configuration definition */
typedef enum _pca9422_gpio_pullup_cfg
{
    kPCA9422_GPIOPullupVsys = 0x00U,
    kPCA9422_GPIOPullupLDO1 = 0x08U,
} pca9422_gpio_pullup_cfg_t;

/*! @brief PCA9422 VSYS UVLO threshold definition */
typedef enum _pca9422_vsys_uvlo_sel
{
    kPCA9422_VsysUVLOSel2p6V = 0x00U,
    kPCA9422_VsysUVLOSel2p7V = 0x01U,
    kPCA9422_VsysUVLOSel2p8V = 0x02U,
} pca9422_vsys_uvlo_sel_t;

/*! @brief PCA9422 DVS smart mode configuration definition */
typedef enum _pca9422_smart_mode
{
    kPCA9422_SmartModeDisabled = 0x00U,
    kPCA9422_SmartModeEnabled  = 0x04U,
} pca9422_smart_mode_t;

/*! @brief PCA9422 Run state definition. */
typedef enum _pca9422_run_state
{
    kPCA9422_RunStateActiveMode    = 0x00U,
    kPCA9422_RunStateSleepMode     = 0x01U,
    kPCA9422_RunStateStandbyMode   = 0x02U,
    kPCA9422_RunStateDPStandbyMode = 0x03U,
} pca9422_run_state_t;

/*! @brief PCA9422 Regulator definition. */
typedef enum _pca9422_regulator
{
    kPCA9422_RegulatorSwitch1 = 0x80U, /* Switch1 regulator. */
    kPCA9422_RegulatorSwitch2 = 0x40U, /* Switch2 regulator. */
    kPCA9422_RegulatorSwitch3 = 0x20U, /* Switch3 regulator. */
    kPCA9422_RegulatorSwitch4 = 0x10U, /* Switch4 regulator. */
    kPCA9422_RegulatorLdo1    = 0x08U, /* LDO1 regulator. */
    kPCA9422_RegulatorLdo2    = 0x04U, /* LDO2 regulator. */
    kPCA9422_RegulatorLdo3    = 0x02U, /* LDO3 regulator. */
    kPCA9422_RegulatorLdo4    = 0x01U, /* LDO4 regulator. */
} pca9422_regulator_t;

/*! @brief PCA9422 Regulator Enable mode definition. */
typedef enum _pca9422_enmode
{
    kPCA9422_EnmodeOnAll                = 0x00U,
    kPCA9422_EnmodeOnActiveSleepStandby = 0x01U,
    kPCA9422_EnmodeOnActiveSleep        = 0x02U,
    kPCA9422_EnmodeOnActive             = 0x03U,
} pca9422_enmode_t;

/*! @brief PCA9422 Buck DVS control definition. */
enum _pca9422_bx_dvs_ctrl
{
    kPCA9422_DVS0thrI2CInActiveAndSleep = 0x00U, /* BUCKxOUT_DVS0 Reg through I2C in both ACTIVE and SLEEP modes */
    kPCA9422_DVS0thrI2CInAcitveAndBxOUTSLEEPInSleep =
        0x01U, /* BUCKxOUT_DVS0 Reg through I2C in ACTIVE mode, and BUCKxOUT_SLEEP when in SLEEP mode */
    kPCA9422_PinInActiveAndBxOUTSLEEPInSleep =
        0x02U, /* DVS_CTRL[2:0] pins in ACTIVE mode and BUCKxOUT_SLEEP when in SLEEP mode */
    kPCA9422_DVS0thrI2CInAcitveAndPinInSleep =
        0x03U, /* BUCKxOUT_DVS0 Reg through I2C in ACTIVE mode, and DVS_CTRL[2:0] pins when in SLEEP mode */
};

/*! @brief PCA9422 Buck DVS Ramp definition. */
typedef enum _pca9422_bx_ramp
{
    kPCA9422_BxRamp_25mVp1us = 0x00U,
    kPCA9422_BxRamp_25mVp2us = 0x40U,
    kPCA9422_BxRamp_25mVp4us = 0x80U,
    kPCA9422_BxRamp_25mVp8us = 0xC0U,
} pca9422_bx_ramp_t;

/*! @brief PCA9422 Buck power mode definition. */
typedef enum _pca9422_bx_lpmode
{
    kPCA9422_BxLPmodeNormal             = 0x00U, /* Normal mode */
    kPCA9422_BxLPmodeAtStandbyDPStandby = 0x10U, /* Low power mode at STANDBY mode and DPSTANDBY mode */
    kPCA9422_BxLPmodeAtDPStandby        = 0x20U, /* Low power mode at DPSTANDBY mode */
    kPCA9422_BxLPmodeForcedLPM          = 0x30U, /* Forced low power mode */
} pca9422_bx_lpmode_t;

/*! @brief PCA9422 Buck Active Discharge definition. */
typedef enum _pca9422_bx_ad
{
    kPCA9422_BxADDisabled = 0x00U,
    kPCA9422_BxADEnabled  = 0x08U,
} pca9422_bx_ad_t;

/*! @brief PCA9422 Buck Forced PWM definition. */
typedef enum _pca9422_bx_fpwm_mode
{
    kPCA9422_BxAutoPFMandPWM = 0x00U,
    kPCA9422_BxForcedPWM     = 0x04U,
} pca9422_bx_fpwm_mode_t;

/*! @brief PCA9422 Buck1 OUT voltage definition. (uV unit) */
#define PCA9422_BUCK1_OUT_MIN        (400000U)  /* 400mV */
#define PCA9422_BUCK1_OUT_STEP       (6250UL)   /* 6.25mV */
#define PCA9422_BUCK1_OUT_MAX        (1975000U) /* 1975mV */
#define PCA9422_BUCK1_OUT_VAL(_volt) (((_volt) - PCA9422_BUCK1_OUT_MIN) / PCA9422_BUCK1_OUT_STEP)
#define PCA9422_BUCK1_OUT_VOLT(_val) (((_val) * PCA9422_BUCK1_OUT_STEP) + PCA9422_BUCK1_OUT_MIN)

/*! @brief PCA9422 Buck2 OUT voltage definition. (uV unit) */
#define PCA9422_BUCK2_OUT_MIN        (400000U)  /* 400mV */
#define PCA9422_BUCK2_OUT_STEP       (25000U)   /* 25mV */
#define PCA9422_BUCK2_OUT_MAX        (3400000U) /* 3400mV */
#define PCA9422_BUCK2_OUT_VAL(_volt) (((_volt) - PCA9422_BUCK2_OUT_MIN) / PCA9422_BUCK2_OUT_STEP)
#define PCA9422_BUCK2_OUT_VOLT(_val) (((_val) * PCA9422_BUCK2_OUT_STEP) + PCA9422_BUCK2_OUT_MIN)

/*! @brief PCA9422 Buck3 OUT voltage definition. (uV unit) */
#define PCA9422_BUCK3_OUT_MIN        (400000U)  /* 400mV */
#define PCA9422_BUCK3_OUT_STEP       (6250UL)   /* 6.25mV */
#define PCA9422_BUCK3_OUT_MAX        (1975000U) /* 1975mV */
#define PCA9422_BUCK3_OUT_VAL(_volt) (((_volt) - PCA9422_BUCK3_OUT_MIN) / PCA9422_BUCK3_OUT_STEP)
#define PCA9422_BUCK3_OUT_VOLT(_val) (((_val) * PCA9422_BUCK3_OUT_STEP) + PCA9422_BUCK3_OUT_MIN)

/*! @brief PCA9422 LDO2/3 output capacitor selection definition. */
typedef enum _pca9422_ldo23_csel
{
    kPCA9422_LDO23CoutLess5uF       = 0x00U, /* Setting for Cout < 5uF */
    kPCA9422_LDO23CoutHigh5uF       = 0x40U, /* Setting for Cout > 5uF */
    kPCA9422_LDO23AutoCoutDetection = 0x80U, /* Auto Cout detection */
} pca9422_ldo23_csel_t;

/*! @brief PCA9422 LDO2/3 output trace resistance compensation definition. */
typedef enum _pca9422_ldo23_llsel
{
    kPCA9422_LDO23LLSelNoComp = 0x00U, /* No Compensation */
    kPCA9422_LDO23LLSel15mOhm = 0x10U, /* 15mOhm */
    kPCA9422_LDO23LLSel30mOhm = 0x20U, /* 30mOhm */
    kPCA9422_LDO23LLSel45mOhm = 0x30U, /* 45mOhm */
} pca9422_ldo23_llsel_t;

/*! @brief PCA9422 LDO2/3 power mode definition. */
typedef enum _pca9422_ldo23_lpmode
{
    kPCA9422_LDO23LPmodeAtRunState         = 0x00U,
    kPCA9422_LDO23LPmodeAtStandbyDPStandby = 0x04U,
    kPCA9422_LDO23LPmodeAtDPStandby        = 0x08U,
    kPCA9422_LDO23LPmodeNormal             = 0x0CU,
} pca9422_ldo23_lpmode_t;

/*! @brief PCA9422 LDO2/3 Load Switch mode definition. */
typedef enum _pca9422_ldo23_mode
{
    kPCA9422_LDO23LDOMode        = 0x00U,
    kPCA9422_LDO23LoadSwitchMode = 0x01U,
} pca9422_ldo23_mode_t;

/*! @brief PCA9422 LDO1 OUT voltage definition. (uV unit) */
#define PCA9422_LDO1_OUT_MIN        (800000U)  /* 800mV */
#define PCA9422_LDO1_OUT_STEP       (25000U)   /* 25mV */
#define PCA9422_LDO1_OUT_MAX        (3000000U) /* 3000mV */
#define PCA9422_LDO1_OUT_VAL(_volt) (((_volt) - PCA9422_LDO1_OUT_MIN) / PCA9422_LDO1_OUT_STEP)
#define PCA9422_LDO1_OUT_VOLT(_val) (((_val) * PCA9422_LDO1_OUT_STEP) + PCA9422_LDO1_OUT_MIN)

/*! @brief PCA9422 LDO2/3 OUT voltage definition. (uV unit) */
#define PCA9422_LDO23_OUT_MIN        (500000U)  /* 500mV */
#define PCA9422_LDO23_OUT_STEP       (25000U)   /* 25mV */
#define PCA9422_LDO23_OUT_MAX        (1950000U) /* 1950mV */
#define PCA9422_LDO23_OUT_VAL(_volt) (((_volt) - PCA9422_LDO23_OUT_MIN) / PCA9422_LDO23_OUT_STEP)
#define PCA9422_LDO23_OUT_VOLT(_val) (((_val) * PCA9422_LDO23_OUT_STEP) + PCA9422_LDO23_OUT_MIN)

/*! @brief PCA9422 LDO4 OUT voltage definition. (uV unit) */
#define PCA9422_LDO4_OUT_MIN        (800000U)  /* 800mV */
#define PCA9422_LDO4_OUT_STEP       (25000U)   /* 25mV */
#define PCA9422_LDO4_OUT_MAX        (3300000U) /* 3300mV */
#define PCA9422_LDO4_OUT_VAL(_volt) (((_volt) - PCA9422_LDO4_OUT_MIN) / PCA9422_LDO4_OUT_STEP)
#define PCA9422_LDO4_OUT_VOLT(_val) (((_val) * PCA9422_LDO4_OUT_STEP) + PCA9422_LDO4_OUT_MIN)

/*! @brief PCA9422 Buck-Boost FPWM mode definition. */
typedef enum _pca9422_bb_fpwm_mode
{
    kPCA9422_BBAutoPFMandPWM = 0x00U, /* Automatic PFM and PWM mode transition */
    kPCA9422_BBForcedPWM     = 0x08U, /* Forced PWM mode */
} pca9422_bb_fpwm_mode_t;

/*! @brief PCA9422 Buck-Boost overcurrent response definition. */
typedef enum _pca9422_bb_fault_oc_ctrl
{
    kPCA9422_BBNotTurnOff = 0x00U,
    kPCA9422_BBTurnOff    = 0x04U,
} pca9422_bb_fault_oc_ctrl_t;

/*! @brief PCA9422 Buck-Boost active discharge control definition. */
typedef enum _pca9422_bb_soft_stdn
{
    kPCA9422_BBRampDownDisabled = 0x00U, /* Digital ramping down Vout is disabled */
    kPCA9422_BBRampDownEnabled  = 0x02U, /* Digital ramping down Vout is enabled */
} pca9422_bb_soft_stdn_t;

/*! @brief PCA9422 Buck-Boost passive discharge control definition. */
typedef enum _pca9422_bb_dis
{
    kPCA9422_BBPassiveDsgDisabled = 0x00U,
    kPCA9422_BBPassiveDsgEnabled  = 0x01U,
} pca9422_bb_dis_t;

/*! @brief PCA9422 Buck-Boost enable in RUN state definition. */
typedef enum _pca9422_bb_enable_in_run
{
    kPCA9422_BBOffInRunState = 0x00U,
    kPCA9422_BBOnInRunState  = 0x40U,
} pca9422_bb_enable_in_run_t;

/*! @brief PCA9422 Buck-Boost operation mode definition. */
typedef enum _pca9422_bb_mode
{
    kPCA9422_BBOPmodeAuto            = 0x00U, /* Auto */
    kPCA9422_BBOPmodeForcedBoostOnly = 0x10U, /* Forced BOOST only */
    kPCA9422_BBOPmodeForcedBuckOnly  = 0x20U, /* Forced BUCK only */
} pca9422_bb_mode_t;

/*! @brief PCA9422 Buck-Boost Enable mode definition. */
typedef enum _pca9422_bb_enmode
{
    kPCA9422_BBEnmodeOnAll                = 0x00U,
    kPCA9422_BBEnmodeOnActiveSleepStandby = 0x04U,
    kPCA9422_BBEnmodeOnActiveSleep        = 0x08U,
    kPCA9422_BBEnmodeOnActive             = 0x0CU,
} pca9422_bb_enmode_t;

/*! @brief PCA9422 Buck-Boost power mode definition. */
typedef enum _pca9422_bb_lpmode
{
    kPCA9422_BBLPmodeNormal             = 0x00U,
    kPCA9422_BBLPmodeAtStandbyDPStandby = 0x01U,
    kPCA9422_BBLPmodeAtDPStandby        = 0x02U,
    kPCA9422_BBLPmodeForcedLPM          = 0x03U,
} pca9422_bb_lpmode_t;

/*! @brief PCA9422 Regulator power mode definition. */
typedef enum _pca9422_reg_lpmode
{
    kPCA9422_LPmodeNormal             = 0x00U,
    kPCA9422_LPmodeAtStandbyDPStandby = 0x01U,
    kPCA9422_LPpmodeAtDPstandby       = 0x02U,
    kPCA9422_LPmodeForcedLPM          = 0x03U,
} pca9422_reg_lpmode_t;

/*! @brief PCA9422 Buck-Boost OUT voltage definition. (uV unit) */
#define PCA9422_BB_OUT_MIN        (1800000U) /* 1800mV */
#define PCA9422_BB_OUT_STEP       (25000U)   /* 25mV */
#define PCA9422_BB_OUT_MAX        (5000000U) /* 5000mV */
#define PCA9422_BB_OUT_VAL(_volt) (((_volt) - PCA9422_BB_OUT_MIN) / PCA9422_BB_OUT_STEP)
#define PCA9422_BB_OUT_VOLT(_val) (((_val) * PCA9422_BB_OUT_STEP) + PCA9422_BB_OUT_MIN)

/*! @brief PCA9422 Regulator Voltage definition. */
typedef enum _pca9422_vout
{
    kPCA9422_RegVout        = 0x00U,
    kPCA9422_RegSleepVout   = 0x01U,
    kPCA9422_RegStandbyVout = 0x02U,
    kPCA9422_SWMaxVout      = 0x03U,
    kPCA9422_BBMinVout      = 0x04U,
    kPCA9422_SWDVS0Vout     = 0x05U,
    kPCA9422_SWDVS1Vout     = 0x06U,
    kPCA9422_SWDVS2Vout     = 0x07U,
    kPCA9422_SWDVS3Vout     = 0x08U,
    kPCA9422_SWDVS4Vout     = 0x09U,
    kPCA9422_SWDVS5Vout     = 0x0AU,
    kPCA9422_SWDVS6Vout     = 0x0BU,
    kPCA9422_SWDVS7Vout     = 0x0CU,
} pca9422_vout_t;

/*! @brief PCA9422 LED enable definition. */
typedef enum _pca9422_led_en
{
    kPCA9422_LedEnDisable = 0x00U,
    kPCA9422_LedEnEnable  = 0x80U,
} pca9422_led_en_t;

/*! @brief PCA9422 LED control definition. */
typedef enum _pca9422_led_ovrd
{
    kPCA9422_LedControlByStateMachine = 0x00U,
    kPCA9422_LedControlBySoftware     = 0x20U,
} pca9422_led_ovrd_t;

/*! @brief PCA9422 Output voltage configuration lock definition. */
typedef enum _pca9422_reg_lock
{
    kPCA9422_RegLockUnlockKey = 0x5CU,
    kPCA9422_RegLockLockKey   = 0x00U,
} pca9422_reg_lock_t;

/*! @brief PCA9422 Mode Configuration definition. */
typedef struct _pca9422_modecfg
{
    uint32_t sw1OutVolt;  /* uV */
    uint32_t sw2OutVolt;  /* uV */
    uint32_t sw3OutVolt;  /* uV */
    uint32_t sw4OutVolt;  /* uV */
    uint32_t ldo1OutVolt; /* uV */
    uint32_t ldo2OutVolt; /* uV */
    uint32_t ldo3OutVolt; /* uV */
    uint32_t ldo4OutVolt; /* uV */
} pca9422_modecfg_t;

/*! @brief PCA9422 Enmode Configuration definition */
typedef struct _pca9422_enmodecfg
{
    pca9422_enmode_t sw1OutEnMode;
    pca9422_enmode_t sw2OutEnMode;
    pca9422_enmode_t sw3OutEnMode;
    pca9422_enmode_t sw4OutEnMode;
    pca9422_enmode_t ldo1OutEnMode;
    pca9422_enmode_t ldo2OutEnMode;
    pca9422_enmode_t ldo3OutEnMode;
    pca9422_enmode_t ldo4OutEnMode;
} pca9422_enmodecfg_t;

/*! @brief PCA9422 Enable configuration definition */
typedef struct _pca9422_enablecfg
{
    bool enableSw1Out;
    bool enableSw2Out;
    bool enableSw3Out;
    bool enableSw4Out;
    bool enableLdo1Out;
    bool enableLdo2Out;
    bool enableLdo3Out;
    bool enableLdo4Out;
} pca9422_enablecfg_t;

/*! @brief PCA9422 Regulator Enable in RUN state definition */
typedef struct _pca9422_regultoren
{
    bool sw1Enable;
    bool sw2Enable;
    bool sw3Enable;
    bool sw4Enable;
    bool ldo1Enable;
    bool ldo2Enable;
    bool ldo3Enable;
    bool ldo4Enable;
} pca9422_regulatoren_t;

/*! @brief PCA9422 Handle definition. */
typedef struct _pca9422_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    status_t (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    status_t (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* The I2C Slave Address Read From OTP. */
    uint8_t slaveAddress;
} pca9422_handle_t;

/*! @brief PCA9422 Configuration Structure definition. */
/*! @brief PCA9422 Charger Configuration Structure definition. */
typedef struct _pca9422_charger_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    status_t (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    status_t (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* Charge current */
    /* Precharge current */
    pca9422_prechg_i_t prechgI;
    /* Charging current step */
    pca9422_chg_i_step_t chgIStep;
    /* Top-off current */
    pca9422_topoff_i_t topoffI;
    /* Fast Charge current */
    uint16_t fastI;
    /* Charging voltage */
    /* VBAT float voltage */
    uint16_t vbatReg;
    /* Recharge threshold */
    pca9422_recharge_th_t rechgVolt;
    /* Charging timer */
    /* Precharge timer - refer _pca9422_precharge_timer */
    pca9422_precharge_timer_t prechgTime;
    /* Fast charge timer - refer _pca9422_fast_chg_timer  */
    pca9422_fast_chg_timer_t fastchgTime;
    /* Top-off timer */
    pca9422_top_off_timer_t topoffTime;
    /* JEITA parameters */
    /* Warm voltage threshold - 45C, refer _pca9422_v_warm */
    pca9422_v_warm_45c_t warmVolt;
    /* Warm plus voltage threshold - 50C, refer _pca9422_v_warm */
    pca9422_v_warm_50c_t warmPlusVolt;
    /* Hot voltage threshold - 60C */
    pca9422_v_hot_60c_t hotVolt;
    /* Cool voltage threshold - 10C */
    pca9422_v_cool_10c_t coolVolt;
    /* Cold voltage threshold - 0C */
    pca9422_v_cold_0c_t coldVolt;
    /* New regulation voltage - Warm(45C) */
    pca9422_new_vbat_45c_t warmVbatReg;
    /* New regulation voltage - Warm plus(50C) */
    pca9422_new_vbat_50c_t warmPlusVbatReg;
    /* New Fast charge current - Cold(10C) */
    pca9422_new_i_vbat_10c_t coldIVbat;
    /* New Fast charge current - Warm(45C) */
    pca9422_new_i_vbat_45c_t warmIVbat;
    /* New Fast charge current - Warm plus(50C) */
    pca9422_new_i_vbat_50c_t warmPlusIVbat;
    /* AICL threshold */
    pca9422_aicl_v_t aiclV;
    /* Input current limit */
    pca9422_chgin_ilim_t icl;
    /* VSYS regulation voltage */
    uint16_t vsysReg;
    /* AMUX wait time */
    pca9422_amux_auto_off_wait_t amuxWaitTime;
    /* AMUX mode */
    pca9422_amux_mode_t amuxMode;
    /* VBAT/VSYS channel scale factor */
    pca9422_amux_vbat_vsys_gain_t amuxVbatGain;
    /* THERM and THERM_BIAS channels scale factor */
    pca9422_amux_therm_gain_t amuxThermGain;
    /* AMUX channel */
    pca9422_amux_channel_t amuxChannel;
    /* The PCA9422 I2C Slave Address. */
    uint8_t slaveAddress;
} pca9422_charger_config_t;

/*! @brief PCA9422 Regulator Configuration Structure definition. */
/*! @brief PCA9422 Buck Configuration Structure definition. */
typedef struct _pca9422_buck_config
{
    uint8_t dvsUpStep;
    uint8_t dvsDnStep;
    uint8_t dvsCtrl;
    pca9422_bx_ramp_t rampSpeed;
    pca9422_bx_lpmode_t lpMode;
    pca9422_bx_ad_t activeDischg;
    pca9422_bx_fpwm_mode_t fpwmEn;
    pca9422_enmode_t enMode;
    uint32_t dvsVout[8];
    uint32_t stbyVout;
    uint32_t maxVout;
    uint32_t sleepVout;
} pca9422_buck_config_t;

/*! @brief PCA9422 LDO2/3/4 Configuration Structure definition. */
typedef struct _pca9422_ldo234_config
{
    pca9422_ldo23_csel_t cSel;
    pca9422_ldo23_llsel_t llSel;
    pca9422_ldo23_lpmode_t lpMode;
    pca9422_enmode_t enMode;
    pca9422_ldo23_mode_t ldoMode;
    bool activeDischg;
    uint32_t vout;
    uint32_t stbyVout;
    uint32_t sleepVout;
} pca9422_ldo234_config_t;

/*! @brief PCA9422 LDO1 Configuration Structure definition. */
typedef struct _pca9422_ldo1_config
{
    bool activeDischg;
    bool enMode;
    uint32_t vout;
} pca9422_ldo1_config_t;

/*! @brief PCA9422 Buck-Boost Configuration Structure definition. */
typedef struct _pca9422_bb_config
{
    pca9422_bb_fpwm_mode_t fpwmEn;
    pca9422_bb_fault_oc_ctrl_t ocCtrl;
    pca9422_bb_soft_stdn_t softStdn;
    pca9422_bb_dis_t passiveDis;
    pca9422_bb_enable_in_run_t enInRun;
    pca9422_bb_mode_t bbMode;
    pca9422_bb_enmode_t enMode;
    pca9422_bb_lpmode_t lpMode;
    uint32_t vout;
    uint32_t stdyVout;
    uint32_t maxVout;
    uint32_t minVout;
    uint32_t sleepVout;
} pca9422_bb_config_t;

typedef struct _pca9422_regulator_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    status_t (*I2C_SendFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
    /* Pointer to the user-defined I2C Receive Data function. */
    status_t (*I2C_ReceiveFunc)(
        uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
    /* Standby Control */
    pca9422_standby_ctrl_t standbyCtrl;
    /* Standby configuration bit */
    pca9422_standby_cfg_t standbyCfg;
    /* DVS_CTRL2 pin enable bit */
    pca9422_dvs_ctrl2_en_t dvsCtrl2En;
    /* VSYS UVLO threshold */
    pca9422_vsys_uvlo_sel_t vsysUvlo;
    /* DVS smart mode */
    pca9422_smart_mode_t smartMode;
    /* Buck1/2/3 configuration */
    pca9422_buck_config_t buck[3];
    /* LDO2/3/4 configuration */
    pca9422_ldo234_config_t ldo[3];
    /* LDO1 configuration */
    pca9422_ldo1_config_t ldo1;
    /* Buck-Boost configuration */
    pca9422_bb_config_t buckBoost;
    /* The PCA9422 I2C Slave Address. */
    uint8_t slaveAddress;
} pca9422_regulator_config_t;

/*!
 * @addtogroup pca9422
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and Control function
 * @{
 */

/*!
 * @brief Gets the default configuration structure for charger.
 *
 * This function initializes the PCA9422 charger configuration structure to default values. The default
 * values are as follows.

 *   config->I2C_SendFunc     = NULL;
 *   config->I2C_ReceiveFunc  = NULL;
 *   config->prechgI          = kPCA9422_PrechgI20percent;
 *   config->chgIStep         = kPCA9422_ChgIStep2p5mA;
 *   config->topoffI          = kPCA9422_TopoffI2p5percent;
 *   config->fastI            = 100U;
 *   config->vbatReg          = 4200U;
 *   config->rechgVolt        = kPCA9422_RechargeTh100mV;
 *   config->prechgTime       = kPCA9422_PrechgTimer30min;
 *   config->fastchgTime      = kPCA9422_FastchgTimer3h;
 *   config->topoffTime       = kPCA9422_TopoffTimer5min;
 *   config->warmVolt         = kPCA9422_Vwarm45C32p63percent;
 *   config->warmPlusVolt     = kPCA9422_Vwarm50C29p07percent;
 *   config->hotVolt          = kPCA9422_Vhot60C22p94percent;
 *   config->coolVolt         = kPCA9422_Vcool10C64p82percent;
 *   config->coldVolt         = kPCA9422_Vcold0C74p18percent;
 *   config->warmVbatReg      = kPCA9422_NewVbat45C_StayVbatReg;
 *   config->warmPlusVbatReg  = kPCA9422_NewVbat50C_StayVbatReg;
 *   config->coldIVbat        = kPCA9422_NewIVbat10C_StayIFastchg;
 *   config->warmIVbat        = kPCA9422_NewIVbat45C_StayIFastchg;
 *   config->warmPlusIVbat    = kPCA9422_NewIVbat50C_StayIFastchg;
 *   config->aiclV            = kPCA9422_AICLV4p5V;
 *   config->icl              = kPCA9422_ChgInIlim_470mA;
 *   config->vsysReg          = 4550U;
 *   config->amuxWaitTime     = kPCA9422_AMUXAutoOffWait_256us;
 *   config->amuxMode         = kPCA9422_AMUXModeManual;
 *   config->amuxVbatGain     = kPCA9422_AMUXVbatVsysGain_1dvd3;
 *   config->amuxThermGain    = kPCA9422_AMUXThermGain_1;
 *   config->amuxChannel      = kPCA9422_AMUXChannel_Off;
 *   config->slaveAddress     = PCA9422_DEFAULT_I2C_ADDR;
 *
 * @param config Pointer to the PCA9422 configuration structure for charger.
 */
void PCA9422_GetChargerDefaultConfig(pca9422_charger_config_t *config);

/*!
 * @brief Initializes a PCA9422 charger instance.
 *
 * This function initializes the PCA9422 battery charger with user-defined settings.
 * This example shows how to set up the pca9422_config_t parameters and how
 * to call the PCA9422_Init function by passing in these parameters.
 * @code
 *   pca9422_config_t pca9422Config;
 *   PCA9422_GetDefaultConfig(&pca9422Config);
 *   pca9422Config.I2C_SendFunc    = APP_I2C_SendFunc;
 *   pca9422Config.I2C_ReceiveFunc = APP_I2C_ReceiveFunc;
 *   PCA9422_Init(&pca9422Handle, &pca9422Config);
 * @endcode
 *
 * @param handle PCA9422 Handle.
 * @param config Pointer to the user-defined configuration structure.
 */
void PCA9422_InitCharger(pca9422_handle_t *handle, const pca9422_charger_config_t *config);
/* @} */

/*!
 * @brief Set Precharge Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param iPrechg Precharge current(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetPreChargeCurrent(pca9422_handle_t *handle, uint8_t iPrechg);

/*!
 * @brief Get Precharge Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return Precharge current(register value).
 */
uint8_t PCA9422_GetPreChargeCurrent(pca9422_handle_t *handle);

/*!
 * @brief Get Topoff Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return Topoff current(register value).
 */
uint8_t PCA9422_GetTopoffCurrent(pca9422_handle_t *handle);

/*!
 * @brief Set Topoff Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param iTopoff Topoff current(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetTopoffCurrent(pca9422_handle_t *handle, uint8_t iTopoff);

/*!
 * @brief Set Fast Charge Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param iFast Fast charge current(mA*10).
 * @return true if success or false if error.
 */
bool PCA9422_SetFastChargeCurrent(pca9422_handle_t *handle, uint16_t iFast);

/*!
 * @brief Get Fast Charge Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return current Fast charge current(mA*10).
 */
uint16_t PCA9422_GetFastChargeCurrent(pca9422_handle_t *handle);

/*!
 * @brief Get Charge Current of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return current charge current(mA).
 */
uint16_t PCA9422_GetChargeCurrent(pca9422_handle_t *handle);
/*!
 * @brief Get VBAT regulation voltage of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return vFloat VBAT floating(regulation) voltage(mV).
 */
uint16_t PCA9422_GetVBATRegulation(pca9422_handle_t *handle);

/*!
 * @brief Set VBAT regulation voltage of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param vFloat VBAT floating(regulation) voltage(mV).
 * @return true if success or false if error.
 */
bool PCA9422_SetVBATRegulation(pca9422_handle_t *handle, uint16_t vFloat);

/*!
 * @brief Set recharge threshold voltage of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param rechgTh Recharge threshold(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetRechargeThreshold(pca9422_handle_t *handle, uint8_t rechgTh);

/*!
 * @brief Set precharge timer of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param tPrechg Precharge Timer(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetPrechargeTimer(pca9422_handle_t *handle, uint8_t tPrechg);

/*!
 * @brief Set fast charge timer of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param tFastchg Fast charge Timer(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetFastchargeTimer(pca9422_handle_t *handle, uint8_t tFastchg);

/*!
 * @brief Set topoff timer of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param tTopoff Topoff Timer(register value).
 * @return true if success or false if error.
 */
bool PCA9422_SetTopoffTimer(pca9422_handle_t *handle, uint8_t tTopoff);

/*!
 * @brief Get Charge State of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return charge state.
 *         0 - No charge
 *         0x01 - Charging On (Fast Charge or Prehcarge state)
 *         0x02 - Constant Voltage or Topoff state
 *         0x04 - Charge Done state
 */
uint8_t PCA9422_GetChargeState(pca9422_handle_t *handle);

/*!
 * @brief Select AMUX channel of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param amuxCh AMUX channel.
 */
void PCA9422_SelectAMUXChannel(pca9422_handle_t *handle, pca9422_amux_channel_t amuxCh);

/*!
 * @brief Set AMUX mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param mode AMUX mode.
 */
void PCA9422_SetAMUXMode(pca9422_handle_t *handle, pca9422_amux_mode_t mode);

/*!
 * @brief Get AMUX mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @return AMUX mode if success or 0xFF if error.
 */
pca9422_amux_mode_t PCA9422_GetAMUXMode(pca9422_handle_t *handle);

/*!
 * @brief Set AMUX configuration of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param config AMUX configuration.
 * @return true if success or false if error.
 */
bool PCA9422_SetAMUXConfig(pca9422_handle_t *handle, pca9422_amux_config_t config);

/*!
 * @brief Get AMUX scale factor for each channel of PCAA9422.
 *
 * @param handle PCA9422 Handle.
 * @param channel AMUX channel.
 * @return scalefactor Scale factor for the channel.
 */
float PCA9422_GetAMUXScaleFactor(pca9422_handle_t *handle, pca9422_amux_channel_t channel);

/*!
 * @brief Set Enable or Disable charge of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param enable if enable is 1 and disable is 0.
 * @return true if success or false if error.
 */
bool PCA9422_SetEnableCharge(pca9422_handle_t *handle, bool enable);

/*!
 * @brief Set Enable or Disable USB suspend Mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param enable if enable is 1 and disable is 0.
 * @return true if success or false if error.
 */
bool PCA9422_SetUSBSuspendMode(pca9422_handle_t *handle, bool enable);

/*!
 * @name Initialization and Control function for regulators
 * @{
 */
/*!
 * @brief Gets the default configuration structure for regulators.
 *
 * This function initializes the PCA9422 regulator configuration structure to default values. The default
 * values are as follows.
 *
 *   pca9422RegConfig->I2C_SendFunc    = NULL;
 *   pca9422RegConfig->I2C_ReceiveFunc = NULL;
 *   pca9422RegConfig->standbyCtrl     = kPCA9422_StandbyCtrlPins;
 *   pca9422RegConfig->standbyCfg      = kPCA9422_StandbyCfgStandby;
 *   pca9422RegConfig->dvsCtrl2En      = kPCA9422_DVSCtrl2EnIgnore;
 *   pca9422RegConfig->vsysUvlo        = kPCA9422_VsysUvloSel2p7V;
 *   pca9422RegConfig->smartMode       = kPCA9422_SmartModeDisabled;
 *   pca9422RegConfig->buck            = *buck;
 *   pca9422RegConfig->ldo             = *ldo;
 *   pca9422RegConfig->ldo1            = ldo1;
 *   pca9422RegConfig->buckBoost       = buckBoost;
 *   pca9422RegConfig->slaveAddress    = PCA9422_DEFAULT_I2C_ADDR;
 *
 * @param RegConfig Pointer to the PCA9422 configuration structure for regulator.
 */
void PCA9422_GetRegulatorDefaultConfig(pca9422_regulator_config_t *RegConfig);

/*!
 * @brief Initializes a PCA9422 instance.
 *
 * This function initializes the PCA9422 regulator with user-defined settings.
 * This example shows how to set up the pca9422_regulator_config_t parameters and
 * how to call the PCA9422_RegInit function by passing in these parameters.
 * @code
 *   pca9422_regulator_config_t pca9422RegConfig;
 *   PCA9422_GetRegDefaultConfig(&pca9422RegConfig);
 *   pca9422RegConfig.I2C_SendFunc    = APP_I2C_SendFunc;
 *   pca9422RegConfig.I2C_ReceiveFunc = APP_I2C_ReceiveFunc;
 *   PCA9422_RegInit(&pca9422Handle, &pca9422RegConfig);
 * @endcode
 *
 * @param handle PCA9422 Handle.
 * @param config Pointer to the user-defined configuration structure for regulator.
 */
void PCA9422_InitRegulator(pca9422_handle_t *handle, const pca9422_regulator_config_t *config);

/*!
 * @brief Gets the default mode configuration structure.
 *
 * This function initializes the PCA9422 mode configuration structure to default values.
 * The default values are as follows.
 *
 *   config->sw1OutVolt         = 1000000;
 *   config->sw2OutVolt         = 1100000;
 *   config->sw3OutVolt         = 1000000;
 *   config->sw4OutVolt         = 1800000;
 *   config->ldo1OutVolt        = 1800000;
 *   config->ldo2OutVolt        = 1800000;
 *   config->ldo3OutVolt        = 1200000;
 *   config->ldo4OutVolt        = 3300000;
 *
 * @param config Pointer to the PCA9422 mode configuration structure.
 */
void PCA9422_GetDefaultPowerModeConfig(pca9422_modecfg_t *config);

/*!
 * @brief Gets the default enmode configuration structure.
 *
 * This function initializes the PCA9422 enmode configuration structure to default values.
 * The default values are as follows.
 *
 *   enModeCfg->sw1OutEnMode  = kPCA9422_EnmodeOnAll;
 *   enModeCfg->sw2OutEnMode  = kPCA9422_EnmodeOnAll;
 *   enModeCfg->sw3OutEnMode  = kPCA9422_EnmodeOnAll;
 *   enModeCfg->sw4OutEnMode  = kPCA9422_EnmodeOnAll;
 *   enModeCfg->ldo1OutEnMode = kPCA9422_EnmodeOnAll;
 *   enModeCfg->ldo2OutEnMode = kPCA9422_EnmodeOnAll;
 *   enModeCfg->ldo3OutEnMode = kPCA9422_EnmodeOnAll;
 *   enModeCfg->ldo4OutEnMode = kPCA9422_EnmodeOnAll;
 *
 * @param enModeCfg Pointer to the PCA9422 enmode configuration structure.
 */
void PCA9422_GetDefaultEnModeConfig(pca9422_enmodecfg_t *enModeCfg);

/*!
 * @brief Gets the default regulator enable configuration structure in RUN state.
 *
 * This function initializes the PCA9422 regulator enable configuration structure in RUN state to default values.
 * The default values are as follows.
 *
 *   regEnCfg->sw1Enable       = true;
 *   regEnCfg->sw2Enable       = true;
 *   regEnCfg->sw3Enable       = true;
 *   regEnCfg->sw4Enable       = true;
 *   regEnCfg->ldo1Enable      = true;
 *   regEnCfg->ldo2Enable      = true;
 *   regEnCfg->ldo3Enable      = true;
 *   regEnCfg->ldo4Enable      = true;
 *
 * @param regEnCfg Pointer to the PCA9422 regulator enable configuration structure in RUN state.
 */
void PCA9422_GetDefaultRegEnableConfig(pca9422_regulatoren_t *regEnCfg);

/*!
 * @brief Gets the default buck config structure.
 *
 * This function initializes the PCA9422 buck config structure to default values. The default
 * values are as follows.
 *
 *   buckCfg->dvs_up_step   = 0;
 *   buckCfg->dvs_dn_step   = 0;
 *   buckCfg->dvs_ctrl      = kPCA9422_Bx_dvs_ctrl_i2c_in_active_sleep;
 *   buckCfg->ramp_speed    = kPCA9422_Bx_ramp_25mVp2us;
 *   buckCfg->lpmode        = kPCA9422_Bx_lpmode_normal;
 *   buckCfg->active_dischg = kPCA9422_Bx_enable_ad;
 *   buckCfg->fpwm_en       = kPCA9422_Bx_fpwm_auto;
 *   buckCfg->enmode        = kPCA9422_Reg_Enmode_on_all;
 *   buckCfg->dvs_vout[8]   = *dvs;
 *   buckCfg->stby_vout     = bx_standby_vout;
 *   buckCfg->max_vout      = bx_max_vout;
 *   buckCfg->sleep_vout    = bx_sleep_vout;
 *
 * @param buckCfg Pointer to the PCA9422 buck configuration structure.
 */
void PCA9422_GetDefaultBuckConfig(pca9422_buck_config_t *buckCfg);

/*!
 * @brief Gets the default LDO2/3/4 config structure.
 *
 * This function initializes the PCA9422 LDO2/3/4 config structure to default values. The default
 * values are as follows.
 *
 *   ldoCfg->csel          = kPCA9422_LDO23_csel_auto_cout_detection;
 *   ldoCfg->llsel         = kPCA9422_LDO23_llsel_15mOhm;
 *   ldoCfg->lpmode        = kPCA9422_LDO23_lpmode_normal;
 *   ldoCfg->ldo_mode      = kPCA9422_LDO23_mode_ldo;
 *   ldoCfg->active_dischg = true;
 *   ldoCfg->vout          = ldox_vout;
 *   ldoCfg->stby_vout     = ldox_stdy_vout;
 *   ldoCfg->sleep_vout    = ldox_sleep_vout;
 *
 * @param ldoCfg Pointer to the PCA9422 ldo234 configuration structure.
 */
void PCA9422_GetDefaultLDO234Config(pca9422_ldo234_config_t *ldoCfg);

/*!
 * @brief Gets the default LDO1 config structure.
 *
 * This function initializes the PCA9422 LDO1 config structure to default values. The default
 * values are as follows.

 bool active_dischg;
 bool enmode;
 uint32_t vout;
 *
 *   ldo1Cfg->active_dischg = true;
 *   ldo1Cfg->enmode        = true;
 *   ldo1Cfg->vout          = 1800000;
 *
 * @param ldo1Cfg Pointer to the PCA9422 LDO1 configuration structure.
 */
void PCA9422_GetDefaultLDO1Config(pca9422_ldo1_config_t *ldo1Cfg);

/*!
 * @brief Gets the default buck-boost config structure.
 *
 * This function initializes the PCA9422 buck-boost config structure to default values. The default
 * values are as follows.
 *
 *   bbCfg->fpwm_en     = kPCA9422_BB_fpwm_auto;
 *   bbCfg->oc_ctrl     = kPCA9422_BB_fault_oc_ctrl_not_turn_off;
 *   bbCfg->soft_stdn   = kPCA9422_BB_soft_stdn_disabled;
 *   bbCfg->passive_dis = kPCA9422_BB_dis_enabled;
 *   bbCfg->en_in_run   = kPCA9422_BB_enable_in_run_on;
 *   bbCfg->bb_mode     = kPCA9422_BB_mode_auto;
 *   bbCfg->enmode      = kPCA9422_BB_enmode_on_all;
 *   bbCfg->lpmode      = kPCA9422_BB_lpmode_normal;
 *   bbCfg->vout        = 5000000;
 *   bbCfg->stby_vout   = 5000000;
 *   bbCfg->max_vout    = 5000000;
 *   bbCfg->min_vout    = 4500000;
 *   bbCfg->sleep_vout  = 5000000;
 *
 * @param bbCfg Pointer to the PCA9422 buck-boost configuration structure.
 */
void PCA9422_GetDefaultBBConfig(pca9422_bb_config_t *bbCfg);

/*!
 * @brief Gets the current regulator enable mode.
 *
 * This function gets the current regulator enable mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param enmode Enable mode of regulator.
 */
void PCA9422_GetRegulatorEnMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_enmode_t *enmode);

/*!
 * @brief Sets the current regulator enable mode.
 *
 * This function sets the current regulator enable mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param enmode Enable mode of regulator.
 */
void PCA9422_SetRegulatorEnMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_enmode_t enmode);

/*!
 * @brief Get LDO1 enable mode.
 *
 * This function get LDO1 enable mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param enmode Enable mode of regulator.
 */
void PCA9422_GetLDO1EnMode(pca9422_handle_t *handle, bool *enmode);

/*!
 * @brief Sets LDO1 enable mode.
 *
 * This function sets LDO1 enable mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param enmode Enable mode of regulator.
 */
void PCA9422_SetLDO1EnMode(pca9422_handle_t *handle, bool enmode);

/*!
 * @brief Gets the current regulator power mode.
 *
 * This function gets the current regulator power mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param lpmode Power mode of regulator.
 */
void PCA9422_GetRegulatorLPMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_reg_lpmode_t *lpmode);

/*!
 * @brief Sets the current regulator power mode.
 *
 * This function sets the current regulator power mode of PCA9422.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param lpmode Power mode of regulator.
 */
void PCA9422_SetRegulatorLPMode(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_reg_lpmode_t lpmode);

/*!
 * @brief Sets voltage value in uV for vout mode.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param vout Vout type of PCA9422.
 * @param volt Regulator voltage in uV of PCA9422.
 */
void PCA9422_SetRegulatorVoltage(pca9422_handle_t *handle, pca9422_regulator_t reg, pca9422_vout_t vout, uint32_t volt);

/*!
 * @brief Gets voltage value in uV for vout mode.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param vout Vout type of PCA9422.
 * @param volt Regulator voltage in uV of PCA9422.
 */
void PCA9422_GetRegulatorVoltage(pca9422_handle_t *handle,
                                 pca9422_regulator_t reg,
                                 pca9422_vout_t vout,
                                 uint32_t *volt);

/*!
 * @brief Get PCA9422 SW1, SW2, SW3, SW4, LDO1, LDO2, LDO3, LDO4 OK status.
 *
 * This function return the PCA9422 regulators status.
 *
 * @param handle PCA9422 Handle.
 * @return ORed regulator status. see @ref pca9422_reg_status_t for regulator status definition.
 */
uint8_t PCA9422_GetRegulatorStatus(pca9422_handle_t *handle);

/*!
 * @brief Switch PCA9422 power mode.
 *
 * This function switch the PCA9422 regulators power mode with pin control.
 *
 * @param handle PCA9422 Handle.
 * @param mode Target power mode to go into.
 */
void PCA9422_SwitchPowerMode(pca9422_handle_t *handle, pca9422_power_mode_t mode);

/*!
 * @brief Get PCA9422 current power mode.
 *
 * This function returns the PCA9422 current power mode.
 *
 * @param handle PCA9422 Handle.
 * @param mode Current power mode.
 * @return true on success, false on failure.
 */
bool PCA9422_GetCurrentPowerMode(pca9422_handle_t *handle, pca9422_power_mode_t *mode);

/*!
 * @brief Get PCA9422 current EN mode.
 *
 * This function returns the PCA9422 current Enmode.
 *
 * @param handle PCA9422 Handle.
 * @param config Current Enmode configuration.
 */
void PCA9422_GetCurrentEnMode(pca9422_handle_t *handle, pca9422_enmodecfg_t *config);

/*!
 * @brief Get PCA9422 standby mode control.
 *
 * This function returns the PCA9422 standby mode control method.
 *
 * @param handle PCA9422 Handle.
 * @param ctrl Standby mode control.
 * @return true on success, false on failure.
 */
bool PCA9422_GetStandbyControl(pca9422_handle_t *handle, pca9422_standby_ctrl_t *ctrl);

/*!
 * @brief Sets Buck DVS control.
 *
 * @param handle PCA9422 Handle.
 * @param reg Buck Regulator
 * @param dvsCtrl Buck DVS control method.
 */
void PCA9422_SetBuckDVSControl(pca9422_handle_t *handle, pca9422_regulator_t reg, uint8_t dvsCtrl);

/*!
 * @brief Enable PCA9422 Regulator in Run state.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param enable true is enable, false is disabled.
 */
void PCA9422_SetEnableRegulatorRunState(pca9422_handle_t *handle, pca9422_regulator_t reg, bool enable);

/*!
 * @brief Get Enable PCA9422 Regulator status in Run state.
 *
 * @param handle PCA9422 Handle.
 * @param reg Regulator of PCA9422.
 * @param enable true is enable, false is disabled.
 */
void PCA9422_GetEnableRegulatorRunState(pca9422_handle_t *handle, pca9422_regulator_t reg, bool *enable);

/*!
 * @brief Read PCA9422 power mode configurations for specific modes.
 *
 * This function read the PCA9422 mode configurations for specific modes with
 * user-defined settings.
 *
 * @param handle PCA9422 Handle.
 * @param powerMode Target mode to read.
 * @param configs Pointer to the configuration to save read information.
 */
void PCA9422_ReadPowerModeConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_modecfg_t *configs);

/*!
 * @brief Write PCA9422 power mode configurations for specific modes.
 *
 * This function write the PCA9422 mode configurations for specific modes with
 * user-defined settings.
 *
 * @param handle PCA9422 Handle.
 * @param powerMode Target mode to write.
 * @param configs Pointer to the configuration to save read information.
 */
void PCA9422_WritePowerModeConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_modecfg_t configs);

/*!
 * @brief Write PCA9422 enmode configurations for specific modes.
 *
 * This function write the PCA9422 enmode configurations for specific modes with
 * user-defined settings.
 *
 * @param handle PCA9422 Handle.
 * @param config Pointer to the configuration to save read information.
 */
void PCA9422_WriteEnModeConfig(pca9422_handle_t *handle, pca9422_enmodecfg_t config);

/*!
 * @brief Write PCA9422 Regulator enable configurations for run state.
 *
 * This function write the PCA9422 Regulator enable configurations for run state with
 * user-defined settings.
 *
 * @param handle PCA9422 Handle.
 * @param config Pointer to the configuration to save read information.
 */
void PCA9422_WriteRegEnableConfig(pca9422_handle_t *handle, pca9422_regulatoren_t config);

/*!
 * @brief Read PCA9422 regulator enable status for specific modes.
 *
 * This function read the PCA9422 enable status configurations for specific modes with
 * user-defined settings.
 *
 * @param handle PCA9422 Handle.
 * @param powerMode Target mode to read.
 * @param configs Pointer to the enable configuration to save read information.
 */
void PCA9422_ReadEnableConfigs(pca9422_handle_t *handle, pca9422_power_mode_t powerMode, pca9422_enablecfg_t *config);

/*!
 * @brief Feed PCA9422 watchdog.
 *
 * This function feed the PCA9422 watch dog.
 *
 * @param handle PCA9422 Handle.
 */
void PCA9422_FeedWatchDog(pca9422_handle_t *handle);

/*!
 * @brief Set PCA9422 watchdog timer.
 *
 * This function set PCA9422 watch dog timer.
 *
 * @param handle PCA9422 Handle.
 * @param wd_timer PCA9422 Watchdog timer.
 */
void PCA9422_SetWatchDogTimer(pca9422_handle_t *handle, pca9422_wd_timer_t wd_timer);
/* @} */

/*!
 * @name Basic register access functions
 * @{
 */

/*!
 * @brief Write the value to register array of PCA9422.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param regBase variable store base address of register array.
 * @param val variable array to be written to PCA9422.
 * @param size array length in bytes to write.
 * @return true if success or false if error.
 */
bool PCA9422_WriteRegs(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val, uint32_t size);

/*!
 * @brief Read the value of register array in PCA9422.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param regBase variable store address of register array.
 * @param val variable array to store return value.
 * @param size array length in bytes to read.
 * @return true if success or false if error.
 */
bool PCA9422_ReadRegs(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val, uint32_t size);

/*!
 * @brief Modify some bits in the register in PCA9422.
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param reg variable store address of register.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 1.
 * @param val Value needs to write into the register.
 * @return true if success or false if error.
 */
bool PCA9422_ModifyReg(pca9422_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

/*!
 * @brief Write the value to register in PCA9422 and read register to confirm it.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param regBase variable store base address of register array.
 * @param val value to be written to PCA9422.
 * @return true if success or false if error.
 */
bool PCA9422_WriteRegsReadback(pca9422_handle_t *handle, uint8_t regBase, uint8_t *val);

/*!
 * @brief Modify some bits in the register in PCA9422 and read register to confirm it.
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param reg variable store address of register.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 1.
 * @param val Value needs to write into the register.
 * @return true if success or false if error.
 */
bool PCA9422_ModifyRegReadback(pca9422_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);
/* @} */

/*!
 * @name Charger Interrupts
 * @{
 */

/*!
 * @brief Enables PCA9422 Charger interrupts according to the provided interrupt source mask.
 *
 * This function enables the PCA9422 interrupts according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt sources of selected interrupt category to enable.
 */
void PCA9422_EnableChargerInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Disable PCA9422 Charger interrupts according to the provided interrupt source mask.
 *
 * This function disables the PCA9422 interrupts according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt sources of selected interrupt category to disable.
 */
void PCA9422_DisableChargerInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Charger interrupt flags.
 *
 * This function gets charger interrupt flags.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to charger interrupt flags.
 */
void PCA9422_GetChargerInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Charger interrupt status flags.
 *
 * This function gets charger interrupt flags.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param status Pointer to charger interrupt status flags.
 */
void PCA9422_GetChargerInterruptStatus(pca9422_handle_t *handle, uint8_t *status);

/* @} */

/*!
 * @name Regulator Interrupt
 * @{
 */

/*!
 * @brief Enables PCA9422 Regulator interrupt according to the provided interrupt source mask.
 *
 * This function enables the PCA9422 Regulator interrupt according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt source of selected interrupt category to enable.
 */
void PCA9422_EnableRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Disable PCA9422 Regulator interrupt according to the provided interrupt source mask.
 *
 * This function disables the PCA9422 Regulator interrupt according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt source of selected interrupt category to disable.
 */
void PCA9422_DisableRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Regulator interrupt flag.
 *
 * This function gets regulator interrupt flag.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to regulator interrupt flag.
 */
void PCA9422_GetRegulatorInterrupt(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Regulator interrupt status flag.
 *
 * This function gets regulator interrupt status flag.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param status Pointer to regulator interrupt status flag.
 */
void PCA9422_GetRegulatorInterruptStatus(pca9422_handle_t *handle, uint8_t *status);

/*!
 * @name Sub-level Interrupt
 * @{
 */

/*!
 * @brief Enables PCA9422 Sub level interrupt according to the provided interrupt source mask.
 *
 * This function enables the PCA9422 sub level interrupt according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt source of selected interrupt category to enable.
 */
void PCA9422_EnableSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Disable PCA9422 Sub level interrupt according to the provided interrupt source mask.
 *
 * This function disables the PCA9422 sub level interrupt according to the provided interrupt source.
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to interrupt source of selected interrupt category to disable.
 */
void PCA9422_DisableSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Sub level interrupt flags.
 *
 * This function gets sub level interrupt flags.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param source Pointer to sub level interrupt flags.
 */
void PCA9422_GetSublevelInterrupts(pca9422_handle_t *handle, uint8_t *source);

/*!
 * @brief Get Top level interrupt status flag.
 *
 * This function gets top level interrupt status flag.
 * The flags are returned as an array of the corresponding interrupt source:
 *
 * @param handle Pointer to a valid PCA9422 instance structure.
 * @param status Pointer to top level interrupt status flag.
 */
void PCA9422_GetToplevelInterruptStatus(pca9422_handle_t *handle, uint8_t *status);
/* @} */

/*!
 * @name mode control functions
 * @{
 */

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_PCA9422_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
