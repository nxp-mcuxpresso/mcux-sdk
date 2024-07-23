/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PM_DEVICE_H_
#define _FSL_PM_DEVICE_H_

#include "fsl_common.h"

#include "fsl_pm_config.h"
#include "fsl_pm_device_config.h"

/*!
 * @addtogroup PM Framework: Power Manager Framework
 * @brief This section includes Power Mode macros, System Constraints macros, and Wakeup source macros.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @name Power Mode Definition
 * @{
 */

/* Power Mode Index */
#define PM_LP_STATE_SLEEP              (0U)
#define PM_LP_STATE_DEEP_SLEEP         (1U)
#define PM_LP_STATE_POWER_DOWN_WAKE_DS (2U)
#define PM_LP_STATE_POWER_DOWN_WAKE_PD (3U)
#define PM_LP_STATE_DEEP_POWER_DOWN    (4U)
#define PM_LP_STATE_VBAT               (5U)
#define PM_LP_STATE_NO_CONSTRAINT      (0xFFU)

/* Give alias for simplified Power Down Mode */
#define PM_LP_STATE_POWER_DOWN PM_LP_STATE_POWER_DOWN_WAKE_PD

/*! @} */

/*! @brief Helper macros
 * @{
 */
#define PM_RESC_MASK(resc_masks, rescIndex) ((resc_masks->rescMask[rescIndex / 32UL] >> (rescIndex % 32UL)) & 1UL)
#define PM_RESC_GROUP(resc_groups, rescIndex) \
    (resc_groups->groupSlice[rescIndex / 8UL] >> (4UL * (rescIndex % 8UL))) & 0xFUL
#define PM_RESOURCE_DB_COUNT (sizeof(resourceDB) / sizeof(*resourceDB))
/*! @} */

/*! @brief Available constraints for resources
 * @{
 */

