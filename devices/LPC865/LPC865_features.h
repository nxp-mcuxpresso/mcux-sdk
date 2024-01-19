/*
** ###################################################################
**     Version:             rev. 1.0, 2022-03-15
**     Build:               b230301
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.0 (2021-07-15)
**         Initial version.
**     - rev. 1.0 (2022-03-15)
**         Revesion of Rev. 1.
**
** ###################################################################
*/

#ifndef _LPC865_FEATURES_H_
#define _LPC865_FEATURES_H_

/* SOC module features */

/* @brief ACOMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACOMP_COUNT (1)
/* @brief ADC availability on the SoC. */
#define FSL_FEATURE_SOC_ADC_COUNT (1)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (1)
/* @brief FTM availability on the SoC. */
#define FSL_FEATURE_SOC_FTM_COUNT (2)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (1)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (1)
/* @brief I3C availability on the SoC. */
#define FSL_FEATURE_SOC_I3C_COUNT (1)
/* @brief INPUTMUX availability on the SoC. */
#define FSL_FEATURE_SOC_INPUTMUX_COUNT (1)
/* @brief IOCON availability on the SoC. */
#define FSL_FEATURE_SOC_IOCON_COUNT (1)
/* @brief MRT availability on the SoC. */
#define FSL_FEATURE_SOC_MRT_COUNT (1)
/* @brief PINT availability on the SoC. */
#define FSL_FEATURE_SOC_PINT_COUNT (1)
/* @brief PMU availability on the SoC. */
#define FSL_FEATURE_SOC_PMU_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (2)
/* @brief SWM availability on the SoC. */
#define FSL_FEATURE_SOC_SWM_COUNT (1)
/* @brief SYSCON availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCON_COUNT (1)
/* @brief USART availability on the SoC. */
#define FSL_FEATURE_SOC_USART_COUNT (3)
/* @brief WWDT availability on the SoC. */
#define FSL_FEATURE_SOC_WWDT_COUNT (1)

/* ACOMP module features */

/* @brief Has INTENA bitfile in CTRL reigster. */
#define FSL_FEATURE_ACOMP_HAS_CTRL_INTENA (1)

/* ADC module features */

/* @brief Do not has input select (register INSEL). */
#define FSL_FEATURE_ADC_HAS_NO_INSEL  (1)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE (1)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_RESOL (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_TSAMP (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE (1)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_CALMODE (1)
/* @brief Has startup register. */
#define FSL_FEATURE_ADC_HAS_STARTUP_REG (0)
/* @brief Has ADC Trim register */
#define FSL_FEATURE_ADC_HAS_TRIM_REG (1)
/* @brief Has Calibration register. */
#define FSL_FEATURE_ADC_HAS_CALIB_REG (0)
/* @brief ADC require calibration clock lower than 30MHz. */
#define FSL_FEATURE_ADC_CALIBRATION_CLOCK_LOWER_THAN_30MHz (1)
/* @brief ADC Has TSAMP bitfile in SEQ_CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_SEQ_CTRL_TSAMP (1)

/* CLOCK module features */

/* @brief GPIOINT clock source. */
#define FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE (1)

/* CRC module features */

/* No feature definitions */

/* DMA module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMA_NUMBER_OF_CHANNELS (16)
/* @brief Align size of DMA descriptor */
#define FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE (512)
/* @brief DMA head link descriptor table align size */
#define FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE (16U)

/* FTM module features */

/* @brief Number of channels. */
#define FSL_FEATURE_FTM_CHANNEL_COUNTn(x) \
    (((x) == FTM0) ? (6) : \
    (((x) == FTM1) ? (4) : (-1)))
/* @brief Has counter reset by the selected input capture event (register bits C0SC[ICRST], C1SC[ICRST], ...). */
#define FSL_FEATURE_FTM_HAS_COUNTER_RESET_BY_CAPTURE_EVENT (1)
/* @brief Has extended deadtime value. */
#define FSL_FEATURE_FTM_HAS_EXTENDED_DEADTIME_VALUE (0)
/* @brief Enable pwm output for the module. */
#define FSL_FEATURE_FTM_HAS_ENABLE_PWM_OUTPUT (1)
/* @brief Has half-cycle reload for the module. */
#define FSL_FEATURE_FTM_HAS_HALFCYCLE_RELOAD (1)
/* @brief Has reload interrupt. */
#define FSL_FEATURE_FTM_HAS_RELOAD_INTERRUPT (1)
/* @brief Has reload initialization trigger. */
#define FSL_FEATURE_FTM_HAS_RELOAD_INITIALIZATION_TRIGGER (1)
/* @brief Has DMA support, bitfield CnSC[DMA]. */
#define FSL_FEATURE_FTM_HAS_DMA_SUPPORT (0)
/* @brief If channel 6 is used to generate channel trigger, bitfield EXTTRIG[CH6TRIG]. */
#define FSL_FEATURE_FTM_HAS_CHANNEL6_TRIGGER (1)
/* @brief If channel 7 is used to generate channel trigger, bitfield EXTTRIG[CH7TRIG]. */
#define FSL_FEATURE_FTM_HAS_CHANNEL7_TRIGGER (1)
/* @brief If instance has only TPM function. */
#define FSL_FEATURE_FTM_IS_TPM_ONLY_INSTANCEn(x) (0)
/* @brief Has frequency of the reload opportunities, bitfield CONF[LDFQ]. */
#define FSL_FEATURE_FTM_HAS_CONF_LDFQ_BIT (1)
/* @brief If has instance with only baisc feature. */
#define FSL_FEATURE_FTM_HAS_BASIC_FEATURE_ONLY_INSTANCE (1)
/* @brief If instance has only basic feature. */
#define FSL_FEATURE_FTM_IS_BASIC_FEATURE_ONLY_INSTANCEn(x) \
    (((x) == FTM0) ? (0) : \
    (((x) == FTM1) ? (1) : (-1)))

