/*
** ###################################################################
**     Processors:          LPC51U68JBD48
**                          LPC51U68JBD64
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC51U68 User manual User manual Rev. 1.0 13 Dec 2017
**     Version:             rev. 1.0, 2017-12-15
**     Build:               b201027
**
**     Abstract:
**         CMSIS Peripheral Access Layer for LPC51U68
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2017-12-15)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file LPC51U68.h
 * @version 1.0
 * @date 2017-12-15
 * @brief CMSIS Peripheral Access Layer for LPC51U68
 *
 * CMSIS Peripheral Access Layer for LPC51U68
 */

#ifndef _LPC51U68_H_
#define _LPC51U68_H_                             /**< Symbol preventing repeated inclusion */

/** Memory map major version (memory maps with equal major version number are
 * compatible) */
#define MCU_MEM_MAP_VERSION 0x0100U
/** Memory map minor version */
#define MCU_MEM_MAP_VERSION_MINOR 0x0000U


/* ----------------------------------------------------------------------------
   -- Interrupt vector numbers
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Interrupt_vector_numbers Interrupt vector numbers
 * @{
 */

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 48                 /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  WDT_BOD_IRQn                 = 0,                /**< Windowed watchdog timer, Brownout detect */
  DMA0_IRQn                    = 1,                /**< DMA controller */
  GINT0_IRQn                   = 2,                /**< GPIO group 0 */
  GINT1_IRQn                   = 3,                /**< GPIO group 1 */
  PIN_INT0_IRQn                = 4,                /**< Pin interrupt 0 or pattern match engine slice 0 */
  PIN_INT1_IRQn                = 5,                /**< Pin interrupt 1or pattern match engine slice 1 */
  PIN_INT2_IRQn                = 6,                /**< Pin interrupt 2 or pattern match engine slice 2 */
  PIN_INT3_IRQn                = 7,                /**< Pin interrupt 3 or pattern match engine slice 3 */
  UTICK0_IRQn                  = 8,                /**< Micro-tick Timer */
  MRT0_IRQn                    = 9,                /**< Multi-rate timer */
  CTIMER0_IRQn                 = 10,               /**< Standard counter/timer CTIMER0 */
  CTIMER1_IRQn                 = 11,               /**< Standard counter/timer CTIMER1 */
  SCT0_IRQn                    = 12,               /**< SCTimer/PWM */
  CTIMER3_IRQn                 = 13,               /**< Standard counter/timer CTIMER3 */
  FLEXCOMM0_IRQn               = 14,               /**< Flexcomm Interface 0 (USART, SPI, I2C) */
  FLEXCOMM1_IRQn               = 15,               /**< Flexcomm Interface 1 (USART, SPI, I2C) */
  FLEXCOMM2_IRQn               = 16,               /**< Flexcomm Interface 2 (USART, SPI, I2C) */
  FLEXCOMM3_IRQn               = 17,               /**< Flexcomm Interface 3 (USART, SPI, I2C) */
  FLEXCOMM4_IRQn               = 18,               /**< Flexcomm Interface 4 (USART, SPI, I2C) */
  FLEXCOMM5_IRQn               = 19,               /**< Flexcomm Interface 5 (USART, SPI, I2C) */
  FLEXCOMM6_IRQn               = 20,               /**< Flexcomm Interface 6 (USART, SPI, I2C, I2S) */
  FLEXCOMM7_IRQn               = 21,               /**< Flexcomm Interface 7 (USART, SPI, I2C, I2S) */
  ADC0_SEQA_IRQn               = 22,               /**< ADC0 sequence A completion. */
  ADC0_SEQB_IRQn               = 23,               /**< ADC0 sequence B completion. */
  ADC0_THCMP_IRQn              = 24,               /**< ADC0 threshold compare and error. */
  Reserved41_IRQn              = 25,               /**< Reserved interrupt */
  Reserved42_IRQn              = 26,               /**< Reserved interrupt */
  USB0_NEEDCLK_IRQn            = 27,               /**< USB Activity Wake-up Interrupt */
  USB0_IRQn                    = 28,               /**< USB device */
  RTC_IRQn                     = 29,               /**< RTC alarm and wake-up interrupts */
  Reserved46_IRQn              = 30,               /**< Reserved interrupt */
  Reserved47_IRQn              = 31                /**< Reserved interrupt */
} IRQn_Type;

/*!
 * @}
 */ /* end of group Interrupt_vector_numbers */


/* ----------------------------------------------------------------------------
   -- Cortex M0 Core Configuration
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Cortex_Core_Configuration Cortex M0 Core Configuration
 * @{
 */

#define __CM0PLUS_REV                  0x0000    /**< Core revision r0p0 */
#define __MPU_PRESENT                  0         /**< Defines if an MPU is present or not */
#define __VTOR_PRESENT                 1         /**< Defines if VTOR is present or not */
#define __NVIC_PRIO_BITS               2         /**< Number of priority bits implemented in the NVIC */
#define __Vendor_SysTickConfig         0         /**< Vendor specific implementation of SysTickConfig is defined */

#include "core_cm0plus.h"              /* Core Peripheral Access Layer */
#include "system_LPC51U68.h"           /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/* ----------------------------------------------------------------------------
   -- Mapping Information
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Mapping_Information Mapping Information
 * @{
 */

/** Mapping Information */
/*!
 * @addtogroup dma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Enumeration for the DMA hardware request
 *
 * Defines the enumeration for the DMA hardware request collections.
 */
typedef enum _dma_request_source
{
    kFlexcomm_Interface0_RX_I2C_Slave = 0U,        /**< Flexcomm Interface 0 RX/I2C Slave */
    kFlexcomm_Interface0_TX_I2C_Master = 1U,       /**< Flexcomm Interface 0 TX/I2C Master */
    kFlexcomm_Interface1_RX_I2C_Slave = 2U,        /**< Flexcomm Interface 1 RX/I2C Slave */
    kFlexcomm_Interface1_TX_I2C_Master = 3U,       /**< Flexcomm Interface 1 TX/I2C Master */
    kFlexcomm_Interface2_RX_I2C_Slave = 4U,        /**< Flexcomm Interface 2 RX/I2C Slave */
    kFlexcomm_Interface2_TX_I2C_Master = 5U,       /**< Flexcomm Interface 2 TX/I2C Master */
    kFlexcomm_Interface3_RX_I2C_Slave = 6U,        /**< Flexcomm Interface 3 RX/I2C Slave */
    kFlexcomm_Interface3_TX_I2C_Master = 7U,       /**< Flexcomm Interface 3 TX/I2C Master */
    kFlexcomm_Interface4_RX_I2C_Slave = 8U,        /**< Flexcomm Interface 4 RX/I2C Slave */
    kFlexcomm_Interface4_TX_I2C_Master = 9U,       /**< Flexcomm Interface 4 TX/I2C Master */
    kFlexcomm_Interface5_RX_I2C_Slave = 10U,       /**< Flexcomm Interface 5 RX/I2C Slave */
    kFlexcomm_Interface5_TX_I2C_Master = 11U,      /**< Flexcomm Interface 5 TX/I2C Master */
    kFlexcomm_Interface6_RX_I2C_Slave = 12U,       /**< Flexcomm Interface 6 RX/I2C Slave */
    kFlexcomm_Interface6_TX_I2C_Master = 13U,      /**< Flexcomm Interface 6 TX/I2C Master */
    kFlexcomm_Interface7_RX_I2C_Slave = 14U,       /**< Flexcomm Interface 7 RX/I2C Slave */
    kFlexcomm_Interface7_TX_I2C_Master = 15U,      /**< Flexcomm Interface 7 TX/I2C Master */
    kDmaRequestNoDMARequest18       = 18U,         /**< No DMA request 18 */
    kDmaRequestNoDMARequest19       = 19U,         /**< No DMA request 19 */
} dma_request_source_t;

/* @} */


/*!
 * @}
 */ /* end of group Mapping_Information */


/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */

/** ADC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls., offset: 0x0 */
  __IO uint32_t INSEL;                             /**< Input Select. Allows selection of the temperature sensor as an alternate input to ADC channel 0., offset: 0x4 */
  __IO uint32_t SEQ_CTRL[2];                       /**< ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n., array offset: 0x8, array step: 0x4 */
  __I  uint32_t SEQ_GDAT[2];                       /**< ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n., array offset: 0x10, array step: 0x4 */
       uint8_t RESERVED_0[8];
  __I  uint32_t DAT[12];                           /**< ADC Channel 0 Data register. This register contains the result of the most recent conversion completed on channel 0., array offset: 0x20, array step: 0x4 */
  __IO uint32_t THR0_LOW;                          /**< ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x50 */
  __IO uint32_t THR1_LOW;                          /**< ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x54 */
  __IO uint32_t THR0_HIGH;                         /**< ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x58 */
  __IO uint32_t THR1_HIGH;                         /**< ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x5C */
  __IO uint32_t CHAN_THRSEL;                       /**< ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel, offset: 0x60 */
  __IO uint32_t INTEN;                             /**< ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated., offset: 0x64 */
  __IO uint32_t FLAGS;                             /**< ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers)., offset: 0x68 */
  __IO uint32_t STARTUP;                           /**< ADC Startup register., offset: 0x6C */
  __IO uint32_t CALIB;                             /**< ADC Calibration register., offset: 0x70 */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name CTRL - ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls. */
/*! @{ */
#define ADC_CTRL_CLKDIV_MASK                     (0xFFU)
#define ADC_CTRL_CLKDIV_SHIFT                    (0U)
/*! CLKDIV - In synchronous mode only, the system clock is divided by this value plus one to produce
 *    the clock for the ADC converter, which should be less than or equal to 72 MHz. Typically,
 *    software should program the smallest value in this field that yields this maximum clock rate or
 *    slightly less, but in certain cases (such as a high-impedance analog source) a slower clock may
 *    be desirable. This field is ignored in the asynchronous operating mode.
 */
#define ADC_CTRL_CLKDIV(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_CLKDIV_SHIFT)) & ADC_CTRL_CLKDIV_MASK)
#define ADC_CTRL_ASYNMODE_MASK                   (0x100U)
#define ADC_CTRL_ASYNMODE_SHIFT                  (8U)
/*! ASYNMODE - Select clock mode.
 *  0b0..Synchronous mode. The ADC clock is derived from the system clock based on the divide value selected in
 *       the CLKDIV field. The ADC clock will be started in a controlled fashion in response to a trigger to
 *       eliminate any uncertainty in the launching of an ADC conversion in response to any synchronous (on-chip) trigger.
 *       In Synchronous mode with the SYNCBYPASS bit (in a sequence control register) set, sampling of the ADC
 *       input and start of conversion will initiate 2 system clocks after the leading edge of a (synchronous) trigger
 *       pulse.
 *  0b1..Asynchronous mode. The ADC clock is based on the output of the ADC clock divider ADCCLKSEL in the SYSCON block.
 */
#define ADC_CTRL_ASYNMODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ASYNMODE_SHIFT)) & ADC_CTRL_ASYNMODE_MASK)
#define ADC_CTRL_RESOL_MASK                      (0x600U)
#define ADC_CTRL_RESOL_SHIFT                     (9U)
/*! RESOL - The number of bits of ADC resolution. Accuracy can be reduced to achieve higher
 *    conversion rates. A single conversion (including one conversion in a burst or sequence) requires the
 *    selected number of bits of resolution plus 3 ADC clocks. This field must only be altered when
 *    the ADC is fully idle. Changing it during any kind of ADC operation may have unpredictable
 *    results. ADC clock frequencies for various resolutions must not exceed: - 5x the system clock rate
 *    for 12-bit resolution - 4.3x the system clock rate for 10-bit resolution - 3.6x the system
 *    clock for 8-bit resolution - 3x the bus clock rate for 6-bit resolution
 *  0b00..6-bit resolution. An ADC conversion requires 9 ADC clocks, plus any clocks specified by the TSAMP field.
 *  0b01..8-bit resolution. An ADC conversion requires 11 ADC clocks, plus any clocks specified by the TSAMP field.
 *  0b10..10-bit resolution. An ADC conversion requires 13 ADC clocks, plus any clocks specified by the TSAMP field.
 *  0b11..12-bit resolution. An ADC conversion requires 15 ADC clocks, plus any clocks specified by the TSAMP field.
 */
#define ADC_CTRL_RESOL(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_RESOL_SHIFT)) & ADC_CTRL_RESOL_MASK)
#define ADC_CTRL_BYPASSCAL_MASK                  (0x800U)
#define ADC_CTRL_BYPASSCAL_SHIFT                 (11U)
/*! BYPASSCAL - Bypass Calibration. This bit may be set to avoid the need to calibrate if offset
 *    error is not a concern in the application.
 *  0b0..Calibrate. The stored calibration value will be applied to the ADC during conversions to compensated for
 *       offset error. A calibration cycle must be performed each time the chip is powered-up. Re-calibration may
 *       be warranted periodically - especially if operating conditions have changed.
 *  0b1..Bypass calibration. Calibration is not utilized. Less time is required when enabling the ADC -
 *       particularly following chip power-up. Attempts to launch a calibration cycle are blocked when this bit is set.
 */
#define ADC_CTRL_BYPASSCAL(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_BYPASSCAL_SHIFT)) & ADC_CTRL_BYPASSCAL_MASK)
#define ADC_CTRL_TSAMP_MASK                      (0x7000U)
#define ADC_CTRL_TSAMP_SHIFT                     (12U)
/*! TSAMP - Sample Time. The default sampling period (TSAMP = '000') at the start of each conversion
 *    is 2.5 ADC clock periods. Depending on a variety of factors, including operating conditions
 *    and the output impedance of the analog source, longer sampling times may be required. See
 *    Section 28.7.10. The TSAMP field specifies the number of additional ADC clock cycles, from zero to
 *    seven, by which the sample period will be extended. The total conversion time will increase by
 *    the same number of clocks. 000 - The sample period will be the default 2.5 ADC clocks. A
 *    complete conversion with 12-bits of accuracy will require 15 clocks. 001- The sample period will
 *    be extended by one ADC clock to a total of 3.5 clock periods. A complete 12-bit conversion will
 *    require 16 clocks. 010 - The sample period will be extended by two clocks to 4.5 ADC clock
 *    cycles. A complete 12-bit conversion will require 17 ADC clocks. 111 - The sample period will be
 *    extended by seven clocks to 9.5 ADC clock cycles. A complete 12-bit conversion will require
 *    22 ADC clocks.
 */
#define ADC_CTRL_TSAMP(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_TSAMP_SHIFT)) & ADC_CTRL_TSAMP_MASK)
/*! @} */

/*! @name INSEL - Input Select. Allows selection of the temperature sensor as an alternate input to ADC channel 0. */
/*! @{ */
#define ADC_INSEL_SEL_MASK                       (0x3U)
#define ADC_INSEL_SEL_SHIFT                      (0U)
/*! SEL - Selects the input source for channel 0. All other values are reserved.
 *  0b00..ADC0_IN0 function.
 *  0b11..Internal temperature sensor.
 */
#define ADC_INSEL_SEL(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_INSEL_SEL_SHIFT)) & ADC_INSEL_SEL_MASK)
/*! @} */

/*! @name SEQ_CTRL - ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n. */
/*! @{ */
#define ADC_SEQ_CTRL_CHANNELS_MASK               (0xFFFU)
#define ADC_SEQ_CTRL_CHANNELS_SHIFT              (0U)
/*! CHANNELS - Selects which one or more of the ADC channels will be sampled and converted when this
 *    sequence is launched. A 1 in any bit of this field will cause the corresponding channel to be
 *    included in the conversion sequence, where bit 0 corresponds to channel 0, bit 1 to channel 1
 *    and so forth. When this conversion sequence is triggered, either by a hardware trigger or via
 *    software command, ADC conversions will be performed on each enabled channel, in sequence,
 *    beginning with the lowest-ordered channel. This field can ONLY be changed while SEQA_ENA (bit 31)
 *    is LOW. It is allowed to change this field and set bit 31 in the same write.
 */
#define ADC_SEQ_CTRL_CHANNELS(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_CHANNELS_SHIFT)) & ADC_SEQ_CTRL_CHANNELS_MASK)
#define ADC_SEQ_CTRL_TRIGGER_MASK                (0x3F000U)
#define ADC_SEQ_CTRL_TRIGGER_SHIFT               (12U)
/*! TRIGGER - Selects which of the available hardware trigger sources will cause this conversion
 *    sequence to be initiated. Program the trigger input number in this field. See Table 476. In order
 *    to avoid generating a spurious trigger, it is recommended writing to this field only when
 *    SEQA_ENA (bit 31) is low. It is safe to change this field and set bit 31 in the same write.
 */
#define ADC_SEQ_CTRL_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGGER_SHIFT)) & ADC_SEQ_CTRL_TRIGGER_MASK)
#define ADC_SEQ_CTRL_TRIGPOL_MASK                (0x40000U)
#define ADC_SEQ_CTRL_TRIGPOL_SHIFT               (18U)
/*! TRIGPOL - Select the polarity of the selected input trigger for this conversion sequence. In
 *    order to avoid generating a spurious trigger, it is recommended writing to this field only when
 *    SEQA_ENA (bit 31) is low. It is safe to change this field and set bit 31 in the same write.
 *  0b0..Negative edge. A negative edge launches the conversion sequence on the selected trigger input.
 *  0b1..Positive edge. A positive edge launches the conversion sequence on the selected trigger input.
 */
#define ADC_SEQ_CTRL_TRIGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGPOL_SHIFT)) & ADC_SEQ_CTRL_TRIGPOL_MASK)
#define ADC_SEQ_CTRL_SYNCBYPASS_MASK             (0x80000U)
#define ADC_SEQ_CTRL_SYNCBYPASS_SHIFT            (19U)
/*! SYNCBYPASS - Setting this bit allows the hardware trigger input to bypass synchronization
 *    flip-flop stages and therefore shorten the time between the trigger input signal and the start of a
 *    conversion. There are slightly different criteria for whether or not this bit can be set
 *    depending on the clock operating mode: Synchronous mode (the ASYNMODE in the CTRL register = 0):
 *    Synchronization may be bypassed (this bit may be set) if the selected trigger source is already
 *    synchronous with the main system clock (eg. coming from an on-chip, system-clock-based timer).
 *    Whether this bit is set or not, a trigger pulse must be maintained for at least one system
 *    clock period. Asynchronous mode (the ASYNMODE in the CTRL register = 1): Synchronization may be
 *    bypassed (this bit may be set) if it is certain that the duration of a trigger input pulse
 *    will be at least one cycle of the ADC clock (regardless of whether the trigger comes from and
 *    on-chip or off-chip source). If this bit is NOT set, the trigger pulse must at least be
 *    maintained for one system clock period.
 *  0b0..Enable trigger synchronization. The hardware trigger bypass is not enabled.
 *  0b1..Bypass trigger synchronization. The hardware trigger bypass is enabled.
 */
#define ADC_SEQ_CTRL_SYNCBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SYNCBYPASS_SHIFT)) & ADC_SEQ_CTRL_SYNCBYPASS_MASK)
#define ADC_SEQ_CTRL_START_MASK                  (0x4000000U)
#define ADC_SEQ_CTRL_START_SHIFT                 (26U)
/*! START - Writing a 1 to this field will launch one pass through this conversion sequence. The
 *    behavior will be identical to a sequence triggered by a hardware trigger. Do not write 1 to this
 *    bit if the BURST bit is set. This bit is only set to a 1 momentarily when written to launch a
 *    conversion sequence. It will consequently always read back as a zero.
 */
#define ADC_SEQ_CTRL_START(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_START_SHIFT)) & ADC_SEQ_CTRL_START_MASK)
#define ADC_SEQ_CTRL_BURST_MASK                  (0x8000000U)
#define ADC_SEQ_CTRL_BURST_SHIFT                 (27U)
/*! BURST - Writing a 1 to this bit will cause this conversion sequence to be continuously cycled
 *    through. Other sequence A triggers will be ignored while this bit is set. Repeated conversions
 *    can be halted by clearing this bit. The sequence currently in progress will be completed before
 *    conversions are terminated. Note that a new sequence could begin just before BURST is cleared.
 */
#define ADC_SEQ_CTRL_BURST(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_BURST_SHIFT)) & ADC_SEQ_CTRL_BURST_MASK)
#define ADC_SEQ_CTRL_SINGLESTEP_MASK             (0x10000000U)
#define ADC_SEQ_CTRL_SINGLESTEP_SHIFT            (28U)
/*! SINGLESTEP - When this bit is set, a hardware trigger or a write to the START bit will launch a
 *    single conversion on the next channel in the sequence instead of the default response of
 *    launching an entire sequence of conversions. Once all of the channels comprising a sequence have
 *    been converted, a subsequent trigger will repeat the sequence beginning with the first enabled
 *    channel. Interrupt generation will still occur either after each individual conversion or at
 *    the end of the entire sequence, depending on the state of the MODE bit.
 */
#define ADC_SEQ_CTRL_SINGLESTEP(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SINGLESTEP_SHIFT)) & ADC_SEQ_CTRL_SINGLESTEP_MASK)
#define ADC_SEQ_CTRL_LOWPRIO_MASK                (0x20000000U)
#define ADC_SEQ_CTRL_LOWPRIO_SHIFT               (29U)
/*! LOWPRIO - Set priority for sequence A.
 *  0b0..Low priority. Any B trigger which occurs while an A conversion sequence is active will be ignored and lost.
 *  0b1..High priority. Setting this bit to a 1 will permit any enabled B sequence trigger (including a B sequence
 *       software start) to immediately interrupt sequence A and launch a B sequence in it's place. The conversion
 *       currently in progress will be terminated. The A sequence that was interrupted will automatically resume
 *       after the B sequence completes. The channel whose conversion was terminated will be re-sampled and the
 *       conversion sequence will resume from that point.
 */
#define ADC_SEQ_CTRL_LOWPRIO(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_LOWPRIO_SHIFT)) & ADC_SEQ_CTRL_LOWPRIO_MASK)
#define ADC_SEQ_CTRL_MODE_MASK                   (0x40000000U)
#define ADC_SEQ_CTRL_MODE_SHIFT                  (30U)
/*! MODE - Indicates whether the primary method for retrieving conversion results for this sequence
 *    will be accomplished via reading the global data register (SEQA_GDAT) at the end of each
 *    conversion, or the individual channel result registers at the end of the entire sequence. Impacts
 *    when conversion-complete interrupt/DMA trigger for sequence-A will be generated and which
 *    overrun conditions contribute to an overrun interrupt as described below.
 *  0b0..End of conversion. The sequence A interrupt/DMA trigger will be set at the end of each individual ADC
 *       conversion performed under sequence A. This flag will mirror the DATAVALID bit in the SEQA_GDAT register. The
 *       OVERRUN bit in the SEQA_GDAT register will contribute to generation of an overrun interrupt/DMA trigger
 *       if enabled.
 *  0b1..End of sequence. The sequence A interrupt/DMA trigger will be set when the entire set of sequence-A
 *       conversions completes. This flag will need to be explicitly cleared by software or by the DMA-clear signal in
 *       this mode. The OVERRUN bit in the SEQA_GDAT register will NOT contribute to generation of an overrun
 *       interrupt/DMA trigger since it is assumed this register may not be utilized in this mode.
 */
#define ADC_SEQ_CTRL_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_MODE_SHIFT)) & ADC_SEQ_CTRL_MODE_MASK)
#define ADC_SEQ_CTRL_SEQ_ENA_MASK                (0x80000000U)
#define ADC_SEQ_CTRL_SEQ_ENA_SHIFT               (31U)
/*! SEQ_ENA - Sequence Enable. In order to avoid spuriously triggering the sequence, care should be
 *    taken to only set the SEQn_ENA bit when the selected trigger input is in its INACTIVE state
 *    (as defined by the TRIGPOL bit). If this condition is not met, the sequence will be triggered
 *    immediately upon being enabled. In order to avoid spuriously triggering the sequence, care
 *    should be taken to only set the SEQn_ENA bit when the selected trigger input is in its INACTIVE
 *    state (as defined by the TRIGPOL bit). If this condition is not met, the sequence will be
 *    triggered immediately upon being enabled.
 *  0b0..Disabled. Sequence n is disabled. Sequence n triggers are ignored. If this bit is cleared while sequence
 *       n is in progress, the sequence will be halted at the end of the current conversion. After the sequence is
 *       re-enabled, a new trigger will be required to restart the sequence beginning with the next enabled channel.
 *  0b1..Enabled. Sequence n is enabled.
 */
#define ADC_SEQ_CTRL_SEQ_ENA(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SEQ_ENA_SHIFT)) & ADC_SEQ_CTRL_SEQ_ENA_MASK)
/*! @} */

/* The count of ADC_SEQ_CTRL */
#define ADC_SEQ_CTRL_COUNT                       (2U)

/*! @name SEQ_GDAT - ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n. */
/*! @{ */
#define ADC_SEQ_GDAT_RESULT_MASK                 (0xFFF0U)
#define ADC_SEQ_GDAT_RESULT_SHIFT                (4U)
/*! RESULT - This field contains the 12-bit ADC conversion result from the most recent conversion
 *    performed under conversion sequence associated with this register. The result is a binary
 *    fraction representing the voltage on the currently-selected input channel as it falls within the
 *    range of VREFP to VREFN. Zero in the field indicates that the voltage on the input pin was less
 *    than, equal to, or close to that on VREFN, while 0xFFF indicates that the voltage on the input
 *    was close to, equal to, or greater than that on VREFP. DATAVALID = 1 indicates that this
 *    result has not yet been read.
 */
#define ADC_SEQ_GDAT_RESULT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_RESULT_SHIFT)) & ADC_SEQ_GDAT_RESULT_MASK)
#define ADC_SEQ_GDAT_THCMPRANGE_MASK             (0x30000U)
#define ADC_SEQ_GDAT_THCMPRANGE_SHIFT            (16U)
/*! THCMPRANGE - Indicates whether the result of the last conversion performed was above, below or
 *    within the range established by the designated threshold comparison registers (THRn_LOW and
 *    THRn_HIGH).
 */
#define ADC_SEQ_GDAT_THCMPRANGE(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPRANGE_SHIFT)) & ADC_SEQ_GDAT_THCMPRANGE_MASK)
#define ADC_SEQ_GDAT_THCMPCROSS_MASK             (0xC0000U)
#define ADC_SEQ_GDAT_THCMPCROSS_SHIFT            (18U)
/*! THCMPCROSS - Indicates whether the result of the last conversion performed represented a
 *    crossing of the threshold level established by the designated LOW threshold comparison register
 *    (THRn_LOW) and, if so, in what direction the crossing occurred.
 */
#define ADC_SEQ_GDAT_THCMPCROSS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPCROSS_SHIFT)) & ADC_SEQ_GDAT_THCMPCROSS_MASK)
#define ADC_SEQ_GDAT_CHN_MASK                    (0x3C000000U)
#define ADC_SEQ_GDAT_CHN_SHIFT                   (26U)
/*! CHN - These bits contain the channel from which the RESULT bits were converted (e.g. 0000
 *    identifies channel 0, 0001 channel 1, etc.).
 */
#define ADC_SEQ_GDAT_CHN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_CHN_SHIFT)) & ADC_SEQ_GDAT_CHN_MASK)
#define ADC_SEQ_GDAT_OVERRUN_MASK                (0x40000000U)
#define ADC_SEQ_GDAT_OVERRUN_SHIFT               (30U)
/*! OVERRUN - This bit is set if a new conversion result is loaded into the RESULT field before a
 *    previous result has been read - i.e. while the DATAVALID bit is set. This bit is cleared, along
 *    with the DATAVALID bit, whenever this register is read. This bit will contribute to an overrun
 *    interrupt/DMA trigger if the MODE bit (in SEQAA_CTRL) for the corresponding sequence is set
 *    to '0' (and if the overrun interrupt is enabled).
 */
#define ADC_SEQ_GDAT_OVERRUN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_OVERRUN_SHIFT)) & ADC_SEQ_GDAT_OVERRUN_MASK)
#define ADC_SEQ_GDAT_DATAVALID_MASK              (0x80000000U)
#define ADC_SEQ_GDAT_DATAVALID_SHIFT             (31U)
/*! DATAVALID - This bit is set to '1' at the end of each conversion when a new result is loaded
 *    into the RESULT field. It is cleared whenever this register is read. This bit will cause a
 *    conversion-complete interrupt for the corresponding sequence if the MODE bit (in SEQA_CTRL) for that
 *    sequence is set to 0 (and if the interrupt is enabled).
 */
#define ADC_SEQ_GDAT_DATAVALID(x)                (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_DATAVALID_SHIFT)) & ADC_SEQ_GDAT_DATAVALID_MASK)
/*! @} */

/* The count of ADC_SEQ_GDAT */
#define ADC_SEQ_GDAT_COUNT                       (2U)

/*! @name DAT - ADC Channel 0 Data register. This register contains the result of the most recent conversion completed on channel 0. */
/*! @{ */
#define ADC_DAT_RESULT_MASK                      (0xFFF0U)
#define ADC_DAT_RESULT_SHIFT                     (4U)
/*! RESULT - This field contains the 12-bit ADC conversion result from the last conversion performed
 *    on this channel. This will be a binary fraction representing the voltage on the AD0[n] pin,
 *    as it falls within the range of VREFP to VREFN. Zero in the field indicates that the voltage on
 *    the input pin was less than, equal to, or close to that on VREFN, while 0xFFF indicates that
 *    the voltage on the input was close to, equal to, or greater than that on VREFP.
 */
#define ADC_DAT_RESULT(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_DAT_RESULT_SHIFT)) & ADC_DAT_RESULT_MASK)
#define ADC_DAT_THCMPRANGE_MASK                  (0x30000U)
#define ADC_DAT_THCMPRANGE_SHIFT                 (16U)
/*! THCMPRANGE - Threshold Range Comparison result. 0x0 = In Range: The last completed conversion
 *    was greater than or equal to the value programmed into the designated LOW threshold register
 *    (THRn_LOW) but less than or equal to the value programmed into the designated HIGH threshold
 *    register (THRn_HIGH). 0x1 = Below Range: The last completed conversion on was less than the value
 *    programmed into the designated LOW threshold register (THRn_LOW). 0x2 = Above Range: The last
 *    completed conversion was greater than the value programmed into the designated HIGH threshold
 *    register (THRn_HIGH). 0x3 = Reserved.
 */
#define ADC_DAT_THCMPRANGE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPRANGE_SHIFT)) & ADC_DAT_THCMPRANGE_MASK)
#define ADC_DAT_THCMPCROSS_MASK                  (0xC0000U)
#define ADC_DAT_THCMPCROSS_SHIFT                 (18U)
/*! THCMPCROSS - Threshold Crossing Comparison result. 0x0 = No threshold Crossing detected: The
 *    most recent completed conversion on this channel had the same relationship (above or below) to
 *    the threshold value established by the designated LOW threshold register (THRn_LOW) as did the
 *    previous conversion on this channel. 0x1 = Reserved. 0x2 = Downward Threshold Crossing
 *    Detected. Indicates that a threshold crossing in the downward direction has occurred - i.e. the
 *    previous sample on this channel was above the threshold value established by the designated LOW
 *    threshold register (THRn_LOW) and the current sample is below that threshold. 0x3 = Upward
 *    Threshold Crossing Detected. Indicates that a threshold crossing in the upward direction has occurred
 *    - i.e. the previous sample on this channel was below the threshold value established by the
 *    designated LOW threshold register (THRn_LOW) and the current sample is above that threshold.
 */
#define ADC_DAT_THCMPCROSS(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPCROSS_SHIFT)) & ADC_DAT_THCMPCROSS_MASK)
#define ADC_DAT_CHANNEL_MASK                     (0x3C000000U)
#define ADC_DAT_CHANNEL_SHIFT                    (26U)
/*! CHANNEL - This field is hard-coded to contain the channel number that this particular register
 *    relates to (i.e. this field will contain 0b0000 for the DAT0 register, 0b0001 for the DAT1
 *    register, etc)
 */
#define ADC_DAT_CHANNEL(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_CHANNEL_SHIFT)) & ADC_DAT_CHANNEL_MASK)
#define ADC_DAT_OVERRUN_MASK                     (0x40000000U)
#define ADC_DAT_OVERRUN_SHIFT                    (30U)
/*! OVERRUN - This bit will be set to a 1 if a new conversion on this channel completes and
 *    overwrites the previous contents of the RESULT field before it has been read - i.e. while the DONE bit
 *    is set. This bit is cleared, along with the DONE bit, whenever this register is read or when
 *    the data related to this channel is read from either of the global SEQn_GDAT registers. This
 *    bit (in any of the 12 registers) will cause an overrun interrupt/DMA trigger to be asserted if
 *    the overrun interrupt is enabled. While it is allowed to include the same channels in both
 *    conversion sequences, doing so may cause erratic behavior of the DONE and OVERRUN bits in the
 *    data registers associated with any of the channels that are shared between the two sequences. Any
 *    erratic OVERRUN behavior will also affect overrun interrupt generation, if enabled.
 */
#define ADC_DAT_OVERRUN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_OVERRUN_SHIFT)) & ADC_DAT_OVERRUN_MASK)
#define ADC_DAT_DATAVALID_MASK                   (0x80000000U)
#define ADC_DAT_DATAVALID_SHIFT                  (31U)
/*! DATAVALID - This bit is set to 1 when an ADC conversion on this channel completes. This bit is
 *    cleared whenever this register is read or when the data related to this channel is read from
 *    either of the global SEQn_GDAT registers. While it is allowed to include the same channels in
 *    both conversion sequences, doing so may cause erratic behavior of the DONE and OVERRUN bits in
 *    the data registers associated with any of the channels that are shared between the two
 *    sequences. Any erratic OVERRUN behavior will also affect overrun interrupt generation, if enabled.
 */
#define ADC_DAT_DATAVALID(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_DAT_DATAVALID_SHIFT)) & ADC_DAT_DATAVALID_MASK)
/*! @} */

/* The count of ADC_DAT */
#define ADC_DAT_COUNT                            (12U)

/*! @name THR0_LOW - ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
/*! @{ */
#define ADC_THR0_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR0_LOW_THRLOW_SHIFT                (4U)
/*! THRLOW - Low threshold value against which ADC results will be compared
 */
#define ADC_THR0_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR0_LOW_THRLOW_SHIFT)) & ADC_THR0_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR1_LOW - ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */
#define ADC_THR1_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR1_LOW_THRLOW_SHIFT                (4U)
/*! THRLOW - Low threshold value against which ADC results will be compared
 */
#define ADC_THR1_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR1_LOW_THRLOW_SHIFT)) & ADC_THR1_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR0_HIGH - ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
/*! @{ */
#define ADC_THR0_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR0_HIGH_THRHIGH_SHIFT              (4U)
/*! THRHIGH - High threshold value against which ADC results will be compared
 */
#define ADC_THR0_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR0_HIGH_THRHIGH_SHIFT)) & ADC_THR0_HIGH_THRHIGH_MASK)
/*! @} */

/*! @name THR1_HIGH - ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */
#define ADC_THR1_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR1_HIGH_THRHIGH_SHIFT              (4U)
/*! THRHIGH - High threshold value against which ADC results will be compared
 */
#define ADC_THR1_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR1_HIGH_THRHIGH_SHIFT)) & ADC_THR1_HIGH_THRHIGH_MASK)
/*! @} */

/*! @name CHAN_THRSEL - ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel */
/*! @{ */
#define ADC_CHAN_THRSEL_CH0_THRSEL_MASK          (0x1U)
#define ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT         (0U)
/*! CH0_THRSEL - Threshold select for channel 0.
 *  0b0..Threshold 0. Results for this channel will be compared against the threshold levels indicated in the THR0_LOW and THR0_HIGH registers.
 *  0b1..Threshold 1. Results for this channel will be compared against the threshold levels indicated in the THR1_LOW and THR1_HIGH registers.
 */
#define ADC_CHAN_THRSEL_CH0_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH0_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH1_THRSEL_MASK          (0x2U)
#define ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT         (1U)
/*! CH1_THRSEL - Threshold select for channel 1. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH1_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH1_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH2_THRSEL_MASK          (0x4U)
#define ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT         (2U)
/*! CH2_THRSEL - Threshold select for channel 2. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH2_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH2_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH3_THRSEL_MASK          (0x8U)
#define ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT         (3U)
/*! CH3_THRSEL - Threshold select for channel 3. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH3_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH3_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH4_THRSEL_MASK          (0x10U)
#define ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT         (4U)
/*! CH4_THRSEL - Threshold select for channel 4. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH4_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH4_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH5_THRSEL_MASK          (0x20U)
#define ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT         (5U)
/*! CH5_THRSEL - Threshold select for channel 5. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH5_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH5_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH6_THRSEL_MASK          (0x40U)
#define ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT         (6U)
/*! CH6_THRSEL - Threshold select for channel 6. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH6_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH6_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH7_THRSEL_MASK          (0x80U)
#define ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT         (7U)
/*! CH7_THRSEL - Threshold select for channel 7. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH7_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH7_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH8_THRSEL_MASK          (0x100U)
#define ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT         (8U)
/*! CH8_THRSEL - Threshold select for channel 8. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH8_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH8_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH9_THRSEL_MASK          (0x200U)
#define ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT         (9U)
/*! CH9_THRSEL - Threshold select for channel 9. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH9_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH9_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH10_THRSEL_MASK         (0x400U)
#define ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT        (10U)
/*! CH10_THRSEL - Threshold select for channel 10. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH10_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH10_THRSEL_MASK)
#define ADC_CHAN_THRSEL_CH11_THRSEL_MASK         (0x800U)
#define ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT        (11U)
/*! CH11_THRSEL - Threshold select for channel 11. See description for channel 0.
 */
#define ADC_CHAN_THRSEL_CH11_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH11_THRSEL_MASK)
/*! @} */

/*! @name INTEN - ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated. */
/*! @{ */
#define ADC_INTEN_SEQA_INTEN_MASK                (0x1U)
#define ADC_INTEN_SEQA_INTEN_SHIFT               (0U)
/*! SEQA_INTEN - Sequence A interrupt enable.
 *  0b0..Disabled. The sequence A interrupt/DMA trigger is disabled.
 *  0b1..Enabled. The sequence A interrupt/DMA trigger is enabled and will be asserted either upon completion of
 *       each individual conversion performed as part of sequence A, or upon completion of the entire A sequence of
 *       conversions, depending on the MODE bit in the SEQA_CTRL register.
 */
#define ADC_INTEN_SEQA_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQA_INTEN_SHIFT)) & ADC_INTEN_SEQA_INTEN_MASK)
#define ADC_INTEN_SEQB_INTEN_MASK                (0x2U)
#define ADC_INTEN_SEQB_INTEN_SHIFT               (1U)
/*! SEQB_INTEN - Sequence B interrupt enable.
 *  0b0..Disabled. The sequence B interrupt/DMA trigger is disabled.
 *  0b1..Enabled. The sequence B interrupt/DMA trigger is enabled and will be asserted either upon completion of
 *       each individual conversion performed as part of sequence B, or upon completion of the entire B sequence of
 *       conversions, depending on the MODE bit in the SEQB_CTRL register.
 */
#define ADC_INTEN_SEQB_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQB_INTEN_SHIFT)) & ADC_INTEN_SEQB_INTEN_MASK)
#define ADC_INTEN_OVR_INTEN_MASK                 (0x4U)
#define ADC_INTEN_OVR_INTEN_SHIFT                (2U)
/*! OVR_INTEN - Overrun interrupt enable.
 *  0b0..Disabled. The overrun interrupt is disabled.
 *  0b1..Enabled. The overrun interrupt is enabled. Detection of an overrun condition on any of the 12 channel
 *       data registers will cause an overrun interrupt/DMA trigger. In addition, if the MODE bit for a particular
 *       sequence is 0, then an overrun in the global data register for that sequence will also cause this
 *       interrupt/DMA trigger to be asserted.
 */
#define ADC_INTEN_OVR_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_OVR_INTEN_SHIFT)) & ADC_INTEN_OVR_INTEN_MASK)
#define ADC_INTEN_ADCMPINTEN0_MASK               (0x18U)
#define ADC_INTEN_ADCMPINTEN0_SHIFT              (3U)
/*! ADCMPINTEN0 - Threshold comparison interrupt enable for channel 0.
 *  0b00..Disabled.
 *  0b01..Outside threshold.
 *  0b10..Crossing threshold.
 *  0b11..Reserved
 */
#define ADC_INTEN_ADCMPINTEN0(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN0_SHIFT)) & ADC_INTEN_ADCMPINTEN0_MASK)
#define ADC_INTEN_ADCMPINTEN1_MASK               (0x60U)
#define ADC_INTEN_ADCMPINTEN1_SHIFT              (5U)
/*! ADCMPINTEN1 - Channel 1 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN1(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN1_SHIFT)) & ADC_INTEN_ADCMPINTEN1_MASK)
#define ADC_INTEN_ADCMPINTEN2_MASK               (0x180U)
#define ADC_INTEN_ADCMPINTEN2_SHIFT              (7U)
/*! ADCMPINTEN2 - Channel 2 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN2(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN2_SHIFT)) & ADC_INTEN_ADCMPINTEN2_MASK)
#define ADC_INTEN_ADCMPINTEN3_MASK               (0x600U)
#define ADC_INTEN_ADCMPINTEN3_SHIFT              (9U)
/*! ADCMPINTEN3 - Channel 3 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN3(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN3_SHIFT)) & ADC_INTEN_ADCMPINTEN3_MASK)
#define ADC_INTEN_ADCMPINTEN4_MASK               (0x1800U)
#define ADC_INTEN_ADCMPINTEN4_SHIFT              (11U)
/*! ADCMPINTEN4 - Channel 4 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN4(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN4_SHIFT)) & ADC_INTEN_ADCMPINTEN4_MASK)
#define ADC_INTEN_ADCMPINTEN5_MASK               (0x6000U)
#define ADC_INTEN_ADCMPINTEN5_SHIFT              (13U)
/*! ADCMPINTEN5 - Channel 5 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN5(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN5_SHIFT)) & ADC_INTEN_ADCMPINTEN5_MASK)
#define ADC_INTEN_ADCMPINTEN6_MASK               (0x18000U)
#define ADC_INTEN_ADCMPINTEN6_SHIFT              (15U)
/*! ADCMPINTEN6 - Channel 6 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN6(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN6_SHIFT)) & ADC_INTEN_ADCMPINTEN6_MASK)
#define ADC_INTEN_ADCMPINTEN7_MASK               (0x60000U)
#define ADC_INTEN_ADCMPINTEN7_SHIFT              (17U)
/*! ADCMPINTEN7 - Channel 7 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN7(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN7_SHIFT)) & ADC_INTEN_ADCMPINTEN7_MASK)
#define ADC_INTEN_ADCMPINTEN8_MASK               (0x180000U)
#define ADC_INTEN_ADCMPINTEN8_SHIFT              (19U)
/*! ADCMPINTEN8 - Channel 8 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN8(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN8_SHIFT)) & ADC_INTEN_ADCMPINTEN8_MASK)
#define ADC_INTEN_ADCMPINTEN9_MASK               (0x600000U)
#define ADC_INTEN_ADCMPINTEN9_SHIFT              (21U)
/*! ADCMPINTEN9 - Channel 9 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN9(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN9_SHIFT)) & ADC_INTEN_ADCMPINTEN9_MASK)
#define ADC_INTEN_ADCMPINTEN10_MASK              (0x1800000U)
#define ADC_INTEN_ADCMPINTEN10_SHIFT             (23U)
/*! ADCMPINTEN10 - Channel 10 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN10(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN10_SHIFT)) & ADC_INTEN_ADCMPINTEN10_MASK)
#define ADC_INTEN_ADCMPINTEN11_MASK              (0x6000000U)
#define ADC_INTEN_ADCMPINTEN11_SHIFT             (25U)
/*! ADCMPINTEN11 - Channel 21 threshold comparison interrupt enable. See description for channel 0.
 */
#define ADC_INTEN_ADCMPINTEN11(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN11_SHIFT)) & ADC_INTEN_ADCMPINTEN11_MASK)
/*! @} */

/*! @name FLAGS - ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers). */
/*! @{ */
#define ADC_FLAGS_THCMP0_MASK                    (0x1U)
#define ADC_FLAGS_THCMP0_SHIFT                   (0U)
/*! THCMP0 - Threshold comparison event on Channel 0. Set to 1 upon either an out-of-range result or
 *    a threshold-crossing result if enabled to do so in the INTEN register. This bit is cleared by
 *    writing a 1.
 */
#define ADC_FLAGS_THCMP0(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP0_SHIFT)) & ADC_FLAGS_THCMP0_MASK)
#define ADC_FLAGS_THCMP1_MASK                    (0x2U)
#define ADC_FLAGS_THCMP1_SHIFT                   (1U)
/*! THCMP1 - Threshold comparison event on Channel 1. See description for channel 0.
 */
#define ADC_FLAGS_THCMP1(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP1_SHIFT)) & ADC_FLAGS_THCMP1_MASK)
#define ADC_FLAGS_THCMP2_MASK                    (0x4U)
#define ADC_FLAGS_THCMP2_SHIFT                   (2U)
/*! THCMP2 - Threshold comparison event on Channel 2. See description for channel 0.
 */
#define ADC_FLAGS_THCMP2(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP2_SHIFT)) & ADC_FLAGS_THCMP2_MASK)
#define ADC_FLAGS_THCMP3_MASK                    (0x8U)
#define ADC_FLAGS_THCMP3_SHIFT                   (3U)
/*! THCMP3 - Threshold comparison event on Channel 3. See description for channel 0.
 */
#define ADC_FLAGS_THCMP3(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP3_SHIFT)) & ADC_FLAGS_THCMP3_MASK)
#define ADC_FLAGS_THCMP4_MASK                    (0x10U)
#define ADC_FLAGS_THCMP4_SHIFT                   (4U)
/*! THCMP4 - Threshold comparison event on Channel 4. See description for channel 0.
 */
#define ADC_FLAGS_THCMP4(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP4_SHIFT)) & ADC_FLAGS_THCMP4_MASK)
#define ADC_FLAGS_THCMP5_MASK                    (0x20U)
#define ADC_FLAGS_THCMP5_SHIFT                   (5U)
/*! THCMP5 - Threshold comparison event on Channel 5. See description for channel 0.
 */
#define ADC_FLAGS_THCMP5(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP5_SHIFT)) & ADC_FLAGS_THCMP5_MASK)
#define ADC_FLAGS_THCMP6_MASK                    (0x40U)
#define ADC_FLAGS_THCMP6_SHIFT                   (6U)
/*! THCMP6 - Threshold comparison event on Channel 6. See description for channel 0.
 */
#define ADC_FLAGS_THCMP6(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP6_SHIFT)) & ADC_FLAGS_THCMP6_MASK)
#define ADC_FLAGS_THCMP7_MASK                    (0x80U)
#define ADC_FLAGS_THCMP7_SHIFT                   (7U)
/*! THCMP7 - Threshold comparison event on Channel 7. See description for channel 0.
 */
#define ADC_FLAGS_THCMP7(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP7_SHIFT)) & ADC_FLAGS_THCMP7_MASK)
#define ADC_FLAGS_THCMP8_MASK                    (0x100U)
#define ADC_FLAGS_THCMP8_SHIFT                   (8U)
/*! THCMP8 - Threshold comparison event on Channel 8. See description for channel 0.
 */
#define ADC_FLAGS_THCMP8(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP8_SHIFT)) & ADC_FLAGS_THCMP8_MASK)
#define ADC_FLAGS_THCMP9_MASK                    (0x200U)
#define ADC_FLAGS_THCMP9_SHIFT                   (9U)
/*! THCMP9 - Threshold comparison event on Channel 9. See description for channel 0.
 */
#define ADC_FLAGS_THCMP9(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP9_SHIFT)) & ADC_FLAGS_THCMP9_MASK)
#define ADC_FLAGS_THCMP10_MASK                   (0x400U)
#define ADC_FLAGS_THCMP10_SHIFT                  (10U)
/*! THCMP10 - Threshold comparison event on Channel 10. See description for channel 0.
 */
#define ADC_FLAGS_THCMP10(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP10_SHIFT)) & ADC_FLAGS_THCMP10_MASK)
#define ADC_FLAGS_THCMP11_MASK                   (0x800U)
#define ADC_FLAGS_THCMP11_SHIFT                  (11U)
/*! THCMP11 - Threshold comparison event on Channel 11. See description for channel 0.
 */
#define ADC_FLAGS_THCMP11(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP11_SHIFT)) & ADC_FLAGS_THCMP11_MASK)
#define ADC_FLAGS_OVERRUN0_MASK                  (0x1000U)
#define ADC_FLAGS_OVERRUN0_SHIFT                 (12U)
/*! OVERRUN0 - Mirrors the OVERRRUN status flag from the result register for ADC channel 0
 */
#define ADC_FLAGS_OVERRUN0(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN0_SHIFT)) & ADC_FLAGS_OVERRUN0_MASK)
#define ADC_FLAGS_OVERRUN1_MASK                  (0x2000U)
#define ADC_FLAGS_OVERRUN1_SHIFT                 (13U)
/*! OVERRUN1 - Mirrors the OVERRRUN status flag from the result register for ADC channel 1
 */
#define ADC_FLAGS_OVERRUN1(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN1_SHIFT)) & ADC_FLAGS_OVERRUN1_MASK)
#define ADC_FLAGS_OVERRUN2_MASK                  (0x4000U)
#define ADC_FLAGS_OVERRUN2_SHIFT                 (14U)
/*! OVERRUN2 - Mirrors the OVERRRUN status flag from the result register for ADC channel 2
 */
#define ADC_FLAGS_OVERRUN2(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN2_SHIFT)) & ADC_FLAGS_OVERRUN2_MASK)
#define ADC_FLAGS_OVERRUN3_MASK                  (0x8000U)
#define ADC_FLAGS_OVERRUN3_SHIFT                 (15U)
/*! OVERRUN3 - Mirrors the OVERRRUN status flag from the result register for ADC channel 3
 */
#define ADC_FLAGS_OVERRUN3(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN3_SHIFT)) & ADC_FLAGS_OVERRUN3_MASK)
#define ADC_FLAGS_OVERRUN4_MASK                  (0x10000U)
#define ADC_FLAGS_OVERRUN4_SHIFT                 (16U)
/*! OVERRUN4 - Mirrors the OVERRRUN status flag from the result register for ADC channel 4
 */
#define ADC_FLAGS_OVERRUN4(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN4_SHIFT)) & ADC_FLAGS_OVERRUN4_MASK)
#define ADC_FLAGS_OVERRUN5_MASK                  (0x20000U)
#define ADC_FLAGS_OVERRUN5_SHIFT                 (17U)
/*! OVERRUN5 - Mirrors the OVERRRUN status flag from the result register for ADC channel 5
 */
#define ADC_FLAGS_OVERRUN5(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN5_SHIFT)) & ADC_FLAGS_OVERRUN5_MASK)
#define ADC_FLAGS_OVERRUN6_MASK                  (0x40000U)
#define ADC_FLAGS_OVERRUN6_SHIFT                 (18U)
/*! OVERRUN6 - Mirrors the OVERRRUN status flag from the result register for ADC channel 6
 */
#define ADC_FLAGS_OVERRUN6(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN6_SHIFT)) & ADC_FLAGS_OVERRUN6_MASK)
#define ADC_FLAGS_OVERRUN7_MASK                  (0x80000U)
#define ADC_FLAGS_OVERRUN7_SHIFT                 (19U)
/*! OVERRUN7 - Mirrors the OVERRRUN status flag from the result register for ADC channel 7
 */
#define ADC_FLAGS_OVERRUN7(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN7_SHIFT)) & ADC_FLAGS_OVERRUN7_MASK)
#define ADC_FLAGS_OVERRUN8_MASK                  (0x100000U)
#define ADC_FLAGS_OVERRUN8_SHIFT                 (20U)
/*! OVERRUN8 - Mirrors the OVERRRUN status flag from the result register for ADC channel 8
 */
#define ADC_FLAGS_OVERRUN8(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN8_SHIFT)) & ADC_FLAGS_OVERRUN8_MASK)
#define ADC_FLAGS_OVERRUN9_MASK                  (0x200000U)
#define ADC_FLAGS_OVERRUN9_SHIFT                 (21U)
/*! OVERRUN9 - Mirrors the OVERRRUN status flag from the result register for ADC channel 9
 */
#define ADC_FLAGS_OVERRUN9(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN9_SHIFT)) & ADC_FLAGS_OVERRUN9_MASK)
#define ADC_FLAGS_OVERRUN10_MASK                 (0x400000U)
#define ADC_FLAGS_OVERRUN10_SHIFT                (22U)
/*! OVERRUN10 - Mirrors the OVERRRUN status flag from the result register for ADC channel 10
 */
#define ADC_FLAGS_OVERRUN10(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN10_SHIFT)) & ADC_FLAGS_OVERRUN10_MASK)
#define ADC_FLAGS_OVERRUN11_MASK                 (0x800000U)
#define ADC_FLAGS_OVERRUN11_SHIFT                (23U)
/*! OVERRUN11 - Mirrors the OVERRRUN status flag from the result register for ADC channel 11
 */
#define ADC_FLAGS_OVERRUN11(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN11_SHIFT)) & ADC_FLAGS_OVERRUN11_MASK)
#define ADC_FLAGS_SEQA_OVR_MASK                  (0x1000000U)
#define ADC_FLAGS_SEQA_OVR_SHIFT                 (24U)
/*! SEQA_OVR - Mirrors the global OVERRUN status flag in the SEQA_GDAT register
 */
#define ADC_FLAGS_SEQA_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_OVR_SHIFT)) & ADC_FLAGS_SEQA_OVR_MASK)
#define ADC_FLAGS_SEQB_OVR_MASK                  (0x2000000U)
#define ADC_FLAGS_SEQB_OVR_SHIFT                 (25U)
/*! SEQB_OVR - Mirrors the global OVERRUN status flag in the SEQB_GDAT register
 */
#define ADC_FLAGS_SEQB_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_OVR_SHIFT)) & ADC_FLAGS_SEQB_OVR_MASK)
#define ADC_FLAGS_SEQA_INT_MASK                  (0x10000000U)
#define ADC_FLAGS_SEQA_INT_SHIFT                 (28U)
/*! SEQA_INT - Sequence A interrupt/DMA trigger. If the MODE bit in the SEQA_CTRL register is 0,
 *    this flag will mirror the DATAVALID bit in the sequence A global data register (SEQA_GDAT), which
 *    is set at the end of every ADC conversion performed as part of sequence A. It will be cleared
 *    automatically when the SEQA_GDAT register is read. If the MODE bit in the SEQA_CTRL register
 *    is 1, this flag will be set upon completion of an entire A sequence. In this case it must be
 *    cleared by writing a 1 to this SEQA_INT bit. This interrupt must be enabled in the INTEN
 *    register.
 */
#define ADC_FLAGS_SEQA_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_INT_SHIFT)) & ADC_FLAGS_SEQA_INT_MASK)
#define ADC_FLAGS_SEQB_INT_MASK                  (0x20000000U)
#define ADC_FLAGS_SEQB_INT_SHIFT                 (29U)
/*! SEQB_INT - Sequence A interrupt/DMA trigger. If the MODE bit in the SEQB_CTRL register is 0,
 *    this flag will mirror the DATAVALID bit in the sequence A global data register (SEQB_GDAT), which
 *    is set at the end of every ADC conversion performed as part of sequence B. It will be cleared
 *    automatically when the SEQB_GDAT register is read. If the MODE bit in the SEQB_CTRL register
 *    is 1, this flag will be set upon completion of an entire B sequence. In this case it must be
 *    cleared by writing a 1 to this SEQB_INT bit. This interrupt must be enabled in the INTEN
 *    register.
 */
#define ADC_FLAGS_SEQB_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_INT_SHIFT)) & ADC_FLAGS_SEQB_INT_MASK)
#define ADC_FLAGS_THCMP_INT_MASK                 (0x40000000U)
#define ADC_FLAGS_THCMP_INT_SHIFT                (30U)
/*! THCMP_INT - Threshold Comparison Interrupt. This bit will be set if any of the THCMP flags in
 *    the lower bits of this register are set to 1 (due to an enabled out-of-range or
 *    threshold-crossing event on any channel). Each type of threshold comparison interrupt on each channel must be
 *    individually enabled in the INTEN register to cause this interrupt. This bit will be cleared
 *    when all of the individual threshold flags are cleared via writing 1s to those bits.
 */
#define ADC_FLAGS_THCMP_INT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP_INT_SHIFT)) & ADC_FLAGS_THCMP_INT_MASK)
#define ADC_FLAGS_OVR_INT_MASK                   (0x80000000U)
#define ADC_FLAGS_OVR_INT_SHIFT                  (31U)
/*! OVR_INT - Overrun Interrupt flag. Any overrun bit in any of the individual channel data
 *    registers will cause this interrupt. In addition, if the MODE bit in either of the SEQn_CTRL registers
 *    is 0 then the OVERRUN bit in the corresponding SEQn_GDAT register will also cause this
 *    interrupt. This interrupt must be enabled in the INTEN register. This bit will be cleared when all
 *    of the individual overrun bits have been cleared via reading the corresponding data registers.
 */
#define ADC_FLAGS_OVR_INT(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVR_INT_SHIFT)) & ADC_FLAGS_OVR_INT_MASK)
/*! @} */

/*! @name STARTUP - ADC Startup register. */
/*! @{ */
#define ADC_STARTUP_ADC_ENA_MASK                 (0x1U)
#define ADC_STARTUP_ADC_ENA_SHIFT                (0U)
/*! ADC_ENA - ADC Enable bit. This bit can only be set to a 1 by software. It is cleared
 *    automatically whenever the ADC is powered down. This bit must not be set until at least 10 microseconds
 *    after the ADC is powered up (typically by altering a system-level ADC power control bit).
 */
#define ADC_STARTUP_ADC_ENA(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_STARTUP_ADC_ENA_SHIFT)) & ADC_STARTUP_ADC_ENA_MASK)
#define ADC_STARTUP_ADC_INIT_MASK                (0x2U)
#define ADC_STARTUP_ADC_INIT_SHIFT               (1U)
/*! ADC_INIT - ADC Initialization. After enabling the ADC (setting the ADC_ENA bit), the API routine
 *    will EITHER set this bit or the CALIB bit in the CALIB register, depending on whether or not
 *    calibration is required. Setting this bit will launch the 'dummy' conversion cycle that is
 *    required if a calibration is not performed. It will also reload the stored calibration value from
 *    a previous calibration unless the BYPASSCAL bit is set. This bit should only be set AFTER the
 *    ADC_ENA bit is set and after the CALIREQD bit is tested to determine whether a calibration or
 *    an ADC dummy conversion cycle is required. It should not be set during the same write that
 *    sets the ADC_ENA bit. This bit can only be set to a '1' by software. It is cleared automatically
 *    when the 'dummy' conversion cycle completes.
 */
#define ADC_STARTUP_ADC_INIT(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_STARTUP_ADC_INIT_SHIFT)) & ADC_STARTUP_ADC_INIT_MASK)
/*! @} */

/*! @name CALIB - ADC Calibration register. */
/*! @{ */
#define ADC_CALIB_CALIB_MASK                     (0x1U)
#define ADC_CALIB_CALIB_SHIFT                    (0U)
/*! CALIB - Calibration request. Setting this bit will launch an ADC calibration cycle. This bit can
 *    only be set to a '1' by software. It is cleared automatically when the calibration cycle
 *    completes.
 */
#define ADC_CALIB_CALIB(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALIB_SHIFT)) & ADC_CALIB_CALIB_MASK)
#define ADC_CALIB_CALREQD_MASK                   (0x2U)
#define ADC_CALIB_CALREQD_SHIFT                  (1U)
/*! CALREQD - Calibration required. This read-only bit indicates if calibration is required when
 *    enabling the ADC. CALREQD will be '1' if no calibration has been run since the chip was
 *    powered-up and if the BYPASSCAL bit in the CTRL register is low. Software will test this bit to
 *    determine whether to initiate a calibration cycle or whether to set the ADC_INIT bit (in the STARTUP
 *    register) to launch the ADC initialization process which includes a 'dummy' conversion cycle.
 *    Note: A 'dummy' conversion cycle requires approximately 6 ADC clocks as opposed to 81 clocks
 *    required for calibration.
 */
#define ADC_CALIB_CALREQD(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALREQD_SHIFT)) & ADC_CALIB_CALREQD_MASK)
#define ADC_CALIB_CALVALUE_MASK                  (0x1FCU)
#define ADC_CALIB_CALVALUE_SHIFT                 (2U)
/*! CALVALUE - Calibration Value. This read-only field displays the calibration value established
 *    during last calibration cycle. This value is not typically of any use to the user.
 */
#define ADC_CALIB_CALVALUE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_CALIB_CALVALUE_SHIFT)) & ADC_CALIB_CALVALUE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x400A0000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_SEQ_IRQS                             { ADC0_SEQA_IRQn, ADC0_SEQB_IRQn }
#define ADC_THCMP_IRQS                           { ADC0_THCMP_IRQn }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ASYNC_SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ASYNC_SYSCON_Peripheral_Access_Layer ASYNC_SYSCON Peripheral Access Layer
 * @{
 */

/** ASYNC_SYSCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t ASYNCPRESETCTRL;                   /**< Async peripheral reset control, offset: 0x0 */
  __O  uint32_t ASYNCPRESETCTRLSET;                /**< Set bits in ASYNCPRESETCTRL, offset: 0x4 */
  __O  uint32_t ASYNCPRESETCTRLCLR;                /**< Clear bits in ASYNCPRESETCTRL, offset: 0x8 */
       uint8_t RESERVED_0[4];
  __IO uint32_t ASYNCAPBCLKCTRL;                   /**< Async peripheral clock control, offset: 0x10 */
  __O  uint32_t ASYNCAPBCLKCTRLSET;                /**< Set bits in ASYNCAPBCLKCTRL, offset: 0x14 */
  __O  uint32_t ASYNCAPBCLKCTRLCLR;                /**< Clear bits in ASYNCAPBCLKCTRL, offset: 0x18 */
       uint8_t RESERVED_1[4];
  __IO uint32_t ASYNCAPBCLKSELA;                   /**< Async APB clock source select A, offset: 0x20 */
} ASYNC_SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- ASYNC_SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ASYNC_SYSCON_Register_Masks ASYNC_SYSCON Register Masks
 * @{
 */

/*! @name ASYNCPRESETCTRL - Async peripheral reset control */
/*! @{ */
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_MASK (0x2000U)
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_SHIFT (13U)
/*! CTIMER3 - Standard counter/timer CTIMER3 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRL_CTIMER3_MASK)
/*! @} */

/*! @name ASYNCPRESETCTRLSET - Set bits in ASYNCPRESETCTRL */
/*! @{ */
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_SHIFT (0U)
/*! ARST_SET - Writing ones to this register sets the corresponding bit or bits in the
 *    ASYNCPRESETCTRL register, if they are implemented. Bits that do not correspond to defined bits in
 *    ASYNCPRESETCTRL are reserved and only zeroes should be written to them.
 */
#define ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRLSET_ARST_SET_MASK)
/*! @} */

/*! @name ASYNCPRESETCTRLCLR - Clear bits in ASYNCPRESETCTRL */
/*! @{ */
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_SHIFT (0U)
/*! ARST_CLR - Writing ones to this register clears the corresponding bit or bits in the
 *    ASYNCPRESETCTRL register, if they are implemented. Bits that do not correspond to defined bits in
 *    ASYNCPRESETCTRL are reserved and only zeroes should be written to them.
 */
#define ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_SHIFT)) & ASYNC_SYSCON_ASYNCPRESETCTRLCLR_ARST_CLR_MASK)
/*! @} */

/*! @name ASYNCAPBCLKCTRL - Async peripheral clock control */
/*! @{ */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_MASK (0x2000U)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_SHIFT (13U)
/*! CTIMER3 - Controls the clock for CTIMER3. 0 = Disable; 1 = Enable.
 */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3(x)  (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRL_CTIMER3_MASK)
/*! @} */

/*! @name ASYNCAPBCLKCTRLSET - Set bits in ASYNCAPBCLKCTRL */
/*! @{ */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_SHIFT (0U)
/*! ACLK_SET - Writing ones to this register sets the corresponding bit or bits in the
 *    ASYNCAPBCLKCTRL register, if they are implemented. Bits that do not correspond to defined bits in
 *    ASYNCPRESETCTRL are reserved and only zeroes should be written to them.
 */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRLSET_ACLK_SET_MASK)
/*! @} */

/*! @name ASYNCAPBCLKCTRLCLR - Clear bits in ASYNCAPBCLKCTRL */
/*! @{ */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_MASK (0xFFFFFFFFU)
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_SHIFT (0U)
/*! ACLK_CLR - Writing ones to this register clears the corresponding bit or bits in the
 *    ASYNCAPBCLKCTRL register, if they are implemented. Bits that do not correspond to defined bits in
 *    ASYNCAPBCLKCTRL are reserved and only zeroes should be written to them.
 */
#define ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR(x) (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKCTRLCLR_ACLK_CLR_MASK)
/*! @} */

/*! @name ASYNCAPBCLKSELA - Async APB clock source select A */
/*! @{ */
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_MASK    (0x3U)
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_SHIFT   (0U)
/*! SEL - Clock source for asynchronous clock source selector A
 *  0b00..Main clock
 *  0b01..FRO 12 MHz
 *  0b10..Reserved setting
 *  0b11..Reserved setting
 */
#define ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL(x)      (((uint32_t)(((uint32_t)(x)) << ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_SHIFT)) & ASYNC_SYSCON_ASYNCAPBCLKSELA_SEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ASYNC_SYSCON_Register_Masks */


/* ASYNC_SYSCON - Peripheral instance base addresses */
/** Peripheral ASYNC_SYSCON base address */
#define ASYNC_SYSCON_BASE                        (0x40040000u)
/** Peripheral ASYNC_SYSCON base pointer */
#define ASYNC_SYSCON                             ((ASYNC_SYSCON_Type *)ASYNC_SYSCON_BASE)
/** Array initializer of ASYNC_SYSCON peripheral base addresses */
#define ASYNC_SYSCON_BASE_ADDRS                  { ASYNC_SYSCON_BASE }
/** Array initializer of ASYNC_SYSCON peripheral base pointers */
#define ASYNC_SYSCON_BASE_PTRS                   { ASYNC_SYSCON }

/*!
 * @}
 */ /* end of group ASYNC_SYSCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */

/** CRC - Register Layout Typedef */
typedef struct {
  __IO uint32_t MODE;                              /**< CRC mode register, offset: 0x0 */
  __IO uint32_t SEED;                              /**< CRC seed register, offset: 0x4 */
  union {                                          /* offset: 0x8 */
    __I  uint32_t SUM;                               /**< CRC checksum register, offset: 0x8 */
    __O  uint32_t WR_DATA;                           /**< CRC data register, offset: 0x8 */
  };
} CRC_Type;

/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/*! @name MODE - CRC mode register */
/*! @{ */
#define CRC_MODE_CRC_POLY_MASK                   (0x3U)
#define CRC_MODE_CRC_POLY_SHIFT                  (0U)
/*! CRC_POLY - CRC polynomial: 1X = CRC-32 polynomial 01 = CRC-16 polynomial 00 = CRC-CCITT polynomial
 */
#define CRC_MODE_CRC_POLY(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CRC_POLY_SHIFT)) & CRC_MODE_CRC_POLY_MASK)
#define CRC_MODE_BIT_RVS_WR_MASK                 (0x4U)
#define CRC_MODE_BIT_RVS_WR_SHIFT                (2U)
/*! BIT_RVS_WR - Data bit order: 1 = Bit order reverse for CRC_WR_DATA (per byte) 0 = No bit order reverse for CRC_WR_DATA (per byte)
 */
#define CRC_MODE_BIT_RVS_WR(x)                   (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_WR_SHIFT)) & CRC_MODE_BIT_RVS_WR_MASK)
#define CRC_MODE_CMPL_WR_MASK                    (0x8U)
#define CRC_MODE_CMPL_WR_SHIFT                   (3U)
/*! CMPL_WR - Data complement: 1 = 1's complement for CRC_WR_DATA 0 = No 1's complement for CRC_WR_DATA
 */
#define CRC_MODE_CMPL_WR(x)                      (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CMPL_WR_SHIFT)) & CRC_MODE_CMPL_WR_MASK)
#define CRC_MODE_BIT_RVS_SUM_MASK                (0x10U)
#define CRC_MODE_BIT_RVS_SUM_SHIFT               (4U)
/*! BIT_RVS_SUM - CRC sum bit order: 1 = Bit order reverse for CRC_SUM 0 = No bit order reverse for CRC_SUM
 */
#define CRC_MODE_BIT_RVS_SUM(x)                  (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_SUM_SHIFT)) & CRC_MODE_BIT_RVS_SUM_MASK)
#define CRC_MODE_CMPL_SUM_MASK                   (0x20U)
#define CRC_MODE_CMPL_SUM_SHIFT                  (5U)
/*! CMPL_SUM - CRC sum complement: 1 = 1's complement for CRC_SUM 0 = No 1's complement for CRC_SUM
 */
#define CRC_MODE_CMPL_SUM(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CMPL_SUM_SHIFT)) & CRC_MODE_CMPL_SUM_MASK)
/*! @} */

/*! @name SEED - CRC seed register */
/*! @{ */
#define CRC_SEED_CRC_SEED_MASK                   (0xFFFFFFFFU)
#define CRC_SEED_CRC_SEED_SHIFT                  (0U)
/*! CRC_SEED - A write access to this register will load CRC seed value to CRC_SUM register with
 *    selected bit order and 1's complement pre-processes. A write access to this register will
 *    overrule the CRC calculation in progresses.
 */
#define CRC_SEED_CRC_SEED(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_SEED_CRC_SEED_SHIFT)) & CRC_SEED_CRC_SEED_MASK)
/*! @} */

/*! @name SUM - CRC checksum register */
/*! @{ */
#define CRC_SUM_CRC_SUM_MASK                     (0xFFFFFFFFU)
#define CRC_SUM_CRC_SUM_SHIFT                    (0U)
/*! CRC_SUM - The most recent CRC sum can be read through this register with selected bit order and 1's complement post-processes.
 */
#define CRC_SUM_CRC_SUM(x)                       (((uint32_t)(((uint32_t)(x)) << CRC_SUM_CRC_SUM_SHIFT)) & CRC_SUM_CRC_SUM_MASK)
/*! @} */

/*! @name WR_DATA - CRC data register */
/*! @{ */
#define CRC_WR_DATA_CRC_WR_DATA_MASK             (0xFFFFFFFFU)
#define CRC_WR_DATA_CRC_WR_DATA_SHIFT            (0U)
/*! CRC_WR_DATA - Data written to this register will be taken to perform CRC calculation with
 *    selected bit order and 1's complement pre-process. Any write size 8, 16 or 32-bit are allowed and
 *    accept back-to-back transactions.
 */
#define CRC_WR_DATA_CRC_WR_DATA(x)               (((uint32_t)(((uint32_t)(x)) << CRC_WR_DATA_CRC_WR_DATA_SHIFT)) & CRC_WR_DATA_CRC_WR_DATA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC_ENGINE base address */
#define CRC_ENGINE_BASE                          (0x40095000u)
/** Peripheral CRC_ENGINE base pointer */
#define CRC_ENGINE                               ((CRC_Type *)CRC_ENGINE_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_ENGINE_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC_ENGINE }

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CTIMER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CTIMER_Peripheral_Access_Layer CTIMER Peripheral Access Layer
 * @{
 */

/** CTIMER - Register Layout Typedef */
typedef struct {
  __IO uint32_t IR;                                /**< Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending., offset: 0x0 */
  __IO uint32_t TCR;                               /**< Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR., offset: 0x4 */
  __IO uint32_t TC;                                /**< Timer Counter. The 32 bit TC is incremented every PR+1 cycles of the APB bus clock. The TC is controlled through the TCR., offset: 0x8 */
  __IO uint32_t PR;                                /**< Prescale Register. When the Prescale Counter (PC) is equal to this value, the next clock increments the TC and clears the PC., offset: 0xC */
  __IO uint32_t PC;                                /**< Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface., offset: 0x10 */
  __IO uint32_t MCR;                               /**< Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs., offset: 0x14 */
  __IO uint32_t MR[4];                             /**< Match Register . MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC., array offset: 0x18, array step: 0x4 */
  __IO uint32_t CCR;                               /**< Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place., offset: 0x28 */
  __I  uint32_t CR[4];                             /**< Capture Register . CR is loaded with the value of TC when there is an event on the CAPn. input., array offset: 0x2C, array step: 0x4 */
  __IO uint32_t EMR;                               /**< External Match Register. The EMR controls the match function and the external match pins., offset: 0x3C */
       uint8_t RESERVED_0[48];
  __IO uint32_t CTCR;                              /**< Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting., offset: 0x70 */
  __IO uint32_t PWMC;                              /**< PWM Control Register. The PWMCON enables PWM mode for the external match pins., offset: 0x74 */
} CTIMER_Type;

/* ----------------------------------------------------------------------------
   -- CTIMER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CTIMER_Register_Masks CTIMER Register Masks
 * @{
 */

/*! @name IR - Interrupt Register. The IR can be written to clear interrupts. The IR can be read to identify which of eight possible interrupt sources are pending. */
/*! @{ */
#define CTIMER_IR_MR0INT_MASK                    (0x1U)
#define CTIMER_IR_MR0INT_SHIFT                   (0U)
/*! MR0INT - Interrupt flag for match channel 0.
 */
#define CTIMER_IR_MR0INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR0INT_SHIFT)) & CTIMER_IR_MR0INT_MASK)
#define CTIMER_IR_MR1INT_MASK                    (0x2U)
#define CTIMER_IR_MR1INT_SHIFT                   (1U)
/*! MR1INT - Interrupt flag for match channel 1.
 */
#define CTIMER_IR_MR1INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR1INT_SHIFT)) & CTIMER_IR_MR1INT_MASK)
#define CTIMER_IR_MR2INT_MASK                    (0x4U)
#define CTIMER_IR_MR2INT_SHIFT                   (2U)
/*! MR2INT - Interrupt flag for match channel 2.
 */
#define CTIMER_IR_MR2INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR2INT_SHIFT)) & CTIMER_IR_MR2INT_MASK)
#define CTIMER_IR_MR3INT_MASK                    (0x8U)
#define CTIMER_IR_MR3INT_SHIFT                   (3U)
/*! MR3INT - Interrupt flag for match channel 3.
 */
#define CTIMER_IR_MR3INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_MR3INT_SHIFT)) & CTIMER_IR_MR3INT_MASK)
#define CTIMER_IR_CR0INT_MASK                    (0x10U)
#define CTIMER_IR_CR0INT_SHIFT                   (4U)
/*! CR0INT - Interrupt flag for capture channel 0 event.
 */
#define CTIMER_IR_CR0INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR0INT_SHIFT)) & CTIMER_IR_CR0INT_MASK)
#define CTIMER_IR_CR1INT_MASK                    (0x20U)
#define CTIMER_IR_CR1INT_SHIFT                   (5U)
/*! CR1INT - Interrupt flag for capture channel 1 event.
 */
#define CTIMER_IR_CR1INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR1INT_SHIFT)) & CTIMER_IR_CR1INT_MASK)
#define CTIMER_IR_CR2INT_MASK                    (0x40U)
#define CTIMER_IR_CR2INT_SHIFT                   (6U)
/*! CR2INT - Interrupt flag for capture channel 2 event.
 */
#define CTIMER_IR_CR2INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR2INT_SHIFT)) & CTIMER_IR_CR2INT_MASK)
#define CTIMER_IR_CR3INT_MASK                    (0x80U)
#define CTIMER_IR_CR3INT_SHIFT                   (7U)
/*! CR3INT - Interrupt flag for capture channel 3 event.
 */
#define CTIMER_IR_CR3INT(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_IR_CR3INT_SHIFT)) & CTIMER_IR_CR3INT_MASK)
/*! @} */

/*! @name TCR - Timer Control Register. The TCR is used to control the Timer Counter functions. The Timer Counter can be disabled or reset through the TCR. */
/*! @{ */
#define CTIMER_TCR_CEN_MASK                      (0x1U)
#define CTIMER_TCR_CEN_SHIFT                     (0U)
/*! CEN - Counter enable.
 *  0b0..Disabled.The counters are disabled.
 *  0b1..Enabled. The Timer Counter and Prescale Counter are enabled.
 */
#define CTIMER_TCR_CEN(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_TCR_CEN_SHIFT)) & CTIMER_TCR_CEN_MASK)
#define CTIMER_TCR_CRST_MASK                     (0x2U)
#define CTIMER_TCR_CRST_SHIFT                    (1U)
/*! CRST - Counter reset.
 *  0b0..Disabled. Do nothing.
 *  0b1..Enabled. The Timer Counter and the Prescale Counter are synchronously reset on the next positive edge of
 *       the APB bus clock. The counters remain reset until TCR[1] is returned to zero.
 */
#define CTIMER_TCR_CRST(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_TCR_CRST_SHIFT)) & CTIMER_TCR_CRST_MASK)
/*! @} */

/*! @name TC - Timer Counter. The 32 bit TC is incremented every PR+1 cycles of the APB bus clock. The TC is controlled through the TCR. */
/*! @{ */
#define CTIMER_TC_TCVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_TC_TCVAL_SHIFT                    (0U)
/*! TCVAL - Timer counter value.
 */
#define CTIMER_TC_TCVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_TC_TCVAL_SHIFT)) & CTIMER_TC_TCVAL_MASK)
/*! @} */

/*! @name PR - Prescale Register. When the Prescale Counter (PC) is equal to this value, the next clock increments the TC and clears the PC. */
/*! @{ */
#define CTIMER_PR_PRVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_PR_PRVAL_SHIFT                    (0U)
/*! PRVAL - Prescale counter value.
 */
#define CTIMER_PR_PRVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_PR_PRVAL_SHIFT)) & CTIMER_PR_PRVAL_MASK)
/*! @} */

/*! @name PC - Prescale Counter. The 32 bit PC is a counter which is incremented to the value stored in PR. When the value in PR is reached, the TC is incremented and the PC is cleared. The PC is observable and controllable through the bus interface. */
/*! @{ */
#define CTIMER_PC_PCVAL_MASK                     (0xFFFFFFFFU)
#define CTIMER_PC_PCVAL_SHIFT                    (0U)
/*! PCVAL - Prescale counter value.
 */
#define CTIMER_PC_PCVAL(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_PC_PCVAL_SHIFT)) & CTIMER_PC_PCVAL_MASK)
/*! @} */

/*! @name MCR - Match Control Register. The MCR is used to control if an interrupt is generated and if the TC is reset when a Match occurs. */
/*! @{ */
#define CTIMER_MCR_MR0I_MASK                     (0x1U)
#define CTIMER_MCR_MR0I_SHIFT                    (0U)
/*! MR0I - Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR0I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0I_SHIFT)) & CTIMER_MCR_MR0I_MASK)
#define CTIMER_MCR_MR0R_MASK                     (0x2U)
#define CTIMER_MCR_MR0R_SHIFT                    (1U)
/*! MR0R - Reset on MR0: the TC will be reset if MR0 matches it. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR0R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0R_SHIFT)) & CTIMER_MCR_MR0R_MASK)
#define CTIMER_MCR_MR0S_MASK                     (0x4U)
#define CTIMER_MCR_MR0S_SHIFT                    (2U)
/*! MR0S - Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR0S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR0S_SHIFT)) & CTIMER_MCR_MR0S_MASK)
#define CTIMER_MCR_MR1I_MASK                     (0x8U)
#define CTIMER_MCR_MR1I_SHIFT                    (3U)
/*! MR1I - Interrupt on MR1: an interrupt is generated when MR1 matches the value in the TC. 0 =
 *    disabled. 1 = enabled. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR1I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1I_SHIFT)) & CTIMER_MCR_MR1I_MASK)
#define CTIMER_MCR_MR1R_MASK                     (0x10U)
#define CTIMER_MCR_MR1R_SHIFT                    (4U)
/*! MR1R - Reset on MR1: the TC will be reset if MR1 matches it. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR1R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1R_SHIFT)) & CTIMER_MCR_MR1R_MASK)
#define CTIMER_MCR_MR1S_MASK                     (0x20U)
#define CTIMER_MCR_MR1S_SHIFT                    (5U)
/*! MR1S - Stop on MR1: the TC and PC will be stopped and TCR[0] will be set to 0 if MR1 matches the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR1S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR1S_SHIFT)) & CTIMER_MCR_MR1S_MASK)
#define CTIMER_MCR_MR2I_MASK                     (0x40U)
#define CTIMER_MCR_MR2I_SHIFT                    (6U)
/*! MR2I - Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR2I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2I_SHIFT)) & CTIMER_MCR_MR2I_MASK)
#define CTIMER_MCR_MR2R_MASK                     (0x80U)
#define CTIMER_MCR_MR2R_SHIFT                    (7U)
/*! MR2R - Reset on MR2: the TC will be reset if MR2 matches it. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR2R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2R_SHIFT)) & CTIMER_MCR_MR2R_MASK)
#define CTIMER_MCR_MR2S_MASK                     (0x100U)
#define CTIMER_MCR_MR2S_SHIFT                    (8U)
/*! MR2S - Stop on MR2: the TC and PC will be stopped and TCR[0] will be set to 0 if MR2 matches the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR2S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR2S_SHIFT)) & CTIMER_MCR_MR2S_MASK)
#define CTIMER_MCR_MR3I_MASK                     (0x200U)
#define CTIMER_MCR_MR3I_SHIFT                    (9U)
/*! MR3I - Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR3I(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3I_SHIFT)) & CTIMER_MCR_MR3I_MASK)
#define CTIMER_MCR_MR3R_MASK                     (0x400U)
#define CTIMER_MCR_MR3R_SHIFT                    (10U)
/*! MR3R - Reset on MR3: the TC will be reset if MR3 matches it. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR3R(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3R_SHIFT)) & CTIMER_MCR_MR3R_MASK)
#define CTIMER_MCR_MR3S_MASK                     (0x800U)
#define CTIMER_MCR_MR3S_SHIFT                    (11U)
/*! MR3S - Stop on MR3: the TC and PC will be stopped and TCR[0] will be set to 0 if MR3 matches the TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_MCR_MR3S(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MCR_MR3S_SHIFT)) & CTIMER_MCR_MR3S_MASK)
/*! @} */

/*! @name MR - Match Register . MR can be enabled through the MCR to reset the TC, stop both the TC and PC, and/or generate an interrupt every time MR matches the TC. */
/*! @{ */
#define CTIMER_MR_MATCH_MASK                     (0xFFFFFFFFU)
#define CTIMER_MR_MATCH_SHIFT                    (0U)
/*! MATCH - Timer counter match value.
 */
#define CTIMER_MR_MATCH(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_MR_MATCH_SHIFT)) & CTIMER_MR_MATCH_MASK)
/*! @} */

/* The count of CTIMER_MR */
#define CTIMER_MR_COUNT                          (4U)

/*! @name CCR - Capture Control Register. The CCR controls which edges of the capture inputs are used to load the Capture Registers and whether or not an interrupt is generated when a capture takes place. */
/*! @{ */
#define CTIMER_CCR_CAP0RE_MASK                   (0x1U)
#define CTIMER_CCR_CAP0RE_SHIFT                  (0U)
/*! CAP0RE - Rising edge of capture channel 0: a sequence of 0 then 1 causes CR0 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP0RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0RE_SHIFT)) & CTIMER_CCR_CAP0RE_MASK)
#define CTIMER_CCR_CAP0FE_MASK                   (0x2U)
#define CTIMER_CCR_CAP0FE_SHIFT                  (1U)
/*! CAP0FE - Falling edge of capture channel 0: a sequence of 1 then 0 causes CR0 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP0FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0FE_SHIFT)) & CTIMER_CCR_CAP0FE_MASK)
#define CTIMER_CCR_CAP0I_MASK                    (0x4U)
#define CTIMER_CCR_CAP0I_SHIFT                   (2U)
/*! CAP0I - Generate interrupt on channel 0 capture event: a CR0 load generates an interrupt.
 */
#define CTIMER_CCR_CAP0I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP0I_SHIFT)) & CTIMER_CCR_CAP0I_MASK)
#define CTIMER_CCR_CAP1RE_MASK                   (0x8U)
#define CTIMER_CCR_CAP1RE_SHIFT                  (3U)
/*! CAP1RE - Rising edge of capture channel 1: a sequence of 0 then 1 causes CR1 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP1RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1RE_SHIFT)) & CTIMER_CCR_CAP1RE_MASK)
#define CTIMER_CCR_CAP1FE_MASK                   (0x10U)
#define CTIMER_CCR_CAP1FE_SHIFT                  (4U)
/*! CAP1FE - Falling edge of capture channel 1: a sequence of 1 then 0 causes CR1 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP1FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1FE_SHIFT)) & CTIMER_CCR_CAP1FE_MASK)
#define CTIMER_CCR_CAP1I_MASK                    (0x20U)
#define CTIMER_CCR_CAP1I_SHIFT                   (5U)
/*! CAP1I - Generate interrupt on channel 1 capture event: a CR1 load generates an interrupt.
 */
#define CTIMER_CCR_CAP1I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP1I_SHIFT)) & CTIMER_CCR_CAP1I_MASK)
#define CTIMER_CCR_CAP2RE_MASK                   (0x40U)
#define CTIMER_CCR_CAP2RE_SHIFT                  (6U)
/*! CAP2RE - Rising edge of capture channel 2: a sequence of 0 then 1 causes CR2 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP2RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2RE_SHIFT)) & CTIMER_CCR_CAP2RE_MASK)
#define CTIMER_CCR_CAP2FE_MASK                   (0x80U)
#define CTIMER_CCR_CAP2FE_SHIFT                  (7U)
/*! CAP2FE - Falling edge of capture channel 2: a sequence of 1 then 0 causes CR2 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP2FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2FE_SHIFT)) & CTIMER_CCR_CAP2FE_MASK)
#define CTIMER_CCR_CAP2I_MASK                    (0x100U)
#define CTIMER_CCR_CAP2I_SHIFT                   (8U)
/*! CAP2I - Generate interrupt on channel 2 capture event: a CR2 load generates an interrupt.
 */
#define CTIMER_CCR_CAP2I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP2I_SHIFT)) & CTIMER_CCR_CAP2I_MASK)
#define CTIMER_CCR_CAP3RE_MASK                   (0x200U)
#define CTIMER_CCR_CAP3RE_SHIFT                  (9U)
/*! CAP3RE - Rising edge of capture channel 3: a sequence of 0 then 1 causes CR3 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP3RE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3RE_SHIFT)) & CTIMER_CCR_CAP3RE_MASK)
#define CTIMER_CCR_CAP3FE_MASK                   (0x400U)
#define CTIMER_CCR_CAP3FE_SHIFT                  (10U)
/*! CAP3FE - Falling edge of capture channel 3: a sequence of 1 then 0 causes CR3 to be loaded with
 *    the contents of TC. 0 = disabled. 1 = enabled.
 */
#define CTIMER_CCR_CAP3FE(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3FE_SHIFT)) & CTIMER_CCR_CAP3FE_MASK)
#define CTIMER_CCR_CAP3I_MASK                    (0x800U)
#define CTIMER_CCR_CAP3I_SHIFT                   (11U)
/*! CAP3I - Generate interrupt on channel 3 capture event: a CR3 load generates an interrupt.
 */
#define CTIMER_CCR_CAP3I(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CCR_CAP3I_SHIFT)) & CTIMER_CCR_CAP3I_MASK)
/*! @} */

/*! @name CR - Capture Register . CR is loaded with the value of TC when there is an event on the CAPn. input. */
/*! @{ */
#define CTIMER_CR_CAP_MASK                       (0xFFFFFFFFU)
#define CTIMER_CR_CAP_SHIFT                      (0U)
/*! CAP - Timer counter capture value.
 */
#define CTIMER_CR_CAP(x)                         (((uint32_t)(((uint32_t)(x)) << CTIMER_CR_CAP_SHIFT)) & CTIMER_CR_CAP_MASK)
/*! @} */

/* The count of CTIMER_CR */
#define CTIMER_CR_COUNT                          (4U)

/*! @name EMR - External Match Register. The EMR controls the match function and the external match pins. */
/*! @{ */
#define CTIMER_EMR_EM0_MASK                      (0x1U)
#define CTIMER_EMR_EM0_SHIFT                     (0U)
/*! EM0 - External Match 0. This bit reflects the state of output MAT0, whether or not this output
 *    is connected to a pin. When a match occurs between the TC and MR0, this bit can either toggle,
 *    go LOW, go HIGH, or do nothing, as selected by EMR[5:4]. This bit is driven to the MAT pins if
 *    the match function is selected via IOCON. 0 = LOW. 1 = HIGH.
 */
#define CTIMER_EMR_EM0(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM0_SHIFT)) & CTIMER_EMR_EM0_MASK)
#define CTIMER_EMR_EM1_MASK                      (0x2U)
#define CTIMER_EMR_EM1_SHIFT                     (1U)
/*! EM1 - External Match 1. This bit reflects the state of output MAT1, whether or not this output
 *    is connected to a pin. When a match occurs between the TC and MR1, this bit can either toggle,
 *    go LOW, go HIGH, or do nothing, as selected by EMR[7:6]. This bit is driven to the MAT pins if
 *    the match function is selected via IOCON. 0 = LOW. 1 = HIGH.
 */
#define CTIMER_EMR_EM1(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM1_SHIFT)) & CTIMER_EMR_EM1_MASK)
#define CTIMER_EMR_EM2_MASK                      (0x4U)
#define CTIMER_EMR_EM2_SHIFT                     (2U)
/*! EM2 - External Match 2. This bit reflects the state of output MAT2, whether or not this output
 *    is connected to a pin. When a match occurs between the TC and MR2, this bit can either toggle,
 *    go LOW, go HIGH, or do nothing, as selected by EMR[9:8]. This bit is driven to the MAT pins if
 *    the match function is selected via IOCON. 0 = LOW. 1 = HIGH.
 */
#define CTIMER_EMR_EM2(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM2_SHIFT)) & CTIMER_EMR_EM2_MASK)
#define CTIMER_EMR_EM3_MASK                      (0x8U)
#define CTIMER_EMR_EM3_SHIFT                     (3U)
/*! EM3 - External Match 3. This bit reflects the state of output MAT3, whether or not this output
 *    is connected to a pin. When a match occurs between the TC and MR3, this bit can either toggle,
 *    go LOW, go HIGH, or do nothing, as selected by MR[11:10]. This bit is driven to the MAT pins
 *    if the match function is selected via IOCON. 0 = LOW. 1 = HIGH.
 */
#define CTIMER_EMR_EM3(x)                        (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EM3_SHIFT)) & CTIMER_EMR_EM3_MASK)
#define CTIMER_EMR_EMC0_MASK                     (0x30U)
#define CTIMER_EMR_EMC0_SHIFT                    (4U)
/*! EMC0 - External Match Control 0. Determines the functionality of External Match 0.
 *  0b00..Do Nothing.
 *  0b01..Clear. Clear the corresponding External Match bit/output to 0 (MAT0 pin is LOW if pinned out).
 *  0b10..Set. Set the corresponding External Match bit/output to 1 (MAT0 pin is HIGH if pinned out).
 *  0b11..Toggle. Toggle the corresponding External Match bit/output.
 */
#define CTIMER_EMR_EMC0(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC0_SHIFT)) & CTIMER_EMR_EMC0_MASK)
#define CTIMER_EMR_EMC1_MASK                     (0xC0U)
#define CTIMER_EMR_EMC1_SHIFT                    (6U)
/*! EMC1 - External Match Control 1. Determines the functionality of External Match 1.
 *  0b00..Do Nothing.
 *  0b01..Clear. Clear the corresponding External Match bit/output to 0 (MAT1 pin is LOW if pinned out).
 *  0b10..Set. Set the corresponding External Match bit/output to 1 (MAT1 pin is HIGH if pinned out).
 *  0b11..Toggle. Toggle the corresponding External Match bit/output.
 */
#define CTIMER_EMR_EMC1(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC1_SHIFT)) & CTIMER_EMR_EMC1_MASK)
#define CTIMER_EMR_EMC2_MASK                     (0x300U)
#define CTIMER_EMR_EMC2_SHIFT                    (8U)
/*! EMC2 - External Match Control 2. Determines the functionality of External Match 2.
 *  0b00..Do Nothing.
 *  0b01..Clear. Clear the corresponding External Match bit/output to 0 (MAT2 pin is LOW if pinned out).
 *  0b10..Set. Set the corresponding External Match bit/output to 1 (MAT2 pin is HIGH if pinned out).
 *  0b11..Toggle. Toggle the corresponding External Match bit/output.
 */
#define CTIMER_EMR_EMC2(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC2_SHIFT)) & CTIMER_EMR_EMC2_MASK)
#define CTIMER_EMR_EMC3_MASK                     (0xC00U)
#define CTIMER_EMR_EMC3_SHIFT                    (10U)
/*! EMC3 - External Match Control 3. Determines the functionality of External Match 3.
 *  0b00..Do Nothing.
 *  0b01..Clear. Clear the corresponding External Match bit/output to 0 (MAT3 pin is LOW if pinned out).
 *  0b10..Set. Set the corresponding External Match bit/output to 1 (MAT3 pin is HIGH if pinned out).
 *  0b11..Toggle. Toggle the corresponding External Match bit/output.
 */
#define CTIMER_EMR_EMC3(x)                       (((uint32_t)(((uint32_t)(x)) << CTIMER_EMR_EMC3_SHIFT)) & CTIMER_EMR_EMC3_MASK)
/*! @} */

/*! @name CTCR - Count Control Register. The CTCR selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting. */
/*! @{ */
#define CTIMER_CTCR_CTMODE_MASK                  (0x3U)
#define CTIMER_CTCR_CTMODE_SHIFT                 (0U)
/*! CTMODE - Counter/Timer Mode This field selects which rising APB bus clock edges can increment
 *    Timer's Prescale Counter (PC), or clear PC and increment Timer Counter (TC). Timer Mode: the TC
 *    is incremented when the Prescale Counter matches the Prescale Register.
 *  0b00..Timer Mode. Incremented every rising APB bus clock edge.
 *  0b01..Counter Mode rising edge. TC is incremented on rising edges on the CAP input selected by bits 3:2.
 *  0b10..Counter Mode falling edge. TC is incremented on falling edges on the CAP input selected by bits 3:2.
 *  0b11..Counter Mode dual edge. TC is incremented on both edges on the CAP input selected by bits 3:2.
 */
#define CTIMER_CTCR_CTMODE(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_CTMODE_SHIFT)) & CTIMER_CTCR_CTMODE_MASK)
#define CTIMER_CTCR_CINSEL_MASK                  (0xCU)
#define CTIMER_CTCR_CINSEL_SHIFT                 (2U)
/*! CINSEL - Count Input Select When bits 1:0 in this register are not 00, these bits select which
 *    CAP pin is sampled for clocking. Note: If Counter mode is selected for a particular CAPn input
 *    in the CTCR, the 3 bits for that input in the Capture Control Register (CCR) must be
 *    programmed as 000. However, capture and/or interrupt can be selected for the other 3 CAPn inputs in the
 *    same timer.
 *  0b00..Channel 0. CAPn.0 for CTIMERn
 *  0b01..Channel 1. CAPn.1 for CTIMERn
 *  0b10..Channel 2. CAPn.2 for CTIMERn
 *  0b11..Channel 3. CAPn.3 for CTIMERn
 */
#define CTIMER_CTCR_CINSEL(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_CINSEL_SHIFT)) & CTIMER_CTCR_CINSEL_MASK)
#define CTIMER_CTCR_ENCC_MASK                    (0x10U)
#define CTIMER_CTCR_ENCC_SHIFT                   (4U)
/*! ENCC - Setting this bit to 1 enables clearing of the timer and the prescaler when the
 *    capture-edge event specified in bits 7:5 occurs.
 */
#define CTIMER_CTCR_ENCC(x)                      (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_ENCC_SHIFT)) & CTIMER_CTCR_ENCC_MASK)
#define CTIMER_CTCR_SELCC_MASK                   (0xE0U)
#define CTIMER_CTCR_SELCC_SHIFT                  (5U)
/*! SELCC - Edge select. When bit 4 is 1, these bits select which capture input edge will cause the
 *    timer and prescaler to be cleared. These bits have no effect when bit 4 is low. Values 0x2 to
 *    0x3 and 0x6 to 0x7 are reserved.
 *  0b000..Channel 0 Rising Edge. Rising edge of the signal on capture channel 0 clears the timer (if bit 4 is set).
 *  0b001..Channel 0 Falling Edge. Falling edge of the signal on capture channel 0 clears the timer (if bit 4 is set).
 *  0b010..Channel 1 Rising Edge. Rising edge of the signal on capture channel 1 clears the timer (if bit 4 is set).
 *  0b011..Channel 1 Falling Edge. Falling edge of the signal on capture channel 1 clears the timer (if bit 4 is set).
 *  0b100..Channel 2 Rising Edge. Rising edge of the signal on capture channel 2 clears the timer (if bit 4 is set).
 *  0b101..Channel 2 Falling Edge. Falling edge of the signal on capture channel 2 clears the timer (if bit 4 is set).
 */
#define CTIMER_CTCR_SELCC(x)                     (((uint32_t)(((uint32_t)(x)) << CTIMER_CTCR_SELCC_SHIFT)) & CTIMER_CTCR_SELCC_MASK)
/*! @} */

/*! @name PWMC - PWM Control Register. The PWMCON enables PWM mode for the external match pins. */
/*! @{ */
#define CTIMER_PWMC_PWMEN0_MASK                  (0x1U)
#define CTIMER_PWMC_PWMEN0_SHIFT                 (0U)
/*! PWMEN0 - PWM mode enable for channel0.
 *  0b0..Match. CTIMERn_MAT0 is controlled by EM0.
 *  0b1..PWM. PWM mode is enabled for CTIMERn_MAT0.
 */
#define CTIMER_PWMC_PWMEN0(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN0_SHIFT)) & CTIMER_PWMC_PWMEN0_MASK)
#define CTIMER_PWMC_PWMEN1_MASK                  (0x2U)
#define CTIMER_PWMC_PWMEN1_SHIFT                 (1U)
/*! PWMEN1 - PWM mode enable for channel1.
 *  0b0..Match. CTIMERn_MAT01 is controlled by EM1.
 *  0b1..PWM. PWM mode is enabled for CTIMERn_MAT1.
 */
#define CTIMER_PWMC_PWMEN1(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN1_SHIFT)) & CTIMER_PWMC_PWMEN1_MASK)
#define CTIMER_PWMC_PWMEN2_MASK                  (0x4U)
#define CTIMER_PWMC_PWMEN2_SHIFT                 (2U)
/*! PWMEN2 - PWM mode enable for channel2.
 *  0b0..Match. CTIMERn_MAT2 is controlled by EM2.
 *  0b1..PWM. PWM mode is enabled for CTIMERn_MAT2.
 */
#define CTIMER_PWMC_PWMEN2(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN2_SHIFT)) & CTIMER_PWMC_PWMEN2_MASK)
#define CTIMER_PWMC_PWMEN3_MASK                  (0x8U)
#define CTIMER_PWMC_PWMEN3_SHIFT                 (3U)
/*! PWMEN3 - PWM mode enable for channel3. Note: It is recommended to use match channel 3 to set the PWM cycle.
 *  0b0..Match. CTIMERn_MAT3 is controlled by EM3.
 *  0b1..PWM. PWM mode is enabled for CT132Bn_MAT3.
 */
#define CTIMER_PWMC_PWMEN3(x)                    (((uint32_t)(((uint32_t)(x)) << CTIMER_PWMC_PWMEN3_SHIFT)) & CTIMER_PWMC_PWMEN3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CTIMER_Register_Masks */


/* CTIMER - Peripheral instance base addresses */
/** Peripheral CTIMER0 base address */
#define CTIMER0_BASE                             (0x40008000u)
/** Peripheral CTIMER0 base pointer */
#define CTIMER0                                  ((CTIMER_Type *)CTIMER0_BASE)
/** Peripheral CTIMER1 base address */
#define CTIMER1_BASE                             (0x40009000u)
/** Peripheral CTIMER1 base pointer */
#define CTIMER1                                  ((CTIMER_Type *)CTIMER1_BASE)
/** Peripheral CTIMER3 base address */
#define CTIMER3_BASE                             (0x40048000u)
/** Peripheral CTIMER3 base pointer */
#define CTIMER3                                  ((CTIMER_Type *)CTIMER3_BASE)
/** Array initializer of CTIMER peripheral base addresses */
#define CTIMER_BASE_ADDRS                        { CTIMER0_BASE, CTIMER1_BASE, 0u, CTIMER3_BASE }
/** Array initializer of CTIMER peripheral base pointers */
#define CTIMER_BASE_PTRS                         { CTIMER0, CTIMER1, (CTIMER_Type *)0u, CTIMER3 }
/** Interrupt vectors for the CTIMER peripheral type */
#define CTIMER_IRQS                              { CTIMER0_IRQn, CTIMER1_IRQn, NotAvail_IRQn, CTIMER3_IRQn }

/*!
 * @}
 */ /* end of group CTIMER_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Peripheral_Access_Layer DMA Peripheral Access Layer
 * @{
 */

/** DMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< DMA control., offset: 0x0 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status., offset: 0x4 */
  __IO uint32_t SRAMBASE;                          /**< SRAM address of the channel configuration table., offset: 0x8 */
       uint8_t RESERVED_0[20];
  struct {                                         /* offset: 0x20, array step: 0x5C */
    __IO uint32_t ENABLESET;                         /**< Channel Enable read and Set for all DMA channels., array offset: 0x20, array step: 0x5C */
         uint8_t RESERVED_0[4];
    __O  uint32_t ENABLECLR;                         /**< Channel Enable Clear for all DMA channels., array offset: 0x28, array step: 0x5C */
         uint8_t RESERVED_1[4];
    __I  uint32_t ACTIVE;                            /**< Channel Active status for all DMA channels., array offset: 0x30, array step: 0x5C */
         uint8_t RESERVED_2[4];
    __I  uint32_t BUSY;                              /**< Channel Busy status for all DMA channels., array offset: 0x38, array step: 0x5C */
         uint8_t RESERVED_3[4];
    __IO uint32_t ERRINT;                            /**< Error Interrupt status for all DMA channels., array offset: 0x40, array step: 0x5C */
         uint8_t RESERVED_4[4];
    __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set for all DMA channels., array offset: 0x48, array step: 0x5C */
         uint8_t RESERVED_5[4];
    __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear for all DMA channels., array offset: 0x50, array step: 0x5C */
         uint8_t RESERVED_6[4];
    __IO uint32_t INTA;                              /**< Interrupt A status for all DMA channels., array offset: 0x58, array step: 0x5C */
         uint8_t RESERVED_7[4];
    __IO uint32_t INTB;                              /**< Interrupt B status for all DMA channels., array offset: 0x60, array step: 0x5C */
         uint8_t RESERVED_8[4];
    __O  uint32_t SETVALID;                          /**< Set ValidPending control bits for all DMA channels., array offset: 0x68, array step: 0x5C */
         uint8_t RESERVED_9[4];
    __O  uint32_t SETTRIG;                           /**< Set Trigger control bits for all DMA channels., array offset: 0x70, array step: 0x5C */
         uint8_t RESERVED_10[4];
    __O  uint32_t ABORT;                             /**< Channel Abort control for all DMA channels., array offset: 0x78, array step: 0x5C */
  } COMMON[1];
       uint8_t RESERVED_1[900];
  struct {                                         /* offset: 0x400, array step: 0x10 */
    __IO uint32_t CFG;                               /**< Configuration register for DMA channel ., array offset: 0x400, array step: 0x10 */
    __I  uint32_t CTLSTAT;                           /**< Control and status register for DMA channel ., array offset: 0x404, array step: 0x10 */
    __IO uint32_t XFERCFG;                           /**< Transfer configuration register for DMA channel ., array offset: 0x408, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } CHANNEL[20];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name CTRL - DMA control. */
/*! @{ */
#define DMA_CTRL_ENABLE_MASK                     (0x1U)
#define DMA_CTRL_ENABLE_SHIFT                    (0U)
/*! ENABLE - DMA controller master enable.
 *  0b0..Disabled. The DMA controller is disabled. This clears any triggers that were asserted at the point when
 *       disabled, but does not prevent re-triggering when the DMA controller is re-enabled.
 *  0b1..Enabled. The DMA controller is enabled.
 */
#define DMA_CTRL_ENABLE(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_CTRL_ENABLE_SHIFT)) & DMA_CTRL_ENABLE_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status. */
/*! @{ */
#define DMA_INTSTAT_ACTIVEINT_MASK               (0x2U)
#define DMA_INTSTAT_ACTIVEINT_SHIFT              (1U)
/*! ACTIVEINT - Summarizes whether any enabled interrupts (other than error interrupts) are pending.
 *  0b0..Not pending. No enabled interrupts are pending.
 *  0b1..Pending. At least one enabled interrupt is pending.
 */
#define DMA_INTSTAT_ACTIVEINT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEINT_SHIFT)) & DMA_INTSTAT_ACTIVEINT_MASK)
#define DMA_INTSTAT_ACTIVEERRINT_MASK            (0x4U)
#define DMA_INTSTAT_ACTIVEERRINT_SHIFT           (2U)
/*! ACTIVEERRINT - Summarizes whether any error interrupts are pending.
 *  0b0..Not pending. No error interrupts are pending.
 *  0b1..Pending. At least one error interrupt is pending.
 */
#define DMA_INTSTAT_ACTIVEERRINT(x)              (((uint32_t)(((uint32_t)(x)) << DMA_INTSTAT_ACTIVEERRINT_SHIFT)) & DMA_INTSTAT_ACTIVEERRINT_MASK)
/*! @} */

/*! @name SRAMBASE - SRAM address of the channel configuration table. */
/*! @{ */
#define DMA_SRAMBASE_OFFSET_MASK                 (0xFFFFFE00U)
#define DMA_SRAMBASE_OFFSET_SHIFT                (9U)
/*! OFFSET - Address bits 31:9 of the beginning of the DMA descriptor table. For 18 channels, the
 *    table must begin on a 512 byte boundary.
 */
#define DMA_SRAMBASE_OFFSET(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_SRAMBASE_OFFSET_SHIFT)) & DMA_SRAMBASE_OFFSET_MASK)
/*! @} */

/*! @name COMMON_ENABLESET - Channel Enable read and Set for all DMA channels. */
/*! @{ */
#define DMA_COMMON_ENABLESET_ENA_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLESET_ENA_SHIFT           (0U)
/*! ENA - Enable for DMA channels. Bit n enables or disables DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = disabled. 1 = enabled.
 */
#define DMA_COMMON_ENABLESET_ENA(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLESET_ENA_SHIFT)) & DMA_COMMON_ENABLESET_ENA_MASK)
/*! @} */

/* The count of DMA_COMMON_ENABLESET */
#define DMA_COMMON_ENABLESET_COUNT               (1U)

/*! @name COMMON_ENABLECLR - Channel Enable Clear for all DMA channels. */
/*! @{ */
#define DMA_COMMON_ENABLECLR_CLR_MASK            (0xFFFFFFFFU)
#define DMA_COMMON_ENABLECLR_CLR_SHIFT           (0U)
/*! CLR - Writing ones to this register clears the corresponding bits in ENABLESET0. Bit n clears
 *    the channel enable bit n. The number of bits = number of DMA channels in this device. Other bits
 *    are reserved.
 */
#define DMA_COMMON_ENABLECLR_CLR(x)              (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ENABLECLR_CLR_SHIFT)) & DMA_COMMON_ENABLECLR_CLR_MASK)
/*! @} */

/* The count of DMA_COMMON_ENABLECLR */
#define DMA_COMMON_ENABLECLR_COUNT               (1U)

/*! @name COMMON_ACTIVE - Channel Active status for all DMA channels. */
/*! @{ */
#define DMA_COMMON_ACTIVE_ACT_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ACTIVE_ACT_SHIFT              (0U)
/*! ACT - Active flag for DMA channel n. Bit n corresponds to DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = not active. 1 = active.
 */
#define DMA_COMMON_ACTIVE_ACT(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ACTIVE_ACT_SHIFT)) & DMA_COMMON_ACTIVE_ACT_MASK)
/*! @} */

/* The count of DMA_COMMON_ACTIVE */
#define DMA_COMMON_ACTIVE_COUNT                  (1U)

/*! @name COMMON_BUSY - Channel Busy status for all DMA channels. */
/*! @{ */
#define DMA_COMMON_BUSY_BSY_MASK                 (0xFFFFFFFFU)
#define DMA_COMMON_BUSY_BSY_SHIFT                (0U)
/*! BSY - Busy flag for DMA channel n. Bit n corresponds to DMA channel n. The number of bits =
 *    number of DMA channels in this device. Other bits are reserved. 0 = not busy. 1 = busy.
 */
#define DMA_COMMON_BUSY_BSY(x)                   (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_BUSY_BSY_SHIFT)) & DMA_COMMON_BUSY_BSY_MASK)
/*! @} */

/* The count of DMA_COMMON_BUSY */
#define DMA_COMMON_BUSY_COUNT                    (1U)

/*! @name COMMON_ERRINT - Error Interrupt status for all DMA channels. */
/*! @{ */
#define DMA_COMMON_ERRINT_ERR_MASK               (0xFFFFFFFFU)
#define DMA_COMMON_ERRINT_ERR_SHIFT              (0U)
/*! ERR - Error Interrupt flag for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = error interrupt is
 *    not active. 1 = error interrupt is active.
 */
#define DMA_COMMON_ERRINT_ERR(x)                 (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ERRINT_ERR_SHIFT)) & DMA_COMMON_ERRINT_ERR_MASK)
/*! @} */

/* The count of DMA_COMMON_ERRINT */
#define DMA_COMMON_ERRINT_COUNT                  (1U)

/*! @name COMMON_INTENSET - Interrupt Enable read and Set for all DMA channels. */
/*! @{ */
#define DMA_COMMON_INTENSET_INTEN_MASK           (0xFFFFFFFFU)
#define DMA_COMMON_INTENSET_INTEN_SHIFT          (0U)
/*! INTEN - Interrupt Enable read and set for DMA channel n. Bit n corresponds to DMA channel n. The
 *    number of bits = number of DMA channels in this device. Other bits are reserved. 0 =
 *    interrupt for DMA channel is disabled. 1 = interrupt for DMA channel is enabled.
 */
#define DMA_COMMON_INTENSET_INTEN(x)             (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENSET_INTEN_SHIFT)) & DMA_COMMON_INTENSET_INTEN_MASK)
/*! @} */

/* The count of DMA_COMMON_INTENSET */
#define DMA_COMMON_INTENSET_COUNT                (1U)

/*! @name COMMON_INTENCLR - Interrupt Enable Clear for all DMA channels. */
/*! @{ */
#define DMA_COMMON_INTENCLR_CLR_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_INTENCLR_CLR_SHIFT            (0U)
/*! CLR - Writing ones to this register clears corresponding bits in the INTENSET0. Bit n
 *    corresponds to DMA channel n. The number of bits = number of DMA channels in this device. Other bits are
 *    reserved.
 */
#define DMA_COMMON_INTENCLR_CLR(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTENCLR_CLR_SHIFT)) & DMA_COMMON_INTENCLR_CLR_MASK)
/*! @} */

/* The count of DMA_COMMON_INTENCLR */
#define DMA_COMMON_INTENCLR_COUNT                (1U)

/*! @name COMMON_INTA - Interrupt A status for all DMA channels. */
/*! @{ */
#define DMA_COMMON_INTA_IA_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTA_IA_SHIFT                 (0U)
/*! IA - Interrupt A status for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = the DMA channel
 *    interrupt A is not active. 1 = the DMA channel interrupt A is active.
 */
#define DMA_COMMON_INTA_IA(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTA_IA_SHIFT)) & DMA_COMMON_INTA_IA_MASK)
/*! @} */

/* The count of DMA_COMMON_INTA */
#define DMA_COMMON_INTA_COUNT                    (1U)

/*! @name COMMON_INTB - Interrupt B status for all DMA channels. */
/*! @{ */
#define DMA_COMMON_INTB_IB_MASK                  (0xFFFFFFFFU)
#define DMA_COMMON_INTB_IB_SHIFT                 (0U)
/*! IB - Interrupt B status for DMA channel n. Bit n corresponds to DMA channel n. The number of
 *    bits = number of DMA channels in this device. Other bits are reserved. 0 = the DMA channel
 *    interrupt B is not active. 1 = the DMA channel interrupt B is active.
 */
#define DMA_COMMON_INTB_IB(x)                    (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_INTB_IB_SHIFT)) & DMA_COMMON_INTB_IB_MASK)
/*! @} */

/* The count of DMA_COMMON_INTB */
#define DMA_COMMON_INTB_COUNT                    (1U)

/*! @name COMMON_SETVALID - Set ValidPending control bits for all DMA channels. */
/*! @{ */
#define DMA_COMMON_SETVALID_SV_MASK              (0xFFFFFFFFU)
#define DMA_COMMON_SETVALID_SV_SHIFT             (0U)
/*! SV - SETVALID control for DMA channel n. Bit n corresponds to DMA channel n. The number of bits
 *    = number of DMA channels in this device. Other bits are reserved. 0 = no effect. 1 = sets the
 *    VALIDPENDING control bit for DMA channel n
 */
#define DMA_COMMON_SETVALID_SV(x)                (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETVALID_SV_SHIFT)) & DMA_COMMON_SETVALID_SV_MASK)
/*! @} */

/* The count of DMA_COMMON_SETVALID */
#define DMA_COMMON_SETVALID_COUNT                (1U)

/*! @name COMMON_SETTRIG - Set Trigger control bits for all DMA channels. */
/*! @{ */
#define DMA_COMMON_SETTRIG_TRIG_MASK             (0xFFFFFFFFU)
#define DMA_COMMON_SETTRIG_TRIG_SHIFT            (0U)
/*! TRIG - Set Trigger control bit for DMA channel 0. Bit n corresponds to DMA channel n. The number
 *    of bits = number of DMA channels in this device. Other bits are reserved. 0 = no effect. 1 =
 *    sets the TRIG bit for DMA channel n.
 */
#define DMA_COMMON_SETTRIG_TRIG(x)               (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_SETTRIG_TRIG_SHIFT)) & DMA_COMMON_SETTRIG_TRIG_MASK)
/*! @} */

/* The count of DMA_COMMON_SETTRIG */
#define DMA_COMMON_SETTRIG_COUNT                 (1U)

/*! @name COMMON_ABORT - Channel Abort control for all DMA channels. */
/*! @{ */
#define DMA_COMMON_ABORT_ABORTCTRL_MASK          (0xFFFFFFFFU)
#define DMA_COMMON_ABORT_ABORTCTRL_SHIFT         (0U)
/*! ABORTCTRL - Abort control for DMA channel 0. Bit n corresponds to DMA channel n. 0 = no effect.
 *    1 = aborts DMA operations on channel n.
 */
#define DMA_COMMON_ABORT_ABORTCTRL(x)            (((uint32_t)(((uint32_t)(x)) << DMA_COMMON_ABORT_ABORTCTRL_SHIFT)) & DMA_COMMON_ABORT_ABORTCTRL_MASK)
/*! @} */

/* The count of DMA_COMMON_ABORT */
#define DMA_COMMON_ABORT_COUNT                   (1U)

/*! @name CHANNEL_CFG - Configuration register for DMA channel . */
/*! @{ */
#define DMA_CHANNEL_CFG_PERIPHREQEN_MASK         (0x1U)
#define DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT        (0U)
/*! PERIPHREQEN - Peripheral request Enable. If a DMA channel is used to perform a memory-to-memory
 *    move, any peripheral DMA request associated with that channel can be disabled to prevent any
 *    interaction between the peripheral and the DMA controller.
 *  0b0..Disabled. Peripheral DMA requests are disabled.
 *  0b1..Enabled. Peripheral DMA requests are enabled.
 */
#define DMA_CHANNEL_CFG_PERIPHREQEN(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_PERIPHREQEN_SHIFT)) & DMA_CHANNEL_CFG_PERIPHREQEN_MASK)
#define DMA_CHANNEL_CFG_HWTRIGEN_MASK            (0x2U)
#define DMA_CHANNEL_CFG_HWTRIGEN_SHIFT           (1U)
/*! HWTRIGEN - Hardware Triggering Enable for this channel.
 *  0b0..Disabled. Hardware triggering is not used.
 *  0b1..Enabled. Use hardware triggering.
 */
#define DMA_CHANNEL_CFG_HWTRIGEN(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_HWTRIGEN_SHIFT)) & DMA_CHANNEL_CFG_HWTRIGEN_MASK)
#define DMA_CHANNEL_CFG_TRIGPOL_MASK             (0x10U)
#define DMA_CHANNEL_CFG_TRIGPOL_SHIFT            (4U)
/*! TRIGPOL - Trigger Polarity. Selects the polarity of a hardware trigger for this channel.
 *  0b0..Active low - falling edge. Hardware trigger is active low or falling edge triggered, based on TRIGTYPE.
 *  0b1..Active high - rising edge. Hardware trigger is active high or rising edge triggered, based on TRIGTYPE.
 */
#define DMA_CHANNEL_CFG_TRIGPOL(x)               (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGPOL_SHIFT)) & DMA_CHANNEL_CFG_TRIGPOL_MASK)
#define DMA_CHANNEL_CFG_TRIGTYPE_MASK            (0x20U)
#define DMA_CHANNEL_CFG_TRIGTYPE_SHIFT           (5U)
/*! TRIGTYPE - Trigger Type. Selects hardware trigger as edge triggered or level triggered.
 *  0b0..Edge. Hardware trigger is edge triggered. Transfers will be initiated and completed, as specified for a single trigger.
 *  0b1..Level. Hardware trigger is level triggered. Note that when level triggering without burst (BURSTPOWER =
 *       0) is selected, only hardware triggers should be used on that channel. Transfers continue as long as the
 *       trigger level is asserted. Once the trigger is de-asserted, the transfer will be paused until the trigger
 *       is, again, asserted. However, the transfer will not be paused until any remaining transfers within the
 *       current BURSTPOWER length are completed.
 */
#define DMA_CHANNEL_CFG_TRIGTYPE(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGTYPE_SHIFT)) & DMA_CHANNEL_CFG_TRIGTYPE_MASK)
#define DMA_CHANNEL_CFG_TRIGBURST_MASK           (0x40U)
#define DMA_CHANNEL_CFG_TRIGBURST_SHIFT          (6U)
/*! TRIGBURST - Trigger Burst. Selects whether hardware triggers cause a single or burst transfer.
 *  0b0..Single transfer. Hardware trigger causes a single transfer.
 *  0b1..Burst transfer. When the trigger for this channel is set to edge triggered, a hardware trigger causes a
 *       burst transfer, as defined by BURSTPOWER. When the trigger for this channel is set to level triggered, a
 *       hardware trigger causes transfers to continue as long as the trigger is asserted, unless the transfer is
 *       complete.
 */
#define DMA_CHANNEL_CFG_TRIGBURST(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_TRIGBURST_SHIFT)) & DMA_CHANNEL_CFG_TRIGBURST_MASK)
#define DMA_CHANNEL_CFG_BURSTPOWER_MASK          (0xF00U)
#define DMA_CHANNEL_CFG_BURSTPOWER_SHIFT         (8U)
/*! BURSTPOWER - Burst Power is used in two ways. It always selects the address wrap size when
 *    SRCBURSTWRAP and/or DSTBURSTWRAP modes are selected (see descriptions elsewhere in this register).
 *    When the TRIGBURST field elsewhere in this register = 1, Burst Power selects how many
 *    transfers are performed for each DMA trigger. This can be used, for example, with peripherals that
 *    contain a FIFO that can initiate a DMA operation when the FIFO reaches a certain level. 0000:
 *    Burst size = 1 (20). 0001: Burst size = 2 (21). 0010: Burst size = 4 (22). 1010: Burst size =
 *    1024 (210). This corresponds to the maximum supported transfer count. others: not supported. The
 *    total transfer length as defined in the XFERCOUNT bits in the XFERCFG register must be an even
 *    multiple of the burst size.
 */
#define DMA_CHANNEL_CFG_BURSTPOWER(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_BURSTPOWER_SHIFT)) & DMA_CHANNEL_CFG_BURSTPOWER_MASK)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK        (0x4000U)
#define DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT       (14U)
/*! SRCBURSTWRAP - Source Burst Wrap. When enabled, the source data address for the DMA is
 *    'wrapped', meaning that the source address range for each burst will be the same. As an example, this
 *    could be used to read several sequential registers from a peripheral for each DMA burst,
 *    reading the same registers again for each burst.
 *  0b0..Disabled. Source burst wrapping is not enabled for this DMA channel.
 *  0b1..Enabled. Source burst wrapping is enabled for this DMA channel.
 */
#define DMA_CHANNEL_CFG_SRCBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_SRCBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_SRCBURSTWRAP_MASK)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK        (0x8000U)
#define DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT       (15U)
/*! DSTBURSTWRAP - Destination Burst Wrap. When enabled, the destination data address for the DMA is
 *    'wrapped', meaning that the destination address range for each burst will be the same. As an
 *    example, this could be used to write several sequential registers to a peripheral for each DMA
 *    burst, writing the same registers again for each burst.
 *  0b0..Disabled. Destination burst wrapping is not enabled for this DMA channel.
 *  0b1..Enabled. Destination burst wrapping is enabled for this DMA channel.
 */
#define DMA_CHANNEL_CFG_DSTBURSTWRAP(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_DSTBURSTWRAP_SHIFT)) & DMA_CHANNEL_CFG_DSTBURSTWRAP_MASK)
#define DMA_CHANNEL_CFG_CHPRIORITY_MASK          (0x70000U)
#define DMA_CHANNEL_CFG_CHPRIORITY_SHIFT         (16U)
/*! CHPRIORITY - Priority of this channel when multiple DMA requests are pending. Eight priority
 *    levels are supported: 0x0 = highest priority. 0x7 = lowest priority.
 */
#define DMA_CHANNEL_CFG_CHPRIORITY(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_CHPRIORITY_SHIFT)) & DMA_CHANNEL_CFG_CHPRIORITY_MASK)
/*! @} */

/* The count of DMA_CHANNEL_CFG */
#define DMA_CHANNEL_CFG_COUNT                    (20U)

/*! @name CHANNEL_CTLSTAT - Control and status register for DMA channel . */
/*! @{ */
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK    (0x1U)
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT   (0U)
/*! VALIDPENDING - Valid pending flag for this channel. This bit is set when a 1 is written to the
 *    corresponding bit in the related SETVALID register when CFGVALID = 1 for the same channel.
 *  0b0..No effect. No effect on DMA operation.
 *  0b1..Valid pending.
 */
#define DMA_CHANNEL_CTLSTAT_VALIDPENDING(x)      (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_VALIDPENDING_SHIFT)) & DMA_CHANNEL_CTLSTAT_VALIDPENDING_MASK)
#define DMA_CHANNEL_CTLSTAT_TRIG_MASK            (0x4U)
#define DMA_CHANNEL_CTLSTAT_TRIG_SHIFT           (2U)
/*! TRIG - Trigger flag. Indicates that the trigger for this channel is currently set. This bit is
 *    cleared at the end of an entire transfer or upon reload when CLRTRIG = 1.
 *  0b0..Not triggered. The trigger for this DMA channel is not set. DMA operations will not be carried out.
 *  0b1..Triggered. The trigger for this DMA channel is set. DMA operations will be carried out.
 */
#define DMA_CHANNEL_CTLSTAT_TRIG(x)              (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CTLSTAT_TRIG_SHIFT)) & DMA_CHANNEL_CTLSTAT_TRIG_MASK)
/*! @} */

/* The count of DMA_CHANNEL_CTLSTAT */
#define DMA_CHANNEL_CTLSTAT_COUNT                (20U)

/*! @name CHANNEL_XFERCFG - Transfer configuration register for DMA channel . */
/*! @{ */
#define DMA_CHANNEL_XFERCFG_CFGVALID_MASK        (0x1U)
#define DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT       (0U)
/*! CFGVALID - Configuration Valid flag. This bit indicates whether the current channel descriptor
 *    is valid and can potentially be acted upon, if all other activation criteria are fulfilled.
 *  0b0..Not valid. The channel descriptor is not considered valid until validated by an associated SETVALID0 setting.
 *  0b1..Valid. The current channel descriptor is considered valid.
 */
#define DMA_CHANNEL_XFERCFG_CFGVALID(x)          (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CFGVALID_SHIFT)) & DMA_CHANNEL_XFERCFG_CFGVALID_MASK)
#define DMA_CHANNEL_XFERCFG_RELOAD_MASK          (0x2U)
#define DMA_CHANNEL_XFERCFG_RELOAD_SHIFT         (1U)
/*! RELOAD - Indicates whether the channel's control structure will be reloaded when the current
 *    descriptor is exhausted. Reloading allows ping-pong and linked transfers.
 *  0b0..Disabled. Do not reload the channels' control structure when the current descriptor is exhausted.
 *  0b1..Enabled. Reload the channels' control structure when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_RELOAD(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_RELOAD_SHIFT)) & DMA_CHANNEL_XFERCFG_RELOAD_MASK)
#define DMA_CHANNEL_XFERCFG_SWTRIG_MASK          (0x4U)
#define DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT         (2U)
/*! SWTRIG - Software Trigger.
 *  0b0..Not set. When written by software, the trigger for this channel is not set. A new trigger, as defined by
 *       the HWTRIGEN, TRIGPOL, and TRIGTYPE will be needed to start the channel.
 *  0b1..Set. When written by software, the trigger for this channel is set immediately. This feature should not
 *       be used with level triggering when TRIGBURST = 0.
 */
#define DMA_CHANNEL_XFERCFG_SWTRIG(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SWTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_SWTRIG_MASK)
#define DMA_CHANNEL_XFERCFG_CLRTRIG_MASK         (0x8U)
#define DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT        (3U)
/*! CLRTRIG - Clear Trigger.
 *  0b0..Not cleared. The trigger is not cleared when this descriptor is exhausted. If there is a reload, the next descriptor will be started.
 *  0b1..Cleared. The trigger is cleared when this descriptor is exhausted
 */
#define DMA_CHANNEL_XFERCFG_CLRTRIG(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_CLRTRIG_SHIFT)) & DMA_CHANNEL_XFERCFG_CLRTRIG_MASK)
#define DMA_CHANNEL_XFERCFG_SETINTA_MASK         (0x10U)
#define DMA_CHANNEL_XFERCFG_SETINTA_SHIFT        (4U)
/*! SETINTA - Set Interrupt flag A for this channel. There is no hardware distinction between
 *    interrupt A and B. They can be used by software to assist with more complex descriptor usage. By
 *    convention, interrupt A may be used when only one interrupt flag is needed.
 *  0b0..No effect.
 *  0b1..Set. The INTA flag for this channel will be set when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_SETINTA(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTA_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTA_MASK)
#define DMA_CHANNEL_XFERCFG_SETINTB_MASK         (0x20U)
#define DMA_CHANNEL_XFERCFG_SETINTB_SHIFT        (5U)
/*! SETINTB - Set Interrupt flag B for this channel. There is no hardware distinction between
 *    interrupt A and B. They can be used by software to assist with more complex descriptor usage. By
 *    convention, interrupt A may be used when only one interrupt flag is needed.
 *  0b0..No effect.
 *  0b1..Set. The INTB flag for this channel will be set when the current descriptor is exhausted.
 */
#define DMA_CHANNEL_XFERCFG_SETINTB(x)           (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SETINTB_SHIFT)) & DMA_CHANNEL_XFERCFG_SETINTB_MASK)
#define DMA_CHANNEL_XFERCFG_WIDTH_MASK           (0x300U)
#define DMA_CHANNEL_XFERCFG_WIDTH_SHIFT          (8U)
/*! WIDTH - Transfer width used for this DMA channel.
 *  0b00..8-bit. 8-bit transfers are performed (8-bit source reads and destination writes).
 *  0b01..16-bit. 6-bit transfers are performed (16-bit source reads and destination writes).
 *  0b10..32-bit. 32-bit transfers are performed (32-bit source reads and destination writes).
 *  0b11..Reserved. Reserved setting, do not use.
 */
#define DMA_CHANNEL_XFERCFG_WIDTH(x)             (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_WIDTH_SHIFT)) & DMA_CHANNEL_XFERCFG_WIDTH_MASK)
#define DMA_CHANNEL_XFERCFG_SRCINC_MASK          (0x3000U)
#define DMA_CHANNEL_XFERCFG_SRCINC_SHIFT         (12U)
/*! SRCINC - Determines whether the source address is incremented for each DMA transfer.
 *  0b00..No increment. The source address is not incremented for each transfer. This is the usual case when the source is a peripheral device.
 *  0b01..1 x width. The source address is incremented by the amount specified by Width for each transfer. This is
 *        the usual case when the source is memory.
 *  0b10..2 x width. The source address is incremented by 2 times the amount specified by Width for each transfer.
 *  0b11..4 x width. The source address is incremented by 4 times the amount specified by Width for each transfer.
 */
#define DMA_CHANNEL_XFERCFG_SRCINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_SRCINC_SHIFT)) & DMA_CHANNEL_XFERCFG_SRCINC_MASK)
#define DMA_CHANNEL_XFERCFG_DSTINC_MASK          (0xC000U)
#define DMA_CHANNEL_XFERCFG_DSTINC_SHIFT         (14U)
/*! DSTINC - Determines whether the destination address is incremented for each DMA transfer.
 *  0b00..No increment. The destination address is not incremented for each transfer. This is the usual case when
 *        the destination is a peripheral device.
 *  0b01..1 x width. The destination address is incremented by the amount specified by Width for each transfer.
 *        This is the usual case when the destination is memory.
 *  0b10..2 x width. The destination address is incremented by 2 times the amount specified by Width for each transfer.
 *  0b11..4 x width. The destination address is incremented by 4 times the amount specified by Width for each transfer.
 */
#define DMA_CHANNEL_XFERCFG_DSTINC(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_DSTINC_SHIFT)) & DMA_CHANNEL_XFERCFG_DSTINC_MASK)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK       (0x3FF0000U)
#define DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT      (16U)
/*! XFERCOUNT - Total number of transfers to be performed, minus 1 encoded. The number of bytes
 *    transferred is: (XFERCOUNT + 1) x data width (as defined by the WIDTH field). The DMA controller
 *    uses this bit field during transfer to count down. Hence, it cannot be used by software to read
 *    back the size of the transfer, for instance, in an interrupt handler. 0x0 = a total of 1
 *    transfer will be performed. 0x1 = a total of 2 transfers will be performed. 0x3FF = a total of
 *    1,024 transfers will be performed.
 */
#define DMA_CHANNEL_XFERCFG_XFERCOUNT(x)         (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_XFERCFG_XFERCOUNT_SHIFT)) & DMA_CHANNEL_XFERCFG_XFERCOUNT_MASK)
/*! @} */

/* The count of DMA_CHANNEL_XFERCFG */
#define DMA_CHANNEL_XFERCFG_COUNT                (20U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA0 base address */
#define DMA0_BASE                                (0x40082000u)
/** Peripheral DMA0 base pointer */
#define DMA0                                     ((DMA_Type *)DMA0_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA0_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_IRQS                                 { DMA0_IRQn }

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FLEXCOMM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXCOMM_Peripheral_Access_Layer FLEXCOMM Peripheral Access Layer
 * @{
 */

/** FLEXCOMM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4088];
  __IO uint32_t PSELID;                            /**< Peripheral Select and Flexcomm ID register., offset: 0xFF8 */
  __I  uint32_t PID;                               /**< Peripheral identification register., offset: 0xFFC */
} FLEXCOMM_Type;

/* ----------------------------------------------------------------------------
   -- FLEXCOMM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXCOMM_Register_Masks FLEXCOMM Register Masks
 * @{
 */

/*! @name PSELID - Peripheral Select and Flexcomm ID register. */
/*! @{ */
#define FLEXCOMM_PSELID_PERSEL_MASK              (0x7U)
#define FLEXCOMM_PSELID_PERSEL_SHIFT             (0U)
/*! PERSEL - Peripheral Select. This field is writable by software.
 *  0b000..No peripheral selected.
 *  0b001..USART function selected.
 *  0b010..SPI function selected.
 *  0b011..I2C function selected.
 *  0b100..I2S transmit function selected.
 *  0b101..I2S receive function selected.
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define FLEXCOMM_PSELID_PERSEL(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_PERSEL_SHIFT)) & FLEXCOMM_PSELID_PERSEL_MASK)
#define FLEXCOMM_PSELID_LOCK_MASK                (0x8U)
#define FLEXCOMM_PSELID_LOCK_SHIFT               (3U)
/*! LOCK - Lock the peripheral select. This field is writable by software.
 *  0b0..Peripheral select can be changed by software.
 *  0b1..Peripheral select is locked and cannot be changed until this Flexcomm or the entire device is reset.
 */
#define FLEXCOMM_PSELID_LOCK(x)                  (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_LOCK_SHIFT)) & FLEXCOMM_PSELID_LOCK_MASK)
#define FLEXCOMM_PSELID_USARTPRESENT_MASK        (0x10U)
#define FLEXCOMM_PSELID_USARTPRESENT_SHIFT       (4U)
/*! USARTPRESENT - USART present indicator. This field is Read-only.
 *  0b0..This Flexcomm does not include the USART function.
 *  0b1..This Flexcomm includes the USART function.
 */
#define FLEXCOMM_PSELID_USARTPRESENT(x)          (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_USARTPRESENT_SHIFT)) & FLEXCOMM_PSELID_USARTPRESENT_MASK)
#define FLEXCOMM_PSELID_SPIPRESENT_MASK          (0x20U)
#define FLEXCOMM_PSELID_SPIPRESENT_SHIFT         (5U)
/*! SPIPRESENT - SPI present indicator. This field is Read-only.
 *  0b0..This Flexcomm does not include the SPI function.
 *  0b1..This Flexcomm includes the SPI function.
 */
#define FLEXCOMM_PSELID_SPIPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_SPIPRESENT_SHIFT)) & FLEXCOMM_PSELID_SPIPRESENT_MASK)
#define FLEXCOMM_PSELID_I2CPRESENT_MASK          (0x40U)
#define FLEXCOMM_PSELID_I2CPRESENT_SHIFT         (6U)
/*! I2CPRESENT - I2C present indicator. This field is Read-only.
 *  0b0..This Flexcomm does not include the I2C function.
 *  0b1..This Flexcomm includes the I2C function.
 */
#define FLEXCOMM_PSELID_I2CPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_I2CPRESENT_SHIFT)) & FLEXCOMM_PSELID_I2CPRESENT_MASK)
#define FLEXCOMM_PSELID_I2SPRESENT_MASK          (0x80U)
#define FLEXCOMM_PSELID_I2SPRESENT_SHIFT         (7U)
/*! I2SPRESENT - I 2S present indicator. This field is Read-only.
 *  0b0..This Flexcomm does not include the I2S function.
 *  0b1..This Flexcomm includes the I2S function.
 */
#define FLEXCOMM_PSELID_I2SPRESENT(x)            (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_I2SPRESENT_SHIFT)) & FLEXCOMM_PSELID_I2SPRESENT_MASK)
#define FLEXCOMM_PSELID_ID_MASK                  (0xFFFFF000U)
#define FLEXCOMM_PSELID_ID_SHIFT                 (12U)
/*! ID - Flexcomm ID.
 */
#define FLEXCOMM_PSELID_ID(x)                    (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PSELID_ID_SHIFT)) & FLEXCOMM_PSELID_ID_MASK)
/*! @} */

/*! @name PID - Peripheral identification register. */
/*! @{ */
#define FLEXCOMM_PID_Minor_Rev_MASK              (0xF00U)
#define FLEXCOMM_PID_Minor_Rev_SHIFT             (8U)
/*! Minor_Rev - Minor revision of module implementation.
 */
#define FLEXCOMM_PID_Minor_Rev(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_Minor_Rev_SHIFT)) & FLEXCOMM_PID_Minor_Rev_MASK)
#define FLEXCOMM_PID_Major_Rev_MASK              (0xF000U)
#define FLEXCOMM_PID_Major_Rev_SHIFT             (12U)
/*! Major_Rev - Major revision of module implementation.
 */
#define FLEXCOMM_PID_Major_Rev(x)                (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_Major_Rev_SHIFT)) & FLEXCOMM_PID_Major_Rev_MASK)
#define FLEXCOMM_PID_ID_MASK                     (0xFFFF0000U)
#define FLEXCOMM_PID_ID_SHIFT                    (16U)
/*! ID - Module identifier for the selected function.
 */
#define FLEXCOMM_PID_ID(x)                       (((uint32_t)(((uint32_t)(x)) << FLEXCOMM_PID_ID_SHIFT)) & FLEXCOMM_PID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLEXCOMM_Register_Masks */


/* FLEXCOMM - Peripheral instance base addresses */
/** Peripheral FLEXCOMM0 base address */
#define FLEXCOMM0_BASE                           (0x40086000u)
/** Peripheral FLEXCOMM0 base pointer */
#define FLEXCOMM0                                ((FLEXCOMM_Type *)FLEXCOMM0_BASE)
/** Peripheral FLEXCOMM1 base address */
#define FLEXCOMM1_BASE                           (0x40087000u)
/** Peripheral FLEXCOMM1 base pointer */
#define FLEXCOMM1                                ((FLEXCOMM_Type *)FLEXCOMM1_BASE)
/** Peripheral FLEXCOMM2 base address */
#define FLEXCOMM2_BASE                           (0x40088000u)
/** Peripheral FLEXCOMM2 base pointer */
#define FLEXCOMM2                                ((FLEXCOMM_Type *)FLEXCOMM2_BASE)
/** Peripheral FLEXCOMM3 base address */
#define FLEXCOMM3_BASE                           (0x40089000u)
/** Peripheral FLEXCOMM3 base pointer */
#define FLEXCOMM3                                ((FLEXCOMM_Type *)FLEXCOMM3_BASE)
/** Peripheral FLEXCOMM4 base address */
#define FLEXCOMM4_BASE                           (0x4008A000u)
/** Peripheral FLEXCOMM4 base pointer */
#define FLEXCOMM4                                ((FLEXCOMM_Type *)FLEXCOMM4_BASE)
/** Peripheral FLEXCOMM5 base address */
#define FLEXCOMM5_BASE                           (0x40096000u)
/** Peripheral FLEXCOMM5 base pointer */
#define FLEXCOMM5                                ((FLEXCOMM_Type *)FLEXCOMM5_BASE)
/** Peripheral FLEXCOMM6 base address */
#define FLEXCOMM6_BASE                           (0x40097000u)
/** Peripheral FLEXCOMM6 base pointer */
#define FLEXCOMM6                                ((FLEXCOMM_Type *)FLEXCOMM6_BASE)
/** Peripheral FLEXCOMM7 base address */
#define FLEXCOMM7_BASE                           (0x40098000u)
/** Peripheral FLEXCOMM7 base pointer */
#define FLEXCOMM7                                ((FLEXCOMM_Type *)FLEXCOMM7_BASE)
/** Array initializer of FLEXCOMM peripheral base addresses */
#define FLEXCOMM_BASE_ADDRS                      { FLEXCOMM0_BASE, FLEXCOMM1_BASE, FLEXCOMM2_BASE, FLEXCOMM3_BASE, FLEXCOMM4_BASE, FLEXCOMM5_BASE, FLEXCOMM6_BASE, FLEXCOMM7_BASE }
/** Array initializer of FLEXCOMM peripheral base pointers */
#define FLEXCOMM_BASE_PTRS                       { FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7 }
/** Interrupt vectors for the FLEXCOMM peripheral type */
#define FLEXCOMM_IRQS                            { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group FLEXCOMM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Peripheral_Access_Layer FMC Peripheral Access Layer
 * @{
 */

/** FMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t FCTR;                              /**< Control register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  __IO uint32_t FBWST;                             /**< Wait state register, offset: 0x10 */
       uint8_t RESERVED_1[12];
  __IO uint32_t FMSSTART;                          /**< Signature start address register, offset: 0x20 */
  __IO uint32_t FMSSTOP;                           /**< Signature stop-address register, offset: 0x24 */
       uint8_t RESERVED_2[4];
  __I  uint32_t FMSW[4];                           /**< Words of 128-bit signature word, array offset: 0x2C, array step: 0x4 */
       uint8_t RESERVED_3[4004];
  __I  uint32_t FMSTAT;                            /**< Signature generation status register, offset: 0xFE0 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FMSTATCLR;                         /**< Signature generation status clear register, offset: 0xFE8 */
} FMC_Type;

/* ----------------------------------------------------------------------------
   -- FMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FMC_Register_Masks FMC Register Masks
 * @{
 */

/*! @name FCTR - Control register */
/*! @{ */
#define FMC_FCTR_FS_RD0_MASK                     (0x8U)
#define FMC_FCTR_FS_RD0_SHIFT                    (3U)
/*! FS_RD0 - Value must be 0 for signature generation.
 */
#define FMC_FCTR_FS_RD0(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_FCTR_FS_RD0_SHIFT)) & FMC_FCTR_FS_RD0_MASK)
#define FMC_FCTR_FS_RD1_MASK                     (0x10U)
#define FMC_FCTR_FS_RD1_SHIFT                    (4U)
/*! FS_RD1 - Value must be 1 for signature generation.
 */
#define FMC_FCTR_FS_RD1(x)                       (((uint32_t)(((uint32_t)(x)) << FMC_FCTR_FS_RD1_SHIFT)) & FMC_FCTR_FS_RD1_MASK)
/*! @} */

/*! @name FBWST - Wait state register */
/*! @{ */
#define FMC_FBWST_WAITSTATES_MASK                (0xFFU)
#define FMC_FBWST_WAITSTATES_SHIFT               (0U)
/*! WAITSTATES - Wait states for signature generation.
 */
#define FMC_FBWST_WAITSTATES(x)                  (((uint32_t)(((uint32_t)(x)) << FMC_FBWST_WAITSTATES_SHIFT)) & FMC_FBWST_WAITSTATES_MASK)
/*! @} */

/*! @name FMSSTART - Signature start address register */
/*! @{ */
#define FMC_FMSSTART_START_MASK                  (0x1FFFFU)
#define FMC_FMSSTART_START_SHIFT                 (0U)
/*! START - Signature generation start address (corresponds to AHB byte address bits[20:4]).
 */
#define FMC_FMSSTART_START(x)                    (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTART_START_SHIFT)) & FMC_FMSSTART_START_MASK)
/*! @} */

/*! @name FMSSTOP - Signature stop-address register */
/*! @{ */
#define FMC_FMSSTOP_STOP_MASK                    (0x1FFFFU)
#define FMC_FMSSTOP_STOP_SHIFT                   (0U)
/*! STOP - Stop address for signature generation (the word specified by STOP is included in the address range).
 */
#define FMC_FMSSTOP_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTOP_STOP_SHIFT)) & FMC_FMSSTOP_STOP_MASK)
#define FMC_FMSSTOP_SIG_START_MASK               (0x20000U)
#define FMC_FMSSTOP_SIG_START_SHIFT              (17U)
/*! SIG_START - When this bit is written to 1, signature generation starts.
 */
#define FMC_FMSSTOP_SIG_START(x)                 (((uint32_t)(((uint32_t)(x)) << FMC_FMSSTOP_SIG_START_SHIFT)) & FMC_FMSSTOP_SIG_START_MASK)
/*! @} */

/*! @name FMSW - Words of 128-bit signature word */
/*! @{ */
#define FMC_FMSW_SW_MASK                         (0xFFFFFFFFU)
#define FMC_FMSW_SW_SHIFT                        (0U)
/*! SW - Words of 128-bit signature (bits).
 */
#define FMC_FMSW_SW(x)                           (((uint32_t)(((uint32_t)(x)) << FMC_FMSW_SW_SHIFT)) & FMC_FMSW_SW_MASK)
/*! @} */

/* The count of FMC_FMSW */
#define FMC_FMSW_COUNT                           (4U)

/*! @name FMSTAT - Signature generation status register */
/*! @{ */
#define FMC_FMSTAT_SIG_DONE_MASK                 (0x4U)
#define FMC_FMSTAT_SIG_DONE_SHIFT                (2U)
/*! SIG_DONE - When 1, a previously started signature generation has completed.
 */
#define FMC_FMSTAT_SIG_DONE(x)                   (((uint32_t)(((uint32_t)(x)) << FMC_FMSTAT_SIG_DONE_SHIFT)) & FMC_FMSTAT_SIG_DONE_MASK)
/*! @} */

/*! @name FMSTATCLR - Signature generation status clear register */
/*! @{ */
#define FMC_FMSTATCLR_SIG_DONE_CLR_MASK          (0x4U)
#define FMC_FMSTATCLR_SIG_DONE_CLR_SHIFT         (2U)
/*! SIG_DONE_CLR - Writing a 1 to this bits clears the signature generation completion flag (SIG_DONE) in the FMSTAT register.
 */
#define FMC_FMSTATCLR_SIG_DONE_CLR(x)            (((uint32_t)(((uint32_t)(x)) << FMC_FMSTATCLR_SIG_DONE_CLR_SHIFT)) & FMC_FMSTATCLR_SIG_DONE_CLR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FMC_Register_Masks */


/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base address */
#define FMC_BASE                                 (0x40034000u)
/** Peripheral FMC base pointer */
#define FMC                                      ((FMC_Type *)FMC_BASE)
/** Array initializer of FMC peripheral base addresses */
#define FMC_BASE_ADDRS                           { FMC_BASE }
/** Array initializer of FMC peripheral base pointers */
#define FMC_BASE_PTRS                            { FMC }

/*!
 * @}
 */ /* end of group FMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GINT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Peripheral_Access_Layer GINT Peripheral Access Layer
 * @{
 */

/** GINT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< GPIO grouped interrupt control register, offset: 0x0 */
       uint8_t RESERVED_0[28];
  __IO uint32_t PORT_POL[2];                       /**< GPIO grouped interrupt port 0 polarity register, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PORT_ENA[2];                       /**< GPIO grouped interrupt port 0 enable register, array offset: 0x40, array step: 0x4 */
} GINT_Type;

/* ----------------------------------------------------------------------------
   -- GINT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GINT_Register_Masks GINT Register Masks
 * @{
 */

/*! @name CTRL - GPIO grouped interrupt control register */
/*! @{ */
#define GINT_CTRL_INT_MASK                       (0x1U)
#define GINT_CTRL_INT_SHIFT                      (0U)
/*! INT - Group interrupt status. This bit is cleared by writing a one to it. Writing zero has no effect.
 *  0b0..No request. No interrupt request is pending.
 *  0b1..Request active. Interrupt request is active.
 */
#define GINT_CTRL_INT(x)                         (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_INT_SHIFT)) & GINT_CTRL_INT_MASK)
#define GINT_CTRL_COMB_MASK                      (0x2U)
#define GINT_CTRL_COMB_SHIFT                     (1U)
/*! COMB - Combine enabled inputs for group interrupt
 *  0b0..Or. OR functionality: A grouped interrupt is generated when any one of the enabled inputs is active (based on its programmed polarity).
 *  0b1..And. AND functionality: An interrupt is generated when all enabled bits are active (based on their programmed polarity).
 */
#define GINT_CTRL_COMB(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_COMB_SHIFT)) & GINT_CTRL_COMB_MASK)
#define GINT_CTRL_TRIG_MASK                      (0x4U)
#define GINT_CTRL_TRIG_SHIFT                     (2U)
/*! TRIG - Group interrupt trigger
 *  0b0..Edge-triggered.
 *  0b1..Level-triggered.
 */
#define GINT_CTRL_TRIG(x)                        (((uint32_t)(((uint32_t)(x)) << GINT_CTRL_TRIG_SHIFT)) & GINT_CTRL_TRIG_MASK)
/*! @} */

/*! @name PORT_POL - GPIO grouped interrupt port 0 polarity register */
/*! @{ */
#define GINT_PORT_POL_POL_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_POL_POL_SHIFT                  (0U)
/*! POL - Configure pin polarity of port m pins for group interrupt. Bit n corresponds to pin PIOm_n
 *    of port m. 0 = the pin is active LOW. If the level on this pin is LOW, the pin contributes to
 *    the group interrupt. 1 = the pin is active HIGH. If the level on this pin is HIGH, the pin
 *    contributes to the group interrupt.
 */
#define GINT_PORT_POL_POL(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_POL_POL_SHIFT)) & GINT_PORT_POL_POL_MASK)
/*! @} */

/* The count of GINT_PORT_POL */
#define GINT_PORT_POL_COUNT                      (2U)

/*! @name PORT_ENA - GPIO grouped interrupt port 0 enable register */
/*! @{ */
#define GINT_PORT_ENA_ENA_MASK                   (0xFFFFFFFFU)
#define GINT_PORT_ENA_ENA_SHIFT                  (0U)
/*! ENA - Enable port 0 pin for group interrupt. Bit n corresponds to pin Pm_n of port m. 0 = the
 *    port 0 pin is disabled and does not contribute to the grouped interrupt. 1 = the port 0 pin is
 *    enabled and contributes to the grouped interrupt.
 */
#define GINT_PORT_ENA_ENA(x)                     (((uint32_t)(((uint32_t)(x)) << GINT_PORT_ENA_ENA_SHIFT)) & GINT_PORT_ENA_ENA_MASK)
/*! @} */

/* The count of GINT_PORT_ENA */
#define GINT_PORT_ENA_COUNT                      (2U)


/*!
 * @}
 */ /* end of group GINT_Register_Masks */


/* GINT - Peripheral instance base addresses */
/** Peripheral GINT0 base address */
#define GINT0_BASE                               (0x40002000u)
/** Peripheral GINT0 base pointer */
#define GINT0                                    ((GINT_Type *)GINT0_BASE)
/** Peripheral GINT1 base address */
#define GINT1_BASE                               (0x40003000u)
/** Peripheral GINT1 base pointer */
#define GINT1                                    ((GINT_Type *)GINT1_BASE)
/** Array initializer of GINT peripheral base addresses */
#define GINT_BASE_ADDRS                          { GINT0_BASE, GINT1_BASE }
/** Array initializer of GINT peripheral base pointers */
#define GINT_BASE_PTRS                           { GINT0, GINT1 }
/** Interrupt vectors for the GINT peripheral type */
#define GINT_IRQS                                { GINT0_IRQn, GINT1_IRQn }

/*!
 * @}
 */ /* end of group GINT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint8_t B[2][32];                           /**< Byte pin registers for all port 0 and 1 GPIO pins, array offset: 0x0, array step: index*0x20, index2*0x1 */
       uint8_t RESERVED_0[4032];
  __IO uint32_t W[2][32];                          /**< Word pin registers for all port 0 and 1 GPIO pins, array offset: 0x1000, array step: index*0x80, index2*0x4 */
       uint8_t RESERVED_1[3840];
  __IO uint32_t DIR[2];                            /**< Direction registers, array offset: 0x2000, array step: 0x4 */
       uint8_t RESERVED_2[120];
  __IO uint32_t MASK[2];                           /**< Mask register, array offset: 0x2080, array step: 0x4 */
       uint8_t RESERVED_3[120];
  __IO uint32_t PIN[2];                            /**< Port pin register, array offset: 0x2100, array step: 0x4 */
       uint8_t RESERVED_4[120];
  __IO uint32_t MPIN[2];                           /**< Masked port register, array offset: 0x2180, array step: 0x4 */
       uint8_t RESERVED_5[120];
  __IO uint32_t SET[2];                            /**< Write: Set register for port Read: output bits for port, array offset: 0x2200, array step: 0x4 */
       uint8_t RESERVED_6[120];
  __O  uint32_t CLR[2];                            /**< Clear port, array offset: 0x2280, array step: 0x4 */
       uint8_t RESERVED_7[120];
  __O  uint32_t NOT[2];                            /**< Toggle port, array offset: 0x2300, array step: 0x4 */
       uint8_t RESERVED_8[120];
  __O  uint32_t DIRSET[2];                         /**< Set pin direction bits for port, array offset: 0x2380, array step: 0x4 */
       uint8_t RESERVED_9[120];
  __O  uint32_t DIRCLR[2];                         /**< Clear pin direction bits for port, array offset: 0x2400, array step: 0x4 */
       uint8_t RESERVED_10[120];
  __O  uint32_t DIRNOT[2];                         /**< Toggle pin direction bits for port, array offset: 0x2480, array step: 0x4 */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name B - Byte pin registers for all port 0 and 1 GPIO pins */
/*! @{ */
#define GPIO_B_PBYTE_MASK                        (0x1U)
#define GPIO_B_PBYTE_SHIFT                       (0U)
/*! PBYTE - Read: state of the pin PIOm_n, regardless of direction, masking, or alternate function,
 *    except that pins configured as analog I/O always read as 0. One register for each port pin.
 *    Supported pins depends on the specific device and package. Write: loads the pin's output bit.
 *    One register for each port pin. Supported pins depends on the specific device and package.
 */
#define GPIO_B_PBYTE(x)                          (((uint8_t)(((uint8_t)(x)) << GPIO_B_PBYTE_SHIFT)) & GPIO_B_PBYTE_MASK)
/*! @} */

/* The count of GPIO_B */
#define GPIO_B_COUNT                             (2U)

/* The count of GPIO_B */
#define GPIO_B_COUNT2                            (32U)

/*! @name W - Word pin registers for all port 0 and 1 GPIO pins */
/*! @{ */
#define GPIO_W_PWORD_MASK                        (0xFFFFFFFFU)
#define GPIO_W_PWORD_SHIFT                       (0U)
/*! PWORD - Read 0: pin PIOm_n is LOW. Write 0: clear output bit. Read 0xFFFF FFFF: pin PIOm_n is
 *    HIGH. Write any value 0x0000 0001 to 0xFFFF FFFF: set output bit. Only 0 or 0xFFFF FFFF can be
 *    read. Writing any value other than 0 will set the output bit. One register for each port pin.
 *    Supported pins depends on the specific device and package.
 */
#define GPIO_W_PWORD(x)                          (((uint32_t)(((uint32_t)(x)) << GPIO_W_PWORD_SHIFT)) & GPIO_W_PWORD_MASK)
/*! @} */

/* The count of GPIO_W */
#define GPIO_W_COUNT                             (2U)

/* The count of GPIO_W */
#define GPIO_W_COUNT2                            (32U)

/*! @name DIR - Direction registers */
/*! @{ */
#define GPIO_DIR_DIRP_MASK                       (0xFFFFFFFFU)
#define GPIO_DIR_DIRP_SHIFT                      (0U)
/*! DIRP - Selects pin direction for pin PIOm_n (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported
 *    pins depends on the specific device and package. 0 = input. 1 = output.
 */
#define GPIO_DIR_DIRP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_DIR_DIRP_SHIFT)) & GPIO_DIR_DIRP_MASK)
/*! @} */

/* The count of GPIO_DIR */
#define GPIO_DIR_COUNT                           (2U)

/*! @name MASK - Mask register */
/*! @{ */
#define GPIO_MASK_MASKP_MASK                     (0xFFFFFFFFU)
#define GPIO_MASK_MASKP_SHIFT                    (0U)
/*! MASKP - Controls which bits corresponding to PIOm_n are active in the MPORT register (bit 0 =
 *    PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on the specific device and package. 0 =
 *    Read MPORT: pin state; write MPORT: load output bit. 1 = Read MPORT: 0; write MPORT: output bit
 *    not affected.
 */
#define GPIO_MASK_MASKP(x)                       (((uint32_t)(((uint32_t)(x)) << GPIO_MASK_MASKP_SHIFT)) & GPIO_MASK_MASKP_MASK)
/*! @} */

/* The count of GPIO_MASK */
#define GPIO_MASK_COUNT                          (2U)

/*! @name PIN - Port pin register */
/*! @{ */
#define GPIO_PIN_PORT_MASK                       (0xFFFFFFFFU)
#define GPIO_PIN_PORT_SHIFT                      (0U)
/*! PORT - Reads pin states or loads output bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported
 *    pins depends on the specific device and package. 0 = Read: pin is low; write: clear output bit.
 *    1 = Read: pin is high; write: set output bit.
 */
#define GPIO_PIN_PORT(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_PIN_PORT_SHIFT)) & GPIO_PIN_PORT_MASK)
/*! @} */

/* The count of GPIO_PIN */
#define GPIO_PIN_COUNT                           (2U)

/*! @name MPIN - Masked port register */
/*! @{ */
#define GPIO_MPIN_MPORTP_MASK                    (0xFFFFFFFFU)
#define GPIO_MPIN_MPORTP_SHIFT                   (0U)
/*! MPORTP - Masked port register (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on
 *    the specific device and package. 0 = Read: pin is LOW and/or the corresponding bit in the MASK
 *    register is 1; write: clear output bit if the corresponding bit in the MASK register is 0. 1
 *    = Read: pin is HIGH and the corresponding bit in the MASK register is 0; write: set output bit
 *    if the corresponding bit in the MASK register is 0.
 */
#define GPIO_MPIN_MPORTP(x)                      (((uint32_t)(((uint32_t)(x)) << GPIO_MPIN_MPORTP_SHIFT)) & GPIO_MPIN_MPORTP_MASK)
/*! @} */

/* The count of GPIO_MPIN */
#define GPIO_MPIN_COUNT                          (2U)

/*! @name SET - Write: Set register for port Read: output bits for port */
/*! @{ */
#define GPIO_SET_SETP_MASK                       (0xFFFFFFFFU)
#define GPIO_SET_SETP_SHIFT                      (0U)
/*! SETP - Read or set output bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on
 *    the specific device and package. 0 = Read: output bit: write: no operation. 1 = Read: output
 *    bit; write: set output bit.
 */
#define GPIO_SET_SETP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_SET_SETP_SHIFT)) & GPIO_SET_SETP_MASK)
/*! @} */

/* The count of GPIO_SET */
#define GPIO_SET_COUNT                           (2U)

/*! @name CLR - Clear port */
/*! @{ */
#define GPIO_CLR_CLRP_MASK                       (0xFFFFFFFFU)
#define GPIO_CLR_CLRP_SHIFT                      (0U)
/*! CLRP - Clear output bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on the
 *    specific device and package. 0 = No operation. 1 = Clear output bit.
 */
#define GPIO_CLR_CLRP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_CLR_CLRP_SHIFT)) & GPIO_CLR_CLRP_MASK)
/*! @} */

/* The count of GPIO_CLR */
#define GPIO_CLR_COUNT                           (2U)

/*! @name NOT - Toggle port */
/*! @{ */
#define GPIO_NOT_NOTP_MASK                       (0xFFFFFFFFU)
#define GPIO_NOT_NOTP_SHIFT                      (0U)
/*! NOTP - Toggle output bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on the
 *    specific device and package. 0 = no operation. 1 = Toggle output bit.
 */
#define GPIO_NOT_NOTP(x)                         (((uint32_t)(((uint32_t)(x)) << GPIO_NOT_NOTP_SHIFT)) & GPIO_NOT_NOTP_MASK)
/*! @} */

/* The count of GPIO_NOT */
#define GPIO_NOT_COUNT                           (2U)

/*! @name DIRSET - Set pin direction bits for port */
/*! @{ */
#define GPIO_DIRSET_DIRSETP_MASK                 (0xFFFFFFFFU)
#define GPIO_DIRSET_DIRSETP_SHIFT                (0U)
/*! DIRSETP - Set direction bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on
 *    the specific device and package. 0 = No operation. 1 = Set direction bit.
 */
#define GPIO_DIRSET_DIRSETP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRSET_DIRSETP_SHIFT)) & GPIO_DIRSET_DIRSETP_MASK)
/*! @} */

/* The count of GPIO_DIRSET */
#define GPIO_DIRSET_COUNT                        (2U)

/*! @name DIRCLR - Clear pin direction bits for port */
/*! @{ */
#define GPIO_DIRCLR_DIRCLRP_MASK                 (0xFFFFFFFFU)
#define GPIO_DIRCLR_DIRCLRP_SHIFT                (0U)
/*! DIRCLRP - Clear direction bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends on
 *    the specific device and package. 0 = No operation. 1 = Clear direction bit.
 */
#define GPIO_DIRCLR_DIRCLRP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRCLR_DIRCLRP_SHIFT)) & GPIO_DIRCLR_DIRCLRP_MASK)
/*! @} */

/* The count of GPIO_DIRCLR */
#define GPIO_DIRCLR_COUNT                        (2U)

/*! @name DIRNOT - Toggle pin direction bits for port */
/*! @{ */
#define GPIO_DIRNOT_DIRNOTP_MASK                 (0xFFFFFFFFU)
#define GPIO_DIRNOT_DIRNOTP_SHIFT                (0U)
/*! DIRNOTP - Toggle direction bits (bit 0 = PIOn_0, bit 1 = PIOn_1, etc.). Supported pins depends
 *    on the specific device and package. 0 = no operation. 1 = Toggle direction bit.
 */
#define GPIO_DIRNOT_DIRNOTP(x)                   (((uint32_t)(((uint32_t)(x)) << GPIO_DIRNOT_DIRNOTP_SHIFT)) & GPIO_DIRNOT_DIRNOTP_MASK)
/*! @} */

/* The count of GPIO_DIRNOT */
#define GPIO_DIRNOT_COUNT                        (2U)


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIO base address */
#define GPIO_BASE                                (0x4008C000u)
/** Peripheral GPIO base pointer */
#define GPIO                                     ((GPIO_Type *)GPIO_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIO_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIO }

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 * @{
 */

/** I2C - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[2048];
  __IO uint32_t CFG;                               /**< Configuration for shared functions., offset: 0x800 */
  __IO uint32_t STAT;                              /**< Status register for Master, Slave, and Monitor functions., offset: 0x804 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable Set and read register., offset: 0x808 */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register., offset: 0x80C */
  __IO uint32_t TIMEOUT;                           /**< Time-out value register., offset: 0x810 */
  __IO uint32_t CLKDIV;                            /**< Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function., offset: 0x814 */
  __I  uint32_t INTSTAT;                           /**< Interrupt Status register for Master, Slave, and Monitor functions., offset: 0x818 */
       uint8_t RESERVED_1[4];
  __IO uint32_t MSTCTL;                            /**< Master control register., offset: 0x820 */
  __IO uint32_t MSTTIME;                           /**< Master timing configuration., offset: 0x824 */
  __IO uint32_t MSTDAT;                            /**< Combined Master receiver and transmitter data register., offset: 0x828 */
       uint8_t RESERVED_2[20];
  __IO uint32_t SLVCTL;                            /**< Slave control register., offset: 0x840 */
  __IO uint32_t SLVDAT;                            /**< Combined Slave receiver and transmitter data register., offset: 0x844 */
  __IO uint32_t SLVADR[4];                         /**< Slave address register., array offset: 0x848, array step: 0x4 */
  __IO uint32_t SLVQUAL0;                          /**< Slave Qualification for address 0., offset: 0x858 */
       uint8_t RESERVED_3[36];
  __I  uint32_t MONRXDAT;                          /**< Monitor receiver data register., offset: 0x880 */
       uint8_t RESERVED_4[1912];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name CFG - Configuration for shared functions. */
/*! @{ */
#define I2C_CFG_MSTEN_MASK                       (0x1U)
#define I2C_CFG_MSTEN_SHIFT                      (0U)
/*! MSTEN - Master Enable. When disabled, configurations settings for the Master function are not
 *    changed, but the Master function is internally reset.
 *  0b0..Disabled. The I2C Master function is disabled.
 *  0b1..Enabled. The I2C Master function is enabled.
 */
#define I2C_CFG_MSTEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MSTEN_SHIFT)) & I2C_CFG_MSTEN_MASK)
#define I2C_CFG_SLVEN_MASK                       (0x2U)
#define I2C_CFG_SLVEN_SHIFT                      (1U)
/*! SLVEN - Slave Enable. When disabled, configurations settings for the Slave function are not
 *    changed, but the Slave function is internally reset.
 *  0b0..Disabled. The I2C slave function is disabled.
 *  0b1..Enabled. The I2C slave function is enabled.
 */
#define I2C_CFG_SLVEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_SLVEN_SHIFT)) & I2C_CFG_SLVEN_MASK)
#define I2C_CFG_MONEN_MASK                       (0x4U)
#define I2C_CFG_MONEN_SHIFT                      (2U)
/*! MONEN - Monitor Enable. When disabled, configurations settings for the Monitor function are not
 *    changed, but the Monitor function is internally reset.
 *  0b0..Disabled. The I2C Monitor function is disabled.
 *  0b1..Enabled. The I2C Monitor function is enabled.
 */
#define I2C_CFG_MONEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONEN_SHIFT)) & I2C_CFG_MONEN_MASK)
#define I2C_CFG_TIMEOUTEN_MASK                   (0x8U)
#define I2C_CFG_TIMEOUTEN_SHIFT                  (3U)
/*! TIMEOUTEN - I2C bus Time-out Enable. When disabled, the time-out function is internally reset.
 *  0b0..Disabled. Time-out function is disabled.
 *  0b1..Enabled. Time-out function is enabled. Both types of time-out flags will be generated and will cause
 *       interrupts if they are enabled. Typically, only one time-out will be used in a system.
 */
#define I2C_CFG_TIMEOUTEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_TIMEOUTEN_SHIFT)) & I2C_CFG_TIMEOUTEN_MASK)
#define I2C_CFG_MONCLKSTR_MASK                   (0x10U)
#define I2C_CFG_MONCLKSTR_SHIFT                  (4U)
/*! MONCLKSTR - Monitor function Clock Stretching.
 *  0b0..Disabled. The Monitor function will not perform clock stretching. Software or DMA may not always be able
 *       to read data provided by the Monitor function before it is overwritten. This mode may be used when
 *       non-invasive monitoring is critical.
 *  0b1..Enabled. The Monitor function will perform clock stretching in order to ensure that software or DMA can
 *       read all incoming data supplied by the Monitor function.
 */
#define I2C_CFG_MONCLKSTR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONCLKSTR_SHIFT)) & I2C_CFG_MONCLKSTR_MASK)
#define I2C_CFG_HSCAPABLE_MASK                   (0x20U)
#define I2C_CFG_HSCAPABLE_SHIFT                  (5U)
/*! HSCAPABLE - High-speed mode Capable enable. Since High Speed mode alters the way I2C pins drive
 *    and filter, as well as the timing for certain I2C signalling, enabling High-speed mode applies
 *    to all functions: Master, Slave, and Monitor.
 *  0b0..Fast-mode plus. The I 2C interface will support Standard-mode, Fast-mode, and Fast-mode Plus, to the
 *       extent that the pin electronics support these modes. Any changes that need to be made to the pin controls,
 *       such as changing the drive strength or filtering, must be made by software via the IOCON register associated
 *       with each I2C pin,
 *  0b1..High-speed. In addition to Standard-mode, Fast-mode, and Fast-mode Plus, the I 2C interface will support
 *       High-speed mode to the extent that the pin electronics support these modes. See Section 25.7.2.2 for more
 *       information.
 */
#define I2C_CFG_HSCAPABLE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_HSCAPABLE_SHIFT)) & I2C_CFG_HSCAPABLE_MASK)
/*! @} */

/*! @name STAT - Status register for Master, Slave, and Monitor functions. */
/*! @{ */
#define I2C_STAT_MSTPENDING_MASK                 (0x1U)
#define I2C_STAT_MSTPENDING_SHIFT                (0U)
/*! MSTPENDING - Master Pending. Indicates that the Master is waiting to continue communication on
 *    the I2C-bus (pending) or is idle. When the master is pending, the MSTSTATE bits indicate what
 *    type of software service if any the master expects. This flag will cause an interrupt when set
 *    if, enabled via the INTENSET register. The MSTPENDING flag is not set when the DMA is handling
 *    an event (if the MSTDMA bit in the MSTCTL register is set). If the master is in the idle
 *    state, and no communication is needed, mask this interrupt.
 *  0b0..In progress. Communication is in progress and the Master function is busy and cannot currently accept a command.
 *  0b1..Pending. The Master function needs software service or is in the idle state. If the master is not in the
 *       idle state, it is waiting to receive or transmit data or the NACK bit.
 */
#define I2C_STAT_MSTPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTPENDING_SHIFT)) & I2C_STAT_MSTPENDING_MASK)
#define I2C_STAT_MSTSTATE_MASK                   (0xEU)
#define I2C_STAT_MSTSTATE_SHIFT                  (1U)
/*! MSTSTATE - Master State code. The master state code reflects the master state when the
 *    MSTPENDING bit is set, that is the master is pending or in the idle state. Each value of this field
 *    indicates a specific required service for the Master function. All other values are reserved. See
 *    Table 400 for details of state values and appropriate responses.
 *  0b000..Idle. The Master function is available to be used for a new transaction.
 *  0b001..Receive ready. Received data available (Master Receiver mode). Address plus Read was previously sent and Acknowledged by slave.
 *  0b010..Transmit ready. Data can be transmitted (Master Transmitter mode). Address plus Write was previously sent and Acknowledged by slave.
 *  0b011..NACK Address. Slave NACKed address.
 *  0b100..NACK Data. Slave NACKed transmitted data.
 */
#define I2C_STAT_MSTSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTATE_SHIFT)) & I2C_STAT_MSTSTATE_MASK)
#define I2C_STAT_MSTARBLOSS_MASK                 (0x10U)
#define I2C_STAT_MSTARBLOSS_SHIFT                (4U)
/*! MSTARBLOSS - Master Arbitration Loss flag. This flag can be cleared by software writing a 1 to
 *    this bit. It is also cleared automatically a 1 is written to MSTCONTINUE.
 *  0b0..No Arbitration Loss has occurred.
 *  0b1..Arbitration loss. The Master function has experienced an Arbitration Loss. At this point, the Master
 *       function has already stopped driving the bus and gone to an idle state. Software can respond by doing nothing,
 *       or by sending a Start in order to attempt to gain control of the bus when it next becomes idle.
 */
#define I2C_STAT_MSTARBLOSS(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTARBLOSS_SHIFT)) & I2C_STAT_MSTARBLOSS_MASK)
#define I2C_STAT_MSTSTSTPERR_MASK                (0x40U)
#define I2C_STAT_MSTSTSTPERR_SHIFT               (6U)
/*! MSTSTSTPERR - Master Start/Stop Error flag. This flag can be cleared by software writing a 1 to
 *    this bit. It is also cleared automatically a 1 is written to MSTCONTINUE.
 *  0b0..No Start/Stop Error has occurred.
 *  0b1..The Master function has experienced a Start/Stop Error. A Start or Stop was detected at a time when it is
 *       not allowed by the I2C specification. The Master interface has stopped driving the bus and gone to an
 *       idle state, no action is required. A request for a Start could be made, or software could attempt to insure
 *       that the bus has not stalled.
 */
#define I2C_STAT_MSTSTSTPERR(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTSTPERR_SHIFT)) & I2C_STAT_MSTSTSTPERR_MASK)
#define I2C_STAT_SLVPENDING_MASK                 (0x100U)
#define I2C_STAT_SLVPENDING_SHIFT                (8U)
/*! SLVPENDING - Slave Pending. Indicates that the Slave function is waiting to continue
 *    communication on the I2C-bus and needs software service. This flag will cause an interrupt when set if
 *    enabled via INTENSET. The SLVPENDING flag is not set when the DMA is handling an event (if the
 *    SLVDMA bit in the SLVCTL register is set). The SLVPENDING flag is read-only and is
 *    automatically cleared when a 1 is written to the SLVCONTINUE bit in the SLVCTL register. The point in time
 *    when SlvPending is set depends on whether the I2C interface is in HSCAPABLE mode. See Section
 *    25.7.2.2.2. When the I2C interface is configured to be HSCAPABLE, HS master codes are
 *    detected automatically. Due to the requirements of the HS I2C specification, slave addresses must
 *    also be detected automatically, since the address must be acknowledged before the clock can be
 *    stretched.
 *  0b0..In progress. The Slave function does not currently need service.
 *  0b1..Pending. The Slave function needs service. Information on what is needed can be found in the adjacent SLVSTATE field.
 */
#define I2C_STAT_SLVPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVPENDING_SHIFT)) & I2C_STAT_SLVPENDING_MASK)
#define I2C_STAT_SLVSTATE_MASK                   (0x600U)
#define I2C_STAT_SLVSTATE_SHIFT                  (9U)
/*! SLVSTATE - Slave State code. Each value of this field indicates a specific required service for
 *    the Slave function. All other values are reserved. See Table 401 for state values and actions.
 *    note that the occurrence of some states and how they are handled are affected by DMA mode and
 *    Automatic Operation modes.
 *  0b00..Slave address. Address plus R/W received. At least one of the four slave addresses has been matched by hardware.
 *  0b01..Slave receive. Received data is available (Slave Receiver mode).
 *  0b10..Slave transmit. Data can be transmitted (Slave Transmitter mode).
 */
#define I2C_STAT_SLVSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSTATE_SHIFT)) & I2C_STAT_SLVSTATE_MASK)
#define I2C_STAT_SLVNOTSTR_MASK                  (0x800U)
#define I2C_STAT_SLVNOTSTR_SHIFT                 (11U)
/*! SLVNOTSTR - Slave Not Stretching. Indicates when the slave function is stretching the I2C clock.
 *    This is needed in order to gracefully invoke Deep Sleep or Power-down modes during slave
 *    operation. This read-only flag reflects the slave function status in real time.
 *  0b0..Stretching. The slave function is currently stretching the I2C bus clock. Deep-Sleep or Power-down mode cannot be entered at this time.
 *  0b1..Not stretching. The slave function is not currently stretching the I 2C bus clock. Deep-sleep or
 *       Power-down mode could be entered at this time.
 */
#define I2C_STAT_SLVNOTSTR(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVNOTSTR_SHIFT)) & I2C_STAT_SLVNOTSTR_MASK)
#define I2C_STAT_SLVIDX_MASK                     (0x3000U)
#define I2C_STAT_SLVIDX_SHIFT                    (12U)
/*! SLVIDX - Slave address match Index. This field is valid when the I2C slave function has been
 *    selected by receiving an address that matches one of the slave addresses defined by any enabled
 *    slave address registers, and provides an identification of the address that was matched. It is
 *    possible that more than one address could be matched, but only one match can be reported here.
 *  0b00..Address 0. Slave address 0 was matched.
 *  0b01..Address 1. Slave address 1 was matched.
 *  0b10..Address 2. Slave address 2 was matched.
 *  0b11..Address 3. Slave address 3 was matched.
 */
#define I2C_STAT_SLVIDX(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVIDX_SHIFT)) & I2C_STAT_SLVIDX_MASK)
#define I2C_STAT_SLVSEL_MASK                     (0x4000U)
#define I2C_STAT_SLVSEL_SHIFT                    (14U)
/*! SLVSEL - Slave selected flag. SLVSEL is set after an address match when software tells the Slave
 *    function to acknowledge the address, or when the address has been automatically acknowledged.
 *    It is cleared when another address cycle presents an address that does not match an enabled
 *    address on the Slave function, when slave software decides to NACK a matched address, when
 *    there is a Stop detected on the bus, when the master NACKs slave data, and in some combinations of
 *    Automatic Operation. SLVSEL is not cleared if software NACKs data.
 *  0b0..Not selected. The Slave function is not currently selected.
 *  0b1..Selected. The Slave function is currently selected.
 */
#define I2C_STAT_SLVSEL(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSEL_SHIFT)) & I2C_STAT_SLVSEL_MASK)
#define I2C_STAT_SLVDESEL_MASK                   (0x8000U)
#define I2C_STAT_SLVDESEL_SHIFT                  (15U)
/*! SLVDESEL - Slave Deselected flag. This flag will cause an interrupt when set if enabled via
 *    INTENSET. This flag can be cleared by writing a 1 to this bit.
 *  0b0..Not deselected. The Slave function has not become deselected. This does not mean that it is currently
 *       selected. That information can be found in the SLVSEL flag.
 *  0b1..Deselected. The Slave function has become deselected. This is specifically caused by the SLVSEL flag
 *       changing from 1 to 0. See the description of SLVSEL for details on when that event occurs.
 */
#define I2C_STAT_SLVDESEL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVDESEL_SHIFT)) & I2C_STAT_SLVDESEL_MASK)
#define I2C_STAT_MONRDY_MASK                     (0x10000U)
#define I2C_STAT_MONRDY_SHIFT                    (16U)
/*! MONRDY - Monitor Ready. This flag is cleared when the MONRXDAT register is read.
 *  0b0..No data. The Monitor function does not currently have data available.
 *  0b1..Data waiting. The Monitor function has data waiting to be read.
 */
#define I2C_STAT_MONRDY(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONRDY_SHIFT)) & I2C_STAT_MONRDY_MASK)
#define I2C_STAT_MONOV_MASK                      (0x20000U)
#define I2C_STAT_MONOV_SHIFT                     (17U)
/*! MONOV - Monitor Overflow flag.
 *  0b0..No overrun. Monitor data has not overrun.
 *  0b1..Overrun. A Monitor data overrun has occurred. This can only happen when Monitor clock stretching not
 *       enabled via the MONCLKSTR bit in the CFG register. Writing 1 to this bit clears the flag.
 */
#define I2C_STAT_MONOV(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONOV_SHIFT)) & I2C_STAT_MONOV_MASK)
#define I2C_STAT_MONACTIVE_MASK                  (0x40000U)
#define I2C_STAT_MONACTIVE_SHIFT                 (18U)
/*! MONACTIVE - Monitor Active flag. Indicates when the Monitor function considers the I 2C bus to
 *    be active. Active is defined here as when some Master is on the bus: a bus Start has occurred
 *    more recently than a bus Stop.
 *  0b0..Inactive. The Monitor function considers the I2C bus to be inactive.
 *  0b1..Active. The Monitor function considers the I2C bus to be active.
 */
#define I2C_STAT_MONACTIVE(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONACTIVE_SHIFT)) & I2C_STAT_MONACTIVE_MASK)
#define I2C_STAT_MONIDLE_MASK                    (0x80000U)
#define I2C_STAT_MONIDLE_SHIFT                   (19U)
/*! MONIDLE - Monitor Idle flag. This flag is set when the Monitor function sees the I2C bus change
 *    from active to inactive. This can be used by software to decide when to process data
 *    accumulated by the Monitor function. This flag will cause an interrupt when set if enabled via the
 *    INTENSET register. The flag can be cleared by writing a 1 to this bit.
 *  0b0..Not idle. The I2C bus is not idle, or this flag has been cleared by software.
 *  0b1..Idle. The I2C bus has gone idle at least once since the last time this flag was cleared by software.
 */
#define I2C_STAT_MONIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONIDLE_SHIFT)) & I2C_STAT_MONIDLE_MASK)
#define I2C_STAT_EVENTTIMEOUT_MASK               (0x1000000U)
#define I2C_STAT_EVENTTIMEOUT_SHIFT              (24U)
/*! EVENTTIMEOUT - Event Time-out Interrupt flag. Indicates when the time between events has been
 *    longer than the time specified by the TIMEOUT register. Events include Start, Stop, and clock
 *    edges. The flag is cleared by writing a 1 to this bit. No time-out is created when the I2C-bus
 *    is idle.
 *  0b0..No time-out. I2C bus events have not caused a time-out.
 *  0b1..Event time-out. The time between I2C bus events has been longer than the time specified by the TIMEOUT register.
 */
#define I2C_STAT_EVENTTIMEOUT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_STAT_EVENTTIMEOUT_SHIFT)) & I2C_STAT_EVENTTIMEOUT_MASK)
#define I2C_STAT_SCLTIMEOUT_MASK                 (0x2000000U)
#define I2C_STAT_SCLTIMEOUT_SHIFT                (25U)
/*! SCLTIMEOUT - SCL Time-out Interrupt flag. Indicates when SCL has remained low longer than the
 *    time specific by the TIMEOUT register. The flag is cleared by writing a 1 to this bit.
 *  0b0..No time-out. SCL low time has not caused a time-out.
 *  0b1..Time-out. SCL low time has caused a time-out.
 */
#define I2C_STAT_SCLTIMEOUT(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SCLTIMEOUT_SHIFT)) & I2C_STAT_SCLTIMEOUT_MASK)
/*! @} */

/*! @name INTENSET - Interrupt Enable Set and read register. */
/*! @{ */
#define I2C_INTENSET_MSTPENDINGEN_MASK           (0x1U)
#define I2C_INTENSET_MSTPENDINGEN_SHIFT          (0U)
/*! MSTPENDINGEN - Master Pending interrupt Enable.
 *  0b0..Disabled. The MstPending interrupt is disabled.
 *  0b1..Enabled. The MstPending interrupt is enabled.
 */
#define I2C_INTENSET_MSTPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTPENDINGEN_SHIFT)) & I2C_INTENSET_MSTPENDINGEN_MASK)
#define I2C_INTENSET_MSTARBLOSSEN_MASK           (0x10U)
#define I2C_INTENSET_MSTARBLOSSEN_SHIFT          (4U)
/*! MSTARBLOSSEN - Master Arbitration Loss interrupt Enable.
 *  0b0..Disabled. The MstArbLoss interrupt is disabled.
 *  0b1..Enabled. The MstArbLoss interrupt is enabled.
 */
#define I2C_INTENSET_MSTARBLOSSEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTARBLOSSEN_SHIFT)) & I2C_INTENSET_MSTARBLOSSEN_MASK)
#define I2C_INTENSET_MSTSTSTPERREN_MASK          (0x40U)
#define I2C_INTENSET_MSTSTSTPERREN_SHIFT         (6U)
/*! MSTSTSTPERREN - Master Start/Stop Error interrupt Enable.
 *  0b0..Disabled. The MstStStpErr interrupt is disabled.
 *  0b1..Enabled. The MstStStpErr interrupt is enabled.
 */
#define I2C_INTENSET_MSTSTSTPERREN(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTSTSTPERREN_SHIFT)) & I2C_INTENSET_MSTSTSTPERREN_MASK)
#define I2C_INTENSET_SLVPENDINGEN_MASK           (0x100U)
#define I2C_INTENSET_SLVPENDINGEN_SHIFT          (8U)
/*! SLVPENDINGEN - Slave Pending interrupt Enable.
 *  0b0..Disabled. The SlvPending interrupt is disabled.
 *  0b1..Enabled. The SlvPending interrupt is enabled.
 */
#define I2C_INTENSET_SLVPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVPENDINGEN_SHIFT)) & I2C_INTENSET_SLVPENDINGEN_MASK)
#define I2C_INTENSET_SLVNOTSTREN_MASK            (0x800U)
#define I2C_INTENSET_SLVNOTSTREN_SHIFT           (11U)
/*! SLVNOTSTREN - Slave Not Stretching interrupt Enable.
 *  0b0..Disabled. The SlvNotStr interrupt is disabled.
 *  0b1..Enabled. The SlvNotStr interrupt is enabled.
 */
#define I2C_INTENSET_SLVNOTSTREN(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVNOTSTREN_SHIFT)) & I2C_INTENSET_SLVNOTSTREN_MASK)
#define I2C_INTENSET_SLVDESELEN_MASK             (0x8000U)
#define I2C_INTENSET_SLVDESELEN_SHIFT            (15U)
/*! SLVDESELEN - Slave Deselect interrupt Enable.
 *  0b0..Disabled. The SlvDeSel interrupt is disabled.
 *  0b1..Enabled. The SlvDeSel interrupt is enabled.
 */
#define I2C_INTENSET_SLVDESELEN(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVDESELEN_SHIFT)) & I2C_INTENSET_SLVDESELEN_MASK)
#define I2C_INTENSET_MONRDYEN_MASK               (0x10000U)
#define I2C_INTENSET_MONRDYEN_SHIFT              (16U)
/*! MONRDYEN - Monitor data Ready interrupt Enable.
 *  0b0..Disabled. The MonRdy interrupt is disabled.
 *  0b1..Enabled. The MonRdy interrupt is enabled.
 */
#define I2C_INTENSET_MONRDYEN(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONRDYEN_SHIFT)) & I2C_INTENSET_MONRDYEN_MASK)
#define I2C_INTENSET_MONOVEN_MASK                (0x20000U)
#define I2C_INTENSET_MONOVEN_SHIFT               (17U)
/*! MONOVEN - Monitor Overrun interrupt Enable.
 *  0b0..Disabled. The MonOv interrupt is disabled.
 *  0b1..Enabled. The MonOv interrupt is enabled.
 */
#define I2C_INTENSET_MONOVEN(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONOVEN_SHIFT)) & I2C_INTENSET_MONOVEN_MASK)
#define I2C_INTENSET_MONIDLEEN_MASK              (0x80000U)
#define I2C_INTENSET_MONIDLEEN_SHIFT             (19U)
/*! MONIDLEEN - Monitor Idle interrupt Enable.
 *  0b0..Disabled. The MonIdle interrupt is disabled.
 *  0b1..Enabled. The MonIdle interrupt is enabled.
 */
#define I2C_INTENSET_MONIDLEEN(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONIDLEEN_SHIFT)) & I2C_INTENSET_MONIDLEEN_MASK)
#define I2C_INTENSET_EVENTTIMEOUTEN_MASK         (0x1000000U)
#define I2C_INTENSET_EVENTTIMEOUTEN_SHIFT        (24U)
/*! EVENTTIMEOUTEN - Event time-out interrupt Enable.
 *  0b0..Disabled. The Event time-out interrupt is disabled.
 *  0b1..Enabled. The Event time-out interrupt is enabled.
 */
#define I2C_INTENSET_EVENTTIMEOUTEN(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_EVENTTIMEOUTEN_SHIFT)) & I2C_INTENSET_EVENTTIMEOUTEN_MASK)
#define I2C_INTENSET_SCLTIMEOUTEN_MASK           (0x2000000U)
#define I2C_INTENSET_SCLTIMEOUTEN_SHIFT          (25U)
/*! SCLTIMEOUTEN - SCL time-out interrupt Enable.
 *  0b0..Disabled. The SCL time-out interrupt is disabled.
 *  0b1..Enabled. The SCL time-out interrupt is enabled.
 */
#define I2C_INTENSET_SCLTIMEOUTEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SCLTIMEOUTEN_SHIFT)) & I2C_INTENSET_SCLTIMEOUTEN_MASK)
/*! @} */

/*! @name INTENCLR - Interrupt Enable Clear register. */
/*! @{ */
#define I2C_INTENCLR_MSTPENDINGCLR_MASK          (0x1U)
#define I2C_INTENCLR_MSTPENDINGCLR_SHIFT         (0U)
/*! MSTPENDINGCLR - Master Pending interrupt clear. Writing 1 to this bit clears the corresponding
 *    bit in the INTENSET register if implemented.
 */
#define I2C_INTENCLR_MSTPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTPENDINGCLR_SHIFT)) & I2C_INTENCLR_MSTPENDINGCLR_MASK)
#define I2C_INTENCLR_MSTARBLOSSCLR_MASK          (0x10U)
#define I2C_INTENCLR_MSTARBLOSSCLR_SHIFT         (4U)
/*! MSTARBLOSSCLR - Master Arbitration Loss interrupt clear.
 */
#define I2C_INTENCLR_MSTARBLOSSCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTARBLOSSCLR_SHIFT)) & I2C_INTENCLR_MSTARBLOSSCLR_MASK)
#define I2C_INTENCLR_MSTSTSTPERRCLR_MASK         (0x40U)
#define I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT        (6U)
/*! MSTSTSTPERRCLR - Master Start/Stop Error interrupt clear.
 */
#define I2C_INTENCLR_MSTSTSTPERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT)) & I2C_INTENCLR_MSTSTSTPERRCLR_MASK)
#define I2C_INTENCLR_SLVPENDINGCLR_MASK          (0x100U)
#define I2C_INTENCLR_SLVPENDINGCLR_SHIFT         (8U)
/*! SLVPENDINGCLR - Slave Pending interrupt clear.
 */
#define I2C_INTENCLR_SLVPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVPENDINGCLR_SHIFT)) & I2C_INTENCLR_SLVPENDINGCLR_MASK)
#define I2C_INTENCLR_SLVNOTSTRCLR_MASK           (0x800U)
#define I2C_INTENCLR_SLVNOTSTRCLR_SHIFT          (11U)
/*! SLVNOTSTRCLR - Slave Not Stretching interrupt clear.
 */
#define I2C_INTENCLR_SLVNOTSTRCLR(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVNOTSTRCLR_SHIFT)) & I2C_INTENCLR_SLVNOTSTRCLR_MASK)
#define I2C_INTENCLR_SLVDESELCLR_MASK            (0x8000U)
#define I2C_INTENCLR_SLVDESELCLR_SHIFT           (15U)
/*! SLVDESELCLR - Slave Deselect interrupt clear.
 */
#define I2C_INTENCLR_SLVDESELCLR(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVDESELCLR_SHIFT)) & I2C_INTENCLR_SLVDESELCLR_MASK)
#define I2C_INTENCLR_MONRDYCLR_MASK              (0x10000U)
#define I2C_INTENCLR_MONRDYCLR_SHIFT             (16U)
/*! MONRDYCLR - Monitor data Ready interrupt clear.
 */
#define I2C_INTENCLR_MONRDYCLR(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONRDYCLR_SHIFT)) & I2C_INTENCLR_MONRDYCLR_MASK)
#define I2C_INTENCLR_MONOVCLR_MASK               (0x20000U)
#define I2C_INTENCLR_MONOVCLR_SHIFT              (17U)
/*! MONOVCLR - Monitor Overrun interrupt clear.
 */
#define I2C_INTENCLR_MONOVCLR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONOVCLR_SHIFT)) & I2C_INTENCLR_MONOVCLR_MASK)
#define I2C_INTENCLR_MONIDLECLR_MASK             (0x80000U)
#define I2C_INTENCLR_MONIDLECLR_SHIFT            (19U)
/*! MONIDLECLR - Monitor Idle interrupt clear.
 */
#define I2C_INTENCLR_MONIDLECLR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONIDLECLR_SHIFT)) & I2C_INTENCLR_MONIDLECLR_MASK)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_MASK        (0x1000000U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT       (24U)
/*! EVENTTIMEOUTCLR - Event time-out interrupt clear.
 */
#define I2C_INTENCLR_EVENTTIMEOUTCLR(x)          (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_EVENTTIMEOUTCLR_MASK)
#define I2C_INTENCLR_SCLTIMEOUTCLR_MASK          (0x2000000U)
#define I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT         (25U)
/*! SCLTIMEOUTCLR - SCL time-out interrupt clear.
 */
#define I2C_INTENCLR_SCLTIMEOUTCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_SCLTIMEOUTCLR_MASK)
/*! @} */

/*! @name TIMEOUT - Time-out value register. */
/*! @{ */
#define I2C_TIMEOUT_TOMIN_MASK                   (0xFU)
#define I2C_TIMEOUT_TOMIN_SHIFT                  (0U)
/*! TOMIN - Time-out time value, bottom four bits. These are hard-wired to 0xF. This gives a minimum
 *    time-out of 16 I2C function clocks and also a time-out resolution of 16 I2C function clocks.
 */
#define I2C_TIMEOUT_TOMIN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TOMIN_SHIFT)) & I2C_TIMEOUT_TOMIN_MASK)
#define I2C_TIMEOUT_TO_MASK                      (0xFFF0U)
#define I2C_TIMEOUT_TO_SHIFT                     (4U)
/*! TO - Time-out time value. Specifies the time-out interval value in increments of 16 I 2C
 *    function clocks, as defined by the CLKDIV register. To change this value while I2C is in operation,
 *    disable all time-outs, write a new value to TIMEOUT, then re-enable time-outs. 0x000 = A
 *    time-out will occur after 16 counts of the I2C function clock. 0x001 = A time-out will occur after
 *    32 counts of the I2C function clock. 0xFFF = A time-out will occur after 65,536 counts of the
 *    I2C function clock.
 */
#define I2C_TIMEOUT_TO(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TO_SHIFT)) & I2C_TIMEOUT_TO_MASK)
/*! @} */

/*! @name CLKDIV - Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function. */
/*! @{ */
#define I2C_CLKDIV_DIVVAL_MASK                   (0xFFFFU)
#define I2C_CLKDIV_DIVVAL_SHIFT                  (0U)
/*! DIVVAL - This field controls how the Flexcomm clock (FCLK) is used by the I2C functions that
 *    need an internal clock in order to operate. 0x0000 = FCLK is used directly by the I2C. 0x0001 =
 *    FCLK is divided by 2 before use. 0x0002 = FCLK is divided by 3 before use. 0xFFFF = FCLK is
 *    divided by 65,536 before use.
 */
#define I2C_CLKDIV_DIVVAL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CLKDIV_DIVVAL_SHIFT)) & I2C_CLKDIV_DIVVAL_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt Status register for Master, Slave, and Monitor functions. */
/*! @{ */
#define I2C_INTSTAT_MSTPENDING_MASK              (0x1U)
#define I2C_INTSTAT_MSTPENDING_SHIFT             (0U)
/*! MSTPENDING - Master Pending.
 */
#define I2C_INTSTAT_MSTPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTPENDING_SHIFT)) & I2C_INTSTAT_MSTPENDING_MASK)
#define I2C_INTSTAT_MSTARBLOSS_MASK              (0x10U)
#define I2C_INTSTAT_MSTARBLOSS_SHIFT             (4U)
/*! MSTARBLOSS - Master Arbitration Loss flag.
 */
#define I2C_INTSTAT_MSTARBLOSS(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTARBLOSS_SHIFT)) & I2C_INTSTAT_MSTARBLOSS_MASK)
#define I2C_INTSTAT_MSTSTSTPERR_MASK             (0x40U)
#define I2C_INTSTAT_MSTSTSTPERR_SHIFT            (6U)
/*! MSTSTSTPERR - Master Start/Stop Error flag.
 */
#define I2C_INTSTAT_MSTSTSTPERR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTSTSTPERR_SHIFT)) & I2C_INTSTAT_MSTSTSTPERR_MASK)
#define I2C_INTSTAT_SLVPENDING_MASK              (0x100U)
#define I2C_INTSTAT_SLVPENDING_SHIFT             (8U)
/*! SLVPENDING - Slave Pending.
 */
#define I2C_INTSTAT_SLVPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVPENDING_SHIFT)) & I2C_INTSTAT_SLVPENDING_MASK)
#define I2C_INTSTAT_SLVNOTSTR_MASK               (0x800U)
#define I2C_INTSTAT_SLVNOTSTR_SHIFT              (11U)
/*! SLVNOTSTR - Slave Not Stretching status.
 */
#define I2C_INTSTAT_SLVNOTSTR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVNOTSTR_SHIFT)) & I2C_INTSTAT_SLVNOTSTR_MASK)
#define I2C_INTSTAT_SLVDESEL_MASK                (0x8000U)
#define I2C_INTSTAT_SLVDESEL_SHIFT               (15U)
/*! SLVDESEL - Slave Deselected flag.
 */
#define I2C_INTSTAT_SLVDESEL(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVDESEL_SHIFT)) & I2C_INTSTAT_SLVDESEL_MASK)
#define I2C_INTSTAT_MONRDY_MASK                  (0x10000U)
#define I2C_INTSTAT_MONRDY_SHIFT                 (16U)
/*! MONRDY - Monitor Ready.
 */
#define I2C_INTSTAT_MONRDY(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONRDY_SHIFT)) & I2C_INTSTAT_MONRDY_MASK)
#define I2C_INTSTAT_MONOV_MASK                   (0x20000U)
#define I2C_INTSTAT_MONOV_SHIFT                  (17U)
/*! MONOV - Monitor Overflow flag.
 */
#define I2C_INTSTAT_MONOV(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONOV_SHIFT)) & I2C_INTSTAT_MONOV_MASK)
#define I2C_INTSTAT_MONIDLE_MASK                 (0x80000U)
#define I2C_INTSTAT_MONIDLE_SHIFT                (19U)
/*! MONIDLE - Monitor Idle flag.
 */
#define I2C_INTSTAT_MONIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONIDLE_SHIFT)) & I2C_INTSTAT_MONIDLE_MASK)
#define I2C_INTSTAT_EVENTTIMEOUT_MASK            (0x1000000U)
#define I2C_INTSTAT_EVENTTIMEOUT_SHIFT           (24U)
/*! EVENTTIMEOUT - Event time-out Interrupt flag.
 */
#define I2C_INTSTAT_EVENTTIMEOUT(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_EVENTTIMEOUT_SHIFT)) & I2C_INTSTAT_EVENTTIMEOUT_MASK)
#define I2C_INTSTAT_SCLTIMEOUT_MASK              (0x2000000U)
#define I2C_INTSTAT_SCLTIMEOUT_SHIFT             (25U)
/*! SCLTIMEOUT - SCL time-out Interrupt flag.
 */
#define I2C_INTSTAT_SCLTIMEOUT(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SCLTIMEOUT_SHIFT)) & I2C_INTSTAT_SCLTIMEOUT_MASK)
/*! @} */

/*! @name MSTCTL - Master control register. */
/*! @{ */
#define I2C_MSTCTL_MSTCONTINUE_MASK              (0x1U)
#define I2C_MSTCTL_MSTCONTINUE_SHIFT             (0U)
/*! MSTCONTINUE - Master Continue. This bit is write-only.
 *  0b0..No effect.
 *  0b1..Continue. Informs the Master function to continue to the next operation. This must done after writing
 *       transmit data, reading received data, or any other housekeeping related to the next bus operation.
 */
#define I2C_MSTCTL_MSTCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTCONTINUE_SHIFT)) & I2C_MSTCTL_MSTCONTINUE_MASK)
#define I2C_MSTCTL_MSTSTART_MASK                 (0x2U)
#define I2C_MSTCTL_MSTSTART_SHIFT                (1U)
/*! MSTSTART - Master Start control. This bit is write-only.
 *  0b0..No effect.
 *  0b1..Start. A Start will be generated on the I2C bus at the next allowed time.
 */
#define I2C_MSTCTL_MSTSTART(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTART_SHIFT)) & I2C_MSTCTL_MSTSTART_MASK)
#define I2C_MSTCTL_MSTSTOP_MASK                  (0x4U)
#define I2C_MSTCTL_MSTSTOP_SHIFT                 (2U)
/*! MSTSTOP - Master Stop control. This bit is write-only.
 *  0b0..No effect.
 *  0b1..Stop. A Stop will be generated on the I2C bus at the next allowed time, preceded by a NACK to the slave
 *       if the master is receiving data from the slave (Master Receiver mode).
 */
#define I2C_MSTCTL_MSTSTOP(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTOP_SHIFT)) & I2C_MSTCTL_MSTSTOP_MASK)
#define I2C_MSTCTL_MSTDMA_MASK                   (0x8U)
#define I2C_MSTCTL_MSTDMA_SHIFT                  (3U)
/*! MSTDMA - Master DMA enable. Data operations of the I2C can be performed with DMA. Protocol type
 *    operations such as Start, address, Stop, and address match must always be done with software,
 *    typically via an interrupt. Address acknowledgement must also be done by software except when
 *    the I2C is configured to be HSCAPABLE (and address acknowledgement is handled entirely by
 *    hardware) or when Automatic Operation is enabled. When a DMA data transfer is complete, MSTDMA
 *    must be cleared prior to beginning the next operation, typically a Start or Stop.This bit is
 *    read/write.
 *  0b0..Disable. No DMA requests are generated for master operation.
 *  0b1..Enable. A DMA request is generated for I2C master data operations. When this I2C master is generating
 *       Acknowledge bits in Master Receiver mode, the acknowledge is generated automatically.
 */
#define I2C_MSTCTL_MSTDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTDMA_SHIFT)) & I2C_MSTCTL_MSTDMA_MASK)
/*! @} */

/*! @name MSTTIME - Master timing configuration. */
/*! @{ */
#define I2C_MSTTIME_MSTSCLLOW_MASK               (0x7U)
#define I2C_MSTTIME_MSTSCLLOW_SHIFT              (0U)
/*! MSTSCLLOW - Master SCL Low time. Specifies the minimum low time that will be asserted by this
 *    master on SCL. Other devices on the bus (masters or slaves) could lengthen this time. This
 *    corresponds to the parameter t LOW in the I2C bus specification. I2C bus specification parameters
 *    tBUF and tSU;STA have the same values and are also controlled by MSTSCLLOW.
 *  0b000..2 clocks. Minimum SCL low time is 2 clocks of the I2C clock pre-divider.
 *  0b001..3 clocks. Minimum SCL low time is 3 clocks of the I2C clock pre-divider.
 *  0b010..4 clocks. Minimum SCL low time is 4 clocks of the I2C clock pre-divider.
 *  0b011..5 clocks. Minimum SCL low time is 5 clocks of the I2C clock pre-divider.
 *  0b100..6 clocks. Minimum SCL low time is 6 clocks of the I2C clock pre-divider.
 *  0b101..7 clocks. Minimum SCL low time is 7 clocks of the I2C clock pre-divider.
 *  0b110..8 clocks. Minimum SCL low time is 8 clocks of the I2C clock pre-divider.
 *  0b111..9 clocks. Minimum SCL low time is 9 clocks of the I2C clock pre-divider.
 */
#define I2C_MSTTIME_MSTSCLLOW(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLLOW_SHIFT)) & I2C_MSTTIME_MSTSCLLOW_MASK)
#define I2C_MSTTIME_MSTSCLHIGH_MASK              (0x70U)
#define I2C_MSTTIME_MSTSCLHIGH_SHIFT             (4U)
/*! MSTSCLHIGH - Master SCL High time. Specifies the minimum high time that will be asserted by this
 *    master on SCL. Other masters in a multi-master system could shorten this time. This
 *    corresponds to the parameter tHIGH in the I2C bus specification. I2C bus specification parameters
 *    tSU;STO and tHD;STA have the same values and are also controlled by MSTSCLHIGH.
 *  0b000..2 clocks. Minimum SCL high time is 2 clock of the I2C clock pre-divider.
 *  0b001..3 clocks. Minimum SCL high time is 3 clocks of the I2C clock pre-divider .
 *  0b010..4 clocks. Minimum SCL high time is 4 clock of the I2C clock pre-divider.
 *  0b011..5 clocks. Minimum SCL high time is 5 clock of the I2C clock pre-divider.
 *  0b100..6 clocks. Minimum SCL high time is 6 clock of the I2C clock pre-divider.
 *  0b101..7 clocks. Minimum SCL high time is 7 clock of the I2C clock pre-divider.
 *  0b110..8 clocks. Minimum SCL high time is 8 clock of the I2C clock pre-divider.
 *  0b111..9 clocks. Minimum SCL high time is 9 clocks of the I2C clock pre-divider.
 */
#define I2C_MSTTIME_MSTSCLHIGH(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLHIGH_SHIFT)) & I2C_MSTTIME_MSTSCLHIGH_MASK)
/*! @} */

/*! @name MSTDAT - Combined Master receiver and transmitter data register. */
/*! @{ */
#define I2C_MSTDAT_DATA_MASK                     (0xFFU)
#define I2C_MSTDAT_DATA_SHIFT                    (0U)
/*! DATA - Master function data register. Read: read the most recently received data for the Master
 *    function. Write: transmit data using the Master function.
 */
#define I2C_MSTDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_MSTDAT_DATA_SHIFT)) & I2C_MSTDAT_DATA_MASK)
/*! @} */

/*! @name SLVCTL - Slave control register. */
/*! @{ */
#define I2C_SLVCTL_SLVCONTINUE_MASK              (0x1U)
#define I2C_SLVCTL_SLVCONTINUE_SHIFT             (0U)
/*! SLVCONTINUE - Slave Continue.
 *  0b0..No effect.
 *  0b1..Continue. Informs the Slave function to continue to the next operation, by clearing the SLVPENDING flag
 *       in the STAT register. This must be done after writing transmit data, reading received data, or any other
 *       housekeeping related to the next bus operation. Automatic Operation has different requirements. SLVCONTINUE
 *       should not be set unless SLVPENDING = 1.
 */
#define I2C_SLVCTL_SLVCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVCONTINUE_SHIFT)) & I2C_SLVCTL_SLVCONTINUE_MASK)
#define I2C_SLVCTL_SLVNACK_MASK                  (0x2U)
#define I2C_SLVCTL_SLVNACK_SHIFT                 (1U)
/*! SLVNACK - Slave NACK.
 *  0b0..No effect.
 *  0b1..NACK. Causes the Slave function to NACK the master when the slave is receiving data from the master (Slave Receiver mode).
 */
#define I2C_SLVCTL_SLVNACK(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVNACK_SHIFT)) & I2C_SLVCTL_SLVNACK_MASK)
#define I2C_SLVCTL_SLVDMA_MASK                   (0x8U)
#define I2C_SLVCTL_SLVDMA_SHIFT                  (3U)
/*! SLVDMA - Slave DMA enable.
 *  0b0..Disabled. No DMA requests are issued for Slave mode operation.
 *  0b1..Enabled. DMA requests are issued for I2C slave data transmission and reception.
 */
#define I2C_SLVCTL_SLVDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVDMA_SHIFT)) & I2C_SLVCTL_SLVDMA_MASK)
#define I2C_SLVCTL_AUTOACK_MASK                  (0x100U)
#define I2C_SLVCTL_AUTOACK_SHIFT                 (8U)
/*! AUTOACK - Automatic Acknowledge.When this bit is set, it will cause an I2C header which matches
 *    SLVADR0 and the direction set by AUTOMATCHREAD to be ACKed immediately; this is used with DMA
 *    to allow processing of the data without intervention. If this bit is clear and a header
 *    matches SLVADR0, the behavior is controlled by AUTONACK in the SLVADR0 register: allowing NACK or
 *    interrupt.
 *  0b0..Normal, non-automatic operation. If AUTONACK = 0, an SlvPending interrupt is generated when a matching
 *       address is received. If AUTONACK = 1, received addresses are NACKed (ignored).
 *  0b1..A header with matching SLVADR0 and matching direction as set by AUTOMATCHREAD will be ACKed immediately,
 *       allowing the master to move on to the data bytes. If the address matches SLVADR0, but the direction does
 *       not match AUTOMATCHREAD, the behavior will depend on the AUTONACK bit in the SLVADR0 register: if AUTONACK
 *       is set, then it will be Nacked; else if AUTONACK is clear, then a SlvPending interrupt is generated.
 */
#define I2C_SLVCTL_AUTOACK(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_AUTOACK_SHIFT)) & I2C_SLVCTL_AUTOACK_MASK)
#define I2C_SLVCTL_AUTOMATCHREAD_MASK            (0x200U)
#define I2C_SLVCTL_AUTOMATCHREAD_SHIFT           (9U)
/*! AUTOMATCHREAD - When AUTOACK is set, this bit controls whether it matches a read or write
 *    request on the next header with an address matching SLVADR0. Since DMA needs to be configured to
 *    match the transfer direction, the direction needs to be specified. This bit allows a direction to
 *    be chosen for the next operation.
 *  0b0..The expected next operation in Automatic Mode is an I2C write.
 *  0b1..The expected next operation in Automatic Mode is an I2C read.
 */
#define I2C_SLVCTL_AUTOMATCHREAD(x)              (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_AUTOMATCHREAD_SHIFT)) & I2C_SLVCTL_AUTOMATCHREAD_MASK)
/*! @} */

/*! @name SLVDAT - Combined Slave receiver and transmitter data register. */
/*! @{ */
#define I2C_SLVDAT_DATA_MASK                     (0xFFU)
#define I2C_SLVDAT_DATA_SHIFT                    (0U)
/*! DATA - Slave function data register. Read: read the most recently received data for the Slave
 *    function. Write: transmit data using the Slave function.
 */
#define I2C_SLVDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_SLVDAT_DATA_SHIFT)) & I2C_SLVDAT_DATA_MASK)
/*! @} */

/*! @name SLVADR - Slave address register. */
/*! @{ */
#define I2C_SLVADR_SADISABLE_MASK                (0x1U)
#define I2C_SLVADR_SADISABLE_SHIFT               (0U)
/*! SADISABLE - Slave Address n Disable.
 *  0b0..Enabled. Slave Address n is enabled.
 *  0b1..Ignored Slave Address n is ignored.
 */
#define I2C_SLVADR_SADISABLE(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SADISABLE_SHIFT)) & I2C_SLVADR_SADISABLE_MASK)
#define I2C_SLVADR_SLVADR_MASK                   (0xFEU)
#define I2C_SLVADR_SLVADR_SHIFT                  (1U)
/*! SLVADR - Slave Address. Seven bit slave address that is compared to received addresses if enabled.
 */
#define I2C_SLVADR_SLVADR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SLVADR_SHIFT)) & I2C_SLVADR_SLVADR_MASK)
#define I2C_SLVADR_AUTONACK_MASK                 (0x8000U)
#define I2C_SLVADR_AUTONACK_SHIFT                (15U)
/*! AUTONACK - Automatic NACK operation. Used in conjunction with AUTOACK and AUTOMATCHREAD, allows
 *    software to ignore I2C traffic while handling previous I2C data or other operations.
 *  0b0..Normal operation, matching I2C addresses are not ignored.
 *  0b1..Automatic-only mode. All incoming addresses are ignored (NACKed), unless AUTOACK is set, it matches
 *       SLVADRn, and AUTOMATCHREAD matches the direction.
 */
#define I2C_SLVADR_AUTONACK(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_AUTONACK_SHIFT)) & I2C_SLVADR_AUTONACK_MASK)
/*! @} */

/* The count of I2C_SLVADR */
#define I2C_SLVADR_COUNT                         (4U)

/*! @name SLVQUAL0 - Slave Qualification for address 0. */
/*! @{ */
#define I2C_SLVQUAL0_QUALMODE0_MASK              (0x1U)
#define I2C_SLVQUAL0_QUALMODE0_SHIFT             (0U)
/*! QUALMODE0 - Qualify mode for slave address 0.
 *  0b0..Mask. The SLVQUAL0 field is used as a logical mask for matching address 0.
 *  0b1..Extend. The SLVQUAL0 field is used to extend address 0 matching in a range of addresses.
 */
#define I2C_SLVQUAL0_QUALMODE0(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_QUALMODE0_SHIFT)) & I2C_SLVQUAL0_QUALMODE0_MASK)
#define I2C_SLVQUAL0_SLVQUAL0_MASK               (0xFEU)
#define I2C_SLVQUAL0_SLVQUAL0_SHIFT              (1U)
/*! SLVQUAL0 - Slave address Qualifier for address 0. A value of 0 causes the address in SLVADR0 to
 *    be used as-is, assuming that it is enabled. If QUALMODE0 = 0, any bit in this field which is
 *    set to 1 will cause an automatic match of the corresponding bit of the received address when it
 *    is compared to the SLVADR0 register. If QUALMODE0 = 1, an address range is matched for
 *    address 0. This range extends from the value defined by SLVADR0 to the address defined by SLVQUAL0
 *    (address matches when SLVADR0[7:1] <= received address <= SLVQUAL0[7:1]).
 */
#define I2C_SLVQUAL0_SLVQUAL0(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_SLVQUAL0_SHIFT)) & I2C_SLVQUAL0_SLVQUAL0_MASK)
/*! @} */

/*! @name MONRXDAT - Monitor receiver data register. */
/*! @{ */
#define I2C_MONRXDAT_MONRXDAT_MASK               (0xFFU)
#define I2C_MONRXDAT_MONRXDAT_SHIFT              (0U)
/*! MONRXDAT - Monitor function Receiver Data. This reflects every data byte that passes on the I2C pins.
 */
#define I2C_MONRXDAT_MONRXDAT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRXDAT_SHIFT)) & I2C_MONRXDAT_MONRXDAT_MASK)
#define I2C_MONRXDAT_MONSTART_MASK               (0x100U)
#define I2C_MONRXDAT_MONSTART_SHIFT              (8U)
/*! MONSTART - Monitor Received Start.
 *  0b0..No start detected. The Monitor function has not detected a Start event on the I2C bus.
 *  0b1..Start detected. The Monitor function has detected a Start event on the I2C bus.
 */
#define I2C_MONRXDAT_MONSTART(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONSTART_SHIFT)) & I2C_MONRXDAT_MONSTART_MASK)
#define I2C_MONRXDAT_MONRESTART_MASK             (0x200U)
#define I2C_MONRXDAT_MONRESTART_SHIFT            (9U)
/*! MONRESTART - Monitor Received Repeated Start.
 *  0b0..No repeated start detected. The Monitor function has not detected a Repeated Start event on the I2C bus.
 *  0b1..Repeated start detected. The Monitor function has detected a Repeated Start event on the I2C bus.
 */
#define I2C_MONRXDAT_MONRESTART(x)               (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRESTART_SHIFT)) & I2C_MONRXDAT_MONRESTART_MASK)
#define I2C_MONRXDAT_MONNACK_MASK                (0x400U)
#define I2C_MONRXDAT_MONNACK_SHIFT               (10U)
/*! MONNACK - Monitor Received NACK.
 *  0b0..Acknowledged. The data currently being provided by the Monitor function was acknowledged by at least one master or slave receiver.
 *  0b1..Not acknowledged. The data currently being provided by the Monitor function was not acknowledged by any receiver.
 */
#define I2C_MONRXDAT_MONNACK(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONNACK_SHIFT)) & I2C_MONRXDAT_MONNACK_MASK)
/*! @} */

/*! @name ID - Peripheral identification register. */
/*! @{ */
#define I2C_ID_APERTURE_MASK                     (0xFFU)
#define I2C_ID_APERTURE_SHIFT                    (0U)
/*! APERTURE - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture.
 */
#define I2C_ID_APERTURE(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_ID_APERTURE_SHIFT)) & I2C_ID_APERTURE_MASK)
#define I2C_ID_MINOR_REV_MASK                    (0xF00U)
#define I2C_ID_MINOR_REV_SHIFT                   (8U)
/*! MINOR_REV - Minor revision of module implementation.
 */
#define I2C_ID_MINOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_ID_MINOR_REV_SHIFT)) & I2C_ID_MINOR_REV_MASK)
#define I2C_ID_MAJOR_REV_MASK                    (0xF000U)
#define I2C_ID_MAJOR_REV_SHIFT                   (12U)
/*! MAJOR_REV - Major revision of module implementation.
 */
#define I2C_ID_MAJOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_ID_MAJOR_REV_SHIFT)) & I2C_ID_MAJOR_REV_MASK)
#define I2C_ID_ID_MASK                           (0xFFFF0000U)
#define I2C_ID_ID_SHIFT                          (16U)
/*! ID - Module identifier for the selected function.
 */
#define I2C_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << I2C_ID_ID_SHIFT)) & I2C_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40086000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40087000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Peripheral I2C2 base address */
#define I2C2_BASE                                (0x40088000u)
/** Peripheral I2C2 base pointer */
#define I2C2                                     ((I2C_Type *)I2C2_BASE)
/** Peripheral I2C3 base address */
#define I2C3_BASE                                (0x40089000u)
/** Peripheral I2C3 base pointer */
#define I2C3                                     ((I2C_Type *)I2C3_BASE)
/** Peripheral I2C4 base address */
#define I2C4_BASE                                (0x4008A000u)
/** Peripheral I2C4 base pointer */
#define I2C4                                     ((I2C_Type *)I2C4_BASE)
/** Peripheral I2C5 base address */
#define I2C5_BASE                                (0x40096000u)
/** Peripheral I2C5 base pointer */
#define I2C5                                     ((I2C_Type *)I2C5_BASE)
/** Peripheral I2C6 base address */
#define I2C6_BASE                                (0x40097000u)
/** Peripheral I2C6 base pointer */
#define I2C6                                     ((I2C_Type *)I2C6_BASE)
/** Peripheral I2C7 base address */
#define I2C7_BASE                                (0x40098000u)
/** Peripheral I2C7 base pointer */
#define I2C7                                     ((I2C_Type *)I2C7_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE, I2C4_BASE, I2C5_BASE, I2C6_BASE, I2C7_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1, I2C2, I2C3, I2C4, I2C5, I2C6, I2C7 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I2S Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Peripheral_Access_Layer I2S Peripheral Access Layer
 * @{
 */

/** I2S - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[3072];
  __IO uint32_t CFG1;                              /**< Configuration register 1 for the primary channel pair., offset: 0xC00 */
  __IO uint32_t CFG2;                              /**< Configuration register 2 for the primary channel pair., offset: 0xC04 */
  __IO uint32_t STAT;                              /**< Status register for the primary channel pair., offset: 0xC08 */
       uint8_t RESERVED_1[16];
  __IO uint32_t DIV;                               /**< Clock divider, used by all channel pairs., offset: 0xC1C */
       uint8_t RESERVED_2[480];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
  __O  uint32_t FIFOWR48H;                         /**< FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE24 */
       uint8_t RESERVED_5[8];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
  __I  uint32_t FIFORD48H;                         /**< FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE34 */
       uint8_t RESERVED_6[8];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
  __I  uint32_t FIFORD48HNOPOP;                    /**< FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA., offset: 0xE44 */
       uint8_t RESERVED_7[436];
  __I  uint32_t ID;                                /**< I2S Module identification, offset: 0xFFC */
} I2S_Type;

/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */

/*! @name CFG1 - Configuration register 1 for the primary channel pair. */
/*! @{ */
#define I2S_CFG1_MAINENABLE_MASK                 (0x1U)
#define I2S_CFG1_MAINENABLE_SHIFT                (0U)
/*! MAINENABLE - Main enable for I 2S function in this Flexcomm
 *  0b0..All I 2S channel pairs in this Flexcomm are disabled and the internal state machines, counters, and flags
 *       are reset. No other channel pairs can be enabled.
 *  0b1..This I 2S channel pair is enabled. Other channel pairs in this Flexcomm may be enabled in their individual PAIRENABLE bits.
 */
#define I2S_CFG1_MAINENABLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MAINENABLE_SHIFT)) & I2S_CFG1_MAINENABLE_MASK)
#define I2S_CFG1_DATAPAUSE_MASK                  (0x2U)
#define I2S_CFG1_DATAPAUSE_SHIFT                 (1U)
/*! DATAPAUSE - Data flow Pause. Allows pausing data flow between the I2S serializer/deserializer
 *    and the FIFO. This could be done in order to change streams, or while restarting after a data
 *    underflow or overflow. When paused, FIFO operations can be done without corrupting data that is
 *    in the process of being sent or received. Once a data pause has been requested, the interface
 *    may need to complete sending data that was in progress before interrupting the flow of data.
 *    Software must check that the pause is actually in effect before taking action. This is done by
 *    monitoring the DATAPAUSED flag in the STAT register. When DATAPAUSE is cleared, data transfer
 *    will resume at the beginning of the next frame.
 *  0b0..Normal operation, or resuming normal operation at the next frame if the I2S has already been paused.
 *  0b1..A pause in the data flow is being requested. It is in effect when DATAPAUSED in STAT = 1.
 */
#define I2S_CFG1_DATAPAUSE(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATAPAUSE_SHIFT)) & I2S_CFG1_DATAPAUSE_MASK)
#define I2S_CFG1_PAIRCOUNT_MASK                  (0xCU)
#define I2S_CFG1_PAIRCOUNT_SHIFT                 (2U)
/*! PAIRCOUNT - Provides the number of I2S channel pairs in this Flexcomm This is a read-only field
 *    whose value may be different in other Flexcomms. 00 = there is 1 I2S channel pair in this
 *    Flexcomm. 01 = there are 2 I2S channel pairs in this Flexcomm. 10 = there are 3 I2S channel pairs
 *    in this Flexcomm. 11 = there are 4 I2S channel pairs in this Flexcomm.
 *  0b00..1 I2S channel pairs in this flexcomm
 *  0b01..2 I2S channel pairs in this flexcomm
 *  0b10..3 I2S channel pairs in this flexcomm
 *  0b11..4 I2S channel pairs in this flexcomm
 */
#define I2S_CFG1_PAIRCOUNT(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_PAIRCOUNT_SHIFT)) & I2S_CFG1_PAIRCOUNT_MASK)
#define I2S_CFG1_MSTSLVCFG_MASK                  (0x30U)
#define I2S_CFG1_MSTSLVCFG_SHIFT                 (4U)
/*! MSTSLVCFG - Master / slave configuration selection, determining how SCK and WS are used by all channel pairs in this Flexcomm.
 *  0b00..Normal slave mode, the default mode. SCK and WS are received from a master and used to transmit or receive data.
 *  0b01..WS synchronized master. WS is received from another master and used to synchronize the generation of
 *        SCK, when divided from the Flexcomm function clock.
 *  0b10..Master using an existing SCK. SCK is received and used directly to generate WS, as well as transmitting or receiving data.
 *  0b11..Normal master mode. SCK and WS are generated so they can be sent to one or more slave devices.
 */
#define I2S_CFG1_MSTSLVCFG(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MSTSLVCFG_SHIFT)) & I2S_CFG1_MSTSLVCFG_MASK)
#define I2S_CFG1_MODE_MASK                       (0xC0U)
#define I2S_CFG1_MODE_SHIFT                      (6U)
/*! MODE - Selects the basic I2S operating mode. Other configurations modify this to obtain all
 *    supported cases. See Formats and modes for examples.
 *  0b00..I2S mode a.k.a. 'classic' mode. WS has a 50% duty cycle, with (for each enabled channel pair) one piece
 *        of left channel data occurring during the first phase, and one pieces of right channel data occurring
 *        during the second phase. In this mode, the data region begins one clock after the leading WS edge for the
 *        frame. For a 50% WS duty cycle, FRAMELEN must define an even number of I2S clocks for the frame. If
 *        FRAMELEN defines an odd number of clocks per frame, the extra clock will occur on the right.
 *  0b01..DSP mode where WS has a 50% duty cycle. See remark for mode 0.
 *  0b10..DSP mode where WS has a one clock long pulse at the beginning of each data frame.
 *  0b11..DSP mode where WS has a one data slot long pulse at the beginning of each data frame.
 */
#define I2S_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_MODE_SHIFT)) & I2S_CFG1_MODE_MASK)
#define I2S_CFG1_RIGHTLOW_MASK                   (0x100U)
#define I2S_CFG1_RIGHTLOW_SHIFT                  (8U)
/*! RIGHTLOW - Right channel data is in the Low portion of FIFO data. Essentially, this swaps left
 *    and right channel data as it is transferred to or from the FIFO. This bit is not used if the
 *    data width is greater than 24 bits or if PDMDATA = 1. Note that if the ONECHANNEL field (bit 10
 *    of this register) = 1, the one channel to be used is the nominally the left channel. POSITION
 *    can still place that data in the frame where right channel data is normally located. if all
 *    enabled channel pairs have ONECHANNEL = 1, then RIGHTLOW = 1 is not allowed.
 *  0b0..The right channel is taken from the high part of the FIFO data. For example, when data is 16 bits, FIFO
 *       bits 31:16 are used for the right channel.
 *  0b1..The right channel is taken from the low part of the FIFO data. For example, when data is 16 bits, FIFO
 *       bits 15:0 are used for the right channel.
 */
#define I2S_CFG1_RIGHTLOW(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_RIGHTLOW_SHIFT)) & I2S_CFG1_RIGHTLOW_MASK)
#define I2S_CFG1_LEFTJUST_MASK                   (0x200U)
#define I2S_CFG1_LEFTJUST_SHIFT                  (9U)
/*! LEFTJUST - Left Justify data.
 *  0b0..Data is transferred between the FIFO and the I2S serializer/deserializer right justified, i.e. starting
 *       from bit 0 and continuing to the position defined by DATALEN. This would correspond to right justified data
 *       in the stream on the data bus.
 *  0b1..Data is transferred between the FIFO and the I2S serializer/deserializer left justified, i.e. starting
 *       from the MSB of the FIFO entry and continuing for the number of bits defined by DATALEN. This would
 *       correspond to left justified data in the stream on the data bus.
 */
#define I2S_CFG1_LEFTJUST(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_LEFTJUST_SHIFT)) & I2S_CFG1_LEFTJUST_MASK)
#define I2S_CFG1_ONECHANNEL_MASK                 (0x400U)
#define I2S_CFG1_ONECHANNEL_SHIFT                (10U)
/*! ONECHANNEL - Single channel mode. Applies to both transmit and receive. This configuration bit
 *    applies only to the first I2S channel pair. Other channel pairs may select this mode
 *    independently in their separate CFG1 registers.
 *  0b0..I2S data for this channel pair is treated as left and right channels.
 *  0b1..I2S data for this channel pair is treated as a single channel, functionally the left channel for this
 *       pair. In mode 0 only, the right side of the frame begins at POSITION = 0x100. This is because mode 0 makes a
 *       clear distinction between the left and right sides of the frame. When ONECHANNEL = 1, the single channel
 *       of data may be placed on the right by setting POSITION to 0x100 + the data position within the right side
 *       (e.g. 0x108 would place data starting at the 8th clock after the middle of the frame). In other modes, data
 *       for the single channel of data is placed at the clock defined by POSITION.
 */
#define I2S_CFG1_ONECHANNEL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_ONECHANNEL_SHIFT)) & I2S_CFG1_ONECHANNEL_MASK)
#define I2S_CFG1_SCK_POL_MASK                    (0x1000U)
#define I2S_CFG1_SCK_POL_SHIFT                   (12U)
/*! SCK_POL - SCK polarity.
 *  0b0..Data is launched on SCK falling edges and sampled on SCK rising edges (standard for I2S).
 *  0b1..Data is launched on SCK rising edges and sampled on SCK falling edges.
 */
#define I2S_CFG1_SCK_POL(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_SCK_POL_SHIFT)) & I2S_CFG1_SCK_POL_MASK)
#define I2S_CFG1_WS_POL_MASK                     (0x2000U)
#define I2S_CFG1_WS_POL_SHIFT                    (13U)
/*! WS_POL - WS polarity.
 *  0b0..Data frames begin at a falling edge of WS (standard for classic I2S).
 *  0b1..WS is inverted, resulting in a data frame beginning at a rising edge of WS (standard for most 'non-classic' variations of I2S).
 */
#define I2S_CFG1_WS_POL(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_WS_POL_SHIFT)) & I2S_CFG1_WS_POL_MASK)
#define I2S_CFG1_DATALEN_MASK                    (0x1F0000U)
#define I2S_CFG1_DATALEN_SHIFT                   (16U)
/*! DATALEN - Data Length, minus 1 encoded, defines the number of data bits to be transmitted or
 *    received for all I2S channel pairs in this Flexcomm. Note that data is only driven to or received
 *    from SDA for the number of bits defined by DATALEN. DATALEN is also used in these ways by the
 *    I2S: Determines the size of data transfers between the FIFO and the I2S
 *    serializer/deserializer. See FIFO buffer configurations and usage In mode 1, 2, and 3, determines the location of
 *    right data following left data in the frame. In mode 3 (where WS has a one data slot long pulse
 *    at the beginning of each data frame) determines the duration of the WS pulse. Values: 0x00 to
 *    0x02 = not supported 0x03 = data is 4 bits in length 0x04 = data is 5 bits in length 0x1F =
 *    data is 32 bits in length
 */
#define I2S_CFG1_DATALEN(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_CFG1_DATALEN_SHIFT)) & I2S_CFG1_DATALEN_MASK)
/*! @} */

/*! @name CFG2 - Configuration register 2 for the primary channel pair. */
/*! @{ */
#define I2S_CFG2_FRAMELEN_MASK                   (0x1FFU)
#define I2S_CFG2_FRAMELEN_SHIFT                  (0U)
/*! FRAMELEN - Frame Length, minus 1 encoded, defines the number of clocks and data bits in the
 *    frames that this channel pair participates in. See Frame format. 0x000 to 0x002 = not supported
 *    0x003 = frame is 4 bits in total length 0x004 = frame is 5 bits in total length 0x1FF = frame is
 *    512 bits in total length if FRAMELEN is an defines an odd length frame (e.g. 33 clocks) in
 *    mode 0 or 1, the extra clock appears in the right half. When MODE = 3, FRAMELEN must be larger
 *    than DATALEN in order for the WS pulse to be generated correctly.
 */
#define I2S_CFG2_FRAMELEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_FRAMELEN_SHIFT)) & I2S_CFG2_FRAMELEN_MASK)
#define I2S_CFG2_POSITION_MASK                   (0x1FF0000U)
#define I2S_CFG2_POSITION_SHIFT                  (16U)
/*! POSITION - Data Position. Defines the location within the frame of the data for this channel
 *    pair. POSITION + DATALEN must be less than FRAMELEN. See Frame format. When MODE = 0, POSITION
 *    defines the location of data in both the left phase and right phase, starting one clock after
 *    the WS edge. In other modes, POSITION defines the location of data within the entire frame.
 *    ONECHANNEL = 1 while MODE = 0 is a special case, see the description of ONECHANNEL. The
 *    combination of DATALEN and the POSITION fields of all channel pairs must be made such that the channels
 *    do not overlap within the frame. 0x000 = data begins at bit position 0 (the first bit
 *    position) within the frame or WS phase. 0x001 = data begins at bit position 1 within the frame or WS
 *    phase. 0x002 = data begins at bit position 2 within the frame or WS phase.
 */
#define I2S_CFG2_POSITION(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_CFG2_POSITION_SHIFT)) & I2S_CFG2_POSITION_MASK)
/*! @} */

/*! @name STAT - Status register for the primary channel pair. */
/*! @{ */
#define I2S_STAT_BUSY_MASK                       (0x1U)
#define I2S_STAT_BUSY_SHIFT                      (0U)
/*! BUSY - Busy status for the primary channel pair. Other BUSY flags may be found in the STAT register for each channel pair.
 *  0b0..The transmitter/receiver for channel pair is currently idle.
 *  0b1..The transmitter/receiver for channel pair is currently processing data.
 */
#define I2S_STAT_BUSY(x)                         (((uint32_t)(((uint32_t)(x)) << I2S_STAT_BUSY_SHIFT)) & I2S_STAT_BUSY_MASK)
#define I2S_STAT_SLVFRMERR_MASK                  (0x2U)
#define I2S_STAT_SLVFRMERR_SHIFT                 (1U)
/*! SLVFRMERR - Slave Frame Error flag. This applies when at least one channel pair is operating as
 *    a slave. An error indicates that the incoming WS signal did not transition as expected due to
 *    a mismatch between FRAMELEN and the actual incoming I2S stream.
 *  0b0..No error has been recorded.
 *  0b1..An error has been recorded for some channel pair that is operating in slave mode. ERROR is cleared by writing a 1 to this bit position.
 */
#define I2S_STAT_SLVFRMERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_STAT_SLVFRMERR_SHIFT)) & I2S_STAT_SLVFRMERR_MASK)
#define I2S_STAT_LR_MASK                         (0x4U)
#define I2S_STAT_LR_SHIFT                        (2U)
/*! LR - Left/Right indication. This flag is considered to be a debugging aid and is not expected to
 *    be used by an I2S driver. Valid when one channel pair is busy. Indicates left or right data
 *    being processed for the currently busy channel pair.
 *  0b0..Left channel.
 *  0b1..Right channel.
 */
#define I2S_STAT_LR(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_STAT_LR_SHIFT)) & I2S_STAT_LR_MASK)
#define I2S_STAT_DATAPAUSED_MASK                 (0x8U)
#define I2S_STAT_DATAPAUSED_SHIFT                (3U)
/*! DATAPAUSED - Data Paused status flag. Applies to all I2S channels
 *  0b0..Data is not currently paused. A data pause may have been requested but is not yet in force, waiting for
 *       an allowed pause point. Refer to the description of the DATAPAUSE control bit in the CFG1 register.
 *  0b1..A data pause has been requested and is now in force.
 */
#define I2S_STAT_DATAPAUSED(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_STAT_DATAPAUSED_SHIFT)) & I2S_STAT_DATAPAUSED_MASK)
/*! @} */

/*! @name DIV - Clock divider, used by all channel pairs. */
/*! @{ */
#define I2S_DIV_DIV_MASK                         (0xFFFU)
#define I2S_DIV_DIV_SHIFT                        (0U)
/*! DIV - This field controls how this I2S block uses the Flexcomm function clock. 0x000 = The
 *    Flexcomm function clock is used directly. 0x001 = The Flexcomm function clock is divided by 2.
 *    0x002 = The Flexcomm function clock is divided by 3. 0xFFF = The Flexcomm function clock is
 *    divided by 4,096.
 */
#define I2S_DIV_DIV(x)                           (((uint32_t)(((uint32_t)(x)) << I2S_DIV_DIV_SHIFT)) & I2S_DIV_DIV_MASK)
/*! @} */

/*! @name FIFOCFG - FIFO configuration and enable register. */
/*! @{ */
#define I2S_FIFOCFG_ENABLETX_MASK                (0x1U)
#define I2S_FIFOCFG_ENABLETX_SHIFT               (0U)
/*! ENABLETX - Enable the transmit FIFO.
 *  0b0..The transmit FIFO is not enabled.
 *  0b1..The transmit FIFO is enabled.
 */
#define I2S_FIFOCFG_ENABLETX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLETX_SHIFT)) & I2S_FIFOCFG_ENABLETX_MASK)
#define I2S_FIFOCFG_ENABLERX_MASK                (0x2U)
#define I2S_FIFOCFG_ENABLERX_SHIFT               (1U)
/*! ENABLERX - Enable the receive FIFO.
 *  0b0..The receive FIFO is not enabled.
 *  0b1..The receive FIFO is enabled.
 */
#define I2S_FIFOCFG_ENABLERX(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_ENABLERX_SHIFT)) & I2S_FIFOCFG_ENABLERX_MASK)
#define I2S_FIFOCFG_TXI2SSE0_MASK                (0x4U)
#define I2S_FIFOCFG_TXI2SSE0_SHIFT               (2U)
/*! TXI2SSE0 - Transmit I2S empty 0. Determines the value sent by the I2S in transmit mode if the TX
 *    FIFO becomes empty. This value is sent repeatedly until the I2S is paused, the error is
 *    cleared, new data is provided, and the I2S is un-paused.
 *  0b0..If the TX FIFO becomes empty, the last value is sent. This setting may be used when the data length is 24
 *       bits or less, or when MONO = 1 for this channel pair.
 *  0b1..If the TX FIFO becomes empty, 0 is sent. Use if the data length is greater than 24 bits or if zero fill is preferred.
 */
#define I2S_FIFOCFG_TXI2SSE0(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_TXI2SSE0_SHIFT)) & I2S_FIFOCFG_TXI2SSE0_MASK)
#define I2S_FIFOCFG_PACK48_MASK                  (0x8U)
#define I2S_FIFOCFG_PACK48_SHIFT                 (3U)
/*! PACK48 - Packing format for 48-bit data. This relates to how data is entered into or taken from the FIFO by software or DMA.
 *  0b0..48-bit I2S FIFO entries are handled as all 24-bit values.
 *  0b1..48-bit I2S FIFO entries are handled as alternating 32-bit and 16-bit values.
 */
#define I2S_FIFOCFG_PACK48(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_PACK48_SHIFT)) & I2S_FIFOCFG_PACK48_MASK)
#define I2S_FIFOCFG_SIZE_MASK                    (0x30U)
#define I2S_FIFOCFG_SIZE_SHIFT                   (4U)
/*! SIZE - FIFO size configuration. This is a read-only field. 0x0 = FIFO is configured as 16
 *    entries of 8 bits. 0x1, 0x2, 0x3 = not applicable to USART.
 */
#define I2S_FIFOCFG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_SIZE_SHIFT)) & I2S_FIFOCFG_SIZE_MASK)
#define I2S_FIFOCFG_DMATX_MASK                   (0x1000U)
#define I2S_FIFOCFG_DMATX_SHIFT                  (12U)
/*! DMATX - DMA configuration for transmit.
 *  0b0..DMA is not used for the transmit function.
 *  0b1..Trigger DMA for the transmit function if the FIFO is not full. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define I2S_FIFOCFG_DMATX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMATX_SHIFT)) & I2S_FIFOCFG_DMATX_MASK)
#define I2S_FIFOCFG_DMARX_MASK                   (0x2000U)
#define I2S_FIFOCFG_DMARX_SHIFT                  (13U)
/*! DMARX - DMA configuration for receive.
 *  0b0..DMA is not used for the receive function.
 *  0b1..Trigger DMA for the receive function if the FIFO is not empty. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define I2S_FIFOCFG_DMARX(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_DMARX_SHIFT)) & I2S_FIFOCFG_DMARX_MASK)
#define I2S_FIFOCFG_WAKETX_MASK                  (0x4000U)
#define I2S_FIFOCFG_WAKETX_SHIFT                 (14U)
/*! WAKETX - Wake-up for transmit FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the transmit FIFO level reaches the value specified by TXLVL in
 *       FIFOTRIG, even when the TXLVL interrupt is not enabled.
 */
#define I2S_FIFOCFG_WAKETX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKETX_SHIFT)) & I2S_FIFOCFG_WAKETX_MASK)
#define I2S_FIFOCFG_WAKERX_MASK                  (0x8000U)
#define I2S_FIFOCFG_WAKERX_SHIFT                 (15U)
/*! WAKERX - Wake-up for receive FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the receive FIFO level reaches the value specified by RXLVL in
 *       FIFOTRIG, even when the RXLVL interrupt is not enabled.
 */
#define I2S_FIFOCFG_WAKERX(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_WAKERX_SHIFT)) & I2S_FIFOCFG_WAKERX_MASK)
#define I2S_FIFOCFG_EMPTYTX_MASK                 (0x10000U)
#define I2S_FIFOCFG_EMPTYTX_SHIFT                (16U)
/*! EMPTYTX - Empty command for the transmit FIFO. When a 1 is written to this bit, the TX FIFO is emptied.
 */
#define I2S_FIFOCFG_EMPTYTX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYTX_SHIFT)) & I2S_FIFOCFG_EMPTYTX_MASK)
#define I2S_FIFOCFG_EMPTYRX_MASK                 (0x20000U)
#define I2S_FIFOCFG_EMPTYRX_SHIFT                (17U)
/*! EMPTYRX - Empty command for the receive FIFO. When a 1 is written to this bit, the RX FIFO is emptied.
 */
#define I2S_FIFOCFG_EMPTYRX(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_EMPTYRX_SHIFT)) & I2S_FIFOCFG_EMPTYRX_MASK)
/*! @} */

/*! @name FIFOSTAT - FIFO status register. */
/*! @{ */
#define I2S_FIFOSTAT_TXERR_MASK                  (0x1U)
#define I2S_FIFOSTAT_TXERR_SHIFT                 (0U)
/*! TXERR - TX FIFO error. Will be set if a transmit FIFO error occurs. This could be an overflow
 *    caused by pushing data into a full FIFO, or by an underflow if the FIFO is empty when data is
 *    needed. Cleared by writing a 1 to this bit.
 */
#define I2S_FIFOSTAT_TXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXERR_SHIFT)) & I2S_FIFOSTAT_TXERR_MASK)
#define I2S_FIFOSTAT_RXERR_MASK                  (0x2U)
#define I2S_FIFOSTAT_RXERR_SHIFT                 (1U)
/*! RXERR - RX FIFO error. Will be set if a receive FIFO overflow occurs, caused by software or DMA
 *    not emptying the FIFO fast enough. Cleared by writing a 1 to this bit.
 */
#define I2S_FIFOSTAT_RXERR(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXERR_SHIFT)) & I2S_FIFOSTAT_RXERR_MASK)
#define I2S_FIFOSTAT_PERINT_MASK                 (0x8U)
#define I2S_FIFOSTAT_PERINT_SHIFT                (3U)
/*! PERINT - Peripheral interrupt. When 1, this indicates that the peripheral function has asserted
 *    an interrupt. The details can be found by reading the peripheral's STAT register.
 */
#define I2S_FIFOSTAT_PERINT(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_PERINT_SHIFT)) & I2S_FIFOSTAT_PERINT_MASK)
#define I2S_FIFOSTAT_TXEMPTY_MASK                (0x10U)
#define I2S_FIFOSTAT_TXEMPTY_SHIFT               (4U)
/*! TXEMPTY - Transmit FIFO empty. When 1, the transmit FIFO is empty. The peripheral may still be processing the last piece of data.
 */
#define I2S_FIFOSTAT_TXEMPTY(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXEMPTY_SHIFT)) & I2S_FIFOSTAT_TXEMPTY_MASK)
#define I2S_FIFOSTAT_TXNOTFULL_MASK              (0x20U)
#define I2S_FIFOSTAT_TXNOTFULL_SHIFT             (5U)
/*! TXNOTFULL - Transmit FIFO not full. When 1, the transmit FIFO is not full, so more data can be
 *    written. When 0, the transmit FIFO is full and another write would cause it to overflow.
 */
#define I2S_FIFOSTAT_TXNOTFULL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXNOTFULL_SHIFT)) & I2S_FIFOSTAT_TXNOTFULL_MASK)
#define I2S_FIFOSTAT_RXNOTEMPTY_MASK             (0x40U)
#define I2S_FIFOSTAT_RXNOTEMPTY_SHIFT            (6U)
/*! RXNOTEMPTY - Receive FIFO not empty. When 1, the receive FIFO is not empty, so data can be read. When 0, the receive FIFO is empty.
 */
#define I2S_FIFOSTAT_RXNOTEMPTY(x)               (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXNOTEMPTY_SHIFT)) & I2S_FIFOSTAT_RXNOTEMPTY_MASK)
#define I2S_FIFOSTAT_RXFULL_MASK                 (0x80U)
#define I2S_FIFOSTAT_RXFULL_SHIFT                (7U)
/*! RXFULL - Receive FIFO full. When 1, the receive FIFO is full. Data needs to be read out to
 *    prevent the peripheral from causing an overflow.
 */
#define I2S_FIFOSTAT_RXFULL(x)                   (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXFULL_SHIFT)) & I2S_FIFOSTAT_RXFULL_MASK)
#define I2S_FIFOSTAT_TXLVL_MASK                  (0x1F00U)
#define I2S_FIFOSTAT_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO current level. A 0 means the TX FIFO is currently empty, and the TXEMPTY
 *    and TXNOTFULL flags will be 1. Other values tell how much data is actually in the TX FIFO at
 *    the point where the read occurs. If the TX FIFO is full, the TXEMPTY and TXNOTFULL flags will be
 *    0.
 */
#define I2S_FIFOSTAT_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_TXLVL_SHIFT)) & I2S_FIFOSTAT_TXLVL_MASK)
#define I2S_FIFOSTAT_RXLVL_MASK                  (0x1F0000U)
#define I2S_FIFOSTAT_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO current level. A 0 means the RX FIFO is currently empty, and the RXFULL and
 *    RXNOTEMPTY flags will be 0. Other values tell how much data is actually in the RX FIFO at the
 *    point where the read occurs. If the RX FIFO is full, the RXFULL and RXNOTEMPTY flags will be
 *    1.
 */
#define I2S_FIFOSTAT_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOSTAT_RXLVL_SHIFT)) & I2S_FIFOSTAT_RXLVL_MASK)
/*! @} */

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
/*! @{ */
#define I2S_FIFOTRIG_TXLVLENA_MASK               (0x1U)
#define I2S_FIFOTRIG_TXLVLENA_SHIFT              (0U)
/*! TXLVLENA - Transmit FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMATX in FIFOCFG is set.
 *  0b0..Transmit FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the transmit FIFO level reaches the value specified by the TXLVL field in this register.
 */
#define I2S_FIFOTRIG_TXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVLENA_SHIFT)) & I2S_FIFOTRIG_TXLVLENA_MASK)
#define I2S_FIFOTRIG_RXLVLENA_MASK               (0x2U)
#define I2S_FIFOTRIG_RXLVLENA_SHIFT              (1U)
/*! RXLVLENA - Receive FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMARX in FIFOCFG is set.
 *  0b0..Receive FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the receive FIFO level reaches the value specified by the RXLVL field in this register.
 */
#define I2S_FIFOTRIG_RXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVLENA_SHIFT)) & I2S_FIFOTRIG_RXLVLENA_MASK)
#define I2S_FIFOTRIG_TXLVL_MASK                  (0xF00U)
#define I2S_FIFOTRIG_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO level trigger point. This field is used only when TXLVLENA = 1. If enabled
 *    to do so, the FIFO level can wake up the device just enough to perform DMA, then return to
 *    the reduced power mode. See Hardware Wake-up control register. 0 = trigger when the TX FIFO
 *    becomes empty. 1 = trigger when the TX FIFO level decreases to one entry. 15 = trigger when the TX
 *    FIFO level decreases to 15 entries (is no longer full).
 */
#define I2S_FIFOTRIG_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_TXLVL_SHIFT)) & I2S_FIFOTRIG_TXLVL_MASK)
#define I2S_FIFOTRIG_RXLVL_MASK                  (0xF0000U)
#define I2S_FIFOTRIG_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO level trigger point. The RX FIFO level is checked when a new piece of data
 *    is received. This field is used only when RXLVLENA = 1. If enabled to do so, the FIFO level
 *    can wake up the device just enough to perform DMA, then return to the reduced power mode. See
 *    Hardware Wake-up control register. 0 = trigger when the RX FIFO has received one entry (is no
 *    longer empty). 1 = trigger when the RX FIFO has received two entries. 15 = trigger when the RX
 *    FIFO has received 16 entries (has become full).
 */
#define I2S_FIFOTRIG_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOTRIG_RXLVL_SHIFT)) & I2S_FIFOTRIG_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
/*! @{ */
#define I2S_FIFOINTENSET_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENSET_TXERR_SHIFT             (0U)
/*! TXERR - Determines whether an interrupt occurs when a transmit error occurs, based on the TXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a transmit error.
 *  0b1..An interrupt will be generated when a transmit error occurs.
 */
#define I2S_FIFOINTENSET_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXERR_SHIFT)) & I2S_FIFOINTENSET_TXERR_MASK)
#define I2S_FIFOINTENSET_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENSET_RXERR_SHIFT             (1U)
/*! RXERR - Determines whether an interrupt occurs when a receive error occurs, based on the RXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a receive error.
 *  0b1..An interrupt will be generated when a receive error occurs.
 */
#define I2S_FIFOINTENSET_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXERR_SHIFT)) & I2S_FIFOINTENSET_RXERR_MASK)
#define I2S_FIFOINTENSET_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENSET_TXLVL_SHIFT             (2U)
/*! TXLVL - Determines whether an interrupt occurs when a the transmit FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the TX FIFO level.
 *  0b1..If TXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the TX FIFO level decreases
 *       to the level specified by TXLVL in the FIFOTRIG register.
 */
#define I2S_FIFOINTENSET_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_TXLVL_SHIFT)) & I2S_FIFOINTENSET_TXLVL_MASK)
#define I2S_FIFOINTENSET_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENSET_RXLVL_SHIFT             (3U)
/*! RXLVL - Determines whether an interrupt occurs when a the receive FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the RX FIFO level.
 *  0b1..If RXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the when the RX FIFO level
 *       increases to the level specified by RXLVL in the FIFOTRIG register.
 */
#define I2S_FIFOINTENSET_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENSET_RXLVL_SHIFT)) & I2S_FIFOINTENSET_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
/*! @{ */
#define I2S_FIFOINTENCLR_TXERR_MASK              (0x1U)
#define I2S_FIFOINTENCLR_TXERR_SHIFT             (0U)
/*! TXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define I2S_FIFOINTENCLR_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXERR_SHIFT)) & I2S_FIFOINTENCLR_TXERR_MASK)
#define I2S_FIFOINTENCLR_RXERR_MASK              (0x2U)
#define I2S_FIFOINTENCLR_RXERR_SHIFT             (1U)
/*! RXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define I2S_FIFOINTENCLR_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXERR_SHIFT)) & I2S_FIFOINTENCLR_RXERR_MASK)
#define I2S_FIFOINTENCLR_TXLVL_MASK              (0x4U)
#define I2S_FIFOINTENCLR_TXLVL_SHIFT             (2U)
/*! TXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define I2S_FIFOINTENCLR_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_TXLVL_SHIFT)) & I2S_FIFOINTENCLR_TXLVL_MASK)
#define I2S_FIFOINTENCLR_RXLVL_MASK              (0x8U)
#define I2S_FIFOINTENCLR_RXLVL_SHIFT             (3U)
/*! RXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define I2S_FIFOINTENCLR_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTENCLR_RXLVL_SHIFT)) & I2S_FIFOINTENCLR_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
/*! @{ */
#define I2S_FIFOINTSTAT_TXERR_MASK               (0x1U)
#define I2S_FIFOINTSTAT_TXERR_SHIFT              (0U)
/*! TXERR - TX FIFO error.
 */
#define I2S_FIFOINTSTAT_TXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXERR_SHIFT)) & I2S_FIFOINTSTAT_TXERR_MASK)
#define I2S_FIFOINTSTAT_RXERR_MASK               (0x2U)
#define I2S_FIFOINTSTAT_RXERR_SHIFT              (1U)
/*! RXERR - RX FIFO error.
 */
#define I2S_FIFOINTSTAT_RXERR(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXERR_SHIFT)) & I2S_FIFOINTSTAT_RXERR_MASK)
#define I2S_FIFOINTSTAT_TXLVL_MASK               (0x4U)
#define I2S_FIFOINTSTAT_TXLVL_SHIFT              (2U)
/*! TXLVL - Transmit FIFO level interrupt.
 */
#define I2S_FIFOINTSTAT_TXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_TXLVL_SHIFT)) & I2S_FIFOINTSTAT_TXLVL_MASK)
#define I2S_FIFOINTSTAT_RXLVL_MASK               (0x8U)
#define I2S_FIFOINTSTAT_RXLVL_SHIFT              (3U)
/*! RXLVL - Receive FIFO level interrupt.
 */
#define I2S_FIFOINTSTAT_RXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_RXLVL_SHIFT)) & I2S_FIFOINTSTAT_RXLVL_MASK)
#define I2S_FIFOINTSTAT_PERINT_MASK              (0x10U)
#define I2S_FIFOINTSTAT_PERINT_SHIFT             (4U)
/*! PERINT - Peripheral interrupt.
 */
#define I2S_FIFOINTSTAT_PERINT(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFOINTSTAT_PERINT_SHIFT)) & I2S_FIFOINTSTAT_PERINT_MASK)
/*! @} */

/*! @name FIFOWR - FIFO write data. */
/*! @{ */
#define I2S_FIFOWR_TXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFOWR_TXDATA_SHIFT                  (0U)
/*! TXDATA - Transmit data to the FIFO. The number of bits used depends on configuration details.
 */
#define I2S_FIFOWR_TXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR_TXDATA_SHIFT)) & I2S_FIFOWR_TXDATA_MASK)
/*! @} */

/*! @name FIFOWR48H - FIFO write data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */
#define I2S_FIFOWR48H_TXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFOWR48H_TXDATA_SHIFT               (0U)
/*! TXDATA - Transmit data to the FIFO. Whether this register is used and the number of bits used depends on configuration details.
 */
#define I2S_FIFOWR48H_TXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFOWR48H_TXDATA_SHIFT)) & I2S_FIFOWR48H_TXDATA_MASK)
/*! @} */

/*! @name FIFORD - FIFO read data. */
/*! @{ */
#define I2S_FIFORD_RXDATA_MASK                   (0xFFFFFFFFU)
#define I2S_FIFORD_RXDATA_SHIFT                  (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on configuration details.
 */
#define I2S_FIFORD_RXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD_RXDATA_SHIFT)) & I2S_FIFORD_RXDATA_MASK)
/*! @} */

/*! @name FIFORD48H - FIFO read data for upper data bits. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */
#define I2S_FIFORD48H_RXDATA_MASK                (0xFFFFFFU)
#define I2S_FIFORD48H_RXDATA_SHIFT               (0U)
/*! RXDATA - Received data from the FIFO. Whether this register is used and the number of bits used depends on configuration details.
 */
#define I2S_FIFORD48H_RXDATA(x)                  (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48H_RXDATA_SHIFT)) & I2S_FIFORD48H_RXDATA_MASK)
/*! @} */

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
/*! @{ */
#define I2S_FIFORDNOPOP_RXDATA_MASK              (0xFFFFFFFFU)
#define I2S_FIFORDNOPOP_RXDATA_SHIFT             (0U)
/*! RXDATA - Received data from the FIFO.
 */
#define I2S_FIFORDNOPOP_RXDATA(x)                (((uint32_t)(((uint32_t)(x)) << I2S_FIFORDNOPOP_RXDATA_SHIFT)) & I2S_FIFORDNOPOP_RXDATA_MASK)
/*! @} */

/*! @name FIFORD48HNOPOP - FIFO data read for upper data bits with no FIFO pop. May only be used if the I2S is configured for 2x 24-bit data and not using DMA. */
/*! @{ */
#define I2S_FIFORD48HNOPOP_RXDATA_MASK           (0xFFFFFFU)
#define I2S_FIFORD48HNOPOP_RXDATA_SHIFT          (0U)
/*! RXDATA - Received data from the FIFO. Whether this register is used and the number of bits used depends on configuration details.
 */
#define I2S_FIFORD48HNOPOP_RXDATA(x)             (((uint32_t)(((uint32_t)(x)) << I2S_FIFORD48HNOPOP_RXDATA_SHIFT)) & I2S_FIFORD48HNOPOP_RXDATA_MASK)
/*! @} */

/*! @name ID - I2S Module identification */
/*! @{ */
#define I2S_ID_Aperture_MASK                     (0xFFU)
#define I2S_ID_Aperture_SHIFT                    (0U)
/*! Aperture - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture.
 */
#define I2S_ID_Aperture(x)                       (((uint32_t)(((uint32_t)(x)) << I2S_ID_Aperture_SHIFT)) & I2S_ID_Aperture_MASK)
#define I2S_ID_Minor_Rev_MASK                    (0xF00U)
#define I2S_ID_Minor_Rev_SHIFT                   (8U)
/*! Minor_Rev - Minor revision of module implementation, starting at 0.
 */
#define I2S_ID_Minor_Rev(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_Minor_Rev_SHIFT)) & I2S_ID_Minor_Rev_MASK)
#define I2S_ID_Major_Rev_MASK                    (0xF000U)
#define I2S_ID_Major_Rev_SHIFT                   (12U)
/*! Major_Rev - Major revision of module implementation, starting at 0.
 */
#define I2S_ID_Major_Rev(x)                      (((uint32_t)(((uint32_t)(x)) << I2S_ID_Major_Rev_SHIFT)) & I2S_ID_Major_Rev_MASK)
#define I2S_ID_ID_MASK                           (0xFFFF0000U)
#define I2S_ID_ID_SHIFT                          (16U)
/*! ID - Unique module identifier for this IP block.
 */
#define I2S_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << I2S_ID_ID_SHIFT)) & I2S_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2S_Register_Masks */


/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base address */
#define I2S0_BASE                                (0x40097000u)
/** Peripheral I2S0 base pointer */
#define I2S0                                     ((I2S_Type *)I2S0_BASE)
/** Peripheral I2S1 base address */
#define I2S1_BASE                                (0x40098000u)
/** Peripheral I2S1 base pointer */
#define I2S1                                     ((I2S_Type *)I2S1_BASE)
/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           { I2S0_BASE, I2S1_BASE }
/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            { I2S0, I2S1 }
/** Interrupt vectors for the I2S peripheral type */
#define I2S_IRQS                                 { FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group I2S_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- INPUTMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Peripheral_Access_Layer INPUTMUX Peripheral Access Layer
 * @{
 */

/** INPUTMUX - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[192];
  __IO uint32_t PINTSEL[4];                        /**< Pin interrupt select register, array offset: 0xC0, array step: 0x4 */
       uint8_t RESERVED_1[16];
  __IO uint32_t DMA_ITRIG_INMUX[22];               /**< Trigger select register for DMA channel, array offset: 0xE0, array step: 0x4 */
       uint8_t RESERVED_2[40];
  __IO uint32_t DMA_OTRIG_INMUX[4];                /**< DMA output trigger selection to become DMA trigger, array offset: 0x160, array step: 0x4 */
       uint8_t RESERVED_3[16];
  __IO uint32_t FREQMEAS_REF;                      /**< Selection for frequency measurement reference clock, offset: 0x180 */
  __IO uint32_t FREQMEAS_TARGET;                   /**< Selection for frequency measurement target clock, offset: 0x184 */
} INPUTMUX_Type;

/* ----------------------------------------------------------------------------
   -- INPUTMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Register_Masks INPUTMUX Register Masks
 * @{
 */

/*! @name PINTSEL - Pin interrupt select register */
/*! @{ */
#define INPUTMUX_PINTSEL_INTPIN_MASK             (0xFFU)
#define INPUTMUX_PINTSEL_INTPIN_SHIFT            (0U)
/*! INTPIN - Pin number select for pin interrupt or pattern match engine input. (PIO0_0 to PIO1_31 correspond to numbers 0 to 63).
 */
#define INPUTMUX_PINTSEL_INTPIN(x)               (((uint32_t)(((uint32_t)(x)) << INPUTMUX_PINTSEL_INTPIN_SHIFT)) & INPUTMUX_PINTSEL_INTPIN_MASK)
/*! @} */

/* The count of INPUTMUX_PINTSEL */
#define INPUTMUX_PINTSEL_COUNT                   (4U)

/*! @name DMA_ITRIG_INMUX - Trigger select register for DMA channel */
/*! @{ */
#define INPUTMUX_DMA_ITRIG_INMUX_INP_MASK        (0x1FU)
#define INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT       (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 21). 0 = ADC0 Sequence A
 *    interrupt 1 = ADC0 Sequence B interrupt 2 = SCT0 DMA request 0 3 = SCT0 DMA request 1 4 =
 *    Timer CTIMER0 Match 0 5 = Timer CTIMER0 Match 1 6 = Timer CTIMER1 Match 0 7 = RESERVED 8 =
 *    RESERVED 9 = Timer CTIMER3 Match 0 10 = RESERVED 11 = RESERVED 12 = Pin interrupt 0 13 = Pin
 *    interrupt 1 14 = Pin interrupt 2 15 = Pin interrupt 3 16 = DMA output trigger mux 0 17 = DMA output
 *    trigger mux 1 18 = DMA output trigger mux 2 19 = DMA output trigger mux 3
 */
#define INPUTMUX_DMA_ITRIG_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA_ITRIG_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_DMA_ITRIG_INMUX */
#define INPUTMUX_DMA_ITRIG_INMUX_COUNT           (22U)

/*! @name DMA_OTRIG_INMUX - DMA output trigger selection to become DMA trigger */
/*! @{ */
#define INPUTMUX_DMA_OTRIG_INMUX_INP_MASK        (0x1FU)
#define INPUTMUX_DMA_OTRIG_INMUX_INP_SHIFT       (0U)
/*! INP - DMA trigger output number (decimal value) for DMA channel n (n = 0 to 19).
 */
#define INPUTMUX_DMA_OTRIG_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_OTRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA_OTRIG_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_DMA_OTRIG_INMUX */
#define INPUTMUX_DMA_OTRIG_INMUX_COUNT           (4U)

/*! @name FREQMEAS_REF - Selection for frequency measurement reference clock */
/*! @{ */
#define INPUTMUX_FREQMEAS_REF_CLKIN_MASK         (0x1FU)
#define INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT        (0U)
/*! CLKIN - Clock source number (decimal value) for frequency measure function target clock: 0 =
 *    CLK_IN 1 = FRO 12 MHz oscillator 2 = Watchdog oscillator 3 = 32 kHz RTC oscillator 4 = Main clock
 *    (see Section 4.5.23) 5 = PIO0_4 6 = PIO0_20 7 = PIO0_24 8 = PIO1_4
 */
#define INPUTMUX_FREQMEAS_REF_CLKIN(x)           (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_REF_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_REF_CLKIN_MASK)
/*! @} */

/*! @name FREQMEAS_TARGET - Selection for frequency measurement target clock */
/*! @{ */
#define INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK      (0x1FU)
#define INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT     (0U)
/*! CLKIN - Clock source number (decimal value) for frequency measure function target clock: 0 =
 *    CLK_IN 1 = FRO 12 MHz oscillator 2 = Watchdog oscillator 3 = 32 kHz RTC oscillator 4 = Main clock
 *    (see Section 4.5.23) 5 = PIO0_4 6 = PIO0_20 7 = PIO0_24 8 = PIO1_4
 */
#define INPUTMUX_FREQMEAS_TARGET_CLKIN(x)        (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FREQMEAS_TARGET_CLKIN_SHIFT)) & INPUTMUX_FREQMEAS_TARGET_CLKIN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group INPUTMUX_Register_Masks */


/* INPUTMUX - Peripheral instance base addresses */
/** Peripheral INPUTMUX base address */
#define INPUTMUX_BASE                            (0x40005000u)
/** Peripheral INPUTMUX base pointer */
#define INPUTMUX                                 ((INPUTMUX_Type *)INPUTMUX_BASE)
/** Array initializer of INPUTMUX peripheral base addresses */
#define INPUTMUX_BASE_ADDRS                      { INPUTMUX_BASE }
/** Array initializer of INPUTMUX peripheral base pointers */
#define INPUTMUX_BASE_PTRS                       { INPUTMUX }

/*!
 * @}
 */ /* end of group INPUTMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- IOCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Peripheral_Access_Layer IOCON Peripheral Access Layer
 * @{
 */

/** IOCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t PIO[2][32];                        /**< Digital I/O control for port 0 pins PIO0_0..Digital I/O control for port 1 pins PIO1_31, array offset: 0x0, array step: index*0x80, index2*0x4 */
} IOCON_Type;

/* ----------------------------------------------------------------------------
   -- IOCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Register_Masks IOCON Register Masks
 * @{
 */

/*! @name PIO - Digital I/O control for port 0 pins PIO0_0..Digital I/O control for port 1 pins PIO1_31 */
/*! @{ */
#define IOCON_PIO_FUNC_MASK                      (0x7U)
#define IOCON_PIO_FUNC_SHIFT                     (0U)
/*! FUNC - Selects pin function.
 *  0b000..Alternative connection 0.
 *  0b001..Alternative connection 1.
 *  0b010..Alternative connection 2.
 *  0b011..Alternative connection 3.
 *  0b100..Alternative connection 4.
 *  0b101..Alternative connection 5.
 *  0b110..Alternative connection 6.
 *  0b111..Alternative connection 7.
 */
#define IOCON_PIO_FUNC(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_FUNC_SHIFT)) & IOCON_PIO_FUNC_MASK)
#define IOCON_PIO_MODE_MASK                      (0x18U)
#define IOCON_PIO_MODE_SHIFT                     (3U)
/*! MODE - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)
#define IOCON_PIO_I2CSLEW_MASK                   (0x20U)
#define IOCON_PIO_I2CSLEW_SHIFT                  (5U)
/*! I2CSLEW - Controls slew rate of I2C pin.
 *  0b0..I2C mode.
 *  0b1..GPIO mode.
 */
#define IOCON_PIO_I2CSLEW(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CSLEW_SHIFT)) & IOCON_PIO_I2CSLEW_MASK)
#define IOCON_PIO_INVERT_MASK                    (0x40U)
#define IOCON_PIO_INVERT_SHIFT                   (6U)
/*! INVERT - Input polarity.
 *  0b0..Disabled. Input function is not inverted.
 *  0b1..Enabled. Input is function inverted.
 */
#define IOCON_PIO_INVERT(x)                      (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_INVERT_SHIFT)) & IOCON_PIO_INVERT_MASK)
#define IOCON_PIO_DIGIMODE_MASK                  (0x80U)
#define IOCON_PIO_DIGIMODE_SHIFT                 (7U)
/*! DIGIMODE - Select Analog/Digital mode.
 *  0b0..Analog mode.
 *  0b1..Digital mode.
 */
#define IOCON_PIO_DIGIMODE(x)                    (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_DIGIMODE_SHIFT)) & IOCON_PIO_DIGIMODE_MASK)
#define IOCON_PIO_FILTEROFF_MASK                 (0x100U)
#define IOCON_PIO_FILTEROFF_SHIFT                (8U)
/*! FILTEROFF - Controls input glitch filter.
 *  0b0..Filter enabled. Noise pulses below approximately 10 ns are filtered out.
 *  0b1..Filter disabled. No input filtering is done.
 */
#define IOCON_PIO_FILTEROFF(x)                   (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_FILTEROFF_SHIFT)) & IOCON_PIO_FILTEROFF_MASK)
#define IOCON_PIO_I2CDRIVE_MASK                  (0x200U)
#define IOCON_PIO_I2CDRIVE_SHIFT                 (9U)
/*! I2CDRIVE - Controls the current sink capability of the pin.
 *  0b0..Low drive. Output drive sink is 4 mA. This is sufficient for standard and fast mode I2C.
 *  0b1..High drive. Output drive sink is 20 mA. This is needed for Fast Mode Plus I 2C. Refer to the appropriate
 *       specific device data sheet for details.
 */
#define IOCON_PIO_I2CDRIVE(x)                    (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CDRIVE_SHIFT)) & IOCON_PIO_I2CDRIVE_MASK)
#define IOCON_PIO_SLEW_MASK                      (0x200U)
#define IOCON_PIO_SLEW_SHIFT                     (9U)
/*! SLEW - Driver slew rate.
 *  0b0..Standard mode, output slew rate control is enabled. More outputs can be switched simultaneously.
 *  0b1..Fast mode, slew rate control is disabled. Refer to the appropriate specific device data sheet for details.
 */
#define IOCON_PIO_SLEW(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_SLEW_SHIFT)) & IOCON_PIO_SLEW_MASK)
#define IOCON_PIO_I2CFILTER_MASK                 (0x400U)
#define IOCON_PIO_I2CFILTER_SHIFT                (10U)
/*! I2CFILTER - Configures I2C features for standard mode, fast mode, and Fast Mode Plus operation.
 *  0b0..Enabled. I2C 50 ns glitch filter enabled.
 *  0b1..Disabled. I2C 50 ns glitch filter disabled.
 */
#define IOCON_PIO_I2CFILTER(x)                   (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CFILTER_SHIFT)) & IOCON_PIO_I2CFILTER_MASK)
#define IOCON_PIO_OD_MASK                        (0x400U)
#define IOCON_PIO_OD_SHIFT                       (10U)
/*! OD - Controls open-drain mode.
 *  0b0..Normal. Normal push-pull output
 *  0b1..Open-drain. Simulated open-drain output (high drive disabled).
 */
#define IOCON_PIO_OD(x)                          (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)
/*! @} */

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT                          (2U)

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT2                         (32U)


/*!
 * @}
 */ /* end of group IOCON_Register_Masks */


/* IOCON - Peripheral instance base addresses */
/** Peripheral IOCON base address */
#define IOCON_BASE                               (0x40001000u)
/** Peripheral IOCON base pointer */
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)
/** Array initializer of IOCON peripheral base addresses */
#define IOCON_BASE_ADDRS                         { IOCON_BASE }
/** Array initializer of IOCON peripheral base pointers */
#define IOCON_BASE_PTRS                          { IOCON }

/*!
 * @}
 */ /* end of group IOCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MRT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MRT_Peripheral_Access_Layer MRT Peripheral Access Layer
 * @{
 */

/** MRT - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x10 */
    __IO uint32_t INTVAL;                            /**< MRT Time interval value register. This value is loaded into the TIMER register., array offset: 0x0, array step: 0x10 */
    __I  uint32_t TIMER;                             /**< MRT Timer register. This register reads the value of the down-counter., array offset: 0x4, array step: 0x10 */
    __IO uint32_t CTRL;                              /**< MRT Control register. This register controls the MRT modes., array offset: 0x8, array step: 0x10 */
    __IO uint32_t STAT;                              /**< MRT Status register., array offset: 0xC, array step: 0x10 */
  } CHANNEL[4];
       uint8_t RESERVED_0[176];
  __IO uint32_t MODCFG;                            /**< Module Configuration register. This register provides information about this particular MRT instance, and allows choosing an overall mode for the idle channel feature., offset: 0xF0 */
  __I  uint32_t IDLE_CH;                           /**< Idle channel register. This register returns the number of the first idle channel., offset: 0xF4 */
  __IO uint32_t IRQ_FLAG;                          /**< Global interrupt flag register, offset: 0xF8 */
} MRT_Type;

/* ----------------------------------------------------------------------------
   -- MRT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MRT_Register_Masks MRT Register Masks
 * @{
 */

/*! @name CHANNEL_INTVAL - MRT Time interval value register. This value is loaded into the TIMER register. */
/*! @{ */
#define MRT_CHANNEL_INTVAL_IVALUE_MASK           (0xFFFFFFU)
#define MRT_CHANNEL_INTVAL_IVALUE_SHIFT          (0U)
/*! IVALUE - Time interval load value. This value is loaded into the TIMERn register and the MRT
 *    channel n starts counting down from IVALUE -1. If the timer is idle, writing a non-zero value to
 *    this bit field starts the timer immediately. If the timer is running, writing a zero to this
 *    bit field does the following: If LOAD = 1, the timer stops immediately. If LOAD = 0, the timer
 *    stops at the end of the time interval.
 */
#define MRT_CHANNEL_INTVAL_IVALUE(x)             (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_INTVAL_IVALUE_SHIFT)) & MRT_CHANNEL_INTVAL_IVALUE_MASK)
#define MRT_CHANNEL_INTVAL_LOAD_MASK             (0x80000000U)
#define MRT_CHANNEL_INTVAL_LOAD_SHIFT            (31U)
/*! LOAD - Determines how the timer interval value IVALUE -1 is loaded into the TIMERn register.
 *    This bit is write-only. Reading this bit always returns 0.
 *  0b0..No force load. The load from the INTVALn register to the TIMERn register is processed at the end of the
 *       time interval if the repeat mode is selected.
 *  0b1..Force load. The INTVALn interval value IVALUE -1 is immediately loaded into the TIMERn register while TIMERn is running.
 */
#define MRT_CHANNEL_INTVAL_LOAD(x)               (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_INTVAL_LOAD_SHIFT)) & MRT_CHANNEL_INTVAL_LOAD_MASK)
/*! @} */

/* The count of MRT_CHANNEL_INTVAL */
#define MRT_CHANNEL_INTVAL_COUNT                 (4U)

/*! @name CHANNEL_TIMER - MRT Timer register. This register reads the value of the down-counter. */
/*! @{ */
#define MRT_CHANNEL_TIMER_VALUE_MASK             (0xFFFFFFU)
#define MRT_CHANNEL_TIMER_VALUE_SHIFT            (0U)
/*! VALUE - Holds the current timer value of the down-counter. The initial value of the TIMERn
 *    register is loaded as IVALUE - 1 from the INTVALn register either at the end of the time interval
 *    or immediately in the following cases: INTVALn register is updated in the idle state. INTVALn
 *    register is updated with LOAD = 1. When the timer is in idle state, reading this bit fields
 *    returns -1 (0x00FF FFFF).
 */
#define MRT_CHANNEL_TIMER_VALUE(x)               (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_TIMER_VALUE_SHIFT)) & MRT_CHANNEL_TIMER_VALUE_MASK)
/*! @} */

/* The count of MRT_CHANNEL_TIMER */
#define MRT_CHANNEL_TIMER_COUNT                  (4U)

/*! @name CHANNEL_CTRL - MRT Control register. This register controls the MRT modes. */
/*! @{ */
#define MRT_CHANNEL_CTRL_INTEN_MASK              (0x1U)
#define MRT_CHANNEL_CTRL_INTEN_SHIFT             (0U)
/*! INTEN - Enable the TIMERn interrupt.
 *  0b0..Disabled. TIMERn interrupt is disabled.
 *  0b1..Enabled. TIMERn interrupt is enabled.
 */
#define MRT_CHANNEL_CTRL_INTEN(x)                (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_CTRL_INTEN_SHIFT)) & MRT_CHANNEL_CTRL_INTEN_MASK)
#define MRT_CHANNEL_CTRL_MODE_MASK               (0x6U)
#define MRT_CHANNEL_CTRL_MODE_SHIFT              (1U)
/*! MODE - Selects timer mode.
 *  0b00..Repeat interrupt mode.
 *  0b01..One-shot interrupt mode.
 *  0b10..One-shot stall mode.
 *  0b11..Reserved.
 */
#define MRT_CHANNEL_CTRL_MODE(x)                 (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_CTRL_MODE_SHIFT)) & MRT_CHANNEL_CTRL_MODE_MASK)
/*! @} */

/* The count of MRT_CHANNEL_CTRL */
#define MRT_CHANNEL_CTRL_COUNT                   (4U)

/*! @name CHANNEL_STAT - MRT Status register. */
/*! @{ */
#define MRT_CHANNEL_STAT_INTFLAG_MASK            (0x1U)
#define MRT_CHANNEL_STAT_INTFLAG_SHIFT           (0U)
/*! INTFLAG - Monitors the interrupt flag.
 *  0b0..No pending interrupt. Writing a zero is equivalent to no operation.
 *  0b1..Pending interrupt. The interrupt is pending because TIMERn has reached the end of the time interval. If
 *       the INTEN bit in the CONTROLn is also set to 1, the interrupt for timer channel n and the global interrupt
 *       are raised. Writing a 1 to this bit clears the interrupt request.
 */
#define MRT_CHANNEL_STAT_INTFLAG(x)              (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_INTFLAG_SHIFT)) & MRT_CHANNEL_STAT_INTFLAG_MASK)
#define MRT_CHANNEL_STAT_RUN_MASK                (0x2U)
#define MRT_CHANNEL_STAT_RUN_SHIFT               (1U)
/*! RUN - Indicates the state of TIMERn. This bit is read-only.
 *  0b0..Idle state. TIMERn is stopped.
 *  0b1..Running. TIMERn is running.
 */
#define MRT_CHANNEL_STAT_RUN(x)                  (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_RUN_SHIFT)) & MRT_CHANNEL_STAT_RUN_MASK)
#define MRT_CHANNEL_STAT_INUSE_MASK              (0x4U)
#define MRT_CHANNEL_STAT_INUSE_SHIFT             (2U)
/*! INUSE - Channel In Use flag. Operating details depend on the MULTITASK bit in the MODCFG
 *    register, and affects the use of IDLE_CH. See Idle channel register for details of the two operating
 *    modes.
 *  0b0..This channel is not in use.
 *  0b1..This channel is in use.
 */
#define MRT_CHANNEL_STAT_INUSE(x)                (((uint32_t)(((uint32_t)(x)) << MRT_CHANNEL_STAT_INUSE_SHIFT)) & MRT_CHANNEL_STAT_INUSE_MASK)
/*! @} */

/* The count of MRT_CHANNEL_STAT */
#define MRT_CHANNEL_STAT_COUNT                   (4U)

/*! @name MODCFG - Module Configuration register. This register provides information about this particular MRT instance, and allows choosing an overall mode for the idle channel feature. */
/*! @{ */
#define MRT_MODCFG_NOC_MASK                      (0xFU)
#define MRT_MODCFG_NOC_SHIFT                     (0U)
/*! NOC - Identifies the number of channels in this MRT.(4 channels on this device.)
 */
#define MRT_MODCFG_NOC(x)                        (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_NOC_SHIFT)) & MRT_MODCFG_NOC_MASK)
#define MRT_MODCFG_NOB_MASK                      (0x1F0U)
#define MRT_MODCFG_NOB_SHIFT                     (4U)
/*! NOB - Identifies the number of timer bits in this MRT. (24 bits wide on this device.)
 */
#define MRT_MODCFG_NOB(x)                        (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_NOB_SHIFT)) & MRT_MODCFG_NOB_MASK)
#define MRT_MODCFG_MULTITASK_MASK                (0x80000000U)
#define MRT_MODCFG_MULTITASK_SHIFT               (31U)
/*! MULTITASK - Selects the operating mode for the INUSE flags and the IDLE_CH register.
 *  0b0..Hardware status mode. In this mode, the INUSE(n) flags for all channels are reset.
 *  0b1..Multi-task mode.
 */
#define MRT_MODCFG_MULTITASK(x)                  (((uint32_t)(((uint32_t)(x)) << MRT_MODCFG_MULTITASK_SHIFT)) & MRT_MODCFG_MULTITASK_MASK)
/*! @} */

/*! @name IDLE_CH - Idle channel register. This register returns the number of the first idle channel. */
/*! @{ */
#define MRT_IDLE_CH_CHAN_MASK                    (0xF0U)
#define MRT_IDLE_CH_CHAN_SHIFT                   (4U)
/*! CHAN - Idle channel. Reading the CHAN bits, returns the lowest idle timer channel. The number is
 *    positioned such that it can be used as an offset from the MRT base address in order to access
 *    the registers for the allocated channel. If all timer channels are running, CHAN = 0xF. See
 *    text above for more details.
 */
#define MRT_IDLE_CH_CHAN(x)                      (((uint32_t)(((uint32_t)(x)) << MRT_IDLE_CH_CHAN_SHIFT)) & MRT_IDLE_CH_CHAN_MASK)
/*! @} */

/*! @name IRQ_FLAG - Global interrupt flag register */
/*! @{ */
#define MRT_IRQ_FLAG_GFLAG0_MASK                 (0x1U)
#define MRT_IRQ_FLAG_GFLAG0_SHIFT                (0U)
/*! GFLAG0 - Monitors the interrupt flag of TIMER0.
 *  0b0..No pending interrupt. Writing a zero is equivalent to no operation.
 *  0b1..Pending interrupt. The interrupt is pending because TIMER0 has reached the end of the time interval. If
 *       the INTEN bit in the CONTROL0 register is also set to 1, the interrupt for timer channel 0 and the global
 *       interrupt are raised. Writing a 1 to this bit clears the interrupt request.
 */
#define MRT_IRQ_FLAG_GFLAG0(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG0_SHIFT)) & MRT_IRQ_FLAG_GFLAG0_MASK)
#define MRT_IRQ_FLAG_GFLAG1_MASK                 (0x2U)
#define MRT_IRQ_FLAG_GFLAG1_SHIFT                (1U)
/*! GFLAG1 - Monitors the interrupt flag of TIMER1. See description of channel 0.
 */
#define MRT_IRQ_FLAG_GFLAG1(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG1_SHIFT)) & MRT_IRQ_FLAG_GFLAG1_MASK)
#define MRT_IRQ_FLAG_GFLAG2_MASK                 (0x4U)
#define MRT_IRQ_FLAG_GFLAG2_SHIFT                (2U)
/*! GFLAG2 - Monitors the interrupt flag of TIMER2. See description of channel 0.
 */
#define MRT_IRQ_FLAG_GFLAG2(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG2_SHIFT)) & MRT_IRQ_FLAG_GFLAG2_MASK)
#define MRT_IRQ_FLAG_GFLAG3_MASK                 (0x8U)
#define MRT_IRQ_FLAG_GFLAG3_SHIFT                (3U)
/*! GFLAG3 - Monitors the interrupt flag of TIMER3. See description of channel 0.
 */
#define MRT_IRQ_FLAG_GFLAG3(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG3_SHIFT)) & MRT_IRQ_FLAG_GFLAG3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MRT_Register_Masks */


/* MRT - Peripheral instance base addresses */
/** Peripheral MRT0 base address */
#define MRT0_BASE                                (0x4000D000u)
/** Peripheral MRT0 base pointer */
#define MRT0                                     ((MRT_Type *)MRT0_BASE)
/** Array initializer of MRT peripheral base addresses */
#define MRT_BASE_ADDRS                           { MRT0_BASE }
/** Array initializer of MRT peripheral base pointers */
#define MRT_BASE_PTRS                            { MRT0 }
/** Interrupt vectors for the MRT peripheral type */
#define MRT_IRQS                                 { MRT0_IRQn }

/*!
 * @}
 */ /* end of group MRT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PINT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PINT_Peripheral_Access_Layer PINT Peripheral Access Layer
 * @{
 */

/** PINT - Register Layout Typedef */
typedef struct {
  __IO uint32_t ISEL;                              /**< Pin Interrupt Mode register, offset: 0x0 */
  __IO uint32_t IENR;                              /**< Pin interrupt level or rising edge interrupt enable register, offset: 0x4 */
  __O  uint32_t SIENR;                             /**< Pin interrupt level or rising edge interrupt set register, offset: 0x8 */
  __O  uint32_t CIENR;                             /**< Pin interrupt level (rising edge interrupt) clear register, offset: 0xC */
  __IO uint32_t IENF;                              /**< Pin interrupt active level or falling edge interrupt enable register, offset: 0x10 */
  __O  uint32_t SIENF;                             /**< Pin interrupt active level or falling edge interrupt set register, offset: 0x14 */
  __O  uint32_t CIENF;                             /**< Pin interrupt active level or falling edge interrupt clear register, offset: 0x18 */
  __IO uint32_t RISE;                              /**< Pin interrupt rising edge register, offset: 0x1C */
  __IO uint32_t FALL;                              /**< Pin interrupt falling edge register, offset: 0x20 */
  __IO uint32_t IST;                               /**< Pin interrupt status register, offset: 0x24 */
  __IO uint32_t PMCTRL;                            /**< Pattern match interrupt control register, offset: 0x28 */
  __IO uint32_t PMSRC;                             /**< Pattern match interrupt bit-slice source register, offset: 0x2C */
  __IO uint32_t PMCFG;                             /**< Pattern match interrupt bit slice configuration register, offset: 0x30 */
} PINT_Type;

/* ----------------------------------------------------------------------------
   -- PINT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PINT_Register_Masks PINT Register Masks
 * @{
 */

/*! @name ISEL - Pin Interrupt Mode register */
/*! @{ */
#define PINT_ISEL_PMODE_MASK                     (0xFFU)
#define PINT_ISEL_PMODE_SHIFT                    (0U)
/*! PMODE - Selects the interrupt mode for each pin interrupt. Bit n configures the pin interrupt
 *    selected in PINTSELn. 0 = Edge sensitive 1 = Level sensitive
 */
#define PINT_ISEL_PMODE(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_ISEL_PMODE_SHIFT)) & PINT_ISEL_PMODE_MASK)
/*! @} */

/*! @name IENR - Pin interrupt level or rising edge interrupt enable register */
/*! @{ */
#define PINT_IENR_ENRL_MASK                      (0xFFU)
#define PINT_IENR_ENRL_SHIFT                     (0U)
/*! ENRL - Enables the rising edge or level interrupt for each pin interrupt. Bit n configures the
 *    pin interrupt selected in PINTSELn. 0 = Disable rising edge or level interrupt. 1 = Enable
 *    rising edge or level interrupt.
 */
#define PINT_IENR_ENRL(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IENR_ENRL_SHIFT)) & PINT_IENR_ENRL_MASK)
/*! @} */

/*! @name SIENR - Pin interrupt level or rising edge interrupt set register */
/*! @{ */
#define PINT_SIENR_SETENRL_MASK                  (0xFFU)
#define PINT_SIENR_SETENRL_SHIFT                 (0U)
/*! SETENRL - Ones written to this address set bits in the IENR, thus enabling interrupts. Bit n
 *    sets bit n in the IENR register. 0 = No operation. 1 = Enable rising edge or level interrupt.
 */
#define PINT_SIENR_SETENRL(x)                    (((uint32_t)(((uint32_t)(x)) << PINT_SIENR_SETENRL_SHIFT)) & PINT_SIENR_SETENRL_MASK)
/*! @} */

/*! @name CIENR - Pin interrupt level (rising edge interrupt) clear register */
/*! @{ */
#define PINT_CIENR_CENRL_MASK                    (0xFFU)
#define PINT_CIENR_CENRL_SHIFT                   (0U)
/*! CENRL - Ones written to this address clear bits in the IENR, thus disabling the interrupts. Bit
 *    n clears bit n in the IENR register. 0 = No operation. 1 = Disable rising edge or level
 *    interrupt.
 */
#define PINT_CIENR_CENRL(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_CIENR_CENRL_SHIFT)) & PINT_CIENR_CENRL_MASK)
/*! @} */

/*! @name IENF - Pin interrupt active level or falling edge interrupt enable register */
/*! @{ */
#define PINT_IENF_ENAF_MASK                      (0xFFU)
#define PINT_IENF_ENAF_SHIFT                     (0U)
/*! ENAF - Enables the falling edge or configures the active level interrupt for each pin interrupt.
 *    Bit n configures the pin interrupt selected in PINTSELn. 0 = Disable falling edge interrupt
 *    or set active interrupt level LOW. 1 = Enable falling edge interrupt enabled or set active
 *    interrupt level HIGH.
 */
#define PINT_IENF_ENAF(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IENF_ENAF_SHIFT)) & PINT_IENF_ENAF_MASK)
/*! @} */

/*! @name SIENF - Pin interrupt active level or falling edge interrupt set register */
/*! @{ */
#define PINT_SIENF_SETENAF_MASK                  (0xFFU)
#define PINT_SIENF_SETENAF_SHIFT                 (0U)
/*! SETENAF - Ones written to this address set bits in the IENF, thus enabling interrupts. Bit n
 *    sets bit n in the IENF register. 0 = No operation. 1 = Select HIGH-active interrupt or enable
 *    falling edge interrupt.
 */
#define PINT_SIENF_SETENAF(x)                    (((uint32_t)(((uint32_t)(x)) << PINT_SIENF_SETENAF_SHIFT)) & PINT_SIENF_SETENAF_MASK)
/*! @} */

/*! @name CIENF - Pin interrupt active level or falling edge interrupt clear register */
/*! @{ */
#define PINT_CIENF_CENAF_MASK                    (0xFFU)
#define PINT_CIENF_CENAF_SHIFT                   (0U)
/*! CENAF - Ones written to this address clears bits in the IENF, thus disabling interrupts. Bit n
 *    clears bit n in the IENF register. 0 = No operation. 1 = LOW-active interrupt selected or
 *    falling edge interrupt disabled.
 */
#define PINT_CIENF_CENAF(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_CIENF_CENAF_SHIFT)) & PINT_CIENF_CENAF_MASK)
/*! @} */

/*! @name RISE - Pin interrupt rising edge register */
/*! @{ */
#define PINT_RISE_RDET_MASK                      (0xFFU)
#define PINT_RISE_RDET_SHIFT                     (0U)
/*! RDET - Rising edge detect. Bit n detects the rising edge of the pin selected in PINTSELn. Read
 *    0: No rising edge has been detected on this pin since Reset or the last time a one was written
 *    to this bit. Write 0: no operation. Read 1: a rising edge has been detected since Reset or the
 *    last time a one was written to this bit. Write 1: clear rising edge detection for this pin.
 */
#define PINT_RISE_RDET(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_RISE_RDET_SHIFT)) & PINT_RISE_RDET_MASK)
/*! @} */

/*! @name FALL - Pin interrupt falling edge register */
/*! @{ */
#define PINT_FALL_FDET_MASK                      (0xFFU)
#define PINT_FALL_FDET_SHIFT                     (0U)
/*! FDET - Falling edge detect. Bit n detects the falling edge of the pin selected in PINTSELn. Read
 *    0: No falling edge has been detected on this pin since Reset or the last time a one was
 *    written to this bit. Write 0: no operation. Read 1: a falling edge has been detected since Reset or
 *    the last time a one was written to this bit. Write 1: clear falling edge detection for this
 *    pin.
 */
#define PINT_FALL_FDET(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_FALL_FDET_SHIFT)) & PINT_FALL_FDET_MASK)
/*! @} */

/*! @name IST - Pin interrupt status register */
/*! @{ */
#define PINT_IST_PSTAT_MASK                      (0xFFU)
#define PINT_IST_PSTAT_SHIFT                     (0U)
/*! PSTAT - Pin interrupt status. Bit n returns the status, clears the edge interrupt, or inverts
 *    the active level of the pin selected in PINTSELn. Read 0: interrupt is not being requested for
 *    this interrupt pin. Write 0: no operation. Read 1: interrupt is being requested for this
 *    interrupt pin. Write 1 (edge-sensitive): clear rising- and falling-edge detection for this pin.
 *    Write 1 (level-sensitive): switch the active level for this pin (in the IENF register).
 */
#define PINT_IST_PSTAT(x)                        (((uint32_t)(((uint32_t)(x)) << PINT_IST_PSTAT_SHIFT)) & PINT_IST_PSTAT_MASK)
/*! @} */

/*! @name PMCTRL - Pattern match interrupt control register */
/*! @{ */
#define PINT_PMCTRL_SEL_PMATCH_MASK              (0x1U)
#define PINT_PMCTRL_SEL_PMATCH_SHIFT             (0U)
/*! SEL_PMATCH - Specifies whether the 8 pin interrupts are controlled by the pin interrupt function or by the pattern match function.
 *  0b0..Pin interrupt. Interrupts are driven in response to the standard pin interrupt function.
 *  0b1..Pattern match. Interrupts are driven in response to pattern matches.
 */
#define PINT_PMCTRL_SEL_PMATCH(x)                (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_SEL_PMATCH_SHIFT)) & PINT_PMCTRL_SEL_PMATCH_MASK)
#define PINT_PMCTRL_ENA_RXEV_MASK                (0x2U)
#define PINT_PMCTRL_ENA_RXEV_SHIFT               (1U)
/*! ENA_RXEV - Enables the RXEV output to the CPU and/or to a GPIO output when the specified boolean expression evaluates to true.
 *  0b0..Disabled. RXEV output to the CPU is disabled.
 *  0b1..Enabled. RXEV output to the CPU is enabled.
 */
#define PINT_PMCTRL_ENA_RXEV(x)                  (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_ENA_RXEV_SHIFT)) & PINT_PMCTRL_ENA_RXEV_MASK)
#define PINT_PMCTRL_PMAT_MASK                    (0xFF000000U)
#define PINT_PMCTRL_PMAT_SHIFT                   (24U)
/*! PMAT - This field displays the current state of pattern matches. A 1 in any bit of this field
 *    indicates that the corresponding product term is matched by the current state of the appropriate
 *    inputs.
 */
#define PINT_PMCTRL_PMAT(x)                      (((uint32_t)(((uint32_t)(x)) << PINT_PMCTRL_PMAT_SHIFT)) & PINT_PMCTRL_PMAT_MASK)
/*! @} */

/*! @name PMSRC - Pattern match interrupt bit-slice source register */
/*! @{ */
#define PINT_PMSRC_SRC0_MASK                     (0x700U)
#define PINT_PMSRC_SRC0_SHIFT                    (8U)
/*! SRC0 - Selects the input source for bit slice 0
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 0.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 0.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 0.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 0.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 0.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 0.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 0.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 0.
 */
#define PINT_PMSRC_SRC0(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC0_SHIFT)) & PINT_PMSRC_SRC0_MASK)
#define PINT_PMSRC_SRC1_MASK                     (0x3800U)
#define PINT_PMSRC_SRC1_SHIFT                    (11U)
/*! SRC1 - Selects the input source for bit slice 1
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 1.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 1.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 1.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 1.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 1.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 1.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 1.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 1.
 */
#define PINT_PMSRC_SRC1(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC1_SHIFT)) & PINT_PMSRC_SRC1_MASK)
#define PINT_PMSRC_SRC2_MASK                     (0x1C000U)
#define PINT_PMSRC_SRC2_SHIFT                    (14U)
/*! SRC2 - Selects the input source for bit slice 2
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 2.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 2.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 2.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 2.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 2.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 2.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 2.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 2.
 */
#define PINT_PMSRC_SRC2(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC2_SHIFT)) & PINT_PMSRC_SRC2_MASK)
#define PINT_PMSRC_SRC3_MASK                     (0xE0000U)
#define PINT_PMSRC_SRC3_SHIFT                    (17U)
/*! SRC3 - Selects the input source for bit slice 3
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 3.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 3.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 3.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 3.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 3.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 3.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 3.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 3.
 */
#define PINT_PMSRC_SRC3(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC3_SHIFT)) & PINT_PMSRC_SRC3_MASK)
#define PINT_PMSRC_SRC4_MASK                     (0x700000U)
#define PINT_PMSRC_SRC4_SHIFT                    (20U)
/*! SRC4 - Selects the input source for bit slice 4
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 4.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 4.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 4.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 4.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 4.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 4.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 4.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 4.
 */
#define PINT_PMSRC_SRC4(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC4_SHIFT)) & PINT_PMSRC_SRC4_MASK)
#define PINT_PMSRC_SRC5_MASK                     (0x3800000U)
#define PINT_PMSRC_SRC5_SHIFT                    (23U)
/*! SRC5 - Selects the input source for bit slice 5
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 5.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 5.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 5.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 5.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 5.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 5.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 5.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 5.
 */
#define PINT_PMSRC_SRC5(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC5_SHIFT)) & PINT_PMSRC_SRC5_MASK)
#define PINT_PMSRC_SRC6_MASK                     (0x1C000000U)
#define PINT_PMSRC_SRC6_SHIFT                    (26U)
/*! SRC6 - Selects the input source for bit slice 6
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 6.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 6.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 6.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 6.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 6.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 6.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 6.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 6.
 */
#define PINT_PMSRC_SRC6(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC6_SHIFT)) & PINT_PMSRC_SRC6_MASK)
#define PINT_PMSRC_SRC7_MASK                     (0xE0000000U)
#define PINT_PMSRC_SRC7_SHIFT                    (29U)
/*! SRC7 - Selects the input source for bit slice 7
 *  0b000..Input 0. Selects the pin selected in the PINTSEL0 register as the source to bit slice 7.
 *  0b001..Input 1. Selects the pin selected in the PINTSEL1 register as the source to bit slice 7.
 *  0b010..Input 2. Selects the pin selected in the PINTSEL2 register as the source to bit slice 7.
 *  0b011..Input 3. Selects the pin selected in the PINTSEL3 register as the source to bit slice 7.
 *  0b100..Input 4. Selects the pin selected in the PINTSEL4 register as the source to bit slice 7.
 *  0b101..Input 5. Selects the pin selected in the PINTSEL5 register as the source to bit slice 7.
 *  0b110..Input 6. Selects the pin selected in the PINTSEL6 register as the source to bit slice 7.
 *  0b111..Input 7. Selects the pin selected in the PINTSEL7 register as the source to bit slice 7.
 */
#define PINT_PMSRC_SRC7(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMSRC_SRC7_SHIFT)) & PINT_PMSRC_SRC7_MASK)
/*! @} */

/*! @name PMCFG - Pattern match interrupt bit slice configuration register */
/*! @{ */
#define PINT_PMCFG_PROD_ENDPTS0_MASK             (0x1U)
#define PINT_PMCFG_PROD_ENDPTS0_SHIFT            (0U)
/*! PROD_ENDPTS0 - Determines whether slice 0 is an endpoint.
 *  0b0..No effect. Slice 0 is not an endpoint.
 *  0b1..endpoint. Slice 0 is the endpoint of a product term (minterm). Pin interrupt 0 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS0(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS0_SHIFT)) & PINT_PMCFG_PROD_ENDPTS0_MASK)
#define PINT_PMCFG_PROD_ENDPTS1_MASK             (0x2U)
#define PINT_PMCFG_PROD_ENDPTS1_SHIFT            (1U)
/*! PROD_ENDPTS1 - Determines whether slice 1 is an endpoint.
 *  0b0..No effect. Slice 1 is not an endpoint.
 *  0b1..endpoint. Slice 1 is the endpoint of a product term (minterm). Pin interrupt 1 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS1(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS1_SHIFT)) & PINT_PMCFG_PROD_ENDPTS1_MASK)
#define PINT_PMCFG_PROD_ENDPTS2_MASK             (0x4U)
#define PINT_PMCFG_PROD_ENDPTS2_SHIFT            (2U)
/*! PROD_ENDPTS2 - Determines whether slice 2 is an endpoint.
 *  0b0..No effect. Slice 2 is not an endpoint.
 *  0b1..endpoint. Slice 2 is the endpoint of a product term (minterm). Pin interrupt 2 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS2(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS2_SHIFT)) & PINT_PMCFG_PROD_ENDPTS2_MASK)
#define PINT_PMCFG_PROD_ENDPTS3_MASK             (0x8U)
#define PINT_PMCFG_PROD_ENDPTS3_SHIFT            (3U)
/*! PROD_ENDPTS3 - Determines whether slice 3 is an endpoint.
 *  0b0..No effect. Slice 3 is not an endpoint.
 *  0b1..endpoint. Slice 3 is the endpoint of a product term (minterm). Pin interrupt 3 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS3(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS3_SHIFT)) & PINT_PMCFG_PROD_ENDPTS3_MASK)
#define PINT_PMCFG_PROD_ENDPTS4_MASK             (0x10U)
#define PINT_PMCFG_PROD_ENDPTS4_SHIFT            (4U)
/*! PROD_ENDPTS4 - Determines whether slice 4 is an endpoint.
 *  0b0..No effect. Slice 4 is not an endpoint.
 *  0b1..endpoint. Slice 4 is the endpoint of a product term (minterm). Pin interrupt 4 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS4(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS4_SHIFT)) & PINT_PMCFG_PROD_ENDPTS4_MASK)
#define PINT_PMCFG_PROD_ENDPTS5_MASK             (0x20U)
#define PINT_PMCFG_PROD_ENDPTS5_SHIFT            (5U)
/*! PROD_ENDPTS5 - Determines whether slice 5 is an endpoint.
 *  0b0..No effect. Slice 5 is not an endpoint.
 *  0b1..endpoint. Slice 5 is the endpoint of a product term (minterm). Pin interrupt 5 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS5(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS5_SHIFT)) & PINT_PMCFG_PROD_ENDPTS5_MASK)
#define PINT_PMCFG_PROD_ENDPTS6_MASK             (0x40U)
#define PINT_PMCFG_PROD_ENDPTS6_SHIFT            (6U)
/*! PROD_ENDPTS6 - Determines whether slice 6 is an endpoint.
 *  0b0..No effect. Slice 6 is not an endpoint.
 *  0b1..endpoint. Slice 6 is the endpoint of a product term (minterm). Pin interrupt 6 in the NVIC is raised if the minterm evaluates as true.
 */
#define PINT_PMCFG_PROD_ENDPTS6(x)               (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_PROD_ENDPTS6_SHIFT)) & PINT_PMCFG_PROD_ENDPTS6_MASK)
#define PINT_PMCFG_CFG0_MASK                     (0x700U)
#define PINT_PMCFG_CFG0_SHIFT                    (8U)
/*! CFG0 - Specifies the match contribution condition for bit slice 0.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG0(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG0_SHIFT)) & PINT_PMCFG_CFG0_MASK)
#define PINT_PMCFG_CFG1_MASK                     (0x3800U)
#define PINT_PMCFG_CFG1_SHIFT                    (11U)
/*! CFG1 - Specifies the match contribution condition for bit slice 1.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG1(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG1_SHIFT)) & PINT_PMCFG_CFG1_MASK)
#define PINT_PMCFG_CFG2_MASK                     (0x1C000U)
#define PINT_PMCFG_CFG2_SHIFT                    (14U)
/*! CFG2 - Specifies the match contribution condition for bit slice 2.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG2(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG2_SHIFT)) & PINT_PMCFG_CFG2_MASK)
#define PINT_PMCFG_CFG3_MASK                     (0xE0000U)
#define PINT_PMCFG_CFG3_SHIFT                    (17U)
/*! CFG3 - Specifies the match contribution condition for bit slice 3.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG3(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG3_SHIFT)) & PINT_PMCFG_CFG3_MASK)
#define PINT_PMCFG_CFG4_MASK                     (0x700000U)
#define PINT_PMCFG_CFG4_SHIFT                    (20U)
/*! CFG4 - Specifies the match contribution condition for bit slice 4.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG4(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG4_SHIFT)) & PINT_PMCFG_CFG4_MASK)
#define PINT_PMCFG_CFG5_MASK                     (0x3800000U)
#define PINT_PMCFG_CFG5_SHIFT                    (23U)
/*! CFG5 - Specifies the match contribution condition for bit slice 5.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG5(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG5_SHIFT)) & PINT_PMCFG_CFG5_MASK)
#define PINT_PMCFG_CFG6_MASK                     (0x1C000000U)
#define PINT_PMCFG_CFG6_SHIFT                    (26U)
/*! CFG6 - Specifies the match contribution condition for bit slice 6.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG6(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG6_SHIFT)) & PINT_PMCFG_CFG6_MASK)
#define PINT_PMCFG_CFG7_MASK                     (0xE0000000U)
#define PINT_PMCFG_CFG7_SHIFT                    (29U)
/*! CFG7 - Specifies the match contribution condition for bit slice 7.
 *  0b000..Constant HIGH. This bit slice always contributes to a product term match.
 *  0b001..Sticky rising edge. Match occurs if a rising edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b010..Sticky falling edge. Match occurs if a falling edge on the specified input has occurred since the last
 *         time the edge detection for this bit slice was cleared. This bit is only cleared when the PMCFG or the
 *         PMSRC registers are written to.
 *  0b011..Sticky rising or falling edge. Match occurs if either a rising or falling edge on the specified input
 *         has occurred since the last time the edge detection for this bit slice was cleared. This bit is only
 *         cleared when the PMCFG or the PMSRC registers are written to.
 *  0b100..High level. Match (for this bit slice) occurs when there is a high level on the input specified for this bit slice in the PMSRC register.
 *  0b101..Low level. Match occurs when there is a low level on the specified input.
 *  0b110..Constant 0. This bit slice never contributes to a match (should be used to disable any unused bit slices).
 *  0b111..Event. Non-sticky rising or falling edge. Match occurs on an event - i.e. when either a rising or
 *         falling edge is first detected on the specified input (this is a non-sticky version of value 0x3) . This bit
 *         is cleared after one clock cycle.
 */
#define PINT_PMCFG_CFG7(x)                       (((uint32_t)(((uint32_t)(x)) << PINT_PMCFG_CFG7_SHIFT)) & PINT_PMCFG_CFG7_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PINT_Register_Masks */


/* PINT - Peripheral instance base addresses */
/** Peripheral PINT base address */
#define PINT_BASE                                (0x40004000u)
/** Peripheral PINT base pointer */
#define PINT                                     ((PINT_Type *)PINT_BASE)
/** Array initializer of PINT peripheral base addresses */
#define PINT_BASE_ADDRS                          { PINT_BASE }
/** Array initializer of PINT peripheral base pointers */
#define PINT_BASE_PTRS                           { PINT }
/** Interrupt vectors for the PINT peripheral type */
#define PINT_IRQS                                { PIN_INT0_IRQn, PIN_INT1_IRQn, PIN_INT2_IRQn, PIN_INT3_IRQn }

/*!
 * @}
 */ /* end of group PINT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< RTC control register, offset: 0x0 */
  __IO uint32_t MATCH;                             /**< RTC match register, offset: 0x4 */
  __IO uint32_t COUNT;                             /**< RTC counter register, offset: 0x8 */
  __IO uint32_t WAKE;                              /**< High-resolution/wake-up timer control register, offset: 0xC */
} RTC_Type;

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name CTRL - RTC control register */
/*! @{ */
#define RTC_CTRL_SWRESET_MASK                    (0x1U)
#define RTC_CTRL_SWRESET_SHIFT                   (0U)
/*! SWRESET - Software reset control
 *  0b0..Not in reset. The RTC is not held in reset. This bit must be cleared prior to configuring or initiating any operation of the RTC.
 *  0b1..In reset. The RTC is held in reset. All register bits within the RTC will be forced to their reset value
 *       except the OFD bit. This bit must be cleared before writing to any register in the RTC - including writes
 *       to set any of the other bits within this register. Do not attempt to write to any bits of this register at
 *       the same time that the reset bit is being cleared.
 */
#define RTC_CTRL_SWRESET(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_SWRESET_SHIFT)) & RTC_CTRL_SWRESET_MASK)
#define RTC_CTRL_ALARM1HZ_MASK                   (0x4U)
#define RTC_CTRL_ALARM1HZ_SHIFT                  (2U)
/*! ALARM1HZ - RTC 1 Hz timer alarm flag status.
 *  0b0..No match. No match has occurred on the 1 Hz RTC timer. Writing a 0 has no effect.
 *  0b1..Match. A match condition has occurred on the 1 Hz RTC timer. This flag generates an RTC alarm interrupt
 *       request RTC_ALARM which can also wake up the part from any low power mode. Writing a 1 clears this bit.
 */
#define RTC_CTRL_ALARM1HZ(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_ALARM1HZ_SHIFT)) & RTC_CTRL_ALARM1HZ_MASK)
#define RTC_CTRL_WAKE1KHZ_MASK                   (0x8U)
#define RTC_CTRL_WAKE1KHZ_SHIFT                  (3U)
/*! WAKE1KHZ - RTC 1 kHz timer wake-up flag status.
 *  0b0..Run. The RTC 1 kHz timer is running. Writing a 0 has no effect.
 *  0b1..Time-out. The 1 kHz high-resolution/wake-up timer has timed out. This flag generates an RTC wake-up
 *       interrupt request RTC-WAKE which can also wake up the part from any low power mode. Writing a 1 clears this bit.
 */
#define RTC_CTRL_WAKE1KHZ(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_WAKE1KHZ_SHIFT)) & RTC_CTRL_WAKE1KHZ_MASK)
#define RTC_CTRL_ALARMDPD_EN_MASK                (0x10U)
#define RTC_CTRL_ALARMDPD_EN_SHIFT               (4U)
/*! ALARMDPD_EN - RTC 1 Hz timer alarm enable for Deep power-down.
 *  0b0..Disable. A match on the 1 Hz RTC timer will not bring the part out of Deep power-down mode.
 *  0b1..Enable. A match on the 1 Hz RTC timer bring the part out of Deep power-down mode.
 */
#define RTC_CTRL_ALARMDPD_EN(x)                  (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_ALARMDPD_EN_SHIFT)) & RTC_CTRL_ALARMDPD_EN_MASK)
#define RTC_CTRL_WAKEDPD_EN_MASK                 (0x20U)
#define RTC_CTRL_WAKEDPD_EN_SHIFT                (5U)
/*! WAKEDPD_EN - RTC 1 kHz timer wake-up enable for Deep power-down.
 *  0b0..Disable. A match on the 1 kHz RTC timer will not bring the part out of Deep power-down mode.
 *  0b1..Enable. A match on the 1 kHz RTC timer bring the part out of Deep power-down mode.
 */
#define RTC_CTRL_WAKEDPD_EN(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_WAKEDPD_EN_SHIFT)) & RTC_CTRL_WAKEDPD_EN_MASK)
#define RTC_CTRL_RTC1KHZ_EN_MASK                 (0x40U)
#define RTC_CTRL_RTC1KHZ_EN_SHIFT                (6U)
/*! RTC1KHZ_EN - RTC 1 kHz clock enable. This bit can be set to 0 to conserve power if the 1 kHz
 *    timer is not used. This bit has no effect when the RTC is disabled (bit 7 of this register is 0).
 *  0b0..Disable. A match on the 1 kHz RTC timer will not bring the part out of Deep power-down mode.
 *  0b1..Enable. The 1 kHz RTC timer is enabled.
 */
#define RTC_CTRL_RTC1KHZ_EN(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC1KHZ_EN_SHIFT)) & RTC_CTRL_RTC1KHZ_EN_MASK)
#define RTC_CTRL_RTC_EN_MASK                     (0x80U)
#define RTC_CTRL_RTC_EN_SHIFT                    (7U)
/*! RTC_EN - RTC enable.
 *  0b0..Disable. The RTC 1 Hz and 1 kHz clocks are shut down and the RTC operation is disabled. This bit should
 *       be 0 when writing to load a value in the RTC counter register.
 *  0b1..Enable. The 1 Hz RTC clock is running and RTC operation is enabled. This bit must be set to initiate
 *       operation of the RTC. The first clock to the RTC counter occurs 1 s after this bit is set. To also enable the
 *       high-resolution, 1 kHz clock, set bit 6 in this register.
 */
#define RTC_CTRL_RTC_EN(x)                       (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC_EN_SHIFT)) & RTC_CTRL_RTC_EN_MASK)
#define RTC_CTRL_RTC_OSC_PD_MASK                 (0x100U)
#define RTC_CTRL_RTC_OSC_PD_SHIFT                (8U)
/*! RTC_OSC_PD - RTC oscillator power-down control.
 *  0b0..RTC oscillator is powered-up and can output a clock if a crystal is correctly connected externally
 *  0b1..RTC oscillator is powered-down.
 */
#define RTC_CTRL_RTC_OSC_PD(x)                   (((uint32_t)(((uint32_t)(x)) << RTC_CTRL_RTC_OSC_PD_SHIFT)) & RTC_CTRL_RTC_OSC_PD_MASK)
/*! @} */

/*! @name MATCH - RTC match register */
/*! @{ */
#define RTC_MATCH_MATVAL_MASK                    (0xFFFFFFFFU)
#define RTC_MATCH_MATVAL_SHIFT                   (0U)
/*! MATVAL - Contains the match value against which the 1 Hz RTC timer will be compared to set the
 *    alarm flag RTC_ALARM and generate an alarm interrupt/wake-up if enabled.
 */
#define RTC_MATCH_MATVAL(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_MATCH_MATVAL_SHIFT)) & RTC_MATCH_MATVAL_MASK)
/*! @} */

/*! @name COUNT - RTC counter register */
/*! @{ */
#define RTC_COUNT_VAL_MASK                       (0xFFFFFFFFU)
#define RTC_COUNT_VAL_SHIFT                      (0U)
/*! VAL - A read reflects the current value of the main, 1 Hz RTC timer. A write loads a new initial
 *    value into the timer. The RTC counter will count up continuously at a 1 Hz rate once the RTC
 *    Software Reset is removed (by clearing bit 0 of the CTRL register). Only write to this
 *    register when the RTC_EN bit in the RTC CTRL Register is 0. The counter increments one second after
 *    the RTC_EN bit is set.
 */
#define RTC_COUNT_VAL(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_COUNT_VAL_SHIFT)) & RTC_COUNT_VAL_MASK)
/*! @} */

/*! @name WAKE - High-resolution/wake-up timer control register */
/*! @{ */
#define RTC_WAKE_VAL_MASK                        (0xFFFFU)
#define RTC_WAKE_VAL_SHIFT                       (0U)
/*! VAL - A read reflects the current value of the high-resolution/wake-up timer. A write pre-loads
 *    a start count value into the wake-up timer and initializes a count-down sequence. Do not write
 *    to this register while counting is in progress.
 */
#define RTC_WAKE_VAL(x)                          (((uint32_t)(((uint32_t)(x)) << RTC_WAKE_VAL_SHIFT)) & RTC_WAKE_VAL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x4002C000u)
/** Peripheral RTC base pointer */
#define RTC                                      ((RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                           { RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            { RTC }
/** Interrupt vectors for the RTC peripheral type */
#define RTC_IRQS                                 { RTC_IRQn }

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SCT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCT_Peripheral_Access_Layer SCT Peripheral Access Layer
 * @{
 */

/** SCT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CONFIG;                            /**< SCT configuration register, offset: 0x0 */
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint16_t CTRLL;                             /**< SCT_CTRLL register, offset: 0x4 */
      __IO uint16_t CTRLH;                             /**< SCT_CTRLH register, offset: 0x6 */
    } CTRL_ACCESS16BIT;
    __IO uint32_t CTRL;                              /**< SCT control register, offset: 0x4 */
  };
  union {                                          /* offset: 0x8 */
    struct {                                         /* offset: 0x8 */
      __IO uint16_t LIMITL;                            /**< SCT_LIMITL register, offset: 0x8 */
      __IO uint16_t LIMITH;                            /**< SCT_LIMITH register, offset: 0xA */
    } LIMIT_ACCESS16BIT;
    __IO uint32_t LIMIT;                             /**< SCT limit event select register, offset: 0x8 */
  };
  union {                                          /* offset: 0xC */
    struct {                                         /* offset: 0xC */
      __IO uint16_t HALTL;                             /**< SCT_HALTL register, offset: 0xC */
      __IO uint16_t HALTH;                             /**< SCT_HALTH register, offset: 0xE */
    } HALT_ACCESS16BIT;
    __IO uint32_t HALT;                              /**< SCT halt event select register, offset: 0xC */
  };
  union {                                          /* offset: 0x10 */
    struct {                                         /* offset: 0x10 */
      __IO uint16_t STOPL;                             /**< SCT_STOPL register, offset: 0x10 */
      __IO uint16_t STOPH;                             /**< SCT_STOPH register, offset: 0x12 */
    } STOP_ACCESS16BIT;
    __IO uint32_t STOP;                              /**< SCT stop event select register, offset: 0x10 */
  };
  union {                                          /* offset: 0x14 */
    struct {                                         /* offset: 0x14 */
      __IO uint16_t STARTL;                            /**< SCT_STARTL register, offset: 0x14 */
      __IO uint16_t STARTH;                            /**< SCT_STARTH register, offset: 0x16 */
    } START_ACCESS16BIT;
    __IO uint32_t START;                             /**< SCT start event select register, offset: 0x14 */
  };
       uint8_t RESERVED_0[40];
  union {                                          /* offset: 0x40 */
    struct {                                         /* offset: 0x40 */
      __IO uint16_t COUNTL;                            /**< SCT_COUNTL register, offset: 0x40 */
      __IO uint16_t COUNTH;                            /**< SCT_COUNTH register, offset: 0x42 */
    } COUNT_ACCESS16BIT;
    __IO uint32_t COUNT;                             /**< SCT counter register, offset: 0x40 */
  };
  union {                                          /* offset: 0x44 */
    struct {                                         /* offset: 0x44 */
      __IO uint16_t STATEL;                            /**< SCT_STATEL register, offset: 0x44 */
      __IO uint16_t STATEH;                            /**< SCT_STATEH register, offset: 0x46 */
    } STATE_ACCESS16BIT;
    __IO uint32_t STATE;                             /**< SCT state register, offset: 0x44 */
  };
  __I  uint32_t INPUT;                             /**< SCT input register, offset: 0x48 */
  union {                                          /* offset: 0x4C */
    struct {                                         /* offset: 0x4C */
      __IO uint16_t REGMODEL;                          /**< SCT_REGMODEL register, offset: 0x4C */
      __IO uint16_t REGMODEH;                          /**< SCT_REGMODEH register, offset: 0x4E */
    } REGMODE_ACCESS16BIT;
    __IO uint32_t REGMODE;                           /**< SCT match/capture mode register, offset: 0x4C */
  };
  __IO uint32_t OUTPUT;                            /**< SCT output register, offset: 0x50 */
  __IO uint32_t OUTPUTDIRCTRL;                     /**< SCT output counter direction control register, offset: 0x54 */
  __IO uint32_t RES;                               /**< SCT conflict resolution register, offset: 0x58 */
  __IO uint32_t DMAREQ0;                           /**< SCT DMA request 0 register, offset: 0x5C */
  __IO uint32_t DMAREQ1;                           /**< SCT DMA request 1 register, offset: 0x60 */
       uint8_t RESERVED_1[140];
  __IO uint32_t EVEN;                              /**< SCT event interrupt enable register, offset: 0xF0 */
  __IO uint32_t EVFLAG;                            /**< SCT event flag register, offset: 0xF4 */
  __IO uint32_t CONEN;                             /**< SCT conflict interrupt enable register, offset: 0xF8 */
  __IO uint32_t CONFLAG;                           /**< SCT conflict flag register, offset: 0xFC */
  union {                                          /* offset: 0x100 */
    union {                                          /* offset: 0x100, array step: 0x4 */
      struct {                                         /* offset: 0x100, array step: 0x4 */
        __IO uint16_t CAPL;                              /**< SCT_CAPL register, array offset: 0x100, array step: 0x4 */
        __IO uint16_t CAPH;                              /**< SCT_CAPH register, array offset: 0x102, array step: 0x4 */
      } CAP_ACCESS16BIT[10];
      __IO uint32_t CAP[10];                           /**< SCT capture register of capture channel, array offset: 0x100, array step: 0x4 */
    };
    union {                                          /* offset: 0x100, array step: 0x4 */
      struct {                                         /* offset: 0x100, array step: 0x4 */
        __IO uint16_t MATCHL;                            /**< SCT_MATCHL register, array offset: 0x100, array step: 0x4 */
        __IO uint16_t MATCHH;                            /**< SCT_MATCHH register, array offset: 0x102, array step: 0x4 */
      } MATCH_ACCESS16BIT[10];
      __IO uint32_t MATCH[10];                         /**< SCT match value register of match channels, array offset: 0x100, array step: 0x4 */
    };
  };
       uint8_t RESERVED_2[216];
  union {                                          /* offset: 0x200 */
    union {                                          /* offset: 0x200, array step: 0x4 */
      struct {                                         /* offset: 0x200, array step: 0x4 */
        __IO uint16_t CAPCTRLL;                          /**< SCT_CAPCTRLL register, array offset: 0x200, array step: 0x4 */
        __IO uint16_t CAPCTRLH;                          /**< SCT_CAPCTRLH register, array offset: 0x202, array step: 0x4 */
      } CAPCTRL_ACCESS16BIT[10];
      __IO uint32_t CAPCTRL[10];                       /**< SCT capture control register, array offset: 0x200, array step: 0x4 */
    };
    union {                                          /* offset: 0x200, array step: 0x4 */
      struct {                                         /* offset: 0x200, array step: 0x4 */
        __IO uint16_t MATCHRELL;                         /**< SCT_MATCHRELL register, array offset: 0x200, array step: 0x4 */
        __IO uint16_t MATCHRELH;                         /**< SCT_MATCHRELH register, array offset: 0x202, array step: 0x4 */
      } MATCHREL_ACCESS16BIT[10];
      __IO uint32_t MATCHREL[10];                      /**< SCT match reload value register, array offset: 0x200, array step: 0x4 */
    };
  };
       uint8_t RESERVED_3[216];
  struct {                                         /* offset: 0x300, array step: 0x8 */
    __IO uint32_t STATE;                             /**< SCT event state register 0, array offset: 0x300, array step: 0x8 */
    __IO uint32_t CTRL;                              /**< SCT event control register 0, array offset: 0x304, array step: 0x8 */
  } EV[10];
       uint8_t RESERVED_4[432];
  struct {                                         /* offset: 0x500, array step: 0x8 */
    __IO uint32_t SET;                               /**< SCT output 0 set register, array offset: 0x500, array step: 0x8 */
    __IO uint32_t CLR;                               /**< SCT output 0 clear register, array offset: 0x504, array step: 0x8 */
  } OUT[8];
} SCT_Type;

/* ----------------------------------------------------------------------------
   -- SCT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SCT_Register_Masks SCT Register Masks
 * @{
 */

/*! @name CONFIG - SCT configuration register */
/*! @{ */
#define SCT_CONFIG_UNIFY_MASK                    (0x1U)
#define SCT_CONFIG_UNIFY_SHIFT                   (0U)
/*! UNIFY - SCT operation
 *  0b0..The SCT operates as two 16-bit counters named COUNTER_L and COUNTER_H.
 *  0b1..The SCT operates as a unified 32-bit counter.
 */
#define SCT_CONFIG_UNIFY(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_UNIFY_SHIFT)) & SCT_CONFIG_UNIFY_MASK)
#define SCT_CONFIG_CLKMODE_MASK                  (0x6U)
#define SCT_CONFIG_CLKMODE_SHIFT                 (1U)
/*! CLKMODE - SCT clock mode
 *  0b00..System Clock Mode. The system clock clocks the entire SCT module including the counter(s) and counter prescalers.
 *  0b01..Sampled System Clock Mode. The system clock clocks the SCT module, but the counter and prescalers are
 *        only enabled to count when the designated edge is detected on the input selected by the CKSEL field. The
 *        minimum pulse width on the selected clock-gate input is 1 bus clock period. This mode is the
 *        high-performance, sampled-clock mode.
 *  0b10..SCT Input Clock Mode. The input/edge selected by the CKSEL field clocks the SCT module, including the
 *        counters and prescalers, after first being synchronized to the system clock. The minimum pulse width on the
 *        clock input is 1 bus clock period. This mode is the low-power, sampled-clock mode.
 *  0b11..Asynchronous Mode. The entire SCT module is clocked directly by the input/edge selected by the CKSEL
 *        field. In this mode, the SCT outputs are switched synchronously to the SCT input clock - not the system
 *        clock. The input clock rate must be at least half the system clock rate and can be the same or faster than
 *        the system clock.
 */
#define SCT_CONFIG_CLKMODE(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_CLKMODE_SHIFT)) & SCT_CONFIG_CLKMODE_MASK)
#define SCT_CONFIG_CKSEL_MASK                    (0x78U)
#define SCT_CONFIG_CKSEL_SHIFT                   (3U)
/*! CKSEL - SCT clock select. The specific functionality of the designated input/edge is dependent
 *    on the CLKMODE bit selection in this register.
 *  0b0000..Rising edges on input 0.
 *  0b0001..Falling edges on input 0.
 *  0b0010..Rising edges on input 1.
 *  0b0011..Falling edges on input 1.
 *  0b0100..Rising edges on input 2.
 *  0b0101..Falling edges on input 2.
 *  0b0110..Rising edges on input 3.
 *  0b0111..Falling edges on input 3.
 *  0b1000..Rising edges on input 4.
 *  0b1001..Falling edges on input 4.
 *  0b1010..Rising edges on input 5.
 *  0b1011..Falling edges on input 5.
 *  0b1100..Rising edges on input 6.
 *  0b1101..Falling edges on input 6.
 *  0b1110..Rising edges on input 7.
 *  0b1111..Falling edges on input 7.
 */
#define SCT_CONFIG_CKSEL(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_CKSEL_SHIFT)) & SCT_CONFIG_CKSEL_MASK)
#define SCT_CONFIG_NORELOAD_L_MASK               (0x80U)
#define SCT_CONFIG_NORELOAD_L_SHIFT              (7U)
/*! NORELOAD_L - A 1 in this bit prevents the lower match registers from being reloaded from their
 *    respective reload registers. Setting this bit eliminates the need to write to the reload
 *    registers MATCHREL if the match values are fixed. Software can write to set or clear this bit at any
 *    time. This bit applies to both the higher and lower registers when the UNIFY bit is set.
 */
#define SCT_CONFIG_NORELOAD_L(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_NORELOAD_L_SHIFT)) & SCT_CONFIG_NORELOAD_L_MASK)
#define SCT_CONFIG_NORELOAD_H_MASK               (0x100U)
#define SCT_CONFIG_NORELOAD_H_SHIFT              (8U)
/*! NORELOAD_H - A 1 in this bit prevents the higher match registers from being reloaded from their
 *    respective reload registers. Setting this bit eliminates the need to write to the reload
 *    registers MATCHREL if the match values are fixed. Software can write to set or clear this bit at
 *    any time. This bit is not used when the UNIFY bit is set.
 */
#define SCT_CONFIG_NORELOAD_H(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_NORELOAD_H_SHIFT)) & SCT_CONFIG_NORELOAD_H_MASK)
#define SCT_CONFIG_INSYNC_MASK                   (0x1E00U)
#define SCT_CONFIG_INSYNC_SHIFT                  (9U)
/*! INSYNC - Synchronization for input N (bit 9 = input 0, bit 10 = input 1,, bit 12 = input 3); all
 *    other bits are reserved. A 1 in one of these bits subjects the corresponding input to
 *    synchronization to the SCT clock, before it is used to create an event. If an input is known to
 *    already be synchronous to the SCT clock, this bit may be set to 0 for faster input response. (Note:
 *    The SCT clock is the system clock for CKMODEs 0-2. It is the selected, asynchronous SCT input
 *    clock for CKMODE3). Note that the INSYNC field only affects inputs used for event generation.
 *    It does not apply to the clock input specified in the CKSEL field.
 */
#define SCT_CONFIG_INSYNC(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_INSYNC_SHIFT)) & SCT_CONFIG_INSYNC_MASK)
#define SCT_CONFIG_AUTOLIMIT_L_MASK              (0x20000U)
#define SCT_CONFIG_AUTOLIMIT_L_SHIFT             (17U)
/*! AUTOLIMIT_L - A one in this bit causes a match on match register 0 to be treated as a de-facto
 *    LIMIT condition without the need to define an associated event. As with any LIMIT event, this
 *    automatic limit causes the counter to be cleared to zero in unidirectional mode or to change
 *    the direction of count in bi-directional mode. Software can write to set or clear this bit at
 *    any time. This bit applies to both the higher and lower registers when the UNIFY bit is set.
 */
#define SCT_CONFIG_AUTOLIMIT_L(x)                (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_AUTOLIMIT_L_SHIFT)) & SCT_CONFIG_AUTOLIMIT_L_MASK)
#define SCT_CONFIG_AUTOLIMIT_H_MASK              (0x40000U)
#define SCT_CONFIG_AUTOLIMIT_H_SHIFT             (18U)
/*! AUTOLIMIT_H - A one in this bit will cause a match on match register 0 to be treated as a
 *    de-facto LIMIT condition without the need to define an associated event. As with any LIMIT event,
 *    this automatic limit causes the counter to be cleared to zero in unidirectional mode or to
 *    change the direction of count in bi-directional mode. Software can write to set or clear this bit
 *    at any time. This bit is not used when the UNIFY bit is set.
 */
#define SCT_CONFIG_AUTOLIMIT_H(x)                (((uint32_t)(((uint32_t)(x)) << SCT_CONFIG_AUTOLIMIT_H_SHIFT)) & SCT_CONFIG_AUTOLIMIT_H_MASK)
/*! @} */

/*! @name CTRLL - SCT_CTRLL register */
/*! @{ */
#define SCT_CTRLL_DOWN_L_MASK                    (0x1U)
#define SCT_CTRLL_DOWN_L_SHIFT                   (0U)
/*! DOWN_L - This bit is 1 when the L or unified counter is counting down. Hardware sets this bit
 *    when the counter is counting up, counter limit occurs, and BIDIR = 1.Hardware clears this bit
 *    when the counter is counting down and a limit condition occurs or when the counter reaches 0.
 */
#define SCT_CTRLL_DOWN_L(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_DOWN_L_SHIFT)) & SCT_CTRLL_DOWN_L_MASK)
#define SCT_CTRLL_STOP_L_MASK                    (0x2U)
#define SCT_CTRLL_STOP_L_SHIFT                   (1U)
/*! STOP_L - When this bit is 1 and HALT is 0, the L or unified counter does not run, but I/O events
 *    related to the counter can occur. If a designated start event occurs, this bit is cleared and
 *    counting resumes.
 */
#define SCT_CTRLL_STOP_L(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_STOP_L_SHIFT)) & SCT_CTRLL_STOP_L_MASK)
#define SCT_CTRLL_HALT_L_MASK                    (0x4U)
#define SCT_CTRLL_HALT_L_SHIFT                   (2U)
/*! HALT_L - When this bit is 1, the L or unified counter does not run and no events can occur. A
 *    reset sets this bit. When the HALT_L bit is one, the STOP_L bit is cleared. It is possible to
 *    remove the halt condition while keeping the SCT in the stop condition (not running) with a
 *    single write to this register to simultaneously clear the HALT bit and set the STOP bit. Once set,
 *    only software can clear this bit to restore counter operation. This bit is set on reset.
 */
#define SCT_CTRLL_HALT_L(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_HALT_L_SHIFT)) & SCT_CTRLL_HALT_L_MASK)
#define SCT_CTRLL_CLRCTR_L_MASK                  (0x8U)
#define SCT_CTRLL_CLRCTR_L_SHIFT                 (3U)
/*! CLRCTR_L - Writing a 1 to this bit clears the L or unified counter. This bit always reads as 0.
 */
#define SCT_CTRLL_CLRCTR_L(x)                    (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_CLRCTR_L_SHIFT)) & SCT_CTRLL_CLRCTR_L_MASK)
#define SCT_CTRLL_BIDIR_L_MASK                   (0x10U)
#define SCT_CTRLL_BIDIR_L_SHIFT                  (4U)
/*! BIDIR_L - L or unified counter direction select
 *  0b0..Up. The counter counts up to a limit condition, then is cleared to zero.
 *  0b1..Up-down. The counter counts up to a limit, then counts down to a limit condition or to 0.
 */
#define SCT_CTRLL_BIDIR_L(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_BIDIR_L_SHIFT)) & SCT_CTRLL_BIDIR_L_MASK)
#define SCT_CTRLL_PRE_L_MASK                     (0x1FE0U)
#define SCT_CTRLL_PRE_L_SHIFT                    (5U)
/*! PRE_L - Specifies the factor by which the SCT clock is prescaled to produce the L or unified
 *    counter clock. The counter clock is clocked at the rate of the SCT clock divided by PRE_L+1.
 *    Clear the counter (by writing a 1 to the CLRCTR bit) whenever changing the PRE value.
 */
#define SCT_CTRLL_PRE_L(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_CTRLL_PRE_L_SHIFT)) & SCT_CTRLL_PRE_L_MASK)
/*! @} */

/*! @name CTRLH - SCT_CTRLH register */
/*! @{ */
#define SCT_CTRLH_DOWN_H_MASK                    (0x1U)
#define SCT_CTRLH_DOWN_H_SHIFT                   (0U)
/*! DOWN_H - This bit is 1 when the H counter is counting down. Hardware sets this bit when the
 *    counter is counting, a counter limit condition occurs, and BIDIR is 1. Hardware clears this bit
 *    when the counter is counting down and a limit condition occurs or when the counter reaches 0.
 */
#define SCT_CTRLH_DOWN_H(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_DOWN_H_SHIFT)) & SCT_CTRLH_DOWN_H_MASK)
#define SCT_CTRLH_STOP_H_MASK                    (0x2U)
#define SCT_CTRLH_STOP_H_SHIFT                   (1U)
/*! STOP_H - When this bit is 1 and HALT is 0, the H counter does not, run but I/O events related to
 *    the counter can occur. If such an event matches the mask in the Start register, this bit is
 *    cleared and counting resumes.
 */
#define SCT_CTRLH_STOP_H(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_STOP_H_SHIFT)) & SCT_CTRLH_STOP_H_MASK)
#define SCT_CTRLH_HALT_H_MASK                    (0x4U)
#define SCT_CTRLH_HALT_H_SHIFT                   (2U)
/*! HALT_H - When this bit is 1, the H counter does not run and no events can occur. A reset sets
 *    this bit. When the HALT_H bit is one, the STOP_H bit is cleared. It is possible to remove the
 *    halt condition while keeping the SCT in the stop condition (not running) with a single write to
 *    this register to simultaneously clear the HALT bit and set the STOP bit. Once set, this bit
 *    can only be cleared by software to restore counter operation. This bit is set on reset.
 */
#define SCT_CTRLH_HALT_H(x)                      (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_HALT_H_SHIFT)) & SCT_CTRLH_HALT_H_MASK)
#define SCT_CTRLH_CLRCTR_H_MASK                  (0x8U)
#define SCT_CTRLH_CLRCTR_H_SHIFT                 (3U)
/*! CLRCTR_H - Writing a 1 to this bit clears the H counter. This bit always reads as 0.
 */
#define SCT_CTRLH_CLRCTR_H(x)                    (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_CLRCTR_H_SHIFT)) & SCT_CTRLH_CLRCTR_H_MASK)
#define SCT_CTRLH_BIDIR_H_MASK                   (0x10U)
#define SCT_CTRLH_BIDIR_H_SHIFT                  (4U)
/*! BIDIR_H - Direction select
 *  0b0..The H counter counts up to its limit condition, then is cleared to zero.
 *  0b1..The H counter counts up to its limit, then counts down to a limit condition or to 0.
 */
#define SCT_CTRLH_BIDIR_H(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_BIDIR_H_SHIFT)) & SCT_CTRLH_BIDIR_H_MASK)
#define SCT_CTRLH_PRE_H_MASK                     (0x1FE0U)
#define SCT_CTRLH_PRE_H_SHIFT                    (5U)
/*! PRE_H - Specifies the factor by which the SCT clock is prescaled to produce the H counter clock.
 *    The counter clock is clocked at the rate of the SCT clock divided by PRELH+1. Clear the
 *    counter (by writing a 1 to the CLRCTR bit) whenever changing the PRE value.
 */
#define SCT_CTRLH_PRE_H(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_CTRLH_PRE_H_SHIFT)) & SCT_CTRLH_PRE_H_MASK)
/*! @} */

/*! @name CTRL - SCT control register */
/*! @{ */
#define SCT_CTRL_DOWN_L_MASK                     (0x1U)
#define SCT_CTRL_DOWN_L_SHIFT                    (0U)
/*! DOWN_L - This bit is 1 when the L or unified counter is counting down. Hardware sets this bit
 *    when the counter is counting up, counter limit occurs, and BIDIR = 1.Hardware clears this bit
 *    when the counter is counting down and a limit condition occurs or when the counter reaches 0.
 */
#define SCT_CTRL_DOWN_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_DOWN_L_SHIFT)) & SCT_CTRL_DOWN_L_MASK)
#define SCT_CTRL_STOP_L_MASK                     (0x2U)
#define SCT_CTRL_STOP_L_SHIFT                    (1U)
/*! STOP_L - When this bit is 1 and HALT is 0, the L or unified counter does not run, but I/O events
 *    related to the counter can occur. If a designated start event occurs, this bit is cleared and
 *    counting resumes.
 */
#define SCT_CTRL_STOP_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_STOP_L_SHIFT)) & SCT_CTRL_STOP_L_MASK)
#define SCT_CTRL_HALT_L_MASK                     (0x4U)
#define SCT_CTRL_HALT_L_SHIFT                    (2U)
/*! HALT_L - When this bit is 1, the L or unified counter does not run and no events can occur. A
 *    reset sets this bit. When the HALT_L bit is one, the STOP_L bit is cleared. It is possible to
 *    remove the halt condition while keeping the SCT in the stop condition (not running) with a
 *    single write to this register to simultaneously clear the HALT bit and set the STOP bit. Once set,
 *    only software can clear this bit to restore counter operation. This bit is set on reset.
 */
#define SCT_CTRL_HALT_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_HALT_L_SHIFT)) & SCT_CTRL_HALT_L_MASK)
#define SCT_CTRL_CLRCTR_L_MASK                   (0x8U)
#define SCT_CTRL_CLRCTR_L_SHIFT                  (3U)
/*! CLRCTR_L - Writing a 1 to this bit clears the L or unified counter. This bit always reads as 0.
 */
#define SCT_CTRL_CLRCTR_L(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_CLRCTR_L_SHIFT)) & SCT_CTRL_CLRCTR_L_MASK)
#define SCT_CTRL_BIDIR_L_MASK                    (0x10U)
#define SCT_CTRL_BIDIR_L_SHIFT                   (4U)
/*! BIDIR_L - L or unified counter direction select
 *  0b0..Up. The counter counts up to a limit condition, then is cleared to zero.
 *  0b1..Up-down. The counter counts up to a limit, then counts down to a limit condition or to 0.
 */
#define SCT_CTRL_BIDIR_L(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_BIDIR_L_SHIFT)) & SCT_CTRL_BIDIR_L_MASK)
#define SCT_CTRL_PRE_L_MASK                      (0x1FE0U)
#define SCT_CTRL_PRE_L_SHIFT                     (5U)
/*! PRE_L - Specifies the factor by which the SCT clock is prescaled to produce the L or unified
 *    counter clock. The counter clock is clocked at the rate of the SCT clock divided by PRE_L+1.
 *    Clear the counter (by writing a 1 to the CLRCTR bit) whenever changing the PRE value.
 */
#define SCT_CTRL_PRE_L(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_PRE_L_SHIFT)) & SCT_CTRL_PRE_L_MASK)
#define SCT_CTRL_DOWN_H_MASK                     (0x10000U)
#define SCT_CTRL_DOWN_H_SHIFT                    (16U)
/*! DOWN_H - This bit is 1 when the H counter is counting down. Hardware sets this bit when the
 *    counter is counting, a counter limit condition occurs, and BIDIR is 1. Hardware clears this bit
 *    when the counter is counting down and a limit condition occurs or when the counter reaches 0.
 */
#define SCT_CTRL_DOWN_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_DOWN_H_SHIFT)) & SCT_CTRL_DOWN_H_MASK)
#define SCT_CTRL_STOP_H_MASK                     (0x20000U)
#define SCT_CTRL_STOP_H_SHIFT                    (17U)
/*! STOP_H - When this bit is 1 and HALT is 0, the H counter does not, run but I/O events related to
 *    the counter can occur. If such an event matches the mask in the Start register, this bit is
 *    cleared and counting resumes.
 */
#define SCT_CTRL_STOP_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_STOP_H_SHIFT)) & SCT_CTRL_STOP_H_MASK)
#define SCT_CTRL_HALT_H_MASK                     (0x40000U)
#define SCT_CTRL_HALT_H_SHIFT                    (18U)
/*! HALT_H - When this bit is 1, the H counter does not run and no events can occur. A reset sets
 *    this bit. When the HALT_H bit is one, the STOP_H bit is cleared. It is possible to remove the
 *    halt condition while keeping the SCT in the stop condition (not running) with a single write to
 *    this register to simultaneously clear the HALT bit and set the STOP bit. Once set, this bit
 *    can only be cleared by software to restore counter operation. This bit is set on reset.
 */
#define SCT_CTRL_HALT_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_HALT_H_SHIFT)) & SCT_CTRL_HALT_H_MASK)
#define SCT_CTRL_CLRCTR_H_MASK                   (0x80000U)
#define SCT_CTRL_CLRCTR_H_SHIFT                  (19U)
/*! CLRCTR_H - Writing a 1 to this bit clears the H counter. This bit always reads as 0.
 */
#define SCT_CTRL_CLRCTR_H(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_CLRCTR_H_SHIFT)) & SCT_CTRL_CLRCTR_H_MASK)
#define SCT_CTRL_BIDIR_H_MASK                    (0x100000U)
#define SCT_CTRL_BIDIR_H_SHIFT                   (20U)
/*! BIDIR_H - Direction select
 *  0b0..The H counter counts up to its limit condition, then is cleared to zero.
 *  0b1..The H counter counts up to its limit, then counts down to a limit condition or to 0.
 */
#define SCT_CTRL_BIDIR_H(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_BIDIR_H_SHIFT)) & SCT_CTRL_BIDIR_H_MASK)
#define SCT_CTRL_PRE_H_MASK                      (0x1FE00000U)
#define SCT_CTRL_PRE_H_SHIFT                     (21U)
/*! PRE_H - Specifies the factor by which the SCT clock is prescaled to produce the H counter clock.
 *    The counter clock is clocked at the rate of the SCT clock divided by PRELH+1. Clear the
 *    counter (by writing a 1 to the CLRCTR bit) whenever changing the PRE value.
 */
#define SCT_CTRL_PRE_H(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CTRL_PRE_H_SHIFT)) & SCT_CTRL_PRE_H_MASK)
/*! @} */

/*! @name LIMITL - SCT_LIMITL register */
/*! @{ */
#define SCT_LIMITL_LIMITL_MASK                   (0xFFFFU)
#define SCT_LIMITL_LIMITL_SHIFT                  (0U)
#define SCT_LIMITL_LIMITL(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_LIMITL_LIMITL_SHIFT)) & SCT_LIMITL_LIMITL_MASK)
/*! @} */

/*! @name LIMITH - SCT_LIMITH register */
/*! @{ */
#define SCT_LIMITH_LIMITH_MASK                   (0xFFFFU)
#define SCT_LIMITH_LIMITH_SHIFT                  (0U)
#define SCT_LIMITH_LIMITH(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_LIMITH_LIMITH_SHIFT)) & SCT_LIMITH_LIMITH_MASK)
/*! @} */

/*! @name LIMIT - SCT limit event select register */
/*! @{ */
#define SCT_LIMIT_LIMMSK_L_MASK                  (0xFFFFU)
#define SCT_LIMIT_LIMMSK_L_SHIFT                 (0U)
/*! LIMMSK_L - If bit n is one, event n is used as a counter limit for the L or unified counter
 *    (event 0 = bit 0, event 1 = bit 1, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_LIMIT_LIMMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_LIMIT_LIMMSK_L_SHIFT)) & SCT_LIMIT_LIMMSK_L_MASK)
#define SCT_LIMIT_LIMMSK_H_MASK                  (0xFFFF0000U)
#define SCT_LIMIT_LIMMSK_H_SHIFT                 (16U)
/*! LIMMSK_H - If bit n is one, event n is used as a counter limit for the H counter (event 0 = bit
 *    16, event 1 = bit 17, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_LIMIT_LIMMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_LIMIT_LIMMSK_H_SHIFT)) & SCT_LIMIT_LIMMSK_H_MASK)
/*! @} */

/*! @name HALTL - SCT_HALTL register */
/*! @{ */
#define SCT_HALTL_HALTL_MASK                     (0xFFFFU)
#define SCT_HALTL_HALTL_SHIFT                    (0U)
#define SCT_HALTL_HALTL(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_HALTL_HALTL_SHIFT)) & SCT_HALTL_HALTL_MASK)
/*! @} */

/*! @name HALTH - SCT_HALTH register */
/*! @{ */
#define SCT_HALTH_HALTH_MASK                     (0xFFFFU)
#define SCT_HALTH_HALTH_SHIFT                    (0U)
#define SCT_HALTH_HALTH(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_HALTH_HALTH_SHIFT)) & SCT_HALTH_HALTH_MASK)
/*! @} */

/*! @name HALT - SCT halt event select register */
/*! @{ */
#define SCT_HALT_HALTMSK_L_MASK                  (0xFFFFU)
#define SCT_HALT_HALTMSK_L_SHIFT                 (0U)
/*! HALTMSK_L - If bit n is one, event n sets the HALT_L bit in the CTRL register (event 0 = bit 0,
 *    event 1 = bit 1, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_HALT_HALTMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_HALT_HALTMSK_L_SHIFT)) & SCT_HALT_HALTMSK_L_MASK)
#define SCT_HALT_HALTMSK_H_MASK                  (0xFFFF0000U)
#define SCT_HALT_HALTMSK_H_SHIFT                 (16U)
/*! HALTMSK_H - If bit n is one, event n sets the HALT_H bit in the CTRL register (event 0 = bit 16,
 *    event 1 = bit 17, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_HALT_HALTMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_HALT_HALTMSK_H_SHIFT)) & SCT_HALT_HALTMSK_H_MASK)
/*! @} */

/*! @name STOPL - SCT_STOPL register */
/*! @{ */
#define SCT_STOPL_STOPL_MASK                     (0xFFFFU)
#define SCT_STOPL_STOPL_SHIFT                    (0U)
#define SCT_STOPL_STOPL(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_STOPL_STOPL_SHIFT)) & SCT_STOPL_STOPL_MASK)
/*! @} */

/*! @name STOPH - SCT_STOPH register */
/*! @{ */
#define SCT_STOPH_STOPH_MASK                     (0xFFFFU)
#define SCT_STOPH_STOPH_SHIFT                    (0U)
#define SCT_STOPH_STOPH(x)                       (((uint16_t)(((uint16_t)(x)) << SCT_STOPH_STOPH_SHIFT)) & SCT_STOPH_STOPH_MASK)
/*! @} */

/*! @name STOP - SCT stop event select register */
/*! @{ */
#define SCT_STOP_STOPMSK_L_MASK                  (0xFFFFU)
#define SCT_STOP_STOPMSK_L_SHIFT                 (0U)
/*! STOPMSK_L - If bit n is one, event n sets the STOP_L bit in the CTRL register (event 0 = bit 0,
 *    event 1 = bit 1, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_STOP_STOPMSK_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_STOP_STOPMSK_L_SHIFT)) & SCT_STOP_STOPMSK_L_MASK)
#define SCT_STOP_STOPMSK_H_MASK                  (0xFFFF0000U)
#define SCT_STOP_STOPMSK_H_SHIFT                 (16U)
/*! STOPMSK_H - If bit n is one, event n sets the STOP_H bit in the CTRL register (event 0 = bit 16,
 *    event 1 = bit 17, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_STOP_STOPMSK_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_STOP_STOPMSK_H_SHIFT)) & SCT_STOP_STOPMSK_H_MASK)
/*! @} */

/*! @name STARTL - SCT_STARTL register */
/*! @{ */
#define SCT_STARTL_STARTL_MASK                   (0xFFFFU)
#define SCT_STARTL_STARTL_SHIFT                  (0U)
#define SCT_STARTL_STARTL(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_STARTL_STARTL_SHIFT)) & SCT_STARTL_STARTL_MASK)
/*! @} */

/*! @name STARTH - SCT_STARTH register */
/*! @{ */
#define SCT_STARTH_STARTH_MASK                   (0xFFFFU)
#define SCT_STARTH_STARTH_SHIFT                  (0U)
#define SCT_STARTH_STARTH(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_STARTH_STARTH_SHIFT)) & SCT_STARTH_STARTH_MASK)
/*! @} */

/*! @name START - SCT start event select register */
/*! @{ */
#define SCT_START_STARTMSK_L_MASK                (0xFFFFU)
#define SCT_START_STARTMSK_L_SHIFT               (0U)
/*! STARTMSK_L - If bit n is one, event n clears the STOP_L bit in the CTRL register (event 0 = bit
 *    0, event 1 = bit 1, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_START_STARTMSK_L(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_START_STARTMSK_L_SHIFT)) & SCT_START_STARTMSK_L_MASK)
#define SCT_START_STARTMSK_H_MASK                (0xFFFF0000U)
#define SCT_START_STARTMSK_H_SHIFT               (16U)
/*! STARTMSK_H - If bit n is one, event n clears the STOP_H bit in the CTRL register (event 0 = bit
 *    16, event 1 = bit 17, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_START_STARTMSK_H(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_START_STARTMSK_H_SHIFT)) & SCT_START_STARTMSK_H_MASK)
/*! @} */

/*! @name COUNTL - SCT_COUNTL register */
/*! @{ */
#define SCT_COUNTL_COUNTL_MASK                   (0xFFFFU)
#define SCT_COUNTL_COUNTL_SHIFT                  (0U)
#define SCT_COUNTL_COUNTL(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_COUNTL_COUNTL_SHIFT)) & SCT_COUNTL_COUNTL_MASK)
/*! @} */

/*! @name COUNTH - SCT_COUNTH register */
/*! @{ */
#define SCT_COUNTH_COUNTH_MASK                   (0xFFFFU)
#define SCT_COUNTH_COUNTH_SHIFT                  (0U)
#define SCT_COUNTH_COUNTH(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_COUNTH_COUNTH_SHIFT)) & SCT_COUNTH_COUNTH_MASK)
/*! @} */

/*! @name COUNT - SCT counter register */
/*! @{ */
#define SCT_COUNT_CTR_L_MASK                     (0xFFFFU)
#define SCT_COUNT_CTR_L_SHIFT                    (0U)
/*! CTR_L - When UNIFY = 0, read or write the 16-bit L counter value. When UNIFY = 1, read or write
 *    the lower 16 bits of the 32-bit unified counter.
 */
#define SCT_COUNT_CTR_L(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_COUNT_CTR_L_SHIFT)) & SCT_COUNT_CTR_L_MASK)
#define SCT_COUNT_CTR_H_MASK                     (0xFFFF0000U)
#define SCT_COUNT_CTR_H_SHIFT                    (16U)
/*! CTR_H - When UNIFY = 0, read or write the 16-bit H counter value. When UNIFY = 1, read or write
 *    the upper 16 bits of the 32-bit unified counter.
 */
#define SCT_COUNT_CTR_H(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_COUNT_CTR_H_SHIFT)) & SCT_COUNT_CTR_H_MASK)
/*! @} */

/*! @name STATEL - SCT_STATEL register */
/*! @{ */
#define SCT_STATEL_STATEL_MASK                   (0xFFFFU)
#define SCT_STATEL_STATEL_SHIFT                  (0U)
#define SCT_STATEL_STATEL(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_STATEL_STATEL_SHIFT)) & SCT_STATEL_STATEL_MASK)
/*! @} */

/*! @name STATEH - SCT_STATEH register */
/*! @{ */
#define SCT_STATEH_STATEH_MASK                   (0xFFFFU)
#define SCT_STATEH_STATEH_SHIFT                  (0U)
#define SCT_STATEH_STATEH(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_STATEH_STATEH_SHIFT)) & SCT_STATEH_STATEH_MASK)
/*! @} */

/*! @name STATE - SCT state register */
/*! @{ */
#define SCT_STATE_STATE_L_MASK                   (0x1FU)
#define SCT_STATE_STATE_L_SHIFT                  (0U)
/*! STATE_L - State variable.
 */
#define SCT_STATE_STATE_L(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_STATE_STATE_L_SHIFT)) & SCT_STATE_STATE_L_MASK)
#define SCT_STATE_STATE_H_MASK                   (0x1F0000U)
#define SCT_STATE_STATE_H_SHIFT                  (16U)
/*! STATE_H - State variable.
 */
#define SCT_STATE_STATE_H(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_STATE_STATE_H_SHIFT)) & SCT_STATE_STATE_H_MASK)
/*! @} */

/*! @name INPUT - SCT input register */
/*! @{ */
#define SCT_INPUT_AIN0_MASK                      (0x1U)
#define SCT_INPUT_AIN0_SHIFT                     (0U)
/*! AIN0 - Input 0 state. Input 0 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN0(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN0_SHIFT)) & SCT_INPUT_AIN0_MASK)
#define SCT_INPUT_AIN1_MASK                      (0x2U)
#define SCT_INPUT_AIN1_SHIFT                     (1U)
/*! AIN1 - Input 1 state. Input 1 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN1(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN1_SHIFT)) & SCT_INPUT_AIN1_MASK)
#define SCT_INPUT_AIN2_MASK                      (0x4U)
#define SCT_INPUT_AIN2_SHIFT                     (2U)
/*! AIN2 - Input 2 state. Input 2 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN2(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN2_SHIFT)) & SCT_INPUT_AIN2_MASK)
#define SCT_INPUT_AIN3_MASK                      (0x8U)
#define SCT_INPUT_AIN3_SHIFT                     (3U)
/*! AIN3 - Input 3 state. Input 3 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN3(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN3_SHIFT)) & SCT_INPUT_AIN3_MASK)
#define SCT_INPUT_AIN4_MASK                      (0x10U)
#define SCT_INPUT_AIN4_SHIFT                     (4U)
/*! AIN4 - Input 4 state. Input 4 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN4(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN4_SHIFT)) & SCT_INPUT_AIN4_MASK)
#define SCT_INPUT_AIN5_MASK                      (0x20U)
#define SCT_INPUT_AIN5_SHIFT                     (5U)
/*! AIN5 - Input 5 state. Input 5 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN5(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN5_SHIFT)) & SCT_INPUT_AIN5_MASK)
#define SCT_INPUT_AIN6_MASK                      (0x40U)
#define SCT_INPUT_AIN6_SHIFT                     (6U)
/*! AIN6 - Input 6 state. Input 6 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN6(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN6_SHIFT)) & SCT_INPUT_AIN6_MASK)
#define SCT_INPUT_AIN7_MASK                      (0x80U)
#define SCT_INPUT_AIN7_SHIFT                     (7U)
/*! AIN7 - Input 7 state. Input 7 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN7(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN7_SHIFT)) & SCT_INPUT_AIN7_MASK)
#define SCT_INPUT_AIN8_MASK                      (0x100U)
#define SCT_INPUT_AIN8_SHIFT                     (8U)
/*! AIN8 - Input 8 state. Input 8 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN8(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN8_SHIFT)) & SCT_INPUT_AIN8_MASK)
#define SCT_INPUT_AIN9_MASK                      (0x200U)
#define SCT_INPUT_AIN9_SHIFT                     (9U)
/*! AIN9 - Input 9 state. Input 9 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN9(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN9_SHIFT)) & SCT_INPUT_AIN9_MASK)
#define SCT_INPUT_AIN10_MASK                     (0x400U)
#define SCT_INPUT_AIN10_SHIFT                    (10U)
/*! AIN10 - Input 10 state. Input 10 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN10(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN10_SHIFT)) & SCT_INPUT_AIN10_MASK)
#define SCT_INPUT_AIN11_MASK                     (0x800U)
#define SCT_INPUT_AIN11_SHIFT                    (11U)
/*! AIN11 - Input 11 state. Input 11 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN11(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN11_SHIFT)) & SCT_INPUT_AIN11_MASK)
#define SCT_INPUT_AIN12_MASK                     (0x1000U)
#define SCT_INPUT_AIN12_SHIFT                    (12U)
/*! AIN12 - Input 12 state. Input 12 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN12(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN12_SHIFT)) & SCT_INPUT_AIN12_MASK)
#define SCT_INPUT_AIN13_MASK                     (0x2000U)
#define SCT_INPUT_AIN13_SHIFT                    (13U)
/*! AIN13 - Input 13 state. Input 13 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN13(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN13_SHIFT)) & SCT_INPUT_AIN13_MASK)
#define SCT_INPUT_AIN14_MASK                     (0x4000U)
#define SCT_INPUT_AIN14_SHIFT                    (14U)
/*! AIN14 - Input 14 state. Input 14 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN14(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN14_SHIFT)) & SCT_INPUT_AIN14_MASK)
#define SCT_INPUT_AIN15_MASK                     (0x8000U)
#define SCT_INPUT_AIN15_SHIFT                    (15U)
/*! AIN15 - Input 15 state. Input 15 state on the last SCT clock edge.
 */
#define SCT_INPUT_AIN15(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_AIN15_SHIFT)) & SCT_INPUT_AIN15_MASK)
#define SCT_INPUT_SIN0_MASK                      (0x10000U)
#define SCT_INPUT_SIN0_SHIFT                     (16U)
/*! SIN0 - Input 0 state. Input 0 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN0(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN0_SHIFT)) & SCT_INPUT_SIN0_MASK)
#define SCT_INPUT_SIN1_MASK                      (0x20000U)
#define SCT_INPUT_SIN1_SHIFT                     (17U)
/*! SIN1 - Input 1 state. Input 1 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN1(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN1_SHIFT)) & SCT_INPUT_SIN1_MASK)
#define SCT_INPUT_SIN2_MASK                      (0x40000U)
#define SCT_INPUT_SIN2_SHIFT                     (18U)
/*! SIN2 - Input 2 state. Input 2 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN2(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN2_SHIFT)) & SCT_INPUT_SIN2_MASK)
#define SCT_INPUT_SIN3_MASK                      (0x80000U)
#define SCT_INPUT_SIN3_SHIFT                     (19U)
/*! SIN3 - Input 3 state. Input 3 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN3(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN3_SHIFT)) & SCT_INPUT_SIN3_MASK)
#define SCT_INPUT_SIN4_MASK                      (0x100000U)
#define SCT_INPUT_SIN4_SHIFT                     (20U)
/*! SIN4 - Input 4 state. Input 4 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN4(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN4_SHIFT)) & SCT_INPUT_SIN4_MASK)
#define SCT_INPUT_SIN5_MASK                      (0x200000U)
#define SCT_INPUT_SIN5_SHIFT                     (21U)
/*! SIN5 - Input 5 state. Input 5 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN5(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN5_SHIFT)) & SCT_INPUT_SIN5_MASK)
#define SCT_INPUT_SIN6_MASK                      (0x400000U)
#define SCT_INPUT_SIN6_SHIFT                     (22U)
/*! SIN6 - Input 6 state. Input 6 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN6(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN6_SHIFT)) & SCT_INPUT_SIN6_MASK)
#define SCT_INPUT_SIN7_MASK                      (0x800000U)
#define SCT_INPUT_SIN7_SHIFT                     (23U)
/*! SIN7 - Input 7 state. Input 7 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN7(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN7_SHIFT)) & SCT_INPUT_SIN7_MASK)
#define SCT_INPUT_SIN8_MASK                      (0x1000000U)
#define SCT_INPUT_SIN8_SHIFT                     (24U)
/*! SIN8 - Input 8 state. Input 8 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN8(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN8_SHIFT)) & SCT_INPUT_SIN8_MASK)
#define SCT_INPUT_SIN9_MASK                      (0x2000000U)
#define SCT_INPUT_SIN9_SHIFT                     (25U)
/*! SIN9 - Input 9 state. Input 9 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN9(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN9_SHIFT)) & SCT_INPUT_SIN9_MASK)
#define SCT_INPUT_SIN10_MASK                     (0x4000000U)
#define SCT_INPUT_SIN10_SHIFT                    (26U)
/*! SIN10 - Input 10 state. Input 10 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN10(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN10_SHIFT)) & SCT_INPUT_SIN10_MASK)
#define SCT_INPUT_SIN11_MASK                     (0x8000000U)
#define SCT_INPUT_SIN11_SHIFT                    (27U)
/*! SIN11 - Input 11 state. Input 11 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN11(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN11_SHIFT)) & SCT_INPUT_SIN11_MASK)
#define SCT_INPUT_SIN12_MASK                     (0x10000000U)
#define SCT_INPUT_SIN12_SHIFT                    (28U)
/*! SIN12 - Input 12 state. Input 12 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN12(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN12_SHIFT)) & SCT_INPUT_SIN12_MASK)
#define SCT_INPUT_SIN13_MASK                     (0x20000000U)
#define SCT_INPUT_SIN13_SHIFT                    (29U)
/*! SIN13 - Input 13 state. Input 13 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN13(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN13_SHIFT)) & SCT_INPUT_SIN13_MASK)
#define SCT_INPUT_SIN14_MASK                     (0x40000000U)
#define SCT_INPUT_SIN14_SHIFT                    (30U)
/*! SIN14 - Input 14 state. Input 14 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN14(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN14_SHIFT)) & SCT_INPUT_SIN14_MASK)
#define SCT_INPUT_SIN15_MASK                     (0x80000000U)
#define SCT_INPUT_SIN15_SHIFT                    (31U)
/*! SIN15 - Input 15 state. Input 15 state following the synchronization specified by INSYNC.
 */
#define SCT_INPUT_SIN15(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_INPUT_SIN15_SHIFT)) & SCT_INPUT_SIN15_MASK)
/*! @} */

/*! @name REGMODEL - SCT_REGMODEL register */
/*! @{ */
#define SCT_REGMODEL_REGMODEL_MASK               (0xFFFFU)
#define SCT_REGMODEL_REGMODEL_SHIFT              (0U)
#define SCT_REGMODEL_REGMODEL(x)                 (((uint16_t)(((uint16_t)(x)) << SCT_REGMODEL_REGMODEL_SHIFT)) & SCT_REGMODEL_REGMODEL_MASK)
/*! @} */

/*! @name REGMODEH - SCT_REGMODEH register */
/*! @{ */
#define SCT_REGMODEH_REGMODEH_MASK               (0xFFFFU)
#define SCT_REGMODEH_REGMODEH_SHIFT              (0U)
#define SCT_REGMODEH_REGMODEH(x)                 (((uint16_t)(((uint16_t)(x)) << SCT_REGMODEH_REGMODEH_SHIFT)) & SCT_REGMODEH_REGMODEH_MASK)
/*! @} */

/*! @name REGMODE - SCT match/capture mode register */
/*! @{ */
#define SCT_REGMODE_REGMOD_L_MASK                (0xFFFFU)
#define SCT_REGMODE_REGMOD_L_SHIFT               (0U)
/*! REGMOD_L - Each bit controls one match/capture register (register 0 = bit 0, register 1 = bit 1,
 *    etc.). The number of bits = number of match/captures in this SCT. 0 = register operates as
 *    match register. 1 = register operates as capture register.
 */
#define SCT_REGMODE_REGMOD_L(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_REGMODE_REGMOD_L_SHIFT)) & SCT_REGMODE_REGMOD_L_MASK)
#define SCT_REGMODE_REGMOD_H_MASK                (0xFFFF0000U)
#define SCT_REGMODE_REGMOD_H_SHIFT               (16U)
/*! REGMOD_H - Each bit controls one match/capture register (register 0 = bit 16, register 1 = bit
 *    17, etc.). The number of bits = number of match/captures in this SCT. 0 = register operates as
 *    match registers. 1 = register operates as capture registers.
 */
#define SCT_REGMODE_REGMOD_H(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_REGMODE_REGMOD_H_SHIFT)) & SCT_REGMODE_REGMOD_H_MASK)
/*! @} */

/*! @name OUTPUT - SCT output register */
/*! @{ */
#define SCT_OUTPUT_OUT_MASK                      (0xFFFFU)
#define SCT_OUTPUT_OUT_SHIFT                     (0U)
/*! OUT - Writing a 1 to bit n forces the corresponding output HIGH. Writing a 0 forces the
 *    corresponding output LOW (output 0 = bit 0, output 1 = bit 1, etc.). The number of bits = number of
 *    outputs in this SCT.
 */
#define SCT_OUTPUT_OUT(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUT_OUT_SHIFT)) & SCT_OUTPUT_OUT_MASK)
/*! @} */

/*! @name OUTPUTDIRCTRL - SCT output counter direction control register */
/*! @{ */
#define SCT_OUTPUTDIRCTRL_SETCLR0_MASK           (0x3U)
#define SCT_OUTPUTDIRCTRL_SETCLR0_SHIFT          (0U)
/*! SETCLR0 - Set/clear operation on output 0. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR0(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR0_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR0_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR1_MASK           (0xCU)
#define SCT_OUTPUTDIRCTRL_SETCLR1_SHIFT          (2U)
/*! SETCLR1 - Set/clear operation on output 1. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR1(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR1_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR1_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR2_MASK           (0x30U)
#define SCT_OUTPUTDIRCTRL_SETCLR2_SHIFT          (4U)
/*! SETCLR2 - Set/clear operation on output 2. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR2(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR2_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR2_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR3_MASK           (0xC0U)
#define SCT_OUTPUTDIRCTRL_SETCLR3_SHIFT          (6U)
/*! SETCLR3 - Set/clear operation on output 3. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR3(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR3_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR3_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR4_MASK           (0x300U)
#define SCT_OUTPUTDIRCTRL_SETCLR4_SHIFT          (8U)
/*! SETCLR4 - Set/clear operation on output 4. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR4(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR4_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR4_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR5_MASK           (0xC00U)
#define SCT_OUTPUTDIRCTRL_SETCLR5_SHIFT          (10U)
/*! SETCLR5 - Set/clear operation on output 5. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR5(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR5_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR5_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR6_MASK           (0x3000U)
#define SCT_OUTPUTDIRCTRL_SETCLR6_SHIFT          (12U)
/*! SETCLR6 - Set/clear operation on output 6. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR6(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR6_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR6_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR7_MASK           (0xC000U)
#define SCT_OUTPUTDIRCTRL_SETCLR7_SHIFT          (14U)
/*! SETCLR7 - Set/clear operation on output 7. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR7(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR7_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR7_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR8_MASK           (0x30000U)
#define SCT_OUTPUTDIRCTRL_SETCLR8_SHIFT          (16U)
/*! SETCLR8 - Set/clear operation on output 8. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR8(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR8_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR8_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR9_MASK           (0xC0000U)
#define SCT_OUTPUTDIRCTRL_SETCLR9_SHIFT          (18U)
/*! SETCLR9 - Set/clear operation on output 9. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR9(x)             (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR9_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR9_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR10_MASK          (0x300000U)
#define SCT_OUTPUTDIRCTRL_SETCLR10_SHIFT         (20U)
/*! SETCLR10 - Set/clear operation on output 10. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR10(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR10_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR10_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR11_MASK          (0xC00000U)
#define SCT_OUTPUTDIRCTRL_SETCLR11_SHIFT         (22U)
/*! SETCLR11 - Set/clear operation on output 11. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR11(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR11_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR11_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR12_MASK          (0x3000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR12_SHIFT         (24U)
/*! SETCLR12 - Set/clear operation on output 12. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR12(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR12_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR12_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR13_MASK          (0xC000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR13_SHIFT         (26U)
/*! SETCLR13 - Set/clear operation on output 13. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR13(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR13_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR13_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR14_MASK          (0x30000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR14_SHIFT         (28U)
/*! SETCLR14 - Set/clear operation on output 14. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR14(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR14_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR14_MASK)
#define SCT_OUTPUTDIRCTRL_SETCLR15_MASK          (0xC0000000U)
#define SCT_OUTPUTDIRCTRL_SETCLR15_SHIFT         (30U)
/*! SETCLR15 - Set/clear operation on output 15. Value 0x3 is reserved. Do not program this value.
 *  0b00..Set and clear do not depend on the direction of any counter.
 *  0b01..Set and clear are reversed when counter L or the unified counter is counting down.
 *  0b10..Set and clear are reversed when counter H is counting down. Do not use if UNIFY = 1.
 */
#define SCT_OUTPUTDIRCTRL_SETCLR15(x)            (((uint32_t)(((uint32_t)(x)) << SCT_OUTPUTDIRCTRL_SETCLR15_SHIFT)) & SCT_OUTPUTDIRCTRL_SETCLR15_MASK)
/*! @} */

/*! @name RES - SCT conflict resolution register */
/*! @{ */
#define SCT_RES_O0RES_MASK                       (0x3U)
#define SCT_RES_O0RES_SHIFT                      (0U)
/*! O0RES - Effect of simultaneous set and clear on output 0.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR0 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR0 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O0RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O0RES_SHIFT)) & SCT_RES_O0RES_MASK)
#define SCT_RES_O1RES_MASK                       (0xCU)
#define SCT_RES_O1RES_SHIFT                      (2U)
/*! O1RES - Effect of simultaneous set and clear on output 1.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR1 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR1 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O1RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O1RES_SHIFT)) & SCT_RES_O1RES_MASK)
#define SCT_RES_O2RES_MASK                       (0x30U)
#define SCT_RES_O2RES_SHIFT                      (4U)
/*! O2RES - Effect of simultaneous set and clear on output 2.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR2 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output n (or set based on the SETCLR2 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O2RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O2RES_SHIFT)) & SCT_RES_O2RES_MASK)
#define SCT_RES_O3RES_MASK                       (0xC0U)
#define SCT_RES_O3RES_SHIFT                      (6U)
/*! O3RES - Effect of simultaneous set and clear on output 3.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR3 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR3 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O3RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O3RES_SHIFT)) & SCT_RES_O3RES_MASK)
#define SCT_RES_O4RES_MASK                       (0x300U)
#define SCT_RES_O4RES_SHIFT                      (8U)
/*! O4RES - Effect of simultaneous set and clear on output 4.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR4 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR4 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O4RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O4RES_SHIFT)) & SCT_RES_O4RES_MASK)
#define SCT_RES_O5RES_MASK                       (0xC00U)
#define SCT_RES_O5RES_SHIFT                      (10U)
/*! O5RES - Effect of simultaneous set and clear on output 5.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR5 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR5 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O5RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O5RES_SHIFT)) & SCT_RES_O5RES_MASK)
#define SCT_RES_O6RES_MASK                       (0x3000U)
#define SCT_RES_O6RES_SHIFT                      (12U)
/*! O6RES - Effect of simultaneous set and clear on output 6.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR6 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR6 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O6RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O6RES_SHIFT)) & SCT_RES_O6RES_MASK)
#define SCT_RES_O7RES_MASK                       (0xC000U)
#define SCT_RES_O7RES_SHIFT                      (14U)
/*! O7RES - Effect of simultaneous set and clear on output 7.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR7 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output n (or set based on the SETCLR7 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O7RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O7RES_SHIFT)) & SCT_RES_O7RES_MASK)
#define SCT_RES_O8RES_MASK                       (0x30000U)
#define SCT_RES_O8RES_SHIFT                      (16U)
/*! O8RES - Effect of simultaneous set and clear on output 8.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR8 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR8 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O8RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O8RES_SHIFT)) & SCT_RES_O8RES_MASK)
#define SCT_RES_O9RES_MASK                       (0xC0000U)
#define SCT_RES_O9RES_SHIFT                      (18U)
/*! O9RES - Effect of simultaneous set and clear on output 9.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR9 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR9 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O9RES(x)                         (((uint32_t)(((uint32_t)(x)) << SCT_RES_O9RES_SHIFT)) & SCT_RES_O9RES_MASK)
#define SCT_RES_O10RES_MASK                      (0x300000U)
#define SCT_RES_O10RES_SHIFT                     (20U)
/*! O10RES - Effect of simultaneous set and clear on output 10.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR10 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR10 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O10RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O10RES_SHIFT)) & SCT_RES_O10RES_MASK)
#define SCT_RES_O11RES_MASK                      (0xC00000U)
#define SCT_RES_O11RES_SHIFT                     (22U)
/*! O11RES - Effect of simultaneous set and clear on output 11.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR11 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR11 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O11RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O11RES_SHIFT)) & SCT_RES_O11RES_MASK)
#define SCT_RES_O12RES_MASK                      (0x3000000U)
#define SCT_RES_O12RES_SHIFT                     (24U)
/*! O12RES - Effect of simultaneous set and clear on output 12.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR12 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR12 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O12RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O12RES_SHIFT)) & SCT_RES_O12RES_MASK)
#define SCT_RES_O13RES_MASK                      (0xC000000U)
#define SCT_RES_O13RES_SHIFT                     (26U)
/*! O13RES - Effect of simultaneous set and clear on output 13.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR13 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR13 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O13RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O13RES_SHIFT)) & SCT_RES_O13RES_MASK)
#define SCT_RES_O14RES_MASK                      (0x30000000U)
#define SCT_RES_O14RES_SHIFT                     (28U)
/*! O14RES - Effect of simultaneous set and clear on output 14.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR14 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR14 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O14RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O14RES_SHIFT)) & SCT_RES_O14RES_MASK)
#define SCT_RES_O15RES_MASK                      (0xC0000000U)
#define SCT_RES_O15RES_SHIFT                     (30U)
/*! O15RES - Effect of simultaneous set and clear on output 15.
 *  0b00..No change.
 *  0b01..Set output (or clear based on the SETCLR15 field in the OUTPUTDIRCTRL register).
 *  0b10..Clear output (or set based on the SETCLR15 field).
 *  0b11..Toggle output.
 */
#define SCT_RES_O15RES(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_RES_O15RES_SHIFT)) & SCT_RES_O15RES_MASK)
/*! @} */

/*! @name DMAREQ0 - SCT DMA request 0 register */
/*! @{ */
#define SCT_DMAREQ0_DEV_0_MASK                   (0xFFFFU)
#define SCT_DMAREQ0_DEV_0_SHIFT                  (0U)
/*! DEV_0 - If bit n is one, event n triggers DMA request 0 (event 0 = bit 0, event 1 = bit 1,
 *    etc.). The number of bits = number of events in this SCT.
 */
#define SCT_DMAREQ0_DEV_0(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ0_DEV_0_SHIFT)) & SCT_DMAREQ0_DEV_0_MASK)
#define SCT_DMAREQ0_DRL0_MASK                    (0x40000000U)
#define SCT_DMAREQ0_DRL0_SHIFT                   (30U)
/*! DRL0 - A 1 in this bit triggers DMA request 0 when it loads the MATCH_L/Unified registers from the RELOAD_L/Unified registers.
 */
#define SCT_DMAREQ0_DRL0(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ0_DRL0_SHIFT)) & SCT_DMAREQ0_DRL0_MASK)
#define SCT_DMAREQ0_DRQ0_MASK                    (0x80000000U)
#define SCT_DMAREQ0_DRQ0_SHIFT                   (31U)
/*! DRQ0 - This read-only bit indicates the state of DMA Request 0. Note that if the related DMA
 *    channel is enabled and properly set up, it is unlikely that software will see this flag, it will
 *    be cleared rapidly by the DMA service. The flag remaining set could point to an issue with DMA
 *    setup.
 */
#define SCT_DMAREQ0_DRQ0(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ0_DRQ0_SHIFT)) & SCT_DMAREQ0_DRQ0_MASK)
/*! @} */

/*! @name DMAREQ1 - SCT DMA request 1 register */
/*! @{ */
#define SCT_DMAREQ1_DEV_1_MASK                   (0xFFFFU)
#define SCT_DMAREQ1_DEV_1_SHIFT                  (0U)
/*! DEV_1 - If bit n is one, event n triggers DMA request 1 (event 0 = bit 0, event 1 = bit 1,
 *    etc.). The number of bits = number of events in this SCT.
 */
#define SCT_DMAREQ1_DEV_1(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ1_DEV_1_SHIFT)) & SCT_DMAREQ1_DEV_1_MASK)
#define SCT_DMAREQ1_DRL1_MASK                    (0x40000000U)
#define SCT_DMAREQ1_DRL1_SHIFT                   (30U)
/*! DRL1 - A 1 in this bit triggers DMA request 1 when it loads the Match L/Unified registers from the Reload L/Unified registers.
 */
#define SCT_DMAREQ1_DRL1(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ1_DRL1_SHIFT)) & SCT_DMAREQ1_DRL1_MASK)
#define SCT_DMAREQ1_DRQ1_MASK                    (0x80000000U)
#define SCT_DMAREQ1_DRQ1_SHIFT                   (31U)
/*! DRQ1 - This read-only bit indicates the state of DMA Request 1. Note that if the related DMA
 *    channel is enabled and properly set up, it is unlikely that software will see this flag, it will
 *    be cleared rapidly by the DMA service. The flag remaining set could point to an issue with DMA
 *    setup.
 */
#define SCT_DMAREQ1_DRQ1(x)                      (((uint32_t)(((uint32_t)(x)) << SCT_DMAREQ1_DRQ1_SHIFT)) & SCT_DMAREQ1_DRQ1_MASK)
/*! @} */

/*! @name EVEN - SCT event interrupt enable register */
/*! @{ */
#define SCT_EVEN_IEN_MASK                        (0xFFFFU)
#define SCT_EVEN_IEN_SHIFT                       (0U)
/*! IEN - The SCT requests an interrupt when bit n of this register and the event flag register are
 *    both one (event 0 = bit 0, event 1 = bit 1, etc.). The number of bits = number of events in
 *    this SCT.
 */
#define SCT_EVEN_IEN(x)                          (((uint32_t)(((uint32_t)(x)) << SCT_EVEN_IEN_SHIFT)) & SCT_EVEN_IEN_MASK)
/*! @} */

/*! @name EVFLAG - SCT event flag register */
/*! @{ */
#define SCT_EVFLAG_FLAG_MASK                     (0xFFFFU)
#define SCT_EVFLAG_FLAG_SHIFT                    (0U)
/*! FLAG - Bit n is one if event n has occurred since reset or a 1 was last written to this bit
 *    (event 0 = bit 0, event 1 = bit 1, etc.). The number of bits = number of events in this SCT.
 */
#define SCT_EVFLAG_FLAG(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_EVFLAG_FLAG_SHIFT)) & SCT_EVFLAG_FLAG_MASK)
/*! @} */

/*! @name CONEN - SCT conflict interrupt enable register */
/*! @{ */
#define SCT_CONEN_NCEN_MASK                      (0xFFFFU)
#define SCT_CONEN_NCEN_SHIFT                     (0U)
/*! NCEN - The SCT requests an interrupt when bit n of this register and the SCT conflict flag
 *    register are both one (output 0 = bit 0, output 1 = bit 1, etc.). The number of bits = number of
 *    outputs in this SCT.
 */
#define SCT_CONEN_NCEN(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CONEN_NCEN_SHIFT)) & SCT_CONEN_NCEN_MASK)
/*! @} */

/*! @name CONFLAG - SCT conflict flag register */
/*! @{ */
#define SCT_CONFLAG_NCFLAG_MASK                  (0xFFFFU)
#define SCT_CONFLAG_NCFLAG_SHIFT                 (0U)
/*! NCFLAG - Bit n is one if a no-change conflict event occurred on output n since reset or a 1 was
 *    last written to this bit (output 0 = bit 0, output 1 = bit 1, etc.). The number of bits =
 *    number of outputs in this SCT.
 */
#define SCT_CONFLAG_NCFLAG(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_NCFLAG_SHIFT)) & SCT_CONFLAG_NCFLAG_MASK)
#define SCT_CONFLAG_BUSERRL_MASK                 (0x40000000U)
#define SCT_CONFLAG_BUSERRL_SHIFT                (30U)
/*! BUSERRL - The most recent bus error from this SCT involved writing CTR L/Unified, STATE
 *    L/Unified, MATCH L/Unified, or the Output register when the L/U counter was not halted. A word write
 *    to certain L and H registers can be half successful and half unsuccessful.
 */
#define SCT_CONFLAG_BUSERRL(x)                   (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_BUSERRL_SHIFT)) & SCT_CONFLAG_BUSERRL_MASK)
#define SCT_CONFLAG_BUSERRH_MASK                 (0x80000000U)
#define SCT_CONFLAG_BUSERRH_SHIFT                (31U)
/*! BUSERRH - The most recent bus error from this SCT involved writing CTR H, STATE H, MATCH H, or
 *    the Output register when the H counter was not halted.
 */
#define SCT_CONFLAG_BUSERRH(x)                   (((uint32_t)(((uint32_t)(x)) << SCT_CONFLAG_BUSERRH_SHIFT)) & SCT_CONFLAG_BUSERRH_MASK)
/*! @} */

/*! @name CAPL - SCT_CAPL register */
/*! @{ */
#define SCT_CAPL_CAPL_MASK                       (0xFFFFU)
#define SCT_CAPL_CAPL_SHIFT                      (0U)
#define SCT_CAPL_CAPL(x)                         (((uint16_t)(((uint16_t)(x)) << SCT_CAPL_CAPL_SHIFT)) & SCT_CAPL_CAPL_MASK)
/*! @} */

/* The count of SCT_CAPL */
#define SCT_CAPL_COUNT                           (10U)

/*! @name CAPH - SCT_CAPH register */
/*! @{ */
#define SCT_CAPH_CAPH_MASK                       (0xFFFFU)
#define SCT_CAPH_CAPH_SHIFT                      (0U)
#define SCT_CAPH_CAPH(x)                         (((uint16_t)(((uint16_t)(x)) << SCT_CAPH_CAPH_SHIFT)) & SCT_CAPH_CAPH_MASK)
/*! @} */

/* The count of SCT_CAPH */
#define SCT_CAPH_COUNT                           (10U)

/*! @name CAP - SCT capture register of capture channel */
/*! @{ */
#define SCT_CAP_CAPn_L_MASK                      (0xFFFFU)
#define SCT_CAP_CAPn_L_SHIFT                     (0U)
/*! CAPn_L - When UNIFY = 0, read the 16-bit counter value at which this register was last captured.
 *    When UNIFY = 1, read the lower 16 bits of the 32-bit value at which this register was last
 *    captured.
 */
#define SCT_CAP_CAPn_L(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CAP_CAPn_L_SHIFT)) & SCT_CAP_CAPn_L_MASK)
#define SCT_CAP_CAPn_H_MASK                      (0xFFFF0000U)
#define SCT_CAP_CAPn_H_SHIFT                     (16U)
/*! CAPn_H - When UNIFY = 0, read the 16-bit counter value at which this register was last captured.
 *    When UNIFY = 1, read the upper 16 bits of the 32-bit value at which this register was last
 *    captured.
 */
#define SCT_CAP_CAPn_H(x)                        (((uint32_t)(((uint32_t)(x)) << SCT_CAP_CAPn_H_SHIFT)) & SCT_CAP_CAPn_H_MASK)
/*! @} */

/* The count of SCT_CAP */
#define SCT_CAP_COUNT                            (10U)

/*! @name MATCHL - SCT_MATCHL register */
/*! @{ */
#define SCT_MATCHL_MATCHL_MASK                   (0xFFFFU)
#define SCT_MATCHL_MATCHL_SHIFT                  (0U)
#define SCT_MATCHL_MATCHL(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_MATCHL_MATCHL_SHIFT)) & SCT_MATCHL_MATCHL_MASK)
/*! @} */

/* The count of SCT_MATCHL */
#define SCT_MATCHL_COUNT                         (10U)

/*! @name MATCHH - SCT_MATCHH register */
/*! @{ */
#define SCT_MATCHH_MATCHH_MASK                   (0xFFFFU)
#define SCT_MATCHH_MATCHH_SHIFT                  (0U)
#define SCT_MATCHH_MATCHH(x)                     (((uint16_t)(((uint16_t)(x)) << SCT_MATCHH_MATCHH_SHIFT)) & SCT_MATCHH_MATCHH_MASK)
/*! @} */

/* The count of SCT_MATCHH */
#define SCT_MATCHH_COUNT                         (10U)

/*! @name MATCH - SCT match value register of match channels */
/*! @{ */
#define SCT_MATCH_MATCHn_L_MASK                  (0xFFFFU)
#define SCT_MATCH_MATCHn_L_SHIFT                 (0U)
/*! MATCHn_L - When UNIFY = 0, read or write the 16-bit value to be compared to the L counter. When
 *    UNIFY = 1, read or write the lower 16 bits of the 32-bit value to be compared to the unified
 *    counter.
 */
#define SCT_MATCH_MATCHn_L(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_MATCH_MATCHn_L_SHIFT)) & SCT_MATCH_MATCHn_L_MASK)
#define SCT_MATCH_MATCHn_H_MASK                  (0xFFFF0000U)
#define SCT_MATCH_MATCHn_H_SHIFT                 (16U)
/*! MATCHn_H - When UNIFY = 0, read or write the 16-bit value to be compared to the H counter. When
 *    UNIFY = 1, read or write the upper 16 bits of the 32-bit value to be compared to the unified
 *    counter.
 */
#define SCT_MATCH_MATCHn_H(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_MATCH_MATCHn_H_SHIFT)) & SCT_MATCH_MATCHn_H_MASK)
/*! @} */

/* The count of SCT_MATCH */
#define SCT_MATCH_COUNT                          (10U)

/*! @name CAPCTRLL - SCT_CAPCTRLL register */
/*! @{ */
#define SCT_CAPCTRLL_CAPCTRLL_MASK               (0xFFFFU)
#define SCT_CAPCTRLL_CAPCTRLL_SHIFT              (0U)
#define SCT_CAPCTRLL_CAPCTRLL(x)                 (((uint16_t)(((uint16_t)(x)) << SCT_CAPCTRLL_CAPCTRLL_SHIFT)) & SCT_CAPCTRLL_CAPCTRLL_MASK)
/*! @} */

/* The count of SCT_CAPCTRLL */
#define SCT_CAPCTRLL_COUNT                       (10U)

/*! @name CAPCTRLH - SCT_CAPCTRLH register */
/*! @{ */
#define SCT_CAPCTRLH_CAPCTRLH_MASK               (0xFFFFU)
#define SCT_CAPCTRLH_CAPCTRLH_SHIFT              (0U)
#define SCT_CAPCTRLH_CAPCTRLH(x)                 (((uint16_t)(((uint16_t)(x)) << SCT_CAPCTRLH_CAPCTRLH_SHIFT)) & SCT_CAPCTRLH_CAPCTRLH_MASK)
/*! @} */

/* The count of SCT_CAPCTRLH */
#define SCT_CAPCTRLH_COUNT                       (10U)

/*! @name CAPCTRL - SCT capture control register */
/*! @{ */
#define SCT_CAPCTRL_CAPCONn_L_MASK               (0xFFFFU)
#define SCT_CAPCTRL_CAPCONn_L_SHIFT              (0U)
/*! CAPCONn_L - If bit m is one, event m causes the CAPn_L (UNIFY = 0) or the CAPn (UNIFY = 1)
 *    register to be loaded (event 0 = bit 0, event 1 = bit 1, etc.). The number of bits = number of
 *    match/captures in this SCT.
 */
#define SCT_CAPCTRL_CAPCONn_L(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CAPCTRL_CAPCONn_L_SHIFT)) & SCT_CAPCTRL_CAPCONn_L_MASK)
#define SCT_CAPCTRL_CAPCONn_H_MASK               (0xFFFF0000U)
#define SCT_CAPCTRL_CAPCONn_H_SHIFT              (16U)
/*! CAPCONn_H - If bit m is one, event m causes the CAPn_H (UNIFY = 0) register to be loaded (event
 *    0 = bit 16, event 1 = bit 17, etc.). The number of bits = number of match/captures in this SCT.
 */
#define SCT_CAPCTRL_CAPCONn_H(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_CAPCTRL_CAPCONn_H_SHIFT)) & SCT_CAPCTRL_CAPCONn_H_MASK)
/*! @} */

/* The count of SCT_CAPCTRL */
#define SCT_CAPCTRL_COUNT                        (10U)

/*! @name MATCHRELL - SCT_MATCHRELL register */
/*! @{ */
#define SCT_MATCHRELL_MATCHRELL_MASK             (0xFFFFU)
#define SCT_MATCHRELL_MATCHRELL_SHIFT            (0U)
#define SCT_MATCHRELL_MATCHRELL(x)               (((uint16_t)(((uint16_t)(x)) << SCT_MATCHRELL_MATCHRELL_SHIFT)) & SCT_MATCHRELL_MATCHRELL_MASK)
/*! @} */

/* The count of SCT_MATCHRELL */
#define SCT_MATCHRELL_COUNT                      (10U)

/*! @name MATCHRELH - SCT_MATCHRELH register */
/*! @{ */
#define SCT_MATCHRELH_MATCHRELH_MASK             (0xFFFFU)
#define SCT_MATCHRELH_MATCHRELH_SHIFT            (0U)
#define SCT_MATCHRELH_MATCHRELH(x)               (((uint16_t)(((uint16_t)(x)) << SCT_MATCHRELH_MATCHRELH_SHIFT)) & SCT_MATCHRELH_MATCHRELH_MASK)
/*! @} */

/* The count of SCT_MATCHRELH */
#define SCT_MATCHRELH_COUNT                      (10U)

/*! @name MATCHREL - SCT match reload value register */
/*! @{ */
#define SCT_MATCHREL_RELOADn_L_MASK              (0xFFFFU)
#define SCT_MATCHREL_RELOADn_L_SHIFT             (0U)
/*! RELOADn_L - When UNIFY = 0, specifies the 16-bit value to be loaded into the MATCHn_L register.
 *    When UNIFY = 1, specifies the lower 16 bits of the 32-bit value to be loaded into the MATCHn
 *    register.
 */
#define SCT_MATCHREL_RELOADn_L(x)                (((uint32_t)(((uint32_t)(x)) << SCT_MATCHREL_RELOADn_L_SHIFT)) & SCT_MATCHREL_RELOADn_L_MASK)
#define SCT_MATCHREL_RELOADn_H_MASK              (0xFFFF0000U)
#define SCT_MATCHREL_RELOADn_H_SHIFT             (16U)
/*! RELOADn_H - When UNIFY = 0, specifies the 16-bit to be loaded into the MATCHn_H register. When
 *    UNIFY = 1, specifies the upper 16 bits of the 32-bit value to be loaded into the MATCHn
 *    register.
 */
#define SCT_MATCHREL_RELOADn_H(x)                (((uint32_t)(((uint32_t)(x)) << SCT_MATCHREL_RELOADn_H_SHIFT)) & SCT_MATCHREL_RELOADn_H_MASK)
/*! @} */

/* The count of SCT_MATCHREL */
#define SCT_MATCHREL_COUNT                       (10U)

/*! @name EV_STATE - SCT event state register 0 */
/*! @{ */
#define SCT_EV_STATE_STATEMSKn_MASK              (0xFFFFU)
#define SCT_EV_STATE_STATEMSKn_SHIFT             (0U)
/*! STATEMSKn - If bit m is one, event n happens in state m of the counter selected by the HEVENT
 *    bit (n = event number, m = state number; state 0 = bit 0, state 1= bit 1, etc.). The number of
 *    bits = number of states in this SCT.
 */
#define SCT_EV_STATE_STATEMSKn(x)                (((uint32_t)(((uint32_t)(x)) << SCT_EV_STATE_STATEMSKn_SHIFT)) & SCT_EV_STATE_STATEMSKn_MASK)
/*! @} */

/* The count of SCT_EV_STATE */
#define SCT_EV_STATE_COUNT                       (10U)

/*! @name EV_CTRL - SCT event control register 0 */
/*! @{ */
#define SCT_EV_CTRL_MATCHSEL_MASK                (0xFU)
#define SCT_EV_CTRL_MATCHSEL_SHIFT               (0U)
/*! MATCHSEL - Selects the Match register associated with this event (if any). A match can occur
 *    only when the counter selected by the HEVENT bit is running.
 */
#define SCT_EV_CTRL_MATCHSEL(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_MATCHSEL_SHIFT)) & SCT_EV_CTRL_MATCHSEL_MASK)
#define SCT_EV_CTRL_HEVENT_MASK                  (0x10U)
#define SCT_EV_CTRL_HEVENT_SHIFT                 (4U)
/*! HEVENT - Select L/H counter. Do not set this bit if UNIFY = 1.
 *  0b0..Selects the L state and the L match register selected by MATCHSEL.
 *  0b1..Selects the H state and the H match register selected by MATCHSEL.
 */
#define SCT_EV_CTRL_HEVENT(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_HEVENT_SHIFT)) & SCT_EV_CTRL_HEVENT_MASK)
#define SCT_EV_CTRL_OUTSEL_MASK                  (0x20U)
#define SCT_EV_CTRL_OUTSEL_SHIFT                 (5U)
/*! OUTSEL - Input/output select
 *  0b0..Selects the inputs selected by IOSEL.
 *  0b1..Selects the outputs selected by IOSEL.
 */
#define SCT_EV_CTRL_OUTSEL(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_OUTSEL_SHIFT)) & SCT_EV_CTRL_OUTSEL_MASK)
#define SCT_EV_CTRL_IOSEL_MASK                   (0x3C0U)
#define SCT_EV_CTRL_IOSEL_SHIFT                  (6U)
/*! IOSEL - Selects the input or output signal number associated with this event (if any). Do not
 *    select an input in this register if CKMODE is 1x. In this case the clock input is an implicit
 *    ingredient of every event.
 */
#define SCT_EV_CTRL_IOSEL(x)                     (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_IOSEL_SHIFT)) & SCT_EV_CTRL_IOSEL_MASK)
#define SCT_EV_CTRL_IOCOND_MASK                  (0xC00U)
#define SCT_EV_CTRL_IOCOND_SHIFT                 (10U)
/*! IOCOND - Selects the I/O condition for event n. (The detection of edges on outputs lag the
 *    conditions that switch the outputs by one SCT clock). In order to guarantee proper edge/state
 *    detection, an input must have a minimum pulse width of at least one SCT clock period .
 *  0b00..LOW
 *  0b01..Rise
 *  0b10..Fall
 *  0b11..HIGH
 */
#define SCT_EV_CTRL_IOCOND(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_IOCOND_SHIFT)) & SCT_EV_CTRL_IOCOND_MASK)
#define SCT_EV_CTRL_COMBMODE_MASK                (0x3000U)
#define SCT_EV_CTRL_COMBMODE_SHIFT               (12U)
/*! COMBMODE - Selects how the specified match and I/O condition are used and combined.
 *  0b00..OR. The event occurs when either the specified match or I/O condition occurs.
 *  0b01..MATCH. Uses the specified match only.
 *  0b10..IO. Uses the specified I/O condition only.
 *  0b11..AND. The event occurs when the specified match and I/O condition occur simultaneously.
 */
#define SCT_EV_CTRL_COMBMODE(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_COMBMODE_SHIFT)) & SCT_EV_CTRL_COMBMODE_MASK)
#define SCT_EV_CTRL_STATELD_MASK                 (0x4000U)
#define SCT_EV_CTRL_STATELD_SHIFT                (14U)
/*! STATELD - This bit controls how the STATEV value modifies the state selected by HEVENT when this
 *    event is the highest-numbered event occurring for that state.
 *  0b0..STATEV value is added into STATE (the carry-out is ignored).
 *  0b1..STATEV value is loaded into STATE.
 */
#define SCT_EV_CTRL_STATELD(x)                   (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_STATELD_SHIFT)) & SCT_EV_CTRL_STATELD_MASK)
#define SCT_EV_CTRL_STATEV_MASK                  (0xF8000U)
#define SCT_EV_CTRL_STATEV_SHIFT                 (15U)
/*! STATEV - This value is loaded into or added to the state selected by HEVENT, depending on
 *    STATELD, when this event is the highest-numbered event occurring for that state. If STATELD and
 *    STATEV are both zero, there is no change to the STATE value.
 */
#define SCT_EV_CTRL_STATEV(x)                    (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_STATEV_SHIFT)) & SCT_EV_CTRL_STATEV_MASK)
#define SCT_EV_CTRL_MATCHMEM_MASK                (0x100000U)
#define SCT_EV_CTRL_MATCHMEM_SHIFT               (20U)
/*! MATCHMEM - If this bit is one and the COMBMODE field specifies a match component to the
 *    triggering of this event, then a match is considered to be active whenever the counter value is
 *    GREATER THAN OR EQUAL TO the value specified in the match register when counting up, LESS THEN OR
 *    EQUAL TO the match value when counting down. If this bit is zero, a match is only be active
 *    during the cycle when the counter is equal to the match value.
 */
#define SCT_EV_CTRL_MATCHMEM(x)                  (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_MATCHMEM_SHIFT)) & SCT_EV_CTRL_MATCHMEM_MASK)
#define SCT_EV_CTRL_DIRECTION_MASK               (0x600000U)
#define SCT_EV_CTRL_DIRECTION_SHIFT              (21U)
/*! DIRECTION - Direction qualifier for event generation. This field only applies when the counters
 *    are operating in BIDIR mode. If BIDIR = 0, the SCT ignores this field. Value 0x3 is reserved.
 *  0b00..Direction independent. This event is triggered regardless of the count direction.
 *  0b01..Counting up. This event is triggered only during up-counting when BIDIR = 1.
 *  0b10..Counting down. This event is triggered only during down-counting when BIDIR = 1.
 */
#define SCT_EV_CTRL_DIRECTION(x)                 (((uint32_t)(((uint32_t)(x)) << SCT_EV_CTRL_DIRECTION_SHIFT)) & SCT_EV_CTRL_DIRECTION_MASK)
/*! @} */

/* The count of SCT_EV_CTRL */
#define SCT_EV_CTRL_COUNT                        (10U)

/*! @name OUT_SET - SCT output 0 set register */
/*! @{ */
#define SCT_OUT_SET_SET_MASK                     (0xFFFFU)
#define SCT_OUT_SET_SET_SHIFT                    (0U)
/*! SET - A 1 in bit m selects event m to set output n (or clear it if SETCLRn = 0x1 or 0x2) output
 *    0 = bit 0, output 1 = bit 1, etc. The number of bits = number of events in this SCT. When the
 *    counter is used in bi-directional mode, it is possible to reverse the action specified by the
 *    output set and clear registers when counting down, See the OUTPUTCTRL register.
 */
#define SCT_OUT_SET_SET(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_OUT_SET_SET_SHIFT)) & SCT_OUT_SET_SET_MASK)
/*! @} */

/* The count of SCT_OUT_SET */
#define SCT_OUT_SET_COUNT                        (8U)

/*! @name OUT_CLR - SCT output 0 clear register */
/*! @{ */
#define SCT_OUT_CLR_CLR_MASK                     (0xFFFFU)
#define SCT_OUT_CLR_CLR_SHIFT                    (0U)
/*! CLR - A 1 in bit m selects event m to clear output n (or set it if SETCLRn = 0x1 or 0x2) event 0
 *    = bit 0, event 1 = bit 1, etc. The number of bits = number of events in this SCT. When the
 *    counter is used in bi-directional mode, it is possible to reverse the action specified by the
 *    output set and clear registers when counting down, See the OUTPUTCTRL register.
 */
#define SCT_OUT_CLR_CLR(x)                       (((uint32_t)(((uint32_t)(x)) << SCT_OUT_CLR_CLR_SHIFT)) & SCT_OUT_CLR_CLR_MASK)
/*! @} */

/* The count of SCT_OUT_CLR */
#define SCT_OUT_CLR_COUNT                        (8U)


/*!
 * @}
 */ /* end of group SCT_Register_Masks */


/* SCT - Peripheral instance base addresses */
/** Peripheral SCT0 base address */
#define SCT0_BASE                                (0x40085000u)
/** Peripheral SCT0 base pointer */
#define SCT0                                     ((SCT_Type *)SCT0_BASE)
/** Array initializer of SCT peripheral base addresses */
#define SCT_BASE_ADDRS                           { SCT0_BASE }
/** Array initializer of SCT peripheral base pointers */
#define SCT_BASE_PTRS                            { SCT0 }
/** Interrupt vectors for the SCT peripheral type */
#define SCT_IRQS                                 { SCT0_IRQn }

/*!
 * @}
 */ /* end of group SCT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[1024];
  __IO uint32_t CFG;                               /**< SPI Configuration register, offset: 0x400 */
  __IO uint32_t DLY;                               /**< SPI Delay register, offset: 0x404 */
  __IO uint32_t STAT;                              /**< SPI Status. Some status flags can be cleared by writing a 1 to that bit position., offset: 0x408 */
  __IO uint32_t INTENSET;                          /**< SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0x40C */
  __O  uint32_t INTENCLR;                          /**< SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared., offset: 0x410 */
       uint8_t RESERVED_1[16];
  __IO uint32_t DIV;                               /**< SPI clock Divider, offset: 0x424 */
  __I  uint32_t INTSTAT;                           /**< SPI Interrupt Status, offset: 0x428 */
       uint8_t RESERVED_2[2516];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
       uint8_t RESERVED_5[12];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
       uint8_t RESERVED_6[12];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
       uint8_t RESERVED_7[440];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name CFG - SPI Configuration register */
/*! @{ */
#define SPI_CFG_ENABLE_MASK                      (0x1U)
#define SPI_CFG_ENABLE_SHIFT                     (0U)
/*! ENABLE - SPI enable.
 *  0b0..Disabled. The SPI is disabled and the internal state machine and counters are reset.
 *  0b1..Enabled. The SPI is enabled for operation.
 */
#define SPI_CFG_ENABLE(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_ENABLE_SHIFT)) & SPI_CFG_ENABLE_MASK)
#define SPI_CFG_MASTER_MASK                      (0x4U)
#define SPI_CFG_MASTER_SHIFT                     (2U)
/*! MASTER - Master mode select.
 *  0b0..Slave mode. The SPI will operate in slave mode. SCK, MOSI, and the SSEL signals are inputs, MISO is an output.
 *  0b1..Master mode. The SPI will operate in master mode. SCK, MOSI, and the SSEL signals are outputs, MISO is an input.
 */
#define SPI_CFG_MASTER(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_MASTER_SHIFT)) & SPI_CFG_MASTER_MASK)
#define SPI_CFG_LSBF_MASK                        (0x8U)
#define SPI_CFG_LSBF_SHIFT                       (3U)
/*! LSBF - LSB First mode enable.
 *  0b0..Standard. Data is transmitted and received in standard MSB first order.
 *  0b1..Reverse. Data is transmitted and received in reverse order (LSB first).
 */
#define SPI_CFG_LSBF(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LSBF_SHIFT)) & SPI_CFG_LSBF_MASK)
#define SPI_CFG_CPHA_MASK                        (0x10U)
#define SPI_CFG_CPHA_SHIFT                       (4U)
/*! CPHA - Clock Phase select.
 *  0b0..Change. The SPI captures serial data on the first clock transition of the transfer (when the clock
 *       changes away from the rest state). Data is changed on the following edge.
 *  0b1..Capture. The SPI changes serial data on the first clock transition of the transfer (when the clock
 *       changes away from the rest state). Data is captured on the following edge.
 */
#define SPI_CFG_CPHA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPHA_SHIFT)) & SPI_CFG_CPHA_MASK)
#define SPI_CFG_CPOL_MASK                        (0x20U)
#define SPI_CFG_CPOL_SHIFT                       (5U)
/*! CPOL - Clock Polarity select.
 *  0b0..Low. The rest state of the clock (between transfers) is low.
 *  0b1..High. The rest state of the clock (between transfers) is high.
 */
#define SPI_CFG_CPOL(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPOL_SHIFT)) & SPI_CFG_CPOL_MASK)
#define SPI_CFG_LOOP_MASK                        (0x80U)
#define SPI_CFG_LOOP_SHIFT                       (7U)
/*! LOOP - Loopback mode enable. Loopback mode applies only to Master mode, and connects transmit
 *    and receive data connected together to allow simple software testing.
 *  0b0..Disabled.
 *  0b1..Enabled.
 */
#define SPI_CFG_LOOP(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LOOP_SHIFT)) & SPI_CFG_LOOP_MASK)
#define SPI_CFG_SPOL0_MASK                       (0x100U)
#define SPI_CFG_SPOL0_SHIFT                      (8U)
/*! SPOL0 - SSEL0 Polarity select.
 *  0b0..Low. The SSEL0 pin is active low.
 *  0b1..High. The SSEL0 pin is active high.
 */
#define SPI_CFG_SPOL0(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL0_SHIFT)) & SPI_CFG_SPOL0_MASK)
#define SPI_CFG_SPOL1_MASK                       (0x200U)
#define SPI_CFG_SPOL1_SHIFT                      (9U)
/*! SPOL1 - SSEL1 Polarity select.
 *  0b0..Low. The SSEL1 pin is active low.
 *  0b1..High. The SSEL1 pin is active high.
 */
#define SPI_CFG_SPOL1(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL1_SHIFT)) & SPI_CFG_SPOL1_MASK)
#define SPI_CFG_SPOL2_MASK                       (0x400U)
#define SPI_CFG_SPOL2_SHIFT                      (10U)
/*! SPOL2 - SSEL2 Polarity select.
 *  0b0..Low. The SSEL2 pin is active low.
 *  0b1..High. The SSEL2 pin is active high.
 */
#define SPI_CFG_SPOL2(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL2_SHIFT)) & SPI_CFG_SPOL2_MASK)
#define SPI_CFG_SPOL3_MASK                       (0x800U)
#define SPI_CFG_SPOL3_SHIFT                      (11U)
/*! SPOL3 - SSEL3 Polarity select.
 *  0b0..Low. The SSEL3 pin is active low.
 *  0b1..High. The SSEL3 pin is active high.
 */
#define SPI_CFG_SPOL3(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL3_SHIFT)) & SPI_CFG_SPOL3_MASK)
/*! @} */

/*! @name DLY - SPI Delay register */
/*! @{ */
#define SPI_DLY_PRE_DELAY_MASK                   (0xFU)
#define SPI_DLY_PRE_DELAY_SHIFT                  (0U)
/*! PRE_DELAY - Controls the amount of time between SSEL assertion and the beginning of a data
 *    transfer. There is always one SPI clock time between SSEL assertion and the first clock edge. This
 *    is not considered part of the pre-delay. 0x0 = No additional time is inserted. 0x1 = 1 SPI
 *    clock time is inserted. 0x2 = 2 SPI clock times are inserted. 0xF = 15 SPI clock times are
 *    inserted.
 */
#define SPI_DLY_PRE_DELAY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_DLY_PRE_DELAY_SHIFT)) & SPI_DLY_PRE_DELAY_MASK)
#define SPI_DLY_POST_DELAY_MASK                  (0xF0U)
#define SPI_DLY_POST_DELAY_SHIFT                 (4U)
/*! POST_DELAY - Controls the amount of time between the end of a data transfer and SSEL
 *    deassertion. 0x0 = No additional time is inserted. 0x1 = 1 SPI clock time is inserted. 0x2 = 2 SPI clock
 *    times are inserted. 0xF = 15 SPI clock times are inserted.
 */
#define SPI_DLY_POST_DELAY(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_DLY_POST_DELAY_SHIFT)) & SPI_DLY_POST_DELAY_MASK)
#define SPI_DLY_FRAME_DELAY_MASK                 (0xF00U)
#define SPI_DLY_FRAME_DELAY_SHIFT                (8U)
/*! FRAME_DELAY - If the EOF flag is set, controls the minimum amount of time between the current
 *    frame and the next frame (or SSEL deassertion if EOT). 0x0 = No additional time is inserted. 0x1
 *    = 1 SPI clock time is inserted. 0x2 = 2 SPI clock times are inserted. 0xF = 15 SPI clock
 *    times are inserted.
 */
#define SPI_DLY_FRAME_DELAY(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_DLY_FRAME_DELAY_SHIFT)) & SPI_DLY_FRAME_DELAY_MASK)
#define SPI_DLY_TRANSFER_DELAY_MASK              (0xF000U)
#define SPI_DLY_TRANSFER_DELAY_SHIFT             (12U)
/*! TRANSFER_DELAY - Controls the minimum amount of time that the SSEL is deasserted between
 *    transfers. 0x0 = The minimum time that SSEL is deasserted is 1 SPI clock time. (Zero added time.) 0x1
 *    = The minimum time that SSEL is deasserted is 2 SPI clock times. 0x2 = The minimum time that
 *    SSEL is deasserted is 3 SPI clock times. 0xF = The minimum time that SSEL is deasserted is 16
 *    SPI clock times.
 */
#define SPI_DLY_TRANSFER_DELAY(x)                (((uint32_t)(((uint32_t)(x)) << SPI_DLY_TRANSFER_DELAY_SHIFT)) & SPI_DLY_TRANSFER_DELAY_MASK)
/*! @} */

/*! @name STAT - SPI Status. Some status flags can be cleared by writing a 1 to that bit position. */
/*! @{ */
#define SPI_STAT_SSA_MASK                        (0x10U)
#define SPI_STAT_SSA_SHIFT                       (4U)
/*! SSA - Slave Select Assert. This flag is set whenever any slave select transitions from
 *    deasserted to asserted, in both master and slave modes. This allows determining when the SPI
 *    transmit/receive functions become busy, and allows waking up the device from reduced power modes when a
 *    slave mode access begins. This flag is cleared by software.
 */
#define SPI_STAT_SSA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSA_SHIFT)) & SPI_STAT_SSA_MASK)
#define SPI_STAT_SSD_MASK                        (0x20U)
#define SPI_STAT_SSD_SHIFT                       (5U)
/*! SSD - Slave Select Deassert. This flag is set whenever any asserted slave selects transition to
 *    deasserted, in both master and slave modes. This allows determining when the SPI
 *    transmit/receive functions become idle. This flag is cleared by software.
 */
#define SPI_STAT_SSD(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSD_SHIFT)) & SPI_STAT_SSD_MASK)
#define SPI_STAT_STALLED_MASK                    (0x40U)
#define SPI_STAT_STALLED_SHIFT                   (6U)
/*! STALLED - Stalled status flag. This indicates whether the SPI is currently in a stall condition.
 */
#define SPI_STAT_STALLED(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_STALLED_SHIFT)) & SPI_STAT_STALLED_MASK)
#define SPI_STAT_ENDTRANSFER_MASK                (0x80U)
#define SPI_STAT_ENDTRANSFER_SHIFT               (7U)
/*! ENDTRANSFER - End Transfer control bit. Software can set this bit to force an end to the current
 *    transfer when the transmitter finishes any activity already in progress, as if the EOT flag
 *    had been set prior to the last transmission. This capability is included to support cases where
 *    it is not known when transmit data is written that it will be the end of a transfer. The bit
 *    is cleared when the transmitter becomes idle as the transfer comes to an end. Forcing an end
 *    of transfer in this manner causes any specified FRAME_DELAY and TRANSFER_DELAY to be inserted.
 */
#define SPI_STAT_ENDTRANSFER(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_STAT_ENDTRANSFER_SHIFT)) & SPI_STAT_ENDTRANSFER_MASK)
#define SPI_STAT_MSTIDLE_MASK                    (0x100U)
#define SPI_STAT_MSTIDLE_SHIFT                   (8U)
/*! MSTIDLE - Master idle status flag. This bit is 1 whenever the SPI master function is fully idle.
 *    This means that the transmit holding register is empty and the transmitter is not in the
 *    process of sending data.
 */
#define SPI_STAT_MSTIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_MSTIDLE_SHIFT)) & SPI_STAT_MSTIDLE_MASK)
/*! @} */

/*! @name INTENSET - SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
/*! @{ */
#define SPI_INTENSET_SSAEN_MASK                  (0x10U)
#define SPI_INTENSET_SSAEN_SHIFT                 (4U)
/*! SSAEN - Slave select assert interrupt enable. Determines whether an interrupt occurs when the Slave Select is asserted.
 *  0b0..Disabled. No interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 *  0b1..Enabled. An interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 */
#define SPI_INTENSET_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSAEN_SHIFT)) & SPI_INTENSET_SSAEN_MASK)
#define SPI_INTENSET_SSDEN_MASK                  (0x20U)
#define SPI_INTENSET_SSDEN_SHIFT                 (5U)
/*! SSDEN - Slave select deassert interrupt enable. Determines whether an interrupt occurs when the Slave Select is deasserted.
 *  0b0..Disabled. No interrupt will be generated when all asserted Slave Selects transition to deasserted.
 *  0b1..Enabled. An interrupt will be generated when all asserted Slave Selects transition to deasserted.
 */
#define SPI_INTENSET_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSDEN_SHIFT)) & SPI_INTENSET_SSDEN_MASK)
#define SPI_INTENSET_MSTIDLEEN_MASK              (0x100U)
#define SPI_INTENSET_MSTIDLEEN_SHIFT             (8U)
/*! MSTIDLEEN - Master idle interrupt enable.
 *  0b0..No interrupt will be generated when the SPI master function is idle.
 *  0b1..An interrupt will be generated when the SPI master function is fully idle.
 */
#define SPI_INTENSET_MSTIDLEEN(x)                (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_MSTIDLEEN_SHIFT)) & SPI_INTENSET_MSTIDLEEN_MASK)
/*! @} */

/*! @name INTENCLR - SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared. */
/*! @{ */
#define SPI_INTENCLR_SSAEN_MASK                  (0x10U)
#define SPI_INTENCLR_SSAEN_SHIFT                 (4U)
/*! SSAEN - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define SPI_INTENCLR_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSAEN_SHIFT)) & SPI_INTENCLR_SSAEN_MASK)
#define SPI_INTENCLR_SSDEN_MASK                  (0x20U)
#define SPI_INTENCLR_SSDEN_SHIFT                 (5U)
/*! SSDEN - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define SPI_INTENCLR_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSDEN_SHIFT)) & SPI_INTENCLR_SSDEN_MASK)
#define SPI_INTENCLR_MSTIDLE_MASK                (0x100U)
#define SPI_INTENCLR_MSTIDLE_SHIFT               (8U)
/*! MSTIDLE - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define SPI_INTENCLR_MSTIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_MSTIDLE_SHIFT)) & SPI_INTENCLR_MSTIDLE_MASK)
/*! @} */

/*! @name DIV - SPI clock Divider */
/*! @{ */
#define SPI_DIV_DIVVAL_MASK                      (0xFFFFU)
#define SPI_DIV_DIVVAL_SHIFT                     (0U)
/*! DIVVAL - Rate divider value. Specifies how the Flexcomm clock (FCLK) is divided to produce the
 *    SPI clock rate in master mode. DIVVAL is -1 encoded such that the value 0 results in FCLK/1,
 *    the value 1 results in FCLK/2, up to the maximum possible divide value of 0xFFFF, which results
 *    in FCLK/65536.
 */
#define SPI_DIV_DIVVAL(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_DIV_DIVVAL_SHIFT)) & SPI_DIV_DIVVAL_MASK)
/*! @} */

/*! @name INTSTAT - SPI Interrupt Status */
/*! @{ */
#define SPI_INTSTAT_SSA_MASK                     (0x10U)
#define SPI_INTSTAT_SSA_SHIFT                    (4U)
/*! SSA - Slave Select Assert.
 */
#define SPI_INTSTAT_SSA(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSA_SHIFT)) & SPI_INTSTAT_SSA_MASK)
#define SPI_INTSTAT_SSD_MASK                     (0x20U)
#define SPI_INTSTAT_SSD_SHIFT                    (5U)
/*! SSD - Slave Select Deassert.
 */
#define SPI_INTSTAT_SSD(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSD_SHIFT)) & SPI_INTSTAT_SSD_MASK)
#define SPI_INTSTAT_MSTIDLE_MASK                 (0x100U)
#define SPI_INTSTAT_MSTIDLE_SHIFT                (8U)
/*! MSTIDLE - Master Idle status flag.
 */
#define SPI_INTSTAT_MSTIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_MSTIDLE_SHIFT)) & SPI_INTSTAT_MSTIDLE_MASK)
/*! @} */

/*! @name FIFOCFG - FIFO configuration and enable register. */
/*! @{ */
#define SPI_FIFOCFG_ENABLETX_MASK                (0x1U)
#define SPI_FIFOCFG_ENABLETX_SHIFT               (0U)
/*! ENABLETX - Enable the transmit FIFO.
 *  0b0..The transmit FIFO is not enabled.
 *  0b1..The transmit FIFO is enabled.
 */
#define SPI_FIFOCFG_ENABLETX(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_ENABLETX_SHIFT)) & SPI_FIFOCFG_ENABLETX_MASK)
#define SPI_FIFOCFG_ENABLERX_MASK                (0x2U)
#define SPI_FIFOCFG_ENABLERX_SHIFT               (1U)
/*! ENABLERX - Enable the receive FIFO.
 *  0b0..The receive FIFO is not enabled.
 *  0b1..The receive FIFO is enabled.
 */
#define SPI_FIFOCFG_ENABLERX(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_ENABLERX_SHIFT)) & SPI_FIFOCFG_ENABLERX_MASK)
#define SPI_FIFOCFG_SIZE_MASK                    (0x30U)
#define SPI_FIFOCFG_SIZE_SHIFT                   (4U)
/*! SIZE - FIFO size configuration. This is a read-only field. 0x0 = FIFO is configured as 16
 *    entries of 8 bits. 0x1, 0x2, 0x3 = not applicable to USART.
 */
#define SPI_FIFOCFG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_SIZE_SHIFT)) & SPI_FIFOCFG_SIZE_MASK)
#define SPI_FIFOCFG_DMATX_MASK                   (0x1000U)
#define SPI_FIFOCFG_DMATX_SHIFT                  (12U)
/*! DMATX - DMA configuration for transmit.
 *  0b0..DMA is not used for the transmit function.
 *  0b1..Trigger DMA for the transmit function if the FIFO is not full. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define SPI_FIFOCFG_DMATX(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_DMATX_SHIFT)) & SPI_FIFOCFG_DMATX_MASK)
#define SPI_FIFOCFG_DMARX_MASK                   (0x2000U)
#define SPI_FIFOCFG_DMARX_SHIFT                  (13U)
/*! DMARX - DMA configuration for receive.
 *  0b0..DMA is not used for the receive function.
 *  0b1..Trigger DMA for the receive function if the FIFO is not empty. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define SPI_FIFOCFG_DMARX(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_DMARX_SHIFT)) & SPI_FIFOCFG_DMARX_MASK)
#define SPI_FIFOCFG_WAKETX_MASK                  (0x4000U)
#define SPI_FIFOCFG_WAKETX_SHIFT                 (14U)
/*! WAKETX - Wake-up for transmit FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the transmit FIFO level reaches the value specified by TXLVL in
 *       FIFOTRIG, even when the TXLVL interrupt is not enabled.
 */
#define SPI_FIFOCFG_WAKETX(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_WAKETX_SHIFT)) & SPI_FIFOCFG_WAKETX_MASK)
#define SPI_FIFOCFG_WAKERX_MASK                  (0x8000U)
#define SPI_FIFOCFG_WAKERX_SHIFT                 (15U)
/*! WAKERX - Wake-up for receive FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the receive FIFO level reaches the value specified by RXLVL in
 *       FIFOTRIG, even when the RXLVL interrupt is not enabled.
 */
#define SPI_FIFOCFG_WAKERX(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_WAKERX_SHIFT)) & SPI_FIFOCFG_WAKERX_MASK)
#define SPI_FIFOCFG_EMPTYTX_MASK                 (0x10000U)
#define SPI_FIFOCFG_EMPTYTX_SHIFT                (16U)
/*! EMPTYTX - Empty command for the transmit FIFO. When a 1 is written to this bit, the TX FIFO is emptied.
 */
#define SPI_FIFOCFG_EMPTYTX(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_EMPTYTX_SHIFT)) & SPI_FIFOCFG_EMPTYTX_MASK)
#define SPI_FIFOCFG_EMPTYRX_MASK                 (0x20000U)
#define SPI_FIFOCFG_EMPTYRX_SHIFT                (17U)
/*! EMPTYRX - Empty command for the receive FIFO. When a 1 is written to this bit, the RX FIFO is emptied.
 */
#define SPI_FIFOCFG_EMPTYRX(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOCFG_EMPTYRX_SHIFT)) & SPI_FIFOCFG_EMPTYRX_MASK)
/*! @} */

/*! @name FIFOSTAT - FIFO status register. */
/*! @{ */
#define SPI_FIFOSTAT_TXERR_MASK                  (0x1U)
#define SPI_FIFOSTAT_TXERR_SHIFT                 (0U)
/*! TXERR - TX FIFO error. Will be set if a transmit FIFO error occurs. This could be an overflow
 *    caused by pushing data into a full FIFO, or by an underflow if the FIFO is empty when data is
 *    needed. Cleared by writing a 1 to this bit.
 */
#define SPI_FIFOSTAT_TXERR(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXERR_SHIFT)) & SPI_FIFOSTAT_TXERR_MASK)
#define SPI_FIFOSTAT_RXERR_MASK                  (0x2U)
#define SPI_FIFOSTAT_RXERR_SHIFT                 (1U)
/*! RXERR - RX FIFO error. Will be set if a receive FIFO overflow occurs, caused by software or DMA
 *    not emptying the FIFO fast enough. Cleared by writing a 1 to this bit.
 */
#define SPI_FIFOSTAT_RXERR(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXERR_SHIFT)) & SPI_FIFOSTAT_RXERR_MASK)
#define SPI_FIFOSTAT_PERINT_MASK                 (0x8U)
#define SPI_FIFOSTAT_PERINT_SHIFT                (3U)
/*! PERINT - Peripheral interrupt. When 1, this indicates that the peripheral function has asserted
 *    an interrupt. The details can be found by reading the peripheral's STAT register.
 */
#define SPI_FIFOSTAT_PERINT(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_PERINT_SHIFT)) & SPI_FIFOSTAT_PERINT_MASK)
#define SPI_FIFOSTAT_TXEMPTY_MASK                (0x10U)
#define SPI_FIFOSTAT_TXEMPTY_SHIFT               (4U)
/*! TXEMPTY - Transmit FIFO empty. When 1, the transmit FIFO is empty. The peripheral may still be processing the last piece of data.
 */
#define SPI_FIFOSTAT_TXEMPTY(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXEMPTY_SHIFT)) & SPI_FIFOSTAT_TXEMPTY_MASK)
#define SPI_FIFOSTAT_TXNOTFULL_MASK              (0x20U)
#define SPI_FIFOSTAT_TXNOTFULL_SHIFT             (5U)
/*! TXNOTFULL - Transmit FIFO not full. When 1, the transmit FIFO is not full, so more data can be
 *    written. When 0, the transmit FIFO is full and another write would cause it to overflow.
 */
#define SPI_FIFOSTAT_TXNOTFULL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXNOTFULL_SHIFT)) & SPI_FIFOSTAT_TXNOTFULL_MASK)
#define SPI_FIFOSTAT_RXNOTEMPTY_MASK             (0x40U)
#define SPI_FIFOSTAT_RXNOTEMPTY_SHIFT            (6U)
/*! RXNOTEMPTY - Receive FIFO not empty. When 1, the receive FIFO is not empty, so data can be read. When 0, the receive FIFO is empty.
 */
#define SPI_FIFOSTAT_RXNOTEMPTY(x)               (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXNOTEMPTY_SHIFT)) & SPI_FIFOSTAT_RXNOTEMPTY_MASK)
#define SPI_FIFOSTAT_RXFULL_MASK                 (0x80U)
#define SPI_FIFOSTAT_RXFULL_SHIFT                (7U)
/*! RXFULL - Receive FIFO full. When 1, the receive FIFO is full. Data needs to be read out to
 *    prevent the peripheral from causing an overflow.
 */
#define SPI_FIFOSTAT_RXFULL(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXFULL_SHIFT)) & SPI_FIFOSTAT_RXFULL_MASK)
#define SPI_FIFOSTAT_TXLVL_MASK                  (0x1F00U)
#define SPI_FIFOSTAT_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO current level. A 0 means the TX FIFO is currently empty, and the TXEMPTY
 *    and TXNOTFULL flags will be 1. Other values tell how much data is actually in the TX FIFO at
 *    the point where the read occurs. If the TX FIFO is full, the TXEMPTY and TXNOTFULL flags will be
 *    0.
 */
#define SPI_FIFOSTAT_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_TXLVL_SHIFT)) & SPI_FIFOSTAT_TXLVL_MASK)
#define SPI_FIFOSTAT_RXLVL_MASK                  (0x1F0000U)
#define SPI_FIFOSTAT_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO current level. A 0 means the RX FIFO is currently empty, and the RXFULL and
 *    RXNOTEMPTY flags will be 0. Other values tell how much data is actually in the RX FIFO at the
 *    point where the read occurs. If the RX FIFO is full, the RXFULL and RXNOTEMPTY flags will be
 *    1.
 */
#define SPI_FIFOSTAT_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOSTAT_RXLVL_SHIFT)) & SPI_FIFOSTAT_RXLVL_MASK)
/*! @} */

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
/*! @{ */
#define SPI_FIFOTRIG_TXLVLENA_MASK               (0x1U)
#define SPI_FIFOTRIG_TXLVLENA_SHIFT              (0U)
/*! TXLVLENA - Transmit FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMATX in FIFOCFG is set.
 *  0b0..Transmit FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the transmit FIFO level reaches the value specified by the TXLVL field in this register.
 */
#define SPI_FIFOTRIG_TXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_TXLVLENA_SHIFT)) & SPI_FIFOTRIG_TXLVLENA_MASK)
#define SPI_FIFOTRIG_RXLVLENA_MASK               (0x2U)
#define SPI_FIFOTRIG_RXLVLENA_SHIFT              (1U)
/*! RXLVLENA - Receive FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMARX in FIFOCFG is set.
 *  0b0..Receive FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the receive FIFO level reaches the value specified by the RXLVL field in this register.
 */
#define SPI_FIFOTRIG_RXLVLENA(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_RXLVLENA_SHIFT)) & SPI_FIFOTRIG_RXLVLENA_MASK)
#define SPI_FIFOTRIG_TXLVL_MASK                  (0xF00U)
#define SPI_FIFOTRIG_TXLVL_SHIFT                 (8U)
/*! TXLVL - Transmit FIFO level trigger point. This field is used only when TXLVLENA = 1. If enabled
 *    to do so, the FIFO level can wake up the device just enough to perform DMA, then return to
 *    the reduced power mode. See Hardware Wake-up control register. 0 = trigger when the TX FIFO
 *    becomes empty. 1 = trigger when the TX FIFO level decreases to one entry. 15 = trigger when the TX
 *    FIFO level decreases to 15 entries (is no longer full).
 */
#define SPI_FIFOTRIG_TXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_TXLVL_SHIFT)) & SPI_FIFOTRIG_TXLVL_MASK)
#define SPI_FIFOTRIG_RXLVL_MASK                  (0xF0000U)
#define SPI_FIFOTRIG_RXLVL_SHIFT                 (16U)
/*! RXLVL - Receive FIFO level trigger point. The RX FIFO level is checked when a new piece of data
 *    is received. This field is used only when RXLVLENA = 1. If enabled to do so, the FIFO level
 *    can wake up the device just enough to perform DMA, then return to the reduced power mode. See
 *    Hardware Wake-up control register. 0 = trigger when the RX FIFO has received one entry (is no
 *    longer empty). 1 = trigger when the RX FIFO has received two entries. 15 = trigger when the RX
 *    FIFO has received 16 entries (has become full).
 */
#define SPI_FIFOTRIG_RXLVL(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_FIFOTRIG_RXLVL_SHIFT)) & SPI_FIFOTRIG_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
/*! @{ */
#define SPI_FIFOINTENSET_TXERR_MASK              (0x1U)
#define SPI_FIFOINTENSET_TXERR_SHIFT             (0U)
/*! TXERR - Determines whether an interrupt occurs when a transmit error occurs, based on the TXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a transmit error.
 *  0b1..An interrupt will be generated when a transmit error occurs.
 */
#define SPI_FIFOINTENSET_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_TXERR_SHIFT)) & SPI_FIFOINTENSET_TXERR_MASK)
#define SPI_FIFOINTENSET_RXERR_MASK              (0x2U)
#define SPI_FIFOINTENSET_RXERR_SHIFT             (1U)
/*! RXERR - Determines whether an interrupt occurs when a receive error occurs, based on the RXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a receive error.
 *  0b1..An interrupt will be generated when a receive error occurs.
 */
#define SPI_FIFOINTENSET_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_RXERR_SHIFT)) & SPI_FIFOINTENSET_RXERR_MASK)
#define SPI_FIFOINTENSET_TXLVL_MASK              (0x4U)
#define SPI_FIFOINTENSET_TXLVL_SHIFT             (2U)
/*! TXLVL - Determines whether an interrupt occurs when a the transmit FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the TX FIFO level.
 *  0b1..If TXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the TX FIFO level decreases
 *       to the level specified by TXLVL in the FIFOTRIG register.
 */
#define SPI_FIFOINTENSET_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_TXLVL_SHIFT)) & SPI_FIFOINTENSET_TXLVL_MASK)
#define SPI_FIFOINTENSET_RXLVL_MASK              (0x8U)
#define SPI_FIFOINTENSET_RXLVL_SHIFT             (3U)
/*! RXLVL - Determines whether an interrupt occurs when a the receive FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the RX FIFO level.
 *  0b1..If RXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the when the RX FIFO level
 *       increases to the level specified by RXLVL in the FIFOTRIG register.
 */
#define SPI_FIFOINTENSET_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENSET_RXLVL_SHIFT)) & SPI_FIFOINTENSET_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
/*! @{ */
#define SPI_FIFOINTENCLR_TXERR_MASK              (0x1U)
#define SPI_FIFOINTENCLR_TXERR_SHIFT             (0U)
/*! TXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define SPI_FIFOINTENCLR_TXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_TXERR_SHIFT)) & SPI_FIFOINTENCLR_TXERR_MASK)
#define SPI_FIFOINTENCLR_RXERR_MASK              (0x2U)
#define SPI_FIFOINTENCLR_RXERR_SHIFT             (1U)
/*! RXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define SPI_FIFOINTENCLR_RXERR(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_RXERR_SHIFT)) & SPI_FIFOINTENCLR_RXERR_MASK)
#define SPI_FIFOINTENCLR_TXLVL_MASK              (0x4U)
#define SPI_FIFOINTENCLR_TXLVL_SHIFT             (2U)
/*! TXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define SPI_FIFOINTENCLR_TXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_TXLVL_SHIFT)) & SPI_FIFOINTENCLR_TXLVL_MASK)
#define SPI_FIFOINTENCLR_RXLVL_MASK              (0x8U)
#define SPI_FIFOINTENCLR_RXLVL_SHIFT             (3U)
/*! RXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define SPI_FIFOINTENCLR_RXLVL(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTENCLR_RXLVL_SHIFT)) & SPI_FIFOINTENCLR_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
/*! @{ */
#define SPI_FIFOINTSTAT_TXERR_MASK               (0x1U)
#define SPI_FIFOINTSTAT_TXERR_SHIFT              (0U)
/*! TXERR - TX FIFO error.
 */
#define SPI_FIFOINTSTAT_TXERR(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_TXERR_SHIFT)) & SPI_FIFOINTSTAT_TXERR_MASK)
#define SPI_FIFOINTSTAT_RXERR_MASK               (0x2U)
#define SPI_FIFOINTSTAT_RXERR_SHIFT              (1U)
/*! RXERR - RX FIFO error.
 */
#define SPI_FIFOINTSTAT_RXERR(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_RXERR_SHIFT)) & SPI_FIFOINTSTAT_RXERR_MASK)
#define SPI_FIFOINTSTAT_TXLVL_MASK               (0x4U)
#define SPI_FIFOINTSTAT_TXLVL_SHIFT              (2U)
/*! TXLVL - Transmit FIFO level interrupt.
 */
#define SPI_FIFOINTSTAT_TXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_TXLVL_SHIFT)) & SPI_FIFOINTSTAT_TXLVL_MASK)
#define SPI_FIFOINTSTAT_RXLVL_MASK               (0x8U)
#define SPI_FIFOINTSTAT_RXLVL_SHIFT              (3U)
/*! RXLVL - Receive FIFO level interrupt.
 */
#define SPI_FIFOINTSTAT_RXLVL(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_RXLVL_SHIFT)) & SPI_FIFOINTSTAT_RXLVL_MASK)
#define SPI_FIFOINTSTAT_PERINT_MASK              (0x10U)
#define SPI_FIFOINTSTAT_PERINT_SHIFT             (4U)
/*! PERINT - Peripheral interrupt.
 */
#define SPI_FIFOINTSTAT_PERINT(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFOINTSTAT_PERINT_SHIFT)) & SPI_FIFOINTSTAT_PERINT_MASK)
/*! @} */

/*! @name FIFOWR - FIFO write data. */
/*! @{ */
#define SPI_FIFOWR_TXDATA_MASK                   (0xFFFFU)
#define SPI_FIFOWR_TXDATA_SHIFT                  (0U)
/*! TXDATA - Transmit data to the FIFO.
 */
#define SPI_FIFOWR_TXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXDATA_SHIFT)) & SPI_FIFOWR_TXDATA_MASK)
#define SPI_FIFOWR_TXSSEL0_N_MASK                (0x10000U)
#define SPI_FIFOWR_TXSSEL0_N_SHIFT               (16U)
/*! TXSSEL0_N - Transmit slave select. This field asserts SSEL0 in master mode. The output on the pin is active LOW by default.
 *  0b0..SSEL0 asserted.
 *  0b1..SSEL0 not asserted.
 */
#define SPI_FIFOWR_TXSSEL0_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL0_N_SHIFT)) & SPI_FIFOWR_TXSSEL0_N_MASK)
#define SPI_FIFOWR_TXSSEL1_N_MASK                (0x20000U)
#define SPI_FIFOWR_TXSSEL1_N_SHIFT               (17U)
/*! TXSSEL1_N - Transmit slave select. This field asserts SSEL1 in master mode. The output on the pin is active LOW by default.
 *  0b0..SSEL1 asserted.
 *  0b1..SSEL1 not asserted.
 */
#define SPI_FIFOWR_TXSSEL1_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL1_N_SHIFT)) & SPI_FIFOWR_TXSSEL1_N_MASK)
#define SPI_FIFOWR_TXSSEL2_N_MASK                (0x40000U)
#define SPI_FIFOWR_TXSSEL2_N_SHIFT               (18U)
/*! TXSSEL2_N - Transmit slave select. This field asserts SSEL2 in master mode. The output on the pin is active LOW by default.
 *  0b0..SSEL2 asserted.
 *  0b1..SSEL2 not asserted.
 */
#define SPI_FIFOWR_TXSSEL2_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL2_N_SHIFT)) & SPI_FIFOWR_TXSSEL2_N_MASK)
#define SPI_FIFOWR_TXSSEL3_N_MASK                (0x80000U)
#define SPI_FIFOWR_TXSSEL3_N_SHIFT               (19U)
/*! TXSSEL3_N - Transmit slave select. This field asserts SSEL3 in master mode. The output on the pin is active LOW by default.
 *  0b0..SSEL3 asserted.
 *  0b1..SSEL3 not asserted.
 */
#define SPI_FIFOWR_TXSSEL3_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_TXSSEL3_N_SHIFT)) & SPI_FIFOWR_TXSSEL3_N_MASK)
#define SPI_FIFOWR_EOT_MASK                      (0x100000U)
#define SPI_FIFOWR_EOT_SHIFT                     (20U)
/*! EOT - End of transfer. The asserted SSEL will be deasserted at the end of a transfer and remain
 *    so far at least the time specified by the Transfer_delay value in the DLY register.
 *  0b0..SSEL not deasserted. This piece of data is not treated as the end of a transfer. SSEL will not be deasserted at the end of this data.
 *  0b1..SSEL deasserted. This piece of data is treated as the end of a transfer. SSEL will be deasserted at the end of this piece of data.
 */
#define SPI_FIFOWR_EOT(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_EOT_SHIFT)) & SPI_FIFOWR_EOT_MASK)
#define SPI_FIFOWR_EOF_MASK                      (0x200000U)
#define SPI_FIFOWR_EOF_SHIFT                     (21U)
/*! EOF - End of frame. Between frames, a delay may be inserted, as defined by the Frame_delay value
 *    in the DLY register. The end of a frame may not be particularly meaningful if the Frame_delay
 *    value = 0. This control can be used as part of the support for frame lengths greater than 16
 *    bits.
 *  0b0..Data not EOF. This piece of data transmitted is not treated as the end of a frame.
 *  0b1..Data EOF. This piece of data is treated as the end of a frame, causing the Frame_delay time to be
 *       inserted before subsequent data is transmitted.
 */
#define SPI_FIFOWR_EOF(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_EOF_SHIFT)) & SPI_FIFOWR_EOF_MASK)
#define SPI_FIFOWR_RXIGNORE_MASK                 (0x400000U)
#define SPI_FIFOWR_RXIGNORE_SHIFT                (22U)
/*! RXIGNORE - Receive Ignore. This allows data to be transmitted using the SPI without the need to
 *    read unneeded data from the receiver. Setting this bit simplifies the transmit process and can
 *    be used with the DMA.
 *  0b0..Read received data. Received data must be read in order to allow transmission to progress. SPI transmit
 *       will halt when the receive data FIFO is full. In slave mode, an overrun error will occur if received data
 *       is not read before new data is received.
 *  0b1..Ignore received data. Received data is ignored, allowing transmission without reading unneeded received
 *       data. No receiver flags are generated.
 */
#define SPI_FIFOWR_RXIGNORE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_RXIGNORE_SHIFT)) & SPI_FIFOWR_RXIGNORE_MASK)
#define SPI_FIFOWR_LEN_MASK                      (0xF000000U)
#define SPI_FIFOWR_LEN_SHIFT                     (24U)
/*! LEN - Data Length. Specifies the data length from 4 to 16 bits. Note that transfer lengths
 *    greater than 16 bits are supported by implementing multiple sequential transmits. 0x0-2 = Reserved.
 *    0x3 = Data transfer is 4 bits in length. 0x4 = Data transfer is 5 bits in length. 0xF = Data
 *    transfer is 16 bits in length.
 */
#define SPI_FIFOWR_LEN(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFOWR_LEN_SHIFT)) & SPI_FIFOWR_LEN_MASK)
/*! @} */

/*! @name FIFORD - FIFO read data. */
/*! @{ */
#define SPI_FIFORD_RXDATA_MASK                   (0xFFFFU)
#define SPI_FIFORD_RXDATA_SHIFT                  (0U)
/*! RXDATA - Received data from the FIFO.
 */
#define SPI_FIFORD_RXDATA(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXDATA_SHIFT)) & SPI_FIFORD_RXDATA_MASK)
#define SPI_FIFORD_RXSSEL0_N_MASK                (0x10000U)
#define SPI_FIFORD_RXSSEL0_N_SHIFT               (16U)
/*! RXSSEL0_N - Slave Select for receive. This field allows the state of the SSEL0 pin to be saved
 *    along with received data. The value will reflect the SSEL0 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_FIFORD_RXSSEL0_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL0_N_SHIFT)) & SPI_FIFORD_RXSSEL0_N_MASK)
#define SPI_FIFORD_RXSSEL1_N_MASK                (0x20000U)
#define SPI_FIFORD_RXSSEL1_N_SHIFT               (17U)
/*! RXSSEL1_N - Slave Select for receive. This field allows the state of the SSEL1 pin to be saved
 *    along with received data. The value will reflect the SSEL1 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_FIFORD_RXSSEL1_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL1_N_SHIFT)) & SPI_FIFORD_RXSSEL1_N_MASK)
#define SPI_FIFORD_RXSSEL2_N_MASK                (0x40000U)
#define SPI_FIFORD_RXSSEL2_N_SHIFT               (18U)
/*! RXSSEL2_N - Slave Select for receive. This field allows the state of the SSEL2 pin to be saved
 *    along with received data. The value will reflect the SSEL2 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_FIFORD_RXSSEL2_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL2_N_SHIFT)) & SPI_FIFORD_RXSSEL2_N_MASK)
#define SPI_FIFORD_RXSSEL3_N_MASK                (0x80000U)
#define SPI_FIFORD_RXSSEL3_N_SHIFT               (19U)
/*! RXSSEL3_N - Slave Select for receive. This field allows the state of the SSEL3 pin to be saved
 *    along with received data. The value will reflect the SSEL3 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_FIFORD_RXSSEL3_N(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_RXSSEL3_N_SHIFT)) & SPI_FIFORD_RXSSEL3_N_MASK)
#define SPI_FIFORD_SOT_MASK                      (0x100000U)
#define SPI_FIFORD_SOT_SHIFT                     (20U)
/*! SOT - Start of Transfer flag. This flag will be 1 if this is the first data after the SSELs went
 *    from deasserted to asserted (i.e., any previous transfer has ended). This information can be
 *    used to identify the first piece of data in cases where the transfer length is greater than 16
 *    bits.
 */
#define SPI_FIFORD_SOT(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_FIFORD_SOT_SHIFT)) & SPI_FIFORD_SOT_MASK)
/*! @} */

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
/*! @{ */
#define SPI_FIFORDNOPOP_RXDATA_MASK              (0xFFFFU)
#define SPI_FIFORDNOPOP_RXDATA_SHIFT             (0U)
/*! RXDATA - Received data from the FIFO.
 */
#define SPI_FIFORDNOPOP_RXDATA(x)                (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXDATA_SHIFT)) & SPI_FIFORDNOPOP_RXDATA_MASK)
#define SPI_FIFORDNOPOP_RXSSEL0_N_MASK           (0x10000U)
#define SPI_FIFORDNOPOP_RXSSEL0_N_SHIFT          (16U)
/*! RXSSEL0_N - Slave Select for receive.
 */
#define SPI_FIFORDNOPOP_RXSSEL0_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL0_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL0_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL1_N_MASK           (0x20000U)
#define SPI_FIFORDNOPOP_RXSSEL1_N_SHIFT          (17U)
/*! RXSSEL1_N - Slave Select for receive.
 */
#define SPI_FIFORDNOPOP_RXSSEL1_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL1_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL1_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL2_N_MASK           (0x40000U)
#define SPI_FIFORDNOPOP_RXSSEL2_N_SHIFT          (18U)
/*! RXSSEL2_N - Slave Select for receive.
 */
#define SPI_FIFORDNOPOP_RXSSEL2_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL2_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL2_N_MASK)
#define SPI_FIFORDNOPOP_RXSSEL3_N_MASK           (0x80000U)
#define SPI_FIFORDNOPOP_RXSSEL3_N_SHIFT          (19U)
/*! RXSSEL3_N - Slave Select for receive.
 */
#define SPI_FIFORDNOPOP_RXSSEL3_N(x)             (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_RXSSEL3_N_SHIFT)) & SPI_FIFORDNOPOP_RXSSEL3_N_MASK)
#define SPI_FIFORDNOPOP_SOT_MASK                 (0x100000U)
#define SPI_FIFORDNOPOP_SOT_SHIFT                (20U)
/*! SOT - Start of transfer flag.
 */
#define SPI_FIFORDNOPOP_SOT(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_FIFORDNOPOP_SOT_SHIFT)) & SPI_FIFORDNOPOP_SOT_MASK)
/*! @} */

/*! @name ID - Peripheral identification register. */
/*! @{ */
#define SPI_ID_APERTURE_MASK                     (0xFFU)
#define SPI_ID_APERTURE_SHIFT                    (0U)
/*! APERTURE - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture.
 */
#define SPI_ID_APERTURE(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_ID_APERTURE_SHIFT)) & SPI_ID_APERTURE_MASK)
#define SPI_ID_MINOR_REV_MASK                    (0xF00U)
#define SPI_ID_MINOR_REV_SHIFT                   (8U)
/*! MINOR_REV - Minor revision of module implementation.
 */
#define SPI_ID_MINOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_ID_MINOR_REV_SHIFT)) & SPI_ID_MINOR_REV_MASK)
#define SPI_ID_MAJOR_REV_MASK                    (0xF000U)
#define SPI_ID_MAJOR_REV_SHIFT                   (12U)
/*! MAJOR_REV - Major revision of module implementation.
 */
#define SPI_ID_MAJOR_REV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_ID_MAJOR_REV_SHIFT)) & SPI_ID_MAJOR_REV_MASK)
#define SPI_ID_ID_MASK                           (0xFFFF0000U)
#define SPI_ID_ID_SHIFT                          (16U)
/*! ID - Module identifier for the selected function.
 */
#define SPI_ID_ID(x)                             (((uint32_t)(((uint32_t)(x)) << SPI_ID_ID_SHIFT)) & SPI_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40086000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x40087000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Peripheral SPI2 base address */
#define SPI2_BASE                                (0x40088000u)
/** Peripheral SPI2 base pointer */
#define SPI2                                     ((SPI_Type *)SPI2_BASE)
/** Peripheral SPI3 base address */
#define SPI3_BASE                                (0x40089000u)
/** Peripheral SPI3 base pointer */
#define SPI3                                     ((SPI_Type *)SPI3_BASE)
/** Peripheral SPI4 base address */
#define SPI4_BASE                                (0x4008A000u)
/** Peripheral SPI4 base pointer */
#define SPI4                                     ((SPI_Type *)SPI4_BASE)
/** Peripheral SPI5 base address */
#define SPI5_BASE                                (0x40096000u)
/** Peripheral SPI5 base pointer */
#define SPI5                                     ((SPI_Type *)SPI5_BASE)
/** Peripheral SPI6 base address */
#define SPI6_BASE                                (0x40097000u)
/** Peripheral SPI6 base pointer */
#define SPI6                                     ((SPI_Type *)SPI6_BASE)
/** Peripheral SPI7 base address */
#define SPI7_BASE                                (0x40098000u)
/** Peripheral SPI7 base pointer */
#define SPI7                                     ((SPI_Type *)SPI7_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE, SPI2_BASE, SPI3_BASE, SPI4_BASE, SPI5_BASE, SPI6_BASE, SPI7_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1, SPI2, SPI3, SPI4, SPI5, SPI6, SPI7 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */

/** SYSCON - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t AHBMATPRIO;                        /**< AHB multilayer matrix priority control, offset: 0x10 */
       uint8_t RESERVED_1[44];
  __IO uint32_t SYSTCKCAL;                         /**< System tick counter calibration, offset: 0x40 */
       uint8_t RESERVED_2[4];
  __IO uint32_t NMISRC;                            /**< NMI Source Select, offset: 0x48 */
  __IO uint32_t ASYNCAPBCTRL;                      /**< Asynchronous APB Control, offset: 0x4C */
       uint8_t RESERVED_3[112];
  __I  uint32_t PIOPORCAP[2];                      /**< POR captured value of port n, array offset: 0xC0, array step: 0x4 */
       uint8_t RESERVED_4[8];
  __I  uint32_t PIORESCAP[2];                      /**< Reset captured value of port n, array offset: 0xD0, array step: 0x4 */
       uint8_t RESERVED_5[40];
  __IO uint32_t PRESETCTRL[2];                     /**< Peripheral reset control n, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_6[24];
  __O  uint32_t PRESETCTRLSET[2];                  /**< Set bits in PRESETCTRLn, array offset: 0x120, array step: 0x4 */
       uint8_t RESERVED_7[24];
  __O  uint32_t PRESETCTRLCLR[2];                  /**< Clear bits in PRESETCTRLn, array offset: 0x140, array step: 0x4 */
       uint8_t RESERVED_8[168];
  __IO uint32_t SYSRSTSTAT;                        /**< System reset status register, offset: 0x1F0 */
       uint8_t RESERVED_9[12];
  __IO uint32_t AHBCLKCTRL[2];                     /**< AHB Clock control n, array offset: 0x200, array step: 0x4 */
       uint8_t RESERVED_10[24];
  __O  uint32_t AHBCLKCTRLSET[2];                  /**< Set bits in AHBCLKCTRLn, array offset: 0x220, array step: 0x4 */
       uint8_t RESERVED_11[24];
  __O  uint32_t AHBCLKCTRLCLR[2];                  /**< Clear bits in AHBCLKCTRLn, array offset: 0x240, array step: 0x4 */
       uint8_t RESERVED_12[56];
  __IO uint32_t MAINCLKSELA;                       /**< Main clock source select A, offset: 0x280 */
  __IO uint32_t MAINCLKSELB;                       /**< Main clock source select B, offset: 0x284 */
  __IO uint32_t CLKOUTSELA;                        /**< CLKOUT clock source select A, offset: 0x288 */
       uint8_t RESERVED_13[4];
  __IO uint32_t SYSPLLCLKSEL;                      /**< PLL clock source select, offset: 0x290 */
       uint8_t RESERVED_14[16];
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select, offset: 0x2A4 */
  __IO uint32_t USBCLKSEL;                         /**< USB clock source select, offset: 0x2A8 */
       uint8_t RESERVED_15[4];
  __IO uint32_t FXCOMCLKSEL[8];                    /**< Flexcomm0 clock source select..Flexcomm7 clock source select, array offset: 0x2B0, array step: 0x4 */
       uint8_t RESERVED_16[16];
  __IO uint32_t MCLKCLKSEL;                        /**< MCLK clock source select, offset: 0x2E0 */
       uint8_t RESERVED_17[4];
  __IO uint32_t FRGCLKSEL;                         /**< Fractional Rate Generator clock source select, offset: 0x2E8 */
       uint8_t RESERVED_18[20];
  __IO uint32_t SYSTICKCLKDIV;                     /**< SYSTICK clock divider, offset: 0x300 */
       uint8_t RESERVED_19[124];
  __IO uint32_t AHBCLKDIV;                         /**< AHB clock divider, offset: 0x380 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider, offset: 0x384 */
       uint8_t RESERVED_20[12];
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider, offset: 0x394 */
  __IO uint32_t USBCLKDIV;                         /**< USB clock divider, offset: 0x398 */
       uint8_t RESERVED_21[4];
  __IO uint32_t FRGCTRL;                           /**< Fractional rate divider, offset: 0x3A0 */
       uint8_t RESERVED_22[8];
  __IO uint32_t MCLKDIV;                           /**< I2S MCLK clock divider, offset: 0x3AC */
       uint8_t RESERVED_23[80];
  __IO uint32_t FLASHCFG;                          /**< Flash wait states configuration, offset: 0x400 */
       uint8_t RESERVED_24[8];
  __IO uint32_t USBCLKCTRL;                        /**< USB clock control, offset: 0x40C */
  __IO uint32_t USBCLKSTAT;                        /**< USB clock status, offset: 0x410 */
       uint8_t RESERVED_25[4];
  __IO uint32_t FREQMECTRL;                        /**< Frequency measure register, offset: 0x418 */
       uint8_t RESERVED_26[4];
  __IO uint32_t MCLKIO;                            /**< MCLK input/output control, offset: 0x420 */
       uint8_t RESERVED_27[220];
  __IO uint32_t FROCTRL;                           /**< FRO oscillator control, offset: 0x500 */
       uint8_t RESERVED_28[4];
  __IO uint32_t WDTOSCCTRL;                        /**< Watchdog oscillator control, offset: 0x508 */
  __IO uint32_t RTCOSCCTRL;                        /**< RTC oscillator 32 kHz output control, offset: 0x50C */
       uint8_t RESERVED_29[112];
  __IO uint32_t SYSPLLCTRL;                        /**< PLL control, offset: 0x580 */
  __I  uint32_t SYSPLLSTAT;                        /**< PLL status, offset: 0x584 */
  __IO uint32_t SYSPLLNDEC;                        /**< PLL N decoder, offset: 0x588 */
  __IO uint32_t SYSPLLPDEC;                        /**< PLL P decoder, offset: 0x58C */
  __IO uint32_t SYSPLLSSCTRL0;                     /**< PLL spread spectrum control 0, offset: 0x590 */
  __IO uint32_t SYSPLLSSCTRL1;                     /**< PLL spread spectrum control 1, offset: 0x594 */
       uint8_t RESERVED_30[104];
  __IO uint32_t PDSLEEPCFG[2];                     /**< Sleep configuration register n, array offset: 0x600, array step: 0x4 */
       uint8_t RESERVED_31[8];
  __IO uint32_t PDRUNCFG[1];                       /**< Power configuration register 0, array offset: 0x610, array step: 0x4 */
       uint8_t RESERVED_32[12];
  __O  uint32_t PDRUNCFGSET[1];                    /**< Set bits in PDRUNCFGn, array offset: 0x620, array step: 0x4 */
       uint8_t RESERVED_33[12];
  __O  uint32_t PDRUNCFGCLR[1];                    /**< Clear bits in PDRUNCFGn, array offset: 0x630, array step: 0x4 */
       uint8_t RESERVED_34[76];
  __IO uint32_t STARTER[1];                        /**< Start logic n wake-up enable register, array offset: 0x680, array step: 0x4 */
       uint8_t RESERVED_35[28];
  __O  uint32_t STARTERSET[1];                     /**< Set bits in STARTERn, array offset: 0x6A0, array step: 0x4 */
       uint8_t RESERVED_36[28];
  __O  uint32_t STARTERCLR[1];                     /**< Clear bits in STARTERn, array offset: 0x6C0, array step: 0x4 */
       uint8_t RESERVED_37[188];
  __IO uint32_t HWWAKE;                            /**< Configures special cases of hardware wake-up, offset: 0x780 */
       uint8_t RESERVED_38[2160];
  __I  uint32_t JTAGIDCODE;                        /**< JTAG ID code register, offset: 0xFF4 */
  __I  uint32_t DEVICE_ID0;                        /**< Part ID register, offset: 0xFF8 */
  __I  uint32_t DEVICE_ID1;                        /**< Boot ROM and die revision register, offset: 0xFFC */
       uint8_t RESERVED_39[127044];
  __IO uint32_t BODCTRL;                           /**< Brown-Out Detect control, offset: 0x20044 */
} SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Register_Masks SYSCON Register Masks
 * @{
 */

/*! @name AHBMATPRIO - AHB multilayer matrix priority control */
/*! @{ */
#define SYSCON_AHBMATPRIO_PRI_ICODE_MASK         (0x3U)
#define SYSCON_AHBMATPRIO_PRI_ICODE_SHIFT        (0U)
/*! PRI_ICODE - Cortex-M4 I-Code bus priority. Should typically be lower than PRI_DCODE for best operation.
 */
#define SYSCON_AHBMATPRIO_PRI_ICODE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_ICODE_SHIFT)) & SYSCON_AHBMATPRIO_PRI_ICODE_MASK)
#define SYSCON_AHBMATPRIO_PRI_DCODE_MASK         (0xCU)
#define SYSCON_AHBMATPRIO_PRI_DCODE_SHIFT        (2U)
/*! PRI_DCODE - Cortex M4 D-Code bus priority.
 */
#define SYSCON_AHBMATPRIO_PRI_DCODE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_DCODE_SHIFT)) & SYSCON_AHBMATPRIO_PRI_DCODE_MASK)
#define SYSCON_AHBMATPRIO_PRI_SYS_MASK           (0x30U)
#define SYSCON_AHBMATPRIO_PRI_SYS_SHIFT          (4U)
/*! PRI_SYS - Cortex M4 System bus priority.
 */
#define SYSCON_AHBMATPRIO_PRI_SYS(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_SYS_SHIFT)) & SYSCON_AHBMATPRIO_PRI_SYS_MASK)
#define SYSCON_AHBMATPRIO_PRI_M0_MASK            (0xC0U)
#define SYSCON_AHBMATPRIO_PRI_M0_SHIFT           (6U)
/*! PRI_M0 - Cortex-M0+ bus priority. Present on selected devices.
 */
#define SYSCON_AHBMATPRIO_PRI_M0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_M0_SHIFT)) & SYSCON_AHBMATPRIO_PRI_M0_MASK)
#define SYSCON_AHBMATPRIO_PRI_USB_MASK           (0x300U)
#define SYSCON_AHBMATPRIO_PRI_USB_SHIFT          (8U)
/*! PRI_USB - USB interface priority.
 */
#define SYSCON_AHBMATPRIO_PRI_USB(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_USB_SHIFT)) & SYSCON_AHBMATPRIO_PRI_USB_MASK)
#define SYSCON_AHBMATPRIO_PRI_DMA_MASK           (0xC00U)
#define SYSCON_AHBMATPRIO_PRI_DMA_SHIFT          (10U)
/*! PRI_DMA - DMA controller priority.
 */
#define SYSCON_AHBMATPRIO_PRI_DMA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBMATPRIO_PRI_DMA_SHIFT)) & SYSCON_AHBMATPRIO_PRI_DMA_MASK)
/*! @} */

/*! @name SYSTCKCAL - System tick counter calibration */
/*! @{ */
#define SYSCON_SYSTCKCAL_CAL_MASK                (0xFFFFFFU)
#define SYSCON_SYSTCKCAL_CAL_SHIFT               (0U)
/*! CAL - System tick timer calibration value.
 */
#define SYSCON_SYSTCKCAL_CAL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_CAL_SHIFT)) & SYSCON_SYSTCKCAL_CAL_MASK)
#define SYSCON_SYSTCKCAL_SKEW_MASK               (0x1000000U)
#define SYSCON_SYSTCKCAL_SKEW_SHIFT              (24U)
/*! SKEW - Initial value for the Systick timer.
 */
#define SYSCON_SYSTCKCAL_SKEW(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_SKEW_SHIFT)) & SYSCON_SYSTCKCAL_SKEW_MASK)
#define SYSCON_SYSTCKCAL_NOREF_MASK              (0x2000000U)
#define SYSCON_SYSTCKCAL_NOREF_SHIFT             (25U)
/*! NOREF - Initial value for the Systick timer.
 */
#define SYSCON_SYSTCKCAL_NOREF(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_NOREF_SHIFT)) & SYSCON_SYSTCKCAL_NOREF_MASK)
/*! @} */

/*! @name NMISRC - NMI Source Select */
/*! @{ */
#define SYSCON_NMISRC_IRQM4_MASK                 (0x3FU)
#define SYSCON_NMISRC_IRQM4_SHIFT                (0U)
/*! IRQM4 - The IRQ number of the interrupt that acts as the Non-Maskable Interrupt (NMI) for the Cortex-M4, if enabled by NMIENM4.
 */
#define SYSCON_NMISRC_IRQM4(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_IRQM4_SHIFT)) & SYSCON_NMISRC_IRQM4_MASK)
#define SYSCON_NMISRC_IRQM0_MASK                 (0x3F00U)
#define SYSCON_NMISRC_IRQM0_SHIFT                (8U)
/*! IRQM0 - The IRQ number of the interrupt that acts as the Non-Maskable Interrupt (NMI) for the
 *    Cortex-M0+, if enabled by NMIENM0. Present on selected devices.
 */
#define SYSCON_NMISRC_IRQM0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_IRQM0_SHIFT)) & SYSCON_NMISRC_IRQM0_MASK)
#define SYSCON_NMISRC_NMIENM0_MASK               (0x40000000U)
#define SYSCON_NMISRC_NMIENM0_SHIFT              (30U)
/*! NMIENM0 - Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by IRQM0. Present on selected devices.
 */
#define SYSCON_NMISRC_NMIENM0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_NMIENM0_SHIFT)) & SYSCON_NMISRC_NMIENM0_MASK)
#define SYSCON_NMISRC_NMIENM4_MASK               (0x80000000U)
#define SYSCON_NMISRC_NMIENM4_SHIFT              (31U)
/*! NMIENM4 - Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by IRQM4.
 */
#define SYSCON_NMISRC_NMIENM4(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_NMIENM4_SHIFT)) & SYSCON_NMISRC_NMIENM4_MASK)
/*! @} */

/*! @name ASYNCAPBCTRL - Asynchronous APB Control */
/*! @{ */
#define SYSCON_ASYNCAPBCTRL_ENABLE_MASK          (0x1U)
#define SYSCON_ASYNCAPBCTRL_ENABLE_SHIFT         (0U)
/*! ENABLE - Enables the asynchronous APB bridge and subsystem.
 *  0b0..Disabled. Asynchronous APB bridge is disabled.
 *  0b1..Enabled. Asynchronous APB bridge is enabled.
 */
#define SYSCON_ASYNCAPBCTRL_ENABLE(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_ASYNCAPBCTRL_ENABLE_SHIFT)) & SYSCON_ASYNCAPBCTRL_ENABLE_MASK)
/*! @} */

/*! @name PIOPORCAP - POR captured value of port n */
/*! @{ */
#define SYSCON_PIOPORCAP_PIOPORCAP_MASK          (0xFFFFFFFFU)
#define SYSCON_PIOPORCAP_PIOPORCAP_SHIFT         (0U)
/*! PIOPORCAP - State of PIOn_31 through PIOn_0 at power-on reset
 */
#define SYSCON_PIOPORCAP_PIOPORCAP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PIOPORCAP_PIOPORCAP_SHIFT)) & SYSCON_PIOPORCAP_PIOPORCAP_MASK)
/*! @} */

/* The count of SYSCON_PIOPORCAP */
#define SYSCON_PIOPORCAP_COUNT                   (2U)

/*! @name PIORESCAP - Reset captured value of port n */
/*! @{ */
#define SYSCON_PIORESCAP_PIORESCAP_MASK          (0xFFFFFFFFU)
#define SYSCON_PIORESCAP_PIORESCAP_SHIFT         (0U)
/*! PIORESCAP - State of PIOn_31 through PIOn_0 for resets other than POR.
 */
#define SYSCON_PIORESCAP_PIORESCAP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PIORESCAP_PIORESCAP_SHIFT)) & SYSCON_PIORESCAP_PIORESCAP_MASK)
/*! @} */

/* The count of SYSCON_PIORESCAP */
#define SYSCON_PIORESCAP_COUNT                   (2U)

/*! @name PRESETCTRL - Peripheral reset control n */
/*! @{ */
#define SYSCON_PRESETCTRL_MRT0_RST_MASK          (0x1U)
#define SYSCON_PRESETCTRL_MRT0_RST_SHIFT         (0U)
/*! MRT0_RST - Multi-rate timer (MRT0) reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_MRT0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MRT0_RST_SHIFT)) & SYSCON_PRESETCTRL_MRT0_RST_MASK)
#define SYSCON_PRESETCTRL_SCT0_RST_MASK          (0x4U)
#define SYSCON_PRESETCTRL_SCT0_RST_SHIFT         (2U)
/*! SCT0_RST - State configurable timer 0 (SCT0) reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_SCT0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_SCT0_RST_SHIFT)) & SYSCON_PRESETCTRL_SCT0_RST_MASK)
#define SYSCON_PRESETCTRL_FLASH_RST_MASK         (0x80U)
#define SYSCON_PRESETCTRL_FLASH_RST_SHIFT        (7U)
/*! FLASH_RST - Flash controller reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FLASH_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FLASH_RST_SHIFT)) & SYSCON_PRESETCTRL_FLASH_RST_MASK)
#define SYSCON_PRESETCTRL_FMC_RST_MASK           (0x100U)
#define SYSCON_PRESETCTRL_FMC_RST_SHIFT          (8U)
/*! FMC_RST - Flash accelerator reset control. Note that the FMC must not be reset while executing
 *    from flash, and must be reconfigured after reset. 0 = Clear reset to this function. 1 = Assert
 *    reset to this function.
 */
#define SYSCON_PRESETCTRL_FMC_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FMC_RST_SHIFT)) & SYSCON_PRESETCTRL_FMC_RST_MASK)
#define SYSCON_PRESETCTRL_UTICK0_RST_MASK        (0x400U)
#define SYSCON_PRESETCTRL_UTICK0_RST_SHIFT       (10U)
/*! UTICK0_RST - Micro-tick Timer reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_UTICK0_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_UTICK0_RST_SHIFT)) & SYSCON_PRESETCTRL_UTICK0_RST_MASK)
#define SYSCON_PRESETCTRL_FC0_RST_MASK           (0x800U)
#define SYSCON_PRESETCTRL_FC0_RST_SHIFT          (11U)
/*! FC0_RST - Flexcomm 0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC0_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC0_RST_SHIFT)) & SYSCON_PRESETCTRL_FC0_RST_MASK)
#define SYSCON_PRESETCTRL_MUX_RST_MASK           (0x800U)
#define SYSCON_PRESETCTRL_MUX_RST_SHIFT          (11U)
/*! MUX_RST - Input mux reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_MUX_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_MUX_RST_SHIFT)) & SYSCON_PRESETCTRL_MUX_RST_MASK)
#define SYSCON_PRESETCTRL_FC1_RST_MASK           (0x1000U)
#define SYSCON_PRESETCTRL_FC1_RST_SHIFT          (12U)
/*! FC1_RST - Flexcomm 1 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC1_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC1_RST_SHIFT)) & SYSCON_PRESETCTRL_FC1_RST_MASK)
#define SYSCON_PRESETCTRL_FC2_RST_MASK           (0x2000U)
#define SYSCON_PRESETCTRL_FC2_RST_SHIFT          (13U)
/*! FC2_RST - Flexcomm 2 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC2_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC2_RST_SHIFT)) & SYSCON_PRESETCTRL_FC2_RST_MASK)
#define SYSCON_PRESETCTRL_IOCON_RST_MASK         (0x2000U)
#define SYSCON_PRESETCTRL_IOCON_RST_SHIFT        (13U)
/*! IOCON_RST - IOCON reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_IOCON_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_IOCON_RST_SHIFT)) & SYSCON_PRESETCTRL_IOCON_RST_MASK)
#define SYSCON_PRESETCTRL_FC3_RST_MASK           (0x4000U)
#define SYSCON_PRESETCTRL_FC3_RST_SHIFT          (14U)
/*! FC3_RST - Flexcomm 3 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC3_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC3_RST_SHIFT)) & SYSCON_PRESETCTRL_FC3_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO0_RST_MASK         (0x4000U)
#define SYSCON_PRESETCTRL_GPIO0_RST_SHIFT        (14U)
/*! GPIO0_RST - GPIO0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_GPIO0_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO0_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO0_RST_MASK)
#define SYSCON_PRESETCTRL_FC4_RST_MASK           (0x8000U)
#define SYSCON_PRESETCTRL_FC4_RST_SHIFT          (15U)
/*! FC4_RST - Flexcomm 4 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC4_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC4_RST_SHIFT)) & SYSCON_PRESETCTRL_FC4_RST_MASK)
#define SYSCON_PRESETCTRL_GPIO1_RST_MASK         (0x8000U)
#define SYSCON_PRESETCTRL_GPIO1_RST_SHIFT        (15U)
/*! GPIO1_RST - GPIO1 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_GPIO1_RST(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GPIO1_RST_SHIFT)) & SYSCON_PRESETCTRL_GPIO1_RST_MASK)
#define SYSCON_PRESETCTRL_FC5_RST_MASK           (0x10000U)
#define SYSCON_PRESETCTRL_FC5_RST_SHIFT          (16U)
/*! FC5_RST - Flexcomm 5 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC5_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC5_RST_SHIFT)) & SYSCON_PRESETCTRL_FC5_RST_MASK)
#define SYSCON_PRESETCTRL_FC6_RST_MASK           (0x20000U)
#define SYSCON_PRESETCTRL_FC6_RST_SHIFT          (17U)
/*! FC6_RST - Flexcomm 6 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC6_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC6_RST_SHIFT)) & SYSCON_PRESETCTRL_FC6_RST_MASK)
#define SYSCON_PRESETCTRL_FC7_RST_MASK           (0x40000U)
#define SYSCON_PRESETCTRL_FC7_RST_SHIFT          (18U)
/*! FC7_RST - Flexcomm 7 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_FC7_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_FC7_RST_SHIFT)) & SYSCON_PRESETCTRL_FC7_RST_MASK)
#define SYSCON_PRESETCTRL_PINT_RST_MASK          (0x40000U)
#define SYSCON_PRESETCTRL_PINT_RST_SHIFT         (18U)
/*! PINT_RST - Pin interrupt (PINT) reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_PINT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_PINT_RST_SHIFT)) & SYSCON_PRESETCTRL_PINT_RST_MASK)
#define SYSCON_PRESETCTRL_GINT_RST_MASK          (0x80000U)
#define SYSCON_PRESETCTRL_GINT_RST_SHIFT         (19U)
/*! GINT_RST - Grouped interrupt (GINT) reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_GINT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_GINT_RST_SHIFT)) & SYSCON_PRESETCTRL_GINT_RST_MASK)
#define SYSCON_PRESETCTRL_DMA0_RST_MASK          (0x100000U)
#define SYSCON_PRESETCTRL_DMA0_RST_SHIFT         (20U)
/*! DMA0_RST - DMA0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_DMA0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_DMA0_RST_SHIFT)) & SYSCON_PRESETCTRL_DMA0_RST_MASK)
#define SYSCON_PRESETCTRL_CRC_RST_MASK           (0x200000U)
#define SYSCON_PRESETCTRL_CRC_RST_SHIFT          (21U)
/*! CRC_RST - CRC generator reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_CRC_RST(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CRC_RST_SHIFT)) & SYSCON_PRESETCTRL_CRC_RST_MASK)
#define SYSCON_PRESETCTRL_WWDT_RST_MASK          (0x400000U)
#define SYSCON_PRESETCTRL_WWDT_RST_SHIFT         (22U)
/*! WWDT_RST - Watchdog timer reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_WWDT_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_WWDT_RST_SHIFT)) & SYSCON_PRESETCTRL_WWDT_RST_MASK)
#define SYSCON_PRESETCTRL_USB0_RST_MASK          (0x2000000U)
#define SYSCON_PRESETCTRL_USB0_RST_SHIFT         (25U)
/*! USB0_RST - USB0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_USB0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_USB0_RST_SHIFT)) & SYSCON_PRESETCTRL_USB0_RST_MASK)
#define SYSCON_PRESETCTRL_CTIMER0_RST_MASK       (0x4000000U)
#define SYSCON_PRESETCTRL_CTIMER0_RST_SHIFT      (26U)
/*! CTIMER0_RST - CTIMER0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_CTIMER0_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CTIMER0_RST_SHIFT)) & SYSCON_PRESETCTRL_CTIMER0_RST_MASK)
#define SYSCON_PRESETCTRL_ADC0_RST_MASK          (0x8000000U)
#define SYSCON_PRESETCTRL_ADC0_RST_SHIFT         (27U)
/*! ADC0_RST - ADC0 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_ADC0_RST(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_ADC0_RST_SHIFT)) & SYSCON_PRESETCTRL_ADC0_RST_MASK)
#define SYSCON_PRESETCTRL_CTIMER1_RST_MASK       (0x8000000U)
#define SYSCON_PRESETCTRL_CTIMER1_RST_SHIFT      (27U)
/*! CTIMER1_RST - CTIMER1 reset control. 0 = Clear reset to this function. 1 = Assert reset to this function.
 */
#define SYSCON_PRESETCTRL_CTIMER1_RST(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL_CTIMER1_RST_SHIFT)) & SYSCON_PRESETCTRL_CTIMER1_RST_MASK)
/*! @} */

/* The count of SYSCON_PRESETCTRL */
#define SYSCON_PRESETCTRL_COUNT                  (2U)

/*! @name PRESETCTRLSET - Set bits in PRESETCTRLn */
/*! @{ */
#define SYSCON_PRESETCTRLSET_RST_SET_MASK        (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLSET_RST_SET_SHIFT       (0U)
/*! RST_SET - Writing ones to this register sets the corresponding bit or bits in the PRESETCTRLn
 *    register, if they are implemented. Bits that do not correspond to defined bits in PRESETCTRLn
 *    are reserved and only zeroes should be written to them.
 */
#define SYSCON_PRESETCTRLSET_RST_SET(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLSET_RST_SET_SHIFT)) & SYSCON_PRESETCTRLSET_RST_SET_MASK)
/*! @} */

/* The count of SYSCON_PRESETCTRLSET */
#define SYSCON_PRESETCTRLSET_COUNT               (2U)

/*! @name PRESETCTRLCLR - Clear bits in PRESETCTRLn */
/*! @{ */
#define SYSCON_PRESETCTRLCLR_RST_CLR_MASK        (0xFFFFFFFFU)
#define SYSCON_PRESETCTRLCLR_RST_CLR_SHIFT       (0U)
/*! RST_CLR - Writing ones to this register clears the corresponding bit or bits in the PRESETCTRLn
 *    register, if they are implemented. Bits that do not correspond to defined bits in PRESETCTRLn
 *    are reserved and only zeroes should be written to them.
 */
#define SYSCON_PRESETCTRLCLR_RST_CLR(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRLCLR_RST_CLR_SHIFT)) & SYSCON_PRESETCTRLCLR_RST_CLR_MASK)
/*! @} */

/* The count of SYSCON_PRESETCTRLCLR */
#define SYSCON_PRESETCTRLCLR_COUNT               (2U)

/*! @name SYSRSTSTAT - System reset status register */
/*! @{ */
#define SYSCON_SYSRSTSTAT_POR_MASK               (0x1U)
#define SYSCON_SYSRSTSTAT_POR_SHIFT              (0U)
/*! POR - POR reset status
 *  0b0..No POR detected
 *  0b1..POR detected. Writing a one clears this reset.
 */
#define SYSCON_SYSRSTSTAT_POR(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_POR_SHIFT)) & SYSCON_SYSRSTSTAT_POR_MASK)
#define SYSCON_SYSRSTSTAT_EXTRST_MASK            (0x2U)
#define SYSCON_SYSRSTSTAT_EXTRST_SHIFT           (1U)
/*! EXTRST - Status of the external RESET pin. External reset status
 *  0b0..No reset event detected.
 *  0b1..Reset detected. Writing a one clears this reset.
 */
#define SYSCON_SYSRSTSTAT_EXTRST(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_EXTRST_SHIFT)) & SYSCON_SYSRSTSTAT_EXTRST_MASK)
#define SYSCON_SYSRSTSTAT_WDT_MASK               (0x4U)
#define SYSCON_SYSRSTSTAT_WDT_SHIFT              (2U)
/*! WDT - Status of the Watchdog reset
 *  0b0..No WDT reset detected
 *  0b1..WDT reset detected. Writing a one clears this reset.
 */
#define SYSCON_SYSRSTSTAT_WDT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_WDT_SHIFT)) & SYSCON_SYSRSTSTAT_WDT_MASK)
#define SYSCON_SYSRSTSTAT_BOD_MASK               (0x8U)
#define SYSCON_SYSRSTSTAT_BOD_SHIFT              (3U)
/*! BOD - Status of the Brown-out detect reset
 *  0b0..No BOD reset detected
 *  0b1..BOD reset detected. Writing a one clears this reset.
 */
#define SYSCON_SYSRSTSTAT_BOD(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_BOD_SHIFT)) & SYSCON_SYSRSTSTAT_BOD_MASK)
#define SYSCON_SYSRSTSTAT_SYSRST_MASK            (0x10U)
#define SYSCON_SYSRSTSTAT_SYSRST_SHIFT           (4U)
/*! SYSRST - Status of the software system reset
 *  0b0..No System reset detected
 *  0b1..System reset detected. Writing a one clears this reset.
 */
#define SYSCON_SYSRSTSTAT_SYSRST(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSRSTSTAT_SYSRST_SHIFT)) & SYSCON_SYSRSTSTAT_SYSRST_MASK)
/*! @} */

/*! @name AHBCLKCTRL - AHB Clock control n */
/*! @{ */
#define SYSCON_AHBCLKCTRL_MRT0_MASK              (0x1U)
#define SYSCON_AHBCLKCTRL_MRT0_SHIFT             (0U)
/*! MRT0 - Enables the clock for the Multi-Rate Timer. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_MRT0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_MRT0_SHIFT)) & SYSCON_AHBCLKCTRL_MRT0_MASK)
#define SYSCON_AHBCLKCTRL_ROM_MASK               (0x2U)
#define SYSCON_AHBCLKCTRL_ROM_SHIFT              (1U)
/*! ROM - Enables the clock for the Boot ROM. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_ROM(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_ROM_SHIFT)) & SYSCON_AHBCLKCTRL_ROM_MASK)
#define SYSCON_AHBCLKCTRL_SCT0_MASK              (0x4U)
#define SYSCON_AHBCLKCTRL_SCT0_SHIFT             (2U)
/*! SCT0 - Enables the clock for SCT0. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_SCT0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_SCT0_SHIFT)) & SYSCON_AHBCLKCTRL_SCT0_MASK)
#define SYSCON_AHBCLKCTRL_FLASH_MASK             (0x80U)
#define SYSCON_AHBCLKCTRL_FLASH_SHIFT            (7U)
/*! FLASH - Enables the clock for the flash controller. 0 = Disable; 1 = Enable. This clock is
 *    needed for flash programming, not for flash read.
 */
#define SYSCON_AHBCLKCTRL_FLASH(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLASH_SHIFT)) & SYSCON_AHBCLKCTRL_FLASH_MASK)
#define SYSCON_AHBCLKCTRL_FMC_MASK               (0x100U)
#define SYSCON_AHBCLKCTRL_FMC_SHIFT              (8U)
/*! FMC - Enables the clock for the Flash accelerator. 0 = Disable; 1 = Enable. This clock is needed if the flash is being read.
 */
#define SYSCON_AHBCLKCTRL_FMC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FMC_SHIFT)) & SYSCON_AHBCLKCTRL_FMC_MASK)
#define SYSCON_AHBCLKCTRL_UTICK0_MASK            (0x400U)
#define SYSCON_AHBCLKCTRL_UTICK0_SHIFT           (10U)
/*! UTICK0 - Enables the clock for the Micro-tick Timer. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_UTICK0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_UTICK0_SHIFT)) & SYSCON_AHBCLKCTRL_UTICK0_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM0_MASK         (0x800U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM0_SHIFT        (11U)
/*! FLEXCOMM0 - Enables the clock for Flexcomm 0. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM0_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM0_MASK)
#define SYSCON_AHBCLKCTRL_INPUTMUX_MASK          (0x800U)
#define SYSCON_AHBCLKCTRL_INPUTMUX_SHIFT         (11U)
/*! INPUTMUX - Enables the clock for the input muxes. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_INPUTMUX(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_INPUTMUX_SHIFT)) & SYSCON_AHBCLKCTRL_INPUTMUX_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM1_MASK         (0x1000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM1_SHIFT        (12U)
/*! FLEXCOMM1 - Enables the clock for Flexcomm 1. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM1_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM1_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM2_MASK         (0x2000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM2_SHIFT        (13U)
/*! FLEXCOMM2 - Enables the clock for Flexcomm 2. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM2(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM2_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM2_MASK)
#define SYSCON_AHBCLKCTRL_IOCON_MASK             (0x2000U)
#define SYSCON_AHBCLKCTRL_IOCON_SHIFT            (13U)
/*! IOCON - Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_IOCON(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_IOCON_SHIFT)) & SYSCON_AHBCLKCTRL_IOCON_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM3_MASK         (0x4000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM3_SHIFT        (14U)
/*! FLEXCOMM3 - Enables the clock for Flexcomm 3. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM3(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM3_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM3_MASK)
#define SYSCON_AHBCLKCTRL_GPIO0_MASK             (0x4000U)
#define SYSCON_AHBCLKCTRL_GPIO0_SHIFT            (14U)
/*! GPIO0 - Enables the clock for the GPIO0 port registers. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_GPIO0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO0_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO0_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM4_MASK         (0x8000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM4_SHIFT        (15U)
/*! FLEXCOMM4 - Enables the clock for Flexcomm 4. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM4(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM4_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM4_MASK)
#define SYSCON_AHBCLKCTRL_GPIO1_MASK             (0x8000U)
#define SYSCON_AHBCLKCTRL_GPIO1_SHIFT            (15U)
/*! GPIO1 - Enables the clock for the GPIO1 port registers. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_GPIO1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GPIO1_SHIFT)) & SYSCON_AHBCLKCTRL_GPIO1_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM5_MASK         (0x10000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM5_SHIFT        (16U)
/*! FLEXCOMM5 - Enables the clock for Flexcomm 5. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM5(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM5_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM5_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM6_MASK         (0x20000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM6_SHIFT        (17U)
/*! FLEXCOMM6 - Enables the clock for Flexcomm 6. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM6(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM6_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM6_MASK)
#define SYSCON_AHBCLKCTRL_FLEXCOMM7_MASK         (0x40000U)
#define SYSCON_AHBCLKCTRL_FLEXCOMM7_SHIFT        (18U)
/*! FLEXCOMM7 - Enables the clock for Flexcomm 7. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_FLEXCOMM7(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_FLEXCOMM7_SHIFT)) & SYSCON_AHBCLKCTRL_FLEXCOMM7_MASK)
#define SYSCON_AHBCLKCTRL_PINT_MASK              (0x40000U)
#define SYSCON_AHBCLKCTRL_PINT_SHIFT             (18U)
/*! PINT - Enables the clock for the pin interrupt block.0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_PINT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_PINT_SHIFT)) & SYSCON_AHBCLKCTRL_PINT_MASK)
#define SYSCON_AHBCLKCTRL_GINT_MASK              (0x80000U)
#define SYSCON_AHBCLKCTRL_GINT_SHIFT             (19U)
/*! GINT - Enables the clock for the grouped pin interrupt block. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_GINT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_GINT_SHIFT)) & SYSCON_AHBCLKCTRL_GINT_MASK)
#define SYSCON_AHBCLKCTRL_DMA0_MASK              (0x100000U)
#define SYSCON_AHBCLKCTRL_DMA0_SHIFT             (20U)
/*! DMA0 - Enables the clock for the DMA0 controller. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_DMA0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_DMA0_SHIFT)) & SYSCON_AHBCLKCTRL_DMA0_MASK)
#define SYSCON_AHBCLKCTRL_CRC_MASK               (0x200000U)
#define SYSCON_AHBCLKCTRL_CRC_SHIFT              (21U)
/*! CRC - Enables the clock for the CRC engine. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_CRC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CRC_SHIFT)) & SYSCON_AHBCLKCTRL_CRC_MASK)
#define SYSCON_AHBCLKCTRL_WWDT_MASK              (0x400000U)
#define SYSCON_AHBCLKCTRL_WWDT_SHIFT             (22U)
/*! WWDT - Enables the clock for the Watchdog Timer. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_WWDT(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_WWDT_SHIFT)) & SYSCON_AHBCLKCTRL_WWDT_MASK)
#define SYSCON_AHBCLKCTRL_RTC_MASK               (0x800000U)
#define SYSCON_AHBCLKCTRL_RTC_SHIFT              (23U)
/*! RTC - Enables the bus clock for the RTC. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_RTC(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_RTC_SHIFT)) & SYSCON_AHBCLKCTRL_RTC_MASK)
#define SYSCON_AHBCLKCTRL_USB0_MASK              (0x2000000U)
#define SYSCON_AHBCLKCTRL_USB0_SHIFT             (25U)
/*! USB0 - Enables the clock for the USB0 interface. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_USB0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_USB0_SHIFT)) & SYSCON_AHBCLKCTRL_USB0_MASK)
#define SYSCON_AHBCLKCTRL_CTIMER0_MASK           (0x4000000U)
#define SYSCON_AHBCLKCTRL_CTIMER0_SHIFT          (26U)
/*! CTIMER0 - Enables the clock for timer CTIMER0. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_CTIMER0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CTIMER0_SHIFT)) & SYSCON_AHBCLKCTRL_CTIMER0_MASK)
#define SYSCON_AHBCLKCTRL_ADC0_MASK              (0x8000000U)
#define SYSCON_AHBCLKCTRL_ADC0_SHIFT             (27U)
/*! ADC0 - Enables the clock for the ADC0 register interface. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_ADC0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_ADC0_SHIFT)) & SYSCON_AHBCLKCTRL_ADC0_MASK)
#define SYSCON_AHBCLKCTRL_CTIMER1_MASK           (0x8000000U)
#define SYSCON_AHBCLKCTRL_CTIMER1_SHIFT          (27U)
/*! CTIMER1 - Enables the clock for timer CTIMER1. 0 = Disable; 1 = Enable.
 */
#define SYSCON_AHBCLKCTRL_CTIMER1(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRL_CTIMER1_SHIFT)) & SYSCON_AHBCLKCTRL_CTIMER1_MASK)
/*! @} */

/* The count of SYSCON_AHBCLKCTRL */
#define SYSCON_AHBCLKCTRL_COUNT                  (2U)

/*! @name AHBCLKCTRLSET - Set bits in AHBCLKCTRLn */
/*! @{ */
#define SYSCON_AHBCLKCTRLSET_CLK_SET_MASK        (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLSET_CLK_SET_SHIFT       (0U)
/*! CLK_SET - Writing ones to this register sets the corresponding bit or bits in the AHBCLKCTRLn
 *    register, if they are implemented. Bits that do not correspond to defined bits in AHBCLKCTRLn
 *    are reserved and only zeroes should be written to them.
 */
#define SYSCON_AHBCLKCTRLSET_CLK_SET(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLSET_CLK_SET_SHIFT)) & SYSCON_AHBCLKCTRLSET_CLK_SET_MASK)
/*! @} */

/* The count of SYSCON_AHBCLKCTRLSET */
#define SYSCON_AHBCLKCTRLSET_COUNT               (2U)

/*! @name AHBCLKCTRLCLR - Clear bits in AHBCLKCTRLn */
/*! @{ */
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR_MASK        (0xFFFFFFFFU)
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR_SHIFT       (0U)
/*! CLK_CLR - Writing ones to this register clears the corresponding bit or bits in the AHBCLKCTRLn
 *    register, if they are implemented. Bits that do not correspond to defined bits in AHBCLKCTRLn
 *    are reserved and only zeroes should be written to them.
 */
#define SYSCON_AHBCLKCTRLCLR_CLK_CLR(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKCTRLCLR_CLK_CLR_SHIFT)) & SYSCON_AHBCLKCTRLCLR_CLK_CLR_MASK)
/*! @} */

/* The count of SYSCON_AHBCLKCTRLCLR */
#define SYSCON_AHBCLKCTRLCLR_COUNT               (2U)

/*! @name MAINCLKSELA - Main clock source select A */
/*! @{ */
#define SYSCON_MAINCLKSELA_SEL_MASK              (0x3U)
#define SYSCON_MAINCLKSELA_SEL_SHIFT             (0U)
/*! SEL - Clock source for main clock source selector A
 *  0b00..FRO 12 MHz (fro_12m)
 *  0b01..CLKIN (clk_in)
 *  0b10..Watchdog oscillator (wdt_clk)
 *  0b11..FRO 96 or 48 MHz (fro_hf)
 */
#define SYSCON_MAINCLKSELA_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELA_SEL_SHIFT)) & SYSCON_MAINCLKSELA_SEL_MASK)
/*! @} */

/*! @name MAINCLKSELB - Main clock source select B */
/*! @{ */
#define SYSCON_MAINCLKSELB_SEL_MASK              (0x3U)
#define SYSCON_MAINCLKSELB_SEL_SHIFT             (0U)
/*! SEL - Clock source for main clock source selector B. Selects the clock source for the main clock.
 *  0b00..MAINCLKSELA. Use the clock source selected in MAINCLKSELA register.
 *  0b01..Reserved setting
 *  0b10..System PLL output (pll_clk)
 *  0b11..RTC oscillator 32 kHz output (32k_clk)
 */
#define SYSCON_MAINCLKSELB_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSELB_SEL_SHIFT)) & SYSCON_MAINCLKSELB_SEL_MASK)
/*! @} */

/*! @name CLKOUTSELA - CLKOUT clock source select A */
/*! @{ */
#define SYSCON_CLKOUTSELA_SEL_MASK               (0x7U)
#define SYSCON_CLKOUTSELA_SEL_SHIFT              (0U)
/*! SEL - CLKOUT clock source selection
 *  0b000..Main clock (main_clk)
 *  0b001..CLKIN (clk_in)
 *  0b010..Watchdog oscillator (wdt_clk)
 *  0b011..FRO 96 or 48 MHz (fro_hf)
 *  0b100..PLL output (pll_clk)
 *  0b101..FRO 12 MHz (fro_12m)
 *  0b110..RTC oscillator 32 kHz output (32k_clk)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_CLKOUTSELA_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTSELA_SEL_SHIFT)) & SYSCON_CLKOUTSELA_SEL_MASK)
/*! @} */

/*! @name SYSPLLCLKSEL - PLL clock source select */
/*! @{ */
#define SYSCON_SYSPLLCLKSEL_SEL_MASK             (0x7U)
#define SYSCON_SYSPLLCLKSEL_SEL_SHIFT            (0U)
/*! SEL - System PLL clock source selection
 *  0b000..FRO 12 MHz (fro_12m)
 *  0b001..CLKIN (clk_in)
 *  0b011..RTC 32 kHz clock (32k_clk)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_SYSPLLCLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCLKSEL_SEL_SHIFT)) & SYSCON_SYSPLLCLKSEL_SEL_MASK)
/*! @} */

/*! @name ADCCLKSEL - ADC clock source select */
/*! @{ */
#define SYSCON_ADCCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_ADCCLKSEL_SEL_SHIFT               (0U)
/*! SEL - ADC clock source selection
 *  0b000..Main clock (main_clk)
 *  0b001..System PLL output (pll_clk)
 *  0b010..FRO 96 or 48 MHz (fro_hf)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_ADCCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKSEL_SEL_SHIFT)) & SYSCON_ADCCLKSEL_SEL_MASK)
/*! @} */

/*! @name USBCLKSEL - USB clock source select */
/*! @{ */
#define SYSCON_USBCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_USBCLKSEL_SEL_SHIFT               (0U)
/*! SEL - USB device clock source selection
 *  0b000..FRO 96 or 48 MHz (fro_hf)
 *  0b001..System PLL output (pll_clk)
 *  0b010..Main clock (main_clk)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_USBCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_USBCLKSEL_SEL_SHIFT)) & SYSCON_USBCLKSEL_SEL_MASK)
/*! @} */

/*! @name FXCOMCLKSEL - Flexcomm0 clock source select..Flexcomm7 clock source select */
/*! @{ */
#define SYSCON_FXCOMCLKSEL_SEL_MASK              (0x7U)
#define SYSCON_FXCOMCLKSEL_SEL_SHIFT             (0U)
/*! SEL - Flexcomm clock source selection. One per Flexcomm.
 *  0b000..FRO 12 MHz (fro_12m)
 *  0b001..FRO 96 or 48 MHz (fro_hf)
 *  0b010..System PLL output (pll_clk)
 *  0b011..MCLK pin input, when selected in IOCON (mclk_in)
 *  0b100..FRG clock, the output of the fractional rate generator (frg_clk)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_FXCOMCLKSEL_SEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FXCOMCLKSEL_SEL_SHIFT)) & SYSCON_FXCOMCLKSEL_SEL_MASK)
/*! @} */

/* The count of SYSCON_FXCOMCLKSEL */
#define SYSCON_FXCOMCLKSEL_COUNT                 (8U)

/*! @name MCLKCLKSEL - MCLK clock source select */
/*! @{ */
#define SYSCON_MCLKCLKSEL_SEL_MASK               (0x7U)
#define SYSCON_MCLKCLKSEL_SEL_SHIFT              (0U)
/*! SEL - MCLK source select. This may be used by Flexcomms that support I2S, and/or by the digital microphone subsystem.
 *  0b000..FRO 96 or 48 MHz (fro_hf)
 *  0b001..System PLL output (pll_clk)
 *  0b010..Main clock (main_clk)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_MCLKCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKCLKSEL_SEL_SHIFT)) & SYSCON_MCLKCLKSEL_SEL_MASK)
/*! @} */

/*! @name FRGCLKSEL - Fractional Rate Generator clock source select */
/*! @{ */
#define SYSCON_FRGCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_FRGCLKSEL_SEL_SHIFT               (0U)
/*! SEL - Fractional Rate Generator clock source select.
 *  0b000..Main clock (main_clk)
 *  0b001..System PLL output (pll_clk)
 *  0b010..FRO 12 MHz (fro_12m)
 *  0b011..FRO 96 or 48 MHz (fro_hf)
 *  0b111..None, this may be selected in order to reduce power when no output is needed.
 */
#define SYSCON_FRGCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCLKSEL_SEL_SHIFT)) & SYSCON_FRGCLKSEL_SEL_MASK)
/*! @} */

/*! @name SYSTICKCLKDIV - SYSTICK clock divider */
/*! @{ */
#define SYSCON_SYSTICKCLKDIV_DIV_MASK            (0xFFU)
#define SYSCON_SYSTICKCLKDIV_DIV_SHIFT           (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_SYSTICKCLKDIV_DIV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTICKCLKDIV_DIV_SHIFT)) & SYSCON_SYSTICKCLKDIV_DIV_MASK)
/*! @} */

/*! @name AHBCLKDIV - AHB clock divider */
/*! @{ */
#define SYSCON_AHBCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_AHBCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_AHBCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_AHBCLKDIV_DIV_SHIFT)) & SYSCON_AHBCLKDIV_DIV_MASK)
/*! @} */

/*! @name CLKOUTDIV - CLKOUT clock divider */
/*! @{ */
#define SYSCON_CLKOUTDIV_DIV_MASK                (0xFFU)
#define SYSCON_CLKOUTDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_CLKOUTDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_DIV_SHIFT)) & SYSCON_CLKOUTDIV_DIV_MASK)
/*! @} */

/*! @name ADCCLKDIV - ADC clock divider */
/*! @{ */
#define SYSCON_ADCCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_ADCCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_ADCCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_DIV_SHIFT)) & SYSCON_ADCCLKDIV_DIV_MASK)
/*! @} */

/*! @name USBCLKDIV - USB clock divider */
/*! @{ */
#define SYSCON_USBCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_USBCLKDIV_DIV_SHIFT               (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_USBCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_USBCLKDIV_DIV_SHIFT)) & SYSCON_USBCLKDIV_DIV_MASK)
/*! @} */

/*! @name FRGCTRL - Fractional rate divider */
/*! @{ */
#define SYSCON_FRGCTRL_DIV_MASK                  (0xFFU)
#define SYSCON_FRGCTRL_DIV_SHIFT                 (0U)
/*! DIV - Denominator of the fractional divider. DIV is equal to the programmed value +1. Always set
 *    to 0xFF to use with the fractional baud rate generator.
 */
#define SYSCON_FRGCTRL_DIV(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCTRL_DIV_SHIFT)) & SYSCON_FRGCTRL_DIV_MASK)
#define SYSCON_FRGCTRL_MULT_MASK                 (0xFF00U)
#define SYSCON_FRGCTRL_MULT_SHIFT                (8U)
/*! MULT - Numerator of the fractional divider. MULT is equal to the programmed value.
 */
#define SYSCON_FRGCTRL_MULT(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FRGCTRL_MULT_SHIFT)) & SYSCON_FRGCTRL_MULT_MASK)
/*! @} */

/*! @name MCLKDIV - I2S MCLK clock divider */
/*! @{ */
#define SYSCON_MCLKDIV_DIV_MASK                  (0xFFU)
#define SYSCON_MCLKDIV_DIV_SHIFT                 (0U)
/*! DIV - Clock divider value. 0: Divide by 1 up to 255: Divide by 256.
 */
#define SYSCON_MCLKDIV_DIV(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKDIV_DIV_SHIFT)) & SYSCON_MCLKDIV_DIV_MASK)
/*! @} */

/*! @name FLASHCFG - Flash wait states configuration */
/*! @{ */
#define SYSCON_FLASHCFG_FETCHCFG_MASK            (0x3U)
#define SYSCON_FLASHCFG_FETCHCFG_SHIFT           (0U)
/*! FETCHCFG - Instruction fetch configuration. This field determines how flash accelerator buffers are used for instruction fetches.
 *  0b00..Instruction fetches from flash are not buffered. Every fetch request from the CPU results in a read of
 *        the flash memory. This setting may use significantly more power than when buffering is enabled.
 *  0b01..One buffer is used for all instruction fetches.
 *  0b10..All buffers may be used for instruction fetches.
 *  0b11..Reserved setting, do not use.
 */
#define SYSCON_FLASHCFG_FETCHCFG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_FETCHCFG_SHIFT)) & SYSCON_FLASHCFG_FETCHCFG_MASK)
#define SYSCON_FLASHCFG_DATACFG_MASK             (0xCU)
#define SYSCON_FLASHCFG_DATACFG_SHIFT            (2U)
/*! DATACFG - Data read configuration. This field determines how flash accelerator buffers are used for data accesses.
 *  0b00..Data accesses from flash are not buffered. Every data access from the CPU results in a read of the flash memory.
 *  0b01..One buffer is used for all data accesses.
 *  0b10..All buffers may be used for data accesses.
 *  0b11..Reserved setting, do not use.
 */
#define SYSCON_FLASHCFG_DATACFG(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_DATACFG_SHIFT)) & SYSCON_FLASHCFG_DATACFG_MASK)
#define SYSCON_FLASHCFG_ACCEL_MASK               (0x10U)
#define SYSCON_FLASHCFG_ACCEL_SHIFT              (4U)
/*! ACCEL - Acceleration enable.
 *  0b0..Flash acceleration is disabled. Every flash read (including those fulfilled from a buffer) takes FLASHTIM
 *       + 1 system clocks. This allows more determinism at a cost of performance.
 *  0b1..Flash acceleration is enabled. Performance is enhanced, dependent on other FLASHCFG settings.
 */
#define SYSCON_FLASHCFG_ACCEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_ACCEL_SHIFT)) & SYSCON_FLASHCFG_ACCEL_MASK)
#define SYSCON_FLASHCFG_PREFEN_MASK              (0x20U)
#define SYSCON_FLASHCFG_PREFEN_SHIFT             (5U)
/*! PREFEN - Prefetch enable.
 *  0b0..No instruction prefetch is performed.
 *  0b1..If the FETCHCFG field is not 0, the next flash line following the current execution address is
 *       automatically prefetched if it is not already buffered.
 */
#define SYSCON_FLASHCFG_PREFEN(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_PREFEN_SHIFT)) & SYSCON_FLASHCFG_PREFEN_MASK)
#define SYSCON_FLASHCFG_PREFOVR_MASK             (0x40U)
#define SYSCON_FLASHCFG_PREFOVR_SHIFT            (6U)
/*! PREFOVR - Prefetch override. This bit only applies when PREFEN = 1 and a buffered instruction is
 *    completing for which the next flash line is not already buffered or being prefetched.
 *  0b0..Any previously initiated prefetch will be completed.
 *  0b1..Any previously initiated prefetch will be aborted, and the next flash line following the current
 *       execution address will be prefetched if not already buffered.
 */
#define SYSCON_FLASHCFG_PREFOVR(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_PREFOVR_SHIFT)) & SYSCON_FLASHCFG_PREFOVR_MASK)
#define SYSCON_FLASHCFG_FLASHTIM_MASK            (0xF000U)
#define SYSCON_FLASHCFG_FLASHTIM_SHIFT           (12U)
/*! FLASHTIM - Flash memory access time. The number of system clocks used for flash accesses is equal to FLASHTIM +1.
 *  0b0000..1 system clock flash access time (for system clock rates up to 12 MHz).
 *  0b0001..2 system clocks flash access time (for system clock rates up to 30 MHz).
 *  0b0010..3 system clocks flash access time (for system clock rates up to 60 MHz).
 *  0b0011..4 system clocks flash access time (for system clock rates up to 85 MHz).
 *  0b0100..5 system clocks flash access time (for system clock rates up to 100 MHz).
 */
#define SYSCON_FLASHCFG_FLASHTIM(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCFG_FLASHTIM_SHIFT)) & SYSCON_FLASHCFG_FLASHTIM_MASK)
/*! @} */

/*! @name USBCLKCTRL - USB clock control */
/*! @{ */
#define SYSCON_USBCLKCTRL_POL_CLK_MASK           (0x2U)
#define SYSCON_USBCLKCTRL_POL_CLK_SHIFT          (1U)
/*! POL_CLK - USB_NEED_CLK polarity for triggering the USB wake-up interrupt
 *  0b0..Falling edge of the USB_NEED_CLK triggers the USB wake-up (default).
 *  0b1..Rising edge of the USB_NEED_CLK triggers the USB wake-up.
 */
#define SYSCON_USBCLKCTRL_POL_CLK(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_USBCLKCTRL_POL_CLK_SHIFT)) & SYSCON_USBCLKCTRL_POL_CLK_MASK)
/*! @} */

/*! @name USBCLKSTAT - USB clock status */
/*! @{ */
#define SYSCON_USBCLKSTAT_NEED_CLKST_MASK        (0x1U)
#define SYSCON_USBCLKSTAT_NEED_CLKST_SHIFT       (0U)
/*! NEED_CLKST - USB_NEED_CLK signal status
 *  0b0..Low
 *  0b1..High
 */
#define SYSCON_USBCLKSTAT_NEED_CLKST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_USBCLKSTAT_NEED_CLKST_SHIFT)) & SYSCON_USBCLKSTAT_NEED_CLKST_MASK)
/*! @} */

/*! @name FREQMECTRL - Frequency measure register */
/*! @{ */
#define SYSCON_FREQMECTRL_CAPVAL_MASK            (0x3FFFU)
#define SYSCON_FREQMECTRL_CAPVAL_SHIFT           (0U)
/*! CAPVAL - Stores the capture result which is used to calculate the frequency of the target clock. This field is read-only.
 */
#define SYSCON_FREQMECTRL_CAPVAL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FREQMECTRL_CAPVAL_SHIFT)) & SYSCON_FREQMECTRL_CAPVAL_MASK)
#define SYSCON_FREQMECTRL_PROG_MASK              (0x80000000U)
#define SYSCON_FREQMECTRL_PROG_SHIFT             (31U)
/*! PROG - Set this bit to one to initiate a frequency measurement cycle. Hardware clears this bit
 *    when the measurement cycle has completed and there is valid capture data in the CAPVAL field
 *    (bits 13:0).
 */
#define SYSCON_FREQMECTRL_PROG(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FREQMECTRL_PROG_SHIFT)) & SYSCON_FREQMECTRL_PROG_MASK)
/*! @} */

/*! @name MCLKIO - MCLK input/output control */
/*! @{ */
#define SYSCON_MCLKIO_DIR_MASK                   (0x1U)
#define SYSCON_MCLKIO_DIR_SHIFT                  (0U)
/*! DIR - MCLK direction control.
 *  0b0..The MCLK function is an input.
 *  0b1..The MCLK function is an output.
 */
#define SYSCON_MCLKIO_DIR(x)                     (((uint32_t)(((uint32_t)(x)) << SYSCON_MCLKIO_DIR_SHIFT)) & SYSCON_MCLKIO_DIR_MASK)
/*! @} */

/*! @name FROCTRL - FRO oscillator control */
/*! @{ */
#define SYSCON_FROCTRL_TRIM_MASK                 (0x3FFFU)
#define SYSCON_FROCTRL_TRIM_SHIFT                (0U)
/*! TRIM - This value is factory trimmed to account for bias and temperature compensation. The value
 *    should not be changed by software. Also see the WRTRIM bit description.
 */
#define SYSCON_FROCTRL_TRIM(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_TRIM_SHIFT)) & SYSCON_FROCTRL_TRIM_MASK)
#define SYSCON_FROCTRL_SEL_MASK                  (0x4000U)
#define SYSCON_FROCTRL_SEL_SHIFT                 (14U)
/*! SEL - Select the fro_hf output frequency. This bit can only be changed by software when the
 *    WRTRIM bit = 1. Note that the factory trim values are for the 96 MHz FRO only.
 *  0b0..48 MHz
 *  0b1..96 MHz
 */
#define SYSCON_FROCTRL_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_SEL_SHIFT)) & SYSCON_FROCTRL_SEL_MASK)
#define SYSCON_FROCTRL_FREQTRIM_MASK             (0xFF0000U)
#define SYSCON_FROCTRL_FREQTRIM_SHIFT            (16U)
/*! FREQTRIM - Frequency trim. Boot code configures this to a device-specific factory trim value for
 *    the 48 MHz FRO. If USBCLKADJ = 1, this field is read-only and provides the value resulting
 *    from USB rate adjustment. See the USBMODCFG flag regarding reading this field. Application code
 *    may adjust this field when USBCLKADJ = 0. A single step of FREQTRIM is roughly equivalent to
 *    0.1% of the selected FRO frequency.
 */
#define SYSCON_FROCTRL_FREQTRIM(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_FREQTRIM_SHIFT)) & SYSCON_FROCTRL_FREQTRIM_MASK)
#define SYSCON_FROCTRL_USBCLKADJ_MASK            (0x1000000U)
#define SYSCON_FROCTRL_USBCLKADJ_SHIFT           (24U)
/*! USBCLKADJ - USB clock adjust mode.
 *  0b0..Normal operation.
 *  0b1..Automatic USB rate adjustment mode. If the USB FS device peripheral is enabled and connected to a USB
 *       host, it provides clock adjustment information to the FRO based on SOF packets. USB rate adjustment requires
 *       a number of cycles to take place. the USBMODCHG bit (see below) indicates when initial adjustment is
 *       complete, and when later adjustments are in progress. software must not alter TRIM and FREQTRIM while USBCLKADJ
 *       = 1. see USBCLKADJ usage notes below this table.
 */
#define SYSCON_FROCTRL_USBCLKADJ(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_USBCLKADJ_SHIFT)) & SYSCON_FROCTRL_USBCLKADJ_MASK)
#define SYSCON_FROCTRL_USBMODCHG_MASK            (0x2000000U)
#define SYSCON_FROCTRL_USBMODCHG_SHIFT           (25U)
/*! USBMODCHG - USB Mode value Change flag. When 1, indicates that the USB trim is currently being
 *    updated (or is still starting up) and software should wait to read FREQTRIM. Update occurs at
 *    most once per millisecond.
 */
#define SYSCON_FROCTRL_USBMODCHG(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_USBMODCHG_SHIFT)) & SYSCON_FROCTRL_USBMODCHG_MASK)
#define SYSCON_FROCTRL_HSPDCLK_MASK              (0x40000000U)
#define SYSCON_FROCTRL_HSPDCLK_SHIFT             (30U)
/*! HSPDCLK - High speed clock enable. Allows disabling the highs-speed FRO output if it is not needed.
 *  0b0..The high-speed FRO output is disabled.
 *  0b1..The selected high-speed FRO output (48 MHz or 96 MHz) is enabled.
 */
#define SYSCON_FROCTRL_HSPDCLK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_HSPDCLK_SHIFT)) & SYSCON_FROCTRL_HSPDCLK_MASK)
#define SYSCON_FROCTRL_WRTRIM_MASK               (0x80000000U)
#define SYSCON_FROCTRL_WRTRIM_SHIFT              (31U)
/*! WRTRIM - Write Trim value. Must be written to 1 to modify the SEL or TRIM fields, during the
 *    same write. This bit always reads as 0.
 */
#define SYSCON_FROCTRL_WRTRIM(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FROCTRL_WRTRIM_SHIFT)) & SYSCON_FROCTRL_WRTRIM_MASK)
/*! @} */

/*! @name WDTOSCCTRL - Watchdog oscillator control */
/*! @{ */
#define SYSCON_WDTOSCCTRL_DIVSEL_MASK            (0x1FU)
#define SYSCON_WDTOSCCTRL_DIVSEL_SHIFT           (0U)
/*! DIVSEL - Divider select. Selects the value of the divider that adjusts the output of the
 *    oscillator. 0x00 = divide by 2 0x01 = divide by 4 0x02 = divide by 6 up to 0x1E = divide by 62 0x1F =
 *    divide by 64
 */
#define SYSCON_WDTOSCCTRL_DIVSEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTOSCCTRL_DIVSEL_SHIFT)) & SYSCON_WDTOSCCTRL_DIVSEL_MASK)
#define SYSCON_WDTOSCCTRL_FREQSEL_MASK           (0x3E0U)
#define SYSCON_WDTOSCCTRL_FREQSEL_SHIFT          (5U)
/*! FREQSEL - Frequency select. Selects the frequency of the oscillator. 0x00 = invalid setting when
 *    watchdog oscillator is running 0x01 = 0.4 MHz 0x02 = 0.6 MHz 0x03 = 0.75 MHz 0x04 = 0.9 MHz
 *    0x05 = 1.0 MHz 0x06 = 1.2 MHz 0x07 = 1.3 MHz 0x08 = 1.4 MHz 0x09 = 1.5 MHz 0x0A = 1.6 MHz 0x0B
 *    = 1.7 MHz 0x0C = 1.8 MHz 0x0D = 1.9 MHz 0x0E = 2.0 MHz 0x0F = 2.05 MHz 0x10 = 2.1 MHz 0x11 =
 *    2.2 MHz 0x12 = 2.25 MHz 0x13 = 2.3 MHz 0x14 = 2.4 MHz 0x15 = 2.45 MHz 0x16 = 2.5 MHz 0x17 = 2.6
 *    MHz 0x18 = 2.65 MHz 0x19 = 2.7 MHz 0x1A = 2.8 MHz 0x1B = 2.85 MHz 0x1C = 2.9 MHz 0x1D = 2.95
 *    MHz 0x1E = 3.0 MHz 0x1F = 3.05 MHz
 */
#define SYSCON_WDTOSCCTRL_FREQSEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_WDTOSCCTRL_FREQSEL_SHIFT)) & SYSCON_WDTOSCCTRL_FREQSEL_MASK)
/*! @} */

/*! @name RTCOSCCTRL - RTC oscillator 32 kHz output control */
/*! @{ */
#define SYSCON_RTCOSCCTRL_EN_MASK                (0x1U)
#define SYSCON_RTCOSCCTRL_EN_SHIFT               (0U)
/*! EN - RTC 32 kHz clock enable.
 *  0b0..Disabled. RTC clock off.
 *  0b1..Enabled. RTC clock on.
 */
#define SYSCON_RTCOSCCTRL_EN(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_RTCOSCCTRL_EN_SHIFT)) & SYSCON_RTCOSCCTRL_EN_MASK)
/*! @} */

/*! @name SYSPLLCTRL - PLL control */
/*! @{ */
#define SYSCON_SYSPLLCTRL_SELR_MASK              (0xFU)
#define SYSCON_SYSPLLCTRL_SELR_SHIFT             (0U)
/*! SELR - Bandwidth select R value
 */
#define SYSCON_SYSPLLCTRL_SELR(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELR_SHIFT)) & SYSCON_SYSPLLCTRL_SELR_MASK)
#define SYSCON_SYSPLLCTRL_SELI_MASK              (0x3F0U)
#define SYSCON_SYSPLLCTRL_SELI_SHIFT             (4U)
/*! SELI - Bandwidth select I value.
 */
#define SYSCON_SYSPLLCTRL_SELI(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELI_SHIFT)) & SYSCON_SYSPLLCTRL_SELI_MASK)
#define SYSCON_SYSPLLCTRL_SELP_MASK              (0x7C00U)
#define SYSCON_SYSPLLCTRL_SELP_SHIFT             (10U)
/*! SELP - Bandwidth select P value
 */
#define SYSCON_SYSPLLCTRL_SELP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_SELP_SHIFT)) & SYSCON_SYSPLLCTRL_SELP_MASK)
#define SYSCON_SYSPLLCTRL_BYPASS_MASK            (0x8000U)
#define SYSCON_SYSPLLCTRL_BYPASS_SHIFT           (15U)
/*! BYPASS - PLL bypass control.
 *  0b0..Bypass disabled. PLL CCO is sent to the PLL post-dividers.
 *  0b1..Bypass enabled. PLL input clock is sent directly to the PLL output (default).
 */
#define SYSCON_SYSPLLCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_BYPASS_SHIFT)) & SYSCON_SYSPLLCTRL_BYPASS_MASK)
#define SYSCON_SYSPLLCTRL_BYPASSCCODIV2_MASK     (0x10000U)
#define SYSCON_SYSPLLCTRL_BYPASSCCODIV2_SHIFT    (16U)
/*! BYPASSCCODIV2 - Bypass feedback clock divide by 2.
 *  0b0..Divide by 2. The CCO feedback clock is divided by 2 in addition to the programmed M divide.
 *  0b1..Bypass. The CCO feedback clock is divided only by the programmed M divide.
 */
#define SYSCON_SYSPLLCTRL_BYPASSCCODIV2(x)       (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_BYPASSCCODIV2_SHIFT)) & SYSCON_SYSPLLCTRL_BYPASSCCODIV2_MASK)
#define SYSCON_SYSPLLCTRL_UPLIMOFF_MASK          (0x20000U)
#define SYSCON_SYSPLLCTRL_UPLIMOFF_SHIFT         (17U)
/*! UPLIMOFF - Disable upper frequency limiter.
 *  0b0..Normal mode.
 *  0b1..Upper frequency limiter disabled.
 */
#define SYSCON_SYSPLLCTRL_UPLIMOFF(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_UPLIMOFF_SHIFT)) & SYSCON_SYSPLLCTRL_UPLIMOFF_MASK)
#define SYSCON_SYSPLLCTRL_BANDSEL_MASK           (0x40000U)
#define SYSCON_SYSPLLCTRL_BANDSEL_SHIFT          (18U)
/*! BANDSEL - PLL filter control. Set this bit to one when the spread spectrum controller is
 *    disabled or at low frequencies. For spread spectrum mode: SEL_EXT = 0, BANDSEL = 0, and UPLIMOFF = 1.
 *  0b0..SSCG control. The PLL filter uses the parameters derived from the spread spectrum controller.
 *  0b1..MDEC control. The PLL filter uses the programmable fields SELP, SELR, and SELI in this register to control the filter constants.
 */
#define SYSCON_SYSPLLCTRL_BANDSEL(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_BANDSEL_SHIFT)) & SYSCON_SYSPLLCTRL_BANDSEL_MASK)
#define SYSCON_SYSPLLCTRL_DIRECTI_MASK           (0x80000U)
#define SYSCON_SYSPLLCTRL_DIRECTI_SHIFT          (19U)
/*! DIRECTI - PLL0 direct input enable
 *  0b0..Disabled. The PLL input divider (N divider) output is used to drive the PLL CCO.
 *  0b1..Enabled. The PLL input divider (N divider) is bypassed. the PLL input clock is used directly to drive the PLL CCO input.
 */
#define SYSCON_SYSPLLCTRL_DIRECTI(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_DIRECTI_SHIFT)) & SYSCON_SYSPLLCTRL_DIRECTI_MASK)
#define SYSCON_SYSPLLCTRL_DIRECTO_MASK           (0x100000U)
#define SYSCON_SYSPLLCTRL_DIRECTO_SHIFT          (20U)
/*! DIRECTO - PLL0 direct output enable.
 *  0b0..Disabled. The PLL output divider (P divider) is used to create the PLL output.
 *  0b1..Enabled. The PLL output divider (P divider) is bypassed, the PLL CCO output is used as the PLL output.
 */
#define SYSCON_SYSPLLCTRL_DIRECTO(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_DIRECTO_SHIFT)) & SYSCON_SYSPLLCTRL_DIRECTO_MASK)
/*! @} */

/*! @name SYSPLLSTAT - PLL status */
/*! @{ */
#define SYSCON_SYSPLLSTAT_LOCK_MASK              (0x1U)
#define SYSCON_SYSPLLSTAT_LOCK_SHIFT             (0U)
/*! LOCK - PLL0 lock indicator
 */
#define SYSCON_SYSPLLSTAT_LOCK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSTAT_LOCK_SHIFT)) & SYSCON_SYSPLLSTAT_LOCK_MASK)
/*! @} */

/*! @name SYSPLLNDEC - PLL N decoder */
/*! @{ */
#define SYSCON_SYSPLLNDEC_NDEC_MASK              (0x3FFU)
#define SYSCON_SYSPLLNDEC_NDEC_SHIFT             (0U)
/*! NDEC - Decoded N-divider coefficient value.
 */
#define SYSCON_SYSPLLNDEC_NDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLNDEC_NDEC_SHIFT)) & SYSCON_SYSPLLNDEC_NDEC_MASK)
#define SYSCON_SYSPLLNDEC_NREQ_MASK              (0x400U)
#define SYSCON_SYSPLLNDEC_NREQ_SHIFT             (10U)
/*! NREQ - NDEC reload request. When a 1 is written to this bit, the NDEC value is loaded into the
 *    PLL. Must be cleared by software for any subsequent load, or the PLL can be powered down and
 *    back up via the PDEN_SYS_PLL bit in the PDRUNCFG register if the NDEC value is changed.
 */
#define SYSCON_SYSPLLNDEC_NREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLNDEC_NREQ_SHIFT)) & SYSCON_SYSPLLNDEC_NREQ_MASK)
/*! @} */

/*! @name SYSPLLPDEC - PLL P decoder */
/*! @{ */
#define SYSCON_SYSPLLPDEC_PDEC_MASK              (0x7FU)
#define SYSCON_SYSPLLPDEC_PDEC_SHIFT             (0U)
/*! PDEC - Decoded P-divider coefficient value.
 */
#define SYSCON_SYSPLLPDEC_PDEC(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLPDEC_PDEC_SHIFT)) & SYSCON_SYSPLLPDEC_PDEC_MASK)
#define SYSCON_SYSPLLPDEC_PREQ_MASK              (0x80U)
#define SYSCON_SYSPLLPDEC_PREQ_SHIFT             (7U)
/*! PREQ - PDEC reload request. When a 1 is written to this bit, the PDEC value is loaded into the
 *    PLL. Must be cleared by software for any subsequent load, or the PLL can be powered down and
 *    back up via the PDEN_SYS_PLL bit in the PDRUNCFG register if the PDEC value is changed.
 */
#define SYSCON_SYSPLLPDEC_PREQ(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLPDEC_PREQ_SHIFT)) & SYSCON_SYSPLLPDEC_PREQ_MASK)
/*! @} */

/*! @name SYSPLLSSCTRL0 - PLL spread spectrum control 0 */
/*! @{ */
#define SYSCON_SYSPLLSSCTRL0_MDEC_MASK           (0x1FFFFU)
#define SYSCON_SYSPLLSSCTRL0_MDEC_SHIFT          (0U)
/*! MDEC - Decoded M-divider coefficient value.
 */
#define SYSCON_SYSPLLSSCTRL0_MDEC(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL0_MDEC_SHIFT)) & SYSCON_SYSPLLSSCTRL0_MDEC_MASK)
#define SYSCON_SYSPLLSSCTRL0_MREQ_MASK           (0x20000U)
#define SYSCON_SYSPLLSSCTRL0_MREQ_SHIFT          (17U)
/*! MREQ - MDEC reload request. When a 1 is written to this bit, the MDEC value is loaded into the
 *    PLL. Must be cleared by software for any subsequent load, or the PLL can be powered down and
 *    back up via the PDEN_SYS_PLL bit in the PDRUNCFG register if the MDEC value is changed.
 */
#define SYSCON_SYSPLLSSCTRL0_MREQ(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL0_MREQ_SHIFT)) & SYSCON_SYSPLLSSCTRL0_MREQ_MASK)
#define SYSCON_SYSPLLSSCTRL0_SEL_EXT_MASK        (0x40000U)
#define SYSCON_SYSPLLSSCTRL0_SEL_EXT_SHIFT       (18U)
/*! SEL_EXT - Select spread spectrum mode. Selects the source of the feedback divider value. For
 *    normal mode, this must be the value from the MDEC field in this register. For spread spectrum
 *    mode: SEL_EXT = 0, BANDSEL = 0, and UPLIMOFF = 1.
 */
#define SYSCON_SYSPLLSSCTRL0_SEL_EXT(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL0_SEL_EXT_SHIFT)) & SYSCON_SYSPLLSSCTRL0_SEL_EXT_MASK)
/*! @} */

/*! @name SYSPLLSSCTRL1 - PLL spread spectrum control 1 */
/*! @{ */
#define SYSCON_SYSPLLSSCTRL1_MD_MASK             (0x7FFFFU)
#define SYSCON_SYSPLLSSCTRL1_MD_SHIFT            (0U)
/*! MD - M- divider value with fraction. MD[18:11]: integer portion of the feedback divider value.
 *    MD[10:0]: fractional portion of the feedback divider value. In fractional mode, fcco = (2 -
 *    BYPASSCCODIV2) x (MD x 2^-11) x Fref
 */
#define SYSCON_SYSPLLSSCTRL1_MD(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_MD_SHIFT)) & SYSCON_SYSPLLSSCTRL1_MD_MASK)
#define SYSCON_SYSPLLSSCTRL1_MDREQ_MASK          (0x80000U)
#define SYSCON_SYSPLLSSCTRL1_MDREQ_SHIFT         (19U)
/*! MDREQ - MD reload request. When a 1 is written to this bit, the MD value is loaded into the PLL.
 *    This bit is cleared when the load is complete
 */
#define SYSCON_SYSPLLSSCTRL1_MDREQ(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_MDREQ_SHIFT)) & SYSCON_SYSPLLSSCTRL1_MDREQ_MASK)
#define SYSCON_SYSPLLSSCTRL1_MF_MASK             (0x700000U)
#define SYSCON_SYSPLLSSCTRL1_MF_SHIFT            (20U)
/*! MF - Programmable modulation frequency fm = Fref/Nss with Fref = Fin/N 0b000 => Nss = 512 (fm _
 *    3.9 - 7.8 kHz) 0b001 => Nss _ 384 (fm _ 5.2 - 10.4 kHz) 0b010 => Nss = 256 (fm _ 7.8 - 15.6
 *    kHz) 0b011 => Nss = 128 (fm _ 15.6 - 31.3 kHz) 0b100 => Nss = 64 (fm _ 32.3 - 64.5 kHz) 0b101 =>
 *    Nss = 32 (fm _ 62.5- 125 kHz) 0b110 => Nss _ 24 (fm _ 83.3- 166.6 kHz) 0b111 => Nss = 16 (fm
 *    _ 125- 250 kHz)
 */
#define SYSCON_SYSPLLSSCTRL1_MF(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_MF_SHIFT)) & SYSCON_SYSPLLSSCTRL1_MF_MASK)
#define SYSCON_SYSPLLSSCTRL1_MR_MASK             (0x3800000U)
#define SYSCON_SYSPLLSSCTRL1_MR_SHIFT            (23U)
/*! MR - Programmable frequency modulation depth. 0 = no spread. _fmodpk-pk = Fref x k/Fcco =
 *    k/MDdec 0b000 -> k = 0 (no spread spectrum) 0b001 => k _ 1 0b010 => k _ 1.5 0b011 => k _ 2 0b100 =>
 *    k _ 3 0b101 => k _ 4 0b110 => k _ 6 0b111 => k _ 8
 */
#define SYSCON_SYSPLLSSCTRL1_MR(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_MR_SHIFT)) & SYSCON_SYSPLLSSCTRL1_MR_MASK)
#define SYSCON_SYSPLLSSCTRL1_MC_MASK             (0xC000000U)
#define SYSCON_SYSPLLSSCTRL1_MC_SHIFT            (26U)
/*! MC - Modulation waveform control. 0 = no compensation. Compensation for low pass filtering of
 *    the PLL to get a triangular modulation at the output of the PLL, giving a flat frequency
 *    spectrum. 0b00 => no compensation 0b10 => recommended setting 0b11 => max. compensation
 */
#define SYSCON_SYSPLLSSCTRL1_MC(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_MC_SHIFT)) & SYSCON_SYSPLLSSCTRL1_MC_MASK)
#define SYSCON_SYSPLLSSCTRL1_PD_MASK             (0x10000000U)
#define SYSCON_SYSPLLSSCTRL1_PD_SHIFT            (28U)
/*! PD - Spread spectrum power-down.
 *  0b0..Enabled. Spread spectrum controller is enabled
 *  0b1..Disabled. Spread spectrum controller is disabled.
 */
#define SYSCON_SYSPLLSSCTRL1_PD(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_PD_SHIFT)) & SYSCON_SYSPLLSSCTRL1_PD_MASK)
#define SYSCON_SYSPLLSSCTRL1_DITHER_MASK         (0x20000000U)
#define SYSCON_SYSPLLSSCTRL1_DITHER_SHIFT        (29U)
/*! DITHER - Select modulation frequency.
 *  0b0..Fixed. Fixed modulation frequency.
 *  0b1..Dither. Randomly dither between two modulation frequencies.
 */
#define SYSCON_SYSPLLSSCTRL1_DITHER(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSSCTRL1_DITHER_SHIFT)) & SYSCON_SYSPLLSSCTRL1_DITHER_MASK)
/*! @} */

/*! @name PDSLEEPCFG - Sleep configuration register n */
/*! @{ */
#define SYSCON_PDSLEEPCFG_PD_SLEEP_MASK          (0xFFFFFFFFU)
#define SYSCON_PDSLEEPCFG_PD_SLEEP_SHIFT         (0U)
/*! PD_SLEEP - See bit descriptions in the PDRUNCFGn register.
 */
#define SYSCON_PDSLEEPCFG_PD_SLEEP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_PD_SLEEP_SHIFT)) & SYSCON_PDSLEEPCFG_PD_SLEEP_MASK)
/*! @} */

/* The count of SYSCON_PDSLEEPCFG */
#define SYSCON_PDSLEEPCFG_COUNT                  (2U)

/*! @name PDRUNCFG - Power configuration register 0 */
/*! @{ */
#define SYSCON_PDRUNCFG_PDEN_FRO_MASK            (0x10U)
#define SYSCON_PDRUNCFG_PDEN_FRO_SHIFT           (4U)
/*! PDEN_FRO - FRO oscillator. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_FRO(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_FRO_SHIFT)) & SYSCON_PDRUNCFG_PDEN_FRO_MASK)
#define SYSCON_PDRUNCFG_PDEN_TS_MASK             (0x40U)
#define SYSCON_PDRUNCFG_PDEN_TS_SHIFT            (6U)
/*! PDEN_TS - Temp sensor. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_TS(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_TS_SHIFT)) & SYSCON_PDRUNCFG_PDEN_TS_MASK)
#define SYSCON_PDRUNCFG_PDEN_BOD_RST_MASK        (0x80U)
#define SYSCON_PDRUNCFG_PDEN_BOD_RST_SHIFT       (7U)
/*! PDEN_BOD_RST - Brown-out Detect reset. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_BOD_RST(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_BOD_RST_SHIFT)) & SYSCON_PDRUNCFG_PDEN_BOD_RST_MASK)
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR_MASK       (0x100U)
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR_SHIFT      (8U)
/*! PDEN_BOD_INTR - Brown-out Detect interrupt. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_BOD_INTR(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_BOD_INTR_SHIFT)) & SYSCON_PDRUNCFG_PDEN_BOD_INTR_MASK)
#define SYSCON_PDRUNCFG_PDEN_ADC0_MASK           (0x400U)
#define SYSCON_PDRUNCFG_PDEN_ADC0_SHIFT          (10U)
/*! PDEN_ADC0 - ADC0. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_ADC0(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_ADC0_SHIFT)) & SYSCON_PDRUNCFG_PDEN_ADC0_MASK)
#define SYSCON_PDRUNCFG_PDEN_SRAM0_MASK          (0x2000U)
#define SYSCON_PDRUNCFG_PDEN_SRAM0_SHIFT         (13U)
/*! PDEN_SRAM0 - SRAM0. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_SRAM0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SRAM0_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SRAM0_MASK)
#define SYSCON_PDRUNCFG_PDEN_SRAMX_MASK          (0x10000U)
#define SYSCON_PDRUNCFG_PDEN_SRAMX_SHIFT         (16U)
/*! PDEN_SRAMX - SRAMX. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_SRAMX(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SRAMX_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SRAMX_MASK)
#define SYSCON_PDRUNCFG_PDEN_ROM_MASK            (0x20000U)
#define SYSCON_PDRUNCFG_PDEN_ROM_SHIFT           (17U)
/*! PDEN_ROM - ROM. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_ROM(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_ROM_SHIFT)) & SYSCON_PDRUNCFG_PDEN_ROM_MASK)
#define SYSCON_PDRUNCFG_PDEN_VDDA_MASK           (0x80000U)
#define SYSCON_PDRUNCFG_PDEN_VDDA_SHIFT          (19U)
/*! PDEN_VDDA - Vdda to the ADC, must be enabled for the ADC to work. Also see bit 23. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_VDDA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VDDA_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VDDA_MASK)
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC_MASK        (0x100000U)
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC_SHIFT       (20U)
/*! PDEN_WDT_OSC - Watchdog oscillator. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_WDT_OSC(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_WDT_OSC_SHIFT)) & SYSCON_PDRUNCFG_PDEN_WDT_OSC_MASK)
#define SYSCON_PDRUNCFG_PDEN_USB_PHY_MASK        (0x200000U)
#define SYSCON_PDRUNCFG_PDEN_USB_PHY_SHIFT       (21U)
/*! PDEN_USB_PHY - USB pin interface. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_USB_PHY(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_USB_PHY_SHIFT)) & SYSCON_PDRUNCFG_PDEN_USB_PHY_MASK)
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL_MASK        (0x400000U)
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL_SHIFT       (22U)
/*! PDEN_SYS_PLL - PLL0. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_SYS_PLL(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_SYS_PLL_SHIFT)) & SYSCON_PDRUNCFG_PDEN_SYS_PLL_MASK)
#define SYSCON_PDRUNCFG_PDEN_VREFP_MASK          (0x800000U)
#define SYSCON_PDRUNCFG_PDEN_VREFP_SHIFT         (23U)
/*! PDEN_VREFP - Vrefp to the ADC, must be enabled for the ADC to work. Also see bit 19. 0 = Powered; 1 = Powered down.
 */
#define SYSCON_PDRUNCFG_PDEN_VREFP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_PDEN_VREFP_SHIFT)) & SYSCON_PDRUNCFG_PDEN_VREFP_MASK)
/*! @} */

/* The count of SYSCON_PDRUNCFG */
#define SYSCON_PDRUNCFG_COUNT                    (1U)

/*! @name PDRUNCFGSET - Set bits in PDRUNCFGn */
/*! @{ */
#define SYSCON_PDRUNCFGSET_PD_SET_MASK           (0xFFFFFFFFU)
#define SYSCON_PDRUNCFGSET_PD_SET_SHIFT          (0U)
/*! PD_SET - Writing ones to this register sets the corresponding bit or bits in the PDRUNCFG
 *    register, if they are implemented. Bits that do not correspond to defined bits in PDRUNCFG are
 *    reserved and only zeroes should be written to them.
 */
#define SYSCON_PDRUNCFGSET_PD_SET(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGSET_PD_SET_SHIFT)) & SYSCON_PDRUNCFGSET_PD_SET_MASK)
/*! @} */

/* The count of SYSCON_PDRUNCFGSET */
#define SYSCON_PDRUNCFGSET_COUNT                 (1U)

/*! @name PDRUNCFGCLR - Clear bits in PDRUNCFGn */
/*! @{ */
#define SYSCON_PDRUNCFGCLR_PD_CLR_MASK           (0xFFFFFFFFU)
#define SYSCON_PDRUNCFGCLR_PD_CLR_SHIFT          (0U)
/*! PD_CLR - Writing ones to this register clears the corresponding bit or bits in the PDRUNCFG
 *    register, if they are implemented. Bits that do not correspond to defined bits in PDRUNCFG are
 *    reserved and only zeroes should be written to them.
 */
#define SYSCON_PDRUNCFGCLR_PD_CLR(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFGCLR_PD_CLR_SHIFT)) & SYSCON_PDRUNCFGCLR_PD_CLR_MASK)
/*! @} */

/* The count of SYSCON_PDRUNCFGCLR */
#define SYSCON_PDRUNCFGCLR_COUNT                 (1U)

/*! @name STARTER - Start logic n wake-up enable register */
/*! @{ */
#define SYSCON_STARTER_WDT_BOD_MASK              (0x1U)
#define SYSCON_STARTER_WDT_BOD_SHIFT             (0U)
/*! WDT_BOD - WWDT and BOD interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_WDT_BOD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_WDT_BOD_SHIFT)) & SYSCON_STARTER_WDT_BOD_MASK)
#define SYSCON_STARTER_DMA0_MASK                 (0x2U)
#define SYSCON_STARTER_DMA0_SHIFT                (1U)
/*! DMA0 - DMA0 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Typically used in sleep mode
 *    only since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_DMA0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_DMA0_SHIFT)) & SYSCON_STARTER_DMA0_MASK)
#define SYSCON_STARTER_GINT0_MASK                (0x4U)
#define SYSCON_STARTER_GINT0_SHIFT               (2U)
/*! GINT0 - Group interrupt 0 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_GINT0(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_GINT0_SHIFT)) & SYSCON_STARTER_GINT0_MASK)
#define SYSCON_STARTER_GINT1_MASK                (0x8U)
#define SYSCON_STARTER_GINT1_SHIFT               (3U)
/*! GINT1 - Group interrupt 1 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_GINT1(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_GINT1_SHIFT)) & SYSCON_STARTER_GINT1_MASK)
#define SYSCON_STARTER_PIN_INT0_MASK             (0x10U)
#define SYSCON_STARTER_PIN_INT0_SHIFT            (4U)
/*! PIN_INT0 - GPIO pin interrupt 0 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Not for pattern match.
 */
#define SYSCON_STARTER_PIN_INT0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT0_SHIFT)) & SYSCON_STARTER_PIN_INT0_MASK)
#define SYSCON_STARTER_PIN_INT1_MASK             (0x20U)
#define SYSCON_STARTER_PIN_INT1_SHIFT            (5U)
/*! PIN_INT1 - GPIO pin interrupt 1 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Not for pattern match.
 */
#define SYSCON_STARTER_PIN_INT1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT1_SHIFT)) & SYSCON_STARTER_PIN_INT1_MASK)
#define SYSCON_STARTER_PIN_INT2_MASK             (0x40U)
#define SYSCON_STARTER_PIN_INT2_SHIFT            (6U)
/*! PIN_INT2 - GPIO pin interrupt 2 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Not for pattern match.
 */
#define SYSCON_STARTER_PIN_INT2(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT2_SHIFT)) & SYSCON_STARTER_PIN_INT2_MASK)
#define SYSCON_STARTER_PIN_INT3_MASK             (0x80U)
#define SYSCON_STARTER_PIN_INT3_SHIFT            (7U)
/*! PIN_INT3 - GPIO pin interrupt 3 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Not for pattern match.
 */
#define SYSCON_STARTER_PIN_INT3(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_PIN_INT3_SHIFT)) & SYSCON_STARTER_PIN_INT3_MASK)
#define SYSCON_STARTER_UTICK0_MASK               (0x100U)
#define SYSCON_STARTER_UTICK0_SHIFT              (8U)
/*! UTICK0 - Micro-tick Timer wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_UTICK0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_UTICK0_SHIFT)) & SYSCON_STARTER_UTICK0_MASK)
#define SYSCON_STARTER_MRT0_MASK                 (0x200U)
#define SYSCON_STARTER_MRT0_SHIFT                (9U)
/*! MRT0 - Multi-Rate Timer wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled. Typically used in
 *    sleep mode only since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_MRT0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_MRT0_SHIFT)) & SYSCON_STARTER_MRT0_MASK)
#define SYSCON_STARTER_CTIMER0_MASK              (0x400U)
#define SYSCON_STARTER_CTIMER0_SHIFT             (10U)
/*! CTIMER0 - Standard counter/timer CTIMER0 wake-up. 0 = Wake-up disabled. 1 = Wake-up
 *    enabled.Typically used in sleep mode only since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_CTIMER0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER0_SHIFT)) & SYSCON_STARTER_CTIMER0_MASK)
#define SYSCON_STARTER_CTIMER1_MASK              (0x800U)
#define SYSCON_STARTER_CTIMER1_SHIFT             (11U)
/*! CTIMER1 - Standard counter/timer CTIMER1 wake-up. 0 = Wake-up disabled. 1 = Wake-up
 *    enabled.Typically used in sleep mode only since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_CTIMER1(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER1_SHIFT)) & SYSCON_STARTER_CTIMER1_MASK)
#define SYSCON_STARTER_SCT0_MASK                 (0x1000U)
#define SYSCON_STARTER_SCT0_SHIFT                (12U)
/*! SCT0 - SCT0 wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.Typically used in sleep mode only
 *    since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_SCT0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_SCT0_SHIFT)) & SYSCON_STARTER_SCT0_MASK)
#define SYSCON_STARTER_CTIMER3_MASK              (0x2000U)
#define SYSCON_STARTER_CTIMER3_SHIFT             (13U)
/*! CTIMER3 - Standard counter/timer CTIMER3 wake-up. 0 = Wake-up disabled. 1 = Wake-up
 *    enabled.Typically used in sleep mode only since the peripheral clock must be running for it to function.
 */
#define SYSCON_STARTER_CTIMER3(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_CTIMER3_SHIFT)) & SYSCON_STARTER_CTIMER3_MASK)
#define SYSCON_STARTER_FLEXCOMM0_MASK            (0x4000U)
#define SYSCON_STARTER_FLEXCOMM0_SHIFT           (14U)
/*! FLEXCOMM0 - Flexcomm0 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM0(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM0_SHIFT)) & SYSCON_STARTER_FLEXCOMM0_MASK)
#define SYSCON_STARTER_FLEXCOMM1_MASK            (0x8000U)
#define SYSCON_STARTER_FLEXCOMM1_SHIFT           (15U)
/*! FLEXCOMM1 - Flexcomm1 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM1(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM1_SHIFT)) & SYSCON_STARTER_FLEXCOMM1_MASK)
#define SYSCON_STARTER_FLEXCOMM2_MASK            (0x10000U)
#define SYSCON_STARTER_FLEXCOMM2_SHIFT           (16U)
/*! FLEXCOMM2 - Flexcomm2 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM2(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM2_SHIFT)) & SYSCON_STARTER_FLEXCOMM2_MASK)
#define SYSCON_STARTER_FLEXCOMM3_MASK            (0x20000U)
#define SYSCON_STARTER_FLEXCOMM3_SHIFT           (17U)
/*! FLEXCOMM3 - Flexcomm3 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM3(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM3_SHIFT)) & SYSCON_STARTER_FLEXCOMM3_MASK)
#define SYSCON_STARTER_FLEXCOMM4_MASK            (0x40000U)
#define SYSCON_STARTER_FLEXCOMM4_SHIFT           (18U)
/*! FLEXCOMM4 - Flexcomm4 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM4(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM4_SHIFT)) & SYSCON_STARTER_FLEXCOMM4_MASK)
#define SYSCON_STARTER_FLEXCOMM5_MASK            (0x80000U)
#define SYSCON_STARTER_FLEXCOMM5_SHIFT           (19U)
/*! FLEXCOMM5 - Flexcomm5 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM5(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM5_SHIFT)) & SYSCON_STARTER_FLEXCOMM5_MASK)
#define SYSCON_STARTER_FLEXCOMM6_MASK            (0x100000U)
#define SYSCON_STARTER_FLEXCOMM6_SHIFT           (20U)
/*! FLEXCOMM6 - Flexcomm6 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM6(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM6_SHIFT)) & SYSCON_STARTER_FLEXCOMM6_MASK)
#define SYSCON_STARTER_FLEXCOMM7_MASK            (0x200000U)
#define SYSCON_STARTER_FLEXCOMM7_SHIFT           (21U)
/*! FLEXCOMM7 - Flexcomm7 peripheral interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_FLEXCOMM7(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_FLEXCOMM7_SHIFT)) & SYSCON_STARTER_FLEXCOMM7_MASK)
#define SYSCON_STARTER_USB0_NEEDCLK_MASK         (0x8000000U)
#define SYSCON_STARTER_USB0_NEEDCLK_SHIFT        (27U)
/*! USB0_NEEDCLK - USB0 activity interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_USB0_NEEDCLK(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB0_NEEDCLK_SHIFT)) & SYSCON_STARTER_USB0_NEEDCLK_MASK)
#define SYSCON_STARTER_USB0_MASK                 (0x10000000U)
#define SYSCON_STARTER_USB0_SHIFT                (28U)
/*! USB0 - USB0 function interrupt wake-up. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_USB0(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_USB0_SHIFT)) & SYSCON_STARTER_USB0_MASK)
#define SYSCON_STARTER_RTC_MASK                  (0x20000000U)
#define SYSCON_STARTER_RTC_SHIFT                 (29U)
/*! RTC - RTC interrupt alarm and wake-up timer. 0 = Wake-up disabled. 1 = Wake-up enabled.
 */
#define SYSCON_STARTER_RTC(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTER_RTC_SHIFT)) & SYSCON_STARTER_RTC_MASK)
/*! @} */

/* The count of SYSCON_STARTER */
#define SYSCON_STARTER_COUNT                     (1U)

/*! @name STARTERSET - Set bits in STARTERn */
/*! @{ */
#define SYSCON_STARTERSET_START_SET_MASK         (0xFFFFFFFFU)
#define SYSCON_STARTERSET_START_SET_SHIFT        (0U)
/*! START_SET - Writing ones to this register sets the corresponding bit or bits in the STARTERn
 *    register, if they are implemented. Bits that do not correspond to defined bits in STARTERn are
 *    reserved and only zeroes should be written to them.
 */
#define SYSCON_STARTERSET_START_SET(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERSET_START_SET_SHIFT)) & SYSCON_STARTERSET_START_SET_MASK)
/*! @} */

/* The count of SYSCON_STARTERSET */
#define SYSCON_STARTERSET_COUNT                  (1U)

/*! @name STARTERCLR - Clear bits in STARTERn */
/*! @{ */
#define SYSCON_STARTERCLR_START_CLR_MASK         (0xFFFFFFFFU)
#define SYSCON_STARTERCLR_START_CLR_SHIFT        (0U)
/*! START_CLR - Writing ones to this register clears the corresponding bit or bits in the STARTERn
 *    register, if they are implemented. Bits that do not correspond to defined bits in STARTERn are
 *    reserved and only zeroes should be written to them.
 */
#define SYSCON_STARTERCLR_START_CLR(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERCLR_START_CLR_SHIFT)) & SYSCON_STARTERCLR_START_CLR_MASK)
/*! @} */

/* The count of SYSCON_STARTERCLR */
#define SYSCON_STARTERCLR_COUNT                  (1U)

/*! @name HWWAKE - Configures special cases of hardware wake-up */
/*! @{ */
#define SYSCON_HWWAKE_FORCEWAKE_MASK             (0x1U)
#define SYSCON_HWWAKE_FORCEWAKE_SHIFT            (0U)
/*! FORCEWAKE - Force peripheral clocking to stay on during Deep Sleep and Power-down modes. When 1,
 *    clocking to peripherals is prevented from being shut down when the CPU enters Deep Sleep and
 *    Power-down modes. This is intended to allow a coprocessor to continue operating while the main
 *    CPU(s) are shut down.
 */
#define SYSCON_HWWAKE_FORCEWAKE(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_FORCEWAKE_SHIFT)) & SYSCON_HWWAKE_FORCEWAKE_MASK)
#define SYSCON_HWWAKE_FCWAKE_MASK                (0x2U)
#define SYSCON_HWWAKE_FCWAKE_SHIFT               (1U)
/*! FCWAKE - Wake for Flexcomms. When 1, any Flexcomm FIFO reaching the level specified by its own
 *    TXLVL will cause peripheral clocking to wake up temporarily while the related status is
 *    asserted.
 */
#define SYSCON_HWWAKE_FCWAKE(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_FCWAKE_SHIFT)) & SYSCON_HWWAKE_FCWAKE_MASK)
#define SYSCON_HWWAKE_WAKEDMA_MASK               (0x8U)
#define SYSCON_HWWAKE_WAKEDMA_SHIFT              (3U)
/*! WAKEDMA - Wake for DMA. When 1, DMA being busy will cause peripheral clocking to remain running
 *    until DMA completes. This is generally used in conjunction with bit 1 and/or 2 in order to
 *    prevent peripheral clocking from being shut down as soon as the cause of wake-up is cleared, but
 *    before DMA has completed its related activity.
 */
#define SYSCON_HWWAKE_WAKEDMA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_HWWAKE_WAKEDMA_SHIFT)) & SYSCON_HWWAKE_WAKEDMA_MASK)
/*! @} */

/*! @name JTAGIDCODE - JTAG ID code register */
/*! @{ */
#define SYSCON_JTAGIDCODE_JTAGID_MASK            (0xFFFFFFFFU)
#define SYSCON_JTAGIDCODE_JTAGID_SHIFT           (0U)
/*! JTAGID - JTAG ID code.
 */
#define SYSCON_JTAGIDCODE_JTAGID(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_JTAGIDCODE_JTAGID_SHIFT)) & SYSCON_JTAGIDCODE_JTAGID_MASK)
/*! @} */

/*! @name DEVICE_ID0 - Part ID register */
/*! @{ */
#define SYSCON_DEVICE_ID0_PARTID_MASK            (0xFFFFFFFFU)
#define SYSCON_DEVICE_ID0_PARTID_SHIFT           (0U)
/*! PARTID - Part ID
 */
#define SYSCON_DEVICE_ID0_PARTID(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID0_PARTID_SHIFT)) & SYSCON_DEVICE_ID0_PARTID_MASK)
/*! @} */

/*! @name DEVICE_ID1 - Boot ROM and die revision register */
/*! @{ */
#define SYSCON_DEVICE_ID1_REVID_MASK             (0xFFFFFFFFU)
#define SYSCON_DEVICE_ID1_REVID_SHIFT            (0U)
/*! REVID - Revision.
 */
#define SYSCON_DEVICE_ID1_REVID(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID1_REVID_SHIFT)) & SYSCON_DEVICE_ID1_REVID_MASK)
/*! @} */

/*! @name BODCTRL - Brown-Out Detect control */
/*! @{ */
#define SYSCON_BODCTRL_BODRSTLEV_MASK            (0x3U)
#define SYSCON_BODCTRL_BODRSTLEV_SHIFT           (0U)
/*! BODRSTLEV - BOD reset level
 *  0b00..Level 0: 1.5 V
 *  0b01..Level 1: 1.85 V
 *  0b10..Level 2: 2.0 V
 *  0b11..Level 3: 2.3 V
 */
#define SYSCON_BODCTRL_BODRSTLEV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTLEV_SHIFT)) & SYSCON_BODCTRL_BODRSTLEV_MASK)
#define SYSCON_BODCTRL_BODRSTENA_MASK            (0x4U)
#define SYSCON_BODCTRL_BODRSTENA_SHIFT           (2U)
/*! BODRSTENA - BOD reset enable
 *  0b0..Disable reset function.
 *  0b1..Enable reset function.
 */
#define SYSCON_BODCTRL_BODRSTENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTENA_SHIFT)) & SYSCON_BODCTRL_BODRSTENA_MASK)
#define SYSCON_BODCTRL_BODINTLEV_MASK            (0x18U)
#define SYSCON_BODCTRL_BODINTLEV_SHIFT           (3U)
/*! BODINTLEV - BOD interrupt level
 *  0b00..Level 0: 2.05 V
 *  0b01..Level 1: 2.45 V
 *  0b10..Level 2: 2.75 V
 *  0b11..Level 3: 3.05 V
 */
#define SYSCON_BODCTRL_BODINTLEV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTLEV_SHIFT)) & SYSCON_BODCTRL_BODINTLEV_MASK)
#define SYSCON_BODCTRL_BODINTENA_MASK            (0x20U)
#define SYSCON_BODCTRL_BODINTENA_SHIFT           (5U)
/*! BODINTENA - BOD interrupt enable
 *  0b0..Disable interrupt function.
 *  0b1..Enable interrupt function.
 */
#define SYSCON_BODCTRL_BODINTENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTENA_SHIFT)) & SYSCON_BODCTRL_BODINTENA_MASK)
#define SYSCON_BODCTRL_BODRSTSTAT_MASK           (0x40U)
#define SYSCON_BODCTRL_BODRSTSTAT_SHIFT          (6U)
/*! BODRSTSTAT - BOD reset status. When 1, a BOD reset has occurred. Cleared by writing 1 to this bit.
 */
#define SYSCON_BODCTRL_BODRSTSTAT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTSTAT_SHIFT)) & SYSCON_BODCTRL_BODRSTSTAT_MASK)
#define SYSCON_BODCTRL_BODINTSTAT_MASK           (0x80U)
#define SYSCON_BODCTRL_BODINTSTAT_SHIFT          (7U)
/*! BODINTSTAT - BOD interrupt status. When 1, a BOD interrupt has occurred. Cleared by writing 1 to this bit.
 */
#define SYSCON_BODCTRL_BODINTSTAT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTSTAT_SHIFT)) & SYSCON_BODCTRL_BODINTSTAT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYSCON_Register_Masks */


/* SYSCON - Peripheral instance base addresses */
/** Peripheral SYSCON base address */
#define SYSCON_BASE                              (0x40000000u)
/** Peripheral SYSCON base pointer */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array initializer of SYSCON peripheral base addresses */
#define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
/** Array initializer of SYSCON peripheral base pointers */
#define SYSCON_BASE_PTRS                         { SYSCON }

/*!
 * @}
 */ /* end of group SYSCON_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Peripheral_Access_Layer USART Peripheral Access Layer
 * @{
 */

/** USART - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG;                               /**< USART Configuration register. Basic USART configuration settings that typically are not changed during operation., offset: 0x0 */
  __IO uint32_t CTL;                               /**< USART Control register. USART control settings that are more likely to change during operation., offset: 0x4 */
  __IO uint32_t STAT;                              /**< USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them., offset: 0x8 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared., offset: 0x10 */
       uint8_t RESERVED_0[12];
  __IO uint32_t BRG;                               /**< Baud Rate Generator register. 16-bit integer baud rate divisor value., offset: 0x20 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status register. Reflects interrupts that are currently enabled., offset: 0x24 */
  __IO uint32_t OSR;                               /**< Oversample selection register for asynchronous communication., offset: 0x28 */
  __IO uint32_t ADDR;                              /**< Address register for automatic address matching., offset: 0x2C */
       uint8_t RESERVED_1[3536];
  __IO uint32_t FIFOCFG;                           /**< FIFO configuration and enable register., offset: 0xE00 */
  __IO uint32_t FIFOSTAT;                          /**< FIFO status register., offset: 0xE04 */
  __IO uint32_t FIFOTRIG;                          /**< FIFO trigger settings for interrupt and DMA request., offset: 0xE08 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FIFOINTENSET;                      /**< FIFO interrupt enable set (enable) and read register., offset: 0xE10 */
  __IO uint32_t FIFOINTENCLR;                      /**< FIFO interrupt enable clear (disable) and read register., offset: 0xE14 */
  __I  uint32_t FIFOINTSTAT;                       /**< FIFO interrupt status register., offset: 0xE18 */
       uint8_t RESERVED_3[4];
  __O  uint32_t FIFOWR;                            /**< FIFO write data., offset: 0xE20 */
       uint8_t RESERVED_4[12];
  __I  uint32_t FIFORD;                            /**< FIFO read data., offset: 0xE30 */
       uint8_t RESERVED_5[12];
  __I  uint32_t FIFORDNOPOP;                       /**< FIFO data read with no FIFO pop., offset: 0xE40 */
       uint8_t RESERVED_6[440];
  __I  uint32_t ID;                                /**< Peripheral identification register., offset: 0xFFC */
} USART_Type;

/* ----------------------------------------------------------------------------
   -- USART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USART_Register_Masks USART Register Masks
 * @{
 */

/*! @name CFG - USART Configuration register. Basic USART configuration settings that typically are not changed during operation. */
/*! @{ */
#define USART_CFG_ENABLE_MASK                    (0x1U)
#define USART_CFG_ENABLE_SHIFT                   (0U)
/*! ENABLE - USART Enable.
 *  0b0..Disabled. The USART is disabled and the internal state machine and counters are reset. While Enable = 0,
 *       all USART interrupts and DMA transfers are disabled. When Enable is set again, CFG and most other control
 *       bits remain unchanged. When re-enabled, the USART will immediately be ready to transmit because the
 *       transmitter has been reset and is therefore available.
 *  0b1..Enabled. The USART is enabled for operation.
 */
#define USART_CFG_ENABLE(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_ENABLE_SHIFT)) & USART_CFG_ENABLE_MASK)
#define USART_CFG_DATALEN_MASK                   (0xCU)
#define USART_CFG_DATALEN_SHIFT                  (2U)
/*! DATALEN - Selects the data size for the USART.
 *  0b00..7 bit Data length.
 *  0b01..8 bit Data length.
 *  0b10..9 bit data length. The 9th bit is commonly used for addressing in multidrop mode. See the ADDRDET bit in the CTL register.
 *  0b11..Reserved.
 */
#define USART_CFG_DATALEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_DATALEN_SHIFT)) & USART_CFG_DATALEN_MASK)
#define USART_CFG_PARITYSEL_MASK                 (0x30U)
#define USART_CFG_PARITYSEL_SHIFT                (4U)
/*! PARITYSEL - Selects what type of parity is used by the USART.
 *  0b00..No parity.
 *  0b01..Reserved.
 *  0b10..Even parity. Adds a bit to each character such that the number of 1s in a transmitted character is even,
 *        and the number of 1s in a received character is expected to be even.
 *  0b11..Odd parity. Adds a bit to each character such that the number of 1s in a transmitted character is odd,
 *        and the number of 1s in a received character is expected to be odd.
 */
#define USART_CFG_PARITYSEL(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CFG_PARITYSEL_SHIFT)) & USART_CFG_PARITYSEL_MASK)
#define USART_CFG_STOPLEN_MASK                   (0x40U)
#define USART_CFG_STOPLEN_SHIFT                  (6U)
/*! STOPLEN - Number of stop bits appended to transmitted data. Only a single stop bit is required for received data.
 *  0b0..1 stop bit.
 *  0b1..2 stop bits. This setting should only be used for asynchronous communication.
 */
#define USART_CFG_STOPLEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_STOPLEN_SHIFT)) & USART_CFG_STOPLEN_MASK)
#define USART_CFG_MODE32K_MASK                   (0x80U)
#define USART_CFG_MODE32K_SHIFT                  (7U)
/*! MODE32K - Selects standard or 32 kHz clocking mode.
 *  0b0..Disabled. USART uses standard clocking.
 *  0b1..Enabled. USART uses the 32 kHz clock from the RTC oscillator as the clock source to the BRG, and uses a special bit clocking scheme.
 */
#define USART_CFG_MODE32K(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_MODE32K_SHIFT)) & USART_CFG_MODE32K_MASK)
#define USART_CFG_LINMODE_MASK                   (0x100U)
#define USART_CFG_LINMODE_SHIFT                  (8U)
/*! LINMODE - LIN break mode enable.
 *  0b0..Disabled. Break detect and generate is configured for normal operation.
 *  0b1..Enabled. Break detect and generate is configured for LIN bus operation.
 */
#define USART_CFG_LINMODE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_LINMODE_SHIFT)) & USART_CFG_LINMODE_MASK)
#define USART_CFG_CTSEN_MASK                     (0x200U)
#define USART_CFG_CTSEN_SHIFT                    (9U)
/*! CTSEN - CTS Enable. Determines whether CTS is used for flow control. CTS can be from the input
 *    pin, or from the USART's own RTS if loopback mode is enabled.
 *  0b0..No flow control. The transmitter does not receive any automatic flow control signal.
 *  0b1..Flow control enabled. The transmitter uses the CTS input (or RTS output in loopback mode) for flow control purposes.
 */
#define USART_CFG_CTSEN(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_CTSEN_SHIFT)) & USART_CFG_CTSEN_MASK)
#define USART_CFG_SYNCEN_MASK                    (0x800U)
#define USART_CFG_SYNCEN_SHIFT                   (11U)
/*! SYNCEN - Selects synchronous or asynchronous operation.
 *  0b0..Asynchronous mode.
 *  0b1..Synchronous mode.
 */
#define USART_CFG_SYNCEN(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCEN_SHIFT)) & USART_CFG_SYNCEN_MASK)
#define USART_CFG_CLKPOL_MASK                    (0x1000U)
#define USART_CFG_CLKPOL_SHIFT                   (12U)
/*! CLKPOL - Selects the clock polarity and sampling edge of received data in synchronous mode.
 *  0b0..Falling edge. Un_RXD is sampled on the falling edge of SCLK.
 *  0b1..Rising edge. Un_RXD is sampled on the rising edge of SCLK.
 */
#define USART_CFG_CLKPOL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_CFG_CLKPOL_SHIFT)) & USART_CFG_CLKPOL_MASK)
#define USART_CFG_SYNCMST_MASK                   (0x4000U)
#define USART_CFG_SYNCMST_SHIFT                  (14U)
/*! SYNCMST - Synchronous mode Master select.
 *  0b0..Slave. When synchronous mode is enabled, the USART is a slave.
 *  0b1..Master. When synchronous mode is enabled, the USART is a master.
 */
#define USART_CFG_SYNCMST(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CFG_SYNCMST_SHIFT)) & USART_CFG_SYNCMST_MASK)
#define USART_CFG_LOOP_MASK                      (0x8000U)
#define USART_CFG_LOOP_SHIFT                     (15U)
/*! LOOP - Selects data loopback mode.
 *  0b0..Normal operation.
 *  0b1..Loopback mode. This provides a mechanism to perform diagnostic loopback testing for USART data. Serial
 *       data from the transmitter (Un_TXD) is connected internally to serial input of the receive (Un_RXD). Un_TXD
 *       and Un_RTS activity will also appear on external pins if these functions are configured to appear on device
 *       pins. The receiver RTS signal is also looped back to CTS and performs flow control if enabled by CTSEN.
 */
#define USART_CFG_LOOP(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_LOOP_SHIFT)) & USART_CFG_LOOP_MASK)
#define USART_CFG_OETA_MASK                      (0x40000U)
#define USART_CFG_OETA_SHIFT                     (18U)
/*! OETA - Output Enable Turnaround time enable for RS-485 operation.
 *  0b0..Disabled. If selected by OESEL, the Output Enable signal deasserted at the end of the last stop bit of a transmission.
 *  0b1..Enabled. If selected by OESEL, the Output Enable signal remains asserted for one character time after the
 *       end of the last stop bit of a transmission. OE will also remain asserted if another transmit begins
 *       before it is deasserted.
 */
#define USART_CFG_OETA(x)                        (((uint32_t)(((uint32_t)(x)) << USART_CFG_OETA_SHIFT)) & USART_CFG_OETA_MASK)
#define USART_CFG_AUTOADDR_MASK                  (0x80000U)
#define USART_CFG_AUTOADDR_SHIFT                 (19U)
/*! AUTOADDR - Automatic Address matching enable.
 *  0b0..Disabled. When addressing is enabled by ADDRDET, address matching is done by software. This provides the
 *       possibility of versatile addressing (e.g. respond to more than one address).
 *  0b1..Enabled. When addressing is enabled by ADDRDET, address matching is done by hardware, using the value in
 *       the ADDR register as the address to match.
 */
#define USART_CFG_AUTOADDR(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CFG_AUTOADDR_SHIFT)) & USART_CFG_AUTOADDR_MASK)
#define USART_CFG_OESEL_MASK                     (0x100000U)
#define USART_CFG_OESEL_SHIFT                    (20U)
/*! OESEL - Output Enable Select.
 *  0b0..Standard. The RTS signal is used as the standard flow control function.
 *  0b1..RS-485. The RTS signal configured to provide an output enable signal to control an RS-485 transceiver.
 */
#define USART_CFG_OESEL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OESEL_SHIFT)) & USART_CFG_OESEL_MASK)
#define USART_CFG_OEPOL_MASK                     (0x200000U)
#define USART_CFG_OEPOL_SHIFT                    (21U)
/*! OEPOL - Output Enable Polarity.
 *  0b0..Low. If selected by OESEL, the output enable is active low.
 *  0b1..High. If selected by OESEL, the output enable is active high.
 */
#define USART_CFG_OEPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_OEPOL_SHIFT)) & USART_CFG_OEPOL_MASK)
#define USART_CFG_RXPOL_MASK                     (0x400000U)
#define USART_CFG_RXPOL_SHIFT                    (22U)
/*! RXPOL - Receive data polarity.
 *  0b0..Standard. The RX signal is used as it arrives from the pin. This means that the RX rest value is 1, start
 *       bit is 0, data is not inverted, and the stop bit is 1.
 *  0b1..Inverted. The RX signal is inverted before being used by the USART. This means that the RX rest value is
 *       0, start bit is 1, data is inverted, and the stop bit is 0.
 */
#define USART_CFG_RXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_RXPOL_SHIFT)) & USART_CFG_RXPOL_MASK)
#define USART_CFG_TXPOL_MASK                     (0x800000U)
#define USART_CFG_TXPOL_SHIFT                    (23U)
/*! TXPOL - Transmit data polarity.
 *  0b0..Standard. The TX signal is sent out without change. This means that the TX rest value is 1, start bit is
 *       0, data is not inverted, and the stop bit is 1.
 *  0b1..Inverted. The TX signal is inverted by the USART before being sent out. This means that the TX rest value
 *       is 0, start bit is 1, data is inverted, and the stop bit is 0.
 */
#define USART_CFG_TXPOL(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CFG_TXPOL_SHIFT)) & USART_CFG_TXPOL_MASK)
/*! @} */

/*! @name CTL - USART Control register. USART control settings that are more likely to change during operation. */
/*! @{ */
#define USART_CTL_TXBRKEN_MASK                   (0x2U)
#define USART_CTL_TXBRKEN_SHIFT                  (1U)
/*! TXBRKEN - Break Enable.
 *  0b0..Normal operation.
 *  0b1..Continuous break. Continuous break is sent immediately when this bit is set, and remains until this bit
 *       is cleared. A break may be sent without danger of corrupting any currently transmitting character if the
 *       transmitter is first disabled (TXDIS in CTL is set) and then waiting for the transmitter to be disabled
 *       (TXDISINT in STAT = 1) before writing 1 to TXBRKEN.
 */
#define USART_CTL_TXBRKEN(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXBRKEN_SHIFT)) & USART_CTL_TXBRKEN_MASK)
#define USART_CTL_ADDRDET_MASK                   (0x4U)
#define USART_CTL_ADDRDET_SHIFT                  (2U)
/*! ADDRDET - Enable address detect mode.
 *  0b0..Disabled. The USART presents all incoming data.
 *  0b1..Enabled. The USART receiver ignores incoming data that does not have the most significant bit of the data
 *       (typically the 9th bit) = 1. When the data MSB bit = 1, the receiver treats the incoming data normally,
 *       generating a received data interrupt. Software can then check the data to see if this is an address that
 *       should be handled. If it is, the ADDRDET bit is cleared by software and further incoming data is handled
 *       normally.
 */
#define USART_CTL_ADDRDET(x)                     (((uint32_t)(((uint32_t)(x)) << USART_CTL_ADDRDET_SHIFT)) & USART_CTL_ADDRDET_MASK)
#define USART_CTL_TXDIS_MASK                     (0x40U)
#define USART_CTL_TXDIS_SHIFT                    (6U)
/*! TXDIS - Transmit Disable.
 *  0b0..Not disabled. USART transmitter is not disabled.
 *  0b1..Disabled. USART transmitter is disabled after any character currently being transmitted is complete. This
 *       feature can be used to facilitate software flow control.
 */
#define USART_CTL_TXDIS(x)                       (((uint32_t)(((uint32_t)(x)) << USART_CTL_TXDIS_SHIFT)) & USART_CTL_TXDIS_MASK)
#define USART_CTL_CC_MASK                        (0x100U)
#define USART_CTL_CC_SHIFT                       (8U)
/*! CC - Continuous Clock generation. By default, SCLK is only output while data is being transmitted in synchronous mode.
 *  0b0..Clock on character. In synchronous mode, SCLK cycles only when characters are being sent on Un_TXD or to
 *       complete a character that is being received.
 *  0b1..Continuous clock. SCLK runs continuously in synchronous mode, allowing characters to be received on
 *       Un_RxD independently from transmission on Un_TXD).
 */
#define USART_CTL_CC(x)                          (((uint32_t)(((uint32_t)(x)) << USART_CTL_CC_SHIFT)) & USART_CTL_CC_MASK)
#define USART_CTL_CLRCCONRX_MASK                 (0x200U)
#define USART_CTL_CLRCCONRX_SHIFT                (9U)
/*! CLRCCONRX - Clear Continuous Clock.
 *  0b0..No effect. No effect on the CC bit.
 *  0b1..Auto-clear. The CC bit is automatically cleared when a complete character has been received. This bit is cleared at the same time.
 */
#define USART_CTL_CLRCCONRX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_CTL_CLRCCONRX_SHIFT)) & USART_CTL_CLRCCONRX_MASK)
#define USART_CTL_AUTOBAUD_MASK                  (0x10000U)
#define USART_CTL_AUTOBAUD_SHIFT                 (16U)
/*! AUTOBAUD - Autobaud enable.
 *  0b0..Disabled. USART is in normal operating mode.
 *  0b1..Enabled. USART is in autobaud mode. This bit should only be set when the USART receiver is idle. The
 *       first start bit of RX is measured and used the update the BRG register to match the received data rate.
 *       AUTOBAUD is cleared once this process is complete, or if there is an AERR.
 */
#define USART_CTL_AUTOBAUD(x)                    (((uint32_t)(((uint32_t)(x)) << USART_CTL_AUTOBAUD_SHIFT)) & USART_CTL_AUTOBAUD_MASK)
/*! @} */

/*! @name STAT - USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them. */
/*! @{ */
#define USART_STAT_RXIDLE_MASK                   (0x2U)
#define USART_STAT_RXIDLE_SHIFT                  (1U)
/*! RXIDLE - Receiver Idle. When 0, indicates that the receiver is currently in the process of
 *    receiving data. When 1, indicates that the receiver is not currently in the process of receiving
 *    data.
 */
#define USART_STAT_RXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXIDLE_SHIFT)) & USART_STAT_RXIDLE_MASK)
#define USART_STAT_TXIDLE_MASK                   (0x8U)
#define USART_STAT_TXIDLE_SHIFT                  (3U)
/*! TXIDLE - Transmitter Idle. When 0, indicates that the transmitter is currently in the process of
 *    sending data.When 1, indicate that the transmitter is not currently in the process of sending
 *    data.
 */
#define USART_STAT_TXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXIDLE_SHIFT)) & USART_STAT_TXIDLE_MASK)
#define USART_STAT_CTS_MASK                      (0x10U)
#define USART_STAT_CTS_SHIFT                     (4U)
/*! CTS - This bit reflects the current state of the CTS signal, regardless of the setting of the
 *    CTSEN bit in the CFG register. This will be the value of the CTS input pin unless loopback mode
 *    is enabled.
 */
#define USART_STAT_CTS(x)                        (((uint32_t)(((uint32_t)(x)) << USART_STAT_CTS_SHIFT)) & USART_STAT_CTS_MASK)
#define USART_STAT_DELTACTS_MASK                 (0x20U)
#define USART_STAT_DELTACTS_SHIFT                (5U)
/*! DELTACTS - This bit is set when a change in the state is detected for the CTS flag above. This bit is cleared by software.
 */
#define USART_STAT_DELTACTS(x)                   (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTACTS_SHIFT)) & USART_STAT_DELTACTS_MASK)
#define USART_STAT_TXDISSTAT_MASK                (0x40U)
#define USART_STAT_TXDISSTAT_SHIFT               (6U)
/*! TXDISSTAT - Transmitter Disabled Status flag. When 1, this bit indicates that the USART
 *    transmitter is fully idle after being disabled via the TXDIS bit in the CFG register (TXDIS = 1).
 */
#define USART_STAT_TXDISSTAT(x)                  (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXDISSTAT_SHIFT)) & USART_STAT_TXDISSTAT_MASK)
#define USART_STAT_RXBRK_MASK                    (0x400U)
#define USART_STAT_RXBRK_SHIFT                   (10U)
/*! RXBRK - Received Break. This bit reflects the current state of the receiver break detection
 *    logic. It is set when the Un_RXD pin remains low for 16 bit times. Note that FRAMERRINT will also
 *    be set when this condition occurs because the stop bit(s) for the character would be missing.
 *    RXBRK is cleared when the Un_RXD pin goes high.
 */
#define USART_STAT_RXBRK(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXBRK_SHIFT)) & USART_STAT_RXBRK_MASK)
#define USART_STAT_DELTARXBRK_MASK               (0x800U)
#define USART_STAT_DELTARXBRK_SHIFT              (11U)
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs. Cleared by software.
 */
#define USART_STAT_DELTARXBRK(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTARXBRK_SHIFT)) & USART_STAT_DELTARXBRK_MASK)
#define USART_STAT_START_MASK                    (0x1000U)
#define USART_STAT_START_SHIFT                   (12U)
/*! START - This bit is set when a start is detected on the receiver input. Its purpose is primarily
 *    to allow wake-up from Deep-sleep or Power-down mode immediately when a start is detected.
 *    Cleared by software.
 */
#define USART_STAT_START(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_START_SHIFT)) & USART_STAT_START_MASK)
#define USART_STAT_FRAMERRINT_MASK               (0x2000U)
#define USART_STAT_FRAMERRINT_SHIFT              (13U)
/*! FRAMERRINT - Framing Error interrupt flag. This flag is set when a character is received with a
 *    missing stop bit at the expected location. This could be an indication of a baud rate or
 *    configuration mismatch with the transmitting source.
 */
#define USART_STAT_FRAMERRINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_FRAMERRINT_SHIFT)) & USART_STAT_FRAMERRINT_MASK)
#define USART_STAT_PARITYERRINT_MASK             (0x4000U)
#define USART_STAT_PARITYERRINT_SHIFT            (14U)
/*! PARITYERRINT - Parity Error interrupt flag. This flag is set when a parity error is detected in a received character.
 */
#define USART_STAT_PARITYERRINT(x)               (((uint32_t)(((uint32_t)(x)) << USART_STAT_PARITYERRINT_SHIFT)) & USART_STAT_PARITYERRINT_MASK)
#define USART_STAT_RXNOISEINT_MASK               (0x8000U)
#define USART_STAT_RXNOISEINT_SHIFT              (15U)
/*! RXNOISEINT - Received Noise interrupt flag. Three samples of received data are taken in order to
 *    determine the value of each received data bit, except in synchronous mode. This acts as a
 *    noise filter if one sample disagrees. This flag is set when a received data bit contains one
 *    disagreeing sample. This could indicate line noise, a baud rate or character format mismatch, or
 *    loss of synchronization during data reception.
 */
#define USART_STAT_RXNOISEINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXNOISEINT_SHIFT)) & USART_STAT_RXNOISEINT_MASK)
#define USART_STAT_ABERR_MASK                    (0x10000U)
#define USART_STAT_ABERR_SHIFT                   (16U)
/*! ABERR - Auto baud Error. An auto baud error can occur if the BRG counts to its limit before the
 *    end of the start bit that is being measured, essentially an auto baud time-out.
 */
#define USART_STAT_ABERR(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_ABERR_SHIFT)) & USART_STAT_ABERR_MASK)
/*! @} */

/*! @name INTENSET - Interrupt Enable read and Set register for USART (not FIFO) status. Contains individual interrupt enable bits for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
/*! @{ */
#define USART_INTENSET_TXIDLEEN_MASK             (0x8U)
#define USART_INTENSET_TXIDLEEN_SHIFT            (3U)
/*! TXIDLEEN - When 1, enables an interrupt when the transmitter becomes idle (TXIDLE = 1).
 */
#define USART_INTENSET_TXIDLEEN(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXIDLEEN_SHIFT)) & USART_INTENSET_TXIDLEEN_MASK)
#define USART_INTENSET_DELTACTSEN_MASK           (0x20U)
#define USART_INTENSET_DELTACTSEN_SHIFT          (5U)
/*! DELTACTSEN - When 1, enables an interrupt when there is a change in the state of the CTS input.
 */
#define USART_INTENSET_DELTACTSEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTACTSEN_SHIFT)) & USART_INTENSET_DELTACTSEN_MASK)
#define USART_INTENSET_TXDISEN_MASK              (0x40U)
#define USART_INTENSET_TXDISEN_SHIFT             (6U)
/*! TXDISEN - When 1, enables an interrupt when the transmitter is fully disabled as indicated by
 *    the TXDISINT flag in STAT. See description of the TXDISINT bit for details.
 */
#define USART_INTENSET_TXDISEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXDISEN_SHIFT)) & USART_INTENSET_TXDISEN_MASK)
#define USART_INTENSET_DELTARXBRKEN_MASK         (0x800U)
#define USART_INTENSET_DELTARXBRKEN_SHIFT        (11U)
/*! DELTARXBRKEN - When 1, enables an interrupt when a change of state has occurred in the detection
 *    of a received break condition (break condition asserted or deasserted).
 */
#define USART_INTENSET_DELTARXBRKEN(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTARXBRKEN_SHIFT)) & USART_INTENSET_DELTARXBRKEN_MASK)
#define USART_INTENSET_STARTEN_MASK              (0x1000U)
#define USART_INTENSET_STARTEN_SHIFT             (12U)
/*! STARTEN - When 1, enables an interrupt when a received start bit has been detected.
 */
#define USART_INTENSET_STARTEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_STARTEN_SHIFT)) & USART_INTENSET_STARTEN_MASK)
#define USART_INTENSET_FRAMERREN_MASK            (0x2000U)
#define USART_INTENSET_FRAMERREN_SHIFT           (13U)
/*! FRAMERREN - When 1, enables an interrupt when a framing error has been detected.
 */
#define USART_INTENSET_FRAMERREN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_FRAMERREN_SHIFT)) & USART_INTENSET_FRAMERREN_MASK)
#define USART_INTENSET_PARITYERREN_MASK          (0x4000U)
#define USART_INTENSET_PARITYERREN_SHIFT         (14U)
/*! PARITYERREN - When 1, enables an interrupt when a parity error has been detected.
 */
#define USART_INTENSET_PARITYERREN(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_PARITYERREN_SHIFT)) & USART_INTENSET_PARITYERREN_MASK)
#define USART_INTENSET_RXNOISEEN_MASK            (0x8000U)
#define USART_INTENSET_RXNOISEEN_SHIFT           (15U)
/*! RXNOISEEN - When 1, enables an interrupt when noise is detected. See description of the RXNOISEINT bit in Table 354.
 */
#define USART_INTENSET_RXNOISEEN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXNOISEEN_SHIFT)) & USART_INTENSET_RXNOISEEN_MASK)
#define USART_INTENSET_ABERREN_MASK              (0x10000U)
#define USART_INTENSET_ABERREN_SHIFT             (16U)
/*! ABERREN - When 1, enables an interrupt when an auto baud error occurs.
 */
#define USART_INTENSET_ABERREN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_ABERREN_SHIFT)) & USART_INTENSET_ABERREN_MASK)
/*! @} */

/*! @name INTENCLR - Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared. */
/*! @{ */
#define USART_INTENCLR_TXIDLECLR_MASK            (0x8U)
#define USART_INTENCLR_TXIDLECLR_SHIFT           (3U)
/*! TXIDLECLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_TXIDLECLR(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXIDLECLR_SHIFT)) & USART_INTENCLR_TXIDLECLR_MASK)
#define USART_INTENCLR_DELTACTSCLR_MASK          (0x20U)
#define USART_INTENCLR_DELTACTSCLR_SHIFT         (5U)
/*! DELTACTSCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_DELTACTSCLR(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTACTSCLR_SHIFT)) & USART_INTENCLR_DELTACTSCLR_MASK)
#define USART_INTENCLR_TXDISCLR_MASK             (0x40U)
#define USART_INTENCLR_TXDISCLR_SHIFT            (6U)
/*! TXDISCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_TXDISCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXDISCLR_SHIFT)) & USART_INTENCLR_TXDISCLR_MASK)
#define USART_INTENCLR_DELTARXBRKCLR_MASK        (0x800U)
#define USART_INTENCLR_DELTARXBRKCLR_SHIFT       (11U)
/*! DELTARXBRKCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_DELTARXBRKCLR(x)          (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTARXBRKCLR_SHIFT)) & USART_INTENCLR_DELTARXBRKCLR_MASK)
#define USART_INTENCLR_STARTCLR_MASK             (0x1000U)
#define USART_INTENCLR_STARTCLR_SHIFT            (12U)
/*! STARTCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_STARTCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_STARTCLR_SHIFT)) & USART_INTENCLR_STARTCLR_MASK)
#define USART_INTENCLR_FRAMERRCLR_MASK           (0x2000U)
#define USART_INTENCLR_FRAMERRCLR_SHIFT          (13U)
/*! FRAMERRCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_FRAMERRCLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_FRAMERRCLR_SHIFT)) & USART_INTENCLR_FRAMERRCLR_MASK)
#define USART_INTENCLR_PARITYERRCLR_MASK         (0x4000U)
#define USART_INTENCLR_PARITYERRCLR_SHIFT        (14U)
/*! PARITYERRCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_PARITYERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_PARITYERRCLR_SHIFT)) & USART_INTENCLR_PARITYERRCLR_MASK)
#define USART_INTENCLR_RXNOISECLR_MASK           (0x8000U)
#define USART_INTENCLR_RXNOISECLR_SHIFT          (15U)
/*! RXNOISECLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_RXNOISECLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXNOISECLR_SHIFT)) & USART_INTENCLR_RXNOISECLR_MASK)
#define USART_INTENCLR_ABERRCLR_MASK             (0x10000U)
#define USART_INTENCLR_ABERRCLR_SHIFT            (16U)
/*! ABERRCLR - Writing 1 clears the corresponding bit in the INTENSET register.
 */
#define USART_INTENCLR_ABERRCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_ABERRCLR_SHIFT)) & USART_INTENCLR_ABERRCLR_MASK)
/*! @} */

/*! @name BRG - Baud Rate Generator register. 16-bit integer baud rate divisor value. */
/*! @{ */
#define USART_BRG_BRGVAL_MASK                    (0xFFFFU)
#define USART_BRG_BRGVAL_SHIFT                   (0U)
/*! BRGVAL - This value is used to divide the USART input clock to determine the baud rate, based on
 *    the input clock from the FRG. 0 = FCLK is used directly by the USART function. 1 = FCLK is
 *    divided by 2 before use by the USART function. 2 = FCLK is divided by 3 before use by the USART
 *    function. 0xFFFF = FCLK is divided by 65,536 before use by the USART function.
 */
#define USART_BRG_BRGVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_BRG_BRGVAL_SHIFT)) & USART_BRG_BRGVAL_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt status register. Reflects interrupts that are currently enabled. */
/*! @{ */
#define USART_INTSTAT_TXIDLE_MASK                (0x8U)
#define USART_INTSTAT_TXIDLE_SHIFT               (3U)
/*! TXIDLE - Transmitter Idle status.
 */
#define USART_INTSTAT_TXIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXIDLE_SHIFT)) & USART_INTSTAT_TXIDLE_MASK)
#define USART_INTSTAT_DELTACTS_MASK              (0x20U)
#define USART_INTSTAT_DELTACTS_SHIFT             (5U)
/*! DELTACTS - This bit is set when a change in the state of the CTS input is detected.
 */
#define USART_INTSTAT_DELTACTS(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTACTS_SHIFT)) & USART_INTSTAT_DELTACTS_MASK)
#define USART_INTSTAT_TXDISINT_MASK              (0x40U)
#define USART_INTSTAT_TXDISINT_SHIFT             (6U)
/*! TXDISINT - Transmitter Disabled Interrupt flag.
 */
#define USART_INTSTAT_TXDISINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXDISINT_SHIFT)) & USART_INTSTAT_TXDISINT_MASK)
#define USART_INTSTAT_DELTARXBRK_MASK            (0x800U)
#define USART_INTSTAT_DELTARXBRK_SHIFT           (11U)
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs.
 */
#define USART_INTSTAT_DELTARXBRK(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTARXBRK_SHIFT)) & USART_INTSTAT_DELTARXBRK_MASK)
#define USART_INTSTAT_START_MASK                 (0x1000U)
#define USART_INTSTAT_START_SHIFT                (12U)
/*! START - This bit is set when a start is detected on the receiver input.
 */
#define USART_INTSTAT_START(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_START_SHIFT)) & USART_INTSTAT_START_MASK)
#define USART_INTSTAT_FRAMERRINT_MASK            (0x2000U)
#define USART_INTSTAT_FRAMERRINT_SHIFT           (13U)
/*! FRAMERRINT - Framing Error interrupt flag.
 */
#define USART_INTSTAT_FRAMERRINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_FRAMERRINT_SHIFT)) & USART_INTSTAT_FRAMERRINT_MASK)
#define USART_INTSTAT_PARITYERRINT_MASK          (0x4000U)
#define USART_INTSTAT_PARITYERRINT_SHIFT         (14U)
/*! PARITYERRINT - Parity Error interrupt flag.
 */
#define USART_INTSTAT_PARITYERRINT(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_PARITYERRINT_SHIFT)) & USART_INTSTAT_PARITYERRINT_MASK)
#define USART_INTSTAT_RXNOISEINT_MASK            (0x8000U)
#define USART_INTSTAT_RXNOISEINT_SHIFT           (15U)
/*! RXNOISEINT - Received Noise interrupt flag.
 */
#define USART_INTSTAT_RXNOISEINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXNOISEINT_SHIFT)) & USART_INTSTAT_RXNOISEINT_MASK)
#define USART_INTSTAT_ABERRINT_MASK              (0x10000U)
#define USART_INTSTAT_ABERRINT_SHIFT             (16U)
/*! ABERRINT - Auto baud Error Interrupt flag.
 */
#define USART_INTSTAT_ABERRINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_ABERRINT_SHIFT)) & USART_INTSTAT_ABERRINT_MASK)
/*! @} */

/*! @name OSR - Oversample selection register for asynchronous communication. */
/*! @{ */
#define USART_OSR_OSRVAL_MASK                    (0xFU)
#define USART_OSR_OSRVAL_SHIFT                   (0U)
/*! OSRVAL - Oversample Selection Value. 0 to 3 = not supported 0x4 = 5 function clocks are used to
 *    transmit and receive each data bit. 0x5 = 6 function clocks are used to transmit and receive
 *    each data bit. 0xF= 16 function clocks are used to transmit and receive each data bit.
 */
#define USART_OSR_OSRVAL(x)                      (((uint32_t)(((uint32_t)(x)) << USART_OSR_OSRVAL_SHIFT)) & USART_OSR_OSRVAL_MASK)
/*! @} */

/*! @name ADDR - Address register for automatic address matching. */
/*! @{ */
#define USART_ADDR_ADDRESS_MASK                  (0xFFU)
#define USART_ADDR_ADDRESS_SHIFT                 (0U)
/*! ADDRESS - 8-bit address used with automatic address matching. Used when address detection is
 *    enabled (ADDRDET in CTL = 1) and automatic address matching is enabled (AUTOADDR in CFG = 1).
 */
#define USART_ADDR_ADDRESS(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ADDR_ADDRESS_SHIFT)) & USART_ADDR_ADDRESS_MASK)
/*! @} */

/*! @name FIFOCFG - FIFO configuration and enable register. */
/*! @{ */
#define USART_FIFOCFG_ENABLETX_MASK              (0x1U)
#define USART_FIFOCFG_ENABLETX_SHIFT             (0U)
/*! ENABLETX - Enable the transmit FIFO.
 *  0b0..The transmit FIFO is not enabled.
 *  0b1..The transmit FIFO is enabled.
 */
#define USART_FIFOCFG_ENABLETX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLETX_SHIFT)) & USART_FIFOCFG_ENABLETX_MASK)
#define USART_FIFOCFG_ENABLERX_MASK              (0x2U)
#define USART_FIFOCFG_ENABLERX_SHIFT             (1U)
/*! ENABLERX - Enable the receive FIFO.
 *  0b0..The receive FIFO is not enabled.
 *  0b1..The receive FIFO is enabled.
 */
#define USART_FIFOCFG_ENABLERX(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_ENABLERX_SHIFT)) & USART_FIFOCFG_ENABLERX_MASK)
#define USART_FIFOCFG_SIZE_MASK                  (0x30U)
#define USART_FIFOCFG_SIZE_SHIFT                 (4U)
/*! SIZE - FIFO size configuration. This is a read-only field. 0x0 = FIFO is configured as 16
 *    entries of 8 bits. 0x1, 0x2, 0x3 = not applicable to USART.
 */
#define USART_FIFOCFG_SIZE(x)                    (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_SIZE_SHIFT)) & USART_FIFOCFG_SIZE_MASK)
#define USART_FIFOCFG_DMATX_MASK                 (0x1000U)
#define USART_FIFOCFG_DMATX_SHIFT                (12U)
/*! DMATX - DMA configuration for transmit.
 *  0b0..DMA is not used for the transmit function.
 *  0b1..Trigger DMA for the transmit function if the FIFO is not full. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define USART_FIFOCFG_DMATX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMATX_SHIFT)) & USART_FIFOCFG_DMATX_MASK)
#define USART_FIFOCFG_DMARX_MASK                 (0x2000U)
#define USART_FIFOCFG_DMARX_SHIFT                (13U)
/*! DMARX - DMA configuration for receive.
 *  0b0..DMA is not used for the receive function.
 *  0b1..Trigger DMA for the receive function if the FIFO is not empty. Generally, data interrupts would be disabled if DMA is enabled.
 */
#define USART_FIFOCFG_DMARX(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_DMARX_SHIFT)) & USART_FIFOCFG_DMARX_MASK)
#define USART_FIFOCFG_WAKETX_MASK                (0x4000U)
#define USART_FIFOCFG_WAKETX_SHIFT               (14U)
/*! WAKETX - Wake-up for transmit FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the transmit FIFO level reaches the value specified by TXLVL in
 *       FIFOTRIG, even when the TXLVL interrupt is not enabled.
 */
#define USART_FIFOCFG_WAKETX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKETX_SHIFT)) & USART_FIFOCFG_WAKETX_MASK)
#define USART_FIFOCFG_WAKERX_MASK                (0x8000U)
#define USART_FIFOCFG_WAKERX_SHIFT               (15U)
/*! WAKERX - Wake-up for receive FIFO level. This allows the device to be woken from reduced power
 *    modes (up to power-down, as long as the peripheral function works in that power mode) without
 *    enabling the TXLVL interrupt. Only DMA wakes up, processes data, and goes back to sleep. The
 *    CPU will remain stopped until woken by another cause, such as DMA completion. See Hardware
 *    Wake-up control register.
 *  0b0..Only enabled interrupts will wake up the device form reduced power modes.
 *  0b1..A device wake-up for DMA will occur if the receive FIFO level reaches the value specified by RXLVL in
 *       FIFOTRIG, even when the RXLVL interrupt is not enabled.
 */
#define USART_FIFOCFG_WAKERX(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_WAKERX_SHIFT)) & USART_FIFOCFG_WAKERX_MASK)
#define USART_FIFOCFG_EMPTYTX_MASK               (0x10000U)
#define USART_FIFOCFG_EMPTYTX_SHIFT              (16U)
/*! EMPTYTX - Empty command for the transmit FIFO. When a 1 is written to this bit, the TX FIFO is emptied.
 */
#define USART_FIFOCFG_EMPTYTX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYTX_SHIFT)) & USART_FIFOCFG_EMPTYTX_MASK)
#define USART_FIFOCFG_EMPTYRX_MASK               (0x20000U)
#define USART_FIFOCFG_EMPTYRX_SHIFT              (17U)
/*! EMPTYRX - Empty command for the receive FIFO. When a 1 is written to this bit, the RX FIFO is emptied.
 */
#define USART_FIFOCFG_EMPTYRX(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOCFG_EMPTYRX_SHIFT)) & USART_FIFOCFG_EMPTYRX_MASK)
/*! @} */

/*! @name FIFOSTAT - FIFO status register. */
/*! @{ */
#define USART_FIFOSTAT_TXERR_MASK                (0x1U)
#define USART_FIFOSTAT_TXERR_SHIFT               (0U)
/*! TXERR - TX FIFO error. Will be set if a transmit FIFO error occurs. This could be an overflow
 *    caused by pushing data into a full FIFO, or by an underflow if the FIFO is empty when data is
 *    needed. Cleared by writing a 1 to this bit.
 */
#define USART_FIFOSTAT_TXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXERR_SHIFT)) & USART_FIFOSTAT_TXERR_MASK)
#define USART_FIFOSTAT_RXERR_MASK                (0x2U)
#define USART_FIFOSTAT_RXERR_SHIFT               (1U)
/*! RXERR - RX FIFO error. Will be set if a receive FIFO overflow occurs, caused by software or DMA
 *    not emptying the FIFO fast enough. Cleared by writing a 1 to this bit.
 */
#define USART_FIFOSTAT_RXERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXERR_SHIFT)) & USART_FIFOSTAT_RXERR_MASK)
#define USART_FIFOSTAT_PERINT_MASK               (0x8U)
#define USART_FIFOSTAT_PERINT_SHIFT              (3U)
/*! PERINT - Peripheral interrupt. When 1, this indicates that the peripheral function has asserted
 *    an interrupt. The details can be found by reading the peripheral's STAT register.
 */
#define USART_FIFOSTAT_PERINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_PERINT_SHIFT)) & USART_FIFOSTAT_PERINT_MASK)
#define USART_FIFOSTAT_TXEMPTY_MASK              (0x10U)
#define USART_FIFOSTAT_TXEMPTY_SHIFT             (4U)
/*! TXEMPTY - Transmit FIFO empty. When 1, the transmit FIFO is empty. The peripheral may still be processing the last piece of data.
 */
#define USART_FIFOSTAT_TXEMPTY(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXEMPTY_SHIFT)) & USART_FIFOSTAT_TXEMPTY_MASK)
#define USART_FIFOSTAT_TXNOTFULL_MASK            (0x20U)
#define USART_FIFOSTAT_TXNOTFULL_SHIFT           (5U)
/*! TXNOTFULL - Transmit FIFO not full. When 1, the transmit FIFO is not full, so more data can be
 *    written. When 0, the transmit FIFO is full and another write would cause it to overflow.
 */
#define USART_FIFOSTAT_TXNOTFULL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXNOTFULL_SHIFT)) & USART_FIFOSTAT_TXNOTFULL_MASK)
#define USART_FIFOSTAT_RXNOTEMPTY_MASK           (0x40U)
#define USART_FIFOSTAT_RXNOTEMPTY_SHIFT          (6U)
/*! RXNOTEMPTY - Receive FIFO not empty. When 1, the receive FIFO is not empty, so data can be read. When 0, the receive FIFO is empty.
 */
#define USART_FIFOSTAT_RXNOTEMPTY(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXNOTEMPTY_SHIFT)) & USART_FIFOSTAT_RXNOTEMPTY_MASK)
#define USART_FIFOSTAT_RXFULL_MASK               (0x80U)
#define USART_FIFOSTAT_RXFULL_SHIFT              (7U)
/*! RXFULL - Receive FIFO full. When 1, the receive FIFO is full. Data needs to be read out to
 *    prevent the peripheral from causing an overflow.
 */
#define USART_FIFOSTAT_RXFULL(x)                 (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXFULL_SHIFT)) & USART_FIFOSTAT_RXFULL_MASK)
#define USART_FIFOSTAT_TXLVL_MASK                (0x1F00U)
#define USART_FIFOSTAT_TXLVL_SHIFT               (8U)
/*! TXLVL - Transmit FIFO current level. A 0 means the TX FIFO is currently empty, and the TXEMPTY
 *    and TXNOTFULL flags will be 1. Other values tell how much data is actually in the TX FIFO at
 *    the point where the read occurs. If the TX FIFO is full, the TXEMPTY and TXNOTFULL flags will be
 *    0.
 */
#define USART_FIFOSTAT_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_TXLVL_SHIFT)) & USART_FIFOSTAT_TXLVL_MASK)
#define USART_FIFOSTAT_RXLVL_MASK                (0x1F0000U)
#define USART_FIFOSTAT_RXLVL_SHIFT               (16U)
/*! RXLVL - Receive FIFO current level. A 0 means the RX FIFO is currently empty, and the RXFULL and
 *    RXNOTEMPTY flags will be 0. Other values tell how much data is actually in the RX FIFO at the
 *    point where the read occurs. If the RX FIFO is full, the RXFULL and RXNOTEMPTY flags will be
 *    1.
 */
#define USART_FIFOSTAT_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOSTAT_RXLVL_SHIFT)) & USART_FIFOSTAT_RXLVL_MASK)
/*! @} */

/*! @name FIFOTRIG - FIFO trigger settings for interrupt and DMA request. */
/*! @{ */
#define USART_FIFOTRIG_TXLVLENA_MASK             (0x1U)
#define USART_FIFOTRIG_TXLVLENA_SHIFT            (0U)
/*! TXLVLENA - Transmit FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMATX in FIFOCFG is set.
 *  0b0..Transmit FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the transmit FIFO level reaches the value specified by the TXLVL field in this register.
 */
#define USART_FIFOTRIG_TXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVLENA_SHIFT)) & USART_FIFOTRIG_TXLVLENA_MASK)
#define USART_FIFOTRIG_RXLVLENA_MASK             (0x2U)
#define USART_FIFOTRIG_RXLVLENA_SHIFT            (1U)
/*! RXLVLENA - Receive FIFO level trigger enable. This trigger will become an interrupt if enabled
 *    in FIFOINTENSET, or a DMA trigger if DMARX in FIFOCFG is set.
 *  0b0..Receive FIFO level does not generate a FIFO level trigger.
 *  0b1..An trigger will be generated if the receive FIFO level reaches the value specified by the RXLVL field in this register.
 */
#define USART_FIFOTRIG_RXLVLENA(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVLENA_SHIFT)) & USART_FIFOTRIG_RXLVLENA_MASK)
#define USART_FIFOTRIG_TXLVL_MASK                (0xF00U)
#define USART_FIFOTRIG_TXLVL_SHIFT               (8U)
/*! TXLVL - Transmit FIFO level trigger point. This field is used only when TXLVLENA = 1. If enabled
 *    to do so, the FIFO level can wake up the device just enough to perform DMA, then return to
 *    the reduced power mode. See Hardware Wake-up control register. 0 = trigger when the TX FIFO
 *    becomes empty. 1 = trigger when the TX FIFO level decreases to one entry. 15 = trigger when the TX
 *    FIFO level decreases to 15 entries (is no longer full).
 */
#define USART_FIFOTRIG_TXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_TXLVL_SHIFT)) & USART_FIFOTRIG_TXLVL_MASK)
#define USART_FIFOTRIG_RXLVL_MASK                (0xF0000U)
#define USART_FIFOTRIG_RXLVL_SHIFT               (16U)
/*! RXLVL - Receive FIFO level trigger point. The RX FIFO level is checked when a new piece of data
 *    is received. This field is used only when RXLVLENA = 1. If enabled to do so, the FIFO level
 *    can wake up the device just enough to perform DMA, then return to the reduced power mode. See
 *    Hardware Wake-up control register. 0 = trigger when the RX FIFO has received one entry (is no
 *    longer empty). 1 = trigger when the RX FIFO has received two entries. 15 = trigger when the RX
 *    FIFO has received 16 entries (has become full).
 */
#define USART_FIFOTRIG_RXLVL(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFOTRIG_RXLVL_SHIFT)) & USART_FIFOTRIG_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENSET - FIFO interrupt enable set (enable) and read register. */
/*! @{ */
#define USART_FIFOINTENSET_TXERR_MASK            (0x1U)
#define USART_FIFOINTENSET_TXERR_SHIFT           (0U)
/*! TXERR - Determines whether an interrupt occurs when a transmit error occurs, based on the TXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a transmit error.
 *  0b1..An interrupt will be generated when a transmit error occurs.
 */
#define USART_FIFOINTENSET_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXERR_SHIFT)) & USART_FIFOINTENSET_TXERR_MASK)
#define USART_FIFOINTENSET_RXERR_MASK            (0x2U)
#define USART_FIFOINTENSET_RXERR_SHIFT           (1U)
/*! RXERR - Determines whether an interrupt occurs when a receive error occurs, based on the RXERR flag in the FIFOSTAT register.
 *  0b0..No interrupt will be generated for a receive error.
 *  0b1..An interrupt will be generated when a receive error occurs.
 */
#define USART_FIFOINTENSET_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXERR_SHIFT)) & USART_FIFOINTENSET_RXERR_MASK)
#define USART_FIFOINTENSET_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENSET_TXLVL_SHIFT           (2U)
/*! TXLVL - Determines whether an interrupt occurs when a the transmit FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the TX FIFO level.
 *  0b1..If TXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the TX FIFO level decreases
 *       to the level specified by TXLVL in the FIFOTRIG register.
 */
#define USART_FIFOINTENSET_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_TXLVL_SHIFT)) & USART_FIFOINTENSET_TXLVL_MASK)
#define USART_FIFOINTENSET_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENSET_RXLVL_SHIFT           (3U)
/*! RXLVL - Determines whether an interrupt occurs when a the receive FIFO reaches the level
 *    specified by the TXLVL field in the FIFOTRIG register.
 *  0b0..No interrupt will be generated based on the RX FIFO level.
 *  0b1..If RXLVLENA in the FIFOTRIG register = 1, an interrupt will be generated when the when the RX FIFO level
 *       increases to the level specified by RXLVL in the FIFOTRIG register.
 */
#define USART_FIFOINTENSET_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENSET_RXLVL_SHIFT)) & USART_FIFOINTENSET_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTENCLR - FIFO interrupt enable clear (disable) and read register. */
/*! @{ */
#define USART_FIFOINTENCLR_TXERR_MASK            (0x1U)
#define USART_FIFOINTENCLR_TXERR_SHIFT           (0U)
/*! TXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define USART_FIFOINTENCLR_TXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXERR_SHIFT)) & USART_FIFOINTENCLR_TXERR_MASK)
#define USART_FIFOINTENCLR_RXERR_MASK            (0x2U)
#define USART_FIFOINTENCLR_RXERR_SHIFT           (1U)
/*! RXERR - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define USART_FIFOINTENCLR_RXERR(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXERR_SHIFT)) & USART_FIFOINTENCLR_RXERR_MASK)
#define USART_FIFOINTENCLR_TXLVL_MASK            (0x4U)
#define USART_FIFOINTENCLR_TXLVL_SHIFT           (2U)
/*! TXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define USART_FIFOINTENCLR_TXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_TXLVL_SHIFT)) & USART_FIFOINTENCLR_TXLVL_MASK)
#define USART_FIFOINTENCLR_RXLVL_MASK            (0x8U)
#define USART_FIFOINTENCLR_RXLVL_SHIFT           (3U)
/*! RXLVL - Writing one clears the corresponding bits in the FIFOINTENSET register.
 */
#define USART_FIFOINTENCLR_RXLVL(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTENCLR_RXLVL_SHIFT)) & USART_FIFOINTENCLR_RXLVL_MASK)
/*! @} */

/*! @name FIFOINTSTAT - FIFO interrupt status register. */
/*! @{ */
#define USART_FIFOINTSTAT_TXERR_MASK             (0x1U)
#define USART_FIFOINTSTAT_TXERR_SHIFT            (0U)
/*! TXERR - TX FIFO error.
 */
#define USART_FIFOINTSTAT_TXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXERR_SHIFT)) & USART_FIFOINTSTAT_TXERR_MASK)
#define USART_FIFOINTSTAT_RXERR_MASK             (0x2U)
#define USART_FIFOINTSTAT_RXERR_SHIFT            (1U)
/*! RXERR - RX FIFO error.
 */
#define USART_FIFOINTSTAT_RXERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXERR_SHIFT)) & USART_FIFOINTSTAT_RXERR_MASK)
#define USART_FIFOINTSTAT_TXLVL_MASK             (0x4U)
#define USART_FIFOINTSTAT_TXLVL_SHIFT            (2U)
/*! TXLVL - Transmit FIFO level interrupt.
 */
#define USART_FIFOINTSTAT_TXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_TXLVL_SHIFT)) & USART_FIFOINTSTAT_TXLVL_MASK)
#define USART_FIFOINTSTAT_RXLVL_MASK             (0x8U)
#define USART_FIFOINTSTAT_RXLVL_SHIFT            (3U)
/*! RXLVL - Receive FIFO level interrupt.
 */
#define USART_FIFOINTSTAT_RXLVL(x)               (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_RXLVL_SHIFT)) & USART_FIFOINTSTAT_RXLVL_MASK)
#define USART_FIFOINTSTAT_PERINT_MASK            (0x10U)
#define USART_FIFOINTSTAT_PERINT_SHIFT           (4U)
/*! PERINT - Peripheral interrupt.
 */
#define USART_FIFOINTSTAT_PERINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFOINTSTAT_PERINT_SHIFT)) & USART_FIFOINTSTAT_PERINT_MASK)
/*! @} */

/*! @name FIFOWR - FIFO write data. */
/*! @{ */
#define USART_FIFOWR_TXDATA_MASK                 (0x1FFU)
#define USART_FIFOWR_TXDATA_SHIFT                (0U)
/*! TXDATA - Transmit data to the FIFO.
 */
#define USART_FIFOWR_TXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFOWR_TXDATA_SHIFT)) & USART_FIFOWR_TXDATA_MASK)
/*! @} */

/*! @name FIFORD - FIFO read data. */
/*! @{ */
#define USART_FIFORD_RXDATA_MASK                 (0x1FFU)
#define USART_FIFORD_RXDATA_SHIFT                (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on the DATALEN and PARITYSEL settings.
 */
#define USART_FIFORD_RXDATA(x)                   (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXDATA_SHIFT)) & USART_FIFORD_RXDATA_MASK)
#define USART_FIFORD_FRAMERR_MASK                (0x2000U)
#define USART_FIFORD_FRAMERR_SHIFT               (13U)
/*! FRAMERR - Framing Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO, and indicates that the character was received with a missing stop bit at
 *    the expected location. This could be an indication of a baud rate or configuration mismatch
 *    with the transmitting source.
 */
#define USART_FIFORD_FRAMERR(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_FRAMERR_SHIFT)) & USART_FIFORD_FRAMERR_MASK)
#define USART_FIFORD_PARITYERR_MASK              (0x4000U)
#define USART_FIFORD_PARITYERR_SHIFT             (14U)
/*! PARITYERR - Parity Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO. This bit will be set when a parity error is detected in a received
 *    character.
 */
#define USART_FIFORD_PARITYERR(x)                (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_PARITYERR_SHIFT)) & USART_FIFORD_PARITYERR_MASK)
#define USART_FIFORD_RXNOISE_MASK                (0x8000U)
#define USART_FIFORD_RXNOISE_SHIFT               (15U)
/*! RXNOISE - Received Noise flag. See description of the RxNoiseInt bit in Table 354.
 */
#define USART_FIFORD_RXNOISE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_FIFORD_RXNOISE_SHIFT)) & USART_FIFORD_RXNOISE_MASK)
/*! @} */

/*! @name FIFORDNOPOP - FIFO data read with no FIFO pop. */
/*! @{ */
#define USART_FIFORDNOPOP_RXDATA_MASK            (0x1FFU)
#define USART_FIFORDNOPOP_RXDATA_SHIFT           (0U)
/*! RXDATA - Received data from the FIFO. The number of bits used depends on the DATALEN and PARITYSEL settings.
 */
#define USART_FIFORDNOPOP_RXDATA(x)              (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXDATA_SHIFT)) & USART_FIFORDNOPOP_RXDATA_MASK)
#define USART_FIFORDNOPOP_FRAMERR_MASK           (0x2000U)
#define USART_FIFORDNOPOP_FRAMERR_SHIFT          (13U)
/*! FRAMERR - Framing Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO, and indicates that the character was received with a missing stop bit at
 *    the expected location. This could be an indication of a baud rate or configuration mismatch
 *    with the transmitting source.
 */
#define USART_FIFORDNOPOP_FRAMERR(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_FRAMERR_SHIFT)) & USART_FIFORDNOPOP_FRAMERR_MASK)
#define USART_FIFORDNOPOP_PARITYERR_MASK         (0x4000U)
#define USART_FIFORDNOPOP_PARITYERR_SHIFT        (14U)
/*! PARITYERR - Parity Error status flag. This bit reflects the status for the data it is read along
 *    with from the FIFO. This bit will be set when a parity error is detected in a received
 *    character.
 */
#define USART_FIFORDNOPOP_PARITYERR(x)           (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_PARITYERR_SHIFT)) & USART_FIFORDNOPOP_PARITYERR_MASK)
#define USART_FIFORDNOPOP_RXNOISE_MASK           (0x8000U)
#define USART_FIFORDNOPOP_RXNOISE_SHIFT          (15U)
/*! RXNOISE - Received Noise flag. See description of the RxNoiseInt bit in Table 354.
 */
#define USART_FIFORDNOPOP_RXNOISE(x)             (((uint32_t)(((uint32_t)(x)) << USART_FIFORDNOPOP_RXNOISE_SHIFT)) & USART_FIFORDNOPOP_RXNOISE_MASK)
/*! @} */

/*! @name ID - Peripheral identification register. */
/*! @{ */
#define USART_ID_APERTURE_MASK                   (0xFFU)
#define USART_ID_APERTURE_SHIFT                  (0U)
/*! APERTURE - Aperture: encoded as (aperture size/4K) -1, so 0x00 means a 4K aperture.
 */
#define USART_ID_APERTURE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_ID_APERTURE_SHIFT)) & USART_ID_APERTURE_MASK)
#define USART_ID_MINOR_REV_MASK                  (0xF00U)
#define USART_ID_MINOR_REV_SHIFT                 (8U)
/*! MINOR_REV - Minor revision of module implementation.
 */
#define USART_ID_MINOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MINOR_REV_SHIFT)) & USART_ID_MINOR_REV_MASK)
#define USART_ID_MAJOR_REV_MASK                  (0xF000U)
#define USART_ID_MAJOR_REV_SHIFT                 (12U)
/*! MAJOR_REV - Major revision of module implementation.
 */
#define USART_ID_MAJOR_REV(x)                    (((uint32_t)(((uint32_t)(x)) << USART_ID_MAJOR_REV_SHIFT)) & USART_ID_MAJOR_REV_MASK)
#define USART_ID_ID_MASK                         (0xFFFF0000U)
#define USART_ID_ID_SHIFT                        (16U)
/*! ID - Module identifier for the selected function.
 */
#define USART_ID_ID(x)                           (((uint32_t)(((uint32_t)(x)) << USART_ID_ID_SHIFT)) & USART_ID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USART_Register_Masks */


/* USART - Peripheral instance base addresses */
/** Peripheral USART0 base address */
#define USART0_BASE                              (0x40086000u)
/** Peripheral USART0 base pointer */
#define USART0                                   ((USART_Type *)USART0_BASE)
/** Peripheral USART1 base address */
#define USART1_BASE                              (0x40087000u)
/** Peripheral USART1 base pointer */
#define USART1                                   ((USART_Type *)USART1_BASE)
/** Peripheral USART2 base address */
#define USART2_BASE                              (0x40088000u)
/** Peripheral USART2 base pointer */
#define USART2                                   ((USART_Type *)USART2_BASE)
/** Peripheral USART3 base address */
#define USART3_BASE                              (0x40089000u)
/** Peripheral USART3 base pointer */
#define USART3                                   ((USART_Type *)USART3_BASE)
/** Peripheral USART4 base address */
#define USART4_BASE                              (0x4008A000u)
/** Peripheral USART4 base pointer */
#define USART4                                   ((USART_Type *)USART4_BASE)
/** Peripheral USART5 base address */
#define USART5_BASE                              (0x40096000u)
/** Peripheral USART5 base pointer */
#define USART5                                   ((USART_Type *)USART5_BASE)
/** Peripheral USART6 base address */
#define USART6_BASE                              (0x40097000u)
/** Peripheral USART6 base pointer */
#define USART6                                   ((USART_Type *)USART6_BASE)
/** Peripheral USART7 base address */
#define USART7_BASE                              (0x40098000u)
/** Peripheral USART7 base pointer */
#define USART7                                   ((USART_Type *)USART7_BASE)
/** Array initializer of USART peripheral base addresses */
#define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE, USART5_BASE, USART6_BASE, USART7_BASE }
/** Array initializer of USART peripheral base pointers */
#define USART_BASE_PTRS                          { USART0, USART1, USART2, USART3, USART4, USART5, USART6, USART7 }
/** Interrupt vectors for the USART peripheral type */
#define USART_IRQS                               { FLEXCOMM0_IRQn, FLEXCOMM1_IRQn, FLEXCOMM2_IRQn, FLEXCOMM3_IRQn, FLEXCOMM4_IRQn, FLEXCOMM5_IRQn, FLEXCOMM6_IRQn, FLEXCOMM7_IRQn }

/*!
 * @}
 */ /* end of group USART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- USB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Peripheral_Access_Layer USB Peripheral Access Layer
 * @{
 */

/** USB - Register Layout Typedef */
typedef struct {
  __IO uint32_t DEVCMDSTAT;                        /**< USB Device Command/Status register, offset: 0x0 */
  __IO uint32_t INFO;                              /**< USB Info register, offset: 0x4 */
  __IO uint32_t EPLISTSTART;                       /**< USB EP Command/Status List start address, offset: 0x8 */
  __IO uint32_t DATABUFSTART;                      /**< USB Data buffer start address, offset: 0xC */
  __IO uint32_t LPM;                               /**< USB Link Power Management register, offset: 0x10 */
  __IO uint32_t EPSKIP;                            /**< USB Endpoint skip, offset: 0x14 */
  __IO uint32_t EPINUSE;                           /**< USB Endpoint Buffer in use, offset: 0x18 */
  __IO uint32_t EPBUFCFG;                          /**< USB Endpoint Buffer Configuration register, offset: 0x1C */
  __IO uint32_t INTSTAT;                           /**< USB interrupt status register, offset: 0x20 */
  __IO uint32_t INTEN;                             /**< USB interrupt enable register, offset: 0x24 */
  __IO uint32_t INTSETSTAT;                        /**< USB set interrupt status register, offset: 0x28 */
       uint8_t RESERVED_0[8];
  __I  uint32_t EPTOGGLE;                          /**< USB Endpoint toggle register, offset: 0x34 */
} USB_Type;

/* ----------------------------------------------------------------------------
   -- USB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup USB_Register_Masks USB Register Masks
 * @{
 */

/*! @name DEVCMDSTAT - USB Device Command/Status register */
/*! @{ */
#define USB_DEVCMDSTAT_DEV_ADDR_MASK             (0x7FU)
#define USB_DEVCMDSTAT_DEV_ADDR_SHIFT            (0U)
/*! DEV_ADDR - USB device address. After bus reset, the address is reset to 0x00. If the enable bit
 *    is set, the device will respond on packets for function address DEV_ADDR. When receiving a
 *    SetAddress Control Request from the USB host, software must program the new address before
 *    completing the status phase of the SetAddress Control Request.
 */
#define USB_DEVCMDSTAT_DEV_ADDR(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_ADDR_SHIFT)) & USB_DEVCMDSTAT_DEV_ADDR_MASK)
#define USB_DEVCMDSTAT_DEV_EN_MASK               (0x80U)
#define USB_DEVCMDSTAT_DEV_EN_SHIFT              (7U)
/*! DEV_EN - USB device enable. If this bit is set, the HW will start responding on packets for function address DEV_ADDR.
 */
#define USB_DEVCMDSTAT_DEV_EN(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DEV_EN_SHIFT)) & USB_DEVCMDSTAT_DEV_EN_MASK)
#define USB_DEVCMDSTAT_SETUP_MASK                (0x100U)
#define USB_DEVCMDSTAT_SETUP_SHIFT               (8U)
/*! SETUP - SETUP token received. If a SETUP token is received and acknowledged by the device, this
 *    bit is set. As long as this bit is set all received IN and OUT tokens will be NAKed by HW. SW
 *    must clear this bit by writing a one. If this bit is zero, HW will handle the tokens to the
 *    CTRL EP0 as indicated by the CTRL EP0 IN and OUT data information programmed by SW.
 */
#define USB_DEVCMDSTAT_SETUP(x)                  (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_SETUP_SHIFT)) & USB_DEVCMDSTAT_SETUP_MASK)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK        (0x200U)
#define USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT       (9U)
/*! FORCE_NEEDCLK - Forces the NEEDCLK output to always be on:
 *  0b0..USB_NEEDCLK has normal function.
 *  0b1..USB_NEEDCLK always 1. Clock will not be stopped in case of suspend.
 */
#define USB_DEVCMDSTAT_FORCE_NEEDCLK(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_FORCE_NEEDCLK_SHIFT)) & USB_DEVCMDSTAT_FORCE_NEEDCLK_MASK)
#define USB_DEVCMDSTAT_LPM_SUP_MASK              (0x800U)
#define USB_DEVCMDSTAT_LPM_SUP_SHIFT             (11U)
/*! LPM_SUP - LPM Supported:
 *  0b0..LPM not supported.
 *  0b1..LPM supported.
 */
#define USB_DEVCMDSTAT_LPM_SUP(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUP_SHIFT)) & USB_DEVCMDSTAT_LPM_SUP_MASK)
#define USB_DEVCMDSTAT_INTONNAK_AO_MASK          (0x1000U)
#define USB_DEVCMDSTAT_INTONNAK_AO_SHIFT         (12U)
/*! INTONNAK_AO - Interrupt on NAK for interrupt and bulk OUT EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_AO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AO_MASK)
#define USB_DEVCMDSTAT_INTONNAK_AI_MASK          (0x2000U)
#define USB_DEVCMDSTAT_INTONNAK_AI_SHIFT         (13U)
/*! INTONNAK_AI - Interrupt on NAK for interrupt and bulk IN EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_AI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_AI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_AI_MASK)
#define USB_DEVCMDSTAT_INTONNAK_CO_MASK          (0x4000U)
#define USB_DEVCMDSTAT_INTONNAK_CO_SHIFT         (14U)
/*! INTONNAK_CO - Interrupt on NAK for control OUT EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_CO(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CO_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CO_MASK)
#define USB_DEVCMDSTAT_INTONNAK_CI_MASK          (0x8000U)
#define USB_DEVCMDSTAT_INTONNAK_CI_SHIFT         (15U)
/*! INTONNAK_CI - Interrupt on NAK for control IN EP
 *  0b0..Only acknowledged packets generate an interrupt
 *  0b1..Both acknowledged and NAKed packets generate interrupts.
 */
#define USB_DEVCMDSTAT_INTONNAK_CI(x)            (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_INTONNAK_CI_SHIFT)) & USB_DEVCMDSTAT_INTONNAK_CI_MASK)
#define USB_DEVCMDSTAT_DCON_MASK                 (0x10000U)
#define USB_DEVCMDSTAT_DCON_SHIFT                (16U)
/*! DCON - Device status - connect. The connect bit must be set by SW to indicate that the device
 *    must signal a connect. The pull-up resistor on USB_DP will be enabled when this bit is set and
 *    the VBUSDEBOUNCED bit is one.
 */
#define USB_DEVCMDSTAT_DCON(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_SHIFT)) & USB_DEVCMDSTAT_DCON_MASK)
#define USB_DEVCMDSTAT_DSUS_MASK                 (0x20000U)
#define USB_DEVCMDSTAT_DSUS_SHIFT                (17U)
/*! DSUS - Device status - suspend. The suspend bit indicates the current suspend state. It is set
 *    to 1 when the device hasn't seen any activity on its upstream port for more than 3
 *    milliseconds. It is reset to 0 on any activity. When the device is suspended (Suspend bit DSUS = 1) and
 *    the software writes a 0 to it, the device will generate a remote wake-up. This will only happen
 *    when the device is connected (Connect bit = 1). When the device is not connected or not
 *    suspended, a writing a 0 has no effect. Writing a 1 never has an effect.
 */
#define USB_DEVCMDSTAT_DSUS(x)                   (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_SHIFT)) & USB_DEVCMDSTAT_DSUS_MASK)
#define USB_DEVCMDSTAT_LPM_SUS_MASK              (0x80000U)
#define USB_DEVCMDSTAT_LPM_SUS_SHIFT             (19U)
/*! LPM_SUS - Device status - LPM Suspend. This bit represents the current LPM suspend state. It is
 *    set to 1 by HW when the device has acknowledged the LPM request from the USB host and the
 *    Token Retry Time of 10 ms has elapsed. When the device is in the LPM suspended state (LPM suspend
 *    bit = 1) and the software writes a zero to this bit, the device will generate a remote
 *    walk-up. Software can only write a zero to this bit when the LPM_REWP bit is set to 1. HW resets this
 *    bit when it receives a host initiated resume. HW only updates the LPM_SUS bit when the
 *    LPM_SUPP bit is equal to one.
 */
#define USB_DEVCMDSTAT_LPM_SUS(x)                (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_SUS_SHIFT)) & USB_DEVCMDSTAT_LPM_SUS_MASK)
#define USB_DEVCMDSTAT_LPM_REWP_MASK             (0x100000U)
#define USB_DEVCMDSTAT_LPM_REWP_SHIFT            (20U)
/*! LPM_REWP - LPM Remote Wake-up Enabled by USB host. HW sets this bit to one when the bRemoteWake
 *    bit in the LPM extended token is set to 1. HW will reset this bit to 0 when it receives the
 *    host initiated LPM resume, when a remote wake-up is sent by the device or when a USB bus reset
 *    is received. Software can use this bit to check if the remote wake-up feature is enabled by the
 *    host for the LPM transaction.
 */
#define USB_DEVCMDSTAT_LPM_REWP(x)               (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_LPM_REWP_SHIFT)) & USB_DEVCMDSTAT_LPM_REWP_MASK)
#define USB_DEVCMDSTAT_DCON_C_MASK               (0x1000000U)
#define USB_DEVCMDSTAT_DCON_C_SHIFT              (24U)
/*! DCON_C - Device status - connect change. The Connect Change bit is set when the device's pull-up
 *    resistor is disconnected because VBus disappeared. The bit is reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DCON_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DCON_C_SHIFT)) & USB_DEVCMDSTAT_DCON_C_MASK)
#define USB_DEVCMDSTAT_DSUS_C_MASK               (0x2000000U)
#define USB_DEVCMDSTAT_DSUS_C_SHIFT              (25U)
/*! DSUS_C - Device status - suspend change. The suspend change bit is set to 1 when the suspend bit
 *    toggles. The suspend bit can toggle because: - The device goes in the suspended state - The
 *    device is disconnected - The device receives resume signaling on its upstream port. The bit is
 *    reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DSUS_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DSUS_C_SHIFT)) & USB_DEVCMDSTAT_DSUS_C_MASK)
#define USB_DEVCMDSTAT_DRES_C_MASK               (0x4000000U)
#define USB_DEVCMDSTAT_DRES_C_SHIFT              (26U)
/*! DRES_C - Device status - reset change. This bit is set when the device received a bus reset. On
 *    a bus reset the device will automatically go to the default state (unconfigured and responding
 *    to address 0). The bit is reset by writing a one to it.
 */
#define USB_DEVCMDSTAT_DRES_C(x)                 (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_DRES_C_SHIFT)) & USB_DEVCMDSTAT_DRES_C_MASK)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK        (0x10000000U)
#define USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT       (28U)
/*! VBUSDEBOUNCED - This bit indicates if Vbus is detected or not. The bit raises immediately when
 *    Vbus becomes high. It drops to zero if Vbus is low for at least 3 ms. If this bit is high and
 *    the DCon bit is set, the HW will enable the pull-up resistor to signal a connect.
 */
#define USB_DEVCMDSTAT_VBUSDEBOUNCED(x)          (((uint32_t)(((uint32_t)(x)) << USB_DEVCMDSTAT_VBUSDEBOUNCED_SHIFT)) & USB_DEVCMDSTAT_VBUSDEBOUNCED_MASK)
/*! @} */

/*! @name INFO - USB Info register */
/*! @{ */
#define USB_INFO_FRAME_NR_MASK                   (0x7FFU)
#define USB_INFO_FRAME_NR_SHIFT                  (0U)
/*! FRAME_NR - Frame number. This contains the frame number of the last successfully received SOF.
 *    In case no SOF was received by the device at the beginning of a frame, the frame number
 *    returned is that of the last successfully received SOF. In case the SOF frame number contained a CRC
 *    error, the frame number returned will be the corrupted frame number as received by the device.
 */
#define USB_INFO_FRAME_NR(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_FRAME_NR_SHIFT)) & USB_INFO_FRAME_NR_MASK)
#define USB_INFO_ERR_CODE_MASK                   (0x7800U)
#define USB_INFO_ERR_CODE_SHIFT                  (11U)
/*! ERR_CODE - The error code which last occurred:
 *  0b0000..No error
 *  0b0001..PID encoding error
 *  0b0010..PID unknown
 *  0b0011..Packet unexpected
 *  0b0100..Token CRC error
 *  0b0101..Data CRC error
 *  0b0110..Time out
 *  0b0111..Babble
 *  0b1000..Truncated EOP
 *  0b1001..Sent/Received NAK
 *  0b1010..Sent Stall
 *  0b1011..Overrun
 *  0b1100..Sent empty packet
 *  0b1101..Bitstuff error
 *  0b1110..Sync error
 *  0b1111..Wrong data toggle
 */
#define USB_INFO_ERR_CODE(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INFO_ERR_CODE_SHIFT)) & USB_INFO_ERR_CODE_MASK)
/*! @} */

/*! @name EPLISTSTART - USB EP Command/Status List start address */
/*! @{ */
#define USB_EPLISTSTART_EP_LIST_MASK             (0xFFFFFF00U)
#define USB_EPLISTSTART_EP_LIST_SHIFT            (8U)
/*! EP_LIST - Start address of the USB EP Command/Status List.
 */
#define USB_EPLISTSTART_EP_LIST(x)               (((uint32_t)(((uint32_t)(x)) << USB_EPLISTSTART_EP_LIST_SHIFT)) & USB_EPLISTSTART_EP_LIST_MASK)
/*! @} */

/*! @name DATABUFSTART - USB Data buffer start address */
/*! @{ */
#define USB_DATABUFSTART_DA_BUF_MASK             (0xFFC00000U)
#define USB_DATABUFSTART_DA_BUF_SHIFT            (22U)
/*! DA_BUF - Start address of the buffer pointer page where all endpoint data buffers are located.
 */
#define USB_DATABUFSTART_DA_BUF(x)               (((uint32_t)(((uint32_t)(x)) << USB_DATABUFSTART_DA_BUF_SHIFT)) & USB_DATABUFSTART_DA_BUF_MASK)
/*! @} */

/*! @name LPM - USB Link Power Management register */
/*! @{ */
#define USB_LPM_HIRD_HW_MASK                     (0xFU)
#define USB_LPM_HIRD_HW_SHIFT                    (0U)
/*! HIRD_HW - Host Initiated Resume Duration - HW. This is the HIRD value from the last received LPM token
 */
#define USB_LPM_HIRD_HW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_HW_SHIFT)) & USB_LPM_HIRD_HW_MASK)
#define USB_LPM_HIRD_SW_MASK                     (0xF0U)
#define USB_LPM_HIRD_SW_SHIFT                    (4U)
/*! HIRD_SW - Host Initiated Resume Duration - SW. This is the time duration required by the USB
 *    device system to come out of LPM initiated suspend after receiving the host initiated LPM resume.
 */
#define USB_LPM_HIRD_SW(x)                       (((uint32_t)(((uint32_t)(x)) << USB_LPM_HIRD_SW_SHIFT)) & USB_LPM_HIRD_SW_MASK)
#define USB_LPM_DATA_PENDING_MASK                (0x100U)
#define USB_LPM_DATA_PENDING_SHIFT               (8U)
/*! DATA_PENDING - As long as this bit is set to one and LPM supported bit is set to one, HW will
 *    return a NYET handshake on every LPM token it receives. If LPM supported bit is set to one and
 *    this bit is zero, HW will return an ACK handshake on every LPM token it receives. If SW has
 *    still data pending and LPM is supported, it must set this bit to 1.
 */
#define USB_LPM_DATA_PENDING(x)                  (((uint32_t)(((uint32_t)(x)) << USB_LPM_DATA_PENDING_SHIFT)) & USB_LPM_DATA_PENDING_MASK)
/*! @} */

/*! @name EPSKIP - USB Endpoint skip */
/*! @{ */
#define USB_EPSKIP_SKIP_MASK                     (0x3FFFFFFFU)
#define USB_EPSKIP_SKIP_SHIFT                    (0U)
/*! SKIP - Endpoint skip: Writing 1 to one of these bits, will indicate to HW that it must
 *    deactivate the buffer assigned to this endpoint and return control back to software. When HW has
 *    deactivated the endpoint, it will clear this bit, but it will not modify the EPINUSE bit. An
 *    interrupt will be generated when the Active bit goes from 1 to 0. Note: In case of double-buffering,
 *    HW will only clear the Active bit of the buffer indicated by the EPINUSE bit.
 */
#define USB_EPSKIP_SKIP(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPSKIP_SKIP_SHIFT)) & USB_EPSKIP_SKIP_MASK)
/*! @} */

/*! @name EPINUSE - USB Endpoint Buffer in use */
/*! @{ */
#define USB_EPINUSE_BUF_MASK                     (0x3FCU)
#define USB_EPINUSE_BUF_SHIFT                    (2U)
/*! BUF - Buffer in use: This register has one bit per physical endpoint. 0: HW is accessing buffer
 *    0. 1: HW is accessing buffer 1.
 */
#define USB_EPINUSE_BUF(x)                       (((uint32_t)(((uint32_t)(x)) << USB_EPINUSE_BUF_SHIFT)) & USB_EPINUSE_BUF_MASK)
/*! @} */

/*! @name EPBUFCFG - USB Endpoint Buffer Configuration register */
/*! @{ */
#define USB_EPBUFCFG_BUF_SB_MASK                 (0x3FCU)
#define USB_EPBUFCFG_BUF_SB_SHIFT                (2U)
/*! BUF_SB - Buffer usage: This register has one bit per physical endpoint. 0: Single-buffer. 1:
 *    Double-buffer. If the bit is set to single-buffer (0), it will not toggle the corresponding
 *    EPINUSE bit when it clears the active bit. If the bit is set to double-buffer (1), HW will toggle
 *    the EPINUSE bit when it clears the Active bit for the buffer.
 */
#define USB_EPBUFCFG_BUF_SB(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPBUFCFG_BUF_SB_SHIFT)) & USB_EPBUFCFG_BUF_SB_MASK)
/*! @} */

/*! @name INTSTAT - USB interrupt status register */
/*! @{ */
#define USB_INTSTAT_EP0OUT_MASK                  (0x1U)
#define USB_INTSTAT_EP0OUT_SHIFT                 (0U)
/*! EP0OUT - Interrupt status register bit for the Control EP0 OUT direction. This bit will be set
 *    if NBytes transitions to zero or the skip bit is set by software or a SETUP packet is
 *    successfully received for the control EP0. If the IntOnNAK_CO is set, this bit will also be set when a
 *    NAK is transmitted for the Control EP0 OUT direction. Software can clear this bit by writing a
 *    one to it.
 */
#define USB_INTSTAT_EP0OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0OUT_SHIFT)) & USB_INTSTAT_EP0OUT_MASK)
#define USB_INTSTAT_EP0IN_MASK                   (0x2U)
#define USB_INTSTAT_EP0IN_SHIFT                  (1U)
/*! EP0IN - Interrupt status register bit for the Control EP0 IN direction. This bit will be set if
 *    NBytes transitions to zero or the skip bit is set by software. If the IntOnNAK_CI is set, this
 *    bit will also be set when a NAK is transmitted for the Control EP0 IN direction. Software can
 *    clear this bit by writing a one to it.
 */
#define USB_INTSTAT_EP0IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP0IN_SHIFT)) & USB_INTSTAT_EP0IN_MASK)
#define USB_INTSTAT_EP1OUT_MASK                  (0x4U)
#define USB_INTSTAT_EP1OUT_SHIFT                 (2U)
/*! EP1OUT - Interrupt status register bit for the EP1 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP1 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP1OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1OUT_SHIFT)) & USB_INTSTAT_EP1OUT_MASK)
#define USB_INTSTAT_EP1IN_MASK                   (0x8U)
#define USB_INTSTAT_EP1IN_SHIFT                  (3U)
/*! EP1IN - Interrupt status register bit for the EP1 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP1 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP1IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP1IN_SHIFT)) & USB_INTSTAT_EP1IN_MASK)
#define USB_INTSTAT_EP2OUT_MASK                  (0x10U)
#define USB_INTSTAT_EP2OUT_SHIFT                 (4U)
/*! EP2OUT - Interrupt status register bit for the EP2 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP2 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP2OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2OUT_SHIFT)) & USB_INTSTAT_EP2OUT_MASK)
#define USB_INTSTAT_EP2IN_MASK                   (0x20U)
#define USB_INTSTAT_EP2IN_SHIFT                  (5U)
/*! EP2IN - Interrupt status register bit for the EP2 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP2 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP2IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP2IN_SHIFT)) & USB_INTSTAT_EP2IN_MASK)
#define USB_INTSTAT_EP3OUT_MASK                  (0x40U)
#define USB_INTSTAT_EP3OUT_SHIFT                 (6U)
/*! EP3OUT - Interrupt status register bit for the EP3 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP3 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP3OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3OUT_SHIFT)) & USB_INTSTAT_EP3OUT_MASK)
#define USB_INTSTAT_EP3IN_MASK                   (0x80U)
#define USB_INTSTAT_EP3IN_SHIFT                  (7U)
/*! EP3IN - Interrupt status register bit for the EP3 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP3 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP3IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP3IN_SHIFT)) & USB_INTSTAT_EP3IN_MASK)
#define USB_INTSTAT_EP4OUT_MASK                  (0x100U)
#define USB_INTSTAT_EP4OUT_SHIFT                 (8U)
/*! EP4OUT - Interrupt status register bit for the EP4 OUT direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes
 *    transitions to zero or the skip bit is set by software. If the IntOnNAK_AO is set, this bit will also be
 *    set when a NAK is transmitted for the EP4 OUT direction. Software can clear this bit by
 *    writing a one to it.
 */
#define USB_INTSTAT_EP4OUT(x)                    (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4OUT_SHIFT)) & USB_INTSTAT_EP4OUT_MASK)
#define USB_INTSTAT_EP4IN_MASK                   (0x200U)
#define USB_INTSTAT_EP4IN_SHIFT                  (9U)
/*! EP4IN - Interrupt status register bit for the EP4 IN direction. This bit will be set if the
 *    corresponding Active bit is cleared by HW. This is done in case the programmed NBytes transitions
 *    to zero or the skip bit is set by software. If the IntOnNAK_AI is set, this bit will also be
 *    set when a NAK is transmitted for the EP4 IN direction. Software can clear this bit by writing
 *    a one to it.
 */
#define USB_INTSTAT_EP4IN(x)                     (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_EP4IN_SHIFT)) & USB_INTSTAT_EP4IN_MASK)
#define USB_INTSTAT_FRAME_INT_MASK               (0x40000000U)
#define USB_INTSTAT_FRAME_INT_SHIFT              (30U)
/*! FRAME_INT - Frame interrupt. This bit is set to one every millisecond when the VbusDebounced bit
 *    and the DCON bit are set. This bit can be used by software when handling isochronous
 *    endpoints. Software can clear this bit by writing a one to it.
 */
#define USB_INTSTAT_FRAME_INT(x)                 (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_FRAME_INT_SHIFT)) & USB_INTSTAT_FRAME_INT_MASK)
#define USB_INTSTAT_DEV_INT_MASK                 (0x80000000U)
#define USB_INTSTAT_DEV_INT_SHIFT                (31U)
/*! DEV_INT - Device status interrupt. This bit is set by HW when one of the bits in the Device
 *    Status Change register are set. Software can clear this bit by writing a one to it.
 */
#define USB_INTSTAT_DEV_INT(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTSTAT_DEV_INT_SHIFT)) & USB_INTSTAT_DEV_INT_MASK)
/*! @} */

/*! @name INTEN - USB interrupt enable register */
/*! @{ */
#define USB_INTEN_EP_INT_EN_MASK                 (0x3FFU)
#define USB_INTEN_EP_INT_EN_SHIFT                (0U)
/*! EP_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing
 *    bit.
 */
#define USB_INTEN_EP_INT_EN(x)                   (((uint32_t)(((uint32_t)(x)) << USB_INTEN_EP_INT_EN_SHIFT)) & USB_INTEN_EP_INT_EN_MASK)
#define USB_INTEN_FRAME_INT_EN_MASK              (0x40000000U)
#define USB_INTEN_FRAME_INT_EN_SHIFT             (30U)
/*! FRAME_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt
 *    routing bit.
 */
#define USB_INTEN_FRAME_INT_EN(x)                (((uint32_t)(((uint32_t)(x)) << USB_INTEN_FRAME_INT_EN_SHIFT)) & USB_INTEN_FRAME_INT_EN_MASK)
#define USB_INTEN_DEV_INT_EN_MASK                (0x80000000U)
#define USB_INTEN_DEV_INT_EN_SHIFT               (31U)
/*! DEV_INT_EN - If this bit is set and the corresponding USB interrupt status bit is set, a HW
 *    interrupt is generated on the interrupt line indicated by the corresponding USB interrupt routing
 *    bit.
 */
#define USB_INTEN_DEV_INT_EN(x)                  (((uint32_t)(((uint32_t)(x)) << USB_INTEN_DEV_INT_EN_SHIFT)) & USB_INTEN_DEV_INT_EN_MASK)
/*! @} */

/*! @name INTSETSTAT - USB set interrupt status register */
/*! @{ */
#define USB_INTSETSTAT_EP_SET_INT_MASK           (0x3FFU)
#define USB_INTSETSTAT_EP_SET_INT_SHIFT          (0U)
/*! EP_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status register
 *    is returned.
 */
#define USB_INTSETSTAT_EP_SET_INT(x)             (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_EP_SET_INT_SHIFT)) & USB_INTSETSTAT_EP_SET_INT_MASK)
#define USB_INTSETSTAT_FRAME_SET_INT_MASK        (0x40000000U)
#define USB_INTSETSTAT_FRAME_SET_INT_SHIFT       (30U)
/*! FRAME_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status
 *    register is returned.
 */
#define USB_INTSETSTAT_FRAME_SET_INT(x)          (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_FRAME_SET_INT_SHIFT)) & USB_INTSETSTAT_FRAME_SET_INT_MASK)
#define USB_INTSETSTAT_DEV_SET_INT_MASK          (0x80000000U)
#define USB_INTSETSTAT_DEV_SET_INT_SHIFT         (31U)
/*! DEV_SET_INT - If software writes a one to one of these bits, the corresponding USB interrupt
 *    status bit is set. When this register is read, the same value as the USB interrupt status
 *    register is returned.
 */
#define USB_INTSETSTAT_DEV_SET_INT(x)            (((uint32_t)(((uint32_t)(x)) << USB_INTSETSTAT_DEV_SET_INT_SHIFT)) & USB_INTSETSTAT_DEV_SET_INT_MASK)
/*! @} */

/*! @name EPTOGGLE - USB Endpoint toggle register */
/*! @{ */
#define USB_EPTOGGLE_TOGGLE_MASK                 (0x3FFU)
#define USB_EPTOGGLE_TOGGLE_SHIFT                (0U)
/*! TOGGLE - Endpoint data toggle: This field indicates the current value of the data toggle for the corresponding endpoint.
 */
#define USB_EPTOGGLE_TOGGLE(x)                   (((uint32_t)(((uint32_t)(x)) << USB_EPTOGGLE_TOGGLE_SHIFT)) & USB_EPTOGGLE_TOGGLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group USB_Register_Masks */


/* USB - Peripheral instance base addresses */
/** Peripheral USB0 base address */
#define USB0_BASE                                (0x40084000u)
/** Peripheral USB0 base pointer */
#define USB0                                     ((USB_Type *)USB0_BASE)
/** Array initializer of USB peripheral base addresses */
#define USB_BASE_ADDRS                           { USB0_BASE }
/** Array initializer of USB peripheral base pointers */
#define USB_BASE_PTRS                            { USB0 }
/** Interrupt vectors for the USB peripheral type */
#define USB_IRQS                                 { USB0_IRQn }
#define USB_NEEDCLK_IRQS                         { USB0_NEEDCLK_IRQn }

/*!
 * @}
 */ /* end of group USB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- UTICK Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UTICK_Peripheral_Access_Layer UTICK Peripheral Access Layer
 * @{
 */

/** UTICK - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control register., offset: 0x0 */
  __IO uint32_t STAT;                              /**< Status register., offset: 0x4 */
  __IO uint32_t CFG;                               /**< Capture configuration register., offset: 0x8 */
  __O  uint32_t CAPCLR;                            /**< Capture clear register., offset: 0xC */
  __I  uint32_t CAP[4];                            /**< Capture register ., array offset: 0x10, array step: 0x4 */
} UTICK_Type;

/* ----------------------------------------------------------------------------
   -- UTICK Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UTICK_Register_Masks UTICK Register Masks
 * @{
 */

/*! @name CTRL - Control register. */
/*! @{ */
#define UTICK_CTRL_DELAYVAL_MASK                 (0x7FFFFFFFU)
#define UTICK_CTRL_DELAYVAL_SHIFT                (0U)
/*! DELAYVAL - Tick interval value. The delay will be equal to DELAYVAL + 1 periods of the timer
 *    clock. The minimum usable value is 1, for a delay of 2 timer clocks. A value of 0 stops the timer.
 */
#define UTICK_CTRL_DELAYVAL(x)                   (((uint32_t)(((uint32_t)(x)) << UTICK_CTRL_DELAYVAL_SHIFT)) & UTICK_CTRL_DELAYVAL_MASK)
#define UTICK_CTRL_REPEAT_MASK                   (0x80000000U)
#define UTICK_CTRL_REPEAT_SHIFT                  (31U)
/*! REPEAT - Repeat delay. 0 = One-time delay. 1 = Delay repeats continuously.
 */
#define UTICK_CTRL_REPEAT(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CTRL_REPEAT_SHIFT)) & UTICK_CTRL_REPEAT_MASK)
/*! @} */

/*! @name STAT - Status register. */
/*! @{ */
#define UTICK_STAT_INTR_MASK                     (0x1U)
#define UTICK_STAT_INTR_SHIFT                    (0U)
/*! INTR - Interrupt flag. 0 = No interrupt is pending. 1 = An interrupt is pending. A write of any
 *    value to this register clears this flag.
 */
#define UTICK_STAT_INTR(x)                       (((uint32_t)(((uint32_t)(x)) << UTICK_STAT_INTR_SHIFT)) & UTICK_STAT_INTR_MASK)
#define UTICK_STAT_ACTIVE_MASK                   (0x2U)
#define UTICK_STAT_ACTIVE_SHIFT                  (1U)
/*! ACTIVE - Active flag. 0 = The Micro-Tick Timer is stopped. 1 = The Micro-Tick Timer is currently active.
 */
#define UTICK_STAT_ACTIVE(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_STAT_ACTIVE_SHIFT)) & UTICK_STAT_ACTIVE_MASK)
/*! @} */

/*! @name CFG - Capture configuration register. */
/*! @{ */
#define UTICK_CFG_CAPEN0_MASK                    (0x1U)
#define UTICK_CFG_CAPEN0_SHIFT                   (0U)
/*! CAPEN0 - Enable Capture 0. 1 = Enabled, 0 = Disabled.
 */
#define UTICK_CFG_CAPEN0(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN0_SHIFT)) & UTICK_CFG_CAPEN0_MASK)
#define UTICK_CFG_CAPEN1_MASK                    (0x2U)
#define UTICK_CFG_CAPEN1_SHIFT                   (1U)
/*! CAPEN1 - Enable Capture 1. 1 = Enabled, 0 = Disabled.
 */
#define UTICK_CFG_CAPEN1(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN1_SHIFT)) & UTICK_CFG_CAPEN1_MASK)
#define UTICK_CFG_CAPEN2_MASK                    (0x4U)
#define UTICK_CFG_CAPEN2_SHIFT                   (2U)
/*! CAPEN2 - Enable Capture 2. 1 = Enabled, 0 = Disabled.
 */
#define UTICK_CFG_CAPEN2(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN2_SHIFT)) & UTICK_CFG_CAPEN2_MASK)
#define UTICK_CFG_CAPEN3_MASK                    (0x8U)
#define UTICK_CFG_CAPEN3_SHIFT                   (3U)
/*! CAPEN3 - Enable Capture 3. 1 = Enabled, 0 = Disabled.
 */
#define UTICK_CFG_CAPEN3(x)                      (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPEN3_SHIFT)) & UTICK_CFG_CAPEN3_MASK)
#define UTICK_CFG_CAPPOL0_MASK                   (0x100U)
#define UTICK_CFG_CAPPOL0_SHIFT                  (8U)
/*! CAPPOL0 - Capture Polarity 0. 0 = Positive edge capture, 1 = Negative edge capture.
 */
#define UTICK_CFG_CAPPOL0(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL0_SHIFT)) & UTICK_CFG_CAPPOL0_MASK)
#define UTICK_CFG_CAPPOL1_MASK                   (0x200U)
#define UTICK_CFG_CAPPOL1_SHIFT                  (9U)
/*! CAPPOL1 - Capture Polarity 1. 0 = Positive edge capture, 1 = Negative edge capture.
 */
#define UTICK_CFG_CAPPOL1(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL1_SHIFT)) & UTICK_CFG_CAPPOL1_MASK)
#define UTICK_CFG_CAPPOL2_MASK                   (0x400U)
#define UTICK_CFG_CAPPOL2_SHIFT                  (10U)
/*! CAPPOL2 - Capture Polarity 2. 0 = Positive edge capture, 1 = Negative edge capture.
 */
#define UTICK_CFG_CAPPOL2(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL2_SHIFT)) & UTICK_CFG_CAPPOL2_MASK)
#define UTICK_CFG_CAPPOL3_MASK                   (0x800U)
#define UTICK_CFG_CAPPOL3_SHIFT                  (11U)
/*! CAPPOL3 - Capture Polarity 3. 0 = Positive edge capture, 1 = Negative edge capture.
 */
#define UTICK_CFG_CAPPOL3(x)                     (((uint32_t)(((uint32_t)(x)) << UTICK_CFG_CAPPOL3_SHIFT)) & UTICK_CFG_CAPPOL3_MASK)
/*! @} */

/*! @name CAPCLR - Capture clear register. */
/*! @{ */
#define UTICK_CAPCLR_CAPCLR0_MASK                (0x1U)
#define UTICK_CAPCLR_CAPCLR0_SHIFT               (0U)
/*! CAPCLR0 - Clear capture 0. Writing 1 to this bit clears the CAP0 register value.
 */
#define UTICK_CAPCLR_CAPCLR0(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR0_SHIFT)) & UTICK_CAPCLR_CAPCLR0_MASK)
#define UTICK_CAPCLR_CAPCLR1_MASK                (0x2U)
#define UTICK_CAPCLR_CAPCLR1_SHIFT               (1U)
/*! CAPCLR1 - Clear capture 1. Writing 1 to this bit clears the CAP1 register value.
 */
#define UTICK_CAPCLR_CAPCLR1(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR1_SHIFT)) & UTICK_CAPCLR_CAPCLR1_MASK)
#define UTICK_CAPCLR_CAPCLR2_MASK                (0x4U)
#define UTICK_CAPCLR_CAPCLR2_SHIFT               (2U)
/*! CAPCLR2 - Clear capture 2. Writing 1 to this bit clears the CAP2 register value.
 */
#define UTICK_CAPCLR_CAPCLR2(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR2_SHIFT)) & UTICK_CAPCLR_CAPCLR2_MASK)
#define UTICK_CAPCLR_CAPCLR3_MASK                (0x8U)
#define UTICK_CAPCLR_CAPCLR3_SHIFT               (3U)
/*! CAPCLR3 - Clear capture 3. Writing 1 to this bit clears the CAP3 register value.
 */
#define UTICK_CAPCLR_CAPCLR3(x)                  (((uint32_t)(((uint32_t)(x)) << UTICK_CAPCLR_CAPCLR3_SHIFT)) & UTICK_CAPCLR_CAPCLR3_MASK)
/*! @} */

/*! @name CAP - Capture register . */
/*! @{ */
#define UTICK_CAP_CAP_VALUE_MASK                 (0x7FFFFFFFU)
#define UTICK_CAP_CAP_VALUE_SHIFT                (0U)
/*! CAP_VALUE - Capture value for the related capture event (UTICK_CAPn. Note: the value is 1 lower
 *    than the actual value of the Micro-tick Timer at the moment of the capture event.
 */
#define UTICK_CAP_CAP_VALUE(x)                   (((uint32_t)(((uint32_t)(x)) << UTICK_CAP_CAP_VALUE_SHIFT)) & UTICK_CAP_CAP_VALUE_MASK)
#define UTICK_CAP_VALID_MASK                     (0x80000000U)
#define UTICK_CAP_VALID_SHIFT                    (31U)
/*! VALID - Capture Valid. When 1, a value has been captured based on a transition of the related
 *    UTICK_CAPn pin. Cleared by writing to the related bit in the CAPCLR register.
 */
#define UTICK_CAP_VALID(x)                       (((uint32_t)(((uint32_t)(x)) << UTICK_CAP_VALID_SHIFT)) & UTICK_CAP_VALID_MASK)
/*! @} */

/* The count of UTICK_CAP */
#define UTICK_CAP_COUNT                          (4U)


/*!
 * @}
 */ /* end of group UTICK_Register_Masks */


/* UTICK - Peripheral instance base addresses */
/** Peripheral UTICK0 base address */
#define UTICK0_BASE                              (0x4000E000u)
/** Peripheral UTICK0 base pointer */
#define UTICK0                                   ((UTICK_Type *)UTICK0_BASE)
/** Array initializer of UTICK peripheral base addresses */
#define UTICK_BASE_ADDRS                         { UTICK0_BASE }
/** Array initializer of UTICK peripheral base pointers */
#define UTICK_BASE_PTRS                          { UTICK0 }
/** Interrupt vectors for the UTICK peripheral type */
#define UTICK_IRQS                               { UTICK0_IRQn }

/*!
 * @}
 */ /* end of group UTICK_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WWDT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WWDT_Peripheral_Access_Layer WWDT Peripheral Access Layer
 * @{
 */

/** WWDT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MOD;                               /**< Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer., offset: 0x0 */
  __IO uint32_t TC;                                /**< Watchdog timer constant register. This 24-bit register determines the time-out value., offset: 0x4 */
  __O  uint32_t FEED;                              /**< Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in TC., offset: 0x8 */
  __I  uint32_t TV;                                /**< Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer., offset: 0xC */
       uint8_t RESERVED_0[4];
  __IO uint32_t WARNINT;                           /**< Watchdog Warning Interrupt compare value., offset: 0x14 */
  __IO uint32_t WINDOW;                            /**< Watchdog Window compare value., offset: 0x18 */
} WWDT_Type;

/* ----------------------------------------------------------------------------
   -- WWDT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WWDT_Register_Masks WWDT Register Masks
 * @{
 */

/*! @name MOD - Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
/*! @{ */
#define WWDT_MOD_WDEN_MASK                       (0x1U)
#define WWDT_MOD_WDEN_SHIFT                      (0U)
/*! WDEN - Watchdog enable bit. Once this bit is set to one and a watchdog feed is performed, the
 *    watchdog timer will run permanently.
 *  0b0..Stop. The watchdog timer is stopped.
 *  0b1..Run. The watchdog timer is running.
 */
#define WWDT_MOD_WDEN(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDEN_SHIFT)) & WWDT_MOD_WDEN_MASK)
#define WWDT_MOD_WDRESET_MASK                    (0x2U)
#define WWDT_MOD_WDRESET_SHIFT                   (1U)
/*! WDRESET - Watchdog reset enable bit. Once this bit has been written with a 1 it cannot be re-written with a 0.
 *  0b0..Interrupt. A watchdog time-out will not cause a chip reset.
 *  0b1..Reset. A watchdog time-out will cause a chip reset.
 */
#define WWDT_MOD_WDRESET(x)                      (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDRESET_SHIFT)) & WWDT_MOD_WDRESET_MASK)
#define WWDT_MOD_WDTOF_MASK                      (0x4U)
#define WWDT_MOD_WDTOF_SHIFT                     (2U)
/*! WDTOF - Watchdog time-out flag. Set when the watchdog timer times out, by a feed error, or by
 *    events associated with WDPROTECT. Cleared by software writing a 0 to this bit position. Causes a
 *    chip reset if WDRESET = 1.
 */
#define WWDT_MOD_WDTOF(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDTOF_SHIFT)) & WWDT_MOD_WDTOF_MASK)
#define WWDT_MOD_WDINT_MASK                      (0x8U)
#define WWDT_MOD_WDINT_SHIFT                     (3U)
/*! WDINT - Warning interrupt flag. Set when the timer is at or below the value in WDWARNINT.
 *    Cleared by software writing a 1 to this bit position. Note that this bit cannot be cleared while the
 *    WARNINT value is equal to the value of the TV register. This can occur if the value of
 *    WARNINT is 0 and the WDRESET bit is 0 when TV decrements to 0.
 */
#define WWDT_MOD_WDINT(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDINT_SHIFT)) & WWDT_MOD_WDINT_MASK)
#define WWDT_MOD_WDPROTECT_MASK                  (0x10U)
#define WWDT_MOD_WDPROTECT_SHIFT                 (4U)
/*! WDPROTECT - Watchdog update mode. This bit can be set once by software and is only cleared by a reset.
 *  0b0..Flexible. The watchdog time-out value (TC) can be changed at any time.
 *  0b1..Threshold. The watchdog time-out value (TC) can be changed only after the counter is below the value of WDWARNINT and WDWINDOW.
 */
#define WWDT_MOD_WDPROTECT(x)                    (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_WDPROTECT_SHIFT)) & WWDT_MOD_WDPROTECT_MASK)
#define WWDT_MOD_LOCK_MASK                       (0x20U)
#define WWDT_MOD_LOCK_SHIFT                      (5U)
/*! LOCK - Once this bit is set to one and a watchdog feed is performed, disabling or powering down
 *    the watchdog oscillator is prevented by hardware. This bit can be set once by software and is
 *    only cleared by any reset.
 */
#define WWDT_MOD_LOCK(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_MOD_LOCK_SHIFT)) & WWDT_MOD_LOCK_MASK)
/*! @} */

/*! @name TC - Watchdog timer constant register. This 24-bit register determines the time-out value. */
/*! @{ */
#define WWDT_TC_COUNT_MASK                       (0xFFFFFFU)
#define WWDT_TC_COUNT_SHIFT                      (0U)
/*! COUNT - Watchdog time-out value.
 */
#define WWDT_TC_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TC_COUNT_SHIFT)) & WWDT_TC_COUNT_MASK)
/*! @} */

/*! @name FEED - Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in TC. */
/*! @{ */
#define WWDT_FEED_FEED_MASK                      (0xFFU)
#define WWDT_FEED_FEED_SHIFT                     (0U)
/*! FEED - Feed value should be 0xAA followed by 0x55.
 */
#define WWDT_FEED_FEED(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_FEED_FEED_SHIFT)) & WWDT_FEED_FEED_MASK)
/*! @} */

/*! @name TV - Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer. */
/*! @{ */
#define WWDT_TV_COUNT_MASK                       (0xFFFFFFU)
#define WWDT_TV_COUNT_SHIFT                      (0U)
/*! COUNT - Counter timer value.
 */
#define WWDT_TV_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TV_COUNT_SHIFT)) & WWDT_TV_COUNT_MASK)
/*! @} */

/*! @name WARNINT - Watchdog Warning Interrupt compare value. */
/*! @{ */
#define WWDT_WARNINT_WARNINT_MASK                (0x3FFU)
#define WWDT_WARNINT_WARNINT_SHIFT               (0U)
/*! WARNINT - Watchdog warning interrupt compare value.
 */
#define WWDT_WARNINT_WARNINT(x)                  (((uint32_t)(((uint32_t)(x)) << WWDT_WARNINT_WARNINT_SHIFT)) & WWDT_WARNINT_WARNINT_MASK)
/*! @} */

/*! @name WINDOW - Watchdog Window compare value. */
/*! @{ */
#define WWDT_WINDOW_WINDOW_MASK                  (0xFFFFFFU)
#define WWDT_WINDOW_WINDOW_SHIFT                 (0U)
/*! WINDOW - Watchdog window value.
 */
#define WWDT_WINDOW_WINDOW(x)                    (((uint32_t)(((uint32_t)(x)) << WWDT_WINDOW_WINDOW_SHIFT)) & WWDT_WINDOW_WINDOW_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group WWDT_Register_Masks */


/* WWDT - Peripheral instance base addresses */
/** Peripheral WWDT base address */
#define WWDT_BASE                                (0x4000C000u)
/** Peripheral WWDT base pointer */
#define WWDT                                     ((WWDT_Type *)WWDT_BASE)
/** Array initializer of WWDT peripheral base addresses */
#define WWDT_BASE_ADDRS                          { WWDT_BASE }
/** Array initializer of WWDT peripheral base pointers */
#define WWDT_BASE_PTRS                           { WWDT }
/** Interrupt vectors for the WWDT peripheral type */
#define WWDT_IRQS                                { WDT_BOD_IRQn }

/*!
 * @}
 */ /* end of group WWDT_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


/* ----------------------------------------------------------------------------
   -- Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Bit_Field_Generic_Macros Macros for use with bit field definitions (xxx_SHIFT, xxx_MASK).
 * @{
 */

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang system_header
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma system_include
#endif

/**
 * @brief Mask and left-shift a bit field value for use in a register bit range.
 * @param field Name of the register bit field.
 * @param value Value of the bit field.
 * @return Masked and shifted value.
 */
#define NXP_VAL2FLD(field, value)    (((value) << (field ## _SHIFT)) & (field ## _MASK))
/**
 * @brief Mask and right-shift a register value to extract a bit field value.
 * @param field Name of the register bit field.
 * @param value Value of the register.
 * @return Masked and shifted bit field value.
 */
#define NXP_FLD2VAL(field, value)    (((value) & (field ## _MASK)) >> (field ## _SHIFT))

/*!
 * @}
 */ /* end of group Bit_Field_Generic_Macros */


/* ----------------------------------------------------------------------------
   -- SDK Compatibility
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SDK_Compatibility_Symbols SDK Compatibility
 * @{
 */

/* No SDK compatibility issues. */

/*!
 * @}
 */ /* end of group SDK_Compatibility_Symbols */


#endif  /* _LPC51U68_H_ */