typedef enum _resc_name
{
    kResc_BUS_SYS_Clk, /*!<    Bus/System Clocks */
    kResc_CORE_WAKE,   /*!<    CORE_WAKE Domain */

    /* These SRAM rescs must remain in this order */
    kResc_SRAM_RAMA0_8K,      /*!<    RAMA0 SRAM */
    kResc_SRAM_RAMA1_8K,      /*!<    RAMA1 SRAM */
    kResc_SRAM_RAMA2_8K,      /*!<    RAMA2 SRAM */
    kResc_SRAM_RAMA3_8K,      /*!<    RAMA3 SRAM */
    kResc_SRAM_RAMX0_32K,     /*!<    RAMX0 SRAM */
    kResc_SRAM_RAMX1_32K,     /*!<    RAMX1 SRAM */
    kResc_SRAM_RAMX2_32K,     /*!<    RAMX2 SRAM */
    kResc_SRAM_RAMB0_32K,     /*!<    RAMB0 SRAM */
    kResc_SRAM_RAMC0_32K,     /*!<    RAMC0 SRAM */
    kResc_SRAM_RAMC1_32K,     /*!<    RAMC1 SRAM */
    kResc_SRAM_RAMD0_32K,     /*!<    RAMD0 SRAM */
    kResc_SRAM_RAMD1_32K,     /*!<    RAMD1 SRAM */
    kResc_SRAM_RAME0_32K,     /*!<    RAME0 SRAM */
    kResc_SRAM_RAME1_32K,     /*!<    RAME1 SRAM */
    kResc_SRAM_RAMF0_32K,     /*!<    RAMF0 SRAM */
    kResc_SRAM_RAMF1_32K,     /*!<    RAMF1 SRAM */
    kResc_SRAM_RAMG01_32K,    /*!<    RAMG0/1 SRAM */
    kResc_SRAM_RAMG23_32K,    /*!<    RAMG2/3 SRAM */
    kResc_SRAM_RAMH01_32K,    /*!<    RAMH0/1 SRAM */
    kResc_SRAM_LPCAC,         /*!<    LPCAC SRAM */
    kResc_SRAM_DMA_PKC,       /*!<    DMA_PKC SRAM */
    kResc_SRAM_USB0,          /*!<    USB0 SRAM */
    kResc_SRAM_PQ,            /*!<    PQ SRAM */
    kResc_SRAM_CAN_ENET_USB1, /*!<    CAN/ENET/USB1 SRAM */
    kResc_SRAM_FLEXSPI0,      /*!<    FLEXSPI0 SRAM */

    kResc_Flash,              /*!<    Flash Memory */
    kResc_DCDC_CORE,          /*!<    DCDC_CORE Regulator */
    kResc_LDO_CORE,           /*!<    LDO_CORE Regulator */
    kResc_LDO_SYS,            /*!<    LDO_SYS Regulator */
    kResc_FRO_144M,           /*!< 31 Internal 144 MHz Oscillator */
    kResc_FRO_12M,            /*!< 32 Internal  12 MHz Oscillator */
    kResc_FRO_16K,            /*!<    Internal  16 kHz Oscillator */
    kResc_OSC_RTC,            /*!<    32 kHz Crystal Oscillator */
    kResc_OSC_SYS,            /*!<    High-Frequency Crystal Oscillator */
    kResc_PLL0,               /*!<    Auxillary APLL */
    kResc_PLL1,               /*!<    System SPLL */
    kResc_VREF,               /*!<    VREF peripheral */
    kResc_USB3V_DET,          /*!<    USB 3V Detect */
    kResc_DAC0,               /*!<    DAC0 peripheral */
    kResc_DAC1,               /*!<    DAC1 peripheral */
    kResc_DAC2,               /*!<    DAC2 peripheral */
    kResc_OPAMP0,             /*!<    OPAMP0 peripheral */
    kResc_OPAMP1,             /*!<    OPAMP1 peripheral */
    kResc_OPAMP2,             /*!<    OPAMP2 peripheral */
    kResc_CMP0,               /*!<    CMP0 peripheral */
    kResc_CMP1,               /*!<    CMP1 peripheral */
    kResc_CMP2,               /*!<    CMP2 peripheral */
    kResc_ADC,                /*!<    ADC peripheral */
    kResc_SINC,               /*!<    SINC Filter peripheral */
    kResc_BG_CORE,            /*!<    VDD_CORE Bandgap */
    kResc_BG_VBAT,            /*!<    VBAT Bandgap */
    kResc_GDET,               /*!<    VDD_CORE Glitch Detect */
    kResc_HVD_CORE,           /*!<    VDD_CORE HVD */
    kResc_HVD_SYS,            /*!<    VDD_SYS HVD */
    kResc_HVD_IO,             /*!<    VDD IO HVD */
    kResc_LVD_CORE,           /*!<    VDD_CORE LVD */
    kResc_LVD_SYS,            /*!<    VDD_SYS LVD */
    kResc_LVD_IO,             /*!<    VDD IO LVD */
    kResc_IO_Det,             /*!<    VDD IO voltage detect */
    kResc_Max_Num             /*!< 61 Maximum Number of Resource Constraints */
} resc_name_t;

/* Helper macros for Resource Contraint Masks */
#define PM_MASK_RESC_RAMA \
    ((1 << kResc_SRAM_RAMA0_8K) | (1 << kResc_SRAM_RAMA1_8K) | (1 << kResc_SRAM_RAMA2_8K) | (1 << kResc_SRAM_RAMA3_8K))