/* I3C module features */

/* @brief Has TERM bitfile in MERRWARN register. */
#define FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM (0)
/* @brief SOC has no reset driver. */
#define FSL_FEATURE_I3C_HAS_NO_RESET (0)
/* @brief Use fixed BAMATCH count, do not provide editable BAMATCH. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH (0)
/* @brief Register SCONFIG do not have IDRAND bitfield. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND (1)
/* @brief Register SCONFIG has HDROK bitfield. */
#define FSL_FEATURE_I3C_HAS_HDROK (1)

/* INPUTMUX module features */

/* @brief Inputmux clock source. */
#define FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE (1)

/* IOCON module features */

/* No feature definitions */

/* MRT module features */

/* @brief number of channels. */
#define FSL_FEATURE_MRT_NUMBER_OF_CHANNELS  (4)
/* @brief Has no MULTITASK bitfile in MODCFG reigster. */
#define FSL_FEATURE_MRT_HAS_NO_MODCFG_MULTITASK (1)
/* @brief Has no INUSE bitfile in STAT reigster. */
#define FSL_FEATURE_MRT_HAS_NO_CHANNEL_STAT_INUSE (1)
/* @brief Writing a zero asserts the MRT reset. */
#define FSL_FEATURE_MRT_WRITE_ZERO_ASSERT_RESET (1)

/* NVIC module features */

/* @brief Number of connected outputs. */
#define FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER (1)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)

/* SPI module features */

/* @brief Has SPOL0 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL0 (1)
/* @brief Has SPOL1 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL1 (1)
/* @brief Has SPOL2 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL2 (1)
/* @brief Has SPOL3 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL3 (1)

/* SWM module features */

/* @brief Has SWM PINENABLE0 ACMP I3. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I3 (1)
/* @brief Has SWM PINENABLE0 ACMP I4. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I4 (1)
/* @brief Has SWM PINENABLE0 ACMP I5. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I5 (1)
/* @brief HAS FLEXTIMER PINASSIGN REGISTER. */
#define FSL_FEATURE_SWM_HAS_FLEXTIMER_PINASSIGN_REGISTER (1)

/* SYSCON module features */

/* @brief Pointer to ROM IAP entry functions */
#define FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION (0x0F001D91)
/* @brief Flash page size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES (64)
/* @brief Flash sector size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES (1024)
/* @brief Flash size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES (65536)
/* @brief IAP has Flash read & write function */
#define FSL_FEATURE_IAP_HAS_FLASH_FUNCTION (1)
/* @brief IAP has FAIM read & write function */
#define FSL_FEATURE_IAP_HAS_FAIM_FUNCTION (1)
/* @brief IAP has read Flash signature function */
#define FSL_FEATURE_IAP_HAS_FLASH_SIGNATURE_READ (0)
/* @brief IAP has read extended Flash signature function */
#define FSL_FEATURE_IAP_HAS_FLASH_EXTENDED_SIGNATURE_READ (1)
/* @brief Starter register discontinuous. */
#define FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS (1)
/* @brief Has PINTSEL register. */
#define FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER (1)

/* USART module features */

/* @brief Has OSR (register OSR). */
#define FSL_FEATURE_USART_HAS_OSR_REGISTER (1)
/* @brief Has TXIDLEEN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_INTENSET_TXIDLEEN (1)
/* @brief Has ABERREN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_ABERR_CHECK (1)
/* @brief Has RXIDLETOEN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_RXIDLETO_CHECK (1)

/* WKT module features */

/* @brief Has SEL_EXTCLK bitfile in CTRL reigster. */
#define FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK (1)

/* WWDT module features */

/* @brief Has no RESET register. */
#define FSL_FEATURE_WWDT_HAS_NO_RESET (1)

#endif /* _LPC865_FEATURES_H_ */

