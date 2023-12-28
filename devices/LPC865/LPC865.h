/*
** ###################################################################
**     Processors:          LPC865M201JBD64
**                          LPC865M201JHI33
**                          LPC865M201JHI48
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC86x User manual Rev.1  March 2022
**     Version:             rev. 1.0, 2022-03-15
**     Build:               b230313
**
**     Abstract:
**         CMSIS Peripheral Access Layer for LPC865
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
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

/*!
 * @file LPC865.h
 * @version 1.0
 * @date 2022-03-15
 * @brief CMSIS Peripheral Access Layer for LPC865
 *
 * CMSIS Peripheral Access Layer for LPC865
 */

#ifndef _LPC865_H_
#define _LPC865_H_                               /**< Symbol preventing repeated inclusion */

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
  SPI0_IRQn                    = 0,                /**< SPI0 interrupt */
  SPI1_IRQn                    = 1,                /**< SPI1 interrupt */
  Reserved18_IRQn              = 2,                /**< Reserved interrupt */
  USART0_IRQn                  = 3,                /**< USART0 interrupt */
  USART1_IRQn                  = 4,                /**< USART1 interrupt */
  USART2_IRQn                  = 5,                /**< USART2 interrupt */
  FTM0_IRQn                    = 6,                /**< FlexTimer0 interrupt */
  FTM1_IRQn                    = 7,                /**< FlexTimer1 interrupt */
  I2C0_IRQn                    = 8,                /**< I2C0 interrupt */
  Reserved25_IRQn              = 9,                /**< Reserved interrupt */
  MRT0_IRQn                    = 10,               /**< Multi-rate timer interrupt */
  ACMP_IRQn                    = 11,               /**< Analog comparator interrupt */
  WDT_IRQn                     = 12,               /**< Windowed watchdog timer interrupt */
  BOD_IRQn                     = 13,               /**< BOD interrupts */
  FLASH_IRQn                   = 14,               /**< flash interrupt */
  WKT_IRQn                     = 15,               /**< Self-wake-up timer interrupt */
  ADC0_SEQA_IRQn               = 16,               /**< ADC0 sequence A completion. */
  ADC0_SEQB_IRQn               = 17,               /**< ADC0 sequence B completion. */
  ADC0_THCMP_IRQn              = 18,               /**< ADC0 threshold compare and error. */
  ADC0_OVR_IRQn                = 19,               /**< ADC0 overrun */
  DMA0_IRQn                    = 20,               /**< DMA0 interrupt */
  I3C0_IRQn                    = 21,               /**< I3C0 interrupt */
  GPIO_HS_IRQ0_IRQn            = 22,               /**< GPIO group A interrupt */
  GPIO_HS_IRQ1_IRQn            = 23,               /**< GPIO group B interrupt */
  PIN_INT0_IRQn                = 24,               /**< Pin interrupt 0 or pattern match engine slice 0 interrupt */
  PIN_INT1_IRQn                = 25,               /**< Pin interrupt 1 or pattern match engine slice 1 interrupt */
  PIN_INT2_IRQn                = 26,               /**< Pin interrupt 2 or pattern match engine slice 2 interrupt */
  PIN_INT3_IRQn                = 27,               /**< Pin interrupt 3 or pattern match engine slice 3 interrupt */
  PIN_INT4_IRQn                = 28,               /**< Pin interrupt 4 or pattern match engine slice 4 interrupt */
  PIN_INT5_IRQn                = 29,               /**< Pin interrupt 5 or pattern match engine slice 5 interrupt */
  PIN_INT6_IRQn                = 30,               /**< Pin interrupt 6 or pattern match engine slice 6 interrupt */
  PIN_INT7_IRQn                = 31                /**< Pin interrupt 7 or pattern match engine slice 7 interrupt */
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
#include "system_LPC865.h"             /* Device specific configuration file */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


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
   -- ACOMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACOMP_Peripheral_Access_Layer ACOMP Peripheral Access Layer
 * @{
 */

/** ACOMP - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Comparator control register, offset: 0x0 */
  __IO uint32_t LAD;                               /**< Voltage ladder register, offset: 0x4 */
} ACOMP_Type;

/* ----------------------------------------------------------------------------
   -- ACOMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ACOMP_Register_Masks ACOMP Register Masks
 * @{
 */

/*! @name CTRL - Comparator control register */
/*! @{ */

#define ACOMP_CTRL_EDGESEL_MASK                  (0x18U)
#define ACOMP_CTRL_EDGESEL_SHIFT                 (3U)
/*! EDGESEL - This field controls which edges on the comparator output set the COMPEDGE bit (bit 23 below):
 *  0b00..Falling edges
 *  0b01..Rising edges
 *  0b10..Both edges
 *  0b11..Both edges
 */
#define ACOMP_CTRL_EDGESEL(x)                    (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_EDGESEL_SHIFT)) & ACOMP_CTRL_EDGESEL_MASK)

#define ACOMP_CTRL_COMPSA_MASK                   (0x40U)
#define ACOMP_CTRL_COMPSA_SHIFT                  (6U)
/*! COMPSA - Comparator output control
 *  0b0..Comparator output is used directly.
 *  0b1..Comparator output is synchronized to the bus clock for output to other modules.
 */
#define ACOMP_CTRL_COMPSA(x)                     (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_COMPSA_SHIFT)) & ACOMP_CTRL_COMPSA_MASK)

#define ACOMP_CTRL_COMP_VP_SEL_MASK              (0x700U)
#define ACOMP_CTRL_COMP_VP_SEL_SHIFT             (8U)
/*! COMP_VP_SEL - Selects positive voltage input
 *  0b000..VOLTAGE_LADDER_OUTPUT
 *  0b001..ACMP_I1
 *  0b010..ACMP_I2
 *  0b011..ACMP_I3
 *  0b100..ACMP_I4
 *  0b101..ACMP_I5
 *  0b110..Band gap. Internal reference voltage.
 *  0b111..None
 */
#define ACOMP_CTRL_COMP_VP_SEL(x)                (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_COMP_VP_SEL_SHIFT)) & ACOMP_CTRL_COMP_VP_SEL_MASK)

#define ACOMP_CTRL_COMP_VM_SEL_MASK              (0x3800U)
#define ACOMP_CTRL_COMP_VM_SEL_SHIFT             (11U)
/*! COMP_VM_SEL - Selects negative voltage input
 *  0b000..VOLTAGE_LADDER_OUTPUT
 *  0b001..ACMP_I1
 *  0b010..ACMP_I2
 *  0b011..ACMP_I3
 *  0b100..ACMP_I4
 *  0b101..ACMP_I5
 *  0b110..Band gap. Internal reference voltage.
 *  0b111..None
 */
#define ACOMP_CTRL_COMP_VM_SEL(x)                (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_COMP_VM_SEL_SHIFT)) & ACOMP_CTRL_COMP_VM_SEL_MASK)

#define ACOMP_CTRL_EDGECLR_MASK                  (0x100000U)
#define ACOMP_CTRL_EDGECLR_SHIFT                 (20U)
/*! EDGECLR - Interrupt clear bit. To clear the COMPEDGE bit and thus negate the interrupt request,
 *    toggle the EDGECLR bit by first writing a 1 and then a 0.
 */
#define ACOMP_CTRL_EDGECLR(x)                    (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_EDGECLR_SHIFT)) & ACOMP_CTRL_EDGECLR_MASK)

#define ACOMP_CTRL_COMPSTAT_MASK                 (0x200000U)
#define ACOMP_CTRL_COMPSTAT_SHIFT                (21U)
/*! COMPSTAT - Comparator status. This bit reflects the state of the comparator output. */
#define ACOMP_CTRL_COMPSTAT(x)                   (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_COMPSTAT_SHIFT)) & ACOMP_CTRL_COMPSTAT_MASK)

#define ACOMP_CTRL_COMPEDGE_MASK                 (0x800000U)
#define ACOMP_CTRL_COMPEDGE_SHIFT                (23U)
/*! COMPEDGE - Comparator edge-detect status. */
#define ACOMP_CTRL_COMPEDGE(x)                   (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_COMPEDGE_SHIFT)) & ACOMP_CTRL_COMPEDGE_MASK)

#define ACOMP_CTRL_INTENA_MASK                   (0x1000000U)
#define ACOMP_CTRL_INTENA_SHIFT                  (24U)
/*! INTENA - Must be set to generate interrupts. */
#define ACOMP_CTRL_INTENA(x)                     (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_INTENA_SHIFT)) & ACOMP_CTRL_INTENA_MASK)

#define ACOMP_CTRL_HYS_MASK                      (0x6000000U)
#define ACOMP_CTRL_HYS_SHIFT                     (25U)
/*! HYS - Controls the hysteresis of the comparator. When the comparator is outputting a certain
 *    state, this is the difference between the selected signals, in the opposite direction from the
 *    state being output, that will switch the output.
 *  0b00..None (the output will switch as the voltages cross)
 *  0b01..5 mv
 *  0b10..10 mv
 *  0b11..20 mv
 */
#define ACOMP_CTRL_HYS(x)                        (((uint32_t)(((uint32_t)(x)) << ACOMP_CTRL_HYS_SHIFT)) & ACOMP_CTRL_HYS_MASK)
/*! @} */

/*! @name LAD - Voltage ladder register */
/*! @{ */

#define ACOMP_LAD_LADEN_MASK                     (0x1U)
#define ACOMP_LAD_LADEN_SHIFT                    (0U)
/*! LADEN - Voltage ladder enable */
#define ACOMP_LAD_LADEN(x)                       (((uint32_t)(((uint32_t)(x)) << ACOMP_LAD_LADEN_SHIFT)) & ACOMP_LAD_LADEN_MASK)

#define ACOMP_LAD_LADSEL_MASK                    (0x3EU)
#define ACOMP_LAD_LADSEL_SHIFT                   (1U)
/*! LADSEL - Voltage ladder value. The reference voltage Vref depends on the LADREF bit below. 00000
 *    = VSS 00001 = 1 x Vref/31 00010 = 2 x Vref/31 ... 11111 = Vref
 */
#define ACOMP_LAD_LADSEL(x)                      (((uint32_t)(((uint32_t)(x)) << ACOMP_LAD_LADSEL_SHIFT)) & ACOMP_LAD_LADSEL_MASK)

#define ACOMP_LAD_LADREF_MASK                    (0x40U)
#define ACOMP_LAD_LADREF_SHIFT                   (6U)
/*! LADREF - Selects the reference voltage Vref for the voltage ladder.
 *  0b0..Supply pin VDD
 *  0b1..VDDCMP pin
 */
#define ACOMP_LAD_LADREF(x)                      (((uint32_t)(((uint32_t)(x)) << ACOMP_LAD_LADREF_SHIFT)) & ACOMP_LAD_LADREF_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ACOMP_Register_Masks */


/* ACOMP - Peripheral instance base addresses */
/** Peripheral ACOMP base address */
#define ACOMP_BASE                               (0x40024000u)
/** Peripheral ACOMP base pointer */
#define ACOMP                                    ((ACOMP_Type *)ACOMP_BASE)
/** Array initializer of ACOMP peripheral base addresses */
#define ACOMP_BASE_ADDRS                         { ACOMP_BASE }
/** Array initializer of ACOMP peripheral base pointers */
#define ACOMP_BASE_PTRS                          { ACOMP }

/*!
 * @}
 */ /* end of group ACOMP_Peripheral_Access_Layer */


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
       uint8_t RESERVED_0[4];
  __IO uint32_t SEQ_CTRL[2];                       /**< ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n., array offset: 0x8, array step: 0x4 */
  __I  uint32_t SEQ_GDAT[2];                       /**< ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n., array offset: 0x10, array step: 0x4 */
       uint8_t RESERVED_1[8];
  __I  uint32_t DAT[12];                           /**< ADC Channel N Data register. This register contains the result of the most recent conversion completed on channel N., array offset: 0x20, array step: 0x4 */
  __IO uint32_t THR0_LOW;                          /**< ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x50 */
  __IO uint32_t THR1_LOW;                          /**< ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x54 */
  __IO uint32_t THR0_HIGH;                         /**< ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x58 */
  __IO uint32_t THR1_HIGH;                         /**< ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x5C */
  __IO uint32_t CHAN_THRSEL;                       /**< ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel, offset: 0x60 */
  __IO uint32_t INTEN;                             /**< ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated., offset: 0x64 */
  __IO uint32_t FLAGS;                             /**< ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers)., offset: 0x68 */
  __IO uint32_t TRM;                               /**< ADC Startup register., offset: 0x6C */
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

#define ADC_CTRL_LPWRMODE_MASK                   (0x400U)
#define ADC_CTRL_LPWRMODE_SHIFT                  (10U)
/*! LPWRMODE - The low-power ADC mode
 *  0b0..The low-power ADC mode is disabled. The analog circuitry remains activated even when no conversions are requested.
 *  0b1..The low-power ADC mode is enabled. The analog circuitry is automatically powered-down when no conversions
 *       are taking place. When any (hardware or software) triggering event is detected, the analog circuitry is
 *       enabled. After the required start-up time, the requested conversion will be launched. Once the conversion
 *       completes, the analog-circuitry will again be powered-down provided no further conversions are pending.
 *       Using this mode can save an appreciable amount of current (approximately 2.5 mA) when conversions are
 *       required relatively infrequently. The penalty for using this mode is an approximately FIFTEEN ADC CLOCK delay (30
 *       clocks in 10-bit mode), based on the frequency specified in the CLKDIV field, from the time the trigger
 *       event occurs until sampling of the A/D input commences. Note: This mode will NOT power-up the A/D if the
 *       ADC_ENA bit is low.
 */
#define ADC_CTRL_LPWRMODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_LPWRMODE_SHIFT)) & ADC_CTRL_LPWRMODE_MASK)

#define ADC_CTRL_CALMODE_MASK                    (0x40000000U)
#define ADC_CTRL_CALMODE_SHIFT                   (30U)
/*! CALMODE - Writing a '1' to this bit will initiate a sef-calibration cycle. This bit will be
 *    automatically cleared by hardware after the calibration cycle is complete. Note: Other bits of
 *    this register may be written to concurrently with setting this bit, however once this bit has
 *    been set no further writes to this register are permitted unitl the full calibration cycle has
 *    ended.
 */
#define ADC_CTRL_CALMODE(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_CALMODE_SHIFT)) & ADC_CTRL_CALMODE_MASK)
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

#define ADC_SEQ_CTRL_TRIGGER_MASK                (0x7000U)
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

#define ADC_SEQ_CTRL_TSAMP_MASK                  (0x1F00000U)
#define ADC_SEQ_CTRL_TSAMP_SHIFT                 (20U)
/*! TSAMP - The default sample period (TSAMP = "00000") at the beginning of each new conversion is
 *    6.5 ADC clock periods. Depending on avariety of factors including ADC clock rate, output
 *    impedance of the analog source driver, ADC resolution, and the selection of channels, the sample
 *    time may need to be increased. The value programmed into the TSAMP fields dictates the number of
 *    additional ADC clock cycles (beyond 6.5) that the sample period will be extended by. Note: Any
 *    additional clocks of sample time inserted will add directly to the overall number of clocks
 *    required for a conversion, effectivelyreducing the overall conversion throughput rate.
 */
#define ADC_SEQ_CTRL_TSAMP(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TSAMP_SHIFT)) & ADC_SEQ_CTRL_TSAMP_MASK)

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

/*! @name DAT - ADC Channel N Data register. This register contains the result of the most recent conversion completed on channel N. */
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
/*! THRLOW - Low threshold value against which ADC results will be compared */
#define ADC_THR0_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR0_LOW_THRLOW_SHIFT)) & ADC_THR0_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR1_LOW - ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */

#define ADC_THR1_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR1_LOW_THRLOW_SHIFT                (4U)
/*! THRLOW - Low threshold value against which ADC results will be compared */
#define ADC_THR1_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR1_LOW_THRLOW_SHIFT)) & ADC_THR1_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR0_HIGH - ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
/*! @{ */

#define ADC_THR0_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR0_HIGH_THRHIGH_SHIFT              (4U)
/*! THRHIGH - High threshold value against which ADC results will be compared */
#define ADC_THR0_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR0_HIGH_THRHIGH_SHIFT)) & ADC_THR0_HIGH_THRHIGH_MASK)
/*! @} */

/*! @name THR1_HIGH - ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */

#define ADC_THR1_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR1_HIGH_THRHIGH_SHIFT              (4U)
/*! THRHIGH - High threshold value against which ADC results will be compared */
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
/*! CH1_THRSEL - Threshold select for channel 1. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH1_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH1_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH2_THRSEL_MASK          (0x4U)
#define ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT         (2U)
/*! CH2_THRSEL - Threshold select for channel 2. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH2_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH2_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH3_THRSEL_MASK          (0x8U)
#define ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT         (3U)
/*! CH3_THRSEL - Threshold select for channel 3. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH3_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH3_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH4_THRSEL_MASK          (0x10U)
#define ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT         (4U)
/*! CH4_THRSEL - Threshold select for channel 4. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH4_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH4_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH5_THRSEL_MASK          (0x20U)
#define ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT         (5U)
/*! CH5_THRSEL - Threshold select for channel 5. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH5_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH5_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH6_THRSEL_MASK          (0x40U)
#define ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT         (6U)
/*! CH6_THRSEL - Threshold select for channel 6. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH6_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH6_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH7_THRSEL_MASK          (0x80U)
#define ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT         (7U)
/*! CH7_THRSEL - Threshold select for channel 7. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH7_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH7_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH8_THRSEL_MASK          (0x100U)
#define ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT         (8U)
/*! CH8_THRSEL - Threshold select for channel 8. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH8_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH8_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH9_THRSEL_MASK          (0x200U)
#define ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT         (9U)
/*! CH9_THRSEL - Threshold select for channel 9. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH9_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH9_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH10_THRSEL_MASK         (0x400U)
#define ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT        (10U)
/*! CH10_THRSEL - Threshold select for channel 10. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH10_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH10_THRSEL_MASK)

#define ADC_CHAN_THRSEL_CH11_THRSEL_MASK         (0x800U)
#define ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT        (11U)
/*! CH11_THRSEL - Threshold select for channel 11. See description for channel 0. */
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
/*! ADCMPINTEN1 - Channel 1 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN1(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN1_SHIFT)) & ADC_INTEN_ADCMPINTEN1_MASK)

#define ADC_INTEN_ADCMPINTEN2_MASK               (0x180U)
#define ADC_INTEN_ADCMPINTEN2_SHIFT              (7U)
/*! ADCMPINTEN2 - Channel 2 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN2(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN2_SHIFT)) & ADC_INTEN_ADCMPINTEN2_MASK)

#define ADC_INTEN_ADCMPINTEN3_MASK               (0x600U)
#define ADC_INTEN_ADCMPINTEN3_SHIFT              (9U)
/*! ADCMPINTEN3 - Channel 3 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN3(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN3_SHIFT)) & ADC_INTEN_ADCMPINTEN3_MASK)

#define ADC_INTEN_ADCMPINTEN4_MASK               (0x1800U)
#define ADC_INTEN_ADCMPINTEN4_SHIFT              (11U)
/*! ADCMPINTEN4 - Channel 4 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN4(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN4_SHIFT)) & ADC_INTEN_ADCMPINTEN4_MASK)

#define ADC_INTEN_ADCMPINTEN5_MASK               (0x6000U)
#define ADC_INTEN_ADCMPINTEN5_SHIFT              (13U)
/*! ADCMPINTEN5 - Channel 5 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN5(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN5_SHIFT)) & ADC_INTEN_ADCMPINTEN5_MASK)

#define ADC_INTEN_ADCMPINTEN6_MASK               (0x18000U)
#define ADC_INTEN_ADCMPINTEN6_SHIFT              (15U)
/*! ADCMPINTEN6 - Channel 6 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN6(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN6_SHIFT)) & ADC_INTEN_ADCMPINTEN6_MASK)

#define ADC_INTEN_ADCMPINTEN7_MASK               (0x60000U)
#define ADC_INTEN_ADCMPINTEN7_SHIFT              (17U)
/*! ADCMPINTEN7 - Channel 7 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN7(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN7_SHIFT)) & ADC_INTEN_ADCMPINTEN7_MASK)

#define ADC_INTEN_ADCMPINTEN8_MASK               (0x180000U)
#define ADC_INTEN_ADCMPINTEN8_SHIFT              (19U)
/*! ADCMPINTEN8 - Channel 8 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN8(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN8_SHIFT)) & ADC_INTEN_ADCMPINTEN8_MASK)

#define ADC_INTEN_ADCMPINTEN9_MASK               (0x600000U)
#define ADC_INTEN_ADCMPINTEN9_SHIFT              (21U)
/*! ADCMPINTEN9 - Channel 9 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN9(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN9_SHIFT)) & ADC_INTEN_ADCMPINTEN9_MASK)

#define ADC_INTEN_ADCMPINTEN10_MASK              (0x1800000U)
#define ADC_INTEN_ADCMPINTEN10_SHIFT             (23U)
/*! ADCMPINTEN10 - Channel 10 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN10(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN10_SHIFT)) & ADC_INTEN_ADCMPINTEN10_MASK)

#define ADC_INTEN_ADCMPINTEN11_MASK              (0x6000000U)
#define ADC_INTEN_ADCMPINTEN11_SHIFT             (25U)
/*! ADCMPINTEN11 - Channel 21 threshold comparison interrupt enable. See description for channel 0. */
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
/*! THCMP1 - Threshold comparison event on Channel 1. See description for channel 0. */
#define ADC_FLAGS_THCMP1(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP1_SHIFT)) & ADC_FLAGS_THCMP1_MASK)

#define ADC_FLAGS_THCMP2_MASK                    (0x4U)
#define ADC_FLAGS_THCMP2_SHIFT                   (2U)
/*! THCMP2 - Threshold comparison event on Channel 2. See description for channel 0. */
#define ADC_FLAGS_THCMP2(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP2_SHIFT)) & ADC_FLAGS_THCMP2_MASK)

#define ADC_FLAGS_THCMP3_MASK                    (0x8U)
#define ADC_FLAGS_THCMP3_SHIFT                   (3U)
/*! THCMP3 - Threshold comparison event on Channel 3. See description for channel 0. */
#define ADC_FLAGS_THCMP3(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP3_SHIFT)) & ADC_FLAGS_THCMP3_MASK)

#define ADC_FLAGS_THCMP4_MASK                    (0x10U)
#define ADC_FLAGS_THCMP4_SHIFT                   (4U)
/*! THCMP4 - Threshold comparison event on Channel 4. See description for channel 0. */
#define ADC_FLAGS_THCMP4(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP4_SHIFT)) & ADC_FLAGS_THCMP4_MASK)

#define ADC_FLAGS_THCMP5_MASK                    (0x20U)
#define ADC_FLAGS_THCMP5_SHIFT                   (5U)
/*! THCMP5 - Threshold comparison event on Channel 5. See description for channel 0. */
#define ADC_FLAGS_THCMP5(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP5_SHIFT)) & ADC_FLAGS_THCMP5_MASK)

#define ADC_FLAGS_THCMP6_MASK                    (0x40U)
#define ADC_FLAGS_THCMP6_SHIFT                   (6U)
/*! THCMP6 - Threshold comparison event on Channel 6. See description for channel 0. */
#define ADC_FLAGS_THCMP6(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP6_SHIFT)) & ADC_FLAGS_THCMP6_MASK)

#define ADC_FLAGS_THCMP7_MASK                    (0x80U)
#define ADC_FLAGS_THCMP7_SHIFT                   (7U)
/*! THCMP7 - Threshold comparison event on Channel 7. See description for channel 0. */
#define ADC_FLAGS_THCMP7(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP7_SHIFT)) & ADC_FLAGS_THCMP7_MASK)

#define ADC_FLAGS_THCMP8_MASK                    (0x100U)
#define ADC_FLAGS_THCMP8_SHIFT                   (8U)
/*! THCMP8 - Threshold comparison event on Channel 8. See description for channel 0. */
#define ADC_FLAGS_THCMP8(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP8_SHIFT)) & ADC_FLAGS_THCMP8_MASK)

#define ADC_FLAGS_THCMP9_MASK                    (0x200U)
#define ADC_FLAGS_THCMP9_SHIFT                   (9U)
/*! THCMP9 - Threshold comparison event on Channel 9. See description for channel 0. */
#define ADC_FLAGS_THCMP9(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP9_SHIFT)) & ADC_FLAGS_THCMP9_MASK)

#define ADC_FLAGS_THCMP10_MASK                   (0x400U)
#define ADC_FLAGS_THCMP10_SHIFT                  (10U)
/*! THCMP10 - Threshold comparison event on Channel 10. See description for channel 0. */
#define ADC_FLAGS_THCMP10(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP10_SHIFT)) & ADC_FLAGS_THCMP10_MASK)

#define ADC_FLAGS_THCMP11_MASK                   (0x800U)
#define ADC_FLAGS_THCMP11_SHIFT                  (11U)
/*! THCMP11 - Threshold comparison event on Channel 11. See description for channel 0. */
#define ADC_FLAGS_THCMP11(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP11_SHIFT)) & ADC_FLAGS_THCMP11_MASK)

#define ADC_FLAGS_OVERRUN0_MASK                  (0x1000U)
#define ADC_FLAGS_OVERRUN0_SHIFT                 (12U)
/*! OVERRUN0 - Mirrors the OVERRRUN status flag from the result register for ADC channel 0 */
#define ADC_FLAGS_OVERRUN0(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN0_SHIFT)) & ADC_FLAGS_OVERRUN0_MASK)

#define ADC_FLAGS_OVERRUN1_MASK                  (0x2000U)
#define ADC_FLAGS_OVERRUN1_SHIFT                 (13U)
/*! OVERRUN1 - Mirrors the OVERRRUN status flag from the result register for ADC channel 1 */
#define ADC_FLAGS_OVERRUN1(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN1_SHIFT)) & ADC_FLAGS_OVERRUN1_MASK)

#define ADC_FLAGS_OVERRUN2_MASK                  (0x4000U)
#define ADC_FLAGS_OVERRUN2_SHIFT                 (14U)
/*! OVERRUN2 - Mirrors the OVERRRUN status flag from the result register for ADC channel 2 */
#define ADC_FLAGS_OVERRUN2(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN2_SHIFT)) & ADC_FLAGS_OVERRUN2_MASK)

#define ADC_FLAGS_OVERRUN3_MASK                  (0x8000U)
#define ADC_FLAGS_OVERRUN3_SHIFT                 (15U)
/*! OVERRUN3 - Mirrors the OVERRRUN status flag from the result register for ADC channel 3 */
#define ADC_FLAGS_OVERRUN3(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN3_SHIFT)) & ADC_FLAGS_OVERRUN3_MASK)

#define ADC_FLAGS_OVERRUN4_MASK                  (0x10000U)
#define ADC_FLAGS_OVERRUN4_SHIFT                 (16U)
/*! OVERRUN4 - Mirrors the OVERRRUN status flag from the result register for ADC channel 4 */
#define ADC_FLAGS_OVERRUN4(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN4_SHIFT)) & ADC_FLAGS_OVERRUN4_MASK)

#define ADC_FLAGS_OVERRUN5_MASK                  (0x20000U)
#define ADC_FLAGS_OVERRUN5_SHIFT                 (17U)
/*! OVERRUN5 - Mirrors the OVERRRUN status flag from the result register for ADC channel 5 */
#define ADC_FLAGS_OVERRUN5(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN5_SHIFT)) & ADC_FLAGS_OVERRUN5_MASK)

#define ADC_FLAGS_OVERRUN6_MASK                  (0x40000U)
#define ADC_FLAGS_OVERRUN6_SHIFT                 (18U)
/*! OVERRUN6 - Mirrors the OVERRRUN status flag from the result register for ADC channel 6 */
#define ADC_FLAGS_OVERRUN6(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN6_SHIFT)) & ADC_FLAGS_OVERRUN6_MASK)

#define ADC_FLAGS_OVERRUN7_MASK                  (0x80000U)
#define ADC_FLAGS_OVERRUN7_SHIFT                 (19U)
/*! OVERRUN7 - Mirrors the OVERRRUN status flag from the result register for ADC channel 7 */
#define ADC_FLAGS_OVERRUN7(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN7_SHIFT)) & ADC_FLAGS_OVERRUN7_MASK)

#define ADC_FLAGS_OVERRUN8_MASK                  (0x100000U)
#define ADC_FLAGS_OVERRUN8_SHIFT                 (20U)
/*! OVERRUN8 - Mirrors the OVERRRUN status flag from the result register for ADC channel 8 */
#define ADC_FLAGS_OVERRUN8(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN8_SHIFT)) & ADC_FLAGS_OVERRUN8_MASK)

#define ADC_FLAGS_OVERRUN9_MASK                  (0x200000U)
#define ADC_FLAGS_OVERRUN9_SHIFT                 (21U)
/*! OVERRUN9 - Mirrors the OVERRRUN status flag from the result register for ADC channel 9 */
#define ADC_FLAGS_OVERRUN9(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN9_SHIFT)) & ADC_FLAGS_OVERRUN9_MASK)

#define ADC_FLAGS_OVERRUN10_MASK                 (0x400000U)
#define ADC_FLAGS_OVERRUN10_SHIFT                (22U)
/*! OVERRUN10 - Mirrors the OVERRRUN status flag from the result register for ADC channel 10 */
#define ADC_FLAGS_OVERRUN10(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN10_SHIFT)) & ADC_FLAGS_OVERRUN10_MASK)

#define ADC_FLAGS_OVERRUN11_MASK                 (0x800000U)
#define ADC_FLAGS_OVERRUN11_SHIFT                (23U)
/*! OVERRUN11 - Mirrors the OVERRRUN status flag from the result register for ADC channel 11 */
#define ADC_FLAGS_OVERRUN11(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN11_SHIFT)) & ADC_FLAGS_OVERRUN11_MASK)

#define ADC_FLAGS_SEQA_OVR_MASK                  (0x1000000U)
#define ADC_FLAGS_SEQA_OVR_SHIFT                 (24U)
/*! SEQA_OVR - Mirrors the global OVERRUN status flag in the SEQA_GDAT register */
#define ADC_FLAGS_SEQA_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_OVR_SHIFT)) & ADC_FLAGS_SEQA_OVR_MASK)

#define ADC_FLAGS_SEQB_OVR_MASK                  (0x2000000U)
#define ADC_FLAGS_SEQB_OVR_SHIFT                 (25U)
/*! SEQB_OVR - Mirrors the global OVERRUN status flag in the SEQB_GDAT register */
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

/*! @name TRM - ADC Startup register. */
/*! @{ */

#define ADC_TRM_VRANGE_MASK                      (0x20U)
#define ADC_TRM_VRANGE_SHIFT                     (5U)
/*! VRANGE - 1.8V to 3.6V Vdd range: This bit MUST be set to '1' if operation below 2.7V is to be
 *    used. Failure to set this bit will result in invalid ADC results. Note: This bit will not be
 *    spec'd on parts that do not support operation below 2.7V
 */
#define ADC_TRM_VRANGE(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_TRM_VRANGE_SHIFT)) & ADC_TRM_VRANGE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4001C000u)
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
/*! CRC_POLY - CRC polynomial: 1X = CRC-32 polynomial 01 = CRC-16 polynomial 00 = CRC-CCITT polynomial */
#define CRC_MODE_CRC_POLY(x)                     (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CRC_POLY_SHIFT)) & CRC_MODE_CRC_POLY_MASK)

#define CRC_MODE_BIT_RVS_WR_MASK                 (0x4U)
#define CRC_MODE_BIT_RVS_WR_SHIFT                (2U)
/*! BIT_RVS_WR - Data bit order: 1 = Bit order reverse for CRC_WR_DATA (per byte) 0 = No bit order reverse for CRC_WR_DATA (per byte) */
#define CRC_MODE_BIT_RVS_WR(x)                   (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_WR_SHIFT)) & CRC_MODE_BIT_RVS_WR_MASK)

#define CRC_MODE_CMPL_WR_MASK                    (0x8U)
#define CRC_MODE_CMPL_WR_SHIFT                   (3U)
/*! CMPL_WR - Data complement: 1 = 1's complement for CRC_WR_DATA 0 = No 1's complement for CRC_WR_DATA */
#define CRC_MODE_CMPL_WR(x)                      (((uint32_t)(((uint32_t)(x)) << CRC_MODE_CMPL_WR_SHIFT)) & CRC_MODE_CMPL_WR_MASK)

#define CRC_MODE_BIT_RVS_SUM_MASK                (0x10U)
#define CRC_MODE_BIT_RVS_SUM_SHIFT               (4U)
/*! BIT_RVS_SUM - CRC sum bit order: 1 = Bit order reverse for CRC_SUM 0 = No bit order reverse for CRC_SUM */
#define CRC_MODE_BIT_RVS_SUM(x)                  (((uint32_t)(((uint32_t)(x)) << CRC_MODE_BIT_RVS_SUM_SHIFT)) & CRC_MODE_BIT_RVS_SUM_MASK)

#define CRC_MODE_CMPL_SUM_MASK                   (0x20U)
#define CRC_MODE_CMPL_SUM_SHIFT                  (5U)
/*! CMPL_SUM - CRC sum complement: 1 = 1's complement for CRC_SUM 0 = No 1's complement for CRC_SUM */
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
/*! CRC_SUM - The most recent CRC sum can be read through this register with selected bit order and 1's complement post-processes. */
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
/** Peripheral CRC base address */
#define CRC_BASE                                 (0x50004000u)
/** Peripheral CRC base pointer */
#define CRC0                                     ((CRC_Type *)CRC_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           { CRC_BASE }
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            { CRC0 }

/*!
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */


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
  } CHANNEL[25];
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

#define DMA_COMMON_ENABLESET_ENA_MASK            (0x1FFFFFFU)
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

#define DMA_COMMON_ENABLECLR_CLR_MASK            (0x1FFFFFFU)
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

#define DMA_COMMON_ACTIVE_ACT_MASK               (0x1FFFFFFU)
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

#define DMA_COMMON_BUSY_BSY_MASK                 (0x1FFFFFFU)
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

#define DMA_COMMON_ERRINT_ERR_MASK               (0x1FFFFFFU)
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

#define DMA_COMMON_INTENSET_INTEN_MASK           (0x1FFFFFFU)
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

#define DMA_COMMON_INTENCLR_CLR_MASK             (0x1FFFFFFU)
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

#define DMA_COMMON_INTA_IA_MASK                  (0x1FFFFFFU)
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

#define DMA_COMMON_INTB_IB_MASK                  (0x1FFFFFFU)
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

#define DMA_CHANNEL_CFG_CHPRIORITY_MASK          (0x30000U)
#define DMA_CHANNEL_CFG_CHPRIORITY_SHIFT         (16U)
/*! CHPRIORITY - Priority of this channel when multiple DMA requests are pending. Four priority
 *    levels are supported: 0x0 = highest priority. 0x3 = lowest priority.
 */
#define DMA_CHANNEL_CFG_CHPRIORITY(x)            (((uint32_t)(((uint32_t)(x)) << DMA_CHANNEL_CFG_CHPRIORITY_SHIFT)) & DMA_CHANNEL_CFG_CHPRIORITY_MASK)
/*! @} */

/* The count of DMA_CHANNEL_CFG */
#define DMA_CHANNEL_CFG_COUNT                    (25U)

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
#define DMA_CHANNEL_CTLSTAT_COUNT                (25U)

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
#define DMA_CHANNEL_XFERCFG_COUNT                (25U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA0 base address */
#define DMA0_BASE                                (0x50005000u)
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
   -- FLASH_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CTRL_Peripheral_Access_Layer FLASH_CTRL Peripheral Access Layer
 * @{
 */

/** FLASH_CTRL - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t FLASHCFG;                          /**< Flash configuration register, offset: 0x10 */
       uint8_t RESERVED_1[12];
  __IO uint32_t FMSSTART;                          /**< Flash signature start address register, offset: 0x20 */
  __IO uint32_t FMSSTOP;                           /**< Flash signaure stop address register, offset: 0x24 */
       uint8_t RESERVED_2[4];
  __I  uint32_t FMSW0;                             /**< Flash signature generation result register returns the flash signature produced by the embedded signature generator.., offset: 0x2C */
       uint8_t RESERVED_3[4016];
  __I  uint32_t FMSTAT;                            /**< Flash signature generation status bit, offset: 0xFE0 */
       uint8_t RESERVED_4[4];
  __O  uint32_t FMSTATCLR;                         /**< Clear FLASH signature generation status bit, offset: 0xFE8 */
} FLASH_CTRL_Type;

/* ----------------------------------------------------------------------------
   -- FLASH_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_CTRL_Register_Masks FLASH_CTRL Register Masks
 * @{
 */

/*! @name FLASHCFG - Flash configuration register */
/*! @{ */

#define FLASH_CTRL_FLASHCFG_FLASHTIM_MASK        (0x3U)
#define FLASH_CTRL_FLASHCFG_FLASHTIM_SHIFT       (0U)
/*! FLASHTIM - Flash memory access time. FLASHTIM +1 is equal to the number of system clocks used for flash access.
 *  0b00..1 system clock flash access time.
 *  0b01..2 system clock flash access time.
 *  0b10..3 system clock flash access time.
 *  0b11..Reserved.
 */
#define FLASH_CTRL_FLASHCFG_FLASHTIM(x)          (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FLASHCFG_FLASHTIM_SHIFT)) & FLASH_CTRL_FLASHCFG_FLASHTIM_MASK)
/*! @} */

/*! @name FMSSTART - Flash signature start address register */
/*! @{ */

#define FLASH_CTRL_FMSSTART_START_MASK           (0x1FFFFU)
#define FLASH_CTRL_FMSSTART_START_SHIFT          (0U)
/*! START - Signature generation start address (corresponds to AHB byte address bits[18:2]). */
#define FLASH_CTRL_FMSSTART_START(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSSTART_START_SHIFT)) & FLASH_CTRL_FMSSTART_START_MASK)
/*! @} */

/*! @name FMSSTOP - Flash signaure stop address register */
/*! @{ */

#define FLASH_CTRL_FMSSTOP_STOPA_MASK            (0x1FFFFU)
#define FLASH_CTRL_FMSSTOP_STOPA_SHIFT           (0U)
/*! STOPA - Stop address for signature generation (the word specified by STOP is included in the
 *    address range). The address is in units of memory words, not bytes.
 */
#define FLASH_CTRL_FMSSTOP_STOPA(x)              (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSSTOP_STOPA_SHIFT)) & FLASH_CTRL_FMSSTOP_STOPA_MASK)

#define FLASH_CTRL_FMSSTOP_STRTBIST_MASK         (0x80000000U)
#define FLASH_CTRL_FMSSTOP_STRTBIST_SHIFT        (31U)
/*! STRTBIST - When this bit is written to 1, signature generation starts. At the end of signature
 *    generation, this bit is automatically cleared.
 */
#define FLASH_CTRL_FMSSTOP_STRTBIST(x)           (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSSTOP_STRTBIST_SHIFT)) & FLASH_CTRL_FMSSTOP_STRTBIST_MASK)
/*! @} */

/*! @name FMSW0 - Flash signature generation result register returns the flash signature produced by the embedded signature generator.. */
/*! @{ */

#define FLASH_CTRL_FMSW0_SIG_MASK                (0xFFFFFFFFU)
#define FLASH_CTRL_FMSW0_SIG_SHIFT               (0U)
/*! SIG - 32-bit signature. */
#define FLASH_CTRL_FMSW0_SIG(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSW0_SIG_SHIFT)) & FLASH_CTRL_FMSW0_SIG_MASK)
/*! @} */

/*! @name FMSTAT - Flash signature generation status bit */
/*! @{ */

#define FLASH_CTRL_FMSTAT_SIG_DONE_MASK          (0x2U)
#define FLASH_CTRL_FMSTAT_SIG_DONE_SHIFT         (1U)
/*! SIG_DONE - This status bit is set at the end of signature computation */
#define FLASH_CTRL_FMSTAT_SIG_DONE(x)            (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSTAT_SIG_DONE_SHIFT)) & FLASH_CTRL_FMSTAT_SIG_DONE_MASK)
/*! @} */

/*! @name FMSTATCLR - Clear FLASH signature generation status bit */
/*! @{ */

#define FLASH_CTRL_FMSTATCLR_SIG_DONE_CLR_MASK   (0x2U)
#define FLASH_CTRL_FMSTATCLR_SIG_DONE_CLR_SHIFT  (1U)
/*! SIG_DONE_CLR - When the bit is written to 1, the SIGNATURE_DONE bit is cleared. */
#define FLASH_CTRL_FMSTATCLR_SIG_DONE_CLR(x)     (((uint32_t)(((uint32_t)(x)) << FLASH_CTRL_FMSTATCLR_SIG_DONE_CLR_SHIFT)) & FLASH_CTRL_FMSTATCLR_SIG_DONE_CLR_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLASH_CTRL_Register_Masks */


/* FLASH_CTRL - Peripheral instance base addresses */
/** Peripheral FLASH_CTRL base address */
#define FLASH_CTRL_BASE                          (0x40040000u)
/** Peripheral FLASH_CTRL base pointer */
#define FLASH_CTRL                               ((FLASH_CTRL_Type *)FLASH_CTRL_BASE)
/** Array initializer of FLASH_CTRL peripheral base addresses */
#define FLASH_CTRL_BASE_ADDRS                    { FLASH_CTRL_BASE }
/** Array initializer of FLASH_CTRL peripheral base pointers */
#define FLASH_CTRL_BASE_PTRS                     { FLASH_CTRL }
/** Interrupt vectors for the FLASH_CTRL peripheral type */
#define FLASH_CTRL_IRQS                          { FLASH_IRQn }

/*!
 * @}
 */ /* end of group FLASH_CTRL_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FTM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Peripheral_Access_Layer FTM Peripheral Access Layer
 * @{
 */

/** FTM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SC;                                /**< Status And Control, offset: 0x0 */
  __IO uint32_t CNT;                               /**< Counter, offset: 0x4 */
  __IO uint32_t MOD;                               /**< Modulo, offset: 0x8 */
  struct {                                         /* offset: 0xC, array step: 0x8 */
    __IO uint32_t CnSC;                              /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8, irregular array, not all indices are valid */
    __IO uint32_t CnV;                               /**< Channel (n) Value, array offset: 0x10, array step: 0x8, irregular array, not all indices are valid */
  } CONTROLS[8];
  __IO uint32_t CNTIN;                             /**< Counter Initial Value, offset: 0x4C */
  __IO uint32_t STATUS;                            /**< Capture And Compare Status, offset: 0x50 */
  __IO uint32_t MODE;                              /**< Features Mode Selection, offset: 0x54 */
  __IO uint32_t SYNC;                              /**< Synchronization, offset: 0x58 */
  __IO uint32_t OUTINIT;                           /**< Initial State For Channels Output, offset: 0x5C */
  __IO uint32_t OUTMASK;                           /**< Output Mask, offset: 0x60 */
  __IO uint32_t COMBINE;                           /**< Function For Linked Channels, offset: 0x64 */
  __IO uint32_t DEADTIME;                          /**< Deadtime Configuration, offset: 0x68 */
  __IO uint32_t EXTTRIG;                           /**< FTM External Trigger, offset: 0x6C */
  __IO uint32_t POL;                               /**< Channels Polarity, offset: 0x70 */
  __IO uint32_t FMS;                               /**< Fault Mode Status, offset: 0x74 */
  __IO uint32_t FILTER;                            /**< Input Capture Filter Control, offset: 0x78 */
  __IO uint32_t FLTCTRL;                           /**< Fault Control, offset: 0x7C, available only on: FTM0 (missing on FTM1) */
  __IO uint32_t QDCTRL;                            /**< Quadrature Decoder Control And Status, offset: 0x80 */
  __IO uint32_t CONF;                              /**< Configuration, offset: 0x84 */
  __IO uint32_t FLTPOL;                            /**< FTM Fault Input Polarity, offset: 0x88, available only on: FTM0 (missing on FTM1) */
  __IO uint32_t SYNCONF;                           /**< Synchronization Configuration, offset: 0x8C */
  __IO uint32_t INVCTRL;                           /**< FTM Inverting Control, offset: 0x90 */
  __IO uint32_t SWOCTRL;                           /**< FTM Software Output Control, offset: 0x94 */
  __IO uint32_t PWMLOAD;                           /**< FTM PWM Load, offset: 0x98 */
  __IO uint32_t HCR;                               /**< Half Cycle Register, offset: 0x9C */
       uint8_t RESERVED_0[352];
  __IO uint32_t MOD_MIRROR;                        /**< Mirror of Modulo Value, offset: 0x200 */
  __IO uint32_t CV_MIRROR[8];                      /**< Mirror of Channel (n) Match Value, array offset: 0x204, array step: 0x4, irregular array, not all indices are valid */
} FTM_Type;

/* ----------------------------------------------------------------------------
   -- FTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTM_Register_Masks FTM Register Masks
 * @{
 */

/*! @name SC - Status And Control */
/*! @{ */

#define FTM_SC_PS_MASK                           (0x7U)
#define FTM_SC_PS_SHIFT                          (0U)
/*! PS - Prescale Factor Selection
 *  0b000..Divide by 1
 *  0b001..Divide by 2
 *  0b010..Divide by 4
 *  0b011..Divide by 8
 *  0b100..Divide by 16
 *  0b101..Divide by 32
 *  0b110..Divide by 64
 *  0b111..Divide by 128
 */
#define FTM_SC_PS(x)                             (((uint32_t)(((uint32_t)(x)) << FTM_SC_PS_SHIFT)) & FTM_SC_PS_MASK)

#define FTM_SC_CLKS_MASK                         (0x18U)
#define FTM_SC_CLKS_SHIFT                        (3U)
/*! CLKS - Clock Source Selection
 *  0b00..No clock selected. This in effect disables the FTM counter.
 *  0b01..FTM input clock
 *  0b10..Fixed frequency clock
 *  0b11..External clock
 */
#define FTM_SC_CLKS(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_SC_CLKS_SHIFT)) & FTM_SC_CLKS_MASK)

#define FTM_SC_CPWMS_MASK                        (0x20U)
#define FTM_SC_CPWMS_SHIFT                       (5U)
/*! CPWMS - Center-Aligned PWM Select
 *  0b0..FTM counter operates in Up Counting mode.
 *  0b1..FTM counter operates in Up-Down Counting mode.
 */
#define FTM_SC_CPWMS(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_SC_CPWMS_SHIFT)) & FTM_SC_CPWMS_MASK)

#define FTM_SC_RIE_MASK                          (0x40U)
#define FTM_SC_RIE_SHIFT                         (6U)
/*! RIE - Reload Point Interrupt Enable
 *  0b0..Reload point interrupt is disabled.
 *  0b1..Reload point interrupt is enabled.
 */
#define FTM_SC_RIE(x)                            (((uint32_t)(((uint32_t)(x)) << FTM_SC_RIE_SHIFT)) & FTM_SC_RIE_MASK)

#define FTM_SC_RF_MASK                           (0x80U)
#define FTM_SC_RF_SHIFT                          (7U)
/*! RF - Reload Flag
 *  0b0..A selected reload point did not happen.
 *  0b1..A selected reload point happened.
 */
#define FTM_SC_RF(x)                             (((uint32_t)(((uint32_t)(x)) << FTM_SC_RF_SHIFT)) & FTM_SC_RF_MASK)

#define FTM_SC_TOIE_MASK                         (0x100U)
#define FTM_SC_TOIE_SHIFT                        (8U)
/*! TOIE - Timer Overflow Interrupt Enable
 *  0b0..Disable TOF interrupts. Use software polling.
 *  0b1..Enable TOF interrupts. An interrupt is generated when TOF equals one.
 */
#define FTM_SC_TOIE(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_SC_TOIE_SHIFT)) & FTM_SC_TOIE_MASK)

#define FTM_SC_TOF_MASK                          (0x200U)
#define FTM_SC_TOF_SHIFT                         (9U)
/*! TOF - Timer Overflow Flag
 *  0b0..FTM counter has not overflowed.
 *  0b1..FTM counter has overflowed.
 */
#define FTM_SC_TOF(x)                            (((uint32_t)(((uint32_t)(x)) << FTM_SC_TOF_SHIFT)) & FTM_SC_TOF_MASK)

#define FTM_SC_PWMEN0_MASK                       (0x10000U)
#define FTM_SC_PWMEN0_SHIFT                      (16U)
/*! PWMEN0 - Channel 0 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN0(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN0_SHIFT)) & FTM_SC_PWMEN0_MASK)

#define FTM_SC_PWMEN1_MASK                       (0x20000U)
#define FTM_SC_PWMEN1_SHIFT                      (17U)
/*! PWMEN1 - Channel 1 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN1(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN1_SHIFT)) & FTM_SC_PWMEN1_MASK)

#define FTM_SC_PWMEN2_MASK                       (0x40000U)
#define FTM_SC_PWMEN2_SHIFT                      (18U)
/*! PWMEN2 - Channel 2 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN2(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN2_SHIFT)) & FTM_SC_PWMEN2_MASK)

#define FTM_SC_PWMEN3_MASK                       (0x80000U)
#define FTM_SC_PWMEN3_SHIFT                      (19U)
/*! PWMEN3 - Channel 3 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN3(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN3_SHIFT)) & FTM_SC_PWMEN3_MASK)

#define FTM_SC_PWMEN4_MASK                       (0x100000U)
#define FTM_SC_PWMEN4_SHIFT                      (20U)
/*! PWMEN4 - Channel 4 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN4(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN4_SHIFT)) & FTM_SC_PWMEN4_MASK)

#define FTM_SC_PWMEN5_MASK                       (0x200000U)
#define FTM_SC_PWMEN5_SHIFT                      (21U)
/*! PWMEN5 - Channel 5 PWM enable bit
 *  0b0..Channel output port is disabled.
 *  0b1..Channel output port is enabled.
 */
#define FTM_SC_PWMEN5(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_SC_PWMEN5_SHIFT)) & FTM_SC_PWMEN5_MASK)
/*! @} */

/*! @name CNT - Counter */
/*! @{ */

#define FTM_CNT_COUNT_MASK                       (0xFFFFU)
#define FTM_CNT_COUNT_SHIFT                      (0U)
/*! COUNT - Counter Value */
#define FTM_CNT_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CNT_COUNT_SHIFT)) & FTM_CNT_COUNT_MASK)
/*! @} */

/*! @name MOD - Modulo */
/*! @{ */

#define FTM_MOD_MOD_MASK                         (0xFFFFU)
#define FTM_MOD_MOD_SHIFT                        (0U)
/*! MOD - MOD */
#define FTM_MOD_MOD(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_MOD_MOD_SHIFT)) & FTM_MOD_MOD_MASK)
/*! @} */

/*! @name CnSC - Channel (n) Status And Control */
/*! @{ */

#define FTM_CnSC_ICRST_MASK                      (0x2U)
#define FTM_CnSC_ICRST_SHIFT                     (1U)
/*! ICRST - FTM counter reset by the selected input capture event.
 *  0b0..FTM counter is not reset when the selected channel (n) input event is detected.
 *  0b1..FTM counter is reset when the selected channel (n) input event is detected.
 */
#define FTM_CnSC_ICRST(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ICRST_SHIFT)) & FTM_CnSC_ICRST_MASK)

#define FTM_CnSC_ELSA_MASK                       (0x4U)
#define FTM_CnSC_ELSA_SHIFT                      (2U)
/*! ELSA - Channel (n) Edge or Level Select */
#define FTM_CnSC_ELSA(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ELSA_SHIFT)) & FTM_CnSC_ELSA_MASK)

#define FTM_CnSC_ELSB_MASK                       (0x8U)
#define FTM_CnSC_ELSB_SHIFT                      (3U)
/*! ELSB - Channel (n) Edge or Level Select */
#define FTM_CnSC_ELSB(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_ELSB_SHIFT)) & FTM_CnSC_ELSB_MASK)

#define FTM_CnSC_MSA_MASK                        (0x10U)
#define FTM_CnSC_MSA_SHIFT                       (4U)
/*! MSA - Channel (n) Mode Select */
#define FTM_CnSC_MSA(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_MSA_SHIFT)) & FTM_CnSC_MSA_MASK)

#define FTM_CnSC_MSB_MASK                        (0x20U)
#define FTM_CnSC_MSB_SHIFT                       (5U)
/*! MSB - Channel (n) Mode Select */
#define FTM_CnSC_MSB(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_MSB_SHIFT)) & FTM_CnSC_MSB_MASK)

#define FTM_CnSC_CHIE_MASK                       (0x40U)
#define FTM_CnSC_CHIE_SHIFT                      (6U)
/*! CHIE - Channel (n) Interrupt Enable
 *  0b0..Disable channel (n) interrupt. Use software polling.
 *  0b1..Enable channel (n) interrupt.
 */
#define FTM_CnSC_CHIE(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_CHIE_SHIFT)) & FTM_CnSC_CHIE_MASK)

#define FTM_CnSC_CHF_MASK                        (0x80U)
#define FTM_CnSC_CHF_SHIFT                       (7U)
/*! CHF - Channel (n) Flag
 *  0b0..No channel (n) event has occurred.
 *  0b1..A channel (n) event has occurred.
 */
#define FTM_CnSC_CHF(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_CHF_SHIFT)) & FTM_CnSC_CHF_MASK)

#define FTM_CnSC_TRIGMODE_MASK                   (0x100U)
#define FTM_CnSC_TRIGMODE_SHIFT                  (8U)
/*! TRIGMODE - Trigger mode control
 *  0b0..Channel outputs will generate the normal PWM outputs without generating a pulse.
 *  0b1..If a match in the channel occurs, a trigger generation on channel output will happen. The trigger pulse width has one FTM clock cycle.
 */
#define FTM_CnSC_TRIGMODE(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_TRIGMODE_SHIFT)) & FTM_CnSC_TRIGMODE_MASK)

#define FTM_CnSC_CHIS_MASK                       (0x200U)
#define FTM_CnSC_CHIS_SHIFT                      (9U)
/*! CHIS - Channel (n) Input State
 *  0b0..The channel (n) input is zero.
 *  0b1..The channel (n) input is one.
 */
#define FTM_CnSC_CHIS(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CnSC_CHIS_SHIFT)) & FTM_CnSC_CHIS_MASK)
/*! @} */

/* The count of FTM_CnSC */
#define FTM_CnSC_COUNT                           (8U)

/*! @name CnV - Channel (n) Value */
/*! @{ */

#define FTM_CnV_VAL_MASK                         (0xFFFFU)
#define FTM_CnV_VAL_SHIFT                        (0U)
/*! VAL - Channel Value */
#define FTM_CnV_VAL(x)                           (((uint32_t)(((uint32_t)(x)) << FTM_CnV_VAL_SHIFT)) & FTM_CnV_VAL_MASK)
/*! @} */

/* The count of FTM_CnV */
#define FTM_CnV_COUNT                            (8U)

/*! @name CNTIN - Counter Initial Value */
/*! @{ */

#define FTM_CNTIN_INIT_MASK                      (0xFFFFU)
#define FTM_CNTIN_INIT_SHIFT                     (0U)
/*! INIT - INIT */
#define FTM_CNTIN_INIT(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_CNTIN_INIT_SHIFT)) & FTM_CNTIN_INIT_MASK)
/*! @} */

/*! @name STATUS - Capture And Compare Status */
/*! @{ */

#define FTM_STATUS_CH0F_MASK                     (0x1U)
#define FTM_STATUS_CH0F_SHIFT                    (0U)
/*! CH0F - Channel 0 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH0F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH0F_SHIFT)) & FTM_STATUS_CH0F_MASK)

#define FTM_STATUS_CH1F_MASK                     (0x2U)
#define FTM_STATUS_CH1F_SHIFT                    (1U)
/*! CH1F - Channel 1 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH1F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH1F_SHIFT)) & FTM_STATUS_CH1F_MASK)

#define FTM_STATUS_CH2F_MASK                     (0x4U)
#define FTM_STATUS_CH2F_SHIFT                    (2U)
/*! CH2F - Channel 2 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH2F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH2F_SHIFT)) & FTM_STATUS_CH2F_MASK)

#define FTM_STATUS_CH3F_MASK                     (0x8U)
#define FTM_STATUS_CH3F_SHIFT                    (3U)
/*! CH3F - Channel 3 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH3F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH3F_SHIFT)) & FTM_STATUS_CH3F_MASK)

#define FTM_STATUS_CH4F_MASK                     (0x10U)
#define FTM_STATUS_CH4F_SHIFT                    (4U)
/*! CH4F - Channel 4 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH4F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH4F_SHIFT)) & FTM_STATUS_CH4F_MASK)

#define FTM_STATUS_CH5F_MASK                     (0x20U)
#define FTM_STATUS_CH5F_SHIFT                    (5U)
/*! CH5F - Channel 5 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH5F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH5F_SHIFT)) & FTM_STATUS_CH5F_MASK)

#define FTM_STATUS_CH6F_MASK                     (0x40U)
#define FTM_STATUS_CH6F_SHIFT                    (6U)
/*! CH6F - Channel 6 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH6F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH6F_SHIFT)) & FTM_STATUS_CH6F_MASK)

#define FTM_STATUS_CH7F_MASK                     (0x80U)
#define FTM_STATUS_CH7F_SHIFT                    (7U)
/*! CH7F - Channel 7 Flag
 *  0b0..No channel event has occurred.
 *  0b1..A channel event has occurred.
 */
#define FTM_STATUS_CH7F(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_STATUS_CH7F_SHIFT)) & FTM_STATUS_CH7F_MASK)
/*! @} */

/*! @name MODE - Features Mode Selection */
/*! @{ */

#define FTM_MODE_FTMEN_MASK                      (0x1U)
#define FTM_MODE_FTMEN_SHIFT                     (0U)
/*! FTMEN - FTM Enable
 *  0b0..TPM compatibility. Free running counter and synchronization compatible with TPM.
 *  0b1..Free running counter and synchronization are different from TPM behavior.
 */
#define FTM_MODE_FTMEN(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FTMEN_SHIFT)) & FTM_MODE_FTMEN_MASK)

#define FTM_MODE_INIT_MASK                       (0x2U)
#define FTM_MODE_INIT_SHIFT                      (1U)
/*! INIT - Initialize The Channels Output */
#define FTM_MODE_INIT(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_MODE_INIT_SHIFT)) & FTM_MODE_INIT_MASK)

#define FTM_MODE_WPDIS_MASK                      (0x4U)
#define FTM_MODE_WPDIS_SHIFT                     (2U)
/*! WPDIS - Write Protection Disable
 *  0b0..Write protection is enabled.
 *  0b1..Write protection is disabled.
 */
#define FTM_MODE_WPDIS(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_MODE_WPDIS_SHIFT)) & FTM_MODE_WPDIS_MASK)

#define FTM_MODE_PWMSYNC_MASK                    (0x8U)
#define FTM_MODE_PWMSYNC_SHIFT                   (3U)
/*! PWMSYNC - PWM Synchronization Mode
 *  0b0..No restrictions. Software and hardware triggers can be used by MOD, CnV, OUTMASK, and FTM counter synchronization.
 *  0b1..Software trigger can only be used by MOD and CnV synchronization, and hardware triggers can only be used
 *       by OUTMASK and FTM counter synchronization.
 */
#define FTM_MODE_PWMSYNC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_PWMSYNC_SHIFT)) & FTM_MODE_PWMSYNC_MASK)

#define FTM_MODE_CAPTEST_MASK                    (0x10U)
#define FTM_MODE_CAPTEST_SHIFT                   (4U)
/*! CAPTEST - Capture Test Mode Enable
 *  0b0..Capture test mode is disabled.
 *  0b1..Capture test mode is enabled.
 */
#define FTM_MODE_CAPTEST(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_CAPTEST_SHIFT)) & FTM_MODE_CAPTEST_MASK)

#define FTM_MODE_FAULTM_MASK                     (0x60U)
#define FTM_MODE_FAULTM_SHIFT                    (5U)
/*! FAULTM - Fault Control Mode
 *  0b00..Fault control is disabled for all channels.
 *  0b01..Fault control is enabled for even channels only (channels 0, 2, 4, and 6), and the selected mode is the manual fault clearing.
 *  0b10..Fault control is enabled for all channels, and the selected mode is the manual fault clearing.
 *  0b11..Fault control is enabled for all channels, and the selected mode is the automatic fault clearing.
 */
#define FTM_MODE_FAULTM(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FAULTM_SHIFT)) & FTM_MODE_FAULTM_MASK)

#define FTM_MODE_FAULTIE_MASK                    (0x80U)
#define FTM_MODE_FAULTIE_SHIFT                   (7U)
/*! FAULTIE - Fault Interrupt Enable
 *  0b0..Fault control interrupt is disabled.
 *  0b1..Fault control interrupt is enabled.
 */
#define FTM_MODE_FAULTIE(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_MODE_FAULTIE_SHIFT)) & FTM_MODE_FAULTIE_MASK)
/*! @} */

/*! @name SYNC - Synchronization */
/*! @{ */

#define FTM_SYNC_CNTMIN_MASK                     (0x1U)
#define FTM_SYNC_CNTMIN_SHIFT                    (0U)
/*! CNTMIN - Minimum Loading Point Enable
 *  0b0..The minimum loading point is disabled.
 *  0b1..The minimum loading point is enabled.
 */
#define FTM_SYNC_CNTMIN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_CNTMIN_SHIFT)) & FTM_SYNC_CNTMIN_MASK)

#define FTM_SYNC_CNTMAX_MASK                     (0x2U)
#define FTM_SYNC_CNTMAX_SHIFT                    (1U)
/*! CNTMAX - Maximum Loading Point Enable
 *  0b0..The maximum loading point is disabled.
 *  0b1..The maximum loading point is enabled.
 */
#define FTM_SYNC_CNTMAX(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_CNTMAX_SHIFT)) & FTM_SYNC_CNTMAX_MASK)

#define FTM_SYNC_REINIT_MASK                     (0x4U)
#define FTM_SYNC_REINIT_SHIFT                    (2U)
/*! REINIT - FTM Counter Reinitialization by Synchronization
 *  0b0..FTM counter continues to count normally.
 *  0b1..FTM counter is updated with its initial value when the selected trigger is detected.
 */
#define FTM_SYNC_REINIT(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_REINIT_SHIFT)) & FTM_SYNC_REINIT_MASK)

#define FTM_SYNC_SYNCHOM_MASK                    (0x8U)
#define FTM_SYNC_SYNCHOM_SHIFT                   (3U)
/*! SYNCHOM - Output Mask Synchronization
 *  0b0..OUTMASK register is updated with the value of its buffer in all rising edges of the FTM input clock.
 *  0b1..OUTMASK register is updated with the value of its buffer only by the PWM synchronization.
 */
#define FTM_SYNC_SYNCHOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_SYNCHOM_SHIFT)) & FTM_SYNC_SYNCHOM_MASK)

#define FTM_SYNC_TRIG0_MASK                      (0x10U)
#define FTM_SYNC_TRIG0_SHIFT                     (4U)
/*! TRIG0 - PWM Synchronization Hardware Trigger 0
 *  0b0..Trigger is disabled.
 *  0b1..Trigger is enabled.
 */
#define FTM_SYNC_TRIG0(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG0_SHIFT)) & FTM_SYNC_TRIG0_MASK)

#define FTM_SYNC_TRIG1_MASK                      (0x20U)
#define FTM_SYNC_TRIG1_SHIFT                     (5U)
/*! TRIG1 - PWM Synchronization Hardware Trigger 1
 *  0b0..Trigger is disabled.
 *  0b1..Trigger is enabled.
 */
#define FTM_SYNC_TRIG1(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG1_SHIFT)) & FTM_SYNC_TRIG1_MASK)

#define FTM_SYNC_TRIG2_MASK                      (0x40U)
#define FTM_SYNC_TRIG2_SHIFT                     (6U)
/*! TRIG2 - PWM Synchronization Hardware Trigger 2
 *  0b0..Trigger is disabled.
 *  0b1..Trigger is enabled.
 */
#define FTM_SYNC_TRIG2(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_TRIG2_SHIFT)) & FTM_SYNC_TRIG2_MASK)

#define FTM_SYNC_SWSYNC_MASK                     (0x80U)
#define FTM_SYNC_SWSYNC_SHIFT                    (7U)
/*! SWSYNC - PWM Synchronization Software Trigger
 *  0b0..Software trigger is not selected.
 *  0b1..Software trigger is selected.
 */
#define FTM_SYNC_SWSYNC(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_SYNC_SWSYNC_SHIFT)) & FTM_SYNC_SWSYNC_MASK)
/*! @} */

/*! @name OUTINIT - Initial State For Channels Output */
/*! @{ */

#define FTM_OUTINIT_CH0OI_MASK                   (0x1U)
#define FTM_OUTINIT_CH0OI_SHIFT                  (0U)
/*! CH0OI - Channel 0 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH0OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH0OI_SHIFT)) & FTM_OUTINIT_CH0OI_MASK)

#define FTM_OUTINIT_CH1OI_MASK                   (0x2U)
#define FTM_OUTINIT_CH1OI_SHIFT                  (1U)
/*! CH1OI - Channel 1 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH1OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH1OI_SHIFT)) & FTM_OUTINIT_CH1OI_MASK)

#define FTM_OUTINIT_CH2OI_MASK                   (0x4U)
#define FTM_OUTINIT_CH2OI_SHIFT                  (2U)
/*! CH2OI - Channel 2 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH2OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH2OI_SHIFT)) & FTM_OUTINIT_CH2OI_MASK)

#define FTM_OUTINIT_CH3OI_MASK                   (0x8U)
#define FTM_OUTINIT_CH3OI_SHIFT                  (3U)
/*! CH3OI - Channel 3 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH3OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH3OI_SHIFT)) & FTM_OUTINIT_CH3OI_MASK)

#define FTM_OUTINIT_CH4OI_MASK                   (0x10U)
#define FTM_OUTINIT_CH4OI_SHIFT                  (4U)
/*! CH4OI - Channel 4 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH4OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH4OI_SHIFT)) & FTM_OUTINIT_CH4OI_MASK)

#define FTM_OUTINIT_CH5OI_MASK                   (0x20U)
#define FTM_OUTINIT_CH5OI_SHIFT                  (5U)
/*! CH5OI - Channel 5 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH5OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH5OI_SHIFT)) & FTM_OUTINIT_CH5OI_MASK)

#define FTM_OUTINIT_CH6OI_MASK                   (0x40U)
#define FTM_OUTINIT_CH6OI_SHIFT                  (6U)
/*! CH6OI - Channel 6 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH6OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH6OI_SHIFT)) & FTM_OUTINIT_CH6OI_MASK)

#define FTM_OUTINIT_CH7OI_MASK                   (0x80U)
#define FTM_OUTINIT_CH7OI_SHIFT                  (7U)
/*! CH7OI - Channel 7 Output Initialization Value
 *  0b0..The initialization value is 0.
 *  0b1..The initialization value is 1.
 */
#define FTM_OUTINIT_CH7OI(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTINIT_CH7OI_SHIFT)) & FTM_OUTINIT_CH7OI_MASK)
/*! @} */

/*! @name OUTMASK - Output Mask */
/*! @{ */

#define FTM_OUTMASK_CH0OM_MASK                   (0x1U)
#define FTM_OUTMASK_CH0OM_SHIFT                  (0U)
/*! CH0OM - Channel 0 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH0OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH0OM_SHIFT)) & FTM_OUTMASK_CH0OM_MASK)

#define FTM_OUTMASK_CH1OM_MASK                   (0x2U)
#define FTM_OUTMASK_CH1OM_SHIFT                  (1U)
/*! CH1OM - Channel 1 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH1OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH1OM_SHIFT)) & FTM_OUTMASK_CH1OM_MASK)

#define FTM_OUTMASK_CH2OM_MASK                   (0x4U)
#define FTM_OUTMASK_CH2OM_SHIFT                  (2U)
/*! CH2OM - Channel 2 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH2OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH2OM_SHIFT)) & FTM_OUTMASK_CH2OM_MASK)

#define FTM_OUTMASK_CH3OM_MASK                   (0x8U)
#define FTM_OUTMASK_CH3OM_SHIFT                  (3U)
/*! CH3OM - Channel 3 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH3OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH3OM_SHIFT)) & FTM_OUTMASK_CH3OM_MASK)

#define FTM_OUTMASK_CH4OM_MASK                   (0x10U)
#define FTM_OUTMASK_CH4OM_SHIFT                  (4U)
/*! CH4OM - Channel 4 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH4OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH4OM_SHIFT)) & FTM_OUTMASK_CH4OM_MASK)

#define FTM_OUTMASK_CH5OM_MASK                   (0x20U)
#define FTM_OUTMASK_CH5OM_SHIFT                  (5U)
/*! CH5OM - Channel 5 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH5OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH5OM_SHIFT)) & FTM_OUTMASK_CH5OM_MASK)

#define FTM_OUTMASK_CH6OM_MASK                   (0x40U)
#define FTM_OUTMASK_CH6OM_SHIFT                  (6U)
/*! CH6OM - Channel 6 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH6OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH6OM_SHIFT)) & FTM_OUTMASK_CH6OM_MASK)

#define FTM_OUTMASK_CH7OM_MASK                   (0x80U)
#define FTM_OUTMASK_CH7OM_SHIFT                  (7U)
/*! CH7OM - Channel 7 Output Mask
 *  0b0..Channel output is not masked. It continues to operate normally.
 *  0b1..Channel output is masked. It is forced to its inactive state.
 */
#define FTM_OUTMASK_CH7OM(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_OUTMASK_CH7OM_SHIFT)) & FTM_OUTMASK_CH7OM_MASK)
/*! @} */

/*! @name COMBINE - Function For Linked Channels */
/*! @{ */

#define FTM_COMBINE_COMBINE0_MASK                (0x1U)
#define FTM_COMBINE_COMBINE0_SHIFT               (0U)
/*! COMBINE0 - Combine Channels For n = 0 */
#define FTM_COMBINE_COMBINE0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE0_SHIFT)) & FTM_COMBINE_COMBINE0_MASK)

#define FTM_COMBINE_COMP0_MASK                   (0x2U)
#define FTM_COMBINE_COMP0_SHIFT                  (1U)
/*! COMP0 - Complement Of Channel (n) For n = 0
 *  0b0..If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode, the channel (n+1) output
 *       is the same as the channel (n) output. If the channel (n+1) is in Output Compare Mode, EPWM or CPWM, the
 *       channel (n+1) output is independent from channel (n) output.
 *  0b1..The channel (n+1) output is the complement of the channel (n) output.
 */
#define FTM_COMBINE_COMP0(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP0_SHIFT)) & FTM_COMBINE_COMP0_MASK)

#define FTM_COMBINE_DECAPEN0_MASK                (0x4U)
#define FTM_COMBINE_DECAPEN0_SHIFT               (2U)
/*! DECAPEN0 - Dual Edge Capture Mode Enable For n = 0 */
#define FTM_COMBINE_DECAPEN0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN0_SHIFT)) & FTM_COMBINE_DECAPEN0_MASK)

#define FTM_COMBINE_DECAP0_MASK                  (0x8U)
#define FTM_COMBINE_DECAP0_SHIFT                 (3U)
/*! DECAP0 - Dual Edge Capture Mode Captures For n = 0
 *  0b0..The dual edge captures are inactive.
 *  0b1..The dual edge captures are active.
 */
#define FTM_COMBINE_DECAP0(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP0_SHIFT)) & FTM_COMBINE_DECAP0_MASK)

#define FTM_COMBINE_DTEN0_MASK                   (0x10U)
#define FTM_COMBINE_DTEN0_SHIFT                  (4U)
/*! DTEN0 - Deadtime Enable For n = 0
 *  0b0..The deadtime insertion in this pair of channels is disabled.
 *  0b1..The deadtime insertion in this pair of channels is enabled.
 */
#define FTM_COMBINE_DTEN0(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN0_SHIFT)) & FTM_COMBINE_DTEN0_MASK)

#define FTM_COMBINE_SYNCEN0_MASK                 (0x20U)
#define FTM_COMBINE_SYNCEN0_SHIFT                (5U)
/*! SYNCEN0 - Synchronization Enable For n = 0
 *  0b0..The PWM synchronization in this pair of channels is disabled.
 *  0b1..The PWM synchronization in this pair of channels is enabled.
 */
#define FTM_COMBINE_SYNCEN0(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN0_SHIFT)) & FTM_COMBINE_SYNCEN0_MASK)

#define FTM_COMBINE_FAULTEN0_MASK                (0x40U)
#define FTM_COMBINE_FAULTEN0_SHIFT               (6U)
/*! FAULTEN0 - Fault Control Enable For n = 0
 *  0b0..The fault control in this pair of channels is disabled.
 *  0b1..The fault control in this pair of channels is enabled.
 */
#define FTM_COMBINE_FAULTEN0(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN0_SHIFT)) & FTM_COMBINE_FAULTEN0_MASK)

#define FTM_COMBINE_COMBINE1_MASK                (0x100U)
#define FTM_COMBINE_COMBINE1_SHIFT               (8U)
/*! COMBINE1 - Combine Channels For n = 2 */
#define FTM_COMBINE_COMBINE1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE1_SHIFT)) & FTM_COMBINE_COMBINE1_MASK)

#define FTM_COMBINE_COMP1_MASK                   (0x200U)
#define FTM_COMBINE_COMP1_SHIFT                  (9U)
/*! COMP1 - Complement Of Channel (n) For n = 2
 *  0b0..If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode, the channel (n+1) output
 *       is the same as the channel (n) output. If the channel (n+1) is in Output Compare Mode, EPWM or CPWM, the
 *       channel (n+1) output is independent from channel (n) output.
 *  0b1..The channel (n+1) output is the complement of the channel (n) output.
 */
#define FTM_COMBINE_COMP1(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP1_SHIFT)) & FTM_COMBINE_COMP1_MASK)

#define FTM_COMBINE_DECAPEN1_MASK                (0x400U)
#define FTM_COMBINE_DECAPEN1_SHIFT               (10U)
/*! DECAPEN1 - Dual Edge Capture Mode Enable For n = 2 */
#define FTM_COMBINE_DECAPEN1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN1_SHIFT)) & FTM_COMBINE_DECAPEN1_MASK)

#define FTM_COMBINE_DECAP1_MASK                  (0x800U)
#define FTM_COMBINE_DECAP1_SHIFT                 (11U)
/*! DECAP1 - Dual Edge Capture Mode Captures For n = 2
 *  0b0..The dual edge captures are inactive.
 *  0b1..The dual edge captures are active.
 */
#define FTM_COMBINE_DECAP1(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP1_SHIFT)) & FTM_COMBINE_DECAP1_MASK)

#define FTM_COMBINE_DTEN1_MASK                   (0x1000U)
#define FTM_COMBINE_DTEN1_SHIFT                  (12U)
/*! DTEN1 - Deadtime Enable For n = 2
 *  0b0..The deadtime insertion in this pair of channels is disabled.
 *  0b1..The deadtime insertion in this pair of channels is enabled.
 */
#define FTM_COMBINE_DTEN1(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN1_SHIFT)) & FTM_COMBINE_DTEN1_MASK)

#define FTM_COMBINE_SYNCEN1_MASK                 (0x2000U)
#define FTM_COMBINE_SYNCEN1_SHIFT                (13U)
/*! SYNCEN1 - Synchronization Enable For n = 2
 *  0b0..The PWM synchronization in this pair of channels is disabled.
 *  0b1..The PWM synchronization in this pair of channels is enabled.
 */
#define FTM_COMBINE_SYNCEN1(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN1_SHIFT)) & FTM_COMBINE_SYNCEN1_MASK)

#define FTM_COMBINE_FAULTEN1_MASK                (0x4000U)
#define FTM_COMBINE_FAULTEN1_SHIFT               (14U)
/*! FAULTEN1 - Fault Control Enable For n = 2
 *  0b0..The fault control in this pair of channels is disabled.
 *  0b1..The fault control in this pair of channels is enabled.
 */
#define FTM_COMBINE_FAULTEN1(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN1_SHIFT)) & FTM_COMBINE_FAULTEN1_MASK)

#define FTM_COMBINE_COMBINE2_MASK                (0x10000U)
#define FTM_COMBINE_COMBINE2_SHIFT               (16U)
/*! COMBINE2 - Combine Channels For n = 4 */
#define FTM_COMBINE_COMBINE2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE2_SHIFT)) & FTM_COMBINE_COMBINE2_MASK)

#define FTM_COMBINE_COMP2_MASK                   (0x20000U)
#define FTM_COMBINE_COMP2_SHIFT                  (17U)
/*! COMP2 - Complement Of Channel (n) For n = 4
 *  0b0..If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode, the channel (n+1) output
 *       is the same as the channel (n) output. If the channel (n+1) is in Output Compare Mode, EPWM or CPWM, the
 *       channel (n+1) output is independent from channel (n) output.
 *  0b1..The channel (n+1) output is the complement of the channel (n) output.
 */
#define FTM_COMBINE_COMP2(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP2_SHIFT)) & FTM_COMBINE_COMP2_MASK)

#define FTM_COMBINE_DECAPEN2_MASK                (0x40000U)
#define FTM_COMBINE_DECAPEN2_SHIFT               (18U)
/*! DECAPEN2 - Dual Edge Capture Mode Enable For n = 4 */
#define FTM_COMBINE_DECAPEN2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN2_SHIFT)) & FTM_COMBINE_DECAPEN2_MASK)

#define FTM_COMBINE_DECAP2_MASK                  (0x80000U)
#define FTM_COMBINE_DECAP2_SHIFT                 (19U)
/*! DECAP2 - Dual Edge Capture Mode Captures For n = 4
 *  0b0..The dual edge captures are inactive.
 *  0b1..The dual edge captures are active.
 */
#define FTM_COMBINE_DECAP2(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP2_SHIFT)) & FTM_COMBINE_DECAP2_MASK)

#define FTM_COMBINE_DTEN2_MASK                   (0x100000U)
#define FTM_COMBINE_DTEN2_SHIFT                  (20U)
/*! DTEN2 - Deadtime Enable For n = 4
 *  0b0..The deadtime insertion in this pair of channels is disabled.
 *  0b1..The deadtime insertion in this pair of channels is enabled.
 */
#define FTM_COMBINE_DTEN2(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN2_SHIFT)) & FTM_COMBINE_DTEN2_MASK)

#define FTM_COMBINE_SYNCEN2_MASK                 (0x200000U)
#define FTM_COMBINE_SYNCEN2_SHIFT                (21U)
/*! SYNCEN2 - Synchronization Enable For n = 4
 *  0b0..The PWM synchronization in this pair of channels is disabled.
 *  0b1..The PWM synchronization in this pair of channels is enabled.
 */
#define FTM_COMBINE_SYNCEN2(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN2_SHIFT)) & FTM_COMBINE_SYNCEN2_MASK)

#define FTM_COMBINE_FAULTEN2_MASK                (0x400000U)
#define FTM_COMBINE_FAULTEN2_SHIFT               (22U)
/*! FAULTEN2 - Fault Control Enable For n = 4
 *  0b0..The fault control in this pair of channels is disabled.
 *  0b1..The fault control in this pair of channels is enabled.
 */
#define FTM_COMBINE_FAULTEN2(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN2_SHIFT)) & FTM_COMBINE_FAULTEN2_MASK)

#define FTM_COMBINE_COMBINE3_MASK                (0x1000000U)
#define FTM_COMBINE_COMBINE3_SHIFT               (24U)
/*! COMBINE3 - Combine Channels For n = 6 */
#define FTM_COMBINE_COMBINE3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMBINE3_SHIFT)) & FTM_COMBINE_COMBINE3_MASK)

#define FTM_COMBINE_COMP3_MASK                   (0x2000000U)
#define FTM_COMBINE_COMP3_SHIFT                  (25U)
/*! COMP3 - Complement Of Channel (n) for n = 6
 *  0b0..If the channels (n) and (n+1) are in Combine Mode or Modified Combine PWM Mode, the channel (n+1) output
 *       is the same as the channel (n) output. If the channel (n+1) is in Output Compare Mode, EPWM or CPWM, the
 *       channel (n+1) output is independent from channel (n) output.
 *  0b1..The channel (n+1) output is the complement of the channel (n) output.
 */
#define FTM_COMBINE_COMP3(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_COMP3_SHIFT)) & FTM_COMBINE_COMP3_MASK)

#define FTM_COMBINE_DECAPEN3_MASK                (0x4000000U)
#define FTM_COMBINE_DECAPEN3_SHIFT               (26U)
/*! DECAPEN3 - Dual Edge Capture Mode Enable For n = 6 */
#define FTM_COMBINE_DECAPEN3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAPEN3_SHIFT)) & FTM_COMBINE_DECAPEN3_MASK)

#define FTM_COMBINE_DECAP3_MASK                  (0x8000000U)
#define FTM_COMBINE_DECAP3_SHIFT                 (27U)
/*! DECAP3 - Dual Edge Capture Mode Captures For n = 6
 *  0b0..The dual edge captures are inactive.
 *  0b1..The dual edge captures are active.
 */
#define FTM_COMBINE_DECAP3(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DECAP3_SHIFT)) & FTM_COMBINE_DECAP3_MASK)

#define FTM_COMBINE_DTEN3_MASK                   (0x10000000U)
#define FTM_COMBINE_DTEN3_SHIFT                  (28U)
/*! DTEN3 - Deadtime Enable For n = 6
 *  0b0..The deadtime insertion in this pair of channels is disabled.
 *  0b1..The deadtime insertion in this pair of channels is enabled.
 */
#define FTM_COMBINE_DTEN3(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_DTEN3_SHIFT)) & FTM_COMBINE_DTEN3_MASK)

#define FTM_COMBINE_SYNCEN3_MASK                 (0x20000000U)
#define FTM_COMBINE_SYNCEN3_SHIFT                (29U)
/*! SYNCEN3 - Synchronization Enable For n = 6
 *  0b0..The PWM synchronization in this pair of channels is disabled.
 *  0b1..The PWM synchronization in this pair of channels is enabled.
 */
#define FTM_COMBINE_SYNCEN3(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_SYNCEN3_SHIFT)) & FTM_COMBINE_SYNCEN3_MASK)

#define FTM_COMBINE_FAULTEN3_MASK                (0x40000000U)
#define FTM_COMBINE_FAULTEN3_SHIFT               (30U)
/*! FAULTEN3 - Fault Control Enable For n = 6
 *  0b0..The fault control in this pair of channels is disabled.
 *  0b1..The fault control in this pair of channels is enabled.
 */
#define FTM_COMBINE_FAULTEN3(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_COMBINE_FAULTEN3_SHIFT)) & FTM_COMBINE_FAULTEN3_MASK)
/*! @} */

/*! @name DEADTIME - Deadtime Configuration */
/*! @{ */

#define FTM_DEADTIME_DTVAL_MASK                  (0x3FU)
#define FTM_DEADTIME_DTVAL_SHIFT                 (0U)
/*! DTVAL - Deadtime Value */
#define FTM_DEADTIME_DTVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_DEADTIME_DTVAL_SHIFT)) & FTM_DEADTIME_DTVAL_MASK)

#define FTM_DEADTIME_DTPS_MASK                   (0xC0U)
#define FTM_DEADTIME_DTPS_SHIFT                  (6U)
/*! DTPS - Deadtime Prescaler Value
 *  0b0x..Divide the FTM input clock by 1.
 *  0b10..Divide the FTM input clock by 4.
 *  0b11..Divide the FTM input clock by 16.
 */
#define FTM_DEADTIME_DTPS(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_DEADTIME_DTPS_SHIFT)) & FTM_DEADTIME_DTPS_MASK)
/*! @} */

/*! @name EXTTRIG - FTM External Trigger */
/*! @{ */

#define FTM_EXTTRIG_CH2TRIG_MASK                 (0x1U)
#define FTM_EXTTRIG_CH2TRIG_SHIFT                (0U)
/*! CH2TRIG - Channel 2 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH2TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH2TRIG_SHIFT)) & FTM_EXTTRIG_CH2TRIG_MASK)

#define FTM_EXTTRIG_CH3TRIG_MASK                 (0x2U)
#define FTM_EXTTRIG_CH3TRIG_SHIFT                (1U)
/*! CH3TRIG - Channel 3 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH3TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH3TRIG_SHIFT)) & FTM_EXTTRIG_CH3TRIG_MASK)

#define FTM_EXTTRIG_CH4TRIG_MASK                 (0x4U)
#define FTM_EXTTRIG_CH4TRIG_SHIFT                (2U)
/*! CH4TRIG - Channel 4 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH4TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH4TRIG_SHIFT)) & FTM_EXTTRIG_CH4TRIG_MASK)

#define FTM_EXTTRIG_CH5TRIG_MASK                 (0x8U)
#define FTM_EXTTRIG_CH5TRIG_SHIFT                (3U)
/*! CH5TRIG - Channel 5 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH5TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH5TRIG_SHIFT)) & FTM_EXTTRIG_CH5TRIG_MASK)

#define FTM_EXTTRIG_CH0TRIG_MASK                 (0x10U)
#define FTM_EXTTRIG_CH0TRIG_SHIFT                (4U)
/*! CH0TRIG - Channel 0 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH0TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH0TRIG_SHIFT)) & FTM_EXTTRIG_CH0TRIG_MASK)

#define FTM_EXTTRIG_CH1TRIG_MASK                 (0x20U)
#define FTM_EXTTRIG_CH1TRIG_SHIFT                (5U)
/*! CH1TRIG - Channel 1 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH1TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH1TRIG_SHIFT)) & FTM_EXTTRIG_CH1TRIG_MASK)

#define FTM_EXTTRIG_INITTRIGEN_MASK              (0x40U)
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             (6U)
/*! INITTRIGEN - Initialization Trigger Enable
 *  0b0..The generation of initialization trigger is disabled.
 *  0b1..The generation of initialization trigger is enabled.
 */
#define FTM_EXTTRIG_INITTRIGEN(x)                (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_INITTRIGEN_SHIFT)) & FTM_EXTTRIG_INITTRIGEN_MASK)

#define FTM_EXTTRIG_TRIGF_MASK                   (0x80U)
#define FTM_EXTTRIG_TRIGF_SHIFT                  (7U)
/*! TRIGF - Channel Trigger Flag
 *  0b0..No channel trigger was generated.
 *  0b1..A channel trigger was generated.
 */
#define FTM_EXTTRIG_TRIGF(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_TRIGF_SHIFT)) & FTM_EXTTRIG_TRIGF_MASK)

#define FTM_EXTTRIG_CH6TRIG_MASK                 (0x100U)
#define FTM_EXTTRIG_CH6TRIG_SHIFT                (8U)
/*! CH6TRIG - Channel 6 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH6TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH6TRIG_SHIFT)) & FTM_EXTTRIG_CH6TRIG_MASK)

#define FTM_EXTTRIG_CH7TRIG_MASK                 (0x200U)
#define FTM_EXTTRIG_CH7TRIG_SHIFT                (9U)
/*! CH7TRIG - Channel 7 External Trigger Enable
 *  0b0..The generation of this external trigger is disabled.
 *  0b1..The generation of this external trigger is enabled.
 */
#define FTM_EXTTRIG_CH7TRIG(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_EXTTRIG_CH7TRIG_SHIFT)) & FTM_EXTTRIG_CH7TRIG_MASK)
/*! @} */

/*! @name POL - Channels Polarity */
/*! @{ */

#define FTM_POL_POL0_MASK                        (0x1U)
#define FTM_POL_POL0_SHIFT                       (0U)
/*! POL0 - Channel 0 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL0(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL0_SHIFT)) & FTM_POL_POL0_MASK)

#define FTM_POL_POL1_MASK                        (0x2U)
#define FTM_POL_POL1_SHIFT                       (1U)
/*! POL1 - Channel 1 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL1(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL1_SHIFT)) & FTM_POL_POL1_MASK)

#define FTM_POL_POL2_MASK                        (0x4U)
#define FTM_POL_POL2_SHIFT                       (2U)
/*! POL2 - Channel 2 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL2(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL2_SHIFT)) & FTM_POL_POL2_MASK)

#define FTM_POL_POL3_MASK                        (0x8U)
#define FTM_POL_POL3_SHIFT                       (3U)
/*! POL3 - Channel 3 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL3(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL3_SHIFT)) & FTM_POL_POL3_MASK)

#define FTM_POL_POL4_MASK                        (0x10U)
#define FTM_POL_POL4_SHIFT                       (4U)
/*! POL4 - Channel 4 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL4(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL4_SHIFT)) & FTM_POL_POL4_MASK)

#define FTM_POL_POL5_MASK                        (0x20U)
#define FTM_POL_POL5_SHIFT                       (5U)
/*! POL5 - Channel 5 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL5(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL5_SHIFT)) & FTM_POL_POL5_MASK)

#define FTM_POL_POL6_MASK                        (0x40U)
#define FTM_POL_POL6_SHIFT                       (6U)
/*! POL6 - Channel 6 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL6(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL6_SHIFT)) & FTM_POL_POL6_MASK)

#define FTM_POL_POL7_MASK                        (0x80U)
#define FTM_POL_POL7_SHIFT                       (7U)
/*! POL7 - Channel 7 Polarity
 *  0b0..The channel polarity is active high.
 *  0b1..The channel polarity is active low.
 */
#define FTM_POL_POL7(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_POL_POL7_SHIFT)) & FTM_POL_POL7_MASK)
/*! @} */

/*! @name FMS - Fault Mode Status */
/*! @{ */

#define FTM_FMS_FAULTF0_MASK                     (0x1U)
#define FTM_FMS_FAULTF0_SHIFT                    (0U)
/*! FAULTF0 - Fault Detection Flag 0
 *  0b0..No fault condition was detected at the fault input.
 *  0b1..A fault condition was detected at the fault input.
 */
#define FTM_FMS_FAULTF0(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF0_SHIFT)) & FTM_FMS_FAULTF0_MASK)

#define FTM_FMS_FAULTF1_MASK                     (0x2U)
#define FTM_FMS_FAULTF1_SHIFT                    (1U)
/*! FAULTF1 - Fault Detection Flag 1
 *  0b0..No fault condition was detected at the fault input.
 *  0b1..A fault condition was detected at the fault input.
 */
#define FTM_FMS_FAULTF1(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF1_SHIFT)) & FTM_FMS_FAULTF1_MASK)

#define FTM_FMS_FAULTF2_MASK                     (0x4U)
#define FTM_FMS_FAULTF2_SHIFT                    (2U)
/*! FAULTF2 - Fault Detection Flag 2
 *  0b0..No fault condition was detected at the fault input.
 *  0b1..A fault condition was detected at the fault input.
 */
#define FTM_FMS_FAULTF2(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF2_SHIFT)) & FTM_FMS_FAULTF2_MASK)

#define FTM_FMS_FAULTF3_MASK                     (0x8U)
#define FTM_FMS_FAULTF3_SHIFT                    (3U)
/*! FAULTF3 - Fault Detection Flag 3
 *  0b0..No fault condition was detected at the fault input.
 *  0b1..A fault condition was detected at the fault input.
 */
#define FTM_FMS_FAULTF3(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF3_SHIFT)) & FTM_FMS_FAULTF3_MASK)

#define FTM_FMS_FAULTIN_MASK                     (0x20U)
#define FTM_FMS_FAULTIN_SHIFT                    (5U)
/*! FAULTIN - Fault Inputs
 *  0b0..The logic OR of the enabled fault inputs is 0.
 *  0b1..The logic OR of the enabled fault inputs is 1.
 */
#define FTM_FMS_FAULTIN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTIN_SHIFT)) & FTM_FMS_FAULTIN_MASK)

#define FTM_FMS_WPEN_MASK                        (0x40U)
#define FTM_FMS_WPEN_SHIFT                       (6U)
/*! WPEN - Write Protection Enable
 *  0b0..Write protection is disabled. Write protected bits can be written.
 *  0b1..Write protection is enabled. Write protected bits cannot be written.
 */
#define FTM_FMS_WPEN(x)                          (((uint32_t)(((uint32_t)(x)) << FTM_FMS_WPEN_SHIFT)) & FTM_FMS_WPEN_MASK)

#define FTM_FMS_FAULTF_MASK                      (0x80U)
#define FTM_FMS_FAULTF_SHIFT                     (7U)
/*! FAULTF - Fault Detection Flag
 *  0b0..No fault condition was detected.
 *  0b1..A fault condition was detected.
 */
#define FTM_FMS_FAULTF(x)                        (((uint32_t)(((uint32_t)(x)) << FTM_FMS_FAULTF_SHIFT)) & FTM_FMS_FAULTF_MASK)
/*! @} */

/*! @name FILTER - Input Capture Filter Control */
/*! @{ */

#define FTM_FILTER_CH0FVAL_MASK                  (0xFU)
#define FTM_FILTER_CH0FVAL_SHIFT                 (0U)
/*! CH0FVAL - Channel 0 Input Filter */
#define FTM_FILTER_CH0FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH0FVAL_SHIFT)) & FTM_FILTER_CH0FVAL_MASK)

#define FTM_FILTER_CH1FVAL_MASK                  (0xF0U)
#define FTM_FILTER_CH1FVAL_SHIFT                 (4U)
/*! CH1FVAL - Channel 1 Input Filter */
#define FTM_FILTER_CH1FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH1FVAL_SHIFT)) & FTM_FILTER_CH1FVAL_MASK)

#define FTM_FILTER_CH2FVAL_MASK                  (0xF00U)
#define FTM_FILTER_CH2FVAL_SHIFT                 (8U)
/*! CH2FVAL - Channel 2 Input Filter */
#define FTM_FILTER_CH2FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH2FVAL_SHIFT)) & FTM_FILTER_CH2FVAL_MASK)

#define FTM_FILTER_CH3FVAL_MASK                  (0xF000U)
#define FTM_FILTER_CH3FVAL_SHIFT                 (12U)
/*! CH3FVAL - Channel 3 Input Filter */
#define FTM_FILTER_CH3FVAL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FILTER_CH3FVAL_SHIFT)) & FTM_FILTER_CH3FVAL_MASK)
/*! @} */

/*! @name FLTCTRL - Fault Control */
/*! @{ */

#define FTM_FLTCTRL_FAULT0EN_MASK                (0x1U)
#define FTM_FLTCTRL_FAULT0EN_SHIFT               (0U)
/*! FAULT0EN - Fault Input 0 Enable
 *  0b0..Fault input is disabled.
 *  0b1..Fault input is enabled.
 */
#define FTM_FLTCTRL_FAULT0EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT0EN_SHIFT)) & FTM_FLTCTRL_FAULT0EN_MASK)

#define FTM_FLTCTRL_FAULT1EN_MASK                (0x2U)
#define FTM_FLTCTRL_FAULT1EN_SHIFT               (1U)
/*! FAULT1EN - Fault Input 1 Enable
 *  0b0..Fault input is disabled.
 *  0b1..Fault input is enabled.
 */
#define FTM_FLTCTRL_FAULT1EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT1EN_SHIFT)) & FTM_FLTCTRL_FAULT1EN_MASK)

#define FTM_FLTCTRL_FAULT2EN_MASK                (0x4U)
#define FTM_FLTCTRL_FAULT2EN_SHIFT               (2U)
/*! FAULT2EN - Fault Input 2 Enable
 *  0b0..Fault input is disabled.
 *  0b1..Fault input is enabled.
 */
#define FTM_FLTCTRL_FAULT2EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT2EN_SHIFT)) & FTM_FLTCTRL_FAULT2EN_MASK)

#define FTM_FLTCTRL_FAULT3EN_MASK                (0x8U)
#define FTM_FLTCTRL_FAULT3EN_SHIFT               (3U)
/*! FAULT3EN - Fault Input 3 Enable
 *  0b0..Fault input is disabled.
 *  0b1..Fault input is enabled.
 */
#define FTM_FLTCTRL_FAULT3EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FAULT3EN_SHIFT)) & FTM_FLTCTRL_FAULT3EN_MASK)

#define FTM_FLTCTRL_FFLTR0EN_MASK                (0x10U)
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               (4U)
/*! FFLTR0EN - Fault Input 0 Filter Enable
 *  0b0..Fault input filter is disabled.
 *  0b1..Fault input filter is enabled.
 */
#define FTM_FLTCTRL_FFLTR0EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR0EN_SHIFT)) & FTM_FLTCTRL_FFLTR0EN_MASK)

#define FTM_FLTCTRL_FFLTR1EN_MASK                (0x20U)
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               (5U)
/*! FFLTR1EN - Fault Input 1 Filter Enable
 *  0b0..Fault input filter is disabled.
 *  0b1..Fault input filter is enabled.
 */
#define FTM_FLTCTRL_FFLTR1EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR1EN_SHIFT)) & FTM_FLTCTRL_FFLTR1EN_MASK)

#define FTM_FLTCTRL_FFLTR2EN_MASK                (0x40U)
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               (6U)
/*! FFLTR2EN - Fault Input 2 Filter Enable
 *  0b0..Fault input filter is disabled.
 *  0b1..Fault input filter is enabled.
 */
#define FTM_FLTCTRL_FFLTR2EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR2EN_SHIFT)) & FTM_FLTCTRL_FFLTR2EN_MASK)

#define FTM_FLTCTRL_FFLTR3EN_MASK                (0x80U)
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               (7U)
/*! FFLTR3EN - Fault Input 3 Filter Enable
 *  0b0..Fault input filter is disabled.
 *  0b1..Fault input filter is enabled.
 */
#define FTM_FLTCTRL_FFLTR3EN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFLTR3EN_SHIFT)) & FTM_FLTCTRL_FFLTR3EN_MASK)

#define FTM_FLTCTRL_FFVAL_MASK                   (0xF00U)
#define FTM_FLTCTRL_FFVAL_SHIFT                  (8U)
/*! FFVAL - Fault Input Filter */
#define FTM_FLTCTRL_FFVAL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FFVAL_SHIFT)) & FTM_FLTCTRL_FFVAL_MASK)

#define FTM_FLTCTRL_FSTATE_MASK                  (0x8000U)
#define FTM_FLTCTRL_FSTATE_SHIFT                 (15U)
/*! FSTATE - Fault output state
 *  0b0..FTM outputs will be placed into safe values when fault events in ongoing (defined by POL bits).
 *  0b1..FTM outputs will be tri-stated when fault event is ongoing
 */
#define FTM_FLTCTRL_FSTATE(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTCTRL_FSTATE_SHIFT)) & FTM_FLTCTRL_FSTATE_MASK)
/*! @} */

/*! @name QDCTRL - Quadrature Decoder Control And Status */
/*! @{ */

#define FTM_QDCTRL_QUADEN_MASK                   (0x1U)
#define FTM_QDCTRL_QUADEN_SHIFT                  (0U)
/*! QUADEN - Quadrature Decoder Mode Enable
 *  0b0..Quadrature Decoder mode is disabled.
 *  0b1..Quadrature Decoder mode is enabled.
 */
#define FTM_QDCTRL_QUADEN(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADEN_SHIFT)) & FTM_QDCTRL_QUADEN_MASK)

#define FTM_QDCTRL_TOFDIR_MASK                   (0x2U)
#define FTM_QDCTRL_TOFDIR_SHIFT                  (1U)
/*! TOFDIR - Timer Overflow Direction In Quadrature Decoder Mode
 *  0b0..TOF bit was set on the bottom of counting. There was an FTM counter decrement and FTM counter changes
 *       from its minimum value (CNTIN register) to its maximum value (MOD register).
 *  0b1..TOF bit was set on the top of counting. There was an FTM counter increment and FTM counter changes from
 *       its maximum value (MOD register) to its minimum value (CNTIN register).
 */
#define FTM_QDCTRL_TOFDIR(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_TOFDIR_SHIFT)) & FTM_QDCTRL_TOFDIR_MASK)

#define FTM_QDCTRL_QUADIR_MASK                   (0x4U)
#define FTM_QDCTRL_QUADIR_SHIFT                  (2U)
/*! QUADIR - FTM Counter Direction In Quadrature Decoder Mode
 *  0b0..Counting direction is decreasing (FTM counter decrement).
 *  0b1..Counting direction is increasing (FTM counter increment).
 */
#define FTM_QDCTRL_QUADIR(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADIR_SHIFT)) & FTM_QDCTRL_QUADIR_MASK)

#define FTM_QDCTRL_QUADMODE_MASK                 (0x8U)
#define FTM_QDCTRL_QUADMODE_SHIFT                (3U)
/*! QUADMODE - Quadrature Decoder Mode
 *  0b0..Phase A and phase B encoding mode.
 *  0b1..Count and direction encoding mode.
 */
#define FTM_QDCTRL_QUADMODE(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_QUADMODE_SHIFT)) & FTM_QDCTRL_QUADMODE_MASK)

#define FTM_QDCTRL_PHBPOL_MASK                   (0x10U)
#define FTM_QDCTRL_PHBPOL_SHIFT                  (4U)
/*! PHBPOL - Phase B Input Polarity
 *  0b0..Normal polarity. Phase B input signal is not inverted before identifying the rising and falling edges of this signal.
 *  0b1..Inverted polarity. Phase B input signal is inverted before identifying the rising and falling edges of this signal.
 */
#define FTM_QDCTRL_PHBPOL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHBPOL_SHIFT)) & FTM_QDCTRL_PHBPOL_MASK)

#define FTM_QDCTRL_PHAPOL_MASK                   (0x20U)
#define FTM_QDCTRL_PHAPOL_SHIFT                  (5U)
/*! PHAPOL - Phase A Input Polarity
 *  0b0..Normal polarity. Phase A input signal is not inverted before identifying the rising and falling edges of this signal.
 *  0b1..Inverted polarity. Phase A input signal is inverted before identifying the rising and falling edges of this signal.
 */
#define FTM_QDCTRL_PHAPOL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHAPOL_SHIFT)) & FTM_QDCTRL_PHAPOL_MASK)

#define FTM_QDCTRL_PHBFLTREN_MASK                (0x40U)
#define FTM_QDCTRL_PHBFLTREN_SHIFT               (6U)
/*! PHBFLTREN - Phase B Input Filter Enable
 *  0b0..Phase B input filter is disabled.
 *  0b1..Phase B input filter is enabled.
 */
#define FTM_QDCTRL_PHBFLTREN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHBFLTREN_SHIFT)) & FTM_QDCTRL_PHBFLTREN_MASK)

#define FTM_QDCTRL_PHAFLTREN_MASK                (0x80U)
#define FTM_QDCTRL_PHAFLTREN_SHIFT               (7U)
/*! PHAFLTREN - Phase A Input Filter Enable
 *  0b0..Phase A input filter is disabled.
 *  0b1..Phase A input filter is enabled.
 */
#define FTM_QDCTRL_PHAFLTREN(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_QDCTRL_PHAFLTREN_SHIFT)) & FTM_QDCTRL_PHAFLTREN_MASK)
/*! @} */

/*! @name CONF - Configuration */
/*! @{ */

#define FTM_CONF_LDFQ_MASK                       (0x1FU)
#define FTM_CONF_LDFQ_SHIFT                      (0U)
/*! LDFQ - Frequency of the Reload Opportunities */
#define FTM_CONF_LDFQ(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_CONF_LDFQ_SHIFT)) & FTM_CONF_LDFQ_MASK)

#define FTM_CONF_BDMMODE_MASK                    (0xC0U)
#define FTM_CONF_BDMMODE_SHIFT                   (6U)
/*! BDMMODE - Debug Mode */
#define FTM_CONF_BDMMODE(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_CONF_BDMMODE_SHIFT)) & FTM_CONF_BDMMODE_MASK)

#define FTM_CONF_GTBEEN_MASK                     (0x200U)
#define FTM_CONF_GTBEEN_SHIFT                    (9U)
/*! GTBEEN - Global Time Base Enable
 *  0b0..Use of an external global time base is disabled.
 *  0b1..Use of an external global time base is enabled.
 */
#define FTM_CONF_GTBEEN(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_CONF_GTBEEN_SHIFT)) & FTM_CONF_GTBEEN_MASK)

#define FTM_CONF_GTBEOUT_MASK                    (0x400U)
#define FTM_CONF_GTBEOUT_SHIFT                   (10U)
/*! GTBEOUT - Global Time Base Output
 *  0b0..A global time base signal generation is disabled.
 *  0b1..A global time base signal generation is enabled.
 */
#define FTM_CONF_GTBEOUT(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_CONF_GTBEOUT_SHIFT)) & FTM_CONF_GTBEOUT_MASK)

#define FTM_CONF_ITRIGR_MASK                     (0x800U)
#define FTM_CONF_ITRIGR_SHIFT                    (11U)
/*! ITRIGR - Initialization trigger on Reload Point
 *  0b0..Initialization trigger is generated on counter wrap events.
 *  0b1..Initialization trigger is generated when a reload point is reached.
 */
#define FTM_CONF_ITRIGR(x)                       (((uint32_t)(((uint32_t)(x)) << FTM_CONF_ITRIGR_SHIFT)) & FTM_CONF_ITRIGR_MASK)
/*! @} */

/*! @name FLTPOL - FTM Fault Input Polarity */
/*! @{ */

#define FTM_FLTPOL_FLT0POL_MASK                  (0x1U)
#define FTM_FLTPOL_FLT0POL_SHIFT                 (0U)
/*! FLT0POL - Fault Input 0 Polarity
 *  0b0..The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *  0b1..The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
#define FTM_FLTPOL_FLT0POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT0POL_SHIFT)) & FTM_FLTPOL_FLT0POL_MASK)

#define FTM_FLTPOL_FLT1POL_MASK                  (0x2U)
#define FTM_FLTPOL_FLT1POL_SHIFT                 (1U)
/*! FLT1POL - Fault Input 1 Polarity
 *  0b0..The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *  0b1..The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
#define FTM_FLTPOL_FLT1POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT1POL_SHIFT)) & FTM_FLTPOL_FLT1POL_MASK)

#define FTM_FLTPOL_FLT2POL_MASK                  (0x4U)
#define FTM_FLTPOL_FLT2POL_SHIFT                 (2U)
/*! FLT2POL - Fault Input 2 Polarity
 *  0b0..The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *  0b1..The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
#define FTM_FLTPOL_FLT2POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT2POL_SHIFT)) & FTM_FLTPOL_FLT2POL_MASK)

#define FTM_FLTPOL_FLT3POL_MASK                  (0x8U)
#define FTM_FLTPOL_FLT3POL_SHIFT                 (3U)
/*! FLT3POL - Fault Input 3 Polarity
 *  0b0..The fault input polarity is active high. A 1 at the fault input indicates a fault.
 *  0b1..The fault input polarity is active low. A 0 at the fault input indicates a fault.
 */
#define FTM_FLTPOL_FLT3POL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_FLTPOL_FLT3POL_SHIFT)) & FTM_FLTPOL_FLT3POL_MASK)
/*! @} */

/*! @name SYNCONF - Synchronization Configuration */
/*! @{ */

#define FTM_SYNCONF_HWTRIGMODE_MASK              (0x1U)
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             (0U)
/*! HWTRIGMODE - Hardware Trigger Mode
 *  0b0..FTM clears the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 *  0b1..FTM does not clear the TRIGj bit when the hardware trigger j is detected, where j = 0, 1,2.
 */
#define FTM_SYNCONF_HWTRIGMODE(x)                (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWTRIGMODE_SHIFT)) & FTM_SYNCONF_HWTRIGMODE_MASK)

#define FTM_SYNCONF_CNTINC_MASK                  (0x4U)
#define FTM_SYNCONF_CNTINC_SHIFT                 (2U)
/*! CNTINC - CNTIN Register Synchronization
 *  0b0..CNTIN register is updated with its buffer value at all rising edges of FTM input clock.
 *  0b1..CNTIN register is updated with its buffer value by the PWM synchronization.
 */
#define FTM_SYNCONF_CNTINC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_CNTINC_SHIFT)) & FTM_SYNCONF_CNTINC_MASK)

#define FTM_SYNCONF_INVC_MASK                    (0x10U)
#define FTM_SYNCONF_INVC_SHIFT                   (4U)
/*! INVC - INVCTRL Register Synchronization
 *  0b0..INVCTRL register is updated with its buffer value at all rising edges of FTM input clock.
 *  0b1..INVCTRL register is updated with its buffer value by the PWM synchronization.
 */
#define FTM_SYNCONF_INVC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_INVC_SHIFT)) & FTM_SYNCONF_INVC_MASK)

#define FTM_SYNCONF_SWOC_MASK                    (0x20U)
#define FTM_SYNCONF_SWOC_SHIFT                   (5U)
/*! SWOC - SWOCTRL Register Synchronization
 *  0b0..SWOCTRL register is updated with its buffer value at all rising edges of FTM input clock.
 *  0b1..SWOCTRL register is updated with its buffer value by the PWM synchronization.
 */
#define FTM_SYNCONF_SWOC(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWOC_SHIFT)) & FTM_SYNCONF_SWOC_MASK)

#define FTM_SYNCONF_SYNCMODE_MASK                (0x80U)
#define FTM_SYNCONF_SYNCMODE_SHIFT               (7U)
/*! SYNCMODE - Synchronization Mode
 *  0b0..Legacy PWM synchronization is selected.
 *  0b1..Enhanced PWM synchronization is selected.
 */
#define FTM_SYNCONF_SYNCMODE(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SYNCMODE_SHIFT)) & FTM_SYNCONF_SYNCMODE_MASK)

#define FTM_SYNCONF_SWRSTCNT_MASK                (0x100U)
#define FTM_SYNCONF_SWRSTCNT_SHIFT               (8U)
/*! SWRSTCNT - FTM counter synchronization is activated by the software trigger
 *  0b0..The software trigger does not activate the FTM counter synchronization.
 *  0b1..The software trigger activates the FTM counter synchronization.
 */
#define FTM_SYNCONF_SWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWRSTCNT_SHIFT)) & FTM_SYNCONF_SWRSTCNT_MASK)

#define FTM_SYNCONF_SWWRBUF_MASK                 (0x200U)
#define FTM_SYNCONF_SWWRBUF_SHIFT                (9U)
/*! SWWRBUF - MOD, HCR, CNTIN, and CV registers synchronization is activated by the software trigger
 *  0b0..The software trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *  0b1..The software trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
#define FTM_SYNCONF_SWWRBUF(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWWRBUF_SHIFT)) & FTM_SYNCONF_SWWRBUF_MASK)

#define FTM_SYNCONF_SWOM_MASK                    (0x400U)
#define FTM_SYNCONF_SWOM_SHIFT                   (10U)
/*! SWOM - Output mask synchronization is activated by the software trigger
 *  0b0..The software trigger does not activate the OUTMASK register synchronization.
 *  0b1..The software trigger activates the OUTMASK register synchronization.
 */
#define FTM_SYNCONF_SWOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWOM_SHIFT)) & FTM_SYNCONF_SWOM_MASK)

#define FTM_SYNCONF_SWINVC_MASK                  (0x800U)
#define FTM_SYNCONF_SWINVC_SHIFT                 (11U)
/*! SWINVC - Inverting control synchronization is activated by the software trigger
 *  0b0..The software trigger does not activate the INVCTRL register synchronization.
 *  0b1..The software trigger activates the INVCTRL register synchronization.
 */
#define FTM_SYNCONF_SWINVC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWINVC_SHIFT)) & FTM_SYNCONF_SWINVC_MASK)

#define FTM_SYNCONF_SWSOC_MASK                   (0x1000U)
#define FTM_SYNCONF_SWSOC_SHIFT                  (12U)
/*! SWSOC - Software output control synchronization is activated by the software trigger
 *  0b0..The software trigger does not activate the SWOCTRL register synchronization.
 *  0b1..The software trigger activates the SWOCTRL register synchronization.
 */
#define FTM_SYNCONF_SWSOC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_SWSOC_SHIFT)) & FTM_SYNCONF_SWSOC_MASK)

#define FTM_SYNCONF_HWRSTCNT_MASK                (0x10000U)
#define FTM_SYNCONF_HWRSTCNT_SHIFT               (16U)
/*! HWRSTCNT - FTM counter synchronization is activated by a hardware trigger
 *  0b0..A hardware trigger does not activate the FTM counter synchronization.
 *  0b1..A hardware trigger activates the FTM counter synchronization.
 */
#define FTM_SYNCONF_HWRSTCNT(x)                  (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWRSTCNT_SHIFT)) & FTM_SYNCONF_HWRSTCNT_MASK)

#define FTM_SYNCONF_HWWRBUF_MASK                 (0x20000U)
#define FTM_SYNCONF_HWWRBUF_SHIFT                (17U)
/*! HWWRBUF - MOD, HCR, CNTIN, and CV registers synchronization is activated by a hardware trigger
 *  0b0..A hardware trigger does not activate MOD, HCR, CNTIN, and CV registers synchronization.
 *  0b1..A hardware trigger activates MOD, HCR, CNTIN, and CV registers synchronization.
 */
#define FTM_SYNCONF_HWWRBUF(x)                   (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWWRBUF_SHIFT)) & FTM_SYNCONF_HWWRBUF_MASK)

#define FTM_SYNCONF_HWOM_MASK                    (0x40000U)
#define FTM_SYNCONF_HWOM_SHIFT                   (18U)
/*! HWOM - Output mask synchronization is activated by a hardware trigger
 *  0b0..A hardware trigger does not activate the OUTMASK register synchronization.
 *  0b1..A hardware trigger activates the OUTMASK register synchronization.
 */
#define FTM_SYNCONF_HWOM(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWOM_SHIFT)) & FTM_SYNCONF_HWOM_MASK)

#define FTM_SYNCONF_HWINVC_MASK                  (0x80000U)
#define FTM_SYNCONF_HWINVC_SHIFT                 (19U)
/*! HWINVC - Inverting control synchronization is activated by a hardware trigger
 *  0b0..A hardware trigger does not activate the INVCTRL register synchronization.
 *  0b1..A hardware trigger activates the INVCTRL register synchronization.
 */
#define FTM_SYNCONF_HWINVC(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWINVC_SHIFT)) & FTM_SYNCONF_HWINVC_MASK)

#define FTM_SYNCONF_HWSOC_MASK                   (0x100000U)
#define FTM_SYNCONF_HWSOC_SHIFT                  (20U)
/*! HWSOC - Software output control synchronization is activated by a hardware trigger
 *  0b0..A hardware trigger does not activate the SWOCTRL register synchronization.
 *  0b1..A hardware trigger activates the SWOCTRL register synchronization.
 */
#define FTM_SYNCONF_HWSOC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SYNCONF_HWSOC_SHIFT)) & FTM_SYNCONF_HWSOC_MASK)
/*! @} */

/*! @name INVCTRL - FTM Inverting Control */
/*! @{ */

#define FTM_INVCTRL_INV0EN_MASK                  (0x1U)
#define FTM_INVCTRL_INV0EN_SHIFT                 (0U)
/*! INV0EN - Pair Channels 0 Inverting Enable
 *  0b0..Inverting is disabled.
 *  0b1..Inverting is enabled.
 */
#define FTM_INVCTRL_INV0EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV0EN_SHIFT)) & FTM_INVCTRL_INV0EN_MASK)

#define FTM_INVCTRL_INV1EN_MASK                  (0x2U)
#define FTM_INVCTRL_INV1EN_SHIFT                 (1U)
/*! INV1EN - Pair Channels 1 Inverting Enable
 *  0b0..Inverting is disabled.
 *  0b1..Inverting is enabled.
 */
#define FTM_INVCTRL_INV1EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV1EN_SHIFT)) & FTM_INVCTRL_INV1EN_MASK)

#define FTM_INVCTRL_INV2EN_MASK                  (0x4U)
#define FTM_INVCTRL_INV2EN_SHIFT                 (2U)
/*! INV2EN - Pair Channels 2 Inverting Enable
 *  0b0..Inverting is disabled.
 *  0b1..Inverting is enabled.
 */
#define FTM_INVCTRL_INV2EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV2EN_SHIFT)) & FTM_INVCTRL_INV2EN_MASK)

#define FTM_INVCTRL_INV3EN_MASK                  (0x8U)
#define FTM_INVCTRL_INV3EN_SHIFT                 (3U)
/*! INV3EN - Pair Channels 3 Inverting Enable
 *  0b0..Inverting is disabled.
 *  0b1..Inverting is enabled.
 */
#define FTM_INVCTRL_INV3EN(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_INVCTRL_INV3EN_SHIFT)) & FTM_INVCTRL_INV3EN_MASK)
/*! @} */

/*! @name SWOCTRL - FTM Software Output Control */
/*! @{ */

#define FTM_SWOCTRL_CH0OC_MASK                   (0x1U)
#define FTM_SWOCTRL_CH0OC_SHIFT                  (0U)
/*! CH0OC - Channel 0 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH0OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH0OC_SHIFT)) & FTM_SWOCTRL_CH0OC_MASK)

#define FTM_SWOCTRL_CH1OC_MASK                   (0x2U)
#define FTM_SWOCTRL_CH1OC_SHIFT                  (1U)
/*! CH1OC - Channel 1 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH1OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH1OC_SHIFT)) & FTM_SWOCTRL_CH1OC_MASK)

#define FTM_SWOCTRL_CH2OC_MASK                   (0x4U)
#define FTM_SWOCTRL_CH2OC_SHIFT                  (2U)
/*! CH2OC - Channel 2 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH2OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH2OC_SHIFT)) & FTM_SWOCTRL_CH2OC_MASK)

#define FTM_SWOCTRL_CH3OC_MASK                   (0x8U)
#define FTM_SWOCTRL_CH3OC_SHIFT                  (3U)
/*! CH3OC - Channel 3 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH3OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH3OC_SHIFT)) & FTM_SWOCTRL_CH3OC_MASK)

#define FTM_SWOCTRL_CH4OC_MASK                   (0x10U)
#define FTM_SWOCTRL_CH4OC_SHIFT                  (4U)
/*! CH4OC - Channel 4 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH4OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH4OC_SHIFT)) & FTM_SWOCTRL_CH4OC_MASK)

#define FTM_SWOCTRL_CH5OC_MASK                   (0x20U)
#define FTM_SWOCTRL_CH5OC_SHIFT                  (5U)
/*! CH5OC - Channel 5 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH5OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH5OC_SHIFT)) & FTM_SWOCTRL_CH5OC_MASK)

#define FTM_SWOCTRL_CH6OC_MASK                   (0x40U)
#define FTM_SWOCTRL_CH6OC_SHIFT                  (6U)
/*! CH6OC - Channel 6 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH6OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH6OC_SHIFT)) & FTM_SWOCTRL_CH6OC_MASK)

#define FTM_SWOCTRL_CH7OC_MASK                   (0x80U)
#define FTM_SWOCTRL_CH7OC_SHIFT                  (7U)
/*! CH7OC - Channel 7 Software Output Control Enable
 *  0b0..The channel output is not affected by software output control.
 *  0b1..The channel output is affected by software output control.
 */
#define FTM_SWOCTRL_CH7OC(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH7OC_SHIFT)) & FTM_SWOCTRL_CH7OC_MASK)

#define FTM_SWOCTRL_CH0OCV_MASK                  (0x100U)
#define FTM_SWOCTRL_CH0OCV_SHIFT                 (8U)
/*! CH0OCV - Channel 0 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH0OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH0OCV_SHIFT)) & FTM_SWOCTRL_CH0OCV_MASK)

#define FTM_SWOCTRL_CH1OCV_MASK                  (0x200U)
#define FTM_SWOCTRL_CH1OCV_SHIFT                 (9U)
/*! CH1OCV - Channel 1 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH1OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH1OCV_SHIFT)) & FTM_SWOCTRL_CH1OCV_MASK)

#define FTM_SWOCTRL_CH2OCV_MASK                  (0x400U)
#define FTM_SWOCTRL_CH2OCV_SHIFT                 (10U)
/*! CH2OCV - Channel 2 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH2OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH2OCV_SHIFT)) & FTM_SWOCTRL_CH2OCV_MASK)

#define FTM_SWOCTRL_CH3OCV_MASK                  (0x800U)
#define FTM_SWOCTRL_CH3OCV_SHIFT                 (11U)
/*! CH3OCV - Channel 3 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH3OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH3OCV_SHIFT)) & FTM_SWOCTRL_CH3OCV_MASK)

#define FTM_SWOCTRL_CH4OCV_MASK                  (0x1000U)
#define FTM_SWOCTRL_CH4OCV_SHIFT                 (12U)
/*! CH4OCV - Channel 4 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH4OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH4OCV_SHIFT)) & FTM_SWOCTRL_CH4OCV_MASK)

#define FTM_SWOCTRL_CH5OCV_MASK                  (0x2000U)
#define FTM_SWOCTRL_CH5OCV_SHIFT                 (13U)
/*! CH5OCV - Channel 5 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH5OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH5OCV_SHIFT)) & FTM_SWOCTRL_CH5OCV_MASK)

#define FTM_SWOCTRL_CH6OCV_MASK                  (0x4000U)
#define FTM_SWOCTRL_CH6OCV_SHIFT                 (14U)
/*! CH6OCV - Channel 6 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH6OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH6OCV_SHIFT)) & FTM_SWOCTRL_CH6OCV_MASK)

#define FTM_SWOCTRL_CH7OCV_MASK                  (0x8000U)
#define FTM_SWOCTRL_CH7OCV_SHIFT                 (15U)
/*! CH7OCV - Channel 7 Software Output Control Value
 *  0b0..The software output control forces 0 to the channel output.
 *  0b1..The software output control forces 1 to the channel output.
 */
#define FTM_SWOCTRL_CH7OCV(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_SWOCTRL_CH7OCV_SHIFT)) & FTM_SWOCTRL_CH7OCV_MASK)
/*! @} */

/*! @name PWMLOAD - FTM PWM Load */
/*! @{ */

#define FTM_PWMLOAD_CH0SEL_MASK                  (0x1U)
#define FTM_PWMLOAD_CH0SEL_SHIFT                 (0U)
/*! CH0SEL - Channel 0 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH0SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH0SEL_SHIFT)) & FTM_PWMLOAD_CH0SEL_MASK)

#define FTM_PWMLOAD_CH1SEL_MASK                  (0x2U)
#define FTM_PWMLOAD_CH1SEL_SHIFT                 (1U)
/*! CH1SEL - Channel 1 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH1SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH1SEL_SHIFT)) & FTM_PWMLOAD_CH1SEL_MASK)

#define FTM_PWMLOAD_CH2SEL_MASK                  (0x4U)
#define FTM_PWMLOAD_CH2SEL_SHIFT                 (2U)
/*! CH2SEL - Channel 2 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH2SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH2SEL_SHIFT)) & FTM_PWMLOAD_CH2SEL_MASK)

#define FTM_PWMLOAD_CH3SEL_MASK                  (0x8U)
#define FTM_PWMLOAD_CH3SEL_SHIFT                 (3U)
/*! CH3SEL - Channel 3 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH3SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH3SEL_SHIFT)) & FTM_PWMLOAD_CH3SEL_MASK)

#define FTM_PWMLOAD_CH4SEL_MASK                  (0x10U)
#define FTM_PWMLOAD_CH4SEL_SHIFT                 (4U)
/*! CH4SEL - Channel 4 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH4SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH4SEL_SHIFT)) & FTM_PWMLOAD_CH4SEL_MASK)

#define FTM_PWMLOAD_CH5SEL_MASK                  (0x20U)
#define FTM_PWMLOAD_CH5SEL_SHIFT                 (5U)
/*! CH5SEL - Channel 5 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH5SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH5SEL_SHIFT)) & FTM_PWMLOAD_CH5SEL_MASK)

#define FTM_PWMLOAD_CH6SEL_MASK                  (0x40U)
#define FTM_PWMLOAD_CH6SEL_SHIFT                 (6U)
/*! CH6SEL - Channel 6 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH6SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH6SEL_SHIFT)) & FTM_PWMLOAD_CH6SEL_MASK)

#define FTM_PWMLOAD_CH7SEL_MASK                  (0x80U)
#define FTM_PWMLOAD_CH7SEL_SHIFT                 (7U)
/*! CH7SEL - Channel 7 Select
 *  0b0..Channel match is not included as a reload opportunity.
 *  0b1..Channel match is included as a reload opportunity.
 */
#define FTM_PWMLOAD_CH7SEL(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_CH7SEL_SHIFT)) & FTM_PWMLOAD_CH7SEL_MASK)

#define FTM_PWMLOAD_HCSEL_MASK                   (0x100U)
#define FTM_PWMLOAD_HCSEL_SHIFT                  (8U)
/*! HCSEL - Half Cycle Select
 *  0b0..Half cycle reload is disabled and it is not considered as a reload opportunity.
 *  0b1..Half cycle reload is enabled and it is considered as a reload opportunity.
 */
#define FTM_PWMLOAD_HCSEL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_HCSEL_SHIFT)) & FTM_PWMLOAD_HCSEL_MASK)

#define FTM_PWMLOAD_LDOK_MASK                    (0x200U)
#define FTM_PWMLOAD_LDOK_SHIFT                   (9U)
/*! LDOK - Load Enable
 *  0b0..Loading updated values is disabled.
 *  0b1..Loading updated values is enabled.
 */
#define FTM_PWMLOAD_LDOK(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_LDOK_SHIFT)) & FTM_PWMLOAD_LDOK_MASK)

#define FTM_PWMLOAD_GLEN_MASK                    (0x400U)
#define FTM_PWMLOAD_GLEN_SHIFT                   (10U)
/*! GLEN - Global Load Enable
 *  0b0..Global Load Ok disabled.
 *  0b1..Global Load OK enabled. A pulse event on the module global load input sets the LDOK bit.
 */
#define FTM_PWMLOAD_GLEN(x)                      (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_GLEN_SHIFT)) & FTM_PWMLOAD_GLEN_MASK)

#define FTM_PWMLOAD_GLDOK_MASK                   (0x800U)
#define FTM_PWMLOAD_GLDOK_SHIFT                  (11U)
/*! GLDOK - Global Load OK
 *  0b0..No action.
 *  0b1..LDOK bit is set.
 */
#define FTM_PWMLOAD_GLDOK(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_PWMLOAD_GLDOK_SHIFT)) & FTM_PWMLOAD_GLDOK_MASK)
/*! @} */

/*! @name HCR - Half Cycle Register */
/*! @{ */

#define FTM_HCR_HCVAL_MASK                       (0xFFFFU)
#define FTM_HCR_HCVAL_SHIFT                      (0U)
/*! HCVAL - Half Cycle Value */
#define FTM_HCR_HCVAL(x)                         (((uint32_t)(((uint32_t)(x)) << FTM_HCR_HCVAL_SHIFT)) & FTM_HCR_HCVAL_MASK)
/*! @} */

/*! @name MOD_MIRROR - Mirror of Modulo Value */
/*! @{ */

#define FTM_MOD_MIRROR_FRACMOD_MASK              (0xF800U)
#define FTM_MOD_MIRROR_FRACMOD_SHIFT             (11U)
/*! FRACMOD - Modulo Fractional Value */
#define FTM_MOD_MIRROR_FRACMOD(x)                (((uint32_t)(((uint32_t)(x)) << FTM_MOD_MIRROR_FRACMOD_SHIFT)) & FTM_MOD_MIRROR_FRACMOD_MASK)

#define FTM_MOD_MIRROR_MOD_MASK                  (0xFFFF0000U)
#define FTM_MOD_MIRROR_MOD_SHIFT                 (16U)
/*! MOD - Mirror of the Modulo Integer Value */
#define FTM_MOD_MIRROR_MOD(x)                    (((uint32_t)(((uint32_t)(x)) << FTM_MOD_MIRROR_MOD_SHIFT)) & FTM_MOD_MIRROR_MOD_MASK)
/*! @} */

/*! @name CV_MIRROR - Mirror of Channel (n) Match Value */
/*! @{ */

#define FTM_CV_MIRROR_FRACVAL_MASK               (0xF800U)
#define FTM_CV_MIRROR_FRACVAL_SHIFT              (11U)
/*! FRACVAL - Channel (n) Match Fractional Value */
#define FTM_CV_MIRROR_FRACVAL(x)                 (((uint32_t)(((uint32_t)(x)) << FTM_CV_MIRROR_FRACVAL_SHIFT)) & FTM_CV_MIRROR_FRACVAL_MASK)

#define FTM_CV_MIRROR_VAL_MASK                   (0xFFFF0000U)
#define FTM_CV_MIRROR_VAL_SHIFT                  (16U)
/*! VAL - Mirror of the Channel (n) Match Integer Value */
#define FTM_CV_MIRROR_VAL(x)                     (((uint32_t)(((uint32_t)(x)) << FTM_CV_MIRROR_VAL_SHIFT)) & FTM_CV_MIRROR_VAL_MASK)
/*! @} */

/* The count of FTM_CV_MIRROR */
#define FTM_CV_MIRROR_COUNT                      (8U)


/*!
 * @}
 */ /* end of group FTM_Register_Masks */


/* FTM - Peripheral instance base addresses */
/** Peripheral FTM0 base address */
#define FTM0_BASE                                (0x50009000u)
/** Peripheral FTM0 base pointer */
#define FTM0                                     ((FTM_Type *)FTM0_BASE)
/** Peripheral FTM1 base address */
#define FTM1_BASE                                (0x5000A000u)
/** Peripheral FTM1 base pointer */
#define FTM1                                     ((FTM_Type *)FTM1_BASE)
/** Array initializer of FTM peripheral base addresses */
#define FTM_BASE_ADDRS                           { FTM0_BASE, FTM1_BASE }
/** Array initializer of FTM peripheral base pointers */
#define FTM_BASE_PTRS                            { FTM0, FTM1 }
/** Interrupt vectors for the FTM peripheral type */
#define FTM_IRQS                                 { FTM0_IRQn, FTM1_IRQn }

/*!
 * @}
 */ /* end of group FTM_Peripheral_Access_Layer */


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

#define GPIO_DIRSET_DIRSETP_MASK                 (0x1FFFFFFFU)
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

#define GPIO_DIRCLR_DIRCLRP_MASK                 (0x1FFFFFFFU)
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

#define GPIO_DIRNOT_DIRNOTP_MASK                 (0x1FFFFFFFU)
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
#define GPIO_BASE                                (0xA0000000u)
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
  __IO uint32_t CFG;                               /**< Configuration for shared functions., offset: 0x0 */
  __IO uint32_t STAT;                              /**< Status register for Master, Slave, and Monitor functions., offset: 0x4 */
  __IO uint32_t INTENSET;                          /**< Interrupt Enable Set and read register., offset: 0x8 */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register., offset: 0xC */
  __IO uint32_t TIMEOUT;                           /**< Time-out value register., offset: 0x10 */
  __IO uint32_t CLKDIV;                            /**< Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function., offset: 0x14 */
  __I  uint32_t INTSTAT;                           /**< Interrupt Status register for Master, Slave, and Monitor functions., offset: 0x18 */
       uint8_t RESERVED_0[4];
  __IO uint32_t MSTCTL;                            /**< Master control register., offset: 0x20 */
  __IO uint32_t MSTTIME;                           /**< Master timing configuration., offset: 0x24 */
  __IO uint32_t MSTDAT;                            /**< Combined Master receiver and transmitter data register., offset: 0x28 */
       uint8_t RESERVED_1[20];
  __IO uint32_t SLVCTL;                            /**< Slave control register., offset: 0x40 */
  __IO uint32_t SLVDAT;                            /**< Combined Slave receiver and transmitter data register., offset: 0x44 */
  __IO uint32_t SLVADR[4];                         /**< Slave address register., array offset: 0x48, array step: 0x4 */
  __IO uint32_t SLVQUAL0;                          /**< Slave Qualification for address 0., offset: 0x58 */
       uint8_t RESERVED_2[36];
  __I  uint32_t MONRXDAT;                          /**< Monitor receiver data register., offset: 0x80 */
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
/*! MSTARBLOSSCLR - Master Arbitration Loss interrupt clear. */
#define I2C_INTENCLR_MSTARBLOSSCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTARBLOSSCLR_SHIFT)) & I2C_INTENCLR_MSTARBLOSSCLR_MASK)

#define I2C_INTENCLR_MSTSTSTPERRCLR_MASK         (0x40U)
#define I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT        (6U)
/*! MSTSTSTPERRCLR - Master Start/Stop Error interrupt clear. */
#define I2C_INTENCLR_MSTSTSTPERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT)) & I2C_INTENCLR_MSTSTSTPERRCLR_MASK)

#define I2C_INTENCLR_SLVPENDINGCLR_MASK          (0x100U)
#define I2C_INTENCLR_SLVPENDINGCLR_SHIFT         (8U)
/*! SLVPENDINGCLR - Slave Pending interrupt clear. */
#define I2C_INTENCLR_SLVPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVPENDINGCLR_SHIFT)) & I2C_INTENCLR_SLVPENDINGCLR_MASK)

#define I2C_INTENCLR_SLVNOTSTRCLR_MASK           (0x800U)
#define I2C_INTENCLR_SLVNOTSTRCLR_SHIFT          (11U)
/*! SLVNOTSTRCLR - Slave Not Stretching interrupt clear. */
#define I2C_INTENCLR_SLVNOTSTRCLR(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVNOTSTRCLR_SHIFT)) & I2C_INTENCLR_SLVNOTSTRCLR_MASK)

#define I2C_INTENCLR_SLVDESELCLR_MASK            (0x8000U)
#define I2C_INTENCLR_SLVDESELCLR_SHIFT           (15U)
/*! SLVDESELCLR - Slave Deselect interrupt clear. */
#define I2C_INTENCLR_SLVDESELCLR(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVDESELCLR_SHIFT)) & I2C_INTENCLR_SLVDESELCLR_MASK)

#define I2C_INTENCLR_MONRDYCLR_MASK              (0x10000U)
#define I2C_INTENCLR_MONRDYCLR_SHIFT             (16U)
/*! MONRDYCLR - Monitor data Ready interrupt clear. */
#define I2C_INTENCLR_MONRDYCLR(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONRDYCLR_SHIFT)) & I2C_INTENCLR_MONRDYCLR_MASK)

#define I2C_INTENCLR_MONOVCLR_MASK               (0x20000U)
#define I2C_INTENCLR_MONOVCLR_SHIFT              (17U)
/*! MONOVCLR - Monitor Overrun interrupt clear. */
#define I2C_INTENCLR_MONOVCLR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONOVCLR_SHIFT)) & I2C_INTENCLR_MONOVCLR_MASK)

#define I2C_INTENCLR_MONIDLECLR_MASK             (0x80000U)
#define I2C_INTENCLR_MONIDLECLR_SHIFT            (19U)
/*! MONIDLECLR - Monitor Idle interrupt clear. */
#define I2C_INTENCLR_MONIDLECLR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONIDLECLR_SHIFT)) & I2C_INTENCLR_MONIDLECLR_MASK)

#define I2C_INTENCLR_EVENTTIMEOUTCLR_MASK        (0x1000000U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT       (24U)
/*! EVENTTIMEOUTCLR - Event time-out interrupt clear. */
#define I2C_INTENCLR_EVENTTIMEOUTCLR(x)          (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_EVENTTIMEOUTCLR_MASK)

#define I2C_INTENCLR_SCLTIMEOUTCLR_MASK          (0x2000000U)
#define I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT         (25U)
/*! SCLTIMEOUTCLR - SCL time-out interrupt clear. */
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
/*! MSTPENDING - Master Pending. */
#define I2C_INTSTAT_MSTPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTPENDING_SHIFT)) & I2C_INTSTAT_MSTPENDING_MASK)

#define I2C_INTSTAT_MSTARBLOSS_MASK              (0x10U)
#define I2C_INTSTAT_MSTARBLOSS_SHIFT             (4U)
/*! MSTARBLOSS - Master Arbitration Loss flag. */
#define I2C_INTSTAT_MSTARBLOSS(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTARBLOSS_SHIFT)) & I2C_INTSTAT_MSTARBLOSS_MASK)

#define I2C_INTSTAT_MSTSTSTPERR_MASK             (0x40U)
#define I2C_INTSTAT_MSTSTSTPERR_SHIFT            (6U)
/*! MSTSTSTPERR - Master Start/Stop Error flag. */
#define I2C_INTSTAT_MSTSTSTPERR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTSTSTPERR_SHIFT)) & I2C_INTSTAT_MSTSTSTPERR_MASK)

#define I2C_INTSTAT_SLVPENDING_MASK              (0x100U)
#define I2C_INTSTAT_SLVPENDING_SHIFT             (8U)
/*! SLVPENDING - Slave Pending. */
#define I2C_INTSTAT_SLVPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVPENDING_SHIFT)) & I2C_INTSTAT_SLVPENDING_MASK)

#define I2C_INTSTAT_SLVNOTSTR_MASK               (0x800U)
#define I2C_INTSTAT_SLVNOTSTR_SHIFT              (11U)
/*! SLVNOTSTR - Slave Not Stretching status. */
#define I2C_INTSTAT_SLVNOTSTR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVNOTSTR_SHIFT)) & I2C_INTSTAT_SLVNOTSTR_MASK)

#define I2C_INTSTAT_SLVDESEL_MASK                (0x8000U)
#define I2C_INTSTAT_SLVDESEL_SHIFT               (15U)
/*! SLVDESEL - Slave Deselected flag. */
#define I2C_INTSTAT_SLVDESEL(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVDESEL_SHIFT)) & I2C_INTSTAT_SLVDESEL_MASK)

#define I2C_INTSTAT_MONRDY_MASK                  (0x10000U)
#define I2C_INTSTAT_MONRDY_SHIFT                 (16U)
/*! MONRDY - Monitor Ready. */
#define I2C_INTSTAT_MONRDY(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONRDY_SHIFT)) & I2C_INTSTAT_MONRDY_MASK)

#define I2C_INTSTAT_MONOV_MASK                   (0x20000U)
#define I2C_INTSTAT_MONOV_SHIFT                  (17U)
/*! MONOV - Monitor Overflow flag. */
#define I2C_INTSTAT_MONOV(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONOV_SHIFT)) & I2C_INTSTAT_MONOV_MASK)

#define I2C_INTSTAT_MONIDLE_MASK                 (0x80000U)
#define I2C_INTSTAT_MONIDLE_SHIFT                (19U)
/*! MONIDLE - Monitor Idle flag. */
#define I2C_INTSTAT_MONIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONIDLE_SHIFT)) & I2C_INTSTAT_MONIDLE_MASK)

#define I2C_INTSTAT_EVENTTIMEOUT_MASK            (0x1000000U)
#define I2C_INTSTAT_EVENTTIMEOUT_SHIFT           (24U)
/*! EVENTTIMEOUT - Event time-out Interrupt flag. */
#define I2C_INTSTAT_EVENTTIMEOUT(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_EVENTTIMEOUT_SHIFT)) & I2C_INTSTAT_EVENTTIMEOUT_MASK)

#define I2C_INTSTAT_SCLTIMEOUT_MASK              (0x2000000U)
#define I2C_INTSTAT_SCLTIMEOUT_SHIFT             (25U)
/*! SCLTIMEOUT - SCL time-out Interrupt flag. */
#define I2C_INTSTAT_SCLTIMEOUT(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SCLTIMEOUT_SHIFT)) & I2C_INTSTAT_SCLTIMEOUT_MASK)
/*! @} */

/*! @name MSTCTL - Master control register. */
/*! @{ */

#define I2C_MSTCTL_MSTCONTINUE_MASK              (0x1U)
#define I2C_MSTCTL_MSTCONTINUE_SHIFT             (0U)
/*! MSTCONTINUE - Master Continue.
 *  0b0..No effect.
 *  0b1..Informs the Master function to continue to the next operation.
 */
#define I2C_MSTCTL_MSTCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTCONTINUE_SHIFT)) & I2C_MSTCTL_MSTCONTINUE_MASK)

#define I2C_MSTCTL_MSTSTART_MASK                 (0x2U)
#define I2C_MSTCTL_MSTSTART_SHIFT                (1U)
/*! MSTSTART - Master Start control.
 *  0b0..No effect.
 *  0b1..Start. A Start will be generated on the I2C bus at the next allowed time.
 */
#define I2C_MSTCTL_MSTSTART(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTART_SHIFT)) & I2C_MSTCTL_MSTSTART_MASK)

#define I2C_MSTCTL_MSTSTOP_MASK                  (0x4U)
#define I2C_MSTCTL_MSTSTOP_SHIFT                 (2U)
/*! MSTSTOP - Master Stop control.
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
 *  0b1..Informs the Slave function to continue to the next operation.
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
/*! SLVADR - Slave Address. Seven bit slave address that is compared to received addresses if enabled. */
#define I2C_SLVADR_SLVADR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SLVADR_SHIFT)) & I2C_SLVADR_SLVADR_MASK)
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
/*! MONRXDAT - Monitor function Receiver Data. This reflects every data byte that passes on the I2C pins. */
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


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40050000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { I2C0_IRQn }

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- I3C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I3C_Peripheral_Access_Layer I3C Peripheral Access Layer
 * @{
 */

/** I3C - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCONFIG;                           /**< Controller Configuration Register, offset: 0x0 */
  __IO uint32_t SCONFIG;                           /**< Target Configuration register, offset: 0x4 */
  __IO uint32_t SSTATUS;                           /**< Target Status Register, offset: 0x8 */
  __IO uint32_t SCTRL;                             /**< Target Control Register, offset: 0xC */
  __IO uint32_t SINTSET;                           /**< Target Interrupt Set Register, offset: 0x10 */
  __IO uint32_t SINTCLR;                           /**< Target Interrupt Clear Register, offset: 0x14 */
  __I  uint32_t SINTMASKED;                        /**< Target Interrupt Mask Register, offset: 0x18 */
  __IO uint32_t SERRWARN;                          /**< Target Errors and Warnings Register, offset: 0x1C */
  __IO uint32_t SDMACTRL;                          /**< Target DMA Control Register, offset: 0x20 */
       uint8_t RESERVED_0[8];
  __IO uint32_t SDATACTRL;                         /**< Target Data Control Register, offset: 0x2C */
  __O  uint32_t SWDATAB;                           /**< Target Write Data Byte Register, offset: 0x30 */
  __O  uint32_t SWDATABE;                          /**< Target Write Data Byte End, offset: 0x34 */
  __O  uint32_t SWDATAH;                           /**< Target Write Data Half-word Register, offset: 0x38 */
  __O  uint32_t SWDATAHE;                          /**< Target Write Data Half-word End Register, offset: 0x3C */
  __I  uint32_t SRDATAB;                           /**< Target Read Data Byte Register, offset: 0x40 */
       uint8_t RESERVED_1[4];
  __I  uint32_t SRDATAH;                           /**< Target Read Data Half-word Register, offset: 0x48 */
       uint8_t RESERVED_2[8];
  __O  uint32_t SWDATAB1;                          /**< Target Write Data Byte Register, offset: 0x54 */
       uint8_t RESERVED_3[8];
  __I  uint32_t SCAPABILITIES;                     /**< Target Capabilities Register, offset: 0x60 */
  __IO uint32_t SDYNADDR;                          /**< Slave Dynamic Address Register, offset: 0x64 */
  __IO uint32_t SMAXLIMITS;                        /**< Target Maximum Limits Register, offset: 0x68 */
  __IO uint32_t SIDPARTNO;                         /**< Target ID Part Number Register, offset: 0x6C */
  __IO uint32_t SIDEXT;                            /**< Target ID Extension Register, offset: 0x70 */
  __IO uint32_t SVENDORID;                         /**< Target Vendor ID Register, offset: 0x74 */
  __IO uint32_t STCCLOCK;                          /**< Target Time Control Clock Register, offset: 0x78 */
  __I  uint32_t SMSGLAST;                          /**< Target Message Last Matched Register, offset: 0x7C */
       uint8_t RESERVED_4[4];
  __IO uint32_t MCTRL;                             /**< Controller Main Control Register, offset: 0x84 */
  __IO uint32_t MSTATUS;                           /**< Controller Status Register, offset: 0x88 */
  __IO uint32_t MIBIRULES;                         /**< Controller In-band Interrupt Registry and Rules Register, offset: 0x8C */
  __IO uint32_t MINTSET;                           /**< Controller Interrupt Set Register, offset: 0x90 */
  __O  uint32_t MINTCLR;                           /**< Controller Interrupt Clear Register, offset: 0x94 */
  __I  uint32_t MINTMASKED;                        /**< Controller Interrupt Mask Register, offset: 0x98 */
  __IO uint32_t MERRWARN;                          /**< Controller Errors and Warnings Register, offset: 0x9C */
  __IO uint32_t MDMACTRL;                          /**< Controller DMA Control Register, offset: 0xA0 */
       uint8_t RESERVED_5[8];
  __IO uint32_t MDATACTRL;                         /**< Controller Data Control Register, offset: 0xAC */
  __O  uint32_t MWDATAB;                           /**< Controller Write Data Byte Register, offset: 0xB0 */
  __O  uint32_t MWDATABE;                          /**< Controller Write Data Byte End Register, offset: 0xB4 */
  __O  uint32_t MWDATAH;                           /**< Controller Write Data Half-word Register, offset: 0xB8 */
  __O  uint32_t MWDATAHE;                          /**< Controller Write Data Halfword End, offset: 0xBC */
  __I  uint32_t MRDATAB;                           /**< Controller Read Data Byte Register, offset: 0xC0 */
       uint8_t RESERVED_6[4];
  __I  uint32_t MRDATAH;                           /**< Controller Read Data Half-word Register, offset: 0xC8 */
  __I  uint32_t MWDATAB1;                          /**< Controller Write Byte Data 1, offset: 0xCC */
  union {                                          /* offset: 0xD0 */
    __O  uint32_t MWMSG_SDR_CONTROL;                 /**< Controller Write Message in SDR mode, offset: 0xD0 */
    __O  uint32_t MWMSG_SDR_DATA;                    /**< Controller Write Message Data in SDR mode, offset: 0xD0 */
  };
  __I  uint32_t MRMSG_SDR;                         /**< Controller Read Message in SDR mode, offset: 0xD4 */
  union {                                          /* offset: 0xD8 */
    __O  uint32_t MWMSG_DDR_CONTROL;                 /**< Controller Write Message in DDR mode: First Control Word, offset: 0xD8 */
    __O  uint32_t MWMSG_DDR_DATA;                    /**< Controller Write Message Data in DDR mode, offset: 0xD8 */
  };
  __IO uint32_t MRMSG_DDR;                         /**< Controller Read Message in DDR mode, offset: 0xDC */
       uint8_t RESERVED_7[4];
  __IO uint32_t MDYNADDR;                          /**< Controller Dynamic Address, offset: 0xE4 */
       uint8_t RESERVED_8[52];
  __I  uint32_t SMAPCTRL0;                         /**< Map Feature Control 0, offset: 0x11C */
       uint8_t RESERVED_9[3804];
  __I  uint32_t SID;                               /**< Slave Module ID Register, offset: 0xFFC */
} I3C_Type;

/* ----------------------------------------------------------------------------
   -- I3C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I3C_Register_Masks I3C Register Masks
 * @{
 */

/*! @name MCONFIG - Controller Configuration Register */
/*! @{ */

#define I3C_MCONFIG_MSTENA_MASK                  (0x3U)
#define I3C_MCONFIG_MSTENA_SHIFT                 (0U)
/*! MSTENA - Controller enable
 *  0b00..CONTROLLER_OFF. Controller is disabled. The I3C module can only use Target mode.
 *  0b01..CONTROLLER_ON. Controller is enabled. When used upon start-up, this I3C module is the Main Controller by
 *        default. The module controls the bus unless the controller ishanded off. If the controller is handed
 *        off, then MSTENA must become 2, so that it has the capability to become the controller again. Performing the
 *        handoff means emittingGETACCMST CCC command. If the command is accepted, the module emits a STOP and
 *        sets the MSTENA field to 2 (or 0).
 *  0b10..MASTER_CAPABLE: The I3C module is controller-capable; however the module is operating as a target now.
 *        When used from the start, the I3C module will start as a target, but will be prepared to switch to
 *        Controller mode. To switch to Controller mode, the target emits an Controller Request (CR), or gets a GETACCMST
 *        CCC command and accepts it (to switch on the STOP).
 *  0b11..RESERVED
 */
#define I3C_MCONFIG_MSTENA(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_MSTENA_SHIFT)) & I3C_MCONFIG_MSTENA_MASK)

#define I3C_MCONFIG_DISTO_MASK                   (0x8U)
#define I3C_MCONFIG_DISTO_SHIFT                  (3U)
/*! DISTO - Disable Timeout
 *  0b1..Timeout disabled, if timeout is configured
 *  0b0..Timeout enabled
 */
#define I3C_MCONFIG_DISTO(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_DISTO_SHIFT)) & I3C_MCONFIG_DISTO_MASK)

#define I3C_MCONFIG_HKEEP_MASK                   (0x30U)
#define I3C_MCONFIG_HKEEP_SHIFT                  (4U)
/*! HKEEP - High-Keeper
 *  0b00..NONE. Use PUR (Pull-Up Resistor). No separate pin_HK_SDA/pin_HK_SCL is used. Only pin_PUR_oena is used
 *        for sda. Hold pin_SCL_oena High in this mode, SCL clock is push-pull and pin_SCL_out toggles which is
 *        actual clock.
 *  0b01..WIRED_IN. High Keeper controls, use pin_HK_SDA/pin_HK_SCL (High Keeper) controls. SCL may use an HK or
 *        that signal (pin_HK_SCL) may only OR into pin_SCL_oena. Uses pin_HK_SDA as well for sda high keeper, along
 *        with pin_PUR_oena.
 *  0b10..PASSIVE_SDA. Passive on SDA, can Hi-Z (high impedance) for Bus Free (IDLE) and hold. The pins,
 *        pin_HK_SDA and pin_HK_SCL are not used, Only a combination of SDA_oena and pin_PUR_oena are used.
 *  0b11..PASSIVE_ON_SDA_SCL. Passive on SDA and SCL, can Hi-Z (high impedance) both for Bus Free (IDLE), and can
 *        Hi-Z SDA for hold. This is for I2C clock stretching mode, where both SCL and SDA are open drain.
 */
#define I3C_MCONFIG_HKEEP(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_HKEEP_SHIFT)) & I3C_MCONFIG_HKEEP_MASK)

#define I3C_MCONFIG_ODSTOP_MASK                  (0x40U)
#define I3C_MCONFIG_ODSTOP_SHIFT                 (6U)
/*! ODSTOP - Open drain stop
 *  0b0..Disable open-drain stop. ODSTOP must be disabled when sending an HDR exit pattern.
 *  0b1..Enable open-drain stop. STOP is emitted at open-drain speeds even for I3C messages. In legacy devices,
 *       this feature can ensure that the legacy devices see the STOP.
 */
#define I3C_MCONFIG_ODSTOP(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_ODSTOP_SHIFT)) & I3C_MCONFIG_ODSTOP_MASK)

#define I3C_MCONFIG_PPBAUD_MASK                  (0xF00U)
#define I3C_MCONFIG_PPBAUD_SHIFT                 (8U)
/*! PPBAUD - Push-pull baud rate */
#define I3C_MCONFIG_PPBAUD(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_PPBAUD_SHIFT)) & I3C_MCONFIG_PPBAUD_MASK)

#define I3C_MCONFIG_PPLOW_MASK                   (0xF000U)
#define I3C_MCONFIG_PPLOW_SHIFT                  (12U)
/*! PPLOW - Push-Pull low */
#define I3C_MCONFIG_PPLOW(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_PPLOW_SHIFT)) & I3C_MCONFIG_PPLOW_MASK)

#define I3C_MCONFIG_ODBAUD_MASK                  (0xFF0000U)
#define I3C_MCONFIG_ODBAUD_SHIFT                 (16U)
/*! ODBAUD - Open drain baud rate */
#define I3C_MCONFIG_ODBAUD(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_ODBAUD_SHIFT)) & I3C_MCONFIG_ODBAUD_MASK)

#define I3C_MCONFIG_ODHPP_MASK                   (0x1000000U)
#define I3C_MCONFIG_ODHPP_SHIFT                  (24U)
/*! ODHPP - Open drain high push-pull */
#define I3C_MCONFIG_ODHPP(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_ODHPP_SHIFT)) & I3C_MCONFIG_ODHPP_MASK)

#define I3C_MCONFIG_SKEW_MASK                    (0xE000000U)
#define I3C_MCONFIG_SKEW_SHIFT                   (25U)
/*! SKEW - Skew */
#define I3C_MCONFIG_SKEW(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_SKEW_SHIFT)) & I3C_MCONFIG_SKEW_MASK)

#define I3C_MCONFIG_I2CBAUD_MASK                 (0xF0000000U)
#define I3C_MCONFIG_I2CBAUD_SHIFT                (28U)
/*! I2CBAUD - I2C baud rate */
#define I3C_MCONFIG_I2CBAUD(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MCONFIG_I2CBAUD_SHIFT)) & I3C_MCONFIG_I2CBAUD_MASK)
/*! @} */

/*! @name SCONFIG - Target Configuration register */
/*! @{ */

#define I3C_SCONFIG_SLVENA_MASK                  (0x1U)
#define I3C_SCONFIG_SLVENA_SHIFT                 (0U)
/*! SLVENA - Target enable */
#define I3C_SCONFIG_SLVENA(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_SLVENA_SHIFT)) & I3C_SCONFIG_SLVENA_MASK)

#define I3C_SCONFIG_NACK_MASK                    (0x2U)
#define I3C_SCONFIG_NACK_SHIFT                   (1U)
/*! NACK - Not acknowledge */
#define I3C_SCONFIG_NACK(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_NACK_SHIFT)) & I3C_SCONFIG_NACK_MASK)

#define I3C_SCONFIG_MATCHSS_MASK                 (0x4U)
#define I3C_SCONFIG_MATCHSS_SHIFT                (2U)
/*! MATCHSS - Match START or STOP */
#define I3C_SCONFIG_MATCHSS(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_MATCHSS_SHIFT)) & I3C_SCONFIG_MATCHSS_MASK)

#define I3C_SCONFIG_S0IGNORE_MASK                (0x8U)
#define I3C_SCONFIG_S0IGNORE_SHIFT               (3U)
/*! S0IGNORE - Ignore TE0/TE1 Errors */
#define I3C_SCONFIG_S0IGNORE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_S0IGNORE_SHIFT)) & I3C_SCONFIG_S0IGNORE_MASK)

#define I3C_SCONFIG_HDROK_MASK                   (0x10U)
#define I3C_SCONFIG_HDROK_SHIFT                  (4U)
/*! HDROK - HDR OK Deprecated. Use the SIDEXT[BCR] field instead */
#define I3C_SCONFIG_HDROK(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_HDROK_SHIFT)) & I3C_SCONFIG_HDROK_MASK)

#define I3C_SCONFIG_OFFLINE_MASK                 (0x200U)
#define I3C_SCONFIG_OFFLINE_SHIFT                (9U)
/*! OFFLINE - Offline */
#define I3C_SCONFIG_OFFLINE(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_OFFLINE_SHIFT)) & I3C_SCONFIG_OFFLINE_MASK)

#define I3C_SCONFIG_BAMATCH_MASK                 (0x3F0000U)
#define I3C_SCONFIG_BAMATCH_SHIFT                (16U)
/*! BAMATCH - Bus available match */
#define I3C_SCONFIG_BAMATCH(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_BAMATCH_SHIFT)) & I3C_SCONFIG_BAMATCH_MASK)

#define I3C_SCONFIG_SADDR_MASK                   (0xFE000000U)
#define I3C_SCONFIG_SADDR_SHIFT                  (25U)
/*! SADDR - Static address */
#define I3C_SCONFIG_SADDR(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SCONFIG_SADDR_SHIFT)) & I3C_SCONFIG_SADDR_MASK)
/*! @} */

/*! @name SSTATUS - Target Status Register */
/*! @{ */

#define I3C_SSTATUS_STNOTSTOP_MASK               (0x1U)
#define I3C_SSTATUS_STNOTSTOP_SHIFT              (0U)
/*! STNOTSTOP - Status Not Stop */
#define I3C_SSTATUS_STNOTSTOP(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STNOTSTOP_SHIFT)) & I3C_SSTATUS_STNOTSTOP_MASK)

#define I3C_SSTATUS_STMSG_MASK                   (0x2U)
#define I3C_SSTATUS_STMSG_SHIFT                  (1U)
/*! STMSG - Status message */
#define I3C_SSTATUS_STMSG(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STMSG_SHIFT)) & I3C_SSTATUS_STMSG_MASK)

#define I3C_SSTATUS_STCCCH_MASK                  (0x4U)
#define I3C_SSTATUS_STCCCH_SHIFT                 (2U)
/*! STCCCH - Status Common Command Code Handler */
#define I3C_SSTATUS_STCCCH(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STCCCH_SHIFT)) & I3C_SSTATUS_STCCCH_MASK)

#define I3C_SSTATUS_STREQRD_MASK                 (0x8U)
#define I3C_SSTATUS_STREQRD_SHIFT                (3U)
/*! STREQRD - Status required */
#define I3C_SSTATUS_STREQRD(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STREQRD_SHIFT)) & I3C_SSTATUS_STREQRD_MASK)

#define I3C_SSTATUS_STREQWR_MASK                 (0x10U)
#define I3C_SSTATUS_STREQWR_SHIFT                (4U)
/*! STREQWR - Status request write */
#define I3C_SSTATUS_STREQWR(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STREQWR_SHIFT)) & I3C_SSTATUS_STREQWR_MASK)

#define I3C_SSTATUS_STDAA_MASK                   (0x20U)
#define I3C_SSTATUS_STDAA_SHIFT                  (5U)
/*! STDAA - Status Dynamic Address Assignment */
#define I3C_SSTATUS_STDAA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STDAA_SHIFT)) & I3C_SSTATUS_STDAA_MASK)

#define I3C_SSTATUS_STHDR_MASK                   (0x40U)
#define I3C_SSTATUS_STHDR_SHIFT                  (6U)
/*! STHDR - Status High Data Rate */
#define I3C_SSTATUS_STHDR(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STHDR_SHIFT)) & I3C_SSTATUS_STHDR_MASK)

#define I3C_SSTATUS_START_MASK                   (0x100U)
#define I3C_SSTATUS_START_SHIFT                  (8U)
/*! START - Start */
#define I3C_SSTATUS_START(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_START_SHIFT)) & I3C_SSTATUS_START_MASK)

#define I3C_SSTATUS_MATCHED_MASK                 (0x200U)
#define I3C_SSTATUS_MATCHED_SHIFT                (9U)
/*! MATCHED - Matched */
#define I3C_SSTATUS_MATCHED(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_MATCHED_SHIFT)) & I3C_SSTATUS_MATCHED_MASK)

#define I3C_SSTATUS_STOP_MASK                    (0x400U)
#define I3C_SSTATUS_STOP_SHIFT                   (10U)
/*! STOP - Stop */
#define I3C_SSTATUS_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_STOP_SHIFT)) & I3C_SSTATUS_STOP_MASK)

#define I3C_SSTATUS_RX_PEND_MASK                 (0x800U)
#define I3C_SSTATUS_RX_PEND_SHIFT                (11U)
/*! RX_PEND - Received message pending */
#define I3C_SSTATUS_RX_PEND(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_RX_PEND_SHIFT)) & I3C_SSTATUS_RX_PEND_MASK)

#define I3C_SSTATUS_TXNOTFULL_MASK               (0x1000U)
#define I3C_SSTATUS_TXNOTFULL_SHIFT              (12U)
/*! TXNOTFULL - Transmit buffer is not full */
#define I3C_SSTATUS_TXNOTFULL(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_TXNOTFULL_SHIFT)) & I3C_SSTATUS_TXNOTFULL_MASK)

#define I3C_SSTATUS_DACHG_MASK                   (0x2000U)
#define I3C_SSTATUS_DACHG_SHIFT                  (13U)
/*! DACHG - DACHG */
#define I3C_SSTATUS_DACHG(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_DACHG_SHIFT)) & I3C_SSTATUS_DACHG_MASK)

#define I3C_SSTATUS_CCC_MASK                     (0x4000U)
#define I3C_SSTATUS_CCC_SHIFT                    (14U)
/*! CCC - Common Command Code */
#define I3C_SSTATUS_CCC(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_CCC_SHIFT)) & I3C_SSTATUS_CCC_MASK)

#define I3C_SSTATUS_ERRWARN_MASK                 (0x8000U)
#define I3C_SSTATUS_ERRWARN_SHIFT                (15U)
/*! ERRWARN - Error warning */
#define I3C_SSTATUS_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_ERRWARN_SHIFT)) & I3C_SSTATUS_ERRWARN_MASK)

#define I3C_SSTATUS_HDRMATCH_MASK                (0x10000U)
#define I3C_SSTATUS_HDRMATCH_SHIFT               (16U)
/*! HDRMATCH - High Data Rate command match */
#define I3C_SSTATUS_HDRMATCH(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_HDRMATCH_SHIFT)) & I3C_SSTATUS_HDRMATCH_MASK)

#define I3C_SSTATUS_CHANDLED_MASK                (0x20000U)
#define I3C_SSTATUS_CHANDLED_SHIFT               (17U)
/*! CHANDLED - Common-Command-Code handled */
#define I3C_SSTATUS_CHANDLED(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_CHANDLED_SHIFT)) & I3C_SSTATUS_CHANDLED_MASK)

#define I3C_SSTATUS_EVENT_MASK                   (0x40000U)
#define I3C_SSTATUS_EVENT_SHIFT                  (18U)
/*! EVENT - Event */
#define I3C_SSTATUS_EVENT(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_EVENT_SHIFT)) & I3C_SSTATUS_EVENT_MASK)

#define I3C_SSTATUS_SLVRST_MASK                  (0x80000U)
#define I3C_SSTATUS_SLVRST_SHIFT                 (19U)
/*! SLVRST - Target Reset */
#define I3C_SSTATUS_SLVRST(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_SLVRST_SHIFT)) & I3C_SSTATUS_SLVRST_MASK)

#define I3C_SSTATUS_EVDET_MASK                   (0x300000U)
#define I3C_SSTATUS_EVDET_SHIFT                  (20U)
/*! EVDET - Event details
 *  0b00..NONE: no event or no pending event
 *  0b01..NO_REQUEST: Request not sent yet. Either there was no START yet, or is waiting for Bus-Available or Bus-Idle (HJ).
 *  0b10..NACKED: Not acknowledged(Request sent and NACKed); the module will try again.
 *  0b11..ACKED: Acknowledged (Request sent and ACKed), so Done (unless the time control data is still being sent).
 */
#define I3C_SSTATUS_EVDET(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_EVDET_SHIFT)) & I3C_SSTATUS_EVDET_MASK)

#define I3C_SSTATUS_IBIDIS_MASK                  (0x1000000U)
#define I3C_SSTATUS_IBIDIS_SHIFT                 (24U)
/*! IBIDIS - In-Band Interrupts are disabled */
#define I3C_SSTATUS_IBIDIS(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_IBIDIS_SHIFT)) & I3C_SSTATUS_IBIDIS_MASK)

#define I3C_SSTATUS_MRDIS_MASK                   (0x2000000U)
#define I3C_SSTATUS_MRDIS_SHIFT                  (25U)
/*! MRDIS - Controller requests are disabled */
#define I3C_SSTATUS_MRDIS(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_MRDIS_SHIFT)) & I3C_SSTATUS_MRDIS_MASK)

#define I3C_SSTATUS_HJDIS_MASK                   (0x8000000U)
#define I3C_SSTATUS_HJDIS_SHIFT                  (27U)
/*! HJDIS - Hot-Join is disabled */
#define I3C_SSTATUS_HJDIS(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_HJDIS_SHIFT)) & I3C_SSTATUS_HJDIS_MASK)

#define I3C_SSTATUS_ACTSTATE_MASK                (0x30000000U)
#define I3C_SSTATUS_ACTSTATE_SHIFT               (28U)
/*! ACTSTATE - Activity state from Common Command Codes (CCC)
 *  0b00..NO_LATENCY: normal bus operations
 *  0b01..LATENCY_1MS: 1 ms of latency
 *  0b10..LATENCY_100MS: 100 ms of latency
 *  0b11..LATENCY_10S: 10 seconds of latency
 */
#define I3C_SSTATUS_ACTSTATE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_ACTSTATE_SHIFT)) & I3C_SSTATUS_ACTSTATE_MASK)

#define I3C_SSTATUS_TIMECTRL_MASK                (0xC0000000U)
#define I3C_SSTATUS_TIMECTRL_SHIFT               (30U)
/*! TIMECTRL - Time control
 *  0b00..NO_TIME_CONTROL: No time control is enabled
 *  0b01..Reserved
 *  0b10..ASYNC_MODE: Asynchronous standard mode (0) is enabled
 *  0b11..RESERVED
 */
#define I3C_SSTATUS_TIMECTRL(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SSTATUS_TIMECTRL_SHIFT)) & I3C_SSTATUS_TIMECTRL_MASK)
/*! @} */

/*! @name SCTRL - Target Control Register */
/*! @{ */

#define I3C_SCTRL_EVENT_MASK                     (0x3U)
#define I3C_SCTRL_EVENT_SHIFT                    (0U)
/*! EVENT - EVENT
 *  0b00..NORMAL_MODE: If EVENT is set to 0 after was a non-0 value, event processing will cancel if the event
 *        processing has not yet started; if event processing has already been started, then event processing will not
 *        be be cancelled.
 *  0b01..IBI: Start an In-Band Interrupt. This will try to push an IBI interrupt onto the I3C bus. If data is
 *        associated with the IBI, then the data will be read from the SCTRL.IBIDATA field. If time control is
 *        enabled, then this data will also include any time control-related bytes; additionally, the IBIDATA byte will
 *        have bit 7 set to 1 automatically (as is required for time control). The IBI interrupt will occur after the
 *        1st (mandatory) IBIDATA, if any.
 *  0b10..MASTER_REQUEST: Start a Master-Request.
 *  0b11..HOT_JOIN_REQUEST: Start a Hot-Join request. A Hot-Join Request should only be used when the device is
 *        powered on after the I3C bus is already powered up, or when the device is connected using hot insertion
 *        methods (the device is powered up when it is physically inserted onto the powered-up I3C bus). The hot join
 *        will wait for Bus Idle, and SCTRL.EVENT=HOT_JOIN_REQUEST must be set before the target enable
 *        (SCONFIG.SLVENA).
 */
#define I3C_SCTRL_EVENT(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_EVENT_SHIFT)) & I3C_SCTRL_EVENT_MASK)

#define I3C_SCTRL_EXTDATA_MASK                   (0x8U)
#define I3C_SCTRL_EXTDATA_SHIFT                  (3U)
/*! EXTDATA - Extended Data */
#define I3C_SCTRL_EXTDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_EXTDATA_SHIFT)) & I3C_SCTRL_EXTDATA_MASK)

#define I3C_SCTRL_MAPIDX_MASK                    (0x70U)
#define I3C_SCTRL_MAPIDX_SHIFT                   (4U)
/*! MAPIDX - Map Index */
#define I3C_SCTRL_MAPIDX(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_MAPIDX_SHIFT)) & I3C_SCTRL_MAPIDX_MASK)

#define I3C_SCTRL_IBIDATA_MASK                   (0xFF00U)
#define I3C_SCTRL_IBIDATA_SHIFT                  (8U)
/*! IBIDATA - In-Band Interrupt data */
#define I3C_SCTRL_IBIDATA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_IBIDATA_SHIFT)) & I3C_SCTRL_IBIDATA_MASK)

#define I3C_SCTRL_PENDINT_MASK                   (0xF0000U)
#define I3C_SCTRL_PENDINT_SHIFT                  (16U)
/*! PENDINT - Pending interrupt */
#define I3C_SCTRL_PENDINT(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_PENDINT_SHIFT)) & I3C_SCTRL_PENDINT_MASK)

#define I3C_SCTRL_ACTSTATE_MASK                  (0x300000U)
#define I3C_SCTRL_ACTSTATE_SHIFT                 (20U)
/*! ACTSTATE - Activity state (of target) */
#define I3C_SCTRL_ACTSTATE(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_ACTSTATE_SHIFT)) & I3C_SCTRL_ACTSTATE_MASK)

#define I3C_SCTRL_VENDINFO_MASK                  (0xFF000000U)
#define I3C_SCTRL_VENDINFO_SHIFT                 (24U)
/*! VENDINFO - Vendor information */
#define I3C_SCTRL_VENDINFO(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SCTRL_VENDINFO_SHIFT)) & I3C_SCTRL_VENDINFO_MASK)
/*! @} */

/*! @name SINTSET - Target Interrupt Set Register */
/*! @{ */

#define I3C_SINTSET_START_MASK                   (0x100U)
#define I3C_SINTSET_START_SHIFT                  (8U)
/*! START - Start interrupt enable */
#define I3C_SINTSET_START(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_START_SHIFT)) & I3C_SINTSET_START_MASK)

#define I3C_SINTSET_MATCHED_MASK                 (0x200U)
#define I3C_SINTSET_MATCHED_SHIFT                (9U)
/*! MATCHED - Match interrupt enable */
#define I3C_SINTSET_MATCHED(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_MATCHED_SHIFT)) & I3C_SINTSET_MATCHED_MASK)

#define I3C_SINTSET_STOP_MASK                    (0x400U)
#define I3C_SINTSET_STOP_SHIFT                   (10U)
/*! STOP - Stop interrupt enable */
#define I3C_SINTSET_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_STOP_SHIFT)) & I3C_SINTSET_STOP_MASK)

#define I3C_SINTSET_RXPEND_MASK                  (0x800U)
#define I3C_SINTSET_RXPEND_SHIFT                 (11U)
/*! RXPEND - Receive interrupt enable */
#define I3C_SINTSET_RXPEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_RXPEND_SHIFT)) & I3C_SINTSET_RXPEND_MASK)

#define I3C_SINTSET_TXSEND_MASK                  (0x1000U)
#define I3C_SINTSET_TXSEND_SHIFT                 (12U)
/*! TXSEND - Transmit interrupt enable */
#define I3C_SINTSET_TXSEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_TXSEND_SHIFT)) & I3C_SINTSET_TXSEND_MASK)

#define I3C_SINTSET_DACHG_MASK                   (0x2000U)
#define I3C_SINTSET_DACHG_SHIFT                  (13U)
/*! DACHG - Dynamic address change interrupt enable */
#define I3C_SINTSET_DACHG(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_DACHG_SHIFT)) & I3C_SINTSET_DACHG_MASK)

#define I3C_SINTSET_CCC_MASK                     (0x4000U)
#define I3C_SINTSET_CCC_SHIFT                    (14U)
/*! CCC - Common Command Code (CCC) (that was not handled by I3C module) interrupt enable */
#define I3C_SINTSET_CCC(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_CCC_SHIFT)) & I3C_SINTSET_CCC_MASK)

#define I3C_SINTSET_ERRWARN_MASK                 (0x8000U)
#define I3C_SINTSET_ERRWARN_SHIFT                (15U)
/*! ERRWARN - Error/warning interrupt enable */
#define I3C_SINTSET_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_ERRWARN_SHIFT)) & I3C_SINTSET_ERRWARN_MASK)

#define I3C_SINTSET_DDRMATCHED_MASK              (0x10000U)
#define I3C_SINTSET_DDRMATCHED_SHIFT             (16U)
/*! DDRMATCHED - Double Data Rate (DDR) interrupt enable */
#define I3C_SINTSET_DDRMATCHED(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_DDRMATCHED_SHIFT)) & I3C_SINTSET_DDRMATCHED_MASK)

#define I3C_SINTSET_CHANDLED_MASK                (0x20000U)
#define I3C_SINTSET_CHANDLED_SHIFT               (17U)
/*! CHANDLED - Common Command Code (CCC) (that was handled by I3C module) interrupt enable */
#define I3C_SINTSET_CHANDLED(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_CHANDLED_SHIFT)) & I3C_SINTSET_CHANDLED_MASK)

#define I3C_SINTSET_EVENT_MASK                   (0x40000U)
#define I3C_SINTSET_EVENT_SHIFT                  (18U)
/*! EVENT - Event interrupt enable */
#define I3C_SINTSET_EVENT(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_EVENT_SHIFT)) & I3C_SINTSET_EVENT_MASK)

#define I3C_SINTSET_SLVRST_MASK                  (0x80000U)
#define I3C_SINTSET_SLVRST_SHIFT                 (19U)
/*! SLVRST - Target Reset */
#define I3C_SINTSET_SLVRST(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTSET_SLVRST_SHIFT)) & I3C_SINTSET_SLVRST_MASK)
/*! @} */

/*! @name SINTCLR - Target Interrupt Clear Register */
/*! @{ */

#define I3C_SINTCLR_START_MASK                   (0x100U)
#define I3C_SINTCLR_START_SHIFT                  (8U)
/*! START - START interrupt enable clear */
#define I3C_SINTCLR_START(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_START_SHIFT)) & I3C_SINTCLR_START_MASK)

#define I3C_SINTCLR_MATCHED_MASK                 (0x200U)
#define I3C_SINTCLR_MATCHED_SHIFT                (9U)
/*! MATCHED - MATCHED interrupt enable clear */
#define I3C_SINTCLR_MATCHED(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_MATCHED_SHIFT)) & I3C_SINTCLR_MATCHED_MASK)

#define I3C_SINTCLR_STOP_MASK                    (0x400U)
#define I3C_SINTCLR_STOP_SHIFT                   (10U)
/*! STOP - STOP interrupt enable clear */
#define I3C_SINTCLR_STOP(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_STOP_SHIFT)) & I3C_SINTCLR_STOP_MASK)

#define I3C_SINTCLR_RXPEND_MASK                  (0x800U)
#define I3C_SINTCLR_RXPEND_SHIFT                 (11U)
/*! RXPEND - RXPEND interrupt enable clear */
#define I3C_SINTCLR_RXPEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_RXPEND_SHIFT)) & I3C_SINTCLR_RXPEND_MASK)

#define I3C_SINTCLR_TXSEND_MASK                  (0x1000U)
#define I3C_SINTCLR_TXSEND_SHIFT                 (12U)
/*! TXSEND - TXSEND interrupt enable clear */
#define I3C_SINTCLR_TXSEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_TXSEND_SHIFT)) & I3C_SINTCLR_TXSEND_MASK)

#define I3C_SINTCLR_DACHG_MASK                   (0x2000U)
#define I3C_SINTCLR_DACHG_SHIFT                  (13U)
/*! DACHG - DACHG interrupt enable clear */
#define I3C_SINTCLR_DACHG(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_DACHG_SHIFT)) & I3C_SINTCLR_DACHG_MASK)

#define I3C_SINTCLR_CCC_MASK                     (0x4000U)
#define I3C_SINTCLR_CCC_SHIFT                    (14U)
/*! CCC - CCC interrupt enable clear */
#define I3C_SINTCLR_CCC(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_CCC_SHIFT)) & I3C_SINTCLR_CCC_MASK)

#define I3C_SINTCLR_ERRWARN_MASK                 (0x8000U)
#define I3C_SINTCLR_ERRWARN_SHIFT                (15U)
/*! ERRWARN - ERRWARN interrupt enable clear */
#define I3C_SINTCLR_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_ERRWARN_SHIFT)) & I3C_SINTCLR_ERRWARN_MASK)

#define I3C_SINTCLR_DDRMATCHED_MASK              (0x10000U)
#define I3C_SINTCLR_DDRMATCHED_SHIFT             (16U)
/*! DDRMATCHED - DDRMATCHED interrupt enable clear */
#define I3C_SINTCLR_DDRMATCHED(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_DDRMATCHED_SHIFT)) & I3C_SINTCLR_DDRMATCHED_MASK)

#define I3C_SINTCLR_CHANDLED_MASK                (0x20000U)
#define I3C_SINTCLR_CHANDLED_SHIFT               (17U)
/*! CHANDLED - CHANDLED interrupt enable clear */
#define I3C_SINTCLR_CHANDLED(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_CHANDLED_SHIFT)) & I3C_SINTCLR_CHANDLED_MASK)

#define I3C_SINTCLR_EVENT_MASK                   (0x40000U)
#define I3C_SINTCLR_EVENT_SHIFT                  (18U)
/*! EVENT - EVENT interrupt enable clear */
#define I3C_SINTCLR_EVENT(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_EVENT_SHIFT)) & I3C_SINTCLR_EVENT_MASK)

#define I3C_SINTCLR_SLVRST_MASK                  (0x80000U)
#define I3C_SINTCLR_SLVRST_SHIFT                 (19U)
/*! SLVRST - SLVRST interrupt enable clear */
#define I3C_SINTCLR_SLVRST(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTCLR_SLVRST_SHIFT)) & I3C_SINTCLR_SLVRST_MASK)
/*! @} */

/*! @name SINTMASKED - Target Interrupt Mask Register */
/*! @{ */

#define I3C_SINTMASKED_START_MASK                (0x100U)
#define I3C_SINTMASKED_START_SHIFT               (8U)
/*! START - START interrupt mask */
#define I3C_SINTMASKED_START(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_START_SHIFT)) & I3C_SINTMASKED_START_MASK)

#define I3C_SINTMASKED_MATCHED_MASK              (0x200U)
#define I3C_SINTMASKED_MATCHED_SHIFT             (9U)
/*! MATCHED - MATCHED interrupt mask */
#define I3C_SINTMASKED_MATCHED(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_MATCHED_SHIFT)) & I3C_SINTMASKED_MATCHED_MASK)

#define I3C_SINTMASKED_STOP_MASK                 (0x400U)
#define I3C_SINTMASKED_STOP_SHIFT                (10U)
/*! STOP - STOP interrupt mask */
#define I3C_SINTMASKED_STOP(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_STOP_SHIFT)) & I3C_SINTMASKED_STOP_MASK)

#define I3C_SINTMASKED_RXPEND_MASK               (0x800U)
#define I3C_SINTMASKED_RXPEND_SHIFT              (11U)
/*! RXPEND - RXPEND interrupt mask */
#define I3C_SINTMASKED_RXPEND(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_RXPEND_SHIFT)) & I3C_SINTMASKED_RXPEND_MASK)

#define I3C_SINTMASKED_TXSEND_MASK               (0x1000U)
#define I3C_SINTMASKED_TXSEND_SHIFT              (12U)
/*! TXSEND - TXSEND interrupt mask */
#define I3C_SINTMASKED_TXSEND(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_TXSEND_SHIFT)) & I3C_SINTMASKED_TXSEND_MASK)

#define I3C_SINTMASKED_DACHG_MASK                (0x2000U)
#define I3C_SINTMASKED_DACHG_SHIFT               (13U)
/*! DACHG - DACHG interrupt mask */
#define I3C_SINTMASKED_DACHG(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_DACHG_SHIFT)) & I3C_SINTMASKED_DACHG_MASK)

#define I3C_SINTMASKED_CCC_MASK                  (0x4000U)
#define I3C_SINTMASKED_CCC_SHIFT                 (14U)
/*! CCC - CCC interrupt mask */
#define I3C_SINTMASKED_CCC(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_CCC_SHIFT)) & I3C_SINTMASKED_CCC_MASK)

#define I3C_SINTMASKED_ERRWARN_MASK              (0x8000U)
#define I3C_SINTMASKED_ERRWARN_SHIFT             (15U)
/*! ERRWARN - ERRWARN interrupt mask */
#define I3C_SINTMASKED_ERRWARN(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_ERRWARN_SHIFT)) & I3C_SINTMASKED_ERRWARN_MASK)

#define I3C_SINTMASKED_DDRMATCHED_MASK           (0x10000U)
#define I3C_SINTMASKED_DDRMATCHED_SHIFT          (16U)
/*! DDRMATCHED - DDRMATCHED interrupt mask */
#define I3C_SINTMASKED_DDRMATCHED(x)             (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_DDRMATCHED_SHIFT)) & I3C_SINTMASKED_DDRMATCHED_MASK)

#define I3C_SINTMASKED_CHANDLED_MASK             (0x20000U)
#define I3C_SINTMASKED_CHANDLED_SHIFT            (17U)
/*! CHANDLED - CHANDLED interrupt mask */
#define I3C_SINTMASKED_CHANDLED(x)               (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_CHANDLED_SHIFT)) & I3C_SINTMASKED_CHANDLED_MASK)

#define I3C_SINTMASKED_EVENT_MASK                (0x40000U)
#define I3C_SINTMASKED_EVENT_SHIFT               (18U)
/*! EVENT - EVENT interrupt mask */
#define I3C_SINTMASKED_EVENT(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SINTMASKED_EVENT_SHIFT)) & I3C_SINTMASKED_EVENT_MASK)
/*! @} */

/*! @name SERRWARN - Target Errors and Warnings Register */
/*! @{ */

#define I3C_SERRWARN_ORUN_MASK                   (0x1U)
#define I3C_SERRWARN_ORUN_SHIFT                  (0U)
/*! ORUN - Overrun error */
#define I3C_SERRWARN_ORUN(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_ORUN_SHIFT)) & I3C_SERRWARN_ORUN_MASK)

#define I3C_SERRWARN_URUN_MASK                   (0x2U)
#define I3C_SERRWARN_URUN_SHIFT                  (1U)
/*! URUN - Underrun error */
#define I3C_SERRWARN_URUN(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_URUN_SHIFT)) & I3C_SERRWARN_URUN_MASK)

#define I3C_SERRWARN_URUNNACK_MASK               (0x4U)
#define I3C_SERRWARN_URUNNACK_SHIFT              (2U)
/*! URUNNACK - Underrun and Not Acknowledged (NACKed) error */
#define I3C_SERRWARN_URUNNACK(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_URUNNACK_SHIFT)) & I3C_SERRWARN_URUNNACK_MASK)

#define I3C_SERRWARN_TERM_MASK                   (0x8U)
#define I3C_SERRWARN_TERM_SHIFT                  (3U)
/*! TERM - Terminated error */
#define I3C_SERRWARN_TERM(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_TERM_SHIFT)) & I3C_SERRWARN_TERM_MASK)

#define I3C_SERRWARN_INVSTART_MASK               (0x10U)
#define I3C_SERRWARN_INVSTART_SHIFT              (4U)
/*! INVSTART - Invalid start error */
#define I3C_SERRWARN_INVSTART(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_INVSTART_SHIFT)) & I3C_SERRWARN_INVSTART_MASK)

#define I3C_SERRWARN_SPAR_MASK                   (0x100U)
#define I3C_SERRWARN_SPAR_SHIFT                  (8U)
/*! SPAR - SDR parity error */
#define I3C_SERRWARN_SPAR(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_SPAR_SHIFT)) & I3C_SERRWARN_SPAR_MASK)

#define I3C_SERRWARN_HPAR_MASK                   (0x200U)
#define I3C_SERRWARN_HPAR_SHIFT                  (9U)
/*! HPAR - HDR parity error */
#define I3C_SERRWARN_HPAR(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_HPAR_SHIFT)) & I3C_SERRWARN_HPAR_MASK)

#define I3C_SERRWARN_HCRC_MASK                   (0x400U)
#define I3C_SERRWARN_HCRC_SHIFT                  (10U)
/*! HCRC - HDR-DDR CRC error */
#define I3C_SERRWARN_HCRC(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_HCRC_SHIFT)) & I3C_SERRWARN_HCRC_MASK)

#define I3C_SERRWARN_S0S1_MASK                   (0x800U)
#define I3C_SERRWARN_S0S1_SHIFT                  (11U)
/*! S0S1 - S0 or S1 error */
#define I3C_SERRWARN_S0S1(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_S0S1_SHIFT)) & I3C_SERRWARN_S0S1_MASK)

#define I3C_SERRWARN_OREAD_MASK                  (0x10000U)
#define I3C_SERRWARN_OREAD_SHIFT                 (16U)
/*! OREAD - Over-read error */
#define I3C_SERRWARN_OREAD(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_OREAD_SHIFT)) & I3C_SERRWARN_OREAD_MASK)

#define I3C_SERRWARN_OWRITE_MASK                 (0x20000U)
#define I3C_SERRWARN_OWRITE_SHIFT                (17U)
/*! OWRITE - Over-write error */
#define I3C_SERRWARN_OWRITE(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SERRWARN_OWRITE_SHIFT)) & I3C_SERRWARN_OWRITE_MASK)
/*! @} */

/*! @name SDMACTRL - Target DMA Control Register */
/*! @{ */

#define I3C_SDMACTRL_DMAFB_MASK                  (0x3U)
#define I3C_SDMACTRL_DMAFB_SHIFT                 (0U)
/*! DMAFB - DMA Read (From-bus) trigger
 *  0b00..DMA not used
 *  0b01..DMA is enabled for one frame.
 *  0b10..DMA enable
 */
#define I3C_SDMACTRL_DMAFB(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SDMACTRL_DMAFB_SHIFT)) & I3C_SDMACTRL_DMAFB_MASK)

#define I3C_SDMACTRL_DMATB_MASK                  (0xCU)
#define I3C_SDMACTRL_DMATB_SHIFT                 (2U)
/*! DMATB - DMA Write (To-bus) trigger
 *  0b00..NOT_USED: DMA is not used
 *  0b01..ENABLE_ONE_FRAME: DMA is enabled for 1 Frame (ended by DMA or terminated). DMATB auto-clears on a STOP
 *        or START (see the Match START or STOP bit (SCONFIG.MATCHSS).
 *  0b10..ENABLE: DMA is enabled until turned off. Normally, ENABLE should only be used with Master Message mode.
 */
#define I3C_SDMACTRL_DMATB(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SDMACTRL_DMATB_SHIFT)) & I3C_SDMACTRL_DMATB_MASK)

#define I3C_SDMACTRL_DMAWIDTH_MASK               (0x30U)
#define I3C_SDMACTRL_DMAWIDTH_SHIFT              (4U)
/*! DMAWIDTH - Width of DMA operations
 *  0b00..BYTE
 *  0b01..BYTE_AGAIN
 *  0b10..HALF_WORD: Half word (16 bits). This will make sure that 2 bytes are free/available in the FIFO.
 *  0b11..RESERVED
 */
#define I3C_SDMACTRL_DMAWIDTH(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDMACTRL_DMAWIDTH_SHIFT)) & I3C_SDMACTRL_DMAWIDTH_MASK)
/*! @} */

/*! @name SDATACTRL - Target Data Control Register */
/*! @{ */

#define I3C_SDATACTRL_FLUSHTB_MASK               (0x1U)
#define I3C_SDATACTRL_FLUSHTB_SHIFT              (0U)
/*! FLUSHTB - Flush the to-bus buffer/FIFO */
#define I3C_SDATACTRL_FLUSHTB(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_FLUSHTB_SHIFT)) & I3C_SDATACTRL_FLUSHTB_MASK)

#define I3C_SDATACTRL_FLUSHFB_MASK               (0x2U)
#define I3C_SDATACTRL_FLUSHFB_SHIFT              (1U)
/*! FLUSHFB - Flushes the from-bus buffer/FIFO */
#define I3C_SDATACTRL_FLUSHFB(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_FLUSHFB_SHIFT)) & I3C_SDATACTRL_FLUSHFB_MASK)

#define I3C_SDATACTRL_UNLOCK_MASK                (0x8U)
#define I3C_SDATACTRL_UNLOCK_SHIFT               (3U)
/*! UNLOCK - Unlock */
#define I3C_SDATACTRL_UNLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_UNLOCK_SHIFT)) & I3C_SDATACTRL_UNLOCK_MASK)

#define I3C_SDATACTRL_TXTRIG_MASK                (0x30U)
#define I3C_SDATACTRL_TXTRIG_SHIFT               (4U)
/*! TXTRIG - Trigger level for TX FIFO emptiness
 *  0b00..Trigger on empty
 *  0b01..Trigger on ¼ full or less
 *  0b10..Trigger on .5 full or less
 *  0b11..Trigger on 1 less than full or less (Default)
 */
#define I3C_SDATACTRL_TXTRIG(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_TXTRIG_SHIFT)) & I3C_SDATACTRL_TXTRIG_MASK)

#define I3C_SDATACTRL_RXTRIG_MASK                (0xC0U)
#define I3C_SDATACTRL_RXTRIG_SHIFT               (6U)
/*! RXTRIG - Trigger level for RX FIFO fullness
 *  0b00..Trigger on not empty
 *  0b01..Trigger on ¼ or more full
 *  0b10..Trigger on .5 or more full
 *  0b11..Trigger on 3/4 or more full
 */
#define I3C_SDATACTRL_RXTRIG(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_RXTRIG_SHIFT)) & I3C_SDATACTRL_RXTRIG_MASK)

#define I3C_SDATACTRL_TXCOUNT_MASK               (0x1F0000U)
#define I3C_SDATACTRL_TXCOUNT_SHIFT              (16U)
/*! TXCOUNT - Count of bytes in TX */
#define I3C_SDATACTRL_TXCOUNT(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_TXCOUNT_SHIFT)) & I3C_SDATACTRL_TXCOUNT_MASK)

#define I3C_SDATACTRL_RXCOUNT_MASK               (0x1F000000U)
#define I3C_SDATACTRL_RXCOUNT_SHIFT              (24U)
/*! RXCOUNT - Count of bytes in RX */
#define I3C_SDATACTRL_RXCOUNT(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_RXCOUNT_SHIFT)) & I3C_SDATACTRL_RXCOUNT_MASK)

#define I3C_SDATACTRL_TXFULL_MASK                (0x40000000U)
#define I3C_SDATACTRL_TXFULL_SHIFT               (30U)
/*! TXFULL - TX is full
 *  0b1..TX is full
 *  0b0..TX is not full
 */
#define I3C_SDATACTRL_TXFULL(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_TXFULL_SHIFT)) & I3C_SDATACTRL_TXFULL_MASK)

#define I3C_SDATACTRL_RXEMPTY_MASK               (0x80000000U)
#define I3C_SDATACTRL_RXEMPTY_SHIFT              (31U)
/*! RXEMPTY - RX is empty
 *  0b1..RX is empty
 *  0b0..RX is not empty
 */
#define I3C_SDATACTRL_RXEMPTY(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SDATACTRL_RXEMPTY_SHIFT)) & I3C_SDATACTRL_RXEMPTY_MASK)
/*! @} */

/*! @name SWDATAB - Target Write Data Byte Register */
/*! @{ */

#define I3C_SWDATAB_DATA_MASK                    (0xFFU)
#define I3C_SWDATAB_DATA_SHIFT                   (0U)
/*! DATA - Data byte to send to master */
#define I3C_SWDATAB_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAB_DATA_SHIFT)) & I3C_SWDATAB_DATA_MASK)

#define I3C_SWDATAB_END_MASK                     (0x100U)
#define I3C_SWDATAB_END_SHIFT                    (8U)
/*! END - End */
#define I3C_SWDATAB_END(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAB_END_SHIFT)) & I3C_SWDATAB_END_MASK)

#define I3C_SWDATAB_END_ALSO_MASK                (0x10000U)
#define I3C_SWDATAB_END_ALSO_SHIFT               (16U)
/*! END_ALSO - End also */
#define I3C_SWDATAB_END_ALSO(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAB_END_ALSO_SHIFT)) & I3C_SWDATAB_END_ALSO_MASK)
/*! @} */

/*! @name SWDATABE - Target Write Data Byte End */
/*! @{ */

#define I3C_SWDATABE_DATA_MASK                   (0xFFU)
#define I3C_SWDATABE_DATA_SHIFT                  (0U)
/*! DATA - Data byte to send to master. */
#define I3C_SWDATABE_DATA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SWDATABE_DATA_SHIFT)) & I3C_SWDATABE_DATA_MASK)
/*! @} */

/*! @name SWDATAH - Target Write Data Half-word Register */
/*! @{ */

#define I3C_SWDATAH_DATA0_MASK                   (0xFFU)
#define I3C_SWDATAH_DATA0_SHIFT                  (0U)
/*! DATA0 - The 1st byte to send to the controller */
#define I3C_SWDATAH_DATA0(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAH_DATA0_SHIFT)) & I3C_SWDATAH_DATA0_MASK)

#define I3C_SWDATAH_DATA1_MASK                   (0xFF00U)
#define I3C_SWDATAH_DATA1_SHIFT                  (8U)
/*! DATA1 - The 2nd byte to send to the controller */
#define I3C_SWDATAH_DATA1(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAH_DATA1_SHIFT)) & I3C_SWDATAH_DATA1_MASK)

#define I3C_SWDATAH_END_MASK                     (0x10000U)
#define I3C_SWDATAH_END_SHIFT                    (16U)
/*! END - End of message */
#define I3C_SWDATAH_END(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAH_END_SHIFT)) & I3C_SWDATAH_END_MASK)
/*! @} */

/*! @name SWDATAHE - Target Write Data Half-word End Register */
/*! @{ */

#define I3C_SWDATAHE_DATA0_MASK                  (0xFFU)
#define I3C_SWDATAHE_DATA0_SHIFT                 (0U)
/*! DATA0 - The 1st byte to send to the controller */
#define I3C_SWDATAHE_DATA0(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAHE_DATA0_SHIFT)) & I3C_SWDATAHE_DATA0_MASK)

#define I3C_SWDATAHE_DATA1_MASK                  (0xFF00U)
#define I3C_SWDATAHE_DATA1_SHIFT                 (8U)
/*! DATA1 - The 2nd byte to send to the controller */
#define I3C_SWDATAHE_DATA1(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAHE_DATA1_SHIFT)) & I3C_SWDATAHE_DATA1_MASK)
/*! @} */

/*! @name SRDATAB - Target Read Data Byte Register */
/*! @{ */

#define I3C_SRDATAB_DATA0_MASK                   (0xFFU)
#define I3C_SRDATAB_DATA0_SHIFT                  (0U)
/*! DATA0 - Byte read from the controller */
#define I3C_SRDATAB_DATA0(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SRDATAB_DATA0_SHIFT)) & I3C_SRDATAB_DATA0_MASK)
/*! @} */

/*! @name SRDATAH - Target Read Data Half-word Register */
/*! @{ */

#define I3C_SRDATAH_LSB_MASK                     (0xFFU)
#define I3C_SRDATAH_LSB_SHIFT                    (0U)
/*! LSB - Represents the first byte read from the controller (and written by the target). */
#define I3C_SRDATAH_LSB(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SRDATAH_LSB_SHIFT)) & I3C_SRDATAH_LSB_MASK)

#define I3C_SRDATAH_MSB_MASK                     (0xFF00U)
#define I3C_SRDATAH_MSB_SHIFT                    (8U)
/*! MSB - Represents the second byte read from the controller (and written by the target). */
#define I3C_SRDATAH_MSB(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_SRDATAH_MSB_SHIFT)) & I3C_SRDATAH_MSB_MASK)
/*! @} */

/*! @name SWDATAB1 - Target Write Data Byte Register */
/*! @{ */

#define I3C_SWDATAB1_DATA_MASK                   (0xFFU)
#define I3C_SWDATAB1_DATA_SHIFT                  (0U)
/*! DATA - Byte rto send to controller */
#define I3C_SWDATAB1_DATA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SWDATAB1_DATA_SHIFT)) & I3C_SWDATAB1_DATA_MASK)
/*! @} */

/*! @name SCAPABILITIES - Target Capabilities Register */
/*! @{ */

#define I3C_SCAPABILITIES_IDENA_MASK             (0x3U)
#define I3C_SCAPABILITIES_IDENA_SHIFT            (0U)
/*! IDENA - ID 48b handler
 *  0b00..APPLICATION: Application handles ID 48b
 *  0b01..HW: Hardware handles ID 48b
 *  0b10..HW_BUT: in hardware but the I3C module instance handles ID 48b.
 *  0b11..PARTNO: a part number register (PARTNO) handles ID 48b
 */
#define I3C_SCAPABILITIES_IDENA(x)               (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_IDENA_SHIFT)) & I3C_SCAPABILITIES_IDENA_MASK)

#define I3C_SCAPABILITIES_IDREG_MASK             (0x3CU)
#define I3C_SCAPABILITIES_IDREG_SHIFT            (2U)
/*! IDREG - ID register */
#define I3C_SCAPABILITIES_IDREG(x)               (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_IDREG_SHIFT)) & I3C_SCAPABILITIES_IDREG_MASK)

#define I3C_SCAPABILITIES_HDRSUPP_MASK           (0xC0U)
#define I3C_SCAPABILITIES_HDRSUPP_SHIFT          (6U)
/*! HDRSUPP - HDR support */
#define I3C_SCAPABILITIES_HDRSUPP(x)             (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_HDRSUPP_SHIFT)) & I3C_SCAPABILITIES_HDRSUPP_MASK)

#define I3C_SCAPABILITIES_MASTER_MASK            (0x200U)
#define I3C_SCAPABILITIES_MASTER_SHIFT           (9U)
/*! MASTER - Controller
 *  0b0..MASTERNOTSUPPORTED: controller capability is not supported.
 *  0b1..MASTERSUPPORTED: controller capability is supported.
 */
#define I3C_SCAPABILITIES_MASTER(x)              (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_MASTER_SHIFT)) & I3C_SCAPABILITIES_MASTER_MASK)

#define I3C_SCAPABILITIES_SADDR_MASK             (0xC00U)
#define I3C_SCAPABILITIES_SADDR_SHIFT            (10U)
/*! SADDR - Static address
 *  0b00..NO_STATIC: No static address
 *  0b01..STATIC: Static address is fixed in hardware
 *  0b10..HW_CONTROL: Hardware controls the static address dynamically (for example, from the pin strap)
 *  0b11..CONFIG: SCONFIG register supplies the static address
 */
#define I3C_SCAPABILITIES_SADDR(x)               (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_SADDR_SHIFT)) & I3C_SCAPABILITIES_SADDR_MASK)

#define I3C_SCAPABILITIES_CCCHANDLE_MASK         (0xF000U)
#define I3C_SCAPABILITIES_CCCHANDLE_SHIFT        (12U)
/*! CCCHANDLE - Common Command Codes (CCC) handling */
#define I3C_SCAPABILITIES_CCCHANDLE(x)           (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_CCCHANDLE_SHIFT)) & I3C_SCAPABILITIES_CCCHANDLE_MASK)

#define I3C_SCAPABILITIES_IBI_MR_HJ_MASK         (0x1F0000U)
#define I3C_SCAPABILITIES_IBI_MR_HJ_SHIFT        (16U)
/*! IBI_MR_HJ - In-Band Interrupts, Controller Requests, Hot Join events */
#define I3C_SCAPABILITIES_IBI_MR_HJ(x)           (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_IBI_MR_HJ_SHIFT)) & I3C_SCAPABILITIES_IBI_MR_HJ_MASK)

#define I3C_SCAPABILITIES_TIMECTRL_MASK          (0x200000U)
#define I3C_SCAPABILITIES_TIMECTRL_SHIFT         (21U)
/*! TIMECTRL - Time control
 *  0b0..NO_TIME_CONTROL_TYPE: No time control is enabled
 *  0b1..ATLEAST1_TIME_CONTROL: at least one time-control type is supported
 */
#define I3C_SCAPABILITIES_TIMECTRL(x)            (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_TIMECTRL_SHIFT)) & I3C_SCAPABILITIES_TIMECTRL_MASK)

#define I3C_SCAPABILITIES_EXTFIFO_MASK           (0x3800000U)
#define I3C_SCAPABILITIES_EXTFIFO_SHIFT          (23U)
/*! EXTFIFO - External FIFO
 *  0b000..NO_EXT_FIFO: No external FIFO is available
 *  0b001..STD_EXT_FIFO: standard available/free external FIFO
 *  0b010..REQUEST_EXT_FIFO: request track external FIFO
 *  0b011..RESERVED
 */
#define I3C_SCAPABILITIES_EXTFIFO(x)             (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_EXTFIFO_SHIFT)) & I3C_SCAPABILITIES_EXTFIFO_MASK)

#define I3C_SCAPABILITIES_FIFOTX_MASK            (0xC000000U)
#define I3C_SCAPABILITIES_FIFOTX_SHIFT           (26U)
/*! FIFOTX - FIFO transmit
 *  0b00..FIFO_2BYTE: 2-byte TX FIFO, the default FIFO transmit value (FIFOTX)
 *  0b01..FIFO_4BYTE: 4-byte TX FIFO
 *  0b10..FIFO_8BYTE: 8-byte TX FIFO
 *  0b11..FIFO_16BYTE: 16-byte TX FIFO
 */
#define I3C_SCAPABILITIES_FIFOTX(x)              (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_FIFOTX_SHIFT)) & I3C_SCAPABILITIES_FIFOTX_MASK)

#define I3C_SCAPABILITIES_FIFORX_MASK            (0x30000000U)
#define I3C_SCAPABILITIES_FIFORX_SHIFT           (28U)
/*! FIFORX - FIFO receive
 *  0b00..FIFO_2BYTE: 2 (or 3)-byte RX FIFO, the default FIFO receive value (FIFORX)
 *  0b01..FIFO_4BYTE: 4-byte RX FIFO
 *  0b10..FIFO_8BYTE: 8-byte RX FIFO
 *  0b11..FIFO_16BYTE: 16-byte RX FIFO
 */
#define I3C_SCAPABILITIES_FIFORX(x)              (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_FIFORX_SHIFT)) & I3C_SCAPABILITIES_FIFORX_MASK)

#define I3C_SCAPABILITIES_INT_MASK               (0x40000000U)
#define I3C_SCAPABILITIES_INT_SHIFT              (30U)
/*! INT - INT
 *  0b1..Interrupts are supported
 *  0b0..Interrupts are not supported
 */
#define I3C_SCAPABILITIES_INT(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_INT_SHIFT)) & I3C_SCAPABILITIES_INT_MASK)

#define I3C_SCAPABILITIES_DMA_MASK               (0x80000000U)
#define I3C_SCAPABILITIES_DMA_SHIFT              (31U)
/*! DMA - DMA
 *  0b1..DMA is supported
 *  0b0..DMA is not supported
 */
#define I3C_SCAPABILITIES_DMA(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SCAPABILITIES_DMA_SHIFT)) & I3C_SCAPABILITIES_DMA_MASK)
/*! @} */

/*! @name SDYNADDR - Slave Dynamic Address Register */
/*! @{ */

#define I3C_SDYNADDR_DAVALID_MASK                (0x1U)
#define I3C_SDYNADDR_DAVALID_SHIFT               (0U)
/*! DAVALID - DAVALID
 *  0b0..DANOTASSIGNED: a Dynamic Address is not assigned
 *  0b1..DAASSIGNED: a Dynamic Address is assigned
 */
#define I3C_SDYNADDR_DAVALID(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SDYNADDR_DAVALID_SHIFT)) & I3C_SDYNADDR_DAVALID_MASK)

#define I3C_SDYNADDR_DADDR_MASK                  (0xFEU)
#define I3C_SDYNADDR_DADDR_SHIFT                 (1U)
/*! DADDR - Dynamic address */
#define I3C_SDYNADDR_DADDR(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SDYNADDR_DADDR_SHIFT)) & I3C_SDYNADDR_DADDR_MASK)

#define I3C_SDYNADDR_MAPIDX_MASK                 (0xF00U)
#define I3C_SDYNADDR_MAPIDX_SHIFT                (8U)
/*! MAPIDX - Mapped Dynamic Address */
#define I3C_SDYNADDR_MAPIDX(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SDYNADDR_MAPIDX_SHIFT)) & I3C_SDYNADDR_MAPIDX_MASK)

#define I3C_SDYNADDR_MAPSA_MASK                  (0x1000U)
#define I3C_SDYNADDR_MAPSA_SHIFT                 (12U)
/*! MAPSA - Map a Static Address */
#define I3C_SDYNADDR_MAPSA(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_SDYNADDR_MAPSA_SHIFT)) & I3C_SDYNADDR_MAPSA_MASK)

#define I3C_SDYNADDR_KEY_MASK                    (0xFFFF0000U)
#define I3C_SDYNADDR_KEY_SHIFT                   (16U)
/*! KEY - Key */
#define I3C_SDYNADDR_KEY(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SDYNADDR_KEY_SHIFT)) & I3C_SDYNADDR_KEY_MASK)
/*! @} */

/*! @name SMAXLIMITS - Target Maximum Limits Register */
/*! @{ */

#define I3C_SMAXLIMITS_MAXRD_MASK                (0xFFFU)
#define I3C_SMAXLIMITS_MAXRD_SHIFT               (0U)
/*! MAXRD - Maximum read length */
#define I3C_SMAXLIMITS_MAXRD(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SMAXLIMITS_MAXRD_SHIFT)) & I3C_SMAXLIMITS_MAXRD_MASK)

#define I3C_SMAXLIMITS_MAXWR_MASK                (0xFFF0000U)
#define I3C_SMAXLIMITS_MAXWR_SHIFT               (16U)
/*! MAXWR - Maximum write length */
#define I3C_SMAXLIMITS_MAXWR(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SMAXLIMITS_MAXWR_SHIFT)) & I3C_SMAXLIMITS_MAXWR_MASK)
/*! @} */

/*! @name SIDPARTNO - Target ID Part Number Register */
/*! @{ */

#define I3C_SIDPARTNO_PARTNO_MASK                (0xFFFFFFFFU)
#define I3C_SIDPARTNO_PARTNO_SHIFT               (0U)
/*! PARTNO - Part number */
#define I3C_SIDPARTNO_PARTNO(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SIDPARTNO_PARTNO_SHIFT)) & I3C_SIDPARTNO_PARTNO_MASK)
/*! @} */

/*! @name SIDEXT - Target ID Extension Register */
/*! @{ */

#define I3C_SIDEXT_DCR_MASK                      (0xFF00U)
#define I3C_SIDEXT_DCR_SHIFT                     (8U)
/*! DCR - Device Characteristic Register */
#define I3C_SIDEXT_DCR(x)                        (((uint32_t)(((uint32_t)(x)) << I3C_SIDEXT_DCR_SHIFT)) & I3C_SIDEXT_DCR_MASK)

#define I3C_SIDEXT_BCR_MASK                      (0xFF0000U)
#define I3C_SIDEXT_BCR_SHIFT                     (16U)
/*! BCR - Bus Characteristics Register */
#define I3C_SIDEXT_BCR(x)                        (((uint32_t)(((uint32_t)(x)) << I3C_SIDEXT_BCR_SHIFT)) & I3C_SIDEXT_BCR_MASK)
/*! @} */

/*! @name SVENDORID - Target Vendor ID Register */
/*! @{ */

#define I3C_SVENDORID_VID_MASK                   (0x7FFFU)
#define I3C_SVENDORID_VID_SHIFT                  (0U)
/*! VID - Vendor ID */
#define I3C_SVENDORID_VID(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SVENDORID_VID_SHIFT)) & I3C_SVENDORID_VID_MASK)
/*! @} */

/*! @name STCCLOCK - Target Time Control Clock Register */
/*! @{ */

#define I3C_STCCLOCK_ACCURACY_MASK               (0xFFU)
#define I3C_STCCLOCK_ACCURACY_SHIFT              (0U)
/*! ACCURACY - Clock accuracy */
#define I3C_STCCLOCK_ACCURACY(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_STCCLOCK_ACCURACY_SHIFT)) & I3C_STCCLOCK_ACCURACY_MASK)

#define I3C_STCCLOCK_FREQ_MASK                   (0xFF00U)
#define I3C_STCCLOCK_FREQ_SHIFT                  (8U)
/*! FREQ - Clock frequency */
#define I3C_STCCLOCK_FREQ(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_STCCLOCK_FREQ_SHIFT)) & I3C_STCCLOCK_FREQ_MASK)
/*! @} */

/*! @name SMSGLAST - Target Message Last Matched Register */
/*! @{ */

#define I3C_SMSGLAST_MAPLAST_MASK                (0xFU)
#define I3C_SMSGLAST_MAPLAST_SHIFT               (0U)
/*! MAPLAST - Matched address index */
#define I3C_SMSGLAST_MAPLAST(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_MAPLAST_SHIFT)) & I3C_SMSGLAST_MAPLAST_MASK)

#define I3C_SMSGLAST_LASTSTATIC_MASK             (0x10U)
#define I3C_SMSGLAST_LASTSTATIC_SHIFT            (4U)
/*! LASTSTATIC - Last Static Address Matched */
#define I3C_SMSGLAST_LASTSTATIC(x)               (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTSTATIC_SHIFT)) & I3C_SMSGLAST_LASTSTATIC_MASK)

#define I3C_SMSGLAST_LASTGROUP_MASK              (0x20U)
#define I3C_SMSGLAST_LASTGROUP_SHIFT             (5U)
/*! LASTGROUP - Last Match Was Group */
#define I3C_SMSGLAST_LASTGROUP(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTGROUP_SHIFT)) & I3C_SMSGLAST_LASTGROUP_MASK)

#define I3C_SMSGLAST_LASTMODE_MASK               (0xC0U)
#define I3C_SMSGLAST_LASTMODE_SHIFT              (6U)
/*! LASTMODE - Last Mode
 *  0b00..SDR mode (or I2C if static) was the last mode.
 *  0b01..HDR-DDR was the last mode.
 *  0b10..HDR-BT was the last mode.
 *  0b11..RESERVED
 */
#define I3C_SMSGLAST_LASTMODE(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTMODE_SHIFT)) & I3C_SMSGLAST_LASTMODE_MASK)

#define I3C_SMSGLAST_MAPLASTM1_MASK              (0xF00U)
#define I3C_SMSGLAST_MAPLASTM1_SHIFT             (8U)
/*! MAPLASTM1 - Previous match index 1 */
#define I3C_SMSGLAST_MAPLASTM1(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_MAPLASTM1_SHIFT)) & I3C_SMSGLAST_MAPLASTM1_MASK)

#define I3C_SMSGLAST_LASTGROUPM1_MASK            (0x2000U)
#define I3C_SMSGLAST_LASTGROUPM1_SHIFT           (13U)
/*! LASTGROUPM1 - Last Match 1 Previous Was Group */
#define I3C_SMSGLAST_LASTGROUPM1(x)              (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTGROUPM1_SHIFT)) & I3C_SMSGLAST_LASTGROUPM1_MASK)

#define I3C_SMSGLAST_LASTMODE1_MASK              (0xC000U)
#define I3C_SMSGLAST_LASTMODE1_SHIFT             (14U)
/*! LASTMODE1 - Last Mode 1
 *  0b00..SDR mode (or I2C if static) was the last mode.
 *  0b01..HDR-DDR was the last mode.
 *  0b10..HDR-BT was the last mode.
 *  0b11..RESERVED
 */
#define I3C_SMSGLAST_LASTMODE1(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTMODE1_SHIFT)) & I3C_SMSGLAST_LASTMODE1_MASK)

#define I3C_SMSGLAST_MAPLASTM2_MASK              (0xF0000U)
#define I3C_SMSGLAST_MAPLASTM2_SHIFT             (16U)
/*! MAPLASTM2 - Previous match index 2 */
#define I3C_SMSGLAST_MAPLASTM2(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_MAPLASTM2_SHIFT)) & I3C_SMSGLAST_MAPLASTM2_MASK)

#define I3C_SMSGLAST_LASTGROUPM2_MASK            (0x200000U)
#define I3C_SMSGLAST_LASTGROUPM2_SHIFT           (21U)
/*! LASTGROUPM2 - Last Match 2 Previous Was Group */
#define I3C_SMSGLAST_LASTGROUPM2(x)              (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTGROUPM2_SHIFT)) & I3C_SMSGLAST_LASTGROUPM2_MASK)

#define I3C_SMSGLAST_LASTMODE2_MASK              (0xC00000U)
#define I3C_SMSGLAST_LASTMODE2_SHIFT             (22U)
/*! LASTMODE2 - Last Mode 2
 *  0b00..SDR mode (or I2C if static) was the last mode 2 previous accesses ago.
 *  0b01..HDR-DDR was the last mode 2 previous accesses ago.
 *  0b10..HDR-BT was the last mode 2 previous accesses ago.
 *  0b11..RESERVED
 */
#define I3C_SMSGLAST_LASTMODE2(x)                (((uint32_t)(((uint32_t)(x)) << I3C_SMSGLAST_LASTMODE2_SHIFT)) & I3C_SMSGLAST_LASTMODE2_MASK)
/*! @} */

/*! @name MCTRL - Controller Main Control Register */
/*! @{ */

#define I3C_MCTRL_REQUEST_MASK                   (0x7U)
#define I3C_MCTRL_REQUEST_SHIFT                  (0U)
/*! REQUEST - Request
 *  0b000..NONE: Indicates that no request is present. The REQUEST field returns to NONE when finished with any
 *         request. The MSTATUS register indicates the state of the controller. See also AutoIBI mode. NONE is only
 *         written as 0: writing 1 to MCTRL[RDTERM] (to stop a read in progress) or when setting MCTRL[IBIRESP] for
 *         MSG use.
 *  0b001..EMITSTARTADDR: Emit START with address and direction from a stopped state or in the middle of a Single
 *         Data Rate (SDR) message. If from a stopped state (IDLE), then emit start may be prevented by an event
 *         (like IBI, MR, HJ), in which case the appropriate interrupt is signaled; note that Emit START can be
 *         resubmitted.
 *  0b010..EMITSTOP: Emit a STOP on bus. Must be in Single Data Rate (SDR) mode. If in Dynamic Address Assignment
 *         (DAA) mode, Emit stop will exit DAA mode.
 *  0b011..IBIACKNACK: Manual In-Band Interrupt (IBI) Acknowledge (ACK) or Not Acknowledge (NACK). When IBIRESP
 *         has indicated a hold on an In-Band Interrupt to allow a manual decision, this request completes it. Uses
 *         IBIRESP to provide the information.
 *  0b100..PROCESSDAA: If not currently in Dynamic Address Assignment (DAA) mode, emits START, 7E, ENTDAA
 *         sequence, then emits 7E/R to process the first target. Stops just before the new Dynamic Address (DA) is to be
 *         emitted. The DA is written using Controller Write Data Byte (MWDATAB), then Process DAA is requested
 *         again to write the new address, and then it starts the next unless marked to STOP. An MSTATUS indicating
 *         NACK means DA was not accepted (for example, parity error). If PROCESSDAA is NACKED on the 7E/R request,
 *         meaning no more targets need a DA, then a COMPLETE is signaled (along with DONE) and a STOP issued. If
 *         TYPE = 2 or TYPE = 3, the DA is assigned and then it emits a STOP (instead of starting a new 7E/R request).
 *         If TYPE = 1 or TYPE = 3, then the DA is taken from the ADDR field (bits 6:0).
 *  0b101..RESERVED
 *  0b110..FORCEEXIT and IBHR: Emit an Exit Pattern from any state. End Double Data Rate (DDR) mode (including
 *         MSGDDR), including a STOP afterward. If MCTRL[TYPE] is 2, perform a Target Reset action (RSTACT can prevent
 *         the reset in the target). Target Reset may follow immediately after RSTACT CCC or after STOP.
 *  0b111..AUTOIBI: Hold in a stopped state, but auto-emit START,7E when the target is holding down SDA to get an
 *         In-Band Interrupt (IBI). Actual In-Band Interrupt handling is defined by IBIRESP.
 */
#define I3C_MCTRL_REQUEST(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_REQUEST_SHIFT)) & I3C_MCTRL_REQUEST_MASK)

#define I3C_MCTRL_TYPE_MASK                      (0x30U)
#define I3C_MCTRL_TYPE_SHIFT                     (4U)
/*! TYPE - Bus type with START
 *  0b00..I3C: Normally the SDR mode of I3C. For ForceExit, the Exit pattern.
 *  0b01..I2C: Normally the Standard I2C protocol.
 *  0b10..DDR: (Double Data Rate): Normally the HDR-DDR mode of I3C. Enter DDR mode (7E and then ENTHDR0), if the
 *        module is not already in DDR mode. The 1st byte written to the TX FIFO should be a command, and should
 *        already be in the FIFO. To end DDR mode, use ForceExit. For ForceExit, the normal IBHR (In-Band Hardware
 *        Reset).
 *  0b11..For ForcedExit, this is forced IBHR.
 */
#define I3C_MCTRL_TYPE(x)                        (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_TYPE_SHIFT)) & I3C_MCTRL_TYPE_MASK)

#define I3C_MCTRL_IBIRESP_MASK                   (0xC0U)
#define I3C_MCTRL_IBIRESP_SHIFT                  (6U)
/*! IBIRESP - In-Band Interrupt (IBI) response
 *  0b00..ACK (acknowledge). When REQUEST = 1 (EmitStartAddr) or REQUEST = 7 (AutoIBI), ACK with mandatory byte
 *        (or not), decided by the Controller In-band Interrupt Registry and Rules (MIBIRULES) register. When REQUEST
 *        = 3 (IBIAckNack), ACK with no mandatory byte.
 *  0b01..NACK: Not acknowledge
 *  0b10..Acknowledge with mandatory byte. When REQUEST = 1 or REQUEST = 7, ignore the MIBIRULES register. Do not
 *        use this setting unless only targets with a mandatory byte can cause an IBI. When REQUEST = 3, ACK with
 *        mandatory byte.
 *  0b11..Manual. When REQUEST = 1 or REQUEST = 7, stop and wait for a decision using the IBI ACK NACK request. When REQUEST = 3, reserved.
 */
#define I3C_MCTRL_IBIRESP(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_IBIRESP_SHIFT)) & I3C_MCTRL_IBIRESP_MASK)

#define I3C_MCTRL_DIR_MASK                       (0x100U)
#define I3C_MCTRL_DIR_SHIFT                      (8U)
/*! DIR - DIR
 *  0b0..DIRWRITE: Write
 *  0b1..DIRREAD: Read
 */
#define I3C_MCTRL_DIR(x)                         (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_DIR_SHIFT)) & I3C_MCTRL_DIR_MASK)

#define I3C_MCTRL_ADDR_MASK                      (0xFE00U)
#define I3C_MCTRL_ADDR_SHIFT                     (9U)
/*! ADDR - ADDR */
#define I3C_MCTRL_ADDR(x)                        (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_ADDR_SHIFT)) & I3C_MCTRL_ADDR_MASK)

#define I3C_MCTRL_RDTERM_MASK                    (0xFF0000U)
#define I3C_MCTRL_RDTERM_SHIFT                   (16U)
/*! RDTERM - Read terminate */
#define I3C_MCTRL_RDTERM(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_MCTRL_RDTERM_SHIFT)) & I3C_MCTRL_RDTERM_MASK)
/*! @} */

/*! @name MSTATUS - Controller Status Register */
/*! @{ */

#define I3C_MSTATUS_STATE_MASK                   (0x7U)
#define I3C_MSTATUS_STATE_SHIFT                  (0U)
/*! STATE - State of the controller
 *  0b000..IDLE: the bus has stopped.
 *  0b001..SLVREQ: Target request. The bus has STOPped but a target is holding SDA low. If using auto-emit IBI (
 *         MCTRL[REQUEST] = 7), the controller will not remain in this state.
 *  0b010..MSGSDR: Single Data Rate Message mode, from using MWMSG_SDR
 *  0b011..NORMACT: normal active Single Data Rate (SDR) state (from using MCTRL and MWDATAn and MRDATAn
 *         registers). The controller will stay in the NORMACT state until a STOP is issued.
 *  0b100..MSGDDR: Double Data Rate (DDR) Message mode (from using MWMSG_DDR or using the normal method with DDR).
 *         The controller will stay in the DDR state, until the controller exits using EXIT (emits the Exit
 *         pattern).
 *  0b101..DAA: in Enter Dynamic Address Assignment (ENTDAA) mode
 *  0b110..IBIACK: waiting for an In-Band Interrupt (IBI) ACK/NACK decision
 *  0b111..IBIRCV: Receiving an In-Band Interrupt (IBI); this IBIRCV state is used after IBI/MR/HJ has won the
 *         arbitration, and IBIRCV state is also used for IBI mandatory byte (if any) and any bytes that follow.
 */
#define I3C_MSTATUS_STATE(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_STATE_SHIFT)) & I3C_MSTATUS_STATE_MASK)

#define I3C_MSTATUS_BETWEEN_MASK                 (0x10U)
#define I3C_MSTATUS_BETWEEN_SHIFT                (4U)
/*! BETWEEN - Between messages or Dynamic Address Assignments (DAA) */
#define I3C_MSTATUS_BETWEEN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_BETWEEN_SHIFT)) & I3C_MSTATUS_BETWEEN_MASK)

#define I3C_MSTATUS_NACKED_MASK                  (0x20U)
#define I3C_MSTATUS_NACKED_SHIFT                 (5U)
/*! NACKED - Not acknowledged */
#define I3C_MSTATUS_NACKED(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_NACKED_SHIFT)) & I3C_MSTATUS_NACKED_MASK)

#define I3C_MSTATUS_IBITYPE_MASK                 (0xC0U)
#define I3C_MSTATUS_IBITYPE_SHIFT                (6U)
/*! IBITYPE - In-Band Interrupt (IBI) type
 *  0b00..NONE: No IBI. This status occurs when MSTATUS[IBIWON] becomes 0.
 *  0b01..IBI: In-Band Interrupt
 *  0b10..MR: Controller Request
 *  0b11..HJ: Hot-Join
 */
#define I3C_MSTATUS_IBITYPE(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_IBITYPE_SHIFT)) & I3C_MSTATUS_IBITYPE_MASK)

#define I3C_MSTATUS_SLVSTART_MASK                (0x100U)
#define I3C_MSTATUS_SLVSTART_SHIFT               (8U)
/*! SLVSTART - Target start */
#define I3C_MSTATUS_SLVSTART(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_SLVSTART_SHIFT)) & I3C_MSTATUS_SLVSTART_MASK)

#define I3C_MSTATUS_MCTRLDONE_MASK               (0x200U)
#define I3C_MSTATUS_MCTRLDONE_SHIFT              (9U)
/*! MCTRLDONE - Controller control done */
#define I3C_MSTATUS_MCTRLDONE(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_MCTRLDONE_SHIFT)) & I3C_MSTATUS_MCTRLDONE_MASK)

#define I3C_MSTATUS_COMPLETE_MASK                (0x400U)
#define I3C_MSTATUS_COMPLETE_SHIFT               (10U)
/*! COMPLETE - COMPLETE */
#define I3C_MSTATUS_COMPLETE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_COMPLETE_SHIFT)) & I3C_MSTATUS_COMPLETE_MASK)

#define I3C_MSTATUS_RXPEND_MASK                  (0x800U)
#define I3C_MSTATUS_RXPEND_SHIFT                 (11U)
/*! RXPEND - RXPEND */
#define I3C_MSTATUS_RXPEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_RXPEND_SHIFT)) & I3C_MSTATUS_RXPEND_MASK)

#define I3C_MSTATUS_TXNOTFULL_MASK               (0x1000U)
#define I3C_MSTATUS_TXNOTFULL_SHIFT              (12U)
/*! TXNOTFULL - TX Buffer or FIFO Not Full */
#define I3C_MSTATUS_TXNOTFULL(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_TXNOTFULL_SHIFT)) & I3C_MSTATUS_TXNOTFULL_MASK)

#define I3C_MSTATUS_IBIWON_MASK                  (0x2000U)
#define I3C_MSTATUS_IBIWON_SHIFT                 (13U)
/*! IBIWON - In-Band Interrupt (IBI) won */
#define I3C_MSTATUS_IBIWON(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_IBIWON_SHIFT)) & I3C_MSTATUS_IBIWON_MASK)

#define I3C_MSTATUS_ERRWARN_MASK                 (0x8000U)
#define I3C_MSTATUS_ERRWARN_SHIFT                (15U)
/*! ERRWARN - Error or warning */
#define I3C_MSTATUS_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_ERRWARN_SHIFT)) & I3C_MSTATUS_ERRWARN_MASK)

#define I3C_MSTATUS_NOWMASTER_MASK               (0x80000U)
#define I3C_MSTATUS_NOWMASTER_SHIFT              (19U)
/*! NOWMASTER - Now controller (now this module is a controller) */
#define I3C_MSTATUS_NOWMASTER(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_NOWMASTER_SHIFT)) & I3C_MSTATUS_NOWMASTER_MASK)

#define I3C_MSTATUS_IBIADDR_MASK                 (0x7F000000U)
#define I3C_MSTATUS_IBIADDR_SHIFT                (24U)
/*! IBIADDR - IBI address */
#define I3C_MSTATUS_IBIADDR(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MSTATUS_IBIADDR_SHIFT)) & I3C_MSTATUS_IBIADDR_MASK)
/*! @} */

/*! @name MIBIRULES - Controller In-band Interrupt Registry and Rules Register */
/*! @{ */

#define I3C_MIBIRULES_ADDR0_MASK                 (0x3FU)
#define I3C_MIBIRULES_ADDR0_SHIFT                (0U)
/*! ADDR0 - ADDR0 */
#define I3C_MIBIRULES_ADDR0(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_ADDR0_SHIFT)) & I3C_MIBIRULES_ADDR0_MASK)

#define I3C_MIBIRULES_ADDR1_MASK                 (0xFC0U)
#define I3C_MIBIRULES_ADDR1_SHIFT                (6U)
/*! ADDR1 - ADDR1 */
#define I3C_MIBIRULES_ADDR1(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_ADDR1_SHIFT)) & I3C_MIBIRULES_ADDR1_MASK)

#define I3C_MIBIRULES_ADDR2_MASK                 (0x3F000U)
#define I3C_MIBIRULES_ADDR2_SHIFT                (12U)
/*! ADDR2 - ADDR2 */
#define I3C_MIBIRULES_ADDR2(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_ADDR2_SHIFT)) & I3C_MIBIRULES_ADDR2_MASK)

#define I3C_MIBIRULES_ADDR3_MASK                 (0xFC0000U)
#define I3C_MIBIRULES_ADDR3_SHIFT                (18U)
/*! ADDR3 - ADDR3 */
#define I3C_MIBIRULES_ADDR3(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_ADDR3_SHIFT)) & I3C_MIBIRULES_ADDR3_MASK)

#define I3C_MIBIRULES_ADDR4_MASK                 (0x3F000000U)
#define I3C_MIBIRULES_ADDR4_SHIFT                (24U)
/*! ADDR4 - ADDR4 */
#define I3C_MIBIRULES_ADDR4(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_ADDR4_SHIFT)) & I3C_MIBIRULES_ADDR4_MASK)

#define I3C_MIBIRULES_MSB0_MASK                  (0x40000000U)
#define I3C_MIBIRULES_MSB0_SHIFT                 (30U)
/*! MSB0 - Set Most Significant address Bit to 0 */
#define I3C_MIBIRULES_MSB0(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_MSB0_SHIFT)) & I3C_MIBIRULES_MSB0_MASK)

#define I3C_MIBIRULES_NOBYTE_MASK                (0x80000000U)
#define I3C_MIBIRULES_NOBYTE_SHIFT               (31U)
/*! NOBYTE - No IBI byte */
#define I3C_MIBIRULES_NOBYTE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MIBIRULES_NOBYTE_SHIFT)) & I3C_MIBIRULES_NOBYTE_MASK)
/*! @} */

/*! @name MINTSET - Controller Interrupt Set Register */
/*! @{ */

#define I3C_MINTSET_SLVSTART_MASK                (0x100U)
#define I3C_MINTSET_SLVSTART_SHIFT               (8U)
/*! SLVSTART - Target start interrupt enable */
#define I3C_MINTSET_SLVSTART(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_SLVSTART_SHIFT)) & I3C_MINTSET_SLVSTART_MASK)

#define I3C_MINTSET_MCTRLDONE_MASK               (0x200U)
#define I3C_MINTSET_MCTRLDONE_SHIFT              (9U)
/*! MCTRLDONE - Controller control done interrupt enable */
#define I3C_MINTSET_MCTRLDONE(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_MCTRLDONE_SHIFT)) & I3C_MINTSET_MCTRLDONE_MASK)

#define I3C_MINTSET_COMPLETE_MASK                (0x400U)
#define I3C_MINTSET_COMPLETE_SHIFT               (10U)
/*! COMPLETE - Completed message interrupt enable */
#define I3C_MINTSET_COMPLETE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_COMPLETE_SHIFT)) & I3C_MINTSET_COMPLETE_MASK)

#define I3C_MINTSET_RXPEND_MASK                  (0x800U)
#define I3C_MINTSET_RXPEND_SHIFT                 (11U)
/*! RXPEND - RX pending interrupt enable */
#define I3C_MINTSET_RXPEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_RXPEND_SHIFT)) & I3C_MINTSET_RXPEND_MASK)

#define I3C_MINTSET_TXNOTFULL_MASK               (0x1000U)
#define I3C_MINTSET_TXNOTFULL_SHIFT              (12U)
/*! TXNOTFULL - TX buffer/FIFO is not full interrupt enable */
#define I3C_MINTSET_TXNOTFULL(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_TXNOTFULL_SHIFT)) & I3C_MINTSET_TXNOTFULL_MASK)

#define I3C_MINTSET_IBIWON_MASK                  (0x2000U)
#define I3C_MINTSET_IBIWON_SHIFT                 (13U)
/*! IBIWON - In-Band Interrupt (IBI) won interrupt enable */
#define I3C_MINTSET_IBIWON(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_IBIWON_SHIFT)) & I3C_MINTSET_IBIWON_MASK)

#define I3C_MINTSET_ERRWARN_MASK                 (0x8000U)
#define I3C_MINTSET_ERRWARN_SHIFT                (15U)
/*! ERRWARN - Error or warning (ERRWARN) interrupt enable */
#define I3C_MINTSET_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_ERRWARN_SHIFT)) & I3C_MINTSET_ERRWARN_MASK)

#define I3C_MINTSET_NOWMASTER_MASK               (0x80000U)
#define I3C_MINTSET_NOWMASTER_SHIFT              (19U)
/*! NOWMASTER - Now controller (now this I3C module is a controller) interrupt enable */
#define I3C_MINTSET_NOWMASTER(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTSET_NOWMASTER_SHIFT)) & I3C_MINTSET_NOWMASTER_MASK)
/*! @} */

/*! @name MINTCLR - Controller Interrupt Clear Register */
/*! @{ */

#define I3C_MINTCLR_SLVSTART_MASK                (0x100U)
#define I3C_MINTCLR_SLVSTART_SHIFT               (8U)
/*! SLVSTART - SLVSTART interrupt enable clear */
#define I3C_MINTCLR_SLVSTART(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_SLVSTART_SHIFT)) & I3C_MINTCLR_SLVSTART_MASK)

#define I3C_MINTCLR_MCTRLDONE_MASK               (0x200U)
#define I3C_MINTCLR_MCTRLDONE_SHIFT              (9U)
/*! MCTRLDONE - MCTRLDONE interrupt enable clear */
#define I3C_MINTCLR_MCTRLDONE(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_MCTRLDONE_SHIFT)) & I3C_MINTCLR_MCTRLDONE_MASK)

#define I3C_MINTCLR_COMPLETE_MASK                (0x400U)
#define I3C_MINTCLR_COMPLETE_SHIFT               (10U)
/*! COMPLETE - COMPLETE interrupt enable clear */
#define I3C_MINTCLR_COMPLETE(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_COMPLETE_SHIFT)) & I3C_MINTCLR_COMPLETE_MASK)

#define I3C_MINTCLR_RXPEND_MASK                  (0x800U)
#define I3C_MINTCLR_RXPEND_SHIFT                 (11U)
/*! RXPEND - RXPEND interrupt enable clear */
#define I3C_MINTCLR_RXPEND(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_RXPEND_SHIFT)) & I3C_MINTCLR_RXPEND_MASK)

#define I3C_MINTCLR_TXNOTFULL_MASK               (0x1000U)
#define I3C_MINTCLR_TXNOTFULL_SHIFT              (12U)
/*! TXNOTFULL - TXNOTFULL interrupt enable clear */
#define I3C_MINTCLR_TXNOTFULL(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_TXNOTFULL_SHIFT)) & I3C_MINTCLR_TXNOTFULL_MASK)

#define I3C_MINTCLR_IBIWON_MASK                  (0x2000U)
#define I3C_MINTCLR_IBIWON_SHIFT                 (13U)
/*! IBIWON - IBIWON interrupt enable clear */
#define I3C_MINTCLR_IBIWON(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_IBIWON_SHIFT)) & I3C_MINTCLR_IBIWON_MASK)

#define I3C_MINTCLR_ERRWARN_MASK                 (0x8000U)
#define I3C_MINTCLR_ERRWARN_SHIFT                (15U)
/*! ERRWARN - ERRWARN interrupt enable clear */
#define I3C_MINTCLR_ERRWARN(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_ERRWARN_SHIFT)) & I3C_MINTCLR_ERRWARN_MASK)

#define I3C_MINTCLR_NOWMASTER_MASK               (0x80000U)
#define I3C_MINTCLR_NOWMASTER_SHIFT              (19U)
/*! NOWMASTER - NOWMASTER interrupt enable clear */
#define I3C_MINTCLR_NOWMASTER(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTCLR_NOWMASTER_SHIFT)) & I3C_MINTCLR_NOWMASTER_MASK)
/*! @} */

/*! @name MINTMASKED - Controller Interrupt Mask Register */
/*! @{ */

#define I3C_MINTMASKED_SLVSTART_MASK             (0x100U)
#define I3C_MINTMASKED_SLVSTART_SHIFT            (8U)
/*! SLVSTART - SLVSTART interrupt mask */
#define I3C_MINTMASKED_SLVSTART(x)               (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_SLVSTART_SHIFT)) & I3C_MINTMASKED_SLVSTART_MASK)

#define I3C_MINTMASKED_MCTRLDONE_MASK            (0x200U)
#define I3C_MINTMASKED_MCTRLDONE_SHIFT           (9U)
/*! MCTRLDONE - MCTRLDONE interrupt mask */
#define I3C_MINTMASKED_MCTRLDONE(x)              (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_MCTRLDONE_SHIFT)) & I3C_MINTMASKED_MCTRLDONE_MASK)

#define I3C_MINTMASKED_COMPLETE_MASK             (0x400U)
#define I3C_MINTMASKED_COMPLETE_SHIFT            (10U)
/*! COMPLETE - COMPLETE interrupt mask */
#define I3C_MINTMASKED_COMPLETE(x)               (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_COMPLETE_SHIFT)) & I3C_MINTMASKED_COMPLETE_MASK)

#define I3C_MINTMASKED_RXPEND_MASK               (0x800U)
#define I3C_MINTMASKED_RXPEND_SHIFT              (11U)
/*! RXPEND - RXPEND interrupt mask */
#define I3C_MINTMASKED_RXPEND(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_RXPEND_SHIFT)) & I3C_MINTMASKED_RXPEND_MASK)

#define I3C_MINTMASKED_TXNOTFULL_MASK            (0x1000U)
#define I3C_MINTMASKED_TXNOTFULL_SHIFT           (12U)
/*! TXNOTFULL - TXNOTFULL interrupt mask */
#define I3C_MINTMASKED_TXNOTFULL(x)              (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_TXNOTFULL_SHIFT)) & I3C_MINTMASKED_TXNOTFULL_MASK)

#define I3C_MINTMASKED_IBIWON_MASK               (0x2000U)
#define I3C_MINTMASKED_IBIWON_SHIFT              (13U)
/*! IBIWON - IBIWON interrupt mask */
#define I3C_MINTMASKED_IBIWON(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_IBIWON_SHIFT)) & I3C_MINTMASKED_IBIWON_MASK)

#define I3C_MINTMASKED_ERRWARN_MASK              (0x8000U)
#define I3C_MINTMASKED_ERRWARN_SHIFT             (15U)
/*! ERRWARN - ERRWARN interrupt mask */
#define I3C_MINTMASKED_ERRWARN(x)                (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_ERRWARN_SHIFT)) & I3C_MINTMASKED_ERRWARN_MASK)

#define I3C_MINTMASKED_NOWMASTER_MASK            (0x80000U)
#define I3C_MINTMASKED_NOWMASTER_SHIFT           (19U)
/*! NOWMASTER - NOWMASTER interrupt mask */
#define I3C_MINTMASKED_NOWMASTER(x)              (((uint32_t)(((uint32_t)(x)) << I3C_MINTMASKED_NOWMASTER_SHIFT)) & I3C_MINTMASKED_NOWMASTER_MASK)
/*! @} */

/*! @name MERRWARN - Controller Errors and Warnings Register */
/*! @{ */

#define I3C_MERRWARN_URUN_MASK                   (0x2U)
#define I3C_MERRWARN_URUN_SHIFT                  (1U)
/*! URUN - Underrun error */
#define I3C_MERRWARN_URUN(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_URUN_SHIFT)) & I3C_MERRWARN_URUN_MASK)

#define I3C_MERRWARN_NACK_MASK                   (0x4U)
#define I3C_MERRWARN_NACK_SHIFT                  (2U)
/*! NACK - Not acknowledge (NACK) error */
#define I3C_MERRWARN_NACK(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_NACK_SHIFT)) & I3C_MERRWARN_NACK_MASK)

#define I3C_MERRWARN_WRABT_MASK                  (0x8U)
#define I3C_MERRWARN_WRABT_SHIFT                 (3U)
/*! WRABT - WRABT (Write abort) error */
#define I3C_MERRWARN_WRABT(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_WRABT_SHIFT)) & I3C_MERRWARN_WRABT_MASK)

#define I3C_MERRWARN_TERM_MASK                   (0x10U)
#define I3C_MERRWARN_TERM_SHIFT                  (4U)
/*! TERM - Terminate error */
#define I3C_MERRWARN_TERM(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_TERM_SHIFT)) & I3C_MERRWARN_TERM_MASK)

#define I3C_MERRWARN_HPAR_MASK                   (0x200U)
#define I3C_MERRWARN_HPAR_SHIFT                  (9U)
/*! HPAR - High data rate parity
 *  0b1..Error
 *  0b0..No error
 */
#define I3C_MERRWARN_HPAR(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_HPAR_SHIFT)) & I3C_MERRWARN_HPAR_MASK)

#define I3C_MERRWARN_HCRC_MASK                   (0x400U)
#define I3C_MERRWARN_HCRC_SHIFT                  (10U)
/*! HCRC - High data rate CRC error
 *  0b1..Error
 *  0b0..No error
 */
#define I3C_MERRWARN_HCRC(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_HCRC_SHIFT)) & I3C_MERRWARN_HCRC_MASK)

#define I3C_MERRWARN_OREAD_MASK                  (0x10000U)
#define I3C_MERRWARN_OREAD_SHIFT                 (16U)
/*! OREAD - Over-read error
 *  0b1..Error
 *  0b0..No error
 */
#define I3C_MERRWARN_OREAD(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_OREAD_SHIFT)) & I3C_MERRWARN_OREAD_MASK)

#define I3C_MERRWARN_OWRITE_MASK                 (0x20000U)
#define I3C_MERRWARN_OWRITE_SHIFT                (17U)
/*! OWRITE - Over-write error
 *  0b1..Error
 *  0b0..No error
 */
#define I3C_MERRWARN_OWRITE(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_OWRITE_SHIFT)) & I3C_MERRWARN_OWRITE_MASK)

#define I3C_MERRWARN_MSGERR_MASK                 (0x40000U)
#define I3C_MERRWARN_MSGERR_SHIFT                (18U)
/*! MSGERR - Message error */
#define I3C_MERRWARN_MSGERR(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_MSGERR_SHIFT)) & I3C_MERRWARN_MSGERR_MASK)

#define I3C_MERRWARN_INVREQ_MASK                 (0x80000U)
#define I3C_MERRWARN_INVREQ_SHIFT                (19U)
/*! INVREQ - Invalid request error */
#define I3C_MERRWARN_INVREQ(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_INVREQ_SHIFT)) & I3C_MERRWARN_INVREQ_MASK)

#define I3C_MERRWARN_TIMEOUT_MASK                (0x100000U)
#define I3C_MERRWARN_TIMEOUT_SHIFT               (20U)
/*! TIMEOUT - TIMEOUT error */
#define I3C_MERRWARN_TIMEOUT(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MERRWARN_TIMEOUT_SHIFT)) & I3C_MERRWARN_TIMEOUT_MASK)
/*! @} */

/*! @name MDMACTRL - Controller DMA Control Register */
/*! @{ */

#define I3C_MDMACTRL_DMAFB_MASK                  (0x3U)
#define I3C_MDMACTRL_DMAFB_SHIFT                 (0U)
/*! DMAFB - DMA from bus
 *  0b00..DMA is not used
 *  0b01..Enable DMA for one frame. STOP or repeated START causes DMAFB to automatically become 0. See SCONFIG[MATCHSS].
 *  0b10..Enable DMA until DMA is turned off
 */
#define I3C_MDMACTRL_DMAFB(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MDMACTRL_DMAFB_SHIFT)) & I3C_MDMACTRL_DMAFB_MASK)

#define I3C_MDMACTRL_DMATB_MASK                  (0xCU)
#define I3C_MDMACTRL_DMATB_SHIFT                 (2U)
/*! DMATB - DMA to bus
 *  0b00..DMA is not used
 *  0b01..Enable DMA for one frame (ended by DMA or Terminated). STOP or START causes DMATB to become 0. See SCONFIG[MATCHSS] .
 *  0b10..Enable DMA until DMA is turned off. Normally, DMA ENABLE should only be used in Controller Message mode.
 */
#define I3C_MDMACTRL_DMATB(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MDMACTRL_DMATB_SHIFT)) & I3C_MDMACTRL_DMATB_MASK)

#define I3C_MDMACTRL_DMAWIDTH_MASK               (0x30U)
#define I3C_MDMACTRL_DMAWIDTH_SHIFT              (4U)
/*! DMAWIDTH - DMA width
 *  0b00..BYTE
 *  0b01..BYTE_AGAIN
 *  0b10..HALF_WORD: Half-word (16 bits). This will make sure that 2 bytes are free/available in FIFO.
 *  0b11..RESERVED
 */
#define I3C_MDMACTRL_DMAWIDTH(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDMACTRL_DMAWIDTH_SHIFT)) & I3C_MDMACTRL_DMAWIDTH_MASK)
/*! @} */

/*! @name MDATACTRL - Controller Data Control Register */
/*! @{ */

#define I3C_MDATACTRL_FLUSHTB_MASK               (0x1U)
#define I3C_MDATACTRL_FLUSHTB_SHIFT              (0U)
/*! FLUSHTB - Flush to-bus buffer/FIFO */
#define I3C_MDATACTRL_FLUSHTB(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_FLUSHTB_SHIFT)) & I3C_MDATACTRL_FLUSHTB_MASK)

#define I3C_MDATACTRL_FLUSHFB_MASK               (0x2U)
#define I3C_MDATACTRL_FLUSHFB_SHIFT              (1U)
/*! FLUSHFB - Flush from-bus buffer/FIFO */
#define I3C_MDATACTRL_FLUSHFB(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_FLUSHFB_SHIFT)) & I3C_MDATACTRL_FLUSHFB_MASK)

#define I3C_MDATACTRL_UNLOCK_MASK                (0x8U)
#define I3C_MDATACTRL_UNLOCK_SHIFT               (3U)
/*! UNLOCK - Unlock */
#define I3C_MDATACTRL_UNLOCK(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_UNLOCK_SHIFT)) & I3C_MDATACTRL_UNLOCK_MASK)

#define I3C_MDATACTRL_TXTRIG_MASK                (0x30U)
#define I3C_MDATACTRL_TXTRIG_SHIFT               (4U)
/*! TXTRIG - Transmit trigger level */
#define I3C_MDATACTRL_TXTRIG(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_TXTRIG_SHIFT)) & I3C_MDATACTRL_TXTRIG_MASK)

#define I3C_MDATACTRL_RXTRIG_MASK                (0xC0U)
#define I3C_MDATACTRL_RXTRIG_SHIFT               (6U)
/*! RXTRIG - Receive trigger level */
#define I3C_MDATACTRL_RXTRIG(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_RXTRIG_SHIFT)) & I3C_MDATACTRL_RXTRIG_MASK)

#define I3C_MDATACTRL_TXCOUNT_MASK               (0x1F0000U)
#define I3C_MDATACTRL_TXCOUNT_SHIFT              (16U)
/*! TXCOUNT - Transmit Byte Count. */
#define I3C_MDATACTRL_TXCOUNT(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_TXCOUNT_SHIFT)) & I3C_MDATACTRL_TXCOUNT_MASK)

#define I3C_MDATACTRL_RXCOUNT_MASK               (0x1F000000U)
#define I3C_MDATACTRL_RXCOUNT_SHIFT              (24U)
/*! RXCOUNT - Receive Byte Count */
#define I3C_MDATACTRL_RXCOUNT(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_RXCOUNT_SHIFT)) & I3C_MDATACTRL_RXCOUNT_MASK)

#define I3C_MDATACTRL_TXFULL_MASK                (0x40000000U)
#define I3C_MDATACTRL_TXFULL_SHIFT               (30U)
/*! TXFULL - Transmit Is Full */
#define I3C_MDATACTRL_TXFULL(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_TXFULL_SHIFT)) & I3C_MDATACTRL_TXFULL_MASK)

#define I3C_MDATACTRL_RXEMPTY_MASK               (0x80000000U)
#define I3C_MDATACTRL_RXEMPTY_SHIFT              (31U)
/*! RXEMPTY - Receive Is Empty */
#define I3C_MDATACTRL_RXEMPTY(x)                 (((uint32_t)(((uint32_t)(x)) << I3C_MDATACTRL_RXEMPTY_SHIFT)) & I3C_MDATACTRL_RXEMPTY_MASK)
/*! @} */

/*! @name MWDATAB - Controller Write Data Byte Register */
/*! @{ */

#define I3C_MWDATAB_DATA_MASK                    (0xFFU)
#define I3C_MWDATAB_DATA_SHIFT                   (0U)
/*! DATA - Data byte */
#define I3C_MWDATAB_DATA(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAB_DATA_SHIFT)) & I3C_MWDATAB_DATA_MASK)

#define I3C_MWDATAB_END_MASK                     (0x100U)
#define I3C_MWDATAB_END_SHIFT                    (8U)
/*! END - End of message */
#define I3C_MWDATAB_END(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAB_END_SHIFT)) & I3C_MWDATAB_END_MASK)

#define I3C_MWDATAB_END_ALSO_MASK                (0x10000U)
#define I3C_MWDATAB_END_ALSO_SHIFT               (16U)
/*! END_ALSO - End of message also */
#define I3C_MWDATAB_END_ALSO(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAB_END_ALSO_SHIFT)) & I3C_MWDATAB_END_ALSO_MASK)
/*! @} */

/*! @name MWDATABE - Controller Write Data Byte End Register */
/*! @{ */

#define I3C_MWDATABE_VALUE_MASK                  (0xFFU)
#define I3C_MWDATABE_VALUE_SHIFT                 (0U)
/*! VALUE - Data */
#define I3C_MWDATABE_VALUE(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MWDATABE_VALUE_SHIFT)) & I3C_MWDATABE_VALUE_MASK)
/*! @} */

/*! @name MWDATAH - Controller Write Data Half-word Register */
/*! @{ */

#define I3C_MWDATAH_DATA0_MASK                   (0xFFU)
#define I3C_MWDATAH_DATA0_SHIFT                  (0U)
/*! DATA0 - Data byte 0 */
#define I3C_MWDATAH_DATA0(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAH_DATA0_SHIFT)) & I3C_MWDATAH_DATA0_MASK)

#define I3C_MWDATAH_DATA1_MASK                   (0xFF00U)
#define I3C_MWDATAH_DATA1_SHIFT                  (8U)
/*! DATA1 - Data byte 1 */
#define I3C_MWDATAH_DATA1(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAH_DATA1_SHIFT)) & I3C_MWDATAH_DATA1_MASK)

#define I3C_MWDATAH_END_MASK                     (0x10000U)
#define I3C_MWDATAH_END_SHIFT                    (16U)
/*! END - End of message */
#define I3C_MWDATAH_END(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAH_END_SHIFT)) & I3C_MWDATAH_END_MASK)
/*! @} */

/*! @name MWDATAHE - Controller Write Data Halfword End */
/*! @{ */

#define I3C_MWDATAHE_DATA0_MASK                  (0xFFU)
#define I3C_MWDATAHE_DATA0_SHIFT                 (0U)
/*! DATA0 - DATA 0 */
#define I3C_MWDATAHE_DATA0(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAHE_DATA0_SHIFT)) & I3C_MWDATAHE_DATA0_MASK)

#define I3C_MWDATAHE_DATA1_MASK                  (0xFF00U)
#define I3C_MWDATAHE_DATA1_SHIFT                 (8U)
/*! DATA1 - DATA 1 */
#define I3C_MWDATAHE_DATA1(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAHE_DATA1_SHIFT)) & I3C_MWDATAHE_DATA1_MASK)
/*! @} */

/*! @name MRDATAB - Controller Read Data Byte Register */
/*! @{ */

#define I3C_MRDATAB_VALUE_MASK                   (0xFFU)
#define I3C_MRDATAB_VALUE_SHIFT                  (0U)
/*! VALUE - VALUE */
#define I3C_MRDATAB_VALUE(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_MRDATAB_VALUE_SHIFT)) & I3C_MRDATAB_VALUE_MASK)
/*! @} */

/*! @name MRDATAH - Controller Read Data Half-word Register */
/*! @{ */

#define I3C_MRDATAH_LSB_MASK                     (0xFFU)
#define I3C_MRDATAH_LSB_SHIFT                    (0U)
/*! LSB - LSB */
#define I3C_MRDATAH_LSB(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_MRDATAH_LSB_SHIFT)) & I3C_MRDATAH_LSB_MASK)

#define I3C_MRDATAH_MSB_MASK                     (0xFF00U)
#define I3C_MRDATAH_MSB_SHIFT                    (8U)
/*! MSB - MSB */
#define I3C_MRDATAH_MSB(x)                       (((uint32_t)(((uint32_t)(x)) << I3C_MRDATAH_MSB_SHIFT)) & I3C_MRDATAH_MSB_MASK)
/*! @} */

/*! @name MWDATAB1 - Controller Write Byte Data 1 */
/*! @{ */

#define I3C_MWDATAB1_VALUE_MASK                  (0xFFU)
#define I3C_MWDATAB1_VALUE_SHIFT                 (0U)
/*! VALUE - VALUE */
#define I3C_MWDATAB1_VALUE(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MWDATAB1_VALUE_SHIFT)) & I3C_MWDATAB1_VALUE_MASK)
/*! @} */

/*! @name MWMSG_SDR_CONTROL - Controller Write Message in SDR mode */
/*! @{ */

#define I3C_MWMSG_SDR_CONTROL_DIR_MASK           (0x1U)
#define I3C_MWMSG_SDR_CONTROL_DIR_SHIFT          (0U)
/*! DIR - Direction
 *  0b0..Write
 *  0b1..Read
 */
#define I3C_MWMSG_SDR_CONTROL_DIR(x)             (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_CONTROL_DIR_SHIFT)) & I3C_MWMSG_SDR_CONTROL_DIR_MASK)

#define I3C_MWMSG_SDR_CONTROL_ADDR_MASK          (0xFEU)
#define I3C_MWMSG_SDR_CONTROL_ADDR_SHIFT         (1U)
/*! ADDR - Contains address to be written. */
#define I3C_MWMSG_SDR_CONTROL_ADDR(x)            (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_CONTROL_ADDR_SHIFT)) & I3C_MWMSG_SDR_CONTROL_ADDR_MASK)

#define I3C_MWMSG_SDR_CONTROL_END_MASK           (0x100U)
#define I3C_MWMSG_SDR_CONTROL_END_SHIFT          (8U)
/*! END - End of SDR message
 *  0b0..Not the end. SDR message ends waiting for a new SDR message (issues a repeated START for a new message).
 *  0b1..End. SDR message ends at the STOP.
 */
#define I3C_MWMSG_SDR_CONTROL_END(x)             (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_CONTROL_END_SHIFT)) & I3C_MWMSG_SDR_CONTROL_END_MASK)

#define I3C_MWMSG_SDR_CONTROL_I2C_MASK           (0x400U)
#define I3C_MWMSG_SDR_CONTROL_I2C_SHIFT          (10U)
/*! I2C - I2C
 *  0b0..I3C message
 *  0b1..I2C message
 */
#define I3C_MWMSG_SDR_CONTROL_I2C(x)             (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_CONTROL_I2C_SHIFT)) & I3C_MWMSG_SDR_CONTROL_I2C_MASK)

#define I3C_MWMSG_SDR_CONTROL_LEN_MASK           (0xF800U)
#define I3C_MWMSG_SDR_CONTROL_LEN_SHIFT          (11U)
/*! LEN - Length */
#define I3C_MWMSG_SDR_CONTROL_LEN(x)             (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_CONTROL_LEN_SHIFT)) & I3C_MWMSG_SDR_CONTROL_LEN_MASK)
/*! @} */

/*! @name MWMSG_SDR_DATA - Controller Write Message Data in SDR mode */
/*! @{ */

#define I3C_MWMSG_SDR_DATA_DATA16B_MASK          (0xFFFFU)
#define I3C_MWMSG_SDR_DATA_DATA16B_SHIFT         (0U)
/*! DATA16B - Data */
#define I3C_MWMSG_SDR_DATA_DATA16B(x)            (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_SDR_DATA_DATA16B_SHIFT)) & I3C_MWMSG_SDR_DATA_DATA16B_MASK)
/*! @} */

/*! @name MRMSG_SDR - Controller Read Message in SDR mode */
/*! @{ */

#define I3C_MRMSG_SDR_DATA_MASK                  (0xFFFFU)
#define I3C_MRMSG_SDR_DATA_SHIFT                 (0U)
/*! DATA - Data */
#define I3C_MRMSG_SDR_DATA(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MRMSG_SDR_DATA_SHIFT)) & I3C_MRMSG_SDR_DATA_MASK)
/*! @} */

/*! @name MWMSG_DDR_CONTROL - Controller Write Message in DDR mode: First Control Word */
/*! @{ */

#define I3C_MWMSG_DDR_CONTROL_ADDRCMD_MASK       (0xFFFFU)
#define I3C_MWMSG_DDR_CONTROL_ADDRCMD_SHIFT      (0U)
/*! ADDRCMD - Address Command */
#define I3C_MWMSG_DDR_CONTROL_ADDRCMD(x)         (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_DDR_CONTROL_ADDRCMD_SHIFT)) & I3C_MWMSG_DDR_CONTROL_ADDRCMD_MASK)
/*! @} */

/*! @name MWMSG_DDR_DATA - Controller Write Message Data in DDR mode */
/*! @{ */

#define I3C_MWMSG_DDR_DATA_DATA16B_MASK          (0xFFFFU)
#define I3C_MWMSG_DDR_DATA_DATA16B_SHIFT         (0U)
/*! DATA16B - Data */
#define I3C_MWMSG_DDR_DATA_DATA16B(x)            (((uint32_t)(((uint32_t)(x)) << I3C_MWMSG_DDR_DATA_DATA16B_SHIFT)) & I3C_MWMSG_DDR_DATA_DATA16B_MASK)
/*! @} */

/*! @name MRMSG_DDR - Controller Read Message in DDR mode */
/*! @{ */

#define I3C_MRMSG_DDR_DATA_MASK                  (0xFFFFU)
#define I3C_MRMSG_DDR_DATA_SHIFT                 (0U)
/*! DATA - Data */
#define I3C_MRMSG_DDR_DATA(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MRMSG_DDR_DATA_SHIFT)) & I3C_MRMSG_DDR_DATA_MASK)
/*! @} */

/*! @name MDYNADDR - Controller Dynamic Address */
/*! @{ */

#define I3C_MDYNADDR_DAVALID_MASK                (0x1U)
#define I3C_MDYNADDR_DAVALID_SHIFT               (0U)
/*! DAVALID - Dynamic address valid
 *  0b1..Valid DA assigned
 *  0b0..No valid DA assigned
 */
#define I3C_MDYNADDR_DAVALID(x)                  (((uint32_t)(((uint32_t)(x)) << I3C_MDYNADDR_DAVALID_SHIFT)) & I3C_MDYNADDR_DAVALID_MASK)

#define I3C_MDYNADDR_DADDR_MASK                  (0xFEU)
#define I3C_MDYNADDR_DADDR_SHIFT                 (1U)
/*! DADDR - Dynamic address */
#define I3C_MDYNADDR_DADDR(x)                    (((uint32_t)(((uint32_t)(x)) << I3C_MDYNADDR_DADDR_SHIFT)) & I3C_MDYNADDR_DADDR_MASK)
/*! @} */

/*! @name SMAPCTRL0 - Map Feature Control 0 */
/*! @{ */

#define I3C_SMAPCTRL0_ENA_MASK                   (0x1U)
#define I3C_SMAPCTRL0_ENA_SHIFT                  (0U)
/*! ENA - Enable Primary Dynamic Address
 *  0b0..Disable
 *  0b1..Enable
 */
#define I3C_SMAPCTRL0_ENA(x)                     (((uint32_t)(((uint32_t)(x)) << I3C_SMAPCTRL0_ENA_SHIFT)) & I3C_SMAPCTRL0_ENA_MASK)

#define I3C_SMAPCTRL0_DA_MASK                    (0xFEU)
#define I3C_SMAPCTRL0_DA_SHIFT                   (1U)
/*! DA - Dynamic Address */
#define I3C_SMAPCTRL0_DA(x)                      (((uint32_t)(((uint32_t)(x)) << I3C_SMAPCTRL0_DA_SHIFT)) & I3C_SMAPCTRL0_DA_MASK)

#define I3C_SMAPCTRL0_CAUSE_MASK                 (0x700U)
#define I3C_SMAPCTRL0_CAUSE_SHIFT                (8U)
/*! CAUSE - Cause
 *  0b000..No information. This value occurs when not configured to write DA.
 *  0b001..Set using ENTDAA
 *  0b010..Set using SETDASA, SETAASA, or SETNEWDA
 *  0b011..Cleared using RSTDAA
 *  0b100..Auto MAP change happened last. The change may have changed this DA as well (for example, ENTDAA, and
 *         SETAASA), but at least one MAP entry automatically changed after.
 */
#define I3C_SMAPCTRL0_CAUSE(x)                   (((uint32_t)(((uint32_t)(x)) << I3C_SMAPCTRL0_CAUSE_SHIFT)) & I3C_SMAPCTRL0_CAUSE_MASK)
/*! @} */

/*! @name SID - Slave Module ID Register */
/*! @{ */

#define I3C_SID_ID_MASK                          (0xFFFFFFFFU)
#define I3C_SID_ID_SHIFT                         (0U)
/*! ID - ID */
#define I3C_SID_ID(x)                            (((uint32_t)(((uint32_t)(x)) << I3C_SID_ID_SHIFT)) & I3C_SID_ID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I3C_Register_Masks */


/* I3C - Peripheral instance base addresses */
/** Peripheral I3C0 base address */
#define I3C0_BASE                                (0x40060000u)
/** Peripheral I3C0 base pointer */
#define I3C0                                     ((I3C_Type *)I3C0_BASE)
/** Array initializer of I3C peripheral base addresses */
#define I3C_BASE_ADDRS                           { I3C0_BASE }
/** Array initializer of I3C peripheral base pointers */
#define I3C_BASE_PTRS                            { I3C0 }
/** Interrupt vectors for the I3C peripheral type */
#define I3C_IRQS                                 { I3C0_IRQn }

/*!
 * @}
 */ /* end of group I3C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- INPUTMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Peripheral_Access_Layer INPUTMUX Peripheral Access Layer
 * @{
 */

/** INPUTMUX - Register Layout Typedef */
typedef struct {
  __IO uint32_t DMA_INMUX_INMUX[2];                /**< DMA output trigger selection to become DMA trigger, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[24];
  __IO uint32_t FTM0_INMUX[3];                     /**< input select register for FTM0, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[20];
  __IO uint32_t DMA_ITRIG_INMUX[16];               /**< Trigger select register for DMA channel, array offset: 0x40, array step: 0x4 */
       uint8_t RESERVED_2[32];
  __IO uint32_t FTM1_INMUX[3];                     /**< input select register for FTM1 input, array offset: 0xA0, array step: 0x4 */
       uint8_t RESERVED_3[20];
  __IO uint32_t FTM0_FLT_INMUX[4];                 /**< input select register for FTM0 FAULT, array offset: 0xC0, array step: 0x4 */
} INPUTMUX_Type;

/* ----------------------------------------------------------------------------
   -- INPUTMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INPUTMUX_Register_Masks INPUTMUX Register Masks
 * @{
 */

/*! @name DMA_INMUX_INMUX - DMA output trigger selection to become DMA trigger */
/*! @{ */

#define INPUTMUX_DMA_INMUX_INMUX_INP_MASK        (0x1FU)
#define INPUTMUX_DMA_INMUX_INMUX_INP_SHIFT       (0U)
/*! INP - DMA trigger output number (decimal value) for DMA channel n (n = 0 to 15). */
#define INPUTMUX_DMA_INMUX_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_INMUX_INMUX_INP_SHIFT)) & INPUTMUX_DMA_INMUX_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_DMA_INMUX_INMUX */
#define INPUTMUX_DMA_INMUX_INMUX_COUNT           (2U)

/*! @name FTM0_INMUX - input select register for FTM0 */
/*! @{ */

#define INPUTMUX_FTM0_INMUX_INP_MASK             (0xFU)
#define INPUTMUX_FTM0_INMUX_INP_SHIFT            (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 12). 0 = GPIO_INT4; 1 =
 *    GPIO_INT5; 2 = GPIO_INT6; 3 = GPIO_INT7; 4= ADC0_SEQA_IRQ; 5 = ADC0_SEQB_IRQ; 6 = COMP0_OUT; 7
 *    = FTM0_INIT_TRIG ORed with FTM0_EXT_TRIG; 8 = FTM1_INIT_TRIG ORed with FTM1_EXT_TRIG; 9= Ored
 *    (FTM0_CH0, FTM0_CH1,.., FTM0_CH5); 10 = Ored (FTM1_CH0, FTM1_CH1,.., FTM1_CH3); 11 =
 *    SDMA_TRIGOUT_A; 12 = SDMA_TRIGOUT_B.
 */
#define INPUTMUX_FTM0_INMUX_INP(x)               (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FTM0_INMUX_INP_SHIFT)) & INPUTMUX_FTM0_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_FTM0_INMUX */
#define INPUTMUX_FTM0_INMUX_COUNT                (3U)

/*! @name DMA_ITRIG_INMUX - Trigger select register for DMA channel */
/*! @{ */

#define INPUTMUX_DMA_ITRIG_INMUX_INP_MASK        (0xFU)
#define INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT       (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 12). 0 = GPIO_INT4; 1 =
 *    GPIO_INT5; 2 = GPIO_INT6; 3 = GPIO_INT7; 4= ADC0_SEQA_IRQ; 5 = ADC0_SEQB_IRQ; 6 = COMP0_OUT; 7
 *    = FTM0_INIT_TRIG ORed with FTM0_EXT_TRIG; 8 = FTM1_INIT_TRIG ORed with FTM1_EXT_TRIG; 9= Ored
 *    (FTM0_CH0, FTM0_CH1,.., FTM0_CH5); 10 = Ored (FTM1_CH0, FTM1_CH1,.., FTM1_CH3); 11 = DMA
 *    trigger mux 0 (DMA_INMUX_INMUX0); 12 = DMA trigger mux 1(DMA_INMUX_INMUX1).
 */
#define INPUTMUX_DMA_ITRIG_INMUX_INP(x)          (((uint32_t)(((uint32_t)(x)) << INPUTMUX_DMA_ITRIG_INMUX_INP_SHIFT)) & INPUTMUX_DMA_ITRIG_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_DMA_ITRIG_INMUX */
#define INPUTMUX_DMA_ITRIG_INMUX_COUNT           (16U)

/*! @name FTM1_INMUX - input select register for FTM1 input */
/*! @{ */

#define INPUTMUX_FTM1_INMUX_INP_MASK             (0xFU)
#define INPUTMUX_FTM1_INMUX_INP_SHIFT            (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 12). 0 = GPIO_INT4; 1 =
 *    GPIO_INT5; 2 = GPIO_INT6; 3 = GPIO_INT7; 4= ADC0_SEQA_IRQ; 5 = ADC0_SEQB_IRQ; 6 = COMP0_OUT; 7
 *    = FTM0_INIT_TRIG ORed with FTM0_EXT_TRIG; 8 = FTM1_INIT_TRIG ORed with FTM1_EXT_TRIG; 9= Ored
 *    (FTM0_CH0, FTM0_CH1,.., FTM0_CH5); 10 = Ored (FTM1_CH0, FTM1_CH1,.., FTM1_CH3); 11 =
 *    SDMA_TRIGOUT_A; 12 = SDMA_TRIGOUT_B.
 */
#define INPUTMUX_FTM1_INMUX_INP(x)               (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FTM1_INMUX_INP_SHIFT)) & INPUTMUX_FTM1_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_FTM1_INMUX */
#define INPUTMUX_FTM1_INMUX_COUNT                (3U)

/*! @name FTM0_FLT_INMUX - input select register for FTM0 FAULT */
/*! @{ */

#define INPUTMUX_FTM0_FLT_INMUX_INP_MASK         (0xFU)
#define INPUTMUX_FTM0_FLT_INMUX_INP_SHIFT        (0U)
/*! INP - Trigger input number (decimal value) for DMA channel n (n = 0 to 12). 0 = GPIO_INT4; 1 =
 *    GPIO_INT5; 2 = GPIO_INT6; 3 = GPIO_INT7; 4= ADC0_SEQA_IRQ; 5 = ADC0_SEQB_IRQ; 6 = COMP0_OUT; 7
 *    = FTM0_INIT_TRIG ORed with FTM0_EXT_TRIG; 8 = FTM1_INIT_TRIG ORed with FTM1_EXT_TRIG; 9= Ored
 *    (FTM0_CH0, FTM0_CH1,.., FTM0_CH5); 10 = Ored (FTM1_CH0, FTM1_CH1,.., FTM1_CH3); 11 =
 *    SDMA_TRIGOUT_A; 12 = SDMA_TRIGOUT_B.
 */
#define INPUTMUX_FTM0_FLT_INMUX_INP(x)           (((uint32_t)(((uint32_t)(x)) << INPUTMUX_FTM0_FLT_INMUX_INP_SHIFT)) & INPUTMUX_FTM0_FLT_INMUX_INP_MASK)
/*! @} */

/* The count of INPUTMUX_FTM0_FLT_INMUX */
#define INPUTMUX_FTM0_FLT_INMUX_COUNT            (4U)


/*!
 * @}
 */ /* end of group INPUTMUX_Register_Masks */


/* INPUTMUX - Peripheral instance base addresses */
/** Peripheral INPUTMUX base address */
#define INPUTMUX_BASE                            (0x4002C000u)
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
  __IO uint32_t PIO[56];                           /**< Digital I/O control for pins PIO0_17..Digital I/O control for pins PIO1_10, array offset: 0x0, array step: 0x4, valid indices: [0-11, 13-18, 20-55] */
} IOCON_Type;

/* ----------------------------------------------------------------------------
   -- IOCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Register_Masks IOCON Register Masks
 * @{
 */

/*! @name PIO - Digital I/O control for pins PIO0_17..Digital I/O control for pins PIO1_10 */
/*! @{ */

#define IOCON_PIO_MODE_MASK                      (0x18U)
#define IOCON_PIO_MODE_SHIFT                     (3U)
/*! MODE - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)

#define IOCON_PIO_HYS_MASK                       (0x20U)
#define IOCON_PIO_HYS_SHIFT                      (5U)
/*! HYS - Hysteresis.
 *  0b0..Disable
 *  0b1..Enable
 */
#define IOCON_PIO_HYS(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_HYS_SHIFT)) & IOCON_PIO_HYS_MASK)

#define IOCON_PIO_INV_MASK                       (0x40U)
#define IOCON_PIO_INV_SHIFT                      (6U)
/*! INV - Invert input
 *  0b0..Input not inverted (HIGH on pin reads as 1; LOW on pin reads as 0).
 *  0b1..Input inverted (HIGH on pin reads as 0, LOW on pin reads as 1).
 */
#define IOCON_PIO_INV(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_INV_SHIFT)) & IOCON_PIO_INV_MASK)

#define IOCON_PIO_I2CMODE_MASK                   (0x300U)
#define IOCON_PIO_I2CMODE_SHIFT                  (8U)
/*! I2CMODE - Selects I2C mode.
 *  0b00..Standard mode/ Fast-mode I2C.
 *  0b01..Standard GPIO functionality. Requires external pull-up for GPIO output function.
 *  0b10..Fast-mode Plus I2C
 *  0b11..Reserved
 */
#define IOCON_PIO_I2CMODE(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CMODE_SHIFT)) & IOCON_PIO_I2CMODE_MASK)

#define IOCON_PIO_OD_MASK                        (0x400U)
#define IOCON_PIO_OD_SHIFT                       (10U)
/*! OD - Open-drain mode.
 *  0b0..Disable.
 *  0b1..Open-drain mode enabled. Remark: This is not a true open-drain mode.
 */
#define IOCON_PIO_OD(x)                          (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)

#define IOCON_PIO_S_MODE_MASK                    (0x1800U)
#define IOCON_PIO_S_MODE_SHIFT                   (11U)
/*! S_MODE - Digital filter sample mode.
 *  0b00..Bypass input filter.
 *  0b01..1 clock cycle. Input pulses shorter than one filter clock are rejected.
 *  0b10..2 clock cycles. Input pulses shorter than two filter clocks are rejected.
 *  0b11..3 clock cycles. Input pulses shorter than three filter clocks are rejected.
 */
#define IOCON_PIO_S_MODE(x)                      (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_S_MODE_SHIFT)) & IOCON_PIO_S_MODE_MASK)

#define IOCON_PIO_CLK_DIV_MASK                   (0xE000U)
#define IOCON_PIO_CLK_DIV_SHIFT                  (13U)
/*! CLK_DIV - Select peripheral clock divider for input filter sampling clock. Value 0x7 is reserved.
 *  0b000..IOCONCLKDIV0
 *  0b001..IOCONCLKDIV1
 *  0b010..IOCONCLKDIV2
 *  0b011..IOCONCLKDIV3
 *  0b100..IOCONCLKDIV4
 *  0b101..IOCONCLKDIV5
 *  0b110..IOCONCLKDIV6
 */
#define IOCON_PIO_CLK_DIV(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_CLK_DIV_SHIFT)) & IOCON_PIO_CLK_DIV_MASK)
/*! @} */

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT                          (56U)


/*!
 * @}
 */ /* end of group IOCON_Register_Masks */


/* IOCON - Peripheral instance base addresses */
/** Peripheral IOCON base address */
#define IOCON_BASE                               (0x40044000u)
/** Peripheral IOCON base pointer */
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)
/** Array initializer of IOCON peripheral base addresses */
#define IOCON_BASE_ADDRS                         { IOCON_BASE }
/** Array initializer of IOCON peripheral base pointers */
#define IOCON_BASE_PTRS                          { IOCON }

#define    IOCON_INDEX_PIO0_17       ( 0)
#define    IOCON_INDEX_PIO0_13       ( 1)
#define    IOCON_INDEX_PIO0_12       ( 2)
#define    IOCON_INDEX_PIO0_5        ( 3)
#define    IOCON_INDEX_PIO0_4        ( 4)
#define    IOCON_INDEX_PIO0_3        ( 5)
#define    IOCON_INDEX_PIO0_2        ( 6)
#define    IOCON_INDEX_PIO0_11       ( 7)
#define    IOCON_INDEX_PIO0_10       ( 8)
#define    IOCON_INDEX_PIO0_16       ( 9)
#define    IOCON_INDEX_PIO0_15       (10)
#define    IOCON_INDEX_PIO0_1        (11)
#define    IOCON_INDEX_PIO0_9        (13)
#define    IOCON_INDEX_PIO0_8        (14)
#define    IOCON_INDEX_PIO0_7        (15)
#define    IOCON_INDEX_PIO0_6        (16)
#define    IOCON_INDEX_PIO0_0        (17)
#define    IOCON_INDEX_PIO0_14       (18)
#define    IOCON_INDEX_PIO0_28       (20)
#define    IOCON_INDEX_PIO0_27       (21)
#define    IOCON_INDEX_PIO0_26       (22)
#define    IOCON_INDEX_PIO0_25       (23)
#define    IOCON_INDEX_PIO0_24       (24)
#define    IOCON_INDEX_PIO0_23       (25)
#define    IOCON_INDEX_PIO0_22       (26)
#define    IOCON_INDEX_PIO0_21       (27)
#define    IOCON_INDEX_PIO0_20       (28)
#define    IOCON_INDEX_PIO0_19       (29)
#define    IOCON_INDEX_PIO0_18       (30)
#define    IOCON_INDEX_PIO1_8        (31)
#define    IOCON_INDEX_PIO1_9        (32)
#define    IOCON_INDEX_PIO1_12       (33)
#define    IOCON_INDEX_PIO1_13       (34)
#define    IOCON_INDEX_PIO0_31       (35)
#define    IOCON_INDEX_PIO1_0        (36)
#define    IOCON_INDEX_PIO1_1        (37)
#define    IOCON_INDEX_PIO1_2        (38)
#define    IOCON_INDEX_PIO1_14       (39)
#define    IOCON_INDEX_PIO1_15       (40)
#define    IOCON_INDEX_PIO1_3        (41)
#define    IOCON_INDEX_PIO1_4        (42)
#define    IOCON_INDEX_PIO1_5        (43)
#define    IOCON_INDEX_PIO1_16       (44)
#define    IOCON_INDEX_PIO1_17       (45)
#define    IOCON_INDEX_PIO1_6        (46)
#define    IOCON_INDEX_PIO1_18       (47)
#define    IOCON_INDEX_PIO1_19       (48)
#define    IOCON_INDEX_PIO1_7        (49)
#define    IOCON_INDEX_PIO0_29       (50)
#define    IOCON_INDEX_PIO0_30       (51)
#define    IOCON_INDEX_PIO1_20       (52)
#define    IOCON_INDEX_PIO1_21       (53)
#define    IOCON_INDEX_PIO1_11       (54)
#define    IOCON_INDEX_PIO1_10       (55)


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
       uint8_t RESERVED_0[180];
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

#define MRT_CHANNEL_INTVAL_IVALUE_MASK           (0x7FFFFFFFU)
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

#define MRT_CHANNEL_TIMER_VALUE_MASK             (0x7FFFFFFFU)
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
/*! @} */

/* The count of MRT_CHANNEL_STAT */
#define MRT_CHANNEL_STAT_COUNT                   (4U)

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
/*! GFLAG1 - Monitors the interrupt flag of TIMER1. See description of channel 0. */
#define MRT_IRQ_FLAG_GFLAG1(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG1_SHIFT)) & MRT_IRQ_FLAG_GFLAG1_MASK)

#define MRT_IRQ_FLAG_GFLAG2_MASK                 (0x4U)
#define MRT_IRQ_FLAG_GFLAG2_SHIFT                (2U)
/*! GFLAG2 - Monitors the interrupt flag of TIMER2. See description of channel 0. */
#define MRT_IRQ_FLAG_GFLAG2(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG2_SHIFT)) & MRT_IRQ_FLAG_GFLAG2_MASK)

#define MRT_IRQ_FLAG_GFLAG3_MASK                 (0x8U)
#define MRT_IRQ_FLAG_GFLAG3_SHIFT                (3U)
/*! GFLAG3 - Monitors the interrupt flag of TIMER3. See description of channel 0. */
#define MRT_IRQ_FLAG_GFLAG3(x)                   (((uint32_t)(((uint32_t)(x)) << MRT_IRQ_FLAG_GFLAG3_SHIFT)) & MRT_IRQ_FLAG_GFLAG3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MRT_Register_Masks */


/* MRT - Peripheral instance base addresses */
/** Peripheral MRT0 base address */
#define MRT0_BASE                                (0x40004000u)
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
#define PINT_BASE                                (0xA0004000u)
/** Peripheral PINT base pointer */
#define PINT                                     ((PINT_Type *)PINT_BASE)
/** Array initializer of PINT peripheral base addresses */
#define PINT_BASE_ADDRS                          { PINT_BASE }
/** Array initializer of PINT peripheral base pointers */
#define PINT_BASE_PTRS                           { PINT }
/** Interrupt vectors for the PINT peripheral type */
#define PINT_IRQS                                { PIN_INT0_IRQn, PIN_INT1_IRQn, PIN_INT2_IRQn, PIN_INT3_IRQn, PIN_INT4_IRQn, PIN_INT5_IRQn, PIN_INT6_IRQn, PIN_INT7_IRQn }

/*!
 * @}
 */ /* end of group PINT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PMU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMU_Peripheral_Access_Layer PMU Peripheral Access Layer
 * @{
 */

/** PMU - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCON;                              /**< Power control register, offset: 0x0 */
  __IO uint32_t GPREG[4];                          /**< General purpose register N, array offset: 0x4, array step: 0x4 */
  __IO uint32_t DPDCTRL;                           /**< Deep power-down control register. Also includes bits for general purpose storage., offset: 0x14 */
} PMU_Type;

/* ----------------------------------------------------------------------------
   -- PMU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMU_Register_Masks PMU Register Masks
 * @{
 */

/*! @name PCON - Power control register */
/*! @{ */

#define PMU_PCON_PM_MASK                         (0x7U)
#define PMU_PCON_PM_SHIFT                        (0U)
/*! PM - Power mode
 *  0b000..Default. The part is in active or sleep mode.
 *  0b001..Deep-sleep mode. ARM WFI will enter Deep-sleep mode.
 *  0b010..Power-down mode. ARM WFI will enter Power-down mode.
 *  0b011..Deep power-down mode. ARM WFI will enter Deep-power down mode (ARM Cortex-M0+ core powered-down).
 */
#define PMU_PCON_PM(x)                           (((uint32_t)(((uint32_t)(x)) << PMU_PCON_PM_SHIFT)) & PMU_PCON_PM_MASK)

#define PMU_PCON_NODPD_MASK                      (0x8U)
#define PMU_PCON_NODPD_SHIFT                     (3U)
/*! NODPD - A 1 in this bit prevents entry to Deep power-down mode when 0x3 is written to the PM
 *    field above, the SLEEPDEEP bit is set, and a WFI is executed. This bit is cleared only by
 *    power-on reset, so writing a one to this bit locks the part in a mode in which Deep power-down mode
 *    is blocked.
 */
#define PMU_PCON_NODPD(x)                        (((uint32_t)(((uint32_t)(x)) << PMU_PCON_NODPD_SHIFT)) & PMU_PCON_NODPD_MASK)

#define PMU_PCON_SLEEPFLAG_MASK                  (0x100U)
#define PMU_PCON_SLEEPFLAG_SHIFT                 (8U)
/*! SLEEPFLAG - Sleep mode flag
 *  0b0..Active mode. Read: No power-down mode entered. Part is in Active mode. Write: No effect.
 *  0b1..Low power mode. Read: Sleep, Deep-sleep or Power-down mode entered. Write: Writing a 1 clears the SLEEPFLAG bit to 0.
 */
#define PMU_PCON_SLEEPFLAG(x)                    (((uint32_t)(((uint32_t)(x)) << PMU_PCON_SLEEPFLAG_SHIFT)) & PMU_PCON_SLEEPFLAG_MASK)

#define PMU_PCON_DPDFLAG_MASK                    (0x800U)
#define PMU_PCON_DPDFLAG_SHIFT                   (11U)
/*! DPDFLAG - Deep power-down flag
 *  0b0..Not Deep power-down. Read: Deep power-down mode not entered. Write: No effect.
 *  0b1..Deep power-down. Read: Deep power-down mode entered. Write: Clear the Deep power-down flag.
 */
#define PMU_PCON_DPDFLAG(x)                      (((uint32_t)(((uint32_t)(x)) << PMU_PCON_DPDFLAG_SHIFT)) & PMU_PCON_DPDFLAG_MASK)
/*! @} */

/*! @name GPREG - General purpose register N */
/*! @{ */

#define PMU_GPREG_GPDATA_MASK                    (0xFFFFFFFFU)
#define PMU_GPREG_GPDATA_SHIFT                   (0U)
/*! GPDATA - Data retained during Deep power-down mode. */
#define PMU_GPREG_GPDATA(x)                      (((uint32_t)(((uint32_t)(x)) << PMU_GPREG_GPDATA_SHIFT)) & PMU_GPREG_GPDATA_MASK)
/*! @} */

/* The count of PMU_GPREG */
#define PMU_GPREG_COUNT                          (4U)

/*! @name DPDCTRL - Deep power-down control register. Also includes bits for general purpose storage. */
/*! @{ */

#define PMU_DPDCTRL_WAKEUPHYS_MASK               (0x1U)
#define PMU_DPDCTRL_WAKEUPHYS_SHIFT              (0U)
/*! WAKEUPHYS - WAKEUP pin hysteresis enable
 *  0b0..Disabled. Hysteresis for WAKEUP pin disabled.
 *  0b1..Enabled. Hysteresis for WAKEUP pin enabled.
 */
#define PMU_DPDCTRL_WAKEUPHYS(x)                 (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_WAKEUPHYS_SHIFT)) & PMU_DPDCTRL_WAKEUPHYS_MASK)

#define PMU_DPDCTRL_WAKEPAD_DISABLE_MASK         (0x2U)
#define PMU_DPDCTRL_WAKEPAD_DISABLE_SHIFT        (1U)
/*! WAKEPAD_DISABLE - WAKEUP pin disable. Setting this bit disables the wake-up pin, so it can be
 *    used for other purposes. Remark: Never set this bit if you intend to use a pin to wake up the
 *    part from Deep power-down mode. You can only disable the wake-up pin if the self wake-up timer
 *    is enabled and configured. Remark: Setting this bit is not necessary if Deep power-down mode is
 *    not used.
 *  0b0..Enabled. The wake-up function is enabled on pin PIO0_4.
 *  0b1..Disabled. Setting this bit disables the wake-up function on pin PIO0_4.
 */
#define PMU_DPDCTRL_WAKEPAD_DISABLE(x)           (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_WAKEPAD_DISABLE_SHIFT)) & PMU_DPDCTRL_WAKEPAD_DISABLE_MASK)

#define PMU_DPDCTRL_ULPOSCEN_MASK                (0x4U)
#define PMU_DPDCTRL_ULPOSCEN_SHIFT               (2U)
/*! ULPOSCEN - Enable the low-power oscillator for use with the 10 kHz self wake-up timer clock. You
 *    must set this bit if the CLKSEL bit in the self wake-up timer CTRL bit is set. Do not enable
 *    the low-power oscillator if the self wake-up timer is clocked by the divided IRC or the
 *    external clock input.
 *  0b0..Disabled.
 *  0b1..Enabled.
 */
#define PMU_DPDCTRL_ULPOSCEN(x)                  (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_ULPOSCEN_SHIFT)) & PMU_DPDCTRL_ULPOSCEN_MASK)

#define PMU_DPDCTRL_ULPOSCDPDEN_MASK             (0x8U)
#define PMU_DPDCTRL_ULPOSCDPDEN_SHIFT            (3U)
/*! ULPOSCDPDEN - causes the low-power oscillator to remain running during Deep power-down mode
 *    provided that bit 2 in this register is set as well. You must set this bit for the self wake-up
 *    timer to be able to wake up the part from Deep power-down mode. Remark: Do not set this bit
 *    unless you use the self wake-up timer with the low-power oscillator clock source to wake up from
 *    Deep power-down mode.
 *  0b0..Disabled.
 *  0b1..Enabled.
 */
#define PMU_DPDCTRL_ULPOSCDPDEN(x)               (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_ULPOSCDPDEN_SHIFT)) & PMU_DPDCTRL_ULPOSCDPDEN_MASK)

#define PMU_DPDCTRL_WAKEUPCLKHYS_MASK            (0x10U)
#define PMU_DPDCTRL_WAKEUPCLKHYS_SHIFT           (4U)
/*! WAKEUPCLKHYS - External clock input for the self wake-up timer WKTCLKIN hysteresis enable.
 *  0b0..Disabled. Hysteresis for WAKEUP clock pin disabled.
 *  0b1..Enabled. Hysteresis for WAKEUP clock pin enabled.
 */
#define PMU_DPDCTRL_WAKEUPCLKHYS(x)              (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_WAKEUPCLKHYS_SHIFT)) & PMU_DPDCTRL_WAKEUPCLKHYS_MASK)

#define PMU_DPDCTRL_WAKECLKPAD_DISABLE_MASK      (0x20U)
#define PMU_DPDCTRL_WAKECLKPAD_DISABLE_SHIFT     (5U)
/*! WAKECLKPAD_DISABLE - Disable the external clock input for the self-wake-up timer. Setting this
 *    bit enables the self-wake-up timer clock pin WKTCLKLIN. To minimize power consumption,
 *    especially in deep power-down mode, disable this clock input when not using the external clock option
 *    for the self-wake-up timer.
 *  0b0..Disabled. Setting this bit disables external clock input on pin PIO0_28.
 *  0b1..Enabled. The external clock input for the self wake-up timer is enabled on pin PIO0_28.
 */
#define PMU_DPDCTRL_WAKECLKPAD_DISABLE(x)        (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_WAKECLKPAD_DISABLE_SHIFT)) & PMU_DPDCTRL_WAKECLKPAD_DISABLE_MASK)

#define PMU_DPDCTRL_RESETHYS_MASK                (0x40U)
#define PMU_DPDCTRL_RESETHYS_SHIFT               (6U)
/*! RESETHYS - RESET pin hysteresis enable.
 *  0b0..Disabled. Hysteresis for RESET pin disabled.
 *  0b1..Enabled. Hysteresis for RESET pin enabled.
 */
#define PMU_DPDCTRL_RESETHYS(x)                  (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_RESETHYS_SHIFT)) & PMU_DPDCTRL_RESETHYS_MASK)

#define PMU_DPDCTRL_RESET_DISABLE_MASK           (0x80U)
#define PMU_DPDCTRL_RESET_DISABLE_SHIFT          (7U)
/*! RESET_DISABLE - RESET pin disable. Setting this bit disables the reset wake-up function, so the
 *    pin can be used for other purposes. Remark: Setting this bit is not necessary if deep
 *    power-down mode is not used.
 *  0b0..Enabled. The reset wake-up function is enabled on pin PIO0_5.
 *  0b1..Disabled. Setting this bit disables the wake-up function on pin PIO0_5.
 */
#define PMU_DPDCTRL_RESET_DISABLE(x)             (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_RESET_DISABLE_SHIFT)) & PMU_DPDCTRL_RESET_DISABLE_MASK)

#define PMU_DPDCTRL_GPDATA_MASK                  (0xFFFFFF00U)
#define PMU_DPDCTRL_GPDATA_SHIFT                 (8U)
/*! GPDATA - Data retained during Deep power-down mode. */
#define PMU_DPDCTRL_GPDATA(x)                    (((uint32_t)(((uint32_t)(x)) << PMU_DPDCTRL_GPDATA_SHIFT)) & PMU_DPDCTRL_GPDATA_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PMU_Register_Masks */


/* PMU - Peripheral instance base addresses */
/** Peripheral PMU base address */
#define PMU_BASE                                 (0x40020000u)
/** Peripheral PMU base pointer */
#define PMU                                      ((PMU_Type *)PMU_BASE)
/** Array initializer of PMU peripheral base addresses */
#define PMU_BASE_ADDRS                           { PMU_BASE }
/** Array initializer of PMU peripheral base pointers */
#define PMU_BASE_PTRS                            { PMU }

/*!
 * @}
 */ /* end of group PMU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFG;                               /**< SPI Configuration register, offset: 0x0 */
  __IO uint32_t DLY;                               /**< SPI Delay register, offset: 0x4 */
  __IO uint32_t STAT;                              /**< SPI Status. Some status flags can be cleared by writing a 1 to that bit position, offset: 0x8 */
  __IO uint32_t INTENSET;                          /**< SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __O  uint32_t INTENCLR;                          /**< SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared., offset: 0x10 */
  __I  uint32_t RXDAT;                             /**< SPI Receive Data, offset: 0x14 */
  __IO uint32_t TXDATCTL;                          /**< SPI Transmit Data with Control, offset: 0x18 */
  __IO uint32_t TXDAT;                             /**< SPI Transmit Data., offset: 0x1C */
  __IO uint32_t TXCTL;                             /**< SPI Transmit Control, offset: 0x20 */
  __IO uint32_t DIV;                               /**< SPI clock Divider, offset: 0x24 */
  __I  uint32_t INTSTAT;                           /**< SPI Interrupt Status, offset: 0x28 */
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

/*! @name STAT - SPI Status. Some status flags can be cleared by writing a 1 to that bit position */
/*! @{ */

#define SPI_STAT_RXRDY_MASK                      (0x1U)
#define SPI_STAT_RXRDY_SHIFT                     (0U)
/*! RXRDY - Receiver Ready flag. When 1, indicates that data is available to be read from the
 *    receiver buffer. Cleared after a read of the RXDAT register.
 */
#define SPI_STAT_RXRDY(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_STAT_RXRDY_SHIFT)) & SPI_STAT_RXRDY_MASK)

#define SPI_STAT_TXRDY_MASK                      (0x2U)
#define SPI_STAT_TXRDY_SHIFT                     (1U)
/*! TXRDY - Transmitter Ready flag. When 1, this bit indicates that data may be written to the
 *    transmit buffer. Previous data may still be in the process of being transmitted. Cleared when data
 *    is written to TXDAT or TXDATCTL until the data is moved to the transmit shift register.
 */
#define SPI_STAT_TXRDY(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_STAT_TXRDY_SHIFT)) & SPI_STAT_TXRDY_MASK)

#define SPI_STAT_RXOV_MASK                       (0x4U)
#define SPI_STAT_RXOV_SHIFT                      (2U)
/*! RXOV - Receiver Overrun interrupt flag. This flag applies only to slave mode (Master = 0). This
 *    flag is set when the beginning of a received character is detected while the receiver buffer
 *    is still in use. If this occurs, the receiver buffer contents are preserved, and the incoming
 *    data is lost. Data received by the SPI should be considered undefined if RxOv is set.
 */
#define SPI_STAT_RXOV(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_STAT_RXOV_SHIFT)) & SPI_STAT_RXOV_MASK)

#define SPI_STAT_TXUR_MASK                       (0x8U)
#define SPI_STAT_TXUR_SHIFT                      (3U)
/*! TXUR - Transmitter Underrun interrupt flag. This flag applies only to slave mode (Master = 0).
 *    In this case, the transmitter must begin sending new data on the next input clock if the
 *    transmitter is idle. If that data is not available in the transmitter holding register at that
 *    point, there is no data to transmit and the TXUR flag is set. Data transmitted by the SPI should be
 *    considered undefined if TXUR is set.
 */
#define SPI_STAT_TXUR(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_STAT_TXUR_SHIFT)) & SPI_STAT_TXUR_MASK)

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
/*! STALLED - Stalled status flag. This indicates whether the SPI is currently in a stall condition. */
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

#define SPI_INTENSET_RXRDYEN_MASK                (0x1U)
#define SPI_INTENSET_RXRDYEN_SHIFT               (0U)
/*! RXRDYEN - Determines whether an interrupt occurs when receiver data is available.
 *  0b0..No interrupt will be generated when receiver data is available.
 *  0b1..An interrupt will be generated when receiver data is available in the RXDAT register.
 */
#define SPI_INTENSET_RXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_RXRDYEN_SHIFT)) & SPI_INTENSET_RXRDYEN_MASK)

#define SPI_INTENSET_TXRDYEN_MASK                (0x2U)
#define SPI_INTENSET_TXRDYEN_SHIFT               (1U)
/*! TXRDYEN - Determines whether an interrupt occurs when the transmitter holding register is available.
 *  0b0..No interrupt will be generated when the transmitter holding register is available.
 *  0b1..An interrupt will be generated when data may be written to TXDAT.
 */
#define SPI_INTENSET_TXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_TXRDYEN_SHIFT)) & SPI_INTENSET_TXRDYEN_MASK)

#define SPI_INTENSET_RXOVEN_MASK                 (0x4U)
#define SPI_INTENSET_RXOVEN_SHIFT                (2U)
/*! RXOVEN - Determines whether an interrupt occurs when a receiver overrun occurs. This happens in
 *    slave mode when there is a need for the receiver to move newly received data to the RXDAT
 *    register when it is already in use. The interface prevents receiver overrun in Master mode by not
 *    allowing a new transmission to begin when a receiver overrun would otherwise occur.
 *  0b0..No interrupt will be generated when a receiver overrun occurs.
 *  0b1..An interrupt will be generated if a receiver overrun occurs.
 */
#define SPI_INTENSET_RXOVEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_RXOVEN_SHIFT)) & SPI_INTENSET_RXOVEN_MASK)

#define SPI_INTENSET_TXUREN_MASK                 (0x8U)
#define SPI_INTENSET_TXUREN_SHIFT                (3U)
/*! TXUREN - Determines whether an interrupt occurs when a transmitter underrun occurs. This happens
 *    in slave mode when there is a need to transmit data when none is available.
 *  0b0..No interrupt will be generated when the transmitter underruns.
 *  0b1..An interrupt will be generated if the transmitter underruns.
 */
#define SPI_INTENSET_TXUREN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_TXUREN_SHIFT)) & SPI_INTENSET_TXUREN_MASK)

#define SPI_INTENSET_SSAEN_MASK                  (0x10U)
#define SPI_INTENSET_SSAEN_SHIFT                 (4U)
/*! SSAEN - Determines whether an interrupt occurs when the Slave Select is asserted.
 *  0b0..No interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 *  0b1..An interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 */
#define SPI_INTENSET_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSAEN_SHIFT)) & SPI_INTENSET_SSAEN_MASK)

#define SPI_INTENSET_SSDEN_MASK                  (0x20U)
#define SPI_INTENSET_SSDEN_SHIFT                 (5U)
/*! SSDEN - Determines whether an interrupt occurs when the Slave Select is deasserted.
 *  0b0..No interrupt will be generated when all asserted Slave Selects transition to deasserted.
 *  0b1..An interrupt will be generated when all asserted Slave Selects transition to deasserted.
 */
#define SPI_INTENSET_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSDEN_SHIFT)) & SPI_INTENSET_SSDEN_MASK)
/*! @} */

/*! @name INTENCLR - SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared. */
/*! @{ */

#define SPI_INTENCLR_RXRDYEN_MASK                (0x1U)
#define SPI_INTENCLR_RXRDYEN_SHIFT               (0U)
/*! RXRDYEN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_RXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_RXRDYEN_SHIFT)) & SPI_INTENCLR_RXRDYEN_MASK)

#define SPI_INTENCLR_TXRDYEN_MASK                (0x2U)
#define SPI_INTENCLR_TXRDYEN_SHIFT               (1U)
/*! TXRDYEN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_TXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_TXRDYEN_SHIFT)) & SPI_INTENCLR_TXRDYEN_MASK)

#define SPI_INTENCLR_RXOVEN_MASK                 (0x4U)
#define SPI_INTENCLR_RXOVEN_SHIFT                (2U)
/*! RXOVEN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_RXOVEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_RXOVEN_SHIFT)) & SPI_INTENCLR_RXOVEN_MASK)

#define SPI_INTENCLR_TXUREN_MASK                 (0x8U)
#define SPI_INTENCLR_TXUREN_SHIFT                (3U)
/*! TXUREN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_TXUREN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_TXUREN_SHIFT)) & SPI_INTENCLR_TXUREN_MASK)

#define SPI_INTENCLR_SSAEN_MASK                  (0x10U)
#define SPI_INTENCLR_SSAEN_SHIFT                 (4U)
/*! SSAEN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSAEN_SHIFT)) & SPI_INTENCLR_SSAEN_MASK)

#define SPI_INTENCLR_SSDEN_MASK                  (0x20U)
#define SPI_INTENCLR_SSDEN_SHIFT                 (5U)
/*! SSDEN - Writing 1 clears the corresponding bits in the INTENSET register. */
#define SPI_INTENCLR_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSDEN_SHIFT)) & SPI_INTENCLR_SSDEN_MASK)
/*! @} */

/*! @name RXDAT - SPI Receive Data */
/*! @{ */

#define SPI_RXDAT_RXDAT_MASK                     (0xFFFFU)
#define SPI_RXDAT_RXDAT_SHIFT                    (0U)
/*! RXDAT - Receiver Data. This contains the next piece of received data. The number of bits that
 *    are used depends on the LEN setting in TXCTL / TXDATCTL.
 */
#define SPI_RXDAT_RXDAT(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXDAT_SHIFT)) & SPI_RXDAT_RXDAT_MASK)

#define SPI_RXDAT_RXSSEL0_N_MASK                 (0x10000U)
#define SPI_RXDAT_RXSSEL0_N_SHIFT                (16U)
/*! RXSSEL0_N - Slave Select for receive. This field allows the state of the SSEL0 pin to be saved
 *    along with received data. The value will reflect the SSEL0 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_RXDAT_RXSSEL0_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL0_N_SHIFT)) & SPI_RXDAT_RXSSEL0_N_MASK)

#define SPI_RXDAT_RXSSEL1_N_MASK                 (0x20000U)
#define SPI_RXDAT_RXSSEL1_N_SHIFT                (17U)
/*! RXSSEL1_N - Slave Select for receive. This field allows the state of the SSEL1 pin to be saved
 *    along with received data. The value will reflect the SSEL1 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_RXDAT_RXSSEL1_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL1_N_SHIFT)) & SPI_RXDAT_RXSSEL1_N_MASK)

#define SPI_RXDAT_RXSSEL2_N_MASK                 (0x40000U)
#define SPI_RXDAT_RXSSEL2_N_SHIFT                (18U)
/*! RXSSEL2_N - Slave Select for receive. This field allows the state of the SSEL2 pin to be saved
 *    along with received data. The value will reflect the SSEL2 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_RXDAT_RXSSEL2_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL2_N_SHIFT)) & SPI_RXDAT_RXSSEL2_N_MASK)

#define SPI_RXDAT_RXSSEL3_N_MASK                 (0x80000U)
#define SPI_RXDAT_RXSSEL3_N_SHIFT                (19U)
/*! RXSSEL3_N - Slave Select for receive. This field allows the state of the SSEL3 pin to be saved
 *    along with received data. The value will reflect the SSEL3 pin for both master and slave
 *    operation. A zero indicates that a slave select is active. The actual polarity of each slave select
 *    pin is configured by the related SPOL bit in CFG.
 */
#define SPI_RXDAT_RXSSEL3_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL3_N_SHIFT)) & SPI_RXDAT_RXSSEL3_N_MASK)

#define SPI_RXDAT_SOT_MASK                       (0x100000U)
#define SPI_RXDAT_SOT_SHIFT                      (20U)
/*! SOT - Start of Transfer flag. This flag will be 1 if this is the first data after the SSELs went
 *    from deasserted to asserted (i.e., any previous transfer has ended). This information can be
 *    used to identify the first piece of data in cases where the transfer length is greater than 16
 *    bit.
 */
#define SPI_RXDAT_SOT(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_SOT_SHIFT)) & SPI_RXDAT_SOT_MASK)
/*! @} */

/*! @name TXDATCTL - SPI Transmit Data with Control */
/*! @{ */

#define SPI_TXDATCTL_TXDAT_MASK                  (0xFFFFU)
#define SPI_TXDATCTL_TXDAT_SHIFT                 (0U)
/*! TXDAT - Transmit Data. This field provides from 1 to 16 bits of data to be transmitted. */
#define SPI_TXDATCTL_TXDAT(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXDAT_SHIFT)) & SPI_TXDATCTL_TXDAT_MASK)

#define SPI_TXDATCTL_TXSSEL0_N_MASK              (0x10000U)
#define SPI_TXDATCTL_TXSSEL0_N_SHIFT             (16U)
/*! TXSSEL0_N - Transmit Slave Select. This field asserts SSEL0 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL0 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL0 asserted.
 *  0b1..SSEL0 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL0_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL0_N_SHIFT)) & SPI_TXDATCTL_TXSSEL0_N_MASK)

#define SPI_TXDATCTL_TXSSEL1_N_MASK              (0x20000U)
#define SPI_TXDATCTL_TXSSEL1_N_SHIFT             (17U)
/*! TXSSEL1_N - Transmit Slave Select. This field asserts SSEL1 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL1 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL1 asserted.
 *  0b1..SSEL1 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL1_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL1_N_SHIFT)) & SPI_TXDATCTL_TXSSEL1_N_MASK)

#define SPI_TXDATCTL_TXSSEL2_N_MASK              (0x40000U)
#define SPI_TXDATCTL_TXSSEL2_N_SHIFT             (18U)
/*! TXSSEL2_N - Transmit Slave Select. This field asserts SSEL2 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL2 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL2 asserted.
 *  0b1..SSEL2 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL2_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL2_N_SHIFT)) & SPI_TXDATCTL_TXSSEL2_N_MASK)

#define SPI_TXDATCTL_TXSSEL3_N_MASK              (0x80000U)
#define SPI_TXDATCTL_TXSSEL3_N_SHIFT             (19U)
/*! TXSSEL3_N - Transmit Slave Select. This field asserts SSEL3 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL3 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL3 asserted.
 *  0b1..SSEL3 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL3_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL3_N_SHIFT)) & SPI_TXDATCTL_TXSSEL3_N_MASK)

#define SPI_TXDATCTL_EOT_MASK                    (0x100000U)
#define SPI_TXDATCTL_EOT_SHIFT                   (20U)
/*! EOT - End of Transfer. The asserted SSEL will be deasserted at the end of a transfer, and remain
 *    so for at least the time specified by the Transfer_delay value in the DLY register.
 *  0b0..This piece of data is not treated as the end of a transfer. SSEL will not be deasserted at the end of this data.
 *  0b1..This piece of data is treated as the end of a transfer. SSEL will be deasserted at the end of this piece of data.
 */
#define SPI_TXDATCTL_EOT(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_EOT_SHIFT)) & SPI_TXDATCTL_EOT_MASK)

#define SPI_TXDATCTL_EOF_MASK                    (0x200000U)
#define SPI_TXDATCTL_EOF_SHIFT                   (21U)
/*! EOF - End of Frame. Between frames, a delay may be inserted, as defined by the FRAME_DELAY value
 *    in the DLY register. The end of a frame may not be particularly meaningful if the FRAME_DELAY
 *    value = 0. This control can be used as part of the support for frame lengths greater than 16
 *    bits.
 *  0b0..This piece of data transmitted is not treated as the end of a frame.
 *  0b1..This piece of data is treated as the end of a frame, causing the FRAME_DELAY time to be inserted before subsequent data is transmitted.
 */
#define SPI_TXDATCTL_EOF(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_EOF_SHIFT)) & SPI_TXDATCTL_EOF_MASK)

#define SPI_TXDATCTL_RXIGNORE_MASK               (0x400000U)
#define SPI_TXDATCTL_RXIGNORE_SHIFT              (22U)
/*! RXIGNORE - Receive Ignore. This allows data to be transmitted using the SPI without the need to
 *    read unneeded data from the receiver.Setting this bit simplifies the transmit process and can
 *    be used with the DMA.
 *  0b0..Received data must be read in order to allow transmission to progress. In slave mode, an overrun error
 *       will occur if received data is not read before new data is received.
 *  0b1..Received data is ignored, allowing transmission without reading unneeded received data. No receiver flags are generated.
 */
#define SPI_TXDATCTL_RXIGNORE(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_RXIGNORE_SHIFT)) & SPI_TXDATCTL_RXIGNORE_MASK)

#define SPI_TXDATCTL_LEN_MASK                    (0xF000000U)
#define SPI_TXDATCTL_LEN_SHIFT                   (24U)
/*! LEN - Data Length. Specifies the data length from 1 to 16 bits. Note that transfer lengths
 *    greater than 16 bits are supported by implementing multiple sequential transmits. 0x0 = Data
 *    transfer is 1 bit in length. 0x1 = Data transfer is 2 bits in length. 0x2 = Data transfer is 3 bits
 *    in length. ... 0xF = Data transfer is 16 bits in length.
 *  0b0000..Data transfer is 1 bit in length.
 *  0b0001..Data transfer is 2 bit in length.
 *  0b0010..Data transfer is 3 bit in length.
 *  0b0011..Data transfer is 4 bit in length.
 *  0b0100..Data transfer is 5 bit in length.
 *  0b0101..Data transfer is 6 bit in length.
 *  0b0110..Data transfer is 7 bit in length.
 *  0b0111..Data transfer is 8 bit in length.
 *  0b1000..Data transfer is 9 bit in length.
 *  0b1001..Data transfer is 10 bit in length.
 *  0b1010..Data transfer is 11 bit in length.
 *  0b1011..Data transfer is 12 bit in length.
 *  0b1100..Data transfer is 13 bit in length.
 *  0b1101..Data transfer is 14 bit in length.
 *  0b1110..Data transfer is 15 bit in length.
 *  0b1111..Data transfer is 16 bit in length.
 */
#define SPI_TXDATCTL_LEN(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_LEN_SHIFT)) & SPI_TXDATCTL_LEN_MASK)
/*! @} */

/*! @name TXDAT - SPI Transmit Data. */
/*! @{ */

#define SPI_TXDAT_DATA_MASK                      (0xFFFFU)
#define SPI_TXDAT_DATA_SHIFT                     (0U)
/*! DATA - Transmit Data. This field provides from 4 to 16 bits of data to be transmitted. */
#define SPI_TXDAT_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_TXDAT_DATA_SHIFT)) & SPI_TXDAT_DATA_MASK)
/*! @} */

/*! @name TXCTL - SPI Transmit Control */
/*! @{ */

#define SPI_TXCTL_TXSSEL0_N_MASK                 (0x10000U)
#define SPI_TXCTL_TXSSEL0_N_SHIFT                (16U)
/*! TXSSEL0_N - Transmit Slave Select 0. */
#define SPI_TXCTL_TXSSEL0_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL0_N_SHIFT)) & SPI_TXCTL_TXSSEL0_N_MASK)

#define SPI_TXCTL_TXSSEL1_N_MASK                 (0x20000U)
#define SPI_TXCTL_TXSSEL1_N_SHIFT                (17U)
/*! TXSSEL1_N - Transmit Slave Select 1. */
#define SPI_TXCTL_TXSSEL1_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL1_N_SHIFT)) & SPI_TXCTL_TXSSEL1_N_MASK)

#define SPI_TXCTL_TXSSEL2_N_MASK                 (0x40000U)
#define SPI_TXCTL_TXSSEL2_N_SHIFT                (18U)
/*! TXSSEL2_N - Transmit Slave Select 2. */
#define SPI_TXCTL_TXSSEL2_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL2_N_SHIFT)) & SPI_TXCTL_TXSSEL2_N_MASK)

#define SPI_TXCTL_TXSSEL3_N_MASK                 (0x80000U)
#define SPI_TXCTL_TXSSEL3_N_SHIFT                (19U)
/*! TXSSEL3_N - Transmit Slave Select 3. */
#define SPI_TXCTL_TXSSEL3_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL3_N_SHIFT)) & SPI_TXCTL_TXSSEL3_N_MASK)

#define SPI_TXCTL_EOT_MASK                       (0x100000U)
#define SPI_TXCTL_EOT_SHIFT                      (20U)
/*! EOT - End of Transfer. */
#define SPI_TXCTL_EOT(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_EOT_SHIFT)) & SPI_TXCTL_EOT_MASK)

#define SPI_TXCTL_EOF_MASK                       (0x200000U)
#define SPI_TXCTL_EOF_SHIFT                      (21U)
/*! EOF - End of Frame. */
#define SPI_TXCTL_EOF(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_EOF_SHIFT)) & SPI_TXCTL_EOF_MASK)

#define SPI_TXCTL_RXIGNORE_MASK                  (0x400000U)
#define SPI_TXCTL_RXIGNORE_SHIFT                 (22U)
/*! RXIGNORE - Receive Ignore. */
#define SPI_TXCTL_RXIGNORE(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_RXIGNORE_SHIFT)) & SPI_TXCTL_RXIGNORE_MASK)

#define SPI_TXCTL_LEN_MASK                       (0xF000000U)
#define SPI_TXCTL_LEN_SHIFT                      (24U)
/*! LEN - Data transfer Length. */
#define SPI_TXCTL_LEN(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_LEN_SHIFT)) & SPI_TXCTL_LEN_MASK)
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

#define SPI_INTSTAT_RXRDY_MASK                   (0x1U)
#define SPI_INTSTAT_RXRDY_SHIFT                  (0U)
/*! RXRDY - Receiver Ready flag. */
#define SPI_INTSTAT_RXRDY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_RXRDY_SHIFT)) & SPI_INTSTAT_RXRDY_MASK)

#define SPI_INTSTAT_TXRDY_MASK                   (0x2U)
#define SPI_INTSTAT_TXRDY_SHIFT                  (1U)
/*! TXRDY - Transmitter Ready flag. */
#define SPI_INTSTAT_TXRDY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_TXRDY_SHIFT)) & SPI_INTSTAT_TXRDY_MASK)

#define SPI_INTSTAT_RXOV_MASK                    (0x4U)
#define SPI_INTSTAT_RXOV_SHIFT                   (2U)
/*! RXOV - Receiver Overrun interrupt flag. */
#define SPI_INTSTAT_RXOV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_RXOV_SHIFT)) & SPI_INTSTAT_RXOV_MASK)

#define SPI_INTSTAT_TXUR_MASK                    (0x8U)
#define SPI_INTSTAT_TXUR_SHIFT                   (3U)
/*! TXUR - Transmitter Underrun interrupt flag. */
#define SPI_INTSTAT_TXUR(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_TXUR_SHIFT)) & SPI_INTSTAT_TXUR_MASK)

#define SPI_INTSTAT_SSA_MASK                     (0x10U)
#define SPI_INTSTAT_SSA_SHIFT                    (4U)
/*! SSA - Slave Select Assert. */
#define SPI_INTSTAT_SSA(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSA_SHIFT)) & SPI_INTSTAT_SSA_MASK)

#define SPI_INTSTAT_SSD_MASK                     (0x20U)
#define SPI_INTSTAT_SSD_SHIFT                    (5U)
/*! SSD - Slave Select Deassert. */
#define SPI_INTSTAT_SSD(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSD_SHIFT)) & SPI_INTSTAT_SSD_MASK)

#define SPI_INTSTAT_MSTIDLE_MASK                 (0x100U)
#define SPI_INTSTAT_MSTIDLE_SHIFT                (8U)
/*! MSTIDLE - Master Idle status flag. */
#define SPI_INTSTAT_MSTIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_MSTIDLE_SHIFT)) & SPI_INTSTAT_MSTIDLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40058000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x4005C000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1 }
/** Interrupt vectors for the SPI peripheral type */
#define SPI_IRQS                                 { SPI0_IRQn, SPI1_IRQn }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SWM_Peripheral_Access_Layer SWM Peripheral Access Layer
 * @{
 */

/** SWM - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint32_t PINASSIGN0;                        /**< Pin assign register 0. Assign movable functions U0_TXD, U0_RXD, U0_RTS, U0_CTS., offset: 0x0 */
      __IO uint32_t PINASSIGN1;                        /**< Pin assign register 1. Assign movable functions U0_SCLK, U1_TXD, U1_RXD, U1_RTS., offset: 0x4 */
      __IO uint32_t PINASSIGN2;                        /**< Pin assign register 2. Assign movable functions U1_CTS, U1_SCLK, U2_TXD, U2_RXD., offset: 0x8 */
      __IO uint32_t PINASSIGN3;                        /**< Pin assign register 3. Assign movable function U2_RTS, U2_CTS, U2_SCLK, SPI0_SCK., offset: 0xC */
      __IO uint32_t PINASSIGN4;                        /**< Pin assign register 4. Assign movable functions SPI0_MOSI, SPI0_MISO, SPI0_SSEL0, SPI0_SSEL1., offset: 0x10 */
      __IO uint32_t PINASSIGN5;                        /**< Pin assign register 5. Assign movable functions SPI0_SSEL2, SPI0_SSEL3, SPI1_SCK, SPI1_MOSI, offset: 0x14 */
      __IO uint32_t PINASSIGN6;                        /**< Pin assign register 6. Assign movable functions SPI1_MISO, SPI1_SSEL0, SPI1_SSEL1, SCT0_IN0., offset: 0x18 */
      __IO uint32_t PINASSIGN7;                        /**< Pin assign register 7. Assign movable functions SCT_IN1, SCT_IN2, SCT_IN3, SCT_OUT0., offset: 0x1C */
      __IO uint32_t PINASSIGN8;                        /**< Pin assign register 8. Assign movable functions ACMP0_OUT, CLKOUT, GPIOINT_BMATCH., offset: 0x20 */
    } PINASSIGN;
    __IO uint32_t PINASSIGN_DATA[9];                 /**< Pin assign register, array offset: 0x0, array step: 0x4 */
  };
       uint8_t RESERVED_0[348];
  __IO uint32_t FTM_PINASSIGN0;                    /**< FlexTimer Pin assign register 0 Assign movable functions., offset: 0x180 */
  __IO uint32_t FTM_PINASSIGN1;                    /**< FlexTimer Pin assign register 0 Assign movable functions., offset: 0x184 */
       uint8_t RESERVED_1[56];
  __IO uint32_t PINENABLE0;                        /**< Pin enable register 0. Enables fixed-pin functions ACMP_I0, ACMP_I1, SWCLK, SWDIO, XTALIN, XTALOUT, RESET, CLKIN, VDDCMP and so on., offset: 0x1C0 */
} SWM_Type;

/* ----------------------------------------------------------------------------
   -- SWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SWM_Register_Masks SWM Register Masks
 * @{
 */

/*! @name PINASSIGN0 - Pin assign register 0. Assign movable functions U0_TXD, U0_RXD, U0_RTS, U0_CTS. */
/*! @{ */

#define SWM_PINASSIGN0_U0_TXD_O_MASK             (0xFFU)
#define SWM_PINASSIGN0_U0_TXD_O_SHIFT            (0U)
/*! U0_TXD_O - U0_TXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35) .
 */
#define SWM_PINASSIGN0_U0_TXD_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN0_U0_TXD_O_SHIFT)) & SWM_PINASSIGN0_U0_TXD_O_MASK)

#define SWM_PINASSIGN0_U0_RXD_I_MASK             (0xFF00U)
#define SWM_PINASSIGN0_U0_RXD_I_SHIFT            (8U)
/*! U0_RXD_I - U0_RXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN0_U0_RXD_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN0_U0_RXD_I_SHIFT)) & SWM_PINASSIGN0_U0_RXD_I_MASK)

#define SWM_PINASSIGN0_U0_RTS_O_MASK             (0xFF0000U)
#define SWM_PINASSIGN0_U0_RTS_O_SHIFT            (16U)
/*! U0_RTS_O - U0_RTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN0_U0_RTS_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN0_U0_RTS_O_SHIFT)) & SWM_PINASSIGN0_U0_RTS_O_MASK)

#define SWM_PINASSIGN0_U0_CTS_I_MASK             (0xFF000000U)
#define SWM_PINASSIGN0_U0_CTS_I_SHIFT            (24U)
/*! U0_CTS_I - U0_CTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN0_U0_CTS_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN0_U0_CTS_I_SHIFT)) & SWM_PINASSIGN0_U0_CTS_I_MASK)
/*! @} */

/*! @name PINASSIGN1 - Pin assign register 1. Assign movable functions U0_SCLK, U1_TXD, U1_RXD, U1_RTS. */
/*! @{ */

#define SWM_PINASSIGN1_U0_SCLK_IO_MASK           (0xFFU)
#define SWM_PINASSIGN1_U0_SCLK_IO_SHIFT          (0U)
/*! U0_SCLK_IO - U0_SCLK function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN1_U0_SCLK_IO(x)             (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN1_U0_SCLK_IO_SHIFT)) & SWM_PINASSIGN1_U0_SCLK_IO_MASK)

#define SWM_PINASSIGN1_U1_TXD_O_MASK             (0xFF00U)
#define SWM_PINASSIGN1_U1_TXD_O_SHIFT            (8U)
/*! U1_TXD_O - U1_TXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN1_U1_TXD_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN1_U1_TXD_O_SHIFT)) & SWM_PINASSIGN1_U1_TXD_O_MASK)

#define SWM_PINASSIGN1_U1_RXD_I_MASK             (0xFF0000U)
#define SWM_PINASSIGN1_U1_RXD_I_SHIFT            (16U)
/*! U1_RXD_I - U1_RXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN1_U1_RXD_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN1_U1_RXD_I_SHIFT)) & SWM_PINASSIGN1_U1_RXD_I_MASK)

#define SWM_PINASSIGN1_U1_RTS_O_MASK             (0xFF000000U)
#define SWM_PINASSIGN1_U1_RTS_O_SHIFT            (24U)
/*! U1_RTS_O - U1_RTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN1_U1_RTS_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN1_U1_RTS_O_SHIFT)) & SWM_PINASSIGN1_U1_RTS_O_MASK)
/*! @} */

/*! @name PINASSIGN2 - Pin assign register 2. Assign movable functions U1_CTS, U1_SCLK, U2_TXD, U2_RXD. */
/*! @{ */

#define SWM_PINASSIGN2_U1_CTS_I_MASK             (0xFFU)
#define SWM_PINASSIGN2_U1_CTS_I_SHIFT            (0U)
/*! U1_CTS_I - U1_CTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN2_U1_CTS_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN2_U1_CTS_I_SHIFT)) & SWM_PINASSIGN2_U1_CTS_I_MASK)

#define SWM_PINASSIGN2_U1_SCLK_IO_MASK           (0xFF00U)
#define SWM_PINASSIGN2_U1_SCLK_IO_SHIFT          (8U)
/*! U1_SCLK_IO - U1_SCLK function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN2_U1_SCLK_IO(x)             (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN2_U1_SCLK_IO_SHIFT)) & SWM_PINASSIGN2_U1_SCLK_IO_MASK)

#define SWM_PINASSIGN2_U2_TXD_O_MASK             (0xFF0000U)
#define SWM_PINASSIGN2_U2_TXD_O_SHIFT            (16U)
/*! U2_TXD_O - U2_TXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN2_U2_TXD_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN2_U2_TXD_O_SHIFT)) & SWM_PINASSIGN2_U2_TXD_O_MASK)

#define SWM_PINASSIGN2_U2_RXD_I_MASK             (0xFF000000U)
#define SWM_PINASSIGN2_U2_RXD_I_SHIFT            (24U)
/*! U2_RXD_I - U2_RXD function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN2_U2_RXD_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN2_U2_RXD_I_SHIFT)) & SWM_PINASSIGN2_U2_RXD_I_MASK)
/*! @} */

/*! @name PINASSIGN3 - Pin assign register 3. Assign movable function U2_RTS, U2_CTS, U2_SCLK, SPI0_SCK. */
/*! @{ */

#define SWM_PINASSIGN3_U2_RTS_O_MASK             (0xFFU)
#define SWM_PINASSIGN3_U2_RTS_O_SHIFT            (0U)
/*! U2_RTS_O - U2_RTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN3_U2_RTS_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN3_U2_RTS_O_SHIFT)) & SWM_PINASSIGN3_U2_RTS_O_MASK)

#define SWM_PINASSIGN3_U2_CTS_I_MASK             (0xFF00U)
#define SWM_PINASSIGN3_U2_CTS_I_SHIFT            (8U)
/*! U2_CTS_I - U2_CTS function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN3_U2_CTS_I(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN3_U2_CTS_I_SHIFT)) & SWM_PINASSIGN3_U2_CTS_I_MASK)

#define SWM_PINASSIGN3_U2_SCLK_IO_MASK           (0xFF0000U)
#define SWM_PINASSIGN3_U2_SCLK_IO_SHIFT          (16U)
/*! U2_SCLK_IO - U2_SCLK function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN3_U2_SCLK_IO(x)             (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN3_U2_SCLK_IO_SHIFT)) & SWM_PINASSIGN3_U2_SCLK_IO_MASK)

#define SWM_PINASSIGN3_SPI0_SCK_IO_MASK          (0xFF000000U)
#define SWM_PINASSIGN3_SPI0_SCK_IO_SHIFT         (24U)
/*! SPI0_SCK_IO - SPI0_SCK function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN3_SPI0_SCK_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN3_SPI0_SCK_IO_SHIFT)) & SWM_PINASSIGN3_SPI0_SCK_IO_MASK)
/*! @} */

/*! @name PINASSIGN4 - Pin assign register 4. Assign movable functions SPI0_MOSI, SPI0_MISO, SPI0_SSEL0, SPI0_SSEL1. */
/*! @{ */

#define SWM_PINASSIGN4_SPI0_MOSI_IO_MASK         (0xFFU)
#define SWM_PINASSIGN4_SPI0_MOSI_IO_SHIFT        (0U)
/*! SPI0_MOSI_IO - SPI0_MOSI function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN4_SPI0_MOSI_IO(x)           (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN4_SPI0_MOSI_IO_SHIFT)) & SWM_PINASSIGN4_SPI0_MOSI_IO_MASK)

#define SWM_PINASSIGN4_SPI0_MISO_IO_MASK         (0xFF00U)
#define SWM_PINASSIGN4_SPI0_MISO_IO_SHIFT        (8U)
/*! SPI0_MISO_IO - SPI0_MISIO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN4_SPI0_MISO_IO(x)           (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN4_SPI0_MISO_IO_SHIFT)) & SWM_PINASSIGN4_SPI0_MISO_IO_MASK)

#define SWM_PINASSIGN4_SPI0_SSEL0_IO_MASK        (0xFF0000U)
#define SWM_PINASSIGN4_SPI0_SSEL0_IO_SHIFT       (16U)
/*! SPI0_SSEL0_IO - SPI0_SSEL0 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN4_SPI0_SSEL0_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN4_SPI0_SSEL0_IO_SHIFT)) & SWM_PINASSIGN4_SPI0_SSEL0_IO_MASK)

#define SWM_PINASSIGN4_SPI0_SSEL1_IO_MASK        (0xFF000000U)
#define SWM_PINASSIGN4_SPI0_SSEL1_IO_SHIFT       (24U)
/*! SPI0_SSEL1_IO - SPI0_SSEL1 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN4_SPI0_SSEL1_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN4_SPI0_SSEL1_IO_SHIFT)) & SWM_PINASSIGN4_SPI0_SSEL1_IO_MASK)
/*! @} */

/*! @name PINASSIGN5 - Pin assign register 5. Assign movable functions SPI0_SSEL2, SPI0_SSEL3, SPI1_SCK, SPI1_MOSI */
/*! @{ */

#define SWM_PINASSIGN5_SPI0_SSEL2_IO_MASK        (0xFFU)
#define SWM_PINASSIGN5_SPI0_SSEL2_IO_SHIFT       (0U)
/*! SPI0_SSEL2_IO - SPI0_SSEL2 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN5_SPI0_SSEL2_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN5_SPI0_SSEL2_IO_SHIFT)) & SWM_PINASSIGN5_SPI0_SSEL2_IO_MASK)

#define SWM_PINASSIGN5_SPI0_SSEL3_IO_MASK        (0xFF00U)
#define SWM_PINASSIGN5_SPI0_SSEL3_IO_SHIFT       (8U)
/*! SPI0_SSEL3_IO - SPI0_SSEL3 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN5_SPI0_SSEL3_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN5_SPI0_SSEL3_IO_SHIFT)) & SWM_PINASSIGN5_SPI0_SSEL3_IO_MASK)

#define SWM_PINASSIGN5_SPI1_SCK_IO_MASK          (0xFF0000U)
#define SWM_PINASSIGN5_SPI1_SCK_IO_SHIFT         (16U)
/*! SPI1_SCK_IO - SPI1_SCK function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN5_SPI1_SCK_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN5_SPI1_SCK_IO_SHIFT)) & SWM_PINASSIGN5_SPI1_SCK_IO_MASK)

#define SWM_PINASSIGN5_SPI1_MOSI_IO_MASK         (0xFF000000U)
#define SWM_PINASSIGN5_SPI1_MOSI_IO_SHIFT        (24U)
/*! SPI1_MOSI_IO - SPI1_MOSI function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN5_SPI1_MOSI_IO(x)           (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN5_SPI1_MOSI_IO_SHIFT)) & SWM_PINASSIGN5_SPI1_MOSI_IO_MASK)
/*! @} */

/*! @name PINASSIGN6 - Pin assign register 6. Assign movable functions SPI1_MISO, SPI1_SSEL0, SPI1_SSEL1, SCT0_IN0. */
/*! @{ */

#define SWM_PINASSIGN6_SPI1_MISO_IO_MASK         (0xFFU)
#define SWM_PINASSIGN6_SPI1_MISO_IO_SHIFT        (0U)
/*! SPI1_MISO_IO - SPI1_MISO function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN6_SPI1_MISO_IO(x)           (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN6_SPI1_MISO_IO_SHIFT)) & SWM_PINASSIGN6_SPI1_MISO_IO_MASK)

#define SWM_PINASSIGN6_SPI1_SSEL0_IO_MASK        (0xFF00U)
#define SWM_PINASSIGN6_SPI1_SSEL0_IO_SHIFT       (8U)
/*! SPI1_SSEL0_IO - SPI1_SSEL0 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN6_SPI1_SSEL0_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN6_SPI1_SSEL0_IO_SHIFT)) & SWM_PINASSIGN6_SPI1_SSEL0_IO_MASK)

#define SWM_PINASSIGN6_SPI1_SSEL1_IO_MASK        (0xFF0000U)
#define SWM_PINASSIGN6_SPI1_SSEL1_IO_SHIFT       (16U)
/*! SPI1_SSEL1_IO - SPI1_SSEL1 function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN6_SPI1_SSEL1_IO(x)          (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN6_SPI1_SSEL1_IO_SHIFT)) & SWM_PINASSIGN6_SPI1_SSEL1_IO_MASK)

#define SWM_PINASSIGN6_I2C0_SDA_IO_MASK          (0xFF000000U)
#define SWM_PINASSIGN6_I2C0_SDA_IO_SHIFT         (24U)
/*! I2C0_SDA_IO - I2C0_SDA_IO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN6_I2C0_SDA_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN6_I2C0_SDA_IO_SHIFT)) & SWM_PINASSIGN6_I2C0_SDA_IO_MASK)
/*! @} */

/*! @name PINASSIGN7 - Pin assign register 7. Assign movable functions SCT_IN1, SCT_IN2, SCT_IN3, SCT_OUT0. */
/*! @{ */

#define SWM_PINASSIGN7_I2C0_SCL_IO_MASK          (0xFFU)
#define SWM_PINASSIGN7_I2C0_SCL_IO_SHIFT         (0U)
/*! I2C0_SCL_IO - I2C0_SCL_IO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN7_I2C0_SCL_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN7_I2C0_SCL_IO_SHIFT)) & SWM_PINASSIGN7_I2C0_SCL_IO_MASK)

#define SWM_PINASSIGN7_I3C0_SDA_IO_MASK          (0xFF00U)
#define SWM_PINASSIGN7_I3C0_SDA_IO_SHIFT         (8U)
/*! I3C0_SDA_IO - I3C0_SDA_IO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN7_I3C0_SDA_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN7_I3C0_SDA_IO_SHIFT)) & SWM_PINASSIGN7_I3C0_SDA_IO_MASK)

#define SWM_PINASSIGN7_I3C0_SCL_IO_MASK          (0xFF0000U)
#define SWM_PINASSIGN7_I3C0_SCL_IO_SHIFT         (16U)
/*! I3C0_SCL_IO - I3C0_SCL_IO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN7_I3C0_SCL_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN7_I3C0_SCL_IO_SHIFT)) & SWM_PINASSIGN7_I3C0_SCL_IO_MASK)

#define SWM_PINASSIGN7_I3C0_PUR_IO_MASK          (0xFF000000U)
#define SWM_PINASSIGN7_I3C0_PUR_IO_SHIFT         (24U)
/*! I3C0_PUR_IO - I3C0_PUR_IO function assignment. The value is the pin number to be assigned to
 *    this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN7_I3C0_PUR_IO(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN7_I3C0_PUR_IO_SHIFT)) & SWM_PINASSIGN7_I3C0_PUR_IO_MASK)
/*! @} */

/*! @name PINASSIGN8 - Pin assign register 8. Assign movable functions ACMP0_OUT, CLKOUT, GPIOINT_BMATCH. */
/*! @{ */

#define SWM_PINASSIGN8_ACMP0_OUT_O_MASK          (0xFFU)
#define SWM_PINASSIGN8_ACMP0_OUT_O_SHIFT         (0U)
/*! ACMP0_OUT_O - ACMP0_OUT function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0
 *    (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN8_ACMP0_OUT_O(x)            (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN8_ACMP0_OUT_O_SHIFT)) & SWM_PINASSIGN8_ACMP0_OUT_O_MASK)

#define SWM_PINASSIGN8_CLKOUT_O_MASK             (0xFF00U)
#define SWM_PINASSIGN8_CLKOUT_O_SHIFT            (8U)
/*! CLKOUT_O - CLKOUT function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN8_CLKOUT_O(x)               (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN8_CLKOUT_O_SHIFT)) & SWM_PINASSIGN8_CLKOUT_O_MASK)

#define SWM_PINASSIGN8_GPIO_INT_BMAT_O_MASK      (0xFF0000U)
#define SWM_PINASSIGN8_GPIO_INT_BMAT_O_SHIFT     (16U)
/*! GPIO_INT_BMAT_O - GPIO_INT_BMAT function assignment. The value is the pin number to be assigned
 *    to this function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from
 *    PIO1_0 (=0x20) to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN8_GPIO_INT_BMAT_O(x)        (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN8_GPIO_INT_BMAT_O_SHIFT)) & SWM_PINASSIGN8_GPIO_INT_BMAT_O_MASK)
/*! @} */

/*! @name PINASSIGN_DATA - Pin assign register */
/*! @{ */

#define SWM_PINASSIGN_DATA_DATA0_MASK            (0xFFU)
#define SWM_PINASSIGN_DATA_DATA0_SHIFT           (0U)
/*! DATA0 - T0_MAT3 function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN_DATA_DATA0(x)              (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN_DATA_DATA0_SHIFT)) & SWM_PINASSIGN_DATA_DATA0_MASK)

#define SWM_PINASSIGN_DATA_DATA1_MASK            (0xFF00U)
#define SWM_PINASSIGN_DATA_DATA1_SHIFT           (8U)
/*! DATA1 - T0_CAP0 function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN_DATA_DATA1(x)              (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN_DATA_DATA1_SHIFT)) & SWM_PINASSIGN_DATA_DATA1_MASK)

#define SWM_PINASSIGN_DATA_DATA2_MASK            (0xFF0000U)
#define SWM_PINASSIGN_DATA_DATA2_SHIFT           (16U)
/*! DATA2 - T0_CAP1 function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN_DATA_DATA2(x)              (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN_DATA_DATA2_SHIFT)) & SWM_PINASSIGN_DATA_DATA2_MASK)

#define SWM_PINASSIGN_DATA_DATA3_MASK            (0xFF000000U)
#define SWM_PINASSIGN_DATA_DATA3_SHIFT           (24U)
/*! DATA3 - T0_CAP2 function assignment. The value is the pin number to be assigned to this
 *    function. The following pins are available: PIO0_0 (= 0) to PIO0_31 (= 0x1F) and from PIO1_0 (=0x20)
 *    to PIO1_21(=0x35).
 */
#define SWM_PINASSIGN_DATA_DATA3(x)              (((uint32_t)(((uint32_t)(x)) << SWM_PINASSIGN_DATA_DATA3_SHIFT)) & SWM_PINASSIGN_DATA_DATA3_MASK)
/*! @} */

/* The count of SWM_PINASSIGN_DATA */
#define SWM_PINASSIGN_DATA_COUNT                 (9U)

/*! @name FTM_PINASSIGN0 - FlexTimer Pin assign register 0 Assign movable functions. */
/*! @{ */

#define SWM_FTM_PINASSIGN0_FTM0_EXTCLK_MASK      (0x3U)
#define SWM_FTM_PINASSIGN0_FTM0_EXTCLK_SHIFT     (0U)
/*! FTM0_EXTCLK - Assign movable function FTM0_EXTCLK 00 = Selection 0 function pins 01 = Selection
 *    1 function pins 10 = Selection 2 function pins 11 = Selection 3 function pins
 */
#define SWM_FTM_PINASSIGN0_FTM0_EXTCLK(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_EXTCLK_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_EXTCLK_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH0_MASK         (0xCU)
#define SWM_FTM_PINASSIGN0_FTM0_CH0_SHIFT        (2U)
/*! FTM0_CH0 - Assign movable function FTM0_CH0 */
#define SWM_FTM_PINASSIGN0_FTM0_CH0(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH0_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH0_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH1_MASK         (0x30U)
#define SWM_FTM_PINASSIGN0_FTM0_CH1_SHIFT        (4U)
/*! FTM0_CH1 - Assign movable function FTM0_CH1 */
#define SWM_FTM_PINASSIGN0_FTM0_CH1(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH1_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH1_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH2_MASK         (0xC0U)
#define SWM_FTM_PINASSIGN0_FTM0_CH2_SHIFT        (6U)
/*! FTM0_CH2 - Assign movable function FTM0_CH2 */
#define SWM_FTM_PINASSIGN0_FTM0_CH2(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH2_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH2_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH3_MASK         (0x300U)
#define SWM_FTM_PINASSIGN0_FTM0_CH3_SHIFT        (8U)
/*! FTM0_CH3 - Assign movable function FTM0_CH3 */
#define SWM_FTM_PINASSIGN0_FTM0_CH3(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH3_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH3_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH4_MASK         (0xC00U)
#define SWM_FTM_PINASSIGN0_FTM0_CH4_SHIFT        (10U)
/*! FTM0_CH4 - Assign movable function FTM0_CH4 */
#define SWM_FTM_PINASSIGN0_FTM0_CH4(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH4_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH4_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_CH5_MASK         (0x3000U)
#define SWM_FTM_PINASSIGN0_FTM0_CH5_SHIFT        (12U)
/*! FTM0_CH5 - Assign movable function FTM0_CH5 */
#define SWM_FTM_PINASSIGN0_FTM0_CH5(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_CH5_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_CH5_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_FAULT0_MASK      (0xC000U)
#define SWM_FTM_PINASSIGN0_FTM0_FAULT0_SHIFT     (14U)
/*! FTM0_FAULT0 - Assign movable function FTM0_FAULT0 */
#define SWM_FTM_PINASSIGN0_FTM0_FAULT0(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_FAULT0_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_FAULT0_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_FAULT1_MASK      (0x30000U)
#define SWM_FTM_PINASSIGN0_FTM0_FAULT1_SHIFT     (16U)
/*! FTM0_FAULT1 - Assign movable function FTM0_FAULT1 */
#define SWM_FTM_PINASSIGN0_FTM0_FAULT1(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_FAULT1_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_FAULT1_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_FAULT2_MASK      (0xC0000U)
#define SWM_FTM_PINASSIGN0_FTM0_FAULT2_SHIFT     (18U)
/*! FTM0_FAULT2 - Assign movable function FTM0_FAULT2 */
#define SWM_FTM_PINASSIGN0_FTM0_FAULT2(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_FAULT2_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_FAULT2_MASK)

#define SWM_FTM_PINASSIGN0_FTM0_FAULT3_MASK      (0x300000U)
#define SWM_FTM_PINASSIGN0_FTM0_FAULT3_SHIFT     (20U)
/*! FTM0_FAULT3 - Assign movable function FTM0_FAULT3 */
#define SWM_FTM_PINASSIGN0_FTM0_FAULT3(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM0_FAULT3_SHIFT)) & SWM_FTM_PINASSIGN0_FTM0_FAULT3_MASK)

#define SWM_FTM_PINASSIGN0_FTM1_EXTCLK_MASK      (0xC00000U)
#define SWM_FTM_PINASSIGN0_FTM1_EXTCLK_SHIFT     (22U)
/*! FTM1_EXTCLK - Assign movable function FTM1_EXTCLK */
#define SWM_FTM_PINASSIGN0_FTM1_EXTCLK(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM1_EXTCLK_SHIFT)) & SWM_FTM_PINASSIGN0_FTM1_EXTCLK_MASK)

#define SWM_FTM_PINASSIGN0_FTM1_CH0_MASK         (0x3000000U)
#define SWM_FTM_PINASSIGN0_FTM1_CH0_SHIFT        (24U)
/*! FTM1_CH0 - Assign movable function FTM1_CH0 */
#define SWM_FTM_PINASSIGN0_FTM1_CH0(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM1_CH0_SHIFT)) & SWM_FTM_PINASSIGN0_FTM1_CH0_MASK)

#define SWM_FTM_PINASSIGN0_FTM1_CH1_MASK         (0xC000000U)
#define SWM_FTM_PINASSIGN0_FTM1_CH1_SHIFT        (26U)
/*! FTM1_CH1 - Assign movable function FTM1_CH1 */
#define SWM_FTM_PINASSIGN0_FTM1_CH1(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM1_CH1_SHIFT)) & SWM_FTM_PINASSIGN0_FTM1_CH1_MASK)

#define SWM_FTM_PINASSIGN0_FTM1_CH2_MASK         (0x30000000U)
#define SWM_FTM_PINASSIGN0_FTM1_CH2_SHIFT        (28U)
/*! FTM1_CH2 - Assign movable function FTM1_CH2 */
#define SWM_FTM_PINASSIGN0_FTM1_CH2(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM1_CH2_SHIFT)) & SWM_FTM_PINASSIGN0_FTM1_CH2_MASK)

#define SWM_FTM_PINASSIGN0_FTM1_CH3_MASK         (0xC0000000U)
#define SWM_FTM_PINASSIGN0_FTM1_CH3_SHIFT        (30U)
/*! FTM1_CH3 - Assign movable function FTM1_CH3 */
#define SWM_FTM_PINASSIGN0_FTM1_CH3(x)           (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN0_FTM1_CH3_SHIFT)) & SWM_FTM_PINASSIGN0_FTM1_CH3_MASK)
/*! @} */

/*! @name FTM_PINASSIGN1 - FlexTimer Pin assign register 0 Assign movable functions. */
/*! @{ */

#define SWM_FTM_PINASSIGN1_FTM1_QD_PHA_MASK      (0x3U)
#define SWM_FTM_PINASSIGN1_FTM1_QD_PHA_SHIFT     (0U)
/*! FTM1_QD_PHA - Assign movable function FTM1_QD_PHA */
#define SWM_FTM_PINASSIGN1_FTM1_QD_PHA(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN1_FTM1_QD_PHA_SHIFT)) & SWM_FTM_PINASSIGN1_FTM1_QD_PHA_MASK)

#define SWM_FTM_PINASSIGN1_FTM1_QD_PHB_MASK      (0xCU)
#define SWM_FTM_PINASSIGN1_FTM1_QD_PHB_SHIFT     (2U)
/*! FTM1_QD_PHB - Assign movable function FTM1_QD_PHB */
#define SWM_FTM_PINASSIGN1_FTM1_QD_PHB(x)        (((uint32_t)(((uint32_t)(x)) << SWM_FTM_PINASSIGN1_FTM1_QD_PHB_SHIFT)) & SWM_FTM_PINASSIGN1_FTM1_QD_PHB_MASK)
/*! @} */

/*! @name PINENABLE0 - Pin enable register 0. Enables fixed-pin functions ACMP_I0, ACMP_I1, SWCLK, SWDIO, XTALIN, XTALOUT, RESET, CLKIN, VDDCMP and so on. */
/*! @{ */

#define SWM_PINENABLE0_ACMP_I1_MASK              (0x1U)
#define SWM_PINENABLE0_ACMP_I1_SHIFT             (0U)
/*! ACMP_I1 - ACMP_I1 function select.
 *  0b0..ACMP_I1 enabled on pin PIO0_00.
 *  0b1..ACMP_I1 disabled.
 */
#define SWM_PINENABLE0_ACMP_I1(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ACMP_I1_SHIFT)) & SWM_PINENABLE0_ACMP_I1_MASK)

#define SWM_PINENABLE0_ACMP_I2_MASK              (0x2U)
#define SWM_PINENABLE0_ACMP_I2_SHIFT             (1U)
/*! ACMP_I2 - ACMP_I2 function select.
 *  0b0..ACMP_I2 enabled on pin PIO0_1.
 *  0b1..ACMP_I2 disabled.
 */
#define SWM_PINENABLE0_ACMP_I2(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ACMP_I2_SHIFT)) & SWM_PINENABLE0_ACMP_I2_MASK)

#define SWM_PINENABLE0_ACMP_I3_MASK              (0x4U)
#define SWM_PINENABLE0_ACMP_I3_SHIFT             (2U)
/*! ACMP_I3 - ACMP_I3 function select.
 *  0b0..ACMP_I3 enabled on pin PIO0_14.
 *  0b1..ACMP_I3 disabled.
 */
#define SWM_PINENABLE0_ACMP_I3(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ACMP_I3_SHIFT)) & SWM_PINENABLE0_ACMP_I3_MASK)

#define SWM_PINENABLE0_ACMP_I4_MASK              (0x8U)
#define SWM_PINENABLE0_ACMP_I4_SHIFT             (3U)
/*! ACMP_I4 - ACMP_I4 function select.
 *  0b0..ACMP_I4 enabled on pin PIO0_23.
 *  0b1..ACMP_I4 disabled.
 */
#define SWM_PINENABLE0_ACMP_I4(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ACMP_I4_SHIFT)) & SWM_PINENABLE0_ACMP_I4_MASK)

#define SWM_PINENABLE0_ACMP_I5_MASK              (0x10U)
#define SWM_PINENABLE0_ACMP_I5_SHIFT             (4U)
/*! ACMP_I5 - ACMP_I5 function select.
 *  0b0..ACMP_I5 enabled on pin PIO0_30.
 *  0b1..ACMP_I5 disabled.
 */
#define SWM_PINENABLE0_ACMP_I5(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ACMP_I5_SHIFT)) & SWM_PINENABLE0_ACMP_I5_MASK)

#define SWM_PINENABLE0_SWCLK_MASK                (0x20U)
#define SWM_PINENABLE0_SWCLK_SHIFT               (5U)
/*! SWCLK - SWCLK function select.
 *  0b0..SWCLK enabled on pin PIO0_3.
 *  0b1..SWCLK disabled.
 */
#define SWM_PINENABLE0_SWCLK(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_SWCLK_SHIFT)) & SWM_PINENABLE0_SWCLK_MASK)

#define SWM_PINENABLE0_SWDIO_MASK                (0x40U)
#define SWM_PINENABLE0_SWDIO_SHIFT               (6U)
/*! SWDIO - SWDIO function select.
 *  0b0..SWDIO enabled on pin PIO0_2.
 *  0b1..SWDIO disabled.
 */
#define SWM_PINENABLE0_SWDIO(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_SWDIO_SHIFT)) & SWM_PINENABLE0_SWDIO_MASK)

#define SWM_PINENABLE0_RESETN_MASK               (0x80U)
#define SWM_PINENABLE0_RESETN_SHIFT              (7U)
/*! RESETN - RESETN function select.
 *  0b0..RESETN enabled on pin PIO0_5.
 *  0b1..RESETN disabled.
 */
#define SWM_PINENABLE0_RESETN(x)                 (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_RESETN_SHIFT)) & SWM_PINENABLE0_RESETN_MASK)

#define SWM_PINENABLE0_CLKIN_MASK                (0x100U)
#define SWM_PINENABLE0_CLKIN_SHIFT               (8U)
/*! CLKIN - CLKIN function select.
 *  0b0..CLKIN enabled on pin PIO0_1.
 *  0b1..CLKIN disabled.
 */
#define SWM_PINENABLE0_CLKIN(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_CLKIN_SHIFT)) & SWM_PINENABLE0_CLKIN_MASK)

#define SWM_PINENABLE0_CMPVREF_MASK              (0x200U)
#define SWM_PINENABLE0_CMPVREF_SHIFT             (9U)
/*! CMPVREF - CMPVREF function select.
 *  0b0..CMPVREF enabled on pin PIO0_6.
 *  0b1..CMPVREF disabled.
 */
#define SWM_PINENABLE0_CMPVREF(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_CMPVREF_SHIFT)) & SWM_PINENABLE0_CMPVREF_MASK)

#define SWM_PINENABLE0_XTALIN_MASK               (0x400U)
#define SWM_PINENABLE0_XTALIN_SHIFT              (10U)
/*! XTALIN - XTALIN function select.
 *  0b0..XTALIN enabled on pin PIO0_8.
 *  0b1..XTALIN disabled.
 */
#define SWM_PINENABLE0_XTALIN(x)                 (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_XTALIN_SHIFT)) & SWM_PINENABLE0_XTALIN_MASK)

#define SWM_PINENABLE0_XTALOUT_MASK              (0x800U)
#define SWM_PINENABLE0_XTALOUT_SHIFT             (11U)
/*! XTALOUT - XTALOUT function select.
 *  0b0..XTALOUT enabled on pin PIO0_9.
 *  0b1..XTALOUT disabled.
 */
#define SWM_PINENABLE0_XTALOUT(x)                (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_XTALOUT_SHIFT)) & SWM_PINENABLE0_XTALOUT_MASK)

#define SWM_PINENABLE0_ADC_0_MASK                (0x1000U)
#define SWM_PINENABLE0_ADC_0_SHIFT               (12U)
/*! ADC_0 - ADC_0 function select.
 *  0b0..ADC_0 enabled on pin PIO0_7.
 *  0b1..ADC_0 disabled.
 */
#define SWM_PINENABLE0_ADC_0(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_0_SHIFT)) & SWM_PINENABLE0_ADC_0_MASK)

#define SWM_PINENABLE0_ADC_1_MASK                (0x2000U)
#define SWM_PINENABLE0_ADC_1_SHIFT               (13U)
/*! ADC_1 - ADC_1 function select.
 *  0b0..ADC_1 enabled on pin PIO0_6.
 *  0b1..ADC_1 disabled.
 */
#define SWM_PINENABLE0_ADC_1(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_1_SHIFT)) & SWM_PINENABLE0_ADC_1_MASK)

#define SWM_PINENABLE0_ADC_2_MASK                (0x4000U)
#define SWM_PINENABLE0_ADC_2_SHIFT               (14U)
/*! ADC_2 - ADC_2 function select.
 *  0b0..ADC_2 enabled on pin PIO0_14.
 *  0b1..ADC_2 disabled.
 */
#define SWM_PINENABLE0_ADC_2(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_2_SHIFT)) & SWM_PINENABLE0_ADC_2_MASK)

#define SWM_PINENABLE0_ADC_3_MASK                (0x8000U)
#define SWM_PINENABLE0_ADC_3_SHIFT               (15U)
/*! ADC_3 - ADC_3 function select.
 *  0b0..ADC_3 enabled on pin PIO0_23.
 *  0b1..ADC_3 disabled.
 */
#define SWM_PINENABLE0_ADC_3(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_3_SHIFT)) & SWM_PINENABLE0_ADC_3_MASK)

#define SWM_PINENABLE0_ADC_4_MASK                (0x10000U)
#define SWM_PINENABLE0_ADC_4_SHIFT               (16U)
/*! ADC_4 - ADC_4 function select.
 *  0b0..ADC_4 enabled on pin PIO0_22.
 *  0b1..ADC_4 disabled.
 */
#define SWM_PINENABLE0_ADC_4(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_4_SHIFT)) & SWM_PINENABLE0_ADC_4_MASK)

#define SWM_PINENABLE0_ADC_5_MASK                (0x20000U)
#define SWM_PINENABLE0_ADC_5_SHIFT               (17U)
/*! ADC_5 - ADC_5 function select.
 *  0b0..ADC_5 enabled on pin PIO0_21.
 *  0b1..ADC_5 disabled.
 */
#define SWM_PINENABLE0_ADC_5(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_5_SHIFT)) & SWM_PINENABLE0_ADC_5_MASK)

#define SWM_PINENABLE0_ADC_6_MASK                (0x40000U)
#define SWM_PINENABLE0_ADC_6_SHIFT               (18U)
/*! ADC_6 - ADC_6 function select.
 *  0b0..ADC_6 enabled on pin PIO0_20.
 *  0b1..ADC_6 disabled.
 */
#define SWM_PINENABLE0_ADC_6(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_6_SHIFT)) & SWM_PINENABLE0_ADC_6_MASK)

#define SWM_PINENABLE0_ADC_7_MASK                (0x80000U)
#define SWM_PINENABLE0_ADC_7_SHIFT               (19U)
/*! ADC_7 - ADC_7 function select.
 *  0b0..ADC_7 enabled on pin PIO0_19.
 *  0b1..ADC_7 disabled.
 */
#define SWM_PINENABLE0_ADC_7(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_7_SHIFT)) & SWM_PINENABLE0_ADC_7_MASK)

#define SWM_PINENABLE0_ADC_8_MASK                (0x100000U)
#define SWM_PINENABLE0_ADC_8_SHIFT               (20U)
/*! ADC_8 - ADC_8 function select.
 *  0b0..ADC_8 enabled on pin PIO0_18.
 *  0b1..ADC_8 disabled.
 */
#define SWM_PINENABLE0_ADC_8(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_8_SHIFT)) & SWM_PINENABLE0_ADC_8_MASK)

#define SWM_PINENABLE0_ADC_9_MASK                (0x200000U)
#define SWM_PINENABLE0_ADC_9_SHIFT               (21U)
/*! ADC_9 - ADC_9 function select.
 *  0b0..ADC_9 enabled on pin PIO0_17.
 *  0b1..ADC_9 disabled.
 */
#define SWM_PINENABLE0_ADC_9(x)                  (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_9_SHIFT)) & SWM_PINENABLE0_ADC_9_MASK)

#define SWM_PINENABLE0_ADC_10_MASK               (0x400000U)
#define SWM_PINENABLE0_ADC_10_SHIFT              (22U)
/*! ADC_10 - ADC_10 function select.
 *  0b0..ADC_10 enabled on pin PIO0_13.
 *  0b1..ADC_10 disabled.
 */
#define SWM_PINENABLE0_ADC_10(x)                 (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_10_SHIFT)) & SWM_PINENABLE0_ADC_10_MASK)

#define SWM_PINENABLE0_ADC_11_MASK               (0x800000U)
#define SWM_PINENABLE0_ADC_11_SHIFT              (23U)
/*! ADC_11 - ADC_11 function select.
 *  0b0..ADC_11 enabled on pin PIO0_4.
 *  0b1..ADC_11 disabled.
 */
#define SWM_PINENABLE0_ADC_11(x)                 (((uint32_t)(((uint32_t)(x)) << SWM_PINENABLE0_ADC_11_SHIFT)) & SWM_PINENABLE0_ADC_11_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SWM_Register_Masks */


/* SWM - Peripheral instance base addresses */
/** Peripheral SWM0 base address */
#define SWM0_BASE                                (0x4000C000u)
/** Peripheral SWM0 base pointer */
#define SWM0                                     ((SWM_Type *)SWM0_BASE)
/** Array initializer of SWM peripheral base addresses */
#define SWM_BASE_ADDRS                           { SWM0_BASE }
/** Array initializer of SWM peripheral base pointers */
#define SWM_BASE_PTRS                            { SWM0 }

/*!
 * @}
 */ /* end of group SWM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */

/** SYSCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t SYSMEMREMAP;                       /**< System Remap register, offset: 0x0 */
       uint8_t RESERVED_0[4];
  __IO uint32_t SYSPLLCTRL;                        /**< PLL control, offset: 0x8 */
  __I  uint32_t SYSPLLSTAT;                        /**< PLL status, offset: 0xC */
       uint8_t RESERVED_1[16];
  __IO uint32_t SYSOSCCTRL;                        /**< system oscillator control, offset: 0x20 */
  __IO uint32_t LPOSCCTRL;                         /**< Low power oscillator control, offset: 0x24 */
  __IO uint32_t FROOSCCTRL;                        /**< FRO oscillator control, offset: 0x28 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FRODIRECTCLKUEN;                   /**< FRO direct clock source update enable register, offset: 0x30 */
       uint8_t RESERVED_3[4];
  __IO uint32_t SYSRSTSTAT;                        /**< System reset status register, offset: 0x38 */
       uint8_t RESERVED_4[4];
  __IO uint32_t SYSPLLCLKSEL;                      /**< System PLL clock source select register, offset: 0x40 */
  __IO uint32_t SYSPLLCLKUEN;                      /**< System PLL clock source update enable register, offset: 0x44 */
  __IO uint32_t MAINCLKPLLSEL;                     /**< Main clock source select register, offset: 0x48 */
  __IO uint32_t MAINCLKPLLUEN;                     /**< Main clock source update enable register, offset: 0x4C */
  __IO uint32_t MAINCLKSEL;                        /**< Main clock source select register, offset: 0x50 */
  __IO uint32_t MAINCLKUEN;                        /**< Main clock source update enable register, offset: 0x54 */
  __IO uint32_t SYSAHBCLKDIV;                      /**< System clock divider register, offset: 0x58 */
  __IO uint32_t SYSPLLDIV;                         /**< System clock divider register, offset: 0x5C */
       uint8_t RESERVED_5[4];
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select register, offset: 0x64 */
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider register, offset: 0x68 */
  __IO uint32_t WKTCLKSEL;                         /**< ADC clock source select register, offset: 0x6C */
       uint8_t RESERVED_6[4];
  __IO uint32_t EXTCLKSEL;                         /**< external clock source select register, offset: 0x74 */
  __IO uint32_t I3CCLKDIV;                         /**< I3C clock divider register, offset: 0x78 */
  __IO uint32_t LPOSCEN;                           /**< LPOSC enable register, offset: 0x7C */
  __IO uint32_t SYSAHBCLKCTRL0;                    /**< System clock group 0 control register, offset: 0x80 */
       uint8_t RESERVED_7[4];
  __IO uint32_t PRESETCTRL0;                       /**< Peripheral reset group 0 control register, offset: 0x88 */
  __IO uint32_t PRESETCTRL1;                       /**< Peripheral reset group 1 control register, offset: 0x8C */
  __IO uint32_t FCLKSEL[6];                        /**< peripheral clock source select register. FCLK0SEL~FCLK2SEL are for UART0~UART2 clock source select register.FCLK3SEL~FCLK4SEL are reserved. FCLK5SEL is for I2C clock source select register., array offset: 0x90, array step: 0x4 */
  __IO uint32_t I3CCLKSEL;                         /**< I3C clock source select register, offset: 0xA8 */
  __IO uint32_t I3CSLOWTCCLKSEL;                   /**< I3CSLOWTC clock source select register, offset: 0xAC */
       uint8_t RESERVED_8[4];
  __IO uint32_t FCLKSEL2[2];                       /**< peripheral clock source select register. FCLK0SEL2~FCLK2SEL2 are for SPI0~SPI1 clock source select register., array offset: 0xB4, array step: 0x4 */
  __IO uint32_t FTM0INTTRIGDIV;                    /**< FTM0INTTRIGDIV register, offset: 0xBC */
       uint8_t RESERVED_9[8];
  __IO uint32_t FTMFLTCFG;                         /**< System clock divider register, offset: 0xC8 */
       uint8_t RESERVED_10[4];
  struct {                                         /* offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGDIV;                            /**< fractional generator N divider value register, array offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGMULT;                           /**< fractional generator N multiplier value register, array offset: 0xD4, array step: 0x10 */
    __IO uint32_t FRGCLKSEL;                         /**< FRG N clock source select register, array offset: 0xD8, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } FRG[2];
  __IO uint32_t CLKOUTSEL;                         /**< CLKOUT clock source select register, offset: 0xF0 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider registers, offset: 0xF4 */
       uint8_t RESERVED_11[60];
  __IO uint32_t IOCONCLKDIV6;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x134 */
  __IO uint32_t IOCONCLKDIV5;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x138 */
  __IO uint32_t IOCONCLKDIV4;                      /**< Peripheral clock 4 to the IOCON block for programmable glitch filter, offset: 0x13C */
  __IO uint32_t IOCONCLKDIV3;                      /**< Peripheral clock 3 to the IOCON block for programmable glitch filter, offset: 0x140 */
  __IO uint32_t IOCONCLKDIV2;                      /**< Peripheral clock 2 to the IOCON block for programmable glitch filter, offset: 0x144 */
  __IO uint32_t IOCONCLKDIV1;                      /**< Peripheral clock 1 to the IOCON block for programmable glitch filter, offset: 0x148 */
  __IO uint32_t IOCONCLKDIV0;                      /**< Peripheral clock 0 to the IOCON block for programmable glitch filter, offset: 0x14C */
  __IO uint32_t BODCTRL;                           /**< BOD control register, offset: 0x150 */
  __IO uint32_t SYSTCKCAL;                         /**< System tick timer calibration register, offset: 0x154 */
       uint8_t RESERVED_12[24];
  __IO uint32_t IRQLATENCY;                        /**< IRQ latency register, offset: 0x170 */
  __IO uint32_t NMISRC;                            /**< NMI source selection register, offset: 0x174 */
  __IO uint32_t PINTSEL[8];                        /**< Pin interrupt select registers N, array offset: 0x178, array step: 0x4 */
       uint8_t RESERVED_13[108];
  __IO uint32_t STARTERP0;                         /**< Start logic 0 pin wake-up enable register 0, offset: 0x204 */
       uint8_t RESERVED_14[12];
  __IO uint32_t STARTERP1;                         /**< Start logic 0 pin wake-up enable register 1, offset: 0x214 */
       uint8_t RESERVED_15[24];
  __IO uint32_t PDSLEEPCFG;                        /**< Deep-sleep configuration register, offset: 0x230 */
  __IO uint32_t PDAWAKECFG;                        /**< Wake-up configuration register, offset: 0x234 */
  __IO uint32_t PDRUNCFG;                          /**< Power configuration register, offset: 0x238 */
       uint8_t RESERVED_16[4];
  __IO uint32_t FLASHCACHECFG;                     /**< Flash cache configuration register, offset: 0x240 */
       uint8_t RESERVED_17[436];
  __I  uint32_t DEVICE_ID;                         /**< Part ID register, offset: 0x3F8 */
} SYSCON_Type;

/* ----------------------------------------------------------------------------
   -- SYSCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Register_Masks SYSCON Register Masks
 * @{
 */

/*! @name SYSMEMREMAP - System Remap register */
/*! @{ */

#define SYSCON_SYSMEMREMAP_MAP_MASK              (0x3U)
#define SYSCON_SYSMEMREMAP_MAP_SHIFT             (0U)
/*! MAP - System memory remap. Value 0x3 is reserved.
 *  0b00..Boot Loader Mode. Interrupt vectors are re-mapped to Boot ROM.
 *  0b01..User RAM Mode. Interrupt vectors are re-mapped to Static RAM.
 *  0b10..User Flash Mode. Interrupt vectors are not re-mapped and reside in Flash.
 */
#define SYSCON_SYSMEMREMAP_MAP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSMEMREMAP_MAP_SHIFT)) & SYSCON_SYSMEMREMAP_MAP_MASK)
/*! @} */

/*! @name SYSPLLCTRL - PLL control */
/*! @{ */

#define SYSCON_SYSPLLCTRL_MSEL_MASK              (0x1FU)
#define SYSCON_SYSPLLCTRL_MSEL_SHIFT             (0U)
/*! MSEL - Feedback divider value. The division value M is the programmed MSEL value + 1. 00000:
 *    Division ratio M = 1 to 11111: Division ratio M = 32
 */
#define SYSCON_SYSPLLCTRL_MSEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_MSEL_SHIFT)) & SYSCON_SYSPLLCTRL_MSEL_MASK)

#define SYSCON_SYSPLLCTRL_PSEL_MASK              (0x60U)
#define SYSCON_SYSPLLCTRL_PSEL_SHIFT             (5U)
/*! PSEL - Post divider ratio P. The division ratio is 2 x P.
 *  0b00..P = 1
 *  0b01..P = 2
 *  0b10..P = 4
 *  0b11..P = 8
 */
#define SYSCON_SYSPLLCTRL_PSEL(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCTRL_PSEL_SHIFT)) & SYSCON_SYSPLLCTRL_PSEL_MASK)
/*! @} */

/*! @name SYSPLLSTAT - PLL status */
/*! @{ */

#define SYSCON_SYSPLLSTAT_LOCK_MASK              (0x1U)
#define SYSCON_SYSPLLSTAT_LOCK_SHIFT             (0U)
/*! LOCK - PLL0 lock indicator */
#define SYSCON_SYSPLLSTAT_LOCK(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLSTAT_LOCK_SHIFT)) & SYSCON_SYSPLLSTAT_LOCK_MASK)
/*! @} */

/*! @name SYSOSCCTRL - system oscillator control */
/*! @{ */

#define SYSCON_SYSOSCCTRL_BYPASS_MASK            (0x1U)
#define SYSCON_SYSOSCCTRL_BYPASS_SHIFT           (0U)
/*! BYPASS - oscillator (Xtal) Test Mode input (Active High) */
#define SYSCON_SYSOSCCTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSOSCCTRL_BYPASS_SHIFT)) & SYSCON_SYSOSCCTRL_BYPASS_MASK)

#define SYSCON_SYSOSCCTRL_FREQRANGE_MASK         (0x2U)
#define SYSCON_SYSOSCCTRL_FREQRANGE_SHIFT        (1U)
/*! FREQRANGE - oscillator low / high transconductance selection input (Active High) 1-20MHz '0' : 15-50MHz '1' */
#define SYSCON_SYSOSCCTRL_FREQRANGE(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSOSCCTRL_FREQRANGE_SHIFT)) & SYSCON_SYSOSCCTRL_FREQRANGE_MASK)
/*! @} */

/*! @name LPOSCCTRL - Low power oscillator control */
/*! @{ */

#define SYSCON_LPOSCCTRL_LPOSC_TRIM_MASK         (0xFFU)
#define SYSCON_LPOSCCTRL_LPOSC_TRIM_SHIFT        (0U)
/*! LPOSC_TRIM - Select divider for Fclkana */
#define SYSCON_LPOSCCTRL_LPOSC_TRIM(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCCTRL_LPOSC_TRIM_SHIFT)) & SYSCON_LPOSCCTRL_LPOSC_TRIM_MASK)

#define SYSCON_LPOSCCTRL_LPOSC_TRIM_T_MASK       (0xF00U)
#define SYSCON_LPOSCCTRL_LPOSC_TRIM_T_SHIFT      (8U)
/*! LPOSC_TRIM_T - Select low power oscillator analog output frequency(Fclkana) */
#define SYSCON_LPOSCCTRL_LPOSC_TRIM_T(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCCTRL_LPOSC_TRIM_T_SHIFT)) & SYSCON_LPOSCCTRL_LPOSC_TRIM_T_MASK)

#define SYSCON_LPOSCCTRL_LPOSC_TRIM_C_MASK       (0x7000U)
#define SYSCON_LPOSCCTRL_LPOSC_TRIM_C_SHIFT      (12U)
#define SYSCON_LPOSCCTRL_LPOSC_TRIM_C(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCCTRL_LPOSC_TRIM_C_SHIFT)) & SYSCON_LPOSCCTRL_LPOSC_TRIM_C_MASK)

#define SYSCON_LPOSCCTRL_LPOSC_TST_IREF_EN_MASK  (0x80000000U)
#define SYSCON_LPOSCCTRL_LPOSC_TST_IREF_EN_SHIFT (31U)
#define SYSCON_LPOSCCTRL_LPOSC_TST_IREF_EN(x)    (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCCTRL_LPOSC_TST_IREF_EN_SHIFT)) & SYSCON_LPOSCCTRL_LPOSC_TST_IREF_EN_MASK)
/*! @} */

/*! @name FROOSCCTRL - FRO oscillator control */
/*! @{ */

#define SYSCON_FROOSCCTRL_FRO_DIRECT_MASK        (0x20000U)
#define SYSCON_FROOSCCTRL_FRO_DIRECT_SHIFT       (17U)
/*! FRO_DIRECT - fro direct clock select
 *  0b0..fro_osc out is divided by 2 (normal boot)
 *  0b1..fro clock is direct from FRO oscillator
 */
#define SYSCON_FROOSCCTRL_FRO_DIRECT(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_FROOSCCTRL_FRO_DIRECT_SHIFT)) & SYSCON_FROOSCCTRL_FRO_DIRECT_MASK)
/*! @} */

/*! @name FRODIRECTCLKUEN - FRO direct clock source update enable register */
/*! @{ */

#define SYSCON_FRODIRECTCLKUEN_ENA_MASK          (0x1U)
#define SYSCON_FRODIRECTCLKUEN_ENA_SHIFT         (0U)
/*! ENA - Enable fro clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_FRODIRECTCLKUEN_ENA(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_FRODIRECTCLKUEN_ENA_SHIFT)) & SYSCON_FRODIRECTCLKUEN_ENA_MASK)
/*! @} */

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
/*! EXTRST - Status of the external RESET pin. External reset status.
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

/*! @name SYSPLLCLKSEL - System PLL clock source select register */
/*! @{ */

#define SYSCON_SYSPLLCLKSEL_SEL_MASK             (0x3U)
#define SYSCON_SYSPLLCLKSEL_SEL_SHIFT            (0U)
/*! SEL - System PLL clock source
 *  0b00..FRO
 *  0b01..External clock
 *  0b10..Low power oscillator
 *  0b11..FRO DIV
 */
#define SYSCON_SYSPLLCLKSEL_SEL(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCLKSEL_SEL_SHIFT)) & SYSCON_SYSPLLCLKSEL_SEL_MASK)
/*! @} */

/*! @name SYSPLLCLKUEN - System PLL clock source update enable register */
/*! @{ */

#define SYSCON_SYSPLLCLKUEN_ENA_MASK             (0x1U)
#define SYSCON_SYSPLLCLKUEN_ENA_SHIFT            (0U)
/*! ENA - Enable system PLL clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_SYSPLLCLKUEN_ENA(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLCLKUEN_ENA_SHIFT)) & SYSCON_SYSPLLCLKUEN_ENA_MASK)
/*! @} */

/*! @name MAINCLKPLLSEL - Main clock source select register */
/*! @{ */

#define SYSCON_MAINCLKPLLSEL_SEL_MASK            (0x3U)
#define SYSCON_MAINCLKPLLSEL_SEL_SHIFT           (0U)
/*! SEL - System PLL clock source
 *  0b00..main_clk_pre_pll
 *  0b01..sys pll
 *  0b10..none
 *  0b11..none
 */
#define SYSCON_MAINCLKPLLSEL_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKPLLSEL_SEL_SHIFT)) & SYSCON_MAINCLKPLLSEL_SEL_MASK)
/*! @} */

/*! @name MAINCLKPLLUEN - Main clock source update enable register */
/*! @{ */

#define SYSCON_MAINCLKPLLUEN_ENA_MASK            (0x1U)
#define SYSCON_MAINCLKPLLUEN_ENA_SHIFT           (0U)
/*! ENA - Enable main clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_MAINCLKPLLUEN_ENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKPLLUEN_ENA_SHIFT)) & SYSCON_MAINCLKPLLUEN_ENA_MASK)
/*! @} */

/*! @name MAINCLKSEL - Main clock source select register */
/*! @{ */

#define SYSCON_MAINCLKSEL_SEL_MASK               (0x3U)
#define SYSCON_MAINCLKSEL_SEL_SHIFT              (0U)
/*! SEL - System PLL clock source
 *  0b00..FRO
 *  0b01..External clock
 *  0b10..Low power oscillator
 *  0b11..FRO_DIV
 */
#define SYSCON_MAINCLKSEL_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKSEL_SEL_SHIFT)) & SYSCON_MAINCLKSEL_SEL_MASK)
/*! @} */

/*! @name MAINCLKUEN - Main clock source update enable register */
/*! @{ */

#define SYSCON_MAINCLKUEN_ENA_MASK               (0x1U)
#define SYSCON_MAINCLKUEN_ENA_SHIFT              (0U)
/*! ENA - Enable main clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_MAINCLKUEN_ENA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKUEN_ENA_SHIFT)) & SYSCON_MAINCLKUEN_ENA_MASK)
/*! @} */

/*! @name SYSAHBCLKDIV - System clock divider register */
/*! @{ */

#define SYSCON_SYSAHBCLKDIV_DIV_MASK             (0xFFU)
#define SYSCON_SYSAHBCLKDIV_DIV_SHIFT            (0U)
/*! DIV - System AHB clock divider values 0: System clock disabled. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_SYSAHBCLKDIV_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKDIV_DIV_SHIFT)) & SYSCON_SYSAHBCLKDIV_DIV_MASK)
/*! @} */

/*! @name SYSPLLDIV - System clock divider register */
/*! @{ */

#define SYSCON_SYSPLLDIV_DIV_MASK                (0xFFU)
#define SYSCON_SYSPLLDIV_DIV_SHIFT               (0U)
/*! DIV - System PLL clock divider values 0: System PLL clock disabled. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_SYSPLLDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSPLLDIV_DIV_SHIFT)) & SYSCON_SYSPLLDIV_DIV_MASK)
/*! @} */

/*! @name ADCCLKSEL - ADC clock source select register */
/*! @{ */

#define SYSCON_ADCCLKSEL_SEL_MASK                (0x3U)
#define SYSCON_ADCCLKSEL_SEL_SHIFT               (0U)
/*! SEL - Clock source for ADC clock
 *  0b00..FRO
 *  0b01..sys pll
 *  0b10..none
 *  0b11..none
 */
#define SYSCON_ADCCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKSEL_SEL_SHIFT)) & SYSCON_ADCCLKSEL_SEL_MASK)
/*! @} */

/*! @name ADCCLKDIV - ADC clock divider register */
/*! @{ */

#define SYSCON_ADCCLKDIV_DIV_MASK                (0xFFU)
#define SYSCON_ADCCLKDIV_DIV_SHIFT               (0U)
/*! DIV - ADC clock divider values 0: ADC clock disabled. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_ADCCLKDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_ADCCLKDIV_DIV_SHIFT)) & SYSCON_ADCCLKDIV_DIV_MASK)
/*! @} */

/*! @name WKTCLKSEL - ADC clock source select register */
/*! @{ */

#define SYSCON_WKTCLKSEL_SEL_MASK                (0x1U)
#define SYSCON_WKTCLKSEL_SEL_SHIFT               (0U)
/*! SEL - WKT clock source selection
 *  0b0..FRO_INT
 *  0b1..LPOSC
 */
#define SYSCON_WKTCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_WKTCLKSEL_SEL_SHIFT)) & SYSCON_WKTCLKSEL_SEL_MASK)
/*! @} */

/*! @name EXTCLKSEL - external clock source select register */
/*! @{ */

#define SYSCON_EXTCLKSEL_SEL_MASK                (0x1U)
#define SYSCON_EXTCLKSEL_SEL_SHIFT               (0U)
/*! SEL - Clock source for external clock
 *  0b0..System oscillator
 *  0b1..Clk_in
 */
#define SYSCON_EXTCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_EXTCLKSEL_SEL_SHIFT)) & SYSCON_EXTCLKSEL_SEL_MASK)
/*! @} */

/*! @name I3CCLKDIV - I3C clock divider register */
/*! @{ */

#define SYSCON_I3CCLKDIV_I3C_FCLK_DIV_MASK       (0xFFU)
#define SYSCON_I3CCLKDIV_I3C_FCLK_DIV_SHIFT      (0U)
/*! I3C_FCLK_DIV - i3c_fclk fast clock divider */
#define SYSCON_I3CCLKDIV_I3C_FCLK_DIV(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_I3CCLKDIV_I3C_FCLK_DIV_SHIFT)) & SYSCON_I3CCLKDIV_I3C_FCLK_DIV_MASK)

#define SYSCON_I3CCLKDIV_I3C_SLOW_TC_CLK_DIV_MASK (0xFF00U)
#define SYSCON_I3CCLKDIV_I3C_SLOW_TC_CLK_DIV_SHIFT (8U)
/*! I3C_SLOW_TC_CLK_DIV - i3c_slow_tc_clk clock divider */
#define SYSCON_I3CCLKDIV_I3C_SLOW_TC_CLK_DIV(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_I3CCLKDIV_I3C_SLOW_TC_CLK_DIV_SHIFT)) & SYSCON_I3CCLKDIV_I3C_SLOW_TC_CLK_DIV_MASK)

#define SYSCON_I3CCLKDIV_I3C_SLOW_CLK_DIV_MASK   (0xFF0000U)
#define SYSCON_I3CCLKDIV_I3C_SLOW_CLK_DIV_SHIFT  (16U)
/*! I3C_SLOW_CLK_DIV - i3c_slow_clk divider */
#define SYSCON_I3CCLKDIV_I3C_SLOW_CLK_DIV(x)     (((uint32_t)(((uint32_t)(x)) << SYSCON_I3CCLKDIV_I3C_SLOW_CLK_DIV_SHIFT)) & SYSCON_I3CCLKDIV_I3C_SLOW_CLK_DIV_MASK)
/*! @} */

/*! @name LPOSCEN - LPOSC enable register */
/*! @{ */

#define SYSCON_LPOSCEN_WDT_CLK_EN_MASK           (0x1U)
#define SYSCON_LPOSCEN_WDT_CLK_EN_SHIFT          (0U)
/*! WDT_CLK_EN - WDT count clock enable
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_LPOSCEN_WDT_CLK_EN(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCEN_WDT_CLK_EN_SHIFT)) & SYSCON_LPOSCEN_WDT_CLK_EN_MASK)

#define SYSCON_LPOSCEN_WKT_CLK_EN_MASK           (0x2U)
#define SYSCON_LPOSCEN_WKT_CLK_EN_SHIFT          (1U)
/*! WKT_CLK_EN - WDT count clock enable
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_LPOSCEN_WKT_CLK_EN(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_LPOSCEN_WKT_CLK_EN_SHIFT)) & SYSCON_LPOSCEN_WKT_CLK_EN_MASK)
/*! @} */

/*! @name SYSAHBCLKCTRL0 - System clock group 0 control register */
/*! @{ */

#define SYSCON_SYSAHBCLKCTRL0_SYS_MASK           (0x1U)
#define SYSCON_SYSAHBCLKCTRL0_SYS_SHIFT          (0U)
/*! SYS - Enables the clock for the AHB, the APB bridge, the Cortex-M0+ core clocks, SYSCON, and the
 *    PMU. This bit is read only and always reads as 1.
 */
#define SYSCON_SYSAHBCLKCTRL0_SYS(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_SYS_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_SYS_MASK)

#define SYSCON_SYSAHBCLKCTRL0_ROM_MASK           (0x2U)
#define SYSCON_SYSAHBCLKCTRL0_ROM_SHIFT          (1U)
/*! ROM - Enables clock for ROM.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_ROM(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_ROM_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_ROM_MASK)

#define SYSCON_SYSAHBCLKCTRL0_RAM_MASK           (0x4U)
#define SYSCON_SYSAHBCLKCTRL0_RAM_SHIFT          (2U)
/*! RAM - Enables clock for SRAM.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_RAM(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_RAM_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_RAM_MASK)

#define SYSCON_SYSAHBCLKCTRL0_FLASH_MASK         (0x10U)
#define SYSCON_SYSAHBCLKCTRL0_FLASH_SHIFT        (4U)
/*! FLASH - Enables clock for flash.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_FLASH(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_FLASH_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_FLASH_MASK)

#define SYSCON_SYSAHBCLKCTRL0_I2C0_MASK          (0x20U)
#define SYSCON_SYSAHBCLKCTRL0_I2C0_SHIFT         (5U)
/*! I2C0 - Enables clock for I2C0.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_I2C0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_I2C0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_I2C0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK         (0x40U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT        (6U)
/*! GPIO0 - Enables clock for GPIO0 port registers.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_GPIO0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_SWM_MASK           (0x80U)
#define SYSCON_SYSAHBCLKCTRL0_SWM_SHIFT          (7U)
/*! SWM - Enables clock for switch matrix.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_SWM(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_SWM_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_SWM_MASK)

#define SYSCON_SYSAHBCLKCTRL0_WKT_MASK           (0x200U)
#define SYSCON_SYSAHBCLKCTRL0_WKT_SHIFT          (9U)
/*! WKT - Enables clock for self-wake-up timer.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_WKT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_WKT_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_WKT_MASK)

#define SYSCON_SYSAHBCLKCTRL0_MRT_MASK           (0x400U)
#define SYSCON_SYSAHBCLKCTRL0_MRT_SHIFT          (10U)
/*! MRT - Enables clock for multi-rate timer.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_MRT(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_MRT_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_MRT_MASK)

#define SYSCON_SYSAHBCLKCTRL0_SPI0_MASK          (0x800U)
#define SYSCON_SYSAHBCLKCTRL0_SPI0_SHIFT         (11U)
/*! SPI0 - Enables clock for SPI0.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_SPI0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_SPI0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_SPI0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_SPI1_MASK          (0x1000U)
#define SYSCON_SYSAHBCLKCTRL0_SPI1_SHIFT         (12U)
/*! SPI1 - Enables clock for SPI1.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_SPI1(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_SPI1_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_SPI1_MASK)

#define SYSCON_SYSAHBCLKCTRL0_CRC_MASK           (0x2000U)
#define SYSCON_SYSAHBCLKCTRL0_CRC_SHIFT          (13U)
/*! CRC - Enables clock for CRC.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_CRC(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_CRC_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_CRC_MASK)

#define SYSCON_SYSAHBCLKCTRL0_UART0_MASK         (0x4000U)
#define SYSCON_SYSAHBCLKCTRL0_UART0_SHIFT        (14U)
/*! UART0 - Enables clock for UART0.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_UART0(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_UART0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_UART0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_UART1_MASK         (0x8000U)
#define SYSCON_SYSAHBCLKCTRL0_UART1_SHIFT        (15U)
/*! UART1 - Enables clock for UART1.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_UART1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_UART1_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_UART1_MASK)

#define SYSCON_SYSAHBCLKCTRL0_UART2_MASK         (0x10000U)
#define SYSCON_SYSAHBCLKCTRL0_UART2_SHIFT        (16U)
/*! UART2 - Enables clock for UART2.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_UART2(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_UART2_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_UART2_MASK)

#define SYSCON_SYSAHBCLKCTRL0_WWDT_MASK          (0x20000U)
#define SYSCON_SYSAHBCLKCTRL0_WWDT_SHIFT         (17U)
/*! WWDT - Enables clock for WWDT.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_WWDT(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_WWDT_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_WWDT_MASK)

#define SYSCON_SYSAHBCLKCTRL0_IOCON_MASK         (0x40000U)
#define SYSCON_SYSAHBCLKCTRL0_IOCON_SHIFT        (18U)
/*! IOCON - Enables clock for IOCON.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_IOCON(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_IOCON_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_IOCON_MASK)

#define SYSCON_SYSAHBCLKCTRL0_ACMP_MASK          (0x80000U)
#define SYSCON_SYSAHBCLKCTRL0_ACMP_SHIFT         (19U)
/*! ACMP - Enables clock for analog comparator.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_ACMP(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_ACMP_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_ACMP_MASK)

#define SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK         (0x100000U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT        (20U)
/*! GPIO1 - Enables clock for GPIO1 port registers.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_GPIO1(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK)

#define SYSCON_SYSAHBCLKCTRL0_FTM0_MASK          (0x200000U)
#define SYSCON_SYSAHBCLKCTRL0_FTM0_SHIFT         (21U)
/*! FTM0 - Enables clock for FTM0.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_FTM0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_FTM0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_FTM0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_FTM1_MASK          (0x400000U)
#define SYSCON_SYSAHBCLKCTRL0_FTM1_SHIFT         (22U)
/*! FTM1 - Enables clock for FTM1.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_FTM1(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_FTM1_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_FTM1_MASK)

#define SYSCON_SYSAHBCLKCTRL0_I3C0_MASK          (0x800000U)
#define SYSCON_SYSAHBCLKCTRL0_I3C0_SHIFT         (23U)
/*! I3C0 - Enables clock to I3C.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_I3C0(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_I3C0_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_I3C0_MASK)

#define SYSCON_SYSAHBCLKCTRL0_ADC_MASK           (0x1000000U)
#define SYSCON_SYSAHBCLKCTRL0_ADC_SHIFT          (24U)
/*! ADC - Enables clock for ADC.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_ADC(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_ADC_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_ADC_MASK)

#define SYSCON_SYSAHBCLKCTRL0_GPIO_INT_MASK      (0x10000000U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO_INT_SHIFT     (28U)
/*! GPIO_INT - Enable clock for GPIO pin interrupt registers
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_GPIO_INT(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_GPIO_INT_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_GPIO_INT_MASK)

#define SYSCON_SYSAHBCLKCTRL0_DMA_MASK           (0x20000000U)
#define SYSCON_SYSAHBCLKCTRL0_DMA_SHIFT          (29U)
/*! DMA - Enables clock for DMA.
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_SYSAHBCLKCTRL0_DMA(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSAHBCLKCTRL0_DMA_SHIFT)) & SYSCON_SYSAHBCLKCTRL0_DMA_MASK)
/*! @} */

/*! @name PRESETCTRL0 - Peripheral reset group 0 control register */
/*! @{ */

#define SYSCON_PRESETCTRL0_FLASH_RST_N_MASK      (0x10U)
#define SYSCON_PRESETCTRL0_FLASH_RST_N_SHIFT     (4U)
/*! FLASH_RST_N - flash controller reset control
 *  0b0..Assert the flash controller reset.
 *  0b1..Clear the flash controller reset.
 */
#define SYSCON_PRESETCTRL0_FLASH_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_FLASH_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_FLASH_RST_N_MASK)

#define SYSCON_PRESETCTRL0_I2C0_RST_N_MASK       (0x20U)
#define SYSCON_PRESETCTRL0_I2C0_RST_N_SHIFT      (5U)
/*! I2C0_RST_N - I2C0 reset control
 *  0b0..Assert the I2C0 reset.
 *  0b1..Clear the I2C0 reset.
 */
#define SYSCON_PRESETCTRL0_I2C0_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_I2C0_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_I2C0_RST_N_MASK)

#define SYSCON_PRESETCTRL0_GPIO0_RST_N_MASK      (0x40U)
#define SYSCON_PRESETCTRL0_GPIO0_RST_N_SHIFT     (6U)
/*! GPIO0_RST_N - GPIO0 reset control
 *  0b0..Assert the GPIO0 reset.
 *  0b1..Clear the GPIO0 reset.
 */
#define SYSCON_PRESETCTRL0_GPIO0_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GPIO0_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_GPIO0_RST_N_MASK)

#define SYSCON_PRESETCTRL0_SWM_RST_N_MASK        (0x80U)
#define SYSCON_PRESETCTRL0_SWM_RST_N_SHIFT       (7U)
/*! SWM_RST_N - SWM reset control
 *  0b0..Assert the SWM reset.
 *  0b1..Clear the SWM reset.
 */
#define SYSCON_PRESETCTRL0_SWM_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_SWM_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_SWM_RST_N_MASK)

#define SYSCON_PRESETCTRL0_WKT_RST_N_MASK        (0x200U)
#define SYSCON_PRESETCTRL0_WKT_RST_N_SHIFT       (9U)
/*! WKT_RST_N - Self-wake-up timer (WKT) reset control
 *  0b0..Assert the WKT reset.
 *  0b1..Clear the WKT reset.
 */
#define SYSCON_PRESETCTRL0_WKT_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_WKT_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_WKT_RST_N_MASK)

#define SYSCON_PRESETCTRL0_MRT_RST_N_MASK        (0x400U)
#define SYSCON_PRESETCTRL0_MRT_RST_N_SHIFT       (10U)
/*! MRT_RST_N - Multi-rate timer (MRT) reset control
 *  0b0..Assert the MRT reset.
 *  0b1..Clear the MRT reset.
 */
#define SYSCON_PRESETCTRL0_MRT_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_MRT_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_MRT_RST_N_MASK)

#define SYSCON_PRESETCTRL0_SPI0_RST_N_MASK       (0x800U)
#define SYSCON_PRESETCTRL0_SPI0_RST_N_SHIFT      (11U)
/*! SPI0_RST_N - SPI0 reset control
 *  0b0..Assert the SPI0 reset.
 *  0b1..Clear the SPI0 reset.
 */
#define SYSCON_PRESETCTRL0_SPI0_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_SPI0_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_SPI0_RST_N_MASK)

#define SYSCON_PRESETCTRL0_SPI1_RST_N_MASK       (0x1000U)
#define SYSCON_PRESETCTRL0_SPI1_RST_N_SHIFT      (12U)
/*! SPI1_RST_N - SPI1 reset control
 *  0b0..Assert the SPI1 reset.
 *  0b1..Clear the SPI1 reset.
 */
#define SYSCON_PRESETCTRL0_SPI1_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_SPI1_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_SPI1_RST_N_MASK)

#define SYSCON_PRESETCTRL0_CRC_RST_N_MASK        (0x2000U)
#define SYSCON_PRESETCTRL0_CRC_RST_N_SHIFT       (13U)
/*! CRC_RST_N - CRC engine reset control
 *  0b0..Assert the CRC reset.
 *  0b1..Clear the CRC reset.
 */
#define SYSCON_PRESETCTRL0_CRC_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_CRC_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_CRC_RST_N_MASK)

#define SYSCON_PRESETCTRL0_UART0_RST_N_MASK      (0x4000U)
#define SYSCON_PRESETCTRL0_UART0_RST_N_SHIFT     (14U)
/*! UART0_RST_N - UART0 reset control
 *  0b0..Assert the UART0 reset.
 *  0b1..Clear the UART0 reset.
 */
#define SYSCON_PRESETCTRL0_UART0_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_UART0_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_UART0_RST_N_MASK)

#define SYSCON_PRESETCTRL0_UART1_RST_N_MASK      (0x8000U)
#define SYSCON_PRESETCTRL0_UART1_RST_N_SHIFT     (15U)
/*! UART1_RST_N - UART1 reset control
 *  0b0..Assert the UART1 reset.
 *  0b1..Clear the UART1 reset.
 */
#define SYSCON_PRESETCTRL0_UART1_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_UART1_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_UART1_RST_N_MASK)

#define SYSCON_PRESETCTRL0_UART2_RST_N_MASK      (0x10000U)
#define SYSCON_PRESETCTRL0_UART2_RST_N_SHIFT     (16U)
/*! UART2_RST_N - UART2 reset control
 *  0b0..Assert the UART2 reset.
 *  0b1..Clear the UART2 reset.
 */
#define SYSCON_PRESETCTRL0_UART2_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_UART2_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_UART2_RST_N_MASK)

#define SYSCON_PRESETCTRL0_IOCON_RST_N_MASK      (0x40000U)
#define SYSCON_PRESETCTRL0_IOCON_RST_N_SHIFT     (18U)
/*! IOCON_RST_N - IOCON reset control
 *  0b0..Assert the IOCON reset.
 *  0b1..Clear the IOCON reset.
 */
#define SYSCON_PRESETCTRL0_IOCON_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_IOCON_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_IOCON_RST_N_MASK)

#define SYSCON_PRESETCTRL0_ACMP_RST_N_MASK       (0x80000U)
#define SYSCON_PRESETCTRL0_ACMP_RST_N_SHIFT      (19U)
/*! ACMP_RST_N - Analog comparator reset control
 *  0b0..Assert the analog comparator reset.
 *  0b1..Clear the analog comparator reset.
 */
#define SYSCON_PRESETCTRL0_ACMP_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_ACMP_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_ACMP_RST_N_MASK)

#define SYSCON_PRESETCTRL0_GPIO1_RST_N_MASK      (0x100000U)
#define SYSCON_PRESETCTRL0_GPIO1_RST_N_SHIFT     (20U)
/*! GPIO1_RST_N - GPIO1 reset control
 *  0b0..Assert the GPIO1 reset.
 *  0b1..Clear the GPIO1 reset.
 */
#define SYSCON_PRESETCTRL0_GPIO1_RST_N(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GPIO1_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_GPIO1_RST_N_MASK)

#define SYSCON_PRESETCTRL0_FTM0_RST_N_MASK       (0x200000U)
#define SYSCON_PRESETCTRL0_FTM0_RST_N_SHIFT      (21U)
/*! FTM0_RST_N - FTM0 reset control
 *  0b0..Assert the FTM0 reset.
 *  0b1..Clear the FTM0 reset.
 */
#define SYSCON_PRESETCTRL0_FTM0_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_FTM0_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_FTM0_RST_N_MASK)

#define SYSCON_PRESETCTRL0_FTM1_RST_N_MASK       (0x400000U)
#define SYSCON_PRESETCTRL0_FTM1_RST_N_SHIFT      (22U)
/*! FTM1_RST_N - FTM1 reset control
 *  0b0..Assert the FTM1 reset.
 *  0b1..Clear the FTM1 reset.
 */
#define SYSCON_PRESETCTRL0_FTM1_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_FTM1_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_FTM1_RST_N_MASK)

#define SYSCON_PRESETCTRL0_I3C_RST_N_MASK        (0x800000U)
#define SYSCON_PRESETCTRL0_I3C_RST_N_SHIFT       (23U)
/*! I3C_RST_N - I3C reset control
 *  0b0..Assert the I3C reset.
 *  0b1..Clear the I3C reset.
 */
#define SYSCON_PRESETCTRL0_I3C_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_I3C_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_I3C_RST_N_MASK)

#define SYSCON_PRESETCTRL0_ADC_RST_N_MASK        (0x1000000U)
#define SYSCON_PRESETCTRL0_ADC_RST_N_SHIFT       (24U)
/*! ADC_RST_N - ADC reset control
 *  0b0..Assert the ADC reset.
 *  0b1..Clear the ADC reset.
 */
#define SYSCON_PRESETCTRL0_ADC_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_ADC_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_ADC_RST_N_MASK)

#define SYSCON_PRESETCTRL0_GPIOINT_RST_N_MASK    (0x10000000U)
#define SYSCON_PRESETCTRL0_GPIOINT_RST_N_SHIFT   (28U)
/*! GPIOINT_RST_N - GPIOINT reset control
 *  0b0..Assert the GPIOINT reset.
 *  0b1..Clear the GPIOINT reset.
 */
#define SYSCON_PRESETCTRL0_GPIOINT_RST_N(x)      (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_GPIOINT_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_GPIOINT_RST_N_MASK)

#define SYSCON_PRESETCTRL0_DMA_RST_N_MASK        (0x20000000U)
#define SYSCON_PRESETCTRL0_DMA_RST_N_SHIFT       (29U)
/*! DMA_RST_N - DMA reset control
 *  0b0..Assert the DMA reset.
 *  0b1..Clear the DMA reset.
 */
#define SYSCON_PRESETCTRL0_DMA_RST_N(x)          (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL0_DMA_RST_N_SHIFT)) & SYSCON_PRESETCTRL0_DMA_RST_N_MASK)
/*! @} */

/*! @name PRESETCTRL1 - Peripheral reset group 1 control register */
/*! @{ */

#define SYSCON_PRESETCTRL1_FRG0_RST_N_MASK       (0x8U)
#define SYSCON_PRESETCTRL1_FRG0_RST_N_SHIFT      (3U)
/*! FRG0_RST_N - Fractional baud rate generator 0 reset control
 *  0b0..Assert the FRG0 reset.
 *  0b1..Clear the FRG0 reset.
 */
#define SYSCON_PRESETCTRL1_FRG0_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FRG0_RST_N_SHIFT)) & SYSCON_PRESETCTRL1_FRG0_RST_N_MASK)

#define SYSCON_PRESETCTRL1_FRG1_RST_N_MASK       (0x10U)
#define SYSCON_PRESETCTRL1_FRG1_RST_N_SHIFT      (4U)
/*! FRG1_RST_N - Fractional baud rate generator 1 reset control
 *  0b0..Assert the FRG1 reset.
 *  0b1..Clear the FRG1 reset.
 */
#define SYSCON_PRESETCTRL1_FRG1_RST_N(x)         (((uint32_t)(((uint32_t)(x)) << SYSCON_PRESETCTRL1_FRG1_RST_N_SHIFT)) & SYSCON_PRESETCTRL1_FRG1_RST_N_MASK)
/*! @} */

/*! @name FCLKSEL - peripheral clock source select register. FCLK0SEL~FCLK2SEL are for UART0~UART2 clock source select register.FCLK3SEL~FCLK4SEL are reserved. FCLK5SEL is for I2C clock source select register. */
/*! @{ */

#define SYSCON_FCLKSEL_SEL_MASK                  (0x7U)
#define SYSCON_FCLKSEL_SEL_SHIFT                 (0U)
/*! SEL - Peripheral clock source
 *  0b000..FRO
 *  0b001..main clock
 *  0b010..Frg0clk
 *  0b011..Frg1clk
 *  0b100..FRO_DIV
 *  0b101..none
 *  0b110..none
 *  0b111..none
 */
#define SYSCON_FCLKSEL_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_FCLKSEL_SEL_SHIFT)) & SYSCON_FCLKSEL_SEL_MASK)
/*! @} */

/* The count of SYSCON_FCLKSEL */
#define SYSCON_FCLKSEL_COUNT                     (6U)

/*! @name I3CCLKSEL - I3C clock source select register */
/*! @{ */

#define SYSCON_I3CCLKSEL_SEL_MASK                (0x7U)
#define SYSCON_I3CCLKSEL_SEL_SHIFT               (0U)
/*! SEL - I3C clock source
 *  0b000..FRO
 *  0b001..external clock
 *  0b010..None
 *  0b011..None
 *  0b100..None
 *  0b101..None
 *  0b110..None
 *  0b111..None
 */
#define SYSCON_I3CCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_I3CCLKSEL_SEL_SHIFT)) & SYSCON_I3CCLKSEL_SEL_MASK)
/*! @} */

/*! @name I3CSLOWTCCLKSEL - I3CSLOWTC clock source select register */
/*! @{ */

#define SYSCON_I3CSLOWTCCLKSEL_SEL_MASK          (0x7U)
#define SYSCON_I3CSLOWTCCLKSEL_SEL_SHIFT         (0U)
/*! SEL - I3C clock source
 *  0b000..I3CFCLK
 *  0b001..Low power oscillator
 *  0b010..None
 *  0b011..None
 *  0b100..None
 *  0b101..None
 *  0b110..None
 *  0b111..None
 */
#define SYSCON_I3CSLOWTCCLKSEL_SEL(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_I3CSLOWTCCLKSEL_SEL_SHIFT)) & SYSCON_I3CSLOWTCCLKSEL_SEL_MASK)
/*! @} */

/*! @name FCLKSEL2 - peripheral clock source select register. FCLK0SEL2~FCLK2SEL2 are for SPI0~SPI1 clock source select register. */
/*! @{ */

#define SYSCON_FCLKSEL2_SEL_MASK                 (0x7U)
#define SYSCON_FCLKSEL2_SEL_SHIFT                (0U)
/*! SEL - Peripheral clock source
 *  0b000..FRO
 *  0b001..main clock
 *  0b010..Frg0clk
 *  0b011..Frg1clk
 *  0b100..FRO_DIV
 *  0b101..none
 *  0b110..none
 *  0b111..none
 */
#define SYSCON_FCLKSEL2_SEL(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_FCLKSEL2_SEL_SHIFT)) & SYSCON_FCLKSEL2_SEL_MASK)
/*! @} */

/* The count of SYSCON_FCLKSEL2 */
#define SYSCON_FCLKSEL2_COUNT                    (2U)

/*! @name FTM0INTTRIGDIV - FTM0INTTRIGDIV register */
/*! @{ */

#define SYSCON_FTM0INTTRIGDIV_FTM0_INT_TRIG_DIV_MASK (0x7FU)
#define SYSCON_FTM0INTTRIGDIV_FTM0_INT_TRIG_DIV_SHIFT (0U)
/*! FTM0_INT_TRIG_DIV - ftm0 ext_trigger_ftm0 or init_trigger_ftm0 divided by 1~128 */
#define SYSCON_FTM0INTTRIGDIV_FTM0_INT_TRIG_DIV(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FTM0INTTRIGDIV_FTM0_INT_TRIG_DIV_SHIFT)) & SYSCON_FTM0INTTRIGDIV_FTM0_INT_TRIG_DIV_MASK)
/*! @} */

/*! @name FTMFLTCFG - System clock divider register */
/*! @{ */

#define SYSCON_FTMFLTCFG_FTM0_FAULT0_MUX_SEL_MASK (0x1U)
#define SYSCON_FTMFLTCFG_FTM0_FAULT0_MUX_SEL_SHIFT (0U)
/*! FTM0_FAULT0_MUX_SEL - Mux selection FTM0 fault from external I/O or internal.
 *  0b0..Select external I/O
 *  0b1..Select internal
 */
#define SYSCON_FTMFLTCFG_FTM0_FAULT0_MUX_SEL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_FTMFLTCFG_FTM0_FAULT0_MUX_SEL_SHIFT)) & SYSCON_FTMFLTCFG_FTM0_FAULT0_MUX_SEL_MASK)

#define SYSCON_FTMFLTCFG_FTM0_FAULT1_MUX_SEL_MASK (0x2U)
#define SYSCON_FTMFLTCFG_FTM0_FAULT1_MUX_SEL_SHIFT (1U)
/*! FTM0_FAULT1_MUX_SEL - Mux selection FTM0 fault from external I/O or internal.
 *  0b0..Select external I/O
 *  0b1..Select internal
 */
#define SYSCON_FTMFLTCFG_FTM0_FAULT1_MUX_SEL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_FTMFLTCFG_FTM0_FAULT1_MUX_SEL_SHIFT)) & SYSCON_FTMFLTCFG_FTM0_FAULT1_MUX_SEL_MASK)

#define SYSCON_FTMFLTCFG_FTM0_FAULT2_MUX_SEL_MASK (0x4U)
#define SYSCON_FTMFLTCFG_FTM0_FAULT2_MUX_SEL_SHIFT (2U)
/*! FTM0_FAULT2_MUX_SEL - Mux selection FTM0 fault from external I/O or internal.
 *  0b0..Select external I/O
 *  0b1..Select internal
 */
#define SYSCON_FTMFLTCFG_FTM0_FAULT2_MUX_SEL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_FTMFLTCFG_FTM0_FAULT2_MUX_SEL_SHIFT)) & SYSCON_FTMFLTCFG_FTM0_FAULT2_MUX_SEL_MASK)

#define SYSCON_FTMFLTCFG_FTM0_FAULT3_MUX_SEL_MASK (0x8U)
#define SYSCON_FTMFLTCFG_FTM0_FAULT3_MUX_SEL_SHIFT (3U)
/*! FTM0_FAULT3_MUX_SEL - Mux selection FTM0 fault from external I/O or internal.
 *  0b0..Select external I/O
 *  0b1..Select internal
 */
#define SYSCON_FTMFLTCFG_FTM0_FAULT3_MUX_SEL(x)  (((uint32_t)(((uint32_t)(x)) << SYSCON_FTMFLTCFG_FTM0_FAULT3_MUX_SEL_SHIFT)) & SYSCON_FTMFLTCFG_FTM0_FAULT3_MUX_SEL_MASK)

#define SYSCON_FTMFLTCFG_FTM0_SW_FAULT_MASK      (0x10U)
#define SYSCON_FTMFLTCFG_FTM0_SW_FAULT_SHIFT     (4U)
/*! FTM0_SW_FAULT - Software fault. */
#define SYSCON_FTMFLTCFG_FTM0_SW_FAULT(x)        (((uint32_t)(((uint32_t)(x)) << SYSCON_FTMFLTCFG_FTM0_SW_FAULT_SHIFT)) & SYSCON_FTMFLTCFG_FTM0_SW_FAULT_MASK)
/*! @} */

/*! @name FRG_FRGDIV - fractional generator N divider value register */
/*! @{ */

#define SYSCON_FRG_FRGDIV_DIV_MASK               (0xFFU)
#define SYSCON_FRG_FRGDIV_DIV_SHIFT              (0U)
/*! DIV - Denominator of the fractional divider. DIV is equal to the programmed value +1. Always set
 *    to 0xFF to use with the fractional baud rate generator.
 */
#define SYSCON_FRG_FRGDIV_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_FRG_FRGDIV_DIV_SHIFT)) & SYSCON_FRG_FRGDIV_DIV_MASK)
/*! @} */

/* The count of SYSCON_FRG_FRGDIV */
#define SYSCON_FRG_FRGDIV_COUNT                  (2U)

/*! @name FRG_FRGMULT - fractional generator N multiplier value register */
/*! @{ */

#define SYSCON_FRG_FRGMULT_MULT_MASK             (0xFFU)
#define SYSCON_FRG_FRGMULT_MULT_SHIFT            (0U)
/*! MULT - Numerator of the fractional divider. MULT is equal to the programmed value. */
#define SYSCON_FRG_FRGMULT_MULT(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_FRG_FRGMULT_MULT_SHIFT)) & SYSCON_FRG_FRGMULT_MULT_MASK)
/*! @} */

/* The count of SYSCON_FRG_FRGMULT */
#define SYSCON_FRG_FRGMULT_COUNT                 (2U)

/*! @name FRG_FRGCLKSEL - FRG N clock source select register */
/*! @{ */

#define SYSCON_FRG_FRGCLKSEL_SEL_MASK            (0x3U)
#define SYSCON_FRG_FRGCLKSEL_SEL_SHIFT           (0U)
/*! SEL - Clock source for frgN_src clock
 *  0b00..FRO
 *  0b01..main clock
 *  0b10..sys pll
 *  0b11..None
 */
#define SYSCON_FRG_FRGCLKSEL_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_FRG_FRGCLKSEL_SEL_SHIFT)) & SYSCON_FRG_FRGCLKSEL_SEL_MASK)
/*! @} */

/* The count of SYSCON_FRG_FRGCLKSEL */
#define SYSCON_FRG_FRGCLKSEL_COUNT               (2U)

/*! @name CLKOUTSEL - CLKOUT clock source select register */
/*! @{ */

#define SYSCON_CLKOUTSEL_SEL_MASK                (0x7U)
#define SYSCON_CLKOUTSEL_SEL_SHIFT               (0U)
/*! SEL - CLKOUT clock source
 *  0b000..FRO
 *  0b001..main clock
 *  0b010..sys pll
 *  0b011..external clock
 *  0b100..Low power oscillator
 *  0b101..None
 *  0b110..None
 *  0b111..None
 */
#define SYSCON_CLKOUTSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTSEL_SEL_SHIFT)) & SYSCON_CLKOUTSEL_SEL_MASK)
/*! @} */

/*! @name CLKOUTDIV - CLKOUT clock divider registers */
/*! @{ */

#define SYSCON_CLKOUTDIV_DIV_MASK                (0xFFU)
#define SYSCON_CLKOUTDIV_DIV_SHIFT               (0U)
/*! DIV - CLKOUT clock divider values 0: Disable CLKOUT clock divider. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_CLKOUTDIV_DIV(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_CLKOUTDIV_DIV_SHIFT)) & SYSCON_CLKOUTDIV_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV6 - Peripheral clock 6 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV6_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV6_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV6_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV6_DIV_SHIFT)) & SYSCON_IOCONCLKDIV6_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV5 - Peripheral clock 6 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV5_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV5_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV5_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV5_DIV_SHIFT)) & SYSCON_IOCONCLKDIV5_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV4 - Peripheral clock 4 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV4_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV4_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV4_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV4_DIV_SHIFT)) & SYSCON_IOCONCLKDIV4_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV3 - Peripheral clock 3 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV3_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV3_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV3_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV3_DIV_SHIFT)) & SYSCON_IOCONCLKDIV3_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV2 - Peripheral clock 2 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV2_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV2_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV2_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV2_DIV_SHIFT)) & SYSCON_IOCONCLKDIV2_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV1 - Peripheral clock 1 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV1_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV1_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV1_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV1_DIV_SHIFT)) & SYSCON_IOCONCLKDIV1_DIV_MASK)
/*! @} */

/*! @name IOCONCLKDIV0 - Peripheral clock 0 to the IOCON block for programmable glitch filter */
/*! @{ */

#define SYSCON_IOCONCLKDIV0_DIV_MASK             (0xFFU)
#define SYSCON_IOCONCLKDIV0_DIV_SHIFT            (0U)
/*! DIV - IOCON glitch filter clock divider values 0: Disable IOCONFILTR_PCLK. 1: Divide by 1. to 255: Divide by 255. */
#define SYSCON_IOCONCLKDIV0_DIV(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_IOCONCLKDIV0_DIV_SHIFT)) & SYSCON_IOCONCLKDIV0_DIV_MASK)
/*! @} */

/*! @name BODCTRL - BOD control register */
/*! @{ */

#define SYSCON_BODCTRL_BODRSTLEV_MASK            (0x3U)
#define SYSCON_BODCTRL_BODRSTLEV_SHIFT           (0U)
/*! BODRSTLEV - BOD reset level
 *  0b00..Reserved
 *  0b01..Level 1
 *  0b10..Level 2
 *  0b11..Level 3
 */
#define SYSCON_BODCTRL_BODRSTLEV(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTLEV_SHIFT)) & SYSCON_BODCTRL_BODRSTLEV_MASK)

#define SYSCON_BODCTRL_BODINTVAL_MASK            (0xCU)
#define SYSCON_BODCTRL_BODINTVAL_SHIFT           (2U)
/*! BODINTVAL - BOD interrupt level
 *  0b00..Reserved
 *  0b01..Level 1
 *  0b10..Level 2
 *  0b11..Level 3
 */
#define SYSCON_BODCTRL_BODINTVAL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODINTVAL_SHIFT)) & SYSCON_BODCTRL_BODINTVAL_MASK)

#define SYSCON_BODCTRL_BODRSTENA_MASK            (0x10U)
#define SYSCON_BODCTRL_BODRSTENA_SHIFT           (4U)
/*! BODRSTENA - BOD reset enable
 *  0b0..Disable reset function.
 *  0b1..Enable reset function.
 */
#define SYSCON_BODCTRL_BODRSTENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_BODCTRL_BODRSTENA_SHIFT)) & SYSCON_BODCTRL_BODRSTENA_MASK)
/*! @} */

/*! @name SYSTCKCAL - System tick timer calibration register */
/*! @{ */

#define SYSCON_SYSTCKCAL_CAL_MASK                (0x3FFFFFFU)
#define SYSCON_SYSTCKCAL_CAL_SHIFT               (0U)
/*! CAL - System tick timer calibration value. */
#define SYSCON_SYSTCKCAL_CAL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_SYSTCKCAL_CAL_SHIFT)) & SYSCON_SYSTCKCAL_CAL_MASK)
/*! @} */

/*! @name IRQLATENCY - IRQ latency register */
/*! @{ */

#define SYSCON_IRQLATENCY_LATENCY_MASK           (0xFFU)
#define SYSCON_IRQLATENCY_LATENCY_SHIFT          (0U)
/*! LATENCY - 8-bit latency value. */
#define SYSCON_IRQLATENCY_LATENCY(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_IRQLATENCY_LATENCY_SHIFT)) & SYSCON_IRQLATENCY_LATENCY_MASK)
/*! @} */

/*! @name NMISRC - NMI source selection register */
/*! @{ */

#define SYSCON_NMISRC_IRQN_MASK                  (0x1FU)
#define SYSCON_NMISRC_IRQN_SHIFT                 (0U)
/*! IRQN - The IRQ number of the interrupt that acts as the Non-Maskable Interrupt (NMI) if bit 31 is 1 */
#define SYSCON_NMISRC_IRQN(x)                    (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_IRQN_SHIFT)) & SYSCON_NMISRC_IRQN_MASK)

#define SYSCON_NMISRC_NMIEN_MASK                 (0x80000000U)
#define SYSCON_NMISRC_NMIEN_SHIFT                (31U)
/*! NMIEN - Write a 1 to this bit to enable the Non-Maskable Interrupt (NMI) source selected by bits 4:0. */
#define SYSCON_NMISRC_NMIEN(x)                   (((uint32_t)(((uint32_t)(x)) << SYSCON_NMISRC_NMIEN_SHIFT)) & SYSCON_NMISRC_NMIEN_MASK)
/*! @} */

/*! @name PINTSEL - Pin interrupt select registers N */
/*! @{ */

#define SYSCON_PINTSEL_INTPIN_MASK               (0x3FU)
#define SYSCON_PINTSEL_INTPIN_SHIFT              (0U)
/*! INTPIN - Pin number select for pin interrupt or pattern match engine input. (PIO0_0 to
 *    PIO0_31correspond to numbers 0 to 31 and PIO1_0 to PIO1_31 correspond to numbers 32 to 63).
 */
#define SYSCON_PINTSEL_INTPIN(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_PINTSEL_INTPIN_SHIFT)) & SYSCON_PINTSEL_INTPIN_MASK)
/*! @} */

/* The count of SYSCON_PINTSEL */
#define SYSCON_PINTSEL_COUNT                     (8U)

/*! @name STARTERP0 - Start logic 0 pin wake-up enable register 0 */
/*! @{ */

#define SYSCON_STARTERP0_PINT0_MASK              (0x1U)
#define SYSCON_STARTERP0_PINT0_SHIFT             (0U)
/*! PINT0 - GPIO pin interrupt 0 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT0(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT0_SHIFT)) & SYSCON_STARTERP0_PINT0_MASK)

#define SYSCON_STARTERP0_PINT1_MASK              (0x2U)
#define SYSCON_STARTERP0_PINT1_SHIFT             (1U)
/*! PINT1 - GPIO pin interrupt 1 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT1(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT1_SHIFT)) & SYSCON_STARTERP0_PINT1_MASK)

#define SYSCON_STARTERP0_PINT2_MASK              (0x4U)
#define SYSCON_STARTERP0_PINT2_SHIFT             (2U)
/*! PINT2 - GPIO pin interrupt 2 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT2(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT2_SHIFT)) & SYSCON_STARTERP0_PINT2_MASK)

#define SYSCON_STARTERP0_PINT3_MASK              (0x8U)
#define SYSCON_STARTERP0_PINT3_SHIFT             (3U)
/*! PINT3 - GPIO pin interrupt 3 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT3(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT3_SHIFT)) & SYSCON_STARTERP0_PINT3_MASK)

#define SYSCON_STARTERP0_PINT4_MASK              (0x10U)
#define SYSCON_STARTERP0_PINT4_SHIFT             (4U)
/*! PINT4 - GPIO pin interrupt 4 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT4(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT4_SHIFT)) & SYSCON_STARTERP0_PINT4_MASK)

#define SYSCON_STARTERP0_PINT5_MASK              (0x20U)
#define SYSCON_STARTERP0_PINT5_SHIFT             (5U)
/*! PINT5 - GPIO pin interrupt 5 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT5(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT5_SHIFT)) & SYSCON_STARTERP0_PINT5_MASK)

#define SYSCON_STARTERP0_PINT6_MASK              (0x40U)
#define SYSCON_STARTERP0_PINT6_SHIFT             (6U)
/*! PINT6 - GPIO pin interrupt 6 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT6(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT6_SHIFT)) & SYSCON_STARTERP0_PINT6_MASK)

#define SYSCON_STARTERP0_PINT7_MASK              (0x80U)
#define SYSCON_STARTERP0_PINT7_SHIFT             (7U)
/*! PINT7 - GPIO pin interrupt 7 wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP0_PINT7(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP0_PINT7_SHIFT)) & SYSCON_STARTERP0_PINT7_MASK)
/*! @} */

/*! @name STARTERP1 - Start logic 0 pin wake-up enable register 1 */
/*! @{ */

#define SYSCON_STARTERP1_SPI0_MASK               (0x1U)
#define SYSCON_STARTERP1_SPI0_SHIFT              (0U)
/*! SPI0 - SPI0 interrupt wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_SPI0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_SPI0_SHIFT)) & SYSCON_STARTERP1_SPI0_MASK)

#define SYSCON_STARTERP1_SPI1_MASK               (0x2U)
#define SYSCON_STARTERP1_SPI1_SHIFT              (1U)
/*! SPI1 - SPI1 interrupt wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_SPI1(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_SPI1_SHIFT)) & SYSCON_STARTERP1_SPI1_MASK)

#define SYSCON_STARTERP1_USART0_MASK             (0x8U)
#define SYSCON_STARTERP1_USART0_SHIFT            (3U)
/*! USART0 - USART0 interrupt wake-up. Configure USART in synchronous slave mode.
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_USART0(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_USART0_SHIFT)) & SYSCON_STARTERP1_USART0_MASK)

#define SYSCON_STARTERP1_USART1_MASK             (0x10U)
#define SYSCON_STARTERP1_USART1_SHIFT            (4U)
/*! USART1 - USART1 interrupt wake-up. Configure USART in synchronous slave mode.
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_USART1(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_USART1_SHIFT)) & SYSCON_STARTERP1_USART1_MASK)

#define SYSCON_STARTERP1_USART2_MASK             (0x20U)
#define SYSCON_STARTERP1_USART2_SHIFT            (5U)
/*! USART2 - USART2 interrupt wake-up. Configure USART in synchronous slave mode.
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_USART2(x)               (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_USART2_SHIFT)) & SYSCON_STARTERP1_USART2_MASK)

#define SYSCON_STARTERP1_I2C0_MASK               (0x100U)
#define SYSCON_STARTERP1_I2C0_SHIFT              (8U)
/*! I2C0 - I2C0 interrupt wake-up.
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_I2C0(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_I2C0_SHIFT)) & SYSCON_STARTERP1_I2C0_MASK)

#define SYSCON_STARTERP1_WWDT_MASK               (0x1000U)
#define SYSCON_STARTERP1_WWDT_SHIFT              (12U)
/*! WWDT - WWDT interrupt wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_WWDT(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_WWDT_SHIFT)) & SYSCON_STARTERP1_WWDT_MASK)

#define SYSCON_STARTERP1_BOD_MASK                (0x2000U)
#define SYSCON_STARTERP1_BOD_SHIFT               (13U)
/*! BOD - BOD interrupt wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_BOD(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_BOD_SHIFT)) & SYSCON_STARTERP1_BOD_MASK)

#define SYSCON_STARTERP1_WKT_MASK                (0x8000U)
#define SYSCON_STARTERP1_WKT_SHIFT               (15U)
/*! WKT - Self-wake-up timer interrupt wake-up
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_STARTERP1_WKT(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_STARTERP1_WKT_SHIFT)) & SYSCON_STARTERP1_WKT_MASK)
/*! @} */

/*! @name PDSLEEPCFG - Deep-sleep configuration register */
/*! @{ */

#define SYSCON_PDSLEEPCFG_BOD_PD_MASK            (0x8U)
#define SYSCON_PDSLEEPCFG_BOD_PD_SHIFT           (3U)
/*! BOD_PD - BOD power-down control for Deep-sleep and Power-down mode
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDSLEEPCFG_BOD_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_BOD_PD_SHIFT)) & SYSCON_PDSLEEPCFG_BOD_PD_MASK)

#define SYSCON_PDSLEEPCFG_LPOSC_PD_MASK          (0x40U)
#define SYSCON_PDSLEEPCFG_LPOSC_PD_SHIFT         (6U)
/*! LPOSC_PD - Low power oscillator power-down control for Deep-sleep and Power-down mode. Changing
 *    this bit to powered-down has no effect when the LOCK bit in the WWDT MOD register is set. In
 *    this case, the Low power oscillator is always running.
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDSLEEPCFG_LPOSC_PD(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDSLEEPCFG_LPOSC_PD_SHIFT)) & SYSCON_PDSLEEPCFG_LPOSC_PD_MASK)
/*! @} */

/*! @name PDAWAKECFG - Wake-up configuration register */
/*! @{ */

#define SYSCON_PDAWAKECFG_FROOUT_PD_MASK         (0x1U)
#define SYSCON_PDAWAKECFG_FROOUT_PD_SHIFT        (0U)
/*! FROOUT_PD - FRO oscillator output wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_FROOUT_PD(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_FROOUT_PD_SHIFT)) & SYSCON_PDAWAKECFG_FROOUT_PD_MASK)

#define SYSCON_PDAWAKECFG_FRO_PD_MASK            (0x2U)
#define SYSCON_PDAWAKECFG_FRO_PD_SHIFT           (1U)
/*! FRO_PD - FRO oscillator power-down wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_FRO_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_FRO_PD_SHIFT)) & SYSCON_PDAWAKECFG_FRO_PD_MASK)

#define SYSCON_PDAWAKECFG_FLASH_PD_MASK          (0x4U)
#define SYSCON_PDAWAKECFG_FLASH_PD_SHIFT         (2U)
/*! FLASH_PD - Flash wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_FLASH_PD(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_FLASH_PD_SHIFT)) & SYSCON_PDAWAKECFG_FLASH_PD_MASK)

#define SYSCON_PDAWAKECFG_BOD_PD_MASK            (0x8U)
#define SYSCON_PDAWAKECFG_BOD_PD_SHIFT           (3U)
/*! BOD_PD - BOD wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_BOD_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_BOD_PD_SHIFT)) & SYSCON_PDAWAKECFG_BOD_PD_MASK)

#define SYSCON_PDAWAKECFG_ADC_PD_MASK            (0x10U)
#define SYSCON_PDAWAKECFG_ADC_PD_SHIFT           (4U)
/*! ADC_PD - ADC wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_ADC_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_ADC_PD_SHIFT)) & SYSCON_PDAWAKECFG_ADC_PD_MASK)

#define SYSCON_PDAWAKECFG_SYSOSC_PD_MASK         (0x20U)
#define SYSCON_PDAWAKECFG_SYSOSC_PD_SHIFT        (5U)
/*! SYSOSC_PD - Crystal oscillator wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDAWAKECFG_SYSOSC_PD(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_SYSOSC_PD_SHIFT)) & SYSCON_PDAWAKECFG_SYSOSC_PD_MASK)

#define SYSCON_PDAWAKECFG_LPOSC_PD_MASK          (0x40U)
#define SYSCON_PDAWAKECFG_LPOSC_PD_SHIFT         (6U)
/*! LPOSC_PD - Low power oscillator wake-up configuration. Changing this bit to powered-down has no
 *    effect when the LOCK bit in the WWDT MOD register is set. In this case, the Low power
 *    oscillator is always running
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDAWAKECFG_LPOSC_PD(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_LPOSC_PD_SHIFT)) & SYSCON_PDAWAKECFG_LPOSC_PD_MASK)

#define SYSCON_PDAWAKECFG_SYSPLL_PD_MASK         (0x80U)
#define SYSCON_PDAWAKECFG_SYSPLL_PD_SHIFT        (7U)
/*! SYSPLL_PD - System PLL wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDAWAKECFG_SYSPLL_PD(x)           (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_SYSPLL_PD_SHIFT)) & SYSCON_PDAWAKECFG_SYSPLL_PD_MASK)

#define SYSCON_PDAWAKECFG_ACMP_MASK              (0x8000U)
#define SYSCON_PDAWAKECFG_ACMP_SHIFT             (15U)
/*! ACMP - Analog comparator wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDAWAKECFG_ACMP(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDAWAKECFG_ACMP_SHIFT)) & SYSCON_PDAWAKECFG_ACMP_MASK)
/*! @} */

/*! @name PDRUNCFG - Power configuration register */
/*! @{ */

#define SYSCON_PDRUNCFG_FROOUT_PD_MASK           (0x1U)
#define SYSCON_PDRUNCFG_FROOUT_PD_SHIFT          (0U)
/*! FROOUT_PD - FRO oscillator output wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FROOUT_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FROOUT_PD_SHIFT)) & SYSCON_PDRUNCFG_FROOUT_PD_MASK)

#define SYSCON_PDRUNCFG_FRO_PD_MASK              (0x2U)
#define SYSCON_PDRUNCFG_FRO_PD_SHIFT             (1U)
/*! FRO_PD - FRO oscillator power-down wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FRO_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FRO_PD_SHIFT)) & SYSCON_PDRUNCFG_FRO_PD_MASK)

#define SYSCON_PDRUNCFG_FLASH_PD_MASK            (0x4U)
#define SYSCON_PDRUNCFG_FLASH_PD_SHIFT           (2U)
/*! FLASH_PD - Flash wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FLASH_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FLASH_PD_SHIFT)) & SYSCON_PDRUNCFG_FLASH_PD_MASK)

#define SYSCON_PDRUNCFG_BOD_PD_MASK              (0x8U)
#define SYSCON_PDRUNCFG_BOD_PD_SHIFT             (3U)
/*! BOD_PD - BOD wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_BOD_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_BOD_PD_SHIFT)) & SYSCON_PDRUNCFG_BOD_PD_MASK)

#define SYSCON_PDRUNCFG_ADC_PD_MASK              (0x10U)
#define SYSCON_PDRUNCFG_ADC_PD_SHIFT             (4U)
/*! ADC_PD - ADC wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_ADC_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_ADC_PD_SHIFT)) & SYSCON_PDRUNCFG_ADC_PD_MASK)

#define SYSCON_PDRUNCFG_SYSOSC_PD_MASK           (0x20U)
#define SYSCON_PDRUNCFG_SYSOSC_PD_SHIFT          (5U)
/*! SYSOSC_PD - Crystal oscillator wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_SYSOSC_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_SYSOSC_PD_SHIFT)) & SYSCON_PDRUNCFG_SYSOSC_PD_MASK)

#define SYSCON_PDRUNCFG_LPOSC_PD_MASK            (0x40U)
#define SYSCON_PDRUNCFG_LPOSC_PD_SHIFT           (6U)
/*! LPOSC_PD - Low power oscillator wake-up configuration. Changing this bit to powered-down has no
 *    effect when the LOCK bit in the WWDT MOD register is set. In this case, the Low power
 *    oscillator is always running
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_LPOSC_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_LPOSC_PD_SHIFT)) & SYSCON_PDRUNCFG_LPOSC_PD_MASK)

#define SYSCON_PDRUNCFG_SYSPLL_PD_MASK           (0x80U)
#define SYSCON_PDRUNCFG_SYSPLL_PD_SHIFT          (7U)
/*! SYSPLL_PD - System PLL wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_SYSPLL_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_SYSPLL_PD_SHIFT)) & SYSCON_PDRUNCFG_SYSPLL_PD_MASK)

#define SYSCON_PDRUNCFG_ACMP_MASK                (0x8000U)
#define SYSCON_PDRUNCFG_ACMP_SHIFT               (15U)
/*! ACMP - Analog comparator wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_ACMP(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_ACMP_SHIFT)) & SYSCON_PDRUNCFG_ACMP_MASK)
/*! @} */

/*! @name FLASHCACHECFG - Flash cache configuration register */
/*! @{ */

#define SYSCON_FLASHCACHECFG_FLASH_CACHE_ENABLE_MASK (0x1U)
#define SYSCON_FLASHCACHECFG_FLASH_CACHE_ENABLE_SHIFT (0U)
/*! FLASH_CACHE_ENABLE - Flash cache enable
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_FLASHCACHECFG_FLASH_CACHE_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCACHECFG_FLASH_CACHE_ENABLE_SHIFT)) & SYSCON_FLASHCACHECFG_FLASH_CACHE_ENABLE_MASK)

#define SYSCON_FLASHCACHECFG_FLASH_BUFFER_ENABLE_MASK (0x2U)
#define SYSCON_FLASHCACHECFG_FLASH_BUFFER_ENABLE_SHIFT (1U)
/*! FLASH_BUFFER_ENABLE - Flash buffer enable
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_FLASHCACHECFG_FLASH_BUFFER_ENABLE(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCACHECFG_FLASH_BUFFER_ENABLE_SHIFT)) & SYSCON_FLASHCACHECFG_FLASH_BUFFER_ENABLE_MASK)

#define SYSCON_FLASHCACHECFG_FLASH_CACHE_INVALID_MASK (0x4U)
#define SYSCON_FLASHCACHECFG_FLASH_CACHE_INVALID_SHIFT (2U)
/*! FLASH_CACHE_INVALID - Flash cache invalid
 *  0b0..disable
 *  0b1..enable
 */
#define SYSCON_FLASHCACHECFG_FLASH_CACHE_INVALID(x) (((uint32_t)(((uint32_t)(x)) << SYSCON_FLASHCACHECFG_FLASH_CACHE_INVALID_SHIFT)) & SYSCON_FLASHCACHECFG_FLASH_CACHE_INVALID_MASK)
/*! @} */

/*! @name DEVICE_ID - Part ID register */
/*! @{ */

#define SYSCON_DEVICE_ID_DEVICEID_MASK           (0xFFFFFFFFU)
#define SYSCON_DEVICE_ID_DEVICEID_SHIFT          (0U)
/*! DEVICEID - Part ID */
#define SYSCON_DEVICE_ID_DEVICEID(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_DEVICE_ID_DEVICEID_SHIFT)) & SYSCON_DEVICE_ID_DEVICEID_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SYSCON_Register_Masks */


/* SYSCON - Peripheral instance base addresses */
/** Peripheral SYSCON base address */
#define SYSCON_BASE                              (0x40048000u)
/** Peripheral SYSCON base pointer */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array initializer of SYSCON peripheral base addresses */
#define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
/** Array initializer of SYSCON peripheral base pointers */
#define SYSCON_BASE_PTRS                         { SYSCON }
/** Interrupt vectors for the SYSCON peripheral type */
#define SYSCON_IRQS                              { BOD_IRQn }

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
  __IO uint32_t INTENSET;                          /**< Interrupt Enable read and Set register. Contains an individual interrupt enable bit for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __O  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared., offset: 0x10 */
  __I  uint32_t RXDAT;                             /**< Receiver Data register. Contains the last character received., offset: 0x14 */
  __I  uint32_t RXDATSTAT;                         /**< Receiver Data with Status register. Combines the last character received with the current USART receive status. Allows DMA or software to recover incoming data and status together., offset: 0x18 */
  __IO uint32_t TXDAT;                             /**< Transmit Data register. Data to be transmitted is written here., offset: 0x1C */
  __IO uint32_t BRG;                               /**< Baud Rate Generator register. 16-bit integer baud rate divisor value., offset: 0x20 */
  __I  uint32_t INTSTAT;                           /**< Interrupt status register. Reflects interrupts that are currently enabled., offset: 0x24 */
  __IO uint32_t OSR;                               /**< Oversample selection register for asynchronous communication., offset: 0x28 */
  __IO uint32_t ADDR;                              /**< Address register for automatic address matching., offset: 0x2C */
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

#define USART_CTL_RXIDLETOCFG_MASK               (0x1C0000U)
#define USART_CTL_RXIDLETOCFG_SHIFT              (18U)
/*! RXIDLETOCFG - RX IDLE time out configuration
 *  0b000..000b - 1 idle character
 *  0b001..001b - 2 idle characters
 *  0b010..010b - 4 idle characters
 *  0b011..011b - 8 idle characters
 *  0b100..100b - 16 idle characters
 *  0b101..101b - 32 idle characters
 *  0b110..110b - 64 idle characters
 *  0b111..111b - 128 idle characters
 */
#define USART_CTL_RXIDLETOCFG(x)                 (((uint32_t)(((uint32_t)(x)) << USART_CTL_RXIDLETOCFG_SHIFT)) & USART_CTL_RXIDLETOCFG_MASK)
/*! @} */

/*! @name STAT - USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them. */
/*! @{ */

#define USART_STAT_RXRDY_MASK                    (0x1U)
#define USART_STAT_RXRDY_SHIFT                   (0U)
/*! RXRDY - Receiver Ready flag. When 1, indicates that data is available to be read from the
 *    receiver buffer. Cleared after a read of the RXDAT or RXDATSTAT registers.
 */
#define USART_STAT_RXRDY(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXRDY_SHIFT)) & USART_STAT_RXRDY_MASK)

#define USART_STAT_RXIDLE_MASK                   (0x2U)
#define USART_STAT_RXIDLE_SHIFT                  (1U)
/*! RXIDLE - Receiver Idle. When 0, indicates that the receiver is currently in the process of
 *    receiving data. When 1, indicates that the receiver is not currently in the process of receiving
 *    data.
 */
#define USART_STAT_RXIDLE(x)                     (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXIDLE_SHIFT)) & USART_STAT_RXIDLE_MASK)

#define USART_STAT_TXRDY_MASK                    (0x4U)
#define USART_STAT_TXRDY_SHIFT                   (2U)
/*! TXRDY - Transmitter Ready flag. When 1, this bit indicates that data may be written to the
 *    transmit buffer. Previous data may still be in the process of being transmitted. Cleared when data
 *    is written to TXDAT. Set when the data is moved from the transmit buffer to the transmit shift
 *    register.
 */
#define USART_STAT_TXRDY(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXRDY_SHIFT)) & USART_STAT_TXRDY_MASK)

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
/*! DELTACTS - This bit is set when a change in the state is detected for the CTS flag above. This bit is cleared by software. */
#define USART_STAT_DELTACTS(x)                   (((uint32_t)(((uint32_t)(x)) << USART_STAT_DELTACTS_SHIFT)) & USART_STAT_DELTACTS_MASK)

#define USART_STAT_TXDISSTAT_MASK                (0x40U)
#define USART_STAT_TXDISSTAT_SHIFT               (6U)
/*! TXDISSTAT - Transmitter Disabled Interrupt flag. When 1, this bit indicates that the USART
 *    transmitter is fully idle after being disabled via the TXDIS in the CTL register (TXDIS = 1).
 */
#define USART_STAT_TXDISSTAT(x)                  (((uint32_t)(((uint32_t)(x)) << USART_STAT_TXDISSTAT_SHIFT)) & USART_STAT_TXDISSTAT_MASK)

#define USART_STAT_OVERRUNINT_MASK               (0x100U)
#define USART_STAT_OVERRUNINT_SHIFT              (8U)
/*! OVERRUNINT - Overrun Error interrupt flag. This flag is set when a new character is received
 *    while the receiver buffer is still in use. If this occurs, the newly received character in the
 *    shift register is lost.
 */
#define USART_STAT_OVERRUNINT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_STAT_OVERRUNINT_SHIFT)) & USART_STAT_OVERRUNINT_MASK)

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
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs.Cleared by software. */
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
/*! PARITYERRINT - Parity Error interrupt flag. This flag is set when a parity error is detected in a received character. */
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
/*! ABERR - Autobaud Error. An autobaud error can occur if the BRG counts to its limit before the
 *    end of the start bit that is being measured, essentially an autobaud time-out.
 */
#define USART_STAT_ABERR(x)                      (((uint32_t)(((uint32_t)(x)) << USART_STAT_ABERR_SHIFT)) & USART_STAT_ABERR_MASK)

#define USART_STAT_RXIDLETO_MASK                 (0x20000U)
#define USART_STAT_RXIDLETO_SHIFT                (17U)
/*! RXIDLETO - RX IDLE Timeout flag. Set when the receiver has been idle for a certain period of
 *    time as specified by CTRL.RXIDLETOCFG. Writing 1 clears this bit and lowers the corresponding
 *    interrupt. Once cleared, it cannot be set again until after the receiver receives a new character
 *    (non-idle).
 */
#define USART_STAT_RXIDLETO(x)                   (((uint32_t)(((uint32_t)(x)) << USART_STAT_RXIDLETO_SHIFT)) & USART_STAT_RXIDLETO_MASK)
/*! @} */

/*! @name INTENSET - Interrupt Enable read and Set register. Contains an individual interrupt enable bit for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
/*! @{ */

#define USART_INTENSET_RXRDYEN_MASK              (0x1U)
#define USART_INTENSET_RXRDYEN_SHIFT             (0U)
/*! RXRDYEN - When 1, enables an interrupt when there is a received character available to be read from the RXDAT register. */
#define USART_INTENSET_RXRDYEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXRDYEN_SHIFT)) & USART_INTENSET_RXRDYEN_MASK)

#define USART_INTENSET_TXRDYEN_MASK              (0x4U)
#define USART_INTENSET_TXRDYEN_SHIFT             (2U)
/*! TXRDYEN - When 1, enables an interrupt when the TXDAT register is available to take another character to transmit. */
#define USART_INTENSET_TXRDYEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXRDYEN_SHIFT)) & USART_INTENSET_TXRDYEN_MASK)

#define USART_INTENSET_TXIDLEEN_MASK             (0x8U)
#define USART_INTENSET_TXIDLEEN_SHIFT            (3U)
/*! TXIDLEEN - When 1, enables an interrupt when the transmitter becomes idle (TXIDLE = 1). */
#define USART_INTENSET_TXIDLEEN(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXIDLEEN_SHIFT)) & USART_INTENSET_TXIDLEEN_MASK)

#define USART_INTENSET_DELTACTSEN_MASK           (0x20U)
#define USART_INTENSET_DELTACTSEN_SHIFT          (5U)
/*! DELTACTSEN - When 1, enables an interrupt when there is a change in the state of the CTS input. */
#define USART_INTENSET_DELTACTSEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTACTSEN_SHIFT)) & USART_INTENSET_DELTACTSEN_MASK)

#define USART_INTENSET_TXDISEN_MASK              (0x40U)
#define USART_INTENSET_TXDISEN_SHIFT             (6U)
/*! TXDISEN - When 1, enables an interrupt when the transmitter is fully disabled as indicated by
 *    the TXDISINT flag in STAT. See description of the TXDISINT bit for details.
 */
#define USART_INTENSET_TXDISEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_TXDISEN_SHIFT)) & USART_INTENSET_TXDISEN_MASK)

#define USART_INTENSET_OVERRUNEN_MASK            (0x100U)
#define USART_INTENSET_OVERRUNEN_SHIFT           (8U)
/*! OVERRUNEN - When 1, enables an interrupt when an overrun error occurred. */
#define USART_INTENSET_OVERRUNEN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_OVERRUNEN_SHIFT)) & USART_INTENSET_OVERRUNEN_MASK)

#define USART_INTENSET_DELTARXBRKEN_MASK         (0x800U)
#define USART_INTENSET_DELTARXBRKEN_SHIFT        (11U)
/*! DELTARXBRKEN - When 1, enables an interrupt when a change of state has occurred in the detection
 *    of a received break condition (break condition asserted or deasserted).
 */
#define USART_INTENSET_DELTARXBRKEN(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_DELTARXBRKEN_SHIFT)) & USART_INTENSET_DELTARXBRKEN_MASK)

#define USART_INTENSET_STARTEN_MASK              (0x1000U)
#define USART_INTENSET_STARTEN_SHIFT             (12U)
/*! STARTEN - When 1, enables an interrupt when a received start bit has been detected. */
#define USART_INTENSET_STARTEN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_STARTEN_SHIFT)) & USART_INTENSET_STARTEN_MASK)

#define USART_INTENSET_FRAMERREN_MASK            (0x2000U)
#define USART_INTENSET_FRAMERREN_SHIFT           (13U)
/*! FRAMERREN - When 1, enables an interrupt when a framing error has been detected. */
#define USART_INTENSET_FRAMERREN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_FRAMERREN_SHIFT)) & USART_INTENSET_FRAMERREN_MASK)

#define USART_INTENSET_PARITYERREN_MASK          (0x4000U)
#define USART_INTENSET_PARITYERREN_SHIFT         (14U)
/*! PARITYERREN - When 1, enables an interrupt when a parity error has been detected. */
#define USART_INTENSET_PARITYERREN(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_PARITYERREN_SHIFT)) & USART_INTENSET_PARITYERREN_MASK)

#define USART_INTENSET_RXNOISEEN_MASK            (0x8000U)
#define USART_INTENSET_RXNOISEEN_SHIFT           (15U)
/*! RXNOISEEN - When 1, enables an interrupt when noise is detected. */
#define USART_INTENSET_RXNOISEEN(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXNOISEEN_SHIFT)) & USART_INTENSET_RXNOISEEN_MASK)

#define USART_INTENSET_ABERREN_MASK              (0x10000U)
#define USART_INTENSET_ABERREN_SHIFT             (16U)
/*! ABERREN - When 1, enables an interrupt when an autobaud error occurs. */
#define USART_INTENSET_ABERREN(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_ABERREN_SHIFT)) & USART_INTENSET_ABERREN_MASK)

#define USART_INTENSET_RXIDLETOEN_MASK           (0x20000U)
#define USART_INTENSET_RXIDLETOEN_SHIFT          (17U)
/*! RXIDLETOEN - RX IDLE timeout interrupt enable. Write 1 to set the bit. Writing 0 has no effect.
 *    0: RX IDLE time out interrupt is disabled. 1: When STAT.RXIDLETO is set, interrupt is asserted.
 */
#define USART_INTENSET_RXIDLETOEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENSET_RXIDLETOEN_SHIFT)) & USART_INTENSET_RXIDLETOEN_MASK)
/*! @} */

/*! @name INTENCLR - Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared. */
/*! @{ */

#define USART_INTENCLR_RXRDYCLR_MASK             (0x1U)
#define USART_INTENCLR_RXRDYCLR_SHIFT            (0U)
/*! RXRDYCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_RXRDYCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXRDYCLR_SHIFT)) & USART_INTENCLR_RXRDYCLR_MASK)

#define USART_INTENCLR_TXRDYCLR_MASK             (0x4U)
#define USART_INTENCLR_TXRDYCLR_SHIFT            (2U)
/*! TXRDYCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_TXRDYCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXRDYCLR_SHIFT)) & USART_INTENCLR_TXRDYCLR_MASK)

#define USART_INTENCLR_TXIDLECLR_MASK            (0x8U)
#define USART_INTENCLR_TXIDLECLR_SHIFT           (3U)
/*! TXIDLECLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_TXIDLECLR(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXIDLECLR_SHIFT)) & USART_INTENCLR_TXIDLECLR_MASK)

#define USART_INTENCLR_DELTACTSCLR_MASK          (0x20U)
#define USART_INTENCLR_DELTACTSCLR_SHIFT         (5U)
/*! DELTACTSCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_DELTACTSCLR(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTACTSCLR_SHIFT)) & USART_INTENCLR_DELTACTSCLR_MASK)

#define USART_INTENCLR_TXDISINTCLR_MASK          (0x40U)
#define USART_INTENCLR_TXDISINTCLR_SHIFT         (6U)
/*! TXDISINTCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_TXDISINTCLR(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_TXDISINTCLR_SHIFT)) & USART_INTENCLR_TXDISINTCLR_MASK)

#define USART_INTENCLR_OVERRUNCLR_MASK           (0x100U)
#define USART_INTENCLR_OVERRUNCLR_SHIFT          (8U)
/*! OVERRUNCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_OVERRUNCLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_OVERRUNCLR_SHIFT)) & USART_INTENCLR_OVERRUNCLR_MASK)

#define USART_INTENCLR_DELTARXBRKCLR_MASK        (0x800U)
#define USART_INTENCLR_DELTARXBRKCLR_SHIFT       (11U)
/*! DELTARXBRKCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_DELTARXBRKCLR(x)          (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_DELTARXBRKCLR_SHIFT)) & USART_INTENCLR_DELTARXBRKCLR_MASK)

#define USART_INTENCLR_STARTCLR_MASK             (0x1000U)
#define USART_INTENCLR_STARTCLR_SHIFT            (12U)
/*! STARTCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_STARTCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_STARTCLR_SHIFT)) & USART_INTENCLR_STARTCLR_MASK)

#define USART_INTENCLR_FRAMERRCLR_MASK           (0x2000U)
#define USART_INTENCLR_FRAMERRCLR_SHIFT          (13U)
/*! FRAMERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_FRAMERRCLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_FRAMERRCLR_SHIFT)) & USART_INTENCLR_FRAMERRCLR_MASK)

#define USART_INTENCLR_PARITYERRCLR_MASK         (0x4000U)
#define USART_INTENCLR_PARITYERRCLR_SHIFT        (14U)
/*! PARITYERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_PARITYERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_PARITYERRCLR_SHIFT)) & USART_INTENCLR_PARITYERRCLR_MASK)

#define USART_INTENCLR_RXNOISECLR_MASK           (0x8000U)
#define USART_INTENCLR_RXNOISECLR_SHIFT          (15U)
/*! RXNOISECLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_RXNOISECLR(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXNOISECLR_SHIFT)) & USART_INTENCLR_RXNOISECLR_MASK)

#define USART_INTENCLR_ABERRCLR_MASK             (0x10000U)
#define USART_INTENCLR_ABERRCLR_SHIFT            (16U)
/*! ABERRCLR - Writing 1 clears the corresponding bit in the INTENSET register. */
#define USART_INTENCLR_ABERRCLR(x)               (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_ABERRCLR_SHIFT)) & USART_INTENCLR_ABERRCLR_MASK)

#define USART_INTENCLR_RXIDLETOEN_MASK           (0x20000U)
#define USART_INTENCLR_RXIDLETOEN_SHIFT          (17U)
/*! RXIDLETOEN - Writing 1 to clears INTENSET[RXIDLETOEN]. Writing 0 has no effect. The access for this bit is write-only. */
#define USART_INTENCLR_RXIDLETOEN(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTENCLR_RXIDLETOEN_SHIFT)) & USART_INTENCLR_RXIDLETOEN_MASK)
/*! @} */

/*! @name RXDAT - Receiver Data register. Contains the last character received. */
/*! @{ */

#define USART_RXDAT_RXDAT_MASK                   (0x1FFU)
#define USART_RXDAT_RXDAT_SHIFT                  (0U)
/*! RXDAT - The USART Receiver Data register contains the next received character. The number of
 *    bits that are relevant depends on the USART configuration settings.
 */
#define USART_RXDAT_RXDAT(x)                     (((uint32_t)(((uint32_t)(x)) << USART_RXDAT_RXDAT_SHIFT)) & USART_RXDAT_RXDAT_MASK)
/*! @} */

/*! @name RXDATSTAT - Receiver Data with Status register. Combines the last character received with the current USART receive status. Allows DMA or software to recover incoming data and status together. */
/*! @{ */

#define USART_RXDATSTAT_RXDAT_MASK               (0x1FFU)
#define USART_RXDATSTAT_RXDAT_SHIFT              (0U)
/*! RXDAT - The USART Receiver Data register contains the next received character. The number of
 *    bits that are relevant depends on the USART configuration settings.
 */
#define USART_RXDATSTAT_RXDAT(x)                 (((uint32_t)(((uint32_t)(x)) << USART_RXDATSTAT_RXDAT_SHIFT)) & USART_RXDATSTAT_RXDAT_MASK)

#define USART_RXDATSTAT_FRAMERR_MASK             (0x2000U)
#define USART_RXDATSTAT_FRAMERR_SHIFT            (13U)
/*! FRAMERR - Framing Error status flag. This bit is valid when there is a character to be read in
 *    the RXDAT register and reflects the status of that character. This bit will set when the
 *    character in RXDAT was received with a missing stop bit at the expected location. This could be an
 *    indication of a baud rate or configuration mismatch with the transmitting source.
 */
#define USART_RXDATSTAT_FRAMERR(x)               (((uint32_t)(((uint32_t)(x)) << USART_RXDATSTAT_FRAMERR_SHIFT)) & USART_RXDATSTAT_FRAMERR_MASK)

#define USART_RXDATSTAT_PARITYERR_MASK           (0x4000U)
#define USART_RXDATSTAT_PARITYERR_SHIFT          (14U)
/*! PARITYERR - Parity Error status flag. This bit is valid when there is a character to be read in
 *    the RXDAT register and reflects the status of that character. This bit will be set when a
 *    parity error is detected in a received character.
 */
#define USART_RXDATSTAT_PARITYERR(x)             (((uint32_t)(((uint32_t)(x)) << USART_RXDATSTAT_PARITYERR_SHIFT)) & USART_RXDATSTAT_PARITYERR_MASK)

#define USART_RXDATSTAT_RXNOISE_MASK             (0x8000U)
#define USART_RXDATSTAT_RXNOISE_SHIFT            (15U)
/*! RXNOISE - Received Noise flag. */
#define USART_RXDATSTAT_RXNOISE(x)               (((uint32_t)(((uint32_t)(x)) << USART_RXDATSTAT_RXNOISE_SHIFT)) & USART_RXDATSTAT_RXNOISE_MASK)
/*! @} */

/*! @name TXDAT - Transmit Data register. Data to be transmitted is written here. */
/*! @{ */

#define USART_TXDAT_TXDAT_MASK                   (0x1FFU)
#define USART_TXDAT_TXDAT_SHIFT                  (0U)
/*! TXDAT - Writing to the USART Transmit Data Register causes the data to be transmitted as soon as
 *    the transmit shift register is available and any conditions for transmitting data are met:
 *    CTS low (if CTSEN bit = 1), TXDIS bit = 0.
 */
#define USART_TXDAT_TXDAT(x)                     (((uint32_t)(((uint32_t)(x)) << USART_TXDAT_TXDAT_SHIFT)) & USART_TXDAT_TXDAT_MASK)
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

#define USART_INTSTAT_RXRDY_MASK                 (0x1U)
#define USART_INTSTAT_RXRDY_SHIFT                (0U)
/*! RXRDY - Receiver Ready flag. */
#define USART_INTSTAT_RXRDY(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXRDY_SHIFT)) & USART_INTSTAT_RXRDY_MASK)

#define USART_INTSTAT_TXRDY_MASK                 (0x4U)
#define USART_INTSTAT_TXRDY_SHIFT                (2U)
/*! TXRDY - Transmitter Ready flag. */
#define USART_INTSTAT_TXRDY(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXRDY_SHIFT)) & USART_INTSTAT_TXRDY_MASK)

#define USART_INTSTAT_TXIDLE_MASK                (0x8U)
#define USART_INTSTAT_TXIDLE_SHIFT               (3U)
/*! TXIDLE - Transmitter idle status. */
#define USART_INTSTAT_TXIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXIDLE_SHIFT)) & USART_INTSTAT_TXIDLE_MASK)

#define USART_INTSTAT_DELTACTS_MASK              (0x20U)
#define USART_INTSTAT_DELTACTS_SHIFT             (5U)
/*! DELTACTS - This bit is set when a change in the state of the CTS input is detected. */
#define USART_INTSTAT_DELTACTS(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTACTS_SHIFT)) & USART_INTSTAT_DELTACTS_MASK)

#define USART_INTSTAT_TXDISINT_MASK              (0x40U)
#define USART_INTSTAT_TXDISINT_SHIFT             (6U)
/*! TXDISINT - Transmitter Disabled Interrupt flag. */
#define USART_INTSTAT_TXDISINT(x)                (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_TXDISINT_SHIFT)) & USART_INTSTAT_TXDISINT_MASK)

#define USART_INTSTAT_OVERRUNINT_MASK            (0x100U)
#define USART_INTSTAT_OVERRUNINT_SHIFT           (8U)
/*! OVERRUNINT - Overrun Error interrupt flag. */
#define USART_INTSTAT_OVERRUNINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_OVERRUNINT_SHIFT)) & USART_INTSTAT_OVERRUNINT_MASK)

#define USART_INTSTAT_DELTARXBRK_MASK            (0x800U)
#define USART_INTSTAT_DELTARXBRK_SHIFT           (11U)
/*! DELTARXBRK - This bit is set when a change in the state of receiver break detection occurs. */
#define USART_INTSTAT_DELTARXBRK(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_DELTARXBRK_SHIFT)) & USART_INTSTAT_DELTARXBRK_MASK)

#define USART_INTSTAT_START_MASK                 (0x1000U)
#define USART_INTSTAT_START_SHIFT                (12U)
/*! START - This bit is set when a start is detected on the receiver input. */
#define USART_INTSTAT_START(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_START_SHIFT)) & USART_INTSTAT_START_MASK)

#define USART_INTSTAT_FRAMERRINT_MASK            (0x2000U)
#define USART_INTSTAT_FRAMERRINT_SHIFT           (13U)
/*! FRAMERRINT - Framing Error interrupt flag. */
#define USART_INTSTAT_FRAMERRINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_FRAMERRINT_SHIFT)) & USART_INTSTAT_FRAMERRINT_MASK)

#define USART_INTSTAT_PARITYERRINT_MASK          (0x4000U)
#define USART_INTSTAT_PARITYERRINT_SHIFT         (14U)
/*! PARITYERRINT - Parity Error interrupt flag. */
#define USART_INTSTAT_PARITYERRINT(x)            (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_PARITYERRINT_SHIFT)) & USART_INTSTAT_PARITYERRINT_MASK)

#define USART_INTSTAT_RXNOISEINT_MASK            (0x8000U)
#define USART_INTSTAT_RXNOISEINT_SHIFT           (15U)
/*! RXNOISEINT - Received Noise interrupt flag. */
#define USART_INTSTAT_RXNOISEINT(x)              (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXNOISEINT_SHIFT)) & USART_INTSTAT_RXNOISEINT_MASK)

#define USART_INTSTAT_ABERR_MASK                 (0x10000U)
#define USART_INTSTAT_ABERR_SHIFT                (16U)
/*! ABERR - Autobaud Error flag. */
#define USART_INTSTAT_ABERR(x)                   (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_ABERR_SHIFT)) & USART_INTSTAT_ABERR_MASK)

#define USART_INTSTAT_RXIDLETOINT_MASK           (0x20000U)
#define USART_INTSTAT_RXIDLETOINT_SHIFT          (17U)
/*! RXIDLETOINT - RX IDLE timeout interrupt flag. The access of this bit is read-only. */
#define USART_INTSTAT_RXIDLETOINT(x)             (((uint32_t)(((uint32_t)(x)) << USART_INTSTAT_RXIDLETOINT_SHIFT)) & USART_INTSTAT_RXIDLETOINT_MASK)
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


/*!
 * @}
 */ /* end of group USART_Register_Masks */


/* USART - Peripheral instance base addresses */
/** Peripheral USART0 base address */
#define USART0_BASE                              (0x40064000u)
/** Peripheral USART0 base pointer */
#define USART0                                   ((USART_Type *)USART0_BASE)
/** Peripheral USART1 base address */
#define USART1_BASE                              (0x40068000u)
/** Peripheral USART1 base pointer */
#define USART1                                   ((USART_Type *)USART1_BASE)
/** Peripheral USART2 base address */
#define USART2_BASE                              (0x4006C000u)
/** Peripheral USART2 base pointer */
#define USART2                                   ((USART_Type *)USART2_BASE)
/** Array initializer of USART peripheral base addresses */
#define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE }
/** Array initializer of USART peripheral base pointers */
#define USART_BASE_PTRS                          { USART0, USART1, USART2 }
/** Interrupt vectors for the USART peripheral type */
#define USART_IRQS                               { USART0_IRQn, USART1_IRQn, USART2_IRQn }

/*!
 * @}
 */ /* end of group USART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WKT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WKT_Peripheral_Access_Layer WKT Peripheral Access Layer
 * @{
 */

/** WKT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Self wake-up timer control register., offset: 0x0 */
       uint8_t RESERVED_0[8];
  __IO uint32_t COUNT;                             /**< Counter register., offset: 0xC */
} WKT_Type;

/* ----------------------------------------------------------------------------
   -- WKT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WKT_Register_Masks WKT Register Masks
 * @{
 */

/*! @name CTRL - Self wake-up timer control register. */
/*! @{ */

#define WKT_CTRL_CLKSEL_MASK                     (0x1U)
#define WKT_CTRL_CLKSEL_SHIFT                    (0U)
/*! CLKSEL - Select the self wake-up timer clock source. Remark: This bit only has an effect if the SEL_EXTCLK bit is not set.
 *  0b0..Divided FRO clock. This clock runs at 750 kHz and provides time-out periods of up to approximately 95
 *       minutes in 1.33 us increments. Remark: This clock is not available in not available in Deep-sleep,
 *       power-down, deep power-down modes. Do not select this option if the timer is to be used to wake up from one of these
 *       modes.
 *  0b1..This is the (nominally) 10 kHz clock and provides time-out periods of up to approximately 119 hours in
 *       100 us increments. The accuracy of this clock is limited to +/- 40 % over temperature and processing.
 *       Remark: This clock is available in all power modes. Prior to use, the low-power oscillator must be enabled. The
 *       oscillator must also be set to remain active in Deep power-down if needed.
 */
#define WKT_CTRL_CLKSEL(x)                       (((uint32_t)(((uint32_t)(x)) << WKT_CTRL_CLKSEL_SHIFT)) & WKT_CTRL_CLKSEL_MASK)

#define WKT_CTRL_ALARMFLAG_MASK                  (0x2U)
#define WKT_CTRL_ALARMFLAG_SHIFT                 (1U)
/*! ALARMFLAG - Wake-up or alarm timer flag.
 *  0b0..No time-out. The self wake-up timer has not timed out. Writing a 0 to has no effect.
 *  0b1..Time-out. The self wake-up timer has timed out. This flag generates an interrupt request which can wake
 *       up the part from any reduced power mode including Deep power-down if the clock source is the low power
 *       oscillator. Writing a 1 clears this status bit.
 */
#define WKT_CTRL_ALARMFLAG(x)                    (((uint32_t)(((uint32_t)(x)) << WKT_CTRL_ALARMFLAG_SHIFT)) & WKT_CTRL_ALARMFLAG_MASK)

#define WKT_CTRL_CLEARCTR_MASK                   (0x4U)
#define WKT_CTRL_CLEARCTR_SHIFT                  (2U)
/*! CLEARCTR - Clears the self wake-up timer.
 *  0b0..No effect. Reading this bit always returns 0.
 *  0b1..Clear the counter. Counting is halted until a new count value is loaded.
 */
#define WKT_CTRL_CLEARCTR(x)                     (((uint32_t)(((uint32_t)(x)) << WKT_CTRL_CLEARCTR_SHIFT)) & WKT_CTRL_CLEARCTR_MASK)

#define WKT_CTRL_SEL_EXTCLK_MASK                 (0x8U)
#define WKT_CTRL_SEL_EXTCLK_SHIFT                (3U)
/*! SEL_EXTCLK - Select external or internal clock source for the self wake-up timer. The internal
 *    clock source is selected by the CLKSEL bit in this register if SET_EXTCLK is set to internal.
 *  0b0..Internal. The clock source is the internal clock selected by the CLKSEL bit.
 *  0b1..External. The self wake-up timer uses the external WKTCLKIN pin.
 */
#define WKT_CTRL_SEL_EXTCLK(x)                   (((uint32_t)(((uint32_t)(x)) << WKT_CTRL_SEL_EXTCLK_SHIFT)) & WKT_CTRL_SEL_EXTCLK_MASK)
/*! @} */

/*! @name COUNT - Counter register. */
/*! @{ */

#define WKT_COUNT_VALUE_MASK                     (0xFFFFFFFFU)
#define WKT_COUNT_VALUE_SHIFT                    (0U)
/*! VALUE - A write to this register pre-loads start count value into the timer and starts the
 *    count-down sequence. A read reflects the current value of the timer.
 */
#define WKT_COUNT_VALUE(x)                       (((uint32_t)(((uint32_t)(x)) << WKT_COUNT_VALUE_SHIFT)) & WKT_COUNT_VALUE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group WKT_Register_Masks */


/* WKT - Peripheral instance base addresses */
/** Peripheral WKT base address */
#define WKT_BASE                                 (0x40008000u)
/** Peripheral WKT base pointer */
#define WKT                                      ((WKT_Type *)WKT_BASE)
/** Array initializer of WKT peripheral base addresses */
#define WKT_BASE_ADDRS                           { WKT_BASE }
/** Array initializer of WKT peripheral base pointers */
#define WKT_BASE_PTRS                            { WKT }
/** Interrupt vectors for the WKT peripheral type */
#define WKT_IRQS                                 { WKT_IRQn }

/*!
 * @}
 */ /* end of group WKT_Peripheral_Access_Layer */


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
/*! COUNT - Watchdog time-out value. */
#define WWDT_TC_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TC_COUNT_SHIFT)) & WWDT_TC_COUNT_MASK)
/*! @} */

/*! @name FEED - Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in TC. */
/*! @{ */

#define WWDT_FEED_FEED_MASK                      (0xFFU)
#define WWDT_FEED_FEED_SHIFT                     (0U)
/*! FEED - Feed value should be 0xAA followed by 0x55. */
#define WWDT_FEED_FEED(x)                        (((uint32_t)(((uint32_t)(x)) << WWDT_FEED_FEED_SHIFT)) & WWDT_FEED_FEED_MASK)
/*! @} */

/*! @name TV - Watchdog timer value register. This 24-bit register reads out the current value of the Watchdog timer. */
/*! @{ */

#define WWDT_TV_COUNT_MASK                       (0xFFFFFFU)
#define WWDT_TV_COUNT_SHIFT                      (0U)
/*! COUNT - Counter timer value. */
#define WWDT_TV_COUNT(x)                         (((uint32_t)(((uint32_t)(x)) << WWDT_TV_COUNT_SHIFT)) & WWDT_TV_COUNT_MASK)
/*! @} */

/*! @name WARNINT - Watchdog Warning Interrupt compare value. */
/*! @{ */

#define WWDT_WARNINT_WARNINT_MASK                (0x3FFU)
#define WWDT_WARNINT_WARNINT_SHIFT               (0U)
/*! WARNINT - Watchdog warning interrupt compare value. */
#define WWDT_WARNINT_WARNINT(x)                  (((uint32_t)(((uint32_t)(x)) << WWDT_WARNINT_WARNINT_SHIFT)) & WWDT_WARNINT_WARNINT_MASK)
/*! @} */

/*! @name WINDOW - Watchdog Window compare value. */
/*! @{ */

#define WWDT_WINDOW_WINDOW_MASK                  (0xFFFFFFU)
#define WWDT_WINDOW_WINDOW_SHIFT                 (0U)
/*! WINDOW - Watchdog window value. */
#define WWDT_WINDOW_WINDOW(x)                    (((uint32_t)(((uint32_t)(x)) << WWDT_WINDOW_WINDOW_SHIFT)) & WWDT_WINDOW_WINDOW_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group WWDT_Register_Masks */


/* WWDT - Peripheral instance base addresses */
/** Peripheral WWDT base address */
#define WWDT_BASE                                (0x40000000u)
/** Peripheral WWDT base pointer */
#define WWDT                                     ((WWDT_Type *)WWDT_BASE)
/** Array initializer of WWDT peripheral base addresses */
#define WWDT_BASE_ADDRS                          { WWDT_BASE }
/** Array initializer of WWDT peripheral base pointers */
#define WWDT_BASE_PTRS                           { WWDT }
/** Interrupt vectors for the WWDT peripheral type */
#define WWDT_IRQS                                { WDT_IRQn }

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


#endif  /* _LPC865_H_ */