#define PM_MASK_RESC_RAMS                                                                                  \
    ((1 << kResc_SRAM_RAMX0_32K) | (1 << kResc_SRAM_RAMX1_32K) | (1 << kResc_SRAM_RAMX2_32K) |             \
     (1 << kResc_SRAM_RAMB0_32K) | (1 << kResc_SRAM_RAMC0_32K) | (1 << kResc_SRAM_RAMC1_32K) |             \
     (1 << kResc_SRAM_RAMD0_32K) | (1 << kResc_SRAM_RAMD1_32K) | (1 << kResc_SRAM_RAME0_32K) |             \
     (1 << kResc_SRAM_RAME1_32K) | (1 << kResc_SRAM_RAMF0_32K) | (1 << kResc_SRAM_RAMF1_32K) |             \
     (1 << kResc_SRAM_RAMG01_32K) | (1 << kResc_SRAM_RAMG23_32K) | (1 << kResc_SRAM_RAMH01_32K) |          \
     (1 << kResc_SRAM_LPCAC) | (1 << kResc_SRAM_DMA_PKC) | (1 << kResc_SRAM_USB0) | (1 << kResc_SRAM_PQ) | \
     (1 << kResc_SRAM_CAN_ENET_USB1) | (1 << kResc_SRAM_FLEXSPI0) | PM_MASK_RESC_RAMA)

/* VBAT */
#define PM_MASK_RESC_LOWEST_VBAT0 PM_MASK_RESC_RAMA
#define PM_MASK_RESC_LOWEST_VBAT1 \
    ((1 << (kResc_FRO_16K - 32)) | (1 << (kResc_OSC_RTC - 32)) | (1 << (kResc_BG_VBAT - 32)))

/* Deep power down */
#define PM_MASK_RESC_LOWEST_DPD0 ((1 << kResc_LDO_SYS) | PM_MASK_RESC_LOWEST_VBAT0)
#define PM_MASK_RESC_LOWEST_DPD1                                                                                       \
    ((1 << (kResc_CMP0 - 32)) | (1 << (kResc_CMP1 - 32)) | (1 << (kResc_HVD_SYS - 32)) | (1 << (kResc_LVD_SYS - 32)) | \
     PM_MASK_RESC_LOWEST_VBAT1)

/* Power down */
#define PM_MASK_RESC_LOWEST_PDPD0 \
    ((1 << kResc_DCDC_CORE) | (1 << kResc_LDO_CORE) | PM_MASK_RESC_RAMS | PM_MASK_RESC_LOWEST_DPD0)
#define PM_MASK_RESC_LOWEST_PDPD1                                                               \
    ((1 << (kResc_USB3V_DET - 32)) | (1 << (kResc_BG_CORE - 32)) | (1 << (kResc_GDET - 32)) |   \
     (1 << (kResc_HVD_CORE - 32)) | (1 << (kResc_LVD_CORE - 32)) | (1 << (kResc_HVD_IO - 32)) | \
     (1 << (kResc_LVD_IO - 32)) | (1 << (kResc_IO_Det - 32)) | PM_MASK_RESC_LOWEST_DPD1)

/* Power down and deep sleep */
#define PM_MASK_RESC_LOWEST_PDDS0 ((1 << kResc_CORE_WAKE) | PM_MASK_RESC_LOWEST_PDPD0)
#define PM_MASK_RESC_LOWEST_PDDS1 ((1 << (kResc_FRO_12M - 32)) | (1 << (kResc_CMP2 - 32)) | PM_MASK_RESC_LOWEST_PDPD1)

/* Deep sleep */
#define PM_MASK_RESC_LOWEST_DEEP_SLEEP0 ((1 << kResc_Flash) | PM_MASK_RESC_LOWEST_PDDS0)
#define PM_MASK_RESC_LOWEST_DEEP_SLEEP1                                                                              \
    ((1 << (kResc_DAC0 - 32)) | (1 << (kResc_DAC1 - 32)) | (1 << (kResc_DAC2 - 32)) | (1 << (kResc_OPAMP0 - 32)) |   \
     (1 << (kResc_OPAMP1 - 32)) | (1 << (kResc_OPAMP2 - 32)) | (1 << (kResc_VREF - 32)) | (1 << (kResc_SINC - 32)) | \
     PM_MASK_RESC_LOWEST_PDDS1)

