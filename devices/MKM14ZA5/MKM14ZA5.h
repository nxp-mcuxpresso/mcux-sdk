/*
** ###################################################################
**     Processors:          MKM14Z128ACHH5
**                          MKM14Z64ACHH5
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MKMxxZxxACxx5RM, Rev. 2, 10/2017
**     Version:             rev. 1.0, 2014-07-22
**     Build:               b210422
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MKM14ZA5
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2014-07-22)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file MKM14ZA5.h
 * @version 1.0
 * @date 2014-07-22
 * @brief CMSIS Peripheral Access Layer for MKM14ZA5
 *
 * CMSIS Peripheral Access Layer for MKM14ZA5
 */

#ifndef _MKM14ZA5_H_
#define _MKM14ZA5_H_                             /**< Symbol preventing repeated inclusion */

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
  DMA0_IRQn                    = 0,                /**< DMA channel 0 transfer complete */
  DMA1_IRQn                    = 1,                /**< DMA channel 1 transfer complete */
  DMA2_IRQn                    = 2,                /**< DMA channel 2 transfer complete */
  DMA3_IRQn                    = 3,                /**< DMA channel 3 transfer complete */
  SPI0_IRQn                    = 4,                /**< SPI0 ORed interrupt */
  SPI1_IRQn                    = 5,                /**< SPI1 ORed interrupt */
  PMC_IRQn                     = 6,                /**< Low-voltage detect, low-voltage warning */
  TMR0_IRQn                    = 7,                /**< Quad Timer Channel 0 */
  TMR1_IRQn                    = 8,                /**< Quad Timer Channel 1 */
  TMR2_IRQn                    = 9,                /**< Quad Timer Channel 2 */
  TMR3_IRQn                    = 10,               /**< Quad Timer Channel 3 */
  PIT0_PIT1_IRQn               = 11,               /**< PIT0/PIT1 ORed interrupt */
  LLWU_IRQn                    = 12,               /**< Low Leakage Wakeup */
  FTFA_IRQn                    = 13,               /**< Command complete and read collision */
  CMP0_CMP1_IRQn               = 14,               /**< CMP0/CMP1 ORed interrupt */
  Reserved31_IRQn              = 15,               /**< Reserved interrupt */
  ADC_IRQn                     = 16,               /**< ADC interrupt */
  PTx_IRQn                     = 17,               /**< Single interrupt vector for GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI */
  RNGA_IRQn                    = 18,               /**< RNGA interrupt */
  UART0_UART1_IRQn             = 19,               /**< UART0/UART1 ORed interrupt */
  UART2_UART3_IRQn             = 20,               /**< UART2/UART3 ORed interrupt */
  AFE_CH0_IRQn                 = 21,               /**< AFE Channel 0 */
  AFE_CH1_IRQn                 = 22,               /**< AFE Channel 1 */
  AFE_CH2_IRQn                 = 23,               /**< AFE Channel 2 */
  AFE_CH3_IRQn                 = 24,               /**< AFE Channel 3 */
  RTC_IRQn                     = 25,               /**< IRTC interrupt */
  I2C0_I2C1_IRQn               = 26,               /**< I2C0/I2C1 ORed interrupt */
  EWM_IRQn                     = 27,               /**< External Watchdog Monitor */
  MCG_IRQn                     = 28,               /**< MCG interrupt */
  WDOG_IRQn                    = 29,               /**< WDOG ORed interrupt */
  LPTMR_IRQn                   = 30,               /**< LPTMR interrupt */
  XBAR_IRQn                    = 31                /**< XBAR interrupt */
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
#include "system_MKM14ZA5.h"           /* Device specific configuration file */

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
 * @addtogroup edma_request
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum _dma_request_source
{
    kDmaRequestMux0Disable          = 0|0x100U,    /**< DMAMUX TriggerDisabled */
    kDmaRequestMux0SPI0Tx           = 1|0x100U,    /**< SPI0 Transmit (DMAMUX0) */
    kDmaRequestMux0SPI0Rx           = 2|0x100U,    /**< SPI0 Receive (DMAMUX0) */
    kDmaRequestMux0UART0Tx          = 3|0x100U,    /**< UART0 Transmit (DMAMUX0) */
    kDmaRequestMux0UART0Rx          = 4|0x100U,    /**< UART0 Receive (DMAMUX0) */
    kDmaRequestMux0I2C0             = 5|0x100U,    /**< I2C0 (DMAMUX0) */
    kDmaRequestMux0XBAR             = 6|0x100U,    /**< XBAR (DMAMUX0) */
    kDmaRequestMux0UART3Tx          = 7|0x100U,    /**< UART3 Transmit (DMAMUX0) */
    kDmaRequestMux0UART3Rx          = 8|0x100U,    /**< UART3 Receive (DMAMUX0) */
    kDmaRequestMux0AFEChannel0      = 9|0x100U,    /**< AFE channel 0 (DMAMUX0) */
    kDmaRequestMux0TMR0             = 10|0x100U,   /**< TMR0 (DMAMUX0) */
    kDmaRequestMux0TMR3             = 11|0x100U,   /**< TMR3 (DMAMUX0) */
    kDmaRequestMux0AFEChannel2      = 12|0x100U,   /**< AFE channel 2 (DMAMUX0) */
    kDmaRequestMux0ADC              = 13|0x100U,   /**< ADC (DMAMUX0) */
    kDmaRequestMux0CMP0             = 14|0x100U,   /**< CMP0 (DMAMUX0) */
    kDmaRequestMux0PTE              = 15|0x100U,   /**< PTE (DMAMUX0) */
    kDmaRequestMux0PTA              = 16|0x100U,   /**< PTA (DMAMUX0) */
    kDmaRequestMux0AlwaysEnabledslot17 = 17|0x100U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux0AlwaysEnabledslot18 = 18|0x100U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux0Reserved19       = 19|0x100U,   /**< Reserved19 */
    kDmaRequestMux0Reserved20       = 20|0x100U,   /**< Reserved20 */
    kDmaRequestMux0Reserved21       = 21|0x100U,   /**< Reserved21 */
    kDmaRequestMux0Reserved22       = 22|0x100U,   /**< Reserved22 */
    kDmaRequestMux0Reserved23       = 23|0x100U,   /**< Reserved23 */
    kDmaRequestMux0Reserved24       = 24|0x100U,   /**< Reserved24 */
    kDmaRequestMux0Reserved25       = 25|0x100U,   /**< Reserved25 */
    kDmaRequestMux0Reserved26       = 26|0x100U,   /**< Reserved26 */
    kDmaRequestMux0Reserved27       = 27|0x100U,   /**< Reserved27 */
    kDmaRequestMux0Reserved28       = 28|0x100U,   /**< Reserved28 */
    kDmaRequestMux0Reserved29       = 29|0x100U,   /**< Reserved29 */
    kDmaRequestMux0Reserved30       = 30|0x100U,   /**< Reserved30 */
    kDmaRequestMux0Reserved31       = 31|0x100U,   /**< Reserved31 */
    kDmaRequestMux0Reserved32       = 32|0x100U,   /**< Reserved32 */
    kDmaRequestMux0Reserved33       = 33|0x100U,   /**< Reserved33 */
    kDmaRequestMux0Reserved34       = 34|0x100U,   /**< Reserved34 */
    kDmaRequestMux0Reserved35       = 35|0x100U,   /**< Reserved35 */
    kDmaRequestMux0Reserved36       = 36|0x100U,   /**< Reserved36 */
    kDmaRequestMux0Reserved37       = 37|0x100U,   /**< Reserved37 */
    kDmaRequestMux0Reserved38       = 38|0x100U,   /**< Reserved38 */
    kDmaRequestMux0Reserved39       = 39|0x100U,   /**< Reserved39 */
    kDmaRequestMux0Reserved40       = 40|0x100U,   /**< Reserved40 */
    kDmaRequestMux0Reserved41       = 41|0x100U,   /**< Reserved41 */
    kDmaRequestMux0Reserved42       = 42|0x100U,   /**< Reserved42 */
    kDmaRequestMux0Reserved43       = 43|0x100U,   /**< Reserved43 */
    kDmaRequestMux0Reserved44       = 44|0x100U,   /**< Reserved44 */
    kDmaRequestMux0Reserved45       = 45|0x100U,   /**< Reserved45 */
    kDmaRequestMux0Reserved46       = 46|0x100U,   /**< Reserved46 */
    kDmaRequestMux0Reserved47       = 47|0x100U,   /**< Reserved47 */
    kDmaRequestMux0Reserved48       = 48|0x100U,   /**< Reserved48 */
    kDmaRequestMux0Reserved49       = 49|0x100U,   /**< Reserved49 */
    kDmaRequestMux0Reserved50       = 50|0x100U,   /**< Reserved50 */
    kDmaRequestMux0Reserved51       = 51|0x100U,   /**< Reserved51 */
    kDmaRequestMux0Reserved52       = 52|0x100U,   /**< Reserved52 */
    kDmaRequestMux0Reserved53       = 53|0x100U,   /**< Reserved53 */
    kDmaRequestMux0Reserved54       = 54|0x100U,   /**< Reserved54 */
    kDmaRequestMux0Reserved55       = 55|0x100U,   /**< Reserved55 */
    kDmaRequestMux0Reserved56       = 56|0x100U,   /**< Reserved56 */
    kDmaRequestMux0Reserved57       = 57|0x100U,   /**< Reserved57 */
    kDmaRequestMux0Reserved58       = 58|0x100U,   /**< Reserved58 */
    kDmaRequestMux0Reserved59       = 59|0x100U,   /**< Reserved59 */
    kDmaRequestMux0Reserved60       = 60|0x100U,   /**< Reserved60 */
    kDmaRequestMux0Reserved61       = 61|0x100U,   /**< Reserved61 */
    kDmaRequestMux0Reserved62       = 62|0x100U,   /**< Reserved62 */
    kDmaRequestMux0Reserved63       = 63|0x100U,   /**< Reserved63 */
    kDmaRequestMux1Disable          = 0|0x200U,    /**< DMAMUX TriggerDisabled */
    kDmaRequestMux1SPI0Tx           = 1|0x200U,    /**< SPI0 Transmit (DMAMUX1) */
    kDmaRequestMux1SPI0Rx           = 2|0x200U,    /**< SPI0 Receive (DMAMUX1) */
    kDmaRequestMux1UART1Tx          = 3|0x200U,    /**< UART1 Transmit (DMAMUX1) */
    kDmaRequestMux1UART1Rx          = 4|0x200U,    /**< UART1 Receive (DMAMUX1) */
    kDmaRequestMux1I2C0             = 5|0x200U,    /**< I2C0 (DMAMUX1) */
    kDmaRequestMux1XBAR             = 6|0x200U,    /**< XBAR (DMAMUX1) */
    kDmaRequestMux1UART3Tx          = 7|0x200U,    /**< UART3 Transmit (DMAMUX1) */
    kDmaRequestMux1UART3Rx          = 8|0x200U,    /**< UART3 Receive (DMAMUX1) */
    kDmaRequestMux1AFEChannel0      = 9|0x200U,    /**< AFE channel 0 (DMAMUX1) */
    kDmaRequestMux1TMR0             = 10|0x200U,   /**< TMR0 (DMAMUX1) */
    kDmaRequestMux1TMR3             = 11|0x200U,   /**< TMR3 (DMAMUX1) */
    kDmaRequestMux1AFEChannel2      = 12|0x200U,   /**< AFE channel 2 (DMAMUX1) */
    kDmaRequestMux1PTE              = 13|0x200U,   /**< PTE (DMAMUX1) */
    kDmaRequestMux1CMP0             = 14|0x200U,   /**< CMP0 (DMAMUX1) */
    kDmaRequestMux1PTF              = 15|0x200U,   /**< PTF (DMAMUX1) */
    kDmaRequestMux1PTB              = 16|0x200U,   /**< PTB (DMAMUX1) */
    kDmaRequestMux1AlwaysEnabledslot17 = 17|0x200U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux1AlwaysEnabledslot18 = 18|0x200U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux1Reserved19       = 19|0x200U,   /**< Reserved19 */
    kDmaRequestMux1Reserved20       = 20|0x200U,   /**< Reserved20 */
    kDmaRequestMux1Reserved21       = 21|0x200U,   /**< Reserved21 */
    kDmaRequestMux1Reserved22       = 22|0x200U,   /**< Reserved22 */
    kDmaRequestMux1Reserved23       = 23|0x200U,   /**< Reserved23 */
    kDmaRequestMux1Reserved24       = 24|0x200U,   /**< Reserved24 */
    kDmaRequestMux1Reserved25       = 25|0x200U,   /**< Reserved25 */
    kDmaRequestMux1Reserved26       = 26|0x200U,   /**< Reserved26 */
    kDmaRequestMux1Reserved27       = 27|0x200U,   /**< Reserved27 */
    kDmaRequestMux1Reserved28       = 28|0x200U,   /**< Reserved28 */
    kDmaRequestMux1Reserved29       = 29|0x200U,   /**< Reserved29 */
    kDmaRequestMux1Reserved30       = 30|0x200U,   /**< Reserved30 */
    kDmaRequestMux1Reserved31       = 31|0x200U,   /**< Reserved31 */
    kDmaRequestMux1Reserved32       = 32|0x200U,   /**< Reserved32 */
    kDmaRequestMux1Reserved33       = 33|0x200U,   /**< Reserved33 */
    kDmaRequestMux1Reserved34       = 34|0x200U,   /**< Reserved34 */
    kDmaRequestMux1Reserved35       = 35|0x200U,   /**< Reserved35 */
    kDmaRequestMux1Reserved36       = 36|0x200U,   /**< Reserved36 */
    kDmaRequestMux1Reserved37       = 37|0x200U,   /**< Reserved37 */
    kDmaRequestMux1Reserved38       = 38|0x200U,   /**< Reserved38 */
    kDmaRequestMux1Reserved39       = 39|0x200U,   /**< Reserved39 */
    kDmaRequestMux1Reserved40       = 40|0x200U,   /**< Reserved40 */
    kDmaRequestMux1Reserved41       = 41|0x200U,   /**< Reserved41 */
    kDmaRequestMux1Reserved42       = 42|0x200U,   /**< Reserved42 */
    kDmaRequestMux1Reserved43       = 43|0x200U,   /**< Reserved43 */
    kDmaRequestMux1Reserved44       = 44|0x200U,   /**< Reserved44 */
    kDmaRequestMux1Reserved45       = 45|0x200U,   /**< Reserved45 */
    kDmaRequestMux1Reserved46       = 46|0x200U,   /**< Reserved46 */
    kDmaRequestMux1Reserved47       = 47|0x200U,   /**< Reserved47 */
    kDmaRequestMux1Reserved48       = 48|0x200U,   /**< Reserved48 */
    kDmaRequestMux1Reserved49       = 49|0x200U,   /**< Reserved49 */
    kDmaRequestMux1Reserved50       = 50|0x200U,   /**< Reserved50 */
    kDmaRequestMux1Reserved51       = 51|0x200U,   /**< Reserved51 */
    kDmaRequestMux1Reserved52       = 52|0x200U,   /**< Reserved52 */
    kDmaRequestMux1Reserved53       = 53|0x200U,   /**< Reserved53 */
    kDmaRequestMux1Reserved54       = 54|0x200U,   /**< Reserved54 */
    kDmaRequestMux1Reserved55       = 55|0x200U,   /**< Reserved55 */
    kDmaRequestMux1Reserved56       = 56|0x200U,   /**< Reserved56 */
    kDmaRequestMux1Reserved57       = 57|0x200U,   /**< Reserved57 */
    kDmaRequestMux1Reserved58       = 58|0x200U,   /**< Reserved58 */
    kDmaRequestMux1Reserved59       = 59|0x200U,   /**< Reserved59 */
    kDmaRequestMux1Reserved60       = 60|0x200U,   /**< Reserved60 */
    kDmaRequestMux1Reserved61       = 61|0x200U,   /**< Reserved61 */
    kDmaRequestMux1Reserved62       = 62|0x200U,   /**< Reserved62 */
    kDmaRequestMux1Reserved63       = 63|0x200U,   /**< Reserved63 */
    kDmaRequestMux2Disable          = 0|0x300U,    /**< DMAMUX TriggerDisabled */
    kDmaRequestMux2SPI1Tx           = 1|0x300U,    /**< SPI1 Transmit (DMAMUX2) */
    kDmaRequestMux2SPI1Rx           = 2|0x300U,    /**< SPI1 Receive (DMAMUX2) */
    kDmaRequestMux2UART1Tx          = 3|0x300U,    /**< UART1 Transmit (DMAMUX2) */
    kDmaRequestMux2UART1Rx          = 4|0x300U,    /**< UART1 Receive (DMAMUX2) */
    kDmaRequestMux2I2C1             = 5|0x300U,    /**< I2C1 (DMAMUX2) */
    kDmaRequestMux2XBAR             = 6|0x300U,    /**< XBAR (DMAMUX2) */
    kDmaRequestMux2UART2Tx          = 7|0x300U,    /**< UART2 Transmit (DMAMUX2) */
    kDmaRequestMux2UART2Rx          = 8|0x300U,    /**< UART2 Receive (DMAMUX2) */
    kDmaRequestMux2AFEChannel1      = 9|0x300U,    /**< AFE channel 1 (DMAMUX2) */
    kDmaRequestMux2TMR2             = 10|0x300U,   /**< TMR2 (DMAMUX2) */
    kDmaRequestMux2TMR1             = 11|0x300U,   /**< TMR1 (DMAMUX2) */
    kDmaRequestMux2AFEChannel3      = 12|0x300U,   /**< AFE channel 3 (DMAMUX2) */
    kDmaRequestMux2PTI              = 13|0x300U,   /**< PTI (DMAMUX2) */
    kDmaRequestMux2CMP1             = 14|0x300U,   /**< CMP1 (DMAMUX2) */
    kDmaRequestMux2PTG              = 15|0x300U,   /**< PTG (DMAMUX2) */
    kDmaRequestMux2PTC              = 16|0x300U,   /**< PTC (DMAMUX2) */
    kDmaRequestMux2AlwaysEnabledslot17 = 17|0x300U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux2AlwaysEnabledslot18 = 18|0x300U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux2Reserved19       = 19|0x300U,   /**< Reserved19 */
    kDmaRequestMux2Reserved20       = 20|0x300U,   /**< Reserved20 */
    kDmaRequestMux2Reserved21       = 21|0x300U,   /**< Reserved21 */
    kDmaRequestMux2Reserved22       = 22|0x300U,   /**< Reserved22 */
    kDmaRequestMux2Reserved23       = 23|0x300U,   /**< Reserved23 */
    kDmaRequestMux2Reserved24       = 24|0x300U,   /**< Reserved24 */
    kDmaRequestMux2Reserved25       = 25|0x300U,   /**< Reserved25 */
    kDmaRequestMux2Reserved26       = 26|0x300U,   /**< Reserved26 */
    kDmaRequestMux2Reserved27       = 27|0x300U,   /**< Reserved27 */
    kDmaRequestMux2Reserved28       = 28|0x300U,   /**< Reserved28 */
    kDmaRequestMux2Reserved29       = 29|0x300U,   /**< Reserved29 */
    kDmaRequestMux2Reserved30       = 30|0x300U,   /**< Reserved30 */
    kDmaRequestMux2Reserved31       = 31|0x300U,   /**< Reserved31 */
    kDmaRequestMux2Reserved32       = 32|0x300U,   /**< Reserved32 */
    kDmaRequestMux2Reserved33       = 33|0x300U,   /**< Reserved33 */
    kDmaRequestMux2Reserved34       = 34|0x300U,   /**< Reserved34 */
    kDmaRequestMux2Reserved35       = 35|0x300U,   /**< Reserved35 */
    kDmaRequestMux2Reserved36       = 36|0x300U,   /**< Reserved36 */
    kDmaRequestMux2Reserved37       = 37|0x300U,   /**< Reserved37 */
    kDmaRequestMux2Reserved38       = 38|0x300U,   /**< Reserved38 */
    kDmaRequestMux2Reserved39       = 39|0x300U,   /**< Reserved39 */
    kDmaRequestMux2Reserved40       = 40|0x300U,   /**< Reserved40 */
    kDmaRequestMux2Reserved41       = 41|0x300U,   /**< Reserved41 */
    kDmaRequestMux2Reserved42       = 42|0x300U,   /**< Reserved42 */
    kDmaRequestMux2Reserved43       = 43|0x300U,   /**< Reserved43 */
    kDmaRequestMux2Reserved44       = 44|0x300U,   /**< Reserved44 */
    kDmaRequestMux2Reserved45       = 45|0x300U,   /**< Reserved45 */
    kDmaRequestMux2Reserved46       = 46|0x300U,   /**< Reserved46 */
    kDmaRequestMux2Reserved47       = 47|0x300U,   /**< Reserved47 */
    kDmaRequestMux2Reserved48       = 48|0x300U,   /**< Reserved48 */
    kDmaRequestMux2Reserved49       = 49|0x300U,   /**< Reserved49 */
    kDmaRequestMux2Reserved50       = 50|0x300U,   /**< Reserved50 */
    kDmaRequestMux2Reserved51       = 51|0x300U,   /**< Reserved51 */
    kDmaRequestMux2Reserved52       = 52|0x300U,   /**< Reserved52 */
    kDmaRequestMux2Reserved53       = 53|0x300U,   /**< Reserved53 */
    kDmaRequestMux2Reserved54       = 54|0x300U,   /**< Reserved54 */
    kDmaRequestMux2Reserved55       = 55|0x300U,   /**< Reserved55 */
    kDmaRequestMux2Reserved56       = 56|0x300U,   /**< Reserved56 */
    kDmaRequestMux2Reserved57       = 57|0x300U,   /**< Reserved57 */
    kDmaRequestMux2Reserved58       = 58|0x300U,   /**< Reserved58 */
    kDmaRequestMux2Reserved59       = 59|0x300U,   /**< Reserved59 */
    kDmaRequestMux2Reserved60       = 60|0x300U,   /**< Reserved60 */
    kDmaRequestMux2Reserved61       = 61|0x300U,   /**< Reserved61 */
    kDmaRequestMux2Reserved62       = 62|0x300U,   /**< Reserved62 */
    kDmaRequestMux2Reserved63       = 63|0x300U,   /**< Reserved63 */
    kDmaRequestMux3Disable          = 0|0x400U,    /**< DMAMUX TriggerDisabled */
    kDmaRequestMux3SPI1Tx           = 1|0x400U,    /**< SPI1 Transmit (DMAMUX3) */
    kDmaRequestMux3SPI1Rx           = 2|0x400U,    /**< SPI1 Receive (DMAMUX3) */
    kDmaRequestMux3UART0Tx          = 3|0x400U,    /**< UART0 Transmit (DMAMUX3) */
    kDmaRequestMux3UART0Rx          = 4|0x400U,    /**< UART0 Receive (DMAMUX3) */
    kDmaRequestMux3I2C1             = 5|0x400U,    /**< I2C1 (DMAMUX3) */
    kDmaRequestMux3XBAR             = 6|0x400U,    /**< XBAR (DMAMUX3) */
    kDmaRequestMux3UART2Tx          = 7|0x400U,    /**< UART2 Transmit (DMAMUX3) */
    kDmaRequestMux3UART2Rx          = 8|0x400U,    /**< UART2 Receive (DMAMUX3) */
    kDmaRequestMux3AFEChannel1      = 9|0x400U,    /**< AFE channel 1 (DMAMUX3) */
    kDmaRequestMux3TMR2             = 10|0x400U,   /**< TMR2 (DMAMUX3) */
    kDmaRequestMux3TMR1             = 11|0x400U,   /**< TMR1 (DMAMUX3) */
    kDmaRequestMux3AFEChannel3      = 12|0x400U,   /**< AFE channel 3 (DMAMUX3) */
    kDmaRequestMux3ADC              = 13|0x400U,   /**< ADC (DMAMUX3) */
    kDmaRequestMux3CMP1             = 14|0x400U,   /**< CMP1 (DMAMUX3) */
    kDmaRequestMux3PTH              = 15|0x400U,   /**< PTH (DMAMUX3) */
    kDmaRequestMux3PTD              = 16|0x400U,   /**< PTD (DMAMUX3) */
    kDmaRequestMux3AlwaysEnabledslot17 = 17|0x400U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux3AlwaysEnabledslot18 = 18|0x400U, /**< DMAMUX Always Enabled slot */
    kDmaRequestMux3Reserved19       = 19|0x400U,   /**< Reserved19 */
    kDmaRequestMux3Reserved20       = 20|0x400U,   /**< Reserved20 */
    kDmaRequestMux3Reserved21       = 21|0x400U,   /**< Reserved21 */
    kDmaRequestMux3Reserved22       = 22|0x400U,   /**< Reserved22 */
    kDmaRequestMux3Reserved23       = 23|0x400U,   /**< Reserved23 */
    kDmaRequestMux3Reserved24       = 24|0x400U,   /**< Reserved24 */
    kDmaRequestMux3Reserved25       = 25|0x400U,   /**< Reserved25 */
    kDmaRequestMux3Reserved26       = 26|0x400U,   /**< Reserved26 */
    kDmaRequestMux3Reserved27       = 27|0x400U,   /**< Reserved27 */
    kDmaRequestMux3Reserved28       = 28|0x400U,   /**< Reserved28 */
    kDmaRequestMux3Reserved29       = 29|0x400U,   /**< Reserved29 */
    kDmaRequestMux3Reserved30       = 30|0x400U,   /**< Reserved30 */
    kDmaRequestMux3Reserved31       = 31|0x400U,   /**< Reserved31 */
    kDmaRequestMux3Reserved32       = 32|0x400U,   /**< Reserved32 */
    kDmaRequestMux3Reserved33       = 33|0x400U,   /**< Reserved33 */
    kDmaRequestMux3Reserved34       = 34|0x400U,   /**< Reserved34 */
    kDmaRequestMux3Reserved35       = 35|0x400U,   /**< Reserved35 */
    kDmaRequestMux3Reserved36       = 36|0x400U,   /**< Reserved36 */
    kDmaRequestMux3Reserved37       = 37|0x400U,   /**< Reserved37 */
    kDmaRequestMux3Reserved38       = 38|0x400U,   /**< Reserved38 */
    kDmaRequestMux3Reserved39       = 39|0x400U,   /**< Reserved39 */
    kDmaRequestMux3Reserved40       = 40|0x400U,   /**< Reserved40 */
    kDmaRequestMux3Reserved41       = 41|0x400U,   /**< Reserved41 */
    kDmaRequestMux3Reserved42       = 42|0x400U,   /**< Reserved42 */
    kDmaRequestMux3Reserved43       = 43|0x400U,   /**< Reserved43 */
    kDmaRequestMux3Reserved44       = 44|0x400U,   /**< Reserved44 */
    kDmaRequestMux3Reserved45       = 45|0x400U,   /**< Reserved45 */
    kDmaRequestMux3Reserved46       = 46|0x400U,   /**< Reserved46 */
    kDmaRequestMux3Reserved47       = 47|0x400U,   /**< Reserved47 */
    kDmaRequestMux3Reserved48       = 48|0x400U,   /**< Reserved48 */
    kDmaRequestMux3Reserved49       = 49|0x400U,   /**< Reserved49 */
    kDmaRequestMux3Reserved50       = 50|0x400U,   /**< Reserved50 */
    kDmaRequestMux3Reserved51       = 51|0x400U,   /**< Reserved51 */
    kDmaRequestMux3Reserved52       = 52|0x400U,   /**< Reserved52 */
    kDmaRequestMux3Reserved53       = 53|0x400U,   /**< Reserved53 */
    kDmaRequestMux3Reserved54       = 54|0x400U,   /**< Reserved54 */
    kDmaRequestMux3Reserved55       = 55|0x400U,   /**< Reserved55 */
    kDmaRequestMux3Reserved56       = 56|0x400U,   /**< Reserved56 */
    kDmaRequestMux3Reserved57       = 57|0x400U,   /**< Reserved57 */
    kDmaRequestMux3Reserved58       = 58|0x400U,   /**< Reserved58 */
    kDmaRequestMux3Reserved59       = 59|0x400U,   /**< Reserved59 */
    kDmaRequestMux3Reserved60       = 60|0x400U,   /**< Reserved60 */
    kDmaRequestMux3Reserved61       = 61|0x400U,   /**< Reserved61 */
    kDmaRequestMux3Reserved62       = 62|0x400U,   /**< Reserved62 */
    kDmaRequestMux3Reserved63       = 63|0x400U,   /**< Reserved63 */
} dma_request_source_t;

/* @} */

typedef enum _xbar_input_signal
{
    kXBAR_InputVdd                  = 0|0x100U,    /**< Logic 1 (VDD) output assigned to XBAR_IN0 input. */
    kXBAR_InputVss                  = 1|0x100U,    /**< Logic 0 (VSS) output assigned to XBAR_IN1 input. */
    kXBAR_InputAfeClock             = 2|0x100U,    /**< AFE modulator clock output output assigned to XBAR_IN2 input. */
    kXBAR_InputAfeModDataOutput     = 3|0x100U,    /**< AFE modulator data output output assigned to XBAR_IN3 input. */
    kXBAR_InputLptmrOutput          = 4|0x100U,    /**< LPTimer Output output assigned to XBAR_IN4 input. */
    kXBAR_InputClockOutput          = 5|0x100U,    /**< Clock Output output assigned to XBAR_IN5 input. */
    kXBAR_InputTmrCh0Output         = 6|0x100U,    /**< Quad Timer channel 0 output output assigned to XBAR_IN6 input. */
    kXBAR_InputTmrCh1Output         = 7|0x100U,    /**< Quad Timer channel 1 output output assigned to XBAR_IN7 input. */
    kXBAR_InputTmrCh2Output         = 8|0x100U,    /**< Quad Timer channel 2 output output assigned to XBAR_IN8 input. */
    kXBAR_InputTmrCh3Output         = 9|0x100U,    /**< Quad Timer channel 3 output output assigned to XBAR_IN9 input. */
    kXBAR_InputRtcClockOutput       = 10|0x100U,   /**< iRTC Clock Output output assigned to XBAR_IN10 input. */
    kXBAR_InputCmp0Output           = 11|0x100U,   /**< CMP0 Output output assigned to XBAR_IN11 input. */
    kXBAR_InputCmp1Output           = 12|0x100U,   /**< CMP1 Output output assigned to XBAR_IN12 input. */
    kXBAR_InputRtcAlarmOutput       = 13|0x100U,   /**< iRTC Alarm Output output assigned to XBAR_IN13 input. */
    kXBAR_InputUartTxOutput         = 14|0x100U,   /**< UART TX Output (after modulation) output assigned to XBAR_IN14 input. */
    kXBAR_InputEwmOutput            = 15|0x100U,   /**< EWM Output (EWM_OUT) output assigned to XBAR_IN15 input. */
    kXBAR_InputPitOut               = 16|0x100U,   /**< PIT Output output assigned to XBAR_IN16 input. */
    kXBAR_InputXbarIn0              = 17|0x100U,   /**< XBAR Input pin 0 output assigned to XBAR_IN17 input. */
    kXBAR_InputXbarIn1              = 18|0x100U,   /**< XBAR Input pin 1 output assigned to XBAR_IN18 input. */
    kXBAR_InputXbarIn2              = 19|0x100U,   /**< XBAR Input pin 2 output assigned to XBAR_IN19 input. */
    kXBAR_InputXbarIn3              = 20|0x100U,   /**< XBAR Input pin 3 output assigned to XBAR_IN20 input. */
    kXBAR_InputXbarIn4              = 21|0x100U,   /**< XBAR Input pin 4 output assigned to XBAR_IN21 input. */
    kXBAR_InputXbarIn5              = 22|0x100U,   /**< XBAR Input pin 5 output assigned to XBAR_IN22 input. */
    kXBAR_InputXbarIn6              = 23|0x100U,   /**< XBAR Input pin 6 output assigned to XBAR_IN23 input. */
    kXBAR_InputXbarIn7              = 24|0x100U,   /**< XBAR Input pin 7 output assigned to XBAR_IN24 input. */
    kXBAR_InputXbarIn8              = 25|0x100U,   /**< XBAR Input pin 8 output assigned to XBAR_IN25 input. */
    kXBAR_InputAdcCocoFlag          = 26|0x100U,   /**< ORed conversion complete flag for all SAR ADC channels output assigned to XBAR_IN26 input. */
    kXBAR_InputAfeAllCocFlag        = 27|0x100U,   /**< ORed conversion complete flag for all AFE channels output assigned to XBAR_IN27 input. */
    kXBAR_InputAfeCh0CocFlag        = 28|0x100U,   /**< AFE Channel 0 conversion complete output assigned to XBAR_IN28 input. */
    kXBAR_InputAfeCh1CocFlag        = 29|0x100U,   /**< AFE Channel 1 conversion complete output assigned to XBAR_IN29 input. */
    kXBAR_InputAfeCh2CocFlag        = 30|0x100U,   /**< AFE Channel 2 conversion complete output assigned to XBAR_IN30 input. */
    kXBAR_InputAfeCh3CocFlag        = 31|0x100U,   /**< AFE Channel 3 conversion complete output assigned to XBAR_IN31 input. */
    kXBAR_InputDmaDoneSignal        = 32|0x100U,   /**< DMA Done Signal output assigned to XBAR_IN32 input. */
} xbar_input_signal_t;

typedef enum _xbar_output_signal
{
    kXBAR_OutputXbDmaInt            = 0|0x100U,    /**< XBAR_OUT0 output assigned to XBAR DMA request or Interrupt */
    kXBAR_OutputAfeCh0ExmodData     = 1|0x100U,    /**< XBAR_OUT1 output assigned to External modulator data input for AFE Channel 0 */
    kXBAR_OutputAfeCh1ExmodData     = 2|0x100U,    /**< XBAR_OUT2 output assigned to External modulator data input for AFE Channel 1 */
    kXBAR_OutputAfeCh2ExmodData     = 3|0x100U,    /**< XBAR_OUT3 output assigned to External modulator data input for AFE Channel 2 */
    kXBAR_OutputAfeCh3ExmodData     = 4|0x100U,    /**< XBAR_OUT4 output assigned to External modulator data input for AFE Channel 3 */
    kXBAR_OutputTmrCh0SecInput      = 5|0x100U,    /**< XBAR_OUT5 output assigned to Quad Timer channel 0 secondary input */
    kXBAR_OutputTmrCh1SecInput      = 6|0x100U,    /**< XBAR_OUT6 output assigned to Quad Timer channel 1 secondary input */
    kXBAR_OutputTmrCh2SecInput      = 7|0x100U,    /**< XBAR_OUT7 output assigned to Quad Timer channel 2 secondary input */
    kXBAR_OutputTmrCh3SecInput      = 8|0x100U,    /**< XBAR_OUT8 output assigned to Quad Timer channel 3 secondary input */
    kXBAR_OutputTmrClockInput1      = 9|0x100U,    /**< XBAR_OUT9 output assigned to Quad Timer primary clock input 1 */
    kXBAR_OutputTmrClockInput2      = 10|0x100U,   /**< XBAR_OUT10 output assigned to Quad Timer primary clock input 2 */
    kXBAR_OutputCmp0SampleWinInput  = 11|0x100U,   /**< XBAR_OUT11 output assigned to CMP0 Sample Window input */
    kXBAR_OutputCmp1SampleWinInput  = 12|0x100U,   /**< XBAR_OUT12 output assigned to CMP1 Sample Window input */
    kXBAR_OutputUartRxInput         = 13|0x100U,   /**< XBAR_OUT13 output assigned to UART Rx IrDA Input */
    kXBAR_OutputUartTxModCarrier    = 14|0x100U,   /**< XBAR_OUT14 output assigned to SIM UART Tx IrDA Modulator Carrier Input */
    kXBAR_OutputAdcTrgA             = 15|0x100U,   /**< XBAR_OUT15 output assigned to SAR ADC trigger select A pulse */
    kXBAR_OutputAdcTrgB             = 16|0x100U,   /**< XBAR_OUT16 output assigned to SAR ADC trigger select B pulse */
    kXBAR_OutputXbOut0              = 17|0x100U,   /**< XBAR_OUT17 output assigned to XBAR Output pin 0 */
    kXBAR_OutputXbOut1              = 18|0x100U,   /**< XBAR_OUT18 output assigned to XBAR Output pin 1 */
    kXBAR_OutputXbOut2              = 19|0x100U,   /**< XBAR_OUT19 output assigned to XBAR Output pin 2 */
    kXBAR_OutputXbOut3              = 20|0x100U,   /**< XBAR_OUT20 output assigned to XBAR Output pin 3 */
    kXBAR_OutputXbOut4              = 21|0x100U,   /**< XBAR_OUT21 output assigned to XBAR Output pin 4 */
    kXBAR_OutputXbOut5              = 22|0x100U,   /**< XBAR_OUT22 output assigned to XBAR Output pin 5 */
    kXBAR_OutputXbOut6              = 23|0x100U,   /**< XBAR_OUT23 output assigned to XBAR Output pin 6 */
    kXBAR_OutputXbOut7              = 24|0x100U,   /**< XBAR_OUT24 output assigned to XBAR Output pin 7 */
    kXBAR_OutputXbOut8              = 25|0x100U,   /**< XBAR_OUT25 output assigned to XBAR Output pin 8 */
    kXBAR_OutputAdcTrgC             = 26|0x100U,   /**< XBAR_OUT26 output assigned to SAR ADC trigger select C pulse */
    kXBAR_OutputAdcTrgD             = 27|0x100U,   /**< XBAR_OUT27 output assigned to SAR ADC trigger select D pulse */
    kXBAR_OutputAfeCh0Trg           = 28|0x100U,   /**< XBAR_OUT28 output assigned to AFE Channel 0 Trigger */
    kXBAR_OutputAfeCh1Trg           = 29|0x100U,   /**< XBAR_OUT29 output assigned to AFE Channel 1 Trigger */
    kXBAR_OutputAfeCh2Trg           = 30|0x100U,   /**< XBAR_OUT30 output assigned to AFE Channel 2 Trigger */
    kXBAR_OutputAfeCh3Trg           = 31|0x100U,   /**< XBAR_OUT31 output assigned to AFE Channel 3 Trigger */
    kXBAR_OutputEwmIn               = 32|0x100U,   /**< XBAR_OUT32 output assigned to EWM input (EWM_IN) */
} xbar_output_signal_t;


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
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
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
  __IO uint32_t SC1[4];                            /**< ADC Status and Control Registers 1, array offset: 0x0, array step: 0x4 */
  __IO uint32_t CFG1;                              /**< ADC Configuration Register 1, offset: 0x10 */
  __IO uint32_t CFG2;                              /**< ADC Configuration Register 2, offset: 0x14 */
  __I  uint32_t R[4];                              /**< ADC Data Result Register, array offset: 0x18, array step: 0x4 */
  __IO uint32_t CV1;                               /**< Compare Value Registers, offset: 0x28 */
  __IO uint32_t CV2;                               /**< Compare Value Registers, offset: 0x2C */
  __IO uint32_t SC2;                               /**< Status and Control Register 2, offset: 0x30 */
  __IO uint32_t SC3;                               /**< Status and Control Register 3, offset: 0x34 */
  __IO uint32_t OFS;                               /**< ADC Offset Correction Register, offset: 0x38 */
  __IO uint32_t PG;                                /**< ADC Plus-Side Gain Register, offset: 0x3C */
       uint8_t RESERVED_0[4];
  __IO uint32_t CLPD;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x44 */
  __IO uint32_t CLPS;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x48 */
  __IO uint32_t CLP4;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x4C */
  __IO uint32_t CLP3;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x50 */
  __IO uint32_t CLP2;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x54 */
  __IO uint32_t CLP1;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x58 */
  __IO uint32_t CLP0;                              /**< ADC Plus-Side General Calibration Value Register, offset: 0x5C */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name SC1 - ADC Status and Control Registers 1 */
/*! @{ */

#define ADC_SC1_ADCH_MASK                        (0x1FU)
#define ADC_SC1_ADCH_SHIFT                       (0U)
/*! ADCH - Input channel select
 *  0b00000..AD0 is selected as input.
 *  0b00001..AD1 is selected as input.
 *  0b00010..AD2 is selected as input.
 *  0b00011..AD3 is selected as input.
 *  0b00100..AD4 is selected as input.
 *  0b00101..AD5 is selected as input.
 *  0b00110..AD6 is selected as input.
 *  0b00111..AD7 is selected as input.
 *  0b01000..AD8 is selected as input.
 *  0b01001..AD9 is selected as input.
 *  0b01010..AD10 is selected as input.
 *  0b01011..AD11 is selected as input.
 *  0b01100..AD12 is selected as input.
 *  0b01101..AD13 is selected as input.
 *  0b01110..AD14 is selected as input.
 *  0b01111..AD15 is selected as input.
 *  0b10000..AD16 is selected as input.
 *  0b10001..AD17 is selected as input.
 *  0b10010..AD18 is selected as input.
 *  0b10011..AD19 is selected as input.
 *  0b10100..AD20 is selected as input.
 *  0b10101..AD21 is selected as input.
 *  0b10110..AD22 is selected as input.
 *  0b10111..AD23 is selected as input.
 *  0b11000..Reserved.
 *  0b11001..Reserved.
 *  0b11010..Temp Sensor (single-ended) is selected as input.
 *  0b11011..Bandgap (single-ended) is selected as input.
 *  0b11100..Reserved.
 *  0b11101..VREFSH is selected as input. Voltage reference selected is determined by SC2[REFSEL].
 *  0b11110..VREFSL is selected as input. Voltage reference selected is determined by SC2[REFSEL].
 *  0b11111..Module is disabled.
 */
#define ADC_SC1_ADCH(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_ADCH_SHIFT)) & ADC_SC1_ADCH_MASK)

#define ADC_SC1_AIEN_MASK                        (0x40U)
#define ADC_SC1_AIEN_SHIFT                       (6U)
/*! AIEN - Interrupt Enable
 *  0b0..Conversion complete interrupt is disabled.
 *  0b1..Conversion complete interrupt is enabled.
 */
#define ADC_SC1_AIEN(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_AIEN_SHIFT)) & ADC_SC1_AIEN_MASK)

#define ADC_SC1_COCO_MASK                        (0x80U)
#define ADC_SC1_COCO_SHIFT                       (7U)
/*! COCO - Conversion Complete Flag
 *  0b0..Conversion is not completed.
 *  0b1..Conversion is completed.
 */
#define ADC_SC1_COCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC1_COCO_SHIFT)) & ADC_SC1_COCO_MASK)
/*! @} */

/* The count of ADC_SC1 */
#define ADC_SC1_COUNT                            (4U)

/*! @name CFG1 - ADC Configuration Register 1 */
/*! @{ */

#define ADC_CFG1_ADICLK_MASK                     (0x3U)
#define ADC_CFG1_ADICLK_SHIFT                    (0U)
/*! ADICLK - Input Clock Select
 *  0b00..Bus clock
 *  0b01..Bus clock divided by 2(BUSCLK/2)
 *  0b10..Alternate clock (ALTCLK)
 *  0b11..Asynchronous clock (ADACK)
 */
#define ADC_CFG1_ADICLK(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADICLK_SHIFT)) & ADC_CFG1_ADICLK_MASK)

#define ADC_CFG1_MODE_MASK                       (0xCU)
#define ADC_CFG1_MODE_SHIFT                      (2U)
/*! MODE - Conversion mode selection
 *  0b00..It is single-ended 8-bit conversion.
 *  0b01..It is single-ended 12-bit conversion .
 *  0b10..It is single-ended 10-bit conversion.
 *  0b11..It is single-ended 16-bit conversion..
 */
#define ADC_CFG1_MODE(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_MODE_SHIFT)) & ADC_CFG1_MODE_MASK)

#define ADC_CFG1_ADLSMP_MASK                     (0x10U)
#define ADC_CFG1_ADLSMP_SHIFT                    (4U)
/*! ADLSMP - Sample Time Configuration
 *  0b0..Short sample time.
 *  0b1..Long sample time.
 */
#define ADC_CFG1_ADLSMP(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLSMP_SHIFT)) & ADC_CFG1_ADLSMP_MASK)

#define ADC_CFG1_ADIV_MASK                       (0x60U)
#define ADC_CFG1_ADIV_SHIFT                      (5U)
/*! ADIV - Clock Divide Select
 *  0b00..The divide ratio is 1 and the clock rate is input clock.
 *  0b01..The divide ratio is 2 and the clock rate is (input clock)/2.
 *  0b10..The divide ratio is 4 and the clock rate is (input clock)/4.
 *  0b11..The divide ratio is 8 and the clock rate is (input clock)/8.
 */
#define ADC_CFG1_ADIV(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADIV_SHIFT)) & ADC_CFG1_ADIV_MASK)

#define ADC_CFG1_ADLPC_MASK                      (0x80U)
#define ADC_CFG1_ADLPC_SHIFT                     (7U)
/*! ADLPC - Low-Power Configuration
 *  0b0..Normal power configuration.
 *  0b1..Low-power configuration. The power is reduced at the expense of maximum clock speed.
 */
#define ADC_CFG1_ADLPC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG1_ADLPC_SHIFT)) & ADC_CFG1_ADLPC_MASK)
/*! @} */

/*! @name CFG2 - ADC Configuration Register 2 */
/*! @{ */

#define ADC_CFG2_ADLSTS_MASK                     (0x3U)
#define ADC_CFG2_ADLSTS_SHIFT                    (0U)
/*! ADLSTS - Long Sample Time Select
 *  0b00..Default longest sample time; 20 extra ADCK cycles; 24 ADCK cycles total.
 *  0b01..12 extra ADCK cycles; 16 ADCK cycles total sample time.
 *  0b10..6 extra ADCK cycles; 10 ADCK cycles total sample time.
 *  0b11..2 extra ADCK cycles; 6 ADCK cycles total sample time.
 */
#define ADC_CFG2_ADLSTS(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADLSTS_SHIFT)) & ADC_CFG2_ADLSTS_MASK)

#define ADC_CFG2_ADHSC_MASK                      (0x4U)
#define ADC_CFG2_ADHSC_SHIFT                     (2U)
/*! ADHSC - High-Speed Configuration
 *  0b0..Normal conversion sequence selected.
 *  0b1..High-speed conversion sequence selected with 2 additional ADCK cycles to total conversion time.
 */
#define ADC_CFG2_ADHSC(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADHSC_SHIFT)) & ADC_CFG2_ADHSC_MASK)

#define ADC_CFG2_ADACKEN_MASK                    (0x8U)
#define ADC_CFG2_ADACKEN_SHIFT                   (3U)
/*! ADACKEN - Asynchronous Clock Output Enable
 *  0b0..Asynchronous clock output disabled; Asynchronous clock is enabled only if selected by ADICLK and a conversion is active.
 *  0b1..Asynchronous clock and clock output is enabled regardless of the state of the ADC.
 */
#define ADC_CFG2_ADACKEN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_CFG2_ADACKEN_SHIFT)) & ADC_CFG2_ADACKEN_MASK)
/*! @} */

/*! @name R - ADC Data Result Register */
/*! @{ */

#define ADC_R_D_MASK                             (0xFFFFU)
#define ADC_R_D_SHIFT                            (0U)
/*! D - Data result
 */
#define ADC_R_D(x)                               (((uint32_t)(((uint32_t)(x)) << ADC_R_D_SHIFT)) & ADC_R_D_MASK)
/*! @} */

/* The count of ADC_R */
#define ADC_R_COUNT                              (4U)

/*! @name CV1 - Compare Value Registers */
/*! @{ */

#define ADC_CV1_CV_MASK                          (0xFFFFU)
#define ADC_CV1_CV_SHIFT                         (0U)
/*! CV - Compare Value.
 */
#define ADC_CV1_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV1_CV_SHIFT)) & ADC_CV1_CV_MASK)
/*! @} */

/*! @name CV2 - Compare Value Registers */
/*! @{ */

#define ADC_CV2_CV_MASK                          (0xFFFFU)
#define ADC_CV2_CV_SHIFT                         (0U)
/*! CV - Compare Value.
 */
#define ADC_CV2_CV(x)                            (((uint32_t)(((uint32_t)(x)) << ADC_CV2_CV_SHIFT)) & ADC_CV2_CV_MASK)
/*! @} */

/*! @name SC2 - Status and Control Register 2 */
/*! @{ */

#define ADC_SC2_REFSEL_MASK                      (0x3U)
#define ADC_SC2_REFSEL_SHIFT                     (0U)
/*! REFSEL - Voltage Reference Selection
 *  0b00..Default voltage reference pin pair, that is, external pins VREFH and VREFL
 *  0b01..Alternate reference pair, that is, VALTH and VALTL . This pair may be additional external pins or
 *        internal sources depending on the MCU configuration. See the chip configuration information for details
 *        specific to this MCU
 *  0b10..Internal bandgap reference and associated ground reference (V BGH and V BGL ). Consult the Chip
 *        Configuration information for details specific to this MCU.
 *  0b11..Reserved
 */
#define ADC_SC2_REFSEL(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_SC2_REFSEL_SHIFT)) & ADC_SC2_REFSEL_MASK)

#define ADC_SC2_DMAEN_MASK                       (0x4U)
#define ADC_SC2_DMAEN_SHIFT                      (2U)
/*! DMAEN - DMA Enable
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled and will assert the ADC DMA request during an ADC conversion complete event noted when any
 *       of the SC1n[COCO] flags is asserted.
 */
#define ADC_SC2_DMAEN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_DMAEN_SHIFT)) & ADC_SC2_DMAEN_MASK)

#define ADC_SC2_ACREN_MASK                       (0x8U)
#define ADC_SC2_ACREN_SHIFT                      (3U)
/*! ACREN - Compare Function Range Enable
 *  0b0..Range function disabled. Only CV1 is compared.
 *  0b1..Range function enabled. Both CV1 and CV2 are compared.
 */
#define ADC_SC2_ACREN(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACREN_SHIFT)) & ADC_SC2_ACREN_MASK)

#define ADC_SC2_ACFGT_MASK                       (0x10U)
#define ADC_SC2_ACFGT_SHIFT                      (4U)
/*! ACFGT - Compare Function Greater Than Enable
 *  0b0..Configures less than threshold, outside range not inclusive and inside range not inclusive; functionality
 *       based on the values placed in CV1 and CV2.
 *  0b1..Configures greater than or equal to threshold, outside and inside ranges inclusive; functionality based on the values placed in CV1 and CV2.
 */
#define ADC_SC2_ACFGT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFGT_SHIFT)) & ADC_SC2_ACFGT_MASK)

#define ADC_SC2_ACFE_MASK                        (0x20U)
#define ADC_SC2_ACFE_SHIFT                       (5U)
/*! ACFE - Compare Function Enable
 *  0b0..Compare function disabled.
 *  0b1..Compare function enabled.
 */
#define ADC_SC2_ACFE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ACFE_SHIFT)) & ADC_SC2_ACFE_MASK)

#define ADC_SC2_ADTRG_MASK                       (0x40U)
#define ADC_SC2_ADTRG_SHIFT                      (6U)
/*! ADTRG - Conversion Trigger Select
 *  0b0..Software trigger selected.
 *  0b1..Hardware trigger selected.
 */
#define ADC_SC2_ADTRG(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADTRG_SHIFT)) & ADC_SC2_ADTRG_MASK)

#define ADC_SC2_ADACT_MASK                       (0x80U)
#define ADC_SC2_ADACT_SHIFT                      (7U)
/*! ADACT - Conversion Active
 *  0b0..Conversion not in progress.
 *  0b1..Conversion in progress.
 */
#define ADC_SC2_ADACT(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_SC2_ADACT_SHIFT)) & ADC_SC2_ADACT_MASK)
/*! @} */

/*! @name SC3 - Status and Control Register 3 */
/*! @{ */

#define ADC_SC3_AVGS_MASK                        (0x3U)
#define ADC_SC3_AVGS_SHIFT                       (0U)
/*! AVGS - Hardware Average Select
 *  0b00..4 samples averaged.
 *  0b01..8 samples averaged.
 *  0b10..16 samples averaged.
 *  0b11..32 samples averaged.
 */
#define ADC_SC3_AVGS(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGS_SHIFT)) & ADC_SC3_AVGS_MASK)

#define ADC_SC3_AVGE_MASK                        (0x4U)
#define ADC_SC3_AVGE_SHIFT                       (2U)
/*! AVGE - Hardware Average Enable
 *  0b0..Hardware average function disabled.
 *  0b1..Hardware average function enabled.
 */
#define ADC_SC3_AVGE(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_AVGE_SHIFT)) & ADC_SC3_AVGE_MASK)

#define ADC_SC3_ADCO_MASK                        (0x8U)
#define ADC_SC3_ADCO_SHIFT                       (3U)
/*! ADCO - Continuous Conversion Enable
 *  0b0..One conversion or one set of conversions if the hardware average function is enabled, that is, AVGE=1, after initiating a conversion.
 *  0b1..Continuous conversions or sets of conversions if the hardware average function is enabled, that is, AVGE=1, after initiating a conversion.
 */
#define ADC_SC3_ADCO(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_ADCO_SHIFT)) & ADC_SC3_ADCO_MASK)

#define ADC_SC3_CALF_MASK                        (0x40U)
#define ADC_SC3_CALF_SHIFT                       (6U)
/*! CALF - Calibration Failed Flag
 *  0b0..Calibration completed normally.
 *  0b1..Calibration failed. ADC accuracy specifications are not guaranteed.
 */
#define ADC_SC3_CALF(x)                          (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CALF_SHIFT)) & ADC_SC3_CALF_MASK)

#define ADC_SC3_CAL_MASK                         (0x80U)
#define ADC_SC3_CAL_SHIFT                        (7U)
/*! CAL - Calibration
 */
#define ADC_SC3_CAL(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_SC3_CAL_SHIFT)) & ADC_SC3_CAL_MASK)
/*! @} */

/*! @name OFS - ADC Offset Correction Register */
/*! @{ */

#define ADC_OFS_OFS_MASK                         (0xFFFFU)
#define ADC_OFS_OFS_SHIFT                        (0U)
/*! OFS - Offset Error Correction Value
 */
#define ADC_OFS_OFS(x)                           (((uint32_t)(((uint32_t)(x)) << ADC_OFS_OFS_SHIFT)) & ADC_OFS_OFS_MASK)
/*! @} */

/*! @name PG - ADC Plus-Side Gain Register */
/*! @{ */

#define ADC_PG_PG_MASK                           (0xFFFFU)
#define ADC_PG_PG_SHIFT                          (0U)
/*! PG - Plus-Side Gain
 */
#define ADC_PG_PG(x)                             (((uint32_t)(((uint32_t)(x)) << ADC_PG_PG_SHIFT)) & ADC_PG_PG_MASK)
/*! @} */

/*! @name CLPD - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLPD_CLPD_MASK                       (0x3FU)
#define ADC_CLPD_CLPD_SHIFT                      (0U)
/*! CLPD - Calibration Value
 */
#define ADC_CLPD_CLPD(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPD_CLPD_SHIFT)) & ADC_CLPD_CLPD_MASK)
/*! @} */

/*! @name CLPS - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLPS_CLPS_MASK                       (0x3FU)
#define ADC_CLPS_CLPS_SHIFT                      (0U)
/*! CLPS - Calibration Value
 */
#define ADC_CLPS_CLPS(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLPS_CLPS_SHIFT)) & ADC_CLPS_CLPS_MASK)
/*! @} */

/*! @name CLP4 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP4_CLP4_MASK                       (0x3FFU)
#define ADC_CLP4_CLP4_SHIFT                      (0U)
/*! CLP4 - Calibration Value
 */
#define ADC_CLP4_CLP4(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP4_CLP4_SHIFT)) & ADC_CLP4_CLP4_MASK)
/*! @} */

/*! @name CLP3 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP3_CLP3_MASK                       (0x1FFU)
#define ADC_CLP3_CLP3_SHIFT                      (0U)
/*! CLP3 - Calibration Value
 */
#define ADC_CLP3_CLP3(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP3_CLP3_SHIFT)) & ADC_CLP3_CLP3_MASK)
/*! @} */

/*! @name CLP2 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP2_CLP2_MASK                       (0xFFU)
#define ADC_CLP2_CLP2_SHIFT                      (0U)
/*! CLP2 - Calibration Value
 */
#define ADC_CLP2_CLP2(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP2_CLP2_SHIFT)) & ADC_CLP2_CLP2_MASK)
/*! @} */

/*! @name CLP1 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP1_CLP1_MASK                       (0x7FU)
#define ADC_CLP1_CLP1_SHIFT                      (0U)
/*! CLP1 - Calibration Value
 */
#define ADC_CLP1_CLP1(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP1_CLP1_SHIFT)) & ADC_CLP1_CLP1_MASK)
/*! @} */

/*! @name CLP0 - ADC Plus-Side General Calibration Value Register */
/*! @{ */

#define ADC_CLP0_CLP0_MASK                       (0x3FU)
#define ADC_CLP0_CLP0_SHIFT                      (0U)
/*! CLP0 - Calibration Value
 */
#define ADC_CLP0_CLP0(x)                         (((uint32_t)(((uint32_t)(x)) << ADC_CLP0_CLP0_SHIFT)) & ADC_CLP0_CLP0_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC base address */
#define ADC_BASE                                 (0x4002B000u)
/** Peripheral ADC base pointer */
#define ADC                                      ((ADC_Type *)ADC_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_IRQS                                 { ADC_IRQn }

/*!
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AFE Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Peripheral_Access_Layer AFE Peripheral Access Layer
 * @{
 */

/** AFE - Register Layout Typedef */
typedef struct {
  __IO uint32_t CFR[4];                            /**< Channel0 Configuration Register..Channel3 Configuration Register, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[8];
  __IO uint32_t CR;                                /**< Control Register, offset: 0x18 */
  __IO uint32_t CKR;                               /**< Clock Configuration Register, offset: 0x1C */
  __IO uint32_t DI;                                /**< DMA and Interrupt Register, offset: 0x20 */
       uint8_t RESERVED_1[8];
  __IO uint32_t DR[4];                             /**< Channel0 Delay Register..Channel3 Delay Register, array offset: 0x2C, array step: 0x4 */
       uint8_t RESERVED_2[8];
  __I  uint32_t RR[4];                             /**< Channel0 Result Register..Channel3 Result Register, array offset: 0x44, array step: 0x4 */
       uint8_t RESERVED_3[8];
  __I  uint32_t SR;                                /**< Status Register, offset: 0x5C */
} AFE_Type;

/* ----------------------------------------------------------------------------
   -- AFE Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AFE_Register_Masks AFE Register Masks
 * @{
 */

/*! @name CFR - Channel0 Configuration Register..Channel3 Configuration Register */
/*! @{ */

#define AFE_CFR_HW_TRG_MASK                      (0x200U)
#define AFE_CFR_HW_TRG_SHIFT                     (9U)
/*! HW_TRG - Hardware Trigger Select
 *  0b0..Software trigger select
 *  0b1..Hardware trigger select
 */
#define AFE_CFR_HW_TRG(x)                        (((uint32_t)(((uint32_t)(x)) << AFE_CFR_HW_TRG_SHIFT)) & AFE_CFR_HW_TRG_MASK)

#define AFE_CFR_DEC_CLK_INP_SEL_MASK             (0x400U)
#define AFE_CFR_DEC_CLK_INP_SEL_SHIFT            (10U)
/*! DEC_CLK_INP_SEL - Decimator Clock Input Select
 *  0b0..On the chip modulator clock will be used
 *  0b1..External clock will be used.
 */
#define AFE_CFR_DEC_CLK_INP_SEL(x)               (((uint32_t)(((uint32_t)(x)) << AFE_CFR_DEC_CLK_INP_SEL_SHIFT)) & AFE_CFR_DEC_CLK_INP_SEL_MASK)

#define AFE_CFR_DEC_CLK_EDGE_SEL_MASK            (0x800U)
#define AFE_CFR_DEC_CLK_EDGE_SEL_SHIFT           (11U)
/*! DEC_CLK_EDGE_SEL - Decimator Clock Edge Select
 *  0b0..Posedge will be used.
 *  0b1..Negedge will be used.
 */
#define AFE_CFR_DEC_CLK_EDGE_SEL(x)              (((uint32_t)(((uint32_t)(x)) << AFE_CFR_DEC_CLK_EDGE_SEL_SHIFT)) & AFE_CFR_DEC_CLK_EDGE_SEL_MASK)

#define AFE_CFR_CC_MASK                          (0x1000U)
#define AFE_CFR_CC_SHIFT                         (12U)
/*! CC - Continuous Conversion/Single Conversion Mode Select
 *  0b0..One conversion following a triggering event
 *  0b1..Continuous conversions following a triggering event.
 */
#define AFE_CFR_CC(x)                            (((uint32_t)(((uint32_t)(x)) << AFE_CFR_CC_SHIFT)) & AFE_CFR_CC_MASK)

#define AFE_CFR_DEC_EN_MASK                      (0x2000U)
#define AFE_CFR_DEC_EN_SHIFT                     (13U)
/*! DEC_EN - Decimation Filter enable
 *  0b0..Decimation filter is disabled.
 *  0b1..Decimation filter is enabled.
 */
#define AFE_CFR_DEC_EN(x)                        (((uint32_t)(((uint32_t)(x)) << AFE_CFR_DEC_EN_SHIFT)) & AFE_CFR_DEC_EN_MASK)

#define AFE_CFR_SD_MOD_EN_MASK                   (0x4000U)
#define AFE_CFR_SD_MOD_EN_SHIFT                  (14U)
/*! SD_MOD_EN - Sigma Delta Modulator enable
 *  0b0..SD ADC1 is disabled
 *  0b1..SD ADC1 is enabled
 */
#define AFE_CFR_SD_MOD_EN(x)                     (((uint32_t)(((uint32_t)(x)) << AFE_CFR_SD_MOD_EN_SHIFT)) & AFE_CFR_SD_MOD_EN_MASK)

#define AFE_CFR_BYP_MODE_MASK                    (0x20000U)
#define AFE_CFR_BYP_MODE_SHIFT                   (17U)
/*! BYP_MODE - AFE Channel3 bypass mode
 *  0b0..Normal mode
 *  0b1..Bypass mode where ADC and PGA of channel0 are disabled.
 */
#define AFE_CFR_BYP_MODE(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_CFR_BYP_MODE_SHIFT)) & AFE_CFR_BYP_MODE_MASK)

#define AFE_CFR_PGA_GAIN_SEL_MASK                (0x380000U)
#define AFE_CFR_PGA_GAIN_SEL_SHIFT               (19U)
/*! PGA_GAIN_SEL - PGA Gain Select
 *  0b000..reserved
 *  0b001..1x (default)
 *  0b010..2x
 *  0b011..4x
 *  0b100..8x
 *  0b101..16x
 *  0b110..32x
 *  0b111..reserved
 */
#define AFE_CFR_PGA_GAIN_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << AFE_CFR_PGA_GAIN_SEL_SHIFT)) & AFE_CFR_PGA_GAIN_SEL_MASK)

#define AFE_CFR_PGA_EN_MASK                      (0x1000000U)
#define AFE_CFR_PGA_EN_SHIFT                     (24U)
/*! PGA_EN - PGA enable
 *  0b0..PGA disabled
 *  0b1..PGA enabled
 */
#define AFE_CFR_PGA_EN(x)                        (((uint32_t)(((uint32_t)(x)) << AFE_CFR_PGA_EN_SHIFT)) & AFE_CFR_PGA_EN_MASK)

#define AFE_CFR_DEC_OSR_MASK                     (0xE0000000U)
#define AFE_CFR_DEC_OSR_SHIFT                    (29U)
/*! DEC_OSR - Decimator OverSampling Ratio select
 *  0b000..64
 *  0b001..128
 *  0b010..256
 *  0b011..512
 *  0b100..1024
 *  0b101..2048
 */
#define AFE_CFR_DEC_OSR(x)                       (((uint32_t)(((uint32_t)(x)) << AFE_CFR_DEC_OSR_SHIFT)) & AFE_CFR_DEC_OSR_MASK)
/*! @} */

/* The count of AFE_CFR */
#define AFE_CFR_COUNT                            (4U)

/*! @name CR - Control Register */
/*! @{ */

#define AFE_CR_STRTUP_CNT_MASK                   (0xFE00U)
#define AFE_CR_STRTUP_CNT_SHIFT                  (9U)
/*! STRTUP_CNT - Start up count
 */
#define AFE_CR_STRTUP_CNT(x)                     (((uint32_t)(((uint32_t)(x)) << AFE_CR_STRTUP_CNT_SHIFT)) & AFE_CR_STRTUP_CNT_MASK)

#define AFE_CR_RESULT_FORMAT_MASK                (0x40000U)
#define AFE_CR_RESULT_FORMAT_SHIFT               (18U)
/*! RESULT_FORMAT - Result Format
 *  0b0..Left justified 2's complement 32-bit : SVVVVVVVVVVVVVVVVVVVVVVV00000000 where (S= sign bit , V=valid result value, 0=zero)
 *  0b1..Right justified 2's complement 32-bit : SSSSSSSSSVVVVVVVVVVVVVVVVVVVVVVV where (S= sign bit , V= valid result value, 0= zero)
 */
#define AFE_CR_RESULT_FORMAT(x)                  (((uint32_t)(((uint32_t)(x)) << AFE_CR_RESULT_FORMAT_SHIFT)) & AFE_CR_RESULT_FORMAT_MASK)

#define AFE_CR_DLY_OK_MASK                       (0x200000U)
#define AFE_CR_DLY_OK_SHIFT                      (21U)
/*! DLY_OK - Delay OK
 */
#define AFE_CR_DLY_OK(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_CR_DLY_OK_SHIFT)) & AFE_CR_DLY_OK_MASK)

#define AFE_CR_RST_B_MASK                        (0x400000U)
#define AFE_CR_RST_B_SHIFT                       (22U)
/*! RST_B - Software Reset
 *  0b0..All ADCs, PGAs and Decimation filters are disabled. Clock Configuration bits will be reset.
 *  0b1...= All ADCs, PGAs and Decimation filters are enabled.
 */
#define AFE_CR_RST_B(x)                          (((uint32_t)(((uint32_t)(x)) << AFE_CR_RST_B_SHIFT)) & AFE_CR_RST_B_MASK)

#define AFE_CR_LPM_EN_MASK                       (0x2000000U)
#define AFE_CR_LPM_EN_SHIFT                      (25U)
/*! LPM_EN - Low power Mode enable
 *  0b0..AFE will be in normal mode
 *  0b1..AFE will be in low power mode. Setting this bit reduce the current consumption of ADC and Buffer
 *       Amplifier , the max modulator clock frequency is below 1Mhz.
 */
#define AFE_CR_LPM_EN(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_CR_LPM_EN_SHIFT)) & AFE_CR_LPM_EN_MASK)

#define AFE_CR_SOFT_TRG3_MASK                    (0x8000000U)
#define AFE_CR_SOFT_TRG3_SHIFT                   (27U)
/*! SOFT_TRG3 - Software Trigger3
 */
#define AFE_CR_SOFT_TRG3(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_CR_SOFT_TRG3_SHIFT)) & AFE_CR_SOFT_TRG3_MASK)

#define AFE_CR_SOFT_TRG2_MASK                    (0x10000000U)
#define AFE_CR_SOFT_TRG2_SHIFT                   (28U)
/*! SOFT_TRG2 - Software Trigger2
 */
#define AFE_CR_SOFT_TRG2(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_CR_SOFT_TRG2_SHIFT)) & AFE_CR_SOFT_TRG2_MASK)

#define AFE_CR_SOFT_TRG1_MASK                    (0x20000000U)
#define AFE_CR_SOFT_TRG1_SHIFT                   (29U)
/*! SOFT_TRG1 - Software Trigger1
 */
#define AFE_CR_SOFT_TRG1(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_CR_SOFT_TRG1_SHIFT)) & AFE_CR_SOFT_TRG1_MASK)

#define AFE_CR_SOFT_TRG0_MASK                    (0x40000000U)
#define AFE_CR_SOFT_TRG0_SHIFT                   (30U)
/*! SOFT_TRG0 - Software Trigger0
 */
#define AFE_CR_SOFT_TRG0(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_CR_SOFT_TRG0_SHIFT)) & AFE_CR_SOFT_TRG0_MASK)

#define AFE_CR_MSTR_EN_MASK                      (0x80000000U)
#define AFE_CR_MSTR_EN_SHIFT                     (31U)
/*! MSTR_EN - AFE Master Enable
 *  0b0..All ADCs are disabled.
 *  0b1..All ADCs and filters will get simultaneously enabled .
 */
#define AFE_CR_MSTR_EN(x)                        (((uint32_t)(((uint32_t)(x)) << AFE_CR_MSTR_EN_SHIFT)) & AFE_CR_MSTR_EN_MASK)
/*! @} */

/*! @name CKR - Clock Configuration Register */
/*! @{ */

#define AFE_CKR_CLS_MASK                         (0x600000U)
#define AFE_CKR_CLS_SHIFT                        (21U)
/*! CLS - Clock Source Select
 *  0b00..mod_clk0
 *  0b01..mod_clk1
 *  0b10..mod_clk2
 *  0b11..mod_clk3
 */
#define AFE_CKR_CLS(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_CKR_CLS_SHIFT)) & AFE_CKR_CLS_MASK)

#define AFE_CKR_DIV_MASK                         (0xF0000000U)
#define AFE_CKR_DIV_SHIFT                        (28U)
/*! DIV - Clock Divider Select
 *  0b0000..divide by 1
 *  0b0001..divide by 2 (default)
 *  0b0010..divide by 4
 *  0b0011..divide by 8
 *  0b0100..divide by 16
 *  0b0101..divide by 32
 *  0b0110..divide by 64
 *  0b0111..divide by 128
 *  0b1xxx..divide by 256
 */
#define AFE_CKR_DIV(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_CKR_DIV_SHIFT)) & AFE_CKR_DIV_MASK)
/*! @} */

/*! @name DI - DMA and Interrupt Register */
/*! @{ */

#define AFE_DI_INTEN3_MASK                       (0x800000U)
#define AFE_DI_INTEN3_SHIFT                      (23U)
/*! INTEN3 - Interrupt Enable 3
 */
#define AFE_DI_INTEN3(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_INTEN3_SHIFT)) & AFE_DI_INTEN3_MASK)

#define AFE_DI_INTEN2_MASK                       (0x1000000U)
#define AFE_DI_INTEN2_SHIFT                      (24U)
/*! INTEN2 - Interrupt Enable 2
 */
#define AFE_DI_INTEN2(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_INTEN2_SHIFT)) & AFE_DI_INTEN2_MASK)

#define AFE_DI_INTEN1_MASK                       (0x2000000U)
#define AFE_DI_INTEN1_SHIFT                      (25U)
/*! INTEN1 - Interrupt Enable 1
 */
#define AFE_DI_INTEN1(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_INTEN1_SHIFT)) & AFE_DI_INTEN1_MASK)

#define AFE_DI_INTEN0_MASK                       (0x4000000U)
#define AFE_DI_INTEN0_SHIFT                      (26U)
/*! INTEN0 - Interrupt Enable 0
 */
#define AFE_DI_INTEN0(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_INTEN0_SHIFT)) & AFE_DI_INTEN0_MASK)

#define AFE_DI_DMAEN3_MASK                       (0x10000000U)
#define AFE_DI_DMAEN3_SHIFT                      (28U)
/*! DMAEN3 - DMA Enable3
 */
#define AFE_DI_DMAEN3(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_DMAEN3_SHIFT)) & AFE_DI_DMAEN3_MASK)

#define AFE_DI_DMAEN2_MASK                       (0x20000000U)
#define AFE_DI_DMAEN2_SHIFT                      (29U)
/*! DMAEN2 - DMA Enable2
 */
#define AFE_DI_DMAEN2(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_DMAEN2_SHIFT)) & AFE_DI_DMAEN2_MASK)

#define AFE_DI_DMAEN1_MASK                       (0x40000000U)
#define AFE_DI_DMAEN1_SHIFT                      (30U)
/*! DMAEN1 - DMA Enable1
 */
#define AFE_DI_DMAEN1(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_DMAEN1_SHIFT)) & AFE_DI_DMAEN1_MASK)

#define AFE_DI_DMAEN0_MASK                       (0x80000000U)
#define AFE_DI_DMAEN0_SHIFT                      (31U)
/*! DMAEN0 - DMA Enable0
 */
#define AFE_DI_DMAEN0(x)                         (((uint32_t)(((uint32_t)(x)) << AFE_DI_DMAEN0_SHIFT)) & AFE_DI_DMAEN0_MASK)
/*! @} */

/*! @name DR - Channel0 Delay Register..Channel3 Delay Register */
/*! @{ */

#define AFE_DR_DLY_MASK                          (0x7FFU)
#define AFE_DR_DLY_SHIFT                         (0U)
/*! DLY - Delay
 */
#define AFE_DR_DLY(x)                            (((uint32_t)(((uint32_t)(x)) << AFE_DR_DLY_SHIFT)) & AFE_DR_DLY_MASK)
/*! @} */

/* The count of AFE_DR */
#define AFE_DR_COUNT                             (4U)

/*! @name RR - Channel0 Result Register..Channel3 Result Register */
/*! @{ */

#define AFE_RR_SDR_MASK                          (0x7FFFFFU)
#define AFE_RR_SDR_SHIFT                         (0U)
/*! SDR - Sample Data result
 */
#define AFE_RR_SDR(x)                            (((uint32_t)(((uint32_t)(x)) << AFE_RR_SDR_SHIFT)) & AFE_RR_SDR_MASK)

#define AFE_RR_SIGN_BITS_MASK                    (0xFF800000U)
#define AFE_RR_SIGN_BITS_SHIFT                   (23U)
/*! SIGN_BITS - Sign Bits
 */
#define AFE_RR_SIGN_BITS(x)                      (((uint32_t)(((uint32_t)(x)) << AFE_RR_SIGN_BITS_SHIFT)) & AFE_RR_SIGN_BITS_MASK)
/*! @} */

/* The count of AFE_RR */
#define AFE_RR_COUNT                             (4U)

/*! @name SR - Status Register */
/*! @{ */

#define AFE_SR_RDY3_MASK                         (0x10000U)
#define AFE_SR_RDY3_SHIFT                        (16U)
/*! RDY3 - AFE Ready4
 *  0b0..AFE Channel3 is disabled or has not completed its start up period
 *  0b1..AFE Channel3 is ready to initiate conversions.
 */
#define AFE_SR_RDY3(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_RDY3_SHIFT)) & AFE_SR_RDY3_MASK)

#define AFE_SR_RDY2_MASK                         (0x20000U)
#define AFE_SR_RDY2_SHIFT                        (17U)
/*! RDY2 - AFE Ready3
 *  0b0..AFE Channel2 is disabled or has not completed its start up period
 *  0b1..AFE Channel2 is ready to initiate conversions.
 */
#define AFE_SR_RDY2(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_RDY2_SHIFT)) & AFE_SR_RDY2_MASK)

#define AFE_SR_RDY1_MASK                         (0x40000U)
#define AFE_SR_RDY1_SHIFT                        (18U)
/*! RDY1 - AFE Ready2
 *  0b0..AFE Channel1 is disabled or has not completed its start up period
 *  0b1..AFE Channel1 is ready to initiate conversions.
 */
#define AFE_SR_RDY1(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_RDY1_SHIFT)) & AFE_SR_RDY1_MASK)

#define AFE_SR_RDY0_MASK                         (0x80000U)
#define AFE_SR_RDY0_SHIFT                        (19U)
/*! RDY0 - AFE Ready1
 *  0b0..AFE Channel0 is disabled or has not completed its start up period
 *  0b1..AFE Channel0 is ready to initiate conversions.
 */
#define AFE_SR_RDY0(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_RDY0_SHIFT)) & AFE_SR_RDY0_MASK)

#define AFE_SR_OVR3_MASK                         (0x200000U)
#define AFE_SR_OVR3_SHIFT                        (21U)
/*! OVR3 - Overflow Flag
 */
#define AFE_SR_OVR3(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_OVR3_SHIFT)) & AFE_SR_OVR3_MASK)

#define AFE_SR_OVR2_MASK                         (0x400000U)
#define AFE_SR_OVR2_SHIFT                        (22U)
/*! OVR2 - Overflow Flag
 */
#define AFE_SR_OVR2(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_OVR2_SHIFT)) & AFE_SR_OVR2_MASK)

#define AFE_SR_OVR1_MASK                         (0x800000U)
#define AFE_SR_OVR1_SHIFT                        (23U)
/*! OVR1 - Overflow Flag
 */
#define AFE_SR_OVR1(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_OVR1_SHIFT)) & AFE_SR_OVR1_MASK)

#define AFE_SR_OVR0_MASK                         (0x1000000U)
#define AFE_SR_OVR0_SHIFT                        (24U)
/*! OVR0 - Overflow Flag
 */
#define AFE_SR_OVR0(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_OVR0_SHIFT)) & AFE_SR_OVR0_MASK)

#define AFE_SR_COC3_MASK                         (0x10000000U)
#define AFE_SR_COC3_SHIFT                        (28U)
/*! COC3 - Conversion Complete
 */
#define AFE_SR_COC3(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_COC3_SHIFT)) & AFE_SR_COC3_MASK)

#define AFE_SR_COC2_MASK                         (0x20000000U)
#define AFE_SR_COC2_SHIFT                        (29U)
/*! COC2 - Conversion Complete
 */
#define AFE_SR_COC2(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_COC2_SHIFT)) & AFE_SR_COC2_MASK)

#define AFE_SR_COC1_MASK                         (0x40000000U)
#define AFE_SR_COC1_SHIFT                        (30U)
/*! COC1 - Conversion Complete
 */
#define AFE_SR_COC1(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_COC1_SHIFT)) & AFE_SR_COC1_MASK)

#define AFE_SR_COC0_MASK                         (0x80000000U)
#define AFE_SR_COC0_SHIFT                        (31U)
/*! COC0 - Conversion Complete
 */
#define AFE_SR_COC0(x)                           (((uint32_t)(((uint32_t)(x)) << AFE_SR_COC0_SHIFT)) & AFE_SR_COC0_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group AFE_Register_Masks */


/* AFE - Peripheral instance base addresses */
/** Peripheral AFE base address */
#define AFE_BASE                                 (0x40030000u)
/** Peripheral AFE base pointer */
#define AFE                                      ((AFE_Type *)AFE_BASE)
/** Array initializer of AFE peripheral base addresses */
#define AFE_BASE_ADDRS                           { AFE_BASE }
/** Array initializer of AFE peripheral base pointers */
#define AFE_BASE_PTRS                            { AFE }
/** Interrupt vectors for the AFE peripheral type */
#define AFE_IRQS                                 { { AFE_CH0_IRQn, AFE_CH1_IRQn, AFE_CH2_IRQn, AFE_CH3_IRQn } }

/*!
 * @}
 */ /* end of group AFE_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- AIPS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Peripheral_Access_Layer AIPS Peripheral Access Layer
 * @{
 */

/** AIPS - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[32];
  __IO uint32_t PACRA;                             /**< Peripheral Access Control Register, offset: 0x20 */
  __IO uint32_t PACRB;                             /**< Peripheral Access Control Register, offset: 0x24 */
       uint8_t RESERVED_1[24];
  __IO uint32_t PACRE;                             /**< Peripheral Access Control Register, offset: 0x40 */
  __IO uint32_t PACRF;                             /**< Peripheral Access Control Register, offset: 0x44 */
  __IO uint32_t PACRG;                             /**< Peripheral Access Control Register, offset: 0x48 */
  __IO uint32_t PACRH;                             /**< Peripheral Access Control Register, offset: 0x4C */
  __IO uint32_t PACRI;                             /**< Peripheral Access Control Register, offset: 0x50 */
  __IO uint32_t PACRJ;                             /**< Peripheral Access Control Register, offset: 0x54 */
  __IO uint32_t PACRK;                             /**< Peripheral Access Control Register, offset: 0x58 */
  __IO uint32_t PACRL;                             /**< Peripheral Access Control Register, offset: 0x5C */
  __IO uint32_t PACRM;                             /**< Peripheral Access Control Register, offset: 0x60 */
  __IO uint32_t PACRN;                             /**< Peripheral Access Control Register, offset: 0x64 */
  __IO uint32_t PACRO;                             /**< Peripheral Access Control Register, offset: 0x68 */
  __IO uint32_t PACRP;                             /**< Peripheral Access Control Register, offset: 0x6C */
} AIPS_Type;

/* ----------------------------------------------------------------------------
   -- AIPS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup AIPS_Register_Masks AIPS Register Masks
 * @{
 */

/*! @name PACRA - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRA_AC7_MASK                      (0x7U)
#define AIPS_PACRA_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRA_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC7_SHIFT)) & AIPS_PACRA_AC7_MASK)

#define AIPS_PACRA_RO7_MASK                      (0x8U)
#define AIPS_PACRA_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO7_SHIFT)) & AIPS_PACRA_RO7_MASK)

#define AIPS_PACRA_AC6_MASK                      (0x70U)
#define AIPS_PACRA_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRA_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC6_SHIFT)) & AIPS_PACRA_AC6_MASK)

#define AIPS_PACRA_RO6_MASK                      (0x80U)
#define AIPS_PACRA_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO6_SHIFT)) & AIPS_PACRA_RO6_MASK)

#define AIPS_PACRA_AC5_MASK                      (0x700U)
#define AIPS_PACRA_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRA_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC5_SHIFT)) & AIPS_PACRA_AC5_MASK)

#define AIPS_PACRA_RO5_MASK                      (0x800U)
#define AIPS_PACRA_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO5_SHIFT)) & AIPS_PACRA_RO5_MASK)

#define AIPS_PACRA_AC4_MASK                      (0x7000U)
#define AIPS_PACRA_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRA_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC4_SHIFT)) & AIPS_PACRA_AC4_MASK)

#define AIPS_PACRA_RO4_MASK                      (0x8000U)
#define AIPS_PACRA_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO4_SHIFT)) & AIPS_PACRA_RO4_MASK)

#define AIPS_PACRA_AC3_MASK                      (0x70000U)
#define AIPS_PACRA_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRA_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC3_SHIFT)) & AIPS_PACRA_AC3_MASK)

#define AIPS_PACRA_RO3_MASK                      (0x80000U)
#define AIPS_PACRA_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO3_SHIFT)) & AIPS_PACRA_RO3_MASK)

#define AIPS_PACRA_AC2_MASK                      (0x700000U)
#define AIPS_PACRA_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRA_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC2_SHIFT)) & AIPS_PACRA_AC2_MASK)

#define AIPS_PACRA_RO2_MASK                      (0x800000U)
#define AIPS_PACRA_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO2_SHIFT)) & AIPS_PACRA_RO2_MASK)

#define AIPS_PACRA_AC1_MASK                      (0x7000000U)
#define AIPS_PACRA_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRA_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC1_SHIFT)) & AIPS_PACRA_AC1_MASK)

#define AIPS_PACRA_RO1_MASK                      (0x8000000U)
#define AIPS_PACRA_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO1_SHIFT)) & AIPS_PACRA_RO1_MASK)

#define AIPS_PACRA_AC0_MASK                      (0x70000000U)
#define AIPS_PACRA_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRA_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_AC0_SHIFT)) & AIPS_PACRA_AC0_MASK)

#define AIPS_PACRA_RO0_MASK                      (0x80000000U)
#define AIPS_PACRA_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRA_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRA_RO0_SHIFT)) & AIPS_PACRA_RO0_MASK)
/*! @} */

/*! @name PACRB - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRB_AC7_MASK                      (0x7U)
#define AIPS_PACRB_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRB_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC7_SHIFT)) & AIPS_PACRB_AC7_MASK)

#define AIPS_PACRB_RO7_MASK                      (0x8U)
#define AIPS_PACRB_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO7_SHIFT)) & AIPS_PACRB_RO7_MASK)

#define AIPS_PACRB_AC6_MASK                      (0x70U)
#define AIPS_PACRB_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRB_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC6_SHIFT)) & AIPS_PACRB_AC6_MASK)

#define AIPS_PACRB_RO6_MASK                      (0x80U)
#define AIPS_PACRB_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO6_SHIFT)) & AIPS_PACRB_RO6_MASK)

#define AIPS_PACRB_AC5_MASK                      (0x700U)
#define AIPS_PACRB_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRB_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC5_SHIFT)) & AIPS_PACRB_AC5_MASK)

#define AIPS_PACRB_RO5_MASK                      (0x800U)
#define AIPS_PACRB_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO5_SHIFT)) & AIPS_PACRB_RO5_MASK)

#define AIPS_PACRB_AC4_MASK                      (0x7000U)
#define AIPS_PACRB_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRB_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC4_SHIFT)) & AIPS_PACRB_AC4_MASK)

#define AIPS_PACRB_RO4_MASK                      (0x8000U)
#define AIPS_PACRB_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO4_SHIFT)) & AIPS_PACRB_RO4_MASK)

#define AIPS_PACRB_AC3_MASK                      (0x70000U)
#define AIPS_PACRB_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRB_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC3_SHIFT)) & AIPS_PACRB_AC3_MASK)

#define AIPS_PACRB_RO3_MASK                      (0x80000U)
#define AIPS_PACRB_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO3_SHIFT)) & AIPS_PACRB_RO3_MASK)

#define AIPS_PACRB_AC2_MASK                      (0x700000U)
#define AIPS_PACRB_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRB_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC2_SHIFT)) & AIPS_PACRB_AC2_MASK)

#define AIPS_PACRB_RO2_MASK                      (0x800000U)
#define AIPS_PACRB_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO2_SHIFT)) & AIPS_PACRB_RO2_MASK)

#define AIPS_PACRB_AC1_MASK                      (0x7000000U)
#define AIPS_PACRB_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRB_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC1_SHIFT)) & AIPS_PACRB_AC1_MASK)

#define AIPS_PACRB_RO1_MASK                      (0x8000000U)
#define AIPS_PACRB_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO1_SHIFT)) & AIPS_PACRB_RO1_MASK)

#define AIPS_PACRB_AC0_MASK                      (0x70000000U)
#define AIPS_PACRB_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRB_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_AC0_SHIFT)) & AIPS_PACRB_AC0_MASK)

#define AIPS_PACRB_RO0_MASK                      (0x80000000U)
#define AIPS_PACRB_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRB_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRB_RO0_SHIFT)) & AIPS_PACRB_RO0_MASK)
/*! @} */

/*! @name PACRE - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRE_AC7_MASK                      (0x7U)
#define AIPS_PACRE_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRE_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC7_SHIFT)) & AIPS_PACRE_AC7_MASK)

#define AIPS_PACRE_RO7_MASK                      (0x8U)
#define AIPS_PACRE_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO7_SHIFT)) & AIPS_PACRE_RO7_MASK)

#define AIPS_PACRE_AC6_MASK                      (0x70U)
#define AIPS_PACRE_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRE_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC6_SHIFT)) & AIPS_PACRE_AC6_MASK)

#define AIPS_PACRE_RO6_MASK                      (0x80U)
#define AIPS_PACRE_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO6_SHIFT)) & AIPS_PACRE_RO6_MASK)

#define AIPS_PACRE_AC5_MASK                      (0x700U)
#define AIPS_PACRE_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRE_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC5_SHIFT)) & AIPS_PACRE_AC5_MASK)

#define AIPS_PACRE_RO5_MASK                      (0x800U)
#define AIPS_PACRE_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO5_SHIFT)) & AIPS_PACRE_RO5_MASK)

#define AIPS_PACRE_AC4_MASK                      (0x7000U)
#define AIPS_PACRE_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRE_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC4_SHIFT)) & AIPS_PACRE_AC4_MASK)

#define AIPS_PACRE_RO4_MASK                      (0x8000U)
#define AIPS_PACRE_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO4_SHIFT)) & AIPS_PACRE_RO4_MASK)

#define AIPS_PACRE_AC3_MASK                      (0x70000U)
#define AIPS_PACRE_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRE_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC3_SHIFT)) & AIPS_PACRE_AC3_MASK)

#define AIPS_PACRE_RO3_MASK                      (0x80000U)
#define AIPS_PACRE_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO3_SHIFT)) & AIPS_PACRE_RO3_MASK)

#define AIPS_PACRE_AC2_MASK                      (0x700000U)
#define AIPS_PACRE_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRE_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC2_SHIFT)) & AIPS_PACRE_AC2_MASK)

#define AIPS_PACRE_RO2_MASK                      (0x800000U)
#define AIPS_PACRE_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO2_SHIFT)) & AIPS_PACRE_RO2_MASK)

#define AIPS_PACRE_AC1_MASK                      (0x7000000U)
#define AIPS_PACRE_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRE_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC1_SHIFT)) & AIPS_PACRE_AC1_MASK)

#define AIPS_PACRE_RO1_MASK                      (0x8000000U)
#define AIPS_PACRE_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO1_SHIFT)) & AIPS_PACRE_RO1_MASK)

#define AIPS_PACRE_AC0_MASK                      (0x70000000U)
#define AIPS_PACRE_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRE_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_AC0_SHIFT)) & AIPS_PACRE_AC0_MASK)

#define AIPS_PACRE_RO0_MASK                      (0x80000000U)
#define AIPS_PACRE_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRE_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRE_RO0_SHIFT)) & AIPS_PACRE_RO0_MASK)
/*! @} */

/*! @name PACRF - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRF_AC7_MASK                      (0x7U)
#define AIPS_PACRF_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRF_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC7_SHIFT)) & AIPS_PACRF_AC7_MASK)

#define AIPS_PACRF_RO7_MASK                      (0x8U)
#define AIPS_PACRF_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO7_SHIFT)) & AIPS_PACRF_RO7_MASK)

#define AIPS_PACRF_AC6_MASK                      (0x70U)
#define AIPS_PACRF_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRF_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC6_SHIFT)) & AIPS_PACRF_AC6_MASK)

#define AIPS_PACRF_RO6_MASK                      (0x80U)
#define AIPS_PACRF_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO6_SHIFT)) & AIPS_PACRF_RO6_MASK)

#define AIPS_PACRF_AC5_MASK                      (0x700U)
#define AIPS_PACRF_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRF_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC5_SHIFT)) & AIPS_PACRF_AC5_MASK)

#define AIPS_PACRF_RO5_MASK                      (0x800U)
#define AIPS_PACRF_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO5_SHIFT)) & AIPS_PACRF_RO5_MASK)

#define AIPS_PACRF_AC4_MASK                      (0x7000U)
#define AIPS_PACRF_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRF_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC4_SHIFT)) & AIPS_PACRF_AC4_MASK)

#define AIPS_PACRF_RO4_MASK                      (0x8000U)
#define AIPS_PACRF_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO4_SHIFT)) & AIPS_PACRF_RO4_MASK)

#define AIPS_PACRF_AC3_MASK                      (0x70000U)
#define AIPS_PACRF_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRF_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC3_SHIFT)) & AIPS_PACRF_AC3_MASK)

#define AIPS_PACRF_RO3_MASK                      (0x80000U)
#define AIPS_PACRF_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO3_SHIFT)) & AIPS_PACRF_RO3_MASK)

#define AIPS_PACRF_AC2_MASK                      (0x700000U)
#define AIPS_PACRF_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRF_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC2_SHIFT)) & AIPS_PACRF_AC2_MASK)

#define AIPS_PACRF_RO2_MASK                      (0x800000U)
#define AIPS_PACRF_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO2_SHIFT)) & AIPS_PACRF_RO2_MASK)

#define AIPS_PACRF_AC1_MASK                      (0x7000000U)
#define AIPS_PACRF_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRF_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC1_SHIFT)) & AIPS_PACRF_AC1_MASK)

#define AIPS_PACRF_RO1_MASK                      (0x8000000U)
#define AIPS_PACRF_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO1_SHIFT)) & AIPS_PACRF_RO1_MASK)

#define AIPS_PACRF_AC0_MASK                      (0x70000000U)
#define AIPS_PACRF_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRF_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_AC0_SHIFT)) & AIPS_PACRF_AC0_MASK)

#define AIPS_PACRF_RO0_MASK                      (0x80000000U)
#define AIPS_PACRF_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRF_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRF_RO0_SHIFT)) & AIPS_PACRF_RO0_MASK)
/*! @} */

/*! @name PACRG - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRG_AC7_MASK                      (0x7U)
#define AIPS_PACRG_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRG_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC7_SHIFT)) & AIPS_PACRG_AC7_MASK)

#define AIPS_PACRG_RO7_MASK                      (0x8U)
#define AIPS_PACRG_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO7_SHIFT)) & AIPS_PACRG_RO7_MASK)

#define AIPS_PACRG_AC6_MASK                      (0x70U)
#define AIPS_PACRG_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRG_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC6_SHIFT)) & AIPS_PACRG_AC6_MASK)

#define AIPS_PACRG_RO6_MASK                      (0x80U)
#define AIPS_PACRG_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO6_SHIFT)) & AIPS_PACRG_RO6_MASK)

#define AIPS_PACRG_AC5_MASK                      (0x700U)
#define AIPS_PACRG_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRG_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC5_SHIFT)) & AIPS_PACRG_AC5_MASK)

#define AIPS_PACRG_RO5_MASK                      (0x800U)
#define AIPS_PACRG_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO5_SHIFT)) & AIPS_PACRG_RO5_MASK)

#define AIPS_PACRG_AC4_MASK                      (0x7000U)
#define AIPS_PACRG_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRG_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC4_SHIFT)) & AIPS_PACRG_AC4_MASK)

#define AIPS_PACRG_RO4_MASK                      (0x8000U)
#define AIPS_PACRG_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO4_SHIFT)) & AIPS_PACRG_RO4_MASK)

#define AIPS_PACRG_AC3_MASK                      (0x70000U)
#define AIPS_PACRG_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRG_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC3_SHIFT)) & AIPS_PACRG_AC3_MASK)

#define AIPS_PACRG_RO3_MASK                      (0x80000U)
#define AIPS_PACRG_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO3_SHIFT)) & AIPS_PACRG_RO3_MASK)

#define AIPS_PACRG_AC2_MASK                      (0x700000U)
#define AIPS_PACRG_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRG_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC2_SHIFT)) & AIPS_PACRG_AC2_MASK)

#define AIPS_PACRG_RO2_MASK                      (0x800000U)
#define AIPS_PACRG_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO2_SHIFT)) & AIPS_PACRG_RO2_MASK)

#define AIPS_PACRG_AC1_MASK                      (0x7000000U)
#define AIPS_PACRG_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRG_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC1_SHIFT)) & AIPS_PACRG_AC1_MASK)

#define AIPS_PACRG_RO1_MASK                      (0x8000000U)
#define AIPS_PACRG_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO1_SHIFT)) & AIPS_PACRG_RO1_MASK)

#define AIPS_PACRG_AC0_MASK                      (0x70000000U)
#define AIPS_PACRG_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRG_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_AC0_SHIFT)) & AIPS_PACRG_AC0_MASK)

#define AIPS_PACRG_RO0_MASK                      (0x80000000U)
#define AIPS_PACRG_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRG_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRG_RO0_SHIFT)) & AIPS_PACRG_RO0_MASK)
/*! @} */

/*! @name PACRH - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRH_AC7_MASK                      (0x7U)
#define AIPS_PACRH_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRH_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC7_SHIFT)) & AIPS_PACRH_AC7_MASK)

#define AIPS_PACRH_RO7_MASK                      (0x8U)
#define AIPS_PACRH_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO7_SHIFT)) & AIPS_PACRH_RO7_MASK)

#define AIPS_PACRH_AC6_MASK                      (0x70U)
#define AIPS_PACRH_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRH_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC6_SHIFT)) & AIPS_PACRH_AC6_MASK)

#define AIPS_PACRH_RO6_MASK                      (0x80U)
#define AIPS_PACRH_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO6_SHIFT)) & AIPS_PACRH_RO6_MASK)

#define AIPS_PACRH_AC5_MASK                      (0x700U)
#define AIPS_PACRH_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRH_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC5_SHIFT)) & AIPS_PACRH_AC5_MASK)

#define AIPS_PACRH_RO5_MASK                      (0x800U)
#define AIPS_PACRH_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO5_SHIFT)) & AIPS_PACRH_RO5_MASK)

#define AIPS_PACRH_AC4_MASK                      (0x7000U)
#define AIPS_PACRH_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRH_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC4_SHIFT)) & AIPS_PACRH_AC4_MASK)

#define AIPS_PACRH_RO4_MASK                      (0x8000U)
#define AIPS_PACRH_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO4_SHIFT)) & AIPS_PACRH_RO4_MASK)

#define AIPS_PACRH_AC3_MASK                      (0x70000U)
#define AIPS_PACRH_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRH_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC3_SHIFT)) & AIPS_PACRH_AC3_MASK)

#define AIPS_PACRH_RO3_MASK                      (0x80000U)
#define AIPS_PACRH_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO3_SHIFT)) & AIPS_PACRH_RO3_MASK)

#define AIPS_PACRH_AC2_MASK                      (0x700000U)
#define AIPS_PACRH_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRH_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC2_SHIFT)) & AIPS_PACRH_AC2_MASK)

#define AIPS_PACRH_RO2_MASK                      (0x800000U)
#define AIPS_PACRH_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO2_SHIFT)) & AIPS_PACRH_RO2_MASK)

#define AIPS_PACRH_AC1_MASK                      (0x7000000U)
#define AIPS_PACRH_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRH_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC1_SHIFT)) & AIPS_PACRH_AC1_MASK)

#define AIPS_PACRH_RO1_MASK                      (0x8000000U)
#define AIPS_PACRH_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO1_SHIFT)) & AIPS_PACRH_RO1_MASK)

#define AIPS_PACRH_AC0_MASK                      (0x70000000U)
#define AIPS_PACRH_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRH_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_AC0_SHIFT)) & AIPS_PACRH_AC0_MASK)

#define AIPS_PACRH_RO0_MASK                      (0x80000000U)
#define AIPS_PACRH_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRH_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRH_RO0_SHIFT)) & AIPS_PACRH_RO0_MASK)
/*! @} */

/*! @name PACRI - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRI_AC7_MASK                      (0x7U)
#define AIPS_PACRI_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRI_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC7_SHIFT)) & AIPS_PACRI_AC7_MASK)

#define AIPS_PACRI_RO7_MASK                      (0x8U)
#define AIPS_PACRI_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO7_SHIFT)) & AIPS_PACRI_RO7_MASK)

#define AIPS_PACRI_AC6_MASK                      (0x70U)
#define AIPS_PACRI_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRI_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC6_SHIFT)) & AIPS_PACRI_AC6_MASK)

#define AIPS_PACRI_RO6_MASK                      (0x80U)
#define AIPS_PACRI_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO6_SHIFT)) & AIPS_PACRI_RO6_MASK)

#define AIPS_PACRI_AC5_MASK                      (0x700U)
#define AIPS_PACRI_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRI_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC5_SHIFT)) & AIPS_PACRI_AC5_MASK)

#define AIPS_PACRI_RO5_MASK                      (0x800U)
#define AIPS_PACRI_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO5_SHIFT)) & AIPS_PACRI_RO5_MASK)

#define AIPS_PACRI_AC4_MASK                      (0x7000U)
#define AIPS_PACRI_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRI_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC4_SHIFT)) & AIPS_PACRI_AC4_MASK)

#define AIPS_PACRI_RO4_MASK                      (0x8000U)
#define AIPS_PACRI_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO4_SHIFT)) & AIPS_PACRI_RO4_MASK)

#define AIPS_PACRI_AC3_MASK                      (0x70000U)
#define AIPS_PACRI_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRI_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC3_SHIFT)) & AIPS_PACRI_AC3_MASK)

#define AIPS_PACRI_RO3_MASK                      (0x80000U)
#define AIPS_PACRI_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO3_SHIFT)) & AIPS_PACRI_RO3_MASK)

#define AIPS_PACRI_AC2_MASK                      (0x700000U)
#define AIPS_PACRI_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRI_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC2_SHIFT)) & AIPS_PACRI_AC2_MASK)

#define AIPS_PACRI_RO2_MASK                      (0x800000U)
#define AIPS_PACRI_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO2_SHIFT)) & AIPS_PACRI_RO2_MASK)

#define AIPS_PACRI_AC1_MASK                      (0x7000000U)
#define AIPS_PACRI_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRI_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC1_SHIFT)) & AIPS_PACRI_AC1_MASK)

#define AIPS_PACRI_RO1_MASK                      (0x8000000U)
#define AIPS_PACRI_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO1_SHIFT)) & AIPS_PACRI_RO1_MASK)

#define AIPS_PACRI_AC0_MASK                      (0x70000000U)
#define AIPS_PACRI_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRI_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_AC0_SHIFT)) & AIPS_PACRI_AC0_MASK)

#define AIPS_PACRI_RO0_MASK                      (0x80000000U)
#define AIPS_PACRI_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRI_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRI_RO0_SHIFT)) & AIPS_PACRI_RO0_MASK)
/*! @} */

/*! @name PACRJ - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRJ_AC7_MASK                      (0x7U)
#define AIPS_PACRJ_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRJ_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC7_SHIFT)) & AIPS_PACRJ_AC7_MASK)

#define AIPS_PACRJ_RO7_MASK                      (0x8U)
#define AIPS_PACRJ_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO7_SHIFT)) & AIPS_PACRJ_RO7_MASK)

#define AIPS_PACRJ_AC6_MASK                      (0x70U)
#define AIPS_PACRJ_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRJ_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC6_SHIFT)) & AIPS_PACRJ_AC6_MASK)

#define AIPS_PACRJ_RO6_MASK                      (0x80U)
#define AIPS_PACRJ_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO6_SHIFT)) & AIPS_PACRJ_RO6_MASK)

#define AIPS_PACRJ_AC5_MASK                      (0x700U)
#define AIPS_PACRJ_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRJ_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC5_SHIFT)) & AIPS_PACRJ_AC5_MASK)

#define AIPS_PACRJ_RO5_MASK                      (0x800U)
#define AIPS_PACRJ_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO5_SHIFT)) & AIPS_PACRJ_RO5_MASK)

#define AIPS_PACRJ_AC4_MASK                      (0x7000U)
#define AIPS_PACRJ_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRJ_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC4_SHIFT)) & AIPS_PACRJ_AC4_MASK)

#define AIPS_PACRJ_RO4_MASK                      (0x8000U)
#define AIPS_PACRJ_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO4_SHIFT)) & AIPS_PACRJ_RO4_MASK)

#define AIPS_PACRJ_AC3_MASK                      (0x70000U)
#define AIPS_PACRJ_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRJ_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC3_SHIFT)) & AIPS_PACRJ_AC3_MASK)

#define AIPS_PACRJ_RO3_MASK                      (0x80000U)
#define AIPS_PACRJ_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO3_SHIFT)) & AIPS_PACRJ_RO3_MASK)

#define AIPS_PACRJ_AC2_MASK                      (0x700000U)
#define AIPS_PACRJ_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRJ_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC2_SHIFT)) & AIPS_PACRJ_AC2_MASK)

#define AIPS_PACRJ_RO2_MASK                      (0x800000U)
#define AIPS_PACRJ_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO2_SHIFT)) & AIPS_PACRJ_RO2_MASK)

#define AIPS_PACRJ_AC1_MASK                      (0x7000000U)
#define AIPS_PACRJ_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRJ_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC1_SHIFT)) & AIPS_PACRJ_AC1_MASK)

#define AIPS_PACRJ_RO1_MASK                      (0x8000000U)
#define AIPS_PACRJ_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO1_SHIFT)) & AIPS_PACRJ_RO1_MASK)

#define AIPS_PACRJ_AC0_MASK                      (0x70000000U)
#define AIPS_PACRJ_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRJ_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_AC0_SHIFT)) & AIPS_PACRJ_AC0_MASK)

#define AIPS_PACRJ_RO0_MASK                      (0x80000000U)
#define AIPS_PACRJ_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRJ_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRJ_RO0_SHIFT)) & AIPS_PACRJ_RO0_MASK)
/*! @} */

/*! @name PACRK - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRK_AC7_MASK                      (0x7U)
#define AIPS_PACRK_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRK_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC7_SHIFT)) & AIPS_PACRK_AC7_MASK)

#define AIPS_PACRK_RO7_MASK                      (0x8U)
#define AIPS_PACRK_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO7_SHIFT)) & AIPS_PACRK_RO7_MASK)

#define AIPS_PACRK_AC6_MASK                      (0x70U)
#define AIPS_PACRK_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRK_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC6_SHIFT)) & AIPS_PACRK_AC6_MASK)

#define AIPS_PACRK_RO6_MASK                      (0x80U)
#define AIPS_PACRK_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO6_SHIFT)) & AIPS_PACRK_RO6_MASK)

#define AIPS_PACRK_AC5_MASK                      (0x700U)
#define AIPS_PACRK_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRK_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC5_SHIFT)) & AIPS_PACRK_AC5_MASK)

#define AIPS_PACRK_RO5_MASK                      (0x800U)
#define AIPS_PACRK_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO5_SHIFT)) & AIPS_PACRK_RO5_MASK)

#define AIPS_PACRK_AC4_MASK                      (0x7000U)
#define AIPS_PACRK_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRK_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC4_SHIFT)) & AIPS_PACRK_AC4_MASK)

#define AIPS_PACRK_RO4_MASK                      (0x8000U)
#define AIPS_PACRK_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO4_SHIFT)) & AIPS_PACRK_RO4_MASK)

#define AIPS_PACRK_AC3_MASK                      (0x70000U)
#define AIPS_PACRK_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRK_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC3_SHIFT)) & AIPS_PACRK_AC3_MASK)

#define AIPS_PACRK_RO3_MASK                      (0x80000U)
#define AIPS_PACRK_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO3_SHIFT)) & AIPS_PACRK_RO3_MASK)

#define AIPS_PACRK_AC2_MASK                      (0x700000U)
#define AIPS_PACRK_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRK_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC2_SHIFT)) & AIPS_PACRK_AC2_MASK)

#define AIPS_PACRK_RO2_MASK                      (0x800000U)
#define AIPS_PACRK_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO2_SHIFT)) & AIPS_PACRK_RO2_MASK)

#define AIPS_PACRK_AC1_MASK                      (0x7000000U)
#define AIPS_PACRK_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRK_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC1_SHIFT)) & AIPS_PACRK_AC1_MASK)

#define AIPS_PACRK_RO1_MASK                      (0x8000000U)
#define AIPS_PACRK_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO1_SHIFT)) & AIPS_PACRK_RO1_MASK)

#define AIPS_PACRK_AC0_MASK                      (0x70000000U)
#define AIPS_PACRK_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRK_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_AC0_SHIFT)) & AIPS_PACRK_AC0_MASK)

#define AIPS_PACRK_RO0_MASK                      (0x80000000U)
#define AIPS_PACRK_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRK_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRK_RO0_SHIFT)) & AIPS_PACRK_RO0_MASK)
/*! @} */

/*! @name PACRL - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRL_AC7_MASK                      (0x7U)
#define AIPS_PACRL_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRL_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC7_SHIFT)) & AIPS_PACRL_AC7_MASK)

#define AIPS_PACRL_RO7_MASK                      (0x8U)
#define AIPS_PACRL_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO7_SHIFT)) & AIPS_PACRL_RO7_MASK)

#define AIPS_PACRL_AC6_MASK                      (0x70U)
#define AIPS_PACRL_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRL_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC6_SHIFT)) & AIPS_PACRL_AC6_MASK)

#define AIPS_PACRL_RO6_MASK                      (0x80U)
#define AIPS_PACRL_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO6_SHIFT)) & AIPS_PACRL_RO6_MASK)

#define AIPS_PACRL_AC5_MASK                      (0x700U)
#define AIPS_PACRL_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRL_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC5_SHIFT)) & AIPS_PACRL_AC5_MASK)

#define AIPS_PACRL_RO5_MASK                      (0x800U)
#define AIPS_PACRL_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO5_SHIFT)) & AIPS_PACRL_RO5_MASK)

#define AIPS_PACRL_AC4_MASK                      (0x7000U)
#define AIPS_PACRL_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRL_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC4_SHIFT)) & AIPS_PACRL_AC4_MASK)

#define AIPS_PACRL_RO4_MASK                      (0x8000U)
#define AIPS_PACRL_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO4_SHIFT)) & AIPS_PACRL_RO4_MASK)

#define AIPS_PACRL_AC3_MASK                      (0x70000U)
#define AIPS_PACRL_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRL_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC3_SHIFT)) & AIPS_PACRL_AC3_MASK)

#define AIPS_PACRL_RO3_MASK                      (0x80000U)
#define AIPS_PACRL_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO3_SHIFT)) & AIPS_PACRL_RO3_MASK)

#define AIPS_PACRL_AC2_MASK                      (0x700000U)
#define AIPS_PACRL_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRL_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC2_SHIFT)) & AIPS_PACRL_AC2_MASK)

#define AIPS_PACRL_RO2_MASK                      (0x800000U)
#define AIPS_PACRL_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO2_SHIFT)) & AIPS_PACRL_RO2_MASK)

#define AIPS_PACRL_AC1_MASK                      (0x7000000U)
#define AIPS_PACRL_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRL_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC1_SHIFT)) & AIPS_PACRL_AC1_MASK)

#define AIPS_PACRL_RO1_MASK                      (0x8000000U)
#define AIPS_PACRL_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO1_SHIFT)) & AIPS_PACRL_RO1_MASK)

#define AIPS_PACRL_AC0_MASK                      (0x70000000U)
#define AIPS_PACRL_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRL_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_AC0_SHIFT)) & AIPS_PACRL_AC0_MASK)

#define AIPS_PACRL_RO0_MASK                      (0x80000000U)
#define AIPS_PACRL_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRL_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRL_RO0_SHIFT)) & AIPS_PACRL_RO0_MASK)
/*! @} */

/*! @name PACRM - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRM_AC7_MASK                      (0x7U)
#define AIPS_PACRM_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRM_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC7_SHIFT)) & AIPS_PACRM_AC7_MASK)

#define AIPS_PACRM_RO7_MASK                      (0x8U)
#define AIPS_PACRM_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO7_SHIFT)) & AIPS_PACRM_RO7_MASK)

#define AIPS_PACRM_AC6_MASK                      (0x70U)
#define AIPS_PACRM_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRM_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC6_SHIFT)) & AIPS_PACRM_AC6_MASK)

#define AIPS_PACRM_RO6_MASK                      (0x80U)
#define AIPS_PACRM_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO6_SHIFT)) & AIPS_PACRM_RO6_MASK)

#define AIPS_PACRM_AC5_MASK                      (0x700U)
#define AIPS_PACRM_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRM_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC5_SHIFT)) & AIPS_PACRM_AC5_MASK)

#define AIPS_PACRM_RO5_MASK                      (0x800U)
#define AIPS_PACRM_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO5_SHIFT)) & AIPS_PACRM_RO5_MASK)

#define AIPS_PACRM_AC4_MASK                      (0x7000U)
#define AIPS_PACRM_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRM_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC4_SHIFT)) & AIPS_PACRM_AC4_MASK)

#define AIPS_PACRM_RO4_MASK                      (0x8000U)
#define AIPS_PACRM_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO4_SHIFT)) & AIPS_PACRM_RO4_MASK)

#define AIPS_PACRM_AC3_MASK                      (0x70000U)
#define AIPS_PACRM_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRM_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC3_SHIFT)) & AIPS_PACRM_AC3_MASK)

#define AIPS_PACRM_RO3_MASK                      (0x80000U)
#define AIPS_PACRM_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO3_SHIFT)) & AIPS_PACRM_RO3_MASK)

#define AIPS_PACRM_AC2_MASK                      (0x700000U)
#define AIPS_PACRM_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRM_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC2_SHIFT)) & AIPS_PACRM_AC2_MASK)

#define AIPS_PACRM_RO2_MASK                      (0x800000U)
#define AIPS_PACRM_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO2_SHIFT)) & AIPS_PACRM_RO2_MASK)

#define AIPS_PACRM_AC1_MASK                      (0x7000000U)
#define AIPS_PACRM_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRM_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC1_SHIFT)) & AIPS_PACRM_AC1_MASK)

#define AIPS_PACRM_RO1_MASK                      (0x8000000U)
#define AIPS_PACRM_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO1_SHIFT)) & AIPS_PACRM_RO1_MASK)

#define AIPS_PACRM_AC0_MASK                      (0x70000000U)
#define AIPS_PACRM_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRM_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_AC0_SHIFT)) & AIPS_PACRM_AC0_MASK)

#define AIPS_PACRM_RO0_MASK                      (0x80000000U)
#define AIPS_PACRM_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRM_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRM_RO0_SHIFT)) & AIPS_PACRM_RO0_MASK)
/*! @} */

/*! @name PACRN - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRN_AC7_MASK                      (0x7U)
#define AIPS_PACRN_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRN_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC7_SHIFT)) & AIPS_PACRN_AC7_MASK)

#define AIPS_PACRN_RO7_MASK                      (0x8U)
#define AIPS_PACRN_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO7_SHIFT)) & AIPS_PACRN_RO7_MASK)

#define AIPS_PACRN_AC6_MASK                      (0x70U)
#define AIPS_PACRN_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRN_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC6_SHIFT)) & AIPS_PACRN_AC6_MASK)

#define AIPS_PACRN_RO6_MASK                      (0x80U)
#define AIPS_PACRN_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO6_SHIFT)) & AIPS_PACRN_RO6_MASK)

#define AIPS_PACRN_AC5_MASK                      (0x700U)
#define AIPS_PACRN_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRN_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC5_SHIFT)) & AIPS_PACRN_AC5_MASK)

#define AIPS_PACRN_RO5_MASK                      (0x800U)
#define AIPS_PACRN_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO5_SHIFT)) & AIPS_PACRN_RO5_MASK)

#define AIPS_PACRN_AC4_MASK                      (0x7000U)
#define AIPS_PACRN_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRN_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC4_SHIFT)) & AIPS_PACRN_AC4_MASK)

#define AIPS_PACRN_RO4_MASK                      (0x8000U)
#define AIPS_PACRN_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO4_SHIFT)) & AIPS_PACRN_RO4_MASK)

#define AIPS_PACRN_AC3_MASK                      (0x70000U)
#define AIPS_PACRN_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRN_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC3_SHIFT)) & AIPS_PACRN_AC3_MASK)

#define AIPS_PACRN_RO3_MASK                      (0x80000U)
#define AIPS_PACRN_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO3_SHIFT)) & AIPS_PACRN_RO3_MASK)

#define AIPS_PACRN_AC2_MASK                      (0x700000U)
#define AIPS_PACRN_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRN_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC2_SHIFT)) & AIPS_PACRN_AC2_MASK)

#define AIPS_PACRN_RO2_MASK                      (0x800000U)
#define AIPS_PACRN_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO2_SHIFT)) & AIPS_PACRN_RO2_MASK)

#define AIPS_PACRN_AC1_MASK                      (0x7000000U)
#define AIPS_PACRN_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRN_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC1_SHIFT)) & AIPS_PACRN_AC1_MASK)

#define AIPS_PACRN_RO1_MASK                      (0x8000000U)
#define AIPS_PACRN_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO1_SHIFT)) & AIPS_PACRN_RO1_MASK)

#define AIPS_PACRN_AC0_MASK                      (0x70000000U)
#define AIPS_PACRN_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRN_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_AC0_SHIFT)) & AIPS_PACRN_AC0_MASK)

#define AIPS_PACRN_RO0_MASK                      (0x80000000U)
#define AIPS_PACRN_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRN_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRN_RO0_SHIFT)) & AIPS_PACRN_RO0_MASK)
/*! @} */

/*! @name PACRO - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRO_AC7_MASK                      (0x7U)
#define AIPS_PACRO_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRO_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC7_SHIFT)) & AIPS_PACRO_AC7_MASK)

#define AIPS_PACRO_RO7_MASK                      (0x8U)
#define AIPS_PACRO_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO7_SHIFT)) & AIPS_PACRO_RO7_MASK)

#define AIPS_PACRO_AC6_MASK                      (0x70U)
#define AIPS_PACRO_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRO_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC6_SHIFT)) & AIPS_PACRO_AC6_MASK)

#define AIPS_PACRO_RO6_MASK                      (0x80U)
#define AIPS_PACRO_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO6_SHIFT)) & AIPS_PACRO_RO6_MASK)

#define AIPS_PACRO_AC5_MASK                      (0x700U)
#define AIPS_PACRO_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRO_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC5_SHIFT)) & AIPS_PACRO_AC5_MASK)

#define AIPS_PACRO_RO5_MASK                      (0x800U)
#define AIPS_PACRO_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO5_SHIFT)) & AIPS_PACRO_RO5_MASK)

#define AIPS_PACRO_AC4_MASK                      (0x7000U)
#define AIPS_PACRO_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRO_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC4_SHIFT)) & AIPS_PACRO_AC4_MASK)

#define AIPS_PACRO_RO4_MASK                      (0x8000U)
#define AIPS_PACRO_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO4_SHIFT)) & AIPS_PACRO_RO4_MASK)

#define AIPS_PACRO_AC3_MASK                      (0x70000U)
#define AIPS_PACRO_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRO_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC3_SHIFT)) & AIPS_PACRO_AC3_MASK)

#define AIPS_PACRO_RO3_MASK                      (0x80000U)
#define AIPS_PACRO_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO3_SHIFT)) & AIPS_PACRO_RO3_MASK)

#define AIPS_PACRO_AC2_MASK                      (0x700000U)
#define AIPS_PACRO_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRO_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC2_SHIFT)) & AIPS_PACRO_AC2_MASK)

#define AIPS_PACRO_RO2_MASK                      (0x800000U)
#define AIPS_PACRO_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO2_SHIFT)) & AIPS_PACRO_RO2_MASK)

#define AIPS_PACRO_AC1_MASK                      (0x7000000U)
#define AIPS_PACRO_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRO_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC1_SHIFT)) & AIPS_PACRO_AC1_MASK)

#define AIPS_PACRO_RO1_MASK                      (0x8000000U)
#define AIPS_PACRO_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO1_SHIFT)) & AIPS_PACRO_RO1_MASK)

#define AIPS_PACRO_AC0_MASK                      (0x70000000U)
#define AIPS_PACRO_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRO_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_AC0_SHIFT)) & AIPS_PACRO_AC0_MASK)

#define AIPS_PACRO_RO0_MASK                      (0x80000000U)
#define AIPS_PACRO_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRO_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRO_RO0_SHIFT)) & AIPS_PACRO_RO0_MASK)
/*! @} */

/*! @name PACRP - Peripheral Access Control Register */
/*! @{ */

#define AIPS_PACRP_AC7_MASK                      (0x7U)
#define AIPS_PACRP_AC7_SHIFT                     (0U)
/*! AC7 - Attribute Check
 */
#define AIPS_PACRP_AC7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC7_SHIFT)) & AIPS_PACRP_AC7_MASK)

#define AIPS_PACRP_RO7_MASK                      (0x8U)
#define AIPS_PACRP_RO7_SHIFT                     (3U)
/*! RO7 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO7(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO7_SHIFT)) & AIPS_PACRP_RO7_MASK)

#define AIPS_PACRP_AC6_MASK                      (0x70U)
#define AIPS_PACRP_AC6_SHIFT                     (4U)
/*! AC6 - Attribute Check
 */
#define AIPS_PACRP_AC6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC6_SHIFT)) & AIPS_PACRP_AC6_MASK)

#define AIPS_PACRP_RO6_MASK                      (0x80U)
#define AIPS_PACRP_RO6_SHIFT                     (7U)
/*! RO6 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO6(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO6_SHIFT)) & AIPS_PACRP_RO6_MASK)

#define AIPS_PACRP_AC5_MASK                      (0x700U)
#define AIPS_PACRP_AC5_SHIFT                     (8U)
/*! AC5 - Attribute Check
 */
#define AIPS_PACRP_AC5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC5_SHIFT)) & AIPS_PACRP_AC5_MASK)

#define AIPS_PACRP_RO5_MASK                      (0x800U)
#define AIPS_PACRP_RO5_SHIFT                     (11U)
/*! RO5 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO5(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO5_SHIFT)) & AIPS_PACRP_RO5_MASK)

#define AIPS_PACRP_AC4_MASK                      (0x7000U)
#define AIPS_PACRP_AC4_SHIFT                     (12U)
/*! AC4 - Attribute Check
 */
#define AIPS_PACRP_AC4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC4_SHIFT)) & AIPS_PACRP_AC4_MASK)

#define AIPS_PACRP_RO4_MASK                      (0x8000U)
#define AIPS_PACRP_RO4_SHIFT                     (15U)
/*! RO4 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO4(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO4_SHIFT)) & AIPS_PACRP_RO4_MASK)

#define AIPS_PACRP_AC3_MASK                      (0x70000U)
#define AIPS_PACRP_AC3_SHIFT                     (16U)
/*! AC3 - Attribute Check
 */
#define AIPS_PACRP_AC3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC3_SHIFT)) & AIPS_PACRP_AC3_MASK)

#define AIPS_PACRP_RO3_MASK                      (0x80000U)
#define AIPS_PACRP_RO3_SHIFT                     (19U)
/*! RO3 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO3(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO3_SHIFT)) & AIPS_PACRP_RO3_MASK)

#define AIPS_PACRP_AC2_MASK                      (0x700000U)
#define AIPS_PACRP_AC2_SHIFT                     (20U)
/*! AC2 - Attribute Check
 */
#define AIPS_PACRP_AC2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC2_SHIFT)) & AIPS_PACRP_AC2_MASK)

#define AIPS_PACRP_RO2_MASK                      (0x800000U)
#define AIPS_PACRP_RO2_SHIFT                     (23U)
/*! RO2 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO2(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO2_SHIFT)) & AIPS_PACRP_RO2_MASK)

#define AIPS_PACRP_AC1_MASK                      (0x7000000U)
#define AIPS_PACRP_AC1_SHIFT                     (24U)
/*! AC1 - Attribute Check
 */
#define AIPS_PACRP_AC1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC1_SHIFT)) & AIPS_PACRP_AC1_MASK)

#define AIPS_PACRP_RO1_MASK                      (0x8000000U)
#define AIPS_PACRP_RO1_SHIFT                     (27U)
/*! RO1 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO1(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO1_SHIFT)) & AIPS_PACRP_RO1_MASK)

#define AIPS_PACRP_AC0_MASK                      (0x70000000U)
#define AIPS_PACRP_AC0_SHIFT                     (28U)
/*! AC0 - Attribute Check
 */
#define AIPS_PACRP_AC0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_AC0_SHIFT)) & AIPS_PACRP_AC0_MASK)

#define AIPS_PACRP_RO0_MASK                      (0x80000000U)
#define AIPS_PACRP_RO0_SHIFT                     (31U)
/*! RO0 - Read Only
 *  0b0..Writes to corresponding AC field are allowed.
 *  0b1..Writes to corresponding AC field are ignored.
 */
#define AIPS_PACRP_RO0(x)                        (((uint32_t)(((uint32_t)(x)) << AIPS_PACRP_RO0_SHIFT)) & AIPS_PACRP_RO0_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group AIPS_Register_Masks */


/* AIPS - Peripheral instance base addresses */
/** Peripheral AIPS base address */
#define AIPS_BASE                                (0x40000000u)
/** Peripheral AIPS base pointer */
#define AIPS                                     ((AIPS_Type *)AIPS_BASE)
/** Array initializer of AIPS peripheral base addresses */
#define AIPS_BASE_ADDRS                          { AIPS_BASE }
/** Array initializer of AIPS peripheral base pointers */
#define AIPS_BASE_PTRS                           { AIPS }

/*!
 * @}
 */ /* end of group AIPS_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */

/** CMP - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR0;                                /**< CMP Control Register 0, offset: 0x0 */
  __IO uint8_t CR1;                                /**< CMP Control Register 1, offset: 0x1 */
  __IO uint8_t FPR;                                /**< CMP Filter Period Register, offset: 0x2 */
  __IO uint8_t SCR;                                /**< CMP Status and Control Register, offset: 0x3 */
  __IO uint8_t DACCR;                              /**< DAC Control Register, offset: 0x4 */
  __IO uint8_t MUXCR;                              /**< MUX Control Register, offset: 0x5 */
} CMP_Type;

/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/*! @name CR0 - CMP Control Register 0 */
/*! @{ */

#define CMP_CR0_HYSTCTR_MASK                     (0x3U)
#define CMP_CR0_HYSTCTR_SHIFT                    (0U)
/*! HYSTCTR - Comparator hard block hysteresis control
 *  0b00..Level 0
 *  0b01..Level 1
 *  0b10..Level 2
 *  0b11..Level 3
 */
#define CMP_CR0_HYSTCTR(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_CR0_HYSTCTR_SHIFT)) & CMP_CR0_HYSTCTR_MASK)

#define CMP_CR0_FILTER_CNT_MASK                  (0x70U)
#define CMP_CR0_FILTER_CNT_SHIFT                 (4U)
/*! FILTER_CNT - Filter Sample Count
 *  0b000..Filter is disabled. If SE = 1, then COUT is a logic 0. This is not a legal state, and is not recommended. If SE = 0, COUT = COUTA.
 *  0b001..One sample must agree. The comparator output is simply sampled.
 *  0b010..2 consecutive samples must agree.
 *  0b011..3 consecutive samples must agree.
 *  0b100..4 consecutive samples must agree.
 *  0b101..5 consecutive samples must agree.
 *  0b110..6 consecutive samples must agree.
 *  0b111..7 consecutive samples must agree.
 */
#define CMP_CR0_FILTER_CNT(x)                    (((uint8_t)(((uint8_t)(x)) << CMP_CR0_FILTER_CNT_SHIFT)) & CMP_CR0_FILTER_CNT_MASK)
/*! @} */

/*! @name CR1 - CMP Control Register 1 */
/*! @{ */

#define CMP_CR1_EN_MASK                          (0x1U)
#define CMP_CR1_EN_SHIFT                         (0U)
/*! EN - Comparator Module Enable
 *  0b0..Analog Comparator is disabled.
 *  0b1..Analog Comparator is enabled.
 */
#define CMP_CR1_EN(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_EN_SHIFT)) & CMP_CR1_EN_MASK)

#define CMP_CR1_OPE_MASK                         (0x2U)
#define CMP_CR1_OPE_SHIFT                        (1U)
/*! OPE - Comparator Output Pin Enable
 *  0b0..CMPO is not available on the associated CMPO output pin.
 *  0b1..CMPO is available on the associated CMPO output pin.
 */
#define CMP_CR1_OPE(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_OPE_SHIFT)) & CMP_CR1_OPE_MASK)

#define CMP_CR1_COS_MASK                         (0x4U)
#define CMP_CR1_COS_SHIFT                        (2U)
/*! COS - Comparator Output Select
 *  0b0..Set the filtered comparator output (CMPO) to equal COUT.
 *  0b1..Set the unfiltered comparator output (CMPO) to equal COUTA.
 */
#define CMP_CR1_COS(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_COS_SHIFT)) & CMP_CR1_COS_MASK)

#define CMP_CR1_INV_MASK                         (0x8U)
#define CMP_CR1_INV_SHIFT                        (3U)
/*! INV - Comparator INVERT
 *  0b0..Does not invert the comparator output.
 *  0b1..Inverts the comparator output.
 */
#define CMP_CR1_INV(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_CR1_INV_SHIFT)) & CMP_CR1_INV_MASK)

#define CMP_CR1_PMODE_MASK                       (0x10U)
#define CMP_CR1_PMODE_SHIFT                      (4U)
/*! PMODE - Power Mode Select
 *  0b0..Low-Speed (LS) Comparison mode selected. In this mode, CMP has slower output propagation delay and lower current consumption.
 *  0b1..High-Speed (HS) Comparison mode selected. In this mode, CMP has faster output propagation delay and higher current consumption.
 */
#define CMP_CR1_PMODE(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_PMODE_SHIFT)) & CMP_CR1_PMODE_MASK)

#define CMP_CR1_TRIGM_MASK                       (0x20U)
#define CMP_CR1_TRIGM_SHIFT                      (5U)
/*! TRIGM - Trigger Mode Enable
 *  0b0..Trigger mode is disabled.
 *  0b1..Trigger mode is enabled.
 */
#define CMP_CR1_TRIGM(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_CR1_TRIGM_SHIFT)) & CMP_CR1_TRIGM_MASK)

#define CMP_CR1_WE_MASK                          (0x40U)
#define CMP_CR1_WE_SHIFT                         (6U)
/*! WE - Windowing Enable
 *  0b0..Windowing mode is not selected.
 *  0b1..Windowing mode is selected.
 */
#define CMP_CR1_WE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_WE_SHIFT)) & CMP_CR1_WE_MASK)

#define CMP_CR1_SE_MASK                          (0x80U)
#define CMP_CR1_SE_SHIFT                         (7U)
/*! SE - Sample Enable
 *  0b0..Sampling mode is not selected.
 *  0b1..Sampling mode is selected.
 */
#define CMP_CR1_SE(x)                            (((uint8_t)(((uint8_t)(x)) << CMP_CR1_SE_SHIFT)) & CMP_CR1_SE_MASK)
/*! @} */

/*! @name FPR - CMP Filter Period Register */
/*! @{ */

#define CMP_FPR_FILT_PER_MASK                    (0xFFU)
#define CMP_FPR_FILT_PER_SHIFT                   (0U)
/*! FILT_PER - Filter Sample Period
 */
#define CMP_FPR_FILT_PER(x)                      (((uint8_t)(((uint8_t)(x)) << CMP_FPR_FILT_PER_SHIFT)) & CMP_FPR_FILT_PER_MASK)
/*! @} */

/*! @name SCR - CMP Status and Control Register */
/*! @{ */

#define CMP_SCR_COUT_MASK                        (0x1U)
#define CMP_SCR_COUT_SHIFT                       (0U)
/*! COUT - Analog Comparator Output
 */
#define CMP_SCR_COUT(x)                          (((uint8_t)(((uint8_t)(x)) << CMP_SCR_COUT_SHIFT)) & CMP_SCR_COUT_MASK)

#define CMP_SCR_CFF_MASK                         (0x2U)
#define CMP_SCR_CFF_SHIFT                        (1U)
/*! CFF - Analog Comparator Flag Falling
 *  0b0..Falling-edge on COUT has not been detected.
 *  0b1..Falling-edge on COUT has occurred.
 */
#define CMP_SCR_CFF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFF_SHIFT)) & CMP_SCR_CFF_MASK)

#define CMP_SCR_CFR_MASK                         (0x4U)
#define CMP_SCR_CFR_SHIFT                        (2U)
/*! CFR - Analog Comparator Flag Rising
 *  0b0..Rising-edge on COUT has not been detected.
 *  0b1..Rising-edge on COUT has occurred.
 */
#define CMP_SCR_CFR(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_CFR_SHIFT)) & CMP_SCR_CFR_MASK)

#define CMP_SCR_IEF_MASK                         (0x8U)
#define CMP_SCR_IEF_SHIFT                        (3U)
/*! IEF - Comparator Interrupt Enable Falling
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IEF(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IEF_SHIFT)) & CMP_SCR_IEF_MASK)

#define CMP_SCR_IER_MASK                         (0x10U)
#define CMP_SCR_IER_SHIFT                        (4U)
/*! IER - Comparator Interrupt Enable Rising
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define CMP_SCR_IER(x)                           (((uint8_t)(((uint8_t)(x)) << CMP_SCR_IER_SHIFT)) & CMP_SCR_IER_MASK)

#define CMP_SCR_DMAEN_MASK                       (0x40U)
#define CMP_SCR_DMAEN_SHIFT                      (6U)
/*! DMAEN - DMA Enable Control
 *  0b0..DMA is disabled.
 *  0b1..DMA is enabled.
 */
#define CMP_SCR_DMAEN(x)                         (((uint8_t)(((uint8_t)(x)) << CMP_SCR_DMAEN_SHIFT)) & CMP_SCR_DMAEN_MASK)
/*! @} */

/*! @name DACCR - DAC Control Register */
/*! @{ */

#define CMP_DACCR_VOSEL_MASK                     (0x3FU)
#define CMP_DACCR_VOSEL_SHIFT                    (0U)
/*! VOSEL - DAC Output Voltage Select
 */
#define CMP_DACCR_VOSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VOSEL_SHIFT)) & CMP_DACCR_VOSEL_MASK)

#define CMP_DACCR_VRSEL_MASK                     (0x40U)
#define CMP_DACCR_VRSEL_SHIFT                    (6U)
/*! VRSEL - Supply Voltage Reference Source Select
 *  0b0..Vin1 is selected as resistor ladder network supply reference.
 *  0b1..Vin2 is selected as resistor ladder network supply reference.
 */
#define CMP_DACCR_VRSEL(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_VRSEL_SHIFT)) & CMP_DACCR_VRSEL_MASK)

#define CMP_DACCR_DACEN_MASK                     (0x80U)
#define CMP_DACCR_DACEN_SHIFT                    (7U)
/*! DACEN - DAC Enable
 *  0b0..DAC is disabled.
 *  0b1..DAC is enabled.
 */
#define CMP_DACCR_DACEN(x)                       (((uint8_t)(((uint8_t)(x)) << CMP_DACCR_DACEN_SHIFT)) & CMP_DACCR_DACEN_MASK)
/*! @} */

/*! @name MUXCR - MUX Control Register */
/*! @{ */

#define CMP_MUXCR_MSEL_MASK                      (0x7U)
#define CMP_MUXCR_MSEL_SHIFT                     (0U)
/*! MSEL - Minus Input Mux Control
 *  0b000..IN0
 *  0b001..IN1
 *  0b010..IN2
 *  0b011..IN3
 *  0b100..IN4
 *  0b101..IN5
 *  0b110..IN6
 *  0b111..IN7
 */
#define CMP_MUXCR_MSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_MSEL_SHIFT)) & CMP_MUXCR_MSEL_MASK)

#define CMP_MUXCR_PSEL_MASK                      (0x38U)
#define CMP_MUXCR_PSEL_SHIFT                     (3U)
/*! PSEL - Plus Input Mux Control
 *  0b000..IN0
 *  0b001..IN1
 *  0b010..IN2
 *  0b011..IN3
 *  0b100..IN4
 *  0b101..IN5
 *  0b110..IN6
 *  0b111..IN7
 */
#define CMP_MUXCR_PSEL(x)                        (((uint8_t)(((uint8_t)(x)) << CMP_MUXCR_PSEL_SHIFT)) & CMP_MUXCR_PSEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CMP_Register_Masks */


/* CMP - Peripheral instance base addresses */
/** Peripheral CMP0 base address */
#define CMP0_BASE                                (0x40072000u)
/** Peripheral CMP0 base pointer */
#define CMP0                                     ((CMP_Type *)CMP0_BASE)
/** Peripheral CMP1 base address */
#define CMP1_BASE                                (0x40072008u)
/** Peripheral CMP1 base pointer */
#define CMP1                                     ((CMP_Type *)CMP1_BASE)
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           { CMP0_BASE, CMP1_BASE }
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            { CMP0, CMP1 }
/** Interrupt vectors for the CMP peripheral type */
#define CMP_IRQS                                 { CMP0_CMP1_IRQn, CMP0_CMP1_IRQn }

/*!
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */

/** CRC - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __IO uint8_t DATALL;                             /**< CRC_DATALL register., offset: 0x0 */
      __IO uint8_t DATALU;                             /**< CRC_DATALU register., offset: 0x1 */
      __IO uint8_t DATAHL;                             /**< CRC_DATAHL register., offset: 0x2 */
      __IO uint8_t DATAHU;                             /**< CRC_DATAHU register., offset: 0x3 */
    } ACCESS8BIT;
    struct {                                         /* offset: 0x0 */
      __IO uint16_t DATAL;                             /**< CRC_DATAL register., offset: 0x0 */
      __IO uint16_t DATAH;                             /**< CRC_DATAH register., offset: 0x2 */
    } ACCESS16BIT;
    __IO uint32_t DATA;                              /**< CRC Data register, offset: 0x0 */
  };
  union {                                          /* offset: 0x4 */
    struct {                                         /* offset: 0x4 */
      __IO uint8_t GPOLYLL;                            /**< CRC_GPOLYLL register., offset: 0x4 */
      __IO uint8_t GPOLYLU;                            /**< CRC_GPOLYLU register., offset: 0x5 */
      __IO uint8_t GPOLYHL;                            /**< CRC_GPOLYHL register., offset: 0x6 */
      __IO uint8_t GPOLYHU;                            /**< CRC_GPOLYHU register., offset: 0x7 */
    } GPOLY_ACCESS8BIT;
    struct {                                         /* offset: 0x4 */
      __IO uint16_t GPOLYL;                            /**< CRC_GPOLYL register., offset: 0x4 */
      __IO uint16_t GPOLYH;                            /**< CRC_GPOLYH register., offset: 0x6 */
    } GPOLY_ACCESS16BIT;
    __IO uint32_t GPOLY;                             /**< CRC Polynomial register, offset: 0x4 */
  };
  union {                                          /* offset: 0x8 */
    struct {                                         /* offset: 0x8 */
           uint8_t RESERVED_0[3];
      __IO uint8_t CTRLHU;                             /**< CRC_CTRLHU register., offset: 0xB */
    } CTRL_ACCESS8BIT;
    __IO uint32_t CTRL;                              /**< CRC Control register, offset: 0x8 */
  };
} CRC_Type;

/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */

/*! @name DATALL - CRC_DATALL register. */
/*! @{ */

#define CRC_DATALL_DATALL_MASK                   (0xFFU)
#define CRC_DATALL_DATALL_SHIFT                  (0U)
/*! DATALL - CRCLL stores the first 8 bits of the 32 bit DATA
 */
#define CRC_DATALL_DATALL(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATALL_DATALL_SHIFT)) & CRC_DATALL_DATALL_MASK)
/*! @} */

/*! @name DATALU - CRC_DATALU register. */
/*! @{ */

#define CRC_DATALU_DATALU_MASK                   (0xFFU)
#define CRC_DATALU_DATALU_SHIFT                  (0U)
/*! DATALU - DATALL stores the second 8 bits of the 32 bit CRC
 */
#define CRC_DATALU_DATALU(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATALU_DATALU_SHIFT)) & CRC_DATALU_DATALU_MASK)
/*! @} */

/*! @name DATAHL - CRC_DATAHL register. */
/*! @{ */

#define CRC_DATAHL_DATAHL_MASK                   (0xFFU)
#define CRC_DATAHL_DATAHL_SHIFT                  (0U)
/*! DATAHL - DATAHL stores the third 8 bits of the 32 bit CRC
 */
#define CRC_DATAHL_DATAHL(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATAHL_DATAHL_SHIFT)) & CRC_DATAHL_DATAHL_MASK)
/*! @} */

/*! @name DATAHU - CRC_DATAHU register. */
/*! @{ */

#define CRC_DATAHU_DATAHU_MASK                   (0xFFU)
#define CRC_DATAHU_DATAHU_SHIFT                  (0U)
/*! DATAHU - DATAHU stores the fourth 8 bits of the 32 bit CRC
 */
#define CRC_DATAHU_DATAHU(x)                     (((uint8_t)(((uint8_t)(x)) << CRC_DATAHU_DATAHU_SHIFT)) & CRC_DATAHU_DATAHU_MASK)
/*! @} */

/*! @name DATAL - CRC_DATAL register. */
/*! @{ */

#define CRC_DATAL_DATAL_MASK                     (0xFFFFU)
#define CRC_DATAL_DATAL_SHIFT                    (0U)
/*! DATAL - DATAL stores the lower 16 bits of the 16/32 bit CRC
 */
#define CRC_DATAL_DATAL(x)                       (((uint16_t)(((uint16_t)(x)) << CRC_DATAL_DATAL_SHIFT)) & CRC_DATAL_DATAL_MASK)
/*! @} */

/*! @name DATAH - CRC_DATAH register. */
/*! @{ */

#define CRC_DATAH_DATAH_MASK                     (0xFFFFU)
#define CRC_DATAH_DATAH_SHIFT                    (0U)
/*! DATAH - DATAH stores the high 16 bits of the 16/32 bit CRC
 */
#define CRC_DATAH_DATAH(x)                       (((uint16_t)(((uint16_t)(x)) << CRC_DATAH_DATAH_SHIFT)) & CRC_DATAH_DATAH_MASK)
/*! @} */

/*! @name DATA - CRC Data register */
/*! @{ */

#define CRC_DATA_LL_MASK                         (0xFFU)
#define CRC_DATA_LL_SHIFT                        (0U)
/*! LL - CRC Low Lower Byte
 */
#define CRC_DATA_LL(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LL_SHIFT)) & CRC_DATA_LL_MASK)

#define CRC_DATA_LU_MASK                         (0xFF00U)
#define CRC_DATA_LU_SHIFT                        (8U)
/*! LU - CRC Low Upper Byte
 */
#define CRC_DATA_LU(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_LU_SHIFT)) & CRC_DATA_LU_MASK)

#define CRC_DATA_HL_MASK                         (0xFF0000U)
#define CRC_DATA_HL_SHIFT                        (16U)
/*! HL - CRC High Lower Byte
 */
#define CRC_DATA_HL(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HL_SHIFT)) & CRC_DATA_HL_MASK)

#define CRC_DATA_HU_MASK                         (0xFF000000U)
#define CRC_DATA_HU_SHIFT                        (24U)
/*! HU - CRC High Upper Byte
 */
#define CRC_DATA_HU(x)                           (((uint32_t)(((uint32_t)(x)) << CRC_DATA_HU_SHIFT)) & CRC_DATA_HU_MASK)
/*! @} */

/*! @name GPOLYLL - CRC_GPOLYLL register. */
/*! @{ */

#define CRC_GPOLYLL_GPOLYLL_MASK                 (0xFFU)
#define CRC_GPOLYLL_GPOLYLL_SHIFT                (0U)
/*! GPOLYLL - POLYLL stores the first 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYLL_GPOLYLL(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLL_GPOLYLL_SHIFT)) & CRC_GPOLYLL_GPOLYLL_MASK)
/*! @} */

/*! @name GPOLYLU - CRC_GPOLYLU register. */
/*! @{ */

#define CRC_GPOLYLU_GPOLYLU_MASK                 (0xFFU)
#define CRC_GPOLYLU_GPOLYLU_SHIFT                (0U)
/*! GPOLYLU - POLYLL stores the second 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYLU_GPOLYLU(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYLU_GPOLYLU_SHIFT)) & CRC_GPOLYLU_GPOLYLU_MASK)
/*! @} */

/*! @name GPOLYHL - CRC_GPOLYHL register. */
/*! @{ */

#define CRC_GPOLYHL_GPOLYHL_MASK                 (0xFFU)
#define CRC_GPOLYHL_GPOLYHL_SHIFT                (0U)
/*! GPOLYHL - POLYHL stores the third 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYHL_GPOLYHL(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHL_GPOLYHL_SHIFT)) & CRC_GPOLYHL_GPOLYHL_MASK)
/*! @} */

/*! @name GPOLYHU - CRC_GPOLYHU register. */
/*! @{ */

#define CRC_GPOLYHU_GPOLYHU_MASK                 (0xFFU)
#define CRC_GPOLYHU_GPOLYHU_SHIFT                (0U)
/*! GPOLYHU - POLYHU stores the fourth 8 bits of the 32 bit CRC
 */
#define CRC_GPOLYHU_GPOLYHU(x)                   (((uint8_t)(((uint8_t)(x)) << CRC_GPOLYHU_GPOLYHU_SHIFT)) & CRC_GPOLYHU_GPOLYHU_MASK)
/*! @} */

/*! @name GPOLYL - CRC_GPOLYL register. */
/*! @{ */

#define CRC_GPOLYL_GPOLYL_MASK                   (0xFFFFU)
#define CRC_GPOLYL_GPOLYL_SHIFT                  (0U)
/*! GPOLYL - POLYL stores the lower 16 bits of the 16/32 bit CRC polynomial value
 */
#define CRC_GPOLYL_GPOLYL(x)                     (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYL_GPOLYL_SHIFT)) & CRC_GPOLYL_GPOLYL_MASK)
/*! @} */

/*! @name GPOLYH - CRC_GPOLYH register. */
/*! @{ */

#define CRC_GPOLYH_GPOLYH_MASK                   (0xFFFFU)
#define CRC_GPOLYH_GPOLYH_SHIFT                  (0U)
/*! GPOLYH - POLYH stores the high 16 bits of the 16/32 bit CRC polynomial value
 */
#define CRC_GPOLYH_GPOLYH(x)                     (((uint16_t)(((uint16_t)(x)) << CRC_GPOLYH_GPOLYH_SHIFT)) & CRC_GPOLYH_GPOLYH_MASK)
/*! @} */

/*! @name GPOLY - CRC Polynomial register */
/*! @{ */

#define CRC_GPOLY_LOW_MASK                       (0xFFFFU)
#define CRC_GPOLY_LOW_SHIFT                      (0U)
/*! LOW - Low Polynominal Half-word
 */
#define CRC_GPOLY_LOW(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_LOW_SHIFT)) & CRC_GPOLY_LOW_MASK)

#define CRC_GPOLY_HIGH_MASK                      (0xFFFF0000U)
#define CRC_GPOLY_HIGH_SHIFT                     (16U)
/*! HIGH - High Polynominal Half-word
 */
#define CRC_GPOLY_HIGH(x)                        (((uint32_t)(((uint32_t)(x)) << CRC_GPOLY_HIGH_SHIFT)) & CRC_GPOLY_HIGH_MASK)
/*! @} */

/*! @name CTRLHU - CRC_CTRLHU register. */
/*! @{ */

#define CRC_CTRLHU_TCRC_MASK                     (0x1U)
#define CRC_CTRLHU_TCRC_SHIFT                    (0U)
/*! TCRC
 *  0b0..16-bit CRC protocol.
 *  0b1..32-bit CRC protocol.
 */
#define CRC_CTRLHU_TCRC(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TCRC_SHIFT)) & CRC_CTRLHU_TCRC_MASK)

#define CRC_CTRLHU_WAS_MASK                      (0x2U)
#define CRC_CTRLHU_WAS_SHIFT                     (1U)
/*! WAS
 *  0b0..Writes to CRC data register are data values.
 *  0b1..Writes to CRC data reguster are seed values.
 */
#define CRC_CTRLHU_WAS(x)                        (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_WAS_SHIFT)) & CRC_CTRLHU_WAS_MASK)

#define CRC_CTRLHU_FXOR_MASK                     (0x4U)
#define CRC_CTRLHU_FXOR_SHIFT                    (2U)
/*! FXOR
 *  0b0..No XOR on reading.
 *  0b1..Invert or complement the read value of CRC data register.
 */
#define CRC_CTRLHU_FXOR(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_FXOR_SHIFT)) & CRC_CTRLHU_FXOR_MASK)

#define CRC_CTRLHU_TOTR_MASK                     (0x30U)
#define CRC_CTRLHU_TOTR_SHIFT                    (4U)
/*! TOTR
 *  0b00..No Transposition.
 *  0b01..Bits in bytes are transposed, bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRLHU_TOTR(x)                       (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOTR_SHIFT)) & CRC_CTRLHU_TOTR_MASK)

#define CRC_CTRLHU_TOT_MASK                      (0xC0U)
#define CRC_CTRLHU_TOT_SHIFT                     (6U)
/*! TOT
 *  0b00..No Transposition.
 *  0b01..Bits in bytes are transposed, bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRLHU_TOT(x)                        (((uint8_t)(((uint8_t)(x)) << CRC_CTRLHU_TOT_SHIFT)) & CRC_CTRLHU_TOT_MASK)
/*! @} */

/*! @name CTRL - CRC Control register */
/*! @{ */

#define CRC_CTRL_TCRC_MASK                       (0x1000000U)
#define CRC_CTRL_TCRC_SHIFT                      (24U)
/*! TCRC
 *  0b0..16-bit CRC protocol.
 *  0b1..32-bit CRC protocol.
 */
#define CRC_CTRL_TCRC(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TCRC_SHIFT)) & CRC_CTRL_TCRC_MASK)

#define CRC_CTRL_WAS_MASK                        (0x2000000U)
#define CRC_CTRL_WAS_SHIFT                       (25U)
/*! WAS - Write CRC Data Register As Seed
 *  0b0..Writes to the CRC data register are data values.
 *  0b1..Writes to the CRC data register are seed values.
 */
#define CRC_CTRL_WAS(x)                          (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_WAS_SHIFT)) & CRC_CTRL_WAS_MASK)

#define CRC_CTRL_FXOR_MASK                       (0x4000000U)
#define CRC_CTRL_FXOR_SHIFT                      (26U)
/*! FXOR - Complement Read Of CRC Data Register
 *  0b0..No XOR on reading.
 *  0b1..Invert or complement the read value of the CRC Data register.
 */
#define CRC_CTRL_FXOR(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_FXOR_SHIFT)) & CRC_CTRL_FXOR_MASK)

#define CRC_CTRL_TOTR_MASK                       (0x30000000U)
#define CRC_CTRL_TOTR_SHIFT                      (28U)
/*! TOTR - Type Of Transpose For Read
 *  0b00..No transposition.
 *  0b01..Bits in bytes are transposed; bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRL_TOTR(x)                         (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOTR_SHIFT)) & CRC_CTRL_TOTR_MASK)

#define CRC_CTRL_TOT_MASK                        (0xC0000000U)
#define CRC_CTRL_TOT_SHIFT                       (30U)
/*! TOT - Type Of Transpose For Writes
 *  0b00..No transposition.
 *  0b01..Bits in bytes are transposed; bytes are not transposed.
 *  0b10..Both bits in bytes and bytes are transposed.
 *  0b11..Only bytes are transposed; no bits in a byte are transposed.
 */
#define CRC_CTRL_TOT(x)                          (((uint32_t)(((uint32_t)(x)) << CRC_CTRL_TOT_SHIFT)) & CRC_CTRL_TOT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group CRC_Register_Masks */


/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE                                 (0x40034000u)
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
       uint8_t RESERVED_0[256];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t SAR;                               /**< Source Address Register, array offset: 0x100, array step: 0x10 */
    __IO uint32_t DAR;                               /**< Destination Address Register, array offset: 0x104, array step: 0x10 */
    union {                                          /* offset: 0x108, array step: 0x10 */
      struct {                                         /* offset: 0x108, array step: 0x10 */
             uint8_t RESERVED_0[3];
             uint8_t DSR;                                /**< DMA_DSR0 register...DMA_DSR3 register., array offset: 0x10B, array step: 0x10 */
      } DMA_DSR_ACCESS8BIT;
      __IO uint32_t DSR_BCR;                           /**< DMA Status Register / Byte Count Register, array offset: 0x108, array step: 0x10 */
    };
    __IO uint32_t DCR;                               /**< DMA Control Register, array offset: 0x10C, array step: 0x10 */
  } DMA[4];
} DMA_Type;

/* ----------------------------------------------------------------------------
   -- DMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMA_Register_Masks DMA Register Masks
 * @{
 */

/*! @name SAR - Source Address Register */
/*! @{ */

#define DMA_SAR_SAR_MASK                         (0xFFFFFFFFU)
#define DMA_SAR_SAR_SHIFT                        (0U)
/*! SAR - SAR
 */
#define DMA_SAR_SAR(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_SAR_SAR_SHIFT)) & DMA_SAR_SAR_MASK)
/*! @} */

/* The count of DMA_SAR */
#define DMA_SAR_COUNT                            (4U)

/*! @name DAR - Destination Address Register */
/*! @{ */

#define DMA_DAR_DAR_MASK                         (0xFFFFFFFFU)
#define DMA_DAR_DAR_SHIFT                        (0U)
/*! DAR - DAR
 */
#define DMA_DAR_DAR(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_DAR_DAR_SHIFT)) & DMA_DAR_DAR_MASK)
/*! @} */

/* The count of DMA_DAR */
#define DMA_DAR_COUNT                            (4U)

/* The count of DMA_DSR */
#define DMA_DSR_COUNT                            (4U)

/*! @name DSR_BCR - DMA Status Register / Byte Count Register */
/*! @{ */

#define DMA_DSR_BCR_BCR_MASK                     (0xFFFFFFU)
#define DMA_DSR_BCR_BCR_SHIFT                    (0U)
/*! BCR - BCR
 */
#define DMA_DSR_BCR_BCR(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BCR_SHIFT)) & DMA_DSR_BCR_BCR_MASK)

#define DMA_DSR_BCR_DONE_MASK                    (0x1000000U)
#define DMA_DSR_BCR_DONE_SHIFT                   (24U)
/*! DONE - Transactions Done
 *  0b0..DMA transfer is not yet complete. Writing a 0 has no effect.
 *  0b1..DMA transfer completed. Writing a 1 to this bit clears all DMA status bits and should be used in an
 *       interrupt service routine to clear the DMA interrupt and error bits.
 */
#define DMA_DSR_BCR_DONE(x)                      (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_DONE_SHIFT)) & DMA_DSR_BCR_DONE_MASK)

#define DMA_DSR_BCR_BSY_MASK                     (0x2000000U)
#define DMA_DSR_BCR_BSY_SHIFT                    (25U)
/*! BSY - Busy
 *  0b0..DMA channel is inactive. Cleared when the DMA has finished the last transaction.
 *  0b1..BSY is set the first time the channel is enabled after a transfer is initiated.
 */
#define DMA_DSR_BCR_BSY(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BSY_SHIFT)) & DMA_DSR_BCR_BSY_MASK)

#define DMA_DSR_BCR_REQ_MASK                     (0x4000000U)
#define DMA_DSR_BCR_REQ_SHIFT                    (26U)
/*! REQ - Request
 *  0b0..No request is pending or the channel is currently active. Cleared when the channel is selected.
 *  0b1..The DMA channel has a transfer remaining and the channel is not selected.
 */
#define DMA_DSR_BCR_REQ(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_REQ_SHIFT)) & DMA_DSR_BCR_REQ_MASK)

#define DMA_DSR_BCR_BED_MASK                     (0x10000000U)
#define DMA_DSR_BCR_BED_SHIFT                    (28U)
/*! BED - Bus Error on Destination
 *  0b0..No bus error occurred.
 *  0b1..The DMA channel terminated with a bus error during the write portion of a transfer.
 */
#define DMA_DSR_BCR_BED(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BED_SHIFT)) & DMA_DSR_BCR_BED_MASK)

#define DMA_DSR_BCR_BES_MASK                     (0x20000000U)
#define DMA_DSR_BCR_BES_SHIFT                    (29U)
/*! BES - Bus Error on Source
 *  0b0..No bus error occurred.
 *  0b1..The DMA channel terminated with a bus error during the read portion of a transfer.
 */
#define DMA_DSR_BCR_BES(x)                       (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_BES_SHIFT)) & DMA_DSR_BCR_BES_MASK)

#define DMA_DSR_BCR_CE_MASK                      (0x40000000U)
#define DMA_DSR_BCR_CE_SHIFT                     (30U)
/*! CE - Configuration Error
 *  0b0..No configuration error exists.
 *  0b1..A configuration error has occurred.
 */
#define DMA_DSR_BCR_CE(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DSR_BCR_CE_SHIFT)) & DMA_DSR_BCR_CE_MASK)
/*! @} */

/* The count of DMA_DSR_BCR */
#define DMA_DSR_BCR_COUNT                        (4U)

/*! @name DCR - DMA Control Register */
/*! @{ */

#define DMA_DCR_LCH2_MASK                        (0x3U)
#define DMA_DCR_LCH2_SHIFT                       (0U)
/*! LCH2 - Link Channel 2
 *  0b00..DMA Channel 0
 *  0b01..DMA Channel 1
 *  0b10..DMA Channel 2
 *  0b11..DMA Channel 3
 */
#define DMA_DCR_LCH2(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LCH2_SHIFT)) & DMA_DCR_LCH2_MASK)

#define DMA_DCR_LCH1_MASK                        (0xCU)
#define DMA_DCR_LCH1_SHIFT                       (2U)
/*! LCH1 - Link Channel 1
 *  0b00..DMA Channel 0
 *  0b01..DMA Channel 1
 *  0b10..DMA Channel 2
 *  0b11..DMA Channel 3
 */
#define DMA_DCR_LCH1(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LCH1_SHIFT)) & DMA_DCR_LCH1_MASK)

#define DMA_DCR_LINKCC_MASK                      (0x30U)
#define DMA_DCR_LINKCC_SHIFT                     (4U)
/*! LINKCC - Link Channel Control
 *  0b00..No channel-to-channel linking
 *  0b01..Perform a link to channel LCH1 after each cycle-steal transfer followed by a link to LCH2 after the BCR decrements to 0.
 *  0b10..Perform a link to channel LCH1 after each cycle-steal transfer
 *  0b11..Perform a link to channel LCH1 after the BCR decrements to 0.
 */
#define DMA_DCR_LINKCC(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DCR_LINKCC_SHIFT)) & DMA_DCR_LINKCC_MASK)

#define DMA_DCR_D_REQ_MASK                       (0x80U)
#define DMA_DCR_D_REQ_SHIFT                      (7U)
/*! D_REQ - Disable Request
 *  0b0..ERQ bit is not affected.
 *  0b1..ERQ bit is cleared when the BCR is exhausted.
 */
#define DMA_DCR_D_REQ(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_D_REQ_SHIFT)) & DMA_DCR_D_REQ_MASK)

#define DMA_DCR_DMOD_MASK                        (0xF00U)
#define DMA_DCR_DMOD_SHIFT                       (8U)
/*! DMOD - Destination Address Modulo
 *  0b0000..Buffer disabled
 *  0b0001..Circular buffer size is 16 bytes
 *  0b0010..Circular buffer size is 32 bytes
 *  0b0011..Circular buffer size is 64 bytes
 *  0b0100..Circular buffer size is 128 bytes
 *  0b0101..Circular buffer size is 256 bytes
 *  0b0110..Circular buffer size is 512 bytes
 *  0b0111..Circular buffer size is 1 KB
 *  0b1000..Circular buffer size is 2 KB
 *  0b1001..Circular buffer size is 4 KB
 *  0b1010..Circular buffer size is 8 KB
 *  0b1011..Circular buffer size is 16 KB
 *  0b1100..Circular buffer size is 32 KB
 *  0b1101..Circular buffer size is 64 KB
 *  0b1110..Circular buffer size is 128 KB
 *  0b1111..Circular buffer size is 256 KB
 */
#define DMA_DCR_DMOD(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DMOD_SHIFT)) & DMA_DCR_DMOD_MASK)

#define DMA_DCR_SMOD_MASK                        (0xF000U)
#define DMA_DCR_SMOD_SHIFT                       (12U)
/*! SMOD - Source Address Modulo
 *  0b0000..Buffer disabled
 *  0b0001..Circular buffer size is 16 bytes.
 *  0b0010..Circular buffer size is 32 bytes.
 *  0b0011..Circular buffer size is 64 bytes.
 *  0b0100..Circular buffer size is 128 bytes.
 *  0b0101..Circular buffer size is 256 bytes.
 *  0b0110..Circular buffer size is 512 bytes.
 *  0b0111..Circular buffer size is 1 KB.
 *  0b1000..Circular buffer size is 2 KB.
 *  0b1001..Circular buffer size is 4 KB.
 *  0b1010..Circular buffer size is 8 KB.
 *  0b1011..Circular buffer size is 16 KB.
 *  0b1100..Circular buffer size is 32 KB.
 *  0b1101..Circular buffer size is 64 KB.
 *  0b1110..Circular buffer size is 128 KB.
 *  0b1111..Circular buffer size is 256 KB.
 */
#define DMA_DCR_SMOD(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SMOD_SHIFT)) & DMA_DCR_SMOD_MASK)

#define DMA_DCR_START_MASK                       (0x10000U)
#define DMA_DCR_START_SHIFT                      (16U)
/*! START - Start Transfer
 *  0b0..DMA inactive
 *  0b1..The DMA begins the transfer in accordance to the values in the TCDn. START is cleared automatically after
 *       one module clock and always reads as logic 0.
 */
#define DMA_DCR_START(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_START_SHIFT)) & DMA_DCR_START_MASK)

#define DMA_DCR_DSIZE_MASK                       (0x60000U)
#define DMA_DCR_DSIZE_SHIFT                      (17U)
/*! DSIZE - Destination Size
 *  0b00..32-bit
 *  0b01..8-bit
 *  0b10..16-bit
 *  0b11..Reserved (generates a configuration error (DSRn[CE]) if incorrectly specified at time of channel activation)
 */
#define DMA_DCR_DSIZE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DSIZE_SHIFT)) & DMA_DCR_DSIZE_MASK)

#define DMA_DCR_DINC_MASK                        (0x80000U)
#define DMA_DCR_DINC_SHIFT                       (19U)
/*! DINC - Destination Increment
 *  0b0..No change to the DAR after a successful transfer.
 *  0b1..The DAR increments by 1, 2, 4 depending upon the size of the transfer.
 */
#define DMA_DCR_DINC(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_DINC_SHIFT)) & DMA_DCR_DINC_MASK)

#define DMA_DCR_SSIZE_MASK                       (0x300000U)
#define DMA_DCR_SSIZE_SHIFT                      (20U)
/*! SSIZE - Source Size
 *  0b00..32-bit
 *  0b01..8-bit
 *  0b10..16-bit
 *  0b11..Reserved (generates a configuration error (DSRn[CE]) if incorrectly specified at time of channel activation)
 */
#define DMA_DCR_SSIZE(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SSIZE_SHIFT)) & DMA_DCR_SSIZE_MASK)

#define DMA_DCR_SINC_MASK                        (0x400000U)
#define DMA_DCR_SINC_SHIFT                       (22U)
/*! SINC - Source Increment
 *  0b0..No change to SAR after a successful transfer.
 *  0b1..The SAR increments by 1, 2, 4 as determined by the transfer size.
 */
#define DMA_DCR_SINC(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_SINC_SHIFT)) & DMA_DCR_SINC_MASK)

#define DMA_DCR_EADREQ_MASK                      (0x800000U)
#define DMA_DCR_EADREQ_SHIFT                     (23U)
/*! EADREQ - Enable asynchronous DMA requests
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define DMA_DCR_EADREQ(x)                        (((uint32_t)(((uint32_t)(x)) << DMA_DCR_EADREQ_SHIFT)) & DMA_DCR_EADREQ_MASK)

#define DMA_DCR_UMNSM_MASK                       (0x3000000U)
#define DMA_DCR_UMNSM_SHIFT                      (24U)
/*! UMNSM - User Mode, Nonsecure Mode
 *  0b00..Channel attributes are set to the current mode.
 *  0b01..If the current mode is privileged and secure, then attributes are set to {privileged, secure}.
 *        Otherwise, writing this value terminates in an error.
 *  0b10..If the current mode is privileged and secure or if the current mode is user and secure, then attributes
 *        are set to {user, secure}. Otherwise, writing this value terminates in an error.
 *  0b11..If the current mode is privileged and secure, user and secure, or user and nonsecure, then attributes are set to {user, nonsecure}.
 */
#define DMA_DCR_UMNSM(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_UMNSM_SHIFT)) & DMA_DCR_UMNSM_MASK)

#define DMA_DCR_CHACR_MASK                       (0xC000000U)
#define DMA_DCR_CHACR_SHIFT                      (26U)
/*! CHACR - Channel Access Control
 */
#define DMA_DCR_CHACR(x)                         (((uint32_t)(((uint32_t)(x)) << DMA_DCR_CHACR_SHIFT)) & DMA_DCR_CHACR_MASK)

#define DMA_DCR_AA_MASK                          (0x10000000U)
#define DMA_DCR_AA_SHIFT                         (28U)
/*! AA - Auto-align
 *  0b0..Auto-align disabled
 *  0b1..If SSIZE indicates a transfer no smaller than DSIZE, source accesses are auto-aligned; otherwise,
 *       destination accesses are auto-aligned. Source alignment takes precedence over destination alignment. If
 *       auto-alignment is enabled, the appropriate address register increments, regardless of DINC or SINC.
 */
#define DMA_DCR_AA(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_DCR_AA_SHIFT)) & DMA_DCR_AA_MASK)

#define DMA_DCR_CS_MASK                          (0x20000000U)
#define DMA_DCR_CS_SHIFT                         (29U)
/*! CS - Cycle Steal
 *  0b0..DMA continuously makes read/write transfers until the BCR decrements to 0.
 *  0b1..Forces a single read/write transfer per request.
 */
#define DMA_DCR_CS(x)                            (((uint32_t)(((uint32_t)(x)) << DMA_DCR_CS_SHIFT)) & DMA_DCR_CS_MASK)

#define DMA_DCR_ERQ_MASK                         (0x40000000U)
#define DMA_DCR_ERQ_SHIFT                        (30U)
/*! ERQ - Enable Peripheral Request
 *  0b0..Peripheral request is ignored.
 *  0b1..Enables peripheral request to initiate transfer. A software-initiated request (setting START) is always enabled.
 */
#define DMA_DCR_ERQ(x)                           (((uint32_t)(((uint32_t)(x)) << DMA_DCR_ERQ_SHIFT)) & DMA_DCR_ERQ_MASK)

#define DMA_DCR_EINT_MASK                        (0x80000000U)
#define DMA_DCR_EINT_SHIFT                       (31U)
/*! EINT - Enable Interrupt on Completion of Transfer
 *  0b0..No interrupt is generated.
 *  0b1..Interrupt signal is enabled.
 */
#define DMA_DCR_EINT(x)                          (((uint32_t)(((uint32_t)(x)) << DMA_DCR_EINT_SHIFT)) & DMA_DCR_EINT_MASK)
/*! @} */

/* The count of DMA_DCR */
#define DMA_DCR_COUNT                            (4U)


/*!
 * @}
 */ /* end of group DMA_Register_Masks */


/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA0                                     ((DMA_Type *)DMA_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           { DMA_BASE }
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            { DMA0 }
/** Interrupt vectors for the DMA peripheral type */
#define DMA_CHN_IRQS                             { { DMA0_IRQn, DMA1_IRQn, DMA2_IRQn, DMA3_IRQn } }

/*!
 * @}
 */ /* end of group DMA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- DMAMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer
 * @{
 */

/** DMAMUX - Register Layout Typedef */
typedef struct {
  __IO uint8_t CHCFG[1];                           /**< Channel Configuration register, array offset: 0x0, array step: 0x1 */
} DMAMUX_Type;

/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */

/*! @name CHCFG - Channel Configuration register */
/*! @{ */

#define DMAMUX_CHCFG_SOURCE_MASK                 (0x3FU)
#define DMAMUX_CHCFG_SOURCE_SHIFT                (0U)
/*! SOURCE - DMA Channel Source (Slot)
 */
#define DMAMUX_CHCFG_SOURCE(x)                   (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_SOURCE_SHIFT)) & DMAMUX_CHCFG_SOURCE_MASK)

#define DMAMUX_CHCFG_TRIG_MASK                   (0x40U)
#define DMAMUX_CHCFG_TRIG_SHIFT                  (6U)
/*! TRIG - DMA Channel Trigger Enable
 *  0b0..Triggering is disabled. If triggering is disabled and ENBL is set, the DMA Channel will simply route the
 *       specified source to the DMA channel. (Normal mode)
 *  0b1..Triggering is enabled. If triggering is enabled and ENBL is set, the DMAMUX is in Periodic Trigger mode.
 */
#define DMAMUX_CHCFG_TRIG(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_TRIG_SHIFT)) & DMAMUX_CHCFG_TRIG_MASK)

#define DMAMUX_CHCFG_ENBL_MASK                   (0x80U)
#define DMAMUX_CHCFG_ENBL_SHIFT                  (7U)
/*! ENBL - DMA Channel Enable
 *  0b0..DMA channel is disabled. This mode is primarily used during configuration of the DMAMux. The DMA has
 *       separate channel enables/disables, which should be used to disable or reconfigure a DMA channel.
 *  0b1..DMA channel is enabled
 */
#define DMAMUX_CHCFG_ENBL(x)                     (((uint8_t)(((uint8_t)(x)) << DMAMUX_CHCFG_ENBL_SHIFT)) & DMAMUX_CHCFG_ENBL_MASK)
/*! @} */

/* The count of DMAMUX_CHCFG */
#define DMAMUX_CHCFG_COUNT                       (1U)


/*!
 * @}
 */ /* end of group DMAMUX_Register_Masks */


/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX0 base address */
#define DMAMUX0_BASE                             (0x40021000u)
/** Peripheral DMAMUX0 base pointer */
#define DMAMUX0                                  ((DMAMUX_Type *)DMAMUX0_BASE)
/** Peripheral DMAMUX1 base address */
#define DMAMUX1_BASE                             (0x40022000u)
/** Peripheral DMAMUX1 base pointer */
#define DMAMUX1                                  ((DMAMUX_Type *)DMAMUX1_BASE)
/** Peripheral DMAMUX2 base address */
#define DMAMUX2_BASE                             (0x40023000u)
/** Peripheral DMAMUX2 base pointer */
#define DMAMUX2                                  ((DMAMUX_Type *)DMAMUX2_BASE)
/** Peripheral DMAMUX3 base address */
#define DMAMUX3_BASE                             (0x40024000u)
/** Peripheral DMAMUX3 base pointer */
#define DMAMUX3                                  ((DMAMUX_Type *)DMAMUX3_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        { DMAMUX0_BASE, DMAMUX1_BASE, DMAMUX2_BASE, DMAMUX3_BASE }
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         { DMAMUX0, DMAMUX1, DMAMUX2, DMAMUX3 }

/*!
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- EWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Peripheral_Access_Layer EWM Peripheral Access Layer
 * @{
 */

/** EWM - Register Layout Typedef */
typedef struct {
  __IO uint8_t CTRL;                               /**< Control Register, offset: 0x0 */
  __O  uint8_t SERV;                               /**< Service Register, offset: 0x1 */
  __IO uint8_t CMPL;                               /**< Compare Low Register, offset: 0x2 */
  __IO uint8_t CMPH;                               /**< Compare High Register, offset: 0x3 */
} EWM_Type;

/* ----------------------------------------------------------------------------
   -- EWM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup EWM_Register_Masks EWM Register Masks
 * @{
 */

/*! @name CTRL - Control Register */
/*! @{ */

#define EWM_CTRL_EWMEN_MASK                      (0x1U)
#define EWM_CTRL_EWMEN_SHIFT                     (0U)
/*! EWMEN - EWM enable.
 */
#define EWM_CTRL_EWMEN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_EWMEN_SHIFT)) & EWM_CTRL_EWMEN_MASK)

#define EWM_CTRL_ASSIN_MASK                      (0x2U)
#define EWM_CTRL_ASSIN_SHIFT                     (1U)
/*! ASSIN - EWM_in's Assertion State Select.
 */
#define EWM_CTRL_ASSIN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_ASSIN_SHIFT)) & EWM_CTRL_ASSIN_MASK)

#define EWM_CTRL_INEN_MASK                       (0x4U)
#define EWM_CTRL_INEN_SHIFT                      (2U)
/*! INEN - Input Enable.
 */
#define EWM_CTRL_INEN(x)                         (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_INEN_SHIFT)) & EWM_CTRL_INEN_MASK)

#define EWM_CTRL_INTEN_MASK                      (0x8U)
#define EWM_CTRL_INTEN_SHIFT                     (3U)
/*! INTEN - Interrupt Enable.
 */
#define EWM_CTRL_INTEN(x)                        (((uint8_t)(((uint8_t)(x)) << EWM_CTRL_INTEN_SHIFT)) & EWM_CTRL_INTEN_MASK)
/*! @} */

/*! @name SERV - Service Register */
/*! @{ */

#define EWM_SERV_SERVICE_MASK                    (0xFFU)
#define EWM_SERV_SERVICE_SHIFT                   (0U)
#define EWM_SERV_SERVICE(x)                      (((uint8_t)(((uint8_t)(x)) << EWM_SERV_SERVICE_SHIFT)) & EWM_SERV_SERVICE_MASK)
/*! @} */

/*! @name CMPL - Compare Low Register */
/*! @{ */

#define EWM_CMPL_COMPAREL_MASK                   (0xFFU)
#define EWM_CMPL_COMPAREL_SHIFT                  (0U)
#define EWM_CMPL_COMPAREL(x)                     (((uint8_t)(((uint8_t)(x)) << EWM_CMPL_COMPAREL_SHIFT)) & EWM_CMPL_COMPAREL_MASK)
/*! @} */

/*! @name CMPH - Compare High Register */
/*! @{ */

#define EWM_CMPH_COMPAREH_MASK                   (0xFFU)
#define EWM_CMPH_COMPAREH_SHIFT                  (0U)
#define EWM_CMPH_COMPAREH(x)                     (((uint8_t)(((uint8_t)(x)) << EWM_CMPH_COMPAREH_SHIFT)) & EWM_CMPH_COMPAREH_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group EWM_Register_Masks */


/* EWM - Peripheral instance base addresses */
/** Peripheral EWM base address */
#define EWM_BASE                                 (0x40061000u)
/** Peripheral EWM base pointer */
#define EWM                                      ((EWM_Type *)EWM_BASE)
/** Array initializer of EWM peripheral base addresses */
#define EWM_BASE_ADDRS                           { EWM_BASE }
/** Array initializer of EWM peripheral base pointers */
#define EWM_BASE_PTRS                            { EWM }
/** Interrupt vectors for the EWM peripheral type */
#define EWM_IRQS                                 { EWM_IRQn }

/*!
 * @}
 */ /* end of group EWM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- FTFA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Peripheral_Access_Layer FTFA Peripheral Access Layer
 * @{
 */

/** FTFA - Register Layout Typedef */
typedef struct {
  __IO uint8_t FSTAT;                              /**< Flash Status Register, offset: 0x0 */
  __IO uint8_t FCNFG;                              /**< Flash Configuration Register, offset: 0x1 */
  __I  uint8_t FSEC;                               /**< Flash Security Register, offset: 0x2 */
  __I  uint8_t FOPT;                               /**< Flash Option Register, offset: 0x3 */
  __IO uint8_t FCCOB3;                             /**< Flash Common Command Object Registers, offset: 0x4 */
  __IO uint8_t FCCOB2;                             /**< Flash Common Command Object Registers, offset: 0x5 */
  __IO uint8_t FCCOB1;                             /**< Flash Common Command Object Registers, offset: 0x6 */
  __IO uint8_t FCCOB0;                             /**< Flash Common Command Object Registers, offset: 0x7 */
  __IO uint8_t FCCOB7;                             /**< Flash Common Command Object Registers, offset: 0x8 */
  __IO uint8_t FCCOB6;                             /**< Flash Common Command Object Registers, offset: 0x9 */
  __IO uint8_t FCCOB5;                             /**< Flash Common Command Object Registers, offset: 0xA */
  __IO uint8_t FCCOB4;                             /**< Flash Common Command Object Registers, offset: 0xB */
  __IO uint8_t FCCOBB;                             /**< Flash Common Command Object Registers, offset: 0xC */
  __IO uint8_t FCCOBA;                             /**< Flash Common Command Object Registers, offset: 0xD */
  __IO uint8_t FCCOB9;                             /**< Flash Common Command Object Registers, offset: 0xE */
  __IO uint8_t FCCOB8;                             /**< Flash Common Command Object Registers, offset: 0xF */
  __IO uint8_t FPROT3;                             /**< Program Flash Protection Registers, offset: 0x10 */
  __IO uint8_t FPROT2;                             /**< Program Flash Protection Registers, offset: 0x11 */
  __IO uint8_t FPROT1;                             /**< Program Flash Protection Registers, offset: 0x12 */
  __IO uint8_t FPROT0;                             /**< Program Flash Protection Registers, offset: 0x13 */
} FTFA_Type;

/* ----------------------------------------------------------------------------
   -- FTFA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FTFA_Register_Masks FTFA Register Masks
 * @{
 */

/*! @name FSTAT - Flash Status Register */
/*! @{ */

#define FTFA_FSTAT_MGSTAT0_MASK                  (0x1U)
#define FTFA_FSTAT_MGSTAT0_SHIFT                 (0U)
/*! MGSTAT0 - Memory Controller Command Completion Status Flag
 */
#define FTFA_FSTAT_MGSTAT0(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_MGSTAT0_SHIFT)) & FTFA_FSTAT_MGSTAT0_MASK)

#define FTFA_FSTAT_FPVIOL_MASK                   (0x10U)
#define FTFA_FSTAT_FPVIOL_SHIFT                  (4U)
/*! FPVIOL - Flash Protection Violation Flag
 *  0b0..No protection violation detected
 *  0b1..Protection violation detected
 */
#define FTFA_FSTAT_FPVIOL(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_FPVIOL_SHIFT)) & FTFA_FSTAT_FPVIOL_MASK)

#define FTFA_FSTAT_ACCERR_MASK                   (0x20U)
#define FTFA_FSTAT_ACCERR_SHIFT                  (5U)
/*! ACCERR - Flash Access Error Flag
 *  0b0..No access error detected
 *  0b1..Access error detected
 */
#define FTFA_FSTAT_ACCERR(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_ACCERR_SHIFT)) & FTFA_FSTAT_ACCERR_MASK)

#define FTFA_FSTAT_RDCOLERR_MASK                 (0x40U)
#define FTFA_FSTAT_RDCOLERR_SHIFT                (6U)
/*! RDCOLERR - Flash Read Collision Error Flag
 *  0b0..No collision error detected
 *  0b1..Collision error detected
 */
#define FTFA_FSTAT_RDCOLERR(x)                   (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_RDCOLERR_SHIFT)) & FTFA_FSTAT_RDCOLERR_MASK)

#define FTFA_FSTAT_CCIF_MASK                     (0x80U)
#define FTFA_FSTAT_CCIF_SHIFT                    (7U)
/*! CCIF - Command Complete Interrupt Flag
 *  0b0..Flash command in progress
 *  0b1..Flash command has completed
 */
#define FTFA_FSTAT_CCIF(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FSTAT_CCIF_SHIFT)) & FTFA_FSTAT_CCIF_MASK)
/*! @} */

/*! @name FCNFG - Flash Configuration Register */
/*! @{ */

#define FTFA_FCNFG_ERSSUSP_MASK                  (0x10U)
#define FTFA_FCNFG_ERSSUSP_SHIFT                 (4U)
/*! ERSSUSP - Erase Suspend
 *  0b0..No suspend requested
 *  0b1..Suspend the current Erase Flash Sector command execution.
 */
#define FTFA_FCNFG_ERSSUSP(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSSUSP_SHIFT)) & FTFA_FCNFG_ERSSUSP_MASK)

#define FTFA_FCNFG_ERSAREQ_MASK                  (0x20U)
#define FTFA_FCNFG_ERSAREQ_SHIFT                 (5U)
/*! ERSAREQ - Erase All Request
 *  0b0..No request or request complete
 *  0b1..Request to: run the Erase All Blocks command, verify the erased state, program the security byte in the
 *       Flash Configuration Field to the unsecure state, and release MCU security by setting the FSEC[SEC] field to
 *       the unsecure state.
 */
#define FTFA_FCNFG_ERSAREQ(x)                    (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_ERSAREQ_SHIFT)) & FTFA_FCNFG_ERSAREQ_MASK)

#define FTFA_FCNFG_RDCOLLIE_MASK                 (0x40U)
#define FTFA_FCNFG_RDCOLLIE_SHIFT                (6U)
/*! RDCOLLIE - Read Collision Error Interrupt Enable
 *  0b0..Read collision error interrupt disabled
 *  0b1..Read collision error interrupt enabled. An interrupt request is generated whenever a flash memory read
 *       collision error is detected (see the description of FSTAT[RDCOLERR]).
 */
#define FTFA_FCNFG_RDCOLLIE(x)                   (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_RDCOLLIE_SHIFT)) & FTFA_FCNFG_RDCOLLIE_MASK)

#define FTFA_FCNFG_CCIE_MASK                     (0x80U)
#define FTFA_FCNFG_CCIE_SHIFT                    (7U)
/*! CCIE - Command Complete Interrupt Enable
 *  0b0..Command complete interrupt disabled
 *  0b1..Command complete interrupt enabled. An interrupt request is generated whenever the FSTAT[CCIF] flag is set.
 */
#define FTFA_FCNFG_CCIE(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FCNFG_CCIE_SHIFT)) & FTFA_FCNFG_CCIE_MASK)
/*! @} */

/*! @name FSEC - Flash Security Register */
/*! @{ */

#define FTFA_FSEC_SEC_MASK                       (0x3U)
#define FTFA_FSEC_SEC_SHIFT                      (0U)
/*! SEC - Flash Security
 *  0b00..MCU security status is secure.
 *  0b01..MCU security status is secure.
 *  0b10..MCU security status is unsecure. (The standard shipping condition of the flash memory module is unsecure.)
 *  0b11..MCU security status is secure.
 */
#define FTFA_FSEC_SEC(x)                         (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_SEC_SHIFT)) & FTFA_FSEC_SEC_MASK)

#define FTFA_FSEC_FSLACC_MASK                    (0xCU)
#define FTFA_FSEC_FSLACC_SHIFT                   (2U)
/*! FSLACC - Factory Security Level Access Code
 *  0b00..NXP factory access granted
 *  0b01..NXP factory access denied
 *  0b10..NXP factory access denied
 *  0b11..NXP factory access granted
 */
#define FTFA_FSEC_FSLACC(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_FSLACC_SHIFT)) & FTFA_FSEC_FSLACC_MASK)

#define FTFA_FSEC_MEEN_MASK                      (0x30U)
#define FTFA_FSEC_MEEN_SHIFT                     (4U)
/*! MEEN - Mass Erase Enable
 *  0b00..Mass erase is enabled
 *  0b01..Mass erase is enabled
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define FTFA_FSEC_MEEN(x)                        (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_MEEN_SHIFT)) & FTFA_FSEC_MEEN_MASK)

#define FTFA_FSEC_KEYEN_MASK                     (0xC0U)
#define FTFA_FSEC_KEYEN_SHIFT                    (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b00..Backdoor key access disabled
 *  0b01..Backdoor key access disabled (preferred KEYEN state to disable backdoor key access)
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define FTFA_FSEC_KEYEN(x)                       (((uint8_t)(((uint8_t)(x)) << FTFA_FSEC_KEYEN_SHIFT)) & FTFA_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Flash Option Register */
/*! @{ */

#define FTFA_FOPT_OPT_MASK                       (0xFFU)
#define FTFA_FOPT_OPT_SHIFT                      (0U)
/*! OPT - Nonvolatile Option
 */
#define FTFA_FOPT_OPT(x)                         (((uint8_t)(((uint8_t)(x)) << FTFA_FOPT_OPT_SHIFT)) & FTFA_FOPT_OPT_MASK)
/*! @} */

/*! @name FCCOB3 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB3_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB3_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB3_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB3_CCOBn_SHIFT)) & FTFA_FCCOB3_CCOBn_MASK)
/*! @} */

/*! @name FCCOB2 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB2_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB2_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB2_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB2_CCOBn_SHIFT)) & FTFA_FCCOB2_CCOBn_MASK)
/*! @} */

/*! @name FCCOB1 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB1_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB1_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB1_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB1_CCOBn_SHIFT)) & FTFA_FCCOB1_CCOBn_MASK)
/*! @} */

/*! @name FCCOB0 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB0_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB0_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB0_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB0_CCOBn_SHIFT)) & FTFA_FCCOB0_CCOBn_MASK)
/*! @} */

/*! @name FCCOB7 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB7_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB7_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB7_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB7_CCOBn_SHIFT)) & FTFA_FCCOB7_CCOBn_MASK)
/*! @} */

/*! @name FCCOB6 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB6_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB6_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB6_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB6_CCOBn_SHIFT)) & FTFA_FCCOB6_CCOBn_MASK)
/*! @} */

/*! @name FCCOB5 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB5_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB5_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB5_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB5_CCOBn_SHIFT)) & FTFA_FCCOB5_CCOBn_MASK)
/*! @} */

/*! @name FCCOB4 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB4_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB4_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB4_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB4_CCOBn_SHIFT)) & FTFA_FCCOB4_CCOBn_MASK)
/*! @} */

/*! @name FCCOBB - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOBB_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOBB_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOBB_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBB_CCOBn_SHIFT)) & FTFA_FCCOBB_CCOBn_MASK)
/*! @} */

/*! @name FCCOBA - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOBA_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOBA_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOBA_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOBA_CCOBn_SHIFT)) & FTFA_FCCOBA_CCOBn_MASK)
/*! @} */

/*! @name FCCOB9 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB9_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB9_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB9_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB9_CCOBn_SHIFT)) & FTFA_FCCOB9_CCOBn_MASK)
/*! @} */

/*! @name FCCOB8 - Flash Common Command Object Registers */
/*! @{ */

#define FTFA_FCCOB8_CCOBn_MASK                   (0xFFU)
#define FTFA_FCCOB8_CCOBn_SHIFT                  (0U)
#define FTFA_FCCOB8_CCOBn(x)                     (((uint8_t)(((uint8_t)(x)) << FTFA_FCCOB8_CCOBn_SHIFT)) & FTFA_FCCOB8_CCOBn_MASK)
/*! @} */

/*! @name FPROT3 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT3_PROT_MASK                    (0xFFU)
#define FTFA_FPROT3_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT3_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT3_PROT_SHIFT)) & FTFA_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT2_PROT_MASK                    (0xFFU)
#define FTFA_FPROT2_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT2_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT2_PROT_SHIFT)) & FTFA_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT1_PROT_MASK                    (0xFFU)
#define FTFA_FPROT1_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT1_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT1_PROT_SHIFT)) & FTFA_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Program Flash Protection Registers */
/*! @{ */

#define FTFA_FPROT0_PROT_MASK                    (0xFFU)
#define FTFA_FPROT0_PROT_SHIFT                   (0U)
/*! PROT - Program Flash Region Protect
 *  0b00000000..Program flash region is protected.
 *  0b00000001..Program flash region is not protected
 */
#define FTFA_FPROT0_PROT(x)                      (((uint8_t)(((uint8_t)(x)) << FTFA_FPROT0_PROT_SHIFT)) & FTFA_FPROT0_PROT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FTFA_Register_Masks */


/* FTFA - Peripheral instance base addresses */
/** Peripheral FTFA base address */
#define FTFA_BASE                                (0x40020000u)
/** Peripheral FTFA base pointer */
#define FTFA                                     ((FTFA_Type *)FTFA_BASE)
/** Array initializer of FTFA peripheral base addresses */
#define FTFA_BASE_ADDRS                          { FTFA_BASE }
/** Array initializer of FTFA peripheral base pointers */
#define FTFA_BASE_PTRS                           { FTFA }
/** Interrupt vectors for the FTFA peripheral type */
#define FTFA_COMMAND_COMPLETE_IRQS               { FTFA_IRQn }

/*!
 * @}
 */ /* end of group FTFA_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint8_t PDOR;                               /**< Port Data Output Register, offset: 0x0 */
       uint8_t RESERVED_0[15];
  __I  uint8_t PDIR;                               /**< Port Data Input Register, offset: 0x10 */
       uint8_t RESERVED_1[3];
  __IO uint8_t PDDR;                               /**< Port Data Direction Register, offset: 0x14 */
       uint8_t RESERVED_2[7];
  __IO uint8_t GACR;                               /**< GPIO Attribute Checker Register, offset: 0x1C */
} GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
/*! @{ */

#define GPIO_PDOR_PDO_MASK                       (0xFFU)
#define GPIO_PDOR_PDO_SHIFT                      (0U)
/*! PDO - Port Data Output
 *  0b00000000..Logic level 0 is driven on pin, provided pin is configured for general-purpose output.
 *  0b00000001..Logic level 1 is driven on pin, provided pin is configured for general-purpose output.
 */
#define GPIO_PDOR_PDO(x)                         (((uint8_t)(((uint8_t)(x)) << GPIO_PDOR_PDO_SHIFT)) & GPIO_PDOR_PDO_MASK)
/*! @} */

/*! @name PDIR - Port Data Input Register */
/*! @{ */

#define GPIO_PDIR_PDI_MASK                       (0xFFU)
#define GPIO_PDIR_PDI_SHIFT                      (0U)
/*! PDI - Port Data Input
 *  0b00000000..Pin logic level is logic 0, or is not configured for use by digital function.
 *  0b00000001..Pin logic level is logic 1.
 */
#define GPIO_PDIR_PDI(x)                         (((uint8_t)(((uint8_t)(x)) << GPIO_PDIR_PDI_SHIFT)) & GPIO_PDIR_PDI_MASK)
/*! @} */

/*! @name PDDR - Port Data Direction Register */
/*! @{ */

#define GPIO_PDDR_PDD_MASK                       (0xFFU)
#define GPIO_PDDR_PDD_SHIFT                      (0U)
/*! PDD - Port Data Direction
 *  0b00000000..Pin is configured as general-purpose input, for the GPIO function.
 *  0b00000001..Pin is configured as general-purpose output, for the GPIO function.
 */
#define GPIO_PDDR_PDD(x)                         (((uint8_t)(((uint8_t)(x)) << GPIO_PDDR_PDD_SHIFT)) & GPIO_PDDR_PDD_MASK)
/*! @} */

/*! @name GACR - GPIO Attribute Checker Register */
/*! @{ */

#define GPIO_GACR_ACB_MASK                       (0x7U)
#define GPIO_GACR_ACB_SHIFT                      (0U)
/*! ACB - Attribute Check Byte
 *  0b000..User nonsecure: Read + Write; User Secure: Read + Write; Privileged Secure: Read + Write
 *  0b001..User nonsecure: Read; User Secure: Read + Write; Privileged Secure: Read + Write
 *  0b010..User nonsecure: None; User Secure: Read + Write; Privileged Secure: Read + Write
 *  0b011..User nonsecure: Read; User Secure: Read; Privileged Secure: Read + Write
 *  0b100..User nonsecure: None; User Secure: Read; Privileged Secure: Read + Write
 *  0b101..User nonsecure: None; User Secure: None; Privileged Secure: Read + Write
 *  0b110..User nonsecure: None; User Secure: None; Privileged Secure: Read
 *  0b111..User nonsecure: None; User Secure: None; Privileged Secure: None
 */
#define GPIO_GACR_ACB(x)                         (((uint8_t)(((uint8_t)(x)) << GPIO_GACR_ACB_SHIFT)) & GPIO_GACR_ACB_MASK)

#define GPIO_GACR_ROB_MASK                       (0x80U)
#define GPIO_GACR_ROB_SHIFT                      (7U)
/*! ROB - Read-Only Byte
 *  0b0..Writes to the ACB are allowed.
 *  0b1..Writes to the ACB are ignored.
 */
#define GPIO_GACR_ROB(x)                         (((uint8_t)(((uint8_t)(x)) << GPIO_GACR_ROB_SHIFT)) & GPIO_GACR_ROB_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIOA base address */
#define GPIOA_BASE                               (0x400FF000u)
/** Peripheral GPIOA base pointer */
#define GPIOA                                    ((GPIO_Type *)GPIOA_BASE)
/** Peripheral GPIOB base address */
#define GPIOB_BASE                               (0x400FF001u)
/** Peripheral GPIOB base pointer */
#define GPIOB                                    ((GPIO_Type *)GPIOB_BASE)
/** Peripheral GPIOC base address */
#define GPIOC_BASE                               (0x400FF002u)
/** Peripheral GPIOC base pointer */
#define GPIOC                                    ((GPIO_Type *)GPIOC_BASE)
/** Peripheral GPIOD base address */
#define GPIOD_BASE                               (0x400FF003u)
/** Peripheral GPIOD base pointer */
#define GPIOD                                    ((GPIO_Type *)GPIOD_BASE)
/** Peripheral GPIOE base address */
#define GPIOE_BASE                               (0x400FF040u)
/** Peripheral GPIOE base pointer */
#define GPIOE                                    ((GPIO_Type *)GPIOE_BASE)
/** Peripheral GPIOF base address */
#define GPIOF_BASE                               (0x400FF041u)
/** Peripheral GPIOF base pointer */
#define GPIOF                                    ((GPIO_Type *)GPIOF_BASE)
/** Peripheral GPIOG base address */
#define GPIOG_BASE                               (0x400FF042u)
/** Peripheral GPIOG base pointer */
#define GPIOG                                    ((GPIO_Type *)GPIOG_BASE)
/** Peripheral GPIOH base address */
#define GPIOH_BASE                               (0x400FF043u)
/** Peripheral GPIOH base pointer */
#define GPIOH                                    ((GPIO_Type *)GPIOH_BASE)
/** Peripheral GPIOI base address */
#define GPIOI_BASE                               (0x400FF080u)
/** Peripheral GPIOI base pointer */
#define GPIOI                                    ((GPIO_Type *)GPIOI_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define GPIO_BASE_ADDRS                          { GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOF_BASE, GPIOG_BASE, GPIOH_BASE, GPIOI_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define GPIO_BASE_PTRS                           { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH, GPIOI }

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
  __IO uint8_t A1;                                 /**< I2C Address Register 1, offset: 0x0 */
  __IO uint8_t F;                                  /**< I2C Frequency Divider register, offset: 0x1 */
  __IO uint8_t C1;                                 /**< I2C Control Register 1, offset: 0x2 */
  __IO uint8_t S;                                  /**< I2C Status register, offset: 0x3 */
  __IO uint8_t D;                                  /**< I2C Data I/O register, offset: 0x4 */
  __IO uint8_t C2;                                 /**< I2C Control Register 2, offset: 0x5 */
  __IO uint8_t FLT;                                /**< I2C Programmable Input Glitch Filter Register, offset: 0x6 */
  __IO uint8_t RA;                                 /**< I2C Range Address register, offset: 0x7 */
  __IO uint8_t SMB;                                /**< I2C SMBus Control and Status register, offset: 0x8 */
  __IO uint8_t A2;                                 /**< I2C Address Register 2, offset: 0x9 */
  __IO uint8_t SLTH;                               /**< I2C SCL Low Timeout Register High, offset: 0xA */
  __IO uint8_t SLTL;                               /**< I2C SCL Low Timeout Register Low, offset: 0xB */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name A1 - I2C Address Register 1 */
/*! @{ */

#define I2C_A1_AD_MASK                           (0xFEU)
#define I2C_A1_AD_SHIFT                          (1U)
/*! AD - Address
 */
#define I2C_A1_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_A1_AD_SHIFT)) & I2C_A1_AD_MASK)
/*! @} */

/*! @name F - I2C Frequency Divider register */
/*! @{ */

#define I2C_F_ICR_MASK                           (0x3FU)
#define I2C_F_ICR_SHIFT                          (0U)
/*! ICR - ClockRate
 */
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_F_ICR_SHIFT)) & I2C_F_ICR_MASK)

#define I2C_F_MULT_MASK                          (0xC0U)
#define I2C_F_MULT_SHIFT                         (6U)
/*! MULT - Multiplier Factor
 *  0b00..mul = 1
 *  0b01..mul = 2
 *  0b10..mul = 4
 *  0b11..Reserved
 */
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_F_MULT_SHIFT)) & I2C_F_MULT_MASK)
/*! @} */

/*! @name C1 - I2C Control Register 1 */
/*! @{ */

#define I2C_C1_DMAEN_MASK                        (0x1U)
#define I2C_C1_DMAEN_SHIFT                       (0U)
/*! DMAEN - DMA Enable
 *  0b0..All DMA signalling disabled.
 *  0b1..DMA transfer is enabled. While SMB[FACK] = 0, the following conditions trigger the DMA request: a data
 *       byte is received, and either address or data is transmitted. (ACK/NACK is automatic) the first byte received
 *       matches the A1 register or is a general call address. If any address matching occurs, S[IAAS] and S[TCF]
 *       are set. If the direction of transfer is known from master to slave, then it is not required to check
 *       S[SRW]. With this assumption, DMA can also be used in this case. In other cases, if the master reads data from
 *       the slave, then it is required to rewrite the C1 register operation. With this assumption, DMA cannot be
 *       used. When FACK = 1, an address or a data byte is transmitted.
 */
#define I2C_C1_DMAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_DMAEN_SHIFT)) & I2C_C1_DMAEN_MASK)

#define I2C_C1_WUEN_MASK                         (0x2U)
#define I2C_C1_WUEN_SHIFT                        (1U)
/*! WUEN - Wakeup Enable
 *  0b0..Normal operation. No interrupt generated when address matching in low power mode.
 *  0b1..Enables the wakeup function in low power mode.
 */
#define I2C_C1_WUEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_WUEN_SHIFT)) & I2C_C1_WUEN_MASK)

#define I2C_C1_RSTA_MASK                         (0x4U)
#define I2C_C1_RSTA_SHIFT                        (2U)
/*! RSTA - Repeat START
 */
#define I2C_C1_RSTA(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_RSTA_SHIFT)) & I2C_C1_RSTA_MASK)

#define I2C_C1_TXAK_MASK                         (0x8U)
#define I2C_C1_TXAK_SHIFT                        (3U)
/*! TXAK - Transmit Acknowledge Enable
 *  0b0..An acknowledge signal is sent to the bus on the following receiving byte (if FACK is cleared) or the
 *       current receiving byte (if FACK is set).
 *  0b1..No acknowledge signal is sent to the bus on the following receiving data byte (if FACK is cleared) or the
 *       current receiving data byte (if FACK is set).
 */
#define I2C_C1_TXAK(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C1_TXAK_SHIFT)) & I2C_C1_TXAK_MASK)

#define I2C_C1_TX_MASK                           (0x10U)
#define I2C_C1_TX_SHIFT                          (4U)
/*! TX - Transmit Mode Select
 *  0b0..Receive
 *  0b1..Transmit
 */
#define I2C_C1_TX(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C1_TX_SHIFT)) & I2C_C1_TX_MASK)

#define I2C_C1_MST_MASK                          (0x20U)
#define I2C_C1_MST_SHIFT                         (5U)
/*! MST - Master Mode Select
 *  0b0..Slave mode
 *  0b1..Master mode
 */
#define I2C_C1_MST(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_C1_MST_SHIFT)) & I2C_C1_MST_MASK)

#define I2C_C1_IICIE_MASK                        (0x40U)
#define I2C_C1_IICIE_SHIFT                       (6U)
/*! IICIE - I2C Interrupt Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C1_IICIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICIE_SHIFT)) & I2C_C1_IICIE_MASK)

#define I2C_C1_IICEN_MASK                        (0x80U)
#define I2C_C1_IICEN_SHIFT                       (7U)
/*! IICEN - I2C Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C1_IICEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C1_IICEN_SHIFT)) & I2C_C1_IICEN_MASK)
/*! @} */

/*! @name S - I2C Status register */
/*! @{ */

#define I2C_S_RXAK_MASK                          (0x1U)
#define I2C_S_RXAK_SHIFT                         (0U)
/*! RXAK - Receive Acknowledge
 *  0b0..Acknowledge signal was received after the completion of one byte of data transmission on the bus
 *  0b1..No acknowledge signal detected
 */
#define I2C_S_RXAK(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_RXAK_SHIFT)) & I2C_S_RXAK_MASK)

#define I2C_S_IICIF_MASK                         (0x2U)
#define I2C_S_IICIF_SHIFT                        (1U)
/*! IICIF - Interrupt Flag
 *  0b0..No interrupt pending
 *  0b1..Interrupt pending
 */
#define I2C_S_IICIF(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_S_IICIF_SHIFT)) & I2C_S_IICIF_MASK)

#define I2C_S_SRW_MASK                           (0x4U)
#define I2C_S_SRW_SHIFT                          (2U)
/*! SRW - Slave Read/Write
 *  0b0..Slave receive, master writing to slave
 *  0b1..Slave transmit, master reading from slave
 */
#define I2C_S_SRW(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_SRW_SHIFT)) & I2C_S_SRW_MASK)

#define I2C_S_RAM_MASK                           (0x8U)
#define I2C_S_RAM_SHIFT                          (3U)
/*! RAM - Range Address Match
 *  0b0..Not addressed
 *  0b1..Addressed as a slave
 */
#define I2C_S_RAM(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_RAM_SHIFT)) & I2C_S_RAM_MASK)

#define I2C_S_ARBL_MASK                          (0x10U)
#define I2C_S_ARBL_SHIFT                         (4U)
/*! ARBL - Arbitration Lost
 *  0b0..Standard bus operation.
 *  0b1..Loss of arbitration.
 */
#define I2C_S_ARBL(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_ARBL_SHIFT)) & I2C_S_ARBL_MASK)

#define I2C_S_BUSY_MASK                          (0x20U)
#define I2C_S_BUSY_SHIFT                         (5U)
/*! BUSY - Bus Busy
 *  0b0..Bus is idle
 *  0b1..Bus is busy
 */
#define I2C_S_BUSY(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_BUSY_SHIFT)) & I2C_S_BUSY_MASK)

#define I2C_S_IAAS_MASK                          (0x40U)
#define I2C_S_IAAS_SHIFT                         (6U)
/*! IAAS - Addressed As A Slave
 *  0b0..Not addressed
 *  0b1..Addressed as a slave
 */
#define I2C_S_IAAS(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_S_IAAS_SHIFT)) & I2C_S_IAAS_MASK)

#define I2C_S_TCF_MASK                           (0x80U)
#define I2C_S_TCF_SHIFT                          (7U)
/*! TCF - Transfer Complete Flag
 *  0b0..Transfer in progress
 *  0b1..Transfer complete
 */
#define I2C_S_TCF(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_S_TCF_SHIFT)) & I2C_S_TCF_MASK)
/*! @} */

/*! @name D - I2C Data I/O register */
/*! @{ */

#define I2C_D_DATA_MASK                          (0xFFU)
#define I2C_D_DATA_SHIFT                         (0U)
/*! DATA - Data
 */
#define I2C_D_DATA(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_D_DATA_SHIFT)) & I2C_D_DATA_MASK)
/*! @} */

/*! @name C2 - I2C Control Register 2 */
/*! @{ */

#define I2C_C2_AD_MASK                           (0x7U)
#define I2C_C2_AD_SHIFT                          (0U)
/*! AD - Slave Address
 */
#define I2C_C2_AD(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_C2_AD_SHIFT)) & I2C_C2_AD_MASK)

#define I2C_C2_RMEN_MASK                         (0x8U)
#define I2C_C2_RMEN_SHIFT                        (3U)
/*! RMEN - Range Address Matching Enable
 *  0b0..Range mode disabled. No address matching occurs for an address within the range of values of the A1 and RA registers.
 *  0b1..Range mode enabled. Address matching occurs when a slave receives an address within the range of values of the A1 and RA registers.
 */
#define I2C_C2_RMEN(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_RMEN_SHIFT)) & I2C_C2_RMEN_MASK)

#define I2C_C2_SBRC_MASK                         (0x10U)
#define I2C_C2_SBRC_SHIFT                        (4U)
/*! SBRC - Slave Baud Rate Control
 *  0b0..The slave baud rate follows the master baud rate and clock stretching may occur
 *  0b1..Slave baud rate is independent of the master baud rate
 */
#define I2C_C2_SBRC(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_SBRC_SHIFT)) & I2C_C2_SBRC_MASK)

#define I2C_C2_HDRS_MASK                         (0x20U)
#define I2C_C2_HDRS_SHIFT                        (5U)
/*! HDRS - High Drive Select
 *  0b0..Normal drive mode
 *  0b1..High drive mode
 */
#define I2C_C2_HDRS(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_C2_HDRS_SHIFT)) & I2C_C2_HDRS_MASK)

#define I2C_C2_ADEXT_MASK                        (0x40U)
#define I2C_C2_ADEXT_SHIFT                       (6U)
/*! ADEXT - Address Extension
 *  0b0..7-bit address scheme
 *  0b1..10-bit address scheme
 */
#define I2C_C2_ADEXT(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_ADEXT_SHIFT)) & I2C_C2_ADEXT_MASK)

#define I2C_C2_GCAEN_MASK                        (0x80U)
#define I2C_C2_GCAEN_SHIFT                       (7U)
/*! GCAEN - General Call Address Enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define I2C_C2_GCAEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_C2_GCAEN_SHIFT)) & I2C_C2_GCAEN_MASK)
/*! @} */

/*! @name FLT - I2C Programmable Input Glitch Filter Register */
/*! @{ */

#define I2C_FLT_FLT_MASK                         (0xFU)
#define I2C_FLT_FLT_SHIFT                        (0U)
/*! FLT - I2C Programmable Filter Factor
 *  0b0000..No filter/bypass
 */
#define I2C_FLT_FLT(x)                           (((uint8_t)(((uint8_t)(x)) << I2C_FLT_FLT_SHIFT)) & I2C_FLT_FLT_MASK)

#define I2C_FLT_STARTF_MASK                      (0x10U)
#define I2C_FLT_STARTF_SHIFT                     (4U)
/*! STARTF - I2C Bus Start Detect Flag
 *  0b0..No start happens on I2C bus
 *  0b1..Start detected on I2C bus
 */
#define I2C_FLT_STARTF(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STARTF_SHIFT)) & I2C_FLT_STARTF_MASK)

#define I2C_FLT_SSIE_MASK                        (0x20U)
#define I2C_FLT_SSIE_SHIFT                       (5U)
/*! SSIE - I2C Bus Stop or Start Interrupt Enable
 *  0b0..Stop or start detection interrupt is disabled
 *  0b1..Stop or start detection interrupt is enabled
 */
#define I2C_FLT_SSIE(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SSIE_SHIFT)) & I2C_FLT_SSIE_MASK)

#define I2C_FLT_STOPF_MASK                       (0x40U)
#define I2C_FLT_STOPF_SHIFT                      (6U)
/*! STOPF - I2C Bus Stop Detect Flag
 *  0b0..No stop happens on I2C bus
 *  0b1..Stop detected on I2C bus
 */
#define I2C_FLT_STOPF(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_FLT_STOPF_SHIFT)) & I2C_FLT_STOPF_MASK)

#define I2C_FLT_SHEN_MASK                        (0x80U)
#define I2C_FLT_SHEN_SHIFT                       (7U)
/*! SHEN - Stop Hold Enable
 *  0b0..Stop holdoff is disabled. The MCU's entry to stop mode is not gated.
 *  0b1..Stop holdoff is enabled.
 */
#define I2C_FLT_SHEN(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_FLT_SHEN_SHIFT)) & I2C_FLT_SHEN_MASK)
/*! @} */

/*! @name RA - I2C Range Address register */
/*! @{ */

#define I2C_RA_RAD_MASK                          (0xFEU)
#define I2C_RA_RAD_SHIFT                         (1U)
/*! RAD - Range Slave Address
 */
#define I2C_RA_RAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_RA_RAD_SHIFT)) & I2C_RA_RAD_MASK)
/*! @} */

/*! @name SMB - I2C SMBus Control and Status register */
/*! @{ */

#define I2C_SMB_SHTF2IE_MASK                     (0x1U)
#define I2C_SMB_SHTF2IE_SHIFT                    (0U)
/*! SHTF2IE - SHTF2 Interrupt Enable
 *  0b0..SHTF2 interrupt is disabled
 *  0b1..SHTF2 interrupt is enabled
 */
#define I2C_SMB_SHTF2IE(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2IE_SHIFT)) & I2C_SMB_SHTF2IE_MASK)

#define I2C_SMB_SHTF2_MASK                       (0x2U)
#define I2C_SMB_SHTF2_SHIFT                      (1U)
/*! SHTF2 - SCL High Timeout Flag 2
 *  0b0..No SCL high and SDA low timeout occurs
 *  0b1..SCL high and SDA low timeout occurs
 */
#define I2C_SMB_SHTF2(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF2_SHIFT)) & I2C_SMB_SHTF2_MASK)

#define I2C_SMB_SHTF1_MASK                       (0x4U)
#define I2C_SMB_SHTF1_SHIFT                      (2U)
/*! SHTF1 - SCL High Timeout Flag 1
 *  0b0..No SCL high and SDA high timeout occurs
 *  0b1..SCL high and SDA high timeout occurs
 */
#define I2C_SMB_SHTF1(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SHTF1_SHIFT)) & I2C_SMB_SHTF1_MASK)

#define I2C_SMB_SLTF_MASK                        (0x8U)
#define I2C_SMB_SLTF_SHIFT                       (3U)
/*! SLTF - SCL Low Timeout Flag
 *  0b0..No low timeout occurs
 *  0b1..Low timeout occurs
 */
#define I2C_SMB_SLTF(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SLTF_SHIFT)) & I2C_SMB_SLTF_MASK)

#define I2C_SMB_TCKSEL_MASK                      (0x10U)
#define I2C_SMB_TCKSEL_SHIFT                     (4U)
/*! TCKSEL - Timeout Counter Clock Select
 *  0b0..Timeout counter counts at the frequency of the I2C module clock / 64
 *  0b1..Timeout counter counts at the frequency of the I2C module clock
 */
#define I2C_SMB_TCKSEL(x)                        (((uint8_t)(((uint8_t)(x)) << I2C_SMB_TCKSEL_SHIFT)) & I2C_SMB_TCKSEL_MASK)

#define I2C_SMB_SIICAEN_MASK                     (0x20U)
#define I2C_SMB_SIICAEN_SHIFT                    (5U)
/*! SIICAEN - Second I2C Address Enable
 *  0b0..I2C address register 2 matching is disabled
 *  0b1..I2C address register 2 matching is enabled
 */
#define I2C_SMB_SIICAEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_SIICAEN_SHIFT)) & I2C_SMB_SIICAEN_MASK)

#define I2C_SMB_ALERTEN_MASK                     (0x40U)
#define I2C_SMB_ALERTEN_SHIFT                    (6U)
/*! ALERTEN - SMBus Alert Response Address Enable
 *  0b0..SMBus alert response address matching is disabled
 *  0b1..SMBus alert response address matching is enabled
 */
#define I2C_SMB_ALERTEN(x)                       (((uint8_t)(((uint8_t)(x)) << I2C_SMB_ALERTEN_SHIFT)) & I2C_SMB_ALERTEN_MASK)

#define I2C_SMB_FACK_MASK                        (0x80U)
#define I2C_SMB_FACK_SHIFT                       (7U)
/*! FACK - Fast NACK/ACK Enable
 *  0b0..An ACK or NACK is sent on the following receiving data byte
 *  0b1..Writing 0 to TXAK after receiving a data byte generates an ACK. Writing 1 to TXAK after receiving a data byte generates a NACK.
 */
#define I2C_SMB_FACK(x)                          (((uint8_t)(((uint8_t)(x)) << I2C_SMB_FACK_SHIFT)) & I2C_SMB_FACK_MASK)
/*! @} */

/*! @name A2 - I2C Address Register 2 */
/*! @{ */

#define I2C_A2_SAD_MASK                          (0xFEU)
#define I2C_A2_SAD_SHIFT                         (1U)
/*! SAD - SMBus Address
 */
#define I2C_A2_SAD(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_A2_SAD_SHIFT)) & I2C_A2_SAD_MASK)
/*! @} */

/*! @name SLTH - I2C SCL Low Timeout Register High */
/*! @{ */

#define I2C_SLTH_SSLT_MASK                       (0xFFU)
#define I2C_SLTH_SSLT_SHIFT                      (0U)
/*! SSLT - SSLT[15:8]
 */
#define I2C_SLTH_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTH_SSLT_SHIFT)) & I2C_SLTH_SSLT_MASK)
/*! @} */

/*! @name SLTL - I2C SCL Low Timeout Register Low */
/*! @{ */

#define I2C_SLTL_SSLT_MASK                       (0xFFU)
#define I2C_SLTL_SSLT_SHIFT                      (0U)
/*! SSLT - SSLT[7:0]
 */
#define I2C_SLTL_SSLT(x)                         (((uint8_t)(((uint8_t)(x)) << I2C_SLTL_SSLT_SHIFT)) & I2C_SLTL_SSLT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40067000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40068000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1 }
/** Interrupt vectors for the I2C peripheral type */
#define I2C_IRQS                                 { I2C0_I2C1_IRQn, I2C0_I2C1_IRQn }

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LLWU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Peripheral_Access_Layer LLWU Peripheral Access Layer
 * @{
 */

/** LLWU - Register Layout Typedef */
typedef struct {
  __IO uint8_t PE1;                                /**< LLWU Pin Enable 1 register, offset: 0x0 */
  __IO uint8_t PE2;                                /**< LLWU Pin Enable 2 register, offset: 0x1 */
  __IO uint8_t PE3;                                /**< LLWU Pin Enable 3 register, offset: 0x2 */
  __IO uint8_t PE4;                                /**< LLWU Pin Enable 4 register, offset: 0x3 */
  __IO uint8_t ME;                                 /**< LLWU Module Enable register, offset: 0x4 */
  __IO uint8_t F1;                                 /**< LLWU Flag 1 register, offset: 0x5 */
  __IO uint8_t F2;                                 /**< LLWU Flag 2 register, offset: 0x6 */
  __I  uint8_t F3;                                 /**< LLWU Flag 3 register, offset: 0x7 */
  __IO uint8_t FILT1;                              /**< LLWU Pin Filter 1 register, offset: 0x8 */
  __IO uint8_t FILT2;                              /**< LLWU Pin Filter 2 register, offset: 0x9 */
} LLWU_Type;

/* ----------------------------------------------------------------------------
   -- LLWU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LLWU_Register_Masks LLWU Register Masks
 * @{
 */

/*! @name PE1 - LLWU Pin Enable 1 register */
/*! @{ */

#define LLWU_PE1_WUPE0_MASK                      (0x3U)
#define LLWU_PE1_WUPE0_SHIFT                     (0U)
/*! WUPE0 - Wakeup Pin Enable For LLWU_P0
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE0(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE0_SHIFT)) & LLWU_PE1_WUPE0_MASK)

#define LLWU_PE1_WUPE1_MASK                      (0xCU)
#define LLWU_PE1_WUPE1_SHIFT                     (2U)
/*! WUPE1 - Wakeup Pin Enable For LLWU_P1
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE1(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE1_SHIFT)) & LLWU_PE1_WUPE1_MASK)

#define LLWU_PE1_WUPE2_MASK                      (0x30U)
#define LLWU_PE1_WUPE2_SHIFT                     (4U)
/*! WUPE2 - Wakeup Pin Enable For LLWU_P2
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE2(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE2_SHIFT)) & LLWU_PE1_WUPE2_MASK)

#define LLWU_PE1_WUPE3_MASK                      (0xC0U)
#define LLWU_PE1_WUPE3_SHIFT                     (6U)
/*! WUPE3 - Wakeup Pin Enable For LLWU_P3
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE1_WUPE3(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE1_WUPE3_SHIFT)) & LLWU_PE1_WUPE3_MASK)
/*! @} */

/*! @name PE2 - LLWU Pin Enable 2 register */
/*! @{ */

#define LLWU_PE2_WUPE4_MASK                      (0x3U)
#define LLWU_PE2_WUPE4_SHIFT                     (0U)
/*! WUPE4 - Wakeup Pin Enable For LLWU_P4
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE4(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE4_SHIFT)) & LLWU_PE2_WUPE4_MASK)

#define LLWU_PE2_WUPE5_MASK                      (0xCU)
#define LLWU_PE2_WUPE5_SHIFT                     (2U)
/*! WUPE5 - Wakeup Pin Enable For LLWU_P5
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE5(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE5_SHIFT)) & LLWU_PE2_WUPE5_MASK)

#define LLWU_PE2_WUPE6_MASK                      (0x30U)
#define LLWU_PE2_WUPE6_SHIFT                     (4U)
/*! WUPE6 - Wakeup Pin Enable For LLWU_P6
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE6(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE6_SHIFT)) & LLWU_PE2_WUPE6_MASK)

#define LLWU_PE2_WUPE7_MASK                      (0xC0U)
#define LLWU_PE2_WUPE7_SHIFT                     (6U)
/*! WUPE7 - Wakeup Pin Enable For LLWU_P7
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE2_WUPE7(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE2_WUPE7_SHIFT)) & LLWU_PE2_WUPE7_MASK)
/*! @} */

/*! @name PE3 - LLWU Pin Enable 3 register */
/*! @{ */

#define LLWU_PE3_WUPE8_MASK                      (0x3U)
#define LLWU_PE3_WUPE8_SHIFT                     (0U)
/*! WUPE8 - Wakeup Pin Enable For LLWU_P8
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE8(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE8_SHIFT)) & LLWU_PE3_WUPE8_MASK)

#define LLWU_PE3_WUPE9_MASK                      (0xCU)
#define LLWU_PE3_WUPE9_SHIFT                     (2U)
/*! WUPE9 - Wakeup Pin Enable For LLWU_P9
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE9(x)                        (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE9_SHIFT)) & LLWU_PE3_WUPE9_MASK)

#define LLWU_PE3_WUPE10_MASK                     (0x30U)
#define LLWU_PE3_WUPE10_SHIFT                    (4U)
/*! WUPE10 - Wakeup Pin Enable For LLWU_P10
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE10(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE10_SHIFT)) & LLWU_PE3_WUPE10_MASK)

#define LLWU_PE3_WUPE11_MASK                     (0xC0U)
#define LLWU_PE3_WUPE11_SHIFT                    (6U)
/*! WUPE11 - Wakeup Pin Enable For LLWU_P11
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE3_WUPE11(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE3_WUPE11_SHIFT)) & LLWU_PE3_WUPE11_MASK)
/*! @} */

/*! @name PE4 - LLWU Pin Enable 4 register */
/*! @{ */

#define LLWU_PE4_WUPE12_MASK                     (0x3U)
#define LLWU_PE4_WUPE12_SHIFT                    (0U)
/*! WUPE12 - Wakeup Pin Enable For LLWU_P12
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE12(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE12_SHIFT)) & LLWU_PE4_WUPE12_MASK)

#define LLWU_PE4_WUPE13_MASK                     (0xCU)
#define LLWU_PE4_WUPE13_SHIFT                    (2U)
/*! WUPE13 - Wakeup Pin Enable For LLWU_P13
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE13(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE13_SHIFT)) & LLWU_PE4_WUPE13_MASK)

#define LLWU_PE4_WUPE14_MASK                     (0x30U)
#define LLWU_PE4_WUPE14_SHIFT                    (4U)
/*! WUPE14 - Wakeup Pin Enable For LLWU_P14
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE14(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE14_SHIFT)) & LLWU_PE4_WUPE14_MASK)

#define LLWU_PE4_WUPE15_MASK                     (0xC0U)
#define LLWU_PE4_WUPE15_SHIFT                    (6U)
/*! WUPE15 - Wakeup Pin Enable For LLWU_P15
 *  0b00..External input pin disabled as wakeup input
 *  0b01..External input pin enabled with rising edge detection
 *  0b10..External input pin enabled with falling edge detection
 *  0b11..External input pin enabled with any change detection
 */
#define LLWU_PE4_WUPE15(x)                       (((uint8_t)(((uint8_t)(x)) << LLWU_PE4_WUPE15_SHIFT)) & LLWU_PE4_WUPE15_MASK)
/*! @} */

/*! @name ME - LLWU Module Enable register */
/*! @{ */

#define LLWU_ME_WUME0_MASK                       (0x1U)
#define LLWU_ME_WUME0_SHIFT                      (0U)
/*! WUME0 - Wakeup Module Enable For Module 0
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME0_SHIFT)) & LLWU_ME_WUME0_MASK)

#define LLWU_ME_WUME1_MASK                       (0x2U)
#define LLWU_ME_WUME1_SHIFT                      (1U)
/*! WUME1 - Wakeup Module Enable for Module 1
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME1_SHIFT)) & LLWU_ME_WUME1_MASK)

#define LLWU_ME_WUME2_MASK                       (0x4U)
#define LLWU_ME_WUME2_SHIFT                      (2U)
/*! WUME2 - Wakeup Module Enable For Module 2
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME2_SHIFT)) & LLWU_ME_WUME2_MASK)

#define LLWU_ME_WUME3_MASK                       (0x8U)
#define LLWU_ME_WUME3_SHIFT                      (3U)
/*! WUME3 - Wakeup Module Enable For Module 3
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME3_SHIFT)) & LLWU_ME_WUME3_MASK)

#define LLWU_ME_WUME4_MASK                       (0x10U)
#define LLWU_ME_WUME4_SHIFT                      (4U)
/*! WUME4 - Wakeup Module Enable For Module 4
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME4_SHIFT)) & LLWU_ME_WUME4_MASK)

#define LLWU_ME_WUME5_MASK                       (0x20U)
#define LLWU_ME_WUME5_SHIFT                      (5U)
/*! WUME5 - Wakeup Module Enable For Module 5
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME5_SHIFT)) & LLWU_ME_WUME5_MASK)

#define LLWU_ME_WUME6_MASK                       (0x40U)
#define LLWU_ME_WUME6_SHIFT                      (6U)
/*! WUME6 - Wakeup Module Enable For Module 6
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME6_SHIFT)) & LLWU_ME_WUME6_MASK)

#define LLWU_ME_WUME7_MASK                       (0x80U)
#define LLWU_ME_WUME7_SHIFT                      (7U)
/*! WUME7 - Wakeup Module Enable For Module 7
 *  0b0..Internal module flag not used as wakeup source
 *  0b1..Internal module flag used as wakeup source
 */
#define LLWU_ME_WUME7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_ME_WUME7_SHIFT)) & LLWU_ME_WUME7_MASK)
/*! @} */

/*! @name F1 - LLWU Flag 1 register */
/*! @{ */

#define LLWU_F1_WUF0_MASK                        (0x1U)
#define LLWU_F1_WUF0_SHIFT                       (0U)
/*! WUF0 - Wakeup Flag For LLWU_P0
 *  0b0..LLWU_P0 input was not a wakeup source
 *  0b1..LLWU_P0 input was a wakeup source
 */
#define LLWU_F1_WUF0(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF0_SHIFT)) & LLWU_F1_WUF0_MASK)

#define LLWU_F1_WUF1_MASK                        (0x2U)
#define LLWU_F1_WUF1_SHIFT                       (1U)
/*! WUF1 - Wakeup Flag For LLWU_P1
 *  0b0..LLWU_P1 input was not a wakeup source
 *  0b1..LLWU_P1 input was a wakeup source
 */
#define LLWU_F1_WUF1(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF1_SHIFT)) & LLWU_F1_WUF1_MASK)

#define LLWU_F1_WUF2_MASK                        (0x4U)
#define LLWU_F1_WUF2_SHIFT                       (2U)
/*! WUF2 - Wakeup Flag For LLWU_P2
 *  0b0..LLWU_P2 input was not a wakeup source
 *  0b1..LLWU_P2 input was a wakeup source
 */
#define LLWU_F1_WUF2(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF2_SHIFT)) & LLWU_F1_WUF2_MASK)

#define LLWU_F1_WUF3_MASK                        (0x8U)
#define LLWU_F1_WUF3_SHIFT                       (3U)
/*! WUF3 - Wakeup Flag For LLWU_P3
 *  0b0..LLWU_P3 input was not a wake-up source
 *  0b1..LLWU_P3 input was a wake-up source
 */
#define LLWU_F1_WUF3(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF3_SHIFT)) & LLWU_F1_WUF3_MASK)

#define LLWU_F1_WUF4_MASK                        (0x10U)
#define LLWU_F1_WUF4_SHIFT                       (4U)
/*! WUF4 - Wakeup Flag For LLWU_P4
 *  0b0..LLWU_P4 input was not a wakeup source
 *  0b1..LLWU_P4 input was a wakeup source
 */
#define LLWU_F1_WUF4(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF4_SHIFT)) & LLWU_F1_WUF4_MASK)

#define LLWU_F1_WUF5_MASK                        (0x20U)
#define LLWU_F1_WUF5_SHIFT                       (5U)
/*! WUF5 - Wakeup Flag For LLWU_P5
 *  0b0..LLWU_P5 input was not a wakeup source
 *  0b1..LLWU_P5 input was a wakeup source
 */
#define LLWU_F1_WUF5(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF5_SHIFT)) & LLWU_F1_WUF5_MASK)

#define LLWU_F1_WUF6_MASK                        (0x40U)
#define LLWU_F1_WUF6_SHIFT                       (6U)
/*! WUF6 - Wakeup Flag For LLWU_P6
 *  0b0..LLWU_P6 input was not a wakeup source
 *  0b1..LLWU_P6 input was a wakeup source
 */
#define LLWU_F1_WUF6(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF6_SHIFT)) & LLWU_F1_WUF6_MASK)

#define LLWU_F1_WUF7_MASK                        (0x80U)
#define LLWU_F1_WUF7_SHIFT                       (7U)
/*! WUF7 - Wakeup Flag For LLWU_P7
 *  0b0..LLWU_P7 input was not a wakeup source
 *  0b1..LLWU_P7 input was a wakeup source
 */
#define LLWU_F1_WUF7(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F1_WUF7_SHIFT)) & LLWU_F1_WUF7_MASK)
/*! @} */

/*! @name F2 - LLWU Flag 2 register */
/*! @{ */

#define LLWU_F2_WUF8_MASK                        (0x1U)
#define LLWU_F2_WUF8_SHIFT                       (0U)
/*! WUF8 - Wakeup Flag For LLWU_P8
 *  0b0..LLWU_P8 input was not a wakeup source
 *  0b1..LLWU_P8 input was a wakeup source
 */
#define LLWU_F2_WUF8(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF8_SHIFT)) & LLWU_F2_WUF8_MASK)

#define LLWU_F2_WUF9_MASK                        (0x2U)
#define LLWU_F2_WUF9_SHIFT                       (1U)
/*! WUF9 - Wakeup Flag For LLWU_P9
 *  0b0..LLWU_P9 input was not a wakeup source
 *  0b1..LLWU_P9 input was a wakeup source
 */
#define LLWU_F2_WUF9(x)                          (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF9_SHIFT)) & LLWU_F2_WUF9_MASK)

#define LLWU_F2_WUF10_MASK                       (0x4U)
#define LLWU_F2_WUF10_SHIFT                      (2U)
/*! WUF10 - Wakeup Flag For LLWU_P10
 *  0b0..LLWU_P10 input was not a wakeup source
 *  0b1..LLWU_P10 input was a wakeup source
 */
#define LLWU_F2_WUF10(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF10_SHIFT)) & LLWU_F2_WUF10_MASK)

#define LLWU_F2_WUF11_MASK                       (0x8U)
#define LLWU_F2_WUF11_SHIFT                      (3U)
/*! WUF11 - Wakeup Flag For LLWU_P11
 *  0b0..LLWU_P11 input was not a wakeup source
 *  0b1..LLWU_P11 input was a wakeup source
 */
#define LLWU_F2_WUF11(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF11_SHIFT)) & LLWU_F2_WUF11_MASK)

#define LLWU_F2_WUF12_MASK                       (0x10U)
#define LLWU_F2_WUF12_SHIFT                      (4U)
/*! WUF12 - Wakeup Flag For LLWU_P12
 *  0b0..LLWU_P12 input was not a wakeup source
 *  0b1..LLWU_P12 input was a wakeup source
 */
#define LLWU_F2_WUF12(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF12_SHIFT)) & LLWU_F2_WUF12_MASK)

#define LLWU_F2_WUF13_MASK                       (0x20U)
#define LLWU_F2_WUF13_SHIFT                      (5U)
/*! WUF13 - Wakeup Flag For LLWU_P13
 *  0b0..LLWU_P13 input was not a wakeup source
 *  0b1..LLWU_P13 input was a wakeup source
 */
#define LLWU_F2_WUF13(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF13_SHIFT)) & LLWU_F2_WUF13_MASK)

#define LLWU_F2_WUF14_MASK                       (0x40U)
#define LLWU_F2_WUF14_SHIFT                      (6U)
/*! WUF14 - Wakeup Flag For LLWU_P14
 *  0b0..LLWU_P14 input was not a wakeup source
 *  0b1..LLWU_P14 input was a wakeup source
 */
#define LLWU_F2_WUF14(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF14_SHIFT)) & LLWU_F2_WUF14_MASK)

#define LLWU_F2_WUF15_MASK                       (0x80U)
#define LLWU_F2_WUF15_SHIFT                      (7U)
/*! WUF15 - Wakeup Flag For LLWU_P15
 *  0b0..LLWU_P15 input was not a wakeup source
 *  0b1..LLWU_P15 input was a wakeup source
 */
#define LLWU_F2_WUF15(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F2_WUF15_SHIFT)) & LLWU_F2_WUF15_MASK)
/*! @} */

/*! @name F3 - LLWU Flag 3 register */
/*! @{ */

#define LLWU_F3_MWUF0_MASK                       (0x1U)
#define LLWU_F3_MWUF0_SHIFT                      (0U)
/*! MWUF0 - Wakeup flag For module 0
 *  0b0..Module 0 input was not a wakeup source
 *  0b1..Module 0 input was a wakeup source
 */
#define LLWU_F3_MWUF0(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF0_SHIFT)) & LLWU_F3_MWUF0_MASK)

#define LLWU_F3_MWUF1_MASK                       (0x2U)
#define LLWU_F3_MWUF1_SHIFT                      (1U)
/*! MWUF1 - Wakeup flag For module 1
 *  0b0..Module 1 input was not a wakeup source
 *  0b1..Module 1 input was a wakeup source
 */
#define LLWU_F3_MWUF1(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF1_SHIFT)) & LLWU_F3_MWUF1_MASK)

#define LLWU_F3_MWUF2_MASK                       (0x4U)
#define LLWU_F3_MWUF2_SHIFT                      (2U)
/*! MWUF2 - Wakeup flag For module 2
 *  0b0..Module 2 input was not a wakeup source
 *  0b1..Module 2 input was a wakeup source
 */
#define LLWU_F3_MWUF2(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF2_SHIFT)) & LLWU_F3_MWUF2_MASK)

#define LLWU_F3_MWUF3_MASK                       (0x8U)
#define LLWU_F3_MWUF3_SHIFT                      (3U)
/*! MWUF3 - Wakeup flag For module 3
 *  0b0..Module 3 input was not a wakeup source
 *  0b1..Module 3 input was a wakeup source
 */
#define LLWU_F3_MWUF3(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF3_SHIFT)) & LLWU_F3_MWUF3_MASK)

#define LLWU_F3_MWUF4_MASK                       (0x10U)
#define LLWU_F3_MWUF4_SHIFT                      (4U)
/*! MWUF4 - Wakeup flag For module 4
 *  0b0..Module 4 input was not a wakeup source
 *  0b1..Module 4 input was a wakeup source
 */
#define LLWU_F3_MWUF4(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF4_SHIFT)) & LLWU_F3_MWUF4_MASK)

#define LLWU_F3_MWUF5_MASK                       (0x20U)
#define LLWU_F3_MWUF5_SHIFT                      (5U)
/*! MWUF5 - Wakeup flag For module 5
 *  0b0..Module 5 input was not a wakeup source
 *  0b1..Module 5 input was a wakeup source
 */
#define LLWU_F3_MWUF5(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF5_SHIFT)) & LLWU_F3_MWUF5_MASK)

#define LLWU_F3_MWUF6_MASK                       (0x40U)
#define LLWU_F3_MWUF6_SHIFT                      (6U)
/*! MWUF6 - Wakeup flag For module 6
 *  0b0..Module 6 input was not a wakeup source
 *  0b1..Module 6 input was a wakeup source
 */
#define LLWU_F3_MWUF6(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF6_SHIFT)) & LLWU_F3_MWUF6_MASK)

#define LLWU_F3_MWUF7_MASK                       (0x80U)
#define LLWU_F3_MWUF7_SHIFT                      (7U)
/*! MWUF7 - Wakeup flag For module 7
 *  0b0..Module 7 input was not a wakeup source
 *  0b1..Module 7 input was a wakeup source
 */
#define LLWU_F3_MWUF7(x)                         (((uint8_t)(((uint8_t)(x)) << LLWU_F3_MWUF7_SHIFT)) & LLWU_F3_MWUF7_MASK)
/*! @} */

/*! @name FILT1 - LLWU Pin Filter 1 register */
/*! @{ */

#define LLWU_FILT1_FILTSEL_MASK                  (0xFU)
#define LLWU_FILT1_FILTSEL_SHIFT                 (0U)
/*! FILTSEL - Filter Pin Select
 *  0b0000..Select LLWU_P0 for filter
 *  0b1111..Select LLWU_P15 for filter
 */
#define LLWU_FILT1_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTSEL_SHIFT)) & LLWU_FILT1_FILTSEL_MASK)

#define LLWU_FILT1_FILTE_MASK                    (0x60U)
#define LLWU_FILT1_FILTE_SHIFT                   (5U)
/*! FILTE - Digital Filter On External Pin
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT1_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTE_SHIFT)) & LLWU_FILT1_FILTE_MASK)

#define LLWU_FILT1_FILTF_MASK                    (0x80U)
#define LLWU_FILT1_FILTF_SHIFT                   (7U)
/*! FILTF - Filter Detect Flag
 *  0b0..Pin Filter 1 was not a wakeup source
 *  0b1..Pin Filter 1 was a wakeup source
 */
#define LLWU_FILT1_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT1_FILTF_SHIFT)) & LLWU_FILT1_FILTF_MASK)
/*! @} */

/*! @name FILT2 - LLWU Pin Filter 2 register */
/*! @{ */

#define LLWU_FILT2_FILTSEL_MASK                  (0xFU)
#define LLWU_FILT2_FILTSEL_SHIFT                 (0U)
/*! FILTSEL - Filter Pin Select
 *  0b0000..Select LLWU_P0 for filter
 *  0b1111..Select LLWU_P15 for filter
 */
#define LLWU_FILT2_FILTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTSEL_SHIFT)) & LLWU_FILT2_FILTSEL_MASK)

#define LLWU_FILT2_FILTE_MASK                    (0x60U)
#define LLWU_FILT2_FILTE_SHIFT                   (5U)
/*! FILTE - Digital Filter On External Pin
 *  0b00..Filter disabled
 *  0b01..Filter posedge detect enabled
 *  0b10..Filter negedge detect enabled
 *  0b11..Filter any edge detect enabled
 */
#define LLWU_FILT2_FILTE(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTE_SHIFT)) & LLWU_FILT2_FILTE_MASK)

#define LLWU_FILT2_FILTF_MASK                    (0x80U)
#define LLWU_FILT2_FILTF_SHIFT                   (7U)
/*! FILTF - Filter Detect Flag
 *  0b0..Pin Filter 2 was not a wakeup source
 *  0b1..Pin Filter 2 was a wakeup source
 */
#define LLWU_FILT2_FILTF(x)                      (((uint8_t)(((uint8_t)(x)) << LLWU_FILT2_FILTF_SHIFT)) & LLWU_FILT2_FILTF_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LLWU_Register_Masks */


/* LLWU - Peripheral instance base addresses */
/** Peripheral LLWU base address */
#define LLWU_BASE                                (0x4007C000u)
/** Peripheral LLWU base pointer */
#define LLWU                                     ((LLWU_Type *)LLWU_BASE)
/** Array initializer of LLWU peripheral base addresses */
#define LLWU_BASE_ADDRS                          { LLWU_BASE }
/** Array initializer of LLWU peripheral base pointers */
#define LLWU_BASE_PTRS                           { LLWU }
/** Interrupt vectors for the LLWU peripheral type */
#define LLWU_IRQS                                { LLWU_IRQn }

/*!
 * @}
 */ /* end of group LLWU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LPTMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Peripheral_Access_Layer LPTMR Peripheral Access Layer
 * @{
 */

/** LPTMR - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR;                               /**< Low Power Timer Control Status Register, offset: 0x0 */
  __IO uint32_t PSR;                               /**< Low Power Timer Prescale Register, offset: 0x4 */
  __IO uint32_t CMR;                               /**< Low Power Timer Compare Register, offset: 0x8 */
  __IO uint32_t CNR;                               /**< Low Power Timer Counter Register, offset: 0xC */
} LPTMR_Type;

/* ----------------------------------------------------------------------------
   -- LPTMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPTMR_Register_Masks LPTMR Register Masks
 * @{
 */

/*! @name CSR - Low Power Timer Control Status Register */
/*! @{ */

#define LPTMR_CSR_TEN_MASK                       (0x1U)
#define LPTMR_CSR_TEN_SHIFT                      (0U)
/*! TEN - Timer Enable
 *  0b0..LPTMR is disabled and internal logic is reset.
 *  0b1..LPTMR is enabled.
 */
#define LPTMR_CSR_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TEN_SHIFT)) & LPTMR_CSR_TEN_MASK)

#define LPTMR_CSR_TMS_MASK                       (0x2U)
#define LPTMR_CSR_TMS_SHIFT                      (1U)
/*! TMS - Timer Mode Select
 *  0b0..Time Counter mode.
 *  0b1..Pulse Counter mode.
 */
#define LPTMR_CSR_TMS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TMS_SHIFT)) & LPTMR_CSR_TMS_MASK)

#define LPTMR_CSR_TFC_MASK                       (0x4U)
#define LPTMR_CSR_TFC_SHIFT                      (2U)
/*! TFC - Timer Free-Running Counter
 *  0b0..CNR is reset whenever TCF is set.
 *  0b1..CNR is reset on overflow.
 */
#define LPTMR_CSR_TFC(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TFC_SHIFT)) & LPTMR_CSR_TFC_MASK)

#define LPTMR_CSR_TPP_MASK                       (0x8U)
#define LPTMR_CSR_TPP_SHIFT                      (3U)
/*! TPP - Timer Pin Polarity
 *  0b0..Pulse Counter input source is active-high, and the CNR will increment on the rising-edge.
 *  0b1..Pulse Counter input source is active-low, and the CNR will increment on the falling-edge.
 */
#define LPTMR_CSR_TPP(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPP_SHIFT)) & LPTMR_CSR_TPP_MASK)

#define LPTMR_CSR_TPS_MASK                       (0x30U)
#define LPTMR_CSR_TPS_SHIFT                      (4U)
/*! TPS - Timer Pin Select
 *  0b00..Pulse counter input 0 is selected.
 *  0b01..Pulse counter input 1 is selected.
 *  0b10..Pulse counter input 2 is selected.
 *  0b11..Pulse counter input 3 is selected.
 */
#define LPTMR_CSR_TPS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TPS_SHIFT)) & LPTMR_CSR_TPS_MASK)

#define LPTMR_CSR_TIE_MASK                       (0x40U)
#define LPTMR_CSR_TIE_SHIFT                      (6U)
/*! TIE - Timer Interrupt Enable
 *  0b0..Timer interrupt disabled.
 *  0b1..Timer interrupt enabled.
 */
#define LPTMR_CSR_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TIE_SHIFT)) & LPTMR_CSR_TIE_MASK)

#define LPTMR_CSR_TCF_MASK                       (0x80U)
#define LPTMR_CSR_TCF_SHIFT                      (7U)
/*! TCF - Timer Compare Flag
 *  0b0..The value of CNR is not equal to CMR and increments.
 *  0b1..The value of CNR is equal to CMR and increments.
 */
#define LPTMR_CSR_TCF(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_CSR_TCF_SHIFT)) & LPTMR_CSR_TCF_MASK)
/*! @} */

/*! @name PSR - Low Power Timer Prescale Register */
/*! @{ */

#define LPTMR_PSR_PCS_MASK                       (0x3U)
#define LPTMR_PSR_PCS_SHIFT                      (0U)
/*! PCS - Prescaler Clock Select
 *  0b00..Prescaler/glitch filter clock 0 selected.
 *  0b01..Prescaler/glitch filter clock 1 selected.
 *  0b10..Prescaler/glitch filter clock 2 selected.
 *  0b11..Prescaler/glitch filter clock 3 selected.
 */
#define LPTMR_PSR_PCS(x)                         (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PCS_SHIFT)) & LPTMR_PSR_PCS_MASK)

#define LPTMR_PSR_PBYP_MASK                      (0x4U)
#define LPTMR_PSR_PBYP_SHIFT                     (2U)
/*! PBYP - Prescaler Bypass
 *  0b0..Prescaler/glitch filter is enabled.
 *  0b1..Prescaler/glitch filter is bypassed.
 */
#define LPTMR_PSR_PBYP(x)                        (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PBYP_SHIFT)) & LPTMR_PSR_PBYP_MASK)

#define LPTMR_PSR_PRESCALE_MASK                  (0x78U)
#define LPTMR_PSR_PRESCALE_SHIFT                 (3U)
/*! PRESCALE - Prescale Value
 *  0b0000..Prescaler divides the prescaler clock by 2; glitch filter does not support this configuration.
 *  0b0001..Prescaler divides the prescaler clock by 4; glitch filter recognizes change on input pin after 2 rising clock edges.
 *  0b0010..Prescaler divides the prescaler clock by 8; glitch filter recognizes change on input pin after 4 rising clock edges.
 *  0b0011..Prescaler divides the prescaler clock by 16; glitch filter recognizes change on input pin after 8 rising clock edges.
 *  0b0100..Prescaler divides the prescaler clock by 32; glitch filter recognizes change on input pin after 16 rising clock edges.
 *  0b0101..Prescaler divides the prescaler clock by 64; glitch filter recognizes change on input pin after 32 rising clock edges.
 *  0b0110..Prescaler divides the prescaler clock by 128; glitch filter recognizes change on input pin after 64 rising clock edges.
 *  0b0111..Prescaler divides the prescaler clock by 256; glitch filter recognizes change on input pin after 128 rising clock edges.
 *  0b1000..Prescaler divides the prescaler clock by 512; glitch filter recognizes change on input pin after 256 rising clock edges.
 *  0b1001..Prescaler divides the prescaler clock by 1024; glitch filter recognizes change on input pin after 512 rising clock edges.
 *  0b1010..Prescaler divides the prescaler clock by 2048; glitch filter recognizes change on input pin after 1024 rising clock edges.
 *  0b1011..Prescaler divides the prescaler clock by 4096; glitch filter recognizes change on input pin after 2048 rising clock edges.
 *  0b1100..Prescaler divides the prescaler clock by 8192; glitch filter recognizes change on input pin after 4096 rising clock edges.
 *  0b1101..Prescaler divides the prescaler clock by 16,384; glitch filter recognizes change on input pin after 8192 rising clock edges.
 *  0b1110..Prescaler divides the prescaler clock by 32,768; glitch filter recognizes change on input pin after 16,384 rising clock edges.
 *  0b1111..Prescaler divides the prescaler clock by 65,536; glitch filter recognizes change on input pin after 32,768 rising clock edges.
 */
#define LPTMR_PSR_PRESCALE(x)                    (((uint32_t)(((uint32_t)(x)) << LPTMR_PSR_PRESCALE_SHIFT)) & LPTMR_PSR_PRESCALE_MASK)
/*! @} */

/*! @name CMR - Low Power Timer Compare Register */
/*! @{ */

#define LPTMR_CMR_COMPARE_MASK                   (0xFFFFU)
#define LPTMR_CMR_COMPARE_SHIFT                  (0U)
/*! COMPARE - Compare Value
 */
#define LPTMR_CMR_COMPARE(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CMR_COMPARE_SHIFT)) & LPTMR_CMR_COMPARE_MASK)
/*! @} */

/*! @name CNR - Low Power Timer Counter Register */
/*! @{ */

#define LPTMR_CNR_COUNTER_MASK                   (0xFFFFU)
#define LPTMR_CNR_COUNTER_SHIFT                  (0U)
/*! COUNTER - Counter Value
 */
#define LPTMR_CNR_COUNTER(x)                     (((uint32_t)(((uint32_t)(x)) << LPTMR_CNR_COUNTER_SHIFT)) & LPTMR_CNR_COUNTER_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group LPTMR_Register_Masks */


/* LPTMR - Peripheral instance base addresses */
/** Peripheral LPTMR base address */
#define LPTMR_BASE                               (0x4003C000u)
/** Peripheral LPTMR base pointer */
#define LPTMR                                    ((LPTMR_Type *)LPTMR_BASE)
/** Array initializer of LPTMR peripheral base addresses */
#define LPTMR_BASE_ADDRS                         { LPTMR_BASE }
/** Array initializer of LPTMR peripheral base pointers */
#define LPTMR_BASE_PTRS                          { LPTMR }
/** Interrupt vectors for the LPTMR peripheral type */
#define LPTMR_IRQS                               { LPTMR_IRQn }

/*!
 * @}
 */ /* end of group LPTMR_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Peripheral_Access_Layer MCG Peripheral Access Layer
 * @{
 */

/** MCG - Register Layout Typedef */
typedef struct {
  __IO uint8_t C1;                                 /**< MCG Control 1 Register, offset: 0x0 */
  __IO uint8_t C2;                                 /**< MCG Control 2 Register, offset: 0x1 */
  __IO uint8_t C3;                                 /**< MCG Control 3 Register, offset: 0x2 */
  __IO uint8_t C4;                                 /**< MCG Control 4 Register, offset: 0x3 */
  __IO uint8_t C5;                                 /**< MCG Control 5 Register, offset: 0x4 */
  __IO uint8_t C6;                                 /**< MCG Control 6 Register, offset: 0x5 */
  __IO uint8_t S;                                  /**< MCG Status Register, offset: 0x6 */
       uint8_t RESERVED_0[1];
  __IO uint8_t SC;                                 /**< MCG Status and Control Register, offset: 0x8 */
       uint8_t RESERVED_1[1];
  __IO uint8_t ATCVH;                              /**< MCG Auto Trim Compare Value High Register, offset: 0xA */
  __IO uint8_t ATCVL;                              /**< MCG Auto Trim Compare Value Low Register, offset: 0xB */
  __IO uint8_t C7;                                 /**< MCG Control 7 Register, offset: 0xC */
  __IO uint8_t C8;                                 /**< MCG Control 8 Register, offset: 0xD */
  __I  uint8_t C9;                                 /**< MCG Control 9 Register, offset: 0xE */
} MCG_Type;

/* ----------------------------------------------------------------------------
   -- MCG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCG_Register_Masks MCG Register Masks
 * @{
 */

/*! @name C1 - MCG Control 1 Register */
/*! @{ */

#define MCG_C1_IREFSTEN_MASK                     (0x1U)
#define MCG_C1_IREFSTEN_SHIFT                    (0U)
/*! IREFSTEN - Internal Reference Stop Enable
 *  0b0..Internal reference clock is disabled in Stop mode.
 *  0b1..Internal reference clock is enabled in Stop mode if IRCLKEN is set or if MCG is in FEI, FBI, or BLPI modes before entering Stop mode.
 */
#define MCG_C1_IREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C1_IREFSTEN_SHIFT)) & MCG_C1_IREFSTEN_MASK)

#define MCG_C1_IRCLKEN_MASK                      (0x2U)
#define MCG_C1_IRCLKEN_SHIFT                     (1U)
/*! IRCLKEN - Internal Reference Clock Enable
 *  0b0..MCGIRCLK inactive.
 *  0b1..MCGIRCLK active.
 */
#define MCG_C1_IRCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C1_IRCLKEN_SHIFT)) & MCG_C1_IRCLKEN_MASK)

#define MCG_C1_IREFS_MASK                        (0x4U)
#define MCG_C1_IREFS_SHIFT                       (2U)
/*! IREFS - Internal Reference Select
 *  0b0..External reference clock is selected.
 *  0b1..The slow internal reference clock is selected.
 */
#define MCG_C1_IREFS(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C1_IREFS_SHIFT)) & MCG_C1_IREFS_MASK)

#define MCG_C1_FRDIV_MASK                        (0x38U)
#define MCG_C1_FRDIV_SHIFT                       (3U)
/*! FRDIV - FLL External Reference Divider
 *  0b000..If RANGE = 0 , Divide Factor is 1; for all other RANGE values, Divide Factor is 32.
 *  0b001..If RANGE = 0 , Divide Factor is 2; for all other RANGE values, Divide Factor is 64.
 *  0b010..If RANGE = 0 , Divide Factor is 4; for all other RANGE values, Divide Factor is 128.
 *  0b011..If RANGE = 0 , Divide Factor is 8; for all other RANGE values, Divide Factor is 256.
 *  0b100..If RANGE = 0 , Divide Factor is 16; for all other RANGE values, Divide Factor is 512.
 *  0b101..If RANGE = 0 , Divide Factor is 32; for all other RANGE values, Divide Factor is 1024.
 *  0b110..If RANGE = 0 , Divide Factor is 64; for all other RANGE values, Divide Factor is 1280 .
 *  0b111..If RANGE = 0 , Divide Factor is 128; for all other RANGE values, Divide Factor is 1536 .
 */
#define MCG_C1_FRDIV(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C1_FRDIV_SHIFT)) & MCG_C1_FRDIV_MASK)

#define MCG_C1_CLKS_MASK                         (0xC0U)
#define MCG_C1_CLKS_SHIFT                        (6U)
/*! CLKS - Clock Source Select
 *  0b00..Encoding 0 - Output of FLL or PLL is selected (depends on PLLS control bit).
 *  0b01..Encoding 1 - Internal reference clock is selected.
 *  0b10..Encoding 2 - External reference clock is selected.
 *  0b11..Encoding 3 - Reserved.
 */
#define MCG_C1_CLKS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C1_CLKS_SHIFT)) & MCG_C1_CLKS_MASK)
/*! @} */

/*! @name C2 - MCG Control 2 Register */
/*! @{ */

#define MCG_C2_IRCS_MASK                         (0x1U)
#define MCG_C2_IRCS_SHIFT                        (0U)
/*! IRCS - Internal Reference Clock Select
 *  0b0..Slow internal reference clock selected.
 *  0b1..Fast internal reference clock selected.
 */
#define MCG_C2_IRCS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C2_IRCS_SHIFT)) & MCG_C2_IRCS_MASK)

#define MCG_C2_LP_MASK                           (0x2U)
#define MCG_C2_LP_SHIFT                          (1U)
/*! LP - Low Power Select
 *  0b0..FLL or PLL is not disabled in bypass modes.
 *  0b1..FLL or PLL is disabled in bypass modes (lower power)
 */
#define MCG_C2_LP(x)                             (((uint8_t)(((uint8_t)(x)) << MCG_C2_LP_SHIFT)) & MCG_C2_LP_MASK)

#define MCG_C2_EREFS0_MASK                       (0x4U)
#define MCG_C2_EREFS0_SHIFT                      (2U)
/*! EREFS0 - External Reference Select
 *  0b0..External reference clock requested.
 *  0b1..Oscillator requested.
 */
#define MCG_C2_EREFS0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_EREFS0_SHIFT)) & MCG_C2_EREFS0_MASK)

#define MCG_C2_HGO0_MASK                         (0x8U)
#define MCG_C2_HGO0_SHIFT                        (3U)
/*! HGO0 - High Gain Oscillator Select
 *  0b0..Configure crystal oscillator for low-power operation.
 *  0b1..Configure crystal oscillator for high-gain operation.
 */
#define MCG_C2_HGO0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C2_HGO0_SHIFT)) & MCG_C2_HGO0_MASK)

#define MCG_C2_RANGE0_MASK                       (0x30U)
#define MCG_C2_RANGE0_SHIFT                      (4U)
/*! RANGE0 - Frequency Range Select
 *  0b00..Encoding 0 - Low frequency range selected for the crystal oscillator .
 *  0b01..Encoding 1 - High frequency range selected for the crystal oscillator .
 *  0b1x..Encoding 2 - Very high frequency range selected for the crystal oscillator .
 */
#define MCG_C2_RANGE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_RANGE0_SHIFT)) & MCG_C2_RANGE0_MASK)

#define MCG_C2_LOCRE0_MASK                       (0x80U)
#define MCG_C2_LOCRE0_SHIFT                      (7U)
/*! LOCRE0 - Loss of Clock Reset Enable
 *  0b0..Interrupt request is generated on a loss of OSC external reference clock.
 *  0b1..Generate a reset request on a loss of OSC external reference clock.
 */
#define MCG_C2_LOCRE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C2_LOCRE0_SHIFT)) & MCG_C2_LOCRE0_MASK)
/*! @} */

/*! @name C3 - MCG Control 3 Register */
/*! @{ */

#define MCG_C3_SCTRIM_MASK                       (0xFFU)
#define MCG_C3_SCTRIM_SHIFT                      (0U)
/*! SCTRIM - Slow Internal Reference Clock Trim Setting
 */
#define MCG_C3_SCTRIM(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C3_SCTRIM_SHIFT)) & MCG_C3_SCTRIM_MASK)
/*! @} */

/*! @name C4 - MCG Control 4 Register */
/*! @{ */

#define MCG_C4_SCFTRIM_MASK                      (0x1U)
#define MCG_C4_SCFTRIM_SHIFT                     (0U)
/*! SCFTRIM - Slow Internal Reference Clock Fine Trim
 */
#define MCG_C4_SCFTRIM(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_C4_SCFTRIM_SHIFT)) & MCG_C4_SCFTRIM_MASK)

#define MCG_C4_FCTRIM_MASK                       (0x1EU)
#define MCG_C4_FCTRIM_SHIFT                      (1U)
/*! FCTRIM - Fast Internal Reference Clock Trim Setting
 */
#define MCG_C4_FCTRIM(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C4_FCTRIM_SHIFT)) & MCG_C4_FCTRIM_MASK)

#define MCG_C4_DRST_DRS_MASK                     (0x60U)
#define MCG_C4_DRST_DRS_SHIFT                    (5U)
/*! DRST_DRS - DCO Range Select
 *  0b00..Encoding 0 - Low range (reset default).
 *  0b01..Encoding 1 - Mid range.
 *  0b10..Encoding 2 - Mid-high range.
 *  0b11..Encoding 3 - High range.
 */
#define MCG_C4_DRST_DRS(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C4_DRST_DRS_SHIFT)) & MCG_C4_DRST_DRS_MASK)

#define MCG_C4_DMX32_MASK                        (0x80U)
#define MCG_C4_DMX32_SHIFT                       (7U)
/*! DMX32 - DCO Maximum Frequency with 32.768 kHz Reference
 *  0b0..DCO has a default range of 25%.
 *  0b1..DCO is fine-tuned for maximum frequency with 32.768 kHz reference.
 */
#define MCG_C4_DMX32(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C4_DMX32_SHIFT)) & MCG_C4_DMX32_MASK)
/*! @} */

/*! @name C5 - MCG Control 5 Register */
/*! @{ */

#define MCG_C5_PLLSTEN0_MASK                     (0x20U)
#define MCG_C5_PLLSTEN0_SHIFT                    (5U)
/*! PLLSTEN0 - PLL Stop Enable
 *  0b0..MCGPLLCLK is disabled in any of the Stop modes.
 *  0b1..MCGPLLCLK is enabled if system is in Normal Stop mode.
 */
#define MCG_C5_PLLSTEN0(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_C5_PLLSTEN0_SHIFT)) & MCG_C5_PLLSTEN0_MASK)

#define MCG_C5_PLLCLKEN0_MASK                    (0x40U)
#define MCG_C5_PLLCLKEN0_SHIFT                   (6U)
/*! PLLCLKEN0 - PLL Clock Enable
 *  0b0..MCGPLLCLK is inactive.
 *  0b1..MCGPLLCLK is active.
 */
#define MCG_C5_PLLCLKEN0(x)                      (((uint8_t)(((uint8_t)(x)) << MCG_C5_PLLCLKEN0_SHIFT)) & MCG_C5_PLLCLKEN0_MASK)
/*! @} */

/*! @name C6 - MCG Control 6 Register */
/*! @{ */

#define MCG_C6_CHGPMP_BIAS_MASK                  (0x1FU)
#define MCG_C6_CHGPMP_BIAS_SHIFT                 (0U)
/*! CHGPMP_BIAS - Directly controls the PLL Charge Pump Current. Appropiate selection of this value
 *    is imperative to ensure stable operation of the PLL closed loop system. The default value for
 *    this field is set to 5'b01000 out of reset which generates a nominal 750nA charge pump current
 *    (lcp).
 */
#define MCG_C6_CHGPMP_BIAS(x)                    (((uint8_t)(((uint8_t)(x)) << MCG_C6_CHGPMP_BIAS_SHIFT)) & MCG_C6_CHGPMP_BIAS_MASK)

#define MCG_C6_CME0_MASK                         (0x20U)
#define MCG_C6_CME0_SHIFT                        (5U)
/*! CME0 - Clock Monitor Enable
 *  0b0..External clock monitor is disabled for OSC.
 *  0b1..External clock monitor is enabled for OSC.
 */
#define MCG_C6_CME0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C6_CME0_SHIFT)) & MCG_C6_CME0_MASK)

#define MCG_C6_PLLS_MASK                         (0x40U)
#define MCG_C6_PLLS_SHIFT                        (6U)
/*! PLLS - PLL Select
 *  0b0..FLL is selected.
 *  0b1..PLL is selected (PLL reference clock must be in the range of 31.25-39.0625 KHz prior to setting the PLLS bit).
 */
#define MCG_C6_PLLS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C6_PLLS_SHIFT)) & MCG_C6_PLLS_MASK)

#define MCG_C6_LOLIE0_MASK                       (0x80U)
#define MCG_C6_LOLIE0_SHIFT                      (7U)
/*! LOLIE0 - Loss of Lock Interrrupt Enable
 *  0b0..No interrupt request is generated on loss of lock.
 *  0b1..Generate an interrupt request on loss of lock.
 */
#define MCG_C6_LOLIE0(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C6_LOLIE0_SHIFT)) & MCG_C6_LOLIE0_MASK)
/*! @} */

/*! @name S - MCG Status Register */
/*! @{ */

#define MCG_S_IRCST_MASK                         (0x1U)
#define MCG_S_IRCST_SHIFT                        (0U)
/*! IRCST - Internal Reference Clock Status
 *  0b0..Source of internal reference clock is the slow clock (32 kHz IRC).
 *  0b1..Source of internal reference clock is the fast clock (4 MHz IRC).
 */
#define MCG_S_IRCST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_IRCST_SHIFT)) & MCG_S_IRCST_MASK)

#define MCG_S_OSCINIT0_MASK                      (0x2U)
#define MCG_S_OSCINIT0_SHIFT                     (1U)
/*! OSCINIT0 - OSC Initialization
 */
#define MCG_S_OSCINIT0(x)                        (((uint8_t)(((uint8_t)(x)) << MCG_S_OSCINIT0_SHIFT)) & MCG_S_OSCINIT0_MASK)

#define MCG_S_CLKST_MASK                         (0xCU)
#define MCG_S_CLKST_SHIFT                        (2U)
/*! CLKST - Clock Mode Status
 *  0b00..Encoding 0 - Output of the FLL is selected (reset default).
 *  0b01..Encoding 1 - Internal reference clock is selected.
 *  0b10..Encoding 2 - External reference clock is selected.
 *  0b11..Encoding 3 - Output of the PLL is selected .
 */
#define MCG_S_CLKST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_CLKST_SHIFT)) & MCG_S_CLKST_MASK)

#define MCG_S_IREFST_MASK                        (0x10U)
#define MCG_S_IREFST_SHIFT                       (4U)
/*! IREFST - Internal Reference Status
 *  0b0..Source of FLL reference clock is the external reference clock.
 *  0b1..Source of FLL reference clock is the internal reference clock.
 */
#define MCG_S_IREFST(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_S_IREFST_SHIFT)) & MCG_S_IREFST_MASK)

#define MCG_S_PLLST_MASK                         (0x20U)
#define MCG_S_PLLST_SHIFT                        (5U)
/*! PLLST - PLL Select Status
 *  0b0..Source of PLLS clock is FLL clock.
 *  0b1..Source of PLLS clock is PLL output clock.
 */
#define MCG_S_PLLST(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_PLLST_SHIFT)) & MCG_S_PLLST_MASK)

#define MCG_S_LOCK0_MASK                         (0x40U)
#define MCG_S_LOCK0_SHIFT                        (6U)
/*! LOCK0 - Lock Status
 *  0b0..PLL is currently unlocked.
 *  0b1..PLL is currently locked.
 */
#define MCG_S_LOCK0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_LOCK0_SHIFT)) & MCG_S_LOCK0_MASK)

#define MCG_S_LOLS0_MASK                         (0x80U)
#define MCG_S_LOLS0_SHIFT                        (7U)
/*! LOLS0 - Loss of Lock Status
 *  0b0..PLL has not lost lock since LOLS 0 was last cleared.
 *  0b1..PLL has lost lock since LOLS 0 was last cleared.
 */
#define MCG_S_LOLS0(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_S_LOLS0_SHIFT)) & MCG_S_LOLS0_MASK)
/*! @} */

/*! @name SC - MCG Status and Control Register */
/*! @{ */

#define MCG_SC_LOCS0_MASK                        (0x1U)
#define MCG_SC_LOCS0_SHIFT                       (0U)
/*! LOCS0 - OSC Loss of Clock Status
 *  0b0..Loss of OSC has not occurred.
 *  0b1..Loss of OSC has occurred.
 */
#define MCG_SC_LOCS0(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_SC_LOCS0_SHIFT)) & MCG_SC_LOCS0_MASK)

#define MCG_SC_FCRDIV_MASK                       (0xEU)
#define MCG_SC_FCRDIV_SHIFT                      (1U)
/*! FCRDIV - Fast Clock Internal Reference Divider
 *  0b000..Divide Factor is 1
 *  0b001..Divide Factor is 2.
 *  0b010..Divide Factor is 4.
 *  0b011..Divide Factor is 8.
 *  0b100..Divide Factor is 16
 *  0b101..Divide Factor is 32
 *  0b110..Divide Factor is 64
 *  0b111..Divide Factor is 128.
 */
#define MCG_SC_FCRDIV(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_SC_FCRDIV_SHIFT)) & MCG_SC_FCRDIV_MASK)

#define MCG_SC_FLTPRSRV_MASK                     (0x10U)
#define MCG_SC_FLTPRSRV_SHIFT                    (4U)
/*! FLTPRSRV - FLL Filter Preserve Enable
 *  0b0..FLL filter and FLL frequency will reset on changes to currect clock mode.
 *  0b1..Fll filter and FLL frequency retain their previous values during new clock mode change.
 */
#define MCG_SC_FLTPRSRV(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_SC_FLTPRSRV_SHIFT)) & MCG_SC_FLTPRSRV_MASK)

#define MCG_SC_ATMF_MASK                         (0x20U)
#define MCG_SC_ATMF_SHIFT                        (5U)
/*! ATMF - Automatic Trim Machine Fail Flag
 *  0b0..Automatic Trim Machine completed normally.
 *  0b1..Automatic Trim Machine failed.
 */
#define MCG_SC_ATMF(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATMF_SHIFT)) & MCG_SC_ATMF_MASK)

#define MCG_SC_ATMS_MASK                         (0x40U)
#define MCG_SC_ATMS_SHIFT                        (6U)
/*! ATMS - Automatic Trim Machine Select
 *  0b0..32 kHz Internal Reference Clock selected.
 *  0b1..4 MHz Internal Reference Clock selected.
 */
#define MCG_SC_ATMS(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATMS_SHIFT)) & MCG_SC_ATMS_MASK)

#define MCG_SC_ATME_MASK                         (0x80U)
#define MCG_SC_ATME_SHIFT                        (7U)
/*! ATME - Automatic Trim Machine Enable
 *  0b0..Auto Trim Machine disabled.
 *  0b1..Auto Trim Machine enabled.
 */
#define MCG_SC_ATME(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_SC_ATME_SHIFT)) & MCG_SC_ATME_MASK)
/*! @} */

/*! @name ATCVH - MCG Auto Trim Compare Value High Register */
/*! @{ */

#define MCG_ATCVH_ATCVH_MASK                     (0xFFU)
#define MCG_ATCVH_ATCVH_SHIFT                    (0U)
/*! ATCVH - ATM Compare Value High
 */
#define MCG_ATCVH_ATCVH(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_ATCVH_ATCVH_SHIFT)) & MCG_ATCVH_ATCVH_MASK)
/*! @} */

/*! @name ATCVL - MCG Auto Trim Compare Value Low Register */
/*! @{ */

#define MCG_ATCVL_ATCVL_MASK                     (0xFFU)
#define MCG_ATCVL_ATCVL_SHIFT                    (0U)
/*! ATCVL - ATM Compare Value Low
 */
#define MCG_ATCVL_ATCVL(x)                       (((uint8_t)(((uint8_t)(x)) << MCG_ATCVL_ATCVL_SHIFT)) & MCG_ATCVL_ATCVL_MASK)
/*! @} */

/*! @name C7 - MCG Control 7 Register */
/*! @{ */

#define MCG_C7_OSCSEL_MASK                       (0x1U)
#define MCG_C7_OSCSEL_SHIFT                      (0U)
/*! OSCSEL - MCG OSC Clock Select
 *  0b0..Selects Oscillator (OSCCLK).
 *  0b1..Selects 32 kHz RTC Oscillator.
 */
#define MCG_C7_OSCSEL(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C7_OSCSEL_SHIFT)) & MCG_C7_OSCSEL_MASK)

#define MCG_C7_PLL32KREFSEL_MASK                 (0xC0U)
#define MCG_C7_PLL32KREFSEL_SHIFT                (6U)
/*! PLL32KREFSEL - MCG PLL 32Khz Reference Clock Select
 *  0b00..Selects 32 kHz RTC Oscillator.
 *  0b01..Selects 32 kHz IRC.
 *  0b10..Selects FLL FRDIV clock.
 *  0b11..Reserved.
 */
#define MCG_C7_PLL32KREFSEL(x)                   (((uint8_t)(((uint8_t)(x)) << MCG_C7_PLL32KREFSEL_SHIFT)) & MCG_C7_PLL32KREFSEL_MASK)
/*! @} */

/*! @name C8 - MCG Control 8 Register */
/*! @{ */

#define MCG_C8_LOCS1_MASK                        (0x1U)
#define MCG_C8_LOCS1_SHIFT                       (0U)
/*! LOCS1 - RTC Loss of Clock Status
 *  0b0..Loss of RTC has not occur.
 *  0b1..Loss of RTC has occur
 */
#define MCG_C8_LOCS1(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C8_LOCS1_SHIFT)) & MCG_C8_LOCS1_MASK)

#define MCG_C8_COARSE_LOLIE_MASK                 (0x10U)
#define MCG_C8_COARSE_LOLIE_SHIFT                (4U)
/*! COARSE_LOLIE - Loss of Coarse Lock Interrrupt Enable
 *  0b0..No interrupt request is generated on coarse loss of lock.
 *  0b1..Generate an interrupt request on coarse loss of lock.
 */
#define MCG_C8_COARSE_LOLIE(x)                   (((uint8_t)(((uint8_t)(x)) << MCG_C8_COARSE_LOLIE_SHIFT)) & MCG_C8_COARSE_LOLIE_MASK)

#define MCG_C8_CME1_MASK                         (0x20U)
#define MCG_C8_CME1_SHIFT                        (5U)
/*! CME1 - Clock Monitor Enable1
 *  0b0..External clock monitor is disabled for RTC clock.
 *  0b1..External clock monitor is enabled for RTC clock.
 */
#define MCG_C8_CME1(x)                           (((uint8_t)(((uint8_t)(x)) << MCG_C8_CME1_SHIFT)) & MCG_C8_CME1_MASK)

#define MCG_C8_LOLRE_MASK                        (0x40U)
#define MCG_C8_LOLRE_SHIFT                       (6U)
/*! LOLRE - PLL Loss of Lock Reset Enable
 *  0b0..Interrupt request is generated on a PLL loss of lock indication. The PLL loss of lock interrupt enable
 *       bit must also be set to generate the interrupt request.
 *  0b1..Generate a reset request on a PLL loss of lock indication.
 */
#define MCG_C8_LOLRE(x)                          (((uint8_t)(((uint8_t)(x)) << MCG_C8_LOLRE_SHIFT)) & MCG_C8_LOLRE_MASK)

#define MCG_C8_LOCRE1_MASK                       (0x80U)
#define MCG_C8_LOCRE1_SHIFT                      (7U)
/*! LOCRE1 - Loss of Clock Reset Enable
 *  0b0..Interrupt request is generated on a loss of RTC external reference clock.
 *  0b1..Generate a reset request on a loss of RTC external reference clock
 */
#define MCG_C8_LOCRE1(x)                         (((uint8_t)(((uint8_t)(x)) << MCG_C8_LOCRE1_SHIFT)) & MCG_C8_LOCRE1_MASK)
/*! @} */

/*! @name C9 - MCG Control 9 Register */
/*! @{ */

#define MCG_C9_COARSE_LOCK_MASK                  (0x40U)
#define MCG_C9_COARSE_LOCK_SHIFT                 (6U)
/*! COARSE_LOCK - Coarse Lock Status
 *  0b0..PLL is currently unlocked.
 *  0b1..PLL is currently locked after first sample.
 */
#define MCG_C9_COARSE_LOCK(x)                    (((uint8_t)(((uint8_t)(x)) << MCG_C9_COARSE_LOCK_SHIFT)) & MCG_C9_COARSE_LOCK_MASK)

#define MCG_C9_COARSE_LOLS_MASK                  (0x80U)
#define MCG_C9_COARSE_LOLS_SHIFT                 (7U)
/*! COARSE_LOLS - Coarse Loss of Lock Status
 *  0b0..PLL has not lost lock since COARSE_LOLS was last cleared.
 *  0b1..PLL has lost lock since COARSE_LOLS was last cleared.
 */
#define MCG_C9_COARSE_LOLS(x)                    (((uint8_t)(((uint8_t)(x)) << MCG_C9_COARSE_LOLS_SHIFT)) & MCG_C9_COARSE_LOLS_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MCG_Register_Masks */


/* MCG - Peripheral instance base addresses */
/** Peripheral MCG base address */
#define MCG_BASE                                 (0x40064000u)
/** Peripheral MCG base pointer */
#define MCG                                      ((MCG_Type *)MCG_BASE)
/** Array initializer of MCG peripheral base addresses */
#define MCG_BASE_ADDRS                           { MCG_BASE }
/** Array initializer of MCG peripheral base pointers */
#define MCG_BASE_PTRS                            { MCG }
/** Interrupt vectors for the MCG peripheral type */
#define MCG_IRQS                                 { MCG_IRQn }
/* MCG C2[EREFS] backward compatibility */
#define MCG_C2_EREFS_MASK         (MCG_C2_EREFS0_MASK)
#define MCG_C2_EREFS_SHIFT        (MCG_C2_EREFS0_SHIFT)
#define MCG_C2_EREFS_WIDTH        (MCG_C2_EREFS0_WIDTH)
#define MCG_C2_EREFS(x)           (MCG_C2_EREFS0(x))

/* MCG C2[HGO] backward compatibility */
#define MCG_C2_HGO_MASK         (MCG_C2_HGO0_MASK)
#define MCG_C2_HGO_SHIFT        (MCG_C2_HGO0_SHIFT)
#define MCG_C2_HGO_WIDTH        (MCG_C2_HGO0_WIDTH)
#define MCG_C2_HGO(x)           (MCG_C2_HGO0(x))

/* MCG C2[RANGE] backward compatibility */
#define MCG_C2_RANGE_MASK         (MCG_C2_RANGE0_MASK)
#define MCG_C2_RANGE_SHIFT        (MCG_C2_RANGE0_SHIFT)
#define MCG_C2_RANGE_WIDTH        (MCG_C2_RANGE0_WIDTH)
#define MCG_C2_RANGE(x)           (MCG_C2_RANGE0(x))


/*!
 * @}
 */ /* end of group MCG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */

/** MCM - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[8];
  __I  uint16_t PLASC;                             /**< Crossbar Switch (AXBS) Slave Configuration, offset: 0x8 */
  __I  uint16_t PLAMC;                             /**< Crossbar Switch (AXBS) Master Configuration, offset: 0xA */
  __IO uint32_t PLACR;                             /**< Platform Control Register, offset: 0xC */
       uint8_t RESERVED_1[32];
  __IO uint32_t PID;                               /**< Process ID register, offset: 0x30 */
       uint8_t RESERVED_2[12];
  __IO uint32_t CPO;                               /**< Compute Operation Control Register, offset: 0x40 */
       uint8_t RESERVED_3[60];
  __IO uint32_t MATCR[1];                          /**< Master Attribute Configuration Register, array offset: 0x80, array step: 0x4 */
} MCM_Type;

/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */

/*! @name PLASC - Crossbar Switch (AXBS) Slave Configuration */
/*! @{ */

#define MCM_PLASC_ASC_MASK                       (0xFFU)
#define MCM_PLASC_ASC_SHIFT                      (0U)
/*! ASC - Each bit in the ASC field indicates whether there is a corresponding connection to the
 *    crossbar switch's slave input port.
 *  0b00000000..A bus slave connection to AXBS input port n is absent.
 *  0b00000001..A bus slave connection to AXBS input port n is present.
 */
#define MCM_PLASC_ASC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLASC_ASC_SHIFT)) & MCM_PLASC_ASC_MASK)
/*! @} */

/*! @name PLAMC - Crossbar Switch (AXBS) Master Configuration */
/*! @{ */

#define MCM_PLAMC_AMC_MASK                       (0xFFU)
#define MCM_PLAMC_AMC_SHIFT                      (0U)
/*! AMC - Each bit in the AMC field indicates whether there is a corresponding connection to the AXBS master input port.
 *  0b00000000..A bus master connection to AXBS input port n is absent
 *  0b00000001..A bus master connection to AXBS input port n is present
 */
#define MCM_PLAMC_AMC(x)                         (((uint16_t)(((uint16_t)(x)) << MCM_PLAMC_AMC_SHIFT)) & MCM_PLAMC_AMC_MASK)
/*! @} */

/*! @name PLACR - Platform Control Register */
/*! @{ */

#define MCM_PLACR_ARB_MASK                       (0x200U)
#define MCM_PLACR_ARB_SHIFT                      (9U)
/*! ARB - Arbitration select
 *  0b0..Fixed-priority arbitration for the crossbar masters
 *  0b1..Round-robin arbitration for the crossbar masters
 */
#define MCM_PLACR_ARB(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ARB_SHIFT)) & MCM_PLACR_ARB_MASK)

#define MCM_PLACR_CFCC_MASK                      (0x400U)
#define MCM_PLACR_CFCC_SHIFT                     (10U)
/*! CFCC - Clear Flash Controller Cache
 */
#define MCM_PLACR_CFCC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_CFCC_SHIFT)) & MCM_PLACR_CFCC_MASK)

#define MCM_PLACR_DFCDA_MASK                     (0x800U)
#define MCM_PLACR_DFCDA_SHIFT                    (11U)
/*! DFCDA - Disable Flash Controller Data Caching
 *  0b0..Enable flash controller data caching
 *  0b1..Disable flash controller data caching.
 */
#define MCM_PLACR_DFCDA(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCDA_SHIFT)) & MCM_PLACR_DFCDA_MASK)

#define MCM_PLACR_DFCIC_MASK                     (0x1000U)
#define MCM_PLACR_DFCIC_SHIFT                    (12U)
/*! DFCIC - Disable Flash Controller Instruction Caching
 *  0b0..Enable flash controller instruction caching.
 *  0b1..Disable flash controller instruction caching.
 */
#define MCM_PLACR_DFCIC(x)                       (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCIC_SHIFT)) & MCM_PLACR_DFCIC_MASK)

#define MCM_PLACR_DFCC_MASK                      (0x2000U)
#define MCM_PLACR_DFCC_SHIFT                     (13U)
/*! DFCC - Disable Flash Controller Cache
 *  0b0..Enable flash controller cache.
 *  0b1..Disable flash controller cache.
 */
#define MCM_PLACR_DFCC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCC_SHIFT)) & MCM_PLACR_DFCC_MASK)

#define MCM_PLACR_EFDS_MASK                      (0x4000U)
#define MCM_PLACR_EFDS_SHIFT                     (14U)
/*! EFDS - Enable Flash Data Speculation
 *  0b0..Disable flash data speculation.
 *  0b1..Enable flash data speculation.
 */
#define MCM_PLACR_EFDS(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_EFDS_SHIFT)) & MCM_PLACR_EFDS_MASK)

#define MCM_PLACR_DFCS_MASK                      (0x8000U)
#define MCM_PLACR_DFCS_SHIFT                     (15U)
/*! DFCS - Disable Flash Controller Speculation
 *  0b0..Enable flash controller speculation.
 *  0b1..Disable flash controller speculation.
 */
#define MCM_PLACR_DFCS(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_DFCS_SHIFT)) & MCM_PLACR_DFCS_MASK)

#define MCM_PLACR_ESFC_MASK                      (0x10000U)
#define MCM_PLACR_ESFC_SHIFT                     (16U)
/*! ESFC - Enable Stalling Flash Controller
 *  0b0..Disable stalling flash controller when flash is busy.
 *  0b1..Enable stalling flash controller when flash is busy.
 */
#define MCM_PLACR_ESFC(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_PLACR_ESFC_SHIFT)) & MCM_PLACR_ESFC_MASK)
/*! @} */

/*! @name PID - Process ID register */
/*! @{ */

#define MCM_PID_PID_MASK                         (0xFFU)
#define MCM_PID_PID_SHIFT                        (0U)
/*! PID - M0_PID For MPU
 *  0b00000000..Reserved for privileged secure tasks
 */
#define MCM_PID_PID(x)                           (((uint32_t)(((uint32_t)(x)) << MCM_PID_PID_SHIFT)) & MCM_PID_PID_MASK)
/*! @} */

/*! @name CPO - Compute Operation Control Register */
/*! @{ */

#define MCM_CPO_CPOREQ_MASK                      (0x1U)
#define MCM_CPO_CPOREQ_SHIFT                     (0U)
/*! CPOREQ - Compute Operation Request
 *  0b0..Request is cleared.
 *  0b1..Request Compute Operation.
 */
#define MCM_CPO_CPOREQ(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOREQ_SHIFT)) & MCM_CPO_CPOREQ_MASK)

#define MCM_CPO_CPOACK_MASK                      (0x2U)
#define MCM_CPO_CPOACK_SHIFT                     (1U)
/*! CPOACK - Compute Operation Acknowledge
 *  0b0..Compute operation entry has not completed or compute operation exit has completed.
 *  0b1..Compute operation entry has completed or compute operation exit has not completed.
 */
#define MCM_CPO_CPOACK(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOACK_SHIFT)) & MCM_CPO_CPOACK_MASK)

#define MCM_CPO_CPOWOI_MASK                      (0x4U)
#define MCM_CPO_CPOWOI_SHIFT                     (2U)
/*! CPOWOI - Compute Operation Wake-up on Interrupt
 *  0b0..No effect.
 *  0b1..When set, the CPOREQ is cleared on any interrupt or exception vector fetch.
 */
#define MCM_CPO_CPOWOI(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_CPO_CPOWOI_SHIFT)) & MCM_CPO_CPOWOI_MASK)
/*! @} */

/*! @name MATCR - Master Attribute Configuration Register */
/*! @{ */

#define MCM_MATCR_ATC0_MASK                      (0x7U)
#define MCM_MATCR_ATC0_SHIFT                     (0U)
/*! ATC0 - Attribute Configuration Master n
 *  0b00x..Master attributes are statically forced to {privileged, secure}.
 *  0b010..Master attributes are statically forced to {user, secure}.
 *  0b011..Master attributes are statically forced to {user, nonsecure}.
 *  0b100..Enable master attribute {privileged or user} and statically force {secure}.
 *  0b101..Enable master attribute {privileged or user} and statically force {nonsecure}.
 *  0b11x..Enable master attribute {privileged or user, secure or nonsecure}
 */
#define MCM_MATCR_ATC0(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_MATCR_ATC0_SHIFT)) & MCM_MATCR_ATC0_MASK)

#define MCM_MATCR_RO0_MASK                       (0x80U)
#define MCM_MATCR_RO0_SHIFT                      (7U)
/*! RO0 - Read-Only Master n
 *  0b0..Writes to the ATCn are allowed.
 *  0b1..Writes to the ATCn are ignored.
 */
#define MCM_MATCR_RO0(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_MATCR_RO0_SHIFT)) & MCM_MATCR_RO0_MASK)

#define MCM_MATCR_ATC2_MASK                      (0x70000U)
#define MCM_MATCR_ATC2_SHIFT                     (16U)
/*! ATC2 - Attribute Configuration Master n
 *  0b00x..Master attributes are statically forced to {privileged, secure}.
 *  0b010..Master attributes are statically forced to {user, secure}.
 *  0b011..Master attributes are statically forced to {user, nonsecure}.
 *  0b100..Enable master attribute {privileged or user} and statically force {secure}.
 *  0b101..Enable master attribute {privileged or user} and statically force {nonsecure}.
 *  0b11x..Enable master attribute {privileged or user, secure or nonsecure}
 */
#define MCM_MATCR_ATC2(x)                        (((uint32_t)(((uint32_t)(x)) << MCM_MATCR_ATC2_SHIFT)) & MCM_MATCR_ATC2_MASK)

#define MCM_MATCR_RO2_MASK                       (0x800000U)
#define MCM_MATCR_RO2_SHIFT                      (23U)
/*! RO2 - Read-Only Master n
 *  0b0..Writes to the ATCn are allowed.
 *  0b1..Writes to the ATCn are ignored.
 */
#define MCM_MATCR_RO2(x)                         (((uint32_t)(((uint32_t)(x)) << MCM_MATCR_RO2_SHIFT)) & MCM_MATCR_RO2_MASK)
/*! @} */

/* The count of MCM_MATCR */
#define MCM_MATCR_COUNT                          (1U)


/*!
 * @}
 */ /* end of group MCM_Register_Masks */


/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base address */
#define MCM_BASE                                 (0xF0003000u)
/** Peripheral MCM base pointer */
#define MCM                                      ((MCM_Type *)MCM_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           { MCM_BASE }
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            { MCM }

/*!
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MTB Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Peripheral_Access_Layer MTB Peripheral Access Layer
 * @{
 */

/** MTB - Register Layout Typedef */
typedef struct {
  __IO uint32_t POSITION;                          /**< MTB Position Register, offset: 0x0 */
  __IO uint32_t MASTER;                            /**< MTB Master Register, offset: 0x4 */
  __IO uint32_t FLOW;                              /**< MTB Flow Register, offset: 0x8 */
  __I  uint32_t BASE;                              /**< MTB Base Register, offset: 0xC */
       uint8_t RESERVED_0[3824];
  __I  uint32_t MODECTRL;                          /**< Integration Mode Control Register, offset: 0xF00 */
       uint8_t RESERVED_1[156];
  __I  uint32_t TAGSET;                            /**< Claim TAG Set Register, offset: 0xFA0 */
  __I  uint32_t TAGCLEAR;                          /**< Claim TAG Clear Register, offset: 0xFA4 */
       uint8_t RESERVED_2[8];
  __I  uint32_t LOCKACCESS;                        /**< Lock Access Register, offset: 0xFB0 */
  __I  uint32_t LOCKSTAT;                          /**< Lock Status Register, offset: 0xFB4 */
  __I  uint32_t AUTHSTAT;                          /**< Authentication Status Register, offset: 0xFB8 */
  __I  uint32_t DEVICEARCH;                        /**< Device Architecture Register, offset: 0xFBC */
       uint8_t RESERVED_3[8];
  __I  uint32_t DEVICECFG;                         /**< Device Configuration Register, offset: 0xFC8 */
  __I  uint32_t DEVICETYPID;                       /**< Device Type Identifier Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTB_Type;

/* ----------------------------------------------------------------------------
   -- MTB Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTB_Register_Masks MTB Register Masks
 * @{
 */

/*! @name POSITION - MTB Position Register */
/*! @{ */

#define MTB_POSITION_WRAP_MASK                   (0x4U)
#define MTB_POSITION_WRAP_SHIFT                  (2U)
/*! WRAP - WRAP
 */
#define MTB_POSITION_WRAP(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_WRAP_SHIFT)) & MTB_POSITION_WRAP_MASK)

#define MTB_POSITION_POINTER_MASK                (0xFFFFFFF8U)
#define MTB_POSITION_POINTER_SHIFT               (3U)
/*! POINTER - Trace Packet Address Pointer[28:0]
 */
#define MTB_POSITION_POINTER(x)                  (((uint32_t)(((uint32_t)(x)) << MTB_POSITION_POINTER_SHIFT)) & MTB_POSITION_POINTER_MASK)
/*! @} */

/*! @name MASTER - MTB Master Register */
/*! @{ */

#define MTB_MASTER_MASK_MASK                     (0x1FU)
#define MTB_MASTER_MASK_SHIFT                    (0U)
/*! MASK - Mask
 */
#define MTB_MASTER_MASK(x)                       (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_MASK_SHIFT)) & MTB_MASTER_MASK_MASK)

#define MTB_MASTER_TSTARTEN_MASK                 (0x20U)
#define MTB_MASTER_TSTARTEN_SHIFT                (5U)
/*! TSTARTEN - Trace Start Input Enable
 */
#define MTB_MASTER_TSTARTEN(x)                   (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTARTEN_SHIFT)) & MTB_MASTER_TSTARTEN_MASK)

#define MTB_MASTER_TSTOPEN_MASK                  (0x40U)
#define MTB_MASTER_TSTOPEN_SHIFT                 (6U)
/*! TSTOPEN - Trace Stop Input Enable
 */
#define MTB_MASTER_TSTOPEN(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_TSTOPEN_SHIFT)) & MTB_MASTER_TSTOPEN_MASK)

#define MTB_MASTER_SFRWPRIV_MASK                 (0x80U)
#define MTB_MASTER_SFRWPRIV_SHIFT                (7U)
/*! SFRWPRIV - Special Function Register Write Privilege
 */
#define MTB_MASTER_SFRWPRIV(x)                   (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_SFRWPRIV_SHIFT)) & MTB_MASTER_SFRWPRIV_MASK)

#define MTB_MASTER_RAMPRIV_MASK                  (0x100U)
#define MTB_MASTER_RAMPRIV_SHIFT                 (8U)
/*! RAMPRIV - RAM Privilege
 */
#define MTB_MASTER_RAMPRIV(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_RAMPRIV_SHIFT)) & MTB_MASTER_RAMPRIV_MASK)

#define MTB_MASTER_HALTREQ_MASK                  (0x200U)
#define MTB_MASTER_HALTREQ_SHIFT                 (9U)
/*! HALTREQ - Halt Request
 */
#define MTB_MASTER_HALTREQ(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_HALTREQ_SHIFT)) & MTB_MASTER_HALTREQ_MASK)

#define MTB_MASTER_EN_MASK                       (0x80000000U)
#define MTB_MASTER_EN_SHIFT                      (31U)
/*! EN - Main Trace Enable
 */
#define MTB_MASTER_EN(x)                         (((uint32_t)(((uint32_t)(x)) << MTB_MASTER_EN_SHIFT)) & MTB_MASTER_EN_MASK)
/*! @} */

/*! @name FLOW - MTB Flow Register */
/*! @{ */

#define MTB_FLOW_AUTOSTOP_MASK                   (0x1U)
#define MTB_FLOW_AUTOSTOP_SHIFT                  (0U)
/*! AUTOSTOP - AUTOSTOP
 */
#define MTB_FLOW_AUTOSTOP(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOSTOP_SHIFT)) & MTB_FLOW_AUTOSTOP_MASK)

#define MTB_FLOW_AUTOHALT_MASK                   (0x2U)
#define MTB_FLOW_AUTOHALT_SHIFT                  (1U)
/*! AUTOHALT - AUTOHALT
 */
#define MTB_FLOW_AUTOHALT(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_AUTOHALT_SHIFT)) & MTB_FLOW_AUTOHALT_MASK)

#define MTB_FLOW_WATERMARK_MASK                  (0xFFFFFFF8U)
#define MTB_FLOW_WATERMARK_SHIFT                 (3U)
/*! WATERMARK - WATERMARK[28:0]
 */
#define MTB_FLOW_WATERMARK(x)                    (((uint32_t)(((uint32_t)(x)) << MTB_FLOW_WATERMARK_SHIFT)) & MTB_FLOW_WATERMARK_MASK)
/*! @} */

/*! @name BASE - MTB Base Register */
/*! @{ */

#define MTB_BASE_BASEADDR_MASK                   (0xFFFFFFFFU)
#define MTB_BASE_BASEADDR_SHIFT                  (0U)
/*! BASEADDR - BASEADDR
 */
#define MTB_BASE_BASEADDR(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_BASE_BASEADDR_SHIFT)) & MTB_BASE_BASEADDR_MASK)
/*! @} */

/*! @name MODECTRL - Integration Mode Control Register */
/*! @{ */

#define MTB_MODECTRL_MODECTRL_MASK               (0xFFFFFFFFU)
#define MTB_MODECTRL_MODECTRL_SHIFT              (0U)
/*! MODECTRL - MODECTRL
 */
#define MTB_MODECTRL_MODECTRL(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_MODECTRL_MODECTRL_SHIFT)) & MTB_MODECTRL_MODECTRL_MASK)
/*! @} */

/*! @name TAGSET - Claim TAG Set Register */
/*! @{ */

#define MTB_TAGSET_TAGSET_MASK                   (0xFFFFFFFFU)
#define MTB_TAGSET_TAGSET_SHIFT                  (0U)
/*! TAGSET - TAGSET
 */
#define MTB_TAGSET_TAGSET(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_TAGSET_TAGSET_SHIFT)) & MTB_TAGSET_TAGSET_MASK)
/*! @} */

/*! @name TAGCLEAR - Claim TAG Clear Register */
/*! @{ */

#define MTB_TAGCLEAR_TAGCLEAR_MASK               (0xFFFFFFFFU)
#define MTB_TAGCLEAR_TAGCLEAR_SHIFT              (0U)
/*! TAGCLEAR - TAGCLEAR
 */
#define MTB_TAGCLEAR_TAGCLEAR(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_TAGCLEAR_TAGCLEAR_SHIFT)) & MTB_TAGCLEAR_TAGCLEAR_MASK)
/*! @} */

/*! @name LOCKACCESS - Lock Access Register */
/*! @{ */

#define MTB_LOCKACCESS_LOCKACCESS_MASK           (0xFFFFFFFFU)
#define MTB_LOCKACCESS_LOCKACCESS_SHIFT          (0U)
#define MTB_LOCKACCESS_LOCKACCESS(x)             (((uint32_t)(((uint32_t)(x)) << MTB_LOCKACCESS_LOCKACCESS_SHIFT)) & MTB_LOCKACCESS_LOCKACCESS_MASK)
/*! @} */

/*! @name LOCKSTAT - Lock Status Register */
/*! @{ */

#define MTB_LOCKSTAT_LOCKSTAT_MASK               (0xFFFFFFFFU)
#define MTB_LOCKSTAT_LOCKSTAT_SHIFT              (0U)
/*! LOCKSTAT - LOCKSTAT
 */
#define MTB_LOCKSTAT_LOCKSTAT(x)                 (((uint32_t)(((uint32_t)(x)) << MTB_LOCKSTAT_LOCKSTAT_SHIFT)) & MTB_LOCKSTAT_LOCKSTAT_MASK)
/*! @} */

/*! @name AUTHSTAT - Authentication Status Register */
/*! @{ */

#define MTB_AUTHSTAT_BIT0_MASK                   (0x1U)
#define MTB_AUTHSTAT_BIT0_SHIFT                  (0U)
#define MTB_AUTHSTAT_BIT0(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT0_SHIFT)) & MTB_AUTHSTAT_BIT0_MASK)

#define MTB_AUTHSTAT_BIT2_MASK                   (0x4U)
#define MTB_AUTHSTAT_BIT2_SHIFT                  (2U)
/*! BIT2 - BIT2
 */
#define MTB_AUTHSTAT_BIT2(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_AUTHSTAT_BIT2_SHIFT)) & MTB_AUTHSTAT_BIT2_MASK)
/*! @} */

/*! @name DEVICEARCH - Device Architecture Register */
/*! @{ */

#define MTB_DEVICEARCH_DEVICEARCH_MASK           (0xFFFFFFFFU)
#define MTB_DEVICEARCH_DEVICEARCH_SHIFT          (0U)
/*! DEVICEARCH - DEVICEARCH
 */
#define MTB_DEVICEARCH_DEVICEARCH(x)             (((uint32_t)(((uint32_t)(x)) << MTB_DEVICEARCH_DEVICEARCH_SHIFT)) & MTB_DEVICEARCH_DEVICEARCH_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */

#define MTB_DEVICECFG_DEVICECFG_MASK             (0xFFFFFFFFU)
#define MTB_DEVICECFG_DEVICECFG_SHIFT            (0U)
/*! DEVICECFG - DEVICECFG
 */
#define MTB_DEVICECFG_DEVICECFG(x)               (((uint32_t)(((uint32_t)(x)) << MTB_DEVICECFG_DEVICECFG_SHIFT)) & MTB_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */

#define MTB_DEVICETYPID_DEVICETYPID_MASK         (0xFFFFFFFFU)
#define MTB_DEVICETYPID_DEVICETYPID_SHIFT        (0U)
/*! DEVICETYPID - DEVICETYPID
 */
#define MTB_DEVICETYPID_DEVICETYPID(x)           (((uint32_t)(((uint32_t)(x)) << MTB_DEVICETYPID_DEVICETYPID_SHIFT)) & MTB_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID4_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID4_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID4_PERIPHID_SHIFT)) & MTB_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID5_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID5_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID5_PERIPHID_SHIFT)) & MTB_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID6_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID6_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID6_PERIPHID_SHIFT)) & MTB_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID7_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID7_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID7_PERIPHID_SHIFT)) & MTB_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID0_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID0_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID0_PERIPHID_SHIFT)) & MTB_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID1_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID1_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID1_PERIPHID_SHIFT)) & MTB_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID2_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID2_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID2_PERIPHID_SHIFT)) & MTB_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define MTB_PERIPHID3_PERIPHID_MASK              (0xFFFFFFFFU)
#define MTB_PERIPHID3_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define MTB_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << MTB_PERIPHID3_PERIPHID_SHIFT)) & MTB_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define MTB_COMPID_COMPID_MASK                   (0xFFFFFFFFU)
#define MTB_COMPID_COMPID_SHIFT                  (0U)
/*! COMPID - Component ID
 */
#define MTB_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x)) << MTB_COMPID_COMPID_SHIFT)) & MTB_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTB_COMPID */
#define MTB_COMPID_COUNT                         (4U)


/*!
 * @}
 */ /* end of group MTB_Register_Masks */


/* MTB - Peripheral instance base addresses */
/** Peripheral MTB base address */
#define MTB_BASE                                 (0xF0000000u)
/** Peripheral MTB base pointer */
#define MTB                                      ((MTB_Type *)MTB_BASE)
/** Array initializer of MTB peripheral base addresses */
#define MTB_BASE_ADDRS                           { MTB_BASE }
/** Array initializer of MTB peripheral base pointers */
#define MTB_BASE_PTRS                            { MTB }

/*!
 * @}
 */ /* end of group MTB_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- MTBDWT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Peripheral_Access_Layer MTBDWT Peripheral Access Layer
 * @{
 */

/** MTBDWT - Register Layout Typedef */
typedef struct {
  __I  uint32_t CTRL;                              /**< MTB DWT Control Register, offset: 0x0 */
       uint8_t RESERVED_0[28];
  struct {                                         /* offset: 0x20, array step: 0x10 */
    __IO uint32_t COMP;                              /**< MTB_DWT Comparator Register, array offset: 0x20, array step: 0x10 */
    __IO uint32_t MASK;                              /**< MTB_DWT Comparator Mask Register, array offset: 0x24, array step: 0x10 */
    __IO uint32_t FCT;                               /**< MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1, array offset: 0x28, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } COMPARATOR[2];
       uint8_t RESERVED_1[448];
  __IO uint32_t TBCTRL;                            /**< MTB_DWT Trace Buffer Control Register, offset: 0x200 */
       uint8_t RESERVED_2[3524];
  __I  uint32_t DEVICECFG;                         /**< Device Configuration Register, offset: 0xFC8 */
  __I  uint32_t DEVICETYPID;                       /**< Device Type Identifier Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} MTBDWT_Type;

/* ----------------------------------------------------------------------------
   -- MTBDWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MTBDWT_Register_Masks MTBDWT Register Masks
 * @{
 */

/*! @name CTRL - MTB DWT Control Register */
/*! @{ */

#define MTBDWT_CTRL_DWTCFGCTRL_MASK              (0xFFFFFFFU)
#define MTBDWT_CTRL_DWTCFGCTRL_SHIFT             (0U)
/*! DWTCFGCTRL - DWT configuration controls
 */
#define MTBDWT_CTRL_DWTCFGCTRL(x)                (((uint32_t)(((uint32_t)(x)) << MTBDWT_CTRL_DWTCFGCTRL_SHIFT)) & MTBDWT_CTRL_DWTCFGCTRL_MASK)

#define MTBDWT_CTRL_NUMCMP_MASK                  (0xF0000000U)
#define MTBDWT_CTRL_NUMCMP_SHIFT                 (28U)
/*! NUMCMP - Number of comparators
 */
#define MTBDWT_CTRL_NUMCMP(x)                    (((uint32_t)(((uint32_t)(x)) << MTBDWT_CTRL_NUMCMP_SHIFT)) & MTBDWT_CTRL_NUMCMP_MASK)
/*! @} */

/*! @name COMP - MTB_DWT Comparator Register */
/*! @{ */

#define MTBDWT_COMP_COMP_MASK                    (0xFFFFFFFFU)
#define MTBDWT_COMP_COMP_SHIFT                   (0U)
/*! COMP - Reference value for comparison
 */
#define MTBDWT_COMP_COMP(x)                      (((uint32_t)(((uint32_t)(x)) << MTBDWT_COMP_COMP_SHIFT)) & MTBDWT_COMP_COMP_MASK)
/*! @} */

/* The count of MTBDWT_COMP */
#define MTBDWT_COMP_COUNT                        (2U)

/*! @name MASK - MTB_DWT Comparator Mask Register */
/*! @{ */

#define MTBDWT_MASK_MASK_MASK                    (0x1FU)
#define MTBDWT_MASK_MASK_SHIFT                   (0U)
/*! MASK - MASK
 */
#define MTBDWT_MASK_MASK(x)                      (((uint32_t)(((uint32_t)(x)) << MTBDWT_MASK_MASK_SHIFT)) & MTBDWT_MASK_MASK_MASK)
/*! @} */

/* The count of MTBDWT_MASK */
#define MTBDWT_MASK_COUNT                        (2U)

/*! @name FCT - MTB_DWT Comparator Function Register 0..MTB_DWT Comparator Function Register 1 */
/*! @{ */

#define MTBDWT_FCT_FUNCTION_MASK                 (0xFU)
#define MTBDWT_FCT_FUNCTION_SHIFT                (0U)
/*! FUNCTION - Function
 *  0b0000..Disabled.
 *  0b0100..Instruction fetch.
 *  0b0101..Data operand read.
 *  0b0110..Data operand write.
 *  0b0111..Data operand (read + write).
 */
#define MTBDWT_FCT_FUNCTION(x)                   (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_FUNCTION_SHIFT)) & MTBDWT_FCT_FUNCTION_MASK)

#define MTBDWT_FCT_DATAVMATCH_MASK               (0x100U)
#define MTBDWT_FCT_DATAVMATCH_SHIFT              (8U)
/*! DATAVMATCH - Data Value Match
 *  0b0..Perform address comparison.
 *  0b1..Perform data value comparison.
 */
#define MTBDWT_FCT_DATAVMATCH(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVMATCH_SHIFT)) & MTBDWT_FCT_DATAVMATCH_MASK)

#define MTBDWT_FCT_DATAVSIZE_MASK                (0xC00U)
#define MTBDWT_FCT_DATAVSIZE_SHIFT               (10U)
/*! DATAVSIZE - Data Value Size
 *  0b00..Byte.
 *  0b01..Halfword.
 *  0b10..Word.
 *  0b11..Reserved. Any attempts to use this value results in UNPREDICTABLE behavior.
 */
#define MTBDWT_FCT_DATAVSIZE(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVSIZE_SHIFT)) & MTBDWT_FCT_DATAVSIZE_MASK)

#define MTBDWT_FCT_DATAVADDR0_MASK               (0xF000U)
#define MTBDWT_FCT_DATAVADDR0_SHIFT              (12U)
/*! DATAVADDR0 - Data Value Address 0
 */
#define MTBDWT_FCT_DATAVADDR0(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_DATAVADDR0_SHIFT)) & MTBDWT_FCT_DATAVADDR0_MASK)

#define MTBDWT_FCT_MATCHED_MASK                  (0x1000000U)
#define MTBDWT_FCT_MATCHED_SHIFT                 (24U)
/*! MATCHED - Comparator match
 *  0b0..No match.
 *  0b1..Match occurred.
 */
#define MTBDWT_FCT_MATCHED(x)                    (((uint32_t)(((uint32_t)(x)) << MTBDWT_FCT_MATCHED_SHIFT)) & MTBDWT_FCT_MATCHED_MASK)
/*! @} */

/* The count of MTBDWT_FCT */
#define MTBDWT_FCT_COUNT                         (2U)

/*! @name TBCTRL - MTB_DWT Trace Buffer Control Register */
/*! @{ */

#define MTBDWT_TBCTRL_ACOMP0_MASK                (0x1U)
#define MTBDWT_TBCTRL_ACOMP0_SHIFT               (0U)
/*! ACOMP0 - Action based on Comparator 0 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT0[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT0[MATCHED].
 */
#define MTBDWT_TBCTRL_ACOMP0(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_ACOMP0_SHIFT)) & MTBDWT_TBCTRL_ACOMP0_MASK)

#define MTBDWT_TBCTRL_ACOMP1_MASK                (0x2U)
#define MTBDWT_TBCTRL_ACOMP1_SHIFT               (1U)
/*! ACOMP1 - Action based on Comparator 1 match
 *  0b0..Trigger TSTOP based on the assertion of MTBDWT_FCT1[MATCHED].
 *  0b1..Trigger TSTART based on the assertion of MTBDWT_FCT1[MATCHED].
 */
#define MTBDWT_TBCTRL_ACOMP1(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_ACOMP1_SHIFT)) & MTBDWT_TBCTRL_ACOMP1_MASK)

#define MTBDWT_TBCTRL_NUMCOMP_MASK               (0xF0000000U)
#define MTBDWT_TBCTRL_NUMCOMP_SHIFT              (28U)
/*! NUMCOMP - Number of Comparators
 */
#define MTBDWT_TBCTRL_NUMCOMP(x)                 (((uint32_t)(((uint32_t)(x)) << MTBDWT_TBCTRL_NUMCOMP_SHIFT)) & MTBDWT_TBCTRL_NUMCOMP_MASK)
/*! @} */

/*! @name DEVICECFG - Device Configuration Register */
/*! @{ */

#define MTBDWT_DEVICECFG_DEVICECFG_MASK          (0xFFFFFFFFU)
#define MTBDWT_DEVICECFG_DEVICECFG_SHIFT         (0U)
/*! DEVICECFG - DEVICECFG
 */
#define MTBDWT_DEVICECFG_DEVICECFG(x)            (((uint32_t)(((uint32_t)(x)) << MTBDWT_DEVICECFG_DEVICECFG_SHIFT)) & MTBDWT_DEVICECFG_DEVICECFG_MASK)
/*! @} */

/*! @name DEVICETYPID - Device Type Identifier Register */
/*! @{ */

#define MTBDWT_DEVICETYPID_DEVICETYPID_MASK      (0xFFFFFFFFU)
#define MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT     (0U)
/*! DEVICETYPID - DEVICETYPID
 */
#define MTBDWT_DEVICETYPID_DEVICETYPID(x)        (((uint32_t)(((uint32_t)(x)) << MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT)) & MTBDWT_DEVICETYPID_DEVICETYPID_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID4_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID4_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID4_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID4_PERIPHID_SHIFT)) & MTBDWT_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID5_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID5_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID5_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID5_PERIPHID_SHIFT)) & MTBDWT_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID6_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID6_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID6_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID6_PERIPHID_SHIFT)) & MTBDWT_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID7_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID7_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID7_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID7_PERIPHID_SHIFT)) & MTBDWT_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID0_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID0_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID0_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID0_PERIPHID_SHIFT)) & MTBDWT_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID1_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID1_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID1_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID1_PERIPHID_SHIFT)) & MTBDWT_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID2_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID2_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID2_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID2_PERIPHID_SHIFT)) & MTBDWT_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define MTBDWT_PERIPHID3_PERIPHID_MASK           (0xFFFFFFFFU)
#define MTBDWT_PERIPHID3_PERIPHID_SHIFT          (0U)
/*! PERIPHID - PERIPHID
 */
#define MTBDWT_PERIPHID3_PERIPHID(x)             (((uint32_t)(((uint32_t)(x)) << MTBDWT_PERIPHID3_PERIPHID_SHIFT)) & MTBDWT_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define MTBDWT_COMPID_COMPID_MASK                (0xFFFFFFFFU)
#define MTBDWT_COMPID_COMPID_SHIFT               (0U)
/*! COMPID - Component ID
 */
#define MTBDWT_COMPID_COMPID(x)                  (((uint32_t)(((uint32_t)(x)) << MTBDWT_COMPID_COMPID_SHIFT)) & MTBDWT_COMPID_COMPID_MASK)
/*! @} */

/* The count of MTBDWT_COMPID */
#define MTBDWT_COMPID_COUNT                      (4U)


/*!
 * @}
 */ /* end of group MTBDWT_Register_Masks */


/* MTBDWT - Peripheral instance base addresses */
/** Peripheral MTBDWT base address */
#define MTBDWT_BASE                              (0xF0001000u)
/** Peripheral MTBDWT base pointer */
#define MTBDWT                                   ((MTBDWT_Type *)MTBDWT_BASE)
/** Array initializer of MTBDWT peripheral base addresses */
#define MTBDWT_BASE_ADDRS                        { MTBDWT_BASE }
/** Array initializer of MTBDWT peripheral base pointers */
#define MTBDWT_BASE_PTRS                         { MTBDWT }

/*!
 * @}
 */ /* end of group MTBDWT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- NV Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Peripheral_Access_Layer NV Peripheral Access Layer
 * @{
 */

/** NV - Register Layout Typedef */
typedef struct {
  __I  uint8_t BACKKEY3;                           /**< Backdoor Comparison Key 3., offset: 0x0 */
  __I  uint8_t BACKKEY2;                           /**< Backdoor Comparison Key 2., offset: 0x1 */
  __I  uint8_t BACKKEY1;                           /**< Backdoor Comparison Key 1., offset: 0x2 */
  __I  uint8_t BACKKEY0;                           /**< Backdoor Comparison Key 0., offset: 0x3 */
  __I  uint8_t BACKKEY7;                           /**< Backdoor Comparison Key 7., offset: 0x4 */
  __I  uint8_t BACKKEY6;                           /**< Backdoor Comparison Key 6., offset: 0x5 */
  __I  uint8_t BACKKEY5;                           /**< Backdoor Comparison Key 5., offset: 0x6 */
  __I  uint8_t BACKKEY4;                           /**< Backdoor Comparison Key 4., offset: 0x7 */
  __I  uint8_t FPROT3;                             /**< Non-volatile P-Flash Protection 1 - Low Register, offset: 0x8 */
  __I  uint8_t FPROT2;                             /**< Non-volatile P-Flash Protection 1 - High Register, offset: 0x9 */
  __I  uint8_t FPROT1;                             /**< Non-volatile P-Flash Protection 0 - Low Register, offset: 0xA */
  __I  uint8_t FPROT0;                             /**< Non-volatile P-Flash Protection 0 - High Register, offset: 0xB */
  __I  uint8_t FSEC;                               /**< Non-volatile Flash Security Register, offset: 0xC */
  __I  uint8_t FOPT;                               /**< Non-volatile Flash Option Register, offset: 0xD */
} NV_Type;

/* ----------------------------------------------------------------------------
   -- NV Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup NV_Register_Masks NV Register Masks
 * @{
 */

/*! @name BACKKEY3 - Backdoor Comparison Key 3. */
/*! @{ */

#define NV_BACKKEY3_KEY_MASK                     (0xFFU)
#define NV_BACKKEY3_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY3_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY3_KEY_SHIFT)) & NV_BACKKEY3_KEY_MASK)
/*! @} */

/*! @name BACKKEY2 - Backdoor Comparison Key 2. */
/*! @{ */

#define NV_BACKKEY2_KEY_MASK                     (0xFFU)
#define NV_BACKKEY2_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY2_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY2_KEY_SHIFT)) & NV_BACKKEY2_KEY_MASK)
/*! @} */

/*! @name BACKKEY1 - Backdoor Comparison Key 1. */
/*! @{ */

#define NV_BACKKEY1_KEY_MASK                     (0xFFU)
#define NV_BACKKEY1_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY1_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY1_KEY_SHIFT)) & NV_BACKKEY1_KEY_MASK)
/*! @} */

/*! @name BACKKEY0 - Backdoor Comparison Key 0. */
/*! @{ */

#define NV_BACKKEY0_KEY_MASK                     (0xFFU)
#define NV_BACKKEY0_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY0_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY0_KEY_SHIFT)) & NV_BACKKEY0_KEY_MASK)
/*! @} */

/*! @name BACKKEY7 - Backdoor Comparison Key 7. */
/*! @{ */

#define NV_BACKKEY7_KEY_MASK                     (0xFFU)
#define NV_BACKKEY7_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY7_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY7_KEY_SHIFT)) & NV_BACKKEY7_KEY_MASK)
/*! @} */

/*! @name BACKKEY6 - Backdoor Comparison Key 6. */
/*! @{ */

#define NV_BACKKEY6_KEY_MASK                     (0xFFU)
#define NV_BACKKEY6_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY6_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY6_KEY_SHIFT)) & NV_BACKKEY6_KEY_MASK)
/*! @} */

/*! @name BACKKEY5 - Backdoor Comparison Key 5. */
/*! @{ */

#define NV_BACKKEY5_KEY_MASK                     (0xFFU)
#define NV_BACKKEY5_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY5_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY5_KEY_SHIFT)) & NV_BACKKEY5_KEY_MASK)
/*! @} */

/*! @name BACKKEY4 - Backdoor Comparison Key 4. */
/*! @{ */

#define NV_BACKKEY4_KEY_MASK                     (0xFFU)
#define NV_BACKKEY4_KEY_SHIFT                    (0U)
/*! KEY - Backdoor Comparison Key.
 */
#define NV_BACKKEY4_KEY(x)                       (((uint8_t)(((uint8_t)(x)) << NV_BACKKEY4_KEY_SHIFT)) & NV_BACKKEY4_KEY_MASK)
/*! @} */

/*! @name FPROT3 - Non-volatile P-Flash Protection 1 - Low Register */
/*! @{ */

#define NV_FPROT3_PROT_MASK                      (0xFFU)
#define NV_FPROT3_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT3_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT3_PROT_SHIFT)) & NV_FPROT3_PROT_MASK)
/*! @} */

/*! @name FPROT2 - Non-volatile P-Flash Protection 1 - High Register */
/*! @{ */

#define NV_FPROT2_PROT_MASK                      (0xFFU)
#define NV_FPROT2_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT2_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT2_PROT_SHIFT)) & NV_FPROT2_PROT_MASK)
/*! @} */

/*! @name FPROT1 - Non-volatile P-Flash Protection 0 - Low Register */
/*! @{ */

#define NV_FPROT1_PROT_MASK                      (0xFFU)
#define NV_FPROT1_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT1_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT1_PROT_SHIFT)) & NV_FPROT1_PROT_MASK)
/*! @} */

/*! @name FPROT0 - Non-volatile P-Flash Protection 0 - High Register */
/*! @{ */

#define NV_FPROT0_PROT_MASK                      (0xFFU)
#define NV_FPROT0_PROT_SHIFT                     (0U)
/*! PROT - P-Flash Region Protect
 */
#define NV_FPROT0_PROT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FPROT0_PROT_SHIFT)) & NV_FPROT0_PROT_MASK)
/*! @} */

/*! @name FSEC - Non-volatile Flash Security Register */
/*! @{ */

#define NV_FSEC_SEC_MASK                         (0x3U)
#define NV_FSEC_SEC_SHIFT                        (0U)
/*! SEC - Flash Security
 *  0b10..MCU security status is unsecure
 *  0b11..MCU security status is secure
 */
#define NV_FSEC_SEC(x)                           (((uint8_t)(((uint8_t)(x)) << NV_FSEC_SEC_SHIFT)) & NV_FSEC_SEC_MASK)

#define NV_FSEC_FSLACC_MASK                      (0xCU)
#define NV_FSEC_FSLACC_SHIFT                     (2U)
/*! FSLACC - Freescale Failure Analysis Access Code
 *  0b10..Freescale factory access denied
 *  0b11..Freescale factory access granted
 */
#define NV_FSEC_FSLACC(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FSEC_FSLACC_SHIFT)) & NV_FSEC_FSLACC_MASK)

#define NV_FSEC_MEEN_MASK                        (0x30U)
#define NV_FSEC_MEEN_SHIFT                       (4U)
/*! MEEN
 *  0b10..Mass erase is disabled
 *  0b11..Mass erase is enabled
 */
#define NV_FSEC_MEEN(x)                          (((uint8_t)(((uint8_t)(x)) << NV_FSEC_MEEN_SHIFT)) & NV_FSEC_MEEN_MASK)

#define NV_FSEC_KEYEN_MASK                       (0xC0U)
#define NV_FSEC_KEYEN_SHIFT                      (6U)
/*! KEYEN - Backdoor Key Security Enable
 *  0b10..Backdoor key access enabled
 *  0b11..Backdoor key access disabled
 */
#define NV_FSEC_KEYEN(x)                         (((uint8_t)(((uint8_t)(x)) << NV_FSEC_KEYEN_SHIFT)) & NV_FSEC_KEYEN_MASK)
/*! @} */

/*! @name FOPT - Non-volatile Flash Option Register */
/*! @{ */

#define NV_FOPT_LPBOOT_MASK                      (0x1U)
#define NV_FOPT_LPBOOT_SHIFT                     (0U)
/*! LPBOOT
 *  0b0..Low-power boot
 *  0b1..Normal boot
 */
#define NV_FOPT_LPBOOT(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FOPT_LPBOOT_SHIFT)) & NV_FOPT_LPBOOT_MASK)

#define NV_FOPT_NMI_EN_MASK                      (0x4U)
#define NV_FOPT_NMI_EN_SHIFT                     (2U)
/*! NMI_EN
 *  0b0..NMI interrupts are always blocked
 *  0b1..NMI_b pin/interrupts reset default to enabled
 */
#define NV_FOPT_NMI_EN(x)                        (((uint8_t)(((uint8_t)(x)) << NV_FOPT_NMI_EN_SHIFT)) & NV_FOPT_NMI_EN_MASK)

#define NV_FOPT_EXE_MODE_MASK                    (0x8U)
#define NV_FOPT_EXE_MODE_SHIFT                   (3U)
/*! EXE_MODE
 *  0b0..Execution Mode is RUN Mode
 *  0b1..Execution Mode is VLPR Mode
 */
#define NV_FOPT_EXE_MODE(x)                      (((uint8_t)(((uint8_t)(x)) << NV_FOPT_EXE_MODE_SHIFT)) & NV_FOPT_EXE_MODE_MASK)

#define NV_FOPT_CLK_SRC_MASK                     (0x20U)
#define NV_FOPT_CLK_SRC_SHIFT                    (5U)
/*! CLK_SRC
 *  0b0..Externally supplied clock used by Flash
 *  0b1..Internal clock source used by Flash
 */
#define NV_FOPT_CLK_SRC(x)                       (((uint8_t)(((uint8_t)(x)) << NV_FOPT_CLK_SRC_SHIFT)) & NV_FOPT_CLK_SRC_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group NV_Register_Masks */


/* NV - Peripheral instance base addresses */
/** Peripheral FTFA_FlashConfig base address */
#define FTFA_FlashConfig_BASE                    (0x400u)
/** Peripheral FTFA_FlashConfig base pointer */
#define FTFA_FlashConfig                         ((NV_Type *)FTFA_FlashConfig_BASE)
/** Array initializer of NV peripheral base addresses */
#define NV_BASE_ADDRS                            { FTFA_FlashConfig_BASE }
/** Array initializer of NV peripheral base pointers */
#define NV_BASE_PTRS                             { FTFA_FlashConfig }

/*!
 * @}
 */ /* end of group NV_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- OSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Peripheral_Access_Layer OSC Peripheral Access Layer
 * @{
 */

/** OSC - Register Layout Typedef */
typedef struct {
  __IO uint8_t CR;                                 /**< OSC Control Register, offset: 0x0 */
} OSC_Type;

/* ----------------------------------------------------------------------------
   -- OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OSC_Register_Masks OSC Register Masks
 * @{
 */

/*! @name CR - OSC Control Register */
/*! @{ */

#define OSC_CR_SC16P_MASK                        (0x1U)
#define OSC_CR_SC16P_SHIFT                       (0U)
/*! SC16P - Oscillator 16 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 16 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC16P(x)                          (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC16P_SHIFT)) & OSC_CR_SC16P_MASK)

#define OSC_CR_SC8P_MASK                         (0x2U)
#define OSC_CR_SC8P_SHIFT                        (1U)
/*! SC8P - Oscillator 8 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 8 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC8P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC8P_SHIFT)) & OSC_CR_SC8P_MASK)

#define OSC_CR_SC4P_MASK                         (0x4U)
#define OSC_CR_SC4P_SHIFT                        (2U)
/*! SC4P - Oscillator 4 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 4 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC4P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC4P_SHIFT)) & OSC_CR_SC4P_MASK)

#define OSC_CR_SC2P_MASK                         (0x8U)
#define OSC_CR_SC2P_SHIFT                        (3U)
/*! SC2P - Oscillator 2 pF Capacitor Load Configure
 *  0b0..Disable the selection.
 *  0b1..Add 2 pF capacitor to the oscillator load.
 */
#define OSC_CR_SC2P(x)                           (((uint8_t)(((uint8_t)(x)) << OSC_CR_SC2P_SHIFT)) & OSC_CR_SC2P_MASK)

#define OSC_CR_EREFSTEN_MASK                     (0x20U)
#define OSC_CR_EREFSTEN_SHIFT                    (5U)
/*! EREFSTEN - External Reference Stop Enable
 *  0b0..External reference clock is disabled in Stop mode.
 *  0b1..External reference clock stays enabled in Stop mode if ERCLKEN is set before entering Stop mode.
 */
#define OSC_CR_EREFSTEN(x)                       (((uint8_t)(((uint8_t)(x)) << OSC_CR_EREFSTEN_SHIFT)) & OSC_CR_EREFSTEN_MASK)

#define OSC_CR_ERCLKEN_MASK                      (0x80U)
#define OSC_CR_ERCLKEN_SHIFT                     (7U)
/*! ERCLKEN - External Reference Enable
 *  0b0..External reference clock is inactive.
 *  0b1..External reference clock is enabled.
 */
#define OSC_CR_ERCLKEN(x)                        (((uint8_t)(((uint8_t)(x)) << OSC_CR_ERCLKEN_SHIFT)) & OSC_CR_ERCLKEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group OSC_Register_Masks */


/* OSC - Peripheral instance base addresses */
/** Peripheral OSC base address */
#define OSC_BASE                                 (0x40066000u)
/** Peripheral OSC base pointer */
#define OSC                                      ((OSC_Type *)OSC_BASE)
/** Array initializer of OSC peripheral base addresses */
#define OSC_BASE_ADDRS                           { OSC_BASE }
/** Array initializer of OSC peripheral base pointers */
#define OSC_BASE_PTRS                            { OSC }

/*!
 * @}
 */ /* end of group OSC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral_Access_Layer PIT Peripheral Access Layer
 * @{
 */

/** PIT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< PIT Module Control Register, offset: 0x0 */
       uint8_t RESERVED_0[252];
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    __I  uint32_t CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    __IO uint32_t TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    __IO uint32_t TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } CHANNEL[2];
} PIT_Type;

/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/*! @name MCR - PIT Module Control Register */
/*! @{ */

#define PIT_MCR_FRZ_MASK                         (0x1U)
#define PIT_MCR_FRZ_SHIFT                        (0U)
/*! FRZ - Freeze
 *  0b0..Timers continue to run in Debug mode.
 *  0b1..Timers are stopped in Debug mode.
 */
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << PIT_MCR_FRZ_SHIFT)) & PIT_MCR_FRZ_MASK)

#define PIT_MCR_MDIS_MASK                        (0x2U)
#define PIT_MCR_MDIS_SHIFT                       (1U)
/*! MDIS - Module Disable - (PIT section)
 *  0b0..Clock for standard PIT timers is enabled.
 *  0b1..Clock for standard PIT timers is disabled.
 */
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_MCR_MDIS_SHIFT)) & PIT_MCR_MDIS_MASK)
/*! @} */

/*! @name LDVAL - Timer Load Value Register */
/*! @{ */

#define PIT_LDVAL_TSV_MASK                       (0xFFFFFFFFU)
#define PIT_LDVAL_TSV_SHIFT                      (0U)
/*! TSV - Timer Start Value
 */
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_LDVAL_TSV_SHIFT)) & PIT_LDVAL_TSV_MASK)
/*! @} */

/* The count of PIT_LDVAL */
#define PIT_LDVAL_COUNT                          (2U)

/*! @name CVAL - Current Timer Value Register */
/*! @{ */

#define PIT_CVAL_TVL_MASK                        (0xFFFFFFFFU)
#define PIT_CVAL_TVL_SHIFT                       (0U)
/*! TVL - Current Timer Value
 */
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_CVAL_TVL_SHIFT)) & PIT_CVAL_TVL_MASK)
/*! @} */

/* The count of PIT_CVAL */
#define PIT_CVAL_COUNT                           (2U)

/*! @name TCTRL - Timer Control Register */
/*! @{ */

#define PIT_TCTRL_TEN_MASK                       (0x1U)
#define PIT_TCTRL_TEN_SHIFT                      (0U)
/*! TEN - Timer Enable
 *  0b0..Timer n is disabled.
 *  0b1..Timer n is enabled.
 */
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TEN_SHIFT)) & PIT_TCTRL_TEN_MASK)

#define PIT_TCTRL_TIE_MASK                       (0x2U)
#define PIT_TCTRL_TIE_SHIFT                      (1U)
/*! TIE - Timer Interrupt Enable
 *  0b0..Interrupt requests from Timer n are disabled.
 *  0b1..Interrupt will be requested whenever TIF is set.
 */
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TIE_SHIFT)) & PIT_TCTRL_TIE_MASK)

#define PIT_TCTRL_CHN_MASK                       (0x4U)
#define PIT_TCTRL_CHN_SHIFT                      (2U)
/*! CHN - Chain Mode
 *  0b0..Timer is not chained.
 *  0b1..Timer is chained to previous timer. For example, for Channel 2, if this field is set, Timer 2 is chained to Timer 1.
 */
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_CHN_SHIFT)) & PIT_TCTRL_CHN_MASK)
/*! @} */

/* The count of PIT_TCTRL */
#define PIT_TCTRL_COUNT                          (2U)

/*! @name TFLG - Timer Flag Register */
/*! @{ */

#define PIT_TFLG_TIF_MASK                        (0x1U)
#define PIT_TFLG_TIF_SHIFT                       (0U)
/*! TIF - Timer Interrupt Flag
 *  0b0..Timeout has not yet occurred.
 *  0b1..Timeout has occurred.
 */
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_TFLG_TIF_SHIFT)) & PIT_TFLG_TIF_MASK)
/*! @} */

/* The count of PIT_TFLG */
#define PIT_TFLG_COUNT                           (2U)


/*!
 * @}
 */ /* end of group PIT_Register_Masks */


/* PIT - Peripheral instance base addresses */
/** Peripheral PIT0 base address */
#define PIT0_BASE                                (0x4002D000u)
/** Peripheral PIT0 base pointer */
#define PIT0                                     ((PIT_Type *)PIT0_BASE)
/** Peripheral PIT1 base address */
#define PIT1_BASE                                (0x4002E000u)
/** Peripheral PIT1 base pointer */
#define PIT1                                     ((PIT_Type *)PIT1_BASE)
/** Array initializer of PIT peripheral base addresses */
#define PIT_BASE_ADDRS                           { PIT0_BASE, PIT1_BASE }
/** Array initializer of PIT peripheral base pointers */
#define PIT_BASE_PTRS                            { PIT0, PIT1 }
/** Interrupt vectors for the PIT peripheral type */
#define PIT_IRQS                                 { { PIT0_PIT1_IRQn, PIT0_PIT1_IRQn }, { PIT0_PIT1_IRQn, PIT0_PIT1_IRQn } }

/*!
 * @}
 */ /* end of group PIT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */

/** PMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t LVDSC1;                             /**< Low Voltage Detect Status And Control 1 register, offset: 0x0 */
  __IO uint8_t LVDSC2;                             /**< Low Voltage Detect Status And Control 2 register, offset: 0x1 */
  __IO uint8_t REGSC;                              /**< Regulator Status And Control register, offset: 0x2 */
} PMC_Type;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */

/*! @name LVDSC1 - Low Voltage Detect Status And Control 1 register */
/*! @{ */

#define PMC_LVDSC1_LVDV_MASK                     (0x3U)
#define PMC_LVDSC1_LVDV_SHIFT                    (0U)
/*! LVDV - Low-Voltage Detect Voltage Select
 *  0b00..Low trip point selected (V LVD = V LVDL )
 *  0b01..High trip point selected (V LVD = V LVDH )
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define PMC_LVDSC1_LVDV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDV_SHIFT)) & PMC_LVDSC1_LVDV_MASK)

#define PMC_LVDSC1_LVDRE_MASK                    (0x10U)
#define PMC_LVDSC1_LVDRE_SHIFT                   (4U)
/*! LVDRE - Low-Voltage Detect Reset Enable
 *  0b0..LVDF does not generate hardware resets
 *  0b1..Force an MCU reset when LVDF = 1
 */
#define PMC_LVDSC1_LVDRE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDRE_SHIFT)) & PMC_LVDSC1_LVDRE_MASK)

#define PMC_LVDSC1_LVDIE_MASK                    (0x20U)
#define PMC_LVDSC1_LVDIE_SHIFT                   (5U)
/*! LVDIE - Low-Voltage Detect Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVDF = 1
 */
#define PMC_LVDSC1_LVDIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDIE_SHIFT)) & PMC_LVDSC1_LVDIE_MASK)

#define PMC_LVDSC1_LVDACK_MASK                   (0x40U)
#define PMC_LVDSC1_LVDACK_SHIFT                  (6U)
/*! LVDACK - Low-Voltage Detect Acknowledge
 */
#define PMC_LVDSC1_LVDACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDACK_SHIFT)) & PMC_LVDSC1_LVDACK_MASK)

#define PMC_LVDSC1_LVDF_MASK                     (0x80U)
#define PMC_LVDSC1_LVDF_SHIFT                    (7U)
/*! LVDF - Low-Voltage Detect Flag
 *  0b0..Low-voltage event not detected
 *  0b1..Low-voltage event detected
 */
#define PMC_LVDSC1_LVDF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC1_LVDF_SHIFT)) & PMC_LVDSC1_LVDF_MASK)
/*! @} */

/*! @name LVDSC2 - Low Voltage Detect Status And Control 2 register */
/*! @{ */

#define PMC_LVDSC2_LVWV_MASK                     (0x3U)
#define PMC_LVDSC2_LVWV_SHIFT                    (0U)
/*! LVWV - Low-Voltage Warning Voltage Select
 *  0b00..Low trip point selected (VLVW = VLVW1)
 *  0b01..Mid 1 trip point selected (VLVW = VLVW2)
 *  0b10..Mid 2 trip point selected (VLVW = VLVW3)
 *  0b11..High trip point selected (VLVW = VLVW4)
 */
#define PMC_LVDSC2_LVWV(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWV_SHIFT)) & PMC_LVDSC2_LVWV_MASK)

#define PMC_LVDSC2_LVWIE_MASK                    (0x20U)
#define PMC_LVDSC2_LVWIE_SHIFT                   (5U)
/*! LVWIE - Low-Voltage Warning Interrupt Enable
 *  0b0..Hardware interrupt disabled (use polling)
 *  0b1..Request a hardware interrupt when LVWF = 1
 */
#define PMC_LVDSC2_LVWIE(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWIE_SHIFT)) & PMC_LVDSC2_LVWIE_MASK)

#define PMC_LVDSC2_LVWACK_MASK                   (0x40U)
#define PMC_LVDSC2_LVWACK_SHIFT                  (6U)
/*! LVWACK - Low-Voltage Warning Acknowledge
 */
#define PMC_LVDSC2_LVWACK(x)                     (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWACK_SHIFT)) & PMC_LVDSC2_LVWACK_MASK)

#define PMC_LVDSC2_LVWF_MASK                     (0x80U)
#define PMC_LVDSC2_LVWF_SHIFT                    (7U)
/*! LVWF - Low-Voltage Warning Flag
 *  0b0..Low-voltage warning event not detected
 *  0b1..Low-voltage warning event detected
 */
#define PMC_LVDSC2_LVWF(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_LVDSC2_LVWF_SHIFT)) & PMC_LVDSC2_LVWF_MASK)
/*! @} */

/*! @name REGSC - Regulator Status And Control register */
/*! @{ */

#define PMC_REGSC_BGBE_MASK                      (0x1U)
#define PMC_REGSC_BGBE_SHIFT                     (0U)
/*! BGBE - Bandgap Buffer Enable
 *  0b0..Bandgap buffer not enabled
 *  0b1..Bandgap buffer enabled
 */
#define PMC_REGSC_BGBE(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGBE_SHIFT)) & PMC_REGSC_BGBE_MASK)

#define PMC_REGSC_BGBDS_MASK                     (0x2U)
#define PMC_REGSC_BGBDS_SHIFT                    (1U)
/*! BGBDS - Bandgap Buffer Drive Select
 *  0b0..Low drive
 *  0b1..High drive
 */
#define PMC_REGSC_BGBDS(x)                       (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGBDS_SHIFT)) & PMC_REGSC_BGBDS_MASK)

#define PMC_REGSC_REGONS_MASK                    (0x4U)
#define PMC_REGSC_REGONS_SHIFT                   (2U)
/*! REGONS - Regulator In Run Regulation Status
 *  0b0..Regulator is in stop regulation or in transition to/from it
 *  0b1..Regulator is in run regulation
 */
#define PMC_REGSC_REGONS(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_REGONS_SHIFT)) & PMC_REGSC_REGONS_MASK)

#define PMC_REGSC_ACKISO_MASK                    (0x8U)
#define PMC_REGSC_ACKISO_SHIFT                   (3U)
/*! ACKISO - Acknowledge Isolation
 *  0b0..Peripherals and I/O pads are in normal run state.
 *  0b1..Certain peripherals and I/O pads are in an isolated and latched state.
 */
#define PMC_REGSC_ACKISO(x)                      (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_ACKISO_SHIFT)) & PMC_REGSC_ACKISO_MASK)

#define PMC_REGSC_BGEN_MASK                      (0x10U)
#define PMC_REGSC_BGEN_SHIFT                     (4U)
/*! BGEN - Bandgap Enable In VLPx Operation
 *  0b0..Bandgap voltage reference is disabled in VLPx , and VLLSx modes.
 *  0b1..Bandgap voltage reference is enabled in VLPx , and VLLSx modes.
 */
#define PMC_REGSC_BGEN(x)                        (((uint8_t)(((uint8_t)(x)) << PMC_REGSC_BGEN_SHIFT)) & PMC_REGSC_BGEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PMC_Register_Masks */


/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE                                 (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC                                      ((PMC_Type *)PMC_BASE)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS                           { PMC_BASE }
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            { PMC }
/** Interrupt vectors for the PMC peripheral type */
#define PMC_IRQS                                 { PMC_IRQn }

/*!
 * @}
 */ /* end of group PMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- PORT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[8];                            /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
       uint8_t RESERVED_0[96];
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_1[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
       uint8_t RESERVED_2[28];
  __IO uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
  __IO uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
  __IO uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
/*! @{ */

#define PORT_PCR_PS_MASK                         (0x1U)
#define PORT_PCR_PS_SHIFT                        (0U)
/*! PS - Pull Select
 *  0b0..Internal pulldown resistor is enabled on the corresponding pin, if the corresponding Port Pull Enable field is set.
 *  0b1..Internal pullup resistor is enabled on the corresponding pin, if the corresponding Port Pull Enable field is set.
 */
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)

#define PORT_PCR_PE_MASK                         (0x2U)
#define PORT_PCR_PE_SHIFT                        (1U)
/*! PE - Pull Enable
 *  0b0..Internal pullup or pulldown resistor is not enabled on the corresponding pin.
 *  0b1..Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)

#define PORT_PCR_SRE_MASK                        (0x4U)
#define PORT_PCR_SRE_SHIFT                       (2U)
/*! SRE - Slew Rate Enable
 *  0b0..Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 *  0b1..Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output.
 */
#define PORT_PCR_SRE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_SRE_SHIFT)) & PORT_PCR_SRE_MASK)

#define PORT_PCR_MUX_MASK                        (0x700U)
#define PORT_PCR_MUX_SHIFT                       (8U)
/*! MUX - Pin Mux Control
 *  0b000..Pin disabled (analog).
 *  0b001..Alternative 1 (GPIO).
 *  0b010..Alternative 2 (chip-specific).
 *  0b011..Alternative 3 (chip-specific).
 *  0b100..Alternative 4 (chip-specific).
 *  0b101..Alternative 5 (chip-specific).
 *  0b110..Alternative 6 (chip-specific).
 *  0b111..Alternative 7 (chip-specific).
 */
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)

#define PORT_PCR_LK_MASK                         (0x8000U)
#define PORT_PCR_LK_SHIFT                        (15U)
/*! LK - Lock Register
 *  0b0..Pin Control Register fields [15:0] are not locked.
 *  0b1..Pin Control Register fields [15:0] are locked and cannot be updated until the next system reset.
 */
#define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_LK_SHIFT)) & PORT_PCR_LK_MASK)

#define PORT_PCR_IRQC_MASK                       (0xF0000U)
#define PORT_PCR_IRQC_SHIFT                      (16U)
/*! IRQC - Interrupt Configuration
 *  0b0000..Interrupt/DMA request disabled.
 *  0b0001..DMA request on rising edge.
 *  0b0010..DMA request on falling edge.
 *  0b0011..DMA request on either edge.
 *  0b1000..Interrupt when logic zero.
 *  0b1001..Interrupt on rising edge.
 *  0b1010..Interrupt on falling edge.
 *  0b1011..Interrupt on either edge.
 *  0b1100..Interrupt when logic one.
 */
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)

#define PORT_PCR_ISF_MASK                        (0x1000000U)
#define PORT_PCR_ISF_SHIFT                       (24U)
/*! ISF - Interrupt Status Flag
 *  0b0..Configured interrupt is not detected.
 *  0b1..Configured interrupt is detected. If the pin is configured to generate a DMA request, then the
 *       corresponding flag will be cleared automatically at the completion of the requested DMA transfer. Otherwise, the
 *       flag remains set until a logic one is written to the flag. If the pin is configured for a level sensitive
 *       interrupt and the pin remains asserted, then the flag is set again immediately after it is cleared.
 */
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)
/*! @} */

/* The count of PORT_PCR */
#define PORT_PCR_COUNT                           (8U)

/*! @name GPCLR - Global Pin Control Low Register */
/*! @{ */

#define PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)

#define PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)
/*! @} */

/*! @name GPCHR - Global Pin Control High Register */
/*! @{ */

#define PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)

#define PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)
/*! @} */

/*! @name ISFR - Interrupt Status Flag Register */
/*! @{ */

#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT                      (0U)
/*! ISF - Interrupt Status Flag
 *  0b00000000000000000000000000000000..Configured interrupt is not detected.
 *  0b00000000000000000000000000000001..Configured interrupt is detected. If the pin is configured to generate a
 *                                      DMA request, then the corresponding flag will be cleared automatically at
 *                                      the completion of the requested DMA transfer. Otherwise, the flag remains set
 *                                      until a logic one is written to the flag. If the pin is configured for a
 *                                      level sensitive interrupt and the pin remains asserted, then the flag is set
 *                                      again immediately after it is cleared.
 */
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)
/*! @} */

/*! @name DFER - Digital Filter Enable Register */
/*! @{ */

#define PORT_DFER_DFE_MASK                       (0xFFFFFFFFU)
#define PORT_DFER_DFE_SHIFT                      (0U)
/*! DFE - Digital Filter Enable
 *  0b00000000000000000000000000000000..Digital filter is disabled on the corresponding pin and output of the digital filter is reset to zero.
 *  0b00000000000000000000000000000001..Digital filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
#define PORT_DFER_DFE(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_DFER_DFE_SHIFT)) & PORT_DFER_DFE_MASK)
/*! @} */

/*! @name DFCR - Digital Filter Clock Register */
/*! @{ */

#define PORT_DFCR_CS_MASK                        (0x1U)
#define PORT_DFCR_CS_SHIFT                       (0U)
/*! CS - Clock Source
 *  0b0..Digital filters are clocked by the bus clock.
 *  0b1..Digital filters are clocked by the 1 kHz LPO clock.
 */
#define PORT_DFCR_CS(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_DFCR_CS_SHIFT)) & PORT_DFCR_CS_MASK)
/*! @} */

/*! @name DFWR - Digital Filter Width Register */
/*! @{ */

#define PORT_DFWR_FILT_MASK                      (0x1FU)
#define PORT_DFWR_FILT_SHIFT                     (0U)
/*! FILT - Filter Length
 */
#define PORT_DFWR_FILT(x)                        (((uint32_t)(((uint32_t)(x)) << PORT_DFWR_FILT_SHIFT)) & PORT_DFWR_FILT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40046000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x40047000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x40048000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x40049000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004A000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)
/** Peripheral PORTF base address */
#define PORTF_BASE                               (0x4004B000u)
/** Peripheral PORTF base pointer */
#define PORTF                                    ((PORT_Type *)PORTF_BASE)
/** Peripheral PORTG base address */
#define PORTG_BASE                               (0x4004C000u)
/** Peripheral PORTG base pointer */
#define PORTG                                    ((PORT_Type *)PORTG_BASE)
/** Peripheral PORTH base address */
#define PORTH_BASE                               (0x4004D000u)
/** Peripheral PORTH base pointer */
#define PORTH                                    ((PORT_Type *)PORTH_BASE)
/** Peripheral PORTI base address */
#define PORTI_BASE                               (0x4004E000u)
/** Peripheral PORTI base pointer */
#define PORTI                                    ((PORT_Type *)PORTI_BASE)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                          { PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE, PORTF_BASE, PORTG_BASE, PORTH_BASE, PORTI_BASE }
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           { PORTA, PORTB, PORTC, PORTD, PORTE, PORTF, PORTG, PORTH, PORTI }
/** Interrupt vectors for the PORT peripheral type */
#define PORT_IRQS                                { PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn, PTx_IRQn }

/*!
 * @}
 */ /* end of group PORT_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Peripheral_Access_Layer RCM Peripheral Access Layer
 * @{
 */

/** RCM - Register Layout Typedef */
typedef struct {
  __I  uint8_t SRS0;                               /**< System Reset Status Register 0, offset: 0x0 */
  __I  uint8_t SRS1;                               /**< System Reset Status Register 1, offset: 0x1 */
       uint8_t RESERVED_0[2];
  __IO uint8_t RPFC;                               /**< Reset Pin Filter Control register, offset: 0x4 */
  __IO uint8_t RPFW;                               /**< Reset Pin Filter Width register, offset: 0x5 */
} RCM_Type;

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */

/*! @name SRS0 - System Reset Status Register 0 */
/*! @{ */

#define RCM_SRS0_WAKEUP_MASK                     (0x1U)
#define RCM_SRS0_WAKEUP_SHIFT                    (0U)
/*! WAKEUP - Low Leakage Wakeup Reset
 *  0b0..Reset not caused by wakeup source
 *  0b1..Reset caused by wakeup source
 */
#define RCM_SRS0_WAKEUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WAKEUP_SHIFT)) & RCM_SRS0_WAKEUP_MASK)

#define RCM_SRS0_LVD_MASK                        (0x2U)
#define RCM_SRS0_LVD_SHIFT                       (1U)
/*! LVD - Low-Voltage Detect Reset
 *  0b0..Reset not caused by LVD trip or POR
 *  0b1..Reset caused by LVD trip or POR
 */
#define RCM_SRS0_LVD(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LVD_SHIFT)) & RCM_SRS0_LVD_MASK)

#define RCM_SRS0_LOC_MASK                        (0x4U)
#define RCM_SRS0_LOC_SHIFT                       (2U)
/*! LOC - Loss-of-Clock Reset
 *  0b0..Reset not caused by a loss of external clock.
 *  0b1..Reset caused by a loss of external clock.
 */
#define RCM_SRS0_LOC(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LOC_SHIFT)) & RCM_SRS0_LOC_MASK)

#define RCM_SRS0_LOL_MASK                        (0x8U)
#define RCM_SRS0_LOL_SHIFT                       (3U)
/*! LOL - Loss-of-Lock Reset
 *  0b0..Reset not caused by a loss of lock in the PLL
 *  0b1..Reset caused by a loss of lock in the PLL
 */
#define RCM_SRS0_LOL(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_LOL_SHIFT)) & RCM_SRS0_LOL_MASK)

#define RCM_SRS0_WDOG_MASK                       (0x20U)
#define RCM_SRS0_WDOG_SHIFT                      (5U)
/*! WDOG - Watchdog
 *  0b0..Reset not caused by watchdog timeout
 *  0b1..Reset caused by watchdog timeout
 */
#define RCM_SRS0_WDOG(x)                         (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_WDOG_SHIFT)) & RCM_SRS0_WDOG_MASK)

#define RCM_SRS0_PIN_MASK                        (0x40U)
#define RCM_SRS0_PIN_SHIFT                       (6U)
/*! PIN - External Reset Pin
 *  0b0..Reset not caused by external reset pin
 *  0b1..Reset caused by external reset pin
 */
#define RCM_SRS0_PIN(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_PIN_SHIFT)) & RCM_SRS0_PIN_MASK)

#define RCM_SRS0_POR_MASK                        (0x80U)
#define RCM_SRS0_POR_SHIFT                       (7U)
/*! POR - Power-On Reset
 *  0b0..Reset not caused by POR
 *  0b1..Reset caused by POR
 */
#define RCM_SRS0_POR(x)                          (((uint8_t)(((uint8_t)(x)) << RCM_SRS0_POR_SHIFT)) & RCM_SRS0_POR_MASK)
/*! @} */

/*! @name SRS1 - System Reset Status Register 1 */
/*! @{ */

#define RCM_SRS1_LOCKUP_MASK                     (0x2U)
#define RCM_SRS1_LOCKUP_SHIFT                    (1U)
/*! LOCKUP - Core Lockup
 *  0b0..Reset not caused by core LOCKUP event
 *  0b1..Reset caused by core LOCKUP event
 */
#define RCM_SRS1_LOCKUP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_LOCKUP_SHIFT)) & RCM_SRS1_LOCKUP_MASK)

#define RCM_SRS1_SW_MASK                         (0x4U)
#define RCM_SRS1_SW_SHIFT                        (2U)
/*! SW - Software
 *  0b0..Reset not caused by software setting of SYSRESETREQ bit
 *  0b1..Reset caused by software setting of SYSRESETREQ bit
 */
#define RCM_SRS1_SW(x)                           (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SW_SHIFT)) & RCM_SRS1_SW_MASK)

#define RCM_SRS1_MDM_AP_MASK                     (0x8U)
#define RCM_SRS1_MDM_AP_SHIFT                    (3U)
/*! MDM_AP - MDM-AP System Reset Request
 *  0b0..Reset not caused by host debugger system setting of the System Reset Request bit
 *  0b1..Reset caused by host debugger system setting of the System Reset Request bit
 */
#define RCM_SRS1_MDM_AP(x)                       (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_MDM_AP_SHIFT)) & RCM_SRS1_MDM_AP_MASK)

#define RCM_SRS1_SACKERR_MASK                    (0x20U)
#define RCM_SRS1_SACKERR_SHIFT                   (5U)
/*! SACKERR - Stop Mode Acknowledge Error Reset
 *  0b0..Reset not caused by peripheral failure to acknowledge attempt to enter stop mode
 *  0b1..Reset caused by peripheral failure to acknowledge attempt to enter stop mode
 */
#define RCM_SRS1_SACKERR(x)                      (((uint8_t)(((uint8_t)(x)) << RCM_SRS1_SACKERR_SHIFT)) & RCM_SRS1_SACKERR_MASK)
/*! @} */

/*! @name RPFC - Reset Pin Filter Control register */
/*! @{ */

#define RCM_RPFC_RSTFLTSRW_MASK                  (0x3U)
#define RCM_RPFC_RSTFLTSRW_SHIFT                 (0U)
/*! RSTFLTSRW - Reset Pin Filter Select in Run and Wait Modes
 *  0b00..All filtering disabled
 *  0b01..Bus clock filter enabled for normal operation
 *  0b10..LPO clock filter enabled for normal operation
 *  0b11..Reserved
 */
#define RCM_RPFC_RSTFLTSRW(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSRW_SHIFT)) & RCM_RPFC_RSTFLTSRW_MASK)

#define RCM_RPFC_RSTFLTSS_MASK                   (0x4U)
#define RCM_RPFC_RSTFLTSS_SHIFT                  (2U)
/*! RSTFLTSS - Reset Pin Filter Select in Stop Mode
 *  0b0..All filtering disabled
 *  0b1..LPO clock filter enabled
 */
#define RCM_RPFC_RSTFLTSS(x)                     (((uint8_t)(((uint8_t)(x)) << RCM_RPFC_RSTFLTSS_SHIFT)) & RCM_RPFC_RSTFLTSS_MASK)
/*! @} */

/*! @name RPFW - Reset Pin Filter Width register */
/*! @{ */

#define RCM_RPFW_RSTFLTSEL_MASK                  (0x1FU)
#define RCM_RPFW_RSTFLTSEL_SHIFT                 (0U)
/*! RSTFLTSEL - Reset Pin Filter Bus Clock Select
 *  0b00000..Bus clock filter count is 1
 *  0b00001..Bus clock filter count is 2
 *  0b00010..Bus clock filter count is 3
 *  0b00011..Bus clock filter count is 4
 *  0b00100..Bus clock filter count is 5
 *  0b00101..Bus clock filter count is 6
 *  0b00110..Bus clock filter count is 7
 *  0b00111..Bus clock filter count is 8
 *  0b01000..Bus clock filter count is 9
 *  0b01001..Bus clock filter count is 10
 *  0b01010..Bus clock filter count is 11
 *  0b01011..Bus clock filter count is 12
 *  0b01100..Bus clock filter count is 13
 *  0b01101..Bus clock filter count is 14
 *  0b01110..Bus clock filter count is 15
 *  0b01111..Bus clock filter count is 16
 *  0b10000..Bus clock filter count is 17
 *  0b10001..Bus clock filter count is 18
 *  0b10010..Bus clock filter count is 19
 *  0b10011..Bus clock filter count is 20
 *  0b10100..Bus clock filter count is 21
 *  0b10101..Bus clock filter count is 22
 *  0b10110..Bus clock filter count is 23
 *  0b10111..Bus clock filter count is 24
 *  0b11000..Bus clock filter count is 25
 *  0b11001..Bus clock filter count is 26
 *  0b11010..Bus clock filter count is 27
 *  0b11011..Bus clock filter count is 28
 *  0b11100..Bus clock filter count is 29
 *  0b11101..Bus clock filter count is 30
 *  0b11110..Bus clock filter count is 31
 *  0b11111..Bus clock filter count is 32
 */
#define RCM_RPFW_RSTFLTSEL(x)                    (((uint8_t)(((uint8_t)(x)) << RCM_RPFW_RSTFLTSEL_SHIFT)) & RCM_RPFW_RSTFLTSEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RCM_Register_Masks */


/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE                                 (0x4007B000u)
/** Peripheral RCM base pointer */
#define RCM                                      ((RCM_Type *)RCM_BASE)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS                           { RCM_BASE }
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            { RCM }

/*!
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RNG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Peripheral_Access_Layer RNG Peripheral Access Layer
 * @{
 */

/** RNG - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< RNGA Control Register, offset: 0x0 */
  __I  uint32_t SR;                                /**< RNGA Status Register, offset: 0x4 */
  __O  uint32_t ER;                                /**< RNGA Entropy Register, offset: 0x8 */
  __I  uint32_t OR;                                /**< RNGA Output Register, offset: 0xC */
} RNG_Type;

/* ----------------------------------------------------------------------------
   -- RNG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RNG_Register_Masks RNG Register Masks
 * @{
 */

/*! @name CR - RNGA Control Register */
/*! @{ */

#define RNG_CR_GO_MASK                           (0x1U)
#define RNG_CR_GO_SHIFT                          (0U)
/*! GO - Go
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define RNG_CR_GO(x)                             (((uint32_t)(((uint32_t)(x)) << RNG_CR_GO_SHIFT)) & RNG_CR_GO_MASK)

#define RNG_CR_HA_MASK                           (0x2U)
#define RNG_CR_HA_SHIFT                          (1U)
/*! HA - High Assurance
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define RNG_CR_HA(x)                             (((uint32_t)(((uint32_t)(x)) << RNG_CR_HA_SHIFT)) & RNG_CR_HA_MASK)

#define RNG_CR_INTM_MASK                         (0x4U)
#define RNG_CR_INTM_SHIFT                        (2U)
/*! INTM - Interrupt Mask
 *  0b0..Not masked
 *  0b1..Masked
 */
#define RNG_CR_INTM(x)                           (((uint32_t)(((uint32_t)(x)) << RNG_CR_INTM_SHIFT)) & RNG_CR_INTM_MASK)

#define RNG_CR_CLRI_MASK                         (0x8U)
#define RNG_CR_CLRI_SHIFT                        (3U)
/*! CLRI - Clear Interrupt
 *  0b0..Do not clear the interrupt.
 *  0b1..Clear the interrupt. When you write 1 to this field, RNGA then resets the error-interrupt indicator (SR[ERRI]). This bit always reads as 0.
 */
#define RNG_CR_CLRI(x)                           (((uint32_t)(((uint32_t)(x)) << RNG_CR_CLRI_SHIFT)) & RNG_CR_CLRI_MASK)

#define RNG_CR_SLP_MASK                          (0x10U)
#define RNG_CR_SLP_SHIFT                         (4U)
/*! SLP - Sleep
 *  0b0..Normal mode
 *  0b1..Sleep (low-power) mode
 */
#define RNG_CR_SLP(x)                            (((uint32_t)(((uint32_t)(x)) << RNG_CR_SLP_SHIFT)) & RNG_CR_SLP_MASK)
/*! @} */

/*! @name SR - RNGA Status Register */
/*! @{ */

#define RNG_SR_SECV_MASK                         (0x1U)
#define RNG_SR_SECV_SHIFT                        (0U)
/*! SECV - Security Violation
 *  0b0..No security violation
 *  0b1..Security violation
 */
#define RNG_SR_SECV(x)                           (((uint32_t)(((uint32_t)(x)) << RNG_SR_SECV_SHIFT)) & RNG_SR_SECV_MASK)

#define RNG_SR_LRS_MASK                          (0x2U)
#define RNG_SR_LRS_SHIFT                         (1U)
/*! LRS - Last Read Status
 *  0b0..No underflow
 *  0b1..Underflow
 */
#define RNG_SR_LRS(x)                            (((uint32_t)(((uint32_t)(x)) << RNG_SR_LRS_SHIFT)) & RNG_SR_LRS_MASK)

#define RNG_SR_ORU_MASK                          (0x4U)
#define RNG_SR_ORU_SHIFT                         (2U)
/*! ORU - Output Register Underflow
 *  0b0..No underflow
 *  0b1..Underflow
 */
#define RNG_SR_ORU(x)                            (((uint32_t)(((uint32_t)(x)) << RNG_SR_ORU_SHIFT)) & RNG_SR_ORU_MASK)

#define RNG_SR_ERRI_MASK                         (0x8U)
#define RNG_SR_ERRI_SHIFT                        (3U)
/*! ERRI - Error Interrupt
 *  0b0..No underflow
 *  0b1..Underflow
 */
#define RNG_SR_ERRI(x)                           (((uint32_t)(((uint32_t)(x)) << RNG_SR_ERRI_SHIFT)) & RNG_SR_ERRI_MASK)

#define RNG_SR_SLP_MASK                          (0x10U)
#define RNG_SR_SLP_SHIFT                         (4U)
/*! SLP - Sleep
 *  0b0..Normal mode
 *  0b1..Sleep (low-power) mode
 */
#define RNG_SR_SLP(x)                            (((uint32_t)(((uint32_t)(x)) << RNG_SR_SLP_SHIFT)) & RNG_SR_SLP_MASK)

#define RNG_SR_OREG_LVL_MASK                     (0xFF00U)
#define RNG_SR_OREG_LVL_SHIFT                    (8U)
/*! OREG_LVL - Output Register Level
 *  0b00000000..No words (empty)
 *  0b00000001..One word (valid)
 */
#define RNG_SR_OREG_LVL(x)                       (((uint32_t)(((uint32_t)(x)) << RNG_SR_OREG_LVL_SHIFT)) & RNG_SR_OREG_LVL_MASK)

#define RNG_SR_OREG_SIZE_MASK                    (0xFF0000U)
#define RNG_SR_OREG_SIZE_SHIFT                   (16U)
/*! OREG_SIZE - Output Register Size
 *  0b00000001..One word (this value is fixed)
 */
#define RNG_SR_OREG_SIZE(x)                      (((uint32_t)(((uint32_t)(x)) << RNG_SR_OREG_SIZE_SHIFT)) & RNG_SR_OREG_SIZE_MASK)
/*! @} */

/*! @name ER - RNGA Entropy Register */
/*! @{ */

#define RNG_ER_EXT_ENT_MASK                      (0xFFFFFFFFU)
#define RNG_ER_EXT_ENT_SHIFT                     (0U)
/*! EXT_ENT - External Entropy
 */
#define RNG_ER_EXT_ENT(x)                        (((uint32_t)(((uint32_t)(x)) << RNG_ER_EXT_ENT_SHIFT)) & RNG_ER_EXT_ENT_MASK)
/*! @} */

/*! @name OR - RNGA Output Register */
/*! @{ */

#define RNG_OR_RANDOUT_MASK                      (0xFFFFFFFFU)
#define RNG_OR_RANDOUT_SHIFT                     (0U)
/*! RANDOUT - Random Output
 *  0b00000000000000000000000000000000..Invalid data (if you read this field when it is 0 and SR[OREG_LVL] is 0,
 *                                      RNGA then writes 1 to SR[ERRI], SR[ORU], and SR[LRS]; when the error
 *                                      interrupt is not masked (CR[INTM]=0), RNGA also asserts an error interrupt request
 *                                      to the interrupt controller).
 */
#define RNG_OR_RANDOUT(x)                        (((uint32_t)(((uint32_t)(x)) << RNG_OR_RANDOUT_SHIFT)) & RNG_OR_RANDOUT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RNG_Register_Masks */


/* RNG - Peripheral instance base addresses */
/** Peripheral RNG base address */
#define RNG_BASE                                 (0x40029000u)
/** Peripheral RNG base pointer */
#define RNG                                      ((RNG_Type *)RNG_BASE)
/** Array initializer of RNG peripheral base addresses */
#define RNG_BASE_ADDRS                           { RNG_BASE }
/** Array initializer of RNG peripheral base pointers */
#define RNG_BASE_PTRS                            { RNG }
/** Interrupt vectors for the RNG peripheral type */
#define RNG_IRQS                                 { RNGA_IRQn }

/*!
 * @}
 */ /* end of group RNG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- ROM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Peripheral_Access_Layer ROM Peripheral Access Layer
 * @{
 */

/** ROM - Register Layout Typedef */
typedef struct {
  __I  uint32_t ENTRY[3];                          /**< Entry, array offset: 0x0, array step: 0x4 */
  __I  uint32_t TABLEMARK;                         /**< End of Table Marker Register, offset: 0xC */
       uint8_t RESERVED_0[4028];
  __I  uint32_t SYSACCESS;                         /**< System Access Register, offset: 0xFCC */
  __I  uint32_t PERIPHID4;                         /**< Peripheral ID Register, offset: 0xFD0 */
  __I  uint32_t PERIPHID5;                         /**< Peripheral ID Register, offset: 0xFD4 */
  __I  uint32_t PERIPHID6;                         /**< Peripheral ID Register, offset: 0xFD8 */
  __I  uint32_t PERIPHID7;                         /**< Peripheral ID Register, offset: 0xFDC */
  __I  uint32_t PERIPHID0;                         /**< Peripheral ID Register, offset: 0xFE0 */
  __I  uint32_t PERIPHID1;                         /**< Peripheral ID Register, offset: 0xFE4 */
  __I  uint32_t PERIPHID2;                         /**< Peripheral ID Register, offset: 0xFE8 */
  __I  uint32_t PERIPHID3;                         /**< Peripheral ID Register, offset: 0xFEC */
  __I  uint32_t COMPID[4];                         /**< Component ID Register, array offset: 0xFF0, array step: 0x4 */
} ROM_Type;

/* ----------------------------------------------------------------------------
   -- ROM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ROM_Register_Masks ROM Register Masks
 * @{
 */

/*! @name ENTRY - Entry */
/*! @{ */

#define ROM_ENTRY_ENTRY_MASK                     (0xFFFFFFFFU)
#define ROM_ENTRY_ENTRY_SHIFT                    (0U)
/*! ENTRY - ENTRY
 */
#define ROM_ENTRY_ENTRY(x)                       (((uint32_t)(((uint32_t)(x)) << ROM_ENTRY_ENTRY_SHIFT)) & ROM_ENTRY_ENTRY_MASK)
/*! @} */

/* The count of ROM_ENTRY */
#define ROM_ENTRY_COUNT                          (3U)

/*! @name TABLEMARK - End of Table Marker Register */
/*! @{ */

#define ROM_TABLEMARK_MARK_MASK                  (0xFFFFFFFFU)
#define ROM_TABLEMARK_MARK_SHIFT                 (0U)
/*! MARK - MARK
 */
#define ROM_TABLEMARK_MARK(x)                    (((uint32_t)(((uint32_t)(x)) << ROM_TABLEMARK_MARK_SHIFT)) & ROM_TABLEMARK_MARK_MASK)
/*! @} */

/*! @name SYSACCESS - System Access Register */
/*! @{ */

#define ROM_SYSACCESS_SYSACCESS_MASK             (0xFFFFFFFFU)
#define ROM_SYSACCESS_SYSACCESS_SHIFT            (0U)
/*! SYSACCESS - SYSACCESS
 */
#define ROM_SYSACCESS_SYSACCESS(x)               (((uint32_t)(((uint32_t)(x)) << ROM_SYSACCESS_SYSACCESS_SHIFT)) & ROM_SYSACCESS_SYSACCESS_MASK)
/*! @} */

/*! @name PERIPHID4 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID4_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID4_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID4_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID4_PERIPHID_SHIFT)) & ROM_PERIPHID4_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID5 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID5_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID5_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID5_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID5_PERIPHID_SHIFT)) & ROM_PERIPHID5_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID6 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID6_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID6_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID6_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID6_PERIPHID_SHIFT)) & ROM_PERIPHID6_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID7 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID7_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID7_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID7_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID7_PERIPHID_SHIFT)) & ROM_PERIPHID7_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID0 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID0_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID0_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID0_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID0_PERIPHID_SHIFT)) & ROM_PERIPHID0_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID1 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID1_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID1_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID1_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID1_PERIPHID_SHIFT)) & ROM_PERIPHID1_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID2 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID2_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID2_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID2_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID2_PERIPHID_SHIFT)) & ROM_PERIPHID2_PERIPHID_MASK)
/*! @} */

/*! @name PERIPHID3 - Peripheral ID Register */
/*! @{ */

#define ROM_PERIPHID3_PERIPHID_MASK              (0xFFFFFFFFU)
#define ROM_PERIPHID3_PERIPHID_SHIFT             (0U)
/*! PERIPHID - PERIPHID
 */
#define ROM_PERIPHID3_PERIPHID(x)                (((uint32_t)(((uint32_t)(x)) << ROM_PERIPHID3_PERIPHID_SHIFT)) & ROM_PERIPHID3_PERIPHID_MASK)
/*! @} */

/*! @name COMPID - Component ID Register */
/*! @{ */

#define ROM_COMPID_COMPID_MASK                   (0xFFFFFFFFU)
#define ROM_COMPID_COMPID_SHIFT                  (0U)
/*! COMPID - Component ID
 */
#define ROM_COMPID_COMPID(x)                     (((uint32_t)(((uint32_t)(x)) << ROM_COMPID_COMPID_SHIFT)) & ROM_COMPID_COMPID_MASK)
/*! @} */

/* The count of ROM_COMPID */
#define ROM_COMPID_COUNT                         (4U)


/*!
 * @}
 */ /* end of group ROM_Register_Masks */


/* ROM - Peripheral instance base addresses */
/** Peripheral ROM base address */
#define ROM_BASE                                 (0xF0002000u)
/** Peripheral ROM base pointer */
#define ROM                                      ((ROM_Type *)ROM_BASE)
/** Array initializer of ROM peripheral base addresses */
#define ROM_BASE_ADDRS                           { ROM_BASE }
/** Array initializer of ROM peripheral base pointers */
#define ROM_BASE_PTRS                            { ROM }

/*!
 * @}
 */ /* end of group ROM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint16_t YEARMON;                           /**< RTC Year and Month Counters Register, offset: 0x0 */
  __IO uint16_t DAYS;                              /**< RTC Days and Day-of-Week Counters Register, offset: 0x2 */
  __IO uint16_t HOURMIN;                           /**< RTC Hours and Minutes Counters Register, offset: 0x4 */
  __IO uint16_t SECONDS;                           /**< RTC Seconds Counters Register, offset: 0x6 */
  __IO uint16_t ALM_YEARMON;                       /**< RTC Year and Months Alarm Register, offset: 0x8 */
  __IO uint16_t ALM_DAYS;                          /**< RTC Days Alarm Register, offset: 0xA */
  __IO uint16_t ALM_HOURMIN;                       /**< RTC Hours and Minutes Alarm Register, offset: 0xC */
  __IO uint16_t ALM_SECONDS;                       /**< RTC Seconds Alarm Register, offset: 0xE */
  __IO uint16_t CTRL;                              /**< RTC Control Register, offset: 0x10 */
  __IO uint16_t STATUS;                            /**< RTC Status Register, offset: 0x12 */
  __IO uint16_t ISR;                               /**< RTC Interrupt Status Register, offset: 0x14 */
  __IO uint16_t IER;                               /**< RTC Interrupt Enable Register, offset: 0x16 */
       uint8_t RESERVED_0[8];
  __IO uint16_t GP_DATA_REG;                       /**< RTC General Purpose Data Register, offset: 0x20 */
  __IO uint16_t DST_HOUR;                          /**< RTC Daylight Saving Hour Register, offset: 0x22 */
  __IO uint16_t DST_MONTH;                         /**< RTC Daylight Saving Month Register, offset: 0x24 */
  __IO uint16_t DST_DAY;                           /**< RTC Daylight Saving Day Register, offset: 0x26 */
  __IO uint16_t COMPEN;                            /**< RTC Compensation Register, offset: 0x28 */
       uint8_t RESERVED_1[8];
  __IO uint16_t TAMPER_SCR;                        /**< RTC Tamper Status and Control Register, offset: 0x32 */
  __IO uint16_t FILTER01_CFG;                      /**< RTC Tamper 0 1 Filter Configuration Register, offset: 0x34 */
  __IO uint16_t FILTER2_CFG;                       /**< RTC Tamper 2 Filter Configuration Register, offset: 0x36 */
       uint8_t RESERVED_2[10];
  __IO uint16_t CTRL2;                             /**< RTC Control 2 Register, offset: 0x42 */
} RTC_Type;

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name YEARMON - RTC Year and Month Counters Register */
/*! @{ */

#define RTC_YEARMON_MON_CNT_MASK                 (0xFU)
#define RTC_YEARMON_MON_CNT_SHIFT                (0U)
/*! MON_CNT
 *  0b0000..Illegal Value
 *  0b0001..January
 *  0b0010..February
 *  0b0011..March
 *  0b0100..April
 *  0b0101..May
 *  0b0110..June
 *  0b0111..July
 *  0b1000..August
 *  0b1001..September
 *  0b0010..October
 *  0b0011..November
 *  0b1100..December
 *  0b1101..Illegal Value
 *  0b1110..Illegal Value
 *  0b1111..Illegal Value
 */
#define RTC_YEARMON_MON_CNT(x)                   (((uint16_t)(((uint16_t)(x)) << RTC_YEARMON_MON_CNT_SHIFT)) & RTC_YEARMON_MON_CNT_MASK)

#define RTC_YEARMON_YROFST_MASK                  (0xFF00U)
#define RTC_YEARMON_YROFST_SHIFT                 (8U)
/*! YROFST - Year Offset Count Value
 */
#define RTC_YEARMON_YROFST(x)                    (((uint16_t)(((uint16_t)(x)) << RTC_YEARMON_YROFST_SHIFT)) & RTC_YEARMON_YROFST_MASK)
/*! @} */

/*! @name DAYS - RTC Days and Day-of-Week Counters Register */
/*! @{ */

#define RTC_DAYS_DAY_CNT_MASK                    (0x1FU)
#define RTC_DAYS_DAY_CNT_SHIFT                   (0U)
/*! DAY_CNT - Days Counter Value.
 */
#define RTC_DAYS_DAY_CNT(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_DAYS_DAY_CNT_SHIFT)) & RTC_DAYS_DAY_CNT_MASK)

#define RTC_DAYS_DOW_MASK                        (0x700U)
#define RTC_DAYS_DOW_SHIFT                       (8U)
/*! DOW - Day of Week Counter Value.
 *  0b000..Sunday
 *  0b001..Monday
 *  0b010..Tuesday
 *  0b011..Wednesday
 *  0b100..Thrusday
 *  0b101..Friday
 *  0b110..Saturday
 *  0b111..Reserved
 */
#define RTC_DAYS_DOW(x)                          (((uint16_t)(((uint16_t)(x)) << RTC_DAYS_DOW_SHIFT)) & RTC_DAYS_DOW_MASK)
/*! @} */

/*! @name HOURMIN - RTC Hours and Minutes Counters Register */
/*! @{ */

#define RTC_HOURMIN_MIN_CNT_MASK                 (0x3FU)
#define RTC_HOURMIN_MIN_CNT_SHIFT                (0U)
/*! MIN_CNT - Minutes Counter Value.
 */
#define RTC_HOURMIN_MIN_CNT(x)                   (((uint16_t)(((uint16_t)(x)) << RTC_HOURMIN_MIN_CNT_SHIFT)) & RTC_HOURMIN_MIN_CNT_MASK)

#define RTC_HOURMIN_HOUR_CNT_MASK                (0x1F00U)
#define RTC_HOURMIN_HOUR_CNT_SHIFT               (8U)
/*! HOUR_CNT - Hours Counter Value.
 */
#define RTC_HOURMIN_HOUR_CNT(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_HOURMIN_HOUR_CNT_SHIFT)) & RTC_HOURMIN_HOUR_CNT_MASK)
/*! @} */

/*! @name SECONDS - RTC Seconds Counters Register */
/*! @{ */

#define RTC_SECONDS_SEC_CNT_MASK                 (0x3FU)
#define RTC_SECONDS_SEC_CNT_SHIFT                (0U)
/*! SEC_CNT - Seconds Counter Value.
 */
#define RTC_SECONDS_SEC_CNT(x)                   (((uint16_t)(((uint16_t)(x)) << RTC_SECONDS_SEC_CNT_SHIFT)) & RTC_SECONDS_SEC_CNT_MASK)
/*! @} */

/*! @name ALM_YEARMON - RTC Year and Months Alarm Register */
/*! @{ */

#define RTC_ALM_YEARMON_ALM_MON_MASK             (0xFU)
#define RTC_ALM_YEARMON_ALM_MON_SHIFT            (0U)
/*! ALM_MON - Months Value for Alarm.
 */
#define RTC_ALM_YEARMON_ALM_MON(x)               (((uint16_t)(((uint16_t)(x)) << RTC_ALM_YEARMON_ALM_MON_SHIFT)) & RTC_ALM_YEARMON_ALM_MON_MASK)

#define RTC_ALM_YEARMON_ALM_YEAR_MASK            (0xFF00U)
#define RTC_ALM_YEARMON_ALM_YEAR_SHIFT           (8U)
/*! ALM_YEAR - Year Value for Alarm.
 */
#define RTC_ALM_YEARMON_ALM_YEAR(x)              (((uint16_t)(((uint16_t)(x)) << RTC_ALM_YEARMON_ALM_YEAR_SHIFT)) & RTC_ALM_YEARMON_ALM_YEAR_MASK)
/*! @} */

/*! @name ALM_DAYS - RTC Days Alarm Register */
/*! @{ */

#define RTC_ALM_DAYS_ALM_DAY_MASK                (0x1FU)
#define RTC_ALM_DAYS_ALM_DAY_SHIFT               (0U)
/*! ALM_DAY - Days Value for Alarm.
 */
#define RTC_ALM_DAYS_ALM_DAY(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_ALM_DAYS_ALM_DAY_SHIFT)) & RTC_ALM_DAYS_ALM_DAY_MASK)
/*! @} */

/*! @name ALM_HOURMIN - RTC Hours and Minutes Alarm Register */
/*! @{ */

#define RTC_ALM_HOURMIN_ALM_MIN_MASK             (0x3FU)
#define RTC_ALM_HOURMIN_ALM_MIN_SHIFT            (0U)
/*! ALM_MIN - Minutes Value for Alarm.
 */
#define RTC_ALM_HOURMIN_ALM_MIN(x)               (((uint16_t)(((uint16_t)(x)) << RTC_ALM_HOURMIN_ALM_MIN_SHIFT)) & RTC_ALM_HOURMIN_ALM_MIN_MASK)

#define RTC_ALM_HOURMIN_ALM_HOUR_MASK            (0x1F00U)
#define RTC_ALM_HOURMIN_ALM_HOUR_SHIFT           (8U)
/*! ALM_HOUR - Hours Value for Alarm.
 */
#define RTC_ALM_HOURMIN_ALM_HOUR(x)              (((uint16_t)(((uint16_t)(x)) << RTC_ALM_HOURMIN_ALM_HOUR_SHIFT)) & RTC_ALM_HOURMIN_ALM_HOUR_MASK)
/*! @} */

/*! @name ALM_SECONDS - RTC Seconds Alarm Register */
/*! @{ */

#define RTC_ALM_SECONDS_ALM_SEC_MASK             (0x3FU)
#define RTC_ALM_SECONDS_ALM_SEC_SHIFT            (0U)
#define RTC_ALM_SECONDS_ALM_SEC(x)               (((uint16_t)(((uint16_t)(x)) << RTC_ALM_SECONDS_ALM_SEC_SHIFT)) & RTC_ALM_SECONDS_ALM_SEC_MASK)

#define RTC_ALM_SECONDS_DEC_SEC_MASK             (0x100U)
#define RTC_ALM_SECONDS_DEC_SEC_SHIFT            (8U)
/*! DEC_SEC - Decrement Seconds Counter by 1.
 */
#define RTC_ALM_SECONDS_DEC_SEC(x)               (((uint16_t)(((uint16_t)(x)) << RTC_ALM_SECONDS_DEC_SEC_SHIFT)) & RTC_ALM_SECONDS_DEC_SEC_MASK)

#define RTC_ALM_SECONDS_INC_SEC_MASK             (0x200U)
#define RTC_ALM_SECONDS_INC_SEC_SHIFT            (9U)
/*! INC_SEC - Increment Seconds Counter by 1.
 */
#define RTC_ALM_SECONDS_INC_SEC(x)               (((uint16_t)(((uint16_t)(x)) << RTC_ALM_SECONDS_INC_SEC_SHIFT)) & RTC_ALM_SECONDS_INC_SEC_MASK)
/*! @} */

/*! @name CTRL - RTC Control Register */
/*! @{ */

#define RTC_CTRL_FINEEN_MASK                     (0x1U)
#define RTC_CTRL_FINEEN_SHIFT                    (0U)
/*! FINEEN - Fine compensation enable bit
 *  0b1..Fine compensation is enabled.
 *  0b0..Fine compensation is disabled
 */
#define RTC_CTRL_FINEEN(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_FINEEN_SHIFT)) & RTC_CTRL_FINEEN_MASK)

#define RTC_CTRL_COMP_EN_MASK                    (0x2U)
#define RTC_CTRL_COMP_EN_SHIFT                   (1U)
#define RTC_CTRL_COMP_EN(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_COMP_EN_SHIFT)) & RTC_CTRL_COMP_EN_MASK)

#define RTC_CTRL_ALM_MATCH_MASK                  (0xCU)
#define RTC_CTRL_ALM_MATCH_SHIFT                 (2U)
/*! ALM_MATCH - Alarm Match bits.
 *  0b00..Only Seconds, Minutes, and Hours matched.
 *  0b01..Only Seconds, Minutes, Hours, and Days matched.
 *  0b10..Only Seconds, Minutes, Hours, Days, and Months matched.
 *  0b11..Only Seconds, Minutes, Hours, Days, Months, and Year (offset) matched.
 */
#define RTC_CTRL_ALM_MATCH(x)                    (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_ALM_MATCH_SHIFT)) & RTC_CTRL_ALM_MATCH_MASK)

#define RTC_CTRL_TIMER_STB_MASK_MASK             (0x10U)
#define RTC_CTRL_TIMER_STB_MASK_SHIFT            (4U)
/*! TIMER_STB_MASK - Sampling timer clocks mask
 *  0b1..Sampling clocks are gated in standby mode
 *  0b0..Sampling clocks are not gated when in standby mode
 */
#define RTC_CTRL_TIMER_STB_MASK(x)               (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_TIMER_STB_MASK_SHIFT)) & RTC_CTRL_TIMER_STB_MASK_MASK)

#define RTC_CTRL_DST_EN_MASK                     (0x40U)
#define RTC_CTRL_DST_EN_SHIFT                    (6U)
/*! DST_EN - Daylight Saving Enable.
 *  0b0..Disabled. Daylight saving changes are not applied. Daylight saving registers can be modified.
 *  0b1..Enabled. Daylight saving changes are applied.
 */
#define RTC_CTRL_DST_EN(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_DST_EN_SHIFT)) & RTC_CTRL_DST_EN_MASK)

#define RTC_CTRL_SWR_MASK                        (0x100U)
#define RTC_CTRL_SWR_SHIFT                       (8U)
/*! SWR - Software Reset bit.
 *  0b0..Software Reset cleared.
 *  0b1..Software Reset asserted.
 */
#define RTC_CTRL_SWR(x)                          (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_SWR_SHIFT)) & RTC_CTRL_SWR_MASK)

#define RTC_CTRL_CLKOUT_MASK                     (0x6000U)
#define RTC_CTRL_CLKOUT_SHIFT                    (13U)
/*! CLKOUT - RTC Clock Output Selection.
 *  0b00..No Output Clock
 *  0b01..Fine 1 Hz Clock
 *  0b10..32.768 kHz Clock
 *  0b11..Coarse 1 Hz Clock
 */
#define RTC_CTRL_CLKOUT(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_CTRL_CLKOUT_SHIFT)) & RTC_CTRL_CLKOUT_MASK)
/*! @} */

/*! @name STATUS - RTC Status Register */
/*! @{ */

#define RTC_STATUS_INVAL_BIT_MASK                (0x1U)
#define RTC_STATUS_INVAL_BIT_SHIFT               (0U)
/*! INVAL_BIT - Invalidate CPU read/write access bit.
 *  0b0..Time /Date Counters can be read/written. Time /Date is valid.
 *  0b1..Time /Date Counter values are changing or Time /Date is invalid and cannot be read or written.
 */
#define RTC_STATUS_INVAL_BIT(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_INVAL_BIT_SHIFT)) & RTC_STATUS_INVAL_BIT_MASK)

#define RTC_STATUS_WRITE_PROT_EN_MASK            (0x2U)
#define RTC_STATUS_WRITE_PROT_EN_SHIFT           (1U)
/*! WRITE_PROT_EN - Write Protect Enable status bit.
 *  0b0..Registers are unlocked and can be accessed.
 *  0b1..Registers are locked and in read-only mode.
 */
#define RTC_STATUS_WRITE_PROT_EN(x)              (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_WRITE_PROT_EN_SHIFT)) & RTC_STATUS_WRITE_PROT_EN_MASK)

#define RTC_STATUS_CPU_LOW_VOLT_MASK             (0x4U)
#define RTC_STATUS_CPU_LOW_VOLT_SHIFT            (2U)
/*! CPU_LOW_VOLT - CPU Low Voltage Warning status bit.
 *  0b0..CPU in Normal Operating Voltage.
 *  0b1..CPU Voltage is below Normal Operating Voltage. RTC Registers in read-only mode.
 */
#define RTC_STATUS_CPU_LOW_VOLT(x)               (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_CPU_LOW_VOLT_SHIFT)) & RTC_STATUS_CPU_LOW_VOLT_MASK)

#define RTC_STATUS_RST_SRC_MASK                  (0x8U)
#define RTC_STATUS_RST_SRC_SHIFT                 (3U)
/*! RST_SRC - Reset Source bit.
 *  0b0..Part was reset due to Standby Mode Exit (that is when VDD is powered up and VBAT was not powered down at all).
 *  0b1..Part was reset due to Power-On Reset (that is Power On Reset when both VBAT and VDD are powered up).
 */
#define RTC_STATUS_RST_SRC(x)                    (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_RST_SRC_SHIFT)) & RTC_STATUS_RST_SRC_MASK)

#define RTC_STATUS_CMP_INT_MASK                  (0x20U)
#define RTC_STATUS_CMP_INT_SHIFT                 (5U)
/*! CMP_INT - Compensation Interval bit.
 */
#define RTC_STATUS_CMP_INT(x)                    (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_CMP_INT_SHIFT)) & RTC_STATUS_CMP_INT_MASK)

#define RTC_STATUS_WE_MASK                       (0xC0U)
#define RTC_STATUS_WE_SHIFT                      (6U)
/*! WE - Write Enable bits.
 *  0b10..Enable Write Protection - Registers are locked.
 */
#define RTC_STATUS_WE(x)                         (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_WE_SHIFT)) & RTC_STATUS_WE_MASK)

#define RTC_STATUS_BUS_ERR_MASK                  (0x100U)
#define RTC_STATUS_BUS_ERR_SHIFT                 (8U)
/*! BUS_ERR - Bus Error bit.
 *  0b0..Read and Write accesses are normal.
 *  0b1..Read or Write accesses occurred when INVAL_BIT was asserted.
 */
#define RTC_STATUS_BUS_ERR(x)                    (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_BUS_ERR_SHIFT)) & RTC_STATUS_BUS_ERR_MASK)

#define RTC_STATUS_CMP_DONE_MASK                 (0x800U)
#define RTC_STATUS_CMP_DONE_SHIFT                (11U)
/*! CMP_DONE - Compensation Done bit.
 *  0b0..Compensation busy or not enabled.
 *  0b1..Compensation completed.
 */
#define RTC_STATUS_CMP_DONE(x)                   (((uint16_t)(((uint16_t)(x)) << RTC_STATUS_CMP_DONE_SHIFT)) & RTC_STATUS_CMP_DONE_MASK)
/*! @} */

/*! @name ISR - RTC Interrupt Status Register */
/*! @{ */

#define RTC_ISR_TAMPER_IS_MASK                   (0x1U)
#define RTC_ISR_TAMPER_IS_SHIFT                  (0U)
/*! TAMPER_IS - Tamper Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted (Default on reset) .
 */
#define RTC_ISR_TAMPER_IS(x)                     (((uint16_t)(((uint16_t)(x)) << RTC_ISR_TAMPER_IS_SHIFT)) & RTC_ISR_TAMPER_IS_MASK)

#define RTC_ISR_ALM_IS_MASK                      (0x4U)
#define RTC_ISR_ALM_IS_SHIFT                     (2U)
/*! ALM_IS - Alarm Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_ALM_IS(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_ALM_IS_SHIFT)) & RTC_ISR_ALM_IS_MASK)

#define RTC_ISR_DAY_IS_MASK                      (0x8U)
#define RTC_ISR_DAY_IS_SHIFT                     (3U)
/*! DAY_IS - Days Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_DAY_IS(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_DAY_IS_SHIFT)) & RTC_ISR_DAY_IS_MASK)

#define RTC_ISR_HOUR_IS_MASK                     (0x10U)
#define RTC_ISR_HOUR_IS_SHIFT                    (4U)
/*! HOUR_IS - Hours Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_HOUR_IS(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_ISR_HOUR_IS_SHIFT)) & RTC_ISR_HOUR_IS_MASK)

#define RTC_ISR_MIN_IS_MASK                      (0x20U)
#define RTC_ISR_MIN_IS_SHIFT                     (5U)
/*! MIN_IS - Minutes Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_MIN_IS(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_MIN_IS_SHIFT)) & RTC_ISR_MIN_IS_MASK)

#define RTC_ISR_IS_1HZ_MASK                      (0x40U)
#define RTC_ISR_IS_1HZ_SHIFT                     (6U)
/*! IS_1HZ - 1 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_1HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_1HZ_SHIFT)) & RTC_ISR_IS_1HZ_MASK)

#define RTC_ISR_IS_2HZ_MASK                      (0x80U)
#define RTC_ISR_IS_2HZ_SHIFT                     (7U)
/*! IS_2HZ - 2 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_2HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_2HZ_SHIFT)) & RTC_ISR_IS_2HZ_MASK)

#define RTC_ISR_IS_4HZ_MASK                      (0x100U)
#define RTC_ISR_IS_4HZ_SHIFT                     (8U)
/*! IS_4HZ - 4 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_4HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_4HZ_SHIFT)) & RTC_ISR_IS_4HZ_MASK)

#define RTC_ISR_IS_8HZ_MASK                      (0x200U)
#define RTC_ISR_IS_8HZ_SHIFT                     (9U)
/*! IS_8HZ - 8 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_8HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_8HZ_SHIFT)) & RTC_ISR_IS_8HZ_MASK)

#define RTC_ISR_IS_16HZ_MASK                     (0x400U)
#define RTC_ISR_IS_16HZ_SHIFT                    (10U)
/*! IS_16HZ - 16 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_16HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_16HZ_SHIFT)) & RTC_ISR_IS_16HZ_MASK)

#define RTC_ISR_IS_32HZ_MASK                     (0x800U)
#define RTC_ISR_IS_32HZ_SHIFT                    (11U)
/*! IS_32HZ - 32 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_32HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_32HZ_SHIFT)) & RTC_ISR_IS_32HZ_MASK)

#define RTC_ISR_IS_64HZ_MASK                     (0x1000U)
#define RTC_ISR_IS_64HZ_SHIFT                    (12U)
/*! IS_64HZ - 64 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_64HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_64HZ_SHIFT)) & RTC_ISR_IS_64HZ_MASK)

#define RTC_ISR_IS_128HZ_MASK                    (0x2000U)
#define RTC_ISR_IS_128HZ_SHIFT                   (13U)
/*! IS_128HZ - 128 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_128HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_128HZ_SHIFT)) & RTC_ISR_IS_128HZ_MASK)

#define RTC_ISR_IS_256HZ_MASK                    (0x4000U)
#define RTC_ISR_IS_256HZ_SHIFT                   (14U)
/*! IS_256HZ - 256 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_256HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_256HZ_SHIFT)) & RTC_ISR_IS_256HZ_MASK)

#define RTC_ISR_IS_512HZ_MASK                    (0x8000U)
#define RTC_ISR_IS_512HZ_SHIFT                   (15U)
/*! IS_512HZ - 512 Hz Interval Interrupt Status bit.
 *  0b0..Interrupt is de-asserted.
 *  0b1..Interrupt is asserted.
 */
#define RTC_ISR_IS_512HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_ISR_IS_512HZ_SHIFT)) & RTC_ISR_IS_512HZ_MASK)
/*! @} */

/*! @name IER - RTC Interrupt Enable Register */
/*! @{ */

#define RTC_IER_TAMPER_IE_MASK                   (0x1U)
#define RTC_IER_TAMPER_IE_SHIFT                  (0U)
/*! TAMPER_IE - Tamper Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled (Default on reset).
 */
#define RTC_IER_TAMPER_IE(x)                     (((uint16_t)(((uint16_t)(x)) << RTC_IER_TAMPER_IE_SHIFT)) & RTC_IER_TAMPER_IE_MASK)

#define RTC_IER_ALM_IE_MASK                      (0x4U)
#define RTC_IER_ALM_IE_SHIFT                     (2U)
/*! ALM_IE - Alarm Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_ALM_IE(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_ALM_IE_SHIFT)) & RTC_IER_ALM_IE_MASK)

#define RTC_IER_DAY_IE_MASK                      (0x8U)
#define RTC_IER_DAY_IE_SHIFT                     (3U)
/*! DAY_IE - Days Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_DAY_IE(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_DAY_IE_SHIFT)) & RTC_IER_DAY_IE_MASK)

#define RTC_IER_HOUR_IE_MASK                     (0x10U)
#define RTC_IER_HOUR_IE_SHIFT                    (4U)
/*! HOUR_IE - Hours Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_HOUR_IE(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_IER_HOUR_IE_SHIFT)) & RTC_IER_HOUR_IE_MASK)

#define RTC_IER_MIN_IE_MASK                      (0x20U)
#define RTC_IER_MIN_IE_SHIFT                     (5U)
/*! MIN_IE - Minutes Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_MIN_IE(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_MIN_IE_SHIFT)) & RTC_IER_MIN_IE_MASK)

#define RTC_IER_IE_1HZ_MASK                      (0x40U)
#define RTC_IER_IE_1HZ_SHIFT                     (6U)
/*! IE_1HZ - 1 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_1HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_1HZ_SHIFT)) & RTC_IER_IE_1HZ_MASK)

#define RTC_IER_IE_2HZ_MASK                      (0x80U)
#define RTC_IER_IE_2HZ_SHIFT                     (7U)
/*! IE_2HZ - 2 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_2HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_2HZ_SHIFT)) & RTC_IER_IE_2HZ_MASK)

#define RTC_IER_IE_4HZ_MASK                      (0x100U)
#define RTC_IER_IE_4HZ_SHIFT                     (8U)
/*! IE_4HZ - 4 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_4HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_4HZ_SHIFT)) & RTC_IER_IE_4HZ_MASK)

#define RTC_IER_IE_8HZ_MASK                      (0x200U)
#define RTC_IER_IE_8HZ_SHIFT                     (9U)
/*! IE_8HZ - 8 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_8HZ(x)                        (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_8HZ_SHIFT)) & RTC_IER_IE_8HZ_MASK)

#define RTC_IER_IE_16HZ_MASK                     (0x400U)
#define RTC_IER_IE_16HZ_SHIFT                    (10U)
/*! IE_16HZ - 16 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_16HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_16HZ_SHIFT)) & RTC_IER_IE_16HZ_MASK)

#define RTC_IER_IE_32HZ_MASK                     (0x800U)
#define RTC_IER_IE_32HZ_SHIFT                    (11U)
/*! IE_32HZ - 32 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_32HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_32HZ_SHIFT)) & RTC_IER_IE_32HZ_MASK)

#define RTC_IER_IE_64HZ_MASK                     (0x1000U)
#define RTC_IER_IE_64HZ_SHIFT                    (12U)
/*! IE_64HZ - 64 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_64HZ(x)                       (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_64HZ_SHIFT)) & RTC_IER_IE_64HZ_MASK)

#define RTC_IER_IE_128HZ_MASK                    (0x2000U)
#define RTC_IER_IE_128HZ_SHIFT                   (13U)
/*! IE_128HZ - 128 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_128HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_128HZ_SHIFT)) & RTC_IER_IE_128HZ_MASK)

#define RTC_IER_IE_256HZ_MASK                    (0x4000U)
#define RTC_IER_IE_256HZ_SHIFT                   (14U)
/*! IE_256HZ - 256 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_256HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_256HZ_SHIFT)) & RTC_IER_IE_256HZ_MASK)

#define RTC_IER_IE_512HZ_MASK                    (0x8000U)
#define RTC_IER_IE_512HZ_SHIFT                   (15U)
/*! IE_512HZ - 512 Hz Interval Interrupt Enable bit.
 *  0b0..Interrupt is disabled.
 *  0b1..Interrupt is enabled.
 */
#define RTC_IER_IE_512HZ(x)                      (((uint16_t)(((uint16_t)(x)) << RTC_IER_IE_512HZ_SHIFT)) & RTC_IER_IE_512HZ_MASK)
/*! @} */

/*! @name GP_DATA_REG - RTC General Purpose Data Register */
/*! @{ */

#define RTC_GP_DATA_REG_CFG0_MASK                (0x1U)
#define RTC_GP_DATA_REG_CFG0_SHIFT               (0U)
/*! CFG0 - 32 kHz RTC OSC Control
 *  0b0..Enables the oscillator
 *  0b1..Disables the oscillator
 */
#define RTC_GP_DATA_REG_CFG0(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG0_SHIFT)) & RTC_GP_DATA_REG_CFG0_MASK)

#define RTC_GP_DATA_REG_CFG1_MASK                (0x2U)
#define RTC_GP_DATA_REG_CFG1_SHIFT               (1U)
/*! CFG1 - Switched capacitor 2 pF enable
 *  0b0..Disables capacitor
 *  0b1..Enables capacitor
 */
#define RTC_GP_DATA_REG_CFG1(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG1_SHIFT)) & RTC_GP_DATA_REG_CFG1_MASK)

#define RTC_GP_DATA_REG_CFG2_MASK                (0x4U)
#define RTC_GP_DATA_REG_CFG2_SHIFT               (2U)
/*! CFG2 - Switched capacitor 4 pF enable
 *  0b0..Disables capacitor
 *  0b1..Enables capacitor
 */
#define RTC_GP_DATA_REG_CFG2(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG2_SHIFT)) & RTC_GP_DATA_REG_CFG2_MASK)

#define RTC_GP_DATA_REG_CFG3_MASK                (0x8U)
#define RTC_GP_DATA_REG_CFG3_SHIFT               (3U)
/*! CFG3 - Switched capacitor 8 pF enable
 *  0b0..Disables capacitor
 *  0b1..Enables capacitor
 */
#define RTC_GP_DATA_REG_CFG3(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG3_SHIFT)) & RTC_GP_DATA_REG_CFG3_MASK)

#define RTC_GP_DATA_REG_CFG4_MASK                (0x10U)
#define RTC_GP_DATA_REG_CFG4_SHIFT               (4U)
/*! CFG4 - Switched capacitor 16 pF enable
 *  0b0..Disables capacitor
 *  0b1..Enables capacitor
 */
#define RTC_GP_DATA_REG_CFG4(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG4_SHIFT)) & RTC_GP_DATA_REG_CFG4_MASK)

#define RTC_GP_DATA_REG_CFG7_MASK                (0x80U)
#define RTC_GP_DATA_REG_CFG7_SHIFT               (7U)
/*! CFG7 - Boot mode override bit
 *  0b0..Boot in RUN
 *  0b1..Boot in VLPR
 */
#define RTC_GP_DATA_REG_CFG7(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_GP_DATA_REG_CFG7_SHIFT)) & RTC_GP_DATA_REG_CFG7_MASK)
/*! @} */

/*! @name DST_HOUR - RTC Daylight Saving Hour Register */
/*! @{ */

#define RTC_DST_HOUR_DST_END_HOUR_MASK           (0x1FU)
#define RTC_DST_HOUR_DST_END_HOUR_SHIFT          (0U)
/*! DST_END_HOUR - Daylight Saving Time (DST) Hours End Value.
 */
#define RTC_DST_HOUR_DST_END_HOUR(x)             (((uint16_t)(((uint16_t)(x)) << RTC_DST_HOUR_DST_END_HOUR_SHIFT)) & RTC_DST_HOUR_DST_END_HOUR_MASK)

#define RTC_DST_HOUR_DST_START_HOUR_MASK         (0x1F00U)
#define RTC_DST_HOUR_DST_START_HOUR_SHIFT        (8U)
/*! DST_START_HOUR - Daylight Saving Time (DST) Hours Start Value.
 */
#define RTC_DST_HOUR_DST_START_HOUR(x)           (((uint16_t)(((uint16_t)(x)) << RTC_DST_HOUR_DST_START_HOUR_SHIFT)) & RTC_DST_HOUR_DST_START_HOUR_MASK)
/*! @} */

/*! @name DST_MONTH - RTC Daylight Saving Month Register */
/*! @{ */

#define RTC_DST_MONTH_DST_END_MONTH_MASK         (0xFU)
#define RTC_DST_MONTH_DST_END_MONTH_SHIFT        (0U)
/*! DST_END_MONTH - Daylight Saving Time (DST) Month End Value.
 */
#define RTC_DST_MONTH_DST_END_MONTH(x)           (((uint16_t)(((uint16_t)(x)) << RTC_DST_MONTH_DST_END_MONTH_SHIFT)) & RTC_DST_MONTH_DST_END_MONTH_MASK)

#define RTC_DST_MONTH_DST_START_MONTH_MASK       (0xF00U)
#define RTC_DST_MONTH_DST_START_MONTH_SHIFT      (8U)
/*! DST_START_MONTH - Daylight Saving Time (DST) Month Start Value.
 */
#define RTC_DST_MONTH_DST_START_MONTH(x)         (((uint16_t)(((uint16_t)(x)) << RTC_DST_MONTH_DST_START_MONTH_SHIFT)) & RTC_DST_MONTH_DST_START_MONTH_MASK)
/*! @} */

/*! @name DST_DAY - RTC Daylight Saving Day Register */
/*! @{ */

#define RTC_DST_DAY_DST_END_DAY_MASK             (0x1FU)
#define RTC_DST_DAY_DST_END_DAY_SHIFT            (0U)
/*! DST_END_DAY - Daylight Saving Time (DST) Day End Value.
 */
#define RTC_DST_DAY_DST_END_DAY(x)               (((uint16_t)(((uint16_t)(x)) << RTC_DST_DAY_DST_END_DAY_SHIFT)) & RTC_DST_DAY_DST_END_DAY_MASK)

#define RTC_DST_DAY_DST_START_DAY_MASK           (0x1F00U)
#define RTC_DST_DAY_DST_START_DAY_SHIFT          (8U)
/*! DST_START_DAY - Daylight Saving Time (DST) Day Start Value.
 */
#define RTC_DST_DAY_DST_START_DAY(x)             (((uint16_t)(((uint16_t)(x)) << RTC_DST_DAY_DST_START_DAY_SHIFT)) & RTC_DST_DAY_DST_START_DAY_MASK)
/*! @} */

/*! @name COMPEN - RTC Compensation Register */
/*! @{ */

#define RTC_COMPEN_COMPEN_VAL_MASK               (0xFFFFU)
#define RTC_COMPEN_COMPEN_VAL_SHIFT              (0U)
/*! COMPEN_VAL - Compensation Value
 */
#define RTC_COMPEN_COMPEN_VAL(x)                 (((uint16_t)(((uint16_t)(x)) << RTC_COMPEN_COMPEN_VAL_SHIFT)) & RTC_COMPEN_COMPEN_VAL_MASK)
/*! @} */

/*! @name TAMPER_SCR - RTC Tamper Status and Control Register */
/*! @{ */

#define RTC_TAMPER_SCR_TMPR_EN_MASK              (0xFU)
#define RTC_TAMPER_SCR_TMPR_EN_SHIFT             (0U)
/*! TMPR_EN - Tamper Control
 */
#define RTC_TAMPER_SCR_TMPR_EN(x)                (((uint16_t)(((uint16_t)(x)) << RTC_TAMPER_SCR_TMPR_EN_SHIFT)) & RTC_TAMPER_SCR_TMPR_EN_MASK)

#define RTC_TAMPER_SCR_TMPR_STS_MASK             (0xF00U)
#define RTC_TAMPER_SCR_TMPR_STS_SHIFT            (8U)
/*! TMPR_STS - Tamper Status Bit
 */
#define RTC_TAMPER_SCR_TMPR_STS(x)               (((uint16_t)(((uint16_t)(x)) << RTC_TAMPER_SCR_TMPR_STS_SHIFT)) & RTC_TAMPER_SCR_TMPR_STS_MASK)
/*! @} */

/*! @name FILTER01_CFG - RTC Tamper 0 1 Filter Configuration Register */
/*! @{ */

#define RTC_FILTER01_CFG_FIL_DUR1_MASK           (0xFU)
#define RTC_FILTER01_CFG_FIL_DUR1_SHIFT          (0U)
/*! FIL_DUR1 - Tamper Detect Bit 1 Filter Duration
 *  0b0000..Filtering operation disabled.
 */
#define RTC_FILTER01_CFG_FIL_DUR1(x)             (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_FIL_DUR1_SHIFT)) & RTC_FILTER01_CFG_FIL_DUR1_MASK)

#define RTC_FILTER01_CFG_CLK_SEL1_MASK           (0x70U)
#define RTC_FILTER01_CFG_CLK_SEL1_SHIFT          (4U)
/*! CLK_SEL1 - Tamper Filter 1 Clock Select
 *  0b000..32 kHz clock
 *  0b001..512 Hz clock
 *  0b010..128 Hz clock
 *  0b011..64 Hz clock
 *  0b100..16 Hz clock
 *  0b101..8 Hz clock
 *  0b110..4 Hz clock
 *  0b111..2 Hz clock
 */
#define RTC_FILTER01_CFG_CLK_SEL1(x)             (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_CLK_SEL1_SHIFT)) & RTC_FILTER01_CFG_CLK_SEL1_MASK)

#define RTC_FILTER01_CFG_POL1_MASK               (0x80U)
#define RTC_FILTER01_CFG_POL1_SHIFT              (7U)
/*! POL1 - Tamper Detect Input Bit 1 Polarity Control
 *  0b0..Tamper detect input bit 1 is active high.
 *  0b1..Tamper detect input bit 1 is active low.
 */
#define RTC_FILTER01_CFG_POL1(x)                 (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_POL1_SHIFT)) & RTC_FILTER01_CFG_POL1_MASK)

#define RTC_FILTER01_CFG_FIL_DUR0_MASK           (0xF00U)
#define RTC_FILTER01_CFG_FIL_DUR0_SHIFT          (8U)
/*! FIL_DUR0 - Tamper Detect Bit 0 Filter Duration
 *  0b0000..Filtering operation disabled.
 */
#define RTC_FILTER01_CFG_FIL_DUR0(x)             (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_FIL_DUR0_SHIFT)) & RTC_FILTER01_CFG_FIL_DUR0_MASK)

#define RTC_FILTER01_CFG_CLK_SEL0_MASK           (0x7000U)
#define RTC_FILTER01_CFG_CLK_SEL0_SHIFT          (12U)
/*! CLK_SEL0 - Tamper Filter 0 Clock Select
 *  0b000..32 kHz clock
 *  0b001..512 Hz clock
 *  0b010..128 Hz clock
 *  0b011..64 Hz clock
 *  0b100..16 Hz clock
 *  0b101..8 Hz clock
 *  0b110..4 Hz clock
 *  0b111..2 Hz clock
 */
#define RTC_FILTER01_CFG_CLK_SEL0(x)             (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_CLK_SEL0_SHIFT)) & RTC_FILTER01_CFG_CLK_SEL0_MASK)

#define RTC_FILTER01_CFG_POL0_MASK               (0x8000U)
#define RTC_FILTER01_CFG_POL0_SHIFT              (15U)
/*! POL0 - Tamper Detect Input Bit 0 Polarity Control
 *  0b0..Tamper detect input bit 0 is active high.
 *  0b1..Tamper detect input bit 0 is active low.
 */
#define RTC_FILTER01_CFG_POL0(x)                 (((uint16_t)(((uint16_t)(x)) << RTC_FILTER01_CFG_POL0_SHIFT)) & RTC_FILTER01_CFG_POL0_MASK)
/*! @} */

/*! @name FILTER2_CFG - RTC Tamper 2 Filter Configuration Register */
/*! @{ */

#define RTC_FILTER2_CFG_FIL_DUR2_MASK            (0xF00U)
#define RTC_FILTER2_CFG_FIL_DUR2_SHIFT           (8U)
/*! FIL_DUR2 - Tamper Detect Bit 2 Filter Duration
 *  0b0000..Filtering operation disabled.
 */
#define RTC_FILTER2_CFG_FIL_DUR2(x)              (((uint16_t)(((uint16_t)(x)) << RTC_FILTER2_CFG_FIL_DUR2_SHIFT)) & RTC_FILTER2_CFG_FIL_DUR2_MASK)

#define RTC_FILTER2_CFG_CLK_SEL2_MASK            (0x7000U)
#define RTC_FILTER2_CFG_CLK_SEL2_SHIFT           (12U)
/*! CLK_SEL2 - Tamper Filter 2 Clock Select
 *  0b000..32 kHz clock
 *  0b001..512 Hz clock
 *  0b010..128 Hz clock
 *  0b011..64 Hz clock
 *  0b100..16 Hz clock
 *  0b101..8 Hz clock
 *  0b110..4 Hz clock
 *  0b111..2 Hz clock
 */
#define RTC_FILTER2_CFG_CLK_SEL2(x)              (((uint16_t)(((uint16_t)(x)) << RTC_FILTER2_CFG_CLK_SEL2_SHIFT)) & RTC_FILTER2_CFG_CLK_SEL2_MASK)

#define RTC_FILTER2_CFG_POL2_MASK                (0x8000U)
#define RTC_FILTER2_CFG_POL2_SHIFT               (15U)
/*! POL2 - Tamper Detect Input Bit 2 Polarity Control
 *  0b0..Tamper detect input bit 2 is active high.
 *  0b1..Tamper detect input bit 2 is active low.
 */
#define RTC_FILTER2_CFG_POL2(x)                  (((uint16_t)(((uint16_t)(x)) << RTC_FILTER2_CFG_POL2_SHIFT)) & RTC_FILTER2_CFG_POL2_MASK)
/*! @} */

/*! @name CTRL2 - RTC Control 2 Register */
/*! @{ */

#define RTC_CTRL2_TAMP_CFG_OVER_MASK             (0x1U)
#define RTC_CTRL2_TAMP_CFG_OVER_SHIFT            (0U)
/*! TAMP_CFG_OVER - Tamper Configuration Over
 *  0b0..Tamper filter processing disabled.
 *  0b1..Tamper filter processing enabled. To enable the tamper feature, this bitfield should be set.
 */
#define RTC_CTRL2_TAMP_CFG_OVER(x)               (((uint16_t)(((uint16_t)(x)) << RTC_CTRL2_TAMP_CFG_OVER_SHIFT)) & RTC_CTRL2_TAMP_CFG_OVER_MASK)

#define RTC_CTRL2_WAKEUP_STATUS_MASK             (0x60U)
#define RTC_CTRL2_WAKEUP_STATUS_SHIFT            (5U)
/*! WAKEUP_STATUS - Wakeup Status
 *  0b00..The wakeup/hibernation pin is in HiZ mode.
 *  0b01..The wakeup/hibernation pin is at logic 0. MCU is in sleep mode.
 *  0b10..The wakeup/ hibernation pin is at logic 1. MCU is in sleep mode.
 *  0b11..Reserved
 */
#define RTC_CTRL2_WAKEUP_STATUS(x)               (((uint16_t)(((uint16_t)(x)) << RTC_CTRL2_WAKEUP_STATUS_SHIFT)) & RTC_CTRL2_WAKEUP_STATUS_MASK)

#define RTC_CTRL2_WAKEUP_MODE_MASK               (0x80U)
#define RTC_CTRL2_WAKEUP_MODE_SHIFT              (7U)
/*! WAKEUP_MODE - Wakeup Mode
 *  0b0..Tamper pin 0 is used as the tamper pin.
 *  0b1..Tamper pin 0 is used as a wakeup/hibernation pin.
 */
#define RTC_CTRL2_WAKEUP_MODE(x)                 (((uint16_t)(((uint16_t)(x)) << RTC_CTRL2_WAKEUP_MODE_SHIFT)) & RTC_CTRL2_WAKEUP_MODE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group RTC_Register_Masks */


/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x40050000u)
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
   -- SIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Peripheral_Access_Layer SIM Peripheral Access Layer
 * @{
 */

/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SOPT1;                             /**< System Options Register 1, offset: 0x0 */
  __IO uint32_t SOPT1_CFG;                         /**< SOPT1 Configuration Register, offset: 0x4 */
       uint8_t RESERVED_0[4092];
  __IO uint32_t CTRL_REG;                          /**< System Control Register, offset: 0x1004 */
       uint8_t RESERVED_1[28];
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
       uint8_t RESERVED_2[12];
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
       uint8_t RESERVED_3[4];
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
  __I  uint32_t UIDH;                              /**< Unique Identification Register High, offset: 0x1054 */
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid-Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_4[8];
  __IO uint32_t MISC_CTL;                          /**< Miscellaneous Control Register, offset: 0x106C */
} SIM_Type;

/* ----------------------------------------------------------------------------
   -- SIM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIM_Register_Masks SIM Register Masks
 * @{
 */

/*! @name SOPT1 - System Options Register 1 */
/*! @{ */

#define SIM_SOPT1_SRAMSIZE_MASK                  (0xF000U)
#define SIM_SOPT1_SRAMSIZE_SHIFT                 (12U)
/*! SRAMSIZE - Returns the size of the system RAM
 *  0b0101..16kB System RAM
 */
#define SIM_SOPT1_SRAMSIZE(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_SRAMSIZE_SHIFT)) & SIM_SOPT1_SRAMSIZE_MASK)

#define SIM_SOPT1_OSC32KSEL_MASK                 (0xC0000U)
#define SIM_SOPT1_OSC32KSEL_SHIFT                (18U)
/*! OSC32KSEL - 32K oscillator clock select
 *  0b00..OSC32KCLK
 *  0b01..ERCLK32K
 *  0b10..MCGIRCLK
 *  0b11..LPO
 */
#define SIM_SOPT1_OSC32KSEL(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_OSC32KSEL_SHIFT)) & SIM_SOPT1_OSC32KSEL_MASK)
/*! @} */

/*! @name SOPT1_CFG - SOPT1 Configuration Register */
/*! @{ */

#define SIM_SOPT1_CFG_LPTMR1SEL_MASK             (0x3U)
#define SIM_SOPT1_CFG_LPTMR1SEL_SHIFT            (0U)
/*! LPTMR1SEL - LP timer Channel1 Select
 *  0b00..Pad PTE4
 *  0b01..Pad PTF4
 *  0b10..Pad PTG1
 *  0b11..Reserved
 */
#define SIM_SOPT1_CFG_LPTMR1SEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_LPTMR1SEL_SHIFT)) & SIM_SOPT1_CFG_LPTMR1SEL_MASK)

#define SIM_SOPT1_CFG_LPTMR2SEL_MASK             (0xCU)
#define SIM_SOPT1_CFG_LPTMR2SEL_SHIFT            (2U)
/*! LPTMR2SEL - LP timer Channel2 Select
 *  0b00..Pad PTD6
 *  0b01..Pad PTF3
 *  0b10..Pad PTG5
 *  0b11..Reserved
 */
#define SIM_SOPT1_CFG_LPTMR2SEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_LPTMR2SEL_SHIFT)) & SIM_SOPT1_CFG_LPTMR2SEL_MASK)

#define SIM_SOPT1_CFG_LPTMR3SEL_MASK             (0x30U)
#define SIM_SOPT1_CFG_LPTMR3SEL_SHIFT            (4U)
/*! LPTMR3SEL - LP timer Channel3 Select
 *  0b00..Pad PTD5
 *  0b01..Pad PTG0
 *  0b10..Pad PTG6
 *  0b11..Reserved
 */
#define SIM_SOPT1_CFG_LPTMR3SEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_LPTMR3SEL_SHIFT)) & SIM_SOPT1_CFG_LPTMR3SEL_MASK)

#define SIM_SOPT1_CFG_CMPOLPTMR0SEL_MASK         (0x40U)
#define SIM_SOPT1_CFG_CMPOLPTMR0SEL_SHIFT        (6U)
/*! CMPOLPTMR0SEL - Comparator output selection for LPTMR channel0
 *  0b0..CMP[1] output selected as LPTMR input[0]
 *  0b1..CMP[0] output selected as LPTMR input[0]
 */
#define SIM_SOPT1_CFG_CMPOLPTMR0SEL(x)           (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_CMPOLPTMR0SEL_SHIFT)) & SIM_SOPT1_CFG_CMPOLPTMR0SEL_MASK)

#define SIM_SOPT1_CFG_RAMSBDIS_MASK              (0x100U)
#define SIM_SOPT1_CFG_RAMSBDIS_SHIFT             (8U)
/*! RAMSBDIS
 *  0b0..Source bias of System SRAM enabled during VLPR and VLPW modes.
 *  0b1..Source bias of System SRAM disabled during VLPR and VLPW modes.
 */
#define SIM_SOPT1_CFG_RAMSBDIS(x)                (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_RAMSBDIS_SHIFT)) & SIM_SOPT1_CFG_RAMSBDIS_MASK)

#define SIM_SOPT1_CFG_RAMBPEN_MASK               (0x200U)
#define SIM_SOPT1_CFG_RAMBPEN_SHIFT              (9U)
/*! RAMBPEN - RAM Bitline Precharge Enable
 *  0b0..Bitline precharge of system SRAM disabled during VLPR and VLPW modes.
 *  0b1..Bitline precharge of system SRAM enabled during VLPR and VLPW modes.
 */
#define SIM_SOPT1_CFG_RAMBPEN(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SOPT1_CFG_RAMBPEN_SHIFT)) & SIM_SOPT1_CFG_RAMBPEN_MASK)
/*! @} */

/*! @name CTRL_REG - System Control Register */
/*! @{ */

#define SIM_CTRL_REG_NMIDIS_MASK                 (0x1U)
#define SIM_CTRL_REG_NMIDIS_SHIFT                (0U)
/*! NMIDIS - NMI Disable
 *  0b0..NMI enabled
 *  0b1..NMI disabled
 */
#define SIM_CTRL_REG_NMIDIS(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_CTRL_REG_NMIDIS_SHIFT)) & SIM_CTRL_REG_NMIDIS_MASK)

#define SIM_CTRL_REG_PLL_VLP_EN_MASK             (0x2U)
#define SIM_CTRL_REG_PLL_VLP_EN_SHIFT            (1U)
/*! PLL_VLP_EN - PLL VLP Enable
 */
#define SIM_CTRL_REG_PLL_VLP_EN(x)               (((uint32_t)(((uint32_t)(x)) << SIM_CTRL_REG_PLL_VLP_EN_SHIFT)) & SIM_CTRL_REG_PLL_VLP_EN_MASK)

#define SIM_CTRL_REG_PTC2_HD_EN_MASK             (0x4U)
#define SIM_CTRL_REG_PTC2_HD_EN_SHIFT            (2U)
/*! PTC2_HD_EN - PTC2 HighDrive Enable
 */
#define SIM_CTRL_REG_PTC2_HD_EN(x)               (((uint32_t)(((uint32_t)(x)) << SIM_CTRL_REG_PTC2_HD_EN_SHIFT)) & SIM_CTRL_REG_PTC2_HD_EN_MASK)

#define SIM_CTRL_REG_SAR_TRG_CLK_SEL_MASK        (0x18U)
#define SIM_CTRL_REG_SAR_TRG_CLK_SEL_SHIFT       (3U)
/*! SAR_TRG_CLK_SEL - SAR ADC Trigger Clk Select
 *  0b00..Bus Clock (During Low Power Modes such as stop, the Bus clock is not available for conversion and should
 *        not be selected in case a conversion needs to be performed while in stop)
 *  0b01..ADC asynchronous Clock
 *  0b10..ERCLK32K
 *  0b11..OSCCLK
 */
#define SIM_CTRL_REG_SAR_TRG_CLK_SEL(x)          (((uint32_t)(((uint32_t)(x)) << SIM_CTRL_REG_SAR_TRG_CLK_SEL_SHIFT)) & SIM_CTRL_REG_SAR_TRG_CLK_SEL_MASK)

#define SIM_CTRL_REG_CLKOUTSEL_MASK              (0xE0U)
#define SIM_CTRL_REG_CLKOUTSEL_SHIFT             (5U)
/*! CLKOUTSEL - Clock out Select
 *  0b000..Disabled
 *  0b001..Gated Core Clk
 *  0b010..Bus/Flash Clk
 *  0b011..LPO clock from PMC
 *  0b100..IRC clock from MCG
 *  0b101..Muxed 32Khz source (please refer SOPT1[19:18] for possible options)
 *  0b110..MHz Oscillator external reference clock
 *  0b111..PLL clock output from MCG
 */
#define SIM_CTRL_REG_CLKOUTSEL(x)                (((uint32_t)(((uint32_t)(x)) << SIM_CTRL_REG_CLKOUTSEL_SHIFT)) & SIM_CTRL_REG_CLKOUTSEL_MASK)
/*! @} */

/*! @name SDID - System Device Identification Register */
/*! @{ */

#define SIM_SDID_PINID_MASK                      (0xFU)
#define SIM_SDID_PINID_SHIFT                     (0U)
/*! PINID - Pincount identification
 *  0b0011..44-pin
 *  0b0100..Reserved
 *  0b0101..64-pin
 *  0b0110..Reserved
 *  0b0111..Reserved
 *  0b1000..100-pin
 *  0b1001..Reserved
 *  0b1010..Reserved
 *  0b1011..Reserved
 *  0b1100..Reserved
 *  0b1101..Reserved
 *  0b1110..Reserved
 *  0b1111..Reserved
 */
#define SIM_SDID_PINID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_PINID_SHIFT)) & SIM_SDID_PINID_MASK)

#define SIM_SDID_DIEID_MASK                      (0xF0U)
#define SIM_SDID_DIEID_SHIFT                     (4U)
/*! DIEID - Die ID
 *  0b0000..First cut
 */
#define SIM_SDID_DIEID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_DIEID_SHIFT)) & SIM_SDID_DIEID_MASK)

#define SIM_SDID_REVID_MASK                      (0xF00U)
#define SIM_SDID_REVID_SHIFT                     (8U)
/*! REVID - Revision ID
 *  0b0010..Third Cut
 */
#define SIM_SDID_REVID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_REVID_SHIFT)) & SIM_SDID_REVID_MASK)

#define SIM_SDID_SRAMSIZE_MASK                   (0xF000U)
#define SIM_SDID_SRAMSIZE_SHIFT                  (12U)
/*! SRAMSIZE - SRAM Size
 *  0b0101..16kB SRAM
 */
#define SIM_SDID_SRAMSIZE(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SRAMSIZE_SHIFT)) & SIM_SDID_SRAMSIZE_MASK)

#define SIM_SDID_ATTR_MASK                       (0xF0000U)
#define SIM_SDID_ATTR_SHIFT                      (16U)
/*! ATTR - Attribute ID
 *  0b0000..M0+ core
 */
#define SIM_SDID_ATTR(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SDID_ATTR_SHIFT)) & SIM_SDID_ATTR_MASK)

#define SIM_SDID_SERIESID_MASK                   (0xF00000U)
#define SIM_SDID_SERIESID_SHIFT                  (20U)
/*! SERIESID - Series ID
 *  0b0011..Metering Series
 */
#define SIM_SDID_SERIESID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SERIESID_SHIFT)) & SIM_SDID_SERIESID_MASK)

#define SIM_SDID_SUBFAMID_MASK                   (0xF000000U)
#define SIM_SDID_SUBFAMID_SHIFT                  (24U)
/*! SUBFAMID - Sub-Family ID
 *  0b0010..Device derivatives with 2 AFE enabled (AFE Channels 0 and 2 are enabled)
 *  0b0011..Device derivatives with 3 AFE enabled (AFE Channels 0, 1, and 2 are enabled)
 *  0b0100..Device derivatives with 4 AFE enabled
 */
#define SIM_SDID_SUBFAMID(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SDID_SUBFAMID_SHIFT)) & SIM_SDID_SUBFAMID_MASK)

#define SIM_SDID_FAMID_MASK                      (0xF0000000U)
#define SIM_SDID_FAMID_SHIFT                     (28U)
/*! FAMID - Metering family ID
 *  0b0001..Device derivatives without LCD
 *  0b0011..Device derivatives with LCD
 */
#define SIM_SDID_FAMID(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SDID_FAMID_SHIFT)) & SIM_SDID_FAMID_MASK)
/*! @} */

/*! @name SCGC4 - System Clock Gating Control Register 4 */
/*! @{ */

#define SIM_SCGC4_EWM_MASK                       (0x2U)
#define SIM_SCGC4_EWM_SHIFT                      (1U)
/*! EWM - External Watchdog Monitor Clock gate control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_EWM(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_EWM_SHIFT)) & SIM_SCGC4_EWM_MASK)

#define SIM_SCGC4_MCG_MASK                       (0x10U)
#define SIM_SCGC4_MCG_SHIFT                      (4U)
/*! MCG - MCG clock gate control.
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_MCG(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_MCG_SHIFT)) & SIM_SCGC4_MCG_MASK)

#define SIM_SCGC4_OSC_MASK                       (0x40U)
#define SIM_SCGC4_OSC_SHIFT                      (6U)
/*! OSC - Oscillator (Mhz) Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_OSC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_OSC_SHIFT)) & SIM_SCGC4_OSC_MASK)

#define SIM_SCGC4_I2C0_MASK                      (0x80U)
#define SIM_SCGC4_I2C0_SHIFT                     (7U)
/*! I2C0 - I2C0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_I2C0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C0_SHIFT)) & SIM_SCGC4_I2C0_MASK)

#define SIM_SCGC4_I2C1_MASK                      (0x100U)
#define SIM_SCGC4_I2C1_SHIFT                     (8U)
/*! I2C1 - I2C1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_I2C1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_I2C1_SHIFT)) & SIM_SCGC4_I2C1_MASK)

#define SIM_SCGC4_UART0_MASK                     (0x400U)
#define SIM_SCGC4_UART0_SHIFT                    (10U)
/*! UART0 - UART0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_UART0(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART0_SHIFT)) & SIM_SCGC4_UART0_MASK)

#define SIM_SCGC4_UART1_MASK                     (0x800U)
#define SIM_SCGC4_UART1_SHIFT                    (11U)
/*! UART1 - UART1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_UART1(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART1_SHIFT)) & SIM_SCGC4_UART1_MASK)

#define SIM_SCGC4_UART2_MASK                     (0x1000U)
#define SIM_SCGC4_UART2_SHIFT                    (12U)
/*! UART2 - UART2 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_UART2(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART2_SHIFT)) & SIM_SCGC4_UART2_MASK)

#define SIM_SCGC4_UART3_MASK                     (0x2000U)
#define SIM_SCGC4_UART3_SHIFT                    (13U)
/*! UART3 - UART3 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_UART3(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_UART3_SHIFT)) & SIM_SCGC4_UART3_MASK)

#define SIM_SCGC4_VREF_MASK                      (0x8000U)
#define SIM_SCGC4_VREF_SHIFT                     (15U)
/*! VREF - VREF Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_VREF(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_VREF_SHIFT)) & SIM_SCGC4_VREF_MASK)

#define SIM_SCGC4_CMP0_MASK                      (0x40000U)
#define SIM_SCGC4_CMP0_SHIFT                     (18U)
/*! CMP0 - High Speed Comparator0 Clock Gate Control.
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_CMP0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_CMP0_SHIFT)) & SIM_SCGC4_CMP0_MASK)

#define SIM_SCGC4_CMP1_MASK                      (0x80000U)
#define SIM_SCGC4_CMP1_SHIFT                     (19U)
/*! CMP1 - High Speed Comparator1 Clock Gate Control.
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_CMP1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_CMP1_SHIFT)) & SIM_SCGC4_CMP1_MASK)

#define SIM_SCGC4_SPI0_MASK                      (0x200000U)
#define SIM_SCGC4_SPI0_SHIFT                     (21U)
/*! SPI0 - SPI0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_SPI0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_SPI0_SHIFT)) & SIM_SCGC4_SPI0_MASK)

#define SIM_SCGC4_SPI1_MASK                      (0x400000U)
#define SIM_SCGC4_SPI1_SHIFT                     (22U)
/*! SPI1 - SPI1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC4_SPI1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC4_SPI1_SHIFT)) & SIM_SCGC4_SPI1_MASK)
/*! @} */

/*! @name SCGC5 - System Clock Gating Control Register 5 */
/*! @{ */

#define SIM_SCGC5_SLCD_MASK                      (0x8U)
#define SIM_SCGC5_SLCD_SHIFT                     (3U)
/*! SLCD - Segmented LCD Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_SLCD(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_SLCD_SHIFT)) & SIM_SCGC5_SLCD_MASK)

#define SIM_SCGC5_PORTA_MASK                     (0x40U)
#define SIM_SCGC5_PORTA_SHIFT                    (6U)
/*! PORTA - PCTLA Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTA(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTA_SHIFT)) & SIM_SCGC5_PORTA_MASK)

#define SIM_SCGC5_PORTB_MASK                     (0x80U)
#define SIM_SCGC5_PORTB_SHIFT                    (7U)
/*! PORTB - PCTLB Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTB(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTB_SHIFT)) & SIM_SCGC5_PORTB_MASK)

#define SIM_SCGC5_PORTC_MASK                     (0x100U)
#define SIM_SCGC5_PORTC_SHIFT                    (8U)
/*! PORTC - PCTLC Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTC(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTC_SHIFT)) & SIM_SCGC5_PORTC_MASK)

#define SIM_SCGC5_PORTD_MASK                     (0x200U)
#define SIM_SCGC5_PORTD_SHIFT                    (9U)
/*! PORTD - PCTLD Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTD(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTD_SHIFT)) & SIM_SCGC5_PORTD_MASK)

#define SIM_SCGC5_PORTE_MASK                     (0x400U)
#define SIM_SCGC5_PORTE_SHIFT                    (10U)
/*! PORTE - PCTLE Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTE(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTE_SHIFT)) & SIM_SCGC5_PORTE_MASK)

#define SIM_SCGC5_PORTF_MASK                     (0x800U)
#define SIM_SCGC5_PORTF_SHIFT                    (11U)
/*! PORTF - PCTLF Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTF(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTF_SHIFT)) & SIM_SCGC5_PORTF_MASK)

#define SIM_SCGC5_PORTG_MASK                     (0x1000U)
#define SIM_SCGC5_PORTG_SHIFT                    (12U)
/*! PORTG - PCTLG Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTG(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTG_SHIFT)) & SIM_SCGC5_PORTG_MASK)

#define SIM_SCGC5_PORTH_MASK                     (0x2000U)
#define SIM_SCGC5_PORTH_SHIFT                    (13U)
/*! PORTH - PCTLH Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTH(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTH_SHIFT)) & SIM_SCGC5_PORTH_MASK)

#define SIM_SCGC5_PORTI_MASK                     (0x4000U)
#define SIM_SCGC5_PORTI_SHIFT                    (14U)
/*! PORTI - PCTLI Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_PORTI(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_PORTI_SHIFT)) & SIM_SCGC5_PORTI_MASK)

#define SIM_SCGC5_IRTC_MASK                      (0x10000U)
#define SIM_SCGC5_IRTC_SHIFT                     (16U)
/*! IRTC - IRTC Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_IRTC(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_IRTC_SHIFT)) & SIM_SCGC5_IRTC_MASK)

#define SIM_SCGC5_IRTCREGFILE_MASK               (0x20000U)
#define SIM_SCGC5_IRTCREGFILE_SHIFT              (17U)
/*! IRTCREGFILE - IRTC_REG_FILE Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_IRTCREGFILE(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_IRTCREGFILE_SHIFT)) & SIM_SCGC5_IRTCREGFILE_MASK)

#define SIM_SCGC5_WDOG_MASK                      (0x80000U)
#define SIM_SCGC5_WDOG_SHIFT                     (19U)
/*! WDOG - Watchdog Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_WDOG(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_WDOG_SHIFT)) & SIM_SCGC5_WDOG_MASK)

#define SIM_SCGC5_XBAR_MASK                      (0x200000U)
#define SIM_SCGC5_XBAR_SHIFT                     (21U)
/*! XBAR - Peripheral Crossbar Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_XBAR(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_XBAR_SHIFT)) & SIM_SCGC5_XBAR_MASK)

#define SIM_SCGC5_TMR0_MASK                      (0x800000U)
#define SIM_SCGC5_TMR0_SHIFT                     (23U)
/*! TMR0 - Quadtimer0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_TMR0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_TMR0_SHIFT)) & SIM_SCGC5_TMR0_MASK)

#define SIM_SCGC5_TMR1_MASK                      (0x1000000U)
#define SIM_SCGC5_TMR1_SHIFT                     (24U)
/*! TMR1 - Quadtimer1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_TMR1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_TMR1_SHIFT)) & SIM_SCGC5_TMR1_MASK)

#define SIM_SCGC5_TMR2_MASK                      (0x2000000U)
#define SIM_SCGC5_TMR2_SHIFT                     (25U)
/*! TMR2 - Quadtimer2 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_TMR2(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_TMR2_SHIFT)) & SIM_SCGC5_TMR2_MASK)

#define SIM_SCGC5_TMR3_MASK                      (0x4000000U)
#define SIM_SCGC5_TMR3_SHIFT                     (26U)
/*! TMR3 - Quadtimer3 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC5_TMR3(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC5_TMR3_SHIFT)) & SIM_SCGC5_TMR3_MASK)
/*! @} */

/*! @name SCGC6 - System Clock Gating Control Register 6 */
/*! @{ */

#define SIM_SCGC6_FTFA_MASK                      (0x1U)
#define SIM_SCGC6_FTFA_SHIFT                     (0U)
/*! FTFA - FTFA Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_FTFA(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_FTFA_SHIFT)) & SIM_SCGC6_FTFA_MASK)

#define SIM_SCGC6_DMAMUX0_MASK                   (0x2U)
#define SIM_SCGC6_DMAMUX0_SHIFT                  (1U)
/*! DMAMUX0 - DMA MUX0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DMAMUX0(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX0_SHIFT)) & SIM_SCGC6_DMAMUX0_MASK)

#define SIM_SCGC6_DMAMUX1_MASK                   (0x4U)
#define SIM_SCGC6_DMAMUX1_SHIFT                  (2U)
/*! DMAMUX1 - DMA MUX1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DMAMUX1(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX1_SHIFT)) & SIM_SCGC6_DMAMUX1_MASK)

#define SIM_SCGC6_DMAMUX2_MASK                   (0x8U)
#define SIM_SCGC6_DMAMUX2_SHIFT                  (3U)
/*! DMAMUX2 - DMA MUX2 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DMAMUX2(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX2_SHIFT)) & SIM_SCGC6_DMAMUX2_MASK)

#define SIM_SCGC6_DMAMUX3_MASK                   (0x10U)
#define SIM_SCGC6_DMAMUX3_SHIFT                  (4U)
/*! DMAMUX3 - DMA MUX3 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_DMAMUX3(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_DMAMUX3_SHIFT)) & SIM_SCGC6_DMAMUX3_MASK)

#define SIM_SCGC6_RNGA_MASK                      (0x200U)
#define SIM_SCGC6_RNGA_SHIFT                     (9U)
/*! RNGA - RNGA Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_RNGA(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_RNGA_SHIFT)) & SIM_SCGC6_RNGA_MASK)

#define SIM_SCGC6_ADC_MASK                       (0x800U)
#define SIM_SCGC6_ADC_SHIFT                      (11U)
/*! ADC - SAR ADC Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_ADC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_ADC_SHIFT)) & SIM_SCGC6_ADC_MASK)

#define SIM_SCGC6_PIT0_MASK                      (0x2000U)
#define SIM_SCGC6_PIT0_SHIFT                     (13U)
/*! PIT0 - PIT0 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_PIT0(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PIT0_SHIFT)) & SIM_SCGC6_PIT0_MASK)

#define SIM_SCGC6_PIT1_MASK                      (0x4000U)
#define SIM_SCGC6_PIT1_SHIFT                     (14U)
/*! PIT1 - PIT1 Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_PIT1(x)                        (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_PIT1_SHIFT)) & SIM_SCGC6_PIT1_MASK)

#define SIM_SCGC6_AFE_MASK                       (0x10000U)
#define SIM_SCGC6_AFE_SHIFT                      (16U)
/*! AFE - AFE Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_AFE(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_AFE_SHIFT)) & SIM_SCGC6_AFE_MASK)

#define SIM_SCGC6_CRC_MASK                       (0x100000U)
#define SIM_SCGC6_CRC_SHIFT                      (20U)
/*! CRC - Programmable CRC Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_CRC(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_CRC_SHIFT)) & SIM_SCGC6_CRC_MASK)

#define SIM_SCGC6_LPTMR_MASK                     (0x10000000U)
#define SIM_SCGC6_LPTMR_SHIFT                    (28U)
/*! LPTMR - LPTMR Clock Gate Control
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC6_LPTMR(x)                       (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_LPTMR_SHIFT)) & SIM_SCGC6_LPTMR_MASK)

#define SIM_SCGC6_SIM_LP_MASK                    (0x40000000U)
#define SIM_SCGC6_SIM_LP_SHIFT                   (30U)
/*! SIM_LP - SIM_LP Clock Gate Control
 *  0b1..Clock is enabled
 *  0b0..Clock is disabled
 */
#define SIM_SCGC6_SIM_LP(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_SIM_LP_SHIFT)) & SIM_SCGC6_SIM_LP_MASK)

#define SIM_SCGC6_SIM_HP_MASK                    (0x80000000U)
#define SIM_SCGC6_SIM_HP_SHIFT                   (31U)
/*! SIM_HP - SIM_HP Clock Gate Control
 *  0b1..Clock is always enabled to SIM
 */
#define SIM_SCGC6_SIM_HP(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_SCGC6_SIM_HP_SHIFT)) & SIM_SCGC6_SIM_HP_MASK)
/*! @} */

/*! @name SCGC7 - System Clock Gating Control Register 7 */
/*! @{ */

#define SIM_SCGC7_MPU_MASK                       (0x1U)
#define SIM_SCGC7_MPU_SHIFT                      (0U)
/*! MPU - MPU Clock Gate control.
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC7_MPU(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_MPU_SHIFT)) & SIM_SCGC7_MPU_MASK)

#define SIM_SCGC7_DMA_MASK                       (0x2U)
#define SIM_SCGC7_DMA_SHIFT                      (1U)
/*! DMA - DMA Clock Gate control.
 *  0b0..Clock disabled
 *  0b1..Clock enabled
 */
#define SIM_SCGC7_DMA(x)                         (((uint32_t)(((uint32_t)(x)) << SIM_SCGC7_DMA_SHIFT)) & SIM_SCGC7_DMA_MASK)
/*! @} */

/*! @name CLKDIV1 - System Clock Divider Register 1 */
/*! @{ */

#define SIM_CLKDIV1_SYSCLKMODE_MASK              (0x8000000U)
#define SIM_CLKDIV1_SYSCLKMODE_SHIFT             (27U)
/*! SYSCLKMODE - System Clock Mode
 *  0b0..1:1:1
 *  0b1..2:1:1
 */
#define SIM_CLKDIV1_SYSCLKMODE(x)                (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_SYSCLKMODE_SHIFT)) & SIM_CLKDIV1_SYSCLKMODE_MASK)

#define SIM_CLKDIV1_SYSDIV_MASK                  (0xF0000000U)
#define SIM_CLKDIV1_SYSDIV_SHIFT                 (28U)
/*! SYSDIV - System Clock divider
 *  0b0000..Divide by 1
 *  0b0001..Divide by 2
 *  0b0010..Divide by 3
 *  0b0011..Divide by 4 and so on..... If FOPT[0] is 0, the divider is set to div-by-8 after system reset is
 *          deasserted (after completion of system initialization sequence)
 */
#define SIM_CLKDIV1_SYSDIV(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_CLKDIV1_SYSDIV_SHIFT)) & SIM_CLKDIV1_SYSDIV_MASK)
/*! @} */

/*! @name FCFG1 - Flash Configuration Register 1 */
/*! @{ */

#define SIM_FCFG1_FLASHDIS_MASK                  (0x1U)
#define SIM_FCFG1_FLASHDIS_SHIFT                 (0U)
/*! FLASHDIS - Flash Disable
 *  0b0..Flash is enabled
 *  0b1..Flash is disabled
 */
#define SIM_FCFG1_FLASHDIS(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDIS_SHIFT)) & SIM_FCFG1_FLASHDIS_MASK)

#define SIM_FCFG1_FLASHDOZE_MASK                 (0x2U)
#define SIM_FCFG1_FLASHDOZE_SHIFT                (1U)
/*! FLASHDOZE - Flash Doze
 *  0b0..Flash remains enabled during Wait mode
 *  0b1..Flash is disabled for the duration of Wait mode
 */
#define SIM_FCFG1_FLASHDOZE(x)                   (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_FLASHDOZE_SHIFT)) & SIM_FCFG1_FLASHDOZE_MASK)

#define SIM_FCFG1_PFSIZE_MASK                    (0xF000000U)
#define SIM_FCFG1_PFSIZE_SHIFT                   (24U)
/*! PFSIZE - Program flash size
 *  0b0000..Reserved
 *  0b0001..Reserved
 *  0b0011..Reserved
 *  0b0100..Reserved
 *  0b0101..64 KB of program flash memory, 2 KB protection region
 *  0b0110..Reserved
 *  0b0111..128 KB of program flash memory, 4 KB protection region
 *  0b1000..Reserved
 *  0b1001..Reserved
 *  0b1111..(Default)
 */
#define SIM_FCFG1_PFSIZE(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_FCFG1_PFSIZE_SHIFT)) & SIM_FCFG1_PFSIZE_MASK)
/*! @} */

/*! @name FCFG2 - Flash Configuration Register 2 */
/*! @{ */

#define SIM_FCFG2_MAXADDR_MASK                   (0x7F000000U)
#define SIM_FCFG2_MAXADDR_SHIFT                  (24U)
/*! MAXADDR - Max address block
 */
#define SIM_FCFG2_MAXADDR(x)                     (((uint32_t)(((uint32_t)(x)) << SIM_FCFG2_MAXADDR_SHIFT)) & SIM_FCFG2_MAXADDR_MASK)
/*! @} */

/*! @name UIDH - Unique Identification Register High */
/*! @{ */

#define SIM_UIDH_UID127_96_MASK                  (0xFFFFFFFFU)
#define SIM_UIDH_UID127_96_SHIFT                 (0U)
/*! UID127_96 - Unique Identification UID[127:96]
 */
#define SIM_UIDH_UID127_96(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_UIDH_UID127_96_SHIFT)) & SIM_UIDH_UID127_96_MASK)
/*! @} */

/*! @name UIDMH - Unique Identification Register Mid-High */
/*! @{ */

#define SIM_UIDMH_UID95_64_MASK                  (0xFFFFFFFFU)
#define SIM_UIDMH_UID95_64_SHIFT                 (0U)
/*! UID95_64 - Unique Identification UID[95:64]
 */
#define SIM_UIDMH_UID95_64(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_UIDMH_UID95_64_SHIFT)) & SIM_UIDMH_UID95_64_MASK)
/*! @} */

/*! @name UIDML - Unique Identification Register Mid-Low */
/*! @{ */

#define SIM_UIDML_UID63_32_MASK                  (0xFFFFFFFFU)
#define SIM_UIDML_UID63_32_SHIFT                 (0U)
/*! UID63_32 - Unique Identification UID[63:32]
 */
#define SIM_UIDML_UID63_32(x)                    (((uint32_t)(((uint32_t)(x)) << SIM_UIDML_UID63_32_SHIFT)) & SIM_UIDML_UID63_32_MASK)
/*! @} */

/*! @name UIDL - Unique Identification Register Low */
/*! @{ */

#define SIM_UIDL_UID31_0_MASK                    (0xFFFFFFFFU)
#define SIM_UIDL_UID31_0_SHIFT                   (0U)
/*! UID31_0 - Unique Identification UID[31:0]
 */
#define SIM_UIDL_UID31_0(x)                      (((uint32_t)(((uint32_t)(x)) << SIM_UIDL_UID31_0_SHIFT)) & SIM_UIDL_UID31_0_MASK)
/*! @} */

/*! @name MISC_CTL - Miscellaneous Control Register */
/*! @{ */

#define SIM_MISC_CTL_XBARAFEMODOUTSEL_MASK       (0x3U)
#define SIM_MISC_CTL_XBARAFEMODOUTSEL_SHIFT      (0U)
/*! XBARAFEMODOUTSEL - XBAR AFE Modulator Output Select
 *  0b00..Sigma Delta Modulator 0 data output
 *  0b01..Sigma Delta Modulator 1 data output
 *  0b10..Sigma Delta Modulator 2 data output
 *  0b11..Sigma Delta Modulator 3 data output
 */
#define SIM_MISC_CTL_XBARAFEMODOUTSEL(x)         (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_XBARAFEMODOUTSEL_SHIFT)) & SIM_MISC_CTL_XBARAFEMODOUTSEL_MASK)

#define SIM_MISC_CTL_DMADONESEL_MASK             (0xCU)
#define SIM_MISC_CTL_DMADONESEL_SHIFT            (2U)
/*! DMADONESEL - DMA Done select
 *  0b00..DMA0
 *  0b01..DMA1
 *  0b10..DMA2
 *  0b11..DMA3
 */
#define SIM_MISC_CTL_DMADONESEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_DMADONESEL_SHIFT)) & SIM_MISC_CTL_DMADONESEL_MASK)

#define SIM_MISC_CTL_AFECLKSEL_MASK              (0x30U)
#define SIM_MISC_CTL_AFECLKSEL_SHIFT             (4U)
/*! AFECLKSEL - AFE Clock Source Select
 *  0b00..MCG PLL Clock selected
 *  0b01..MCG FLL Clock selected
 *  0b10..OSC Clock selected
 *  0b11..Disabled
 */
#define SIM_MISC_CTL_AFECLKSEL(x)                (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_AFECLKSEL_SHIFT)) & SIM_MISC_CTL_AFECLKSEL_MASK)

#define SIM_MISC_CTL_AFECLKPADDIR_MASK           (0x40U)
#define SIM_MISC_CTL_AFECLKPADDIR_SHIFT          (6U)
/*! AFECLKPADDIR - AFE Clock Pad Direction
 *  0b0..AFE CLK PAD is input
 *  0b1..AFE CLK PAD is output
 */
#define SIM_MISC_CTL_AFECLKPADDIR(x)             (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_AFECLKPADDIR_SHIFT)) & SIM_MISC_CTL_AFECLKPADDIR_MASK)

#define SIM_MISC_CTL_UARTMODTYPE_MASK            (0x80U)
#define SIM_MISC_CTL_UARTMODTYPE_SHIFT           (7U)
/*! UARTMODTYPE - UART Modulation Type
 *  0b0..TypeA (ORed) Modulation selected for IRDA
 *  0b1..TypeB (ANDed) Modulation selected for IRDA
 */
#define SIM_MISC_CTL_UARTMODTYPE(x)              (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_UARTMODTYPE_SHIFT)) & SIM_MISC_CTL_UARTMODTYPE_MASK)

#define SIM_MISC_CTL_UART0IRSEL_MASK             (0x100U)
#define SIM_MISC_CTL_UART0IRSEL_SHIFT            (8U)
/*! UART0IRSEL - UART0 IRDA Select
 *  0b0..Pad RX input (PTD[0] or PTF[3], as selected in Pinmux control) selected for RX input of UART0 and UART0 TX signal is not used for modulation
 *  0b1..UART0 selected for IRDA modulation. UART0 TX modulated by XBAR_OUT[14] and UART0 RX input connected to XBAR_OUT[13]
 */
#define SIM_MISC_CTL_UART0IRSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_UART0IRSEL_SHIFT)) & SIM_MISC_CTL_UART0IRSEL_MASK)

#define SIM_MISC_CTL_UART1IRSEL_MASK             (0x200U)
#define SIM_MISC_CTL_UART1IRSEL_SHIFT            (9U)
/*! UART1IRSEL - UART1 IRDA Select
 *  0b0..Pad RX input (PTD[2] or PTI[0], as selected in Pinmux control) selected for RX input of UART1 and UART1 TX signal is not used for modulation
 *  0b1..UART1 selected for IRDA modulation. UART1 TX modulated by XBAR_OUT[14] and UART1 RX input connected to XBAR_OUT[13]
 */
#define SIM_MISC_CTL_UART1IRSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_UART1IRSEL_SHIFT)) & SIM_MISC_CTL_UART1IRSEL_MASK)

#define SIM_MISC_CTL_UART2IRSEL_MASK             (0x400U)
#define SIM_MISC_CTL_UART2IRSEL_SHIFT            (10U)
/*! UART2IRSEL - UART2 IRDA Select
 *  0b0..Pad RX input PTE[6] selected for RX input of UART2 and UART2 TX signal is not used for modulation
 *  0b1..UART2 selected for IRDA modulation. UART2 TX modulated by XBAR_OUT[14] and UART2 RX input connected to XBAR_OUT[13].
 */
#define SIM_MISC_CTL_UART2IRSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_UART2IRSEL_SHIFT)) & SIM_MISC_CTL_UART2IRSEL_MASK)

#define SIM_MISC_CTL_UART3IRSEL_MASK             (0x800U)
#define SIM_MISC_CTL_UART3IRSEL_SHIFT            (11U)
/*! UART3IRSEL - UART3 IRDA Select
 *  0b0..Pad RX input (PTC[3] or PTD[7], as selected in Pinmux control) selected for RX input of UART3 and UART3 TX signal is not used for modulation
 *  0b1..UART3 selected for IRDA modulation. UART3 TX modulated by XBAR_OUT[14] and UART3 RX input connected to XBAR_OUT[13].
 */
#define SIM_MISC_CTL_UART3IRSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_UART3IRSEL_SHIFT)) & SIM_MISC_CTL_UART3IRSEL_MASK)

#define SIM_MISC_CTL_XBARPITOUTSEL_MASK          (0x3000U)
#define SIM_MISC_CTL_XBARPITOUTSEL_SHIFT         (12U)
/*! XBARPITOUTSEL - XBAR PIT Output select
 *  0b00..PIT0[0] (default)
 *  0b01..PIT0[1]
 *  0b10..PIT1[0]
 *  0b11..PIT1[1]
 */
#define SIM_MISC_CTL_XBARPITOUTSEL(x)            (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_XBARPITOUTSEL_SHIFT)) & SIM_MISC_CTL_XBARPITOUTSEL_MASK)

#define SIM_MISC_CTL_EWMINSEL_MASK               (0x4000U)
#define SIM_MISC_CTL_EWMINSEL_SHIFT              (14U)
/*! EWMINSEL - External Watchdog Monitor Input Select
 *  0b0..Input from PAD (PTE[2] or PTE[4] as selected from Pinmux control )
 *  0b1..Peripheral Crossbar (XBAR) Output[32]
 */
#define SIM_MISC_CTL_EWMINSEL(x)                 (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_EWMINSEL_SHIFT)) & SIM_MISC_CTL_EWMINSEL_MASK)

#define SIM_MISC_CTL_TMR0PLLCLKSEL_MASK          (0x8000U)
#define SIM_MISC_CTL_TMR0PLLCLKSEL_SHIFT         (15U)
/*! TMR0PLLCLKSEL - Timer CH0 PLL clock select
 *  0b0..Selects Bus Clock as source for the Timer CH0
 *  0b1..Selects the PLL_AFE clock as the source for Timer CH0. The PLL_AFE clock source is itself selected using the MISC_CTL[5:4]
 */
#define SIM_MISC_CTL_TMR0PLLCLKSEL(x)            (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR0PLLCLKSEL_SHIFT)) & SIM_MISC_CTL_TMR0PLLCLKSEL_MASK)

#define SIM_MISC_CTL_TMR0SCSSEL_MASK             (0x10000U)
#define SIM_MISC_CTL_TMR0SCSSEL_SHIFT            (16U)
/*! TMR0SCSSEL - Quadtimer Channel0 Secondary Count Source Select
 *  0b0..Pad PTF1 or PTD5, depending upon PCTL configuration.
 *  0b1..Peripheral Crossbar (XBAR) Output[5]
 */
#define SIM_MISC_CTL_TMR0SCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR0SCSSEL_SHIFT)) & SIM_MISC_CTL_TMR0SCSSEL_MASK)

#define SIM_MISC_CTL_TMR1SCSSEL_MASK             (0x20000U)
#define SIM_MISC_CTL_TMR1SCSSEL_SHIFT            (17U)
/*! TMR1SCSSEL - Quadtimer Channel1 Secondary Count Source Select
 *  0b0..Pad PTG0 or PTC6, depending upon PCTL configuration.
 *  0b1..Peripheral Crossbar (XBAR) Output[6]
 */
#define SIM_MISC_CTL_TMR1SCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR1SCSSEL_SHIFT)) & SIM_MISC_CTL_TMR1SCSSEL_MASK)

#define SIM_MISC_CTL_TMR2SCSSEL_MASK             (0x40000U)
#define SIM_MISC_CTL_TMR2SCSSEL_SHIFT            (18U)
/*! TMR2SCSSEL - Quadtimer Channel2 Secondary Count Source Select
 *  0b0..Pad PTF7 or PTF0, depending upon PCTL configuration.
 *  0b1..Peripheral Crossbar (XBAR) Output[7]
 */
#define SIM_MISC_CTL_TMR2SCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR2SCSSEL_SHIFT)) & SIM_MISC_CTL_TMR2SCSSEL_MASK)

#define SIM_MISC_CTL_TMR3SCSSEL_MASK             (0x80000U)
#define SIM_MISC_CTL_TMR3SCSSEL_SHIFT            (19U)
/*! TMR3SCSSEL - Quadtimer Channel3 Secondary Count Source Select
 *  0b0..Pad PTE5 or PTD1, depending upon PCTL configuration.
 *  0b1..Peripheral Crossbar (XBAR) Output[8]
 */
#define SIM_MISC_CTL_TMR3SCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR3SCSSEL_SHIFT)) & SIM_MISC_CTL_TMR3SCSSEL_MASK)

#define SIM_MISC_CTL_TMR0PCSSEL_MASK             (0x300000U)
#define SIM_MISC_CTL_TMR0PCSSEL_SHIFT            (20U)
/*! TMR0PCSSEL - Quadtimer Channel0 Primary Count Source Select
 *  0b00..Bus Clock
 *  0b01..Peripheral Crossbar Output [9]
 *  0b10..Peripheral Crossbar Output [10]
 *  0b11..Disabled
 */
#define SIM_MISC_CTL_TMR0PCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR0PCSSEL_SHIFT)) & SIM_MISC_CTL_TMR0PCSSEL_MASK)

#define SIM_MISC_CTL_TMR1PCSSEL_MASK             (0xC00000U)
#define SIM_MISC_CTL_TMR1PCSSEL_SHIFT            (22U)
/*! TMR1PCSSEL - Quadtimer Channel1 Primary Count Source Select
 *  0b00..Bus Clock
 *  0b01..Peripheral Crossbar Output [9]
 *  0b10..Peripheral Crossbar Output [10]
 *  0b11..Disabled
 */
#define SIM_MISC_CTL_TMR1PCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR1PCSSEL_SHIFT)) & SIM_MISC_CTL_TMR1PCSSEL_MASK)

#define SIM_MISC_CTL_TMR2PCSSEL_MASK             (0x3000000U)
#define SIM_MISC_CTL_TMR2PCSSEL_SHIFT            (24U)
/*! TMR2PCSSEL - Quadtimer Channel2 Primary Count Source Select
 *  0b00..Bus Clock
 *  0b01..Peripheral Crossbar Output [9]
 *  0b10..Peripheral Crossbar Output [10]
 *  0b11..Disabled
 */
#define SIM_MISC_CTL_TMR2PCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR2PCSSEL_SHIFT)) & SIM_MISC_CTL_TMR2PCSSEL_MASK)

#define SIM_MISC_CTL_TMR3PCSSEL_MASK             (0xC000000U)
#define SIM_MISC_CTL_TMR3PCSSEL_SHIFT            (26U)
/*! TMR3PCSSEL - Quadtimer Channel3 Primary Count Source Select
 *  0b00..Bus Clock
 *  0b01..Peripheral Crossbar Output [9]
 *  0b10..Peripheral Crossbar Output [10]
 *  0b11..Disabled
 */
#define SIM_MISC_CTL_TMR3PCSSEL(x)               (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_TMR3PCSSEL_SHIFT)) & SIM_MISC_CTL_TMR3PCSSEL_MASK)

#define SIM_MISC_CTL_RTCCLKSEL_MASK              (0x10000000U)
#define SIM_MISC_CTL_RTCCLKSEL_SHIFT             (28U)
/*! RTCCLKSEL - RTC Clock select
 *  0b0..RTC OSC_32K clock selected
 *  0b1..32K IRC Clock selected
 */
#define SIM_MISC_CTL_RTCCLKSEL(x)                (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_RTCCLKSEL_SHIFT)) & SIM_MISC_CTL_RTCCLKSEL_MASK)

#define SIM_MISC_CTL_VREFBUFOUTEN_MASK           (0x20000000U)
#define SIM_MISC_CTL_VREFBUFOUTEN_SHIFT          (29U)
/*! VREFBUFOUTEN - VrefBuffer Output Enable
 *  0b0..Buffer does not drive PAD
 *  0b1..Buffer drives selected voltage (selected by vref_buffer_sel) on pad
 */
#define SIM_MISC_CTL_VREFBUFOUTEN(x)             (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_VREFBUFOUTEN_SHIFT)) & SIM_MISC_CTL_VREFBUFOUTEN_MASK)

#define SIM_MISC_CTL_VREFBUFINSEL_MASK           (0x40000000U)
#define SIM_MISC_CTL_VREFBUFINSEL_SHIFT          (30U)
/*! VREFBUFINSEL - VrefBuffer Input Select
 *  0b0..Internal Reference selected as Buffer Input
 *  0b1..External Reference selected as Buffer Input
 */
#define SIM_MISC_CTL_VREFBUFINSEL(x)             (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_VREFBUFINSEL_SHIFT)) & SIM_MISC_CTL_VREFBUFINSEL_MASK)

#define SIM_MISC_CTL_VREFBUFPD_MASK              (0x80000000U)
#define SIM_MISC_CTL_VREFBUFPD_SHIFT             (31U)
/*! VREFBUFPD - VrefBuffer Power Down
 *  0b0..Buffer Enabled
 *  0b1..Buffer Powered Down
 */
#define SIM_MISC_CTL_VREFBUFPD(x)                (((uint32_t)(((uint32_t)(x)) << SIM_MISC_CTL_VREFBUFPD_SHIFT)) & SIM_MISC_CTL_VREFBUFPD_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define SIM_BASE                                 (0x4003E000u)
/** Peripheral SIM base pointer */
#define SIM                                      ((SIM_Type *)SIM_BASE)
/** Array initializer of SIM peripheral base addresses */
#define SIM_BASE_ADDRS                           { SIM_BASE }
/** Array initializer of SIM peripheral base pointers */
#define SIM_BASE_PTRS                            { SIM }

/*!
 * @}
 */ /* end of group SIM_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Peripheral_Access_Layer SMC Peripheral Access Layer
 * @{
 */

/** SMC - Register Layout Typedef */
typedef struct {
  __IO uint8_t PMPROT;                             /**< Power Mode Protection register, offset: 0x0 */
  __IO uint8_t PMCTRL;                             /**< Power Mode Control register, offset: 0x1 */
  __IO uint8_t STOPCTRL;                           /**< Stop Control Register, offset: 0x2 */
  __I  uint8_t PMSTAT;                             /**< Power Mode Status register, offset: 0x3 */
} SMC_Type;

/* ----------------------------------------------------------------------------
   -- SMC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SMC_Register_Masks SMC Register Masks
 * @{
 */

/*! @name PMPROT - Power Mode Protection register */
/*! @{ */

#define SMC_PMPROT_AVLLS_MASK                    (0x2U)
#define SMC_PMPROT_AVLLS_SHIFT                   (1U)
/*! AVLLS - Allow Very-Low-Leakage Stop Mode
 *  0b0..Any VLLSx mode is not allowed
 *  0b1..Any VLLSx mode is allowed
 */
#define SMC_PMPROT_AVLLS(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLLS_SHIFT)) & SMC_PMPROT_AVLLS_MASK)

#define SMC_PMPROT_AVLP_MASK                     (0x20U)
#define SMC_PMPROT_AVLP_SHIFT                    (5U)
/*! AVLP - Allow Very-Low-Power Modes
 *  0b0..VLPR, VLPW, and VLPS are not allowed.
 *  0b1..VLPR, VLPW, and VLPS are allowed.
 */
#define SMC_PMPROT_AVLP(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMPROT_AVLP_SHIFT)) & SMC_PMPROT_AVLP_MASK)
/*! @} */

/*! @name PMCTRL - Power Mode Control register */
/*! @{ */

#define SMC_PMCTRL_STOPM_MASK                    (0x7U)
#define SMC_PMCTRL_STOPM_SHIFT                   (0U)
/*! STOPM - Stop Mode Control
 *  0b000..Normal Stop (STOP)
 *  0b001..Reserved
 *  0b010..Very-Low-Power Stop (VLPS)
 *  0b011..Reserved
 *  0b100..Very-Low-Leakage Stop (VLLSx)
 *  0b101..Reserved
 *  0b110..Reseved
 *  0b111..Reserved
 */
#define SMC_PMCTRL_STOPM(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPM_SHIFT)) & SMC_PMCTRL_STOPM_MASK)

#define SMC_PMCTRL_STOPA_MASK                    (0x8U)
#define SMC_PMCTRL_STOPA_SHIFT                   (3U)
/*! STOPA - Stop Aborted
 *  0b0..The previous stop mode entry was successful.
 *  0b1..The previous stop mode entry was aborted.
 */
#define SMC_PMCTRL_STOPA(x)                      (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_STOPA_SHIFT)) & SMC_PMCTRL_STOPA_MASK)

#define SMC_PMCTRL_RUNM_MASK                     (0x60U)
#define SMC_PMCTRL_RUNM_SHIFT                    (5U)
/*! RUNM - Run Mode Control
 *  0b00..Normal Run mode (RUN)
 *  0b01..Reserved
 *  0b10..Very-Low-Power Run mode (VLPR)
 *  0b11..Reserved
 */
#define SMC_PMCTRL_RUNM(x)                       (((uint8_t)(((uint8_t)(x)) << SMC_PMCTRL_RUNM_SHIFT)) & SMC_PMCTRL_RUNM_MASK)
/*! @} */

/*! @name STOPCTRL - Stop Control Register */
/*! @{ */

#define SMC_STOPCTRL_VLLSM_MASK                  (0x7U)
#define SMC_STOPCTRL_VLLSM_SHIFT                 (0U)
/*! VLLSM - VLLS Mode Control
 *  0b000..VLLS0
 *  0b001..VLLS1
 *  0b010..VLLS2
 *  0b011..VLLS3
 *  0b100..Reserved
 *  0b101..Reserved
 *  0b110..Reserved
 *  0b111..Reserved
 */
#define SMC_STOPCTRL_VLLSM(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_VLLSM_SHIFT)) & SMC_STOPCTRL_VLLSM_MASK)

#define SMC_STOPCTRL_PORPO_MASK                  (0x20U)
#define SMC_STOPCTRL_PORPO_SHIFT                 (5U)
/*! PORPO - POR Power Option
 *  0b0..POR detect circuit is enabled in VLLS0
 *  0b1..POR detect circuit is disabled in VLLS0
 */
#define SMC_STOPCTRL_PORPO(x)                    (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PORPO_SHIFT)) & SMC_STOPCTRL_PORPO_MASK)

#define SMC_STOPCTRL_PSTOPO_MASK                 (0xC0U)
#define SMC_STOPCTRL_PSTOPO_SHIFT                (6U)
/*! PSTOPO - Partial Stop Option
 *  0b00..STOP - Normal Stop mode
 *  0b01..PSTOP1 - Partial Stop with both system and bus clocks disabled
 *  0b10..PSTOP2 - Partial Stop with system clock disabled and bus clock enabled
 *  0b11..Reserved
 */
#define SMC_STOPCTRL_PSTOPO(x)                   (((uint8_t)(((uint8_t)(x)) << SMC_STOPCTRL_PSTOPO_SHIFT)) & SMC_STOPCTRL_PSTOPO_MASK)
/*! @} */

/*! @name PMSTAT - Power Mode Status register */
/*! @{ */

#define SMC_PMSTAT_PMSTAT_MASK                   (0xFFU)
#define SMC_PMSTAT_PMSTAT_SHIFT                  (0U)
/*! PMSTAT - Power Mode Status
 */
#define SMC_PMSTAT_PMSTAT(x)                     (((uint8_t)(((uint8_t)(x)) << SMC_PMSTAT_PMSTAT_SHIFT)) & SMC_PMSTAT_PMSTAT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SMC_Register_Masks */


/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE                                 (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC                                      ((SMC_Type *)SMC_BASE)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS                           { SMC_BASE }
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            { SMC }

/*!
 * @}
 */ /* end of group SMC_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
  __IO uint8_t S;                                  /**< SPI Status Register, offset: 0x0 */
  __IO uint8_t BR;                                 /**< SPI Baud Rate Register, offset: 0x1 */
  __IO uint8_t C2;                                 /**< SPI Control Register 2, offset: 0x2 */
  __IO uint8_t C1;                                 /**< SPI Control Register 1, offset: 0x3 */
  __IO uint8_t ML;                                 /**< SPI Match Register low, offset: 0x4 */
  __IO uint8_t MH;                                 /**< SPI match register high, offset: 0x5 */
  __IO uint8_t DL;                                 /**< SPI Data Register low, offset: 0x6 */
  __IO uint8_t DH;                                 /**< SPI data register high, offset: 0x7 */
       uint8_t RESERVED_0[2];
  __IO uint8_t CI;                                 /**< SPI clear interrupt register, offset: 0xA */
  __IO uint8_t C3;                                 /**< SPI control register 3, offset: 0xB */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name S - SPI Status Register */
/*! @{ */

#define SPI_S_RFIFOEF_MASK                       (0x1U)
#define SPI_S_RFIFOEF_SHIFT                      (0U)
/*! RFIFOEF - SPI read FIFO empty flag
 *  0b0..Read FIFO has data. Reads of the DH:DL registers in 16-bit mode or the DL register in 8-bit mode will empty the read FIFO.
 *  0b1..Read FIFO is empty.
 */
#define SPI_S_RFIFOEF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_RFIFOEF_SHIFT)) & SPI_S_RFIFOEF_MASK)

#define SPI_S_TXFULLF_MASK                       (0x2U)
#define SPI_S_TXFULLF_SHIFT                      (1U)
/*! TXFULLF - Transmit FIFO full flag
 *  0b0..Transmit FIFO has less than 8 bytes
 *  0b1..Transmit FIFO has 8 bytes of data
 */
#define SPI_S_TXFULLF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_TXFULLF_SHIFT)) & SPI_S_TXFULLF_MASK)

#define SPI_S_TNEAREF_MASK                       (0x4U)
#define SPI_S_TNEAREF_SHIFT                      (2U)
/*! TNEAREF - Transmit FIFO nearly empty flag
 *  0b0..Transmit FIFO has more than 16 bits (when C3[5] is 0) or more than 32 bits (when C3[5] is 1) remaining to transmit
 *  0b1..Transmit FIFO has an amount of data equal to or less than 16 bits (when C3[5] is 0) or 32 bits (when C3[5] is 1) remaining to transmit
 */
#define SPI_S_TNEAREF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_TNEAREF_SHIFT)) & SPI_S_TNEAREF_MASK)

#define SPI_S_RNFULLF_MASK                       (0x8U)
#define SPI_S_RNFULLF_SHIFT                      (3U)
/*! RNFULLF - Receive FIFO nearly full flag
 *  0b0..Receive FIFO has received less than 48 bits (when C3[4] is 0) or less than 32 bits (when C3[4] is 1)
 *  0b1..Receive FIFO has received data of an amount equal to or greater than 48 bits (when C3[4] is 0) or 32 bits (when C3[4] is 1)
 */
#define SPI_S_RNFULLF(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_S_RNFULLF_SHIFT)) & SPI_S_RNFULLF_MASK)

#define SPI_S_MODF_MASK                          (0x10U)
#define SPI_S_MODF_SHIFT                         (4U)
/*! MODF - Master Mode Fault Flag
 *  0b0..No mode fault error
 *  0b1..Mode fault error detected
 */
#define SPI_S_MODF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_MODF_SHIFT)) & SPI_S_MODF_MASK)

#define SPI_S_SPTEF_MASK                         (0x20U)
#define SPI_S_SPTEF_SHIFT                        (5U)
/*! SPTEF - SPI Transmit Buffer Empty Flag (when FIFO is not supported or not enabled) or SPI
 *    transmit FIFO empty flag (when FIFO is supported and enabled)
 *  0b0..SPI transmit buffer not empty (when FIFOMODE is not present or is 0) or SPI FIFO not empty (when FIFOMODE is 1)
 *  0b1..SPI transmit buffer empty (when FIFOMODE is not present or is 0) or SPI FIFO empty (when FIFOMODE is 1)
 */
#define SPI_S_SPTEF(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_S_SPTEF_SHIFT)) & SPI_S_SPTEF_MASK)

#define SPI_S_SPMF_MASK                          (0x40U)
#define SPI_S_SPMF_SHIFT                         (6U)
/*! SPMF - SPI Match Flag
 *  0b0..Value in the receive data buffer does not match the value in the MH:ML registers
 *  0b1..Value in the receive data buffer matches the value in the MH:ML registers
 */
#define SPI_S_SPMF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_SPMF_SHIFT)) & SPI_S_SPMF_MASK)

#define SPI_S_SPRF_MASK                          (0x80U)
#define SPI_S_SPRF_SHIFT                         (7U)
/*! SPRF - SPI Read Buffer Full Flag (when FIFO is not supported or not enabled) or SPI read FIFO
 *    FULL flag (when FIFO is supported and enabled)
 *  0b0..No data available in the receive data buffer (when FIFOMODE is not present or is 0) or Read FIFO is not full (when FIFOMODE is 1)
 *  0b1..Data available in the receive data buffer (when FIFOMODE is not present or is 0) or Read FIFO is full (when FIFOMODE is 1)
 */
#define SPI_S_SPRF(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_S_SPRF_SHIFT)) & SPI_S_SPRF_MASK)
/*! @} */

/*! @name BR - SPI Baud Rate Register */
/*! @{ */

#define SPI_BR_SPR_MASK                          (0xFU)
#define SPI_BR_SPR_SHIFT                         (0U)
/*! SPR - SPI Baud Rate Divisor
 *  0b0000..Baud rate divisor is 2.
 *  0b0001..Baud rate divisor is 4.
 *  0b0010..Baud rate divisor is 8.
 *  0b0011..Baud rate divisor is 16.
 *  0b0100..Baud rate divisor is 32.
 *  0b0101..Baud rate divisor is 64.
 *  0b0110..Baud rate divisor is 128.
 *  0b0111..Baud rate divisor is 256.
 *  0b1000..Baud rate divisor is 512.
 */
#define SPI_BR_SPR(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_BR_SPR_SHIFT)) & SPI_BR_SPR_MASK)

#define SPI_BR_SPPR_MASK                         (0x70U)
#define SPI_BR_SPPR_SHIFT                        (4U)
/*! SPPR - SPI Baud Rate Prescale Divisor
 *  0b000..Baud rate prescaler divisor is 1.
 *  0b001..Baud rate prescaler divisor is 2.
 *  0b010..Baud rate prescaler divisor is 3.
 *  0b011..Baud rate prescaler divisor is 4.
 *  0b100..Baud rate prescaler divisor is 5.
 *  0b101..Baud rate prescaler divisor is 6.
 *  0b110..Baud rate prescaler divisor is 7.
 *  0b111..Baud rate prescaler divisor is 8.
 */
#define SPI_BR_SPPR(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_BR_SPPR_SHIFT)) & SPI_BR_SPPR_MASK)
/*! @} */

/*! @name C2 - SPI Control Register 2 */
/*! @{ */

#define SPI_C2_SPC0_MASK                         (0x1U)
#define SPI_C2_SPC0_SHIFT                        (0U)
/*! SPC0 - SPI Pin Control 0
 *  0b0..SPI uses separate pins for data input and data output (pin mode is normal). In master mode of operation:
 *       MISO is master in and MOSI is master out. In slave mode of operation: MISO is slave out and MOSI is slave
 *       in.
 *  0b1..SPI configured for single-wire bidirectional operation (pin mode is bidirectional). In master mode of
 *       operation: MISO is not used by SPI; MOSI is master in when BIDIROE is 0 or master I/O when BIDIROE is 1. In
 *       slave mode of operation: MISO is slave in when BIDIROE is 0 or slave I/O when BIDIROE is 1; MOSI is not
 *       used by SPI.
 */
#define SPI_C2_SPC0(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPC0_SHIFT)) & SPI_C2_SPC0_MASK)

#define SPI_C2_SPISWAI_MASK                      (0x2U)
#define SPI_C2_SPISWAI_SHIFT                     (1U)
/*! SPISWAI - SPI Stop in Wait Mode
 *  0b0..SPI clocks continue to operate in Wait mode.
 *  0b1..SPI clocks stop when the MCU enters Wait mode.
 */
#define SPI_C2_SPISWAI(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPISWAI_SHIFT)) & SPI_C2_SPISWAI_MASK)

#define SPI_C2_RXDMAE_MASK                       (0x4U)
#define SPI_C2_RXDMAE_SHIFT                      (2U)
/*! RXDMAE - Receive DMA enable
 *  0b0..DMA request for receive is disabled and interrupt from SPRF is allowed
 *  0b1..DMA request for receive is enabled and interrupt from SPRF is disabled
 */
#define SPI_C2_RXDMAE(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_RXDMAE_SHIFT)) & SPI_C2_RXDMAE_MASK)

#define SPI_C2_BIDIROE_MASK                      (0x8U)
#define SPI_C2_BIDIROE_SHIFT                     (3U)
/*! BIDIROE - Bidirectional Mode Output Enable
 *  0b0..Output driver disabled so SPI data I/O pin acts as an input
 *  0b1..SPI I/O pin enabled as an output
 */
#define SPI_C2_BIDIROE(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_BIDIROE_SHIFT)) & SPI_C2_BIDIROE_MASK)

#define SPI_C2_MODFEN_MASK                       (0x10U)
#define SPI_C2_MODFEN_SHIFT                      (4U)
/*! MODFEN - Master Mode-Fault Function Enable
 *  0b0..Mode fault function disabled, master SS pin reverts to general-purpose I/O not controlled by SPI
 *  0b1..Mode fault function enabled, master SS pin acts as the mode fault input or the slave select output
 */
#define SPI_C2_MODFEN(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_MODFEN_SHIFT)) & SPI_C2_MODFEN_MASK)

#define SPI_C2_TXDMAE_MASK                       (0x20U)
#define SPI_C2_TXDMAE_SHIFT                      (5U)
/*! TXDMAE - Transmit DMA enable
 *  0b0..DMA request for transmit is disabled and interrupt from SPTEF is allowed
 *  0b1..DMA request for transmit is enabled and interrupt from SPTEF is disabled
 */
#define SPI_C2_TXDMAE(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C2_TXDMAE_SHIFT)) & SPI_C2_TXDMAE_MASK)

#define SPI_C2_SPIMODE_MASK                      (0x40U)
#define SPI_C2_SPIMODE_SHIFT                     (6U)
/*! SPIMODE - SPI 8-bit or 16-bit mode
 *  0b0..8-bit SPI shift register, match register, and buffers
 *  0b1..16-bit SPI shift register, match register, and buffers
 */
#define SPI_C2_SPIMODE(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPIMODE_SHIFT)) & SPI_C2_SPIMODE_MASK)

#define SPI_C2_SPMIE_MASK                        (0x80U)
#define SPI_C2_SPMIE_SHIFT                       (7U)
/*! SPMIE - SPI Match Interrupt Enable
 *  0b0..Interrupts from SPMF inhibited (use polling)
 *  0b1..When SPMF is 1, requests a hardware interrupt
 */
#define SPI_C2_SPMIE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C2_SPMIE_SHIFT)) & SPI_C2_SPMIE_MASK)
/*! @} */

/*! @name C1 - SPI Control Register 1 */
/*! @{ */

#define SPI_C1_LSBFE_MASK                        (0x1U)
#define SPI_C1_LSBFE_SHIFT                       (0U)
/*! LSBFE - LSB First (shifter direction)
 *  0b0..SPI serial data transfers start with the most significant bit.
 *  0b1..SPI serial data transfers start with the least significant bit.
 */
#define SPI_C1_LSBFE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C1_LSBFE_SHIFT)) & SPI_C1_LSBFE_MASK)

#define SPI_C1_SSOE_MASK                         (0x2U)
#define SPI_C1_SSOE_SHIFT                        (1U)
/*! SSOE - Slave Select Output Enable
 *  0b0..When C2[MODFEN] is 0: In master mode, SS pin function is general-purpose I/O (not SPI). In slave mode, SS
 *       pin function is slave select input. When C2[MODFEN] is 1: In master mode, SS pin function is SS input for
 *       mode fault. In slave mode, SS pin function is slave select input.
 *  0b1..When C2[MODFEN] is 0: In master mode, SS pin function is general-purpose I/O (not SPI). In slave mode, SS
 *       pin function is slave select input. When C2[MODFEN] is 1: In master mode, SS pin function is automatic SS
 *       output. In slave mode: SS pin function is slave select input.
 */
#define SPI_C1_SSOE(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_SSOE_SHIFT)) & SPI_C1_SSOE_MASK)

#define SPI_C1_CPHA_MASK                         (0x4U)
#define SPI_C1_CPHA_SHIFT                        (2U)
/*! CPHA - Clock Phase
 *  0b0..First edge on SPSCK occurs at the middle of the first cycle of a data transfer.
 *  0b1..First edge on SPSCK occurs at the start of the first cycle of a data transfer.
 */
#define SPI_C1_CPHA(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_CPHA_SHIFT)) & SPI_C1_CPHA_MASK)

#define SPI_C1_CPOL_MASK                         (0x8U)
#define SPI_C1_CPOL_SHIFT                        (3U)
/*! CPOL - Clock Polarity
 *  0b0..Active-high SPI clock (idles low)
 *  0b1..Active-low SPI clock (idles high)
 */
#define SPI_C1_CPOL(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_CPOL_SHIFT)) & SPI_C1_CPOL_MASK)

#define SPI_C1_MSTR_MASK                         (0x10U)
#define SPI_C1_MSTR_SHIFT                        (4U)
/*! MSTR - Master/Slave Mode Select
 *  0b0..SPI module configured as a slave SPI device
 *  0b1..SPI module configured as a master SPI device
 */
#define SPI_C1_MSTR(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_MSTR_SHIFT)) & SPI_C1_MSTR_MASK)

#define SPI_C1_SPTIE_MASK                        (0x20U)
#define SPI_C1_SPTIE_SHIFT                       (5U)
/*! SPTIE - SPI Transmit Interrupt Enable
 *  0b0..Interrupts from SPTEF inhibited (use polling)
 *  0b1..When SPTEF is 1, hardware interrupt requested
 */
#define SPI_C1_SPTIE(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPTIE_SHIFT)) & SPI_C1_SPTIE_MASK)

#define SPI_C1_SPE_MASK                          (0x40U)
#define SPI_C1_SPE_SHIFT                         (6U)
/*! SPE - SPI System Enable
 *  0b0..SPI system inactive
 *  0b1..SPI system enabled
 */
#define SPI_C1_SPE(x)                            (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPE_SHIFT)) & SPI_C1_SPE_MASK)

#define SPI_C1_SPIE_MASK                         (0x80U)
#define SPI_C1_SPIE_SHIFT                        (7U)
/*! SPIE - SPI Interrupt Enable: for SPRF and MODF (when FIFO is not supported or not enabled) or
 *    for read FIFO (when FIFO is supported and enabled)
 *  0b0..Interrupts from SPRF and MODF are inhibited-use polling (when FIFOMODE is not present or is 0) or Read
 *       FIFO Full Interrupts are disabled (when FIFOMODE is 1)
 *  0b1..Request a hardware interrupt when SPRF or MODF is 1 (when FIFOMODE is not present or is 0) or Read FIFO
 *       Full Interrupts are enabled (when FIFOMODE is 1)
 */
#define SPI_C1_SPIE(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_C1_SPIE_SHIFT)) & SPI_C1_SPIE_MASK)
/*! @} */

/*! @name ML - SPI Match Register low */
/*! @{ */

#define SPI_ML_Bits_MASK                         (0xFFU)
#define SPI_ML_Bits_SHIFT                        (0U)
/*! Bits - Hardware compare value (low byte)
 */
#define SPI_ML_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_ML_Bits_SHIFT)) & SPI_ML_Bits_MASK)
/*! @} */

/*! @name MH - SPI match register high */
/*! @{ */

#define SPI_MH_Bits_MASK                         (0xFFU)
#define SPI_MH_Bits_SHIFT                        (0U)
/*! Bits - Hardware compare value (high byte)
 */
#define SPI_MH_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_MH_Bits_SHIFT)) & SPI_MH_Bits_MASK)
/*! @} */

/*! @name DL - SPI Data Register low */
/*! @{ */

#define SPI_DL_Bits_MASK                         (0xFFU)
#define SPI_DL_Bits_SHIFT                        (0U)
/*! Bits - Data (low byte)
 */
#define SPI_DL_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_DL_Bits_SHIFT)) & SPI_DL_Bits_MASK)
/*! @} */

/*! @name DH - SPI data register high */
/*! @{ */

#define SPI_DH_Bits_MASK                         (0xFFU)
#define SPI_DH_Bits_SHIFT                        (0U)
/*! Bits - Data (high byte)
 */
#define SPI_DH_Bits(x)                           (((uint8_t)(((uint8_t)(x)) << SPI_DH_Bits_SHIFT)) & SPI_DH_Bits_MASK)
/*! @} */

/*! @name CI - SPI clear interrupt register */
/*! @{ */

#define SPI_CI_SPRFCI_MASK                       (0x1U)
#define SPI_CI_SPRFCI_SHIFT                      (0U)
/*! SPRFCI - Receive FIFO full flag clear interrupt
 */
#define SPI_CI_SPRFCI(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_SPRFCI_SHIFT)) & SPI_CI_SPRFCI_MASK)

#define SPI_CI_SPTEFCI_MASK                      (0x2U)
#define SPI_CI_SPTEFCI_SHIFT                     (1U)
/*! SPTEFCI - Transmit FIFO empty flag clear interrupt
 */
#define SPI_CI_SPTEFCI(x)                        (((uint8_t)(((uint8_t)(x)) << SPI_CI_SPTEFCI_SHIFT)) & SPI_CI_SPTEFCI_MASK)

#define SPI_CI_RNFULLFCI_MASK                    (0x4U)
#define SPI_CI_RNFULLFCI_SHIFT                   (2U)
/*! RNFULLFCI - Receive FIFO nearly full flag clear interrupt
 */
#define SPI_CI_RNFULLFCI(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_CI_RNFULLFCI_SHIFT)) & SPI_CI_RNFULLFCI_MASK)

#define SPI_CI_TNEAREFCI_MASK                    (0x8U)
#define SPI_CI_TNEAREFCI_SHIFT                   (3U)
/*! TNEAREFCI - Transmit FIFO nearly empty flag clear interrupt
 */
#define SPI_CI_TNEAREFCI(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_CI_TNEAREFCI_SHIFT)) & SPI_CI_TNEAREFCI_MASK)

#define SPI_CI_RXFOF_MASK                        (0x10U)
#define SPI_CI_RXFOF_SHIFT                       (4U)
/*! RXFOF - Receive FIFO overflow flag
 *  0b0..Receive FIFO overflow condition has not occurred
 *  0b1..Receive FIFO overflow condition occurred
 */
#define SPI_CI_RXFOF(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_CI_RXFOF_SHIFT)) & SPI_CI_RXFOF_MASK)

#define SPI_CI_TXFOF_MASK                        (0x20U)
#define SPI_CI_TXFOF_SHIFT                       (5U)
/*! TXFOF - Transmit FIFO overflow flag
 *  0b0..Transmit FIFO overflow condition has not occurred
 *  0b1..Transmit FIFO overflow condition occurred
 */
#define SPI_CI_TXFOF(x)                          (((uint8_t)(((uint8_t)(x)) << SPI_CI_TXFOF_SHIFT)) & SPI_CI_TXFOF_MASK)

#define SPI_CI_RXFERR_MASK                       (0x40U)
#define SPI_CI_RXFERR_SHIFT                      (6U)
/*! RXFERR - Receive FIFO error flag
 *  0b0..No receive FIFO error occurred
 *  0b1..A receive FIFO error occurred
 */
#define SPI_CI_RXFERR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_RXFERR_SHIFT)) & SPI_CI_RXFERR_MASK)

#define SPI_CI_TXFERR_MASK                       (0x80U)
#define SPI_CI_TXFERR_SHIFT                      (7U)
/*! TXFERR - Transmit FIFO error flag
 *  0b0..No transmit FIFO error occurred
 *  0b1..A transmit FIFO error occurred
 */
#define SPI_CI_TXFERR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_CI_TXFERR_SHIFT)) & SPI_CI_TXFERR_MASK)
/*! @} */

/*! @name C3 - SPI control register 3 */
/*! @{ */

#define SPI_C3_FIFOMODE_MASK                     (0x1U)
#define SPI_C3_FIFOMODE_SHIFT                    (0U)
/*! FIFOMODE - FIFO mode enable
 *  0b0..Buffer mode disabled
 *  0b1..Data available in the receive data buffer
 */
#define SPI_C3_FIFOMODE(x)                       (((uint8_t)(((uint8_t)(x)) << SPI_C3_FIFOMODE_SHIFT)) & SPI_C3_FIFOMODE_MASK)

#define SPI_C3_RNFULLIEN_MASK                    (0x2U)
#define SPI_C3_RNFULLIEN_SHIFT                   (1U)
/*! RNFULLIEN - Receive FIFO nearly full interrupt enable
 *  0b0..No interrupt upon RNFULLF being set
 *  0b1..Enable interrupts upon RNFULLF being set
 */
#define SPI_C3_RNFULLIEN(x)                      (((uint8_t)(((uint8_t)(x)) << SPI_C3_RNFULLIEN_SHIFT)) & SPI_C3_RNFULLIEN_MASK)

#define SPI_C3_TNEARIEN_MASK                     (0x4U)
#define SPI_C3_TNEARIEN_SHIFT                    (2U)
/*! TNEARIEN - Transmit FIFO nearly empty interrupt enable
 *  0b0..No interrupt upon TNEAREF being set
 *  0b1..Enable interrupts upon TNEAREF being set
 */
#define SPI_C3_TNEARIEN(x)                       (((uint8_t)(((uint8_t)(x)) << SPI_C3_TNEARIEN_SHIFT)) & SPI_C3_TNEARIEN_MASK)

#define SPI_C3_INTCLR_MASK                       (0x8U)
#define SPI_C3_INTCLR_SHIFT                      (3U)
/*! INTCLR - Interrupt clearing mechanism select
 *  0b0..These interrupts are cleared when the corresponding flags are cleared depending on the state of the FIFOs
 *  0b1..These interrupts are cleared by writing the corresponding bits in the CI register
 */
#define SPI_C3_INTCLR(x)                         (((uint8_t)(((uint8_t)(x)) << SPI_C3_INTCLR_SHIFT)) & SPI_C3_INTCLR_MASK)

#define SPI_C3_RNFULLF_MARK_MASK                 (0x10U)
#define SPI_C3_RNFULLF_MARK_SHIFT                (4U)
/*! RNFULLF_MARK - Receive FIFO nearly full watermark
 *  0b0..RNFULLF is set when the receive FIFO has 48 bits or more
 *  0b1..RNFULLF is set when the receive FIFO has 32 bits or more
 */
#define SPI_C3_RNFULLF_MARK(x)                   (((uint8_t)(((uint8_t)(x)) << SPI_C3_RNFULLF_MARK_SHIFT)) & SPI_C3_RNFULLF_MARK_MASK)

#define SPI_C3_TNEAREF_MARK_MASK                 (0x20U)
#define SPI_C3_TNEAREF_MARK_SHIFT                (5U)
/*! TNEAREF_MARK - Transmit FIFO nearly empty watermark
 *  0b0..TNEAREF is set when the transmit FIFO has 16 bits or less
 *  0b1..TNEAREF is set when the transmit FIFO has 32 bits or less
 */
#define SPI_C3_TNEAREF_MARK(x)                   (((uint8_t)(((uint8_t)(x)) << SPI_C3_TNEAREF_MARK_SHIFT)) & SPI_C3_TNEAREF_MARK_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40075000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x40076000u)
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
   -- SYSMPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSMPU_Peripheral_Access_Layer SYSMPU Peripheral Access Layer
 * @{
 */

/** SYSMPU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CESR;                              /**< Control/Error Status Register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x10, array step: 0x8 */
    __I  uint32_t EAR;                               /**< Error Address Register, slave port n, array offset: 0x10, array step: 0x8 */
    __I  uint32_t EDR;                               /**< Error Detail Register, slave port n, array offset: 0x14, array step: 0x8 */
  } SP[2];
       uint8_t RESERVED_1[992];
  __IO uint32_t WORD[8][4];                        /**< Region Descriptor n, Word 0..Region Descriptor n, Word 3, array offset: 0x400, array step: index*0x10, index2*0x4 */
       uint8_t RESERVED_2[896];
  __IO uint32_t RGDAAC[8];                         /**< Region Descriptor Alternate Access Control n, array offset: 0x800, array step: 0x4 */
} SYSMPU_Type;

/* ----------------------------------------------------------------------------
   -- SYSMPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSMPU_Register_Masks SYSMPU Register Masks
 * @{
 */

/*! @name CESR - Control/Error Status Register */
/*! @{ */

#define SYSMPU_CESR_VLD_MASK                     (0x1U)
#define SYSMPU_CESR_VLD_SHIFT                    (0U)
/*! VLD - Valid
 *  0b0..MPU is disabled. All accesses from all bus masters are allowed.
 *  0b1..MPU is enabled
 */
#define SYSMPU_CESR_VLD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_VLD_SHIFT)) & SYSMPU_CESR_VLD_MASK)

#define SYSMPU_CESR_NRGD_MASK                    (0xF00U)
#define SYSMPU_CESR_NRGD_SHIFT                   (8U)
/*! NRGD - Number Of Region Descriptors
 *  0b0000..8 region descriptors
 *  0b0001..12 region descriptors
 *  0b0010..16 region descriptors
 */
#define SYSMPU_CESR_NRGD(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_NRGD_SHIFT)) & SYSMPU_CESR_NRGD_MASK)

#define SYSMPU_CESR_NSP_MASK                     (0xF000U)
#define SYSMPU_CESR_NSP_SHIFT                    (12U)
/*! NSP - Number Of Slave Ports
 */
#define SYSMPU_CESR_NSP(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_NSP_SHIFT)) & SYSMPU_CESR_NSP_MASK)

#define SYSMPU_CESR_HRL_MASK                     (0xF0000U)
#define SYSMPU_CESR_HRL_SHIFT                    (16U)
/*! HRL - Hardware Revision Level
 */
#define SYSMPU_CESR_HRL(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_HRL_SHIFT)) & SYSMPU_CESR_HRL_MASK)

#define SYSMPU_CESR_SPERR_MASK                   (0xC0000000U)
#define SYSMPU_CESR_SPERR_SHIFT                  (30U)
/*! SPERR - Slave Port n Error
 *  0b00..No error has occurred for slave port n.
 *  0b01..An error has occurred for slave port n.
 */
#define SYSMPU_CESR_SPERR(x)                     (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_SPERR_SHIFT)) & SYSMPU_CESR_SPERR_MASK)
/*! @} */

/*! @name EAR - Error Address Register, slave port n */
/*! @{ */

#define SYSMPU_EAR_EADDR_MASK                    (0xFFFFFFFFU)
#define SYSMPU_EAR_EADDR_SHIFT                   (0U)
/*! EADDR - Error Address
 */
#define SYSMPU_EAR_EADDR(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_EAR_EADDR_SHIFT)) & SYSMPU_EAR_EADDR_MASK)
/*! @} */

/* The count of SYSMPU_EAR */
#define SYSMPU_EAR_COUNT                         (2U)

/*! @name EDR - Error Detail Register, slave port n */
/*! @{ */

#define SYSMPU_EDR_ERW_MASK                      (0x1U)
#define SYSMPU_EDR_ERW_SHIFT                     (0U)
/*! ERW - Error Read/Write
 *  0b0..Read
 *  0b1..Write
 */
#define SYSMPU_EDR_ERW(x)                        (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_ERW_SHIFT)) & SYSMPU_EDR_ERW_MASK)

#define SYSMPU_EDR_EATTR_MASK                    (0xEU)
#define SYSMPU_EDR_EATTR_SHIFT                   (1U)
/*! EATTR - Error Attributes
 *  0b000..User mode, instruction access
 *  0b001..User mode, data access
 *  0b010..Supervisor mode, instruction access
 *  0b011..Supervisor mode, data access
 */
#define SYSMPU_EDR_EATTR(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EATTR_SHIFT)) & SYSMPU_EDR_EATTR_MASK)

#define SYSMPU_EDR_EMN_MASK                      (0xF0U)
#define SYSMPU_EDR_EMN_SHIFT                     (4U)
/*! EMN - Error Master Number
 */
#define SYSMPU_EDR_EMN(x)                        (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EMN_SHIFT)) & SYSMPU_EDR_EMN_MASK)

#define SYSMPU_EDR_EPID_MASK                     (0xFF00U)
#define SYSMPU_EDR_EPID_SHIFT                    (8U)
/*! EPID - Error Process Identification
 */
#define SYSMPU_EDR_EPID(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EPID_SHIFT)) & SYSMPU_EDR_EPID_MASK)

#define SYSMPU_EDR_EACD_MASK                     (0xFFFF0000U)
#define SYSMPU_EDR_EACD_SHIFT                    (16U)
/*! EACD - Error Access Control Detail
 */
#define SYSMPU_EDR_EACD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EACD_SHIFT)) & SYSMPU_EDR_EACD_MASK)
/*! @} */

/* The count of SYSMPU_EDR */
#define SYSMPU_EDR_COUNT                         (2U)

/*! @name WORD - Region Descriptor n, Word 0..Region Descriptor n, Word 3 */
/*! @{ */

#define SYSMPU_WORD_M0UM_MASK                    (0x7U)
#define SYSMPU_WORD_M0UM_SHIFT                   (0U)
/*! M0UM - Bus Master 0 User Mode Access Control
 */
#define SYSMPU_WORD_M0UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0UM_SHIFT)) & SYSMPU_WORD_M0UM_MASK)

#define SYSMPU_WORD_VLD_MASK                     (0x1U)
#define SYSMPU_WORD_VLD_SHIFT                    (0U)
/*! VLD - Valid
 *  0b0..Region descriptor is invalid
 *  0b1..Region descriptor is valid
 */
#define SYSMPU_WORD_VLD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_VLD_SHIFT)) & SYSMPU_WORD_VLD_MASK)

#define SYSMPU_WORD_M0SM_MASK                    (0x18U)
#define SYSMPU_WORD_M0SM_SHIFT                   (3U)
/*! M0SM - Bus Master 0 Supervisor Mode Access Control
 */
#define SYSMPU_WORD_M0SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0SM_SHIFT)) & SYSMPU_WORD_M0SM_MASK)

#define SYSMPU_WORD_ENDADDR_MASK                 (0xFFFFFFE0U)
#define SYSMPU_WORD_ENDADDR_SHIFT                (5U)
/*! ENDADDR - End Address
 */
#define SYSMPU_WORD_ENDADDR(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_ENDADDR_SHIFT)) & SYSMPU_WORD_ENDADDR_MASK)

#define SYSMPU_WORD_M0PE_MASK                    (0x20U)
#define SYSMPU_WORD_M0PE_SHIFT                   (5U)
/*! M0PE - Bus Master 0 Process Identifier enable
 */
#define SYSMPU_WORD_M0PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0PE_SHIFT)) & SYSMPU_WORD_M0PE_MASK)

#define SYSMPU_WORD_SRTADDR_MASK                 (0xFFFFFFE0U)
#define SYSMPU_WORD_SRTADDR_SHIFT                (5U)
/*! SRTADDR - Start Address
 */
#define SYSMPU_WORD_SRTADDR(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_SRTADDR_SHIFT)) & SYSMPU_WORD_SRTADDR_MASK)

#define SYSMPU_WORD_M1UM_MASK                    (0x1C0U)
#define SYSMPU_WORD_M1UM_SHIFT                   (6U)
/*! M1UM - Bus Master 1 User Mode Access Control
 */
#define SYSMPU_WORD_M1UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1UM_SHIFT)) & SYSMPU_WORD_M1UM_MASK)

#define SYSMPU_WORD_M1SM_MASK                    (0x600U)
#define SYSMPU_WORD_M1SM_SHIFT                   (9U)
/*! M1SM - Bus Master 1 Supervisor Mode Access Control
 */
#define SYSMPU_WORD_M1SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1SM_SHIFT)) & SYSMPU_WORD_M1SM_MASK)

#define SYSMPU_WORD_M1PE_MASK                    (0x800U)
#define SYSMPU_WORD_M1PE_SHIFT                   (11U)
/*! M1PE - Bus Master 1 Process Identifier enable
 */
#define SYSMPU_WORD_M1PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1PE_SHIFT)) & SYSMPU_WORD_M1PE_MASK)

#define SYSMPU_WORD_M2UM_MASK                    (0x7000U)
#define SYSMPU_WORD_M2UM_SHIFT                   (12U)
/*! M2UM - Bus Master 2 User Mode Access control
 */
#define SYSMPU_WORD_M2UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2UM_SHIFT)) & SYSMPU_WORD_M2UM_MASK)

#define SYSMPU_WORD_M2SM_MASK                    (0x18000U)
#define SYSMPU_WORD_M2SM_SHIFT                   (15U)
/*! M2SM - Bus Master 2 Supervisor Mode Access Control
 */
#define SYSMPU_WORD_M2SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2SM_SHIFT)) & SYSMPU_WORD_M2SM_MASK)

#define SYSMPU_WORD_PIDMASK_MASK                 (0xFF0000U)
#define SYSMPU_WORD_PIDMASK_SHIFT                (16U)
/*! PIDMASK - Process Identifier Mask
 */
#define SYSMPU_WORD_PIDMASK(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_PIDMASK_SHIFT)) & SYSMPU_WORD_PIDMASK_MASK)

#define SYSMPU_WORD_M2PE_MASK                    (0x20000U)
#define SYSMPU_WORD_M2PE_SHIFT                   (17U)
/*! M2PE - Bus Master 2 Process Identifier Enable
 */
#define SYSMPU_WORD_M2PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2PE_SHIFT)) & SYSMPU_WORD_M2PE_MASK)

#define SYSMPU_WORD_M3UM_MASK                    (0x1C0000U)
#define SYSMPU_WORD_M3UM_SHIFT                   (18U)
/*! M3UM - Bus Master 3 User Mode Access Control
 *  0b000..An attempted access of that mode may be terminated with an access error (if not allowed by another descriptor) and the access not performed.
 *  0b001..Allows the given access type to occur
 */
#define SYSMPU_WORD_M3UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3UM_SHIFT)) & SYSMPU_WORD_M3UM_MASK)

#define SYSMPU_WORD_M3SM_MASK                    (0x600000U)
#define SYSMPU_WORD_M3SM_SHIFT                   (21U)
/*! M3SM - Bus Master 3 Supervisor Mode Access Control
 *  0b00..r/w/x; read, write and execute allowed
 *  0b01..r/x; read and execute allowed, but no write
 *  0b10..r/w; read and write allowed, but no execute
 *  0b11..Same as User mode defined in M3UM
 */
#define SYSMPU_WORD_M3SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3SM_SHIFT)) & SYSMPU_WORD_M3SM_MASK)

#define SYSMPU_WORD_M3PE_MASK                    (0x800000U)
#define SYSMPU_WORD_M3PE_SHIFT                   (23U)
/*! M3PE - Bus Master 3 Process Identifier Enable
 *  0b0..Do not include the process identifier in the evaluation
 *  0b1..Include the process identifier and mask (RGDn_WORD3) in the region hit evaluation
 */
#define SYSMPU_WORD_M3PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3PE_SHIFT)) & SYSMPU_WORD_M3PE_MASK)

#define SYSMPU_WORD_M4WE_MASK                    (0x1000000U)
#define SYSMPU_WORD_M4WE_SHIFT                   (24U)
/*! M4WE - Bus Master 4 Write Enable
 *  0b0..Bus master 4 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 4 writes allowed
 */
#define SYSMPU_WORD_M4WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M4WE_SHIFT)) & SYSMPU_WORD_M4WE_MASK)

#define SYSMPU_WORD_PID_MASK                     (0xFF000000U)
#define SYSMPU_WORD_PID_SHIFT                    (24U)
/*! PID - Process Identifier
 */
#define SYSMPU_WORD_PID(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_PID_SHIFT)) & SYSMPU_WORD_PID_MASK)

#define SYSMPU_WORD_M4RE_MASK                    (0x2000000U)
#define SYSMPU_WORD_M4RE_SHIFT                   (25U)
/*! M4RE - Bus Master 4 Read Enable
 *  0b0..Bus master 4 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 4 reads allowed
 */
#define SYSMPU_WORD_M4RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M4RE_SHIFT)) & SYSMPU_WORD_M4RE_MASK)

#define SYSMPU_WORD_M5WE_MASK                    (0x4000000U)
#define SYSMPU_WORD_M5WE_SHIFT                   (26U)
/*! M5WE - Bus Master 5 Write Enable
 *  0b0..Bus master 5 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 5 writes allowed
 */
#define SYSMPU_WORD_M5WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M5WE_SHIFT)) & SYSMPU_WORD_M5WE_MASK)

#define SYSMPU_WORD_M5RE_MASK                    (0x8000000U)
#define SYSMPU_WORD_M5RE_SHIFT                   (27U)
/*! M5RE - Bus Master 5 Read Enable
 *  0b0..Bus master 5 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 5 reads allowed
 */
#define SYSMPU_WORD_M5RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M5RE_SHIFT)) & SYSMPU_WORD_M5RE_MASK)

#define SYSMPU_WORD_M6WE_MASK                    (0x10000000U)
#define SYSMPU_WORD_M6WE_SHIFT                   (28U)
/*! M6WE - Bus Master 6 Write Enable
 *  0b0..Bus master 6 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 6 writes allowed
 */
#define SYSMPU_WORD_M6WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M6WE_SHIFT)) & SYSMPU_WORD_M6WE_MASK)

#define SYSMPU_WORD_M6RE_MASK                    (0x20000000U)
#define SYSMPU_WORD_M6RE_SHIFT                   (29U)
/*! M6RE - Bus Master 6 Read Enable
 *  0b0..Bus master 6 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 6 reads allowed
 */
#define SYSMPU_WORD_M6RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M6RE_SHIFT)) & SYSMPU_WORD_M6RE_MASK)

#define SYSMPU_WORD_M7WE_MASK                    (0x40000000U)
#define SYSMPU_WORD_M7WE_SHIFT                   (30U)
/*! M7WE - Bus Master 7 Write Enable
 *  0b0..Bus master 7 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 7 writes allowed
 */
#define SYSMPU_WORD_M7WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M7WE_SHIFT)) & SYSMPU_WORD_M7WE_MASK)

#define SYSMPU_WORD_M7RE_MASK                    (0x80000000U)
#define SYSMPU_WORD_M7RE_SHIFT                   (31U)
/*! M7RE - Bus Master 7 Read Enable
 *  0b0..Bus master 7 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 7 reads allowed
 */
#define SYSMPU_WORD_M7RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M7RE_SHIFT)) & SYSMPU_WORD_M7RE_MASK)
/*! @} */

/* The count of SYSMPU_WORD */
#define SYSMPU_WORD_COUNT                        (8U)

/* The count of SYSMPU_WORD */
#define SYSMPU_WORD_COUNT2                       (4U)

/*! @name RGDAAC - Region Descriptor Alternate Access Control n */
/*! @{ */

#define SYSMPU_RGDAAC_M0UM_MASK                  (0x7U)
#define SYSMPU_RGDAAC_M0UM_SHIFT                 (0U)
/*! M0UM - Bus Master 0 User Mode Access Control
 */
#define SYSMPU_RGDAAC_M0UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0UM_SHIFT)) & SYSMPU_RGDAAC_M0UM_MASK)

#define SYSMPU_RGDAAC_M0SM_MASK                  (0x18U)
#define SYSMPU_RGDAAC_M0SM_SHIFT                 (3U)
/*! M0SM - Bus Master 0 Supervisor Mode Access Control
 */
#define SYSMPU_RGDAAC_M0SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0SM_SHIFT)) & SYSMPU_RGDAAC_M0SM_MASK)

#define SYSMPU_RGDAAC_M0PE_MASK                  (0x20U)
#define SYSMPU_RGDAAC_M0PE_SHIFT                 (5U)
/*! M0PE - Bus Master 0 Process Identifier Enable
 */
#define SYSMPU_RGDAAC_M0PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0PE_SHIFT)) & SYSMPU_RGDAAC_M0PE_MASK)

#define SYSMPU_RGDAAC_M1UM_MASK                  (0x1C0U)
#define SYSMPU_RGDAAC_M1UM_SHIFT                 (6U)
/*! M1UM - Bus Master 1 User Mode Access Control
 */
#define SYSMPU_RGDAAC_M1UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1UM_SHIFT)) & SYSMPU_RGDAAC_M1UM_MASK)

#define SYSMPU_RGDAAC_M1SM_MASK                  (0x600U)
#define SYSMPU_RGDAAC_M1SM_SHIFT                 (9U)
/*! M1SM - Bus Master 1 Supervisor Mode Access Control
 */
#define SYSMPU_RGDAAC_M1SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1SM_SHIFT)) & SYSMPU_RGDAAC_M1SM_MASK)

#define SYSMPU_RGDAAC_M1PE_MASK                  (0x800U)
#define SYSMPU_RGDAAC_M1PE_SHIFT                 (11U)
/*! M1PE - Bus Master 1 Process Identifier Enable
 */
#define SYSMPU_RGDAAC_M1PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1PE_SHIFT)) & SYSMPU_RGDAAC_M1PE_MASK)

#define SYSMPU_RGDAAC_M2UM_MASK                  (0x7000U)
#define SYSMPU_RGDAAC_M2UM_SHIFT                 (12U)
/*! M2UM - Bus Master 2 User Mode Access Control
 */
#define SYSMPU_RGDAAC_M2UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2UM_SHIFT)) & SYSMPU_RGDAAC_M2UM_MASK)

#define SYSMPU_RGDAAC_M2SM_MASK                  (0x18000U)
#define SYSMPU_RGDAAC_M2SM_SHIFT                 (15U)
/*! M2SM - Bus Master 2 Supervisor Mode Access Control
 */
#define SYSMPU_RGDAAC_M2SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2SM_SHIFT)) & SYSMPU_RGDAAC_M2SM_MASK)

#define SYSMPU_RGDAAC_M2PE_MASK                  (0x20000U)
#define SYSMPU_RGDAAC_M2PE_SHIFT                 (17U)
/*! M2PE - Bus Master 2 Process Identifier Enable
 */
#define SYSMPU_RGDAAC_M2PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2PE_SHIFT)) & SYSMPU_RGDAAC_M2PE_MASK)

#define SYSMPU_RGDAAC_M3UM_MASK                  (0x1C0000U)
#define SYSMPU_RGDAAC_M3UM_SHIFT                 (18U)
/*! M3UM - Bus Master 3 User Mode Access Control
 *  0b000..An attempted access of that mode may be terminated with an access error (if not allowed by another descriptor) and the access not performed.
 *  0b001..Allows the given access type to occur
 */
#define SYSMPU_RGDAAC_M3UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3UM_SHIFT)) & SYSMPU_RGDAAC_M3UM_MASK)

#define SYSMPU_RGDAAC_M3SM_MASK                  (0x600000U)
#define SYSMPU_RGDAAC_M3SM_SHIFT                 (21U)
/*! M3SM - Bus Master 3 Supervisor Mode Access Control
 *  0b00..r/w/x; read, write and execute allowed
 *  0b01..r/x; read and execute allowed, but no write
 *  0b10..r/w; read and write allowed, but no execute
 *  0b11..Same as User mode defined in M3UM
 */
#define SYSMPU_RGDAAC_M3SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3SM_SHIFT)) & SYSMPU_RGDAAC_M3SM_MASK)

#define SYSMPU_RGDAAC_M3PE_MASK                  (0x800000U)
#define SYSMPU_RGDAAC_M3PE_SHIFT                 (23U)
/*! M3PE - Bus Master 3 Process Identifier Enable
 *  0b0..Do not include the process identifier in the evaluation
 *  0b1..Include the process identifier and mask (RGDn.RGDAAC) in the region hit evaluation
 */
#define SYSMPU_RGDAAC_M3PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3PE_SHIFT)) & SYSMPU_RGDAAC_M3PE_MASK)

#define SYSMPU_RGDAAC_M4WE_MASK                  (0x1000000U)
#define SYSMPU_RGDAAC_M4WE_SHIFT                 (24U)
/*! M4WE - Bus Master 4 Write Enable
 *  0b0..Bus master 4 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 4 writes allowed
 */
#define SYSMPU_RGDAAC_M4WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M4WE_SHIFT)) & SYSMPU_RGDAAC_M4WE_MASK)

#define SYSMPU_RGDAAC_M4RE_MASK                  (0x2000000U)
#define SYSMPU_RGDAAC_M4RE_SHIFT                 (25U)
/*! M4RE - Bus Master 4 Read Enable
 *  0b0..Bus master 4 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 4 reads allowed
 */
#define SYSMPU_RGDAAC_M4RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M4RE_SHIFT)) & SYSMPU_RGDAAC_M4RE_MASK)

#define SYSMPU_RGDAAC_M5WE_MASK                  (0x4000000U)
#define SYSMPU_RGDAAC_M5WE_SHIFT                 (26U)
/*! M5WE - Bus Master 5 Write Enable
 *  0b0..Bus master 5 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 5 writes allowed
 */
#define SYSMPU_RGDAAC_M5WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M5WE_SHIFT)) & SYSMPU_RGDAAC_M5WE_MASK)

#define SYSMPU_RGDAAC_M5RE_MASK                  (0x8000000U)
#define SYSMPU_RGDAAC_M5RE_SHIFT                 (27U)
/*! M5RE - Bus Master 5 Read Enable
 *  0b0..Bus master 5 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 5 reads allowed
 */
#define SYSMPU_RGDAAC_M5RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M5RE_SHIFT)) & SYSMPU_RGDAAC_M5RE_MASK)

#define SYSMPU_RGDAAC_M6WE_MASK                  (0x10000000U)
#define SYSMPU_RGDAAC_M6WE_SHIFT                 (28U)
/*! M6WE - Bus Master 6 Write Enable
 *  0b0..Bus master 6 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 6 writes allowed
 */
#define SYSMPU_RGDAAC_M6WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M6WE_SHIFT)) & SYSMPU_RGDAAC_M6WE_MASK)

#define SYSMPU_RGDAAC_M6RE_MASK                  (0x20000000U)
#define SYSMPU_RGDAAC_M6RE_SHIFT                 (29U)
/*! M6RE - Bus Master 6 Read Enable
 *  0b0..Bus master 6 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 6 reads allowed
 */
#define SYSMPU_RGDAAC_M6RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M6RE_SHIFT)) & SYSMPU_RGDAAC_M6RE_MASK)

#define SYSMPU_RGDAAC_M7WE_MASK                  (0x40000000U)
#define SYSMPU_RGDAAC_M7WE_SHIFT                 (30U)
/*! M7WE - Bus Master 7 Write Enable
 *  0b0..Bus master 7 writes terminate with an access error and the write is not performed
 *  0b1..Bus master 7 writes allowed
 */
#define SYSMPU_RGDAAC_M7WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M7WE_SHIFT)) & SYSMPU_RGDAAC_M7WE_MASK)

#define SYSMPU_RGDAAC_M7RE_MASK                  (0x80000000U)
#define SYSMPU_RGDAAC_M7RE_SHIFT                 (31U)
/*! M7RE - Bus Master 7 Read Enable
 *  0b0..Bus master 7 reads terminate with an access error and the read is not performed
 *  0b1..Bus master 7 reads allowed
 */
#define SYSMPU_RGDAAC_M7RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M7RE_SHIFT)) & SYSMPU_RGDAAC_M7RE_MASK)
/*! @} */

/* The count of SYSMPU_RGDAAC */
#define SYSMPU_RGDAAC_COUNT                      (8U)


/*!
 * @}
 */ /* end of group SYSMPU_Register_Masks */


/* SYSMPU - Peripheral instance base addresses */
/** Peripheral SYSMPU base address */
#define SYSMPU_BASE                              (0x4000A000u)
/** Peripheral SYSMPU base pointer */
#define SYSMPU                                   ((SYSMPU_Type *)SYSMPU_BASE)
/** Array initializer of SYSMPU peripheral base addresses */
#define SYSMPU_BASE_ADDRS                        { SYSMPU_BASE }
/** Array initializer of SYSMPU peripheral base pointers */
#define SYSMPU_BASE_PTRS                         { SYSMPU }

/*!
 * @}
 */ /* end of group SYSMPU_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- TMR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Peripheral_Access_Layer TMR Peripheral Access Layer
 * @{
 */

/** TMR - Register Layout Typedef */
typedef struct {
  __IO uint16_t COMP1;                             /**< Timer Channel Compare Register 1, offset: 0x0 */
  __IO uint16_t COMP2;                             /**< Timer Channel Compare Register 2, offset: 0x2 */
  __IO uint16_t CAPT;                              /**< Timer Channel Capture Register, offset: 0x4 */
  __IO uint16_t LOAD;                              /**< Timer Channel Load Register, offset: 0x6 */
  __IO uint16_t HOLD;                              /**< Timer Channel Hold Register, offset: 0x8 */
  __IO uint16_t CNTR;                              /**< Timer Channel Counter Register, offset: 0xA */
  __IO uint16_t CTRL;                              /**< Timer Channel Control Register, offset: 0xC */
  __IO uint16_t SCTRL;                             /**< Timer Channel Status and Control Register, offset: 0xE */
  __IO uint16_t CMPLD1;                            /**< Timer Channel Comparator Load Register 1, offset: 0x10 */
  __IO uint16_t CMPLD2;                            /**< Timer Channel Comparator Load Register 2, offset: 0x12 */
  __IO uint16_t CSCTRL;                            /**< Timer Channel Comparator Status and Control Register, offset: 0x14 */
  __IO uint16_t FILT;                              /**< Timer Channel Input Filter Register, offset: 0x16 */
       uint8_t RESERVED_0[6];
  __IO uint16_t ENBL;                              /**< Timer Channel Enable Register, offset: 0x1E */
} TMR_Type;

/* ----------------------------------------------------------------------------
   -- TMR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TMR_Register_Masks TMR Register Masks
 * @{
 */

/*! @name COMP1 - Timer Channel Compare Register 1 */
/*! @{ */

#define TMR_COMP1_COMPARISON_1_MASK              (0xFFFFU)
#define TMR_COMP1_COMPARISON_1_SHIFT             (0U)
/*! COMPARISON_1 - Comparison Value 1
 */
#define TMR_COMP1_COMPARISON_1(x)                (((uint16_t)(((uint16_t)(x)) << TMR_COMP1_COMPARISON_1_SHIFT)) & TMR_COMP1_COMPARISON_1_MASK)
/*! @} */

/*! @name COMP2 - Timer Channel Compare Register 2 */
/*! @{ */

#define TMR_COMP2_COMPARISON_2_MASK              (0xFFFFU)
#define TMR_COMP2_COMPARISON_2_SHIFT             (0U)
/*! COMPARISON_2 - Comparison Value 2
 */
#define TMR_COMP2_COMPARISON_2(x)                (((uint16_t)(((uint16_t)(x)) << TMR_COMP2_COMPARISON_2_SHIFT)) & TMR_COMP2_COMPARISON_2_MASK)
/*! @} */

/*! @name CAPT - Timer Channel Capture Register */
/*! @{ */

#define TMR_CAPT_CAPTURE_MASK                    (0xFFFFU)
#define TMR_CAPT_CAPTURE_SHIFT                   (0U)
/*! CAPTURE - Capture Value
 */
#define TMR_CAPT_CAPTURE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CAPT_CAPTURE_SHIFT)) & TMR_CAPT_CAPTURE_MASK)
/*! @} */

/*! @name LOAD - Timer Channel Load Register */
/*! @{ */

#define TMR_LOAD_LOAD_MASK                       (0xFFFFU)
#define TMR_LOAD_LOAD_SHIFT                      (0U)
/*! LOAD - Timer Load Register
 */
#define TMR_LOAD_LOAD(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_LOAD_LOAD_SHIFT)) & TMR_LOAD_LOAD_MASK)
/*! @} */

/*! @name HOLD - Timer Channel Hold Register */
/*! @{ */

#define TMR_HOLD_HOLD_MASK                       (0xFFFFU)
#define TMR_HOLD_HOLD_SHIFT                      (0U)
#define TMR_HOLD_HOLD(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_HOLD_HOLD_SHIFT)) & TMR_HOLD_HOLD_MASK)
/*! @} */

/*! @name CNTR - Timer Channel Counter Register */
/*! @{ */

#define TMR_CNTR_COUNTER_MASK                    (0xFFFFU)
#define TMR_CNTR_COUNTER_SHIFT                   (0U)
#define TMR_CNTR_COUNTER(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CNTR_COUNTER_SHIFT)) & TMR_CNTR_COUNTER_MASK)
/*! @} */

/*! @name CTRL - Timer Channel Control Register */
/*! @{ */

#define TMR_CTRL_OUTMODE_MASK                    (0x7U)
#define TMR_CTRL_OUTMODE_SHIFT                   (0U)
/*! OUTMODE - Output Mode
 *  0b000..Asserted while counter is active
 *  0b001..Clear OFLAG output on successful compare
 *  0b010..Set OFLAG output on successful compare
 *  0b011..Toggle OFLAG output on successful compare
 *  0b100..Toggle OFLAG output using alternating compare registers
 *  0b101..Set on compare, cleared on secondary source input edge
 *  0b110..Set on compare, cleared on counter rollover
 *  0b111..Enable gated clock output while counter is active
 */
#define TMR_CTRL_OUTMODE(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_OUTMODE_SHIFT)) & TMR_CTRL_OUTMODE_MASK)

#define TMR_CTRL_COINIT_MASK                     (0x8U)
#define TMR_CTRL_COINIT_SHIFT                    (3U)
/*! COINIT - Co-Channel Initialization
 *  0b0..Co-channel counter/timers cannot force a re-initialization of this counter/timer
 *  0b1..Co-channel counter/timers may force a re-initialization of this counter/timer
 */
#define TMR_CTRL_COINIT(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_COINIT_SHIFT)) & TMR_CTRL_COINIT_MASK)

#define TMR_CTRL_DIR_MASK                        (0x10U)
#define TMR_CTRL_DIR_SHIFT                       (4U)
/*! DIR - Count Direction
 *  0b0..Count up.
 *  0b1..Count down.
 */
#define TMR_CTRL_DIR(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_DIR_SHIFT)) & TMR_CTRL_DIR_MASK)

#define TMR_CTRL_LENGTH_MASK                     (0x20U)
#define TMR_CTRL_LENGTH_SHIFT                    (5U)
/*! LENGTH - Count Length
 *  0b0..Roll over.
 *  0b1..Count until compare, then re-initialize. If counting up, a successful compare occurs when the counter
 *       reaches a COMP1 value. If counting down, a successful compare occurs when the counter reaches a COMP2 value.
 *       When output mode $4 is used, alternating values of COMP1 and COMP2 are used to generate successful
 *       comparisons. For example, the counter counts until a COMP1 value is reached, re-initializes, counts until COMP2
 *       value is reached, re-initializes, counts until COMP1 value is reached, and so on.
 */
#define TMR_CTRL_LENGTH(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_LENGTH_SHIFT)) & TMR_CTRL_LENGTH_MASK)

#define TMR_CTRL_ONCE_MASK                       (0x40U)
#define TMR_CTRL_ONCE_SHIFT                      (6U)
/*! ONCE - Count Once
 *  0b0..Count repeatedly.
 *  0b1..Count until compare and then stop. If counting up, a successful compare occurs when the counter reaches a
 *       COMP1 value. If counting down, a successful compare occurs when the counter reaches a COMP2 value. When
 *       output mode $4 is used, the counter re-initializes after reaching the COMP1 value, continues to count to
 *       the COMP2 value, and then stops.
 */
#define TMR_CTRL_ONCE(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_ONCE_SHIFT)) & TMR_CTRL_ONCE_MASK)

#define TMR_CTRL_SCS_MASK                        (0x180U)
#define TMR_CTRL_SCS_SHIFT                       (7U)
/*! SCS - Secondary Count Source
 *  0b00..Counter 0 input pin
 *  0b01..Counter 1 input pin
 *  0b10..Counter 2 input pin
 *  0b11..Counter 3 input pin
 */
#define TMR_CTRL_SCS(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_SCS_SHIFT)) & TMR_CTRL_SCS_MASK)

#define TMR_CTRL_PCS_MASK                        (0x1E00U)
#define TMR_CTRL_PCS_SHIFT                       (9U)
/*! PCS - Primary Count Source
 *  0b0000..Counter 0 input pin
 *  0b0001..Counter 1 input pin
 *  0b0010..Counter 2 input pin
 *  0b0011..Counter 3 input pin
 *  0b0100..Counter 0 output
 *  0b0101..Counter 1 output
 *  0b0110..Counter 2 output
 *  0b0111..Counter 3 output
 *  0b1000..IP bus clock divide by 1 prescaler
 *  0b1001..IP bus clock divide by 2 prescaler
 *  0b1010..IP bus clock divide by 4 prescaler
 *  0b1011..IP bus clock divide by 8 prescaler
 *  0b1100..IP bus clock divide by 16 prescaler
 *  0b1101..IP bus clock divide by 32 prescaler
 *  0b1110..IP bus clock divide by 64 prescaler
 *  0b1111..IP bus clock divide by 128 prescaler
 */
#define TMR_CTRL_PCS(x)                          (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_PCS_SHIFT)) & TMR_CTRL_PCS_MASK)

#define TMR_CTRL_CM_MASK                         (0xE000U)
#define TMR_CTRL_CM_SHIFT                        (13U)
/*! CM - Count Mode
 *  0b000..No operation
 *  0b001..Count rising edges of primary sourceRising edges are counted only when SCTRL[IPS] = 0. Falling edges
 *         are counted when SCTRL[IPS] = 1. If the primary count source is IP bus clock divide by 1, only rising
 *         edges are counted regardless of the value of SCTRL[IPS].
 *  0b010..Count rising and falling edges of primary sourceIP bus clock divide by 1 cannot be used as a primary count source in edge count mode.
 *  0b011..Count rising edges of primary source while secondary input high active
 *  0b100..Quadrature count mode, uses primary and secondary sources
 *  0b101..Count rising edges of primary source; secondary source specifies directionRising edges are counted only
 *         when SCTRL[IPS] = 0. Falling edges are counted when SCTRL[IPS] = 1.
 *  0b110..Edge of secondary source triggers primary count until compare
 *  0b111..Cascaded counter mode (up/down)The primary count source must be set to one of the counter outputs.
 */
#define TMR_CTRL_CM(x)                           (((uint16_t)(((uint16_t)(x)) << TMR_CTRL_CM_SHIFT)) & TMR_CTRL_CM_MASK)
/*! @} */

/*! @name SCTRL - Timer Channel Status and Control Register */
/*! @{ */

#define TMR_SCTRL_OEN_MASK                       (0x1U)
#define TMR_SCTRL_OEN_SHIFT                      (0U)
/*! OEN - Output Enable
 *  0b0..The external pin is configured as an input.
 *  0b1..The OFLAG output signal is driven on the external pin. Other timer groups using this external pin as
 *       their input see the driven value. The polarity of the signal is determined by OPS.
 */
#define TMR_SCTRL_OEN(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_OEN_SHIFT)) & TMR_SCTRL_OEN_MASK)

#define TMR_SCTRL_OPS_MASK                       (0x2U)
#define TMR_SCTRL_OPS_SHIFT                      (1U)
/*! OPS - Output Polarity Select
 *  0b0..True polarity.
 *  0b1..Inverted polarity.
 */
#define TMR_SCTRL_OPS(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_OPS_SHIFT)) & TMR_SCTRL_OPS_MASK)

#define TMR_SCTRL_FORCE_MASK                     (0x4U)
#define TMR_SCTRL_FORCE_SHIFT                    (2U)
/*! FORCE - Force OFLAG Output
 */
#define TMR_SCTRL_FORCE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_FORCE_SHIFT)) & TMR_SCTRL_FORCE_MASK)

#define TMR_SCTRL_VAL_MASK                       (0x8U)
#define TMR_SCTRL_VAL_SHIFT                      (3U)
/*! VAL - Forced OFLAG Value
 */
#define TMR_SCTRL_VAL(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_VAL_SHIFT)) & TMR_SCTRL_VAL_MASK)

#define TMR_SCTRL_EEOF_MASK                      (0x10U)
#define TMR_SCTRL_EEOF_SHIFT                     (4U)
/*! EEOF - Enable External OFLAG Force
 */
#define TMR_SCTRL_EEOF(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_EEOF_SHIFT)) & TMR_SCTRL_EEOF_MASK)

#define TMR_SCTRL_MSTR_MASK                      (0x20U)
#define TMR_SCTRL_MSTR_SHIFT                     (5U)
/*! MSTR - Master Mode
 */
#define TMR_SCTRL_MSTR(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_MSTR_SHIFT)) & TMR_SCTRL_MSTR_MASK)

#define TMR_SCTRL_CAPTURE_MODE_MASK              (0xC0U)
#define TMR_SCTRL_CAPTURE_MODE_SHIFT             (6U)
/*! CAPTURE_MODE - Input Capture Mode
 *  0b00..Capture function is disabled
 *  0b01..Load capture register on rising edge (when IPS=0) or falling edge (when IPS=1) of input
 *  0b10..Load capture register on falling edge (when IPS=0) or rising edge (when IPS=1) of input
 *  0b11..Load capture register on both edges of input
 */
#define TMR_SCTRL_CAPTURE_MODE(x)                (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_CAPTURE_MODE_SHIFT)) & TMR_SCTRL_CAPTURE_MODE_MASK)

#define TMR_SCTRL_INPUT_MASK                     (0x100U)
#define TMR_SCTRL_INPUT_SHIFT                    (8U)
/*! INPUT - External Input Signal
 */
#define TMR_SCTRL_INPUT(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_INPUT_SHIFT)) & TMR_SCTRL_INPUT_MASK)

#define TMR_SCTRL_IPS_MASK                       (0x200U)
#define TMR_SCTRL_IPS_SHIFT                      (9U)
/*! IPS - Input Polarity Select
 */
#define TMR_SCTRL_IPS(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IPS_SHIFT)) & TMR_SCTRL_IPS_MASK)

#define TMR_SCTRL_IEFIE_MASK                     (0x400U)
#define TMR_SCTRL_IEFIE_SHIFT                    (10U)
/*! IEFIE - Input Edge Flag Interrupt Enable
 */
#define TMR_SCTRL_IEFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IEFIE_SHIFT)) & TMR_SCTRL_IEFIE_MASK)

#define TMR_SCTRL_IEF_MASK                       (0x800U)
#define TMR_SCTRL_IEF_SHIFT                      (11U)
/*! IEF - Input Edge Flag
 */
#define TMR_SCTRL_IEF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_IEF_SHIFT)) & TMR_SCTRL_IEF_MASK)

#define TMR_SCTRL_TOFIE_MASK                     (0x1000U)
#define TMR_SCTRL_TOFIE_SHIFT                    (12U)
/*! TOFIE - Timer Overflow Flag Interrupt Enable
 */
#define TMR_SCTRL_TOFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TOFIE_SHIFT)) & TMR_SCTRL_TOFIE_MASK)

#define TMR_SCTRL_TOF_MASK                       (0x2000U)
#define TMR_SCTRL_TOF_SHIFT                      (13U)
/*! TOF - Timer Overflow Flag
 */
#define TMR_SCTRL_TOF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TOF_SHIFT)) & TMR_SCTRL_TOF_MASK)

#define TMR_SCTRL_TCFIE_MASK                     (0x4000U)
#define TMR_SCTRL_TCFIE_SHIFT                    (14U)
/*! TCFIE - Timer Compare Flag Interrupt Enable
 */
#define TMR_SCTRL_TCFIE(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TCFIE_SHIFT)) & TMR_SCTRL_TCFIE_MASK)

#define TMR_SCTRL_TCF_MASK                       (0x8000U)
#define TMR_SCTRL_TCF_SHIFT                      (15U)
/*! TCF - Timer Compare Flag
 */
#define TMR_SCTRL_TCF(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_SCTRL_TCF_SHIFT)) & TMR_SCTRL_TCF_MASK)
/*! @} */

/*! @name CMPLD1 - Timer Channel Comparator Load Register 1 */
/*! @{ */

#define TMR_CMPLD1_COMPARATOR_LOAD_1_MASK        (0xFFFFU)
#define TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT       (0U)
#define TMR_CMPLD1_COMPARATOR_LOAD_1(x)          (((uint16_t)(((uint16_t)(x)) << TMR_CMPLD1_COMPARATOR_LOAD_1_SHIFT)) & TMR_CMPLD1_COMPARATOR_LOAD_1_MASK)
/*! @} */

/*! @name CMPLD2 - Timer Channel Comparator Load Register 2 */
/*! @{ */

#define TMR_CMPLD2_COMPARATOR_LOAD_2_MASK        (0xFFFFU)
#define TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT       (0U)
#define TMR_CMPLD2_COMPARATOR_LOAD_2(x)          (((uint16_t)(((uint16_t)(x)) << TMR_CMPLD2_COMPARATOR_LOAD_2_SHIFT)) & TMR_CMPLD2_COMPARATOR_LOAD_2_MASK)
/*! @} */

/*! @name CSCTRL - Timer Channel Comparator Status and Control Register */
/*! @{ */

#define TMR_CSCTRL_CL1_MASK                      (0x3U)
#define TMR_CSCTRL_CL1_SHIFT                     (0U)
/*! CL1 - Compare Load Control 1
 *  0b00..Never preload
 *  0b01..Load upon successful compare with the value in COMP1
 *  0b10..Load upon successful compare with the value in COMP2
 *  0b11..Reserved
 */
#define TMR_CSCTRL_CL1(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_CL1_SHIFT)) & TMR_CSCTRL_CL1_MASK)

#define TMR_CSCTRL_CL2_MASK                      (0xCU)
#define TMR_CSCTRL_CL2_SHIFT                     (2U)
/*! CL2 - Compare Load Control 2
 *  0b00..Never preload
 *  0b01..Load upon successful compare with the value in COMP1
 *  0b10..Load upon successful compare with the value in COMP2
 *  0b11..Reserved
 */
#define TMR_CSCTRL_CL2(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_CL2_SHIFT)) & TMR_CSCTRL_CL2_MASK)

#define TMR_CSCTRL_TCF1_MASK                     (0x10U)
#define TMR_CSCTRL_TCF1_SHIFT                    (4U)
/*! TCF1 - Timer Compare 1 Interrupt Flag
 */
#define TMR_CSCTRL_TCF1(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF1_SHIFT)) & TMR_CSCTRL_TCF1_MASK)

#define TMR_CSCTRL_TCF2_MASK                     (0x20U)
#define TMR_CSCTRL_TCF2_SHIFT                    (5U)
/*! TCF2 - Timer Compare 2 Interrupt Flag
 */
#define TMR_CSCTRL_TCF2(x)                       (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF2_SHIFT)) & TMR_CSCTRL_TCF2_MASK)

#define TMR_CSCTRL_TCF1EN_MASK                   (0x40U)
#define TMR_CSCTRL_TCF1EN_SHIFT                  (6U)
/*! TCF1EN - Timer Compare 1 Interrupt Enable
 */
#define TMR_CSCTRL_TCF1EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF1EN_SHIFT)) & TMR_CSCTRL_TCF1EN_MASK)

#define TMR_CSCTRL_TCF2EN_MASK                   (0x80U)
#define TMR_CSCTRL_TCF2EN_SHIFT                  (7U)
/*! TCF2EN - Timer Compare 2 Interrupt Enable
 */
#define TMR_CSCTRL_TCF2EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCF2EN_SHIFT)) & TMR_CSCTRL_TCF2EN_MASK)

#define TMR_CSCTRL_UP_MASK                       (0x200U)
#define TMR_CSCTRL_UP_SHIFT                      (9U)
/*! UP - Counting Direction Indicator
 *  0b0..The last count was in the DOWN direction.
 *  0b1..The last count was in the UP direction.
 */
#define TMR_CSCTRL_UP(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_UP_SHIFT)) & TMR_CSCTRL_UP_MASK)

#define TMR_CSCTRL_TCI_MASK                      (0x400U)
#define TMR_CSCTRL_TCI_SHIFT                     (10U)
/*! TCI - Triggered Count Initialization Control
 *  0b0..Stop counter upon receiving a second trigger event while still counting from the first trigger event.
 *  0b1..Reload the counter upon receiving a second trigger event while still counting from the first trigger event.
 */
#define TMR_CSCTRL_TCI(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_TCI_SHIFT)) & TMR_CSCTRL_TCI_MASK)

#define TMR_CSCTRL_ROC_MASK                      (0x800U)
#define TMR_CSCTRL_ROC_SHIFT                     (11U)
/*! ROC - Reload on Capture
 *  0b0..Do not reload the counter on a capture event.
 *  0b1..Reload the counter on a capture event.
 */
#define TMR_CSCTRL_ROC(x)                        (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_ROC_SHIFT)) & TMR_CSCTRL_ROC_MASK)

#define TMR_CSCTRL_ALT_LOAD_MASK                 (0x1000U)
#define TMR_CSCTRL_ALT_LOAD_SHIFT                (12U)
/*! ALT_LOAD - Alternative Load Enable
 *  0b0..Counter can be re-initialized only with the LOAD register.
 *  0b1..Counter can be re-initialized with the LOAD or CMPLD2 registers depending on count direction.
 */
#define TMR_CSCTRL_ALT_LOAD(x)                   (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_ALT_LOAD_SHIFT)) & TMR_CSCTRL_ALT_LOAD_MASK)

#define TMR_CSCTRL_FAULT_MASK                    (0x2000U)
#define TMR_CSCTRL_FAULT_SHIFT                   (13U)
/*! FAULT - Fault Enable
 *  0b0..Fault function disabled.
 *  0b1..Fault function enabled.
 */
#define TMR_CSCTRL_FAULT(x)                      (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_FAULT_SHIFT)) & TMR_CSCTRL_FAULT_MASK)

#define TMR_CSCTRL_DBG_EN_MASK                   (0xC000U)
#define TMR_CSCTRL_DBG_EN_SHIFT                  (14U)
/*! DBG_EN - Debug Actions Enable
 *  0b00..Continue with normal operation during debug mode. (default)
 *  0b01..Halt TMR counter during debug mode.
 *  0b10..Force TMR output to logic 0 (prior to consideration of SCTRL[OPS]).
 *  0b11..Both halt counter and force output to 0 during debug mode.
 */
#define TMR_CSCTRL_DBG_EN(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_CSCTRL_DBG_EN_SHIFT)) & TMR_CSCTRL_DBG_EN_MASK)
/*! @} */

/*! @name FILT - Timer Channel Input Filter Register */
/*! @{ */

#define TMR_FILT_FILT_PER_MASK                   (0xFFU)
#define TMR_FILT_FILT_PER_SHIFT                  (0U)
/*! FILT_PER - Input Filter Sample Period
 */
#define TMR_FILT_FILT_PER(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_FILT_FILT_PER_SHIFT)) & TMR_FILT_FILT_PER_MASK)

#define TMR_FILT_FILT_CNT_MASK                   (0x700U)
#define TMR_FILT_FILT_CNT_SHIFT                  (8U)
/*! FILT_CNT - Input Filter Sample Count
 */
#define TMR_FILT_FILT_CNT(x)                     (((uint16_t)(((uint16_t)(x)) << TMR_FILT_FILT_CNT_SHIFT)) & TMR_FILT_FILT_CNT_MASK)
/*! @} */

/*! @name ENBL - Timer Channel Enable Register */
/*! @{ */

#define TMR_ENBL_ENBL_MASK                       (0xFU)
#define TMR_ENBL_ENBL_SHIFT                      (0U)
/*! ENBL - Timer Channel Enable
 *  0b0000..Timer channel is disabled.
 *  0b0001..Timer channel is enabled. (default)
 */
#define TMR_ENBL_ENBL(x)                         (((uint16_t)(((uint16_t)(x)) << TMR_ENBL_ENBL_SHIFT)) & TMR_ENBL_ENBL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group TMR_Register_Masks */


/* TMR - Peripheral instance base addresses */
/** Peripheral TMR0 base address */
#define TMR0_BASE                                (0x40057000u)
/** Peripheral TMR0 base pointer */
#define TMR0                                     ((TMR_Type *)TMR0_BASE)
/** Peripheral TMR1 base address */
#define TMR1_BASE                                (0x40058000u)
/** Peripheral TMR1 base pointer */
#define TMR1                                     ((TMR_Type *)TMR1_BASE)
/** Peripheral TMR2 base address */
#define TMR2_BASE                                (0x40059000u)
/** Peripheral TMR2 base pointer */
#define TMR2                                     ((TMR_Type *)TMR2_BASE)
/** Peripheral TMR3 base address */
#define TMR3_BASE                                (0x4005A000u)
/** Peripheral TMR3 base pointer */
#define TMR3                                     ((TMR_Type *)TMR3_BASE)
/** Array initializer of TMR peripheral base addresses */
#define TMR_BASE_ADDRS                           { TMR0_BASE, TMR1_BASE, TMR2_BASE, TMR3_BASE }
/** Array initializer of TMR peripheral base pointers */
#define TMR_BASE_PTRS                            { TMR0, TMR1, TMR2, TMR3 }
/** Interrupt vectors for the TMR peripheral type */
#define TMR_IRQS                                 { TMR0_IRQn, TMR1_IRQn, TMR2_IRQn, TMR3_IRQn }

/*!
 * @}
 */ /* end of group TMR_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- UART Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Peripheral_Access_Layer UART Peripheral Access Layer
 * @{
 */

/** UART - Register Layout Typedef */
typedef struct {
  __IO uint8_t BDH;                                /**< UART Baud Rate Registers: High, offset: 0x0 */
  __IO uint8_t BDL;                                /**< UART Baud Rate Registers: Low, offset: 0x1 */
  __IO uint8_t C1;                                 /**< UART Control Register 1, offset: 0x2 */
  __IO uint8_t C2;                                 /**< UART Control Register 2, offset: 0x3 */
  __I  uint8_t S1;                                 /**< UART Status Register 1, offset: 0x4 */
  __IO uint8_t S2;                                 /**< UART Status Register 2, offset: 0x5 */
  __IO uint8_t C3;                                 /**< UART Control Register 3, offset: 0x6 */
  __IO uint8_t D;                                  /**< UART Data Register, offset: 0x7 */
  __IO uint8_t MA1;                                /**< UART Match Address Registers 1, offset: 0x8 */
  __IO uint8_t MA2;                                /**< UART Match Address Registers 2, offset: 0x9 */
  __IO uint8_t C4;                                 /**< UART Control Register 4, offset: 0xA */
  __IO uint8_t C5;                                 /**< UART Control Register 5, offset: 0xB */
  __I  uint8_t ED;                                 /**< UART Extended Data Register, offset: 0xC */
  __IO uint8_t MODEM;                              /**< UART Modem Register, offset: 0xD */
       uint8_t RESERVED_0[2];
  __IO uint8_t PFIFO;                              /**< UART FIFO Parameters, offset: 0x10 */
  __IO uint8_t CFIFO;                              /**< UART FIFO Control Register, offset: 0x11 */
  __IO uint8_t SFIFO;                              /**< UART FIFO Status Register, offset: 0x12 */
  __IO uint8_t TWFIFO;                             /**< UART FIFO Transmit Watermark, offset: 0x13 */
  __I  uint8_t TCFIFO;                             /**< UART FIFO Transmit Count, offset: 0x14 */
  __IO uint8_t RWFIFO;                             /**< UART FIFO Receive Watermark, offset: 0x15 */
  __I  uint8_t RCFIFO;                             /**< UART FIFO Receive Count, offset: 0x16 */
       uint8_t RESERVED_1[1];
  __IO uint8_t C7816;                              /**< UART 7816 Control Register, offset: 0x18 */
  __IO uint8_t IE7816;                             /**< UART 7816 Interrupt Enable Register, offset: 0x19 */
  __IO uint8_t IS7816;                             /**< UART 7816 Interrupt Status Register, offset: 0x1A */
  union {                                          /* offset: 0x1B */
    __IO uint8_t WP7816T0;                           /**< UART 7816 Wait Parameter Register, offset: 0x1B */
    __IO uint8_t WP7816T1;                           /**< UART 7816 Wait Parameter Register, offset: 0x1B */
  };
  __IO uint8_t WN7816;                             /**< UART 7816 Wait N Register, offset: 0x1C */
  __IO uint8_t WF7816;                             /**< UART 7816 Wait FD Register, offset: 0x1D */
  __IO uint8_t ET7816;                             /**< UART 7816 Error Threshold Register, offset: 0x1E */
  __IO uint8_t TL7816;                             /**< UART 7816 Transmit Length Register, offset: 0x1F */
} UART_Type;

/* ----------------------------------------------------------------------------
   -- UART Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup UART_Register_Masks UART Register Masks
 * @{
 */

/*! @name BDH - UART Baud Rate Registers: High */
/*! @{ */

#define UART_BDH_SBR_MASK                        (0x1FU)
#define UART_BDH_SBR_SHIFT                       (0U)
/*! SBR - UART Baud Rate Bits
 */
#define UART_BDH_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDH_SBR_SHIFT)) & UART_BDH_SBR_MASK)

#define UART_BDH_RXEDGIE_MASK                    (0x40U)
#define UART_BDH_RXEDGIE_SHIFT                   (6U)
/*! RXEDGIE - RxD Input Active Edge Interrupt Enable
 *  0b0..Hardware interrupts from RXEDGIF disabled using polling.
 *  0b1..RXEDGIF interrupt request enabled.
 */
#define UART_BDH_RXEDGIE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_BDH_RXEDGIE_SHIFT)) & UART_BDH_RXEDGIE_MASK)
/*! @} */

/*! @name BDL - UART Baud Rate Registers: Low */
/*! @{ */

#define UART_BDL_SBR_MASK                        (0xFFU)
#define UART_BDL_SBR_SHIFT                       (0U)
/*! SBR - UART Baud Rate Bits
 */
#define UART_BDL_SBR(x)                          (((uint8_t)(((uint8_t)(x)) << UART_BDL_SBR_SHIFT)) & UART_BDL_SBR_MASK)
/*! @} */

/*! @name C1 - UART Control Register 1 */
/*! @{ */

#define UART_C1_PT_MASK                          (0x1U)
#define UART_C1_PT_SHIFT                         (0U)
/*! PT - Parity Type
 *  0b0..Even parity.
 *  0b1..Odd parity.
 */
#define UART_C1_PT(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PT_SHIFT)) & UART_C1_PT_MASK)

#define UART_C1_PE_MASK                          (0x2U)
#define UART_C1_PE_SHIFT                         (1U)
/*! PE - Parity Enable
 *  0b0..Parity function disabled.
 *  0b1..Parity function enabled.
 */
#define UART_C1_PE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C1_PE_SHIFT)) & UART_C1_PE_MASK)

#define UART_C1_ILT_MASK                         (0x4U)
#define UART_C1_ILT_SHIFT                        (2U)
/*! ILT - Idle Line Type Select
 *  0b0..Idle character bit count starts after start bit.
 *  0b1..Idle character bit count starts after stop bit.
 */
#define UART_C1_ILT(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C1_ILT_SHIFT)) & UART_C1_ILT_MASK)

#define UART_C1_WAKE_MASK                        (0x8U)
#define UART_C1_WAKE_SHIFT                       (3U)
/*! WAKE - Receiver Wakeup Method Select
 *  0b0..Idle line wakeup.
 *  0b1..Address mark wakeup.
 */
#define UART_C1_WAKE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_WAKE_SHIFT)) & UART_C1_WAKE_MASK)

#define UART_C1_M_MASK                           (0x10U)
#define UART_C1_M_SHIFT                          (4U)
/*! M - 9-bit or 8-bit Mode Select
 *  0b0..Normal-start + 8 data bits (MSB/LSB first as determined by MSBF) + stop.
 *  0b1..Use-start + 9 data bits (MSB/LSB first as determined by MSBF) + stop.
 */
#define UART_C1_M(x)                             (((uint8_t)(((uint8_t)(x)) << UART_C1_M_SHIFT)) & UART_C1_M_MASK)

#define UART_C1_RSRC_MASK                        (0x20U)
#define UART_C1_RSRC_SHIFT                       (5U)
/*! RSRC - Receiver Source Select
 *  0b0..Selects internal loop back mode. The receiver input is internally connected to transmitter output.
 *  0b1..Single wire UART mode where the receiver input is connected to the transmit pin input signal.
 */
#define UART_C1_RSRC(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C1_RSRC_SHIFT)) & UART_C1_RSRC_MASK)

#define UART_C1_LOOPS_MASK                       (0x80U)
#define UART_C1_LOOPS_SHIFT                      (7U)
/*! LOOPS - Loop Mode Select
 *  0b0..Normal operation.
 *  0b1..Loop mode where transmitter output is internally connected to receiver input. The receiver input is determined by RSRC.
 */
#define UART_C1_LOOPS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C1_LOOPS_SHIFT)) & UART_C1_LOOPS_MASK)
/*! @} */

/*! @name C2 - UART Control Register 2 */
/*! @{ */

#define UART_C2_SBK_MASK                         (0x1U)
#define UART_C2_SBK_SHIFT                        (0U)
/*! SBK - Send Break
 *  0b0..Normal transmitter operation.
 *  0b1..Queue break characters to be sent.
 */
#define UART_C2_SBK(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_SBK_SHIFT)) & UART_C2_SBK_MASK)

#define UART_C2_RWU_MASK                         (0x2U)
#define UART_C2_RWU_SHIFT                        (1U)
/*! RWU - Receiver Wakeup Control
 *  0b0..Normal operation.
 *  0b1..RWU enables the wakeup function and inhibits further receiver interrupt requests. Normally, hardware
 *       wakes the receiver by automatically clearing RWU.
 */
#define UART_C2_RWU(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RWU_SHIFT)) & UART_C2_RWU_MASK)

#define UART_C2_RE_MASK                          (0x4U)
#define UART_C2_RE_SHIFT                         (2U)
/*! RE - Receiver Enable
 *  0b0..Receiver off.
 *  0b1..Receiver on.
 */
#define UART_C2_RE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_RE_SHIFT)) & UART_C2_RE_MASK)

#define UART_C2_TE_MASK                          (0x8U)
#define UART_C2_TE_SHIFT                         (3U)
/*! TE - Transmitter Enable
 *  0b0..Transmitter off.
 *  0b1..Transmitter on.
 */
#define UART_C2_TE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C2_TE_SHIFT)) & UART_C2_TE_MASK)

#define UART_C2_ILIE_MASK                        (0x10U)
#define UART_C2_ILIE_SHIFT                       (4U)
/*! ILIE - Idle Line Interrupt Enable
 *  0b0..IDLE interrupt requests disabled.
 *  0b1..IDLE interrupt requests enabled.
 */
#define UART_C2_ILIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_ILIE_SHIFT)) & UART_C2_ILIE_MASK)

#define UART_C2_RIE_MASK                         (0x20U)
#define UART_C2_RIE_SHIFT                        (5U)
/*! RIE - Receiver Full Interrupt or DMA Transfer Enable
 *  0b0..RDRF interrupt and DMA transfer requests disabled.
 *  0b1..RDRF interrupt or DMA transfer requests enabled.
 */
#define UART_C2_RIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_RIE_SHIFT)) & UART_C2_RIE_MASK)

#define UART_C2_TCIE_MASK                        (0x40U)
#define UART_C2_TCIE_SHIFT                       (6U)
/*! TCIE - Transmission Complete Interrupt Enable
 *  0b0..TC interrupt requests disabled.
 *  0b1..TC interrupt requests enabled.
 */
#define UART_C2_TCIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C2_TCIE_SHIFT)) & UART_C2_TCIE_MASK)

#define UART_C2_TIE_MASK                         (0x80U)
#define UART_C2_TIE_SHIFT                        (7U)
/*! TIE - Transmitter Interrupt or DMA Transfer Enable.
 *  0b0..TDRE interrupt and DMA transfer requests disabled.
 *  0b1..TDRE interrupt or DMA transfer requests enabled.
 */
#define UART_C2_TIE(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C2_TIE_SHIFT)) & UART_C2_TIE_MASK)
/*! @} */

/*! @name S1 - UART Status Register 1 */
/*! @{ */

#define UART_S1_PF_MASK                          (0x1U)
#define UART_S1_PF_SHIFT                         (0U)
/*! PF - Parity Error Flag
 *  0b0..No parity error detected since the last time this flag was cleared. If the receive buffer has a depth
 *       greater than 1, then there may be data in the receive buffer what was received with a parity error.
 *  0b1..At least one dataword was received with a parity error since the last time this flag was cleared.
 */
#define UART_S1_PF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_PF_SHIFT)) & UART_S1_PF_MASK)

#define UART_S1_FE_MASK                          (0x2U)
#define UART_S1_FE_SHIFT                         (1U)
/*! FE - Framing Error Flag
 *  0b0..No framing error detected.
 *  0b1..Framing error.
 */
#define UART_S1_FE(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_FE_SHIFT)) & UART_S1_FE_MASK)

#define UART_S1_NF_MASK                          (0x4U)
#define UART_S1_NF_SHIFT                         (2U)
/*! NF - Noise Flag
 *  0b0..No noise detected since the last time this flag was cleared. If the receive buffer has a depth greater
 *       than 1 then there may be data in the receiver buffer that was received with noise.
 *  0b1..At least one dataword was received with noise detected since the last time the flag was cleared.
 */
#define UART_S1_NF(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_NF_SHIFT)) & UART_S1_NF_MASK)

#define UART_S1_OR_MASK                          (0x8U)
#define UART_S1_OR_SHIFT                         (3U)
/*! OR - Receiver Overrun Flag
 *  0b0..No overrun has occurred since the last time the flag was cleared.
 *  0b1..Overrun has occurred or the overrun flag has not been cleared since the last overrun occured.
 */
#define UART_S1_OR(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_OR_SHIFT)) & UART_S1_OR_MASK)

#define UART_S1_IDLE_MASK                        (0x10U)
#define UART_S1_IDLE_SHIFT                       (4U)
/*! IDLE - Idle Line Flag
 *  0b0..Receiver input is either active now or has never become active since the IDLE flag was last cleared.
 *  0b1..Receiver input has become idle or the flag has not been cleared since it last asserted.
 */
#define UART_S1_IDLE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_IDLE_SHIFT)) & UART_S1_IDLE_MASK)

#define UART_S1_RDRF_MASK                        (0x20U)
#define UART_S1_RDRF_SHIFT                       (5U)
/*! RDRF - Receive Data Register Full Flag
 *  0b0..The number of datawords in the receive buffer is less than the number indicated by RXWATER.
 *  0b1..The number of datawords in the receive buffer is equal to or greater than the number indicated by RXWATER
 *       at some point in time since this flag was last cleared.
 */
#define UART_S1_RDRF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_RDRF_SHIFT)) & UART_S1_RDRF_MASK)

#define UART_S1_TC_MASK                          (0x40U)
#define UART_S1_TC_SHIFT                         (6U)
/*! TC - Transmit Complete Flag
 *  0b0..Transmitter active (sending data, a preamble, or a break).
 *  0b1..Transmitter idle (transmission activity complete).
 */
#define UART_S1_TC(x)                            (((uint8_t)(((uint8_t)(x)) << UART_S1_TC_SHIFT)) & UART_S1_TC_MASK)

#define UART_S1_TDRE_MASK                        (0x80U)
#define UART_S1_TDRE_SHIFT                       (7U)
/*! TDRE - Transmit Data Register Empty Flag
 *  0b0..The amount of data in the transmit buffer is greater than the value indicated by TWFIFO[TXWATER].
 *  0b1..The amount of data in the transmit buffer is less than or equal to the value indicated by TWFIFO[TXWATER]
 *       at some point in time since the flag has been cleared.
 */
#define UART_S1_TDRE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S1_TDRE_SHIFT)) & UART_S1_TDRE_MASK)
/*! @} */

/*! @name S2 - UART Status Register 2 */
/*! @{ */

#define UART_S2_RAF_MASK                         (0x1U)
#define UART_S2_RAF_SHIFT                        (0U)
/*! RAF - Receiver Active Flag
 *  0b0..UART receiver idle/inactive waiting for a start bit.
 *  0b1..UART receiver active, RxD input not idle.
 */
#define UART_S2_RAF(x)                           (((uint8_t)(((uint8_t)(x)) << UART_S2_RAF_SHIFT)) & UART_S2_RAF_MASK)

#define UART_S2_BRK13_MASK                       (0x4U)
#define UART_S2_BRK13_SHIFT                      (2U)
/*! BRK13 - Break Transmit Character Length
 *  0b0..Break character is 10, 11, or 12 bits long.
 *  0b1..Break character is 13 or 14 bits long.
 */
#define UART_S2_BRK13(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_BRK13_SHIFT)) & UART_S2_BRK13_MASK)

#define UART_S2_RWUID_MASK                       (0x8U)
#define UART_S2_RWUID_SHIFT                      (3U)
/*! RWUID - Receive Wakeup Idle Detect
 *  0b0..S1[IDLE] is not set upon detection of an idle character.
 *  0b1..S1[IDLE] is set upon detection of an idle character.
 */
#define UART_S2_RWUID(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RWUID_SHIFT)) & UART_S2_RWUID_MASK)

#define UART_S2_RXINV_MASK                       (0x10U)
#define UART_S2_RXINV_SHIFT                      (4U)
/*! RXINV - Receive Data Inversion
 *  0b0..Receive data is not inverted.
 *  0b1..Receive data is inverted.
 */
#define UART_S2_RXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_S2_RXINV_SHIFT)) & UART_S2_RXINV_MASK)

#define UART_S2_MSBF_MASK                        (0x20U)
#define UART_S2_MSBF_SHIFT                       (5U)
/*! MSBF - Most Significant Bit First
 *  0b0..LSB (bit0) is the first bit that is transmitted following the start bit. Further, the first bit received
 *       after the start bit is identified as bit0.
 *  0b1..MSB (bit8, bit7 or bit6) is the first bit that is transmitted following the start bit, depending on the
 *       setting of C1[M] and C1[PE]. Further, the first bit received after the start bit is identified as bit8,
 *       bit7, or bit6, depending on the setting of C1[M] and C1[PE].
 */
#define UART_S2_MSBF(x)                          (((uint8_t)(((uint8_t)(x)) << UART_S2_MSBF_SHIFT)) & UART_S2_MSBF_MASK)

#define UART_S2_RXEDGIF_MASK                     (0x40U)
#define UART_S2_RXEDGIF_SHIFT                    (6U)
/*! RXEDGIF - RxD Pin Active Edge Interrupt Flag
 *  0b0..No active edge on the receive pin has occurred.
 *  0b1..An active edge on the receive pin has occurred.
 */
#define UART_S2_RXEDGIF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_S2_RXEDGIF_SHIFT)) & UART_S2_RXEDGIF_MASK)
/*! @} */

/*! @name C3 - UART Control Register 3 */
/*! @{ */

#define UART_C3_PEIE_MASK                        (0x1U)
#define UART_C3_PEIE_SHIFT                       (0U)
/*! PEIE - Parity Error Interrupt Enable
 *  0b0..PF interrupt requests are disabled.
 *  0b1..PF interrupt requests are enabled.
 */
#define UART_C3_PEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_PEIE_SHIFT)) & UART_C3_PEIE_MASK)

#define UART_C3_FEIE_MASK                        (0x2U)
#define UART_C3_FEIE_SHIFT                       (1U)
/*! FEIE - Framing Error Interrupt Enable
 *  0b0..FE interrupt requests are disabled.
 *  0b1..FE interrupt requests are enabled.
 */
#define UART_C3_FEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_FEIE_SHIFT)) & UART_C3_FEIE_MASK)

#define UART_C3_NEIE_MASK                        (0x4U)
#define UART_C3_NEIE_SHIFT                       (2U)
/*! NEIE - Noise Error Interrupt Enable
 *  0b0..NF interrupt requests are disabled.
 *  0b1..NF interrupt requests are enabled.
 */
#define UART_C3_NEIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_NEIE_SHIFT)) & UART_C3_NEIE_MASK)

#define UART_C3_ORIE_MASK                        (0x8U)
#define UART_C3_ORIE_SHIFT                       (3U)
/*! ORIE - Overrun Error Interrupt Enable
 *  0b0..OR interrupts are disabled.
 *  0b1..OR interrupt requests are enabled.
 */
#define UART_C3_ORIE(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C3_ORIE_SHIFT)) & UART_C3_ORIE_MASK)

#define UART_C3_TXINV_MASK                       (0x10U)
#define UART_C3_TXINV_SHIFT                      (4U)
/*! TXINV - Transmit Data Inversion.
 *  0b0..Transmit data is not inverted.
 *  0b1..Transmit data is inverted.
 */
#define UART_C3_TXINV(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXINV_SHIFT)) & UART_C3_TXINV_MASK)

#define UART_C3_TXDIR_MASK                       (0x20U)
#define UART_C3_TXDIR_SHIFT                      (5U)
/*! TXDIR - Transmitter Pin Data Direction in Single-Wire mode
 *  0b0..TXD pin is an input in single wire mode.
 *  0b1..TXD pin is an output in single wire mode.
 */
#define UART_C3_TXDIR(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C3_TXDIR_SHIFT)) & UART_C3_TXDIR_MASK)

#define UART_C3_T8_MASK                          (0x40U)
#define UART_C3_T8_SHIFT                         (6U)
/*! T8 - Transmit Bit 8
 */
#define UART_C3_T8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_T8_SHIFT)) & UART_C3_T8_MASK)

#define UART_C3_R8_MASK                          (0x80U)
#define UART_C3_R8_SHIFT                         (7U)
/*! R8 - Received Bit 8
 */
#define UART_C3_R8(x)                            (((uint8_t)(((uint8_t)(x)) << UART_C3_R8_SHIFT)) & UART_C3_R8_MASK)
/*! @} */

/*! @name D - UART Data Register */
/*! @{ */

#define UART_D_RT_MASK                           (0xFFU)
#define UART_D_RT_SHIFT                          (0U)
#define UART_D_RT(x)                             (((uint8_t)(((uint8_t)(x)) << UART_D_RT_SHIFT)) & UART_D_RT_MASK)
/*! @} */

/*! @name MA1 - UART Match Address Registers 1 */
/*! @{ */

#define UART_MA1_MA_MASK                         (0xFFU)
#define UART_MA1_MA_SHIFT                        (0U)
/*! MA - Match Address
 */
#define UART_MA1_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA1_MA_SHIFT)) & UART_MA1_MA_MASK)
/*! @} */

/*! @name MA2 - UART Match Address Registers 2 */
/*! @{ */

#define UART_MA2_MA_MASK                         (0xFFU)
#define UART_MA2_MA_SHIFT                        (0U)
/*! MA - Match Address
 */
#define UART_MA2_MA(x)                           (((uint8_t)(((uint8_t)(x)) << UART_MA2_MA_SHIFT)) & UART_MA2_MA_MASK)
/*! @} */

/*! @name C4 - UART Control Register 4 */
/*! @{ */

#define UART_C4_BRFA_MASK                        (0x1FU)
#define UART_C4_BRFA_SHIFT                       (0U)
/*! BRFA - Baud Rate Fine Adjust
 */
#define UART_C4_BRFA(x)                          (((uint8_t)(((uint8_t)(x)) << UART_C4_BRFA_SHIFT)) & UART_C4_BRFA_MASK)

#define UART_C4_M10_MASK                         (0x20U)
#define UART_C4_M10_SHIFT                        (5U)
/*! M10 - 10-bit Mode select
 *  0b0..The parity bit is the ninth bit in the serial transmission.
 *  0b1..The parity bit is the tenth bit in the serial transmission.
 */
#define UART_C4_M10(x)                           (((uint8_t)(((uint8_t)(x)) << UART_C4_M10_SHIFT)) & UART_C4_M10_MASK)

#define UART_C4_MAEN2_MASK                       (0x40U)
#define UART_C4_MAEN2_SHIFT                      (6U)
/*! MAEN2 - Match Address Mode Enable 2
 *  0b0..All data received is transferred to the data buffer if MAEN1 is cleared.
 *  0b1..All data received with the most significant bit cleared, is discarded. All data received with the most
 *       significant bit set, is compared with contents of MA2 register. If no match occurs, the data is discarded.
 *       If a match occurs, data is transferred to the data buffer. This field must be cleared when C7816[ISO7816E]
 *       is set/enabled.
 */
#define UART_C4_MAEN2(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN2_SHIFT)) & UART_C4_MAEN2_MASK)

#define UART_C4_MAEN1_MASK                       (0x80U)
#define UART_C4_MAEN1_SHIFT                      (7U)
/*! MAEN1 - Match Address Mode Enable 1
 *  0b0..All data received is transferred to the data buffer if MAEN2 is cleared.
 *  0b1..All data received with the most significant bit cleared, is discarded. All data received with the most
 *       significant bit set, is compared with contents of MA1 register. If no match occurs, the data is discarded.
 *       If match occurs, data is transferred to the data buffer. This field must be cleared when C7816[ISO7816E] is
 *       set/enabled.
 */
#define UART_C4_MAEN1(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C4_MAEN1_SHIFT)) & UART_C4_MAEN1_MASK)
/*! @} */

/*! @name C5 - UART Control Register 5 */
/*! @{ */

#define UART_C5_RDMAS_MASK                       (0x20U)
#define UART_C5_RDMAS_SHIFT                      (5U)
/*! RDMAS - Receiver Full DMA Select
 *  0b0..If C2[RIE] and S1[RDRF] are set, the RDFR interrupt request signal is asserted to request an interrupt service.
 *  0b1..If C2[RIE] and S1[RDRF] are set, the RDRF DMA request signal is asserted to request a DMA transfer.
 */
#define UART_C5_RDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_RDMAS_SHIFT)) & UART_C5_RDMAS_MASK)

#define UART_C5_TDMAS_MASK                       (0x80U)
#define UART_C5_TDMAS_SHIFT                      (7U)
/*! TDMAS - Transmitter DMA Select
 *  0b0..If C2[TIE] is set and the S1[TDRE] flag is set, the TDRE interrupt request signal is asserted to request interrupt service.
 *  0b1..If C2[TIE] is set and the S1[TDRE] flag is set, the TDRE DMA request signal is asserted to request a DMA transfer.
 */
#define UART_C5_TDMAS(x)                         (((uint8_t)(((uint8_t)(x)) << UART_C5_TDMAS_SHIFT)) & UART_C5_TDMAS_MASK)
/*! @} */

/*! @name ED - UART Extended Data Register */
/*! @{ */

#define UART_ED_PARITYE_MASK                     (0x40U)
#define UART_ED_PARITYE_SHIFT                    (6U)
/*! PARITYE
 *  0b0..The dataword was received without a parity error.
 *  0b1..The dataword was received with a parity error.
 */
#define UART_ED_PARITYE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_ED_PARITYE_SHIFT)) & UART_ED_PARITYE_MASK)

#define UART_ED_NOISY_MASK                       (0x80U)
#define UART_ED_NOISY_SHIFT                      (7U)
/*! NOISY
 *  0b0..The dataword was received without noise.
 *  0b1..The data was received with noise.
 */
#define UART_ED_NOISY(x)                         (((uint8_t)(((uint8_t)(x)) << UART_ED_NOISY_SHIFT)) & UART_ED_NOISY_MASK)
/*! @} */

/*! @name MODEM - UART Modem Register */
/*! @{ */

#define UART_MODEM_TXCTSE_MASK                   (0x1U)
#define UART_MODEM_TXCTSE_SHIFT                  (0U)
/*! TXCTSE - Transmitter clear-to-send enable
 *  0b0..CTS has no effect on the transmitter.
 *  0b1..Enables clear-to-send operation. The transmitter checks the state of CTS each time it is ready to send a
 *       character. If CTS is asserted, the character is sent. If CTS is deasserted, the signal TXD remains in the
 *       mark state and transmission is delayed until CTS is asserted. Changes in CTS as a character is being sent
 *       do not affect its transmission.
 */
#define UART_MODEM_TXCTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXCTSE_SHIFT)) & UART_MODEM_TXCTSE_MASK)

#define UART_MODEM_TXRTSE_MASK                   (0x2U)
#define UART_MODEM_TXRTSE_SHIFT                  (1U)
/*! TXRTSE - Transmitter request-to-send enable
 *  0b0..The transmitter has no effect on RTS.
 *  0b1..When a character is placed into an empty transmitter data buffer , RTS asserts one bit time before the
 *       start bit is transmitted. RTS deasserts one bit time after all characters in the transmitter data buffer and
 *       shift register are completely sent, including the last stop bit. (FIFO) Ensure that C2[TE] is asserted
 *       before assertion of this bit.
 */
#define UART_MODEM_TXRTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXRTSE_SHIFT)) & UART_MODEM_TXRTSE_MASK)

#define UART_MODEM_TXRTSPOL_MASK                 (0x4U)
#define UART_MODEM_TXRTSPOL_SHIFT                (2U)
/*! TXRTSPOL - Transmitter request-to-send polarity
 *  0b0..Transmitter RTS is active low.
 *  0b1..Transmitter RTS is active high.
 */
#define UART_MODEM_TXRTSPOL(x)                   (((uint8_t)(((uint8_t)(x)) << UART_MODEM_TXRTSPOL_SHIFT)) & UART_MODEM_TXRTSPOL_MASK)

#define UART_MODEM_RXRTSE_MASK                   (0x8U)
#define UART_MODEM_RXRTSE_SHIFT                  (3U)
/*! RXRTSE - Receiver request-to-send enable
 *  0b0..The receiver has no effect on RTS.
 *  0b1..RTS is deasserted if the number of characters in the receiver data register (FIFO) is equal to or greater
 *       than RWFIFO[RXWATER]. RTS is asserted when the number of characters in the receiver data register (FIFO)
 *       is less than RWFIFO[RXWATER]. See Hardware flow control
 */
#define UART_MODEM_RXRTSE(x)                     (((uint8_t)(((uint8_t)(x)) << UART_MODEM_RXRTSE_SHIFT)) & UART_MODEM_RXRTSE_MASK)
/*! @} */

/*! @name PFIFO - UART FIFO Parameters */
/*! @{ */

#define UART_PFIFO_RXFIFOSIZE_MASK               (0x7U)
#define UART_PFIFO_RXFIFOSIZE_SHIFT              (0U)
/*! RXFIFOSIZE - Receive FIFO. Buffer Depth
 *  0b000..Receive FIFO/Buffer depth = 1 dataword.
 *  0b001..Receive FIFO/Buffer depth = 4 datawords.
 *  0b010..Receive FIFO/Buffer depth = 8 datawords.
 *  0b011..Receive FIFO/Buffer depth = 16 datawords.
 *  0b100..Receive FIFO/Buffer depth = 32 datawords.
 *  0b101..Receive FIFO/Buffer depth = 64 datawords.
 *  0b110..Receive FIFO/Buffer depth = 128 datawords.
 *  0b111..Reserved.
 */
#define UART_PFIFO_RXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_RXFIFOSIZE_SHIFT)) & UART_PFIFO_RXFIFOSIZE_MASK)

#define UART_PFIFO_RXFE_MASK                     (0x8U)
#define UART_PFIFO_RXFE_SHIFT                    (3U)
/*! RXFE - Receive FIFO Enable
 *  0b0..Receive FIFO is not enabled. Buffer is depth 1. (Legacy support)
 *  0b1..Receive FIFO is enabled. Buffer is depth indicted by RXFIFOSIZE.
 */
#define UART_PFIFO_RXFE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_RXFE_SHIFT)) & UART_PFIFO_RXFE_MASK)

#define UART_PFIFO_TXFIFOSIZE_MASK               (0x70U)
#define UART_PFIFO_TXFIFOSIZE_SHIFT              (4U)
/*! TXFIFOSIZE - Transmit FIFO. Buffer Depth
 *  0b000..Transmit FIFO/Buffer depth = 1 dataword.
 *  0b001..Transmit FIFO/Buffer depth = 4 datawords.
 *  0b010..Transmit FIFO/Buffer depth = 8 datawords.
 *  0b011..Transmit FIFO/Buffer depth = 16 datawords.
 *  0b100..Transmit FIFO/Buffer depth = 32 datawords.
 *  0b101..Transmit FIFO/Buffer depth = 64 datawords.
 *  0b110..Transmit FIFO/Buffer depth = 128 datawords.
 *  0b111..Reserved.
 */
#define UART_PFIFO_TXFIFOSIZE(x)                 (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_TXFIFOSIZE_SHIFT)) & UART_PFIFO_TXFIFOSIZE_MASK)

#define UART_PFIFO_TXFE_MASK                     (0x80U)
#define UART_PFIFO_TXFE_SHIFT                    (7U)
/*! TXFE - Transmit FIFO Enable
 *  0b0..Transmit FIFO is not enabled. Buffer is depth 1. (Legacy support).
 *  0b1..Transmit FIFO is enabled. Buffer is depth indicated by TXFIFOSIZE.
 */
#define UART_PFIFO_TXFE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_PFIFO_TXFE_SHIFT)) & UART_PFIFO_TXFE_MASK)
/*! @} */

/*! @name CFIFO - UART FIFO Control Register */
/*! @{ */

#define UART_CFIFO_RXUFE_MASK                    (0x1U)
#define UART_CFIFO_RXUFE_SHIFT                   (0U)
/*! RXUFE - Receive FIFO Underflow Interrupt Enable
 *  0b0..RXUF flag does not generate an interrupt to the host.
 *  0b1..RXUF flag generates an interrupt to the host.
 */
#define UART_CFIFO_RXUFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXUFE_SHIFT)) & UART_CFIFO_RXUFE_MASK)

#define UART_CFIFO_TXOFE_MASK                    (0x2U)
#define UART_CFIFO_TXOFE_SHIFT                   (1U)
/*! TXOFE - Transmit FIFO Overflow Interrupt Enable
 *  0b0..TXOF flag does not generate an interrupt to the host.
 *  0b1..TXOF flag generates an interrupt to the host.
 */
#define UART_CFIFO_TXOFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_TXOFE_SHIFT)) & UART_CFIFO_TXOFE_MASK)

#define UART_CFIFO_RXOFE_MASK                    (0x4U)
#define UART_CFIFO_RXOFE_SHIFT                   (2U)
/*! RXOFE - Receive FIFO Overflow Interrupt Enable
 *  0b0..RXOF flag does not generate an interrupt to the host.
 *  0b1..RXOF flag generates an interrupt to the host.
 */
#define UART_CFIFO_RXOFE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXOFE_SHIFT)) & UART_CFIFO_RXOFE_MASK)

#define UART_CFIFO_RXFLUSH_MASK                  (0x40U)
#define UART_CFIFO_RXFLUSH_SHIFT                 (6U)
/*! RXFLUSH - Receive FIFO/Buffer Flush
 *  0b0..No flush operation occurs.
 *  0b1..All data in the receive FIFO/buffer is cleared out.
 */
#define UART_CFIFO_RXFLUSH(x)                    (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_RXFLUSH_SHIFT)) & UART_CFIFO_RXFLUSH_MASK)

#define UART_CFIFO_TXFLUSH_MASK                  (0x80U)
#define UART_CFIFO_TXFLUSH_SHIFT                 (7U)
/*! TXFLUSH - Transmit FIFO/Buffer Flush
 *  0b0..No flush operation occurs.
 *  0b1..All data in the transmit FIFO/Buffer is cleared out.
 */
#define UART_CFIFO_TXFLUSH(x)                    (((uint8_t)(((uint8_t)(x)) << UART_CFIFO_TXFLUSH_SHIFT)) & UART_CFIFO_TXFLUSH_MASK)
/*! @} */

/*! @name SFIFO - UART FIFO Status Register */
/*! @{ */

#define UART_SFIFO_RXUF_MASK                     (0x1U)
#define UART_SFIFO_RXUF_SHIFT                    (0U)
/*! RXUF - Receiver Buffer Underflow Flag
 *  0b0..No receive buffer underflow has occurred since the last time the flag was cleared.
 *  0b1..At least one receive buffer underflow has occurred since the last time the flag was cleared.
 */
#define UART_SFIFO_RXUF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXUF_SHIFT)) & UART_SFIFO_RXUF_MASK)

#define UART_SFIFO_TXOF_MASK                     (0x2U)
#define UART_SFIFO_TXOF_SHIFT                    (1U)
/*! TXOF - Transmitter Buffer Overflow Flag
 *  0b0..No transmit buffer overflow has occurred since the last time the flag was cleared.
 *  0b1..At least one transmit buffer overflow has occurred since the last time the flag was cleared.
 */
#define UART_SFIFO_TXOF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_TXOF_SHIFT)) & UART_SFIFO_TXOF_MASK)

#define UART_SFIFO_RXOF_MASK                     (0x4U)
#define UART_SFIFO_RXOF_SHIFT                    (2U)
/*! RXOF - Receiver Buffer Overflow Flag
 *  0b0..No receive buffer overflow has occurred since the last time the flag was cleared.
 *  0b1..At least one receive buffer overflow has occurred since the last time the flag was cleared.
 */
#define UART_SFIFO_RXOF(x)                       (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXOF_SHIFT)) & UART_SFIFO_RXOF_MASK)

#define UART_SFIFO_RXEMPT_MASK                   (0x40U)
#define UART_SFIFO_RXEMPT_SHIFT                  (6U)
/*! RXEMPT - Receive Buffer/FIFO Empty
 *  0b0..Receive buffer is not empty.
 *  0b1..Receive buffer is empty.
 */
#define UART_SFIFO_RXEMPT(x)                     (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_RXEMPT_SHIFT)) & UART_SFIFO_RXEMPT_MASK)

#define UART_SFIFO_TXEMPT_MASK                   (0x80U)
#define UART_SFIFO_TXEMPT_SHIFT                  (7U)
/*! TXEMPT - Transmit Buffer/FIFO Empty
 *  0b0..Transmit buffer is not empty.
 *  0b1..Transmit buffer is empty.
 */
#define UART_SFIFO_TXEMPT(x)                     (((uint8_t)(((uint8_t)(x)) << UART_SFIFO_TXEMPT_SHIFT)) & UART_SFIFO_TXEMPT_MASK)
/*! @} */

/*! @name TWFIFO - UART FIFO Transmit Watermark */
/*! @{ */

#define UART_TWFIFO_TXWATER_MASK                 (0xFFU)
#define UART_TWFIFO_TXWATER_SHIFT                (0U)
/*! TXWATER - Transmit Watermark
 */
#define UART_TWFIFO_TXWATER(x)                   (((uint8_t)(((uint8_t)(x)) << UART_TWFIFO_TXWATER_SHIFT)) & UART_TWFIFO_TXWATER_MASK)
/*! @} */

/*! @name TCFIFO - UART FIFO Transmit Count */
/*! @{ */

#define UART_TCFIFO_TXCOUNT_MASK                 (0xFFU)
#define UART_TCFIFO_TXCOUNT_SHIFT                (0U)
/*! TXCOUNT - Transmit Counter
 */
#define UART_TCFIFO_TXCOUNT(x)                   (((uint8_t)(((uint8_t)(x)) << UART_TCFIFO_TXCOUNT_SHIFT)) & UART_TCFIFO_TXCOUNT_MASK)
/*! @} */

/*! @name RWFIFO - UART FIFO Receive Watermark */
/*! @{ */

#define UART_RWFIFO_RXWATER_MASK                 (0xFFU)
#define UART_RWFIFO_RXWATER_SHIFT                (0U)
/*! RXWATER - Receive Watermark
 */
#define UART_RWFIFO_RXWATER(x)                   (((uint8_t)(((uint8_t)(x)) << UART_RWFIFO_RXWATER_SHIFT)) & UART_RWFIFO_RXWATER_MASK)
/*! @} */

/*! @name RCFIFO - UART FIFO Receive Count */
/*! @{ */

#define UART_RCFIFO_RXCOUNT_MASK                 (0xFFU)
#define UART_RCFIFO_RXCOUNT_SHIFT                (0U)
/*! RXCOUNT - Receive Counter
 */
#define UART_RCFIFO_RXCOUNT(x)                   (((uint8_t)(((uint8_t)(x)) << UART_RCFIFO_RXCOUNT_SHIFT)) & UART_RCFIFO_RXCOUNT_MASK)
/*! @} */

/*! @name C7816 - UART 7816 Control Register */
/*! @{ */

#define UART_C7816_ISO_7816E_MASK                (0x1U)
#define UART_C7816_ISO_7816E_SHIFT               (0U)
/*! ISO_7816E - ISO-7816 Functionality Enabled
 *  0b0..ISO-7816 functionality is turned off/not enabled.
 *  0b1..ISO-7816 functionality is turned on/enabled.
 */
#define UART_C7816_ISO_7816E(x)                  (((uint8_t)(((uint8_t)(x)) << UART_C7816_ISO_7816E_SHIFT)) & UART_C7816_ISO_7816E_MASK)

#define UART_C7816_TTYPE_MASK                    (0x2U)
#define UART_C7816_TTYPE_SHIFT                   (1U)
/*! TTYPE - Transfer Type
 *  0b0..T = 0 per the ISO-7816 specification.
 *  0b1..T = 1 per the ISO-7816 specification.
 */
#define UART_C7816_TTYPE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_TTYPE_SHIFT)) & UART_C7816_TTYPE_MASK)

#define UART_C7816_INIT_MASK                     (0x4U)
#define UART_C7816_INIT_SHIFT                    (2U)
/*! INIT - Detect Initial Character
 *  0b0..Normal operating mode. Receiver does not seek to identify initial character.
 *  0b1..Receiver searches for initial character.
 */
#define UART_C7816_INIT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_C7816_INIT_SHIFT)) & UART_C7816_INIT_MASK)

#define UART_C7816_ANACK_MASK                    (0x8U)
#define UART_C7816_ANACK_SHIFT                   (3U)
/*! ANACK - Generate NACK on Error
 *  0b0..No NACK is automatically generated.
 *  0b1..A NACK is automatically generated if a parity error is detected or if an invalid initial character is detected.
 */
#define UART_C7816_ANACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ANACK_SHIFT)) & UART_C7816_ANACK_MASK)

#define UART_C7816_ONACK_MASK                    (0x10U)
#define UART_C7816_ONACK_SHIFT                   (4U)
/*! ONACK - Generate NACK on Overflow
 *  0b0..The received data does not generate a NACK when the receipt of the data results in an overflow event.
 *  0b1..If the receiver buffer overflows, a NACK is automatically sent on a received character.
 */
#define UART_C7816_ONACK(x)                      (((uint8_t)(((uint8_t)(x)) << UART_C7816_ONACK_SHIFT)) & UART_C7816_ONACK_MASK)
/*! @} */

/*! @name IE7816 - UART 7816 Interrupt Enable Register */
/*! @{ */

#define UART_IE7816_RXTE_MASK                    (0x1U)
#define UART_IE7816_RXTE_SHIFT                   (0U)
/*! RXTE - Receive Threshold Exceeded Interrupt Enable
 *  0b0..The assertion of IS7816[RXT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[RXT] results in the generation of an interrupt.
 */
#define UART_IE7816_RXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_RXTE_SHIFT)) & UART_IE7816_RXTE_MASK)

#define UART_IE7816_TXTE_MASK                    (0x2U)
#define UART_IE7816_TXTE_SHIFT                   (1U)
/*! TXTE - Transmit Threshold Exceeded Interrupt Enable
 *  0b0..The assertion of IS7816[TXT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[TXT] results in the generation of an interrupt.
 */
#define UART_IE7816_TXTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_TXTE_SHIFT)) & UART_IE7816_TXTE_MASK)

#define UART_IE7816_GTVE_MASK                    (0x4U)
#define UART_IE7816_GTVE_SHIFT                   (2U)
/*! GTVE - Guard Timer Violated Interrupt Enable
 *  0b0..The assertion of IS7816[GTV] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[GTV] results in the generation of an interrupt.
 */
#define UART_IE7816_GTVE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_GTVE_SHIFT)) & UART_IE7816_GTVE_MASK)

#define UART_IE7816_INITDE_MASK                  (0x10U)
#define UART_IE7816_INITDE_SHIFT                 (4U)
/*! INITDE - Initial Character Detected Interrupt Enable
 *  0b0..The assertion of IS7816[INITD] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[INITD] results in the generation of an interrupt.
 */
#define UART_IE7816_INITDE(x)                    (((uint8_t)(((uint8_t)(x)) << UART_IE7816_INITDE_SHIFT)) & UART_IE7816_INITDE_MASK)

#define UART_IE7816_BWTE_MASK                    (0x20U)
#define UART_IE7816_BWTE_SHIFT                   (5U)
/*! BWTE - Block Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[BWT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[BWT] results in the generation of an interrupt.
 */
#define UART_IE7816_BWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_BWTE_SHIFT)) & UART_IE7816_BWTE_MASK)

#define UART_IE7816_CWTE_MASK                    (0x40U)
#define UART_IE7816_CWTE_SHIFT                   (6U)
/*! CWTE - Character Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[CWT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[CWT] results in the generation of an interrupt.
 */
#define UART_IE7816_CWTE(x)                      (((uint8_t)(((uint8_t)(x)) << UART_IE7816_CWTE_SHIFT)) & UART_IE7816_CWTE_MASK)

#define UART_IE7816_WTE_MASK                     (0x80U)
#define UART_IE7816_WTE_SHIFT                    (7U)
/*! WTE - Wait Timer Interrupt Enable
 *  0b0..The assertion of IS7816[WT] does not result in the generation of an interrupt.
 *  0b1..The assertion of IS7816[WT] results in the generation of an interrupt.
 */
#define UART_IE7816_WTE(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IE7816_WTE_SHIFT)) & UART_IE7816_WTE_MASK)
/*! @} */

/*! @name IS7816 - UART 7816 Interrupt Status Register */
/*! @{ */

#define UART_IS7816_RXT_MASK                     (0x1U)
#define UART_IS7816_RXT_SHIFT                    (0U)
/*! RXT - Receive Threshold Exceeded Interrupt
 *  0b0..The number of consecutive NACKS generated as a result of parity errors and buffer overruns is less than
 *       or equal to the value in ET7816[RXTHRESHOLD].
 *  0b1..The number of consecutive NACKS generated as a result of parity errors and buffer overruns is greater than the value in ET7816[RXTHRESHOLD].
 */
#define UART_IS7816_RXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_RXT_SHIFT)) & UART_IS7816_RXT_MASK)

#define UART_IS7816_TXT_MASK                     (0x2U)
#define UART_IS7816_TXT_SHIFT                    (1U)
/*! TXT - Transmit Threshold Exceeded Interrupt
 *  0b0..The number of retries and corresponding NACKS does not exceed the value in ET7816[TXTHRESHOLD].
 *  0b1..The number of retries and corresponding NACKS exceeds the value in ET7816[TXTHRESHOLD].
 */
#define UART_IS7816_TXT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_TXT_SHIFT)) & UART_IS7816_TXT_MASK)

#define UART_IS7816_GTV_MASK                     (0x4U)
#define UART_IS7816_GTV_SHIFT                    (2U)
/*! GTV - Guard Timer Violated Interrupt
 *  0b0..A guard time (GT, CGT, or BGT) has not been violated.
 *  0b1..A guard time (GT, CGT, or BGT) has been violated.
 */
#define UART_IS7816_GTV(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_GTV_SHIFT)) & UART_IS7816_GTV_MASK)

#define UART_IS7816_INITD_MASK                   (0x10U)
#define UART_IS7816_INITD_SHIFT                  (4U)
/*! INITD - Initial Character Detected Interrupt
 *  0b0..A valid initial character has not been received.
 *  0b1..A valid initial character has been received.
 */
#define UART_IS7816_INITD(x)                     (((uint8_t)(((uint8_t)(x)) << UART_IS7816_INITD_SHIFT)) & UART_IS7816_INITD_MASK)

#define UART_IS7816_BWT_MASK                     (0x20U)
#define UART_IS7816_BWT_SHIFT                    (5U)
/*! BWT - Block Wait Timer Interrupt
 *  0b0..Block wait time (BWT) has not been violated.
 *  0b1..Block wait time (BWT) has been violated.
 */
#define UART_IS7816_BWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_BWT_SHIFT)) & UART_IS7816_BWT_MASK)

#define UART_IS7816_CWT_MASK                     (0x40U)
#define UART_IS7816_CWT_SHIFT                    (6U)
/*! CWT - Character Wait Timer Interrupt
 *  0b0..Character wait time (CWT) has not been violated.
 *  0b1..Character wait time (CWT) has been violated.
 */
#define UART_IS7816_CWT(x)                       (((uint8_t)(((uint8_t)(x)) << UART_IS7816_CWT_SHIFT)) & UART_IS7816_CWT_MASK)

#define UART_IS7816_WT_MASK                      (0x80U)
#define UART_IS7816_WT_SHIFT                     (7U)
/*! WT - Wait Timer Interrupt
 *  0b0..Wait time (WT) has not been violated.
 *  0b1..Wait time (WT) has been violated.
 */
#define UART_IS7816_WT(x)                        (((uint8_t)(((uint8_t)(x)) << UART_IS7816_WT_SHIFT)) & UART_IS7816_WT_MASK)
/*! @} */

/*! @name WP7816T0 - UART 7816 Wait Parameter Register */
/*! @{ */

#define UART_WP7816T0_WI_MASK                    (0xFFU)
#define UART_WP7816T0_WI_SHIFT                   (0U)
/*! WI - Wait Time Integer (C7816[TTYPE] = 0)
 */
#define UART_WP7816T0_WI(x)                      (((uint8_t)(((uint8_t)(x)) << UART_WP7816T0_WI_SHIFT)) & UART_WP7816T0_WI_MASK)
/*! @} */

/*! @name WP7816T1 - UART 7816 Wait Parameter Register */
/*! @{ */

#define UART_WP7816T1_BWI_MASK                   (0xFU)
#define UART_WP7816T1_BWI_SHIFT                  (0U)
/*! BWI - Block Wait Time Integer(C7816[TTYPE] = 1)
 */
#define UART_WP7816T1_BWI(x)                     (((uint8_t)(((uint8_t)(x)) << UART_WP7816T1_BWI_SHIFT)) & UART_WP7816T1_BWI_MASK)

#define UART_WP7816T1_CWI_MASK                   (0xF0U)
#define UART_WP7816T1_CWI_SHIFT                  (4U)
/*! CWI - Character Wait Time Integer (C7816[TTYPE] = 1)
 */
#define UART_WP7816T1_CWI(x)                     (((uint8_t)(((uint8_t)(x)) << UART_WP7816T1_CWI_SHIFT)) & UART_WP7816T1_CWI_MASK)
/*! @} */

/*! @name WN7816 - UART 7816 Wait N Register */
/*! @{ */

#define UART_WN7816_GTN_MASK                     (0xFFU)
#define UART_WN7816_GTN_SHIFT                    (0U)
/*! GTN - Guard Band N
 */
#define UART_WN7816_GTN(x)                       (((uint8_t)(((uint8_t)(x)) << UART_WN7816_GTN_SHIFT)) & UART_WN7816_GTN_MASK)
/*! @} */

/*! @name WF7816 - UART 7816 Wait FD Register */
/*! @{ */

#define UART_WF7816_GTFD_MASK                    (0xFFU)
#define UART_WF7816_GTFD_SHIFT                   (0U)
/*! GTFD - FD Multiplier
 */
#define UART_WF7816_GTFD(x)                      (((uint8_t)(((uint8_t)(x)) << UART_WF7816_GTFD_SHIFT)) & UART_WF7816_GTFD_MASK)
/*! @} */

/*! @name ET7816 - UART 7816 Error Threshold Register */
/*! @{ */

#define UART_ET7816_RXTHRESHOLD_MASK             (0xFU)
#define UART_ET7816_RXTHRESHOLD_SHIFT            (0U)
/*! RXTHRESHOLD - Receive NACK Threshold
 */
#define UART_ET7816_RXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_RXTHRESHOLD_SHIFT)) & UART_ET7816_RXTHRESHOLD_MASK)

#define UART_ET7816_TXTHRESHOLD_MASK             (0xF0U)
#define UART_ET7816_TXTHRESHOLD_SHIFT            (4U)
/*! TXTHRESHOLD - Transmit NACK Threshold
 *  0b0000..TXT asserts on the first NACK that is received.
 *  0b0001..TXT asserts on the second NACK that is received.
 */
#define UART_ET7816_TXTHRESHOLD(x)               (((uint8_t)(((uint8_t)(x)) << UART_ET7816_TXTHRESHOLD_SHIFT)) & UART_ET7816_TXTHRESHOLD_MASK)
/*! @} */

/*! @name TL7816 - UART 7816 Transmit Length Register */
/*! @{ */

#define UART_TL7816_TLEN_MASK                    (0xFFU)
#define UART_TL7816_TLEN_SHIFT                   (0U)
/*! TLEN - Transmit Length
 */
#define UART_TL7816_TLEN(x)                      (((uint8_t)(((uint8_t)(x)) << UART_TL7816_TLEN_SHIFT)) & UART_TL7816_TLEN_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group UART_Register_Masks */


/* UART - Peripheral instance base addresses */
/** Peripheral UART0 base address */
#define UART0_BASE                               (0x4006A000u)
/** Peripheral UART0 base pointer */
#define UART0                                    ((UART_Type *)UART0_BASE)
/** Peripheral UART1 base address */
#define UART1_BASE                               (0x4006B000u)
/** Peripheral UART1 base pointer */
#define UART1                                    ((UART_Type *)UART1_BASE)
/** Peripheral UART2 base address */
#define UART2_BASE                               (0x4006C000u)
/** Peripheral UART2 base pointer */
#define UART2                                    ((UART_Type *)UART2_BASE)
/** Peripheral UART3 base address */
#define UART3_BASE                               (0x4006D000u)
/** Peripheral UART3 base pointer */
#define UART3                                    ((UART_Type *)UART3_BASE)
/** Array initializer of UART peripheral base addresses */
#define UART_BASE_ADDRS                          { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE }
/** Array initializer of UART peripheral base pointers */
#define UART_BASE_PTRS                           { UART0, UART1, UART2, UART3 }
/** Interrupt vectors for the UART peripheral type */
#define UART_RX_TX_IRQS                          { UART0_UART1_IRQn, UART0_UART1_IRQn, UART2_UART3_IRQn, UART2_UART3_IRQn }
#define UART_ERR_IRQS                            { UART0_UART1_IRQn, UART0_UART1_IRQn, UART2_UART3_IRQn, UART2_UART3_IRQn }

/*!
 * @}
 */ /* end of group UART_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- VREF Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Peripheral_Access_Layer VREF Peripheral Access Layer
 * @{
 */

/** VREF - Register Layout Typedef */
typedef struct {
  __IO uint8_t VREFH_TRM;                          /**< VREF Trim Register, offset: 0x0 */
  __IO uint8_t VREFH_SC;                           /**< VREF Status and Control Register, offset: 0x1 */
       uint8_t RESERVED_0[3];
  __IO uint8_t VREFL_TRM;                          /**< VREFL TRIM Register, offset: 0x5 */
} VREF_Type;

/* ----------------------------------------------------------------------------
   -- VREF Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VREF_Register_Masks VREF Register Masks
 * @{
 */

/*! @name VREFH_TRM - VREF Trim Register */
/*! @{ */

#define VREF_VREFH_TRM_TRIM_MASK                 (0x3FU)
#define VREF_VREFH_TRM_TRIM_SHIFT                (0U)
/*! TRIM - Trim bits
 *  0b000000..Min
 *  0b111111..Max
 */
#define VREF_VREFH_TRM_TRIM(x)                   (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_TRM_TRIM_SHIFT)) & VREF_VREFH_TRM_TRIM_MASK)

#define VREF_VREFH_TRM_CHOPEN_MASK               (0x40U)
#define VREF_VREFH_TRM_CHOPEN_SHIFT              (6U)
/*! CHOPEN - Chop oscillator enable. When set, internal chopping operation is enabled and the
 *    internal analog offset will be minimized.
 *  0b0..Chop oscillator is disabled.
 *  0b1..Chop oscillator is enabled.
 */
#define VREF_VREFH_TRM_CHOPEN(x)                 (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_TRM_CHOPEN_SHIFT)) & VREF_VREFH_TRM_CHOPEN_MASK)
/*! @} */

/*! @name VREFH_SC - VREF Status and Control Register */
/*! @{ */

#define VREF_VREFH_SC_MODE_LV_MASK               (0x3U)
#define VREF_VREFH_SC_MODE_LV_SHIFT              (0U)
/*! MODE_LV - Buffer Mode selection
 *  0b00..Bandgap on only, for stabilization and startup
 *  0b01..High power buffer mode enabled
 *  0b10..Low-power buffer mode enabled
 *  0b11..Reserved
 */
#define VREF_VREFH_SC_MODE_LV(x)                 (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_SC_MODE_LV_SHIFT)) & VREF_VREFH_SC_MODE_LV_MASK)

#define VREF_VREFH_SC_VREFST_MASK                (0x4U)
#define VREF_VREFH_SC_VREFST_SHIFT               (2U)
/*! VREFST - Internal Voltage Reference stable
 *  0b0..The module is disabled or not stable.
 *  0b1..The module is stable.
 */
#define VREF_VREFH_SC_VREFST(x)                  (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_SC_VREFST_SHIFT)) & VREF_VREFH_SC_VREFST_MASK)

#define VREF_VREFH_SC_ICOMPEN_MASK               (0x20U)
#define VREF_VREFH_SC_ICOMPEN_SHIFT              (5U)
/*! ICOMPEN - Second order curvature compensation enable
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define VREF_VREFH_SC_ICOMPEN(x)                 (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_SC_ICOMPEN_SHIFT)) & VREF_VREFH_SC_ICOMPEN_MASK)

#define VREF_VREFH_SC_REGEN_MASK                 (0x40U)
#define VREF_VREFH_SC_REGEN_SHIFT                (6U)
/*! REGEN - Regulator enable
 *  0b0..Internal 1.75 V regulator is disabled.
 *  0b1..Internal 1.75 V regulator is enabled.
 */
#define VREF_VREFH_SC_REGEN(x)                   (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_SC_REGEN_SHIFT)) & VREF_VREFH_SC_REGEN_MASK)

#define VREF_VREFH_SC_VREFEN_MASK                (0x80U)
#define VREF_VREFH_SC_VREFEN_SHIFT               (7U)
/*! VREFEN - Internal Voltage Reference enable
 *  0b0..The module is disabled.
 *  0b1..The module is enabled.
 */
#define VREF_VREFH_SC_VREFEN(x)                  (((uint8_t)(((uint8_t)(x)) << VREF_VREFH_SC_VREFEN_SHIFT)) & VREF_VREFH_SC_VREFEN_MASK)
/*! @} */

/*! @name VREFL_TRM - VREFL TRIM Register */
/*! @{ */

#define VREF_VREFL_TRM_VREFL_TRIM_MASK           (0x7U)
#define VREF_VREFL_TRM_VREFL_TRIM_SHIFT          (0U)
#define VREF_VREFL_TRM_VREFL_TRIM(x)             (((uint8_t)(((uint8_t)(x)) << VREF_VREFL_TRM_VREFL_TRIM_SHIFT)) & VREF_VREFL_TRM_VREFL_TRIM_MASK)

#define VREF_VREFL_TRM_VREFL_EN_MASK             (0x8U)
#define VREF_VREFL_TRM_VREFL_EN_SHIFT            (3U)
/*! VREFL_EN
 *  0b0..Disable
 *  0b1..Enable
 */
#define VREF_VREFL_TRM_VREFL_EN(x)               (((uint8_t)(((uint8_t)(x)) << VREF_VREFL_TRM_VREFL_EN_SHIFT)) & VREF_VREFL_TRM_VREFL_EN_MASK)

#define VREF_VREFL_TRM_VREFL_SEL_MASK            (0x10U)
#define VREF_VREFL_TRM_VREFL_SEL_SHIFT           (4U)
/*! VREFL_SEL
 *  0b0..Internal reference
 *  0b1..External reference
 */
#define VREF_VREFL_TRM_VREFL_SEL(x)              (((uint8_t)(((uint8_t)(x)) << VREF_VREFL_TRM_VREFL_SEL_SHIFT)) & VREF_VREFL_TRM_VREFL_SEL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group VREF_Register_Masks */


/* VREF - Peripheral instance base addresses */
/** Peripheral VREF base address */
#define VREF_BASE                                (0x4006F000u)
/** Peripheral VREF base pointer */
#define VREF                                     ((VREF_Type *)VREF_BASE)
/** Array initializer of VREF peripheral base addresses */
#define VREF_BASE_ADDRS                          { VREF_BASE }
/** Array initializer of VREF peripheral base pointers */
#define VREF_BASE_PTRS                           { VREF }

/*!
 * @}
 */ /* end of group VREF_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- WDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Peripheral_Access_Layer WDOG Peripheral Access Layer
 * @{
 */

/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint16_t STCTRLH;                           /**< Watchdog Status and Control Register High, offset: 0x0 */
  __IO uint16_t STCTRLL;                           /**< Watchdog Status and Control Register Low, offset: 0x2 */
  __IO uint16_t TOVALH;                            /**< Watchdog Time-out Value Register High, offset: 0x4 */
  __IO uint16_t TOVALL;                            /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  __IO uint16_t WINH;                              /**< Watchdog Window Register High, offset: 0x8 */
  __IO uint16_t WINL;                              /**< Watchdog Window Register Low, offset: 0xA */
  __IO uint16_t REFRESH;                           /**< Watchdog Refresh register, offset: 0xC */
  __IO uint16_t UNLOCK;                            /**< Watchdog Unlock register, offset: 0xE */
  __IO uint16_t TMROUTH;                           /**< Watchdog Timer Output Register High, offset: 0x10 */
  __IO uint16_t TMROUTL;                           /**< Watchdog Timer Output Register Low, offset: 0x12 */
  __IO uint16_t RSTCNT;                            /**< Watchdog Reset Count register, offset: 0x14 */
  __IO uint16_t PRESC;                             /**< Watchdog Prescaler register, offset: 0x16 */
} WDOG_Type;

/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */

/*! @name STCTRLH - Watchdog Status and Control Register High */
/*! @{ */

#define WDOG_STCTRLH_WDOGEN_MASK                 (0x1U)
#define WDOG_STCTRLH_WDOGEN_SHIFT                (0U)
/*! WDOGEN
 *  0b0..WDOG is disabled.
 *  0b1..WDOG is enabled.
 */
#define WDOG_STCTRLH_WDOGEN(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_WDOGEN_SHIFT)) & WDOG_STCTRLH_WDOGEN_MASK)

#define WDOG_STCTRLH_CLKSRC_MASK                 (0x2U)
#define WDOG_STCTRLH_CLKSRC_SHIFT                (1U)
/*! CLKSRC
 *  0b0..WDOG clock sourced from LPO .
 *  0b1..WDOG clock sourced from alternate clock source.
 */
#define WDOG_STCTRLH_CLKSRC(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_CLKSRC_SHIFT)) & WDOG_STCTRLH_CLKSRC_MASK)

#define WDOG_STCTRLH_IRQRSTEN_MASK               (0x4U)
#define WDOG_STCTRLH_IRQRSTEN_SHIFT              (2U)
/*! IRQRSTEN
 *  0b0..WDOG time-out generates reset only.
 *  0b1..WDOG time-out initially generates an interrupt. After WCT, it generates a reset.
 */
#define WDOG_STCTRLH_IRQRSTEN(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_IRQRSTEN_SHIFT)) & WDOG_STCTRLH_IRQRSTEN_MASK)

#define WDOG_STCTRLH_WINEN_MASK                  (0x8U)
#define WDOG_STCTRLH_WINEN_SHIFT                 (3U)
/*! WINEN
 *  0b0..Windowing mode is disabled.
 *  0b1..Windowing mode is enabled.
 */
#define WDOG_STCTRLH_WINEN(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_WINEN_SHIFT)) & WDOG_STCTRLH_WINEN_MASK)

#define WDOG_STCTRLH_ALLOWUPDATE_MASK            (0x10U)
#define WDOG_STCTRLH_ALLOWUPDATE_SHIFT           (4U)
/*! ALLOWUPDATE
 *  0b0..No further updates allowed to WDOG write-once registers.
 *  0b1..WDOG write-once registers can be unlocked for updating.
 */
#define WDOG_STCTRLH_ALLOWUPDATE(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_ALLOWUPDATE_SHIFT)) & WDOG_STCTRLH_ALLOWUPDATE_MASK)

#define WDOG_STCTRLH_DBGEN_MASK                  (0x20U)
#define WDOG_STCTRLH_DBGEN_SHIFT                 (5U)
/*! DBGEN
 *  0b0..WDOG is disabled in CPU Debug mode.
 *  0b1..WDOG is enabled in CPU Debug mode.
 */
#define WDOG_STCTRLH_DBGEN(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_DBGEN_SHIFT)) & WDOG_STCTRLH_DBGEN_MASK)

#define WDOG_STCTRLH_STOPEN_MASK                 (0x40U)
#define WDOG_STCTRLH_STOPEN_SHIFT                (6U)
/*! STOPEN
 *  0b0..WDOG is disabled in CPU Stop mode.
 *  0b1..WDOG is enabled in CPU Stop mode.
 */
#define WDOG_STCTRLH_STOPEN(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_STOPEN_SHIFT)) & WDOG_STCTRLH_STOPEN_MASK)

#define WDOG_STCTRLH_TESTWDOG_MASK               (0x400U)
#define WDOG_STCTRLH_TESTWDOG_SHIFT              (10U)
#define WDOG_STCTRLH_TESTWDOG(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_TESTWDOG_SHIFT)) & WDOG_STCTRLH_TESTWDOG_MASK)

#define WDOG_STCTRLH_TESTSEL_MASK                (0x800U)
#define WDOG_STCTRLH_TESTSEL_SHIFT               (11U)
/*! TESTSEL
 *  0b0..Quick test. The timer runs in normal operation. You can load a small time-out value to do a quick test.
 *  0b1..Byte test. Puts the timer in the byte test mode where individual bytes of the timer are enabled for
 *       operation and are compared for time-out against the corresponding byte of the programmed time-out value. Select
 *       the byte through BYTESEL[1:0] for testing.
 */
#define WDOG_STCTRLH_TESTSEL(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_TESTSEL_SHIFT)) & WDOG_STCTRLH_TESTSEL_MASK)

#define WDOG_STCTRLH_BYTESEL_MASK                (0x3000U)
#define WDOG_STCTRLH_BYTESEL_SHIFT               (12U)
/*! BYTESEL
 *  0b00..Byte 0 selected
 *  0b01..Byte 1 selected
 *  0b10..Byte 2 selected
 *  0b11..Byte 3 selected
 */
#define WDOG_STCTRLH_BYTESEL(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_BYTESEL_SHIFT)) & WDOG_STCTRLH_BYTESEL_MASK)

#define WDOG_STCTRLH_DISTESTWDOG_MASK            (0x4000U)
#define WDOG_STCTRLH_DISTESTWDOG_SHIFT           (14U)
/*! DISTESTWDOG
 *  0b0..WDOG functional test mode is not disabled.
 *  0b1..WDOG functional test mode is disabled permanently until reset.
 */
#define WDOG_STCTRLH_DISTESTWDOG(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLH_DISTESTWDOG_SHIFT)) & WDOG_STCTRLH_DISTESTWDOG_MASK)
/*! @} */

/*! @name STCTRLL - Watchdog Status and Control Register Low */
/*! @{ */

#define WDOG_STCTRLL_INTFLG_MASK                 (0x8000U)
#define WDOG_STCTRLL_INTFLG_SHIFT                (15U)
#define WDOG_STCTRLL_INTFLG(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_STCTRLL_INTFLG_SHIFT)) & WDOG_STCTRLL_INTFLG_MASK)
/*! @} */

/*! @name TOVALH - Watchdog Time-out Value Register High */
/*! @{ */

#define WDOG_TOVALH_TOVALHIGH_MASK               (0xFFFFU)
#define WDOG_TOVALH_TOVALHIGH_SHIFT              (0U)
#define WDOG_TOVALH_TOVALHIGH(x)                 (((uint16_t)(((uint16_t)(x)) << WDOG_TOVALH_TOVALHIGH_SHIFT)) & WDOG_TOVALH_TOVALHIGH_MASK)
/*! @} */

/*! @name TOVALL - Watchdog Time-out Value Register Low */
/*! @{ */

#define WDOG_TOVALL_TOVALLOW_MASK                (0xFFFFU)
#define WDOG_TOVALL_TOVALLOW_SHIFT               (0U)
#define WDOG_TOVALL_TOVALLOW(x)                  (((uint16_t)(((uint16_t)(x)) << WDOG_TOVALL_TOVALLOW_SHIFT)) & WDOG_TOVALL_TOVALLOW_MASK)
/*! @} */

/*! @name WINH - Watchdog Window Register High */
/*! @{ */

#define WDOG_WINH_WINHIGH_MASK                   (0xFFFFU)
#define WDOG_WINH_WINHIGH_SHIFT                  (0U)
#define WDOG_WINH_WINHIGH(x)                     (((uint16_t)(((uint16_t)(x)) << WDOG_WINH_WINHIGH_SHIFT)) & WDOG_WINH_WINHIGH_MASK)
/*! @} */

/*! @name WINL - Watchdog Window Register Low */
/*! @{ */

#define WDOG_WINL_WINLOW_MASK                    (0xFFFFU)
#define WDOG_WINL_WINLOW_SHIFT                   (0U)
#define WDOG_WINL_WINLOW(x)                      (((uint16_t)(((uint16_t)(x)) << WDOG_WINL_WINLOW_SHIFT)) & WDOG_WINL_WINLOW_MASK)
/*! @} */

/*! @name REFRESH - Watchdog Refresh register */
/*! @{ */

#define WDOG_REFRESH_WDOGREFRESH_MASK            (0xFFFFU)
#define WDOG_REFRESH_WDOGREFRESH_SHIFT           (0U)
#define WDOG_REFRESH_WDOGREFRESH(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_REFRESH_WDOGREFRESH_SHIFT)) & WDOG_REFRESH_WDOGREFRESH_MASK)
/*! @} */

/*! @name UNLOCK - Watchdog Unlock register */
/*! @{ */

#define WDOG_UNLOCK_WDOGUNLOCK_MASK              (0xFFFFU)
#define WDOG_UNLOCK_WDOGUNLOCK_SHIFT             (0U)
#define WDOG_UNLOCK_WDOGUNLOCK(x)                (((uint16_t)(((uint16_t)(x)) << WDOG_UNLOCK_WDOGUNLOCK_SHIFT)) & WDOG_UNLOCK_WDOGUNLOCK_MASK)
/*! @} */

/*! @name TMROUTH - Watchdog Timer Output Register High */
/*! @{ */

#define WDOG_TMROUTH_TIMEROUTHIGH_MASK           (0xFFFFU)
#define WDOG_TMROUTH_TIMEROUTHIGH_SHIFT          (0U)
#define WDOG_TMROUTH_TIMEROUTHIGH(x)             (((uint16_t)(((uint16_t)(x)) << WDOG_TMROUTH_TIMEROUTHIGH_SHIFT)) & WDOG_TMROUTH_TIMEROUTHIGH_MASK)
/*! @} */

/*! @name TMROUTL - Watchdog Timer Output Register Low */
/*! @{ */

#define WDOG_TMROUTL_TIMEROUTLOW_MASK            (0xFFFFU)
#define WDOG_TMROUTL_TIMEROUTLOW_SHIFT           (0U)
#define WDOG_TMROUTL_TIMEROUTLOW(x)              (((uint16_t)(((uint16_t)(x)) << WDOG_TMROUTL_TIMEROUTLOW_SHIFT)) & WDOG_TMROUTL_TIMEROUTLOW_MASK)
/*! @} */

/*! @name RSTCNT - Watchdog Reset Count register */
/*! @{ */

#define WDOG_RSTCNT_RSTCNT_MASK                  (0xFFFFU)
#define WDOG_RSTCNT_RSTCNT_SHIFT                 (0U)
#define WDOG_RSTCNT_RSTCNT(x)                    (((uint16_t)(((uint16_t)(x)) << WDOG_RSTCNT_RSTCNT_SHIFT)) & WDOG_RSTCNT_RSTCNT_MASK)
/*! @} */

/*! @name PRESC - Watchdog Prescaler register */
/*! @{ */

#define WDOG_PRESC_PRESCVAL_MASK                 (0x700U)
#define WDOG_PRESC_PRESCVAL_SHIFT                (8U)
#define WDOG_PRESC_PRESCVAL(x)                   (((uint16_t)(((uint16_t)(x)) << WDOG_PRESC_PRESCVAL_SHIFT)) & WDOG_PRESC_PRESCVAL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group WDOG_Register_Masks */


/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG base address */
#define WDOG_BASE                                (0x40053000u)
/** Peripheral WDOG base pointer */
#define WDOG                                     ((WDOG_Type *)WDOG_BASE)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS                          { WDOG_BASE }
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           { WDOG }
/** Interrupt vectors for the WDOG peripheral type */
#define WDOG_IRQS                                { WDOG_IRQn }

/*!
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- XBAR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Peripheral_Access_Layer XBAR Peripheral Access Layer
 * @{
 */

/** XBAR - Register Layout Typedef */
typedef struct {
  __IO uint16_t SEL0;                              /**< Crossbar Select Register 0, offset: 0x0 */
  __IO uint16_t SEL1;                              /**< Crossbar Select Register 1, offset: 0x2 */
  __IO uint16_t SEL2;                              /**< Crossbar Select Register 2, offset: 0x4 */
  __IO uint16_t SEL3;                              /**< Crossbar Select Register 3, offset: 0x6 */
  __IO uint16_t SEL4;                              /**< Crossbar Select Register 4, offset: 0x8 */
  __IO uint16_t SEL5;                              /**< Crossbar Select Register 5, offset: 0xA */
  __IO uint16_t SEL6;                              /**< Crossbar Select Register 6, offset: 0xC */
  __IO uint16_t SEL7;                              /**< Crossbar Select Register 7, offset: 0xE */
  __IO uint16_t SEL8;                              /**< Crossbar Select Register 8, offset: 0x10 */
  __IO uint16_t SEL9;                              /**< Crossbar Select Register 9, offset: 0x12 */
  __IO uint16_t SEL10;                             /**< Crossbar Select Register 10, offset: 0x14 */
  __IO uint16_t SEL11;                             /**< Crossbar Select Register 11, offset: 0x16 */
  __IO uint16_t SEL12;                             /**< Crossbar Select Register 12, offset: 0x18 */
  __IO uint16_t SEL13;                             /**< Crossbar Select Register 13, offset: 0x1A */
  __IO uint16_t SEL14;                             /**< Crossbar Select Register 14, offset: 0x1C */
  __IO uint16_t SEL15;                             /**< Crossbar Select Register 15, offset: 0x1E */
  __IO uint16_t SEL16;                             /**< Crossbar Select Register 16, offset: 0x20 */
  __IO uint16_t CTRL0;                             /**< Crossbar Control Register 0, offset: 0x22 */
} XBAR_Type;

/* ----------------------------------------------------------------------------
   -- XBAR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XBAR_Register_Masks XBAR Register Masks
 * @{
 */

/*! @name SEL0 - Crossbar Select Register 0 */
/*! @{ */

#define XBAR_SEL0_SEL0_MASK                      (0x3FU)
#define XBAR_SEL0_SEL0_SHIFT                     (0U)
/*! SEL0
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL0_SEL0(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL0_SEL0_SHIFT)) & XBAR_SEL0_SEL0_MASK)

#define XBAR_SEL0_SEL1_MASK                      (0x3F00U)
#define XBAR_SEL0_SEL1_SHIFT                     (8U)
/*! SEL1
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL0_SEL1(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL0_SEL1_SHIFT)) & XBAR_SEL0_SEL1_MASK)
/*! @} */

/*! @name SEL1 - Crossbar Select Register 1 */
/*! @{ */

#define XBAR_SEL1_SEL2_MASK                      (0x3FU)
#define XBAR_SEL1_SEL2_SHIFT                     (0U)
/*! SEL2
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL1_SEL2(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL1_SEL2_SHIFT)) & XBAR_SEL1_SEL2_MASK)

#define XBAR_SEL1_SEL3_MASK                      (0x3F00U)
#define XBAR_SEL1_SEL3_SHIFT                     (8U)
/*! SEL3
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL1_SEL3(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL1_SEL3_SHIFT)) & XBAR_SEL1_SEL3_MASK)
/*! @} */

/*! @name SEL2 - Crossbar Select Register 2 */
/*! @{ */

#define XBAR_SEL2_SEL4_MASK                      (0x3FU)
#define XBAR_SEL2_SEL4_SHIFT                     (0U)
/*! SEL4
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL2_SEL4(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL2_SEL4_SHIFT)) & XBAR_SEL2_SEL4_MASK)

#define XBAR_SEL2_SEL5_MASK                      (0x3F00U)
#define XBAR_SEL2_SEL5_SHIFT                     (8U)
/*! SEL5
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL2_SEL5(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL2_SEL5_SHIFT)) & XBAR_SEL2_SEL5_MASK)
/*! @} */

/*! @name SEL3 - Crossbar Select Register 3 */
/*! @{ */

#define XBAR_SEL3_SEL6_MASK                      (0x3FU)
#define XBAR_SEL3_SEL6_SHIFT                     (0U)
/*! SEL6
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL3_SEL6(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL3_SEL6_SHIFT)) & XBAR_SEL3_SEL6_MASK)

#define XBAR_SEL3_SEL7_MASK                      (0x3F00U)
#define XBAR_SEL3_SEL7_SHIFT                     (8U)
/*! SEL7
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL3_SEL7(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL3_SEL7_SHIFT)) & XBAR_SEL3_SEL7_MASK)
/*! @} */

/*! @name SEL4 - Crossbar Select Register 4 */
/*! @{ */

#define XBAR_SEL4_SEL8_MASK                      (0x3FU)
#define XBAR_SEL4_SEL8_SHIFT                     (0U)
/*! SEL8
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL4_SEL8(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL4_SEL8_SHIFT)) & XBAR_SEL4_SEL8_MASK)

#define XBAR_SEL4_SEL9_MASK                      (0x3F00U)
#define XBAR_SEL4_SEL9_SHIFT                     (8U)
/*! SEL9
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL4_SEL9(x)                        (((uint16_t)(((uint16_t)(x)) << XBAR_SEL4_SEL9_SHIFT)) & XBAR_SEL4_SEL9_MASK)
/*! @} */

/*! @name SEL5 - Crossbar Select Register 5 */
/*! @{ */

#define XBAR_SEL5_SEL10_MASK                     (0x3FU)
#define XBAR_SEL5_SEL10_SHIFT                    (0U)
/*! SEL10
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL5_SEL10(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL5_SEL10_SHIFT)) & XBAR_SEL5_SEL10_MASK)

#define XBAR_SEL5_SEL11_MASK                     (0x3F00U)
#define XBAR_SEL5_SEL11_SHIFT                    (8U)
/*! SEL11
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL5_SEL11(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL5_SEL11_SHIFT)) & XBAR_SEL5_SEL11_MASK)
/*! @} */

/*! @name SEL6 - Crossbar Select Register 6 */
/*! @{ */

#define XBAR_SEL6_SEL12_MASK                     (0x3FU)
#define XBAR_SEL6_SEL12_SHIFT                    (0U)
/*! SEL12
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL6_SEL12(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL6_SEL12_SHIFT)) & XBAR_SEL6_SEL12_MASK)

#define XBAR_SEL6_SEL13_MASK                     (0x3F00U)
#define XBAR_SEL6_SEL13_SHIFT                    (8U)
/*! SEL13
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL6_SEL13(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL6_SEL13_SHIFT)) & XBAR_SEL6_SEL13_MASK)
/*! @} */

/*! @name SEL7 - Crossbar Select Register 7 */
/*! @{ */

#define XBAR_SEL7_SEL14_MASK                     (0x3FU)
#define XBAR_SEL7_SEL14_SHIFT                    (0U)
/*! SEL14
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL7_SEL14(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL7_SEL14_SHIFT)) & XBAR_SEL7_SEL14_MASK)

#define XBAR_SEL7_SEL15_MASK                     (0x3F00U)
#define XBAR_SEL7_SEL15_SHIFT                    (8U)
/*! SEL15
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL7_SEL15(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL7_SEL15_SHIFT)) & XBAR_SEL7_SEL15_MASK)
/*! @} */

/*! @name SEL8 - Crossbar Select Register 8 */
/*! @{ */

#define XBAR_SEL8_SEL16_MASK                     (0x3FU)
#define XBAR_SEL8_SEL16_SHIFT                    (0U)
/*! SEL16
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL8_SEL16(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL8_SEL16_SHIFT)) & XBAR_SEL8_SEL16_MASK)

#define XBAR_SEL8_SEL17_MASK                     (0x3F00U)
#define XBAR_SEL8_SEL17_SHIFT                    (8U)
/*! SEL17
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL8_SEL17(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL8_SEL17_SHIFT)) & XBAR_SEL8_SEL17_MASK)
/*! @} */

/*! @name SEL9 - Crossbar Select Register 9 */
/*! @{ */

#define XBAR_SEL9_SEL18_MASK                     (0x3FU)
#define XBAR_SEL9_SEL18_SHIFT                    (0U)
/*! SEL18
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL9_SEL18(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL9_SEL18_SHIFT)) & XBAR_SEL9_SEL18_MASK)

#define XBAR_SEL9_SEL19_MASK                     (0x3F00U)
#define XBAR_SEL9_SEL19_SHIFT                    (8U)
/*! SEL19
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL9_SEL19(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_SEL9_SEL19_SHIFT)) & XBAR_SEL9_SEL19_MASK)
/*! @} */

/*! @name SEL10 - Crossbar Select Register 10 */
/*! @{ */

#define XBAR_SEL10_SEL20_MASK                    (0x3FU)
#define XBAR_SEL10_SEL20_SHIFT                   (0U)
/*! SEL20
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL10_SEL20(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL10_SEL20_SHIFT)) & XBAR_SEL10_SEL20_MASK)

#define XBAR_SEL10_SEL21_MASK                    (0x3F00U)
#define XBAR_SEL10_SEL21_SHIFT                   (8U)
/*! SEL21
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL10_SEL21(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL10_SEL21_SHIFT)) & XBAR_SEL10_SEL21_MASK)
/*! @} */

/*! @name SEL11 - Crossbar Select Register 11 */
/*! @{ */

#define XBAR_SEL11_SEL22_MASK                    (0x3FU)
#define XBAR_SEL11_SEL22_SHIFT                   (0U)
/*! SEL22
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL11_SEL22(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL11_SEL22_SHIFT)) & XBAR_SEL11_SEL22_MASK)

#define XBAR_SEL11_SEL23_MASK                    (0x3F00U)
#define XBAR_SEL11_SEL23_SHIFT                   (8U)
/*! SEL23
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL11_SEL23(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL11_SEL23_SHIFT)) & XBAR_SEL11_SEL23_MASK)
/*! @} */

/*! @name SEL12 - Crossbar Select Register 12 */
/*! @{ */

#define XBAR_SEL12_SEL24_MASK                    (0x3FU)
#define XBAR_SEL12_SEL24_SHIFT                   (0U)
/*! SEL24
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL12_SEL24(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL12_SEL24_SHIFT)) & XBAR_SEL12_SEL24_MASK)

#define XBAR_SEL12_SEL25_MASK                    (0x3F00U)
#define XBAR_SEL12_SEL25_SHIFT                   (8U)
/*! SEL25
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL12_SEL25(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL12_SEL25_SHIFT)) & XBAR_SEL12_SEL25_MASK)
/*! @} */

/*! @name SEL13 - Crossbar Select Register 13 */
/*! @{ */

#define XBAR_SEL13_SEL26_MASK                    (0x3FU)
#define XBAR_SEL13_SEL26_SHIFT                   (0U)
/*! SEL26
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL13_SEL26(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL13_SEL26_SHIFT)) & XBAR_SEL13_SEL26_MASK)

#define XBAR_SEL13_SEL27_MASK                    (0x3F00U)
#define XBAR_SEL13_SEL27_SHIFT                   (8U)
/*! SEL27
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL13_SEL27(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL13_SEL27_SHIFT)) & XBAR_SEL13_SEL27_MASK)
/*! @} */

/*! @name SEL14 - Crossbar Select Register 14 */
/*! @{ */

#define XBAR_SEL14_SEL28_MASK                    (0x3FU)
#define XBAR_SEL14_SEL28_SHIFT                   (0U)
/*! SEL28
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL14_SEL28(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL14_SEL28_SHIFT)) & XBAR_SEL14_SEL28_MASK)

#define XBAR_SEL14_SEL29_MASK                    (0x3F00U)
#define XBAR_SEL14_SEL29_SHIFT                   (8U)
/*! SEL29
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL14_SEL29(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL14_SEL29_SHIFT)) & XBAR_SEL14_SEL29_MASK)
/*! @} */

/*! @name SEL15 - Crossbar Select Register 15 */
/*! @{ */

#define XBAR_SEL15_SEL30_MASK                    (0x3FU)
#define XBAR_SEL15_SEL30_SHIFT                   (0U)
/*! SEL30
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL15_SEL30(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL15_SEL30_SHIFT)) & XBAR_SEL15_SEL30_MASK)

#define XBAR_SEL15_SEL31_MASK                    (0x3F00U)
#define XBAR_SEL15_SEL31_SHIFT                   (8U)
/*! SEL31
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL15_SEL31(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL15_SEL31_SHIFT)) & XBAR_SEL15_SEL31_MASK)
/*! @} */

/*! @name SEL16 - Crossbar Select Register 16 */
/*! @{ */

#define XBAR_SEL16_SEL32_MASK                    (0x3FU)
#define XBAR_SEL16_SEL32_SHIFT                   (0U)
/*! SEL32
 *  0b000000..Logic 1 (VDD)
 *  0b000001..Logic 0 (VSS)
 *  0b000010..AFE modulator clock output
 *  0b000011..AFE modulator data output
 *  0b000100..LPTimer Output
 *  0b000101..Clock Output
 *  0b000110..Quad Timer channel 0 output
 *  0b000111..Quad Timer channel 1 output
 *  0b001000..Quad Timer channel 2 output
 *  0b001001..Quad Timer channel 3 output
 *  0b001010..iRTC Clock Output
 *  0b001011..CMP0 Output
 *  0b001100..CMP1 Output
 *  0b001101..iRTC Alarm Output
 *  0b001110..UART TX Output (after modulation)
 *  0b001111..EWM Output (EWM_OUT)
 *  0b010000..PIT Output
 *  0b010001..XBAR Input pin 0
 *  0b010010..XBAR Input pin 1
 *  0b010011..XBAR Input pin 2
 *  0b010100..XBAR Input pin 3
 *  0b010101..XBAR Input pin 4
 *  0b010110..XBAR Input pin 5
 *  0b010111..XBAR Input pin 6
 *  0b011000..XBAR Input pin 7
 *  0b011001..XBAR Input pin 8
 *  0b011010..ORed conversion complete flag for all SAR ADC channels
 *  0b011011..ORed conversion complete flag for all AFE channels
 *  0b011100..AFE Channel 0 conversion complete
 *  0b011101..AFE Channel 1 conversion complete
 *  0b011110..AFE Channel 2 conversion complete
 *  0b011111..AFE Channel 3 conversion complete
 *  0b100000..DMA Done Signal
 */
#define XBAR_SEL16_SEL32(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_SEL16_SEL32_SHIFT)) & XBAR_SEL16_SEL32_MASK)
/*! @} */

/*! @name CTRL0 - Crossbar Control Register 0 */
/*! @{ */

#define XBAR_CTRL0_DEN0_MASK                     (0x1U)
#define XBAR_CTRL0_DEN0_SHIFT                    (0U)
/*! DEN0 - DMA Enable for XBAR_OUT0
 *  0b0..DMA disabled
 *  0b1..DMA enabled
 */
#define XBAR_CTRL0_DEN0(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_CTRL0_DEN0_SHIFT)) & XBAR_CTRL0_DEN0_MASK)

#define XBAR_CTRL0_IEN0_MASK                     (0x2U)
#define XBAR_CTRL0_IEN0_SHIFT                    (1U)
/*! IEN0 - Interrupt Enable for XBAR_OUT0
 *  0b0..Interrupt disabled
 *  0b1..Interrupt enabled
 */
#define XBAR_CTRL0_IEN0(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_CTRL0_IEN0_SHIFT)) & XBAR_CTRL0_IEN0_MASK)

#define XBAR_CTRL0_EDGE0_MASK                    (0xCU)
#define XBAR_CTRL0_EDGE0_SHIFT                   (2U)
/*! EDGE0 - Active edge for edge detection on XBAR_OUT0
 *  0b00..STS0 never asserts
 *  0b01..STS0 asserts on rising edges of XBAR_OUT0
 *  0b10..STS0 asserts on falling edges of XBAR_OUT0
 *  0b11..STS0 asserts on rising and falling edges of XBAR_OUT0
 */
#define XBAR_CTRL0_EDGE0(x)                      (((uint16_t)(((uint16_t)(x)) << XBAR_CTRL0_EDGE0_SHIFT)) & XBAR_CTRL0_EDGE0_MASK)

#define XBAR_CTRL0_STS0_MASK                     (0x10U)
#define XBAR_CTRL0_STS0_SHIFT                    (4U)
/*! STS0 - Edge detection status for XBAR_OUT0
 *  0b0..Active edge not yet detected on XBAR_OUT0
 *  0b1..Active edge detected on XBAR_OUT0
 */
#define XBAR_CTRL0_STS0(x)                       (((uint16_t)(((uint16_t)(x)) << XBAR_CTRL0_STS0_SHIFT)) & XBAR_CTRL0_STS0_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group XBAR_Register_Masks */


/* XBAR - Peripheral instance base addresses */
/** Peripheral XBAR base address */
#define XBAR_BASE                                (0x40055000u)
/** Peripheral XBAR base pointer */
#define XBAR                                     ((XBAR_Type *)XBAR_BASE)
/** Array initializer of XBAR peripheral base addresses */
#define XBAR_BASE_ADDRS                          { XBAR_BASE }
/** Array initializer of XBAR peripheral base pointers */
#define XBAR_BASE_PTRS                           { XBAR }
/** Interrupt vectors for the XBAR peripheral type */
#define XBAR_IRQS                                { XBAR_IRQn }

/*!
 * @}
 */ /* end of group XBAR_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
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


#endif  /* _MKM14ZA5_H_ */

