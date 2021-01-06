/*
** ###################################################################
**     Version:             rev. 1.2, 2017-06-08
**     Build:               b190506
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2016-08-12)
**         Initial version.
**     - rev. 1.1 (2016-11-25)
**         Update CANFD and Classic CAN register.
**         Add MAC TIMERSTAMP registers.
**     - rev. 1.2 (2017-06-08)
**         Remove RTC_CTRL_RTC_OSC_BYPASS.
**         SYSCON_ARMTRCLKDIV rename to SYSCON_ARMTRACECLKDIV.
**         Remove RESET and HALT from SYSCON_AHBCLKDIV.
**
** ###################################################################
*/

#ifndef _LPC811_FEATURES_H_
#define _LPC811_FEATURES_H_

/* SOC module features */

/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (1)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (1)
/* @brief IOCON availability on the SoC. */
#define FSL_FEATURE_SOC_IOCON_COUNT (1)
/* @brief MRT availability on the SoC. */
#define FSL_FEATURE_SOC_MRT_COUNT (1)
/* @brief MTB availability on the SoC. */
#define FSL_FEATURE_SOC_MTB_COUNT (1)
/* @brief PINT availability on the SoC. */
#define FSL_FEATURE_SOC_PINT_COUNT (1)
/* @brief PMU availability on the SoC. */
#define FSL_FEATURE_SOC_PMU_COUNT (1)
/* @brief SCT availability on the SoC. */
#define FSL_FEATURE_SOC_SCT_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (1)
/* @brief SWM availability on the SoC. */
#define FSL_FEATURE_SOC_SWM_COUNT (1)
/* @brief SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCON_COUNT (1)
/* @brief USART availability on the SoC. */
#define FSL_FEATURE_SOC_USART_COUNT (2)
/* @brief WWDT availability on the SoC. */
#define FSL_FEATURE_SOC_WWDT_COUNT (1)

/* ACOMP module features */

/* @brief Has INTENA bitfile in CTRL reigster. */
#define FSL_FEATURE_ACOMP_HAS_CTRL_INTENA (0)

/* CLOCK module features */

/* @brief GPIOINT clock source. */
#define FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE (0)

/* IOCON module features */

/* No feature definitions */

/* MRT module features */

/* @brief Writing a zero asserts the MRT reset. */
#define FSL_FEATURE_MRT_WRITE_ZERO_ASSERT_RESET (1)
/* @brief Has no MULTITASK bitfile in MODCFG reigster. */
#define FSL_FEATURE_MRT_HAS_NO_MODCFG_MULTITASK (1)
/* @brief Has no INUSE bitfile in STAT reigster. */
#define FSL_FEATURE_MRT_HAS_NO_CHANNEL_STAT_INUSE (1)
/* @brief number of channels. */
#define FSL_FEATURE_MRT_NUMBER_OF_CHANNELS  (4)

/* NVIC module features */

/* @brief Number of connected outputs. */
#define FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER (1)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)

/* SCT module features */

/* @brief Number of events */
#define FSL_FEATURE_SCT_NUMBER_OF_EVENTS (6)
/* @brief Number of states */
#define FSL_FEATURE_SCT_NUMBER_OF_STATES (2)
/* @brief Number of match capture */
#define FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE (5)
/* @brief Writing a zero asserts the SCT reset. */
#define FSL_FEATURE_SCT_WRITE_ZERO_ASSERT_RESET (1)
/* @brief Do not has DMA request register (register DMAREQ0). */
#define FSL_FEATURE_SCT_HAS_NO_DMA_REQUEST (1)
/* @brief Number of outputs */
#define FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS (4)

/* SPI module features */

/* @brief Has SPOL0 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL0 (1)
/* @brief Has SPOL1 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL1 (0)
/* @brief Has SPOL2 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL2 (0)
/* @brief Has SPOL3 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL3 (0)

/* SWM module features */

/* @brief Has SWM PINENABLE0 ACMP I3. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I3 (0)
/* @brief Has SWM PINENABLE0 ACMP I4. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I4 (0)
/* @brief Has SWM PINENABLE0 ACMP I5. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I5 (0)

/* SYSCON module features */

/* @brief Pointer to ROM IAP entry functions */
#define FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION (0x1fff1ff1)
/* @brief Flash page size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES (64)
/* @brief Flash sector size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES (1024)
/* @brief Flash size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES (8192)
/* @brief IAP has Flash read & write function */
#define FSL_FEATURE_IAP_HAS_FLASH_FUNCTION (1)
/* @brief Starter register discontinuous. */
#define FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS (1)
/* @brief Has PINTSEL register. */
#define FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER (1)

/* USART module features */

/* @brief Has OSR (register OSR). */
#define FSL_FEATURE_USART_HAS_OSR_REGISTER (0)
/* @brief Has TXIDLEEN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_INTENSET_TXIDLEEN (0)
/* @brief Has ABERREN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_ABERR_CHECK (0)

/* WKT module features */

/* @brief Has SEL_EXTCLK bitfile in CTRL reigster. */
#define FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK (0)

/* WWDT module features */

/* @brief Has no RESET register. */
#define FSL_FEATURE_WWDT_HAS_NO_RESET (1)

#endif /* _LPC811_FEATURES_H_ */