/* Sleep */
#define PM_MASK_RESC_LOWEST_SLEEP0 ((1 << kResc_FRO_144M) | PM_MASK_RESC_LOWEST_DEEP_SLEEP0)
#define PM_MASK_RESC_LOWEST_SLEEP1                                                                                 \
    ((1 << (kResc_PLL0 - 32)) | (1 << (kResc_PLL1 - 32)) | (1 << (kResc_OSC_SYS - 32)) | (1 << (kResc_ADC - 32)) | \
     PM_MASK_RESC_LOWEST_DEEP_SLEEP1)

/* Resource constraints that are not variable, set by the power mode*/
#define PM_MASK_RESC_NOT_VAR0 ~((1 << kResc_BUS_SYS_Clk) & (1 << kResc_CORE_WAKE))
#define PM_MASK_RESC_NOT_VAR1 (0xFFFFFFFFU)

/* Constraints used by application. */
/*!
 * @brief Set the constraint that BUS and SYSTEM clock should be ON.
 */
#define PM_RESC_BUS_SYS_CLK_ON PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_BUS_SYS_Clk)
/*!
 * @brief Constraint only applies in Power Down mode.  Configures if CORE_WAKE
          domain should be in Deep Sleep, or can go into Power Down mode.
 */
#define PM_RESC_CORE_WAKE_DEEP_SLEEP PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_CORE_WAKE)

/*!
 * @brief Set RAMAs in active, retain, power-off mode.
 */
#define PM_RESC_RAMA0_8K_ACTIVE    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMA0_8K)
#define PM_RESC_RAMA0_8K_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMA0_8K)
#define PM_RESC_RAMA0_8K_POWEROFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMA0_8K)

#define PM_RESC_RAMA1_8K_ACTIVE    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMA1_8K)
#define PM_RESC_RAMA1_8K_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMA1_8K)
#define PM_RESC_RAMA1_8K_POWEROFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMA1_8K)

#define PM_RESC_RAMA2_8K_ACTIVE    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMA2_8K)
#define PM_RESC_RAMA2_8K_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMA2_8K)
#define PM_RESC_RAMA2_8K_POWEROFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMA2_8K)

#define PM_RESC_RAMA3_8K_ACTIVE    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMA3_8K)
#define PM_RESC_RAMA3_8K_RETENTION PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMA3_8K)
#define PM_RESC_RAMA3_8K_POWEROFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMA3_8K)

/*!
 * @brief Set system SRAMs in active, retain, power-off mode.
 */
#define PM_RESC_RAMX0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMX0_32K)
#define PM_RESC_RAMX0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMX0_32K)
#define PM_RESC_RAMX0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMX0_32K)

#define PM_RESC_RAMX1_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMX1_32K)
#define PM_RESC_RAMX1_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMX1_32K)
#define PM_RESC_RAMX1_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMX1_32K)

#define PM_RESC_RAMX2_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMX2_32K)
#define PM_RESC_RAMX2_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMX2_32K)
#define PM_RESC_RAMX2_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMX2_32K)

#define PM_RESC_RAMB0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMB0_32K)
#define PM_RESC_RAMB0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMB0_32K)
#define PM_RESC_RAMB0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMB0_32K)

#define PM_RESC_RAMC0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMC0_32K)
#define PM_RESC_RAMC0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMC0_32K)
#define PM_RESC_RAMC0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMC0_32K)

#define PM_RESC_RAMC1_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMC1_32K)
#define PM_RESC_RAMC1_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMC1_32K)
#define PM_RESC_RAMC1_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMC1_32K)

#define PM_RESC_RAMD0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMD0_32K)
#define PM_RESC_RAMD0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMD0_32K)
#define PM_RESC_RAMD0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMD0_32K)

#define PM_RESC_RAMD1_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMD1_32K)
#define PM_RESC_RAMD1_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMD1_32K)
#define PM_RESC_RAMD1_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMD1_32K)

#define PM_RESC_RAME0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAME0_32K)
#define PM_RESC_RAME0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAME0_32K)
#define PM_RESC_RAME0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAME0_32K)

#define PM_RESC_RAME1_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAME1_32K)
#define PM_RESC_RAME1_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAME1_32K)
#define PM_RESC_RAME1_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAME1_32K)

#define PM_RESC_RAMF0_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMF0_32K)
#define PM_RESC_RAMF0_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMF0_32K)
#define PM_RESC_RAMF0_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMF0_32K)

#define PM_RESC_RAMF1_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMF1_32K)
#define PM_RESC_RAMF1_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMF1_32K)
#define PM_RESC_RAMF1_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMF1_32K)

#define PM_RESC_RAMG01_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMG01_32K)
#define PM_RESC_RAMG01_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMG01_32K)
#define PM_RESC_RAMG01_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMG01_32K)

#define PM_RESC_RAMG23_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMG23_32K)
#define PM_RESC_RAMG23_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMG23_32K)
#define PM_RESC_RAMG23_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMG23_32K)

#define PM_RESC_RAMH01_32K_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_RAMH01_32K)
#define PM_RESC_RAMH01_32K_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_RAMH01_32K)
#define PM_RESC_RAMH01_32K_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_RAMH01_32K)

#define PM_RESC_RAM_LPCAC_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_LPCAC)
#define PM_RESC_RAM_LPCAC_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_LPCAC)
#define PM_RESC_RAM_LPCAC_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_LPCAC)

#define PM_RESC_RAM_DMA_PKC_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_DMA_PKC)
#define PM_RESC_RAM_DMA_PKC_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_DMA_PKC)
#define PM_RESC_RAM_DMA_PKC_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_DMA_PKC)

#define PM_RESC_RAM_USB0_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_USB0)
#define PM_RESC_RAM_USB0_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_USB0)
#define PM_RESC_RAM_USB0_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_USB0)

#define PM_RESC_RAM_PQ_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_PQ)
#define PM_RESC_RAM_PQ_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_PQ)
#define PM_RESC_RAM_PQ_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_PQ)

#define PM_RESC_RAM_CAN_ENET_USB1_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_CAN_ENET_USB1)
#define PM_RESC_RAM_CAN_ENET_USB1_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_CAN_ENET_USB1)
#define PM_RESC_RAM_CAN_ENET_USB1_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_CAN_ENET_USB1)

#define PM_RESC_RAM_FLEXSPI0_ACTIVE   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SRAM_FLEXSPI0)
#define PM_RESC_RAM_FLEXSPI0_RETAINED PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_FLEXSPI0)
#define PM_RESC_RAM_FLEXSPI0_POWEROFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SRAM_FLEXSPI0)

/*!
 * @brief Set the constraints that the Flash can be Active or Low-Power modes.
 *
 * The internal flash memory can enter low-power mode when the overall chip is in these mode:
 * 1. Active mode, under software control (FLASHCR[FLASHDIS])
 * 2. Sleep mode, optionally (FLASHCR[FLASHDOZE])
 */
#define PM_RESC_FLASH_ACTIVE PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_Flash)
#define PM_RESC_FLASH_LP     PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_Flash)

/*!
 * @brief Set the constraints for the regulators' drive strength modes.
 */
#define PM_RESC_DCDC_CORE_DS_NORMAL PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DCDC_CORE)
#define PM_RESC_DCDC_CORE_DS_LOW    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON2, kResc_DCDC_CORE)

#define PM_RESC_LDO_CORE_DS_NORMAL PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LDO_CORE)
#define PM_RESC_LDO_CORE_DS_LOW    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_LDO_CORE)

#define PM_RESC_LDO_SYS_DS_NORMAL PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LDO_SYS)
#define PM_RESC_LDO_SYS_DS_LOW    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_LDO_SYS)

/*!
 * @brief Set the constraints for the VDD_CORE BandGap modes.
 */
#define PM_RESC_CORE_BG_ON_BUF_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_BG_CORE)
#define PM_RESC_CORE_BG_ON_BUF_OFF PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_BG_CORE)

/*!
 * @brief Set the constraints for the remaining peripherals/features that are On or Off.
 */
#define PM_RESC_FRO_144M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_FRO_144M)
#define PM_RESC_FRO_144M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_FRO_144M)

#define PM_RESC_FRO_12M_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_FRO_12M)
#define PM_RESC_FRO_12M_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_FRO_12M)

#define PM_RESC_FRO_16K_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_FRO_16K)
#define PM_RESC_FRO_16K_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_FRO_16K)

#define PM_RESC_OSC_RTC_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_RTC)
#define PM_RESC_OSC_RTC_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_RTC)

#define PM_RESC_OSC_SYS_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OSC_SYS)
#define PM_RESC_OSC_SYS_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OSC_SYS)

#define PM_RESC_PLL0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_PLL0)
#define PM_RESC_PLL0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_PLL0)

#define PM_RESC_PLL1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_PLL1)
#define PM_RESC_PLL1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_PLL1)

#define PM_RESC_ADC_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ADC)
#define PM_RESC_ADC_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_ADC)

#define PM_RESC_CMP0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_CMP0)
#define PM_RESC_CMP0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_CMP0)

#define PM_RESC_CMP1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_CMP1)
#define PM_RESC_CMP1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_CMP1)

#define PM_RESC_CMP2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_CMP2)
#define PM_RESC_CMP2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_CMP2)

#define PM_RESC_DAC0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DAC0)
#define PM_RESC_DAC0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_DAC0)

#define PM_RESC_DAC1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DAC1)
#define PM_RESC_DAC1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_DAC1)

#define PM_RESC_DAC2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_DAC2)
#define PM_RESC_DAC2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_DAC2)

#define PM_RESC_OPAMP0_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OPAMP0)
#define PM_RESC_OPAMP0_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OPAMP0)

#define PM_RESC_OPAMP1_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OPAMP1)
#define PM_RESC_OPAMP1_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OPAMP1)

#define PM_RESC_OPAMP2_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_OPAMP2)
#define PM_RESC_OPAMP2_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_OPAMP2)

#define PM_RESC_VREF_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_VREF)
#define PM_RESC_VREF_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_VREF)

#define PM_RESC_SINC_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SINC)
#define PM_RESC_SINC_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_SINC)

#define PM_RESC_USB3V_DET_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_USB3V_DET)
#define PM_RESC_USB3V_DET_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_USB3V_DET)

#define PM_RESC_BG_VBAT_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_BG_VBAT)
#define PM_RESC_BG_VBAT_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_BG_VBAT)

#define PM_RESC_GDET_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_GDET)
#define PM_RESC_GDET_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_GDET)

/* vdd_core, vdd_sys, and vdd_io low-, high-voltage detect */
#define PM_RESC_HVD_CORE_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_HVD_CORE)
#define PM_RESC_HVD_CORE_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_HVD_CORE)
#define PM_RESC_HVD_SYS_ON   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_HVD_SYS)
#define PM_RESC_HVD_SYS_OFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_HVD_SYS)
#define PM_RESC_HVD_IO_ON    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_HVD_IO)
#define PM_RESC_HVD_IO_OFF   PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_HVD_IO)

#define PM_RESC_LVD_CORE_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LVD_CORE)
#define PM_RESC_LVD_CORE_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LVD_CORE)
#define PM_RESC_LVD_SYS_ON   PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LVD_SYS)
#define PM_RESC_LVD_SYS_OFF  PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LVD_SYS)
#define PM_RESC_LVD_IO_ON    PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LVD_IO)
#define PM_RESC_LVD_IO_OFF   PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_LVD_IO)

#define PM_RESC_IO_DET_ON  PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_IO_Det)
#define PM_RESC_IO_DET_OFF PM_ENCODE_RESC(PM_RESOURCE_OFF, kResc_IO_Det)
/*! @} */

#if FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER

/*!
 * @name Wakeup enumerations
 * @{
 */

typedef enum _wakeup_inputType
{
    kWup_inputType_extPin = 0U, /*!< External Pin type */
    kWup_inputType_intMod,      /*!< Internal Module type */
} wakeup_inputType_t;

typedef enum _wakeup_pin_det
{
    kWup_pinDet_RisingEdge = 1U, /*!< Rising  Edge detection */
    kWup_pinDet_FallingEdge,     /*!< Falling Edge detection */
    kWup_pinDet_AnyChange,       /*!< Any Change   detection */
} wakeup_pin_det_t;

typedef enum _wakeup_pinID
{
    kWup_pinID_P0_4  = 0U,  /*!< Port0 Pin4 */
    kWup_pinID_P0_7  = 1U,  /*!< Port0 Pin7 */
    kWup_pinID_P0_16 = 2U,  /*!< Port0 Pin16 */
    kWup_pinID_P0_19 = 3U,  /*!< Port0 Pin19 */
    kWup_pinID_P0_20 = 4U,  /*!< Port0 Pin20 */
    kWup_pinID_P0_23 = 5U,  /*!< Port0 Pin23 */
    kWup_pinID_P1_0  = 6U,  /*!< Port1 Pin0 */
    kWup_pinID_P1_3  = 7U,  /*!< Port1 Pin3 */
    kWup_pinID_P1_4  = 8U,  /*!< Port1 Pin4 */
    kWup_pinID_P1_7  = 9U,  /*!< Port1 Pin7 */
    kWup_pinID_P1_8  = 10U, /*!< Port1 Pin8 */
    kWup_pinID_P1_11 = 11U, /*!< Port1 Pin11 */
    kWup_pinID_P1_12 = 12U, /*!< Port1 Pin12 */
    kWup_pinID_P1_15 = 13U, /*!< Port1 Pin15 */
    kWup_pinID_P1_16 = 14U, /*!< Port1 Pin16 */
    kWup_pinID_P1_19 = 15U, /*!< Port2 Pin19 */
    kWup_pinID_P2_2  = 16U, /*!< Port2 Pin2 */
    kWup_pinID_P2_4  = 17U, /*!< Port2 Pin4 */
    kWup_pinID_P4_0  = 18U, /*!< Port4 Pin0 */
    kWup_pinID_P4_3  = 19U, /*!< Port4 Pin3 */
    kWup_pinID_P4_12 = 20U, /*!< Port4 Pin12 */
    kWup_pinID_P4_15 = 21U, /*!< Port4 Pin15 */
    kWup_pinID_P3_0  = 22U, /*!< Port3 Pin0 */
    kWup_pinID_P3_8  = 23U, /*!< Port3 Pin8 */
    kWup_pinID_P3_11 = 24U, /*!< Port3 Pin11 */
    kWup_pinID_P3_14 = 25U, /*!< Port3 Pin14 */
    kWup_pinID_P3_17 = 26U, /*!< Port3 Pin17 */
    kWup_pinID_P3_20 = 27U, /*!< Port3 Pin20 */
} wakeup_pinID_t;

typedef enum _wakeup_modID
{
    kWup_modID_SPC0 = 0U, /*!< SPC */
    kWup_modID_VBAT = 1U, /*!< VBAT */
    kWup_modID_RTC  = 2U, /*!< RTC */
    // kWup_modID_TDET = 3U,       /*!< TDET */
    kWup_modID_GPIO5_INT0 = 4U, /*!< GPIO5 interrupt 0 */
    kWup_modID_GPIO5_INT1 = 5U, /*!< GPIO5 interrupt 1 */
    kWup_modID_LPTMR0     = 6U, /*!< LPTMR0 */
    kWup_modID_LPTMR1     = 7U, /*!< LPTMR1 */
    kWup_modID_CMP0       = 8U, /*!< CMP0 */
    kWup_modID_CMP1       = 9U, /*!< CMP1 */
} wakeup_modID_t;

/*! @} */

/*!
 * @name System Wakeup source definitions.
 * @{
 */

/*!
 * @brief Enable external pin as the wakeup source, detect on rising edge/falling edge/any edge.
 */
#define PM_WSID_P0_4_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_4, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_4_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_4, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_4_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_4, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P0_7_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_7, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_7_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_7, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_7_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_7, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P0_16_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_16, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_16_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_16, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_16_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_16, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P0_19_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_19, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_19_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_19, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_19_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_19, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P0_20_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_20, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_20_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_20, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_20_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P0_20, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P0_23_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_0, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P0_23_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_0, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P0_23_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_0, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_0_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_3, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_0_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_3, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_0_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_3, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_3_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_4, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_3_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_4, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_3_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_4, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_4_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_7, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_4_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_7, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_4_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_7, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_7_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_8, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_7_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_8, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_7_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_8, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_8_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_11, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_8_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_11, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_8_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_11, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_11_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_12, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_11_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_12, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_11_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_12, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_12_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_15, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_12_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_15, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_12_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_15, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_15_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_16, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_15_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_16, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_15_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_16, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_16_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_19, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_16_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_19, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_16_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P1_19, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P1_19_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_2, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P1_19_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_2, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P1_19_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_2, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P2_2_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_4, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P2_2_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_4, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P2_2_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P2_4, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P2_4_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_0, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P2_4_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_0, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P2_4_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_0, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P4_0_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_3, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P4_0_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_3, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P4_0_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_3, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P4_12_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_12, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P4_12_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_12, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P4_12_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_12, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P4_15_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_15, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P4_15_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_15, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P4_15_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P4_15, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_0_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_0, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_0_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_0, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_0_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_0, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_8_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_8, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_8_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_8, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_8_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_8, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_11_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_11, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_11_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_11, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_11_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_11, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_14_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_14, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_14_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_14, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_14_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_14, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_17_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_17, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_17_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_17, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_17_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_17, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

#define PM_WSID_P3_20_RISING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_20, PORT_EFT_IRQn, kWup_pinDet_RisingEdge)
#define PM_WSID_P3_20_FALLING_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_20, PORT_EFT_IRQn, kWup_pinDet_FallingEdge)
#define PM_WSID_P3_20_ANY_EDGE \
    PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_extPin, kWup_pinID_P3_20, PORT_EFT_IRQn, kWup_pinDet_AnyChange)

/*!
 * @brief Enable on-chip module as the wakeup source.
 */
#define PM_WSID_SPC  PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_SPC0, SPC_IRQn, 0UL)
#define PM_WSID_VBAT PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_VBAT, VBAT0_IRQn, 0UL)
#define PM_WSID_RTC  PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_RTC, RTC_IRQn, 0UL)
// #define PM_WSID_TDET            PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_TDET, xxx, 0UL)
#define PM_WSID_GPIO5_INT0 PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_GPIO5_INT0, GPIO50_IRQn, 0UL)
#define PM_WSID_GPIO5_INT1 PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_GPIO5_INT1, GPIO51_IRQn, 0UL)
#define PM_WSID_LPTMR0     PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_LPTMR0, LPTMR0_IRQn, 0UL)
#define PM_WSID_LPTMR1     PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_LPTMR1, LPTMR1_IRQn, 0UL)
#define PM_WSID_CMP0       PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_CMP0, HSCMP0_IRQn, 0UL)
#define PM_WSID_CMP1       PM_ENCODE_WAKEUP_SOURCE_ID(kWup_inputType_intMod, kWup_modID_CMP1, HSCMP1_IRQn, 0UL)

/*! @} */

#endif /* FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER */

/*******************************************************************************
 * APIs
 ******************************************************************************/

#endif /* _FSL_PM_DEVICE_H_ */
